CXX ?= c++
CXXFLAGS ?= -O2 -std=c++14
CPPFLAGS ?= -I../../architecture
FAUST ?= faust

.PHONY: check clean

check: voice-steal-repro legato-fade-repro bargraph-current-repro mcu-poly mcu-poly-nortti
	./voice-steal-repro
	./legato-fade-repro
	./bargraph-current-repro

voice-steal-repro: voice-steal-repro.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@

legato-fade-repro: legato-fade-repro.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@

bargraph-current-repro: bargraph-current-repro.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@

# mcu-poly-dsp.h against poly-dsp.h (UI paths, MIDI, assign modes, bit identical
# audio), voice stealing, slices, limits, soundfiles, voices made under -mem
mcu-poly: mcu-poly-test
	./mcu-poly-test

mcupolyvoice.h: mcu-poly-voice.dsp
	$(FAUST) -cn mcupolyvoice -i $< -o $@

mcupolyeffect.h: mcu-poly-voice.dsp
	$(FAUST) -cn mcupolyeffect -pn effect -i $< -o $@

mcupolyvoicemem.h: mcu-poly-voice.dsp
	$(FAUST) -mem -cn mcupolyvoicemem -i $< -o $@

mcu-poly-test: mcu-poly-test.cpp mcupolyvoice.h mcupolyeffect.h mcupolyvoicemem.h ../../architecture/faust/dsp/mcu-poly-dsp.h
	$(CXX) $(CPPFLAGS) -I. $(CXXFLAGS) $< -o $@

# the same without RTTI, as on a Teensy (-fno-rtti; MIDI registered with
# setMidiHandler()); DAISY_NO_RTTI only for poly-dsp.h, the reference, which
# needs it to build without RTTI
mcu-poly-nortti: mcu-poly-test-nortti
	./mcu-poly-test-nortti

mcu-poly-test-nortti: mcu-poly-test.cpp mcupolyvoice.h mcupolyeffect.h mcupolyvoicemem.h ../../architecture/faust/dsp/mcu-poly-dsp.h
	$(CXX) $(CPPFLAGS) -I. $(CXXFLAGS) -fno-rtti -DDAISY_NO_RTTI $< -o $@

clean:
	rm -f voice-steal-repro legato-fade-repro bargraph-current-repro mcu-poly-test mcu-poly-test-nortti mcupolyvoice.h mcupolyeffect.h mcupolyvoicemem.h
