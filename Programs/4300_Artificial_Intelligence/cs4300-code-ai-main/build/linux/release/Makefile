BASE_DIR := ../../../..

# ORDER IS IMPORTANT HERE!
DIRS := \
	$(BASE_DIR)/cs4300-code-ai-lib \
	$(BASE_DIR)/cs4300-code-ai-environment \
	$(BASE_DIR)/cs4300-code-ai-agents 
#\
#$(BASE_DIR)/cs4300-code-ai-cgl

REVDIRS := $(shell (for d in $(DIRS); do echo $$d; done) | tac)

all: \
	normal-build \
	debug-build \
	profile-debug-build \
	optimize-build

all-release: \
	all \
	release-build

all-clean: \
	release-clean \
	optimize-clean \
	profile-debug-clean \
	debug-clean \
	normal-clean

all-spotless: \
	release-spotless \
	optimize-spotless \
	profile-debug-spotless \
	debug-spotless \
	normal-spotless

normal-build: 
	for d in $(DIRS); do \
		(cd $${d}/build/linux; \
		make configure; \
		B_OPTIMIZE=0 B_PROFILE=0 B_DEBUG=0 make;) \
	done

debug-build: 
	for d in $(DIRS); do \
		(cd $${d}/build/linux; \
		make configure; \
		B_OPTIMIZE=0 B_PROFILE=0 B_DEBUG=1 make;) \
	done

profile-debug-build: 
	for d in $(DIRS); do \
		(cd $${d}/build/linux; \
		make configure; \
		B_OPTIMIZE=0 B_PROFILE=1 B_DEBUG=1 make;) \
	done

optimize-build: 
	for d in $(DIRS); do \
		(cd $${d}/build/linux; \
		make configure; \
		B_OPTIMIZE=1 B_PROFILE=0 B_DEBUG=0 make;) \
	done

SERVERS  := WW_Test WumpusWorld \
	TicTacToeServer \
	SW_Test ScavengerServer \
	MancalaServer \
	CC_Test CCheckersServer \
	CandyServer

DISPLAYS := WD_Test WumpusDisplay \
	TicTacToeDisplay \
	SD_Test ScavengerDisplay \
	MancalaDisplay \
	CD_Test CCheckersDisplay \
	CandyDisplay

AGENTS := WA_Test WumpusAgent \
	TicTacToeAgent \
	SA_Test ScavengerAgent \
	MancalaAgent \
	CA_Test CCheckersAgent \
	CandyAgent

SPECIAL_AGENTS := WA_Test_f11 WA_Test_f10 WA_Test_f09 WA_Test_f08 WA_Test_cgl \
	SOstudent2012 SOcgl2012 \
	SA_Test_search_f09 SA_Test_search_f08 SA_Test_online_f11 SA_Test_online_f09 SA_Test_online_cgl SA_Test_objects_f09 \
	cgl_book_spring cgl_book_process CCcgl2012 CA_Test_cgl CA_Test_f06 CA_Test_f08 CA_Test_f09 CA_Test_f10 CA_Test_f11 \
	CandyAgentCgl \
	ChineseCheckers-2012 ScavengerLearningAgent2012	WumpusAgent-2012 \
	ChineseCheckers-2013 msllogic.txt ScavengerLearningAgent2013 SOstudent2013 SSstudent2013 WumpusAgent-2013

OTHERS_TO_CLEAN := TSPSolver-LocalSearch TSP_*.txt \
	SudokuSolver-LocalSearch \
	SliderSolver SliderInformed \
	RectangleSolver Rectangle \
	PL_Test PL_Shell PL_Dragons_2012 PL_Dragons PL_Wumpus \
	Genesis.pl \
	FOL_Test \
	EightSquareInformed \
	DTL_Test \
	RunScavengerTourney*.py \
	WorldBuilder \
	scav_world.txt world-assignment-grade.txt \
	scavenger*.out scores*.out killme* *~ \
	y12m*_world.txt \
	y13m*-world.txt \
	WumpusWorldScript \
	RunChineseCheckers2012.py RunScavengerLearning2012.py RunWumpusWorld2012.py \
	MazeDriver MazeGenerator MazeSolver NumbersDriver NumbersSolver \
	RunChineseCheckers2013.py RunScavengerLearning2013.py RunScavengerOnline2013.py RunWumpusWorld2013.py \
	ScavengerAgent_cgl ScavengerAgent_cgl2012 ScavengerData WumpusAgent_cgl

OPTIMIZED_TO_CLEAN := \
	TSP_*.txt \
	scav_world.txt world-assignment-grade.txt \
	scavenger*.out scores*.out killme* *~ \
	y12m*_world.txt allscores* bak \
	CCRUNME cgl_book_process cgl_book_spring dragons.PL \
	PL_Dragons PL_Dragons_2012 PL_Shell PL_Test PL_Wumpus RUN_CC_CGL RunScavengerTourney2012.py \
	singood.PL SOstudent2012 TSP_generator_border.py TSP_generator.py \
	WA_Test WorldBuilder WW_Test \
	y13m*-world.txt WA_Test_f* TSPSolver-LocalSearch SudokuSolver-LocalSearch SA_Test_* SOcgl2012 \
	Run*2013.py Run*2012.py CA_Test_* msllogic.txt

release-build:
	@echo "release-build is no longer suppported"
#	 ( \
#	   now=`date '+y%ym%md%d'`; \
#	   if [ ! -d ai-release-$${now} ]; then \
#	     mkdir ai-release-$${now}; \
#	     tar -cf - -C $(BASE_DIR) ai ai-agents ai-lib | tar -xf - -C ai-release-$${now}; \
#	     cd ai-release-$${now}; \
#	     find ai -name RunProg -print | xargs rm; \
#	     for d in ai ai-agents ai-lib; do \
#	       find $${d} -name '.depend*' -print | xargs rm -f; \
#	       find $${d} -name '00obj*' -print | xargs rm -rf; \
#	       find $${d} -name 'CVS' -print | xargs rm -rf; \
#	     done; \
#	     cd ai-lib/third; rm -f freeglut* boost*; cd ../..; \
#	     cd ai/lib; \
#	           /bin/false rm -rf 00lib-gp; \
#	           find . -name 'libboost_wserialization*' -print | xargs rm -f; \
#	           find . -name 'libboost_serialization-d*' -print | xargs rm -f; \
#	           find . -name 'libboost_serialization-s*' -print | xargs rm -f; \
#	           find . -name 'libboost_serialization-mt-*' -print | xargs rm -f; \
#	           find . -name 'libboost_serialization.*' -print | xargs rm -f; \
#	     cd ../..; \
#	     cd ai/bin; \
#	           rm -f $(SERVERS) $(DISPLAYS) $(AGENTS) $(SPECIAL_AGENTS) $(OTHERS_TO_CLEAN); \
#	           cd 00bin-g; \
#	               rm -f *_f?? *_cgl; \
#	               rm -f $(SERVERS) $(DISPLAYS) $(AGENTS) $(SPECIAL_AGENTS) $(OTHERS_TO_CLEAN); \
#	           cd ..; \
#	           cd 00bin-gp; \
#	               rm -f *_f?? *_cgl; \
#	               rm -f $(SERVERS) $(DISPLAYS) $(AGENTS) $(SPECIAL_AGENTS) $(OTHERS_TO_CLEAN); \
#	           cd ..; \
#	           cd 00bin-o; \
#	               rm -f $(OPTIMIZED_TO_CLEAN); \
#	           cd ..; \
#	           /bin/false rm -rf 00bin-gp; \
#	     cd ../..; \
#	   else \
#	     echo \*\*\* ai-release-$${now} already exists.; \
#	   fi \
#	 )


normal-clean: 
	for d in $(REVDIRS); do \
		(cd $${d}/build/linux; \
		make configure; \
		B_OPTIMIZE=0 B_PROFILE=0 B_DEBUG=0 make clean;) \
	done

debug-clean: 
	for d in $(REVDIRS); do \
		(cd $${d}/build/linux; \
		make configure; \
		B_OPTIMIZE=0 B_PROFILE=0 B_DEBUG=1 make clean;) \
	done

profile-debug-clean: 
	for d in $(REVDIRS); do \
		(cd $${d}/build/linux; \
		make configure; \
		B_OPTIMIZE=0 B_PROFILE=1 B_DEBUG=1 make clean;) \
	done

optimize-clean: 
	for d in $(REVDIRS); do \
		(cd $${d}/build/linux; \
		make configure; \
		B_OPTIMIZE=1 B_PROFILE=0 B_DEBUG=0 make clean;) \
	done


release-clean:
	( \
	  now=`date '+y%ym%md%d'`; \
	  if [ -d ai-release-$${now} ]; then \
	    rm -rf ai-release-$${now}; \
	  else \
	    echo \*\*\* ai-release-$${now} does not already exist.; \
	  fi \
	)

normal-spotless: 
	for d in $(REVDIRS); do \
		(cd $${d}/build/linux; \
		make configure; \
		B_OPTIMIZE=0 B_PROFILE=0 B_DEBUG=0 make spotless;) \
	done

debug-spotless: 
	for d in $(REVDIRS); do \
		(cd $${d}/build/linux; \
		make configure; \
		B_OPTIMIZE=0 B_PROFILE=0 B_DEBUG=1 make spotless;) \
	done

profile-debug-spotless: 
	for d in $(REVDIRS); do \
		(cd $${d}/build/linux; \
		make configure; \
		B_OPTIMIZE=0 B_PROFILE=1 B_DEBUG=1 make spotless;) \
	done

optimize-spotless: 
	for d in $(REVDIRS); do \
		(cd $${d}/build/linux; \
		make configure; \
		B_OPTIMIZE=1 B_PROFILE=0 B_DEBUG=0 make spotless;) \
	done


release-spotless:
	( \
	  now=`date '+y%ym%md%d'`; \
	  if [ -d ai-release-$${now} ]; then \
	    rm -rf ai-release-$${now}; \
	  else \
	    echo \*\*\* ai-release-$${now} does not already exist.; \
	  fi \
	)

