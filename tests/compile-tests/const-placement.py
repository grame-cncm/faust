#!/usr/bin/env python3
"""Regression test: init-time constants only become DSP fields when compute reads them.

A shared constant (fConstN / iConstN) used only to compute other constants is
a local variable of instanceConstants. It is a field of the DSP structure only
when the sample loop (or a control-rate computation) reads it. Every constant
used to be a field, which wastes memory on small targets.

For the cpp and c backends, in scalar and vector modes, this checks that:
  - the first program has locals in instanceConstants, and fewer fields than
    constants (the optimisation happens);
  - no local is mentioned outside the function declaring it (the stack
    variable would be undeclared there);
  - the second program, where a shared constant is read in a recursive loop,
    keeps that constant as a field.
"""

import argparse
from pathlib import Path
import re
import subprocess
import sys
import tempfile

# fConst0 (sample rate) and the products of the table lookup are init only
INIT_ONLY = "import(\"stdfaust.lib\");\nprocess = os.osc(1000) : fi.lowpass(2, 2000);\n"

# k is shared (twice) and read by the recursion: it must stay a field
IN_COMPUTE = """import("stdfaust.lib");
k = exp(0.0 - 1000.0 / ma.SR);
process = _ <: (+ ~ *(k)), (_ * k * k);
"""

NAME = re.compile(r"\b[fi]Const\d+\b")
LOCAL = re.compile(r"^\s+(?:float|double|int)\s+([fi]Const\d+)\s*=")
FIELD = re.compile(r"^\s+(?:float|double|int)\s+([fi]Const\d+);")


def function_spans(lines):
    """(first, last) line indexes of every top-level or class-level function."""
    spans, i = [], 0
    head = re.compile(r"^\s*(?:virtual\s+)?(?:static\s+)?[\w:<>*&\s]+\s+\w+\([^;]*\)\s*(?:override\s*)?\{\s*$")
    while i < len(lines):
        if head.match(lines[i]):
            depth, j = 0, i
            while j < len(lines):
                depth += lines[j].count("{") - lines[j].count("}")
                if depth == 0:
                    break
                j += 1
            spans.append((i, j))
            i = j
        i += 1
    return spans


def check(text, label):
    """Return (list of errors, number of locals, number of fields)."""
    lines = text.splitlines()
    spans = function_spans(lines)
    errors, locals_, fields = [], {}, set()
    for n, line in enumerate(lines):
        m = LOCAL.match(line)
        if m:
            locals_[m.group(1)] = n
        m = FIELD.match(line)
        if m:
            fields.add(m.group(1))
    for name, decl in locals_.items():
        span = next((s for s in spans if s[0] <= decl <= s[1]), None)
        if span is None:
            errors.append(f"{label}: cannot find the function declaring {name}")
            continue
        for n, line in enumerate(lines):
            if re.search(rf"\b{name}\b", line) and not span[0] <= n <= span[1]:
                errors.append(f"{label}: local {name} used outside its function, line {n + 1}")
                break
    return errors, len(locals_), len(fields)


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    parser.add_argument("--langs", nargs="+", default=["cpp", "c"])
    args = parser.parse_args()

    failures = 0
    with tempfile.TemporaryDirectory(prefix="faust-const-placement-") as temp:
        work = Path(temp)
        for name, dsp in (("init_only", INIT_ONLY), ("in_compute", IN_COMPUTE)):
            (work / f"{name}.dsp").write_text(dsp)
        for lang in args.langs:
            for mode in ([], ["-vec"], ["-vec", "-lv", "1"]):
                label = f"{lang}{' ' + ' '.join(mode) if mode else ''}"
                results = {}
                for name in ("init_only", "in_compute"):
                    out = work / f"{name}.{lang}"
                    r = subprocess.run([str(args.faust), "-lang", lang, "-I", str(repo / "libraries"),
                                        *mode, str(work / f"{name}.dsp"), "-o", str(out)],
                                       capture_output=True, text=True)
                    if r.returncode != 0:
                        print(f"FAIL [{label}] {name}: faust failed: {r.stderr.strip()}")
                        failures += 1
                        break
                    results[name] = check(out.read_text(), f"{label} {name}")
                else:
                    errors = results["init_only"][0] + results["in_compute"][0]
                    _, n_local, n_field = results["init_only"]
                    if n_local == 0 or n_field == 0:
                        errors.append(f"{label} init_only: {n_local} locals, {n_field} fields, "
                                      "expected both")
                    _, k_local, k_field = results["in_compute"]
                    if k_field == 0:
                        errors.append(f"{label} in_compute: the constant read by the "
                                      "recursion is not a field")
                    if errors:
                        failures += 1
                        print(f"FAIL [{label}]")
                        for e in errors:
                            print(f"    {e}")
                    else:
                        print(f"ok   [{label}] init_only: {n_local} locals, {n_field} fields; "
                              f"in_compute: {k_local} locals, {k_field} fields")
    if failures:
        sys.exit(1)


if __name__ == "__main__":
    main()
