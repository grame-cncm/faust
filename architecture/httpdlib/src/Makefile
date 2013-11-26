subprojects := html httpd include json lib msg nodes
sources = $(wildcard *.cpp) $(wildcard html/*.cpp) $(wildcard httpd/*.cpp)  $(wildcard json/*.cpp) $(wildcard msg/*.cpp) $(wildcard nodes/*.cpp)
objects = $(sources:.cpp=.o)
objects += hexa/jsscripts.o
objects += hexa/stylesheet.o

VPATH = $(subprojects)

system	?= $(shell uname -s)

TARGETS := ../libHTTPDFaust.a 

ifeq ($(system), Darwin)
ARCHFLAGS :=  -arch i386 -arch x86_64
else
ARCHFLAGS := 
endif

CXXFLAGS ?= -O3 -Wall -Wuninitialized $(ARCHFLAGS)
CXXFLAGS += `pkg-config --cflags libmicrohttpd` -I../../../architecture -I/usr/local/include -Wno-parentheses $(addprefix -I, $(subprojects)) -DINSTALL_PREFIX='"$(prefix)"'

all : $(TARGETS)

../libHTTPDFaust.a : $(objects)
	rm -f $@
	ar cq $@ $(objects)
	ranlib $@

../libHTTPDFaust.dylib  :  $(objects)
	libtool -dynamic $(objects) -lc -lstdc++ `pkg-config --libs libmicrohttpd` -install_name /usr/local/lib/faust/libHTTPDFaust.dylib -o $@
	
depend :
	makedepend -fMakefile -w120 -Y -- $(CXXFLAGS) -- $(sources)
	
clean :
	rm -f $(objects) hexa/jsscripts hexa/jsscripts.cpp
	rm -f $(objects) hexa/stylesheet hexa/stylesheet.cpp
	rm -f $(TARGETS)
	

hexa/jsscripts.o : hexa/jsscripts.cpp

hexa/stylesheet.o : hexa/stylesheet.cpp

hexa/jsscripts.cpp : hexa/jsscripts
	cd hexa; xxd -i jsscripts jsscripts.cpp

hexa/stylesheet.cpp : hexa/stylesheet
	cd hexa; xxd -i stylesheet stylesheet.cpp

hexa/jsscripts : ../html/js/svg/*.js ../html/js/svg/jquerysvg/jquery.svg.js
	cat ../html/js/svg/jquery-1.7.1.min.js > $@
	echo " " >> $@
	cat ../html/js/svg/jquerysvg/jquery.svg.min.js >> $@
	echo " " >> $@
	cat ../html/js/svg/jquerysvg/jquery.svgdom.min.js >> $@
	echo " " >> $@
	cat ../html/js/svg/faust_proto.js >> $@
	echo " " >> $@
	cat ../html/js/svg/faust_mobile.js >> $@
	echo " " >> $@
	cat ../html/js/svg/faust_ui_inits.js >> $@
	echo " " >> $@
	cat ../html/js/svg/faust_load_external_file.js >> $@
	echo " " >> $@
	cat ../html/js/svg/faust_ui_objects.js >> $@
	echo " " >> $@
	cat ../html/js/svg/faust_ui_builder.js >> $@
	echo " " >> $@
	cat ../html/js/svg/faust_ui_interact.js >> $@
	echo " " >> $@
	cat ../html/js/svg/faust_server_communication.js >> $@

hexa/stylesheet : ../html/js/svg/faust_css.css
	cat ../html/js/svg/faust_css.css > $@

# DO NOT DELETE

HTTPDControler.o: include/HTTPDControler.h nodes/FaustFactory.h nodes/MessageDriven.h msg/MessageProcessor.h
HTTPDControler.o: lib/smartpointer.h nodes/FaustNode.h msg/Message.h httpd/HTTPDSetup.h json/jsonfactory.h
HTTPDControler.o: json/jsonroot.h json/jsonnode.h json/jsoncontrol.h html/htmlfactory.h html/htmlpage.h
HTTPDControler.o: nodes/RootNode.h
html/htmlfactory.o: html/htmlfactory.h html/htmlpage.h
html/htmlpage.o: lib/deelx.h html/htmlpage.h html/jsscripts.h html/stylesheet.h
html/htmlui.o: html/htmlui.h html/htmlfactory.h html/htmlpage.h
httpd/Address.o: httpd/Address.h
httpd/HTTPDServer.o: httpd/HTTPDServer.h msg/Message.h lib/smartpointer.h msg/MessageProcessor.h
httpd/HTTPDSetup.o: httpd/HTTPDSetup.h httpd/HTTPDServer.h msg/MessageProcessor.h
json/jsoncontrol.o: json/jsoncontrol.h json/jsonnode.h lib/smartpointer.h
json/jsonfactory.o: json/jsonfactory.h json/jsonroot.h lib/smartpointer.h json/jsonnode.h json/jsoncontrol.h
json/jsonfactory.o: json/jsongroup.h
json/jsonfaustui.o: include/jsonfaustui.h ../../../architecture/faust/gui/meta.h ../../../architecture/faust/gui/UI.h
json/jsonfaustui.o: json/jsonui.h json/jsonfactory.h json/jsonroot.h lib/smartpointer.h json/jsonnode.h
json/jsonfaustui.o: json/jsoncontrol.h
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
