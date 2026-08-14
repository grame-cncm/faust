#!/bin/zsh
# FLOAT LEG : the order auto-differential in float.
# Within one backend, changing the emission order does not change the
# arithmetic DAG ; without -ffast-math the float outputs of the default,
# -ss 11 and -ss 12 orders must be BIT-IDENTICAL. Any difference is an
# order-dependent read (the one-sample class). Each program is its own
# oracle : no references to maintain, resonance irrelevant.
# Usage : ./float-leg.sh   (from tests/impulse-tests ; faust in ../../build/bin)
setopt shwordsplit 2>/dev/null
IT=$(cd "$(dirname "$0")" && pwd)
FAUST="$IT/../../build/bin/faust"
W="$IT/ir/float-leg"
mkdir -p "$W"; cd "$W" || exit 1
pass=0; fail=0; skip=0
for f in "$IT"/dsp/*.dsp; do
    p=$(basename "$f" .dsp)
    okgen=1
    for v in def s11 s12; do
        case $v in def) opts="";; s11) opts="-ss 11";; s12) opts="-ss 12";; esac
        "$FAUST" -lang ocpp -I "$IT/dsp" $opts -i -A "$IT/../../architecture" \
            -a "$IT/archs/impulsearch.cpp" "$f" -o "$p-$v.cpp" 2>/dev/null
        [ -s "$p-$v.cpp" ] || okgen=0
    done
    [ $okgen -eq 0 ] && { echo "SKIP_GEN $p"; skip=$((skip+1)); rm -f "$p-"*; continue; }
    for v in def s11 s12; do
        c++ -O3 -I"$IT/../../architecture" -I"$IT/archs" -pthread -std=c++11 \
            "$p-$v.cpp" -o "$p-$v" 2>/dev/null &
    done
    wait
    { [ -x "$p-def" ] && [ -x "$p-s11" ] && [ -x "$p-s12" ]; } || \
        { echo "SKIP_CXX $p"; skip=$((skip+1)); rm -f "$p-"*; continue; }
    for v in def s11 s12; do ./"$p-$v" -n 60000 > "$p-$v.ir" 2>/dev/null; done
    if cmp -s "$p-def.ir" "$p-s11.ir" && cmp -s "$p-def.ir" "$p-s12.ir"; then
        pass=$((pass+1))
    else
        echo "DIFFERE $p"; fail=$((fail+1))
    fi
    rm -f "$p-def" "$p-s11" "$p-s12" "$p-"*.cpp
done
echo "float-leg : $pass OK, $fail DIFFERE, $skip SKIP"
[ $fail -eq 0 ]
