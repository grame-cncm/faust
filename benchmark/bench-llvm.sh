#!/bin/bash
AOPT="-b 1024 -p 3 -d hw:0"
DST=results-$(date +%y%m%d.%H%M%S)

echo "Faust ALSA Benchmark : " $AOPT > $DST
uname -a >> $DST
date  >> $DST
"scalar"  >> $DST
for d in *.dsp; do
	echo $d 
	./gcoreaudiollvm $d >> $DST
done

"sch"  >> $DST
for d in *.dsp; do
	echo $d 
	./gcoreaudiollvm $d -sch -vs 1024 >> $DST
done


"vec1"  >> $DST
for d in *.dsp; do
	echo $d 
	./gcoreaudiollvm $d -vec -lv 1 -vs 1024 >> $DST
done

"vec2"  >> $DST
for d in *.dsp; do
	echo $d 
	./gcoreaudiollvm $d -vec -lv 1 -dfs -vs 1024 >> $DST
done
