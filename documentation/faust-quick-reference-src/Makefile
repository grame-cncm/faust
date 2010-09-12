cover-faust-quick-reference.pdf : faust-quick-reference.pdf images/cover-faust.pdf
	pdftk images/cover-faust.pdf faust-quick-reference.pdf cat output cover-faust-quick-reference.pdf
	
faust-quick-reference.pdf : faust-quick-reference.tex images/cover-faust.pdf
	pdflatex faust-quick-reference.tex
	rail faust-quick-reference
	pdflatex faust-quick-reference.tex
	
clean :
	rm -f *.out *.toc *.pdf *.aux *.dvi *.rai *.rao *.log *~
	
	
