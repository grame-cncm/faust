#
# Makefile for testing the faust OSC UI
#

MAKE     ?= make
LIBDIR   ?= ../../build/lib
version  := $(shell cat osc-version.txt)

outfiles   = $(shell [ -d $(version) ] && find $(version) -name "*.txt" || echo)
validfiles = $(outfiles:%.txt=%.valid)


#########################################################################
#all: osclistener $(outfiles)

all: osclistener 
	$(MAKE) -f Make.size size=float
	$(MAKE) -f Make.size size=double
	

help:
	@echo "Available target are:"
	@echo " 'all' (default): build and run all the dsp found in the 'dsp' folder using an OSC UI"
	@echo "                  Each dsp is compiled twice: using the static and the dynamic OSC libs."
	@echo "                  The test sends the OSC messages taken from each corresponding dsp/*.osc.txt"
	@echo "                  while the application is running."
	@echo "                  Each test is performed using float and double as FAUSTFLOAT size."
	@echo "                  It produces impulse response files on output, located in the $(version) folder."
	@echo " 'validate VERSION=n.n.n' : compares the current output with a previous one"
	@echo "                  that is read from a 'n.n.n' folder."
	@echo 
	@echo "Note: $(version) is taken from the 'osc-version.txt' file that you can freely modify."
	
validate: $(validfiles)
	@echo "Validating version $(version) with version $(VERSION)"	
	

osclistener: tools/osclistener.cpp
	$(CXX) $(OPTIONS) -I../../architecture/osclib/oscpack $(LIBDIR)/libOSCFaust.a  tools/osclistener.cpp -o osclistener


#########################################################################
# rules for validation
%.valid : %.txt
	$(eval tmp := $(patsubst $(version)/%, $(VERSION)/%, $<))	
	@[ -f  $(tmp) ] || echo $< : new file
	@diff $<  $(tmp) 2>/dev/null >/dev/null || ([ -f  $(tmp) ] && echo "open -t $< $(patsubst $(version)/%, $(VERSION)/%, $<) # to check changes")
