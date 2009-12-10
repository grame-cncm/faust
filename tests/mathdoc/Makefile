# This Makefile is mostly intended to gather all resulting faust2mathdoc pdf files into the single directory "allmathpdfs".
# GRAME 2009
# Karim Barkati


DSP = $(wildcard *.dsp)
TEX = $(wildcard *-mdoc/tex/*.tex)
PDF = $(wildcard *-mdoc/pdf/*.pdf)

all : mathdoc copy


.PHONY: all clean compile copy install mathdoc help


compile :
	$(MAKE) -C ../../compiler -f Makefile.unix

install :
	sudo $(MAKE) -C ../.. install
	sudo $(MAKE) -C ../../tools/faust2appls install

mathdoc :
	faust2mathdoc *.dsp

copy :
	mkdir -p allmathdsps
	mkdir -p allmathtexs
	mkdir -p allmathpdfs
	cp $(DSP) allmathdsps/
	cp $(TEX) allmathtexs/
	cp $(PDF) allmathpdfs/

help :
	@echo "make or make all : compile math documentation of all examples, then copy resulting pdf files into \"allmathpdfs\" directory."
	@echo "make clean   : remove \"*-mdoc\" and \"allmath*\" directories."
	@echo "make compile : compile the faust compiler."
	@echo "make install : install the faust compiler and faust2appls scripts."
	@echo "make mathdoc    : generate math documentation of all examples (with faust2mathdoc)."
	@echo "make copy    : copy dsp, pdf, and tex files into \"allmathdsps\", \"allmathpdfs\", and \"allmathtexs\" directories."
	@echo "make total   : clean, compile faust, install faust and faust2appls, compile math docs, and copy files."

clean :
	rm -rf *-mdoc
	rm -rf allmath*

total : clean compile install mathdoc copy