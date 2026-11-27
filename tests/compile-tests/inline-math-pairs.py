#!/usr/bin/env python3
"""The sine and the cosine of one argument keep their calls (LES-FONCTIONS-MATHEMATIQUES-EN-LIGNE).

Under -im (the default), in single precision, the cpp, ocpp and c generators write the sine, the
cosine and the hyperbolic tangent without a call of the libm (faustsin17f, faustcos17f,
fausttanhf) when the interval of the argument allows it. The sine and the cosine of the same
argument are the exception : both keep their calls, which the C++ compiler joins in one call
that reduces the argument once for the two values (sincosf) ; two inline versions would reduce
it twice.

The code only is read : for each program, the calls of the inline versions and those of the libm
are counted in the generated text, the definitions of the versions left aside.

1. A pair, at the sample rate, at the rate of the controls, in one output or in two : no
   inline version, one call of the sine and one of the cosine.
2. A sine alone, a cosine alone, a sine and a cosine of two arguments : the inline versions, no
   call.
3. A pair next to a sine and a cosine alone : the pair keeps its calls, the others are inline ;
   the hyperbolic tangent of the argument of a pair is inline.
4. The generator of a table has a loop of its own, where no call of the program can be joined
   with one of its calls : the sine of one table and the cosine of another, the sine and the
   cosine in one generator, a sine of the program and the cosine of a table are inline. A node
   has one version : the sine of a pair of the program, when a generator computes it too, keeps
   its call in the generator.
5. -noim and the double precision : every call stays.
6. -vec, with the loop variant that writes each loop once (-lv 1) : the counts of the scalar
   code.
"""

import argparse
from pathlib import Path
import re
import subprocess
import sys
import tempfile

PHASE = r"ph(f) = (+(f) : \(x).(x - floor(x))) ~ _;" "\n"
SLIDERS = ('a = hslider("a", 0.1, -3, 3, 0.01);\n'
           'b = hslider("b", 0.2, -3, 3, 0.01);\n')
# the argument of the generators, and the index that reads the tables
TABLE = ("tr = 6.2831855 * float(ba.time % 1024) / 1024;\n"
         'ti = int(hslider("i", 0, 0, 1023, 1));\n')

# name, program, (inline sines, inline cosines, inline tanh, calls of the sine, calls of the cosine)
PROGRAMS = [
    ("pair at the sample rate", "process = sin(ph(a)) * cos(ph(a));\n", (0, 0, 0, 1, 1)),
    ("pair in two outputs", "process = sin(ph(a)), cos(ph(a));\n", (0, 0, 0, 1, 1)),
    ("pair at the rate of the controls", "process = _ * sin(a), _ * cos(a);\n", (0, 0, 0, 1, 1)),
    ("sine alone", "process = sin(ph(a));\n", (1, 0, 0, 0, 0)),
    ("cosine alone", "process = cos(ph(a));\n", (0, 1, 0, 0, 0)),
    ("two arguments", "process = sin(ph(a)), cos(ph(b));\n", (1, 1, 0, 0, 0)),
    ("pair and others", "process = sin(ph(a)) * cos(ph(a)), sin(ph(b)), cos(2 * ph(b));\n", (1, 1, 0, 1, 1)),
    ("pair and tanh", "process = sin(ph(a)), cos(ph(a)), ma.tanh(ph(a));\n", (0, 0, 1, 1, 1)),
    ("two tables", "process = rdtable(1024, sin(tr), ti), rdtable(1024, cos(tr), ti);\n", (1, 1, 0, 0, 0)),
    ("one generator", "process = rdtable(1024, sin(tr) * cos(tr), ti);\n", (1, 1, 0, 0, 0)),
    ("sine and table of the cosine", "process = sin(ph(0.01)) * rdtable(1024, cos(ph(0.01)), ti);\n", (1, 1, 0, 0, 0)),
    ("pair and table of its sine", "process = sin(tr) * cos(tr) + rdtable(1024, sin(tr), ti);\n", (0, 0, 0, 2, 1)),
]

COUNTS = [r"\bfaustsin17f\(", r"\bfaustcos17f\(", r"\bfausttanhf\(", r"\bsinf?\(", r"\bcosf?\(", r"\btanhf?\("]


def counts(text):
    # the definitions of the versions, and the calls of the libm they keep on the other targets, aside
    body = "\n".join(l for l in text.split("\n") if "static inline" not in l)
    return tuple(len(re.findall(c, body)) for c in COUNTS)


def faust(args, dsp, lang, options):
    cmd = [str(args.faust), "-lang", lang] + options + [str(dsp)]
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0:
        raise RuntimeError(f"faust {lang} {' '.join(options)} {dsp.name} : {r.stderr.strip()}")
    return r.stdout


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    args, _ = parser.parse_known_args()
    args.faust = args.faust.resolve()
    fails = []
    n = 0
    with tempfile.TemporaryDirectory(prefix="faust-inline-math-pairs-") as temp:
        dsp = Path(temp) / "pairs.dsp"
        for name, source, (isin, icos, itanh, csin, ccos) in PROGRAMS:
            dsp.write_text('import("stdfaust.lib");\n' + SLIDERS + PHASE + TABLE + source)
            nsin, ncos, ntanh = isin + csin, icos + ccos, itanh
            for lang in ("cpp", "ocpp", "c"):
                cases = [
                    ("-single", ["-single"], (isin, icos, itanh, csin, ccos, 0)),
                    ("-single -vec -lv 1", ["-single", "-vec", "-lv", "1"], (isin, icos, itanh, csin, ccos, 0)),
                    ("-single -noim", ["-single", "-noim"], (0, 0, 0, nsin, ncos, ntanh)),
                    ("-double", ["-double"], (0, 0, 0, nsin, ncos, ntanh)),
                ]
                for label, options, expected in cases:
                    n += 1
                    got = counts(faust(args, dsp, lang, options))
                    ok = got == expected
                    print(f"{'ok  ' if ok else 'FAIL'} {lang:4s} {label:18s} {name:32s} inline sin, cos, tanh and"
                          f" calls of sin, cos, tanh : {got}" + ("" if ok else f", expected {expected}"))
                    if not ok:
                        fails.append(f"{lang} {label} {name}")
    if fails:
        print(f"{len(fails)} failures out of {n} : {', '.join(fails)}")
        sys.exit(1)
    print(f"The sine and the cosine of one argument keep their calls, the others are inline : {n} codes read.")


if __name__ == "__main__":
    main()
