#!/bin/bash
AOPT="-b 1024 -p 3 -d hw:0"
DST=results-$(date +%y%m%d.%H%M%S)

echo "Faust ALSA Benchmark : " $AOPT > $DST
uname -a >> $DST
date  >> $DST
for d in *dir; do
	for f in $d/*; do
		if [ -x $f ]; then
			$f $AOPT >> $DST
		fi
	done
done
