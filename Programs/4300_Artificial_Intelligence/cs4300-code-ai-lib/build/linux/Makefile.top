MAKE_CONFIG := Makefile.config
MAKE_CONFIG_IN := $(MAKE_CONFIG).in

-include $(MAKE_DIR)/$(MAKE_CONFIG)

#
# directory locations
# 
AI_BIN_DIR       := $(AI_PREFIX_DIR)/bin
AI_LIB_DIR       := $(AI_PREFIX_DIR)/lib
AI_SRC_DIR       := $(AI_PREFIX_DIR)/src
AI_PROG_DIR      := $(AI_PREFIX_DIR)/prog
AI_INC_DIR       := $(AI_PREFIX_DIR)/include
AI_THIRD_DIR     := $(AI_PREFIX_DIR)/third
AI_BUILD_DIR     := $(AI_PREFIX_DIR)/build/linux
AI_UTIL_DIR      := $(AI_PREFIX_DIR)/prog/utils

SRC_DIR          := $(PREFIX_DIR)/src
PROG_DIR         := $(PREFIX_DIR)/prog
INC_DIR          := $(PREFIX_DIR)/include
THIRD_DIR        := $(PREFIX_DIR)/third
BUILD_DIR        := $(PREFIX_DIR)/build/linux
UTIL_DIR         := $(PREFIX_DIR)/prog/utils
OBJ_BASE         := 00obj
LIB_BASE         := 00lib
BIN_BASE         := 00bin

#
# debug, release, profile
#
CXX_DRP     := 
DIR_POSTFIX :=
ifeq ($(strip $(B_OPTIMIZE)),1)
CXX_DRP := $(CXX_DRP) -O2
DIR_POSTFIX := $(DIR_POSTFIX)o
endif
ifeq ($(strip $(B_DEBUG)),1)
CXX_DRP := $(CXX_DRP) -g
DIR_POSTFIX := $(DIR_POSTFIX)g
endif
ifeq ($(strip $(B_PROFILE)),1)
CXX_DRP := $(CXX_DRP) -pg
DIR_POSTFIX := $(DIR_POSTFIX)p
endif
ifeq ($(strip $(B_DISPLAY)),1)
CXX_DRP := $(CXX_DRP) -DUSE_GLUT
DIR_POSTFIX := $(DIR_POSTFIX)
endif

ifneq ($(strip $(DIR_POSTFIX)),)
OBJ_BASE   := $(OBJ_BASE)-$(DIR_POSTFIX)
AI_LIB_DIR := $(AI_LIB_DIR)/$(LIB_BASE)-$(DIR_POSTFIX)
AI_BIN_DIR := $(AI_BIN_DIR)/$(BIN_BASE)-$(DIR_POSTFIX)
endif
FORCE_OBJ_BASE := $(OBJ_BASE)/.force_build

LIB_FILES        := \
	$(AI_LIB_DIR)/libaienvironment.a \
	$(AI_LIB_DIR)/libaiagent.a \
	$(AI_LIB_DIR)/libaisearch.a \
	$(AI_LIB_DIR)/libailocalsearch.a \
	$(AI_LIB_DIR)/libaicsp.a \
	$(AI_LIB_DIR)/libaipl.a \
	$(AI_LIB_DIR)/libaifol.a

#
# compiler values
#
DEBUG_ERROR := 4
DEBUG_ERROR_MSG := 12
DEBUG_ERROR_DISPLAY := 20
DEBUG_ERROR_MSG_DISPLAY := 28
DEBUG_ERROR_ENV := 68
DEBUG_ERROR_MSG_ENV := 76
DEBUG_ERROR_MSG_DISPLAY_ENV := 92
DEBUG_LEVEL := $(DEBUG_ERROR)
#DEBUG_LEVEL := $(DEBUG_ERROR_ENV)
LDFLAGS  := -L$(AI_LIB_DIR) -laienvironment -laiagent -laisearch -lailocalsearch -laicsp -laipl -laifol -lpthread
CXXFLAGS    := -I$(AI_INC_DIR)              -Wall -Werror $(CXX_DRP) -std=c++11 -DDEBUG_LEVEL=$(DEBUG_LEVEL)

ifeq ($(LINUX),1)
LDFLAGS := $(LDFLAGS) -lglut -lGLU -lGL 
else ifeq ($(DARWIN),1)
LDFLAGS := $(LDFLAGS) -L /usr/local/lib -lglut
LDFLAGS := $(LDFLAGS) -framework OpenGL
#LDFLAGS := $(LDFLAGS) -framework GLUT 
CXXFLAGS := $(CXXFLAGS) -Wno-deprecated
else
LDFLAGS := $(LDFLAGS) -lglut -lGLU -lGL 
endif

DEPCXXFLAGS := -I$(INC_DIR) -I$(AI_INC_DIR) -Wall -Werror $(CXX_DRP) -std=c++11 -DDEBUG_LEVEL=$(DEBUG_LEVEL)
CXX      := g++
CC       := gcc

#
# required libraries
#
UBUNTU_PACKAGES := libglu1-mesa-dev mesa-common-dev libxext-dev g++ libxxf86vm-dev libxi-dev freeglut3-dev libgl1-mesa-dev
UBUNTU_PACKAGE_COUNT := 8
BREW_PACKAGES := freeglut
BREW_PACKAGES_RE := ^(freeglut)$$
BREW_PACKAGE_COUNT := 1

#
# make values
#
MAX_JOBS := 8
MAKE_FLAGS := -k -j $(MAX_JOBS)

# Local Variables:
# mode:makefile
# End:
