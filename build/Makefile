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
VERSION := 2.14.3

#===============================================================
# current generator and backends
CACHE  = $(FAUSTDIR)/CMakeCache.txt
BCACHE = $(FAUSTDIR)/backends.txt
TCACHE = $(FAUSTDIR)/targets.txt
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


.PHONY: faust install uninstall osc http package

MAKE ?= make

CMAKEOPT ?= -DCMAKE_BUILD_TYPE=Release
BUILDOPT ?= --config Release

#CMAKEOPT ?= -DCMAKE_BUILD_TYPE=Debug
#BUILDOPT ?= --config Debug

#===============================================================
# options
JOBS	 ?= -j 4
BACKENDS ?= $(shell [ -f $(BCACHE) ] && (grep BACKENDS $(BCACHE) | cut -d= -f2) || echo regular.cmake)
TARGETS  ?= $(shell [ -f $(TCACHE) ] && (grep TARGETS $(TCACHE) | cut -d= -f2) || echo regular.cmake)
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

clean:
	cmake --build $(FAUSTDIR) --target clean

distclean:
	rm -rf $(FAUSTDIR)


#===============================================================
help:
	@echo "-------- FAUST compiler makefile --------"
	@echo "Available targets are:"
	@echo " 'all' (default) : builds the current targets (as defined by your targets setup)."
	@echo
	@echo "Targets that require specific setup (see TARGETS option):"
	@echo " 'faust' 	 : builds the Faust compiler."
	@echo " 'osc'        : builds the static Faust OSC libraries"
	@echo " 'http'       : builds the static Faust HTTPD libraries"
	@echo " 'staticlib'  : builds the libfaust library in static mode."
	@echo " 'dynamiclib' : builds the libfaust library in dynamic mode."
	@echo " 'oscdynamic' : builds the OSC library in dynamic mode."
	@echo " 'httpdynamic': builds the HTTPD library in dynamic mode."
	@echo
	@echo " 'ioslib'     : builds the libfaust static lib for iOS (makes use of the ios.cmake backend)"
	@echo
	@echo "Cleaning:"
	@echo " 'clean'      : removes the output of the 'all' targets"
	@echo " 'distclean'  : removes the 'FAUSTDIR' folder ($(FAUSTDIR)) but preserves the bin and lib folders"
	@echo
	@echo "Targets excluded from all:"
	@echo " 'wasmlib'    : builds the libfaust as a WebAssembly library"
	@echo " 'asmjslib'   : builds the libfaust as an ASMJS library"
	@echo
	@echo "Available options:"
	@echo "  FAUSTDIR=<dir>              : the compilation directory. Default to '$(FAUSTDIR)'"
	@echo "  GENERATOR=<a cmake generator>: see cmake -h. Default to '$(GENERATOR)'"
	@echo "  CMAKEOPT=<cmake options>    : pass options to cmake for project generation."
	@echo "  BUILDOPT=<cmake options>    : pass options to cmake at build time (default to $(BUILDOPT))."
	@echo "  BACKENDS=<backends file>    : see 'Backends' below"
	@echo "  TARGETS=<targets file>      : see 'Targets' below"
	@echo "  JOBS        : intended to set the number of tasks to run in parallel (default is $(JOBS))"
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

	
faust: $(PROJ) 
	cmake --build $(FAUSTDIR) --target faust $(BUILDOPT) -- $(JOBS)

osc: $(PROJ)
	cmake --build $(FAUSTDIR) --target oscstatic $(BUILDOPT) -- $(JOBS)

oscdynamic: $(PROJ)
	cmake --build $(FAUSTDIR) --target oscdynamic $(BUILDOPT) -- $(JOBS)

http: $(PROJ)
	cmake --build $(FAUSTDIR) --target httpstatic $(BUILDOPT) -- $(JOBS)

httpdynamic: $(PROJ)
	cmake --build $(FAUSTDIR) --target httpdynamic $(BUILDOPT) -- $(JOBS)

jsscripts: 
	make -C ../architecture/httpdlib/src/hexa

#===============================================================
# packaging
#===============================================================
PACK := package/Faust-$(VERSION)
package:
	make $(NATIVEPACK)

winpack:
	cd $(FAUSTDIR) && cmake -DUSE_LLVM_CONFIG=off -DPACK=on -C ../bakckends/most.cmake -C ../targets/most.cmake ..
	make
	cd $(FAUSTDIR) && cpack -G NSIS64
	mv  $(FAUSTDIR)/Faust-*.exe .

macpack: package/README.html
	make -C package/Tools
	-[ -d $(PACK) ] && rm -rf $(PACK)
	make cmake BACKENDs=all.cmake TARGETS=all.cmake
	make install PREFIX=../$(PACK)/Faust-$(VERSION)
	cp package/install $(PACK)/Faust-$(VERSION)
	cp package/INSTALL.rtf $(PACK)
	cp package/README.html $(PACK)
	hdiutil create Faust-$(VERSION).dmg -srcfolder $(PACK) -ov

linuxpack:
	@echo Linux packaging not implemented. 

package/README.html: ../README.md
	echo "<!DOCTYPE html><html><xmp>" > package/README.html
	cat ../README.md >> package/README.html
	echo "</xmp>" >> package/README.html
	echo "<script src=http://strapdownjs.com/v/0.2/strapdown.js></script>" >> package/README.html
	echo "</html>" >> package/README.html
	

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
	cd $(FAUSTDIR) && cmake -C ../backends/$(BACKENDS) -C ../targets/$(TARGETS) $(CMAKEOPT) -G '$(GENERATOR)' ..
	@echo BACKENDS=$(BACKENDS) > $(BCACHE)
	@echo TARGETS=$(TARGETS) > $(TCACHE)

reset: $(FAUSTDIR)
	cd $(FAUSTDIR) && cmake -C ../backends/$(BACKENDS) $(CMAKEOPT) -DINCLUDE_STATIC=off -DINCLUDE_DYNAMIC=off -DINCLUDE_HTTP=on -DOSCDYNAMIC=off -DHTTPDYNAMIC=off ..


#===============================================================
# building faust with emscripten
#===============================================================
wasmlib: $(FAUSTDIR) $(FAUSTDIR)/Makefile
	@$(MAKE) checkemcc
	cmake --build $(FAUSTDIR) --target wasmlib $(BUILDOPT) -- $(JOBS)

asmjslib: $(FAUSTDIR) $(FAUSTDIR)/Makefile
	@$(MAKE) checkemcc
	cmake --build $(FAUSTDIR) --target asmjslib $(BUILDOPT) -- $(JOBS)

checkemcc:
	@which $(EMCC) > /dev/null || (echo "### emcc must be available from your PATH."; false;)


#===============================================================
# faust install
#===============================================================
installLog := $(FAUSTDIR)/install_manifest.txt
install:
	cd $(FAUSTDIR) && cmake .. -DCMAKE_INSTALL_PREFIX=$(PREFIX) 
	cmake --build $(FAUSTDIR) --target install
uninstall: installedfiles = $(shell cat $(installLog))
uninstall: $(installLog)
	rm -f $(installedfiles) $(installLog)

#===============================================================
undefined:
	$(error System is undefined, not target available)
