#!/usr/bin/env python3
"""faustauto — le mode auto complet du backend ocpp, en deux couches.

Couche 1 (statique, gratuite) : la signature du programme (FAUST_SS_SIG)
élague les 53 modes en 3 ou 4 candidats. Deux sorties :
  - fusion sûre  (recmii >= 50, ou >= 5 flux réels)  -> fusion + les DEUX régimes d'ordre
  - incertain                                        -> fusion + 2 ordres + df
Le régime d'ordre suit la borne de récurrence : recmii >= 45 -> localité
(hybride R2), sinon rafales (alignement).

Couche 2 (mesurée) : chaque candidat est compilé puis benché ~0.3 s,
en tours alternés ; le gagnant mesuré est émis. Les paysages accidentés
(cap, jumeaux vocoder/filterBank) ont prouvé qu'aucune règle statique
ne remplace cette mesure.

Usage : faustauto.py fichier.dsp [-o sortie.cpp] [--rounds N] [--keep]
"""

import argparse
import os
import re
import subprocess
import sys
import tempfile
import time

FAUST = os.environ.get("FAUSTAUTO_FAUST",
                       os.path.join(os.path.dirname(__file__), "../../build/bin/faust"))
BENCH_HEADER = os.environ.get("FAUSTAUTO_BH", "/usr/local/share/fctool/bencharch_header.cpp")
BENCH_FOOTER = os.environ.get("FAUSTAUTO_BF", "/usr/local/share/fctool/bencharch_footer.cpp")
CXX = os.environ.get("FAUSTAUTO_CXX", "clang++")
CXXFLAGS = os.environ.get("FAUSTAUTO_CXXFLAGS",
                          "-O3 -ffast-math -march=native -fbracket-depth=1024").split()

# la nomenclature officielle (MODES.md §7)
CAND = {
    "fu":  ["-ls-fuse", "-ls-sched", "model"],
    "df":  ["-ss", "0"],
    "al":  ["-ss", "8"],
    "h2":  ["-ss", "9", "-ls-R", "2", "-ls-U", "4"],
    "h32": ["-ss", "9", "-ls-R", "32", "-ls-U", "4"],
    "cs8": ["-ss", "7", "-ls-R", "8", "-ls-U", "4"],
    "t4":  ["-temp", "4"],
    "t4fu": ["-temp", "4", "-ls-fuse", "-ls-sched", "model"],
    "t1fu": ["-temp", "1", "-ls-fuse", "-ls-sched", "model"],
    "fi":  ["-fir", "-iirt"],
    "fib": ["-fir", "-iirt", "-lsum"],
    "fifu":  ["-fir", "-iirt", "-ls-fuse", "-ls-sched", "model"],
    "fibfu": ["-fir", "-iirt", "-lsum", "-ls-fuse", "-ls-sched", "model"],
    "lz":  ["-lazyselect"],
    # cs2 : l'ordonnanceur compositionnel CSSCHEDULE (blocs dominateurs,
    # faisceau de Pareto, budget 1M). Étage 4 (2026-08-13) : paradigma
    # 0.58, pluckedString 0.80, nylonGuitar 0.90, réverbes banques 0.98,
    # pertes <= 3.5% ailleurs. Compile 0.4-10 s : le plus cher du jury.
    "cs2": ["-ss", "11"],
}


def signature(dsp):
    env = dict(os.environ, FAUST_SS_SIG="1")
    r = subprocess.run([FAUST, "-lang", "ocpp", dsp, "-o", os.devnull],
                       env=env, capture_output=True, text=True)
    m = re.search(r"SS_SIG ([^\n]*)", r.stderr)
    if not m:
        sys.exit(f"faustauto: pas de signature (faust a dit : {r.stderr.strip()[:200]})")
    return {k: int(v) for k, v in re.findall(r"(\w+)=(\d+)", m.group(1))}


def candidates(sig):
    """L'élagueur : la signature -> (zone, liste de candidats).

    Depuis la normalisation des letrec (2026-08-09), recmii se mesure sur
    les NIDS VRAIS et l'inventaire fir/iir sépare statiquement les
    ex-jumeaux (vocoder fir=64/iir=0 vs filterBank fir=29/iir=10). Et
    l'étagement structurel -temp 4 est une dimension nouvelle : gains
    ×0.45-0.66 sur cloches/générateurs — le flash-bench le découvre.
    """
    fusion_signal = sig["recmii"] >= 50 or sig["nstreams"] >= 5
    locality = sig["recmii"] >= 45
    order = ["h2", "cs8"] if locality else ["al", "h32"]
    # la dimension -lazyselect ne paie que sur les programmes riches en
    # selects (vocal 0.78, oberheim 0.74) et coûte ailleurs : candidat
    # seulement au-delà du seuil statique
    lazy = ["lz"] if sig.get("nselect", 0) >= 8 else []
    if fusion_signal:
        # les zones sûres embarquent les deux régimes d'ordre (validation
        # 2026-08-08) + le témoin étagé
        # t1fu : le grain SSA sous la fusion -- répare le pire cas de fu
        # (korg35HPF 1.08 -> 0.81) et mène le geomean du jury (0.692)
        # fi : l'algèbre -fir révélée+émise -- gains concentrés
        # (spectralTilt 0.52, korg35HPF 0.72), pertes réverb : le flash-
        # bench arbitre. df partout : la ligne de base de la carte.
        other = "al" if locality else "h2"
        # cs2 sans porte statique (campagne 2026-08-13) : la couche 2
        # arbitre ; une porte informée par les signatures des gagnants
        # pourra venir après la carte
        return "fusion-sûre", ["fu", order[0], other, "t4fu", "t1fu", "df", "cs2", "fi",
                               "fib", "fifu", "fibfu"] + lazy
    return "incertain", ["fu", order[0], order[1], "df", "cs2", "t4", "fi", "fib",
                         "fifu", "fibfu"] + lazy


def compile_candidate(dsp, name, workdir):
    cpp = os.path.join(workdir, f"{name}.cpp")
    r = subprocess.run([FAUST, "-lang", "ocpp", *CAND[name], dsp, "-o", cpp],
                       capture_output=True, text=True)
    if r.returncode != 0 or not os.path.getsize(cpp):
        return None, None
    wrapped = os.path.join(workdir, f"{name}-b.cpp")
    with open(wrapped, "w") as out:
        for part in (BENCH_HEADER, cpp, BENCH_FOOTER):
            out.write(open(part).read())
    binp = os.path.join(workdir, f"{name}-bin")
    r = subprocess.run([CXX, *CXXFLAGS, wrapped, "-o", binp], capture_output=True)
    if r.returncode != 0:
        return cpp, None
    return cpp, binp


def run_once(binp, iters):
    r = subprocess.run([binp, str(iters)], capture_output=True, text=True)
    m = re.findall(r"([0-9.]+) ms", r.stdout)
    return float(m[-1]) if m else None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("dsp")
    ap.add_argument("-o", "--output")
    ap.add_argument("--rounds", type=int, default=2)
    ap.add_argument("--keep", action="store_true", help="garder le dossier de travail")
    a = ap.parse_args()

    t0 = time.time()
    sig = signature(a.dsp)
    zone, cands = candidates(sig)
    print(f"faustauto: zone {zone} ; candidats {cands}")
    print(f"  signature : nodes={sig['nodes']} recmii={sig['recmii']} "
          f"nstreams={sig['nstreams']} bankable={sig['bankablepct']}% top1={sig['top1']}")

    workdir = tempfile.mkdtemp(prefix="faustauto-")
    built = {}
    for name in cands:
        cpp, binp = compile_candidate(a.dsp, name, workdir)
        if binp:
            built[name] = (cpp, binp)
        else:
            print(f"  {name}: échec de construction, écarté")
    if not built:
        sys.exit("faustauto: aucun candidat construit")

    # bench éclair : sonde, puis tours alternés
    iters = {}
    for name, (_, binp) in built.items():
        t = run_once(binp, 3)
        iters[name] = max(10, min(3000, int(300 / max(t, 1e-3)))) if t else 10
    times = {name: [] for name in built}
    for _ in range(a.rounds):
        for name, (_, binp) in built.items():
            t = run_once(binp, iters[name])
            if t is not None:
                times[name].append(t)
    best, score = None, None
    for name in built:
        if times[name]:
            m = min(times[name])
            print(f"  {name:<4} {m:.4f} ms")
            if score is None or m < score:
                best, score = name, m
    print(f"faustauto: gagnant {best} ({score:.4f} ms) — options : "
          f"{' '.join(CAND[best])}  [{time.time()-t0:.1f} s]")
    if a.output:
        with open(a.output, "w") as out:
            out.write(open(built[best][0]).read())
        print(f"faustauto: émis dans {a.output}")
    if not a.keep:
        import shutil
        shutil.rmtree(workdir, ignore_errors=True)


if __name__ == "__main__":
    main()
