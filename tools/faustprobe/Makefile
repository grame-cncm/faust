# faustprobe needs libfaust with the LLVM backend, as a static library that
# already holds LLVM: libfaustwithllvm.a,
# installed by 'make install' of a build with the LLVM backend (see build/README.md).

DESTDIR   ?=
PREFIX    ?= /usr/local
prefix    := $(DESTDIR)$(PREFIX)

FAUST     ?= faust
INCDIR    ?= $(shell $(FAUST) -includedir)
LIBDIR    ?= $(shell $(FAUST) -libdir)
LIBFAUST  ?= $(LIBDIR)/libfaustwithllvm.a
CXX       ?= c++
CXXFLAGS  ?= -O2
LLVMCONFIG ?= llvm-config
SYSTEMLIBS ?= $(shell $(LLVMCONFIG) --link-static --system-libs 2>/dev/null)
LIBPATHS  ?= $(shell $(LLVMCONFIG) --ldflags 2>/dev/null) -L/opt/local/lib -L/opt/homebrew/lib

system := $(shell uname -s)
ifeq ($(system), Darwin)
DEADSTRIP := -Wl,-dead_strip
else
DEADSTRIP := -Wl,--gc-sections
endif

SOURCES := faustprobe.cpp analysis.cpp audio.cpp cli.cpp engine.cpp eval.cpp json.cpp mode_freqresp.cpp \
           mode_poly.cpp mode_render.cpp mode_svg.cpp mode_train.cpp poly.cpp report.cpp text.cpp train.cpp
OBJECTS := $(SOURCES:%.cpp=build/%.o)

all: faustprobe

faustprobe: $(OBJECTS) $(LIBFAUST)
	$(CXX) $(OBJECTS) $(LIBFAUST) $(LDFLAGS) $(LIBPATHS) $(SYSTEMLIBS) -lz -lncurses -lpthread $(DEADSTRIP) -o $@

build/%.o: %.cpp $(wildcard *.h)
	@mkdir -p build
	$(CXX) -std=c++17 $(CXXFLAGS) -Wall -I$(INCDIR) -c $< -o $@

UNITSOURCES := tests/unit.cpp analysis.cpp audio.cpp json.cpp text.cpp

tests/unit: $(UNITSOURCES) $(wildcard *.h)
	$(CXX) -std=c++17 $(CXXFLAGS) -Wall $(UNITSOURCES) -o $@

test: faustprobe tests/unit
	@mkdir -p tests/out
	cd tests && ./unit
	./tests/run.sh

# 'make benchmark' at the root links faustprobe with the library of the build
# tree: rebuilding it here would link it with the installed one.
install:
	@test -x faustprobe || (echo "faustprobe is not built: run 'make benchmark' at the root, or 'make' here"; false)
	install -d $(prefix)/bin
	install -m 755 faustprobe $(prefix)/bin

uninstall:
	rm -f $(prefix)/bin/faustprobe

clean:
	rm -rf build faustprobe tests/unit tests/out

.PHONY: all test install uninstall clean
