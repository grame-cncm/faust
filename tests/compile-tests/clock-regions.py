#!/usr/bin/env python3
"""Regression test: the front end of the clock regions.

ondemand(P), upsampling(P) and downsampling(P) compute P on a clock derived
from the clock of their context. If P has n inputs and m outputs, the region
has 1+n inputs and m outputs: its first input is the rate of the derived
clock. The three words are reserved.

The front end parses the regions, types them, prints them (in the error
messages and with -e) and draws them. The signals have no clocks yet: the
propagation refuses a region with a message that names it. The test checks
each of these, and that its own checks reject a program without a region.
"""

import argparse
from pathlib import Path
import re
import subprocess
import sys
import tempfile

REGIONS = ("ondemand", "upsampling", "downsampling")
NOT_YET = "is not supported yet"
LABEL = re.compile(r'<text [^>]*>([^<]*)</text>')


def run(faust, options, program, cwd):
    (cwd / "t.dsp").write_text(program)
    return subprocess.run([str(faust), *options, "t.dsp"], cwd=cwd, capture_output=True, text=True)


def labels(cwd):
    svg = cwd / "t-svg" / "process.svg"
    return set(LABEL.findall(svg.read_text(encoding="utf-8"))) if svg.is_file() else set()


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    faust = parser.parse_args().faust.resolve()

    failures = 0

    def verdict(name, errors, detail):
        nonlocal failures
        if errors:
            failures += 1
            print(f"FAIL [{name}]")
            for e in errors:
                print(f"    {e}")
        else:
            print(f"PASS [{name}]: {detail}")

    with tempfile.TemporaryDirectory(prefix="faust-clock-regions-") as temp:
        work = Path(temp)

        def fresh(tag):
            cwd = work / tag
            cwd.mkdir()
            return cwd

        for region in REGIONS:
            # P = + has 2 inputs and 1 output : the region has 3 inputs and 1 output
            good = run(faust, [], f"process = (_,_,_) : {region}(+) : _;", fresh(f"{region}-good"))
            bad = run(faust, [], f"process = (_,_) : {region}(+);", fresh(f"{region}-bad"))
            errors = []
            if good.returncode == 0 or f"'{region}' {NOT_YET}" not in good.stderr:
                errors.append(f"3 inputs, 1 output : expected the refusal of the propagation, got "
                              f"{good.stderr.strip()[:120]!r}")
            if "outputs [2] of A must be equal to the number of inputs [3] of B" not in bad.stderr:
                errors.append(f"2 signals into the region : expected 3 inputs, got {bad.stderr.strip()[:160]!r}")
            if f"B = {region}(+)" not in bad.stderr:
                errors.append(f"the error does not print the region as {region}(+)")
            verdict(f"{region} : type", errors, "1+n inputs, m outputs, printed by its keyword")

            reserved = run(faust, [], f"{region} = 3;\nprocess = {region};", fresh(f"{region}-word"))
            verdict(f"{region} : reserved word",
                    [] if "syntax error" in reserved.stderr else ["a definition of the word is accepted"],
                    "a definition of the word is a syntax error")

        program = "process = ondemand(ondemand(_)), upsampling(+ ~ *(0.5)), downsampling(mem);"
        cwd = fresh("svg")
        run(faust, ["-svg"], program, cwd)
        expected = {"ondemand", "upsampling", "downsampling", "run", "rate"}
        found = labels(cwd)
        verdict("-svg", [f"labels missing from process.svg : {sorted(expected - found)}"]
                if expected - found else [], f"the frames are labelled {sorted(expected)}")

        cwd = fresh("expand")
        run(faust, ["-e", "-o", "e.dsp"], program, cwd)
        text = (cwd / "e.dsp").read_text() if (cwd / "e.dsp").is_file() else ""
        missing = [r for r in REGIONS if f"{r}(" not in text]
        verdict("-e", [f"not printed in the expanded program : {missing}"] if missing else [],
                "the three regions are printed in the expanded program")

        # the checks above must fail on a program without a region
        cwd = fresh("self")
        plain = run(faust, ["-svg"], "process = (_,_,_) : (+,_ : +) : _;", cwd)
        blind = []
        if plain.returncode != 0 or NOT_YET in plain.stderr:
            blind.append("a program without a region is refused")
        if labels(cwd) & {"ondemand", "upsampling", "downsampling", "run", "rate"}:
            blind.append("a drawing without a region shows the labels of one")
        verdict("self check", blind, "a program without a region compiles, and its drawing has no frame")

    return 1 if failures else 0


if __name__ == "__main__":
    sys.exit(main())
