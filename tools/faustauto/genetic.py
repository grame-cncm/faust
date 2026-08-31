#!/usr/bin/env python3
"""genetic — genetic exploration of the compilation-option space
around ONE program, under the promoted judge.

Genome: one allele per gene (scheduler, R, U, fusion, split,
staging, fir, lsum, lazy, gatequiv, selectn, rp, tau, atoms).
Fitness: flash ns/sample (promotion spin active), min of 2 runs;
a broken build = infinite fitness (selection cleans it out).
CORRECTNESS: hard constraint -- the best of each generation must
reproduce df's IR under the onset criterion, or be DISQUALIFIED.
Usage: genetic.py program.dsp [--pop 16] [--gens 20]
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

def rand_genome(rng, free):
    # locked genes stay at allele 0 (their "off"/default form)
    return {k: (rng.randrange(len(GENES.get(k) or ENVGENES[k])) if k in free else 0) for k in ALL}

def seed_genome(**kw):
    g = {k: 0 for k in ALL}
    g.update(kw)
    return g

class Evaluator:
    def __init__(self, dsp, wd, runs=2):
        self.dsp, self.wd, self.cache, self.n, self.runs = dsp, wd, {}, 0, runs
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
            vals = [v for v in (fa.run_once(b) for _ in range(self.runs)) if v]
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
    ap.add_argument("--mut", type=float, default=0.15, help="per-gene mutation probability")
    ap.add_argument("--elite", type=int, default=2, help="genomes carried over unchanged")
    ap.add_argument("--tourney", type=int, default=3, help="tournament size for parent selection")
    ap.add_argument("--stall", type=int, default=6,
                    help="stop after N generations without real progress")
    ap.add_argument("--runs", type=int, default=2, help="flash runs per fitness (the min is kept)")
    ap.add_argument("--genes", default=None,
                    help="comma list restricting the searched genes, e.g. sched,R,U,fuse "
                         "(the others stay locked at their off/default allele)")
    ap.add_argument("--book", action="store_true",
                    help="inscrire le champion valide au livre de recettes")
    a = ap.parse_args()
    free = set(ALL)
    if a.genes:
        free = {g.strip() for g in a.genes.split(",") if g.strip()}
        unknown = free - set(ALL)
        if unknown:
            sys.exit(f"genetic: unknown gene(s) {sorted(unknown)} ; available: {ALL}")
    rng = random.Random(a.seed)
    wd = tempfile.mkdtemp(prefix="gen-")
    ev = Evaluator(a.dsp, wd, runs=a.runs)
    # seeds: the known points of the map + randomness
    pop = [
        seed_genome(),                                   # df
        seed_genome(temp=1, fuse=1),                     # t1fu (reverbTank winner)
        seed_genome(lsum=1),                             # lb
        seed_genome(fuse=1),                             # fu
        seed_genome(sched=4, R=3, U=1),                  # cs2
        seed_genome(gq=1, sn=1, lazy=1),                 # gqsn
    ]
    if a.genes:
        # a restricted search space also restricts the seeds
        for g in pop:
            for k in ALL:
                if k not in free:
                    g[k] = 0
    while len(pop) < a.pop:
        pop.append(rand_genome(rng, free))
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
        if stall >= a.stall:
            print("stagnation, arret.", flush=True)
            break
        # next generation: elitism, tournament, uniform crossover, mutation
        elite = [dict(pop[i]) for _, i in scored[:a.elite]]
        def pick():
            cands = rng.sample(range(len(pop)), a.tourney)
            return pop[min(cands, key=lambda i: ev.fitness(pop[i]))]
        nxt = elite
        while len(nxt) < a.pop:
            p1, p2 = pick(), pick()
            child = {k: (p1 if rng.random() < 0.5 else p2)[k] for k in ALL}
            for k in ALL:
                if k in free and rng.random() < a.mut:
                    child[k] = rng.randrange(len(GENES.get(k) or ENVGENES[k]))
            nxt.append(child)
        pop = nxt
    # verdict: correctness of the champion, else walk back up the ranking
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
