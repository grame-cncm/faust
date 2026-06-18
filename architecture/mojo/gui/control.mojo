# gui/control.mojo

from conf import *

# ControlGui architecture implementation.

struct ControlGui(FaustGui):
    var buttons: List[Ptr[FaustFloat, MUTA_NOTRK]]

    def __init__(out ui):
        ui.buttons = List[Ptr[FaustFloat, MUTA_NOTRK]]()

    def add_button[dreal: DType](
        mut ui, var label: String, mut zone: SIMD[dreal, 1]
    ) -> None:
        ui.buttons.append(
            Ptr(to=zone).bitcast[FaustFloat]().unsafe_origin_cast[MUTA_NOTRK]()
        )

    def set_buttons(mut ui, var state: Bool) -> None:
        var value = FaustFloat(1.0) if state else FaustFloat(0.0)
        for button in ui.buttons:
            button[] = value

    def run(mut ui) -> S32: return 0
