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
MAKE ?= make

SAMPLESROOT := ../..
REGRESSION := ..
FAUSTLIBS ?= ../../libraries
FAUSTINC  ?= ../../architecture/faust

version := $(shell $(FAUST) --version | grep Version | sed -e 's/^..*Version //')

dspfiles  = $(shell find $(SAMPLESROOT)/examples -name "*.dsp" | grep -v TODO | grep -v old | grep -v faust-stk)
regressionfiles = $(shell find $(REGRESSION)/codegen-tests -name "*.dsp")

langs    := js ajs wasm java fir rust llvm
gcclangs := cpp o.cpp c 
examplesout   := $(foreach lang, $(langs), $(dspfiles:$(SAMPLESROOT)/%.dsp=$(version)/$(lang)/%.$(lang)))
regressionout := $(foreach lang, $(langs), $(regressionfiles:$(REGRESSION)/%.dsp=$(version)/$(lang)/%.$(lang)))
interpout   := $(dspfiles:$(SAMPLESROOT)/%.dsp=$(version)/interp/%.itp)
interpout   += $(regressionfiles:$(REGRESSION)/%.dsp=$(version)/interp/%.itp)

gccexamplesout   := $(foreach lang, $(gcclangs), $(dspfiles:$(SAMPLESROOT)/%.dsp=$(version)/$(lang)/%.$(lang)))
gccregressionout := $(foreach lang, $(gcclangs), $(regressionfiles:$(REGRESSION)/%.dsp=$(version)/$(lang)/%.$(lang)))

gccobj := $(gccexamplesout:%.cpp=%.o)  $(gccexamplesout:%.ocpp=%.o) $(gccexamplesout:%.c=%.o)
gccobj += $(gccregressionout:%.cpp=%.o)  $(gccregressionout:%.ocpp=%.o) $(gccregressionout:%.c=%.o)

CXX ?= g++
GCC ?= gcc

OPTIONS := -Wno-unused-command-line-argument -I$(FAUSTINC)

all:
	$(MAKE) examples
	$(MAKE) regression
	$(MAKE) gcc


help:
	@echo "-------- FAUST compilation tests --------"
	@echo "Available targets are:"
	@echo " 'all' (default): compiles all the dsp found in the examples and regression"
	@echo "              folders using all backends (apart the interp backend)"
	@echo "              C and C++ output are also compile using $(GCC) and $(CXX)"
	@echo "              Output is located in a folder named using faust version"
	@echo "Specific targets:"
	@echo " 'examples'   : use only the examples folder"
	@echo " 'regression' : use only the regression folder"
	@echo " 'gcc'        : use only the c, cpp and ocpp backends and compiles"
	@echo "                the C and C++ output"
	@echo " 'interp'     : compiles using the interpreter backend"
	
gcc: $(gccexamplesout) $(gccregressionout) $(gccobj)
examples: $(examplesout) $(gccexamplesout)
regression: $(regressionout) $(gccregressionout)

clean:
	rm -rf $(version)


#########################################################################
# interp lang has a special status since the corresponding backend may not
# be available due to gcc specific extensions
interp: $(interpout)

test:
	@echo $(interpout)

#########################################################################
# rule for cpp output
$(version)/cpp/%.cpp: $(SAMPLESROOT)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang cpp -I $(FAUSTLIBS) -a ./min.cpp $<  -o $@ 
$(version)/cpp/%.cpp: $(REGRESSION)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang cpp -I $(FAUSTLIBS) -a ./min.cpp $<  -o $@ 

#########################################################################
# rule for ocpp output
$(version)/o.cpp/%.o.cpp: $(SAMPLESROOT)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang ocpp -I $(FAUSTLIBS) -a ./min.cpp $<  -o $@ 
$(version)/o.cpp/%.o.cpp: $(REGRESSION)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang ocpp -I $(FAUSTLIBS) -a ./min.cpp $<  -o $@ 

#########################################################################
# rule for c output
$(version)/c/%.c: $(SAMPLESROOT)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang c -I $(FAUSTLIBS) -a ./min.c $<  -o $@ 
$(version)/c/%.c: $(REGRESSION)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang c -I $(FAUSTLIBS) -a ./min.c $<  -o $@ 

#########################################################################
# rule for js output
$(version)/js/%.js: $(SAMPLESROOT)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang js -I $(FAUSTLIBS) $<  -o $@ 
$(version)/js/%.js: $(REGRESSION)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang js -I $(FAUSTLIBS) $<  -o $@ 

#########################################################################
# rule for asmjs output
$(version)/ajs/%.ajs: $(SAMPLESROOT)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang ajs -I $(FAUSTLIBS) $<  -o $@ 
$(version)/ajs/%.ajs: $(REGRESSION)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang ajs -I $(FAUSTLIBS) $<  -o $@ 

#########################################################################
# rule for wasm output
$(version)/wasm/%.wasm: $(SAMPLESROOT)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang wast/wasm -I $(FAUSTLIBS) $<  -o $@ 
$(version)/wasm/%.wasm: $(REGRESSION)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang wast/wasm -I $(FAUSTLIBS) $<  -o $@ 

#########################################################################
# rule for java output
$(version)/java/%.java: $(SAMPLESROOT)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang java -I $(FAUSTLIBS) $<  -o $@ 
$(version)/java/%.java: $(REGRESSION)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang java -I $(FAUSTLIBS) $<  -o $@ 

#########################################################################
# rule for fir output
$(version)/fir/%.fir: $(SAMPLESROOT)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang fir -I $(FAUSTLIBS) $<  -o $@ 
$(version)/fir/%.fir: $(REGRESSION)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang fir -I $(FAUSTLIBS) $<  -o $@ 

#########################################################################
# rule for rust output
$(version)/rust/%.rust: $(SAMPLESROOT)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang rust -I $(FAUSTLIBS) $<  -o $@ 
$(version)/rust/%.rust: $(REGRESSION)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang rust -I $(FAUSTLIBS) $<  -o $@ 

#########################################################################
# rule for llvm output
$(version)/llvm/%.llvm: $(SAMPLESROOT)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang llvm -I $(FAUSTLIBS) $<  -o $@ 
$(version)/llvm/%.llvm: $(REGRESSION)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang llvm -I $(FAUSTLIBS) $<  -o $@ 

#########################################################################
# rule for interp output
$(version)/interp/%.itp: $(SAMPLESROOT)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang interp -I $(FAUSTLIBS) $<  -o $@ 
$(version)/interp/%.itp: $(REGRESSION)/%.dsp
	@[ -d $(@D) ] || mkdir -p $(@D)
	$(FAUST) -lang interp -I $(FAUSTLIBS) $<  -o $@ 


#########################################################################
# rules for c/c++ compilation
$(version)/cpp/%.o: $(version)/cpp/%.cpp
	$(eval tmp := $(patsubst $(version)/cpp/%, $(SAMPLESROOT)/%, $(<D)))	
	$(CXX) -c $(OPTIONS) -I$(tmp) $< -o $@ 

$(version)/o.cpp/%.o.o: $(version)/o.cpp/%.o.cpp
	$(eval tmp := $(patsubst $(version)/ocpp/%, $(SAMPLESROOT)/%, $(<D)))	
	$(CXX) -c $(OPTIONS) -I$(tmp) $< -o $@ 

$(version)/c/%.o: $(version)/c/%.c
	$(eval tmp := $(patsubst $(version)/c/%, $(SAMPLESROOT)/%, $(<D)))	
	$(GCC) -c $(OPTIONS) -I$(tmp) $< -o $@ 
