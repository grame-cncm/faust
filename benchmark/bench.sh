#!/bin/bash
AOPT="-b 2048 -p 2 -d hw:1"
DST=results-$(date +%y%m%d.%H%M%S)

echo "Faust ALSA Benchmark : " $AOPT > $DST
uname -a >> $DST
for d in *dir; do
	for f in $d/*; do
		if [ -x $f ]; then
			$f $AOPT >> $DST
		fi
	done
done
