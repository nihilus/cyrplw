#!perl -w
# dirty hack to fix XS function in ida_wrap.c
# 16 Jul 2013 (C) RedPlait
use strict;
use warnings;

my @xs_names;
my $str;
my $state = 0;

while( $str = <> )
{
  if ( !$state && $str =~ /extern XS\(([^\)]+)\)/ )
  {
    push @xs_names, $1;
  }
  if ( $str =~ /swig_commands\[\]/ )
  {
    print $str;
    $state++;
    next;
  }
  if ( $state == 1 &&
       $str =~ /\{0,0\}/
     )
  {
    my $iter;
    foreach $iter ( @xs_names )
    {
      my $bind_name = $iter;
      $bind_name =~ s/myxs_//;
      printf("{\"IDA::%s\", %s},\n", $bind_name, $iter);
    }
    $state++;
  }
  print $str;
}