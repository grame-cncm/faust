###############################################################
#
#			Build liboscpack.a and libOSCFaust.a the 2
#			static libraries needed to provide support
#           for Open Sound Control in Faust generated
#           applications.
#			
###############################################################
VERSION=0.93
SOVERSION=1

.PHONY: all clean depend


all : liboscpack.a libOSCFaust.a

dynamic : liboscpack.a libOSCFaust.$(VERSION).dylib


liboscpack.a : oscpack/liboscpack.a
	cp oscpack/liboscpack.a $@

libOSCFaust.a : faust/libOSCFaust.a
	cp faust/libOSCFaust.a $@

libOSCFaust.$(VERSION).dylib : faust/libOSCFaust.$(VERSION).dylib
	cp faust/libOSCFaust.$(VERSION).dylib $@
	ln -s libOSCFaust.$(VERSION).dylib libOSCFaust.$(SOVERSION).dylib
	ln -s libOSCFaust.$(SOVERSION).dylib libOSCFaust.dylib
	
oscpack/liboscpack.a:
	make -C oscpack
	
faust/libOSCFaust.a:
	make -C faust
	
faust/libOSCFaust.$(VERSION).dylib:
	make -C faust VERSION=$(VERSION) MODE=SHARED
	
clean :
	rm -f liboscpack.a 
	rm -f libOSCFaust.a
	rm -f libOSCFaust*.dylib
	make -C oscpack clean
	make -C faust clean

depend :
	make -C oscpack depend
	make -C faust depend

