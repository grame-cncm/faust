#!/bin/bash
# verdict.sh <faust> <program> [options...]
#
# Compiles the program and prints its verdict : "accepted" (exit status 0), "refused"
# (a refusal by the certification, recognised by its message), or "failed <first error
# line>" for anything else -- a syntax error, an unknown symbol, a missing library, a
# signal or an assertion of the compiler. A failure is never an expected refusal.
set -u
F=${1:?usage: verdict.sh <faust> <program> [options...]}; P=${2:?usage: verdict.sh <faust> <program> [options...]}; shift 2
d=$(mktemp -d); trap 'rm -rf "$d"' EXIT
"$F" "$@" "$P" -o "$d/out" > /dev/null 2> "$d/err"; rc=$?
if [ $rc -eq 0 ]; then echo accepted; exit 0; fi
CERT="ERROR : (can't compute the min and max values of|possible negative values of|(highest|lowest) of a signal that may be invalid|this program is certified for only|out of range soundfile part number|invalid delay parameter range|too big delay value|an integer remainder may stop the execution|a signal has no valid value)"
if [ $rc -lt 128 ] && grep -qE "$CERT" "$d/err" && ! grep -q "ASSERT" "$d/err"; then echo refused; exit 0; fi
echo "failed (exit $rc) $(head -1 "$d/err")"
