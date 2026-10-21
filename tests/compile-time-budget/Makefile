#
# The compile-time budget : `make check FAUST=<faust under test> REF=<reference faust>`
# compiles the impulse tests and the slowest programs with both binaries, single and double
# precision, and fails when a ratio of times passes its ceiling (TOTAL for a whole set, ONE
# for a single program), when faust refuses a program the reference accepts, or when a
# compilation takes more than TIMEOUT seconds. Measure on a quiet machine.
#

FAUST ?= ../../build/bin/faust
REF   ?=
TOTAL ?= 3.0
ONE   ?= 8.0
FLOOR ?= 0.05
RUNS  ?= 3
TIMEOUT ?= 300

.PHONY: check
check:
	@test -n "$(REF)" || { echo "REF must name the reference faust binary"; exit 1; }
	@python3 budget.py $(FAUST) $(REF) --total $(TOTAL) --one $(ONE) --floor $(FLOOR) --runs $(RUNS) --timeout $(TIMEOUT)
