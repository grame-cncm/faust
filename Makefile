prefix := /usr/local
arch := $(wildcard architecture/*.*)
mfiles := $(wildcard examples/Makefile.*)

all : 
	$(MAKE) -C compiler


.PHONY: clean depend install

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
	
distribution :
	$(MAKE) -C compiler clean
	$(MAKE) -C examples clean
	mkdir -p faust
	cp README faust
	cp -r architecture faust
	cp -r compiler faust
	cp -r examples faust
	cp Makefile faust
	cp faust_tutorial.pdf faust
	tar czf faust.tgz faust
	rm -r faust
