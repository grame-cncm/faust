# The determinism gate

For one commit of the compiler and one program, the emitted code must be
the same, byte for byte, whatever C++ compiler and machine built faust.
See `../TESTING.md`, "Gate 3", for the property, the rule the code
follows and the reasons.

```
make binaries [CXX_A=g++ CXX_B=clang++]   two full builds -> bin/faust-a, bin/faust-b
make check [FAUST_A=... FAUST_B=...]      the witnesses by both binaries, compared byte for byte
make lint                                 the unsequenced-construction lint on compiler/
make clean
```

`witnesses.txt` : one witness per line, `name <TAB> file <TAB> process`
(the process name is the `-pn` of a library specification, `-` for a
plain program). Paths are relative to this directory. The witnesses were
chosen among the programs that diverged most between a g++ build and a
clang build before the fix, one per family of construction sites
(propagation, normalization, vectorization, widgets, recursive groups,
FIR), plus a few tiny ones. To add one, append a line ; keep the list
short, this gate is meant to run in seconds.

The two compilers of a pair must evaluate the arguments of a call in
different orders, or the pair is blind to the family this gate exists for :
`order.cpp` is the probe, `build-two.sh` runs it and warns. Measured :
GCC on x86-64 evaluates right to left ; clang (x86-64, arm64) and GCC on
arm64 (MacPorts gcc15) evaluate left to right. On an arm64 Mac, a local
pair is therefore not discriminating : use the lint, or compare against a
binary built with g++ on an x86-64 Linux machine.

`determinism.sh` generates every witness under six option sets with both
binaries into `out/a` and `out/b` and compares ; `build-two.sh` builds
the two binaries (the two builds share `build/bin/faust`, so they run one
after the other, from `build/det-a` and `build/det-b`).

Across two machines (a Mac with clang, a Linux with g++) : `make
fingerprint > mac.txt` on one, copy the file, `make compare FILE=mac.txt`
on the other. The witnesses whose constants go through the host's libm
(`libm-witnesses.txt`) are reported apart : they may differ at the last
ulp between two C libraries, and that is the known residual.

`lint/unsequenced.py` : `--why NAME` prints why a function is considered
order-significant ; `--out DIR` saves the call graph and the sites as
JSON.
