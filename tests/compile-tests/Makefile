#
# Makefile for testing the faust compiler output
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
	$(MAKE) -f Make.lang outdir=js 	lang=js  ext=js 	FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=ajs lang=ajs ext=ajs 	FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=wasm lang=wast/wasm ext=wasm FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=java lang=java ext=java FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=fir lang=fir ext=fir FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=rust lang=rust ext=rust FAUSTOPTIONS=""
	$(MAKE) -f Make.lang outdir=llvm lang=llvm ext=llvm FAUSTOPTIONS=""
	$(MAKE) gcc

#########################################################################
# interp lang has a special status since the corresponding backend may not
# be available due to gcc specific extensions
interp:
	$(MAKE) -f Make.lang outdir=interp lang=interp ext=itp FAUSTOPTIONS=""


help:
	@echo "-------- FAUST compilation tests --------"
	@echo "Available targets are:"
	@echo " 'all' (default): compiles all the dsp found in the examples and regression"
	@echo "              folders using all backends (apart the interp backend)"
	@echo "              C and C++ output are also compile using $(GCC) and $(CXX)"
	@echo "              Output is located in a folder named using faust version ($(version))"
	@echo "Specific targets:"
	@echo " 'gcc'        : compiles the C and C++ output of the 'cpp', 'ocpp' and 'c' backends"
	@echo " 'interp'     : compiles using the interpreter backend"
	
gcc: $(gccobj)


#########################################################################
# rules for c/c++ compilation
%.o: %.cpp
	$(eval tmp1 := $(patsubst $(version)/cpp/%, $(SAMPLESROOT)/%, $(<D)))	
	$(eval tmp := $(patsubst $(version)/ocpp/%, $(REGRESSION)/%, $(tmp1)))	
	$(CXX) -c $(OPTIONS) -I$(tmp) $< -o $@ 

%.o: %.c
	$(eval tmp := $(patsubst $(version)/c/%, $(SAMPLESROOT)/%, $(<D)))	
	$(GCC) -c $(OPTIONS) -I$(tmp) $< -o $@ 
