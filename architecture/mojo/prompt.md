Stiamo lavorando nel fork FAUST di Manuel Farzini, branch `mojo-gpu`,
principalmente dentro `architecture/mojo`.

Devi implementare il refactor completo dell'integrazione tra PortAudio,
TerminalGui e GPU descritto da `spec_01.mojo`.

Prima di modificare file:

1. controlla branch, commit corrente e working tree;
2. leggi integralmente `spec_01.mojo`;
3. ispeziona le implementazioni attuali di DSP, GUI, PortAudio e GPU;
4. confronta il codice con la specifica;
5. presenta un piano breve basato sui file realmente presenti.

Non modificare i contratti CPU esistenti per adattarli alla GPU.

Vincoli architetturali
======================

- `FaustDsp`, `FaustGui` e `FaustAudio` sono contratti storici del progetto.
- Mantieni invariati i metodi esistenti di questi contratti.
- L'unica estensione ammessa è `FaustAudio.is_alive()`.
- Aggiorna le implementazioni esistenti di `FaustAudio` per soddisfarla.
- `FaustDspGpu` estende `FaustDsp` con la sola capacità GPU generata.
- `GpuDevice` implementa `FaustGpu`.
- `GpuAdapter` implementa `FaustDsp` mediante composizione.
- Il normale `PortAudio` riceve un `GpuAdapter` come qualsiasi altro DSP.
- Non deve più esistere un driver `PortAudioGpu` separato.
- Il driver PortAudio non deve conoscere GPU, DeviceContext o DeviceBuffer.
- L'entry point compone DSP, GUI, mappa, GPU, adapter e PortAudio.
- Preferisci composizione e delega all'ereditarietà applicativa.

Composizione prevista
=====================

    generated DSP : FaustDspGpu
        + GpuDevice[Dsp] : FaustGpu
        -> GpuAdapter[Dsp, GpuDevice[Dsp]] : FaustDsp
        -> PortAudio.start(adapter)

La GUI viene costruita direttamente sul DSP host:

    dsp.build_user_interface(terminal_gui)

La mappa GPU viene costruita attraverso una seconda visita FaustGui:

    build_gpu_control_map(dsp, control_map)

Questa seconda visita ha esclusivamente lo scopo di descrivere le zone da
trasferire e non deve introdurre un layer generale di sincronizzazione GUI.

Non introdurre
==============

- `SyncGui`;
- `ControlDsp`;
- `GpuAudio`;
- `PortAudioGpu`;
- mutex, lock, ring buffer o wrapper atomici per le zone GUI;
- una variante incompatibile di `FaustDsp`;
- una `compute` CPU fittizia che produce silenzio;
- ownership implicita del DSP dentro GUI, adapter o driver audio.

Modello delle zone
==================

La GUI segue il normale paradigma delle architetture Faust:

- slider e checkbox scrivono direttamente nelle zone `FaustFloat`;
- il callback audio legge direttamente le zone;
- i bargraph vengono letti direttamente dalla GUI;
- un aggiornamento visibile con un blocco di ritardo è accettabile;
- non serve coerenza transazionale tra zone indipendenti.

La sincronizzazione esplicita serve soltanto per il lavoro GPU:

1. copia delle zone attive host verso lo stato DSP sul dispositivo;
2. copia degli ingressi nei buffer GPU;
3. esecuzione di `FaustDspGpu.gpu_compute`;
4. sincronizzazione del lavoro richiesto dal blocco;
5. copia delle uscite verso gli stream host;
6. copia delle zone passive verso le zone host.

Errori
======

- Le API che possono restituire errori devono usare codici espliciti.
- `FaustGpu.process()` restituisce `None`.
- `GpuDevice` memorizza in `err` il primo errore di elaborazione.
- Gli errori successivi non devono sovrascrivere il primo.
- `GpuAdapter.compute()` delega direttamente a `gpu.process()`.
- `get_error()` viene letto soltanto dopo `PortAudio.stop()`.
- Ogni membro `err` deve avere una ragione precisa.
- `TerminalGui.err` conserva errori prodotti da metodi widget che ritornano
  `None`.
- `GpuControlMap.err` conserva errori prodotti durante la visita FaustGui.
- `GpuDevice.err` conserva errori che `FaustDsp.compute` non può restituire.
- Non usare eccezioni nel callback audio.
- Cattura eventuali errori delle API Mojo fuori dal percorso real-time oppure
  convertili in codici di errore senza lasciarli propagare.

Ownership e ordine
==================

L'entry point possiede tutti i componenti.

Ordine di preparazione:

1. alloca e inizializza il DSP;
2. costruisce TerminalGui;
3. costruisce e verifica GpuControlMap;
4. prepara GpuDevice;
5. costruisce GpuAdapter;
6. inizializza e avvia PortAudio;
7. chiama TerminalGui.run() sul main thread.

Ordine di chiusura:

1. TerminalGui.run() termina;
2. PortAudio.stop() arresta il callback;
3. viene letto GpuDevice.get_error();
4. GpuDevice.release() rilascia le risorse GPU;
5. TerminalGui.close() chiude il terminale;
6. il DSP viene deinizializzato, se richiesto, e liberato.

Non liberare o spostare DSP, GPU o adapter mentre il callback può usarli.

GUI
===

- `TerminalGui` mantiene il normale metodo bloccante `FaustGui.run()`.
- Usa il modello stack-based delle architetture Faust e GTK.
- Ogni contenitore e controllo è rappresentato da un `Widget`.
- Usa indici parent e uno stack dei contenitori aperti.
- Usa `FaustFloat` esplicitamente per tutte le zone GUI.
- Non rendere `FaustGui`, `TerminalGui` o `GpuControlMap` generici su `dreal`.
- Implementa anche i metodi FaustGui con implementazione predefinita vuota,
  quando necessari per soddisfare correttamente il contratto.
- Mantieni il modulo terminale C11 e la relativa FFI separati dalla logica GPU.

Capacità e memoria
==================

- Preferisci `Arr` a lunghezza fissa per widget, stack e zone host.
- Definisci capacità compile-time con nomi espliciti.
- Non creare un tipo distinto per ogni piccolo dettaglio.
- Usa `List` dove il numero di DeviceBuffer dipende dalla configurazione e
  l'API GPU rende scomodo o impossibile usare `Arr`.
- Non allocare e non modificare liste dentro il callback audio.
- Tutte le allocazioni GPU avvengono durante `prepare`.
- Lo stato ricorsivo del DSP resta sul dispositivo tra blocchi consecutivi.
- Non copiare l'intero DSP host sul dispositivo a ogni callback.
- Non copiare lo stato DSP dal dispositivo all'host a ogni callback.
- Trasferisci soltanto ingressi, uscite e singole zone UI richieste.

Configurazione compile-time
===========================

Valuta l'uso di `std.sys.defined` e `get_defined_*` per configurazioni che:

- sono note durante la compilazione;
- non cambiano durante l'esecuzione;
- non rappresentano ownership o stato runtime;
- possono essere fornite tramite flag del compilatore.

Non trasformare automaticamente in define:

- errori;
- flag di preparazione;
- handle e context;
- buffer;
- lunghezze runtime effettive;
- puntatori alle zone;
- stato persistente del DSP.

Precisione
==========

- L'I/O dell'architettura usa `dfaust`.
- Le zone GUI usano `FaustFloat`.
- L'architettura GPU corrente assume `dfaust == f32`.
- Mantieni `dfaust` nelle API audio e nei DeviceBuffer.
- Non sostituire indiscriminatamente `dfaust` con `f32`.
- Inserisci gli eventuali `comptime assert` dentro le funzioni che richiedono
  l'evidenza.
- Un `comptime assert` a livello di modulo non compila.
- Le funzioni matematiche come `sin` e `log10` possono richiedere evidenza che
  `dfaust` sia floating-point.

Naming
======

Usa nomi brevi per membri, parametri e variabili locali:

- `context` -> `ctx`;
- `inputs` -> `ins`;
- `outputs` -> `outs`;
- `num_*` -> `n_*`.

Non rinominare API o metodi appartenenti ai contratti Faust:

- `get_num_inputs`;
- `get_num_outputs`;
- `add_num_entry`;
- `build_user_interface`;
- gli altri nomi pubblici stabiliti dal progetto.

Nomi stabiliti:

- `FaustDspGpu`;
- `FaustGpu`;
- `GpuDevice`;
- `GpuAdapter`;
- `GpuControlMap`;
- `GpuControlZone`;
- `TerminalGui`;
- `Widget`;
- `portaudio-terminal-gpu.mojo`.

Stile Mojo
==========

- Nessuna virgola dopo l'ultimo argomento, parametro o campo.
- Usa sempre `var`, `mut`, `imm`, `ref` o `out` in modo esplicito.
- Lunghezza del codice: circa 90 caratteri, massimo tollerato 95.
- Lunghezza dei commenti: circa 75 caratteri, massimo tollerato 80.
- Se una firma entra sulla riga del nome, lasciala sulla stessa riga.
- Se gli argomenti entrano tutti nella riga successiva, raggruppali lì.
- Se non entrano, usa un argomento per riga.
- Nelle firme multilinea allinea i tipi con due spazi dopo il nome più lungo.
- Nelle struct allinea i tipi con due spazi dopo il membro più lungo.
- Aggiungi implementazioni one-line quando sono semplici deleghe.
- Non lasciare righe di commento contenenti soltanto `#`.
- Mantieni nomi, commenti e documentazione coerenti nei casi analoghi.
- Non applicare una nota `ARI` soltanto al punto annotato: generalizzala.

Stile delle specifiche
======================

Le specifiche in `spec_01.mojo` sono in italiano e usano normali commenti.

Formato:

    # Breve definizione della struttura.
    # @desc
    # - Operazione o comportamento pubblico.
    # @rep
    # - member: significato del membro.
    # @note
    # - Vincolo o interazione importante non coperta dalle altre sezioni.

Regole:

- La prima riga definisce sinteticamente il tipo.
- `@desc` descrive ciò che fanno i metodi e il comportamento pubblico.
- Non ripete trait già visibili nella signature.
- Non descrive ciò che il tipo non fa.
- `@rep` elenca tutti i membri della struttura.
- Se la rappresentazione non è ancora definita usa soltanto `- ...`.
- Se una dichiarazione non ha membri, ometti completamente `@rep`.
- `@note` contiene soltanto lifecycle, concorrenza o vincoli importanti.
- Non usare flag inventate come `@thread` o `@life`.
- Non inserire note ovvie o ridondanti.
- Ogni membro `err` deve spiegare perché l'errore viene conservato.
- Non lasciare righe contenenti soltanto `#`.

C11 terminale
=============

Se il refactor tocca il modulo C11:

- conserva C11 portabile;
- mantieni separati `termgui.h`, `termgui.c`, `ffi.mojo` e `terminal.mojo`;
- usa tipi `s8/u8/s16/u16/s32/u32/s64/u64`, `usize` e `ssize`;
- usa `ssize` per differenze e offset quando appropriato;
- usa `cast(T, value)`;
- usa macro funzione minuscole con prefisso `mj_`;
- usa macro costanti maiuscole;
- usa sempre le graffe per branch e cicli;
- nelle funzioni C metti la graffa sulla riga successiva;
- non aggiungere trailing comma;
- mantieni `mj_panic` attivo anche in release;
- disabilita soltanto `mj_assert` in release.

Procedura di implementazione
============================

- Parti dal branch e dai file correnti, non da vecchi artefatti scratch.
- Conserva le modifiche non correlate presenti nella working tree.
- Non eliminare o riscrivere codice CPU funzionante senza necessità.
- Sposta le responsabilità GPU nei componenti previsti dalla specifica.
- Elimina il vecchio percorso GPU soltanto quando il nuovo percorso lo
  sostituisce realmente.
- Aggiorna import ed export dopo aver stabilizzato i componenti.
- Mantieni il frontend piccolo e dedicato alla composizione.
- Verifica prima il normale percorso PortAudio CPU.
- Verifica poi PortAudio + TerminalGui CPU.
- Verifica infine PortAudio + TerminalGui + GPU.
- Usa il probe GPU esistente per la prima integrazione.
- Non modificare il generatore finché l'architettura non è stabile.
- Se Mojo o Metal non sono disponibili, esegui verifiche statiche e indica
  esplicitamente quali prove devono essere effettuate sul Mac di Manuel.

Risultato atteso
================

Al termine devono esistere:

- un solo driver PortAudio;
- un contratto `FaustGpu`;
- un runtime `GpuDevice`;
- un adapter `GpuAdapter` compatibile con il normale PortAudio;
- una `GpuControlMap` costruita attraverso `FaustGui`;
- una `TerminalGui` stack-based basata su `FaustFloat`;
- un frontend `portaudio-terminal-gpu.mojo`;
- nessun layer generale di sincronizzazione GUI;
- nessuna modifica incompatibile ai contratti storici Faust;
- build CPU ancora funzionanti;
- probe GPU verificabile sul Mac di Manuel.

Usa `spec_01.mojo` come fonte canonica. Se il codice corrente e la specifica
divergono, segnala la divergenza prima di prendere una decisione irreversibile.
