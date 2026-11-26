CXX ?= c++
ARCH ?= ../../architecture
CXXFLAGS ?= -O2

.PHONY: check-sr-adapter-reset
check-sr-adapter-reset:
	@set -eu; status=0; tmp=$$(mktemp -d); trap 'rm -rf "$$tmp"' EXIT; \
	for precision in float double; do \
	  $(CXX) $(CXXFLAGS) -std=c++11 -ffp-contract=off -DFAUSTFLOAT=$$precision \
	    -I"$(ARCH)" sr-adapter-reset.cpp -o "$$tmp/test"; \
	  echo "Sample-rate adapter reset ($$precision)"; \
	  "$$tmp/test" || status=1; \
	done; exit $$status

.PHONY: check-combiner-control
check-combiner-control:
	@set -eu; status=0; tmp=$$(mktemp -d); trap 'rm -rf "$$tmp"' EXIT; \
	for precision in float double; do \
	  $(CXX) $(CXXFLAGS) -std=c++11 -ffp-contract=off -DFAUSTFLOAT=$$precision \
	    -I"$(ARCH)" combiner-control.cpp -o "$$tmp/test"; \
	  echo "DSP combiner control ($$precision)"; \
	  "$$tmp/test" || status=1; \
	done; exit $$status

.PHONY: check-timed-controls
check-timed-controls:
	@set -eu; status=0; tmp=$$(mktemp -d); trap 'rm -rf "$$tmp"' EXIT; \
	for precision in float double; do \
	  $(CXX) $(CXXFLAGS) -std=c++11 -ffp-contract=off -DFAUSTFLOAT=$$precision \
	    -I"$(ARCH)" timed-controls.cpp -o "$$tmp/test"; \
	  echo "Timed controls ($$precision)"; \
	  "$$tmp/test" || status=1; \
	done; exit $$status
