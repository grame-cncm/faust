#!/usr/bin/env python3
"""
The compile-time budget : the time faust takes on two sets of programs, against a reference
binary, and two ceilings it must not pass.

  budget.py FAUST REF [--total T] [--one O] [--floor F] [--runs N] [--timeout S]

Each program is compiled N times by each binary (the minimum is kept : the noise of the
machine only adds time), in single and double precision. The gate fails when the ratio of
the total times of a set passes T, or the ratio of one program passes O ; a reference time
below F seconds counts as F there, since a fixed step of a few milliseconds multiplies the
time of a program the reference compiles at once. The gate also fails when FAUST refuses a
program REF accepts (refusing a costly program would lower the ratio), or when a compilation
takes more than S seconds ; a program refused by REF is left out and counted. The sets : the
impulse tests (tests/impulse-tests/dsp), and the programs whose compilation was the slowest
against master-dev when the gate was set.
"""
import argparse, os, platform, subprocess, sys, time

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(HERE, "..", ".."))
WORST = ["examples/smartKeyboard/violin2.dsp", "examples/physicalModeling/violin.dsp",
         "examples/reverb/fdnRev.dsp", "examples/reverb/reverbDesigner.dsp",
         "examples/physicalModeling/mi-faust/13_Construction/construction.dsp",
         "examples/physicalModeling/mi-faust/12_TriangleMesh/triangleMesh.dsp",
         "examples/misc/guitarix.dsp"]

def version(b):
    out = subprocess.run([b, "--version"], capture_output=True, text=True).stdout.splitlines()
    return out[1] if len(out) > 1 else "?"

def timed(b, args, runs, timeout):
    """("ok", best time), ("refused", None) or ("timeout", None)"""
    best = None
    for _ in range(runs):
        t0 = time.perf_counter()
        try:
            r = subprocess.run([b] + args, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL,
                               timeout=timeout)
        except subprocess.TimeoutExpired:
            return "timeout", None
        dt = time.perf_counter() - t0
        if r.returncode != 0: return "refused", None
        best = dt if best is None else min(best, dt)
    return "ok", best

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("faust"); ap.add_argument("ref")
    ap.add_argument("--total", type=float, default=3.0)
    ap.add_argument("--one", type=float, default=8.0)
    ap.add_argument("--floor", type=float, default=0.05)
    ap.add_argument("--runs", type=int, default=3)
    ap.add_argument("--timeout", type=float, default=300.0)
    a = ap.parse_args()
    print("faust : %s (%s)" % (a.faust, version(a.faust)))
    print("ref   : %s (%s)" % (a.ref, version(a.ref)))
    print("machine : %s %s, %d runs per compilation, ceilings : total x%.2f, one x%.2f (floor %.3f s), "
          "timeout %.0f s" % (platform.machine(), platform.system(), a.runs, a.total, a.one, a.floor, a.timeout))
    impulse = sorted(os.path.join("tests/impulse-tests/dsp", f)
                     for f in os.listdir(os.path.join(ROOT, "tests/impulse-tests/dsp")) if f.endswith(".dsp"))
    sets = [("impulse", impulse), ("worst", WORST)]
    bad = 0
    for name, files in sets:
        for prec in ("-single", "-double"):
            tb = tr = 0.0; n = 0; skipped = 0; worst = (0.0, ""); over = []; failed = []
            for f in files:
                path = os.path.join(ROOT, f)
                args = ["-lang", "cpp", prec, "-I", os.path.dirname(path), path, "-o", os.devnull]
                sb, b = timed(a.faust, args, a.runs, a.timeout)
                sr, r = timed(a.ref, args, a.runs, a.timeout)
                if sb == "timeout" or sr == "timeout":
                    failed.append("%s : more than %.0f s (%s)" % (f, a.timeout, "faust" if sb == "timeout" else "ref"))
                    continue
                if sb == "refused" and sr == "ok":
                    failed.append("%s : refused by faust, accepted by ref" % f); continue
                if sr == "refused":
                    skipped += 1; continue
                n += 1; tb += b; tr += r
                one = b / max(r, a.floor)
                if one > worst[0]: worst = (one, f)
                if one > a.one: over.append("%s x%.2f (%.3f s against %.3f s)" % (f, one, b, r))
            if n == 0:
                print("FAIL  %-7s %-7s : no program measured" % (name, prec)); bad += 1
                for o in failed: print("      " + o)
                continue
            ratio = tb / tr
            ok = ratio <= a.total and worst[0] <= a.one and not failed
            print("%s  %-7s %-7s : %d programs (%d refused by ref, left out), %.2f s against %.2f s, "
                  "x%.2f ; worst x%.2f %s" % ("ok  " if ok else "FAIL", name, prec, n, skipped, tb, tr, ratio,
                                              worst[0], worst[1]))
            for o in over: print("      over the ceiling : " + o)
            for o in failed: print("      " + o)
            bad += 0 if ok else 1
    print("%d legs failed" % bad)
    sys.exit(1 if bad else 0)

main()
