ifeq ($(LINUX),1)
SED := sed -i
else ifeq ($(DARWIN),1)
SED := sed -i ''
else
SED := sed -i
endif

configure: $(MAKE_CONFIG)
	@echo Configuring the location of your directory tree
	@(x=`pwd`; x=`dirname $$x`; x=`dirname $$x`; \
	 $(SED) 's?^PREFIX_DIR *:=.*$$?PREFIX_DIR := '$$x'?' $(MAKE_CONFIG))
	@(x=`pwd`; x=`dirname $$x`; x=`dirname $$x`; x=`dirname $$x`; \
	 $(SED) 's?^AI_PREFIX_DIR *:=.*$$?AI_PREFIX_DIR := '$$x'/cs4300-code-ai?' $(MAKE_CONFIG))
	@echo Checking your installed development packages
ifeq ($(LINUX),1)
	@(x=`dpkg --list $(UBUNTU_PACKAGES) | egrep ^ii | wc -l`; if [ "$$x" != "$(UBUNTU_PACKAGE_COUNT)" ]; then echo "*** You must: sudo apt install $(UBUNTU_PACKAGES)"; fi)
else ifeq ($(DARWIN),1)
	@echo Hope you have the correct packages installed on your OS.
	@(x=`brew list | egrep '$(BREW_PACKAGES_RE)' | wc -l`; if [ "$$x" -ne "$(BREW_PACKAGE_COUNT)" ]; then echo "*** You must: brew install $(BREW_PACKAGES)"; fi)
endif

configure-optimize-on: $(MAKE_CONFIG)
	$(SED) 's?^B_OPTIMIZE *=.*$$?B_OPTIMIZE = 1?' $(MAKE_CONFIG)
configure-optimize-off: $(MAKE_CONFIG)
	$(SED) 's?^B_OPTIMIZE *=.*$$?B_OPTIMIZE = 0?' $(MAKE_CONFIG)
configure-debug-on: $(MAKE_CONFIG)
	$(SED) 's?^B_DEBUG *=.*$$?B_DEBUG = 1?' $(MAKE_CONFIG)
configure-debug-off: $(MAKE_CONFIG)
	$(SED) 's?^B_DEBUG *=.*$$?B_DEBUG = 0?' $(MAKE_CONFIG)
configure-profile-on: $(MAKE_CONFIG)
	$(SED) 's?^B_PROFILE *=.*$$?B_PROFILE = 1?' $(MAKE_CONFIG)
configure-profile-off: $(MAKE_CONFIG)
	$(SED) 's?^B_PROFILE *=.*$$?B_PROFILE = 0?' $(MAKE_CONFIG)
configure-display-on: $(MAKE_CONFIG)
	$(SED) 's?^B_DISPLAY *=.*$$?B_DISPLAY = 1?' $(MAKE_CONFIG)
configure-display-off: $(MAKE_CONFIG)
	$(SED) 's?^B_DISPLAY *=.*$$?B_DISPLAY = 0?' $(MAKE_CONFIG)
# Local Variables:
# mode:makefile
# End:
