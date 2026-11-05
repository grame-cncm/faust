CXX ?= c++
CXXFLAGS ?= -O2 -std=c++14
CPPFLAGS ?= -I../../architecture

.PHONY: check clean

check: rpn-nrpn-decoding
	./rpn-nrpn-decoding

rpn-nrpn-decoding: rpn-nrpn-decoding.cpp ../../architecture/faust/midi/midi.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@

clean:
	rm -f rpn-nrpn-decoding
