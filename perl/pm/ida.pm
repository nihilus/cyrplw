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

#
# op_t.type
#                  Description                          Data field
use constant o_void     =>  0; #  No Operand                           ----------
use constant o_reg      =>  1; #  General Register (al,ax,es,ds...)    reg
use constant o_mem      =>  2; #  Direct Memory Reference  (DATA)      addr
use constant o_phrase   =>  3; #  Memory Ref [Base Reg + Index Reg]    phrase
use constant o_displ    =>  4; #  Memory Reg [Base Reg + Index Reg + Displacement] phrase+addr
use constant o_imm      =>  5; #  Immediate Value                      value
use constant o_far      =>  6; #  Immediate Far Address  (CODE)        addr
use constant o_near     =>  7; #  Immediate Near Address (CODE)        addr
use constant o_idpspec0 =>  8; #  IDP specific type
use constant o_idpspec1 =>  9; #  IDP specific type
use constant o_idpspec2 => 10; #  IDP specific type
use constant o_idpspec3 => 11; #  IDP specific type
use constant o_idpspec4 => 12; #  IDP specific type
use constant o_idpspec5 => 13; #  IDP specific type
use constant o_last     => 14; #  first unused type
#
# op_t.dtyp
#
use constant dt_byte     => 0; #  8 bit
use constant dt_word     => 1; #  16 bit
use constant dt_dword    => 2; #  32 bit
use constant dt_float    => 3; #  4 byte
use constant dt_double   => 4; #  8 byte
use constant dt_tbyte    => 5; #  variable size (ph.tbyte_size)
use constant dt_packreal => 6; #  packed real format for mc68040
use constant dt_qword    => 7; #  64 bit
use constant dt_byte16   => 8; #  128 bit
use constant dt_code     => 9; #  ptr to code (not used?)
use constant dt_void     => 10; #  none
use constant dt_fword    => 11; #  48 bit
use constant dt_bitfild  => 12; #  bit field (mc680x0)
use constant dt_string   => 13; #  pointer to asciiz string
use constant dt_unicode  => 14; #  pointer to unicode string
use constant dt_3byte    => 15; #  3-byte data
use constant dt_ldbl     => 16; #  long double (which may be different from tbyte)
use constant dt_byte32   => 17; # 256 bit
use constant dt_byte64   => 18; # 512 bit

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

use constant FF_IVL   => 0x00000100;
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

###
#
# F U N C T I O N S
#
###
sub isLoaded
{
  my $flags = GetFlags(shift);
  return ($flags & FF_IVL) != 0;
}

sub isCode
{
  my $flags = GetFlags(shift);
  return ($flags & MS_CLS) == FF_CODE;
}

sub isData
{
  my $flags = GetFlags(shift);
  return ($flags & MS_CLS) == FF_DATA;
}

sub isUnknown
{
  my $flags = GetFlags(shift);
  return ($flags & MS_CLS) == FF_UNK;
}

sub isByte
{
  my $flags = GetFlags(shift);
  return (($flags & MS_CLS) == FF_DATA) &&
         (($flags & DT_TYPE) == FF_BYTE)
  ;
}

sub isWord
{
  my $flags = GetFlags(shift);
  return (($flags & MS_CLS) == FF_DATA) &&
         (($flags & DT_TYPE) == FF_WORD)
  ;
}

sub isDwrd
{
  my $flags = GetFlags(shift);
  return (($flags & MS_CLS) == FF_DATA) &&
         (($flags & DT_TYPE) == FF_DWRD)
  ;
}

sub isQwrd
{
  my $flags = GetFlags(shift);
  return (($flags & MS_CLS) == FF_DATA) &&
         (($flags & DT_TYPE) == FF_QWRD)
  ;
}

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
func_n
func_qty
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
isLoaded
isCode
isData
isUnknown
isByte
isWord
isDwrd
isQwrd
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
MakeUnknown
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
NextUnknown
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
PrevUnknown
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
ToggleBnot
ToggleSign
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
o_void
o_reg
o_mem
o_phrase
o_displ
o_imm
o_far
o_near
o_idpspec0
o_idpspec1
o_idpspec2
o_idpspec3
o_idpspec4
o_idpspec5
o_last
dt_byte
dt_word
dt_dword
dt_float
dt_double
dt_tbyte
dt_packreal
dt_qword
dt_byte16
dt_code
dt_void
dt_fword
dt_bitfild
dt_string
dt_unicode
dt_3byte
dt_ldbl
dt_byte32
dt_byte64
ua_ana
get_mnem
get_op
ad16
ad32
ad64
op16
op32
);

1;
__END__
