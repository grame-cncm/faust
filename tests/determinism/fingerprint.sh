#!/bin/bash
# fingerprint.sh <faust> [witnesses]
#
# Generates the witnesses with ONE faust binary and prints one line per
# generation, "md5 name.set", so that two machines can compare their emitted
# code without moving it : build faust on each, run this on each, then
# compare.sh the two files. Portable md5 (md5sum on Linux, md5 on macOS).
# A generation that failed is printed "FAIL name.set", never as the md5 of its
# failure marker ; the header lines, starting with '#', name the binary and the
# libraries. Exit status 1 when a generation failed, 2 when nothing was generated.
set -u; export LC_ALL=C
HERE=$(cd "$(dirname "$0")" && pwd)
F=${1:?usage: fingerprint.sh <faust> [witnesses]}; W=${2:-$HERE/witnesses.txt}
F=$(cd "$(dirname "$F")" && pwd)/$(basename "$F"); W=$(cd "$(dirname "$W")" && pwd)/$(basename "$W")
log=$("$HERE/determinism.sh" "$F" "$F" "$W" 2>&1)
echo "# faust : $("$F" --version | grep 'Source commit')"
echo "$log" | grep '^libraries : ' | sed 's/^/# /'
if echo "$log" | grep -q 'has no stdfaust.lib'; then echo "$log" | grep 'NOT A VERDICT' >&2; exit 2; fi
cd "$HERE/out/a" || exit 2
n=0; failed=0
for f in ./*.cpp; do
    [ -e "$f" ] || continue
    name=${f#./}
    n=$((n+1))
    if grep -qx 'FAUSTFAIL' "$f"; then failed=$((failed+1)); echo "FAIL  $name"; continue; fi
    if command -v md5sum > /dev/null; then md5sum "$f" | sed 's#  \./#  #'; else md5 -r "$f" | sed 's# \./#  #'; fi
done | sort -k2
n=$(ls ./*.cpp 2>/dev/null | wc -l); failed=$(grep -lx 'FAUSTFAIL' ./*.cpp 2>/dev/null | wc -l)
[ "$n" -eq 0 ] && { echo "fingerprint : nothing was generated" >&2; exit 2; }
[ "$failed" -gt 0 ] && { echo "fingerprint : $failed generation(s) of $n failed (see FAIL lines) : not a fingerprint to compare" >&2; exit 1; }
exit 0
