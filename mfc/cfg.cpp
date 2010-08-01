#include "cfg.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern "C" const char *__stdcall idadir(char *);

Cfg::Cfg(char *cfg_name)
{
  ida_dir = idadir(NULL);
  ida_len = strlen(ida_dir);
  fp = NULL;
  alloced = 0;
  ptr = NULL;
  m_name = _strdup(cfg_name);
  m_name_len = strlen(m_name);
}

Cfg::~Cfg()
{
  if ( fp )
   fclose(fp);
  if ( ptr )
   free(ptr);
  if ( m_name )
   free(m_name);
}

char *Cfg::read_string(int &size)
{
  if ( !alloced )
  {
    alloced = 20;
    ptr = (char *)malloc(alloced);
  }
  char c;
  size = 0;
  while( !feof(fp) )
  {
    c = fgetc(fp);
    if ( feof(fp) )
     break;
    if ( !c )
     break;
    if ( c == 0xa )
     break;
    if ( c == 0xd )
    {
      if ( feof(fp) )
       break;
      c = fgetc(fp);
      if ( c == 0xa )
       break;
      else
       ungetc(c, fp);
    }
    /* add this symbol */
    if ( size >= alloced )
     ptr = (char *)realloc(ptr, alloced *= 2);
    ptr[size++] = c;
  }
  /* we need to add last zero symbol */
  if ( size >= alloced )
   ptr = (char *)realloc(ptr, alloced + 1);
  ptr[size] = 0;
  return ptr;  
}

char *Cfg::my_read_string()
{
  char *res;
  int size;
  while( !feof(fp) )
  {
    res = read_string(size);
    if ( !size )
     continue;
    while( *res && isspace(*res) )
     res++;
    if ( !*res )
     continue;
    if ( *res == '#' )
     continue;
    return res;
  }
  return NULL;  
}

/* format is easy - KEY=value */
void Cfg::process(char *target)
{
  char *eq = strchr(target, '=');
  if ( !eq )
   return;
  char *value = eq + 1;
  *eq-- = 0;
  while( eq > target && isspace(*eq) )
    *eq-- = 0;
  while( *value && isspace(*value) )
    value++;
  parse(target, value);
}

int Cfg::read()
{
  /* 1) construct name of cfg file */
  char *fname = (char *)malloc(ida_len + 3 + m_name_len + 8);
  strcpy(fname, ida_dir);
  if ( fname[ida_len - 1] != '\\' )
  {
    fname[ida_len] = '\\';
    fname[ida_len + 1] = 0;
  }
  strcat(fname, "plugins\\");
  strcat(fname, m_name);
  fp = fopen(fname, "r");
  if ( fp == NULL )
  {
    free(fname);
    return 0;
  }
  /* 2) read and parse */
  int res = 0;
  char *curr;
  while( curr = my_read_string() )
  {
    res++;
    process(curr);
  }
  /* 3) cleanup */
  fclose(fp);
  fp = NULL;
  free(fname);
  return res;
}