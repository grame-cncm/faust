STRIP =

FAUST 	?= faust
LIB 	?= $(shell $(FAUST) -libdir)
INC 	:= $(shell $(FAUST) -includedir)
LIBS 	:= $(LIB)/libfaust.a
FASTMATH = $(shell $(FAUST) -includedir)/faust/dsp/fastmath.cpp
ifndef LLVM
LLVM	:= `llvm-config --ldflags --libs all --system-libs`
endif

ARCHS   ?=
# ARCHS   ?= -arch x86_64

LAME_LD_FLAGS ?= 

COMPILEOPT  := -std=c++11 -O3 -Wall
COMPILEOPT1 := -O3 -Wall
COMMLIBS	:= $(LIB)/libOSCFaust.a $(LIB)/libHTTPDFaust.a -lmicrohttpd -lpthread
MACOSLIBS	:= -framework CoreAudio -framework AudioUnit -framework CoreServices -framework CoreMIDI -framework CoreFoundation

DESTDIR ?=
PREFIX ?= /usr/local

prefix := $(DESTDIR)$(PREFIX)

TARGETS ?= dynamic-faust faustbench-llvm faustbench-llvm-interp faustbench-interp dynamic-jack-gtk interp-tracer faust-osc-controller signal-tester signal-tester-c box-tester box-tester-c
system := $(shell uname -s)
ifeq ($(system), Darwin)
	STRIP = -dead_strip
	TARGETS := $(TARGETS) dynamic-coreaudio-gtk poly-dynamic-jack-gtk dynamic-machine-jack-gtk 
endif

all: $(TARGETS)

faustbench-llvm: faustbench-llvm.cpp $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT) $(ARCHS) faustbench-llvm.cpp -L/opt/local/lib $(LIBS) -I $(INC) $(LLVM) $(STRIP) -lz -lncurses -lpthread -o $@

faustbench-llvm-interp: faustbench-llvm-interp.cpp $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT) $(ARCHS) faustbench-llvm-interp.cpp -L/opt/local/lib $(LIBS) -I $(INC) $(LLVM) $(STRIP) -lz -lncurses -lpthread -o $@

faustbench-interp: faustbench-interp.cpp $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT) $(ARCHS) faustbench-interp.cpp -L/opt/local/lib $(LIBS) -I $(INC)  $(LLVM) $(STRIP) -lz -lncurses -lpthread -o $@

faustbench-interp-comp: faustbench-interp-comp.cpp $(LIB)/libfaustmachine.a
	$(CXX) $(COMPILEOPT) $(ARCHS) faustbench-interp-comp.cpp $(LIB)/libfaustmachine.a /usr/local/lib/libmir.a -I $(INC) $(LLVM) $(STRIP) -lz -lncurses -lpthread -o $@

dynamic-faust: dynamic-faust.cpp $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT) $(ARCHS) dynamic-faust.cpp -L/opt/local/lib $(LIBS) -I $(INC) $(LLVM) $(STRIP) -lpthread -o $@

dynamic-jack-gtk: dynamic-jack-gtk.cpp $(LIB)/libfaust.a
	$(CXX) -DJACK $(COMPILEOPT) $(ARCHS) dynamic-jack-gtk.cpp -L/opt/local/lib $(LAME_LD_FLAGS) $(LIBS) -I $(INC) $(LLVM) `pkg-config --cflags --libs sndfile samplerate jack gtk+-3.0` $(STRIP) $(COMMLIBS) -o $@

dynamic-machine-jack-gtk: dynamic-machine-jack-gtk.cpp $(LIB)/libfaustmachine.a
	$(CXX) $(COMPILEOPT) $(ARCHS) dynamic-machine-jack-gtk.cpp -L/opt/local/lib $(LAME_LD_FLAGS) $(LIB)/libfaustmachine.a /usr/local/lib/libmir.a -I $(INC) $(LLVM) `pkg-config --cflags --libs sndfile samplerate jack gtk+-3.0` $(STRIP) $(COMMLIBS) -o $@

dynamic-coreaudio-gtk: dynamic-jack-gtk.cpp $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT) $(ARCHS) dynamic-jack-gtk.cpp -L/opt/local/lib $(LAME_LD_FLAGS) $(LIBS) -I $(INC) $(LLVM) `pkg-config --cflags --libs sndfile samplerate gtk+-3.0` $(STRIP) $(COMMLIBS) $(MACOSLIBS) -o $@

poly-dynamic-jack-gtk: poly-dynamic-jack-gtk.cpp $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT) $(ARCHS) poly-dynamic-jack-gtk.cpp -L/opt/local/lib $(LAME_LD_FLAGS) $(LIBS) -I $(INC) $(LLVM) `pkg-config --cflags --libs jack gtk+-3.0 sndfile samplerate` $(STRIP) -lz -lncurses -lpthread $(COMMLIBS) $(MACOSLIBS) -o $@

faust-osc-controller: faust-osc-controller.cpp
	$(CXX) $(COMPILEOPT) $(ARCHS) faust-osc-controller.cpp -I $(INC) `pkg-config --cflags --libs gtk+-3.0` $(STRIP) $(LIB)/libOSCFaust.a -llo -o $@

interp-tracer: interp-tracer.cpp $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT) $(ARCHS) interp-tracer.cpp $(LIBS) -I $(INC) $(LLVM) `pkg-config --cflags --libs gtk+-3.0` $(STRIP) -lz -lncurses -lpthread -o $@

signal-tester: signal-tester.cpp $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT) $(ARCHS) signal-tester.cpp -L/opt/local/lib $(LIBS) -I $(INC) $(LLVM) `pkg-config --cflags --libs jack gtk+-3.0` $(STRIP) -lz -lncurses -lpthread -o $@

signal-tester-c: signal-tester.c $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT1) $(ARCHS) signal-tester.c -L/opt/local/lib $(LIBS) -I $(INC) $(LLVM) $(STRIP) -lz -lncurses -lpthread -o signal-tester-c

box-tester: box-tester.cpp $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT) $(ARCHS) box-tester.cpp -L/opt/local/lib $(LIBS) -I $(INC) $(LLVM) `pkg-config --cflags --libs jack gtk+-3.0` $(STRIP) -lz -lncurses -lpthread -o $@

box-tester-c: box-tester.c $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT1) $(ARCHS) box-tester.c -L/opt/local/lib $(LIBS) -I $(INC) $(LLVM) $(STRIP) -lz -lncurses -lpthread -o box-tester-c

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
	cp -r iOS-bench $(shell $(FAUST) --archdir)

install-package:
	cp $(TARGETS) $(prefix)/bin
	cp faustbench.cpp $(prefix)/share/faust
	cp faustbench $(prefix)/bin
	cp faust2object $(prefix)/bin
	
clean:
	rm -f $(TARGETS)
	rm -f fastmath.bc fastmath.wasm layout-ui
