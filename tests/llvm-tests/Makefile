LIB ?= ../../build/lib
INC = ../../architecture

DESTDIR ?=
PREFIX ?= /usr/local

prefix := $(DESTDIR)$(PREFIX)

all: llvm-test 

llvm-test: llvm-test.cpp $(LIB)/libfaust.a
	$(CXX) -std=c++11 -O3 llvm-test.cpp -I $(INC) $(LIB)/libfaust.a  -lpthread `llvm-config --ldflags --libs all --system-libs` -o llvm-test

install: 
	([ -e llvm-test ]) && cp llvm-test $(prefix)/bin

clean:
	rm -f llvm-test
	
