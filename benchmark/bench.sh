#!/bin/bash

echo "benchmark" > results.txt
for d in *dir; do
	for f in $d/*; do
		if [ -x $f ]; then
			$f -b 2048 -p 3 -d hw:0 >> results.txt
		fi
	done
done
