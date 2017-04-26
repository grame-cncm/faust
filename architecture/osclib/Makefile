###############################################################
#
#			Build liboscpack.a and libOSCFaust.a the 2
#			static libraries needed to provide support
#           for Open Sound Control in Faust generated
#           applications.
#			
###############################################################
VERSION=0.95
SOVERSION=0

.PHONY: all clean depend android

system	?= $(shell uname -s)

ifeq ($(system), Darwin)
ARCHFLAGS :=  -arch i386 -arch x86_64
LIB_EXT = dylib
TARGET = libOSCFaust.$(VERSION).$(LIB_EXT)
LIB_SONAME = libOSCFaust.$(SOVERSION).$(LIB_EXT)
else
ARCHFLAGS := 
ifneq ($(findstring MINGW32, $(system)),)
LIB_EXT = dll
TARGET = libOSCFaust-$(VERSION).$(LIB_EXT)
LIB_SONAME = libOSCFaust-$(SOVERSION).$(LIB_EXT)
else
CXXFLAGS += -fPIC
LIB_EXT = so
TARGET = libOSCFaust.$(LIB_EXT).$(VERSION)
LIB_SONAME = libOSCFaust.$(LIB_EXT).$(SOVERSION)
endif
endif

LIB_NAME = libOSCFaust.$(LIB_EXT)

all : liboscpack.a libOSCFaust.a

dynamic : liboscpack.a $(TARGET)


liboscpack.a : oscpack/liboscpack.a
	cp oscpack/liboscpack.a $@

libOSCFaust.a : liboscpack.a faust/libOSCFaust.a
	cp faust/libOSCFaust.a $@
# This "links" liboscpack.a into libOSCFaust.a.
ifeq ($(system), Darwin)
# On Darwin, we need to use Apple's libtool here, since ar can't handle
# archives containing more than one architecture.
	libtool libOSCFaust.a liboscpack.a -o tmp.a && rm -f libOSCFaust.a && mv tmp.a libOSCFaust.a
else
# Other systems use ar. The following should work with most systems having a
# modern ar (including GNU ar), but may need adjustments for systems with
# older ar versions or fat binaries like on OS X.
	(rm -Rf tmpdir && mkdir tmpdir && cd tmpdir && ar x ../liboscpack.a && ar q ../libOSCFaust.a `ar t ../liboscpack.a | grep .o` && cd .. && rm -Rf tmpdir)
# Older ar versions might need this?
#	ranlib $@
endif

$(TARGET) : faust/$(TARGET)
	cp faust/$(TARGET) $@
	ln -sf $(TARGET) $(LIB_SONAME)
	ln -sf $(LIB_SONAME) $(LIB_NAME)

	
oscpack/liboscpack.a:
	make -C oscpack
	
faust/libOSCFaust.a:
	make -C faust
	
faust/$(TARGET):
	make -C faust VERSION=$(VERSION) SOVERSION=$(SOVERSION) PREFIX=$(PREFIX) MODE=SHARED

ios : 
	make -C oscpack ios
	make -C faust ios

android :
	ndk-build -C android -j 4

clean :
	rm -f liboscpack.a libOSCFaust.a
	rm -f libOSCFaust*.dylib libOSCFaust.so* libOSCFaust*.dll
	make -C oscpack clean
	make -C faust clean

depend :
	make -C oscpack depend
	make -C faust depend

