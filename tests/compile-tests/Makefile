# Makefile to exercise Faust compiler output across many backends.
# Default target builds C/C++, Cmajor, JSFX, Julia, etc. into a directory
# named after the Faust version (e.g., 2.82.5/...). Additional targets
# cover JSON generation/compare, platform-specific runs, and tracer demos.
system := $(shell uname -s)
system := $(shell echo $(system) | grep MINGW > /dev/null && echo MINGW || echo $(system))
ifeq ($(system), MINGW)
 FAUST ?= ../../build/bin/faust.exe
else
 FAUST ?= ../../build/bin/faust
endif
MAKE ?= make

# Source locations and includes shared across targets
SAMPLESROOT := ../..
REGRESSION := ..
FAUSTLIBS1 ?= ../../libraries
FAUSTLIBS2 ?= ../../libraries/old
FAUSTINC  ?= ../../architecture/faust

# Lists of DSPs used by the JSON targets (examples + codegen-tests, minus exclusions)
DSP_EXAMPLES := $(shell find $(SAMPLESROOT)/examples -name "*.dsp" | grep -v "TODO\|old\|faust-stk\|SAM")
DSP_REGRESSION := $(shell find $(REGRESSION)/codegen-tests -name "*.dsp" | grep -v BUG)

# Capture current Faust version to segregate outputs
version := $(shell $(FAUST) --version | grep Version | sed -e 's/^..*Version //')

cxxfiles  = $(shell find $(version) -name "*.cpp")
cfiles    = $(shell find $(version) -name "*.c")
cppobj := $(cxxfiles:%.cpp=%.o) 
cobj :=  $(cfiles:%.c=%.o)

CXX ?= g++
GCC ?= gcc

CPP_OPTIONS := -std=c++14 -Wno-unused-command-line-argument -I$(FAUSTINC)

C_OPTIONS := -Wno-unused-command-line-argument -I$(FAUSTINC)

# Default: run all backends plus native C/C++ compilation checks
all:
	$(MAKE) -f Make.lang outdir=cpp lang=cpp ext=cpp FAUSTOPTIONS=" -a ./min.cpp"
	$(MAKE) -f Make.lang outdir=ocpp lang=ocpp ext=cpp FAUSTOPTIONS=" -a ./min.cpp"
	$(MAKE) -f Make.lang outdir=c lang=c ext=c FAUSTOPTIONS=" -a ./min.c"
	$(MAKE) -f Make.lang outdir=cmajor lang=cmajor ext=cmajor FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=codebox lang=codebox ext=codebox FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=dlang lang=dlang ext=dlang FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=fir lang=fir ext=fir FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=julia lang=julia ext=julia FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=jsfx lang=jsfx ext=jsfx FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=interp lang=interp ext=fbc FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=jax lang=jax ext=jax FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=llvm lang=llvm ext=bc  FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=rust lang=rust ext=rs FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=wasm lang=wasm ext=wasm FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=wast lang=wast ext=wast FAUSTOPTIONS=""
	$(MAKE) gcc1
	$(MAKE) gcc2
	
json:  # Generate JSON descriptors only (-json/-O)
	$(call GENJSON,$(version)/json)
	
json-compare:
	@olddir=$(version)/json; newdir=$(version)/json-new; \
	if [ ! -d $$olddir ]; then \
		echo "Reference JSON directory '$$olddir' not found; run 'make json' first."; \
		exit 1; \
	fi; \
	rm -rf $$newdir; \
	$(call GENJSON,$$newdir); \
	diff -ru $$olddir $$newdir
	
check: 
	export FAUST_DEBUG=FIR_VAR_CHECKER; \
	$(MAKE) -f Make.lang outdir=cpp lang=cpp ext=cpp FAUSTOPTIONS=" -a ./min.cpp"
	
release:
	$(MAKE) c
	$(MAKE) os
	$(MAKE) gcc1
	$(MAKE) gcc2
	$(MAKE) interp
	$(MAKE) trace
	
web:
	$(MAKE) -f Make.lang outdir=wasm lang=wasm ext=wasm FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=wast lang=wast ext=wast FAUSTOPTIONS=""
	
os:
	$(MAKE) -f Make.lang outdir=cppos0 lang=cpp ext=cpp FAUSTOPTIONS=" -os -a ./min.cpp"
	$(MAKE) -f Make.lang outdir=cos0 lang=c ext=c FAUSTOPTIONS="-lang c -os -a ./min.c"

c:  # Only C and C++ backends with minimal arch files
	$(MAKE) -f Make.lang outdir=cpp lang=cpp ext=cpp FAUSTOPTIONS=" -a ./min.cpp"
	$(MAKE) -f Make.lang outdir=ocpp lang=ocpp ext=o.cpp FAUSTOPTIONS=" -a ./min.cpp"
	$(MAKE) -f Make.lang outdir=c lang=c ext=c FAUSTOPTIONS=" -a ./min.c"

llvm:  # LLVM backend (scalar + vector)
	$(MAKE) -f Make.lang outdir=llvm lang=llvm ext=llvm FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=llvm/vec lang=llvm ext=llvm FAUSTOPTIONS=" -vec -lv 1"

julia:  # Julia backend
	$(MAKE) -f Make.lang outdir=julia lang=julia ext=julia FAUSTOPTIONS=""
	
rust:   # Rust backend
	$(MAKE) -f Make.lang outdir=rust lang=rust ext=rust FAUSTOPTIONS=""
	
trace:  # Interpreter tracer demo
	$(MAKE) -f Make.lang interp-tracer 
	
jtrace: # Julia tracer demo
	$(MAKE) -f Make.lang julia-tracer 

cmajor: # faust2cmajor wrapper
	$(MAKE) -f Make.lang cmajor 

rnbo:   # faust2rnbo wrapper
	$(MAKE) -f Make.lang rnbo 
	
doc:    # Markdown/SVG documentation generation
	$(MAKE) -f Make.lang doc 

me:     # C++ backend with -me option
	$(MAKE) -f Make.lang outdir=cpp lang=cpp ext=cpp FAUSTOPTIONS=" -me -a ./min.cpp"

#########################################################################
# interp lang has a special status since the corresponding backend may not
# be available due to gcc specific extensions
interp:
	$(MAKE) -f Make.lang outdir=interp lang=interp ext=fbc FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=interp/vec lang=interp ext=fbc FAUSTOPTIONS=" -vec -lv 1"

help:
	@echo "-------- FAUST compilation tests --------"
	@echo "Available targets are:"
	@echo " 'all' (default): compiles all the dsp found in the examples and regression"
	@echo "              folders using all backends (apart the interp backend)"
	@echo "              C and C++ output are also compile using $(GCC) and $(CXX)"
	@echo "              Output is located in a folder named using faust version ($(version))"
	@echo " 'release'  to test C++, C backend, 'os', 'interp' and 'trace' specific targets"
	@echo "Specific targets:"
	@echo " 'gcc1'       : compiles the C and C++ output of the 'cpp' and 'ocpp' backends"
	@echo " 'gcc2'       : compiles the C and C++ output of the 'c' backend"
	@echo " 'c'          : compiles using the 'cpp', 'ocpp' and 'c' backends"
	@echo " 'os'         : compiles using the 'cpp' and 'c' backends in -osX mode"
	@echo " 'llvm'       : compiles using the LLVM backend"
	@echo " 'interp'     : compiles using the interpreter backend"
	@echo " 'julia'      : compiles using the Julia backend"
	@echo " 'rust'       : compiles using the Rust backend"
	@echo " 'web'        : compiles using the wast/wasm backends"
	@echo " 'cmajor'     : compiles using faust2cmajor"
	@echo " 'rnbo'       : compiles using faust2rnbo"
	@echo " 'trace'      : compiles using the interp-tracer application"
	@echo " 'jtrace'     : compiles using Julia minimal-control architecture"
	@echo " 'json'       : generates JSON descriptions with '-json' and keeps them"
	@echo " 'json-compare': regenerates JSON (-json) and diffs against existing $(version)/json"
	@echo " 'me'         : compiles using the C++ backend with -me option"
	@echo " 'check'      : compiles using the C++ backend and FAUST_DEBUG=FIR_VAR_CHECKER"
	@echo " 'doc'        : test the -mdoc, -svg options"

	@echo " 'clean'      : to remove the folder named using faust version"
	@echo "Using a specific version of Faust libraries:"
	@echo " 'make FAUSTLIBS=/path/to/libraries'"

gcc1: $(cppobj)

gcc2: $(cobj)

clean:
	rm -rf $(version)

# Generate JSON files only (no .o/.cpp) into a versioned directory using -json/-O.
#
# $(1): output root directory (e.g., $(version)/json or $(version)/json-new)
define GENJSON
@outdir=$(1); \
mkdir -p $$outdir; \
for file in $(DSP_EXAMPLES) $(DSP_REGRESSION); do \
	case $$file in \
	  $(SAMPLESROOT)/*) rel=$${file#$(SAMPLESROOT)/};; \
	  $(REGRESSION)/*) rel=$${file#$(REGRESSION)/};; \
	esac; \
	dest=$$outdir/$$(dirname -- "$$rel"); \
	mkdir -p "$$dest"; \
	$(FAUST) -lang cpp -I $(FAUSTLIBS1) -I $(FAUSTLIBS2) -json "$$file" -O "$$dest" > /dev/null; \
done
endef

#########################################################################
# rules for c/c++ compilation
%.o: %.cpp
	$(eval tmp1 := $(patsubst $(version)/cpp/%, $(SAMPLESROOT)/%, $(<D)))
	$(eval tmp := $(patsubst $(version)/ocpp/%, $(REGRESSION)/%, $(tmp1)))
	$(CXX) -c $(CPP_OPTIONS) -I$(tmp) $< -o $@ 

%.o: %.c
	$(eval tmp := $(patsubst $(version)/c/%, $(SAMPLESROOT)/%, $(<D)))
	$(GCC) -c $(C_OPTIONS) -I$(tmp) $< -o $@ 
