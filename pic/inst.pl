#!/usr/bin/perl -w
# Script for generating of x86data.c from data and x86.h files
use warnings;

######## CONSTANT ########
# default filenames
$INC_FILE='x86.h';
$OUT_FILE='x86data.c';
$DATA_FILE='data';
# struct name
$STRUCT_NAME='struct RP_opcode';
$MAIN_DATA='RP_data';
# section names
# pseudo section for struct names
$STRUCT='STRUCT';
$TYPE  ='TYPE';
$FROM  ='FROM';
$REGS  ='REGS';
$OP    ='OP';
$CFLAGS='CFLAGS';
$RFLAGS='RFLAGS';
$UFLAGS='UFLAGS';
%allowed_regz = ( 
 'EAX' => 0,
 'ECX' => 1,
 'EDX' => 2,
 'EBX' => 3,
 'ESP' => 4,
 'EBP' => 5,
 'ESI' => 6,
 'EDI' => 7,
 'RAX' => 0,
 'RCX' => 1,
 'RDX' => 2,
 'RBX' => 3,
 'RSP' => 4,
 'RBP' => 5,
 'RSI' => 6,
 'RDI' => 7,
 'R8'  => 8,
 'R9'  => 9,
 'R10'  => 10,
 'R11'  => 11,
 'R12'  => 12,
 'R13'  => 13,
 'R14'  => 14,
 'R15'  => 15,
 'RIP'  => 28,
 'ES'  => 29,
 'CS'  => 30,
 'SS'  => 31,
 'DS'  => 32,
 'FS'  => 33,
 'GS'  => 34
);

######## INCLUDES ########
use Getopt::Std;

sub usage
{
 printf <<EOF;
 x86 opcodes manipulation program. Options:
 -c file	Check for errors, error report place in file
 -d file	Set data file (default $DATA_FILE)
 -i file	Set include file (default $INC_FILE)
 -n file	Generate new skeleton file
 -o file	Set output file (default $OUT_FILE)
 -s 		Skip doubtfull instructions (marked with ???)
 -? 		Shows this help screen
EOF
 exit;
}

######## MAIN ########
# for command line args parsing
my %opts;
# for opcodez hash
my(%opcodez, %opcodez2);
# for error handling
my(@errorz);
# max opcode value
my($str, $name, $value, $max_opcode);

# счётчик строк
my $N = 0;
# типа, сама база данных
my(%datas);
my($ref);

# read command line args
getopts('c:d:i:n:o:?', \%opts);

usage if ( exists($opts{'?'}) );

if ( exists($opts{'i'}) )
{
  $INC_FILE = $opts{'i'};
  $INC_FILE =~ s/^\s*//;
  $INC_FILE =~ s/\s*$//;
}

if ( exists($opts{'o'}) )
{
  $OUT_FILE = $opts{'o'};
  $OUT_FILE =~ s/^\s*//;
  $OUT_FILE =~ s/\s*$//;
}

# read include file
open(IN, $INC_FILE) or die("Cannot open include file \"$INC_FILE\" ($!)");
$max_opcode = 0;
while($str = <IN>)
{
  chomp $str;
  $str =~ s/^\s*//;
  $str =~ s/\s*$//;
  next if ( exists($opts{'s'}) and $str =~ /\?\?\?/ );
  next if ( $str !~ /^#define\s*Ix86_(.*)$/ );
  $str = $1;
  $str =~ s/\/\*.*\*\///g;
  ( $name, $value ) = ( split /[ \t]+/, $str );
  $name =~ s/\s*$//;
  $value =~ s/^\s*//;
  $value = int($value);
  $max_opcode = $value if ( $value > $max_opcode );
  if ( exists($opcodez{$value}) )
  {
   push(@errorz, "Duplicates values for " . $value . ": old was " . $opcodez{$value} . " and new is " . $name );
  }
  $opcodez{$value} = $name;
}

# if just check for errors in include file
if ( exists($opts{'c'}) )
{
  $name = $opts{'c'};
  $name =~ s/^\s*//;
  $name =~ s/\s*$//;
  usage if ( ! $name or $name =~ /^-/ );
  open(CHECK, '>' . $name) or die("Cannot open error report file \"$name\", ($!)");
  if ( 0 != (@errorz) )
  {
    foreach $str (@errorz)
    {
      printf(CHECK $str . "\n");
    }
  }
  for ( $str = 1; $str <= $max_opcode; $str++ )
  {
    if ( ! exists($opcodez{$str}) )
    {
     printf(CHECK "No inctruction for %d opcode !\n", $str);
    }
  }
  close CHECK;
  if ( -z $name )
  {
    printf("No errors\n");
    unlink($name);
  }
  exit;
}

# Create skeleton file
if ( exists($opts{'n'}) )
{
 $name = $opts{'n'};
 $name =~ s/^\s*//;
 $name =~ s/\s*$//;
 usage if ( ! $name or $name =~ /^-/ );
 die("$name already exists") if ( -f $name );
 open(SKEL, '>' . $name) or die("Cannot open skeleton file \"$name\", ($!)");
 for ( $str = 1; $str <= $max_opcode; $str++ )
 {
   printf(SKEL "[%s]\n\n", $opcodez{$str} ) if ( exists($opcodez{$str}) );
 }
 close(SKEL);
 exit;
}

# вторую сделаем для быстрого поиска
while( ($value, $name) = each (%opcodez) )
{
 $opcodez2{$name} = $value;
}

sub process_flags
{
  my($data, $what) = @_;
  my(%cf, $str);

  foreach $str (split(/[\s,|]+/, $data))
  {
    if ( exists($cf{$str}) )
    {
      printf("Warning: line %d, duplicated $what %s, ignored\n", $N, $str);
      next;
    }
    $cf{$str} = 1;
  }
  return join(' | ', map { 'f_' . $_ } sort { $a cmp $b } (keys %cf) );
}

sub process_line
{
  my ($ref, $str) = @_;
  my($section, $data);
  if ( $str !~ /^(.*):(.*)$/ )
  {
    printf("Line %d: bad format\n", $N );
    return;
  }
  $section = $1;
  $data = $2;
  $section =~ s/^\s*//;
  $section =~ s/\s*$//;
  $data =~ s/^\s*//;
  $data =~ s/\s*$//;
  return if ( !$section or !$data );
  $section = uc($section);
  $data = uc($data);
  # основная обработка 
  #####=- тип инструкции
  if ( $section eq $TYPE )
  {
    # types: 3D FPU U MMX SIMD
    if ( $data ne '3D'   and
         $data ne 'U'    and
         $data ne 'FPU'  and
         $data ne 'MMX'  and
         $data ne 'SSE'  and
         $data ne 'SSE3' and
         $data ne 'SSSE3'
       )
    {
      printf("Error: line %d, unknown $TYPE \"%s\"\n", $N, $data);
      return;
    }
    if ( exists($ref->{$TYPE}) )
    {
      printf("Error: line %d, duplicated data for $TYPE\n", $N);
    } else {
      $data = 'AMD_3D' if ( $data eq '3D' );
      $data = 'UNKNOWN_IT' if ( $data eq 'U' );
      $ref->{$TYPE} = $data;
    }
    return;
  }
  #####=- с какого проца
  if ( $section eq $FROM )
  {
    # processor types: 486 P PPro PII
    if ( $data ne '486' and
         $data ne 'P' and
         $data ne 'PPRO' and
         $data ne 'P4' and
         $data ne 'PII' )
    {
      printf("Error: line %d, unknown processor type \"%s\"\n", $N, $data);
      return;
    }
    if ( exists($ref->{$FROM}) )
    {
      printf("Error: line %d, duplicated data for $FROM\n", $N);
    } else {
      $ref->{$FROM} = 'FROM_' . $data;
    }
    return;
  }
  #####=- changed op
  if ( $section eq $OP )
  {
    if ( exists($ref->{$OP}) )
    {
      printf("Error: line %d, duplicated data for $OP\n", $N);
      return;
    }
    my $op = 0;
    foreach $section (split(/[\s,]+/, $data))
    {
      if ( $section < 1 or $section > 3 )
      {
        printf("Error: line %d, operand must be between 1 and 3\n", $N);
        next;
      }
      if ( $op & (1 << ($section-1)) )
      {
        printf("Warning: line %d, duplicated $OP, ignored\n", $N);
        next;
      }
      $op |= (1 << ($section-1));
    }
    $ref->{$OP} = $op;
    return;
  }
  #####=- изменяемые регистры
  if ( $section eq $REGS )
  {
    if ( exists($ref->{$REGS}) )
    {
      printf("Error: line %d, duplicated data for $REGS\n", $N);
      return;
    }
    my(%regs);
    foreach $section (split(/[\s,|]+/, $data))
    {
      if ( $section eq 'AH' or $section eq 'AL' or $section eq 'AX' )
      {
        printf("Warning, line %d: change %s to EAX\n", $N, $section);
        $section = 'EAX';
      } elsif ( $section eq 'BH' or $section eq 'BL' or $section eq 'BX' )
      {
        printf("Warning, line %d: change %s to EBX\n", $N, $section);
        $section = 'EBX';
      } elsif ( $section eq 'CH' or $section eq 'CL' or $section eq 'CX' )
      {
        printf("Warning, line %d: change %s to ECX\n", $N, $section);
        $section = 'ECX';
      } elsif ( $section eq 'DH' or $section eq 'DL' or $section eq 'DX' )
      {
        printf("Warning, line %d: change %s to EDX\n", $N, $section);
        $section = 'EDX';
      }
      if ( exists($regs{$section}) )
      {
        printf("Warning: line %d, duplicated $REGS %s, ignored\n", $N, $section);
        next;
      }
      if ( !exists($allowed_regz{$section}) )
      {
        printf("Error: line %d, unknown $REGS %s, ignored\n", $N, $section);
        next;
      }
      $regs{$section} = $allowed_regz{$section};
    }
    $data = join(' | ', map { '(1 << r_' . $_ . ')' } sort { $regs{$a} <=> $regs{$b} } (keys %regs) );
    $ref->{$REGS} = $data if ( defined($data) and $data );
    return;
  }
  #####=- изменяемые флаги
  if ( $section eq $CFLAGS )
  {
    if ( exists($ref->{$CFLAGS}) )
    {
      printf("Error: line %d, duplicated data for $CFLAGS\n", $N);
      return;
    }
    $data = process_flags($data, $CFLAGS);
    $ref->{$CFLAGS} = $data if ( defined($data) and $data );
    return;
  }
  #####=- дальше аналогично
  if ( $section eq 'RFLAGS' )
  {
    if ( exists($ref->{$RFLAGS}) )
    {
      printf("Error: line %d, duplicated data for $RFLAGS\n", $N);
      return;
    }
    $data = process_flags($data, $RFLAGS);
    $ref->{$RFLAGS} = $data if ( defined($data) and $data );
    return;
  }
  #####=-
  if ( $section eq 'UFLAGS' )
  {
    if ( exists($ref->{$UFLAGS}) )
    {
      printf("Error: line %d, duplicated data for $UFLAGS\n", $N);
      return;
    }
    $data = process_flags($data, $UFLAGS);
    $ref->{$UFLAGS} = $data if ( defined($data) and $data );
    return;
  }
  # crX flags now just ignored
  return if ( $section eq 'FCFLAGS' or $section eq 'FUFLAGS' );
  printf("Warning: line %d: unknown data \"%s\"\n", $N, $section );
}

# Нда.. Типа, функция сравнения двух hash для оптимизации
# Аргументы: ссылки на hashы, содержимое к-рых нужно сравнить
# PS:
# 1) при сравнении не учитываются поля $STRUCT
# 2) все данные - строки, кроме $OP
sub cmp_2data
{
  my($ref_a, $ref_b) = @_;
  my(%props, $name, $value);

  foreach $name ( keys %$ref_a )
  {
###DEBUG: printf("Prop %s\n", $name);
    $props{$name} = 1 if ( $name ne $STRUCT );
  }
# Strange bug occurs when I used
# while( ($name, $value) = each (keys %$ref_b) ) ...
  foreach $name (keys %$ref_b)
  {
    $value = $ref_b->{$name};
###DEBUG: printf("%s -> %s\n", $name, $value );
    next if ( $name eq $STRUCT );
    if ( $name eq $OP )
    {
      return 0 if ( !exists($ref_a->{$name}) or $value != $ref_a->{$name} );
    } else
    {
      return 0 if ( !exists($ref_a->{$name}) or $value ne $ref_a->{$name} );
    }
###DEBUG: printf("Name %s match\n", $name);
    delete $props{$name};
  }
###DEBUG:foreach $name ( keys %props )
###DEBUG:{
###DEBUG:  printf("Remains %s\n", $name);
###DEBUG:}
  return ( 0 == ( keys %props ) );
}

# типа, по умолчанию сгородить выходной файл
$name = $opts{'d'} || $DATA_FILE;
$name =~ s/^\s*//;
$name =~ s/\s*$//;
usage if ( ! $name or $name =~ /^-/ );
$DATA_FILE = $name;
die("$OUT_FILE already exists") if ( -f $OUT_FILE );
$N = 0;
open(DATA, $DATA_FILE) or die("Cannot open data file \"$DATA_FILE\", ($!)");
# читаем data и парзим
while( $str = <DATA> )
{
  chomp $str;
  $str =~ s/^\s*//;
  $str =~ s/\s*$//;
  $N++;
  next if ( ! $str or $str =~ /^\#/ );
  if ( $str =~ /\[(\S+)\]/ )
  {
    $name = $1;
    if ( ! exists($opcodez2{$name}) )
    {
      printf("Unknown opcode \"$name\"\n");
      next;
    }
    die("Duplicated entries for \"$name\"\n") if ( exists($datas{$name}) );
    $datas{$name} = {};
    $ref = $datas{$name};
    next;
  }
  process_line($ref, $str);
}
close(DATA);
# заоптимизируем
my(@already_mustbe);
optimize:
while ( ($name, $value) = each(%datas) )
{
  foreach $str ( @already_mustbe )
  {
###DEBUG:printf("%s vs %s\n", $str, $name );
    if ( cmp_2data($value, $datas{$str}) )
    {
      $value->{$STRUCT} = $str;
###DEBUG:printf("Optimize: %s like %s\n", $name, $str );
      next optimize;
    }
  }
  push @already_mustbe, $name;
  $value->{$STRUCT} = $name;
}

# типа, самая главная функция
# Поля структуры:
# type -> $TYPE
# from -> $FROM
# regs -> $REGS
# cflags -> $CFLAGS
# rflags -> $RFLAGS
# uflags -> $UFLAGS
# op -> $OP
#
sub print_struct
{
 my($name, $ref) = @_;
 printf(OUT "const %s opcode_%s = {\n", $STRUCT_NAME, $name );
 # type
 printf(OUT "\t%s,\n", exists($ref->{$TYPE}) ? $ref->{$TYPE} : "0" );
 # from
 printf(OUT "\t%s,\n", exists($ref->{$FROM}) ? $ref->{$FROM} : "0" );
 # regs
 printf(OUT "\t%s,\n", exists($ref->{$REGS}) ? $ref->{$REGS} : "0" );
 # cflags
 printf(OUT "\t%s,\n", exists($ref->{$CFLAGS}) ? $ref->{$CFLAGS} : "0" );
 # rflags
 printf(OUT "\t%s,\n", exists($ref->{$RFLAGS}) ? $ref->{$RFLAGS} : "0" );
 # uflags
 printf(OUT "\t%s,\n", exists($ref->{$UFLAGS}) ? $ref->{$UFLAGS} : "0" );
 # op
 printf(OUT "\t%d\n", exists($ref->{$OP}) ? $ref->{$OP} : "0" );
 printf(OUT "};\n\n");
}

# теперь городим выходной файл
open(OUT, '>' . $OUT_FILE) or die("Cannot open output file \"$OUT_FILE\", ($!)");

# header
print OUT <<EOF;
/* Warning ! this file generated automatically with inst.pl
   Don`t edit it manually
 */
#include \"$INC_FILE\"

/* for NULL declaration */
#include <stdlib.h>

EOF

foreach $name (sort { $a cmp $b} @already_mustbe)
{
 print_struct($name, $datas{$name});
}

# header for main struct
print OUT <<EOF;
const $STRUCT_NAME *const $MAIN_DATA\[\] = {
EOF

for ( $name = 1; $name <= $max_opcode; $name++ )
{
 if ( !exists($opcodez{$name}) )
 {
   printf(OUT "/* %d */\tNULL", $name);
 } else {
   if ( exists $datas{$opcodez{$name}}->{$STRUCT} )
   {
     printf(OUT "/* %d eq %s */\t\&opcode_%s", 
       $name, $opcodez{$name}, $datas{$opcodez{$name}}->{$STRUCT} 
     );
   } else {
     printf(OUT "/* %d eq %s */\tNULL", $name, $opcodez{$name});
   }
 }
 printf(OUT ",\n") if ( $name != $max_opcode );
}

# footer
print OUT<<EOF;
 };
EOF
close(OUT);