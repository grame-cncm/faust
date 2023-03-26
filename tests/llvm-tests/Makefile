LIB := $(shell faust --libdir)
LIB_OPT := /opt/local/lib
INC := $(shell faust --includedir)

DESTDIR ?=
PREFIX ?= /usr/local

prefix := $(DESTDIR)$(PREFIX)

all: llvm-test llvm-algebra-test llvm-test-c

llvm-test: llvm-test.cpp $(LIB)/libfaust.a
	$(CXX) -std=c++11 -O3 llvm-test.cpp -I$(INC) -L$(LIB) -L$(LIB_OPT) $(LIB)/libfaust.a -lpthread `llvm-config --ldflags --libs all --system-libs` -o llvm-test

# To test the LLVM backend with dynamic libfaust on Apple M1 and Rosetta
llvm-test-x86: llvm-test.cpp 
	$(CXX) -arch x86_64 -std=c++11 -O3 llvm-test.cpp -I$(INC) -L$(LIB) -L$(LIB_OPT) -lfaust -lpthread -DJIT_TARGET="\"x86_64-apple-darwin\"" -o llvm-test

# To test the LLVM backend with dynamic libfaust on Apple M1
llvm-test-arm: llvm-test.cpp 
	$(CXX) -std=c++11 -O3 llvm-test.cpp -I$(INC) -L$(LIB) -L$(LIB_OPT) -lfaust -lpthread  -o llvm-test

llvm-test-c: llvm-test.c $(LIB)/libfaust.a
	$(CXX) llvm-test.c -O3 -I $(INC) -L$(LIB_OPT) $(LIB)/libfaust.a -lpthread `llvm-config --ldflags --libs all --system-libs` -o llvm-test-c

llvm-algebra-test: llvm-algebra-test.cpp $(LIB)/libfaust.a
	$(CXX) -std=c++11 -O3 llvm-algebra-test.cpp -I$(INC) -L$(LIB) -L$(LIB_OPT) $(LIB)/libfaust.a -lpthread `llvm-config --ldflags --libs all --system-libs` `pkg-config --cflags --libs gtk+-2.0` -o llvm-algebra-test

install: 
	([ -e llvm-test ]) && cp llvm-test $(prefix)/bin

test: llvm-test
	./llvm-test foo.dsp
	
test-c: llvm-test-c
	./llvm-test-c foo.dsp

clean:
	rm -f llvm-test llvm-test-c llvm-algebra-test
	
