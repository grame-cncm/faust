#
# Acceptance policy : every program of refused/ must be refused, and every program of
# accepted/ accepted, under each option set. `make check` prints one line per program
# and option set, a count, and fails when there is at least one mismatch.
#

FAUST ?= ../../build/bin/faust

OPTION_SETS := "-lang cpp" "-lang ocpp" "-lang c" "-lang cpp -double" \
               "-lang cpp -mcd 2000" "-lang cpp -dlt 0" "-lang rust -dlt 0" "-lang ocpp -ls"

.PHONY: check check-nocert check-mcs
check:
	@$(FAUST) --version | sed -n 2p
	@out=$$(mktemp -d); bad=0; n=0; \
	for set in $(OPTION_SETS); do \
	  for f in refused/*.dsp accepted/*.dsp; do \
	    n=$$((n+1)); \
	    if $(FAUST) $$set $$f -o $$out/x > /dev/null 2> $$out/err; then got=accepted; else got=refused; fi; \
	    want=$${f%%/*}; \
	    if [ "$$got" = "$$want" ]; then echo "ok        $$f [$$set] $$got"; \
	    else echo "MISMATCH  $$f [$$set] $$got, expected $$want"; head -2 $$out/err; bad=$$((bad+1)); fi; \
	  done; \
	done; \
	rm -r $$out; \
	echo "$$n verdicts, $$bad mismatches"; \
	test $$bad -eq 0

# -nocert : the programs of nocert/ and the delays whose lower bound only may be negative are
# refused by default and accepted under -nocert ; every other program of refused/ stays refused
NOCERT_ACCEPTED := refused/delay-slider-negative.dsp $(wildcard nocert/*.dsp)

check-nocert:
	@$(FAUST) --version | sed -n 2p
	@out=$$(mktemp -d); bad=0; n=0; \
	for f in refused/*.dsp nocert/*.dsp; do \
	  case " $(NOCERT_ACCEPTED) " in *" $$f "*) want=accepted;; *) want=refused;; esac; \
	  for set in "" "-nocert"; do \
	    n=$$((n+1)); \
	    if [ -z "$$set" ]; then w=refused; else w=$$want; fi; \
	    if $(FAUST) $$set $$f -o $$out/x > /dev/null 2> $$out/err; then got=accepted; else got=refused; fi; \
	    if [ "$$got" = "$$w" ]; then echo "ok        $$f [$$set] $$got"; \
	    else echo "MISMATCH  $$f [$$set] $$got, expected $$w"; head -2 $$out/err; bad=$$((bad+1)); fi; \
	  done; \
	done; \
	rm -r $$out; \
	echo "$$n verdicts, $$bad mismatches"; \
	test $$bad -eq 0

# -mcs : the programs of mcs/ are certified for a duration between 10 and 60 seconds at
# 48000 Hz : accepted by default (-mcs 10), refused under -mcs 60, accepted again under
# -mcs 60 -nocert
check-mcs:
	@$(FAUST) --version | sed -n 2p
	@out=$$(mktemp -d); bad=0; n=0; \
	for f in mcs/*.dsp; do \
	  for set in "" "-mcs 60" "-mcs 60 -nocert"; do \
	    n=$$((n+1)); \
	    if [ "$$set" = "-mcs 60" ]; then w=refused; else w=accepted; fi; \
	    if $(FAUST) $$set $$f -o $$out/x > /dev/null 2> $$out/err; then got=accepted; else got=refused; fi; \
	    if [ "$$got" = "$$w" ]; then echo "ok        $$f [$$set] $$got"; \
	    else echo "MISMATCH  $$f [$$set] $$got, expected $$w"; head -2 $$out/err; bad=$$((bad+1)); fi; \
	  done; \
	done; \
	rm -r $$out; \
	echo "$$n verdicts, $$bad mismatches"; \
	test $$bad -eq 0
