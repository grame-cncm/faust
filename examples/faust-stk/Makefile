# Directory containing Faust .lib and .cpp architecture files:
ck1 := /opt/local/lib/faust/music.lib
ck2 := /usr/local/lib/faust/music.lib
ck3 := $(FAUST_LIB_PATH)/faust/music.lib
LIB := $(if $(wildcard $(ck1)),/opt/local/lib,"")
LIB := $(if $(wildcard $(ck2)),/usr/local/lib,$(LIB))
LIB := $(if $(wildcard $(ck3)),$(FAUST_LIB_PATH),$(LIB))

ifeq ($(OSC),1)
 OSCCTRL := "-DOSCCTRL -I$(LIB)/faust/osclib"
 QTDEFS  := "DEFINES += OSCCTRL"
 OSCLIB  := -L$(LIB)/faust/osclib -lOSCFaust -loscpack
endif

MYICCFLAGS := '-O3 -xT -ftz -fno-alias -fp-model fast=2 $(OSCCTRL)' 

ifeq ($(system), Darwin)
MYGCCFLAGS := '-O3 -march=native -mfpmath=sse -msse -msse2 -msse3 -ffast-math $(OSCCTRL)'
else
MYGCCFLAGS := '-O3 -mfpmath=sse -msse -msse2 -msse3 -ffast-math $(OSCCTRL)'
endif

VSIZE := 256

SC_SOURCE_DIR = ../../supercollider

ifdef POLY
  PDPOLY=$(POLY)
else
  PDPOLY=2
endif

ifdef RADIO
  PDRADIO=-r $(RADIO)
endif

MYF2PDFLAGS='-s -n $(PDPOLY) $(PDRADIO)'

all puredata:
	install -d puredatadir
	$(MAKE) DEST='puredatadir/' ARCH='puredata.cpp' LIB='-L$(LIB)' F2PDFLAGS=$(MYF2PDFLAGS) CXXFLAGS=$(MYGCCFLAGS) -f Makefile.pdcompile

pdpoly2 :
	install -d puredatadir
	$(MAKE) DEST='puredatadir/' ARCH='puredata.cpp' LIB='-L$(LIB)' F2PDFLAGS='-n 2 -s' -f Makefile.pdcompile

pdpoly4 :
	install -d puredatadir
	$(MAKE) DEST='puredatadir/' ARCH='puredata.cpp' LIB='-L$(LIB)' F2PDFLAGS='-n 4 -s' -f Makefile.pdcompile

pdpoly6 :
	install -d puredatadir
	$(MAKE) DEST='puredatadir/' ARCH='puredata.cpp' LIB='-L$(LIB)' F2PDFLAGS='-n 6 -s' -f Makefile.pdcompile

pdpoly8 :
	install -d puredatadir
	$(MAKE) DEST='puredatadir/' ARCH='puredata.cpp' LIB='-L$(LIB)' F2PDFLAGS='-n 8 -s' -f Makefile.pdcompile

test: ijackgtk ijackvec ijackomp gjackgtk gjackvec gjackomp

ijackgtk :
	install -d ijackgtkdir
	$(MAKE) DEST='ijackgtkdir/' ARCH='jack-gtk.cpp' LIB='-L$(LIB) `pkg-config --cflags --libs jack gtk+-2.0` -I/usr/local/include' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

ijackvec :
	install -d ijackvecdir
	$(MAKE) DEST='ijackvecdir/' ARCH='jack-gtk.cpp' VEC='-vec -lv 1 -vs $(VSIZE)' LIB='-L$(LIB) `pkg-config --cflags --libs jack gtk+-2.0` -I/usr/local/include' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

ijackomp :
	install -d ijackompdir
	$(MAKE) DEST='ijackompdir/' ARCH='jack-gtk.cpp' VEC='-vs $(VSIZE) -omp' LIB='-L$(LIB) `pkg-config --cflags --libs jack gtk+-2.0` -I/usr/local/include' CXX='icc' CXXFLAGS='-openmp '$(MYICCFLAGS) -f Makefile.compile

ijacksch :
	install -d ijackschdir
	$(MAKE) DEST='ijackschdir/' ARCH='jack-gtk.cpp' VEC='-sch -vs $(VSIZE)' LIB='-L$(LIB) `pkg-config --cflags --libs jack gtk+-2.0` -I/usr/local/include' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

gjackgtk :
	install -d gjackgtkdir
	$(MAKE) DEST='gjackgtkdir/' ARCH='jack-gtk.cpp' LIB='-L$(LIB) `pkg-config --cflags --libs jack gtk+-2.0` -I/usr/local/include' CXX='g++' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

gjackvec :
	install -d gjackvecdir
	$(MAKE) DEST='gjackvecdir/' ARCH='jack-gtk.cpp' VEC='-vec -lv 1 -vs $(VSIZE)' LIB='-L$(LIB) `pkg-config --cflags --libs jack gtk+-2.0` -I/usr/local/include' CXX='g++' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.compile

gjackomp :
	install -d gjackompdir
	$(MAKE) DEST='gjackompdir/' ARCH='jack-gtk.cpp' VEC='-vec -vs $(VSIZE) -omp' LIB='-L$(LIB) `pkg-config --cflags --libs jack gtk+-2.0` -I/usr/local/include' CXX='g++' CXXFLAGS='-fopenmp '$(MYGCCFLAGS) -f Makefile.compile

svg:
	$(MAKE) -f Makefile.svgcompile

alsagtk :
	install -d alsagtkdir
	$(MAKE) DEST='alsagtkdir/' ARCH='alsa-gtk.cpp' LIB='-I$(LIB)/faust/ -lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0` $(OSCLIB)'  CXXFLAGS=$(OSCCTRL) -f Makefile.compile

ialsagtk :
	install -d ialsagtkdir
	$(MAKE) DEST='ialsagtkdir/' ARCH='alsa-gtk.cpp' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

ialsavec :
	install -d ialsavecdir
	$(MAKE) DEST='ialsavecdir/' ARCH='alsa-gtk.cpp' VEC='-vec -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

ialsaomp :
	install -d ialsaompdir
	$(MAKE) DEST='ialsaompdir/' ARCH='alsa-gtk.cpp' VEC='-omp -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS='-openmp '$(MYICCFLAGS) -f Makefile.compile

ialsasch :
	install -d ialsaschdir
	$(MAKE) DEST='ialsaschdir/' ARCH='alsa-gtk.cpp' VEC='-sch -vs $(VSIZE)' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' CXX='icc' CXXFLAGS=$(MYICCFLAGS) -f Makefile.compile

jackgtk :
	install -d jackgtkdir
	$(MAKE) DEST='jackgtkdir/' ARCH='jack-gtk.cpp' LIB='-I$(LIB)/faust/ `pkg-config --cflags --libs jack gtk+-2.0` $(OSCLIB)' CXXFLAGS=$(OSCCTRL) -f Makefile.compile

msjackgtk :
	install -d msjackgtkdir
	$(MAKE) DEST='msjackgtkdir/' ARCH='ms-jack-gtk.cpp' LIB='-lMidiShare `pkg-config --cflags --libs jack gtk+-2.0`' -f Makefile.compile

jackqt :
	install -d jackqtdir
	$(MAKE) DEST='jackqtdir/' ARCH='jack-qt.cpp' LIB='-ljack $(OSCLIB)' DEFS=$(QTDEFS) CXXFLAGS=$(MYGCCFLAGS) -f Makefile.qtcompile

jackqtsch :
	install -d jackqtschdir
	$(MAKE) DEST='jackqtschdir/' ARCH='jack-qt.cpp' VEC='-sch -vs $(VSIZE)' LIB='-ljack' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.qtcompile

netjackqt :
	install -d netjackqtdir
	$(MAKE) DEST='netjackqtdir/' ARCH='netjack-qt.cpp' LIB='-ljacknet $(OSCLIB)' DEFS=$(QTDEFS) CXXFLAGS=$(MYGCCFLAGS) -f Makefile.qtcompile

jackwt :
	install -d jackwtdir
	$(MAKE) DEST='jackwtdir/' ARCH='jack-wt.cpp' LIB='-I$(LIB)/faust/ -ljack -lwt -lwthttp -lboost_signals-mt $(OSCLIB)' DEFS=$(QTDEFS) -f Makefile.compile

paqt :
	install -d paqtdir
	$(MAKE) DEST='paqtdir/' ARCH='pa-qt.cpp' LIB='-lportaudio $(OSCLIB)'  DEFS=$(QTDEFS) -f Makefile.qtcompile

caqt :
	install -d caqtdir
	$(MAKE) DEST='caqtdir/' ARCH='ca-qt.cpp' LIB='-framework CoreAudio -framework AudioUnit -framework CoreServices $(OSCLIB)' CXXFLAGS=$(MYGCCFLAGS)  DEFS=$(QTDEFS)  -f Makefile.qtcompile

oscioqt :  OSCLIB = -L$(LIB)/faust/osclib -lOSCFaust -loscpack
oscioqt :
	install -d oscioqtdir
	$(MAKE) DEST='oscioqtdir/' ARCH='oscio-qt.cpp' LIB='-ljack $(OSCLIB)' DEFS=$(QTDEFS) -f Makefile.qtcompile

osciogtk :  OSCLIB = -L$(LIB)/faust/osclib -lOSCFaust -loscpack
osciogtk :
	install -d osciogtkdir
	$(MAKE) DEST='osciogtkdir/' ARCH='oscio-gtk.cpp' LIB='-I$(LIB)/faust/ `pkg-config --cflags --libs jack gtk+-2.0` $(OSCLIB)' CXXFLAGS=-I$(LIB)/faust/osclib -f Makefile.compile

alsaqt :
	install -d alsaqtdir
	$(MAKE) DEST='alsaqtdir/' ARCH='alsa-qt.cpp' LIB='-lpthread -lasound $(OSCLIB)' DEFS=$(QTDEFS) -f Makefile.qtcompile

ladspa :
	install -d ladspadir
	$(MAKE) DEST='ladspadir/' ARCH='ladspa.cpp' LIB='-I$(LIB)/faust/' EXT='.so' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.ladspacompile

ladspasch :
	install -d ladspaschdir
	$(MAKE) DEST='ladspaschdir/' ARCH='ladspa.cpp' VEC='-sch -vs $(VSIZE)' LIB='-I$(LIB)/faust/' EXT='.so' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.ladspacompile

dssi :
	install -d dssidir
	$(MAKE) DEST='dssidir/' ARCH='dssi.cpp' LIB='-I$(LIB)/faust/' EXT='.so' CXXFLAGS=$(MYGCCFLAGS) -f Makefile.dssicompile

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
	$(MAKE) DEST='pagtkdir/' ARCH='pa-gtk.cpp' LIB='-I$(LIB)/faust/ -lpthread  -lportaudio `pkg-config gtk+-2.0  --cflags --libs` $(OSCLIB)' CXXFLAGS=$(OSCCTRL) -f Makefile.compile

pawx :
	install -d pawxdir
	$(MAKE) DEST='pawxdir/' ARCH='pa-wx.cpp' LIB='-lpthread  -lportaudio `wx-config --cflags --libs`' -f Makefile.compile

module :
	install -d moduledir
	$(MAKE) DEST='moduledir/' ARCH='module.cpp' LIB='-fPIC -shared' EXT='.so' -f Makefile.compile

bundle :
	install -d bundledir
	$(MAKE) DEST='bundledir/' ARCH='module.cpp' LIB='-I$(LIB)/faust/ -fPIC -bundle' EXT='.so' -f Makefile.compile

maxmsp msp :
	install -d mspdir
	$(MAKE) DEST='mspdir/' ARCH='max-msp.cpp' LIB='' -f Makefile.mspcompile

w32vstdir :
	mkdir w32vstdir

w32vst : w32vstdir
	$(MAKE) DEST='w32vstdir/' ARCH='vst2p4.cpp' LIB='' -f Makefile.w32vstcompile

vst :
	install -d vstdir
	$(MAKE) DEST='vstdir/' ARCH='vst.cpp' LIB='' -f Makefile.vstcompile

iphone :
	install -d iphonedir
	$(MAKE) DEST='iphonedir/' ARCH='iphone-cocoa.cpp' LIB='' -f Makefile.iphonecompile

iphonenet :
	install -d iphonenetdir
	$(MAKE) DEST='iphonenetdir/' ARCH='iphone-cocoa-net.cpp' LIB='' -f Makefile.iphonenetcompile

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
	$(MAKE) DEST='sndfiledir/' ARCH='sndfile.cpp' LIB='-I$(LIB)/faust/ -lsndfile'  -f Makefile.compile
CXXFLAGS=$(OSCCTRL)
plot :
	install -d plotdir
	$(MAKE) DEST='plotdir/' ARCH='plot.cpp' LIB='' -f Makefile.compile

matlabplot :
	install -d matlabplotdir
	$(MAKE) DEST='matlabplotdir/' ARCH='matlabplot.cpp' LIB='' -f Makefile.compile

q :
	install -d qdir
	$(MAKE) DEST='qdir/' ARCH='q.cpp' LIB='' -f Makefile.qcompile

supercollider sc:
	install -d supercolliderdir
	$(MAKE) DEST='supercolliderdir/' -f Makefile.sccompile

jackconsole :
	install -d jackconsoledir
	$(MAKE) DEST='jackconsoledir/' ARCH='jack-console.cpp' VEC='-vec -vs $(VSIZE)' LIB='-I$(LIB)/faust/ `pkg-config --cflags --libs jack ` $(OSCLIB)' CXXFLAGS=$(OSCCTRL) -f Makefile.compile

mathdoc :
	$(MAKE) -f Makefile.mathdoc

help:
	@echo "make alsagtk     [OSC=1] : compile examples as ALSA applications with a GTK Graphical User Interface"
	@echo "make alsaqt      [OSC=1] : compile examples as ALSA applications with a QT4 Graphical User Interface"
	@echo "make sndfile             : compile examples as sound file processors with a Command line User Interface"
	@echo "make jackconsole [OSC=1] : compile examples as JACK applications with a Command line User Interface"
	@echo "make jackgtk     [OSC=1] : compile examples as JACK applications with a GTK Graphical User Interface"
	@echo "make jackqt      [OSC=1] : compile examples as JACK applications with a QT4 Graphical User Interface"
	@echo "make jackwx              : compile examples as JACK applications with a wxWindows Graphical User Interface"
	@echo "make ossgtk              : compile examples as OSS applications with a GTK Graphical User Interface"
	@echo "make osswx               : compile examples as OSS applications with a wxWindows Graphical User Interface"
	@echo "make pagtk       [OSC=1] : compile examples as PortAudio applications with a GTK Graphical User Interface"
	@echo "make paqt        [OSC=1] : compile examples as PortAudio applications with a QT4 Graphical User Interface"
	@echo "make pawx                : compile examples as PortAudio applications with a wxWindows Graphical User Interface"
	@echo "make caqt        [OSC=1] : compile examples as CoreAudio applications with a QT4 Graphical User Interface"
	@echo "make oscioqt             : compile examples as OSC driven applications with a QT4 Graphical User Interface"
	@echo "--------------------------------------------"
	@echo "make ladspa        : compile examples as LADSPA plugins"
	@echo "make dssi          : compile examples as DSSI plugins"
	@echo "make csound        : compile examples as CSOUND opcodes"
	@echo "make csounddouble  : compile examples as double precision CSOUND opcodes"
	@echo "make maxmsp        : compile examples as Max/MSP externals"
	@echo "make vst           : compile examples as native VST plugins"
	@echo "make w32vst        : crosscompile examples as windows VST plugins"
	@echo "make iphone        : compile examples for Apple iPhone/iPod"
	@echo "make supercollider : compile examples as Supercollider plugins"
	@echo "make puredata      : compile examples as Puredata externals"
	@echo "make q             : compile examples as Q plugins"
	@echo "--------------------------------------------"
	@echo "make svg           : generate the examples block-diagrams in SVG format "
	@echo "make mathdoc       : generate the examples math documentation in TEX and PDF formats "
	@echo "make bench         : compile examples as command line benchmarks "
	@echo "make plot          : compile examples as command line programs that print samples for plotting  with, e.g., gnuplot"
	@echo "make matlabplot    : compile examples as command line programs that print samples in matlab input format"
	@echo "--------------------------------------------"
	@echo "make clean         : remove all object files"

clean :
	rm -rf *dir
	rm -rf *-svg
	$(MAKE) -f Makefile.mathdoc clean
