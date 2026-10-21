#!/usr/bin/env python3
"""Turn the -cn and -scn names into valid identifiers.

The names given with -cn and -scn were pasted unchanged into the generated
code and the architecture file (only a few characters of -cn were replaced),
so a name such as the one faust2lv2 derives from `2-band.dsp` produced C++
that does not compile. Every character outside [A-Za-z0-9_] now becomes '_',
a name that does not start with a letter or '_' gets the prefix "dsp", and
-wall reports the change.

Each name is compiled with the cpp, ocpp and c backends through the minimal
architectures, inlined with -i as the faust2* scripts do, then built and run.
Valid names, an empty -cn (an error) and an empty -scn (a class without a
base class) are unchanged.
"""
import argparse
from pathlib import Path
import subprocess
import tempfile

SOURCE = "process = _ * 0.5;\n"

# (-cn, -scn, expected class name, expected super class name)
CASES = [
    ("2-band", None, "dsp2_band", "dsp"),
    ("my-dsp", "my-base", "my_dsp", "my_base"),
    ("my dsp.v2", "2base", "my_dsp_v2", "dsp2base"),
    (".foo", None, "dsp_foo", "dsp"),
    ("café", None, "caf__", "dsp"),
    ("Bidule", "Machin", "Bidule", "Machin"),
    ("_priv", None, "_priv", "dsp"),
]


def run(command, work, check=True):
    print("+", " ".join(map(str, command)), flush=True)
    return subprocess.run(command, cwd=work, check=check, capture_output=True, text=True)


def faust_cmd(args, *options):
    return [args.faust, "-A", args.arch, "-wall", *options]


def check_case(args, work, cn, scn, exp_cn, exp_scn):
    names = ["-cn", cn] + (["-scn", scn] if scn is not None else [])
    for lang, arch, compiler in [("cpp", "minimal.cpp", args.cxx),
                                 ("ocpp", "minimal.cpp", args.cxx),
                                 ("c", "minimal.c", args.cc)]:
        options = names if lang != "c" else ["-cn", cn]
        ext = "c" if lang == "c" else "cpp"
        out = work / f"{lang}.{ext}"
        res = run(faust_cmd(args, "-lang", lang, "-i", "-a", args.arch / arch, *options,
                            work / "g.dsp", "-o", out), work)
        code = out.read_text()
        renamed = [o for o, n, e in [("-cn", cn, exp_cn), ("-scn", scn, exp_scn)]
                   if n is not None and n != e and (lang != "c" or o == "-cn")]
        # The ocpp backend prints no -wall warning at all, so only cpp and c are checked
        if lang != "ocpp":
            for option in renamed:
                assert f"WARNING : {option} '" in res.stderr, (lang, option, "no warning")
            if not renamed:
                assert "is not a valid identifier" not in res.stderr, (lang, "warning")
        if lang == "c":
            assert f"new{exp_cn}(" in code, (lang, exp_cn)
        else:
            assert f"class {exp_cn} : public {exp_scn}" in code, (lang, exp_cn, exp_scn)
        flags = ["-lm"] if lang == "c" else ["-std=c++17"]
        run([compiler, out, "-o", work / lang, *flags], work)
        run([work / lang], work)
        if lang == "c":
            print(f"PASS {lang} -cn {cn!r}: {exp_cn}", flush=True)
        else:
            print(f"PASS {lang} -cn {cn!r} -scn {scn!r}: {exp_cn} : {exp_scn}", flush=True)


def main():
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--faust", type=Path, default=repo / "build/bin/faust")
    parser.add_argument("--cxx", default="c++")
    parser.add_argument("--cc", default="cc")
    args = parser.parse_args()
    args.faust = args.faust.resolve()
    args.arch = repo / "architecture"
    print(run([args.faust, "--version"], repo).stdout, flush=True)
    with tempfile.TemporaryDirectory(prefix="faust-class-name-") as temp:
        work = Path(temp)
        (work / "g.dsp").write_text(SOURCE)
        for cn, scn, exp_cn, exp_scn in CASES:
            check_case(args, work, cn, scn, exp_cn, exp_scn)

        res = run(faust_cmd(args, "-cn", "", work / "g.dsp"), work, check=False)
        assert res.returncode != 0 and "-cn used with empty string" in res.stderr, res
        print("PASS -cn '': rejected", flush=True)

        res = run(faust_cmd(args, "-scn", "", work / "g.dsp"), work)
        assert "class mydsp {" in res.stdout, "-scn '' should give a class without base"
        print("PASS -scn '': class without a base class", flush=True)


if __name__ == "__main__":
    main()
