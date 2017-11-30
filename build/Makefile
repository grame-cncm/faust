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
TASKS	?= 4


faust:
	make $(TARGET)

#===============================================================
help:
	@echo "-------- FAUST compiler makefile --------"
	@echo "Available targets are:"
	@echo " 'faust' (default): builds the FAUST compiler and the static FAUST library."
	@echo " 'wasm'     : builds the FAUST compiler as a Web Assembly library"
	@echo " 'asmjs'    : builds the FAUST compiler as a ASM JS library"
	@echo "Available options:"
	@echo "  VERBOSE=[ON | OFF(default)] : set or unset verbose mode for makefile based build"
	@echo "  TASKS=[1-n] : set the number of tasks to run in parallel (default is $(TASKS))"

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
	cd $(FAUSTDIR) && cmake -C ../backends.cmake -DVERBOSE=$(VERBOSE) .. -G "Unix Makefiles"
	make -C $(FAUSTDIR) -j $(TASKS)

#===============================================================
# building faust on windows
# default is to build using MSYS
#===============================================================
windows:
	@[ -d $(FAUSTDIR) ] || mkdir $(FAUSTDIR)
	cd $(FAUSTDIR) && cmake -C ../backends.cmake -DVERBOSE=$(VERBOSE) .. -G "MSYS Makefiles"
	make -C $(FAUSTDIR) -j $(TASKS)
	
#===============================================================
# building faust with emscripten
#===============================================================
wasm:
	@make checkemcc
	@[ -d $(WASMDIR) ] || mkdir $(WASMDIR)
	cd $(WASMDIR) && cmake -C ../emcc.cmake -DWASM_BACKEND=ON -DLIBWASM=ON -DVERBOSE=$(VERBOSE) .. 
	make -C $(WASMDIR) -j $(TASKS)

asmjs:
	@make checkemcc
	@[ -d $(ASMJSDIR) ] || mkdir $(ASMJSDIR)
	cd $(ASMJSDIR) && cmake -C ../emcc.cmake -DASMJS_BACKEND=ON -DLIBASMJS=ON -DVERBOSE=$(VERBOSE) .. 
	make -C $(ASMJSDIR) -j $(TASKS)
	
checkemcc:
	@which $(EMCC) > /dev/null || (echo "### emcc must be available from your PATH."; false;)

undefined:
	$(error System is undefined, not target available)

