version := 0.9.12

DESTDIR ?= 
PREFIX ?= /usr/local

MAKEFILE := Makefile.unix

prefix := $(DESTDIR)$(PREFIX)
arch   := $(wildcard architecture/*.*)
mfiles := $(wildcard examples/Makefile.*)
vname := faust-$(version)-$(shell date +%y%m%d.%H%M%S)
zname := faust-$(version)

all :
	$(MAKE) -C compiler -f $(MAKEFILE)


.PHONY: clean depend install ininstall dist parser help

help :
	@echo "make or make all : compiler the faust compiler"
	@echo "make parser : generate the parser from the lex and yacc files"
	@echo "make clean : remove all object files"
	@echo "make doc : generate the documentation using doxygen"
	@echo "make install : install the compiler and the architecture files in $(prefix)/bin $(prefix)/lib/faust"
	@echo "make uninstall : undo what install did"
	@echo "make dist : make a tar.gz file ready for distribution"
	@echo "make log : make a changelog file"
	@echo "make zip : make a windows binary distribution"

parser :
	$(MAKE) -C compiler -f $(MAKEFILE) parser

clean :
	$(MAKE) -C compiler -f $(MAKEFILE) clean
	$(MAKE) -C examples clean

depend :
	$(MAKE) -C compiler -f $(MAKEFILE) depend


doc :
	$(MAKE) -C compiler -f $(MAKEFILE) doc


install :
	mkdir -p $(prefix)/lib/faust/
	mkdir -p $(prefix)/bin/
	install compiler/faust $(prefix)/bin/
	install -m 0644 $(arch) $(prefix)/lib/faust/
	rm -rf $(prefix)/lib/faust/VST
	cp -r architecture/VST $(prefix)/lib/faust/
	rm -rf $(prefix)/lib/faust/iPhone
	cp -r architecture/iPhone $(prefix)/lib/faust/
	find $(prefix)/lib/faust/ -name CVS | xargs rm -rf
	install -m 0644 $(mfiles) $(prefix)/lib/faust/


uninstall :
	rm -rf $(prefix)/lib/faust/
	rm -f $(prefix)/bin/faust

dist :
	$(MAKE) -C compiler -f $(MAKEFILE) clean
	$(MAKE) -C examples clean
	mkdir -p faust-$(version)
	cp README COPYING Makefile faust-$(version)
	cp -r architecture faust-$(version)
	cp -r benchmark faust-$(version)
	cp -r compiler faust-$(version)
	cp -r documentation faust-$(version)
	cp -r examples faust-$(version)
	cp -r syntax-highlighting faust-$(version)
	cp -r tools faust-$(version)
	find faust-$(version) -name CVS | xargs rm -rf
	find faust-$(version) -name "*~" | xargs rm -rf
	find faust-$(version) -name ".#*" | xargs rm -rf
	find faust-$(version) -name "*.o" | xargs rm -rf
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
	find $(vname) -name "*~" | xargs rm -rf
	tar czfv $(vname).tar.gz $(vname)
	rm -rf $(vname)

zip :
	mkdir -p $(zname)
	cp README COPYING Makefile $(zname)
	cp -r architecture $(zname)
	cp    compiler/faust.exe $(zname)
	cp -r examples $(zname)
	cp -r documentation $(zname)
	cp -r syntax-highlighting $(zname)
	cp -r tools $(zname)
	find $(zname) -name "*~" | xargs rm -rf
	find $(zname) -name CVS | xargs rm -rf
	find $(zname) -name ".#*" | xargs rm -rf
	zip -r $(zname).zip $(zname)
	rm -rf $(zname)

log :
	cvs2cl --fsf
# DO NOT DELETE
