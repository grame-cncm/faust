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
CMAKEOPT ?= 

#===============================================================
# options
TASKS	 ?= 4
BACKENDS ?= $(shell [ -f $(BCACHE) ] && (grep BACKENDS $(BCACHE) | cut -d= -f2) || echo backends.cmake)
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
# main target
all: $(PROJ)
	cmake --build $(FAUSTDIR) -- -j $(TASKS)

clean:
	cmake --build $(FAUSTDIR) --target clean

#===============================================================
help:
	@echo "-------- FAUST compiler makefile --------"
	@echo "Available targets are:"
	@echo " 'all' (default) : build the current targets (default to faust and osc)."
	@echo " 'faust' 	 : builds the FAUST compiler."
	@echo " 'staticlib'  : builds the FAUST static library."
	@echo " 'dynamiclib' : builds the FAUST dynamic library."
	@echo " 'wasmlib'    : builds the FAUST compiler as a Web Assembly library"
	@echo " 'asmjslib'   : builds the FAUST compiler as a ASM JS library"
	@echo " 'ios'        : builds the static lib for iOS (makes use of the ios.cmake backend)"
	@echo " 'osc'        : builds the static and dynamic Faust OSC libraries"
	@echo " 'http'       : builds the static and dynamic Faust HTTPD libraries"
	@echo " 'clean'      : clean remove the output of the 'all' targets"
	@echo
	@echo "Available options:"
	@echo "  FAUSTDIR=<dir>              : the compilation directory. Default to '$(FAUSTDIR)'"
	@echo "  CMAKEOPT=<cmake options>    : pass options to cmake."
	@echo "  BACKENDS=<backends>         : see 'Backends' below"
	@echo "  TASKS=[1-n] : set the number of tasks to run in parallel (default is $(TASKS))"
	@echo
	@echo "Backends:"
	@echo "  the FAUST backends included by default are described in the '$(BACKENDS)' file"
	@echo "  you can freely customize this file or use another file with the BACKENDS option"
	@echo
	@echo "Utilities targets:"
	@echo "the following targets do not recompile but change the cmake generated project."
	@echo " 'cmake'      : regenerate the Makefile (or platform specific project)"
	@echo " 'includelibs'    : includes the static and dynamic libraries in the project."
	@echo " 'includestatic'  : includes the static library in the project."
	@echo " 'includedynamic' : includes the dynamic library in the project."
	@echo " 'includehttp'    : includes the httpd library in the project."
	@echo " 'includeall'     : includes all libraries in the project."
	@echo " 'includebasic'   : includes the basic targets in the project (faust and osc)."
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

test:
	@echo GENERATOR $(GENERATOR)
	@echo BACKENDS  $(BACKENDS)
	
faust: $(PROJ) 
	cmake --build $(FAUSTDIR) --target faust -- -j $(TASKS)

osc: $(PROJ)
	cmake --build $(FAUSTDIR) --target oscstatic -- -j $(TASKS)
	cmake --build $(FAUSTDIR) --target oscdynamic -- -j $(TASKS)

http: $(PROJ)
	cmake --build $(FAUSTDIR) --target httpstatic -- -j $(TASKS)
	cmake --build $(FAUSTDIR) --target httpdynamic -- -j $(TASKS)


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
	cmake --build $(FAUSTDIR) --target staticlib  -- -j $(TASKS) 

dynamiclib: $(PROJ)
	cmake --build $(FAUSTDIR) --target dynamiclib -- -j $(TASKS)


#===============================================================
# building libfaust.a for ios
#===============================================================
ios: $(IOSDIR) $(IOSDIR)/faust.xcodeproj
	cmake --build $(IOSDIR) --target staticlib --config Release --  -jobs $(TASKS)
	cmake --build $(IOSDIR) --target OSCFaust --config Release --  -jobs $(TASKS)

$(IOSDIR)/faust.xcodeproj: CMakeLists.txt ios.cmake
	cd $(IOSDIR) && cmake -C ../ios.cmake .. -G Xcode


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

includelibs: $(PROJ)
	cd $(FAUSTDIR) && cmake -DINCLUDE_STATIC=on -DINCLUDE_DYNAMIC=on ..

includestatic: $(PROJ)
	cd $(FAUSTDIR) && cmake -DINCLUDE_STATIC=on ..

includedynamic: $(PROJ)
	cd $(FAUSTDIR) && cmake -DINCLUDE_DYNAMIC=on ..

includehttp: $(PROJ)
	cd $(FAUSTDIR) && cmake -DINCLUDE_HTTP=on ..

includeall: $(PROJ)
	cd $(FAUSTDIR) && cmake -DINCLUDE_STATIC=on -DINCLUDE_DYNAMIC=on -DINCLUDE_HTTP=on ..

includebasic: $(PROJ)
	cd $(FAUSTDIR) && cmake -DINCLUDE_STATIC=off -DINCLUDE_DYNAMIC=off -DINCLUDE_HTTP=off ..


#===============================================================
# building faust with emscripten
#===============================================================
wasmlib: $(FAUSTDIR) $(FAUSTDIR)/Makefile
	@$(MAKE) checkemcc
	cmake --build $(FAUSTDIR) --target wasmlib -- -j $(TASKS)

asmjslib: $(FAUSTDIR) $(FAUSTDIR)/Makefile
	@$(MAKE) checkemcc
	cmake --build $(FAUSTDIR) --target asmjslib -- -j $(TASKS)

checkemcc:
	@which $(EMCC) > /dev/null || (echo "### emcc must be available from your PATH."; false;)


#===============================================================
# faust install
#===============================================================
installLog := $(FAUSTDIR)/install_manifest.txt
install:
	cd $(FAUSTDIR) && cmake .. -DCMAKE_INSTALL_PREFIX=$(DESTDIR)$(PREFIX) 
	cmake --build $(FAUSTDIR) --target install
uninstall: installedfiles = $(shell cat $(installLog))
uninstall: $(installLog)
	rm $(installedfiles) $(installLog)

#===============================================================
undefined:
	$(error System is undefined, not target available)
