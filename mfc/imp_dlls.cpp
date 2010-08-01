#include "imp_dlls.h"
#include <segment.hpp>
#include <kernwin.hpp>

char * idaapi read_zero_ended_string(ea_t ea);

static void free_imp(dnode_t *node, void *)
{
  char *key = (char *)dnode_getkey(node);
  if ( key )
   qfree(key);
  free(node);
}

int imp_cmp(const void *a, const void *b)
{
  return stricmp((const char *)a, (const char *)b);
}

Imp_Dlls::Imp_Dlls()
{
  m_dict = dict_create(DICTCOUNT_T_MAX, imp_cmp);
  dict_set_allocator(m_dict, NULL, free_imp, NULL);
  // get import
  netnode penode("$ PE header");
  char nth[256];
  penode.valobj(&nth, sizeof(nth));
  m_imp = get_imp_va(&nth);
  loaded_base = penode.altval(-2);
  m_imp += loaded_base;
}

Imp_Dlls::~Imp_Dlls()
{
  if ( m_dict )
  {
    dict_free(m_dict);
    dict_destroy(m_dict);
    m_dict = NULL;
  }
}

dnode_t *Imp_Dlls::get(dnode_t *prev)
{
  if ( prev == NULL )
   return dict_first(m_dict);
  return dict_next(m_dict, prev);
}

int Imp_Dlls::add_import(ea_t addr)
{
  char *s = read_zero_ended_string(addr);
  if ( !s )
   return -1;
  dnode_t *node = dict_lookup(m_dict, s);
  if ( node )
  {
   qfree(s);
   return 1;
  }
  dict_alloc_insert(m_dict, (const void *)s, NULL);
  return 0;
}

// standart pe import directory entry
typedef struct sIMPORT_DIRECTORY_ENTRY {
  unsigned int  ImportLookUp;      // +00h       // offset of lookup table.
  unsigned int  TimeDateStamp;     // +04h       // junk, usually 0.
  unsigned int  ForwardChain;      // +08h       // junk, usually -1.
  unsigned int  NameRVA;           // +0Ch       // rva of dll name.
  unsigned int  AddressTableRVA;   // +10h       // rva of import address table.
} tMPORT_DIRECTORY_ENTRY, *pIMPORT_DIRECTORY_ENTRY;

int Imp_Dlls::get_dlls(void)
{
  tMPORT_DIRECTORY_ENTRY ImpDir;
  ea_t dir_va;

  if ( 0 == (dir_va = m_imp) )
    return(-1); // no import

  segment_t *seg = getseg(m_imp);
  if ( !seg )
  {
    warning("Bad import structure");
    return -2;
  }
  while(dir_va < seg->endEA)
  {
    ImpDir.ImportLookUp     = get_long(dir_va+0x00);
    ImpDir.TimeDateStamp    = get_long(dir_va+0x04);
    ImpDir.ForwardChain     = get_long(dir_va+0x08);
    ImpDir.NameRVA          = get_long(dir_va+0x0C);
    ImpDir.AddressTableRVA  = get_long(dir_va+0x10);

    if ( 0 == ImpDir.NameRVA )
      break; // all done

    add_import(ImpDir.NameRVA + loaded_base);
    dir_va += 0x14; // next dir
  }

  return(0); // all ok
}
