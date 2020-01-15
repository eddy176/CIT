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
print "color,shape,size,${lum_header}pickup\n";

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
	$total_examples ++;
	if($value > 0 &&
	   $mass < 25. &&
	   $volume < 100.)
	{
	    print "$color,$shape,$size,${lum}Yes\n";
	}
	else
	{
	    print "$color,$shape,$size,${lum}No\n";
	}
    }
    else
    {
    }
}

my $percent_given = 100.*$total_examples / $total_objects;
print STDERR "$total_examples pickup examples given of $total_objects possible ($percent_given %).\n";
