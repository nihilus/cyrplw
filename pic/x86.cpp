#include "x86.hpp"

const int max_RP_data = 593; /* it`s may be changed in next versions of IDA */

const struct RP_opcode opcode_axdiv = {
	0,
	0,
	(1 << r_EAX),
	0,
	0,
	f_AF | f_CF | f_OF | f_PF | f_SF | f_ZF,
	0
};

const struct RP_opcode opcode_axmul = {
	0,
	0,
	(1 << r_EAX),
	f_CF | f_OF,
	0,
	f_AF | f_PF | f_SF | f_ZF,
	0	
};
 
const struct RP_opcode opcode_aximul1 = {
	0,
	0,
	(1 << r_EAX),
	f_CF | f_OF,
	0,
	f_AF | f_PF | f_SF | f_ZF,
	0
};

const struct RP_opcode opcode_aximul2 = {
	0,
	0,
	(1 << r_EAX) | (1 << r_EDX),
	f_CF | f_OF,
	0,
	f_AF | f_PF | f_SF | f_ZF,
	0
};

const RP_opcode * idaapi
get_opcode(const insn_t *instr)
{
  if ( NULL == instr )
    return NULL;
  if ( instr->itype > max_RP_data )
  {
    msg("Too big instruction itype %d vs max %d\n", instr->itype, max_RP_data );
    return NULL;
  }
  /***** check for some exceptions ******/
  /* First case: (i)div r/m8 - changed only EAX register */
  if ( (instr->itype == Ix86_div ||
        instr->itype == Ix86_idiv) &&
       instr->Op1.dtyp == dt_byte )
   return &opcode_axdiv;
  /* Second case: mul operand */
  if ( instr->itype == Ix86_mul && instr->Op1.dtyp == dt_byte )
   return &opcode_axmul;
  /* Third case: imul operand */
  if ( instr->itype == Ix86_imul &&
       instr->Op1.type == o_reg  &&
       instr->Op1.type <= r_AH   &&
       r_EAX == (instr->Op1.reg & 0x7) )
  {
   if ( instr->Op1.dtyp == dt_byte )
    return &opcode_aximul1;
   else
    return &opcode_aximul2;
  }
  return RP_data[instr->itype-1];
}

bool idaapi
is_change_reg(const insn_t *instr, const RP_opcode *opcode, int reg)
{
  if ( NULL == instr || NULL == opcode )
   return false;
  /* reduce reg */
  if ( (reg >= r_AL) && (reg <= r_BH) )
   reg = reg & 0x7;
  if ( opcode->regs & (1<<reg) )
   return true;
  /* check operands */
  if ( (1 & opcode->ops) && 
       instr->Op1.type == o_reg &&
       instr->Op1.reg == reg )
   return true;
  if ( (2 & opcode->ops) &&
       instr->Op2.type == o_reg &&
       instr->Op2.reg == reg )
   return true;
  if ( (4 & opcode->ops) &&
       instr->Op3.type == o_reg &&
       instr->Op3.reg == reg )
   return true;
  return false;
}

bool idaapi
is_deal_with_reg(op_t *op, int check_reg)
{
  if ( exists_reg(op) && op->reg == check_reg )
   return true;
  if ( exists_phrase(op) && op->phrase == check_reg )
   return true;
  if ( op->specflag1 == 1 )
  {
    if ( get_SIB_base(op->specflag2) == check_reg ||
         get_SIB_reg(op->specflag2) == check_reg )
     return true;
  }
  return false;
}

dref_t idaapi
get_dreftype_op1(const insn_t *instr)
{
  const struct RP_opcode *rp = get_opcode(instr);
  if ( NULL != rp )
  {
   if ( rp->ops & 1 )
    return dr_W;
   if ( instr->itype == Ix86_push )
    return dr_O;
  }
  return dr_R;
}

dref_t idaapi
get_dreftype_op2(const insn_t *instr)
{
  if ( instr->itype == Ix86_lea )
   return dr_O;
  const struct RP_opcode *rp = get_opcode(instr);
  if ( rp != NULL && rp->ops & 0x2 )
   return dr_W;
  return dr_R;
}

bool idaapi
is_change_stack(const insn_t *instr)
{
  const struct RP_opcode *rp = get_opcode(instr);
  if ( NULL == rp )
   return false;
  return is_change_reg(instr, rp, r_ESP);
}
