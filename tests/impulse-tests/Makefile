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

GCCOPTIONS := -O3 -I../../architectures -Iarchs -pthread -std=c++11
outdir ?= float
lang ?= cpp
arch ?= ./archs/impulsearch.cpp
FAUSTOPTIONS := -lang $(lang) -double -i -a $(arch)
FAUSTASMJSOPTIONS ?= 

.PHONY: test reference

dspfiles := $(wildcard dsp/*.dsp)

listfiles = $(dspfiles:dsp/%.dsp=ir/$1/%.ir) $(dspfiles:dsp/%.dsp=ir/$1/vec/%.ir) $(dspfiles:dsp/%.dsp=ir/$1/sched/%.ir) $(dspfiles:dsp/%.dsp=ir/$1/omp/%.ir) 

mutefiles = $(dspfiles:dsp/%.dsp=ir/mute/%.ir) 

listintermediate = $(dspfiles:dsp/%.dsp=ir/$1/%) $(dspfiles:dsp/%.dsp=ir/$1/%.cpp) $(dspfiles:dsp/%.dsp=ir/$1/vec/%) $(dspfiles:dsp/%.dsp=ir/$1/vec/%.cpp) $(dspfiles:dsp/%.dsp=ir/$1/sched/%) $(dspfiles:dsp/%.dsp=ir/$1/sched/%.cpp) $(dspfiles:dsp/%.dsp=ir/$1/omp/%) $(dspfiles:dsp/%.dsp=ir/$1/omp/%.cpp)

.INTERMEDIATE: $(call listintermediate, $(outdir))


#.DELETE_ON_ERROR: $(cppfiles)

TOOLSOPTIONS := -std=c++11 -O3 -I../../architectures
LIB    ?= ../../build/lib/libfaust.a
SRCDIR := tools


all:
	make float
	make double
	make quad
	make mute


test:
#	$(file > faustoptions.txt, "some text")
	@echo $(call listwebfiles,$(asmjsdir))

help:
	@echo "-------- FAUST impulse response tests --------"
	@echo "Available targets are:"
	@echo " 'all' (default): call the float, double, quad and mute targets"
	@echo " 'float'    : check float output in scalar, vec, openmp and sched modes"
	@echo " 'double'   : check double output in scalar, vec, openmp and sched modes"
	@echo " 'quad'     : check quad output in scalar, vec, openmp and sched modes"
	@echo " 'mute'     : check double output with mute"
	@echo
	@echo " 'web'      : call the asmjs and wasm targets"
	@echo " 'asmjs'    : check double output with asmjs backend and various options"
	@echo " 'wasm'     : check double output with wasm backend and various options"
	@echo
	@echo " 'llvm'     : check double output with llvm backend and various options"
	@echo
	@echo "Specific targets:"
	@echo " 'reference' : builds the reference files"
	@echo " 'tools'     : builds binary tools used by the tests"



#########################################################################
# checking float, double and quad outputs
float:  
	make _float  outdir=float
_float: FAUSTOPTIONS = -lang $(lang) -single -i -a $(arch)
_float : ir/float/vec ir/float/sched ir/float/omp $(call listfiles,float)

double: 
	make _double outdir=double
_double: FAUSTOPTIONS = -lang $(lang) -double -i -a $(arch)
_double: ir/double/vec ir/double/sched ir/double/omp $(call listfiles,double)

quad:  
	make _quad outdir=quad
_quad: FAUSTOPTIONS = -lang $(lang) -quad -i -a $(arch)
_quad: ir/quad/vec ir/quad/sched ir/quad/omp $(call listfiles,quad)

mute: ir/mute  $(mutefiles)

#########################################################################
# web backends
web:
	make asmjs
	make wasm
	
asmjs:  
	make -f Make.web asmjs
	make -f Make.web asmjs outdir=asmjs_inpl FAUSTOPTIONS=-inpl

wasm:
	make -f Make.web wasm
	make -f Make.web wasm wasmdir=wasm_ftz1 FAUSTOPTIONS="-ftz 1"

#########################################################################
# llvm backends
llvm:  
	make -f Make.llvm
	make -f Make.llvm outdir=llvm_inpl FAUSTOPTIONS=-inpl
	

#########################################################################
# output directories
ir/$(outdir)/vec:
	mkdir -p ir/$(outdir)/vec
ir/$(outdir)/sched:
	mkdir -p ir/$(outdir)/sched
ir/$(outdir)/omp:
	mkdir -p ir/$(outdir)/omp
ir/mute:
	mkdir -p ir/mute

#########################################################################
# building reference files
reference: 
	make -f Make.ref

tools: filesCompare impulseinterp impulsellvm



#########################################################################
# tools
filesCompare: $(SRCDIR)/filesCompare.cpp
	$(CXX) $(TOOLSOPTIONS) $(SRCDIR)/filesCompare.cpp -o filesCompare

impulseinterp: $(SRCDIR)/impulseinterp.cpp ../../build/lib/libfaust.a
	$(CXX) $(TOOLSOPTIONS) -Iarchs $(SRCDIR)/impulseinterp.cpp $(LIB) `llvm-config --ldflags --libs all --system-libs` -o impulseinterp

impulsellvm: $(SRCDIR)/impulsellvm.cpp ../../build/lib/libfaust.a
	$(CXX) $(TOOLSOPTIONS) -Iarchs $(SRCDIR)/impulsellvm.cpp $(LIB) `llvm-config --ldflags --libs all --system-libs` -o impulsellvm


#########################################################################
# rules for scalar, vec, openmp and sched tests
ir/$(outdir)/%.ir: ir/$(outdir)/% reference/%.ir
	$< -n 60000 > $@
	filesCompare  $@ reference/$(notdir $@)
ir/$(outdir)/% : ir/$(outdir)/%.cpp
	$(CXX) $(GCCOPTIONS) $<  -o $@
ir/$(outdir)/%.cpp : dsp/%.dsp
	$(FAUST) $(FAUSTOPTIONS) $<  -o $@

ir/$(outdir)/vec/%.ir: ir/$(outdir)/vec/% reference/%.ir
	$< -n 60000 > $@
	filesCompare  $@ reference/$(notdir $@)
ir/$(outdir)/vec/% : ir/$(outdir)/vec/%.cpp
	$(CXX) $(GCCOPTIONS) $<  -o $@
ir/$(outdir)/vec/%.cpp : dsp/%.dsp
	$(FAUST) $(FAUSTOPTIONS) -vec $<  -o $@

ir/$(outdir)/sched/%.ir: ir/$(outdir)/sched/% reference/%.ir
	$< -n 60000 > $@
	filesCompare  $@ reference/$(notdir $@)
ir/$(outdir)/sched/%.cpp : dsp/%.dsp
	$(FAUST) $(FAUSTOPTIONS) -sch $<  -o $@
ir/$(outdir)/sched/% : ir/$(outdir)/sched/%.cpp
	$(CXX) $(GCCOPTIONS) $<  -o $@

ir/$(outdir)/omp/%.ir: ir/$(outdir)/omp/% reference/%.ir
	$< -n 60000 > $@
	filesCompare  $@ reference/$(notdir $@)
ir/$(outdir)/omp/%.cpp : dsp/%.dsp
	$(FAUST) $(FAUSTOPTIONS) -omp $<  -o $@
ir/$(outdir)/omp/% : ir/$(outdir)/omp/%.cpp
	$(CXX) $(GCCOPTIONS) $<  -o $@

#########################################################################
# rules for mute tests
ir/mute/%.ir: ir/mute/% reference/%.ir
	$< -n 60000 > $@
	filesCompare  $@ reference/$(notdir $@)
ir/mute/%.cpp : dsp/%-mute.dsp
	$(FAUST) $(FAUSTOPTIONS) $<  -o $@
ir/mute/% : ir/mute/%.cpp
	$(CXX) $(GCCOPTIONS) $<  -o $@
dsp/%-mute.dsp : dsp/%.dsp
	echo "process = P : par(i, outputs(P), (_,(1-checkbox(\"fakedisable %2i\")) : *) ) with { P = component(\"$<\"); };" > $@
