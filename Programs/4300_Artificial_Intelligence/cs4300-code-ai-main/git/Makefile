BASE_DIR := ../..

DIRS := \
	$(BASE_DIR)/cs4300-code-ai-main \
	$(BASE_DIR)/cs4300-code-ai-lib \
	$(BASE_DIR)/cs4300-code-ai-environment \
	$(BASE_DIR)/cs4300-code-ai-agents \
	$(BASE_DIR)/cs4300-code-ai-cgl \
	$(BASE_DIR)/cs4300-code-ai-students \
	$(BASE_DIR)/cs4300-code-ai

all:
	@echo Choose something to do

git-status:
	for d in $(DIRS); do \
	  ( echo "-------------------------------------------------"; \
	    echo $$d; \
	    cd $$d; \
	    git status; \
	    echo ""; \
	  ); \
	done

git-pull:
	for d in $(DIRS); do \
	  ( echo "-------------------------------------------------"; \
	    echo $$d; \
	    cd $$d; \
	    git pull; \
	    echo ""; \
	  ); \
	done

git-push:
	for d in $(DIRS); do \
	  ( echo "-------------------------------------------------"; \
	    echo $$d; \
	    cd $$d; \
	    git push; \
	    echo ""; \
	  ); \
	done

git-branch-list:
	for d in $(DIRS); do \
	  ( echo "-------------------------------------------------"; \
	    echo $$d; \
	    cd $$d; \
	    git branch --list; \
	    echo ""; \
	  ); \
	done

git-branch-a:
	for d in $(DIRS); do \
	  ( echo "-------------------------------------------------"; \
	    echo $$d; \
	    cd $$d; \
	    git branch -a; \
	    echo ""; \
	  ); \
	done

git-checkout-dev:
	for d in $(DIRS); do \
	  ( echo "-------------------------------------------------"; \
	    echo $$d; \
	    cd $$d; \
	    git checkout dev; \
	    echo ""; \
	  ); \
	done

git-checkout-unit-test:
	for d in $(DIRS); do \
	  ( echo "-------------------------------------------------"; \
	    echo $$d; \
	    cd $$d; \
	    git checkout unit-test; \
	    echo ""; \
	  ); \
	done

git-checkout-master:
	for d in $(DIRS); do \
	  ( echo "-------------------------------------------------"; \
	    echo $$d; \
	    cd $$d; \
	    git checkout master; \
	    echo ""; \
	  ); \
	done

git-merge-dev:
	for d in $(DIRS); do \
	  ( echo "-------------------------------------------------"; \
	    echo $$d; \
	    cd $$d; \
	    git merge dev; \
	    echo ""; \
	  ); \
	done

git-merge-master:
	for d in $(DIRS); do \
	  ( echo "-------------------------------------------------"; \
	    echo $$d; \
	    cd $$d; \
	    git merge master; \
	    echo ""; \
	  ); \
	done

git-push-origin-master:
	for d in $(DIRS); do \
	  ( echo "-------------------------------------------------"; \
	    echo $$d; \
	    cd $$d; \
	    git push origin master; \
	    echo ""; \
	  ); \
	done
