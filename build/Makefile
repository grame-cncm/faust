#
# FAUST compiler makefile
#

ARCHS ?= 
LLVM ?= 

LLVM_PACKAGE_VERSION ?= 
LLVM_DIR ?= 
LLVM_LIB_DIR ?= 
LLVM_INCLUDE_DIRS ?= 
LLVM_LIBS ?= 
LLVM_DEFINITIONS ?= 
LLVM_LD_FLAGS ?= 
INCLUDE_LLVM ?= OFF
USE_LLVM_CONFIG ?= ON

BUILD_HTTP_STATIC ?= OFF
USE_STATIC_SNDFILE ?= 0
MAXSDK ?= $(shell echo $(PWD)/../max-sdk-base/c74support)

# start to determine the current platform
system := $(shell uname -s)
# normalizes MINGW versions
system := $(shell echo $(system) | grep MINGW > /dev/null && echo MINGW || echo $(system))

#===============================================================
# output directories
FAUSTDIR ?= faustdir
IOSDIR   := iosdir
VERSION := 2.76.0

#===============================================================
# current generator and backends
CACHE  = $(FAUSTDIR)/CMakeCache.txt
BCACHE = $(FAUSTDIR)/backends.txt
TCACHE = $(FAUSTDIR)/targets.txt
LCACHE = $(FAUSTDIR)/libsdir.txt
ifeq ($(system), MINGW)
	GENERATOR ?= $(shell [ -f $(CACHE) ] && (grep CMAKE_GENERATOR:INTERNAL $(CACHE) | cut -d= -f2) || echo MSYS Makefiles)
	NATIVEPACK = winpack
else
	PREFIX ?= /usr/local
	GENERATOR ?= $(shell [ -f $(CACHE) ] && (grep CMAKE_GENERATOR:INTERNAL $(CACHE) | cut -d= -f2) || echo Unix Makefiles)
endif
DESTDIR ?=

ifeq ($(system), MINGW)
	NATIVEPACK = winpack
else ifeq ($(system), Darwin)
	NATIVEPACK = macpack
else
	NATIVEPACK = linuxpack
endif
DESTDIR ?=


.PHONY: faust install uninstall osc http package wasmglue cmake

MAKE ?= make
CMAKE ?= $(shell which cmake)

WORKLET ?= no
WORKLETOPT = "-DWORKLET=off"
ifeq ($(WORKLET), on)
WORKLETOPT = "-DWORKLET=on"
endif

CMAKEOPT ?= -DCMAKE_BUILD_TYPE=Release $(WORKLETOPT)
BUILDOPT ?= --config Release

#CMAKEOPT ?= -DCMAKE_BUILD_TYPE=Debug $(WORKLETOPT)
#BUILDOPT ?= --config Debug

#===============================================================
# options
BACKENDS ?= $(shell [ -f $(BCACHE) ] && (grep BACKENDS $(BCACHE) | cut -d= -f2) || echo regular.cmake)
TARGETS  ?= $(shell [ -f $(TCACHE) ] && (grep TARGETS $(TCACHE) | cut -d= -f2) || echo regular.cmake)
LIBSDIR  ?= $(shell [ -f $(LCACHE) ] && (grep LIBSDIR $(LCACHE) | cut -d= -f2) || echo lib)
EMCC 	 ?= emcc

#===============================================================
ifeq ($(GENERATOR), Xcode)
	PROJ = $(FAUSTDIR)/faust.xcodeproj
endif
ifneq (,$(findstring Makefile, $(GENERATOR)))
	PROJ = $(FAUSTDIR)/Makefile
endif
ifneq (,$(findstring Visual Studio,$(GENERATOR)))
	PROJ = $(FAUSTDIR)/faust.sln
endif

#===============================================================
# main targets
all: $(PROJ)
	$(CMAKE) --build $(FAUSTDIR) $(BUILDOPT) 

full:
	$(MAKE) cmake BACKENDS=all.cmake TARGETS=all.cmake 
	$(CMAKE) --build $(FAUSTDIR) $(BUILDOPT) 

clean:
	$(CMAKE) --build $(FAUSTDIR) --target clean
	rm -f lib/libfaustwithllvm.a

distclean:
	rm -rf $(FAUSTDIR)

#===============================================================
help:
	@echo "-------- FAUST compiler makefile --------"
	@echo "Available targets are:"
	@echo " 'all' (default) : builds the current targets (as defined by your targets setup)."
	@echo " 'full'          : builds the all targets with all backends."
	@echo
	@echo "Targets that require specific setup (see TARGETS option):"
	@echo " 'faust' 	 : builds the Faust compiler."
	@echo " 'osc'        : builds the static Faust OSC libraries"
	@echo " 'http'       : builds the static Faust HTTPD libraries"
	@echo " 'staticlib'  : builds the libfaust library in static mode."
	@echo " 'dynamiclib' : builds the libfaust library in dynamic mode."
	@echo " 'oscdynamic' : builds the OSC library in dynamic mode."
	@echo " 'httpdynamic': builds the HTTPD library in dynamic mode."
	@echo " 'oscandroid' : builds the OSC library for Android."
	@echo " 'ioslib'     : builds the libfaust static lib for iOS (makes use of the ios.cmake backend)"
	@echo
	@echo "Cleaning:"
	@echo " 'clean'      : removes the output of the 'all' targets"
	@echo " 'distclean'  : removes the 'FAUSTDIR' folder ($(FAUSTDIR)) but preserves the bin and lib folders"
	@echo
	@echo "Targets excluded from all:"
	@echo " 'wasmlib'    : builds libfaust as a WebAssembly library"
	@echo " 'wasmglue'   : builds the WebAssembly glue library."
	@echo
	@echo "Available options:"
	@echo "  FAUSTDIR=<dir>              : the compilation directory. Default to '$(FAUSTDIR)'"
	@echo "  LIBSDIR                     : the libraries destination directory, default: $(LIBSDIR)"
	@echo "  GENERATOR=<a cmake generator>: see cmake -h. Default to '$(GENERATOR)'"
	@echo "  CMAKEOPT=<cmake options>    : pass options to cmake for project generation."
	@echo "  BUILDOPT=<cmake options>    : pass options to cmake at build time (default to $(BUILDOPT))."
	@echo "  BACKENDS=<backends file>    : see 'Backends' below"
	@echo "  TARGETS=<targets file>      : see 'Targets' below"
	@echo "  WORKLET                     : Compile wasm glue library for worklet (default is off)"
	@echo
	@echo "Backends:"
	@echo "  the Faust backends currently included are described in the '$(BACKENDS)' file"
	@echo "  you can freely customize this file or use another file with the BACKENDS option"
	@echo
	@echo "Targets:"
	@echo "  the targets currently included are described in the '$(TARGETS)' file"
	@echo "  you can freely customize this file or use another file with the TARGETS option"
	@echo
	@echo "Utilities targets:"
	@echo " 'cmake'      : regenerate the project using the current config"
	@echo " 'universal'  : [macOS] set the universal binaries option ON (x86_64 and arm64)."
	@echo " 'native'     : [macOS] set the universal binaries option OFF."
	@echo " 'verbose'    : turn the verbose makefile option ON."
	@echo " 'silent'     : turn the verbose makefile option OFF."
	@echo " 'jsscripts'  : to rebuild javascript resources (from architecture/httpdlib)."
	@echo
	@echo "Installation targets:"
	@echo " 'install'    : install faust to the target directory (default to $(DESTDIR)$(PREFIX)),"
	@echo " 'uninstall'  : remove previously installed files,"
	@echo "Installation options:"
	@echo " 'DESTDIR'    : the destination directory,"
	@echo " 'PREFIX'     : the destination prefix,"
	@echo "  Note that when using a relative path, it is relative to FAUSTDIR ($(FAUSTDIR))"
	@echo "------ see also the README.md file ------"
	@echo
	@echo "Packaging targets:"
	@echo " 'package'    : build a Faust package for the current platform"
	@echo " 'release'    : build a Faust release (macOS only)"
	@echo "                includes faust, faustgen and dist packages"


faust: $(PROJ) 
	$(CMAKE) --build $(FAUSTDIR) --target faust $(BUILDOPT) 

osc: $(PROJ)
	$(CMAKE) --build $(FAUSTDIR) --target oscstatic $(BUILDOPT) 

oscdynamic: $(PROJ)
	$(CMAKE) --build $(FAUSTDIR) --target oscdynamic $(BUILDOPT) 

oscandroid: $(PROJ)
	cd ../architecture/osclib/android/&& ndk-build 

http: $(PROJ)
	$(CMAKE) --build $(FAUSTDIR) --target httpstatic $(BUILDOPT) 

httpdynamic: $(PROJ)
	$(CMAKE) --build $(FAUSTDIR) --target httpdynamic $(BUILDOPT) 

jsscripts: 
	$(MAKE) -C ../architecture/httpdlib/src/hexa

#===============================================================
# packaging
#===============================================================
# don't change the PACK variable, files are put at first hierarchy level
PACK := package/Faust-$(VERSION)
package:
	$(MAKE) $(NATIVEPACK)

winpack:
	cd $(FAUSTDIR) && $(CMAKE) -DUSE_LLVM_CONFIG=off -DPACK=on -C ../backends/most.cmake -C ../targets/most.cmake ..
	$(MAKE)
	cd $(FAUSTDIR) && cpack -G NSIS64
	mv $(FAUSTDIR)/Faust-*.exe .

macpack: package/README.html
	-[ -d $(PACK) ] && rm -rf $(PACK)
	$(MAKE) cmake BACKENDs=all.cmake TARGETS=all.cmake
	$(MAKE) install PREFIX=../$(PACK)/Faust-$(VERSION)
	$(MAKE) mactools FAUSTDIR=../../build/$(PACK)/Faust-$(VERSION)
	cp package/INSTALL.html $(PACK)
	cp package/README.html $(PACK)
	hdiutil create Faust-$(VERSION).dmg -fs HFS+ -srcfolder $(PACK) -format UDBZ -ov

mactools:
	$(MAKE) -C ../tools/benchmark FAUSTDIR=$(FAUSTDIR) TARGETS="dynamic-faust faustbench-llvm interp-tracer" LLVM="$(LLVM)" ARCHS="$(ARCHS)" USE_STATIC_SNDFILE=$(USE_STATIC_SNDFILE)
	$(MAKE) -C ../tools/benchmark install PREFIX=$(FAUSTDIR) FAUSTDIR=$(FAUSTDIR) TARGETS="dynamic-faust faustbench-llvm interp-tracer" LLVM="$(LLVM)" ARCHS="$(ARCHS)" USE_STATIC_SNDFILE=$(USE_STATIC_SNDFILE)
	$(MAKE) -C ../tools/sound2faust TARGETS="sound2faust sound2file" ARCHS="$(ARCHS)" USE_STATIC_SNDFILE=$(USE_STATIC_SNDFILE)
	$(MAKE) -C ../tools/sound2faust install PREFIX=$(FAUSTDIR) TARGETS="sound2faust sound2file" ARCHS="$(ARCHS)" USE_STATIC_SNDFILE=$(USE_STATIC_SNDFILE)

linuxpack:
	@echo Linux packaging not implemented. 

package/README.html: ../README.md
	echo "<!DOCTYPE html><html><xmp>" > package/README.html
	cat ../README.md >> package/README.html
	echo "</xmp>" >> package/README.html
	echo "<script type=\"text/javascript\">" >> package/README.html
	cat package/strapdown.min.js >> package/README.html
	echo "</script>" >> package/README.html
	echo "</html>" >> package/README.html


#===============================================================
# release
#===============================================================
FAUSTLIVE ?=../../faustlive
FAUSTGEN ?=../embedded/faustgen
release: APATH=$(shell pwd)
release:
	@echo "################## Building faust package ###################"
	$(MAKE) cmake BACKENDS=all.cmake TARGETS=all.cmake
	$(MAKE) all
	$(MAKE) package
	@[ -d Release-$(VERSION) ] || mkdir Release-$(VERSION)
	rm -rf Release-$(VERSION)/*
	cp Faust-$(VERSION).dmg Release-$(VERSION) 
	$(MAKE) install PREFIX=$(HOME)/Faust-$(VERSION)
	@echo "################## Building faust src distribution ###################"
	$(MAKE) -C .. dist
	mv ../faust-$(VERSION).tar.gz Release-$(VERSION)
	$(MAKE) faustgen
# 	$(MAKE) faustlive  # todo:

faustgen:
	@echo "################## Building faustgen package ###################"
	$(MAKE) -C $(FAUSTGEN) clean
	$(MAKE) -C $(FAUSTGEN) FAUST_PATH_IS_ABSOLUTE=1 FAUST=$(HOME)/Faust-$(VERSION)/bin/faust USE_STATIC_SNDFILE=$(USE_STATIC_SNDFILE) MAXSDK="$(MAXSDK)"
	$(MAKE) -C $(FAUSTGEN) package
	cp $(FAUSTGEN)/package/*.dmg Release-$(VERSION)

faustlive: APATH=$(shell pwd)
faustlive:
	@echo "################## Building faustlive package ###################"
	$(MAKE) -C $(FAUSTLIVE)/Build release FAUST=$(HOME)/Faust-$(VERSION)/bin/faust DEST=$(APATH)/Release-$(VERSION)


#===============================================================
# building universal binaries on macos
#===============================================================
universal: $(FAUSTDIR)
	cd $(FAUSTDIR) && $(CMAKE) -DUNIVERSAL=ON ..

native: $(FAUSTDIR)
	cd $(FAUSTDIR) && $(CMAKE) -DUNIVERSAL=OFF ..


#===============================================================
# building libraries
#===============================================================
staticlib: $(PROJ)
	$(CMAKE) --build $(FAUSTDIR) --target staticlib $(BUILDOPT)   

dynamiclib: $(PROJ)
	$(CMAKE) --build $(FAUSTDIR) --target dynamiclib $(BUILDOPT) 


#===============================================================
# building libfaust.a for ios
#===============================================================
ioslib: $(IOSDIR) $(IOSDIR)/faust.xcodeproj
	$(CMAKE) --build $(IOSDIR) --target staticlib $(BUILDOPT) 
	$(CMAKE) --build $(IOSDIR) --target oscstatic $(BUILDOPT) 

$(IOSDIR)/faust.xcodeproj: CMakeLists.txt backends/ios.cmake
	cd $(IOSDIR) && $(CMAKE) -C ../backends/ios.cmake ..  -DINCLUDE_STATIC=on -DINCLUDE_HTTP=off -G Xcode


#===============================================================
# misc targets
#===============================================================
$(FAUSTDIR):
	mkdir $(FAUSTDIR)

$(IOSDIR): 
	mkdir $(IOSDIR)

$(PROJ): 
	$(MAKE) cmake

verbose: $(FAUSTDIR)
	cd $(FAUSTDIR) && $(CMAKE) -DCMAKE_VERBOSE_MAKEFILE=ON ..

silent: $(FAUSTDIR)
	cd $(FAUSTDIR) && $(CMAKE) -DCMAKE_VERBOSE_MAKEFILE=OFF ..

cmake: $(FAUSTDIR)
	cd $(FAUSTDIR) && $(CMAKE) -C ../backends/$(BACKENDS) -C ../targets/$(TARGETS) $(CMAKEOPT) -DINCLUDE_LLVM=$(INCLUDE_LLVM) -DUSE_LLVM_CONFIG=$(USE_LLVM_CONFIG) -DLLVM_PACKAGE_VERSION=$(LLVM_PACKAGE_VERSION) -DLLVM_LIBS="$(LLVM_LIBS)" -DLLVM_LIB_DIR="$(LLVM_LIB_DIR)" -DLLVM_INCLUDE_DIRS="$(LLVM_INCLUDE_DIRS)" -DLLVM_DEFINITIONS="$(LLVM_DEFINITIONS)" -DLLVM_LD_FLAGS="$(LLVM_LD_FLAGS)" $(DEPLOYMENT) -DLIBSDIR=$(LIBSDIR) -DBUILD_HTTP_STATIC=$(BUILD_HTTP_STATIC) -G '$(GENERATOR)' ..
	@echo BACKENDS=$(BACKENDS) > $(BCACHE)
	@echo TARGETS=$(TARGETS) > $(TCACHE)
	@echo LIBSDIR=$(LIBSDIR) > $(LCACHE)


#===============================================================
# building faust with emscripten
#===============================================================
WASMFS := wasm-filesystem
WASMLIBDIR := share/faust
wasmlib: $(FAUSTDIR) $(FAUSTDIR)/Makefile
	@$(MAKE) checkemcc
	mkdir -p $(WASMFS)/$(WASMLIBDIR) && cp ../libraries/*.lib ../libraries/old/*.lib $(WASMFS)/$(WASMLIBDIR)
	mkdir -p $(WASMFS)/rsrc && cp ../architecture/webaudio/mixer32.wasm $(WASMFS)/rsrc && cp ../architecture/webaudio/mixer64.wasm $(WASMFS)/rsrc
	$(CMAKE) --build $(FAUSTDIR) --target wasmlib $(BUILDOPT) -- $(JOBS)
	cp $(FAUSTDIR)/emcc/libfaust-wasm.* lib
	rm -rf $(WASMFS)

wasmglue: $(FAUSTDIR) $(FAUSTDIR)/Makefile
	@$(MAKE) checkemcc
	$(CMAKE) --build $(FAUSTDIR) --target wasmglue $(BUILDOPT) 

checkemcc:
	@which $(EMCC) > /dev/null || (echo "### emcc must be available from your PATH."; false;)


#===============================================================
# faust install
#===============================================================
installLog := $(FAUSTDIR)/install_manifest.txt
install:
	if test -d ../.git; then git submodule update --init; fi
	cd $(FAUSTDIR) && $(CMAKE) .. -DCMAKE_INSTALL_PREFIX=$(PREFIX) $(CMAKEOPT)
	$(CMAKE) --build $(FAUSTDIR) --target install

uninstall: $(installLog)
	$(shell cat $(installLog) | xargs rm -f)
	rm -f $(installLog)

#===============================================================
undefined:
	$(error System is undefined, not target available)
