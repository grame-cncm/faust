#!/usr/bin/env python3
"""Regression test: faust finds its own directory in PATH without which(1).

When called by a bare name, faust looks itself up in PATH to locate the
libraries and architecture files next to its binary. It used to run
`which faust` through a shell, and the deprecated which(1) of Debian
bookworm then printed a warning on stderr at every invocation (issue #676).

The test calls faust as `faust`, through a symbolic link, with a `which`
that fails loudly first in PATH, then a directory and a non-executable file
named `faust`, which the lookup must skip. faust must print nothing on
stderr, and `--libdir` must be the lib directory next to the real binary.
The other runs find the link through an empty PATH entry, which stands for
the current directory, and through a relative one-letter entry, which a
"./" prefix test used to strip from the path.
"""

import argparse
import os
from pathlib import Path
import subprocess
import sys
import tempfile


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    args = parser.parse_args()

    faust = args.faust.resolve()
    expected = str(faust.parent.parent / "lib")
    failures = 0
    with tempfile.TemporaryDirectory(prefix="faust-exe-path-") as temp:
        work = Path(temp)
        noisy, as_dir, as_file, link_dir = (work / d for d in ("noisy", "dir", "file", "b"))
        for d in (noisy, as_dir, as_file, link_dir):
            d.mkdir()
        (noisy / "which").write_text("#!/bin/sh\necho 'which: deprecated' >&2\nexit 1\n")
        (noisy / "which").chmod(0o755)
        (as_dir / "faust").mkdir()
        (as_file / "faust").write_text("")
        (link_dir / "faust").symlink_to(faust)

        prefix = os.pathsep.join(str(d) for d in (noisy, as_dir, as_file))
        cases = [
            ("PATH entry", prefix + os.pathsep + str(link_dir), link_dir),
            ("empty PATH entry", prefix + os.pathsep, link_dir),
            ("relative PATH entry", prefix + os.pathsep + link_dir.name, work),
        ]
        for name, path, cwd in cases:
            env = dict(os.environ, PATH=path)
            r = subprocess.run(["faust", "--libdir"], executable=str(link_dir / "faust"),
                               cwd=cwd, env=env, capture_output=True, text=True)
            libdir = r.stdout.strip()
            if r.returncode != 0 or r.stderr or libdir != expected:
                print(f"FAIL [{name}]: exit {r.returncode}, --libdir {libdir!r} "
                      f"(expected {expected!r}), stderr {r.stderr.strip()!r}")
                failures += 1
            else:
                print(f"PASS [{name}]: --libdir {libdir}")

    return 1 if failures else 0


if __name__ == "__main__":
    sys.exit(main())
