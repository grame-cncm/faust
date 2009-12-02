# This Makefile is mostly intended to gather all resulting faust2math pdf files into the single directory "all-pdfs".
# GRAME 2009
# Karim Barkati


DSP = $(wildcard *.dsp)
TEX = $(wildcard *-math/tex/*.tex)
PDF = $(wildcard *-math/pdf/*.pdf)

all : math copy


.PHONY: all clean compile copy install math help


compile :
	$(MAKE) -C ../../compiler Makefile.unix

install :
	sudo $(MAKE) -C ../.. install
	sudo $(MAKE) -C ../../tools/faust2appls install

math :
	faust2math *.dsp

copy :
	mkdir -p all-dsps
	mkdir -p all-texs
	mkdir -p all-pdfs
	cp $(DSP) all-dsps/
	cp $(TEX) all-texs/
	cp $(PDF) all-pdfs/

help :
	@echo "make or make all : compile math documentation of all examples, then copy resulting pdf files into \"all-pdfs\" directory."
	@echo "make clean   : remove \"*-math\" and \"all-*\" directories."
	@echo "make compile : compile the faust compiler."
	@echo "make install : install the faust compiler and faust2appls scripts."
	@echo "make math    : generate math documentation of all examples (with faust2math)."
	@echo "make copy    : copy dsp, pdf, and tex files into \"all-dsps\", \"all-pdfs\", and \"all-texs\" directories."
	@echo "make total   : clean, compile faust, install faust and faust2appls, compile math docs, and copy files."

clean :
	rm -rf *-math
	rm -rf all-*

total : clean compile install math copy