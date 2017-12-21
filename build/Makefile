#
# FAUST compiler makefile
#

# start to determine the current platform
TARGET := undefined
system	:= $(shell uname -s)
# normalizes MINGW versions
system := $(shell echo $(system) | grep MINGW > /dev/null && echo MINGW || echo $(system))
ifeq ($(system), Darwin)
	TARGET = unix
	DLIBEXT = dylib
	SLIBEXT = a
else
ifeq ($(system), MINGW)
	TARGET = windows
	DLIBEXT = dll
	SLIBEXT = lib
else
ifeq ($(system), Linux)
	TARGET = unix
	DLIBEXT = so
	SLIBEXT = a
endif
endif
endif

CMAKEOPT ?= -DCMAKE_BUILD_TYPE=Release


#===============================================================
# output directories
FAUSTDIR := faustdir
IOSDIR   := iosdir

.PHONY: faust 

#===============================================================
# options
TASKS	?= 4
BACKENDS?= backends.cmake

EMCC 	?= emcc


#===============================================================
# main target
faust:
	make $(TARGET)

clean:
	cmake --build $(FAUSTDIR) --target clean

#===============================================================
help:
	@echo "-------- FAUST compiler makefile --------"
	@echo "Available targets are:"
	@echo " 'faust' (default): builds the FAUST compiler."
	@echo " 'staticlib'  : builds the FAUST static library."
	@echo " 'dynamiclib' : builds the FAUST static library."
	@echo " 'wasmlib'    : builds the FAUST compiler as a Web Assembly library"
	@echo " 'asmjslib'   : builds the FAUST compiler as a ASM JS library"
	@echo " 'ios'        : builds the static lib for iOS (makes use of the ios.cmake backend)"
	@echo " 'cmake'      : regenerate the Makefile (or platform specific project)"
	@echo " 'clean'      : clean remove the output of the 'faust' target"
	@echo
	@echo "Available options:"
	@echo "  CMAKEOPT=<cmake options>    : pass options to cmake. Default to '-DCMAKE_BUILD_TYPE=Release'"
	@echo "  BACKENDS=<backends>         : see 'Backends' below"
	@echo "  TASKS=[1-n] : set the number of tasks to run in parallel (default is $(TASKS))"
	@echo
	@echo "Backends:"
	@echo "  the FAUST backends included by default are described in the '$(BACKENDS)' file"
	@echo "  you can freely customize this file or use another file with the BACKENDS option"
	@echo
	@echo "Utilities:"
	@echo " 'universal'   : [MacOSX] set the universal binaries option ON."
	@echo " 'native'      : [MacOSX] set the universal binaries option OFF."
	@echo " 'verbose'     : turn the verbose makefile option ON."
	@echo " 'silent'      : turn the verbose makefile option OFF."



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
	cmake --build $(FAUSTDIR) -- -j $(TASKS)

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

verbose:
	cd $(FAUSTDIR) && cmake -C ../$(BACKENDS) $(CMAKEOPT) -DCMAKE_VERBOSE_MAKEFILE=ON ..

silent:
	cd $(FAUSTDIR) && cmake -C ../$(BACKENDS) $(CMAKEOPT) -DCMAKE_VERBOSE_MAKEFILE=OFF ..

cmake:
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
	@make checkemcc
	cmake --build $(FAUSTDIR) --target wasmlib -- -j $(TASKS)

asmjslib: $(FAUSTDIR) $(FAUSTDIR)/Makefile
	@make checkemcc
	cmake --build $(FAUSTDIR) --target asmjslib -- -j $(TASKS)

checkemcc:
	@which $(EMCC) > /dev/null || (echo "### emcc must be available from your PATH."; false;)

undefined:
	$(error System is undefined, not target available)
