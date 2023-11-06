DSP := $(shell find . -name "*.dsp")
SVG	:= $(DSP:%.dsp=%.svg)
DOT	:= $(DSP:%.dsp=%.dot)
PDF	:= $(DSP:%.dsp=%.pdf)



all : $(PDF)

%.pdf : %.dot
	dot -Tpdf "$<" -o "$@" 

%.dot : %.dsp
	faust "$<" -svg -o /dev/null  || echo "OK"
	inkscape --export-pdf="$(<:.dsp=-bd.pdf)" "$(<:.dsp=-svg)/process.svg"
	rm -rf "$(<:.dsp=-svg)"


clean :
	rm -f *.dot *.pdf


SVG	:= $(DSP:%.dsp=%.svg)
PDF	:= $(DSP:%.dsp=%.pdf)



all : $(PDF)

%.pdf : %.svg
	inkscape --export-pdf="$@" "$<"
