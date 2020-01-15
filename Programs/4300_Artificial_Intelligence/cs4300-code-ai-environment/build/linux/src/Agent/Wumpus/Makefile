MAKE_DIR := $(shell mkpath="."; count=0; while [ \( ! -e "$$mkpath/Makefile.top" \) -a \( "$$count" -lt 10 \) ]; do mkpath="$$mkpath/.."; count=`echo $$count | awk '{print $$1 + 1;}'`; done; echo $$mkpath;)

include $(MAKE_DIR)/Makefile.top

LOCAL_PART    := Agent/Wumpus
LOCAL_SRC_DIR := $(SRC_DIR)/$(LOCAL_PART)
LOCAL_INC_DIR := $(INC_DIR)/$(LOCAL_PART)

AI_SRC := \
	WumpusAction.cpp \
	WumpusAgent.cpp \
	WumpusDisplayDriver.cpp \
	WumpusEnvironment.cpp \
	WumpusEnvironmentDisplay.cpp \
	WumpusEnvironmentDriver.cpp \
	WumpusObjects.cpp

AI_HEADERS := \
	WumpusAction.h \
	WumpusAgent.h \
	WumpusDisplayDriver.h \
	WumpusEnvironment.h \
	WumpusEnvironmentDisplay.h \
	WumpusEnvironmentDriver.h \
	WumpusObjects.h

CXX_HEADERS := \
	${AI_HEADERS:%.h=$(LOCAL_PART)/%.h}\
	ai_wumpus.h 

CXX_SRC  := \
	$(AI_SRC) 


TARGET_HEADERS    := ${CXX_HEADERS:%.h=$(AI_INC_DIR)/%.h}
TARGET_OBJS       := ${CXX_SRC:%.cpp=$(OBJ_BASE)/%.o}
TARGET_LIB        := $(AI_LIB_DIR)/libaienvironment.a

include $(MAKE_DIR)/Makefile.rules
include $(MAKE_DIR)/Makefile.dep

# Local Variables:
# mode:makefile
# End:
