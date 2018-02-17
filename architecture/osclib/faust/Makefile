subprojects := . src src/lib src/msg src/nodes src/osc src/threads ../..
sources = $(sort $(wildcard src/*.cpp) $(wildcard src/*/*.cpp))
objects = $(sources:.cpp=.o)

VPATH = $(subprojects)

system	?= $(shell uname -s)

# Darwin/OS X: default installation name prefix for the dynamic library. This
# defaults to the installation prefix (a fixed path) if we have one, but
# depending on usage (plugin or executable) you may want to keep it empty or
# use some generic prefix such as @loader_path/ instead (see below).

ifneq ($(PREFIX),)
	INSTALL_PREFIX = $(PREFIX)/lib/
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

ifeq ($(system), Darwin)
	ARCHFLAGS := -mmacosx-version-min=10.9  # we only support osx from 10.9 and up 
else
	ARCHFLAGS := 
	ifeq ($(findstring MINGW, $(system)),)
		CXXFLAGS += -fPIC
	endif
endif

ifeq ($(MODE), SHARED)
	ifeq ($(system), Darwin)
		TARGET=libOSCFaust.$(VERSION).dylib
		SONAME=libOSCFaust.$(SOVERSION).dylib
		ifneq ($(INSTALL_PREFIX),)
			INSTALL_NAME = -install_name "$(INSTALL_PREFIX)$(SONAME)"
		endif
	else
		ifneq ($(findstring MINGW, $(system)),)
			TARGET=libOSCFaust-$(VERSION).dll
			SONAME=libOSCFaust-$(SOVERSION).dll
		else
			TARGET=libOSCFaust.so.$(VERSION)
			SONAME=libOSCFaust.so.$(SOVERSION)
		endif
	endif
else
	TARGET=libOSCFaust.a
endif


CXXFLAGS ?= -O3 -Wall -Wuninitialized 
CXXFLAGS += -Wno-parentheses -I../oscpack -I../oscpack/osc $(addprefix -I, $(subprojects)) -DINSTALL_PREFIX='"$(prefix)"' $(ARCHFLAGS)

all : $(TARGET)

libOSCFaust.$(VERSION).dylib : $(objects)
	$(CXX) -dynamiclib $(INSTALL_NAME) -compatibility_version $(SOVERSION) -current_version $(VERSION) $(ARCHFLAGS) $(objects) -L.. -loscpack -o libOSCFaust.$(VERSION).dylib

libOSCFaust.so.$(VERSION) : $(objects)
	$(CXX) -shared -Wl,-soname,$(SONAME) -fPIC $(ARCHFLAGS) $(LDFLAGS) $(objects) -L.. -loscpack -o libOSCFaust.so.$(VERSION)

libOSCFaust-$(VERSION).dll : $(objects)
	$(CXX) -shared $(ARCHFLAGS) $(LDFLAGS) $(objects) -L.. -loscpack -lwsock32 -lws2_32 -lwinmm -o libOSCFaust-$(VERSION).dll

libOSCFaust.a : $(objects)
	rm -f $@
	ar cq $@ $(objects)
	ranlib $@
	

ios: IPHONEOS_DEPLOYMENT_TARGET=5.0
ios: CXX = /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ 
ios: CXXFLAGS += -std=c++11 -stdlib=libstdc++ -arch armv7 -arch armv7s -arch arm64 -pipe -O3 -gdwarf-2 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS7.1.sdk
ios: CXXFLAGS += -fvisibility=hidden -Wno-overloaded-virtual -Wno-parentheses $(addprefix -I, $(subprojects)) -DINSTALL_PREFIX='"$(prefix)"' 

ios : libOSCFaust.a 
	
depend :
	makedepend -fMakefile -w120 -Y -- $(CXXFLAGS) -- $(sources)
	
clean :
	rm -f $(objects)
	rm -f libOSCFaust.a libOSCFaust*.dylib libOSCFaust.so* libOSCFaust*.dll
	


# DO NOT DELETE

src/OSCControler.o: faust/OSCControler.h faust/osc/FaustFactory.h faust/osc/FaustNode.h faust/osc/MessageDriven.h
src/OSCControler.o: faust/osc/MessageProcessor.h faust/osc/smartpointer.h faust/osc/Message.h ../../faust/gui/GUI.h
src/OSCControler.o: ../../faust/gui/UI.h ../../faust/gui/ring-buffer.h faust/osc/RootNode.h faust/OSCIO.h
src/OSCControler.o: src/osc/OSCSetup.h src/osc/OSCStream.h ../oscpack/osc/OscOutboundPacketStream.h
src/OSCControler.o: ../oscpack/osc/OscTypes.h ../oscpack/osc/OscException.h ../oscpack/ip/UdpSocket.h
src/OSCControler.o: ../oscpack/ip/NetworkingUtils.h ../oscpack/ip/IpEndpointName.h src/lib/OSCFError.h
src/OSCControler.o: src/lib/OSCRegexp.h src/lib/deelx.h
src/lib/OSCFError.o: src/lib/OSCFError.h src/osc/OSCStream.h ../oscpack/osc/OscOutboundPacketStream.h
src/lib/OSCFError.o: ../oscpack/osc/OscTypes.h ../oscpack/osc/OscException.h ../oscpack/ip/UdpSocket.h
src/lib/OSCFError.o: ../oscpack/ip/NetworkingUtils.h ../oscpack/ip/IpEndpointName.h faust/osc/Message.h
src/lib/OSCFError.o: faust/osc/smartpointer.h
src/lib/OSCRegexp.o: src/lib/OSCRegexp.h src/lib/deelx.h
src/msg/Message.o: faust/osc/Message.h faust/osc/smartpointer.h src/lib/OSCFError.h src/osc/OSCStream.h
src/msg/Message.o: ../oscpack/osc/OscOutboundPacketStream.h ../oscpack/osc/OscTypes.h ../oscpack/osc/OscException.h
src/msg/Message.o: ../oscpack/ip/UdpSocket.h ../oscpack/ip/NetworkingUtils.h ../oscpack/ip/IpEndpointName.h
src/nodes/FaustFactory.o: faust/osc/FaustFactory.h faust/osc/FaustNode.h faust/osc/MessageDriven.h
src/nodes/FaustFactory.o: faust/osc/MessageProcessor.h faust/osc/smartpointer.h faust/osc/Message.h
src/nodes/FaustFactory.o: ../../faust/gui/GUI.h ../../faust/gui/UI.h ../../faust/gui/ring-buffer.h faust/osc/RootNode.h
src/nodes/FaustFactory.o: src/osc/OSCAddress.h
src/nodes/FaustNode.o: faust/osc/FaustNode.h faust/osc/MessageDriven.h faust/osc/MessageProcessor.h
src/nodes/FaustNode.o: faust/osc/smartpointer.h faust/osc/Message.h ../../faust/gui/GUI.h ../../faust/gui/UI.h
src/nodes/FaustNode.o: ../../faust/gui/ring-buffer.h faust/osc/RootNode.h faust/OSCControler.h faust/osc/FaustFactory.h
src/nodes/FaustNode.o: src/osc/OSCStream.h ../oscpack/osc/OscOutboundPacketStream.h ../oscpack/osc/OscTypes.h
src/nodes/FaustNode.o: ../oscpack/osc/OscException.h ../oscpack/ip/UdpSocket.h ../oscpack/ip/NetworkingUtils.h
src/nodes/FaustNode.o: ../oscpack/ip/IpEndpointName.h
src/nodes/MessageDriven.o: faust/osc/Message.h faust/osc/smartpointer.h faust/osc/MessageDriven.h
src/nodes/MessageDriven.o: faust/osc/MessageProcessor.h src/osc/OSCAddress.h src/lib/OSCFError.h src/osc/OSCStream.h
src/nodes/MessageDriven.o: ../oscpack/osc/OscOutboundPacketStream.h ../oscpack/osc/OscTypes.h
src/nodes/MessageDriven.o: ../oscpack/osc/OscException.h ../oscpack/ip/UdpSocket.h ../oscpack/ip/NetworkingUtils.h
src/nodes/MessageDriven.o: ../oscpack/ip/IpEndpointName.h src/lib/OSCRegexp.h src/lib/deelx.h
src/nodes/RootNode.o: faust/OSCControler.h faust/osc/FaustFactory.h faust/osc/FaustNode.h faust/osc/MessageDriven.h
src/nodes/RootNode.o: faust/osc/MessageProcessor.h faust/osc/smartpointer.h faust/osc/Message.h ../../faust/gui/GUI.h
src/nodes/RootNode.o: ../../faust/gui/UI.h ../../faust/gui/ring-buffer.h faust/osc/RootNode.h faust/OSCIO.h
src/nodes/RootNode.o: src/osc/OSCStream.h ../oscpack/osc/OscOutboundPacketStream.h ../oscpack/osc/OscTypes.h
src/nodes/RootNode.o: ../oscpack/osc/OscException.h ../oscpack/ip/UdpSocket.h ../oscpack/ip/NetworkingUtils.h
src/nodes/RootNode.o: ../oscpack/ip/IpEndpointName.h ../oscpack/ip/NetworkingUtils.h
src/osc/OSCAddress.o: src/osc/OSCAddress.h
src/osc/OSCIO.o: faust/OSCIO.h src/osc/OSCStream.h ../oscpack/osc/OscOutboundPacketStream.h ../oscpack/osc/OscTypes.h
src/osc/OSCIO.o: ../oscpack/osc/OscException.h ../oscpack/ip/UdpSocket.h ../oscpack/ip/NetworkingUtils.h
src/osc/OSCIO.o: ../oscpack/ip/IpEndpointName.h
src/osc/OSCListener.o: faust/osc/Message.h faust/osc/smartpointer.h src/osc/OSCListener.h faust/osc/MessageProcessor.h
src/osc/OSCListener.o: ../oscpack/ip/UdpSocket.h ../oscpack/ip/NetworkingUtils.h ../oscpack/ip/IpEndpointName.h
src/osc/OSCListener.o: ../oscpack/osc/OscPacketListener.h ../oscpack/osc/OscReceivedElements.h
src/osc/OSCListener.o: ../oscpack/osc/OscTypes.h ../oscpack/osc/OscException.h ../oscpack/ip/PacketListener.h
src/osc/OSCListener.o: src/osc/OSCStream.h ../oscpack/osc/OscOutboundPacketStream.h
src/osc/OSCListener.o: ../oscpack/osc/OscReceivedElements.h ../oscpack/ip/IpEndpointName.h
src/osc/OSCSetup.o: src/osc/OSCSetup.h src/osc/OSCStream.h ../oscpack/osc/OscOutboundPacketStream.h
src/osc/OSCSetup.o: ../oscpack/osc/OscTypes.h ../oscpack/osc/OscException.h ../oscpack/ip/UdpSocket.h
src/osc/OSCSetup.o: ../oscpack/ip/NetworkingUtils.h ../oscpack/ip/IpEndpointName.h src/threads/TThreads.h
src/osc/OSCSetup.o: src/osc/OSCListener.h faust/osc/smartpointer.h faust/osc/MessageProcessor.h
src/osc/OSCSetup.o: ../oscpack/osc/OscPacketListener.h ../oscpack/osc/OscReceivedElements.h
src/osc/OSCSetup.o: ../oscpack/ip/PacketListener.h
src/osc/OSCStream.o: src/osc/OSCStream.h ../oscpack/osc/OscOutboundPacketStream.h ../oscpack/osc/OscTypes.h
src/osc/OSCStream.o: ../oscpack/osc/OscException.h ../oscpack/ip/UdpSocket.h ../oscpack/ip/NetworkingUtils.h
src/osc/OSCStream.o: ../oscpack/ip/IpEndpointName.h
src/threads/pthreads_impl.o: src/threads/TThreads.h
