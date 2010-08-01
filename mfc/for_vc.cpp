//#include <rp/rp.hpp>
#include <ida.hpp>
#include <bytes.hpp>
#include <segment.hpp>

void idaapi
copy_fromIDA(uchar *membuf, ea_t src_a, ulong len)
{
  ulong i;
  for ( i = 0; i < (len & ~4); i+=4 )
  {
    *((int *)(membuf + i)) = get_long(src_a + i);
  }
  if ( i != len )
   for ( ulong i1 = (len & 4); i1; i1-- )
   {
    *(membuf + len - i1 ) = get_byte(src_a + len - i1);
   }
}

/* read zero-ended string from IDA. Warning - you responsible for freeing
  returned string */
char * idaapi
read_zero_ended_string(ea_t ea)
{
  segment_t *seg = getseg(ea);
  if ( !seg )
   return NULL;
  int len = 0;
  int i;
  long c;
  for ( i = ea; i < seg->endEA; i++ )
  {
    c = get_byte(i);
    if ( !c )
     break;
    len++;
  }
  if (!len)
   return NULL;
  char *res = (char *)qalloc(len + 1);
  copy_fromIDA((unsigned char *)res, ea, len + 1);
  return res;
}

char * idaapi
read_zero_ended_unicode_string(ea_t ea)
{
  segment_t *seg = getseg(ea);
  if ( !seg )
   return NULL;
  int len = 0;
  int i;
  long c;
  for ( i = ea; i < seg->endEA; i++ )
  {
    c = get_word(i);
    if ( !c )
     break;
    len++;
  }
  if (!len)
   return NULL;
  len = (len + 1) << 1;
  char *res = (char *)qalloc(len);
  copy_fromIDA((unsigned char *)res, ea, len);
  return res;
}
/* set comment - may be called several times with same comment */
void idaapi
rp_set_comment(ea_t ea, const char *comment, bool is_before, bool rptbl)
{
   if ( NULL == comment || ! *comment )
    return;
   ssize_t cmt_size;
   cmt_size = get_cmt(ea, rptbl, NULL, 0);
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

/* check for available space in loaded file */
bool idaapi
check_for_available_space(ea_t from_a, ulong size)
{
  segment_t *s;
  while(size > 0)
  {
    s = getseg(from_a);
    if ( NULL == s )
      return false;
    if ( s->endEA >= from_a + size )
     return true;
    size -= s->endEA - from_a + 1;
    from_a = s->endEA + 1;
  }
  return true;
}
