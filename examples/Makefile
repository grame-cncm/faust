MYICCFLAGS := '-O3 -xT -ftz -fno-alias -fp-model fast=2' 
MYGCCFLAGS := '-O3 -march=native -mfpmath=sse -msse -msse2 -msse3 -ffast-math'

SC_SOURCE_DIR = ../../supercollider

all : jackgtk

test: ijackgtk ijackvec ijackomp gjackgtk gjackvec gjackomp

ijackgtk :
	install -d ijackgtkdir
	$(MAKE) DEST='ijackgtkdir/' ARCH='jack-gtk.cpp' LIB='-L/usr/local/lib `pkg-config --cflags --libs jack gtk+-2.0` -I/usr/local/include' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

ijackvec :
	install -d ijackvecdir
	$(MAKE) DEST='ijackvecdir/' ARCH='jack-gtk.cpp' VEC='-vec -vs 4096' LIB='-L/usr/local/lib `pkg-config --cflags --libs jack gtk+-2.0` -I/usr/local/include' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

ijackomp :
	install -d ijackompdir
	$(MAKE) DEST='ijackompdir/' ARCH='jack-gtk.cpp' VEC='-vs 4096 -omp' LIB='-L/usr/local/lib `pkg-config --cflags --libs jack gtk+-2.0` -I/usr/local/include' CXX='icc' CXXFLAGS='-openmp '$(MYICCFLAGS) -f Makefile.compile

gjackgtk :
	install -d gjackgtkdir
	$(MAKE) DEST='gjackgtkdir/' ARCH='jack-gtk.cpp' LIB='-L/usr/local/lib `pkg-config --cflags --libs jack gtk+-2.0` -I/usr/local/include' CXX='g++' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

gjackvec :
	install -d gjackvecdir
	$(MAKE) DEST='gjackvecdir/' ARCH='jack-gtk.cpp' VEC='-vec -vs 4096' LIB='-L/usr/local/lib `pkg-config --cflags --libs jack gtk+-2.0` -I/usr/local/include' CXX='g++' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

gjackomp :
	install -d gjackompdir
	$(MAKE) DEST='gjackompdir/' ARCH='jack-gtk.cpp' VEC='-vec -vs 4096 -omp' LIB='-L/usr/local/lib `pkg-config --cflags --libs jack gtk+-2.0` -I/usr/local/include' CXX='g++' CXXFLAGS='-fopenmp '$(MYGCCFLAGS) -f Makefile.compile

svg:
	$(MAKE) -f Makefile.svg
	
puredata :
	install -d puredatadir
	$(MAKE) DEST='puredatadir/' ARCH='puredata.cpp' LIB='' -f Makefile.pdcompile

alsagtk :
	install -d alsagtkdir
	$(MAKE) DEST='alsagtkdir/' ARCH='alsa-gtk.cpp' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' -f Makefile.compile

jackgtk :
	install -d jackgtkdir
	$(MAKE) DEST='jackgtkdir/' ARCH='jack-gtk.cpp' LIB='`pkg-config --cflags --libs jack gtk+-2.0`' -f Makefile.compile

msjackgtk :
	install -d msjackgtkdir
	$(MAKE) DEST='msjackgtkdir/' ARCH='ms-jack-gtk.cpp' LIB='-lMidiShare `pkg-config --cflags --libs jack gtk+-2.0`' -f Makefile.compile

jackqt :
	install -d jackqtdir
	$(MAKE) DEST='jackqtdir/' ARCH='jack-qt.cpp' LIB='-ljack' -f Makefile.qtcompile

alsaqt :
	install -d alsaqtdir
	$(MAKE) DEST='alsaqtdir/' ARCH='alsa-qt.cpp' LIB='-lpthread -lasound' -f Makefile.qtcompile

ladspa :
	install -d ladspadir
	$(MAKE) DEST='ladspadir/' ARCH='ladspa.cpp' LIB='-fPIC -shared' EXT='.so' -f Makefile.ladspacompile
	
jackwx :
	install -d jackwxdir
	$(MAKE) DEST='jackwxdir/' ARCH='jack-wx.cpp' LIB='`pkg-config jack  --cflags --libs` `wx-config --cflags --libs`' -f Makefile.compile

ossgtk :
	install -d ossgtkdir
	$(MAKE) DEST='ossgtkdir/' ARCH='oss-gtk.cpp' LIB='-lpthread  `pkg-config gtk+-2.0  --cflags --libs`' -f Makefile.compile

osswx :
	install -d osswxdir
	$(MAKE) DEST='osswxdir/' ARCH='oss-wx.cpp' LIB='-lpthread  `wx-config --cflags --libs`' -f Makefile.compile

pagtk :
	install -d pagtkdir
	$(MAKE) DEST='pagtkdir/' ARCH='pa-gtk.cpp' LIB='-lpthread  -lportaudio `pkg-config gtk+-2.0  --cflags --libs`' -f Makefile.compile

pawx :
	install -d pawxdir
	$(MAKE) DEST='pawxdir/' ARCH='pa-wx.cpp' LIB='-lpthread  -lportaudio `wx-config --cflags --libs`' -f Makefile.compile

module :
	install -d moduledir
	$(MAKE) DEST='moduledir/' ARCH='module.cpp' LIB='-fPIC -shared' EXT='.so' -f Makefile.compile

bundle :
	install -d bundledir
	$(MAKE) DEST='bundledir/' ARCH='module.cpp' LIB='-fPIC -bundle' EXT='.so' -f Makefile.compile

msp :
	install -d mspdir
	$(MAKE) DEST='mspdir/' ARCH='max-msp.cpp' LIB='' -f Makefile.mspcompile

vst :
	install -d vstdir
	$(MAKE) DEST='vstdir/' ARCH='vst.cpp' LIB='' -f Makefile.vstcompile

bench :
	install -d benchdir
	$(MAKE) DEST='benchdir/' ARCH='bench.cpp' LIB='' -f Makefile.compile

ibench :
	install -d ibenchdir
	$(MAKE) DEST='ibenchdir/' ARCH='parbench.cpp' LIB='' CXX='icc' CXXFLAGS='-O3 -xT -ftz -fno-alias -fp-model fast=2' -f Makefile.compile

ivecbench :
	install -d ivecbenchdir
	$(MAKE) DEST='ivecbenchdir/' ARCH='parbench.cpp' VEC='-vec -vs 1024' LIB='' CXX='icc' CXXFLAGS='-O3 -xT -ftz -fno-alias -fp-model fast=2' -f Makefile.compile

ivecjack :
	install -d ivecjackdir
	$(MAKE) DEST='ivecjackdir/' ARCH='jack-gtk.cpp' VEC='-vec -vs 1024' LIB='`pkg-config --cflags --libs jack gtk+-2.0`' CXX='icc' CXXFLAGS='-O3 -xT -ftz -fno-alias -fp-model fast=2' -f Makefile.compile

iparbench :
	install -d iparbenchdir
	$(MAKE) DEST='iparbenchdir/' ARCH='parbench.cpp' VEC='-vec -vs 1024 -omp' LIB='' CXX='icc' CXXFLAGS='-O3 -openmp -xT -ftz -fno-alias -fp-model fast=2' -f Makefile.compile

gparbench :
	install -d gparbenchdir
	$(MAKE) DEST='gparbenchdir/' ARCH='parbench.cpp' VEC='-vec -vs 1024 -omp' LIB='' CXX='g++' CXXFLAGS='-O3 -march=native -mfpmath=sse -msse -msse2 -msse3 -ffast-math' -f Makefile.compile

sndfile :
	install -d sndfiledir
	$(MAKE) DEST='sndfiledir/' ARCH='sndfile.cpp' LIB='-lsndfile' -f Makefile.compile

plot :
	install -d plotdir
	$(MAKE) DEST='plotdir/' ARCH='plot.cpp' LIB='' -f Makefile.compile

matlabplot :
	install -d matlabplotdir
	$(MAKE) DEST='matlabplotdir/' ARCH='matlabplot.cpp' LIB='' -f Makefile.compile

q :
	install -d qdir
	$(MAKE) DEST='qdir/' ARCH='q.cpp' LIB='' -f Makefile.qcompile

# supercollider :
# 	install -d supercolliderdir
# 	$(MAKE) DEST='supercolliderdir/' ARCH='../architecture/supercollider.cpp' CXXFLAGS='`pkg-config --cflags libscsynth`' LIB='-fPIC -shared' EXT='.so' -f Makefile.sccompile

supercollider :
	ls *.dsp | ../tools/scbuilder/scbuilder \
			FAUST2SC=../tools/faust2sc-1.0.0/faust2sc \
			FAUST2SC_PREFIX="Faust_" \
			SC_SOURCE_DIR=$(SC_SOURCE_DIR) \
			BUILD_DIR=supercolliderdir

jackconsole :
	install -d jackconsoledir
	$(MAKE) DEST='jackconsoledir/' ARCH='jack-console.cpp' LIB='`pkg-config --cflags --libs jack `' -f Makefile.compile


clean :
	rm -rf *dir
