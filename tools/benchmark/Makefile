STRIP =

FAUST 	?= faust
system := $(shell uname -s)

ifeq ($(system), Darwin)
# We can't execute an arm64 faust executable on a GitHub x86 runner,
# so we may some strong assumptions about where the include/libs are.
FAUSTDIR ?= ../../build
LIB 	?= $(FAUSTDIR)/lib
INC 	:= $(FAUSTDIR)/include
FARCH 	:= $(FAUSTDIR)/share/faust
else
LIB 	?= $(shell $(FAUST) -libdir)
INC 	:= $(shell $(FAUST) -includedir)
FARCH 	:= $(shell $(FAUST) -archdir)
endif
FASTMATH = $(INC)/faust/dsp/fastmath.cpp
LIBS 	:= $(LIB)/libfaust.a
LIB_FLAGS := /opt/local/lib
ifndef LLVM
LLVM	:= `llvm-config --link-static --ldflags --libs all --system-libs`
endif

ARCHS   ?=
# ARCHS   ?= -arch x86_64

USE_STATIC_SNDFILE ?= 0

ifeq ($(USE_STATIC_SNDFILE),1)
	LAME_PRIMARY_PREFIX ?= /usr/local/Cellar/lame
	LAME_BACKUP_PREFIX ?= /opt/homebrew/Cellar/lame
	LAME_STATIC_LIBS ?= $(shell find $(LAME_PRIMARY_PREFIX) -name libmp3lame.a 2>/dev/null || find $(LAME_BACKUP_PREFIX) -name libmp3lame.a 2>/dev/null)
	SNDFILE_STATIC_LIBS = $(shell pkg-config --libs sndfile | sed -n 's/^-L\([^ ]*\).*$$/\1/p')/libsndfile.a
	FLAC_STATIC_LIBS = $(shell pkg-config --libs flac | sed -n 's/^-L\([^ ]*\).*$$/\1/p')/libflac.a
	OGG_STATIC_LIBS = $(shell pkg-config --libs ogg | sed -n 's/^-L\([^ ]*\).*$$/\1/p')/libogg.a
	VORBIS_STATIC_LIBS = $(shell pkg-config --libs vorbis | sed -n 's/^-L\([^ ]*\).*$$/\1/p')/libvorbis.a
	VORBISFILE_STATIC_LIBS = $(shell pkg-config --libs vorbis | sed -n 's/^-L\([^ ]*\).*$$/\1/p')/libvorbisfile.a
	VORBISENC_STATIC_LIBS = $(shell pkg-config --libs vorbis | sed -n 's/^-L\([^ ]*\).*$$/\1/p')/libvorbisenc.a
	MPG123_STATIC_LIBS = $(shell pkg-config --libs libmpg123 | sed -n 's/^-L\([^ ]*\).*$$/\1/p')/libmpg123.a
	OPUS_STATIC_LIBS = $(shell pkg-config --libs opus | sed -n 's/^-L\([^ ]*\).*$$/\1/p')/libopus.a

	SNDFILE_LIBS = $(SNDFILE_STATIC_LIBS) $(FLAC_STATIC_LIBS) $(OGG_STATIC_LIBS) $(VORBIS_STATIC_LIBS) $(VORBISFILE_STATIC_LIBS) $(VORBISENC_STATIC_LIBS) $(MPG123_STATIC_LIBS) $(OPUS_STATIC_LIBS) $(LAME_STATIC_LIBS)
else
	SNDFILE_LIBS ?= `pkg-config --cflags --libs sndfile`
endif

COMPILEOPT  := -std=c++11 -O3 -Wall -no-pie
COMPILEOPT1 := -O3 -Wall -no-pie
COMMLIBS	:= $(LIB)/libOSCFaust.a $(LIB)/libHTTPDFaust.a -lpthread $(shell pkg-config --libs libmicrohttpd)
MACOSLIBS	:= -framework CoreAudio -framework AudioUnit -framework CoreServices -framework CoreMIDI -framework CoreFoundation

DESTDIR ?=
PREFIX ?= /usr/local

prefix := $(DESTDIR)$(PREFIX)

TARGETS ?= dynamic-faust faustbench-llvm faustbench-llvm-interp faustbench-interp dynamic-jack-gtk interp-tracer faust-osc-controller signal-tester signal-tester-c box-tester box-tester-c
ifeq ($(system), Darwin)
	STRIP = -dead_strip
	TARGETS := $(TARGETS) dynamic-coreaudio-gtk poly-dynamic-jack-gtk 
endif

all: $(TARGETS)

faustbench-llvm: faustbench-llvm.cpp $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT) $(ARCHS) faustbench-llvm.cpp -L $(LIB_FLAGS) $(LIBS) -I $(INC) $(LLVM) $(STRIP) -lz -lncurses -lpthread -o $@

faustbench-llvm-interp: faustbench-llvm-interp.cpp $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT) $(ARCHS) faustbench-llvm-interp.cpp -L $(LIB_FLAGS) $(LIBS) -I $(INC) $(LLVM) $(STRIP) -lz -lncurses -lpthread -o $@

faustbench-interp: faustbench-interp.cpp $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT) $(ARCHS) faustbench-interp.cpp -L $(LIB_FLAGS) $(LIBS) -I $(INC)  $(LLVM) $(STRIP) -lz -lncurses -lpthread -o $@

faustbench-interp-comp: faustbench-interp-comp.cpp $(LIB)/libfaustmachine.a
	$(CXX) $(COMPILEOPT) $(ARCHS) faustbench-interp-comp.cpp $(LIB)/libfaustmachine.a -I $(INC) $(LLVM) $(STRIP) -lz -lncurses -lpthread -o $@

dynamic-faust: dynamic-faust.cpp $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT) $(ARCHS) dynamic-faust.cpp -L $(LIB_FLAGS) $(LIBS) -I $(INC) $(LLVM) $(STRIP) -lpthread -o $@

dynamic-jack-gtk: dynamic-jack-gtk.cpp $(LIB)/libfaust.a
	$(CXX) -DJACK $(COMPILEOPT) $(ARCHS) dynamic-jack-gtk.cpp -L $(LIB_FLAGS) $(SNDFILE_LIBS) $(LIBS) -I $(INC) $(LLVM) `pkg-config --cflags --libs samplerate jack gtk+-2.0` `pkg-config --cflags sndfile` $(STRIP) $(COMMLIBS) -o $@

dynamic-machine-jack-gtk: dynamic-machine-jack-gtk.cpp $(LIB)/libfaustmachine.a
	$(CXX) $(COMPILEOPT) $(ARCHS) dynamic-machine-jack-gtk.cpp -L $(LIB_FLAGS) $(SNDFILE_LIBS) $(LIB)/libfaustmachine.a -I $(INC) $(LLVM) `pkg-config --cflags --libs samplerate jack gtk+-2.0` `pkg-config --cflags sndfile` $(STRIP) $(COMMLIBS) -o $@

dynamic-coreaudio-gtk: dynamic-jack-gtk.cpp $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT) $(ARCHS) dynamic-jack-gtk.cpp -L $(LIB_FLAGS) $(SNDFILE_LIBS) $(LIBS) -I $(INC) $(LLVM) `pkg-config --cflags --libs samplerate gtk+-2.0` `pkg-config --cflags sndfile` $(STRIP) $(COMMLIBS) $(MACOSLIBS) -o $@

poly-dynamic-jack-gtk: poly-dynamic-jack-gtk.cpp $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT) $(ARCHS) poly-dynamic-jack-gtk.cpp -L $(LIB_FLAGS) $(SNDFILE_LIBS) $(LIBS) -I $(INC) $(LLVM) `pkg-config --cflags --libs jack gtk+-2.0 samplerate` `pkg-config --cflags sndfile` $(STRIP) -lz -lncurses -lpthread $(COMMLIBS) $(MACOSLIBS) -o $@

faust-osc-controller: faust-osc-controller.cpp
	$(CXX) $(COMPILEOPT) $(ARCHS) faust-osc-controller.cpp -I $(INC) `pkg-config --cflags --libs gtk+-2.0 liblo` $(STRIP) $(LIB)/libOSCFaust.a -llo -o $@

interp-tracer: interp-tracer.cpp $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT) $(ARCHS) interp-tracer.cpp -L $(LIB_FLAGS) $(LIBS) -I $(INC) $(LLVM) $(STRIP) -lz -lncurses -lpthread -o $@

signal-tester: signal-tester.cpp $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT) $(ARCHS) signal-tester.cpp -L $(LIB_FLAGS) $(LIBS) -I $(INC) $(LLVM) `pkg-config --cflags --libs jack gtk+-2.0` $(STRIP) -lz -lncurses -lpthread -o $@

signal-tester-c: signal-tester.c $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT1) $(ARCHS) signal-tester.c -L $(LIB_FLAGS) $(LIBS) -I $(INC) $(LLVM) $(STRIP) -lz -lncurses -lpthread -o signal-tester-c

box-tester: box-tester.cpp $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT) $(ARCHS) box-tester.cpp -L $(LIB_FLAGS) $(LIBS) -I $(INC) $(LLVM) `pkg-config --cflags --libs jack gtk+-2.0` $(STRIP) -lz -lncurses -lpthread -o $@

box-tester-c: box-tester.c $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT1) $(ARCHS) box-tester.c -L $(LIB_FLAGS) $(LIBS) -I $(INC) $(LLVM) $(STRIP) -lz -lncurses -lpthread -o box-tester-c

layout-ui: layout-ui.cpp
	$(CXX) $(COMPILEOPT) $(ARCHS) layout-ui.cpp -I $(INC) $(LIBS) $(LLVM) -o $@

fastmath: $(FASTMATH)
	clang++ -Ofast -emit-llvm -S $(FASTMATH) -o fastmath.ll
	clang++ -Ofast -emit-llvm -c $(FASTMATH) -o fastmath.bc

emcc: $(FASTMATH)
	emcc -O3 -s WASM=1 -s SIDE_MODULE=1 -s LEGALIZE_JS_FFI=0 $(FASTMATH) -o fastmath.wasm
	wasm-dis fastmath.wasm -o fastmath.wast

install:
	cp $(TARGETS) $(prefix)/bin
	cp wasm-node-bench.js wasm-bench.js wasm-bench-emcc.js wasm-bench-jsmem.js $(prefix)/share/faust/webaudio
	cp faustbench.cpp $(prefix)/share/faust
	cp faustbench $(prefix)/bin
	cp faust2object $(prefix)/bin
	cp faustbench-wasm $(prefix)/bin
	cp faust2benchwasm $(prefix)/bin
	cp faust-tester $(prefix)/bin
	cp -r iOS-bench $(prefix)/share/faust

install-package:
	cp $(TARGETS) $(prefix)/bin
	cp faustbench.cpp $(prefix)/share/faust
	cp faustbench $(prefix)/bin
	cp faust2object $(prefix)/bin
	
clean:
	rm -f $(TARGETS)
	rm -f fastmath.bc fastmath.wasm layout-ui
