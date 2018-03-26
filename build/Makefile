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

#===============================================================
# current generator and backends
CACHE  = $(FAUSTDIR)/CMakeCache.txt
BCACHE = $(FAUSTDIR)/backends.txt
ifeq ($(system),  MINGW)
	GENERATOR ?= $(shell [ -f $(CACHE) ] && (grep CMAKE_GENERATOR:INTERNAL $(CACHE) | cut -d= -f2) || echo MSYS Makefiles)
else
	PREFIX ?= /usr/local
	GENERATOR ?= $(shell [ -f $(CACHE) ] && (grep CMAKE_GENERATOR:INTERNAL $(CACHE) | cut -d= -f2) || echo Unix Makefiles)
endif
DESTDIR ?=


.PHONY: faust install uninstall osc http

MAKE ?= make

CMAKEOPT ?= -DCMAKE_BUILD_TYPE=Release
BUILDOPT ?= --config Release

#CMAKEOPT ?= -DCMAKE_BUILD_TYPE=Debug
#BUILDOPT ?= --config Debug

#===============================================================
# options
JOBS	 ?= -j 4
BACKENDS ?= $(shell [ -f $(BCACHE) ] && (grep BACKENDS $(BCACHE) | cut -d= -f2) || echo backends.cmake)
EMCC 	 ?= emcc

#===============================================================
ifeq ($(GENERATOR), Xcode)
	PROJ = $(FAUSTDIR)/faust.xcodeproj
	JOBS = -jobs 4
endif
ifneq (,$(findstring Makefile, $(GENERATOR)))
	PROJ = $(FAUSTDIR)/Makefile
endif
ifneq (,$(findstring Visual Studio,$(GENERATOR)))
	PROJ = $(FAUSTDIR)/faust.sln
	JOBS = /maxcpucount:4
endif


#===============================================================
# main target
all: $(PROJ)
	cmake --build $(FAUSTDIR) $(BUILDOPT) -- $(JOBS)

clean: $(PROJ)
	cmake --build $(FAUSTDIR) --target clean

#===============================================================
help:
	@echo "-------- FAUST compiler makefile --------"
	@echo "Available targets are:"
	@echo " 'all' (default) : builds the current targets (defined by configxxx - default to faust, osc and http)."
	@echo " 'faust' 	 : builds the FAUST compiler."
	@echo " 'staticlib'  : builds the libfaust library in static mode (requires configstatic)."
	@echo " 'dynamiclib' : builds the libfaust library in dynamic mode (requires configdynamic)."
	@echo " 'wasmlib'    : builds the libfaust as a Web Assembly library"
	@echo " 'asmjslib'   : builds the libfaust as a ASM JS library"
	@echo " 'ioslib'     : builds the libfaust static lib for iOS (makes use of the ios.cmake backend)"
	@echo " 'osc'        : builds the static Faust OSC libraries"
	@echo " 'http'       : builds the static Faust HTTPD libraries"
	@echo " 'clean'      : removes the output of the 'all' targets"
	@echo
	@echo "Available options:"
	@echo "  FAUSTDIR=<dir>              : the compilation directory. Default to '$(FAUSTDIR)'"
	@echo "  GENERATOR=<a cmake generator>: see cmake -h. Default to '$(GENERATOR)'"
	@echo "  CMAKEOPT=<cmake options>    : pass options to cmake for project generation."
	@echo "  BUILDOPT=<cmake options>    : pass options to cmake at build time (default to $(BUILDOPT))."
	@echo "  BACKENDS=<backends file>    : see 'Backends' below"
	@echo "  JOBS        : intended to set the number of tasks to run in parallel (default is $(JOBS))"
	@echo
	@echo "Backends:"
	@echo "  the FAUST backends included by default are described in the '$(BACKENDS)' file"
	@echo "  you can freely customize this file or use another file with the BACKENDS option"
	@echo
	@echo "Project configuration targets:"
	@echo "the following targets do not recompile but change the cmake generated project."
	@echo " 'configstatic'  : includes the static library in the project."
	@echo " 'configdynamic' : includes the dynamic library in the project."
	@echo " 'configall'     : includes all libraries in the project."
	@echo " 'reset'      : reset the project to the basic targets (faust, osc and http)."
	@echo " 'cmake'      : regenerate the project using the current config"
	@echo
	@echo "Utilities targets:"
	@echo " 'universal'  : [MacOSX] set the universal binaries option ON."
	@echo " 'native'     : [MacOSX] set the universal binaries option OFF."
	@echo " 'verbose'    : turn the verbose makefile option ON."
	@echo " 'silent'     : turn the verbose makefile option OFF."
	@echo
	@echo "Installation targets:"
	@echo " 'install'    : install faust to the target directory (default to $(DESTDIR)$(PREFIX)),"
	@echo " 'uninstall'  : remove previously installed files,"
	@echo "Installation options:"
	@echo " 'DESTDIR'    : the destination directory,"
	@echo " 'PREFIX'     : the destination directory,"
	@echo "  Note that when using a relative path, it is relative to FAUSTDIR ($(FAUSTDIR))"
	@echo "------ see also the README.md file ------"

	
faust: $(PROJ) 
	cmake --build $(FAUSTDIR) --target faust $(BUILDOPT) -- $(JOBS)

osc: $(PROJ)
	cmake --build $(FAUSTDIR) --target oscstatic $(BUILDOPT) -- $(JOBS)
#	cmake --build $(FAUSTDIR) --target oscdynamic $(BUILDOPT) -- $(JOBS)

http: $(PROJ)
	cmake --build $(FAUSTDIR) --target httpstatic $(BUILDOPT) -- $(JOBS)
#	cmake --build $(FAUSTDIR) --target httpdynamic $(BUILDOPT) -- $(JOBS)


#===============================================================
# building universal binaries on macos
#===============================================================
universal: 
	cd $(FAUSTDIR) && cmake -DUNIVERSAL=ON ..

native: 
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
ioslib: $(IOSDIR) $(IOSDIR)/faust.xcodeproj
	cmake --build $(IOSDIR) --target staticlib $(BUILDOPT) -- $(JOBS)
	cmake --build $(IOSDIR) --target OSCFaust $(BUILDOPT) --  $(JOBS)

$(IOSDIR)/faust.xcodeproj: CMakeLists.txt backends/ios.cmake
	cd $(IOSDIR) && cmake -C ../backends/ios.cmake .. -G Xcode


#===============================================================
# misc targets
#===============================================================
$(FAUSTDIR):
	mkdir $(FAUSTDIR)

$(IOSDIR): 
	mkdir $(IOSDIR)

$(PROJ): $(FAUSTDIR) backends/$(BACKENDS)
	$(MAKE) cmake

verbose: $(FAUSTDIR)
	cd $(FAUSTDIR) && cmake -DCMAKE_VERBOSE_MAKEFILE=ON ..

silent: $(FAUSTDIR)
	cd $(FAUSTDIR) && cmake -DCMAKE_VERBOSE_MAKEFILE=OFF ..

cmake: $(FAUSTDIR)
	cd $(FAUSTDIR) && cmake -C ../backends/$(BACKENDS) $(CMAKEOPT) -G '$(GENERATOR)' ..
	@echo BACKENDS=$(BACKENDS) > $(BCACHE)

configstatic: STATIC ?= on
configstatic: $(PROJ)
	cd $(FAUSTDIR) && cmake -DINCLUDE_STATIC=$(STATIC) ..

configdynamic: DYNAMIC ?= on
configdynamic: $(PROJ)
	cd $(FAUSTDIR) && cmake -DINCLUDE_DYNAMIC=$(DYNAMIC) ..

confighttp: HTTP ?= on
confighttp: $(PROJ)
	cd $(FAUSTDIR) && cmake -DINCLUDE_HTTP=on ..

configall: $(PROJ)
	cd $(FAUSTDIR) && cmake -DINCLUDE_STATIC=on -DINCLUDE_DYNAMIC=on -DINCLUDE_HTTP=on ..

reset: STATIC ?= off
reset: DYNAMIC ?= off
reset: HTTP ?= on
reset: BACKENDS ?= backends.cmake
reset: $(PROJ)
	cd $(FAUSTDIR) && cmake -C ../backends/$(BACKENDS) $(CMAKEOPT) -DINCLUDE_STATIC=$(STATIC) -DINCLUDE_DYNAMIC=$(DYNAMIC) -DINCLUDE_HTTP=$(HTTP) ..


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
