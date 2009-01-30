#!/bin/bash

cat benchmark > results.txt
for d in *dir; do
	for f in $d/*; do
		if [ -x $f ]; then
			$f -b 2048 -p 2 -d hw:1 >> results.txt
		fi
	done
done
