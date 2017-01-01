# Generic Makefile for testing that Faust code compiles

# derived from faust2puredata Makefile

dspsrc  := $(wildcard *.dsp)
cppsrc  := $(dspsrc:.dsp=.cpp)
eps 	:= $(dspsrc:.dsp=.eps)
app 	:= $(dspsrc:.dsp=.app)
ml 	:= $(dspsrc:.dsp=.m)
prt 	:= $(dspsrc:.dsp=)
prtc 	:= $(dspsrc:.dsp=.dsp.cpp)

cpp: $(cppsrc)
svg: $(svg)
xml: $(xml)

clean:
	rm -Rf *~ octave-workspace *-svg

distclean tclean realclean: clean
	rm -f $(cppsrc)
	rm -rf $(app)
	rm -rf $(svg)
	rm -f $(ml) $(prt) $(prtc)
	rm -f pfo-*.eps

%.dsp-svg: %.dsp
	faust -svg $< -o /dev/null >/dev/null

%.syn-svg: %.syn
	faust -svg $< -o /dev/null >/dev/null

%.cpp: %.dsp
	faust $(VEC) $< -o $@ >/dev/null

%.dsp.xml: %.dsp
	faust -xml $< -o /dev/null

%.eps: %-svg/process.svg
	rsvg-convert --format=ps $< > $@
