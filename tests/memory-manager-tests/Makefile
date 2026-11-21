CXX ?= c++
CXXFLAGS ?= -O2 -std=c++14
CPPFLAGS ?= -I../../architecture
FAUST ?= faust

.PHONY: check clean

check: tiered-memory-test
	./tiered-memory-test

tiersmem.h: tiers.dsp
	$(FAUST) -mem -cn tiersmem -i $< -o $@

tiersplain.h: tiers.dsp
	$(FAUST) -cn tiersplain -i $< -o $@

tiered-memory-test: tiered-memory-test.cpp tiersmem.h tiersplain.h ../../architecture/faust/dsp/tiered-memory-manager.h
	$(CXX) $(CPPFLAGS) -I. $(CXXFLAGS) $< -o $@

clean:
	rm -f tiered-memory-test tiersmem.h tiersplain.h
