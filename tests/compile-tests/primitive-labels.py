#!/usr/bin/env python3
"""Regression test (issue #323): a string named after a math primitive.

An extended primitive (exp, cos, pow...) is attached to the ordinary symbol
of its name, which every string leaf of the same name shares. A signal pass
that recognized the primitive by its symbol alone took the label of
nentry("exp", ...) for an application of exp, and the compiler crashed
(an assertion, then a segmentation fault). Only a node with branches is an
application (sigXtendedData, signals.hh).

The test compiles, for each of the 22 primitives, its name as the label of a
slider, a nentry (in a group of the same name, with metadata), a button and
a bargraph, and also as a group, a soundfile, a declared value, an ffunction
include and an fvariable file name. Each compilation must succeed and the
generated C++ must carry every label.
"""

import argparse
from pathlib import Path
import subprocess
import sys
import tempfile

PRIMITIVES = ["abs", "acos", "asin", "atan", "atan2", "ceil", "cos", "exp", "exp10",
              "floor", "fmod", "log", "log10", "max", "min", "pow", "remainder", "rint",
              "round", "sin", "sqrt", "tan"]


def widgets_program():
    items = []
    for n in PRIMITIVES:
        items.append(f'(hslider("h:a/{n}", 0.5, 0, 1, 0.01) : exp), '
                     f'nentry("v:{n}/[1]{n}[unit:{n}]", 0.5, 0, 1, 0.01), '
                     f'(button("h:b/{n}") : hbargraph("h:c/{n}", 0, 1))')
    return "process = " + ",\n  ".join(items) + ";\n"


OTHERS = """\
declare name "exp";
f = ffunction(float cosf(float), <math.h>, "");
g = ffunction(float myfun(float), "exp", "pow");
v = fvariable(float tanv, "atan");
process = hgroup("exp", vgroup("cos", (hslider("[1]sin", 0.5, 0, 1, 0.01) : f),
                                      (nentry("pow", 0.1, 0, 1, 0.1) : g))),
          v, ((0,0) : soundfile("log", 1) : !, !, _), tgroup("max", button("min"));
"""

# (name, program, labels that the generated C++ must carry)
CASES = [
    ("widgets", widgets_program(), PRIMITIVES),
    ("groups, soundfile, declare, ffunction", OTHERS,
     ["exp", "cos", "sin", "pow", "log", "max", "min"]),
]

OPTIONS = [[], ["-lang", "c"], ["-lang", "ocpp"], ["-vec"], ["-double"], ["-os"],
           ["-svg"], ["-json"]]


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    args = parser.parse_args()
    faust = args.faust.resolve()

    failures = 0
    with tempfile.TemporaryDirectory(prefix="faust-prim-labels-") as temp:
        work = Path(temp)
        for i, (name, program, labels) in enumerate(CASES):
            dsp = work / f"t{i}.dsp"
            dsp.write_text(program)
            for options in OPTIONS:
                out = work / f"t{i}.out"
                r = subprocess.run([str(faust), *options, dsp.name, "-o", out.name],
                                   cwd=work, capture_output=True, text=True)
                tag = f"[{name}] {' '.join(options) or 'default'}"
                if r.returncode != 0:
                    failures += 1
                    print(f"FAIL {tag}: exit {r.returncode}\n    {r.stderr.strip()[:300]}")
                    continue
                if not options:
                    code = out.read_text(encoding="utf-8")
                    missing = [n for n in labels if f'"{n}"' not in code]
                    if missing:
                        failures += 1
                        print(f"FAIL {tag}: labels missing from the C++: {missing}")
                        continue
                print(f"PASS {tag}")
    return 1 if failures else 0


if __name__ == "__main__":
    sys.exit(main())
