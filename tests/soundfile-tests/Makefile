# Soundfile channel wrap tests: a soundfile read with more channels than it actually has reads
# channel 'chan % fChannels'. Each configuration compiles wrap.dsp with the given Faust options,
# builds it with soundfile-wrap.cpp (SoundUI + LibsndfileReader) under AddressSanitizer and runs it.
# Needs libsndfile (found with pkg-config).

CXX ?= c++
ROOT := ../..
FAUST ?= $(ROOT)/build/bin/faust
SNDFILE := $(shell pkg-config --cflags --libs sndfile)
CXXFLAGS := -std=c++17 -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer -I$(ROOT)/architecture

# name : Faust options : C++ options
CONFIGS := single:-single:-DFAUSTFLOAT=float \
           double:-double:-DFAUSTFLOAT=double~-DSOUND_DOUBLE \
           single-ec:-single~-ec:-DFAUSTFLOAT=float~-DEXT_CONTROL \
           double-vec:-double~-vec:-DFAUSTFLOAT=double~-DSOUND_DOUBLE \
           double-vec-lv1:-double~-vec~-vs~8~-lv~1:-DFAUSTFLOAT=double~-DSOUND_DOUBLE

field = $(subst ~, ,$(word $(2),$(subst :, ,$(1))))
NAMES := $(foreach c,$(CONFIGS),$(call field,$(c),1))

.PHONY: check clean
check: $(NAMES:%=build/%.run)
	@echo "All soundfile wrap tests passed"

define CONFIG
build/$(call field,$(1),1).cpp: wrap.dsp
	@mkdir -p build
	$(FAUST) $(call field,$(1),2) wrap.dsp -o $$@

build/$(call field,$(1),1): soundfile-wrap.cpp build/$(call field,$(1),1).cpp
	$(CXX) $(CXXFLAGS) $(call field,$(1),3) -DGENERATED='"build/$(call field,$(1),1).cpp"' soundfile-wrap.cpp $(SNDFILE) -o $$@

build/$(call field,$(1),1).run: build/$(call field,$(1),1)
	./build/$(call field,$(1),1)
endef

$(foreach c,$(CONFIGS),$(eval $(call CONFIG,$(c))))

clean:
	rm -rf build wrap3.wav
