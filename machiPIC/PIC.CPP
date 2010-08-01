/* MachO i386 PICode analyzer plugin
 * Created: 29 Apr 2006 (C) RedPlait, redplait@gmail.com
 */
#include <ida.hpp>
#include <idp.hpp>
#include <loader.hpp>
#include <kernwin.hpp>
#include <bytes.hpp>
#include <allins.hpp>
#include <nalt.hpp>
#include <offset.hpp>

#include <stdio.h>

#define r_EAX	0
#define r_ECX	1
#define r_EDX	2
#define r_EBX	3
#define r_ESP	4
#define r_EBP	5
#define r_ESI	6
#define r_EDI	7

char PIC_comment[] = "Code analyzer plugin for MachO/x86 position independent code";
char PIC_help[] =
 "MachO/x86 PIC code analyzer plugin\n"
  "\n"
  "This plugin analyses position independent code from MachO binaries for x86 processors family\n"
  " v0.1 written by RedPlait, 29 Apr 2006";
char PIC_wanted_hotkey[] = "Ctrl-Alt-M";
char PIC_wanted_name[] = "MachO/x86 PIC analyzer plugin";

//#define RP_DEBUG

FILE *m_log = NULL;
int m_was_open = 0;

/* set comment - may be called several times with same comment */
void idaapi
rp_set_comment(ea_t ea, const char *comment, bool is_before, bool rptbl)
{
   if ( NULL == comment || ! *comment )
    return;
   ssize_t cmt_size;
   cmt_size = get_cmt(ea, rptbl, NULL, 0);
   if ( !cmt_size || -1 == cmt_size )
   {
      set_cmt(ea, comment, rptbl);
      return;
   }
   char *old_cmt = (char *)qalloc(cmt_size + 1);
   get_cmt(ea, rptbl, old_cmt, cmt_size);
   if ( NULL != strstr(old_cmt, comment) )
   {
     qfree(old_cmt);
     return;
   }
   if ( is_before )
   {
     int cl = strlen(comment);
     char *a = (char *)qalloc(cl + 2 + strlen(old_cmt));
     strcpy(a, comment);
     a[cl] = ',';
     strcpy(a+cl+1, old_cmt);
     set_cmt(ea, a, rptbl);
     qfree(a);
   } else
   {
     append_cmt(ea, "," , rptbl );
     append_cmt(ea, comment, rptbl );
   }
   qfree(old_cmt);
}

char *reg_name(int r)
{
  if ( r >= ph.regsNum )
   return "hz";
  return ph.regNames[r];
}

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

#ifdef RP_DEBUG
void check_log()
{
  if ( m_was_open || m_log != NULL )
   return;
  m_was_open++;
  m_log = fopen("machipic.log", "w");
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
	fprintf(m_log,"Opnd%d.reg %d (%s)\n", num, Op.reg, reg_name(Op.reg) );
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
#endif /* RP_DEBUG */

class prolog_finder
{
  public:
   prolog_finder()
   {
     m_res = BADADDR;
     m_bx_thunk = m_cx_thunk = BADADDR;
     m_reg = 0;
   }
   // methods for PIC prolog finding
   int find_prolog(ea_t start, ea_t end);
   inline ea_t res()	{ return m_res; }
   inline int reg()	{ return m_reg; }
   // analyze methods
   void analyze();
  protected:
   void pic_add_dref(ea_t from, ea_t to, dref_t dtype);
   int is_pic_thunk(ea_t addr);
   int is_stop();
   int pic_lea(ea_t a);
   // 1 May 2006 - simple switch support
   int is_cmpja(ea_t &a, int size);
   int is_addjmp(ea_t &a, int size);
   void do_simple_swtable();

   ea_t m_res;
   int m_reg;
   ea_t m_end;
   // for switch processing
   struct switch_info_t m_switch;
   ea_t m_value;
   ulong ms_size;
   // cache
   ea_t m_bx_thunk;
   ea_t m_cx_thunk;
};

static char abuf[0x10];

void prolog_finder::pic_add_dref(ea_t from, ea_t to, dref_t dtype)
{
  add_dref(from, to, dtype);
  btoa(abuf, 0x10, to, 0x10);
  rp_set_comment(from, abuf, false, false);
}

int prolog_finder::is_stop()
{
  if ((cmd.itype == NN_pop) &&
      (cmd.Op1.type == o_reg) &&
      (cmd.Op1.reg == m_reg) )
   return 1;
  return 0;
}

int prolog_finder::is_cmpja(ea_t &a, int size)
{
  if ( cmd.itype != NN_cmp )
   return 0;
  ms_size = 0;
  if ( cmd.Op2.type != o_imm )
   return 0;
  ms_size = cmd.Op2.value;
  a += size;
  size = ua_ana0(a);
  a += size;
  if ( (cmd.itype == NN_ja) && exists_addr(&cmd.Op1) )
  {
    ms_size++;
    m_switch.defjump = cmd.Op1.addr;
  }
  else
   ms_size = 0;
  return 1;
}

int prolog_finder::is_addjmp(ea_t &a, int size)
{
  if ( (cmd.itype != NN_add)   ||
       (cmd.Op1.type != o_reg) ||
       (cmd.Op2.type != o_reg) ||
       (cmd.Op2.reg != m_reg)
     )
   return 0;
  int added_reg = cmd.Op1.reg;
  int size2 = ua_ana0(a + size);
  if ( !size2 )
   return 0;
  if ( cmd.itype != NN_jmpni )
   return 0;
  if ( (cmd.Op1.type == o_reg) &&
       (cmd.Op1.reg == added_reg) )
  {
    m_switch.startea = a + size;
    a += size + size2;
    return 1;
  }
  return 0;
}

int prolog_finder::pic_lea(ea_t a)
{
  if ( cmd.itype != NN_lea )
   return 0;
  if ( exists_phrase(&cmd.Op2) &&
       (cmd.Op2.phrase == m_reg) &&
       exists_addr(&cmd.Op2)
      )
  {
    ea_t old_addr = cmd.Op2.addr;
    del_dref(a,old_addr);
    m_value = old_addr + m_res;
    pic_add_dref(a, m_value, dr_O);
    return 1;
  }
  return 0;
}

void prolog_finder::analyze()
{
  if ( BADADDR == m_res )
   return;
  flags_t flag;
  ea_t a;
  int size;
  for ( a = m_res; a < m_end; )
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
     // check for stop of analyze
     if ( is_stop() )
       return;
     // lots of checking located below
     if ( pic_lea(a) )
     {
       a += size;
       continue;
     }
     // for switch processing
     if ( is_cmpja(a, size) )
       continue;
     if ( is_addjmp(a, size) )
     {
//       msg("addjmp at %X, size %X\n", a, ms_size);
       do_simple_swtable();
       continue;
     }
     // final
     a += size;
  }
}

void prolog_finder::do_simple_swtable()
{
  if ( ! ms_size )
   return;
  flags_t flag = getFlags(m_switch.startea);
  if ( flag & FF_JUMP )
   return;
  // fill switch_info
  m_switch.flags = SWI_V32 | SWI_DEFAULT;
  m_switch.ncases = ms_size;
  m_switch.lowcase = 0;
  m_switch.jumps = m_value;
  set_switch_info(m_switch.startea, &m_switch);
  // setup switch flag
  flag |= FF_JUMP;
  setFlags(m_switch.startea, flag);
  msg("Do switch at %X tab %X size %X\n", m_switch.startea, m_value, ms_size);
  ea_t v, curr = m_value;
  do_unknown_range(curr, 4 * ms_size, true);
  int i;
  ulong ov;
  for ( i = 0; i < ms_size; i++, curr += 4 )
  {
    ov = get_long(curr);
    v = m_res + ov;
    doDwrd(curr,4);
    del_dref(curr,ov);
    // lets fix value
    put_long(curr, v);
//    pic_add_dref(curr, v, dr_O);
    op_offset(curr, 0, REF_OFF32);
    flag = getFlags(v);
    if ( !isCode(flag) )
     ua_code(v);
  }
}

int prolog_finder::find_prolog(ea_t start, ea_t end)
{
  m_res = BADADDR;
  m_end = end;
  flags_t flag;
  ea_t a;
  int size;
  ea_t supesp = BADADDR;
  // 1) - lets find instruction sub esp, const
  for ( ea_t a = start; a < m_end; )
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
     if ( (cmd.itype == NN_sub) &&
          (cmd.Op1.type == o_reg) &&
          (cmd.Op1.reg == r_ESP) &&
          (cmd.Op2.type == o_imm)
        )
     {
       supesp = a + size;
       break;
     }
     // final
     a += size;
  }
  // 2) try to find prolog
  if ( supesp == BADADDR )
   return 0;
  int i;
  a = supesp;
  for ( i = 0; (i < 4) && (a < m_end); i++ )
  {
     flag = getFlags(a);
     if ( !isCode(flag) )
      return 0;
     size = ua_ana0(a);
     if ( !size )
       return 0;
     if ( (cmd.itype == NN_call) &&
          (cmd.Op1.type == o_near) &&
          exists_addr(&cmd.Op1) )
     {
       ea_t ca = cmd.Op1.addr;
       if ( is_pic_thunk(ca) )
       {
         m_res = a + size;
         return 1;
       }
     }
     a += size;
  }
  return 0;
}

int prolog_finder::is_pic_thunk(ea_t addr)
{
  if ( m_bx_thunk != BADADDR &&
       m_bx_thunk == addr )
  {
    m_reg = r_EBX;
    return 1;
  }
  if ( m_cx_thunk != BADADDR &&
       m_cx_thunk == addr )
  {
    m_reg = r_ECX;
    return 1;
  }
  flags_t flag = getFlags(addr);
  if ( !isCode(flag) )
   return 0;
  unsigned char thunk_body[4];
  if ( !get_many_bytes(addr, thunk_body, 4) )
   return 0;
  if ( (thunk_body[0] == 0x8B) &&
       (thunk_body[1] == 0x1C) &&
       (thunk_body[2] == 0x24) &&
       (thunk_body[3] == 0xC3) )
  {
    if ( m_bx_thunk == BADADDR )
      m_bx_thunk = addr;
    m_reg = r_EBX;
    return 1;
  }
  if ( (thunk_body[0] == 0x8B) &&
       (thunk_body[1] == 0x0C) &&
       (thunk_body[2] == 0x24) &&
       (thunk_body[3] == 0xC3) )
  {
    if ( m_cx_thunk == BADADDR )
      m_cx_thunk = addr;
    m_reg = r_ECX;
    return 1;
  }
  return 0;
}

void main_process(prolog_finder *pf, ea_t from, ea_t to)
{
  int res = pf->find_prolog(from,to);
  if ( res )
  {
#ifdef RP_DEBUG
    int reg = pf->reg();
    msg("Found prolog at %X reg %d (%s)\n",
     pf->res(), reg, reg_name(reg));
#endif /* RP_DEBUG */
    pf->analyze();
  }

#ifdef RP_DEBUG
  int size;
  flags_t flag;
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
     report_instr(a);
     // final
     a += size;
  }
#endif /* RP_DEBUG */
}

void idaapi
PIC_run(int arg)
{
  ea_t curr_addr = get_screen_ea();
  int n_funcz, i;
  func_t *curr_func;
  prolog_finder pf;

  switch(arg)
  {
    case 0:
     curr_func = get_func(curr_addr);
     if ( NULL == curr_func )
     {
       warning("Cannot operate on non-function address %X\n", curr_addr);
       return;
     }
       main_process(&pf, curr_func->startEA, curr_func->endEA);
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
       main_process(&pf, curr_func->startEA, curr_func->endEA);
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
  if ( ph.id != PLFM_386 )
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
