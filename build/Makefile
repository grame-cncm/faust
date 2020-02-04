#
# FAUST compiler makefile
#

# start to determine the current platform
system := $(shell uname -s)
# normalizes MINGW versions
system := $(shell echo $(system) | grep MINGW > /dev/null && echo MINGW || echo $(system))

#===============================================================
# output directories
FAUSTDIR ?= faustdir
IOSDIR   := iosdir
VERSION := 2.22.2

#===============================================================
# current generator and backends
CACHE  = $(FAUSTDIR)/CMakeCache.txt
BCACHE = $(FAUSTDIR)/backends.txt
TCACHE = $(FAUSTDIR)/targets.txt
LCACHE = $(FAUSTDIR)/libsdir.txt
ifeq ($(system),  MINGW)
	GENERATOR ?= $(shell [ -f $(CACHE) ] && (grep CMAKE_GENERATOR:INTERNAL $(CACHE) | cut -d= -f2) || echo MSYS Makefiles)
	NATIVEPACK = winpack
else
	PREFIX ?= /usr/local
	GENERATOR ?= $(shell [ -f $(CACHE) ] && (grep CMAKE_GENERATOR:INTERNAL $(CACHE) | cut -d= -f2) || echo Unix Makefiles)
endif
DESTDIR ?=

ifeq ($(system),  MINGW)
	NATIVEPACK = winpack
else ifeq ($(system),  Darwin)
	NATIVEPACK = macpack
else
	NATIVEPACK = linuxpack
endif
DESTDIR ?=


.PHONY: faust install uninstall osc http package wasmglue

MAKE ?= make

WORKLET ?= no
WORKLETOPT = "-DWORKLET=off"
ifeq ($(WORKLET), on)
WORKLETOPT = "-DWORKLET=on"
endif
CMAKEOPT ?= -DCMAKE_BUILD_TYPE=Debug $(WORKLETOPT)
BUILDOPT ?= --config Debug

#CMAKEOPT ?= -DCMAKE_BUILD_TYPE=Debug
#BUILDOPT ?= --config Debug

#===============================================================
# options
JOBS	 ?= -j 4
BACKENDS ?= $(shell [ -f $(BCACHE) ] && (grep BACKENDS $(BCACHE) | cut -d= -f2) || echo regular.cmake)
TARGETS  ?= $(shell [ -f $(TCACHE) ] && (grep TARGETS $(TCACHE) | cut -d= -f2) || echo regular.cmake)
LIBSDIR  ?= $(shell [ -f $(LCACHE) ] && (grep LIBSDIR $(LCACHE) | cut -d= -f2) || echo lib)
EMCC 	 ?= emcc

#===============================================================
ifeq ($(GENERATOR), Xcode)
	PROJ = $(FAUSTDIR)/faust.xcodeproj
	JOBS ?= -jobs 4
endif
ifneq (,$(findstring Makefile, $(GENERATOR)))
	PROJ = $(FAUSTDIR)/Makefile
endif
ifneq (,$(findstring "Visual Studio",$(GENERATOR)))
	PROJ = $(FAUSTDIR)/faust.sln
	JOBS ?= /maxcpucount:4
endif

#===============================================================
# main targets
all: $(PROJ)
	cmake --build $(FAUSTDIR) $(BUILDOPT) -- $(JOBS)

full:
	$(MAKE) cmake BACKENDS=all.cmake TARGETS=all.cmake 
	cmake --build $(FAUSTDIR) $(BUILDOPT) -- $(JOBS)

clean:
	cmake --build $(FAUSTDIR) --target clean

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
	@echo "  JOBS    : intended to set the number of tasks to run in parallel (default is $(JOBS))"
	@echo "  WORKLET : Compile wasm glue library for worklet (default is off)"
	@echo
	@echo "Backends:"
	@echo "  the FAUST backends currently included are described in the '$(BACKENDS)' file"
	@echo "  you can freely customize this file or use another file with the BACKENDS option"
	@echo
	@echo "Targets:"
	@echo "  the targets currently included are described in the '$(TARGETS)' file"
	@echo "  you can freely customize this file or use another file with the TARGETS option"
	@echo
	@echo "Utilities targets:"
	@echo " 'cmake'      : regenerate the project using the current config"
	@echo " 'universal'  : [MacOSX] set the universal binaries option ON."
	@echo " 'native'     : [MacOSX] set the universal binaries option OFF."
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
	@echo " 'package'    : build a faust package for the current platform"
	@echo " 'release'    : build a faust release (MacOS only)"
	@echo "                includes faust, faustgen and dist packages"

	
faust: $(PROJ) 
	cmake --build $(FAUSTDIR) --target faust $(BUILDOPT) -- $(JOBS)

osc: $(PROJ)
	cmake --build $(FAUSTDIR) --target oscstatic $(BUILDOPT) -- $(JOBS)

oscdynamic: $(PROJ)
	cmake --build $(FAUSTDIR) --target oscdynamic $(BUILDOPT) -- $(JOBS)

oscandroid: $(PROJ)
	cd ../architecture/osclib/android/&& ndk-build 

http: $(PROJ)
	cmake --build $(FAUSTDIR) --target httpstatic $(BUILDOPT) -- $(JOBS)

httpdynamic: $(PROJ)
	cmake --build $(FAUSTDIR) --target httpdynamic $(BUILDOPT) -- $(JOBS)

jsscripts: 
	$(MAKE) -C ../architecture/httpdlib/src/hexa

#===============================================================
# packaging
#===============================================================
PACK := package/Faust-$(VERSION)
package:
	$(MAKE) $(NATIVEPACK)

winpack:
	cd $(FAUSTDIR) && cmake -DUSE_LLVM_CONFIG=off -DPACK=on -C ../bakckends/most.cmake -C ../targets/most.cmake ..
	$(MAKE)
	cd $(FAUSTDIR) && cpack -G NSIS64
	mv $(FAUSTDIR)/Faust-*.exe .

macpack: package/README.html
	-[ -d $(PACK) ] && rm -rf $(PACK)
	$(MAKE) cmake BACKENDs=all.cmake TARGETS=all.cmake  CMAKEOPT="-DDEPLOYMENT_TARGET=on"
	$(MAKE) install PREFIX=../$(PACK)/Faust-$(VERSION)
	cp package/INSTALL.html $(PACK)
	cp package/README.html $(PACK)
	hdiutil create Faust-$(VERSION).dmg -fs HFS+ -srcfolder $(PACK) -format UDBZ -ov

linuxpack:
	@echo Linux packaging not implemented. 

package/README.html: ../README.md
	echo "<!DOCTYPE html><html><xmp>" > package/README.html
	cat ../README.md >> package/README.html
	echo "</xmp>" >> package/README.html
	echo "<script src=http://strapdownjs.com/v/0.2/strapdown.js></script>" >> package/README.html
	echo "</html>" >> package/README.html


#===============================================================
# release
#===============================================================
FAUSTLIVE ?=../../faustlive
release: FAUSTGEN=../embedded/faustgen
release: APATH=$(shell pwd)
release:
	git pull --rebase
	@echo "################## Building faust package ###################"
	$(MAKE) cmake BACKENDS=all.cmake TARGETS=all.cmake CMAKEOPT="-DDEPLOYMENT_TARGET=on"
	$(MAKE) all
	$(MAKE) package
	@[ -d Release-$(VERSION) ] || mkdir Release-$(VERSION)
	rm -rf Release-$(VERSION)/*
	cp Faust-$(VERSION).dmg Release-$(VERSION) 
	$(MAKE) install PREFIX=$(HOME)/Faust-$(VERSION)
	@echo "################## Building faustgen package ###################"
	$(MAKE) -C $(FAUSTGEN) clean
	$(MAKE) -C $(FAUSTGEN) FAUST=$(HOME)/Faust-$(VERSION)/bin/faust
	$(MAKE) -C $(FAUSTGEN) package
	cp $(FAUSTGEN)/package/*.dmg Release-$(VERSION) 
	@echo "################## Building faust src distribution ###################"
	$(MAKE) -C .. dist
	mv ../faust-$(VERSION).tar.gz Release-$(VERSION)
	@echo "################## Building faustlive package ###################"
	$(MAKE) -C $(FAUSTLIVE)/Build release FAUST=$(HOME)/Faust-$(VERSION)/bin/faust DEST=$(APATH)/Release-$(VERSION)


#===============================================================
# building universal binaries on macos
#===============================================================
universal: $(FAUSTDIR)
	cd $(FAUSTDIR) && cmake -DUNIVERSAL=ON ..

native: $(FAUSTDIR)
	cd $(FAUSTDIR) && cmake -DUNIVERSAL=OFF ..


#===============================================================
# building libraries
#===============================================================
staticlib: $(PROJ)
	cmake --build $(FAUSTDIR) --target staticlib $(BUILDOPT)  -- $(JOBS) 

dynamiclib: $(PROJ)
	cmake --build $(FAUSTDIR) --target dynamiclib $(BUILDOPT) -- $(JOBS)


#===============================================================
# building libfaust.a for ios
#===============================================================
ioslib: JOBS ?= -jobs 4
ioslib: $(IOSDIR) $(IOSDIR)/faust.xcodeproj
	cmake --build $(IOSDIR) --target staticlib $(BUILDOPT) -- $(JOBS)
	cmake --build $(IOSDIR) --target oscstatic $(BUILDOPT) -- $(JOBS)

$(IOSDIR)/faust.xcodeproj: CMakeLists.txt backends/ios.cmake
	cd $(IOSDIR) && cmake -C ../backends/ios.cmake ..  -DINCLUDE_STATIC=on -DINCLUDE_HTTP=off -G Xcode


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
	cd $(FAUSTDIR) && cmake -DCMAKE_VERBOSE_MAKEFILE=ON ..

silent: $(FAUSTDIR)
	cd $(FAUSTDIR) && cmake -DCMAKE_VERBOSE_MAKEFILE=OFF ..

cmake: $(FAUSTDIR)
	cd $(FAUSTDIR) && cmake -C ../backends/$(BACKENDS) -C ../targets/$(TARGETS) $(CMAKEOPT) -DLIBSDIR=$(LIBSDIR) -G '$(GENERATOR)' ..
	@echo BACKENDS=$(BACKENDS) > $(BCACHE)
	@echo TARGETS=$(TARGETS) > $(TCACHE)
	@echo LIBSDIR=$(LIBSDIR) > $(LCACHE)


#===============================================================
# building faust with emscripten
#===============================================================
wasmlib: $(FAUSTDIR) $(FAUSTDIR)/Makefile
	@$(MAKE) checkemcc
	mkdir -p wasm-libraries && cp ../libraries/*.lib ../libraries/old/*.lib wasm-libraries
	cmake --build $(FAUSTDIR) --target wasmlib $(BUILDOPT) -- $(JOBS)
	rm -rf wasm-libraries

wasmglue: $(FAUSTDIR) $(FAUSTDIR)/Makefile
	@$(MAKE) checkemcc
	cmake --build $(FAUSTDIR) --target wasmglue $(BUILDOPT) -- $(JOBS)

checkemcc:
	@which $(EMCC) > /dev/null || (echo "### emcc must be available from your PATH."; false;)


#===============================================================
# faust install
#===============================================================
installLog := $(FAUSTDIR)/install_manifest.txt
install:
	cd $(FAUSTDIR) && cmake .. -DCMAKE_INSTALL_PREFIX=$(PREFIX)
	cmake  --build $(FAUSTDIR) --target install
uninstall: installedfiles = $(shell cat $(installLog))
uninstall: $(installLog)
	rm -f $(installedfiles) $(installLog)

#===============================================================
undefined:
	$(error System is undefined, not target available)
