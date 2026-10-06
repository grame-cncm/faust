# Interval tests

The intervals of the Faust compiler must contain every value the compiled program can
produce : the guards of the table accesses, among others, are decided by them. Their
bounds are rounded outward (`compiler/interval/interval_def.hh`).

```sh
make -C tests/interval-tests test          # FAUST=... to choose the compiler
```

`check.sh` runs three kinds of checks:

1. **The directed rounding** (`directed.cpp`) : `addDown`, `mulUp`... and `floatBound`
   against the rounding modes of the machine, on random operands and edge cases.
2. **The tables at run time** : each `.dsp` is compiled with `bounds-driver.cpp`
   (every slider at its minimum then at its maximum, the inputs at -1 then 1), in
   `-single` and `-double`, by a C++ compiler with `-fsanitize=array-bounds` : an
   access out of a table stops the program.
3. **The generated code** : where the run time cannot show the defect (an FMA on a
   machine that does not fuse, a comparison wrongly decided, a guard written twice).

| Program | Defect it guards against |
| :--- | :--- |
| `fma_edge.dsp` | a bound rounded to nearest excludes the value of an FMA : `x = a*b + c` proven `>= 0.5`, `0.49999997` with an FMA (arm64) |
| `zone_edge.dsp` | a slider read from a float `FAUSTFLOAT` zone passes its declared minimum (the float of 0.7 is below 0.7) : in `-double`, `x < 0.7` was decided false and folded |
| `rwtable_write.dsp` | the write guard of an `rwtable` dropped when its read index needs none |
| `tabulate_clamped.dsp` | an index clamped by `ba.tabulate(1, ...)` guarded a second time |
