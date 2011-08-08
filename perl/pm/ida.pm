package IDA;
require Exporter;
@ISA = qw(Exporter);
package IDA;
boot_IDA();
package IDA;

###
#
# C O N S T A N T S
#
###
use constant BADADDR => 0xFFFFFFFF;
use constant MAXADDR => 0xFF000000;

use constant MS_CLS  => 0x00000600;             # Mask for typing
use constant FF_CODE => 0x00000600;             # Code ?
use constant FF_DATA => 0x00000400;             # Data ?
use constant FF_TAIL => 0x00000200;             # Tail ?
use constant FF_UNK  => 0x00000000;             # Unknown ?

use constant MS_COMM => 0x000FF800;             # Mask of common bits
use constant FF_COMM => 0x00000800;             # Has comment?
use constant FF_REF  => 0x00001000;             # has references?
use constant FF_LINE => 0x00002000;             # Has next or prev cmt lines ?
use constant FF_NAME => 0x00004000;             # Has user-defined name ?
use constant FF_LABL => 0x00008000;             # Has dummy name?
use constant FF_FLOW => 0x00010000;             # Exec flow from prev instruction?
use constant FF_VAR  => 0x00080000;             # Is byte variable ?

use constant MS_0TYPE => 0x00F00000;            # Mask for 1st arg typing
use constant FF_0VOID => 0x00000000;            # Void (unknown)?
use constant FF_0NUMH => 0x00100000;            # Hexadecimal number?
use constant FF_0NUMD => 0x00200000;            # Decimal number?
use constant FF_0CHAR => 0x00300000;            # Char ('x')?
use constant FF_0SEG  => 0x00400000;            # Segment?
use constant FF_0OFF  => 0x00500000;            # Offset?
use constant FF_0NUMB => 0x00600000;            # Binary number?
use constant FF_0NUMO => 0x00700000;            # Octal number?
use constant FF_0ENUM => 0x00800000;            # Enumeration?
use constant FF_0FOP  => 0x00900000;            # Forced operand?
use constant FF_0STRO => 0x00A00000;            # Struct offset?
use constant FF_0STK  => 0x00B00000;            # Stack variable?
use constant FF_0FLT  => 0x00C00000;		# Floating point number?
use constant FF_0CUST => 0x00D00000;            # Custom format type?

use constant MS_1TYPE => 0x0F000000;            # Mask for 2nd arg typing
use constant FF_1VOID => 0x00000000;            # Void (unknown)?
use constant FF_1NUMH => 0x01000000;            # Hexadecimal number?
use constant FF_1NUMD => 0x02000000;            # Decimal number?
use constant FF_1CHAR => 0x03000000;            # Char ('x')?
use constant FF_1SEG  => 0x04000000;            # Segment?
use constant FF_1OFF  => 0x05000000;            # Offset?
use constant FF_1NUMB => 0x06000000;            # Binary number?
use constant FF_1NUMO => 0x07000000;            # Octal number?
use constant FF_1ENUM => 0x08000000;            # Enumeration?
use constant FF_1FOP  => 0x09000000;            # Forced operand?
use constant FF_1STRO => 0x0A000000;            # Struct offset?
use constant FF_1STK  => 0x0B000000;            # Stack variable?
use constant FF_1FLT  => 0x0C000000;            # Floating point number?
use constant FF_1CUST => 0x0D000000;            # Custom format type?

use constant DT_TYPE => 0xF0000000;             # Mask for DATA typing

use constant FF_BYTE => 0x00000000;             # byte
use constant FF_WORD => 0x10000000;             # word
use constant FF_DWRD => 0x20000000;             # dword
use constant FF_QWRD => 0x30000000;             # qword
use constant FF_TBYT => 0x40000000;             # tbyte
use constant FF_ASCI => 0x50000000;             # ASCII ?
use constant FF_STRU => 0x60000000;             # Struct ?
use constant FF_OWRD => 0x70000000;             # octaword (16 bytes)
use constant FF_FLOAT => 0x80000000;            # float
use constant FF_DOUBLE => 0x90000000;           # double
use constant FF_PACKREAL => 0xA0000000;         # packed decimal real
use constant FF_ALIGN    => 0xB0000000;         # alignment directive
use constant FF_3BYTE  =>  0xC0000000;          # 3-byte data
use constant FF_CUSTOM =>  0xD0000000;          # custom data type

use constant MS_CODE => 0xF0000000;
use constant FF_FUNC => 0x10000000;             # function start?
use constant FF_IMMD => 0x40000000;             # Has Immediate value ?
use constant FF_JUMP => 0x80000000;             # Has jump table

#
# loader flags
#
use constant NEF_SEGS   => 0x0001;               # Create segments
use constant NEF_RSCS   => 0x0002;               # Load resources
use constant NEF_NAME   => 0x0004;               # Rename entries
use constant NEF_MAN    => 0x0008;               # Manual load
use constant NEF_FILL   => 0x0010;               # Fill segment gaps
use constant NEF_IMPS   => 0x0020;               # Create imports section
use constant NEF_TIGHT  => 0x0040;               # Don't align segments (OMF)
use constant NEF_FIRST  => 0x0080;               # This is the first file loaded
use constant NEF_CODE   => 0x0100;               # for load_binary_file:
use constant NEF_RELOAD => 0x0200;               # reload the file at the same place:
use constant NEF_FLAT   => 0x0400;               # Autocreated FLAT group (PE)
use constant NEF_MINI   => 0x0800;               # Create mini database (do not copy
                                                 # segment bytes from the input file;
use constant NEF_LOPT   => 0x1000;               # Display additional loader options dialog
use constant NEF_LALL   => 0x2000;               # Load all segments without questions

# Names constants
use constant SN_CHECK      => 0x01;   # Fail if the name contains invalid characters
                                      #  If this bit is clear, all invalid chars
                                      # (those !is_ident_char()) will be replaced
                                      # by SubstChar (usually '_')
                                      # List of valid characters is defined in ida.cfg
use constant SN_NOCHECK    => 0x00;   # Replace invalid chars with SubstChar
use constant SN_PUBLIC     => 0x02;   # if set, make name public
use constant SN_NON_PUBLIC => 0x04;   # if set, make name non-public
use constant SN_WEAK       => 0x08;   # if set, make name weak
use constant SN_NON_WEAK   => 0x10;   # if set, make name non-weak
use constant SN_AUTO       => 0x20;   # if set, make name autogenerated
use constant SN_NON_AUTO   => 0x40;   # if set, make name non-autogenerated
use constant SN_NOLIST     => 0x80;   # if set, exclude name from the list
                                      # if not set, then include the name into
                                      # the list (however, if other bits are set,
                                      # the name might be immediately excluded
                                      # from the list)
use constant SN_NOWARN     => 0x100;  # don't display a warning if failed
use constant SN_LOCAL      => 0x200;  # create local name. a function should exist.
                                      # local names can't be public or weak.
                                      # also they are not included into the list of names
                                      # they can't have dummy prefixes

#
# for GetFunctionAttr
#
use constant FUNCATTR_START   => 0;	# function start address
use constant FUNCATTR_END     => 4;     # function end address
use constant FUNCATTR_FLAGS   => 8;     # function flags
use constant FUNCATTR_FRAME   => 10;    # function frame id
use constant FUNCATTR_FRSIZE  => 14;    # size of local variables
use constant FUNCATTR_FRREGS  => 18;    # size of saved registers area
use constant FUNCATTR_ARGSIZE => 20;    # number of bytes purged from the stack
use constant FUNCATTR_FPD     => 24;    # frame pointer delta
use constant FUNCATTR_COLOR   => 28;    # function color code

#
# for AddHotKey
#
use constant IDCHK_OK => 0;
use constant IDCHK_ARG => -1;
use constant IDCHK_KEY => -2;
use constant IDCHK_MAX => -3;

#
# for SetSegnemtType
#
use constant SEG_NORM => 0;
use constant SEG_XTRN => 1;
use constant SEG_CODE => 2;
use constant SEG_DATA => 3;
use constant SEG_IMP => 4;
use constant SEG_GRP => 6;
use constant SEG_NULL => 7;
use constant SEG_UNDF => 8;
use constant SEG_BSS => 9;
use constant SEG_ABSSYM => 10;
use constant SEG_COMM => 11;
use constant SEG_IMEM => 12;       # internal processor memory & sfr (8051)

#
# for GetSegmentAttr
#
use constant SEGATTR_START  =>  0;      # starting address
use constant SEGATTR_END    =>  4;      # ending address
use constant SEGATTR_ORGBASE => 16;
use constant SEGATTR_ALIGN  => 20;      # alignment
use constant SEGATTR_COMB   => 21;      # combination
use constant SEGATTR_PERM   => 22;      # permissions
use constant SEGATTR_USE32  => 23;      # use32 (32-bit segment?)
use constant SEGATTR_FLAGS  => 24;      # segment flags
use constant SEGATTR_SEL    => 26;      # segment selector
use constant SEGATTR_DEF_ES => 30;      # default ES value
use constant SEGATTR_DEF_CS => 34;      # default CS value
use constant SEGATTR_DEF_SS => 38;      # default SS value
use constant SEGATTR_DEF_DS => 42;      # default DS value
use constant SEGATTR_DEF_FS => 46;      # default FS value
use constant SEGATTR_DEF_GS => 50;      # default GS value
use constant SEGATTR_TYPE   => 94;      # segment type
use constant SEGATTR_COLOR  => 95;      # segment color

#
# for GenerateFile
#
use constant OFILE_MAP => 0;
use constant OFILE_EXE => 1;
use constant OFILE_IDC => 2;
use constant OFILE_LST => 3;
use constant OFILE_ASM => 4;
use constant OFILE_DIF => 5;

#
# for AddStrucMember
# 
use constant STRUC_ERROR_MEMBER_NAME    => -1; # already has member with this name (bad name)
use constant STRUC_ERROR_MEMBER_OFFSET  => -2; # already has member at this offset
use constant STRUC_ERROR_MEMBER_SIZE    => -3; # bad number of bytes or bad sizeof(type)
use constant STRUC_ERROR_MEMBER_TINFO   => -4; # bad typeid parameter
use constant STRUC_ERROR_MEMBER_STRUCT  => -5; # bad struct id (the 1st argument)
use constant STRUC_ERROR_MEMBER_UNIVAR  => -6; # unions can't have variable sized members
use constant STRUC_ERROR_MEMBER_VARLAST => -7; # variable sized member should be the last member in the structure

# output control flags:
use constant GENFLG_MAPSEGS => 0x0001; # map: generate map of segments
use constant GENFLG_MAPNAME => 0x0002; # map: include dummy names
use constant GENFLG_MAPDMNG => 0x0004; # map: demangle names
use constant GENFLG_IDCTYPE => 0x0008; # idc: gen only information about types
use constant GENFLG_ASMTYPE => 0x0010; # asm&lst: gen information about types too
use constant GENFLG_GENHTML => 0x0020; # asm&lst: generate html (gui version only)
use constant GENFLG_ASMINC  => 0x0040; # asm&lst: gen information only about types

#
# for AddConstEx
#
use constant CONST_ERROR_NAME  => 1;    # already have member with this name (bad name)
use constant CONST_ERROR_VALUE => 2;    # already have member with this value
use constant CONST_ERROR_ENUM  => 3;    # bad enum id
use constant CONST_ERROR_MASK  => 4;    # bad bmask
use constant CONST_ERROR_ILLV  => 5;    # bad bmask and value combination (~bmask & value != 0)

#
# for GetStringType
#
use constant ASCSTR_C => 0;
use constant ASCSTR_PASCAL => 1;
use constant ASCSTR_LEN2 => 2;
use constant ASCSTR_UNICODE => 3;
use constant ASCSTR_LEN4 => 4;
use constant ASCSTR_ULEN2 => 5;
use constant ASCSTR_ULEN4 => 6;
use constant ASCSTR_LAST => 6;

# for FindXXX
use constant SEARCH_UP     => 0;       # search backward
use constant SEARCH_DOWN   => 0x01;    # search forward
use constant SEARCH_NEXT   => 0x02;    # search next occurence
use constant SEARCH_CASE   => 0x04;    # search case-sensitive
                                       # (only for bin&txt search)
use constant SEARCH_REGEX  => 0x08;    # enable regular expressions
use constant SEARCH_NOBRK  => 0x10;    # don't test ctrl-break
use constant SEARCH_NOSHOW => 0x20;    # don't display the search progress

# for AddCodeXref
use constant fl_CF => 16;              # Call Far
use constant fl_CN => 17;              # Call Near
use constant fl_JF => 18;              # Jump Far
use constant fl_JN => 19;              # Jump Near
use constant fl_US => 20;              # User specified
use constant fl_F  => 21;              # Ordinary flow

# Data reference types:
use constant dr_O => 1;                # Offset
use constant dr_W => 2;                # Write
use constant dr_R => 3;                # Read
use constant dr_T => 4;                # Text (names in manual operands)
use constant dr_I => 5;		       # Informational

# for GetFunctionFlags/SetFunctionFlags
use constant FUNC_NORET   => 0x00000001;     # function doesn't return
use constant FUNC_FAR     => 0x00000002;     # far function
use constant FUNC_LIB     => 0x00000004;     # library function
use constant FUNC_STATIC  => 0x00000008;     # static function
use constant FUNC_FRAME   => 0x00000010;     # function uses frame pointer (BP)
use constant FUNC_USERFAR => 0x00000020;     # user has specified far-ness
                                             # of the function
use constant FUNC_HIDDEN  => 0x00000040;     # a hidden function
use constant FUNC_THUNK   => 0x00000080;     # thunk (jump) function
use constant FUNC_BOTTOMBP =>  0x00000100;   # BP points to the bottom of the stack frame
use constant FUNC_TAIL    => 0x00008000;     # This is a function tail.

# for AutoMark
use constant AU_UNK  => 10;    # make unknown
use constant AU_CODE => 20;    # convert to instruction
use constant AU_PROC => 30;    # make function
use constant AU_USED => 40;    # reanalyse
use constant AU_LIBF => 60;    # apply a flirt signature (the current signature!)
use constant AU_FINAL => 200;  # coagulate unexplored items

# for SetStatus
use constant IDA_STATUS_READY    => 0; # READY     IDA is idle
use constant IDA_STATUS_THINKING => 1; # THINKING  Analyzing but the user may press keys
use constant IDA_STATUS_WAITING  => 2; # WAITING   Waiting for the user input
use constant IDA_STATUS_WORK     => 3; # BUSY      IDA is busy

use constant REF_OFF8   => 0;  # 8bit full offset
use constant REF_OFF16  => 1;  # 16bit full offset
use constant REF_OFF32  => 2;  # 32bit full offset
use constant REF_LOW8   => 3;  # low 8bits of 16bit offset
use constant REF_LOW16  => 4;  # low 16bits of 32bit offset
use constant REF_HIGH8  => 5;  # high 8bits of 16bit offset
use constant REF_HIGH16 => 6;  # high 16bits of 32bit offset
use constant REF_VHIGH  => 7;  # high ph.high_fixup_bits of 32bit offset (processor dependent)
use constant REF_LOW    => 8;  # low  (32-ph.high_fixup_bits) of 32bit offset (processor dependent)
use constant REF_OFF64  => 9;  # 64bit full offset
use constant REFINFO_RVA  => 0x10;     # based reference (rva)
use constant REFINFO_PASTEND => 0x20;  # reference past an item
                                       # it may point to an nonexistitng address
                                       # do not destroy alignment dirs
use constant REFINFO_NOBASE  =>  0x80; # offset base is a number
                                       # implies that base have be any value
                                       # nb: base xrefs are created only if base
                                       # points to the middle of a segment

# fixup types
use constant FIXUP_MASK    =>  0xF;
use constant FIXUP_OFF8    =>  0;       # 8-bit offset.
use constant FIXUP_BYTE    =>  FIXUP_OFF8; # 8-bit offset.
use constant FIXUP_OFF16   =>  1;       # 16-bit offset.
use constant FIXUP_SEG16   =>  2;       # 16-bit base--logical segment base (selector).
use constant FIXUP_PTR32   =>  3;       # 32-bit long pointer (16-bit base:16-bit
                                        # offset).
use constant FIXUP_OFF32   =>  4;       # 32-bit offset.
use constant FIXUP_PTR48   =>  5;       # 48-bit pointer (16-bit base:32-bit offset).
use constant FIXUP_HI8     =>  6;       # high  8 bits of 16bit offset
use constant FIXUP_HI16    =>  7;       # high 16 bits of 32bit offset
use constant FIXUP_LOW8    =>  8;       # low   8 bits of 16bit offset
use constant FIXUP_LOW16   =>  9;       # low  16 bits of 32bit offset
use constant FIXUP_REL     =>  0x10;    # fixup is relative to the linear address
                                        # specified in the 3d parameter to set_fixup()
use constant FIXUP_SELFREL =>  0x0;     # self-relative?
                                #   - disallows the kernel to convert operands
                                #      in the first pass
                                #   - this fixup is used during output
                                # This type of fixups is not used anymore.
                                # Anyway you can use it for commenting purposes
                                # in the loader modules
use constant FIXUP_EXTDEF  =>  0x20;    # target is a location (otherwise - segment)
use constant FIXUP_UNUSED  =>  0x40;    # fixup is ignored by IDA
                                #   - disallows the kernel to convert operands
                                #   - this fixup is not used during output
use constant FIXUP_CREATED =>  0x80;    # fixup was not present in the input file

#
# color_t enum
#
use constant COLOR_DEFAULT  => 0x01;         # Default
use constant COLOR_REGCMT   => 0x02;         # Regular comment
use constant COLOR_RPTCMT   => 0x03;         # Repeatable comment (comment defined somewhere else)
use constant COLOR_AUTOCMT  => 0x04;         # Automatic comment
use constant COLOR_INSN     => 0x05;         # Instruction
use constant COLOR_DATNAME  => 0x06;         # Dummy Data Name
use constant COLOR_DNAME    => 0x07;         # Regular Data Name
use constant COLOR_DEMNAME  => 0x08;         # Demangled Name
use constant COLOR_SYMBOL   => 0x09;         # Punctuation
use constant COLOR_CHAR     => 0x0A;         # Char constant in instruction
use constant COLOR_STRING   => 0x0B;         # String constant in instruction
use constant COLOR_NUMBER   => 0x0C;         # Numeric constant in instruction
use constant COLOR_VOIDOP   => 0x0D;         # Void operand
use constant COLOR_CREF     => 0x0E;         # Code reference
use constant COLOR_DREF     => 0x0F;         # Data reference
use constant COLOR_CREFTAIL => 0x10;         # Code reference to tail byte
use constant COLOR_DREFTAIL => 0x11;         # Data reference to tail byte
use constant COLOR_ERROR    => 0x12;         # Error or problem
use constant COLOR_PREFIX   => 0x13;         # Line prefix
use constant COLOR_BINPREF  => 0x14;         # Binary line prefix bytes
use constant COLOR_EXTRA    => 0x15;         # Extra line
use constant COLOR_ALTOP    => 0x16;         # Alternative operand
use constant COLOR_HIDNAME  => 0x17;         # Hidden name
use constant COLOR_LIBNAME  => 0x18;         # Library function name
use constant COLOR_LOCNAME  => 0x19;         # Local variable name
use constant COLOR_CODNAME  => 0x1A;         # Dummy code name
use constant COLOR_ASMDIR   => 0x1B;         # Assembler directive
use constant COLOR_MACRO    => 0x1C;         # Macro
use constant COLOR_DSTR     => 0x1D;         # String constant in data directive
use constant COLOR_DCHAR    => 0x1E;         # Char constant in data directive
use constant COLOR_DNUM     => 0x1F;         # Numeric constant in data directive
use constant COLOR_KEYWORD  => 0x20;         # Keywords
use constant COLOR_REG      => 0x21;         # Register name
use constant COLOR_IMPNAME  => 0x22;         # Imported name
use constant COLOR_SEGNAME  => 0x23;         # Segment name
use constant COLOR_UNKNAME  => 0x24;         # Dummy unknown name
use constant COLOR_CNAME    => 0x25;         # Regular code name
use constant COLOR_UNAME    => 0x26;         # Regular unknown name
use constant COLOR_COLLAPSED=> 0x27;         # Collapsed line
use constant COLOR_FG_MAX   => 0x28;         # Max color number

#
# Intel x86 instructions
#
use constant Ix86_aaa => 1;
use constant Ix86_aad => 2;
use constant Ix86_aam => 3;
use constant Ix86_aas => 4;
use constant Ix86_adc => 5;
use constant Ix86_add => 6;
use constant Ix86_and => 7;
use constant Ix86_arpl => 8;
use constant Ix86_bound => 9;
use constant Ix86_bsf => 10;
use constant Ix86_bsr => 11;
use constant Ix86_bt => 12;
use constant Ix86_btc => 13;
use constant Ix86_btr => 14;
use constant Ix86_bts => 15;
use constant Ix86_call => 16;
use constant Ix86_callfi => 17;
use constant Ix86_callni => 18;
use constant Ix86_cbw => 19;
use constant Ix86_cwde => 20;
use constant Ix86_cdqe => 21;
use constant Ix86_clc => 22;
use constant Ix86_cld => 23;
use constant Ix86_cli => 24;
use constant Ix86_clts => 25;
use constant Ix86_cmc => 26;
use constant Ix86_cmp => 27;
use constant Ix86_cmps => 28;
use constant Ix86_cwd => 29;
use constant Ix86_cdq => 30;
use constant Ix86_cqo => 31;
use constant Ix86_daa => 32;
use constant Ix86_das => 33;
use constant Ix86_dec => 34;
use constant Ix86_div => 35;
use constant Ix86_enterw => 36;
use constant Ix86_enter => 37;
use constant Ix86_enterd => 38;
use constant Ix86_enterq => 39;
use constant Ix86_hlt => 40;
use constant Ix86_idiv => 41;
use constant Ix86_imul => 42;
use constant Ix86_in => 43;
use constant Ix86_inc => 44;
use constant Ix86_ins => 45;
use constant Ix86_int => 46;
use constant Ix86_into => 47;
use constant Ix86_int3 => 48;
use constant Ix86_iretw => 49;
use constant Ix86_iret => 50;
use constant Ix86_iretd => 51;
use constant Ix86_iretq => 52;
use constant Ix86_ja => 53;
use constant Ix86_jae => 54;
use constant Ix86_jb => 55;
use constant Ix86_jbe => 56;
use constant Ix86_jc => 57;
use constant Ix86_jcxz => 58;
use constant Ix86_jecxz => 59;
use constant Ix86_jrcxz => 60;
use constant Ix86_je => 61;
use constant Ix86_jg => 62;
use constant Ix86_jge => 63;
use constant Ix86_jl => 64;
use constant Ix86_jle => 65;
use constant Ix86_jna => 66;
use constant Ix86_jnae => 67;
use constant Ix86_jnb => 68;
use constant Ix86_jnbe => 69;
use constant Ix86_jnc => 70;
use constant Ix86_jne => 71;
use constant Ix86_jng => 72;
use constant Ix86_jnge => 73;
use constant Ix86_jnl => 74;
use constant Ix86_jnle => 75;
use constant Ix86_jno => 76;
use constant Ix86_jnp => 77;
use constant Ix86_jns => 78;
use constant Ix86_jnz => 79;
use constant Ix86_jo => 80;
use constant Ix86_jp => 81;
use constant Ix86_jpe => 82;
use constant Ix86_jpo => 83;
use constant Ix86_js => 84;
use constant Ix86_jz => 85;
use constant Ix86_jmp => 86;
use constant Ix86_jmpfi => 87;
use constant Ix86_jmpni => 88;
use constant Ix86_jmp_short => 89;
use constant Ix86_lahf => 90;
use constant Ix86_lar => 91;
use constant Ix86_lea => 92;
use constant Ix86_leavew => 93;
use constant Ix86_leave => 94;
use constant Ix86_leaved => 95;
use constant Ix86_leaveq => 96;
use constant Ix86_lgdt => 97;
use constant Ix86_lidt => 98;
use constant Ix86_lgs => 99;
use constant Ix86_lss => 100;
use constant Ix86_lds => 101;
use constant Ix86_les => 102;
use constant Ix86_lfs => 103;
use constant Ix86_lldt => 104;
use constant Ix86_lmsw => 105;
use constant Ix86_lock => 106;
use constant Ix86_lods => 107;
use constant Ix86_loopw => 108;
use constant Ix86_loop => 109;
use constant Ix86_loopd => 110;
use constant Ix86_loopq => 111;
use constant Ix86_loopwe => 112;
use constant Ix86_loope => 113;
use constant Ix86_loopde => 114;
use constant Ix86_loopqe => 115;
use constant Ix86_loopwne => 116;
use constant Ix86_loopne => 117;
use constant Ix86_loopdne => 118;
use constant Ix86_loopqne => 119;
use constant Ix86_lsl => 120;
use constant Ix86_ltr => 121;
use constant Ix86_mov => 122;
use constant Ix86_movsp => 123;
use constant Ix86_movs => 124;
use constant Ix86_movsx => 125;
use constant Ix86_movzx => 126;
use constant Ix86_mul => 127;
use constant Ix86_neg => 128;
use constant Ix86_nop => 129;
use constant Ix86_not => 130;
use constant Ix86_or => 131;
use constant Ix86_out => 132;
use constant Ix86_outs => 133;
use constant Ix86_pop => 134;
use constant Ix86_popaw => 135;
use constant Ix86_popa => 136;
use constant Ix86_popad => 137;
use constant Ix86_popaq => 138;
use constant Ix86_popfw => 139;
use constant Ix86_popf => 140;
use constant Ix86_popfd => 141;
use constant Ix86_popfq => 142;
use constant Ix86_push => 143;
use constant Ix86_pushaw => 144;
use constant Ix86_pusha => 145;
use constant Ix86_pushad => 146;
use constant Ix86_pushaq => 147;
use constant Ix86_pushfw => 148;
use constant Ix86_pushf => 149;
use constant Ix86_pushfd => 150;
use constant Ix86_pushfq => 151;
use constant Ix86_rcl => 152;
use constant Ix86_rcr => 153;
use constant Ix86_rol => 154;
use constant Ix86_ror => 155;
use constant Ix86_rep => 156;
use constant Ix86_repe => 157;
use constant Ix86_repne => 158;
use constant Ix86_retn => 159;
use constant Ix86_retf => 160;
use constant Ix86_sahf => 161;
use constant Ix86_sal => 162;
use constant Ix86_sar => 163;
use constant Ix86_shl => 164;
use constant Ix86_shr => 165;
use constant Ix86_sbb => 166;
use constant Ix86_scas => 167;
use constant Ix86_seta => 168;
use constant Ix86_setae => 169;
use constant Ix86_setb => 170;
use constant Ix86_setbe => 171;
use constant Ix86_setc => 172;
use constant Ix86_sete => 173;
use constant Ix86_setg => 174;
use constant Ix86_setge => 175;
use constant Ix86_setl => 176;
use constant Ix86_setle => 177;
use constant Ix86_setna => 178;
use constant Ix86_setnae => 179;
use constant Ix86_setnb => 180;
use constant Ix86_setnbe => 181;
use constant Ix86_setnc => 182;
use constant Ix86_setne => 183;
use constant Ix86_setng => 184;
use constant Ix86_setnge => 185;
use constant Ix86_setnl => 186;
use constant Ix86_setnle => 187;
use constant Ix86_setno => 188;
use constant Ix86_setnp => 189;
use constant Ix86_setns => 190;
use constant Ix86_setnz => 191;
use constant Ix86_seto => 192;
use constant Ix86_setp => 193;
use constant Ix86_setpe => 194;
use constant Ix86_setpo => 195;
use constant Ix86_sets => 196;
use constant Ix86_setz => 197;
use constant Ix86_sgdt => 198;
use constant Ix86_sidt => 199;
use constant Ix86_shld => 200;
use constant Ix86_shrd => 201;
use constant Ix86_sldt => 202;
use constant Ix86_smsw => 203;
use constant Ix86_stc => 204;
use constant Ix86_std => 205;
use constant Ix86_sti => 206;
use constant Ix86_stos => 207;
use constant Ix86_str => 208;
use constant Ix86_sub => 209;
use constant Ix86_test => 210;
use constant Ix86_verr => 211;
use constant Ix86_verw => 212;
use constant Ix86_wait => 213;
use constant Ix86_xchg => 214;
use constant Ix86_xlat => 215;
use constant Ix86_xor => 216;
use constant Ix86_cmpxchg => 217;
use constant Ix86_bswap => 218;
use constant Ix86_xadd => 219;
use constant Ix86_invd => 220;
use constant Ix86_wbinvd => 221;
use constant Ix86_invlpg => 222;
use constant Ix86_rdmsr => 223;
use constant Ix86_wrmsr => 224;
use constant Ix86_cpuid => 225;
use constant Ix86_cmpxchg8b => 226;
use constant Ix86_rdtsc => 227;
use constant Ix86_rsm => 228;
use constant Ix86_cmova => 229;
use constant Ix86_cmovb => 230;
use constant Ix86_cmovbe => 231;
use constant Ix86_cmovg => 232;
use constant Ix86_cmovge => 233;
use constant Ix86_cmovl => 234;
use constant Ix86_cmovle => 235;
use constant Ix86_cmovnb => 236;
use constant Ix86_cmovno => 237;
use constant Ix86_cmovnp => 238;
use constant Ix86_cmovns => 239;
use constant Ix86_cmovnz => 240;
use constant Ix86_cmovo => 241;
use constant Ix86_cmovp => 242;
use constant Ix86_cmovs => 243;
use constant Ix86_cmovz => 244;
use constant Ix86_fcmovb => 245;
use constant Ix86_fcmove => 246;
use constant Ix86_fcmovbe => 247;
use constant Ix86_fcmovu => 248;
use constant Ix86_fcmovnb => 249;
use constant Ix86_fcmovne => 250;
use constant Ix86_fcmovnbe => 251;
use constant Ix86_fcmovnu => 252;
use constant Ix86_fcomi => 253;
use constant Ix86_fucomi => 254;
use constant Ix86_fcomip => 255;
use constant Ix86_fucomip => 256;
use constant Ix86_rdpmc => 257;
use constant Ix86_fld => 258;
use constant Ix86_fst => 259;
use constant Ix86_fstp => 260;
use constant Ix86_fxch => 261;
use constant Ix86_fild => 262;
use constant Ix86_fist => 263;
use constant Ix86_fistp => 264;
use constant Ix86_fbld => 265;
use constant Ix86_fbstp => 266;
use constant Ix86_fadd => 267;
use constant Ix86_faddp => 268;
use constant Ix86_fiadd => 269;
use constant Ix86_fsub => 270;
use constant Ix86_fsubp => 271;
use constant Ix86_fisub => 272;
use constant Ix86_fsubr => 273;
use constant Ix86_fsubrp => 274;
use constant Ix86_fisubr => 275;
use constant Ix86_fmul => 276;
use constant Ix86_fmulp => 277;
use constant Ix86_fimul => 278;
use constant Ix86_fdiv => 279;
use constant Ix86_fdivp => 280;
use constant Ix86_fidiv => 281;
use constant Ix86_fdivr => 282;
use constant Ix86_fdivrp => 283;
use constant Ix86_fidivr => 284;
use constant Ix86_fsqrt => 285;
use constant Ix86_fscale => 286;
use constant Ix86_fprem => 287;
use constant Ix86_frndint => 288;
use constant Ix86_fxtract => 289;
use constant Ix86_fabs => 290;
use constant Ix86_fchs => 291;
use constant Ix86_fcom => 292;
use constant Ix86_fcomp => 293;
use constant Ix86_fcompp => 294;
use constant Ix86_ficom => 295;
use constant Ix86_ficomp => 296;
use constant Ix86_ftst => 297;
use constant Ix86_fxam => 298;
use constant Ix86_fptan => 299;
use constant Ix86_fpatan => 300;
use constant Ix86_f2xm1 => 301;
use constant Ix86_fyl2x => 302;
use constant Ix86_fyl2xp1 => 303;
use constant Ix86_fldz => 304;
use constant Ix86_fld1 => 305;
use constant Ix86_fldpi => 306;
use constant Ix86_fldl2t => 307;
use constant Ix86_fldl2e => 308;
use constant Ix86_fldlg2 => 309;
use constant Ix86_fldln2 => 310;
use constant Ix86_finit => 311;
use constant Ix86_fninit => 312;
use constant Ix86_fsetpm => 313;
use constant Ix86_fldcw => 314;
use constant Ix86_fstcw => 315;
use constant Ix86_fnstcw => 316;
use constant Ix86_fstsw => 317;
use constant Ix86_fnstsw => 318;
use constant Ix86_fclex => 319;
use constant Ix86_fnclex => 320;
use constant Ix86_fstenv => 321;
use constant Ix86_fnstenv => 322;
use constant Ix86_fldenv => 323;
use constant Ix86_fsave => 324;
use constant Ix86_fnsave => 325;
use constant Ix86_frstor => 326;
use constant Ix86_fincstp => 327;
use constant Ix86_fdecstp => 328;
use constant Ix86_ffree => 329;
use constant Ix86_fnop => 330;
use constant Ix86_feni => 331;
use constant Ix86_fneni => 332;
use constant Ix86_fdisi => 333;
use constant Ix86_fndisi => 334;
use constant Ix86_fprem1 => 335;
use constant Ix86_fsincos => 336;
use constant Ix86_fsin => 337;
use constant Ix86_fcos => 338;
use constant Ix86_fucom => 339;
use constant Ix86_fucomp => 340;
use constant Ix86_fucompp => 341;
use constant Ix86_setalc => 342;
use constant Ix86_svdc => 343;
use constant Ix86_rsdc => 344;
use constant Ix86_svldt => 345;
use constant Ix86_rsldt => 346;
use constant Ix86_svts => 347;
use constant Ix86_rsts => 348;
use constant Ix86_icebp => 349;
use constant Ix86_loadall => 350;
use constant Ix86_emms => 351;
use constant Ix86_movd => 352;
use constant Ix86_movq => 353;
use constant Ix86_packsswb => 354;
use constant Ix86_packssdw => 355;
use constant Ix86_packuswb => 356;
use constant Ix86_paddb => 357;
use constant Ix86_paddw => 358;
use constant Ix86_paddd => 359;
use constant Ix86_paddsb => 360;
use constant Ix86_paddsw => 361;
use constant Ix86_paddusb => 362;
use constant Ix86_paddusw => 363;
use constant Ix86_pand => 364;
use constant Ix86_pandn => 365;
use constant Ix86_pcmpeqb => 366;
use constant Ix86_pcmpeqw => 367;
use constant Ix86_pcmpeqd => 368;
use constant Ix86_pcmpgtb => 369;
use constant Ix86_pcmpgtw => 370;
use constant Ix86_pcmpgtd => 371;
use constant Ix86_pmaddwd => 372;
use constant Ix86_pmulhw => 373;
use constant Ix86_pmullw => 374;
use constant Ix86_por => 375;
use constant Ix86_psllw => 376;
use constant Ix86_pslld => 377;
use constant Ix86_psllq => 378;
use constant Ix86_psraw => 379;
use constant Ix86_psrad => 380;
use constant Ix86_psrlw => 381;
use constant Ix86_psrld => 382;
use constant Ix86_psrlq => 383;
use constant Ix86_psubb => 384;
use constant Ix86_psubw => 385;
use constant Ix86_psubd => 386;
use constant Ix86_psubsb => 387;
use constant Ix86_psubsw => 388;
use constant Ix86_psubusb => 389;
use constant Ix86_psubusw => 390;
use constant Ix86_punpckhbw => 391;
use constant Ix86_punpckhwd => 392;
use constant Ix86_punpckhdq => 393;
use constant Ix86_punpcklbw => 394;
use constant Ix86_punpcklwd => 395;
use constant Ix86_punpckldq => 396;
use constant Ix86_pxor => 397;
use constant Ix86_fxsave => 398;
use constant Ix86_fxrstor => 399;
use constant Ix86_sysenter => 400;
use constant Ix86_sysexit => 401;
use constant Ix86_pavgusb => 402;
use constant Ix86_pfadd => 403;
use constant Ix86_pfsub => 404;
use constant Ix86_pfsubr => 405;
use constant Ix86_pfacc => 406;
use constant Ix86_pfcmpge => 407;
use constant Ix86_pfcmpgt => 408;
use constant Ix86_pfcmpeq => 409;
use constant Ix86_pfmin => 410;
use constant Ix86_pfmax => 411;
use constant Ix86_pi2fd => 412;
use constant Ix86_pf2id => 413;
use constant Ix86_pfrcp => 414;
use constant Ix86_pfrsqrt => 415;
use constant Ix86_pfmul => 416;
use constant Ix86_pfrcpit1 => 417;
use constant Ix86_pfrsqit1 => 418;
use constant Ix86_pfrcpit2 => 419;
use constant Ix86_pmulhrw => 420;
use constant Ix86_femms => 421;
use constant Ix86_prefetch => 422;
use constant Ix86_prefetchw => 423;
use constant Ix86_addps => 424;
use constant Ix86_addss => 425;
use constant Ix86_andnps => 426;
use constant Ix86_andps => 427;
use constant Ix86_cmpps => 428;
use constant Ix86_cmpss => 429;
use constant Ix86_comiss => 430;
use constant Ix86_cvtpi2ps => 431;
use constant Ix86_cvtps2pi => 432;
use constant Ix86_cvtsi2ss => 433;
use constant Ix86_cvtss2si => 434;
use constant Ix86_cvttps2pi => 435;
use constant Ix86_cvttss2si => 436;
use constant Ix86_divps => 437;
use constant Ix86_divss => 438;
use constant Ix86_ldmxcsr => 439;
use constant Ix86_maxps => 440;
use constant Ix86_maxss => 441;
use constant Ix86_minps => 442;
use constant Ix86_minss => 443;
use constant Ix86_movaps => 444;
use constant Ix86_movhlps => 445;
use constant Ix86_movhps => 446;
use constant Ix86_movlhps => 447;
use constant Ix86_movlps => 448;
use constant Ix86_movmskps => 449;
use constant Ix86_movss => 450;
use constant Ix86_movups => 451;
use constant Ix86_mulps => 452;
use constant Ix86_mulss => 453;
use constant Ix86_orps => 454;
use constant Ix86_rcpps => 455;
use constant Ix86_rcpss => 456;
use constant Ix86_rsqrtps => 457;
use constant Ix86_rsqrtss => 458;
use constant Ix86_shufps => 459;
use constant Ix86_sqrtps => 460;
use constant Ix86_sqrtss => 461;
use constant Ix86_stmxcsr => 462;
use constant Ix86_subps => 463;
use constant Ix86_subss => 464;
use constant Ix86_ucomiss => 465;
use constant Ix86_unpckhps => 466;
use constant Ix86_unpcklps => 467;
use constant Ix86_xorps => 468;
use constant Ix86_pavgb => 469;
use constant Ix86_pavgw => 470;
use constant Ix86_pextrw => 471;
use constant Ix86_pinsrw => 472;
use constant Ix86_pmaxsw => 473;
use constant Ix86_pmaxub => 474;
use constant Ix86_pminsw => 475;
use constant Ix86_pminub => 476;
use constant Ix86_pmovmskb => 477;
use constant Ix86_pmulhuw => 478;
use constant Ix86_psadbw => 479;
use constant Ix86_pshufw => 480;
use constant Ix86_maskmovq => 481;
use constant Ix86_movntps => 482;
use constant Ix86_movntq => 483;
use constant Ix86_prefetcht0 => 484;
use constant Ix86_prefetcht1 => 485;
use constant Ix86_prefetcht2 => 486;
use constant Ix86_prefetchnta => 487;
use constant Ix86_sfence => 488;
use constant Ix86_cmpeqps => 489;
use constant Ix86_cmpltps => 490;
use constant Ix86_cmpleps => 491;
use constant Ix86_cmpunordps => 492;
use constant Ix86_cmpneqps => 493;
use constant Ix86_cmpnltps => 494;
use constant Ix86_cmpnleps => 495;
use constant Ix86_cmpordps => 496;
use constant Ix86_cmpeqss => 497;
use constant Ix86_cmpltss => 498;
use constant Ix86_cmpless => 499;
use constant Ix86_cmpunordss => 500;
use constant Ix86_cmpneqss => 501;
use constant Ix86_cmpnltss => 502;
use constant Ix86_cmpnless => 503;
use constant Ix86_cmpordss => 504;
use constant Ix86_pf2iw => 505;
use constant Ix86_pfnacc => 506;
use constant Ix86_pfpnacc => 507;
use constant Ix86_pi2fw => 508;
use constant Ix86_pswapd => 509;
use constant Ix86_fstp1 => 510;
use constant Ix86_fcom2 => 511;
use constant Ix86_fcomp3 => 512;
use constant Ix86_fxch4 => 513;
use constant Ix86_fcomp5 => 514;
use constant Ix86_ffreep => 515;
use constant Ix86_fxch7 => 516;
use constant Ix86_fstp8 => 517;
use constant Ix86_fstp9 => 518;
use constant Ix86_addpd => 519;
use constant Ix86_addsd => 520;
use constant Ix86_andnpd => 521;
use constant Ix86_andpd => 522;
use constant Ix86_clflush => 523;
use constant Ix86_cmppd => 524;
use constant Ix86_cmpsd => 525;
use constant Ix86_comisd => 526;
use constant Ix86_cvtdq2pd => 527;
use constant Ix86_cvtdq2ps => 528;
use constant Ix86_cvtpd2dq => 529;
use constant Ix86_cvtpd2pi => 530;
use constant Ix86_cvtpd2ps => 531;
use constant Ix86_cvtpi2pd => 532;
use constant Ix86_cvtps2dq => 533;
use constant Ix86_cvtps2pd => 534;
use constant Ix86_cvtsd2si => 535;
use constant Ix86_cvtsd2ss => 536;
use constant Ix86_cvtsi2sd => 537;
use constant Ix86_cvtss2sd => 538;
use constant Ix86_cvttpd2dq => 539;
use constant Ix86_cvttpd2pi => 540;
use constant Ix86_cvttps2dq => 541;
use constant Ix86_cvttsd2si => 542;
use constant Ix86_divpd => 543;
use constant Ix86_divsd => 544;
use constant Ix86_lfence => 545;
use constant Ix86_maskmovdqu => 546;
use constant Ix86_maxpd => 547;
use constant Ix86_maxsd => 548;
use constant Ix86_mfence => 549;
use constant Ix86_minpd => 550;
use constant Ix86_minsd => 551;
use constant Ix86_movapd => 552;
use constant Ix86_movdq2q => 553;
use constant Ix86_movdqa => 554;
use constant Ix86_movdqu => 555;
use constant Ix86_movhpd => 556;
use constant Ix86_movlpd => 557;
use constant Ix86_movmskpd => 558;
use constant Ix86_movntdq => 559;
use constant Ix86_movnti => 560;
use constant Ix86_movntpd => 561;
use constant Ix86_movq2dq => 562;
use constant Ix86_movsd => 563;
use constant Ix86_movupd => 564;
use constant Ix86_mulpd => 565;
use constant Ix86_mulsd => 566;
use constant Ix86_orpd => 567;
use constant Ix86_paddq => 568;
use constant Ix86_pause => 569;
use constant Ix86_pmuludq => 570;
use constant Ix86_pshufd => 571;
use constant Ix86_pshufhw => 572;
use constant Ix86_pshuflw => 573;
use constant Ix86_pslldq => 574;
use constant Ix86_psrldq => 575;
use constant Ix86_psubq => 576;
use constant Ix86_punpckhqdq => 577;
use constant Ix86_punpcklqdq => 578;
use constant Ix86_shufpd => 579;
use constant Ix86_sqrtpd => 580;
use constant Ix86_sqrtsd => 581;
use constant Ix86_subpd => 582;
use constant Ix86_subsd => 583;
use constant Ix86_ucomisd => 584;
use constant Ix86_unpckhpd => 585;
use constant Ix86_unpcklpd => 586;
use constant Ix86_xorpd => 587;
use constant Ix86_syscall => 588;
use constant Ix86_sysret => 589;
use constant Ix86_swapgs => 590;

###
#
# F U N C T I O N S
#
###
sub AutoMark
{
  my($ea, $qtype) = @_;
  AutoMark2($ea, $ea+1, $qtype);
}

sub GetConst
{
  my($id,$v,$mask) = @_;
  return GetConstEx($id,$v,0,$mask);
}

sub OpOffset
{
  my($ea, $base) = @_;
  return OpOff($ea, -1, $base);
}

sub here
{
  return ScreenEA();
}

sub OpNum
{
  return OpNumber(shift, -1);
}

sub OpChar
{
  return OpChr(shift, -1);
}

sub OpDec
{
  return OpDecimal(shift, -1);
}

sub OpSegment
{
  return OpSeg(shift, -1);
}

sub SegStart
{
  return GetSegmentAttr(shift, SEGATTR_START);
}

sub SegEnd
{
  return GetSegmentAttr(shift, SEGATTR_END);
}

sub SetSegmentType
{
  my($ea, $type) = @_;
  return SetSegmentAttr($ea, SEGATTR_TYPE, $type);
}

sub GetFunctionFlags
{
  my $ea = shift;
  return GetFunctionAttr($ea, FUNCATTR_FLAGS);
}

sub SetFunctionFlags
{
  my($ea, $flags) = @_;
  return SetFunctionAttr($ea, FUNCATTR_FLAGS, $flags);
}

sub MakeStruct
{
  my($ea, $name) = @_;
  return MakeStructEx($ea, -1, $name);
}

sub GetTrueName
{
  my $ea = shift;
  return GetTrueNameEx(BADADDR, $ea);
}

sub Name
{
  my $ea = shift;
  return NameEx(BADADDR, $ea);
}

sub get_ascii_str
{
  local $addr = shift;
  local $res = "";
  local $c;
  while ( $c = Byte($addr) )
  {
    $res .= chr($c);
    $addr++;
  }
  return $res;
}

###
#
# E X P O R T E D   N A M E S
#
###
@EXPORT = qw(
BADADDR
MAXADDR
MS_CLS
FF_CODE
FF_DATA
FF_TAIL
FF_UNK
MS_COMM
FF_COMM
FF_REF
FF_LINE
FF_NAME
FF_LABL
FF_FLOW
FF_VAR
MS_0TYPE
FF_0VOID
FF_0NUMH
FF_0NUMD
FF_0CHAR
FF_0SEG
FF_0OFF
FF_0NUMB
FF_0NUMO
FF_0ENUM
FF_0FOP
FF_0STRO
FF_0STK
FF_0FLT
FF_0CUST
MS_1TYPE
FF_1VOID
FF_1NUMH
FF_1NUMD
FF_1CHAR
FF_1SEG
FF_1OFF
FF_1NUMB
FF_1NUMO
FF_1ENUM
FF_1FOP
FF_1STRO
FF_1STK
FF_1FLT
FF_1CUST
DT_TYPE
FF_BYTE
FF_WORD
FF_DWRD
FF_QWRD
FF_TBYT
FF_ASCI
FF_STRU
FF_OWRD
FF_FLOAT
FF_DOUBLE
FF_PACKREAL
FF_ALIGN
FF_3BYTE
FF_CUSTOM
MS_CODE
FF_FUNC
FF_IMMD
FF_JUMP
IDCHK_OK
IDCHK_ARG
IDCHK_KEY
IDCHK_MAX
NEF_SEGS
NEF_RSCS
NEF_NAME
NEF_MAN
NEF_FILL
NEF_IMPS
NEF_TIGHT
NEF_FIRST
NEF_CODE
NEF_RELOAD
NEF_FLAT
NEF_MINI
NEF_LOPT
NEF_LALL
SEG_NORM
SEG_XTRN
SEG_CODE
SEG_DATA
SEG_IMP
SEG_GRP
SEG_NULL
SEG_UNDF
SEG_BSS
SEG_ABSSYM
SEG_COMM
SEG_IMEM
SEGATTR_START
SEGATTR_END
SEGATTR_ORGBASE
SEGATTR_ALIGN
SEGATTR_COMB
SEGATTR_PERM
SEGATTR_USE32
SEGATTR_FLAGS
SEGATTR_SEL
SEGATTR_DEF_ES
SEGATTR_DEF_CS
SEGATTR_DEF_SS
SEGATTR_DEF_DS
SEGATTR_DEF_FS
SEGATTR_DEF_GS
SEGATTR_TYPE
SEGATTR_COLOR
OFILE_MAP
OFILE_EXE
OFILE_IDC
OFILE_LST
OFILE_ASM
OFILE_DIF
GENFLG_MAPSEGS
GENFLG_MAPNAME
GENFLG_MAPDMNG
GENFLG_MAPLOC
GENFLG_IDCTYPE
GENFLG_ASMTYPE
GENFLG_GENHTML
GENFLG_ASMINC
ASCSTR_C
ASCSTR_PASCAL
ASCSTR_LEN2
ASCSTR_UNICODE
ASCSTR_LEN4
ASCSTR_ULEN2
ASCSTR_ULEN4
ASCSTR_LAST
SEARCH_UP
SEARCH_DOWN
SEARCH_NEXT
SEARCH_CASE
SEARCH_REGEX
SEARCH_NOBRK
SEARCH_NOSHOW
SN_CHECK
SN_NOCHECK
SN_PUBLIC
SN_NON_PUBLIC
SN_WEAK
SN_NON_WEAK
SN_AUTO
SN_NON_AUTO
SN_NOLIST
SN_NOWARN
SN_LOCAL
STRUC_ERROR_MEMBER_NAME
STRUC_ERROR_MEMBER_OFFSET
STRUC_ERROR_MEMBER_SIZE
STRUC_ERROR_MEMBER_TINFO
STRUC_ERROR_MEMBER_STRUCT
STRUC_ERROR_MEMBER_UNIVAR
STRUC_ERROR_MEMBER_VARLAST
CONST_ERROR_NAME
CONST_ERROR_VALUE
CONST_ERROR_ENUM
CONST_ERROR_MASK
CONST_ERROR_ILLV
fl_CF
fl_CN
fl_JF
fl_JN
fl_US
fl_F
dr_O
dr_W
dr_R
dr_T
dr_I
FUNCATTR_START
FUNCATTR_END
FUNCATTR_FLAGS
FUNCATTR_FRAME
FUNCATTR_FRSIZE
FUNCATTR_FRREGS
FUNCATTR_ARGSIZE
FUNCATTR_FPD
FUNCATTR_COLOR
FUNC_NORET
FUNC_FAR
FUNC_LIB
FUNC_STATIC
FUNC_FRAME
FUNC_USERFAR
FUNC_HIDDEN
FUNC_THUNK
FUNC_BOTTOMBP
FUNC_TAIL
AU_UNK
AU_CODE
AU_PROC
AU_USED
AU_LIBF
AU_FINAL
IDA_STATUS_READY
IDA_STATUS_THINKING
IDA_STATUS_WAITING
IDA_STATUS_WORK
REF_OFF8
REF_OFF16
REF_OFF32
REF_LOW8
REF_LOW16
REF_HIGH8
REF_HIGH16
REF_VHIGH
REF_VLOW
REF_OFF64
REFINFO_RVA
REFINFO_PASTEND
REFINFO_NOBASE
FIXUP_MASK
FIXUP_BYTE
FIXUP_OFF8
FIXUP_OFF16
FIXUP_SEG16
FIXUP_PTR32
FIXUP_OFF32
FIXUP_PTR48
FIXUP_HI8
FIXUP_HI16
FIXUP_LOW8
FIXUP_LOW16
FIXUP_REL
FIXUP_SELFREL
FIXUP_EXTDEF
FIXUP_UNUSED
FIXUP_CREATED
COLOR_DEFAULT
COLOR_REGCMT
COLOR_RPTCMT
COLOR_AUTOCMT
COLOR_INSN
COLOR_DATNAME
COLOR_DNAME
COLOR_DEMNAME
COLOR_SYMBOL
COLOR_CHAR
COLOR_STRING
COLOR_NUMBER
COLOR_VOIDOP
COLOR_CREF
COLOR_DREF
COLOR_CREFTAIL
COLOR_DREFTAIL
COLOR_ERROR
COLOR_PREFIX
COLOR_BINPREF
COLOR_EXTRA
COLOR_ALTOP
COLOR_HIDNAME
COLOR_LIBNAME
COLOR_LOCNAME
COLOR_CODNAME
COLOR_ASMDIR
COLOR_MACRO
COLOR_DSTR
COLOR_DCHAR
COLOR_DNUM
COLOR_KEYWORD
COLOR_REG
COLOR_IMPNAME
COLOR_SEGNAME
COLOR_UNKNAME
COLOR_CNAME
COLOR_UNAME
COLOR_COLLAPSED
COLOR_FG_MAX
Ix86_aaa
Ix86_aad
Ix86_aam
Ix86_aas
Ix86_adc
Ix86_add
Ix86_and
Ix86_arpl
Ix86_bound
Ix86_bsf
Ix86_bsr
Ix86_bt
Ix86_btc
Ix86_btr
Ix86_bts
Ix86_call
Ix86_callfi
Ix86_callni
Ix86_cbw
Ix86_cwde
Ix86_cdqe
Ix86_clc
Ix86_cld
Ix86_cli
Ix86_clts
Ix86_cmc
Ix86_cmp
Ix86_cmps
Ix86_cwd
Ix86_cdq
Ix86_cqo
Ix86_daa
Ix86_das
Ix86_dec
Ix86_div
Ix86_enterw
Ix86_enter
Ix86_enterd
Ix86_enterq
Ix86_hlt
Ix86_idiv
Ix86_imul
Ix86_in
Ix86_inc
Ix86_ins
Ix86_int
Ix86_into
Ix86_int3
Ix86_iretw
Ix86_iret
Ix86_iretd
Ix86_iretq
Ix86_ja
Ix86_jae
Ix86_jb
Ix86_jbe
Ix86_jc
Ix86_jcxz
Ix86_jecxz
Ix86_jrcxz
Ix86_je
Ix86_jg
Ix86_jge
Ix86_jl
Ix86_jle
Ix86_jna
Ix86_jnae
Ix86_jnb
Ix86_jnbe
Ix86_jnc
Ix86_jne
Ix86_jng
Ix86_jnge
Ix86_jnl
Ix86_jnle
Ix86_jno
Ix86_jnp
Ix86_jns
Ix86_jnz
Ix86_jo
Ix86_jp
Ix86_jpe
Ix86_jpo
Ix86_js
Ix86_jz
Ix86_jmp
Ix86_jmpfi
Ix86_jmpni
Ix86_jmp_short
Ix86_lahf
Ix86_lar
Ix86_lea
Ix86_leavew
Ix86_leave
Ix86_leaved
Ix86_leaveq
Ix86_lgdt
Ix86_lidt
Ix86_lgs
Ix86_lss
Ix86_lds
Ix86_les
Ix86_lfs
Ix86_lldt
Ix86_lmsw
Ix86_lock
Ix86_lods
Ix86_loopw
Ix86_loop
Ix86_loopd
Ix86_loopq
Ix86_loopwe
Ix86_loope
Ix86_loopde
Ix86_loopqe
Ix86_loopwne
Ix86_loopne
Ix86_loopdne
Ix86_loopqne
Ix86_lsl
Ix86_ltr
Ix86_mov
Ix86_movsp
Ix86_movs
Ix86_movsx
Ix86_movzx
Ix86_mul
Ix86_neg
Ix86_nop
Ix86_not
Ix86_or
Ix86_out
Ix86_outs
Ix86_pop
Ix86_popaw
Ix86_popa
Ix86_popad
Ix86_popaq
Ix86_popfw
Ix86_popf
Ix86_popfd
Ix86_popfq
Ix86_push
Ix86_pushaw
Ix86_pusha
Ix86_pushad
Ix86_pushaq
Ix86_pushfw
Ix86_pushf
Ix86_pushfd
Ix86_pushfq
Ix86_rcl
Ix86_rcr
Ix86_rol
Ix86_ror
Ix86_rep
Ix86_repe
Ix86_repne
Ix86_retn
Ix86_retf
Ix86_sahf
Ix86_sal
Ix86_sar
Ix86_shl
Ix86_shr
Ix86_sbb
Ix86_scas
Ix86_seta
Ix86_setae
Ix86_setb
Ix86_setbe
Ix86_setc
Ix86_sete
Ix86_setg
Ix86_setge
Ix86_setl
Ix86_setle
Ix86_setna
Ix86_setnae
Ix86_setnb
Ix86_setnbe
Ix86_setnc
Ix86_setne
Ix86_setng
Ix86_setnge
Ix86_setnl
Ix86_setnle
Ix86_setno
Ix86_setnp
Ix86_setns
Ix86_setnz
Ix86_seto
Ix86_setp
Ix86_setpe
Ix86_setpo
Ix86_sets
Ix86_setz
Ix86_sgdt
Ix86_sidt
Ix86_shld
Ix86_shrd
Ix86_sldt
Ix86_smsw
Ix86_stc
Ix86_std
Ix86_sti
Ix86_stos
Ix86_str
Ix86_sub
Ix86_test
Ix86_verr
Ix86_verw
Ix86_wait
Ix86_xchg
Ix86_xlat
Ix86_xor
Ix86_cmpxchg
Ix86_bswap
Ix86_xadd
Ix86_invd
Ix86_wbinvd
Ix86_invlpg
Ix86_rdmsr
Ix86_wrmsr
Ix86_cpuid
Ix86_cmpxchg8b
Ix86_rdtsc
Ix86_rsm
Ix86_cmova
Ix86_cmovb
Ix86_cmovbe
Ix86_cmovg
Ix86_cmovge
Ix86_cmovl
Ix86_cmovle
Ix86_cmovnb
Ix86_cmovno
Ix86_cmovnp
Ix86_cmovns
Ix86_cmovnz
Ix86_cmovo
Ix86_cmovp
Ix86_cmovs
Ix86_cmovz
Ix86_fcmovb
Ix86_fcmove
Ix86_fcmovbe
Ix86_fcmovu
Ix86_fcmovnb
Ix86_fcmovne
Ix86_fcmovnbe
Ix86_fcmovnu
Ix86_fcomi
Ix86_fucomi
Ix86_fcomip
Ix86_fucomip
Ix86_rdpmc
Ix86_fld
Ix86_fst
Ix86_fstp
Ix86_fxch
Ix86_fild
Ix86_fist
Ix86_fistp
Ix86_fbld
Ix86_fbstp
Ix86_fadd
Ix86_faddp
Ix86_fiadd
Ix86_fsub
Ix86_fsubp
Ix86_fisub
Ix86_fsubr
Ix86_fsubrp
Ix86_fisubr
Ix86_fmul
Ix86_fmulp
Ix86_fimul
Ix86_fdiv
Ix86_fdivp
Ix86_fidiv
Ix86_fdivr
Ix86_fdivrp
Ix86_fidivr
Ix86_fsqrt
Ix86_fscale
Ix86_fprem
Ix86_frndint
Ix86_fxtract
Ix86_fabs
Ix86_fchs
Ix86_fcom
Ix86_fcomp
Ix86_fcompp
Ix86_ficom
Ix86_ficomp
Ix86_ftst
Ix86_fxam
Ix86_fptan
Ix86_fpatan
Ix86_f2xm1
Ix86_fyl2x
Ix86_fyl2xp1
Ix86_fldz
Ix86_fld1
Ix86_fldpi
Ix86_fldl2t
Ix86_fldl2e
Ix86_fldlg2
Ix86_fldln2
Ix86_finit
Ix86_fninit
Ix86_fsetpm
Ix86_fldcw
Ix86_fstcw
Ix86_fnstcw
Ix86_fstsw
Ix86_fnstsw
Ix86_fclex
Ix86_fnclex
Ix86_fstenv
Ix86_fnstenv
Ix86_fldenv
Ix86_fsave
Ix86_fnsave
Ix86_frstor
Ix86_fincstp
Ix86_fdecstp
Ix86_ffree
Ix86_fnop
Ix86_feni
Ix86_fneni
Ix86_fdisi
Ix86_fndisi
Ix86_fprem1
Ix86_fsincos
Ix86_fsin
Ix86_fcos
Ix86_fucom
Ix86_fucomp
Ix86_fucompp
Ix86_setalc
Ix86_svdc
Ix86_rsdc
Ix86_svldt
Ix86_rsldt
Ix86_svts
Ix86_rsts
Ix86_icebp
Ix86_loadall
Ix86_emms
Ix86_movd
Ix86_movq
Ix86_packsswb
Ix86_packssdw
Ix86_packuswb
Ix86_paddb
Ix86_paddw
Ix86_paddd
Ix86_paddsb
Ix86_paddsw
Ix86_paddusb
Ix86_paddusw
Ix86_pand
Ix86_pandn
Ix86_pcmpeqb
Ix86_pcmpeqw
Ix86_pcmpeqd
Ix86_pcmpgtb
Ix86_pcmpgtw
Ix86_pcmpgtd
Ix86_pmaddwd
Ix86_pmulhw
Ix86_pmullw
Ix86_por
Ix86_psllw
Ix86_pslld
Ix86_psllq
Ix86_psraw
Ix86_psrad
Ix86_psrlw
Ix86_psrld
Ix86_psrlq
Ix86_psubb
Ix86_psubw
Ix86_psubd
Ix86_psubsb
Ix86_psubsw
Ix86_psubusb
Ix86_psubusw
Ix86_punpckhbw
Ix86_punpckhwd
Ix86_punpckhdq
Ix86_punpcklbw
Ix86_punpcklwd
Ix86_punpckldq
Ix86_pxor
Ix86_fxsave
Ix86_fxrstor
Ix86_sysenter
Ix86_sysexit
Ix86_pavgusb
Ix86_pfadd
Ix86_pfsub
Ix86_pfsubr
Ix86_pfacc
Ix86_pfcmpge
Ix86_pfcmpgt
Ix86_pfcmpeq
Ix86_pfmin
Ix86_pfmax
Ix86_pi2fd
Ix86_pf2id
Ix86_pfrcp
Ix86_pfrsqrt
Ix86_pfmul
Ix86_pfrcpit1
Ix86_pfrsqit1
Ix86_pfrcpit2
Ix86_pmulhrw
Ix86_femms
Ix86_prefetch
Ix86_prefetchw
Ix86_addps
Ix86_addss
Ix86_andnps
Ix86_andps
Ix86_cmpps
Ix86_cmpss
Ix86_comiss
Ix86_cvtpi2ps
Ix86_cvtps2pi
Ix86_cvtsi2ss
Ix86_cvtss2si
Ix86_cvttps2pi
Ix86_cvttss2si
Ix86_divps
Ix86_divss
Ix86_ldmxcsr
Ix86_maxps
Ix86_maxss
Ix86_minps
Ix86_minss
Ix86_movaps
Ix86_movhlps
Ix86_movhps
Ix86_movlhps
Ix86_movlps
Ix86_movmskps
Ix86_movss
Ix86_movups
Ix86_mulps
Ix86_mulss
Ix86_orps
Ix86_rcpps
Ix86_rcpss
Ix86_rsqrtps
Ix86_rsqrtss
Ix86_shufps
Ix86_sqrtps
Ix86_sqrtss
Ix86_stmxcsr
Ix86_subps
Ix86_subss
Ix86_ucomiss
Ix86_unpckhps
Ix86_unpcklps
Ix86_xorps
Ix86_pavgb
Ix86_pavgw
Ix86_pextrw
Ix86_pinsrw
Ix86_pmaxsw
Ix86_pmaxub
Ix86_pminsw
Ix86_pminub
Ix86_pmovmskb
Ix86_pmulhuw
Ix86_psadbw
Ix86_pshufw
Ix86_maskmovq
Ix86_movntps
Ix86_movntq
Ix86_prefetcht0
Ix86_prefetcht1
Ix86_prefetcht2
Ix86_prefetchnta
Ix86_sfence
Ix86_cmpeqps
Ix86_cmpltps
Ix86_cmpleps
Ix86_cmpunordps
Ix86_cmpneqps
Ix86_cmpnltps
Ix86_cmpnleps
Ix86_cmpordps
Ix86_cmpeqss
Ix86_cmpltss
Ix86_cmpless
Ix86_cmpunordss
Ix86_cmpneqss
Ix86_cmpnltss
Ix86_cmpnless
Ix86_cmpordss
Ix86_pf2iw
Ix86_pfnacc
Ix86_pfpnacc
Ix86_pi2fw
Ix86_pswapd
Ix86_fstp1
Ix86_fcom2
Ix86_fcomp3
Ix86_fxch4
Ix86_fcomp5
Ix86_ffreep
Ix86_fxch7
Ix86_fstp8
Ix86_fstp9
Ix86_addpd
Ix86_addsd
Ix86_andnpd
Ix86_andpd
Ix86_clflush
Ix86_cmppd
Ix86_cmpsd
Ix86_comisd
Ix86_cvtdq2pd
Ix86_cvtdq2ps
Ix86_cvtpd2dq
Ix86_cvtpd2pi
Ix86_cvtpd2ps
Ix86_cvtpi2pd
Ix86_cvtps2dq
Ix86_cvtps2pd
Ix86_cvtsd2si
Ix86_cvtsd2ss
Ix86_cvtsi2sd
Ix86_cvtss2sd
Ix86_cvttpd2dq
Ix86_cvttpd2pi
Ix86_cvttps2dq
Ix86_cvttsd2si
Ix86_divpd
Ix86_divsd
Ix86_lfence
Ix86_maskmovdqu
Ix86_maxpd
Ix86_maxsd
Ix86_mfence
Ix86_minpd
Ix86_minsd
Ix86_movapd
Ix86_movdq2q
Ix86_movdqa
Ix86_movdqu
Ix86_movhpd
Ix86_movlpd
Ix86_movmskpd
Ix86_movntdq
Ix86_movnti
Ix86_movntpd
Ix86_movq2dq
Ix86_movsd
Ix86_movupd
Ix86_mulpd
Ix86_mulsd
Ix86_orpd
Ix86_paddq
Ix86_pause
Ix86_pmuludq
Ix86_pshufd
Ix86_pshufhw
Ix86_pshuflw
Ix86_pslldq
Ix86_psrldq
Ix86_psubq
Ix86_punpckhqdq
Ix86_punpcklqdq
Ix86_shufpd
Ix86_sqrtpd
Ix86_sqrtsd
Ix86_subpd
Ix86_subsd
Ix86_ucomisd
Ix86_unpckhpd
Ix86_unpcklpd
Ix86_xorpd
Ix86_syscall
Ix86_sysret
Ix86_swapgs
AddCodeXref
AddConstEx
AddEntryPoint
AddEnum
AddHotkey
AddSeg
AddSourceFile
AddStrucEx
AddStrucMember
Add_dref
AltOp
AnalyzeArea
AppendFchunk
ApplySig
AskAddr
AskFile
AskIdent
AskLong
AskSeg
AskSelector
AskStr
AskYN
Atoa
AutoMark
AutoMark2
AutoUnmark
Batch
BeginTypeUpdating
Byte
ChangeConfig
ChooseFunction
Comment
CompileIDC
CreateArray
DbgByte
DbgDword
DbgQword
DbgRead
DbgWord
DbgWrite
DelArrayElement
DelCodeXref
DelConstEx
DelEnum
DelExtLnA
DelExtLnB
DelFixup
DelFunction
DelHashElement
DelHiddenArea
DelHotkey
DelLineNumber
DelSeg
DelSelector
DelSourceFile
DelStruc
DelStrucMember
Del_dref
DeleteAll
DeleteArray
Demangle
Dfirst
DfirstB
Dnext
DnextB
Dword
EndTypeUpdating
Exec
ExecIDC
Exit
ExtLinA
ExtLinB
FindBinary
FindCode
FindData
FindExplored
FindFuncEnd
FindImmediate
FindSelector
FindText
FindUnexplored
FindVoid
FirstFuncFchunk
FirstSeg
get_ascii_str
GenerateFile
GetArrayId
GetBmaskCmt
GetBmaskName
GetCharPrm
GetColor
GetConstBmask
GetConstByName
GetConstCmt
GetConstEnum
GetConstEx
GetConstName
GetConstValue
GetCurrentLine
GetCustomDataFormat
GetCustomDataType
GetDisasm
GetEntryName
GetEntryOrdinal
GetEntryPoint
GetEntryPointQty
GetEnum
GetEnumCmt
GetEnumFlag
GetEnumIdx
GetEnumName
GetEnumQty
GetEnumSize
GetEnumWidth
GetFchunkAttr
GetFchunkReferer
GetFirstBmask
GetFirstConst
GetFirstHashKey
GetFirstIndex
GetFirstMember
GetFirstStrucIdx
GetFixupTgtDispl
GetFixupTgtOff
GetFixupTgtSel
GetFixupTgtType
GetFlags
GetFrame
GetFrameArgsSize
GetFrameLvarSize
GetFrameRegsSize
GetFrameSize
GetFuncOffset
GetFunctionAttr
GetFunctionCmt
GetFunctionFlags
GetFunctionName
GetHashLong
GetHashString
GetIdaDirectory
GetIdbPath
GetInputFile
GetInputFilePath
GetInputMD5
GetLastBmask
GetLastConst
GetLastHashKey
GetLastIndex
GetLastMember
GetLastStrucIdx
GetLineNumber
GetLocalType
GetLocalTypeName
GetLongPrm
GetManualInsn
GetMarkComment
GetMarkedPos
GetMaxLocalType
GetMemberComment
GetMemberFlag
GetMemberName
GetMemberOffset
GetMemberQty
GetMemberSize
GetMemberStrId
GetMinSpd
GetMnem
GetNextBmask
GetNextConst
GetNextFixupEA
GetNextHashKey
GetNextIndex
GetNextStrucIdx
GetOpType
GetOperandValue
GetOpnd
GetOriginalByte
GetOriginalDword
GetOriginalWord
GetPrevBmask
GetPrevConst
GetPrevFixupEA
GetPrevHashKey
GetPrevIndex
GetPrevStrucIdx
GetReg
GetSegmentAttr
GetShortPrm
GetSourceFile
GetSpDiff
GetSpd
GetString
GetStringType
GetStrucComment
GetStrucId
GetStrucIdByName
GetStrucIdx
GetStrucName
GetStrucNextOff
GetStrucPrevOff
GetStrucQty
GetStrucSize
GetTrueName
GetTrueNameEx
GetnEnum
GetType
GuessType
HideArea
HideName
IDA_version
IdpName
IsBitfield
is_debugged
IsPublicName
IsUnion
ItemEnd
ItemHead
ItemSize
Jump
LineA
LineB
load_ids
loader_name
LoadTil
LocByName
LocByNameEx
MK_FP
MakeAlign
MakeArray
MakeByte
MakeCode
MakeComm
MakeData
MakeDouble
MakeDword
MakeFloat
MakeFrame
MakeFunction
MakeLocal
MakeName
MakeNameEx
MakeNameNonPublic
MakeNamePublic
MakeOword
MakePackReal
MakeQword
MakeRptCmt
MakeStr
MakeStruct
MakeTbyte
MakeUnkn
MakeUnknRange
MakeVar
MakeWord
MarkPosition
Name
NameEx
NextAddr
NextFchunk
NextFuncFchunk
NextFunction
NextHead
NextNotTail
NextSeg
OpAlt
OpBinary
OpChr
OpDecimal
OpEnumEx
OpFloat
OpHex
OpHigh
OpNot
OpNumber
OpOctal
OpOff
OpOffEx
OpSeg
OpSign
OpStkvar
OpStroffEx
ParseTypes
PatchByte
PatchDbgByte
PatchDword
PatchWord
PrevAddr
PrevFchunk
PrevFunction
PrevHead
PrevNotTail
ProcessUiAction
Qword
RebaseProgram
RecalcSpd
Refresh
RefreshLists
RemoveFchunk
RenameArray
RenameEntryPoint
RenameSeg
Rfirst
Rfirst0
RfirstB
RfirstB0
Rnext
Rnext0
RnextB
RnextB0
RptCmt
RunPlugin
save_idb
ScreenEA
SegAddrng
SegAlign
SegBounds
SegByBase
SegByName
SegClass
SegComb
SegCreate
SegDefReg
SegDelete
SegEnd
SegName
SegRename
SegStart
SelEnd
SelStart
SetArrayFormat
SetArrayLong
SetArrayString
SetBmaskCmt
SetBmaskName
SetCharPrm
SetColor
SetConstCmt
SetConstName
SetEnumBf
SetEnumCmt
SetEnumFlag
SetEnumIdx
SetEnumName
SetEnumWidth
SetFchunkAttr
SetFchunkOwner
SetFixup
SetFlags
SetFunctionAttr
SetFunctionCmt
SetFunctionEnd
SetFunctionFlags
SetHashLong
SetHashString
SetHiddenArea
SetInputFilePath
SetLineNumber
SetLocalType
SetLongPrm
SetManualInsn
SetMemberComment
SetMemberName
SetMemberType
SetPrcsr
SetReg
SetSegmentType
SetSelector
SetShortPrm
SetSpDiff
SetStatus
SetStorageType
SetStrucComment
SetStrucIdx
SetStrucName
SetTargetAssembler
SetType
ShowName
Til2Idb
Wait
Word
XrefType
loadfile
readlong
readshort
readstr
savefile
strfill
writelong
writeshort
writestr
xtol
here
OpOffset
OpNum
OpChar
OpDec
OpSegment
);

1;
__END__
