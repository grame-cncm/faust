#!/bin/bash
# compare.sh <fingerprint-1> <fingerprint-2>
#
# Compares two fingerprint files (fingerprint.sh) : same witness generated on
# two machines, or by two builds. Across machines, the witnesses whose
# constants are folded through the host's libm (pow, tan, sin, cos) may differ
# at the last ulp : they are listed in libm-witnesses.txt and reported apart.
set -u; export LC_ALL=C
HERE=$(cd "$(dirname "$0")" && pwd)
A=${1:?usage: compare.sh <fingerprint-1> <fingerprint-2>}; B=${2:?usage: compare.sh <fingerprint-1> <fingerprint-2>}
same=0; diff=0; libm=0; missing=0; failed=0
grep '^#' "$A" | sed 's/^/  first  /'; grep '^#' "$B" | sed 's/^/  second /'
while read -r m name; do
    case "$m" in \#*) continue;; esac
    mb=$(awk -v n="$name" '$2 == n {print $1}' "$B")
    # a failed generation, on either side, is not an identity
    if [ "$m" = "FAIL" ] || [ "$mb" = "FAIL" ]; then failed=$((failed+1)); echo "  FAIL  $name"; continue; fi
    if [ -z "$mb" ]; then missing=$((missing+1)); continue; fi
    if [ "$m" = "$mb" ]; then same=$((same+1)); continue; fi
    w=${name%%.*}
    if grep -qx "$w" "$HERE/libm-witnesses.txt" 2>/dev/null; then libm=$((libm+1)); echo "  libm  $name   (expected across machines : a constant at the last ulp)"
    else diff=$((diff+1)); echo "  DIFF  $name"; fi
done < "$A"
echo "identical : $same   different : $diff   libm (expected across machines) : $libm   failed : $failed   missing in second : $missing"
[ $diff -gt 0 ] && exit 1
if [ $failed -gt 0 ] || [ $missing -gt 0 ] || [ $same -eq 0 ]; then
    echo "NOT A VERDICT : a generation failed or is missing, or nothing was compared"; exit 2
fi
echo "OK : the emitted code is the same (up to the libm witnesses)"; exit 0
