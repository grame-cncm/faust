DESTDIR ?= 
PREFIX ?= /usr/local

MAKEFILE := Makefile.unix

prefix := $(DESTDIR)$(PREFIX)
dest   := $(prefix)/bin

help:
	@echo This is a makefile to install the Faust tools.
	@echo The only target is 'install'. Install directory is $(dest) by default. 
	@echo Call 'make install DESTDIR=/your/install/dir' to install to another location.

install:
	mkdir -p $(dest)
	install faust2alqt $(dest)
	install faust2alsa $(dest)
	install faust2caqt $(dest)
	install faust2csound $(dest)
	install faust2ladspa $(dest)
	install faust2dssi $(dest)
	install faust2eps $(dest)
	install faust2firefox $(dest)
	install faust2jack $(dest)
	install faust2jackinternal $(dest)
	install faust2jackserver $(dest)
	install faust2jackconsole $(dest)
	install faust2jaqt $(dest)
	install faust2mathdoc $(dest)
	install faust2mathviewer $(dest)
	install faust2msp $(dest)
	install faust2max6 $(dest)
	install faust2octave $(dest)
	install faust2paqt $(dest)
	install faust2pdf $(dest)
	install faust2plot $(dest)
	install faust2png $(dest)
	install faust2puredata $(dest)
	install faust2svg $(dest)
	install faust2supercollider $(dest)
	install ../faust2sc-1.0.0/faust2sc $(dest)
	install faust2graph $(dest)
	install faust2graphviewer $(dest)
	install faust2sig $(dest)
	install faust2sigviewer $(dest)
	install faust2netjackqt $(dest)
	install faust2vst $(dest)
	install faust2ios $(dest)
	install faust2lv2 $(dest)
	install faust2lv2synth $(dest)

uninstall:
	rm -f $(dest)/faust2alqt
	rm -f $(dest)/faust2alsa 
	rm -f $(dest)/faust2caqt
	rm -f $(dest)/faust2csound
	rm -f $(dest)/faust2ladspa
	rm -f $(dest)/faust2dssi
	rm -f $(dest)/faust2eps
	rm -f $(dest)/faust2firefox
	rm -f $(dest)/faust2jack
	rm -f $(dest)/faust2jackinternal
	rm -f $(dest)/faust2jackserver
	rm -f $(dest)/faust2jackconsole
	rm -f $(dest)/faust2jaqt
	rm -f $(dest)/faust2mathdoc
	rm -f $(dest)/faust2mathviewer
	rm -f $(dest)/faust2msp
	rm -f $(dest)/faust2max6
	rm -f $(dest)/faust2octave
	rm -f $(dest)/faust2paqt
	rm -f $(dest)/faust2pdf
	rm -f $(dest)/faust2plot
	rm -f $(dest)/faust2png
	rm -f $(dest)/faust2puredata
	rm -f $(dest)/faust2svg
	rm -f $(dest)/faust2supercollider
	rm -f $(dest)/faust2sc
	rm -f $(dest)/faust2graph
	rm -f $(dest)/faust2graphviewer
	rm -f $(dest)/faust2sig
	rm -f $(dest)/faust2sigviewer
	rm -f $(dest)/faust2netjackqt
	rm -f $(dest)/faust2vst
	rm -f $(dest)/faust2ios
	rm -f $(dest)/faust2lv2
	rm -f $(dest)/faust2lv2synth

