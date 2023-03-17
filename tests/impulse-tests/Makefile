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
GCCOPTIONS := -O3 -I../../architecture -Iarchs -pthread -std=c++14
outdir ?= float
arch ?= ./archs/impulsearch.cpp
FAUSTOPTIONS := -lang cpp -double -i -a $(arch)

.PHONY: test reference

dspfiles := $(wildcard dsp/*.dsp)
mutefiles = $(dspfiles:dsp/%.dsp=ir/mute/%.ir)

TOOLSOPTIONS := -std=c++14 -O3 -I../../architecture
LIB ?= ../../build/lib/libfaust.a
MACHINE_LIB ?= ../../build/lib/libfaustmachine.a
LLVM_LIB ?= `llvm-config --ldflags --libs all --system-libs`
SRCDIR := tools

all:
	$(MAKE) cpp
	$(MAKE) cpp1
	$(MAKE) ocpp
	$(MAKE) c
	$(MAKE) c1
	$(MAKE) mute
	$(MAKE) wasm
	$(MAKE) wast
	$(MAKE) llvm
	$(MAKE) llvm1
	$(MAKE) interp
	$(MAKE) interp1
	$(MAKE) rust
	$(MAKE) dlang
	$(MAKE) jax
	$(MAKE) julia

help:
	@echo "-------- FAUST impulse response tests --------"
	@echo "Available targets are:"
	@echo " 'all' (default): call all the targets below"
	@echo
	@echo " 'cpp'    : check float and double outputs with the cpp backend in scalar, vec, openmp and sched modes"
	@echo " 'cpp1'   : check double outputs with the cpp backend in scalar one-sample mode (-os0)"
	@echo " 'cpp2'   : check double outputs with the cpp backend in scalar one-sample mode (-os1)"
	@echo " 'cpp3'   : check double outputs with the cpp backend in scalar one-sample mode (-os2)"
	@echo " 'cpp4'   : check double outputs with the cpp backend in scalar one-sample mode (-os3)"
	@echo " 'cpp5'   : check double outputs with the cpp backend in scalar one-sample mode (-os3) and -mem"
	@echo " 'cpp6'   : check double outputs with the cpp backend in scalar and -mem"
	@echo " 'ocpp'   : check double outputs with the ocpp backend in scalar mode"
	@echo " 'c'      : check float and double outputs with the c backend in scalar, vec, openmp and sched modes"
	@echo " 'c1'     : check double outputs with the c backend in scalar one-sample mode (-os0)"
	@echo " 'c2'     : check double outputs with the c backend in scalar one-sample mode (-os1)"
	@echo " 'c3'     : check double outputs with the c backend in scalar one-sample mode (-os2)"
	@echo " 'c4'     : check double outputs with the c backend in scalar one-sample mode (-os3)"
	@echo " 'mute'   : check double output with mute"
	@echo " 'wasm'   : check double output with wasm backend and various options"
	@echo " 'wast'   : check double output with wast backend and various options"
	@echo " 'llvm'   : check double output with llvm backend and various options"
	@echo " 'llvm1'  : check double output with llvm backend in object code mode (using 'dynamic-faust') and various options"
	@echo " 'interp' : check double output with interpreter backend and various options"
	@echo " 'interp1' : check double output with interpreter/(llvm or MIR) backend and various options"
	@echo " 'rust'   : check double output with rust backend and various options"
	@echo " 'cmajor' : check double output with cmajor backend and various options"
	@echo " 'dlang'  : check double output with D backend and various options"
	@echo " 'jax'    : check double output with JAX backend and various options"
	@echo " 'julia'  : check double output with Julia backend and various options"
	@echo " 'me'     : check double outputs with the cpp backend in scalar with activated math exceptions"
	@echo "Warning: you must have at least 10G available on your hard disk to run all the tests"
	@echo
	@echo "Specific targets:"
	@echo " 'travis'            : tests subset for travis"
	@echo " 'web'               : call the wast/wasm targets"
	@echo " 'reference'         : builds the reference files"
	@echo " 'reference-box'     : builds the reference box files"
	@echo " 'reference-signal'  : builds the reference signal files"
	@echo " 'reference-type'    : builds the reference signal type files"
	@echo " 'test-box'          : test box creation intermediate step"
	@echo " 'test-signal'       : test signal creation intermediate step"
	@echo " 'test-type'         : test signal typing intermediate step"
	@echo " 'tools'             : builds binary tools used by the tests"
	
	@echo
	@echo "Experimental targets:"
	@echo " 'quad'    : check quad output with the cpp and c backends in scalar, vec, openmp and sched modes"
	@echo
	@echo "NOTE1: when running make with option '-j', you should also use '-i' (see the README.md file)"
	@echo "NOTE2: An experimental FIR checker can be activated for all backends testing using 'export FAUST_DEBUG=FIR_CHECKER'."
	@echo

#########################################################################
# automatic travis test
travis:
	$(MAKE) -f Make.gcc outdir=cpp/double          lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double"
	$(MAKE) -f Make.gcc outdir=cpp/double/dlt0     lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -dlt 0"
	$(MAKE) -f Make.gcc outdir=cpp/double/vec      lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -vec"
	$(MAKE) -f Make.gcc outdir=cpp/double/vec/fun  lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -vec -fun"
	$(MAKE) -f Make.gcc outdir=cpp/double/omp      lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -omp"
	#$(MAKE) -f Make.gcc outdir=cpp/double/sch     lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -sch"

#########################################################################
# c++ and c backends
cpp:
	$(MAKE) -f Make.gcc outdir=cpp/double           lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double"
	$(MAKE) -f Make.gcc outdir=cpp/double/fp        lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -fp"
	$(MAKE) -f Make.gcc outdir=cpp/double/wall      lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -wall"
	$(MAKE) -f Make.gcc outdir=cpp/double/mcd0      lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -mcd 0"
	$(MAKE) -f Make.gcc outdir=cpp/double/mapp      lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -mapp"
	$(MAKE) -f Make.gcc outdir=cpp/double/rui       lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -rui"
	$(MAKE) -f Make.gcc outdir=cpp/double/nvi       lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -nvi"
	$(MAKE) -f Make.gcc outdir=cpp/double/dlt0      lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -dlt 0"
	$(MAKE) -f Make.gcc outdir=cpp/double/dlt256    lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -dlt 256"
	$(MAKE) -f Make.gcc outdir=cpp/double/vec/lv0   lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -vec -lv 0"
	$(MAKE) -f Make.gcc outdir=cpp/double/vec/lv0/fun   lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -vec -lv 0 -fun"
	$(MAKE) -f Make.gcc outdir=cpp/double/vec/lv0/vs16  lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -vec -lv 0 -vs 16"
	$(MAKE) -f Make.gcc outdir=cpp/double/vec/lv1       lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -vec -lv 1"
	$(MAKE) -f Make.gcc outdir=cpp/double/vec/lv1/fun   lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -vec -lv 1 -fun"
	$(MAKE) -f Make.gcc outdir=cpp/double/vec/lv1/vs16  lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -vec -lv 1 -vs 16"
	$(MAKE) -f Make.gcc outdir=cpp/double/sched     lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -sch"
	$(MAKE) -f Make.gcc outdir=cpp/double/sched/fun lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -sch -fun"
	$(MAKE) -f Make.gcc outdir=cpp/double/omp       lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -omp"
	$(MAKE) -f Make.gcc outdir=cpp/double/omp/fun   lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -omp -fun"
	$(MAKE) -f Make.gcc outdir=cpp/float            lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -single"
	$(MAKE) -f Make.gcc outdir=cpp/float/vec        lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -single -vec"
	$(MAKE) -f Make.gcc outdir=cpp/float/sched      lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -single -sch"
	$(MAKE) -f Make.gcc outdir=cpp/float/omp        lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -single -omp"

quad:
	$(MAKE) -f Make.gcc outdir=cpp/quad        lang=cpp arch=impulsearch.cpp   FAUSTOPTIONS="-I dsp -quad"
	$(MAKE) -f Make.gcc outdir=cpp/quad/vec    lang=cpp arch=impulsearch.cpp   FAUSTOPTIONS="-I dsp -quad -vec"
	$(MAKE) -f Make.gcc outdir=cpp/quad/sched  lang=cpp arch=impulsearch.cpp   FAUSTOPTIONS="-I dsp -quad -sch"
	$(MAKE) -f Make.gcc outdir=cpp/quad/omp    lang=cpp arch=impulsearch.cpp   FAUSTOPTIONS="-I dsp -quad -omp"
	$(MAKE) -f Make.gcc outdir=c/quad          lang=c arch=impulsearch2.cpp    FAUSTOPTIONS="-I dsp -quad"
	$(MAKE) -f Make.gcc outdir=c/quad/vec      lang=c arch=impulsearch2.cpp    FAUSTOPTIONS="-I dsp -quad -vec"
	$(MAKE) -f Make.gcc outdir=c/quad/sched    lang=c arch=impulsearch2.cpp    FAUSTOPTIONS="-I dsp -quad -sch"
	$(MAKE) -f Make.gcc outdir=c/quad/omp      lang=c arch=impulsearch2.cpp    FAUSTOPTIONS="-I dsp -quad -omp"

fx:
	$(MAKE) -f Make.gcc outdir=cpp/fx            lang=cpp arch=impulsearchfx.cpp   FAUSTOPTIONS="-I dsp -fx"
	$(MAKE) -f Make.gcc outdir=cpp/fx/os0        lang=cpp arch=impulsearchfx.cpp   FAUSTOPTIONS="-I dsp -fx -os0"
	$(MAKE) -f Make.gcc outdir=cpp/fx/os1        lang=cpp arch=impulsearchfx.cpp   FAUSTOPTIONS="-I dsp -fx -os1"
	$(MAKE) -f Make.gcc outdir=cpp/fx/os2        lang=cpp arch=impulsearchfx.cpp   FAUSTOPTIONS="-I dsp -fx -os2"
	$(MAKE) -f Make.gcc outdir=cpp/fx/os3        lang=cpp arch=impulsearch4.cpp   FAUSTOPTIONS="-I dsp -fx -os3"
	$(MAKE) -f Make.gcc outdir=c/fx              lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-I dsp -fx"
	$(MAKE) -f Make.gcc outdir=c/fx/os0          lang=c arch=impulsearch2bis.cpp FAUSTOPTIONS="-I dsp -fx -os0"
	$(MAKE) -f Make.gcc outdir=c/fx/os1          lang=c arch=impulsearch2ter.cpp FAUSTOPTIONS="-I dsp -fx -os1"
	$(MAKE) -f Make.gcc outdir=c/fx/os2          lang=c arch=impulsearch2ter.cpp FAUSTOPTIONS="-I dsp -fx -os2"
	$(MAKE) -f Make.gcc outdir=c/fx/os3          lang=c arch=impulsearch2qua.cpp FAUSTOPTIONS="-I dsp -fx -os3"

cpp1:
	$(MAKE) -f Make.gcc outdir=cpp1/double       lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -os0"
	$(MAKE) -f Make.gcc outdir=cpp1/double/mcd0  lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -os0 -mcd 0"
	$(MAKE) -f Make.gcc outdir=cpp1/double/nvi   lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -os0 -nvi"

cpp2:
	$(MAKE) -f Make.gcc outdir=cpp2/double       lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -os1"
	$(MAKE) -f Make.gcc outdir=cpp2/double/mcd0  lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -os1 -mcd 0"
	$(MAKE) -f Make.gcc outdir=cpp2/double/nvi   lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -os1 -nvi"

cpp3:
	$(MAKE) -f Make.gcc outdir=cpp3_s1/double      lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -os2 -fpga-mem 1000"
	$(MAKE) -f Make.gcc outdir=cpp3_s1/double/mcd0 lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -os2 -fpga-mem 1000 -mcd 0"
	$(MAKE) -f Make.gcc outdir=cpp3_s1/double/nvi  lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -os2 -fpga-mem 1000 -nvi"
	$(MAKE) -f Make.gcc outdir=cpp3_s2/double      lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -os2 -fpga-mem 10000"
	$(MAKE) -f Make.gcc outdir=cpp3_s2/double/mcd0 lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -os2 -fpga-mem 10000 -mcd 0"
	$(MAKE) -f Make.gcc outdir=cpp3_s3/double      lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -os2 -fpga-mem 50000"
	$(MAKE) -f Make.gcc outdir=cpp3_s3/double/mcd0 lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -os2 -fpga-mem 50000 -mcd 0"

cpp4:
	$(MAKE) -f Make.gcc outdir=cpp4_s1/double      lang=cpp arch=impulsearch4.cpp FAUSTOPTIONS="-I dsp -double -os3 -fpga-mem 1000"
	$(MAKE) -f Make.gcc outdir=cpp4_s1/double/mcd0 lang=cpp arch=impulsearch4.cpp FAUSTOPTIONS="-I dsp -double -os3 -fpga-mem 1000 -mcd 0"
	$(MAKE) -f Make.gcc outdir=cpp4_s1/double/nvi  lang=cpp arch=impulsearch4.cpp FAUSTOPTIONS="-I dsp -double -os3 -fpga-mem 1000 -nvi"
	$(MAKE) -f Make.gcc outdir=cpp4_s2/double      lang=cpp arch=impulsearch4.cpp FAUSTOPTIONS="-I dsp -double -os3 -fpga-mem 10000"
	$(MAKE) -f Make.gcc outdir=cpp4_s2/double/mcd0 lang=cpp arch=impulsearch4.cpp FAUSTOPTIONS="-I dsp -double -os3 -fpga-mem 10000 -mcd 0"
	$(MAKE) -f Make.gcc outdir=cpp4_s3/double      lang=cpp arch=impulsearch4.cpp FAUSTOPTIONS="-I dsp -double -os3 -fpga-mem 50000"
	$(MAKE) -f Make.gcc outdir=cpp4_s3/double/mcd0 lang=cpp arch=impulsearch4.cpp FAUSTOPTIONS="-I dsp -double -os3 -fpga-mem 50000 -mcd 0"

cpp5:
	$(MAKE) -f Make.gcc outdir=cpp5_s1/double      lang=cpp arch=impulsearch5.cpp FAUSTOPTIONS="-I dsp -double -os3 -mem -fpga-mem 1000"
	$(MAKE) -f Make.gcc outdir=cpp5_s1/double/mcd0 lang=cpp arch=impulsearch5.cpp FAUSTOPTIONS="-I dsp -double -os3 -mem -fpga-mem 1000 -mcd 0"
	$(MAKE) -f Make.gcc outdir=cpp5_s1/double/nvi  lang=cpp arch=impulsearch5.cpp FAUSTOPTIONS="-I dsp -double -os3 -mem -fpga-mem 1000 -nvi"
	$(MAKE) -f Make.gcc outdir=cpp5_s2/double      lang=cpp arch=impulsearch5.cpp FAUSTOPTIONS="-I dsp -double -os3 -mem -fpga-mem 10000"
	$(MAKE) -f Make.gcc outdir=cpp5_s2/double/mcd0 lang=cpp arch=impulsearch5.cpp FAUSTOPTIONS="-I dsp -double -os3 -mem -fpga-mem 10000 -mcd 0"
	$(MAKE) -f Make.gcc outdir=cpp5_s3/double      lang=cpp arch=impulsearch5.cpp FAUSTOPTIONS="-I dsp -double -os3 -mem -fpga-mem 50000"
	$(MAKE) -f Make.gcc outdir=cpp5_s3/double/mcd0 lang=cpp arch=impulsearch5.cpp FAUSTOPTIONS="-I dsp -double -os3 -mem -fpga-mem 50000 -mcd 0"

cpp6:
	$(MAKE) -f Make.gcc outdir=cpp6_s1/double/mem  lang=cpp arch=impulsearch6.cpp FAUSTOPTIONS="-I dsp -double -mem -fpga-mem 1000"
	$(MAKE) -f Make.gcc outdir=cpp6_s1/double/nvi  lang=cpp arch=impulsearch6.cpp FAUSTOPTIONS="-I dsp -double -mem -fpga-mem 1000 -nvi"

ocpp:
	$(MAKE) -f Make.gcc outdir=ocpp/double          lang=ocpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double"
	$(MAKE) -f Make.gcc outdir=ocpp/double/mcd0     lang=ocpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -mcd 0"
	$(MAKE) -f Make.gcc outdir=ocpp/double/vec/lv0  lang=ocpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -vec -lv 0"
	$(MAKE) -f Make.gcc outdir=ocpp/double/vec/lv1  lang=ocpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -vec -lv 1"

vecocpp:
	$(MAKE) -f Make.gcc outdir=ocpp/double/vec/lv1  lang=ocpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -vec -lv 1"

me:
	$(MAKE) -f Make.gcc outdir=me/double  lang=cpp arch=impulsearch3.cpp FAUSTOPTIONS="-I dsp -double"

c:
	$(MAKE) -f Make.gcc outdir=c/double             lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-I dsp -double"
	$(MAKE) -f Make.gcc outdir=c/double/lp          lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-I dsp -double -fp"
	$(MAKE) -f Make.gcc outdir=c/double/dlt0        lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-I dsp -double -dlt 0"
	$(MAKE) -f Make.gcc outdir=c/double/dlt256      lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-I dsp -double -dlt 256"
	$(MAKE) -f Make.gcc outdir=c/double/vec/lv0     lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-I dsp -double -vec -lv 0"
	$(MAKE) -f Make.gcc outdir=c/double/vec/lv0/fun     lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-I dsp -double -vec -lv 0 -fun"
	$(MAKE) -f Make.gcc outdir=c/double/vec/lv0/vs16    lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-I dsp -double -vec -lv 0 -vs 16"
	$(MAKE) -f Make.gcc outdir=c/double/vec/lv1         lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-I dsp -double -vec -lv 1"
	$(MAKE) -f Make.gcc outdir=c/double/vec/lv1/fun     lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-I dsp -double -vec -lv 1 -fun"
	$(MAKE) -f Make.gcc outdir=c/double/vec/lv1/vs16    lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-I dsp -double -vec -lv 1 -vs 16"
	$(MAKE) -f Make.gcc outdir=c/double/sched       lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-I dsp -double -sch"
	$(MAKE) -f Make.gcc outdir=c/double/sched/fun   lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-I dsp -double -sch -fun"
	$(MAKE) -f Make.gcc outdir=c/double/omp         lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-I dsp -double -omp"
	$(MAKE) -f Make.gcc outdir=c/double/omp/fun     lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-I dsp -double -omp -fun"
	$(MAKE) -f Make.gcc outdir=c/float              lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-I dsp -single"
	$(MAKE) -f Make.gcc outdir=c/float/vec          lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-I dsp -single -vec"
	$(MAKE) -f Make.gcc outdir=c/float/sched        lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-I dsp -single -sch"
	$(MAKE) -f Make.gcc outdir=c/float/omp          lang=c arch=impulsearch2.cpp FAUSTOPTIONS="-I dsp -single -omp"

c1:
	$(MAKE) -f Make.gcc outdir=c1/double         lang=c arch=impulsearch2bis.cpp FAUSTOPTIONS="-I dsp -double -os0"
	$(MAKE) -f Make.gcc outdir=c1/double/dlt0    lang=c arch=impulsearch2bis.cpp FAUSTOPTIONS="-I dsp -double -os0 -dlt 0"
	$(MAKE) -f Make.gcc outdir=c1/double/dlt256  lang=c arch=impulsearch2bis.cpp FAUSTOPTIONS="-I dsp -double -os0 -dlt 256"

c2:
	$(MAKE) -f Make.gcc outdir=c2/double         lang=c arch=impulsearch2ter.cpp FAUSTOPTIONS="-I dsp -double -os1"
	$(MAKE) -f Make.gcc outdir=c2/double/dlt0    lang=c arch=impulsearch2ter.cpp FAUSTOPTIONS="-I dsp -double -os1 -dlt 0"
	$(MAKE) -f Make.gcc outdir=c2/double/dlt256  lang=c arch=impulsearch2ter.cpp FAUSTOPTIONS="-I dsp -double -os1 -dlt 256"

c3:
	$(MAKE) -f Make.gcc outdir=c3_s1/double lang=c arch=impulsearch2ter.cpp FAUSTOPTIONS="-I dsp -double -os2 -fpga-mem 1000"
	$(MAKE) -f Make.gcc outdir=c3_s2/double lang=c arch=impulsearch2ter.cpp FAUSTOPTIONS="-I dsp -double -os2 -fpga-mem 10000"
	$(MAKE) -f Make.gcc outdir=c3_s3/double lang=c arch=impulsearch2ter.cpp FAUSTOPTIONS="-I dsp -double -os2 -fpga-mem 50000"
	
c4:
	$(MAKE) -f Make.gcc outdir=c4_s1/double lang=c arch=impulsearch2qua.cpp FAUSTOPTIONS="-I dsp -double -os3 -fpga-mem 1000"
	$(MAKE) -f Make.gcc outdir=c4_s2/double lang=c arch=impulsearch2qua.cpp FAUSTOPTIONS="-I dsp -double -os3 -fpga-mem 10000"
	$(MAKE) -f Make.gcc outdir=c4_s3/double lang=c arch=impulsearch2qua.cpp FAUSTOPTIONS="-I dsp -double -os3 -fpga-mem 50000"

mute: ir/mute  $(mutefiles)

#########################################################################
# web backends ('wasmdir/wastdir' used instead of 'outdir')
web:
	$(MAKE) wasm
	$(MAKE) wast

wasm:
	$(MAKE) -f Make.web wasm wasmdir=wasm/double         FAUSTOPTIONS="-I dsp"
	$(MAKE) -f Make.web wasm wasmdir=wasm/double/mapp    FAUSTOPTIONS="-I dsp -mapp"
	$(MAKE) -f Make.web wasm wasmdir=wasm/double/dlt0    FAUSTOPTIONS="-I dsp -dlt 0"
	$(MAKE) -f Make.web wasm wasmdir=wasm/double/dlt256  FAUSTOPTIONS="-I dsp -dlt 256"
	$(MAKE) -f Make.web wasm wasmdir=wasm/double/ftz1    FAUSTOPTIONS="-I dsp -ftz 1"
	$(MAKE) -f Make.web wasm wasmdir=wasm/double/ftz2    FAUSTOPTIONS="-I dsp -ftz 2"

wast:
	$(MAKE) -f Make.web wast wastdir=wast/double         FAUSTOPTIONS="-I dsp"
	$(MAKE) -f Make.web wast wastdir=wast/double/lp      FAUSTOPTIONS="-I dsp -fp"
	$(MAKE) -f Make.web wast wastdir=wast/double/mapp    FAUSTOPTIONS="-I dsp -mapp"
	$(MAKE) -f Make.web wast wastdir=wast/double/dlt0    FAUSTOPTIONS="-I dsp -dlt 0"
	$(MAKE) -f Make.web wast wastdir=wast/double/dlt256  FAUSTOPTIONS="-I dsp -dlt 256"
	$(MAKE) -f Make.web wast wastdir=wast/double/ftz1    FAUSTOPTIONS="-I dsp -ftz 1"
	$(MAKE) -f Make.web wast wastdir=wast/double/ftz2    FAUSTOPTIONS="-I dsp -ftz 2"

#########################################################################
# llvm backend
llvm:
	$(MAKE) -f Make.llvm outdir=llvm/double               FAUSTOPTIONS="-I dsp"
	$(MAKE) -f Make.llvm outdir=llvm/double/ftz1          FAUSTOPTIONS="-I dsp -ftz 1"
	$(MAKE) -f Make.llvm outdir=llvm/double/ftz2          FAUSTOPTIONS="-I dsp -ftz 2"
	$(MAKE) -f Make.llvm outdir=llvm/double/ct            FAUSTOPTIONS="-I dsp -ct 0"
	$(MAKE) -f Make.llvm outdir=llvm/double/mapp          FAUSTOPTIONS="-I dsp -mapp"
	$(MAKE) -f Make.llvm outdir=llvm/double/rui           FAUSTOPTIONS="-I dsp -rui"
	$(MAKE) -f Make.llvm outdir=llvm/double/inpl          FAUSTOPTIONS="-I dsp -inpl"
	$(MAKE) -f Make.llvm outdir=llvm/double/dlt0          FAUSTOPTIONS="-I dsp -dlt 0"
	$(MAKE) -f Make.llvm outdir=llvm/double/dlt256        FAUSTOPTIONS="-I dsp -dlt 256"
	$(MAKE) -f Make.llvm outdir=llvm/double/vec/lv0       FAUSTOPTIONS="-I dsp -vec -lv 0"
	$(MAKE) -f Make.llvm outdir=llvm/double/vec/lv0/fun   FAUSTOPTIONS="-I dsp -vec -lv 0 -fun"
	$(MAKE) -f Make.llvm outdir=llvm/double/vec/lv0/vs16  FAUSTOPTIONS="-I dsp -vec -lv 0 -vs 16"
	$(MAKE) -f Make.llvm outdir=llvm/double/vec/lv1       FAUSTOPTIONS="-I dsp -vec -lv 1"
	$(MAKE) -f Make.llvm outdir=llvm/double/vec/lv1/fun   FAUSTOPTIONS="-I dsp -vec -lv 1 -fun"
	$(MAKE) -f Make.llvm outdir=llvm/double/vec/lv1/vs16  FAUSTOPTIONS="-I dsp -vec -lv 1 -vs 16"
	$(MAKE) -f Make.llvm outdir=llvm/double/vec/vs200     FAUSTOPTIONS="-I dsp -vec -vs 200"
	$(MAKE) -f Make.llvm outdir=llvm/double/vec/g         FAUSTOPTIONS="-I dsp -vec -lv 1 -g"
	$(MAKE) -f Make.llvm outdir=llvm/double/vec/gfun      FAUSTOPTIONS="-I dsp -vec -lv 1 -g -fun"
	#$(MAKE) -f Make.llvm outdir=llvm/double/sch FAUSTOPTIONS="-I dsp -sch"

#########################################################################
# llvm backend in object code mode
llvm1:
	$(MAKE) -f Make.llvm1 outdir=llvm1/double               FAUSTOPTIONS="-I dsp -double"
	$(MAKE) -f Make.llvm1 outdir=llvm1/double/inpl          FAUSTOPTIONS="-I dsp -double -inpl"
	$(MAKE) -f Make.llvm1 outdir=llvm1/double/dlt0          FAUSTOPTIONS="-I dsp -double -dlt 0"
	$(MAKE) -f Make.llvm1 outdir=llvm1/double/dlt256        FAUSTOPTIONS="-I dsp -double -dlt 256"
	$(MAKE) -f Make.llvm1 outdir=llvm1/double/vec/lv0       FAUSTOPTIONS="-I dsp -double -vec -lv 0"
	$(MAKE) -f Make.llvm1 outdir=llvm1/double/vec/lv0/fun   FAUSTOPTIONS="-I dsp -double -vec -lv 0 -fun"
	$(MAKE) -f Make.llvm1 outdir=llvm1/double/vec/lv0/vs16  FAUSTOPTIONS="-I dsp -double -vec -lv 0 -vs 16"
	$(MAKE) -f Make.llvm1 outdir=llvm1/double/vec/lv1       FAUSTOPTIONS="-I dsp -double -vec -lv 1"
	$(MAKE) -f Make.llvm1 outdir=llvm1/double/vec/lv1/fun   FAUSTOPTIONS="-I dsp -double -vec -lv 1 -fun"
	$(MAKE) -f Make.llvm1 outdir=llvm1/double/vec/lv1/vs16  FAUSTOPTIONS="-I dsp -double -vec -lv 1 -vs 16"
	$(MAKE) -f Make.llvm1 outdir=llvm1/double/vec/vs200     FAUSTOPTIONS="-I dsp -double -vec -vs 200"
	$(MAKE) -f Make.llvm1 outdir=llvm1/double/vec/g         FAUSTOPTIONS="-I dsp -double -vec -lv 1 -g"
	$(MAKE) -f Make.llvm1 outdir=llvm1/double/vec/gfun      FAUSTOPTIONS="-I dsp -double -vec -lv 1 -g -fun"
	#$(MAKE) -f Make.llvm1 outdir=llvm1/double/sch          FAUSTOPTIONS="-I dsp -sch"

#########################################################################
# interp backend
interp:
	$(MAKE) -f Make.interp outdir=interp/double              FAUSTOPTIONS="-I dsp"
	$(MAKE) -f Make.interp outdir=interp/double/ct           FAUSTOPTIONS="-I dsp -ct 0"
	$(MAKE) -f Make.interp outdir=interp/double/cir          FAUSTOPTIONS="-I dsp -cir"
	$(MAKE) -f Make.interp outdir=interp/double/mapp         FAUSTOPTIONS="-I dsp -mapp"
	$(MAKE) -f Make.interp outdir=interp/double/rui          FAUSTOPTIONS="-I dsp -rui"
	$(MAKE) -f Make.interp outdir=interp/double/dlt0         FAUSTOPTIONS="-I dsp -dlt 0"
	$(MAKE) -f Make.interp outdir=interp/double/dlt256       FAUSTOPTIONS="-I dsp -dlt 256"
	#$(MAKE) -f Make.interp outdir=interp/double/lv0         FAUSTOPTIONS="-I dsp -vec -lv 0"
	#$(MAKE) -f Make.interp outdir=interp/double/lv0/vs16    FAUSTOPTIONS="-I dsp -vec -lv 0 -vs 16"
	$(MAKE) -f Make.interp outdir=interp/double/vec/lv1      FAUSTOPTIONS="-I dsp -vec -lv 1"
	$(MAKE) -f Make.interp outdir=interp/double/vec/lv1/vs16 FAUSTOPTIONS="-I dsp -vec -lv 1 -vs 16"
	#$(MAKE) -f Make.interp outdir=interp/double/vec/vs200   FAUSTOPTIONS="-I dsp -vec -vs 200"
	$(MAKE) -f Make.interp outdir=interp/double/vec/g        FAUSTOPTIONS="-I dsp -vec -lv 1 -g"
	$(MAKE) -f Make.interp outdir=interp/double/inpl         FAUSTOPTIONS="-I dsp -inpl"
	$(MAKE) -f Make.interp outdir=interp/double/ftz          FAUSTOPTIONS="-I dsp -ftz 1"

#########################################################################
# interp backend in LLVM mode
interp1:
	$(MAKE) -f Make.interp1 outdir=interp1/double              FAUSTOPTIONS="-I dsp"
	$(MAKE) -f Make.interp1 outdir=interp1/double/dlt0         FAUSTOPTIONS="-I dsp -dlt 0"
	$(MAKE) -f Make.interp1 outdir=interp1/double/dlt256       FAUSTOPTIONS="-I dsp -dlt 256"
	#$(MAKE) -f Make.interp1 outdir=interp1/double/lv0         FAUSTOPTIONS="-I dsp -vec -lv 0"
	#$(MAKE) -f Make.interp1 outdir=interp1/double/lv0/vs16    FAUSTOPTIONS="-I dsp -vec -lv 0 -vs 16"
	$(MAKE) -f Make.interp1 outdir=interp1/double/vec/lv1      FAUSTOPTIONS="-I dsp -vec -lv 1"
	$(MAKE) -f Make.interp1 outdir=interp1/double/vec/lv1/vs16 FAUSTOPTIONS="-I dsp -vec -lv 1 -vs 16"
	#$(MAKE) -f Make.interp1 outdir=interp1/double/vec/vs200   FAUSTOPTIONS="-I dsp -vec -vs 200"
	$(MAKE) -f Make.interp1 outdir=interp1/double/vec/g        FAUSTOPTIONS="-I dsp -vec -lv 1 -g"
	$(MAKE) -f Make.interp1 outdir=interp1/double/inpl         FAUSTOPTIONS="-I dsp -inpl"
	$(MAKE) -f Make.interp1 outdir=interp1/double/ftz          FAUSTOPTIONS="-I dsp -ftz 1"

#########################################################################
# Rust backend
rust:
	$(MAKE) -f Make.rust FAUSTOPTIONS="-I dsp -double"
	$(MAKE) -f Make.rust FAUSTOPTIONS="-I dsp -double -fp"

#########################################################################
# Cmajor backend
cmajor:
	$(MAKE) -f Make.cmajor outdir=cmajor      FAUSTOPTIONS=" -I dsp -double"
	$(MAKE) -f Make.cmajor outdir=cmajor/fp   FAUSTOPTIONS=" -I dsp -double -fp"
	$(MAKE) -f Make.cmajor outdir=cmajor/mapp FAUSTOPTIONS=" -I dsp -double -mapp"

#########################################################################
# D backend
dlang:
	$(MAKE) -f Make.dlang outdir=dlang/double     FAUSTOPTIONS="-I dsp -double"
	$(MAKE) -f Make.dlang outdir=dlang/double/lp  FAUSTOPTIONS="-I dsp -double -fp"
	$(MAKE) -f Make.dlang outdir=dlang/double/vec FAUSTOPTIONS="-I dsp -double -vec"

#########################################################################
# JAX backend
jax:
	$(MAKE) -f Make.jax outdir=jax/double FAUSTOPTIONS="-I dsp -double"
	
#########################################################################
# Julia backend
julia:
	$(MAKE) -f Make.julia outdir=julia/double FAUSTOPTIONS="-I dsp -double"

#########################################################################
# output directories
ir/mute:
	mkdir -p ir/mute

#########################################################################
# building reference files
reference:
	$(MAKE) -f Make.ref

reference-box:
	$(MAKE) -f Make.ref reference-box FAUSTOPTIONS="-I dsp"
	
reference-signal:
	$(MAKE) -f Make.ref reference-signal FAUSTOPTIONS="-I dsp"

reference-type:
	$(MAKE) -f Make.ref reference-type FAUSTOPTIONS="-I dsp"

tools: filesCompare impulsellvm impulseinterp impulseinterp1 

clean:
	rm -f filesCompare impulsellvm impulseinterp impulseinterp1

#########################################################################
# Testing Box and Signal creation intermediate steps

test-box:
	cd dsp && ./box-script *.dsp

test-signal:
	cd dsp && ./sig-script *.dsp
	
#########################################################################
# Testing signal type

test-type:
	cd dsp && ./type-script *.dsp

#########################################################################
# tools
filesCompare: $(SRCDIR)/filesCompare.cpp
	$(CXX) $(TOOLSOPTIONS) $(SRCDIR)/filesCompare.cpp -o filesCompare

impulseinterp: $(SRCDIR)/impulseinterp.cpp ./archs/controlTools.h $(LIB)
	$(CXX) $(TOOLSOPTIONS) -L/opt/local/lib -Iarchs $(SRCDIR)/impulseinterp.cpp $(LIB) $(LLVM_LIB) -o impulseinterp

impulseinterp1: $(SRCDIR)/impulseinterp1.cpp ./archs/controlTools.h $(LIB)
	$(CXX) $(TOOLSOPTIONS) -L/opt/local/lib -Iarchs $(SRCDIR)/impulseinterp1.cpp $(MACHINE_LIB) $(LLVM_LIB) -o impulseinterp1

# Target to use the Interp MIR backend
impulseinterp2: $(SRCDIR)/impulseinterp1.cpp ./archs/controlTools.h $(LIB)
	$(CXX) $(TOOLSOPTIONS) -L/opt/local/lib -Iarchs $(SRCDIR)/impulseinterp1.cpp $(MACHINE_LIB) /usr/local/lib/libmir.a -o impulseinterp1

impulsellvm: $(SRCDIR)/impulsellvm.cpp ./archs/controlTools.h $(LIB)
	$(CXX) $(TOOLSOPTIONS) -L/opt/local/lib -Iarchs $(SRCDIR)/impulsellvm.cpp $(LIB) $(LLVM_LIB) $(WINSOCK) -o impulsellvm

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
	echo "process = P : par(i, outputs(P), (_,(1-checkbox(\"fakedisable %2i\")) : *)) with { P = component(\"$<\"); };" > $@
