#!/bin/bash
# Run the synthetic tests whose name matches a pattern, each as one entry point
# of synthetic_tests.dsp (faust -pn <name>), under the cpp and ocpp backends of
# one faust binary, and judge the two outputs at 17 digits ; with REF set to a
# second faust binary (master-dev, a milestone), its cpp output judges both.
#
#   usage : ./check.sh [name-regex] [extra faust options...]
#   env   : FAUST (default ../../build/bin/faust)  REF (optional reference faust)
#           N frames (48000)  BLOCK (64)  TOL relative-to-scale tolerance (1e-12)
#           JOBS parallel tests (6)  OUT results directory, outside the source tree by default
#           (~/.cache/faust-synthetic/check : generated bodies in the tree get indexed by the editor)
#   e.g.  ./check.sh 'r[1-3][1-3]'          ./check.sh 'd..' -ss 8        REF=~/faust-refbins/faust-X ./check.sh
set -u
cd "$(dirname "$0")"
PATTERN=${1:-'[a-z][0-9][0-9]'}; shift || true
FAUST=${FAUST:-../../build/bin/faust}; REF=${REF:-}; N=${N:-48000}; BLOCK=${BLOCK:-64}; TOL=${TOL:-1e-12}; JOBS=${JOBS:-6}; OUT=${OUT:-${XDG_CACHE_HOME:-$HOME/.cache}/faust-synthetic/check}
ARCH=$HOME/Documents/Install/faust/architecture; [ -d ../../architecture ] && ARCH=$(cd ../../architecture && pwd)
CXX=${CXX:-c++}; CXXFLAGS=${CXXFLAGS:--O2 -std=c++17}
mkdir -p "$OUT"; RES="$OUT/results.tsv"; : > "$RES"
NAMES=$(grep -o "^$PATTERN" synthetic_tests.dsp | grep -o '^[a-z][0-9][0-9]' | sort -u)
[ -n "$NAMES" ] || { echo "no test matches '$PATTERN'"; exit 1; }
echo "faust  : $FAUST  ($($FAUST --version 2>&1 | head -1))"; [ -n "$REF" ] && echo "ref    : $REF  ($($REF --version 2>&1 | head -1))"
echo "judge  : $CXX $CXXFLAGS -DFAUSTFLOAT=double ; $N frames, blocks of $BLOCK, tolerance $TOL of the scale"
one() {
  name=$1; shift; W="$OUT/$name"; mkdir -p "$W"
  for leg in cpp ocpp ${REF:+ref}; do
    bin=$FAUST; lang=$leg; [ "$leg" = ref ] && { bin=$REF; lang=cpp; }
    if ! "$bin" -lang $lang -double -t 0 "$@" -a print_arch.cpp -pn "$name" synthetic_tests.dsp -o "$W/$leg.cpp" 2>"$W/$leg.err"; then
      printf '%s\tFAUSTFAIL-%s\t%s\n' "$name" "$leg" "$(head -1 "$W/$leg.err" | cut -c1-100)"; return; fi
    if ! $CXX $CXXFLAGS -DFAUSTFLOAT=double -I "$ARCH" "$W/$leg.cpp" -o "$W/$leg" 2>"$W/$leg.cxx"; then
      printf '%s\tCXXFAIL-%s\t%s\n' "$name" "$leg" "$(grep -m1 'error:' "$W/$leg.cxx" | sed 's/.*error: //' | cut -c1-100)"; return; fi
    if ! "$W/$leg" "$N" 48000 "$BLOCK" > "$W/$leg.out" 2>/dev/null; then printf '%s\tRUNFAIL-%s\trc=%s\n' "$name" "$leg" "$?"; return; fi
  done
  python3 - "$W" "$TOL" ${REF:+ref} <<'PY'
import sys, os
W, tol = sys.argv[1], float(sys.argv[2]); legs = ["cpp", "ocpp"] + (["ref"] if len(sys.argv) > 3 else [])
def load(p): return [[float(x) for x in l.split('\t')[1:]] for l in open(p) if '\t' in l]
o = {l: load(os.path.join(W, l + ".out")) for l in legs}
def judge(a, b):
    n = min(len(a), len(b)); scale = max((abs(v) for r in a[:n] for v in r), default=1.0) or 1.0
    first = None; worst = 0.0
    for i in range(n):
        for j in range(min(len(a[i]), len(b[i]))):
            d = abs(a[i][j] - b[i][j]) / scale
            if d > worst: worst = d
            if first is None and a[i][j] != b[i][j]: first = (i, j, a[i][j], b[i][j])
    if worst <= tol: return "OK" + ("" if first is None else " (ulp from %d)" % first[0])
    return "DIFF from %d ch%d : %.17g vs %.17g, worst %.1e" % (first[0], first[1], first[2], first[3], worst)
verdicts = ["cpp/ocpp: " + judge(o["cpp"], o["ocpp"])]
if "ref" in o: verdicts += ["ref/cpp: " + judge(o["ref"], o["cpp"]), "ref/ocpp: " + judge(o["ref"], o["ocpp"])]
status = "OK" if all(v.split(": ")[1].startswith("OK") for v in verdicts) else "DIFF"
print("%s\t%s\t%s" % (os.path.basename(W), status, " ; ".join(verdicts)))
PY
  [ "$KEEP" = 1 ] || rm -f "$W"/*.out "$W/cpp" "$W/ocpp" "$W/ref" 2>/dev/null
}
export -f one 2>/dev/null; KEEP=${KEEP:-0}
i=0
for name in $NAMES; do i=$((i+1)); ( one "$name" "$@" >> "$RES" ) & if [ $((i % JOBS)) -eq 0 ]; then wait; fi; done; wait
sort -o "$RES" "$RES"
echo; awk -F'\t' '{print $2}' "$RES" | sort | uniq -c | awk '{printf "  %s %s\n", $1, $2}'
echo; awk -F'\t' '$2!="OK"' "$RES" | cut -c1-200
echo; echo "results : $RES"
