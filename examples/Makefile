MYICCFLAGS := '-O3 -xT -ftz -fno-alias -fp-model fast=2' 
MYGCCFLAGS := '-O3 -march=native -mfpmath=sse -msse -msse2 -msse3 -ffast-math'
#MYGCCFLAGS := '-O3'
VSIZE := 1024

SC_SOURCE_DIR = ../../supercollider


all : jackgtk

test: ijackgtk ijackvec ijackomp gjackgtk gjackvec gjackomp

ijackgtk :
	install -d ijackgtkdir
	$(MAKE) DEST='ijackgtkdir/' ARCH='jack-gtk.cpp' LIB='-L/usr/local/lib `pkg-config --cflags --libs jack gtk+-2.0` -I/usr/local/include' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

ijackvec :
	install -d ijackvecdir
	$(MAKE) DEST='ijackvecdir/' ARCH='jack-gtk.cpp' VEC='-vec -vs $(VSIZE)' LIB='-L/usr/local/lib `pkg-config --cflags --libs jack gtk+-2.0` -I/usr/local/include' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

ijackomp :
	install -d ijackompdir
	$(MAKE) DEST='ijackompdir/' ARCH='jack-gtk.cpp' VEC='-vs $(VSIZE) -omp' LIB='-L/usr/local/lib `pkg-config --cflags --libs jack gtk+-2.0` -I/usr/local/include' CXX='icc' CXXFLAGS='-openmp '$(MYICCFLAGS) -f Makefile.compile

gjackgtk :
	install -d gjackgtkdir
	$(MAKE) DEST='gjackgtkdir/' ARCH='jack-gtk.cpp' LIB='-L/usr/local/lib `pkg-config --cflags --libs jack gtk+-2.0` -I/usr/local/include' CXX='g++' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

gjackvec :
	install -d gjackvecdir
	$(MAKE) DEST='gjackvecdir/' ARCH='jack-gtk.cpp' VEC='-vec -vs $(VSIZE)' LIB='-L/usr/local/lib `pkg-config --cflags --libs jack gtk+-2.0` -I/usr/local/include' CXX='g++' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

gjackomp :
	install -d gjackompdir
	$(MAKE) DEST='gjackompdir/' ARCH='jack-gtk.cpp' VEC='-vec -vs $(VSIZE) -omp' LIB='-L/usr/local/lib `pkg-config --cflags --libs jack gtk+-2.0` -I/usr/local/include' CXX='g++' CXXFLAGS='-fopenmp '$(MYGCCFLAGS) -f Makefile.compile

svg:
	$(MAKE) -f Makefile.svgcompile
	
puredata :
	install -d puredatadir
	$(MAKE) DEST='puredatadir/' ARCH='puredata.cpp' LIB='' -f Makefile.pdcompile

alsagtk :
	install -d alsagtkdir
	$(MAKE) DEST='alsagtkdir/' ARCH='alsa-gtk.cpp' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' -f Makefile.compile

ialsagtk :
	install -d ialsagtkdir
	$(MAKE) DEST='ialsagtkdir/' ARCH='alsa-gtk.cpp' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

ialsavec :
	install -d ialsavecdir
	$(MAKE) DEST='ialsavecdir/' ARCH='alsa-gtk.cpp' VEC='-vec -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

ialsaomp :
	install -d ialsaompdir
	$(MAKE) DEST='ialsaompdir/' ARCH='alsa-gtk.cpp' VEC='-omp -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS='-openmp '$(MYICCFLAGS) -f Makefile.compile

jackgtk :
	install -d jackgtkdir
	$(MAKE) DEST='jackgtkdir/' ARCH='jack-gtk.cpp' LIB='`pkg-config --cflags --libs jack gtk+-2.0`' -f Makefile.compile

msjackgtk :
	install -d msjackgtkdir
	$(MAKE) DEST='msjackgtkdir/' ARCH='ms-jack-gtk.cpp' LIB='-lMidiShare `pkg-config --cflags --libs jack gtk+-2.0`' -f Makefile.compile

jackqt :
	install -d jackqtdir
	$(MAKE) DEST='jackqtdir/' ARCH='jack-qt.cpp' LIB='-ljack' -f Makefile.qtcompile

paqt :
	install -d paqtdir
	$(MAKE) DEST='paqtdir/' ARCH='pa-qt.cpp' LIB='-lportaudio' -f Makefile.qtcompile

caqt :
	install -d caqtdir
	$(MAKE) DEST='caqtdir/' ARCH='ca-qt.cpp' LIB='-framework CoreAudio -framework AudioUnit -framework CoreServices' -f Makefile.qtcompile

alsaqt :
	install -d alsaqtdir
	$(MAKE) DEST='alsaqtdir/' ARCH='alsa-qt.cpp' LIB='-lpthread -lasound' -f Makefile.qtcompile

ladspa :
	install -d ladspadir
	$(MAKE) DEST='ladspadir/' ARCH='ladspa.cpp' LIB='-fPIC -bundle' EXT='.so' -f Makefile.ladspacompile

csound :
	install -d csounddir
	$(MAKE) DEST='csounddir/' -f Makefile.csound

csounddouble :
	install -d csounddoubledir
	$(MAKE) DEST='csounddoubledir/' VEC='-double' -f Makefile.csound
	
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

w32vstdir :
	mkdir w32vstdir

w32vst : w32vstdir
	$(MAKE) DEST='w32vstdir/' ARCH='vst2p4.cpp' LIB='' -f Makefile.w32vstcompile

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
	$(MAKE) DEST='ivecbenchdir/' ARCH='parbench.cpp' VEC='-vec -vs $(VSIZE)' LIB='' CXX='icc' CXXFLAGS='-O3 -xT -ftz -fno-alias -fp-model fast=2' -f Makefile.compile

ivecjack :
	install -d ivecjackdir
	$(MAKE) DEST='ivecjackdir/' ARCH='jack-gtk.cpp' VEC='-vec -vs $(VSIZE)' LIB='`pkg-config --cflags --libs jack gtk+-2.0`' CXX='icc' CXXFLAGS='-O3 -xT -ftz -fno-alias -fp-model fast=2' -f Makefile.compile

iparbench :
	install -d iparbenchdir
	$(MAKE) DEST='iparbenchdir/' ARCH='parbench.cpp' VEC='-vec -vs $(VSIZE) -omp' LIB='' CXX='icc' CXXFLAGS='-O3 -openmp -xT -ftz -fno-alias -fp-model fast=2' -f Makefile.compile

gparbench :
	install -d gparbenchdir
	$(MAKE) DEST='gparbenchdir/' ARCH='parbench.cpp' VEC='-vec -vs $(VSIZE) -omp' LIB='' CXX='g++' CXXFLAGS='-O3 -march=native -mfpmath=sse -msse -msse2 -msse3 -ffast-math' -f Makefile.compile

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
			BUILD_DIR=supercolliderdir \
			$(SCONS_OPTIONS)

jackconsole :
	install -d jackconsoledir
	$(MAKE) DEST='jackconsoledir/' ARCH='jack-console.cpp' LIB='`pkg-config --cflags --libs jack `' -f Makefile.compile

mathdoc :
	$(MAKE) -f Makefile.mathdoc

help:
	@echo "make alsagtk       : compile examples as ALSA applications with a GTK Graphical User Interface"
	@echo "make alsaqt        : compile examples as ALSA applications with a QT4 Graphical User Interface"
	@echo "make sndfile       : compile examples as sound file processors with a Command line User Interface"
	@echo "make jackconsole   : compile examples as JACK applications with a Command line User Interface"
	@echo "make jackgtk       : compile examples as JACK applications with a GTK Graphical User Interface"
	@echo "make jackqt        : compile examples as JACK applications with a QT4 Graphical User Interface"
	@echo "make jackwx        : compile examples as JACK applications with a wxWindows Graphical User Interface"
	@echo "make ossgtk        : compile examples as OSS applications with a GTK Graphical User Interface"
	@echo "make osswx         : compile examples as OSS applications with a wxWindows Graphical User Interface"
	@echo "make pagtk         : compile examples as PortAudio applications with a GTK Graphical User Interface"
	@echo "make paqt          : compile examples as PortAudio applications with a QT4 Graphical User Interface"
	@echo "make pawx          : compile examples as PortAudio applications with a wxWindows Graphical User Interface"
	@echo "make caqt          : compile examples as CoreAudio applications with a QT4 Graphical User Interface"
	@echo "--------------------------------------------"
	@echo "make ladspa        : compile examples as LADSPA plugins"
	@echo "make csound        : compile examples as CSOUND opcodes"
	@echo "make csounddouble  : compile examples as double precision CSOUND opcodes"
	@echo "make maxmsp        : compile examples as Max/MSP externals"
	@echo "make vst           : compile examples as native VST plugins"
	@echo "make w32vst        : crosscompile examples as windows VST plugins"
	@echo "make supercollider : compile examples as Supercollider plugins"
	@echo "make puredata      : compile examples as Puredata externals"
	@echo "make q             : compile examples as Q plugins"
	@echo "--------------------------------------------"
	@echo "make svg           : generate the examples block-diagrams in SVG format "
	@echo "make mathdoc       : generate the examples math documentation in TEX and PDF formats "
	@echo "make bench         : compile examples as command line benchmarks "
	@echo "make plot          : compile examples as command line programs that plot samples with matlab "
	@echo "--------------------------------------------"
	@echo "make clean         : remove all object files"

clean :
	rm -rf *dir
	$(MAKE) -f Makefile.mathdoc clean
