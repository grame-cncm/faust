
dspsrc  := $(wildcard *.dsp)
cppsrc  := $(dspsrc:.dsp=.cpp)
plugins	:= $(dspsrc:%.dsp=%~.pd_linux)
svg 	:= $(dspsrc:.dsp=-svg)
xml 	:= $(dspsrc:.dsp=.dsp.xml)
pd 	:= $(dspsrc:.dsp=.pd)

all: $(plugins) $(svg)

clean:
	rm -Rf *~ $(cppsrc) $(plugins) $(svg) $(xml)

%.cpp %.dsp.xml %-svg: %.dsp
	faust -xml -svg -sd -a puredata.cpp $< -o $@

%~.pd_linux: %.cpp
	g++ -shared -fPIC -Dmydsp=$(@:%~.pd_linux=%) -o $@ $<

%.pd: %.dsp.xml
	faust2pd -s $<
