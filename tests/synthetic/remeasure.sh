#!/bin/bash
# Re-measure the option set elected for every test (an elections tsv : name,
# winner label, ns, options with -lang) with bench_arch.cpp, best of several
# rounds of at least 100 ms, so that the elected set is compared to the other
# legs with the same instrument and the same judge. Writes a tsv with the
# columns name, winner, ns (re-measured), options -- the --elections input
# of heatmap.py.
#   usage : ./remeasure.sh elections.tsv [out.tsv]
#   env   : FAUST, CXX, BENCHFLAGS, N, BLOCK, ROUNDS, OUT (~/.cache/faust-synthetic/remeasure) as bench.sh
set -u
cd "$(dirname "$0")"
OUT=${OUT:-${XDG_CACHE_HOME:-$HOME/.cache}/faust-synthetic/remeasure}
IN=$1; RES=${2:-$OUT/elections-remeasured.tsv}
FAUST=${FAUST:-../../build/bin/faust}; N=${N:-48000}; BLOCK=${BLOCK:-64}; ROUNDS=${ROUNDS:-7}
ARCH=$(cd ../../architecture && pwd); CXX=${CXX:-c++}; BENCHFLAGS=${BENCHFLAGS:--O3 -ffast-math}
mkdir -p "$OUT" "$(dirname "$RES")"; printf 'name\twinner\tns\toptions\n' > "$RES"
echo "faust : $FAUST ; judge : $CXX $BENCHFLAGS -DFAUSTFLOAT=double ($($CXX --version | head -1)) ; $N frames, blocks of $BLOCK, best of $ROUNDS rounds"
tail -n +2 "$IN" | while IFS=$'\t' read -r name winner ns opts rest; do
  [ -n "$name" ] && [ -n "$opts" ] || continue
  W="$OUT/$name"; mkdir -p "$W"
  # shellcheck disable=SC2086
  if ! "$FAUST" $opts -double -t 0 -a bench_arch.cpp -pn "$name" synthetic_tests.dsp -o "$W/elected.cpp" 2>"$W/elected.err"; then printf '%s\t%s\tFAUSTFAIL\t%s\n' "$name" "$winner" "$opts" >> "$RES"; continue; fi
  if ! $CXX $BENCHFLAGS -std=c++17 -DFAUSTFLOAT=double -I "$ARCH" "$W/elected.cpp" -o "$W/elected" 2>"$W/elected.cxx"; then printf '%s\t%s\tCXXFAIL\t%s\n' "$name" "$winner" "$opts" >> "$RES"; continue; fi
  m=$("$W/elected" "$N" 48000 "$BLOCK" "$ROUNDS" 2>/dev/null)
  printf '%s\t%s\t%s\t%s\n' "$name" "$winner" "$m" "$opts" >> "$RES"
done
echo "results : $RES ($(( $(wc -l < "$RES") - 1 )) tests)"
