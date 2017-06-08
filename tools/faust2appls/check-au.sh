#!/usr/bin/env sh
failures=0
for i in $(seq 0 $1); do
	auvaltool -v aufx cabl Gram 1> /dev/null 2> /dev/null
	if [ $? -gt 0 ]; then
		failures=$((failures+1))
	fi
done
echo $failures
