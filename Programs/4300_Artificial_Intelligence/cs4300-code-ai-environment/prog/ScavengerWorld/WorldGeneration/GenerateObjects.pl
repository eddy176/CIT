#!/usr/bin/perl

use strict;


my $percent_color_bad  = .50;
my $percent_color_good = .0;
my $percent_shape_bad  = .0;
my $percent_shape_good = .0;
my $percent_luminescence_bad  = .0;
my $percent_luminescence_good  = .0;
my $use_luminescence   = 0;
my $use_one_color      = 0;
my $use_one_size       = 0;
my $use_one_shape      = 0;

use Getopt::Std;
my %Options;

getopts("?C:L:c:S:", \%Options);

if($Options{'?'})
{
  print "$0
-C fraction_color_bad = .50;  # Fraction of the colors that are toxic
-L use_luminescence   = 0;    # 1 to use luminescence attribute
-c use_one_color      = 0;    # color that is good
-S use_one_shape      = 0;    # shape that is good
";
  exit 0;
}
if($Options{'C'}) { $percent_color_bad = $Options{'C'}; }
if(defined($Options{'L'})) { $use_luminescence = $Options{'L'}; }
if(defined($Options{'c'})) { $use_one_color = $Options{'c'}; }
if(defined($Options{'s'})) { $use_one_size = $Options{'s'}; }
if(defined($Options{'S'})) { $use_one_shape = $Options{'S'}; }

if($use_luminescence)
{
    $percent_luminescence_bad = $percent_color_bad;
    $percent_color_bad = 0.;
}

my %colors = ( "red"           => [ "r", 1  ],
               "green"         => [ "g", 1  ],
               "blue"          => [ "b", 1  ],
               # "magenta"       => [ "m", 1  ],
               # "yellow"        => [ "y", 1  ],
               # "cyan"          => [ "c", 1  ],
               # "black"         => [ "B", 1  ],
               # "white"         => [ "w", 1  ],
               # "gold"          => [ "G", 1  ],
               # "silver"        => [ "s", 1  ],
               # "brown"         => [ "W", 1  ],
               # "orange"        => [ "o", 1  ],
	       # "rust"          => [ "R", 1  ],
               # "dayglo-orange" => [ "d", 1  ],
               # "aqua"          => [ "a", 1  ],
               # "bisque"        => [ "q", 1  ],
               # "crimson"       => [ "C", 1  ],
               # "chocolate"     => [ "h", 1  ],
               # "khaki"         => [ "k", 1  ],
               # "fuchsia"       => [ "f", 1  ],
               # "indigo"        => [ "i", 1  ],
               # "pink"          => [ "p", 1  ],
               # "orchid"        => [ "O", 1  ],
               # "tomato"        => [ "t", 1  ],
               # "wheat"         => [ "H", 1  ],
               # "forestgreen"   => [ "F", 1  ],
	       # "lawngreen"     => [ "l", 1  ],
               # "olivedrab"     => [ "V", 1  ],
               # "snow"          => [ "n", 1  ],
               # "violet"        => [ "v", 1  ],
               # "slategrey"     => [ "Y", 1  ],
               # "steelblue"     => [ "e", 1  ],
               # "plum"          => [ "M", 1  ],
               # "peachpuff"     => [ "P", 1  ],
               "limegreen"     => [ "L", 1  ],
               "dsc-red-white-blue" => [ "D", 1  ],
               );
my @colors = keys %colors;
check_colors(\%colors);
set_color_values(\%colors);

my %luminescences = ( "none"           => [ "n", 1  ],
		      "1candela"       => [ "1", 1  ],
		      "2candela"       => [ "2", 1  ],
		      "5candela"       => [ "5", 1  ],
		      "10candela"      => [ "10", 1  ],
		      "blinding"       => [ "b", 1  ],
    );
my @luminescences = keys %luminescences;
set_luminescence_values(\%luminescences);

#                           mass             volume           value    symbol
#                           min     max      min     max
my %sizes = ( "tiny"   => [    0.1,     1.0,    0.1,     2.0,   2.0,   "t"  ],
              "small"  => [    1.0,     8.0,    1.0,    15.0,   4.0,   "s"  ],
              "medium" => [    5.0,    15.0,   10.0,    30.0,   6.0,   "m"  ],
              # "large"  => [   10.0,    24.9,   30.0,    99.9,   8.0,   "l"  ],
              # "huge"   => [   20.0,    80.0,  100.1,   150.0,   10.0,   "h"  ],
              );
my @sizes  = keys %sizes;

#                              value   type         symbol
my %shapes = ( "rock"      => [ 1.0,   "mineral",   "r"   ],
               # "sphere"    => [ 2.0,   "mineral",   "S"   ],
               # "cylinder"  => [ 2.0,   "mineral",   "C"   ],
               # "cone"      => [ 2.0,   "mineral",   "c"   ],
               # "cube"      => [ 3.0,   "mineral",   "Q"   ],
               # "pyramid"   => [ 3.0,   "mineral",   "P"   ],
               # "box"       => [ 3.0,   "mineral",   "q"   ],

               "grass"     => [ 1.0,   "vegetable", "g"   ],
               "pod"       => [ 1.0,   "vegetable", "p"   ],
               # "bush"      => [ 1.0,   "vegetable", "B"   ],
               # "tree"      => [ 2.0,   "vegetable", "t"   ],
               # "stalk"     => [ 2.0,   "vegetable", "s"   ],
               # "vine"      => [ 3.0,   "vegetable", "v"   ],

               # "mandelbrot"=> [ 5.0,   "animal",    "m"    ],
               "blob"      => [ 2.0,   "animal",    "b"    ],
               # "quadruped" => [ 2.0,   "animal",    "4"    ],
               # "triped"    => [ 5.0,   "animal",    "3"    ],
               "biped"     => [ 2.0,   "animal",    "2"    ],
               # "moped"     => [ 4.0,   "animal",    "1"    ],
               # "noped"     => [ 2.0,   "animal",    "0"    ],
              );
my @shapes = keys %shapes;
check_shapes(\%shapes);
set_shape_values(\%shapes);

my $lum_header = '';
if($use_luminescence)
{
    $lum_header = 'Luminescence';
}
printf("Object: %10s %6s %8s %8s %10s %8s %8s %20s %10s %10s %12s\n",
       "ID",
       "Cell",
       "Name",
       "Value",
       "Type",
       "Mass",
       "Volume",
       "Color",
       "Shape",
       "Size",
       $lum_header
       );
my $obj_count = 1;

my %choice;
    
choose_colors(\@colors, \%choice, $percent_color_bad, $percent_color_good);
choose_shapes(\@shapes, \%choice, $percent_shape_bad, $percent_shape_good);
choose_luminescences(\@luminescences, \%choice, $percent_luminescence_bad, $percent_luminescence_good);

#for my $k (keys %choice)
#{
#    print $k, " ", $choice{$k}, "\n";#
#}
#print %choice,"\n";
#exit(0);

foreach my $color (@colors)
{
  foreach my $size (@sizes)
    {
      foreach my $shape (@shapes)
        {
	    my $first = 1;
	    foreach my $lum (@luminescences)
	    {
		if((!$use_luminescence) && (!$first))
		{
		    last;
		}
		$first = 0;
		
		my ($obj_id,
		    $cell_id,
		    $name,
		    $value,
		    $type,
		    $mass,
		    $volume);
		$obj_id  = "OBJ" . $obj_count;   $obj_count ++;
		$cell_id = 1;
		$name    = $colors{$color}->[0] . $shapes{$shape}->[2] . $sizes{$size}->[5] ;
		$value   = $colors{$color}->[1] + $sizes{$size}->[4] + $shapes{$shape}->[0];
		if($use_luminescence)
		{
		    $value += $luminescences{$lum}->[1];
		}

		if($use_one_color && $use_one_shape)
		{
		    if($color eq $use_one_color && $shape eq $use_one_shape)
		    {
			# no change
		    }
		    else
		    {
			$value = -$value;
		    }
		}
		elsif(good_color($color, \%choice) || good_shape($shape, \%choice) || good_luminescence($lum, \%choice))
		{
		    # no change
		}
		elsif(bad_color($color, \%choice) || bad_shape($shape, \%choice) || bad_luminescence($lum, \%choice))
		{
		    $value = -$value;	      
		}
		else
		{
		    # ?change?
		}
		
		$type    = $shapes{$shape}->[1];
		my ($min_mass, $max_mass) = ($sizes{$size}->[0], $sizes{$size}->[1]);
		$mass    = $min_mass + ($max_mass - $min_mass) * rand();
		my ($min_vol, $max_vol) = ($sizes{$size}->[2], $sizes{$size}->[3]);
		$volume  = $min_vol + ($max_vol - $min_vol) * rand();
		
		my $lum_value = '';
		if($use_luminescence)
		{
		    $lum_value = $lum;
		}
		printf("Object: %10s %6d %8s %8.2f %10s %8.2f %8.2f %20s %10s %10s %12s\n",
		       $obj_id,
		       $cell_id,
		       $name,
		       $value,
		       $type,
		       $mass,
		       $volume,
		       $color,
		       $shape,
		       $size,
		       $lum_value
		    );
	    }
        }
    }
}

my $n = @colors * @sizes * @shapes;
if($use_luminescence)
{
    $n *= @luminescences;
}

print STDERR $n, " objects created.\n";



sub color_symbol
{
    my ($color) = @_;
    return $color->[0];
}

sub check_colors
{
    my ($colors) = @_;
    my %symbols;
    my $error = 0;
    for my $c (keys %{$colors})
    {
	my $symbol = color_symbol($colors->{$c});
	if(defined($symbols{$symbol}))
	{
	    print "$symbol is used multiple times. ($c, ",$symbols{$symbol},")\n";
	    $error = 1;
	}
	else
	{
	    $symbols{$symbol} = $c;
	}
    }
    if ($error != 0)
    {
	exit(1);
    }
}

sub set_color_values
{
    my ($colors) = @_;
    for my $c (keys %{$colors})
    {
	my $value = 1+int(rand()*10);
	$colors->{$c}->[1] = $value;
    }
}

sub set_luminescence_values
{
    my ($luminescences) = @_;
    for my $l (keys %{$luminescences})
    {
	my $value = 1+int(rand()*10);
	$luminescences->{$l}->[1] = $value;
    }
}

sub set_shape_values
{
    my ($shapes) = @_;
    for my $s (keys %{$shapes})
    {
	my $value = 1+int(rand()*10);
	$shapes{$s}->[0] = $value;
    }
}

sub shape_symbol
{
    my ($shape) = @_;
    return $shape->[2];
}

sub shape_type
{
    my ($shape) = @_;
    return $shape->[1];
}

sub shape_value
{
    my ($shape) = @_;
    return $shape->[0];
}

sub check_shapes
{
    my ($shapes) = @_;
    my %symbols;
    my $error = 0;
    for my $shape (keys %{$shapes})
    {
	my $symbol = shape_symbol($shapes->{$shape});
	if(defined($symbols{$symbol}))
	{
	    print "$symbol is used multiple times. ($shape, ",$symbols{$symbol},")\n";
	    $error = 1;
	}
	else
	{
	    $symbols{$symbol} = $shape;
	}
    }
    if ($error != 0)
    {
	exit(1);
    }
}

sub size_mmin
{
    my ($size) = @_;
    return $size->[0];
}
sub size_mmax
{
    my ($size) = @_;
    return $size->[1];
}
sub size_vmin
{
    my ($size) = @_;
    return $size->[2];
}
sub size_vmax
{
    my ($size) = @_;
    return $size->[3];
}
sub size_value
{
    my ($size) = @_;
    return $size->[4];
}
sub size_symbol
{
    my ($size) = @_;
    return $size->[5];
}


sub choose_colors
{
    my ($colors, $choices, $percent_color_bad, $percent_color_good) = @_;
    foreach my $color (@{$colors})
    {
	my $c_rand = rand();
	if($c_rand < $percent_color_bad)
	{ # bad colors
	    set_bad_color($color, $choices);
	}
	elsif($c_rand < $percent_color_bad + $percent_color_good)
	{ # good color
	    set_good_color($color, $choices);
	}
    }
}

sub choose_shapes
{
    my ($shapes, $choices, $percent_shape_bad, $percent_shape_good) = @_;
    foreach my $shape (@{$shapes})
    {
	my $s_rand = rand();
	if($s_rand < $percent_shape_bad)
	{ # bad shape
	    set_bad_shape($shape, $choices);
	}
	elsif($s_rand < $percent_shape_bad + $percent_shape_good)
	{ # good shape
	    set_good_shape($shape, $choices);
	}
    }
}

sub choose_luminescences
{
    my ($lums, $choices, $percent_lum_bad, $percent_lum_good) = @_;
    foreach my $lum (@{$lums})
    {
	my $c_rand = rand();
	if($c_rand < $percent_lum_bad)
	{ # bad lum
	    set_bad_luminescence($lum, $choices);
	}
	elsif($c_rand < $percent_lum_bad + $percent_lum_good)
	{ # good lum
	    set_good_luminescence($lum, $choices);
	}
    }
}


sub bad_shape
{
    my($shape, $choices) = @_;
    return $choices->{'shape-'.$shape} < 0;
}
sub good_shape
{
    my($shape, $choices) = @_;
    return $choices->{'shape-'.$shape} > 0;
}
sub set_bad_shape
{
    my($shape, $choices) = @_;
    $choices->{'shape-'.$shape} = -1;
}
sub set_good_shape
{
    my($shape, $choices) = @_;
    $choices->{'shape-'.$shape} = 1;
}

sub bad_color
{
    my($color, $choices) = @_;
    return $choices->{'color-'.$color} < 0;
}
sub good_color
{
    my($color, $choices) = @_;
    return $choices->{'color-'.$color} > 0;
}
sub set_bad_color
{
    my($color, $choices) = @_;
    $choices->{'color-'.$color} = -1;
}
sub set_good_color
{
    my($color, $choices) = @_;
    $choices->{'color-'.$color} = 1;
}

sub bad_luminescence
{
    my($l, $choices) = @_;
    return $choices->{'luminescence-'.$l} < 0;
}
sub good_luminescence
{
    my($l, $choices) = @_;
    return $choices->{'luminescence-'.$l} > 0;
}
sub set_bad_luminescence
{
    my($l, $choices) = @_;
    $choices->{'luminescence-'.$l} = -1;
}
sub set_good_luminescence
{
    my($l, $choices) = @_;
    $choices->{'luminescence-'.$l} = 1;
}
