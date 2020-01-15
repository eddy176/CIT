define cube wg ***ww**** *g**g**** ****r**** ****b**** ****o**** ****y****
define cube wr ****w**w* ****g**** *r**r**** ****b**** ****o**** ****y****
define cube wb ****ww*** ****g**** ****r**** *b**b**** ****o**** ****y****
define cube wo *w**w**** ****g**** ****r**** ****b**** *o**o**** ****y****

define cube og ****w**** ***gg**** ****r**** ****b**** ****oo*** ****y****
define cube gr ****w**** ****gg*** ***rr**** ****b**** ****o**** ****y****
define cube rb ****w**** ****g**** ****rr*** ***bb**** ****o**** ****y****
define cube bo ****w**** ****g**** ****r**** ****bb*** ***oo**** ****y****

define cube yg ****w**** ****g**g* ****r**** ****b**** ****o**** ***yy****
define cube yr ****w**** ****g**** ****r**r* ****b**** ****o**** *y**y****
define cube yb ****w**** ****g**** ****r**** ****b**b* ****o**** ****yy***
define cube yo ****w**** ****g**** ****r**** ****b**** ****o**o* ****y**y*

define cube wgo w***w**** g***g**** ****r**** ****b**** **o*o**** ****y****
define cube wob **w*w**** ****g**** ****r**** **b*b**** o***o**** ****y****
define cube wrg ****w*w** **g*g**** r***r**** ****b**** ****o**** ****y****
define cube wbr ****w***w ****g**** **r*r**** b***b**** ****o**** ****y****

define cube ygr ****w**** ****g***g ****r*r** ****b**** ****o**** y***y****
define cube yrb ****w**** ****g**** ****r***r ****b*b** ****o**** **y*y****
define cube yog ****w**** ****g*g** ****r**** ****b**** ****o***o ****y*y**
define cube ybo ****w**** ****g**** ****r**** ****b***b ****o*o** ****y***y

#Step 1: edges 
#yellow top
define cube petrus_ybo_e yb bo yo
define cube petrus_yog_e yg yo og
define cube petrus_yrb_e yb yr rb
define cube petrus_ygr_e yr yg gr
#white top
define cube petrus_wgo_e wo wg og
define cube petrus_wob_e wo wb bo
define cube petrus_wrg_e wr wg gr
define cube petrus_wbr_e wb wr rb

#Step 2: corners 
#yellow top
define cube petrus_byo petrus_ybo_e ybo
define cube petrus_yog petrus_yog_e yog
define cube petrus_yrb petrus_yrb_e yrb
define cube petrus_ygr petrus_ygr_e ygr
#white top
define cube petrus_wgo petrus_wgo_e wgo
define cube petrus_wob petrus_wob_e wob
define cube petrus_wrg petrus_wrg_e wrg
define cube petrus_wbr petrus_wbr_e wbr

#Step 3: 2x2x3 
define cube petrus_2x2x3_ygo1 petrus_byo yg yog
define cube petrus_2x2x3_ygo2 petrus_byo og yog

define cube petrus_2x2x3_wob1 petrus_byo wo wob
define cube petrus_2x2x3_wob2 petrus_byo wb wob

define cube petrus_2x2x3_yrb1 petrus_byo rb yrb
define cube petrus_2x2x3_yrb2 petrus_byo yr yrb

#Step 4: petrus + 1st edges 
define cube petrus_1st_e_orange petrus_2x2x3_ygo1 petrus_2x2x3_ygo2
define cube petrus_1st_e_blue petrus_2x2x3_wob1 petrus_2x2x3_wob2
define cube petrus_1st_e_yellow petrus_2x2x3_yrb1 petrus_2x2x3_yrb2

#Step 5: petrus 1st 
define cube petrus_1st_orange petrus_1st_e_orange wgo
define cube petrus_1st_blue petrus_1st_e_blue wbr
define cube petrus_1st_yellow petrus_1st_e_yellow ygr

#Step6: 2nd 
define cube 2nd_orange_d petrus_1st_orange wg
define cube 2nd_blue_d petrus_1st_blue wr
define cube 2nd_yellow_d petrus_1st_yellow gr

#Step7: half cross
define cube orange_d_c_rbwr 2nd_orange_d rb wr
define cube orange_d_c_gryr 2nd_orange_d gr yr
define cube blue_d_c_ygog 2nd_blue_d yg og
define cube blue_d_c_wggr 2nd_blue_d wg gr
define cube yellow_d_c_wrwg 2nd_yellow_d wr wg
define cube yellow_d_c_wbwo 2nd_yellow_d wb wo

#Step 8: 3rd cross
define cube orange_d_c_rbwrrg orange_d_c_rbwr rg
define cube orange_d_c_gryrrb orange_d_c_gryr rb
define cube blue_d_c_ygoggr blue_d_c_ygog gr
define cube blue_d_c_wggrog blue_d_c_wggr og
define cube yellow_d_c_wrwgwb yellow_d_c_wrwg wb
define cube yellow_d_c_wbwowg yellow_d_c_wbwo wg

define cube orange_d_c_rbwryr orange_d_c_rbwr yr
define cube orange_d_c_gryrwr orange_d_c_gryr wr
define cube blue_d_c_ygogwg blue_d_c_ygog wg
define cube blue_d_c_wggryg blue_d_c_wggr yg
define cube yellow_d_c_wrwgwo yellow_d_c_wrwg wo
define cube yellow_d_c_wbwowr yellow_d_c_wbwo wr

#Step 9: cross
define cube orange_d_cross orange_d_c_rbwrrg yr
define cube blue_d_cross blue_d_c_ygoggr wg
define cube yellow_d_cross yellow_d_c_wrwgwb wo