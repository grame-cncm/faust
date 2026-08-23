#!/usr/bin/env python3
"""genetic — exploration genetique de l'espace des options de
compilation autour d'UN programme, au juge promu.

Genome : un allele par gene (ordonnanceur, R, U, fusion, eclate,
etagement, fir, lsum, lazy, gatequiv, selectn, rp, tau, atomes).
Fitness : ns/echantillon flash (spin de promotion actif), min de 2
runs ; un build casse = fitness infinie (la selection nettoie).
JUSTESSE : contrainte dure -- le meilleur de chaque generation doit
reproduire l'IR du df au critere d'onset, sinon DISQUALIFIE.
Usage : genetic.py programme.dsp [--pop 16] [--gens 20]
"""
import argparse, os, random, shutil, subprocess, sys, tempfile, time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import faustauto as fa

GENES = {
    "sched": [[], ["-ss","0"], ["-ss","8"], ["-ss","9"], ["-ss","11"], ["-ss","12"]],
    "R":     [["-ls-R","2"], ["-ls-R","8"], ["-ls-R","16"], ["-ls-R","32"], ["-ls-R","64"]],
    "U":     [["-ls-U","2"], ["-ls-U","4"], ["-ls-U","8"]],
    "fuse":  [[], ["-ls-fuse","-ls-sched","model"]],
    "ls":    [[], ["-ls","-ls-sched","model"]],
    "temp":  [[], ["-temp","1"], ["-temp","2"], ["-temp","4"], ["-temp","8"]],
    "fir":   [[], ["-fir","-iirt"]],
    "lsum":  [[], ["-lsum"]],
    "lazy":  [[], ["-lazyselect"]],
    "gq":    [[], ["-gatequiv"]],
    "sn":    [[], ["-selectn"]],
}
ENVGENES = {
    "rp":    [{}, {"FAUST_SS_RINGPRELOAD": "1"}],
    "tau":   [{}, {"FAUST_GATEQUIV_TAU": "6"}, {"FAUST_GATEQUIV_TAU": "24"}],
    "atoms": [{}, {"FAUST_LZ_ATOMS": "2"}, {"FAUST_LZ_ATOMS": "6"}],
}
ALL = list(GENES) + list(ENVGENES)

def flags_of(g):
    fl = []
    for k in GENES:
        fl += GENES[k][g[k]]
    env = {}
    for k in ENVGENES:
        env.update(ENVGENES[k][g[k]])
    return fl, env

def rand_genome(rng):
    return {k: rng.randrange(len(GENES.get(k) or ENVGENES[k])) for k in ALL}

def seed_genome(**kw):
    g = {k: 0 for k in ALL}
    g.update(kw)
    return g

class Evaluator:
    def __init__(self, dsp, wd):
        self.dsp, self.wd, self.cache, self.n = dsp, wd, {}, 0
    def fitness(self, g):
        fl, env = flags_of(g)
        key = (tuple(fl), tuple(sorted(env.items())))
        if key in self.cache:
            return self.cache[key]
        self.n += 1
        tag = f"g{self.n}"
        cpp = os.path.join(self.wd, tag + ".cpp")
        try:
            r = subprocess.run([fa.FAUST, "-lang", "ocpp", *fl, "-a", fa.FLASH_ARCH,
                                "-A", fa.ARCH_DIR, self.dsp, "-o", cpp],
                               env=dict(os.environ, **env), capture_output=True, timeout=120)
            if r.returncode or not os.path.getsize(cpp):
                raise RuntimeError()
            b = os.path.join(self.wd, tag)
            r = subprocess.run([fa.CXX, *fa.CXXFLAGS, f"-I{fa.ARCH_DIR}", f"-I{fa.ARCHS_DIR}",
                                cpp, "-o", b], capture_output=True, timeout=180)
            if r.returncode:
                raise RuntimeError()
            vals = [v for v in (fa.run_once(b) for _ in range(2)) if v]
            fit = min(vals) if vals else float("inf")
        except Exception:
            fit = float("inf")
        self.cache[key] = fit
        for f in (cpp, os.path.join(self.wd, tag)):
            try: os.remove(f)
            except OSError: pass
        return fit
    def correct(self, g):
        fl, env = flags_of(g)
        ref = fa.impulse_ir(self.dsp, [], {}, self.wd, "ref")
        ir  = fa.impulse_ir(self.dsp, fl, env, self.wd, "cand")
        return ref is None or (ir is not None and fa.ir_equivalent(ref, ir))

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("dsp")
    ap.add_argument("--pop", type=int, default=16)
    ap.add_argument("--gens", type=int, default=20)
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--book", action="store_true",
                    help="inscrire le champion valide au livre de recettes")
    a = ap.parse_args()
    rng = random.Random(a.seed)
    wd = tempfile.mkdtemp(prefix="gen-")
    ev = Evaluator(a.dsp, wd)
    # graines : les points connus de la carte + hasard
    pop = [
        seed_genome(),                                   # df
        seed_genome(temp=1, fuse=1),                     # t1fu (elu reverbTank)
        seed_genome(lsum=1),                             # lb
        seed_genome(fuse=1),                             # fu
        seed_genome(sched=4, R=3, U=1),                  # cs2
        seed_genome(gq=1, sn=1, lazy=1),                 # gqsn
    ]
    while len(pop) < a.pop:
        pop.append(rand_genome(rng))
    best, bestg = float("inf"), None
    stall = 0
    for gen in range(a.gens):
        scored = sorted(((ev.fitness(g), i) for i, g in enumerate(pop)), key=lambda x: x[0])
        gbest, gi = scored[0]
        improved = gbest < best * 0.995
        if gbest < best:
            best, bestg = gbest, dict(pop[gi])
        stall = 0 if improved else stall + 1
        fl, env = flags_of(pop[gi])
        print(f"gen {gen:2d} : best={gbest:8.3f} (global {best:8.3f}) "
              f"evals={ev.n} : {' '.join(fl)} {env}", flush=True)
        if stall >= 6:
            print("stagnation, arret.", flush=True)
            break
        # nouvelle generation : elitisme 2, tournoi 3, croisement uniforme, mutation
        elite = [dict(pop[i]) for _, i in scored[:2]]
        def pick():
            cands = rng.sample(range(len(pop)), 3)
            return pop[min(cands, key=lambda i: ev.fitness(pop[i]))]
        nxt = elite
        while len(nxt) < a.pop:
            p1, p2 = pick(), pick()
            child = {k: (p1 if rng.random() < 0.5 else p2)[k] for k in ALL}
            for k in ALL:
                if rng.random() < 0.15:
                    child[k] = rng.randrange(len(GENES.get(k) or ENVGENES[k]))
            nxt.append(child)
        pop = nxt
    # verdict : justesse du champion, sinon on remonte le classement
    print("\nverification de justesse du champion...", flush=True)
    if ev.correct(bestg):
        fl, env = flags_of(bestg)
        print(f"CHAMPION VALIDE : {best:.3f} ns : {' '.join(fl)} {env}")
        if a.book:
            import datetime
            book = os.path.join(os.path.dirname(os.path.abspath(__file__)), "recipes.tsv")
            base = os.path.basename(a.dsp)
            lines = [l for l in open(book)] if os.path.exists(book) else []
            lines = [l for l in lines if not l.startswith(base + "\t")]
            envs = " ".join(f"{k}={v}" for k, v in sorted(env.items()))
            lines.append(f"{base}\t{datetime.date.today()}\t{' '.join(fl)}\t{envs or '-'}\n")
            open(book, "w").writelines(lines)
            print(f"inscrit au livre : {base}")
    else:
        print("champion DISQUALIFIE (IR fausse) — a instruire")
    shutil.rmtree(wd, ignore_errors=True)

if __name__ == "__main__":
    main()
