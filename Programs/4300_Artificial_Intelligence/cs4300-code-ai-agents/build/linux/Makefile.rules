RULES_MK := ../../../cs4300-code-ai-main/build/linux/mk/rules.mk
DEP_MK := ../../../cs4300-code-ai-main/build/linux/mk/dep.mk
TOP_MK := ../../../cs4300-code-ai-main/build/linux/mk/top.mk
CONFIG_IN_MK := ../../../cs4300-code-ai-main/build/linux/mk/config_in.mk
CONFIGURE_RULES_MK := ../../../cs4300-code-ai-main/build/linux/mk/configure_rules.mk

all: \
	$(TARGET_HEADERS) \
	$(OBJ_BASE) $(AI_LIB_DIR) $(AI_BIN_DIR) \
	$(TARGET_LIB) \
	$(TARGET_PROG)

install: all 

ifneq ($(strip $(TARGET_OBJS)),)

# This amendment must be here, because top.mk is included before REMOTE_INC_DIR is known
ifneq ($(strip $(REMOTE_INC_DIR)),)
CXXFLAGS := $(CXXFLAGS) -I$(REMOTE_INC_DIR)
endif

$(TARGET_LIB): $(TARGET_OBJS)
	@mkdir -p `dirname $@`
	ar crs $@ $?

$(TARGET_PROG): $(TARGET_OBJS) $(LIB_FILES)
	@mkdir -p `dirname $@`
	$(CXX) $(CXXFLAGS) -o $@ $(TARGET_OBJS) $(LDFLAGS)

endif

ifneq ($(strip $(TARGET_HEADERS)),)

$(TARGET_HEADERS): $(AI_INC_DIR)/%.h : $(INC_DIR)/%.h
	@mkdir -p `dirname $@`
	cp $< $@

endif


ifneq ($(strip $(CXX_TEST_SRC)),)

unit-test-prog: $(TARGET_LIB) $(TARGET_OBJS) 
	$(CXX) -o unit-test-prog -I$(LOCAL_INC_DIR) $(CXXFLAGS) -pthread $(CXX_TEST_SRC) $(TARGET_OBJS) $(LDFLAGS) -lgtest -lgtest_main

unit-test: unit-test-prog
	./unit-test-prog
	@rm -f ./unit-test-prog
else

unit-test-prog:
	@echo "No unit-test-prog defined."

unit-test:
	@echo "No unit-test defined."

endif

objs: $(OBJ_BASE) $(TARGET_OBJS)
libs: $(AI_LIB_DIR) $(TARGET_LIB)
bins: $(AI_BIN_DIR) $(TARGET_PROG)

$(OBJ_BASE) $(AI_LIB_DIR) $(AI_BIN_DIR):
	mkdir -p $@

$(FORCE_OBJ_BASE):
	-mkdir -p $(OBJ_BASE)
	touch $(FORCE_OBJ_BASE)

clean:
	-rm -f $(CXX_SRC_DEPS)
	-rm -f $(TARGET_OBJS)
	-d=$(OBJ_BASE); if [ -d $$d ]; then if [ `ls -A $$d | wc -l` = "0" ]; then rmdir $$d; fi; fi
	-rm -f *~
	-rm -f $(LOCAL_INC_DIR)/*~
	-rm -f $(LOCAL_SRC_DIR)/*~
	-rm -f $(INC_DIR)/*~

ifeq ($(strip $(LOCAL_SPOTLESS)),)
spotless: clean
else
spotless: clean local_spotless
endif
	-rm -f $(CXX_SRC_DEPS)
	-rm -f $(TARGET_LIB)
	-d=$(AI_LIB_DIR); if [ -d $$d ]; then if [ `ls -A $$d | wc -l` = "0" ]; then rmdir $$d; fi; fi
	-d=$(AI_PREFIX_DIR)/lib; if [ -d $$d ]; then if [ `ls -A $$d | wc -l` = "0" ]; then rmdir $$d; fi; fi
	-rm -f $(TARGET_PROG)
	-d=$(AI_BIN_DIR); if [ -d $$d ]; then if [ `ls -A $$d | wc -l` = "0" ]; then rmdir $$d; fi; fi
	-d=$(AI_PREFIX_DIR)/bin; if [ -d $$d ]; then if [ `ls -A $$d | wc -l` = "0" ]; then rmdir $$d; fi; fi
	-rm -f $(TARGET_HEADERS)
	-d=$(AI_INC_DIR)/$(LOCAL_PART); if [ -d $$d ]; then if [ `ls -A $$d | wc -l` = "0" ]; then rmdir $$d; fi; fi
	-d=$(AI_INC_DIR); if [ -d $$d ]; then if [ `ls -A $$d | wc -l` = "0" ]; then rmdir $$d; fi; fi
	-d=$(AI_PREFIX_DIR)/include; if [ -d $$d ]; then if [ `ls -A $$d | wc -l` = "0" ]; then rmdir $$d; fi; fi
	-rm -f $(TARGET_OBJS)
	-d=$(OBJ_BASE); if [ -d $$d ]; then if [ `ls -A $$d | wc -l` = "0" ]; then rmdir $$d; fi; fi

ifneq ($(strip $(LOCAL_AGENT_SELECT)),)
Makefile.agents $(LOCAL_SRC_DIR)/$(LOCAL_AGENT_SELECT): $(UTIL_DIR)/AddAgentPrograms.pl $(LOCAL_SRC_DIR)/AgentPrograms.pm
	$(UTIL_DIR)/AddAgentPrograms.pl -A $(LOCAL_SRC_DIR)/AgentPrograms.pm -S $(LOCAL_SRC_DIR)/$(LOCAL_AGENT_SELECT) -M Makefile.agents
endif
# Local Variables:
# mode:makefile
# End:
