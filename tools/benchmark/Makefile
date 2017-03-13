# Directory containing Faust .lib and .cpp architecture files:
ck1 := /opt/local/share/faust/music.lib
ck2 := /usr/local/share/faust/music.lib
ck3 := $(FAUST_LIB_PATH)/faust/music.lib
LIB := $(if $(wildcard $(ck1)),/opt/local/lib,"")
LIB := $(if $(wildcard $(ck2)),/usr/local/lib,$(LIB))
LIB := $(if $(wildcard $(ck3)),$(FAUST_LIB_PATH),$(LIB))

all: faustbench-llvm faustbench-llvm-interp dynamic-jack-gtk

faustbench-llvm: 
	c++ -O3 faustbench-llvm.cpp $(LIB)/libfaust.a  `llvm-config --ldflags --libs all --system-libs` -lz -lncurses -lcrypto -o faustbench-llvm

faustbench-llvm-interp: faustbench-llvm-interp.cpp
	$(CXX) -O3 faustbench-llvm-interp.cpp $(LIB)/libfaust.a  `llvm-config --ldflags --libs all --system-libs` `pkg-config --cflags --libs jack gtk+-2.0` -lz -lncurses -lcrypto -o faustbench-llvm-interp

dynamic-jack-gtk: dynamic-jack-gtk.cpp
	$(CXX) -g dynamic-jack-gtk.cpp $(LIB)/libfaust.a  `llvm-config --ldflags --libs all --system-libs` `pkg-config --cflags --libs jack gtk+-2.0` -lz -lncurses -lcrypto -o dynamic-jack-gtk


install:

	([ -e dynamic-jack-gtk ]) && cp dynamic-jack-gtk  /usr/local//bin || echo dynamic-jack-gtk  not found
	([ -e faustbench-llvm ]) && cp faustbench-llvm /usr/local/bin || echo faustbench-llvm not found
	([ -e faustbench-llvm-interp ]) && cp faustbench-llvm-interp /usr/local/bin || echo faustbench-llvm-interp not found


clean:

	([ -e dynamic-jack-gtk ]) && rm dynamic-jack-gtk || echo dynamic-jack-gtk  not found
	([ -e faustbench-llvm ]) && rm faustbench-llvm || echo faustbench-llvm not found
	([ -e faustbench-llvm-interp ]) && rm faustbench-llvm-interp || echo faustbench-llvm-interp not found

