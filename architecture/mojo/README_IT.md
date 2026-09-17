# Faust to Mojo architectures

Questa directory contiene le architetture e i componenti di supporto utilizzati dal backend Mojo di FAUST
per trasformare il DSP generato in un programma eseguibile.

Un backend FAUST comprende due parti principali:

- il **generatore**, che traduce la rappresentazione intermedia nel linguaggio di destinazione;
- il **sistema di architetture**, che fornisce l'ambiente necessario per utilizzare il DSP generato.

Il generatore Mojo produce `struct mydsp`, con stato, inizializzazione, metadati, descrizione della UI e
metodi di elaborazione. L'architettura aggiunge il punto d'ingresso, il driver audio, la GUI, la gestione
della memoria e il codice di supporto. Il percorso CPU usa `compute`; quello GPU, ancora sperimentale,
genera anche le operazioni richieste da `FaustDspGpu`.

## Architetture FAUST

Un'architettura FAUST è un template Mojo selezionato con `-a`. Il compilatore inserisce il DSP fra la
prima sezione dell'architettura (import e definizioni) e la seconda (punto d'ingresso):

```
    import e definizioni forniti dall'architettura
    <<includeIntrinsic>>
    <<includeclass>>
    main e gestione del ciclo di vita forniti dall'architettura
```

`<<includeclass>>` riceve la classe DSP emessa da `MojoCodeContainer.produceClass()`;
`<<includeIntrinsic>>` rimane nel template per l'espansione dell'architettura da parte del compilatore.
I template top-level usano commenti di sezione per delimitare queste parti.

Seguono questa struttura `portaudio.mojo`, `portaudio-terminal.mojo`, `portaudio-proto.mojo`,
`portaudio-terminal-gpu.mojo`, `bench.mojo`, `inspect.mojo` e `impulse.mojo`. I package sottostanti
contengono le implementazioni riutilizzabili; i template le compongono attorno al DSP generato.

## Interfaccia del DSP

Il trait `FaustDsp`, in `dsp/dsp.mojo`, definisce il contratto comune delle architetture CPU: numero di
ingressi e uscite, sample rate, inizializzazione e reset, metadati e JSON, costruzione della UI ed
elaborazione a blocchi:

```
    dsp.compute(count, inputs, outputs)
```

La `mydsp` generata implementa il contratto; la callback PortAudio può quindi elaborarla senza conoscere
i suoi campi. Anche benchmark e impulse test usano questa interfaccia.

La variante GPU implementa inoltre `FaustDspGpu`, in `dsp/gpu.mojo`. Il trait aggiunge le operazioni
statiche `gpu_work_size(count)` e
`gpu_compute(ctx, dsp_raw, in_buf, out_buf, work_buf, count)`. La sua implementazione predefinita di
`compute` è vuota: per eseguire l'audio GPU si passa a PortAudio un `AdapterDsp[mydsp]`, il cui `compute`
inoltra il blocco a `GpuDevice`. Passare direttamente il DSP GPU a PortAudio non avvierebbe il calcolo GPU.

Generatore e architettura selezionata si incontrano nel file Mojo completo:

```
    programma FAUST               template di architettura (-a)
          |                                  |
    generatore Mojo                import e main dell'applicazione
          |                                  |
          +------------ mydsp ---------------+
                           |
                    compilatore Mojo
                           |
                      applicazione
```

## Organizzazione in moduli e package Mojo

Un file `.mojo` è un modulo. Una directory con `__init__.mojo` è un package il cui initializer può
riesportare l'API pubblica. La struttura attuale è:

```
    architecture/mojo/
    ├── audio/                 FaustAudio, PortAudio, FFI PortAudio
    ├── bench/                 esecuzione benchmark e report
    ├── conf/                  prelude, alias e definizioni compile-time
    ├── dsp/                   FaustDsp, FaustDspGpu, AdapterDsp
    ├── gpu/                   GpuDevice e helper GPU
    ├── gui/                   FaustGui, ControlGui, ProtoGui, TerminalGui, mappa GPU
    │   └── terminal/native/   libreria terminale C11 e Makefile
    ├── help/                  helper matematici, SIMD e I/O
    ├── mem/                   allocazione dei buffer
    ├── meta/                  FaustMeta
    ├── pulse/                 esecuzione degli impulse test
    ├── portaudio.mojo
    ├── portaudio-terminal.mojo
    ├── portaudio-proto.mojo
    ├── portaudio-terminal-gpu.mojo
    ├── bench.mojo
    ├── inspect.mojo
    └── impulse.mojo
```

I template importano dai package pubblici, non dai moduli che li implementano. Importano sempre l'intero
prelude con `from conf import *`; gli altri import dipendono dalle necessità del template. Per esempio,
`impulse.mojo` usa `from pulse import *` e `from gui import FaustGui, ControlGui`. Il template terminale
GPU riceve `AdapterDsp` da `dsp`, `GpuDevice` e `has_accelerator` da `gpu`, `TerminalGui` e la mappa
dei controlli da `gui`, e `PortAudio` da `audio`.

I moduli di implementazione possono importare direttamente un modulo interno per evitare cicli fra i
package. I file `__init__.mojo` stabiliscono l'interfaccia pubblica utilizzata dai template.

### Posizione dei file generati

Il file Mojo generato importa questi package. Occorre passare a Mojo `architecture/mojo` tramite `-I`,
indipendentemente dalla directory che contiene il file generato:

```
    mojo build -I architecture/mojo path/to/generated_dsp.mojo -o generated_dsp
```

Se si compila da `architecture/mojo`, basta `-I .`.

## Ambiente Pixi

Questa directory è un workspace Pixi. `pixi.toml` usa i canali `max-nightly` e `conda-forge`, dipende
da versioni di sviluppo di `modular` e `mojo` ed è configurato per `osx-arm64`. `pixi.lock` conserva la
risoluzione delle dipendenze. Da questa directory:

```
    pixi install
    pixi shell
```

È possibile eseguire un comando anche tramite `pixi run`.

## Componenti comuni

### Configurazione

`conf/prelude.mojo` esporta alias aritmetici e SIMD, tipi puntatore e stream, costanti di memoria e
allineamento e il tipo dei campioni esterni. `conf/__init__.mojo` riesporta tutto il prelude. Il prelude
importa con `*` le definizioni comuni della libreria standard e dell'host GPU.

```
    comptime dfaust = get_defined_dtype["DFAUST", f32]()
    comptime FaustFloat = Scalar[dfaust]
```

`DFAUST` usa `f32` per default e può essere impostato con `-D DFAUST=DType.float32`. Indica il tipo dei
campioni esterni e delle zone UI; è distinto dalla precisione interna selezionata da FAUST con `-single`
o `-double`. I template PortAudio e GPU attuali richiedono campioni esterni a 32 bit. Il generatore Mojo
GPU attuale richiede anche la precisione interna `-single`.

### DSP

Il package `dsp` esporta `FaustDsp`, `FaustDspGpu` e `AdapterDsp`. L'adapter mantiene puntatori al DSP
generato e a un device GPU preparato; delega al DSP inizializzazione, metadati e costruzione della UI, e
implementa `FaustDsp.compute` chiamando `GpuDevice.process`.

### Audio

`audio` esporta `FaustAudio`, `PortAudio`, `SAMP_RATE` e `BUFF_SIZE`. Il contratto `FaustAudio` comprende
`init`, `start`, `stop` e `is_alive`. `audio/portaudio/ffi.mojo` contiene i binding C; l'implementazione
PortAudio apre uno stream `float32` non interleaved e registra una callback che richiama `compute` del DSP.
Lo stesso driver può ricevere un DSP CPU generato oppure l'adapter GPU.

PortAudio definisce `SAMP_RATE` come valore in kHz moltiplicato per 1.000: il default `96` corrisponde a
96 kHz. Il valore predefinito di `BUFF_SIZE` è 256 frame. Per i template PortAudio, quindi, si passa
`-D SAMP_RATE=48` per ottenere 48 kHz.

### GUI

`gui` esporta il trait `FaustGui`, `ControlGui`, `ProtoGui`, `TerminalGui` e gli helper della mappa GPU.
Il metodo generato `build_user_interface` descrive gruppi annidati, controlli, bargraph e metadati usando
i metodi di `FaustGui`. `run()` è la chiamata bloccante della GUI sul thread principale; le operazioni
per widget non supportati possono utilizzare le implementazioni predefinite vuote del trait.

- `ControlGui` gestisce i pulsanti degli impulse test.
- `ProtoGui` è un piccolo prototipo con input testuale.
- `TerminalGui` costruisce una gerarchia di widget basata su stack ed esegue la GUI terminale nativa C11.

La GUI terminale supporta slider, campi numerici, pulsanti, checkbox, bargraph, interazione con il mouse
e inserimento di valori numerici. `gui/terminal/ffi.mojo` collega Mojo a
`gui/terminal/native/termgui.c`. Prima del linking di un'architettura terminale va compilata la libreria:

```
    make -C gui/terminal/native release
```

Il risultato è `gui/terminal/native/build/libtermgui.a`.

### GPU

`gpu` esporta `GpuDevice`, i codici di errore GPU, gli indici dei kernel e `has_accelerator`.
`GpuDevice.prepare` alloca sul device lo stato DSP, i buffer dei canali e la memoria di lavoro.
`GpuControlMap` visita la UI del DSP e registra le zone attive dei controlli e le zone passive dei meter.
Per ogni blocco, il device trasferisce i controlli modificati e gli ingressi, accoda i kernel generati,
copia sul lato host uscite e meter, quindi sincronizza. Lo stato DSP rimane sul device fra i blocchi.
`get_error` riporta gli errori della callback dopo la riproduzione; `release` libera le risorse GPU
quando l'elaborazione è terminata.

Questo è il percorso GPU prototipale corrente: il DSP generato implementa `FaustDspGpu` e l'integrazione
con `FaustAudio` e `PortAudio` avviene tramite composizione con `AdapterDsp`.

### Metadata

`meta` fornisce `FaustMeta`, l'interfaccia usata dal codice generato per esporre i metadati FAUST.

### Help

`help` contiene gli helper matematici, le operazioni SIMD di load e store e l'attesa dell'input usate dal
codice generato e dai template.

### Memory

`mem` fornisce l'allocazione e il rilascio espliciti dei buffer per benchmark, ispezione e impulse test.

### Benchmark e Test

`bench` implementa l'esecuzione e i report utilizzati da `bench.mojo` e `inspect.mojo`. `pulse`
implementa il runner degli impulse test utilizzato da `impulse.mojo`. I rispettivi template top-level
allocano DSP e buffer e invocano le funzioni dei package.

## Architetture disponibili

I template `.mojo` nella directory principale vengono selezionati con l'opzione FAUST `-a`.

**portaudio.mojo**

Alloca e inizializza un DSP CPU, avvia PortAudio, attende input standard sul thread principale, arresta
lo stream e libera il DSP. La callback PortAudio chiama `compute` del DSP.

**portaudio-terminal.mojo**

Costruisce una `TerminalGui` dal DSP CPU, avvia PortAudio ed entra nel loop bloccante della GUI terminale.
La GUI modifica le zone dei controlli nel DSP host; la callback le legge durante l'elaborazione.
Per il linking servono PortAudio e `libtermgui.a`.

**portaudio-proto.mojo**

Costruisce `ProtoGui()` dal DSP CPU ed esegue il suo semplice loop testuale mentre PortAudio elabora
l'audio. È un template per prototipi; l'architettura terminale nativa fornisce una UI più completa.

**portaudio-terminal-gpu.mojo**

Costruisce `TerminalGui`, `GpuControlMap`, `GpuDevice[mydsp]`, `AdapterDsp[mydsp]` e il normale driver
`PortAudio`. Dopo aver preparato il device, passa l'adapter a PortAudio e avvia la GUI sul thread
principale. All'uscita arresta lo stream audio prima di liberare le risorse GPU e DSP. Richiede un DSP
GPU, un acceleratore supportato, PortAudio e `libtermgui.a`.

**bench.mojo**

Alloca i buffer, esegue il warmup del DSP CPU, misura ripetutamente `compute` e produce un report senza
avviare un driver audio. Il package di benchmark controlla l'eventuale output CSV.

**inspect.mojo**

Esegue il DSP CPU tramite una funzione esportata e non inlined chiamata `inspect_compute`. `keep` e
`clobber_memory` facilitano l'individuazione del codice prodotto a basso livello.

**impulse.mojo**

Inizializza il DSP CPU e `ControlGui`, quindi usa `pulse` per stampare la risposta all'impulso nel
formato richiesto dagli impulse test di FAUST.

## Flusso di esecuzione audio

Nei template CPU, `main` inizializza `mydsp`, costruisce eventualmente la GUI e passa il DSP a
`PortAudio.start`. La callback PortAudio chiama `mydsp.compute`. Il thread principale attende in `run`
della GUI o nel loop di input dell'architettura, quindi arresta PortAudio e libera il DSP.

```
    main                             callback PortAudio
      |                                      |
      +--> mydsp.init                        |
      +--> build_user_interface (opzionale) |
      +--> PortAudio.start(mydsp) ---------> mydsp.compute
      +--> GUI.run / attesa input            |
      +--> PortAudio.stop <------------------+
      +--> libera mydsp
```

Nel template terminale GPU, `main` crea inoltre la mappa dei controlli e il device prima di chiamare
`PortAudio.start(adapter)`. La callback chiama `AdapterDsp.compute`, che invoca `GpuDevice.process`:
controlli host e ingressi raggiungono il device, i kernel generati elaborano il blocco, poi uscite audio
e meter tornano sull'host. La callback termina il blocco dopo la sincronizzazione GPU.

## Configurazione a compile time

Le definizioni Mojo `-D` specializzano l'architettura durante la build del file generato:

```
    -D DFAUST=DType.float32 -D SAMP_RATE=48 -D BUFF_SIZE=128
```

Per PortAudio, `SAMP_RATE=48` indica 48 kHz. Il benchmark definisce invece il sample rate direttamente
in Hz (default 96.000); anche `pulse` usa Hz (default 44.100). `BUFF_SIZE` misura i frame. Benchmark e
ispezione usano altre definizioni, fra cui `COMPUTE_ITERS`.

Le opzioni FAUST `-single` e `-double` selezionano la precisione *interna* del DSP. `-gpu` seleziona il
generatore Mojo GPU sperimentale, che attualmente richiede `-single` e produce un DSP conforme a
`FaustDspGpu` per il relativo template.

## Workflow essenziale

Da `architecture/mojo`, si genera un DSP CPU con il template terminale:

```
    make -C gui/terminal/native release
    /path/to/faust -lang mojo -single -a portaudio-terminal.mojo \
        -o program.mojo src/phasorsine.dsp
```

Si compila fornendo i package dell'architettura e le librerie native al linker:

```
    mojo build -O3 -I . -D DFAUST=DType.float32 -D SAMP_RATE=48 -D BUFF_SIZE=128 \
        -Xlinker -L/opt/homebrew/opt/portaudio/lib -Xlinker -lportaudio \
        -Xlinker gui/terminal/native/build/libtermgui.a -Xlinker -lm \
        -o program program.mojo
```

Per elaborare sulla GPU si selezionano il generatore e il template GPU, quindi si compila con le stesse
opzioni di linking di PortAudio e della libreria terminale:

```
    /path/to/faust -lang mojo -gpu -single -a portaudio-terminal-gpu.mojo \
        -o program_gpu.mojo src/phasorsine.dsp
    mojo build -O3 -I . -D DFAUST=DType.float32 -D SAMP_RATE=48 -D BUFF_SIZE=128 \
        -Xlinker -L/opt/homebrew/opt/portaudio/lib -Xlinker -lportaudio \
        -Xlinker gui/terminal/native/build/libtermgui.a -Xlinker -lm \
        -o program_gpu program_gpu.mojo
```

La directory della libreria PortAudio va adattata all'installazione locale. Per usare `portaudio.mojo`,
`portaudio-proto.mojo`, `bench.mojo`, `inspect.mojo` o `impulse.mojo`, basta cambiare il template passato
a `-a` e fornire le librerie richieste dal template scelto.
