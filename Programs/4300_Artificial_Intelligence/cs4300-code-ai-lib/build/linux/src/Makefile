MAKE_DIR := $(shell mkpath="."; count=0; while [ \( ! -e "$$mkpath/Makefile.top" \) -a \( "$$count" -lt 10 \) ]; do mkpath="$$mkpath/.."; count=`echo $$count | awk '{print $$1 + 1;}'`; done; echo $$mkpath;)
include $(MAKE_DIR)/Makefile.top

PROJECT_LIST  := Support Agent Search LocalSearch PL FOL CSP

all install clean spotless:
	for d in $(PROJECT_LIST); do \
		(cd $$d; $(MAKE) $(MAKE_FLAGS) $@) \
	done

include $(MAKE_DIR)/Makefile.dep
