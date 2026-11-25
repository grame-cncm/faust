#!/usr/bin/env python3
"""
Phase 0 of ANALYSE_YDSP_JIT.md: the FBC compiled by YDSP (interp-ydsp) against the interpreter, interp-fpb and
interp-mir, with and without the promotion of heap cells to registers, on the DSPs of the FPB bench.

For every DSP:
  1. faust -lang interp -single -> <name>.fbc (a faust built with the INTERP backend)
  2. every engine writes its outputs for the same input, with a parameter change halfway (interp-fpb-bench.cpp,
     'dump'): they must be identical to the interpreter's
  3. every engine is timed (ns per sample, best of 5 runs); the C++ class of the DSP (faust -lang cpp, compiled with
     -O3 -ffp-contract=off) is timed the same way, as the ceiling
Then the same correctness check with -double, with two instances of one factory, and in vector mode.

Engines: interp; fpb; mir (FAUST_INTERP_MIR_PROMOTE=0); mir+promo (FAUST_INTERP_MIR_PROMOTE=1); ydsp-mem (FAUST_INTERP_YDSP_PROMOTE=0); ydsp;
ydsp-strict (FAUST_INTERP_YDSP_LIBMF32=0: YDSP's strict float32 transcendentals, computed in float64).

  python3 run-bench.py --faust <faust> --arch <faust>/architecture \\
      --libfaust-interp <libfaust.a, INTERP> --libfaust-fpb <libfaust.a, INTERP_COMP + INTERP_FPB_BUILD> \\
      --libfaust-mir <libfaust.a, INTERP_COMP + INTERP_MIR_BUILD> --libmir <libmir.a> \\
      --libfaust-ydsp <libfaust.a, INTERP_COMP + INTERP_YDSP_BUILD> --yup <YUP repository> \\
      [--yup-ninja <YUP build.ninja>] [--lib <dir with stdfaust.lib>] [--sr 48000] [--bs 128] [--seconds 1]
      [--only osc,echo] [--out build]

The YUP modules (yup_core, yup_audio_basics, yup_dsp, yup_dsp_jit, asmjit, SLEEF...) are compiled with the
sources and flags of YUP's own yup_dsp_compiler build, read from its build.ninja, into <out>/yup (once; delete the
directory to rebuild). Nothing is written in the YUP repository. Writes results.md and results.json next to this
script.
"""
import argparse
import concurrent.futures
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
BENCH_SRC = os.path.join(ROOT, "tests", "interp-tests", "interp-fpb", "interp-fpb-bench.cpp")

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

# name, bench executable kind, environment
ENGINES = [
    ("interp", "interp", {}),
    ("fpb", "fpb", {}),
    ("mir", "mir", {"FAUST_INTERP_MIR_PROMOTE": "0"}),
    ("mir+promo", "mir", {"FAUST_INTERP_MIR_PROMOTE": "1"}),
    ("ydsp-mem", "ydsp", {"FAUST_INTERP_YDSP_PROMOTE": "0"}),
    ("ydsp", "ydsp", {}),
    ("ydsp-strict", "ydsp", {"FAUST_INTERP_YDSP_LIBMF32": "0"}),
]
# YDSP's strict mode computes float32 transcendentals in float64 (about one ulp from the interpreter's float32 libm):
# its differences are reported, but do not fail the run
EXPECTED_TO_DIFFER = {"ydsp-strict"}

FRAMEWORKS = ["-framework", "UserNotifications", "-framework", "CoreAudio", "-framework", "CoreMIDI", "-framework",
              "AudioToolbox", "-framework", "Cocoa", "-framework", "IOKit", "-framework", "Security", "-framework",
              "Foundation", "-framework", "Accelerate", "-lz"]


def run(cmd, env=None, check=True, cwd=None):
    r = subprocess.run(cmd, capture_output=True, text=True, env=env, cwd=cwd)
    if check and r.returncode != 0:
        raise RuntimeError(" ".join(cmd) + " failed:\n" + (r.stderr or r.stdout)[-2000:])
    return r


def compare(a, b, fmt):
    """None if the sizes differ, else (number of samples whose bits differ, largest difference of value)"""
    if len(a) != len(b):
        return None
    if a == b:
        return (0, 0.0)
    size = struct.calcsize(fmt)
    n = len(a) // size
    bits = "I" if fmt == "f" else "Q"
    x, y = struct.unpack("<%d%s" % (n, bits), a), struct.unpack("<%d%s" % (n, bits), b)
    fx, fy = struct.unpack("<%d%s" % (n, fmt), a), struct.unpack("<%d%s" % (n, fmt), b)
    count, m = 0, 0.0
    for i in range(n):
        if x[i] != y[i]:
            count += 1
            u, v = fx[i], fy[i]
            m = max(m, abs(u - v) if not (math.isnan(u) or math.isnan(v)) else float("inf"))
    return (count, m)


def identical(d):
    return d is not None and d[0] == 0


def ninja_jobs(ninja):
    """(lang, source, defines, includes, flags) of the yup_dsp_compiler objects of YUP's build.ninja"""
    lines = open(ninja).read().split("\n")
    jobs = []
    for i, line in enumerate(lines):
        m = re.match(r"^build CMakeFiles/yup_dsp_compiler\.dir/\S+\.o: (C|CXX)_COMPILER\S* (\S+)", line)
        if not m:
            continue
        v = {}
        for k in lines[i + 1:i + 12]:
            mm = re.match(r"^  (DEFINES|FLAGS|INCLUDES) = (.*)", k)
            if mm:
                v[mm.group(1)] = mm.group(2).split()
            elif not k.startswith("  "):
                break
        jobs.append((m.group(1), m.group(2), v.get("DEFINES", []), v.get("INCLUDES", []), v.get("FLAGS", [])))
    return jobs


def build_yup(ninja, out):
    lib = os.path.join(out, "libyup_ydsp.a")
    if os.path.exists(lib):
        return lib
    os.makedirs(out, exist_ok=True)
    cmds = []
    for lang, src, d, inc, fl in ninja_jobs(ninja):
        if "/cmake/tools/" in src:  # the tool itself
            continue
        obj = os.path.join(out, os.path.basename(src) + ".o")
        extra = ["-x", "objective-c++"] if src.endswith(".mm") else []
        cmds.append((obj, ["clang++" if lang == "CXX" else "clang"] + extra + d + inc + fl + ["-c", src, "-o", obj]))

    def one(c):
        # from <out>: a file named 'version' in the current directory (the Faust root has one) hides <version>
        return c[0], run(c[1], check=False, cwd=out)

    with concurrent.futures.ThreadPoolExecutor(8) as ex:
        for obj, r in ex.map(one, cmds):
            if r.returncode != 0:
                raise RuntimeError("YUP: " + obj + "\n" + r.stderr[-2000:])
    run(["libtool", "-static", "-o", lib] + [c[0] for c in cmds], cwd=out)
    return lib


def lib_commit(lib):
    """the FAUSTGITVERSION string compiled into a libfaust archive"""
    r = run(["strings", "-a", lib], check=False)
    found = sorted(set(l for l in r.stdout.split("\n") if re.fullmatch(r"[0-9a-f]{9}(-modified)?", l)))
    return ", ".join(found) or "unknown"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--faust", required=True)
    ap.add_argument("--arch", required=True)
    for k in ("interp", "fpb", "mir", "ydsp"):
        ap.add_argument("--libfaust-" + k, required=True)
    ap.add_argument("--libmir", default="/usr/local/lib/libmir.a")
    ap.add_argument("--yup", default=os.path.expanduser("~/Developpements/yup"))
    ap.add_argument("--yup-ninja", default=None)
    ap.add_argument("--lib", default=None)
    ap.add_argument("--sr", default="48000")
    ap.add_argument("--bs", default="128")
    ap.add_argument("--seconds", default="1")
    ap.add_argument("--only", default=None)
    ap.add_argument("--out", default=os.path.join(HERE, "build"))
    ap.add_argument("--cxx", default=os.environ.get("CXX", "clang++"))
    args = ap.parse_args()
    os.makedirs(args.out, exist_ok=True)
    out = args.out
    lib = args.lib or run([args.faust, "--dspdir"]).stdout.strip()
    ninja = args.yup_ninja or os.path.join(args.yup, "build", "ydsp_compiler", "build.ninja")

    # 1. YUP, the translator, the bench executables
    yuplib = build_yup(ninja, os.path.join(out, "yup"))
    jit = [j for j in ninja_jobs(ninja) if j[1].endswith("yup_dsp_jit/yup_dsp_jit.cpp")][0]
    obj = os.path.join(out, "fbc_ydsp_compiler.o")
    inc = ["-I" + os.path.join(ROOT, p) for p in ("compiler/generator/interpreter", "compiler/generator", "compiler",
                                                 "compiler/tlib", "compiler/errors", "architecture")]
    run([args.cxx, "-std=gnu++20", "-O3", "-DNDEBUG"] + jit[2] + jit[3] + inc +
        ["-c", os.path.join(HERE, "fbc_ydsp_compiler.cpp"), "-o", obj], cwd=out)
    links = {
        "interp": [args.libfaust_interp],
        "fpb": [args.libfaust_fpb],
        "mir": [args.libfaust_mir, args.libmir],
        "ydsp": [obj, args.libfaust_ydsp, yuplib] + FRAMEWORKS,
    }
    exe = {}
    for kind, deps in links.items():
        for real in ("float", "double"):
            e = os.path.join(out, "bench-%s-%s" % (kind, real))
            cmd = [args.cxx, "-std=c++17", "-O3", "-I", args.arch, BENCH_SRC] + deps + ["-o", e]
            if real == "double":
                cmd.insert(3, "-DFAUSTFLOAT=double")
            run(cmd, cwd=out)
            exe[(kind, real)] = e

    def engine_env(env, trace=False):
        e = dict(os.environ, **env)
        if trace:
            e["FAUST_INTERP_YDSP_TRACE"] = "1"
            e["FAUST_INTERP_FPB_TRACE"] = "1"
        return e

    def dump(kind, env, real, fbc, outfile, mode="dump"):
        cmd = [exe[(kind, real)], mode, fbc, outfile] + (["400", args.sr, args.bs] if mode == "dump" else [])
        p = run(cmd, env=engine_env(env, True), cwd=out)
        with open(outfile, "rb") as f:
            return f.read(), p.stderr.strip()

    names = sorted(DSPS)
    if args.only:
        names = [n for n in names if n in args.only.split(",")]
    results = []
    for name in names:
        dsp = os.path.join(ROOT, DSPS[name])
        fbc = os.path.join(out, name + ".fbc")
        r = {"name": name, "ns": {}, "diff": {}, "trace": {}}
        results.append(r)
        try:
            run([args.faust, "-I", lib, "-lang", "interp", "-single", dsp, "-o", fbc])
            ref = None
            for ename, kind, env in ENGINES:
                data, trace = dump(kind, env, "float", fbc, os.path.join(out, "%s.%s.f32" % (name, ename)))
                r["trace"][ename] = trace
                if ename == "interp":
                    ref = data
                else:
                    r["diff"][ename] = compare(ref, data, "f")
            for ename, kind, env in ENGINES:
                p = run([exe[(kind, "float")], "bench", fbc, args.sr, args.bs, args.seconds], env=engine_env(env),
                        cwd=out)
                r["ns"][ename] = json.loads(p.stdout)["ns"]
            # the ceiling: the C++ class of the DSP
            cpp = os.path.join(out, name + ".cpp")
            run([args.faust, "-I", lib, "-lang", "cpp", "-single", "-a", os.path.join(HERE, "cpp-bench-arch.cpp"),
                 dsp, "-o", cpp])
            ce = os.path.join(out, name + "-cpp")
            run([args.cxx, "-std=c++17", "-O3", "-ffp-contract=off", "-I", args.arch, cpp, "-o", ce])
            r["ns"]["cpp"] = json.loads(run([ce, args.sr, args.bs, args.seconds]).stdout)["ns"]
            m = re.search(r"compiled to (\d+) bytes .*?(\d+) IR instructions.*?, ([\d.]+) ms", r["trace"]["ydsp"])
            r["ydsp_bytes"], r["ydsp_ms"] = (int(m.group(1)), float(m.group(3))) if m else (None, None)
            r["ydsp_compiled"] = m is not None
            print("%-26s " % name + "  ".join("%s %.1f" % (e, r["ns"][e]) for e in r["ns"]) +
                  "  identical " + ("yes" if all(identical(d) for d in r["diff"].values()) else str(r["diff"])) +
                  ("" if m else "  (YDSP: " + r["trace"]["ydsp"] + ")"))
        except Exception as e:
            r["error"] = str(e)
            print("%-26s ERROR %s" % (name, str(e).splitlines()[0]))

    def check(label, names_, faust_opts, real, mode="dump"):
        rows = []
        for name in [n for n in names_ if n in names]:
            dsp = os.path.join(ROOT, DSPS[name])
            fbc = os.path.join(out, "%s.%s.fbc" % (name, label))
            run([args.faust, "-I", lib, "-lang", "interp"] + faust_opts + [dsp, "-o", fbc])
            fmt = "d" if real == "double" else "f"
            ref, row = None, {"name": name, "diff": {}, "trace": {}}
            for ename, kind, env in ENGINES:
                data, trace = dump(kind, env, real, fbc, os.path.join(out, "%s.%s.%s" % (name, label, ename)), mode)
                row["trace"][ename] = trace
                if ename == "interp":
                    ref = data
                else:
                    row["diff"][ename] = compare(ref, data, fmt)
            rows.append(row)
            print("%-8s %-20s %s" % (label, name, row["diff"]))
        return rows

    doubles = check("double", ("osc", "freeverb", "zita_rev1", "vocoder"), ["-double"], "double")
    multis = check("multi", ("osc", "zita_rev1", "vocoder"), ["-single"], "float", "multi")
    vecs = check("vec", ("osc", "freeverb"), ["-single", "-vec", "-lv", "1"], "float")

    env = {
        "cpu": run(["sysctl", "-n", "machdep.cpu.brand_string"], check=False).stdout.strip() or platform.processor(),
        "os": "%s %s %s" % (platform.system(), platform.release(), platform.machine()),
        "cxx": run([args.cxx, "--version"]).stdout.splitlines()[0],
        "faust": " / ".join(run([args.faust, "--version"]).stdout.splitlines()[0:2]),
        "libfaust": {k: lib_commit(getattr(args, "libfaust_" + k)) for k in ("interp", "fpb", "mir", "ydsp")},
        "yup": run(["git", "-C", args.yup, "log", "-1", "--format=%h %ad", "--date=short"], check=False).stdout.strip(),
        "sr": args.sr, "bs": args.bs, "seconds": args.seconds,
    }
    with open(os.path.join(HERE, "results.json"), "w") as f:
        json.dump({"env": env, "results": results, "double": doubles, "multi": multis, "vec": vecs}, f, indent=2)

    ok = [r for r in results if "error" not in r]
    cols = [e[0] for e in ENGINES] + ["cpp"]

    def gmean(f):
        vals = [f(r) for r in ok]
        return math.exp(sum(math.log(v) for v in vals) / len(vals)) if vals else float("nan")

    def fmt_diff(d):
        if d is None:
            return "size differs"
        return "0" if d[0] == 0 else "%d samples differ, max %.1e" % d

    lines = ["# interp-ydsp: phase 0 measurements", "",
             "%s, %s." % (env["cpu"], env["os"]), "",
             "- C++ compiler: %s, `-O3` (libraries, bench, translator); the C++ ceiling with `-O3 -ffp-contract=off`"
             % env["cxx"],
             "- FBC from `%s`, `-lang interp -single`" % env["faust"],
             "- libfaust (`Source commit` compiled in): " + ", ".join("%s %s" % kv for kv in env["libfaust"].items()),
             "- YUP %s (YDSP module compiled with the flags of YUP's own Release build)" % env["yup"],
             "- Sample rate %s Hz, blocks of %s samples, best of 5 runs of %.1f s each, after a warm-up."
             % (args.sr, args.bs, float(args.seconds) / 5),
             "- **interp**: the interpreter; **fpb**, **mir**: the DSP block compiled by interp-fpb, interp-mir "
             "(`FAUST_INTERP_MIR_PROMOTE=0`); **mir+promo**: interp-mir with `FAUST_INTERP_MIR_PROMOTE=1`; **ydsp-mem**: interp-ydsp with "
             "`FAUST_INTERP_YDSP_PROMOTE=0`; **ydsp**: interp-ydsp (promotion on); **ydsp-strict**: interp-ydsp "
             "with `FAUST_INTERP_YDSP_LIBMF32=0` (YDSP's strict mode: float32 transcendentals computed in float64, "
             "expected to differ from the interpreter by about one ulp); **cpp**: the C++ class.",
             "- Every engine's outputs are compared with the interpreter's (400 blocks of noise, every parameter "
             "moved halfway): **%d DSPs**, %d engines compared with the interpreter on each, bit for bit."
             % (len(ok), len(ENGINES) - 1),
             "", "## ns per sample", "",
             "| DSP | " + " | ".join(cols) + " | mir / ydsp-mem | mir+promo / ydsp | ydsp / cpp | identical | YDSP code, compile |",
             "|---|" + "---:|" * (len(cols) + 3) + "---|---|"]
    for r in ok:
        ns = r["ns"]
        same = all(identical(d) for e, d in r["diff"].items() if e not in EXPECTED_TO_DIFFER)
        lines.append("| [%s](../../../%s) | " % (r["name"], DSPS[r["name"]]) +
                     " | ".join("%.2f" % ns[c] for c in cols) +
                     " | ×%.2f | ×%.2f | ×%.2f | %s | %s |" % (
                         ns["mir"] / ns["ydsp-mem"], ns["mir+promo"] / ns["ydsp"], ns["ydsp"] / ns["cpp"],
                         ("yes" if same else "NO: " + ", ".join("%s %s" % (e, fmt_diff(d)) for e, d in r["diff"].items()
                                                              if not identical(d) and e not in EXPECTED_TO_DIFFER))
                         + ("" if identical(r["diff"]["ydsp-strict"]) else " (ydsp-strict: %s)" % fmt_diff(r["diff"]["ydsp-strict"])),
                         "%d B, %.1f ms" % (r["ydsp_bytes"], r["ydsp_ms"]) if r["ydsp_compiled"] else "not compiled"))
    lines += ["", "## Geometric means", "",
              "| ratio | value |", "|---|---:|"]
    for e in cols[1:]:
        lines.append("| interp / %s (speedup over the interpreter) | ×%.2f |" % (e, gmean(lambda r: r["ns"]["interp"] / r["ns"][e])))
    lines += ["| mir / ydsp-mem (the code generator, same translation without promotion) | ×%.2f |"
              % gmean(lambda r: r["ns"]["mir"] / r["ns"]["ydsp-mem"]),
              "| mir+promo / ydsp (the code generator, same translation with promotion) | ×%.2f |"
              % gmean(lambda r: r["ns"]["mir+promo"] / r["ns"]["ydsp"]),
              "| mir / mir+promo (promotion, MIR) | ×%.2f |" % gmean(lambda r: r["ns"]["mir"] / r["ns"]["mir+promo"]),
              "| ydsp-mem / ydsp (promotion, YDSP) | ×%.2f |" % gmean(lambda r: r["ns"]["ydsp-mem"] / r["ns"]["ydsp"]),
              "| ydsp-strict / ydsp (YDSP's strict float32 transcendentals, in float64) | ×%.2f |"
              % gmean(lambda r: r["ns"]["ydsp-strict"] / r["ns"]["ydsp"]),
              "| ydsp / cpp (distance to the C++ ceiling) | ×%.2f |" % gmean(lambda r: r["ns"]["ydsp"] / r["ns"]["cpp"])]

    def summary(label, rows):
        return "%s: " % label + "; ".join(
            "%s %s" % (row["name"], "identical for every engine" if all(identical(d) for d in row["diff"].values())
                       else ", ".join("%s %s" % (e, fmt_diff(d)) for e, d in row["diff"].items()))
            for row in rows) + "."

    lines += ["", "## Other checks (correctness only)", ""]
    if doubles:
        lines.append("- " + summary("`-double`", doubles))
    if multis:
        lines.append("- " + summary("two instances of one factory, computed alternately", multis))
    if vecs:
        lines.append("- " + summary("`-vec -lv 1`", vecs))
        for row in vecs:
            lines.append("  - %s, YDSP: %s" % (row["name"], row["trace"]["ydsp"] or "(no trace)"))
    bad = [r for r in results if "error" in r]
    if bad:
        lines += ["", "Not measured:", ""] + ["- **%s**: %s" % (r["name"], r["error"].splitlines()[0]) for r in bad]
    with open(os.path.join(HERE, "results.md"), "w") as f:
        f.write("\n".join(lines) + "\n")
    print("\nwrote results.md and results.json")
    diffs = [d for r in ok for e, d in r["diff"].items() if e not in EXPECTED_TO_DIFFER] + \
        [d for row in doubles + multis + vecs for e, d in row["diff"].items() if e not in EXPECTED_TO_DIFFER]
    if bad or not all(identical(d) for d in diffs):
        sys.exit(1)


if __name__ == "__main__":
    main()
