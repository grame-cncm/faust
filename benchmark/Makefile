system	:= $(shell uname -s)

ifeq ($(system), Darwin)
MYGCCFLAGS := '-O3  -mfpmath=sse -msse -msse2 -msse3 -ffast-math -ftree-vectorize'
else
MYGCCFLAGS := '-O3 -march=native -mfpmath=sse -msse -msse2 -msse3 -ffast-math -ftree-vectorize'
endif

MYICCFLAGS := '-O3 -xHost -ftz -fno-alias -fp-model fast=2' 


VSIZE := 1024

all : icc gcc
icc : ialsascal ialsavec ialsavec2 ialsavec4 ialsaomp2 ialsasch ialsasch2
gcc : galsascal galsavec galsavec2 galsavec4 galsaomp2 galsasch galsasch2
osx : gcoreaudioscal gcoreaudiovec1 gcoreaudiovec2 gcoreaudiovec3 gcoreaudiovec4 gcoreaudiosch gcoreaudiosch2


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

gcoreaudioscal :
	install -d gcoreaudioscaldir
	$(MAKE) DEST='gcoreaudioscaldir/' ARCH='coreaudio-gtk-bench.cpp' LIB='-lpthread -framework CoreAudio -framework AudioUnit -framework CoreServices `pkg-config --cflags --libs gtk+-2.0`' CXX='g++' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

gcoreaudiovec1 :
	install -d gcoreaudiovec1dir
	$(MAKE) DEST='gcoreaudiovec1dir/' ARCH='coreaudio-gtk-bench.cpp' VEC='-vec -lv 1 -vs $(VSIZE)' LIB='-lpthread -framework CoreAudio -framework AudioUnit -framework CoreServices `pkg-config --cflags --libs gtk+-2.0`' CXX='g++' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

gcoreaudiovec2 :
	install -d gcoreaudiovec2dir
	$(MAKE) DEST='gcoreaudiovec2dir/' ARCH='coreaudio-gtk-bench.cpp' VEC='-vec -dfs -vs $(VSIZE)' LIB='-lpthread -framework CoreAudio -framework AudioUnit -framework CoreServices `pkg-config --cflags --libs gtk+-2.0`' CXX='g++' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

gcoreaudiovec3 :
	install -d gcoreaudiovec3dir
	$(MAKE) DEST='gcoreaudiovec3dir/' ARCH='coreaudio-gtk-bench.cpp' VEC='-vec -g -vs $(VSIZE)' LIB='-lpthread -framework CoreAudio -framework AudioUnit -framework CoreServices `pkg-config --cflags --libs gtk+-2.0`' CXX='g++' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

gcoreaudiovec4 :
	install -d gcoreaudiovec4dir
	$(MAKE) DEST='gcoreaudiovec4dir/' ARCH='coreaudio-gtk-bench.cpp' VEC='-vec -dfs -g -vs $(VSIZE)' LIB='-lpthread -framework CoreAudio -framework AudioUnit -framework CoreServices `pkg-config --cflags --libs gtk+-2.0`' CXX='g++' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

gcoreaudiosch :
	install -d gcoreaudioschdir
	$(MAKE) DEST='gcoreaudioschdir/' ARCH='coreaudio-gtk-bench.cpp' VEC='-sch -vs $(VSIZE)' LIB='-lpthread -framework CoreAudio -framework AudioUnit -framework CoreServices `pkg-config --cflags --libs gtk+-2.0`' CXX='g++' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

gcoreaudiosch2 :
	install -d gcoreaudiosch2dir
	$(MAKE) DEST='gcoreaudiosch2dir/' ARCH='coreaudio-gtk-bench.cpp' VEC='-sch -g -vs $(VSIZE)' LIB='-lpthread -framework CoreAudio -framework AudioUnit -framework CoreServices `pkg-config --cflags --libs gtk+-2.0`' CXX='g++' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

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


clean :
	rm -rf *dir
