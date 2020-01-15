GTEST_DIR := ../..

all: libgtest.a libgtest_main.a install

make configure:
	@echo "googletest $@ ok"

libgtest.a:
	g++ -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) \
	    -pthread -c $(GTEST_DIR)/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o

libgtest_main.a:
	g++ -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) \
	    -pthread -c $(GTEST_DIR)/src/gtest_main.cc
	ar -rv libgtest_main.a gtest_main.o


LIB_DIR_BASE := ../../../cs4300-code-ai/lib
INCLUDE_DIR_BASE := ../../../cs4300-code-ai/include
LIB_GTEST := $(LIB_DIR_BASE)/libgtest.a
LIB_GTEST_MAIN := $(LIB_DIR_BASE)/libgtest_main.a
LIB_DIRS := $(LIB_DIR_BASE)/00lib-g $(LIB_DIR_BASE)/00lib-o $(LIB_DIR_BASE)/00lib-gp
LIB_LINKS1 := $(patsubst %,%/libgtest.a,$(LIB_DIRS))
LIB_LINKS2 := $(patsubst %,%/libgtest_main.a,$(LIB_DIRS))

$(LIB_LINKS1):
	for d in $@; do \
		(ln -s ../libgtest.a $$d;) \
	done

$(LIB_LINKS2):
	for d in $@; do \
		(ln -s ../libgtest_main.a $$d;) \
	done

$(LIB_GTEST): libgtest.a
	cp $^ $@

$(LIB_GTEST_MAIN): libgtest_main.a
	cp $^ $@

SRC_INCLUDE_FILES := $(shell find $(GTEST_DIR)/include/gtest/ -type f)
DST_INCLUDE_FILES := $(patsubst $(GTEST_DIR)/include/%,$(INCLUDE_DIR_BASE)/%,$(SRC_INCLUDE_FILES))

$(DST_INCLUDE_FILES) : $(INCLUDE_DIR_BASE)/% : $(GTEST_DIR)/include/%
	@d=`dirname $@`; if [ ! -e $$d ]; then mkdir -p $$d; fi
	cp $^ $@

install: $(LIB_GTEST) $(LIB_GTEST_MAIN) $(LIB_LINKS1) $(LIB_LINKS2) $(DST_INCLUDE_FILES)

clean:
	rm -f libgtest.a gtest-all.o libgtest_main.a gtest_main.o

spotless: clean
	rm -f $(DST_INCLUDE_FILES)
	rm -f $(LIB_LINKS1) $(LIB_LINKS2)
	rm -f $(LIB_GTEST) $(LIB_GTEST_MAIN)


