#!/usr/bin/env python3
"""paramsearch — layer 3: search over the compiler's numeric
parameters, under the same judge as the elections (six locks).

A KNOB = candidate values around the default, a set of WITNESSES
(the programs where the knob's family wins or comes close, per the
V8 map), and a transport (environment variable or flags). Protocol:
per witness, one binary per value, co-measured alternating rounds;
aggregate = geomean of the normalised curves; a new default is only
proclaimed if it confirms its lead on a SECOND, spaced-out draw
(the karplus rule). Usage:

    paramsearch.py tau|atoms [--rounds N]
"""
import argparse, math, os, shutil, subprocess, sys, tempfile, time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import faustauto as fa

EX = os.path.join(fa.FAUST_ROOT, "examples")

KNOBS = {
    "tau": {
        "flags": ["-gatequiv"],
        "env": "FAUST_GATEQUIV_TAU",
        "default": 12,
        "values": [6, 9, 12, 16, 24, 32],
        "witnesses": [
            f"{EX}/bela/FMSynth2.dsp", f"{EX}/bela/FMSynth2_FX.dsp",
            f"{EX}/quantizing/quantizedChords.dsp", f"{EX}/bela/FMSynth2_Analog.dsp",
            f"{EX}/misc/drumkit.dsp", f"{EX}/dynamic/noiseGate.dsp",
            f"{EX}/physicalModeling/marimbaMIDI.dsp", f"{EX}/bela/WaveSynth_Analog.dsp",
        ],
    },
    "atoms": {
        "flags": ["-lazyselect"],
        "env": "FAUST_LZ_ATOMS",
        "default": 4,
        "values": [2, 3, 4, 5, 6],
        # dx7 is the CLIFF (8 -> DNF growth, stack crash): a mandatory
        # witness; a value that does not compile is disqualified
        "witnesses": [
            f"{EX}/bela/FMSynth2_FX.dsp", f"{EX}/bela/GrainGenerator.dsp",
            f"{EX}/bela/simpleSynth.dsp", f"{EX}/generator/brightOrgan.dsp",
            f"{EX}/quantizing/quantizedChords.dsp", f"{EX}/generator/dx7.dsp",
            f"{EX}/physicalModeling/vocalFOFMIDI.dsp",
        ],
    },
}

def build(dsp, flags, envn, val, wd, tag):
    cpp = os.path.join(wd, f"{tag}.cpp")
    env = dict(os.environ, **({envn: str(val)} if envn else {}))
    r = subprocess.run([fa.FAUST, "-lang", "ocpp", *flags, "-a", fa.FLASH_ARCH,
                        "-A", fa.ARCH_DIR, dsp, "-o", cpp],
                       env=env, capture_output=True, timeout=180)
    if r.returncode or not os.path.getsize(cpp):
        return None
    b = os.path.join(wd, f"{tag}-bin")
    r = subprocess.run([fa.CXX, *fa.CXXFLAGS, f"-I{fa.ARCH_DIR}", f"-I{fa.ARCHS_DIR}",
                        cpp, "-o", b], capture_output=True)
    return b if r.returncode == 0 else None

def rounds(bins, n):
    names = list(bins)
    times = {k: [] for k in names}
    for t in range(n):
        for k in names[t % len(names):] + names[:t % len(names)]:
            v = fa.run_once(bins[k])
            if v is not None:
                times[k].append(v)
    return {k: min(v) for k, v in times.items() if v}

def measure(knob, w, rounds_n):
    """One witness: a binary per value, alternating rounds; normalised curve."""
    wd = tempfile.mkdtemp(prefix="ps-")
    try:
        bins = {}
        for val in knob["values"]:
            b = build(w, knob["flags"], knob["env"], val, wd, f"v{val}")
            if b:
                bins[val] = b
            else:
                print(f"    valeur {val} : INCONSTRUCTIBLE (disqualifiée sur ce témoin)")
        if len(bins) < 2:
            return None
        fa.wait_quiet()
        time.sleep(4)
        best = rounds(bins, rounds_n)
        m = min(best.values())
        return {v: best[v] / m for v in best}
    finally:
        shutil.rmtree(wd, ignore_errors=True)

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("knob", choices=sorted(KNOBS))
    ap.add_argument("--rounds", type=int, default=6)
    a = ap.parse_args()
    knob = KNOBS[a.knob]
    print(f"paramsearch {a.knob} : defaut={knob['default']} valeurs={knob['values']}")
    curves = {}
    for w in knob["witnesses"]:
        name = os.path.basename(w)
        print(f"  temoin {name} ...", flush=True)
        c = measure(knob, w, a.rounds)
        if c:
            curves[name] = c
            print("    " + "  ".join(f"{v}:{r:.3f}" for v, r in sorted(c.items())))
    # aggregate: geomean of the curves per value (values present everywhere)
    common = set.intersection(*(set(c) for c in curves.values()))
    agg = {v: math.exp(sum(math.log(c[v]) for c in curves.values()) / len(curves))
           for v in common}
    print("\nagregat (geomean des courbes, 1.000 = meilleur du temoin) :")
    for v, r in sorted(agg.items()):
        mark = " <- defaut" if v == knob["default"] else ""
        print(f"  {v:4d} : {r:.4f}{mark}")
    winner = min(agg, key=agg.get)
    if winner == knob["default"]:
        print(f"\nverdict : le defaut {knob['default']} est confirme.")
        return
    # two-draw rule: the pretender must confirm, spaced out
    print(f"\npretendant {winner} (vs defaut {knob['default']}) — second tirage espace...")
    time.sleep(60)
    gains = []
    for w in knob["witnesses"]:
        wd = tempfile.mkdtemp(prefix="ps2-")
        try:
            bins = {}
            for val in (winner, knob["default"]):
                b = build(w, knob["flags"], knob["env"], val, wd, f"v{val}")
                if b:
                    bins[val] = b
            if len(bins) == 2:
                fa.wait_quiet()
                time.sleep(4)
                best = rounds(bins, a.rounds)
                gains.append(best[winner] / best[knob["default"]])
        finally:
            shutil.rmtree(wd, ignore_errors=True)
    g = math.exp(sum(map(math.log, gains)) / len(gains))
    print(f"second tirage : pretendant/defaut = {g:.4f} sur {len(gains)} temoins")
    if g < 0.995:
        print(f"verdict : {winner} CONFIRME comme meilleur defaut (deux tirages).")
    else:
        print(f"verdict : avantage non reproduit — le defaut {knob['default']} reste.")

if __name__ == "__main__":
    main()
