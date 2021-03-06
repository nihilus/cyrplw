#!perl -w
# Lame script to parse avx/xop opcodes list from bochs
# 21 Oct 2012 (C) RedPlait
# 22 Oct 2012 - add pseudo-ops for vcmppd/vcmpps/vcmpsd/vcmpss (-p option)
use strict;
use warnings;
use Getopt::Std;
use vars qw/$opt_c $opt_p $opt_v/;

sub usage()
{
    print STDERR <<EOF;
Usage is $0 [options] file(s) with opcodes
Options:
  -c -- use const modifier
  -p -- add pseudo names for vcmpXX
  -v -- verbose mode
EOF
    exit (8);
}

# opcodes names 
my %op_names;
# array of modified opcodes
my @opz;
# to gather types of operands to process
my %op_types;
# map for dups
my %dup_names;
# my enum names
my @e_names;

# pseudo-names
my @vcmppd = qw(
 VCMPEQPD
 VCMPLTPD
 VCMPLEPD
 VCMPUNORDPD
 VCMPNEQPD
 VCMPNLTPD
 VCMPNLEPD
 VCMPORDPD
 VCMPEQ_UQPD
 VCMPNGEPD
 VCMPNGTPD
 VCMPFALSEPD
 VCMPNEQ_OQPD
 VCMPGEPD
 VCMPGTPD
 VCMPTRUEPD
 VCMPEQ_OSPD
 VCMPLT_OQPD
 VCMPLE_OQPD
 VCMPUNORD_SPD
 VCMPNEQ_USPD
 VCMPNLT_UQPD
 VCMPNLE_UQPD
 VCMPORD_SPD
 VCMPEQ_USPD
 VCMPNGE_UQPD
 VCMPNGT_UQPD
 VCMPFALSE_OSPD
 VCMPNEQ_OSPD
 VCMPGE_OQPD
 VCMPGT_OQPD
 VCMPTRUE_USPD
);

my @vcmpps = qw(
 VCMPEQPS
 VCMPLTPS
 VCMPLEPS
 VCMPUNORDPS
 VCMPNEQPS
 VCMPNLTPS
 VCMPNLEPS
 VCMPORDPS
 VCMPEQ_UQPS
 VCMPNGEPS
 VCMPNGTPS
 VCMPFALSEPS
 VCMPNEQ_OQPS
 VCMPGEPS
 VCMPGTPS
 VCMPTRUEPS
 VCMPEQ_OSPS
 VCMPLT_OQPS
 VCMPLE_OQPS
 VCMPUNORD_SPS
 VCMPNEQ_USPS
 VCMPNLT_UQPS
 VCMPNLE_UQPS
 VCMPORD_SPS
 VCMPEQ_USPS
 VCMPNGE_UQPS
 VCMPNGT_UQPS
 VCMPFALSE_OSPS
 VCMPNEQ_OSPS
 VCMPGE_OQPS
 VCMPGT_OQPS
 VCMPTRUE_USPS
);

my @vcmpsd = qw(
 VCMPEQSD
 VCMPLTSD
 VCMPLESD
 VCMPUNORDSD
 VCMPNEQSD
 VCMPNLTSD
 VCMPNLESD
 VCMPORDSD
 VCMPEQ_UQSD
 VCMPNGESD
 VCMPNGTSD
 VCMPFALSESD
 VCMPNEQ_OQSD
 VCMPGESD
 VCMPGTSD
 VCMPTRUESD
 VCMPEQ_OSSD
 VCMPLT_OQSD
 VCMPLE_OQSD
 VCMPUNORD_SSD
 VCMPNEQ_USSD
 VCMPNLT_UQSD
 VCMPNLE_UQSD
 VCMPORD_SSD
 VCMPEQ_USSD
 VCMPNGE_UQSD
 VCMPNGT_UQSD
 VCMPFALSE_OSSD
 VCMPNEQ_OSSD
 VCMPGE_OQSD
 VCMPGT_OQSD
 VCMPTRUE_USSD
);

my @vcmpss = qw(
 VCMPEQSS
 VCMPLTSS
 VCMPLESS
 VCMPUNORDSS
 VCMPNEQSS
 VCMPNLTSS
 VCMPNLESS
 VCMPORDSS
 VCMPEQ_UQSS
 VCMPNGESS
 VCMPNGTSS
 VCMPFALSESS
 VCMPNEQ_OQSS
 VCMPGESS
 VCMPGTSS
 VCMPTRUESS
 VCMPEQ_OSSS
 VCMPLT_OQSS
 VCMPLE_OQSS
 VCMPUNORD_SSS
 VCMPNEQ_USSS
 VCMPNLT_UQSS
 VCMPNLE_UQSS
 VCMPORD_SSS
 VCMPEQ_USSS
 VCMPNGE_UQSS
 VCMPNGT_UQSS
 VCMPFALSE_OSSS
 VCMPNEQ_OSSS
 VCMPGE_OQSS
 VCMPGT_OQSS
 VCMPTRUE_USSS
);

my @pseudo_ops = (
 # vcmppd
 [
   \@vcmppd,
   [ 'Vpd', 'Hpd', 'Wpd', 'Ib', 'IA_AVX' ]
 ],
 # vcmpps
 [
   \@vcmpps,
   [ 'Vps', 'Hps', 'Wps', 'Ib', 'IA_AVX' ]
 ],
 # vcmpsd
 [
   \@vcmpsd,
   [ 'Vsd', 'Hpd', 'Wsd', 'Ib', 'IA_AVX' ]
 ],
 # vcmpss
 [
   \@vcmpss,
   [ 'Vss', 'Hps', 'Wss', 'Ib', 'IA_AVX' ]
 ]
);

sub dump_optypes
{
  my $iter;
  foreach $iter ( keys %op_types )
  {
    printf("%s: %d\n", $iter, $op_types{$iter});
  }
}

sub find_max_dup
{
  my $iter;
  my $res = 0;
  foreach $iter (values %dup_names)
  {
    $res = $iter if ( $res < $iter );
  }
  return $res;
}

sub make_ida_enum
{
  my %dups;
  my($iter, $name, $e_name, $n);
  $n = 0;
  # header
  printf("enum avx_insn_type_t\n{\n");
  foreach $iter ( @opz )
  {
    $name = $iter->[1]->[0];
    if ( exists $dup_names{$name} )
    {
      $dups{$name}++;
      $name = $name . $dups{$name};
    }
    $e_name = 'AVX_' . $name;
    push @e_names, $e_name;
    printf(" %s", $e_name);
    if ( !$n )
    {
      printf(" = CUSTOM_CMD_ITYPE,\n");
    } else {
      printf(",\n");
    }
    $n++;
  }
  if ( defined $opt_p )
  {
    foreach $iter ( @pseudo_ops )
    {
      my $niters = $iter->[0];
      foreach $name ( @$niters )
      {
        $e_name = 'AVX_' . lc($name);
        push @e_names, $e_name;
        printf(" %s,\n", $e_name);
      }
    }
  }
  # footer
  printf("};\n");
}

sub make_ops
{
  my($iter, $n, $op, $e_name);
  $n = 0;
  # header
  printf("\n// merged AVX & XOP opcodes\n");
  foreach $iter ( @opz )
  {
    $e_name = $e_names[$n];
    $op = $iter->[1];
    printf("%sstruct BxDisasmOpcodeInfo_t\n ", defined($opt_c) ? "const " : "");
    printf("%s = { \"%s\", %s, %s, %s, %s, %s, %s};\n", 
      $iter->[0], $op->[0], $e_name, $op->[1], $op->[2], $op->[3], $op->[4],$op->[5]
    );
    $n++;
  }
  # pseudo-ops
  if ( defined $opt_p )
  {
    printf("\n// AVX pseudo-ops\n");
    foreach $iter ( @pseudo_ops )
    {
      my $niters = $iter->[0];
      foreach my $name ( @$niters )
      {
        $e_name = 'AVX_' . lc($name);
        $op = $iter->[1];
        printf("%sstruct BxDisasmOpcodeInfo_t\n ", defined($opt_c) ? "const " : "");
        printf("Ia_pseudo_%s = { \"%s\", %s, %s, %s, %s, %s, %s};\n", 
          lc($name), lc($name), $e_name, $op->[0], $op->[1], $op->[2], $op->[3],$op->[4]
        );
        $n++;
      }
    }
  }
  # footer
  printf("\n");
}

sub make_map
{
  my($iter, $n, $e_name);
  $n = 0;
  # header
  printf("\n%sstruct BxDisasmOpcodeInfo_t *opcode_map[] = {\n", defined($opt_c) ? "const " : "");
  foreach $iter ( @opz )
  {
    $e_name = $e_names[$n];
    printf("/* %s */ &%s,\n", $e_name, $iter->[0]);
    $n++;
  }
  if ( defined $opt_p )
  {
    foreach $iter ( @pseudo_ops )
    {
      my $niters = $iter->[0];
      foreach my $name ( @$niters )
      {
        $e_name = $e_names[$n];
        printf("/* %s */ &Ia_pseudo_%s,\n", $e_name, lc($name));
        $n++;
      }
    }
  }
  # footer
  printf("};\n");

}

sub parse
{
  my $fname = shift;
  my($fh, $str, $name, $res);
  open($fh, '<', $fname) or die("Cannot open file $fname, error $!\n");
  while( $str = <$fh> )
  {
    chomp $str;
    next if ( $str !~ /^(\S+)\s+=\s+{(.*)}/ );
    $name = $1;
    my @ops = (split /\s?,\s?/, $2)[0, 2, 3, 4, 5, 6];
    $ops[0] =~ s/^\s*//;
    $ops[0] =~ s/\"//g;
    # check that we don`t have such name yet
    printf("%s: @ops\n", $name) if ( defined $opt_v );
    if ( exists $op_names{$ops[0]} )
    {
#      warn("Duplicated name: $ops[0]\n");
      $dup_names{$ops[0]}++;
    }
    $op_names{$ops[0]}++;
    $res++;
    # put operands
    $op_types{$ops[$_]}++ foreach qw(1 2 3 4);
    # store this opcode
    push @opz, [ $name, \@ops ];
  }
  $res = 0;
  return $res;
}

# main
my $status = getopts("cpv");
usage() if ( !$status );
parse($_) foreach @ARGV;
if ( defined $opt_v )
{
  dump_optypes();
  printf("Max dup count: %d\n", find_max_dup());
}
# produce IDA enum
make_ida_enum();
make_ops();
make_map();