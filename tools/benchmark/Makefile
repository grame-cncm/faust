LIB := ../../compiler
FASTMATH = ../../architecture/faust/dsp/fastmath.cpp
#FASTMATH = ../../architecture/faust/dsp/fastmath-light.cpp

DESTDIR ?=
PREFIX ?= /usr/local

prefix := $(DESTDIR)$(PREFIX)

all: faustbench-llvm faustbench-llvm-interp dynamic-jack-gtk interp-tracer fastmath

faustbench-llvm: faustbench-llvm.cpp
	$(CXX) -std=c++11 -O3 faustbench-llvm.cpp $(LIB)/libfaust.a  `llvm-config --ldflags --libs all --system-libs` -lz -lncurses -lpthread -o faustbench-llvm

faustbench-llvm-interp: faustbench-llvm-interp.cpp
	$(CXX) -std=c++11 -O3 faustbench-llvm-interp.cpp $(LIB)/libfaust.a  `llvm-config --ldflags --libs all --system-libs` `pkg-config --cflags --libs jack gtk+-2.0` -lz -lncurses -lpthread -o faustbench-llvm-interp

dynamic-jack-gtk: dynamic-jack-gtk.cpp
	$(CXX) -std=c++11 -O3 dynamic-jack-gtk.cpp $(LIB)/libfaust.a  `llvm-config --ldflags --libs all --system-libs` `pkg-config --cflags --libs jack gtk+-2.0` -lz -lncurses -lpthread -lOSCFaust -lHTTPDFaust -lmicrohttpd -o dynamic-jack-gtk

dynamic-jack-gtk-plugin: dynamic-jack-gtk.cpp
	$(CXX) -std=c++11 -O3 dynamic-jack-gtk.cpp -DINTERP_PLUGIN $(LIB)/libfaustplugin.a  `llvm-config --ldflags --libs all --system-libs` `pkg-config --cflags --libs jack gtk+-2.0` -lz -lncurses -lpthread -o dynamic-jack-gtk-plugin

interp-tracer: interp-tracer.cpp
	$(CXX) -std=c++11 -O3 interp-tracer.cpp $(LIB)/libfaust.a `llvm-config --ldflags --libs all --system-libs` `pkg-config --cflags --libs gtk+-2.0` -lz -lncurses -lpthread -o interp-tracer

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
	([ -e dynamic-jack-gtk ]) && cp dynamic-jack-gtk $(prefix)/bin || echo dynamic-jack-gtk not found
	([ -e interp-tracer ]) && cp interp-tracer $(prefix)/bin || echo interp-tracer not found
	([ -e dynamic-jack-gtk-plugin ]) && cp dynamic-jack-gtk-plugin  $(prefix)/bin || echo dynamic-jack-gtk-plugin not found
	([ -e faustbench-llvm ]) && cp faustbench-llvm $(prefix)/bin || echo faustbench-llvm not found
	([ -e faustbench-llvm-interp ]) && cp faustbench-llvm-interp $(prefix)/bin || echo faustbench-llvm-interp not found
	([ -e fastmath.bc ]) && cp fastmath.bc $(prefix)/share/faust || echo fastmath.bc not found
	([ -e fastmath.wasm ]) && cp fastmath.wasm $(prefix)/share/faust || echo fastmath.wasm not found

clean:

	([ -e dynamic-jack-gtk-plugin ]) && rm dynamic-jack-gtk-plugin || echo dynamic-jack-gtk-plugin not found
	([ -e dynamic-jack-gtk ]) && rm dynamic-jack-gtk || echo dynamic-jack-gtk not found
	([ -e interp-tracer ]) && rm interp-tracer || echo interp-tracer not found
	([ -e faustbench-llvm ]) && rm faustbench-llvm || echo faustbench-llvm not found
	([ -e faustbench-llvm-interp ]) && rm faustbench-llvm-interp || echo faustbench-llvm-interp not found
	([ -e fastmath.bc ]) && rm fastmath.bc || echo fastmath.bc not found

