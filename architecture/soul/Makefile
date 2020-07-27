
LIB ?= /usr/local/lib
DESTDIR ?=
PREFIX ?= /usr/local

prefix := $(DESTDIR)$(PREFIX)

all: soul-faust-player soul-faust-tester

soul-faust-player: soul-faust-player.cpp 
	c++ -std=c++14 -O3 -I /usr/local/include  -I `pkg-config --cflags --libs gtk+-2.0 jack` -framework CoreMIDI soul-faust-player.cpp $(LIB)/libfaust.a `llvm-config --ldflags --libs all --system-libs` -o soul-faust-player

soul-faust-tester: soul-faust-tester.cpp 
	c++ -std=c++14 -O3 -I /usr/local/include  soul-faust-tester.cpp $(LIB)/libfaust.a `llvm-config --ldflags --libs all --system-libs` -o soul-faust-tester

install:
	([ -e soul-faust-player ]) && cp soul-faust-player  $(prefix)/bin || echo soul-faust-player not found
	([ -e soul-faust-tester ]) && cp soul-faust-tester  $(prefix)/bin || echo soul-faust-tester not found
	
clean:
	rm -f soul-faust-player soul-faust-tester
