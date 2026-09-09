"""C11 ABI only. Keep scalar constants and Event layout in sync with termgui.h."""

from conf import *
from std.ffi import CStringSlice, external_call

# Opaque, nullable C pointers. C never receives a Mojo object or a DSP zone.
comptime Handle = OptPtr[Void, MUT_NOTRK]
comptime Value = Ptr[Void, MUT_NOTRK]
comptime ERROR_NONE = S32(0)
comptime ERROR_INVALID_ARG = S32(1)
comptime ERROR_INVALID_STATE = S32(2)
comptime ERROR_BAD_ALLOC = S32(3)
comptime ERROR_CAPACITY = S32(4)
comptime ERROR_IO = S32(5)
comptime ERROR_TERM = S32(6)
comptime ERROR_UNSUPPORTED = S32(7)
comptime BOX_TAB = S32(0)
comptime BOX_HORIZONTAL = S32(1)
comptime BOX_VERTICAL = S32(2)
comptime WIDGET_BUTTON = S32(0)
comptime WIDGET_CHECK_BUTTON = S32(1)
comptime WIDGET_SLIDER = S32(2)
comptime WIDGET_NUM_ENTRY = S32(3)
comptime WIDGET_BARGRAPH = S32(4)
comptime EVENT_NONE = S32(0)
comptime EVENT_VALUE = S32(1)
comptime EVENT_BUTTON_PRESS = S32(2)
comptime EVENT_BUTTON_RELEASE = S32(3)
comptime EVENT_QUIT = S32(4)
comptime EVENT_RESIZE = S32(5)

@fieldwise_init
struct Event(ImplicitlyCopyable):
    var kind: S32
    var id: S32
    var val: F64

def error_str(err: S32) -> String:
    return String(external_call["error_str", CStringSlice[IMM_NOTRK]](err))

def gui_create(mut ui: Handle) -> S32:
    comptime assert size_of[Event]() == 16, "C Event ABI must be 16 bytes"
    return external_call["gui_create", S32](Ptr(to=ui))

def gui_destroy(ui: Handle):
    external_call["gui_destroy", Void](ui)

def gui_start(ui: Handle) -> S32:
    return external_call["gui_start", S32](ui)

def gui_step(ui: Handle, wait_ms: S32, mut evt: Event) -> S32:
    return external_call["gui_step", S32](ui, wait_ms, Ptr(to=evt))

def gui_stop(ui: Handle) -> S32:
    return external_call["gui_stop", S32](ui)

def gui_open_box(ui: Handle, kind: S32, var lbl: String, mut id: S32) -> S32:
    return external_call["gui_open_box", S32](ui, kind, lbl.as_c_string_slice().unsafe_ptr(), Ptr(to=id))

def gui_close_box(ui: Handle) -> S32:
    return external_call["gui_close_box", S32](ui)

def gui_add_button(ui: Handle, var lbl: String, mut id: S32) -> S32:
    return external_call["gui_add_button", S32](ui, lbl.as_c_string_slice().unsafe_ptr(), Ptr(to=id))

def gui_add_check_button(ui: Handle, var lbl: String, init: F64, mut id: S32) -> S32:
    return external_call["gui_add_check_button", S32](ui, lbl.as_c_string_slice().unsafe_ptr(), init, Ptr(to=id))

def gui_add_slider(ui: Handle, var lbl: String, init: F64, min: F64, max: F64, step: F64, mut id: S32) -> S32:
    return external_call["gui_add_slider", S32](ui, lbl.as_c_string_slice().unsafe_ptr(), init, min, max, step, Ptr(to=id))

def gui_add_num_entry(ui: Handle, var lbl: String, init: F64, min: F64, max: F64, step: F64, mut id: S32) -> S32:
    return external_call["gui_add_num_entry", S32](ui, lbl.as_c_string_slice().unsafe_ptr(), init, min, max, step, Ptr(to=id))

def gui_add_bargraph(ui: Handle, var lbl: String, min: F64, max: F64, mut id: S32) -> S32:
    return external_call["gui_add_bargraph", S32](ui, lbl.as_c_string_slice().unsafe_ptr(), min, max, Ptr(to=id))

def gui_set_val(ui: Handle, id: S32, val: F64) -> S32:
    return external_call["gui_set_val", S32](ui, id, val)

def gui_set_unit(ui: Handle, id: S32, var unit: String) -> S32:
    return external_call["gui_set_unit", S32](ui, id, unit.as_c_string_slice().unsafe_ptr())

def gui_get_value(ui: Handle, id: S32, mut ptr: Handle) -> S32:
    return external_call["gui_get_value", S32](ui, id, Ptr(to=ptr))

@always_inline
def value_load(ptr: Value) -> F64:
    return external_call["value_load", F64](ptr)

@always_inline
def value_store(ptr: Value, val: F64):
    external_call["value_store", Void](ptr, val)

@always_inline
def value_exchange(ptr: Value, val: F64) -> F64:
    return external_call["value_exchange", F64](ptr, val)
