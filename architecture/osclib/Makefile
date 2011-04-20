###############################################################
#
#			Build liboscpack.a and libOSCFaust.a the 2
#			static libraries needed to provide support
#           for Open Sound Control in Faust generated
#           applications.
#			
###############################################################

.PHONY: all clean depend


all : liboscpack.a libOSCFaust.a


liboscpack.a : oscpack/liboscpack.a
	cp oscpack/liboscpack.a $@

libOSCFaust.a : faust/libOSCFaust.a
	cp faust/libOSCFaust.a $@
	
	
oscpack/liboscpack.a:
	make -C oscpack
	
faust/libOSCFaust.a:
	make -C faust
	
	
clean :
	rm -f liboscpack.a 
	rm -f libOSCFaust.a
	make -C oscpack clean
	make -C faust clean

depend :
	make -C oscpack depend
	make -C faust depend

