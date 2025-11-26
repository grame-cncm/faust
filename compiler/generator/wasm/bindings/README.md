WASM bindings overview
======================

This directory defines the Emscripten bindings that expose libfaust to JavaScript. The bindings live in `binding.cpp` and are generated into the `Module` object produced by the wasm build.

Exports
-------

`libFaustWasm` class
- `version()`
- `createDSPFactory(name, dsp, args, internal_memory)`
- `deleteDSPFactory(cfactory)`
- `deleteAllDSPFactories()`
- `expandDSP(name, dsp, args)`
- `generateAuxFiles(name, dsp, args)`
- `cleanupAfterException()`
- `getErrorAfterException()`
- `getInfos(what)`
- `FaustWasm` objects carry `{ cfactory, data, json }`.

Enums and structs
- `SType`, `SOperator`, and `Interval`.
- Vectors: `vector<int>`, `vector<CTree*>`, `vector<string>`, `vector<SType>`.

Box API (libfaust-box.h)
- Constructors/operators: `boxInt`, `boxReal`, `boxWire`, `boxCut`, sequencing/parallel/split/merge/route/rec/delay, casts, tables, waveform/soundfile, selectors, math (`boxAdd`… and zero-arg overloads), UI widgets, groups, attach, `boxPrim2`.
- Helpers: `primXname`, `ffname`, `ffarity`, `extractName`, `tree2str`, `tree2int`, `getUserData`, `printBox`.
- Converters: `DSPToBoxes`, `boxesToSignals`, `boxesToSignals2`, `createSourceFromBoxes`, `getBoxType`.
- Introspection: all `isBox*` functions are exported. For overloads with out-parameters, the wrapped versions return an object `{ result, <fields> }` where pointer outputs are encoded as integers (reinterpret_cast of the C++ pointer).
- Wrapped helpers: `getDefNameProperty`, `isBoxAccess`, `isBoxComponent`, `isBoxLibrary`, `isBoxMetadata`, `isBoxRoute`, `isBoxWithLocalDef`, `isBoxIdent`, `isBoxInputs`, `isBoxIPar`, `isBoxIProd`, `isBoxISeq`, `isBoxISum`, `isBoxMerge`, `isBoxOutputs`, `isBoxPar`, `isBoxRec`, `isBoxSeq`, `isBoxInt`, `isBoxReal`, `isBoxSlot`.

Signal API (libfaust-signal.h)
- Constructors/operators: full set of `sig*` creators (constants, tables, soundfile accessors, selectors, math, recursion, UI, attach/control), plus `simplifyToNormalForm`/`simplifyToNormalForm2`, `createSourceFromSignals`.
- Helpers: `tree2str`, `getUserData`, interval accessors (`getSigInterval`, `setSigInterval`), `xtendedArity`, `xtendedName`, `printSignal`.
- Introspection: all `isSig*`, `isProj`, `isRec` are exported. For overloads with out-parameters the wrapped versions return `{ result, <fields> }` using pointer values as integers. Wrapped helpers include `isSigInt`, `isSigInt64`, `isSigReal`, `isSigInput`, `isSigOutput`, `isSigDelay(1)`, `isSigPrefix`, doc-table checks, selectors, math (`isSigBinOp`, `isSigFFun`, `isSigFConst`, `isSigFVar`), casts, UI, control/enable, soundfile accessors, etc.

Usage notes
-----------
- Call `createLibContext()` before using the APIs and `destroyLibContext()` when done.
- Pointers are surfaced as integer values; pass them back to other exported functions unchanged to operate on the same underlying C++ objects.
- Wrapper results always contain a boolean `result` field indicating success; additional fields are only meaningful when `result` is true.
