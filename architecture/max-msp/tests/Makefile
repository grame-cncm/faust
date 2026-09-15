PYTHON ?= python3
.DEFAULT_GOAL := test

.PHONY: help test check faustgen2max faust2gen faust2max6 faust2rnbo \
	faust2max6-integration

help:
	@echo "Max/MSP architecture test targets:"
	@echo "  make test                   Run all portable tests (default)"
	@echo "  make check                  Alias for make test"
	@echo "  make faustgen2max           Run faustgen2max tests"
	@echo "  make faust2gen              Run faust2gen tests"
	@echo "  make faust2max6             Run faust2max6 argument tests"
	@echo "  make faust2rnbo             Run faust2rnbo generation tests"
	@echo "  make faust2max6-integration Compile and verify native Max externals"

test check:
	$(PYTHON) -m unittest discover -s . -p 'test_*.py' -v

faustgen2max:
	$(PYTHON) test_faustgen2max.py -v

faust2gen:
	$(PYTHON) test_faust2gen.py -v

faust2max6:
	$(PYTHON) test_faust2max6.py -v

faust2rnbo:
	$(PYTHON) test_faust2rnbo.py -v

faust2max6-integration:
	FAUST_RUN_MAX_INTEGRATION=1 $(PYTHON) test_faust2max6.py -v
