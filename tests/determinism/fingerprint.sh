#!/bin/bash
# fingerprint.sh <faust> [witnesses]
#
# Generates the witnesses with ONE faust binary and prints one line per
# generation, "md5 name.set", so that two machines can compare their emitted
# code without moving it : build faust on each, run this on each, then
# compare.sh the two files. Portable md5 (md5sum on Linux, md5 on macOS).
set -u; export LC_ALL=C
HERE=$(cd "$(dirname "$0")" && pwd)
F=${1:?usage: fingerprint.sh <faust> [witnesses]}; W=${2:-$HERE/witnesses.txt}
F=$(cd "$(dirname "$F")" && pwd)/$(basename "$F"); W=$(cd "$(dirname "$W")" && pwd)/$(basename "$W")
"$HERE/determinism.sh" "$F" "$F" "$W" > /dev/null 2>&1 || true
cd "$HERE/out/a" || exit 2
if command -v md5sum > /dev/null; then md5sum ./*.cpp | sed 's#  \./#  #'; else md5 -r ./*.cpp | sed 's# \./#  #'; fi | sort -k2
