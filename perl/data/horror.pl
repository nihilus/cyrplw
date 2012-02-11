#!/usr/bin/perl -w
#
# Read and make full IDC functions prototypes
# (C) RedPlait (redp@mail.ru), 31 DEC 2001
# 
# Added support of stdcall for IDCFuncs and @implemented array
#  1 Oct 2004 (C) RedPlait
#
# Added memset for string result from IDCFuncs because some functions
# don`t fill this struct for bad result
#  22 Dec 2004 (C) RedPlait
# 
# 'long' from IDC now will be 'unsigned long' (not just 'long') in C and Perl
#  25 Dec 2004 (C) RedPlait
#
# Add support for VT_STR2
#  26 jul 2011 (C) RedPlait
#
# Move debugger interface to different files
#   3 Aug 2011 (C) RedPlait

# Storage format for each function:
#  hash, where key is name and value is ref to hash
#   where keys is 'r' for result, 'i' for index in IDC funcs table
#   and 'a' is ref to array of parameters
# // yeah, little lisp like :-)
#

use Getopt::Std;
use vars qw/$opt_i $opt_m $opt_p $opt_t/;

# globals
$IDC_IDC = '../../../../idc/idc.idc';
$MY_FILE = 'idc.out';
# outpit files names
$XS_FILE = 'IDA.xs';
$PM_FILE = 'ida.pm';
$I_SWIG  = 'ida.i';
$C_FILE	 = 'ida.cpp';
$H_FILE  = 'ida.h';
# big mama array name
$ARRAY   = 'RP_Funcs';

sub usage
{
  printf <<EOF;
 Options:
 -i file	Name of IDC.IDC (default $IDC_IDC)                            
 -m file	Name of extracted IDC functions descriptions (default $MY_FILE)
 -p		Print internal functions representing and exit
 -t [xs|pm|i|c|h] Type of output (Perl XS/Perl PM/SWIG interface/C files)
 -?		Shows this help screen
EOF
  exit 8;
}

#list of recognized IDC functions return values
%results = (
 'success' => 1,
 'long'    => 1,
 'int'     => 1,
 'char'    => 1,
 'string'  => 1,
 'void'    => 1
);

# list of functions wich I will implemented by myself (to emit marshalling to IDC functions)
@implemented = qw(
 MakeByte
 MakeWord
 MakeDword
 MakeQword
 MakeOword
 MakeFloat
 MakeDouble
 MakePackReal
 MakeTbyte
 MakeUnkn
 OpBinary
 OpOctal
 OpDecimal
 OpHex
 OpChr
 OpNumber
 PatchByte
 PatchWord
 PatchDword
 GetIdbPath
 GetFlags
 Byte
 Word
 Dword
 Jump
 RunPlugin
 MakeComm
 MakeRptCmt
 GetInputFile
 GetInputFilePath
 ScreenEA
 SetStatus
 GetEntryPointQty
 GetEntryPoint
 GetStrucQty
 GetOriginalByte
);

# list of ignored IDC functions (those names conflicted with C RunTime library 
# or can be implemented in Perl much better)
my @ignored_IDC = qw(
 sprintf
 fprintf
 ftell
 xtol
 atol
 fputc
 filelength
 fseek
 strlen
 fclose
 ltoa
 fgetc
 strstr
 substr
 fopen
 Sleep
 rename
 trim
 mkdir
 unlink
 rotate_left
 CompileEx
);

# Debugger interface functions
my %dbg_idc = (
 'DbgByte' => 1,
 'DbgDword' => 1,
 'DbgQword' => 1,
 'DbgRead' => 1,
 'DbgWord' => 1,
 'DbgWrite' => 1,
 'PatchDbgByte' => 1,
 'LoadDebugger' => 1,
 'StartDebugger' => 1,
 'StopDebugger' => 1,
 'PauseProcess' => 1,
 'GetProcessQty' => 1,
 'GetProcessPid' => 1,
 'GetProcessName' => 1,
 'AttachProcess' => 1,
 'DetachProcess' => 1,
 'GetThreadQty' => 1,
 'GetThreadId' => 1,
 'GetCurrentThreadId' => 1,
 'SelectThread' => 1,
 'SuspendThread' => 1,
 'ResumeThread' => 1,
 'GetFirstModule' => 1,
 'GetNextModule' => 1,
 'GetModuleName' => 1,
 'GetModuleSize' => 1,
 'StepInto' => 1,
 'StepOver' => 1,
 'RunTo' => 1,
 'StepUntilRet' => 1,
 'GetDebuggerEvent' => 1,
 'RefreshDebuggerMemory' => 1,
 'TakeMemorySnapshot' => 1,
 'GetProcessState' => 1,
 'GetEventId' => 1,
 'GetEventPid' => 1,
 'GetEventTid' => 1,
 'GetEventEa' => 1,
 'IsEventHandled' => 1,
 'GetEventModuleName' => 1,
 'GetEventModuleBase' => 1,
 'GetEventModuleSize' => 1,
 'GetEventExitCode' => 1,
 'GetEventInfo' => 1,
 'GetEventBptHardwareEa' => 1,
 'GetEventExceptionCode' => 1,
 'GetEventExceptionEa' => 1,
 'CanExceptionContinue' => 1,
 'GetEventExceptionInfo' => 1,
 'SetDebuggerOptions' => 1,
 'SetRemoteDebugger' => 1,
 'GetExceptionQty' => 1,
 'GetExceptionCode' => 1,
 'GetExceptionName' => 1,
 'GetExceptionFlags' => 1,
 'DefineException' => 1,
 'SetExceptionFlags' => 1,
 'ForgetException' => 1,
 'GetRegValue' => 1,
 'SetRegValue' => 1,
 'GetBptQty' => 1,
 'GetBptEA' => 1,
 'GetBptAttr' => 1,
 'SetBptAttr' => 1,
 'SetBptCndEx' => 1,
 'AddBptEx' => 1,
 'DelBpt' => 1,
 'EnableBpt' => 1,
 'CheckBpt' => 1,
 'EnableTracing' => 1,
 'Appcall' => 1,
 'CleanupAppcall' => 1,
);

# list of IDC functions to need be renamed
%renamed_IDC = (
 'atoa'		=> 'Atoa',
 'add_dref'	=> 'Add_dref',
 'del_dref'	=> 'Del_dref',
 'Compile'      => 'CompileIDC'
);

sub is_implemented
{
  my $what = shift;
  my $str;
  foreach $str ( @implemented )
  {
    return 1 if ( $str eq $what );
  }
  return 0;
}

#
# Read IDC generated file
#
sub read_my_file
{
  my $f_hash = shift;
  open(IN, $MY_FILE)
    or die("Cannot open IDC extracted file '" . $MY_FILE . "' ($!)");
  my($name, $arg_ref, $arg, $str, $fh, $index);
  $index = 0;
  while($str = <IN>)
  {
     chomp $str;
     $str =~ s/^\s*//;
     $str =~ s/\s*$//;
     next if ( $str eq '' );
     next if ( $str !~ /^(\S+)/ );
     $name = $1;
     $str = $';
     $str =~ s/^\s*//;
     # check for existance of this function
     if ( exists $f_hash->{$name} )
     {
       warn("Duplicated definition of '" . $name . "'");
       next;
     }
     $f_hash->{$name} = {};
     $fh = $f_hash->{$name};
     $fh->{'i'} = $index;
     if ( $str ne '' ) # we dont have args for this function
     {
      $fh->{'a'} = [];
      $arg_ref = $fh->{'a'};
      foreach $arg ( split /\s+/, $str )
      {
        push @$arg_ref, $arg;
      }
     }
     $index++;
  }
  close IN;
}

#
# Read and parse IDC.IDC file
#
sub parse_IDC
{
  my $f_hash = shift;
  my($str, $res, $name, $status);
  open IN, $IDC_IDC
    or die("Cannot open IDC functions file '" . $IDC_IDC . "' ($!)");
  $status = 0;
  while( $str = <IN> )
  {
    chomp $str;
    if ( !$status )
    {
      $str =~ s/^\s*//;
      $str =~ s/\s*$//;
      $str =~ s/^\/\///;
      $str =~ s/^\s*//;
      $status = 1 if ( $str eq 'List of built-in functions' );
      next;
    }
    next if ( $str =~ /^\s+/ );
    next if ( $str =~ /^#/ );
    $str =~ s#\s*//.*$##;
    next if ( $str eq '' );
    next if ( $str !~ /;$/ );
    next if ( $str =~ m#^//# );
    next if ( $str !~ /^(\S+)\s+(\S+)\s*\(/ );
    $name = $2;
    $res  = $1;
    # check for existance
    if ( !exists $f_hash->{$name} )
    {
      warn("Unknown IDC function '" . $name . "'");
      next;
    }
    # check for return value
    if ( !exists $results{$res} )
    {
      warn("Unknown return value '" . $res . "' for function " . $name);
      $f_hash->{$name}->{'e'} = 0;
      next;
    }
    $f_hash->{$name}->{'r'} = $res;
  }
  close IN;
}
 
#
# Generator of code
# You can modify it to make binding to any other script engine
# (for example to Ruby, Lisp or Scheme :-)

sub form_result
{
  my $rtype = shift;
  return '' if ( !defined($rtype) or $rtype eq '' );
  if ( $rtype eq 'long' )
  {
    return 'unsigned long';
  }
  if ( $rtype eq 'int' )
  {
    return 'long';
  }
  if ( $rtype eq 'void' )
  {
    return 'void';
  }
  if ( $rtype eq 'success' )
  {
    return 'int';
  }
  if ( $rtype eq 'char' )
  {
    return 'char *';
  }
  if ( $rtype eq 'string' )
  {
    return 'char *';
  }
  return '';
}

# validate functions hash. If I cannot to do some function with strange result
# I put reason to 'e' hash node. There are following bad results:
#  0 - strange return value (this checks in parse_IDC)
#  1 - strange or unsupported (like ...) args
# Last update at 9 JAN 2001: if some function presented in ignore_IDC hash -
#  it will be simple removed from main hash
sub validate
{
  my $f_hash = shift;
  my($arg, $arg_ref, $name, $ref, $res);
  # remove some IDC functions
  foreach $name ( @ignored_IDC )
  {
    delete $f_hash->{$name};
  }
  # rename some functions
  while( ($name, $arg) = each %renamed_IDC )
  {
    next if ( !exists $f_hash->{$name} );
    $f_hash->{$arg} = $f_hash->{$name};
    delete $f_hash->{$name};
  }
  # do rest of processing
  while ( ($name, $ref) = each %$f_hash )
  {
    # check for debugger functions
    if ( exists $dbg_idc{$name} )
    {
      delete $f_hash->{$name};
      next;
    }
    next if ( exists $ref->{'e'} );
    $res = form_result($ref->{'r'});
    if ( !defined $res or $res eq '')
    {
      $ref->{'e'} = 0;
      next;
    }
    $arg_ref = $ref->{'a'};
    next if (! defined $arg_ref );	# nothing to check - no args
    foreach $arg ( @$arg_ref )
    {
      $ref->{'e'} = 1
       if ( $arg != 1 and $arg != 2 and $arg != 7 );
    }
  }
}

sub form_arg
{
  my $type = shift;
  if ( $type == 1 )
  {
    return 'char *';
  }
  if ( $type == 2 )
  {
    return 'long';
  }
  if ( $type == 7 )
  {
     return 'char *';
  }
  warn("Unknown arg type $type\n");
  return '';
}

##
## XS related functions
##
sub is_can_do_XS
{
  my $href = shift;
  my ($args, $arg);
  return 1
    if ( !exists $href->{'a'} );
  $args = $href->{'a'};
  foreach $arg ( @$args )
  {
    return 0 if ( '' eq form_arg $arg );
  }
  return 1;
}

# main horror
sub form_one_XS
{
  my($name,$href) = @_;
  my($res, $arg, $arg_ref, $arg_count, $index);
  $res = form_result $href->{'r'};
  if ( $res eq '' )
  {
    return 0;
  }
  printf("%s\n", $res);
  printf("%s(", $name);
  # form args
  if ( exists $href->{'a'} )
  {
    $arg_ref = $href->{'a'};
    $arg_count = scalar @$arg_ref;
    for ( $arg = 0; $arg < $arg_count; $arg++ )
    {
      printf(",") if ( $arg );
      printf("arg%d", $arg);
    }
  } else {
    $arg_count = 0;
  }
  printf(")\n");
  # args description
  if ( $arg_count )
  {
    $index = 0;
    foreach $arg ( @$arg_ref )
    {
      printf("\t%s\targ%d\n",
        form_arg($arg), $index);
      $index++;
    }
  }
  # preinit part
  printf("PREINIT:\n");
  printf("\tvoid *fp = %s->f[%d].fp;\n", $ARRAY, $href->{'i'} );
  printf("\tvalue_t res;\n");
  if ( $res eq 'char *' )
  {
    printf("\tmemset(&res, 0, sizeof(res));\n");
  }
  printf("\tvalue_t args[%d];\n", $arg_count )
    if ( $arg_count );
  # code part
  printf("CODE:\n");
  # init variables
  if ( $arg_count )
  {
    for ( $index = 0; $index < $arg_count; $index++ )
    {
      if ( $arg_ref->[$index] == 1 )
      {
        printf("\targs[%d].vtype = VT_STR;\n", $index);
        printf("\targs[%d].str = arg%d;\n", $index, $index);
        next;
      }
      if ( $arg_ref->[$index] == 2 )
      {
        printf("\targs[%d].vtype = VT_LONG;\n", $index);
        printf("\targs[%d].num = arg%d;\n", $index, $index);
        next;
      }
      die("Strange type " . $arg_ref->[$index] . " of argument in function '" . $name . "'");
    }
  }
  # call IDC func
  # Blja nah, IDA used Borland fastcall convention, so first param passed
  # in EAX and second in EDX
  # 1 OCT 2004 - in IDA 4.70 all functions in IDCFuncs array now stdcall
  # 		 so I changed asm code to meet new conversion calling
  printf(" __asm {\n");
  printf("   lea eax, res\n   push eax\n");
  if ( $arg_count )
  {
     printf("   lea eax, args\n   push eax\n");
  } else {
     printf("   xor eax, eax\n    push eax\n");
  }
  printf("   call [fp]\n}\n");
  # result
  if ( $res ne 'void' )
  {
    if ( $res eq 'long' or $res eq 'int' or $res eq 'unsigned long' )
    {
      printf("\tRETVAL = res.num;\n");
    } elsif ( $res eq 'char *' )
    {
      printf <<EOF;
	if ( res.c_str() == NULL )
	  RETVAL = NULL;
	else {
	  RETVAL = _strdup(res.c_str());
	  VarFree(&res);
	}
EOF
    }
    printf("OUTPUT:\n\tRETVAL\n");
  }
  printf "\n";
}

sub form_XS_header
{
  print <<EoH;
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
MODULE = IDA         PACKAGE = IDA

EoH
}

sub form_XS
{
  my $f_hash = shift;
  my($name,$ref);
  form_XS_header;
  foreach $name ( keys %$f_hash )
  {
    next if ( exists $f_hash->{$name}->{'e'} );
    if ( !is_can_do_XS($f_hash->{$name}) )
    {
      $ref = $f_hash->{$name};
      $ref->{'b'} = 1;
      next;
    }
    form_one_XS($name, $f_hash->{$name});
  }
}

##
## SWIG related functions. Warning - all use global filehandle OUT
##
sub produce_SWIG_header
{
  printf OUT <<'EoH';
%module IDA
%{

EoH
}

sub do_addition
{
  printf(OUT "extern int IDA_version(void);\n");
  printf(OUT "extern char *loader_name(void);\n");
  printf(OUT "extern int load_ids(char *);\n");
  printf(OUT "extern void save_idb(void);\n");
  printf(OUT "extern int is_debugged(void);\n");
  printf(OUT "extern long GetOriginalWord(long);\n");
  printf(OUT "extern long GetOriginalDword(long);\n");
  printf(OUT "extern void MakeUnknRange(long, long, int);\n");
  printf(OUT "extern int IsPublicName(long);\n");
  printf(OUT "extern void MakeNamePublic(long);\n");
  printf(OUT "extern void MakeNameNonPublic(long);\n");
  printf(OUT "extern void HideName(long);\n");
  printf(OUT "extern void ShowName(long);\n");
  printf(OUT "extern char *IdpName(void);\n");
}

sub make_flist
{
  my $hash = shift;
  my($name, $href, $arg_ref, $arg, $arg_count, $res);
  while ( ($name, $href) = each %$hash )
  {
    next if ( exists $href->{'e'} );
    $res = form_result $href->{'r'};
    printf(OUT "extern %s %s(", $res, $name);
    $arg_ref = $href->{'a'};
    if ( defined $arg_ref )
    {
      $arg_count = scalar @$arg_ref;
      for ( $arg = 0; $arg < $arg_count; $arg++ )
      {
        printf(OUT ",")
	  if ( $arg );
        printf(OUT "%s ", form_arg($arg_ref->[$arg]));
      }
    }
    printf(OUT ");\n");
  }
  do_addition;
}

sub produce_SWIG
{
  my $hash = shift;
  open (OUT, ">" . $I_SWIG)
    or die("Cannot create output file '" . $I_SWIG . "', ($!)");
  produce_SWIG_header;
  # make extern functions declarations to make compiler happy
  make_flist($hash);
  printf(OUT "%%}\n\n");
  # make real list
  make_flist($hash);
  close OUT; 
}

##
## PM related files
##
sub PM_header
{
print OUT <<'EoH';
package IDA;
require Exporter;
@ISA = qw(Exporter);
package IDA;
boot_IDA();
package IDA;

@EXPORT = qw(
EoH
}

sub PM_footer
{
print OUT <<'EoF';
);

1;
__END__
EoF
}

sub produce_PM
{
  my $hash = shift;
  my($name, $href);

  open (OUT, ">" . $PM_FILE)
    or die("Cannot create output file '" . $PM_FILE . "', ($!)");
  PM_header;
  foreach $name ( sort keys %$hash )
  {
    $href = $hash->{$name};
    next if ( exists $href->{'e'} );
    printf(OUT "%s\n", $name);
  }
  PM_footer;
  close OUT;
}

##
## H related files
##
sub H_header
{
print OUT <<'EoH';
#ifndef MY_IDA_H
# define MY_IDA_H

#include <ida.hpp>
#include <expr.hpp>

#if __cplusplus
 extern "C"
 {
#endif

extern funcset_t *RP_Funcs;

EoH
}

sub H_footer
{
print OUT <<'EoH'

#if __cplusplus
 };
#endif

#endif /* MY_IDA_H */
EoH
}

sub produce_H
{
  my $hash = shift;
  my($name, $href, $arg_ref, $arg, $arg_count, $res);

  open (OUT, ">" . $H_FILE)
    or die("Cannot create output file '" . $H_FILE . "', ($!)");
  H_header;
  while ( ($name, $href) = each %$hash )
  {
    next if ( exists $href->{'e'} );
    $res = form_result $href->{'r'};
    printf(OUT "%s %s(", $res, $name);
    $arg_ref = $href->{'a'};
    if ( defined $arg_ref )
    {
      $arg_count = scalar @$arg_ref;
      for ( $arg = 0; $arg < $arg_count; $arg++ )
      {
        printf(OUT ",")
	  if ( $arg );
        printf(OUT "%s ", form_arg($arg_ref->[$arg]));
      }
    }
    printf(OUT ");\n");
  }
  do_addition;
  H_footer;
  close OUT; 
}

##
## C related code
##
sub form_C_header
{
 print OUT <<EoH;
#include "ida.h"

EoH
}

sub make_C_function
{
  my($name, $href) = @_;
  my($res, $arg, $args, $arg_count, $index);

  $res = form_result $href->{'r'};
  if ( $res eq '' )
  {
    return 0;
  }

  printf(OUT "%s\n%s(", $res, $name);
  # args
  if ( exists $href->{'a'} )
  {
     $args = $href->{'a'};
     $arg_count = scalar @$args;
     for ( $index = 0; $index < $arg_count; $index++ )
     {
       printf(OUT ",") if ( $index );
       printf(OUT "%s arg%d", form_arg($args->[$index]), $index);
     }
  } else {
    $arg_count = 0;
  }
  printf(OUT ")\n{\n");
  # body of function
  printf(OUT " char *resstr;\n") if ( $res eq 'char *' );
  printf(OUT " void *fp = %s->f[%d].fp;\n", $ARRAY, $href->{'i'} );
  printf(OUT " value_t res;\n");
  if ( $res eq 'char *' )
  {
    printf(OUT "\tmemset(&res, 0, sizeof(res));\n");
  }
  printf(OUT " value_t args[%d];\n", $arg_count )
    if ( $arg_count );
  if ( $arg_count )
  {
    for ( $index = 0; $index < $arg_count; $index++ )
    {
      if ( $args->[$index] == 1 )
      {
        printf(OUT " args[%d].vtype = VT_STR;\n", $index);
        printf(OUT " args[%d].str = arg%d;\n", $index, $index);
        next;
      }
      if ( $args->[$index] == 2 )
      {
        printf(OUT " args[%d].vtype = VT_LONG;\n", $index);
        printf(OUT " args[%d].num = arg%d;\n", $index, $index);
        next;
      }
      if ( $args->[$index] == 7 )
      {
        printf(OUT " args[%d]._set_string(arg%d);\n", $index, $index);
        next;
      }
      die("Strange type " . $args->[$index] . " of argument in function '" . $name . "'");
    }
  }
  # Blja nah, IDA used Borland fastcall convention, so first param passed
  # in EAX and second in EDX
  # 1 OCT 2004 - in IDA 4.70 all functions in IDCFuncs array now stdcall
  # 		 so I changed asm code to meet new conversion calling
  printf(OUT " __asm {\n");
  printf(OUT "   lea eax, res\n   push eax\n");
  if ( $arg_count )
  {
     printf(OUT "   lea eax, args\n   push eax\n");
  } else {
     printf(OUT "   xor eax, eax\n   push eax\n");
  }
  printf(OUT "   call [fp]\n}\n");
  # form result
  if ( $res ne 'void' )
  {
    if ( $res eq 'long' or $res eq 'int' or $res eq 'unsigned long' )
    {
      printf(OUT " return res.num;\n");
    } else {
      printf OUT <<EOF;
 if ( res.c_str() == NULL )
  return NULL;
 resstr = _strdup(res.c_str());
 VarFree(&res);
 return resstr;
EOF
    }
  }
  printf(OUT "}\n\n");
};

sub produce_C
{
  my $hash = shift;
  my($name, $href);
  open (OUT, ">" . $C_FILE)
   or die("Cannot create output file '" . $C_FILE . "', ($!)");
  form_C_header;
  while( ($name, $href) = each %$hash )
  {
    next if ( exists $href->{'e'} );
    next if ( !is_can_do_XS($href) );
    next if ( is_implemented($name) );
    make_C_function $name, $href;
  }
  close OUT;
}

# print IDC functions hash (for debugging only :-)
sub print_fhash
{
  my $f_hash = shift;
  my($fh, $arg, $arg_ref, $name);
  foreach $name ( sort keys %$f_hash )
  {
     $fh = $f_hash->{$name};
     printf("%3.3d ", $fh->{'i'});
     # print return value
     if ( exists $fh->{'r'} )
     {
       printf("%s ", $fh->{'r'});
     } else {
       printf("none ");
     }
     printf("%s ", $name);
     if ( exists $fh->{'a'} )
     {
       $arg_ref = $fh->{'a'}; 
       foreach $arg ( @$arg_ref )
       {
         printf("%d ", $arg);
       }
     }
     printf(" (BAD %d)", $fh->{'e'})
       if ( exists $fh->{'e'} );
     printf("\n");
  }
}

 ###  ##  ###
#### MAIN ####
 ###  ##  ###
my %fhash;

my $status = getopts('pi:m:t:');
usage() if !$status;

$IDC_IDC = $opt_i if ( defined $opt_i );
$MY_FILE = $opt_m if ( defined $opt_m );

read_my_file \%fhash;
parse_IDC    \%fhash;
validate     \%fhash;
# here you have full info about builtin IDC functions
# O`k what need to produce ?
if ( defined $opt_p )
{
  print_fhash \%fhash;
  exit 0;
}

my $action;
$action = $opt_t;
$action = 'xs'
 if (! defined $action );
if ( $action eq 'xs' )
{
   close STDOUT;
   open STDOUT, ">" . $XS_FILE
     or die("Cannot create output XS file '" . $XS_FILE . "', ($!)");
   form_XS \%fhash;
} elsif ( $action eq 'pm' )
{
   produce_PM \%fhash;
} elsif ( $action eq 'i' )
{
   produce_SWIG \%fhash;
} elsif ( $action eq 'c' )
{
   produce_C \%fhash;
} elsif ( $action eq 'h' )
{
   produce_H \%fhash;
} else {
   usage();
}
