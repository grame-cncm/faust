src := $(wildcard *.dot)
dst := $(src:.dot=.pdf)

dsp := $(wildcard *.dsp)
png := $(dsp:.dsp=.png)

all : $(dst) $(png)

%.pdf : %.dot
	dot -Tpdf -o $@ $<

%.png : %.dsp
	faust2png $<
	cp $(<)-png/process.png $@
	
