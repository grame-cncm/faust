LIB ?= ../../build/lib
INC = ../../architecture

DESTDIR ?=
PREFIX ?= /usr/local

prefix := $(DESTDIR)$(PREFIX)

all: llvm-test 

llvm-test: llvm-test.cpp $(LIB)/libfaust.a
	$(CXX) -std=c++11 -O3 llvm-test.cpp -I $(INC) $(LIB)/libfaust.a  `llvm-config --ldflags --libs all --system-libs` -dead_strip -o llvm-test

install:
 
	([ -e llvm-test ]) && cp llvm-test $(prefix)/bin

clean:

	([ -e llvm-test ]) && rm llvm-test|| echo llvm-test not found
	