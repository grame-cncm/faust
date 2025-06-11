LIB := $(shell faust --libdir)
LIB_OPT := /opt/local/lib
INC := $(shell faust --includedir)
system := $(shell uname -s)

DESTDIR ?=
PREFIX ?= /usr/local
LIB_OPT1 ?=

ifeq ($(system), Darwin)
LIB_OPT1=-framework CoreFoundation
INC_OPT=/opt/local/include
else ifeq ($(system), Linux)
LDFLAGS=-Wl,--export-dynamic
endif

MACOSLIBS := -framework CoreAudio -framework AudioUnit -framework CoreServices -framework CoreMIDI -framework CoreFoundation

LLVM := `llvm-config --link-static --ldflags --libs all --system-libs`

prefix := $(DESTDIR)$(PREFIX)

all: signal-test

signal-test: signal-test.cpp $(LIB)/libfaust.a
	c++ -O3 -std=c++11 signal-test.cpp $(LIB)/libfaust.a $(LLVM) -L$(LIB_OPT) `pkg-config --cflags --libs gtk+-2.0` `pkg-config --cflags` $(MACOSLIBS) -o signal-test

install: 
	([ -e signal-test ]) && cp signal-test $(prefix)/bin

clean:
	rm -f signal-test
	
help:
	@echo "Available targets:"
	@echo "  signal-test - test the Signal interpreter"
	@echo "  help         - Display this help message"
