#LIB := ../../compiler
LIB ?= ../../build/lib
INC = ../../architecture
INC1 = ../../compiler/generator/interpreter/
FASTMATH = ../../architecture/faust/dsp/fastmath.cpp
#FASTMATH = ../../architecture/faust/dsp/fastmath-light.cpp

DESTDIR ?=
PREFIX ?= /usr/local

prefix := $(DESTDIR)$(PREFIX)

all: dynamic-faust faustbench-llvm faustbench-llvm-interp faustbench-interp dynamic-jack-gtk dynamic-machine-jack-gtk poly-dynamic-jack-gtk interp-tracer fastmath faust-osc-controller

faustbench-llvm: faustbench-llvm.cpp $(LIB)/libfaust.a
	$(CXX) -std=c++11 -O3 faustbench-llvm.cpp -I $(INC) $(LIB)/libfaust.a `llvm-config --ldflags --libs all --system-libs` -dead_strip -lz -lncurses -lpthread -o faustbench-llvm

faustbench-llvm-interp: faustbench-llvm-interp.cpp $(LIB)/libfaust.a
	$(CXX) -std=c++11 -O3 faustbench-llvm-interp.cpp -I $(INC) $(LIB)/libfaust.a `llvm-config --ldflags --libs all --system-libs` -dead_strip -lz -lncurses -lpthread -o faustbench-llvm-interp

faustbench-interp: faustbench-interp.cpp $(LIB)/libfaust.a
	$(CXX) -std=c++11 -O3 faustbench-interp.cpp -I $(INC) $(LIB)/libfaust.a `llvm-config --ldflags --libs all --system-libs` -dead_strip -lz -lncurses -lpthread -o faustbench-interp

dynamic-faust: dynamic-faust.cpp $(LIB)/libfaust.a
	$(CXX) -std=c++11 -O3 dynamic-faust.cpp -I $(INC) $(LIB)/libfaust.a `llvm-config --ldflags --libs all --system-libs` -dead_strip -o dynamic-faust

dynamic-jack-gtk: dynamic-jack-gtk.cpp $(LIB)/libfaust.a
	$(CXX) -std=c++11 -O3 dynamic-jack-gtk.cpp -I $(INC) $(LIB)/libfaust.a  `llvm-config --ldflags --libs all --system-libs` `pkg-config --cflags --libs jack sndfile samplerate gtk+-2.0` -dead_strip -lOSCFaust -lHTTPDFaust -lmicrohttpd -o dynamic-jack-gtk

dynamic-machine-jack-gtk: dynamic-machine-jack-gtk.cpp $(LIB)/libfaustmachine.a
	$(CXX) -std=c++11 -O3 dynamic-machine-jack-gtk.cpp -I $(INC1) $(LIB)/libfaustmachine.a `llvm-config --ldflags --libs all --system-libs` `pkg-config --cflags --libs jack gtk+-2.0` -dead_strip -lOSCFaust -lHTTPDFaust -lmicrohttpd -o dynamic-machine-jack-gtk

poly-dynamic-jack-gtk: poly-dynamic-jack-gtk.cpp
	$(CXX) -std=c++11 -O3 poly-dynamic-jack-gtk.cpp -I $(INC) $(LIB)/libfaust.a `llvm-config --ldflags --libs all --system-libs` `pkg-config --cflags --libs jack gtk+-2.0 sndfile samplerate` -dead_strip -lz -lncurses -lpthread -lOSCFaust -lHTTPDFaust -lmicrohttpd -framework CoreAudio -framework AudioUnit -framework CoreServices -framework CoreMIDI -framework CoreFoundation -o poly-dynamic-jack-gtk

faust-osc-controller: faust-osc-controller.cpp
	$(CXX) -std=c++11 -O3 faust-osc-controller.cpp -I $(INC) `pkg-config --cflags --libs gtk+-2.0` -dead_strip -lOSCFaust -llo -o faust-osc-controller

interp-tracer: interp-tracer.cpp $(LIB)/libfaust.a
	$(CXX) -std=c++11 -O3 interp-tracer.cpp -I $(INC) $(LIB)/libfaust.a `llvm-config --ldflags --libs all --system-libs` `pkg-config --cflags --libs gtk+-2.0` -dead_strip -lz -lncurses -lpthread -o interp-tracer

fastmath: $(FASTMATH)
	clang++ -Ofast -emit-llvm -S $(FASTMATH) -o fastmath.ll
	clang++ -Ofast -emit-llvm -c $(FASTMATH) -o fastmath.bc

emcc: $(FASTMATH)
	emcc -O3 -s WASM=1 -s SIDE_MODULE=1 -s LEGALIZE_JS_FFI=0 $(FASTMATH) -o fastmath.wasm
	wasm-dis fastmath.wasm -o fastmath.wast

install:

	cp faustbench-wasm $(prefix)/bin
	cp faust2benchwasm $(prefix)/bin
	cp wasm-node-bench.js wasm-bench.js wasm-bench-emcc.js wasm-bench-jsmem.js $(prefix)/share/faust/webaudio
	cp faustbench.cpp $(prefix)/share/faust
	cp faustbench $(prefix)/bin
	cp faust-tester $(prefix)/bin
	([ -e dynamic-jack-gtk ]) && cp dynamic-jack-gtk $(prefix)/bin || echo dynamic-jack-gtk not found
	([ -e dynamic-faust ]) && cp dynamic-faust $(prefix)/bin || echo dynamic-faust not found
	([ -e dynamic-machine-jack-gtk ]) && cp dynamic-machine-jack-gtk $(prefix)/bin || echo dynamic-machine-jack-gtk not found
	([ -e poly-dynamic-jack-gtk ]) && cp poly-dynamic-jack-gtk $(prefix)/bin || echo poly-dynamic-jack-gtk not found
	([ -e interp-tracer ]) && cp interp-tracer $(prefix)/bin || echo interp-tracer not found
	([ -e faustbench-llvm ]) && cp faustbench-llvm $(prefix)/bin || echo faustbench-llvm not found
	([ -e faustbench-llvm-interp ]) && cp faustbench-llvm-interp $(prefix)/bin || echo faustbench-llvm-interp not found
	([ -e faustbench-interp ]) && cp faustbench-interp $(prefix)/bin || echo faustbench-interp not found
	([ -e fastmath.bc ]) && cp fastmath.bc $(prefix)/share/faust || echo fastmath.bc not found
	([ -e fastmath.wasm ]) && cp fastmath.wasm $(prefix)/share/faust || echo fastmath.wasm not found
	([ -e faust-osc-controller ]) && cp faust-osc-controller $(prefix)/bin || echo faust-osc-controller not found

clean:

	([ -e dynamic-jack-gtk ]) && rm dynamic-jack-gtk || echo dynamic-jack-gtk not found
	([ -e dynamic-faust ]) && rm dynamic-faust || echo dynamic-faust not found
	([ -e dynamic-machine-jack-gtk ]) && rm dynamic-machine-jack-gtk || echo dynamic-machine-jack-gtk not found
	([ -e poly-dynamic-jack-gtk ]) && rm poly-dynamic-jack-gtk || echo poly-dynamic-jack-gtk not found
	([ -e interp-tracer ]) && rm interp-tracer || echo interp-tracer not found
	([ -e dynamic-jack-gtk-plugin ]) && rm dynamic-jack-gtk-plugi || echo dynamic-jack-gtk-plugi not found
	([ -e faustbench-llvm ]) && rm faustbench-llvm || echo faustbench-llvm not found
	([ -e faustbench-llvm-interp ]) && rm faustbench-llvm-interp || echo faustbench-llvm-interp not found
	([ -e faustbench-interp ]) && rm faustbench-interp || echo faustbench-interp not found
	([ -e fastmath.bc ]) && rm fastmath.bc || echo fastmath.bc not found
	([ -e fastmath.wasm ]) && rm fastmath.wasm || echo fastmath.wasm not found
	([ -e faust-osc-controller ]) && rm faust-osc-controller || echo faust-osc-controller not found
