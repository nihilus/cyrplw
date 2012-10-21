#ifndef PPC_E_H
# define PPC_E_H	"Lame PowerPC emulator for PIC addresses resolving"

#include <ida.hpp>
#include <idp.hpp>
#include <loader.hpp>
#include <kernwin.hpp>
#include <bytes.hpp>

#include "smac.h"

inline bool idaapi
exists_reg(op_t *op)
{
  return (op->type == o_reg);
}

inline bool idaapi
exists_phrase(op_t *op)
{
  return (op->type == o_phrase || op->type == o_displ );
}

inline bool idaapi
exists_value(op_t *op)
{
  return (op->type == o_imm ||
   ((op->type == o_displ) && (op->flags & OF_OUTER_DISP))
  );
}

inline bool idaapi
exists_addr(op_t *op)
{
  return (op->type == o_mem || op->type == o_far || op->type == o_near ||
  ((op->type == o_displ) && !(op->flags & OF_NO_BASE_DISP))
  );
}

struct ppc_greg
{
  unsigned long value;
  char is_const;
};

class ppc_lemul
{
  public:
   ppc_lemul(smac_reffer *);
   void reset();
   int emul(ea_t);
   inline int status()	{ return m_status; }
   inline ea_t base_addr()
   {
     if ( !m_status )
      return BADADDR;
     return m_base;
   }
   inline int basreg()
   {
     if ( !m_status )
      return 0;
     return m_basereg;
   }

   static const char *reg_name(int r);
  protected:
   smac_reffer *m_reffer;

   char m_cmt[80];
   struct ppc_greg m_regs[32];
   int m_status;
   ea_t m_base;
   int m_basereg;

   void do_cmt(ea_t, int reg, ea_t value);
   int is_pic_b(ea_t);
   int is_mflr();
   void do_lis();
   void do_ori();
   void do_add(ea_t);
};
#endif /* PPC_E_H */