all : jackgtk 

alsagtk :
	install -d alsagtkdir
	$(MAKE) DEST='alsagtkdir/' ARCH='alsa-gtk.cpp' LIB='-lpthread -lasound  `pkg-config gtk+-2.0 --cflags --libs`' -f Makefile.compile
	
jackgtk :
	install -d jackgtkdir
	$(MAKE) DEST='jackgtkdir/' ARCH='jack-gtk.cpp' LIB='-ljack  `pkg-config gtk+-2.0  --cflags --libs`' -f Makefile.compile
	
vecalsagtk :
	install -d vecalsagtkdir
	$(MAKE) VEC='-vec' DEST='vecalsagtkdir/' ARCH='alsa-gtk.cpp' LIB='-lpthread -lasound  `pkg-config gtk+-2.0 --cflags --libs`' -f Makefile.compile
	
vecjackgtk :
	install -d vecjackgtkdir
	$(MAKE) VEC='-vec' DEST='vecjackgtkdir/' ARCH='jack-gtk.cpp' LIB='-ljack  `pkg-config gtk+-2.0  --cflags --libs`' -f Makefile.compile
	
jackwx :
	install -d jackwxdir
	$(MAKE) DEST='jackwxdir/' ARCH='jack-wx.cpp' LIB='-ljack `wx-config --cflags --libs`' -f Makefile.compile

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

sndfile :
	install -d sndfiledir
	$(MAKE) DEST='sndfiledir/' ARCH='sndfile.cpp' LIB='-lsndfile' -f Makefile.compile

plot :
	install -d plotdir
	$(MAKE) DEST='plotdir/' ARCH='plot.cpp' LIB='' -f Makefile.compile

clean :
	rm -rf alsagtkdir jackgtkdir vecalsagtkdir vecjackgtkdir jackwxdir ossgtkdir osswxdir pagtkdir pawxdir moduledir sndfiledir plotdir
	
