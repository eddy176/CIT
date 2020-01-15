#!/usr/bin/perl

use strict;

my $probability_pick = .30;

use Getopt::Std;
my %Options;

getopts("?p:", \%Options);

if($Options{'?'})
{
  print "$0
-p probability    = $probability_pick;   # probability of a single object being used as an example
";
  exit 0;
}
if($Options{'p'}) { $probability_pick = $Options{'p'}; }

my $total_objects = 0;
my $total_examples = 0;

# header line
my $line = <>;
#Object:         ID   Cell     Name    Value       Type     Mass   Volume                Color      Shape       Size Luminescence
my ($obj,
    $id,
    $cell,
    $name,
    $value,
    $type,
    $mass,
    $volume,
    $color,
    $shape,
    $size,
    $use_luminescence) = split /\s+/, $line;
my $lum_header = '';
if($use_luminescence)
{
    $lum_header = 'luminescence,'
}
print "color,shape,size,${lum_header}value\n";

while($line = <>)
{
    $total_objects ++;
    chomp($line);
    my ($obj,
	$id,
	$cell,
	$name,
	$value,
	$type,
	$mass,
	$volume,
	$color,
	$shape,
	$size,
	$luminescence) = split /\s+/, $line;
    if(rand() < $probability_pick)
    {
	my $lum = "";
	if($use_luminescence)
	{
	    $lum = "${luminescence},"
	}
	my $v = '';
	$total_examples ++;
#	if ( $value < -19 )
#	{
#	    $v = 'N_20_25';
#	}
#	elsif ( $value < -13 )
#	{
#	    $v = 'N_14_19';
#	}
#	elsif ( $value < -8 )
#	{
#	    $v = 'N_9_13';
#	}
#	elsif ( $value < -4 )
#	{
#	    $v = 'N_5_8';
#	}
#	elsif ( $value < -0 )
#	{
#	    $v = 'N_1_4';
#	}
#	elsif ( $value < 1 )
#	{
#	    $v = 'NP_0';
#	}
#	elsif ( $value < 5 )
#	{
#	    $v = 'P_1_4';
#	}
#	elsif ( $value < 9 )
#	{
#	    $v = 'P_5_8';
#	}
#	elsif ( $value < 14 )
#	{
#	    $v = 'P_9_13';
#	}
#	elsif ( $value < 20 )
#	{
#	    $v = 'P_14_19';
#	}
#	else
#	{
#	    $v = 'P_20_25';
#	}
	if(0)
	{
	}
	elsif($value < 0)
	{
	    $v = 'LESS_ZERO';
	}
	elsif($value > 0)
	{
	    my $dv = 5;
	    $v = sprintf('P_%d', $dv*int($value/$dv));
	    #$v = sprintf("P_%d", 1 + int(log($value)));
	}
	else
	{
	    $v = 'ZERO';
	}
	print "$color,$shape,$size,${lum}$v\n";
    }
    else
    {
    }
}

my $percent_given = 100.*$total_examples / $total_objects;
print STDERR "$total_examples value examples given of $total_objects possible ($percent_given %).\n";
