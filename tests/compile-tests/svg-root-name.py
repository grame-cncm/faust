#!/usr/bin/env python3
"""Regression test: the root diagram of -svg is always process.svg.

The tools that open a drawing (faustgen~, faust2firefox, faust2svgviewer,
faust2feh, faust2mathdoc) open <name>-svg/process.svg. With -pn, the root
used to be named after its definition and the node's serial
(p2-2336.svg), and a definition named process drawn in its own file was
written to process.svg: the tools then opened an inner diagram, or
nothing. Without -pn, an inner process (a component whose process is
redefined) overwrote the root.

For each drawing the test checks that process.svg is the root (the only
file without a back link, titled with the name of the entry point), that
every other file is <name>-<serial>.svg with a back link to a file that
links to it, that every link names an existing file, that every file is
reachable from the root, and that a second run writes the same files. With
-ps, the files are the same, numbered by the PostScript device. With -mdoc,
the figure of a <diagram> that is not process includes the root file of its
directory. The checks must first reject corrupted drawings.
"""

import argparse
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tempfile

PROGRAM = """\
lp(c) = *(1-c) : + ~ *(c);
stage(c) = _ <: lp(c), (lp(c) : lp(c)) :> _;
process = stage(0.5) : stage(0.25);
p2 = _ <: stage(0.1), stage(0.2);
test = process <: _, (process : stage(0.3)) :> _;
one = stage(0.5);
"""

COMPONENT = """\
lp(c) = *(1-c) : + ~ *(c);
process = component("t.dsp") : component("t.dsp")[process = lp(0.3) : lp(0.4);];
"""

MDOC = PROGRAM + """\
<mdoc>
<diagram>process</diagram>
<diagram>one</diagram>
</mdoc>
"""

# (name, faust options, program, title of the root, an inner process expected)
CASES = [
    ("default", ["-svg"], "t.dsp", "process", False),
    ("default, folded", ["-svg", "-f", "1"], "t.dsp", "process", False),
    ("-pn p2", ["-svg", "-pn", "p2"], "t.dsp", "p2", False),
    ("-pn test using process, folded", ["-svg", "-f", "1", "-pn", "test"], "t.dsp", "test", True),
    ("component redefining process", ["-svg", "-f", "1"], "c.dsp", "process", True),
]

BACK_LINK = re.compile(r'<svg [^\n]*>\n<a xlink:href="([^"]*)">')
LINK = re.compile(r'xlink:href="([^"]*)"')
# the label of a decorated schema (SVGDev::label); the root's is drawn last
LABEL = re.compile(r'<text x="[^"]*" y="[^"]*" font-family="Arial" font-size="7">([^<]*)</text>')
INNER = re.compile(r"^[A-Za-z][A-Za-z0-9]*-[0-9]+\.svg$")


def check_drawing(directory, title, inner_process):
    """Return the list of the defects of the drawing in <directory>."""
    files = {p.name: p.read_text(encoding="utf-8") for p in directory.glob("*.svg")}
    errors = []
    if "process.svg" not in files:
        return [f"no process.svg among {len(files)} files"]
    back, forward = {}, {}
    for name, text in files.items():
        m = BACK_LINK.match(text.replace('<?xml version="1.0"?>\n', "", 1))
        back[name] = m.group(1) if m else None
        forward[name] = set(LINK.findall(text)) - {back[name]}
        for target in sorted(forward[name]):
            if target not in files:
                errors.append(f"{name} links to missing {target}")
    if back["process.svg"] is not None:
        errors.append(f"process.svg is not the root: back link to {back['process.svg']}")
    labels = [label for label in LABEL.findall(files["process.svg"]) if label]
    if not labels or labels[-1] != title:
        errors.append(f"process.svg is titled {labels[-1:]}, expected {title!r}")
    for name in sorted(files):
        if name == "process.svg":
            continue
        if not INNER.match(name):
            errors.append(f"{name} is not <name>-<serial>.svg")
        parent = back[name]
        if parent is None:
            errors.append(f"{name} has no back link: a second root")
        elif parent not in files or name not in forward[parent]:
            errors.append(f"{name} has a back link to {parent}, which does not link to it")
    reached, todo = set(), ["process.svg"]
    while todo:
        name = todo.pop()
        if name in reached or name not in files:
            continue
        reached.add(name)
        todo.extend(forward[name])
    for name in sorted(set(files) - reached):
        errors.append(f"{name} is not reachable from process.svg")
    if inner_process and not any(re.match(r"^process-[0-9]+\.svg$", n) for n in files):
        errors.append("no inner process-<serial>.svg")
    return errors


def same_files(a, b):
    """Return the names of the files that differ between directories a and b."""
    names = {p.name for p in a.iterdir()} | {p.name for p in b.iterdir()}
    return sorted(n for n in names
                  if not ((a / n).is_file() and (b / n).is_file()
                          and (a / n).read_bytes() == (b / n).read_bytes()))


def run_faust(faust, options, program, cwd):
    r = subprocess.run([str(faust), *options, program], cwd=cwd,
                       capture_output=True, text=True)
    if r.returncode != 0:
        raise RuntimeError(f"faust {' '.join(options)} {program}: exit {r.returncode}\n{r.stderr}")


def draw(faust, options, program, work, tag):
    cwd = work / tag
    cwd.mkdir()
    (cwd / "t.dsp").write_text(PROGRAM)
    (cwd / "c.dsp").write_text(COMPONENT)
    (cwd / "m.dsp").write_text(MDOC)
    run_faust(faust, options, program, cwd)
    return cwd


def self_check(drawing, work):
    """The checks must reject a corrupted drawing: return the failures."""
    failures = []

    def corrupted(tag, change):
        copy = work / tag
        shutil.copytree(drawing, copy)
        change(copy)
        return copy

    def missing_link(d):
        p = d / "process.svg"
        text = p.read_text(encoding="utf-8")
        target = sorted(set(LINK.findall(text)))[0]
        p.write_text(text.replace(f'"{target}"', '"missing-1.svg"', 1), encoding="utf-8")

    def inner_as_root(d):
        inner = sorted(d.glob("process-*.svg"))[0]
        (d / "process.svg").rename(d / "test-1.svg")
        inner.rename(d / "process.svg")

    for tag, change in (("missing link", missing_link),
                        ("inner process as root", inner_as_root),
                        ("no process.svg", lambda d: (d / "process.svg").unlink())):
        errors = check_drawing(corrupted("self-" + tag.replace(" ", "-"), change), "test", True)
        if not errors:
            failures.append(f"the drawing check accepts a drawing with {tag}")
    other = corrupted("self-bytes", lambda d: None)
    p = next(other.glob("*.svg"))
    p.write_bytes(p.read_bytes().replace(b"0", b"1", 1))
    if not same_files(drawing, other):
        failures.append("the comparison of two runs accepts a changed file")
    return failures


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    args = parser.parse_args()
    faust = args.faust.resolve()

    failures = 0
    with tempfile.TemporaryDirectory(prefix="faust-svg-root-") as temp:
        work = Path(temp)
        stem = {"t.dsp": "t", "c.dsp": "c"}
        drawings, passed = {}, set()
        for i, (name, options, program, title, inner) in enumerate(CASES):
            first = draw(faust, options, program, work, f"{i}a") / f"{stem[program]}-svg"
            second = draw(faust, options, program, work, f"{i}b") / f"{stem[program]}-svg"
            drawings[name] = first
            errors = check_drawing(first, title, inner)
            differ = same_files(first, second)
            if differ:
                errors.append(f"a second run differs on {len(differ)} files: {differ[:3]}")
            count = len(list(first.glob("*.svg")))
            if errors:
                failures += 1
                print(f"FAIL [{name}]: {count} files")
                for e in errors:
                    print(f"    {e}")
            else:
                passed.add(name)
                print(f"PASS [{name}]: {count} files, root process.svg titled {title}")

        # corrupting a drawing proves something only if the drawing passes
        base = "-pn test using process, folded"
        if base in passed:
            self_failures = self_check(drawings[base], work)
            for failure in self_failures:
                failures += 1
                print(f"FAIL [self check]: {failure}")
            if not self_failures:
                print("PASS [self check]: 3 corrupted drawings and a changed file rejected")
        else:
            print(f"SKIP [self check]: the drawing it corrupts ({base}) fails")

        # -ps draws the same diagrams, numbered: process-1.ps, <name>-<serial>-<k>.ps
        options = ["-ps", "-f", "1", "-pn", "test"]
        ps = draw(faust, options, "t.dsp", work, "ps") / "t-ps"
        ps_stems = {re.sub(r"-[0-9]+\.ps$", "", p.name) for p in ps.glob("*.ps")}
        svg_stems = {p.stem for p in drawings["-pn test using process, folded"].glob("*.svg")}
        if "process-1.ps" in {p.name for p in ps.glob("*.ps")} and ps_stems == svg_stems:
            print(f"PASS [-ps -pn test]: {len(ps_stems)} files, root process-1.ps")
        else:
            failures += 1
            print(f"FAIL [-ps -pn test]: {sorted(ps_stems ^ svg_stems)[:5]} differ from -svg, "
                  f"files {sorted(p.name for p in ps.glob('process*'))}")

        # -mdoc: each <diagram> has its directory, whose root is process.svg
        mdoc = draw(faust, ["-mdoc"], "m.dsp", work, "mdoc") / "m-mdoc"
        tex = (mdoc / "tex" / "m.tex").read_text(encoding="utf-8")
        figures = re.findall(r"\\includegraphics\[[^]]*\]\{\.\./svg/(svg-[0-9]+)/([^}]*)\}", tex)
        errors = [] if len(figures) == 2 else [f"{len(figures)} figures, expected 2"]
        for (directory, root), title in zip(figures, ("process", "one")):
            if root != "process":
                errors.append(f"{directory}: the figure includes {root}, not process")
            errors += [f"{directory}: {e}"
                       for e in check_drawing(mdoc / "svg" / directory, title, False)]
        if errors:
            failures += 1
            print("FAIL [-mdoc]:")
            for e in errors:
                print(f"    {e}")
        else:
            print(f"PASS [-mdoc]: {len(figures)} figures, each includes its process.svg")

    return 1 if failures else 0


if __name__ == "__main__":
    sys.exit(main())
