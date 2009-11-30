#!bin/bash
# Karim Barkati
# Juillet 2009

cd ../..
make parser && make && compiler/faust examples/doc-test.dsp
