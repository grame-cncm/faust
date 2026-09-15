"""Helpers for tests that compile selected methods from the faustgen sources."""

import os
from pathlib import Path
import shlex
import subprocess


ROOT = Path(__file__).resolve().parents[1]
FACTORY_SOURCE = ROOT / "src/faustgen_factory.cpp"
FACTORY_HEADER = ROOT / "src/faustgen_factory.h"
FAUSTGEN_SOURCE = ROOT / "src/faustgen~.cpp"


def definition(source, signature):
    """Return one complete C++ function definition containing *signature*."""
    start = source.index(signature)
    opening = source.index("{", start)
    depth = 1
    closing = opening + 1
    while depth:
        if closing == len(source):
            raise ValueError(f"unterminated definition: {signature}")
        depth += (source[closing] == "{") - (source[closing] == "}")
        closing += 1
    return source[start:closing]


def definitions(source, signatures):
    return "\n\n".join(definition(source, signature) for signature in signatures)


def compile_and_run(cpp, temporary, name="test", flags=()):
    """Compile and execute a self-contained C++ regression harness."""
    temporary = Path(temporary)
    source = temporary / f"{name}.cpp"
    binary = temporary / name
    source.write_text(cpp)

    # Some developer shells put an empty element in CPLUS_INCLUDE_PATH. That
    # makes Clang search the caller's current directory and can make the Faust
    # repository's ./version script shadow libc++'s <version> header.
    env = os.environ.copy()
    for variable in ("CPATH", "CPLUS_INCLUDE_PATH", "C_INCLUDE_PATH"):
        if variable in env:
            env[variable] = os.pathsep.join(
                entry for entry in env[variable].split(os.pathsep) if entry
            )

    environment_flags = shlex.split(env.get("FAUSTGEN_TEST_CXXFLAGS", ""))
    subprocess.run(
        ["c++", "-std=c++11", *environment_flags, *flags, str(source), "-o", str(binary)],
        cwd=temporary,
        env=env,
        check=True,
    )
    subprocess.run([str(binary)], cwd=temporary, env=env, check=True)
