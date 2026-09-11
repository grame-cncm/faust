# gui/gui.mojo

from conf import *

# ==============================================================
# FaustGui interface declaration.
# General contract for GUI architectures.
# Note that we provide a default nop implementation for each
# method, so the compiler does check for missing definitions.
# The only exception is run(), which is required.
# ==============================================================

trait FaustGui:

    # Main blocking loop to be implemented by GUI architectures.
    # Called between FaustAudio.start() and FaustAudio.stop() to
    # keep the main thread alive while the audio stream is running.
    @always_inline
    def run(mut ui) -> S32: ...

    # widget's layout

    @always_inline
    def open_tab_box(mut ui, var label: String) -> None:
        pass

    @always_inline
    def open_horizontal_box(mut ui, var label: String) -> None:
        pass

    @always_inline
    def open_vertical_box(mut ui, label: String) -> None:
        pass

    @always_inline
    def close_box(mut ui) -> None:
        pass

    # active widgets

    @always_inline
    def add_button(mut ui, var label: String, mut zone: FaustFloat) -> None: pass

    @always_inline
    def add_check_button(
        mut ui, var label: String, mut zone: FaustFloat
    ) -> None: pass

    @always_inline
    def add_vertical_slider(
        mut ui,
        var label:  String,
        mut zone:   FaustFloat,
        var init:   FaustFloat,
        var min:    FaustFloat,
        var max:    FaustFloat,
        var step:   FaustFloat
    ) -> None: pass

    @always_inline
    def add_horizontal_slider(
        mut ui,
        var label:  String,
        mut zone:   FaustFloat,
        var init:   FaustFloat,
        var min:    FaustFloat,
        var max:    FaustFloat,
        var step:   FaustFloat
    ) -> None: pass

    @always_inline
    def add_num_entry(
        mut ui,
        var label:  String,
        mut zone:   FaustFloat,
        var init:   FaustFloat,
        var min:    FaustFloat,
        var max:    FaustFloat,
        var step:   FaustFloat
    ) -> None: pass

    # passive widgets

    @always_inline
    def add_vertical_bargraph(
        mut ui, 
        var label:  String,
        mut zone:   FaustFloat,
        var min:    FaustFloat,
        var max:    FaustFloat
    ) -> None: pass

    @always_inline
    def add_horizontal_bargraph(
        mut ui,
        var label:  String,
        mut zone:   FaustFloat,
        var min:    FaustFloat,
        var max:    FaustFloat
    ) -> None: pass

    # metadata declarations

    @always_inline
    def declare(
        mut ui, mut zone: FaustFloat, var key: String, var val: String
    ) -> None: pass
