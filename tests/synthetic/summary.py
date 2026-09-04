#!/usr/bin/env python3
"""Summary of a bench results.tsv : per family, the ocpp/cpp ratio (geomean,
best, worst), the medians, and the efficiency per unit of work of each
backend (nanoseconds per frame and per unit) with the most and least
efficient tests. The unit of work is the family's own : m filters (S*P),
r stages + taps (D+K), d delays (N), t table readers (N), w multiply-adds
(B*L).   usage : summary.py results.tsv [family-regex]"""
import sys, re, math, collections

UNITS = {"m": ("filters", lambda x, y: x * y),
         "r": ("stages+taps", lambda x, y: x + y),
         "d": ("delays", lambda x, y: x),
         "t": ("readers", lambda x, y: x),
         "w": ("multiply-adds", lambda x, y: x * y)}

def main(path, pat=None):
    rows = [l.rstrip("\n").split("\t") for l in open(path)][1:]
    fam = collections.defaultdict(list)
    for r in rows:
        if pat and not re.match(pat, r[0]):
            continue
        try:
            name, c, o = r[0], float(r[4]), float(r[5])
        except (ValueError, IndexError):
            continue
        f, x, y = name[0], int(name[1]), int(name[2])
        unit, work = UNITS.get(f, ("units", lambda x, y: 1))
        w = work(x, y)
        fam[f].append((name, c, o, o / c, c / w, o / w, w))
    print("family\tn\tgeomean ocpp/cpp\tbest (ocpp faster)\tworst (ocpp slower)\tmedian ns cpp\tmedian ns ocpp")
    for f in sorted(fam):
        v = fam[f]
        g = math.exp(sum(math.log(t[3]) for t in v) / len(v))
        b = min(v, key=lambda t: t[3]); wst = max(v, key=lambda t: t[3])
        mc = sorted(t[1] for t in v)[len(v) // 2]; mo = sorted(t[2] for t in v)[len(v) // 2]
        print("%s\t%d\t%.3f\t%s %.3f\t%s %.3f\t%.2f\t%.2f" % (f, len(v), g, b[0], b[3], wst[0], wst[3], mc, mo))
    print("\nefficiency : ns per frame and per unit of work (the family's unit)")
    print("family\tunit\tbackend\tmost efficient\tleast efficient\tmedian")
    for f in sorted(fam):
        v = fam[f]; unit = UNITS.get(f, ("units",))[0]
        for i, lab in ((4, "cpp"), (5, "ocpp")):
            s = sorted(v, key=lambda t: t[i])
            med = sorted(t[i] for t in v)[len(v) // 2]
            print("%s\t%s\t%s\t%s %.2f\t%s %.2f\t%.2f" % (f, unit, lab, s[0][0], s[0][i], s[-1][0], s[-1][i], med))

if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2] if len(sys.argv) > 2 else None)
