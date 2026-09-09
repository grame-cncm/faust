# gui/bridge.mojo

from std.memory.unsafe_pointer import pointer_to_int

from conf import *
from .gui import FaustGui


@fieldwise_init
struct BridgeZone(ImplicitlyCopyable, Movable):
    var host: Ptr[FaustFloat, MUT_NOTRK]
    var offset: Int
    var cached: FaustFloat


struct BridgeGui(FaustGui):
    var dsp: OptPtr[U8, MUT_NOTRK]
    var zones: List[BridgeZone]

    def __init__(out ui):
        ui.dsp = None
        ui.zones = List[BridgeZone]()

    @always_inline
    def reset(mut ui, dsp: Ptr[U8, MUT_NOTRK]) -> None:
        ui.dsp = dsp
        ui.zones = List[BridgeZone]()

    @always_inline
    def _add_zone[dreal: DType](mut ui, mut zone: SIMD[dreal, 1]) -> None:
        comptime assert dreal == dfaust
        var host = Ptr(to=zone).unsafe_bitcast[FaustFloat]().unsafe_origin_cast[MUT_NOTRK]()
        var offset = pointer_to_int(host) - pointer_to_int(ui.dsp.unsafe_value())
        ui.zones.append(BridgeZone(host, offset, host[]))

    @always_inline
    def add_button[dreal: DType](
        mut ui, var label: String, mut zone: SIMD[dreal, 1]
    ) -> None:
        ui._add_zone(zone)

    @always_inline
    def add_check_button[dreal: DType](
        mut ui, var label: String, mut zone: SIMD[dreal, 1]
    ) -> None:
        ui._add_zone(zone)

    @always_inline
    def add_vertical_slider[dreal: DType](
        mut ui, var label: String, mut zone: SIMD[dreal, 1],
        var init: SIMD[dreal, 1], var min: SIMD[dreal, 1],
        var max: SIMD[dreal, 1], var step: SIMD[dreal, 1]
    ) -> None:
        ui._add_zone(zone)

    @always_inline
    def add_horizontal_slider[dreal: DType](
        mut ui, var label: String, mut zone: SIMD[dreal, 1],
        var init: SIMD[dreal, 1], var min: SIMD[dreal, 1],
        var max: SIMD[dreal, 1], var step: SIMD[dreal, 1]
    ) -> None:
        ui._add_zone(zone)

    @always_inline
    def add_num_entry[dreal: DType](
        mut ui, var label: String, mut zone: SIMD[dreal, 1],
        var init: SIMD[dreal, 1], var min: SIMD[dreal, 1],
        var max: SIMD[dreal, 1], var step: SIMD[dreal, 1]
    ) -> None:
        ui._add_zone(zone)

    @always_inline
    def run(mut ui) -> S32:
        return 0
