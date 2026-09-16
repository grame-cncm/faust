
- Per il generatore e container GPU voglio generare esplicitamente `F32` o `f32` anche per `kFloat_macro` o
  qullo che è. non voglio vedere `FaustFloat` e `dfaust` nel generato, li usiamo espliciti e ci togliamo il
  pensiero, internal `F64` e `f64` e `F32`, `f32` external/driver.
- Non voglio che tu definisci classi con logica (metodi) all'interno di `MojoGPUCodeContainer` e
  `MojoGPUInstVisitor`, a meno che non siano `struct` piccole e completamente passive o enum senza alcun
  meccanismo di ereditarieta'.
- Non introdurre headedrs aggiuntivi dato che cosi non ci sono errori di import, preferisci `unordered_map`
  a `ordered_map` e, se servono, usa gli alias che ho definito invece dei tipi raw.
- Il codice è pensato per essere wrappabile dal sistema delle architetture, il generato non deve gestire
  gli header, non generare include headers e import e quant'altro. Idealmente il code container dovrebbe
  contenere davvero pochissimo codice, come il `VecCodeContainer`, non si dovrebbe assolutamente ridefinire
  `createContainer` e sono molto, molto scettico anche su ridefinire `produceClass`, al momento tendo a
  considerarlo un errore di design.
- Voglio che prendi esempio come coding style dal vector code container: 
  - se serve per ripulire il codice utilizzi tecnice simili a quelle che uso con le macro con
    `mj_simd_emit_check`, `mj_simd_emit_set`, `mj_simd_accept`, ecc, ecc;
  - utilizza in modo simile a quanto ho fatto io il `mj_panic` invece delle `faustexceptions`, usa le
    `faustexceptions` sempre in modo similare a quanto ho fatto io, ma al momento ne abbiamo davvero troppe;
    - in caso non ti ricordi: per me gli `assert` sono assunzioni/asserzioni che vengono spente in release,
      invece i `panic` sono assunzioni/asserzioni che non vengono mai spente.
- In modo SECONDARIO, potresti ispirarti a `architecture/mojo/gui/terminal/native/termgui.h` e/o `termgui.c`
  oppure la mia `libcx`, ma in modo appunto secondario perché qui in `faust2mojo` dobbiamo comunque fare un
  po' di `OOP` style, invece in `termgui` e `libcx` lo stile super procedurale.
