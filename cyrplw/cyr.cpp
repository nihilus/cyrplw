// dirty hack
#define USE_DANGEROUS_FUNCTIONS

#include <ida.hpp>
#include <idp.hpp>
#include <loader.hpp>
#include <kernwin.hpp>
#include <bytes.hpp>
#include <entry.hpp>

/* set comment - may be called several times with same comment */
void idaapi
rp_set_comment(ea_t ea, const char *comment, bool is_before, bool rptbl = false)
{
   if ( NULL == comment || ! *comment )
    return;
   ssize_t cmt_size = get_cmt(ea, rptbl, NULL, 0);
   if ( !cmt_size || -1 == cmt_size )
   {
      set_cmt(ea, comment, rptbl);
      return;
   }
   char *old_cmt = (char *)qalloc(cmt_size + 1);
   get_cmt(ea, rptbl, old_cmt, cmt_size);
   if ( NULL != strstr(old_cmt, comment) )
   {
     qfree(old_cmt);
     return;
   }
   if ( is_before )
   {
     int cl = strlen(comment);
     char *a = (char *)qalloc(cl + 2 + strlen(old_cmt));
     strcpy(a, comment);
     a[cl] = ',';
     strcpy(a+cl+1, old_cmt);
     set_cmt(ea, a, rptbl);
     qfree(a);
   } else
   {
     append_cmt(ea, "," , rptbl );
     append_cmt(ea, comment, rptbl );
   }
   qfree(old_cmt);
}

#define RP_ALT		0
#define RP_ISO		1
#define RP_KOI		2
#define RP_MAC		3
#define RP_WIN		4

short def_from = RP_ALT; /* IMHO most frequently used */
short def_to = RP_ALT;   /* for IDA console mode */

#include "output.c"

/******************** CONSTANTS *******************/
char CYR_comment[] = "Plugin for cyrillic support";
char CYR_help[] =
 "Plugin for cyrillic support\n"
  "\n"
  "Convert among russian code pages, also has basic Unicode support";
char CYR_wanted_name[] = "Cyrillic plugin";
char CYR_wanted_hotkey[] = "Alt-C";

void
processUnicode(ea_t from)
{
  ea_t end = from;
  long c;
  while(1)
  {
    c = get_word(end);
    if ( !c )
     break;
    end+=2;
  }
  if ( end == from )
   return;
  unsigned char *s = (unsigned char *)qalloc(end - from + 1);
  end = from;
  int i = 0;
  while(1)
  {
    c = get_word(end);
    if ( !c )
    {
      s[i] = 0x0;
      break;
    }
    if ( c & 0x0400 )
      s[i] = (c & 0xff) + 176;
    else
      s[i] = (c & 0xff);
    /* Unicode string in 1251 code page */
    if ( def_to != RP_WIN )
      s[i] = cyr_trans[RP_WIN][def_to][s[i]];
    end+=2;
    i++;
  }
  make_ascii_string(from, end - from, ASCSTR_UNICODE);
  rp_set_comment(from, (const char *)s, false);
  qfree(s);
}

void
CYR_run(int arg)
{
  ea_t curr_ea = get_screen_ea();
  ea_t s_start, s_end;
  long c;
  /* check if we need decode selected area */
  int selected = read_selection(&s_start, &s_end);
  segment_t *seg = NULL;
  if ( !selected )
  {
    seg = getseg(curr_ea);
    if ( NULL == seg )
    {
      warning("Cannot determine segment for current address 0x%X", curr_ea);
      return;
    }
  } else if ( s_start == s_end )
     return;
  // ask user about decoding
  const char format[] = "Cyrillic encoding params\n"
   " From         To\n"
   "<Alt:R>     <Alt:r>\n"
   "<Iso:R>     <Iso:r>\n"
   "<Koi:R>     <Koi:r>\n"
   "<Mac:R>     <Mac:r>\n"
   "<Win:R>     <Win:r>>\n"
   "<Unicode:R>>\n"
;
  if ( !AskUsingForm_c(format, &def_to, &def_from) )
    return;
  if ( def_from == 5 ) /* Unicode */
    processUnicode(curr_ea);
  else if ( selected )
  {
    /* is the code page the same ? */
    if ( def_from == def_to )
      return;
    ea_t curr, start = s_start;
    long processed = 0;
    /* convert selelected area with some strings */
    for ( curr = s_start; curr < s_end; curr++ )
    {
      c = get_byte(curr);
      if ( c )
      {
        processed++;
        c = cyr_trans[def_from][def_to][c];
        put_byte(curr, c);
      } else {
        if ( processed )
          make_ascii_string(start, processed, ASCSTR_C);
        processed = 0;
        start = curr + 1;
      }
    }
    if ( processed )
      make_ascii_string(start, processed, ASCSTR_C);
  } else
  {
    /* is the code page the same ? */
    if ( def_from == def_to )
      return;
    ea_t end = curr_ea;
    segment_t *s = getseg(end);
    /* convert string from current addr to first zero symbol */
    while(end < s->endEA)
    {
      c = get_byte(end);
      if ( !c )
        break;
      c = cyr_trans[def_from][def_to][c];
      put_byte(end, c);
      end++;
    }
    if ( end - curr_ea )
      make_ascii_string(curr_ea, end - curr_ea, ASCSTR_C);
  }
}

int
CYR_init(void)
{
 /* for Unix most preffered KOI8 */
 if ( inf.filetype == f_COFF ||
      inf.filetype == f_AR   ||
      inf.filetype == f_ELF  ||
      inf.filetype == f_AOUT )
 {
   def_from = RP_KOI;
   return PLUGIN_OK;
 }
 /* for Win32 - 1251 */
 if ( inf.filetype == f_PE )
 {
    def_from = RP_WIN;
    return PLUGIN_OK;
 }
 /* for MAC */
 if ( ph.id == PLFM_6800 ||
      ph.id == PLFM_PPC )
   def_from = RP_MAC;
 /* I know nothing about other combinations of file format/processor */
 return PLUGIN_OK;
}

void
CYR_term(void)
{ }

/*
 * PLUGIN description
 */
extern "C" plugin_t PLUGIN = {
  IDP_INTERFACE_VERSION,
  0,                    // plugin flags - ???
  CYR_init,             // initialize function
  CYR_term,             // terminate. this pointer may be NULL.
  CYR_run,              // invoke plugin
  CYR_comment,          // long comment about the plugin
  CYR_help,             // multiline help about the plugin
  CYR_wanted_name,      // the preferred short name of the plugin
  CYR_wanted_hotkey     // the preferred hotkey to run the plugin
};
