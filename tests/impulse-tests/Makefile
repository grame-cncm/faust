#
# Makefile for testing the Faust compiler output
#

system := $(shell uname -s)
system := $(shell echo $(system) | grep MINGW > /dev/null && echo MINGW || echo $(system))
ifeq ($(system), MINGW)
 FAUST ?= ../../build/bin/faust.exe
 COMPARE := ./filesCompare.exe
 WINSOCK = -lws2_32
else
 FAUST ?= ../../build/bin/faust
 COMPARE := ./filesCompare
 WINSOCK = 
endif

MAKE ?= make
GCCOPTIONS := -O3 -I../../architecture -Iarchs -pthread -std=c++11
outdir ?= float
arch ?= ./archs/impulsearch.cpp
FAUSTOPTIONS := -lang cpp -double -i -a $(arch)

.PHONY: test reference

dspfiles := $(wildcard dsp/*.dsp)
mutefiles = $(dspfiles:dsp/%.dsp=ir/mute/%.ir)

TOOLSOPTIONS := -std=c++11 -O3 -I../../architecture
LIB    ?= ../../build/lib/libfaust.a
SRCDIR := tools

all:
	$(MAKE) cpp
	$(MAKE) c
	$(MAKE) mute
#   $(MAKE) asmjs
	$(MAKE) wasm
	$(MAKE) wast
	$(MAKE) llvm
	$(MAKE) interp

help:
	@echo "-------- FAUST impulse response tests --------"
	@echo "Available targets are:"
	@echo " 'all' (default): call all the targets below"
	@echo
	@echo " 'cpp'    : check float and double outputs with the cpp backend in scalar, vec, openmp and sched modes"
	@echo " 'c'      : check float and double outputs with the c backend in scalar, vec, openmp and sched modes"
	@echo " 'mute'   : check double output with mute"
	@echo " 'asmjs'  : check double output with asmjs backend and various options"
	@echo " 'wasm'   : check double output with wasm backend and various options"
	@echo " 'wast'   : check double output with wast backend and various options"
	@echo " 'llvm'   : check double output with llvm backend and various options"
	@echo " 'interp' : check double output with interpreter backend and various options"
	@echo "Warning: you must have at least 10G available on your hard disk to run all the tests"
	@echo
	@echo "Specific targets:"
	@echo " 'travis'    : tests subset for travis"
	@echo " 'web'       : call the asmjs and wast/wasm targets"
	@echo " 'reference' : builds the reference files"
	@echo " 'tools'     : builds binary tools used by the tests"
	@echo
	@echo "Experimental targets:"
	@echo " 'quad'    : check quad output with the cpp and c backends in scalar, vec, openmp and sched modes"
	@echo
	@echo "NOTE: when running make with option '-j', you should also use '-i' (see the README.md file)"
	@echo

#########################################################################
# automatic travis test
travis:
	$(MAKE) -f Make.gcc outdir=cpp/double       lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-double"
	$(MAKE) -f Make.gcc outdir=cpp/double/vec   lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-double -vec"
	$(MAKE) -f Make.gcc outdir=cpp/double/omp   lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-double -omp"


#########################################################################
# c and c++ backends
cpp:
	$(MAKE) -f Make.gcc outdir=cpp/double           lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-double"
	$(MAKE) -f Make.gcc outdir=cpp/double/vec/lv0   lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-double -vec -lv 0"
	$(MAKE) -f Make.gcc outdir=cpp/double/vec/lv0/vs16   lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-double -vec -lv 0 -vs 16"
	$(MAKE) -f Make.gcc outdir=cpp/double/vec/lv1   lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-double -vec -lv 1"
	$(MAKE) -f Make.gcc outdir=cpp/double/vec/lv1/vs16   lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-double -vec -lv 1 -vs 16"
	$(MAKE) -f Make.gcc outdir=cpp/double/sched     lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-double -sch"
	$(MAKE) -f Make.gcc outdir=cpp/double/omp       lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-double -omp"
	$(MAKE) -f Make.gcc outdir=cpp/float            lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-single"
	$(MAKE) -f Make.gcc outdir=cpp/float/vec        lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-single -vec"
	$(MAKE) -f Make.gcc outdir=cpp/float/sched      lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-single -sch"
	$(MAKE) -f Make.gcc outdir=cpp/float/omp        lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-single -omp"

c:
	$(MAKE) -f Make.gcc outdir=c/double             lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-double"
	$(MAKE) -f Make.gcc outdir=c/double/vec/lv0     lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-double -vec -lv 0"
	$(MAKE) -f Make.gcc outdir=c/double/vec/lv0/vs16     lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-double -vec -lv 0 -vs 16"
	$(MAKE) -f Make.gcc outdir=c/double/vec/lv1     lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-double -vec -lv 1"
	$(MAKE) -f Make.gcc outdir=c/double/vec/lv1/vs16     lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-double -vec -lv 1 -vs 16"
	$(MAKE) -f Make.gcc outdir=c/double/sched       lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-double -sch"
	$(MAKE) -f Make.gcc outdir=c/double/omp         lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-double -omp"
	$(MAKE) -f Make.gcc outdir=c/float              lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-single"
	$(MAKE) -f Make.gcc outdir=c/float/vec          lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-single -vec"
	$(MAKE) -f Make.gcc outdir=c/float/sched        lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-single -sch"
	$(MAKE) -f Make.gcc outdir=c/float/omp          lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-single -omp"

quad:
	$(MAKE) -f Make.gcc outdir=cpp/quad         lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-quad"
	$(MAKE) -f Make.gcc outdir=cpp/quad/vec     lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-quad -vec"
	$(MAKE) -f Make.gcc outdir=cpp/quad/sched   lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-quad -sch"
	$(MAKE) -f Make.gcc outdir=cpp/quad/omp     lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-quad -omp"
	$(MAKE) -f Make.gcc outdir=c/quad           lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-quad"
	$(MAKE) -f Make.gcc outdir=c/quad/vec       lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-quad -vec"
	$(MAKE) -f Make.gcc outdir=c/quad/sched     lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-quad -sch"
	$(MAKE) -f Make.gcc outdir=c/quad/omp       lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-quad -omp"

mute: ir/mute  $(mutefiles)

#########################################################################
# web backends
web:
	$(MAKE) asmjs
	$(MAKE) wasm
	$(MAKE) wast

asmjs:
	$(MAKE) -f Make.web asmjs
	$(MAKE) -f Make.web asmjs outdir=asmjs/inpl FAUSTOPTIONS=-inpl

wasm:
	$(MAKE) -f Make.web wasm
	$(MAKE) -f Make.web wasm wasmdir=wasm/ftz1 FAUSTOPTIONS="-ftz 1"

wast:
	$(MAKE) -f Make.web wast
	$(MAKE) -f Make.web wast wastdir=wast/ftz1 FAUSTOPTIONS="-ftz 1"

#########################################################################
# llvm backend
llvm:
	$(MAKE) -f Make.llvm
	$(MAKE) -f Make.llvm outdir=llvm/inpl FAUSTOPTIONS=-inpl
	$(MAKE) -f Make.llvm outdir=llvm/vec/lv0 FAUSTOPTIONS="-vec -lv 0"
	$(MAKE) -f Make.llvm outdir=llvm/vec/lv0/vs16 FAUSTOPTIONS="-vec -lv 0 -vs 16"
	$(MAKE) -f Make.llvm outdir=llvm/vec/lv1 FAUSTOPTIONS="-vec -lv 1"
	$(MAKE) -f Make.llvm outdir=llvm/vec/lv1/vs16 FAUSTOPTIONS="-vec -lv 1 -vs 16"
	$(MAKE) -f Make.llvm outdir=llvm/vec/vs200 FAUSTOPTIONS="-vec -vs 200" 
	$(MAKE) -f Make.llvm outdir=llvm/vec/g FAUSTOPTIONS="-vec -lv 1 -g"
	$(MAKE) -f Make.llvm outdir=llvm/vec/gfun FAUSTOPTIONS="-vec -lv 1 -g -fun" 
#	$(MAKE) -f Make.llvm outdir=llvm/sch FAUSTOPTIONS="-sch" 

#########################################################################
# interp backend
interp:
	$(MAKE) -f Make.interp
	#$(MAKE) -f Make.interp outdir=interp/lv0 FAUSTOPTIONS="-vec -lv 0"
	#$(MAKE) -f Make.interp outdir=interp/lv0/vs16 FAUSTOPTIONS="-vec -lv 0 -vs 16"
	$(MAKE) -f Make.interp outdir=interp/vec/lv1 FAUSTOPTIONS="-vec -lv 1"
	$(MAKE) -f Make.interp outdir=interp/vec/lv1/vs16 FAUSTOPTIONS="-vec -lv 1 -vs 16"
	#$(MAKE) -f Make.interp outdir=interp/vec/vs200 FAUSTOPTIONS="-vec -vs 200" 
	$(MAKE) -f Make.interp outdir=interp/vec/g FAUSTOPTIONS="-vec -lv 1 -g"
	$(MAKE) -f Make.interp outdir=interp/inpl FAUSTOPTIONS=-inpl
	$(MAKE) -f Make.interp outdir=interp/ftz FAUSTOPTIONS="-ftz 0"
	

#########################################################################
# output directories
ir/mute:
	mkdir -p ir/mute

#########################################################################
# building reference files
reference:
	$(MAKE) -f Make.ref

tools: filesCompare impulsellvm impulseinterp

clean: 
	rm -f filesCompare impulsellvm impulseinterp

#########################################################################
# tools
filesCompare: $(SRCDIR)/filesCompare.cpp
	$(CXX) $(TOOLSOPTIONS) $(SRCDIR)/filesCompare.cpp -o filesCompare

impulseinterp: $(SRCDIR)/impulseinterp.cpp ./archs/controlTools.h $(LIB)
	$(CXX) $(TOOLSOPTIONS) -Iarchs $(SRCDIR)/impulseinterp.cpp $(LIB) `llvm-config --ldflags --libs all --system-libs` -o impulseinterp

impulsellvm: $(SRCDIR)/impulsellvm.cpp ./archs/controlTools.h $(LIB)
	$(CXX) $(TOOLSOPTIONS) -Iarchs $(SRCDIR)/impulsellvm.cpp $(LIB) `llvm-config --ldflags --libs all --system-libs` $(WINSOCK) -o impulsellvm

#########################################################################
# rules for mute tests
ir/mute/%.ir: ir/mute/% reference/%.ir
	$< -n 30000 > $@
	$(COMPARE)  $@ reference/$(notdir $@)
ir/mute/%.cpp : dsp/%-mute.dsp
	$(FAUST) $(FAUSTOPTIONS) $<  -o $@
ir/mute/% : ir/mute/%.cpp
	$(CXX) $(GCCOPTIONS) $<  -o $@
dsp/%-mute.dsp : dsp/%.dsp
	echo "process = P : par(i, outputs(P), (_,(1-checkbox(\"fakedisable %2i\")) : *) ) with { P = component(\"$<\"); };" > $@
