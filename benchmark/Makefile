# Directory containing Faust .lib and .cpp architecture files:
ck1 := /opt/local/share/faust/music.lib
ck2 := /usr/local/share/faust/music.lib
ck3 := $(FAUST_LIB_PATH)/faust/music.lib
LIB := $(if $(wildcard $(ck1)),/opt/local/lib,"")
LIB := $(if $(wildcard $(ck2)),/usr/local/lib,$(LIB))
LIB := $(if $(wildcard $(ck3)),$(FAUST_LIB_PATH),$(LIB))

DESTDIR ?=
PREFIX ?= /usr/local

prefix := $(DESTDIR)$(PREFIX)

system	:= $(shell uname -s)

LLVM_VERSION = $(shell llvm-config --version)

ifeq ($(LLVM_VERSION), 3.1)
LLVM_VERSION = LLVM_31
CXX = /opt/local/libexec/llvm-3.1/bin/clang++
endif

ifeq ($(LLVM_VERSION), 3.2)
LLVM_VERSION = LLVM_32
CXX = /opt/local/libexec/llvm-3.2/bin/clang++
endif

ifeq ($(LLVM_VERSION), 3.3)
LLVM_VERSION = LLVM_33
CXX = /opt/local/libexec/llvm-3.3/bin/clang++
LLC = /opt/local/libexec/llvm-3.3/bin/llc
endif

ifeq ($(LLVM_VERSION),$(filter $(LLVM_VERSION),3.4, 3.4.1, 3.4.2))
LLVM_VERSION = LLVM_34
CXX = /opt/local/libexec/llvm-3.4/bin/clang++
LLC = /opt/local/libexec/llvm-3.4/bin/llc
endif

ifeq ($(LLVM_VERSION), 3.4.2)
LLVM_VERSION = LLVM_34
CXX = /opt/local/libexec/llvm-3.4/bin/clang++
LLC = /opt/local/libexec/llvm-3.4/bin/llc
endif

ifeq ($(LLVM_VERSION), 3.5)
LLVM_VERSION = LLVM_35
CXX = /opt/local/libexec/llvm-3.5/bin/clang++
LLC = /opt/local/libexec/llvm-3.5/bin/llc
endif

ifeq ($(LLVM_VERSION),$(filter $(LLVM_VERSION), 3.6.0 3.6.1 3.6.2))
LLVM_VERSION = LLVM_36
CXX = /opt/local/libexec/llvm-3.6/bin/clang++
LLC = /opt/local/libexec/llvm-3.6/bin/llc
endif

ifeq ($(LLVM_VERSION),$(filter $(LLVM_VERSION), 3.7.0 3.7.1 3.7.2))
LLVM_VERSION = LLVM_37
CXX = /opt/local/libexec/llvm-3.7/bin/clang++
LLC = /opt/local/libexec/llvm-3.7/bin/llc
endif

ifeq ($(LLVM_VERSION),$(filter $(LLVM_VERSION), 3.8.0 3.8.1))
LLVM_VERSION = LLVM_38
CXX = /opt/local/libexec/llvm-3.8/bin/clang++
LLC = /opt/local/libexec/llvm-3.8/bin/llc
endif

ifeq ($(LLVM_VERSION),$(filter $(LLVM_VERSION), 3.9.0 3.9.1))
LLVM_VERSION  = LLVM_39
CXX = /opt/local/libexec/llvm-3.9/bin/clang++
LLC = /opt/local/libexec/llvm-3.9/bin/llc
endif

ifeq ($(LLVM_VERSION),$(filter $(LLVM_VERSION), 4.0.0, 4.0.1))
LLVM_VERSION  = LLVM_40
CXX = /opt/local/libexec/llvm-4.0/bin/clang++
LLC = /opt/local/libexec/llvm-4.0/bin/llc
endif

ifeq ($(LLVM_VERSION),$(filter $(LLVM_VERSION), 5.0.0))
LLVM_VERSION  = LLVM_50
CXX = /opt/local/libexec/llvm-5.0/bin/clang++
LLC = /opt/local/libexec/llvm-5.0/bin/llc
endif

ifeq ($(system), Darwin)
#MYGCCFLAGS := '-O3 -mfpmath=sse -msse -msse2 -msse3 -ffast-math '
#MYGCCFLAGS := '-O3 -mfpmath=sse -msse -msse2 -msse3 -ffast-math -fvectorize -fslp-vectorize'

MYGCCFLAGS := '-O3 -march=native -fvectorize -fslp-vectorize-aggressive'

else
MYGCCFLAGS := '-O3  -march=native -mfpmath=sse -msse -msse2 -msse3 -ffast-math -ftree-vectorize'
endif

MYICCFLAGS := '-O3 -xHost -ftz -fno-alias -fp-model fast=2' 

VSIZE := 1024

all : icc gcc
icc : ialsascal ialsavec ialsavec2 ialsavec4 ialsaomp2 ialsasch ialsasch2
gcc : galsascal galsavec galsavec2 galsavec4 galsaomp2 galsasch galsasch2
#osx : gcoreaudioscal gcoreaudiovec1 gcoreaudiovec2 gcoreaudiovec3 gcoreaudiovec4 gcoreaudiosch gcoreaudiosch2
osx : gcoreaudioscal gcoreaudiovec1 gcoreaudiovec2 gcoreaudiosch gcoreaudiollvm  bscal bvec1 bvec2 bscalllvm
#osx : bscal bvec1 bvec2 bscalllvm


### intel-compiler single-precision x {scalar, vector and openMP}

ialsascal :
	install -d ialsascaldir
	$(MAKE) DEST='ialsascaldir/' ARCH='alsa-gtk-bench.cpp' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

ialsasch :
	install -d ialsaschdir
	$(MAKE) DEST='ialsaschdir/' ARCH='alsa-gtk-bench.cpp' VEC='-sch -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

ialsasch2 :
	install -d ialsasch2dir
	$(MAKE) DEST='ialsasch2dir/' ARCH='alsa-gtk-bench.cpp' VEC='-sch -g -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

ialsavec :
	install -d ialsavecdir
	$(MAKE) DEST='ialsavecdir/' ARCH='alsa-gtk-bench.cpp' VEC='-vec -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

ialsavec1 :
	install -d ialsavec1dir
	$(MAKE) DEST='ialsavec1dir/' ARCH='alsa-gtk-bench.cpp' VEC='-vec -lv 1 -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

ialsavec2 :
	install -d ialsavec2dir
	$(MAKE) DEST='ialsavec2dir/' ARCH='alsa-gtk-bench.cpp' VEC='-vec -dfs -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

ialsavec3 :
	install -d ialsavec3dir
	$(MAKE) DEST='ialsavec3dir/' ARCH='alsa-gtk-bench.cpp' VEC='-vec -g -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

ialsavec4 :
	install -d ialsavec4dir
	$(MAKE) DEST='ialsavec4dir/' ARCH='alsa-gtk-bench.cpp' VEC='-vec -g -vs 16' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

ialsaomp :
	install -d ialsaompdir
	$(MAKE) DEST='ialsaompdir/' ARCH='alsa-gtk-bench.cpp' VEC='-omp -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS='-openmp '$(MYICCFLAGS) -f Makefile.compile

ialsaomp2 :
	install -d ialsaomp2dir
	$(MAKE) DEST='ialsaomp2dir/' ARCH='alsa-gtk-bench.cpp' VEC='-omp -g -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS='-openmp '$(MYICCFLAGS) -f Makefile.compile

### gcc-compiler single-precision x {scalar, vector and openMP}

galsascal :
	install -d galsascaldir
	$(MAKE) DEST='galsascaldir/' ARCH='alsa-gtk-bench.cpp' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='g++' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

galsasch :
	install -d galsaschdir
	$(MAKE) DEST='galsaschdir/' ARCH='alsa-gtk-bench.cpp' VEC='-sch -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='g++' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

galsasch2 :
	install -d galsasch2dir
	$(MAKE) DEST='galsasch2dir/' ARCH='alsa-gtk-bench.cpp' VEC='-sch -g -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='g++' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

galsavec :
	install -d galsavecdir
	$(MAKE) DEST='galsavecdir/' ARCH='alsa-gtk-bench.cpp' VEC='-vec -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='g++' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

galsavec1 :
	install -d galsavec1dir
	$(MAKE) DEST='galsavec1dir/' ARCH='alsa-gtk-bench.cpp' VEC='-vec -lv 1 -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='g++' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

galsavec2 :
	install -d galsavec2dir
	$(MAKE) DEST='galsavec2dir/' ARCH='alsa-gtk-bench.cpp' VEC='-vec -dfs -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='g++' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

galsavec3 :
	install -d galsavec3dir
	$(MAKE) DEST='galsavec3dir/' ARCH='alsa-gtk-bench.cpp' VEC='-vec -g -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='g++' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

galsavec4 :
	install -d galsavec4dir
	$(MAKE) DEST='galsavec4dir/' ARCH='alsa-gtk-bench.cpp' VEC='-vec -g -vs 16' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='g++' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

galsaomp :
	install -d galsaompdir
	$(MAKE) DEST='galsaompdir/' ARCH='alsa-gtk-bench.cpp' VEC='-omp -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='g++' CXXFLAGS='-fopenmp '$(MYGCCFLAGS) -f Makefile.compile

galsaomp2 :
	install -d galsaomp2dir
	$(MAKE) DEST='galsaomp2dir/' ARCH='alsa-gtk-bench.cpp' VEC='-omp -g -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='g++' CXXFLAGS='-fopenmp '$(MYGCCFLAGS) -f Makefile.compile


# OSX 
	
gcoreaudiollvm : coreaudio-gtk-llvm-bench.cpp
	$(CXX) -O3 -D$(LLVM_VERSION) -emit-llvm -S ../architecture/scheduler.cpp -o scheduler.ll
	$(CXX) -O3 coreaudio-gtk-llvm-bench.cpp /usr/local/lib/libfaust.a  -lpthread -framework CoreAudio -framework AudioUnit -framework CoreServices `pkg-config --cflags --libs gtk+-2.0` `llvm-config --ldflags --libs all --system-libs` -o gcoreaudiollvm

bscalllvm : console-bench-llvm.cpp
	$(CXX) -O3 console-bench-llvm.cpp /usr/local/lib/libfaust.a `llvm-config --ldflags --libs all --system-libs` -o bscalllvm

bscal :
	install -d bscaldir
	$(MAKE) DEST='bscaldir/' ARCH='console-bench.cpp' LIB='' CXX=$(CXX) CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

bvec1 :
	install -d bvec1dir
	$(MAKE) DEST='bvec1dir/' ARCH='console-bench.cpp' VEC='-vec -lv 1 -vs $(VSIZE)' LIB='' CXX=$(CXX) CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

bvec2:
	install -d bvec2dir
	$(MAKE) DEST='bvec2dir/' ARCH='console-bench.cpp' VEC='-vec -dfs -vs $(VSIZE)' LIB='' CXX=$(CXX) CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

gcoreaudioscal :
	install -d gcoreaudioscaldir
	$(MAKE) DEST='gcoreaudioscaldir/' ARCH='coreaudio-gtk-bench.cpp' LIB='-lpthread -framework CoreAudio -framework AudioUnit -framework CoreServices `pkg-config --cflags --libs gtk+-2.0`' CXX=$(CXX) CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile


gcoreaudiovec1 :
	install -d gcoreaudiovec1dir
	$(MAKE) DEST='gcoreaudiovec1dir/' ARCH='coreaudio-gtk-bench.cpp' VEC='-vec -lv 1 -vs $(VSIZE)' LIB='-lpthread -framework CoreAudio -framework AudioUnit -framework CoreServices `pkg-config --cflags --libs gtk+-2.0`' CXX=$(CXX) CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

gcoreaudiovec2 :
	install -d gcoreaudiovec2dir
	$(MAKE) DEST='gcoreaudiovec2dir/' ARCH='coreaudio-gtk-bench.cpp' VEC='-vec -dfs -vs $(VSIZE)' LIB='-lpthread -framework CoreAudio -framework AudioUnit -framework CoreServices `pkg-config --cflags --libs gtk+-2.0`' CXX=$(CXX) CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

gcoreaudiovec3 :
	install -d gcoreaudiovec3dir
	$(MAKE) DEST='gcoreaudiovec3dir/' ARCH='coreaudio-gtk-bench.cpp' VEC='-vec -g -vs $(VSIZE)' LIB='-lpthread -framework CoreAudio -framework AudioUnit -framework CoreServices `pkg-config --cflags --libs gtk+-2.0`' CXX=$(CXX) CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

gcoreaudiovec4 :
	install -d gcoreaudiovec4dir
	$(MAKE) DEST='gcoreaudiovec4dir/' ARCH='coreaudio-gtk-bench.cpp' VEC='-vec -dfs -g -vs $(VSIZE)' LIB='-lpthread -framework CoreAudio -framework AudioUnit -framework CoreServices `pkg-config --cflags --libs gtk+-2.0`' CXX=$(CXX) CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

gcoreaudiosch :
	install -d gcoreaudioschdir
	$(MAKE) DEST='gcoreaudioschdir/' ARCH='coreaudio-gtk-bench.cpp' VEC='-sch -vs $(VSIZE)' LIB='-lpthread -framework CoreAudio -framework AudioUnit -framework CoreServices `pkg-config --cflags --libs gtk+-2.0`' CXX=$(CXX) CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

gcoreaudiosch2 :
	install -d gcoreaudiosch2dir
	$(MAKE) DEST='gcoreaudiosch2dir/' ARCH='coreaudio-gtk-bench.cpp' VEC='-sch -g -vs $(VSIZE)' LIB='-lpthread -framework CoreAudio -framework AudioUnit -framework CoreServices `pkg-config --cflags --libs gtk+-2.0`' CXX=$(CXX) CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

### intel-compiler double-precision x {scalar, vector and openMP}

idalsascal :
	install -d idalsascaldir
	$(MAKE) DEST='idalsascaldir/' ARCH='alsa-gtk-bench.cpp' VEC='-double' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

idalsavec :
	install -d idalsavecdir
	$(MAKE) DEST='idalsavecdir/' ARCH='alsa-gtk-bench.cpp' VEC='-double -vec -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

idalsaomp :
	install -d idalsaompdir
	$(MAKE) DEST='idalsaompdir/' ARCH='alsa-gtk-bench.cpp' VEC='-double -omp -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS='-openmp '$(MYICCFLAGS) -f Makefile.compile

### intel-compiler quad-precision x {scalar, vector and openMP}

iqalsascal :
	install -d iqalsascaldir
	$(MAKE) DEST='iqalsascaldir/' ARCH='alsa-gtk-bench.cpp' VEC='-quad' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

iqalsavec :
	install -d iqalsavecdir
	$(MAKE) DEST='iqalsavecdir/' ARCH='alsa-gtk-bench.cpp' VEC='-quad -vec -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

iqalsaomp :
	install -d iqalsaompdir
	$(MAKE) DEST='iqalsaompdir/' ARCH='alsa-gtk-bench.cpp' VEC='-quad -omp -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS='-openmp '$(MYICCFLAGS) -f Makefile.compile


install:
	([ -e scheduler.ll ]) && cp scheduler.ll $(prefix)/lib/faust || echo scheduler.ll not found

.PHONY: depend clean

depend : 
	makedepend *.cpp -w120 -Y -I $(PREFIX)/include

clean :
	rm -rf *dir
	([ -e gcoreaudiollvm ] && rm gcoreaudiollvm) || echo gcoreaudiollvm not found
	([ -e bscalllvm ] && rm bscalllvm) || echo gcoreaudiollvm not found
	([ -e scheduler.ll ] && rm scheduler.ll ) || echo scheduler.ll not found

# DO NOT DELETE

console-bench-llvm.o: /usr/local/include/faust/audio/coreaudio-dsp.h /usr/local/include/faust/audio/audio.h
console-bench-llvm.o: /usr/local/include/faust/dsp/dsp.h /usr/local/include/faust/dsp/dsp-bench.h
console-bench-llvm.o: /usr/local/include/faust/dsp/llvm-dsp.h /usr/local/include/faust/gui/meta.h
console-bench-llvm.o: /usr/local/include/faust/misc.h
console-bench.o: /usr/local/include/faust/audio/coreaudio-dsp.h /usr/local/include/faust/audio/audio.h
console-bench.o: /usr/local/include/faust/dsp/dsp.h /usr/local/include/faust/dsp/dsp-bench.h
console-bench.o: /usr/local/include/faust/gui/UI.h /usr/local/include/faust/dsp/llvm-dsp.h
console-bench.o: /usr/local/include/faust/gui/meta.h /usr/local/include/faust/misc.h
coreaudio-gtk-bench.o: /usr/local/include/faust/audio/coreaudio-dsp.h /usr/local/include/faust/audio/audio.h
coreaudio-gtk-bench.o: /usr/local/include/faust/dsp/dsp.h /usr/local/include/faust/dsp/dsp-bench.h
coreaudio-gtk-bench.o: /usr/local/include/faust/misc.h /usr/local/include/faust/gui/meta.h
coreaudio-gtk-bench.o: /usr/local/include/faust/gui/faustgtk.h /usr/local/include/faust/gui/GUI.h
coreaudio-gtk-bench.o: /usr/local/include/faust/gui/UI.h /usr/local/include/faust/gui/ring-buffer.h
coreaudio-gtk-bench.o: /usr/local/include/faust/gui/MetaDataUI.h /usr/local/include/faust/gui/SimpleParser.h
coreaudio-gtk-llvm-bench.o: /usr/local/include/faust/audio/coreaudio-dsp.h /usr/local/include/faust/audio/audio.h
coreaudio-gtk-llvm-bench.o: /usr/local/include/faust/dsp/dsp.h /usr/local/include/faust/dsp/dsp-bench.h
coreaudio-gtk-llvm-bench.o: /usr/local/include/faust/dsp/llvm-dsp.h /usr/local/include/faust/gui/meta.h
coreaudio-gtk-llvm-bench.o: /usr/local/include/faust/misc.h /usr/local/include/faust/gui/faustgtk.h
coreaudio-gtk-llvm-bench.o: /usr/local/include/faust/gui/GUI.h /usr/local/include/faust/gui/UI.h
coreaudio-gtk-llvm-bench.o: /usr/local/include/faust/gui/ring-buffer.h /usr/local/include/faust/gui/MetaDataUI.h
coreaudio-gtk-llvm-bench.o: /usr/local/include/faust/gui/SimpleParser.h
