libname     := liboscpack.a
system		?= $(shell uname -s)

ifeq ($(system), Darwin)
subprojects := ip ip/posix osc
sources     := $(sort $(wildcard ip/*.cpp)  $(wildcard ip/posix/*.cpp)  $(wildcard osc/*.cpp))
ARCHFLAGS 	:=  -mmacosx-version-min=10.9

else
ifeq ($(system), Linux)
subprojects := ip ip/posix osc
sources     := $(sort $(wildcard ip/*.cpp)  $(wildcard ip/posix/*.cpp)  $(wildcard osc/*.cpp))
ARCHFLAGS 	:=
CXXFLAGS += -fPIC

else
ifeq ($(system), GNU/kFreeBSD)
subprojects := ip ip/posix osc
sources     := $(sort $(wildcard ip/*.cpp)  $(wildcard ip/posix/*.cpp)  $(wildcard osc/*.cpp))
ARCHFLAGS      :=

else
subprojects := ip ip/win32 osc
sources     := $(sort $(wildcard ip/*.cpp)  $(wildcard ip/win32/*.cpp)  $(wildcard osc/*.cpp))
ARCHFLAGS 	:=
endif
endif
endif

VPATH = $(subprojects)

CXXFLAGS ?= -O3 -Wall -Wuninitialized
CXXFLAGS += -Wno-parentheses -I. $(addprefix -I, $(subprojects)) $(ARCHFLAGS)

objects := $(sources:.cpp=.o)


## TARGETS

all: $(libname)

$(libname): $(objects)
	rm -f $@
	ar cq $@ $(objects)
	ranlib $@

depend :
	makedepend -fMakefile -w120 -Y -- $(CXXFLAGS) -- $(sources)

ios: IPHONEOS_DEPLOYMENT_TARGET=5.0
ios: CXX = /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++
ios: CXXFLAGS += -std=c++11 -stdlib=libstdc++  -arch armv7 -arch armv7s -arch arm64 -pipe -O3 -gdwarf-2 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS7.1.sdk
ios: CXXFLAGS += -fvisibility=hidden -Wno-overloaded-virtual -Wno-parentheses $(addprefix -I, $(subprojects)) -DINSTALL_PREFIX='"$(prefix)"'

ios : liboscpack.a

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
