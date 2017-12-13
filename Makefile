version := 2.5.13

system	?= $(shell uname -s)

ifeq ($(system), Darwin)
LIB_EXT = dylib
else
ifneq ($(findstring MINGW32, $(system)),)
LIB_EXT = dll
EXE = .exe
else
LIB_EXT = so
endif
endif

DESTDIR ?=
PREFIX ?= /usr/local
CROSS=i586-mingw32msvc-

MAKEFILE := Makefile.unix

prefix := $(DESTDIR)$(PREFIX)
arch   := $(wildcard architecture/*.*)
mfiles := $(wildcard examples/Makefile.*)
vname := faust-$(version)-$(shell date +%y%m%d.%H%M%S)
zname := faust-$(version)

.PHONY: all world dynamic benchmark httpd remote win32 ios ios-llvm asmjs wasm sound2faust

all :
	$(MAKE) -C compiler -f $(MAKEFILE) prefix=$(prefix)
	$(MAKE) -C architecture/osclib

universal :
	$(MAKE) -C compiler -f $(MAKEFILE) prefix=$(prefix) universal
	$(MAKE) -C architecture/osclib

# make world: This builds all the common targets for a fairly complete Faust
# installation: Faust compiler and library, sound2faust utility, OSC and HTTPD
# libraries (both static and dynamic). Most of the extra targets require
# additional dependencies and hence aren't built by default; please check the
# Faust README for details. This target may be built in parallel (make -j).
# NOTE: Once the remote target is readily supported on most platforms, it
# should be added here. This requires Jack2 1.9.10 or later which isn't
# usually installed on most systems, so we skip this target for now.
world : all sound2faust httpd dynamic

dynamic : all httpd
	$(MAKE) -C compiler -f $(MAKEFILE) dynamic prefix=$(prefix)
	$(MAKE) -C architecture/httpdlib/src dynamic PREFIX=$(PREFIX)
	$(MAKE) -C architecture/osclib dynamic PREFIX=$(PREFIX)

benchmark : all
	$(MAKE) -C tools/benchmark all

httpd :
	$(MAKE) -C architecture/httpdlib/src all

remote :
	$(MAKE) -C embedded/faustremote/RemoteServer all
	$(MAKE) -C embedded/faustremote all

win32 :
	$(MAKE) -C compiler -f $(MAKEFILE) prefix=$(prefix) CXX=$(CROSS)g++
	$(MAKE) -C architecture/osclib CXX=$(CROSS)g++ system=Win32

debug :
	$(MAKE) -C compiler debug -f $(MAKEFILE) prefix=$(prefix)

plugin :
	$(MAKE) -C compiler plugin -f $(MAKEFILE) prefix=$(prefix)

ios :
	$(MAKE) -C compiler ios -f $(MAKEFILE) prefix=$(prefix)

ios-llvm :
	$(MAKE) -C compiler ios-llvm -f $(MAKEFILE) prefix=$(prefix)

asmjs :
	$(MAKE) -C compiler asmjs -f $(MAKEFILE) prefix=$(prefix)

wasm :
	$(MAKE) -C compiler wasm -f $(MAKEFILE) prefix=$(prefix)

light :
	$(MAKE) -C compiler light -f $(MAKEFILE) prefix=$(prefix)

sound2faust :

	$(MAKE) -C tools/sound2faust

bench :

	$(MAKE) -C tools/benchmark

.PHONY: clean depend install uninstall dist parser help

help :
	@echo "Usage : 'make; sudo make install'"
	@echo "For http support : 'make httpd; make; sudo make install' (requires GNU libmicrohttpd)"
	@echo "make or make all : compile the Faust compiler and osc support library"
	@echo "make httpd : compile httpdlib (requires GNU libmicrohttpd)"
	@echo "make dynamic : compile httpd & osc supports as dynamic libraries"
	@echo "make asmjs : compile asmjs libfaust.js"
	@echo "make wasm : compile wasm libfaust-wasm.js"
	@echo "make universal : on OSX, compile 32/64bits version of compiler and libraries"
	@echo "make light : only compile C/C++ backend (to avoid dependency with LLVM)"
	@echo "make debug : produce a debug version of compiler and libraries"
	@echo "make sound2faust : compile sound to DSP file converter"
	@echo "make remote : compile remote components used by FaustLive"
	@echo "make parser : generate the parser from the lex and yacc files"
	@echo "make clean : remove all object files"
	@echo "make doc : generate the documentation using doxygen"
	@echo "make doclib : generate the documentation of the faust libraries"
	@echo "make install : install the compiler, tools and the architecture files in $(prefix)/bin $(prefix)/share/faust $(prefix)/include/faust"
	@echo "make uninstall : undo what install did"
	@echo "make dist : make a Faust distribution as a .zip file"
	@echo "make log : make a changelog file"

parser :
	$(MAKE) -C compiler -f $(MAKEFILE) parser

clean :
	$(MAKE) -C compiler -f $(MAKEFILE) clean
	$(MAKE) -C architecture/osclib clean
	$(MAKE) -C architecture/httpdlib/src clean
	$(MAKE) -C embedded/faustremote/RemoteServer clean
	$(MAKE) -C embedded/faustremote clean
	$(MAKE) -C tools/sound2faust clean
	$(MAKE) -C tools/benchmark clean

depend :
	$(MAKE) -C compiler -f $(MAKEFILE) depend
	$(MAKE) -C architecture/osclib depend
	$(MAKE) -C architecture/httpdlib/src depend

doc :
	$(MAKE) -C compiler -f $(MAKEFILE) doc

doclib :
	./libraries/generateDoc

man :
	pandoc --standalone --to man compiler/README.md -o faust.1

install :
	# install faust itself
	mkdir -p $(prefix)/bin/
	mkdir -p $(prefix)/lib/
	mkdir -p $(prefix)/include/
	mkdir -p $(prefix)/include/faust/
	mkdir -p $(prefix)/include/faust/osc/
	mkdir -p $(prefix)/include/faust/dsp/
	mkdir -p $(prefix)/share/faust
	([ -e compiler/faust ] && install compiler/faust $(prefix)/bin/)  || echo faust not available
	([ -e compiler/libfaust.$(LIB_EXT) ] && install compiler/libfaust.$(LIB_EXT) $(prefix)/lib/) || echo libfaust.$(LIB_EXT) not available
	([ -e compiler/libfaust.a ] && install compiler/libfaust.a $(prefix)/lib/) || echo libfaust.a not available
	cp compiler/generator/libfaust.h  $(prefix)/include/faust/dsp/
	cp compiler/generator/libfaust-c.h  $(prefix)/include/faust/dsp/
	cp compiler/generator/llvm/llvm-dsp.h  $(prefix)/include/faust/dsp/
	cp compiler/generator/llvm/llvm-c-dsp.h  $(prefix)/include/faust/dsp/
	cp compiler/generator/interpreter/interpreter-dsp.h  $(prefix)/include/faust/dsp/
	cp compiler/generator/wasm/wasm-dsp.h  $(prefix)/include/faust/dsp/
	([ -e compiler/scheduler.ll ] && chmod gou+r compiler/scheduler.ll) || echo scheduler.ll not available
	([ -e compiler/scheduler.ll ] && cp compiler/scheduler.ll $(prefix)/lib/faust) || echo scheduler.ll not available

	# install architecture and faust library files
	cp architecture/*.c $(prefix)/share/faust/
	cp architecture/*.rs $(prefix)/share/faust/
	cp architecture/*.cpp $(prefix)/share/faust/
	cp architecture/*.java $(prefix)/share/faust/
	cp architecture/*.js $(prefix)/share/faust/
	cp architecture/*.a $(prefix)/share/faust/
	cp libraries/old/*.lib $(prefix)/share/faust/
	cp libraries/*.lib $(prefix)/share/faust/

	# This is needed by faust2lv2 -gui / lv2ui.cpp.
	cp architecture/lv2qtgui.h $(prefix)/share/faust/

	# This is needed by faust2faustvst -gui / faustvst.cpp.
	cp architecture/faustvstqt.h $(prefix)/share/faust/

	# install iOS
	rm -rf $(prefix)/share/faust/iOS
	cp -r architecture/iOS $(prefix)/share/faust/
	cp -r architecture/osclib $(prefix)/share/faust
	rm -rf $(prefix)/share/faust/iOS/DerivedData/
	# install smartKeyboard
	rm -rf $(prefix)/share/faust/smartKeyboard
	cp -r architecture/smartKeyboard $(prefix)/share/faust/
	# install Juce
	rm -rf $(prefix)/share/faust/juce
	cp -r architecture/juce $(prefix)/share/faust/
	# install AU
	rm -rf $(prefix)/share/faust/AU/
	cp -r architecture/AU $(prefix)/share/faust/
	# install Android
	rm -rf $(prefix)/share/faust/android
	cp -r architecture/android $(prefix)/share/faust/
	# install APIs
	rm -rf $(prefix)/share/faust/api/
	cp -r architecture/api $(prefix)/share/faust/
	# install nodejs
	rm -rf $(prefix)/share/faust/nodejs/
	cp -r architecture/nodejs $(prefix)/share/faust/
	# install Max/MSP
	rm -rf $(prefix)/share/faust/max-msp/
	cp -r architecture/max-msp $(prefix)/share/faust/
	#install unity
	rm -rf $(prefix)/share/faust/unity
	cp -r architecture/unity $(prefix)/share/faust/

	# install math documentation files
	cp architecture/mathdoctexts-*.txt $(prefix)/share/faust/
	cp architecture/latexheader.tex $(prefix)/share/faust/

	# install additional binary libraries (osc, http,...)
	([ -e architecture/httpdlib/libHTTPDFaust.a ] && cp architecture/httpdlib/libHTTPDFaust.a $(prefix)/lib/) || echo libHTTPDFaust.a not available
	([ -e architecture/httpdlib/libHTTPDFaust.$(LIB_EXT) ] && cp architecture/httpdlib/libHTTPDFaust.$(LIB_EXT) $(prefix)/lib/) || echo libHTTPDFaust.$(LIB_EXT) not available

	([ -e architecture/osclib/libOSCFaust.a ] && cp architecture/osclib/libOSCFaust.a $(prefix)/lib/) || echo libOSCFaust.a not available
	([ -e architecture/osclib/libOSCFaust.$(LIB_EXT) ] && cp -a architecture/osclib/libOSCFaust*.$(LIB_EXT)* $(prefix)/lib/) || echo libOSCFaust.$(LIB_EXT) not available

	cp -r architecture/httpdlib/html/js $(prefix)/share/faust/js
	([ -e architecture/httpdlib/src/hexa/stylesheet ] && cp architecture/httpdlib/src/hexa/stylesheet $(prefix)/share/faust/js/stylesheet.js) || echo stylesheet not available
	([ -e architecture/httpdlib/src/hexa/jsscripts ] && cp architecture/httpdlib/src/hexa/jsscripts $(prefix)/share/faust/js/jsscripts.js) || echo jsscripts not available

	# install includes files for architectures
	cp -r architecture/faust $(prefix)/include/

	# install additional includes files for binary libraries  (osc, http,...)
	cp architecture/osclib/faust/faust/OSCControler.h $(prefix)/include/faust/gui/
	cp architecture/osclib/faust/faust/osc/*.h $(prefix)/include/faust/osc/
	cp architecture/httpdlib/src/include/*.h $(prefix)/include/faust/gui/

	# install faust2xxx tools
	make -C tools/faust2appls install

	# install sound converter
	[ -e tools/sound2faust/sound2faust ] && make -C tools/sound2faust install || echo sound2faust not compiled

	# install faustremote
	([ -e embedded/faustremote/libfaustremote.a ] &&  install embedded/faustremote/libfaustremote.a  $(prefix)/lib/) || echo remote not compiled
	cp embedded/faustremote/remote-dsp.h  $(prefix)/include/faust/dsp/

	# install webaudio
	cp -r architecture/webaudio $(prefix)/share/faust/

	# install Max/MSP
	cp -r architecture/max-msp $(prefix)/share/faust/

	# install benchmark tools
	rm -rf $(prefix)/share/faust/iOS-bench
	cp -r tools/benchmark/iOS-bench $(prefix)/share/faust/
	cp tools/benchmark/faustbench $(prefix)/bin/
	cp tools/benchmark/faustbench.cpp $(prefix)/share/faust/
	([ -e tools/benchmark/faustbench-llvm ]) && install tools/benchmark/faustbench $(prefix)/bin/ || echo faustbench-llvm not found
	([ -e tools/benchmark/faustbench-llvm-interp ]) && install tools/benchmark/faustbench-llvm $(prefix)/bin/ || echo faustbench-llvm-interp not found

	# install Faust man file
	([ -e faust.1 ]) && (install -d $(prefix)/share/man/man1/; install faust.1 $(prefix)/share/man/man1) || echo faust.1 not found

uninstall :
	rm -f $(addprefix $(prefix)/lib/, libfaust.a libfaust.$(LIB_EXT) libHTTPDFaust.a libHTTPDFaust.$(LIB_EXT) libOSCFaust.a libOSCFaust*.$(LIB_EXT)* libfaustremote.a)
	rm -rf $(prefix)/share/faust/
	rm -rf $(prefix)/include/faust/
	rm -f $(prefix)/bin/faust$(EXE)
	rm -f $(prefix)/bin/RemoteServer$(EXE)
	make -C tools/faust2appls uninstall
	rm -f $(prefix)/bin/sound2faust$(EXE)
	rm -f $(prefix)/bin/faustbench
	rm -f $(prefix)/share/man/man1/faust.1

# make a faust distribution .zip file
dist :
	git archive --format=tar.gz -o faust-$(version).tgz --prefix=faust-$(version)/ HEAD

log :
	git log --oneline --date-order --reverse --after={2014-05-19} master >log-$(version)

# Make Debian packages. This builds a package from the current HEAD in a
# subdirectory named $(debdist). It also creates the source archive that goes
# along with it. All files will be created in the toplevel Faust source
# directory.

# To make this work, you need to have the Debian package toolchain (debuild
# and friends) installed. Also make sure you have your DEBEMAIL and
# DEBFULLNAME environment variables set up as explained in the debchange(1)
# manual page. These are needed to create changelog entries and in order to
# sign the Debian packages created with 'make deb' and 'make debsrc'.

# The typical workflow is as follows:

# 1. Run 'make debchange' once to create a new debian/changelog entry. You
# *must* do this once so that debuild knows about the proper version number of
# the package.

# 2. Run 'make deb' to build a signed binary package. Or 'make deb-us' for an
# unsigned one.

# If you only need the binary package for local deployment then you're done.
# Otherwise proceed to step 3.

# 3. Run 'make debsrc' to create a signed Debian source package which can be
# uploaded, e.g, to Launchpad using 'dput'. Or 'make debsrc-us' for an
# unsigned package.

# 4. Run 'make debclean' to get rid of any files that were created in steps 2
# and 3.

# The Debian version gets derived from the package version $(version) as well
# as the date and serial number of the last commit.
debversion = $(version)+git$(shell git log -1 --format=%cd --date=short 2>/dev/null | sed -e 's/-//g')+$(shell git rev-list --count HEAD 2>/dev/null)
# Debian revision number of the package.
debrevision = 1
# Source tarball and folder.
debsrc = faust2_$(debversion).orig.tar.gz
debdist = faust2-$(debversion)

submodules = libraries

# This is used for automatically generated debian/changelog entries (cf. 'make
# debchange'). Adjust as needed.
debmsg = "Build from latest upstream source."
debprio = "low"

.PHONY: debversion debchange debclean deb debsrc deb-us debsrc-us

debversion:
	@echo $(debversion)

debchange:
	dch -u $(debprio) -v $(debversion)-$(debrevision) $(debmsg) && dch -r ""

debclean:
	rm -rf $(debdist)
	rm -f faust2_$(version)+git* faust2-dbgsym_$(version)+git*

deb: $(debsrc)
	rm -rf $(debdist)
	tar xfz $(debsrc)
# Here we just copy debian/ from the working copy since it might have changes
# that haven't been committed yet.
	cd $(debdist) && cp -R ../debian . && debuild $(DEBUILD_FLAGS)
	rm -rf $(debdist)

debsrc:
	$(MAKE) deb DEBUILD_FLAGS=-S

deb-us:
	$(MAKE) deb DEBUILD_FLAGS="-us -uc"

debsrc-us:
	$(MAKE) deb DEBUILD_FLAGS="-S -us -uc"

$(debsrc) :
	rm -rf $(debdist)
# Make sure that the submodules are initialized.
	git submodule update --init
# Grab the main source.
	git archive --format=tar.gz --prefix=$(debdist)/ HEAD | tar xfz -
# Grab the submodules.
	for x in $(submodules); do (cd $(debdist) && rm -rf $$x && git -C ../$$x archive --format=tar.gz --prefix=$$x/ HEAD | tar xfz -); done
# Create the source tarball.
	tar cfz $(debsrc) $(debdist)
	rm -rf $(debdist)

# DO NOT DELETE
