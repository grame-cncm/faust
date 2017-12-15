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

.PHONY: tests

OPTIONS := -std=c++11 -O3 -I.
LIB    ?= ../../build/lib/libfaust.a
SRCDIR := tools

all: filesCompare impulseinterp impulsellvm tests

tests:
	sh test.sh -float
	sh test.sh -cpp
	sh test.sh -c 
	sh test.sh -llvm 
	sh test.sh -interp 
	sh test.sh -ajs 
	sh test.sh -ajs-e 
	sh test.sh -lf-ajs 
	sh testwithmute.sh


#########################################################################
# tools
filesCompare: $(SRCDIR)/filesCompare.cpp
	$(CXX) $(OPTIONS) $(SRCDIR)/filesCompare.cpp -o filesCompare

impulseinterp: $(SRCDIR)/impulsearch3.cpp ../../build/lib/libfaust.a
	$(CXX) $(OPTIONS) $(SRCDIR)/impulsearch3.cpp $(LIB) `llvm-config --ldflags --libs all --system-libs` -o impulseinterp

impulsellvm: $(SRCDIR)/impulsearch4.cpp ../../build/lib/libfaust.a
	$(CXX) $(OPTIONS) $(SRCDIR)/impulsearch4.cpp $(LIB) `llvm-config --ldflags --libs all --system-libs` -o impulsellvm