
# Generic Makefile for Faust Pd plugins.
# Translates ordinary effects (.dsp) and synths (.syn => -n 8).

# make, make all: make plugins and wrappers
# make cpp: make C++ sources
# make svg: make SVG diagrams
# make clean: remove all generated stuff

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

# Define the desired number of voices for synth (.syn) plugins here:
NVOICES = 8

dspsrc  := $(wildcard *.dsp)
synsrc  := $(wildcard *.syn)
cppsrc  := $(dspsrc:.dsp=.cpp) $(synsrc:.syn=.cpp)
plugins	:= $(dspsrc:%.dsp=%~$(DLL)) $(synsrc:%.syn=%~$(DLL))
svg 	:= $(dspsrc:.dsp=.dsp-svg) $(synsrc:.syn=.syn-svg)
xml 	:= $(dspsrc:.dsp=.dsp.xml) $(synsrc:.syn=.syn.xml)
pd 	:= $(dspsrc:.dsp=.pd) $(synsrc:.syn=.pd)

#faust2pd = faust2pd
faust2pd = ../../faust2pd

#all: $(plugins) $(svg) $(pd)
all: $(plugins) $(pd)
cpp: $(cppsrc)
svg: $(svg)
xml: $(xml)
pd:  $(pd)

clean:
	rm -Rf *~ $(plugins)

distclean: clean
	rm -f $(cppsrc)

realclean: distclean
	rm -Rf $(svg) $(xml) $(pd)

%.dsp-svg: %.dsp
	faust -svg $< -o /dev/null >/dev/null

%.syn-svg: %.syn
	faust -svg $< -o /dev/null >/dev/null

%.cpp: %.dsp
	faust $(VEC) -a puredata.cpp $< -o $@

%.cpp: %.syn
	faust $(VEC) -a puredata.cpp $< -o $@

%.dsp.xml: %.dsp
	faust -xml $< -o /dev/null

%.syn.xml: %.syn
	faust -xml $< -o /dev/null

%~$(DLL): %.cpp
	$(CXX) $(shared) $(EXTRA_CFLAGS) $(CFLAGS) -Dmydsp=$(@:%~$(DLL)=%) $(LDFLAGS) $< -o $@ $(PDLIB)

%.pd: %.dsp.xml
	$(faust2pd) -s $<

%.pd: %.syn.xml
	$(faust2pd) -n $(NVOICES) -s $<
