#!/usr/bin/env python3
"""
interp-ydsp against interp-mir on a corpus of DSPs (directories of .dsp files), with the bench executables that
run-bench.py builds (bench-interp-float, bench-mir-float, bench-ydsp-float in --bin).

For every DSP:
  1. faust -lang interp -single (from the DSP's directory) -> .fbc; a DSP faust rejects is counted and skipped
  2. the interpreter, interp-mir and interp-ydsp write their outputs (interp-fpb-bench.cpp 'dump': 400 blocks of
     noise, every parameter moved to 60 % halfway); MIR and YDSP must give the interpreter's outputs, bit for bit
  3. the three engines are timed (ns per sample, best of 5 runs)
interp-mir runs with its defaults (promotion of heap cells on), interp-ydsp with its defaults. A DSP whose block
YDSP does not compile (the interpreter runs it) or that crashes an engine is reported, and left out of the means.

  python3 run-corpus.py --bin <run-bench out dir> --faust <faust> --lib <dir with stdfaust.lib> \\
      --corpus <dir> [--corpus <dir> ...] [--seconds 0.5] [--out <dir>] [--name <report name>]

Writes corpus-<name>.md and corpus-<name>.json next to this script.
"""
import argparse
import glob
import json
import math
import os
import platform
import re
import struct
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.normpath(os.path.join(HERE, "..", "..", ".."))
ENGINES = ("interp", "mir", "ydsp")
TIMEOUT = 300


def run(cmd, env=None, cwd=None):
    try:
        return subprocess.run(cmd, capture_output=True, text=True, env=env, cwd=cwd, timeout=TIMEOUT)
    except subprocess.TimeoutExpired:
        return None


def compare(a, b):
    """(number of float32 samples whose bits differ, largest difference), None if the sizes differ"""
    if len(a) != len(b):
        return None
    if a == b:
        return (0, 0.0)
    n = len(a) // 4
    x, y = struct.unpack("<%dI" % n, a), struct.unpack("<%dI" % n, b)
    fx, fy = struct.unpack("<%df" % n, a), struct.unpack("<%df" % n, b)
    count, m = 0, 0.0
    for i in range(n):
        if x[i] != y[i]:
            count += 1
            u, v = fx[i], fy[i]
            m = max(m, abs(u - v) if not (math.isnan(u) or math.isnan(v)) else float("inf"))
    return (count, m)


def quantiles(vals, qs):
    s = sorted(vals)
    out = []
    for q in qs:
        k = (len(s) - 1) * q
        f, c = math.floor(k), math.ceil(k)
        out.append(s[f] if f == c else s[f] + (s[c] - s[f]) * (k - f))
    return out


def gmean(vals):
    return math.exp(sum(math.log(v) for v in vals) / len(vals)) if vals else float("nan")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--bin", required=True)
    ap.add_argument("--faust", required=True)
    ap.add_argument("--lib", required=True)
    ap.add_argument("--corpus", action="append", required=True)
    ap.add_argument("--seconds", default="0.5")
    ap.add_argument("--out", default=os.path.join(HERE, "build", "corpus"))
    ap.add_argument("--name", default="corpus")
    args = ap.parse_args()
    os.makedirs(args.out, exist_ok=True)
    exe = {e: os.path.join(args.bin, "bench-%s-float" % e) for e in ENGINES}
    trace_env = dict(os.environ, FAUST_INTERP_YDSP_TRACE="1")

    dsps = []
    for c in args.corpus:
        dsps += sorted(glob.glob(os.path.join(os.path.abspath(c), "**", "*.dsp"), recursive=True))
    results = []
    for i, dsp in enumerate(dsps):
        rel = os.path.relpath(dsp, ROOT)
        tag = re.sub(r"[^A-Za-z0-9_.-]", "_", rel)
        fbc = os.path.join(args.out, tag + ".fbc")
        r = {"dsp": rel}
        results.append(r)
        p = run([args.faust, "-I", args.lib, "-I", os.path.dirname(dsp), "-lang", "interp", "-single", dsp, "-o", fbc],
                cwd=os.path.dirname(dsp))
        if p is None or p.returncode != 0 or not os.path.exists(fbc):
            r["status"] = "faust failed"
            r["why"] = ("timeout" if p is None else (p.stderr or p.stdout).strip().splitlines()[-1:] or [""])
            print("%3d/%d %-60s faust failed" % (i + 1, len(dsps), rel))
            continue
        data = {}
        bad = None
        for e in ENGINES:
            out = os.path.join(args.out, "%s.%s.f32" % (tag, e))
            p = run([exe[e], "dump", fbc, out, "400", "48000", "128"], env=trace_env)
            if p is None or p.returncode != 0:
                bad = "%s %s" % (e, "timeout" if p is None else "exit %d" % p.returncode)
                break
            if e == "ydsp":
                r["ydsp_trace"] = p.stderr.strip()
            with open(out, "rb") as f:
                data[e] = f.read()
            os.remove(out)
        if bad:
            r["status"] = "crash"
            r["why"] = bad
            print("%3d/%d %-60s CRASH %s" % (i + 1, len(dsps), rel, bad))
            continue
        r["diff"] = {e: compare(data["interp"], data[e]) for e in ("mir", "ydsp")}
        r["ydsp_compiled"] = "compiled to" in r.get("ydsp_trace", "")
        m = re.search(r"compiled to (\d+) bytes.*?, ([\d.]+) ms", r.get("ydsp_trace", ""))
        if m:
            r["ydsp_bytes"], r["ydsp_ms"] = int(m.group(1)), float(m.group(2))
        r["ns"] = {}
        for e in ENGINES:
            p = run([exe[e], "bench", fbc, "48000", "128", args.seconds])
            if p is None or p.returncode != 0:
                r["ns"] = None
                break
            r["ns"][e] = json.loads(p.stdout)["ns"]
        same = all(d is not None and d[0] == 0 for d in r["diff"].values())
        if r["ns"] is None:
            r["status"] = "crash"
            r["why"] = "while timing"
        elif not same:
            r["status"] = "differs"
        elif not r["ydsp_compiled"]:
            r["status"] = "ydsp not compiled"
            r["why"] = r.get("ydsp_trace", "")
        else:
            r["status"] = "ok"
        ns = r["ns"] or {}
        print("%3d/%d %-60s %-18s %s" % (i + 1, len(dsps), rel, r["status"],
              "  ".join("%s %.1f" % (e, ns[e]) for e in ns) +
              ("  mir/ydsp x%.2f" % (ns["mir"] / ns["ydsp"]) if len(ns) == 3 else "")))

    # report
    ok = [r for r in results if r["status"] == "ok"]
    counts = {}
    for r in results:
        counts[r["status"]] = counts.get(r["status"], 0) + 1
    ratio = [r["ns"]["mir"] / r["ns"]["ydsp"] for r in ok]
    env = {
        "cpu": subprocess.run(["sysctl", "-n", "machdep.cpu.brand_string"], capture_output=True, text=True).stdout.strip(),
        "os": "%s %s %s" % (platform.system(), platform.release(), platform.machine()),
        "faust": " / ".join(subprocess.run([args.faust, "--version"], capture_output=True, text=True).stdout.splitlines()[0:2]),
        "load": os.getloadavg(),
        "seconds": args.seconds,
    }
    with open(os.path.join(HERE, "corpus-%s.json" % args.name), "w") as f:
        json.dump({"env": env, "corpus": [os.path.relpath(os.path.abspath(c), ROOT) for c in args.corpus],
                   "results": results}, f, indent=2)

    lines = ["# interp-ydsp against interp-mir: %s" % args.name, "",
             "%s, %s. Load average at the end: %.1f %.1f %.1f." % ((env["cpu"], env["os"]) + tuple(env["load"])), "",
             "- FBC from `%s`, `-lang interp -single`; bench executables built by run-bench.py." % env["faust"],
             "- Corpus: " + ", ".join("`%s`" % os.path.relpath(os.path.abspath(c), ROOT) for c in args.corpus) +
             " (%d DSPs)." % len(results),
             "- interp-mir and interp-ydsp with their defaults (promotion on in both). Outputs compared with the "
             "interpreter's, bit for bit (400 blocks of noise, parameters moved halfway); best of 5 runs of %.2f s."
             % (float(args.seconds) / 5), "",
             "## Counts", "", "| status | DSPs |", "|---|---:|"]
    for k in ("ok", "ydsp not compiled", "differs", "crash", "faust failed"):
        lines.append("| %s | %d |" % (k, counts.get(k, 0)))
    if ok:
        q = quantiles(ratio, (0, 0.1, 0.25, 0.5, 0.75, 0.9, 1))
        lines += ["", "## Speed, on the %d DSPs both compile with the interpreter's outputs" % len(ok), "",
                  "| ratio | value |", "|---|---:|",
                  "| interp / mir, geometric mean | ×%.2f |" % gmean([r["ns"]["interp"] / r["ns"]["mir"] for r in ok]),
                  "| interp / ydsp, geometric mean | ×%.2f |" % gmean([r["ns"]["interp"] / r["ns"]["ydsp"] for r in ok]),
                  "| **mir / ydsp, geometric mean** | **×%.2f** |" % gmean(ratio),
                  "| mir / ydsp: min, 10 %%, 25 %%, median, 75 %%, 90 %%, max | %s |" % ", ".join("×%.2f" % v for v in q),
                  "| DSPs where YDSP is faster than MIR (ratio > 1) | %d of %d |" % (sum(1 for v in ratio if v > 1), len(ok)),
                  "| DSPs where YDSP is more than 10 %% slower (ratio < 0.9) | %d |" % sum(1 for v in ratio if v < 0.9),
                  "| YDSP compile time: median, max | %.1f ms, %.1f ms |" % tuple(
                      [quantiles([r["ydsp_ms"] for r in ok], (0.5,))[0], max(r["ydsp_ms"] for r in ok)])]
        srt = sorted(ok, key=lambda r: r["ns"]["mir"] / r["ns"]["ydsp"])

        def row(r):
            ns = r["ns"]
            return "| %s | %.2f | %.2f | %.2f | ×%.2f |" % (r["dsp"], ns["interp"], ns["mir"], ns["ydsp"], ns["mir"] / ns["ydsp"])
        hdr = ["| DSP | interp ns | mir ns | ydsp ns | mir / ydsp |", "|---|---:|---:|---:|---:|"]
        lines += ["", "### The 10 DSPs where YDSP does worst against MIR", ""] + hdr + [row(r) for r in srt[:10]]
        lines += ["", "### The 10 DSPs where YDSP does best against MIR", ""] + hdr + [row(r) for r in srt[-10:][::-1]]
    others = [r for r in results if r["status"] != "ok"]
    if others:
        lines += ["", "## Not in the means", "", "| DSP | status | why |", "|---|---|---|"]
        for r in others:
            why = r.get("why", "")
            if r["status"] == "differs":
                why = ", ".join("%s: %s" % (e, "size differs" if d is None else "%d samples differ, max %.1e" % d)
                                for e, d in r["diff"].items() if d is None or d[0] != 0)
            if isinstance(why, list):
                why = " ".join(why)
            why = why.replace("interp-ydsp: DSP block not compiled (", "").replace("), the interpreter runs it", "")
            lines.append("| %s | %s | %s |" % (r["dsp"], r["status"], why.replace("|", "/")[:160]))
    with open(os.path.join(HERE, "corpus-%s.md" % args.name), "w") as f:
        f.write("\n".join(lines) + "\n")
    print("\nwrote corpus-%s.md and corpus-%s.json" % (args.name, args.name))


if __name__ == "__main__":
    main()
