# 
# FAUST compiler makefile
#

# start to determine the current platform
TARGET := undefined
system	:= $(shell uname -s)
# normalizes MINGW versions
system := $(shell echo $(system) | grep MINGW > /dev/null && echo MINGW || echo $(system))
ifeq ($(system), Darwin)
	TARGET = macos
else
ifeq ($(system), MINGW)
	TARGET = windows
else
ifeq ($(system), Linux)
	TARGET = linux
endif
endif
endif


.PHONY: wasm asmjs faust macos windows linux

FAUSTDIR := faust
WASMDIR  := wasm
ASMJSDIR := asmjs
EMCC 	?= emcc
VERBOSE ?= OFF

faust:
	make $(TARGET)

help:
	@echo "-------- FAUST compiler makefile --------"
	@echo "Available targets are:"
	@echo " 'faust' (default): builds the FAUST compiler and the static FAUST library."
	@echo " 'wasm'     : builds the FAUST compiler as a Web Assembly library"
	@echo " 'asmjs'    : builds the FAUST compiler as a ASM JS library"
	@echo "Available options:"
	@echo "  VERBOSE=[ON | OFF(default)] : set or unset verbose mode for makefile based build"

#===============================================================
# building faust on mac os
# default is to use the unix makefile strategy
#===============================================================
macos:
	make linux

#===============================================================
# building faust on linux
#===============================================================
linux:
	@[ -d $(FAUSTDIR) ] || mkdir $(FAUSTDIR)
	cd $(FAUSTDIR) && cmake -C ../backends.cmake -DVERBOSE=$(VERBOSE) .. 
	make -C $(FAUSTDIR) -j 8

#===============================================================
# building faust on windows
# default is to build the 64bits architecture
#===============================================================
windows:
	@[ -d $(FAUSTDIR) ] || mkdir $(FAUSTDIR)
	cd $(FAUSTDIR) && cmake -C ../backends.cmake -DVERBOSE=$(VERBOSE) .. 
	make -C $(FAUSTDIR) -j 8
	
#===============================================================
# building faust with emscripten
#===============================================================
wasm:
	@make checkemcc
	@[ -d $(WASMDIR) ] || mkdir $(WASMDIR)
	cd $(WASMDIR) && cmake -C ../emcc.cmake -DWASM_BACKEND=ON -DLIBWASM=ON -DVERBOSE=$(VERBOSE) .. 
	make -C $(WASMDIR) -j 8

asmjs:
	@make checkemcc
	@[ -d $(ASMJSDIR) ] || mkdir $(ASMJSDIR)
	cd $(ASMJSDIR) && cmake -C ../emcc.cmake -DASMJS_BACKEND=ON -DLIBASMJS=ON -DVERBOSE=$(VERBOSE) .. 
	make -C $(ASMJSDIR) -j 8
	
checkemcc:
	@which $(EMCC) > /dev/null || (echo "### emcc must be available from your PATH."; false;)

undefined:
	$(error System is undefined, not target available)

