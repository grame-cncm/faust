STRIP =

FAUST 	?= faust
LIB 	?= $(shell $(FAUST) -libdir)
INC 	:= $(shell $(FAUST) -includedir)
LIBS 	:= $(LIB)/libfaust.a
FASTMATH = $(shell $(FAUST) -includedir)/faust/dsp/fastmath.cpp
LLVM	:= `llvm-config --ldflags --libs all --system-libs`
COMPILEOPT  := -std=c++11 -O3
COMMLIBS	:= $(LIB)/libOSCFaust.a $(LIB)/libHTTPDFaust.a  -lmicrohttpd
MACOSLIBS	:= -framework CoreAudio -framework AudioUnit -framework CoreServices -framework CoreMIDI -framework CoreFoundation

DESTDIR ?=
PREFIX ?= /usr/local

prefix := $(DESTDIR)$(PREFIX)

TARGETS ?= dynamic-faust faustbench-llvm faustbench-llvm-interp faustbench-interp dynamic-jack-gtk dynamic-machine-jack-gtk interp-tracer fastmath faust-osc-controller
system := $(shell uname -s)
ifeq ($(system), Darwin)
	STRIP = -dead_strip
	TARGETS := $(TARGETS) dynamic-coreaudio-gtk poly-dynamic-jack-gtk
endif

all: $(TARGETS)

faustbench-llvm: faustbench-llvm.cpp $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT) faustbench-llvm.cpp $(LIBS) -I $(INC) $(LLVM) $(STRIP) -lz -lncurses -lpthread -o $@

faustbench-llvm-interp: faustbench-llvm-interp.cpp $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT) faustbench-llvm-interp.cpp  $(LIBS) -I $(INC)  $(LLVM) $(STRIP) -lz -lncurses -lpthread -o f$@

faustbench-interp: faustbench-interp.cpp $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT) faustbench-interp.cpp  $(LIBS) -I $(INC)  $(LLVM) $(STRIP) -lz -lncurses -lpthread -o $@

faustbench-interp-comp: faustbench-interp-comp.cpp $(LIB)/libfaustmachine.a
	$(CXX) $(COMPILEOPT) faustbench-interp-comp.cpp $(LIB)/libfaustmachine.a mir.o mir-gen.o -I $(INC)  $(LLVM) $(STRIP) -lz -lncurses -lpthread -o $@

dynamic-faust: dynamic-faust.cpp $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT) dynamic-faust.cpp $(LIBS) -I $(INC)  $(LLVM) $(STRIP) -o $@

dynamic-jack-gtk: dynamic-jack-gtk.cpp $(LIB)/libfaust.a
	$(CXX) -DJACK $(COMPILEOPT) dynamic-jack-gtk.cpp  $(LIBS) -I $(INC)  $(LLVM) `pkg-config --cflags --libs sndfile samplerate jack gtk+-2.0` $(STRIP) $(COMMLIBS) -o $@

dynamic-machine-jack-gtk: dynamic-machine-jack-gtk.cpp $(LIB)/libfaustmachine.a
	$(CXX) $(COMPILEOPT) dynamic-machine-jack-gtk.cpp $(LIB)/libfaustmachine.a -I $(INC)  $(LLVM) `pkg-config --cflags --libs jack gtk+-2.0` $(STRIP) $(COMMLIBS) -o $@

dynamic-coreaudio-gtk: dynamic-jack-gtk.cpp $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT) dynamic-jack-gtk.cpp  $(LIBS) -I $(INC)  $(LLVM) `pkg-config --cflags --libs sndfile samplerate gtk+-2.0` $(STRIP) $(COMMLIBS) $(MACOSLIBS) -o $@

poly-dynamic-jack-gtk: poly-dynamic-jack-gtk.cpp $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT) poly-dynamic-jack-gtk.cpp $(LIBS) -I $(INC)  $(LLVM) `pkg-config --cflags --libs jack gtk+-2.0 sndfile samplerate` $(STRIP) -lz -lncurses -lpthread $(COMMLIBS) $(MACOSLIBS) -o $@

faust-osc-controller: faust-osc-controller.cpp
	$(CXX) $(COMPILEOPT) faust-osc-controller.cpp -I $(INC) `pkg-config --cflags --libs gtk+-2.0` $(STRIP) $(LIB)/libOSCFaust.a -llo -o $@

interp-tracer: interp-tracer.cpp $(LIB)/libfaust.a
	$(CXX) $(COMPILEOPT) interp-tracer.cpp $(LIBS) -I $(INC)  $(LLVM) `pkg-config --cflags --libs gtk+-2.0` $(STRIP) -lz -lncurses -lpthread -o $@

layout-ui: layout-ui.cpp
	$(CXX) $(COMPILEOPT) layout-ui.cpp -I $(INC) $(LIBS)  $(LLVM) -o $@

fastmath: $(FASTMATH)
	clang++ -Ofast -emit-llvm -S $(FASTMATH) -o fastmath.ll
	clang++ -Ofast -emit-llvm -c $(FASTMATH) -o fastmath.bc

emcc: $(FASTMATH)
	emcc -O3 -s WASM=1 -s SIDE_MODULE=1 -s LEGALIZE_JS_FFI=0 $(FASTMATH) -o fastmath.wasm
	wasm-dis fastmath.wasm -o fastmath.wast

install:
	cp $(TARGETS) $(prefix)/bin

#	cp faust2object $(prefix)/bin
#	cp faustbench-wasm $(prefix)/bin
#	cp faust2benchwasm $(prefix)/bin
	cp wasm-node-bench.js wasm-bench.js wasm-bench-emcc.js wasm-bench-jsmem.js $(prefix)/share/faust/webaudio
	cp faustbench.cpp $(prefix)/share/faust
#	cp faustbench $(prefix)/bin
#	cp faust-tester $(prefix)/bin
# 	([ -e dynamic-jack-gtk ]) && cp dynamic-jack-gtk $(prefix)/bin || echo dynamic-jack-gtk not found
# 	([ -e dynamic-coreaudio-gtk ]) && cp dynamic-coreaudio-gtk $(prefix)/bin || echo dynamic-coreaudio-gtk not found
# 	([ -e dynamic-faust ]) && cp dynamic-faust $(prefix)/bin || echo dynamic-faust not found
# 	([ -e dynamic-machine-jack-gtk ]) && cp dynamic-machine-jack-gtk $(prefix)/bin || echo dynamic-machine-jack-gtk not found
# 	([ -e poly-dynamic-jack-gtk ]) && cp poly-dynamic-jack-gtk $(prefix)/bin || echo poly-dynamic-jack-gtk not found
# 	([ -e interp-tracer ]) && cp interp-tracer $(prefix)/bin || echo interp-tracer not found
# 	([ -e faustbench-llvm ]) && cp faustbench-llvm $(prefix)/bin || echo faustbench-llvm not found
# 	([ -e faustbench-llvm-interp ]) && cp faustbench-llvm-interp $(prefix)/bin || echo faustbench-llvm-interp not found
# 	([ -e faustbench-interp ]) && cp faustbench-interp $(prefix)/bin || echo faustbench-interp not found
# 	([ -e faustbench-interp-comp ]) && cp faustbench-interp-comp $(prefix)/bin || echo faustbench-interp-comp not found
# 	([ -e fastmath.bc ]) && cp fastmath.bc $(prefix)/share/faust || echo fastmath.bc not found
# 	([ -e fastmath.wasm ]) && cp fastmath.wasm $(prefix)/share/faust || echo fastmath.wasm not found
# 	([ -e faust-osc-controller ]) && cp faust-osc-controller $(prefix)/bin || echo faust-osc-controller not found
# 	([ -e layout-ui ]) && cp layout-ui $(prefix)/bin || echo layout-ui not found
	cp -r iOS-bench $(shell $(FAUST) --archdir)

clean:
	rm -f $(TARGETS)
	rm -f fastmath.bc fastmath.wasm layout-ui
