# These paths are searched for llvm-config* in reverse order (/opt/local/bin
# is included for compatibility with MacPorts).
llvm_paths = /usr/bin /opt/local/bin /usr/local/bin

# Search heuristic for finding a suitable llvm-config. This will select a
# default 'llvm-config', if it's on the PATH. Otherwise it will look for
# llvm-config* on the paths above and select the lexicographically greatest
# among these. Usually this will give the llvm-config for the latest LLVM
# version on your system, preferring later paths in the list (so /usr/local
# will be considered before /usr). If none of these work then you can either
# link a suitable llvm-config to a location somewhere on your PATH, or just
# set LLVM_CONFIG manually.

LLVM_CONFIG = $(lastword $(wildcard /usr/bin/llvm-config* /opt/local/bin/llvm-config* /usr/local/bin/llvm-config*) $(shell which llvm-config 2> /dev/null))

CC            = gcc -O3
CXX           = g++ -O3 -fvisibility=hidden
DEFINE	      = D_REENTRANT	 
INCPATH       = -I. -I../ -I../../../architecture -I../../../compiler/generator -I../../../compiler/generator/llvm -I../../../compiler/generator/interpreter -I../../../compiler/utils -I/usr/include -I/opt/local/include 
LINK          = g++

system	?= $(shell uname -s)

sources =  $(wildcard *.cpp)
objects = $(sources:.cpp=.o)

ifeq ($(system), Darwin)
	LIBS = ../../../build/lib/libfaust.a -framework CoreAudio -framework AudioUnit -framework CoreServices -framework CoreFoundation -lportaudio -ljack -ljacknet -L/opt/local/lib ../../../build/lib/libOSCFaust.a ../../../architecture/httpdlib/libHTTPDFaust.a -framework CoreMIDI -lmicrohttpd -lpthread `$(LLVM_CONFIG) --ldflags` `$(LLVM_CONFIG) --libs` -lz -lncurses -ldl -llo
else 
	LIBS = ../../../build/lib/libfaust.a ../../../build/lib/libOSCFaust.a ../../../architecture/httpdlib/libHTTPDFaust.a -ljack -ljacknet -lmicrohttpd -lpthread `$(LLVM_CONFIG) --ldflags` `$(LLVM_CONFIG) --libs` -lz -lncurses -ldl -llo
endif

####### Files

SOURCES       = remote_server.cpp main.cpp ../utilities.cpp
				
OBJECTS       = remote_server.o main.o utilities.o
DESTDIR       = 
TARGET        = RemoteServer

first: all

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

clean: 
	rm -f $(OBJECTS) $(TARGET)

####### Compile

remote_server.o: remote_server.cpp remote_server.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o remote_server.o remote_server.cpp

main.o: main.cpp remote_server.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

utilities.o: ../utilities.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o utilities.o ../utilities.cpp
