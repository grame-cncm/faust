CXX ?= c++
CXXFLAGS ?= -O2 -std=c++14
CPPFLAGS ?= -I../../architecture

.PHONY: check clean

check: rpn-number-repro
	./rpn-number-repro

rpn-number-repro: rpn-number-repro.cpp ../../architecture/faust/midi/midi.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@

clean:
	rm -f rpn-number-repro
