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
	ifneq ($(GENERATOR), "MSYS Makefiles")
	ifeq ($(ARCH), Win32)
		GENERATOR = $(GENERATOR)
	else
		GENERATOR = $(GENERATOR) $(ARCH)
	endif
	endif
else
ifeq ($(system), Linux)
	TARGET = linux
	GENERATOR ?= "Unix Makefiles"
endif
endif
endif

CMAKEOPT ?= "-DCMAKE_BUILD_TYPE=Release"
ifdef LLVM_DIR
	CMAKEOPT += -DLLVM_DIR=\"$(LLVM_DIR)\"
endif


#===============================================================
# output directories
FAUSTDIR := faustdir
XCODEDIR := xcode
VS14DIR:= vs14
VS12DIR:= vs12
WASMDIR  := wasm
ASMJSDIR := asmjs

.PHONY: faust $(WASMDIR) $(ASMJSDIR) $(FAUSTDIR) $(XCODEDIR) $(VS14DIR) $(VS12DIR)

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
	
clean:
	rm -rf $(FAUSTDIR) faust faust.exe libfaust.* faust.dll faust.lib

#===============================================================
help:
	@echo "-------- FAUST compiler makefile --------"
	@echo "Available targets are:"
	@echo " 'faust' (default): builds the FAUST compiler and the FAUST libraries."
	@echo " 'wasm'     : builds the FAUST compiler as a Web Assembly library"
	@echo " 'asmjs'    : builds the FAUST compiler as a ASM JS library"
	@echo " 'clean'    : clean remove the output of the 'faust' target"
	@echo 
	@echo "Platform specific targets :"
	@echo " 'xcode'    : [Mac OS]  equivalent to the faust target but using xcode build"
	@echo " 'vs14'     : [Windows] equivalent to the faust target but using visual studio 14 build"
	@echo " 'vs12'     : [Windows] equivalent to the faust target but using visual studio 12 build"
	@echo 
	@echo "Available options:"
	@echo "  CMAKEOPT=<cmake options>    : pass options to cmake. Default to '-DCMAKE_BUILD_TYPE=Release'"
	@echo "  GENERATOR=<cmake generator> : set the cmake generator to use"
	@echo "                                Note that it may conflict with the 'make' command"
	@echo "  BACKENDS=<backends>         : see 'Backends' below"
	@echo "  LLVM_DIR=<dir>              : sets the llvm directory (may be used with LLVM backend)"
	@echo "  ARCH=[Win64 | ARM | Win32]  : [Windows] defaults to Win64"
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
	make _umake BACKENDS=$(BACKENDS) CMAKEOPT=$(CMAKEOPT) VERBOSE=$(VERBOSE) TASKS=$(TASKS)
	make _maccp DIR=$(FAUSTDIR)

xcode: CMAKEOPT ?= ""
xcode:
	@[ -d $(XCODEDIR) ] || mkdir $(XCODEDIR)
	cd $(XCODEDIR) && cmake -C ../$(BACKENDS) $(CMAKEOPT) .. -G Xcode
	xcodebuild -jobs $(TASKS) -project $(XCODEDIR)/faust.xcodeproj -target ALL_BUILD -configuration Release
	make _maccp DIR=$(XCODEDIR)/Release

_maccp:
	-[ -e $(DIR)/faust ] && cp $(DIR)/faust .
	-[ -e $(DIR)/libfaust.a ] && cp $(DIR)/libfaust.a .
	-[ -e $(DIR)/libfaust.dylib ] && cp $(DIR)/libfaust.dylib .


#===============================================================
# building faust on linux
#===============================================================
linux:
	make _umake BACKENDS=$(BACKENDS) CMAKEOPT=$(CMAKEOPT) VERBOSE=$(VERBOSE) TASKS=$(TASKS)
	-[ -e $(FAUSTDIR)/faust ] && cp $(FAUSTDIR)/faust .
	-[ -e $(FAUSTDIR)/libfaust.a ] && cp $(FAUSTDIR)/libfaust.a .
	-[ -e $(FAUSTDIR)/libfaust.so ] && cp $(FAUSTDIR)/libfaust.so* .

#===============================================================
# building faust on windows
# default is to build using MSYS makefiles
#===============================================================
windows:
	make _umake BACKENDS=$(BACKENDS) CMAKEOPT=$(CMAKEOPT) VERBOSE=$(VERBOSE) TASKS=$(TASKS)
	-cp $(FAUSTDIR)/faust.exe .
	-cp $(FAUSTDIR)/libfaust.dll $(FAUSTDIR)/libfaust.dll.a .
	-cp $(FAUSTDIR)/libfaust.a .

vs14:
	make _VS VSDIR=$(VS14DIR)$(ARCH) MSVC="C:\Program Files (x86)\Microsoft Visual Studio 14.0" GENERATOR="Visual Studio 14 2015" TASKS=$(TASKS)

vs12:
	make _VS VSDIR=$(VS12DIR)$(ARCH) MSVC="C:\Program Files (x86)\Microsoft Visual Studio 12.0" GENERATOR="Visual Studio 12 2013" TASKS=$(TASKS)

_VS:
	@[ -d $(VSDIR) ] || mkdir $(VSDIR)
	cd $(VSDIR) && cmake -C ../$(BACKENDS) $(CMAKEOPT) .. -G "$(GENERATOR)" 
	cmd /c "\"$(MSVC)\VC\vcvarsall.bat\" && msbuild $(VSDIR)/faust.sln /maxcpucount:$(TASKS) /p:Configuration=Release"

	
#===============================================================
# building using unix makefiles
#===============================================================
_umake:
	@[ -d $(FAUSTDIR) ] || mkdir $(FAUSTDIR)
	cd $(FAUSTDIR) && cmake -C ../$(BACKENDS) $(CMAKEOPT) -DCMAKE_VERBOSE_MAKEFILE=$(VERBOSE) .. -G $(GENERATOR)
	make -C $(FAUSTDIR) -j $(TASKS)


#===============================================================
# building faust with emscripten
#===============================================================
wasm: CMAKEOPT += -DWASM_BACKEND=ON -DLIBWASM=ON -DCMAKE_VERBOSE_MAKEFILE=$(VERBOSE)
wasm:
	@make checkemcc
	@[ -d $(WASMDIR) ] || mkdir $(WASMDIR)
	cd $(WASMDIR) && cmake -C ../emcc.cmake $(CMAKEOPT) .. 
	make -C $(WASMDIR) -j $(TASKS)
	cp $(WASMDIR)/libfaust-wasm.* .

asmjs: CMAKEOPT += -DASMJS_BACKEND=ON -DLIBASMJS=ON -DCMAKE_VERBOSE_MAKEFILE=$(VERBOSE)
asmjs:
	@make checkemcc
	@[ -d $(ASMJSDIR) ] || mkdir $(ASMJSDIR)
	cd $(ASMJSDIR) && cmake -C ../emcc.cmake $(CMAKEOPT) ..  
	make -C $(ASMJSDIR) -j $(TASKS)
	cp $(ASMJSDIR)/libfaust.js .
	
checkemcc:
	@which $(EMCC) > /dev/null || (echo "### emcc must be available from your PATH."; false;)

undefined:
	$(error System is undefined, not target available)

