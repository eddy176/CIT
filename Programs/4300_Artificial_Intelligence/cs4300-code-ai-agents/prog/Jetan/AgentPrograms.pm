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
   constructor => 'ai::Jetan::Manual(opts)',
 },
 {
   name => 'Random',
   key  => 'r',
   header => 'aiSampleRandom.h',
   cpp    => ['aiSampleRandom.cpp'],
   constructor => 'ai::Jetan::Random(opts)',
 },
# this needs to be edited when I add an agent utility function
#{
#  name => '',
#  key  => '',
#  header => '',
#  constructor => '',
#},
{
 name => 'AlphaBeta',
 key  => 'K',
 header => 'JetanAlphaBeta.h',
 cpp    => ['JetanAlphaBeta.cpp'],
 constructor => 'ai::Jetan::AlphaBeta(opts)',
},

# {
#  name => 'JABTEST',
#  key  => 'H',
#  header => 'JABTEST.h',
#  cpp    => ['JABTEST.cpp'],
#  constructor => 'ai::Jetan::JABTEST(opts)',
# },

# {
#  name => 'ABThreaded',
#  key  => 'T',
#  header => 'JetanABThreaded.h',
#  cpp    => ['JetanABThreaded.cpp'],
#  constructor => 'ai::Jetan::ABThreaded(opts)',
# },

# {
#  name => 'Minimax',
#  key  => 'm',
#  header => 'JetanMinimax.h',
#  cpp    => ['JetanMinimax.cpp'],
#  constructor => 'ai::Jetan::Minimax(opts)',
# },
 ];

1;
