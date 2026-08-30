#!/usr/bin/env python3
"""faustauto — the complete auto mode of the ocpp backend, in two layers.

Layer 1 (static, free): the program signature (FAUST_SS_SIG) prunes the
53 modes down to 3 or 4 candidates. Two outcomes:
  - safe fusion  (recmii >= 50, or >= 5 real streams)  -> fusion + BOTH ordering regimes
  - uncertain                                          -> fusion + 2 orders + df
The ordering regime follows the recurrence bound: recmii >= 45 -> locality
(R2 hybrid), otherwise bursts (alignment).

Layer 2 (measured): each candidate is compiled then benched for ~0.3 s,
in alternating rounds; the measured winner is emitted. Rugged landscapes
(cap, the vocoder/filterBank twins) proved that no static rule can
replace this measurement.

Usage: faustauto.py file.dsp [-o output.cpp] [--rounds N] [--keep]
"""

import argparse
import os
import re
import subprocess
import sys
import tempfile
import time

FAUST = os.environ.get("FAUSTAUTO_FAUST",
                       os.path.join(os.path.dirname(__file__), "../../build/bin/faust"))
# Layer 2 rules with the SINGLE JUDGE of the map (2026-08-16 decision):
# flashbench arch (blocks of 512, LCG input, min over repetitions), float,
# -O3 -ffast-math -march=native. The former bencharch (1 s block,
# min-stable protocol) diverged from the reference judge by up to x2.7 on
# the very same binary (quantizedChords): elections must be rendered by
# the authoritative judge, not by a cousin.
FAUST_ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
FLASH_ARCH = os.path.join(FAUST_ROOT, "tests", "impulse-tests", "archs", "flashbench.cpp")
ARCH_DIR   = os.path.join(FAUST_ROOT, "architecture")
ARCHS_DIR  = os.path.join(FAUST_ROOT, "tests", "impulse-tests", "archs")
FLASH_ENV  = {"FLASH_REPS": "10", "FLASH_BLOCKS": "100", "FLASH_WARM": "120"}
# The C++ compiler is part of the judge: "clang++" resolved to the
# MacPorts LLVM 22 while the map had been judged with the Apple clang of
# /usr/bin/c++ -- a x2.6 gap on quantizedChords, plus layout-sensitive
# builds. The judge pins the binary, not a name.
CXX = os.environ.get("FAUSTAUTO_CXX", "/usr/bin/c++")
CXXFLAGS = os.environ.get("FAUSTAUTO_CXXFLAGS",
                          "-O3 -ffast-math -march=native -fbracket-depth=1024").split()

# the official nomenclature (MODES.md §7)
CAND = {
    "fu":  ["-ls-fuse", "-ls-sched", "model"],
    # ls: the BARE split, no fusion -- the fine grain. Found missing from
    # the jury on 2026-08-16: on quantizedChords (20 independent table
    # oscillators) fu is 2.1x WORSE than df where ls is 25% BETTER --
    # the fusion oracle under-weighs the shape of loop bodies. ls is the
    # candidate for banks of independent chains.
    "ls":  ["-ls", "-ls-sched", "model"],
    "df":  ["-ss", "0"],
    "al":  ["-ss", "8"],
    "h2":  ["-ss", "9", "-ls-R", "2", "-ls-U", "4"],
    "h32": ["-ss", "9", "-ls-R", "32", "-ls-U", "4"],
    "cs8": ["-ss", "7", "-ls-R", "8", "-ls-U", "4"],
    "t4":  ["-temp", "4"],
    "t4fu": ["-temp", "4", "-ls-fuse", "-ls-sched", "model"],
    "t1fu": ["-temp", "1", "-ls-fuse", "-ls-sched", "model"],
    "fi":  ["-fir", "-iirt"],
    "fib": ["-fir", "-iirt", "-lsum"],
    "fifu":  ["-fir", "-iirt", "-ls-fuse", "-ls-sched", "model"],
    "fibfu": ["-fir", "-iirt", "-lsum", "-ls-fuse", "-ls-sched", "model"],
    # fibmx: fibfu + the matrix form (-mxr). Two effects: dense families
    # escape the -lsum butterfly (DNN x0.50 from that saving alone), and
    # under -ls the rows of recurrent blocks become contiguous
    # table+vector dot products (statespace 9.46 -> 7.76). With no
    # family present it is byte-identical to fibfu -- only invite it
    # when the signature sees nmatrix >= 1.
    "fibmx": ["-fir", "-iirt", "-lsum", "-mxr", "-ls-fuse", "-ls-sched", "model"],
    "lz":  ["-lazyselect"],
    "lzh": ["-lazyselect", "-ss", "9", "-ls-R", "32", "-ls-U", "4"],
    "gq":  ["-gatequiv"],
    "gqlz": ["-gatequiv", "-lazyselect"],
    "lb":  ["-lsum"],
    "sn":  ["-selectn"],
    "gqsn": ["-gatequiv", "-selectn"],
    # cs2: the compositional scheduler (dominator blocks, Pareto beam,
    # 1M budget), as a PAIR of spines since the (R,U) x 2-spine map of
    # 2026-08-13: the default (20,4) was optimal nowhere. cs2 = df spine
    # at (32,4) (greyhole 3.53, pluckedString 6.77); cs2b = bf spine at
    # (32,8) (paradigma 2.76, record x0.51, fdnRev 12.21). Each compiles
    # in 0.4-10 s: the most expensive members of the jury.
    "cs2":  ["-ss", "11", "-ls-R", "32", "-ls-U", "4"],
    "cs2b": ["-ss", "12", "-ls-R", "32", "-ls-U", "8"],
    # rp: ring-read preloading (df + env) -- the loads leave as a burst
    # at the head of the loop body, with a register move at the original
    # slot. Proved by counters on freeverb (stalls -43%), a per-program
    # candidate (zitaRev 1.03: never a default).
    "rp":   ["-ss", "0"],
}

# candidates carried by an environment variable rather than flags
# (the compiler is invoked with this extra environment)
CAND_ENV = {
    "rp": {"FAUST_SS_RINGPRELOAD": "1"},
}


def signature(dsp):
    env = dict(os.environ, FAUST_SS_SIG="1")
    r = subprocess.run([FAUST, "-lang", "ocpp", dsp, "-o", os.devnull],
                       env=env, capture_output=True, text=True)
    m = re.search(r"SS_SIG ([^\n]*)", r.stderr)
    if not m:
        sys.exit(f"faustauto: pas de signature (faust a dit : {r.stderr.strip()[:200]})")
    sig = {k: int(v) for k, v in re.findall(r"(\w+)=(\d+)", m.group(1))}
    # the fourth form: matrix family count. A separate probe (families
    # only exist after revealSum, outside the signature's default world)
    # -- ~0.5 s, which only pays for inviting fibmx where it can differ
    # from fibfu.
    r = subprocess.run([FAUST, "-lang", "ocpp", "-fir", "-iirt", "-lsum", dsp,
                        "-o", os.devnull],
                       env=dict(os.environ, FAUST_MATRIX_CENSUS="1"),
                       capture_output=True, text=True)
    fams = re.findall(r"MATRIX census : \d+ candidats, (\d+) familles", r.stderr)
    sig["nmatrix"] = int(fams[-1]) if fams else 0
    return sig


def candidates(sig, full=False):
    """The pruner: signature -> (zone, candidate list).

    Layer 1 DISTILLED from the V7/V8 campaigns (2026-08-22, 199
    programs, elections stable across both): a universal core plus
    signature-driven zones. Validated by REGRET: the sub-jury contains
    an option within <=1.7% of the true winner over ALL of V8 (geomean
    1.0009), and generalises to V7 (1.0021, one 9% exception). Average
    size 10.2 candidates versus 15.6 for the full jury — the election
    drops from ~45 s to ~25 s. --full restores the full jury (campaign
    mode: it is what builds the maps the distillation comes from —
    never distil from the distillation).
    """
    if full:
        fusion_signal = sig["recmii"] >= 50 or sig["nstreams"] >= 5
        locality = sig["recmii"] >= 45
        order = ["h2", "cs8"] if locality else ["al", "h32"]
        lazy = ["lz", "lzh", "gq", "gqlz", "sn", "gqsn"] if sig.get("nselect", 0) >= 8 else []
        lazy += ["lb"]
        # fibmx only where it exists: with no family it is fibfu byte
        # for byte (the stopwatch would only be splitting noise)
        mx = ["fibmx"] if sig.get("nmatrix", 0) >= 1 else []
        if fusion_signal:
            other = "al" if locality else "h2"
            return "fusion-sûre", ["fu", "ls", order[0], other, "t4fu", "t1fu", "df", "rp", "cs2",
                                   "cs2b", "fi", "fib", "fifu", "fibfu"] + mx + lazy
        return "incertain", ["fu", "ls", order[0], order[1], "df", "rp", "cs2", "cs2b", "t4", "fi",
                             "fib", "fifu", "fibfu"] + mx + lazy
    n, r, st = sig["nodes"], sig["recmii"], sig["nstreams"]
    sel, alu = sig.get("nselect", 0), sig["nalu"]
    # the universal core: df the reference, lb (sum factorisation,
    # a no-op elsewhere), fu the fusion, al the alignment, and the
    # fir-fusion pair (fifu WITHOUT -lsum and fibfu WITH: on the guitar
    # programs -lsum costs, on the Lab ones it pays — they travel
    # together)
    cand = ["df", "lb", "fu", "al", "fifu", "fibfu"]
    if sig.get("nmatrix", 0) >= 1:
        cand += ["fibmx"]        # the matrix form, where families exist
    if n < 200 or alu > 0.9 * n:
        cand += ["fi"]           # small programs or pure ALU (ambisonics)
    if r >= 80:
        cand += ["t1fu", "t4fu"]  # dominant recurrence -> fine staging
    if st >= 20:
        cand += ["t4fu"]
    if r >= 40 or st >= 5:
        cand += ["h2"]           # locality or streams -> R2 hybrid
    else:
        cand += ["h32"]
    if st >= 8:
        cand += ["rp"]           # bursts of ring reads
    if n >= 700 or r >= 80:
        cand += ["cs2"]          # big or recurrent -> df spine
    if n >= 200:
        cand += ["cs2b"]         # the bf spine carries the big ones (violin, vital_rev)
    if sel >= 8:
        cand += ["lz", "gqlz", "t4", "sn", "gqsn"]
    return "distillée", list(dict.fromkeys(cand))


def compile_candidate(dsp, name, workdir):
    cpp = os.path.join(workdir, f"{name}.cpp")
    env = dict(os.environ, **CAND_ENV.get(name, {}))
    r = subprocess.run([FAUST, "-lang", "ocpp", *CAND[name],
                        "-a", FLASH_ARCH, "-A", ARCH_DIR, dsp, "-o", cpp],
                       env=env, capture_output=True, text=True)
    if r.returncode != 0 or not os.path.getsize(cpp):
        return None, None
    binp = os.path.join(workdir, f"{name}-bin")
    r = subprocess.run([CXX, *CXXFLAGS, f"-I{ARCH_DIR}", f"-I{ARCHS_DIR}", cpp, "-o", binp],
                       capture_output=True)
    if r.returncode != 0:
        return cpp, None
    return cpp, binp


FAUST_DIR = os.path.normpath(os.path.join(os.path.dirname(__file__), "../.."))
IMPULSE_ARCH = os.path.join(FAUST_DIR, "tests/impulse-tests/archs/impulsearch.cpp")
# 17-digit harness for the gate: at 6 decimals, a ulp-class onset stays
# invisible for 30k samples then surfaces as a spurious finite
# divergence -- the onset criterion requires full precision
HIPREC_DIR = os.path.join(tempfile.gettempdir(), "faustauto-hiprec")
def _ensure_hiprec():
    os.makedirs(HIPREC_DIR, exist_ok=True)
    dst = os.path.join(HIPREC_DIR, "controlTools.h")
    if not os.path.exists(dst):
        src = open(os.path.join(FAUST_DIR, "tests/impulse-tests/archs/controlTools.h")).read()
        open(dst, "w").write(src.replace("%8.6f", "%.17g"))
    return HIPREC_DIR
NUMRE = re.compile(r"-?\d+\.?\d*(?:[eE][+-]?\d+)?")

# Lock 6 (2026-08-22, the V8 night): periods where fresh subprocesses
# are served on E-cores / slow DVFS steps -- QUANTISED and STABLE
# values (2.98 instead of 1.6 on the canary), hence invisible to any
# dispersion guard. Cause partially proved (background QoS:
# taskpolicy -b reproduces a deterministic 2.46), partially open
# (global regimes with no declared thermal state). Defense: a
# calibrated BINARY canary, launched through the same path as the
# candidates; if it measures slow, we wait instead of counting.
CANARY_DIR = os.path.join(tempfile.gettempdir(), "faustauto-canary")

def _ensure_canary():
    """Build and calibrate the canary (once, cached); returns
    (binary, ref) or (None, None) if it cannot be built."""
    os.makedirs(CANARY_DIR, exist_ok=True)
    b = os.path.join(CANARY_DIR, "canary-bin")
    reff = os.path.join(CANARY_DIR, "canary.ref")
    if os.path.exists(b) and os.path.exists(reff) and not os.environ.get("FAUSTAUTO_RECAL"):
        try:
            return b, float(open(reff).read())
        except ValueError:
            pass
    dsp = os.path.join(FAUST_ROOT, "examples", "analysis", "vumeter.dsp")
    cpp, binp = compile_candidate(dsp, "df", CANARY_DIR)
    if not binp:
        return None, None
    if binp != b:
        os.replace(binp, b)
    for _ in range(10):
        vals = [v for v in (run_once(b) for _ in range(10)) if v]
        if vals and max(vals) / min(vals) < 1.15:
            open(reff, "w").write(f"{min(vals):.6f}")
            return b, min(vals)
        print("faustauto: etalonnage du canari instable, attente 60 s", file=sys.stderr)
        time.sleep(60)
    return None, None

def wait_quiet(max_waits=5):
    """Wait for a stable OS scheduler; past max_waits, proceed while
    flagging the measurements as non-canonical (a tool must not block
    forever)."""
    b, ref = _ensure_canary()
    if b is None:
        return True
    for _ in range(max_waits):
        vals = [v for v in (run_once(b) for _ in range(3)) if v]
        if vals and min(vals) < 1.25 * ref:
            return True
        print(f"faustauto: canari lent ({min(vals):.3f} vs {ref:.3f} etalonne), attente 60 s",
              file=sys.stderr)
        time.sleep(60)
    print("ATTENTION: ordonnanceur instable persistant -- mesures non canoniques", file=sys.stderr)
    return False

def impulse_ir(dsp, flags, env, workdir, tag):
    """-double impulse response (60000 samples); None if unbuildable."""
    cpp = os.path.join(workdir, f"ir-{tag}.cpp")
    r = subprocess.run([FAUST, "-lang", "ocpp", "-double", *flags, "-i", "-A",
                        os.path.join(FAUST_DIR, "architecture"), "-a", IMPULSE_ARCH,
                        dsp, "-o", cpp], env=dict(os.environ, **env), capture_output=True)
    if r.returncode:
        return None
    b = os.path.join(workdir, f"ir-{tag}")
    r = subprocess.run(["/usr/bin/c++", "-O2", "-std=c++17", "-I" + _ensure_hiprec(),
                        "-I" + os.path.join(FAUST_DIR, "architecture"),
                        "-I" + os.path.join(FAUST_DIR, "tests/impulse-tests/archs"),
                        cpp, "-o", b], capture_output=True)
    if r.returncode:
        return None
    r = subprocess.run([b, "-n", "60000"], capture_output=True, text=True)
    return r.stdout if r.returncode == 0 and r.stdout.strip() else None

def ir_equivalent(a, b, onset_tol=1e-11):
    """ONSET criterion (2026-08-18 verdict, the VA ladder family):
    what matters is the FIRST divergence. Ulp-class (< onset_tol
    relative) = legal floating-point reassociation; everything after
    it may diverge freely -- resonant VA filters amplify one ulp up to
    ~2.0 relative within 30k samples (positive Lyapunov exponent) with
    no arithmetic being wrong. A FINITE divergence from the start
    (the dup/gate_compressor case: rel ~1 at sample 0) =
    miscompilation, rejected. Newborn NaN/inf = rejected."""
    if a == b:
        return True
    la, lb = a.splitlines(), b.splitlines()
    if len(la) != len(lb):
        return False
    for x, y in zip(la, lb):
        if x == y:
            continue
        na, nb = NUMRE.findall(x), NUMRE.findall(y)
        if len(na) != len(nb):
            return False
        for u, v in zip(na, nb):
            if 'nan' in u or 'nan' in v or 'inf' in u or 'inf' in v:
                return u == v
            fu, fv = float(u), float(v)
            d = abs(fu - fv)
            if d == 0.0:
                continue
            # first divergence found: is it ulp-class?
            return d <= onset_tol * max(abs(fu), abs(fv), 1e-30)
    return True

def run_once(binp, iters=None):
    r = subprocess.run([binp], env=dict(os.environ, **FLASH_ENV),
                       capture_output=True, text=True)
    m = re.match(r"([0-9.]+)", r.stdout)
    return float(m.group(1)) if m else None


RECIPES = os.path.join(os.path.dirname(os.path.abspath(__file__)), "recipes.tsv")

def book_recipe(dsp):
    """The recipe book (layer 4): an evolved recipe for THIS program,
    injected as candidate 'bk'. Returns (flags, env) or None."""
    base = os.path.basename(dsp)
    try:
        for l in open(RECIPES):
            if l.startswith("#") or not l.strip():
                continue
            c = l.rstrip("\n").split("\t")
            if len(c) >= 4 and c[0] == base:
                flags = c[2].split()
                env   = dict(kv.split("=", 1) for kv in c[3].split() if "=" in kv)
                return flags, env
    except FileNotFoundError:
        pass
    return None

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("dsp")
    ap.add_argument("-o", "--output")
    ap.add_argument("--rounds", type=int, default=2)
    ap.add_argument("--keep", action="store_true", help="garder le dossier de travail")
    ap.add_argument("--full", action="store_true",
                    help="jury complet (mode campagne, ~15-19 candidats)")
    a = ap.parse_args()

    t0 = time.time()
    sig = signature(a.dsp)
    zone, cands = candidates(sig, full=a.full)
    recipe = book_recipe(a.dsp)
    if recipe is not None:
        CAND["bk"] = recipe[0]
        CAND_ENV["bk"] = recipe[1]
        cands = cands + ["bk"]
        print("faustauto: recette du livre injectée (candidat bk)")
    print(f"faustauto: zone {zone} ; candidats {cands}")
    print(f"  signature : nodes={sig['nodes']} recmii={sig['recmii']} "
          f"nstreams={sig['nstreams']} bankable={sig['bankablepct']}% top1={sig['top1']}")

    workdir = tempfile.mkdtemp(prefix="faustauto-")
    built = {}
    for name in cands:
        cpp, binp = compile_candidate(a.dsp, name, workdir)
        if binp:
            built[name] = (cpp, binp)
        else:
            print(f"  {name}: échec de construction, écarté")
    if not built:
        sys.exit("faustauto: aucun candidat construit")

    # flash bench: the judge's uniform protocol (min of 10 repetitions
    # of 100 blocks of 512), alternating rounds. THERMAL PAUSE first:
    # the compile phase (20+ candidates at -O3) heats the machine and
    # used to pollute the first round (co-measurement lesson; lfBoost
    # V4, highShelf/lowCut V5: ls builds worth 2.28 measured at 4.45
    # and losing).
    # power gate : on battery, frequency scaling biases even co-measured
    # ratios (memory-bound and compute-bound codes throttle differently).
    # Refuse to bench rather than record a biased verdict.
    try:
        batt = subprocess.run(["pmset", "-g", "batt"], capture_output=True, text=True).stdout
        if "Battery Power" in batt:
            sys.exit("REFUS : sur batterie (pmset). Brancher le secteur avant de bencher "
                     "(FAUSTAUTO_ALLOW_BATTERY=1 pour outrepasser, resultats non canoniques).")                 if not os.environ.get("FAUSTAUTO_ALLOW_BATTERY") else                 print("ATTENTION : bench sur batterie (FAUSTAUTO_ALLOW_BATTERY) -- resultats non canoniques", file=sys.stderr)
    except FileNotFoundError:
        pass
    wait_quiet()
    time.sleep(6)
    times = {name: [] for name in built}
    for attempt in range(2):
        times = {name: [] for name in built}
        for _ in range(a.rounds):
            for name, (_, binp) in built.items():
                t = run_once(binp)
                if t is not None:
                    times[name].append(t)
        spread = [max(v) / min(v) for v in times.values() if v and min(v) > 0]
        dirty = sum(1 for r in spread if r > 1.6) / max(1, len(spread))
        if dirty <= 0.4:
            break
        print(f"faustauto: tour disperse ({int(dirty*100)}% instables), re-essai", file=sys.stderr)
        wait_quiet()
    # PODIUM RE-RACE: min-of-2 is fragile to spikes, and only the head
    # of the ranking matters. WIDE repechage: every candidate within 2x
    # of the provisional leader gets 4 more alternating rounds — a true
    # winner polluted by a factor of 2 (ls on the filters: worth 2.28,
    # measured 4.45) remains recoverable. Cap of 8 to bound the cost.
    ranked = sorted((n for n in built if times[n]), key=lambda n: min(times[n]))
    lead   = min(times[ranked[0]]) if ranked else 0.0
    podium = [n for n in ranked if min(times[n]) <= 2.0 * lead][:8]
    for _ in range(4):
        for name in podium:
            t = run_once(built[name][1])
            if t is not None:
                times[name].append(t)
    for name in built:
        if times[name]:
            print(f"  {name:<4} {min(times[name]):.4f} ns")
    # CORRECTNESS GATE (dbmeter lesson, the VA ladder family): elections
    # measure speed, never correctness — a wrong-but-fast candidate
    # would win. The winner must reproduce df's impulse response (at the
    # bit, or reassociation < 1e-9 relative); otherwise DISQUALIFIED,
    # next in line. df itself is always accepted.
    ref_ir = impulse_ir(a.dsp, [], {}, workdir, "ref")
    ranked2 = sorted((n for n in built if times[n]), key=lambda n: min(times[n]))
    best, score = None, None
    for name in ranked2:
        if name == "df" or ref_ir is None:
            best, score = name, min(times[name])
            break
        el_ir = impulse_ir(a.dsp, CAND[name], CAND_ENV.get(name, {}), workdir, name)
        if el_ir is not None and ir_equivalent(ref_ir, el_ir):
            best, score = name, min(times[name])
            break
        print(f"  {name}: DISQUALIFIÉ (réponse impulsionnelle fausse)")
    if best is None and ranked2:
        best, score = "df" if "df" in built else ranked2[0], min(times["df" if "df" in built else ranked2[0]])
    print(f"faustauto: gagnant {best} ({score:.4f} ns/éch.) — options : "
          f"{' '.join(CAND[best])}  [{time.time()-t0:.1f} s]")
    if a.output:
        with open(a.output, "w") as out:
            out.write(open(built[best][0]).read())
        print(f"faustauto: émis dans {a.output}")
    if not a.keep:
        import shutil
        shutil.rmtree(workdir, ignore_errors=True)


if __name__ == "__main__":
    main()
