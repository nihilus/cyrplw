#include "rubber.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

struct Rubber_mem *
new_Rubber()
{
  struct Rubber_mem *res = (struct Rubber_mem *)malloc(sizeof(struct Rubber_mem));
  if ( NULL == res )
  {
    fprintf(stderr, "Cannot alloc new Rubber_mem\n");
    abort();
  }
  res->size = 0;
  if ( NULL == ( res->p = (char *)malloc( res->alloced = INITIAL_RUBBER ) ) )
  {
    fprintf(stderr, "Cannot alloc initial Rubber_mem\n");
    abort();
  }
  return res;
}

void
del_Rubber(struct Rubber_mem *ptr)
{
  if ( NULL == ptr )
   return;
  if ( ptr->p != NULL )
   free(ptr->p);
  free(ptr);
}

void
add_Rubber(struct Rubber_mem *ptr, const char *buffer, int len)
{
  if ( ptr->alloced - ptr->size < len )
  {
    ptr->p = (char *)realloc(ptr->p, ptr->alloced *= INCREMENT);
    if ( NULL == ptr->p )
    {
      fprintf(stderr, "Cannot realloc %d bytes in add_Rubber\n",
       ptr->alloced );
      abort();
    }
  }
  if ( len == 1 )
   *(ptr->p + ptr->size++) = *buffer;
  else
  {
   memcpy(ptr->p + ptr->size, buffer, len);
   ptr->size += len;
  }
}

int
rp_read_string(FILE *fp, struct Rubber_mem *r)
{
  static char zero_char = '\0';
  static char lf_char = (char)0xd;
  int c;
  int is_d = 0, res = 0;
  
  /* first reset string */
  r->size = 0;
  while( !feof(fp) )
  {
    c = fgetc(fp);
    if ( feof(fp) )
     break;
    if ( c == 0xa )
    {
      add_Rubber(r, &zero_char, 1);
      return res;
    }
    if ( is_d )
    {
     add_Rubber(r, &lf_char, 1);
     res++;
     is_d = 0;
    }
    if ( c == 0xd )
    {
     is_d = 1;
     continue;
    }
    add_Rubber(r, (char *)&c, 1);
    res++;
  }
  add_Rubber(r, &zero_char, 1);
  return res;
}

/* to share this function between many modules */
char *trimstring(char *str)
{
  char *ptr;
  while(*str && isspace(*str))
   str++;
  if ( !*str )
   return str;
  ptr = str + strlen(str) - 1;
  while( ptr != str && isspace(*ptr) )
   ptr++;
  *(ptr + 1) = '\0';
  return str;
}

