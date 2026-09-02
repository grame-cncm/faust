# Faust to Mojo architectures

Il contenuto di questa cartella implementa le architetture e le componenti di supporto utilizzate dal
backend Mojo di FAUST per trasformare il codice DSP transpilato in un programma eseguibile.

Un backend di FAUST si compone infatti di due parti principali:

- il **generatore**, che traduce la rappresentazione intermedia di FAUST nel linguaggio target;
- il **sistema di architetture**, che fornisce l'ambiente necessario per utilizzare il DSP generato.

Nel caso del backend Mojo, il generatore produce principalmente la `struct mydsp`, contenente lo stato,
le operazioni di inizializzazione, i metadati, la descrizione dell'interfaccia utente e il kernel `compute`.

Le architetture presenti in questa directory forniscono invece le componenti esterne al DSP: driver audio,
interfacce utente, gestione dei buffer, funzioni di supporto e punti di ingresso dell'applicazione.

In questo modo il codice di elaborazione rimane indipendente dal contesto nel quale viene eseguito. Lo
stesso DSP può quindi essere inserito in architetture differenti senza modificare il codice prodotto dal
generatore.

## Architetture FAUST

Un'architettura FAUST è un file nel linguaggo target (nella fattispecie Mojo) usato come template durante
la compilazione. Il file contiene il codice necessario ad utilizzare il DSP e due punti nei quali il
compilatore inserisce il codice generato:

```
    <<includeIntrinsic>>
    <<includeclass>>
```

Nel caso di Mojo solo `<<includeclass>>` viene effettivamente rimpiazzato. Il codice iniettato è l'output di

```
    MojoCodeContainer.produceClass()
```

tuttavia nei file si utilizza anche `<<includeIntrinsic>>` per il corretto funzionamento del compilatore.

Una normale architettura Mojo assume quindi la seguente forma:

```
    codice fornito dall'architettura
    |
    |--> import, tipi e componenti di supporto
    |
    codice generato da FAUST
    <<includeIntrinsic>>
    <<includeclass>> 
    |
    |--> vengono sostituite le tag con la struct
    |
    codice fornito dall'architettura
    |
    |--> main, driver, allocazione e controllo dell'esecuzione
    |
    EOF
```

I file `portaudio.mojo`, `portaudio-terminal.mojo`, `bench.mojo`, `inspect.mojo` e `impulse.mojo` seguono
tutti questo schema. Ciò che cambia è il codice che circonda `mydsp` e, di conseguenza, lo scopo del
programma risultante.

Questa separazione è particolarmente importante nel modello FAUST: il generatore non deve conoscere il
driver audio, il sistema di interfaccia utente o il framework di benchmark utilizzato. Produce solamente un
DSP conforme al contratto atteso dalle architetture.

Si precisa che, in questo contesto, viene considerato codice di architettura anche il codice di supporto
contenuto nelle sottocartelle di `architecture/mojo`. Tali moduli sono l'implementazione interna delle
componenti dell'architettura e vengono utilizzati dai template presenti direttamente in `architecture/mojo`. 

I template vengono passati al compilatore FAUST tramite l'opzione `-a` per costruire il programma Mojo
completo attorno al DSP generato.

## Interfaccia del DSP

Il contratto comune tra il DSP generato e le architetture è rappresentato dal trait `FaustDsp`, dichiarato
in `dsp/dsp.mojo`.

Il trait descrive le operazioni che una classe DSP generata deve fornire. Fra queste sono presenti:

- gli accessor per sample rate, numero di ingressi e numero di uscite;
- le operazioni di inizializzazione e reset dell'istanza;
- la produzione dei metadati e della descrizione JSON;
- la costruzione dell'interfaccia utente;
- il metodo `compute`, che esegue il calcolo del DSP su un blocco di campioni.

L'interfaccia principale per il calcolo è concettualmente:

```
    dsp.compute(count, inputs, outputs)
```

dove `count` indica il numero di frame da elaborare e `inputs` e `outputs` rappresentano rispettivamente
gli stream di ingresso e di uscita.

La relazione tra generatore e architetture può essere riassunta come segue:

```
    programma FAUST
    |
    FAUST compiler
    |
    +------------------+
    |                  |
    generatore Mojo          |
    |            architecture file
    struct mydsp            |
    |                  |
    +--------+---------+
    |
    sorgente Mojo completo
    |
    compilatore Mojo
    |
    applicazione
```

Le architetture non dipendono quindi dall'implementazione interna di un particolare DSP, ma unicamente
dall'interfaccia comune esposta dalla classe generata.

## Organizzazione in moduli e package Mojo

Mojo distingue tra **moduli** e **package**. Un file `.mojo` può essere utilizzato come modulo, mentre una
directory viene riconosciuta come package quando contiene un file `__init__.mojo`.

Questa directory sfrutta tale organizzazione per separare le differenti responsabilità dell'architettura.

```
    architecture/mojo/
    ├── audio/
    │   ├── __init__.mojo
    │   └── portaudio/
    ├── conf/
    │   ├── __init__.mojo
    │   └── prelude.mojo
    ├── dsp/
    │   ├── __init__.mojo
    │   └── dsp.mojo
    ├── gui/
    │   ├── __init__.mojo
    │   ├── gui.mojo
    │   ├── terminal.mojo
    │   └── control.mojo
    ├── help/
    ├── mem/
    ├── meta/
    ├── bench/
    ├── test/
    ├── portaudio.mojo
    ├── portaudio-terminal.mojo
    ├── bench.mojo
    ├── inspect.mojo
    └── impulse.mojo
```

I file `__init__.mojo` espongono l'interfaccia pubblica del relativo package, generalmente re-esportando le
definizioni dei moduli interni. Questo permette alle architetture top-level di utilizzare import sintetici:

```
    from conf import *
    from dsp import *
    from gui import *
    from meta import *
```

### Posizione dei file transpilati

Le architetture importano package locali come `conf`, `dsp`, `gui`, `meta`, `mem` e `audio`. Per rendere
disponibili questi package al compilatore Mojo, `architecture/mojo` deve essere incluso nel percorso di
ricerca tramite l'opzione `-I`.

Ad esempio, dopo l'espansione di `portaudio.mojo`, il file transpilato contiene:

```
    from conf import *
    from dsp import *
    from gui import *
    from meta import *
    from audio.portaudio import *
```

Il file transpilato può essere generato in qualsiasi directory, purché durante la compilazione venga fornito
il percorso che contiene i package dell'architettura:

```
    mojo build -I architecture/mojo path/to/generated_dsp.mojo -o generated_dsp
```

## Ambiente Pixi

La directory costituisce anche un workspace Pixi autonomo. Il file `pixi.toml` definisce l'ambiente nel
quale vengono compilate ed eseguite le architetture Mojo.

Il manifest utilizza i canali:

```
    channels = [
        "https://conda.modular.com/max-nightly",
        "conda-forge"
    ]
```

e installa versioni nightly di `modular` e `mojo`. Il workspace è configurato per `osx-arm64`.

L'ambiente può essere installato e attivato dalla directory con:

```
    pixi install
    pixi shell
```

Un comando può essere eseguito direttamente nell'ambiente anche tramite `pixi run` (`pixi run mojo build ..`).

Il file `pixi.lock` memorizza la risoluzione concreta delle dipendenze e permette di ricostruire lo stesso
ambiente a partire dal manifest.

## Componenti comuni

Le sottodirectory implementano componenti riutilizzabili dalle diverse architetture top-level.

### Configurazione

Il package `conf` contiene le definizioni comuni necessarie sia al codice generato sia alle architetture.

Il modulo `conf/prelude.mojo` centralizza in particolare:

- alias per i tipi aritmetici utilizzati dal backend;
- tipi e costanti `DType`;
- alias per i tipi SIMD;
- tipi puntatore e relativi origin;
- rappresentazione degli stream audio;
- costanti relative all'allineamento e alla memoria;
- definizione della precisione esterna `DFAUST`.

La precisione dell'architettura viene configurata a compile time tramite l'opzione:

```
    -D DFAUST=DType.float32
```

Il tipo viene quindi recuperato nel codice attraverso `get_defined_dtype`:

```
    comptime dfaust = get_defined_dtype["DFAUST", DType.float32]()
```

e utilizzato per definire `FaustFloat`:

```
    comptime FaustFloat = Scalar[dfaust]  # SIMD[dfaust, 1]
```

`FaustFloat` rappresenta quindi il tipo numerico utilizzato dall'architettura e assume la precisione
specificata tramite `DFAUST`; se l'opzione non viene fornita, viene utilizzato `f32`.

### DSP

Il package `dsp` definisce il trait `FaustDsp` che rappresenta il contratto fra il codice prodotto dal
generatore e il resto dell'architettura.

Le architetture possono quindi essere scritte genericamente rispetto al tipo concreto del DSP. Il driver
audio, ad esempio, richiede semplicemente un tipo conforme a `FaustDsp` e può invocarne gli accessor e il
metodo `compute` senza conoscere i campi o le operazioni generate per un particolare programma FAUST.

### Audio

Il package `audio` contiene l'astrazione del driver audio.

Il modulo `audio/audio.mojo` definisce il trait `FaustAudio`, composto dalle operazioni:

```
    init
    start
    stop
```

Un driver audio concreto implementa tale contratto e riceve un DSP conforme a `FaustDsp`.

L'implementazione basata su `PortAudio` si trova nel package `audio/portaudio`, ulteriormente separato in:

- `ffi.mojo`, che espone le definizioni necessarie per interagire con la API C di PortAudio;
- `portaudio.mojo`, che implementa il driver `PortAudio` e gli helper specifici per FAUST.

Il driver inizializza `PortAudio`, seleziona i dispositivi di ingresso e uscita, costruisce i parametri dello
stream e registra una callback associata all'istanza DSP.

All'arrivo di un nuovo blocco audio, la callback converte i buffer ricevuti da PortAudio nella
rappresentazione attesa dal backend e richiama:

```
    dsp[].compute(S32(count), inputs, outputs)
```

Il thread audio diventa quindi responsabile dell'invocazione real-time del kernel generato.

### GUI

Il package `gui` definisce l'astrazione delle interfacce utente attraverso il trait `FaustGui`.

Il trait riproduce le operazioni utilizzate dal sistema UI di FAUST per descrivere gerarchie di widget,
controlli attivi, bargraph e metadati. La maggior parte delle operazioni ha implementazione vuota: una GUI
concreta può quindi implementare solamente le funzionalità di cui necessita.

Il metodo `build_user_interface` generato all'interno di `mydsp` riceve una implementazione di `FaustGui` e
registra presso di essa i parametri del DSP. Le zone associate ai controlli fanno riferimento direttamente
ai campi della struttura DSP, permettendo a una interfaccia di modificare i parametri utilizzati da `compute`.

Non è stato investito tempo nella realizzione di una GUI completa. Attualmente si hanno le seguenti.

- `TerminalGui` − Una semplice interfaccia testuale usata a scopo dimostrativo e di prototyping.
- `ControlGui` − Utilizzata dal framework degli impulse test per controllare i parametri del DSP.

In particolare, `TerminalGui`, conserva una rappresentazione dei widget costruiti da FAUST e permette di
modificare da terminale il valore di uno slider mentre il thread audio continua ad eseguire il DSP.

### Metadata

Il package `meta` fornisce l'interfaccia utilizzata dal codice generato per esportare i metadati associati
al programma FAUST.

### Help

Il package `help` contiene funzioni di supporto utilizzate dal codice generato. Queste utility semplificano
l'implementazione del visitor e mantengono il codice prodotto più compatto e leggibile.

Il package raccoglie principalmente helper matematici e operazioni SIMD di load e store polimorfiche che
lavorano sia con puntatori sia con array. (`vload, vstore`).

### Memory

Il package `mem` contiene le utility per l'allocazione e la gestione manuale dei buffer. Questo package
viene principalmente utilizzato dalle architetture di test, benchmark e ispezione.

### Benchmark e Test

I package `bench` e `test` contengono il codice specifico per l'integrazione rispettivamente con il
framework di benchmark e con i gli `impulse-tests` del backend.

Le architetture top-level corrispondenti rimangono leggere: inizializzano il DSP, costruiscono i buffer
necessari e delegano il lavoro alle funzioni fornite da questi package.

## Architetture disponibili

I file `.mojo` presenti direttamente nella directory costituiscono i template destinati ad essere passati
a FAUST tramite l'opzione `-a`.

**portaudio.mojo**

L'architettura `portaudio.mojo` integra il DSP generato con `PortAudio`.

Il programma risultante:

1. alloca una istanza di `mydsp`;
2. inizializza il DSP con il sample rate;
3. inizializza il driver `PortAudio`;
4. apre e avvia lo stream audio;
5. mantiene attivo il thread principale mentre `PortAudio` esegue il DSP nella propria callback;
6. arresta il driver e libera l'istanza.

Il driver `PortAudio` supporta unicamente precisione a 32 bit, per cui l'architettura verifica a compile
time che `DFAUST` corrisponda a `f32`.

**portaudio-terminal.mojo**

L'architettura `portaudio-terminal.mojo` estende il caso precedente aggiungendo `TerminalGui`.

Dopo l'inizializzazione del DSP viene costruita l'interfaccia:

```
    var gui = TerminalGui[dfaust]()
    dsp[].build_user_interface(gui)
```

Il driver audio viene quindi avviato normalmente, mentre il thread principale entra nel loop della GUI.
L'utente può modificare i parametri esposti dal DSP e tali modifiche vengono osservate dal successivo
calcolo audio.

Questa architettura mostra l'interazione fra il DSP generato, un driver audio e una implementazione del
modello grafico di FAUST.

**bench.mojo**

L'architettura `bench.mojo` integra il codice Mojo con il framework di benchmark.

Non viene utilizzato un driver audio reale. L'architettura alloca direttamente i buffer di ingresso e
uscita, inizializza il DSP, esegue una fase di warmup e misura ripetutamente `compute`.

Il risultato viene trasformato in un report e può essere scritto nei formati utilizzati dal framework,
permettendo di confrontare il codice Mojo con le altre implementazioni senza introdurre il costo o la
variabilità di un sistema audio real-time.

**inspect.mojo**

L'architettura `inspect.mojo` è destinata all'ispezione di codice a basso livello prodotto da Mojo.

Anche in questo caso vengono allocati direttamente i buffer e viene inizializzata una istanza DSP, ma il
kernel viene richiamato attraverso una funzione dedicata:

```
    @no_inline
    @export("inspect_compute")
    def inspect_compute(...)
```

Il simbolo esplicito e la disabilitazione dell'inlining rendono più semplice individuare il codice
corrispondente a `compute` e analizzarne assembly o rappresentazioni intermedie.

Le primitive `keep` e `clobber_memory` impediscono inoltre che il compilatore elimini il calcolo durante
l'ottimizzazione.

**impulse.mojo**

L'architettura `impulse.mojo` integra il backend con il sistema di impulse test di FAUST.

L'architettura inizializza il DSP e una `ControlGui`, genera l'header previsto dal framework e delega
l'esecuzione alle utility contenute in `test/impulse`.

I campioni prodotti vengono stampati su standard output. Il framework esterno può quindi redirigerli nei
file `.ir` e confrontare la risposta del backend Mojo con le implementazioni `.ir` di riferimento.

## Flusso di esecuzione audio

Nel caso di una applicazione PortAudio, l'interazione completa fra le componenti è:

```
    main
    |
    +--> alloca mydsp
    |
    +--> mydsp.init(sample_rate)
    |
    +--> [opzionale] mydsp.build_user_interface(gui)
    |
    +--> PortAudio.init()
    |
    +--> PortAudio.start(mydsp)
    |        |
    |        +--> legge numero ingressi/uscite dal DSP
    |        +--> apre lo stream
    |        +--> registra faust_callback
    |
    +--> thread principale rimane attivo
    |
    |                  thread PortAudio
    |                       |
    |                       v
    |                faust_callback
    |                       |
    |                       v
    |             mydsp.compute(...)
    |                       |
    |                       v
    |                  output audio
    |
    +--> PortAudio.stop()
    |
    +--> libera mydsp
```

Il punto di contatto fra le componenti rimane `FaustDsp`: il generatore produce la classe conforme al trait,
mentre l'architettura decide quando e in quale contesto invocarne le operazioni.

## Configurazione a compile time

Diverse proprietà delle architetture vengono configurate a compile time passando opzioni `-D` al
compilatore Mojo, ad esempio:

```
    mojo build -D DFAUST=DType.float32 -D BUFF_SIZE=128 -D SAMP_RATE=48000 ...
```

I valori vengono quindi recuperati nel codice tramite le funzioni fornite da `std.sys.defines`, come
`get_defined_dtype` e `get_defined_int`.

Fra le opzioni utilizzate dalle componenti sono presenti:

- `DFAUST`, che seleziona il tipo numerico degli stream esterni;
- `BUFF_SIZE`, che controlla la dimensione del blocco nelle architetture che la espongono;
- `SAMP_RATE`, che seleziona il sample rate;
- ulteriori opzioni specifiche dei framework di benchmark e ispezione.

Questo meccanismo permette di specializzare l'architettura durante la compilazione senza modificarne il
codice sorgente.

## Workflow essenziale

Una tipica generazione combina un programma FAUST con una architettura attraverso l'opzione `-a`. Ad esempio,
dalla root del repository:

```
    build/bin/faust \
    -lang mojo \
    -a architecture/mojo/portaudio.mojo \
    path/to/program.dsp \
    -o path/to/program.mojo
```

Il file transpilato può quindi essere compilato indicando il percorso dei package dell'architettura:

```
    mojo build \
    -I architecture/mojo \
    path/to/program.mojo \
    -o path/to/program
```

Per utilizzare una architettura diversa è sufficiente cambiare il template passato a `-a`:

```
    -a architecture/mojo/portaudio-terminal.mojo
    -a architecture/mojo/bench.mojo
    -a architecture/mojo/inspect.mojo
    -a architecture/mojo/impulse.mojo
```

La separazione tra generatore, interfacce comuni e architecture file permette di utilizzare lo stesso
backend Mojo in differenti contesti di esecuzione.
