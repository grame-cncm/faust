#!/bin/bash
AOPT=""
DST=results-$(date +%y%m%d.%H%M%S)

if [[ $(uname) == Darwin ]]; then
AOPT="--buffer 1024"
echo "Faust CoreAudio Benchmark : " $AOPT > $DST
else
AOPT="-b 1024 -p 3 -d hw:0"
echo "Faust ALSA Benchmark : " $AOPT > $DST
fi
uname -a >> $DST
date  >> $DST

for d in *dir; do
	for f in $d/*; do
		if [ -x $f ]; then
			$f $AOPT >> $DST
		fi
	done
done
