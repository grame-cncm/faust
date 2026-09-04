#!/bin/bash
# Time the synthetic tests whose name matches a pattern under the cpp and ocpp
# backends of one faust binary : compile everything first (in parallel), then
# measure sequentially, the two backends of a test back to back, best of
# several rounds, nanoseconds per frame. Summary (summary.py, also usable on
# a saved results.tsv) : ratio ocpp/cpp per family, and the efficiency per
# unit of work of the family (m : filters S*P, r : stages + taps, d : delays,
# t : readers, w : multiply-adds B*L).
#
#   usage : ./bench.sh [name-regex] [extra faust options...]
#   env   : FAUST (../../build/bin/faust)  CXX (c++)  BENCHFLAGS (-O3 -ffast-math)
#           N frames (48000)  BLOCK (64)  ROUNDS (7)  JOBS compile jobs (6)  OUT (bench)
set -u
cd "$(dirname "$0")"
PATTERN=${1:-'[a-z][0-9][0-9]'}; shift || true
FAUST=${FAUST:-../../build/bin/faust}; N=${N:-48000}; BLOCK=${BLOCK:-64}; ROUNDS=${ROUNDS:-7}; JOBS=${JOBS:-6}; OUT=${OUT:-bench}
ARCH=$HOME/Documents/Install/faust/architecture; [ -d ../../architecture ] && ARCH=$(cd ../../architecture && pwd)
CXX=${CXX:-c++}; BENCHFLAGS=${BENCHFLAGS:--O3 -ffast-math}
mkdir -p "$OUT"; RES="$OUT/results.tsv"
NAMES=$(grep -o "^$PATTERN" synthetic_tests.dsp | grep -o '^[a-z][0-9][0-9]' | sort -u)
[ -n "$NAMES" ] || { echo "no test matches '$PATTERN'"; exit 1; }
echo "faust : $FAUST ($($FAUST --version 2>&1 | head -1)) ; judge : $CXX $BENCHFLAGS -DFAUSTFLOAT=double ($($CXX --version | head -1))"
echo "frames $N, blocks of $BLOCK, best of $ROUNDS rounds, faust options : $*"
build() { name=$1; shift; W="$OUT/$name"; mkdir -p "$W"
  for lang in cpp ocpp; do
    "$FAUST" -lang $lang -double -t 0 "$@" -a bench_arch.cpp -pn "$name" synthetic_tests.dsp -o "$W/$lang.cpp" 2>"$W/$lang.err" || { echo "FAUSTFAIL" > "$W/$lang.ns"; continue; }
    $CXX $BENCHFLAGS -std=c++17 -DFAUSTFLOAT=double -I "$ARCH" "$W/$lang.cpp" -o "$W/$lang" 2>"$W/$lang.cxx" || echo "CXXFAIL" > "$W/$lang.ns"
  done; }
i=0; for name in $NAMES; do i=$((i+1)); ( build "$name" "$@" ) & if [ $((i % JOBS)) -eq 0 ]; then wait; fi; done; wait
printf 'name\tfamily\tx\ty\tns_cpp\tns_ocpp\tratio_ocpp_cpp\n' > "$RES"
for name in $NAMES; do W="$OUT/$name"
  for lang in cpp ocpp; do [ -x "$W/$lang" ] && "$W/$lang" "$N" 48000 "$BLOCK" "$ROUNDS" > "$W/$lang.ns" 2>/dev/null; done
  c=$(cat "$W/cpp.ns"); o=$(cat "$W/ocpp.ns")
  r=$(python3 -c "import sys
try: print('%.3f' % (float('$o')/float('$c')))
except Exception: print('n/a')")
  printf '%s\t%s\t%s\t%s\t%s\t%s\t%s\n' "$name" "${name:0:1}" "${name:1:1}" "${name:2:1}" "$c" "$o" "$r" >> "$RES"
done
python3 "$(dirname "$0")/summary.py" "$RES"
echo; echo "results : $RES"
