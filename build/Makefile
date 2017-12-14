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
else
ifeq ($(system), MINGW)
	TARGET = windows
else
ifeq ($(system), Linux)
	TARGET = unix
endif
endif
endif

CMAKEOPT ?= -DCMAKE_BUILD_TYPE=Release


#===============================================================
# output directories
FAUSTDIR := faustdir
BINDIR := bin
LIBDIR := lib

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
	rm -rf $(FAUSTDIR) $(BINDIR) $(LIBDIR)

#===============================================================
help:
	@echo "-------- FAUST compiler makefile --------"
	@echo "Available targets are:"
	@echo " 'faust' (default): builds the FAUST compiler."
	@echo " 'staticlib'  : builds the FAUST static library."
	@echo " 'dynamiclib' : builds the FAUST static library."
	@echo " 'wasmlib'     : builds the FAUST compiler as a Web Assembly library"
	@echo " 'asmjslib'    : builds the FAUST compiler as a ASM JS library"
	@echo " 'cmake'       : regenerate the Makefile (or platform specific project)
	@echo " 'clean'       : clean remove the output of the 'faust' target"
	@echo
	@echo "Available options:"
	@echo "  CMAKEOPT=<cmake options>    : pass options to cmake. Default to '-DCMAKE_BUILD_TYPE=Release'"
	@echo "  BACKENDS=<backends>         : see 'Backends' below"
	@echo "  TASKS=[1-n] : set the number of tasks to run in parallel (default is $(TASKS))"
	@echo
	@echo "Backends:"
	@echo "  the FAUST backends included by default are described in the '$(BACKENDS)' file"
	@echo "  you can freely customize this file or use another file with the BACKENDS option"



#===============================================================
# building faust on unix like systems
#===============================================================
unix: $(FAUSTDIR) $(FAUSTDIR)/Makefile $(BINDIR)
	cmake --build $(FAUSTDIR) -- -j $(TASKS)
	cp $(FAUSTDIR)/faust $(BINDIR)


staticlib: $(FAUSTDIR) $(FAUSTDIR)/Makefile $(LIBDIR)
	cmake --build $(FAUSTDIR) --target staticlib  -- -j $(TASKS)
	cp $(FAUSTDIR)/libfaust.a $(LIBDIR)

dynamiclib: $(FAUSTDIR) $(FAUSTDIR)/Makefile $(LIBDIR)
	cmake --build $(FAUSTDIR) --target dynamiclib -- -j $(TASKS)
	cp $(FAUSTDIR)/libfaust.dylib $(LIBDIR) || true
	cp $(FAUSTDIR)/libfaust.so $(LIBDIR) || true

#===============================================================
# misc targets
#===============================================================
$(FAUSTDIR):
	mkdir $(FAUSTDIR)

$(BINDIR):
	mkdir $(BINDIR)

$(LIBDIR):
	mkdir $(LIBDIR)

$(FAUSTDIR)/Makefile: CMakeLists.txt $(BACKENDS)
	cd $(FAUSTDIR) && cmake -C ../$(BACKENDS) $(CMAKEOPT) ..

cmake:
	cd $(FAUSTDIR) && cmake -C ../$(BACKENDS) $(CMAKEOPT) ..


#===============================================================
# building faust on windows
# default is to build using MSYS makefiles
#===============================================================
windows: $(FAUSTDIR) $(BINDIR)
	cd $(FAUSTDIR) && cmake -C ../$(BACKENDS) $(CMAKEOPT) .. -G "MSYS Makefiles"
	cmake --build $(FAUSTDIR) -- -j $(TASKS)
	cp $(FAUSTDIR)/faust.exe $(BINDIR)		|| echo no faust.exe output

#===============================================================
# building faust with emscripten
#===============================================================
wasmlib: $(FAUSTDIR) $(FAUSTDIR)/Makefile $(LIBDIR)
	@make checkemcc
	cmake --build $(FAUSTDIR) --target wasmlib -- -j $(TASKS)
	cp $(FAUSTDIR)/emcc/libfaust-wasm.* $(LIBDIR)

asmjslib: $(FAUSTDIR) $(FAUSTDIR)/Makefile $(LIBDIR)
	@make checkemcc
	cmake --build $(FAUSTDIR) --target asmjslib -- -j $(TASKS)
	cp $(FAUSTDIR)/emcc/libfaust.js $(LIBDIR)

checkemcc:
	@which $(EMCC) > /dev/null || (echo "### emcc must be available from your PATH."; false;)

undefined:
	$(error System is undefined, not target available)
