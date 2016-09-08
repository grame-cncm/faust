#!/bin/bash
AOPT="-b 1024 -p 3 -d hw:0"
DST=results-$(date +%y%m%d.%H%M%S)

if [[ $(uname) == Darwin ]]; then
AOPT="--buffer 1024"
echo "Faust CoreAudio LLVM Benchmark : " $AOPT > $DST
else
AOPT="-b 1024 -p 3 -d hw:0"
echo "Faust ALSA LLVM Benchmark : " $AOPT > $DST
fi
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


