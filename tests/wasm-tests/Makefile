LIB := $(shell faust --libdir)
LIB_OPT := /opt/local/lib
INC := $(shell faust --includedir)

DESTDIR ?=
PREFIX ?= /usr/local

LLVM := `llvm-config --link-static --ldflags --libs all --system-libs`

prefix := $(DESTDIR)$(PREFIX)

all: wasm-test wasm-test-c wasm-machine-test

wasm-test: wasm-test.cpp $(LIB)/libfaust.a
	$(CXX) -std=c++11 -O3 wasm-test.cpp -I $(INC) -L$(LIB) -L$(LIB_OPT) $(LIB)/libfaust.a $(LIB)/libwasmtime.a $(LLVM) -o wasm-test

# To test the wasm/MIR backend with static libfaust
wasm-test1: wasm-test.cpp $(LIB)/libfaust.a
	$(CXX) -std=c++11 -O3 wasm-test.cpp -I $(INC) -L$(LIB_OPT) $(LIB)/libfaust.a $(LIB)/libmir.a -o wasm-test1

# To test the wasm/MIR backend with dynamic libfaust
wasm-test2: wasm-test.cpp
	$(CXX) -std=c++11 -O3 wasm-test.cpp -I $(INC) -L$(LIB) -lfaust -o wasm-test2

wasm-test-c: wasm-test.c $(LIB)/libfaust.a
	$(CXX) -O3 wasm-test.c -I $(INC) -L$(LIB) -L$(LIB_OPT) $(LIB)/libfaust.a $(LLVM) -o wasm-test-c

wasm-machine-test: wasm-machine-test.cpp $(LIB)/libfaustmachine.a foo.wasm
	$(CXX) -std=c++11 -O3 wasm-machine-test.cpp -I $(INC) -L$(LIB_OPT) $(LIB)/libfaustmachine.a -o wasm-machine-test

foo.wasm:
	faust -lang wasm foo.dsp -o foo.wasm
	
install: 
	([ -e wasm-test ]) && cp wasm-test $(prefix)/bin
	([ -e wasm-machine-test ]) && cp wasm-machine-test $(prefix)/bin

test: wasm-test wasm-machine-test
	./wasm-test foo.dsp
	./wasm-machine-test foo.wasm

clean:
	rm -f wasm-test wasm-test-c wasm-machine-test foo.wasm
	
