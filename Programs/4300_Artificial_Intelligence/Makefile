DIRS := googletest cs4300-code-ai-lib cs4300-code-ai-environment cs4300-code-ai-agents

default:
	$(MAKE) all

%:
	for d in $(DIRS); do \
		$(MAKE) -C $$d/build/linux $@; \
	done
