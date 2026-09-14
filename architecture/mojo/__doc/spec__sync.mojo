# Public API draft for the compositional PortAudio, TerminalGui and GPU path.
#
# This file is a design specification, not an implementation. Method bodies are
# intentionally omitted. The existing FaustDsp and FaustGui contracts are
# preserved unchanged. FaustAudio gains only the is_alive status operation.

from max.gpu.host import DeviceBuffer, DeviceContext

from conf import *
from dsp import FaustDsp
from gui import FaustGui
from audio import FaustAudio
from meta import FaustMeta


# ==============================================================================
# Additional contracts
# ==============================================================================

# A `SyncGui` defines block-boundary exchange between GUI-owned storage and
# host DSP zones.
# @desc
# - Allows a DSP adapter to consume active controls before a compute block.
# - Allows a DSP adapter to publish passive controls after a compute block.
# - Does not define presentation, event handling or GUI lifecycle operations.
# @thread
# - Both operations are called only by the audio thread.
# - Implementations must not allocate, block, render or acquire locks.
trait SyncGui:
    @always_inline
    def pull(imm gui) -> None:
        ...

    @always_inline
    def push(imm gui) -> None:
        ...


# ==============================================================================
# Generated GPU DSP contract
# ==============================================================================

# A `FaustDspGpu` is a complete generated FaustDsp with an additional GPU
# execution capability.
# @desc
# - Preserves the complete FaustDsp contract, including its CPU compute method.
# - Adds the work-buffer sizing operation required by the GPU runtime.
# - Adds the static operation that enqueues one DSP block on a prepared device.
# - Contains no DeviceContext, DeviceBuffer or host-side runtime ownership.
# - Never provides an empty CPU compute implementation.
# @rep
# - The generated DSP state remains a normal FaustDsp host representation.
# - The same representation is copied to persistent device storage by FaustGpu.
# - UI zones use FaustFloat while internal compute precision remains independent.
# @thread
# - Normal FaustDsp operations execute on the host.
# - `gpu_compute` only enqueues device work through the supplied context.
trait FaustDspGpu(FaustDsp):
    @staticmethod
    def gpu_work_size(imm block_size: S32) -> Int:
        ...

    @staticmethod
    def gpu_compute(
        mut context: DeviceContext,
        imm dsp: DeviceBuffer[u8],
        imm inputs: DeviceBuffer[dfaust],
        imm outputs: DeviceBuffer[dfaust],
        imm work: DeviceBuffer[u8],
        imm count: S32
    ) raises -> None:
        ...


# ==============================================================================
# Terminal GUI
# ==============================================================================

# Widget kinds shared by stack-based FaustGui implementations.
comptime GUI_WIDGET_CAP = get_defined_int["GUI_WIDGET_CAP", 256]()
comptime GUI_STACK_CAP = get_defined_int["GUI_STACK_CAP", 64]()
comptime assert GUI_WIDGET_CAP > 0, "Expected a positive GUI widget capacity."
comptime assert GUI_STACK_CAP > 0, "Expected a positive GUI stack capacity."
comptime assert GUI_STACK_CAP <= GUI_WIDGET_CAP, "GUI stack exceeds widget capacity."

comptime WIDGET_ROOT = S32(0)
comptime WIDGET_TAB_BOX = S32(1)
comptime WIDGET_HORIZONTAL_BOX = S32(2)
comptime WIDGET_VERTICAL_BOX = S32(3)
comptime WIDGET_BUTTON = S32(4)
comptime WIDGET_CHECK_BUTTON = S32(5)
comptime WIDGET_SLIDER = S32(6)
comptime WIDGET_NUM_ENTRY = S32(7)
comptime WIDGET_BARGRAPH = S32(8)


# A `Widget` is one element of the stack-built Faust GUI representation.
# @rep
# - Root, boxes, active controls and bargraphs use the same representation.
# - Its index in the owning widget list is its stable identifier.
# - `parent` is -1 for the root and otherwise indexes another Widget.
# - `zone` is absent for the root and boxes.
# - Range fields are meaningful only for controls and bargraphs.
@fieldwise_init
struct Widget(Movable):
    var kind: S32
    var parent: S32
    var label: String
    var zone: OptPtr[FaustFloat, MUT_NOTRK]
    var init: FaustFloat
    var min: FaustFloat
    var max: FaustFloat
    var step: FaustFloat
    var unit: String


# A `TerminalGui` is a terminal-based `FaustGui` with `SyncGui` capability.
# @desc
# - Builds a native terminal presentation from the generated Faust UI tree.
# - Stores widget values in native lock-free atomic slots.
# - Exchanges active and passive values with host DSP zones through SyncGui.
# - Provides the blocking `run` operation required by FaustGui.
# - Provides a split start, tick and stop lifecycle for composed entry points.
# @rep
# - Owns the native terminal handle and its widget storage.
# - Stores root, boxes, controls and bargraphs together in `widgets`.
# - Uses the top of `stack` as the parent of the next widget.
# - Keeps fixed-capacity slots and alias ownership parallel to the widget array.
# - Returns a capacity error instead of growing storage at runtime.
# - Keeps an immutable binding between atomic slots and host DSP zones after check.
# - Does not own the DSP whose zones are bound to the widgets.
# @thread
# - Construction, widget registration, run, start, tick, stop and close belong to
#   the main thread.
# - Pull and push belong exclusively to the audio thread after check succeeds.
# @life
# - `run` is blocking and is equivalent to start, repeated tick and stop.
# - `close` releases native storage and must execute only after audio has stopped.
struct TerminalGui(FaustGui, SyncGui):
    var raw: OptPtr[Void, MUT_NOTRK]
    var widgets: Arr[Widget, GUI_WIDGET_CAP]
    var widgets_len: S32
    var stack: Arr[S32, GUI_STACK_CAP]
    var stack_len: S32
    var slots: Arr[OptPtr[Void, MUT_NOTRK], GUI_WIDGET_CAP]
    var owns: Arr[Bool, GUI_WIDGET_CAP]
    var error: S32
    var frozen: Bool
    var running: Bool

    def __init__(out gui):
        ...

    def check(mut gui) -> S32:
        ...

    def start(mut gui) -> S32:
        ...

    def tick(mut gui, imm wait_ms: S32 = -1) -> Bool:
        ...

    def stop(mut gui) -> S32:
        ...

    def run(mut gui) -> S32:
        ...

    def close(mut gui) -> None:
        ...

    @always_inline
    def pull(imm gui) -> None:
        ...

    @always_inline
    def push(imm gui) -> None:
        ...

    @always_inline
    def open_tab_box(mut gui, var label: String) -> None:
        ...

    @always_inline
    def open_horizontal_box(mut gui, var label: String) -> None:
        ...

    @always_inline
    def open_vertical_box(mut gui, imm label: String) -> None:
        ...

    @always_inline
    def close_box(mut gui) -> None:
        ...

    @always_inline
    def add_button(mut gui, var label: String, mut zone: FaustFloat) -> None:
        ...

    @always_inline
    def add_check_button(
        mut gui, var label: String, mut zone: FaustFloat
    ) -> None:
        ...

    @always_inline
    def add_vertical_slider(
        mut gui,
        var label: String,
        mut zone: FaustFloat,
        var init: FaustFloat,
        var min: FaustFloat,
        var max: FaustFloat,
        var step: FaustFloat
    ) -> None:
        ...

    @always_inline
    def add_horizontal_slider(
        mut gui,
        var label: String,
        mut zone: FaustFloat,
        var init: FaustFloat,
        var min: FaustFloat,
        var max: FaustFloat,
        var step: FaustFloat
    ) -> None:
        ...

    @always_inline
    def add_num_entry(
        mut gui,
        var label: String,
        mut zone: FaustFloat,
        var init: FaustFloat,
        var min: FaustFloat,
        var max: FaustFloat,
        var step: FaustFloat
    ) -> None:
        ...

    @always_inline
    def add_vertical_bargraph(
        mut gui,
        var label: String,
        mut zone: FaustFloat,
        var min: FaustFloat,
        var max: FaustFloat
    ) -> None:
        ...

    @always_inline
    def add_horizontal_bargraph(
        mut gui,
        var label: String,
        mut zone: FaustFloat,
        var min: FaustFloat,
        var max: FaustFloat
    ) -> None:
        ...

    @always_inline
    def declare(
        mut gui, mut zone: FaustFloat, var key: String, var val: String
    ) -> None:
        ...


# ==============================================================================
# GPU control map
# ==============================================================================

# A `GpuControlMap` is a `FaustGui` visitor that discovers the UI zones requiring
# host-device exchange.
# @desc
# - Builds the same stack-based Widget representation as TerminalGui.
# - Records device offsets parallel to the widget list.
# - Removes duplicate aliases while rejecting mixed active and passive aliases.
# - Validates that every zone belongs to the flat device-copyable DSP state.
# @rep
# - Stores root, boxes, controls and bargraphs together in `widgets`.
# - Uses the top of `stack` as the parent of the next widget.
# - Uses -1 as the offset of widgets without a DSP zone.
# - Returns a capacity error instead of growing storage at runtime.
# - Stores the base address used to derive byte offsets during UI construction.
# - Does not own either the host DSP or any device allocation.
# @thread
# - It is built and validated on the main thread before audio starts.
# - Its validated description is immutable while the audio thread is active.
struct GpuControlMap(FaustGui):
    var widgets: Arr[Widget, GUI_WIDGET_CAP]
    var widgets_len: S32
    var stack: Arr[S32, GUI_STACK_CAP]
    var stack_len: S32
    var offsets: Arr[Int, GUI_WIDGET_CAP]
    var dsp_base: Ptr[u8, MUT_NOTRK]
    var dsp_size: Int
    var error: S32
    var frozen: Bool

    def __init__(out controls):
        ...

    def reset[Dsp: FaustDspGpu](mut controls, var dsp: Ptr[Dsp]) -> None:
        ...

    def check[Dsp: FaustDspGpu](imm controls) -> S32:
        ...

    @always_inline
    def open_tab_box(mut controls, var label: String) -> None:
        ...

    @always_inline
    def open_horizontal_box(mut controls, var label: String) -> None:
        ...

    @always_inline
    def open_vertical_box(mut controls, imm label: String) -> None:
        ...

    @always_inline
    def close_box(mut controls) -> None:
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
        var label: String,
        mut zone: FaustFloat,
        var init: FaustFloat,
        var min: FaustFloat,
        var max: FaustFloat,
        var step: FaustFloat
    ) -> None:
        ...

    @always_inline
    def add_horizontal_slider(
        mut controls,
        var label: String,
        mut zone: FaustFloat,
        var init: FaustFloat,
        var min: FaustFloat,
        var max: FaustFloat,
        var step: FaustFloat
    ) -> None:
        ...

    @always_inline
    def add_num_entry(
        mut controls,
        var label: String,
        mut zone: FaustFloat,
        var init: FaustFloat,
        var min: FaustFloat,
        var max: FaustFloat,
        var step: FaustFloat
    ) -> None:
        ...

    @always_inline
    def add_vertical_bargraph(
        mut controls,
        var label: String,
        mut zone: FaustFloat,
        var min: FaustFloat,
        var max: FaustFloat
    ) -> None:
        ...

    @always_inline
    def add_horizontal_bargraph(
        mut controls,
        var label: String,
        mut zone: FaustFloat,
        var min: FaustFloat,
        var max: FaustFloat
    ) -> None:
        ...

    @always_inline
    def declare(
        mut controls, mut zone: FaustFloat, var key: String, var value: String
    ) -> None:
        ...

    @always_inline
    def run(mut controls) -> S32:
        ...


# `build_gpu_control_map` builds and validates a GpuControlMap from the generated
# Faust UI description.
# @desc
# - Resets `controls` against `dsp`.
# - Calls `dsp.build_user_interface(controls)` exactly once.
# - Returns the result of the final bounds and alias validation.
# - Does not modify the user-facing GUI or allocate device resources.
def build_gpu_control_map[Dsp: FaustDspGpu](
    var dsp: Ptr[Dsp], mut controls: GpuControlMap
) -> S32:
    ...


# ==============================================================================
# GPU contract
# ==============================================================================

# A `FaustGpu` defines the host-side runtime capability used by a GpuAdapter.
# @desc
# - Prepares persistent GPU state from an initialized FaustDspGpu.
# - Processes one complete host audio block through the device.
# - Exposes a latched runtime error without changing the FaustDsp compute contract.
# - Releases GPU resources only after audio processing has stopped.
# @thread
# - `prepare` and `release` belong to the main thread.
# - `process` belongs exclusively to the audio thread.
# - `get_error` may be queried by the main thread according to the implementation's
#   publication rules.
trait FaustGpu:
    def prepare[Dsp: FaustDspGpu](
        mut gpu, var dsp: Ptr[Dsp], imm controls: GpuControlMap, imm block_size: S32
    ) -> S32:
        ...

    @always_inline
    def process(
        mut gpu, imm count: S32, var inputs: ImmStreams, var outputs: MutStreams
    ) -> S32:
        ...

    @always_inline
    def get_error(imm gpu) -> S32:
        ...

    def release(mut gpu) -> S32:
        ...


# ==============================================================================
# GPU runtime
# ==============================================================================

comptime GPU_ZONE_CAP = GUI_WIDGET_CAP


# A `GpuDevice` implements FaustGpu for one concrete generated FaustDspGpu.
# @desc
# - Creates and owns the DeviceContext used by the DSP.
# - Keeps the initialized DSP state resident on the device across audio blocks.
# - Preallocates device input, output, work and UI transfer storage.
# - Copies active controls and input channels before launching GPU computation.
# - Copies output channels and passive meters back before returning from process.
# - Performs one final synchronization before host buffers can be reused.
# @rep
# - The `Dsp` parameter fixes the only DSP layout accepted by prepare.
# - Device allocations and sub-buffer views remain stable until release.
# - Host zone arrays use fixed compile-time capacity.
# - DeviceBuffer lists contain only resources successfully created by the context.
# - The first nonzero processing error is latched until release.
# - No allocation or list mutation occurs inside process.
# @life
# - A successful prepare is followed by zero or more process calls and one release.
# - Release is idempotent and never frees storage while device work may be in flight.
struct GpuDevice[Dsp: FaustDspGpu](FaustGpu):
    var context: DeviceContext
    var dsp: DeviceBuffer[u8]
    var inputs: DeviceBuffer[dfaust]
    var outputs: DeviceBuffer[dfaust]
    var work: DeviceBuffer[u8]
    var input_channels: List[DeviceBuffer[dfaust]]
    var output_channels: List[DeviceBuffer[dfaust]]
    var active_zones: Arr[Ptr[FaustFloat, MUT_NOTRK], GPU_ZONE_CAP]
    var active_len: S32
    var active_buffers: List[DeviceBuffer[u8]]
    var passive_zones: Arr[Ptr[FaustFloat, MUT_NOTRK], GPU_ZONE_CAP]
    var passive_len: S32
    var passive_buffers: List[DeviceBuffer[u8]]
    var block_size: S32
    var num_inputs: S32
    var num_outputs: S32
    var error: S32
    var prepared: Bool

    def __init__(out gpu):
        ...

    def prepare[SourceDsp: FaustDspGpu](
        mut gpu,
        var dsp: Ptr[SourceDsp],
        imm controls: GpuControlMap,
        imm block_size: S32
    ) -> S32:
        ...

    @always_inline
    def process(
        mut gpu, imm count: S32, var inputs: ImmStreams, var outputs: MutStreams
    ) -> S32:
        ...

    @always_inline
    def get_error(imm gpu) -> S32:
        ...

    def release(mut gpu) -> S32:
        ...


# ==============================================================================
# DSP adapters
# ==============================================================================

# A `GpuAdapter` presents GPU processing through the unchanged FaustDsp
# contract.
# @desc
# - Selects the GPU capability of a FaustDspGpu instead of its CPU compute.
# - Delegates DSP metadata, initialization and UI construction to `dsp`.
# - Implements compute by delegating one complete block to `gpu.process`.
# - Converts a GPU runtime failure into the failure policy required by FaustDsp,
#   whose compute operation cannot return an error.
# - Is not generated DSP state and does not duplicate FaustDspGpu.
# @rep
# - Borrows one initialized FaustDspGpu and one prepared FaustGpu implementation.
# - Owns neither component.
# - Both referenced components outlive every call performed through the adapter.
# @thread
# - Compute belongs exclusively to the audio thread.
# - All other FaustDsp operations execute before audio starts.
@fieldwise_init
struct GpuAdapter[Dsp: FaustDspGpu, Gpu: FaustGpu](FaustDsp):
    var dsp: Ptr[Self.Dsp]
    var gpu: Ptr[Self.Gpu]

    @always_inline
    def get_num_inputs(imm adapter) -> S32:
        ...

    @always_inline
    def get_num_outputs(imm adapter) -> S32:
        ...

    @always_inline
    def get_sample_rate(imm adapter) -> S32:
        ...

    @always_inline
    def class_init(mut adapter, imm sample_rate: S32) -> None:
        ...

    @always_inline
    def instance_constants(mut adapter, imm sample_rate: S32) -> None:
        ...

    @always_inline
    def instance_reset_user_interface(mut adapter) -> None:
        ...

    @always_inline
    def instance_clear(mut adapter) -> None:
        ...

    @always_inline
    def instance_init(mut adapter, imm sample_rate: S32) -> None:
        ...

    @always_inline
    def init(mut adapter, imm sample_rate: S32) -> None:
        ...

    @always_inline
    def get_json(imm adapter) -> String:
        ...

    @always_inline
    def metadata(imm adapter, mut meta: Some[FaustMeta]) -> None:
        ...

    @always_inline
    def build_user_interface(mut adapter, mut gui: Some[FaustGui]) -> None:
        ...

    @always_inline
    def compute(
        mut adapter, var count: S32, var inputs: ImmStreams, var outputs: MutStreams
    ) -> None:
        ...


# A `ControlDsp` adds block-boundary GUI synchronization to any FaustDsp.
# @desc
# - Delegates the complete FaustDsp contract to `dsp`.
# - Calls `sync.pull` immediately before each delegated compute operation.
# - Calls `sync.push` immediately after each delegated compute operation.
# - Has no dependency on a concrete GUI, audio driver or GPU implementation.
# @rep
# - Borrows one FaustDsp and one SyncGui implementation.
# - Owns neither component.
# - Both referenced components outlive every call performed through the adapter.
# @thread
# - Compute, pull and push belong exclusively to the audio thread.
# - All remaining FaustDsp operations execute before audio starts.
@fieldwise_init
struct ControlDsp[Dsp: FaustDsp, Sync: SyncGui](FaustDsp):
    var dsp: Ptr[Self.Dsp]
    var sync: Ptr[Self.Sync]

    @always_inline
    def get_num_inputs(imm control) -> S32:
        ...

    @always_inline
    def get_num_outputs(imm control) -> S32:
        ...

    @always_inline
    def get_sample_rate(imm control) -> S32:
        ...

    @always_inline
    def class_init(mut control, imm sample_rate: S32) -> None:
        ...

    @always_inline
    def instance_constants(mut control, imm sample_rate: S32) -> None:
        ...

    @always_inline
    def instance_reset_user_interface(mut control) -> None:
        ...

    @always_inline
    def instance_clear(mut control) -> None:
        ...

    @always_inline
    def instance_init(mut control, imm sample_rate: S32) -> None:
        ...

    @always_inline
    def init(mut control, imm sample_rate: S32) -> None:
        ...

    @always_inline
    def get_json(imm control) -> String:
        ...

    @always_inline
    def metadata(imm control, mut meta: Some[FaustMeta]) -> None:
        ...

    @always_inline
    def build_user_interface(mut control, mut gui: Some[FaustGui]) -> None:
        ...

    @always_inline
    def compute(
        mut control, var count: S32, var inputs: ImmStreams, var outputs: MutStreams
    ) -> None:
        ...


# ==============================================================================
# Composed audio and GPU runtime
# ==============================================================================

# A `GpuAudio` composes one asynchronous Faust audio driver and one Faust GPU
# runtime while implementing both public contracts through delegation.
# @desc
# - Delegates init and start to `audio`.
# - Delegates prepare, process, get_error and release to `gpu`.
# - Reports the combined audio and GPU execution state through is_alive.
# - Stops the audio callback before releasing any GPU resource.
# @rep
# - Owns both contained components.
# - Does not own the DSP adapter passed to start.
# - The DSP adapter passed to start may borrow `gpu` through this structure.
# @life
# - Prepare completes before start exposes the composed DSP to the audio callback.
# - Stop first proves audio callback quiescence and then calls release.
# - Failed audio shutdown leaves GPU storage alive rather than freeing in-flight data.
@fieldwise_init
struct GpuAudio[Audio: FaustAudio, Gpu: FaustGpu](FaustAudio, FaustGpu):
    var audio: Self.Audio
    var gpu: Self.Gpu

    @always_inline
    def init(mut runtime) -> S32:
        ...

    @always_inline
    def start[Dsp: FaustDsp](mut runtime, var dsp: Ptr[Dsp]) -> S32:
        ...

    @always_inline
    def is_alive(imm runtime) -> S32:
        ...

    def stop(mut runtime) -> S32:
        ...

    def prepare[Dsp: FaustDspGpu](
        mut runtime,
        var dsp: Ptr[Dsp],
        imm controls: GpuControlMap,
        imm block_size: S32
    ) -> S32:
        ...

    @always_inline
    def process(
        mut runtime, imm count: S32, var inputs: ImmStreams, var outputs: MutStreams
    ) -> S32:
        ...

    @always_inline
    def get_error(imm runtime) -> S32:
        ...

    def release(mut runtime) -> S32:
        ...


# ==============================================================================
# Expected composition in portaudio-terminal-gpu.mojo
# ==============================================================================

# mydsp
#   -> GpuDevice[mydsp]
#   -> GpuAudio[PortAudio, GpuDevice[mydsp]]
#   -> GpuAdapter[mydsp, GpuAudio[...]]
#   -> ControlDsp[GpuAdapter[...], TerminalGui]
#   -> GpuAudio.start(control_dsp)
#
# Ownership remains in the architecture entry point. Destruction order is:
# TerminalGui.stop -> GpuAudio.stop -> TerminalGui.close -> mydsp.free.
