# package for IDA perl
use strict;
use warnings;
package IDAOps;

require Exporter;
our @ISA = qw(Exporter);

use constant aux_lock        => 0x0001;
use constant aux_rep         => 0x0002;
use constant aux_repne       => 0x0004;
use constant aux_use32       => 0x0008;  # segment type is 32-bits
use constant aux_use64       => 0x0010;  # segment type is 64-bits
use constant aux_large       => 0x0020;  # offset field is 32-bit (16-bit is not enough)
use constant aux_short       => 0x0040;  # short (byte) displacement used
use constant aux_sgpref      => 0x0080;  # a segment prefix byte is not used
use constant aux_oppref      => 0x0100;  # operand size prefix byte is not used
use constant aux_adpref      => 0x0200;  # address size prefix byte is not used
use constant aux_basess      => 0x0400;  # SS based instruction
use constant aux_natop       => 0x0800;  # operand size is not overridden by prefix
use constant aux_natad       => 0x1000;  # addressing mode is not overridden by prefix
use constant aux_fpemu       => 0x2000;  # FP emulator instruction
use constant aux_vexpr       => 0x4000;  # VEX-encoded instruction
# enum RegNo
use constant R_none => -1;
use constant R_ax => 0;
use constant R_cx => 1;
use constant R_dx => 2;
use constant R_bx => 3;
use constant R_sp => 4;
use constant R_bp => 5;
use constant R_si => 6;
use constant R_di => 7;
use constant R_r8 => 8;
use constant R_r9 => 9;
use constant R_r10 => 10;
use constant R_r11 => 11;
use constant R_r12 => 12;
use constant R_r13 => 13;
use constant R_r14 => 14;
use constant R_r15 => 15;
use constant R_al => 16;
use constant R_cl => 17;
use constant R_dl => 18;
use constant R_bl => 19;
use constant R_ah => 20;
use constant R_ch => 21;
use constant R_dh => 22;
use constant R_bh => 23;
use constant R_spl => 24;
use constant R_bpl => 25;
use constant R_sil => 26;
use constant R_dil => 27;
use constant R_ip => 28;
use constant R_es => 29;    # 0
use constant R_cs => 30;    # 1
use constant R_ss => 31;    # 2
use constant R_ds => 32;    # 3
use constant R_fs => 33;
use constant R_gs => 34;
use constant R_cf => 35;    # main cc's
use constant R_zf => 36;
use constant R_sf => 37;
use constant R_of => 38;
use constant R_pf => 39;    # additional cc's
use constant R_af => 40;
use constant R_tf => 41;
use constant R_if => 42;
use constant R_df => 43;
use constant R_efl => 44;   # eflags
# the following registers will be used in the disassembly
# starting from ida v5.7
use constant R_st0 => 45;   # floating point registers (not used in disassembly)
use constant R_st1 => 46;
use constant R_st2 => 47;
use constant R_st3 => 48;
use constant R_st4 => 49;
use constant R_st5 => 50;
use constant R_st6 => 51;
use constant R_st7 => 52;
use constant R_fpctrl => 53;# fpu control register
use constant R_fpstat => 54;# fpu status register
use constant R_fptags => 55;# fpu tags register

use constant R_mm0 => 56;   # mmx registers
use constant R_mm1 => 57;
use constant R_mm2 => 58;
use constant R_mm3 => 59;
use constant R_mm4 => 60;
use constant R_mm5 => 61;
use constant R_mm6 => 62;
use constant R_mm7 => 63;

use constant R_xmm0 => 64;  # xmm registers
use constant R_xmm1 => 65;
use constant R_xmm2 => 66;
use constant R_xmm3 => 67;
use constant R_xmm4 => 68;
use constant R_xmm5 => 69;
use constant R_xmm6 => 70;
use constant R_xmm7 => 71;
use constant R_xmm8 => 72;
use constant R_xmm9 => 73;
use constant R_xmm10 => 74;
use constant R_xmm11 => 75;
use constant R_xmm12 => 76;
use constant R_xmm13 => 77;
use constant R_xmm14 => 78;
use constant R_xmm15 => 79;
use constant R_mxcsr => 80;

use constant R_ymm0  => 81; # AVX 256-bit registers
use constant R_ymm1  => 82;
use constant R_ymm2  => 83;
use constant R_ymm3  => 84;
use constant R_ymm4  => 85;
use constant R_ymm5  => 86;
use constant R_ymm6  => 87;
use constant R_ymm7  => 88;
use constant R_ymm8  => 89;
use constant R_ymm9  => 90;
use constant R_ymm10 => 91;
use constant R_ymm11 => 92;
use constant R_ymm12 => 93;
use constant R_ymm13 => 94;
use constant R_ymm14 => 95;
use constant R_ymm15 => 96;

###
#
# E X P O R T E D   N A M E S
#
###
our @EXPORT = qw(
aux_lock
aux_rep
aux_repne
aux_use32
aux_use64
aux_large
aux_short
aux_sgpref
aux_oppref
aux_adpref
aux_basess
aux_natop
aux_natad
aux_fpemu
aux_vexpr
R_none
R_ax
R_cx
R_dx
R_bx
R_sp
R_bp
R_si
R_di
R_r8
R_r9
R_r10
R_r11
R_r12
R_r13
R_r14
R_r15
R_al
R_cl
R_dl
R_bl
R_ah
R_ch
R_dh
R_bh
R_spl
R_bpl
R_sil
R_dil
R_ip
R_es
R_cs
R_ss
R_ds
R_fs
R_gs
R_cf
R_zf
R_sf
R_of
R_pf
R_af
R_tf
R_if
R_df
R_efl
R_st0
R_st1
R_st2
R_st3
R_st4
R_st5
R_st6
R_st7
R_fpctrl
R_fpstat
R_fptags
R_mm0
R_mm1
R_mm2
R_mm3
R_mm4
R_mm5
R_mm6
R_mm7
R_xmm0
R_xmm1
R_xmm2
R_xmm3
R_xmm4
R_xmm5
R_xmm6
R_xmm7
R_xmm8
R_xmm9
R_xmm10
R_xmm11
R_xmm12
R_xmm13
R_xmm14
R_xmm15
R_mxcsr
R_ymm0
R_ymm1
R_ymm2
R_ymm3
R_ymm4
R_ymm5
R_ymm6
R_ymm7
R_ymm8
R_ymm9
R_ymm10
R_ymm11
R_ymm12
R_ymm13
R_ymm14
R_ymm15
);

1;