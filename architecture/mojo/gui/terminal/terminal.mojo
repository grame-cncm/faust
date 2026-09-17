# gui/terminal/terminal.mojo

from conf import *
from gui.gui import FaustGui
from .ffi import *


comptime GUI_WIDGET_CAP = 256
comptime GUI_STACK_CAP = 32
comptime GUI_ROOT = S32(-1)
comptime GUI_TAB_BOX = S32(10)
comptime GUI_HORIZONTAL_BOX = S32(11)
comptime GUI_VERTICAL_BOX = S32(12)


# An element of the stack-based Faust UI hierarchy.
# @rep
# - kind: container or control kind.
# - parent: index of its containing widget.
# - label: label shown in the terminal.
# - zone: host-side control or bargraph zone, if present.
# - init: initial control value.
# - min: lowest displayed or editable value.
# - max: highest displayed or editable value.
# - step: increment used by the control.
# - unit: unit declared in Faust metadata.
# - id: widget identifier in the native module.
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


# A `FaustGui` that presents the DSP in the terminal.
# @desc
# - Registers containers and controls in a stack-based hierarchy.
# - Writes events to host zones and reads bargraphs from those zones.
# - Runs the blocking GUI loop and closes the terminal.
# @rep
# - widgets: registered containers and controls.
# - widgets_len: number of valid widgets in `widgets`.
# - stack: path of open containers.
# - stack_len: number of valid entries in `stack`.
# - top: position of the current container in `stack`.
# - raw: opaque handle from the C11 module.
# - err: first error from widget methods returning `None`.
# - frozen: whether UI construction is complete.
# - pending_zone: zone for a pending `unit` declaration.
# - pending_unit: unit declared for `pending_zone`.
# @note
# - `run` blocks the main thread after PortAudio starts.
# - The frontend calls `close` only after audio stops.
struct TerminalGui(FaustGui):
    var widgets:       Arr[Widget, GUI_WIDGET_CAP]
    var widgets_len:   S32
    var stack:         Arr[S32, GUI_STACK_CAP]
    var stack_len:     S32
    var top:           S32
    var raw:           Handle
    var err:           S32
    var frozen:        Bool
    var pending_zone:  OptPtr[FaustFloat, MUT_NOTRK]
    var pending_unit:  String

    def __init__(out ui):
        ui.widgets = Arr[Widget, GUI_WIDGET_CAP](
            fill=Widget(GUI_ROOT, 0, String(""), None, 0, 0, 0, 0, String(""), S32(-1))
        )
        ui.widgets[0].label = String("root")
        ui.widgets_len = 1
        ui.stack = Arr[S32, GUI_STACK_CAP](fill=0)
        ui.stack_len = 1
        ui.top = 0
        ui.raw = None
        ui.err = 0
        ui.frozen = False
        ui.pending_zone = None
        ui.pending_unit = String("")
        ui.err = gui_create(ui.raw)

    def __deinit__(deinit ui):
        if ui.raw != None:
            gui_destroy(ui.raw)

    def check(imm ui) -> S32:
        if ui.err:
            return ui.err
        if ui.raw == None or ui.top != 0:
            return ERROR_INVALID_STATE
        return ERROR_NONE

    def close(mut ui) -> None:
        if ui.raw != None:
            gui_destroy(ui.raw)
            ui.raw = None
        ui.frozen = True

    @always_inline
    def building(mut ui) -> Bool:
        if ui.frozen and not ui.err:
            ui.err = ERROR_INVALID_STATE
        return not ui.err

    @always_inline
    def open_box(mut ui, kind: S32, native: S32, var label: String) -> None:
        if not ui.building():
            return
        if ui.widgets_len == GUI_WIDGET_CAP or ui.stack_len == GUI_STACK_CAP:
            ui.err = ERROR_CAPACITY
            return
        var id = S32(-1)
        ui.err = gui_open_box(ui.raw, native, label, id)
        if ui.err:
            return
        var idx = ui.widgets_len
        ui.widgets[Int(idx)] = Widget(
            kind, ui.stack[Int(ui.top)], label^, None, 0, 0, 0, 0, String(""), id
        )
        ui.widgets_len += 1
        ui.stack[Int(ui.stack_len)] = idx
        ui.stack_len += 1
        ui.top += 1

    @always_inline
    def open_tab_box(mut ui, var label: String) -> None:
        ui.open_box(GUI_TAB_BOX, BOX_TAB, label^)

    @always_inline
    def open_horizontal_box(mut ui, var label: String) -> None:
        ui.open_box(GUI_HORIZONTAL_BOX, BOX_HORIZONTAL, label^)

    @always_inline
    def open_vertical_box(mut ui, var label: String) -> None:
        ui.open_box(GUI_VERTICAL_BOX, BOX_VERTICAL, label^)

    @always_inline
    def close_box(mut ui) -> None:
        if not ui.building():
            return
        if ui.top <= 0:
            ui.err = ERROR_INVALID_STATE
            return
        ui.err = gui_close_box(ui.raw)
        if not ui.err:
            ui.stack_len -= 1
            ui.top -= 1

    @always_inline
    def add[kind: S32](
        mut ui,
        var label:  String,
        mut zone:   FaustFloat,
        imm init:   F64,
        imm min:    F64,
        imm max:    F64,
        imm step:   F64
    ) -> None:
        if not ui.building():
            return
        if ui.widgets_len == GUI_WIDGET_CAP:
            ui.err = ERROR_CAPACITY
            return
        var id = S32(-1)
        comptime if kind == WIDGET_BUTTON:
            ui.err = gui_add_button(ui.raw, label, id)
        elif kind == WIDGET_CHECK_BUTTON:
            ui.err = gui_add_check_button(ui.raw, label, init, id)
        elif kind == WIDGET_SLIDER:
            ui.err = gui_add_slider(ui.raw, label, init, min, max, step, id)
        elif kind == WIDGET_NUM_ENTRY:
            ui.err = gui_add_num_entry(ui.raw, label, init, min, max, step, id)
        else:
            ui.err = gui_add_bargraph(ui.raw, label, min, max, id)
        if ui.err:
            return
        var ptr = Ptr(to=zone).unsafe_origin_cast[MUT_NOTRK]()
        var repeated = False
        for i in range(1, Int(ui.widgets_len)):
            if ui.widgets[i].zone == ptr:
                if ui.widgets[i].kind != kind:
                    ui.err = ERROR_UNSUPPORTED
                    return
                repeated = True
                break
        if not repeated:
            comptime if kind != WIDGET_BARGRAPH:
                zone = FaustFloat(init)
        var unit = String("")
        if ui.pending_zone == ptr:
            unit = String(ui.pending_unit)
            ui.err = gui_set_unit(ui.raw, id, unit)
            ui.pending_zone = None
        if ui.err:
            return
        ui.widgets[Int(ui.widgets_len)] = Widget(
            kind,
            ui.stack[Int(ui.top)],
            label^,
            ptr,
            FaustFloat(init),
            FaustFloat(min),
            FaustFloat(max),
            FaustFloat(step),
            unit^,
            id
        )
        ui.widgets_len += 1

    @always_inline
    def add_button(mut ui, var label: String, mut zone: FaustFloat) -> None:
        ui.add[WIDGET_BUTTON](label^, zone, 0, 0, 1, 1)

    @always_inline
    def add_check_button(mut ui, var label: String, mut zone: FaustFloat) -> None:
        ui.add[WIDGET_CHECK_BUTTON](label^, zone, 0, 0, 1, 1)

    @always_inline
    def add_horizontal_slider(
        mut ui,
        var label:  String,
        mut zone:   FaustFloat,
        var init:   FaustFloat,
        var min:    FaustFloat,
        var max:    FaustFloat,
        var step:   FaustFloat
    ) -> None:
        ui.add[WIDGET_SLIDER](label^, zone, F64(init), F64(min), F64(max), F64(step))

    @always_inline
    def add_vertical_slider(
        mut ui,
        var label:  String,
        mut zone:   FaustFloat,
        var init:   FaustFloat,
        var min:    FaustFloat,
        var max:    FaustFloat,
        var step:   FaustFloat
    ) -> None:
        ui.add_horizontal_slider(label^, zone, init, min, max, step)

    @always_inline
    def add_num_entry(
        mut ui,
        var label:  String,
        mut zone:   FaustFloat,
        var init:   FaustFloat,
        var min:    FaustFloat,
        var max:    FaustFloat,
        var step:   FaustFloat
    ) -> None:
        ui.add[WIDGET_NUM_ENTRY](label^, zone, F64(init), F64(min), F64(max), F64(step))

    @always_inline
    def add_horizontal_bargraph(
        mut ui,
        var label: String, mut zone: FaustFloat, var min: FaustFloat, var max: FaustFloat
    ) -> None:
        ui.add[WIDGET_BARGRAPH](label^, zone, 0, F64(min), F64(max), 0)

    @always_inline
    def add_vertical_bargraph(
        mut ui,
        var label: String, mut zone: FaustFloat, var min: FaustFloat, var max: FaustFloat
    ) -> None:
        ui.add_horizontal_bargraph(label^, zone, min, max)

    @always_inline
    def declare(
        mut ui, mut zone: FaustFloat, var key: String, var val: String
    ) -> None:
        if not ui.building() or key != "unit":
            return
        var ptr = Ptr(to=zone).unsafe_origin_cast[MUT_NOTRK]()
        ui.pending_zone = ptr
        ui.pending_unit = val^
        for i in range(1, Int(ui.widgets_len)):
            if ui.widgets[i].zone == ptr:
                ui.err = gui_set_unit(ui.raw, ui.widgets[i].id, ui.pending_unit)
                if ui.err:
                    return
                ui.widgets[i].unit = String(ui.pending_unit)
                ui.pending_zone = None

    @always_inline
    def refresh(mut ui) -> None:
        for i in range(1, Int(ui.widgets_len)):
            if ui.widgets[i].zone == None:
                continue
            var zone = ui.widgets[i].zone.unsafe_value()
            ui.err = gui_set_val(ui.raw, ui.widgets[i].id, F64(zone[]))
            if ui.err:
                return

    def start(mut ui) -> S32:
        ui.err = ui.check()
        if ui.err:
            return ui.err
        ui.frozen = True
        ui.refresh()
        if not ui.err:
            ui.err = gui_start(ui.raw)
        return ui.err

    def stop(mut ui) -> S32:
        if ui.raw == None:
            return ERROR_NONE
        return gui_stop(ui.raw)

    def tick(mut ui, wait_ms: S32 = -1) -> Bool:
        if not ui.frozen or ui.raw == None:
            ui.err = ERROR_INVALID_STATE
            return False
        ui.refresh()
        if ui.err:
            return False
        var evt = Event(EVENT_NONE, S32(-1), F64(0))
        ui.err = gui_step(ui.raw, wait_ms, evt)
        if ui.err or evt.kind == EVENT_QUIT:
            return False
        if evt.kind == EVENT_VALUE or evt.kind == EVENT_BUTTON_PRESS or (
            evt.kind == EVENT_BUTTON_RELEASE
        ):
            for i in range(1, Int(ui.widgets_len)):
                if ui.widgets[i].id == evt.id and ui.widgets[i].zone != None:
                    var ptr = ui.widgets[i].zone.unsafe_value()
                    ptr[] = FaustFloat(evt.val)
                    break
        return True

    def run(mut ui) -> S32:
        if not ui.start():
            while ui.tick():
                pass
        var end = ui.stop()
        return ui.err if ui.err else end

