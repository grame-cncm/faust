CXX ?= c++
CXXFLAGS ?= -O2 -std=c++14
CPPFLAGS ?= -I../../architecture
FAUST ?= faust

GENERATED = tiersmem.h tiersplain.h tablesmem.h tablesplain.h

.PHONY: check clean

check: tiered-memory-test
	./tiered-memory-test

%mem.h: %.dsp
	$(FAUST) -mem -cn $*mem -i $< -o $@

%plain.h: %.dsp
	$(FAUST) -cn $*plain -i $< -o $@

tiered-memory-test: tiered-memory-test.cpp $(GENERATED) ../../architecture/faust/dsp/tiered-memory-manager.h
	$(CXX) $(CPPFLAGS) -I. $(CXXFLAGS) $< -o $@

clean:
	rm -f tiered-memory-test $(GENERATED)
	rm -rf tiered-memory-test.dSYM
