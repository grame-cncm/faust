subprojects := include httpd lib msg nodes threads
sources = $(wildcard *.cpp) $(wildcard */*.cpp) 
objects = $(sources:.cpp=.o)

VPATH = $(subprojects)

system	?= $(shell uname -s)

ifeq ($(system), Darwin)
ARCHFLAGS :=  -arch i386 -arch x86_64
else
ARCHFLAGS := 
endif

CXXFLAGS ?= -O3 -Wall -Wuninitialized $(ARCHFLAGS)
CXXFLAGS += -Wno-parentheses -I../oscpack -I../oscpack/osc $(addprefix -I, $(subprojects)) -DINSTALL_PREFIX='"$(prefix)"'

all : libHTTPDFaust.a

libHTTPDFaust.a : $(objects)
	rm -f $@
	ar cq $@ $(objects)
	ranlib $@
	
	
depend :
	makedepend -fMakefile -w120 -Y -- $(CXXFLAGS) -- $(sources)
	
clean :
	rm -f $(objects)
	rm -f libHTTPDFaust.a
	


# DO NOT DELETE

HTTPDControler.o: include/HTTPDControler.h nodes/FaustFactory.h nodes/MessageDriven.h msg/MessageProcessor.h
HTTPDControler.o: lib/smartpointer.h httpd/HTTPDSetup.h nodes/RootNode.h
httpd/Address.o: httpd/Address.h
httpd/HTTPDServer.o: httpd/HTTPDServer.h threads/TThreads.h msg/Message.h lib/smartpointer.h msg/MessageProcessor.h
httpd/HTTPDSetup.o: httpd/HTTPDSetup.h httpd/HTTPDServer.h threads/TThreads.h msg/MessageProcessor.h
msg/Message.o: msg/Message.h lib/smartpointer.h
nodes/FaustFactory.o: nodes/FaustFactory.h nodes/MessageDriven.h msg/MessageProcessor.h lib/smartpointer.h
nodes/FaustFactory.o: nodes/FaustNode.h nodes/RootNode.h
nodes/FaustNode.o: nodes/FaustNode.h nodes/MessageDriven.h msg/MessageProcessor.h lib/smartpointer.h msg/Message.h
nodes/FaustNode.o: httpd/HTTPDServer.h threads/TThreads.h
nodes/MessageDriven.o: httpd/Address.h msg/Message.h lib/smartpointer.h nodes/MessageDriven.h msg/MessageProcessor.h
nodes/RootNode.o: nodes/RootNode.h nodes/MessageDriven.h msg/MessageProcessor.h lib/smartpointer.h msg/Message.h
threads/pthreads_impl.o: threads/TThreads.h
