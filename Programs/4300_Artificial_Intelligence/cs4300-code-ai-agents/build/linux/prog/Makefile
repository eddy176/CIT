MAKE_DIR := $(shell mkpath="."; count=0; while [ \( ! -e "$$mkpath/Makefile.top" \) -a \( "$$count" -lt 10 \) ]; do mkpath="$$mkpath/.."; count=`echo $$count | awk '{print $$1 + 1;}'`; done; echo $$mkpath;)
include $(MAKE_DIR)/Makefile.top

#PROJECT_LIST  :=  utils ScavengerWorld WumpusWorld PLTest FOLTest Rectangle Candy \
#	CCheckers TicTacToe Mancala Numbers Maze
PROJECT_LIST  :=  \
	utils \
	Abalone \
	Candy \
	CCheckers \
	Jetan \
	Mancala \
	Maze \
	PLTest \
	Rectangle \
	RubiksCube \
	ScavengerWorld \
	Sudoku \
	TicTacToe \
	UltimateTicTacToe \
	VertexCover \
	WumpusWorld

all install clean spotless:
	for d in $(PROJECT_LIST); do \
		(cd $$d; $(MAKE) $@) \
	done

include $(MAKE_DIR)/Makefile.dep

# Local Variables:
# mode:makefile
# End:
