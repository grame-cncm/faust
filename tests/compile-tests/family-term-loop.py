#!/usr/bin/env python3
"""One loop of terms for the hosts of a family whose member calls an inline function.

A sum of many terms of one shape is a family (LES-FAMILLES-DE-LA-FORME-DE-CALCUL), which ocpp
computes in loops over arrays. When the sum was cut in partial sums, the family has several
hosts, and each host has a loop over its own members : four members for a sum cut in fours.
When the member calls a function written without a call of the libm (faustsin17f, faustcos17f,
fausttanhf, LES-FONCTIONS-MATHEMATIQUES-EN-LIGNE), the function is the whole cost of the member
and a C++ compiler vectorizes it across more members than a host has : the terms of every host
are then stored by one loop over all the members, and each host is summed from its terms, in
the lanes and the order of its own loop.

The code only is read, in ocpp :

1. Several hosts and an inline sine, cosine or hyperbolic tangent : one array of terms, of the
   size of the family ; the loop over all the members written twice with the same body. For
   clang, plain loops of whole vectors : the multiples of 16 members in one loop, then a loop
   of 8, a loop of 4, and the members that remain, fewer than 4. For the other compilers,
   groups of four, with the members beyond the last whole group in a loop of their own. One
   sum per host, and the terms the hosts read are the terms of the array, each once, in
   order ; no loop of a host computes a member.
2. The same programs under -noim and in double precision, where every call stays : one loop
   per host, no array of terms.
3. Several hosts and a member without a call, with a call that has no inline version (exp),
   or with the sine and the cosine of one argument, which keep their calls : one loop per host.
"""

import argparse
from pathlib import Path
import re
import subprocess
import sys
import tempfile

HEAD = ('import("stdfaust.lib");\n'
        'f = hslider("f", 110, 20, 200, 0.01);\n'
        r"ph(k) = (+(f / ma.SR * (k + 1)) : \(x).(x - floor(x))) ~ _;" "\n")

# name, program, the inline function its member calls ("" : none)
PROGRAMS = [
    ("64 sines", "process = sum(k, 64, sin(2 * ma.PI * ph(k)) / (k + 1));\n", "faustsin17f"),
    ("64 cosines", "process = sum(k, 64, cos(2 * ma.PI * ph(k)) / (k + 1));\n", "faustcos17f"),
    ("64 hyperbolic tangents", "process = sum(k, 64, ma.tanh(3 * ph(k) - 1) / (k + 1));\n", "fausttanhf"),
    ("10 sines", "process = sum(k, 10, sin(2 * ma.PI * ph(k)) / (k + 1));\n", "faustsin17f"),
    ("48 sines", "process = sum(k, 48, sin(2 * ma.PI * ph(k)) / (k + 1));\n", "faustsin17f"),
    ("64 members without a call", "process = sum(k, 64, ph(k) / (k + 1));\n", ""),
    ("64 exponentials", "process = sum(k, 64, exp(0 - ph(k)) / (k + 1));\n", ""),
    ("64 pairs", "process = sum(k, 64, sin(2 * ma.PI * ph(k)) * cos(2 * ma.PI * ph(k)) / (k + 1));\n", ""),
]


def faust(args, dsp, options):
    cmd = [str(args.faust), "-lang", "ocpp"] + options + [str(dsp)]
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0:
        raise RuntimeError(f"faust ocpp {' '.join(options)} {dsp.name} : {r.stderr.strip()}")
    return r.stdout


def hosts(text):
    return sorted(int(h) for h in set(re.findall(r"\bfFam0H(\d+)L\[\d+\] = \{\};", text)))


def per_host(text):
    """One loop per host, which computes its members and adds them : the reason of a refusal, or ''."""
    H = hosts(text)
    if len(H) < 2:
        return f"{len(H)} host(s), several expected"
    if "fFam0Tm" in text:
        return "an array of terms"
    loops = len(re.findall(r"^\s*#pragma clang loop vectorize\(disable\)$", text, re.M))
    if loops != len(H):
        return f"{loops} loops for {len(H)} hosts"
    return ""


def joint(text, function):
    """One loop of terms for all the hosts : the reason of a refusal, or ''."""
    H = hosts(text)
    if len(H) < 2:
        return f"{len(H)} host(s), several expected"
    decl = re.findall(r"^\s*float \tfFam0Tm\[(\d+)\];$", text, re.M)
    if len(decl) != 1:
        return f"{len(decl)} arrays of terms"
    P = int(decl[0])
    lines = [l.strip() for l in text.split("\n")]
    i = lines.index(f"float \tfFam0Tm[{P}];")
    # the loop over all the members, twice
    if lines[i + 1] != "#if defined(__clang__)":
        return "no text for clang after the array of terms"
    # for clang : every whole vector of 16 in one loop, at most one loop of 8 and one of 4, the rest
    bounds, c = [], 0
    for size in (16, 8, 4, 1):
        n = ((P - c) // size) * size if size in (16, 1) else (size if P - c >= size else 0)
        if n:
            bounds.append((c, c + n))
            c += n
    k = i + 2
    body = None
    for a, b in bounds:
        m = re.fullmatch(rf"for \(int c = {a}; c < {b}; c\+\+\) \{{(.*) \}}", lines[k])
        if not m or (body is not None and m.group(1) != body):
            return f"no plain loop over the members {a} to {b - 1}, with the body of the others"
        body = m.group(1)
        k += 1
    if lines[k] != "#else":
        return f"more plain loops than the {len(bounds)} expected"
    if f"fFam0Tm[c] = " not in body or f"{function}(" not in body:
        return f"the loop does not store a term that calls {function}"
    main = (P // 4) * 4
    g = re.fullmatch(rf"for \(int c0 = 0; c0 < {main}; c0 \+= 4\) \{{ for \(int j = 0; j < 4; j\+\+\) \{{ int c = c0 \+ j;(.*) \}} \}}",
                     lines[k + 1])
    if not g or g.group(1) != body:
        return "the loop in groups of four has not the body of the plain loops"
    k += 2
    if main < P:
        r = re.fullmatch(rf"for \(int c = {main}; c < {P}; c\+\+\) \{{(.*) \}}", lines[k])
        if not r or r.group(1) != body:
            return "the members beyond the last group of four have not the body of the plain loops"
        k += 1
    if lines[k] != "#endif":
        return "the two texts of the loop are not closed"
    # the terms the hosts read : every term once, in order
    read = []
    for h in H:
        grp = re.findall(rf"for \(int c0 = (\d+); c0 < (\d+); c0 \+= (\d+)\) \{{ for \(int j = 0; j < (\d+); j\+\+\) "
                         rf"\{{ fFam0H{h}L\[j\] \+= fFam0Tm\[c0 \+ j\]; \}} \}}", text)
        if len(grp) != 1 or grp[0][2] != grp[0][3]:
            return f"host {h} : no sum of its terms in lanes"
        lo, hi, W = int(grp[0][0]), int(grp[0][1]), int(grp[0][2])
        if (hi - lo) % W != 0:
            return f"host {h} : {hi - lo} terms in {W} lanes"
        read += list(range(lo, hi))
        for a, b in re.findall(rf"for \(int c = (\d+); c < (\d+); c\+\+\) \{{ fFam0H{h}L\[0\] \+= fFam0Tm\[c\]; \}}", text):
            read += list(range(int(a), int(b)))
    if read != list(range(P)):
        return f"the hosts read the terms {read}, not the {P} terms in order"
    if re.search(r"fFam0H\d+L\[\w+\] \+= \(", text) or "vectorize(disable)" in text:
        return "a loop of a host computes a member"
    return ""


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    args, _ = parser.parse_known_args()
    args.faust = args.faust.resolve()
    fails = []
    n = 0
    with tempfile.TemporaryDirectory(prefix="faust-family-term-loop-") as temp:
        dsp = Path(temp) / "family.dsp"
        for name, source, function in PROGRAMS:
            dsp.write_text(HEAD + source)
            cases = [("-single", ["-single"], function), ("-single -noim", ["-single", "-noim"], ""),
                     ("-double", ["-double"], "")]
            for label, options, fun in cases:
                n += 1
                text = faust(args, dsp, options)
                why = joint(text, fun) if fun else per_host(text)
                form = "one loop of terms" if fun else "one loop per host"
                print(f"{'ok  ' if not why else 'FAIL'} {label:14s} {name:26s} {form}, {len(hosts(text))} hosts"
                      + (f" : {why}" if why else ""))
                if why:
                    fails.append(f"{label} {name}")
    if fails:
        print(f"{len(fails)} failures out of {n} : {', '.join(fails)}")
        sys.exit(1)
    print(f"One loop of terms for the hosts of a family whose member calls an inline function : {n} codes read.")


if __name__ == "__main__":
    main()
