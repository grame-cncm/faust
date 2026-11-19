#!/usr/bin/env python3
"""
Interp vs interp-fpb: correctness and speed on DSPs of the Faust examples (DSPS below).

For every DSP:
  1. faust -lang interp -single -> <name>.fbc (a faust built with the INTERP backend)
  2. both engines write their outputs for the same input, with a parameter change halfway: they must be identical
  3. both engines are timed (ns per sample, best of 5 runs)
Then the same correctness check with -double on a few DSPs.

  python3 run-bench.py --faust <faust> --arch <faust>/architecture \
      --libfaust-interp <libfaust.a with INTERP> --libfaust-fpb <libfaust.a with INTERP_COMP + INTERP_FPB_BUILD> \
      [--lib <dir with stdfaust.lib>] [--sr 48000] [--bs 128] [--seconds 1] [--only osc,echo] [--out build]

Writes results.md and results.json next to this script.
"""
import argparse
import json
import math
import os
import platform
import struct
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.normpath(os.path.join(HERE, "..", "..", ".."))

# name -> DSP, relative to the root of the Faust repository
DSPS = {
    "compressor": "examples/dynamic/compressor.dsp",
    "crybaby": "examples/filtering/cryBaby.dsp",
    "echo": "examples/delayEcho/echo.dsp",
    "flanger": "examples/phasing/flanger.dsp",
    "freeverb": "examples/reverb/freeverb.dsp",
    "moog_vcf": "examples/filtering/moogVCF.dsp",
    "osc": "examples/generator/osc.dsp",
    "parametric_eq": "examples/filtering/parametricEqualizer.dsp",
    "phaser2": "examples/phasing/phaser.dsp",
    "virtual_analog_oscillator": "examples/generator/virtualAnalog.dsp",
    "vocoder": "examples/filtering/vocoder.dsp",
    "zita_rev1": "examples/reverb/zitaRev.dsp",
}


def dsp_path(name):
    return os.path.join(ROOT, DSPS[name])


def run(cmd, env=None, check=True):
    r = subprocess.run(cmd, capture_output=True, text=True, env=env)
    if check and r.returncode != 0:
        raise RuntimeError(" ".join(cmd) + " failed:\n" + (r.stderr or r.stdout)[-2000:])
    return r


def compare(a, b, fmt):
    if len(a) != len(b):
        return None
    size = struct.calcsize(fmt)
    n = len(a) // size
    x = struct.unpack("<%d%s" % (n, fmt), a)
    y = struct.unpack("<%d%s" % (n, fmt), b)
    m = 0.0
    for u, v in zip(x, y):
        if u != v:
            d = abs(u - v) if not (math.isnan(u) or math.isnan(v)) else float("inf")
            m = max(m, d)
    return m


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--faust", required=True)
    ap.add_argument("--arch", required=True)
    ap.add_argument("--libfaust-interp", required=True)
    ap.add_argument("--libfaust-fpb", required=True)
    ap.add_argument("--lib", default=None)
    ap.add_argument("--sr", default="48000")
    ap.add_argument("--bs", default="128")
    ap.add_argument("--seconds", default="1")
    ap.add_argument("--only", default=None)
    ap.add_argument("--out", default=os.path.join(HERE, "build"))
    ap.add_argument("--cxx", default=os.environ.get("CXX", "c++"))
    args = ap.parse_args()
    os.makedirs(args.out, exist_ok=True)
    lib = args.lib or run([args.faust, "--dspdir"]).stdout.strip()

    exe = {}
    for kind, libfaust in (("interp", args.libfaust_interp), ("fpb", args.libfaust_fpb)):
        for real in ("float", "double"):
            e = os.path.join(args.out, "bench-%s-%s" % (kind, real))
            cmd = [args.cxx, "-std=c++17", "-O3", "-I", args.arch, os.path.join(HERE, "interp-fpb-bench.cpp"),
                   libfaust, "-o", e]
            if real == "double":
                cmd.insert(3, "-DFAUSTFLOAT=double")
            run(cmd)
            exe[(kind, real)] = e

    names = sorted(DSPS)
    if args.only:
        names = [n for n in names if n in args.only.split(",")]
    trace_env = dict(os.environ, FAUST_INTERP_FPB_TRACE="1")
    results = []
    for name in names:
        dsp = dsp_path(name)
        fbc = os.path.join(args.out, name + ".fbc")
        r = {"name": name}
        results.append(r)
        try:
            run([args.faust, "-I", lib, "-lang", "interp", "-single", dsp, "-o", fbc])
            dumps = {}
            for kind in ("interp", "fpb"):
                out = os.path.join(args.out, "%s.%s.f32" % (name, kind))
                p = run([exe[(kind, "float")], "dump", fbc, out, "400", args.sr, args.bs],
                        env=trace_env if kind == "fpb" else None)
                if kind == "fpb":
                    r["trace"] = p.stderr.strip()
                with open(out, "rb") as f:
                    dumps[kind] = f.read()
            r["diff"] = compare(dumps["interp"], dumps["fpb"], "f")
            r["compiled"] = "compiled to" in r["trace"]
            for kind in ("interp", "fpb"):
                p = run([exe[(kind, "float")], "bench", fbc, args.sr, args.bs, args.seconds])
                r[kind + "_ns"] = json.loads(p.stdout)["ns"]
            print("%-28s interp %9.2f ns  interp-fpb %9.2f ns  x%.2f  diff %s  %s" % (
                name, r["interp_ns"], r["fpb_ns"], r["interp_ns"] / r["fpb_ns"], r["diff"],
                "" if r["compiled"] else "(NOT COMPILED: " + r["trace"] + ")"))
        except Exception as e:
            r["error"] = str(e)
            print("%-28s ERROR %s" % (name, str(e).splitlines()[0]))

    # -double: correctness only
    doubles = []
    for name in [n for n in ("osc", "freeverb", "zita_rev1", "vocoder") if n in names]:
        dsp = dsp_path(name)
        fbc = os.path.join(args.out, name + ".double.fbc")
        run([args.faust, "-I", lib, "-lang", "interp", "-double", dsp, "-o", fbc])
        dumps = {}
        for kind in ("interp", "fpb"):
            out = os.path.join(args.out, "%s.double.%s.f64" % (name, kind))
            p = run([exe[(kind, "double")], "dump", fbc, out, "400", args.sr, args.bs], env=trace_env)
            with open(out, "rb") as f:
                dumps[kind] = f.read()
        d = compare(dumps["interp"], dumps["fpb"], "d")
        doubles.append({"name": name, "diff": d})
        print("-double %-20s diff %s" % (name, d))

    # two instances of one factory, used alternately
    multis = []
    for name in [n for n in ("osc", "zita_rev1", "vocoder") if n in names]:
        fbc = os.path.join(args.out, name + ".fbc")
        dumps = {}
        for kind in ("interp", "fpb"):
            out = os.path.join(args.out, "%s.multi.%s.f32" % (name, kind))
            run([exe[(kind, "float")], "multi", fbc, out])
            with open(out, "rb") as f:
                dumps[kind] = f.read()
        d = compare(dumps["interp"], dumps["fpb"], "f")
        multis.append({"name": name, "diff": d})
        print("two instances %-14s diff %s" % (name, d))

    # a block the FPB compiler does not take (vector mode): the interpreter must run it, with the same result
    fallbacks = []
    for name in [n for n in ("osc", "freeverb") if n in names]:
        dsp = dsp_path(name)
        fbc = os.path.join(args.out, name + ".vec.fbc")
        run([args.faust, "-I", lib, "-lang", "interp", "-single", "-vec", "-lv", "1", dsp, "-o", fbc])
        dumps, trace = {}, ""
        for kind in ("interp", "fpb"):
            out = os.path.join(args.out, "%s.vec.%s.f32" % (name, kind))
            p = run([exe[(kind, "float")], "dump", fbc, out, "400", args.sr, args.bs], env=trace_env)
            if kind == "fpb":
                trace = p.stderr.strip()
            with open(out, "rb") as f:
                dumps[kind] = f.read()
        d = compare(dumps["interp"], dumps["fpb"], "f")
        fallbacks.append({"name": name, "diff": d, "trace": trace})
        print("-vec fallback %-14s diff %s  (%s)" % (name, d, trace))

    env = {
        "cpu": run(["sysctl", "-n", "machdep.cpu.brand_string"], check=False).stdout.strip() or platform.processor(),
        "os": "%s %s %s" % (platform.system(), platform.release(), platform.machine()),
        "cxx": run([args.cxx, "--version"]).stdout.splitlines()[0] + "  -O3",
        "faust": run([args.faust, "--version"]).stdout.splitlines()[0],
        "sr": args.sr, "bs": args.bs, "seconds": args.seconds,
    }
    with open(os.path.join(HERE, "results.json"), "w") as f:
        json.dump({"env": env, "results": results, "double": doubles, "multi": multis, "fallback": fallbacks}, f, indent=2)

    ok = [r for r in results if "fpb_ns" in r]
    lines = ["# interp vs interp-fpb", "",
             "%s, %s." % (env["cpu"], env["os"]), "",
             "- C++ compiler: %s (the libraries and this bench)" % env["cxx"],
             "- %s; FBC from `-lang interp -single`" % env["faust"],
             "- Sample rate %s Hz, blocks of %s samples, best of 5 runs of %.1f s each, after a warm-up."
             % (args.sr, args.bs, float(args.seconds) / 5),
             "- **interp**: libfaust built with the INTERP backend; **interp-fpb**: libfaust built with INTERP_COMP "
             "and `INTERP_FPB_BUILD` (the DSP block compiled to FPB steps, the other blocks interpreted).",
             "- **diff**: max |interp − interp-fpb| over 400 blocks of noise, with every parameter moved halfway "
             "(0 = identical outputs).", "",
             "| DSP | interp ns / sample | interp-fpb ns / sample | speedup | diff | FPB steps |",
             "|---|---:|---:|---:|---:|---|"]
    for r in ok:
        steps = r["trace"].split("compiled to ")[1].split(" steps")[0] if r["compiled"] else "not compiled"
        lines.append("| [%s](../../../%s) | %.2f | %.2f | **×%.2f** | %s | %s |" % (
            r["name"], DSPS[r["name"]], r["interp_ns"], r["fpb_ns"], r["interp_ns"] / r["fpb_ns"],
            "0" if r["diff"] == 0 else ("%.1e" % r["diff"] if r["diff"] is not None else "size differs"), steps))
    if ok:
        g = math.exp(sum(math.log(r["interp_ns"] / r["fpb_ns"]) for r in ok) / len(ok))
        lines.append("| **geometric mean** | | | **×%.2f** | | |" % g)
    if doubles:
        lines += ["", "`-double` (correctness only): " + ", ".join(
            "%s %s" % (d["name"], "identical" if d["diff"] == 0 else "diff %s" % d["diff"]) for d in doubles) + "."]
    if multis:
        lines += ["", "Two instances of one factory, computed alternately (correctness only): " + ", ".join(
            "%s %s" % (d["name"], "identical" if d["diff"] == 0 else "diff %s" % d["diff"]) for d in multis) + "."]
    if fallbacks:
        lines += ["", "`-vec` (not compiled by FPB, the interpreter runs the DSP block): " + ", ".join(
            "%s %s" % (d["name"], "identical" if d["diff"] == 0 else "diff %s" % d["diff"]) for d in fallbacks) + "."]
    bad = [r for r in results if "fpb_ns" not in r]
    if bad:
        lines += ["", "Not measured:", ""] + ["- **%s**: %s" % (r["name"], r.get("error", "").splitlines()[0]) for r in bad]
    with open(os.path.join(HERE, "results.md"), "w") as f:
        f.write("\n".join(lines) + "\n")
    print("\nwrote results.md and results.json")
    if any(r.get("diff") not in (0, 0.0) for r in ok) or any(d["diff"] not in (0, 0.0) for d in doubles + multis + fallbacks):
        sys.exit(1)


if __name__ == "__main__":
    main()
