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
ifneq (,$(findstring "Visual Studio",$(GENERATOR)))
	PROJ = $(FAUSTDIR)/faust.sln
	JOBS = /maxcpucount:4
endif


#===============================================================
# main target
all: $(PROJ)
	cmake --build $(FAUSTDIR) $(BUILDOPT) -- $(JOBS)

clean: $(FAUSTDIR)
	cmake --build $(FAUSTDIR) --target clean

#===============================================================
help:
	@echo "-------- FAUST compiler makefile --------"
	@echo "Available targets are:"
	@echo " 'all' (default) : builds the current targets (defined by configxxx - default to faust, osc and http)."
	@echo " 'faust' 	 : builds the Faust compiler."
	@echo " 'ioslib'     : builds the libfaust static lib for iOS (makes use of the ios.cmake backend)"
	@echo " 'osc'        : builds the static Faust OSC libraries"
	@echo " 'http'       : builds the static Faust HTTPD libraries"
	@echo " 'clean'      : removes the output of the 'all' targets"
	@echo
	@echo "Targets excluded from all:"
	@echo " 'wasmlib'    : builds the libfaust as a WebAssembly library"
	@echo " 'asmjslib'   : builds the libfaust as an ASMJS library"
	@echo
	@echo "Targets that require specific configs:"
	@echo " 'staticlib'  : builds the libfaust library in static mode (requires configstatic)."
	@echo " 'dynamiclib' : builds the libfaust library in dynamic mode (requires configdynamic)."
	@echo " 'oscdynamic' : builds the OSC library in dynamic mode (requires configoscdynamic)."
	@echo " 'httpdynamic': builds the HTTPD library in dynamic mode (requires confighttpdynamic)."
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
	@echo " 'configoscdynamic'  : includes the dynamic OSC library in the project."
	@echo " 'confighttpdynamic' : includes the dynamic HTTP library in the project."
	@echo " 'reset'      : reset the project to the basic targets (faust, osc and http)."
	@echo " 'cmake'      : regenerate the project using the current config"
	@echo
	@echo "Utilities targets:"
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
	cd $(FAUSTDIR) && cmake -C ../backends/$(BACKENDS) $(CMAKEOPT) -G '$(GENERATOR)' ..
	@echo BACKENDS=$(BACKENDS) > $(BCACHE)

configstatic: STATIC ?= on
configstatic: $(FAUSTDIR)
	cd $(FAUSTDIR) && cmake -DINCLUDE_STATIC=$(STATIC) ..

configdynamic: DYNAMIC ?= on
configdynamic: $(FAUSTDIR)
	cd $(FAUSTDIR) && cmake -DINCLUDE_DYNAMIC=$(DYNAMIC) ..

confighttp: HTTP ?= on
confighttp: $(FAUSTDIR)
	cd $(FAUSTDIR) && cmake -DINCLUDE_HTTP=$(HTTP) ..

configoscdynamic: OSCDYN ?= on
configoscdynamic:
	cd $(FAUSTDIR) && cmake -DOSCDYNAMIC=$(OSCDYN) ..

confighttpdynamic: HTTPDYN ?= on
confighttpdynamic:
	cd $(FAUSTDIR) && cmake -DHTTPDYNAMIC=$(HTTPDYN) ..

configall: $(FAUSTDIR)
	cd $(FAUSTDIR) && cmake -DINCLUDE_STATIC=on -DINCLUDE_DYNAMIC=on -DINCLUDE_HTTP=on ..

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
