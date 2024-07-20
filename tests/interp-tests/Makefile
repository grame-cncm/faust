LIB := $(shell faust --libdir)
LIB_OPT := /opt/local/lib
INC := $(shell faust --includedir)

DESTDIR ?=
PREFIX ?= /usr/local

LLVM := `llvm-config --link-static --ldflags --libs all --system-libs`

prefix := $(DESTDIR)$(PREFIX)

all: interp-test interp-test-c interp-machine-test

interp-test: interp-test.cpp $(LIB)/libfaust.a
	$(CXX) -std=c++11 -O3 interp-test.cpp -I $(INC) -L$(LIB) -L$(LIB_OPT) $(LIB)/libfaust.a $(LLVM) -o interp-test

# To test the Interp/MIR backend with static libfaust
interp-test1: interp-test.cpp $(LIB)/libfaust.a
	$(CXX) -std=c++11 -O3 interp-test.cpp -I $(INC) -L$(LIB_OPT) $(LIB)/libfaust.a $(LIB)/libmir.a -o interp-test1

# To test the Interp/MIR backend with dynamic libfaust
interp-test2: interp-test.cpp
	$(CXX) -std=c++11 -O3 interp-test.cpp -I $(INC) -L$(LIB) -lfaust -o interp-test2

interp-test-c: interp-test.c $(LIB)/libfaust.a
	$(CXX) -O3 interp-test.c -I $(INC) -L$(LIB) -L$(LIB_OPT) $(LIB)/libfaust.a $(LLVM) -o interp-test-c

interp-machine-test: interp-machine-test.cpp $(LIB)/libfaustmachine.a foo.fbc
	$(CXX) -std=c++11 -O3 interp-machine-test.cpp -I $(INC) -L$(LIB_OPT) $(LIB)/libfaustmachine.a -o interp-machine-test

foo.fbc:
	faust -lang interp foo.dsp -o foo.fbc
	
install: 
	([ -e interp-test ]) && cp interp-test $(prefix)/bin
	([ -e interp-machine-test ]) && cp interp-machine-test $(prefix)/bin

test: interp-test interp-machine-test
	./interp-test foo.dsp
	./interp-machine-test foo.fbc

clean:
	rm -f interp-test interp-test-c interp-machine-test foo.fbc
	
