#
# OS detection
#
OPERATING_SYSTEM := $(shell uname)
ifeq ($(strip $(OPERATING_SYSTEM)),Linux)
LINUX := 1
DARWIN := 0
else ifeq ($(strip $(OPERATING_SYSTEM)),Darwin)
LINUX := 0
DARWIN := 1
else
LINUX := 0
DARWIN := 0
$(error No know operating system found. $(OPERATING_SYSTEM))
endif

#
# Optional compiler flags
#
ifeq ($(strip $(B_OPTIMIZE)),)
B_OPTIMIZE = 1
endif
ifeq ($(strip $(B_DEBUG)),)
B_DEBUG = 0
endif
ifeq ($(strip $(B_PROFILE)),)
B_PROFILE = 0
endif
ifeq ($(strip $(B_DISPLAY)),)
B_DISPLAY = 1
endif

#
# Directory locations
# 
PREFIX_DIR := UNCONFIGURED
AI_PREFIX_DIR := UNCONFIGURED
# Local Variables:
# mode:makefile
# End:
