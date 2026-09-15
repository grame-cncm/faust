# Specifica pubblica dell'architettura PortAudio + TerminalGui + GPU.
# I corpi indicati con `...` non definiscono ancora l'implementazione.
# I contratti Faust esistenti restano invariati, salvo `FaustAudio.is_alive`.

from max.gpu.host import DeviceBuffer, DeviceContext

from conf import *
from dsp import FaustDsp
from gui import FaustGui
from meta import FaustMeta


# ==============================================================================
# GPU DSP
# ==============================================================================

# Un `FaustDsp` generato che espone anche l'elaborazione GPU.
# @desc
# - Calcola la memoria temporanea richiesta per un blocco audio.
# - Accoda sul dispositivo il calcolo di un intero blocco audio.
# @note
# - Lo stato generato deve poter essere copiato sul dispositivo.

trait FaustDspGpu(FaustDsp):
    @staticmethod
    def gpu_work_size(imm block_size: S32) -> Int:
        ...

    @staticmethod
    def gpu_compute(
        mut ctx:    DeviceContext,
        imm dsp:    DeviceBuffer[u8],
        imm ins:    DeviceBuffer[dfaust],
        imm outs:   DeviceBuffer[dfaust],
        imm work:   DeviceBuffer[u8],
        imm count:  S32
    ) raises -> None:
        ...


# ==============================================================================
# GUI terminale
# ==============================================================================

comptime GUI_WIDGET_CAP = 256
comptime GUI_STACK_CAP = 32

comptime WIDGET_ROOT = S32(0)
comptime WIDGET_TAB_BOX = S32(1)
comptime WIDGET_HORIZONTAL_BOX = S32(2)
comptime WIDGET_VERTICAL_BOX = S32(3)
comptime WIDGET_BUTTON = S32(4)
comptime WIDGET_CHECK_BUTTON = S32(5)
comptime WIDGET_VERTICAL_SLIDER = S32(6)
comptime WIDGET_HORIZONTAL_SLIDER = S32(7)
comptime WIDGET_NUM_ENTRY = S32(8)
comptime WIDGET_VERTICAL_BARGRAPH = S32(9)
comptime WIDGET_HORIZONTAL_BARGRAPH = S32(10)


# Un elemento della gerarchia stack-based costruita attraverso `FaustGui`.
# @rep
# - kind: tipo del contenitore o del controllo rappresentato.
# - parent: indice del contenitore al quale appartiene il widget.
# - label: etichetta mostrata dalla GUI.
# - zone: zona Faust associata al controllo, se presente.
# - init: valore iniziale del controllo.
# - min: valore minimo del controllo o del bargraph.
# - max: valore massimo del controllo o del bargraph.
# - step: incremento applicato durante la modifica del controllo.
# - unit: unità di misura dichiarata nei metadati Faust.

@fieldwise_init
struct Widget(Movable):
    var kind:    S32
    var parent:  S32
    var label:   String
    var zone:    OptPtr[FaustFloat, MUT_NOTRK]
    var init:    FaustFloat
    var min:     FaustFloat
    var max:     FaustFloat
    var step:    FaustFloat
    var unit:    String


# Una `FaustGui` che presenta e controlla il DSP attraverso il terminale.
# @desc
# - Costruisce una gerarchia stack-based di contenitori e controlli.
# - Collega i controlli e i bargraph direttamente alle zone Faust.
# - Verifica che il terminale supporti le operazioni richieste.
# - Esegue il ciclo bloccante di rendering e gestione degli eventi.
# - Chiude il terminale e rilascia le relative risorse.
# @rep
# - widgets: memoria statica contenente tutti i widget della GUI.
# - widgets_len: numero di elementi validi in `widgets`.
# - stack: indici dei contenitori attualmente aperti.
# - stack_len: numero di elementi validi in `stack`.
# - top: posizione del contenitore corrente nello stack.
# - handle: riferimento opaco allo stato del modulo terminale nativo.
# - err: primo errore prodotto durante costruzione o gestione della GUI.
# - opened: indica che il terminale è stato aperto correttamente.
# @note
# - `err` resta nello stato perché i metodi widget non restituiscono errori.
# - La GUI viene costruita prima dell'avvio del driver audio.
# - `run` blocca il main thread mentre PortAudio esegue il callback.
# - Le zone seguono il normale modello di accesso diretto di Faust.

struct TerminalGui(FaustGui):
    var widgets:      Arr[Widget, GUI_WIDGET_CAP]
    var widgets_len:  S32
    var stack:        Arr[S32, GUI_STACK_CAP]
    var stack_len:    S32
    var top:          S32
    var handle:       OptPtr[Void, MUT_NOTRK]
    var err:          S32
    var opened:       Bool

    def __init__(out gui):
        ...

    def check(imm gui) -> S32:
        ...

    def close(mut gui) -> None:
        ...

    @always_inline
    def open_tab_box(mut gui, var label: String) -> None:
        ...

    @always_inline
    def open_horizontal_box(mut gui, var label: String) -> None:
        ...

    @always_inline
    def open_vertical_box(mut gui, var label: String) -> None:
        ...

    @always_inline
    def close_box(mut gui) -> None:
        ...

    @always_inline
    def add_button(
        mut gui, var label: String, mut zone: FaustFloat
    ) -> None:
        ...

    @always_inline
    def add_check_button(
        mut gui, var label: String, mut zone: FaustFloat
    ) -> None:
        ...

    @always_inline
    def add_vertical_slider(
        mut gui,
        var label:  String,
        mut zone:   FaustFloat,
        var init:   FaustFloat,
        var min:    FaustFloat,
        var max:    FaustFloat,
        var step:   FaustFloat
    ) -> None:
        ...

    @always_inline
    def add_horizontal_slider(
        mut gui,
        var label:  String,
        mut zone:   FaustFloat,
        var init:   FaustFloat,
        var min:    FaustFloat,
        var max:    FaustFloat,
        var step:   FaustFloat
    ) -> None:
        ...

    @always_inline
    def add_num_entry(
        mut gui,
        var label:  String,
        mut zone:   FaustFloat,
        var init:   FaustFloat,
        var min:    FaustFloat,
        var max:    FaustFloat,
        var step:   FaustFloat
    ) -> None:
        ...

    @always_inline
    def add_vertical_bargraph(
        mut gui,
        var label:  String,
        mut zone:   FaustFloat,
        var min:    FaustFloat,
        var max:    FaustFloat
    ) -> None:
        ...

    @always_inline
    def add_horizontal_bargraph(
        mut gui,
        var label:  String,
        mut zone:   FaustFloat,
        var min:    FaustFloat,
        var max:    FaustFloat
    ) -> None:
        ...

    @always_inline
    def declare(
        mut gui, mut zone: FaustFloat, var key: String, var value: String
    ) -> None:
        ...

    def run(mut gui) -> S32:
        ...


# ==============================================================================
# Mappa dei controlli GPU
# ==============================================================================

comptime GPU_ZONE_CAP = GUI_WIDGET_CAP


# Una zona Faust trasferita tra lo stato host e lo stato GPU del DSP.
# @rep
# - host: indirizzo della zona Faust nello stato host.
# - offset: posizione in byte della zona all'interno del DSP.
# - passive: indica che la zona contiene un valore prodotto dal DSP.

@fieldwise_init
struct GpuControlZone(ImplicitlyCopyable, Movable):
    var host:     Ptr[FaustFloat, MUT_NOTRK]
    var offset:   Int
    var passive:  Bool


# Una `FaustGui` che descrive le zone trasferite da `GpuDevice`.
# @desc
# - Associa la mappa a una specifica istanza del DSP.
# - Registra senza duplicati controlli attivi e bargraph passivi.
# - Calcola l'offset di ogni zona rispetto all'inizio del DSP.
# - Verifica capacità, puntatori e compatibilità con il DSP.
# @rep
# - base: indirizzo iniziale dello stato host del DSP.
# - active: descrizioni dei controlli copiati verso il dispositivo.
# - active_len: numero di elementi validi in `active`.
# - passive: descrizioni dei bargraph copiati verso lo stato host.
# - passive_len: numero di elementi validi in `passive`.
# - err: primo errore incontrato durante la costruzione della mappa.
# @note
# - `err` resta nello stato perché i metodi widget non restituiscono errori.
# - Gli offset restano validi finché l'istanza del DSP non viene spostata.

struct GpuControlMap(FaustGui):
    var base:         Ptr[U8, MUT_NOTRK]
    var active:       Arr[GpuControlZone, GPU_ZONE_CAP]
    var active_len:   S32
    var passive:      Arr[GpuControlZone, GPU_ZONE_CAP]
    var passive_len:  S32
    var err:          S32

    def __init__(out controls):
        ...

    def reset[Dsp: FaustDspGpu](
        mut controls, var dsp: Ptr[Dsp]
    ) -> None:
        ...

    def check[Dsp: FaustDspGpu](imm controls) -> S32:
        ...

    @always_inline
    def add_button(
        mut controls, var label: String, mut zone: FaustFloat
    ) -> None:
        ...

    @always_inline
    def add_check_button(
        mut controls, var label: String, mut zone: FaustFloat
    ) -> None:
        ...

    @always_inline
    def add_vertical_slider(
        mut controls,
        var label:  String,
        mut zone:   FaustFloat,
        var init:   FaustFloat,
        var min:    FaustFloat,
        var max:    FaustFloat,
        var step:   FaustFloat
    ) -> None:
        ...

    @always_inline
    def add_horizontal_slider(
        mut controls,
        var label:  String,
        mut zone:   FaustFloat,
        var init:   FaustFloat,
        var min:    FaustFloat,
        var max:    FaustFloat,
        var step:   FaustFloat
    ) -> None:
        ...

    @always_inline
    def add_num_entry(
        mut controls,
        var label:  String,
        mut zone:   FaustFloat,
        var init:   FaustFloat,
        var min:    FaustFloat,
        var max:    FaustFloat,
        var step:   FaustFloat
    ) -> None:
        ...

    @always_inline
    def add_vertical_bargraph(
        mut controls,
        var label:  String,
        mut zone:   FaustFloat,
        var min:    FaustFloat,
        var max:    FaustFloat
    ) -> None:
        ...

    @always_inline
    def add_horizontal_bargraph(
        mut controls,
        var label:  String,
        mut zone:   FaustFloat,
        var min:    FaustFloat,
        var max:    FaustFloat
    ) -> None:
        ...

    @always_inline
    def declare(
        mut controls,
        mut zone:   FaustFloat,
        var key:    String,
        var value:  String
    ) -> None:
        ...

    @always_inline
    def run(mut controls) -> S32:
        return 0


# Costruisce e verifica la mappa delle zone GPU di un DSP.
def build_gpu_control_map[Dsp: FaustDspGpu](
    var dsp: Ptr[Dsp], mut controls: GpuControlMap
) -> S32:
    controls.reset(dsp)
    dsp[].build_user_interface(controls)
    return controls.check[Dsp]()


# ==============================================================================
# Contratto GPU
# ==============================================================================

# Un runtime host che elabora blocchi audio attraverso la GPU.
# @desc
# - Prepara lo stato persistente e le risorse richieste dal DSP.
# - Elabora un blocco audio usando stream host di ingresso e uscita.
# - Espone l'errore memorizzato durante l'elaborazione.
# - Rilascia tutte le risorse create durante la preparazione.
# @note
# - `prepare` e `release` vengono chiamati fuori dal callback audio.
# - `process` viene chiamato esclusivamente dal callback audio.
# - `get_error` viene interrogato dopo aver fermato il driver audio.

trait FaustGpu:
    def prepare[Dsp: FaustDspGpu](
        mut gpu, var dsp: Ptr[Dsp], imm controls: GpuControlMap, imm block_size: S32
    ) -> S32:
        ...

    @always_inline
    def process(
        mut gpu, imm count: S32, var ins: ImmStreams, var outs: MutStreams
    ) -> None:
        ...

    @always_inline
    def get_error(imm gpu) -> S32:
        ...

    def release(mut gpu) -> S32:
        ...


# ==============================================================================
# Runtime GPU
# ==============================================================================

# Un `FaustGpu` che gestisce un DSP e i relativi buffer sul dispositivo.
# @desc
# - Prepara lo stato persistente del DSP e i buffer del dispositivo.
# - Copia controlli e ingressi sul dispositivo prima del calcolo.
# - Accoda il calcolo GPU e ne attende il completamento.
# - Copia uscite e bargraph nelle rispettive zone host.
# - Memorizza il primo errore incontrato durante l'elaborazione.
# - Rilascia le risorse create durante la preparazione.
# @rep
# - ctx: contesto usato per eseguire le operazioni GPU.
# - dsp: stato persistente del DSP memorizzato sul dispositivo.
# - ins: memoria contigua contenente tutti i canali di ingresso.
# - outs: memoria contigua contenente tutti i canali di uscita.
# - work: memoria temporanea richiesta dal calcolo del DSP.
# - in_chans: viste dei singoli canali contenuti in `ins`.
# - out_chans: viste dei singoli canali contenuti in `outs`.
# - active_zones: zone host dei controlli trasferiti al dispositivo.
# - active_len: numero di elementi validi in `active_zones`.
# - active_bufs: viste delle zone attive nello stato GPU del DSP.
# - passive_zones: zone host aggiornate con i valori dei bargraph.
# - passive_len: numero di elementi validi in `passive_zones`.
# - passive_bufs: viste delle zone passive nello stato GPU del DSP.
# - block_size: numero massimo di frame elaborati in un blocco.
# - n_ins: numero di canali audio di ingresso.
# - n_outs: numero di canali audio di uscita.
# - err: primo errore incontrato durante l'elaborazione.
# - prepared: indica che il runtime è pronto per elaborare blocchi.
# @note
# - `err` resta nello stato perché `process` non restituisce errori.
# - `process` non alloca memoria e non modifica le liste dei buffer.
# - La sincronizzazione attende il lavoro GPU del blocco corrente.
# - `release` viene chiamato soltanto dopo aver fermato il callback.

struct GpuDevice[Dsp: FaustDspGpu](FaustGpu):
    var ctx:            DeviceContext
    var dsp:            DeviceBuffer[u8]
    var ins:            DeviceBuffer[dfaust]
    var outs:           DeviceBuffer[dfaust]
    var work:           DeviceBuffer[u8]
    var in_chans:       List[DeviceBuffer[dfaust]]
    var out_chans:      List[DeviceBuffer[dfaust]]
    var active_zones:   Arr[Ptr[FaustFloat, MUT_NOTRK], GPU_ZONE_CAP]
    var active_len:     S32
    var active_bufs:    List[DeviceBuffer[u8]]
    var passive_zones:  Arr[Ptr[FaustFloat, MUT_NOTRK], GPU_ZONE_CAP]
    var passive_len:    S32
    var passive_bufs:   List[DeviceBuffer[u8]]
    var block_size:     S32
    var n_ins:          S32
    var n_outs:         S32
    var err:            S32
    var prepared:       Bool

    def __init__(out gpu):
        ...

    def prepare[SourceDsp: FaustDspGpu](
        mut gpu,
        var dsp:         Ptr[SourceDsp],
        imm controls:    GpuControlMap,
        imm block_size:  S32
    ) -> S32:
        ...

    @always_inline
    def process(
        mut gpu, imm count: S32, var ins: ImmStreams, var outs: MutStreams
    ) -> None:
        ...

    @always_inline
    def get_error(imm gpu) -> S32:
        ...

    def release(mut gpu) -> S32:
        ...


# ==============================================================================
# Adattatore DSP
# ==============================================================================

# Un `FaustDsp` che adatta l'elaborazione GPU al normale percorso audio.
# @desc
# - Delega al DSP inizializzazione, metadati e costruzione della GUI.
# - Delega a `gpu.process` l'elaborazione di ciascun blocco audio.
# @rep
# - dsp: DSP generato dal quale ottenere stato e operazioni Faust.
# - gpu: runtime responsabile dell'elaborazione sul dispositivo.
# @note
# - Il DSP e il runtime devono restare validi durante l'uso dell'adapter.
# - Gli errori restano nel runtime perché `compute` non li restituisce.

@fieldwise_init
struct GpuAdapter[Dsp: FaustDspGpu, Gpu: FaustGpu](FaustDsp):
    var dsp:  Ptr[Self.Dsp]
    var gpu:  Ptr[Self.Gpu]

    @always_inline
    def get_num_inputs(imm adapter) -> S32:
        return adapter.dsp[].get_num_inputs()

    @always_inline
    def get_num_outputs(imm adapter) -> S32:
        return adapter.dsp[].get_num_outputs()

    @always_inline
    def get_sample_rate(imm adapter) -> S32:
        return adapter.dsp[].get_sample_rate()

    @always_inline
    def class_init(mut adapter, imm sample_rate: S32) -> None:
        adapter.dsp[].class_init(sample_rate)

    @always_inline
    def instance_constants(mut adapter, imm sample_rate: S32) -> None:
        adapter.dsp[].instance_constants(sample_rate)

    @always_inline
    def instance_reset_user_interface(mut adapter) -> None:
        adapter.dsp[].instance_reset_user_interface()

    @always_inline
    def instance_clear(mut adapter) -> None:
        adapter.dsp[].instance_clear()

    @always_inline
    def instance_init(mut adapter, imm sample_rate: S32) -> None:
        adapter.dsp[].instance_init(sample_rate)

    @always_inline
    def init(mut adapter, imm sample_rate: S32) -> None:
        adapter.dsp[].init(sample_rate)

    @always_inline
    def get_json(imm adapter) -> String:
        return adapter.dsp[].get_json()

    @always_inline
    def metadata(imm adapter, mut meta: Some[FaustMeta]) -> None:
        adapter.dsp[].metadata(meta)

    @always_inline
    def build_user_interface(
        mut adapter, mut gui: Some[FaustGui]
    ) -> None:
        adapter.dsp[].build_user_interface(gui)

    @always_inline
    def compute(
        mut adapter, var count: S32, var ins: ImmStreams, var outs: MutStreams
    ) -> None:
        adapter.gpu[].process(count, ins, outs)


# ==============================================================================
# Composizione prevista
# ==============================================================================

# Il frontend `portaudio-terminal-gpu.mojo` possiede:
# - un DSP generato;
# - una `TerminalGui`;
# - una `GpuControlMap`;
# - un `GpuDevice`;
# - un `GpuAdapter`;
# - un normale driver `PortAudio`.
#
# Ordine di costruzione:
# - il DSP costruisce la `TerminalGui`;
# - il DSP costruisce la `GpuControlMap`;
# - `GpuDevice.prepare` prepara DSP, zone e buffer sul dispositivo;
# - `GpuAdapter` associa il DSP al runtime GPU;
# - `PortAudio.start` riceve il `GpuAdapter`;
# - `TerminalGui.run` esegue il ciclo bloccante principale.
#
# Ordine di chiusura:
# - `TerminalGui.run` termina;
# - `PortAudio.stop` arresta il callback;
# - `GpuDevice.get_error` restituisce l'eventuale errore;
# - `GpuDevice.release` rilascia le risorse GPU;
# - `TerminalGui.close` chiude il terminale;
# - il frontend distrugge il DSP.
#
# Ordine di elaborazione GPU:
# - le zone attive vengono copiate nello stato GPU del DSP;
# - gli ingressi vengono copiati nei buffer del dispositivo;
# - `gpu_compute` accoda il calcolo del DSP;
# - le uscite vengono copiate negli stream host;
# - le zone passive vengono copiate nelle zone host.
