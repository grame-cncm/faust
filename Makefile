version := 2.0.a48

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

prefix := $(DESTDIR)$(PREFIX)
arch   := $(wildcard architecture/*.*)
mfiles := $(wildcard examples/Makefile.*)
vname := faust-$(version)-$(shell date +%y%m%d.%H%M%S)
zname := faust-$(version)

.PHONY: all world dynamic httpd remote win32 ios ios-llvm emcc sound2faust

all :
	$(MAKE) -C compiler -f $(MAKEFILE) prefix=$(prefix)
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

httpd :
	$(MAKE) -C architecture/httpdlib/src all

remote :
	$(MAKE) -C embedded/faustremote/RemoteServer all
	$(MAKE) -C embedded/faustremote all

win32 :
	$(MAKE) -C compiler -f $(MAKEFILE) prefix=$(prefix) CXX=$(CROSS)g++
	$(MAKE) -C architecture/osclib CXX=$(CROSS)g++ system=Win32

ios :
	$(MAKE) -C compiler ios -f $(MAKEFILE) prefix=$(prefix)

ios-llvm :
	$(MAKE) -C compiler ios-llvm -f $(MAKEFILE) prefix=$(prefix)

emcc :
	$(MAKE) -C compiler emcc -f $(MAKEFILE) prefix=$(prefix)

sound2faust:

	$(MAKE) -C tools/sound2faust

.PHONY: clean depend install uninstall dist parser help

help :
	@echo "Usage : 'make; sudo make install'"
	@echo "For http support : 'make httpd; make; sudo make install' (requires GNU libmicrohttpd)"
	@echo "make or make all : compile the Faust compiler and osc support library"
	@echo "make httpd : compile httpdlib (requires GNU libmicrohttpd)"
	@echo "make dynamic : compile httpd & osc supports as dynamic libraries"
	@echo "make sound2faust : compile sound to DSP file converter"
	@echo "make remote : compile remote components used by FaustLive"
	@echo "make parser : generate the parser from the lex and yacc files"
	@echo "make clean : remove all object files"
	@echo "make doc : generate the documentation using doxygen"
	@echo "make install : install the compiler, tools and the architecture files in $(prefix)/bin $(prefix)/lib/faust $(prefix)/include/faust"
	@echo "make uninstall : undo what install did"
	@echo "make dist : make a Faust distribution as a .zip file"
	@echo "make log : make a changelog file"

parser :
	$(MAKE) -C compiler -f $(MAKEFILE) parser

clean :
	$(MAKE) -C compiler -f $(MAKEFILE) clean
	$(MAKE) -C examples clean
	$(MAKE) -C architecture/osclib clean
	$(MAKE) -C architecture/httpdlib/src clean
	$(MAKE) -C embedded/faustremote/RemoteServer clean
	$(MAKE) -C embedded/faustremote clean
	$(MAKE) -C tools/sound2faust clean

depend :
	$(MAKE) -C compiler -f $(MAKEFILE) depend
	$(MAKE) -C architecture/osclib depend
	$(MAKE) -C architecture/httpdlib/src depend


doc :
	$(MAKE) -C compiler -f $(MAKEFILE) doc


install :
	# install faust itself
	mkdir -p $(prefix)/bin/
	mkdir -p $(prefix)/include/
	mkdir -p $(prefix)/include/faust/
	mkdir -p $(prefix)/include/faust/osc/
	mkdir -p $(prefix)/include/faust/dsp/
	mkdir -p $(prefix)/lib/faust
	([ -e compiler/faust ] && install compiler/faust $(prefix)/bin/)  || echo faust not available
	([ -e compiler/libfaust.$(LIB_EXT) ] && install compiler/libfaust.$(LIB_EXT) $(prefix)/lib/) || echo libfaust.$(LIB_EXT) not available
	([ -e compiler/libfaust.a ] && install compiler/libfaust.a $(prefix)/lib/) || echo libfaust.a not available
	cp compiler/generator/llvm/llvm-dsp.h  $(prefix)/include/faust/dsp/
	cp compiler/generator/llvm/llvm-c-dsp.h  $(prefix)/include/faust/dsp/
	cp compiler/generator/interpreter/interpreter-dsp.h  $(prefix)/include/faust/dsp/
	([ -e compiler/scheduler.ll ] && chmod gou+r compiler/scheduler.ll) || echo scheduler.ll not available
	([ -e compiler/scheduler.ll ] && cp compiler/scheduler.ll $(prefix)/lib/faust) || echo scheduler.ll not available

	# install architecture and faust library files
	cp architecture/*.c $(prefix)/lib/faust/
	cp architecture/*.cpp $(prefix)/lib/faust/
	cp architecture/*.java $(prefix)/lib/faust/
	cp architecture/*.js $(prefix)/lib/faust/
	cp architecture/*.html $(prefix)/lib/faust/
	cp architecture/*.lib $(prefix)/lib/faust/
	# This is needed by faust2lv2 -gui / lv2ui.cpp.
	cp architecture/lv2qtgui.h $(prefix)/lib/faust/
	# This is needed by faust2faustvst -gui / faustvst.cpp.
	cp architecture/faustvstqt.h $(prefix)/lib/faust/
	# install iOS
	rm -rf $(prefix)/lib/faust/iOS
	cp -r architecture/iOS $(prefix)/lib/faust/
	cp -r architecture/osclib $(prefix)/lib/faust/iOS
	rm -rf $(prefix)/lib/faust/iOS/DerivedData/
	rm -rf $(prefix)/lib/faust/iOSKeyboard
	cp -r architecture/iOSKeyboard $(prefix)/lib/faust/
	# install AU
	rm -rf $(prefix)/lib/faust/AU/
	cp -r architecture/AU $(prefix)/lib/faust/
	cp -r architecture/android $(prefix)/lib/faust/
	cp -r architecture/max-msp $(prefix)/lib/faust/

	# install math documentation files
	cp architecture/mathdoctexts-*.txt $(prefix)/lib/faust/
	cp architecture/latexheader.tex $(prefix)/lib/faust/
	# install additional binary libraries (osc, http,...)
	([ -e architecture/httpdlib/libHTTPDFaust.a ] && cp architecture/httpdlib/libHTTPDFaust.a $(prefix)/lib/) || echo libHTTPDFaust.a not available
	([ -e architecture/httpdlib/libHTTPDFaust.$(LIB_EXT) ] && cp architecture/httpdlib/libHTTPDFaust.$(LIB_EXT) $(prefix)/lib/) || echo libHTTPDFaust.$(LIB_EXT) not available

	([ -e architecture/osclib/libOSCFaust.a ] && cp architecture/osclib/libOSCFaust.a $(prefix)/lib/) || echo libOSCFaust.a not available
	([ -e architecture/osclib/libOSCFaust.$(LIB_EXT) ] && cp -a architecture/osclib/libOSCFaust*.$(LIB_EXT)* $(prefix)/lib/) || echo libOSCFaust.$(LIB_EXT) not available

	cp -r architecture/httpdlib/html/js $(prefix)/lib/faust/js
	([ -e architecture/httpdlib/src/hexa/stylesheet ] && cp architecture/httpdlib/src/hexa/stylesheet $(prefix)/lib/faust/js/stylesheet.js) || echo stylesheet not available
	([ -e architecture/httpdlib/src/hexa/jsscripts ] && cp architecture/httpdlib/src/hexa/jsscripts $(prefix)/lib/faust/js/jsscripts.js) || echo jsscripts not available
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
	cp -r architecture/webaudio $(prefix)/lib/faust/
	# install Max/MSP
	cp -r architecture/max-msp $(prefix)/lib/faust/

uninstall :
	rm -f $(addprefix $(prefix)/lib/, libfaust.a libfaust.$(LIB_EXT) libHTTPDFaust.a libHTTPDFaust.$(LIB_EXT) libOSCFaust.a libOSCFaust*.$(LIB_EXT)* libfaustremote.a)
	rm -rf $(prefix)/lib/faust/
	rm -rf $(prefix)/include/faust/
	rm -f $(prefix)/bin/faust$(EXE)
	rm -f $(prefix)/bin/RemoteServer$(EXE)
	make -C tools/faust2appls uninstall
	rm -f $(prefix)/bin/sound2faust$(EXE)

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

# This is used for automatically generated debian/changelog entries (cf. 'make
# debchange'). Adjust as needed.
debmsg = "Build from latest upstream source."
debprio = "low"

.PHONY: debversion debchange debclean deb debsrc deb-us debsrc-us

debversion:
	@echo $(debversion)

debchange:
	dch -u $(debprio) -v $(debversion)-$(debrevision) $(debmsg) && dch -r ""

debclean: $(debsrc)
	rm -rf $(debdist)
	rm -f faust2_$(version)+git*

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
	git archive --format=tar.gz -o $(debsrc) --prefix=$(debdist)/ HEAD

# DO NOT DELETE
