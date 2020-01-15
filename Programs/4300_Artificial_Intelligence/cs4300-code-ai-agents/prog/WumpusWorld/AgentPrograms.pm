#
#
#
our $aps =
[
 {
   name => 'Simpleton',
   key  => 'S',
   header => 'Simpleton.h',
   cpp    => ['Simpleton.cpp'],
   constructor => 'ai::Sample::Simpleton()',
 },
 {
   name => 'Aristotle',
   key  => 'A',
   header => 'Aristotle.h',
   cpp    => ['Aristotle.cpp'],
   constructor => 'ai::Sample::Aristotle()',
 },
 {
   name => 'Harbad',
   key  => 'G',
   header => 'starterGimli.h',
   cpp    => ['starterGimli.cpp','starterGimliKnowledgeBase.cpp','starterGimliWumpusSearch.cpp'],
   constructor => 'starter::Gimli(opts)',
 },
#{
#  name => '',
#  key  => '',
#  header => '',
#  constructor => '',
#},
 ];

1;
