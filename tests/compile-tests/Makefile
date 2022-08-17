#
# Makefile for testing the Faust compiler output
#
system := $(shell uname -s)
system := $(shell echo $(system) | grep MINGW > /dev/null && echo MINGW || echo $(system))
ifeq ($(system), MINGW)
 FAUST ?= ../../build/bin/faust.exe
else
 FAUST ?= ../../build/bin/faust
endif
MAKE ?= make

SAMPLESROOT := ../..
REGRESSION := ..
FAUSTINC  ?= ../../architecture/faust

version := $(shell $(FAUST) --version | grep Version | sed -e 's/^..*Version //')

cxxfiles  = $(shell find $(version) -name "*.cpp")
cfiles    = $(shell find $(version) -name "*.c")
gccobj := $(cxxfiles:%.cpp=%.o) $(cfiles:%.c=%.o)

CXX ?= g++
GCC ?= gcc

OPTIONS := -Wno-unused-command-line-argument -I$(FAUSTINC)

all:
	$(MAKE) -f Make.lang outdir=cpp lang=cpp ext=cpp 	FAUSTOPTIONS=" -a ./min.cpp"
	$(MAKE) -f Make.lang outdir=ocpp lang=ocpp ext=o.cpp FAUSTOPTIONS=" -a ./min.cpp"
	$(MAKE) -f Make.lang outdir=c 	lang=c   ext=c 		FAUSTOPTIONS=" -a ./min.c"
	$(MAKE) -f Make.lang outdir=wasm lang=wasm ext=wasm FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=wast lang=wast ext=wast FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=llvm lang=llvm ext=llvm  FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=fir lang=fir ext=fir FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=julia lang=julia ext=julia FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=rust lang=rust ext=rust FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=llvm lang=llvm ext=llvm FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=soul lang=soul ext=soul FAUSTOPTIONS=""
	$(MAKE) gcc

web:
	$(MAKE) -f Make.lang outdir=wasm lang=wasm ext=wasm FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=wast lang=wast ext=wast FAUSTOPTIONS=""
	
c:
	$(MAKE) -f Make.lang outdir=cpp lang=cpp ext=cpp FAUSTOPTIONS=" -a ./min.cpp"
	$(MAKE) -f Make.lang outdir=ocpp lang=ocpp ext=o.cpp FAUSTOPTIONS=" -a ./min.cpp"
	$(MAKE) -f Make.lang outdir=c lang=c ext=c FAUSTOPTIONS=" -a ./min.c"

llvm:
	$(MAKE) -f Make.lang outdir=llvm lang=llvm ext=llvm FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=llvm/vec lang=llvm ext=llvm FAUSTOPTIONS=" -vec -lv 1"

julia:
	$(MAKE) -f Make.lang outdir=julia lang=julia ext=julia FAUSTOPTIONS=""
	
rust:
	$(MAKE) -f Make.lang outdir=rust lang=rust ext=rust FAUSTOPTIONS=""
	
soul:
	$(MAKE) -f Make.lang outdir=soul lang=soul ext=soul FAUSTOPTIONS=""

trace:
	$(MAKE) -f Make.lang interp-tracer 
	
jtrace:
	$(MAKE) -f Make.lang julia-tracer 

me:
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
	@echo "Specific targets:"
	@echo " 'gcc'        : compiles the C and C++ output of the 'cpp', 'ocpp' and 'c' backends"
	@echo " 'soul'       : compiles using the SOUL backend"
	@echo " 'llvm'       : compiles using the LLVM backend"
	@echo " 'interp'     : compiles using the interpreter backend"
	@echo " 'julia'       : compiles using the Julia backend"
	@echo " 'rust'       : compiles using the Rust backend"
	@echo " 'web'        : compiles using the wast/wasm backends"
	@echo " 'trace'      : compiles using the interp-tracer application"
	@echo " 'jtrace'     : compiles using Julia minimal-control architecture"
	@echo " 'me'         : compiles using the C++ backend with -me option"
	@echo " 'clean'      : to remove the folder named using faust version"
	@echo "Using a specific version of Faust libraries:"
	@echo " 'make FAUSTLIBS=/path/to/libraries'"
 	
gcc: $(gccobj)

clean:
	rm -rf $(version)

#########################################################################
# rules for c/c++ compilation
%.o: %.cpp
	$(eval tmp1 := $(patsubst $(version)/cpp/%, $(SAMPLESROOT)/%, $(<D)))	
	$(eval tmp := $(patsubst $(version)/ocpp/%, $(REGRESSION)/%, $(tmp1)))	
	$(CXX) -c $(OPTIONS) -I$(tmp) $< -o $@ 

%.o: %.c
	$(eval tmp := $(patsubst $(version)/c/%, $(SAMPLESROOT)/%, $(<D)))	
	$(GCC) -c $(OPTIONS) -I$(tmp) $< -o $@ 
