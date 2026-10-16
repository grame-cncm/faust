# Short delay line tests (see README.md).

CXX ?= c++
ROOT := ../..
FAUST ?= $(ROOT)/build/bin/faust
CXXFLAGS := -std=c++17 -O1 -g -fsanitize=address,undefined,float-cast-overflow -fno-sanitize-recover=all \
            -fno-omit-frame-pointer -ffp-contract=off -I$(ROOT)/architecture

# name : dsp : Faust options (~ is a space) : C++ options (~ is a space)
# The fma cases need -O2: g++ does not contract at -O1.
CONFIGS := zone-double:zone:-double:-DCONTROLS_AT_MAX \
           fma-single:fma:-single:-DCONTROLS_AT_MAX~-O2~-ffp-contract=fast \
           nan-control-double:nan_control:-double:-DCONTROLS_AT_MIN \
           nan-input-single:nan_input:-single:-DNAN_INPUT \
           vec-fma4-single:fma4:-single~-vec:-DCONTROLS_AT_MAX~-O2~-ffp-contract=fast \
           vec-nan-input-single:nan_input:-single~-vec:-DNAN_INPUT \
           veclv1-fma4-single:fma4:-single~-vec~-lv~1:-DCONTROLS_AT_MAX~-O2~-ffp-contract=fast \
           ocpp-zone-double:zone:-double~-lang~ocpp:-DCONTROLS_AT_MAX \
           ocpp-fma4-single:fma4:-single~-lang~ocpp:-DCONTROLS_AT_MAX~-O2~-ffp-contract=fast \
           ocpp-nan-input-single:nan_input:-single~-lang~ocpp:-DNAN_INPUT

field = $(subst ~, ,$(word $(2),$(subst :, ,$(1))))
NAMES := $(foreach c,$(CONFIGS),$(call field,$(c),1))

.PHONY: check clean
check: $(NAMES:%=build/%.run)
	@echo "All delay tests passed"

define CONFIG
build/$(call field,$(1),1).cpp: $(call field,$(1),2).dsp
	@mkdir -p build
	$(FAUST) $(call field,$(1),3) $(call field,$(1),2).dsp -o $$@

build/$(call field,$(1),1): delay-edge.cpp build/$(call field,$(1),1).cpp
	$(CXX) $(CXXFLAGS) $(call field,$(1),4) -DGENERATED='"build/$(call field,$(1),1).cpp"' delay-edge.cpp -o $$@

build/$(call field,$(1),1).run: build/$(call field,$(1),1)
	ASAN_OPTIONS=detect_leaks=0 ./build/$(call field,$(1),1)
endef

$(foreach c,$(CONFIGS),$(eval $(call CONFIG,$(c))))

clean:
	rm -rf build
