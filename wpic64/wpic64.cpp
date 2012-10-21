#include "wpic64.hpp"
#include "rp.hpp"
#include "x86.hpp"

#include <name.hpp>
#include <funcs.hpp>
#include <ua.hpp>
#include <xref.hpp>
#include <search.hpp>
#include <segment.hpp>
// now included in intel.hpp
// #include <allins.hpp>
#include <intel.hpp>

#include <list>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// #define WPIC64_SHOW

const char *g_log_filename = "c:\\work\\wpic64.log";
FILE *rp_log_fp = NULL;
// some stat
int g_found = 0;
int g_reffed = 0;

#ifdef WPIC64_SHOW
void
report_instr(ea_t adr)
{
  flags_t flag = getFlags(adr);
  RP_TRACE2("%I64X (%X)\n", adr, flag);
  RP_TRACE4("itype %d size %d auxpref.lo 0x%X auxpref.hi 0x%X\n", cmd.itype, cmd.size,
    cmd.auxpref_chars.low, cmd.auxpref_chars.high );

  if ( cmd.Op1.type ) RP_TRACE1("Opnd1.type %d\n", cmd.Op1.type );
  if ( cmd.Op1.dtyp ) RP_TRACE1("Opnd1.dtyp %d\n", cmd.Op1.dtyp );
  if ( exists_reg(&cmd.Op1) )
	RP_TRACE1("Opnd1.reg %d\n", cmd.Op1.reg );
  if ( exists_phrase(&cmd.Op1) )
	RP_TRACE1("Opnd1.phrase %d\n", cmd.Op1.phrase );
  if ( exists_value(&cmd.Op1) )
	RP_TRACE1("Opnd1.value 0x%X\n", cmd.Op1.value );
  if ( exists_addr(&cmd.Op1) )
	RP_TRACE1("Opnd1.addr 0x%I64X\n", cmd.Op1.addr );
  RP_TRACE2("Opnd1.specval: low %d hi %d\n", cmd.Op1.specval_shorts.low, cmd.Op1.specval_shorts.high );
  if ( cmd.Op1.specflag1 || cmd.Op1.specflag2 ) 
  {
     RP_TRACE1("Opnd1.specflag1 %d\n", cmd.Op1.specflag1 );
     RP_TRACE1("Opnd1.specflag2 %d\n", cmd.Op1.specflag2 );
  }

  if ( cmd.Op2.type ) RP_TRACE1("Opnd2.type %d\n", cmd.Op2.type );
  if ( cmd.Op2.dtyp ) RP_TRACE1("Opnd2.dtyp %d\n", cmd.Op2.dtyp );
  if ( exists_reg(&cmd.Op2) )
	RP_TRACE1("Opnd2.reg %d\n", cmd.Op2.reg );
  if ( exists_phrase(&cmd.Op2) )
	RP_TRACE1("Opnd2.phrase %d\n", cmd.Op2.phrase );
  if ( exists_value(&cmd.Op2) )
	RP_TRACE1("Opnd2.value 0x%X\n", cmd.Op2.value );
  if ( exists_addr(&cmd.Op2) )
	RP_TRACE1("Opnd2.addr 0x%X\n", cmd.Op2.addr );
  RP_TRACE2("Opnd2.specval: low %d hi %d\n", cmd.Op2.specval_shorts.low, cmd.Op2.specval_shorts.high );
  if ( cmd.Op2.specflag1 )
  {
     RP_TRACE1("Opnd2.specflag1 %d\n", cmd.Op2.specflag1 );
     RP_TRACE1("Opnd2.specflag2 %d\n", cmd.Op2.specflag2 );
   }

   if ( cmd.Op3.type ) RP_TRACE1("Opnd3.type %d\n", cmd.Op3.type );
   if ( cmd.Op3.dtyp ) RP_TRACE1("Opnd3.dtyp %d\n", cmd.Op3.dtyp );
   if ( exists_reg(&cmd.Op3) )
	RP_TRACE1("Opnd3.reg %d\n", cmd.Op3.reg );
   if ( exists_phrase(&cmd.Op3) )
	RP_TRACE1("Opnd3.phrase %d\n", cmd.Op3.phrase );
   if ( exists_value(&cmd.Op3) )
	RP_TRACE1("Opnd3.value 0x%X\n", cmd.Op3.value );
   if ( exists_addr(&cmd.Op3) )
	RP_TRACE1("Opnd3.addr 0x%X\n", cmd.Op3.addr );
   RP_TRACE2("Opnd3.specval: low %d hi %d\n", cmd.Op3.specval_shorts.low, cmd.Op3.specval_shorts.high );
   if ( cmd.Op3.specflag1 )
   {
     RP_TRACE1("Opnd3.specflag1 %d\n", cmd.Op3.specflag1 );
     RP_TRACE1("Opnd3.specflag2 %d\n", cmd.Op3.specflag2 );
   }
}
#endif // WPIC64_SHOW

ea_t
get_next_code(ea_t start)
{
  segment_t *cs = getseg(start);
  if ( NULL == cs )
   return NULL;

  for ( start = get_item_end(start); start < cs->endEA; start = get_item_end(start) )
   if ( isCode(getFlags(start)) )
    return start;
  return cs->endEA;
}

int cmp_base_and_zero_index(const op_t &op, uint16 base_reg)
{
  if ( x86_base(op) == base_reg )
    return 1;
  if ( op.hasSIB && !sib_scale(op) && sib_index(op) == base_reg )
    return 1;
  return 0;
}

int is_our_base_reg(uint16 base_reg, uval_t &value, char &dtyp)
{
  if ( exists_phrase(&cmd.Op1) && exists_addr(&cmd.Op1) && cmp_base_and_zero_index(cmd.Op1, base_reg) )
  {
    value = cmd.Op1.addr;
    dtyp  = cmd.Op1.dtyp;
    return 1;
  }
  if ( exists_phrase(&cmd.Op2) && exists_addr(&cmd.Op2) && cmp_base_and_zero_index(cmd.Op2, base_reg) )
  {
    value = cmd.Op2.addr;
    dtyp  = cmd.Op2.dtyp;
    return 1;
  }
  return 0;
}

bool
is_change_base_reg(const insn_t *instr, uint16 base_reg)
{
  const struct RP_opcode *rp = get_opcode(instr);
  if ( NULL == rp )
   return false;
  return is_change_reg(instr, rp, base_reg);
}

int is_end_cf()
{
  return (cmd.itype == NN_jmp) ||
         (cmd.itype == NN_jmpfi) ||
	 (cmd.itype == NN_jmpni) ||
	 (cmd.itype == NN_jmpshort) ||
	 (cmd.itype == NN_int) ||
	 (cmd.itype == NN_int3) ||
	 (cmd.itype == NN_iretw) ||
	 (cmd.itype == NN_iret) ||
	 (cmd.itype == NN_iretd) ||
	 (cmd.itype == NN_iretq)
  ;
}

void analyze_wpic(ea_t &curr_addr, ea_t seg_end, ea_t base)
{
  uval_t val;
  char dtyp;
  uint16 base_reg = cmd.Op1.reg;
  curr_addr = get_item_end(curr_addr);
  while(curr_addr < seg_end)
  {
    int len = decode_insn(curr_addr);
    if ( !len )
      break;
    // is this instruction destroy content of base reg ?
    if ( is_change_base_reg(&cmd, base_reg) )
      break;
    // check for jmp/retn/int3
    if ( is_end_cf() )
      break;
#ifdef WPIC64_SHOW
    report_instr(curr_addr);
#endif /* WPIC64_SHOW */
    // check for base reg and offset
    if ( is_our_base_reg(base_reg, val, dtyp) )
    {
      ea_t ref_addr = base + val;
      pic_add_dref(curr_addr, ref_addr, dr_O, dtyp, true);
      g_reffed++;
    }
    curr_addr += len;
  }
}

void process_all(std::list<segment_t *> *list, ea_t base)
{
  char pattern[256];
  // check if base already have some name
  if ( NULL == get_name(BADADDR, base, pattern, sizeof(pattern)) )
    qsnprintf(pattern, sizeof(pattern), "%I64xh", base);
  std::list<segment_t *>::const_iterator citer;
  for ( citer = list->begin(); citer != list->end(); ++citer )
  {
    ea_t curr_addr = find_text((*citer)->startEA, 0, 0, pattern, SEARCH_DOWN);
    for ( ; curr_addr != BADADDR; curr_addr = find_text(get_next_code(curr_addr), 0, 0, pattern, SEARCH_DOWN | SEARCH_NEXT) )
    {
      g_found++;
      if ( curr_addr > (*citer)->endEA )
        break;
      flags_t flag = getFlags(curr_addr);
      if ( !isCode(flag) )
        continue;
      if ( !decode_insn(curr_addr) )
        continue;
#ifdef WPIC64_SHOW
      report_instr(curr_addr);
#endif /* WPIC64_SHOW */
      // check if this is real lea
      if ( (cmd.itype != NN_lea)   ||
           (cmd.Op1.type != o_reg) ||
           (cmd.Op2.type != o_mem)
         )
        continue;
      // yep, we have some lea instr, run analyzer
      analyze_wpic(curr_addr, (*citer)->endEA, base);
    }
  }
}

int idaapi
WPIC64_init(void)
{
 // we must be inside PE
 if ( inf.filetype != f_PE )
   return PLUGIN_SKIP;
 // and with x386 processor
 if ( ph.id != PLFM_386 )
   return PLUGIN_SKIP;
 return PLUGIN_OK;
}

void idaapi
WPIC64_term(void)
{
  if ( NULL != rp_log_fp )
  {
    fclose(rp_log_fp);
    rp_log_fp = NULL;
  }
}

void idaapi
WPIC64_run(int arg)
{
  // dirty hack to get ImageBase of loaded PE module
  netnode penode("$ PE header");
  IMAGE_NT_HEADERS64 hdr64;
  ssize_t res = penode.valobj(&hdr64, sizeof(hdr64));
  ea_t base;
  if ( res > 0 )
  {
#ifdef _DEBUG
    msg("Base: %I64X\n", hdr64.OptionalHeader.ImageBase);
#endif
    base = hdr64.OptionalHeader.ImageBase;
  } else
    return;
  // collect all executable section
  int segs_cnt = get_segm_qty();
  std::list<segment_t *> exec_segs;
  for ( int i = 0; i < segs_cnt; i++ )
  {
    segment_t *current = getnseg(i);
    if ( ! (current->perm & SEGPERM_EXEC) )
      continue;
    // skip HEADER "section"
    if ( current->startEA == base )
      continue;
    try
    {
      exec_segs.push_back(current);
    } catch(std::bad_alloc)
    { }
  }
  if ( !exec_segs.size() )
  {
    msg("No executable segments found\n");
    return;
  }
#ifdef WPIC64_SHOW
  rp_log_fp = fopen(g_log_filename, "w+t");
#endif /* WPIC64_SHOW */
  // zero stat
  g_reffed = 0;
  g_found = 0;
  // fire !
  process_all(&exec_segs, base);
  // dump stat
  msg("Found %d, reffed %d\n", g_found, g_reffed);
}

char WPIC64_comment[] = "Code analyzer plugin for AMD64 code for windows";
char WPIC64_help[] =
 "WPIC64 code analyzer plugin\n"
  "\n"
  "This plugin analyses position independent code for AMD64 processors family on windows";
char WPIC64_wanted_name[] = "WPIC64 analyzer plugin";
char WPIC64_wanted_hotkey[] = "Alt-W";

/*
 * PLUGIN description
 */
extern "C" plugin_t PLUGIN = {
  IDP_INTERFACE_VERSION,
  0,                    // plugin flags - ???
  WPIC64_init,             // initialize function
  WPIC64_term,             // terminate. this pointer may be NULL.
  WPIC64_run,              // invoke plugin
  WPIC64_comment,          // long comment about the plugin
  WPIC64_help,             // multiline help about the plugin
  WPIC64_wanted_name,      // the preferred short name of the plugin
  WPIC64_wanted_hotkey     // the preferred hotkey to run the plugin
};
