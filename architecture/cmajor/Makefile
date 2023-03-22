
FAUST ?= faust
LIB ?= $(shell $(FAUST) -libdir)
LIB_OPT ?= /opt/local/lib
INC = /usr/local/include
DESTDIR ?=
PREFIX ?= /usr/local
MACOSLIBS := -framework CoreAudio -framework AudioUnit -framework CoreServices -framework CoreMIDI -framework CoreFoundation

prefix := $(DESTDIR)$(PREFIX)

all: cmajor-faust-player cmajor-faust-tester cmajor-faust-editor

cmajor-faust-player: cmajor-faust-player.cpp 
	c++ cmajor-faust-player.cpp -std=c++17 -O3 -I$(INC) -L$(LIB_OPT) $(MACOSLIBS) $(LIB)/libfaust.a -I /opt/local/include/gtk-2.0 -I `pkg-config --cflags --libs samplerate gtk+-2.0 jack` `llvm-config --ldflags --libs all --system-libs` -o cmajor-faust-player

cmajor-faust-tester: cmajor-faust-tester.cpp 
	c++ cmajor-faust-tester.cpp -std=c++17 -O3 -I$(INC) -L$(LIB_OPT) $(LIB)/libfaust.a `llvm-config --ldflags --libs all --system-libs` -o cmajor-faust-tester

cmajor-faust-editor: cmajor-faust-editor.cpp cmajor-tools.h
	c++ cmajor-faust-editor.cpp -std=c++17 -O3 -I$(INC) -L$(LIB_OPT) $(LIB)/libfaust.a libefsw-static-release.a $(MACOSLIBS) `llvm-config --ldflags --libs all --system-libs` -o cmajor-faust-editor

install:
	([ -e cmajor-faust-player ]) && cp cmajor-faust-player  $(prefix)/bin || echo cmajor-faust-player not found
	([ -e cmajor-faust-tester ]) && cp cmajor-faust-tester  $(prefix)/bin || echo cmajor-faust-tester not found
	([ -e cmajor-faust-editor ]) && cp cmajor-faust-editor  $(prefix)/bin || echo cmajor-faust-editor not found
	
clean:
	rm -f cmajor-faust-player cmajor-faust-tester cmajor-faust-editor
