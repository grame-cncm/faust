###############################################################
#
#			Build liboscpack.a and libOSCFaust.a the 2
#			static libraries needed to provide support
#           for Open Sound Control in Faust generated
#           applications.
#			
###############################################################
VERSION=0.93
SOVERSION=0

.PHONY: all clean depend

system	?= $(shell uname -s)

ifeq ($(system), Darwin)
ARCHFLAGS :=  -arch i386 -arch x86_64
LIB_EXT = dylib
TARGET = libOSCFaust.$(VERSION).$(LIB_EXT)
LIB_SONAME = libOSCFaust.$(SOVERSION).$(LIB_EXT)
else
ARCHFLAGS := 
CXXFLAGS += -fPIC
LIB_EXT = so
TARGET = libOSCFaust.$(LIB_EXT).$(VERSION)
LIB_SONAME = libOSCFaust.$(LIB_EXT).$(SOVERSION)
endif

LIB_NAME = libOSCFaust.$(LIB_EXT)

all : liboscpack.a libOSCFaust.a

dynamic : liboscpack.a $(TARGET)


liboscpack.a : oscpack/liboscpack.a
	cp oscpack/liboscpack.a $@

libOSCFaust.a : faust/libOSCFaust.a
	cp faust/libOSCFaust.a $@

$(TARGET) : faust/$(TARGET)
	cp faust/$(TARGET) $@
	ln -sf $(TARGET) $(LIB_SONAME)
	ln -sf $(LIB_SONAME) $(LIB_NAME)
	
oscpack/liboscpack.a:
	make -C oscpack
	
faust/libOSCFaust.a:
	make -C faust
	
faust/$(TARGET):
	make -C faust VERSION=$(VERSION) MODE=SHARED
	
clean :
	rm -f liboscpack.a libOSCFaust.a
	rm -f libOSCFaust*.dylib libOSCFaust.so*
	make -C oscpack clean
	make -C faust clean

depend :
	make -C oscpack depend
	make -C faust depend

