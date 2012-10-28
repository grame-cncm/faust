subprojects := html httpd include json lib msg nodes
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
CXXFLAGS += -Wno-parentheses $(addprefix -I, $(subprojects)) -DINSTALL_PREFIX='"$(prefix)"'

target := ../libHTTPDFaust.a

all : $(target)

$(target) : $(objects)
	rm -f $@
	ar cq $@ $(objects)
	ranlib $@
	
	
depend :
	makedepend -fMakefile -w120 -Y -- $(CXXFLAGS) -- $(sources)
	
clean :
	rm -f $(objects)
	rm -f $(target)
	


# DO NOT DELETE

HTTPDControler.o: include/HTTPDControler.h nodes/FaustFactory.h nodes/MessageDriven.h msg/MessageProcessor.h
HTTPDControler.o: lib/smartpointer.h nodes/FaustNode.h msg/Message.h httpd/HTTPDSetup.h json/jsonfactory.h
HTTPDControler.o: json/jsonroot.h json/jsonnode.h json/jsoncontrol.h html/htmlfactory.h html/htmlpage.h
HTTPDControler.o: nodes/RootNode.h
html/htmlfactory.o: html/htmlfactory.h html/htmlpage.h
html/htmlpage.o: lib/deelx.h html/htmlpage.h
html/htmlrow.o: html/htmlpage.h
html/htmlui.o: html/htmlui.h html/htmlfactory.h html/htmlpage.h
httpd/Address.o: httpd/Address.h
httpd/HTTPDServer.o: httpd/HTTPDServer.h msg/Message.h lib/smartpointer.h msg/MessageProcessor.h
httpd/HTTPDSetup.o: httpd/HTTPDSetup.h httpd/HTTPDServer.h msg/MessageProcessor.h
json/jsoncontrol.o: json/jsoncontrol.h json/jsonnode.h lib/smartpointer.h
json/jsonfactory.o: json/jsonfactory.h json/jsonroot.h lib/smartpointer.h json/jsonnode.h json/jsoncontrol.h
json/jsonfactory.o: json/jsongroup.h
json/jsonfaustui.o: include/jsonfaustui.h include/UI.h json/jsonui.h json/jsonfactory.h json/jsonroot.h
json/jsonfaustui.o: lib/smartpointer.h json/jsonnode.h json/jsoncontrol.h
json/jsongroup.o: json/jsongroup.h json/jsonnode.h lib/smartpointer.h
json/jsonroot.o: json/jsonroot.h lib/smartpointer.h json/jsonnode.h
json/jsonui.o: json/jsonui.h json/jsonfactory.h json/jsonroot.h lib/smartpointer.h json/jsonnode.h json/jsoncontrol.h
msg/Message.o: msg/Message.h lib/smartpointer.h
nodes/FaustFactory.o: nodes/FaustFactory.h nodes/MessageDriven.h msg/MessageProcessor.h lib/smartpointer.h
nodes/FaustFactory.o: nodes/FaustNode.h msg/Message.h nodes/RootNode.h
nodes/FaustNode.o: nodes/FaustNode.h nodes/MessageDriven.h msg/MessageProcessor.h lib/smartpointer.h msg/Message.h
nodes/FaustNode.o: httpd/HTTPDServer.h
nodes/MessageDriven.o: httpd/Address.h msg/Message.h lib/smartpointer.h nodes/MessageDriven.h msg/MessageProcessor.h
nodes/MessageDriven.o: httpd/HTTPDServer.h
nodes/RootNode.o: nodes/RootNode.h nodes/MessageDriven.h msg/MessageProcessor.h lib/smartpointer.h msg/Message.h
