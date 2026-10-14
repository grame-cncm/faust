#!/usr/bin/env python3
"""Canonicity of the normal form : equivalent writings of one computation should give the
same normal form, or at least the same intervals.

Each subdirectory is a family ; its .dsp files are writings of the same computation, with
the same controls. The first file (in name order) is the reference ; every other writing
is compared with it on the output of `faust -norm` :

  same       the equations and their types are identical ;
  intervals  the equations differ, the intervals of the outputs are identical (their
             bounds and validity ; a different lsb is reported, not judged) ;
  differs    the intervals of the outputs differ ;
  error      the writing does not compile.

expected.tsv gives the status each writing is expected to reach (family, writing, status,
reason). The check fails when a writing does worse than expected, and reports the ones
that do better : their expectation is then raised (--update rewrites the statuses,
keeping the reasons).

usage : canonical.py --faust BIN [--lib DIR] [--update]
"""
import argparse, os, re, subprocess, sys

RANK = {"error": -1, "differs": 0, "intervals": 1, "same": 2}
HERE = os.path.dirname(os.path.abspath(__file__))

ap = argparse.ArgumentParser()
ap.add_argument("--faust", required=True)
ap.add_argument("--lib", default=os.path.join(HERE, "..", "..", "libraries"))
ap.add_argument("--update", action="store_true")
opt = ap.parse_args()


def normal_form(path):
    """the equations and the types of the outputs printed by faust -norm, or None"""
    cmd = [opt.faust, "-norm", "-I", os.path.abspath(opt.lib), os.path.basename(path)]
    r = subprocess.run(cmd, capture_output=True, text=True, cwd=os.path.dirname(path))
    if "Dump normal form finished" not in r.stdout + r.stderr:
        return None, (r.stderr or r.stdout).strip().splitlines()[:1]
    lines = [l for l in r.stdout.splitlines() if l.strip() and not l.startswith("Dump normal form")]
    # the equations without their type comments, comment-only lines dropped ; the types of
    # the outputs : the comment of the process line
    # (a line too long for the column of types has its type on the line above)
    equations, outputs, above = [], "", ""
    for l in lines:
        if l.lstrip().startswith("//"):
            above = l.strip()[2:].strip()
            continue
        text, _, comment = l.partition("  //")
        equations.append(text.rstrip())
        if l.startswith("process"):
            outputs = comment.strip() or above
        above = ""
    bounds = re.sub(r" lsb -?[0-9]+", "", outputs)
    return {"full": "\n".join(lines), "equations": "\n".join(equations), "outputs": outputs,
            "bounds": bounds}, None


def status(ref, nf):
    if nf is None:
        return "error"
    if nf["full"] == ref["full"]:
        return "same"
    if nf["bounds"] == ref["bounds"]:
        return "intervals"
    return "differs"


def first_difference(a, b):
    for x, y in zip(a.splitlines(), b.splitlines()):
        if x != y:
            return x.strip()[:90] + "  |  " + y.strip()[:90]
    return "(one is a prefix of the other)"


expected = {}
exp_path = os.path.join(HERE, "expected.tsv")
if os.path.exists(exp_path):
    for l in open(exp_path):
        if l.strip() and not l.startswith("#"):
            fam, wri, st, *reason = l.rstrip("\n").split("\t")
            expected[(fam, wri)] = (st, reason[0] if reason else "")

version = subprocess.run([opt.faust, "--version"], capture_output=True, text=True).stdout.splitlines()
print("faust :", opt.faust)
print(" ", " / ".join(l for l in version if "Version" in l or "Source commit" in l))
observed, worse, better, total = [], 0, 0, 0
for fam in sorted(d for d in os.listdir(HERE) if os.path.isdir(os.path.join(HERE, d))):
    files = sorted(f for f in os.listdir(os.path.join(HERE, fam)) if f.endswith(".dsp"))
    if len(files) < 2:
        continue
    ref, err = normal_form(os.path.join(HERE, fam, files[0]))
    print(f"\n{fam} (reference {files[0]})")
    if ref is None:
        print(f"  the reference does not compile : {err}")
        worse += 1
        continue
    for f in files[1:]:
        nf, err = normal_form(os.path.join(HERE, fam, f))
        st = status(ref, nf)
        exp, reason = expected.get((fam, f), ("same", ""))
        total += 1
        verdict = "ok"
        if RANK[st] < RANK[exp]:
            verdict, worse = "WORSE", worse + 1
        elif RANK[st] > RANK[exp]:
            verdict, better = "better", better + 1
        print(f"  {f:28s} {st:10s} expected {exp:10s} {verdict}")
        if st == "intervals":
            print(f"      first difference : {first_difference(ref['equations'], nf['equations'])}")
            if nf["outputs"] != ref["outputs"]:
                print(f"      lsb : {ref['outputs']}  |  {nf['outputs']}")
        if st == "differs":
            print(f"      outputs : {ref['outputs']}  |  {nf['outputs']}")
        if st == "error":
            print(f"      {err}")
        observed.append((fam, f, st, reason))

print(f"\n{total} writings compared : {worse} worse than expected, {better} better")
if opt.update:
    with open(exp_path, "w") as out:
        out.write("# family\twriting\tstatus (same, intervals, differs)\treason\n")
        for fam, f, st, reason in observed:
            out.write(f"{fam}\t{f}\t{st}\t{reason}\n")
    print("expected.tsv rewritten from the observed statuses")
sys.exit(1 if worse else 0)
