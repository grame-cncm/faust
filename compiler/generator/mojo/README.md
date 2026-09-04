## Faust to Mojo generator

The code in this directory implements the FAUST-to-Mojo transpiler.

### Miscellaneous files

- `.clangd`: configuration used to silence some Clangd LSP errors.
  - It defines the `MOJO_BUILD=1` environment variable, which is used later at compile time.

### Configuration files

These are the files prefixed with `_`. They contain private code outside the classes directly used by the
other compiler components (`faust/compiler` and `faust/compiler/generator`).

- `_mojo_hal.hh`: abstraction layer for the underlying hardware (`Hardware Abstraction Layer`).
- `_mojo_macro.hh`: macros used to improve the ergonomics and semantic clarity of the public code.
- `_mojo_utils.hh`: helper functions for the main public classes.

### Main files

These files contain the main backend classes, whose interfaces are used by other compiler components.

They are divided into header files (`*.hh`), containing class declarations, and implementation files
(`*.cpp`), containing the corresponding definitions.

The two main components are:

- `MojoInstVisitor` - The producer that translates `FAUST IR` instructions into `Mojo` code and writes
  them to the output stream.
- `MojoCodeContainer` - Uses the producer to build the type (`struct mydsp`) that encapsulates the DSP
  kernel.

In other words, the visitor traverses the `FAUST IR` instructions and produces their textual representation
in `Mojo`; the container organizes the generated code to build the structure representing the `FAUST`
program.

- `mojo_instructions.hh` - Declares `MojoInstVisitor` and its derived classes `MojoVecInstVisitor` and
  `MojoInitFieldsVisitor`.
- `mojo_code_container.hh` - Declares `MojoCodeContainer` and its derived classes
  `MojoScalarCodeContainer` and `MojoVecCodeContainer`.

- `mojo_instructions.cpp` - Implements `MojoInstVisitor` and `MojoInitFieldsVisitor`.
- `mojo_vec_instructions.cpp` - Implements `MojoVecInstVisitor`.
- `mojo_code_container.cpp` - Implements `MojoCodeContainer` and the derived `MojoVecCodeContainer`.

### Instructions Visitor

The `FAUST` language describes DSPs in a purely functional form. During transpilation, this representation
is progressively transformed into the `FAUST IR`, a procedural and imperative intermediate representation
composed of typed instructions for declarations, expressions, memory accesses, loops and control flow.
The Mojo backend traverses this IR and translates each instruction into the corresponding `Mojo` source
code. The *Code Container* organizes this code into a `struct` representing the generated DSP.

The translation is implemented by `MojoInstVisitor` using the *visitor pattern*. The class derives from
`TextInstVisitor`, from which it inherits the common infrastructure used to traverse the IR and write
indented textual code to an output stream. It overloads the `visit` operation for the different instruction
types. When an instruction accepts the visitor, the operation corresponding to its concrete type is
selected.

`MojoInitFieldsVisitor` is a visitor specialized in generating field initializations for the DSP `struct`
*default constructor*, `__init__`. For each declaration, it emits an assignment to the corresponding field,
using either the value stored in the `FAUST IR` or, when no value is present, a zero initializer appropriate
for the type.

### Code Container

`MojoCodeContainer` organizes the code produced by the instruction visitors and builds the `struct` that
represents the DSP in `Mojo`. The class derives from `CodeContainer` and defines the common structure of the
generated program.

The main container interface is `produceClass`, which coordinates the generation of the different sections.
By convention, helpers that write individual code sections use the `write` prefix. The container generates:

- the header and numeric type definitions;
- the `struct` declaration and its fields;
- the *default constructor* and field initialization;
- accessors for the sample rate and the number of inputs and outputs;
- instance initialization and reset functions;
- metadata and the JSON representation of the DSP;
- the method used to build the user interface;
- the `compute` method containing the DSP computation.

`MojoCodeContainer` is an abstract class from which `MojoScalarCodeContainer` and `MojoVecCodeContainer`
derive. The `createContainer` factory selects the appropriate variant according to the compilation options:
the scalar container is used for ordinary generation, while the vector container is instantiated when the
`-vec` option is enabled. The two implementations share the general structure of the `struct` and
specialize the generation of `compute` through `writeCompute`.

Instruction production uses two global visitors: `gScalarProducer`, shared by the scalar portions of the
code, and `gVectorProducer`, created by the vector container for explicit SIMD generation. Even in vector
mode, declarations, initializations, metadata and the user interface are still produced by the scalar
visitor. The vector visitor is used only to generate the `compute` method.

The vector container also derives from `VectorCodeContainer`, which encapsulates the vector representation
of the computation and the ability to distinguish recursive nodes from vectorizable ones.

### Explicit SIMD emission

With the `-vec` option, FAUST reorganizes the imperative DSP representation by dividing the computation
into subloops ordered according to the dependencies described by the corresponding DAG. The subloops are
also classified as recursive, and therefore not vectorizable, or independent across iterations.

In the traditional FAUST path, this form allows the compiler of the target language, for example `clang`,
to autovectorize compatible subloops. Mojo instead disables LLVM autovectorization passes, so scalar
emission is not automatically converted into vector instructions.

The Mojo backend therefore uses the subdivision into subloops produced by `-vec` as the basis for explicit
vectorization, using the SIMD type system provided by the language.

The fundamental numeric type is `SIMD[dtype, width]`, where `dtype` is the primitive type, for example
`f32`, and `width` is the vector width, namely the number of elements on which the operation is performed
in parallel. `SIMD[dtype, 1]` corresponds to the scalar case `Scalar[dtype]`; `width` is also used as a
parameter in metaprogramming operations.

In the Mojo backend, recursive subloops are fully unrolled into `vsize` operations through `comptime for`,
while independent loops are translated into explicit SIMD instructions.

The scalar fallback is also applied to loops that are not recursive but contain memory accesses that are
incompatible with contiguous vectorization.

The implementation requires several assumptions and workarounds, described in the following sections,
which in some cases couple the responsibilities of the container and the visitor. These solutions adapt
the structure of the `FAUST IR` and the generated expressions to the constraints of Mojo's type system.

The first important assumption concerns floating-point precision. SIMD emission supports only `f64`
internal computation precision and `f32` precision for the external driver architecture.

#### Vector Code Container

`MojoVecCodeContainer` derives from both `MojoCodeContainer` and `VectorCodeContainer`. The former provides
the common structure of the DSP `struct`, while the latter transforms the DSP kernel into a graph of loops.

The container explicitly generates the `vindex` index, the `end` limit and the main loop increment. The
equivalent declaration is removed from the DAG, while `MojoVecInstVisitor` recognizes the main loop through
the name `vindex`. This introduces an intentional coupling between the container and the visitor.

The generated code obtains the native vector widths of the target:

```
    vsize = simd_width_of[f32]()
    hsize = simd_width_of[f64]()
```

Here, `vsize` means "vector size" and `hsize` means "half size".

Because an `f32` vector contains twice as many lanes as an `f64` vector, the following relation holds:

```
    vsize = 2 * hsize
```

The name `vsize` was chosen for semantic continuity with the FAUST `-vs` option, and the two values must
match for correctness:

- FAUST generates subloops of `-vs` frames (e.g. `for i in 0..vsize`);
- Mojo uses `vsize` (and `hsize`) to define types, invoke operations and advance through the buffer.

A mismatch between the two values introduces structural errors.

The backend is independent of a specific hardware SIMD extension, provided that FAUST compilation uses the
native `f32` width of the target:

```
    ARM NEON 128 bit
        -vs 4
        vsize = 4
        hsize = 2

    x86 AVX2 256 bit
        -vs 8
        vsize = 8
        hsize = 4

    x86 AVX-512 512 bit
        -vs 16
        vsize = 16
        hsize = 8
```

Generation also uses `-mcd 4`, which defines the threshold above which delay lines are represented with a
ring buffer rather than through copies.

In the Mojo backend's vec mode, `-vs` and `-mcd` must match `vsize`. With `-vs 4 -mcd 4`, delay lines below
the threshold are rounded to four elements; otherwise, they use a ring buffer.

The subloops are therefore compatible with processing blocks of `vsize` frames.

The currently supported invocation is:

```
    faust -double -vec -dfs -vs 4 -mcd 4 -lang mojo [name].dsp -o [name].mojo
```

The backend has only been tested with this configuration on Apple M1 and M4 processors, which use 128-bit
NEON SIMD. The x86 configurations are theoretically supported but have not been verified.

#### Vector Instructions Visitor

`MojoVecInstVisitor` derives from `MojoInstVisitor` and reuses its scalar instruction operations.

In addition to generating vector constructors, casts, binary operations, SIMD loads and stores, the
specialized `visit` operations classify subloops according to the required emission strategy.

Visiting an inner loop may produce:

- a single SIMD store to an `f32` destination (`vsize` elements);
- the broadcast of a scalar value;
- two SIMD stores to an `f64` destination (`2 * hsize` elements);
- the join of two `f64` results followed by a final store to `f32`;
- a scalar loop unrolled through `comptime for` for recursive loops;
- a scalar loop unrolled through `comptime for` for memory access patterns that are not linear;
- specialized handling for updating a bargraph and a related parameter;
- specialized handling for updating multiple bargraphs and a parameter unrelated to them.

The visitor assumes that the last (or only) instruction in the loop is the main `StoreVarInst`. From this
instruction, it obtains the destination, result type and strategy required to generate the complete loop.

#### Generation state

`MojoVecInstVisitor` divides the generation logic among `visit` operations and their helpers. It maintains
global state for the current loop to share context between these methods.

- `gSIMDEmit` indicates whether the visited instructions must be emitted in SIMD form;
- `gSIMDHigh` indicates generation of the second portion of an `f64` block, shifted by `hsize`;
- `gSIMDHalf` selects width `H`, corresponding to the SIMD width of `f64` (`Half`);
- `gSIMDJoin` indicates that two `f64` results must be packed into a single `f32` vector;
- `gCurLhsDT` stores the result type assigned by the current loop (`Current Lhs DType`);
- `gCurAddrs` stores the current destination name;
- `gCurIndex` identifies the index of the FAUST loop removed during vectorization.

The `gSIMDHalf` flag generates operations with the explicit `H` parameter, such as `vstore[H]`, and is
essential when the numeric type does not match its native SIMD width, for example:

```
    SIMD[f32, simd_width_of[f64]()]
```

#### Contextual visit macros

The SIMD macros generally apply a save-and-restore pattern to the state:

```
    save the current flag value
    set the new context
    visit the instruction
    restore the previous value
```

`mj_simd_emit_set` and `mj_simd_emit_restore` delimit a SIMD emission region, while
`mj_simd_emit_accept` applies the same pattern around a single instruction visit.
`mj_simd_high_accept` visits an expression with `gSIMDHigh` enabled to produce the second `f64` portion.
The `mj_scalar_accept` and `mj_scalar_visit` macros temporarily disable SIMD emission and delegate the
translation to the scalar behavior inherited from `MojoInstVisitor`.

This mechanism avoids manually replicating flag management in every `visit` operation and preserves the
outer context during recursive visits.

#### Mixed precision and SIMD widths

The difference between `vsize` and `hsize` requires explicit handling of mixed-precision expressions.
Numeric values are emitted using different constructors according to their type and context:

```
    s32  -> S32Vec / S32Hec
    f32  -> F32Vec / F32Hec
    f64  -> F64Vec
```

The `Hec` types represent `s32` or `f32` values with the same number of lanes as the `f64` vector. They are
required when an integer or an `f32` value participates in an `f64` expression.

The `gSIMDHalf` flag propagates this choice to all subsequent operands in the expression, preventing
operations between vectors with incompatible widths.

When the destination is `f64`, the visitor generates the low and high portions separately:

```
    vstore(dst, low)
    vstore(dst, high, hsize)
```

During the second visit, `gSIMDHigh` adds `hsize` to indexed accesses. When an `f64` expression must instead
be written to an `f32` output, the two portions are combined:

```
    vstore(dst, low.join(high))
```

#### Memory access analysis

Vectorization is allowed only when every SIMD lane accesses consecutive addresses. The visitor currently
recognizes simple affine indices relative to the loop index:

```
    A[i]
    A[i + c]
    A[i - c]
    A[c + i]
```

`gCurIndex` represents the scalar index removed from the vector loop, while `visitIndex` translates these
forms into an offset for `vload` or `vstore`. During generation of the high `f64` portion, an additional
offset equal to `hsize` is added.

Circular indices, operators other than addition and subtraction, function calls and indirect accesses are
classified as not vectorizable. Expressions such as:

```
    table[f(i)]
    buffer[(i + offset) & mask]
```

would respectively require gather operations or explicit handling of the address used by each lane. Since
these operations are not implemented yet, the loop is conservatively translated through the scalar path.
A normal contiguous `vload` would not be semantically equivalent to a gather.

#### Scalar fallback and special cases

Recursive loops and loops with non-vectorizable accesses are emitted as scalar loops executed over the
`vsize` lanes of the current block:

```
    comptime for i in range(vsize):
        scalar body
```

The fallback uses `MojoInstVisitor` to emit scalar operations, preserving their order after unrolling.

Bargraphs are handled as two separate cases:

- The bargraph is directly related to the parameter written by the final store. The value is computed in
  SIMD form, and the bargraph is updated with the final element of the block.

- The loop contains multiple bargraph updates followed by the store of an unrelated parameter. The updates
  are emitted in scalar form through `comptime for`, while the final store is handled separately according
  to the vectorization rules described above.

Recognition is based on the number of instructions and names containing `bargraph`, assuming that the
parameter store is the last instruction in the loop.

#### Current constraints and workarounds

- `-vs` must match the width returned by `simd_width_of[f32]()`.

- This correspondence is required by the backend but is not explicitly checked yet.

- The main loop is recognized by the name `vindex`.

- The declaration containing `vsize` is ignored because it is generated directly by the container.

- The first DAG element is removed under the assumption that it initializes the main index.

- Each loop has one main `StoreVarInst`, which is the last instruction.

- Loops may contain one, two or more than two instructions:
  - only the main store;
  - a bargraph update and the related main store;
  - several bargraph updates and a main store that is not necessarily related to them.

- Bargraphs are recognized through the loop shape and field names.

- Index vectorizability is limited to simple affine expressions.

- Gather and scatter are not implemented and trigger the scalar fallback.

- SIMD state is global and is restored manually at the end of each loop.

- `gSIMDHalf` persists for the entire loop to keep operand widths consistent.

- Generation does not emit the scalar path for frames remaining after the final complete block.

The final constraint means that the buffer size must be compatible with `vsize`. The visitor ignores the
`IfInst` produced by the FAUST pipeline to handle remaining frames, while the main loop processes only
complete SIMD blocks.
