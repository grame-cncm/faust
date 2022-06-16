LIB := $(shell faust --libdir)
INC := $(shell faust --includedir)

DESTDIR ?=
PREFIX ?= /usr/local

prefix := $(DESTDIR)$(PREFIX)

all: interp-test interp-test-c interp-machine-test

interp-test: interp-test.cpp $(LIB)/libfaust.a
	$(CXX) -std=c++11 -O3 interp-test.cpp -I $(INC) $(LIB)/libfaust.a `llvm-config --ldflags --libs all --system-libs` -o interp-test

interp-test-c: interp-test.c $(LIB)/libfaust.a
	$(CXX) -O3 interp-test.c -I $(INC) $(LIB)/libfaust.a `llvm-config --ldflags --libs all --system-libs` -o interp-test-c

interp-machine-test: interp-machine-test.cpp $(LIB)/libfaustmachine.a foo.fbc
	$(CXX) -std=c++11 -O3 interp-machine-test.cpp -I $(INC) $(LIB)/libfaustmachine.a -o interp-machine-test

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
	
