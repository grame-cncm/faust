# gui/map.mojo

from conf import *
from dsp import FaustDspGpu
from .gui import FaustGui

comptime GPU_ZONE_CAP = 256
comptime GPU_MAP_INVALID = S32(-2996)


# A Faust zone copied between host and device.
# @rep
# - host: zone address within the host-side DSP state.
# - offset: byte offset from the beginning of the DSP.
# - passive: whether GPU processing updates the zone.
@fieldwise_init
struct GpuControlZone(ImplicitlyCopyable, Movable):
    var host:     Ptr[FaustFloat, MUT_NOTRK]
    var offset:   Int
    var passive:  Bool


# A `FaustGui` that describes GPU DSP controls and meters.
# @desc
# - Collects active and passive zones without duplicates.
# - Checks that the zones belong to the DSP instance.
# @rep
# - base: starting address of the host-side DSP.
# - active: control zones sent to the device.
# - active_len: number of valid zones in `active`.
# - passive: meter zones returned from the device.
# - passive_len: number of valid zones in `passive`.
# - err: first error while visiting the UI.
# @note
# - Widget methods return `None`; `check` reports the recorded error.
struct GpuControlMap(FaustGui):
    var base:         OptPtr[U8, MUT_NOTRK]
    var active:       Arr[GpuControlZone, GPU_ZONE_CAP]
    var active_len:   S32
    var passive:      Arr[GpuControlZone, GPU_ZONE_CAP]
    var passive_len:  S32
    var err:          S32

    def __init__(out map):
        map.base = None
        map.active = Arr[GpuControlZone, GPU_ZONE_CAP](
            fill=GpuControlZone(Ptr[FaustFloat, MUT_NOTRK].unsafe_dangling(), 0, False)
        )
        map.active_len = 0
        map.passive = Arr[GpuControlZone, GPU_ZONE_CAP](
            fill=GpuControlZone(Ptr[FaustFloat, MUT_NOTRK].unsafe_dangling(), 0, True)
        )
        map.passive_len = 0
        map.err = 0

    def reset[Dsp: FaustDspGpu](mut map, var dsp: Ptr[Dsp]) -> None:
        map.base = dsp.unsafe_bitcast[U8]()
        map.active_len = 0
        map.passive_len = 0
        map.err = 0

    def check[Dsp: FaustDspGpu](imm map) -> S32:
        if map.err:
            return map.err
        if map.base == None:
            return GPU_MAP_INVALID
        var limit = size_of[Dsp]() - size_of[FaustFloat]()
        for i in range(Int(map.active_len)):
            if map.active[i].offset < 0 or map.active[i].offset > limit:
                return GPU_MAP_INVALID
        for i in range(Int(map.passive_len)):
            if map.passive[i].offset < 0 or map.passive[i].offset > limit:
                return GPU_MAP_INVALID
        return 0

    @always_inline
    def _add(mut map, mut zone: FaustFloat, passive: Bool) -> None:
        if map.err or map.base == None:
            return
        var host = Ptr(to=zone).unsafe_origin_cast[MUT_NOTRK]()
        for i in range(Int(map.active_len)):
            if map.active[i].host == host:
                if passive:
                    map.err = GPU_MAP_INVALID
                return
        for i in range(Int(map.passive_len)):
            if map.passive[i].host == host:
                if not passive:
                    map.err = GPU_MAP_INVALID
                return
        var offset = pointer_to_int(host) - pointer_to_int(map.base.unsafe_value())
        if passive:
            if map.passive_len == GPU_ZONE_CAP:
                map.err = GPU_MAP_INVALID
                return
            map.passive[Int(map.passive_len)] = GpuControlZone(host, offset, True)
            map.passive_len += 1
        else:
            if map.active_len == GPU_ZONE_CAP:
                map.err = GPU_MAP_INVALID
                return
            map.active[Int(map.active_len)] = GpuControlZone(host, offset, False)
            map.active_len += 1

    @always_inline
    def add_button(mut map, var label: String, mut zone: FaustFloat) -> None:
        map._add(zone, False)

    @always_inline
    def add_check_button(mut map, var label: String, mut zone: FaustFloat) -> None:
        map._add(zone, False)

    @always_inline
    def add_vertical_slider(
        mut map,
        var label:  String,
        mut zone:   FaustFloat,
        var init:   FaustFloat,
        var min:    FaustFloat,
        var max:    FaustFloat,
        var step:   FaustFloat
    ) -> None:
        map._add(zone, False)

    @always_inline
    def add_horizontal_slider(
        mut map,
        var label:  String,
        mut zone:   FaustFloat,
        var init:   FaustFloat,
        var min:    FaustFloat,
        var max:    FaustFloat,
        var step:   FaustFloat
    ) -> None:
        map._add(zone, False)

    @always_inline
    def add_num_entry(
        mut map,
        var label:  String,
        mut zone:   FaustFloat,
        var init:   FaustFloat,
        var min:    FaustFloat,
        var max:    FaustFloat,
        var step:   FaustFloat
    ) -> None:
        map._add(zone, False)

    @always_inline
    def add_vertical_bargraph(
        mut map, var label: String, mut zone: FaustFloat, var min: FaustFloat,
        var max: FaustFloat
    ) -> None:
        map._add(zone, True)

    @always_inline
    def add_horizontal_bargraph(
        mut map, var label: String, mut zone: FaustFloat, var min: FaustFloat,
        var max: FaustFloat
    ) -> None:
        map._add(zone, True)

    @always_inline
    def run(mut map) -> S32:
        return 0


# Builds and checks the map through the regular `FaustGui` API.
def build_gpu_control_map[Dsp: FaustDspGpu](
    var dsp: Ptr[Dsp], mut map: GpuControlMap
) -> S32:
    map.reset(dsp)
    dsp[].build_user_interface(map)
    return map.check[Dsp]()
