LIB := ../../compiler

all: faustbench-llvm faustbench-llvm-interp dynamic-jack-gtk

faustbench-llvm: faustbench-llvm.cpp
	$(CXX) -O3 faustbench-llvm.cpp $(LIB)/libfaust.a  `llvm-config --ldflags --libs all --system-libs` -lz -lncurses -lcrypto -o faustbench-llvm

faustbench-llvm-interp: faustbench-llvm-interp.cpp
	$(CXX) -O3 faustbench-llvm-interp.cpp $(LIB)/libfaust.a  `llvm-config --ldflags --libs all --system-libs` `pkg-config --cflags --libs jack gtk+-2.0` -lz -lncurses -lcrypto -o faustbench-llvm-interp

dynamic-jack-gtk: dynamic-jack-gtk.cpp
	$(CXX) -O3 dynamic-jack-gtk.cpp $(LIB)/libfaust.a  `llvm-config --ldflags --libs all --system-libs` `pkg-config --cflags --libs jack gtk+-2.0` -lz -lncurses -lcrypto -o dynamic-jack-gtk


install:

	([ -e dynamic-jack-gtk ]) && cp dynamic-jack-gtk  /usr/local/bin || echo dynamic-jack-gtk  not found
	([ -e faustbench-llvm ]) && cp faustbench-llvm /usr/local/bin || echo faustbench-llvm not found
	([ -e faustbench-llvm-interp ]) && cp faustbench-llvm-interp /usr/local/bin || echo faustbench-llvm-interp not found

clean:

	([ -e dynamic-jack-gtk ]) && rm dynamic-jack-gtk || echo dynamic-jack-gtk  not found
	([ -e faustbench-llvm ]) && rm faustbench-llvm || echo faustbench-llvm not found
	([ -e faustbench-llvm-interp ]) && rm faustbench-llvm-interp || echo faustbench-llvm-interp not found

