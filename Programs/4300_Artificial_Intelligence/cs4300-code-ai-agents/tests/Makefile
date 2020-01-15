ROBOT := $(shell which robot)

all: test

test: $(ROBOT)
ifndef ROBOT
	$(error "robot is not available, install robot framework.")
endif
	$(ROBOT) pl_tests.txt


clean:
	-rm -f log.html output.xml report.html
	-rm -f *~
