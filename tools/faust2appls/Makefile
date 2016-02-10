DESTDIR ?=
PREFIX ?= /usr/local

MAKEFILE := Makefile.unix

prefix := $(DESTDIR)$(PREFIX)
dest   := $(prefix)/bin

help:
	@echo This is a makefile to install the Faust tools.
	@echo The only target is 'install'. Install directory is $(dest) by default.
	@echo Call 'make install DESTDIR=/your/install/dir' to install to another location.

# Check for some common locations of the VST SDK files. This falls back to
# /usr/local/src/vstsdk if none of these are found. In that case, or if make
# picks the wrong location, you can also set the SDK variable explicitly.
sdkpaths = /usr/local/include /usr/local/src /usr/include /usr/src
sdkpat = vst* VST*
SDK = $(firstword $(wildcard $(foreach path,$(sdkpaths),$(addprefix $(path)/,$(sdkpat)))) /usr/src/vstsdk)
# Steinberg's distribution zip has the SDK source files in the
# public.sdk/source/vst2.x subdirectory, while some Linux packages (e.g.,
# steinberg-vst in the Arch User Repositories) keep them directly under $(SDK).
SDKSRC = $(firstword $(patsubst %/,%,$(dir $(wildcard $(addsuffix vstplugmain.cpp,$(SDK)/ $(SDK)/public.sdk/source/vst2.x/)))) $(SDK)/public.sdk/source/vst2.x)

# This sets the proper SDK paths in the faust2faustvst script, detected at
# installation time.
faust2faustvst: faust2faustvst.in
	sed -e 's?@SDK@?$(SDK)?g;s?@SDKSRC@?$(SDKSRC)?g' < $< > $@
	chmod a+x $@

install: faust2faustvst
	mkdir -p $(dest)
	install ../faust2sc-1.0.0/faust2sc $(dest)
	install faust2alqt $(dest)
	install faust2alsa $(dest)
	install faust2alsaconsole $(dest)
	install faust2android $(dest)
	install faust2api $(dest)
	install faust2asmjs $(dest)
	install faust2au $(dest)
	install faust2caqt $(dest)
	install faust2csound $(dest)
	install faust2dssi $(dest)
	install faust2eps $(dest)
	install faust2faustvst $(dest)
	install faust2firefox $(dest)
	install faust2gen $(dest)
	install faust2graph $(dest)
	install faust2graphviewer $(dest)
	install faust2ios $(dest)
	install faust2jack $(dest)
	install faust2jackconsole $(dest)
	install faust2jackinternal $(dest)
	install faust2jackserver $(dest)
	install faust2jaqt $(dest)
	install faust2ladspa $(dest)
	install faust2lv2 $(dest)
	install faust2lv2synth $(dest)
	install faust2mathdoc $(dest)
	install faust2mathviewer $(dest)
	install faust2max6 $(dest)
	install faust2md $(dest)
	install faust2msp $(dest)
	install faust2netjackconsole $(dest)
	install faust2netjackqt $(dest)
	install faust2octave $(dest)
	install faust2owl $(dest)
	install faust2paqt $(dest)
	install faust2pdf $(dest)
	install faust2plot $(dest)
	install faust2png $(dest)
	install faust2puredata $(dest)
	install faust2raqt $(dest)
	install faust2ros $(dest)
	install faust2rosgtk $(dest)
	install faust2rpialsaconsole $(dest)
	install faust2rpinetjackconsole $(dest)
	install faust2sig $(dest)
	install faust2sigviewer $(dest)
	install faust2supercollider $(dest)
	install faust2svg $(dest)
	install faust2vst $(dest)
	install faust2vsti $(dest)
	install faust2w32max6 $(dest)
	install faust2w32msp $(dest)
	install faust2w32puredata $(dest)
	install faust2w32vst $(dest)
	install faust2webaudioasm $(dest)
	install faustoptflags $(dest)
	install faustpath $(dest)
	rm -f faust2faustvst

uninstall:
	rm -f $(dest)/faust2sc
	rm -f $(dest)/faust2alqt
	rm -f $(dest)/faust2alsa
	rm -f $(dest)/faust2alsaconsole
	rm -f $(dest)/faust2android
	rm -f $(dest)/faust2api
	rm -f $(dest)/faust2asmjs
	rm -f $(dest)/faust2au
	rm -f $(dest)/faust2caqt
	rm -f $(dest)/faust2csound
	rm -f $(dest)/faust2dssi
	rm -f $(dest)/faust2eps
	rm -f $(dest)/faust2faustvst
	rm -f $(dest)/faust2firefox
	rm -f $(dest)/faust2gen
	rm -f $(dest)/faust2graph
	rm -f $(dest)/faust2graphviewer
	rm -f $(dest)/faust2ios
	rm -f $(dest)/faust2jack
	rm -f $(dest)/faust2jackconsole
	rm -f $(dest)/faust2jackinternal
	rm -f $(dest)/faust2jackserver
	rm -f $(dest)/faust2jaqt
	rm -f $(dest)/faust2ladspa
	rm -f $(dest)/faust2lv2
	rm -f $(dest)/faust2lv2synth
	rm -f $(dest)/faust2mathdoc
	rm -f $(dest)/faust2mathviewer
	rm -f $(dest)/faust2max6
	rm -f $(dest)/faust2md
	rm -f $(dest)/faust2msp
	rm -f $(dest)/faust2netjackconsole
	rm -f $(dest)/faust2netjackqt
	rm -f $(dest)/faust2octave
	rm -f $(dest)/faust2owl
	rm -f $(dest)/faust2paqt
	rm -f $(dest)/faust2pdf
	rm -f $(dest)/faust2plot
	rm -f $(dest)/faust2png
	rm -f $(dest)/faust2puredata
	rm -f $(dest)/faust2raqt
	rm -f $(dest)/faust2ros
	rm -f $(dest)/faust2rosgtk
	rm -f $(dest)/faust2rpialsaconsole
	rm -f $(dest)/faust2rpinetjackconsole
	rm -f $(dest)/faust2sig
	rm -f $(dest)/faust2sigviewer
	rm -f $(dest)/faust2supercollider
	rm -f $(dest)/faust2svg
	rm -f $(dest)/faust2vst
	rm -f $(dest)/faust2vsti
	rm -f $(dest)/faust2w32max6
	rm -f $(dest)/faust2w32msp
	rm -f $(dest)/faust2w32puredata
	rm -f $(dest)/faust2w32vst
	rm -f $(dest)/faust2webaudioasm
	rm -f $(dest)/faustoptflags
	rm -f $(dest)/faustpath
