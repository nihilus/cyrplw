#ifndef IMP_DLLS_H
# define IMP_DLLS_H

#include <ida.hpp>
#include <bytes.hpp>
#include "dict.h"

extern "C" unsigned long __cdecl get_imp_va(void *ptr);

class Imp_Dlls
{
  public:
   Imp_Dlls();
   ~Imp_Dlls();

   dnode_t *get(dnode_t *prev = NULL);
   int get_dlls(void);
   int add_import(ea_t);
  protected:
   ea_t loaded_base;
   ea_t m_imp;
   dict_t *m_dict;
};
#endif /* IMP_DLLS_H */