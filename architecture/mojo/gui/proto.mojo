# gui/proto.mojo

from conf import *
from .gui import FaustGui

# ==============================================================
# ProtoGui architecture implementation.
# Terminal-based GUI listening for user input for demo purposes.
# ==============================================================

struct ProtoGui(FaustGui):
    var widgets: Arr[Widget, MAX_CAP]
    var widgets_len: S32
    var stack: Arr[S32, MAX_CAP]
    var stack_len: S32
    var top: S32

    @always_inline
    def __init__(out ui):
        ui.widgets = Arr[Widget, MAX_CAP](uninitialized=True)
        ui.widgets_len = 0

        ui.stack = Arr[S32, MAX_CAP](fill=0)
        ui.stack_len = 0
        ui.top = 0

        ui.widgets[0] = Widget(
            WIDGET_ROOT, String("root"), 0,
            NULL_PTR[FaustFloat, MUT_NOTRK],
            0.0, 0.0, 0.0, 0.0,
        )
        ui.widgets_len = 1

        ui.stack[0] = 0
        ui.stack_len = 1
        ui.top = 0

    @always_inline
    def open_vertical_box(mut ui, var label: String) -> None:
        var parent = ui.stack[ui.top]
        var idx = ui.widgets_len 

        ui.widgets[idx] = Widget(
            WIDGET_VBOX, label, parent,
            NULL_PTR[FaustFloat, MUT_NOTRK],
            0.0, 0.0, 0.0, 0.0,
        )
        ui.widgets_len += 1

        ui.stack[ui.stack_len] = idx
        ui.stack_len += 1
        ui.top += 1

    @always_inline
    def close_box(mut ui) -> None:
        if ui.top > 0:
            ui.stack_len -= 1
            ui.top -= 1

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
        var parent = ui.stack[ui.top]
        var idx = ui.widgets_len 
        zone = init
        ui.widgets[idx] = Widget(
            WIDGET_HSLIDER, label, parent,
            Ptr(to=zone).unsafe_origin_cast[MUT_NOTRK](),
            init, min, max, step,
        )
        ui.widgets_len += 1

    @always_inline
    def set_hslider_value(mut ui, index: S32, mut value: FaustFloat) -> None:
        if index < 0 or index >= ui.widgets_len:
            return
        if ui.widgets[index].kind != WIDGET_HSLIDER:
            return
        if value < ui.widgets[index].min:
            value = ui.widgets[index].min
        elif value > ui.widgets[index].max:
            value = ui.widgets[index].max
        ui.widgets[index].zone.unsafe_value()[] = value

    @always_inline
    def find_first_hslider(mut ui) -> S32:
        for var i in range(ui.widgets_len):
            if ui.widgets[i].kind == WIDGET_HSLIDER:
                return i
        return -1
    
    @always_inline
    def run(mut ui) -> S32:
        try:
            var slider = ui.find_first_hslider()
            if slider < 0:
                return 0
            while True:
                var line = input()
                var s = String(line)
                if s == "q":
                    return 0
                var value = FaustFloat(atof(s))
                ui.set_hslider_value(slider, value)
        except Error:
            return 1
     
# ==============================================================
# Widget implementation
# ==============================================================

comptime WIDGET_ROOT = 0
comptime WIDGET_VBOX = 1
comptime WIDGET_HSLIDER = 2
comptime MAX_CAP = 128

@fieldwise_init
struct Widget(ImplicitlyCopyable, Movable):
    var kind: S32
    var label: String
    var parent: S32

    # Slider payload.
    # Meaningful only when kind == WIDGET_HSLIDER.
    var zone: OptPtr[FaustFloat, MUT_NOTRK]
    var init: FaustFloat
    var min: FaustFloat
    var max: FaustFloat
    var step: FaustFloat

