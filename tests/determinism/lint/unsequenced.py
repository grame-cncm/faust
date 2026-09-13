#!/usr/bin/env python3
"""The unsequenced-construction lint.

The compiler's trees carry a serial number given at creation ; every order the
compiler reads (sets, normal forms, recursive groups) is the creation order.
When two arguments of one call both create trees, the C++ compiler that built
faust chooses which is created first (the order of evaluation of function
arguments is unspecified ; GCC and clang differ), and the emitted code follows.
The rule (tests/TESTING.md, "Determinism") : two such arguments are computed in
separate statements.

This lint finds the violations statically :
  pass 1 (per translation unit, in parallel) : every function's callees, and
         every call or unsequenced binary operator whose operands contain calls ;
  pass 2 : Fx, the closure of the call graph towards the primitive effects
         (CTree::CTree, CTree::make, tree(...), unique(...), getFreshID), then
         the sites whose operands reach Fx at least twice.

Not reported, because the language sequences them : the operators <<, >>, =,
the compound assignments, [], &&, ||, the comma (C++17, overloaded forms
included) and braced initializer lists (C++11).

Usage : unsequenced.py [--root DIR] [--out DIR] [--why NAME] [--json]
  exit status 1 when a site remains, 0 when none.
Requires the clang python bindings and a libclang matching them ; set
LIBCLANG (path to libclang.so/.dylib) and CLANG_RESOURCE_DIR when the
defaults below do not find them.
"""
import os, sys, json, re, glob, subprocess, platform, argparse
from multiprocessing import Pool
import clang.cindex as ci

ap = argparse.ArgumentParser()
ap.add_argument("--root", default=None, help="faust source root (default : three levels above this file)")
ap.add_argument("--out", default=None, help="where to write graph.json (default : no file)")
ap.add_argument("--why", action="append", default=[], help="print a path from NAME to a primitive effect")
ap.add_argument("--jobs", type=int, default=8)
ap.add_argument("--quiet", action="store_true")
opt = ap.parse_args()

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(opt.root) if opt.root else os.path.abspath(os.path.join(HERE, "..", "..", ".."))
COMP = os.path.join(ROOT, "compiler")

# --- libclang ---------------------------------------------------------------
def find_libclang():
    if os.environ.get("LIBCLANG"):
        return os.environ["LIBCLANG"]
    cands = glob.glob("/opt/local/libexec/llvm-*/lib/libclang.dylib") + glob.glob("/opt/homebrew/opt/llvm*/lib/libclang.dylib") \
        + glob.glob("/usr/lib/llvm-*/lib/libclang.so*") + glob.glob("/usr/lib/libclang.so*") + glob.glob("/usr/lib64/libclang.so*")
    def version(p):
        m = re.search(r"llvm-?(\d+)", p); return int(m.group(1)) if m else 0
    cands = sorted(set(cands), key=version, reverse=True)
    return cands[0] if cands else None
LIB = find_libclang()
if LIB:
    ci.Config.set_library_file(LIB)
def resource_dir():
    if os.environ.get("CLANG_RESOURCE_DIR"):
        return os.environ["CLANG_RESOURCE_DIR"]
    if LIB:
        m = re.search(r"(/opt/local/libexec/llvm-(\d+))/lib/libclang", LIB)
        if m and os.path.isdir(f"{m.group(1)}/lib/clang/{m.group(2)}"):
            return f"{m.group(1)}/lib/clang/{m.group(2)}"
        m = re.search(r"(/usr/lib/llvm-(\d+))/lib/libclang", LIB)
        if m and os.path.isdir(f"{m.group(1)}/lib/clang/{m.group(2)}"):
            return f"{m.group(1)}/lib/clang/{m.group(2)}"
    for cc in ("clang", "clang++"):
        try:
            return subprocess.run([cc, "-print-resource-dir"], capture_output=True, text=True).stdout.strip()
        except Exception:
            pass
    return None
RES = resource_dir()

DEFINES = ["-DASSEMBLYSCRIPT_BUILD", "-DCMAJOR_BUILD", "-DCODEBOX_BUILD", "-DCPP_BUILD", "-DCSHARP_BUILD",
           "-DC_BUILD", "-DDLANG_BUILD", "-DJAVA_BUILD", "-DJSFX_BUILD", "-DJULIA_BUILD", '-DLIBDIR="lib"',
           "-DLINEN_BUILD", "-DNNX_BUILD", "-DOCPP_BUILD", "-DRUST_BUILD", "-DSDF3_BUILD",
           "-DTLIB_API=LIBFAUST_API", '-DTLIB_EXPORT_HEADER=<faust/export.h>', "-DVHDL_BUILD", "-DWASM_BUILD",
           "-DFAUST_EXE", "-DFIR_BUILD", "-DINTERP_BUILD", "-DTEMPLATE_BUILD"]
# units that need headers the lint does not have (LLVM, emscripten) : skipped, not analysed
SKIP_DIRS = ("compiler/generator/llvm", "compiler/generator/wasm/bindings")
INCLUDES = ["-I" + d for d, _, _ in os.walk(COMP)] + ["-I" + os.path.join(ROOT, "architecture")]
SYSROOT = []
if platform.system() == "Darwin":
    sdk = subprocess.run(["xcrun", "--show-sdk-path"], capture_output=True, text=True).stdout.strip()
    SYSROOT = ["-isysroot", sdk] if sdk else []
ARGS = ["-std=gnu++17", "-x", "c++"] + (["-resource-dir", RES] if RES else []) + SYSROOT + DEFINES + INCLUDES

# the bindings may predate the native library : register every unknown cursor kind
for _i in range(0, 1200):
    try:
        ci.CursorKind.from_id(_i)
    except ValueError:
        try:
            ci.CursorKind(_i)
        except Exception:
            pass

# --- what counts ------------------------------------------------------------
# primitive effects : exact names, so that a homonym (another class's make()) does not pollute Fx
PRIMITIVE = re.compile(r"^(CTree::CTree|CTree::make|tree|unique|global::getFreshID|ScalarCompiler::getFreshID|DocCompiler::getFreshID)$")
# sinks : the closure does not go through them. They only run on a failure path
# (an assertion, an exception being built), where the creation order is moot,
# and they reach tree() through the printing of the compilation options.
SINK = re.compile(r"^(faustassertaux|faustexception::faustexception|faustexception::.*|global::printCompilationOptions)$")
FUNC_KINDS = {ci.CursorKind.FUNCTION_DECL, ci.CursorKind.CXX_METHOD, ci.CursorKind.CONSTRUCTOR,
              ci.CursorKind.DESTRUCTOR, ci.CursorKind.CONVERSION_FUNCTION, ci.CursorKind.FUNCTION_TEMPLATE}
UNSEQ_BIN = {"+", "-", "*", "/", "%", "<", ">", "<=", ">=", "==", "!=", "&", "|", "^"}
SEQ_BIN = {"&&", "||", ",", "=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<", ">>", "<<=", ">>="}
# overloaded operators the standard sequences (C++17) : never a site, whatever their arguments do
SEQ_OPERATOR = re.compile(r"operator(<<|>>|=|\[\]|&&|\|\||,|[-+*/%&|^]=|<<=|>>=)$")

def qualname(c):
    parts = []
    while c is not None and c.kind != ci.CursorKind.TRANSLATION_UNIT:
        if c.spelling:
            parts.append(c.spelling)
        c = c.semantic_parent
    return "::".join(reversed(parts))

def in_project(c):
    f = c.location.file
    return f is not None and f.name.startswith(ROOT)

def calls_in(node, acc):
    if node.kind == ci.CursorKind.LAMBDA_EXPR:
        return
    if node.kind == ci.CursorKind.CALL_EXPR:
        r = node.referenced
        if r is not None and r.kind in FUNC_KINDS:
            acc.add(r.get_usr())
    for ch in node.get_children():
        calls_in(ch, acc)

def operator_spelling(node):
    kids = list(node.get_children())
    if len(kids) != 2:
        return None
    left_end = kids[0].extent.end
    for t in node.get_tokens():
        if t.extent.start.offset >= left_end.offset and t.spelling in UNSEQ_BIN | SEQ_BIN:
            return t.spelling
    return None

def braced(node):
    """a constructor call written as a braced initializer list : its elements are sequenced"""
    for t in node.get_tokens():
        return t.spelling == "{"
    return False

def visit_function(fn, tu_result):
    usr = fn.get_usr()
    callees = set()
    sites = []
    def walk(node):
        if node.kind == ci.CursorKind.LAMBDA_EXPR:
            return
        if node.kind == ci.CursorKind.CALL_EXPR:
            r = node.referenced
            if r is not None and r.kind in FUNC_KINDS:
                callees.add(r.get_usr())
            args = list(node.get_arguments())
            callee = qualname(r) if r else node.spelling
            if len(args) >= 2 and not SEQ_OPERATOR.search(callee) and not braced(node):
                ops = []
                for a in args:
                    s = set(); calls_in(a, s); ops.append(sorted(s))
                if sum(1 for s in ops if s) >= 2:
                    sites.append({"kind": "call", "callee": callee,
                                  "file": os.path.relpath(node.location.file.name, ROOT), "line": node.location.line,
                                  "operands": ops})
        elif node.kind == ci.CursorKind.BINARY_OPERATOR:
            op = operator_spelling(node)
            if op in UNSEQ_BIN:
                ops = []
                for k in node.get_children():
                    s = set(); calls_in(k, s); ops.append(sorted(s))
                if sum(1 for s in ops if s) >= 2:
                    sites.append({"kind": "op " + op, "callee": "", "file": os.path.relpath(node.location.file.name, ROOT),
                                  "line": node.location.line, "operands": ops})
        for ch in node.get_children():
            walk(ch)
    for ch in fn.get_children():
        if ch.kind == ci.CursorKind.COMPOUND_STMT:
            walk(ch)
    tu_result["functions"][usr] = {"name": qualname(fn), "callees": sorted(callees),
                                   "file": os.path.relpath(fn.location.file.name, ROOT)}
    for s in sites:
        s["in"] = usr
    tu_result["sites"].extend(sites)

def analyse(path):
    idx = ci.Index.create()
    try:
        tu = idx.parse(path, args=ARGS)
    except ci.TranslationUnitLoadError as e:
        return {"tu": path, "error": str(e), "functions": {}, "sites": []}
    errs = [d for d in tu.diagnostics if d.severity >= ci.Diagnostic.Error]
    res = {"tu": os.path.relpath(path, ROOT), "errors": len(errs),
           "first_error": (errs[0].spelling[:100] if errs else ""), "functions": {}, "sites": []}
    def top(node):
        if node.kind in FUNC_KINDS and node.is_definition() and in_project(node):
            visit_function(node, res)
            return
        for ch in node.get_children():
            if node.kind == ci.CursorKind.TRANSLATION_UNIT or in_project(ch) or ch.kind in (
                    ci.CursorKind.NAMESPACE, ci.CursorKind.CLASS_DECL, ci.CursorKind.STRUCT_DECL, ci.CursorKind.CLASS_TEMPLATE):
                top(ch)
    top(tu.cursor)
    return res

def translation_units():
    tus = []
    for d, _, files in os.walk(COMP):
        if any(os.path.relpath(d, ROOT).startswith(sd) for sd in SKIP_DIRS):
            continue
        for f in files:
            if f.endswith(".cpp"):
                tus.append(os.path.join(d, f))
    return sorted(tus)

if __name__ == "__main__":
    if LIB is None:
        print("libclang not found : set LIBCLANG", file=sys.stderr); sys.exit(2)
    tus = translation_units()
    with Pool(opt.jobs) as pool:
        results = pool.map(analyse, tus)
    functions, sites, tu_errors = {}, [], []
    for r in results:
        if r.get("error"): tu_errors.append((r["tu"], r["error"])); continue
        if r["errors"]: tu_errors.append((r["tu"], r["first_error"]))
        for usr, f in r["functions"].items():
            if usr in functions:
                functions[usr]["callees"] = sorted(set(functions[usr]["callees"]) | set(f["callees"]))
            else:
                functions[usr] = f
        sites.extend(r["sites"])
    seen, uniq = set(), []
    for s in sites:
        k = (s["file"], s["line"], s["kind"])
        if k not in seen: seen.add(k); uniq.append(s)
    sites = uniq
    prim = {u for u, f in functions.items() if PRIMITIVE.search(f["name"])}
    callers = {}
    for u, f in functions.items():
        for c in f["callees"]:
            callers.setdefault(c, set()).add(u)
    sink = {u for u, f in functions.items() if SINK.search(f["name"])}
    fx = set(prim); parent = {u: None for u in prim}; frontier = list(prim)
    while frontier:
        u = frontier.pop()
        for c in callers.get(u, ()):
            if c not in fx and c not in sink: fx.add(c); parent[c] = u; frontier.append(c)
    hot = [s for s in sites if sum(1 for ops in s["operands"] if any(u in fx for u in ops)) >= 2]
    hot.sort(key=lambda s: (s["file"], s["line"]))
    if opt.out:
        os.makedirs(opt.out, exist_ok=True)
        json.dump({"functions": {u: f for u, f in functions.items()}, "fx": sorted(fx), "primitives": sorted(prim),
                   "sites": hot, "tu_errors": tu_errors}, open(os.path.join(opt.out, "graph.json"), "w"), indent=1)
    for name in opt.why:
        us = [u for u, f in functions.items() if f["name"] == name or f["name"].endswith("::" + name)]
        if not us:
            print(f"--why {name} : unknown function"); continue
        for u in us:
            if u not in fx:
                print(f"--why {functions[u]['name']} ({functions[u]['file']}) : not in Fx"); continue
            path, x = [], u
            while x is not None:
                path.append(functions[x]["name"] + " (" + functions[x]["file"] + ")"); x = parent[x]
            print(f"--why {functions[u]['name']} : " + "  ->  ".join(path))
    if not opt.quiet:
        print(f"translation units : {len(tus)}, with errors : {len(tu_errors)}")
        for t, e in tu_errors:
            print(f"    {t} : {e}")
        print(f"functions : {len(functions)}, primitives : {len(prim)}, Fx : {len(fx)}")
        print(f"sites with two operands calling something : {len(sites)}")
        print(f"sites with two operands reaching Fx : {len(hot)}")
    for s in hot:
        try:
            txt = open(os.path.join(ROOT, s["file"])).read().split("\n")[s["line"] - 1].strip()[:100]
        except Exception:
            txt = ""
        print(f'{s["file"]}:{s["line"]}: [{s["kind"]}{" " + s["callee"] if s["callee"] else ""}] {txt}')
    sys.exit(1 if hot else 0)
