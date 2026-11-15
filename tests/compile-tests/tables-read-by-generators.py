#!/usr/bin/env python3
"""The tables of the program : a table whose generator reads another table (LES-TABLES-DU-PROGRAMME).

A constant table (rdtable) belongs to the program, not to the generator that reads it : it is
declared once, and filled once by classInit, after every table its generator reads. A read-write
table (rwtable) read inside a generator is a member of the generator object.

1. The values : each program is compiled in cpp, ocpp and c, single and double, scalar and -vec,
   and its first ten samples are the expected ones. A table never filled reads 0, a table
   filled after its reader gives the values of an empty table.
2. Once : in the programs where t1 is read at two levels, the code declares one array per table.
3. The refusals : -it and -mem cannot place such a table, and say so instead of emitting code.

The comparison must first reject a wrong expected value.
"""

import argparse
from pathlib import Path
import re
import subprocess
import sys
import tempfile

RAMP = "ramp = (+(1) ~ _) - 1;\n"

# name : (program, expected samples, number of constant tables, each a static array)
CASES = {
    "one": ("t1(i) = rdtable(8, ramp * 10, i);\nprocess = t1(ramp & 7) + 1;",
            "1 11 21 31 41 51 61 71 1 11", 1),
    "dep": ("t1(i) = rdtable(8, ramp * 10, i);\nt2(i) = rdtable(8, t1(ramp) + 1, i);\n"
            "process = t2(ramp & 7);",
            "1 11 21 31 41 51 61 71 1 11", 2),
    "chain": ("t1(i) = rdtable(4, ramp + 1, i);\nt2(i) = rdtable(4, t1(ramp) * t1(ramp), i);\n"
              "t3(i) = rdtable(4, t2(ramp) + t1(3 - ramp), i);\nprocess = t3(ramp & 3);",
              "5 7 11 17 5 7 11 17 5 7", 3),
    "shared": ("t1(i) = rdtable(8, ramp * 10, i);\nt2(i) = rdtable(8, t1(ramp) + 1, i);\n"
               "process = t2(ramp & 7) + t1(ramp & 7);",
               "1 21 41 61 81 101 121 141 1 21", 2),
    "twogen": ("t1(i) = rdtable(8, ramp * 10, i);\nt2(i) = rdtable(8, t1(ramp) + t1(7 - ramp), i);\n"
               "t3(i) = rdtable(8, t1(ramp) * 2, i);\nprocess = t2(ramp & 7) + t3(ramp & 7);",
               "70 90 110 130 150 170 190 210 70 90", 3),
    "rwgen": ("t1(i) = rdtable(8, ramp * 10, i);\nprocess = rwtable(8, t1(ramp) + 1, 0, 0, ramp & 7);",
              "0 11 21 31 41 51 61 71 0 11", 1),
    "genrw": ("t2(i) = rdtable(8, rwtable(8, ramp * 10, 0, 0, ramp) + 1, i);\nprocess = t2(ramp & 7);",
              "1 11 21 31 41 51 61 71 1 11", 1),
    "mixgen": ("process = rwtable(8, ramp * 10, 0, 0, ramp & 7) + rdtable(8, ramp * 10, ramp & 7);",
               "0 20 40 60 80 100 120 140 0 20", 1),
}

RUNNER_CPP = r"""
#include <cstdio>
#include <faust/dsp/dsp.h>
#include <faust/gui/meta.h>
#include <faust/gui/UI.h>
#include "generated.h"
int main()
{
    mydsp d;
    d.init(48000);
    FAUSTFLOAT out[10];
    FAUSTFLOAT* outputs[1] = {out};
    d.compute(10, nullptr, outputs);
    for (int i = 0; i < 10; i++) printf("%g ", double(out[i]));
    printf("\n");
    return 0;
}
"""

RUNNER_C = r"""
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "faust/gui/CInterface.h"
#include "generated.h"
int main()
{
    mydsp* d = newmydsp();
    initmydsp(d, 48000);
    FAUSTFLOAT out[10];
    FAUSTFLOAT* outputs[1] = {out};
    computemydsp(d, 10, NULL, outputs);
    for (int i = 0; i < 10; i++) printf("%g ", (double)out[i]);
    printf("\n");
    return 0;
}
"""

# a static array of the generated code : one per table
ARRAY = re.compile(r"^\s*static\s+(?:int|float|double)\s+itbl\w*\s*\[\d+\]", re.M)


def faust(args, dsp, opts, out):
    cmd = [str(args.faust)] + opts + ["-cn", "mydsp", str(dsp), "-o", str(out)]
    r = subprocess.run(cmd, capture_output=True, text=True)
    return r.returncode, r.stderr.strip()


def build_and_run(args, work, lang, prec):
    fl = "float" if prec == "single" else "double"
    if lang == "c":
        (work / "runner.c").write_text(RUNNER_C)
        cmd = [args.cc, "-std=c11", f"-DFAUSTFLOAT={fl}", "-I", str(args.arch),
               str(work / "runner.c"), "-o", str(work / "runner"), "-lm"]
    else:
        (work / "runner.cpp").write_text(RUNNER_CPP)
        cmd = [args.cxx, "-std=c++17", "-ffp-contract=off", f"-DFAUSTFLOAT={fl}", "-I", str(args.arch),
               str(work / "runner.cpp"), "-o", str(work / "runner")]
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0:
        first = next((l for l in r.stderr.splitlines() if "error" in l), r.stderr.strip())
        return None, f"build : {first}"
    out = subprocess.run([str(work / "runner")], capture_output=True, text=True)
    return " ".join(out.stdout.split()), None


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    parser.add_argument("--cxx", default="g++")
    parser.add_argument("--cc", default="cc")
    parser.add_argument("--arch", type=Path, default=repo / "architecture")
    args, _ = parser.parse_known_args()
    args.faust = args.faust.resolve()
    fails = []
    n = 0
    with tempfile.TemporaryDirectory(prefix="faust-tables-") as temp:
        work = Path(temp)

        # The comparison rejects a wrong expected value
        src, want, _ = CASES["dep"]
        (work / "dep.dsp").write_text(RAMP + src)
        code, err = faust(args, work / "dep.dsp", ["-lang", "cpp"], work / "generated.h")
        got, err = build_and_run(args, work, "cpp", "single") if code == 0 else (None, err)
        if got is None or got == want.replace("11", "12"):
            print(f"NOT A VERDICT : the comparison does not reject a wrong value ({err or got})")
            sys.exit(2)

        for name, (src, want, tables) in CASES.items():
            dsp = work / f"{name}.dsp"
            dsp.write_text(RAMP + src)
            for lang in ("cpp", "ocpp", "c"):
                for prec in ("single", "double"):
                    for vec in ([], ["-vec"]):
                        opts = ["-lang", lang, "-" + prec] + vec
                        case = f"{name:7s} {lang:4s} {prec:6s} {' '.join(vec):4s}"
                        n += 1
                        code, err = faust(args, dsp, opts, work / "generated.h")
                        if code != 0:
                            got = f"faust : {err}"
                        else:
                            got, err = build_and_run(args, work, lang, prec)
                            got = got if err is None else err
                        ok = got == want
                        print(f"{'ok  ' if ok else 'FAIL'} {case} : {got}")
                        if not ok:
                            fails.append(case)
                            continue
                        arrays = len(ARRAY.findall((work / "generated.h").read_text()))
                        if arrays != tables:
                            print(f"FAIL {case} : {arrays} static arrays for {tables} constant tables")
                            fails.append(case + " (arrays)")

        for opt, name in (("-it", "dep"), ("-mem", "genrw")):
            n += 1
            code, err = faust(args, work / f"{name}.dsp", ["-lang", "cpp", opt], work / "refused.h")
            ok = code != 0 and "not supported with " + opt in err
            print(f"{'ok  ' if ok else 'FAIL'} {name} cpp {opt} refused : {err or 'compiled'}")
            if not ok:
                fails.append(f"{name} {opt}")

    print(f"{n} cases compared")
    if fails:
        print(f"{len(fails)} failures : {', '.join(fails)}")
        sys.exit(1)
    print("Every table is filled once, before the generators that read it.")


if __name__ == "__main__":
    main()
