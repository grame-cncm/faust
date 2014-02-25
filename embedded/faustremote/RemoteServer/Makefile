#############################################################################
# Makefile for building: DynamicCompiler.app/Contents/MacOS/DynamicCompiler
####### Compiler, tools and options

CC            = gcc -g
CXX           = g++ -g
DEFINE	      = D_REENTRANT	 
INCPATH       = -I. -I/usr/include -I. -I/opt/local/include -I. -F/Library/Frameworks
LINK          = g++
LLVM_CONFIG   = llvm-config
LIBS          = `$(LLVM_CONFIG) --ldflags` `$(LLVM_CONFIG) --libs`  -L/usr/local/lib/faust -lfaust -lHTTPDFaust -ljacknet -ljack -L/opt/local/lib -lmicrohttpd -lpthread -lcrypto

sources =  $(wildcard *.cpp)
objects = $(sources:.cpp=.o)

####### Files

SOURCES       = Server.cpp \
				main.cpp 
				
OBJECTS       = Server.o \
				main.o
DESTDIR       = 
TARGET        = ./RemoteServer

first: all

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)
			$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

clean: 
	rm -f $(objects)

####### Compile

Server.o: Server.cpp Server.h TMutex.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Server.o Server.cpp

main.o: main.cpp Server.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

