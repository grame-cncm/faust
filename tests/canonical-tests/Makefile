# Canonicity of the normal form : see canonical.py and tests/TESTING.md (Gate 6)
FAUST  ?= ../../build/bin/faust
PYTHON ?= python3
LIB    ?= ../../libraries

.PHONY: check update help

check:
	$(PYTHON) canonical.py --faust $(FAUST) --lib $(LIB)

update:
	$(PYTHON) canonical.py --faust $(FAUST) --lib $(LIB) --update

help:
	@echo "make check  : compare every writing of each family with its reference (FAUST=<binary>)"
	@echo "make update : rewrite expected.tsv from the observed statuses, keeping the reasons"
