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
# La couche 2 juge au JUGE UNIQUE de la carte (decision du 2026-08-16) :
# arch flashbench (blocs de 512, entree LCG, min des repetitions), float,
# -O3 -ffast-math -march=native. L'ancien bencharch (bloc d'1 s, protocole
# min-stable) divergeait du juge de reference jusqu'a x2.7 sur un meme
# binaire (quantizedChords) : les elections doivent etre rendues par le
# juge qui fait foi, pas par un cousin.
FAUST_ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
FLASH_ARCH = os.path.join(FAUST_ROOT, "tests", "impulse-tests", "archs", "flashbench.cpp")
ARCH_DIR   = os.path.join(FAUST_ROOT, "architecture")
ARCHS_DIR  = os.path.join(FAUST_ROOT, "tests", "impulse-tests", "archs")
FLASH_ENV  = {"FLASH_REPS": "10", "FLASH_BLOCKS": "100", "FLASH_WARM": "120"}
# Le compilateur C++ fait partie du juge : "clang++" resolvait vers le
# LLVM MacPorts 22 quand la carte etait jugee par l'Apple clang de
# /usr/bin/c++ -- x2.6 d'ecart sur quantizedChords, et des builds
# sensibles au layout. Le juge epingle le binaire, pas un nom.
CXX = os.environ.get("FAUSTAUTO_CXX", "/usr/bin/c++")
CXXFLAGS = os.environ.get("FAUSTAUTO_CXXFLAGS",
                          "-O3 -ffast-math -march=native -fbracket-depth=1024").split()

# la nomenclature officielle (MODES.md §7)
CAND = {
    "fu":  ["-ls-fuse", "-ls-sched", "model"],
    # ls : l'eclate NU, sans fusion -- le grain fin. Decouvert absent du
    # jury le 2026-08-16 : sur quantizedChords (20 oscillateurs a table
    # independants) fu fait 2.1x PIRE que df la ou ls fait 25% MIEUX --
    # l'oracle de fusion sous-pese la forme des corps. ls est le candidat
    # des bancs de chaines independantes.
    "ls":  ["-ls", "-ls-sched", "model"],
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
    "lzh": ["-lazyselect", "-ss", "9", "-ls-R", "32", "-ls-U", "4"],
    "gq":  ["-gatequiv"],
    "gqlz": ["-gatequiv", "-lazyselect"],
    "lb":  ["-lsum"],
    # cs2 : l'ordonnanceur compositionnel CSSCHEDULE (blocs dominateurs,
    # faisceau de Pareto, budget 1M), en PAIRE d'épines depuis la carte
    # (R,U) x 2 épines du 2026-08-13 : le défaut (20,4) n'était optimal
    # nulle part. cs2 = épine df à (32,4) (greyhole 3.53, pluckedString
    # 6.77) ; cs2b = épine bf à (32,8) (paradigma 2.76 record x0.51,
    # fdnRev 12.21). Compile 0.4-10 s chacun : les plus chers du jury.
    "cs2":  ["-ss", "11", "-ls-R", "32", "-ls-U", "4"],
    "cs2b": ["-ss", "12", "-ls-R", "32", "-ls-U", "8"],
    # rp : le prechargement des lectures d'anneau (df + env) -- les loads
    # partent en rafale en tete du corps de boucle, mouvement de registre
    # au slot d'origine. Prouve par compteurs sur freeverb (stalls -43%),
    # candidat par-programme (zitaRev 1.03 : jamais un defaut).
    "rp":   ["-ss", "0"],
}

# les candidats portes par une variable d'environnement plutot que des
# drapeaux (le compilateur est invoque avec cet environnement en plus)
CAND_ENV = {
    "rp": {"FAUST_SS_RINGPRELOAD": "1"},
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
    lazy = ["lz", "lzh", "gq", "gqlz"] if sig.get("nselect", 0) >= 8 else []
    lazy += ["lb"]  # -lsum autonome (2026-08-18) : la factorisation polynomiale
                    # des sommes, decouplee de -fir -- old_freeverb 133->65 adds
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
        return "fusion-sûre", ["fu", "ls", order[0], other, "t4fu", "t1fu", "df", "rp", "cs2", "cs2b",
                               "fi", "fib", "fifu", "fibfu"] + lazy
    return "incertain", ["fu", "ls", order[0], order[1], "df", "rp", "cs2", "cs2b", "t4", "fi", "fib",
                         "fifu", "fibfu"] + lazy


def compile_candidate(dsp, name, workdir):
    cpp = os.path.join(workdir, f"{name}.cpp")
    env = dict(os.environ, **CAND_ENV.get(name, {}))
    r = subprocess.run([FAUST, "-lang", "ocpp", *CAND[name],
                        "-a", FLASH_ARCH, "-A", ARCH_DIR, dsp, "-o", cpp],
                       env=env, capture_output=True, text=True)
    if r.returncode != 0 or not os.path.getsize(cpp):
        return None, None
    binp = os.path.join(workdir, f"{name}-bin")
    r = subprocess.run([CXX, *CXXFLAGS, f"-I{ARCH_DIR}", f"-I{ARCHS_DIR}", cpp, "-o", binp],
                       capture_output=True)
    if r.returncode != 0:
        return cpp, None
    return cpp, binp


FAUST_DIR = os.path.normpath(os.path.join(os.path.dirname(__file__), "../.."))
IMPULSE_ARCH = os.path.join(FAUST_DIR, "tests/impulse-tests/archs/impulsearch.cpp")
# harnais 17 chiffres pour la porte : a 6 decimales, un onset d'ulp est
# invisible pendant 30k echantillons puis surgit comme une fausse
# divergence finie -- le critere d'onset exige la pleine precision
HIPREC_DIR = os.path.join(tempfile.gettempdir(), "faustauto-hiprec")
def _ensure_hiprec():
    os.makedirs(HIPREC_DIR, exist_ok=True)
    dst = os.path.join(HIPREC_DIR, "controlTools.h")
    if not os.path.exists(dst):
        src = open(os.path.join(FAUST_DIR, "tests/impulse-tests/archs/controlTools.h")).read()
        open(dst, "w").write(src.replace("%8.6f", "%.17g"))
    return HIPREC_DIR
NUMRE = re.compile(r"-?\d+\.?\d*(?:[eE][+-]?\d+)?")

def impulse_ir(dsp, flags, env, workdir, tag):
    """Reponse impulsionnelle -double (60000 ech.) ; None si inconstructible."""
    cpp = os.path.join(workdir, f"ir-{tag}.cpp")
    r = subprocess.run([FAUST, "-lang", "ocpp", "-double", *flags, "-i", "-A",
                        os.path.join(FAUST_DIR, "architecture"), "-a", IMPULSE_ARCH,
                        dsp, "-o", cpp], env=dict(os.environ, **env), capture_output=True)
    if r.returncode:
        return None
    b = os.path.join(workdir, f"ir-{tag}")
    r = subprocess.run(["/usr/bin/c++", "-O2", "-std=c++17", "-I" + _ensure_hiprec(),
                        "-I" + os.path.join(FAUST_DIR, "architecture"),
                        "-I" + os.path.join(FAUST_DIR, "tests/impulse-tests/archs"),
                        cpp, "-o", b], capture_output=True)
    if r.returncode:
        return None
    r = subprocess.run([b, "-n", "60000"], capture_output=True, text=True)
    return r.stdout if r.returncode == 0 and r.stdout.strip() else None

def ir_equivalent(a, b, onset_tol=1e-11):
    """Critere d'ONSET (verdict du 2026-08-18, famille des echelles VA) :
    ce qui compte est la PREMIERE divergence. Classe ulp (< onset_tol
    relatif) = reassociation flottante legale ; la suite peut diverger
    librement -- les filtres VA resonnants amplifient un ulp jusqu'a
    ~2.0 relatif en 30k echantillons (Lyapunov positif), sans qu'aucune
    arithmetique soit fausse. Une divergence FINIE d'entree (le cas
    dup/gate_compressor : rel ~1 a l'echantillon 0) = miscompilation,
    rejetee. NaN/inf naissants = rejet."""
    if a == b:
        return True
    la, lb = a.splitlines(), b.splitlines()
    if len(la) != len(lb):
        return False
    for x, y in zip(la, lb):
        if x == y:
            continue
        na, nb = NUMRE.findall(x), NUMRE.findall(y)
        if len(na) != len(nb):
            return False
        for u, v in zip(na, nb):
            if 'nan' in u or 'nan' in v or 'inf' in u or 'inf' in v:
                return u == v
            fu, fv = float(u), float(v)
            d = abs(fu - fv)
            if d == 0.0:
                continue
            # premiere divergence trouvee : classe-t-elle ulp ?
            return d <= onset_tol * max(abs(fu), abs(fv), 1e-30)
    return True

def run_once(binp, iters=None):
    r = subprocess.run([binp], env=dict(os.environ, **FLASH_ENV),
                       capture_output=True, text=True)
    m = re.match(r"([0-9.]+)", r.stdout)
    return float(m.group(1)) if m else None


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

    # bench éclair : protocole uniforme du juge (min de 10 répétitions de
    # 100 blocs de 512), tours alternés. PAUSE THERMIQUE d'abord : la
    # phase de compilation (20+ candidats à -O3) chauffe la machine et
    # polluait le premier tour (leçon co-mesure ; lfBoost V4, highShelf/
    # lowCut V5 : des ls à 2.28 mesurés 4.45 et perdants).
    time.sleep(6)
    times = {name: [] for name in built}
    for _ in range(a.rounds):
        for name, (_, binp) in built.items():
            t = run_once(binp)
            if t is not None:
                times[name].append(t)
    # RE-COURSE DU PODIUM : min-de-2 est fragile aux pointes, et seule la
    # tête compte. Repêchage LARGE : tout candidat à moins de 2x du
    # meneur provisoire regagne 4 tours alternés — un vrai vainqueur
    # pollué d'un facteur 2 (ls sur les filtres : 2.28 mesuré 4.45)
    # reste repêchable. Plafond 8 pour borner le coût.
    ranked = sorted((n for n in built if times[n]), key=lambda n: min(times[n]))
    lead   = min(times[ranked[0]]) if ranked else 0.0
    podium = [n for n in ranked if min(times[n]) <= 2.0 * lead][:8]
    for _ in range(4):
        for name in podium:
            t = run_once(built[name][1])
            if t is not None:
                times[name].append(t)
    for name in built:
        if times[name]:
            print(f"  {name:<4} {min(times[name]):.4f} ns")
    # PORTE DE JUSTESSE (leçon dbmeter, famille des échelles VA) : les
    # élections mesurent la vitesse, jamais la justesse — un candidat
    # faux-mais-rapide gagnerait. L'élu doit reproduire la réponse
    # impulsionnelle du df (au bit, ou réassociation < 1e-9 relatif) ;
    # sinon DISQUALIFIÉ, au suivant. df lui-même est toujours accepté.
    ref_ir = impulse_ir(a.dsp, [], {}, workdir, "ref")
    ranked2 = sorted((n for n in built if times[n]), key=lambda n: min(times[n]))
    best, score = None, None
    for name in ranked2:
        if name == "df" or ref_ir is None:
            best, score = name, min(times[name])
            break
        el_ir = impulse_ir(a.dsp, CAND[name], CAND_ENV.get(name, {}), workdir, name)
        if el_ir is not None and ir_equivalent(ref_ir, el_ir):
            best, score = name, min(times[name])
            break
        print(f"  {name}: DISQUALIFIÉ (réponse impulsionnelle fausse)")
    if best is None and ranked2:
        best, score = "df" if "df" in built else ranked2[0], min(times["df" if "df" in built else ranked2[0]])
    print(f"faustauto: gagnant {best} ({score:.4f} ns/éch.) — options : "
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
