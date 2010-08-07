#include "regs.hpp"
#include "../pic/x86.hpp"
#include "../pic/rp.hpp"
#include <bytes.hpp>
#include <ua.hpp>

#ifdef RP_DEBUG
# include "pic.hpp"
#endif

/* for debugging */
#include "rp_debug.h"

int my_vm::get_hreg(int hr)
{
  switch(hr)
  {
    case r_AL:
    case r_AH: return r_EAX;
    case r_CL:
    case r_CH: return r_ECX;
    case r_DL:
    case r_DH: return r_EDX;
    case r_BL:
    case r_BH: return r_EBX;
  }
  return -1;
}

void my_vm::reset_regs()
{
  actual = 0;
  for ( int i = 0; i < 8; i++ )
   regs[i].reset();
}

void my_vm::reset_reg(int r)
{
  if ( r > 7 )
   return;
  if ( regs[r].is_s )
  {
   actual--;
   regs[r].reset();
  }
}

void my_vm::set_reg(int r, tid_t tid)
{
  if ( r > 7 )
   return;
  if ( !regs[r].is_s )
   actual++;
  regs[r].set_s(tid);
}

void my_vm::xfer_reg(int from, int to)
{
  if ( regs[to].is_s )
   reset_reg(to);
  if ( !regs[from].is_s )
   return;
  set_reg(to, regs[from].tid);
  regs[to].offset = regs[from].offset;
}

static int
is_end_instr(int code)
{
  switch(code)
  {
    case Ix86_call:
    case Ix86_callfi:
    case Ix86_callni:
    case Ix86_jmp:
    case Ix86_jmpfi:
    case Ix86_jmpni:
    case Ix86_jmpshort: 
    case Ix86_ret:
    case Ix86_retf:
     return 1;
  }
  return 0;
}

/* Something similar to VM
 * Returns: size of analyzed instruction
 * Logic: unpredictable :-)
 */
int my_vm::analize_instr(ea_t addr)
{
  int size = ua_ana0(addr);
  if ( size < 1 )
   return size;
#ifdef RP_DEBUG
 msg("analize: %X, size %d\n", addr, size);
// report_instr(addr);
#endif
  /* check for mov reg, ds:[offset to struct] instr */
  if ( cmd.itype == Ix86_mov &&
       cmd.Op1.type == o_reg &&
       cmd.Op2.type == o_mem &&
       cmd.Op1.reg < 7 &&
       cmd.Op1.dtyp == dt_dword && cmd.Op2.dtyp == dt_dword )
  {
    ea_t addr = cmd.Op2.addr;
    dnode_t *node = map->is_presented(addr);
    if ( node != NULL )
    {
#ifdef RP_DEBUG
 msg("Track reg %d\n", cmd.Op1.reg);
#endif
      set_reg(cmd.Op1.reg, (tid_t)dnode_get(node));
      return size;
    }
    reset_reg(cmd.Op1.reg);
    return size;
  }
  /* check for interregister moving */
  if ( cmd.itype == Ix86_mov &&
       cmd.Op1.type == o_reg &&
       cmd.Op2.type == o_reg &&
       cmd.Op1.reg < 7 && cmd.Op2.reg < 7 &&
       cmd.Op1.dtyp == dt_dword && cmd.Op2.dtyp == dt_dword )
  {
#ifdef RP_DEBUG
 msg("transfer from %d -> %d\n", cmd.Op2.reg, cmd.Op1.reg);
#endif
    xfer_reg(cmd.Op2.reg, cmd.Op1.reg);
    return size;
  }
  /* check for (sadly) base reg modification (in present time I can track only
   * one instruction: add reg, const (const < struct_size !)
   */
  if ( cmd.itype == Ix86_add &&
       cmd.Op1.type == o_reg &&
       cmd.Op2.type == o_imm &&
       cmd.Op1.reg < 7 )
  {
#ifdef RP_DEBUG
 msg("Add to reg\n");
#endif
    if ( regs[cmd.Op1.reg].is_s )
    {
#ifdef RP_DEBUG
 msg("Offset is %d\n", cmd.Op2.value);
#endif
      regs[cmd.Op1.reg].offset += cmd.Op2.value;
      return size;
    }
    return size;
  }
  /* check for something usefull :-) We have two cases: 
   * 1) mov something, [reg+off]
   * 2) mov[reg+off], something
   */
  if ( cmd.Op1.type == o_displ &&
       exists_addr(&cmd.Op1)   &&
       !exists_value(&cmd.Op1) &&
       cmd.Op1.phrase < 7      &&
       regs[cmd.Op1.phrase].is_s )
  {
    tid_t tid = regs[cmd.Op1.phrase].tid;
//    rp_set_comment(addr, get_struc_name(tid), true);
    struc_t *s = get_struc(tid);
    op_stroff(addr, 0, &s->id, 2, regs[cmd.Op1.phrase].offset);
  }
  /* second case */
  if ( cmd.Op2.type == o_displ &&
       exists_addr(&cmd.Op2)   &&
       !exists_value(&cmd.Op2) &&
       cmd.Op2.phrase < 7      &&
       regs[cmd.Op2.phrase].is_s )
  {
    tid_t tid = regs[cmd.Op2.phrase].tid;
//    rp_set_comment(addr, get_struc_name(tid), true);
    struc_t *s = get_struc(tid);
    op_stroff(addr, 1, &s->id, 2, regs[cmd.Op2.phrase].offset);
  }
  /* also we consider all calls as killed all registers */
  if ( is_end_instr(cmd.itype) )
  {
    reset_regs();
    return size;
  }
  /* O`k, next we need to check if our reg is trashed */  
  const struct RP_opcode *rp_op = get_opcode(&cmd);
  if ( NULL != rp_op )
  {
    for ( int i = 0; i < 7; i++ )
     if ( is_change_reg(&cmd, rp_op, i) )
      reset_reg(i);
  }
  return size;
}