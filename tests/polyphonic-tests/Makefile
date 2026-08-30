CXX ?= c++
CXXFLAGS ?= -O2 -std=c++14
CPPFLAGS ?= -I../../architecture

.PHONY: check clean

check: voice-steal-repro legato-fade-repro
	./voice-steal-repro
	./legato-fade-repro

voice-steal-repro: voice-steal-repro.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@

legato-fade-repro: legato-fade-repro.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@

clean:
	rm -f voice-steal-repro legato-fade-repro
