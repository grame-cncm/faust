version := 2.76.0

system	?= $(shell uname -s)

-include user.mk
DESTDIR ?=
PREFIX ?= /usr/local
INSTALL_LIBDIR ?= lib
CROSS=i586-mingw32msvc-
BUILDLOCATION := build
DEBUGFOLDER := faustdebug
BINLOCATION := $(BUILDLOCATION)/bin
LIBLOCATION := $(BUILDLOCATION)/lib

MAKEFILE := Makefile.unix

prefix := $(DESTDIR)$(PREFIX)
arch   := $(wildcard architecture/*.*)
mfiles := $(wildcard examples/Makefile.*)
vname := faust-$(version)-$(shell date +%y%m%d.%H%M%S)
zname := faust-$(version)

.PHONY: all world benchmark remote ios ios-llvm wasm sound2faust

# The main targets

compiler : updatesubmodules
	$(MAKE) -C $(BUILDLOCATION) cmake BACKENDS=regular.cmake TARGETS=regular.cmake
	$(MAKE) -C $(BUILDLOCATION)

most : updatesubmodules
	$(MAKE) -C $(BUILDLOCATION) cmake BACKENDS=most.cmake TARGETS=most.cmake
	$(MAKE) -C $(BUILDLOCATION)

developer : updatesubmodules
	$(MAKE) -C $(BUILDLOCATION) cmake BACKENDS=all.cmake TARGETS=developer.cmake
	$(MAKE) -C $(BUILDLOCATION)

all : updatesubmodules
	$(MAKE) -C $(BUILDLOCATION) cmake BACKENDS=all.cmake TARGETS=all.cmake
	$(MAKE) -C $(BUILDLOCATION)

libsall : updatesubmodules
	$(MAKE) -C $(BUILDLOCATION) cmake BACKENDS=regular.cmake TARGETS=all.cmake
	$(MAKE) -C $(BUILDLOCATION)

travis : updatesubmodules
	$(MAKE) -C $(BUILDLOCATION) cmake BACKENDS=backends.cmake TARGETS=regular.cmake
	$(MAKE) -C $(BUILDLOCATION)

# Universal and native: special developer modes

universal :
	$(MAKE) -C $(BUILDLOCATION) universal
	@echo
	@echo "### Universal mode is ON"
	@echo "### You need to recompile"
	@echo "### Use 'make native' to revert"

native :
	$(MAKE) -C $(BUILDLOCATION) native
	@echo
	@echo "### Universal mode is OFF"
	@echo "### You need to recompile"

# make world (MAINTAINERS TARGET): This builds all the common targets for a
# fairly complete Faust installation: Faust compiler (including the LLVM
# backend) and library, sound2faust utility, OSC and HTTPD libraries (both
# static and dynamic).

# CAVEAT: END USERS should note that this target requires a substantial amount
# of additional dependencies (in particular, LLVM) which aren't readily
# pre-installed on most systems, hence you should NOT use this target (which
# is mostly aimed at package maintainers) unless you KNOW WHAT YOU'RE DOING.
# Don't complain if the target doesn't build for you, use one of the standard
# build targets instead. You have been warned! :)

# MAINTAINERS: Once the "remote" target is readily supported on most
# platforms, it should be added here. This requires Jack2 1.9.10 or later
# which isn't regularly installed on most systems at present, so we skip this
# target for now.

world : all 
	$(MAKE) -C tools/sound2faust

benchmark : developer
	$(MAKE) -C tools/benchmark all

remote : developer
	$(MAKE) -C embedded/faustremote/RemoteServer all
	$(MAKE) -C embedded/faustremote all

debug :
	$(MAKE) -C $(BUILDLOCATION) FAUSTDIR=faustdebug CMAKEOPT=-DCMAKE_BUILD_TYPE=Debug
#	$(MAKE) -C compiler debug -f $(MAKEFILE) prefix=$(prefix)

ioslib :
	$(MAKE) -C $(BUILDLOCATION) ioslib

wasm :
	$(MAKE) -C $(BUILDLOCATION) wasmlib
	$(MAKE) -C $(BUILDLOCATION) cmake WORKLET=on
	$(MAKE) -C $(BUILDLOCATION) wasmglue
	# Hack : be sure to use LIB_NAME define in build/wasmglue/CMakeLists.txt
	echo "export default FaustModule;" >> $(BUILDLOCATION)/lib/libfaust-worklet-glue.js
	# Fix for EMCC codegen bug
	echo "var tempDouble, tempI64;" >> $(BUILDLOCATION)/lib/libfaust-worklet-glue.js
	$(MAKE) -C $(BUILDLOCATION) cmake WORKLET=off
	$(MAKE) -C $(BUILDLOCATION) wasmglue

sound2faust :
	$(MAKE) -C tools/sound2faust

.PHONY: clean install uninstall dist parser help format

help :
	@echo "===== Faust main makefile ====="
	@echo "Main targets"
	@echo " 'compiler' (def): builds the Faust compiler (without the LLVM backend), and the Faust osc and httpd libraries"
	@echo " 'most'          : builds the Faust compiler with LLVM backend and every static libraries"
	@echo " 'developer'     : builds the Faust compiler with every possible backends and every static libraries"
	@echo " 'all'           : builds the Faust compiler with every possible backends and every static and dynamic libraries"
	@echo " 'libsall'       : builds the Faust compiler (without the LLVM backend) and includes all the static and dynamic libraries"
	@echo
	@echo " 'install'       : install the compiler, tools and the architecture files in $(prefix)/bin $(prefix)/share/faust $(prefix)/include/faust"
	@echo " 'clean'         : remove all object files (but keep build configurations)"
	@echo " 'distclean'     : clean everything by removing the build/faustdir folder"
	@echo 
	@echo "Other targets"
	@echo " 'debug'         : similar to 'all' target but with debug info. Output is in $(BUILDLOCATION)/$(DEBUGFOLDER)"
	@echo " 'wasm'          : builds the Faust WebAssembly libraries"
	@echo " 'benchmark'     : builds the benchmark tools (see tools/benchmark)"
	@echo " 'remote'        : builds the libfaustremote.a library and the Faust RemoteServer"
	@echo " 'sound2faust'   : builds the sound2faust utilities (requires libsndfile)"
	@echo " 'parser'        : generates the parser from the lex and yacc files"
	@echo
	@echo "Distribution target"
	@echo " 'world'         : the 'all' target and sound2faust"
	@echo
	@echo "Platform specific targets:"
	@echo " 'universal'     : [MacOSX] switch to universal binaries mode"
	@echo " 'native'        : [MacOSX] switch to native mode"
	@echo " 'ioslib'        : [iOS] build the Faust static library for iOS"
	@echo
	@echo "Utilities targets:"
	@echo " 'man'              : generate the Faust man page"
	@echo " 'doc'              : generate the documentation using doxygen"
	@echo " 'doclib'           : generate the documentation of the Faust libraries"
	@echo " 'updatesubmodules' : update the libraries submodule"
	@echo " 'devinstall'       : install the benchmark tools"
	@echo " 'uninstall'        : undo what install did"
	@echo " 'dist'             : make a Faust distribution as a .zip file"
	@echo " 'log'              : make a changelog file"
	@echo " 'format'           : clang-format all src files"
	@echo

readme:
	@cat resources/man-header.txt
	@build/bin/faust -h | sed -e 's/\(-[a-zA-Z][a-zA-Z]*\)/**\1**/' \
			 | sed -e 's/\(--[a-zA-Z][a-zA-Z-]*\)/**\1**/' \
			 | sed -e 's/</\\</g' \
			 | sed '/-----*/ G' \
			 | sed '/\.$$/ G' 
	@cat resources/man-footer.txt
		 
	
parser :
	$(MAKE) -C compiler/parser

clean :
	$(MAKE) -C build clean
	$(MAKE) -C embedded/faustremote/RemoteServer clean
	$(MAKE) -C embedded/faustremote clean
	$(MAKE) -C tools/sound2faust clean
	$(MAKE) -C tools/benchmark clean

distclean :
	rm -rf build/faustdir

doc: $(wildcard compiler/*.cpp) $(wildcard compiler/*/*.cpp) $(wildcard compiler/*/*.h) $(wildcard compiler/*/*.hh)
	cd documentation/libfaust && doxygen
	cd documentation/libfaustremote && doxygen
	cd documentation/compiler && doxygen
	

format :
	find compiler -path compiler/parser -prune -o -iname '*.cpp' -execdir clang-format -i -style=file {} \;
	find compiler -path compiler/parser -prune -o -iname '*.hh' -execdir clang-format -i -style=file {} \;
	find compiler -path compiler/parser -prune -o -iname '*.h' -execdir clang-format -i -style=file {} \;

# the target 'lib' can be used to init and update the libraries submodule
updatesubmodules :
	if test -d .git; then git submodule update --init --recursive; fi


doclib : updatesubmodules
	./libraries/generateDoc

man :
	make -C documentation/man man

install :
	make -C $(BUILDLOCATION) install DESTDIR=$(DESTDIR) PREFIX=$(PREFIX)

uninstall :
	make -C $(BUILDLOCATION) uninstall


# install benchmark tools
devinstall:
	$(MAKE) -C tools/benchmark install

# make a Faust distribution tarball
dist = faust-$(version)
submodules = libraries tools/faust2ck
dist :
	rm -rf $(dist)
# Make sure that the submodules are initialized.
	git submodule update --init
# Grab the main source.
	git archive --format=tar.gz --prefix=$(dist)/ HEAD | tar xfz -
# Grab the submodules.
	for x in $(submodules); do (cd $(dist) && rm -rf $$x && git -C ../$$x archive --format=tar.gz --prefix=$$x/ HEAD | tar xfz -); done
# Create the source tarball.
	tar cfz $(dist).tar.gz $(dist)
	rm -rf $(dist)

# this does the same, but uses the $(debversion) instead (see below) which
# includes the actual git revision number and hash (useful for git snapshots)
dist-snapshot :
	$(MAKE) dist dist=faust-$(debversion)

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
debsrc = faust_$(debversion).orig.tar.gz
debdist = faust-$(debversion)

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
	rm -f faust_$(version)+git* faust-dbgsym_$(version)+git*

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
