# Public specification of the PortAudio + TerminalGui + GPU architecture.
# Bodies marked `...` do not define an implementation yet.
# Existing Faust contracts remain unchanged, except `FaustAudio.is_alive`.

from max.gpu.host import DeviceBuffer, DeviceContext

from conf import *
from dsp import FaustDsp
from gui import FaustGui
from meta import FaustMeta


# ==============================================================================
# GPU DSP
# ==============================================================================

# A generated `FaustDsp` that also exposes GPU processing.
# @desc
# - Computes the temporary memory required for an audio block.
# - Enqueues processing of a complete audio block on the device.
# @note
# - Generated state must be copyable to the device.

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
# Terminal GUI
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


# An element of the stack-based hierarchy built through `FaustGui`.
# @rep
# - kind: represented container or control kind.
# - parent: index of the widget's containing container.
# - label: label shown in the GUI.
# - zone: associated Faust zone, if present.
# - init: initial control value.
# - min: lowest control or bargraph value.
# - max: highest control or bargraph value.
# - step: increment applied when editing the control.
# - unit: unit of measurement declared in Faust metadata.
# - id: widget identifier in the native terminal module.

@fieldwise_init
struct Widget(Copyable):
    var kind:    S32
    var parent:  S32
    var label:   String
    var zone:    OptPtr[FaustFloat, MUT_NOTRK]
    var init:    FaustFloat
    var min:     FaustFloat
    var max:     FaustFloat
    var step:    FaustFloat
    var unit:    String
    var id:      S32


# A `FaustGui` that presents and controls the DSP in the terminal.
# @desc
# - Builds a stack-based hierarchy of containers and controls.
# - Binds controls and bargraphs directly to Faust zones.
# - Checks that the terminal supports the required operations.
# - Runs the blocking rendering and event loop.
# - Closes the terminal and releases its resources.
# @rep
# - widgets: fixed storage for all GUI widgets.
# - widgets_len: number of valid elements in `widgets`.
# - stack: indices of currently open containers.
# - stack_len: number of valid elements in `stack`.
# - top: position of the current container in the stack.
# - raw: opaque handle for native terminal state.
# - err: first error during GUI construction or operation.
# - frozen: whether UI construction is complete.
# - pending_zone: zone awaiting a `unit` declaration.
# - pending_unit: declared unit for `pending_zone`.
# @note
# - Widget methods cannot return errors, so `err` lives in GUI state.
# - Build the GUI before starting the audio driver.
# - `run` blocks the main thread while PortAudio calls back.
# - Zones follow Faust's regular direct-access model.

struct TerminalGui(FaustGui):
    var widgets:       Arr[Widget, GUI_WIDGET_CAP]
    var widgets_len:   S32
    var stack:         Arr[S32, GUI_STACK_CAP]
    var stack_len:     S32
    var top:           S32
    var raw:           OptPtr[Void, MUT_NOTRK]
    var err:           S32
    var frozen:        Bool
    var pending_zone:  OptPtr[FaustFloat, MUT_NOTRK]
    var pending_unit:  String

    def __init__(out gui):
        ...

    def check(imm gui) -> S32:
        ...

    def stop(mut gui) -> S32:
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
# GPU control map
# ==============================================================================

comptime GPU_ZONE_CAP = GUI_WIDGET_CAP


# A Faust zone transferred between host and GPU DSP state.
# @rep
# - host: Faust zone address in host state.
# - offset: byte offset of the zone within the DSP.
# - passive: whether the DSP produces the zone's value.

@fieldwise_init
struct GpuControlZone(ImplicitlyCopyable, Movable):
    var host:     Ptr[FaustFloat, MUT_NOTRK]
    var offset:   Int
    var passive:  Bool


# A `FaustGui` that describes zones transferred by `GpuDevice`.
# @desc
# - Associates the map with a specific DSP instance.
# - Registers active controls and passive bargraphs without duplicates.
# - Computes each zone's offset from the beginning of the DSP.
# - Checks capacity, pointers, and DSP compatibility.
# @rep
# - base: starting address of host-side DSP state.
# - active: controls copied to the device.
# - active_len: number of valid elements in `active`.
# - passive: bargraphs copied back to host state.
# - passive_len: number of valid elements in `passive`.
# - err: first error during map construction.
# @note
# - Widget methods cannot return errors, so `err` lives in map state.
# - Offsets remain valid while the DSP instance stays at its address.

struct GpuControlMap(FaustGui):
    var base:         OptPtr[U8, MUT_NOTRK]
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


# Builds and checks the DSP's GPU zone map.
def build_gpu_control_map[Dsp: FaustDspGpu](
    var dsp: Ptr[Dsp], mut controls: GpuControlMap
) -> S32:
    controls.reset(dsp)
    dsp[].build_user_interface(controls)
    return controls.check[Dsp]()


# ==============================================================================
# GPU contract
# ==============================================================================

# A host runtime that processes audio blocks on the GPU.
# @desc
# - Prepares persistent state and resources required by the DSP.
# - Processes an audio block using host input and output streams.
# - Reports an error recorded during processing.
# - Releases all resources created during preparation.
# @note
# - `prepare` and `release` are called outside the audio callback.
# - Only the audio callback calls `process`.
# - Query `get_error` after stopping the audio driver.

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
# GPU runtime
# ==============================================================================

# Allocated GPU resources for a concrete DSP instance.
# @rep
# - ctx: context that owns GPU operations.
# - dsp: persistent DSP state on the device.
# - ins: contiguous input-channel buffer.
# - outs: contiguous output-channel buffer.
# - work: temporary memory required by the DSP.
# - in_chans: individual channel views into `ins`.
# - out_chans: individual channel views into `outs`.
# - active_zones: host addresses of control zones.
# - active_bufs: device views into control zones.
# - cached: stable snapshots of controls sent to the device.
# - passive_zones: host addresses of bargraph zones.
# - passive_bufs: device views into bargraph zones.
# - block_size: number of frames per prepared block.
# - n_ins: number of input audio channels.
# - n_outs: number of output audio channels.

@fieldwise_init
struct GpuStorage[Dsp: FaustDspGpu](Movable):
    var ctx:            DeviceContext
    var dsp:            DeviceBuffer[u8]
    var ins:            DeviceBuffer[dfaust]
    var outs:           DeviceBuffer[dfaust]
    var work:           DeviceBuffer[u8]
    var in_chans:       List[DeviceBuffer[dfaust]]
    var out_chans:      List[DeviceBuffer[dfaust]]
    var active_zones:   Arr[Ptr[FaustFloat, MUT_NOTRK], GPU_ZONE_CAP]
    var active_bufs:    List[DeviceBuffer[u8]]
    var cached:         Arr[FaustFloat, GPU_ZONE_CAP]
    var passive_zones:  Arr[Ptr[FaustFloat, MUT_NOTRK], GPU_ZONE_CAP]
    var passive_bufs:   List[DeviceBuffer[u8]]
    var block_size:     S32
    var n_ins:          S32
    var n_outs:         S32


# A `FaustGpu` that prepares and processes a DSP on the device.
# @desc
# - Prepares the DSP, channels, and required UI zones.
# - Copies controls and inputs, runs kernels, and publishes outputs and meters.
# - Records the first error and releases resources after audio stops.
# @rep
# - state: resources allocated during `prepare`, or `None`.
# - err: first callback error; `process` returns `None`.
# @note
# - Failed GPU synchronization leaves device storage allocated.

struct GpuDevice[Dsp: FaustDspGpu](FaustGpu):
    var state:  OptPtr[GpuStorage[Self.Dsp], MUT_NOTRK]
    var err:    S32

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
# DSP adapter
# ==============================================================================

# A `FaustDsp` that adapts GPU processing to the regular audio path.
# @desc
# - Delegates initialization, metadata, and GUI building to the DSP.
# - Delegates each audio block to `gpu.process`.
# @rep
# - dsp: generated DSP providing Faust state and operations.
# - gpu: runtime responsible for device-side processing.
# @note
# - Keep the DSP and runtime alive while the adapter uses them.
# - The runtime records errors because `compute` cannot return them.

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
# Frontend composition
# ==============================================================================

# `main` composes all components and owns the initialized DSP.
# It stops audio before freeing callback state and reports explicit error codes.
# If callback or DMA quiescence cannot be verified, it retains live allocations.
def main() -> None:
    ...


# The `portaudio-terminal-gpu.mojo` frontend owns:
# - a generated DSP;
# - a `TerminalGui`;
# - a `GpuControlMap`;
# - a `GpuDevice`;
# - a `GpuAdapter`;
# - a regular `PortAudio` driver.

# Construction order:
# - the DSP builds `TerminalGui`;
# - the DSP builds `GpuControlMap`;
# - `GpuDevice.prepare` allocates DSP state, zones, and device buffers;
# - `GpuAdapter` associates the DSP with the GPU runtime;
# - `PortAudio.start` receives `GpuAdapter`;
# - `TerminalGui.run` runs the blocking main loop.

# Shutdown order:
# - `TerminalGui.run` ends;
# - `PortAudio.stop` stops the callback;
# - `GpuDevice.get_error` reports any GPU error;
# - `GpuDevice.release` frees GPU resources;
# - `TerminalGui.close` closes the terminal;
# - the frontend destroys the DSP.

# GPU block order:
# - copy active zones into device-side DSP state;
# - copy inputs into device buffers;
# - `gpu_compute` enqueues DSP processing;
# - copy outputs into host streams;
# - copy passive zones back into host zones.
