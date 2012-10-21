#include <ida.hpp>
#include <idp.hpp>
#include <name.hpp>
#include <bytes.hpp>
#include <loader.hpp>
#include <kernwin.hpp>
#include "disasm.h"
#include "dis_tables.h"
#include "bochs.inc"
// two tables from Bochs disasm
const struct BxDisasmOpcodeInfo_t Ia_Invalid = { "(invalid)", (avx_insn_type_t)0, XX, XX, XX, XX, 0 };
#include "dis_tables_avx.inc"
#include "dis_tables_xop.inc"
#include "und_tables.h"
#include <intel.hpp>

static BxDisasmOpcodeTable_t BxDisasmGroupSSE_ERR[4] = {
  /* -- */ { 0, &Ia_Invalid },
  /* 66 */ { 0, &Ia_Invalid },
  /* F3 */ { 0, &Ia_Invalid },
  /* F2 */ { 0, &Ia_Invalid }
};

static ea_t ea_start; // address of current instruction start
static ea_t ea; // current address within the instruction

//
// disasm from Bochs implementation
//
//////////////////
// Intel STYLE
//////////////////

static const char *intel_general_16bit_regname[16] = {
    "ax",  "cx",  "dx",   "bx",   "sp",   "bp",   "si",   "di",
    "r8w", "r9w", "r10w", "r11w", "r12w", "r13w", "r14w", "r15w"
};

static const char *intel_general_32bit_regname[16] = {
    "eax", "ecx", "edx",  "ebx",  "esp",  "ebp",  "esi",  "edi",
    "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d"
};

static const char *intel_general_64bit_regname[16] = {
    "rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi",
    "r8",  "r9",  "r10", "r11", "r12", "r13", "r14", "r15"
};

static const char *intel_general_8bit_regname_rex[16] = {
    "al",  "cl",  "dl",   "bl",   "spl",  "bpl",  "sil",  "dil",
    "r8b", "r9b", "r10b", "r11b", "r12b", "r13b", "r14b", "r15b"
};

static const char *intel_general_8bit_regname[8] = {
    "al",  "cl",  "dl",  "bl",  "ah",  "ch",  "dh",  "bh"
};

static const char *intel_segment_name[8] = {
    "es",  "cs",  "ss",  "ds",  "fs",  "gs",  "??",  "??"
};

static const char *intel_index16[8] = {
    "bx+si",
    "bx+di",
    "bp+si",
    "bp+di",
    "si",
    "di",
    "bp",
    "bx"
};

static const char *intel_vector_reg_name[2] = {
    "xmm", "ymm"
};

void disassembler::set_syntax_intel()
{
  intel_mode = 1;

  general_16bit_regname = intel_general_16bit_regname;
  general_8bit_regname = intel_general_8bit_regname;
  general_32bit_regname = intel_general_32bit_regname;
  general_8bit_regname_rex = intel_general_8bit_regname_rex;
  general_64bit_regname = intel_general_64bit_regname;

  segment_name = intel_segment_name;
  index16 = intel_index16;
  vector_reg_name = intel_vector_reg_name;

  initialize_modrm_segregs();
}

void disassembler::initialize_modrm_segregs()
{
  sreg_mod00_rm16[0] = segment_name[DS_REG];
  sreg_mod00_rm16[1] = segment_name[DS_REG];
  sreg_mod00_rm16[2] = segment_name[SS_REG];
  sreg_mod00_rm16[3] = segment_name[SS_REG];
  sreg_mod00_rm16[4] = segment_name[DS_REG];
  sreg_mod00_rm16[5] = segment_name[DS_REG];
  sreg_mod00_rm16[6] = segment_name[DS_REG];
  sreg_mod00_rm16[7] = segment_name[DS_REG];

  sreg_mod01or10_rm16[0] = segment_name[DS_REG];
  sreg_mod01or10_rm16[1] = segment_name[DS_REG];
  sreg_mod01or10_rm16[2] = segment_name[SS_REG];
  sreg_mod01or10_rm16[3] = segment_name[SS_REG];
  sreg_mod01or10_rm16[4] = segment_name[DS_REG];
  sreg_mod01or10_rm16[5] = segment_name[DS_REG];
  sreg_mod01or10_rm16[6] = segment_name[SS_REG];
  sreg_mod01or10_rm16[7] = segment_name[DS_REG];

  sreg_mod00_base32[0]  = segment_name[DS_REG];
  sreg_mod00_base32[1]  = segment_name[DS_REG];
  sreg_mod00_base32[2]  = segment_name[DS_REG];
  sreg_mod00_base32[3]  = segment_name[DS_REG];
  sreg_mod00_base32[4]  = segment_name[SS_REG];
  sreg_mod00_base32[5]  = segment_name[DS_REG];
  sreg_mod00_base32[6]  = segment_name[DS_REG];
  sreg_mod00_base32[7]  = segment_name[DS_REG];
  sreg_mod00_base32[8]  = segment_name[DS_REG];
  sreg_mod00_base32[9]  = segment_name[DS_REG];
  sreg_mod00_base32[10] = segment_name[DS_REG];
  sreg_mod00_base32[11] = segment_name[DS_REG];
  sreg_mod00_base32[12] = segment_name[DS_REG];
  sreg_mod00_base32[13] = segment_name[DS_REG];
  sreg_mod00_base32[14] = segment_name[DS_REG];
  sreg_mod00_base32[15] = segment_name[DS_REG];

  sreg_mod01or10_base32[0]  = segment_name[DS_REG];
  sreg_mod01or10_base32[1]  = segment_name[DS_REG];
  sreg_mod01or10_base32[2]  = segment_name[DS_REG];
  sreg_mod01or10_base32[3]  = segment_name[DS_REG];
  sreg_mod01or10_base32[4]  = segment_name[SS_REG];
  sreg_mod01or10_base32[5]  = segment_name[SS_REG];
  sreg_mod01or10_base32[6]  = segment_name[DS_REG];
  sreg_mod01or10_base32[7]  = segment_name[DS_REG];
  sreg_mod01or10_base32[8]  = segment_name[DS_REG];
  sreg_mod01or10_base32[9]  = segment_name[DS_REG];
  sreg_mod01or10_base32[10] = segment_name[DS_REG];
  sreg_mod01or10_base32[11] = segment_name[DS_REG];
  sreg_mod01or10_base32[12] = segment_name[DS_REG];
  sreg_mod01or10_base32[13] = segment_name[DS_REG];
  sreg_mod01or10_base32[14] = segment_name[DS_REG];
  sreg_mod01or10_base32[15] = segment_name[DS_REG];
}

Bit8u disassembler::fetch_byte_at(int off)
{
  return get_byte(ea_start + off);
}

Bit8u disassembler::fetch_byte() 
{
  return get_byte(ea++);
};

Bit8u disassembler::peek_byte() 
{
  return get_byte(ea);
};

Bit16u disassembler::fetch_word() 
{
  Bit16u res = get_word(ea); 
  ea += 2;
  return res;
};

Bit32u disassembler::fetch_dword() 
{
  Bit32u res = get_long(ea);
  ea += 4;
  return res;
};

Bit64u disassembler::fetch_qword() 
{
  Bit64u res = get_qword(ea);
  ea += 8;
  return res;
};

#define OPCODE(entry) ((BxDisasmOpcodeInfo_t*) entry->OpcodeInfo)
#define OPCODE_TABLE(entry) ((BxDisasmOpcodeTable_t*) entry->OpcodeInfo)

static const unsigned char instruction_has_modrm[512] = {
  /*       0 1 2 3 4 5 6 7 8 9 a b c d e f          */
  /*       -------------------------------          */
  /* 00 */ 1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,
  /* 10 */ 1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,
  /* 20 */ 1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,
  /* 30 */ 1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,
  /* 40 */ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  /* 50 */ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  /* 60 */ 0,0,1,1,0,0,0,0,0,1,0,1,0,0,0,0,
  /* 70 */ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  /* 80 */ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  /* 90 */ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  /* A0 */ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  /* B0 */ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  /* C0 */ 1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,
  /* D0 */ 1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,
  /* E0 */ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  /* F0 */ 0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,
  /*       0 1 2 3 4 5 6 7 8 9 a b c d e f           */
  /*       -------------------------------           */
           1,1,1,1,0,0,0,0,0,0,0,0,0,1,0,1, /* 0F 00 */
           1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, /* 0F 10 */
           1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1, /* 0F 20 */
           0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0, /* 0F 30 */
           1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, /* 0F 40 */
           1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, /* 0F 50 */
           1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, /* 0F 60 */
           1,1,1,1,1,1,1,0,1,1,0,0,1,1,1,1, /* 0F 70 */
           0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /* 0F 80 */
           1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, /* 0F 90 */
           0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1, /* 0F A0 */
           1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, /* 0F B0 */
           1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0, /* 0F C0 */
           1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, /* 0F D0 */
           1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, /* 0F E0 */
           1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0  /* 0F F0 */
  /*       -------------------------------           */
  /*       0 1 2 3 4 5 6 7 8 9 a b c d e f           */
};

void disassembler::print_disassembly_intel(const x86_insn *insn, const BxDisasmOpcodeInfo_t *entry)
{
  if (entry->Operand1) {
    (this->*entry->Operand1)(insn, 0);
  }
  if (entry->Operand2) {
    (this->*entry->Operand2)(insn, 1);
  }
  if (entry->Operand3) {
    (this->*entry->Operand3)(insn, 2);
  }
  if (entry->Operand4) {
    (this->*entry->Operand4)(insn, 3);
  }
}

void disassembler::decode_modrm(x86_insn *insn)
{
  insn->modrm = fetch_byte();
  BX_DECODE_MODRM(insn->modrm, insn->mod, insn->nnn, insn->rm);
  // MOVs with CRx and DRx always use register ops and ignore the mod field.
  if ((insn->b1 & ~3) == 0x120) insn->mod = 3;

  insn->nnn |= insn->rex_r;
  insn->rm  |= insn->rex_b;

  if ( insn->rex_b )
    cmd.rex |= REX_B;
  if ( insn->rex_r )
    cmd.rex |= REX_R;
  if ( insn->rex_x )
    cmd.rex |= REX_X;
  if (insn->mod == 3) {
    return; /* mod, reg, reg */
  }

  if (insn->as_64)
  {
      if ((insn->rm & 7) != 4) { /* rm != 100b, no s-i-b byte */
        // one byte modrm
        switch (insn->mod) {
          case 0:
            resolve_modrm = &disassembler::resolve64_mod0;
            if ((insn->rm & 7) == 5) /* no reg, 32-bit displacement */
              insn->displacement.displ32 = fetch_dword();
            break;
          case 1:
            /* reg, 8-bit displacement, sign extend */
            resolve_modrm = &disassembler::resolve64_mod1or2;
            insn->displacement.displ32 = (Bit8s) fetch_byte();
            break;
          case 2:
            /* reg, 32-bit displacement */
            resolve_modrm = &disassembler::resolve64_mod1or2;
            insn->displacement.displ32 = fetch_dword();
            break;
        } /* switch (mod) */
      } /* if (rm != 4) */
      else { /* rm == 4, s-i-b byte follows */
        insn->Sib = fetch_byte();
        BX_DECODE_SIB(insn->Sib, insn->scale, insn->index, insn->base);
        insn->base  |= insn->rex_b;
        insn->index |= insn->rex_x;

        switch (insn->mod) {
          case 0:
            resolve_modrm = &disassembler::resolve64_mod0_rm4;
            if ((insn->base & 7) == 5)
              insn->displacement.displ32 = fetch_dword();
            break;
          case 1:
            resolve_modrm = &disassembler::resolve64_mod1or2_rm4;
            insn->displacement.displ32 = (Bit8s) fetch_byte();
            break;
          case 2:
            resolve_modrm = &disassembler::resolve64_mod1or2_rm4;
            insn->displacement.displ32 = fetch_dword();
            break;
        }
      } /* s-i-b byte follows */
  }
  else
  {
    if (insn->as_32)
    {
      if ((insn->rm & 7) != 4) { /* rm != 100b, no s-i-b byte */
        // one byte modrm
        switch (insn->mod) {
          case 0:
            resolve_modrm = &disassembler::resolve32_mod0;
            if ((insn->rm & 7) == 5) /* no reg, 32-bit displacement */
              insn->displacement.displ32 = fetch_dword();
            break;
          case 1:
            /* reg, 8-bit displacement, sign extend */
            resolve_modrm = &disassembler::resolve32_mod1or2;
            insn->displacement.displ32 = (Bit8s) fetch_byte();
            break;
          case 2:
            /* reg, 32-bit displacement */
            resolve_modrm = &disassembler::resolve32_mod1or2;
            insn->displacement.displ32 = fetch_dword();
            break;
        } /* switch (mod) */
      } /* if (rm != 4) */
      else { /* rm == 4, s-i-b byte follows */
        insn->Sib = fetch_byte();
        BX_DECODE_SIB(insn->Sib, insn->scale, insn->index, insn->base);
        insn->base  |= insn->rex_b;
        insn->index |= insn->rex_x;

        switch (insn->mod) {
          case 0:
            resolve_modrm = &disassembler::resolve32_mod0_rm4;
            if ((insn->base & 7) == 5)
              insn->displacement.displ32 = fetch_dword();
            break;
          case 1:
            resolve_modrm = &disassembler::resolve32_mod1or2_rm4;
            insn->displacement.displ32 = (Bit8s) fetch_byte();
            break;
          case 2:
            resolve_modrm = &disassembler::resolve32_mod1or2_rm4;
            insn->displacement.displ32 = fetch_dword();
            break;
        }
      } /* s-i-b byte follows */
    }
    else {
      assert(insn->rex_b == 0);
      assert(insn->rex_x == 0);
      assert(insn->rex_r == 0);
      /* 16 bit addressing modes. */
      switch (insn->mod) {
        case 0:
          resolve_modrm = &disassembler::resolve16_mod0;
          if(insn->rm == 6)
            insn->displacement.displ16 = fetch_word();
          break;
        case 1:
          /* reg, 8-bit displacement, sign extend */
          resolve_modrm = &disassembler::resolve16_mod1or2;
          insn->displacement.displ16 = (Bit8s) fetch_byte();
          break;
        case 2:
          resolve_modrm = &disassembler::resolve16_mod1or2;
          insn->displacement.displ16 = fetch_word();
          break;
      } /* switch (mod) ... */
    }
  }
}

void disassembler::resolve16_mod0(const x86_insn *insn, unsigned datasize, int op_n)
{
  const char *seg;

  if (insn->is_seg_override())
    seg = segment_name[insn->seg_override];
  else
    seg = sreg_mod00_rm16[insn->rm];

  if(insn->rm == 6)
    print_memory_access16(datasize, seg, NULL, insn->displacement.displ16, op_n);
  else
    print_memory_access16(datasize, seg, insn->rm, 0, op_n);
}

void disassembler::resolve16_mod1or2(const x86_insn *insn, unsigned datasize, int op_n)
{
  const char *seg;

  if (insn->is_seg_override())
    seg = segment_name[insn->seg_override];
  else
    seg = sreg_mod01or10_rm16[insn->rm];

  print_memory_access16(datasize, seg, insn->rm, insn->displacement.displ16, op_n);
}

void disassembler::resolve32_mod0(const x86_insn *insn, unsigned datasize, int op_n)
{
  const char *seg;

  if (insn->is_seg_override())
    seg = segment_name[insn->seg_override];
  else
    seg = segment_name[DS_REG];

  if ((insn->rm & 7) == 5) /* no reg, 32-bit displacement */
    print_memory_access32(datasize, seg, R_ip, NULL, 0, insn->displacement.displ32, op_n);
  else
    print_memory_access32(datasize, seg, R_ax + insn->rm, NULL, 0, 0, op_n);
}

void disassembler::resolve32_mod1or2(const x86_insn *insn, unsigned datasize, int op_n)
{
  const char *seg;

  if (insn->is_seg_override())
    seg = segment_name[insn->seg_override];
  else
    seg = sreg_mod01or10_base32[insn->rm];

  print_memory_access32(datasize, seg,
      R_ax + insn->rm, NULL, 0, insn->displacement.displ32, op_n);
}

void disassembler::resolve32_mod0_rm4(const x86_insn *insn, unsigned datasize, int op_n)
{
  char vsib_index[8];
  int index = 0;
  int base = 0;
  const char *seg;
  Bit32u disp32 = 0;

  if (insn->is_seg_override())
    seg = segment_name[insn->seg_override];
  else
    seg = sreg_mod00_base32[insn->base];

  if ((insn->base & 7) != 5)
    base = R_ax + insn->base;
  else
    disp32 = insn->displacement.displ32;

  if (datasize & VSIB_Index) {
    sprintf(vsib_index, "%s%d", vector_reg_name[insn->vex_l], insn->index);
    index = R_xmm0 + insn->index;
  }
  else {
    if (insn->index != 4)
      index = R_ax + insn->index;
  }

  print_memory_access32(datasize, seg, base, index, insn->scale, disp32, op_n);
}

void disassembler::resolve32_mod1or2_rm4(const x86_insn *insn, unsigned datasize, int op_n)
{
  char vsib_index[8];
  int index = 0;
  const char *seg;

  if (insn->is_seg_override())
    seg = segment_name[insn->seg_override];
  else
    seg = sreg_mod01or10_base32[insn->base];

  if (datasize & VSIB_Index) {
    sprintf(vsib_index, "%s%d", vector_reg_name[insn->vex_l], insn->index);
    index = R_xmm0 + insn->index;
  }
  else {
    if (insn->index != 4)
      index = R_ax + insn->index;
  }

  print_memory_access32(datasize, seg,
      R_ax + insn->base, index, insn->scale, insn->displacement.displ32, op_n);
}

void disassembler::resolve64_mod0(const x86_insn *insn, unsigned datasize, int op_n)
{
  const char *seg, *rip_regname;

  if (insn->is_seg_override())
    seg = segment_name[insn->seg_override];
  else
    seg = segment_name[DS_REG];

  rip_regname = "rip";

  if ((insn->rm & 7) == 5) /* no reg, 32-bit displacement */
    print_memory_access64(datasize, seg, R_ip, NULL, 0, (Bit32s) insn->displacement.displ32, op_n);
  else
    print_memory_access64(datasize, seg, R_ax + insn->rm, NULL, 0, 0, op_n);
}

void disassembler::resolve64_mod1or2(const x86_insn *insn, unsigned datasize, int op_n)
{
  const char *seg;

  if (insn->is_seg_override())
    seg = segment_name[insn->seg_override];
  else
    seg = sreg_mod01or10_base32[insn->rm];

  print_memory_access64(datasize, seg,
      R_ax + insn->rm, NULL, 0, (Bit32s) insn->displacement.displ32, op_n);
}

void disassembler::resolve64_mod0_rm4(const x86_insn *insn, unsigned datasize, int op_n)
{
  char vsib_index[8];
  int index = 0;
  int base = 0;
  const char *seg;
  Bit32s disp32 = 0;

  if (insn->is_seg_override())
    seg = segment_name[insn->seg_override];
  else
    seg = sreg_mod00_base32[insn->base];

  if ((insn->base & 7) != 5)
    base = R_ax + insn->base;
  else
    disp32 = (Bit32s) insn->displacement.displ32;

  if (datasize & VSIB_Index) {
    sprintf(vsib_index, "%s%d", vector_reg_name[insn->vex_l], insn->index);
    index = insn->vex_l + R_xmm0;
  }
  else {
    if (insn->index != 4)
      index = R_ax + insn->index;
  }

  print_memory_access64(datasize, seg, base, index, insn->scale, disp32, op_n);
}

void disassembler::set_dsize(int datasize, int op_n)
{
  switch(datasize)
  {
    case B_SIZE:
      cmd.Operands[op_n].dtyp = dt_byte;
     break;
    case W_SIZE:
      cmd.Operands[op_n].dtyp = dt_word;
     break;
    case D_SIZE:
      cmd.Operands[op_n].dtyp = dt_dword;
     break;
    case Q_SIZE:
      cmd.Operands[op_n].dtyp = dt_qword;
     break;
    case XMM_SIZE:
      cmd.Operands[op_n].dtyp = dt_byte16;
     break;
    case YMM_SIZE:
      cmd.Operands[op_n].dtyp = dt_ldbl;
     break;
  }
}

void disassembler::print_memory_access16(int datasize,
                const char *seg, int index, Bit16u disp, int op_n)
{
    set_dsize(datasize, op_n);
    if ( disp )
    {
      cmd.Operands[op_n].type = o_displ;      // See reg for phrase
      cmd.Operands[op_n].addr = disp;
    } else {
      cmd.Operands[op_n].type = o_phrase;      // See reg for phrase
      cmd.Operands[op_n].addr = 0;
    }
    if (index == NULL)
    {
      msg("ma16: %s:0x%x\n", seg, (unsigned) disp);
    }
    else
    {
      cmd.Operands[op_n].sib |= index << 3;
      if (disp != 0) {
        if (offset_mode_hex)
          msg("ma16: %s:[%d+0x%x]\n", seg, index, (unsigned) disp);
        else
          msg("ma16: %s:[%d+%d]\n", seg, index, (int) (Bit16s) disp);
      }
      else
        msg("ma16: %s:[%d]\n", seg, index);
    }
}

void disassembler::print_memory_access32(int datasize,
        const char *seg, int base, int index, int scale, Bit32s disp, int op_n)
{

   int m_scale = 1 << scale;
   set_dsize(datasize, op_n);
    if ( disp )
    {
      cmd.Operands[op_n].type = o_displ;      // See reg for phrase
      cmd.Operands[op_n].addr = disp;
    } else {
      cmd.Operands[op_n].type = o_phrase;      // See reg for phrase
      cmd.Operands[op_n].addr = 0;
    }
    if (base == NULL)
    {
      if (index == NULL)
      {
        msg("ma32: %s:0x%x\n", seg, (unsigned) disp);
      }
      else
      {
        cmd.Operands[op_n].hasSIB = 1;
        cmd.Operands[op_n].sib |= index << 3;
        if (m_scale != 1)
        {
          cmd.Operands[op_n].sib |= scale << 6;
          if (disp != 0) {
            if (offset_mode_hex)
              msg("ma32: %s:[%d*%d+0x%x]\n", seg, index, m_scale, (unsigned) disp);
            else
              msg("ma32: %s:[%d*%d+%d]\n", seg, index, m_scale, (int) disp);
          }
          else
            msg("ma32: %s:[%d*%d]\n", seg, index, m_scale);
        }
        else
        {
          if (disp != 0) {
            if (offset_mode_hex)
              msg("ma32: %s:[%d+0x%x]\n", seg, index, (unsigned) disp);
            else
              msg("ma32: %s:[%d+%d]\n", seg, index, (int) disp);
          }
          else {
            msg("ma32: %s:[%d]\n", seg, index);
          }
        }
      }
    }
    else
    {
      cmd.Operands[op_n].hasSIB = 1;
      cmd.Operands[op_n].sib |= base;
      if (index == NULL)
      {
        if (disp != 0) {
          if (offset_mode_hex)
            msg("ma32: %s:[%d+0x%x]", seg, base, (unsigned) disp);
          else
            msg("ma32: %s:[%d+%d]", seg, base, (int) disp);
        }
        else {
          msg("ma32: %s:[%d]", seg, base);
        }
      }
      else
      {
        cmd.Operands[op_n].sib |= index << 3;
        if (m_scale != 1)
        {
          cmd.Operands[op_n].sib |= scale << 6;
          if (disp != 0) {
            if (offset_mode_hex)
              msg("ma32: %s:[%d+%d*%d+0x%x]", seg, base, index, scale, (unsigned) disp);
            else
              msg("ma32: %s:[%d+%d*%d%+d]", seg, base, index, scale, (int) disp);
          }
          else {
            msg("ma32: %s:[%d+%d*%d]", seg, base, index, scale);
          }
        }
        else
        {
          if (disp != 0) {
            if (offset_mode_hex)
              msg("ma32: %s:[%d+%d+0x%x]", seg, base, index, (unsigned) disp);
            else
              msg("ma32: %s:[%d+%d%+d]", seg, base, index, (int) disp);
          }
          else
            msg("ma32: %s:[%d+%d]", seg, base, index);
        }
      }
    }

}

void disassembler::print_memory_access64(int datasize,
        const char *seg, int base, int index, int scale, Bit32s disp, int op_n)
{
  Bit64u disp64 = (Bit64s) disp;

  int m_scale = 1 << scale;
  set_dsize(datasize, op_n);
    if ( disp )
    {
      cmd.Operands[op_n].type = o_displ;      // See reg for phrase
      cmd.Operands[op_n].addr = disp;
    } else {
      cmd.Operands[op_n].type = o_phrase;      // See reg for phrase
      cmd.Operands[op_n].addr = 0;
    }
    if (base == NULL)
    {
      if (index == NULL)
      {
        msg("ma64: %s:0x%08x%08x\n", seg, GET32H(disp64), GET32L(disp64));
      }
      else
      {
        cmd.Operands[op_n].hasSIB = 1;
        cmd.Operands[op_n].sib |= index << 3;
        if (m_scale != 1)
        {
          cmd.Operands[op_n].sib |= scale << 6;
          if (disp != 0) {
            if (offset_mode_hex)
              msg("ma64: %s:[%d*%d+0x%08x%08x]\n", seg, index, m_scale, GET32H(disp64), GET32L(disp64));
            else
              msg("ma64: %s:[%d*%d+%d]\n", seg, index, m_scale, (int) disp);
          }
          else
            msg("ma64: %s:[%d*%d]\n", seg, index, m_scale);
        }
        else
        {
          if (disp != 0) {
            if (offset_mode_hex)
              msg("ma64: %s:[%d+0x%08x%08x]\n", seg, index, GET32H(disp64), GET32L(disp64));
            else
              msg("ma64: %s:[%d+%d]\n", seg, index, (int) disp);
          }
          else {
            msg("ma64: %s:[%d]\n", seg, index);
          }
        }
      }
    }
    else
    {
      cmd.Operands[op_n].hasSIB = 1;
      cmd.Operands[op_n].sib |= base;
      if (index == NULL)
      {
        if (disp != 0) {
          if (offset_mode_hex)
            msg("ma64: %s:[%d+0x%08x%08x]\n", seg, base, GET32H(disp64), GET32L(disp64));
          else
            msg("ma64: %s:[%d+%d]\n", seg, base, (int) disp);
        }
        else {
          msg("ma64: %s:[%d]\n", seg, base);
        }
      }
      else
      {
        cmd.Operands[op_n].sib |= index << 3;
        if (m_scale != 1)
        {
          cmd.Operands[op_n].sib |= scale << 6;
          if (disp != 0) {
            if (offset_mode_hex)
              msg("ma64: %s:[%d+%d*%d+0x%08x%08x]\n", seg, base, index, m_scale, GET32H(disp64), GET32L(disp64));
            else
              msg("ma64: %s:[%d+%d*%d+%d]\n", seg, base, index, m_scale, (int) disp);
          }
          else {
            msg("ma64: %s:[%d+%d*%d]\n", seg, base, index, m_scale);
          }
        }
        else
        {
          if (disp != 0) {
            if (offset_mode_hex)
              msg("ma64: %s:[%d+%d+0x%08x%08x]\n", seg, base, index, GET32H(disp64), GET32L(disp64));
            else
              msg("ma64: %s:[%d+%d+%d]\n", seg, base, index, (int) disp);
          }
          else
            msg("ma64: %s:[%d+%d]\n", seg, base, index);
        }
      }
    }
}

void disassembler::resolve64_mod1or2_rm4(const x86_insn *insn, unsigned datasize, int op_n)
{
  char vsib_index[8];
  int index = 0;
  const char *seg;

  if (insn->is_seg_override())
    seg = segment_name[insn->seg_override];
  else
    seg = sreg_mod01or10_base32[insn->base];

  if (datasize & VSIB_Index) {
    sprintf(vsib_index, "%s%d", vector_reg_name[insn->vex_l], insn->index);
    index = R_xmm0 + insn->index;
  }
  else {
    if (insn->index != 4)
      index = R_ax + insn->index;
  }

  print_memory_access64(datasize, seg,
      R_ax + insn->base, index, insn->scale, (Bit32s) insn->displacement.displ32, op_n);
}

x86_insn disassembler::decode(bx_bool is_32, bx_bool is_64, bx_address base, bx_address ip, const Bit8u *instr)
{
  if (is_64) is_32 = 1;
  x86_insn insn(is_32, is_64);
  const Bit8u *instruction_begin = instr;
  resolve_modrm = NULL;

  db_eip = ip;
  db_base = base; // cs linear base (base for PM & cs<<4 for RM & VM)

#define SSE_PREFIX_NONE 0
#define SSE_PREFIX_66   1
#define SSE_PREFIX_F3   2
#define SSE_PREFIX_F2   3      /* only one SSE prefix could be used */
  unsigned sse_prefix = SSE_PREFIX_NONE, sse_opcode = 0;
  unsigned rex_prefix = 0, prefixes = 0;

  for(;;)
  {
    insn.b1 = fetch_byte();
    prefixes++;

    switch(insn.b1) {
      case 0x40:     // rex
      case 0x41:
      case 0x42:
      case 0x43:
      case 0x44:
      case 0x45:
      case 0x46:
      case 0x47:
      case 0x48:
      case 0x49:
      case 0x4A:
      case 0x4B:
      case 0x4C:
      case 0x4D:
      case 0x4E:
      case 0x4F:
        if (! is_64) break;
        rex_prefix = insn.b1;
        continue;

      case 0x26:     // ES:
      case 0x2e:     // CS:
      case 0x36:     // SS:
      case 0x3e:     // DS:
        if (! is_64) insn.seg_override = (insn.b1 >> 3) & 3;
        rex_prefix = 0;
        continue;

      case 0x64:     // FS:
      case 0x65:     // GS:
        insn.seg_override = insn.b1 & 0xf;
        rex_prefix = 0;
        continue;

      case 0x66:     // operand size override
        if (!insn.os_64) insn.os_32 = !is_32;
        if (!sse_prefix) sse_prefix = SSE_PREFIX_66;
        rex_prefix = 0;
        continue;

      case 0x67:     // address size override
        if (!is_64) insn.as_32 = !is_32;
        insn.as_64 = 0;
        rex_prefix = 0;
        continue;

      case 0xf0:     // lock
        rex_prefix = 0;
        continue;

      case 0xf2:     // repne
      case 0xf3:     // rep
        sse_prefix = (insn.b1 & 0xf) ^ 1;
        rex_prefix = 0;
        continue;

      // no more prefixes
      default:
        break;
    }

    break;
  }

  if (insn.b1 == 0x0f)
  {
    insn.b1 = 0x100 | fetch_byte();
  }

  if (rex_prefix) {
    insn.extend8b = 1;
    if (rex_prefix & 0x8) {
      insn.os_64 = 1;
      insn.os_32 = 1;
    }
    if (rex_prefix & 0x4) insn.rex_r = 8;
    if (rex_prefix & 0x2) insn.rex_x = 8;
    if (rex_prefix & 0x1) insn.rex_b = 8;
  }

  const BxDisasmOpcodeTable_t *opcode_table = NULL, *entry = NULL;

  if ((insn.b1 & ~1) == 0xc4 && (is_64 || (peek_byte() & 0xc0) == 0xc0))
  {
    if (sse_prefix)
    {
      msg("%a: bad vex+rex prefix\n", ea_start);
      throw 1;
    }
    if (rex_prefix)
    {
      msg("%a: bad vex+sse prefix\n", ea_start);
      throw 2;
    }
#ifdef _DEBUG
    msg("vex\n");
#endif /* _DEBUG */
    // decode 0xC4 or 0xC5 VEX prefix
    sse_prefix = decode_vex(&insn);
    if (insn.b1 < 256 || insn.b1 >= 1024)
      throw 3;
    else
      entry = BxDisasmOpcodesAVX + (insn.b1 - 256);
  }
  else if (insn.b1 == 0x8f && (is_64 || (peek_byte() & 0xc0) == 0xc0) && (peek_byte() & 0x8) == 0x8)
  {
    if (sse_prefix)
    {
      msg("%a: bad xop+rex prefix\n", ea_start);
      throw 4;
    }
    if (rex_prefix)
    {
      msg("%a: bad xop+sse prefix\n", ea_start);
      throw 5;
    }
#ifdef _DEBUG
    msg("xop\n");
#endif /* _DEBUG */
    // decode 0x8F XOP prefix
    sse_prefix = decode_xop(&insn);
    if (insn.b1 >= 768 || sse_prefix != 0)
      entry = &BxDisasmGroupSSE_ERR[0];
    else
      entry = BxDisasmOpcodesXOP + insn.b1;
  }
  if ( entry == NULL )
  {
    msg("unknown entry\n");
    throw 7;
  }
  if (insn.b1 >= 512 || instruction_has_modrm[insn.b1] || insn.is_xop > 0)
  {
    // take 3rd byte for 3-byte opcode
    if (entry->Attr == _GRP3BOP) {
      entry = &(OPCODE_TABLE(entry)[fetch_byte()]);
    }

    decode_modrm(&insn);
  }

  int attr = entry->Attr;
#ifdef _DEBUG
  msg("attr: %d\n", attr);
#endif /* _DEBUG */ 
  while(attr)
  {
    switch(attr) {
       case _GROUPN:
         entry = &(OPCODE_TABLE(entry)[insn.nnn & 7]);
         break;

       case _GRPSSE66:
         /* SSE opcode group with only prefix 0x66 allowed */
         sse_opcode = 1;
         if (sse_prefix != SSE_PREFIX_66)
             entry = &(BxDisasmGroupSSE_ERR[sse_prefix]);
         attr = 0;
         continue;

       case _GRPSSEF2:
         /* SSE opcode group with only prefix 0xF2 allowed */
         sse_opcode = 1;
         if (sse_prefix != SSE_PREFIX_F2)
             entry = &(BxDisasmGroupSSE_ERR[sse_prefix]);
         attr = 0;
         continue;

       case _GRPSSEF3:
         /* SSE opcode group with only prefix 0xF3 allowed */
         sse_opcode = 1;
         if (sse_prefix != SSE_PREFIX_F3)
             entry = &(BxDisasmGroupSSE_ERR[sse_prefix]);
         attr = 0;
         continue;

       case _SPLIT11B:
         entry = &(OPCODE_TABLE(entry)[insn.mod != 3]); /* REG/MEM */
         break;

       case _GRPRM:
         entry = &(OPCODE_TABLE(entry)[insn.rm & 7]);
         break;

       case _GRP64B:
         entry = &(OPCODE_TABLE(entry)[insn.os_64 ? 2 : insn.os_32]);
         if (sse_prefix == SSE_PREFIX_66)
             sse_prefix = 0;
         break;

       case _GRPSSE:
         sse_opcode = 1;
         /* For SSE opcodes, look into another 4 entries table
            with the opcode prefixes (NONE, 0x66, 0xF2, 0xF3) */
         entry = &(OPCODE_TABLE(entry)[sse_prefix]);
         break;

       case _GRPVEXW:
         entry = &(OPCODE_TABLE(entry)[insn.vex_w]);
         break;

       default:
         msg("Internal disassembler error - unknown attribute %d!\n", attr);
         return x86_insn(is_32, is_64);
    }

    /* get additional attributes from group table */
    attr = entry->Attr;
  }

#define BRANCH_NOT_TAKEN 0x2E
#define BRANCH_TAKEN     0x3E

  unsigned branch_hint = 0;

  // print prefixes
  for(unsigned i=0;i<prefixes;i++)
  {
    Bit8u prefix_byte = fetch_byte_at(i);

    if (! insn.is_xop && ! insn.is_vex) {
      if (insn.b1 == 0x90 && !insn.rex_b && prefix_byte == 0xF3)
        continue;

      if (prefix_byte == 0xF3 || prefix_byte == 0xF2) {
        if (! sse_opcode) {
          const BxDisasmOpcodeTable_t *prefix = &(opcode_table[prefix_byte]);
#ifdef _DEBUG
          msg("%s ", OPCODE(prefix)->IntelOpcode);
#endif /* _DEBUG */
        }
      }

      // branch hint for jcc instructions
      if ((insn.b1 >= 0x070 && insn.b1 <= 0x07F) ||
          (insn.b1 >= 0x180 && insn.b1 <= 0x18F))
      {
        if (prefix_byte == BRANCH_NOT_TAKEN || prefix_byte == BRANCH_TAKEN)
          branch_hint = prefix_byte;
      }
    }
  }

  const BxDisasmOpcodeInfo_t *opcode = OPCODE(entry);

  if (! insn.is_xop && ! insn.is_vex) {
    // patch jecx opcode
    if (insn.b1 == 0xE3 && insn.as_32 && !insn.as_64)
      throw 1;

    // fix nop opcode
    if (insn.b1 == 0x90) {
      if (sse_prefix == SSE_PREFIX_F3)
        throw 8;
      else if (!insn.rex_b)
        throw 9;
    }
  }
  cmd.itype = opcode->avx_opcode;
#ifdef _DEBUG
  msg("itype: %d, ea %a, begin at %a\n", cmd.itype, ea, (ea_t)instruction_begin);
#endif /* _DEBUG */
  // print instruction disassembly
  print_disassembly_intel(&insn, opcode);

  if (insn.is_vex < 0)
  {
	  msg("%a: bad vex", ea_start);
	  throw 10;
  }
  insn.ilen = (unsigned)(ea - (ea_t)instruction_begin);

  return insn;
}

unsigned disassembler::decode_vex(x86_insn *insn)
{
  insn->is_vex = 1;

  unsigned b2 = fetch_byte(), vex_opcode_extension = 1;

  insn->rex_r = (b2 & 0x80) ? 0 : 0x8;

  if (insn->b1 == 0xc4) {
    // decode 3-byte VEX prefix
    insn->rex_x = (b2 & 0x40) ? 0 : 0x8;
    if (insn->is_64)
      insn->rex_b = (b2 & 0x20) ? 0 : 0x8;

    vex_opcode_extension = b2 & 0x1f;
    if (! vex_opcode_extension || vex_opcode_extension > 3)
      insn->is_vex = -1;

    b2 = fetch_byte(); // fetch VEX3 byte
    if (b2 & 0x80) {
      insn->os_64 = 1;
      insn->os_32 = 1;
      insn->vex_w = 1;
    }
  }

  insn->vex_vvv = 15 - ((b2 >> 3) & 0xf);
  insn->vex_l = (b2 >> 2) & 0x1;
  insn->b1 = fetch_byte() + 256 * vex_opcode_extension;
  return b2 & 0x3;
}

unsigned disassembler::decode_xop(x86_insn *insn)
{
  insn->is_xop = 1;

  unsigned b2 = fetch_byte(), xop_opcode_extension = 1;

  insn->rex_r = (b2 & 0x80) ? 0 : 0x8;
  insn->rex_x = (b2 & 0x40) ? 0 : 0x8;
  if (insn->is_64)
    insn->rex_b = (b2 & 0x20) ? 0 : 0x8;

  xop_opcode_extension = (b2 & 0x1f) - 8;
  if (xop_opcode_extension >= 3)
    insn->is_xop = -1;

  b2 = fetch_byte(); // fetch VEX3 byte
  if (b2 & 0x80) {
    insn->os_64 = 1;
    insn->os_32 = 1;
    insn->vex_w = 1;
  }

  insn->vex_vvv = 15 - ((b2 >> 3) & 0xf);
  insn->vex_l = (b2 >> 2) & 0x1;
  insn->b1 = fetch_byte() + 256 * xop_opcode_extension;

  return b2 & 0x3;
}

void disassembler::Ib(const x86_insn *insn, int op_n)
{
  cmd.Operands[op_n].dtyp = dt_byte;
  cmd.Operands[op_n].type = o_imm;
  cmd.Operands[op_n].offb = ea - ea_start;
  cmd.Operands[op_n].value = fetch_byte();
  cmd.Operands[op_n].flags |= OF_SHOW;
}

void disassembler::Id(const x86_insn *insn, int op_n)
{
  cmd.Operands[op_n].dtyp = dt_dword;
  cmd.Operands[op_n].type = o_imm;
  cmd.Operands[op_n].offb = ea - ea_start;
  cmd.Operands[op_n].value = fetch_dword();
  cmd.Operands[op_n].flags |= OF_SHOW;
}

void disassembler::Iq(const x86_insn *insn, int op_n)
{
  cmd.Operands[op_n].dtyp = dt_qword;
  cmd.Operands[op_n].type = o_imm;
  cmd.Operands[op_n].offb = ea - ea_start;
  cmd.Operands[op_n].value = fetch_qword();
  cmd.Operands[op_n].flags |= OF_SHOW;
}

// general purpose register
void disassembler::Gb(const x86_insn *insn, int op_n)
{
  cmd.Operands[op_n].type = o_reg;
  cmd.Operands[op_n].dtyp = dt_byte;
  cmd.Operands[op_n].reg = R_ax + insn->nnn;
}

void disassembler::Gw(const x86_insn *insn, int op_n)
{
  cmd.Operands[op_n].type = o_reg;
  cmd.Operands[op_n].dtyp = dt_word;
  cmd.Operands[op_n].reg = R_ax + insn->nnn;
}

void disassembler::Gd(const x86_insn *insn, int op_n)
{
  cmd.Operands[op_n].type = o_reg;
  cmd.Operands[op_n].dtyp = dt_dword;
  cmd.Operands[op_n].reg = R_ax + insn->nnn;
}

void disassembler::Gq(const x86_insn *insn, int op_n)
{
  cmd.Operands[op_n].type = o_reg;
  cmd.Operands[op_n].dtyp = dt_qword;
  cmd.Operands[op_n].reg = R_ax + insn->nnn;
}

void disassembler::Gy(const x86_insn *insn, int op_n)
{
  if (insn->os_64) Gq(insn, op_n);
  else Gd(insn, op_n);
}

// vex encoded general purpose register
void disassembler::By(const x86_insn *insn, int op_n)
{
  if (insn->os_64) 
  {
    cmd.Operands[op_n].type = o_reg;
    cmd.Operands[op_n].dtyp = dt_qword;
    cmd.Operands[op_n].reg = R_ax + insn->vex_vvv;
  } else {
    cmd.Operands[op_n].type = o_reg;
    cmd.Operands[op_n].dtyp = dt_dword;
    cmd.Operands[op_n].reg = R_ax + insn->vex_vvv;
  }
}

// general purpose register or memory operand
void disassembler::Eb(const x86_insn *insn, int op_n)
{
  if (insn->mod == 3) {
    Gb(insn, op_n);
  }
  else
    (this->*resolve_modrm)(insn, B_SIZE, op_n);
}

void disassembler::Ew(const x86_insn *insn, int op_n)
{
  if (insn->mod == 3)
    Gw(insn, op_n);
  else
    (this->*resolve_modrm)(insn, W_SIZE, op_n);
}

void disassembler::Ed(const x86_insn *insn, int op_n)
{
  if (insn->mod == 3)
    Gd(insn, op_n);
  else
    (this->*resolve_modrm)(insn, D_SIZE, op_n);
}

void disassembler::Eq(const x86_insn *insn, int op_n)
{
  if (insn->mod == 3)
    Gq(insn, op_n);
  else
    (this->*resolve_modrm)(insn, Q_SIZE, op_n);
}

void disassembler::Ey(const x86_insn *insn, int op_n)
{
  if (insn->os_64) Eq(insn, op_n);
  else Ed(insn, op_n);
}

void disassembler::Ebd(const x86_insn *insn, int op_n)
{
  if (insn->mod == 3)
  {
    cmd.Operands[op_n].type = o_reg;
    cmd.Operands[op_n].dtyp = dt_byte;
    cmd.Operands[op_n].reg = R_ax + insn->rm;
  }
  else
    (this->*resolve_modrm)(insn, B_SIZE, op_n);
}

void disassembler::Ewd(const x86_insn *insn, int op_n)
{
  if (insn->mod == 3)
  {
    cmd.Operands[op_n].type = o_reg;
    cmd.Operands[op_n].dtyp = dt_word;
    cmd.Operands[op_n].reg = R_ax + insn->rm;
  } else
    (this->*resolve_modrm)(insn, W_SIZE, op_n);
}

void disassembler::OP_M(const x86_insn *insn, unsigned size, int op_n)
{
  if (insn->mod == 3)
    msg("OP_M: bad mod, addr %a", ea);
  else
    (this->*resolve_modrm)(insn, size, op_n);
}

void disassembler::Ma(const x86_insn *insn, int op_n) { OP_M(insn, X_SIZE, op_n); }
void disassembler::Mp(const x86_insn *insn, int op_n) { OP_M(insn, X_SIZE, op_n); }
void disassembler::Ms(const x86_insn *insn, int op_n) { OP_M(insn, X_SIZE, op_n); }
void disassembler::Mx(const x86_insn *insn, int op_n) { OP_M(insn, X_SIZE, op_n); }

void disassembler::Mb(const x86_insn *insn, int op_n) { OP_M(insn, B_SIZE, op_n); }
void disassembler::Mw(const x86_insn *insn, int op_n) { OP_M(insn, W_SIZE, op_n); }
void disassembler::Md(const x86_insn *insn, int op_n) { OP_M(insn, D_SIZE, op_n); }
void disassembler::Mq(const x86_insn *insn, int op_n) { OP_M(insn, Q_SIZE, op_n); }
void disassembler::Mt(const x86_insn *insn, int op_n) { OP_M(insn, T_SIZE, op_n); }

void disassembler::Mdq(const x86_insn *insn, int op_n) { OP_M(insn, XMM_SIZE + insn->vex_l, op_n); }
void disassembler::Mps(const x86_insn *insn, int op_n) { OP_M(insn, XMM_SIZE + insn->vex_l, op_n); }
void disassembler::Mpd(const x86_insn *insn, int op_n) { OP_M(insn, XMM_SIZE + insn->vex_l, op_n); }
void disassembler::Mss(const x86_insn *insn, int op_n) { OP_M(insn, D_SIZE, op_n); }
void disassembler::Msd(const x86_insn *insn, int op_n) { OP_M(insn, Q_SIZE, op_n); }

// xmm/ymm register
void disassembler::Udq(const x86_insn *insn, int op_n)
{
//  msg("Udq(%d): %s%d\n", op_n, vector_reg_name[insn->vex_l], insn->rm);
  if ( !insn->vex_l )
  {
    cmd.Operands[op_n].type = o_reg;
    cmd.Operands[op_n].dtyp = dt_byte16;
    cmd.Operands[op_n].reg  = R_xmm0 + insn->rm;
  } else {
    cmd.Operands[op_n].type = o_reg;
    cmd.Operands[op_n].dtyp = dt_ldbl;
    cmd.Operands[op_n].reg  = R_xmm0 + insn->rm;
  }
}

void disassembler::Ups(const x86_insn *insn, int op_n) { Udq(insn, op_n); }
void disassembler::Upd(const x86_insn *insn, int op_n) { Udq(insn, op_n); }
void disassembler::Uq(const x86_insn *insn, int op_n) { Udq(insn, op_n); }

void disassembler::Vq(const x86_insn *insn, int op_n)
{
//   msg("Vq(%d): %s%d\n", op_n, vector_reg_name[insn->vex_l], insn->nnn);
  if ( !insn->vex_l )
  {
    cmd.Operands[op_n].type = o_reg;
    cmd.Operands[op_n].dtyp = dt_byte16;
    cmd.Operands[op_n].reg  = R_xmm0 + insn->nnn;
  } else {
    cmd.Operands[op_n].type = o_reg;
    cmd.Operands[op_n].dtyp = dt_ldbl;
    cmd.Operands[op_n].reg  = R_xmm0 + insn->nnn;
  }
}

void disassembler::Vdq(const x86_insn *insn, int op_n) { Vq(insn, op_n); }
void disassembler::Vss(const x86_insn *insn, int op_n) { Vq(insn, op_n); }
void disassembler::Vsd(const x86_insn *insn, int op_n) { Vq(insn, op_n); }
void disassembler::Vps(const x86_insn *insn, int op_n) { Vq(insn, op_n); }
void disassembler::Vpd(const x86_insn *insn, int op_n) { Vq(insn, op_n); }

void disassembler::VIb(const x86_insn *insn, int op_n)
{
  unsigned vreg = fetch_byte() >> 4;
  if (! insn->is_64) vreg &= 7;
//  msg("VIb(%d): %s%d\n", op_n, vector_reg_name[insn->vex_l], vreg);
  if ( !insn->vex_l )
  {
    cmd.Operands[op_n].type = o_reg;
    cmd.Operands[op_n].dtyp = dt_byte16;
    cmd.Operands[op_n].reg  = R_xmm0 + vreg;
    cmd.Operands[op_n].flags |= OF_SHOW;
  } else {
    cmd.Operands[op_n].type = o_reg;
    cmd.Operands[op_n].dtyp = dt_ldbl;
    cmd.Operands[op_n].reg  = R_xmm0 + vreg;
    cmd.Operands[op_n].flags |= OF_SHOW;
  }
}

// gather VSib
void disassembler::VSib(const x86_insn *insn, int op_n)
{
  if(insn->mod == 3)
    msg("VSib(%d): bad mod, addr %a\n", op_n, ea);
  else
    (this->*resolve_modrm)(insn, (XMM_SIZE + insn->vex_l) | VSIB_Index, op_n);
}

void disassembler::Hdq(const x86_insn *insn, int op_n)
{
//  msg("Hdq(%d): %s%d\n", op_n, vector_reg_name[insn->vex_l], insn->vex_vvv);
  if ( !insn->vex_l )
  {
    cmd.Operands[op_n].type = o_reg;
    cmd.Operands[op_n].dtyp = dt_byte16;
    cmd.Operands[op_n].reg  = R_xmm0 + insn->vex_vvv;
  } else {
    cmd.Operands[op_n].type = o_reg;
    cmd.Operands[op_n].dtyp = dt_ldbl;
    cmd.Operands[op_n].reg  = R_xmm0 + insn->vex_vvv;
  }
}

void disassembler::Hps(const x86_insn *insn, int op_n) { Hdq(insn, op_n); }
void disassembler::Hpd(const x86_insn *insn, int op_n) { Hdq(insn, op_n); }
void disassembler::Hss(const x86_insn *insn, int op_n) { Hdq(insn, op_n); }
void disassembler::Hsd(const x86_insn *insn, int op_n) { Hdq(insn, op_n); }

void disassembler::Wdq(const x86_insn *insn, int op_n)
{
  if (insn->mod == 3) Udq(insn, op_n);
  else
    (this->*resolve_modrm)(insn, XMM_SIZE + insn->vex_l, op_n);
}

void disassembler::Wb(const x86_insn *insn, int op_n)
{
  if (insn->mod == 3) Udq(insn, op_n);
  else
    (this->*resolve_modrm)(insn, B_SIZE, op_n);
}

void disassembler::Ww(const x86_insn *insn, int op_n)
{
  if (insn->mod == 3) Udq(insn, op_n);
  else
    (this->*resolve_modrm)(insn, W_SIZE, op_n);
}

void disassembler::Wd(const x86_insn *insn, int op_n)
{
  if (insn->mod == 3) Udq(insn, op_n);
  else
    (this->*resolve_modrm)(insn, D_SIZE, op_n);
}

void disassembler::Wq(const x86_insn *insn, int op_n)
{
  if (insn->mod == 3) Udq(insn, op_n);
  else
    (this->*resolve_modrm)(insn, Q_SIZE, op_n);
}

void disassembler::Wsd(const x86_insn *insn, int op_n) { Wq(insn, op_n); }
void disassembler::Wss(const x86_insn *insn, int op_n) { Wd(insn, op_n); }
void disassembler::Wpd(const x86_insn *insn, int op_n) { Wdq(insn, op_n); }
void disassembler::Wps(const x86_insn *insn, int op_n) { Wdq(insn, op_n); }

// Some definitions from IBM PC:

#define segrg specval_shorts.high  // IBM PC expects the segment address
                                   // to be here
#define R_cl  9
#define R_ss  18
#define R_ds  19

//----------------------------------------------------------------------
static int get_dataseg(int defseg)
{
  if ( defseg == R_ss ) cmd.auxpref |= aux_basess;
  return defseg;
}

//--------------------------------------------------------------------------
//
//              process r/m byte of the instruction
//
static void process_rm(op_t &x, uchar postbyte)
{
  int Mod = (postbyte >> 6) & 3;
  x.reg = postbyte & 7;
  if ( Mod == 3 )               // register
  {
    if ( x.dtyp == dt_byte ) x.reg += 8;
    x.type = o_reg;
  }
  else                          // memory
  {
    if ( Mod == 0 && x.reg == 6 )
    {
      x.type = o_mem;
      x.offb = uchar(ea-cmd.ea);
      x.addr = get_word(ea); ea+=2;
      x.segrg = (uint16)get_dataseg(R_ds);
    }
    else
    {
      x.type = o_phrase;      // See reg for phrase
      x.addr = 0;
      x.segrg = (uint16)get_dataseg((x.phrase == 2 || x.phrase == 3 || x.phrase == 6) ? R_ss : R_ds);
                              // [bp+si],[bp+di],[bp] by SS
      if ( Mod != 0 )
      {
        x.type = o_displ;     // i.e. phrase + offset
        x.offb = uchar(ea-cmd.ea);
        if ( Mod == 1 )
        {
          x.addr = char(get_byte(ea++));
          cmd.auxpref |= aux_short;
        }
        else
        {
          x.addr = get_word(ea); ea+=2;
        }
      }
    }
  }
}

//--------------------------------------------------------------------------
// Analyze an instruction and fill the 'cmd' structure
size_t ana(void)
{
  disassembler disa;
#ifdef _DEBUG
  msg("avx_ana called, addr: %a\n", ea);
#endif /* _DEBUG */
  try
  {
    x86_insn val = 
#ifdef __EA64__
    disa.decode64(NULL, ea, (const Bit8u *)ea);
#else
    disa.decode32(NULL, ea, (const Bit8u *)ea);
#endif
#ifdef _DEBUG
    msg("len returned: %d\n", val.ilen);
#endif /* _DEBUG */
    return val.ilen;
  } catch(int v)
  {
    msg("avx_ana: exception %d raised\n", v);
    return 0;
  }
  return 0;
}

//--------------------------------------------------------------------------
// This callback is called for IDP (processor module) notification events
// Here we extend the processor module to disassemble opcode 0x0F
// (This is a hypothetical example)
// There are 2 approaches for the extensions:
//  A. Quick & dirty
//       you implemented custom_ana and custom_out
//       The first checks if the instruction is valid
//       The second generates its text
//  B. Thourough and clean
//       you implement all callbacks
//       custom_ana fills the 'cmd' structure
//       custom_emu creates all xrefs using ua_add_[cd]ref functions
//       custom_out generates the instruction representation
//         (only if the instruction requires special processing
//          or the processor module can't handle the custom instruction for any reason)
//       custom_outop generates the operand representation (only if the operand requires special processing)
//       custom_mnem returns the instruction mnemonics (without the operands)
// The main difference between these 2 approaches is in the presence of cross-references
// and the amount of special processing required by the new instructions

// The quick & dirty approach
// We just produce the instruction mnemonics along with its operands
// No cross-references are created. No special processing.
static int idaapi dirty_extension_callback(void * /*user_data*/, int event_id, va_list va)
{
  switch ( event_id )
  {
    case processor_t::custom_ana:
      {
        ea = ea_start = cmd.ea;
        size_t length = ana();
        if ( length )
        {
          cmd.size = (uint16)length;
          return int(length+1);       // event processed
        }
      }
      break;
    case processor_t::custom_outop:
      {
        op_t *op  = va_arg(va, op_t *);
        if ( (op->type == o_reg) &&
             (op->dtyp == dt_ldbl)
           )
        {
          char buf[6];
          _snprintf(buf, sizeof(buf), "ymm%d", op->reg - R_xmm0);
          out_register(buf);
          return 2;
        }
      }
      break;
    case processor_t::custom_mnem:
      if ( (cmd.itype >= CUSTOM_CMD_ITYPE) &&
           (cmd.itype - CUSTOM_CMD_ITYPE) < _countof(opcode_map)
         )
      {
        const struct BxDisasmOpcodeInfo_t *opcode = opcode_map[cmd.itype - CUSTOM_CMD_ITYPE];
        char *buf   = va_arg(va, char *);
        size_t size = va_arg(va, size_t);
        qstrncpy(buf, opcode->IntelOpcode, size);
        return 2;
      }
      break;
  }
  return 0;                     // event is not processed
}

//--------------------------------------------------------------------------
//
//      Initialize.
//
//      IDA will call this function only once.
//      If this function returns PLUGIN_SKIP, IDA will never load it again.
//      If this function returns PLUGIN_OK, IDA will unload the plugin but
//      remember that the plugin agreed to work with the database.
//      The plugin will be loaded again if the user invokes it by
//      pressing the hotkey or selecting it from the menu.
//      After the second load the plugin will stay on memory.
//      If this function returns PLUGIN_KEEP, IDA will keep the plugin
//      in the memory. In this case the initialization function can hook
//      into the processor module and user interface notification points.
//      See the hook_to_notification_point() function.
//
//      In this example we check the processor type and make the decision.
//      You may or may not check any other conditions to decide what you do:
//      whether you agree to work with the database or not.
//

static bool hooked = false;
static netnode nec_node;
static const char node_name[] = "$ AVX/XOP plugin";

int idaapi init(void)
{
  if ( ph.id != PLFM_386 ) return PLUGIN_SKIP;
  nec_node.create(node_name);
  hooked = nec_node.altval(0);
  if ( hooked )
  {
    hook_to_notification_point(HT_IDP, dirty_extension_callback, NULL);
    msg("AVX/XOP processor extender is enabled\n");
    return PLUGIN_KEEP;
  }
  return PLUGIN_OK;
}

//--------------------------------------------------------------------------
//      Terminate.
//      Usually this callback is empty.
//      The plugin should unhook from the notification lists if
//      hook_to_notification_point() was used.
//
//      IDA will call this function when the user asks to exit.
//      This function won't be called in the case of emergency exits.

void idaapi term(void)
{
  unhook_from_notification_point(HT_IDP, dirty_extension_callback);
}

//--------------------------------------------------------------------------
//
//      The plugin method
//
//      This is the main function of plugin.
//
//      It will be called when the user selects the plugin.
//
//              arg - the input argument, it can be specified in
//                    plugins.cfg file. The default is zero.
//
//

void idaapi run(int /*arg*/)
{
  if ( hooked )
    unhook_from_notification_point(HT_IDP, dirty_extension_callback);
  else
    hook_to_notification_point(HT_IDP, dirty_extension_callback, NULL);
  hooked = !hooked;
  nec_node.create(node_name);
  nec_node.altset(0, hooked);
  info("AUTOHIDE NONE\n"
       "AVX/XOP processor extender now is %s", hooked ? "enabled" : "disabled");
}

//--------------------------------------------------------------------------
char comment[] = "AVX/XOP opcodes processor extender plugin";

//--------------------------------------------------------------------------
// This is the preferred name of the plugin module in the menu system
// The preferred name may be overriden in plugins.cfg file

char wanted_name[] = "AVX/XOP opcodes processor extender";


// This is the preferred hotkey for the plugin module
// The preferred hotkey may be overriden in plugins.cfg file
// Note: IDA won't tell you if the hotkey is not correct
//       It will just disable the hotkey.

char wanted_hotkey[] = "";


//--------------------------------------------------------------------------
//
//      PLUGIN DESCRIPTION BLOCK
//
//--------------------------------------------------------------------------
plugin_t PLUGIN =
{
  IDP_INTERFACE_VERSION,
  PLUGIN_PROC,          // plugin flags
  init,                 // initialize

  term,                 // terminate. this pointer may be NULL.

  run,                  // invoke plugin

  comment,              // long comment about the plugin
                        // it could appear in the status line
                        // or as a hint

  NULL,                 // multiline help about the plugin

  wanted_name,          // the preferred short name of the plugin
  wanted_hotkey         // the preferred hotkey to run the plugin
};
