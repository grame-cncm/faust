"""Faust UI adapter. Main-thread presentation, callback-owned DSP zones."""

from conf import *
from dsp import FaustDsp
from gui import FaustGui
from meta import FaustMeta
from .ffi import *


@fieldwise_init
struct Binding[dtype: DType](ImplicitlyCopyable):
    var id: S32
    var kind: S32
    var zone: Ptr[Scalar[Self.dtype]]
    var slot: Value
    var own: Bool  # Aliased widgets share one slot and one DSP transfer.


@fieldwise_init
struct Unit[dtype: DType](Movable):
    var zone: Ptr[Scalar[Self.dtype]]
    var text: String


struct TerminalGui[dtype: DType = dfaust](FaustGui):
    comptime Real = Scalar[Self.dtype]
    var raw: Handle
    var err: S32
    var frozen: Bool
    var binds: List[Binding[Self.dtype]]
    var units: List[Unit[Self.dtype]]

    def __init__(out ui):
        ui.raw = None
        ui.binds = List[Binding[Self.dtype]]()
        ui.units = List[Unit[Self.dtype]]()
        ui.frozen = False
        ui.err = gui_create(ui.raw)

    def __deinit__(deinit ui):
        # The caller MUST stop audio first. close() after driver.stop() also
        # extends Mojo's ASAP lifetime past all untracked callback references.
        gui_destroy(ui.raw)

    def close(mut ui):
        gui_destroy(ui.raw)
        ui.raw = None
        ui.frozen = True

    def check(mut ui) -> S32:
        # Seal the immutable binding list before it is published to audio.
        ui.frozen = True
        if ui.raw == None and not ui.err:
            ui.err = ERROR_INVALID_STATE
        return ui.err

    def start(mut ui) -> S32:
        if ui.check():
            return ui.err
        ui.refresh()
        if not ui.err:
            ui.err = gui_start(ui.raw)
        return ui.err

    def stop(mut ui) -> S32:
        # Stop presentation only; close() releases storage after audio stops.
        if ui.raw == None:
            return ERROR_NONE
        return gui_stop(ui.raw)

    def building(mut ui) -> Bool:
        if ui.frozen and not ui.err:
            ui.err = ERROR_INVALID_STATE
        return not ui.err

    def open_box(mut ui, kind: S32, var label: String):
        if ui.building():
            var id = S32(-1)
            ui.err = gui_open_box(ui.raw, kind, label^, id)

    def open_tab_box(mut ui, var label: String) -> None:
        ui.open_box(BOX_TAB, label^)

    def open_horizontal_box(mut ui, var label: String) -> None:
        ui.open_box(BOX_HORIZONTAL, label^)

    def open_vertical_box(mut ui, label: String) -> None:
        ui.open_box(BOX_VERTICAL, String(label))

    def close_box(mut ui) -> None:
        if ui.building():
            ui.err = gui_close_box(ui.raw)

    def add[dreal: DType, kind: S32](
        mut ui, var label: String, mut zone: SIMD[dreal, 1],
        init: F64, min: F64, max: F64, step: F64,
    ):
        comptime assert dreal == Self.dtype, "UI zone precision mismatch"
        if not ui.building():
            return
        var id = S32(-1)
        comptime if kind == WIDGET_BUTTON:
            ui.err = gui_add_button(ui.raw, label^, id)
        elif kind == WIDGET_CHECK_BUTTON:
            ui.err = gui_add_check_button(ui.raw, label^, init, id)
        elif kind == WIDGET_SLIDER:
            ui.err = gui_add_slider(ui.raw, label^, init, min, max, step, id)
        elif kind == WIDGET_NUM_ENTRY:
            ui.err = gui_add_num_entry(ui.raw, label^, init, min, max, step, id)
        else:
            ui.err = gui_add_bargraph(ui.raw, label^, min, max, id)
        if ui.err:
            return
        var slot: Handle = None
        ui.err = gui_get_value(ui.raw, id, slot)
        if ui.err:
            return
        var ptr = Ptr(to=zone).unsafe_bitcast[Self.Real]().unsafe_origin_cast[MUT_NOTRK]()
        var own = True
        for i in range(len(ui.binds)):
            if ui.binds[i].zone == ptr:
                if ui.binds[i].kind != kind:
                    ui.err = ERROR_UNSUPPORTED
                    return
                slot = ui.binds[i].slot
                own = False
                break
        if own:
            comptime if kind != WIDGET_BARGRAPH:
                zone = SIMD[dreal, 1](init)
            value_store(slot.unsafe_value(), F64(zone))
        ui.binds.append(Binding[Self.dtype](id, kind, ptr, slot.unsafe_value(), own))
        for i in range(len(ui.units)):
            if ui.units[i].zone == ptr:
                ui.err = gui_set_unit(ui.raw, id, String(ui.units[i].text))
                break

    def add_button[dreal: DType](mut ui, var label: String, mut zone: SIMD[dreal, 1]) -> None:
        ui.add[dreal, WIDGET_BUTTON](label^, zone, 0, 0, 1, 1)

    def add_check_button[dreal: DType](mut ui, var label: String, mut zone: SIMD[dreal, 1]) -> None:
        ui.add[dreal, WIDGET_CHECK_BUTTON](label^, zone, 0, 0, 1, 1)

    def add_horizontal_slider[dreal: DType](
        mut ui, var label: String, mut zone: SIMD[dreal, 1],
        var init: SIMD[dreal, 1], var min: SIMD[dreal, 1],
        var max: SIMD[dreal, 1], var step: SIMD[dreal, 1],
    ) -> None:
        ui.add[dreal, WIDGET_SLIDER](label^, zone, F64(init), F64(min), F64(max), F64(step))

    def add_vertical_slider[dreal: DType](
        mut ui, var label: String, mut zone: SIMD[dreal, 1],
        var init: SIMD[dreal, 1], var min: SIMD[dreal, 1],
        var max: SIMD[dreal, 1], var step: SIMD[dreal, 1],
    ) -> None:
        ui.add_horizontal_slider(label^, zone, init, min, max, step)

    def add_num_entry[dreal: DType](
        mut ui, var label: String, mut zone: SIMD[dreal, 1],
        var init: SIMD[dreal, 1], var min: SIMD[dreal, 1],
        var max: SIMD[dreal, 1], var step: SIMD[dreal, 1],
    ) -> None:
        ui.add[dreal, WIDGET_NUM_ENTRY](label^, zone, F64(init), F64(min), F64(max), F64(step))

    def add_horizontal_bargraph[dreal: DType](
        mut ui, var label: String, mut zone: SIMD[dreal, 1],
        var min: SIMD[dreal, 1], var max: SIMD[dreal, 1],
    ) -> None:
        ui.add[dreal, WIDGET_BARGRAPH](label^, zone, 0, F64(min), F64(max), 0)

    def add_vertical_bargraph[dreal: DType](
        mut ui, var label: String, mut zone: SIMD[dreal, 1],
        var min: SIMD[dreal, 1], var max: SIMD[dreal, 1],
    ) -> None:
        ui.add_horizontal_bargraph(label^, zone, min, max)

    def declare[dreal: DType](
        mut ui, mut zone: SIMD[dreal, 1], var key: String, var val: String,
    ) -> None:
        comptime assert dreal == Self.dtype, "UI zone precision mismatch"
        if not ui.building() or key != "unit":
            return
        var ptr = Ptr(to=zone).unsafe_bitcast[Self.Real]().unsafe_origin_cast[MUT_NOTRK]()
        # Key by address, never 'last declaration': box metadata uses null_val.
        for i in range(len(ui.binds)):
            if ui.binds[i].zone == ptr:
                ui.err = gui_set_unit(ui.raw, ui.binds[i].id, String(val))
                if ui.err:
                    return
        for i in range(len(ui.units)):
            if ui.units[i].zone == ptr:
                ui.units[i].text = val^
                return
        ui.units.append(Unit[Self.dtype](ptr, val^))

    @always_inline
    def pull(imm ui):
        # AUDIO ONLY. Immutable bindings, scalar atomics, no rendering/allocation.
        for i in range(len(ui.binds)):
            var wdg = ui.binds[i]
            if not wdg.own or wdg.kind == WIDGET_BARGRAPH:
                continue
            var val = F64(0)
            if wdg.kind == WIDGET_BUTTON:
                val = value_exchange(wdg.slot, 0)
            else:
                val = value_load(wdg.slot)
            wdg.zone[] = Self.Real(val)

    @always_inline
    def push(imm ui):
        # AUDIO ONLY. No reads of presentation snapshots or event state.
        for i in range(len(ui.binds)):
            var wdg = ui.binds[i]
            if wdg.own and wdg.kind == WIDGET_BARGRAPH:
                value_store(wdg.slot, F64(wdg.zone[]))

    def refresh(mut ui):
        # MAIN ONLY. Runtime zone access belongs exclusively to pull()/push().
        if ui.err:
            return
        for i in range(len(ui.binds)):
            var wdg = ui.binds[i]
            if wdg.kind != WIDGET_BUTTON:
                ui.err = gui_set_val(ui.raw, wdg.id, value_load(wdg.slot))
                if ui.err:
                    return

    def tick(mut ui, wait_ms: S32 = -1) -> Bool:
        if not ui.frozen or ui.raw == None:
            ui.err = ERROR_INVALID_STATE
        ui.refresh()
        if ui.err:
            return False
        var evt = Event(EVENT_NONE, -1, 0)
        ui.err = gui_step(ui.raw, wait_ms, evt)
        if ui.err or evt.kind == EVENT_QUIT:
            return False
        if evt.kind == EVENT_VALUE or evt.kind == EVENT_BUTTON_PRESS:
            for i in range(len(ui.binds)):
                if ui.binds[i].id == evt.id:
                    value_store(ui.binds[i].slot, evt.val)
                    break
        # RELEASE only resets the visible button. Audio consumes the latched
        # press once, keeping it high for one complete DSP block even if slow.
        return True

    def run(mut ui) -> S32:
        if not ui.start():
            while ui.tick():
                pass
        var err = ui.stop()
        return ui.err if ui.err else err


@fieldwise_init
struct ControlDsp[Dsp: FaustDsp, dtype: DType = dfaust](FaustDsp):
    """CPU proxy: the existing PortAudio driver calls the normal DSP contract."""
    var dsp: Ptr[Self.Dsp]
    var ui: Ptr[TerminalGui[Self.dtype]]

    def get_num_inputs(imm ctl) -> S32:
        return ctl.dsp[].get_num_inputs()

    def get_num_outputs(imm ctl) -> S32:
        return ctl.dsp[].get_num_outputs()

    def get_sample_rate(imm ctl) -> S32:
        return ctl.dsp[].get_sample_rate()

    def class_init(mut ctl, imm sample_rate: S32) -> None:
        ctl.dsp[].class_init(sample_rate)

    def instance_constants(mut ctl, imm sample_rate: S32) -> None:
        ctl.dsp[].instance_constants(sample_rate)

    def instance_reset_user_interface(mut ctl) -> None:
        ctl.dsp[].instance_reset_user_interface()

    def instance_clear(mut ctl) -> None:
        ctl.dsp[].instance_clear()

    def instance_init(mut ctl, imm sample_rate: S32) -> None:
        ctl.dsp[].instance_init(sample_rate)

    def init(mut ctl, imm sample_rate: S32) -> None:
        ctl.dsp[].init(sample_rate)

    def get_json(imm ctl) -> String:
        return ctl.dsp[].get_json()

    def metadata(imm ctl, mut meta: Some[FaustMeta]) -> None:
        ctl.dsp[].metadata(meta)

    def build_user_interface(mut ctl, mut ui: Some[FaustGui]) -> None:
        ctl.dsp[].build_user_interface(ui)

    @always_inline
    def compute(mut ctl, var count: S32, var inputs: ImmStreams, var outputs: MutStreams) -> None:
        ctl.ui[].pull()
        ctl.dsp[].compute(count, inputs, outputs)
        ctl.ui[].push()
