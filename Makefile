version := 0.9.3
prefix := /usr/local
arch := $(wildcard architecture/*.*)
mfiles := $(wildcard examples/Makefile.*)

all : 
	$(MAKE) -C compiler


.PHONY: clean depend install ininstall dist

clean :
	$(MAKE) -C compiler clean

depend :
	$(MAKE) -C compiler depend

	
doc :
	$(MAKE) -C compiler doc

	
install :
	mkdir -p $(prefix)/lib/faust/
	install compiler/faust $(prefix)/bin
	install $(arch) $(prefix)/lib/faust/
	install $(mfiles) $(prefix)/lib/faust/

	
uninstall :
	rm -rf $(prefix)/lib/faust/
	rm -f $(prefix)/bin/faust

dist :
	$(MAKE) -C compiler clean
	$(MAKE) -C examples clean
	mkdir -p faust-$(version)
	cp README COPYING faust-$(version)
	cp -r architecture faust-$(version)
	cp -r compiler faust-$(version)
	cp -r examples faust-$(version)
	find faust-$(version) -name CVS | xargs rm -rf
	cp Makefile faust-$(version)
	cp faust_tutorial.pdf faust-$(version)
	rm -f faust-$(version).tar.gz
	tar czf faust-$(version).tar.gz faust-$(version)
	rm -rf faust-$(version)
