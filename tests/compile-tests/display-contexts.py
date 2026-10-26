#!/usr/bin/env python3
"""Regression test: a harvested bargraph shows the value its expression has in the program.

The ocpp backend evaluates a harvested bargraph once per block (the control context), from
values captured at the end of the sample loop (the audio context) : spec
LE-CONTEXTE-DES-OCCURRENCES. Each case below compiles a program whose bargraph displays an
expression E, and a witness program that outputs E as an audio channel ; after each block,
the bargraph must hold the last sample of that channel. The cases are the defects the
contexts had :

- a negation shared by an output and a sum of the display stopped the compiler, and a
  chain of shared negations grew exponentially (a negation is a signed read of its
  operand, never a value of its own) ;
- a node shared with the branch of an enable, a control or a select (-lazyselect,
  -selectn) was computed only when the condition held, and the bargraph showed a stale
  value (the display uses are unconditional) ;
- under -reassoc, -temp and -mindelay, the contexts were computed before the rewrite of
  the program, and the C++ code did not compile ;
- a block of no sample left the bargraph with an uninitialized capture (the bargraph keeps
  its value, 0 before the first block) ;
- under -ls -inpl, an input read by the display only was captured from a buffer the
  outputs had overwritten (it is read before the loops, under -ls with or without -inpl).
"""

import argparse
import math
from pathlib import Path
import re
import subprocess
import sys
import tempfile

ENV = "env = abs : *(0.1) : + ~ *(0.9);"  # a follower : a recursion, no library
PEAK = "env = abs : e with { p = 0.9998; e(x) = x * (1.0 - p) : (+ : max(x,_)) ~ *(p); };"
LP = "lp = *(0.2) : + ~ *(0.8);"

A_ENABLE = "A(x) = sin(x)*2 + x@3;"
B_SELECT = "B(x) = cos(x)*3;"
A_DELAY = "A(x) = (sin(x)*2)@3;"
STAGE = "st = _ <: (0.5 - sin(_)) * (0.7 - sin(_));"

# name : (program, witness, faust options, witness channel, runner modes, sin calls expected)
CASES = {
    "shared negation": (
        'process(x) = attach(0 - sin(x), 1 - sin(x) : hbargraph("b", -2, 2));',
        "process(x) = 0 - sin(x), 1 - sin(x);", [], 1, [], None),
    "shared negation, follower": (
        f'{ENV}\nprocess(x) = attach(x * (1 - env(x)), 0.5 - env(x) : hbargraph("b", -2, 2));',
        f"{ENV}\nprocess(x) = x * (1 - env(x)), 0.5 - env(x);", [], 1, [], None),
    "chain of shared negations": (
        f'{STAGE}\nprocess = _ <: _, (seq(k, 16, st) : hbargraph("b", -2, 2)) : attach;',
        f"{STAGE}\nprocess = _ <: _, seq(k, 16, st);", [], 1, [], 16),
    "enable": (
        f'{A_ENABLE}\nprocess(x) = attach(enable(A(x), x > 0), A(x) : hbargraph("b", -3, 3));',
        f"{A_ENABLE}\nprocess(x) = enable(A(x), x > 0), A(x);", [], 1, [], None),
    "control": (
        f'{A_ENABLE}\nprocess(x) = attach(control(A(x), x > 0), A(x) : hbargraph("b", -3, 3));',
        f"{A_ENABLE}\nprocess(x) = control(A(x), x > 0), A(x);", [], 1, [], None),
    "enable, delayed": (
        f'{A_DELAY}\nprocess(x) = attach(enable(A(x), x > 0), A(x) : hbargraph("b", -3, 3));',
        f"{A_DELAY}\nprocess(x) = enable(A(x), x > 0), A(x);", [], 1, [], None),
    "select, -lazyselect": (
        f'{A_ENABLE}\n{B_SELECT}\nprocess(x) = attach(select2(x > 0, A(x), B(x)), A(x) : hbargraph("b", -2, 2));',
        f"{A_ENABLE}\n{B_SELECT}\nprocess(x) = select2(x > 0, A(x), B(x)), A(x);", ["-lazyselect"], 1, [], None),
    "select, -selectn": (
        f'{A_ENABLE}\n{B_SELECT}\nprocess(x) = attach(select2(x > 0, A(x), B(x)), A(x) : hbargraph("b", -2, 2));',
        f"{A_ENABLE}\n{B_SELECT}\nprocess(x) = select2(x > 0, A(x), B(x)), A(x);", ["-selectn"], 1, [], None),
    "-reassoc": (
        f'{PEAK}\nprocess = _ <: (_ * (env <: _, (sin : hbargraph("b", -1, 1)) : attach));',
        f"{PEAK}\nprocess = _ <: _ * env, sin(env);", ["-reassoc"], 1, [], None),
    "-temp 1": (
        f'{PEAK}\nprocess = _ <: (_ * (env <: _, (sin : hbargraph("b", -1, 1)) : attach));',
        f"{PEAK}\nprocess = _ <: _ * env, sin(env);", ["-temp", "1"], 1, [], None),
    "-mindelay 2": (
        f'{PEAK}\nprocess = _ <: (_ * (env <: _, (sin : hbargraph("b", -1, 1)) : attach));',
        f"{PEAK}\nprocess = _ <: _ * env, sin(env);", ["-mindelay", "2"], 1, [], None),
    "block of no sample": (
        'process = _ <: _, (_@100 : +(0.5) <: sin + cos : 20 * log10(abs(_)) : hbargraph("b", -60, 10)) : attach;',
        "process = _ <: _, (_@100 : +(0.5) <: sin + cos : 20 * log10(abs(_)));", [], 1, ["zerofirst"], None),
    "input, -ls": (
        f'{LP}\nprocess = _ <: (lp : lp : *(0.5)), (sin : hbargraph("b", -1, 1)) : attach;',
        f"{LP}\nprocess = _ <: (lp : lp : *(0.5)), sin;", ["-ls"], 1, [], None),
    "input, -inpl": (
        f'{LP}\nprocess = _ <: (lp : lp : *(0.5)), (sin : hbargraph("b", -1, 1)) : attach;',
        f"{LP}\nprocess = _ <: (lp : lp : *(0.5)), sin;", ["-inpl"], 1, ["inplace"], None),
    "input, -ls -inpl": (
        f'{LP}\nprocess = _ <: (lp : lp : *(0.5)), (sin : hbargraph("b", -1, 1)) : attach;',
        f"{LP}\nprocess = _ <: (lp : lp : *(0.5)), sin;", ["-ls", "-inpl"], 1, ["inplace"], None),
}

# Runs mydsp for NB blocks of B samples and prints, after each block, the first bargraph
# and the last sample of every output. The object is built on memory that is not zero, so
# an uninitialized bargraph or capture does not read as 0 by chance.
RUNNER = r"""
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <new>
#include <vector>
#include <faust/dsp/dsp.h>
#include <faust/gui/meta.h>
#include <faust/gui/DecoratorUI.h>
#include "generated.cpp"

struct Controls : public GenericUI {
    std::vector<FAUSTFLOAT*> fBars;
    struct In { FAUSTFLOAT* zone; FAUSTFLOAT lo, hi; bool binary; };
    std::vector<In> fIns;
    void addButton(const char*, FAUSTFLOAT* z) override { fIns.push_back({z, 0, 1, true}); }
    void addCheckButton(const char*, FAUSTFLOAT* z) override { fIns.push_back({z, 0, 1, true}); }
    void addVerticalSlider(const char*, FAUSTFLOAT* z, FAUSTFLOAT, FAUSTFLOAT lo, FAUSTFLOAT hi, FAUSTFLOAT) override { fIns.push_back({z, lo, hi, false}); }
    void addHorizontalSlider(const char*, FAUSTFLOAT* z, FAUSTFLOAT, FAUSTFLOAT lo, FAUSTFLOAT hi, FAUSTFLOAT) override { fIns.push_back({z, lo, hi, false}); }
    void addNumEntry(const char*, FAUSTFLOAT* z, FAUSTFLOAT, FAUSTFLOAT lo, FAUSTFLOAT hi, FAUSTFLOAT) override { fIns.push_back({z, lo, hi, false}); }
    void addHorizontalBargraph(const char*, FAUSTFLOAT* z, FAUSTFLOAT, FAUSTFLOAT) override { fBars.push_back(z); }
    void addVerticalBargraph(const char*, FAUSTFLOAT* z, FAUSTFLOAT, FAUSTFLOAT) override { fBars.push_back(z); }
};

static uint32_t gSeed = 12345;
static double noise() { gSeed = gSeed * 1664525u + 1013904223u; return (gSeed >> 8) / double(1 << 24) - 0.5; }

int main(int argc, char** argv) {
    const int B = 64, NB = 30;
    const bool inplace = argc > 1 && !std::strcmp(argv[1], "inplace");
    const bool zerofirst = argc > 1 && !std::strcmp(argv[1], "zerofirst");
    alignas(mydsp) static unsigned char memory[sizeof(mydsp)];
    std::memset(memory, 0x7f, sizeof(memory));
    mydsp* d = new (memory) mydsp();
    d->init(48000);
    Controls ui;
    d->buildUserInterface(&ui);
    int ni = d->getNumInputs(), no = d->getNumOutputs();
    std::vector<std::vector<FAUSTFLOAT>> in(ni, std::vector<FAUSTFLOAT>(B)), out(no, std::vector<FAUSTFLOAT>(B));
    std::vector<FAUSTFLOAT*> ip(ni), op(no);
    for (int c = 0; c < ni; c++) ip[c] = in[c].data();
    for (int c = 0; c < no; c++) op[c] = (inplace && c < ni) ? ip[c] : out[c].data();
    if (zerofirst) {
        d->compute(0, ip.data(), op.data());
        std::printf("zero %.9g\n", ui.fBars.empty() ? 0.0 : double(*ui.fBars[0]));
    }
    long n = 0;
    for (int b = 0; b < NB; b++) {
        if (b == NB / 3) {
            for (auto& x : ui.fIns) *x.zone = x.binary ? 1 : FAUSTFLOAT(x.lo + 0.7 * (x.hi - x.lo));
        }
        if (b == (2 * NB) / 3) {
            for (auto& x : ui.fIns) if (x.binary) *x.zone = 0;
        }
        for (int c = 0; c < ni; c++)
            for (int k = 0; k < B; k++) in[c][k] = FAUSTFLOAT(0.5 * std::sin(0.003 * (n + k) * (c + 1)) + 0.4 * noise());
        d->compute(B, ip.data(), op.data());
        n += B;
        if (!ui.fBars.empty()) std::printf("block %d bar %.9g\n", b, double(*ui.fBars[0]));
        for (int c = 0; c < no; c++) std::printf("block %d last %d %.9g\n", b, c, double(op[c][B - 1]));
    }
    return 0;
}
"""

SIN = re.compile(r"\bsin[fl]?\s*\(")


def run(args, repo, work, tag, source, options, mode):
    """Compiles source with faust and the runner ; returns the runner's output, or an error."""
    (work / f"{tag}.dsp").write_text(source + "\n")
    try:
        r = subprocess.run([str(args.faust), "-lang", "ocpp", *options, str(work / f"{tag}.dsp"),
                            "-o", str(work / f"{tag}.cpp")], capture_output=True, text=True, timeout=60)
    except subprocess.TimeoutExpired:
        return None, "faust did not finish in 60 s"
    if r.returncode != 0:
        return None, f"faust failed: {r.stderr.strip()}"
    code = (work / f"{tag}.cpp").read_text()
    (work / f"{tag}-runner.cpp").write_text(RUNNER.replace('"generated.cpp"', f'"{tag}.cpp"'))
    r = subprocess.run([args.cxx, "-std=c++17", "-O1", "-ffp-contract=off", "-I", str(repo / "architecture"),
                        f"{tag}-runner.cpp", "-o", f"{tag}-runner"], cwd=work, capture_output=True, text=True)
    if r.returncode != 0:
        return None, f"C++ compilation failed:\n{r.stderr.strip()}"
    r = subprocess.run([str(work / f"{tag}-runner"), *mode], cwd=work, capture_output=True, text=True)
    if r.returncode != 0:
        return None, f"the runner failed: {r.stderr.strip()}"
    return (code, r.stdout), None


def same(a, b):
    if math.isnan(a) or math.isnan(b):
        return math.isnan(a) and math.isnan(b)
    return abs(a - b) <= 1e-5 * max(1.0, abs(b))


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    parser.add_argument("--cxx", default="c++")
    args = parser.parse_args()

    failures = 0
    for name, (program, witness, options, chan, mode, sins) in CASES.items():
        with tempfile.TemporaryDirectory(prefix="faust-display-contexts-") as temp:
            work = Path(temp)
            p, err = run(args, repo, work, "program", program, options, mode)
            if err:
                print(f"FAIL [{name}]: {err}")
                failures += 1
                continue
            w, err = run(args, repo, work, "witness", witness, options, [])
            if err:
                print(f"FAIL [{name}]: witness: {err}")
                failures += 1
                continue
            problems = []
            if sins is not None and len(SIN.findall(p[0])) != sins:
                problems.append(f"{len(SIN.findall(p[0]))} calls of sin, expected {sins}")
            bars, lasts, zero = {}, {}, None
            for line in p[1].splitlines():
                f = line.split()
                if f[0] == "zero":
                    zero = float(f[1])
                elif f[2] == "bar":
                    bars[int(f[1])] = float(f[3])
            for line in w[1].splitlines():
                f = line.split()
                if f[2] == "last" and int(f[3]) == chan:
                    lasts[int(f[1])] = float(f[4])
            if "zerofirst" in mode and zero != 0.0:
                problems.append(f"after a block of no sample, the bargraph is {zero}, expected 0")
            if len(bars) != 30 or len(lasts) != 30:
                problems.append(f"{len(bars)} bargraph values and {len(lasts)} witness values, expected 30")
            wrong = [b for b in sorted(bars) if b in lasts and not same(bars[b], lasts[b])]
            if wrong:
                b = wrong[0]
                problems.append(f"{len(wrong)} blocks of 30 differ, first block {b}: "
                                f"bargraph {bars[b]!r}, expected {lasts[b]!r}")
            if problems:
                print(f"FAIL [{name}]: " + "; ".join(problems))
                failures += 1
            else:
                print(f"ok   [{name}]")
    if failures:
        sys.exit(1)


if __name__ == "__main__":
    main()
