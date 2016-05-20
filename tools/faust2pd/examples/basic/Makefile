DLL = .pd_linux
shared = -shared

# Try to guess the host system type and figure out platform specifics.
host = $(shell ../../config.guess)
ifneq "$(findstring -mingw,$(host))" ""
# Windows
DLL = .dll
PDLIB = -Wl,--enable-auto-import -lpd
endif
ifneq "$(findstring -darwin,$(host))" ""
# OSX
DLL = .pd_darwin
shared = -dynamiclib -Wl,-undefined -Wl,dynamic_lookup
endif
ifneq "$(findstring x86_64-,$(host))" ""
# 64 bit, needs -fPIC flag
EXTRA_CFLAGS += -fPIC
endif
ifneq "$(findstring x86,$(host))" ""
# architecture-specific options for x86 and x86_64
EXTRA_CFLAGS += -msse -ffast-math
endif

EXTRA_CFLAGS += -I ../../pd

dspsrc  := $(wildcard *.dsp)
cppsrc  := $(dspsrc:.dsp=.cpp)
mods	:= $(dspsrc:%.dsp=%~$(DLL))
svg 	:= $(dspsrc:.dsp=.svg)
xml 	:= $(dspsrc:.dsp=.dsp.xml)
pd 	:= $(dspsrc:.dsp=.pd)
libs    := $(wildcard *.lib)

ARCH     = puredata.cpp
#FAUST2PD = faust2pd
FAUST2PD = ../../faust2pd
F2PDFLAGS = -s

all: $(mods)

cpp: $(cppsrc)

svg: $(svg)

xml: $(xml)

%~$(DLL): %.cpp
	$(CXX) $(shared) $(EXTRA_CFLAGS) $(CFLAGS) -Dmydsp=$(@:%~$(DLL)=%) $(LDFLAGS) $< -o $@ $(PDLIB)

%.cpp: %.dsp
	faust $(VEC) -a $(ARCH) $< -o $@

%.svg: %.dsp
	faust -svg $< -o /dev/null >/dev/null

%.dsp.xml: %.dsp
	faust -xml $< -o /dev/null

%.pd: %.dsp.xml
	$(FAUST2PD) $(F2PDFLAGS) $<

clean:
	rm -f $(mods) *~ *.a *.o

distclean:
	rm -f $(mods) $(cppsrc) *~ *.a *.o

clean-cpp:
	rm -f $(cppsrc)

clean-xml:
	rm -f $(xml)

clean-pd:
	rm -f $(pd)

clean-svg:
	rm -rf *-svg

realclean:
	rm -f $(mods) $(cppsrc) $(xml) $(pd) *~ *.a *.o
	rm -rf *-svg
