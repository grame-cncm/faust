#
# FAUST compiler makefile
#

# start to determine the current platform
TARGET := undefined
system := $(shell uname -s)
# normalizes MINGW versions
system := $(shell echo $(system) | grep MINGW > /dev/null && echo MINGW || echo $(system))
ifeq ($(system), Darwin)
	TARGET = unix
	PREFIX ?= /usr/local
else
 ifeq ($(system), MINGW)
	TARGET = windows
 else
  ifeq ($(system), Linux)
	TARGET = unix
	PREFIX ?= /usr/local
  endif
 endif
endif
DESTDIR ?=


.PHONY: faust install uninstall osc http

MAKE ?= make
CMAKEOPT ?= -DCMAKE_BUILD_TYPE=Release

#===============================================================
# output directories
FAUSTDIR ?= faustdir
IOSDIR   := iosdir

#===============================================================
# options
TASKS	?= 4
BACKENDS?= backends.cmake
EMCC 	?= emcc

#===============================================================
# main target
faust:
	$(MAKE) $(TARGET)

clean:
	cmake --build $(FAUSTDIR) --target clean

#===============================================================
help:
	@echo "-------- FAUST compiler makefile --------"
	@echo "Available targets are:"
	@echo " 'faust' (default): builds the FAUST compiler."
	@echo " 'staticlib'  : builds the FAUST static library."
	@echo " 'dynamiclib' : builds the FAUST dynamic library."
	@echo " 'wasmlib'    : builds the FAUST compiler as a Web Assembly library"
	@echo " 'asmjslib'   : builds the FAUST compiler as a ASM JS library"
	@echo " 'ios'        : builds the static lib for iOS (makes use of the ios.cmake backend)"
	@echo " 'osc'        : builds the static and dynamic Faust OSC libraries"
	@echo " 'http'       : builds the static and dynamic Faust HTTPD libraries"
	@echo " 'all'        : call the faust, staticlib, dynamiclib, osc and http targets."
	@echo " 'windows'    : build the faust, staticlib and dynamiclib targets using MSYS Makefiles,"
	@echo "                see the README.md file for other options."
	@echo " 'install'    : install ,"
	@echo " 'clean'      : clean remove the output of the 'all' targets"
	@echo
	@echo "Available options:"
	@echo "  FAUSTDIR=<dir>              : the compilation directory. Default to '$(FAUSTDIR)'"
	@echo "  CMAKEOPT=<cmake options>    : pass options to cmake. Default to '$(CMAKEOPT)'"
	@echo "  BACKENDS=<backends>         : see 'Backends' below"
	@echo "  TASKS=[1-n] : set the number of tasks to run in parallel (default is $(TASKS))"
	@echo
	@echo "Backends:"
	@echo "  the FAUST backends included by default are described in the '$(BACKENDS)' file"
	@echo "  you can freely customize this file or use another file with the BACKENDS option"
	@echo
	@echo "Utilities targets:"
	@echo " 'cmake'      : regenerate the Makefile (or platform specific project)"
	@echo " 'universal'  : [MacOSX] set the universal binaries option ON."
	@echo " 'native'     : [MacOSX] set the universal binaries option OFF."
	@echo " 'verbose'    : turn the verbose makefile option ON."
	@echo " 'silent'     : turn the verbose makefile option OFF."
	@echo
	@echo "Installation targets:"
	@echo " 'install'    : install faust to the target directory (default to $(DESTDIR)$(PREFIX)),"
	@echo "Installation options:"
	@echo " 'DESTDIR'    : the destination directory,"
	@echo " 'PREFIX'     : the destination directory,"
	@echo "  Note that when using a relative path, it is relative to FAUSTDIR ($(FAUSTDIR))"

all:
	$(MAKE) faust
	$(MAKE) staticlib
	$(MAKE) dynamiclib
	$(MAKE) osc
	$(MAKE) http

osc:
	cmake --build $(FAUSTDIR) --target oscstatic -- -j $(TASKS)
	cmake --build $(FAUSTDIR) --target oscdynamic -- -j $(TASKS)

http:
	cmake --build $(FAUSTDIR) --target httpstatic -- -j $(TASKS)
	cmake --build $(FAUSTDIR) --target httpdynamic -- -j $(TASKS)


#===============================================================
# building universal binaries on macos
#===============================================================
universal: 
	cd $(FAUSTDIR) && cmake -C ../$(BACKENDS) $(CMAKEOPT) -DUNIVERSAL=ON ..

native: 
	cd $(FAUSTDIR) && cmake -C ../$(BACKENDS) $(CMAKEOPT) -DUNIVERSAL=OFF ..


#===============================================================
# building faust on unix like systems
#===============================================================
unix: $(FAUSTDIR) $(FAUSTDIR)/Makefile
	cmake --build $(FAUSTDIR) --target faust -- -j $(TASKS)

staticlib: $(FAUSTDIR) $(FAUSTDIR)/Makefile
	cmake --build $(FAUSTDIR) --target staticlib  -- -j $(TASKS) 

dynamiclib: $(FAUSTDIR) $(FAUSTDIR)/Makefile
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

$(FAUSTDIR)/Makefile: CMakeLists.txt $(BACKENDS)
	cd $(FAUSTDIR) && cmake -C ../$(BACKENDS) $(CMAKEOPT) ..

verbose: $(FAUSTDIR)
	cd $(FAUSTDIR) && cmake -C ../$(BACKENDS) $(CMAKEOPT) -DCMAKE_VERBOSE_MAKEFILE=ON ..

silent: $(FAUSTDIR)
	cd $(FAUSTDIR) && cmake -C ../$(BACKENDS) $(CMAKEOPT) -DCMAKE_VERBOSE_MAKEFILE=OFF ..

cmake: $(FAUSTDIR)
	cd $(FAUSTDIR) && cmake -C ../$(BACKENDS) $(CMAKEOPT) ..


#===============================================================
# building faust on windows
# default is to build using MSYS makefiles
#===============================================================
windows: $(FAUSTDIR)
	cd $(FAUSTDIR) && cmake -C ../$(BACKENDS) $(CMAKEOPT) .. -G "MSYS Makefiles"
	cmake --build $(FAUSTDIR) -- -j $(TASKS)

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
