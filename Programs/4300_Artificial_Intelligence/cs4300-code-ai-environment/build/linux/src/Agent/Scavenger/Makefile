MAKE_DIR := $(shell mkpath="."; count=0; while [ \( ! -e "$$mkpath/Makefile.top" \) -a \( "$$count" -lt 10 \) ]; do mkpath="$$mkpath/.."; count=`echo $$count | awk '{print $$1 + 1;}'`; done; echo $$mkpath;)

include $(MAKE_DIR)/Makefile.top

LOCAL_PART    := Agent/Scavenger
LOCAL_SRC_DIR := $(SRC_DIR)/$(LOCAL_PART)
LOCAL_INC_DIR := $(INC_DIR)/$(LOCAL_PART)

AI_SRC := \
	ScavengerCell.cpp \
	ScavengerCellInterface.cpp \
	ScavengerLocation.cpp \
	ScavengerObject.cpp \
	ScavengerBase.cpp \
	ScavengerAgent.cpp \
	ScavengerDisplayDriver.cpp \
	ScavengerEnvironment.cpp \
	ScavengerEnvironmentDisplay.cpp \
	ScavengerEnvironmentDisplay3D.cpp \
	ScavengerEnvironmentDriver.cpp \
	ScavengerTexture.cpp \
	ScavengerEnvironmentModel.cpp \
	ScavengerHover.cpp \
	ScavengerModel.cpp \
	ScavengerAction.cpp 

AI_HEADERS := \
	ScavengerCell.h \
	ScavengerCellInterface.h \
	ScavengerLocation.h \
	ScavengerObject.h \
	ScavengerBase.h \
	ScavengerAgent.h \
	ScavengerDisplayDriver.h \
	ScavengerEnvironment.h \
	ScavengerEnvironmentDisplay.h \
	ScavengerEnvironmentDisplay3D.h \
	ScavengerEnvironmentDriver.h \
	ScavengerTexture.h \
	ScavengerEnvironmentModel.h \
	ScavengerHover.h \
	ScavengerModel.h \
	ScavengerAction.h

CXX_HEADERS := \
	${AI_HEADERS:%.h=$(LOCAL_PART)/%.h}\
	ai_scavenger.h 

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
