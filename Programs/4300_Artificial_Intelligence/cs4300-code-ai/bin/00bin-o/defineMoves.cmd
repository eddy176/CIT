define move Allan F F U' L R' F F L' R U' F F

define move Swap_bw_wr R' U' R U R'

define move daisy_2_cross F F R R L L B B

# BOTTOM LAYER CROSS->FIRST
define move bottomcorner1 F D F'
define move bottomcorner2 R' D' R
define move bottomcorner3 R' D R F D2 F'

define move topcornerwrongway R' D R F D F'

# 2ND LAYER SOLVING
define move 2ndlayer1 z z U R U' R' U' F' U F z z
define move 2ndlayer2 z z U' L' U L U F U' F' z z

define move 2ndlayer3 z z R U' R' U F' U U F U F' U U F z z 

# YELLOW CROSS SOLVING
define move ycross1 z z F U R U' R' F' z z
define move ycross2 z z F R U R' U' F' z z
define move ycross3 z z U R U R' U R U2 R' z z

# SOLVING LAST CORNER 1
define move lastcorners_1 z z U R U' L' U R' U' L z z

# SOLVING LAST CORNER 2
define move lastcorners_2 z z R' D' R D z z
define move lastcorners_3 z z R' D' R D R' D' R D z z
define move lastcorners_4 z z R' D' R D R' D' R D R' D' R D R' D' R D z z


