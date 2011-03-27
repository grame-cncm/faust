libname     := liboscpack.a
subprojects := ip ip/posix osc
sources     := $(wildcard ip/*.cpp)  $(wildcard ip/posix/*.cpp)  $(wildcard osc/*.cpp)

VPATH = $(subprojects)

CXXFLAGS ?= -O3 -Wall -Wuninitialized 
CXXFLAGS += -Wno-parentheses -I. $(addprefix -I, $(subprojects))

objects := $(sources:.cpp=.o)


## TARGETS

all: $(libname)

$(libname): $(objects)
	rm -f $@
	ar cq $@ $(objects)
	ranlib $@
	
depend :
	makedepend -fMakefile -w120 -Y -- $(CXXFLAGS) -- $(sources)
	
clean :
	rm -f $(objects)
	rm -f $(libname)
	
	
# DO NOT DELETE

ip/IpEndpointName.o: ip/IpEndpointName.h ip/NetworkingUtils.h
ip/posix/NetworkingUtils.o: ip/NetworkingUtils.h
ip/posix/UdpSocket.o: ip/UdpSocket.h ip/NetworkingUtils.h ip/IpEndpointName.h ip/PacketListener.h ip/TimerListener.h
osc/OscOutboundPacketStream.o: osc/OscOutboundPacketStream.h osc/OscTypes.h osc/OscException.h osc/OscHostEndianness.h
osc/OscPrintReceivedElements.o: osc/OscPrintReceivedElements.h osc/OscReceivedElements.h osc/OscTypes.h
osc/OscPrintReceivedElements.o: osc/OscException.h
osc/OscReceivedElements.o: osc/OscReceivedElements.h osc/OscTypes.h osc/OscException.h osc/OscHostEndianness.h
osc/OscTypes.o: osc/OscTypes.h
