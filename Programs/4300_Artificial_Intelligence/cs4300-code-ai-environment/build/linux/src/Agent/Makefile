MAKE_DIR := $(shell mkpath="."; count=0; while [ \( ! -e "$$mkpath/Makefile.top" \) -a \( "$$count" -lt 10 \) ]; do mkpath="$$mkpath/.."; count=`echo $$count | awk '{print $$1 + 1;}'`; done; echo $$mkpath;)

include $(MAKE_DIR)/Makefile.top

# XY is needed by other environments
# All are needed by Base with the DisplayDriver
PROJECT_LIST  := \
	XY \
	Abalone \
	TicTacToe \
	UltimateTicTacToe \
	Jetan \
	Wumpus \
	Candy \
	CCheckers \
	Mancala \
	Scavenger \

# XY \
# CCheckers TicTacToe Mancala \
# Obstacle Scavenger Wumpus \
# Candy # Base Vacuum

all install clean spotless:
	for d in $(PROJECT_LIST); do \
		(cd $$d; $(MAKE) $(MAKE_FLAGS) $@) \
	done

include $(MAKE_DIR)/Makefile.dep


# Local Variables:
# mode:makefile
# End:
