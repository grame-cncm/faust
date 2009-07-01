src := $(wildcard *.dot)
dst := $(src:.dot=.pdf)

all : $(dst)

%.pdf : %.dot
	dot -Tpdf -o $@ $<
	
