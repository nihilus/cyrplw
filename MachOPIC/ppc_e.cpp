#include "ppc_e.h"
#include <allins.hpp>

const char *ppc_lemul::reg_name(int r)
{
  if ( r >= ph.regsNum )
   return "hz";
  return ph.regNames[r];
}

ppc_lemul::ppc_lemul(smac_reffer *ref)
{
  m_reffer = ref;
  reset();
}

void ppc_lemul::reset()
{
  m_basereg = 0;
  m_status = 0;
  memset(m_regs, 0, sizeof(m_regs));
}

int ppc_lemul::is_pic_b(ea_t ea)
{
  if ( cmd.itype != PPC_b )
   return 0;
  if ( !exists_addr(&cmd.Op1) )
   return 0;
  if ( cmd.Op1.addr != ea + cmd.size )
   return 0;
  return 1;
}

int ppc_lemul::is_mflr()
{
  if ( cmd.itype != PPC_mflr )
   return 0;
  if ( cmd.Op2.type != 8 )
   return 0;
  if ( cmd.Op1.type != o_reg )
   return 0;
  m_basereg = cmd.Op1.reg;
  m_regs[m_basereg].value = m_base;
  m_regs[m_basereg].is_const = 1;
  return 1;
}

void ppc_lemul::do_lis()
{
  int reg = cmd.Op1.reg;
  if ( reg == m_basereg )
  {
    reset();
    return;
  }
  unsigned long value = (cmd.Op2.value << 16) & 0xffff0000;
  if ( m_regs[reg].is_const )
   m_regs[reg].value = value;
  else {
   m_regs[reg].is_const = 1;
   m_regs[reg].value = value;
  }
}

void ppc_lemul::do_ori()
{
  int reg1 = cmd.Op1.reg;
  if ( reg1 == m_basereg )
  {
    reset();
    return;
  }
  int reg2 = cmd.Op2.reg;
  if ( reg1 == reg2 )
  {
    if ( m_regs[reg1].is_const )
     m_regs[reg1].value |= cmd.Op3.value;
    return;
  }
  m_regs[reg1].is_const = 0;
}

void ppc_lemul::do_cmt(ea_t a, int reg, ea_t value)
{
  ea_t real_value = value;
  if ( m_reffer != NULL )
   real_value = m_reffer->add(a, value);
  qsnprintf(m_cmt, sizeof(m_cmt), "%s %X", reg_name(reg), real_value);
  set_cmt(a, m_cmt, false);
}

void ppc_lemul::do_add(ea_t a)
{
  int reg_D = cmd.Op1.reg;
  int reg_A = cmd.Op2.reg;
  int reg_B = cmd.Op3.reg;
  // check what we add
  if ( reg_A == m_basereg || reg_B == m_basereg )
  {
    if ( m_regs[reg_A].is_const &&
         m_regs[reg_B].is_const )
    {
      m_regs[reg_D].is_const = 1;
      m_regs[reg_D].value = m_regs[reg_A].value + m_regs[reg_B].value;
      do_cmt(a, reg_D, m_regs[reg_D].value);
      return;
    } else {
      reset();
      return;
    }
  }
  // finally check what reg changed
  if ( reg_D == m_basereg )
   reset();
}

int ppc_lemul::emul(ea_t a)
{
  if ( !m_status )
  {
    if ( is_pic_b(a) )
    {
      m_status = 1;
      m_base = cmd.Op1.addr;
    }
    return m_status;
  }
  if ( m_status == 1 )
  {
    if ( is_mflr() )
    {
      m_status = 2;
    } else {
      reset();
    }
    return m_status;
  }
  // main processing - after b $+4, mflr
  if ( m_status == 2 )
  {
    switch(cmd.itype)
    {
      case PPC_add:
        do_add(a);
       break;
      case PPC_lis:
        do_lis();
       break;
      case PPC_mtlr:
       break;
      case PPC_ori:
        do_ori();
       break;

 //     default:
 //      reset();
    }
  }
  return m_status;
}