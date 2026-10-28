#!/usr/bin/env python3
"""Regression test: process.svg is the diagram of the program, whatever process it calls.

A definition named process inside the program (an environment's own process, called as
env.process) was written to process.svg too : drawn after the root, it replaced the
diagram of the program. The root alone is now drawn in process.svg ; an inner process has
its own file, process-<serial>.svg, linked from the root and linking back to it.

Two programs, drawn with -svg -f 1 (every named block in its own file) : one environment
whose process is scaled by 0.5, and two environments whose processes are chained.
process.svg must hold the root (the 0.5 of the first program), link to one file per inner
process, and each of them must exist and link back to process.svg.
"""

import argparse
from pathlib import Path
import re
import subprocess
import sys
import tempfile

PROGRAMS = {
    "one": ("""
synth = environment { process = +(0.01) ~ _ : sin; };
process = synth.process : *(0.5);
""", 1, "0.5"),
    "two": ("""
synth = environment { process = +(0.01) ~ _ : sin; };
echo = environment { process = _ <: _, @(100) :> *(0.3); };
process = synth.process : echo.process;
""", 2, None),
}


def links(svg):
    return sorted(set(re.findall(r'href="([^"]*)"', svg.read_text())))


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    args = parser.parse_args()
    faust = args.faust.resolve()

    failures = 0
    with tempfile.TemporaryDirectory(prefix="faust-svg-inner-process-") as temp:
        work = Path(temp)
        for name, (dsp, inner, text) in PROGRAMS.items():
            (work / f"{name}.dsp").write_text(dsp)
            r = subprocess.run([faust, "-svg", "-f", "1", f"{name}.dsp", "-o", "/dev/null"],
                               cwd=work, capture_output=True, text=True)
            root = work / f"{name}-svg" / "process.svg"
            if r.returncode != 0 or not root.exists():
                print(f"{name} : faust failed : {r.stderr.strip()}")
                failures += 1
                continue
            problems = []
            out = links(root)
            if len(out) != inner or not all(re.fullmatch(r"process-\d+\.svg", l) for l in out):
                problems.append(f"process.svg links to {out}, expected {inner} process-<serial>.svg")
            for l in out:
                f = root.parent / l
                if not f.exists():
                    problems.append(f"{l} does not exist")
                elif "process.svg" not in links(f):
                    problems.append(f"{l} does not link back to process.svg")
            if text and f">{text}" not in root.read_text():
                problems.append(f"process.svg does not show {text}")
            print(f"{name} : " + ("ok" if not problems else "; ".join(problems)))
            failures += bool(problems)
    print("all programs passed" if failures == 0 else f"{failures} program(s) FAILED")
    sys.exit(1 if failures else 0)


if __name__ == "__main__":
    main()
