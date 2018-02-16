subprojects := html httpd include json lib msg nodes
http_fetcher = ../../../compiler/parser/sourcefetcher.cpp
sources0 = $(wildcard *.cpp) $(wildcard html/*.cpp) $(wildcard httpd/*.cpp)  $(wildcard json/*.cpp) $(wildcard msg/*.cpp) $(wildcard nodes/*.cpp)
sources = $(sources0) $(http_fetcher)
objects = $(sources0:.cpp=.o)
objects += sourcefetcher.o
objects += hexa/jsscripts.o
objects += hexa/stylesheet.o

VPATH = $(subprojects)

system	?= $(shell uname -s)

ifeq ($(system), Darwin)
ARCHFLAGS := -mmacosx-version-min=10.9  # we only support osx from 10.9 and up 
LIB_EXT = dylib
# Darwin/OS X: default installation name prefix for the dynamic library. This
# defaults to the installation prefix (a fixed path) if we have one, but
# depending on usage (plugin or executable) you may want to keep it empty or
# use some generic prefix such as @loader_path/ instead (see below).
ifneq ($(PREFIX),)
INSTALL_PREFIX = $(PREFIX)/lib/
endif
ifneq ($(INSTALL_PREFIX),)
INSTALL_NAME = -install_name "$(INSTALL_PREFIX)libHTTPDFaust.dylib"
endif
else
ARCHFLAGS := 
ifneq ($(findstring MINGW, $(system)),)
LIB_EXT = dll
else
CXXFLAGS += -fPIC
LIB_EXT = so
endif
endif

# Here are some useful alternative options for the installation name prefix
# (cf., e.g., https://wincent.com/wiki/@executable_path,_@load_path_and_@rpath):

# @executable_path: Useful if the dylib is distributed with an application
# (add path relative to the main executable if needed):
#INSTALL_PREFIX = @executable_path/

# @loader_path (OS X 10.4+): Useful if the dylib is distributed with a plugin
# (add path relative to the plugin if needed):
#INSTALL_PREFIX = @loader_path/

# @rpath (OS X 10.5+): Useful if the dylib is distributed with an application
# which has an rpath coded into it:
#INSTALL_PREFIX = @rpath/

CXXFLAGS ?= -O3 -Wall -Wuninitialized
CXXFLAGS += `pkg-config --cflags libmicrohttpd` -I../../../architecture -I../../../compiler/tlib -I/usr/local/include -Wno-parentheses $(addprefix -I, $(subprojects)) -DINSTALL_PREFIX='"$(prefix)"' $(ARCHFLAGS)

all: ../libHTTPDFaust.a

dynamic : ../libHTTPDFaust.$(LIB_EXT)

sourcefetcher.o: $(http_fetcher)
	$(CXX) $(CXXFLAGS) -fPIC $(http_fetcher) -c -o sourcefetcher.o
	
../libHTTPDFaust.a : $(objects)
	rm -f $@
	ar cq $@ $(objects)
	ranlib $@

../libHTTPDFaust.dylib :  $(objects)
	$(CXX) -dynamiclib $(INSTALL_NAME) $(ARCHFLAGS) $(objects) `pkg-config --libs libmicrohttpd` -o $@

../libHTTPDFaust.so  :  $(objects)
	$(CXX) -shared -fPIC $(LDFLAGS) -o $@ $(objects) `pkg-config --libs libmicrohttpd`

../libHTTPDFaust.dll  :  $(objects)
	$(CXX) -shared $(LDFLAGS) -o $@ $(objects) `pkg-config --libs libmicrohttpd` -lwsock32
	
depend :
	makedepend -fMakefile -w120 -Y -- $(CXXFLAGS) -- $(sources)
	
clean :
	rm -f $(objects) hexa/jsscripts hexa/jsscripts.cpp
	rm -f $(objects) hexa/stylesheet hexa/stylesheet.cpp
	rm -f ../libHTTPDFaust.a ../libHTTPDFaust.dylib ../libHTTPDFaust.so ../libHTTPDFaust.dll
	

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
	cat ../html/js/svg/faust_jquery_svg_backend.js >> $@
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
	cat ../html/js/svg/faust_ui_audio_bridge.js >> $@
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
../../../compiler/parser/sourcefetcher.o: ../../../compiler/tlib/compatibility.hh
../../../compiler/parser/sourcefetcher.o: ../../../compiler/parser/sourcefetcher.hh
