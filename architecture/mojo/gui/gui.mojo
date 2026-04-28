# gui/gui.mojo


from conf.prelude import *


# ------------------------------------------------------------ #
# FaustGui interface                                           #
# General interface for the GUI architectures.                 #
# Nota: each method as a default nop implementation, so the    #
#       compiler does not check for missing definitions.       #
# ------------------------------------------------------------ #

trait FaustGui:

    # main loop

    @always_inline
    def run(mut ui) -> S32: ...

    # widget's layout

    @always_inline
    def open_tab_box(mut ui, var label: String) -> None: pass

    @always_inline
    def open_horizontal_box(mut ui, var label: String) -> None: pass

    @always_inline
    def open_vertical_box(mut ui, label: String) -> None: pass

    @always_inline
    def close_box(mut ui) -> None: pass

    # active widgets

    @always_inline
    def add_button[dreal: DType](
        mut ui, var label: String, mut zone: SIMD[dreal, 1]
    ) -> None: pass

    @always_inline
    def add_check_button[dreal: DType](
        mut ui, var label: String, mut zone: SIMD[dreal, 1]
    ) -> None: pass

    @always_inline
    def add_vertical_slider[dreal: DType](
        mut ui,
        var label:    String,
        mut zone:     SIMD[dreal, 1],
        var init:     SIMD[dreal, 1],
        var min:      SIMD[dreal, 1],
        var max:      SIMD[dreal, 1],
        var step:     SIMD[dreal, 1]
    ) -> None: pass

    @always_inline
    def add_horizontal_slider[dreal: DType](
        mut ui,
        var label:    String,
        mut zone:     SIMD[dreal, 1],
        var init:     SIMD[dreal, 1],
        var min:      SIMD[dreal, 1],
        var max:      SIMD[dreal, 1],
        var step:     SIMD[dreal, 1]
    ) -> None: pass

    @always_inline
    def add_num_entry[dreal: DType](
        mut ui,
        var label:    String,
        mut zone:     SIMD[dreal, 1],
        var init:     SIMD[dreal, 1],
        var min:      SIMD[dreal, 1],
        var max:      SIMD[dreal, 1],
        var step:     SIMD[dreal, 1]
    ) -> None: pass

    # passive widgets

    @always_inline
    def add_vertical_bargraph[dreal: DType](
        mut ui, 
        var label:    String,
        mut zone:     SIMD[dreal, 1],
        var min:      SIMD[dreal, 1],
        var max:      SIMD[dreal, 1]
    ) -> None: pass

    @always_inline
    def add_horizontal_bargraph[dreal: DType](
        mut ui,
        var label:    String,
        mut zone:     SIMD[dreal, 1],
        var min:      SIMD[dreal, 1],
        var max:      SIMD[dreal, 1]
    ) -> None: pass

    # metadata declarations

    @always_inline
    def declare[dreal: DType](
        mut ui,
        mut zone:     SIMD[dreal, 1],
        var key:      String,
        var val:      String
    ) -> None: pass


