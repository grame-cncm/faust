#-- gui/gui.mojo


from conf.prelude import *


trait FaustGui:

    # Main loop

    @always_inline
    def run(mut ui) -> S32: ...

    # widget's layout
    
    # def open_tab_box(mut ui, var label: String) -> None: ...

    # def open_hori_box(mut ui, var label: String) -> None: ...

    @always_inline
    def open_vert_box(mut ui, label: String) -> None: ...

    @always_inline
    def close_box(mut ui) -> None: ...

    # active widgets

    # def add_button[dtype: DType](
    #     mut ui, var label: String, mut zone: SIMD[dtype, 1]
    # ) -> None: ...

    # def add_check_button[dtype: DType](
    #     mut ui, var label: String, mut zone: SIMD[dtype, 1]
    # ) -> None: ...

    # XXX: var or read?

    # def add_vert_slider[dtype: DType](
    #     mut ui,
    #     var label:    String,
    #     mut zone:     SIMD[dtype, 1],
    #     var init:     SIMD[dtype, 1],
    #     var min:      SIMD[dtype, 1],
    #     var max:      SIMD[dtype, 1],
    #     var step:     SIMD[dtype, 1]
    # ) -> None: ...

    @always_inline
    def add_hori_slider[dtype: DType](
        mut ui,
        var label:    String,
        mut zone:     SIMD[dtype, 1],
        var init:     SIMD[dtype, 1],
        var min:      SIMD[dtype, 1],
        var max:      SIMD[dtype, 1],
        var step:     SIMD[dtype, 1]
    ) -> None: ...

    # def add_num_entry[dtype: DType](
    #     mut ui,
    #     var label:    String,
    #     mut zone:     SIMD[dtype, 1],
    #     var init:     SIMD[dtype, 1],
    #     var min:      SIMD[dtype, 1],
    #     var max:      SIMD[dtype, 1],
    #     var step:     SIMD[dtype, 1]
    # ) -> None: ...

    # passive widgets

    # def add_vert_bargraph[dtype: DType](
    #     mut ui, 
    #     var label:    String,
    #     mut zone:     SIMD[dtype, 1],
    #     var min:      SIMD[dtype, 1],
    #     var max:      SIMD[dtype, 1]
    # ) -> None: ...

    # def add_hori_bargraph[dtype: DType](
    #     mut ui,
    #     var label:    String,
    #     mut zone:     SIMD[dtype, 1],
    #     var min:      SIMD[dtype, 1],
    #     var max:      SIMD[dtype, 1]
    # ) -> None: ...

    # metadata declarations

    # def declare[dtype: DType](
    #     mut ui,
    #     mut zone:     SIMD[dtype, 1],
    #     var key:      String,
    #     var val:      String
    # ) -> None: ...
