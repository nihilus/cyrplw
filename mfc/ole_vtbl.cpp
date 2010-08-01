#include <ida.hpp>
#include <idp.hpp>
#include <bytes.hpp>
#include <struct.hpp>
#include "tlb_buben.h"

struc_t *add_ole_vtbl(char *name)
{
  int len = strlen(name);
  char *vtbl_struct_name = (char *)qalloc(len + 6);
  strcpy(vtbl_struct_name, name);
  strcat(vtbl_struct_name, "_vtbl");
  tid_t tid = get_struc_id(vtbl_struct_name);
  if ( tid != BADADDR ) // already loaded
  {
    qfree(vtbl_struct_name);
    return NULL;
  }
  tid = add_struc(BADADDR, vtbl_struct_name, false);
  if ( tid == BADADDR )
  {
    msg("Cannot add VTBL for %s\n", name);
    qfree(vtbl_struct_name);
    return NULL;
  }
  struc_t *s = get_struc(tid);
  qfree(vtbl_struct_name);
  return s;  
}

void add_ole_vtbl_members(struc_t *s, struct buben_methods *methods, int size)
{
  int res;
  for ( int i = 0; i < size; i++ )
  {
    res = add_struc_member(s, methods[i].name, methods[i].offset, dwrdflag() /*| offflag() */, NULL, sizeof(ea_t));
    if ( 0 != res )
      msg("Cannot add member %s: %d\n", methods[i].name, res);
  }
  free_buben_methods(methods, size);
  // lets check first 3 method of added vtbl
  member_t *m;
  m = get_member(s, 0);
  if ( NULL == m ) // QueryInterface
    add_struc_member(s, "QueryInterface", 0, dwrdflag(), NULL, sizeof(ea_t));
  m = get_member(s, sizeof(ea_t));
  if ( NULL == m )
    add_struc_member(s, "AddRef", sizeof(ea_t), dwrdflag(), NULL, sizeof(ea_t));
  m = get_member(s, 2 * sizeof(ea_t));
  if ( NULL == m )
    add_struc_member(s, "Release", 2 * sizeof(ea_t), dwrdflag(), NULL, sizeof(ea_t));
}