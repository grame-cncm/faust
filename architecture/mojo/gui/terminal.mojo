#-- gui/control.mojo


from conf.prelude import *


# --------------------------------------------------------------
# TerminalGui interface implementation
# --------------------------------------------------------------


# struct TerminalGui(FaustGui):
struct TerminalGui[numeric: DType](FaustGui):
    comptime Numeric = SIMD[Self.numeric, 1]
    var widgets: Arr[Widget[Self.numeric], MAX_CAP]
    var widgets_len: S32
    var stack: Arr[S32, MAX_CAP]
    var stack_len: S32
    var top: S32

    @always_inline
    def __init__(out ui):
        ui.widgets = Arr[Widget[Self.numeric], MAX_CAP](uninitialized=True)
        ui.widgets_len = 0

        ui.stack = Arr[S32, MAX_CAP](fill=0)
        ui.stack_len = 0
        ui.top = 0

        ui.widgets[0] = Widget[Self.numeric](
            WIDGET_ROOT,
            String("root"),
            0,
            {},
            0.0,
            0.0,
            0.0,
            0.0,
        )
        ui.widgets_len = 1

        ui.stack[0] = 0
        ui.stack_len = 1
        ui.top = 0

    @always_inline
    def open_vert_box(mut ui, label: String) -> None:
        var parent = ui.stack[ui.top]
        var idx = ui.widgets_len 

        ui.widgets[idx] = Widget[Self.numeric](
            WIDGET_VBOX,
            label,
            parent,
            {},
            SIMD[Self.numeric, 1](0.0),
            SIMD[Self.numeric, 1](0.0),
            SIMD[Self.numeric, 1](0.0),
            SIMD[Self.numeric, 1](0.0),
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
    def add_hori_slider[dtype: DType](
        mut ui,
        var label: String,
        mut zone: SIMD[dtype, 1],
        var init: SIMD[dtype, 1],
        var min: SIMD [dtype, 1],
        var max: SIMD [dtype, 1],
        var step: SIMD[dtype, 1]
    ) -> None:
        comptime assert dtype == Self.numeric
        var parent = ui.stack[ui.top]
        var idx = ui.widgets_len 

        zone = init

        ui.widgets[idx] = Widget[Self.numeric](
            WIDGET_HSLIDER,
            label,
            parent,
            Ptr(to=zone).bitcast[Self.Numeric]().unsafe_origin_cast[MUTA_EXT](),
            Self.Numeric(init),
            Self.Numeric(min),
            Self.Numeric(max),
            Self.Numeric(step),
        )
        ui.widgets_len += 1

    @always_inline
    def set_hslider_value(mut ui, index: S32, mut value: SIMD[Self.numeric, 1]) -> None:
        if index < 0 or index >= ui.widgets_len:
            return

        if ui.widgets[index].kind != WIDGET_HSLIDER:
            return

        if value < ui.widgets[index].min:
            value = ui.widgets[index].min
        elif value > ui.widgets[index].max:
            value = ui.widgets[index].max

        ui.widgets[index].zone[] = value

    @always_inline
    def find_first_hslider(mut ui) -> S32:
        for var i in range(ui.widgets_len):
            if ui.widgets[i].kind == WIDGET_HSLIDER:
                return i
        return -1

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

                var value = SIMD[Self.numeric, 1](atof(s))
                ui.set_hslider_value(slider, value)

        except Error:
            return 1


# --------------------------------------------------------------
# Widget implementation
# --------------------------------------------------------------


comptime WIDGET_ROOT = 0
comptime WIDGET_VBOX = 1
comptime WIDGET_HSLIDER = 2
comptime MAX_CAP = 128


@fieldwise_init
struct Widget[dtype: DType](ImplicitlyCopyable, Movable):
    var kind: S32
    var label: String
    var parent: S32

    # Slider payload.
    # Meaningful only when kind == WIDGET_HSLIDER.
    var zone: Ptr[SIMD[Self.dtype, 1], MUTA_EXT]
    var init: SIMD[Self.dtype, 1]
    var min: SIMD[Self.dtype, 1]
    var max: SIMD[Self.dtype, 1]
    var step: SIMD[Self.dtype, 1]
