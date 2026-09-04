## Faust to Mojo generator

Il codice presente in questa cartella implementa il transpilatore da FAUST a Mojo.

### File miscellanei

- `.clangd`: configurazione per silenziare alcuni errori dello LSP Clangd
  - Definisce la variabile di ambiente `MOJO_BUILD=1`, utilizzata successivamente a compile time.

### File di configurazione

Si tratta dei file prefissi da `_`, contenenti codice privato che esula dalle classi strettamente utilizzate
dalle altre componenti compilatore (`faust/compiler`, `faust/compiler/generator`).

- `_mojo_hal.hh`: codice per l'astrazione dall'hardware sottostante (`Hardware Abstraction Layer`).
- `_mojo_macro.hh`: macro per ergonomia e pulizia semantica del codice pubblico.
- `_mojo_utils.hh`: funzioni helper per le classi pubbliche principali.

### File principali

Contengono le classi principali del backend, le cui interfacce vengono utilizzate dalle altre componenti
del compilatore.

I file si suddividono in file di intestazione (`*.hh`), contenenti le dichiarazioni delle classi, e file
di implementazione (`*.cpp`), contenenti le relative definizioni.

Le due componenti principali sono:

- `MojoInstVisitor` − Il produttore che traduce le istruzioni della `FAUST IR` in codice `Mojo` e le scrive
  sullo stream di output.
- `MojoCodeContainer` − Usa il produttore per costruire il tipo (`struct mydsp`) che incapsula il kernel DSP.

In altri termini, il visitor attraversa le istruzioni della `FAUST IR` e ne produce la rappresentazione
testuale in `Mojo`; il container organizza il codice prodotto per costruire la struttura che rappresenta
il programma `FAUST`.

- `mojo_instructions.hh` − Dichiara `MojoInstVisitor` e le derivate `MojoVecInstVisitor` e `MojoInitFieldsVisitor`.
- `mojo_code_container.hh` − Dichiara `MojoCodeContainer` e le derivate `MojoScalarCodeContainer` e `MojoVecCodeContainer`.

- `mojo_instructions.cpp` − Implementa `MojoInstVisitor` e `MojoInitFieldsVisitor`.
- `mojo_vec_instructions.cpp` − Implementa `MojoVecInstVisitor`.
- `mojo_code_container.cpp` − Implementa `MojoCodeContainer` e la derivata `MojoVecCodeContainer`.

### Instructions Visitor

Il linguaggio `FAUST` descrive il DSP in forma puramente funzionale. Durante la transpilazione, questa viene
progressivamente trasformata nella `FAUST IR`, una rappresentazione intermedia procedurale e imperativa
composta da istruzioni tipizzate per dichiarazioni, espressioni, accessi alla memoria, cicli e controllo di
flusso. Il backend Mojo attraversa questa IR e traduce ciascuna istruzione nel corrispondente codice
sorgente `Mojo`, organizzato dal *Code Container*  in una `struct` che rappresenta il DSP generato.

La traduzione è implementata da `MojoInstVisitor` mediante il *visitor pattern*. La classe deriva da
`TextInstVisitor`, dal quale eredita l'infrastruttura comune per attraversare l'IR e produrre codice
testuale indentato su uno stream di output, e sovraccarica l'operazione `visit` per i differenti tipi di
istruzione. Quando un'istruzione accetta il visitor, viene selezionata l'operazione corrispondente al suo
tipo concreto.

`MojoInitFieldsVisitor` è un visitor specializzato nella generazione delle inizializzazioni dei campi
nel *default constructor* `__init__` della `struct` DSP. Per ogni dichiarazione emette l'assegnamento
al relativo campo, usando il valore presente nella `FAUST IR` oppure, quando assente, un inizializzatore
a zero appropriato al tipo.

### Code Container

`MojoCodeContainer` organizza il codice prodotto dagli instruction visitor e costruisce la `struct`
che rappresenta il DSP in `Mojo`. La classe deriva da `CodeContainer` e definisce la struttura comune
del programma generato.

L'interfaccia principale del container è `produceClass`, che coordina la generazione delle diverse sezioni.
Per convenzione, gli helper che scrivono le singole sezioni del codice hanno il prefisso `write`. Il
container genera:

- l'intestazione e le definizioni dei tipi numerici;
- la dichiarazione della `struct` e dei relativi campi;
- il *default constructor* e l'inizializzazione dei campi;
- gli accessor per sample rate, numero di ingressi e numero di uscite;
- le funzioni di inizializzazione e reset dell'istanza;
- i metadati e la rappresentazione JSON del DSP;
- il metodo per la costruzione dell'interfaccia utente;
- il metodo `compute` contenente il calcolo del DSP.

`MojoCodeContainer` è una classe astratta dalla quale derivano `MojoScalarCodeContainer` e
`MojoVecCodeContainer`. La factory `createContainer` seleziona la variante appropriata in base alle
opzioni di compilazione: il container scalare viene usato per la generazione ordinaria, mentre quello
vettoriale viene istanziato quando è attiva l'opzione `-vec`. Le due implementazioni condividono la
struttura generale della `struct` e specializzano la generazione di `compute` tramite `writeCompute`.

La produzione delle istruzioni utilizza due visitor globali: `gScalarProducer`, condiviso dalle parti
scalari del codice, e `gVectorProducer`, creato dal container vettoriale per la generazione esplicita
SIMD. Anche in modalità  vettoriale, dichiarazioni, inizializzazioni, metadati e interfaccia utente
continuano a essere prodotti dal visitor scalare; il visitor vettoriale viene utilizzato solamente
per la generazione del metodo `compute`.

Il container vettoriale deriva inoltre da `VectorCodeContainer`, il quale incapsula la rappresentazione del
calcolo vettoriale e la capacità  di individuare i nodi ricorsivi e quelli che possono essere vettorizzati.

### Explicit SIMD emission

Con l'opzione `-vec`, FAUST riorganizza la rappresentazione imperativa del DSP suddividendo il calcolo in
sottocicli ordinati secondo le dipendenze descritte dal relativo DAG. I sottocicli vengono inoltre distinti
tra ricorsivi, quindi non vettorizzabili, e indipendenti tra le iterazioni.

Nel percorso tradizionale di FAUST, questa forma permette al compilatore del linguaggio target, ad esempio
`clang`, di autovettorizzare i sottocicli compatibili. Mojo disabilita invece i pass di autovettorizzazione
di LLVM, per cui l'emissione scalare non viene convertita automaticamente in istruzioni vettoriali.

Il backend Mojo utilizza quindi la suddivisione in sottocicli prodotta da `-vec` come base per una
vettorizzazione esplicita, sfruttando il sistema di tipi SIMD fornito dal linguaggio.

Il tipo numerico fondamentale è `SIMD[dtype, width]`, dove `dtype` è il tipo primitivo, ad esempio
`f32`, e `width` è la larghezza del vettore, ovvero il numero di elementi sui quali l'operazione viene
eseguita in parallelo. `SIMD[dtype, 1]` corrisponde al caso scalare `Scalar[dtype]`; la `width` viene
inoltre utilizzata come parametro nelle operazioni di metaprogrammazione.

Nel backend Mojo i sottocicli ricorsivi vengono sottoposti ad unrolling completo di `vsize` operazioni
tramite `comptime for`, mentre i cicli indipendenti vengono tradotti in istruzioni SIMD esplicite.

Il fallback scalare viene applicato anche ai cicli che, pur non essendo ricorsivi, contengono accessi alla
memoria non compatibili con una vettorizzazione contigua. 

L'implementazione richiede alcune assunzioni e workaround, descritti nei paragrafi seguenti, che in alcuni
casi introducono un accoppiamento tra le responsabilità  del container e del visitor. Queste soluzioni
permettono di adattare la struttura della `FAUST IR` e le espressioni generate ai vincoli del type system
di Mojo.

La prima importante assunzione riguarda la precisione di calcolo dei numeri reali. La modalità  di emissione
SIMD supporta unicamente precisione di calcolo interna `f64` e precisione dell'architettura del driver
esterno di `f32`.

#### Vector Code Container

`MojoVecCodeContainer` deriva sia da `MojoCodeContainer` sia da `VectorCodeContainer`. Il primo fornisce la
struttura comune della `struct` DSP, mentre il secondo trasforma il kernel DSP in un grafo di cicli.

Il container genera esplicitamente l'indice `vindex`, il limite `end` e l'incremento del ciclo principale.
La dichiarazione equivalente viene rimossa dal DAG, mentre `MojoVecInstVisitor` riconosce il main loop dal
nome `vindex`. Questo introduce un accoppiamento intenzionale tra container e visitor.

Nel codice generato si ricavano le larghezze native del target:

```
    vsize = simd_width_of[f32]()
    hsize = simd_width_of[f64]()
```

dove `vsize` significa "vector size" ed `hsize` significa "half size".

Poiché un vettore `f32` contiene il doppio delle lane di un vettore `f64`, vale la relazione:

```
    vsize = 2 * hsize
```

Il nome `vsize` è stato scelto per continuità  semantico con l'opzione `-vs` di FAUST e il loro valore deve
coincidere ai fini della correttezza:

- FAUST genera sub-loop di `-vs` frame (e.g. `for i in 0..vsize`),
- Mojo utilizza `vsize` (ed `hsize`) per definire tipi, invocare operazioni ed avanzare nel buffer,

una discrepanza tra i due valori introduce degli errori strutturali.

Il backend risulta indipendente da una specifica estensione hardware SIMD, purché la compilazione FAUST usi
la larghezza `f32` nativa del target:

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

La generazione utilizza inoltre `-mcd 4`, che definisce la soglia oltre la quale le delay line vengono
rappresentate mediante ring buffer anziché tramite copie.

Nella vec mode del backend Mojo, `-vs` e `-mcd` devono coincidere con `vsize`. Con `-vs 4 -mcd 4`, delay
line inferiori alla soglia vengono arrotondate a quattro elementi, altrimenti utilizzano un ring buffer.

I sottocicli sono quindi compatibili con l'elaborazione in blocchi di `vsize` frame.

L'invocazione attualmente supportata è quindi:

```
    faust -double -vec -dfs -vs 4 -mcd 4 -lang mojo [name].dsp -o [name].mojo
```

Il backend è stato testato con unicamente con tale configurazione su Apple M1 e M4, basati su SIMD NEON da
128 bit. Le configurazioni x86 sono teoricamente supportate ma non sono state verificate.

#### Vector Instructions Visitor

`MojoVecInstVisitor` deriva da `MojoInstVisitor` del quale riutilizza le operazioni per istruzioni scalari. 

Le operazioni `visit` specializzate, oltre a generare costruttori vettoriali, cast, operazioni binarie,
caricamenti e scritture SIMD, classificano i sottocicli in base alla strategia di emissione richiesta.

La visita di un ciclo interno puà² produrre:

- una singola scrittura SIMD su destinazione `f32` (di `vsize` elementi);
- il broadcast di un valore scalare;
- due scritture SIMD per una destinazione `f64` (di `2 * hsize` elementi);
- il join di due risultati `f64` con scrittura finale su `f32`;
- un ciclo scalare con unrolling `comptime for` per i cicli ricorsivi;
- un ciclo scalare con unrolling `comptime for` per forme con accesso a memoria non lineare;
- un trattamento specializzato per l'aggiornamento di un bargraph e di un parametro ad esso legato;
- un trattamento specializzato per l'aggiornamento di bargraph multipli e di un parametro non legato ad essi.

Il visitor assume che l'ultima (o unica) istruzione del ciclo sia lo `StoreVarInst` principale. Da questa
ricava la destinazione, il tipo del risultato e la strategia necessaria per generare l'intero ciclo.

#### Stato di generazione

`MojoVecInstVisitor` suddivide la logica di generazione tra le operazioni `visit` e i relativi helper. Per
condividere il contesto tra questi metodi mantiene uno stato globale per il ciclo corrente.

- `gSIMDEmit` indica se le istruzioni visitate devono essere emesse in forma SIMD;
- `gSIMDHigh` indica la generazione della seconda porzione di un blocco `f64` (con shift di `hsize`);
- `gSIMDHalf` seleziona la larghezza `H`, corrispondente alla larghezza SIMD di `f64` (`Half`);
- `gCurLhsDT` mantiene il tipo del risultato assegnato dal ciclo corrente (`Current Lhs DType`);
- `gCurAddrs` mantiene il nome della destinazione corrente;
- `gCurIndex` identifica l'indice del ciclo FAUST eliminato durante la vettorizzazione;
- `gCurBargraph` identifica un bargraph i cui valori vengono salvati temporaneamente in un array.

La flag `gSIMDHalf` genera operazioni con parametro esplicito `H`, come `vstore[H]`, ed è essenziale per
ottenere risultati nei quali il tipo numerico non corrisponde alla larghezza SIMD nativa, ad esempio:

```
    SIMD[f32, simd_width_of[f64]()`
```

#### Macro di visita contestuale

Le macro SIMD applicano generalmente un pattern di salvataggio e ripristino dello stato:

```
    salva il valore corrente della flag
    imposta il nuovo contesto
    visita l'istruzione
    ripristina il valore precedente
```

`mj_simd_emit_set` e `mj_simd_emit_restore` delimitano una regione di emissione SIMD, mentre
`mj_simd_emit_accept` applica lo stesso pattern attorno alla visita di una singola istruzione.
`mj_simd_high_accept` visita un'espressione con `gSIMDHigh` attivo per produrre la seconda porzione `f64`.
Le macro `mj_scalar_accept` e `mj_scalar_visit` disattivano invece temporaneamente l'emissione SIMD e
delegano la traduzione al comportamento scalare ereditato da `MojoInstVisitor`.

Questo meccanismo evita di replicare manualmente la gestione delle flag in ogni operazione `visit`
e preserva il contesto esterno durante le visite ricorsive.

#### Precisione mista e larghezze SIMD

La differenza tra `vsize` e `hsize` richiede una gestione esplicita delle espressioni a precisione
mista. I valori numerici vengono emessi usando costruttori differenti secondo il tipo e il contesto:

```
    s32  -> S32Vec / S32Hec
    f32  -> F32Vec / F32Hec
    f64  -> F64Vec
```

I tipi `Hec` rappresentano valori `s32` o `f32` con lo stesso numero di lane del vettore `f64`. Sono
necessari, quando un intero o un valore `f32` partecipa a un'espressione `f64`.

La flag `gSIMDHalf` propaga questa scelta a tutti gli operandi successivi dell'espressione, evitando
operazioni tra vettori con larghezze incompatibili.

Quando la destinazione è `f64`, il visitor genera separatamente la porzione bassa e quella alta:

```
    vstore(dst, low)
    vstore(dst, high, hsize)
```

Durante la seconda visita `gSIMDHigh` aggiunge `hsize` agli accessi indicizzati. Quando invece
un'espressione `f64` deve essere scritta su un'uscita `f32`, le due porzioni vengono combinate:

```
    vstore(dst, low.join(high))
```

#### Analisi degli accessi alla memoria

La vettorizzazione è consentita solamente quando ogni lane SIMD accede a indirizzi consecutivi.
Il visitor riconosce attualmente indici affini semplici rispetto all'indice del ciclo:

```
    A[i]
    A[i + c]
    A[i - c]
    A[c + i]
```

`gCurIndex` rappresenta l'indice scalare rimosso dal ciclo vettoriale, mentre `visitIndex` traduce
queste forme in un offset per `vload` o `vstore`. Durante la generazione della porzione alta `f64`
viene aggiunto un ulteriore offset pari a `hsize`.

Indici circolari, operatori diversi da somma e sottrazione, chiamate di funzione e accessi indiretti
sono classificati come non vettorizzabili. Espressioni quali:

```
    table[f(i)]
    buffer[(i + offset) & mask]
```

richiederebbero rispettivamente operazioni gather o una gestione esplicita dell'indirizzamento delle
singole lane. Poiché queste operazioni non sono ancora implementate, il ciclo viene conservativamente
tradotto mediante il percorso scalare. Un normale `vload` contiguo non sarebbe infatti semanticamente
equivalente a un gather.

#### Fallback scalare e casi speciali

I cicli ricorsivi e quelli con accessi non vettorizzabili vengono emessi come cicli scalari svolti
per le `vsize` lane del blocco corrente:

```
    comptime for i in range(vsize):
        scalar body
```

Il fallback usa `MojoInstVisitor` per emettere le operazioni scalari, preservandone l'ordine anche
dopo l'unrolling.

I bargraph vengono gestiti distinguendo due casi:

- Il bargraph è direttamente collegato al parametro scritto dallo store finale. Il valore viene
  calcolato in SIMD e il bargraph viene aggiornato con l'ultimo elemento del blocco.

- Il ciclo contiene più aggiornamenti di bargraph, seguiti dallo store di un parametro non direttamente
  correlato. Gli aggiornamenti vengono emessi scalarmente tramite `comptime for`, mentre lo store
  finale viene elaborato separatamente secondo le regole di vettorizzazione di cui sopra.

Il riconoscimento è basato sul numero delle istruzioni e sui nomi contenenti `bargraph`, assumendo
che lo store del parametro sia l'ultima istruzione del ciclo.

#### Vincoli e workaround correnti

- `-vs` deve corrispondere alla larghezza restituita da `simd_width_of[f32]()`.

- Questa corrispondenza è richiesta dal backend, ma non viene ancora verificata esplicitamente.

- Il ciclo principale è riconosciuto dal nome `vindex`.

- La dichiarazione contenente `vsize` viene ignorata perché generata direttamente dal container.

- Il primo elemento del DAG viene rimosso assumendo che sia l'inizializzazione dell'indice principale.

- Ciascun ciclo ha una singola `StoreVarInst` principale ed è l'ultima istruzione.

- I cicli possono avere una, due o più di due istruzioni:
  - la sola store principale;
  - l'update di un bargraph e la store principale ad esso correlata;
  - l'update di diversi bargraph e la store principale ad essi *non* necessariamente correlata;

- I bargraph sono riconosciuti attraverso la forma del ciclo e il nome dei campi.

- La vettorizzabilità  degli indici è limitata a semplici espressioni affini.

- Gather e scatter non sono implementati e causano il fallback scalare.

- Lo stato SIMD è globale e viene ripristinato manualmente alla fine di ogni ciclo.

- `gSIMDHalf` persiste per l'intero ciclo per mantenere coerente la larghezza degli operandi.

- La generazione non emette il percorso scalare per gli eventuali frame rimanenti dopo l'ultimo blocco
  completo.

L'ultimo vincolo implica che la dimensione del buffer sia compatibile con `vsize`. Il visitor ignora infatti
l'`IfInst` prodotto dalla pipeline FAUST per la gestione dei frame rimanenti ed il ciclo principale processa
solamente blocchi SIMD completi.
