
LIB ?= /usr/local/lib
DESTDIR ?=
PREFIX ?= /usr/local

prefix := $(DESTDIR)$(PREFIX)

all: soul-faust-player

soul-faust-player: soul-faust-player.cpp 
	c++ -std=c++11 -O3 -I /usr/local/include  -I include -I `pkg-config --cflags --libs gtk+-2.0 jack` -framework CoreMIDI soul-faust-player.cpp $(LIB)/libfaust.a `llvm-config --ldflags --libs all --system-libs` -o soul-faust-player

install:
	cp soul-player $(prefix)/bin
	
clean:
	rm -f soul-faust-player
