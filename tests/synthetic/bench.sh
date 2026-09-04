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
#           N frames (48000)  BLOCK (64)  ROUNDS (7)  JOBS compile jobs (6)
#           OUT results directory, OUTSIDE the source tree by default (~/.cache/faust-synthetic/bench :
#           the hundreds of generated bodies would otherwise be indexed by the editor's C++ tools)
#           LEGS : the configurations measured, "label:lang:options;..." (default
#           "cpp:cpp:;ocpp:ocpp:") ; e.g. LEGS="ocpp:ocpp:;cpp:cpp:;cppvec:cpp:-vec;fu:ocpp:-ls-fuse -ls-sched model"
#           The first two legs give the ratio column (second over first).
set -u
cd "$(dirname "$0")"
PATTERN=${1:-'[a-z][0-9][0-9]'}; shift || true
FAUST=${FAUST:-../../build/bin/faust}; N=${N:-48000}; BLOCK=${BLOCK:-64}; ROUNDS=${ROUNDS:-7}; JOBS=${JOBS:-6}; OUT=${OUT:-${XDG_CACHE_HOME:-$HOME/.cache}/faust-synthetic/bench}
ARCH=$HOME/Documents/Install/faust/architecture; [ -d ../../architecture ] && ARCH=$(cd ../../architecture && pwd)
CXX=${CXX:-c++}; BENCHFLAGS=${BENCHFLAGS:--O3 -ffast-math}; LEGS=${LEGS:-cpp:cpp:;ocpp:ocpp:}
IFS=';' read -r -a LEGARR <<< "$LEGS"; LABELS=(); for leg in "${LEGARR[@]}"; do LABELS+=("${leg%%:*}"); done
mkdir -p "$OUT"; RES="$OUT/results.tsv"
NAMES=$(grep -o "^$PATTERN" synthetic_tests.dsp | grep -o '^[a-z][0-9][0-9]' | sort -u)
[ -n "$NAMES" ] || { echo "no test matches '$PATTERN'"; exit 1; }
echo "faust : $FAUST ($($FAUST --version 2>&1 | head -1)) ; judge : $CXX $BENCHFLAGS -DFAUSTFLOAT=double ($($CXX --version | head -1))"
echo "frames $N, blocks of $BLOCK, best of $ROUNDS rounds, faust options : $*"
build() { name=$1; shift; W="$OUT/$name"; mkdir -p "$W"
  for leg in "${LEGARR[@]}"; do
    label=${leg%%:*}; rest=${leg#*:}; lang=${rest%%:*}; opts=${rest#*:}
    # shellcheck disable=SC2086
    "$FAUST" -lang $lang -double -t 0 $opts "$@" -a bench_arch.cpp -pn "$name" synthetic_tests.dsp -o "$W/$label.cpp" 2>"$W/$label.err" || { echo "FAUSTFAIL" > "$W/$label.ns"; continue; }
    $CXX $BENCHFLAGS -std=c++17 -DFAUSTFLOAT=double -I "$ARCH" "$W/$label.cpp" -o "$W/$label" 2>"$W/$label.cxx" || echo "CXXFAIL" > "$W/$label.ns"
  done; }
i=0; for name in $NAMES; do i=$((i+1)); ( build "$name" "$@" ) & if [ $((i % JOBS)) -eq 0 ]; then wait; fi; done; wait
{ printf 'name\tfamily\tx\ty'; for l in "${LABELS[@]}"; do printf '\tns_%s' "$l"; done; printf '\tratio_%s_%s\n' "${LABELS[1]}" "${LABELS[0]}"; } > "$RES"
for name in $NAMES; do W="$OUT/$name"; line="$name\t${name:0:1}\t${name:1:1}\t${name:2:1}"
  for l in "${LABELS[@]}"; do [ -x "$W/$l" ] && "$W/$l" "$N" 48000 "$BLOCK" "$ROUNDS" > "$W/$l.ns" 2>/dev/null; line="$line\t$(cat "$W/$l.ns")"; done
  a=$(cat "$W/${LABELS[0]}.ns"); b=$(cat "$W/${LABELS[1]}.ns")
  r=$(python3 -c "import sys
try: print('%.3f' % (float('$b')/float('$a')))
except Exception: print('n/a')")
  printf "$line\t%s\n" "$r" >> "$RES"
done
python3 "$(dirname "$0")/summary.py" "$RES"
echo; echo "results : $RES"
