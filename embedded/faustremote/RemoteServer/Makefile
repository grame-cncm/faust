CC            = gcc -O3
CXX           = g++ -O3
DEFINE	      = D_REENTRANT	 
INCPATH       = -I. -I../ -I../../../architecture -I/usr/include -I/opt/local/include 
LINK          = g++
LLVM_CONFIG   = llvm-config
LIBS          = -L../../../compiler /usr/local/lib/faust/libfaust.a -ljacknet -ljack -L/opt/local/lib -lmicrohttpd -lpthread -lcrypto `$(LLVM_CONFIG) --ldflags` `$(LLVM_CONFIG) --libs` -ldl -llo

sources =  $(wildcard *.cpp)
objects = $(sources:.cpp=.o)

####### Files

SOURCES       = Server.cpp main.cpp ../utilities.cpp
				
OBJECTS       = Server.o main.o utilities.o
DESTDIR       = 
TARGET        = RemoteServer

first: all

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

clean: 
	rm -f $(objects)

####### Compile

Server.o: Server.cpp Server.h ../TMutex.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Server.o Server.cpp

main.o: main.cpp Server.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

utilities.o: ../utilities.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o utilities.o ../utilities.cpp
