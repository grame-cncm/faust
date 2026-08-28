Il codice presente in questa cartella implementa il transpilatore da FAUST a Mojo.

### File miscellanei

- `.clangd`: configurazione per silenziare alcuni errori dello LSP Clangd
  - Definisice la variabile di ambiente `MOJO_BUILD=1` che viene passata solo successivamente a compile time.

### File di configurazione

Si tratta dei file prefissi da `_`, contenenti codice privato che esula dalle classi strettamente utilizzate
dalle altre componenti compilatore (`faust/compiler`, `faust/compiler/generator`).

- `_mojo_hal.hh`: codice per l'astrazione dall'hardware sottostante (`Hardware Abstraction Layer`).
- `_mojo_macro.hh`: macro per ergonomia e pulizia semantica del codice pubblico.
- `_mojo_utils.hh`: funzioni helper per le classi pubbliche principali.

### File principali

Contengono il codice contenente classi le cui interfacce sono pubbliche ed utilizzate dalle altre componenti
del compilatore tramite ereditarietà (polimorfismo per sottotipizzazione).

Tali file si suddividono in file di intestazione (`*.hh`), contenenti le dichiarazioni delle classi, e file
di implementazione (`*.cpp`), contenenti le definizioni delle classi.

In sintesi, i file implementano le due seguenti classi.

- `MojoInstVisitor` − Il produttore che traduce il codice `FAUST` in codice `Mojo` e lo scrive su output.
- `MojoCodeCtonainer` − Usa il produttore per generare il tipo (`struct mydsp`) che incapsula il kernel DSP.

In altri termini: 
- il produttore implementa un *visitor pattern* sui token della `FAUST IR` e li traduce in token `Mojo`
- il container si avvale dei token di cui sopra per costruire la struttura dati che effettivamente
  rappresenta il programma `FAUST`.

- `mojo_instructions.hh`: dichiara `MojoInstVisitor` e la classe derivata `MojoVecInstVisitor`.
- `mojo_code_container.hh`: dichiara `MojoCodeContainer` e la classe derivata `MojoVecCodeContainer`.

- `mojo_instructions.cpp`: implementa `MojoInstVisitor`.
- `mojo_vec_instructions.cpp`: implementa `MojoInstVisitor` e la classe derivata `MojoVecInstVisitor`.
- `mojo_code_container.cpp`: implementa `MojoCodeContainer` e la classe derivata `MojoVecCodeContainer`.

### Instructions Visitor

### Code Container

### Special case: explicit SIMD emission
