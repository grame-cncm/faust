
sources = $(wildcard RemoteClient/*.cpp)
sources += utilities.cpp
sources += $(wildcard RemoteServer/*.cpp) 

objects = $(sources:.cpp=.o)

os 	:= $(shell uname)
system	?= $(shell uname -s)

PREFIX ?= /usr/local
INCPATH = -I. -I../../compiler -I../../compiler/errors -I../../architecture -I../../compiler/utils -I../../compiler/generator/ -I../../compiler/generator/llvm -I../../compiler/generator/interpreter -I/usr/include -I/opt/local/include -F/Library/

ifeq ($(system), Darwin)
	CXX 		= g++
	CXXFLAGS	= -O3 $(INCPATH) -arch x86_64 -fvisibility=hidden 
	LIB_EXT     	= dylib
else 
	ARCHFLAGS	:= 
	CXXFLAGS	= -O3 $(INCPATH) -fvisibility=hidden 
	LIBFLAGS	:= --mode=link --tag=CXX -fvisibility=hidden
	LIB_EXT     	= so
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
	install libfaustremote.a  /usr/local/lib
	cp remote-dsp.h  /usr/local/include/faust/dsp/

clean :
	rm -f $(objects) libfaustremote.a

depend :
	makedepend -w120 -Y -- $(sources)


# DO NOT DELETE

RemoteClient/Sources/remote_dsp_aux.o: RemoteClient/Sources/remote_dsp_aux.h 
RemoteClient/Sources/remote_dsp_aux.o: utilities.h
utilities.o: utilities.h
RemoteServer/remote_server.o: RemoteServer/remote_server.h utilities.h
