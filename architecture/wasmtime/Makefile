LIB := $(shell faust --libdir)
LIB_OPT := /opt/local/lib
INC := $(shell faust --includedir)

DESTDIR ?=
PREFIX ?= /usr/local

LLVM := `llvm-config --link-static --ldflags --libs all --system-libs`

prefix := $(DESTDIR)$(PREFIX)

all: faustwasmtime faustbench-wasmtime

faustwasmtime: faustwasmtime.cpp $(LIB)/libfaust.a
	$(CXX) -std=c++11 -O3 faustwasmtime.cpp -I $(INC) -L$(LIB) -L$(LIB_OPT) $(LIB)/libfaust.a $(LIB)/libwasmtime.a $(LIB)/libHTTPDFaust.a  $(LLVM) `pkg-config --cflags --libs jack libmicrohttpd` -o faustwasmtime

faustbench-wasmtime: faustbench-wasmtime.cpp $(LIB)/libfaust.a
	$(CXX) -std=c++11 -O3 faustbench-wasmtime.cpp -I $(INC) -L$(LIB) -L$(LIB_OPT) $(LIB)/libfaust.a $(LIB)/libwasmtime.a $(LLVM) -o faustbench-wasmtime
	
install: 
	([ -e faustwasmtime ]) && cp faustwasmtime $(prefix)/bin
	([ -e faustbench-wasmtime ]) && cp faustbench-wasmtime $(prefix)/bin

clean:
	rm -f faustwasmtime faustbench-wasmtime
	
