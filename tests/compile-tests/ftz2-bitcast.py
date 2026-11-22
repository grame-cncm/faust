#!/usr/bin/env python3
"""Regression test: -ftz 2 generates compiling C and C++ code.

-ftz 2 bitcasts a recursive real value to an integer to test its exponent.
The cpp backend printed *reinterpret_cast<int*>(&EXPR) and the c backend a
malformed *((int*(&EXPR), neither of which compiles when EXPR is an rvalue
such as -fTemp0 (and both break strict aliasing). The bitcast now goes through
a memcpy based faust_bitcast_f/_d helper defined next to the faust_wrap_* ones.

Each DSP is compiled with cpp and c, in single and double precision, and the
result (generated with the minimal architecture) is syntax checked with the C/C++ compiler.
"""

import argparse
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

# an rvalue operand (-fTemp0) and a plain one
DSPS = ["process = (_*0.5-0.5)~_;", "process = (_*0.5+0.1)~_;"]
CC = {"cpp": ["c++", "-x", "c++"], "c": ["cc", "-x", "c"]}
ARCH = {"cpp": "minimal.cpp", "c": "minimal.c"}


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    parser.add_argument("--langs", nargs="+", default=["cpp", "c"])
    args = parser.parse_args()

    failures = 0
    with tempfile.TemporaryDirectory(prefix="faust-ftz2-bitcast-") as temp:
        work = Path(temp)
        for i, dsp in enumerate(DSPS):
            dsp_file = work / f"t{i}.dsp"
            dsp_file.write_text(dsp)
            for lang in args.langs:
                for prec in ("-single", "-double"):
                    tag = f"{lang} {prec} dsp{i}"
                    out = work / f"t{i}{prec}.{lang}"
                    r = subprocess.run([str(args.faust), "-lang", lang, prec, "-ftz", "2",
                                        "-a", str(repo / "architecture" / ARCH[lang]),
                                        str(dsp_file), "-o", str(out)],
                                       capture_output=True, text=True)
                    if r.returncode != 0:
                        print(f"FAIL [{tag}]: faust failed: {r.stderr.strip()}")
                        failures += 1
                        continue
                    cmd = CC[lang]
                    if shutil.which(cmd[0]) is None:
                        print(f"skip [{tag}]: no {cmd[0]}")
                        continue
                    r = subprocess.run(cmd + ["-fsyntax-only", "-I", str(repo / "architecture"), str(out)],
                                       capture_output=True, text=True)
                    if r.returncode != 0 or "reinterpret_cast" in out.read_text():
                        print(f"FAIL [{tag}]: {r.stderr.strip()}")
                        failures += 1
                    else:
                        print(f"ok   [{tag}]")
    if failures:
        sys.exit(1)


if __name__ == "__main__":
    main()
