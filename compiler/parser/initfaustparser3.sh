#!bin/bash
# Karim Barkati
# Juillet 2009

cd ../..
make parser && make && compiler/faust -doc examples/doc-test2.dsp &&
echo "#################
cat compiler/documentator/doc-test2.tex
" && cat compiler/documentator/doc-test2.tex
