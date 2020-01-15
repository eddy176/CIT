MAKE_DIR := $(shell mkpath="."; count=0; while [ \( ! -e "$$mkpath/Makefile.top" \) -a \( "$$count" -lt 10 \) ]; do mkpath="$$mkpath/.."; count=`echo $$count | awk '{print $$1 + 1;}'`; done; echo $$mkpath;)
include $(MAKE_DIR)/Makefile.top

LOCAL_PART    := Agent
LOCAL_SRC_DIR := $(SRC_DIR)/$(LOCAL_PART)
LOCAL_INC_DIR := $(INC_DIR)/$(LOCAL_PART)

AI_SRC := \
	Action.cpp \
	PerceptAtom.cpp \
	Percept.cpp \
	AgentProgram.cpp \
	Location.cpp \
	Object.cpp \
	Agent.cpp \
	Environment.cpp \
	EnvironmentDisplay.cpp \
	Options.cpp \
	Socket.cpp \
	Message.cpp \
	AgentDriver.cpp \
	EnvironmentDriver.cpp \
	DisplayDriver.cpp \
	RandomNumber.cpp \
	FileDescriptor.cpp

AI_HEADERS := \
	Action.h \
	PerceptAtom.h \
	Percept.h \
	AgentProgram.h \
	Location.h \
	Object.h \
	Agent.h \
	Environment.h \
	EnvironmentDisplay.h \
	Options.h \
	Socket.h \
	Message.h \
	AgentDriver.h \
	EnvironmentDriver.h \
	DisplayDriver.h \
	RandomNumber.h \
	FileDescriptor.h

CXX_HEADERS := \
	${AI_HEADERS:%.h=$(LOCAL_PART)/%.h}\
	ai_agent.h ai_glut.h

CXX_SRC  := \
	$(AI_SRC)

TARGET_HEADERS    := ${CXX_HEADERS:%.h=$(AI_INC_DIR)/%.h}
TARGET_OBJS       := ${CXX_SRC:%.cpp=$(OBJ_BASE)/%.o}
TARGET_LIB        := $(AI_LIB_DIR)/libaiagent.a

include $(MAKE_DIR)/Makefile.rules
include $(MAKE_DIR)/Makefile.dep
