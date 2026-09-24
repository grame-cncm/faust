#!/usr/bin/env python3
"""Check that documentation/COMPILING-FAUST-PROGRAMS.md covers the compiler's options.

Every option printed by `faust -h` must appear in the document, either as a row
of an option table (a line starting with "| `-opt`") or in the table of options
left out of scope ; and every option the document lists must still be printed by
`faust -h`, unless its row says "(not in -h)". The environment variables the
compiler reads (getenv("FAUST_...") in compiler/) must each be named in the
document too.

usage : check-compiling-doc.py [path/to/faust]    (default : build/bin/faust)
exit 0 when the document and the compiler agree, 1 otherwise, with the list of
disagreements. Run it from the root of the repository.
"""
import pathlib
import re
import subprocess
import sys

ROOT = pathlib.Path(__file__).resolve().parents[2]
DOC = ROOT / "documentation" / "COMPILING-FAUST-PROGRAMS.md"
FAUST = sys.argv[1] if len(sys.argv) > 1 else str(ROOT / "build" / "bin" / "faust")

# the options of `faust -h` : every token of the form -xxx that begins a help entry
# (an entry may be glued to the previous line, so the search is not anchored)
help_text = subprocess.run([FAUST, "-h"], capture_output=True, text=True).stdout
if "Code generation options" not in help_text:
    print(f"cannot read the help of {FAUST}")
    sys.exit(1)
in_help = set()
for line in help_text.splitlines():
    for m in re.finditer(r"(?:^|\s{2,}|\.)(-[A-Za-z][A-Za-z0-9-]*)\s", line):
        in_help.add(m.group(1))

doc_text = DOC.read_text(encoding="utf-8")
documented, hidden = set(), set()
for line in doc_text.splitlines():
    m = re.match(r"\|\s*`(-[A-Za-z][A-Za-z0-9-]*)", line)
    if m:
        documented.add(m.group(1))
        if "(not in -h)" in line:
            hidden.add(m.group(1))

env_read = set()
for f in (ROOT / "compiler").rglob("*"):
    if f.suffix in (".cpp", ".hh") and f.is_file():
        env_read |= set(re.findall(r'getenv\("(FAUST_[A-Z0-9_]+)"\)', f.read_text(errors="ignore")))
env_missing = sorted(v for v in env_read if f"`{v}`" not in doc_text)

undocumented = sorted(in_help - documented)
stale = sorted(documented - in_help - hidden)
hidden_but_listed = sorted(hidden & in_help)

ok = not (undocumented or stale or env_missing or hidden_but_listed)
print(f"faust -h : {len(in_help)} options ; document : {len(documented)} rows "
      f"({len(hidden)} marked not in -h) ; environment variables read : {len(env_read)}")
for title, items in (("in faust -h, missing from the document", undocumented),
                     ("in the document, no longer in faust -h", stale),
                     ("marked (not in -h) but printed by faust -h", hidden_but_listed),
                     ("environment variables read by the compiler, not named in the document", env_missing)):
    if items:
        print(f"{title} ({len(items)}) : {' '.join(items)}")
print("OK" if ok else "FAILED")
sys.exit(0 if ok else 1)
