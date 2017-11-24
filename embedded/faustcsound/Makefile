###########################################################################
#				BUILD AND INSTALL THE CSOUND6 FAUST OPCODE 
#				USAGE: make; sudo make install
###########################################################################

system			:= $(shell uname -s)

ifeq ($(system), Darwin)
CSOUNDHEADERS := /Library/Frameworks/CsoundLib64.framework/Headers/
CSOUNDOPCODES := /Library/Frameworks/CsoundLib64.framework/Resources/Opcodes64/
FAUSTOPCODE := libfaustcsound.dylib
else
CSOUNDHEADERS := XXXXX
CSOUNDOPCODES := YYYYY
FAUSTOPCODE := libfaustcsound.so
endif


build : $(FAUSTOPCODE)

install : 
	cp $(FAUSTOPCODE) $(CSOUNDOPCODES)
	
clean :
	rm -rf $(FAUSTOPCODE)
	

### FOR DARWIN	
libfaustcsound.dylib : faustcsound.cpp
	g++ -O3 -dynamiclib -o libfaustcsound.dylib faustcsound.cpp -DFAUSTFLOAT=double -DUSE_DOUBLE -I$(CSOUNDHEADERS) -lz -lncurses -L/usr/local/lib -lfaust `llvm-config --ldflags --libs all`

## FOR LINUX
libfaustcsound.so : faustcsound.cpp
 	g++ -O3 -shared -o libfaustcsound.so faustcsound.cpp -DFAUSTFLOAT=double -DUSE_DOUBLE -I$(CSOUNDHEADERS)  -L/usr/local/lib -lfaust `llvm-config --ldflags --libs all`
