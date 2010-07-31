/*
 * This plugin analyses PIC code from UNIX-system
 * Red Plait, redplait@gmail.com
 * Version 0.3, 4-III-2000
 *	added support my x86 assembler library, also UDK C compiler PIC prolog
 *	(from UnixWare 7.1)
 * Version 0.2, 3-II-2000
 * Version 0.1, 16-I-2000
 */
#include "pic.hpp"
#include "rp.hpp"
#include "x86.hpp"

#include <name.hpp>
#include <funcs.hpp>
#include <ua.hpp>
#include <xref.hpp>
#include <segment.hpp>

const char *log_filename = "c:\\tmp\\pic.log";
FILE *rp_log_fp = NULL;

/* For debugging there are two macros:
 * PIC_DEBUG - shows misc debug info
 * PIC_SHOW - shows dump cmd for each instruction
 *
 * For Ilfak bugs work around (defined in rp.hpp):
 * NO_DO_FLOAT	if no doFloat exported
 * NO_DO_DOUBLE if no doDouble exported
 */
//#define PIC_SHOW	true
//#define PIC_DEBUG	true

/**************** CONSTS ****************/
/* global offset table possible names */
const char *got_name = "$_GLOBAL_OFFSET_TABLE_",
           *got_name1 = "_GLOBAL_OFFSET_TABLE_",
           *got_name2 = "_got";
/* base register for PIC instructions */
const int pic_reg = r_EBX;

bool is_first = true;
ea_t got_addr = BADADDR;
ea_t got_plt_addr = BADADDR;

#ifdef PIC_SHOW
void
report_instr(ea_t adr)
{
  flags_t flag = getFlags(adr);
  RP_TRACE2("%X (%X)\n", adr, flag);
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
	RP_TRACE1("Opnd1.addr 0x%X\n", cmd.Op1.addr );
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
#endif // PIC_SHOW

ea_t
get_next_code(ea_t start)
{
  segment_t *cs = getseg(start);
  if ( NULL == cs )
   return NULL;

  for ( ; start < cs->endEA; start = get_item_end(start) )
   if ( isCode(start) )
    return start;
  return cs->endEA;
}

void
one_switch_entry(ea_t ea, ea_t ptr)
{
  if ( !isData(ea) )
   do_unknown_range(ea, 4, true);
  add_cref(ea, ptr, 
#if (IDP_INTERFACE_VERSION > 65)
  fl_USobsolete
#else
  fl_US
#endif
  );
  char abuf[0x10];
  btoa(abuf, 0x10, ptr, 0x10);
  rp_set_comment(ea, abuf, false );
  ua_code(ptr);
  doDwrd(ea, 4);
#ifdef PIC_DEBUG
 RP_TRACE2("add_cref %X to %X\n", ea, ptr );
#endif
}

void
process_switchA(ea_t curr, ea_t start, unsigned int N)
{
  ea_t diff = start - curr;
  unsigned long i;

  if ( diff && diff < 4 )
  {
    do_unknown_range(curr, diff, true);
  }
  if ( isTail(getFlags(start)) )
     do_unknown(prev_not_tail(start),false);
  else
     do_unknown_range(start, N << 2, true);
  for ( i = 0; i <= N; i++ )
  {
    diff = start + (i<<2);
    one_switch_entry(diff, got_addr - get_long(diff));
  }
}

int
process_switchB(ea_t curr, ea_t start, ea_t func_end)
{
  ea_t diff = start - curr, 
       min = func_end,
       ptr;
  unsigned long i;

  if ( diff && diff < 4 )
  {
    do_unknown_range(curr, diff, true);
  }
#ifdef PIC_DEBUG
 RP_TRACE2("start %X, to %X\n", start, func_end);
#endif
  ptr = get_next_code(start);
  if ( NULL == ptr )
   do_unknown(start,false);
  else
  {
   if ( isTail(getFlags(start)) )
   {
     do_unknown(prev_not_tail(start),false);
   }
   else
     do_unknown_range(start, ptr-start, true);
  }
  for ( i = 0; start+i < min; i += 4 )
  {
    ptr = got_addr - get_long(start + i);
#ifdef PIC_DEBUG
 RP_TRACE3("min is %X, ptr %X, i %d\n", min, ptr, i);
#endif
    if ( ptr < func_end )
    {
      if ( ptr < min )
        min = ptr;
#ifdef PIC_DEBUG
 RP_TRACE2("one_switch_entry %X, ptr %X\n", start+i, ptr );
#endif
      one_switch_entry(start+i, ptr);
    } else
     break; /* end ? */
  }
  return (i>>2);
}

bool
is_change_PIC_reg(const insn_t *instr)
{
  const struct RP_opcode *rp = get_opcode(instr);
  if ( NULL == rp )
   return false;
  return is_change_reg(instr, rp, pic_reg);
}

static int is_gotbase_call(ea_t addr)
{
  unsigned char buf[4];
  get_many_bytes(addr, buf, 4);
  if ( buf[0] == 0x8B &&
       buf[1] == 0x1C &&
       buf[2] == 0x24 &&
       buf[3] == 0xC3 )
   return 1;
  return 0;
}

int is_gotbase()
{
  if ( cmd.itype == Ix86_call &&
       cmd.Op1.type == o_near )
  {
    return is_gotbase_call(cmd.Op1.addr);
  }
  return 0;
}

/* main workhorse */
void
process_PIC(ea_t from, ea_t to)
{
  int size;
  flags_t flag;
  dref_t dtype;
  bool has_PIC_init = false;
/***********************************************************\
 * Also we trace three special cases:
 * 1. Raw (not recognized ed by IDA) PIC prolog.
 *   call $+5
 *   pop ebx <-- fake_addr
 *   ... one or more non related with ebx instr
 *   add ebx, offset_to_GOT
 * 2. Switch stmt
 * a) with known size N
 *   cmp reg1, N
 *   ja ...
 *   mov reg2, ebx
 *   sub reg2, [ebx+reg1*4+offset]
 *   jmp reg2
 * b) more general but size is unknown
 *   mov reg1, ebx
 *   sub reg1, [ebx+regX*4+offset]
 *   jmp reg1
 * 3. On UnixWare 7 UDK C compiler produced prolog
 *  jmp end_of_function
 * main_function_body:
 *  ...
 * end_of_function:
 *  prolog like 1)
 *  jmp main_function_body
\***********************************************************/
  int first_case = 0;
  ea_t fake_addr = 0;
  ea_t pic_to = 0;
  int second_case = 0;
  int reg1 = pic_reg, reg2, N = 0, offset;
  int second_caseB = 0;

  int there_jump = 0, from_jump, to_jump;

#ifdef PIC_DEBUG
  RP_TRACE1("start %X\n", from);
  RP_TRACE1("end %X\n", to);
#endif
  for ( ea_t a = from; a < to; )
  {
     flag = getFlags(a);
     if ( !isCode(flag) )
     {
       a++;
       continue;
     }
     size = ua_ana0(a);
#define PIC_CONT	a += size; continue;
     if ( !size )
     {
       warning("Bad instruction at %X", a);
       a++;
       continue;
     }
#ifdef PIC_SHOW
 report_instr(a);
#endif
     if ( !has_PIC_init )
     {
        if ( !there_jump )
        {
          if ( cmd.itype == Ix86_jmp &&
	       ( cmd.Op1.type == o_near || cmd.Op1.type == o_far ) &&
	       cmd.Op1.addr < to &&
	       cmd.Op1.addr > a )
	  {
	    from_jump = a + size;
	    there_jump = 1;
	    to_jump = a = cmd.Op1.addr;
#ifdef PIC_DEBUG
 RP_TRACE2("from_jump %X, to_jump %X\n", from_jump, to_jump);
#endif
	    continue;
	  }
          there_jump = -1;
        }
        if ( !first_case && is_gotbase() )
        {
          first_case = 2;
          fake_addr = a + size;
          PIC_CONT;
        }
        if ( first_case )
          switch(first_case)
          {
             case 1:
               if ( cmd.itype == Ix86_pop &&
                    cmd.Op1.type == o_reg &&
                    cmd.Op1.reg == pic_reg )
               {
                 first_case = 2;
#ifdef PIC_DEBUG
 RP_TRACE("first case 2\n");
#endif
               } else
               {
                 if ( is_change_stack(&cmd) )
		 {
                   first_case = 0;
                 } else
	 	 {
		   PIC_CONT;
		 }
               }
                break;
             case 2:
               if ( cmd.itype == Ix86_add  &&
	            cmd.Op1.type == 1	   &&
		    cmd.Op1.reg == pic_reg &&
		    cmd.Op2.type == o_imm )
	       {
		  pic_to = fake_addr + cmd.Op2.value;
	          if ( (pic_to != got_addr) &&
                       (pic_to != got_plt_addr)
                     )
	            warning("Strange PIC prolog at %X, points to %X", a, pic_to);
#ifdef PIC_DEBUG
 RP_TRACE("PIC_init 1\n");
#endif
		  pic_add_dref(a, pic_to, dr_O, cmd.Op2.dtyp);
                  has_PIC_init = true;
                  first_case = 0;
	       }
	       if ( is_change_PIC_reg(&cmd) )
	       {
	          first_case = 0;
     	       }
                break;
          }
        if ( first_case || has_PIC_init )
        {
          PIC_CONT;
        }
        if ( cmd.itype == Ix86_mov	&&
             cmd.Op1.type == o_reg	&&
             cmd.Op1.reg == pic_reg	&&
             cmd.Op2.type == o_imm 	&&
             cmd.Op2.value == got_addr )
        {
          has_PIC_init = true;
#ifdef PIC_DEBUG
 RP_TRACE("PIC_init 2\n");
#endif
          PIC_CONT;
        }
        if ( cmd.itype == Ix86_call &&
             cmd.Op1.type == o_near &&
             cmd.Op1.addr == a + 5 )
        {
          first_case = 1;
          fake_addr = a + size;
#ifdef PIC_DEBUG
 RP_TRACE("first_case 1\n");
#endif
          PIC_CONT;
        }
       PIC_CONT;
     } /* not prolog yet */
     if ( there_jump == 1 &&
	  cmd.itype == Ix86_jmp &&
	  ( cmd.Op1.type == o_near || cmd.Op1.type == o_far ) &&
	  cmd.Op1.addr < to &&
	  cmd.Op1.addr < a  &&
	  cmd.Op1.addr >= from_jump )
     {
       there_jump = 2;
       a = from_jump;
       to = to_jump;
       continue;
     }
     if ( second_case )
       switch(second_case)
       {
         case 1:
          if ( cmd.itype == Ix86_ja &&
	       (cmd.Op1.type == o_far || cmd.Op1.type == o_near) )
	  {
#ifdef PIC_DEBUG
 RP_TRACE("second_case 2\n");
#endif
	    second_case = 2;
	  } else
	  {
	    second_case = 0;
	  }
           break;
         case 2:
          if ( cmd.itype == Ix86_mov	  &&
	       cmd.Op1.type == o_reg 	  &&
	       cmd.Op2.type == o_reg	  &&
	       cmd.Op2.reg == pic_reg )
	  {
	     reg2 = cmd.Op1.reg;
#ifdef PIC_DEBUG
 RP_TRACE("second_case 3\n");
#endif
	     second_case = 3;
	  } else
	  {
   	     second_case = 0;
	  }
	   break;
         case 3:
          if ( cmd.itype == Ix86_sub   &&
	       cmd.Op1.type == o_reg   &&
	       cmd.Op1.reg == reg2     &&
	       cmd.Op2.type == o_displ &&
	       cmd.Op2.specflag1 == 1  &&
	       get_SIB_base(cmd.Op2.specflag2) == pic_reg	&&
	       get_SIB_reg(cmd.Op2.specflag2) == reg1		&&
	       get_SIB_SS(cmd.Op2.specflag2) == 2 ) /* wow! sub reg2, [pic_reg+reg1*4+offset] */
	  {
	     offset = cmd.Op2.addr;
	     pic_add_dref(a, pic_to + offset, dr_O, cmd.Op2.dtyp);
#ifdef PIC_DEBUG
 RP_TRACE("second_case 4\n");
#endif
	     second_case = 4;
	  } else
	  {
#ifdef PIC_DEBUG
 RP_TRACE5("%d <-> %d, %d <-> %d, %d\n",
  get_SIB_base(cmd.Op2.specflag2), pic_reg,
  get_SIB_reg(cmd.Op2.specflag2), reg1,
  get_SIB_SS(cmd.Op2.specflag2) );
#endif
	     second_case = 0;
	  }
	   break;
         case 4:
          if ( cmd.itype == Ix86_jmpni &&
	       cmd.Op1.type == o_reg &&
	       cmd.Op1.reg == reg2 )
	  {
#ifdef PIC_DEBUG
 RP_TRACE2("second_case: %d from %X\n", N, (got_addr + offset) );
#endif
	     process_switchA(a+size, pic_to + offset, N);
	     second_case = 0;
	     PIC_CONT;
	  } else
	  {
	     second_case = 0;
	  }
	   break;
       }
       if ( second_case )
       {
         PIC_CONT;
       }
       if ( cmd.itype == Ix86_cmp &&
	    cmd.Op1.type == o_reg &&
	    cmd.Op2.type == o_imm )
       {
          second_case = 1;
          reg1 = cmd.Op1.reg;
          N = cmd.Op2.value;
          PIC_CONT;
       }
       /* check for 2b case */
       if ( second_caseB )
        switch(second_caseB)
        {
          case 1:
           if ( cmd.itype == Ix86_sub   &&
		cmd.Op1.type == o_reg   &&
		cmd.Op1.reg == reg1     &&
	 	cmd.Op2.type == o_displ	&&
                cmd.Op2.specflag1 == 1	&&
		get_SIB_base(cmd.Op2.specflag2) == pic_reg &&
		get_SIB_reg(cmd.Op2.specflag2) != pic_reg  &&
		get_SIB_SS(cmd.Op2.specflag2) == 2 )
	   {
	     offset = cmd.Op2.addr;
	     second_caseB = 2;
#ifdef PIC_DEBUG
 RP_TRACE("second_caseB is 2\n");
#endif
	   } else
	   {
#ifdef PIC_DEBUG
 RP_TRACE5("%d <-> %d, %d <-> %d, %d\n",
  get_SIB_base(cmd.Op2.specflag2), pic_reg,
  get_SIB_reg(cmd.Op2.specflag2), reg1,
  get_SIB_SS(cmd.Op2.specflag2) );
#endif
	     second_caseB = 0;
	   }
            break;
          case 2:
	   if ( cmd.itype == Ix86_jmpni &&
	        cmd.Op1.type == o_reg &&
	        cmd.Op1.reg == reg1 )
	   {
#ifdef PIC_DEBUG
 RP_TRACE1("second_caseB: from %X\n", (got_addr + offset) );
#endif
	     process_switchB(a+size, pic_to + offset, to);
	     second_caseB = 0;
	     PIC_CONT;
	   } else
	   {
	     second_caseB = 0;
	   }
            break;
        } /* second_caseB switch */
       if ( cmd.itype == Ix86_mov &&
            cmd.Op1.type == o_reg &&
            cmd.Op2.type == o_reg &&
            cmd.Op2.reg == pic_reg )
       {
          second_caseB = 1;
          reg1 = cmd.Op1.reg;
#ifdef PIC_DEBUG
 RP_TRACE("second_caseB is 1\n");
#endif
          PIC_CONT; /* ?? we anyway don`t deal with such instruction... */
       }
       /* no more special cases... */
       /* check for 1st operand for pic_reg */
       if ( cmd.Op1.type == o_displ )
       {
         if ( cmd.Op1.phrase == pic_reg  &&
	      ! cmd.Op1.specflag1 )
	 {
           fake_addr = 0;
           if ( exists_addr(&cmd.Op1) )
             fake_addr = cmd.Op1.addr;
	   dtype = get_dreftype_op1(&cmd);
	   pic_add_dref(a, pic_to + fake_addr, dtype, cmd.Op1.dtyp);
#ifdef PIC_DEBUG
 RP_TRACE1("PIC: %X\n", got_addr + fake_addr);
#endif
           PIC_CONT;
         }
         if ( cmd.Op1.specflag1 == 1 && (
             ( get_SIB_base(cmd.Op1.specflag2) == pic_reg  &&
               get_SIB_reg(cmd.Op1.specflag2) != pic_reg ) 	||
             ( get_SIB_base(cmd.Op1.specflag2) != pic_reg  &&
               get_SIB_reg(cmd.Op1.specflag2) == pic_reg   &&
               get_SIB_SS(cmd.Op1.specflag2) == 0 ) ) )
         {
            fake_addr = 0;
            if ( exists_addr(&cmd.Op1) )
              fake_addr = cmd.Op1.addr;
	    dtype = get_dreftype_op1(&cmd);
	    pic_add_dref(a, pic_to + fake_addr, dtype, cmd.Op1.dtyp);
#ifdef PIC_DEBUG
 RP_TRACE1("PIC: %X\n", got_addr + fake_addr);
#endif
            PIC_CONT;
         }
       }
       /* check for 2nd operand for pic_reg */
       if ( cmd.Op2.type == o_displ )
       {
         if ( cmd.Op2.phrase == pic_reg  &&
	      ! cmd.Op2.specflag1 )
	 {
           fake_addr = 0;
           if ( exists_addr(&cmd.Op2) )
             fake_addr = cmd.Op2.addr;
	   pic_add_dref(a, pic_to + fake_addr, get_dreftype_op2(&cmd), cmd.Op2.dtyp);
#ifdef PIC_DEBUG
 RP_TRACE1("PIC: %X\n", got_addr + fake_addr);
#endif
           PIC_CONT;
         }
         if ( cmd.Op2.specflag1 == 1 && (
             ( get_SIB_base(cmd.Op2.specflag2) == pic_reg  &&
               get_SIB_reg(cmd.Op2.specflag2) != pic_reg ) 	||
             ( get_SIB_base(cmd.Op2.specflag2) != pic_reg  &&
               get_SIB_reg(cmd.Op2.specflag2) == pic_reg   &&
               get_SIB_SS(cmd.Op2.specflag2) == 0 ) ) )
         {
            fake_addr = 0;
            if ( exists_addr(&cmd.Op2) )
              fake_addr = cmd.Op2.addr;
#ifdef PIC_DEBUG
 RP_TRACE1("PIC: %X\n", got_addr + fake_addr);
#endif      
	    pic_add_dref(a, pic_to + fake_addr, get_dreftype_op2(&cmd), cmd.Op2.dtyp);
            PIC_CONT;
         }
       }
     a += size;
  }
}

int idaapi
PIC_init(void)
{
/* Strange bug - file opened hier but closed and eq NULL in PIC_run function !
 * Gluck...
 * if ( NULL == ( rp_log_fp = fopen(log_filename, "w+t") ) )
 * {
 *  warning("Cannot open log file %s, errno = %d\n",
 *    log_filename, errno );
 *  return PLUGIN_SKIP;
 * }
 */
#ifdef PIC_DEBUG
 msg("PIC: filetype %d\n", inf.filetype );
#endif
 if ( inf.filetype != f_COFF   &&
      inf.filetype != f_AR     &&
      inf.filetype != f_LOADER &&
      inf.filetype != f_ELF    &&
      inf.filetype != f_AOUT )
   return PLUGIN_SKIP;
#ifdef PIC_DEBUG
 msg("Current proc type %d\n", ph.id);
#endif
 if ( ph.id != PLFM_386 )
   return PLUGIN_SKIP;
 return PLUGIN_OK;
}

void idaapi
PIC_term(void)
{
#ifdef PIC_DEBUG
  msg("PIC_term\n");
#endif
  if ( NULL != rp_log_fp )
  {
    fclose(rp_log_fp);
    rp_log_fp = NULL;
  }
}

void idaapi
PIC_run(int arg)
{
  ea_t curr_addr;
  int n_funcz, i;
  func_t *curr_func;

  if ( is_first )
  {
    got_addr = get_name_ea(BADADDR, got_name);
    if ( BADADDR == got_addr )
    {
      got_addr = get_name_ea(BADADDR,got_name1);
      if ( BADADDR != got_addr )
      {
        got_addr = get_long(got_addr);
      } else
      {
        got_addr = get_name_ea(BADADDR, got_name2);
      }
    }
    is_first = false;
    // 2 Nov 2005: dirty hack, bcs get_name_ea("_got") return BADADDR
    segment_t *s;
    if ( BADADDR == got_addr )
    {
      s = get_segm_by_name(".got");
      if ( s != NULL )
       got_addr = s->startEA; 
    }
    // 14 oct 2009
    s = get_segm_by_name(".got.plt");
    if ( s != NULL )
      got_plt_addr = s->startEA;
  }
  if ( BADADDR == got_addr )
  {
    msg("Cannot resolve _got address. Bad plugin initialization");
    return;
  }
#ifdef PIC_DEBUG
  RP_TRACE1( "got_addr %X\n", got_addr );
#endif
  switch (arg)
  {
   case 0: /* only function under current EA */
     curr_addr = get_screen_ea();
#ifdef PIC_DEBUG
     RP_TRACE1( "curr_addr %X\n", curr_addr );
#endif
     /* next I had to resolve function */
     curr_func = get_func(curr_addr);
     if ( NULL == curr_func )
     {
       warning("Cannot operate not on function, address %X\n", curr_addr);
       return;
     }
#if defined(PIC_DEBUG) || defined(PIC_SHOW)
     rp_log_fp = fopen(log_filename, "w+t");
#endif
     process_PIC(curr_func->startEA, curr_func->endEA);
#if defined(PIC_DEBUG) || defined(PIC_SHOW)
     if ( NULL != rp_log_fp )
     {
      fclose(rp_log_fp);
      rp_log_fp = NULL;
     }
#endif
    break;
   case 1: /* process all defined functions */
#if defined(PIC_DEBUG) || defined(PIC_SHOW)
     rp_log_fp = fopen(log_filename, "w+t");
#endif
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
         RP_TRACE1("PIC: cannot get func N %d\n", i);
         continue;
       }
       process_PIC(curr_func->startEA, curr_func->endEA);
     }
#if defined(PIC_DEBUG) || defined(PIC_SHOW)
     if ( NULL != rp_log_fp )
     {
      fclose(rp_log_fp);
      rp_log_fp = NULL;
     }
#endif
    break;
   default:
     warning("PIC: Unknown arg %d", arg);
    break;
  } /* switch */
}

char PIC_comment[] = "Code analyzer plugin for UNIX position independent i386 code";
char PIC_help[] =
 "PIC code analyzer plugin\n"
  "\n"
  "This plugin analyses position independent code (mostly from UNIX-systems) for Intel i386 processors family";
char PIC_wanted_name[] = "PIC analyzer plugin";
char PIC_wanted_hotkey[] = "Alt-P";

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
