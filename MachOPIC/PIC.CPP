#include <ida.hpp>
#include <idp.hpp>
#include <loader.hpp>
#include <kernwin.hpp>
#include <bytes.hpp>

#include <stdio.h>

#include "ppc_e.h"

char PIC_comment[] = "Code analyzer plugin for MachO position independent code";
char PIC_help[] =
 "MachO PIC code analyzer plugin\n"
  "\n"
  "This plugin analyses position independent code from MachO binaries for PowerPC processors family";
char PIC_wanted_hotkey[] = "Ctrl-Alt-M";
char PIC_wanted_name[] = "MachO PIC analyzer plugin";

// #define RP_DEBUG

FILE *m_log = NULL;
int m_was_open = 0;

#ifdef RP_DEBUG
void check_log()
{
  if ( m_was_open || m_log != NULL )
   return;
  m_was_open++;
  m_log = fopen("machopic.log", "w");
}

const char *op_type(optype_t t)
{
  switch(t)
  {
    case o_void: return "void";
    case o_reg:  return "reg";
    case o_mem:  return "mem";
    case o_phrase: return "phrase";
    case o_displ:  return "displ";
    case o_imm:  return "imm";
    case o_far:  return "far";
    case o_near: return "near";
    case o_idpspec0: return "spec0";
    case o_idpspec1: return "spec1";
    case o_idpspec2: return "spec2";
    case o_idpspec3: return "spec3";
    case o_idpspec4: return "spec4";
    case o_idpspec5: return "spec5";
  }
  return "hz";
}

const char *d_type(char d)
{
  switch(d)
  {
    case 0: return "byte";
    case 1: return "word";
    case 2: return "dword";
    case 3: return "float";
    case 4: return "double";
    case 5: return "tbyte";
    case 6: return "packreal";
    case 7: return "qword";
    case 8: return "byte16";
    case 9: return "code";
    case 10: return "void";
    case 11: return "fword";
    case 12: return "bitfild";
    case 13: return "string";
    case 14: return "unicode";
    case 15: return "3byte";
  }
  return "hz";
}

void dump_op(int num, op_t &Op)
{
    fprintf(m_log,"Opnd%d.type %d (%s)\n", num, Op.type, op_type(Op.type) );
    fprintf(m_log,"Opnd%d.dtyp %d (%s)\n", num, Op.dtyp, d_type(Op.dtyp) );
    if ( exists_reg(&Op) )
	fprintf(m_log,"Opnd%d.reg %d (%s)\n", num, Op.reg, ppc_lemul::reg_name(Op.reg) );
    if ( exists_phrase(&Op) )
	fprintf(m_log,"Opnd%d.phrase %d\n", num, Op.phrase );
    if ( exists_value(&Op) )
	fprintf(m_log,"Opnd%d.value 0x%X\n", num, Op.value );
    if ( exists_addr(&Op) )
	fprintf(m_log,"Opnd%d.addr 0x%X\n", num, Op.addr );
    fprintf(m_log,"Opnd%d.specval: low %d hi %d\n", num, Op.specval_shorts.low, Op.specval_shorts.high );
    if ( Op.specflag1 || Op.specflag2 ) 
    {
      fprintf(m_log,"Opnd%d.specflag1 %d\n", num, Op.specflag1 );
      fprintf(m_log,"Opnd%d.specflag2 %d\n", num, Op.specflag2 );
    }
}

void
report_instr(ea_t adr)
{
  check_log();
  if ( m_log == NULL )
   return;
  const char *i_name = ph.instruc[cmd.itype].name;
  flags_t flag = getFlags(adr);
  fprintf(m_log, "%X (%X)\n", adr, flag);
  fprintf(m_log, "itype %d (%s) size %d auxpref.lo 0x%X auxpref.hi 0x%X\n", 
    cmd.itype, i_name, cmd.size,
    cmd.auxpref_chars.low, cmd.auxpref_chars.high );

  // dump 1st op
  if ( cmd.Op1.type ) 
  {
    dump_op(1, cmd.Op1);
  }
  // dump 2nd op
  if ( cmd.Op2.type ) 
  {
    dump_op(2, cmd.Op2);
  }
  // dump 3rd op
  if ( cmd.Op3.type ) 
  {
    dump_op(3, cmd.Op3);
  }
}
#endif

void process_PIC(smac_reffer *ref, ea_t from, ea_t to)
{
  int size;
  flags_t flag;
  ppc_lemul em(ref);
  int res;

  for ( ea_t a = from; a < to; )
  {
     flag = getFlags(a);
     if ( !isCode(flag) )
     {
       a++;
       continue;
     }
     size = ua_ana0(a);
     if ( !size )
     {
       warning("Bad instruction at %X", a);
       a++;
       continue;
     }
     // dump
#ifdef RP_DEBUG
     report_instr(a);
#endif
     // main processing
     res = em.emul(a);
#ifdef RP_DEBUG
     if ( m_log != NULL && 2 == res )
      fprintf(m_log, "Gotcha %X !\n", em.base_addr());
#endif
     // final
     a += size;
  }
#ifdef RP_DEBUG
  if ( m_log != NULL )
    fflush(m_log);
#endif
}

void idaapi
PIC_run(int arg)
{
  ea_t curr_addr = get_screen_ea();
  int n_funcz, i;
  func_t *curr_func;
  smac_reffer sr;

  switch(arg)
  {
    case 0:
     curr_func = get_func(curr_addr);
     if ( NULL == curr_func )
     {
       warning("Cannot operate on non-function address %X\n", curr_addr);
       return;
     }
     process_PIC(&sr, curr_func->startEA, curr_func->endEA);
     break;
    case 1:
     n_funcz = get_func_qty();
     if ( !n_funcz )
     {
       warning("No functions defined!");
       return;
     }
     for ( i = 0; i < n_funcz; i++ )
     {
       curr_func = getn_func(i);
       if ( NULL == curr_func )
       {
#ifdef RP_DEBUG
         check_log();
         if ( m_log != NULL )
          fprintf(m_log, "machoPIC: cannot get func N %d\n", i);
#endif
         continue;
       }
       process_PIC(&sr, curr_func->startEA, curr_func->endEA);
     }
     break;
    default:
      warning("Illegal parameter %d for %s\n"
"Allowed parameters:\n"
" 0 - analyze current function\n"
" 1 - analyze all functions\n",
 arg, PIC_wanted_name);
  }
}

void idaapi
PIC_term(void)
{
  if ( m_log != NULL )
  {
    fclose(m_log);
    m_log = NULL;
  }
}

int idaapi 
PIC_init()
{
//  msg("PIC: filetype %d\n", inf.filetype ); // - 17 .eq. f_LOADER
  if ( ph.id != PLFM_PPC )
   return PLUGIN_SKIP;
  return PLUGIN_OK;
}

/*
 * PLUGIN description
 */
extern "C" plugin_t PLUGIN = {
  IDP_INTERFACE_VERSION,
  0,                    // plugin flags - ???
  PIC_init,             // initialize function
  PIC_term,             // terminate. this pointer may be NULL.
  PIC_run,              // invoke plugin
  PIC_comment,          // long comment about the plugin
  PIC_help,             // multiline help about the plugin
  PIC_wanted_name,      // the preferred short name of the plugin
  PIC_wanted_hotkey     // the preferred hotkey to run the plugin
};
