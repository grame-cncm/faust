
sources =  $(wildcard Sources/*.cpp)

objects = $(sources:.cpp=.o)

os 	:= $(shell uname)
system	?= $(shell uname -s)

PREFIX ?= /usr/local

ifeq ($(system), Darwin)
	ARCHFLAGS 	:=  -arch i386 -arch x86_64
	CXX 		= g++
	CXXFLAGS	= -Wglobal-constructors  
	LIB_EXT        = dylib
	LLVM_CONFIG 	= llvm-config
	
else 
	ARCHFLAGS 	:= 
	LIBFLAGS	:= --mode=link --tag=CXX
	LLVM_CONFIG 	= $(word 1,$(wildcard /usr/bin/llvm-config*))
	LIB_EXT        = so
endif

LLVM_VERSION = $(shell $(LLVM_CONFIG) --version)

ifeq ($(system), Darwin)
	LLVM_CLANG = $(shell $(LLVM_CONFIG) --prefix)/bin/clang++
else
	LLVM_CLANG = clang++
endif

ifeq ($(LLVM_VERSION), 3.0)
	LLVM_VERSION = LLVM_30
endif

ifeq ($(LLVM_VERSION), 3.1)
	LLVM_VERSION = LLVM_31
endif

ifeq ($(LLVM_VERSION), 3.2)
	LLVM_VERSION = LLVM_32
endif

ifeq ($(LLVM_VERSION), 3.3)
	LLVM_VERSION = LLVM_33
endif

ifeq ($(LLVM_VERSION), 3.4svn)
	LLVM_VERSION = LLVM_34
endif

CXXFLAGS += -O3 -Wall -Wuninitialized 
CXXFLAGS += -fvisibility=hidden -Wno-overloaded-virtual -Wno-parentheses $(addprefix -I, $(subprojects)) -DINSTALL_PREFIX='"$(prefix)"' 
CXXFLAGS += -I`$(LLVM_CONFIG) --includedir` -I../architecture -D$(LLVM_VERSION) -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS
CXXFLAGS += $(ARCHFLAGS)


first: all

####### Build rules

all: $(objects) libfaustremote.a
#$(CXX) $(CXXFLAGS) -ldl -lcurl -ljacknet $(objects)


libfaustremote.a :
		libtool -static $(LIBFLAGS) $(objects) -o libfaustremote.a 

install:
	install libfaustremote.a  /usr/local/lib/faust/ 
	cp remote-dsp.h  /usr/local/include/faust/

clean :
	rm -f $(objects) libfaustremote.a

remote_dsp_aux.o: JsonParser.h


