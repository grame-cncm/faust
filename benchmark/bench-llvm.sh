#!/bin/bash
AOPT="-b 1024 -p 3 -d hw:0"
DST=results-$(date +%y%m%d.%H%M%S)

echo "Faust ALSA Benchmark : " $AOPT > $DST
uname -a >> $DST
date  >> $DST

for d in *.dsp; do
	echo $d 
	./bscalllvm $d >> $DST
done

for d in *.dsp; do
	echo $d 
	./bscalllvm $d -vec -lv 1 -vs 1024 >> $DST
done

for d in *.dsp; do
	echo $d 
	./bscalllvm $d -vec -dfs -vs 1024 >> $DST
done

for d in *.dsp; do
	echo $d 
	./gcoreaudiollvm $d >> $DST
done

for d in *.dsp; do
	echo $d 
	./gcoreaudiollvm $d -sch -vs 1024 >> $DST
done

for d in *.dsp; do
	echo $d 
	./gcoreaudiollvm $d -vec -lv 1 -vs 1024 >> $DST
done

for d in *.dsp; do
	echo $d 
	./gcoreaudiollvm $d -vec -dfs -vs 1024 >> $DST
done


