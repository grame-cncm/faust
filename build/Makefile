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
	GENERATOR ?= "Unix Makefiles"
else
ifeq ($(system), MINGW)
	TARGET = windows
	GENERATOR ?= "MSYS Makefiles"
	ARCH ?= Win64
else
ifeq ($(system), Linux)
	TARGET = linux
	GENERATOR ?= "Unix Makefiles"
endif
endif
endif


.PHONY: wasm asmjs faust xcode vs12 vs14

#===============================================================
# output directories
FAUSTDIR := faust
XCODEDIR := xcode
VS14DIR:= vs14
VS12DIR:= vs12

WASMDIR  := wasm
ASMJSDIR := asmjs

#===============================================================
# options
VERBOSE ?= OFF
TASKS	?= 4
BACKENDS?= backends.cmake

EMCC 	?= emcc


#===============================================================
# main target
faust:
	make $(TARGET)

#===============================================================
help:
	@echo "-------- FAUST compiler makefile --------"
	@echo "Available targets are:"
	@echo " 'faust' (default): builds the FAUST compiler and the static FAUST library."
	@echo " 'wasm'     : builds the FAUST compiler as a Web Assembly library"
	@echo " 'asmjs'    : builds the FAUST compiler as a ASM JS library"
	@echo 
	@echo "Platform specific targets :"
	@echo " 'xcode'    : [Mac OS] equivalent to the faust target but using xcode build"
	@echo " 'vs14'     : [Windows] equivalent to the faust target but using visual studio 14 build"
	@echo " 'vs12'     : [Windows] equivalent to the faust target but using visual studio 12 build"
	@echo 
	@echo "Available options:"
	@echo "  GENERATOR=<cmake generator> : set the cmake generator to use"
	@echo "                                Note that it may conflict with the 'make' command"
	@echo "  BACKENDS=<backends>         : see 'Backends' below"
	@echo "  VERBOSE=[ON | OFF(default)] : set or unset verbose mode for makefile based build"
	@echo "  TASKS=[1-n] : set the number of tasks to run in parallel (default is $(TASKS))"
	@echo 
	@echo "Backends:"
	@echo "  the FAUST backends included by default are described in the '$(BACKENDS)' file"
	@echo "  you can freely customize this file or use another file with the BACKENDS option"

#===============================================================
# building faust on mac os
# default is to use the unix makefile strategy
#===============================================================
macos:
	make linux

xcode:
	@[ -d $(XCODEDIR) ] || mkdir $(XCODEDIR)
	cd $(XCODEDIR) && cmake -C ../$(BACKENDS) .. -G Xcode
	xcodebuild -jobs $(TASKS) -project $(XCODEDIR)/faust.xcodeproj -target ALL_BUILD -configuration Release

#===============================================================
# building faust on linux
#===============================================================
linux:
	@[ -d $(FAUSTDIR) ] || mkdir $(FAUSTDIR)
	cd $(FAUSTDIR) && cmake -C ../$(BACKENDS) -DVERBOSE=$(VERBOSE) .. -G $(GENERATOR)
	make -C $(FAUSTDIR) -j $(TASKS)

#===============================================================
# building faust on windows
# default is to build using MSYS makefiles
#===============================================================
windows:
	make linux

vs14:
	make _VS VSDIR=$(VS14DIR) MSVC="C:\Program Files (x86)\Microsoft Visual Studio 14.0" GENERATOR="Visual Studio 14 2015 $(ARCH)" TASKS=$(TASKS)

vs12:
	make _VS VSDIR=$(VS12DIR) MSVC="C:\Program Files (x86)\Microsoft Visual Studio 12.0" GENERATOR="Visual Studio 12 2013 $(ARCH)" TASKS=$(TASKS)

_VS:
	@[ -d $(VSDIR) ] || mkdir $(VSDIR)
	cd $(VSDIR) && cmake -C ../$(BACKENDS) .. -G $(GENERATOR) 
	cmd /c "\"$(MSVC)\VC\vcvarsall.bat\" && msbuild $(VSDIR)/faust.sln /maxcpucount:$(TASKS) /p:Configuration=Release"

	
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

