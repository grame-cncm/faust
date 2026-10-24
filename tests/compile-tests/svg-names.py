#!/usr/bin/env python3
"""Regression test: a diagram never draws a definition name that is wrong.

Hash-consing makes two definitions with the same value share one tree:
with `gain1 = 0.4; gain2 = 0.4;` both are the same `0.4` box, the two
occurrences cannot be told apart, and `-svg` drew `gain1` around both
(issue #266). Such a box is now drawn without a name, while a name that
belongs to every occurrence (one definition used twice, an alias) is kept.

Each case compiles a program with -svg and counts the definition names
written in process.svg.
"""

import argparse
from pathlib import Path
import re
import subprocess
import sys
import tempfile

# (program, {name: number of times it must be drawn in process.svg})
CASES = [
    # issue #266: two definitions with the same value
    ("gain1 = 0.4; gain2 = 0.4; process = _ : gain1 * _ : gain2 * _;",
     {"gain1": 0, "gain2": 0}),
    ("gain1 = 0.4; gain2 = 0.4000001; process = _ : gain1 * _ : gain2 * _;",
     {"gain1": 1, "gain2": 1}),
    ("f1 = +(1); f2 = +(1); process = f1 : f2;",
     {"f1": 0, "f2": 0}),
    # the same value reached through a simplification, or an environment
    ("g1 = 0.4; g2 = 0.2*2; process = _ : g1 * _ : g2 * _;",
     {"g1": 0, "g2": 0}),
    ("e = environment { a = 0.4; b = 0.4; }; process = _ * e.a : _ * e.b;",
     {"a": 0, "b": 0}),
    # one definition used twice keeps its name
    ("gain = 0.4; process = _ : gain * _ : gain * _;",
     {"gain": 2}),
    # an alias renames the value of its right-hand side...
    ("bar = +(1); foo = bar; process = foo : foo;",
     {"foo": 2, "bar": 0}),
    # ... unless the right-hand side is also used directly, in either order
    ("bar = +(1); foo = bar; process = foo : bar;",
     {"foo": 0, "bar": 0}),
    ("bar = +(1); foo = bar; process = bar : foo;",
     {"foo": 0, "bar": 0}),
    # an alias of one of two definitions with the same value
    ("gain1 = 0.4; gain2 = 0.4; foo = gain1; process = _ * foo;",
     {"foo": 1}),
    ("gain1 = 0.4; gain2 = 0.4; foo = gain1; process = _ * foo : _ * gain2;",
     {"foo": 0, "gain1": 0, "gain2": 0}),
    # two functions with the same body: the name of an application may be
    # wrong (v2 applied to b is not v1(b)), the name of a definition that
    # contains it is not
    ("v1(x) = x : +(1); v2(x) = x : +(1);"
     " process = v1(hslider(\"a\",0,0,1,0.1)), v2(hslider(\"b\",0,0,1,0.1));",
     {"v1(hslider(&quot;b&quot;, 0.0f, 0.0f, 1.0f, 0.1f))": 0}),
    ("v1(x) = x : +(1); v2(x) = x : +(1); c1 = v1(hslider(\"a\",0,0,1,0.1));"
     " c2 = v2(hslider(\"b\",0,0,1,0.1)); process = c1, c2;",
     {"c1": 1, "c2": 1}),
    # applications of one function to different arguments keep their names
    ("g(x) = x + 1; process = g(2), g(2), g(3);",
     {"g(2)": 2, "g(3)": 1}),
]

TEXT = re.compile(r"<text[^>]*>([^<]*)</text>")


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    args = parser.parse_args()
    faust = args.faust.resolve()  # faust runs in the temporary directory

    failures = 0
    with tempfile.TemporaryDirectory(prefix="faust-svg-names-") as temp:
        work = Path(temp)
        for i, (program, expected) in enumerate(CASES):
            dsp_file = work / f"case{i}.dsp"
            dsp_file.write_text(program + "\n")
            r = subprocess.run([str(faust), "-svg", dsp_file.name, "-o", "/dev/null"],
                               cwd=work, capture_output=True, text=True)
            svg = work / f"case{i}-svg" / "process.svg"
            if r.returncode != 0 or not svg.exists():
                print(f"FAIL [{i}] faust failed: {r.stderr.strip()}\n    {program}")
                failures += 1
                continue
            labels = TEXT.findall(svg.read_text())
            wrong = {name: labels.count(name) for name, count in expected.items()
                     if labels.count(name) != count}
            if wrong:
                failures += 1
                print(f"FAIL [{i}] {program}")
                for name, count in wrong.items():
                    print(f"    {name} drawn {count} times, expected {expected[name]}")
            else:
                print(f"ok   [{i}] {program}")
    print(f"{len(CASES) - failures} of {len(CASES)} cases passed")
    if failures:
        sys.exit(1)


if __name__ == "__main__":
    main()
