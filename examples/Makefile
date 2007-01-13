all : jackgtk

puredata :
	install -d puredatadir
	$(MAKE) DEST='puredatadir/' ARCH='puredata.cpp' LIB='' -f Makefile.pdcompile

alsagtk :
	install -d alsagtkdir
	$(MAKE) DEST='alsagtkdir/' ARCH='alsa-gtk.cpp' LIB='-lpthread -lasound  `pkg-config --cflags --libs gtk+-2.0`' -f Makefile.compile

jackgtk :
	install -d jackgtkdir
	$(MAKE) DEST='jackgtkdir/' ARCH='jack-gtk.cpp' LIB='`pkg-config --cflags --libs jack gtk+-2.0`' -f Makefile.compile

jackqt :
	install -d jackqtdir
	$(MAKE) DEST='jackqtdir/' ARCH='jack-qt.cpp' -f Makefile.qtcompile

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

sndfile :
	install -d sndfiledir
	$(MAKE) DEST='sndfiledir/' ARCH='sndfile.cpp' LIB='-lsndfile' -f Makefile.compile

plot :
	install -d plotdir
	$(MAKE) DEST='plotdir/' ARCH='plot.cpp' LIB='' -f Makefile.compile

q :
	install -d qdir
	$(MAKE) DEST='qdir/' ARCH='q.cpp' LIB='' -f Makefile.qcompile

supercollider :
	install -d supercolliderdir
	$(MAKE) DEST='supercolliderdir/' ARCH='../architecture/supercollider.cpp' CXXFLAGS='`pkg-config --cflags libscsynth`' LIB='-fPIC -shared' EXT='.so' -f Makefile.sccompile

jackconsole :
	install -d jackconsoledir
	$(MAKE) DEST='jackconsoledir/' ARCH='jack-console.cpp' LIB='`pkg-config --cflags --libs jack `' -f Makefile.compile


clean :
	rm -rf alsagtkdir jackgtkdir vecalsagtkdir vecjackgtkdir ladspadir jackwxdir ossgtkdir osswxdir pagtkdir pawxdir moduledir bundledir mspdir vstdir benchdir sndfiledir plotdir benchdir supercolliderdir puredatadir qdir plotdir jackconsoledir *-ps *-svg


