
sources = $(wildcard Sources/*.cpp)
sources += ../utilities.cpp

objects = $(sources:.cpp=.o)

os 	:= $(shell uname)
system	?= $(shell uname -s)

PREFIX ?= /usr/local
INCPATH = -I. -I../ -I../../../architecture -I../../../compiler -I../../../compiler/generator/ -I../../../compiler/generator/llvm -I/usr/include -I/opt/local/include -F/Library/

ifeq ($(system), Darwin)
	CXX 		= g++
	CXXFLAGS	= $(INCPATH) -O3 -arch x86_64
	LIB_EXT     = dylib
else 
	ARCHFLAGS	:= 
	CXXFLAGS	= $(INCPATH) -O3
	LIBFLAGS	:= --mode=link --tag=CXX
	LIB_EXT     = so
endif

first: all

####### Build rules

all: $(objects) libfaustremote.a


ifeq ($(system), Darwin)
libfaustremote.a : $(objects)
	libtool -static $(LIBFLAGS) $(objects) -o libfaustremote.a
else 
libfaustremote.a : $(objects)
	rm -f $@
	ar cq $@ $(objects)
	ranlib $@
endif

install:
	install libfaustremote.a  /usr/local/lib/faust/ 
	cp remote-dsp.h  /usr/local/include/faust/

clean :
	rm -f $(objects) libfaustremote.a

depend :
	makedepend -w120 -Y -- $(sources)


# DO NOT DELETE

Sources/JsonParser.o: Sources/JsonParser.h
Sources/remote_dsp_aux.o: Sources/remote_dsp_aux.h ../TMutex.h Sources/JsonParser.h
Sources/remote_dsp_aux.o: ../../../compiler/generator/smartpointer.h ../../../compiler/libfaust.h
Sources/remote_dsp_aux.o: ../../../compiler/export.hh ../utilities.h
../utilities.o: ../utilities.h
