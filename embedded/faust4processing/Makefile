# where to install the library
PROCESSING = ~/Documents/Processing/libraries
DST = $(PROCESSING)/faustProcessing

all : binaries examples
	
	
help :
	@echo "You need to have Faust2 compiled and installed"
	@echo "make           : build the faustProcessing library and the examples"
	@echo "make install   : install the faustProcessing library into $(PROCESSING)"
	@echo "make uninstall : remove the faustProcessing library from $(PROCESSING)"
	@echo "make clean     : remove the files produced by make"


binaries :
	mkdir -p binaries
	make -C binaries -f ../src/Makefile.library
	
	
examples : 
	mkdir examples
	./src/scripts/buildProcessingExamples
	
	
clean :
	rm -rf examples 
	rm -rf binaries
	
	
install :
	# install library properties
	mkdir -p $(DST)
	mkdir -p $(DST)/library
	cp src/library.properties $(DST)/
	# install library
	cp binaries/faustProcessing.jar $(DST)/library
	cp binaries/libFaustEngine.jnilib $(DST)/library
	cp src/faust-libraries/*  $(DST)/library
	# install examples
	cp -r examples $(DST)
	

uninstall :
	rm -rf $(DST)
