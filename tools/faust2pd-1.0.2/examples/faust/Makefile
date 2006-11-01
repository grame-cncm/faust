dspsrc  := $(wildcard *.dsp)
cppsrc  := $(dspsrc:.dsp=.cpp)
mods	:= $(dspsrc:%.dsp=%~.pd_linux)
svg 	:= $(dspsrc:.dsp=.svg)
xml 	:= $(dspsrc:.dsp=.dsp.xml)
pd 	:= $(dspsrc:.dsp=.pd)
libs    := $(wildcard *.lib)

CFLAGS  = -DPD -O2 -funroll-loops -fomit-frame-pointer -fPIC \
    -Wall -W -Wshadow -Wno-unused -Wno-parentheses -Wno-switch
INCLUDE =

#ARCH     = puredata.cpp
#FAUST2PD = faust2pd
ARCH     = ../../faust/puredata.cpp
FAUST2PD = q -p ../../faust2pd: faust2pd --
F2PDFLAGS = -r 10 -s

all: $(mods) $(pd)

cpp: $(cppsrc)

svg: $(svg)

xml: $(xml)

%~.pd_linux: %.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -shared -Dmydsp=$(@:%~.pd_linux=%) $< -o $@

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
