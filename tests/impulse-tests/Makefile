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
# -fwrapv: Faust-generated code assumes two's-complement wrapping for the
# integer noise LCG (1103515245 * i + 12345 overflows int, which is UB in
# C/C++). Newer compilers (observed with Apple clang 21) exploit that UB
# at -O2/-O3 and miscompile the table-fill variant (dsp/table.dsp).
GCCOPTIONS := -O3 -I../../architecture -I/usr/local/include/ap_fixed -Iarchs -pthread -std=c++14
outdir ?= float
arch ?= ./archs/impulsearch.cpp
FAUSTOPTIONS := -lang cpp -double -i -a $(arch)
CLANG_TIDY ?= clang-tidy
CLANG_TIDY_OUTDIR ?= cpp/double
CLANG_TIDY_CHECKS ?= clang-analyzer-*,-clang-analyzer-cplusplus.NewDeleteLeaks
CLANG_TIDY_ARGS ?=
CLANG_TIDY_CXXFLAGS ?= -std=c++11 -I../../architecture -I/usr/local/include/ap_fixed -Iarchs -pthread
CLANG_TIDY_FAUSTOPTIONS ?= -I dsp -double
CLANG_TIDY_ARCH ?= impulsearch.cpp

.PHONY: test reference clang-tidy clang-tidy-cpp asan-cpp asc

dspfiles := $(wildcard dsp/*.dsp)
mutefiles = $(dspfiles:dsp/%.dsp=ir/mute/%.ir)
CLANG_TIDY_CPP_FILES := $(dspfiles:dsp/%.dsp=ir/$(CLANG_TIDY_OUTDIR)/%.cpp)

TOOLSOPTIONS := -std=c++14 -O3 -I../../architecture
LIB ?= ../../build/lib/libfaust.a
MACHINE_LIB ?= ../../build/lib/libfaustmachine.a
LLVM_LIB ?= `llvm-config --link-static --ldflags --libs all --system-libs`
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
	$(MAKE) nnx
	$(MAKE) linen
	$(MAKE) julia

help:
	@echo "-------- FAUST impulse response tests --------"
	@echo "Available targets are:"
	@echo " 'all' (default): call all the targets below"
	@echo " 'legs'   : list every leg (one run of Make.gcc) ; run one alone with 'make leg/<outdir>'"
	@echo
	@echo " 'cpp'    : check float and double outputs with the cpp backend in scalar, vec, openmp and sched modes"
	@echo " 'cpp1'   : check double outputs with the cpp backend in scalar and -mem"
	@echo " 'cpp2'   : check double outputs with the cpp backend in scalar and -ec, -os and -mem0/-mem1"
	@echo " 'cpp3'   : check double outputs with the cpp backend in vec and -ec and -mem0/-mem1"
	@echo " 'cpp4'   : check double outputs with the cpp backend in scalar and -ec, -os/-vec, -fpga-mem and -mem2"
	@echo " 'ocpp'   : check double outputs with the ocpp backend in scalar mode"
	@echo " 'c'      : check float and double outputs with the c backend in scalar, vec, openmp and sched modes"
	@echo " 'c1'     : check double outputs with the cpp backend in scalar and -ec, -os and -mem0/-mem1"
	@echo " 'c2'     : check double outputs with the cpp backend in -ec, -os/-vec -fpga-mem and -mem2"
	@echo " 'mute'   : check double output with mute"
	@echo " 'wasm'   : check double output with wasm backend and various options"
	@echo " 'wast'   : check double output with wast backend and various options"
	@echo " 'llvm'   : check double output with llvm backend and various options"
	@echo " 'llvm1'  : check double output with llvm backend in object code mode (using 'dynamic-faust') and various options"
	@echo " 'interp' : check double output with interpreter backend and various options"
	@echo " 'interp1' : check double output with interpreter/(llvm or MIR) backend and various options"
	@echo " 'rust'   : check double output with rust backend and various options"
	@echo " 'cmajor' : check double output with cmajor backend and various options"
	@echo " 'rnbo'   : check double output with rnbo backend and various options"
	@echo " 'dlang'  : check double output with D backend and various options"
	@echo " 'nnx'    : check double output with NNX backend and various options"
	@echo " 'linen'  : check double output with Linen backend and various options"
	@echo " 'julia'  : check double output with Julia backend and various options"
	@echo " 'jsfx'   : check double output with JSFX backend and various options"
	@echo " 'assemblyscript' : smoke-test output generation with AssemblyScript backend"
	@echo " 'asc'    : AssemblyScript impulse tests with reference comparison (compare=1)"
	@echo " 'signal' : check double output with signal interpreter"
	@echo " 'me'     : check double outputs with the cpp backend in scalar with activated math exceptions"
	@echo "Warning: you must have at least 10G available on your hard disk to run all the tests"
	@echo
	@echo "Specific targets:"
	@echo " 'travis'                 : tests subset for travis"
	@echo " 'web'                    : call the wast/wasm targets"
	@echo " 'reference'              : build the reference files"
	@echo " 'reference-box'          : build the reference box files"
	@echo " 'reference-signal'       : build the reference signal files"
	@echo " 'reference-signal-wn'    : build the reference signal files without normalisation (FAUST_OPT=FAUST_SIG_NO_NORM)"
	@echo " 'reference-type'         : build the reference signal type files"
	@echo " 'reference-fir'          : build the reference FIR files"
	@echo " 'reference-cpp'          : build the reference C++ files"
	@echo " 'test-box'               : test box creation intermediate step"
	@echo " 'test-signal'            : test signal creation intermediate step"
	@echo " 'test-signal-wn'         : test signal creation intermediate step without normalisation (FAUST_OPT=FAUST_SIG_NO_NORM)"
	@echo " 'test-type'              : test signal typing intermediate step"
	@echo " 'test-fir'               : test FIR intermediate step"
	@echo " 'test-cpp'               : test C++ generation step"
	@echo " 'clang-tidy'             : run clang-tidy (clang-analyzer checks like uninit/UB/null deref; static-only) on generated C++ in ir/$(CLANG_TIDY_OUTDIR)"
	@echo " 'asan-cpp'               : build+run generated C++ with AddressSanitizer (runtime checks for heap/stack/UAF/OOB)"
	@echo " 'bench'                  : benchmark using faustbench-llvm and faustbench"
	@echo " 'interp-tracer'          : test using the interp-tracer tool"
	@echo " 'tools'                  : builds binary tools used by the tests"
	
	@echo
	@echo "Experimental targets:"
	@echo " 'quad'    : check quad output with the cpp and c backends in scalar, vec, openmp and sched modes"
	@echo
	@echo "NOTE1: when running make with option '-j', you should also use '-i' (see the README.md file)"
	@echo "NOTE2: an experimental FIR checker can be activated for all backends testing using 'export FAUST_DEBUG=FIR_CHECKER'."
	@echo "NOTE3: on macOS ARM, 'make universal' can be used to build a x86_64/arm64 target. Then 'arch -x86_64 /bin/bash' allows to launch targets in x86_64 mode."
	@echo

#########################################################################
# AssemblyScript backend shortcut
asc:
	$(MAKE) -f Make.assemblyscript assemblyscript compare=1

#########################################################################
# automatic travis test
# ---- Legs ------------------------------------------------------------------
# A leg is one run of Make.gcc : an output directory, a language, an
# architecture and the faust options. Each leg is its own target, so that
# `make -k <family>` keeps going past a failing leg -- inside a single recipe
# the first failing line ends the recipe, and -k only carries across
# targets -- and so that one leg can be run alone : `make leg/cpp/double/vec/lv0`.
# `make legs` lists them. A leg is defined once, even when several families use it.

define LEG
LEGS += leg/$(strip $(1))
.PHONY: leg/$(strip $(1))
leg/$(strip $(1)):
	$$(MAKE) -f Make.gcc outdir=$(strip $(1)) lang=$(strip $(2)) arch=$(strip $(3)) FAUSTOPTIONS="$(strip $(4))"
endef

# travis
$(eval $(call LEG, cpp/double                   , cpp , impulsearch.cpp     , -I dsp -double))
$(eval $(call LEG, cpp/double/dlt0              , cpp , impulsearch.cpp     , -I dsp -double -dlt 0))
$(eval $(call LEG, cpp/double/vec               , cpp , impulsearch.cpp     , -I dsp -double -vec))
$(eval $(call LEG, cpp/double/vec/fun           , cpp , impulsearch.cpp     , -I dsp -double -vec -fun))
$(eval $(call LEG, cpp/double/omp               , cpp , impulsearch.cpp     , -I dsp -double -omp))

# cpp
$(eval $(call LEG, cpp/double/uim               , cpp , impulsearch.cpp     , -I dsp -double -uim))
$(eval $(call LEG, cpp/double/it                , cpp , impulsearch.cpp     , -I dsp -double -it))
$(eval $(call LEG, cpp/double/fp                , cpp , impulsearch.cpp     , -I dsp -double -fp))
$(eval $(call LEG, cpp/double/wall              , cpp , impulsearch.cpp     , -I dsp -double -wall))
$(eval $(call LEG, cpp/double/mcd0              , cpp , impulsearch.cpp     , -I dsp -double -mcd 0))
$(eval $(call LEG, cpp/double/mapp              , cpp , impulsearch.cpp     , -I dsp -double -mapp))
$(eval $(call LEG, cpp/double/rui               , cpp , impulsearch.cpp     , -I dsp -double -rui))
$(eval $(call LEG, cpp/double/nvi               , cpp , impulsearch.cpp     , -I dsp -double -nvi))
$(eval $(call LEG, cpp/double/dlt256            , cpp , impulsearch.cpp     , -I dsp -double -dlt 256))
$(eval $(call LEG, cpp/double/vec/lv0           , cpp , impulsearch.cpp     , -I dsp -double -vec -lv 0))
$(eval $(call LEG, cpp/double/vec/lv0/fun       , cpp , impulsearch.cpp     , -I dsp -double -vec -lv 0 -fun))
$(eval $(call LEG, cpp/double/vec/lv0/vs16      , cpp , impulsearch.cpp     , -I dsp -double -vec -lv 0 -vs 16))
$(eval $(call LEG, cpp/double/vec/lv1           , cpp , impulsearch.cpp     , -I dsp -double -vec -lv 1))
$(eval $(call LEG, cpp/double/vec/lv1/fun       , cpp , impulsearch.cpp     , -I dsp -double -vec -lv 1 -fun))
$(eval $(call LEG, cpp/double/vec/lv1/vs16      , cpp , impulsearch.cpp     , -I dsp -double -vec -lv 1 -vs 16))
$(eval $(call LEG, cpp/double/sched             , cpp , impulsearch.cpp     , -I dsp -double -sch))
$(eval $(call LEG, cpp/double/sched/fun         , cpp , impulsearch.cpp     , -I dsp -double -sch -fun))
$(eval $(call LEG, cpp/double/omp/fun           , cpp , impulsearch.cpp     , -I dsp -double -omp -fun))
$(eval $(call LEG, cpp/float                    , cpp , impulsearch.cpp     , -I dsp -single))
$(eval $(call LEG, cpp/float/vec                , cpp , impulsearch.cpp     , -I dsp -single -vec))
$(eval $(call LEG, cpp/float/sched              , cpp , impulsearch.cpp     , -I dsp -single -sch))
$(eval $(call LEG, cpp/float/omp                , cpp , impulsearch.cpp     , -I dsp -single -omp))

# quad
$(eval $(call LEG, cpp/quad                     , cpp , impulsearch.cpp     , -I dsp -quad))
$(eval $(call LEG, cpp/quad/vec                 , cpp , impulsearch.cpp     , -I dsp -quad -vec))
$(eval $(call LEG, cpp/quad/sched               , cpp , impulsearch.cpp     , -I dsp -quad -sch))
$(eval $(call LEG, cpp/quad/omp                 , cpp , impulsearch.cpp     , -I dsp -quad -omp))
$(eval $(call LEG, c/quad                       , c   , impulsearch2.cpp    , -I dsp -quad))
$(eval $(call LEG, c/quad/vec                   , c   , impulsearch2.cpp    , -I dsp -quad -vec))
$(eval $(call LEG, c/quad/sched                 , c   , impulsearch2.cpp    , -I dsp -quad -sch))
$(eval $(call LEG, c/quad/omp                   , c   , impulsearch2.cpp    , -I dsp -quad -omp))

# fx
$(eval $(call LEG, cpp/fx                       , cpp , impulsearchfx.cpp   , -I dsp -fx))
$(eval $(call LEG, c/fx                         , c   , impulsearch2.cpp    , -I dsp -fx))

# fx1
$(eval $(call LEG, cpp/fx1                      , cpp , impulsearchfx.cpp   , -I dsp -fx -fx-size -1))
$(eval $(call LEG, c/fx1                        , c   , impulsearch2.cpp    , -I dsp -fx -fx-size -1))

# cpp1
$(eval $(call LEG, cpp1/double/mem0             , cpp , impulsearch6.cpp    , -I dsp -double -mem))
$(eval $(call LEG, cpp1/double/mem1             , cpp , impulsearch6.cpp    , -I dsp -double -it -mem1))
$(eval $(call LEG, cpp1/double/mem1fpgamemth0   , cpp , impulsearch6.cpp    , -I dsp -double -it -mem1 -fpga-mem-th 0))
$(eval $(call LEG, cpp1/double/mem1fpgamemth2   , cpp , impulsearch6.cpp    , -I dsp -double -it -mem1 -fpga-mem-th 2))
$(eval $(call LEG, cpp1/double/mem1fpgamemth8   , cpp , impulsearch6.cpp    , -I dsp -double -it -mem1 -fpga-mem-th 8))

# cpp2
$(eval $(call LEG, cpp2/double/ec               , cpp , impulsearch7.cpp    , -I dsp -double -ec))
$(eval $(call LEG, cpp2/double/ecmem0           , cpp , impulsearch7bis.cpp , -I dsp -double -ec -mem))
$(eval $(call LEG, cpp2/double/ecmem1it         , cpp , impulsearch7bis.cpp , -I dsp -double -ec -mem1 -it))
$(eval $(call LEG, cpp2/double/os               , cpp , impulsearch7ter.cpp , -I dsp -double -os))
$(eval $(call LEG, cpp2/double/osec             , cpp , impulsearch7ter.cpp , -I dsp -double -os -ec))
$(eval $(call LEG, cpp2/double/osmem            , cpp , impulsearch7qua.cpp , -I dsp -double -os -mem))
$(eval $(call LEG, cpp2/double/osmem1           , cpp , impulsearch7qua.cpp , -I dsp -double -os -mem1 -it))
$(eval $(call LEG, cpp2/double/osecmem          , cpp , impulsearch7qua.cpp , -I dsp -double -os -ec -mem))
$(eval $(call LEG, cpp2/double/osecmem1it       , cpp , impulsearch7qua.cpp , -I dsp -double -os -ec -mem1 -it))

# cpp3
$(eval $(call LEG, cpp3/double/vecec            , cpp , impulsearch7.cpp    , -I dsp -t 0 -double -vec -ec))
$(eval $(call LEG, cpp3/double/vececmem0        , cpp , impulsearch7bis.cpp , -I dsp -t 0 -double -vec -ec -mem))
$(eval $(call LEG, cpp3/double/vececmem1it      , cpp , impulsearch7bis.cpp , -I dsp -t 0 -double -vec -ec -mem1 -it))
$(eval $(call LEG, cpp3/double/vecfunecmem1it   , cpp , impulsearch7bis.cpp , -I dsp -t 0 -double -vec -fun -ec -mem1 -it))

# cpp4
$(eval $(call LEG, cpp4/double/mem2             , cpp , impulsearch8.cpp    , -I dsp -double -mem2 -it))
$(eval $(call LEG, cpp4/double/ecmem2           , cpp , impulsearch8bis.cpp , -I dsp -double -ec -mem2 -it))
$(eval $(call LEG, cpp4/double/fpga10mem2it     , cpp , impulsearch8.cpp    , -I dsp -double -fpga-mem 10 -mem2 -it))
$(eval $(call LEG, cpp4/double/fpga100mem2it    , cpp , impulsearch8.cpp    , -I dsp -double -fpga-mem 100 -mem2 -it))
$(eval $(call LEG, cpp4/double/fpga1000mem2it   , cpp , impulsearch8.cpp    , -I dsp -double -fpga-mem 1000 -mem2 -it))
$(eval $(call LEG, cpp4/double/fpga10000mem2it  , cpp , impulsearch8.cpp    , -I dsp -double -fpga-mem 10000 -mem2 -it))
$(eval $(call LEG, cpp4/double/ecfpga10mem2it   , cpp , impulsearch8bis.cpp , -I dsp -double -ec -fpga-mem 10 -mem2 -it))
$(eval $(call LEG, cpp4/double/ecfpga100mem2it  , cpp , impulsearch8bis.cpp , -I dsp -double -ec -fpga-mem 100 -mem2 -it))
$(eval $(call LEG, cpp4/double/ecfpga1000mem2it , cpp , impulsearch8bis.cpp , -I dsp -double -ec -fpga-mem 1000 -mem2 -it))
$(eval $(call LEG, cpp4/double/ecfpga10000mem2it, cpp , impulsearch8bis.cpp , -I dsp -double -ec -fpga-mem 10000 -mem2 -it))
$(eval $(call LEG, cpp4/double/vecmem2it        , cpp , impulsearch8.cpp    , -I dsp -t 0 -double -vec -mem2 -it))
$(eval $(call LEG, cpp4/double/vececmem2it      , cpp , impulsearch8bis.cpp , -I dsp -t 0 -double -vec -ec -mem2 -it))
$(eval $(call LEG, cpp4/double/veclv1ecmem2it   , cpp , impulsearch8bis.cpp , -I dsp -t 0 -double -vec -lv 1 -ec -mem2 -it))
$(eval $(call LEG, cpp4/double/vecfunecmem2it   , cpp , impulsearch8bis.cpp , -I dsp -t 0 -double -vec -fun -ec -mem2 -it))
$(eval $(call LEG, cpp4/double/osmem2it         , cpp , impulsearch8ter.cpp , -I dsp -double -os -mem2 -it))
$(eval $(call LEG, cpp4/double/osecmem2it       , cpp , impulsearch8ter.cpp , -I dsp -double -os -ec -mem2 -it))
$(eval $(call LEG, cpp4/double/osfpga10mem2it   , cpp , impulsearch8ter.cpp , -I dsp -double -os -fpga-mem 10 -mem2 -it))
$(eval $(call LEG, cpp4/double/osfpga100mem2it  , cpp , impulsearch8ter.cpp , -I dsp -double -os -fpga-mem 100 -mem2 -it))
$(eval $(call LEG, cpp4/double/ecosfpga10mem2it , cpp , impulsearch8ter.cpp , -I dsp -double -ec -os -fpga-mem 10 -mem2 -it))
$(eval $(call LEG, cpp4/double/ecosfpga100mem2it, cpp , impulsearch8ter.cpp , -I dsp -double -ec -os -fpga-mem 100 -mem2 -it))

# ocpp
$(eval $(call LEG, ocpp/double                  , ocpp, impulsearch.cpp     , -I dsp -double))
$(eval $(call LEG, ocpp/double/mcd0             , ocpp, impulsearch.cpp     , -I dsp -double -mcd 0))
$(eval $(call LEG, ocpp/double/vec/lv0          , ocpp, impulsearch.cpp     , -I dsp -double -vec -lv 0))
$(eval $(call LEG, ocpp/double/vec/lv1          , ocpp, impulsearch.cpp     , -I dsp -double -vec -lv 1))

# me
$(eval $(call LEG, me/double                    , cpp , impulsearch3.cpp    , -I dsp -double))

# c
$(eval $(call LEG, c/double                     , c   , impulsearch2.cpp    , -I dsp -double))
$(eval $(call LEG, c/double/it                  , c   , impulsearch2.cpp    , -I dsp -double -it))
$(eval $(call LEG, c/double/lp                  , c   , impulsearch2.cpp    , -I dsp -double -fp))
$(eval $(call LEG, c/double/dlt0                , c   , impulsearch2.cpp    , -I dsp -double -dlt 0))
$(eval $(call LEG, c/double/dlt256              , c   , impulsearch2.cpp    , -I dsp -double -dlt 256))
$(eval $(call LEG, c/double/vec/lv0             , c   , impulsearch2.cpp    , -I dsp -double -vec -lv 0))
$(eval $(call LEG, c/double/vec/lv0/fun         , c   , impulsearch2.cpp    , -I dsp -double -vec -lv 0 -fun))
$(eval $(call LEG, c/double/vec/lv0/vs16        , c   , impulsearch2.cpp    , -I dsp -double -vec -lv 0 -vs 16))
$(eval $(call LEG, c/double/vec/lv1             , c   , impulsearch2.cpp    , -I dsp -double -vec -lv 1))
$(eval $(call LEG, c/double/vec/lv1/fun         , c   , impulsearch2.cpp    , -I dsp -double -vec -lv 1 -fun))
$(eval $(call LEG, c/double/vec/lv1/vs16        , c   , impulsearch2.cpp    , -I dsp -double -vec -lv 1 -vs 16))
$(eval $(call LEG, c/double/sched               , c   , impulsearch2.cpp    , -I dsp -double -sch))
$(eval $(call LEG, c/double/sched/fun           , c   , impulsearch2.cpp    , -I dsp -double -sch -fun))
$(eval $(call LEG, c/double/omp                 , c   , impulsearch2.cpp    , -I dsp -double -omp))
$(eval $(call LEG, c/double/omp/fun             , c   , impulsearch2.cpp    , -I dsp -double -omp -fun))
$(eval $(call LEG, c/float                      , c   , impulsearch2.cpp    , -I dsp -single))
$(eval $(call LEG, c/float/vec                  , c   , impulsearch2.cpp    , -I dsp -single -vec))
$(eval $(call LEG, c/float/sched                , c   , impulsearch2.cpp    , -I dsp -single -sch))
$(eval $(call LEG, c/float/omp                  , c   , impulsearch2.cpp    , -I dsp -single -omp))

# c1
$(eval $(call LEG, c1/double/ec                 , c   , impulsearch9.cpp    , -I dsp -double -ec))
$(eval $(call LEG, c1/double/os                 , c   , impulsearch9bis.cpp , -I dsp -double -os))
$(eval $(call LEG, c1/double/osec               , c   , impulsearch9ter.cpp , -I dsp -double -os -ec))
$(eval $(call LEG, c1/double/mem2it             , c   , impulsearch9qua.cpp , -I dsp -double -mem2 -it))
$(eval $(call LEG, c1/double/fpga10mem2it       , c   , impulsearch9qua.cpp , -I dsp -double -fpga-mem 10 -mem2 -it))
$(eval $(call LEG, c1/double/fpga100mem2it      , c   , impulsearch9qua.cpp , -I dsp -double -fpga-mem 100 -mem2 -it))
$(eval $(call LEG, c1/double/fpga1000mem2it     , c   , impulsearch9qua.cpp , -I dsp -double -fpga-mem 1000 -mem2 -it))
$(eval $(call LEG, c1/double/vecfpga100mem2it   , c   , impulsearch9qua.cpp , -I dsp -double -t 0 -vec -fpga-mem 1000 -mem2 -it))

# c2
$(eval $(call LEG, c2/double/ecos0mem2it        , c   , impulsearch10.cpp   , -I dsp -double -ec -os -mem2 -it))
$(eval $(call LEG, c2/double/ecosfpga10mem2it   , c   , impulsearch10.cpp   , -I dsp -double -fpga-mem 10 -ec -os -mem2 -it))
$(eval $(call LEG, c2/double/ecosfpga100mem2it  , c   , impulsearch10.cpp   , -I dsp -double -fpga-mem 100 -ec -os -mem2 -it))
$(eval $(call LEG, c2/double/vececfpga100mem2it , c   , impulsearch10bis.cpp, -I dsp -double -vec -fpga-mem 100 -ec -mem2 -it))

legs:
	@for l in $(LEGS); do echo $$l; done

.PHONY: travis
#$(MAKE) -f Make.gcc outdir=cpp/double/sch     lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double -sch"
travis: leg/cpp/double \
	leg/cpp/double/dlt0 \
	leg/cpp/double/vec \
	leg/cpp/double/vec/fun \
	leg/cpp/double/omp

.PHONY: cpp
cpp: leg/cpp/double \
	leg/cpp/double/uim \
	leg/cpp/double/it \
	leg/cpp/double/fp \
	leg/cpp/double/wall \
	leg/cpp/double/mcd0 \
	leg/cpp/double/mapp \
	leg/cpp/double/rui \
	leg/cpp/double/nvi \
	leg/cpp/double/dlt0 \
	leg/cpp/double/dlt256 \
	leg/cpp/double/vec/lv0 \
	leg/cpp/double/vec/lv0/fun \
	leg/cpp/double/vec/lv0/vs16 \
	leg/cpp/double/vec/lv1 \
	leg/cpp/double/vec/lv1/fun \
	leg/cpp/double/vec/lv1/vs16 \
	leg/cpp/double/sched \
	leg/cpp/double/sched/fun \
	leg/cpp/double/omp \
	leg/cpp/double/omp/fun \
	leg/cpp/float \
	leg/cpp/float/vec \
	leg/cpp/float/sched \
	leg/cpp/float/omp

.PHONY: quad
quad: leg/cpp/quad \
	leg/cpp/quad/vec \
	leg/cpp/quad/sched \
	leg/cpp/quad/omp \
	leg/c/quad \
	leg/c/quad/vec \
	leg/c/quad/sched \
	leg/c/quad/omp

.PHONY: fx
fx: leg/cpp/fx \
	leg/c/fx

.PHONY: fx1
fx1: leg/cpp/fx1 \
	leg/c/fx1

.PHONY: cpp1
cpp1: leg/cpp1/double/mem0 \
	leg/cpp1/double/mem1 \
	leg/cpp1/double/mem1fpgamemth0 \
	leg/cpp1/double/mem1fpgamemth2 \
	leg/cpp1/double/mem1fpgamemth8

.PHONY: cpp2
cpp2: leg/cpp2/double/ec \
	leg/cpp2/double/ecmem0 \
	leg/cpp2/double/ecmem1it \
	leg/cpp2/double/os \
	leg/cpp2/double/osec \
	leg/cpp2/double/osmem \
	leg/cpp2/double/osmem1 \
	leg/cpp2/double/osecmem \
	leg/cpp2/double/osecmem1it

.PHONY: cpp3
cpp3: leg/cpp3/double/vecec \
	leg/cpp3/double/vececmem0 \
	leg/cpp3/double/vececmem1it \
	leg/cpp3/double/vecfunecmem1it

.PHONY: cpp4
cpp4: leg/cpp4/double/mem2 \
	leg/cpp4/double/ecmem2 \
	leg/cpp4/double/fpga10mem2it \
	leg/cpp4/double/fpga100mem2it \
	leg/cpp4/double/fpga1000mem2it \
	leg/cpp4/double/fpga10000mem2it \
	leg/cpp4/double/ecfpga10mem2it \
	leg/cpp4/double/ecfpga100mem2it \
	leg/cpp4/double/ecfpga1000mem2it \
	leg/cpp4/double/ecfpga10000mem2it \
	leg/cpp4/double/vecmem2it \
	leg/cpp4/double/vececmem2it \
	leg/cpp4/double/veclv1ecmem2it \
	leg/cpp4/double/vecfunecmem2it \
	leg/cpp4/double/osmem2it \
	leg/cpp4/double/osecmem2it \
	leg/cpp4/double/osfpga10mem2it \
	leg/cpp4/double/osfpga100mem2it \
	leg/cpp4/double/ecosfpga10mem2it \
	leg/cpp4/double/ecosfpga100mem2it

.PHONY: ocpp
ocpp: leg/ocpp/double \
	leg/ocpp/double/mcd0 \
	leg/ocpp/double/vec/lv0 \
	leg/ocpp/double/vec/lv1

.PHONY: vecocpp
vecocpp: leg/ocpp/double/vec/lv1

.PHONY: me
me: leg/me/double

.PHONY: c
c: leg/c/double \
	leg/c/double/it \
	leg/c/double/lp \
	leg/c/double/dlt0 \
	leg/c/double/dlt256 \
	leg/c/double/vec/lv0 \
	leg/c/double/vec/lv0/fun \
	leg/c/double/vec/lv0/vs16 \
	leg/c/double/vec/lv1 \
	leg/c/double/vec/lv1/fun \
	leg/c/double/vec/lv1/vs16 \
	leg/c/double/sched \
	leg/c/double/sched/fun \
	leg/c/double/omp \
	leg/c/double/omp/fun \
	leg/c/float \
	leg/c/float/vec \
	leg/c/float/sched \
	leg/c/float/omp

.PHONY: c1
c1: leg/c1/double/ec \
	leg/c1/double/os \
	leg/c1/double/osec \
	leg/c1/double/mem2it \
	leg/c1/double/fpga10mem2it \
	leg/c1/double/fpga100mem2it \
	leg/c1/double/fpga1000mem2it \
	leg/c1/double/vecfpga100mem2it

.PHONY: c2
c2: leg/c2/double/ecos0mem2it \
	leg/c2/double/ecosfpga10mem2it \
	leg/c2/double/ecosfpga100mem2it \
	leg/c2/double/vececfpga100mem2it

#########################################################################
# automatic github action test
github_action:
	$(MAKE) -f Make.rust outdir=rust/it CARGOOPTIONS="" FAUSTOPTIONS="-I dsp -double -it -a archs/rust/architecture_trait_ff64.rs"
	$(MAKE) -f Make.rust outdir=rust/inpl CARGOOPTIONS="" FAUSTOPTIONS="-I ../../libraries/ -double -inpl -rnt -rnlm -a archs/rust/architecture_inpl.rs"
	$(MAKE) -f Make.rust outdir=rust/no CARGOOPTIONS="" FAUSTOPTIONS="-I ../../libraries/ -double -a archs/rust/architecture_trait_ff64.rs"
	$(MAKE) -f Make.gcc outdir=cpp/double lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I ../../libraries/ -I dsp -double"
	# NNX/Linen impulse tests need jax/flax, which the platform CI images do not
	# install; they are covered by the dedicated jax-tests workflow instead.

#########################################################################
# c++ and c backends

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
	export FAUST_OPT=FAUST_LLVM_NO_FM; \
	$(MAKE) -f Make.llvm outdir=llvm/double               FAUSTOPTIONS="-I dsp"
	$(MAKE) -f Make.llvm outdir=llvm/double/it            FAUSTOPTIONS="-I dsp -it"
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
	export FAUST_OPT=FAUST_LLVM_NO_FM; \
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
# signal interpreter
signal:
	$(MAKE) -f Make.signal outdir=signal/double              FAUSTOPTIONS="-I dsp"

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
	$(MAKE) -f Make.rust outdir=rust/it CARGOOPTIONS="" FAUSTOPTIONS="-I dsp -double -it -a archs/rust/architecture_trait_ff64.rs"
	$(MAKE) -f Make.rust outdir=rust/cm CARGOOPTIONS="" FAUSTOPTIONS="-I dsp -double -cm -a archs/rust/architecture_cm.rs"
	$(MAKE) -f Make.rust outdir=rust/3232 precision=1.4 CARGOOPTIONS="" FAUSTOPTIONS="-I dsp -single -rnlm -a archs/rust/architecture_trait_ff32.rs"
	$(MAKE) -f Make.rust outdir=rust/3264 precision=1 CARGOOPTIONS="" FAUSTOPTIONS="-I dsp -double -rnlm -a archs/rust/architecture_trait_ff32.rs"
	$(MAKE) -f Make.rust outdir=rust/6432 precision=24 CARGOOPTIONS="" FAUSTOPTIONS="-I dsp -single  -a archs/rust/architecture_trait_ff64.rs"
	$(MAKE) -f Make.rust outdir=rust/6464 CARGOOPTIONS="" FAUSTOPTIONS="-I dsp -double -a archs/rust/architecture_trait_ff64.rs"
	$(MAKE) -f Make.rust outdir=rust/inpl CARGOOPTIONS="" FAUSTOPTIONS="-I dsp -double -inpl -rnt -rnlm -a archs/rust/architecture_inpl.rs"
	$(MAKE) -f Make.rust outdir=rust/osec CARGOOPTIONS="" FAUSTOPTIONS="-I dsp -double -os -ec -rnt -rnlm -a archs/rust/architecture_osecrnt.rs"
	$(MAKE) -f Make.rust outdir=rust/os CARGOOPTIONS="" FAUSTOPTIONS="-I dsp -double -os -rnt -rnlm -a archs/rust/architecture_osrnt.rs"
	$(MAKE) -f Make.rust outdir=rust/ecrnt CARGOOPTIONS="" FAUSTOPTIONS="-I dsp -double -ec -rnt -rnlm -a archs/rust/architecture_ecrnt.rs"
	$(MAKE) -f Make.rust outdir=rust/fp FAUSTOPTIONS="-I dsp -double -fp -a archs/rust/architecture_trait_ff64.rs"
	$(MAKE) -f Make.rust outdir=rust/vec4 CARGOOPTIONS="" FAUSTOPTIONS="-I dsp -double -vec -vs 4 -a archs/rust/architecture_trait_ff64.rs"
	$(MAKE) -f Make.rust outdir=rust/vec32 FAUSTOPTIONS="-I dsp -double -vec -vs 32 -a archs/rust/architecture_trait_ff64.rs"

#########################################################################
# Cmajor backend
cmajor:
	$(MAKE) -f Make.cmajor outdir=cmajor      FAUSTOPTIONS=" -I dsp -double"
	$(MAKE) -f Make.cmajor outdir=cmajor/fp   FAUSTOPTIONS=" -I dsp -double -fp"
	$(MAKE) -f Make.cmajor outdir=cmajor/mapp FAUSTOPTIONS=" -I dsp -double -mapp"

#########################################################################
# RNBO backend
rnbo:
	$(MAKE) -f Make.rnbo outdir=rnbo      FAUSTOPTIONS=" -I dsp -double"

#########################################################################
# D backend
dlang:
	$(MAKE) -f Make.dlang outdir=dlang/double     FAUSTOPTIONS="-I dsp -double"
	$(MAKE) -f Make.dlang outdir=dlang/double/lp  FAUSTOPTIONS="-I dsp -double -fp"
	$(MAKE) -f Make.dlang outdir=dlang/double/vec FAUSTOPTIONS="-I dsp -double -vec"

#########################################################################
# NNX backend
nnx:
	$(MAKE) -f Make.nnx outdir=nnx/double FAUSTOPTIONS="-I dsp -double"

#########################################################################
# Linen backend
linen:
	$(MAKE) -f Make.linen outdir=linen/double FAUSTOPTIONS="-I dsp -double"

#########################################################################
# Julia backend
julia:
	$(MAKE) -f Make.julia outdir=julia/double FAUSTOPTIONS="-I dsp -double"

#########################################################################
# JSFX backend
jsfx:
	$(MAKE) -f Make.jsfx outdir=jsfx/double   FAUSTOPTIONS="-I dsp -double"

#########################################################################
# AssemblyScript backend (experimental smoke test)
assemblyscript:
	$(MAKE) -f Make.assemblyscript outdir=assemblyscript/double FAUSTOPTIONS="-I dsp -double"

#########################################################################
# output directories
ir/mute:
	mkdir -p ir/mute

#########################################################################
# building reference files
reference:
	$(MAKE) -f Make.ref

reference-box:
	cd reference && rm -f *.box
	 $(MAKE) -f Make.ref reference-box FAUSTOPTIONS="-I dsp"
	
reference-signal-wn:
	cd reference && rm -f *.sig
	export FAUST_OPT=FAUST_SIG_NO_NORM; $(MAKE) -f Make.ref reference-signal FAUSTOPTIONS="-I dsp"

reference-signal:
	cd reference && rm -f *.sig
	$(MAKE) -f Make.ref reference-signal FAUSTOPTIONS="-I dsp"

reference-type:
	cd reference && rm -f *.type
	$(MAKE) -f Make.ref reference-type FAUSTOPTIONS="-I dsp"
	
reference-fir:
	cd reference && rm -f *.fir
	$(MAKE) -f Make.ref reference-fir FAUSTOPTIONS="-I dsp"

reference-cpp:
	cd reference && rm -f *.cpp1
	$(MAKE) -f Make.ref reference-cpp FAUSTOPTIONS="-I dsp"

tools: filesCompare impulsellvm impulseinterp impulseinterp1 impulsesignal

clean:
	rm -f filesCompare impulsellvm impulseinterp impulseinterp1 impulsesignal

#########################################################################
# Testing Box, Signal, Type and C++ creation steps

test-box:
	cd dsp && ./box-script *.dsp

test-signal-wn:
	export FAUST_OPT=FAUST_SIG_NO_NORM; cd dsp && ./sig-script *.dsp
	
test-signal:
	cd dsp && ./sig-script *.dsp

test-type:
	 cd dsp && ./type-script *.dsp

test-fir:
	cd dsp && ./fir-script *.dsp

test-cpp:
	cd dsp && ./cpp-script *.dsp

#########################################################################
# Static analysis on generated C++ code

clang-tidy: clang-tidy-cpp
	@find ir/$(CLANG_TIDY_OUTDIR) -name '*.cpp' -type f -print -quit | grep -q . || (echo "No generated C++ in ir/$(CLANG_TIDY_OUTDIR)."; exit 1)
	@find ir/$(CLANG_TIDY_OUTDIR) -name '*.cpp' -type f -exec $(CLANG_TIDY) $(CLANG_TIDY_ARGS) -checks="$(CLANG_TIDY_CHECKS)" {} -- $(CLANG_TIDY_CXXFLAGS) \;

clang-tidy-cpp:
	$(MAKE) -f Make.gcc outdir=$(CLANG_TIDY_OUTDIR) lang=cpp arch=$(CLANG_TIDY_ARCH) FAUSTOPTIONS="$(CLANG_TIDY_FAUSTOPTIONS)" ir/$(CLANG_TIDY_OUTDIR) $(CLANG_TIDY_CPP_FILES)

#########################################################################
# Runtime sanitizer on generated C++ code

asan-cpp:
	$(MAKE) -f Make.gcc outdir=cpp/asan/double lang=cpp arch=impulsearch.cpp FAUSTOPTIONS="-I dsp -double" SAN=asan

#########################################################################
# Benchmark using faustbench-llvm and faustbench

bench:
	cd dsp && ./bench-script *.dsp

#########################################################################
# Using interp-tracer

interp-tracer:
	cd dsp && ./interp-tracer-script *.dsp

#########################################################################
# tools
filesCompare: $(SRCDIR)/filesCompare.cpp
	$(CXX) $(TOOLSOPTIONS) $(SRCDIR)/filesCompare.cpp -o filesCompare

impulseinterp: $(SRCDIR)/impulseinterp.cpp ./archs/controlTools.h $(LIB)
	$(CXX) $(TOOLSOPTIONS) -L/opt/local/lib -I/usr/local/include/ap_fixed -Iarchs $(SRCDIR)/impulseinterp.cpp $(LIB) $(LLVM_LIB) -o impulseinterp

impulseinterp1: $(SRCDIR)/impulseinterp1.cpp ./archs/controlTools.h $(LIB)
	$(CXX) $(TOOLSOPTIONS) -L/opt/local/lib -I/usr/local/include/ap_fixed -Iarchs $(SRCDIR)/impulseinterp1.cpp $(MACHINE_LIB) $(LLVM_LIB) -o impulseinterp1

# Target to use the Interp MIR backend
impulseinterp2: $(SRCDIR)/impulseinterp1.cpp ./archs/controlTools.h $(LIB)
	$(CXX) $(TOOLSOPTIONS) -L/opt/local/lib -I/usr/local/include/ap_fixed -Iarchs $(SRCDIR)/impulseinterp1.cpp $(MACHINE_LIB) /usr/local/lib/libmir.a -o impulseinterp1

impulsellvm: $(SRCDIR)/impulsellvm.cpp ./archs/controlTools.h $(LIB)
	$(CXX) $(TOOLSOPTIONS) -L/opt/local/lib -I/usr/local/include/ap_fixed -Iarchs $(SRCDIR)/impulsellvm.cpp $(LIB) $(LLVM_LIB) $(WINSOCK) -o impulsellvm

impulsesignal: $(SRCDIR)/impulsesignal.cpp ./archs/controlTools.h $(LIB)
	$(CXX) $(TOOLSOPTIONS) -L/opt/local/lib -I/usr/local/include/ap_fixed -Iarchs $(SRCDIR)/impulsesignal.cpp $(LIB) $(LLVM_LIB) $(WINSOCK) -o impulsesignal

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
