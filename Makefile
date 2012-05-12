version := 2.0.a3

DESTDIR ?= 
PREFIX ?= /usr/local
CROSS=i586-mingw32msvc-

MAKEFILE := Makefile.unix

prefix := $(DESTDIR)$(PREFIX)
arch   := $(wildcard architecture/*.*)
mfiles := $(wildcard examples/Makefile.*)
vname := faust-$(version)-$(shell date +%y%m%d.%H%M%S)
zname := faust-$(version)

all :
	$(MAKE) -C compiler -f $(MAKEFILE) prefix=$(prefix)
	$(MAKE) -C architecture/osclib

lib :
	$(MAKE) -C compiler -f $(MAKEFILE) libfaust prefix=$(prefix)

httpd :
	$(MAKE) -C architecture/httpdlib/src

win32 :
	$(MAKE) -C compiler -f $(MAKEFILE) prefix=$(prefix) CXX=$(CROSS)g++
	$(MAKE) -C architecture/osclib CXX=$(CROSS)g++ system=Win32


.PHONY: clean depend install uninstall dist parser help

help :
	@echo "make or make all : compiler the faust compiler"
	@echo "make parser : generate the parser from the lex and yacc files"
	@echo "make clean : remove all object files"
	@echo "make doc : generate the documentation using doxygen"
	@echo "make install : install the compiler and the architecture files in $(prefix)/bin $(prefix)/lib/faust $(prefix)/include/faust"
	@echo "make uninstall : undo what install did"
	@echo "make dist : make a tar.gz file ready for distribution"
	@echo "make log : make a changelog file"
	@echo "make zip : make a windows binary distribution"

parser :
	$(MAKE) -C compiler -f $(MAKEFILE) parser

clean :
	$(MAKE) -C compiler -f $(MAKEFILE) clean
	$(MAKE) -C examples clean
	$(MAKE) -C architecture/osclib clean
	$(MAKE) -C architecture/httpdlib/src clean

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
	mkdir -p $(prefix)/lib/faust
	install compiler/faust $(prefix)/bin/
	install compiler/libfaust.a $(prefix)/lib/faust
	# install architecture and faust library files
	cp architecture/*.c $(prefix)/lib/faust/
	cp architecture/*.cpp $(prefix)/lib/faust/
	cp architecture/*.java $(prefix)/lib/faust/
	cp architecture/*.js $(prefix)/lib/faust/
	cp architecture/*.html $(prefix)/lib/faust/
	cp architecture/*.lib $(prefix)/lib/faust/
	# install math documentation files
	cp architecture/mathdoctexts-*.txt $(prefix)/lib/faust/
	cp architecture/latexheader.tex $(prefix)/lib/faust/
	# install additional binary libraries (osc, http,...)
	([ -e architecture/httpdlib/libHTTPDFaust.a ] && cp architecture/httpdlib/libHTTPDFaust.a $(prefix)/lib/faust/) || echo libHTTPDFaust not available	
	cp architecture/osclib/*.a $(prefix)/lib/faust/
	# install includes files for architectures
	cp -r architecture/faust $(prefix)/include/
	# install additional includes files for binary libraries  (osc, http,...)
	cp architecture/osclib/faust/include/OSCControler.h $(prefix)/include/faust/gui/
	cp architecture/httpdlib/src/include/*.h $(prefix)/include/faust/gui/
	# install faust2xxx tools
	make -C tools/faust2appls install


uninstall :
	rm -rf $(prefix)/lib/faust/
	rm -rf $(prefix)/include/faust/
	rm -f $(prefix)/bin/faust
	make -C tools/faust2appls uninstall

dist :
	$(MAKE) -C compiler -f $(MAKEFILE) clean
	$(MAKE) -C examples clean
	mkdir -p faust-$(version)
	cp README WHATSNEW COPYING Makefile faust-$(version)
	cp -r architecture faust-$(version)
	cp -r benchmark faust-$(version)
	cp -r compiler faust-$(version)
	cp -r documentation faust-$(version)
	cp -r examples faust-$(version)
	cp -r syntax-highlighting faust-$(version)
	cp -r tools faust-$(version)
	cp -r windows faust-$(version)
	find faust-$(version) -name CVS | xargs rm -rf
	find faust-$(version) -name "*~" | xargs rm -rf
	find faust-$(version) -name ".#*" | xargs rm -rf
	find faust-$(version) -name "*.o" | xargs rm -rf
	rm -f faust-$(version).tar.gz
	tar czfv faust-$(version).tar.gz faust-$(version)
	rm -rf faust-$(version)

# make a faust distribution by cloning the git repository
clonedist :
	git clone git://faudiostream.git.sourceforge.net/gitroot/faudiostream/faudiostream faust-$(version)
	rm -rf faust-$(version)/.git
	rm -f faust-$(version).tar.gz
	tar czfv faust-$(version).tar.gz faust-$(version)
	rm -rf faust-$(version)

archive :
	$(MAKE) -C compiler -f $(MAKEFILE) clean
	$(MAKE) -C examples clean
	mkdir -p $(vname)
	cp README COPYING Makefile $(vname)
	cp -r architecture $(vname)
	cp -r benchmark $(vname)
	cp -r compiler $(vname)
	cp -r documentation $(vname)
	cp -r examples $(vname)
	cp -r syntax-highlighting $(vname)
	cp -r tools $(vname)
	cp -r windows $(vname)
	find $(vname) -name "*~" | xargs rm -rf
	tar czfv $(vname).tar.gz $(vname)
	rm -rf $(vname)

zip :
	mkdir -p $(zname)
	cp README COPYING Makefile $(zname)
	cp -r architecture $(zname)
	cp -r benchmark $(zname)
	cp    compiler/faust.exe $(zname)
	cp -r examples $(zname)
	cp -r documentation $(zname)
	cp -r syntax-highlighting $(zname)
	cp -r tools $(zname)
	cp -r windows $(zname)
	find $(zname) -name "*~" | xargs rm -rf
	find $(zname) -name CVS | xargs rm -rf
	find $(zname) -name ".#*" | xargs rm -rf
	zip -r $(zname).zip $(zname)
	rm -rf $(zname)

log :
	cvs2cl --fsf

# DO NOT DELETE
