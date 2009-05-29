MYICCFLAGS := '-O3 -xHost -ftz -fno-alias -fp-model fast=2' 
MYGCCFLAGS := '-O3 -march=native -mfpmath=sse -msse -msse2 -msse3 -ffast-math -ftree-vectorize'

VSIZE := 3968

all : icc gcc
icc : ialsascal ialsavec ialsaomp
gcc : galsascal galsavec galsaomp


### intel-compiler single-precision x {scalar, vector and openMP}

ialsascal :
	install -d ialsascaldir
	$(MAKE) DEST='ialsascaldir/' ARCH='alsa-gtk-bench.cpp' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

ialsavec :
	install -d ialsavecdir
	$(MAKE) DEST='ialsavecdir/' ARCH='alsa-gtk-bench.cpp' VEC='-vec -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

ialsaomp :
	install -d ialsaompdir
	$(MAKE) DEST='ialsaompdir/' ARCH='alsa-gtk-bench.cpp' VEC='-omp -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS='-openmp '$(MYICCFLAGS) -f Makefile.compile



### gcc-compiler single-precision x {scalar, vector and openMP}

galsascal :
	install -d galsascaldir
	$(MAKE) DEST='galsascaldir/' ARCH='alsa-gtk-bench.cpp' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='g++' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

galsavec :
	install -d galsavecdir
	$(MAKE) DEST='galsavecdir/' ARCH='alsa-gtk-bench.cpp' VEC='-vec -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='g++' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

galsaomp :
	install -d galsaompdir
	$(MAKE) DEST='galsaompdir/' ARCH='alsa-gtk-bench.cpp' VEC='-omp -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='g++' CXXFLAGS='-fopenmp '$(MYGCCFLAGS) -f Makefile.compile



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
