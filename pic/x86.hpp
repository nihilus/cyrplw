#ifndef RP_X86_HPP
#define RP_X86_HPP	"Written by Red Plait, 19-II-2000"

#include <ida.hpp>
#include <ua.hpp>
#include "x86.h"

const RP_opcode * idaapi get_opcode(const insn_t *instr);
bool idaapi is_change_reg(const insn_t *instr, const RP_opcode *opcode, int reg);
bool idaapi is_deal_with_reg(op_t *op, int check_reg);


/* some useful macros */
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

/* for SIB spliting */
inline int idaapi
get_SIB_base(char c)
{
  return (unsigned int)c & 7;
}

inline int idaapi
get_SIB_reg(char c)
{
  return ((unsigned int)c >> 3) & 7;
}

inline int idaapi
get_SIB_SS(char c)
{
  return ((unsigned int)c & 0xC0) >> 6;
}

dref_t idaapi get_dreftype_op1(const insn_t *);
dref_t idaapi get_dreftype_op2(const insn_t *);

void idaapi pic_add_dref(ea_t, ea_t, dref_t, char);
bool idaapi is_change_stack(const insn_t *);

#endif /* RP_X86_HPP */