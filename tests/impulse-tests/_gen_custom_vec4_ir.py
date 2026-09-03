#!/usr/bin/env python3
"""Experimental C++ impulse generation, with the Mojo/_bench vector flags.

From tests/impulse-tests: python3 _gen_custom_vec4_ir.py
Optionally select DSP names: python3 _gen_custom_vec4_ir.py osc bells

Internal precision: double. Architecture precision: float.
Uses the existing impulsearch.cpp architecture. Does not compare results.
"""

import os
from pathlib import Path
import shlex
import signal
import subprocess
import sys


TESTS = Path(__file__).resolve().parent
ROOT = TESTS.parents[1]
FAUST = [str(ROOT / "build/bin/faust")]
CXX = shlex.split(os.environ.get("CXX", "clang++"))


def run(command, log, timeout, stdout=None):
    with log.open("w") as errors:
        errors.write(shlex.join(command) + "\n\n")
        errors.flush()
        output = stdout.open("w") if stdout else errors
        try:
            process = subprocess.Popen(
                command, cwd=TESTS, stdout=output, stderr=errors,
                start_new_session=True,
            )
            try:
                return process.wait(timeout=timeout) == 0
            except (subprocess.TimeoutExpired, KeyboardInterrupt) as exc:
                os.killpg(process.pid, signal.SIGKILL)
                process.wait()
                if isinstance(exc, KeyboardInterrupt):
                    raise
                errors.write(f"\nTIMEOUT after {timeout} seconds\n")
                return False
        except OSError as exc:
            errors.write(str(exc) + "\n")
            return False
        finally:
            if stdout:
                output.close()


def main():
    sources = sorted((TESTS / "dsp").glob("*.dsp"))
    if sys.argv[1:]:
        names = {Path(name).stem for name in sys.argv[1:]}
        missing = names - {source.stem for source in sources}
        if missing:
            sys.exit("Unknown DSP names: " + ", ".join(sorted(missing)))
        sources = [source for source in sources if source.stem in names]
    if not sources:
        sys.exit("No DSP files found in " + str(TESTS / "dsp"))
    if not Path(FAUST[0]).is_file():
        sys.exit("Build Faust first: missing " + FAUST[0])

    output = TESTS / "reference/_custom"
    build = output / "build"
    build.mkdir(parents=True, exist_ok=True)
    print(f"Results: {output}", flush=True)
    failed = []
    for source in sources:
        name = source.stem
        generated = build / f"{name}_vec4.cpp"
        binary = build / f"{name}_vec4.bin"
        response = output / f"{name}_vec4.ir"
        partial = build / f"{name}_vec4.ir.partial"
        generate = [*FAUST, "-lang", "cpp", "-double", "-vec", "-vs", "4", "-dfs", "-mcd", "4",
                    "-I", str(TESTS / "dsp"), "-I", str(ROOT / "libraries"),
                    "-i", "-A", str(ROOT / "architecture"),
                    "-a", str(TESTS / "archs/impulsearch.cpp"),
                    str(source), "-o", str(generated)]
        compile_cpp = [*CXX, "-std=gnu++23", "-O3", "-fwrapv", "-pthread",
                       "-DFAUSTFLOAT=float", "-I", str(ROOT / "architecture"),
                       "-I", str(TESTS / "archs"), "-I", "/usr/local/include/ap_fixed",
                       str(generated), "-o", str(binary)]
        for stage, command, timeout, stdout in (
            ("generate", generate, 120, None),
            ("build", compile_cpp, 600, None),
            ("run", [str(binary), "-n", "60000"], 120, partial),
        ):
            if not run(command, build / f"{name}_vec4.{stage}.log", timeout, stdout):
                failed.append(f"{name}: {stage}")
                print(f"{name}: FAILED ({stage})", flush=True)
                break
        else:
            partial.rename(response)
            print(f"{name}: OK", flush=True)
        binary.unlink(missing_ok=True)

    print(f"\nGenerated {len(sources) - len(failed)}/{len(sources)} responses in {output}")
    return int(bool(failed))


if __name__ == "__main__":
    sys.exit(main())
