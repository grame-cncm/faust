subprojects := . src src/lib src/msg src/nodes src/osc src/threads ../..
sources = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp) 
objects = $(sources:.cpp=.o)

VPATH = $(subprojects)

system	?= $(shell uname -s)

ifeq ($(system), Darwin)
ARCHFLAGS :=  -arch i386 -arch x86_64
else
ARCHFLAGS := 
CXXFLAGS += -fPIC
endif

ifeq ($(MODE), SHARED)
ifeq ($(system), Darwin)
TARGET=libOSCFaust.$(VERSION).dylib
else
TARGET=libOSCFaust.so.$(VERSION)
endif
else
TARGET=libOSCFaust.a
endif


CXXFLAGS ?= -O3 -Wall -Wuninitialized $(ARCHFLAGS)
CXXFLAGS += -Wno-parentheses -I../oscpack -I../oscpack/osc $(addprefix -I, $(subprojects)) -DINSTALL_PREFIX='"$(prefix)"'

all : $(TARGET)

libOSCFaust.$(VERSION).dylib : $(objects)
	c++ -dynamiclib $(ARCHFLAGS) $(objects) -L.. -loscpack -o libOSCFaust.$(VERSION).dylib

libOSCFaust.so.$(VERSION) : $(objects)
	c++ -shared -fPIC $(ARCHFLAGS) $(objects) -L.. -loscpack -o libOSCFaust.so.$(VERSION)

libOSCFaust.a : $(objects)
	rm -f $@
	ar cq $@ $(objects)
	ranlib $@
	
	
depend :
	makedepend -fMakefile -w120 -Y -- $(CXXFLAGS) -- $(sources)
	
clean :
	rm -f $(objects)
	rm -f libOSCFaust.a libOSCFaust*.dylib libOSCFaust.so*
	


# DO NOT DELETE

src/OSCControler.o: faust/OSCControler.h faust/osc/FaustFactory.h faust/osc/FaustNode.h faust/osc/MessageDriven.h
src/OSCControler.o: faust/osc/MessageProcessor.h faust/osc/smartpointer.h faust/osc/Message.h ../../faust/gui/GUI.h
src/OSCControler.o: ../../faust/gui/UI.h faust/OSCIO.h src/osc/OSCSetup.h src/osc/OSCStream.h
src/OSCControler.o: ../oscpack/osc/OscOutboundPacketStream.h ../oscpack/osc/OscTypes.h ../oscpack/osc/OscException.h
src/OSCControler.o: ../oscpack/ip/UdpSocket.h ../oscpack/ip/NetworkingUtils.h ../oscpack/ip/IpEndpointName.h
src/OSCControler.o: src/lib/OSCFError.h src/nodes/RootNode.h
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
src/nodes/FaustFactory.o: ../../faust/gui/GUI.h ../../faust/gui/UI.h src/nodes/RootNode.h src/osc/OSCAddress.h
src/nodes/FaustNode.o: faust/osc/FaustNode.h faust/osc/MessageDriven.h faust/osc/MessageProcessor.h
src/nodes/FaustNode.o: faust/osc/smartpointer.h faust/osc/Message.h ../../faust/gui/GUI.h ../../faust/gui/UI.h
src/nodes/FaustNode.o: src/osc/OSCStream.h ../oscpack/osc/OscOutboundPacketStream.h ../oscpack/osc/OscTypes.h
src/nodes/FaustNode.o: ../oscpack/osc/OscException.h ../oscpack/ip/UdpSocket.h ../oscpack/ip/NetworkingUtils.h
src/nodes/FaustNode.o: ../oscpack/ip/IpEndpointName.h faust/OSCControler.h faust/osc/FaustFactory.h
src/nodes/MessageDriven.o: faust/osc/Message.h faust/osc/smartpointer.h faust/osc/MessageDriven.h
src/nodes/MessageDriven.o: faust/osc/MessageProcessor.h src/osc/OSCAddress.h src/lib/OSCFError.h src/osc/OSCStream.h
src/nodes/MessageDriven.o: ../oscpack/osc/OscOutboundPacketStream.h ../oscpack/osc/OscTypes.h
src/nodes/MessageDriven.o: ../oscpack/osc/OscException.h ../oscpack/ip/UdpSocket.h ../oscpack/ip/NetworkingUtils.h
src/nodes/MessageDriven.o: ../oscpack/ip/IpEndpointName.h src/lib/OSCRegexp.h src/lib/deelx.h
src/nodes/RootNode.o: faust/OSCControler.h faust/osc/FaustFactory.h faust/osc/FaustNode.h faust/osc/MessageDriven.h
src/nodes/RootNode.o: faust/osc/MessageProcessor.h faust/osc/smartpointer.h faust/osc/Message.h ../../faust/gui/GUI.h
src/nodes/RootNode.o: ../../faust/gui/UI.h faust/OSCIO.h src/nodes/RootNode.h src/osc/OSCStream.h
src/nodes/RootNode.o: ../oscpack/osc/OscOutboundPacketStream.h ../oscpack/osc/OscTypes.h ../oscpack/osc/OscException.h
src/nodes/RootNode.o: ../oscpack/ip/UdpSocket.h ../oscpack/ip/NetworkingUtils.h ../oscpack/ip/IpEndpointName.h
src/nodes/RootNode.o: ../oscpack/ip/NetworkingUtils.h
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
