DESTDIR ?= 
PREFIX ?= /usr/local

MAKEFILE := Makefile.unix

prefix := $(DESTDIR)$(PREFIX)
dest   := $(prefix)/bin

help:
	@echo This is a makefile to install the Faust tools.
	@echo The only target is 'install'. Install directory is $(dest) by default. 
	@echo Call 'make install dest=/your/install/dir' to install to another location.

install:
	install faust2alsa $(dest)
	install faust2caqt $(dest)
	install faust2csound $(dest)
	install faust2eps $(dest)
	install faust2firefox $(dest)
	install faust2jack $(dest)
	install faust2jackinternal $(dest)
	install faust2jackserver $(dest)
	install faust2jaqt $(dest)
	install faust2mathdoc $(dest)
	install faust2mathviewer $(dest)
	install faust2msp $(dest)
	install faust2octave $(dest)
	install faust2paqt $(dest)
	install faust2pdf $(dest)
	install faust2plot $(dest)
	install faust2png $(dest)
	install faust2puredata $(dest)
	install faust2svg $(dest)
	install faust2graph $(dest)
	install faust2graphviewer $(dest)

