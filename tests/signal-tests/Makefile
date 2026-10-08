FAUST ?= faust
PYTHON ?= python3
LIB ?= $(shell $(FAUST) --libdir)
LIB_OPT := /opt/local/lib
INC ?= $(shell $(FAUST) --includedir)
system := $(shell uname -s)

ifeq ($(system), Darwin)
SHARED_LIBFAUST ?= $(LIB)/libfaust.dylib
else
SHARED_LIBFAUST ?= $(LIB)/libfaust.so
endif

.PHONY: all clean clean-api help api-info check-shared-api check-signal-api check-box-api
.SECONDARY: signal-api-references.inc box-api-references.inc

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

# Link directly to the shared library so a static archive cannot hide missing exports.
signal-api-test box-api-test: %-api-test: %-api-test.cpp %-api-references.inc $(SHARED_LIBFAUST) Makefile | api-info
	$(CXX) $(CXXFLAGS) -std=c++11 -I"$(INC)" $< "$(SHARED_LIBFAUST)" -Wl,-rpath,"$(abspath $(LIB))" $(LDFLAGS) -o $@

%-api-references.inc: $(INC)/faust/dsp/libfaust-%.h generate-api-references.py
	$(PYTHON) generate-api-references.py $< $@

api-info:
	$(FAUST) --version
	$(CXX) --version
	uname -sm
	@echo "Shared library under test: $(SHARED_LIBFAUST)"
	@echo "Public headers under test: $(INC)"

check-signal-api: signal-api-test
	./signal-api-test

check-box-api: box-api-test
	./box-api-test

check-shared-api: check-signal-api check-box-api

install: 
	([ -e signal-test ]) && cp signal-test $(prefix)/bin

clean-api:
	rm -f signal-api-test box-api-test signal-api-references.inc box-api-references.inc

clean: clean-api
	rm -f signal-test
	
help:
	@echo "Available targets:"
	@echo "  signal-test - test the Signal interpreter"
	@echo "  check-shared-api - check all public C++ Signal and Box API links against shared libfaust"
	@echo "  check-signal-api / check-box-api - check one public API"
	@echo "  clean-api - remove API test executables and generated references"
	@echo "  help         - Display this help message"
