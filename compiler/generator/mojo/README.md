## Faust to Mojo generator

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

- `mojo_instructions.hh` − Dichiara `MojoInstVisitor` e le derivate `MojoVecInstVisitor` e `MojoInitFieldsVisitor`.
- `mojo_code_container.hh` − Dichiara `MojoCodeContainer` e le derivate `MojoScalarCodeContainer` e `MojoVecCodeContainer`.

- `mojo_instructions.cpp` − Implementa `MojoInstVisitor` e `MojoInitFieldsVisitor`.
- `mojo_vec_instructions.cpp` − Implementa `MojoVecInstVisitor`.
- `mojo_code_container.cpp` − Implementa `MojoCodeContainer` e le derivata `MojoVecCodeContainer`.

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
del programma generato, indipendentemente dalla strategia usata per il calcolo scalare o vettoriale.

L'interfaccia principale del container è `produceClass`, che coordina l'intera generazione invocando
in ordine le operazioni necessarie. Per convenzione, gli helper che scrivono le singole sezioni del
codice hanno il prefisso `write`. Il container genera:

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
vettoriale viene istanziato quando è attiva l'opzione `-vec`. La struttura generale della `struct`
rimane condivisa; le due implementazioni specializzano la generazione del metodo `compute` attraverso
la rispettiva implementazione di `writeCompute`.

La produzione delle istruzioni utilizza due visitor globali: `gScalarProducer`, condiviso dalle parti
scalari del codice, e `gVectorProducer`, creato dal container vettoriale per la generazione esplicita
SIMD. Anche in modalità vettoriale, dichiarazioni, inizializzazioni, metadati e interfaccia utente
continuano a essere prodotti dal visitor scalare; il visitor vettoriale viene utilizzato solamente
per la generazione del metodo `compute`.

Il container vettoriale deriva inoltre da `VectorCodeContainer`, il quale incapsula la rappresentazione del
calcolo vettoriale e la capacità di individuare i nodi ricorsivi e quelli che possono essere vettorizzati.

### Explicit SIMD emission

### Explicit SIMD emission

Con l'opzione `-vec`, FAUST riorganizza la rappresentazione imperativa del DSP suddividendo il calcolo
in sottocicli e ordinandoli secondo le dipendenze descritte dal relativo DAG. Questa trasformazione
separa le porzioni ricorsive da quelle indipendenti tra le iterazioni e produce cicli regolari che i
backend tradizionali possono affidare all'autovectorization del compilatore. Nel caso di Mojo, tuttavia,
i pass di autovectorization di LLVM sono disabilitati: la struttura vettoriale preparata da FAUST viene
preservata, ma l'emissione scalare non viene successivamente convertita in istruzioni SIMD. Il backend
Mojo costituisce quindi un caso particolare e utilizza la suddivisione in sottocicli prodotta da FAUST
come base per una vectorizzazione esplicita.

Questa strategia è facilitata dal sistema di tipi intrinsecamente vettoriale di Mojo.
`SIMD[dtype, width]` rappresenta il tipo numerico fondamentale e supporta direttamente le comuni
operazioni aritmetiche, logiche e di confronto tra vettori compatibili. `Scalar[dtype]` corrisponde
al caso particolare `SIMD[dtype, 1]`, rendendo scalari e vettori parte dello stesso modello. Il backend
può quindi preservare la struttura delle espressioni generate da FAUST e sostituire i valori scalari
con vettori, caricamenti e scritture SIMD della larghezza appropriata.

FAUST distingue i sottocicli ricorsivi da quelli indipendenti e potenzialmente vettorizzabili. Il
backend utilizza questa informazione per scegliere la strategia di emissione: i cicli vettorizzabili
vengono tradotti direttamente in operazioni SIMD, mentre quelli ricorsivi vengono emessi come cicli
scalari racchiusi in un `comptime for`. Mojo esegue questo ciclo durante la compilazione e ne effettua
l'unrolling completo, generando una sequenza di operazioni scalari senza mantenere un ciclo interno
a runtime. Lo stesso fallback viene applicato ai cicli che, pur non essendo ricorsivi, contengono
accessi alla memoria non compatibili con una vectorizzazione contigua. La generazione è coordinata
da `MojoVecCodeContainer` e implementata a livello di istruzione da `MojoVecInstVisitor`.

#### Vector Code Container

`MojoVecCodeContainer` deriva sia da `MojoCodeContainer` sia da `VectorCodeContainer`. Il primo
fornisce la struttura comune della `struct` DSP, mentre il secondo trasforma il kernel in un grafo
di cicli vettorializzabili.

La modalità di emissione SIMD supporta unicamente precisione di calcolo interna `f64` e precisione
dell'architettura del driver esterno a `f32`.

Nel codice generato si ricavano le larghezze native del target:

```
    vsize = simd_width_of[f32]()
    hsize = simd_width_of[f64]()
```

dove `hsize` significa "half size".

La vector size specificata con l'opzione FAUST `-vs` deve corrispondere a `vsize`. FAUST prepara
infatti la IR per blocchi di `-vs` frame, mentre il codice Mojo usa `vsize` per definire i tipi SIMD
e avanzare nel buffer. Valori differenti produrrebbero quindi una discrepanza tra la struttura del
DAG e il numero di frame elaborati dal ciclo generato.

Questa relazione mantiene il backend indipendente da una specifica estensione SIMD, purché la
compilazione FAUST usi la larghezza `f32` nativa del target. Ad esempio:

```
    ARM NEON 128 bit
        vsize = 4
        hsize = 2
        -vs 4

    x86 AVX2 256 bit
        vsize = 8
        hsize = 4
        -vs 8

    x86 AVX-512 512 bit
        vsize = 16
        hsize = 8
        -vs 16
```

Il backend è stato testato su Apple M1 e M4, entrambi basati su SIMD NEON da 128 bit, usando
`-vs 4`. Le configurazioni x86 rimangono compatibili con il modello di generazione, ma non sono
ancora state verificate sperimentalmente.

Poiché un vettore `f32` contiene il doppio delle lane di un vettore `f64`, vale la relazione:

```
    vsize = 2 * hsize
```

Un blocco richiede quindi una singola operazione SIMD per i dati esterni `f32`, ma due operazioni
per il calcolo interno `f64`.

Il container genera esplicitamente l'indice `vindex`, il limite `end` e l'incremento del ciclo
principale. La dichiarazione equivalente prodotta dalla trasformazione FAUST viene rimossa dal DAG,
mentre `MojoVecInstVisitor` riconosce il ciclo principale attraverso il nome `vindex`. Queste sono
assunzioni dipendenti dalla forma corrente della IR e costituiscono un accoppiamento intenzionale
tra container e visitor.

#### Vector Instructions Visitor

`MojoVecInstVisitor` deriva da `MojoInstVisitor` e ne riutilizza la generazione scalare quando
un'istruzione non appartiene a un'espressione SIMD. Le operazioni `visit` specializzate generano
costruttori vettoriali, cast, operazioni binarie, caricamenti e scritture SIMD, oltre a classificare
i cicli interni secondo la strategia di emissione richiesta.

La visita di un ciclo interno può produrre:

- una normale scrittura SIMD;
- il broadcast di un valore scalare;
- due operazioni SIMD per una destinazione `f64`;
- l'unione di due risultati `f64` prima della scrittura su una destinazione `f32`;
- un ciclo scalare svolto a compile time quando la vectorizzazione non è sicura;
- un trattamento specializzato per gli aggiornamenti dei bargraph.

Il visitor assume che l'ultima istruzione del ciclo sia lo `StoreVarInst` principale. Da questa
ricava la destinazione, il tipo del risultato e la strategia necessaria per generare l'intero ciclo.

#### Stato di generazione

La traduzione di una singola istruzione non contiene sempre informazioni sufficienti per scegliere
il tipo e la larghezza SIMD corretti. `MojoVecInstVisitor` mantiene quindi uno stato globale che
propaga il contesto durante la visita ricorsiva dell'espressione:

- `gSIMDEmit` indica se le istruzioni visitate devono essere emesse in forma SIMD;
- `gSIMDHigh` indica la generazione della seconda porzione di un blocco `f64`;
- `gSIMDWide` seleziona la larghezza `W`, corrispondente alla larghezza SIMD di `f64`;
- `gSIMDJoin` indica una conversione da due risultati `f64` a un singolo vettore `f32`;
- `gCurLhsDT` mantiene il tipo del risultato assegnato dal ciclo corrente;
- `gCurAddrs` mantiene il nome della destinazione corrente;
- `gCurIndex` identifica l'indice del ciclo FAUST eliminato durante la vectorizzazione.

Questo stato permette ai visitor annidati di conoscere il contesto dell'espressione senza modificare
le classi della `FAUST IR` o estendere l'interfaccia di ogni operazione `visit`. La soluzione è
semplice e locale al backend, ma rende la generazione dipendente dall'ordine delle visite e non
rientrante.

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
`mj_simd_high_accept` visita nuovamente un'espressione con `gSIMDHigh` attivo per produrre la
seconda porzione `f64`. Le macro `mj_scalar_accept` e `mj_scalar_visit` disattivano invece
temporaneamente l'emissione SIMD e delegano la traduzione al comportamento scalare ereditato da
`MojoInstVisitor`.

Questo meccanismo evita di replicare manualmente la gestione delle flag in ogni operazione `visit`
e preserva il contesto esterno durante le visite ricorsive. `gSIMDWide` rappresenta un'eccezione:
quando viene attivata da un caricamento, rimane valida fino alla fine del ciclo corrente. Il precedente
ripristino dopo ogni singolo caricamento produceva infatti operandi SIMD con un numero differente di
lane. La flag viene quindi azzerata insieme al restante stato nell'uscita comune del ciclo.

#### Precisione mista e larghezze SIMD

La differenza tra `vsize` e `hsize` richiede una gestione esplicita delle espressioni a precisione
mista. I valori numerici vengono emessi usando costruttori differenti secondo il tipo e il contesto:

```
    s32  -> S32Vec / S32Wec
    f32  -> F32Vec / F32Wec
    f64  -> F64Vec
```

I tipi `Wec` rappresentano valori `s32` o `f32` con lo stesso numero di lane del vettore `f64`.
Sono necessari, ad esempio, quando un intero o un valore esterno `f32` partecipa a un'espressione
interna `f64`. `gSIMDWide` propaga questa scelta a tutti gli operandi successivi dell'espressione,
evitando operazioni tra vettori con larghezze incompatibili.

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

In questo caso `gSIMDJoin` segnala che entrambe le visite devono usare la larghezza `hsize` prima
dell'operazione `join`.

#### Analisi degli accessi alla memoria

La vectorizzazione è consentita solamente quando ogni lane SIMD accede a indirizzi consecutivi.
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
sono classificati come non vectorizzabili. Espressioni quali:

```
    table[f(i)]
    buffer[(i + offset) & mask]
```

richiederebbero rispettivamente operazioni gather o una gestione esplicita dell'indirizzamento delle
singole lane. Poiché queste operazioni non sono ancora implementate, il ciclo viene conservativamente
tradotto mediante il percorso scalare. Un normale `vload` contiguo non sarebbe infatti semanticamente
equivalente a un gather.

#### Fallback scalare e casi speciali

I cicli ricorsivi e quelli con accessi non vectorizzabili vengono emessi come cicli scalari svolti
per le `vsize` lane del blocco corrente:

```
    comptime for i in range(vsize):
        scalar body
```

Questo mantiene l'organizzazione a blocchi del ciclo principale senza modificare la semantica degli
accessi dipendenti dalle iterazioni precedenti. Il fallback riutilizza intenzionalmente
`MojoInstVisitor`; il visitor scalare non dipende dalle flag SIMD e rimane utilizzabile
indipendentemente dal percorso vettoriale.

Gli aggiornamenti dei bargraph richiedono un trattamento separato perché la `FAUST IR` combina
la scrittura del buffer e l'aggiornamento del relativo campo scalare nello stesso ciclo. Il visitor
riconosce queste forme attraverso il numero delle istruzioni e i nomi contenenti `bargraph`. Per il
caso semplice genera il buffer SIMD e assegna al campo del bargraph l'ultimo valore del blocco; in
presenza di più aggiornamenti mantiene invece una breve sequenza scalare.

Questa classificazione dipende da forme specifiche della IR e rappresenta uno degli workaround meno
generali del backend. In particolare, presuppone che le istruzioni del ciclo siano `StoreVarInst`,
che lo store principale sia l'ultimo e che i campi dei bargraph siano riconoscibili dal nome.

#### Vincoli e workaround correnti

L'implementazione privilegia la correttezza e una modifica locale del backend rispetto a una
ristrutturazione della `FAUST IR`. Di conseguenza, alcune informazioni vengono ricavate mediante
convenzioni strutturali o nominali:

- `-vs` deve corrispondere alla larghezza restituita da `simd_width_of[f32]()`;
- questa corrispondenza è richiesta dal backend, ma non viene ancora verificata esplicitamente;
- il ciclo principale è riconosciuto dal nome `vindex`;
- la dichiarazione contenente `vsize` viene ignorata perché generata direttamente dal container;
- il primo elemento del DAG viene rimosso assumendo che sia l'inizializzazione dell'indice principale;
- l'ultima istruzione di un ciclo interno viene assunta come store principale;
- i bargraph sono riconosciuti attraverso la forma del ciclo e il nome dei campi;
- la vectorizzabilità degli indici è limitata a semplici espressioni affini;
- gather e scatter non sono implementati e causano il fallback scalare;
- lo stato SIMD è globale e viene ripristinato manualmente alla fine di ogni ciclo;
- `gSIMDWide` persiste per l'intero ciclo per mantenere coerente la larghezza degli operandi;
- la generazione non emette il percorso scalare per gli eventuali frame rimanenti dopo l'ultimo
  blocco completo.

L'ultimo vincolo implica che la dimensione del buffer deve essere compatibile con `vsize`. Il visitor
ignora infatti l'`IfInst` prodotto dalla pipeline FAUST per la gestione dei frame rimanenti, mentre
il ciclo principale processa solamente blocchi SIMD completi.

Questi workaround rendono esplicite le assunzioni sulle quali si basa l'attuale implementazione.
Permettono di supportare la configurazione SIMD prevista senza introdurre modifiche invasive nelle
strutture condivise del compilatore, ma rappresentano anche i principali punti da generalizzare in
una futura revisione del backend.
