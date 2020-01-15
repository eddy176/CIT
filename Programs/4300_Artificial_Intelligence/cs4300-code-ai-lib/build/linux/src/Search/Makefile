MAKE_DIR := $(shell mkpath="."; count=0; while [ \( ! -e "$$mkpath/Makefile.top" \) -a \( "$$count" -lt 10 \) ]; do mkpath="$$mkpath/.."; count=`echo $$count | awk '{print $$1 + 1;}'`; done; echo $$mkpath;)
include $(MAKE_DIR)/Makefile.top

LOCAL_PART    := Search
LOCAL_SRC_DIR := $(SRC_DIR)/$(LOCAL_PART)
LOCAL_INC_DIR := $(INC_DIR)/$(LOCAL_PART)

SEARCH_SRC := \
	Action.cpp \
	State.cpp \
	ActionStatePair.cpp \
	Node.cpp \
	Problem.cpp \
	Frontier.cpp \
		BFFrontier.cpp \
		UCFrontier.cpp \
		DFFrontier.cpp \
		DLFrontier.cpp \
		GreedyFrontier.cpp \
		AStarFrontier.cpp \
		AStarLimitedFrontier.cpp \
		BFLimitedFrontier.cpp \
	Solution.cpp \
	Algorithm.cpp \
		Tree.cpp \
		Graph.cpp \
			ClosedList.cpp

SEARCH_HEADERS := \
	Action.h \
	State.h \
	ActionStatePair.h \
	Node.h \
	Problem.h \
	Frontier.h \
		BFFrontier.h \
		UCFrontier.h \
		DFFrontier.h \
		DLFrontier.h \
		GreedyFrontier.h \
		AStarFrontier.h \
		AStarLimitedFrontier.h \
		BFLimitedFrontier.h \
	Solution.h \
	Algorithm.h \
		Tree.h \
		Graph.h \
			ClosedList.h


CXX_HEADERS := \
	${SEARCH_HEADERS:%.h=$(LOCAL_PART)/%.h}\
	ai_search.h

CXX_SRC  := \
	$(SEARCH_SRC) 

TARGET_HEADERS    := ${CXX_HEADERS:%.h=$(AI_INC_DIR)/%.h}
TARGET_OBJS       := ${CXX_SRC:%.cpp=$(OBJ_BASE)/%.o}
TARGET_LIB        := $(AI_LIB_DIR)/libaisearch.a

include $(MAKE_DIR)/Makefile.rules
include $(MAKE_DIR)/Makefile.dep
