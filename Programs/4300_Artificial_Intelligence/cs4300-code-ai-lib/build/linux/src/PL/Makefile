MAKE_DIR := $(shell mkpath="."; count=0; while [ \( ! -e "$$mkpath/Makefile.top" \) -a \( "$$count" -lt 10 \) ]; do mkpath="$$mkpath/.."; count=`echo $$count | awk '{print $$1 + 1;}'`; done; echo $$mkpath;)
include $(MAKE_DIR)/Makefile.top

LOCAL_PART    := PL
LOCAL_SRC_DIR := $(SRC_DIR)/$(LOCAL_PART)
LOCAL_INC_DIR := $(INC_DIR)/$(LOCAL_PART)

PL_SRC := \
	Symbol.cpp \
	Sentence.cpp \
	KnowledgeBase.cpp \
	KnowledgeBaseFast.cpp

PL_HEADERS := \
	Symbol.h \
	Sentence.h \
	KnowledgeBase.h \
	KnowledgeBaseFast.h

PL_TEST_SRC := $(shell ls -1 $(LOCAL_SRC_DIR)/tests/*.cpp)

CXX_HEADERS := \
	${PL_HEADERS:%.h=$(LOCAL_PART)/%.h}\
	ai_pl.h

CXX_SRC  := \
	$(PL_SRC) 

CXX_TEST_SRC := $(PL_TEST_SRC)

TARGET_HEADERS    := ${CXX_HEADERS:%.h=$(AI_INC_DIR)/%.h}
TARGET_OBJS       := ${CXX_SRC:%.cpp=$(OBJ_BASE)/%.o}
TARGET_LIB        := $(AI_LIB_DIR)/libaipl.a

include $(MAKE_DIR)/Makefile.rules
include $(MAKE_DIR)/Makefile.dep
