#!/usr/bin/env python3
"""Heat-maps of the efficiency of one family over its (x, y) grid, one map
per measured leg, plus the map of the best leg (and, given an elections
tsv, the elected option set and its efficiency).

  usage : heatmap.py results.tsv [--family m] [--elections elect.tsv] [--out dir]

Efficiency = nanoseconds per frame per unit of the family's work (m :
filters S*P, r : stages + taps, d : delays, t : readers, w : B*L). Every map
shares one colour scale, so a lighter cell is a cheaper filter whatever the
leg. The elections tsv has the columns name, winner label, winner ns and
the elected option set (fcautotool output collected by elect.sh)."""
import sys, argparse, math, collections
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np

UNITS = {"m": ("filters S×P", lambda x, y: x * y), "r": ("stages + taps", lambda x, y: x + y),
         "d": ("delays", lambda x, y: x), "t": ("readers", lambda x, y: x), "w": ("multiply-adds B×L", lambda x, y: x * y)}
AXES = {"m": ("P (width)", "S (depth)"), "r": ("K (taps)", "D (stages)"), "d": ("V (kind)", "N (delays)"),
        "t": ("Z (delay + 1)", "N (readers)"), "w": ("L (stages)", "B (generators)")}

def load(path):
    rows = [l.rstrip("\n").split("\t") for l in open(path)]
    head, rows = rows[0], rows[1:]
    legs = [h[3:] for h in head if h.startswith("ns_")]
    data = {}
    for r in rows:
        d = dict(zip(head, r))
        try:
            data[d["name"]] = {l: float(d["ns_" + l]) for l in legs}
        except ValueError:
            pass
    return legs, data

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("results"); ap.add_argument("--family", default="m")
    ap.add_argument("--elections", default=None); ap.add_argument("--out", default=".")
    a = ap.parse_args()
    legs, data = load(a.results)
    f = a.family; unit, work = UNITS[f]; xl, yl = AXES[f]
    ys = sorted({int(n[1]) for n in data if n[0] == f}); xs = sorted({int(n[2]) for n in data if n[0] == f})
    grids = {}
    for l in legs:
        g = np.full((len(ys), len(xs)), np.nan)
        for i, y in enumerate(ys):
            for j, x in enumerate(xs):
                n = "%s%d%d" % (f, y, x)
                if n in data and l in data[n]:
                    g[i, j] = data[n][l] / work(y, x)
        grids[l] = g
    elect = None
    if a.elections:
        elect = {}
        for r in [l.rstrip("\n").split("\t") for l in open(a.elections)][1:]:
            try:
                elect[r[0]] = (r[1], float(r[2]), r[3])
            except (ValueError, IndexError):
                pass
        g = np.full((len(ys), len(xs)), np.nan); lab = np.full((len(ys), len(xs)), "", dtype=object)
        for i, y in enumerate(ys):
            for j, x in enumerate(xs):
                n = "%s%d%d" % (f, y, x)
                if n in elect:
                    g[i, j] = elect[n][1] / work(y, x); lab[i, j] = elect[n][0]
        grids["elected"] = g
    best = np.full((len(ys), len(xs)), np.nan); bestlab = np.full((len(ys), len(xs)), "", dtype=object)
    for i in range(len(ys)):
        for j in range(len(xs)):
            cands = [(grids[l][i, j], l) for l in grids if not np.isnan(grids[l][i, j])]
            if cands:
                best[i, j], bestlab[i, j] = min(cands)
    vals = np.concatenate([g[~np.isnan(g)] for g in grids.values()] + [best[~np.isnan(best)]])
    vmin, vmax = np.nanmin(vals), np.nanmax(vals)
    panels = list(grids.items()) + [("best of all", best)]
    ncol = 3; nrow = math.ceil(len(panels) / ncol)
    fig, axs = plt.subplots(nrow, ncol, figsize=(5.2 * ncol, 4.6 * nrow), squeeze=False)
    for k, (name, g) in enumerate(panels):
        ax = axs[k // ncol][k % ncol]
        im = ax.imshow(g, cmap="viridis_r", vmin=vmin, vmax=vmax, origin="lower")
        ax.set_xticks(range(len(xs))); ax.set_xticklabels(xs); ax.set_yticks(range(len(ys))); ax.set_yticklabels(ys)
        ax.set_xlabel(xl); ax.set_ylabel(yl); ax.set_title(name)
        for i in range(len(ys)):
            for j in range(len(xs)):
                if not np.isnan(g[i, j]):
                    txt = "%.2f" % g[i, j]
                    if name == "best of all":
                        txt = bestlab[i, j]
                    elif name == "elected" and elect is not None:
                        txt = lab[i, j]
                    ax.text(j, i, txt, ha="center", va="center", fontsize=6, color="white" if g[i, j] > (vmin + vmax) / 2 else "black")
    for k in range(len(panels), nrow * ncol):
        axs[k // ncol][k % ncol].axis("off")
    fig.colorbar(im, ax=axs.ravel().tolist(), shrink=0.6, label="ns per frame per %s" % unit)
    fig.suptitle("family %s : efficiency, ns per frame per %s (lighter = cheaper)" % (f, unit))
    out = "%s/heatmap-%s.png" % (a.out, f)
    fig.savefig(out, dpi=130, bbox_inches="tight")
    print("wrote", out)
    # the text summary : which leg is best where
    counts = collections.Counter(bestlab[i, j] for i in range(len(ys)) for j in range(len(xs)) if bestlab[i, j])
    print("best leg per cell :", dict(counts))

if __name__ == "__main__":
    main()
