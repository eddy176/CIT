#
#
#
our $aps =
[
 {
   name => 'Manual',
   key  => 'M',
   header => 'aiSampleManual.h',
   cpp    => ['aiSampleManual.cpp'],
   constructor => 'ai::UltimateTicTacToe::Manual(opts)',
 },
 {
   name => 'Random',
   key  => 'r',
   header => 'aiSampleRandom.h',
   cpp    => ['aiSampleRandom.cpp'],
   constructor => 'ai::UltimateTicTacToe::Random(opts)',
 },
#{
#  name => '',
#  key  => '',
#  header => '',
#  constructor => '',
#},
 ];

1;
