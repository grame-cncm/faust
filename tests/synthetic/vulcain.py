#!/usr/local/bin/python3
"""vulcain -- forge, from faust's own single-chain kernel bodies, the chain-major loop
structure of a filter matrix : P chains of S filters, k chains interleaved per loop,
P/k loops, the family's wiring (m : P in P out ; i : one input fanned out ; o : P in,
outputs accumulated into one ; x : one in, one out). The prototype of a fusion oracle
that cuts by chain rather than by stage.

  vulcain.py --family m --S 9 --P 9 --k 1 [--float] [--arch bench_arch.cpp] -o out.cpp
"""
import argparse, os, re, subprocess, sys, tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
FAUST = os.environ.get("FAUST", os.path.join(HERE, "../../build/bin/faust"))

ap = argparse.ArgumentParser()
ap.add_argument("--family", choices="miox", default="m"); ap.add_argument("--S", type=int, default=3)
ap.add_argument("--P", type=int, default=3); ap.add_argument("--k", type=int, default=1)
ap.add_argument("--float", action="store_true"); ap.add_argument("--arch", default="bench_arch.cpp")
ap.add_argument("--kernels", default="-fir -iirt -lsum", help="faust options for the chain bodies")
ap.add_argument("-o", required=True)
a = ap.parse_args()
prec = [] if a.float else ["-double"]
work = tempfile.mkdtemp(prefix="vulcain-")

def chain_source(S, j):
    return ('import("stdfaust.lib");\nf(i,j) = fi.resonlp(30+500*i+50*j,5,1);\n'
            'process = seq(i, %d, f(i, %d));\n' % (S, j))

def faust(dsp, out, arch=None):
    cmd = [FAUST, "-lang", "ocpp", *prec, *a.kernels.split(), "-t", "0"] + (["-a", arch] if arch else []) + [dsp, "-o", out]
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0: sys.exit("faust failed on %s : %s" % (dsp, r.stderr[:200]))

# 1. the P chain classes, members made public, class renamed
chains = []
for j in range(a.P):
    dsp = os.path.join(work, "chain%d.dsp" % j); open(dsp, "w").write(chain_source(a.S, j))
    cpp = os.path.join(work, "chain%d.cpp" % j); faust(dsp, cpp)
    src = open(cpp).read()
    m = re.search(r"class mydsp : public dsp \{.*?\n\};", src, re.S)
    if not m: sys.exit("no class in chain %d" % j)
    cls = m.group(0)
    body = cls.split("\n", 1)[1]
    cls = "class chain%d : public dsp {\n  public:\n" % j + body.replace("  private:\n", "", 1)
    cls = cls.replace("virtual mydsp* clone()", "virtual chain%d* clone()" % j).replace("return new mydsp()", "return new chain%d()" % j)
    # members : names declared at class scope (before the first 'public:' method), locals : declared in compute
    decl_zone = cls.split("virtual void metadata", 1)[0]
    members = set()   # declaration lines only : the comments of that zone name locals of compute
    for l in decl_zone.split("\n"):
        d = re.match(r"\s*(?:double|float|int|FAUSTFLOAT)\s+\t?(\w+)", l)
        if d: members.add(d.group(1))
    cm = re.search(r"\tvirtual void compute \(int count, FAUSTFLOAT\*\* input, FAUSTFLOAT\*\* output\) \{\n(.*?)\n\t\}", cls, re.S)
    if not cm: sys.exit("no compute in chain %d" % j)
    lines = cm.group(1).split("\n")
    locals_ = set()
    for l in lines:
        d = re.match(r"\s*(?:double|float|int|FAUSTFLOAT)\s+\t?(\w+)", l)
        if d and d.group(1) not in ("index",): locals_.add(d.group(1))
    # split compute : declarations / prologue / loop body / epilogue
    decls, pro, loop, epi = [], [], [], []
    state = "decl"
    for l in lines:
        s = l.strip()
        if state == "decl":
            if re.match(r"(double|float|int)\s+\t?\w+\[\d+\];", s): decls.append(s); continue
            if s.startswith("const int index") or s.startswith("FAUSTFLOAT* input0") or s.startswith("FAUSTFLOAT* output0") or s.startswith("// schedule"): continue
            state = "pro"
        if state == "pro":
            if s.startswith("for (int i=0; i<count; i++) {"): state = "loop"; continue
            pro.append(s); continue
        if state == "loop":
            if l == "\t\t}": state = "epi"; continue
            loop.append(s); continue
        epi.append(s)
    def rename(s):
        def sub(m):
            n = m.group(0)
            if n in locals_: return "%s_%d" % (n, j)   # a local of compute shadows a member of the same name
            if n in members: return "c%d.%s" % (j, n)
            return n
        return re.sub(r"\b([fi][A-Z]\w*|IOTA|vIota\d+|idx\w+)\b", sub, s)
    chains.append(dict(cls=cls, decls=[rename(x) for x in decls], pro=[rename(x) for x in pro],
                       loop=[rename(x) for x in loop], epi=[rename(x) for x in epi]))

# 2. the wiring of the family
fam = a.family
nin = a.P if fam in "mo" else 1
nout = a.P if fam in "mi" else 1
def wire(j, first, s):
    s = s.replace("input0[i]", "input%d[i]" % (j if fam in "mo" else 0))
    m = re.match(r"output0\[i\] = \(FAUSTFLOAT\)\((.*)\);\s*// Zone Exec Code", s)
    if m:
        e = m.group(1)
        if fam in "mi": return "output%d[i] = (FAUSTFLOAT)(%s);" % (j, e)
        return "output0[i] %s (FAUSTFLOAT)(%s);" % ("=" if first else "+=", e)
    return s

groups = [list(range(g, min(g + a.k, a.P))) for g in range(0, a.P, a.k)]
out = []
out.append("// forged by vulcain : family %s, S=%d, P=%d, k=%d chains per loop, %d loops, chain bodies %s\n" % (fam, a.S, a.P, a.k, len(groups), a.kernels))
for c in chains: out.append(c["cls"] + "\n")
out.append("class mydsp : public dsp {\n  public:\n")
for j in range(a.P): out.append("\tchain%d c%d;\n" % (j, j))
out.append("\tvirtual void metadata(Meta* m) { m->declare(\"name\", \"vulcain\"); }\n")
out.append("\tvirtual int getNumInputs() { return %d; }\n\tvirtual int getNumOutputs() { return %d; }\n" % (nin, nout))
for meth in ("instanceConstants", "instanceInit", "init"):
    out.append("\tvirtual void %s(int sr) { %s }\n" % (meth, " ".join("c%d.%s(sr);" % (j, meth) for j in range(a.P))))
for meth in ("instanceResetUserInterface", "instanceClear"):
    out.append("\tvirtual void %s() { %s }\n" % (meth, " ".join("c%d.%s();" % (j, meth) for j in range(a.P))))
out.append("\tvirtual int getSampleRate() { return c0.getSampleRate(); }\n\tvirtual mydsp* clone() { return new mydsp(); }\n")
out.append("\tvirtual void buildUserInterface(UI* ui) { (void)ui; }\n")
out.append("\tvirtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {\n")
for c in range(nin): out.append("\t\tFAUSTFLOAT* input%d = input[%d];\n" % (c, c))
for c in range(nout): out.append("\t\tFAUSTFLOAT* output%d = output[%d];\n" % (c, c))
first = True
for gi, g in enumerate(groups):
    out.append("\t\t// loop %d : chains %s\n" % (gi, ",".join(str(j) for j in g)))
    for j in g:
        for d in chains[j]["decls"]: out.append("\t\t%s\n" % d)
        for p in chains[j]["pro"]: out.append("\t\t%s\n" % p)
    out.append("\t\tfor (int i=0; i<count; i++) {\n")
    for j in g:
        for s in chains[j]["loop"]:
            w = wire(j, first, s)
            if w.startswith("output0[i]") and fam in "ox": first = False
            out.append("\t\t\t%s\n" % w)
    out.append("\t\t}\n")
    for j in g:
        for e in chains[j]["epi"]: out.append("\t\t%s\n" % e)
out.append("\t}\n};\n")
forged = "".join(out)

# 3. the architecture around it : faust's own file for chain 0 with the class region replaced
full = os.path.join(work, "full.cpp"); faust(os.path.join(work, "chain0.dsp"), full, arch=os.path.join(HERE, a.arch))
src = open(full).read()
m = re.search(r"class mydsp : public dsp \{.*?\n\};", src, re.S)
open(a.o, "w").write(src[:m.start()] + forged + src[m.end():])
print("forged %s : %d chains of %d filters, k=%d, %d loops -> %s" % (fam, a.P, a.S, a.k, len(groups), a.o))
