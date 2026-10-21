#!/usr/bin/env python3
"""Compile and execute non-finite constants (C++, Julia, Rust, Java, D, C#, AssemblyScript).

An infinite constant was printed as INFINITY whatever its sign, so the C++
code computed +inf where the program has -inf. The ocpp backend tested the
constant in double precision: in -single, 1e38 * 10 (folded in double, a
finite 1e39) became "inf.0f", which does not compile. The Julia backend printed
it the same way, but INFINITY is the C macro, undefined in Julia: the
generated code did not load (UndefVarError: INFINITY not defined). The
Julia literals are Inf32 and NaN32 for Float32, Inf and NaN for Float64.
Rust, Java, D and C# had the same INFINITY and did not compile; each now
uses its own constants (f32::INFINITY, Float.POSITIVE_INFINITY,
float.infinity, float.PositiveInfinity, and the double ones).
AssemblyScript had the same issue; it now uses f32.POSITIVE_INFINITY,
f32.NEGATIVE_INFINITY, f32.NaN and the f64 ones.

The program outputs +inf, -inf and 1e38 * 10 (+inf in single precision) at
its first sample, and 0 after; it is generated in single and double
precision for each backend and run. D is compiled only (--backends dlang,
with stubs for the dplug imports), C# only generated (--backends csharp):
the generated names are checked.
"""
import re
import shutil
import argparse
from pathlib import Path
import subprocess
import tempfile

SOURCE = """
ma = library("maths.lib");
I = ma.MAX * 2;                  // +inf, folded to a constant
first = (+(1) ~ _) == 1;         // 1 at the first sample only
process = select2(first, 0.0, I), select2(first, 0.0, 0 - I), select2(first, 0.0, 1e38 * 10.0);
"""

CPP_RUNNER = """
#include <cmath>
#include <cstdio>
#include <faust/dsp/dsp.h>
#include <faust/gui/meta.h>
#include <faust/gui/UI.h>
#include "generated.cpp"

int main() {
    FAUSTFLOAT out[3][2];
    FAUSTFLOAT* outputs[3] = {out[0], out[1], out[2]};
    mydsp dsp;
    dsp.init(44100);
    dsp.compute(2, nullptr, outputs);
    bool ok = std::isinf(out[0][0]) && out[0][0] > 0 && std::isinf(out[1][0]) && out[1][0] < 0
              && out[0][1] == 0 && out[1][1] == 0 && out[2][1] == 0
              && (sizeof(FAUSTFLOAT) == 4 ? (std::isinf(out[2][0]) && out[2][0] > 0) : out[2][0] == 1e39);
    if (!ok) std::printf("    got %g %g %g, then %g %g %g\\n", double(out[0][0]), double(out[1][0]),
                         double(out[2][0]), double(out[0][1]), double(out[1][1]), double(out[2][1]));
    return ok ? 0 : 1;
}
"""

RUNNER = """
abstract type dsp end
abstract type FMeta end
abstract type UI end
const FAUSTFLOAT = SAMPLE
include("mydsp.jl")
d = mydsp{SAMPLE}()
init!(d, Int32(44100))
output = zeros(SAMPLE, 2, 3)
compute!(d, Int32(2), zeros(SAMPLE, 2, 0), output)
@assert output[1, 1] == SAMPLE(Inf) output
@assert output[1, 2] == SAMPLE(-Inf) output
@assert output[1, 3] == (SAMPLE == Float32 ? Inf32 : 1e39) output
@assert all(iszero, output[2, :]) output
"""


EXPECTED = {"single": ["inf", "-inf", "inf", "0", "0", "0"],
            "double": ["inf", "-inf", "1e+39", "0", "0", "0"]}


def check_printed(lang, precision, text):
    """The six values printed by a runner (+inf, -inf, 1e38 * 10, then 0 three times)."""
    got = []
    for word in text.split():
        v = float(word.replace("Infinity", "inf"))
        got.append("inf" if v == float("inf") else "-inf" if v == -float("inf") else
                   ("0" if v == 0 else f"{v:g}"))
    if got != EXPECTED[precision]:
        raise SystemExit(f"FAIL {lang} {precision}: {got} instead of {EXPECTED[precision]}")


RUST_MAIN = """
fn main() {
    let mut dsp = mydsp::new();
    dsp.init(44100);
    let mut a = [0.0; 2]; let mut b = [0.0; 2]; let mut c = [0.0; 2];
    let inputs: [&[FaustFloat]; 0] = [];
    dsp.compute(2, &inputs, &mut [&mut a, &mut b, &mut c]);
    println!("{} {} {} {} {} {}", a[0], b[0], c[0], a[1], b[1], c[1]);
}
"""

JAVA_STUBS = (
    "class dsp {}\nclass Meta {void declare(String k,String v){}}\n"
    "interface FaustVarAccess {String getId(); void set(SAMPLE v); SAMPLE get();}\n"
    "class UI {void declare(String z,String k,String v){}\n"
    + "".join(f"void open{g}Box(String label){{}}\n" for g in ["Tab", "Horizontal", "Vertical"])
    + "void closeBox(){}\n"
    + "".join(f"void add{w}(String l,FaustVarAccess v){{}}\n" for w in ["Button", "CheckButton"])
    + "".join(f"void add{w}(String l,FaustVarAccess v,SAMPLE i,SAMPLE min,SAMPLE max,SAMPLE step){{}}\n"
              for w in ["HorizontalSlider", "VerticalSlider", "NumEntry"])
    + "".join(f"void add{w}(String l,FaustVarAccess v,SAMPLE min,SAMPLE max){{}}\n"
              for w in ["HorizontalBargraph", "VerticalBargraph"])
    + "}\npublic class Runner {public static void main(String[] args){mydsp d=new mydsp();"
    "d.init(44100);d.buildUserInterface(new UI());SAMPLE[][] in=new SAMPLE[0][2];"
    "SAMPLE[][] o=new SAMPLE[3][2];d.compute(2,in,o);System.out.println(o[0][0]+\" \"+o[1][0]"
    "+\" \"+o[2][0]+\" \"+o[0][1]+\" \"+o[1][1]+\" \"+o[2][1]);}}\n")

# What the generated D code imports from dplug, and the types it expects around it
D_NOGC = """module dplug.core.nogc;
T mallocNew(T, Args...)(Args args) nothrow @nogc { return null; }
T[] mallocSlice(T)(size_t n) nothrow @nogc { return null; }
void destroyFree(T)(T p) nothrow @nogc {}
auto assumeNothrowNoGC(T)(T t) nothrow @nogc { return t; }
"""
D_STUBS = """
public alias FAUSTFLOAT = SAMPLE;
class dsp { nothrow: @nogc: }
struct Meta { void declare(string k, string v) nothrow @nogc {} }
struct UI {
nothrow: @nogc:
    void openTabBox(string l) {} void openHorizontalBox(string l) {} void openVerticalBox(string l) {}
    void closeBox() {} void declare(FAUSTFLOAT* z, string k, string v) {}
    void addButton(string l, FAUSTFLOAT* z) {} void addCheckButton(string l, FAUSTFLOAT* z) {}
    void addHorizontalSlider(string l, FAUSTFLOAT* z, FAUSTFLOAT i, FAUSTFLOAT a, FAUSTFLOAT b, FAUSTFLOAT s) {}
    void addVerticalSlider(string l, FAUSTFLOAT* z, FAUSTFLOAT i, FAUSTFLOAT a, FAUSTFLOAT b, FAUSTFLOAT s) {}
    void addNumEntry(string l, FAUSTFLOAT* z, FAUSTFLOAT i, FAUSTFLOAT a, FAUSTFLOAT b, FAUSTFLOAT s) {}
    void addHorizontalBargraph(string l, FAUSTFLOAT* z, FAUSTFLOAT a, FAUSTFLOAT b) {}
    void addVerticalBargraph(string l, FAUSTFLOAT* z, FAUSTFLOAT a, FAUSTFLOAT b) {}
}
"""
D_MAIN = """import mydsp;
void main() {
    auto d = new mydsp.mydsp();
    d.initialize(44100);
    FAUSTFLOAT[2][3] o;
    FAUSTFLOAT*[] outs = [o[0].ptr, o[1].ptr, o[2].ptr];
    FAUSTFLOAT*[] ins = [];
    d.compute(2, ins, outs);
}
"""

CSHARP_NAMES = {"single": ["float.PositiveInfinity", "float.NegativeInfinity"],
                "double": ["double.PositiveInfinity", "double.NegativeInfinity"]}

ASC_NAMES = {"single": ["f32.POSITIVE_INFINITY", "f32.NEGATIVE_INFINITY"],
             "double": ["f64.POSITIVE_INFINITY", "f64.NEGATIVE_INFINITY"]}

ASC_RUNNER = """
export function run(): void {
    let d = new mydsp();
    let ins = new Array<Array<SAMPLE>>(0);
    let outs = new Array<Array<SAMPLE>>(3);
    outs[0] = new Array<SAMPLE>(1);
    outs[1] = new Array<SAMPLE>(1);
    outs[2] = new Array<SAMPLE>(1);
    d.compute(1, ins, outs);
}
"""


def run(command, work):
    print("+", " ".join(map(str, command)), flush=True)
    subprocess.run(command, cwd=work, check=True)


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    parser.add_argument("--julia", default="julia")
    parser.add_argument("--cxx", default="c++")
    parser.add_argument("--cargo", default="cargo")
    parser.add_argument("--offline", action="store_true", help="use cached Cargo dependencies")
    parser.add_argument("--javac", default="javac")
    parser.add_argument("--java", default="java")
    parser.add_argument("--ldc", default="ldc2")
    parser.add_argument("--asc", default="asc")
    parser.add_argument("--backends", nargs="+",
                        choices=["cpp", "ocpp", "julia", "rust", "java", "dlang", "csharp", "asc"],
                        default=["cpp", "ocpp", "julia", "rust", "java"])
    args = parser.parse_args()
    faust = args.faust.resolve()
    run([faust, "--version"], repo)
    for lang in [b for b in args.backends if b in ("cpp", "ocpp")]:
        for precision in ["single", "double"]:
            with tempfile.TemporaryDirectory(prefix="faust-nonfinite-cpp-") as temp:
                work = Path(temp)
                (work / "nonfinite.dsp").write_text(SOURCE)
                run([faust, "-I", repo / "libraries", "-lang", lang, "-" + precision,
                     work / "nonfinite.dsp", "-o", work / "generated.cpp"], work)
                (work / "runner.cpp").write_text(CPP_RUNNER)
                define = ["-DFAUSTFLOAT=double"] if precision == "double" else []
                run([args.cxx, "-std=c++17", "-O1", *define, "-I", repo / "architecture",
                     "runner.cpp", "-o", "runner"], work)
                run([work / "runner"], work)
                print(f"PASS {lang} {precision}: non-finite constants", flush=True)
    for precision in ["single", "double"] if "rust" in args.backends else []:
        with tempfile.TemporaryDirectory(prefix="faust-nonfinite-rust-") as temp:
            work = Path(temp)
            (work / "nonfinite.dsp").write_text(SOURCE)
            arch = (repo / "architecture/rust/minimal.rs").read_text().split("fn main() {")[0]
            if precision == "double":
                arch = arch.replace("type FaustFloat = F32;", "type FaustFloat = F64;")
            (work / "runner.rs").write_text(arch + RUST_MAIN)
            run([faust, "-I", repo / "libraries", "-lang", "rust", "-" + precision,
                 work / "nonfinite.dsp", "-a", work / "runner.rs", "-o", work / "mydsp.rs"], work)
            (work / "Cargo.toml").write_text(
                '[package]\nname = "faust-nonfinite"\nversion = "0.1.0"\nedition = "2024"\n'
                '[[bin]]\nname = "nonfinite"\npath = "mydsp.rs"\n'
                '[dependencies]\nlibm = "0.2"\nnum-traits = "0.2"\n')
            out = subprocess.run([args.cargo, "run", "--quiet"] + (["--offline"] if args.offline else []),
                                 cwd=work, check=True, capture_output=True, text=True).stdout
            check_printed("rust", precision, out)
            print(f"PASS rust {precision}: non-finite constants", flush=True)
    for precision in ["single", "double"] if "java" in args.backends else []:
        with tempfile.TemporaryDirectory(prefix="faust-nonfinite-java-") as temp:
            work = Path(temp)
            (work / "nonfinite.dsp").write_text(SOURCE)
            run([faust, "-I", repo / "libraries", "-lang", "java", "-" + precision,
                 work / "nonfinite.dsp", "-o", work / "mydsp.java"], work)
            sample = "float" if precision == "single" else "double"
            (work / "Runner.java").write_text(JAVA_STUBS.replace("SAMPLE", sample))
            run([args.javac, "mydsp.java", "Runner.java"], work)
            out = subprocess.run([args.java, "Runner"], cwd=work, check=True,
                                 capture_output=True, text=True).stdout
            check_printed("java", precision, out)
            print(f"PASS java {precision}: non-finite constants", flush=True)
    for precision in ["single", "double"] if "dlang" in args.backends else []:
        with tempfile.TemporaryDirectory(prefix="faust-nonfinite-d-") as temp:
            work = Path(temp)
            (work / "nonfinite.dsp").write_text(SOURCE)
            run([faust, "-I", repo / "libraries", "-lang", "dlang", "-" + precision,
                 work / "nonfinite.dsp", "-o", work / "generated.d"], work)
            sample = "float" if precision == "single" else "double"
            code = (work / "generated.d").read_text()
            (work / "mydsp.d").write_text(
                code.replace("module mydsp;", "module mydsp;" + D_STUBS.replace("SAMPLE", sample), 1))
            (work / "dplug" / "core").mkdir(parents=True)
            (work / "dplug" / "core" / "nogc.d").write_text(D_NOGC)
            (work / "main.d").write_text(D_MAIN)
            run([args.ldc, "-of=nonfinite", "main.d", "mydsp.d", "dplug/core/nogc.d"], work)
            print(f"PASS dlang {precision}: non-finite constants compile", flush=True)
    for precision in ["single", "double"] if "csharp" in args.backends else []:
        with tempfile.TemporaryDirectory(prefix="faust-nonfinite-csharp-") as temp:
            work = Path(temp)
            (work / "nonfinite.dsp").write_text(SOURCE)
            run([faust, "-I", repo / "libraries", "-lang", "csharp", "-" + precision,
                 work / "nonfinite.dsp", "-o", work / "mydsp.cs"], work)
            code = (work / "mydsp.cs").read_text()
            missing = [n for n in CSHARP_NAMES[precision] if n not in code]
            if missing or re.search(r"\bINFINITY\b", code):
                raise SystemExit(f"FAIL csharp {precision}: missing {missing} or INFINITY left")
            print(f"PASS csharp {precision}: non-finite constants generated", flush=True)
    for precision in ["single", "double"] if "asc" in args.backends else []:
        with tempfile.TemporaryDirectory(prefix="faust-nonfinite-asc-") as temp:
            work = Path(temp)
            (work / "nonfinite.dsp").write_text(SOURCE)
            run([faust, "-I", repo / "libraries", "-lang", "asc", "-" + precision,
                 work / "nonfinite.dsp", "-o", work / "mydsp.ts"], work)
            code = (work / "mydsp.ts").read_text()
            missing = [n for n in ASC_NAMES[precision] if n not in code]
            if missing or re.search(r"\bINFINITY\b", code) or re.search(r"\bNAN\b", code):
                raise SystemExit(f"FAIL asc {precision}: missing {missing} or INFINITY/NAN left")
            sample = "f32" if precision == "single" else "f64"
            (work / "mydsp.ts").write_text(code + ASC_RUNNER.replace("SAMPLE", sample))
            asc_cmd = [args.asc] if shutil.which(args.asc) else ["npx", "-p", "assemblyscript", "asc"] if shutil.which("npx") else None
            if asc_cmd:
                run([*asc_cmd, "mydsp.ts", "--outFile", "mydsp.wasm"], work)
                print(f"PASS asc {precision}: non-finite constants compile", flush=True)
            else:
                print(f"PASS asc {precision}: non-finite constants generated", flush=True)
    if "julia" not in args.backends:
        return
    run([args.julia, "--version"], repo)
    for precision in ["single", "double"]:
        with tempfile.TemporaryDirectory(prefix="faust-nonfinite-julia-") as temp:
            work = Path(temp)
            (work / "nonfinite.dsp").write_text(SOURCE)
            run([faust, "-I", repo / "libraries", "-lang", "julia", "-" + precision,
                 work / "nonfinite.dsp", "-o", work / "mydsp.jl"], work)
            sample = "Float32" if precision == "single" else "Float64"
            (work / "runner.jl").write_text(RUNNER.replace("SAMPLE", sample))
            run([args.julia, "--startup-file=no", "runner.jl"], work)
            print(f"PASS julia {precision}: non-finite constants", flush=True)


if __name__ == "__main__":
    main()
