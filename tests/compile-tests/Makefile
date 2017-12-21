#
# Makefile for testing the faust compiler output
#

system := $(shell uname -s)
system := $(shell echo $(system) | grep MINGW > /dev/null && echo MINGW || echo $(system))
ifeq ($(system), MINGW)
 FAUST ?= ../../build/bin/faust.exe
else
 FAUST ?= ../../build/bin/faust
endif

SAMPLESROOT := ../..
FAUSTLIBS ?= ../../libraries
FAUSTINC  ?= ../../architecture/faust

version := $(shell $(FAUST) --version | grep Version | sed -e 's/^..*Version //')

dspfiles  = $(shell find $(SAMPLESROOT)/examples -name "*.dsp" | grep -v TODO | grep -v faust-stk | grep -v "misc/guitarix.dsp")

cppout	:= $(patsubst $(SAMPLESROOT)/%.dsp, $(version)/cpp/%.cpp,   $(dspfiles))
ocppout	:= $(patsubst $(SAMPLESROOT)/%.dsp, $(version)/ocpp/%.cpp,  $(dspfiles))
cout	:= $(patsubst $(SAMPLESROOT)/%.dsp, $(version)/c/%.c,       $(dspfiles))
jsout	:= $(patsubst $(SAMPLESROOT)/%.dsp, $(version)/js/%.js,     $(dspfiles))
ajsout	:= $(patsubst $(SAMPLESROOT)/%.dsp, $(version)/ajs/%.js,    $(dspfiles))
wasmout	:= $(patsubst $(SAMPLESROOT)/%.dsp, $(version)/wasm/%.js,   $(dspfiles))
javaout	:= $(patsubst $(SAMPLESROOT)/%.dsp, $(version)/java/%.java, $(dspfiles))
firout 	:= $(patsubst $(SAMPLESROOT)/%.dsp, $(version)/fir/%.fir,   $(dspfiles))
rustout := $(patsubst $(SAMPLESROOT)/%.dsp, $(version)/rust/%.rust, $(dspfiles))
llvmout := $(patsubst $(SAMPLESROOT)/%.dsp, $(version)/llvm/%.llvm, $(dspfiles))
interpout := $(patsubst $(SAMPLESROOT)/%.dsp, $(version)/interp/%.itp, $(dspfiles))

cppobj	:= $(patsubst %.cpp, %.o, $(cppout))
ocppobj	:= $(patsubst %.cpp, %.o, $(ocppout))
cobj	:= $(patsubst %.c, %.o, $(cout))

CXX ?= g++
GCC ?= gcc

OPTIONS := -Wno-unused-command-line-argument -I$(FAUSTINC)

all:
	make cpp
	make ocpp
	make c
	make js
	make asmjs
	make wasm
	make java
	make fir
	make rust
	make llvm
#	make interp


help:
	@echo "-------- FAUST compilation tests --------"
	@echo "Available targets are:"
	@echo " 'all' (default): compiles all the dsp found in the examples folder"
	@echo "            using all backends (apart the interp backend)"
	@echo "            C and C++ output are also compile using $(GCC) and $(CXX)"
	@echo "            Output is located in a folder named using faust version"
	@echo "Individual targets:"
	@echo " 'cpp'    : makes use of the cpp backend          (-lang cpp)"
	@echo " 'ocpp'   : makes use of the old cpp backend      (-lang ocpp)"
	@echo " 'c'      : makes use of the c backend            (-lang c)"
	@echo " 'js'     : makes use of the javascript backend   (-lang js)"
	@echo " 'asmjs'  : makes use of the asmjs backend        (-lang ajs)"
	@echo " 'wasm'   : makes use of the web-assembly backend (-lang wast/wasm)"
	@echo " 'java'   : makes use of the java backend         (-lang java)"
	@echo " 'fir'    : makes use of the fir backend          (-lang fir)"
	@echo " 'rust'   : makes use of the rust backend         (-lang rust)"
	@echo " 'llvm'   : makes use of the LLVM backend         (-lang llvm)"
	@echo " 'interp' : makes use of the interpreter backend  (-lang interp)"
	


clean:
	rm -rf $(version)


#########################################################################
cpp:   $(cppout) $(cppobj)
ocpp:  $(ocppout) $(ocppobj)
c:     $(cout) $(cobj)
js:    $(jsout)
asmjs: $(ajsout)
wasm:  $(wasmout)
java:  $(javaout)
fir:   $(firout)
rust:  $(rustout)
llvm:  $(llvmout)
interp: $(interpout)

#########################################################################
# rule for cpp output
$(version)/cpp/%.cpp: $(SAMPLESROOT)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang cpp -I $(FAUSTLIBS) -a ./min.cpp $<  > $@ || (rm $@ ; false; )

#########################################################################
# rule for ocpp output
$(version)/ocpp/%.cpp: $(SAMPLESROOT)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang ocpp -I $(FAUSTLIBS) -a ./min.cpp $<  > $@ || (rm $@ ; false; )

#########################################################################
# rule for c output
$(version)/c/%.c: $(SAMPLESROOT)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang c -I $(FAUSTLIBS) -a ./min.c $<  > $@ || (rm $@ ; false; )

#########################################################################
# rule for js output
$(version)/js/%.js: $(SAMPLESROOT)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang js -I $(FAUSTLIBS) $<  > $@ || (rm $@ ; false; )

#########################################################################
# rule for asmjs output
$(version)/ajs/%.js: $(SAMPLESROOT)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang ajs -I $(FAUSTLIBS) $<  > $@ || (rm $@ ; false; )

#########################################################################
# rule for wasm output
$(version)/wasm/%.js: $(SAMPLESROOT)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang wast/wasm -I $(FAUSTLIBS) $<  > $@ || (rm $@ ; false; )

#########################################################################
# rule for java output
$(version)/java/%.java: $(SAMPLESROOT)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang java -I $(FAUSTLIBS) $<  > $@ || (rm $@ ; false; )

#########################################################################
# rule for fir output
$(version)/fir/%.fir: $(SAMPLESROOT)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang fir -I $(FAUSTLIBS) $<  > $@ || (rm $@ ; false; )

#########################################################################
# rule for rust output
$(version)/rust/%.rust: $(SAMPLESROOT)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang rust -I $(FAUSTLIBS) $<  > $@ || (rm $@ ; false; )

#########################################################################
# rule for llvm output
$(version)/llvm/%.llvm: $(SAMPLESROOT)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang llvm -I $(FAUSTLIBS) $<  > $@ || (rm $@ ; false; )

#########################################################################
# rule for interp output
$(version)/interp/%.itp: $(SAMPLESROOT)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang interp -I $(FAUSTLIBS) $<  > $@ || (rm $@ ; false; )


#########################################################################
# rules for c/c++ compilation
$(version)/cpp/%.o: $(version)/cpp/%.cpp
	$(eval tmp := $(patsubst $(version)/cpp/%, $(SAMPLESROOT)/%, $(<D)))	
	$(CXX) -c $(OPTIONS) -I$(tmp) $< -o $@

$(version)/ocpp/%.o: $(version)/ocpp/%.cpp
	$(eval tmp := $(patsubst $(version)/ocpp/%, $(SAMPLESROOT)/%, $(<D)))	
	$(CXX) -c $(OPTIONS) -I$(tmp) $< -o $@

$(version)/c/%.o: $(version)/c/%.c
	$(eval tmp := $(patsubst $(version)/c/%, $(SAMPLESROOT)/%, $(<D)))	
	$(GCC) -c $(OPTIONS) -I$(tmp) $< -o $@
