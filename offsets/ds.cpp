#include "ds.hpp"
#include <ida.hpp>
#include <kernwin.hpp>
#include <segment.hpp>
#include "rubber.h"
#include <sys/stat.h>
#include "ds.hpp"
#include <ctype.h>
#include <struct.hpp>
#include <name.hpp>
#include <diskio.hpp>
#include <loader.hpp>
#include <sys/stat.h>
#include "rp_debug.h"

static int
mapping_cmp(const void *a, const void *b)
{
  ea_t a1 = (ea_t)a, 
       b1 = (ea_t)b;
  if ( a1 < b1 )
   return -1;
  if ( a1 > b1 )
   return 1;
  return 0;
}

dnode_t *
RP_mapping::is_presented(ea_t addr)
{ 
  if ( NULL == mapping )
   return (dnode_t *)NULL;
  return dict_lookup(mapping, (const void *)addr);  
}

RP_mapping::RP_mapping(char *fn, int _verbose)
 : verbose(_verbose)
{
  old_time = 0;
  our_file = fn;
  mapping = dict_create(DICTCOUNT_T_MAX, mapping_cmp);
}

RP_mapping::~RP_mapping()
{
  if ( NULL != mapping )
  {
    dict_free(mapping);
    dict_destroy(mapping);
  }
  if ( our_file != NULL )
   qfree(our_file);
}

int
RP_mapping::successfull_creating()
{
  if ( NULL != mapping )
   return 1;
  else
   return 0;
}

void
RP_mapping::clear()
{
  if ( NULL == mapping )
   return;
  dict_free(mapping);
}

/*** file I/O ***/
int
RP_mapping::read_config()
{
/* Logic for this function: 
 * time of prev last file changes stored in old_time
 * if it is zero - try to read file at first time
 * if not - check current modify time
 * if file was changed - reread config
 */
 struct stat rp_stat;
 FILE *fp;
 
 if ( old_time == 0 )
 {
   fp = fopen(our_file, "r");
   if ( NULL == fp )
   {
     return 0;
   }
   fstat(fileno(fp), &rp_stat);
   old_time = rp_stat.st_mtime;
   int res = read_file(fp);
   fclose(fp);
   return res;
 }
 if ( -1 == stat(our_file, &rp_stat) )
  return 1; // ?? may be file already killed ?
 if ( old_time >= rp_stat.st_mtime )
  return 1;
 fp = fopen(our_file, "r");
 if ( NULL == fp )
  return 0;
 int res = read_file(fp);
 fclose(fp);
 return res;
}

int
RP_mapping::process_string(char *str, int ln)
{
  char *arg1, *arg2;
  for ( arg1 = arg2 = str; !isspace( *arg2) && *arg2; arg2++ )
    ;
  if ( !*arg2 )
   return 0;
  *arg2++ = 0x0;
  if ( !*arg2)
   return 0;
  for ( ; *arg2 && isspace(*arg2); arg2++ )
   ;
  if ( !*arg2 )
   return 0;
  // next - just trim all spaces at end
  char *ptr = arg2 + 1;
  for ( ; !isspace(*ptr) && *ptr; ptr++ )
   ;
  *ptr = 0x0;
  /* O`k, now arg1 contains address or name and arg2 contains name of struct */
  // first check for struct presence
  tid_t tid = get_struc_id(arg2);
  if ( BADADDR == tid )
  {
    if ( verbose )
      msg("Cannot find struct '%s'\n", arg2);
    return 0;
  }
  // next try to resolve first arg as name
  ea_t ea = get_name_ea(BADADDR, arg1);
  if ( ea != BADADDR )
  {
   /* first check for already presenting */
   dnode_t *again = is_presented(ea);
   if ( NULL != again )
   {
    if ( verbose )
      msg("Warning, address %X already in dictionary, overwrite\n", ea);
    dnode_put(again, (void *)tid);
   } else {
    /* place to dict new mapping name -> tid_t */
    dict_alloc_insert(mapping, (const void *)ea, (void *)tid);
   }
#ifdef RP_DEBUG
 msg("Mapping %X (%s) -> %s (%X) \n", ea, arg1, arg2, tid);
#endif
   return 1;
  }
  /* well may be we shold add yet one underscore at begin of name ? */
  {
   int len = strlen(arg1);
   char *dup = (char *)qalloc(len + 2);
   *dup = '_';
   strcpy(dup + 1, arg1);
   ea = get_name_ea(BADADDR, dup);
   if ( BADADDR != ea )
   {
     dnode_t *again = is_presented(ea);
     if ( NULL != again )
     {
      if ( verbose )
       msg("Warning, address %X already in dictionary, overwrite\n", ea);
      dnode_put(again, (void *)tid);
     } else {
      dict_alloc_insert(mapping, (const void *)ea, (void *)tid);
     }
#ifdef RP_DEBUG
 msg("Mapping %X (%s) -> %s (%X) \n", ea, dup, arg2, tid);
#endif
     qfree(dup);
     return 1;
   }
   qfree(dup);
  }
  /* well - may be we has address ? */
  if ( *arg1 == '0' && ( arg1[1] == 'x' || arg1[1] == 'X' ) )
  {
   arg1 += 2;
   if ( ! *arg1 )
   {
    if ( verbose )
      msg("Line %d. Bad address '%s'\n", ln, arg1 - 2);
    return 0;
   }
  }
  char *notused;
  ea = strtol(arg1, &notused, 0x10);
  if ( !ea )
  {
   if ( verbose )
     msg("Line %d. Bad address '%s'\n", ln, arg1);
   return 0;
  }
  // O`k it seems that we really has some address. Lets check it
  if ( NULL == getseg(ea) )
  {
   if ( verbose )
     msg("Line %d. Address %X is not in your file\n", ln, ea);
   return 0;
  }
  dnode_t *again = is_presented(ea);
  if ( NULL != again )
  {
   if ( verbose )
    msg("Warning, address %X already in dictionary, overwrite\n", ea);
   dnode_put(again, (void *)tid);
  } else {
   dict_alloc_insert(mapping, (const void *)ea, (void *)tid);
  }
#ifdef RP_DEBUG
 msg("Mapping %X -> %s (%X) \n", ea, arg2, tid);
#endif
  return 1;  
}

int
RP_mapping::read_file(FILE *fp)
{
  clear();
  if ( mapping == NULL )
  {
   if ( verbose )
    msg("mapping problems");
   return 0;
  }
  Rubber_mem *str = new_Rubber();
  char *ptr;
  int linenum = 0;

  while( !feof(fp) )
  {
   rp_read_string(fp, str);
   linenum++;
   ptr = trimstring(str->p);
   if ( ! *ptr || *ptr == '#' ) // empty strings and comments are ignored
    continue;
   process_string(ptr, linenum);
  }
  if ( NULL != str )
   del_Rubber(str);
  return dict_count(mapping);
}

/* Dumb algorithm of filename searching:
 * 1) get filename of currently disassembled filename
 * 2) chomp ext
 * 3) add our ext and try to open
 * 4) if failed - get name and add our exe
 * 5) and apply standard IDA file search mechanism (over getsysfile)
 * That`s all folks
 */
char *
RP_mapping::find_path(const char *my_ext)
{
  int my_ext_len = 0;
  /* lets in beginning cut all initial dots from proposed extentsion */
  if ( my_ext != NULL )
  {
    while ( *my_ext && *my_ext == '.' )
     my_ext++;
    if ( *my_ext )
     my_ext_len = strlen(my_ext);
  }
  /* try to find filename of current database */
  char own_name[_MAX_PATH];
  get_input_file_path(own_name, sizeof(own_name));
  if ( NULL == own_name )
  {
    return NULL;
  }
  /* main processing */
  char *path = NULL, 
       *file = NULL, 
       *ext = NULL;
  qsplitpath(own_name, &path, &file);
  if ( file == NULL )
   return NULL;

  char *filebase = NULL;
  qsplitfile(file, NULL, &ext);
  if ( ext != NULL )
  {
    int base_len = ext - file;
    filebase = (char *)qalloc(base_len);
    strncpy(filebase, file, base_len - 1);
    filebase[base_len - 1] = 0x0;
  } else
    filebase = qstrdup(file);
  int filebase_len = strlen(filebase);
  /* O`k lets try p 1) */
  if ( NULL != path )
  {
    int need_len;
    int base_len = file - own_name;
    need_len = base_len + 3 + filebase_len + my_ext_len;
    char *res = (char *)qalloc(need_len);
    strncpy(res, path, base_len);
    res[base_len - 1] = '\\';
    strcpy(res + base_len, filebase);
    if ( my_ext != NULL )
    {
      strcat(res, ".");
      strcat(res, my_ext);
    }
    struct stat st;
#ifdef RP_DEBUG
 msg("Try %s\n", res);
#endif
    if ( -1 != stat(res, &st) )
    {
#ifdef RP_DEBUG
 msg("Find %s (time %X)\n", res, st.st_mtime );
#endif
      qfree(filebase);
      return res;
    }
    qfree(res);
  }
  /* next part do same thing as qmakefile missed by Ilfak */
  char *st_buf = filebase;
  if ( my_ext_len )
  {
    st_buf = (char *)qalloc(2 + my_ext_len + filebase_len);
    strcpy(st_buf, filebase);
    st_buf[filebase_len] = '.';
    strcpy(st_buf + filebase_len + 1, my_ext);
  }
#ifdef RP_DEBUG
 msg("st_buf '%s', my_ext_len %d, filebase_len %d, my_ext %s\n", 
    st_buf, my_ext_len, filebase_len, my_ext);
#endif
  char *res = (char *)qalloc(_MAX_PATH + 1);
  char *ret_val = getsysfile(res, _MAX_PATH, st_buf, CFG_SUBDIR);
  if ( NULL == ret_val )
    qfree(res);
  if ( st_buf != filebase )
    qfree(st_buf);
  if ( filebase != NULL )
    qfree(filebase);
  return ret_val;
}  
