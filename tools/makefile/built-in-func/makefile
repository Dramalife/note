files := $(shell ls .)
files := $(filter-out makefile, $(files))

all:
	for f in $(files); do \
	  echo "\n\n#####\n# $$f\n#####"; \
	  make -f $$f; \
	done
