MAKE_DIR := $(shell mkpath="."; count=0; while [ \( ! -e "$$mkpath/Makefile.top" \) -a \( "$$count" -lt 10 \) ]; do mkpath="$$mkpath/.."; count=`echo $$count | awk '{print $$1 + 1;}'`; done; echo $$mkpath;)

include $(MAKE_DIR)/Makefile.top

LOCAL_PART    := Agent
LOCAL_SRC_DIR := $(SRC_DIR)/$(LOCAL_PART)
LOCAL_INC_DIR := $(INC_DIR)/$(LOCAL_PART)

AI_SRC :=

AI_HEADERS := 

CXX_HEADERS := \
	${AI_HEADERS:%.h=$(LOCAL_PART)/%.h}

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
