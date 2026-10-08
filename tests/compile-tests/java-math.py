#!/usr/bin/env python3
"""Compile and execute Java math, numeric conversion and UI regressions."""

from pathlib import Path
import argparse
import subprocess
import math
import struct
import tempfile

p = argparse.ArgumentParser(description=__doc__)
p.add_argument("--faust", default="build/bin/faust")
p.add_argument("--javac", default="javac")
p.add_argument("--java", default="java")
p.add_argument("--work-dir", type=Path, help="Keep generated sources and logs here")
a = p.parse_args()
a.faust = str(Path(a.faust).resolve())
workspace = tempfile.TemporaryDirectory(prefix="faust-java-math-")
out = a.work_dir.resolve() if a.work_dir else Path(workspace.name)
out.mkdir(parents=True, exist_ok=True)
root = Path(__file__).resolve().parents[2]

print(subprocess.check_output([a.faust, "--version"], text=True), flush=True)
print(subprocess.check_output([a.javac, "-version"], text=True), flush=True)
xs = [-5.5, -2.5, -1.5, -0.5, -0.0, 0.0, 0.5, 1.5, 2.5, 5.5]


def roundaway(x):
    if not math.isfinite(x):
        return x
    integral = math.floor(abs(x))
    return math.copysign(integral + (abs(x) - integral >= 0.5), x)


def compare(values, expected, tolerance):
    if len(values) != len(expected):
        return ["output count: %d != %d" % (len(values), len(expected))]
    errors = []
    for index, (actual, wanted) in enumerate(zip(values, expected)):
        if math.isnan(wanted):
            valid = math.isnan(actual)
        elif math.isinf(wanted):
            valid = actual == wanted
        elif wanted == 0:
            valid = actual == 0 and math.copysign(1, actual) == math.copysign(1, wanted)
        else:
            valid = math.isfinite(actual) and abs(actual - wanted) <= tolerance * abs(
                wanted
            )
        if not valid:
            errors.append((index, actual, wanted))
    return errors


def rint(x):
    return math.copysign(round(x), x)


def inverse_oracle(v):
    x = v[0]
    acosh = math.acosh(x) if x >= 1 else math.nan
    atanh = (
        math.atanh(x)
        if abs(x) < 1
        else (math.copysign(math.inf, x) if abs(x) == 1 else math.nan)
    )
    return [math.asinh(x), acosh, atanh]


def enabled(v):
    # enable holds its previous output while its clock is disabled.
    if v[1]:
        enabled.value = v[0]
    return [enabled.value, 2 * enabled.value]


enabled.value = 0.0


cases = [
    (
        "enable",
        "process(x,y)=enable(x,int(y)),enable(2*x,int(y));",
        [[-0.5, 0.0, 0.25, 0.75], [1.0, 0.0, 1.0, 0.0]],
        enabled,
    ),
    (
        "mixed_select",
        "process(x,y)=select2(y,x>0,int(x)),select2(y,int(x),x>0);",
        [[-0.5, 0.0, 0.25, 0.75], [0.0, 1.0, 0.0, 1.0]],
        lambda v: [
            int(v[0]) if v[1] else int(v[0] > 0),
            int(v[0] > 0) if v[1] else int(v[0]),
        ],
    ),
    (
        "integer_table",
        "process(x)=waveform{1,2,3,4},int(x):rdtable;",
        [[0.0, 1.0, 2.0, 3.0]],
        lambda v: [int(v[0]) + 1],
    ),
    (
        "real_table",
        "process(x)=waveform{0.1,0.2,0.3,0.4},int(x):rdtable;",
        [[0.0, 1.0, 2.0, 3.0]],
        lambda v: [0.1 * (int(v[0]) + 1)],
    ),
    (
        "inverse_hyperbolic",
        'import("stdfaust.lib"); process(x)=ma.asinh(x),ma.acosh(x),ma.atanh(x);',
        [
            [
                -1e308,
                -1e20,
                -1.0,
                -0.5,
                -1e-20,
                -0.0,
                0.0,
                1e-20,
                0.5,
                1.0,
                1.0000000000000002,
                1e20,
                1e308,
            ]
        ],
        inverse_oracle,
    ),
    (
        "classification",
        'import("stdfaust.lib"); process(x,y)=ma.isnan(x),ma.isinf(x),ma.copysign(x,y);',
        [
            [math.nan, math.inf, -math.inf, -0.0, 0.0, 2.0],
            [-1.0, -1.0, 1.0, 1.0, -1.0, -1.0],
        ],
        lambda v: [
            int(math.isnan(v[0])),
            int(math.isinf(v[0])),
            math.copysign(v[0], v[1]),
        ],
    ),
    (
        "round_boundaries",
        "process(x)=round(x);",
        [
            [
                -1e20,
                -0.49999999999999994,
                -0.0,
                0.0,
                0.49999999999999994,
                1e20,
                math.inf,
                -math.inf,
                math.nan,
            ]
        ],
        lambda v: [roundaway(v[0])],
    ),
    (
        "hyperbolic",
        'import("stdfaust.lib"); process(x)=ma.tanh(x),ma.sinh(x),ma.cosh(x);',
        [[-1.0, 0.0, 1.0]],
        lambda v: [math.tanh(v[0]), math.sinh(v[0]), math.cosh(v[0])],
    ),
    (
        "remainder_rint",
        "process(x,y)=remainder(x,y),rint(x);",
        [xs, [2.0] * len(xs)],
        lambda v: [math.remainder(*v), rint(v[0])],
    ),
    (
        "fmod_round",
        "process(x,y)=x%y,round(x);",
        [xs, [2.0] * len(xs)],
        lambda v: [math.fmod(*v), roundaway(v[0])],
    ),
    (
        "precision",
        "process(x)=float(int(x));",
        [[16777217.0, 16777219.0, 1.0, -1.0]],
        lambda v: [int(v[0])],
    ),
    (
        "booleans",
        "process(x)=(x>0)+1,(x>0)&(x<0.5),select2(x>0,2,3),float(x>0),(x>0)*x,(x>0)==(x<0.5);",
        [[-0.5, 0.0, 0.25, 0.75]],
        lambda v: [
            int(v[0] > 0) + 1,
            int(v[0] > 0) & int(v[0] < 0.5),
            3 if v[0] > 0 else 2,
            int(v[0] > 0),
            int(v[0] > 0) * v[0],
            int((v[0] > 0) == (v[0] < 0.5)),
        ],
    ),
    (
        "ui",
        'process=hslider("Gain",1.0000000001,0,2,0.0001);',
        [],
        lambda v: [1.0000000001],
    ),
    (
        "integer_pow",
        'import("stdfaust.lib"); s=ba.period(2)<1; process=pow(250,s)-(1+249*s),pow(25,6*s)-(1+244140624*s),pow(-3,3*s)-(1-28*s),pow(2,2*s-1)-2*s,pow(-2,2*s-1)+2*s,pow(46340,2*s)-(1+2147395599*s);',
        [],
        lambda v: [0] * 6,
    ),
]
failed = 0
compared = 0
negative_controls = set()
for precision in ["single", "double"]:
    sample = "float" if precision == "single" else "double"
    cast = lambda x: (
        (
            math.copysign(math.inf, x)
            if abs(x) > 3.4028234663852886e38
            else struct.unpack("f", struct.pack("f", x))[0]
        )
        if precision == "single"
        else x
    )
    for name, source, inputs, oracle in cases:
        work = out / (precision + "-" + name)
        work.mkdir(exist_ok=True)
        (work / "test.dsp").write_text(source)
        command = [
            a.faust,
            "-lang",
            "java",
            "-" + precision,
            "-I",
            str(root / "libraries"),
            str(work / "test.dsp"),
            "-o",
            str(work / "mydsp.java"),
        ]
        g = subprocess.run(command, capture_output=True, text=True)
        (work / "faust.log").write_text(g.stdout + g.stderr)
        if g.returncode:
            print("FAIL", precision, name, "generation", flush=True)
            print(g.stdout + g.stderr, flush=True)
            failed += 1
            continue
        n = len(inputs[0]) if inputs else 2
        outputs = len(oracle([c[0] for c in inputs]))
        ui = "class dsp {}\nclass Meta {void declare(String k,String v){}}\ninterface FaustVarAccess {String getId(); void set(SAMPLE v); SAMPLE get();}\nclass UI {void declare(String z,String k,String v){}\n"
        for group in ["Tab", "Horizontal", "Vertical"]:
            ui += "void open" + group + "Box(String label){}\n"
        ui += "void closeBox(){}\n"
        for widget in ["Button", "CheckButton"]:
            ui += "void add" + widget + "(String l,FaustVarAccess v){}\n"
        for widget in ["HorizontalSlider", "VerticalSlider", "NumEntry"]:
            ui += (
                "void add"
                + widget
                + "(String l,FaustVarAccess v,SAMPLE i,SAMPLE min,SAMPLE max,SAMPLE step){}\n"
            )
        for widget in ["HorizontalBargraph", "VerticalBargraph"]:
            ui += (
                "void add"
                + widget
                + "(String l,FaustVarAccess v,SAMPLE min,SAMPLE max){}\n"
            )
        ui += "}\n"

        def literal(v):
            value = (
                "Double.NaN"
                if math.isnan(v)
                else (
                    "Double.POSITIVE_INFINITY"
                    if v == math.inf
                    else ("Double.NEGATIVE_INFINITY" if v == -math.inf else repr(v))
                )
            )
            return "(" + sample + ")(" + value + ")"

        rows = ",".join("{" + ",".join(literal(v) for v in c) + "}" for c in inputs)
        runner = (
            ui
            + "public class Runner {public static void main(String[] args){mydsp d=new mydsp();d.init(48000);d.buildUserInterface(new UI());SAMPLE[][] inputs={"
            + rows
            + "};SAMPLE[][] output=new SAMPLE["
            + str(outputs)
            + "]["
            + str(n)
            + "];d.compute("
            + str(n)
            + ",inputs,output);for(int i=0;i<"
            + str(n)
            + ";i++)for(int c=0;c<"
            + str(outputs)
            + ";c++)System.out.println((double)output[c][i]);}}\n"
        )
        (work / "Runner.java").write_text(runner.replace("SAMPLE", sample))
        b = subprocess.run(
            [a.javac, "mydsp.java", "Runner.java"],
            cwd=work,
            capture_output=True,
            text=True,
        )
        (work / "javac.log").write_text(b.stdout + b.stderr)
        if b.returncode:
            print("FAIL", precision, name, "javac", flush=True)
            print(b.stdout + b.stderr, flush=True)
            failed += 1
            continue
        r = subprocess.run(
            [a.java, "-cp", str(work), "Runner"],
            cwd=work,
            capture_output=True,
            text=True,
        )
        (work / "output.log").write_text(r.stdout + r.stderr)
        if r.returncode:
            print("FAIL", precision, name, "runtime", flush=True)
            print(r.stdout + r.stderr, flush=True)
            failed += 1
            continue
        values = list(map(float, r.stdout.split()))
        expected = [
            cast(x) for i in range(n) for x in oracle([cast(c[i]) for c in inputs])
        ]
        tol = 2e-6 if precision == "single" else 1e-12
        errors = compare(values, expected, tol)
        # Exercise the verdict on an intentionally corrupted real output.
        if precision not in negative_controls:
            negative_controls.add(precision)
            corrupted = values.copy()
            corrupted[0] += 1
            if not compare(corrupted, expected, tol):
                raise AssertionError("Comparator accepted a corrupted output")
            print(
                "Negative control:", precision, "corrupted output rejected", flush=True
            )
        if len(values) != len(expected) or errors:
            print("FAIL", precision, name, "numeric", errors[:5], flush=True)
            failed += 1
        else:
            compared += n * outputs
            print("PASS", precision, name, n * outputs, "values", flush=True)
print("Compared:", compared, "values; failed:", failed, flush=True)
raise SystemExit(bool(failed))
