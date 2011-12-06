/* Warning ! this file generated automatically with inst.pl
   Don`t edit it manually
 */
#include "x86.h"

/* for NULL declaration */
#include <stdlib.h>

const struct RP_opcode opcode_aaa = {
	0,
	0,
	(1 << r_EAX),
	f_AF | f_CF,
	0,
	f_OF | f_PF | f_SF | f_ZF,
	0
};

const struct RP_opcode opcode_aad = {
	0,
	0,
	(1 << r_EAX),
	f_PF | f_SF | f_ZF,
	0,
	f_AF | f_CF | f_OF,
	0
};

const struct RP_opcode opcode_and = {
	0,
	0,
	0,
	f_CF | f_OF | f_PF | f_SF | f_ZF,
	0,
	f_AF,
	1
};

const struct RP_opcode opcode_arpl = {
	0,
	0,
	0,
	f_ZF,
	0,
	0,
	1
};

const struct RP_opcode opcode_bsf = {
	0,
	0,
	0,
	f_ZF,
	0,
	f_AF | f_CF | f_OF | f_PF | f_SF,
	1
};

const struct RP_opcode opcode_bswap = {
	0,
	FROM_486,
	0,
	0,
	0,
	0,
	1
};

const struct RP_opcode opcode_bt = {
	0,
	0,
	0,
	f_CF,
	0,
	f_AF | f_OF | f_PF | f_SF | f_ZF,
	0
};

const struct RP_opcode opcode_btc = {
	0,
	0,
	0,
	f_CF,
	0,
	f_AF | f_OF | f_PF | f_SF | f_ZF,
	1
};

const struct RP_opcode opcode_call = {
	0,
	0,
	(1 << r_ESP),
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_cdq = {
	0,
	0,
	(1 << r_EAX) | (1 << r_EDX),
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_cdqe = {
	0,
	0,
	(1 << r_EAX),
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_cmova = {
	0,
	FROM_PPRO,
	0,
	0,
	f_CF | f_ZF,
	0,
	1
};

const struct RP_opcode opcode_cmovg = {
	0,
	FROM_PPRO,
	0,
	0,
	f_OF | f_SF | f_ZF,
	0,
	1
};

const struct RP_opcode opcode_cmovl = {
	0,
	FROM_PPRO,
	0,
	0,
	f_OF | f_SF,
	0,
	1
};

const struct RP_opcode opcode_cmovnb = {
	0,
	FROM_PPRO,
	0,
	0,
	f_CF,
	0,
	1
};

const struct RP_opcode opcode_cmovno = {
	0,
	FROM_PPRO,
	0,
	0,
	f_OF,
	0,
	1
};

const struct RP_opcode opcode_cmovnp = {
	0,
	FROM_PPRO,
	0,
	0,
	f_PF,
	0,
	1
};

const struct RP_opcode opcode_cmovns = {
	0,
	FROM_PPRO,
	0,
	0,
	f_SF,
	0,
	1
};

const struct RP_opcode opcode_cmovnz = {
	0,
	FROM_PPRO,
	0,
	0,
	f_ZF,
	0,
	1
};

const struct RP_opcode opcode_cmp = {
	0,
	0,
	0,
	f_AF | f_CF | f_OF | f_PF | f_SF | f_ZF,
	0,
	0,
	0
};

const struct RP_opcode opcode_cmpsb = {
	0,
	0,
	(1 << r_ESI) | (1 << r_EDI),
	f_AF | f_CF | f_OF | f_PF | f_SF | f_ZF,
	f_DF,
	0,
	0
};

const struct RP_opcode opcode_cmpunordps = {
	SSE,
	0,
	0,
	0,
	0,
	0,
	1
};

const struct RP_opcode opcode_cmpxchg = {
	0,
	FROM_486,
	(1 << r_EAX),
	f_AF | f_CF | f_OF | f_PF | f_SF | f_ZF,
	0,
	0,
	1
};

const struct RP_opcode opcode_cmpxchg16b = {
	0,
	0,
	(1 << r_RAX) | (1 << r_RDX),
	f_ZF,
	0,
	0,
	0
};

const struct RP_opcode opcode_cmpxchg8b = {
	0,
	FROM_P,
	(1 << r_EAX) | (1 << r_EDX),
	f_ZF,
	0,
	0,
	0
};

const struct RP_opcode opcode_comiss = {
	SSE,
	0,
	0,
	f_AF | f_CF | f_OF | f_PF | f_SF | f_ZF,
	0,
	0,
	0
};

const struct RP_opcode opcode_cpuid = {
	0,
	FROM_486,
	(1 << r_EAX) | (1 << r_ECX) | (1 << r_EDX) | (1 << r_EBX),
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_das = {
	0,
	0,
	(1 << r_EAX),
	f_AF | f_CF | f_PF | f_SF | f_ZF,
	0,
	f_OF,
	0
};

const struct RP_opcode opcode_dec = {
	0,
	0,
	0,
	f_AF | f_OF | f_PF | f_SF | f_ZF,
	0,
	0,
	1
};

const struct RP_opcode opcode_div = {
	0,
	0,
	(1 << r_EAX) | (1 << r_EDX),
	0,
	0,
	f_AF | f_CF | f_OF | f_PF | f_SF | f_ZF,
	0
};

const struct RP_opcode opcode_emms = {
	MMX,
	0,
	0,
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_fcmovb = {
	FPU,
	FROM_PPRO,
	0,
	0,
	f_CF,
	0,
	1
};

const struct RP_opcode opcode_fcmovbe = {
	FPU,
	FROM_PPRO,
	0,
	0,
	f_CF | f_ZF,
	0,
	1
};

const struct RP_opcode opcode_fcmove = {
	FPU,
	FROM_PPRO,
	0,
	0,
	f_ZF,
	0,
	1
};

const struct RP_opcode opcode_fcmovu = {
	FPU,
	FROM_PPRO,
	0,
	0,
	f_PF,
	0,
	1
};

const struct RP_opcode opcode_fcomip = {
	FPU,
	FROM_PPRO,
	0,
	f_CF | f_PF | f_ZF,
	0,
	0,
	0
};

const struct RP_opcode opcode_fimul = {
	FPU,
	0,
	0,
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_fstcw = {
	FPU,
	0,
	0,
	0,
	0,
	0,
	2
};

const struct RP_opcode opcode_imul = {
	0,
	0,
	0,
	f_CF | f_OF,
	0,
	f_AF | f_PF | f_SF | f_ZF,
	1
};

const struct RP_opcode opcode_jna = {
	0,
	0,
	0,
	0,
	f_CF | f_ZF,
	0,
	0
};

const struct RP_opcode opcode_jnb = {
	0,
	0,
	0,
	0,
	f_CF,
	0,
	0
};

const struct RP_opcode opcode_jne = {
	0,
	0,
	0,
	0,
	f_ZF,
	0,
	0
};

const struct RP_opcode opcode_jng = {
	0,
	0,
	0,
	0,
	f_OF | f_SF | f_ZF,
	0,
	0
};

const struct RP_opcode opcode_jnl = {
	0,
	0,
	0,
	0,
	f_OF | f_SF,
	0,
	0
};

const struct RP_opcode opcode_jno = {
	0,
	0,
	0,
	0,
	f_OF,
	0,
	0
};

const struct RP_opcode opcode_jnp = {
	0,
	0,
	0,
	0,
	f_PF,
	0,
	0
};

const struct RP_opcode opcode_jns = {
	0,
	0,
	0,
	0,
	f_SF,
	0,
	0
};

const struct RP_opcode opcode_ldmxcsr = {
	SSE,
	0,
	0,
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_lds = {
	0,
	0,
	(1 << r_DS),
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_leave = {
	0,
	0,
	(1 << r_ESP) | (1 << r_EBP),
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_les = {
	0,
	0,
	(1 << r_ES),
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_lfence = {
	0,
	FROM_P4,
	0,
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_lfs = {
	0,
	0,
	(1 << r_FS),
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_lgs = {
	0,
	0,
	(1 << r_GS),
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_loadall = {
	UNKNOWN_IT,
	0,
	0,
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_lods = {
	0,
	0,
	(1 << r_EAX) | (1 << r_ESI),
	0,
	f_DF,
	0,
	0
};

const struct RP_opcode opcode_loopd = {
	0,
	0,
	(1 << r_ECX),
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_loopde = {
	0,
	0,
	(1 << r_ECX),
	0,
	f_ZF,
	0,
	0
};

const struct RP_opcode opcode_lss = {
	0,
	0,
	(1 << r_SS),
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_monitor = {
	SSE3,
	0,
	0,
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_movs = {
	0,
	0,
	(1 << r_ESI) | (1 << r_EDI),
	0,
	f_DF,
	0,
	0
};

const struct RP_opcode opcode_mul = {
	0,
	0,
	(1 << r_EAX) | (1 << r_EDX),
	f_CF | f_OF,
	0,
	f_AF | f_PF | f_SF | f_ZF,
	0
};

const struct RP_opcode opcode_neg = {
	0,
	0,
	0,
	f_AF | f_CF | f_OF | f_PF | f_SF | f_ZF,
	0,
	0,
	1
};

const struct RP_opcode opcode_outs = {
	0,
	0,
	(1 << r_ESI),
	0,
	f_DF,
	0,
	0
};

const struct RP_opcode opcode_pfpnacc = {
	0,
	0,
	0,
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_pfsub = {
	AMD_3D,
	0,
	0,
	0,
	0,
	0,
	1
};

const struct RP_opcode opcode_phaddsw = {
	SSSE3,
	0,
	0,
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_pop = {
	0,
	0,
	(1 << r_ESP),
	0,
	0,
	0,
	1
};

const struct RP_opcode opcode_popad = {
	0,
	0,
	(1 << r_EAX) | (1 << r_ECX) | (1 << r_EDX) | (1 << r_EBX) | (1 << r_ESP) | (1 << r_EBP) | (1 << r_ESI) | (1 << r_EDI),
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_popf = {
	0,
	0,
	(1 << r_ESP),
	f_AF | f_CF | f_DF | f_IF | f_OF | f_PF | f_SF | f_ZF,
	0,
	0,
	0
};

const struct RP_opcode opcode_prefetchw = {
	AMD_3D,
	0,
	0,
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_psubusw = {
	MMX,
	0,
	0,
	0,
	0,
	0,
	1
};

const struct RP_opcode opcode_rcl = {
	0,
	0,
	0,
	f_CF,
	f_CF,
	f_OF,
	1
};

const struct RP_opcode opcode_rdpmc = {
	0,
	FROM_PPRO,
	(1 << r_EAX) | (1 << r_EDX),
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_rdtsc = {
	0,
	FROM_P,
	(1 << r_EAX) | (1 << r_EDX),
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_rol = {
	0,
	0,
	0,
	f_CF,
	0,
	f_OF,
	1
};

const struct RP_opcode opcode_rsldt = {
	UNKNOWN_IT,
	FROM_486,
	0,
	0,
	0,
	0,
	1
};

const struct RP_opcode opcode_rsm = {
	0,
	FROM_486,
	0,
	f_AF | f_CF | f_DF | f_IF | f_OF | f_SF | f_ZF,
	0,
	0,
	0
};

const struct RP_opcode opcode_sahf = {
	0,
	0,
	0,
	f_AF | f_CF | f_PF | f_SF | f_ZF,
	0,
	0,
	0
};

const struct RP_opcode opcode_sbb = {
	0,
	0,
	0,
	f_AF | f_CF | f_OF | f_PF | f_SF | f_ZF,
	f_CF,
	0,
	1
};

const struct RP_opcode opcode_scas = {
	0,
	0,
	(1 << r_EDI),
	f_AF | f_CF | f_OF | f_PF | f_SF | f_ZF,
	f_DF,
	0,
	0
};

const struct RP_opcode opcode_setae = {
	0,
	0,
	0,
	0,
	f_CF,
	0,
	1
};

const struct RP_opcode opcode_setalc = {
	UNKNOWN_IT,
	0,
	(1 << r_EAX),
	0,
	f_CF,
	0,
	0
};

const struct RP_opcode opcode_setbe = {
	0,
	0,
	0,
	0,
	f_CF | f_ZF,
	0,
	1
};

const struct RP_opcode opcode_sete = {
	0,
	0,
	0,
	0,
	f_ZF,
	0,
	1
};

const struct RP_opcode opcode_setnge = {
	0,
	0,
	0,
	0,
	f_OF | f_SF,
	0,
	1
};

const struct RP_opcode opcode_setnle = {
	0,
	0,
	0,
	0,
	f_OF | f_SF | f_ZF,
	0,
	1
};

const struct RP_opcode opcode_seto = {
	0,
	0,
	0,
	0,
	f_OF,
	0,
	1
};

const struct RP_opcode opcode_setp = {
	0,
	0,
	0,
	0,
	f_PF,
	0,
	1
};

const struct RP_opcode opcode_sets = {
	0,
	0,
	0,
	0,
	f_SF,
	0,
	1
};

const struct RP_opcode opcode_shld = {
	0,
	0,
	0,
	f_CF | f_PF | f_SF | f_ZF,
	0,
	f_AF | f_OF,
	1
};

const struct RP_opcode opcode_stc = {
	0,
	0,
	0,
	f_CF,
	0,
	0,
	0
};

const struct RP_opcode opcode_std = {
	0,
	0,
	0,
	f_DF,
	0,
	0,
	0
};

const struct RP_opcode opcode_sti = {
	0,
	0,
	0,
	f_IF,
	0,
	0,
	0
};

const struct RP_opcode opcode_stos = {
	0,
	0,
	(1 << r_EDI),
	0,
	f_DF,
	0,
	0
};

const struct RP_opcode opcode_str = {
	0,
	0,
	0,
	0,
	0,
	0,
	1
};

const struct RP_opcode opcode_sysenter = {
	0,
	FROM_PII,
	(1 << r_ESP) | (1 << r_CS) | (1 << r_SS),
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_test = {
	0,
	0,
	0,
	f_CF | f_OF | f_PF | f_SF | f_ZF,
	0,
	f_AF,
	0
};

const struct RP_opcode opcode_verr = {
	0,
	0,
	0,
	f_ZF,
	0,
	0,
	0
};

const struct RP_opcode opcode_wbinvd = {
	0,
	FROM_486,
	0,
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_wrmsr = {
	0,
	FROM_P,
	0,
	0,
	0,
	0,
	0
};

const struct RP_opcode opcode_xadd = {
	0,
	FROM_486,
	0,
	f_AF | f_CF | f_OF | f_PF | f_SF | f_ZF,
	0,
	0,
	3
};

const struct RP_opcode opcode_xchg = {
	0,
	0,
	0,
	0,
	0,
	0,
	3
};

const struct RP_opcode *const RP_data[] = {
/* 1 eq aaa */	&opcode_aaa,
/* 2 eq aad */	&opcode_aad,
/* 3 eq aam */	&opcode_aad,
/* 4 eq aas */	&opcode_aaa,
/* 5 eq adc */	&opcode_sbb,
/* 6 eq add */	&opcode_neg,
/* 7 eq and */	&opcode_and,
/* 8 eq arpl */	&opcode_arpl,
/* 9 eq bound */	&opcode_pfpnacc,
/* 10 eq bsf */	&opcode_bsf,
/* 11 eq bsr */	&opcode_bsf,
/* 12 eq bt */	&opcode_bt,
/* 13 eq btc */	&opcode_btc,
/* 14 eq btr */	&opcode_btc,
/* 15 eq bts */	&opcode_btc,
/* 16 eq call */	&opcode_call,
/* 17 eq callfi */	&opcode_call,
/* 18 eq callni */	&opcode_call,
/* 19 eq cbw */	&opcode_cdqe,
/* 20 eq cwde */	&opcode_cdqe,
/* 21 eq cdqe */	&opcode_cdqe,
/* 22 eq clc */	&opcode_stc,
/* 23 eq cld */	&opcode_std,
/* 24 eq cli */	&opcode_sti,
/* 25 eq clts */	&opcode_pfpnacc,
/* 26 eq cmc */	&opcode_stc,
/* 27 eq cmp */	&opcode_cmp,
/* 28 eq cmpsb */	&opcode_cmpsb,
/* 29 eq cwd */	&opcode_cdq,
/* 30 eq cdq */	&opcode_cdq,
/* 31 eq cqo */	&opcode_pfpnacc,
/* 32 eq daa */	&opcode_das,
/* 33 eq das */	&opcode_das,
/* 34 eq dec */	&opcode_dec,
/* 35 eq div */	&opcode_div,
/* 36 eq enterw */	&opcode_leave,
/* 37 eq enter */	&opcode_leave,
/* 38 eq enterd */	&opcode_leave,
/* 39 eq enterq */	&opcode_leave,
/* 40 eq hlt */	&opcode_pfpnacc,
/* 41 eq idiv */	&opcode_div,
/* 42 eq imul */	&opcode_imul,
/* 43 eq in */	&opcode_cdqe,
/* 44 eq inc */	&opcode_dec,
/* 45 eq ins */	&opcode_stos,
/* 46 eq int */	&opcode_call,
/* 47 eq into */	&opcode_call,
/* 48 eq int3 */	&opcode_call,
/* 49 eq iretw */	&opcode_call,
/* 50 eq iret */	&opcode_call,
/* 51 eq iretd */	&opcode_call,
/* 52 eq iretq */	&opcode_call,
/* 53 eq ja */	&opcode_jna,
/* 54 eq jae */	&opcode_jnb,
/* 55 eq jb */	&opcode_jnb,
/* 56 eq jbe */	&opcode_jna,
/* 57 eq jc */	&opcode_jnb,
/* 58 eq jcxz */	&opcode_pfpnacc,
/* 59 eq jecxz */	&opcode_pfpnacc,
/* 60 eq jrcxz */	&opcode_pfpnacc,
/* 61 eq je */	&opcode_jne,
/* 62 eq jg */	&opcode_jng,
/* 63 eq jge */	&opcode_jnl,
/* 64 eq jl */	&opcode_jnl,
/* 65 eq jle */	&opcode_jng,
/* 66 eq jna */	&opcode_jna,
/* 67 eq jnae */	&opcode_jnb,
/* 68 eq jnb */	&opcode_jnb,
/* 69 eq jnbe */	&opcode_jna,
/* 70 eq jnc */	&opcode_jnb,
/* 71 eq jne */	&opcode_jne,
/* 72 eq jng */	&opcode_jng,
/* 73 eq jnge */	&opcode_jnl,
/* 74 eq jnl */	&opcode_jnl,
/* 75 eq jnle */	&opcode_jng,
/* 76 eq jno */	&opcode_jno,
/* 77 eq jnp */	&opcode_jnp,
/* 78 eq jns */	&opcode_jns,
/* 79 eq jnz */	&opcode_jne,
/* 80 eq jo */	&opcode_jno,
/* 81 eq jp */	&opcode_jnp,
/* 82 eq jpe */	&opcode_jnp,
/* 83 eq jpo */	&opcode_jno,
/* 84 eq js */	&opcode_jns,
/* 85 eq jz */	&opcode_jne,
/* 86 eq jmp */	&opcode_pfpnacc,
/* 87 eq jmpfi */	&opcode_pfpnacc,
/* 88 eq jmpni */	&opcode_pfpnacc,
/* 89 eq jmpshort */	&opcode_pfpnacc,
/* 90 eq lahf */	&opcode_cdqe,
/* 91 eq lar */	&opcode_arpl,
/* 92 eq lea */	&opcode_str,
/* 93 eq leavew */	&opcode_leave,
/* 94 eq leave */	&opcode_leave,
/* 95 eq leaved */	&opcode_leave,
/* 96 eq leaveq */	&opcode_leave,
/* 97 eq lgdt */	&opcode_pfpnacc,
/* 98 eq lidt */	&opcode_pfpnacc,
/* 99 eq lgs */	&opcode_lgs,
/* 100 eq lss */	&opcode_lss,
/* 101 eq lds */	&opcode_lds,
/* 102 eq les */	&opcode_les,
/* 103 eq lfs */	&opcode_lfs,
/* 104 eq lldt */	&opcode_pfpnacc,
/* 105 eq lmsw */	&opcode_pfpnacc,
/* 106 eq lock */	NULL,
/* 107 eq lods */	&opcode_lods,
/* 108 eq loopw */	&opcode_loopd,
/* 109 eq loop */	&opcode_loopd,
/* 110 eq loopd */	&opcode_loopd,
/* 111 eq loopq */	&opcode_loopd,
/* 112 eq loopwe */	&opcode_loopde,
/* 113 eq loope */	&opcode_loopde,
/* 114 eq loopde */	&opcode_loopde,
/* 115 eq loopqe */	&opcode_loopde,
/* 116 eq loopwne */	&opcode_loopde,
/* 117 eq loopne */	&opcode_loopde,
/* 118 eq loopdne */	&opcode_loopde,
/* 119 eq loopqne */	&opcode_loopde,
/* 120 eq lsl */	&opcode_verr,
/* 121 eq ltr */	&opcode_pfpnacc,
/* 122 eq mov */	&opcode_str,
/* 123 eq movsp */	&opcode_str,
/* 124 eq movs */	&opcode_movs,
/* 125 eq movsx */	&opcode_str,
/* 126 eq movzx */	&opcode_str,
/* 127 eq mul */	&opcode_mul,
/* 128 eq neg */	&opcode_neg,
/* 129 eq nop */	&opcode_pfpnacc,
/* 130 eq not */	&opcode_str,
/* 131 eq or */	&opcode_and,
/* 132 eq out */	&opcode_pfpnacc,
/* 133 eq outs */	&opcode_outs,
/* 134 eq pop */	&opcode_pop,
/* 135 eq popaw */	&opcode_popad,
/* 136 eq popa */	&opcode_popad,
/* 137 eq popad */	&opcode_popad,
/* 138 eq popaq */	&opcode_call,
/* 139 eq popfw */	&opcode_popf,
/* 140 eq popf */	&opcode_popf,
/* 141 eq popfd */	&opcode_popf,
/* 142 eq popfq */	&opcode_popf,
/* 143 eq push */	&opcode_call,
/* 144 eq pushaw */	&opcode_call,
/* 145 eq pusha */	&opcode_call,
/* 146 eq pushad */	&opcode_call,
/* 147 eq pushaq */	&opcode_call,
/* 148 eq pushfw */	&opcode_call,
/* 149 eq pushf */	&opcode_call,
/* 150 eq pushfd */	&opcode_call,
/* 151 eq pushfq */	&opcode_call,
/* 152 eq rcl */	&opcode_rcl,
/* 153 eq rcr */	&opcode_rcl,
/* 154 eq rol */	&opcode_rol,
/* 155 eq ror */	&opcode_rol,
/* 156 eq rep */	&opcode_pfpnacc,
/* 157 eq repe */	&opcode_pfpnacc,
/* 158 eq repne */	&opcode_pfpnacc,
/* 159 eq ret */	&opcode_call,
/* 160 eq retf */	&opcode_call,
/* 161 eq sahf */	&opcode_sahf,
/* 162 eq sal */	&opcode_and,
/* 163 eq sar */	&opcode_and,
/* 164 eq shl */	&opcode_and,
/* 165 eq shr */	&opcode_and,
/* 166 eq sbb */	&opcode_sbb,
/* 167 eq scas */	&opcode_scas,
/* 168 eq seta */	&opcode_setbe,
/* 169 eq setae */	&opcode_setae,
/* 170 eq setb */	&opcode_setae,
/* 171 eq setbe */	&opcode_setbe,
/* 172 eq setc */	&opcode_setae,
/* 173 eq sete */	&opcode_sete,
/* 174 eq setg */	&opcode_setnle,
/* 175 eq setge */	&opcode_setnge,
/* 176 eq setl */	&opcode_setnge,
/* 177 eq setle */	&opcode_setnle,
/* 178 eq setna */	&opcode_setbe,
/* 179 eq setnae */	&opcode_setae,
/* 180 eq setnb */	&opcode_setae,
/* 181 eq setnbe */	&opcode_setbe,
/* 182 eq setnc */	&opcode_setae,
/* 183 eq setne */	&opcode_sete,
/* 184 eq setng */	&opcode_setnle,
/* 185 eq setnge */	&opcode_setnge,
/* 186 eq setnl */	&opcode_setnge,
/* 187 eq setnle */	&opcode_setnle,
/* 188 eq setno */	&opcode_seto,
/* 189 eq setnp */	&opcode_setp,
/* 190 eq setns */	&opcode_sets,
/* 191 eq setnz */	&opcode_sete,
/* 192 eq seto */	&opcode_seto,
/* 193 eq setp */	&opcode_setp,
/* 194 eq setpe */	&opcode_setp,
/* 195 eq setpo */	&opcode_setp,
/* 196 eq sets */	&opcode_sets,
/* 197 eq setz */	&opcode_sete,
/* 198 eq sgdt */	&opcode_str,
/* 199 eq sidt */	&opcode_str,
/* 200 eq shld */	&opcode_shld,
/* 201 eq shrd */	&opcode_shld,
/* 202 eq sldt */	&opcode_str,
/* 203 eq smsw */	&opcode_str,
/* 204 eq stc */	&opcode_stc,
/* 205 eq std */	&opcode_std,
/* 206 eq sti */	&opcode_sti,
/* 207 eq stos */	&opcode_stos,
/* 208 eq str */	&opcode_str,
/* 209 eq sub */	&opcode_neg,
/* 210 eq test */	&opcode_test,
/* 211 eq verr */	&opcode_verr,
/* 212 eq verw */	&opcode_verr,
/* 213 eq wait */	&opcode_pfpnacc,
/* 214 eq xchg */	&opcode_xchg,
/* 215 eq xlat */	&opcode_cdqe,
/* 216 eq xor */	&opcode_and,
/* 217 eq cmpxchg */	&opcode_cmpxchg,
/* 218 eq bswap */	&opcode_bswap,
/* 219 eq xadd */	&opcode_xadd,
/* 220 eq invd */	&opcode_wbinvd,
/* 221 eq wbinvd */	&opcode_wbinvd,
/* 222 eq invlpg */	&opcode_wbinvd,
/* 223 eq rdmsr */	&opcode_rdtsc,
/* 224 eq wrmsr */	&opcode_wrmsr,
/* 225 eq cpuid */	&opcode_cpuid,
/* 226 eq cmpxchg8b */	&opcode_cmpxchg8b,
/* 227 eq rdtsc */	&opcode_rdtsc,
/* 228 eq rsm */	&opcode_rsm,
/* 229 eq cmova */	&opcode_cmova,
/* 230 eq cmovb */	&opcode_cmovnb,
/* 231 eq cmovbe */	&opcode_cmova,
/* 232 eq cmovg */	&opcode_cmovg,
/* 233 eq cmovge */	&opcode_cmovl,
/* 234 eq cmovl */	&opcode_cmovl,
/* 235 eq cmovle */	&opcode_cmovg,
/* 236 eq cmovnb */	&opcode_cmovnb,
/* 237 eq cmovno */	&opcode_cmovno,
/* 238 eq cmovnp */	&opcode_cmovnp,
/* 239 eq cmovns */	&opcode_cmovns,
/* 240 eq cmovnz */	&opcode_cmovnz,
/* 241 eq cmovo */	&opcode_cmovno,
/* 242 eq cmovp */	&opcode_cmovnp,
/* 243 eq cmovs */	&opcode_cmovns,
/* 244 eq cmovz */	&opcode_cmovnz,
/* 245 eq fcmovb */	&opcode_fcmovb,
/* 246 eq fcmove */	&opcode_fcmove,
/* 247 eq fcmovbe */	&opcode_fcmovbe,
/* 248 eq fcmovu */	&opcode_fcmovu,
/* 249 eq fcmovnb */	&opcode_fcmovb,
/* 250 eq fcmovne */	&opcode_fcmove,
/* 251 eq fcmovnbe */	&opcode_fcmovbe,
/* 252 eq fcmovnu */	&opcode_fcmovu,
/* 253 eq fcomi */	&opcode_fcomip,
/* 254 eq fucomi */	&opcode_fcomip,
/* 255 eq fcomip */	&opcode_fcomip,
/* 256 eq fucomip */	&opcode_fcomip,
/* 257 eq rdpmc */	&opcode_rdpmc,
/* 258 eq fld */	&opcode_fimul,
/* 259 eq fst */	&opcode_fstcw,
/* 260 eq fstp */	&opcode_fstcw,
/* 261 eq fxch */	&opcode_fimul,
/* 262 eq fild */	&opcode_fimul,
/* 263 eq fist */	&opcode_fstcw,
/* 264 eq fistp */	&opcode_fstcw,
/* 265 eq fbld */	&opcode_fimul,
/* 266 eq fbstp */	&opcode_fstcw,
/* 267 eq fadd */	&opcode_fimul,
/* 268 eq faddp */	&opcode_fimul,
/* 269 eq fiadd */	&opcode_fimul,
/* 270 eq fsub */	&opcode_fimul,
/* 271 eq fsubp */	&opcode_fimul,
/* 272 eq fisub */	&opcode_fimul,
/* 273 eq fsubr */	&opcode_fimul,
/* 274 eq fsubrp */	&opcode_fimul,
/* 275 eq fisubr */	&opcode_fimul,
/* 276 eq fmul */	&opcode_fimul,
/* 277 eq fmulp */	&opcode_fimul,
/* 278 eq fimul */	&opcode_fimul,
/* 279 eq fdiv */	&opcode_fimul,
/* 280 eq fdivp */	&opcode_fimul,
/* 281 eq fidiv */	&opcode_fimul,
/* 282 eq fdivr */	&opcode_fimul,
/* 283 eq fdivrp */	&opcode_fimul,
/* 284 eq fidivr */	&opcode_fimul,
/* 285 eq fsqrt */	&opcode_fimul,
/* 286 eq fscale */	&opcode_fimul,
/* 287 eq fprem */	&opcode_fimul,
/* 288 eq frndint */	&opcode_fimul,
/* 289 eq fxtract */	&opcode_fimul,
/* 290 eq fabs */	&opcode_fimul,
/* 291 eq fchs */	&opcode_fimul,
/* 292 eq fcom */	&opcode_fimul,
/* 293 eq fcomp */	&opcode_fimul,
/* 294 eq fcompp */	&opcode_fimul,
/* 295 eq ficom */	&opcode_fimul,
/* 296 eq ficomp */	&opcode_fimul,
/* 297 eq ftst */	&opcode_fimul,
/* 298 eq fxam */	&opcode_fimul,
/* 299 eq fptan */	&opcode_fimul,
/* 300 eq fpatan */	&opcode_fimul,
/* 301 eq f2xm1 */	&opcode_fimul,
/* 302 eq fyl2x */	&opcode_fimul,
/* 303 eq fyl2xp1 */	&opcode_fimul,
/* 304 eq fldz */	&opcode_fimul,
/* 305 eq fld1 */	&opcode_fimul,
/* 306 eq fldpi */	&opcode_fimul,
/* 307 eq fldl2t */	&opcode_fimul,
/* 308 eq fldl2e */	&opcode_fimul,
/* 309 eq fldlg2 */	&opcode_fimul,
/* 310 eq fldln2 */	&opcode_fimul,
/* 311 eq finit */	&opcode_fimul,
/* 312 eq fninit */	&opcode_fimul,
/* 313 eq fsetpm */	&opcode_pfpnacc,
/* 314 eq fldcw */	&opcode_fimul,
/* 315 eq fstcw */	&opcode_fstcw,
/* 316 eq fnstcw */	&opcode_fstcw,
/* 317 eq fstsw */	&opcode_fstcw,
/* 318 eq fnstsw */	&opcode_fstcw,
/* 319 eq fclex */	&opcode_fimul,
/* 320 eq fnclex */	&opcode_fimul,
/* 321 eq fstenv */	&opcode_fstcw,
/* 322 eq fnstenv */	&opcode_fstcw,
/* 323 eq fldenv */	&opcode_fimul,
/* 324 eq fsave */	&opcode_fstcw,
/* 325 eq fnsave */	&opcode_fstcw,
/* 326 eq frstor */	&opcode_fimul,
/* 327 eq fincstp */	&opcode_fimul,
/* 328 eq fdecstp */	&opcode_fimul,
/* 329 eq ffree */	&opcode_fimul,
/* 330 eq fnop */	&opcode_fimul,
/* 331 eq feni */	&opcode_fimul,
/* 332 eq fneni */	&opcode_fimul,
/* 333 eq fdisi */	&opcode_fimul,
/* 334 eq fndisi */	&opcode_fimul,
/* 335 eq fprem1 */	&opcode_fimul,
/* 336 eq fsincos */	&opcode_fimul,
/* 337 eq fsin */	&opcode_fimul,
/* 338 eq fcos */	&opcode_fimul,
/* 339 eq fucom */	&opcode_fimul,
/* 340 eq fucomp */	&opcode_fimul,
/* 341 eq fucompp */	&opcode_fimul,
/* 342 eq setalc */	&opcode_setalc,
/* 343 eq svdc */	&opcode_rsldt,
/* 344 eq rsdc */	&opcode_rsldt,
/* 345 eq svldt */	&opcode_rsldt,
/* 346 eq rsldt */	&opcode_rsldt,
/* 347 eq svts */	&opcode_rsldt,
/* 348 eq rsts */	&opcode_rsldt,
/* 349 eq icebp */	&opcode_loadall,
/* 350 eq loadall */	&opcode_loadall,
/* 351 eq emms */	&opcode_emms,
/* 352 eq movd */	&opcode_psubusw,
/* 353 eq movq */	&opcode_psubusw,
/* 354 eq packsswb */	&opcode_psubusw,
/* 355 eq packssdw */	&opcode_psubusw,
/* 356 eq packuswb */	&opcode_psubusw,
/* 357 eq paddb */	&opcode_psubusw,
/* 358 eq paddw */	&opcode_psubusw,
/* 359 eq paddd */	&opcode_psubusw,
/* 360 eq paddsb */	&opcode_psubusw,
/* 361 eq paddsw */	&opcode_psubusw,
/* 362 eq paddusb */	&opcode_psubusw,
/* 363 eq paddusw */	&opcode_psubusw,
/* 364 eq pand */	&opcode_psubusw,
/* 365 eq pandn */	&opcode_psubusw,
/* 366 eq pcmpeqb */	&opcode_psubusw,
/* 367 eq pcmpeqw */	&opcode_psubusw,
/* 368 eq pcmpeqd */	&opcode_psubusw,
/* 369 eq pcmpgtb */	&opcode_psubusw,
/* 370 eq pcmpgtw */	&opcode_psubusw,
/* 371 eq pcmpgtd */	&opcode_psubusw,
/* 372 eq pmaddwd */	&opcode_psubusw,
/* 373 eq pmulhw */	&opcode_psubusw,
/* 374 eq pmullw */	&opcode_psubusw,
/* 375 eq por */	&opcode_psubusw,
/* 376 eq psllw */	&opcode_psubusw,
/* 377 eq pslld */	&opcode_psubusw,
/* 378 eq psllq */	&opcode_psubusw,
/* 379 eq psraw */	&opcode_psubusw,
/* 380 eq psrad */	&opcode_psubusw,
/* 381 eq psrlw */	&opcode_psubusw,
/* 382 eq psrld */	&opcode_psubusw,
/* 383 eq psrlq */	&opcode_psubusw,
/* 384 eq psubb */	&opcode_psubusw,
/* 385 eq psubw */	&opcode_psubusw,
/* 386 eq psubd */	&opcode_psubusw,
/* 387 eq psubsb */	&opcode_psubusw,
/* 388 eq psubsw */	&opcode_psubusw,
/* 389 eq psubusb */	&opcode_psubusw,
/* 390 eq psubusw */	&opcode_psubusw,
/* 391 eq punpckhbw */	&opcode_psubusw,
/* 392 eq punpckhwd */	&opcode_psubusw,
/* 393 eq punpckhdq */	&opcode_psubusw,
/* 394 eq punpcklbw */	&opcode_psubusw,
/* 395 eq punpcklwd */	&opcode_psubusw,
/* 396 eq punpckldq */	&opcode_psubusw,
/* 397 eq pxor */	&opcode_psubusw,
/* 398 eq fxsave */	&opcode_cmpunordps,
/* 399 eq fxrstor */	&opcode_ldmxcsr,
/* 400 eq sysenter */	&opcode_sysenter,
/* 401 eq sysexit */	&opcode_sysenter,
/* 402 eq pavgusb */	&opcode_pfsub,
/* 403 eq pfadd */	&opcode_pfsub,
/* 404 eq pfsub */	&opcode_pfsub,
/* 405 eq pfsubr */	&opcode_pfsub,
/* 406 eq pfacc */	&opcode_pfsub,
/* 407 eq pfcmpge */	&opcode_pfsub,
/* 408 eq pfcmpgt */	&opcode_pfsub,
/* 409 eq pfcmpeq */	&opcode_pfsub,
/* 410 eq pfmin */	&opcode_pfsub,
/* 411 eq pfmax */	&opcode_pfsub,
/* 412 eq pi2fd */	&opcode_pfsub,
/* 413 eq pf2id */	&opcode_pfsub,
/* 414 eq pfrcp */	&opcode_pfsub,
/* 415 eq pfrsqrt */	&opcode_pfsub,
/* 416 eq pfmul */	&opcode_pfsub,
/* 417 eq pfrcpit1 */	&opcode_pfsub,
/* 418 eq pfrsqit1 */	&opcode_pfsub,
/* 419 eq pfrcpit2 */	&opcode_pfsub,
/* 420 eq pmulhrw */	&opcode_pfsub,
/* 421 eq femms */	&opcode_prefetchw,
/* 422 eq prefetch */	&opcode_prefetchw,
/* 423 eq prefetchw */	&opcode_prefetchw,
/* 424 eq addps */	&opcode_cmpunordps,
/* 425 eq addss */	&opcode_cmpunordps,
/* 426 eq andnps */	&opcode_cmpunordps,
/* 427 eq andps */	&opcode_cmpunordps,
/* 428 eq cmpps */	&opcode_cmpunordps,
/* 429 eq cmpss */	&opcode_cmpunordps,
/* 430 eq comiss */	&opcode_comiss,
/* 431 eq cvtpi2ps */	&opcode_cmpunordps,
/* 432 eq cvtps2pi */	&opcode_cmpunordps,
/* 433 eq cvtsi2ss */	&opcode_cmpunordps,
/* 434 eq cvtss2si */	&opcode_cmpunordps,
/* 435 eq cvttps2pi */	&opcode_cmpunordps,
/* 436 eq cvttss2si */	&opcode_cmpunordps,
/* 437 eq divps */	&opcode_cmpunordps,
/* 438 eq divss */	&opcode_cmpunordps,
/* 439 eq ldmxcsr */	&opcode_ldmxcsr,
/* 440 eq maxps */	&opcode_cmpunordps,
/* 441 eq maxss */	&opcode_cmpunordps,
/* 442 eq minps */	&opcode_cmpunordps,
/* 443 eq minss */	&opcode_cmpunordps,
/* 444 eq movaps */	&opcode_cmpunordps,
/* 445 eq movhlps */	&opcode_cmpunordps,
/* 446 eq movhps */	&opcode_cmpunordps,
/* 447 eq movlhps */	&opcode_cmpunordps,
/* 448 eq movlps */	&opcode_cmpunordps,
/* 449 eq movmskps */	&opcode_cmpunordps,
/* 450 eq movss */	&opcode_cmpunordps,
/* 451 eq movups */	&opcode_cmpunordps,
/* 452 eq mulps */	&opcode_cmpunordps,
/* 453 eq mulss */	&opcode_cmpunordps,
/* 454 eq orps */	&opcode_cmpunordps,
/* 455 eq rcpps */	&opcode_cmpunordps,
/* 456 eq rcpss */	&opcode_cmpunordps,
/* 457 eq rsqrtps */	&opcode_cmpunordps,
/* 458 eq rsqrtss */	&opcode_cmpunordps,
/* 459 eq shufps */	&opcode_cmpunordps,
/* 460 eq sqrtps */	&opcode_cmpunordps,
/* 461 eq sqrtss */	&opcode_cmpunordps,
/* 462 eq stmxcsr */	&opcode_cmpunordps,
/* 463 eq subps */	&opcode_cmpunordps,
/* 464 eq subss */	&opcode_cmpunordps,
/* 465 eq ucomiss */	&opcode_comiss,
/* 466 eq unpckhps */	&opcode_cmpunordps,
/* 467 eq unpcklps */	&opcode_cmpunordps,
/* 468 eq xorps */	&opcode_cmpunordps,
/* 469 eq pavgb */	&opcode_psubusw,
/* 470 eq pavgw */	&opcode_psubusw,
/* 471 eq pextrw */	&opcode_psubusw,
/* 472 eq pinsrw */	&opcode_psubusw,
/* 473 eq pmaxsw */	&opcode_psubusw,
/* 474 eq pmaxub */	&opcode_psubusw,
/* 475 eq pminsw */	&opcode_psubusw,
/* 476 eq pminub */	&opcode_psubusw,
/* 477 eq pmovmskb */	&opcode_psubusw,
/* 478 eq pmulhuw */	&opcode_psubusw,
/* 479 eq psadbw */	&opcode_psubusw,
/* 480 eq pshufw */	&opcode_psubusw,
/* 481 eq maskmovq */	&opcode_emms,
/* 482 eq movntps */	&opcode_cmpunordps,
/* 483 eq movntq */	&opcode_cmpunordps,
/* 484 eq prefetcht0 */	&opcode_ldmxcsr,
/* 485 eq prefetcht1 */	&opcode_ldmxcsr,
/* 486 eq prefetcht2 */	&opcode_ldmxcsr,
/* 487 eq prefetchnta */	&opcode_ldmxcsr,
/* 488 eq sfence */	&opcode_ldmxcsr,
/* 489 eq cmpeqps */	&opcode_cmpunordps,
/* 490 eq cmpltps */	&opcode_cmpunordps,
/* 491 eq cmpleps */	&opcode_cmpunordps,
/* 492 eq cmpunordps */	&opcode_cmpunordps,
/* 493 eq cmpneqps */	&opcode_cmpunordps,
/* 494 eq cmpnltps */	&opcode_cmpunordps,
/* 495 eq cmpnleps */	&opcode_cmpunordps,
/* 496 eq cmpordps */	&opcode_cmpunordps,
/* 497 eq cmpeqss */	&opcode_cmpunordps,
/* 498 eq cmpltss */	&opcode_cmpunordps,
/* 499 eq cmpless */	&opcode_cmpunordps,
/* 500 eq cmpunordss */	&opcode_cmpunordps,
/* 501 eq cmpneqss */	&opcode_cmpunordps,
/* 502 eq cmpnltss */	&opcode_cmpunordps,
/* 503 eq cmpnless */	&opcode_cmpunordps,
/* 504 eq cmpordss */	&opcode_cmpunordps,
/* 505 eq pf2iw */	&opcode_pfpnacc,
/* 506 eq pfnacc */	&opcode_pfpnacc,
/* 507 eq pfpnacc */	&opcode_pfpnacc,
/* 508 eq pi2fw */	&opcode_pfpnacc,
/* 509 eq pswapd */	&opcode_pfpnacc,
/* 510 eq fstp1 */	&opcode_fimul,
/* 511 eq fcom2 */	&opcode_fimul,
/* 512 eq fcomp3 */	&opcode_fimul,
/* 513 eq fxch4 */	&opcode_fimul,
/* 514 eq fcomp5 */	&opcode_fimul,
/* 515 eq ffreep */	&opcode_fimul,
/* 516 eq fxch7 */	&opcode_fimul,
/* 517 eq fstp8 */	&opcode_fimul,
/* 518 eq fstp9 */	&opcode_fimul,
/* 519 eq addpd */	&opcode_lfence,
/* 520 eq addsd */	&opcode_lfence,
/* 521 eq andnpd */	&opcode_lfence,
/* 522 eq andpd */	&opcode_lfence,
/* 523 eq clflush */	&opcode_lfence,
/* 524 eq cmppd */	&opcode_lfence,
/* 525 eq cmpsd */	&opcode_lfence,
/* 526 eq comisd */	&opcode_lfence,
/* 527 eq cvtdq2pd */	&opcode_lfence,
/* 528 eq cvtdq2ps */	&opcode_lfence,
/* 529 eq cvtpd2dq */	&opcode_lfence,
/* 530 eq cvtpd2pi */	&opcode_lfence,
/* 531 eq cvtpd2ps */	&opcode_lfence,
/* 532 eq cvtpi2pd */	&opcode_lfence,
/* 533 eq cvtps2dq */	&opcode_lfence,
/* 534 eq cvtps2pd */	&opcode_lfence,
/* 535 eq cvtsd2si */	&opcode_lfence,
/* 536 eq cvtsd2ss */	&opcode_lfence,
/* 537 eq cvtsi2sd */	&opcode_lfence,
/* 538 eq cvtss2sd */	&opcode_lfence,
/* 539 eq cvttpd2dq */	&opcode_lfence,
/* 540 eq cvttpd2pi */	&opcode_lfence,
/* 541 eq cvttps2dq */	&opcode_lfence,
/* 542 eq cvttsd2si */	&opcode_lfence,
/* 543 eq divpd */	&opcode_lfence,
/* 544 eq divsd */	&opcode_lfence,
/* 545 eq lfence */	&opcode_lfence,
/* 546 eq maskmovdqu */	&opcode_lfence,
/* 547 eq maxpd */	&opcode_lfence,
/* 548 eq maxsd */	&opcode_lfence,
/* 549 eq mfence */	&opcode_lfence,
/* 550 eq minpd */	&opcode_lfence,
/* 551 eq minsd */	&opcode_lfence,
/* 552 eq movapd */	&opcode_lfence,
/* 553 eq movdq2q */	&opcode_lfence,
/* 554 eq movdqa */	&opcode_lfence,
/* 555 eq movdqu */	&opcode_lfence,
/* 556 eq movhpd */	&opcode_lfence,
/* 557 eq movlpd */	&opcode_lfence,
/* 558 eq movmskpd */	&opcode_lfence,
/* 559 eq movntdq */	&opcode_lfence,
/* 560 eq movnti */	&opcode_lfence,
/* 561 eq movntpd */	&opcode_lfence,
/* 562 eq movq2dq */	&opcode_lfence,
/* 563 eq movsd */	&opcode_lfence,
/* 564 eq movupd */	&opcode_lfence,
/* 565 eq mulpd */	&opcode_lfence,
/* 566 eq mulsd */	&opcode_lfence,
/* 567 eq orpd */	&opcode_lfence,
/* 568 eq paddq */	&opcode_lfence,
/* 569 eq pause */	&opcode_lfence,
/* 570 eq pmuludq */	&opcode_lfence,
/* 571 eq pshufd */	&opcode_lfence,
/* 572 eq pshufhw */	&opcode_lfence,
/* 573 eq pshuflw */	&opcode_lfence,
/* 574 eq pslldq */	&opcode_lfence,
/* 575 eq psrldq */	&opcode_lfence,
/* 576 eq psubq */	&opcode_lfence,
/* 577 eq punpckhqdq */	&opcode_lfence,
/* 578 eq punpcklqdq */	&opcode_lfence,
/* 579 eq shufpd */	&opcode_lfence,
/* 580 eq sqrtpd */	&opcode_lfence,
/* 581 eq sqrtsd */	&opcode_lfence,
/* 582 eq subpd */	&opcode_lfence,
/* 583 eq subsd */	&opcode_lfence,
/* 584 eq ucomisd */	&opcode_lfence,
/* 585 eq unpckhpd */	&opcode_lfence,
/* 586 eq unpcklpd */	&opcode_lfence,
/* 587 eq xorpd */	&opcode_lfence,
/* 588 eq syscall */	&opcode_pfpnacc,
/* 589 eq sysret */	&opcode_pfpnacc,
/* 590 eq swapgs */	&opcode_pfpnacc,
/* 591 eq movddup */	&opcode_monitor,
/* 592 eq movshdup */	&opcode_ldmxcsr,
/* 593 eq movsldup */	&opcode_ldmxcsr,
/* 594 eq movsxd */	&opcode_str,
/* 595 eq cmpxchg16b */	&opcode_cmpxchg16b,
/* 596 eq addsubpd */	&opcode_monitor,
/* 597 eq addsubps */	&opcode_monitor,
/* 598 eq haddpd */	&opcode_monitor,
/* 599 eq haddps */	&opcode_monitor,
/* 600 eq hsubpd */	&opcode_monitor,
/* 601 eq hsubps */	&opcode_monitor,
/* 602 eq monitor */	&opcode_monitor,
/* 603 eq mwait */	&opcode_monitor,
/* 604 eq fisttp */	&opcode_monitor,
/* 605 eq lddqu */	&opcode_monitor,
/* 606 eq psignb */	&opcode_phaddsw,
/* 607 eq psignw */	&opcode_phaddsw,
/* 608 eq psignd */	&opcode_phaddsw,
/* 609 eq pshufb */	&opcode_phaddsw,
/* 610 eq pmulhrsw */	&opcode_phaddsw,
/* 611 eq pmaddubsw */	&opcode_phaddsw,
/* 612 eq phsubsw */	&opcode_phaddsw,
/* 613 eq phaddsw */	&opcode_phaddsw,
/* 614 eq phaddw */	&opcode_phaddsw,
/* 615 eq phaddd */	&opcode_phaddsw,
/* 616 eq phsubw */	&opcode_phaddsw,
/* 617 eq phsubd */	&opcode_phaddsw,
/* 618 eq palignr */	&opcode_phaddsw,
/* 619 eq pabsb */	&opcode_phaddsw,
/* 620 eq pabsw */	&opcode_phaddsw,
/* 621 eq pabsd */	&opcode_phaddsw,
/* 622 eq vmcall */	NULL,
/* 623 eq vmclear */	NULL,
/* 624 eq vmlaunch */	NULL,
/* 625 eq vmresume */	NULL,
/* 626 eq vmptrld */	NULL,
/* 627 eq vmptrst */	NULL,
/* 628 eq vmread */	NULL,
/* 629 eq vmwrite */	NULL,
/* 630 eq vmxoff */	NULL,
/* 631 eq vmxon */	NULL,
/* 632 eq ud2 */	NULL,
/* 633 eq rdtscp */	NULL,
/* 634 eq pfrcpv */	NULL,
/* 635 eq pfrsqrtv */	NULL,
/* 636 eq cmpeqpd */	NULL,
/* 637 eq cmpltpd */	NULL,
/* 638 eq cmplepd */	NULL,
/* 639 eq cmpunordpd */	NULL,
/* 640 eq cmpneqpd */	NULL,
/* 641 eq cmpnltpd */	NULL,
/* 642 eq cmpnlepd */	NULL,
/* 643 eq cmpordpd */	NULL,
/* 644 eq cmpeqsd */	NULL,
/* 645 eq cmpltsd */	NULL,
/* 646 eq cmplesd */	NULL,
/* 647 eq cmpunordsd */	NULL,
/* 648 eq cmpneqsd */	NULL,
/* 649 eq cmpnltsd */	NULL,
/* 650 eq cmpnlesd */	NULL,
/* 651 eq cmpordsd */	NULL,
/* 652 eq blendpd */	NULL,
/* 653 eq blendps */	NULL,
/* 654 eq blendvpd */	NULL,
/* 655 eq blendvps */	NULL,
/* 656 eq dppd */	NULL,
/* 657 eq dpps */	NULL,
/* 658 eq extractps */	NULL,
/* 659 eq insertps */	NULL,
/* 660 eq movntdqa */	NULL,
/* 661 eq mpsadbw */	NULL,
/* 662 eq packusdw */	NULL,
/* 663 eq pblendvb */	NULL,
/* 664 eq pblendw */	NULL,
/* 665 eq pcmpeqq */	NULL,
/* 666 eq pextrb */	NULL,
/* 667 eq pextrd */	NULL,
/* 668 eq pextrq */	NULL,
/* 669 eq phminposuw */	NULL,
/* 670 eq pinsrb */	NULL,
/* 671 eq pinsrd */	NULL,
/* 672 eq pinsrq */	NULL,
/* 673 eq pmaxsb */	NULL,
/* 674 eq pmaxsd */	NULL,
/* 675 eq pmaxud */	NULL,
/* 676 eq pmaxuw */	NULL,
/* 677 eq pminsb */	NULL,
/* 678 eq pminsd */	NULL,
/* 679 eq pminud */	NULL,
/* 680 eq pminuw */	NULL,
/* 681 eq pmovsxbw */	NULL,
/* 682 eq pmovsxbd */	NULL,
/* 683 eq pmovsxbq */	NULL,
/* 684 eq pmovsxwd */	NULL,
/* 685 eq pmovsxwq */	NULL,
/* 686 eq pmovsxdq */	NULL,
/* 687 eq pmovzxbw */	NULL,
/* 688 eq pmovzxbd */	NULL,
/* 689 eq pmovzxbq */	NULL,
/* 690 eq pmovzxwd */	NULL,
/* 691 eq pmovzxwq */	NULL,
/* 692 eq pmovzxdq */	NULL,
/* 693 eq pmuldq */	NULL,
/* 694 eq pmulld */	NULL,
/* 695 eq ptest */	NULL,
/* 696 eq roundpd */	NULL,
/* 697 eq roundps */	NULL,
/* 698 eq roundsd */	NULL,
/* 699 eq roundss */	NULL,
/* 700 eq crc32 */	NULL,
/* 701 eq pcmpestri */	NULL,
/* 702 eq pcmpestrm */	NULL,
/* 703 eq pcmpistri */	NULL,
/* 704 eq pcmpistrm */	NULL,
/* 705 eq pcmpgtq */	NULL,
/* 706 eq popcnt */	NULL,
/* 707 eq extrq */	NULL,
/* 708 eq insertq */	NULL,
/* 709 eq movntsd */	NULL,
/* 710 eq movntss */	NULL,
/* 711 eq lzcnt */	NULL,
/* 712 eq xgetbv */	NULL,
/* 713 eq xrstor */	NULL,
/* 714 eq xsave */	NULL,
/* 715 eq xsetbv */	NULL,
/* 716 eq getsec */	NULL,
/* 717 eq clgi */	NULL,
/* 718 eq invlpga */	NULL,
/* 719 eq skinit */	NULL,
/* 720 eq stgi */	NULL,
/* 721 eq vmexit */	NULL,
/* 722 eq vmload */	NULL,
/* 723 eq vmmcall */	NULL,
/* 724 eq vmrun */	NULL,
/* 725 eq vmsave */	NULL,
/* 726 eq invept */	NULL,
/* 727 eq invvpid */	NULL,
/* 728 eq movbe */	NULL,
/* 729 eq aesenc */	NULL,
/* 730 eq aesenclast */	NULL,
/* 731 eq aesdec */	NULL,
/* 732 eq aesdeclast */	NULL,
/* 733 eq aesimc */	NULL,
/* 734 eq aeskeygenassist */	NULL,
/* 735 eq pclmulqdq */	NULL };
