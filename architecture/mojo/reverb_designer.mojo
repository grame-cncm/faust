# ==============================================================================
# Faust to Mojo impulse architecture for the impulse-tests integration.
# Provides the definitions and the main entry point to run the dsp, and print
# the samples to stdout. The impulse-tests framework will generate the impulse
# responses redirecting the output to the `.ir` files.
# ==============================================================================
# First section of architecture provided code start.
# Imports the modules and the definitions of the architecture code.
# ==============================================================================

from conf import *
from mem import *
from dsp import *
from gui import *
from meta import *
from help import *
from test.impulse import *
from gui.control import ControlGui

# ==============================================================================
# First section of architecture provided code end.
# ==============================================================================
# Code generated with Faust 2.87.10 (https://faust.grame.fr)
# name: "reverb_designer"
# Compilation options: 
#   -a impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 
#   -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs
# ==============================================================================

comptime dreal = f64
comptime wreal = simd_width_of[dreal]()
comptime Real = Scalar[dreal]
comptime RVec = SIMD[dreal, simd_width_of[dreal]()]

@fieldwise_init
struct mydsp(FaustDsp):
    var null_val: FaustFloat
    var i_rec17_perm: Arr[S32, 4]
    var rec16_perm: Arr[F64, 4]
    var sample_rate: S32
    var const0: F64
    var const1: F64
    var hslider0: FaustFloat
    var rec22_perm: Arr[F64, 4]
    var rec21_perm: Arr[F64, 4]
    var hslider1: FaustFloat
    var rec20_perm: Arr[F64, 4]
    var hslider2: FaustFloat
    var rec19_perm: Arr[F64, 4]
    var hslider3: FaustFloat
    var rec18_perm: Arr[F64, 4]
    var rec28_perm: Arr[F64, 4]
    var rec27_perm: Arr[F64, 4]
    var yec0_perm: Arr[F64, 4]
    var rec26_perm: Arr[F64, 4]
    var rec25_perm: Arr[F64, 4]
    var rec24_perm: Arr[F64, 4]
    var rec23_perm: Arr[F64, 4]
    var rec33_perm: Arr[F64, 4]
    var rec32_perm: Arr[F64, 4]
    var yec1_perm: Arr[F64, 4]
    var rec31_perm: Arr[F64, 4]
    var rec30_perm: Arr[F64, 4]
    var rec29_perm: Arr[F64, 4]
    var rec37_perm: Arr[F64, 4]
    var rec36_perm: Arr[F64, 4]
    var yec2_perm: Arr[F64, 4]
    var rec35_perm: Arr[F64, 4]
    var rec34_perm: Arr[F64, 4]
    var rec39_perm: Arr[F64, 4]
    var rec38_perm: Arr[F64, 4]
    var rec44_perm: Arr[F64, 4]
    var rec43_perm: Arr[F64, 4]
    var rec42_perm: Arr[F64, 4]
    var rec41_perm: Arr[F64, 4]
    var rec40_perm: Arr[F64, 4]
    var rec50_perm: Arr[F64, 4]
    var rec49_perm: Arr[F64, 4]
    var yec3_perm: Arr[F64, 4]
    var rec48_perm: Arr[F64, 4]
    var rec47_perm: Arr[F64, 4]
    var rec46_perm: Arr[F64, 4]
    var rec45_perm: Arr[F64, 4]
    var rec55_perm: Arr[F64, 4]
    var rec54_perm: Arr[F64, 4]
    var yec4_perm: Arr[F64, 4]
    var rec53_perm: Arr[F64, 4]
    var rec52_perm: Arr[F64, 4]
    var rec51_perm: Arr[F64, 4]
    var rec59_perm: Arr[F64, 4]
    var rec58_perm: Arr[F64, 4]
    var yec5_perm: Arr[F64, 4]
    var rec57_perm: Arr[F64, 4]
    var rec56_perm: Arr[F64, 4]
    var rec61_perm: Arr[F64, 4]
    var rec60_perm: Arr[F64, 4]
    var rec66_perm: Arr[F64, 4]
    var rec65_perm: Arr[F64, 4]
    var rec64_perm: Arr[F64, 4]
    var rec63_perm: Arr[F64, 4]
    var rec62_perm: Arr[F64, 4]
    var rec72_perm: Arr[F64, 4]
    var rec71_perm: Arr[F64, 4]
    var yec6_perm: Arr[F64, 4]
    var rec70_perm: Arr[F64, 4]
    var rec69_perm: Arr[F64, 4]
    var rec68_perm: Arr[F64, 4]
    var rec67_perm: Arr[F64, 4]
    var rec77_perm: Arr[F64, 4]
    var rec76_perm: Arr[F64, 4]
    var yec7_perm: Arr[F64, 4]
    var rec75_perm: Arr[F64, 4]
    var rec74_perm: Arr[F64, 4]
    var rec73_perm: Arr[F64, 4]
    var rec81_perm: Arr[F64, 4]
    var rec80_perm: Arr[F64, 4]
    var yec8_perm: Arr[F64, 4]
    var rec79_perm: Arr[F64, 4]
    var rec78_perm: Arr[F64, 4]
    var rec83_perm: Arr[F64, 4]
    var rec82_perm: Arr[F64, 4]
    var rec88_perm: Arr[F64, 4]
    var rec87_perm: Arr[F64, 4]
    var rec86_perm: Arr[F64, 4]
    var rec85_perm: Arr[F64, 4]
    var rec84_perm: Arr[F64, 4]
    var rec94_perm: Arr[F64, 4]
    var rec93_perm: Arr[F64, 4]
    var yec9_perm: Arr[F64, 4]
    var rec92_perm: Arr[F64, 4]
    var rec91_perm: Arr[F64, 4]
    var rec90_perm: Arr[F64, 4]
    var rec89_perm: Arr[F64, 4]
    var rec99_perm: Arr[F64, 4]
    var rec98_perm: Arr[F64, 4]
    var yec10_perm: Arr[F64, 4]
    var rec97_perm: Arr[F64, 4]
    var rec96_perm: Arr[F64, 4]
    var rec95_perm: Arr[F64, 4]
    var rec103_perm: Arr[F64, 4]
    var rec102_perm: Arr[F64, 4]
    var yec11_perm: Arr[F64, 4]
    var rec101_perm: Arr[F64, 4]
    var rec100_perm: Arr[F64, 4]
    var rec105_perm: Arr[F64, 4]
    var rec104_perm: Arr[F64, 4]
    var rec110_perm: Arr[F64, 4]
    var rec109_perm: Arr[F64, 4]
    var rec108_perm: Arr[F64, 4]
    var rec107_perm: Arr[F64, 4]
    var rec106_perm: Arr[F64, 4]
    var rec116_perm: Arr[F64, 4]
    var rec115_perm: Arr[F64, 4]
    var yec12_perm: Arr[F64, 4]
    var rec114_perm: Arr[F64, 4]
    var rec113_perm: Arr[F64, 4]
    var rec112_perm: Arr[F64, 4]
    var rec111_perm: Arr[F64, 4]
    var rec121_perm: Arr[F64, 4]
    var rec120_perm: Arr[F64, 4]
    var yec13_perm: Arr[F64, 4]
    var rec119_perm: Arr[F64, 4]
    var rec118_perm: Arr[F64, 4]
    var rec117_perm: Arr[F64, 4]
    var rec125_perm: Arr[F64, 4]
    var rec124_perm: Arr[F64, 4]
    var yec14_perm: Arr[F64, 4]
    var rec123_perm: Arr[F64, 4]
    var rec122_perm: Arr[F64, 4]
    var rec127_perm: Arr[F64, 4]
    var rec126_perm: Arr[F64, 4]
    var rec132_perm: Arr[F64, 4]
    var rec131_perm: Arr[F64, 4]
    var rec130_perm: Arr[F64, 4]
    var rec129_perm: Arr[F64, 4]
    var rec128_perm: Arr[F64, 4]
    var rec138_perm: Arr[F64, 4]
    var rec137_perm: Arr[F64, 4]
    var yec15_perm: Arr[F64, 4]
    var rec136_perm: Arr[F64, 4]
    var rec135_perm: Arr[F64, 4]
    var rec134_perm: Arr[F64, 4]
    var rec133_perm: Arr[F64, 4]
    var rec143_perm: Arr[F64, 4]
    var rec142_perm: Arr[F64, 4]
    var yec16_perm: Arr[F64, 4]
    var rec141_perm: Arr[F64, 4]
    var rec140_perm: Arr[F64, 4]
    var rec139_perm: Arr[F64, 4]
    var rec147_perm: Arr[F64, 4]
    var rec146_perm: Arr[F64, 4]
    var yec17_perm: Arr[F64, 4]
    var rec145_perm: Arr[F64, 4]
    var rec144_perm: Arr[F64, 4]
    var rec149_perm: Arr[F64, 4]
    var rec148_perm: Arr[F64, 4]
    var rec154_perm: Arr[F64, 4]
    var rec153_perm: Arr[F64, 4]
    var rec152_perm: Arr[F64, 4]
    var rec151_perm: Arr[F64, 4]
    var rec150_perm: Arr[F64, 4]
    var rec160_perm: Arr[F64, 4]
    var rec159_perm: Arr[F64, 4]
    var yec18_perm: Arr[F64, 4]
    var rec158_perm: Arr[F64, 4]
    var rec157_perm: Arr[F64, 4]
    var rec156_perm: Arr[F64, 4]
    var rec155_perm: Arr[F64, 4]
    var rec165_perm: Arr[F64, 4]
    var rec164_perm: Arr[F64, 4]
    var yec19_perm: Arr[F64, 4]
    var rec163_perm: Arr[F64, 4]
    var rec162_perm: Arr[F64, 4]
    var rec161_perm: Arr[F64, 4]
    var rec169_perm: Arr[F64, 4]
    var rec168_perm: Arr[F64, 4]
    var yec20_perm: Arr[F64, 4]
    var rec167_perm: Arr[F64, 4]
    var rec166_perm: Arr[F64, 4]
    var rec171_perm: Arr[F64, 4]
    var rec170_perm: Arr[F64, 4]
    var rec176_perm: Arr[F64, 4]
    var rec175_perm: Arr[F64, 4]
    var rec174_perm: Arr[F64, 4]
    var rec173_perm: Arr[F64, 4]
    var rec172_perm: Arr[F64, 4]
    var rec182_perm: Arr[F64, 4]
    var rec181_perm: Arr[F64, 4]
    var yec21_perm: Arr[F64, 4]
    var rec180_perm: Arr[F64, 4]
    var rec179_perm: Arr[F64, 4]
    var rec178_perm: Arr[F64, 4]
    var rec177_perm: Arr[F64, 4]
    var rec187_perm: Arr[F64, 4]
    var rec186_perm: Arr[F64, 4]
    var yec22_perm: Arr[F64, 4]
    var rec185_perm: Arr[F64, 4]
    var rec184_perm: Arr[F64, 4]
    var rec183_perm: Arr[F64, 4]
    var rec191_perm: Arr[F64, 4]
    var rec190_perm: Arr[F64, 4]
    var yec23_perm: Arr[F64, 4]
    var rec189_perm: Arr[F64, 4]
    var rec188_perm: Arr[F64, 4]
    var rec193_perm: Arr[F64, 4]
    var rec192_perm: Arr[F64, 4]
    var rec198_perm: Arr[F64, 4]
    var rec197_perm: Arr[F64, 4]
    var rec196_perm: Arr[F64, 4]
    var rec195_perm: Arr[F64, 4]
    var rec194_perm: Arr[F64, 4]
    var rec204_perm: Arr[F64, 4]
    var rec203_perm: Arr[F64, 4]
    var yec24_perm: Arr[F64, 4]
    var rec202_perm: Arr[F64, 4]
    var rec201_perm: Arr[F64, 4]
    var rec200_perm: Arr[F64, 4]
    var rec199_perm: Arr[F64, 4]
    var rec209_perm: Arr[F64, 4]
    var rec208_perm: Arr[F64, 4]
    var yec25_perm: Arr[F64, 4]
    var rec207_perm: Arr[F64, 4]
    var rec206_perm: Arr[F64, 4]
    var rec205_perm: Arr[F64, 4]
    var rec213_perm: Arr[F64, 4]
    var rec212_perm: Arr[F64, 4]
    var yec26_perm: Arr[F64, 4]
    var rec211_perm: Arr[F64, 4]
    var rec210_perm: Arr[F64, 4]
    var rec215_perm: Arr[F64, 4]
    var rec214_perm: Arr[F64, 4]
    var rec220_perm: Arr[F64, 4]
    var rec219_perm: Arr[F64, 4]
    var rec218_perm: Arr[F64, 4]
    var rec217_perm: Arr[F64, 4]
    var rec216_perm: Arr[F64, 4]
    var rec226_perm: Arr[F64, 4]
    var rec225_perm: Arr[F64, 4]
    var yec27_perm: Arr[F64, 4]
    var rec224_perm: Arr[F64, 4]
    var rec223_perm: Arr[F64, 4]
    var rec222_perm: Arr[F64, 4]
    var rec221_perm: Arr[F64, 4]
    var rec231_perm: Arr[F64, 4]
    var rec230_perm: Arr[F64, 4]
    var yec28_perm: Arr[F64, 4]
    var rec229_perm: Arr[F64, 4]
    var rec228_perm: Arr[F64, 4]
    var rec227_perm: Arr[F64, 4]
    var rec235_perm: Arr[F64, 4]
    var rec234_perm: Arr[F64, 4]
    var yec29_perm: Arr[F64, 4]
    var rec233_perm: Arr[F64, 4]
    var rec232_perm: Arr[F64, 4]
    var rec237_perm: Arr[F64, 4]
    var rec236_perm: Arr[F64, 4]
    var rec242_perm: Arr[F64, 4]
    var rec241_perm: Arr[F64, 4]
    var rec240_perm: Arr[F64, 4]
    var rec239_perm: Arr[F64, 4]
    var rec238_perm: Arr[F64, 4]
    var rec248_perm: Arr[F64, 4]
    var rec247_perm: Arr[F64, 4]
    var yec30_perm: Arr[F64, 4]
    var rec246_perm: Arr[F64, 4]
    var rec245_perm: Arr[F64, 4]
    var rec244_perm: Arr[F64, 4]
    var rec243_perm: Arr[F64, 4]
    var rec253_perm: Arr[F64, 4]
    var rec252_perm: Arr[F64, 4]
    var yec31_perm: Arr[F64, 4]
    var rec251_perm: Arr[F64, 4]
    var rec250_perm: Arr[F64, 4]
    var rec249_perm: Arr[F64, 4]
    var rec257_perm: Arr[F64, 4]
    var rec256_perm: Arr[F64, 4]
    var yec32_perm: Arr[F64, 4]
    var rec255_perm: Arr[F64, 4]
    var rec254_perm: Arr[F64, 4]
    var rec259_perm: Arr[F64, 4]
    var rec258_perm: Arr[F64, 4]
    var rec264_perm: Arr[F64, 4]
    var rec263_perm: Arr[F64, 4]
    var rec262_perm: Arr[F64, 4]
    var rec261_perm: Arr[F64, 4]
    var rec260_perm: Arr[F64, 4]
    var rec270_perm: Arr[F64, 4]
    var rec269_perm: Arr[F64, 4]
    var yec33_perm: Arr[F64, 4]
    var rec268_perm: Arr[F64, 4]
    var rec267_perm: Arr[F64, 4]
    var rec266_perm: Arr[F64, 4]
    var rec265_perm: Arr[F64, 4]
    var rec275_perm: Arr[F64, 4]
    var rec274_perm: Arr[F64, 4]
    var yec34_perm: Arr[F64, 4]
    var rec273_perm: Arr[F64, 4]
    var rec272_perm: Arr[F64, 4]
    var rec271_perm: Arr[F64, 4]
    var rec279_perm: Arr[F64, 4]
    var rec278_perm: Arr[F64, 4]
    var yec35_perm: Arr[F64, 4]
    var rec277_perm: Arr[F64, 4]
    var rec276_perm: Arr[F64, 4]
    var rec281_perm: Arr[F64, 4]
    var rec280_perm: Arr[F64, 4]
    var rec286_perm: Arr[F64, 4]
    var rec285_perm: Arr[F64, 4]
    var rec284_perm: Arr[F64, 4]
    var rec283_perm: Arr[F64, 4]
    var rec282_perm: Arr[F64, 4]
    var rec292_perm: Arr[F64, 4]
    var rec291_perm: Arr[F64, 4]
    var yec36_perm: Arr[F64, 4]
    var rec290_perm: Arr[F64, 4]
    var rec289_perm: Arr[F64, 4]
    var rec288_perm: Arr[F64, 4]
    var rec287_perm: Arr[F64, 4]
    var rec297_perm: Arr[F64, 4]
    var rec296_perm: Arr[F64, 4]
    var yec37_perm: Arr[F64, 4]
    var rec295_perm: Arr[F64, 4]
    var rec294_perm: Arr[F64, 4]
    var rec293_perm: Arr[F64, 4]
    var rec301_perm: Arr[F64, 4]
    var rec300_perm: Arr[F64, 4]
    var yec38_perm: Arr[F64, 4]
    var rec299_perm: Arr[F64, 4]
    var rec298_perm: Arr[F64, 4]
    var rec303_perm: Arr[F64, 4]
    var rec302_perm: Arr[F64, 4]
    var rec308_perm: Arr[F64, 4]
    var rec307_perm: Arr[F64, 4]
    var rec306_perm: Arr[F64, 4]
    var rec305_perm: Arr[F64, 4]
    var rec304_perm: Arr[F64, 4]
    var rec314_perm: Arr[F64, 4]
    var rec313_perm: Arr[F64, 4]
    var yec39_perm: Arr[F64, 4]
    var rec312_perm: Arr[F64, 4]
    var rec311_perm: Arr[F64, 4]
    var rec310_perm: Arr[F64, 4]
    var rec309_perm: Arr[F64, 4]
    var rec319_perm: Arr[F64, 4]
    var rec318_perm: Arr[F64, 4]
    var yec40_perm: Arr[F64, 4]
    var rec317_perm: Arr[F64, 4]
    var rec316_perm: Arr[F64, 4]
    var rec315_perm: Arr[F64, 4]
    var rec323_perm: Arr[F64, 4]
    var rec322_perm: Arr[F64, 4]
    var yec41_perm: Arr[F64, 4]
    var rec321_perm: Arr[F64, 4]
    var rec320_perm: Arr[F64, 4]
    var rec325_perm: Arr[F64, 4]
    var rec324_perm: Arr[F64, 4]
    var rec330_perm: Arr[F64, 4]
    var rec329_perm: Arr[F64, 4]
    var rec328_perm: Arr[F64, 4]
    var rec327_perm: Arr[F64, 4]
    var rec326_perm: Arr[F64, 4]
    var rec336_perm: Arr[F64, 4]
    var rec335_perm: Arr[F64, 4]
    var yec42_perm: Arr[F64, 4]
    var rec334_perm: Arr[F64, 4]
    var rec333_perm: Arr[F64, 4]
    var rec332_perm: Arr[F64, 4]
    var rec331_perm: Arr[F64, 4]
    var rec341_perm: Arr[F64, 4]
    var rec340_perm: Arr[F64, 4]
    var yec43_perm: Arr[F64, 4]
    var rec339_perm: Arr[F64, 4]
    var rec338_perm: Arr[F64, 4]
    var rec337_perm: Arr[F64, 4]
    var rec345_perm: Arr[F64, 4]
    var rec344_perm: Arr[F64, 4]
    var yec44_perm: Arr[F64, 4]
    var rec343_perm: Arr[F64, 4]
    var rec342_perm: Arr[F64, 4]
    var rec347_perm: Arr[F64, 4]
    var rec346_perm: Arr[F64, 4]
    var rec352_perm: Arr[F64, 4]
    var rec351_perm: Arr[F64, 4]
    var rec350_perm: Arr[F64, 4]
    var rec349_perm: Arr[F64, 4]
    var rec348_perm: Arr[F64, 4]
    var rec358_perm: Arr[F64, 4]
    var rec357_perm: Arr[F64, 4]
    var yec45_perm: Arr[F64, 4]
    var rec356_perm: Arr[F64, 4]
    var rec355_perm: Arr[F64, 4]
    var rec354_perm: Arr[F64, 4]
    var rec353_perm: Arr[F64, 4]
    var rec363_perm: Arr[F64, 4]
    var rec362_perm: Arr[F64, 4]
    var yec46_perm: Arr[F64, 4]
    var rec361_perm: Arr[F64, 4]
    var rec360_perm: Arr[F64, 4]
    var rec359_perm: Arr[F64, 4]
    var rec367_perm: Arr[F64, 4]
    var rec366_perm: Arr[F64, 4]
    var yec47_perm: Arr[F64, 4]
    var rec365_perm: Arr[F64, 4]
    var rec364_perm: Arr[F64, 4]
    var rec369_perm: Arr[F64, 4]
    var rec368_perm: Arr[F64, 4]
    var checkbox0: FaustFloat
    var button0: FaustFloat
    var vec0_perm: Arr[F64, 4]
    var button1: FaustFloat
    var vec1_perm: Arr[F64, 4]
    var button2: FaustFloat
    var const2: F64
    var const3: F64
    var hslider4: FaustFloat
    var vslider0: FaustFloat
    var vslider1: FaustFloat
    var vslider2: FaustFloat
    var vslider3: FaustFloat
    var vslider4: FaustFloat
    var hslider5: FaustFloat
    var checkbox1: FaustFloat
    var yec48: Arr[F64, 16384]
    var yec48_idx: S32
    var yec48_idx_save: S32
    var rec0_perm: Arr[F64, 4]
    var button3: FaustFloat
    var vec2_perm: Arr[F64, 4]
    var yec49: Arr[F64, 16384]
    var yec49_idx: S32
    var yec49_idx_save: S32
    var rec1_perm: Arr[F64, 4]
    var yec50: Arr[F64, 16384]
    var yec50_idx: S32
    var yec50_idx_save: S32
    var rec2_perm: Arr[F64, 4]
    var yec51: Arr[F64, 16384]
    var yec51_idx: S32
    var yec51_idx_save: S32
    var rec3_perm: Arr[F64, 4]
    var yec52: Arr[F64, 16384]
    var yec52_idx: S32
    var yec52_idx_save: S32
    var rec4_perm: Arr[F64, 4]
    var yec53: Arr[F64, 16384]
    var yec53_idx: S32
    var yec53_idx_save: S32
    var rec5_perm: Arr[F64, 4]
    var yec54: Arr[F64, 16384]
    var yec54_idx: S32
    var yec54_idx_save: S32
    var rec6_perm: Arr[F64, 4]
    var yec55: Arr[F64, 16384]
    var yec55_idx: S32
    var yec55_idx_save: S32
    var rec7_perm: Arr[F64, 4]
    var yec56: Arr[F64, 16384]
    var yec56_idx: S32
    var yec56_idx_save: S32
    var rec8_perm: Arr[F64, 4]
    var yec57: Arr[F64, 16384]
    var yec57_idx: S32
    var yec57_idx_save: S32
    var rec9_perm: Arr[F64, 4]
    var yec58: Arr[F64, 16384]
    var yec58_idx: S32
    var yec58_idx_save: S32
    var rec10_perm: Arr[F64, 4]
    var yec59: Arr[F64, 16384]
    var yec59_idx: S32
    var yec59_idx_save: S32
    var rec11_perm: Arr[F64, 4]
    var yec60: Arr[F64, 16384]
    var yec60_idx: S32
    var yec60_idx_save: S32
    var rec12_perm: Arr[F64, 4]
    var yec61: Arr[F64, 16384]
    var yec61_idx: S32
    var yec61_idx_save: S32
    var rec13_perm: Arr[F64, 4]
    var yec62: Arr[F64, 16384]
    var yec62_idx: S32
    var yec62_idx_save: S32
    var rec14_perm: Arr[F64, 4]
    var yec63: Arr[F64, 16384]
    var yec63_idx: S32
    var yec63_idx_save: S32
    var rec15_perm: Arr[F64, 4]
    var hslider6: FaustFloat

    @always_inline
    def __init__(out dsp):
        dsp.null_val = FaustFloat(0.0)
        dsp.i_rec17_perm = Arr[S32, 4](fill=0)
        dsp.rec16_perm = Arr[F64, 4](fill=0.0)
        dsp.sample_rate = 0
        dsp.const0 = 0.0
        dsp.const1 = 0.0
        dsp.hslider0 = 0.0
        dsp.rec22_perm = Arr[F64, 4](fill=0.0)
        dsp.rec21_perm = Arr[F64, 4](fill=0.0)
        dsp.hslider1 = 0.0
        dsp.rec20_perm = Arr[F64, 4](fill=0.0)
        dsp.hslider2 = 0.0
        dsp.rec19_perm = Arr[F64, 4](fill=0.0)
        dsp.hslider3 = 0.0
        dsp.rec18_perm = Arr[F64, 4](fill=0.0)
        dsp.rec28_perm = Arr[F64, 4](fill=0.0)
        dsp.rec27_perm = Arr[F64, 4](fill=0.0)
        dsp.yec0_perm = Arr[F64, 4](fill=0.0)
        dsp.rec26_perm = Arr[F64, 4](fill=0.0)
        dsp.rec25_perm = Arr[F64, 4](fill=0.0)
        dsp.rec24_perm = Arr[F64, 4](fill=0.0)
        dsp.rec23_perm = Arr[F64, 4](fill=0.0)
        dsp.rec33_perm = Arr[F64, 4](fill=0.0)
        dsp.rec32_perm = Arr[F64, 4](fill=0.0)
        dsp.yec1_perm = Arr[F64, 4](fill=0.0)
        dsp.rec31_perm = Arr[F64, 4](fill=0.0)
        dsp.rec30_perm = Arr[F64, 4](fill=0.0)
        dsp.rec29_perm = Arr[F64, 4](fill=0.0)
        dsp.rec37_perm = Arr[F64, 4](fill=0.0)
        dsp.rec36_perm = Arr[F64, 4](fill=0.0)
        dsp.yec2_perm = Arr[F64, 4](fill=0.0)
        dsp.rec35_perm = Arr[F64, 4](fill=0.0)
        dsp.rec34_perm = Arr[F64, 4](fill=0.0)
        dsp.rec39_perm = Arr[F64, 4](fill=0.0)
        dsp.rec38_perm = Arr[F64, 4](fill=0.0)
        dsp.rec44_perm = Arr[F64, 4](fill=0.0)
        dsp.rec43_perm = Arr[F64, 4](fill=0.0)
        dsp.rec42_perm = Arr[F64, 4](fill=0.0)
        dsp.rec41_perm = Arr[F64, 4](fill=0.0)
        dsp.rec40_perm = Arr[F64, 4](fill=0.0)
        dsp.rec50_perm = Arr[F64, 4](fill=0.0)
        dsp.rec49_perm = Arr[F64, 4](fill=0.0)
        dsp.yec3_perm = Arr[F64, 4](fill=0.0)
        dsp.rec48_perm = Arr[F64, 4](fill=0.0)
        dsp.rec47_perm = Arr[F64, 4](fill=0.0)
        dsp.rec46_perm = Arr[F64, 4](fill=0.0)
        dsp.rec45_perm = Arr[F64, 4](fill=0.0)
        dsp.rec55_perm = Arr[F64, 4](fill=0.0)
        dsp.rec54_perm = Arr[F64, 4](fill=0.0)
        dsp.yec4_perm = Arr[F64, 4](fill=0.0)
        dsp.rec53_perm = Arr[F64, 4](fill=0.0)
        dsp.rec52_perm = Arr[F64, 4](fill=0.0)
        dsp.rec51_perm = Arr[F64, 4](fill=0.0)
        dsp.rec59_perm = Arr[F64, 4](fill=0.0)
        dsp.rec58_perm = Arr[F64, 4](fill=0.0)
        dsp.yec5_perm = Arr[F64, 4](fill=0.0)
        dsp.rec57_perm = Arr[F64, 4](fill=0.0)
        dsp.rec56_perm = Arr[F64, 4](fill=0.0)
        dsp.rec61_perm = Arr[F64, 4](fill=0.0)
        dsp.rec60_perm = Arr[F64, 4](fill=0.0)
        dsp.rec66_perm = Arr[F64, 4](fill=0.0)
        dsp.rec65_perm = Arr[F64, 4](fill=0.0)
        dsp.rec64_perm = Arr[F64, 4](fill=0.0)
        dsp.rec63_perm = Arr[F64, 4](fill=0.0)
        dsp.rec62_perm = Arr[F64, 4](fill=0.0)
        dsp.rec72_perm = Arr[F64, 4](fill=0.0)
        dsp.rec71_perm = Arr[F64, 4](fill=0.0)
        dsp.yec6_perm = Arr[F64, 4](fill=0.0)
        dsp.rec70_perm = Arr[F64, 4](fill=0.0)
        dsp.rec69_perm = Arr[F64, 4](fill=0.0)
        dsp.rec68_perm = Arr[F64, 4](fill=0.0)
        dsp.rec67_perm = Arr[F64, 4](fill=0.0)
        dsp.rec77_perm = Arr[F64, 4](fill=0.0)
        dsp.rec76_perm = Arr[F64, 4](fill=0.0)
        dsp.yec7_perm = Arr[F64, 4](fill=0.0)
        dsp.rec75_perm = Arr[F64, 4](fill=0.0)
        dsp.rec74_perm = Arr[F64, 4](fill=0.0)
        dsp.rec73_perm = Arr[F64, 4](fill=0.0)
        dsp.rec81_perm = Arr[F64, 4](fill=0.0)
        dsp.rec80_perm = Arr[F64, 4](fill=0.0)
        dsp.yec8_perm = Arr[F64, 4](fill=0.0)
        dsp.rec79_perm = Arr[F64, 4](fill=0.0)
        dsp.rec78_perm = Arr[F64, 4](fill=0.0)
        dsp.rec83_perm = Arr[F64, 4](fill=0.0)
        dsp.rec82_perm = Arr[F64, 4](fill=0.0)
        dsp.rec88_perm = Arr[F64, 4](fill=0.0)
        dsp.rec87_perm = Arr[F64, 4](fill=0.0)
        dsp.rec86_perm = Arr[F64, 4](fill=0.0)
        dsp.rec85_perm = Arr[F64, 4](fill=0.0)
        dsp.rec84_perm = Arr[F64, 4](fill=0.0)
        dsp.rec94_perm = Arr[F64, 4](fill=0.0)
        dsp.rec93_perm = Arr[F64, 4](fill=0.0)
        dsp.yec9_perm = Arr[F64, 4](fill=0.0)
        dsp.rec92_perm = Arr[F64, 4](fill=0.0)
        dsp.rec91_perm = Arr[F64, 4](fill=0.0)
        dsp.rec90_perm = Arr[F64, 4](fill=0.0)
        dsp.rec89_perm = Arr[F64, 4](fill=0.0)
        dsp.rec99_perm = Arr[F64, 4](fill=0.0)
        dsp.rec98_perm = Arr[F64, 4](fill=0.0)
        dsp.yec10_perm = Arr[F64, 4](fill=0.0)
        dsp.rec97_perm = Arr[F64, 4](fill=0.0)
        dsp.rec96_perm = Arr[F64, 4](fill=0.0)
        dsp.rec95_perm = Arr[F64, 4](fill=0.0)
        dsp.rec103_perm = Arr[F64, 4](fill=0.0)
        dsp.rec102_perm = Arr[F64, 4](fill=0.0)
        dsp.yec11_perm = Arr[F64, 4](fill=0.0)
        dsp.rec101_perm = Arr[F64, 4](fill=0.0)
        dsp.rec100_perm = Arr[F64, 4](fill=0.0)
        dsp.rec105_perm = Arr[F64, 4](fill=0.0)
        dsp.rec104_perm = Arr[F64, 4](fill=0.0)
        dsp.rec110_perm = Arr[F64, 4](fill=0.0)
        dsp.rec109_perm = Arr[F64, 4](fill=0.0)
        dsp.rec108_perm = Arr[F64, 4](fill=0.0)
        dsp.rec107_perm = Arr[F64, 4](fill=0.0)
        dsp.rec106_perm = Arr[F64, 4](fill=0.0)
        dsp.rec116_perm = Arr[F64, 4](fill=0.0)
        dsp.rec115_perm = Arr[F64, 4](fill=0.0)
        dsp.yec12_perm = Arr[F64, 4](fill=0.0)
        dsp.rec114_perm = Arr[F64, 4](fill=0.0)
        dsp.rec113_perm = Arr[F64, 4](fill=0.0)
        dsp.rec112_perm = Arr[F64, 4](fill=0.0)
        dsp.rec111_perm = Arr[F64, 4](fill=0.0)
        dsp.rec121_perm = Arr[F64, 4](fill=0.0)
        dsp.rec120_perm = Arr[F64, 4](fill=0.0)
        dsp.yec13_perm = Arr[F64, 4](fill=0.0)
        dsp.rec119_perm = Arr[F64, 4](fill=0.0)
        dsp.rec118_perm = Arr[F64, 4](fill=0.0)
        dsp.rec117_perm = Arr[F64, 4](fill=0.0)
        dsp.rec125_perm = Arr[F64, 4](fill=0.0)
        dsp.rec124_perm = Arr[F64, 4](fill=0.0)
        dsp.yec14_perm = Arr[F64, 4](fill=0.0)
        dsp.rec123_perm = Arr[F64, 4](fill=0.0)
        dsp.rec122_perm = Arr[F64, 4](fill=0.0)
        dsp.rec127_perm = Arr[F64, 4](fill=0.0)
        dsp.rec126_perm = Arr[F64, 4](fill=0.0)
        dsp.rec132_perm = Arr[F64, 4](fill=0.0)
        dsp.rec131_perm = Arr[F64, 4](fill=0.0)
        dsp.rec130_perm = Arr[F64, 4](fill=0.0)
        dsp.rec129_perm = Arr[F64, 4](fill=0.0)
        dsp.rec128_perm = Arr[F64, 4](fill=0.0)
        dsp.rec138_perm = Arr[F64, 4](fill=0.0)
        dsp.rec137_perm = Arr[F64, 4](fill=0.0)
        dsp.yec15_perm = Arr[F64, 4](fill=0.0)
        dsp.rec136_perm = Arr[F64, 4](fill=0.0)
        dsp.rec135_perm = Arr[F64, 4](fill=0.0)
        dsp.rec134_perm = Arr[F64, 4](fill=0.0)
        dsp.rec133_perm = Arr[F64, 4](fill=0.0)
        dsp.rec143_perm = Arr[F64, 4](fill=0.0)
        dsp.rec142_perm = Arr[F64, 4](fill=0.0)
        dsp.yec16_perm = Arr[F64, 4](fill=0.0)
        dsp.rec141_perm = Arr[F64, 4](fill=0.0)
        dsp.rec140_perm = Arr[F64, 4](fill=0.0)
        dsp.rec139_perm = Arr[F64, 4](fill=0.0)
        dsp.rec147_perm = Arr[F64, 4](fill=0.0)
        dsp.rec146_perm = Arr[F64, 4](fill=0.0)
        dsp.yec17_perm = Arr[F64, 4](fill=0.0)
        dsp.rec145_perm = Arr[F64, 4](fill=0.0)
        dsp.rec144_perm = Arr[F64, 4](fill=0.0)
        dsp.rec149_perm = Arr[F64, 4](fill=0.0)
        dsp.rec148_perm = Arr[F64, 4](fill=0.0)
        dsp.rec154_perm = Arr[F64, 4](fill=0.0)
        dsp.rec153_perm = Arr[F64, 4](fill=0.0)
        dsp.rec152_perm = Arr[F64, 4](fill=0.0)
        dsp.rec151_perm = Arr[F64, 4](fill=0.0)
        dsp.rec150_perm = Arr[F64, 4](fill=0.0)
        dsp.rec160_perm = Arr[F64, 4](fill=0.0)
        dsp.rec159_perm = Arr[F64, 4](fill=0.0)
        dsp.yec18_perm = Arr[F64, 4](fill=0.0)
        dsp.rec158_perm = Arr[F64, 4](fill=0.0)
        dsp.rec157_perm = Arr[F64, 4](fill=0.0)
        dsp.rec156_perm = Arr[F64, 4](fill=0.0)
        dsp.rec155_perm = Arr[F64, 4](fill=0.0)
        dsp.rec165_perm = Arr[F64, 4](fill=0.0)
        dsp.rec164_perm = Arr[F64, 4](fill=0.0)
        dsp.yec19_perm = Arr[F64, 4](fill=0.0)
        dsp.rec163_perm = Arr[F64, 4](fill=0.0)
        dsp.rec162_perm = Arr[F64, 4](fill=0.0)
        dsp.rec161_perm = Arr[F64, 4](fill=0.0)
        dsp.rec169_perm = Arr[F64, 4](fill=0.0)
        dsp.rec168_perm = Arr[F64, 4](fill=0.0)
        dsp.yec20_perm = Arr[F64, 4](fill=0.0)
        dsp.rec167_perm = Arr[F64, 4](fill=0.0)
        dsp.rec166_perm = Arr[F64, 4](fill=0.0)
        dsp.rec171_perm = Arr[F64, 4](fill=0.0)
        dsp.rec170_perm = Arr[F64, 4](fill=0.0)
        dsp.rec176_perm = Arr[F64, 4](fill=0.0)
        dsp.rec175_perm = Arr[F64, 4](fill=0.0)
        dsp.rec174_perm = Arr[F64, 4](fill=0.0)
        dsp.rec173_perm = Arr[F64, 4](fill=0.0)
        dsp.rec172_perm = Arr[F64, 4](fill=0.0)
        dsp.rec182_perm = Arr[F64, 4](fill=0.0)
        dsp.rec181_perm = Arr[F64, 4](fill=0.0)
        dsp.yec21_perm = Arr[F64, 4](fill=0.0)
        dsp.rec180_perm = Arr[F64, 4](fill=0.0)
        dsp.rec179_perm = Arr[F64, 4](fill=0.0)
        dsp.rec178_perm = Arr[F64, 4](fill=0.0)
        dsp.rec177_perm = Arr[F64, 4](fill=0.0)
        dsp.rec187_perm = Arr[F64, 4](fill=0.0)
        dsp.rec186_perm = Arr[F64, 4](fill=0.0)
        dsp.yec22_perm = Arr[F64, 4](fill=0.0)
        dsp.rec185_perm = Arr[F64, 4](fill=0.0)
        dsp.rec184_perm = Arr[F64, 4](fill=0.0)
        dsp.rec183_perm = Arr[F64, 4](fill=0.0)
        dsp.rec191_perm = Arr[F64, 4](fill=0.0)
        dsp.rec190_perm = Arr[F64, 4](fill=0.0)
        dsp.yec23_perm = Arr[F64, 4](fill=0.0)
        dsp.rec189_perm = Arr[F64, 4](fill=0.0)
        dsp.rec188_perm = Arr[F64, 4](fill=0.0)
        dsp.rec193_perm = Arr[F64, 4](fill=0.0)
        dsp.rec192_perm = Arr[F64, 4](fill=0.0)
        dsp.rec198_perm = Arr[F64, 4](fill=0.0)
        dsp.rec197_perm = Arr[F64, 4](fill=0.0)
        dsp.rec196_perm = Arr[F64, 4](fill=0.0)
        dsp.rec195_perm = Arr[F64, 4](fill=0.0)
        dsp.rec194_perm = Arr[F64, 4](fill=0.0)
        dsp.rec204_perm = Arr[F64, 4](fill=0.0)
        dsp.rec203_perm = Arr[F64, 4](fill=0.0)
        dsp.yec24_perm = Arr[F64, 4](fill=0.0)
        dsp.rec202_perm = Arr[F64, 4](fill=0.0)
        dsp.rec201_perm = Arr[F64, 4](fill=0.0)
        dsp.rec200_perm = Arr[F64, 4](fill=0.0)
        dsp.rec199_perm = Arr[F64, 4](fill=0.0)
        dsp.rec209_perm = Arr[F64, 4](fill=0.0)
        dsp.rec208_perm = Arr[F64, 4](fill=0.0)
        dsp.yec25_perm = Arr[F64, 4](fill=0.0)
        dsp.rec207_perm = Arr[F64, 4](fill=0.0)
        dsp.rec206_perm = Arr[F64, 4](fill=0.0)
        dsp.rec205_perm = Arr[F64, 4](fill=0.0)
        dsp.rec213_perm = Arr[F64, 4](fill=0.0)
        dsp.rec212_perm = Arr[F64, 4](fill=0.0)
        dsp.yec26_perm = Arr[F64, 4](fill=0.0)
        dsp.rec211_perm = Arr[F64, 4](fill=0.0)
        dsp.rec210_perm = Arr[F64, 4](fill=0.0)
        dsp.rec215_perm = Arr[F64, 4](fill=0.0)
        dsp.rec214_perm = Arr[F64, 4](fill=0.0)
        dsp.rec220_perm = Arr[F64, 4](fill=0.0)
        dsp.rec219_perm = Arr[F64, 4](fill=0.0)
        dsp.rec218_perm = Arr[F64, 4](fill=0.0)
        dsp.rec217_perm = Arr[F64, 4](fill=0.0)
        dsp.rec216_perm = Arr[F64, 4](fill=0.0)
        dsp.rec226_perm = Arr[F64, 4](fill=0.0)
        dsp.rec225_perm = Arr[F64, 4](fill=0.0)
        dsp.yec27_perm = Arr[F64, 4](fill=0.0)
        dsp.rec224_perm = Arr[F64, 4](fill=0.0)
        dsp.rec223_perm = Arr[F64, 4](fill=0.0)
        dsp.rec222_perm = Arr[F64, 4](fill=0.0)
        dsp.rec221_perm = Arr[F64, 4](fill=0.0)
        dsp.rec231_perm = Arr[F64, 4](fill=0.0)
        dsp.rec230_perm = Arr[F64, 4](fill=0.0)
        dsp.yec28_perm = Arr[F64, 4](fill=0.0)
        dsp.rec229_perm = Arr[F64, 4](fill=0.0)
        dsp.rec228_perm = Arr[F64, 4](fill=0.0)
        dsp.rec227_perm = Arr[F64, 4](fill=0.0)
        dsp.rec235_perm = Arr[F64, 4](fill=0.0)
        dsp.rec234_perm = Arr[F64, 4](fill=0.0)
        dsp.yec29_perm = Arr[F64, 4](fill=0.0)
        dsp.rec233_perm = Arr[F64, 4](fill=0.0)
        dsp.rec232_perm = Arr[F64, 4](fill=0.0)
        dsp.rec237_perm = Arr[F64, 4](fill=0.0)
        dsp.rec236_perm = Arr[F64, 4](fill=0.0)
        dsp.rec242_perm = Arr[F64, 4](fill=0.0)
        dsp.rec241_perm = Arr[F64, 4](fill=0.0)
        dsp.rec240_perm = Arr[F64, 4](fill=0.0)
        dsp.rec239_perm = Arr[F64, 4](fill=0.0)
        dsp.rec238_perm = Arr[F64, 4](fill=0.0)
        dsp.rec248_perm = Arr[F64, 4](fill=0.0)
        dsp.rec247_perm = Arr[F64, 4](fill=0.0)
        dsp.yec30_perm = Arr[F64, 4](fill=0.0)
        dsp.rec246_perm = Arr[F64, 4](fill=0.0)
        dsp.rec245_perm = Arr[F64, 4](fill=0.0)
        dsp.rec244_perm = Arr[F64, 4](fill=0.0)
        dsp.rec243_perm = Arr[F64, 4](fill=0.0)
        dsp.rec253_perm = Arr[F64, 4](fill=0.0)
        dsp.rec252_perm = Arr[F64, 4](fill=0.0)
        dsp.yec31_perm = Arr[F64, 4](fill=0.0)
        dsp.rec251_perm = Arr[F64, 4](fill=0.0)
        dsp.rec250_perm = Arr[F64, 4](fill=0.0)
        dsp.rec249_perm = Arr[F64, 4](fill=0.0)
        dsp.rec257_perm = Arr[F64, 4](fill=0.0)
        dsp.rec256_perm = Arr[F64, 4](fill=0.0)
        dsp.yec32_perm = Arr[F64, 4](fill=0.0)
        dsp.rec255_perm = Arr[F64, 4](fill=0.0)
        dsp.rec254_perm = Arr[F64, 4](fill=0.0)
        dsp.rec259_perm = Arr[F64, 4](fill=0.0)
        dsp.rec258_perm = Arr[F64, 4](fill=0.0)
        dsp.rec264_perm = Arr[F64, 4](fill=0.0)
        dsp.rec263_perm = Arr[F64, 4](fill=0.0)
        dsp.rec262_perm = Arr[F64, 4](fill=0.0)
        dsp.rec261_perm = Arr[F64, 4](fill=0.0)
        dsp.rec260_perm = Arr[F64, 4](fill=0.0)
        dsp.rec270_perm = Arr[F64, 4](fill=0.0)
        dsp.rec269_perm = Arr[F64, 4](fill=0.0)
        dsp.yec33_perm = Arr[F64, 4](fill=0.0)
        dsp.rec268_perm = Arr[F64, 4](fill=0.0)
        dsp.rec267_perm = Arr[F64, 4](fill=0.0)
        dsp.rec266_perm = Arr[F64, 4](fill=0.0)
        dsp.rec265_perm = Arr[F64, 4](fill=0.0)
        dsp.rec275_perm = Arr[F64, 4](fill=0.0)
        dsp.rec274_perm = Arr[F64, 4](fill=0.0)
        dsp.yec34_perm = Arr[F64, 4](fill=0.0)
        dsp.rec273_perm = Arr[F64, 4](fill=0.0)
        dsp.rec272_perm = Arr[F64, 4](fill=0.0)
        dsp.rec271_perm = Arr[F64, 4](fill=0.0)
        dsp.rec279_perm = Arr[F64, 4](fill=0.0)
        dsp.rec278_perm = Arr[F64, 4](fill=0.0)
        dsp.yec35_perm = Arr[F64, 4](fill=0.0)
        dsp.rec277_perm = Arr[F64, 4](fill=0.0)
        dsp.rec276_perm = Arr[F64, 4](fill=0.0)
        dsp.rec281_perm = Arr[F64, 4](fill=0.0)
        dsp.rec280_perm = Arr[F64, 4](fill=0.0)
        dsp.rec286_perm = Arr[F64, 4](fill=0.0)
        dsp.rec285_perm = Arr[F64, 4](fill=0.0)
        dsp.rec284_perm = Arr[F64, 4](fill=0.0)
        dsp.rec283_perm = Arr[F64, 4](fill=0.0)
        dsp.rec282_perm = Arr[F64, 4](fill=0.0)
        dsp.rec292_perm = Arr[F64, 4](fill=0.0)
        dsp.rec291_perm = Arr[F64, 4](fill=0.0)
        dsp.yec36_perm = Arr[F64, 4](fill=0.0)
        dsp.rec290_perm = Arr[F64, 4](fill=0.0)
        dsp.rec289_perm = Arr[F64, 4](fill=0.0)
        dsp.rec288_perm = Arr[F64, 4](fill=0.0)
        dsp.rec287_perm = Arr[F64, 4](fill=0.0)
        dsp.rec297_perm = Arr[F64, 4](fill=0.0)
        dsp.rec296_perm = Arr[F64, 4](fill=0.0)
        dsp.yec37_perm = Arr[F64, 4](fill=0.0)
        dsp.rec295_perm = Arr[F64, 4](fill=0.0)
        dsp.rec294_perm = Arr[F64, 4](fill=0.0)
        dsp.rec293_perm = Arr[F64, 4](fill=0.0)
        dsp.rec301_perm = Arr[F64, 4](fill=0.0)
        dsp.rec300_perm = Arr[F64, 4](fill=0.0)
        dsp.yec38_perm = Arr[F64, 4](fill=0.0)
        dsp.rec299_perm = Arr[F64, 4](fill=0.0)
        dsp.rec298_perm = Arr[F64, 4](fill=0.0)
        dsp.rec303_perm = Arr[F64, 4](fill=0.0)
        dsp.rec302_perm = Arr[F64, 4](fill=0.0)
        dsp.rec308_perm = Arr[F64, 4](fill=0.0)
        dsp.rec307_perm = Arr[F64, 4](fill=0.0)
        dsp.rec306_perm = Arr[F64, 4](fill=0.0)
        dsp.rec305_perm = Arr[F64, 4](fill=0.0)
        dsp.rec304_perm = Arr[F64, 4](fill=0.0)
        dsp.rec314_perm = Arr[F64, 4](fill=0.0)
        dsp.rec313_perm = Arr[F64, 4](fill=0.0)
        dsp.yec39_perm = Arr[F64, 4](fill=0.0)
        dsp.rec312_perm = Arr[F64, 4](fill=0.0)
        dsp.rec311_perm = Arr[F64, 4](fill=0.0)
        dsp.rec310_perm = Arr[F64, 4](fill=0.0)
        dsp.rec309_perm = Arr[F64, 4](fill=0.0)
        dsp.rec319_perm = Arr[F64, 4](fill=0.0)
        dsp.rec318_perm = Arr[F64, 4](fill=0.0)
        dsp.yec40_perm = Arr[F64, 4](fill=0.0)
        dsp.rec317_perm = Arr[F64, 4](fill=0.0)
        dsp.rec316_perm = Arr[F64, 4](fill=0.0)
        dsp.rec315_perm = Arr[F64, 4](fill=0.0)
        dsp.rec323_perm = Arr[F64, 4](fill=0.0)
        dsp.rec322_perm = Arr[F64, 4](fill=0.0)
        dsp.yec41_perm = Arr[F64, 4](fill=0.0)
        dsp.rec321_perm = Arr[F64, 4](fill=0.0)
        dsp.rec320_perm = Arr[F64, 4](fill=0.0)
        dsp.rec325_perm = Arr[F64, 4](fill=0.0)
        dsp.rec324_perm = Arr[F64, 4](fill=0.0)
        dsp.rec330_perm = Arr[F64, 4](fill=0.0)
        dsp.rec329_perm = Arr[F64, 4](fill=0.0)
        dsp.rec328_perm = Arr[F64, 4](fill=0.0)
        dsp.rec327_perm = Arr[F64, 4](fill=0.0)
        dsp.rec326_perm = Arr[F64, 4](fill=0.0)
        dsp.rec336_perm = Arr[F64, 4](fill=0.0)
        dsp.rec335_perm = Arr[F64, 4](fill=0.0)
        dsp.yec42_perm = Arr[F64, 4](fill=0.0)
        dsp.rec334_perm = Arr[F64, 4](fill=0.0)
        dsp.rec333_perm = Arr[F64, 4](fill=0.0)
        dsp.rec332_perm = Arr[F64, 4](fill=0.0)
        dsp.rec331_perm = Arr[F64, 4](fill=0.0)
        dsp.rec341_perm = Arr[F64, 4](fill=0.0)
        dsp.rec340_perm = Arr[F64, 4](fill=0.0)
        dsp.yec43_perm = Arr[F64, 4](fill=0.0)
        dsp.rec339_perm = Arr[F64, 4](fill=0.0)
        dsp.rec338_perm = Arr[F64, 4](fill=0.0)
        dsp.rec337_perm = Arr[F64, 4](fill=0.0)
        dsp.rec345_perm = Arr[F64, 4](fill=0.0)
        dsp.rec344_perm = Arr[F64, 4](fill=0.0)
        dsp.yec44_perm = Arr[F64, 4](fill=0.0)
        dsp.rec343_perm = Arr[F64, 4](fill=0.0)
        dsp.rec342_perm = Arr[F64, 4](fill=0.0)
        dsp.rec347_perm = Arr[F64, 4](fill=0.0)
        dsp.rec346_perm = Arr[F64, 4](fill=0.0)
        dsp.rec352_perm = Arr[F64, 4](fill=0.0)
        dsp.rec351_perm = Arr[F64, 4](fill=0.0)
        dsp.rec350_perm = Arr[F64, 4](fill=0.0)
        dsp.rec349_perm = Arr[F64, 4](fill=0.0)
        dsp.rec348_perm = Arr[F64, 4](fill=0.0)
        dsp.rec358_perm = Arr[F64, 4](fill=0.0)
        dsp.rec357_perm = Arr[F64, 4](fill=0.0)
        dsp.yec45_perm = Arr[F64, 4](fill=0.0)
        dsp.rec356_perm = Arr[F64, 4](fill=0.0)
        dsp.rec355_perm = Arr[F64, 4](fill=0.0)
        dsp.rec354_perm = Arr[F64, 4](fill=0.0)
        dsp.rec353_perm = Arr[F64, 4](fill=0.0)
        dsp.rec363_perm = Arr[F64, 4](fill=0.0)
        dsp.rec362_perm = Arr[F64, 4](fill=0.0)
        dsp.yec46_perm = Arr[F64, 4](fill=0.0)
        dsp.rec361_perm = Arr[F64, 4](fill=0.0)
        dsp.rec360_perm = Arr[F64, 4](fill=0.0)
        dsp.rec359_perm = Arr[F64, 4](fill=0.0)
        dsp.rec367_perm = Arr[F64, 4](fill=0.0)
        dsp.rec366_perm = Arr[F64, 4](fill=0.0)
        dsp.yec47_perm = Arr[F64, 4](fill=0.0)
        dsp.rec365_perm = Arr[F64, 4](fill=0.0)
        dsp.rec364_perm = Arr[F64, 4](fill=0.0)
        dsp.rec369_perm = Arr[F64, 4](fill=0.0)
        dsp.rec368_perm = Arr[F64, 4](fill=0.0)
        dsp.checkbox0 = 0.0
        dsp.button0 = 0.0
        dsp.vec0_perm = Arr[F64, 4](fill=0.0)
        dsp.button1 = 0.0
        dsp.vec1_perm = Arr[F64, 4](fill=0.0)
        dsp.button2 = 0.0
        dsp.const2 = 0.0
        dsp.const3 = 0.0
        dsp.hslider4 = 0.0
        dsp.vslider0 = 0.0
        dsp.vslider1 = 0.0
        dsp.vslider2 = 0.0
        dsp.vslider3 = 0.0
        dsp.vslider4 = 0.0
        dsp.hslider5 = 0.0
        dsp.checkbox1 = 0.0
        dsp.yec48 = Arr[F64, 16384](fill=0.0)
        dsp.yec48_idx = 0
        dsp.yec48_idx_save = 0
        dsp.rec0_perm = Arr[F64, 4](fill=0.0)
        dsp.button3 = 0.0
        dsp.vec2_perm = Arr[F64, 4](fill=0.0)
        dsp.yec49 = Arr[F64, 16384](fill=0.0)
        dsp.yec49_idx = 0
        dsp.yec49_idx_save = 0
        dsp.rec1_perm = Arr[F64, 4](fill=0.0)
        dsp.yec50 = Arr[F64, 16384](fill=0.0)
        dsp.yec50_idx = 0
        dsp.yec50_idx_save = 0
        dsp.rec2_perm = Arr[F64, 4](fill=0.0)
        dsp.yec51 = Arr[F64, 16384](fill=0.0)
        dsp.yec51_idx = 0
        dsp.yec51_idx_save = 0
        dsp.rec3_perm = Arr[F64, 4](fill=0.0)
        dsp.yec52 = Arr[F64, 16384](fill=0.0)
        dsp.yec52_idx = 0
        dsp.yec52_idx_save = 0
        dsp.rec4_perm = Arr[F64, 4](fill=0.0)
        dsp.yec53 = Arr[F64, 16384](fill=0.0)
        dsp.yec53_idx = 0
        dsp.yec53_idx_save = 0
        dsp.rec5_perm = Arr[F64, 4](fill=0.0)
        dsp.yec54 = Arr[F64, 16384](fill=0.0)
        dsp.yec54_idx = 0
        dsp.yec54_idx_save = 0
        dsp.rec6_perm = Arr[F64, 4](fill=0.0)
        dsp.yec55 = Arr[F64, 16384](fill=0.0)
        dsp.yec55_idx = 0
        dsp.yec55_idx_save = 0
        dsp.rec7_perm = Arr[F64, 4](fill=0.0)
        dsp.yec56 = Arr[F64, 16384](fill=0.0)
        dsp.yec56_idx = 0
        dsp.yec56_idx_save = 0
        dsp.rec8_perm = Arr[F64, 4](fill=0.0)
        dsp.yec57 = Arr[F64, 16384](fill=0.0)
        dsp.yec57_idx = 0
        dsp.yec57_idx_save = 0
        dsp.rec9_perm = Arr[F64, 4](fill=0.0)
        dsp.yec58 = Arr[F64, 16384](fill=0.0)
        dsp.yec58_idx = 0
        dsp.yec58_idx_save = 0
        dsp.rec10_perm = Arr[F64, 4](fill=0.0)
        dsp.yec59 = Arr[F64, 16384](fill=0.0)
        dsp.yec59_idx = 0
        dsp.yec59_idx_save = 0
        dsp.rec11_perm = Arr[F64, 4](fill=0.0)
        dsp.yec60 = Arr[F64, 16384](fill=0.0)
        dsp.yec60_idx = 0
        dsp.yec60_idx_save = 0
        dsp.rec12_perm = Arr[F64, 4](fill=0.0)
        dsp.yec61 = Arr[F64, 16384](fill=0.0)
        dsp.yec61_idx = 0
        dsp.yec61_idx_save = 0
        dsp.rec13_perm = Arr[F64, 4](fill=0.0)
        dsp.yec62 = Arr[F64, 16384](fill=0.0)
        dsp.yec62_idx = 0
        dsp.yec62_idx_save = 0
        dsp.rec14_perm = Arr[F64, 4](fill=0.0)
        dsp.yec63 = Arr[F64, 16384](fill=0.0)
        dsp.yec63_idx = 0
        dsp.yec63_idx_save = 0
        dsp.rec15_perm = Arr[F64, 4](fill=0.0)
        dsp.hslider6 = 0.0

    @always_inline
    def get_sample_rate(imm dsp) -> S32:
        return dsp.sample_rate

    @always_inline
    def get_num_outputs(imm dsp) -> S32:
        return 2

    @always_inline
    def get_num_inputs(imm dsp) -> S32:
        return 2

    @always_inline
    def class_init(mut dsp, imm sample_rate: S32) -> None:
        pass

    @always_inline
    def instance_constants(mut dsp, imm sample_rate: S32) -> None:
        dsp.sample_rate = sample_rate
        dsp.const0 = min(1.92e+05, max(1.0, F64(dsp.sample_rate)))
        dsp.const1 = (3.141592653589793) / (dsp.const0)
        dsp.const2 = (6.907755278982138) / (dsp.const0)
        dsp.const3 = (0.0029154518950437317) * (dsp.const0)

    @always_inline
    def instance_reset_user_interface(mut dsp) -> None:
        dsp.hslider0 = 4000.0
        dsp.hslider1 = 2000.0
        dsp.hslider2 = 1000.0
        dsp.hslider3 = 500.0
        dsp.checkbox0 = 0.0
        dsp.button0 = 0.0
        dsp.button1 = 0.0
        dsp.button2 = 0.0
        dsp.hslider4 = 46.0
        dsp.vslider0 = 2.7
        dsp.vslider1 = 3.8
        dsp.vslider2 = 5.0
        dsp.vslider3 = 6.5
        dsp.vslider4 = 8.4
        dsp.hslider5 = 63.0
        dsp.checkbox1 = 0.0
        dsp.button3 = 0.0
        dsp.hslider6 = -40.0

    @always_inline
    def instance_clear(mut dsp) -> None:
        var l0 = S32(0)
        while (l0) < (S32(4)): 
            dsp.i_rec17_perm[l0] = S32(0)
            l0 = (l0) + (S32(1))
        var l1 = S32(0)
        while (l1) < (S32(4)): 
            dsp.rec16_perm[l1] = 0.0
            l1 = (l1) + (S32(1))
        var l2 = S32(0)
        while (l2) < (S32(4)): 
            dsp.rec22_perm[l2] = 0.0
            l2 = (l2) + (S32(1))
        var l3 = S32(0)
        while (l3) < (S32(4)): 
            dsp.rec21_perm[l3] = 0.0
            l3 = (l3) + (S32(1))
        var l4 = S32(0)
        while (l4) < (S32(4)): 
            dsp.rec20_perm[l4] = 0.0
            l4 = (l4) + (S32(1))
        var l5 = S32(0)
        while (l5) < (S32(4)): 
            dsp.rec19_perm[l5] = 0.0
            l5 = (l5) + (S32(1))
        var l6 = S32(0)
        while (l6) < (S32(4)): 
            dsp.rec18_perm[l6] = 0.0
            l6 = (l6) + (S32(1))
        var l7 = S32(0)
        while (l7) < (S32(4)): 
            dsp.rec28_perm[l7] = 0.0
            l7 = (l7) + (S32(1))
        var l8 = S32(0)
        while (l8) < (S32(4)): 
            dsp.rec27_perm[l8] = 0.0
            l8 = (l8) + (S32(1))
        var l9 = S32(0)
        while (l9) < (S32(4)): 
            dsp.yec0_perm[l9] = 0.0
            l9 = (l9) + (S32(1))
        var l10 = S32(0)
        while (l10) < (S32(4)): 
            dsp.rec26_perm[l10] = 0.0
            l10 = (l10) + (S32(1))
        var l11 = S32(0)
        while (l11) < (S32(4)): 
            dsp.rec25_perm[l11] = 0.0
            l11 = (l11) + (S32(1))
        var l12 = S32(0)
        while (l12) < (S32(4)): 
            dsp.rec24_perm[l12] = 0.0
            l12 = (l12) + (S32(1))
        var l13 = S32(0)
        while (l13) < (S32(4)): 
            dsp.rec23_perm[l13] = 0.0
            l13 = (l13) + (S32(1))
        var l14 = S32(0)
        while (l14) < (S32(4)): 
            dsp.rec33_perm[l14] = 0.0
            l14 = (l14) + (S32(1))
        var l15 = S32(0)
        while (l15) < (S32(4)): 
            dsp.rec32_perm[l15] = 0.0
            l15 = (l15) + (S32(1))
        var l16 = S32(0)
        while (l16) < (S32(4)): 
            dsp.yec1_perm[l16] = 0.0
            l16 = (l16) + (S32(1))
        var l17 = S32(0)
        while (l17) < (S32(4)): 
            dsp.rec31_perm[l17] = 0.0
            l17 = (l17) + (S32(1))
        var l18 = S32(0)
        while (l18) < (S32(4)): 
            dsp.rec30_perm[l18] = 0.0
            l18 = (l18) + (S32(1))
        var l19 = S32(0)
        while (l19) < (S32(4)): 
            dsp.rec29_perm[l19] = 0.0
            l19 = (l19) + (S32(1))
        var l20 = S32(0)
        while (l20) < (S32(4)): 
            dsp.rec37_perm[l20] = 0.0
            l20 = (l20) + (S32(1))
        var l21 = S32(0)
        while (l21) < (S32(4)): 
            dsp.rec36_perm[l21] = 0.0
            l21 = (l21) + (S32(1))
        var l22 = S32(0)
        while (l22) < (S32(4)): 
            dsp.yec2_perm[l22] = 0.0
            l22 = (l22) + (S32(1))
        var l23 = S32(0)
        while (l23) < (S32(4)): 
            dsp.rec35_perm[l23] = 0.0
            l23 = (l23) + (S32(1))
        var l24 = S32(0)
        while (l24) < (S32(4)): 
            dsp.rec34_perm[l24] = 0.0
            l24 = (l24) + (S32(1))
        var l25 = S32(0)
        while (l25) < (S32(4)): 
            dsp.rec39_perm[l25] = 0.0
            l25 = (l25) + (S32(1))
        var l26 = S32(0)
        while (l26) < (S32(4)): 
            dsp.rec38_perm[l26] = 0.0
            l26 = (l26) + (S32(1))
        var l27 = S32(0)
        while (l27) < (S32(4)): 
            dsp.rec44_perm[l27] = 0.0
            l27 = (l27) + (S32(1))
        var l28 = S32(0)
        while (l28) < (S32(4)): 
            dsp.rec43_perm[l28] = 0.0
            l28 = (l28) + (S32(1))
        var l29 = S32(0)
        while (l29) < (S32(4)): 
            dsp.rec42_perm[l29] = 0.0
            l29 = (l29) + (S32(1))
        var l30 = S32(0)
        while (l30) < (S32(4)): 
            dsp.rec41_perm[l30] = 0.0
            l30 = (l30) + (S32(1))
        var l31 = S32(0)
        while (l31) < (S32(4)): 
            dsp.rec40_perm[l31] = 0.0
            l31 = (l31) + (S32(1))
        var l32 = S32(0)
        while (l32) < (S32(4)): 
            dsp.rec50_perm[l32] = 0.0
            l32 = (l32) + (S32(1))
        var l33 = S32(0)
        while (l33) < (S32(4)): 
            dsp.rec49_perm[l33] = 0.0
            l33 = (l33) + (S32(1))
        var l34 = S32(0)
        while (l34) < (S32(4)): 
            dsp.yec3_perm[l34] = 0.0
            l34 = (l34) + (S32(1))
        var l35 = S32(0)
        while (l35) < (S32(4)): 
            dsp.rec48_perm[l35] = 0.0
            l35 = (l35) + (S32(1))
        var l36 = S32(0)
        while (l36) < (S32(4)): 
            dsp.rec47_perm[l36] = 0.0
            l36 = (l36) + (S32(1))
        var l37 = S32(0)
        while (l37) < (S32(4)): 
            dsp.rec46_perm[l37] = 0.0
            l37 = (l37) + (S32(1))
        var l38 = S32(0)
        while (l38) < (S32(4)): 
            dsp.rec45_perm[l38] = 0.0
            l38 = (l38) + (S32(1))
        var l39 = S32(0)
        while (l39) < (S32(4)): 
            dsp.rec55_perm[l39] = 0.0
            l39 = (l39) + (S32(1))
        var l40 = S32(0)
        while (l40) < (S32(4)): 
            dsp.rec54_perm[l40] = 0.0
            l40 = (l40) + (S32(1))
        var l41 = S32(0)
        while (l41) < (S32(4)): 
            dsp.yec4_perm[l41] = 0.0
            l41 = (l41) + (S32(1))
        var l42 = S32(0)
        while (l42) < (S32(4)): 
            dsp.rec53_perm[l42] = 0.0
            l42 = (l42) + (S32(1))
        var l43 = S32(0)
        while (l43) < (S32(4)): 
            dsp.rec52_perm[l43] = 0.0
            l43 = (l43) + (S32(1))
        var l44 = S32(0)
        while (l44) < (S32(4)): 
            dsp.rec51_perm[l44] = 0.0
            l44 = (l44) + (S32(1))
        var l45 = S32(0)
        while (l45) < (S32(4)): 
            dsp.rec59_perm[l45] = 0.0
            l45 = (l45) + (S32(1))
        var l46 = S32(0)
        while (l46) < (S32(4)): 
            dsp.rec58_perm[l46] = 0.0
            l46 = (l46) + (S32(1))
        var l47 = S32(0)
        while (l47) < (S32(4)): 
            dsp.yec5_perm[l47] = 0.0
            l47 = (l47) + (S32(1))
        var l48 = S32(0)
        while (l48) < (S32(4)): 
            dsp.rec57_perm[l48] = 0.0
            l48 = (l48) + (S32(1))
        var l49 = S32(0)
        while (l49) < (S32(4)): 
            dsp.rec56_perm[l49] = 0.0
            l49 = (l49) + (S32(1))
        var l50 = S32(0)
        while (l50) < (S32(4)): 
            dsp.rec61_perm[l50] = 0.0
            l50 = (l50) + (S32(1))
        var l51 = S32(0)
        while (l51) < (S32(4)): 
            dsp.rec60_perm[l51] = 0.0
            l51 = (l51) + (S32(1))
        var l52 = S32(0)
        while (l52) < (S32(4)): 
            dsp.rec66_perm[l52] = 0.0
            l52 = (l52) + (S32(1))
        var l53 = S32(0)
        while (l53) < (S32(4)): 
            dsp.rec65_perm[l53] = 0.0
            l53 = (l53) + (S32(1))
        var l54 = S32(0)
        while (l54) < (S32(4)): 
            dsp.rec64_perm[l54] = 0.0
            l54 = (l54) + (S32(1))
        var l55 = S32(0)
        while (l55) < (S32(4)): 
            dsp.rec63_perm[l55] = 0.0
            l55 = (l55) + (S32(1))
        var l56 = S32(0)
        while (l56) < (S32(4)): 
            dsp.rec62_perm[l56] = 0.0
            l56 = (l56) + (S32(1))
        var l57 = S32(0)
        while (l57) < (S32(4)): 
            dsp.rec72_perm[l57] = 0.0
            l57 = (l57) + (S32(1))
        var l58 = S32(0)
        while (l58) < (S32(4)): 
            dsp.rec71_perm[l58] = 0.0
            l58 = (l58) + (S32(1))
        var l59 = S32(0)
        while (l59) < (S32(4)): 
            dsp.yec6_perm[l59] = 0.0
            l59 = (l59) + (S32(1))
        var l60 = S32(0)
        while (l60) < (S32(4)): 
            dsp.rec70_perm[l60] = 0.0
            l60 = (l60) + (S32(1))
        var l61 = S32(0)
        while (l61) < (S32(4)): 
            dsp.rec69_perm[l61] = 0.0
            l61 = (l61) + (S32(1))
        var l62 = S32(0)
        while (l62) < (S32(4)): 
            dsp.rec68_perm[l62] = 0.0
            l62 = (l62) + (S32(1))
        var l63 = S32(0)
        while (l63) < (S32(4)): 
            dsp.rec67_perm[l63] = 0.0
            l63 = (l63) + (S32(1))
        var l64 = S32(0)
        while (l64) < (S32(4)): 
            dsp.rec77_perm[l64] = 0.0
            l64 = (l64) + (S32(1))
        var l65 = S32(0)
        while (l65) < (S32(4)): 
            dsp.rec76_perm[l65] = 0.0
            l65 = (l65) + (S32(1))
        var l66 = S32(0)
        while (l66) < (S32(4)): 
            dsp.yec7_perm[l66] = 0.0
            l66 = (l66) + (S32(1))
        var l67 = S32(0)
        while (l67) < (S32(4)): 
            dsp.rec75_perm[l67] = 0.0
            l67 = (l67) + (S32(1))
        var l68 = S32(0)
        while (l68) < (S32(4)): 
            dsp.rec74_perm[l68] = 0.0
            l68 = (l68) + (S32(1))
        var l69 = S32(0)
        while (l69) < (S32(4)): 
            dsp.rec73_perm[l69] = 0.0
            l69 = (l69) + (S32(1))
        var l70 = S32(0)
        while (l70) < (S32(4)): 
            dsp.rec81_perm[l70] = 0.0
            l70 = (l70) + (S32(1))
        var l71 = S32(0)
        while (l71) < (S32(4)): 
            dsp.rec80_perm[l71] = 0.0
            l71 = (l71) + (S32(1))
        var l72 = S32(0)
        while (l72) < (S32(4)): 
            dsp.yec8_perm[l72] = 0.0
            l72 = (l72) + (S32(1))
        var l73 = S32(0)
        while (l73) < (S32(4)): 
            dsp.rec79_perm[l73] = 0.0
            l73 = (l73) + (S32(1))
        var l74 = S32(0)
        while (l74) < (S32(4)): 
            dsp.rec78_perm[l74] = 0.0
            l74 = (l74) + (S32(1))
        var l75 = S32(0)
        while (l75) < (S32(4)): 
            dsp.rec83_perm[l75] = 0.0
            l75 = (l75) + (S32(1))
        var l76 = S32(0)
        while (l76) < (S32(4)): 
            dsp.rec82_perm[l76] = 0.0
            l76 = (l76) + (S32(1))
        var l77 = S32(0)
        while (l77) < (S32(4)): 
            dsp.rec88_perm[l77] = 0.0
            l77 = (l77) + (S32(1))
        var l78 = S32(0)
        while (l78) < (S32(4)): 
            dsp.rec87_perm[l78] = 0.0
            l78 = (l78) + (S32(1))
        var l79 = S32(0)
        while (l79) < (S32(4)): 
            dsp.rec86_perm[l79] = 0.0
            l79 = (l79) + (S32(1))
        var l80 = S32(0)
        while (l80) < (S32(4)): 
            dsp.rec85_perm[l80] = 0.0
            l80 = (l80) + (S32(1))
        var l81 = S32(0)
        while (l81) < (S32(4)): 
            dsp.rec84_perm[l81] = 0.0
            l81 = (l81) + (S32(1))
        var l82 = S32(0)
        while (l82) < (S32(4)): 
            dsp.rec94_perm[l82] = 0.0
            l82 = (l82) + (S32(1))
        var l83 = S32(0)
        while (l83) < (S32(4)): 
            dsp.rec93_perm[l83] = 0.0
            l83 = (l83) + (S32(1))
        var l84 = S32(0)
        while (l84) < (S32(4)): 
            dsp.yec9_perm[l84] = 0.0
            l84 = (l84) + (S32(1))
        var l85 = S32(0)
        while (l85) < (S32(4)): 
            dsp.rec92_perm[l85] = 0.0
            l85 = (l85) + (S32(1))
        var l86 = S32(0)
        while (l86) < (S32(4)): 
            dsp.rec91_perm[l86] = 0.0
            l86 = (l86) + (S32(1))
        var l87 = S32(0)
        while (l87) < (S32(4)): 
            dsp.rec90_perm[l87] = 0.0
            l87 = (l87) + (S32(1))
        var l88 = S32(0)
        while (l88) < (S32(4)): 
            dsp.rec89_perm[l88] = 0.0
            l88 = (l88) + (S32(1))
        var l89 = S32(0)
        while (l89) < (S32(4)): 
            dsp.rec99_perm[l89] = 0.0
            l89 = (l89) + (S32(1))
        var l90 = S32(0)
        while (l90) < (S32(4)): 
            dsp.rec98_perm[l90] = 0.0
            l90 = (l90) + (S32(1))
        var l91 = S32(0)
        while (l91) < (S32(4)): 
            dsp.yec10_perm[l91] = 0.0
            l91 = (l91) + (S32(1))
        var l92 = S32(0)
        while (l92) < (S32(4)): 
            dsp.rec97_perm[l92] = 0.0
            l92 = (l92) + (S32(1))
        var l93 = S32(0)
        while (l93) < (S32(4)): 
            dsp.rec96_perm[l93] = 0.0
            l93 = (l93) + (S32(1))
        var l94 = S32(0)
        while (l94) < (S32(4)): 
            dsp.rec95_perm[l94] = 0.0
            l94 = (l94) + (S32(1))
        var l95 = S32(0)
        while (l95) < (S32(4)): 
            dsp.rec103_perm[l95] = 0.0
            l95 = (l95) + (S32(1))
        var l96 = S32(0)
        while (l96) < (S32(4)): 
            dsp.rec102_perm[l96] = 0.0
            l96 = (l96) + (S32(1))
        var l97 = S32(0)
        while (l97) < (S32(4)): 
            dsp.yec11_perm[l97] = 0.0
            l97 = (l97) + (S32(1))
        var l98 = S32(0)
        while (l98) < (S32(4)): 
            dsp.rec101_perm[l98] = 0.0
            l98 = (l98) + (S32(1))
        var l99 = S32(0)
        while (l99) < (S32(4)): 
            dsp.rec100_perm[l99] = 0.0
            l99 = (l99) + (S32(1))
        var l100 = S32(0)
        while (l100) < (S32(4)): 
            dsp.rec105_perm[l100] = 0.0
            l100 = (l100) + (S32(1))
        var l101 = S32(0)
        while (l101) < (S32(4)): 
            dsp.rec104_perm[l101] = 0.0
            l101 = (l101) + (S32(1))
        var l102 = S32(0)
        while (l102) < (S32(4)): 
            dsp.rec110_perm[l102] = 0.0
            l102 = (l102) + (S32(1))
        var l103 = S32(0)
        while (l103) < (S32(4)): 
            dsp.rec109_perm[l103] = 0.0
            l103 = (l103) + (S32(1))
        var l104 = S32(0)
        while (l104) < (S32(4)): 
            dsp.rec108_perm[l104] = 0.0
            l104 = (l104) + (S32(1))
        var l105 = S32(0)
        while (l105) < (S32(4)): 
            dsp.rec107_perm[l105] = 0.0
            l105 = (l105) + (S32(1))
        var l106 = S32(0)
        while (l106) < (S32(4)): 
            dsp.rec106_perm[l106] = 0.0
            l106 = (l106) + (S32(1))
        var l107 = S32(0)
        while (l107) < (S32(4)): 
            dsp.rec116_perm[l107] = 0.0
            l107 = (l107) + (S32(1))
        var l108 = S32(0)
        while (l108) < (S32(4)): 
            dsp.rec115_perm[l108] = 0.0
            l108 = (l108) + (S32(1))
        var l109 = S32(0)
        while (l109) < (S32(4)): 
            dsp.yec12_perm[l109] = 0.0
            l109 = (l109) + (S32(1))
        var l110 = S32(0)
        while (l110) < (S32(4)): 
            dsp.rec114_perm[l110] = 0.0
            l110 = (l110) + (S32(1))
        var l111 = S32(0)
        while (l111) < (S32(4)): 
            dsp.rec113_perm[l111] = 0.0
            l111 = (l111) + (S32(1))
        var l112 = S32(0)
        while (l112) < (S32(4)): 
            dsp.rec112_perm[l112] = 0.0
            l112 = (l112) + (S32(1))
        var l113 = S32(0)
        while (l113) < (S32(4)): 
            dsp.rec111_perm[l113] = 0.0
            l113 = (l113) + (S32(1))
        var l114 = S32(0)
        while (l114) < (S32(4)): 
            dsp.rec121_perm[l114] = 0.0
            l114 = (l114) + (S32(1))
        var l115 = S32(0)
        while (l115) < (S32(4)): 
            dsp.rec120_perm[l115] = 0.0
            l115 = (l115) + (S32(1))
        var l116 = S32(0)
        while (l116) < (S32(4)): 
            dsp.yec13_perm[l116] = 0.0
            l116 = (l116) + (S32(1))
        var l117 = S32(0)
        while (l117) < (S32(4)): 
            dsp.rec119_perm[l117] = 0.0
            l117 = (l117) + (S32(1))
        var l118 = S32(0)
        while (l118) < (S32(4)): 
            dsp.rec118_perm[l118] = 0.0
            l118 = (l118) + (S32(1))
        var l119 = S32(0)
        while (l119) < (S32(4)): 
            dsp.rec117_perm[l119] = 0.0
            l119 = (l119) + (S32(1))
        var l120 = S32(0)
        while (l120) < (S32(4)): 
            dsp.rec125_perm[l120] = 0.0
            l120 = (l120) + (S32(1))
        var l121 = S32(0)
        while (l121) < (S32(4)): 
            dsp.rec124_perm[l121] = 0.0
            l121 = (l121) + (S32(1))
        var l122 = S32(0)
        while (l122) < (S32(4)): 
            dsp.yec14_perm[l122] = 0.0
            l122 = (l122) + (S32(1))
        var l123 = S32(0)
        while (l123) < (S32(4)): 
            dsp.rec123_perm[l123] = 0.0
            l123 = (l123) + (S32(1))
        var l124 = S32(0)
        while (l124) < (S32(4)): 
            dsp.rec122_perm[l124] = 0.0
            l124 = (l124) + (S32(1))
        var l125 = S32(0)
        while (l125) < (S32(4)): 
            dsp.rec127_perm[l125] = 0.0
            l125 = (l125) + (S32(1))
        var l126 = S32(0)
        while (l126) < (S32(4)): 
            dsp.rec126_perm[l126] = 0.0
            l126 = (l126) + (S32(1))
        var l127 = S32(0)
        while (l127) < (S32(4)): 
            dsp.rec132_perm[l127] = 0.0
            l127 = (l127) + (S32(1))
        var l128 = S32(0)
        while (l128) < (S32(4)): 
            dsp.rec131_perm[l128] = 0.0
            l128 = (l128) + (S32(1))
        var l129 = S32(0)
        while (l129) < (S32(4)): 
            dsp.rec130_perm[l129] = 0.0
            l129 = (l129) + (S32(1))
        var l130 = S32(0)
        while (l130) < (S32(4)): 
            dsp.rec129_perm[l130] = 0.0
            l130 = (l130) + (S32(1))
        var l131 = S32(0)
        while (l131) < (S32(4)): 
            dsp.rec128_perm[l131] = 0.0
            l131 = (l131) + (S32(1))
        var l132 = S32(0)
        while (l132) < (S32(4)): 
            dsp.rec138_perm[l132] = 0.0
            l132 = (l132) + (S32(1))
        var l133 = S32(0)
        while (l133) < (S32(4)): 
            dsp.rec137_perm[l133] = 0.0
            l133 = (l133) + (S32(1))
        var l134 = S32(0)
        while (l134) < (S32(4)): 
            dsp.yec15_perm[l134] = 0.0
            l134 = (l134) + (S32(1))
        var l135 = S32(0)
        while (l135) < (S32(4)): 
            dsp.rec136_perm[l135] = 0.0
            l135 = (l135) + (S32(1))
        var l136 = S32(0)
        while (l136) < (S32(4)): 
            dsp.rec135_perm[l136] = 0.0
            l136 = (l136) + (S32(1))
        var l137 = S32(0)
        while (l137) < (S32(4)): 
            dsp.rec134_perm[l137] = 0.0
            l137 = (l137) + (S32(1))
        var l138 = S32(0)
        while (l138) < (S32(4)): 
            dsp.rec133_perm[l138] = 0.0
            l138 = (l138) + (S32(1))
        var l139 = S32(0)
        while (l139) < (S32(4)): 
            dsp.rec143_perm[l139] = 0.0
            l139 = (l139) + (S32(1))
        var l140 = S32(0)
        while (l140) < (S32(4)): 
            dsp.rec142_perm[l140] = 0.0
            l140 = (l140) + (S32(1))
        var l141 = S32(0)
        while (l141) < (S32(4)): 
            dsp.yec16_perm[l141] = 0.0
            l141 = (l141) + (S32(1))
        var l142 = S32(0)
        while (l142) < (S32(4)): 
            dsp.rec141_perm[l142] = 0.0
            l142 = (l142) + (S32(1))
        var l143 = S32(0)
        while (l143) < (S32(4)): 
            dsp.rec140_perm[l143] = 0.0
            l143 = (l143) + (S32(1))
        var l144 = S32(0)
        while (l144) < (S32(4)): 
            dsp.rec139_perm[l144] = 0.0
            l144 = (l144) + (S32(1))
        var l145 = S32(0)
        while (l145) < (S32(4)): 
            dsp.rec147_perm[l145] = 0.0
            l145 = (l145) + (S32(1))
        var l146 = S32(0)
        while (l146) < (S32(4)): 
            dsp.rec146_perm[l146] = 0.0
            l146 = (l146) + (S32(1))
        var l147 = S32(0)
        while (l147) < (S32(4)): 
            dsp.yec17_perm[l147] = 0.0
            l147 = (l147) + (S32(1))
        var l148 = S32(0)
        while (l148) < (S32(4)): 
            dsp.rec145_perm[l148] = 0.0
            l148 = (l148) + (S32(1))
        var l149 = S32(0)
        while (l149) < (S32(4)): 
            dsp.rec144_perm[l149] = 0.0
            l149 = (l149) + (S32(1))
        var l150 = S32(0)
        while (l150) < (S32(4)): 
            dsp.rec149_perm[l150] = 0.0
            l150 = (l150) + (S32(1))
        var l151 = S32(0)
        while (l151) < (S32(4)): 
            dsp.rec148_perm[l151] = 0.0
            l151 = (l151) + (S32(1))
        var l152 = S32(0)
        while (l152) < (S32(4)): 
            dsp.rec154_perm[l152] = 0.0
            l152 = (l152) + (S32(1))
        var l153 = S32(0)
        while (l153) < (S32(4)): 
            dsp.rec153_perm[l153] = 0.0
            l153 = (l153) + (S32(1))
        var l154 = S32(0)
        while (l154) < (S32(4)): 
            dsp.rec152_perm[l154] = 0.0
            l154 = (l154) + (S32(1))
        var l155 = S32(0)
        while (l155) < (S32(4)): 
            dsp.rec151_perm[l155] = 0.0
            l155 = (l155) + (S32(1))
        var l156 = S32(0)
        while (l156) < (S32(4)): 
            dsp.rec150_perm[l156] = 0.0
            l156 = (l156) + (S32(1))
        var l157 = S32(0)
        while (l157) < (S32(4)): 
            dsp.rec160_perm[l157] = 0.0
            l157 = (l157) + (S32(1))
        var l158 = S32(0)
        while (l158) < (S32(4)): 
            dsp.rec159_perm[l158] = 0.0
            l158 = (l158) + (S32(1))
        var l159 = S32(0)
        while (l159) < (S32(4)): 
            dsp.yec18_perm[l159] = 0.0
            l159 = (l159) + (S32(1))
        var l160 = S32(0)
        while (l160) < (S32(4)): 
            dsp.rec158_perm[l160] = 0.0
            l160 = (l160) + (S32(1))
        var l161 = S32(0)
        while (l161) < (S32(4)): 
            dsp.rec157_perm[l161] = 0.0
            l161 = (l161) + (S32(1))
        var l162 = S32(0)
        while (l162) < (S32(4)): 
            dsp.rec156_perm[l162] = 0.0
            l162 = (l162) + (S32(1))
        var l163 = S32(0)
        while (l163) < (S32(4)): 
            dsp.rec155_perm[l163] = 0.0
            l163 = (l163) + (S32(1))
        var l164 = S32(0)
        while (l164) < (S32(4)): 
            dsp.rec165_perm[l164] = 0.0
            l164 = (l164) + (S32(1))
        var l165 = S32(0)
        while (l165) < (S32(4)): 
            dsp.rec164_perm[l165] = 0.0
            l165 = (l165) + (S32(1))
        var l166 = S32(0)
        while (l166) < (S32(4)): 
            dsp.yec19_perm[l166] = 0.0
            l166 = (l166) + (S32(1))
        var l167 = S32(0)
        while (l167) < (S32(4)): 
            dsp.rec163_perm[l167] = 0.0
            l167 = (l167) + (S32(1))
        var l168 = S32(0)
        while (l168) < (S32(4)): 
            dsp.rec162_perm[l168] = 0.0
            l168 = (l168) + (S32(1))
        var l169 = S32(0)
        while (l169) < (S32(4)): 
            dsp.rec161_perm[l169] = 0.0
            l169 = (l169) + (S32(1))
        var l170 = S32(0)
        while (l170) < (S32(4)): 
            dsp.rec169_perm[l170] = 0.0
            l170 = (l170) + (S32(1))
        var l171 = S32(0)
        while (l171) < (S32(4)): 
            dsp.rec168_perm[l171] = 0.0
            l171 = (l171) + (S32(1))
        var l172 = S32(0)
        while (l172) < (S32(4)): 
            dsp.yec20_perm[l172] = 0.0
            l172 = (l172) + (S32(1))
        var l173 = S32(0)
        while (l173) < (S32(4)): 
            dsp.rec167_perm[l173] = 0.0
            l173 = (l173) + (S32(1))
        var l174 = S32(0)
        while (l174) < (S32(4)): 
            dsp.rec166_perm[l174] = 0.0
            l174 = (l174) + (S32(1))
        var l175 = S32(0)
        while (l175) < (S32(4)): 
            dsp.rec171_perm[l175] = 0.0
            l175 = (l175) + (S32(1))
        var l176 = S32(0)
        while (l176) < (S32(4)): 
            dsp.rec170_perm[l176] = 0.0
            l176 = (l176) + (S32(1))
        var l177 = S32(0)
        while (l177) < (S32(4)): 
            dsp.rec176_perm[l177] = 0.0
            l177 = (l177) + (S32(1))
        var l178 = S32(0)
        while (l178) < (S32(4)): 
            dsp.rec175_perm[l178] = 0.0
            l178 = (l178) + (S32(1))
        var l179 = S32(0)
        while (l179) < (S32(4)): 
            dsp.rec174_perm[l179] = 0.0
            l179 = (l179) + (S32(1))
        var l180 = S32(0)
        while (l180) < (S32(4)): 
            dsp.rec173_perm[l180] = 0.0
            l180 = (l180) + (S32(1))
        var l181 = S32(0)
        while (l181) < (S32(4)): 
            dsp.rec172_perm[l181] = 0.0
            l181 = (l181) + (S32(1))
        var l182 = S32(0)
        while (l182) < (S32(4)): 
            dsp.rec182_perm[l182] = 0.0
            l182 = (l182) + (S32(1))
        var l183 = S32(0)
        while (l183) < (S32(4)): 
            dsp.rec181_perm[l183] = 0.0
            l183 = (l183) + (S32(1))
        var l184 = S32(0)
        while (l184) < (S32(4)): 
            dsp.yec21_perm[l184] = 0.0
            l184 = (l184) + (S32(1))
        var l185 = S32(0)
        while (l185) < (S32(4)): 
            dsp.rec180_perm[l185] = 0.0
            l185 = (l185) + (S32(1))
        var l186 = S32(0)
        while (l186) < (S32(4)): 
            dsp.rec179_perm[l186] = 0.0
            l186 = (l186) + (S32(1))
        var l187 = S32(0)
        while (l187) < (S32(4)): 
            dsp.rec178_perm[l187] = 0.0
            l187 = (l187) + (S32(1))
        var l188 = S32(0)
        while (l188) < (S32(4)): 
            dsp.rec177_perm[l188] = 0.0
            l188 = (l188) + (S32(1))
        var l189 = S32(0)
        while (l189) < (S32(4)): 
            dsp.rec187_perm[l189] = 0.0
            l189 = (l189) + (S32(1))
        var l190 = S32(0)
        while (l190) < (S32(4)): 
            dsp.rec186_perm[l190] = 0.0
            l190 = (l190) + (S32(1))
        var l191 = S32(0)
        while (l191) < (S32(4)): 
            dsp.yec22_perm[l191] = 0.0
            l191 = (l191) + (S32(1))
        var l192 = S32(0)
        while (l192) < (S32(4)): 
            dsp.rec185_perm[l192] = 0.0
            l192 = (l192) + (S32(1))
        var l193 = S32(0)
        while (l193) < (S32(4)): 
            dsp.rec184_perm[l193] = 0.0
            l193 = (l193) + (S32(1))
        var l194 = S32(0)
        while (l194) < (S32(4)): 
            dsp.rec183_perm[l194] = 0.0
            l194 = (l194) + (S32(1))
        var l195 = S32(0)
        while (l195) < (S32(4)): 
            dsp.rec191_perm[l195] = 0.0
            l195 = (l195) + (S32(1))
        var l196 = S32(0)
        while (l196) < (S32(4)): 
            dsp.rec190_perm[l196] = 0.0
            l196 = (l196) + (S32(1))
        var l197 = S32(0)
        while (l197) < (S32(4)): 
            dsp.yec23_perm[l197] = 0.0
            l197 = (l197) + (S32(1))
        var l198 = S32(0)
        while (l198) < (S32(4)): 
            dsp.rec189_perm[l198] = 0.0
            l198 = (l198) + (S32(1))
        var l199 = S32(0)
        while (l199) < (S32(4)): 
            dsp.rec188_perm[l199] = 0.0
            l199 = (l199) + (S32(1))
        var l200 = S32(0)
        while (l200) < (S32(4)): 
            dsp.rec193_perm[l200] = 0.0
            l200 = (l200) + (S32(1))
        var l201 = S32(0)
        while (l201) < (S32(4)): 
            dsp.rec192_perm[l201] = 0.0
            l201 = (l201) + (S32(1))
        var l202 = S32(0)
        while (l202) < (S32(4)): 
            dsp.rec198_perm[l202] = 0.0
            l202 = (l202) + (S32(1))
        var l203 = S32(0)
        while (l203) < (S32(4)): 
            dsp.rec197_perm[l203] = 0.0
            l203 = (l203) + (S32(1))
        var l204 = S32(0)
        while (l204) < (S32(4)): 
            dsp.rec196_perm[l204] = 0.0
            l204 = (l204) + (S32(1))
        var l205 = S32(0)
        while (l205) < (S32(4)): 
            dsp.rec195_perm[l205] = 0.0
            l205 = (l205) + (S32(1))
        var l206 = S32(0)
        while (l206) < (S32(4)): 
            dsp.rec194_perm[l206] = 0.0
            l206 = (l206) + (S32(1))
        var l207 = S32(0)
        while (l207) < (S32(4)): 
            dsp.rec204_perm[l207] = 0.0
            l207 = (l207) + (S32(1))
        var l208 = S32(0)
        while (l208) < (S32(4)): 
            dsp.rec203_perm[l208] = 0.0
            l208 = (l208) + (S32(1))
        var l209 = S32(0)
        while (l209) < (S32(4)): 
            dsp.yec24_perm[l209] = 0.0
            l209 = (l209) + (S32(1))
        var l210 = S32(0)
        while (l210) < (S32(4)): 
            dsp.rec202_perm[l210] = 0.0
            l210 = (l210) + (S32(1))
        var l211 = S32(0)
        while (l211) < (S32(4)): 
            dsp.rec201_perm[l211] = 0.0
            l211 = (l211) + (S32(1))
        var l212 = S32(0)
        while (l212) < (S32(4)): 
            dsp.rec200_perm[l212] = 0.0
            l212 = (l212) + (S32(1))
        var l213 = S32(0)
        while (l213) < (S32(4)): 
            dsp.rec199_perm[l213] = 0.0
            l213 = (l213) + (S32(1))
        var l214 = S32(0)
        while (l214) < (S32(4)): 
            dsp.rec209_perm[l214] = 0.0
            l214 = (l214) + (S32(1))
        var l215 = S32(0)
        while (l215) < (S32(4)): 
            dsp.rec208_perm[l215] = 0.0
            l215 = (l215) + (S32(1))
        var l216 = S32(0)
        while (l216) < (S32(4)): 
            dsp.yec25_perm[l216] = 0.0
            l216 = (l216) + (S32(1))
        var l217 = S32(0)
        while (l217) < (S32(4)): 
            dsp.rec207_perm[l217] = 0.0
            l217 = (l217) + (S32(1))
        var l218 = S32(0)
        while (l218) < (S32(4)): 
            dsp.rec206_perm[l218] = 0.0
            l218 = (l218) + (S32(1))
        var l219 = S32(0)
        while (l219) < (S32(4)): 
            dsp.rec205_perm[l219] = 0.0
            l219 = (l219) + (S32(1))
        var l220 = S32(0)
        while (l220) < (S32(4)): 
            dsp.rec213_perm[l220] = 0.0
            l220 = (l220) + (S32(1))
        var l221 = S32(0)
        while (l221) < (S32(4)): 
            dsp.rec212_perm[l221] = 0.0
            l221 = (l221) + (S32(1))
        var l222 = S32(0)
        while (l222) < (S32(4)): 
            dsp.yec26_perm[l222] = 0.0
            l222 = (l222) + (S32(1))
        var l223 = S32(0)
        while (l223) < (S32(4)): 
            dsp.rec211_perm[l223] = 0.0
            l223 = (l223) + (S32(1))
        var l224 = S32(0)
        while (l224) < (S32(4)): 
            dsp.rec210_perm[l224] = 0.0
            l224 = (l224) + (S32(1))
        var l225 = S32(0)
        while (l225) < (S32(4)): 
            dsp.rec215_perm[l225] = 0.0
            l225 = (l225) + (S32(1))
        var l226 = S32(0)
        while (l226) < (S32(4)): 
            dsp.rec214_perm[l226] = 0.0
            l226 = (l226) + (S32(1))
        var l227 = S32(0)
        while (l227) < (S32(4)): 
            dsp.rec220_perm[l227] = 0.0
            l227 = (l227) + (S32(1))
        var l228 = S32(0)
        while (l228) < (S32(4)): 
            dsp.rec219_perm[l228] = 0.0
            l228 = (l228) + (S32(1))
        var l229 = S32(0)
        while (l229) < (S32(4)): 
            dsp.rec218_perm[l229] = 0.0
            l229 = (l229) + (S32(1))
        var l230 = S32(0)
        while (l230) < (S32(4)): 
            dsp.rec217_perm[l230] = 0.0
            l230 = (l230) + (S32(1))
        var l231 = S32(0)
        while (l231) < (S32(4)): 
            dsp.rec216_perm[l231] = 0.0
            l231 = (l231) + (S32(1))
        var l232 = S32(0)
        while (l232) < (S32(4)): 
            dsp.rec226_perm[l232] = 0.0
            l232 = (l232) + (S32(1))
        var l233 = S32(0)
        while (l233) < (S32(4)): 
            dsp.rec225_perm[l233] = 0.0
            l233 = (l233) + (S32(1))
        var l234 = S32(0)
        while (l234) < (S32(4)): 
            dsp.yec27_perm[l234] = 0.0
            l234 = (l234) + (S32(1))
        var l235 = S32(0)
        while (l235) < (S32(4)): 
            dsp.rec224_perm[l235] = 0.0
            l235 = (l235) + (S32(1))
        var l236 = S32(0)
        while (l236) < (S32(4)): 
            dsp.rec223_perm[l236] = 0.0
            l236 = (l236) + (S32(1))
        var l237 = S32(0)
        while (l237) < (S32(4)): 
            dsp.rec222_perm[l237] = 0.0
            l237 = (l237) + (S32(1))
        var l238 = S32(0)
        while (l238) < (S32(4)): 
            dsp.rec221_perm[l238] = 0.0
            l238 = (l238) + (S32(1))
        var l239 = S32(0)
        while (l239) < (S32(4)): 
            dsp.rec231_perm[l239] = 0.0
            l239 = (l239) + (S32(1))
        var l240 = S32(0)
        while (l240) < (S32(4)): 
            dsp.rec230_perm[l240] = 0.0
            l240 = (l240) + (S32(1))
        var l241 = S32(0)
        while (l241) < (S32(4)): 
            dsp.yec28_perm[l241] = 0.0
            l241 = (l241) + (S32(1))
        var l242 = S32(0)
        while (l242) < (S32(4)): 
            dsp.rec229_perm[l242] = 0.0
            l242 = (l242) + (S32(1))
        var l243 = S32(0)
        while (l243) < (S32(4)): 
            dsp.rec228_perm[l243] = 0.0
            l243 = (l243) + (S32(1))
        var l244 = S32(0)
        while (l244) < (S32(4)): 
            dsp.rec227_perm[l244] = 0.0
            l244 = (l244) + (S32(1))
        var l245 = S32(0)
        while (l245) < (S32(4)): 
            dsp.rec235_perm[l245] = 0.0
            l245 = (l245) + (S32(1))
        var l246 = S32(0)
        while (l246) < (S32(4)): 
            dsp.rec234_perm[l246] = 0.0
            l246 = (l246) + (S32(1))
        var l247 = S32(0)
        while (l247) < (S32(4)): 
            dsp.yec29_perm[l247] = 0.0
            l247 = (l247) + (S32(1))
        var l248 = S32(0)
        while (l248) < (S32(4)): 
            dsp.rec233_perm[l248] = 0.0
            l248 = (l248) + (S32(1))
        var l249 = S32(0)
        while (l249) < (S32(4)): 
            dsp.rec232_perm[l249] = 0.0
            l249 = (l249) + (S32(1))
        var l250 = S32(0)
        while (l250) < (S32(4)): 
            dsp.rec237_perm[l250] = 0.0
            l250 = (l250) + (S32(1))
        var l251 = S32(0)
        while (l251) < (S32(4)): 
            dsp.rec236_perm[l251] = 0.0
            l251 = (l251) + (S32(1))
        var l252 = S32(0)
        while (l252) < (S32(4)): 
            dsp.rec242_perm[l252] = 0.0
            l252 = (l252) + (S32(1))
        var l253 = S32(0)
        while (l253) < (S32(4)): 
            dsp.rec241_perm[l253] = 0.0
            l253 = (l253) + (S32(1))
        var l254 = S32(0)
        while (l254) < (S32(4)): 
            dsp.rec240_perm[l254] = 0.0
            l254 = (l254) + (S32(1))
        var l255 = S32(0)
        while (l255) < (S32(4)): 
            dsp.rec239_perm[l255] = 0.0
            l255 = (l255) + (S32(1))
        var l256 = S32(0)
        while (l256) < (S32(4)): 
            dsp.rec238_perm[l256] = 0.0
            l256 = (l256) + (S32(1))
        var l257 = S32(0)
        while (l257) < (S32(4)): 
            dsp.rec248_perm[l257] = 0.0
            l257 = (l257) + (S32(1))
        var l258 = S32(0)
        while (l258) < (S32(4)): 
            dsp.rec247_perm[l258] = 0.0
            l258 = (l258) + (S32(1))
        var l259 = S32(0)
        while (l259) < (S32(4)): 
            dsp.yec30_perm[l259] = 0.0
            l259 = (l259) + (S32(1))
        var l260 = S32(0)
        while (l260) < (S32(4)): 
            dsp.rec246_perm[l260] = 0.0
            l260 = (l260) + (S32(1))
        var l261 = S32(0)
        while (l261) < (S32(4)): 
            dsp.rec245_perm[l261] = 0.0
            l261 = (l261) + (S32(1))
        var l262 = S32(0)
        while (l262) < (S32(4)): 
            dsp.rec244_perm[l262] = 0.0
            l262 = (l262) + (S32(1))
        var l263 = S32(0)
        while (l263) < (S32(4)): 
            dsp.rec243_perm[l263] = 0.0
            l263 = (l263) + (S32(1))
        var l264 = S32(0)
        while (l264) < (S32(4)): 
            dsp.rec253_perm[l264] = 0.0
            l264 = (l264) + (S32(1))
        var l265 = S32(0)
        while (l265) < (S32(4)): 
            dsp.rec252_perm[l265] = 0.0
            l265 = (l265) + (S32(1))
        var l266 = S32(0)
        while (l266) < (S32(4)): 
            dsp.yec31_perm[l266] = 0.0
            l266 = (l266) + (S32(1))
        var l267 = S32(0)
        while (l267) < (S32(4)): 
            dsp.rec251_perm[l267] = 0.0
            l267 = (l267) + (S32(1))
        var l268 = S32(0)
        while (l268) < (S32(4)): 
            dsp.rec250_perm[l268] = 0.0
            l268 = (l268) + (S32(1))
        var l269 = S32(0)
        while (l269) < (S32(4)): 
            dsp.rec249_perm[l269] = 0.0
            l269 = (l269) + (S32(1))
        var l270 = S32(0)
        while (l270) < (S32(4)): 
            dsp.rec257_perm[l270] = 0.0
            l270 = (l270) + (S32(1))
        var l271 = S32(0)
        while (l271) < (S32(4)): 
            dsp.rec256_perm[l271] = 0.0
            l271 = (l271) + (S32(1))
        var l272 = S32(0)
        while (l272) < (S32(4)): 
            dsp.yec32_perm[l272] = 0.0
            l272 = (l272) + (S32(1))
        var l273 = S32(0)
        while (l273) < (S32(4)): 
            dsp.rec255_perm[l273] = 0.0
            l273 = (l273) + (S32(1))
        var l274 = S32(0)
        while (l274) < (S32(4)): 
            dsp.rec254_perm[l274] = 0.0
            l274 = (l274) + (S32(1))
        var l275 = S32(0)
        while (l275) < (S32(4)): 
            dsp.rec259_perm[l275] = 0.0
            l275 = (l275) + (S32(1))
        var l276 = S32(0)
        while (l276) < (S32(4)): 
            dsp.rec258_perm[l276] = 0.0
            l276 = (l276) + (S32(1))
        var l277 = S32(0)
        while (l277) < (S32(4)): 
            dsp.rec264_perm[l277] = 0.0
            l277 = (l277) + (S32(1))
        var l278 = S32(0)
        while (l278) < (S32(4)): 
            dsp.rec263_perm[l278] = 0.0
            l278 = (l278) + (S32(1))
        var l279 = S32(0)
        while (l279) < (S32(4)): 
            dsp.rec262_perm[l279] = 0.0
            l279 = (l279) + (S32(1))
        var l280 = S32(0)
        while (l280) < (S32(4)): 
            dsp.rec261_perm[l280] = 0.0
            l280 = (l280) + (S32(1))
        var l281 = S32(0)
        while (l281) < (S32(4)): 
            dsp.rec260_perm[l281] = 0.0
            l281 = (l281) + (S32(1))
        var l282 = S32(0)
        while (l282) < (S32(4)): 
            dsp.rec270_perm[l282] = 0.0
            l282 = (l282) + (S32(1))
        var l283 = S32(0)
        while (l283) < (S32(4)): 
            dsp.rec269_perm[l283] = 0.0
            l283 = (l283) + (S32(1))
        var l284 = S32(0)
        while (l284) < (S32(4)): 
            dsp.yec33_perm[l284] = 0.0
            l284 = (l284) + (S32(1))
        var l285 = S32(0)
        while (l285) < (S32(4)): 
            dsp.rec268_perm[l285] = 0.0
            l285 = (l285) + (S32(1))
        var l286 = S32(0)
        while (l286) < (S32(4)): 
            dsp.rec267_perm[l286] = 0.0
            l286 = (l286) + (S32(1))
        var l287 = S32(0)
        while (l287) < (S32(4)): 
            dsp.rec266_perm[l287] = 0.0
            l287 = (l287) + (S32(1))
        var l288 = S32(0)
        while (l288) < (S32(4)): 
            dsp.rec265_perm[l288] = 0.0
            l288 = (l288) + (S32(1))
        var l289 = S32(0)
        while (l289) < (S32(4)): 
            dsp.rec275_perm[l289] = 0.0
            l289 = (l289) + (S32(1))
        var l290 = S32(0)
        while (l290) < (S32(4)): 
            dsp.rec274_perm[l290] = 0.0
            l290 = (l290) + (S32(1))
        var l291 = S32(0)
        while (l291) < (S32(4)): 
            dsp.yec34_perm[l291] = 0.0
            l291 = (l291) + (S32(1))
        var l292 = S32(0)
        while (l292) < (S32(4)): 
            dsp.rec273_perm[l292] = 0.0
            l292 = (l292) + (S32(1))
        var l293 = S32(0)
        while (l293) < (S32(4)): 
            dsp.rec272_perm[l293] = 0.0
            l293 = (l293) + (S32(1))
        var l294 = S32(0)
        while (l294) < (S32(4)): 
            dsp.rec271_perm[l294] = 0.0
            l294 = (l294) + (S32(1))
        var l295 = S32(0)
        while (l295) < (S32(4)): 
            dsp.rec279_perm[l295] = 0.0
            l295 = (l295) + (S32(1))
        var l296 = S32(0)
        while (l296) < (S32(4)): 
            dsp.rec278_perm[l296] = 0.0
            l296 = (l296) + (S32(1))
        var l297 = S32(0)
        while (l297) < (S32(4)): 
            dsp.yec35_perm[l297] = 0.0
            l297 = (l297) + (S32(1))
        var l298 = S32(0)
        while (l298) < (S32(4)): 
            dsp.rec277_perm[l298] = 0.0
            l298 = (l298) + (S32(1))
        var l299 = S32(0)
        while (l299) < (S32(4)): 
            dsp.rec276_perm[l299] = 0.0
            l299 = (l299) + (S32(1))
        var l300 = S32(0)
        while (l300) < (S32(4)): 
            dsp.rec281_perm[l300] = 0.0
            l300 = (l300) + (S32(1))
        var l301 = S32(0)
        while (l301) < (S32(4)): 
            dsp.rec280_perm[l301] = 0.0
            l301 = (l301) + (S32(1))
        var l302 = S32(0)
        while (l302) < (S32(4)): 
            dsp.rec286_perm[l302] = 0.0
            l302 = (l302) + (S32(1))
        var l303 = S32(0)
        while (l303) < (S32(4)): 
            dsp.rec285_perm[l303] = 0.0
            l303 = (l303) + (S32(1))
        var l304 = S32(0)
        while (l304) < (S32(4)): 
            dsp.rec284_perm[l304] = 0.0
            l304 = (l304) + (S32(1))
        var l305 = S32(0)
        while (l305) < (S32(4)): 
            dsp.rec283_perm[l305] = 0.0
            l305 = (l305) + (S32(1))
        var l306 = S32(0)
        while (l306) < (S32(4)): 
            dsp.rec282_perm[l306] = 0.0
            l306 = (l306) + (S32(1))
        var l307 = S32(0)
        while (l307) < (S32(4)): 
            dsp.rec292_perm[l307] = 0.0
            l307 = (l307) + (S32(1))
        var l308 = S32(0)
        while (l308) < (S32(4)): 
            dsp.rec291_perm[l308] = 0.0
            l308 = (l308) + (S32(1))
        var l309 = S32(0)
        while (l309) < (S32(4)): 
            dsp.yec36_perm[l309] = 0.0
            l309 = (l309) + (S32(1))
        var l310 = S32(0)
        while (l310) < (S32(4)): 
            dsp.rec290_perm[l310] = 0.0
            l310 = (l310) + (S32(1))
        var l311 = S32(0)
        while (l311) < (S32(4)): 
            dsp.rec289_perm[l311] = 0.0
            l311 = (l311) + (S32(1))
        var l312 = S32(0)
        while (l312) < (S32(4)): 
            dsp.rec288_perm[l312] = 0.0
            l312 = (l312) + (S32(1))
        var l313 = S32(0)
        while (l313) < (S32(4)): 
            dsp.rec287_perm[l313] = 0.0
            l313 = (l313) + (S32(1))
        var l314 = S32(0)
        while (l314) < (S32(4)): 
            dsp.rec297_perm[l314] = 0.0
            l314 = (l314) + (S32(1))
        var l315 = S32(0)
        while (l315) < (S32(4)): 
            dsp.rec296_perm[l315] = 0.0
            l315 = (l315) + (S32(1))
        var l316 = S32(0)
        while (l316) < (S32(4)): 
            dsp.yec37_perm[l316] = 0.0
            l316 = (l316) + (S32(1))
        var l317 = S32(0)
        while (l317) < (S32(4)): 
            dsp.rec295_perm[l317] = 0.0
            l317 = (l317) + (S32(1))
        var l318 = S32(0)
        while (l318) < (S32(4)): 
            dsp.rec294_perm[l318] = 0.0
            l318 = (l318) + (S32(1))
        var l319 = S32(0)
        while (l319) < (S32(4)): 
            dsp.rec293_perm[l319] = 0.0
            l319 = (l319) + (S32(1))
        var l320 = S32(0)
        while (l320) < (S32(4)): 
            dsp.rec301_perm[l320] = 0.0
            l320 = (l320) + (S32(1))
        var l321 = S32(0)
        while (l321) < (S32(4)): 
            dsp.rec300_perm[l321] = 0.0
            l321 = (l321) + (S32(1))
        var l322 = S32(0)
        while (l322) < (S32(4)): 
            dsp.yec38_perm[l322] = 0.0
            l322 = (l322) + (S32(1))
        var l323 = S32(0)
        while (l323) < (S32(4)): 
            dsp.rec299_perm[l323] = 0.0
            l323 = (l323) + (S32(1))
        var l324 = S32(0)
        while (l324) < (S32(4)): 
            dsp.rec298_perm[l324] = 0.0
            l324 = (l324) + (S32(1))
        var l325 = S32(0)
        while (l325) < (S32(4)): 
            dsp.rec303_perm[l325] = 0.0
            l325 = (l325) + (S32(1))
        var l326 = S32(0)
        while (l326) < (S32(4)): 
            dsp.rec302_perm[l326] = 0.0
            l326 = (l326) + (S32(1))
        var l327 = S32(0)
        while (l327) < (S32(4)): 
            dsp.rec308_perm[l327] = 0.0
            l327 = (l327) + (S32(1))
        var l328 = S32(0)
        while (l328) < (S32(4)): 
            dsp.rec307_perm[l328] = 0.0
            l328 = (l328) + (S32(1))
        var l329 = S32(0)
        while (l329) < (S32(4)): 
            dsp.rec306_perm[l329] = 0.0
            l329 = (l329) + (S32(1))
        var l330 = S32(0)
        while (l330) < (S32(4)): 
            dsp.rec305_perm[l330] = 0.0
            l330 = (l330) + (S32(1))
        var l331 = S32(0)
        while (l331) < (S32(4)): 
            dsp.rec304_perm[l331] = 0.0
            l331 = (l331) + (S32(1))
        var l332 = S32(0)
        while (l332) < (S32(4)): 
            dsp.rec314_perm[l332] = 0.0
            l332 = (l332) + (S32(1))
        var l333 = S32(0)
        while (l333) < (S32(4)): 
            dsp.rec313_perm[l333] = 0.0
            l333 = (l333) + (S32(1))
        var l334 = S32(0)
        while (l334) < (S32(4)): 
            dsp.yec39_perm[l334] = 0.0
            l334 = (l334) + (S32(1))
        var l335 = S32(0)
        while (l335) < (S32(4)): 
            dsp.rec312_perm[l335] = 0.0
            l335 = (l335) + (S32(1))
        var l336 = S32(0)
        while (l336) < (S32(4)): 
            dsp.rec311_perm[l336] = 0.0
            l336 = (l336) + (S32(1))
        var l337 = S32(0)
        while (l337) < (S32(4)): 
            dsp.rec310_perm[l337] = 0.0
            l337 = (l337) + (S32(1))
        var l338 = S32(0)
        while (l338) < (S32(4)): 
            dsp.rec309_perm[l338] = 0.0
            l338 = (l338) + (S32(1))
        var l339 = S32(0)
        while (l339) < (S32(4)): 
            dsp.rec319_perm[l339] = 0.0
            l339 = (l339) + (S32(1))
        var l340 = S32(0)
        while (l340) < (S32(4)): 
            dsp.rec318_perm[l340] = 0.0
            l340 = (l340) + (S32(1))
        var l341 = S32(0)
        while (l341) < (S32(4)): 
            dsp.yec40_perm[l341] = 0.0
            l341 = (l341) + (S32(1))
        var l342 = S32(0)
        while (l342) < (S32(4)): 
            dsp.rec317_perm[l342] = 0.0
            l342 = (l342) + (S32(1))
        var l343 = S32(0)
        while (l343) < (S32(4)): 
            dsp.rec316_perm[l343] = 0.0
            l343 = (l343) + (S32(1))
        var l344 = S32(0)
        while (l344) < (S32(4)): 
            dsp.rec315_perm[l344] = 0.0
            l344 = (l344) + (S32(1))
        var l345 = S32(0)
        while (l345) < (S32(4)): 
            dsp.rec323_perm[l345] = 0.0
            l345 = (l345) + (S32(1))
        var l346 = S32(0)
        while (l346) < (S32(4)): 
            dsp.rec322_perm[l346] = 0.0
            l346 = (l346) + (S32(1))
        var l347 = S32(0)
        while (l347) < (S32(4)): 
            dsp.yec41_perm[l347] = 0.0
            l347 = (l347) + (S32(1))
        var l348 = S32(0)
        while (l348) < (S32(4)): 
            dsp.rec321_perm[l348] = 0.0
            l348 = (l348) + (S32(1))
        var l349 = S32(0)
        while (l349) < (S32(4)): 
            dsp.rec320_perm[l349] = 0.0
            l349 = (l349) + (S32(1))
        var l350 = S32(0)
        while (l350) < (S32(4)): 
            dsp.rec325_perm[l350] = 0.0
            l350 = (l350) + (S32(1))
        var l351 = S32(0)
        while (l351) < (S32(4)): 
            dsp.rec324_perm[l351] = 0.0
            l351 = (l351) + (S32(1))
        var l352 = S32(0)
        while (l352) < (S32(4)): 
            dsp.rec330_perm[l352] = 0.0
            l352 = (l352) + (S32(1))
        var l353 = S32(0)
        while (l353) < (S32(4)): 
            dsp.rec329_perm[l353] = 0.0
            l353 = (l353) + (S32(1))
        var l354 = S32(0)
        while (l354) < (S32(4)): 
            dsp.rec328_perm[l354] = 0.0
            l354 = (l354) + (S32(1))
        var l355 = S32(0)
        while (l355) < (S32(4)): 
            dsp.rec327_perm[l355] = 0.0
            l355 = (l355) + (S32(1))
        var l356 = S32(0)
        while (l356) < (S32(4)): 
            dsp.rec326_perm[l356] = 0.0
            l356 = (l356) + (S32(1))
        var l357 = S32(0)
        while (l357) < (S32(4)): 
            dsp.rec336_perm[l357] = 0.0
            l357 = (l357) + (S32(1))
        var l358 = S32(0)
        while (l358) < (S32(4)): 
            dsp.rec335_perm[l358] = 0.0
            l358 = (l358) + (S32(1))
        var l359 = S32(0)
        while (l359) < (S32(4)): 
            dsp.yec42_perm[l359] = 0.0
            l359 = (l359) + (S32(1))
        var l360 = S32(0)
        while (l360) < (S32(4)): 
            dsp.rec334_perm[l360] = 0.0
            l360 = (l360) + (S32(1))
        var l361 = S32(0)
        while (l361) < (S32(4)): 
            dsp.rec333_perm[l361] = 0.0
            l361 = (l361) + (S32(1))
        var l362 = S32(0)
        while (l362) < (S32(4)): 
            dsp.rec332_perm[l362] = 0.0
            l362 = (l362) + (S32(1))
        var l363 = S32(0)
        while (l363) < (S32(4)): 
            dsp.rec331_perm[l363] = 0.0
            l363 = (l363) + (S32(1))
        var l364 = S32(0)
        while (l364) < (S32(4)): 
            dsp.rec341_perm[l364] = 0.0
            l364 = (l364) + (S32(1))
        var l365 = S32(0)
        while (l365) < (S32(4)): 
            dsp.rec340_perm[l365] = 0.0
            l365 = (l365) + (S32(1))
        var l366 = S32(0)
        while (l366) < (S32(4)): 
            dsp.yec43_perm[l366] = 0.0
            l366 = (l366) + (S32(1))
        var l367 = S32(0)
        while (l367) < (S32(4)): 
            dsp.rec339_perm[l367] = 0.0
            l367 = (l367) + (S32(1))
        var l368 = S32(0)
        while (l368) < (S32(4)): 
            dsp.rec338_perm[l368] = 0.0
            l368 = (l368) + (S32(1))
        var l369 = S32(0)
        while (l369) < (S32(4)): 
            dsp.rec337_perm[l369] = 0.0
            l369 = (l369) + (S32(1))
        var l370 = S32(0)
        while (l370) < (S32(4)): 
            dsp.rec345_perm[l370] = 0.0
            l370 = (l370) + (S32(1))
        var l371 = S32(0)
        while (l371) < (S32(4)): 
            dsp.rec344_perm[l371] = 0.0
            l371 = (l371) + (S32(1))
        var l372 = S32(0)
        while (l372) < (S32(4)): 
            dsp.yec44_perm[l372] = 0.0
            l372 = (l372) + (S32(1))
        var l373 = S32(0)
        while (l373) < (S32(4)): 
            dsp.rec343_perm[l373] = 0.0
            l373 = (l373) + (S32(1))
        var l374 = S32(0)
        while (l374) < (S32(4)): 
            dsp.rec342_perm[l374] = 0.0
            l374 = (l374) + (S32(1))
        var l375 = S32(0)
        while (l375) < (S32(4)): 
            dsp.rec347_perm[l375] = 0.0
            l375 = (l375) + (S32(1))
        var l376 = S32(0)
        while (l376) < (S32(4)): 
            dsp.rec346_perm[l376] = 0.0
            l376 = (l376) + (S32(1))
        var l377 = S32(0)
        while (l377) < (S32(4)): 
            dsp.rec352_perm[l377] = 0.0
            l377 = (l377) + (S32(1))
        var l378 = S32(0)
        while (l378) < (S32(4)): 
            dsp.rec351_perm[l378] = 0.0
            l378 = (l378) + (S32(1))
        var l379 = S32(0)
        while (l379) < (S32(4)): 
            dsp.rec350_perm[l379] = 0.0
            l379 = (l379) + (S32(1))
        var l380 = S32(0)
        while (l380) < (S32(4)): 
            dsp.rec349_perm[l380] = 0.0
            l380 = (l380) + (S32(1))
        var l381 = S32(0)
        while (l381) < (S32(4)): 
            dsp.rec348_perm[l381] = 0.0
            l381 = (l381) + (S32(1))
        var l382 = S32(0)
        while (l382) < (S32(4)): 
            dsp.rec358_perm[l382] = 0.0
            l382 = (l382) + (S32(1))
        var l383 = S32(0)
        while (l383) < (S32(4)): 
            dsp.rec357_perm[l383] = 0.0
            l383 = (l383) + (S32(1))
        var l384 = S32(0)
        while (l384) < (S32(4)): 
            dsp.yec45_perm[l384] = 0.0
            l384 = (l384) + (S32(1))
        var l385 = S32(0)
        while (l385) < (S32(4)): 
            dsp.rec356_perm[l385] = 0.0
            l385 = (l385) + (S32(1))
        var l386 = S32(0)
        while (l386) < (S32(4)): 
            dsp.rec355_perm[l386] = 0.0
            l386 = (l386) + (S32(1))
        var l387 = S32(0)
        while (l387) < (S32(4)): 
            dsp.rec354_perm[l387] = 0.0
            l387 = (l387) + (S32(1))
        var l388 = S32(0)
        while (l388) < (S32(4)): 
            dsp.rec353_perm[l388] = 0.0
            l388 = (l388) + (S32(1))
        var l389 = S32(0)
        while (l389) < (S32(4)): 
            dsp.rec363_perm[l389] = 0.0
            l389 = (l389) + (S32(1))
        var l390 = S32(0)
        while (l390) < (S32(4)): 
            dsp.rec362_perm[l390] = 0.0
            l390 = (l390) + (S32(1))
        var l391 = S32(0)
        while (l391) < (S32(4)): 
            dsp.yec46_perm[l391] = 0.0
            l391 = (l391) + (S32(1))
        var l392 = S32(0)
        while (l392) < (S32(4)): 
            dsp.rec361_perm[l392] = 0.0
            l392 = (l392) + (S32(1))
        var l393 = S32(0)
        while (l393) < (S32(4)): 
            dsp.rec360_perm[l393] = 0.0
            l393 = (l393) + (S32(1))
        var l394 = S32(0)
        while (l394) < (S32(4)): 
            dsp.rec359_perm[l394] = 0.0
            l394 = (l394) + (S32(1))
        var l395 = S32(0)
        while (l395) < (S32(4)): 
            dsp.rec367_perm[l395] = 0.0
            l395 = (l395) + (S32(1))
        var l396 = S32(0)
        while (l396) < (S32(4)): 
            dsp.rec366_perm[l396] = 0.0
            l396 = (l396) + (S32(1))
        var l397 = S32(0)
        while (l397) < (S32(4)): 
            dsp.yec47_perm[l397] = 0.0
            l397 = (l397) + (S32(1))
        var l398 = S32(0)
        while (l398) < (S32(4)): 
            dsp.rec365_perm[l398] = 0.0
            l398 = (l398) + (S32(1))
        var l399 = S32(0)
        while (l399) < (S32(4)): 
            dsp.rec364_perm[l399] = 0.0
            l399 = (l399) + (S32(1))
        var l400 = S32(0)
        while (l400) < (S32(4)): 
            dsp.rec369_perm[l400] = 0.0
            l400 = (l400) + (S32(1))
        var l401 = S32(0)
        while (l401) < (S32(4)): 
            dsp.rec368_perm[l401] = 0.0
            l401 = (l401) + (S32(1))
        var l402 = S32(0)
        while (l402) < (S32(4)): 
            dsp.vec0_perm[l402] = 0.0
            l402 = (l402) + (S32(1))
        var l403 = S32(0)
        while (l403) < (S32(4)): 
            dsp.vec1_perm[l403] = 0.0
            l403 = (l403) + (S32(1))
        var l404 = S32(0)
        while (l404) < (S32(16384)): 
            dsp.yec48[l404] = 0.0
            l404 = (l404) + (S32(1))
        dsp.yec48_idx = S32(0)
        dsp.yec48_idx_save = S32(0)
        var l405 = S32(0)
        while (l405) < (S32(4)): 
            dsp.rec0_perm[l405] = 0.0
            l405 = (l405) + (S32(1))
        var l406 = S32(0)
        while (l406) < (S32(4)): 
            dsp.vec2_perm[l406] = 0.0
            l406 = (l406) + (S32(1))
        var l407 = S32(0)
        while (l407) < (S32(16384)): 
            dsp.yec49[l407] = 0.0
            l407 = (l407) + (S32(1))
        dsp.yec49_idx = S32(0)
        dsp.yec49_idx_save = S32(0)
        var l408 = S32(0)
        while (l408) < (S32(4)): 
            dsp.rec1_perm[l408] = 0.0
            l408 = (l408) + (S32(1))
        var l409 = S32(0)
        while (l409) < (S32(16384)): 
            dsp.yec50[l409] = 0.0
            l409 = (l409) + (S32(1))
        dsp.yec50_idx = S32(0)
        dsp.yec50_idx_save = S32(0)
        var l410 = S32(0)
        while (l410) < (S32(4)): 
            dsp.rec2_perm[l410] = 0.0
            l410 = (l410) + (S32(1))
        var l411 = S32(0)
        while (l411) < (S32(16384)): 
            dsp.yec51[l411] = 0.0
            l411 = (l411) + (S32(1))
        dsp.yec51_idx = S32(0)
        dsp.yec51_idx_save = S32(0)
        var l412 = S32(0)
        while (l412) < (S32(4)): 
            dsp.rec3_perm[l412] = 0.0
            l412 = (l412) + (S32(1))
        var l413 = S32(0)
        while (l413) < (S32(16384)): 
            dsp.yec52[l413] = 0.0
            l413 = (l413) + (S32(1))
        dsp.yec52_idx = S32(0)
        dsp.yec52_idx_save = S32(0)
        var l414 = S32(0)
        while (l414) < (S32(4)): 
            dsp.rec4_perm[l414] = 0.0
            l414 = (l414) + (S32(1))
        var l415 = S32(0)
        while (l415) < (S32(16384)): 
            dsp.yec53[l415] = 0.0
            l415 = (l415) + (S32(1))
        dsp.yec53_idx = S32(0)
        dsp.yec53_idx_save = S32(0)
        var l416 = S32(0)
        while (l416) < (S32(4)): 
            dsp.rec5_perm[l416] = 0.0
            l416 = (l416) + (S32(1))
        var l417 = S32(0)
        while (l417) < (S32(16384)): 
            dsp.yec54[l417] = 0.0
            l417 = (l417) + (S32(1))
        dsp.yec54_idx = S32(0)
        dsp.yec54_idx_save = S32(0)
        var l418 = S32(0)
        while (l418) < (S32(4)): 
            dsp.rec6_perm[l418] = 0.0
            l418 = (l418) + (S32(1))
        var l419 = S32(0)
        while (l419) < (S32(16384)): 
            dsp.yec55[l419] = 0.0
            l419 = (l419) + (S32(1))
        dsp.yec55_idx = S32(0)
        dsp.yec55_idx_save = S32(0)
        var l420 = S32(0)
        while (l420) < (S32(4)): 
            dsp.rec7_perm[l420] = 0.0
            l420 = (l420) + (S32(1))
        var l421 = S32(0)
        while (l421) < (S32(16384)): 
            dsp.yec56[l421] = 0.0
            l421 = (l421) + (S32(1))
        dsp.yec56_idx = S32(0)
        dsp.yec56_idx_save = S32(0)
        var l422 = S32(0)
        while (l422) < (S32(4)): 
            dsp.rec8_perm[l422] = 0.0
            l422 = (l422) + (S32(1))
        var l423 = S32(0)
        while (l423) < (S32(16384)): 
            dsp.yec57[l423] = 0.0
            l423 = (l423) + (S32(1))
        dsp.yec57_idx = S32(0)
        dsp.yec57_idx_save = S32(0)
        var l424 = S32(0)
        while (l424) < (S32(4)): 
            dsp.rec9_perm[l424] = 0.0
            l424 = (l424) + (S32(1))
        var l425 = S32(0)
        while (l425) < (S32(16384)): 
            dsp.yec58[l425] = 0.0
            l425 = (l425) + (S32(1))
        dsp.yec58_idx = S32(0)
        dsp.yec58_idx_save = S32(0)
        var l426 = S32(0)
        while (l426) < (S32(4)): 
            dsp.rec10_perm[l426] = 0.0
            l426 = (l426) + (S32(1))
        var l427 = S32(0)
        while (l427) < (S32(16384)): 
            dsp.yec59[l427] = 0.0
            l427 = (l427) + (S32(1))
        dsp.yec59_idx = S32(0)
        dsp.yec59_idx_save = S32(0)
        var l428 = S32(0)
        while (l428) < (S32(4)): 
            dsp.rec11_perm[l428] = 0.0
            l428 = (l428) + (S32(1))
        var l429 = S32(0)
        while (l429) < (S32(16384)): 
            dsp.yec60[l429] = 0.0
            l429 = (l429) + (S32(1))
        dsp.yec60_idx = S32(0)
        dsp.yec60_idx_save = S32(0)
        var l430 = S32(0)
        while (l430) < (S32(4)): 
            dsp.rec12_perm[l430] = 0.0
            l430 = (l430) + (S32(1))
        var l431 = S32(0)
        while (l431) < (S32(16384)): 
            dsp.yec61[l431] = 0.0
            l431 = (l431) + (S32(1))
        dsp.yec61_idx = S32(0)
        dsp.yec61_idx_save = S32(0)
        var l432 = S32(0)
        while (l432) < (S32(4)): 
            dsp.rec13_perm[l432] = 0.0
            l432 = (l432) + (S32(1))
        var l433 = S32(0)
        while (l433) < (S32(16384)): 
            dsp.yec62[l433] = 0.0
            l433 = (l433) + (S32(1))
        dsp.yec62_idx = S32(0)
        dsp.yec62_idx_save = S32(0)
        var l434 = S32(0)
        while (l434) < (S32(4)): 
            dsp.rec14_perm[l434] = 0.0
            l434 = (l434) + (S32(1))
        var l435 = S32(0)
        while (l435) < (S32(16384)): 
            dsp.yec63[l435] = 0.0
            l435 = (l435) + (S32(1))
        dsp.yec63_idx = S32(0)
        dsp.yec63_idx_save = S32(0)
        var l436 = S32(0)
        while (l436) < (S32(4)): 
            dsp.rec15_perm[l436] = 0.0
            l436 = (l436) + (S32(1))

    @always_inline
    def instance_init(mut dsp, imm sample_rate: S32) -> None:
        dsp.instance_constants(sample_rate)
        dsp.instance_reset_user_interface()
        dsp.instance_clear()

    @always_inline
    def init(mut dsp, imm sample_rate: S32) -> None:
        dsp.class_init(sample_rate)
        dsp.instance_init(sample_rate)

    @always_inline
    def get_json(imm dsp) -> String:
        return "{\"name\": \"reverb_designer\",\"filename\": \"reverb_designer.dsp\",\"version\": \"2.87.10\",\"compile_options\": \"-a impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs\",\"library_list\": [\"/usr/local/share/faust/effect.lib\",\"/usr/local/share/faust/filter.lib\",\"/usr/local/share/faust/music.lib\",\"/usr/local/share/faust/math.lib\",\"/usr/local/share/faust/oscillator.lib\"],\"include_pathnames\": [\"/Users/manuelfarzini/Personal/dev/repo/faust/build/share/faust\",\"/Users/manuelfarzini/Personal/dev/repo/faust/build/bin//share/faust\",\"/usr/local/share/faust\",\"/usr/share/faust\",\"/Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/dsp\",\"/Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/dsp\"],\"size\": 2110916,\"inputs\": 2,\"outputs\": 2,\"meta\": [ { \"compile_options\": \"-a impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs\" },{ \"effect.lib/author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"effect.lib/copyright\": \"Julius O. Smith III\" },{ \"effect.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"effect.lib/exciter_author\": \"Priyanka Shekar (pshekar@ccrma.stanford.edu)\" },{ \"effect.lib/exciter_copyright\": \"Copyright (c) 2013 Priyanka Shekar\" },{ \"effect.lib/exciter_license\": \"MIT License (MIT)\" },{ \"effect.lib/exciter_name\": \"Harmonic Exciter\" },{ \"effect.lib/exciter_version\": \"1.0\" },{ \"effect.lib/license\": \"STK-4.3\" },{ \"effect.lib/name\": \"Faust Audio Effect Library\" },{ \"effect.lib/version\": \"1.33\" },{ \"filename\": \"reverb_designer.dsp\" },{ \"filter.lib/author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"filter.lib/copyright\": \"Julius O. Smith III\" },{ \"filter.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"filter.lib/license\": \"STK-4.3\" },{ \"filter.lib/name\": \"Faust Filter Library\" },{ \"filter.lib/reference\": \"https://ccrma.stanford.edu/~jos/filters/\" },{ \"filter.lib/version\": \"1.29\" },{ \"math.lib/author\": \"GRAME\" },{ \"math.lib/copyright\": \"GRAME\" },{ \"math.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"math.lib/license\": \"LGPL with exception\" },{ \"math.lib/name\": \"Math Library\" },{ \"math.lib/version\": \"1.0\" },{ \"music.lib/author\": \"GRAME\" },{ \"music.lib/copyright\": \"GRAME\" },{ \"music.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"music.lib/license\": \"LGPL with exception\" },{ \"music.lib/name\": \"Music Library\" },{ \"music.lib/version\": \"1.0\" },{ \"name\": \"reverb_designer\" },{ \"oscillator.lib/author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"oscillator.lib/copyright\": \"Julius O. Smith III\" },{ \"oscillator.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"oscillator.lib/license\": \"STK-4.3\" },{ \"oscillator.lib/name\": \"Faust Oscillator Library\" },{ \"oscillator.lib/version\": \"1.11\" }],\"ui\": [ {\"type\": \"vgroup\",\"label\": \"reverb_designer\",\"items\": [ {\"type\": \"vgroup\",\"label\": \"FEEDBACK DELAY NETWORK (FDN) REVERBERATOR, ORDER 16\",\"meta\": [{ \"tooltip\": \"See Faust\'s effect.lib for documentation and references\" }],\"items\": [ {\"type\": \"vgroup\",\"label\": \"Band Crossover Frequencies\",\"meta\": [{ \"1\": \"\" }],\"items\": [ {\"type\": \"hslider\",\"label\": \"Band 0 upper edge in Hz\",\"varname\": \"fHslider3\",\"shortname\": \"Band_0_upper_edge_in_Hz\",\"address\": \"/reverb_designer/FEEDBACK_DELAY_NETWORK__FDN__REVERBERATOR__ORDER_16/Band_Crossover_Frequencies/Band_0_upper_edge_in_Hz\",\"meta\": [{ \"0\": \"\" },{ \"scale\": \"log\" },{ \"tooltip\": \"Each delay-line signal is split into frequency-bands for separate decay-time control in each band\" },{ \"unit\": \"Hz\" }],\"init\": 500,\"min\": 100,\"max\": 10000,\"step\": 1},{\"type\": \"hslider\",\"label\": \"Band 1 upper edge in Hz\",\"varname\": \"fHslider2\",\"shortname\": \"Band_1_upper_edge_in_Hz\",\"address\": \"/reverb_designer/FEEDBACK_DELAY_NETWORK__FDN__REVERBERATOR__ORDER_16/Band_Crossover_Frequencies/Band_1_upper_edge_in_Hz\",\"meta\": [{ \"1\": \"\" },{ \"scale\": \"log\" },{ \"tooltip\": \"Each delay-line signal is split into frequency-bands for separate decay-time control in each band\" },{ \"unit\": \"Hz\" }],\"init\": 1000,\"min\": 100,\"max\": 10000,\"step\": 1},{\"type\": \"hslider\",\"label\": \"Band 2 upper edge in Hz\",\"varname\": \"fHslider1\",\"shortname\": \"Band_2_upper_edge_in_Hz\",\"address\": \"/reverb_designer/FEEDBACK_DELAY_NETWORK__FDN__REVERBERATOR__ORDER_16/Band_Crossover_Frequencies/Band_2_upper_edge_in_Hz\",\"meta\": [{ \"2\": \"\" },{ \"scale\": \"log\" },{ \"tooltip\": \"Each delay-line signal is split into frequency-bands for separate decay-time control in each band\" },{ \"unit\": \"Hz\" }],\"init\": 2000,\"min\": 100,\"max\": 10000,\"step\": 1},{\"type\": \"hslider\",\"label\": \"Band 3 upper edge in Hz\",\"varname\": \"fHslider0\",\"shortname\": \"Band_3_upper_edge_in_Hz\",\"address\": \"/reverb_designer/FEEDBACK_DELAY_NETWORK__FDN__REVERBERATOR__ORDER_16/Band_Crossover_Frequencies/Band_3_upper_edge_in_Hz\",\"meta\": [{ \"3\": \"\" },{ \"scale\": \"log\" },{ \"tooltip\": \"Each delay-line signal is split into frequency-bands for separate decay-time control in each band\" },{ \"unit\": \"Hz\" }],\"init\": 4000,\"min\": 100,\"max\": 10000,\"step\": 1}]},{\"type\": \"hgroup\",\"label\": \"Band Decay Times (T60)\",\"meta\": [{ \"2\": \"\" }],\"items\": [ {\"type\": \"vslider\",\"label\": \"0\",\"varname\": \"fVslider4\",\"shortname\": \"0\",\"address\": \"/reverb_designer/FEEDBACK_DELAY_NETWORK__FDN__REVERBERATOR__ORDER_16/Band_Decay_Times__T60_/0\",\"meta\": [{ \"0\": \"\" },{ \"scale\": \"log\" },{ \"tooltip\": \"T60 is the 60dB decay-time in seconds. For concert halls, an overall reverberation time (T60) near 1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each frequency band.  In real rooms, higher frequency bands generally decay faster due to absorption and scattering.\" },{ \"unit\": \"s\" }],\"init\": 8.4,\"min\": 0.1,\"max\": 100,\"step\": 0.1},{\"type\": \"vslider\",\"label\": \"1\",\"varname\": \"fVslider3\",\"shortname\": \"1\",\"address\": \"/reverb_designer/FEEDBACK_DELAY_NETWORK__FDN__REVERBERATOR__ORDER_16/Band_Decay_Times__T60_/1\",\"meta\": [{ \"1\": \"\" },{ \"scale\": \"log\" },{ \"tooltip\": \"T60 is the 60dB decay-time in seconds. For concert halls, an overall reverberation time (T60) near 1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each frequency band.  In real rooms, higher frequency bands generally decay faster due to absorption and scattering.\" },{ \"unit\": \"s\" }],\"init\": 6.5,\"min\": 0.1,\"max\": 100,\"step\": 0.1},{\"type\": \"vslider\",\"label\": \"2\",\"varname\": \"fVslider2\",\"shortname\": \"2\",\"address\": \"/reverb_designer/FEEDBACK_DELAY_NETWORK__FDN__REVERBERATOR__ORDER_16/Band_Decay_Times__T60_/2\",\"meta\": [{ \"2\": \"\" },{ \"scale\": \"log\" },{ \"tooltip\": \"T60 is the 60dB decay-time in seconds. For concert halls, an overall reverberation time (T60) near 1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each frequency band.  In real rooms, higher frequency bands generally decay faster due to absorption and scattering.\" },{ \"unit\": \"s\" }],\"init\": 5,\"min\": 0.1,\"max\": 100,\"step\": 0.1},{\"type\": \"vslider\",\"label\": \"3\",\"varname\": \"fVslider1\",\"shortname\": \"3\",\"address\": \"/reverb_designer/FEEDBACK_DELAY_NETWORK__FDN__REVERBERATOR__ORDER_16/Band_Decay_Times__T60_/3\",\"meta\": [{ \"3\": \"\" },{ \"scale\": \"log\" },{ \"tooltip\": \"T60 is the 60dB decay-time in seconds. For concert halls, an overall reverberation time (T60) near 1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each frequency band.  In real rooms, higher frequency bands generally decay faster due to absorption and scattering.\" },{ \"unit\": \"s\" }],\"init\": 3.8,\"min\": 0.1,\"max\": 100,\"step\": 0.1},{\"type\": \"vslider\",\"label\": \"4\",\"varname\": \"fVslider0\",\"shortname\": \"4\",\"address\": \"/reverb_designer/FEEDBACK_DELAY_NETWORK__FDN__REVERBERATOR__ORDER_16/Band_Decay_Times__T60_/4\",\"meta\": [{ \"4\": \"\" },{ \"scale\": \"log\" },{ \"tooltip\": \"T60 is the 60dB decay-time in seconds. For concert halls, an overall reverberation time (T60) near 1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each frequency band.  In real rooms, higher frequency bands generally decay faster due to absorption and scattering.\" },{ \"unit\": \"s\" }],\"init\": 2.7,\"min\": 0.1,\"max\": 100,\"step\": 0.1}]},{\"type\": \"vgroup\",\"label\": \"Room Dimensions\",\"meta\": [{ \"3\": \"\" }],\"items\": [ {\"type\": \"hslider\",\"label\": \"min acoustic ray length\",\"varname\": \"fHslider4\",\"shortname\": \"min_acoustic_ray_length\",\"address\": \"/reverb_designer/FEEDBACK_DELAY_NETWORK__FDN__REVERBERATOR__ORDER_16/Room_Dimensions/min_acoustic_ray_length\",\"meta\": [{ \"1\": \"\" },{ \"scale\": \"log\" },{ \"tooltip\": \"This length (in meters) determines the shortest delay-line used in the FDN reverberator.               Think of it as the shortest wall-to-wall separation in the room.\" },{ \"unit\": \"m\" }],\"init\": 46,\"min\": 0.1,\"max\": 63,\"step\": 0.1},{\"type\": \"hslider\",\"label\": \"max acoustic ray length\",\"varname\": \"fHslider5\",\"shortname\": \"max_acoustic_ray_length\",\"address\": \"/reverb_designer/FEEDBACK_DELAY_NETWORK__FDN__REVERBERATOR__ORDER_16/Room_Dimensions/max_acoustic_ray_length\",\"meta\": [{ \"2\": \"\" },{ \"scale\": \"log\" },{ \"tooltip\": \"This length (in meters) determines the longest delay-line used in the FDN reverberator.               Think of it as the largest wall-to-wall separation in the room.\" },{ \"unit\": \"m\" }],\"init\": 63,\"min\": 0.1,\"max\": 63,\"step\": 0.1}]},{\"type\": \"hgroup\",\"label\": \"Input Controls\",\"meta\": [{ \"4\": \"\" }],\"items\": [ {\"type\": \"vgroup\",\"label\": \"Input Config\",\"meta\": [{ \"1\": \"\" }],\"items\": [ {\"type\": \"checkbox\",\"label\": \"Mute Ext Inputs\",\"varname\": \"fCheckbox1\",\"shortname\": \"Mute_Ext_Inputs\",\"address\": \"/reverb_designer/FEEDBACK_DELAY_NETWORK__FDN__REVERBERATOR__ORDER_16/Input_Controls/Input_Config/Mute_Ext_Inputs\",\"meta\": [{ \"1\": \"\" },{ \"tooltip\": \"When this is checked, the stereo external audio inputs are disabled (good for hearing the impulse response or pink-noise response alone)\" }]},{\"type\": \"checkbox\",\"label\": \"Pink Noise\",\"varname\": \"fCheckbox0\",\"shortname\": \"Pink_Noise\",\"address\": \"/reverb_designer/FEEDBACK_DELAY_NETWORK__FDN__REVERBERATOR__ORDER_16/Input_Controls/Input_Config/Pink_Noise\",\"meta\": [{ \"2\": \"\" },{ \"tooltip\": \"Pink Noise (or 1/f noise) is Constant-Q Noise (useful for adjusting the EQ sections)\" }]}]},{\"type\": \"hgroup\",\"label\": \"Impulse Selection\",\"meta\": [{ \"2\": \"\" }],\"items\": [ {\"type\": \"button\",\"label\": \"Left\",\"varname\": \"fButton0\",\"shortname\": \"Left\",\"address\": \"/reverb_designer/FEEDBACK_DELAY_NETWORK__FDN__REVERBERATOR__ORDER_16/Input_Controls/Impulse_Selection/Left\",\"meta\": [{ \"1\": \"\" },{ \"tooltip\": \"Send impulse into LEFT channel\" }]},{\"type\": \"button\",\"label\": \"Center\",\"varname\": \"fButton1\",\"shortname\": \"Center\",\"address\": \"/reverb_designer/FEEDBACK_DELAY_NETWORK__FDN__REVERBERATOR__ORDER_16/Input_Controls/Impulse_Selection/Center\",\"meta\": [{ \"2\": \"\" },{ \"tooltip\": \"Send impulse into LEFT and RIGHT channels\" }]},{\"type\": \"button\",\"label\": \"Right\",\"varname\": \"fButton3\",\"shortname\": \"Right\",\"address\": \"/reverb_designer/FEEDBACK_DELAY_NETWORK__FDN__REVERBERATOR__ORDER_16/Input_Controls/Impulse_Selection/Right\",\"meta\": [{ \"3\": \"\" },{ \"tooltip\": \"Send impulse into RIGHT channel\" }]}]},{\"type\": \"vgroup\",\"label\": \"Reverb State\",\"meta\": [{ \"3\": \"\" }],\"items\": [ {\"type\": \"button\",\"label\": \"Quench\",\"varname\": \"fButton2\",\"shortname\": \"Quench\",\"address\": \"/reverb_designer/FEEDBACK_DELAY_NETWORK__FDN__REVERBERATOR__ORDER_16/Input_Controls/Reverb_State/Quench\",\"meta\": [{ \"1\": \"\" },{ \"tooltip\": \"Hold down \'Quench\' to clear the reverberator\" }]}]}]}]},{\"type\": \"hslider\",\"label\": \"Output Level (dB)\",\"varname\": \"fHslider6\",\"shortname\": \"Output_Level_dB\",\"address\": \"/reverb_designer/Output_Level__dB_\",\"meta\": [{ \"3\": \"\" },{ \"tooltip\": \"Output scale factor\" },{ \"unit\": \"dB\" }],\"init\": -40,\"min\": -70,\"max\": 20,\"step\": 0.1}]}]}"

    @always_inline
    def metadata(imm dsp, mut meta: Some[FaustMeta]) -> None:
        meta.declare("compile_options", "-a impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 4 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs")
        meta.declare("effect.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)")
        meta.declare("effect.lib/copyright", "Julius O. Smith III")
        meta.declare("effect.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.")
        meta.declare("effect.lib/exciter_author", "Priyanka Shekar (pshekar@ccrma.stanford.edu)")
        meta.declare("effect.lib/exciter_copyright", "Copyright (c) 2013 Priyanka Shekar")
        meta.declare("effect.lib/exciter_license", "MIT License (MIT)")
        meta.declare("effect.lib/exciter_name", "Harmonic Exciter")
        meta.declare("effect.lib/exciter_version", "1.0")
        meta.declare("effect.lib/license", "STK-4.3")
        meta.declare("effect.lib/name", "Faust Audio Effect Library")
        meta.declare("effect.lib/version", "1.33")
        meta.declare("filename", "reverb_designer.dsp")
        meta.declare("filter.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)")
        meta.declare("filter.lib/copyright", "Julius O. Smith III")
        meta.declare("filter.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.")
        meta.declare("filter.lib/license", "STK-4.3")
        meta.declare("filter.lib/name", "Faust Filter Library")
        meta.declare("filter.lib/reference", "https://ccrma.stanford.edu/~jos/filters/")
        meta.declare("filter.lib/version", "1.29")
        meta.declare("math.lib/author", "GRAME")
        meta.declare("math.lib/copyright", "GRAME")
        meta.declare("math.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.")
        meta.declare("math.lib/license", "LGPL with exception")
        meta.declare("math.lib/name", "Math Library")
        meta.declare("math.lib/version", "1.0")
        meta.declare("music.lib/author", "GRAME")
        meta.declare("music.lib/copyright", "GRAME")
        meta.declare("music.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.")
        meta.declare("music.lib/license", "LGPL with exception")
        meta.declare("music.lib/name", "Music Library")
        meta.declare("music.lib/version", "1.0")
        meta.declare("name", "reverb_designer")
        meta.declare("oscillator.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)")
        meta.declare("oscillator.lib/copyright", "Julius O. Smith III")
        meta.declare("oscillator.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.")
        meta.declare("oscillator.lib/license", "STK-4.3")
        meta.declare("oscillator.lib/name", "Faust Oscillator Library")
        meta.declare("oscillator.lib/version", "1.11")

    @always_inline
    def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None:
        ui.open_vertical_box("reverb_designer")
        ui.declare(dsp.null_val, "tooltip", "See Faust's effect.lib for documentation and references")
        ui.open_vertical_box("FEEDBACK DELAY NETWORK (FDN) REVERBERATOR, ORDER 16")
        ui.declare(dsp.null_val, "1", "")
        ui.open_vertical_box("Band Crossover Frequencies")
        ui.declare(dsp.hslider3, "0", "")
        ui.declare(dsp.hslider3, "scale", "log")
        ui.declare(dsp.hslider3, "tooltip", "Each delay-line signal is split into frequency-bands for separate decay-time control in each band")
        ui.declare(dsp.hslider3, "unit", "Hz")
        ui.add_horizontal_slider("Band 0 upper edge in Hz", dsp.hslider3, FaustFloat(500.0), FaustFloat(100.0), FaustFloat(10000.0), FaustFloat(1.0))
        ui.declare(dsp.hslider2, "1", "")
        ui.declare(dsp.hslider2, "scale", "log")
        ui.declare(dsp.hslider2, "tooltip", "Each delay-line signal is split into frequency-bands for separate decay-time control in each band")
        ui.declare(dsp.hslider2, "unit", "Hz")
        ui.add_horizontal_slider("Band 1 upper edge in Hz", dsp.hslider2, FaustFloat(1000.0), FaustFloat(100.0), FaustFloat(10000.0), FaustFloat(1.0))
        ui.declare(dsp.hslider1, "2", "")
        ui.declare(dsp.hslider1, "scale", "log")
        ui.declare(dsp.hslider1, "tooltip", "Each delay-line signal is split into frequency-bands for separate decay-time control in each band")
        ui.declare(dsp.hslider1, "unit", "Hz")
        ui.add_horizontal_slider("Band 2 upper edge in Hz", dsp.hslider1, FaustFloat(2000.0), FaustFloat(100.0), FaustFloat(10000.0), FaustFloat(1.0))
        ui.declare(dsp.hslider0, "3", "")
        ui.declare(dsp.hslider0, "scale", "log")
        ui.declare(dsp.hslider0, "tooltip", "Each delay-line signal is split into frequency-bands for separate decay-time control in each band")
        ui.declare(dsp.hslider0, "unit", "Hz")
        ui.add_horizontal_slider("Band 3 upper edge in Hz", dsp.hslider0, FaustFloat(4000.0), FaustFloat(100.0), FaustFloat(10000.0), FaustFloat(1.0))
        ui.close_box()
        ui.declare(dsp.null_val, "2", "")
        ui.open_horizontal_box("Band Decay Times (T60)")
        ui.declare(dsp.vslider4, "0", "")
        ui.declare(dsp.vslider4, "scale", "log")
        ui.declare(dsp.vslider4, "tooltip", "T60 is the 60dB decay-time in seconds. For concert halls, an overall reverberation time (T60) near 1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each frequency band.  In real rooms, higher frequency bands generally decay faster due to absorption and scattering.")
        ui.declare(dsp.vslider4, "unit", "s")
        ui.add_vertical_slider("0", dsp.vslider4, FaustFloat(8.4), FaustFloat(0.1), FaustFloat(100.0), FaustFloat(0.1))
        ui.declare(dsp.vslider3, "1", "")
        ui.declare(dsp.vslider3, "scale", "log")
        ui.declare(dsp.vslider3, "tooltip", "T60 is the 60dB decay-time in seconds. For concert halls, an overall reverberation time (T60) near 1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each frequency band.  In real rooms, higher frequency bands generally decay faster due to absorption and scattering.")
        ui.declare(dsp.vslider3, "unit", "s")
        ui.add_vertical_slider("1", dsp.vslider3, FaustFloat(6.5), FaustFloat(0.1), FaustFloat(100.0), FaustFloat(0.1))
        ui.declare(dsp.vslider2, "2", "")
        ui.declare(dsp.vslider2, "scale", "log")
        ui.declare(dsp.vslider2, "tooltip", "T60 is the 60dB decay-time in seconds. For concert halls, an overall reverberation time (T60) near 1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each frequency band.  In real rooms, higher frequency bands generally decay faster due to absorption and scattering.")
        ui.declare(dsp.vslider2, "unit", "s")
        ui.add_vertical_slider("2", dsp.vslider2, FaustFloat(5.0), FaustFloat(0.1), FaustFloat(100.0), FaustFloat(0.1))
        ui.declare(dsp.vslider1, "3", "")
        ui.declare(dsp.vslider1, "scale", "log")
        ui.declare(dsp.vslider1, "tooltip", "T60 is the 60dB decay-time in seconds. For concert halls, an overall reverberation time (T60) near 1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each frequency band.  In real rooms, higher frequency bands generally decay faster due to absorption and scattering.")
        ui.declare(dsp.vslider1, "unit", "s")
        ui.add_vertical_slider("3", dsp.vslider1, FaustFloat(3.8), FaustFloat(0.1), FaustFloat(100.0), FaustFloat(0.1))
        ui.declare(dsp.vslider0, "4", "")
        ui.declare(dsp.vslider0, "scale", "log")
        ui.declare(dsp.vslider0, "tooltip", "T60 is the 60dB decay-time in seconds. For concert halls, an overall reverberation time (T60) near 1.9 seconds is typical [Beranek 2004]. Here we may set T60 independently in each frequency band.  In real rooms, higher frequency bands generally decay faster due to absorption and scattering.")
        ui.declare(dsp.vslider0, "unit", "s")
        ui.add_vertical_slider("4", dsp.vslider0, FaustFloat(2.7), FaustFloat(0.1), FaustFloat(100.0), FaustFloat(0.1))
        ui.close_box()
        ui.declare(dsp.null_val, "3", "")
        ui.open_vertical_box("Room Dimensions")
        ui.declare(dsp.hslider4, "1", "")
        ui.declare(dsp.hslider4, "scale", "log")
        ui.declare(dsp.hslider4, "tooltip", "This length (in meters) determines the shortest delay-line used in the FDN reverberator.               Think of it as the shortest wall-to-wall separation in the room.")
        ui.declare(dsp.hslider4, "unit", "m")
        ui.add_horizontal_slider("min acoustic ray length", dsp.hslider4, FaustFloat(46.0), FaustFloat(0.1), FaustFloat(63.0), FaustFloat(0.1))
        ui.declare(dsp.hslider5, "2", "")
        ui.declare(dsp.hslider5, "scale", "log")
        ui.declare(dsp.hslider5, "tooltip", "This length (in meters) determines the longest delay-line used in the FDN reverberator.               Think of it as the largest wall-to-wall separation in the room.")
        ui.declare(dsp.hslider5, "unit", "m")
        ui.add_horizontal_slider("max acoustic ray length", dsp.hslider5, FaustFloat(63.0), FaustFloat(0.1), FaustFloat(63.0), FaustFloat(0.1))
        ui.close_box()
        ui.declare(dsp.null_val, "4", "")
        ui.open_horizontal_box("Input Controls")
        ui.declare(dsp.null_val, "1", "")
        ui.open_vertical_box("Input Config")
        ui.declare(dsp.checkbox1, "1", "")
        ui.declare(dsp.checkbox1, "tooltip", "When this is checked, the stereo external audio inputs are disabled (good for hearing the impulse response or pink-noise response alone)")
        ui.add_check_button("Mute Ext Inputs", dsp.checkbox1)
        ui.declare(dsp.checkbox0, "2", "")
        ui.declare(dsp.checkbox0, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise (useful for adjusting the EQ sections)")
        ui.add_check_button("Pink Noise", dsp.checkbox0)
        ui.close_box()
        ui.declare(dsp.null_val, "2", "")
        ui.open_horizontal_box("Impulse Selection")
        ui.declare(dsp.button0, "1", "")
        ui.declare(dsp.button0, "tooltip", "Send impulse into LEFT channel")
        ui.add_button("Left", dsp.button0)
        ui.declare(dsp.button1, "2", "")
        ui.declare(dsp.button1, "tooltip", "Send impulse into LEFT and RIGHT channels")
        ui.add_button("Center", dsp.button1)
        ui.declare(dsp.button3, "3", "")
        ui.declare(dsp.button3, "tooltip", "Send impulse into RIGHT channel")
        ui.add_button("Right", dsp.button3)
        ui.close_box()
        ui.declare(dsp.null_val, "3", "")
        ui.open_vertical_box("Reverb State")
        ui.declare(dsp.button2, "1", "")
        ui.declare(dsp.button2, "tooltip", "Hold down 'Quench' to clear the reverberator")
        ui.add_button("Quench", dsp.button2)
        ui.close_box()
        ui.close_box()
        ui.close_box()
        ui.declare(dsp.hslider6, "3", "")
        ui.declare(dsp.hslider6, "tooltip", "Output scale factor")
        ui.declare(dsp.hslider6, "unit", "dB")
        ui.add_horizontal_slider("Output Level (dB)", dsp.hslider6, FaustFloat(-40.0), FaustFloat(-70.0), FaustFloat(20.0), FaustFloat(0.1))
        ui.close_box()

    @always_inline
    def compute(mut dsp, var count: S32, var inputs: ImmStreams, var outputs: MutStreams) -> None:
        comptime assert dfaust == DType.float32, "Expected 32 bit float driver precision."
        comptime vsize = S32(simd_width_of[f32]())
        comptime hsize = S32(simd_width_of[f64]())
        comptime H = simd_width_of[f64]()
        var vindex = S32(0)
        var end = count - vsize
        var input0_ptr = inputs[unsafe_offset = S32(0)]
        var input1_ptr = inputs[unsafe_offset = S32(1)]
        var output0_ptr = outputs[unsafe_offset = S32(0)]
        var output1_ptr = outputs[unsafe_offset = S32(1)]
        var i_rec17_tmp = Arr[S32, 8](uninitialized=True)
        var i_rec17 = Ptr(to=i_rec17_tmp[S32(4)])
        var rec16_tmp = Arr[F64, 8](uninitialized=True)
        var rec16 = Ptr(to=rec16_tmp[S32(4)])
        var slow0 = tan((dsp.const1) * (F64(dsp.hslider0)))
        var slow1 = (1.0) / (slow0)
        var slow2 = (1.0) / ((slow1) + (1.0))
        var slow3 = (1.0) - (slow1)
        var rec22_tmp = Arr[F64, 8](uninitialized=True)
        var rec22 = Ptr(to=rec22_tmp[S32(4)])
        var slow4 = (((slow1) + (1.0000000000000004)) / (slow0)) + (1.0)
        var slow5 = (1.0) / (slow4)
        var slow6 = (((slow1) + (-1.0000000000000004)) / (slow0)) + (1.0)
        var slow7 = pow_unrolled[2](slow0)
        var slow8 = (2.0) * ((1.0) - ((1.0) / (slow7)))
        var rec21_tmp = Arr[F64, 8](uninitialized=True)
        var rec21 = Ptr(to=rec21_tmp[S32(4)])
        var slow9 = (1.0) / ((slow7) * (slow4))
        var slow10 = tan((dsp.const1) * (F64(dsp.hslider1)))
        var slow11 = (1.0) / (slow10)
        var slow12 = (slow11) + (1.0)
        var slow13 = (1.0) / (((slow12) / (slow10)) + (1.0))
        var slow14 = (1.0) - (slow11)
        var slow15 = (1.0) - ((slow14) / (slow10))
        var slow16 = pow_unrolled[2](slow10)
        var slow17 = (2.0) * ((1.0) - ((1.0) / (slow16)))
        var zec0 = Arr[F64, 4](uninitialized=True)
        var rec20_tmp = Arr[F64, 8](uninitialized=True)
        var rec20 = Ptr(to=rec20_tmp[S32(4)])
        var slow18 = tan((dsp.const1) * (F64(dsp.hslider2)))
        var slow19 = (1.0) / (slow18)
        var slow20 = (slow19) + (1.0)
        var slow21 = (1.0) / (((slow20) / (slow18)) + (1.0))
        var slow22 = (1.0) - (slow19)
        var slow23 = (1.0) - ((slow22) / (slow18))
        var slow24 = pow_unrolled[2](slow18)
        var slow25 = (2.0) * ((1.0) - ((1.0) / (slow24)))
        var zec1 = Arr[F64, 4](uninitialized=True)
        var rec19_tmp = Arr[F64, 8](uninitialized=True)
        var rec19 = Ptr(to=rec19_tmp[S32(4)])
        var slow26 = tan((dsp.const1) * (F64(dsp.hslider3)))
        var slow27 = (1.0) / (slow26)
        var slow28 = (slow27) + (1.0)
        var slow29 = (1.0) / (((slow28) / (slow26)) + (1.0))
        var slow30 = (1.0) - (slow27)
        var slow31 = (1.0) - ((slow30) / (slow26))
        var slow32 = pow_unrolled[2](slow26)
        var slow33 = (2.0) * ((1.0) - ((1.0) / (slow32)))
        var zec2 = Arr[F64, 4](uninitialized=True)
        var rec18_tmp = Arr[F64, 8](uninitialized=True)
        var rec18 = Ptr(to=rec18_tmp[S32(4)])
        var rec28_tmp = Arr[F64, 8](uninitialized=True)
        var rec28 = Ptr(to=rec28_tmp[S32(4)])
        var rec27_tmp = Arr[F64, 8](uninitialized=True)
        var rec27 = Ptr(to=rec27_tmp[S32(4)])
        var slow34 = (1.0) / (slow12)
        var yec0_tmp = Arr[F64, 8](uninitialized=True)
        var yec0 = Ptr(to=yec0_tmp[S32(4)])
        var rec26_tmp = Arr[F64, 8](uninitialized=True)
        var rec26 = Ptr(to=rec26_tmp[S32(4)])
        var slow35 = (((slow11) + (1.0000000000000004)) / (slow10)) + (1.0)
        var slow36 = (1.0) / (slow35)
        var slow37 = (((slow11) + (-1.0000000000000004)) / (slow10)) + (1.0)
        var rec25_tmp = Arr[F64, 8](uninitialized=True)
        var rec25 = Ptr(to=rec25_tmp[S32(4)])
        var slow38 = (1.0) / ((slow16) * (slow35))
        var zec3 = Arr[F64, 4](uninitialized=True)
        var rec24_tmp = Arr[F64, 8](uninitialized=True)
        var rec24 = Ptr(to=rec24_tmp[S32(4)])
        var zec4 = Arr[F64, 4](uninitialized=True)
        var rec23_tmp = Arr[F64, 8](uninitialized=True)
        var rec23 = Ptr(to=rec23_tmp[S32(4)])
        var rec33_tmp = Arr[F64, 8](uninitialized=True)
        var rec33 = Ptr(to=rec33_tmp[S32(4)])
        var rec32_tmp = Arr[F64, 8](uninitialized=True)
        var rec32 = Ptr(to=rec32_tmp[S32(4)])
        var slow39 = (1.0) / (slow20)
        var yec1_tmp = Arr[F64, 8](uninitialized=True)
        var yec1 = Ptr(to=yec1_tmp[S32(4)])
        var rec31_tmp = Arr[F64, 8](uninitialized=True)
        var rec31 = Ptr(to=rec31_tmp[S32(4)])
        var slow40 = (((slow19) + (1.0000000000000004)) / (slow18)) + (1.0)
        var slow41 = (1.0) / (slow40)
        var slow42 = (((slow19) + (-1.0000000000000004)) / (slow18)) + (1.0)
        var rec30_tmp = Arr[F64, 8](uninitialized=True)
        var rec30 = Ptr(to=rec30_tmp[S32(4)])
        var slow43 = (1.0) / ((slow24) * (slow40))
        var zec5 = Arr[F64, 4](uninitialized=True)
        var rec29_tmp = Arr[F64, 8](uninitialized=True)
        var rec29 = Ptr(to=rec29_tmp[S32(4)])
        var rec37_tmp = Arr[F64, 8](uninitialized=True)
        var rec37 = Ptr(to=rec37_tmp[S32(4)])
        var rec36_tmp = Arr[F64, 8](uninitialized=True)
        var rec36 = Ptr(to=rec36_tmp[S32(4)])
        var slow44 = (1.0) / (slow28)
        var yec2_tmp = Arr[F64, 8](uninitialized=True)
        var yec2 = Ptr(to=yec2_tmp[S32(4)])
        var rec35_tmp = Arr[F64, 8](uninitialized=True)
        var rec35 = Ptr(to=rec35_tmp[S32(4)])
        var slow45 = (1.0) / ((((slow27) + (1.0000000000000004)) / (slow26)) + (1.0))
        var slow46 = (((slow27) + (-1.0000000000000004)) / (slow26)) + (1.0)
        var rec34_tmp = Arr[F64, 8](uninitialized=True)
        var rec34 = Ptr(to=rec34_tmp[S32(4)])
        var rec39_tmp = Arr[F64, 8](uninitialized=True)
        var rec39 = Ptr(to=rec39_tmp[S32(4)])
        var rec38_tmp = Arr[F64, 8](uninitialized=True)
        var rec38 = Ptr(to=rec38_tmp[S32(4)])
        var rec44_tmp = Arr[F64, 8](uninitialized=True)
        var rec44 = Ptr(to=rec44_tmp[S32(4)])
        var rec43_tmp = Arr[F64, 8](uninitialized=True)
        var rec43 = Ptr(to=rec43_tmp[S32(4)])
        var zec6 = Arr[F64, 4](uninitialized=True)
        var rec42_tmp = Arr[F64, 8](uninitialized=True)
        var rec42 = Ptr(to=rec42_tmp[S32(4)])
        var zec7 = Arr[F64, 4](uninitialized=True)
        var rec41_tmp = Arr[F64, 8](uninitialized=True)
        var rec41 = Ptr(to=rec41_tmp[S32(4)])
        var zec8 = Arr[F64, 4](uninitialized=True)
        var rec40_tmp = Arr[F64, 8](uninitialized=True)
        var rec40 = Ptr(to=rec40_tmp[S32(4)])
        var rec50_tmp = Arr[F64, 8](uninitialized=True)
        var rec50 = Ptr(to=rec50_tmp[S32(4)])
        var rec49_tmp = Arr[F64, 8](uninitialized=True)
        var rec49 = Ptr(to=rec49_tmp[S32(4)])
        var yec3_tmp = Arr[F64, 8](uninitialized=True)
        var yec3 = Ptr(to=yec3_tmp[S32(4)])
        var rec48_tmp = Arr[F64, 8](uninitialized=True)
        var rec48 = Ptr(to=rec48_tmp[S32(4)])
        var rec47_tmp = Arr[F64, 8](uninitialized=True)
        var rec47 = Ptr(to=rec47_tmp[S32(4)])
        var zec9 = Arr[F64, 4](uninitialized=True)
        var rec46_tmp = Arr[F64, 8](uninitialized=True)
        var rec46 = Ptr(to=rec46_tmp[S32(4)])
        var zec10 = Arr[F64, 4](uninitialized=True)
        var rec45_tmp = Arr[F64, 8](uninitialized=True)
        var rec45 = Ptr(to=rec45_tmp[S32(4)])
        var rec55_tmp = Arr[F64, 8](uninitialized=True)
        var rec55 = Ptr(to=rec55_tmp[S32(4)])
        var rec54_tmp = Arr[F64, 8](uninitialized=True)
        var rec54 = Ptr(to=rec54_tmp[S32(4)])
        var yec4_tmp = Arr[F64, 8](uninitialized=True)
        var yec4 = Ptr(to=yec4_tmp[S32(4)])
        var rec53_tmp = Arr[F64, 8](uninitialized=True)
        var rec53 = Ptr(to=rec53_tmp[S32(4)])
        var rec52_tmp = Arr[F64, 8](uninitialized=True)
        var rec52 = Ptr(to=rec52_tmp[S32(4)])
        var zec11 = Arr[F64, 4](uninitialized=True)
        var rec51_tmp = Arr[F64, 8](uninitialized=True)
        var rec51 = Ptr(to=rec51_tmp[S32(4)])
        var rec59_tmp = Arr[F64, 8](uninitialized=True)
        var rec59 = Ptr(to=rec59_tmp[S32(4)])
        var rec58_tmp = Arr[F64, 8](uninitialized=True)
        var rec58 = Ptr(to=rec58_tmp[S32(4)])
        var yec5_tmp = Arr[F64, 8](uninitialized=True)
        var yec5 = Ptr(to=yec5_tmp[S32(4)])
        var rec57_tmp = Arr[F64, 8](uninitialized=True)
        var rec57 = Ptr(to=rec57_tmp[S32(4)])
        var rec56_tmp = Arr[F64, 8](uninitialized=True)
        var rec56 = Ptr(to=rec56_tmp[S32(4)])
        var rec61_tmp = Arr[F64, 8](uninitialized=True)
        var rec61 = Ptr(to=rec61_tmp[S32(4)])
        var rec60_tmp = Arr[F64, 8](uninitialized=True)
        var rec60 = Ptr(to=rec60_tmp[S32(4)])
        var rec66_tmp = Arr[F64, 8](uninitialized=True)
        var rec66 = Ptr(to=rec66_tmp[S32(4)])
        var rec65_tmp = Arr[F64, 8](uninitialized=True)
        var rec65 = Ptr(to=rec65_tmp[S32(4)])
        var zec12 = Arr[F64, 4](uninitialized=True)
        var rec64_tmp = Arr[F64, 8](uninitialized=True)
        var rec64 = Ptr(to=rec64_tmp[S32(4)])
        var zec13 = Arr[F64, 4](uninitialized=True)
        var rec63_tmp = Arr[F64, 8](uninitialized=True)
        var rec63 = Ptr(to=rec63_tmp[S32(4)])
        var zec14 = Arr[F64, 4](uninitialized=True)
        var rec62_tmp = Arr[F64, 8](uninitialized=True)
        var rec62 = Ptr(to=rec62_tmp[S32(4)])
        var rec72_tmp = Arr[F64, 8](uninitialized=True)
        var rec72 = Ptr(to=rec72_tmp[S32(4)])
        var rec71_tmp = Arr[F64, 8](uninitialized=True)
        var rec71 = Ptr(to=rec71_tmp[S32(4)])
        var yec6_tmp = Arr[F64, 8](uninitialized=True)
        var yec6 = Ptr(to=yec6_tmp[S32(4)])
        var rec70_tmp = Arr[F64, 8](uninitialized=True)
        var rec70 = Ptr(to=rec70_tmp[S32(4)])
        var rec69_tmp = Arr[F64, 8](uninitialized=True)
        var rec69 = Ptr(to=rec69_tmp[S32(4)])
        var zec15 = Arr[F64, 4](uninitialized=True)
        var rec68_tmp = Arr[F64, 8](uninitialized=True)
        var rec68 = Ptr(to=rec68_tmp[S32(4)])
        var zec16 = Arr[F64, 4](uninitialized=True)
        var rec67_tmp = Arr[F64, 8](uninitialized=True)
        var rec67 = Ptr(to=rec67_tmp[S32(4)])
        var rec77_tmp = Arr[F64, 8](uninitialized=True)
        var rec77 = Ptr(to=rec77_tmp[S32(4)])
        var rec76_tmp = Arr[F64, 8](uninitialized=True)
        var rec76 = Ptr(to=rec76_tmp[S32(4)])
        var yec7_tmp = Arr[F64, 8](uninitialized=True)
        var yec7 = Ptr(to=yec7_tmp[S32(4)])
        var rec75_tmp = Arr[F64, 8](uninitialized=True)
        var rec75 = Ptr(to=rec75_tmp[S32(4)])
        var rec74_tmp = Arr[F64, 8](uninitialized=True)
        var rec74 = Ptr(to=rec74_tmp[S32(4)])
        var zec17 = Arr[F64, 4](uninitialized=True)
        var rec73_tmp = Arr[F64, 8](uninitialized=True)
        var rec73 = Ptr(to=rec73_tmp[S32(4)])
        var rec81_tmp = Arr[F64, 8](uninitialized=True)
        var rec81 = Ptr(to=rec81_tmp[S32(4)])
        var rec80_tmp = Arr[F64, 8](uninitialized=True)
        var rec80 = Ptr(to=rec80_tmp[S32(4)])
        var yec8_tmp = Arr[F64, 8](uninitialized=True)
        var yec8 = Ptr(to=yec8_tmp[S32(4)])
        var rec79_tmp = Arr[F64, 8](uninitialized=True)
        var rec79 = Ptr(to=rec79_tmp[S32(4)])
        var rec78_tmp = Arr[F64, 8](uninitialized=True)
        var rec78 = Ptr(to=rec78_tmp[S32(4)])
        var rec83_tmp = Arr[F64, 8](uninitialized=True)
        var rec83 = Ptr(to=rec83_tmp[S32(4)])
        var rec82_tmp = Arr[F64, 8](uninitialized=True)
        var rec82 = Ptr(to=rec82_tmp[S32(4)])
        var rec88_tmp = Arr[F64, 8](uninitialized=True)
        var rec88 = Ptr(to=rec88_tmp[S32(4)])
        var rec87_tmp = Arr[F64, 8](uninitialized=True)
        var rec87 = Ptr(to=rec87_tmp[S32(4)])
        var zec18 = Arr[F64, 4](uninitialized=True)
        var rec86_tmp = Arr[F64, 8](uninitialized=True)
        var rec86 = Ptr(to=rec86_tmp[S32(4)])
        var zec19 = Arr[F64, 4](uninitialized=True)
        var rec85_tmp = Arr[F64, 8](uninitialized=True)
        var rec85 = Ptr(to=rec85_tmp[S32(4)])
        var zec20 = Arr[F64, 4](uninitialized=True)
        var rec84_tmp = Arr[F64, 8](uninitialized=True)
        var rec84 = Ptr(to=rec84_tmp[S32(4)])
        var rec94_tmp = Arr[F64, 8](uninitialized=True)
        var rec94 = Ptr(to=rec94_tmp[S32(4)])
        var rec93_tmp = Arr[F64, 8](uninitialized=True)
        var rec93 = Ptr(to=rec93_tmp[S32(4)])
        var yec9_tmp = Arr[F64, 8](uninitialized=True)
        var yec9 = Ptr(to=yec9_tmp[S32(4)])
        var rec92_tmp = Arr[F64, 8](uninitialized=True)
        var rec92 = Ptr(to=rec92_tmp[S32(4)])
        var rec91_tmp = Arr[F64, 8](uninitialized=True)
        var rec91 = Ptr(to=rec91_tmp[S32(4)])
        var zec21 = Arr[F64, 4](uninitialized=True)
        var rec90_tmp = Arr[F64, 8](uninitialized=True)
        var rec90 = Ptr(to=rec90_tmp[S32(4)])
        var zec22 = Arr[F64, 4](uninitialized=True)
        var rec89_tmp = Arr[F64, 8](uninitialized=True)
        var rec89 = Ptr(to=rec89_tmp[S32(4)])
        var rec99_tmp = Arr[F64, 8](uninitialized=True)
        var rec99 = Ptr(to=rec99_tmp[S32(4)])
        var rec98_tmp = Arr[F64, 8](uninitialized=True)
        var rec98 = Ptr(to=rec98_tmp[S32(4)])
        var yec10_tmp = Arr[F64, 8](uninitialized=True)
        var yec10 = Ptr(to=yec10_tmp[S32(4)])
        var rec97_tmp = Arr[F64, 8](uninitialized=True)
        var rec97 = Ptr(to=rec97_tmp[S32(4)])
        var rec96_tmp = Arr[F64, 8](uninitialized=True)
        var rec96 = Ptr(to=rec96_tmp[S32(4)])
        var zec23 = Arr[F64, 4](uninitialized=True)
        var rec95_tmp = Arr[F64, 8](uninitialized=True)
        var rec95 = Ptr(to=rec95_tmp[S32(4)])
        var rec103_tmp = Arr[F64, 8](uninitialized=True)
        var rec103 = Ptr(to=rec103_tmp[S32(4)])
        var rec102_tmp = Arr[F64, 8](uninitialized=True)
        var rec102 = Ptr(to=rec102_tmp[S32(4)])
        var yec11_tmp = Arr[F64, 8](uninitialized=True)
        var yec11 = Ptr(to=yec11_tmp[S32(4)])
        var rec101_tmp = Arr[F64, 8](uninitialized=True)
        var rec101 = Ptr(to=rec101_tmp[S32(4)])
        var rec100_tmp = Arr[F64, 8](uninitialized=True)
        var rec100 = Ptr(to=rec100_tmp[S32(4)])
        var rec105_tmp = Arr[F64, 8](uninitialized=True)
        var rec105 = Ptr(to=rec105_tmp[S32(4)])
        var rec104_tmp = Arr[F64, 8](uninitialized=True)
        var rec104 = Ptr(to=rec104_tmp[S32(4)])
        var rec110_tmp = Arr[F64, 8](uninitialized=True)
        var rec110 = Ptr(to=rec110_tmp[S32(4)])
        var rec109_tmp = Arr[F64, 8](uninitialized=True)
        var rec109 = Ptr(to=rec109_tmp[S32(4)])
        var zec24 = Arr[F64, 4](uninitialized=True)
        var rec108_tmp = Arr[F64, 8](uninitialized=True)
        var rec108 = Ptr(to=rec108_tmp[S32(4)])
        var zec25 = Arr[F64, 4](uninitialized=True)
        var rec107_tmp = Arr[F64, 8](uninitialized=True)
        var rec107 = Ptr(to=rec107_tmp[S32(4)])
        var zec26 = Arr[F64, 4](uninitialized=True)
        var rec106_tmp = Arr[F64, 8](uninitialized=True)
        var rec106 = Ptr(to=rec106_tmp[S32(4)])
        var rec116_tmp = Arr[F64, 8](uninitialized=True)
        var rec116 = Ptr(to=rec116_tmp[S32(4)])
        var rec115_tmp = Arr[F64, 8](uninitialized=True)
        var rec115 = Ptr(to=rec115_tmp[S32(4)])
        var yec12_tmp = Arr[F64, 8](uninitialized=True)
        var yec12 = Ptr(to=yec12_tmp[S32(4)])
        var rec114_tmp = Arr[F64, 8](uninitialized=True)
        var rec114 = Ptr(to=rec114_tmp[S32(4)])
        var rec113_tmp = Arr[F64, 8](uninitialized=True)
        var rec113 = Ptr(to=rec113_tmp[S32(4)])
        var zec27 = Arr[F64, 4](uninitialized=True)
        var rec112_tmp = Arr[F64, 8](uninitialized=True)
        var rec112 = Ptr(to=rec112_tmp[S32(4)])
        var zec28 = Arr[F64, 4](uninitialized=True)
        var rec111_tmp = Arr[F64, 8](uninitialized=True)
        var rec111 = Ptr(to=rec111_tmp[S32(4)])
        var rec121_tmp = Arr[F64, 8](uninitialized=True)
        var rec121 = Ptr(to=rec121_tmp[S32(4)])
        var rec120_tmp = Arr[F64, 8](uninitialized=True)
        var rec120 = Ptr(to=rec120_tmp[S32(4)])
        var yec13_tmp = Arr[F64, 8](uninitialized=True)
        var yec13 = Ptr(to=yec13_tmp[S32(4)])
        var rec119_tmp = Arr[F64, 8](uninitialized=True)
        var rec119 = Ptr(to=rec119_tmp[S32(4)])
        var rec118_tmp = Arr[F64, 8](uninitialized=True)
        var rec118 = Ptr(to=rec118_tmp[S32(4)])
        var zec29 = Arr[F64, 4](uninitialized=True)
        var rec117_tmp = Arr[F64, 8](uninitialized=True)
        var rec117 = Ptr(to=rec117_tmp[S32(4)])
        var rec125_tmp = Arr[F64, 8](uninitialized=True)
        var rec125 = Ptr(to=rec125_tmp[S32(4)])
        var rec124_tmp = Arr[F64, 8](uninitialized=True)
        var rec124 = Ptr(to=rec124_tmp[S32(4)])
        var yec14_tmp = Arr[F64, 8](uninitialized=True)
        var yec14 = Ptr(to=yec14_tmp[S32(4)])
        var rec123_tmp = Arr[F64, 8](uninitialized=True)
        var rec123 = Ptr(to=rec123_tmp[S32(4)])
        var rec122_tmp = Arr[F64, 8](uninitialized=True)
        var rec122 = Ptr(to=rec122_tmp[S32(4)])
        var rec127_tmp = Arr[F64, 8](uninitialized=True)
        var rec127 = Ptr(to=rec127_tmp[S32(4)])
        var rec126_tmp = Arr[F64, 8](uninitialized=True)
        var rec126 = Ptr(to=rec126_tmp[S32(4)])
        var rec132_tmp = Arr[F64, 8](uninitialized=True)
        var rec132 = Ptr(to=rec132_tmp[S32(4)])
        var rec131_tmp = Arr[F64, 8](uninitialized=True)
        var rec131 = Ptr(to=rec131_tmp[S32(4)])
        var zec30 = Arr[F64, 4](uninitialized=True)
        var rec130_tmp = Arr[F64, 8](uninitialized=True)
        var rec130 = Ptr(to=rec130_tmp[S32(4)])
        var zec31 = Arr[F64, 4](uninitialized=True)
        var rec129_tmp = Arr[F64, 8](uninitialized=True)
        var rec129 = Ptr(to=rec129_tmp[S32(4)])
        var zec32 = Arr[F64, 4](uninitialized=True)
        var rec128_tmp = Arr[F64, 8](uninitialized=True)
        var rec128 = Ptr(to=rec128_tmp[S32(4)])
        var rec138_tmp = Arr[F64, 8](uninitialized=True)
        var rec138 = Ptr(to=rec138_tmp[S32(4)])
        var rec137_tmp = Arr[F64, 8](uninitialized=True)
        var rec137 = Ptr(to=rec137_tmp[S32(4)])
        var yec15_tmp = Arr[F64, 8](uninitialized=True)
        var yec15 = Ptr(to=yec15_tmp[S32(4)])
        var rec136_tmp = Arr[F64, 8](uninitialized=True)
        var rec136 = Ptr(to=rec136_tmp[S32(4)])
        var rec135_tmp = Arr[F64, 8](uninitialized=True)
        var rec135 = Ptr(to=rec135_tmp[S32(4)])
        var zec33 = Arr[F64, 4](uninitialized=True)
        var rec134_tmp = Arr[F64, 8](uninitialized=True)
        var rec134 = Ptr(to=rec134_tmp[S32(4)])
        var zec34 = Arr[F64, 4](uninitialized=True)
        var rec133_tmp = Arr[F64, 8](uninitialized=True)
        var rec133 = Ptr(to=rec133_tmp[S32(4)])
        var rec143_tmp = Arr[F64, 8](uninitialized=True)
        var rec143 = Ptr(to=rec143_tmp[S32(4)])
        var rec142_tmp = Arr[F64, 8](uninitialized=True)
        var rec142 = Ptr(to=rec142_tmp[S32(4)])
        var yec16_tmp = Arr[F64, 8](uninitialized=True)
        var yec16 = Ptr(to=yec16_tmp[S32(4)])
        var rec141_tmp = Arr[F64, 8](uninitialized=True)
        var rec141 = Ptr(to=rec141_tmp[S32(4)])
        var rec140_tmp = Arr[F64, 8](uninitialized=True)
        var rec140 = Ptr(to=rec140_tmp[S32(4)])
        var zec35 = Arr[F64, 4](uninitialized=True)
        var rec139_tmp = Arr[F64, 8](uninitialized=True)
        var rec139 = Ptr(to=rec139_tmp[S32(4)])
        var rec147_tmp = Arr[F64, 8](uninitialized=True)
        var rec147 = Ptr(to=rec147_tmp[S32(4)])
        var rec146_tmp = Arr[F64, 8](uninitialized=True)
        var rec146 = Ptr(to=rec146_tmp[S32(4)])
        var yec17_tmp = Arr[F64, 8](uninitialized=True)
        var yec17 = Ptr(to=yec17_tmp[S32(4)])
        var rec145_tmp = Arr[F64, 8](uninitialized=True)
        var rec145 = Ptr(to=rec145_tmp[S32(4)])
        var rec144_tmp = Arr[F64, 8](uninitialized=True)
        var rec144 = Ptr(to=rec144_tmp[S32(4)])
        var rec149_tmp = Arr[F64, 8](uninitialized=True)
        var rec149 = Ptr(to=rec149_tmp[S32(4)])
        var rec148_tmp = Arr[F64, 8](uninitialized=True)
        var rec148 = Ptr(to=rec148_tmp[S32(4)])
        var rec154_tmp = Arr[F64, 8](uninitialized=True)
        var rec154 = Ptr(to=rec154_tmp[S32(4)])
        var rec153_tmp = Arr[F64, 8](uninitialized=True)
        var rec153 = Ptr(to=rec153_tmp[S32(4)])
        var zec36 = Arr[F64, 4](uninitialized=True)
        var rec152_tmp = Arr[F64, 8](uninitialized=True)
        var rec152 = Ptr(to=rec152_tmp[S32(4)])
        var zec37 = Arr[F64, 4](uninitialized=True)
        var rec151_tmp = Arr[F64, 8](uninitialized=True)
        var rec151 = Ptr(to=rec151_tmp[S32(4)])
        var zec38 = Arr[F64, 4](uninitialized=True)
        var rec150_tmp = Arr[F64, 8](uninitialized=True)
        var rec150 = Ptr(to=rec150_tmp[S32(4)])
        var rec160_tmp = Arr[F64, 8](uninitialized=True)
        var rec160 = Ptr(to=rec160_tmp[S32(4)])
        var rec159_tmp = Arr[F64, 8](uninitialized=True)
        var rec159 = Ptr(to=rec159_tmp[S32(4)])
        var yec18_tmp = Arr[F64, 8](uninitialized=True)
        var yec18 = Ptr(to=yec18_tmp[S32(4)])
        var rec158_tmp = Arr[F64, 8](uninitialized=True)
        var rec158 = Ptr(to=rec158_tmp[S32(4)])
        var rec157_tmp = Arr[F64, 8](uninitialized=True)
        var rec157 = Ptr(to=rec157_tmp[S32(4)])
        var zec39 = Arr[F64, 4](uninitialized=True)
        var rec156_tmp = Arr[F64, 8](uninitialized=True)
        var rec156 = Ptr(to=rec156_tmp[S32(4)])
        var zec40 = Arr[F64, 4](uninitialized=True)
        var rec155_tmp = Arr[F64, 8](uninitialized=True)
        var rec155 = Ptr(to=rec155_tmp[S32(4)])
        var rec165_tmp = Arr[F64, 8](uninitialized=True)
        var rec165 = Ptr(to=rec165_tmp[S32(4)])
        var rec164_tmp = Arr[F64, 8](uninitialized=True)
        var rec164 = Ptr(to=rec164_tmp[S32(4)])
        var yec19_tmp = Arr[F64, 8](uninitialized=True)
        var yec19 = Ptr(to=yec19_tmp[S32(4)])
        var rec163_tmp = Arr[F64, 8](uninitialized=True)
        var rec163 = Ptr(to=rec163_tmp[S32(4)])
        var rec162_tmp = Arr[F64, 8](uninitialized=True)
        var rec162 = Ptr(to=rec162_tmp[S32(4)])
        var zec41 = Arr[F64, 4](uninitialized=True)
        var rec161_tmp = Arr[F64, 8](uninitialized=True)
        var rec161 = Ptr(to=rec161_tmp[S32(4)])
        var rec169_tmp = Arr[F64, 8](uninitialized=True)
        var rec169 = Ptr(to=rec169_tmp[S32(4)])
        var rec168_tmp = Arr[F64, 8](uninitialized=True)
        var rec168 = Ptr(to=rec168_tmp[S32(4)])
        var yec20_tmp = Arr[F64, 8](uninitialized=True)
        var yec20 = Ptr(to=yec20_tmp[S32(4)])
        var rec167_tmp = Arr[F64, 8](uninitialized=True)
        var rec167 = Ptr(to=rec167_tmp[S32(4)])
        var rec166_tmp = Arr[F64, 8](uninitialized=True)
        var rec166 = Ptr(to=rec166_tmp[S32(4)])
        var rec171_tmp = Arr[F64, 8](uninitialized=True)
        var rec171 = Ptr(to=rec171_tmp[S32(4)])
        var rec170_tmp = Arr[F64, 8](uninitialized=True)
        var rec170 = Ptr(to=rec170_tmp[S32(4)])
        var rec176_tmp = Arr[F64, 8](uninitialized=True)
        var rec176 = Ptr(to=rec176_tmp[S32(4)])
        var rec175_tmp = Arr[F64, 8](uninitialized=True)
        var rec175 = Ptr(to=rec175_tmp[S32(4)])
        var zec42 = Arr[F64, 4](uninitialized=True)
        var rec174_tmp = Arr[F64, 8](uninitialized=True)
        var rec174 = Ptr(to=rec174_tmp[S32(4)])
        var zec43 = Arr[F64, 4](uninitialized=True)
        var rec173_tmp = Arr[F64, 8](uninitialized=True)
        var rec173 = Ptr(to=rec173_tmp[S32(4)])
        var zec44 = Arr[F64, 4](uninitialized=True)
        var rec172_tmp = Arr[F64, 8](uninitialized=True)
        var rec172 = Ptr(to=rec172_tmp[S32(4)])
        var rec182_tmp = Arr[F64, 8](uninitialized=True)
        var rec182 = Ptr(to=rec182_tmp[S32(4)])
        var rec181_tmp = Arr[F64, 8](uninitialized=True)
        var rec181 = Ptr(to=rec181_tmp[S32(4)])
        var yec21_tmp = Arr[F64, 8](uninitialized=True)
        var yec21 = Ptr(to=yec21_tmp[S32(4)])
        var rec180_tmp = Arr[F64, 8](uninitialized=True)
        var rec180 = Ptr(to=rec180_tmp[S32(4)])
        var rec179_tmp = Arr[F64, 8](uninitialized=True)
        var rec179 = Ptr(to=rec179_tmp[S32(4)])
        var zec45 = Arr[F64, 4](uninitialized=True)
        var rec178_tmp = Arr[F64, 8](uninitialized=True)
        var rec178 = Ptr(to=rec178_tmp[S32(4)])
        var zec46 = Arr[F64, 4](uninitialized=True)
        var rec177_tmp = Arr[F64, 8](uninitialized=True)
        var rec177 = Ptr(to=rec177_tmp[S32(4)])
        var rec187_tmp = Arr[F64, 8](uninitialized=True)
        var rec187 = Ptr(to=rec187_tmp[S32(4)])
        var rec186_tmp = Arr[F64, 8](uninitialized=True)
        var rec186 = Ptr(to=rec186_tmp[S32(4)])
        var yec22_tmp = Arr[F64, 8](uninitialized=True)
        var yec22 = Ptr(to=yec22_tmp[S32(4)])
        var rec185_tmp = Arr[F64, 8](uninitialized=True)
        var rec185 = Ptr(to=rec185_tmp[S32(4)])
        var rec184_tmp = Arr[F64, 8](uninitialized=True)
        var rec184 = Ptr(to=rec184_tmp[S32(4)])
        var zec47 = Arr[F64, 4](uninitialized=True)
        var rec183_tmp = Arr[F64, 8](uninitialized=True)
        var rec183 = Ptr(to=rec183_tmp[S32(4)])
        var rec191_tmp = Arr[F64, 8](uninitialized=True)
        var rec191 = Ptr(to=rec191_tmp[S32(4)])
        var rec190_tmp = Arr[F64, 8](uninitialized=True)
        var rec190 = Ptr(to=rec190_tmp[S32(4)])
        var yec23_tmp = Arr[F64, 8](uninitialized=True)
        var yec23 = Ptr(to=yec23_tmp[S32(4)])
        var rec189_tmp = Arr[F64, 8](uninitialized=True)
        var rec189 = Ptr(to=rec189_tmp[S32(4)])
        var rec188_tmp = Arr[F64, 8](uninitialized=True)
        var rec188 = Ptr(to=rec188_tmp[S32(4)])
        var rec193_tmp = Arr[F64, 8](uninitialized=True)
        var rec193 = Ptr(to=rec193_tmp[S32(4)])
        var rec192_tmp = Arr[F64, 8](uninitialized=True)
        var rec192 = Ptr(to=rec192_tmp[S32(4)])
        var rec198_tmp = Arr[F64, 8](uninitialized=True)
        var rec198 = Ptr(to=rec198_tmp[S32(4)])
        var rec197_tmp = Arr[F64, 8](uninitialized=True)
        var rec197 = Ptr(to=rec197_tmp[S32(4)])
        var zec48 = Arr[F64, 4](uninitialized=True)
        var rec196_tmp = Arr[F64, 8](uninitialized=True)
        var rec196 = Ptr(to=rec196_tmp[S32(4)])
        var zec49 = Arr[F64, 4](uninitialized=True)
        var rec195_tmp = Arr[F64, 8](uninitialized=True)
        var rec195 = Ptr(to=rec195_tmp[S32(4)])
        var zec50 = Arr[F64, 4](uninitialized=True)
        var rec194_tmp = Arr[F64, 8](uninitialized=True)
        var rec194 = Ptr(to=rec194_tmp[S32(4)])
        var rec204_tmp = Arr[F64, 8](uninitialized=True)
        var rec204 = Ptr(to=rec204_tmp[S32(4)])
        var rec203_tmp = Arr[F64, 8](uninitialized=True)
        var rec203 = Ptr(to=rec203_tmp[S32(4)])
        var yec24_tmp = Arr[F64, 8](uninitialized=True)
        var yec24 = Ptr(to=yec24_tmp[S32(4)])
        var rec202_tmp = Arr[F64, 8](uninitialized=True)
        var rec202 = Ptr(to=rec202_tmp[S32(4)])
        var rec201_tmp = Arr[F64, 8](uninitialized=True)
        var rec201 = Ptr(to=rec201_tmp[S32(4)])
        var zec51 = Arr[F64, 4](uninitialized=True)
        var rec200_tmp = Arr[F64, 8](uninitialized=True)
        var rec200 = Ptr(to=rec200_tmp[S32(4)])
        var zec52 = Arr[F64, 4](uninitialized=True)
        var rec199_tmp = Arr[F64, 8](uninitialized=True)
        var rec199 = Ptr(to=rec199_tmp[S32(4)])
        var rec209_tmp = Arr[F64, 8](uninitialized=True)
        var rec209 = Ptr(to=rec209_tmp[S32(4)])
        var rec208_tmp = Arr[F64, 8](uninitialized=True)
        var rec208 = Ptr(to=rec208_tmp[S32(4)])
        var yec25_tmp = Arr[F64, 8](uninitialized=True)
        var yec25 = Ptr(to=yec25_tmp[S32(4)])
        var rec207_tmp = Arr[F64, 8](uninitialized=True)
        var rec207 = Ptr(to=rec207_tmp[S32(4)])
        var rec206_tmp = Arr[F64, 8](uninitialized=True)
        var rec206 = Ptr(to=rec206_tmp[S32(4)])
        var zec53 = Arr[F64, 4](uninitialized=True)
        var rec205_tmp = Arr[F64, 8](uninitialized=True)
        var rec205 = Ptr(to=rec205_tmp[S32(4)])
        var rec213_tmp = Arr[F64, 8](uninitialized=True)
        var rec213 = Ptr(to=rec213_tmp[S32(4)])
        var rec212_tmp = Arr[F64, 8](uninitialized=True)
        var rec212 = Ptr(to=rec212_tmp[S32(4)])
        var yec26_tmp = Arr[F64, 8](uninitialized=True)
        var yec26 = Ptr(to=yec26_tmp[S32(4)])
        var rec211_tmp = Arr[F64, 8](uninitialized=True)
        var rec211 = Ptr(to=rec211_tmp[S32(4)])
        var rec210_tmp = Arr[F64, 8](uninitialized=True)
        var rec210 = Ptr(to=rec210_tmp[S32(4)])
        var rec215_tmp = Arr[F64, 8](uninitialized=True)
        var rec215 = Ptr(to=rec215_tmp[S32(4)])
        var rec214_tmp = Arr[F64, 8](uninitialized=True)
        var rec214 = Ptr(to=rec214_tmp[S32(4)])
        var rec220_tmp = Arr[F64, 8](uninitialized=True)
        var rec220 = Ptr(to=rec220_tmp[S32(4)])
        var rec219_tmp = Arr[F64, 8](uninitialized=True)
        var rec219 = Ptr(to=rec219_tmp[S32(4)])
        var zec54 = Arr[F64, 4](uninitialized=True)
        var rec218_tmp = Arr[F64, 8](uninitialized=True)
        var rec218 = Ptr(to=rec218_tmp[S32(4)])
        var zec55 = Arr[F64, 4](uninitialized=True)
        var rec217_tmp = Arr[F64, 8](uninitialized=True)
        var rec217 = Ptr(to=rec217_tmp[S32(4)])
        var zec56 = Arr[F64, 4](uninitialized=True)
        var rec216_tmp = Arr[F64, 8](uninitialized=True)
        var rec216 = Ptr(to=rec216_tmp[S32(4)])
        var rec226_tmp = Arr[F64, 8](uninitialized=True)
        var rec226 = Ptr(to=rec226_tmp[S32(4)])
        var rec225_tmp = Arr[F64, 8](uninitialized=True)
        var rec225 = Ptr(to=rec225_tmp[S32(4)])
        var yec27_tmp = Arr[F64, 8](uninitialized=True)
        var yec27 = Ptr(to=yec27_tmp[S32(4)])
        var rec224_tmp = Arr[F64, 8](uninitialized=True)
        var rec224 = Ptr(to=rec224_tmp[S32(4)])
        var rec223_tmp = Arr[F64, 8](uninitialized=True)
        var rec223 = Ptr(to=rec223_tmp[S32(4)])
        var zec57 = Arr[F64, 4](uninitialized=True)
        var rec222_tmp = Arr[F64, 8](uninitialized=True)
        var rec222 = Ptr(to=rec222_tmp[S32(4)])
        var zec58 = Arr[F64, 4](uninitialized=True)
        var rec221_tmp = Arr[F64, 8](uninitialized=True)
        var rec221 = Ptr(to=rec221_tmp[S32(4)])
        var rec231_tmp = Arr[F64, 8](uninitialized=True)
        var rec231 = Ptr(to=rec231_tmp[S32(4)])
        var rec230_tmp = Arr[F64, 8](uninitialized=True)
        var rec230 = Ptr(to=rec230_tmp[S32(4)])
        var yec28_tmp = Arr[F64, 8](uninitialized=True)
        var yec28 = Ptr(to=yec28_tmp[S32(4)])
        var rec229_tmp = Arr[F64, 8](uninitialized=True)
        var rec229 = Ptr(to=rec229_tmp[S32(4)])
        var rec228_tmp = Arr[F64, 8](uninitialized=True)
        var rec228 = Ptr(to=rec228_tmp[S32(4)])
        var zec59 = Arr[F64, 4](uninitialized=True)
        var rec227_tmp = Arr[F64, 8](uninitialized=True)
        var rec227 = Ptr(to=rec227_tmp[S32(4)])
        var rec235_tmp = Arr[F64, 8](uninitialized=True)
        var rec235 = Ptr(to=rec235_tmp[S32(4)])
        var rec234_tmp = Arr[F64, 8](uninitialized=True)
        var rec234 = Ptr(to=rec234_tmp[S32(4)])
        var yec29_tmp = Arr[F64, 8](uninitialized=True)
        var yec29 = Ptr(to=yec29_tmp[S32(4)])
        var rec233_tmp = Arr[F64, 8](uninitialized=True)
        var rec233 = Ptr(to=rec233_tmp[S32(4)])
        var rec232_tmp = Arr[F64, 8](uninitialized=True)
        var rec232 = Ptr(to=rec232_tmp[S32(4)])
        var rec237_tmp = Arr[F64, 8](uninitialized=True)
        var rec237 = Ptr(to=rec237_tmp[S32(4)])
        var rec236_tmp = Arr[F64, 8](uninitialized=True)
        var rec236 = Ptr(to=rec236_tmp[S32(4)])
        var rec242_tmp = Arr[F64, 8](uninitialized=True)
        var rec242 = Ptr(to=rec242_tmp[S32(4)])
        var rec241_tmp = Arr[F64, 8](uninitialized=True)
        var rec241 = Ptr(to=rec241_tmp[S32(4)])
        var zec60 = Arr[F64, 4](uninitialized=True)
        var rec240_tmp = Arr[F64, 8](uninitialized=True)
        var rec240 = Ptr(to=rec240_tmp[S32(4)])
        var zec61 = Arr[F64, 4](uninitialized=True)
        var rec239_tmp = Arr[F64, 8](uninitialized=True)
        var rec239 = Ptr(to=rec239_tmp[S32(4)])
        var zec62 = Arr[F64, 4](uninitialized=True)
        var rec238_tmp = Arr[F64, 8](uninitialized=True)
        var rec238 = Ptr(to=rec238_tmp[S32(4)])
        var rec248_tmp = Arr[F64, 8](uninitialized=True)
        var rec248 = Ptr(to=rec248_tmp[S32(4)])
        var rec247_tmp = Arr[F64, 8](uninitialized=True)
        var rec247 = Ptr(to=rec247_tmp[S32(4)])
        var yec30_tmp = Arr[F64, 8](uninitialized=True)
        var yec30 = Ptr(to=yec30_tmp[S32(4)])
        var rec246_tmp = Arr[F64, 8](uninitialized=True)
        var rec246 = Ptr(to=rec246_tmp[S32(4)])
        var rec245_tmp = Arr[F64, 8](uninitialized=True)
        var rec245 = Ptr(to=rec245_tmp[S32(4)])
        var zec63 = Arr[F64, 4](uninitialized=True)
        var rec244_tmp = Arr[F64, 8](uninitialized=True)
        var rec244 = Ptr(to=rec244_tmp[S32(4)])
        var zec64 = Arr[F64, 4](uninitialized=True)
        var rec243_tmp = Arr[F64, 8](uninitialized=True)
        var rec243 = Ptr(to=rec243_tmp[S32(4)])
        var rec253_tmp = Arr[F64, 8](uninitialized=True)
        var rec253 = Ptr(to=rec253_tmp[S32(4)])
        var rec252_tmp = Arr[F64, 8](uninitialized=True)
        var rec252 = Ptr(to=rec252_tmp[S32(4)])
        var yec31_tmp = Arr[F64, 8](uninitialized=True)
        var yec31 = Ptr(to=yec31_tmp[S32(4)])
        var rec251_tmp = Arr[F64, 8](uninitialized=True)
        var rec251 = Ptr(to=rec251_tmp[S32(4)])
        var rec250_tmp = Arr[F64, 8](uninitialized=True)
        var rec250 = Ptr(to=rec250_tmp[S32(4)])
        var zec65 = Arr[F64, 4](uninitialized=True)
        var rec249_tmp = Arr[F64, 8](uninitialized=True)
        var rec249 = Ptr(to=rec249_tmp[S32(4)])
        var rec257_tmp = Arr[F64, 8](uninitialized=True)
        var rec257 = Ptr(to=rec257_tmp[S32(4)])
        var rec256_tmp = Arr[F64, 8](uninitialized=True)
        var rec256 = Ptr(to=rec256_tmp[S32(4)])
        var yec32_tmp = Arr[F64, 8](uninitialized=True)
        var yec32 = Ptr(to=yec32_tmp[S32(4)])
        var rec255_tmp = Arr[F64, 8](uninitialized=True)
        var rec255 = Ptr(to=rec255_tmp[S32(4)])
        var rec254_tmp = Arr[F64, 8](uninitialized=True)
        var rec254 = Ptr(to=rec254_tmp[S32(4)])
        var rec259_tmp = Arr[F64, 8](uninitialized=True)
        var rec259 = Ptr(to=rec259_tmp[S32(4)])
        var rec258_tmp = Arr[F64, 8](uninitialized=True)
        var rec258 = Ptr(to=rec258_tmp[S32(4)])
        var rec264_tmp = Arr[F64, 8](uninitialized=True)
        var rec264 = Ptr(to=rec264_tmp[S32(4)])
        var rec263_tmp = Arr[F64, 8](uninitialized=True)
        var rec263 = Ptr(to=rec263_tmp[S32(4)])
        var zec66 = Arr[F64, 4](uninitialized=True)
        var rec262_tmp = Arr[F64, 8](uninitialized=True)
        var rec262 = Ptr(to=rec262_tmp[S32(4)])
        var zec67 = Arr[F64, 4](uninitialized=True)
        var rec261_tmp = Arr[F64, 8](uninitialized=True)
        var rec261 = Ptr(to=rec261_tmp[S32(4)])
        var zec68 = Arr[F64, 4](uninitialized=True)
        var rec260_tmp = Arr[F64, 8](uninitialized=True)
        var rec260 = Ptr(to=rec260_tmp[S32(4)])
        var rec270_tmp = Arr[F64, 8](uninitialized=True)
        var rec270 = Ptr(to=rec270_tmp[S32(4)])
        var rec269_tmp = Arr[F64, 8](uninitialized=True)
        var rec269 = Ptr(to=rec269_tmp[S32(4)])
        var yec33_tmp = Arr[F64, 8](uninitialized=True)
        var yec33 = Ptr(to=yec33_tmp[S32(4)])
        var rec268_tmp = Arr[F64, 8](uninitialized=True)
        var rec268 = Ptr(to=rec268_tmp[S32(4)])
        var rec267_tmp = Arr[F64, 8](uninitialized=True)
        var rec267 = Ptr(to=rec267_tmp[S32(4)])
        var zec69 = Arr[F64, 4](uninitialized=True)
        var rec266_tmp = Arr[F64, 8](uninitialized=True)
        var rec266 = Ptr(to=rec266_tmp[S32(4)])
        var zec70 = Arr[F64, 4](uninitialized=True)
        var rec265_tmp = Arr[F64, 8](uninitialized=True)
        var rec265 = Ptr(to=rec265_tmp[S32(4)])
        var rec275_tmp = Arr[F64, 8](uninitialized=True)
        var rec275 = Ptr(to=rec275_tmp[S32(4)])
        var rec274_tmp = Arr[F64, 8](uninitialized=True)
        var rec274 = Ptr(to=rec274_tmp[S32(4)])
        var yec34_tmp = Arr[F64, 8](uninitialized=True)
        var yec34 = Ptr(to=yec34_tmp[S32(4)])
        var rec273_tmp = Arr[F64, 8](uninitialized=True)
        var rec273 = Ptr(to=rec273_tmp[S32(4)])
        var rec272_tmp = Arr[F64, 8](uninitialized=True)
        var rec272 = Ptr(to=rec272_tmp[S32(4)])
        var zec71 = Arr[F64, 4](uninitialized=True)
        var rec271_tmp = Arr[F64, 8](uninitialized=True)
        var rec271 = Ptr(to=rec271_tmp[S32(4)])
        var rec279_tmp = Arr[F64, 8](uninitialized=True)
        var rec279 = Ptr(to=rec279_tmp[S32(4)])
        var rec278_tmp = Arr[F64, 8](uninitialized=True)
        var rec278 = Ptr(to=rec278_tmp[S32(4)])
        var yec35_tmp = Arr[F64, 8](uninitialized=True)
        var yec35 = Ptr(to=yec35_tmp[S32(4)])
        var rec277_tmp = Arr[F64, 8](uninitialized=True)
        var rec277 = Ptr(to=rec277_tmp[S32(4)])
        var rec276_tmp = Arr[F64, 8](uninitialized=True)
        var rec276 = Ptr(to=rec276_tmp[S32(4)])
        var rec281_tmp = Arr[F64, 8](uninitialized=True)
        var rec281 = Ptr(to=rec281_tmp[S32(4)])
        var rec280_tmp = Arr[F64, 8](uninitialized=True)
        var rec280 = Ptr(to=rec280_tmp[S32(4)])
        var rec286_tmp = Arr[F64, 8](uninitialized=True)
        var rec286 = Ptr(to=rec286_tmp[S32(4)])
        var rec285_tmp = Arr[F64, 8](uninitialized=True)
        var rec285 = Ptr(to=rec285_tmp[S32(4)])
        var zec72 = Arr[F64, 4](uninitialized=True)
        var rec284_tmp = Arr[F64, 8](uninitialized=True)
        var rec284 = Ptr(to=rec284_tmp[S32(4)])
        var zec73 = Arr[F64, 4](uninitialized=True)
        var rec283_tmp = Arr[F64, 8](uninitialized=True)
        var rec283 = Ptr(to=rec283_tmp[S32(4)])
        var zec74 = Arr[F64, 4](uninitialized=True)
        var rec282_tmp = Arr[F64, 8](uninitialized=True)
        var rec282 = Ptr(to=rec282_tmp[S32(4)])
        var rec292_tmp = Arr[F64, 8](uninitialized=True)
        var rec292 = Ptr(to=rec292_tmp[S32(4)])
        var rec291_tmp = Arr[F64, 8](uninitialized=True)
        var rec291 = Ptr(to=rec291_tmp[S32(4)])
        var yec36_tmp = Arr[F64, 8](uninitialized=True)
        var yec36 = Ptr(to=yec36_tmp[S32(4)])
        var rec290_tmp = Arr[F64, 8](uninitialized=True)
        var rec290 = Ptr(to=rec290_tmp[S32(4)])
        var rec289_tmp = Arr[F64, 8](uninitialized=True)
        var rec289 = Ptr(to=rec289_tmp[S32(4)])
        var zec75 = Arr[F64, 4](uninitialized=True)
        var rec288_tmp = Arr[F64, 8](uninitialized=True)
        var rec288 = Ptr(to=rec288_tmp[S32(4)])
        var zec76 = Arr[F64, 4](uninitialized=True)
        var rec287_tmp = Arr[F64, 8](uninitialized=True)
        var rec287 = Ptr(to=rec287_tmp[S32(4)])
        var rec297_tmp = Arr[F64, 8](uninitialized=True)
        var rec297 = Ptr(to=rec297_tmp[S32(4)])
        var rec296_tmp = Arr[F64, 8](uninitialized=True)
        var rec296 = Ptr(to=rec296_tmp[S32(4)])
        var yec37_tmp = Arr[F64, 8](uninitialized=True)
        var yec37 = Ptr(to=yec37_tmp[S32(4)])
        var rec295_tmp = Arr[F64, 8](uninitialized=True)
        var rec295 = Ptr(to=rec295_tmp[S32(4)])
        var rec294_tmp = Arr[F64, 8](uninitialized=True)
        var rec294 = Ptr(to=rec294_tmp[S32(4)])
        var zec77 = Arr[F64, 4](uninitialized=True)
        var rec293_tmp = Arr[F64, 8](uninitialized=True)
        var rec293 = Ptr(to=rec293_tmp[S32(4)])
        var rec301_tmp = Arr[F64, 8](uninitialized=True)
        var rec301 = Ptr(to=rec301_tmp[S32(4)])
        var rec300_tmp = Arr[F64, 8](uninitialized=True)
        var rec300 = Ptr(to=rec300_tmp[S32(4)])
        var yec38_tmp = Arr[F64, 8](uninitialized=True)
        var yec38 = Ptr(to=yec38_tmp[S32(4)])
        var rec299_tmp = Arr[F64, 8](uninitialized=True)
        var rec299 = Ptr(to=rec299_tmp[S32(4)])
        var rec298_tmp = Arr[F64, 8](uninitialized=True)
        var rec298 = Ptr(to=rec298_tmp[S32(4)])
        var rec303_tmp = Arr[F64, 8](uninitialized=True)
        var rec303 = Ptr(to=rec303_tmp[S32(4)])
        var rec302_tmp = Arr[F64, 8](uninitialized=True)
        var rec302 = Ptr(to=rec302_tmp[S32(4)])
        var rec308_tmp = Arr[F64, 8](uninitialized=True)
        var rec308 = Ptr(to=rec308_tmp[S32(4)])
        var rec307_tmp = Arr[F64, 8](uninitialized=True)
        var rec307 = Ptr(to=rec307_tmp[S32(4)])
        var zec78 = Arr[F64, 4](uninitialized=True)
        var rec306_tmp = Arr[F64, 8](uninitialized=True)
        var rec306 = Ptr(to=rec306_tmp[S32(4)])
        var zec79 = Arr[F64, 4](uninitialized=True)
        var rec305_tmp = Arr[F64, 8](uninitialized=True)
        var rec305 = Ptr(to=rec305_tmp[S32(4)])
        var zec80 = Arr[F64, 4](uninitialized=True)
        var rec304_tmp = Arr[F64, 8](uninitialized=True)
        var rec304 = Ptr(to=rec304_tmp[S32(4)])
        var rec314_tmp = Arr[F64, 8](uninitialized=True)
        var rec314 = Ptr(to=rec314_tmp[S32(4)])
        var rec313_tmp = Arr[F64, 8](uninitialized=True)
        var rec313 = Ptr(to=rec313_tmp[S32(4)])
        var yec39_tmp = Arr[F64, 8](uninitialized=True)
        var yec39 = Ptr(to=yec39_tmp[S32(4)])
        var rec312_tmp = Arr[F64, 8](uninitialized=True)
        var rec312 = Ptr(to=rec312_tmp[S32(4)])
        var rec311_tmp = Arr[F64, 8](uninitialized=True)
        var rec311 = Ptr(to=rec311_tmp[S32(4)])
        var zec81 = Arr[F64, 4](uninitialized=True)
        var rec310_tmp = Arr[F64, 8](uninitialized=True)
        var rec310 = Ptr(to=rec310_tmp[S32(4)])
        var zec82 = Arr[F64, 4](uninitialized=True)
        var rec309_tmp = Arr[F64, 8](uninitialized=True)
        var rec309 = Ptr(to=rec309_tmp[S32(4)])
        var rec319_tmp = Arr[F64, 8](uninitialized=True)
        var rec319 = Ptr(to=rec319_tmp[S32(4)])
        var rec318_tmp = Arr[F64, 8](uninitialized=True)
        var rec318 = Ptr(to=rec318_tmp[S32(4)])
        var yec40_tmp = Arr[F64, 8](uninitialized=True)
        var yec40 = Ptr(to=yec40_tmp[S32(4)])
        var rec317_tmp = Arr[F64, 8](uninitialized=True)
        var rec317 = Ptr(to=rec317_tmp[S32(4)])
        var rec316_tmp = Arr[F64, 8](uninitialized=True)
        var rec316 = Ptr(to=rec316_tmp[S32(4)])
        var zec83 = Arr[F64, 4](uninitialized=True)
        var rec315_tmp = Arr[F64, 8](uninitialized=True)
        var rec315 = Ptr(to=rec315_tmp[S32(4)])
        var rec323_tmp = Arr[F64, 8](uninitialized=True)
        var rec323 = Ptr(to=rec323_tmp[S32(4)])
        var rec322_tmp = Arr[F64, 8](uninitialized=True)
        var rec322 = Ptr(to=rec322_tmp[S32(4)])
        var yec41_tmp = Arr[F64, 8](uninitialized=True)
        var yec41 = Ptr(to=yec41_tmp[S32(4)])
        var rec321_tmp = Arr[F64, 8](uninitialized=True)
        var rec321 = Ptr(to=rec321_tmp[S32(4)])
        var rec320_tmp = Arr[F64, 8](uninitialized=True)
        var rec320 = Ptr(to=rec320_tmp[S32(4)])
        var rec325_tmp = Arr[F64, 8](uninitialized=True)
        var rec325 = Ptr(to=rec325_tmp[S32(4)])
        var rec324_tmp = Arr[F64, 8](uninitialized=True)
        var rec324 = Ptr(to=rec324_tmp[S32(4)])
        var rec330_tmp = Arr[F64, 8](uninitialized=True)
        var rec330 = Ptr(to=rec330_tmp[S32(4)])
        var rec329_tmp = Arr[F64, 8](uninitialized=True)
        var rec329 = Ptr(to=rec329_tmp[S32(4)])
        var zec84 = Arr[F64, 4](uninitialized=True)
        var rec328_tmp = Arr[F64, 8](uninitialized=True)
        var rec328 = Ptr(to=rec328_tmp[S32(4)])
        var zec85 = Arr[F64, 4](uninitialized=True)
        var rec327_tmp = Arr[F64, 8](uninitialized=True)
        var rec327 = Ptr(to=rec327_tmp[S32(4)])
        var zec86 = Arr[F64, 4](uninitialized=True)
        var rec326_tmp = Arr[F64, 8](uninitialized=True)
        var rec326 = Ptr(to=rec326_tmp[S32(4)])
        var rec336_tmp = Arr[F64, 8](uninitialized=True)
        var rec336 = Ptr(to=rec336_tmp[S32(4)])
        var rec335_tmp = Arr[F64, 8](uninitialized=True)
        var rec335 = Ptr(to=rec335_tmp[S32(4)])
        var yec42_tmp = Arr[F64, 8](uninitialized=True)
        var yec42 = Ptr(to=yec42_tmp[S32(4)])
        var rec334_tmp = Arr[F64, 8](uninitialized=True)
        var rec334 = Ptr(to=rec334_tmp[S32(4)])
        var rec333_tmp = Arr[F64, 8](uninitialized=True)
        var rec333 = Ptr(to=rec333_tmp[S32(4)])
        var zec87 = Arr[F64, 4](uninitialized=True)
        var rec332_tmp = Arr[F64, 8](uninitialized=True)
        var rec332 = Ptr(to=rec332_tmp[S32(4)])
        var zec88 = Arr[F64, 4](uninitialized=True)
        var rec331_tmp = Arr[F64, 8](uninitialized=True)
        var rec331 = Ptr(to=rec331_tmp[S32(4)])
        var rec341_tmp = Arr[F64, 8](uninitialized=True)
        var rec341 = Ptr(to=rec341_tmp[S32(4)])
        var rec340_tmp = Arr[F64, 8](uninitialized=True)
        var rec340 = Ptr(to=rec340_tmp[S32(4)])
        var yec43_tmp = Arr[F64, 8](uninitialized=True)
        var yec43 = Ptr(to=yec43_tmp[S32(4)])
        var rec339_tmp = Arr[F64, 8](uninitialized=True)
        var rec339 = Ptr(to=rec339_tmp[S32(4)])
        var rec338_tmp = Arr[F64, 8](uninitialized=True)
        var rec338 = Ptr(to=rec338_tmp[S32(4)])
        var zec89 = Arr[F64, 4](uninitialized=True)
        var rec337_tmp = Arr[F64, 8](uninitialized=True)
        var rec337 = Ptr(to=rec337_tmp[S32(4)])
        var rec345_tmp = Arr[F64, 8](uninitialized=True)
        var rec345 = Ptr(to=rec345_tmp[S32(4)])
        var rec344_tmp = Arr[F64, 8](uninitialized=True)
        var rec344 = Ptr(to=rec344_tmp[S32(4)])
        var yec44_tmp = Arr[F64, 8](uninitialized=True)
        var yec44 = Ptr(to=yec44_tmp[S32(4)])
        var rec343_tmp = Arr[F64, 8](uninitialized=True)
        var rec343 = Ptr(to=rec343_tmp[S32(4)])
        var rec342_tmp = Arr[F64, 8](uninitialized=True)
        var rec342 = Ptr(to=rec342_tmp[S32(4)])
        var rec347_tmp = Arr[F64, 8](uninitialized=True)
        var rec347 = Ptr(to=rec347_tmp[S32(4)])
        var rec346_tmp = Arr[F64, 8](uninitialized=True)
        var rec346 = Ptr(to=rec346_tmp[S32(4)])
        var rec352_tmp = Arr[F64, 8](uninitialized=True)
        var rec352 = Ptr(to=rec352_tmp[S32(4)])
        var rec351_tmp = Arr[F64, 8](uninitialized=True)
        var rec351 = Ptr(to=rec351_tmp[S32(4)])
        var zec90 = Arr[F64, 4](uninitialized=True)
        var rec350_tmp = Arr[F64, 8](uninitialized=True)
        var rec350 = Ptr(to=rec350_tmp[S32(4)])
        var zec91 = Arr[F64, 4](uninitialized=True)
        var rec349_tmp = Arr[F64, 8](uninitialized=True)
        var rec349 = Ptr(to=rec349_tmp[S32(4)])
        var zec92 = Arr[F64, 4](uninitialized=True)
        var rec348_tmp = Arr[F64, 8](uninitialized=True)
        var rec348 = Ptr(to=rec348_tmp[S32(4)])
        var rec358_tmp = Arr[F64, 8](uninitialized=True)
        var rec358 = Ptr(to=rec358_tmp[S32(4)])
        var rec357_tmp = Arr[F64, 8](uninitialized=True)
        var rec357 = Ptr(to=rec357_tmp[S32(4)])
        var yec45_tmp = Arr[F64, 8](uninitialized=True)
        var yec45 = Ptr(to=yec45_tmp[S32(4)])
        var rec356_tmp = Arr[F64, 8](uninitialized=True)
        var rec356 = Ptr(to=rec356_tmp[S32(4)])
        var rec355_tmp = Arr[F64, 8](uninitialized=True)
        var rec355 = Ptr(to=rec355_tmp[S32(4)])
        var zec93 = Arr[F64, 4](uninitialized=True)
        var rec354_tmp = Arr[F64, 8](uninitialized=True)
        var rec354 = Ptr(to=rec354_tmp[S32(4)])
        var zec94 = Arr[F64, 4](uninitialized=True)
        var rec353_tmp = Arr[F64, 8](uninitialized=True)
        var rec353 = Ptr(to=rec353_tmp[S32(4)])
        var rec363_tmp = Arr[F64, 8](uninitialized=True)
        var rec363 = Ptr(to=rec363_tmp[S32(4)])
        var rec362_tmp = Arr[F64, 8](uninitialized=True)
        var rec362 = Ptr(to=rec362_tmp[S32(4)])
        var yec46_tmp = Arr[F64, 8](uninitialized=True)
        var yec46 = Ptr(to=yec46_tmp[S32(4)])
        var rec361_tmp = Arr[F64, 8](uninitialized=True)
        var rec361 = Ptr(to=rec361_tmp[S32(4)])
        var rec360_tmp = Arr[F64, 8](uninitialized=True)
        var rec360 = Ptr(to=rec360_tmp[S32(4)])
        var zec95 = Arr[F64, 4](uninitialized=True)
        var rec359_tmp = Arr[F64, 8](uninitialized=True)
        var rec359 = Ptr(to=rec359_tmp[S32(4)])
        var rec367_tmp = Arr[F64, 8](uninitialized=True)
        var rec367 = Ptr(to=rec367_tmp[S32(4)])
        var rec366_tmp = Arr[F64, 8](uninitialized=True)
        var rec366 = Ptr(to=rec366_tmp[S32(4)])
        var yec47_tmp = Arr[F64, 8](uninitialized=True)
        var yec47 = Ptr(to=yec47_tmp[S32(4)])
        var rec365_tmp = Arr[F64, 8](uninitialized=True)
        var rec365 = Ptr(to=rec365_tmp[S32(4)])
        var rec364_tmp = Arr[F64, 8](uninitialized=True)
        var rec364 = Ptr(to=rec364_tmp[S32(4)])
        var rec369_tmp = Arr[F64, 8](uninitialized=True)
        var rec369 = Ptr(to=rec369_tmp[S32(4)])
        var rec368_tmp = Arr[F64, 8](uninitialized=True)
        var rec368 = Ptr(to=rec368_tmp[S32(4)])
        var slow47 = (0.1) * (F64(dsp.checkbox0))
        var zec96 = Arr[F64, 4](uninitialized=True)
        var slow48 = F64(dsp.button0)
        var vec0_tmp = Arr[F64, 8](uninitialized=True)
        var vec0 = Ptr(to=vec0_tmp[S32(4)])
        var slow49 = F64(dsp.button1)
        var vec1_tmp = Arr[F64, 8](uninitialized=True)
        var vec1 = Ptr(to=vec1_tmp[S32(4)])
        var i_zec97 = Arr[S32, 4](uninitialized=True)
        var zec98 = Arr[F64, 4](uninitialized=True)
        var slow50 = (0.25) * ((1.0) - ((0.5) * (F64(dsp.button2))))
        var slow51 = F64(dsp.hslider4)
        var slow52 = pow(2.0, floor(((1.4426950408889634) * (log((dsp.const3) * (slow51)))) + (0.5)))
        var slow53 = F64(dsp.vslider0)
        var slow54 = exp(-((dsp.const2) * ((slow52) / (slow53))))
        var slow55 = F64(dsp.vslider1)
        var slow56 = exp(-((dsp.const2) * ((slow52) / (slow55))))
        var slow57 = F64(dsp.vslider2)
        var slow58 = exp(-((dsp.const2) * ((slow52) / (slow57))))
        var slow59 = F64(dsp.vslider3)
        var slow60 = (exp(-((dsp.const2) * ((slow52) / (slow59))))) / (slow32)
        var slow61 = F64(dsp.vslider4)
        var slow62 = exp(-((dsp.const2) * ((slow52) / (slow61))))
        var zec99 = Arr[F64, 4](uninitialized=True)
        var slow63 = F64(dsp.hslider5)
        var slow64 = (slow63) / (slow51)
        var slow65 = pow(23.0, floor(((0.318928988903801) * (log((dsp.const3) * ((slow51) * (pow(slow64, 0.5333333333333333)))))) + (0.5)))
        var slow66 = exp(-((dsp.const2) * ((slow65) / (slow53))))
        var slow67 = exp(-((dsp.const2) * ((slow65) / (slow55))))
        var slow68 = exp(-((dsp.const2) * ((slow65) / (slow57))))
        var slow69 = (exp(-((dsp.const2) * ((slow65) / (slow59))))) / (slow32)
        var slow70 = exp(-((dsp.const2) * ((slow65) / (slow61))))
        var zec100 = Arr[F64, 4](uninitialized=True)
        var zec101 = Arr[F64, 4](uninitialized=True)
        var slow71 = pow(11.0, floor(((0.4170323914242463) * (log((dsp.const3) * ((slow51) * (pow(slow64, 0.26666666666666666)))))) + (0.5)))
        var slow72 = exp(-((dsp.const2) * ((slow71) / (slow53))))
        var slow73 = exp(-((dsp.const2) * ((slow71) / (slow55))))
        var slow74 = exp(-((dsp.const2) * ((slow71) / (slow57))))
        var slow75 = (exp(-((dsp.const2) * ((slow71) / (slow59))))) / (slow32)
        var slow76 = exp(-((dsp.const2) * ((slow71) / (slow61))))
        var zec102 = Arr[F64, 4](uninitialized=True)
        var slow77 = pow(41.0, floor(((0.269282508064391) * (log((dsp.const3) * ((slow51) * (pow(slow64, 0.8)))))) + (0.5)))
        var slow78 = exp(-((dsp.const2) * ((slow77) / (slow53))))
        var slow79 = exp(-((dsp.const2) * ((slow77) / (slow55))))
        var slow80 = exp(-((dsp.const2) * ((slow77) / (slow57))))
        var slow81 = (exp(-((dsp.const2) * ((slow77) / (slow59))))) / (slow32)
        var slow82 = exp(-((dsp.const2) * ((slow77) / (slow61))))
        var zec103 = Arr[F64, 4](uninitialized=True)
        var zec104 = Arr[F64, 4](uninitialized=True)
        var zec105 = Arr[F64, 4](uninitialized=True)
        var slow83 = pow(5.0, floor(((0.6213349345596119) * (log((dsp.const3) * ((slow51) * (pow(slow64, 0.13333333333333333)))))) + (0.5)))
        var slow84 = exp(-((dsp.const2) * ((slow83) / (slow53))))
        var slow85 = exp(-((dsp.const2) * ((slow83) / (slow55))))
        var slow86 = exp(-((dsp.const2) * ((slow83) / (slow57))))
        var slow87 = (exp(-((dsp.const2) * ((slow83) / (slow59))))) / (slow32)
        var slow88 = exp(-((dsp.const2) * ((slow83) / (slow61))))
        var zec106 = Arr[F64, 4](uninitialized=True)
        var slow89 = pow(31.0, floor(((0.29120667621996243) * (log((dsp.const3) * ((slow51) * (pow(slow64, 0.6666666666666666)))))) + (0.5)))
        var slow90 = exp(-((dsp.const2) * ((slow89) / (slow53))))
        var slow91 = exp(-((dsp.const2) * ((slow89) / (slow55))))
        var slow92 = exp(-((dsp.const2) * ((slow89) / (slow57))))
        var slow93 = (exp(-((dsp.const2) * ((slow89) / (slow59))))) / (slow32)
        var slow94 = exp(-((dsp.const2) * ((slow89) / (slow61))))
        var zec107 = Arr[F64, 4](uninitialized=True)
        var zec108 = Arr[F64, 4](uninitialized=True)
        var slow95 = pow(17.0, floor(((0.35295612386476116) * (log((dsp.const3) * ((slow51) * (pow(slow64, 0.4)))))) + (0.5)))
        var slow96 = exp(-((dsp.const2) * ((slow95) / (slow53))))
        var slow97 = exp(-((dsp.const2) * ((slow95) / (slow55))))
        var slow98 = exp(-((dsp.const2) * ((slow95) / (slow57))))
        var slow99 = (exp(-((dsp.const2) * ((slow95) / (slow59))))) / (slow32)
        var slow100 = exp(-((dsp.const2) * ((slow95) / (slow61))))
        var zec109 = Arr[F64, 4](uninitialized=True)
        var slow101 = pow(47.0, floor(((0.25973030217227155) * (log((dsp.const3) * ((slow51) * (pow(slow64, 0.9333333333333333)))))) + (0.5)))
        var slow102 = exp(-((dsp.const2) * ((slow101) / (slow53))))
        var slow103 = exp(-((dsp.const2) * ((slow101) / (slow55))))
        var slow104 = exp(-((dsp.const2) * ((slow101) / (slow57))))
        var slow105 = (exp(-((dsp.const2) * ((slow101) / (slow59))))) / (slow32)
        var slow106 = exp(-((dsp.const2) * ((slow101) / (slow61))))
        var zec110 = Arr[F64, 4](uninitialized=True)
        var zec111 = Arr[F64, 4](uninitialized=True)
        var zec112 = Arr[F64, 4](uninitialized=True)
        var zec113 = Arr[F64, 4](uninitialized=True)
        var slow107 = pow(3.0, floor(((0.9102392266268373) * (log((dsp.const3) * ((slow51) * (pow(slow64, 0.06666666666666667)))))) + (0.5)))
        var slow108 = exp(-((dsp.const2) * ((slow107) / (slow53))))
        var slow109 = exp(-((dsp.const2) * ((slow107) / (slow55))))
        var slow110 = exp(-((dsp.const2) * ((slow107) / (slow57))))
        var slow111 = (exp(-((dsp.const2) * ((slow107) / (slow59))))) / (slow32)
        var slow112 = exp(-((dsp.const2) * ((slow107) / (slow61))))
        var zec114 = Arr[F64, 4](uninitialized=True)
        var slow113 = pow(29.0, floor(((0.2969742043733701) * (log((dsp.const3) * ((slow51) * (pow(slow64, 0.6)))))) + (0.5)))
        var slow114 = exp(-((dsp.const2) * ((slow113) / (slow53))))
        var slow115 = exp(-((dsp.const2) * ((slow113) / (slow55))))
        var slow116 = exp(-((dsp.const2) * ((slow113) / (slow57))))
        var slow117 = (exp(-((dsp.const2) * ((slow113) / (slow59))))) / (slow32)
        var slow118 = exp(-((dsp.const2) * ((slow113) / (slow61))))
        var zec115 = Arr[F64, 4](uninitialized=True)
        var zec116 = Arr[F64, 4](uninitialized=True)
        var slow119 = pow(13.0, floor(((0.3898712452512801) * (log((dsp.const3) * ((slow51) * (pow(slow64, 0.3333333333333333)))))) + (0.5)))
        var slow120 = exp(-((dsp.const2) * ((slow119) / (slow53))))
        var slow121 = exp(-((dsp.const2) * ((slow119) / (slow55))))
        var slow122 = exp(-((dsp.const2) * ((slow119) / (slow57))))
        var slow123 = (exp(-((dsp.const2) * ((slow119) / (slow59))))) / (slow32)
        var slow124 = exp(-((dsp.const2) * ((slow119) / (slow61))))
        var zec117 = Arr[F64, 4](uninitialized=True)
        var slow125 = pow(43.0, floor(((0.265872585674852) * (log((dsp.const3) * ((slow51) * (pow(slow64, 0.8666666666666667)))))) + (0.5)))
        var slow126 = exp(-((dsp.const2) * ((slow125) / (slow53))))
        var slow127 = exp(-((dsp.const2) * ((slow125) / (slow55))))
        var slow128 = exp(-((dsp.const2) * ((slow125) / (slow57))))
        var slow129 = (exp(-((dsp.const2) * ((slow125) / (slow59))))) / (slow32)
        var slow130 = exp(-((dsp.const2) * ((slow125) / (slow61))))
        var zec118 = Arr[F64, 4](uninitialized=True)
        var zec119 = Arr[F64, 4](uninitialized=True)
        var zec120 = Arr[F64, 4](uninitialized=True)
        var slow131 = pow(7.0, floor(((0.5138983423697507) * (log((dsp.const3) * ((slow51) * (pow(slow64, 0.2)))))) + (0.5)))
        var slow132 = exp(-((dsp.const2) * ((slow131) / (slow53))))
        var slow133 = exp(-((dsp.const2) * ((slow131) / (slow55))))
        var slow134 = exp(-((dsp.const2) * ((slow131) / (slow57))))
        var slow135 = (exp(-((dsp.const2) * ((slow131) / (slow59))))) / (slow32)
        var slow136 = exp(-((dsp.const2) * ((slow131) / (slow61))))
        var zec121 = Arr[F64, 4](uninitialized=True)
        var slow137 = pow(37.0, floor(((0.2769378934088574) * (log((dsp.const3) * ((slow51) * (pow(slow64, 0.7333333333333333)))))) + (0.5)))
        var slow138 = exp(-((dsp.const2) * ((slow137) / (slow53))))
        var slow139 = exp(-((dsp.const2) * ((slow137) / (slow55))))
        var slow140 = exp(-((dsp.const2) * ((slow137) / (slow57))))
        var slow141 = (exp(-((dsp.const2) * ((slow137) / (slow59))))) / (slow32)
        var slow142 = exp(-((dsp.const2) * ((slow137) / (slow61))))
        var zec122 = Arr[F64, 4](uninitialized=True)
        var zec123 = Arr[F64, 4](uninitialized=True)
        var slow143 = pow(19.0, floor(((0.3396232718951086) * (log((dsp.const3) * ((slow51) * (pow(slow64, 0.4666666666666667)))))) + (0.5)))
        var slow144 = exp(-((dsp.const2) * ((slow143) / (slow53))))
        var slow145 = exp(-((dsp.const2) * ((slow143) / (slow55))))
        var slow146 = exp(-((dsp.const2) * ((slow143) / (slow57))))
        var slow147 = (exp(-((dsp.const2) * ((slow143) / (slow59))))) / (slow32)
        var slow148 = exp(-((dsp.const2) * ((slow143) / (slow61))))
        var zec124 = Arr[F64, 4](uninitialized=True)
        var slow149 = pow(53.0, floor(((0.2518706487516997) * (log((dsp.const3) * (slow63)))) + (0.5)))
        var slow150 = exp(-((dsp.const2) * ((slow149) / (slow53))))
        var slow151 = exp(-((dsp.const2) * ((slow149) / (slow55))))
        var slow152 = exp(-((dsp.const2) * ((slow149) / (slow57))))
        var slow153 = (exp(-((dsp.const2) * ((slow149) / (slow59))))) / (slow32)
        var slow154 = exp(-((dsp.const2) * ((slow149) / (slow61))))
        var zec125 = Arr[F64, 4](uninitialized=True)
        var zec126 = Arr[F64, 4](uninitialized=True)
        var zec127 = Arr[F64, 4](uninitialized=True)
        var zec128 = Arr[F64, 4](uninitialized=True)
        var slow155 = (1.0) - (F64(dsp.checkbox1))
        var zec129 = Arr[F64, 4](uninitialized=True)
        var i_slow156 = (S32((slow52) + (-1.0))) & (S32(8191))
        var rec0_tmp = Arr[F64, 8](uninitialized=True)
        var rec0 = Ptr(to=rec0_tmp[S32(4)])
        var slow157 = F64(dsp.button3)
        var vec2_tmp = Arr[F64, 8](uninitialized=True)
        var vec2 = Ptr(to=vec2_tmp[S32(4)])
        var zec130 = Arr[F64, 4](uninitialized=True)
        var zec131 = Arr[F64, 4](uninitialized=True)
        var i_slow158 = (S32((slow107) + (-1.0))) & (S32(8191))
        var rec1_tmp = Arr[F64, 8](uninitialized=True)
        var rec1 = Ptr(to=rec1_tmp[S32(4)])
        var zec132 = Arr[F64, 4](uninitialized=True)
        var zec133 = Arr[F64, 4](uninitialized=True)
        var zec134 = Arr[F64, 4](uninitialized=True)
        var i_slow159 = (S32((slow83) + (-1.0))) & (S32(8191))
        var rec2_tmp = Arr[F64, 8](uninitialized=True)
        var rec2 = Ptr(to=rec2_tmp[S32(4)])
        var zec135 = Arr[F64, 4](uninitialized=True)
        var i_slow160 = (S32((slow131) + (-1.0))) & (S32(8191))
        var rec3_tmp = Arr[F64, 8](uninitialized=True)
        var rec3 = Ptr(to=rec3_tmp[S32(4)])
        var zec136 = Arr[F64, 4](uninitialized=True)
        var zec137 = Arr[F64, 4](uninitialized=True)
        var zec138 = Arr[F64, 4](uninitialized=True)
        var zec139 = Arr[F64, 4](uninitialized=True)
        var zec140 = Arr[F64, 4](uninitialized=True)
        var zec141 = Arr[F64, 4](uninitialized=True)
        var i_slow161 = (S32((slow71) + (-1.0))) & (S32(8191))
        var rec4_tmp = Arr[F64, 8](uninitialized=True)
        var rec4 = Ptr(to=rec4_tmp[S32(4)])
        var i_slow162 = (S32((slow119) + (-1.0))) & (S32(8191))
        var rec5_tmp = Arr[F64, 8](uninitialized=True)
        var rec5 = Ptr(to=rec5_tmp[S32(4)])
        var zec142 = Arr[F64, 4](uninitialized=True)
        var zec143 = Arr[F64, 4](uninitialized=True)
        var i_slow163 = (S32((slow95) + (-1.0))) & (S32(8191))
        var rec6_tmp = Arr[F64, 8](uninitialized=True)
        var rec6 = Ptr(to=rec6_tmp[S32(4)])
        var i_slow164 = (S32((slow143) + (-1.0))) & (S32(8191))
        var rec7_tmp = Arr[F64, 8](uninitialized=True)
        var rec7 = Ptr(to=rec7_tmp[S32(4)])
        var zec144 = Arr[F64, 4](uninitialized=True)
        var zec145 = Arr[F64, 4](uninitialized=True)
        var zec146 = Arr[F64, 4](uninitialized=True)
        var zec147 = Arr[F64, 4](uninitialized=True)
        var zec148 = Arr[F64, 4](uninitialized=True)
        var zec149 = Arr[F64, 4](uninitialized=True)
        var zec150 = Arr[F64, 4](uninitialized=True)
        var zec151 = Arr[F64, 4](uninitialized=True)
        var zec152 = Arr[F64, 4](uninitialized=True)
        var zec153 = Arr[F64, 4](uninitialized=True)
        var zec154 = Arr[F64, 4](uninitialized=True)
        var zec155 = Arr[F64, 4](uninitialized=True)
        var zec156 = Arr[F64, 4](uninitialized=True)
        var zec157 = Arr[F64, 4](uninitialized=True)
        var i_slow165 = (S32((slow65) + (-1.0))) & (S32(8191))
        var rec8_tmp = Arr[F64, 8](uninitialized=True)
        var rec8 = Ptr(to=rec8_tmp[S32(4)])
        var i_slow166 = (S32((slow113) + (-1.0))) & (S32(8191))
        var rec9_tmp = Arr[F64, 8](uninitialized=True)
        var rec9 = Ptr(to=rec9_tmp[S32(4)])
        var zec158 = Arr[F64, 4](uninitialized=True)
        var zec159 = Arr[F64, 4](uninitialized=True)
        var i_slow167 = (S32((slow89) + (-1.0))) & (S32(8191))
        var rec10_tmp = Arr[F64, 8](uninitialized=True)
        var rec10 = Ptr(to=rec10_tmp[S32(4)])
        var i_slow168 = (S32((slow137) + (-1.0))) & (S32(8191))
        var rec11_tmp = Arr[F64, 8](uninitialized=True)
        var rec11 = Ptr(to=rec11_tmp[S32(4)])
        var zec160 = Arr[F64, 4](uninitialized=True)
        var zec161 = Arr[F64, 4](uninitialized=True)
        var zec162 = Arr[F64, 4](uninitialized=True)
        var zec163 = Arr[F64, 4](uninitialized=True)
        var zec164 = Arr[F64, 4](uninitialized=True)
        var zec165 = Arr[F64, 4](uninitialized=True)
        var i_slow169 = (S32((slow77) + (-1.0))) & (S32(8191))
        var rec12_tmp = Arr[F64, 8](uninitialized=True)
        var rec12 = Ptr(to=rec12_tmp[S32(4)])
        var i_slow170 = (S32((slow125) + (-1.0))) & (S32(8191))
        var rec13_tmp = Arr[F64, 8](uninitialized=True)
        var rec13 = Ptr(to=rec13_tmp[S32(4)])
        var zec166 = Arr[F64, 4](uninitialized=True)
        var zec167 = Arr[F64, 4](uninitialized=True)
        var i_slow171 = (S32((slow101) + (-1.0))) & (S32(8191))
        var rec14_tmp = Arr[F64, 8](uninitialized=True)
        var rec14 = Ptr(to=rec14_tmp[S32(4)])
        var i_slow172 = (S32((slow149) + (-1.0))) & (S32(8191))
        var rec15_tmp = Arr[F64, 8](uninitialized=True)
        var rec15 = Ptr(to=rec15_tmp[S32(4)])
        var slow173 = pow(1e+01, (0.05) * (F64(dsp.hslider6)))
        while vindex <= end:
            var input0 = Ptr(to=input0_ptr[unsafe_offset = vindex])
            var input1 = Ptr(to=input1_ptr[unsafe_offset = vindex])
            var output0 = Ptr(to=output0_ptr[unsafe_offset = vindex])
            var output1 = Ptr(to=output1_ptr[unsafe_offset = vindex])
            vstore(i_rec17_tmp, vload(dsp.i_rec17_perm))
            comptime for i in range(vsize):
                i_rec17[unsafe_offset = i] = ((S32(1103515245)) * (i_rec17[unsafe_offset = (i) - (S32(1))])) + (S32(12345))
            vstore(dsp.i_rec17_perm, vload(i_rec17_tmp, vsize))
            vstore(rec16_tmp, vload[H](dsp.rec16_perm))
            vstore(rec16_tmp, vload[H](dsp.rec16_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec16[unsafe_offset = i] = (((0.5221894) * (rec16[unsafe_offset = (i) - (S32(3))])) + (((4.656612875245797e-10) * (F64(i_rec17[unsafe_offset = i]))) + ((2.494956002) * (rec16[unsafe_offset = (i) - (S32(1))])))) - ((2.017265875) * (rec16[unsafe_offset = (i) - (S32(2))]))
            vstore(dsp.rec16_perm, vload[H](rec16_tmp, vsize))
            vstore(dsp.rec16_perm, vload[H](rec16_tmp, vsize + hsize), hsize)
            vstore(zec96, (F64Vec(slow47)) * ((((F64Vec(0.049922035)) * (vload[H](rec16))) + ((F64Vec(0.050612699)) * (vload[H](rec16, - S32(2))))) - (((F64Vec(0.095993537)) * (vload[H](rec16, - S32(1)))) + ((F64Vec(0.004408786)) * (vload[H](rec16, - S32(3)))))))
            vstore(zec96, (F64Vec(slow47)) * ((((F64Vec(0.049922035)) * (vload[H](rec16, hsize))) + ((F64Vec(0.050612699)) * (vload[H](rec16, - S32(2) + hsize)))) - (((F64Vec(0.095993537)) * (vload[H](rec16, - S32(1) + hsize))) + ((F64Vec(0.004408786)) * (vload[H](rec16, - S32(3) + hsize))))), hsize)
            vstore(vec0_tmp, vload[H](dsp.vec0_perm))
            vstore(vec0_tmp, vload[H](dsp.vec0_perm, hsize), hsize)
            vstore[wfaust](vec0, slow48)
            vstore(dsp.vec0_perm, vload[H](vec0_tmp, vsize))
            vstore(dsp.vec0_perm, vload[H](vec0_tmp, vsize + hsize), hsize)
            vstore(vec1_tmp, vload[H](dsp.vec1_perm))
            vstore(vec1_tmp, vload[H](dsp.vec1_perm, hsize), hsize)
            vstore[wfaust](vec1, slow49)
            vstore(dsp.vec1_perm, vload[H](vec1_tmp, vsize))
            vstore(dsp.vec1_perm, vload[H](vec1_tmp, vsize + hsize), hsize)
            vstore(i_zec97, (((F64Vec(slow49)) - (vload[H](vec1, - S32(1)))).gt(F64Vec(0.0)).cast[s32]()))
            vstore(i_zec97, (((F64Vec(slow49)) - (vload[H](vec1, - S32(1) + hsize))).gt(F64Vec(0.0)).cast[s32]()), hsize)
            vstore(zec98, (((((F64Vec(slow48)) - (vload[H](vec0, - S32(1)))).gt(F64Vec(0.0)).cast[s32]())) + (vload[H](i_zec97))).cast[f64]())
            vstore(zec98, (((((F64Vec(slow48)) - (vload[H](vec0, - S32(1) + hsize))).gt(F64Vec(0.0)).cast[s32]())) + (vload[H](i_zec97, hsize))).cast[f64](), hsize)
            vstore(zec129, (F64Vec(slow155)) * ((vload[H](input0)).cast[f64]()))
            vstore(zec129, (F64Vec(slow155)) * ((vload[H](input0, hsize)).cast[f64]()), hsize)
            vstore(vec2_tmp, vload[H](dsp.vec2_perm))
            vstore(vec2_tmp, vload[H](dsp.vec2_perm, hsize), hsize)
            vstore[wfaust](vec2, slow157)
            vstore(dsp.vec2_perm, vload[H](vec2_tmp, vsize))
            vstore(dsp.vec2_perm, vload[H](vec2_tmp, vsize + hsize), hsize)
            vstore(zec130, ((vload[H](i_zec97)) + ((((F64Vec(slow157)) - (vload[H](vec2, - S32(1)))).gt(F64Vec(0.0)).cast[s32]()))).cast[f64]())
            vstore(zec130, ((vload[H](i_zec97, hsize)) + ((((F64Vec(slow157)) - (vload[H](vec2, - S32(1) + hsize))).gt(F64Vec(0.0)).cast[s32]()))).cast[f64](), hsize)
            vstore(zec131, (F64Vec(slow155)) * ((vload[H](input1)).cast[f64]()))
            vstore(zec131, (F64Vec(slow155)) * ((vload[H](input1, hsize)).cast[f64]()), hsize)
            vstore(zec132, ((vload[H](zec129)) + (vload[H](zec98))) + (vload[H](zec96)))
            vstore(zec132, ((vload[H](zec129, hsize)) + (vload[H](zec98, hsize))) + (vload[H](zec96, hsize)), hsize)
            vstore(zec135, (vload[H](zec130)) + ((vload[H](zec96)) + (vload[H](zec131))))
            vstore(zec135, (vload[H](zec130, hsize)) + ((vload[H](zec96, hsize)) + (vload[H](zec131, hsize))), hsize)
            vstore(rec22_tmp, vload[H](dsp.rec22_perm))
            vstore(rec22_tmp, vload[H](dsp.rec22_perm, hsize), hsize)
            vstore(rec21_tmp, vload[H](dsp.rec21_perm))
            vstore(rec21_tmp, vload[H](dsp.rec21_perm, hsize), hsize)
            vstore(rec20_tmp, vload[H](dsp.rec20_perm))
            vstore(rec20_tmp, vload[H](dsp.rec20_perm, hsize), hsize)
            vstore(rec19_tmp, vload[H](dsp.rec19_perm))
            vstore(rec19_tmp, vload[H](dsp.rec19_perm, hsize), hsize)
            vstore(rec18_tmp, vload[H](dsp.rec18_perm))
            vstore(rec18_tmp, vload[H](dsp.rec18_perm, hsize), hsize)
            vstore(rec28_tmp, vload[H](dsp.rec28_perm))
            vstore(rec28_tmp, vload[H](dsp.rec28_perm, hsize), hsize)
            vstore(rec27_tmp, vload[H](dsp.rec27_perm))
            vstore(rec27_tmp, vload[H](dsp.rec27_perm, hsize), hsize)
            vstore(yec0_tmp, vload[H](dsp.yec0_perm))
            vstore(yec0_tmp, vload[H](dsp.yec0_perm, hsize), hsize)
            vstore(rec26_tmp, vload[H](dsp.rec26_perm))
            vstore(rec26_tmp, vload[H](dsp.rec26_perm, hsize), hsize)
            vstore(rec25_tmp, vload[H](dsp.rec25_perm))
            vstore(rec25_tmp, vload[H](dsp.rec25_perm, hsize), hsize)
            vstore(rec24_tmp, vload[H](dsp.rec24_perm))
            vstore(rec24_tmp, vload[H](dsp.rec24_perm, hsize), hsize)
            vstore(rec23_tmp, vload[H](dsp.rec23_perm))
            vstore(rec23_tmp, vload[H](dsp.rec23_perm, hsize), hsize)
            vstore(rec33_tmp, vload[H](dsp.rec33_perm))
            vstore(rec33_tmp, vload[H](dsp.rec33_perm, hsize), hsize)
            vstore(rec32_tmp, vload[H](dsp.rec32_perm))
            vstore(rec32_tmp, vload[H](dsp.rec32_perm, hsize), hsize)
            vstore(yec1_tmp, vload[H](dsp.yec1_perm))
            vstore(yec1_tmp, vload[H](dsp.yec1_perm, hsize), hsize)
            vstore(rec31_tmp, vload[H](dsp.rec31_perm))
            vstore(rec31_tmp, vload[H](dsp.rec31_perm, hsize), hsize)
            vstore(rec30_tmp, vload[H](dsp.rec30_perm))
            vstore(rec30_tmp, vload[H](dsp.rec30_perm, hsize), hsize)
            vstore(rec29_tmp, vload[H](dsp.rec29_perm))
            vstore(rec29_tmp, vload[H](dsp.rec29_perm, hsize), hsize)
            vstore(rec37_tmp, vload[H](dsp.rec37_perm))
            vstore(rec37_tmp, vload[H](dsp.rec37_perm, hsize), hsize)
            vstore(rec36_tmp, vload[H](dsp.rec36_perm))
            vstore(rec36_tmp, vload[H](dsp.rec36_perm, hsize), hsize)
            vstore(yec2_tmp, vload[H](dsp.yec2_perm))
            vstore(yec2_tmp, vload[H](dsp.yec2_perm, hsize), hsize)
            vstore(rec35_tmp, vload[H](dsp.rec35_perm))
            vstore(rec35_tmp, vload[H](dsp.rec35_perm, hsize), hsize)
            vstore(rec34_tmp, vload[H](dsp.rec34_perm))
            vstore(rec34_tmp, vload[H](dsp.rec34_perm, hsize), hsize)
            vstore(rec39_tmp, vload[H](dsp.rec39_perm))
            vstore(rec39_tmp, vload[H](dsp.rec39_perm, hsize), hsize)
            vstore(rec38_tmp, vload[H](dsp.rec38_perm))
            vstore(rec38_tmp, vload[H](dsp.rec38_perm, hsize), hsize)
            vstore(rec44_tmp, vload[H](dsp.rec44_perm))
            vstore(rec44_tmp, vload[H](dsp.rec44_perm, hsize), hsize)
            vstore(rec43_tmp, vload[H](dsp.rec43_perm))
            vstore(rec43_tmp, vload[H](dsp.rec43_perm, hsize), hsize)
            vstore(rec42_tmp, vload[H](dsp.rec42_perm))
            vstore(rec42_tmp, vload[H](dsp.rec42_perm, hsize), hsize)
            vstore(rec41_tmp, vload[H](dsp.rec41_perm))
            vstore(rec41_tmp, vload[H](dsp.rec41_perm, hsize), hsize)
            vstore(rec40_tmp, vload[H](dsp.rec40_perm))
            vstore(rec40_tmp, vload[H](dsp.rec40_perm, hsize), hsize)
            vstore(rec50_tmp, vload[H](dsp.rec50_perm))
            vstore(rec50_tmp, vload[H](dsp.rec50_perm, hsize), hsize)
            vstore(rec49_tmp, vload[H](dsp.rec49_perm))
            vstore(rec49_tmp, vload[H](dsp.rec49_perm, hsize), hsize)
            vstore(yec3_tmp, vload[H](dsp.yec3_perm))
            vstore(yec3_tmp, vload[H](dsp.yec3_perm, hsize), hsize)
            vstore(rec48_tmp, vload[H](dsp.rec48_perm))
            vstore(rec48_tmp, vload[H](dsp.rec48_perm, hsize), hsize)
            vstore(rec47_tmp, vload[H](dsp.rec47_perm))
            vstore(rec47_tmp, vload[H](dsp.rec47_perm, hsize), hsize)
            vstore(rec46_tmp, vload[H](dsp.rec46_perm))
            vstore(rec46_tmp, vload[H](dsp.rec46_perm, hsize), hsize)
            vstore(rec45_tmp, vload[H](dsp.rec45_perm))
            vstore(rec45_tmp, vload[H](dsp.rec45_perm, hsize), hsize)
            vstore(rec55_tmp, vload[H](dsp.rec55_perm))
            vstore(rec55_tmp, vload[H](dsp.rec55_perm, hsize), hsize)
            vstore(rec54_tmp, vload[H](dsp.rec54_perm))
            vstore(rec54_tmp, vload[H](dsp.rec54_perm, hsize), hsize)
            vstore(yec4_tmp, vload[H](dsp.yec4_perm))
            vstore(yec4_tmp, vload[H](dsp.yec4_perm, hsize), hsize)
            vstore(rec53_tmp, vload[H](dsp.rec53_perm))
            vstore(rec53_tmp, vload[H](dsp.rec53_perm, hsize), hsize)
            vstore(rec52_tmp, vload[H](dsp.rec52_perm))
            vstore(rec52_tmp, vload[H](dsp.rec52_perm, hsize), hsize)
            vstore(rec51_tmp, vload[H](dsp.rec51_perm))
            vstore(rec51_tmp, vload[H](dsp.rec51_perm, hsize), hsize)
            vstore(rec59_tmp, vload[H](dsp.rec59_perm))
            vstore(rec59_tmp, vload[H](dsp.rec59_perm, hsize), hsize)
            vstore(rec58_tmp, vload[H](dsp.rec58_perm))
            vstore(rec58_tmp, vload[H](dsp.rec58_perm, hsize), hsize)
            vstore(yec5_tmp, vload[H](dsp.yec5_perm))
            vstore(yec5_tmp, vload[H](dsp.yec5_perm, hsize), hsize)
            vstore(rec57_tmp, vload[H](dsp.rec57_perm))
            vstore(rec57_tmp, vload[H](dsp.rec57_perm, hsize), hsize)
            vstore(rec56_tmp, vload[H](dsp.rec56_perm))
            vstore(rec56_tmp, vload[H](dsp.rec56_perm, hsize), hsize)
            vstore(rec61_tmp, vload[H](dsp.rec61_perm))
            vstore(rec61_tmp, vload[H](dsp.rec61_perm, hsize), hsize)
            vstore(rec60_tmp, vload[H](dsp.rec60_perm))
            vstore(rec60_tmp, vload[H](dsp.rec60_perm, hsize), hsize)
            vstore(rec66_tmp, vload[H](dsp.rec66_perm))
            vstore(rec66_tmp, vload[H](dsp.rec66_perm, hsize), hsize)
            vstore(rec65_tmp, vload[H](dsp.rec65_perm))
            vstore(rec65_tmp, vload[H](dsp.rec65_perm, hsize), hsize)
            vstore(rec64_tmp, vload[H](dsp.rec64_perm))
            vstore(rec64_tmp, vload[H](dsp.rec64_perm, hsize), hsize)
            vstore(rec63_tmp, vload[H](dsp.rec63_perm))
            vstore(rec63_tmp, vload[H](dsp.rec63_perm, hsize), hsize)
            vstore(rec62_tmp, vload[H](dsp.rec62_perm))
            vstore(rec62_tmp, vload[H](dsp.rec62_perm, hsize), hsize)
            vstore(rec72_tmp, vload[H](dsp.rec72_perm))
            vstore(rec72_tmp, vload[H](dsp.rec72_perm, hsize), hsize)
            vstore(rec71_tmp, vload[H](dsp.rec71_perm))
            vstore(rec71_tmp, vload[H](dsp.rec71_perm, hsize), hsize)
            vstore(yec6_tmp, vload[H](dsp.yec6_perm))
            vstore(yec6_tmp, vload[H](dsp.yec6_perm, hsize), hsize)
            vstore(rec70_tmp, vload[H](dsp.rec70_perm))
            vstore(rec70_tmp, vload[H](dsp.rec70_perm, hsize), hsize)
            vstore(rec69_tmp, vload[H](dsp.rec69_perm))
            vstore(rec69_tmp, vload[H](dsp.rec69_perm, hsize), hsize)
            vstore(rec68_tmp, vload[H](dsp.rec68_perm))
            vstore(rec68_tmp, vload[H](dsp.rec68_perm, hsize), hsize)
            vstore(rec67_tmp, vload[H](dsp.rec67_perm))
            vstore(rec67_tmp, vload[H](dsp.rec67_perm, hsize), hsize)
            vstore(rec77_tmp, vload[H](dsp.rec77_perm))
            vstore(rec77_tmp, vload[H](dsp.rec77_perm, hsize), hsize)
            vstore(rec76_tmp, vload[H](dsp.rec76_perm))
            vstore(rec76_tmp, vload[H](dsp.rec76_perm, hsize), hsize)
            vstore(yec7_tmp, vload[H](dsp.yec7_perm))
            vstore(yec7_tmp, vload[H](dsp.yec7_perm, hsize), hsize)
            vstore(rec75_tmp, vload[H](dsp.rec75_perm))
            vstore(rec75_tmp, vload[H](dsp.rec75_perm, hsize), hsize)
            vstore(rec74_tmp, vload[H](dsp.rec74_perm))
            vstore(rec74_tmp, vload[H](dsp.rec74_perm, hsize), hsize)
            vstore(rec73_tmp, vload[H](dsp.rec73_perm))
            vstore(rec73_tmp, vload[H](dsp.rec73_perm, hsize), hsize)
            vstore(rec81_tmp, vload[H](dsp.rec81_perm))
            vstore(rec81_tmp, vload[H](dsp.rec81_perm, hsize), hsize)
            vstore(rec80_tmp, vload[H](dsp.rec80_perm))
            vstore(rec80_tmp, vload[H](dsp.rec80_perm, hsize), hsize)
            vstore(yec8_tmp, vload[H](dsp.yec8_perm))
            vstore(yec8_tmp, vload[H](dsp.yec8_perm, hsize), hsize)
            vstore(rec79_tmp, vload[H](dsp.rec79_perm))
            vstore(rec79_tmp, vload[H](dsp.rec79_perm, hsize), hsize)
            vstore(rec78_tmp, vload[H](dsp.rec78_perm))
            vstore(rec78_tmp, vload[H](dsp.rec78_perm, hsize), hsize)
            vstore(rec83_tmp, vload[H](dsp.rec83_perm))
            vstore(rec83_tmp, vload[H](dsp.rec83_perm, hsize), hsize)
            vstore(rec82_tmp, vload[H](dsp.rec82_perm))
            vstore(rec82_tmp, vload[H](dsp.rec82_perm, hsize), hsize)
            vstore(rec88_tmp, vload[H](dsp.rec88_perm))
            vstore(rec88_tmp, vload[H](dsp.rec88_perm, hsize), hsize)
            vstore(rec87_tmp, vload[H](dsp.rec87_perm))
            vstore(rec87_tmp, vload[H](dsp.rec87_perm, hsize), hsize)
            vstore(rec86_tmp, vload[H](dsp.rec86_perm))
            vstore(rec86_tmp, vload[H](dsp.rec86_perm, hsize), hsize)
            vstore(rec85_tmp, vload[H](dsp.rec85_perm))
            vstore(rec85_tmp, vload[H](dsp.rec85_perm, hsize), hsize)
            vstore(rec84_tmp, vload[H](dsp.rec84_perm))
            vstore(rec84_tmp, vload[H](dsp.rec84_perm, hsize), hsize)
            vstore(rec94_tmp, vload[H](dsp.rec94_perm))
            vstore(rec94_tmp, vload[H](dsp.rec94_perm, hsize), hsize)
            vstore(rec93_tmp, vload[H](dsp.rec93_perm))
            vstore(rec93_tmp, vload[H](dsp.rec93_perm, hsize), hsize)
            vstore(yec9_tmp, vload[H](dsp.yec9_perm))
            vstore(yec9_tmp, vload[H](dsp.yec9_perm, hsize), hsize)
            vstore(rec92_tmp, vload[H](dsp.rec92_perm))
            vstore(rec92_tmp, vload[H](dsp.rec92_perm, hsize), hsize)
            vstore(rec91_tmp, vload[H](dsp.rec91_perm))
            vstore(rec91_tmp, vload[H](dsp.rec91_perm, hsize), hsize)
            vstore(rec90_tmp, vload[H](dsp.rec90_perm))
            vstore(rec90_tmp, vload[H](dsp.rec90_perm, hsize), hsize)
            vstore(rec89_tmp, vload[H](dsp.rec89_perm))
            vstore(rec89_tmp, vload[H](dsp.rec89_perm, hsize), hsize)
            vstore(rec99_tmp, vload[H](dsp.rec99_perm))
            vstore(rec99_tmp, vload[H](dsp.rec99_perm, hsize), hsize)
            vstore(rec98_tmp, vload[H](dsp.rec98_perm))
            vstore(rec98_tmp, vload[H](dsp.rec98_perm, hsize), hsize)
            vstore(yec10_tmp, vload[H](dsp.yec10_perm))
            vstore(yec10_tmp, vload[H](dsp.yec10_perm, hsize), hsize)
            vstore(rec97_tmp, vload[H](dsp.rec97_perm))
            vstore(rec97_tmp, vload[H](dsp.rec97_perm, hsize), hsize)
            vstore(rec96_tmp, vload[H](dsp.rec96_perm))
            vstore(rec96_tmp, vload[H](dsp.rec96_perm, hsize), hsize)
            vstore(rec95_tmp, vload[H](dsp.rec95_perm))
            vstore(rec95_tmp, vload[H](dsp.rec95_perm, hsize), hsize)
            vstore(rec103_tmp, vload[H](dsp.rec103_perm))
            vstore(rec103_tmp, vload[H](dsp.rec103_perm, hsize), hsize)
            vstore(rec102_tmp, vload[H](dsp.rec102_perm))
            vstore(rec102_tmp, vload[H](dsp.rec102_perm, hsize), hsize)
            vstore(yec11_tmp, vload[H](dsp.yec11_perm))
            vstore(yec11_tmp, vload[H](dsp.yec11_perm, hsize), hsize)
            vstore(rec101_tmp, vload[H](dsp.rec101_perm))
            vstore(rec101_tmp, vload[H](dsp.rec101_perm, hsize), hsize)
            vstore(rec100_tmp, vload[H](dsp.rec100_perm))
            vstore(rec100_tmp, vload[H](dsp.rec100_perm, hsize), hsize)
            vstore(rec105_tmp, vload[H](dsp.rec105_perm))
            vstore(rec105_tmp, vload[H](dsp.rec105_perm, hsize), hsize)
            vstore(rec104_tmp, vload[H](dsp.rec104_perm))
            vstore(rec104_tmp, vload[H](dsp.rec104_perm, hsize), hsize)
            vstore(rec110_tmp, vload[H](dsp.rec110_perm))
            vstore(rec110_tmp, vload[H](dsp.rec110_perm, hsize), hsize)
            vstore(rec109_tmp, vload[H](dsp.rec109_perm))
            vstore(rec109_tmp, vload[H](dsp.rec109_perm, hsize), hsize)
            vstore(rec108_tmp, vload[H](dsp.rec108_perm))
            vstore(rec108_tmp, vload[H](dsp.rec108_perm, hsize), hsize)
            vstore(rec107_tmp, vload[H](dsp.rec107_perm))
            vstore(rec107_tmp, vload[H](dsp.rec107_perm, hsize), hsize)
            vstore(rec106_tmp, vload[H](dsp.rec106_perm))
            vstore(rec106_tmp, vload[H](dsp.rec106_perm, hsize), hsize)
            vstore(rec116_tmp, vload[H](dsp.rec116_perm))
            vstore(rec116_tmp, vload[H](dsp.rec116_perm, hsize), hsize)
            vstore(rec115_tmp, vload[H](dsp.rec115_perm))
            vstore(rec115_tmp, vload[H](dsp.rec115_perm, hsize), hsize)
            vstore(yec12_tmp, vload[H](dsp.yec12_perm))
            vstore(yec12_tmp, vload[H](dsp.yec12_perm, hsize), hsize)
            vstore(rec114_tmp, vload[H](dsp.rec114_perm))
            vstore(rec114_tmp, vload[H](dsp.rec114_perm, hsize), hsize)
            vstore(rec113_tmp, vload[H](dsp.rec113_perm))
            vstore(rec113_tmp, vload[H](dsp.rec113_perm, hsize), hsize)
            vstore(rec112_tmp, vload[H](dsp.rec112_perm))
            vstore(rec112_tmp, vload[H](dsp.rec112_perm, hsize), hsize)
            vstore(rec111_tmp, vload[H](dsp.rec111_perm))
            vstore(rec111_tmp, vload[H](dsp.rec111_perm, hsize), hsize)
            vstore(rec121_tmp, vload[H](dsp.rec121_perm))
            vstore(rec121_tmp, vload[H](dsp.rec121_perm, hsize), hsize)
            vstore(rec120_tmp, vload[H](dsp.rec120_perm))
            vstore(rec120_tmp, vload[H](dsp.rec120_perm, hsize), hsize)
            vstore(yec13_tmp, vload[H](dsp.yec13_perm))
            vstore(yec13_tmp, vload[H](dsp.yec13_perm, hsize), hsize)
            vstore(rec119_tmp, vload[H](dsp.rec119_perm))
            vstore(rec119_tmp, vload[H](dsp.rec119_perm, hsize), hsize)
            vstore(rec118_tmp, vload[H](dsp.rec118_perm))
            vstore(rec118_tmp, vload[H](dsp.rec118_perm, hsize), hsize)
            vstore(rec117_tmp, vload[H](dsp.rec117_perm))
            vstore(rec117_tmp, vload[H](dsp.rec117_perm, hsize), hsize)
            vstore(rec125_tmp, vload[H](dsp.rec125_perm))
            vstore(rec125_tmp, vload[H](dsp.rec125_perm, hsize), hsize)
            vstore(rec124_tmp, vload[H](dsp.rec124_perm))
            vstore(rec124_tmp, vload[H](dsp.rec124_perm, hsize), hsize)
            vstore(yec14_tmp, vload[H](dsp.yec14_perm))
            vstore(yec14_tmp, vload[H](dsp.yec14_perm, hsize), hsize)
            vstore(rec123_tmp, vload[H](dsp.rec123_perm))
            vstore(rec123_tmp, vload[H](dsp.rec123_perm, hsize), hsize)
            vstore(rec122_tmp, vload[H](dsp.rec122_perm))
            vstore(rec122_tmp, vload[H](dsp.rec122_perm, hsize), hsize)
            vstore(rec127_tmp, vload[H](dsp.rec127_perm))
            vstore(rec127_tmp, vload[H](dsp.rec127_perm, hsize), hsize)
            vstore(rec126_tmp, vload[H](dsp.rec126_perm))
            vstore(rec126_tmp, vload[H](dsp.rec126_perm, hsize), hsize)
            vstore(rec132_tmp, vload[H](dsp.rec132_perm))
            vstore(rec132_tmp, vload[H](dsp.rec132_perm, hsize), hsize)
            vstore(rec131_tmp, vload[H](dsp.rec131_perm))
            vstore(rec131_tmp, vload[H](dsp.rec131_perm, hsize), hsize)
            vstore(rec130_tmp, vload[H](dsp.rec130_perm))
            vstore(rec130_tmp, vload[H](dsp.rec130_perm, hsize), hsize)
            vstore(rec129_tmp, vload[H](dsp.rec129_perm))
            vstore(rec129_tmp, vload[H](dsp.rec129_perm, hsize), hsize)
            vstore(rec128_tmp, vload[H](dsp.rec128_perm))
            vstore(rec128_tmp, vload[H](dsp.rec128_perm, hsize), hsize)
            vstore(rec138_tmp, vload[H](dsp.rec138_perm))
            vstore(rec138_tmp, vload[H](dsp.rec138_perm, hsize), hsize)
            vstore(rec137_tmp, vload[H](dsp.rec137_perm))
            vstore(rec137_tmp, vload[H](dsp.rec137_perm, hsize), hsize)
            vstore(yec15_tmp, vload[H](dsp.yec15_perm))
            vstore(yec15_tmp, vload[H](dsp.yec15_perm, hsize), hsize)
            vstore(rec136_tmp, vload[H](dsp.rec136_perm))
            vstore(rec136_tmp, vload[H](dsp.rec136_perm, hsize), hsize)
            vstore(rec135_tmp, vload[H](dsp.rec135_perm))
            vstore(rec135_tmp, vload[H](dsp.rec135_perm, hsize), hsize)
            vstore(rec134_tmp, vload[H](dsp.rec134_perm))
            vstore(rec134_tmp, vload[H](dsp.rec134_perm, hsize), hsize)
            vstore(rec133_tmp, vload[H](dsp.rec133_perm))
            vstore(rec133_tmp, vload[H](dsp.rec133_perm, hsize), hsize)
            vstore(rec143_tmp, vload[H](dsp.rec143_perm))
            vstore(rec143_tmp, vload[H](dsp.rec143_perm, hsize), hsize)
            vstore(rec142_tmp, vload[H](dsp.rec142_perm))
            vstore(rec142_tmp, vload[H](dsp.rec142_perm, hsize), hsize)
            vstore(yec16_tmp, vload[H](dsp.yec16_perm))
            vstore(yec16_tmp, vload[H](dsp.yec16_perm, hsize), hsize)
            vstore(rec141_tmp, vload[H](dsp.rec141_perm))
            vstore(rec141_tmp, vload[H](dsp.rec141_perm, hsize), hsize)
            vstore(rec140_tmp, vload[H](dsp.rec140_perm))
            vstore(rec140_tmp, vload[H](dsp.rec140_perm, hsize), hsize)
            vstore(rec139_tmp, vload[H](dsp.rec139_perm))
            vstore(rec139_tmp, vload[H](dsp.rec139_perm, hsize), hsize)
            vstore(rec147_tmp, vload[H](dsp.rec147_perm))
            vstore(rec147_tmp, vload[H](dsp.rec147_perm, hsize), hsize)
            vstore(rec146_tmp, vload[H](dsp.rec146_perm))
            vstore(rec146_tmp, vload[H](dsp.rec146_perm, hsize), hsize)
            vstore(yec17_tmp, vload[H](dsp.yec17_perm))
            vstore(yec17_tmp, vload[H](dsp.yec17_perm, hsize), hsize)
            vstore(rec145_tmp, vload[H](dsp.rec145_perm))
            vstore(rec145_tmp, vload[H](dsp.rec145_perm, hsize), hsize)
            vstore(rec144_tmp, vload[H](dsp.rec144_perm))
            vstore(rec144_tmp, vload[H](dsp.rec144_perm, hsize), hsize)
            vstore(rec149_tmp, vload[H](dsp.rec149_perm))
            vstore(rec149_tmp, vload[H](dsp.rec149_perm, hsize), hsize)
            vstore(rec148_tmp, vload[H](dsp.rec148_perm))
            vstore(rec148_tmp, vload[H](dsp.rec148_perm, hsize), hsize)
            vstore(rec154_tmp, vload[H](dsp.rec154_perm))
            vstore(rec154_tmp, vload[H](dsp.rec154_perm, hsize), hsize)
            vstore(rec153_tmp, vload[H](dsp.rec153_perm))
            vstore(rec153_tmp, vload[H](dsp.rec153_perm, hsize), hsize)
            vstore(rec152_tmp, vload[H](dsp.rec152_perm))
            vstore(rec152_tmp, vload[H](dsp.rec152_perm, hsize), hsize)
            vstore(rec151_tmp, vload[H](dsp.rec151_perm))
            vstore(rec151_tmp, vload[H](dsp.rec151_perm, hsize), hsize)
            vstore(rec150_tmp, vload[H](dsp.rec150_perm))
            vstore(rec150_tmp, vload[H](dsp.rec150_perm, hsize), hsize)
            vstore(rec160_tmp, vload[H](dsp.rec160_perm))
            vstore(rec160_tmp, vload[H](dsp.rec160_perm, hsize), hsize)
            vstore(rec159_tmp, vload[H](dsp.rec159_perm))
            vstore(rec159_tmp, vload[H](dsp.rec159_perm, hsize), hsize)
            vstore(yec18_tmp, vload[H](dsp.yec18_perm))
            vstore(yec18_tmp, vload[H](dsp.yec18_perm, hsize), hsize)
            vstore(rec158_tmp, vload[H](dsp.rec158_perm))
            vstore(rec158_tmp, vload[H](dsp.rec158_perm, hsize), hsize)
            vstore(rec157_tmp, vload[H](dsp.rec157_perm))
            vstore(rec157_tmp, vload[H](dsp.rec157_perm, hsize), hsize)
            vstore(rec156_tmp, vload[H](dsp.rec156_perm))
            vstore(rec156_tmp, vload[H](dsp.rec156_perm, hsize), hsize)
            vstore(rec155_tmp, vload[H](dsp.rec155_perm))
            vstore(rec155_tmp, vload[H](dsp.rec155_perm, hsize), hsize)
            vstore(rec165_tmp, vload[H](dsp.rec165_perm))
            vstore(rec165_tmp, vload[H](dsp.rec165_perm, hsize), hsize)
            vstore(rec164_tmp, vload[H](dsp.rec164_perm))
            vstore(rec164_tmp, vload[H](dsp.rec164_perm, hsize), hsize)
            vstore(yec19_tmp, vload[H](dsp.yec19_perm))
            vstore(yec19_tmp, vload[H](dsp.yec19_perm, hsize), hsize)
            vstore(rec163_tmp, vload[H](dsp.rec163_perm))
            vstore(rec163_tmp, vload[H](dsp.rec163_perm, hsize), hsize)
            vstore(rec162_tmp, vload[H](dsp.rec162_perm))
            vstore(rec162_tmp, vload[H](dsp.rec162_perm, hsize), hsize)
            vstore(rec161_tmp, vload[H](dsp.rec161_perm))
            vstore(rec161_tmp, vload[H](dsp.rec161_perm, hsize), hsize)
            vstore(rec169_tmp, vload[H](dsp.rec169_perm))
            vstore(rec169_tmp, vload[H](dsp.rec169_perm, hsize), hsize)
            vstore(rec168_tmp, vload[H](dsp.rec168_perm))
            vstore(rec168_tmp, vload[H](dsp.rec168_perm, hsize), hsize)
            vstore(yec20_tmp, vload[H](dsp.yec20_perm))
            vstore(yec20_tmp, vload[H](dsp.yec20_perm, hsize), hsize)
            vstore(rec167_tmp, vload[H](dsp.rec167_perm))
            vstore(rec167_tmp, vload[H](dsp.rec167_perm, hsize), hsize)
            vstore(rec166_tmp, vload[H](dsp.rec166_perm))
            vstore(rec166_tmp, vload[H](dsp.rec166_perm, hsize), hsize)
            vstore(rec171_tmp, vload[H](dsp.rec171_perm))
            vstore(rec171_tmp, vload[H](dsp.rec171_perm, hsize), hsize)
            vstore(rec170_tmp, vload[H](dsp.rec170_perm))
            vstore(rec170_tmp, vload[H](dsp.rec170_perm, hsize), hsize)
            vstore(rec176_tmp, vload[H](dsp.rec176_perm))
            vstore(rec176_tmp, vload[H](dsp.rec176_perm, hsize), hsize)
            vstore(rec175_tmp, vload[H](dsp.rec175_perm))
            vstore(rec175_tmp, vload[H](dsp.rec175_perm, hsize), hsize)
            vstore(rec174_tmp, vload[H](dsp.rec174_perm))
            vstore(rec174_tmp, vload[H](dsp.rec174_perm, hsize), hsize)
            vstore(rec173_tmp, vload[H](dsp.rec173_perm))
            vstore(rec173_tmp, vload[H](dsp.rec173_perm, hsize), hsize)
            vstore(rec172_tmp, vload[H](dsp.rec172_perm))
            vstore(rec172_tmp, vload[H](dsp.rec172_perm, hsize), hsize)
            vstore(rec182_tmp, vload[H](dsp.rec182_perm))
            vstore(rec182_tmp, vload[H](dsp.rec182_perm, hsize), hsize)
            vstore(rec181_tmp, vload[H](dsp.rec181_perm))
            vstore(rec181_tmp, vload[H](dsp.rec181_perm, hsize), hsize)
            vstore(yec21_tmp, vload[H](dsp.yec21_perm))
            vstore(yec21_tmp, vload[H](dsp.yec21_perm, hsize), hsize)
            vstore(rec180_tmp, vload[H](dsp.rec180_perm))
            vstore(rec180_tmp, vload[H](dsp.rec180_perm, hsize), hsize)
            vstore(rec179_tmp, vload[H](dsp.rec179_perm))
            vstore(rec179_tmp, vload[H](dsp.rec179_perm, hsize), hsize)
            vstore(rec178_tmp, vload[H](dsp.rec178_perm))
            vstore(rec178_tmp, vload[H](dsp.rec178_perm, hsize), hsize)
            vstore(rec177_tmp, vload[H](dsp.rec177_perm))
            vstore(rec177_tmp, vload[H](dsp.rec177_perm, hsize), hsize)
            vstore(rec187_tmp, vload[H](dsp.rec187_perm))
            vstore(rec187_tmp, vload[H](dsp.rec187_perm, hsize), hsize)
            vstore(rec186_tmp, vload[H](dsp.rec186_perm))
            vstore(rec186_tmp, vload[H](dsp.rec186_perm, hsize), hsize)
            vstore(yec22_tmp, vload[H](dsp.yec22_perm))
            vstore(yec22_tmp, vload[H](dsp.yec22_perm, hsize), hsize)
            vstore(rec185_tmp, vload[H](dsp.rec185_perm))
            vstore(rec185_tmp, vload[H](dsp.rec185_perm, hsize), hsize)
            vstore(rec184_tmp, vload[H](dsp.rec184_perm))
            vstore(rec184_tmp, vload[H](dsp.rec184_perm, hsize), hsize)
            vstore(rec183_tmp, vload[H](dsp.rec183_perm))
            vstore(rec183_tmp, vload[H](dsp.rec183_perm, hsize), hsize)
            vstore(rec191_tmp, vload[H](dsp.rec191_perm))
            vstore(rec191_tmp, vload[H](dsp.rec191_perm, hsize), hsize)
            vstore(rec190_tmp, vload[H](dsp.rec190_perm))
            vstore(rec190_tmp, vload[H](dsp.rec190_perm, hsize), hsize)
            vstore(yec23_tmp, vload[H](dsp.yec23_perm))
            vstore(yec23_tmp, vload[H](dsp.yec23_perm, hsize), hsize)
            vstore(rec189_tmp, vload[H](dsp.rec189_perm))
            vstore(rec189_tmp, vload[H](dsp.rec189_perm, hsize), hsize)
            vstore(rec188_tmp, vload[H](dsp.rec188_perm))
            vstore(rec188_tmp, vload[H](dsp.rec188_perm, hsize), hsize)
            vstore(rec193_tmp, vload[H](dsp.rec193_perm))
            vstore(rec193_tmp, vload[H](dsp.rec193_perm, hsize), hsize)
            vstore(rec192_tmp, vload[H](dsp.rec192_perm))
            vstore(rec192_tmp, vload[H](dsp.rec192_perm, hsize), hsize)
            vstore(rec198_tmp, vload[H](dsp.rec198_perm))
            vstore(rec198_tmp, vload[H](dsp.rec198_perm, hsize), hsize)
            vstore(rec197_tmp, vload[H](dsp.rec197_perm))
            vstore(rec197_tmp, vload[H](dsp.rec197_perm, hsize), hsize)
            vstore(rec196_tmp, vload[H](dsp.rec196_perm))
            vstore(rec196_tmp, vload[H](dsp.rec196_perm, hsize), hsize)
            vstore(rec195_tmp, vload[H](dsp.rec195_perm))
            vstore(rec195_tmp, vload[H](dsp.rec195_perm, hsize), hsize)
            vstore(rec194_tmp, vload[H](dsp.rec194_perm))
            vstore(rec194_tmp, vload[H](dsp.rec194_perm, hsize), hsize)
            vstore(rec204_tmp, vload[H](dsp.rec204_perm))
            vstore(rec204_tmp, vload[H](dsp.rec204_perm, hsize), hsize)
            vstore(rec203_tmp, vload[H](dsp.rec203_perm))
            vstore(rec203_tmp, vload[H](dsp.rec203_perm, hsize), hsize)
            vstore(yec24_tmp, vload[H](dsp.yec24_perm))
            vstore(yec24_tmp, vload[H](dsp.yec24_perm, hsize), hsize)
            vstore(rec202_tmp, vload[H](dsp.rec202_perm))
            vstore(rec202_tmp, vload[H](dsp.rec202_perm, hsize), hsize)
            vstore(rec201_tmp, vload[H](dsp.rec201_perm))
            vstore(rec201_tmp, vload[H](dsp.rec201_perm, hsize), hsize)
            vstore(rec200_tmp, vload[H](dsp.rec200_perm))
            vstore(rec200_tmp, vload[H](dsp.rec200_perm, hsize), hsize)
            vstore(rec199_tmp, vload[H](dsp.rec199_perm))
            vstore(rec199_tmp, vload[H](dsp.rec199_perm, hsize), hsize)
            vstore(rec209_tmp, vload[H](dsp.rec209_perm))
            vstore(rec209_tmp, vload[H](dsp.rec209_perm, hsize), hsize)
            vstore(rec208_tmp, vload[H](dsp.rec208_perm))
            vstore(rec208_tmp, vload[H](dsp.rec208_perm, hsize), hsize)
            vstore(yec25_tmp, vload[H](dsp.yec25_perm))
            vstore(yec25_tmp, vload[H](dsp.yec25_perm, hsize), hsize)
            vstore(rec207_tmp, vload[H](dsp.rec207_perm))
            vstore(rec207_tmp, vload[H](dsp.rec207_perm, hsize), hsize)
            vstore(rec206_tmp, vload[H](dsp.rec206_perm))
            vstore(rec206_tmp, vload[H](dsp.rec206_perm, hsize), hsize)
            vstore(rec205_tmp, vload[H](dsp.rec205_perm))
            vstore(rec205_tmp, vload[H](dsp.rec205_perm, hsize), hsize)
            vstore(rec213_tmp, vload[H](dsp.rec213_perm))
            vstore(rec213_tmp, vload[H](dsp.rec213_perm, hsize), hsize)
            vstore(rec212_tmp, vload[H](dsp.rec212_perm))
            vstore(rec212_tmp, vload[H](dsp.rec212_perm, hsize), hsize)
            vstore(yec26_tmp, vload[H](dsp.yec26_perm))
            vstore(yec26_tmp, vload[H](dsp.yec26_perm, hsize), hsize)
            vstore(rec211_tmp, vload[H](dsp.rec211_perm))
            vstore(rec211_tmp, vload[H](dsp.rec211_perm, hsize), hsize)
            vstore(rec210_tmp, vload[H](dsp.rec210_perm))
            vstore(rec210_tmp, vload[H](dsp.rec210_perm, hsize), hsize)
            vstore(rec215_tmp, vload[H](dsp.rec215_perm))
            vstore(rec215_tmp, vload[H](dsp.rec215_perm, hsize), hsize)
            vstore(rec214_tmp, vload[H](dsp.rec214_perm))
            vstore(rec214_tmp, vload[H](dsp.rec214_perm, hsize), hsize)
            vstore(rec220_tmp, vload[H](dsp.rec220_perm))
            vstore(rec220_tmp, vload[H](dsp.rec220_perm, hsize), hsize)
            vstore(rec219_tmp, vload[H](dsp.rec219_perm))
            vstore(rec219_tmp, vload[H](dsp.rec219_perm, hsize), hsize)
            vstore(rec218_tmp, vload[H](dsp.rec218_perm))
            vstore(rec218_tmp, vload[H](dsp.rec218_perm, hsize), hsize)
            vstore(rec217_tmp, vload[H](dsp.rec217_perm))
            vstore(rec217_tmp, vload[H](dsp.rec217_perm, hsize), hsize)
            vstore(rec216_tmp, vload[H](dsp.rec216_perm))
            vstore(rec216_tmp, vload[H](dsp.rec216_perm, hsize), hsize)
            vstore(rec226_tmp, vload[H](dsp.rec226_perm))
            vstore(rec226_tmp, vload[H](dsp.rec226_perm, hsize), hsize)
            vstore(rec225_tmp, vload[H](dsp.rec225_perm))
            vstore(rec225_tmp, vload[H](dsp.rec225_perm, hsize), hsize)
            vstore(yec27_tmp, vload[H](dsp.yec27_perm))
            vstore(yec27_tmp, vload[H](dsp.yec27_perm, hsize), hsize)
            vstore(rec224_tmp, vload[H](dsp.rec224_perm))
            vstore(rec224_tmp, vload[H](dsp.rec224_perm, hsize), hsize)
            vstore(rec223_tmp, vload[H](dsp.rec223_perm))
            vstore(rec223_tmp, vload[H](dsp.rec223_perm, hsize), hsize)
            vstore(rec222_tmp, vload[H](dsp.rec222_perm))
            vstore(rec222_tmp, vload[H](dsp.rec222_perm, hsize), hsize)
            vstore(rec221_tmp, vload[H](dsp.rec221_perm))
            vstore(rec221_tmp, vload[H](dsp.rec221_perm, hsize), hsize)
            vstore(rec231_tmp, vload[H](dsp.rec231_perm))
            vstore(rec231_tmp, vload[H](dsp.rec231_perm, hsize), hsize)
            vstore(rec230_tmp, vload[H](dsp.rec230_perm))
            vstore(rec230_tmp, vload[H](dsp.rec230_perm, hsize), hsize)
            vstore(yec28_tmp, vload[H](dsp.yec28_perm))
            vstore(yec28_tmp, vload[H](dsp.yec28_perm, hsize), hsize)
            vstore(rec229_tmp, vload[H](dsp.rec229_perm))
            vstore(rec229_tmp, vload[H](dsp.rec229_perm, hsize), hsize)
            vstore(rec228_tmp, vload[H](dsp.rec228_perm))
            vstore(rec228_tmp, vload[H](dsp.rec228_perm, hsize), hsize)
            vstore(rec227_tmp, vload[H](dsp.rec227_perm))
            vstore(rec227_tmp, vload[H](dsp.rec227_perm, hsize), hsize)
            vstore(rec235_tmp, vload[H](dsp.rec235_perm))
            vstore(rec235_tmp, vload[H](dsp.rec235_perm, hsize), hsize)
            vstore(rec234_tmp, vload[H](dsp.rec234_perm))
            vstore(rec234_tmp, vload[H](dsp.rec234_perm, hsize), hsize)
            vstore(yec29_tmp, vload[H](dsp.yec29_perm))
            vstore(yec29_tmp, vload[H](dsp.yec29_perm, hsize), hsize)
            vstore(rec233_tmp, vload[H](dsp.rec233_perm))
            vstore(rec233_tmp, vload[H](dsp.rec233_perm, hsize), hsize)
            vstore(rec232_tmp, vload[H](dsp.rec232_perm))
            vstore(rec232_tmp, vload[H](dsp.rec232_perm, hsize), hsize)
            vstore(rec237_tmp, vload[H](dsp.rec237_perm))
            vstore(rec237_tmp, vload[H](dsp.rec237_perm, hsize), hsize)
            vstore(rec236_tmp, vload[H](dsp.rec236_perm))
            vstore(rec236_tmp, vload[H](dsp.rec236_perm, hsize), hsize)
            vstore(rec242_tmp, vload[H](dsp.rec242_perm))
            vstore(rec242_tmp, vload[H](dsp.rec242_perm, hsize), hsize)
            vstore(rec241_tmp, vload[H](dsp.rec241_perm))
            vstore(rec241_tmp, vload[H](dsp.rec241_perm, hsize), hsize)
            vstore(rec240_tmp, vload[H](dsp.rec240_perm))
            vstore(rec240_tmp, vload[H](dsp.rec240_perm, hsize), hsize)
            vstore(rec239_tmp, vload[H](dsp.rec239_perm))
            vstore(rec239_tmp, vload[H](dsp.rec239_perm, hsize), hsize)
            vstore(rec238_tmp, vload[H](dsp.rec238_perm))
            vstore(rec238_tmp, vload[H](dsp.rec238_perm, hsize), hsize)
            vstore(rec248_tmp, vload[H](dsp.rec248_perm))
            vstore(rec248_tmp, vload[H](dsp.rec248_perm, hsize), hsize)
            vstore(rec247_tmp, vload[H](dsp.rec247_perm))
            vstore(rec247_tmp, vload[H](dsp.rec247_perm, hsize), hsize)
            vstore(yec30_tmp, vload[H](dsp.yec30_perm))
            vstore(yec30_tmp, vload[H](dsp.yec30_perm, hsize), hsize)
            vstore(rec246_tmp, vload[H](dsp.rec246_perm))
            vstore(rec246_tmp, vload[H](dsp.rec246_perm, hsize), hsize)
            vstore(rec245_tmp, vload[H](dsp.rec245_perm))
            vstore(rec245_tmp, vload[H](dsp.rec245_perm, hsize), hsize)
            vstore(rec244_tmp, vload[H](dsp.rec244_perm))
            vstore(rec244_tmp, vload[H](dsp.rec244_perm, hsize), hsize)
            vstore(rec243_tmp, vload[H](dsp.rec243_perm))
            vstore(rec243_tmp, vload[H](dsp.rec243_perm, hsize), hsize)
            vstore(rec253_tmp, vload[H](dsp.rec253_perm))
            vstore(rec253_tmp, vload[H](dsp.rec253_perm, hsize), hsize)
            vstore(rec252_tmp, vload[H](dsp.rec252_perm))
            vstore(rec252_tmp, vload[H](dsp.rec252_perm, hsize), hsize)
            vstore(yec31_tmp, vload[H](dsp.yec31_perm))
            vstore(yec31_tmp, vload[H](dsp.yec31_perm, hsize), hsize)
            vstore(rec251_tmp, vload[H](dsp.rec251_perm))
            vstore(rec251_tmp, vload[H](dsp.rec251_perm, hsize), hsize)
            vstore(rec250_tmp, vload[H](dsp.rec250_perm))
            vstore(rec250_tmp, vload[H](dsp.rec250_perm, hsize), hsize)
            vstore(rec249_tmp, vload[H](dsp.rec249_perm))
            vstore(rec249_tmp, vload[H](dsp.rec249_perm, hsize), hsize)
            vstore(rec257_tmp, vload[H](dsp.rec257_perm))
            vstore(rec257_tmp, vload[H](dsp.rec257_perm, hsize), hsize)
            vstore(rec256_tmp, vload[H](dsp.rec256_perm))
            vstore(rec256_tmp, vload[H](dsp.rec256_perm, hsize), hsize)
            vstore(yec32_tmp, vload[H](dsp.yec32_perm))
            vstore(yec32_tmp, vload[H](dsp.yec32_perm, hsize), hsize)
            vstore(rec255_tmp, vload[H](dsp.rec255_perm))
            vstore(rec255_tmp, vload[H](dsp.rec255_perm, hsize), hsize)
            vstore(rec254_tmp, vload[H](dsp.rec254_perm))
            vstore(rec254_tmp, vload[H](dsp.rec254_perm, hsize), hsize)
            vstore(rec259_tmp, vload[H](dsp.rec259_perm))
            vstore(rec259_tmp, vload[H](dsp.rec259_perm, hsize), hsize)
            vstore(rec258_tmp, vload[H](dsp.rec258_perm))
            vstore(rec258_tmp, vload[H](dsp.rec258_perm, hsize), hsize)
            vstore(rec264_tmp, vload[H](dsp.rec264_perm))
            vstore(rec264_tmp, vload[H](dsp.rec264_perm, hsize), hsize)
            vstore(rec263_tmp, vload[H](dsp.rec263_perm))
            vstore(rec263_tmp, vload[H](dsp.rec263_perm, hsize), hsize)
            vstore(rec262_tmp, vload[H](dsp.rec262_perm))
            vstore(rec262_tmp, vload[H](dsp.rec262_perm, hsize), hsize)
            vstore(rec261_tmp, vload[H](dsp.rec261_perm))
            vstore(rec261_tmp, vload[H](dsp.rec261_perm, hsize), hsize)
            vstore(rec260_tmp, vload[H](dsp.rec260_perm))
            vstore(rec260_tmp, vload[H](dsp.rec260_perm, hsize), hsize)
            vstore(rec270_tmp, vload[H](dsp.rec270_perm))
            vstore(rec270_tmp, vload[H](dsp.rec270_perm, hsize), hsize)
            vstore(rec269_tmp, vload[H](dsp.rec269_perm))
            vstore(rec269_tmp, vload[H](dsp.rec269_perm, hsize), hsize)
            vstore(yec33_tmp, vload[H](dsp.yec33_perm))
            vstore(yec33_tmp, vload[H](dsp.yec33_perm, hsize), hsize)
            vstore(rec268_tmp, vload[H](dsp.rec268_perm))
            vstore(rec268_tmp, vload[H](dsp.rec268_perm, hsize), hsize)
            vstore(rec267_tmp, vload[H](dsp.rec267_perm))
            vstore(rec267_tmp, vload[H](dsp.rec267_perm, hsize), hsize)
            vstore(rec266_tmp, vload[H](dsp.rec266_perm))
            vstore(rec266_tmp, vload[H](dsp.rec266_perm, hsize), hsize)
            vstore(rec265_tmp, vload[H](dsp.rec265_perm))
            vstore(rec265_tmp, vload[H](dsp.rec265_perm, hsize), hsize)
            vstore(rec275_tmp, vload[H](dsp.rec275_perm))
            vstore(rec275_tmp, vload[H](dsp.rec275_perm, hsize), hsize)
            vstore(rec274_tmp, vload[H](dsp.rec274_perm))
            vstore(rec274_tmp, vload[H](dsp.rec274_perm, hsize), hsize)
            vstore(yec34_tmp, vload[H](dsp.yec34_perm))
            vstore(yec34_tmp, vload[H](dsp.yec34_perm, hsize), hsize)
            vstore(rec273_tmp, vload[H](dsp.rec273_perm))
            vstore(rec273_tmp, vload[H](dsp.rec273_perm, hsize), hsize)
            vstore(rec272_tmp, vload[H](dsp.rec272_perm))
            vstore(rec272_tmp, vload[H](dsp.rec272_perm, hsize), hsize)
            vstore(rec271_tmp, vload[H](dsp.rec271_perm))
            vstore(rec271_tmp, vload[H](dsp.rec271_perm, hsize), hsize)
            vstore(rec279_tmp, vload[H](dsp.rec279_perm))
            vstore(rec279_tmp, vload[H](dsp.rec279_perm, hsize), hsize)
            vstore(rec278_tmp, vload[H](dsp.rec278_perm))
            vstore(rec278_tmp, vload[H](dsp.rec278_perm, hsize), hsize)
            vstore(yec35_tmp, vload[H](dsp.yec35_perm))
            vstore(yec35_tmp, vload[H](dsp.yec35_perm, hsize), hsize)
            vstore(rec277_tmp, vload[H](dsp.rec277_perm))
            vstore(rec277_tmp, vload[H](dsp.rec277_perm, hsize), hsize)
            vstore(rec276_tmp, vload[H](dsp.rec276_perm))
            vstore(rec276_tmp, vload[H](dsp.rec276_perm, hsize), hsize)
            vstore(rec281_tmp, vload[H](dsp.rec281_perm))
            vstore(rec281_tmp, vload[H](dsp.rec281_perm, hsize), hsize)
            vstore(rec280_tmp, vload[H](dsp.rec280_perm))
            vstore(rec280_tmp, vload[H](dsp.rec280_perm, hsize), hsize)
            vstore(rec286_tmp, vload[H](dsp.rec286_perm))
            vstore(rec286_tmp, vload[H](dsp.rec286_perm, hsize), hsize)
            vstore(rec285_tmp, vload[H](dsp.rec285_perm))
            vstore(rec285_tmp, vload[H](dsp.rec285_perm, hsize), hsize)
            vstore(rec284_tmp, vload[H](dsp.rec284_perm))
            vstore(rec284_tmp, vload[H](dsp.rec284_perm, hsize), hsize)
            vstore(rec283_tmp, vload[H](dsp.rec283_perm))
            vstore(rec283_tmp, vload[H](dsp.rec283_perm, hsize), hsize)
            vstore(rec282_tmp, vload[H](dsp.rec282_perm))
            vstore(rec282_tmp, vload[H](dsp.rec282_perm, hsize), hsize)
            vstore(rec292_tmp, vload[H](dsp.rec292_perm))
            vstore(rec292_tmp, vload[H](dsp.rec292_perm, hsize), hsize)
            vstore(rec291_tmp, vload[H](dsp.rec291_perm))
            vstore(rec291_tmp, vload[H](dsp.rec291_perm, hsize), hsize)
            vstore(yec36_tmp, vload[H](dsp.yec36_perm))
            vstore(yec36_tmp, vload[H](dsp.yec36_perm, hsize), hsize)
            vstore(rec290_tmp, vload[H](dsp.rec290_perm))
            vstore(rec290_tmp, vload[H](dsp.rec290_perm, hsize), hsize)
            vstore(rec289_tmp, vload[H](dsp.rec289_perm))
            vstore(rec289_tmp, vload[H](dsp.rec289_perm, hsize), hsize)
            vstore(rec288_tmp, vload[H](dsp.rec288_perm))
            vstore(rec288_tmp, vload[H](dsp.rec288_perm, hsize), hsize)
            vstore(rec287_tmp, vload[H](dsp.rec287_perm))
            vstore(rec287_tmp, vload[H](dsp.rec287_perm, hsize), hsize)
            vstore(rec297_tmp, vload[H](dsp.rec297_perm))
            vstore(rec297_tmp, vload[H](dsp.rec297_perm, hsize), hsize)
            vstore(rec296_tmp, vload[H](dsp.rec296_perm))
            vstore(rec296_tmp, vload[H](dsp.rec296_perm, hsize), hsize)
            vstore(yec37_tmp, vload[H](dsp.yec37_perm))
            vstore(yec37_tmp, vload[H](dsp.yec37_perm, hsize), hsize)
            vstore(rec295_tmp, vload[H](dsp.rec295_perm))
            vstore(rec295_tmp, vload[H](dsp.rec295_perm, hsize), hsize)
            vstore(rec294_tmp, vload[H](dsp.rec294_perm))
            vstore(rec294_tmp, vload[H](dsp.rec294_perm, hsize), hsize)
            vstore(rec293_tmp, vload[H](dsp.rec293_perm))
            vstore(rec293_tmp, vload[H](dsp.rec293_perm, hsize), hsize)
            vstore(rec301_tmp, vload[H](dsp.rec301_perm))
            vstore(rec301_tmp, vload[H](dsp.rec301_perm, hsize), hsize)
            vstore(rec300_tmp, vload[H](dsp.rec300_perm))
            vstore(rec300_tmp, vload[H](dsp.rec300_perm, hsize), hsize)
            vstore(yec38_tmp, vload[H](dsp.yec38_perm))
            vstore(yec38_tmp, vload[H](dsp.yec38_perm, hsize), hsize)
            vstore(rec299_tmp, vload[H](dsp.rec299_perm))
            vstore(rec299_tmp, vload[H](dsp.rec299_perm, hsize), hsize)
            vstore(rec298_tmp, vload[H](dsp.rec298_perm))
            vstore(rec298_tmp, vload[H](dsp.rec298_perm, hsize), hsize)
            vstore(rec303_tmp, vload[H](dsp.rec303_perm))
            vstore(rec303_tmp, vload[H](dsp.rec303_perm, hsize), hsize)
            vstore(rec302_tmp, vload[H](dsp.rec302_perm))
            vstore(rec302_tmp, vload[H](dsp.rec302_perm, hsize), hsize)
            vstore(rec308_tmp, vload[H](dsp.rec308_perm))
            vstore(rec308_tmp, vload[H](dsp.rec308_perm, hsize), hsize)
            vstore(rec307_tmp, vload[H](dsp.rec307_perm))
            vstore(rec307_tmp, vload[H](dsp.rec307_perm, hsize), hsize)
            vstore(rec306_tmp, vload[H](dsp.rec306_perm))
            vstore(rec306_tmp, vload[H](dsp.rec306_perm, hsize), hsize)
            vstore(rec305_tmp, vload[H](dsp.rec305_perm))
            vstore(rec305_tmp, vload[H](dsp.rec305_perm, hsize), hsize)
            vstore(rec304_tmp, vload[H](dsp.rec304_perm))
            vstore(rec304_tmp, vload[H](dsp.rec304_perm, hsize), hsize)
            vstore(rec314_tmp, vload[H](dsp.rec314_perm))
            vstore(rec314_tmp, vload[H](dsp.rec314_perm, hsize), hsize)
            vstore(rec313_tmp, vload[H](dsp.rec313_perm))
            vstore(rec313_tmp, vload[H](dsp.rec313_perm, hsize), hsize)
            vstore(yec39_tmp, vload[H](dsp.yec39_perm))
            vstore(yec39_tmp, vload[H](dsp.yec39_perm, hsize), hsize)
            vstore(rec312_tmp, vload[H](dsp.rec312_perm))
            vstore(rec312_tmp, vload[H](dsp.rec312_perm, hsize), hsize)
            vstore(rec311_tmp, vload[H](dsp.rec311_perm))
            vstore(rec311_tmp, vload[H](dsp.rec311_perm, hsize), hsize)
            vstore(rec310_tmp, vload[H](dsp.rec310_perm))
            vstore(rec310_tmp, vload[H](dsp.rec310_perm, hsize), hsize)
            vstore(rec309_tmp, vload[H](dsp.rec309_perm))
            vstore(rec309_tmp, vload[H](dsp.rec309_perm, hsize), hsize)
            vstore(rec319_tmp, vload[H](dsp.rec319_perm))
            vstore(rec319_tmp, vload[H](dsp.rec319_perm, hsize), hsize)
            vstore(rec318_tmp, vload[H](dsp.rec318_perm))
            vstore(rec318_tmp, vload[H](dsp.rec318_perm, hsize), hsize)
            vstore(yec40_tmp, vload[H](dsp.yec40_perm))
            vstore(yec40_tmp, vload[H](dsp.yec40_perm, hsize), hsize)
            vstore(rec317_tmp, vload[H](dsp.rec317_perm))
            vstore(rec317_tmp, vload[H](dsp.rec317_perm, hsize), hsize)
            vstore(rec316_tmp, vload[H](dsp.rec316_perm))
            vstore(rec316_tmp, vload[H](dsp.rec316_perm, hsize), hsize)
            vstore(rec315_tmp, vload[H](dsp.rec315_perm))
            vstore(rec315_tmp, vload[H](dsp.rec315_perm, hsize), hsize)
            vstore(rec323_tmp, vload[H](dsp.rec323_perm))
            vstore(rec323_tmp, vload[H](dsp.rec323_perm, hsize), hsize)
            vstore(rec322_tmp, vload[H](dsp.rec322_perm))
            vstore(rec322_tmp, vload[H](dsp.rec322_perm, hsize), hsize)
            vstore(yec41_tmp, vload[H](dsp.yec41_perm))
            vstore(yec41_tmp, vload[H](dsp.yec41_perm, hsize), hsize)
            vstore(rec321_tmp, vload[H](dsp.rec321_perm))
            vstore(rec321_tmp, vload[H](dsp.rec321_perm, hsize), hsize)
            vstore(rec320_tmp, vload[H](dsp.rec320_perm))
            vstore(rec320_tmp, vload[H](dsp.rec320_perm, hsize), hsize)
            vstore(rec325_tmp, vload[H](dsp.rec325_perm))
            vstore(rec325_tmp, vload[H](dsp.rec325_perm, hsize), hsize)
            vstore(rec324_tmp, vload[H](dsp.rec324_perm))
            vstore(rec324_tmp, vload[H](dsp.rec324_perm, hsize), hsize)
            vstore(rec330_tmp, vload[H](dsp.rec330_perm))
            vstore(rec330_tmp, vload[H](dsp.rec330_perm, hsize), hsize)
            vstore(rec329_tmp, vload[H](dsp.rec329_perm))
            vstore(rec329_tmp, vload[H](dsp.rec329_perm, hsize), hsize)
            vstore(rec328_tmp, vload[H](dsp.rec328_perm))
            vstore(rec328_tmp, vload[H](dsp.rec328_perm, hsize), hsize)
            vstore(rec327_tmp, vload[H](dsp.rec327_perm))
            vstore(rec327_tmp, vload[H](dsp.rec327_perm, hsize), hsize)
            vstore(rec326_tmp, vload[H](dsp.rec326_perm))
            vstore(rec326_tmp, vload[H](dsp.rec326_perm, hsize), hsize)
            vstore(rec336_tmp, vload[H](dsp.rec336_perm))
            vstore(rec336_tmp, vload[H](dsp.rec336_perm, hsize), hsize)
            vstore(rec335_tmp, vload[H](dsp.rec335_perm))
            vstore(rec335_tmp, vload[H](dsp.rec335_perm, hsize), hsize)
            vstore(yec42_tmp, vload[H](dsp.yec42_perm))
            vstore(yec42_tmp, vload[H](dsp.yec42_perm, hsize), hsize)
            vstore(rec334_tmp, vload[H](dsp.rec334_perm))
            vstore(rec334_tmp, vload[H](dsp.rec334_perm, hsize), hsize)
            vstore(rec333_tmp, vload[H](dsp.rec333_perm))
            vstore(rec333_tmp, vload[H](dsp.rec333_perm, hsize), hsize)
            vstore(rec332_tmp, vload[H](dsp.rec332_perm))
            vstore(rec332_tmp, vload[H](dsp.rec332_perm, hsize), hsize)
            vstore(rec331_tmp, vload[H](dsp.rec331_perm))
            vstore(rec331_tmp, vload[H](dsp.rec331_perm, hsize), hsize)
            vstore(rec341_tmp, vload[H](dsp.rec341_perm))
            vstore(rec341_tmp, vload[H](dsp.rec341_perm, hsize), hsize)
            vstore(rec340_tmp, vload[H](dsp.rec340_perm))
            vstore(rec340_tmp, vload[H](dsp.rec340_perm, hsize), hsize)
            vstore(yec43_tmp, vload[H](dsp.yec43_perm))
            vstore(yec43_tmp, vload[H](dsp.yec43_perm, hsize), hsize)
            vstore(rec339_tmp, vload[H](dsp.rec339_perm))
            vstore(rec339_tmp, vload[H](dsp.rec339_perm, hsize), hsize)
            vstore(rec338_tmp, vload[H](dsp.rec338_perm))
            vstore(rec338_tmp, vload[H](dsp.rec338_perm, hsize), hsize)
            vstore(rec337_tmp, vload[H](dsp.rec337_perm))
            vstore(rec337_tmp, vload[H](dsp.rec337_perm, hsize), hsize)
            vstore(rec345_tmp, vload[H](dsp.rec345_perm))
            vstore(rec345_tmp, vload[H](dsp.rec345_perm, hsize), hsize)
            vstore(rec344_tmp, vload[H](dsp.rec344_perm))
            vstore(rec344_tmp, vload[H](dsp.rec344_perm, hsize), hsize)
            vstore(yec44_tmp, vload[H](dsp.yec44_perm))
            vstore(yec44_tmp, vload[H](dsp.yec44_perm, hsize), hsize)
            vstore(rec343_tmp, vload[H](dsp.rec343_perm))
            vstore(rec343_tmp, vload[H](dsp.rec343_perm, hsize), hsize)
            vstore(rec342_tmp, vload[H](dsp.rec342_perm))
            vstore(rec342_tmp, vload[H](dsp.rec342_perm, hsize), hsize)
            vstore(rec347_tmp, vload[H](dsp.rec347_perm))
            vstore(rec347_tmp, vload[H](dsp.rec347_perm, hsize), hsize)
            vstore(rec346_tmp, vload[H](dsp.rec346_perm))
            vstore(rec346_tmp, vload[H](dsp.rec346_perm, hsize), hsize)
            vstore(rec352_tmp, vload[H](dsp.rec352_perm))
            vstore(rec352_tmp, vload[H](dsp.rec352_perm, hsize), hsize)
            vstore(rec351_tmp, vload[H](dsp.rec351_perm))
            vstore(rec351_tmp, vload[H](dsp.rec351_perm, hsize), hsize)
            vstore(rec350_tmp, vload[H](dsp.rec350_perm))
            vstore(rec350_tmp, vload[H](dsp.rec350_perm, hsize), hsize)
            vstore(rec349_tmp, vload[H](dsp.rec349_perm))
            vstore(rec349_tmp, vload[H](dsp.rec349_perm, hsize), hsize)
            vstore(rec348_tmp, vload[H](dsp.rec348_perm))
            vstore(rec348_tmp, vload[H](dsp.rec348_perm, hsize), hsize)
            vstore(rec358_tmp, vload[H](dsp.rec358_perm))
            vstore(rec358_tmp, vload[H](dsp.rec358_perm, hsize), hsize)
            vstore(rec357_tmp, vload[H](dsp.rec357_perm))
            vstore(rec357_tmp, vload[H](dsp.rec357_perm, hsize), hsize)
            vstore(yec45_tmp, vload[H](dsp.yec45_perm))
            vstore(yec45_tmp, vload[H](dsp.yec45_perm, hsize), hsize)
            vstore(rec356_tmp, vload[H](dsp.rec356_perm))
            vstore(rec356_tmp, vload[H](dsp.rec356_perm, hsize), hsize)
            vstore(rec355_tmp, vload[H](dsp.rec355_perm))
            vstore(rec355_tmp, vload[H](dsp.rec355_perm, hsize), hsize)
            vstore(rec354_tmp, vload[H](dsp.rec354_perm))
            vstore(rec354_tmp, vload[H](dsp.rec354_perm, hsize), hsize)
            vstore(rec353_tmp, vload[H](dsp.rec353_perm))
            vstore(rec353_tmp, vload[H](dsp.rec353_perm, hsize), hsize)
            vstore(rec363_tmp, vload[H](dsp.rec363_perm))
            vstore(rec363_tmp, vload[H](dsp.rec363_perm, hsize), hsize)
            vstore(rec362_tmp, vload[H](dsp.rec362_perm))
            vstore(rec362_tmp, vload[H](dsp.rec362_perm, hsize), hsize)
            vstore(yec46_tmp, vload[H](dsp.yec46_perm))
            vstore(yec46_tmp, vload[H](dsp.yec46_perm, hsize), hsize)
            vstore(rec361_tmp, vload[H](dsp.rec361_perm))
            vstore(rec361_tmp, vload[H](dsp.rec361_perm, hsize), hsize)
            vstore(rec360_tmp, vload[H](dsp.rec360_perm))
            vstore(rec360_tmp, vload[H](dsp.rec360_perm, hsize), hsize)
            vstore(rec359_tmp, vload[H](dsp.rec359_perm))
            vstore(rec359_tmp, vload[H](dsp.rec359_perm, hsize), hsize)
            vstore(rec367_tmp, vload[H](dsp.rec367_perm))
            vstore(rec367_tmp, vload[H](dsp.rec367_perm, hsize), hsize)
            vstore(rec366_tmp, vload[H](dsp.rec366_perm))
            vstore(rec366_tmp, vload[H](dsp.rec366_perm, hsize), hsize)
            vstore(yec47_tmp, vload[H](dsp.yec47_perm))
            vstore(yec47_tmp, vload[H](dsp.yec47_perm, hsize), hsize)
            vstore(rec365_tmp, vload[H](dsp.rec365_perm))
            vstore(rec365_tmp, vload[H](dsp.rec365_perm, hsize), hsize)
            vstore(rec364_tmp, vload[H](dsp.rec364_perm))
            vstore(rec364_tmp, vload[H](dsp.rec364_perm, hsize), hsize)
            vstore(rec369_tmp, vload[H](dsp.rec369_perm))
            vstore(rec369_tmp, vload[H](dsp.rec369_perm, hsize), hsize)
            vstore(rec368_tmp, vload[H](dsp.rec368_perm))
            vstore(rec368_tmp, vload[H](dsp.rec368_perm, hsize), hsize)
            dsp.yec48_idx = ((dsp.yec48_idx) + (dsp.yec48_idx_save)) & (S32(16383))
            vstore(rec0_tmp, vload[H](dsp.rec0_perm))
            vstore(rec0_tmp, vload[H](dsp.rec0_perm, hsize), hsize)
            dsp.yec49_idx = ((dsp.yec49_idx) + (dsp.yec49_idx_save)) & (S32(16383))
            vstore(rec1_tmp, vload[H](dsp.rec1_perm))
            vstore(rec1_tmp, vload[H](dsp.rec1_perm, hsize), hsize)
            dsp.yec50_idx = ((dsp.yec50_idx) + (dsp.yec50_idx_save)) & (S32(16383))
            vstore(rec2_tmp, vload[H](dsp.rec2_perm))
            vstore(rec2_tmp, vload[H](dsp.rec2_perm, hsize), hsize)
            dsp.yec51_idx = ((dsp.yec51_idx) + (dsp.yec51_idx_save)) & (S32(16383))
            vstore(rec3_tmp, vload[H](dsp.rec3_perm))
            vstore(rec3_tmp, vload[H](dsp.rec3_perm, hsize), hsize)
            dsp.yec52_idx = ((dsp.yec52_idx) + (dsp.yec52_idx_save)) & (S32(16383))
            vstore(rec4_tmp, vload[H](dsp.rec4_perm))
            vstore(rec4_tmp, vload[H](dsp.rec4_perm, hsize), hsize)
            dsp.yec53_idx = ((dsp.yec53_idx) + (dsp.yec53_idx_save)) & (S32(16383))
            vstore(rec5_tmp, vload[H](dsp.rec5_perm))
            vstore(rec5_tmp, vload[H](dsp.rec5_perm, hsize), hsize)
            dsp.yec54_idx = ((dsp.yec54_idx) + (dsp.yec54_idx_save)) & (S32(16383))
            vstore(rec6_tmp, vload[H](dsp.rec6_perm))
            vstore(rec6_tmp, vload[H](dsp.rec6_perm, hsize), hsize)
            dsp.yec55_idx = ((dsp.yec55_idx) + (dsp.yec55_idx_save)) & (S32(16383))
            vstore(rec7_tmp, vload[H](dsp.rec7_perm))
            vstore(rec7_tmp, vload[H](dsp.rec7_perm, hsize), hsize)
            dsp.yec56_idx = ((dsp.yec56_idx) + (dsp.yec56_idx_save)) & (S32(16383))
            vstore(rec8_tmp, vload[H](dsp.rec8_perm))
            vstore(rec8_tmp, vload[H](dsp.rec8_perm, hsize), hsize)
            dsp.yec57_idx = ((dsp.yec57_idx) + (dsp.yec57_idx_save)) & (S32(16383))
            vstore(rec9_tmp, vload[H](dsp.rec9_perm))
            vstore(rec9_tmp, vload[H](dsp.rec9_perm, hsize), hsize)
            dsp.yec58_idx = ((dsp.yec58_idx) + (dsp.yec58_idx_save)) & (S32(16383))
            vstore(rec10_tmp, vload[H](dsp.rec10_perm))
            vstore(rec10_tmp, vload[H](dsp.rec10_perm, hsize), hsize)
            dsp.yec59_idx = ((dsp.yec59_idx) + (dsp.yec59_idx_save)) & (S32(16383))
            vstore(rec11_tmp, vload[H](dsp.rec11_perm))
            vstore(rec11_tmp, vload[H](dsp.rec11_perm, hsize), hsize)
            dsp.yec60_idx = ((dsp.yec60_idx) + (dsp.yec60_idx_save)) & (S32(16383))
            vstore(rec12_tmp, vload[H](dsp.rec12_perm))
            vstore(rec12_tmp, vload[H](dsp.rec12_perm, hsize), hsize)
            dsp.yec61_idx = ((dsp.yec61_idx) + (dsp.yec61_idx_save)) & (S32(16383))
            vstore(rec13_tmp, vload[H](dsp.rec13_perm))
            vstore(rec13_tmp, vload[H](dsp.rec13_perm, hsize), hsize)
            dsp.yec62_idx = ((dsp.yec62_idx) + (dsp.yec62_idx_save)) & (S32(16383))
            vstore(rec14_tmp, vload[H](dsp.rec14_perm))
            vstore(rec14_tmp, vload[H](dsp.rec14_perm, hsize), hsize)
            dsp.yec63_idx = ((dsp.yec63_idx) + (dsp.yec63_idx_save)) & (S32(16383))
            vstore(rec15_tmp, vload[H](dsp.rec15_perm))
            vstore(rec15_tmp, vload[H](dsp.rec15_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec22[unsafe_offset = i] = -((slow2) * (((slow3) * (rec22[unsafe_offset = (i) - (S32(1))])) - ((slow1) * ((rec0[unsafe_offset = (i) - (S32(1))]) - (rec0[unsafe_offset = (i) - (S32(2))])))))
                rec21[unsafe_offset = i] = (rec22[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec21[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec21[unsafe_offset = (i) - (S32(1))]))))
                zec0[i] = (slow17) * (rec20[unsafe_offset = (i) - (S32(1))])
                rec20[unsafe_offset = i] = ((slow9) * ((rec21[unsafe_offset = (i) - (S32(2))]) + ((rec21[unsafe_offset = i]) - ((2.0) * (rec21[unsafe_offset = (i) - (S32(1))]))))) - ((slow13) * (((slow15) * (rec20[unsafe_offset = (i) - (S32(2))])) + (zec0[i])))
                zec1[i] = (slow25) * (rec19[unsafe_offset = (i) - (S32(1))])
                rec19[unsafe_offset = i] = ((rec20[unsafe_offset = (i) - (S32(2))]) + ((slow13) * ((zec0[i]) + ((slow15) * (rec20[unsafe_offset = i]))))) - ((slow21) * (((slow23) * (rec19[unsafe_offset = (i) - (S32(2))])) + (zec1[i])))
                zec2[i] = (slow33) * (rec18[unsafe_offset = (i) - (S32(1))])
                rec18[unsafe_offset = i] = ((rec19[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec1[i]) + ((slow23) * (rec19[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec18[unsafe_offset = (i) - (S32(2))])) + (zec2[i])))
                rec28[unsafe_offset = i] = -((slow2) * (((slow3) * (rec28[unsafe_offset = (i) - (S32(1))])) - ((rec0[unsafe_offset = (i) - (S32(1))]) + (rec0[unsafe_offset = (i) - (S32(2))]))))
                rec27[unsafe_offset = i] = (rec28[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec27[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec27[unsafe_offset = (i) - (S32(1))]))))
                yec0[unsafe_offset = i] = (slow5) * ((rec27[unsafe_offset = (i) - (S32(2))]) + ((rec27[unsafe_offset = i]) + ((2.0) * (rec27[unsafe_offset = (i) - (S32(1))]))))
                rec26[unsafe_offset = i] = -((slow34) * (((slow14) * (rec26[unsafe_offset = (i) - (S32(1))])) - ((slow11) * ((yec0[unsafe_offset = i]) - (yec0[unsafe_offset = (i) - (S32(1))])))))
                rec25[unsafe_offset = i] = (rec26[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec25[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec25[unsafe_offset = (i) - (S32(1))]))))
                zec3[i] = (slow25) * (rec24[unsafe_offset = (i) - (S32(1))])
                rec24[unsafe_offset = i] = ((slow38) * ((rec25[unsafe_offset = (i) - (S32(2))]) + ((rec25[unsafe_offset = i]) - ((2.0) * (rec25[unsafe_offset = (i) - (S32(1))]))))) - ((slow21) * (((slow23) * (rec24[unsafe_offset = (i) - (S32(2))])) + (zec3[i])))
                zec4[i] = (slow33) * (rec23[unsafe_offset = (i) - (S32(1))])
                rec23[unsafe_offset = i] = ((rec24[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec3[i]) + ((slow23) * (rec24[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec23[unsafe_offset = (i) - (S32(2))])) + (zec4[i])))
                rec33[unsafe_offset = i] = -((slow34) * (((slow14) * (rec33[unsafe_offset = (i) - (S32(1))])) - ((yec0[unsafe_offset = i]) + (yec0[unsafe_offset = (i) - (S32(1))]))))
                rec32[unsafe_offset = i] = (rec33[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec32[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec32[unsafe_offset = (i) - (S32(1))]))))
                yec1[unsafe_offset = i] = (slow36) * ((rec32[unsafe_offset = (i) - (S32(2))]) + ((rec32[unsafe_offset = i]) + ((2.0) * (rec32[unsafe_offset = (i) - (S32(1))]))))
                rec31[unsafe_offset = i] = -((slow39) * (((slow22) * (rec31[unsafe_offset = (i) - (S32(1))])) - ((slow19) * ((yec1[unsafe_offset = i]) - (yec1[unsafe_offset = (i) - (S32(1))])))))
                rec30[unsafe_offset = i] = (rec31[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec30[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec30[unsafe_offset = (i) - (S32(1))]))))
                zec5[i] = (slow33) * (rec29[unsafe_offset = (i) - (S32(1))])
                rec29[unsafe_offset = i] = ((slow43) * ((rec30[unsafe_offset = (i) - (S32(2))]) + ((rec30[unsafe_offset = i]) - ((2.0) * (rec30[unsafe_offset = (i) - (S32(1))]))))) - ((slow29) * (((slow31) * (rec29[unsafe_offset = (i) - (S32(2))])) + (zec5[i])))
                rec37[unsafe_offset = i] = -((slow39) * (((slow22) * (rec37[unsafe_offset = (i) - (S32(1))])) - ((yec1[unsafe_offset = i]) + (yec1[unsafe_offset = (i) - (S32(1))]))))
                rec36[unsafe_offset = i] = (rec37[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec36[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec36[unsafe_offset = (i) - (S32(1))]))))
                yec2[unsafe_offset = i] = (slow41) * ((rec36[unsafe_offset = (i) - (S32(2))]) + ((rec36[unsafe_offset = i]) + ((2.0) * (rec36[unsafe_offset = (i) - (S32(1))]))))
                rec35[unsafe_offset = i] = -((slow44) * (((slow30) * (rec35[unsafe_offset = (i) - (S32(1))])) - ((slow27) * ((yec2[unsafe_offset = i]) - (yec2[unsafe_offset = (i) - (S32(1))])))))
                rec34[unsafe_offset = i] = (rec35[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec34[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec34[unsafe_offset = (i) - (S32(1))]))))
                rec39[unsafe_offset = i] = -((slow44) * (((slow30) * (rec39[unsafe_offset = (i) - (S32(1))])) - ((yec2[unsafe_offset = i]) + (yec2[unsafe_offset = (i) - (S32(1))]))))
                rec38[unsafe_offset = i] = (rec39[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec38[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec38[unsafe_offset = (i) - (S32(1))]))))
                rec44[unsafe_offset = i] = -((slow2) * (((slow3) * (rec44[unsafe_offset = (i) - (S32(1))])) - ((slow1) * ((rec8[unsafe_offset = (i) - (S32(1))]) - (rec8[unsafe_offset = (i) - (S32(2))])))))
                rec43[unsafe_offset = i] = (rec44[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec43[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec43[unsafe_offset = (i) - (S32(1))]))))
                zec6[i] = (slow17) * (rec42[unsafe_offset = (i) - (S32(1))])
                rec42[unsafe_offset = i] = ((slow9) * ((rec43[unsafe_offset = (i) - (S32(2))]) + ((rec43[unsafe_offset = i]) - ((2.0) * (rec43[unsafe_offset = (i) - (S32(1))]))))) - ((slow13) * (((slow15) * (rec42[unsafe_offset = (i) - (S32(2))])) + (zec6[i])))
                zec7[i] = (slow25) * (rec41[unsafe_offset = (i) - (S32(1))])
                rec41[unsafe_offset = i] = ((rec42[unsafe_offset = (i) - (S32(2))]) + ((slow13) * ((zec6[i]) + ((slow15) * (rec42[unsafe_offset = i]))))) - ((slow21) * (((slow23) * (rec41[unsafe_offset = (i) - (S32(2))])) + (zec7[i])))
                zec8[i] = (slow33) * (rec40[unsafe_offset = (i) - (S32(1))])
                rec40[unsafe_offset = i] = ((rec41[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec7[i]) + ((slow23) * (rec41[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec40[unsafe_offset = (i) - (S32(2))])) + (zec8[i])))
                rec50[unsafe_offset = i] = -((slow2) * (((slow3) * (rec50[unsafe_offset = (i) - (S32(1))])) - ((rec8[unsafe_offset = (i) - (S32(1))]) + (rec8[unsafe_offset = (i) - (S32(2))]))))
                rec49[unsafe_offset = i] = (rec50[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec49[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec49[unsafe_offset = (i) - (S32(1))]))))
                yec3[unsafe_offset = i] = (slow5) * ((rec49[unsafe_offset = (i) - (S32(2))]) + ((rec49[unsafe_offset = i]) + ((2.0) * (rec49[unsafe_offset = (i) - (S32(1))]))))
                rec48[unsafe_offset = i] = -((slow34) * (((slow14) * (rec48[unsafe_offset = (i) - (S32(1))])) - ((slow11) * ((yec3[unsafe_offset = i]) - (yec3[unsafe_offset = (i) - (S32(1))])))))
                rec47[unsafe_offset = i] = (rec48[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec47[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec47[unsafe_offset = (i) - (S32(1))]))))
                zec9[i] = (slow25) * (rec46[unsafe_offset = (i) - (S32(1))])
                rec46[unsafe_offset = i] = ((slow38) * ((rec47[unsafe_offset = (i) - (S32(2))]) + ((rec47[unsafe_offset = i]) - ((2.0) * (rec47[unsafe_offset = (i) - (S32(1))]))))) - ((slow21) * (((slow23) * (rec46[unsafe_offset = (i) - (S32(2))])) + (zec9[i])))
                zec10[i] = (slow33) * (rec45[unsafe_offset = (i) - (S32(1))])
                rec45[unsafe_offset = i] = ((rec46[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec9[i]) + ((slow23) * (rec46[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec45[unsafe_offset = (i) - (S32(2))])) + (zec10[i])))
                rec55[unsafe_offset = i] = -((slow34) * (((slow14) * (rec55[unsafe_offset = (i) - (S32(1))])) - ((yec3[unsafe_offset = i]) + (yec3[unsafe_offset = (i) - (S32(1))]))))
                rec54[unsafe_offset = i] = (rec55[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec54[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec54[unsafe_offset = (i) - (S32(1))]))))
                yec4[unsafe_offset = i] = (slow36) * ((rec54[unsafe_offset = (i) - (S32(2))]) + ((rec54[unsafe_offset = i]) + ((2.0) * (rec54[unsafe_offset = (i) - (S32(1))]))))
                rec53[unsafe_offset = i] = -((slow39) * (((slow22) * (rec53[unsafe_offset = (i) - (S32(1))])) - ((slow19) * ((yec4[unsafe_offset = i]) - (yec4[unsafe_offset = (i) - (S32(1))])))))
                rec52[unsafe_offset = i] = (rec53[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec52[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec52[unsafe_offset = (i) - (S32(1))]))))
                zec11[i] = (slow33) * (rec51[unsafe_offset = (i) - (S32(1))])
                rec51[unsafe_offset = i] = ((slow43) * ((rec52[unsafe_offset = (i) - (S32(2))]) + ((rec52[unsafe_offset = i]) - ((2.0) * (rec52[unsafe_offset = (i) - (S32(1))]))))) - ((slow29) * (((slow31) * (rec51[unsafe_offset = (i) - (S32(2))])) + (zec11[i])))
                rec59[unsafe_offset = i] = -((slow39) * (((slow22) * (rec59[unsafe_offset = (i) - (S32(1))])) - ((yec4[unsafe_offset = i]) + (yec4[unsafe_offset = (i) - (S32(1))]))))
                rec58[unsafe_offset = i] = (rec59[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec58[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec58[unsafe_offset = (i) - (S32(1))]))))
                yec5[unsafe_offset = i] = (slow41) * ((rec58[unsafe_offset = (i) - (S32(2))]) + ((rec58[unsafe_offset = i]) + ((2.0) * (rec58[unsafe_offset = (i) - (S32(1))]))))
                rec57[unsafe_offset = i] = -((slow44) * (((slow30) * (rec57[unsafe_offset = (i) - (S32(1))])) - ((slow27) * ((yec5[unsafe_offset = i]) - (yec5[unsafe_offset = (i) - (S32(1))])))))
                rec56[unsafe_offset = i] = (rec57[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec56[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec56[unsafe_offset = (i) - (S32(1))]))))
                rec61[unsafe_offset = i] = -((slow44) * (((slow30) * (rec61[unsafe_offset = (i) - (S32(1))])) - ((yec5[unsafe_offset = i]) + (yec5[unsafe_offset = (i) - (S32(1))]))))
                rec60[unsafe_offset = i] = (rec61[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec60[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec60[unsafe_offset = (i) - (S32(1))]))))
                rec66[unsafe_offset = i] = -((slow2) * (((slow3) * (rec66[unsafe_offset = (i) - (S32(1))])) - ((slow1) * ((rec4[unsafe_offset = (i) - (S32(1))]) - (rec4[unsafe_offset = (i) - (S32(2))])))))
                rec65[unsafe_offset = i] = (rec66[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec65[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec65[unsafe_offset = (i) - (S32(1))]))))
                zec12[i] = (slow17) * (rec64[unsafe_offset = (i) - (S32(1))])
                rec64[unsafe_offset = i] = ((slow9) * ((rec65[unsafe_offset = (i) - (S32(2))]) + ((rec65[unsafe_offset = i]) - ((2.0) * (rec65[unsafe_offset = (i) - (S32(1))]))))) - ((slow13) * (((slow15) * (rec64[unsafe_offset = (i) - (S32(2))])) + (zec12[i])))
                zec13[i] = (slow25) * (rec63[unsafe_offset = (i) - (S32(1))])
                rec63[unsafe_offset = i] = ((rec64[unsafe_offset = (i) - (S32(2))]) + ((slow13) * ((zec12[i]) + ((slow15) * (rec64[unsafe_offset = i]))))) - ((slow21) * (((slow23) * (rec63[unsafe_offset = (i) - (S32(2))])) + (zec13[i])))
                zec14[i] = (slow33) * (rec62[unsafe_offset = (i) - (S32(1))])
                rec62[unsafe_offset = i] = ((rec63[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec13[i]) + ((slow23) * (rec63[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec62[unsafe_offset = (i) - (S32(2))])) + (zec14[i])))
                rec72[unsafe_offset = i] = -((slow2) * (((slow3) * (rec72[unsafe_offset = (i) - (S32(1))])) - ((rec4[unsafe_offset = (i) - (S32(1))]) + (rec4[unsafe_offset = (i) - (S32(2))]))))
                rec71[unsafe_offset = i] = (rec72[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec71[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec71[unsafe_offset = (i) - (S32(1))]))))
                yec6[unsafe_offset = i] = (slow5) * ((rec71[unsafe_offset = (i) - (S32(2))]) + ((rec71[unsafe_offset = i]) + ((2.0) * (rec71[unsafe_offset = (i) - (S32(1))]))))
                rec70[unsafe_offset = i] = -((slow34) * (((slow14) * (rec70[unsafe_offset = (i) - (S32(1))])) - ((slow11) * ((yec6[unsafe_offset = i]) - (yec6[unsafe_offset = (i) - (S32(1))])))))
                rec69[unsafe_offset = i] = (rec70[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec69[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec69[unsafe_offset = (i) - (S32(1))]))))
                zec15[i] = (slow25) * (rec68[unsafe_offset = (i) - (S32(1))])
                rec68[unsafe_offset = i] = ((slow38) * ((rec69[unsafe_offset = (i) - (S32(2))]) + ((rec69[unsafe_offset = i]) - ((2.0) * (rec69[unsafe_offset = (i) - (S32(1))]))))) - ((slow21) * (((slow23) * (rec68[unsafe_offset = (i) - (S32(2))])) + (zec15[i])))
                zec16[i] = (slow33) * (rec67[unsafe_offset = (i) - (S32(1))])
                rec67[unsafe_offset = i] = ((rec68[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec15[i]) + ((slow23) * (rec68[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec67[unsafe_offset = (i) - (S32(2))])) + (zec16[i])))
                rec77[unsafe_offset = i] = -((slow34) * (((slow14) * (rec77[unsafe_offset = (i) - (S32(1))])) - ((yec6[unsafe_offset = i]) + (yec6[unsafe_offset = (i) - (S32(1))]))))
                rec76[unsafe_offset = i] = (rec77[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec76[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec76[unsafe_offset = (i) - (S32(1))]))))
                yec7[unsafe_offset = i] = (slow36) * ((rec76[unsafe_offset = (i) - (S32(2))]) + ((rec76[unsafe_offset = i]) + ((2.0) * (rec76[unsafe_offset = (i) - (S32(1))]))))
                rec75[unsafe_offset = i] = -((slow39) * (((slow22) * (rec75[unsafe_offset = (i) - (S32(1))])) - ((slow19) * ((yec7[unsafe_offset = i]) - (yec7[unsafe_offset = (i) - (S32(1))])))))
                rec74[unsafe_offset = i] = (rec75[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec74[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec74[unsafe_offset = (i) - (S32(1))]))))
                zec17[i] = (slow33) * (rec73[unsafe_offset = (i) - (S32(1))])
                rec73[unsafe_offset = i] = ((slow43) * ((rec74[unsafe_offset = (i) - (S32(2))]) + ((rec74[unsafe_offset = i]) - ((2.0) * (rec74[unsafe_offset = (i) - (S32(1))]))))) - ((slow29) * (((slow31) * (rec73[unsafe_offset = (i) - (S32(2))])) + (zec17[i])))
                rec81[unsafe_offset = i] = -((slow39) * (((slow22) * (rec81[unsafe_offset = (i) - (S32(1))])) - ((yec7[unsafe_offset = i]) + (yec7[unsafe_offset = (i) - (S32(1))]))))
                rec80[unsafe_offset = i] = (rec81[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec80[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec80[unsafe_offset = (i) - (S32(1))]))))
                yec8[unsafe_offset = i] = (slow41) * ((rec80[unsafe_offset = (i) - (S32(2))]) + ((rec80[unsafe_offset = i]) + ((2.0) * (rec80[unsafe_offset = (i) - (S32(1))]))))
                rec79[unsafe_offset = i] = -((slow44) * (((slow30) * (rec79[unsafe_offset = (i) - (S32(1))])) - ((slow27) * ((yec8[unsafe_offset = i]) - (yec8[unsafe_offset = (i) - (S32(1))])))))
                rec78[unsafe_offset = i] = (rec79[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec78[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec78[unsafe_offset = (i) - (S32(1))]))))
                rec83[unsafe_offset = i] = -((slow44) * (((slow30) * (rec83[unsafe_offset = (i) - (S32(1))])) - ((yec8[unsafe_offset = i]) + (yec8[unsafe_offset = (i) - (S32(1))]))))
                rec82[unsafe_offset = i] = (rec83[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec82[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec82[unsafe_offset = (i) - (S32(1))]))))
                rec88[unsafe_offset = i] = -((slow2) * (((slow3) * (rec88[unsafe_offset = (i) - (S32(1))])) - ((slow1) * ((rec12[unsafe_offset = (i) - (S32(1))]) - (rec12[unsafe_offset = (i) - (S32(2))])))))
                rec87[unsafe_offset = i] = (rec88[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec87[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec87[unsafe_offset = (i) - (S32(1))]))))
                zec18[i] = (slow17) * (rec86[unsafe_offset = (i) - (S32(1))])
                rec86[unsafe_offset = i] = ((slow9) * ((rec87[unsafe_offset = (i) - (S32(2))]) + ((rec87[unsafe_offset = i]) - ((2.0) * (rec87[unsafe_offset = (i) - (S32(1))]))))) - ((slow13) * (((slow15) * (rec86[unsafe_offset = (i) - (S32(2))])) + (zec18[i])))
                zec19[i] = (slow25) * (rec85[unsafe_offset = (i) - (S32(1))])
                rec85[unsafe_offset = i] = ((rec86[unsafe_offset = (i) - (S32(2))]) + ((slow13) * ((zec18[i]) + ((slow15) * (rec86[unsafe_offset = i]))))) - ((slow21) * (((slow23) * (rec85[unsafe_offset = (i) - (S32(2))])) + (zec19[i])))
                zec20[i] = (slow33) * (rec84[unsafe_offset = (i) - (S32(1))])
                rec84[unsafe_offset = i] = ((rec85[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec19[i]) + ((slow23) * (rec85[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec84[unsafe_offset = (i) - (S32(2))])) + (zec20[i])))
                rec94[unsafe_offset = i] = -((slow2) * (((slow3) * (rec94[unsafe_offset = (i) - (S32(1))])) - ((rec12[unsafe_offset = (i) - (S32(1))]) + (rec12[unsafe_offset = (i) - (S32(2))]))))
                rec93[unsafe_offset = i] = (rec94[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec93[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec93[unsafe_offset = (i) - (S32(1))]))))
                yec9[unsafe_offset = i] = (slow5) * ((rec93[unsafe_offset = (i) - (S32(2))]) + ((rec93[unsafe_offset = i]) + ((2.0) * (rec93[unsafe_offset = (i) - (S32(1))]))))
                rec92[unsafe_offset = i] = -((slow34) * (((slow14) * (rec92[unsafe_offset = (i) - (S32(1))])) - ((slow11) * ((yec9[unsafe_offset = i]) - (yec9[unsafe_offset = (i) - (S32(1))])))))
                rec91[unsafe_offset = i] = (rec92[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec91[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec91[unsafe_offset = (i) - (S32(1))]))))
                zec21[i] = (slow25) * (rec90[unsafe_offset = (i) - (S32(1))])
                rec90[unsafe_offset = i] = ((slow38) * ((rec91[unsafe_offset = (i) - (S32(2))]) + ((rec91[unsafe_offset = i]) - ((2.0) * (rec91[unsafe_offset = (i) - (S32(1))]))))) - ((slow21) * (((slow23) * (rec90[unsafe_offset = (i) - (S32(2))])) + (zec21[i])))
                zec22[i] = (slow33) * (rec89[unsafe_offset = (i) - (S32(1))])
                rec89[unsafe_offset = i] = ((rec90[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec21[i]) + ((slow23) * (rec90[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec89[unsafe_offset = (i) - (S32(2))])) + (zec22[i])))
                rec99[unsafe_offset = i] = -((slow34) * (((slow14) * (rec99[unsafe_offset = (i) - (S32(1))])) - ((yec9[unsafe_offset = i]) + (yec9[unsafe_offset = (i) - (S32(1))]))))
                rec98[unsafe_offset = i] = (rec99[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec98[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec98[unsafe_offset = (i) - (S32(1))]))))
                yec10[unsafe_offset = i] = (slow36) * ((rec98[unsafe_offset = (i) - (S32(2))]) + ((rec98[unsafe_offset = i]) + ((2.0) * (rec98[unsafe_offset = (i) - (S32(1))]))))
                rec97[unsafe_offset = i] = -((slow39) * (((slow22) * (rec97[unsafe_offset = (i) - (S32(1))])) - ((slow19) * ((yec10[unsafe_offset = i]) - (yec10[unsafe_offset = (i) - (S32(1))])))))
                rec96[unsafe_offset = i] = (rec97[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec96[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec96[unsafe_offset = (i) - (S32(1))]))))
                zec23[i] = (slow33) * (rec95[unsafe_offset = (i) - (S32(1))])
                rec95[unsafe_offset = i] = ((slow43) * ((rec96[unsafe_offset = (i) - (S32(2))]) + ((rec96[unsafe_offset = i]) - ((2.0) * (rec96[unsafe_offset = (i) - (S32(1))]))))) - ((slow29) * (((slow31) * (rec95[unsafe_offset = (i) - (S32(2))])) + (zec23[i])))
                rec103[unsafe_offset = i] = -((slow39) * (((slow22) * (rec103[unsafe_offset = (i) - (S32(1))])) - ((yec10[unsafe_offset = i]) + (yec10[unsafe_offset = (i) - (S32(1))]))))
                rec102[unsafe_offset = i] = (rec103[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec102[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec102[unsafe_offset = (i) - (S32(1))]))))
                yec11[unsafe_offset = i] = (slow41) * ((rec102[unsafe_offset = (i) - (S32(2))]) + ((rec102[unsafe_offset = i]) + ((2.0) * (rec102[unsafe_offset = (i) - (S32(1))]))))
                rec101[unsafe_offset = i] = -((slow44) * (((slow30) * (rec101[unsafe_offset = (i) - (S32(1))])) - ((slow27) * ((yec11[unsafe_offset = i]) - (yec11[unsafe_offset = (i) - (S32(1))])))))
                rec100[unsafe_offset = i] = (rec101[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec100[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec100[unsafe_offset = (i) - (S32(1))]))))
                rec105[unsafe_offset = i] = -((slow44) * (((slow30) * (rec105[unsafe_offset = (i) - (S32(1))])) - ((yec11[unsafe_offset = i]) + (yec11[unsafe_offset = (i) - (S32(1))]))))
                rec104[unsafe_offset = i] = (rec105[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec104[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec104[unsafe_offset = (i) - (S32(1))]))))
                rec110[unsafe_offset = i] = -((slow2) * (((slow3) * (rec110[unsafe_offset = (i) - (S32(1))])) - ((slow1) * ((rec2[unsafe_offset = (i) - (S32(1))]) - (rec2[unsafe_offset = (i) - (S32(2))])))))
                rec109[unsafe_offset = i] = (rec110[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec109[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec109[unsafe_offset = (i) - (S32(1))]))))
                zec24[i] = (slow17) * (rec108[unsafe_offset = (i) - (S32(1))])
                rec108[unsafe_offset = i] = ((slow9) * ((rec109[unsafe_offset = (i) - (S32(2))]) + ((rec109[unsafe_offset = i]) - ((2.0) * (rec109[unsafe_offset = (i) - (S32(1))]))))) - ((slow13) * (((slow15) * (rec108[unsafe_offset = (i) - (S32(2))])) + (zec24[i])))
                zec25[i] = (slow25) * (rec107[unsafe_offset = (i) - (S32(1))])
                rec107[unsafe_offset = i] = ((rec108[unsafe_offset = (i) - (S32(2))]) + ((slow13) * ((zec24[i]) + ((slow15) * (rec108[unsafe_offset = i]))))) - ((slow21) * (((slow23) * (rec107[unsafe_offset = (i) - (S32(2))])) + (zec25[i])))
                zec26[i] = (slow33) * (rec106[unsafe_offset = (i) - (S32(1))])
                rec106[unsafe_offset = i] = ((rec107[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec25[i]) + ((slow23) * (rec107[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec106[unsafe_offset = (i) - (S32(2))])) + (zec26[i])))
                rec116[unsafe_offset = i] = -((slow2) * (((slow3) * (rec116[unsafe_offset = (i) - (S32(1))])) - ((rec2[unsafe_offset = (i) - (S32(1))]) + (rec2[unsafe_offset = (i) - (S32(2))]))))
                rec115[unsafe_offset = i] = (rec116[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec115[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec115[unsafe_offset = (i) - (S32(1))]))))
                yec12[unsafe_offset = i] = (slow5) * ((rec115[unsafe_offset = (i) - (S32(2))]) + ((rec115[unsafe_offset = i]) + ((2.0) * (rec115[unsafe_offset = (i) - (S32(1))]))))
                rec114[unsafe_offset = i] = -((slow34) * (((slow14) * (rec114[unsafe_offset = (i) - (S32(1))])) - ((slow11) * ((yec12[unsafe_offset = i]) - (yec12[unsafe_offset = (i) - (S32(1))])))))
                rec113[unsafe_offset = i] = (rec114[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec113[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec113[unsafe_offset = (i) - (S32(1))]))))
                zec27[i] = (slow25) * (rec112[unsafe_offset = (i) - (S32(1))])
                rec112[unsafe_offset = i] = ((slow38) * ((rec113[unsafe_offset = (i) - (S32(2))]) + ((rec113[unsafe_offset = i]) - ((2.0) * (rec113[unsafe_offset = (i) - (S32(1))]))))) - ((slow21) * (((slow23) * (rec112[unsafe_offset = (i) - (S32(2))])) + (zec27[i])))
                zec28[i] = (slow33) * (rec111[unsafe_offset = (i) - (S32(1))])
                rec111[unsafe_offset = i] = ((rec112[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec27[i]) + ((slow23) * (rec112[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec111[unsafe_offset = (i) - (S32(2))])) + (zec28[i])))
                rec121[unsafe_offset = i] = -((slow34) * (((slow14) * (rec121[unsafe_offset = (i) - (S32(1))])) - ((yec12[unsafe_offset = i]) + (yec12[unsafe_offset = (i) - (S32(1))]))))
                rec120[unsafe_offset = i] = (rec121[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec120[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec120[unsafe_offset = (i) - (S32(1))]))))
                yec13[unsafe_offset = i] = (slow36) * ((rec120[unsafe_offset = (i) - (S32(2))]) + ((rec120[unsafe_offset = i]) + ((2.0) * (rec120[unsafe_offset = (i) - (S32(1))]))))
                rec119[unsafe_offset = i] = -((slow39) * (((slow22) * (rec119[unsafe_offset = (i) - (S32(1))])) - ((slow19) * ((yec13[unsafe_offset = i]) - (yec13[unsafe_offset = (i) - (S32(1))])))))
                rec118[unsafe_offset = i] = (rec119[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec118[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec118[unsafe_offset = (i) - (S32(1))]))))
                zec29[i] = (slow33) * (rec117[unsafe_offset = (i) - (S32(1))])
                rec117[unsafe_offset = i] = ((slow43) * ((rec118[unsafe_offset = (i) - (S32(2))]) + ((rec118[unsafe_offset = i]) - ((2.0) * (rec118[unsafe_offset = (i) - (S32(1))]))))) - ((slow29) * (((slow31) * (rec117[unsafe_offset = (i) - (S32(2))])) + (zec29[i])))
                rec125[unsafe_offset = i] = -((slow39) * (((slow22) * (rec125[unsafe_offset = (i) - (S32(1))])) - ((yec13[unsafe_offset = i]) + (yec13[unsafe_offset = (i) - (S32(1))]))))
                rec124[unsafe_offset = i] = (rec125[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec124[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec124[unsafe_offset = (i) - (S32(1))]))))
                yec14[unsafe_offset = i] = (slow41) * ((rec124[unsafe_offset = (i) - (S32(2))]) + ((rec124[unsafe_offset = i]) + ((2.0) * (rec124[unsafe_offset = (i) - (S32(1))]))))
                rec123[unsafe_offset = i] = -((slow44) * (((slow30) * (rec123[unsafe_offset = (i) - (S32(1))])) - ((slow27) * ((yec14[unsafe_offset = i]) - (yec14[unsafe_offset = (i) - (S32(1))])))))
                rec122[unsafe_offset = i] = (rec123[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec122[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec122[unsafe_offset = (i) - (S32(1))]))))
                rec127[unsafe_offset = i] = -((slow44) * (((slow30) * (rec127[unsafe_offset = (i) - (S32(1))])) - ((yec14[unsafe_offset = i]) + (yec14[unsafe_offset = (i) - (S32(1))]))))
                rec126[unsafe_offset = i] = (rec127[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec126[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec126[unsafe_offset = (i) - (S32(1))]))))
                rec132[unsafe_offset = i] = -((slow2) * (((slow3) * (rec132[unsafe_offset = (i) - (S32(1))])) - ((slow1) * ((rec10[unsafe_offset = (i) - (S32(1))]) - (rec10[unsafe_offset = (i) - (S32(2))])))))
                rec131[unsafe_offset = i] = (rec132[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec131[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec131[unsafe_offset = (i) - (S32(1))]))))
                zec30[i] = (slow17) * (rec130[unsafe_offset = (i) - (S32(1))])
                rec130[unsafe_offset = i] = ((slow9) * ((rec131[unsafe_offset = (i) - (S32(2))]) + ((rec131[unsafe_offset = i]) - ((2.0) * (rec131[unsafe_offset = (i) - (S32(1))]))))) - ((slow13) * (((slow15) * (rec130[unsafe_offset = (i) - (S32(2))])) + (zec30[i])))
                zec31[i] = (slow25) * (rec129[unsafe_offset = (i) - (S32(1))])
                rec129[unsafe_offset = i] = ((rec130[unsafe_offset = (i) - (S32(2))]) + ((slow13) * ((zec30[i]) + ((slow15) * (rec130[unsafe_offset = i]))))) - ((slow21) * (((slow23) * (rec129[unsafe_offset = (i) - (S32(2))])) + (zec31[i])))
                zec32[i] = (slow33) * (rec128[unsafe_offset = (i) - (S32(1))])
                rec128[unsafe_offset = i] = ((rec129[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec31[i]) + ((slow23) * (rec129[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec128[unsafe_offset = (i) - (S32(2))])) + (zec32[i])))
                rec138[unsafe_offset = i] = -((slow2) * (((slow3) * (rec138[unsafe_offset = (i) - (S32(1))])) - ((rec10[unsafe_offset = (i) - (S32(1))]) + (rec10[unsafe_offset = (i) - (S32(2))]))))
                rec137[unsafe_offset = i] = (rec138[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec137[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec137[unsafe_offset = (i) - (S32(1))]))))
                yec15[unsafe_offset = i] = (slow5) * ((rec137[unsafe_offset = (i) - (S32(2))]) + ((rec137[unsafe_offset = i]) + ((2.0) * (rec137[unsafe_offset = (i) - (S32(1))]))))
                rec136[unsafe_offset = i] = -((slow34) * (((slow14) * (rec136[unsafe_offset = (i) - (S32(1))])) - ((slow11) * ((yec15[unsafe_offset = i]) - (yec15[unsafe_offset = (i) - (S32(1))])))))
                rec135[unsafe_offset = i] = (rec136[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec135[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec135[unsafe_offset = (i) - (S32(1))]))))
                zec33[i] = (slow25) * (rec134[unsafe_offset = (i) - (S32(1))])
                rec134[unsafe_offset = i] = ((slow38) * ((rec135[unsafe_offset = (i) - (S32(2))]) + ((rec135[unsafe_offset = i]) - ((2.0) * (rec135[unsafe_offset = (i) - (S32(1))]))))) - ((slow21) * (((slow23) * (rec134[unsafe_offset = (i) - (S32(2))])) + (zec33[i])))
                zec34[i] = (slow33) * (rec133[unsafe_offset = (i) - (S32(1))])
                rec133[unsafe_offset = i] = ((rec134[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec33[i]) + ((slow23) * (rec134[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec133[unsafe_offset = (i) - (S32(2))])) + (zec34[i])))
                rec143[unsafe_offset = i] = -((slow34) * (((slow14) * (rec143[unsafe_offset = (i) - (S32(1))])) - ((yec15[unsafe_offset = i]) + (yec15[unsafe_offset = (i) - (S32(1))]))))
                rec142[unsafe_offset = i] = (rec143[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec142[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec142[unsafe_offset = (i) - (S32(1))]))))
                yec16[unsafe_offset = i] = (slow36) * ((rec142[unsafe_offset = (i) - (S32(2))]) + ((rec142[unsafe_offset = i]) + ((2.0) * (rec142[unsafe_offset = (i) - (S32(1))]))))
                rec141[unsafe_offset = i] = -((slow39) * (((slow22) * (rec141[unsafe_offset = (i) - (S32(1))])) - ((slow19) * ((yec16[unsafe_offset = i]) - (yec16[unsafe_offset = (i) - (S32(1))])))))
                rec140[unsafe_offset = i] = (rec141[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec140[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec140[unsafe_offset = (i) - (S32(1))]))))
                zec35[i] = (slow33) * (rec139[unsafe_offset = (i) - (S32(1))])
                rec139[unsafe_offset = i] = ((slow43) * ((rec140[unsafe_offset = (i) - (S32(2))]) + ((rec140[unsafe_offset = i]) - ((2.0) * (rec140[unsafe_offset = (i) - (S32(1))]))))) - ((slow29) * (((slow31) * (rec139[unsafe_offset = (i) - (S32(2))])) + (zec35[i])))
                rec147[unsafe_offset = i] = -((slow39) * (((slow22) * (rec147[unsafe_offset = (i) - (S32(1))])) - ((yec16[unsafe_offset = i]) + (yec16[unsafe_offset = (i) - (S32(1))]))))
                rec146[unsafe_offset = i] = (rec147[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec146[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec146[unsafe_offset = (i) - (S32(1))]))))
                yec17[unsafe_offset = i] = (slow41) * ((rec146[unsafe_offset = (i) - (S32(2))]) + ((rec146[unsafe_offset = i]) + ((2.0) * (rec146[unsafe_offset = (i) - (S32(1))]))))
                rec145[unsafe_offset = i] = -((slow44) * (((slow30) * (rec145[unsafe_offset = (i) - (S32(1))])) - ((slow27) * ((yec17[unsafe_offset = i]) - (yec17[unsafe_offset = (i) - (S32(1))])))))
                rec144[unsafe_offset = i] = (rec145[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec144[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec144[unsafe_offset = (i) - (S32(1))]))))
                rec149[unsafe_offset = i] = -((slow44) * (((slow30) * (rec149[unsafe_offset = (i) - (S32(1))])) - ((yec17[unsafe_offset = i]) + (yec17[unsafe_offset = (i) - (S32(1))]))))
                rec148[unsafe_offset = i] = (rec149[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec148[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec148[unsafe_offset = (i) - (S32(1))]))))
                rec154[unsafe_offset = i] = -((slow2) * (((slow3) * (rec154[unsafe_offset = (i) - (S32(1))])) - ((slow1) * ((rec6[unsafe_offset = (i) - (S32(1))]) - (rec6[unsafe_offset = (i) - (S32(2))])))))
                rec153[unsafe_offset = i] = (rec154[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec153[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec153[unsafe_offset = (i) - (S32(1))]))))
                zec36[i] = (slow17) * (rec152[unsafe_offset = (i) - (S32(1))])
                rec152[unsafe_offset = i] = ((slow9) * ((rec153[unsafe_offset = (i) - (S32(2))]) + ((rec153[unsafe_offset = i]) - ((2.0) * (rec153[unsafe_offset = (i) - (S32(1))]))))) - ((slow13) * (((slow15) * (rec152[unsafe_offset = (i) - (S32(2))])) + (zec36[i])))
                zec37[i] = (slow25) * (rec151[unsafe_offset = (i) - (S32(1))])
                rec151[unsafe_offset = i] = ((rec152[unsafe_offset = (i) - (S32(2))]) + ((slow13) * ((zec36[i]) + ((slow15) * (rec152[unsafe_offset = i]))))) - ((slow21) * (((slow23) * (rec151[unsafe_offset = (i) - (S32(2))])) + (zec37[i])))
                zec38[i] = (slow33) * (rec150[unsafe_offset = (i) - (S32(1))])
                rec150[unsafe_offset = i] = ((rec151[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec37[i]) + ((slow23) * (rec151[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec150[unsafe_offset = (i) - (S32(2))])) + (zec38[i])))
                rec160[unsafe_offset = i] = -((slow2) * (((slow3) * (rec160[unsafe_offset = (i) - (S32(1))])) - ((rec6[unsafe_offset = (i) - (S32(1))]) + (rec6[unsafe_offset = (i) - (S32(2))]))))
                rec159[unsafe_offset = i] = (rec160[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec159[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec159[unsafe_offset = (i) - (S32(1))]))))
                yec18[unsafe_offset = i] = (slow5) * ((rec159[unsafe_offset = (i) - (S32(2))]) + ((rec159[unsafe_offset = i]) + ((2.0) * (rec159[unsafe_offset = (i) - (S32(1))]))))
                rec158[unsafe_offset = i] = -((slow34) * (((slow14) * (rec158[unsafe_offset = (i) - (S32(1))])) - ((slow11) * ((yec18[unsafe_offset = i]) - (yec18[unsafe_offset = (i) - (S32(1))])))))
                rec157[unsafe_offset = i] = (rec158[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec157[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec157[unsafe_offset = (i) - (S32(1))]))))
                zec39[i] = (slow25) * (rec156[unsafe_offset = (i) - (S32(1))])
                rec156[unsafe_offset = i] = ((slow38) * ((rec157[unsafe_offset = (i) - (S32(2))]) + ((rec157[unsafe_offset = i]) - ((2.0) * (rec157[unsafe_offset = (i) - (S32(1))]))))) - ((slow21) * (((slow23) * (rec156[unsafe_offset = (i) - (S32(2))])) + (zec39[i])))
                zec40[i] = (slow33) * (rec155[unsafe_offset = (i) - (S32(1))])
                rec155[unsafe_offset = i] = ((rec156[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec39[i]) + ((slow23) * (rec156[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec155[unsafe_offset = (i) - (S32(2))])) + (zec40[i])))
                rec165[unsafe_offset = i] = -((slow34) * (((slow14) * (rec165[unsafe_offset = (i) - (S32(1))])) - ((yec18[unsafe_offset = i]) + (yec18[unsafe_offset = (i) - (S32(1))]))))
                rec164[unsafe_offset = i] = (rec165[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec164[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec164[unsafe_offset = (i) - (S32(1))]))))
                yec19[unsafe_offset = i] = (slow36) * ((rec164[unsafe_offset = (i) - (S32(2))]) + ((rec164[unsafe_offset = i]) + ((2.0) * (rec164[unsafe_offset = (i) - (S32(1))]))))
                rec163[unsafe_offset = i] = -((slow39) * (((slow22) * (rec163[unsafe_offset = (i) - (S32(1))])) - ((slow19) * ((yec19[unsafe_offset = i]) - (yec19[unsafe_offset = (i) - (S32(1))])))))
                rec162[unsafe_offset = i] = (rec163[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec162[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec162[unsafe_offset = (i) - (S32(1))]))))
                zec41[i] = (slow33) * (rec161[unsafe_offset = (i) - (S32(1))])
                rec161[unsafe_offset = i] = ((slow43) * ((rec162[unsafe_offset = (i) - (S32(2))]) + ((rec162[unsafe_offset = i]) - ((2.0) * (rec162[unsafe_offset = (i) - (S32(1))]))))) - ((slow29) * (((slow31) * (rec161[unsafe_offset = (i) - (S32(2))])) + (zec41[i])))
                rec169[unsafe_offset = i] = -((slow39) * (((slow22) * (rec169[unsafe_offset = (i) - (S32(1))])) - ((yec19[unsafe_offset = i]) + (yec19[unsafe_offset = (i) - (S32(1))]))))
                rec168[unsafe_offset = i] = (rec169[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec168[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec168[unsafe_offset = (i) - (S32(1))]))))
                yec20[unsafe_offset = i] = (slow41) * ((rec168[unsafe_offset = (i) - (S32(2))]) + ((rec168[unsafe_offset = i]) + ((2.0) * (rec168[unsafe_offset = (i) - (S32(1))]))))
                rec167[unsafe_offset = i] = -((slow44) * (((slow30) * (rec167[unsafe_offset = (i) - (S32(1))])) - ((slow27) * ((yec20[unsafe_offset = i]) - (yec20[unsafe_offset = (i) - (S32(1))])))))
                rec166[unsafe_offset = i] = (rec167[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec166[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec166[unsafe_offset = (i) - (S32(1))]))))
                rec171[unsafe_offset = i] = -((slow44) * (((slow30) * (rec171[unsafe_offset = (i) - (S32(1))])) - ((yec20[unsafe_offset = i]) + (yec20[unsafe_offset = (i) - (S32(1))]))))
                rec170[unsafe_offset = i] = (rec171[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec170[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec170[unsafe_offset = (i) - (S32(1))]))))
                rec176[unsafe_offset = i] = -((slow2) * (((slow3) * (rec176[unsafe_offset = (i) - (S32(1))])) - ((slow1) * ((rec14[unsafe_offset = (i) - (S32(1))]) - (rec14[unsafe_offset = (i) - (S32(2))])))))
                rec175[unsafe_offset = i] = (rec176[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec175[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec175[unsafe_offset = (i) - (S32(1))]))))
                zec42[i] = (slow17) * (rec174[unsafe_offset = (i) - (S32(1))])
                rec174[unsafe_offset = i] = ((slow9) * ((rec175[unsafe_offset = (i) - (S32(2))]) + ((rec175[unsafe_offset = i]) - ((2.0) * (rec175[unsafe_offset = (i) - (S32(1))]))))) - ((slow13) * (((slow15) * (rec174[unsafe_offset = (i) - (S32(2))])) + (zec42[i])))
                zec43[i] = (slow25) * (rec173[unsafe_offset = (i) - (S32(1))])
                rec173[unsafe_offset = i] = ((rec174[unsafe_offset = (i) - (S32(2))]) + ((slow13) * ((zec42[i]) + ((slow15) * (rec174[unsafe_offset = i]))))) - ((slow21) * (((slow23) * (rec173[unsafe_offset = (i) - (S32(2))])) + (zec43[i])))
                zec44[i] = (slow33) * (rec172[unsafe_offset = (i) - (S32(1))])
                rec172[unsafe_offset = i] = ((rec173[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec43[i]) + ((slow23) * (rec173[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec172[unsafe_offset = (i) - (S32(2))])) + (zec44[i])))
                rec182[unsafe_offset = i] = -((slow2) * (((slow3) * (rec182[unsafe_offset = (i) - (S32(1))])) - ((rec14[unsafe_offset = (i) - (S32(1))]) + (rec14[unsafe_offset = (i) - (S32(2))]))))
                rec181[unsafe_offset = i] = (rec182[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec181[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec181[unsafe_offset = (i) - (S32(1))]))))
                yec21[unsafe_offset = i] = (slow5) * ((rec181[unsafe_offset = (i) - (S32(2))]) + ((rec181[unsafe_offset = i]) + ((2.0) * (rec181[unsafe_offset = (i) - (S32(1))]))))
                rec180[unsafe_offset = i] = -((slow34) * (((slow14) * (rec180[unsafe_offset = (i) - (S32(1))])) - ((slow11) * ((yec21[unsafe_offset = i]) - (yec21[unsafe_offset = (i) - (S32(1))])))))
                rec179[unsafe_offset = i] = (rec180[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec179[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec179[unsafe_offset = (i) - (S32(1))]))))
                zec45[i] = (slow25) * (rec178[unsafe_offset = (i) - (S32(1))])
                rec178[unsafe_offset = i] = ((slow38) * ((rec179[unsafe_offset = (i) - (S32(2))]) + ((rec179[unsafe_offset = i]) - ((2.0) * (rec179[unsafe_offset = (i) - (S32(1))]))))) - ((slow21) * (((slow23) * (rec178[unsafe_offset = (i) - (S32(2))])) + (zec45[i])))
                zec46[i] = (slow33) * (rec177[unsafe_offset = (i) - (S32(1))])
                rec177[unsafe_offset = i] = ((rec178[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec45[i]) + ((slow23) * (rec178[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec177[unsafe_offset = (i) - (S32(2))])) + (zec46[i])))
                rec187[unsafe_offset = i] = -((slow34) * (((slow14) * (rec187[unsafe_offset = (i) - (S32(1))])) - ((yec21[unsafe_offset = i]) + (yec21[unsafe_offset = (i) - (S32(1))]))))
                rec186[unsafe_offset = i] = (rec187[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec186[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec186[unsafe_offset = (i) - (S32(1))]))))
                yec22[unsafe_offset = i] = (slow36) * ((rec186[unsafe_offset = (i) - (S32(2))]) + ((rec186[unsafe_offset = i]) + ((2.0) * (rec186[unsafe_offset = (i) - (S32(1))]))))
                rec185[unsafe_offset = i] = -((slow39) * (((slow22) * (rec185[unsafe_offset = (i) - (S32(1))])) - ((slow19) * ((yec22[unsafe_offset = i]) - (yec22[unsafe_offset = (i) - (S32(1))])))))
                rec184[unsafe_offset = i] = (rec185[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec184[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec184[unsafe_offset = (i) - (S32(1))]))))
                zec47[i] = (slow33) * (rec183[unsafe_offset = (i) - (S32(1))])
                rec183[unsafe_offset = i] = ((slow43) * ((rec184[unsafe_offset = (i) - (S32(2))]) + ((rec184[unsafe_offset = i]) - ((2.0) * (rec184[unsafe_offset = (i) - (S32(1))]))))) - ((slow29) * (((slow31) * (rec183[unsafe_offset = (i) - (S32(2))])) + (zec47[i])))
                rec191[unsafe_offset = i] = -((slow39) * (((slow22) * (rec191[unsafe_offset = (i) - (S32(1))])) - ((yec22[unsafe_offset = i]) + (yec22[unsafe_offset = (i) - (S32(1))]))))
                rec190[unsafe_offset = i] = (rec191[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec190[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec190[unsafe_offset = (i) - (S32(1))]))))
                yec23[unsafe_offset = i] = (slow41) * ((rec190[unsafe_offset = (i) - (S32(2))]) + ((rec190[unsafe_offset = i]) + ((2.0) * (rec190[unsafe_offset = (i) - (S32(1))]))))
                rec189[unsafe_offset = i] = -((slow44) * (((slow30) * (rec189[unsafe_offset = (i) - (S32(1))])) - ((slow27) * ((yec23[unsafe_offset = i]) - (yec23[unsafe_offset = (i) - (S32(1))])))))
                rec188[unsafe_offset = i] = (rec189[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec188[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec188[unsafe_offset = (i) - (S32(1))]))))
                rec193[unsafe_offset = i] = -((slow44) * (((slow30) * (rec193[unsafe_offset = (i) - (S32(1))])) - ((yec23[unsafe_offset = i]) + (yec23[unsafe_offset = (i) - (S32(1))]))))
                rec192[unsafe_offset = i] = (rec193[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec192[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec192[unsafe_offset = (i) - (S32(1))]))))
                rec198[unsafe_offset = i] = -((slow2) * (((slow3) * (rec198[unsafe_offset = (i) - (S32(1))])) - ((slow1) * ((rec1[unsafe_offset = (i) - (S32(1))]) - (rec1[unsafe_offset = (i) - (S32(2))])))))
                rec197[unsafe_offset = i] = (rec198[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec197[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec197[unsafe_offset = (i) - (S32(1))]))))
                zec48[i] = (slow17) * (rec196[unsafe_offset = (i) - (S32(1))])
                rec196[unsafe_offset = i] = ((slow9) * ((rec197[unsafe_offset = (i) - (S32(2))]) + ((rec197[unsafe_offset = i]) - ((2.0) * (rec197[unsafe_offset = (i) - (S32(1))]))))) - ((slow13) * (((slow15) * (rec196[unsafe_offset = (i) - (S32(2))])) + (zec48[i])))
                zec49[i] = (slow25) * (rec195[unsafe_offset = (i) - (S32(1))])
                rec195[unsafe_offset = i] = ((rec196[unsafe_offset = (i) - (S32(2))]) + ((slow13) * ((zec48[i]) + ((slow15) * (rec196[unsafe_offset = i]))))) - ((slow21) * (((slow23) * (rec195[unsafe_offset = (i) - (S32(2))])) + (zec49[i])))
                zec50[i] = (slow33) * (rec194[unsafe_offset = (i) - (S32(1))])
                rec194[unsafe_offset = i] = ((rec195[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec49[i]) + ((slow23) * (rec195[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec194[unsafe_offset = (i) - (S32(2))])) + (zec50[i])))
                rec204[unsafe_offset = i] = -((slow2) * (((slow3) * (rec204[unsafe_offset = (i) - (S32(1))])) - ((rec1[unsafe_offset = (i) - (S32(1))]) + (rec1[unsafe_offset = (i) - (S32(2))]))))
                rec203[unsafe_offset = i] = (rec204[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec203[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec203[unsafe_offset = (i) - (S32(1))]))))
                yec24[unsafe_offset = i] = (slow5) * ((rec203[unsafe_offset = (i) - (S32(2))]) + ((rec203[unsafe_offset = i]) + ((2.0) * (rec203[unsafe_offset = (i) - (S32(1))]))))
                rec202[unsafe_offset = i] = -((slow34) * (((slow14) * (rec202[unsafe_offset = (i) - (S32(1))])) - ((slow11) * ((yec24[unsafe_offset = i]) - (yec24[unsafe_offset = (i) - (S32(1))])))))
                rec201[unsafe_offset = i] = (rec202[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec201[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec201[unsafe_offset = (i) - (S32(1))]))))
                zec51[i] = (slow25) * (rec200[unsafe_offset = (i) - (S32(1))])
                rec200[unsafe_offset = i] = ((slow38) * ((rec201[unsafe_offset = (i) - (S32(2))]) + ((rec201[unsafe_offset = i]) - ((2.0) * (rec201[unsafe_offset = (i) - (S32(1))]))))) - ((slow21) * (((slow23) * (rec200[unsafe_offset = (i) - (S32(2))])) + (zec51[i])))
                zec52[i] = (slow33) * (rec199[unsafe_offset = (i) - (S32(1))])
                rec199[unsafe_offset = i] = ((rec200[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec51[i]) + ((slow23) * (rec200[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec199[unsafe_offset = (i) - (S32(2))])) + (zec52[i])))
                rec209[unsafe_offset = i] = -((slow34) * (((slow14) * (rec209[unsafe_offset = (i) - (S32(1))])) - ((yec24[unsafe_offset = i]) + (yec24[unsafe_offset = (i) - (S32(1))]))))
                rec208[unsafe_offset = i] = (rec209[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec208[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec208[unsafe_offset = (i) - (S32(1))]))))
                yec25[unsafe_offset = i] = (slow36) * ((rec208[unsafe_offset = (i) - (S32(2))]) + ((rec208[unsafe_offset = i]) + ((2.0) * (rec208[unsafe_offset = (i) - (S32(1))]))))
                rec207[unsafe_offset = i] = -((slow39) * (((slow22) * (rec207[unsafe_offset = (i) - (S32(1))])) - ((slow19) * ((yec25[unsafe_offset = i]) - (yec25[unsafe_offset = (i) - (S32(1))])))))
                rec206[unsafe_offset = i] = (rec207[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec206[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec206[unsafe_offset = (i) - (S32(1))]))))
                zec53[i] = (slow33) * (rec205[unsafe_offset = (i) - (S32(1))])
                rec205[unsafe_offset = i] = ((slow43) * ((rec206[unsafe_offset = (i) - (S32(2))]) + ((rec206[unsafe_offset = i]) - ((2.0) * (rec206[unsafe_offset = (i) - (S32(1))]))))) - ((slow29) * (((slow31) * (rec205[unsafe_offset = (i) - (S32(2))])) + (zec53[i])))
                rec213[unsafe_offset = i] = -((slow39) * (((slow22) * (rec213[unsafe_offset = (i) - (S32(1))])) - ((yec25[unsafe_offset = i]) + (yec25[unsafe_offset = (i) - (S32(1))]))))
                rec212[unsafe_offset = i] = (rec213[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec212[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec212[unsafe_offset = (i) - (S32(1))]))))
                yec26[unsafe_offset = i] = (slow41) * ((rec212[unsafe_offset = (i) - (S32(2))]) + ((rec212[unsafe_offset = i]) + ((2.0) * (rec212[unsafe_offset = (i) - (S32(1))]))))
                rec211[unsafe_offset = i] = -((slow44) * (((slow30) * (rec211[unsafe_offset = (i) - (S32(1))])) - ((slow27) * ((yec26[unsafe_offset = i]) - (yec26[unsafe_offset = (i) - (S32(1))])))))
                rec210[unsafe_offset = i] = (rec211[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec210[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec210[unsafe_offset = (i) - (S32(1))]))))
                rec215[unsafe_offset = i] = -((slow44) * (((slow30) * (rec215[unsafe_offset = (i) - (S32(1))])) - ((yec26[unsafe_offset = i]) + (yec26[unsafe_offset = (i) - (S32(1))]))))
                rec214[unsafe_offset = i] = (rec215[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec214[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec214[unsafe_offset = (i) - (S32(1))]))))
                rec220[unsafe_offset = i] = -((slow2) * (((slow3) * (rec220[unsafe_offset = (i) - (S32(1))])) - ((slow1) * ((rec9[unsafe_offset = (i) - (S32(1))]) - (rec9[unsafe_offset = (i) - (S32(2))])))))
                rec219[unsafe_offset = i] = (rec220[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec219[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec219[unsafe_offset = (i) - (S32(1))]))))
                zec54[i] = (slow17) * (rec218[unsafe_offset = (i) - (S32(1))])
                rec218[unsafe_offset = i] = ((slow9) * ((rec219[unsafe_offset = (i) - (S32(2))]) + ((rec219[unsafe_offset = i]) - ((2.0) * (rec219[unsafe_offset = (i) - (S32(1))]))))) - ((slow13) * (((slow15) * (rec218[unsafe_offset = (i) - (S32(2))])) + (zec54[i])))
                zec55[i] = (slow25) * (rec217[unsafe_offset = (i) - (S32(1))])
                rec217[unsafe_offset = i] = ((rec218[unsafe_offset = (i) - (S32(2))]) + ((slow13) * ((zec54[i]) + ((slow15) * (rec218[unsafe_offset = i]))))) - ((slow21) * (((slow23) * (rec217[unsafe_offset = (i) - (S32(2))])) + (zec55[i])))
                zec56[i] = (slow33) * (rec216[unsafe_offset = (i) - (S32(1))])
                rec216[unsafe_offset = i] = ((rec217[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec55[i]) + ((slow23) * (rec217[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec216[unsafe_offset = (i) - (S32(2))])) + (zec56[i])))
                rec226[unsafe_offset = i] = -((slow2) * (((slow3) * (rec226[unsafe_offset = (i) - (S32(1))])) - ((rec9[unsafe_offset = (i) - (S32(1))]) + (rec9[unsafe_offset = (i) - (S32(2))]))))
                rec225[unsafe_offset = i] = (rec226[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec225[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec225[unsafe_offset = (i) - (S32(1))]))))
                yec27[unsafe_offset = i] = (slow5) * ((rec225[unsafe_offset = (i) - (S32(2))]) + ((rec225[unsafe_offset = i]) + ((2.0) * (rec225[unsafe_offset = (i) - (S32(1))]))))
                rec224[unsafe_offset = i] = -((slow34) * (((slow14) * (rec224[unsafe_offset = (i) - (S32(1))])) - ((slow11) * ((yec27[unsafe_offset = i]) - (yec27[unsafe_offset = (i) - (S32(1))])))))
                rec223[unsafe_offset = i] = (rec224[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec223[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec223[unsafe_offset = (i) - (S32(1))]))))
                zec57[i] = (slow25) * (rec222[unsafe_offset = (i) - (S32(1))])
                rec222[unsafe_offset = i] = ((slow38) * ((rec223[unsafe_offset = (i) - (S32(2))]) + ((rec223[unsafe_offset = i]) - ((2.0) * (rec223[unsafe_offset = (i) - (S32(1))]))))) - ((slow21) * (((slow23) * (rec222[unsafe_offset = (i) - (S32(2))])) + (zec57[i])))
                zec58[i] = (slow33) * (rec221[unsafe_offset = (i) - (S32(1))])
                rec221[unsafe_offset = i] = ((rec222[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec57[i]) + ((slow23) * (rec222[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec221[unsafe_offset = (i) - (S32(2))])) + (zec58[i])))
                rec231[unsafe_offset = i] = -((slow34) * (((slow14) * (rec231[unsafe_offset = (i) - (S32(1))])) - ((yec27[unsafe_offset = i]) + (yec27[unsafe_offset = (i) - (S32(1))]))))
                rec230[unsafe_offset = i] = (rec231[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec230[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec230[unsafe_offset = (i) - (S32(1))]))))
                yec28[unsafe_offset = i] = (slow36) * ((rec230[unsafe_offset = (i) - (S32(2))]) + ((rec230[unsafe_offset = i]) + ((2.0) * (rec230[unsafe_offset = (i) - (S32(1))]))))
                rec229[unsafe_offset = i] = -((slow39) * (((slow22) * (rec229[unsafe_offset = (i) - (S32(1))])) - ((slow19) * ((yec28[unsafe_offset = i]) - (yec28[unsafe_offset = (i) - (S32(1))])))))
                rec228[unsafe_offset = i] = (rec229[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec228[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec228[unsafe_offset = (i) - (S32(1))]))))
                zec59[i] = (slow33) * (rec227[unsafe_offset = (i) - (S32(1))])
                rec227[unsafe_offset = i] = ((slow43) * ((rec228[unsafe_offset = (i) - (S32(2))]) + ((rec228[unsafe_offset = i]) - ((2.0) * (rec228[unsafe_offset = (i) - (S32(1))]))))) - ((slow29) * (((slow31) * (rec227[unsafe_offset = (i) - (S32(2))])) + (zec59[i])))
                rec235[unsafe_offset = i] = -((slow39) * (((slow22) * (rec235[unsafe_offset = (i) - (S32(1))])) - ((yec28[unsafe_offset = i]) + (yec28[unsafe_offset = (i) - (S32(1))]))))
                rec234[unsafe_offset = i] = (rec235[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec234[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec234[unsafe_offset = (i) - (S32(1))]))))
                yec29[unsafe_offset = i] = (slow41) * ((rec234[unsafe_offset = (i) - (S32(2))]) + ((rec234[unsafe_offset = i]) + ((2.0) * (rec234[unsafe_offset = (i) - (S32(1))]))))
                rec233[unsafe_offset = i] = -((slow44) * (((slow30) * (rec233[unsafe_offset = (i) - (S32(1))])) - ((slow27) * ((yec29[unsafe_offset = i]) - (yec29[unsafe_offset = (i) - (S32(1))])))))
                rec232[unsafe_offset = i] = (rec233[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec232[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec232[unsafe_offset = (i) - (S32(1))]))))
                rec237[unsafe_offset = i] = -((slow44) * (((slow30) * (rec237[unsafe_offset = (i) - (S32(1))])) - ((yec29[unsafe_offset = i]) + (yec29[unsafe_offset = (i) - (S32(1))]))))
                rec236[unsafe_offset = i] = (rec237[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec236[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec236[unsafe_offset = (i) - (S32(1))]))))
                rec242[unsafe_offset = i] = -((slow2) * (((slow3) * (rec242[unsafe_offset = (i) - (S32(1))])) - ((slow1) * ((rec5[unsafe_offset = (i) - (S32(1))]) - (rec5[unsafe_offset = (i) - (S32(2))])))))
                rec241[unsafe_offset = i] = (rec242[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec241[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec241[unsafe_offset = (i) - (S32(1))]))))
                zec60[i] = (slow17) * (rec240[unsafe_offset = (i) - (S32(1))])
                rec240[unsafe_offset = i] = ((slow9) * ((rec241[unsafe_offset = (i) - (S32(2))]) + ((rec241[unsafe_offset = i]) - ((2.0) * (rec241[unsafe_offset = (i) - (S32(1))]))))) - ((slow13) * (((slow15) * (rec240[unsafe_offset = (i) - (S32(2))])) + (zec60[i])))
                zec61[i] = (slow25) * (rec239[unsafe_offset = (i) - (S32(1))])
                rec239[unsafe_offset = i] = ((rec240[unsafe_offset = (i) - (S32(2))]) + ((slow13) * ((zec60[i]) + ((slow15) * (rec240[unsafe_offset = i]))))) - ((slow21) * (((slow23) * (rec239[unsafe_offset = (i) - (S32(2))])) + (zec61[i])))
                zec62[i] = (slow33) * (rec238[unsafe_offset = (i) - (S32(1))])
                rec238[unsafe_offset = i] = ((rec239[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec61[i]) + ((slow23) * (rec239[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec238[unsafe_offset = (i) - (S32(2))])) + (zec62[i])))
                rec248[unsafe_offset = i] = -((slow2) * (((slow3) * (rec248[unsafe_offset = (i) - (S32(1))])) - ((rec5[unsafe_offset = (i) - (S32(1))]) + (rec5[unsafe_offset = (i) - (S32(2))]))))
                rec247[unsafe_offset = i] = (rec248[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec247[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec247[unsafe_offset = (i) - (S32(1))]))))
                yec30[unsafe_offset = i] = (slow5) * ((rec247[unsafe_offset = (i) - (S32(2))]) + ((rec247[unsafe_offset = i]) + ((2.0) * (rec247[unsafe_offset = (i) - (S32(1))]))))
                rec246[unsafe_offset = i] = -((slow34) * (((slow14) * (rec246[unsafe_offset = (i) - (S32(1))])) - ((slow11) * ((yec30[unsafe_offset = i]) - (yec30[unsafe_offset = (i) - (S32(1))])))))
                rec245[unsafe_offset = i] = (rec246[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec245[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec245[unsafe_offset = (i) - (S32(1))]))))
                zec63[i] = (slow25) * (rec244[unsafe_offset = (i) - (S32(1))])
                rec244[unsafe_offset = i] = ((slow38) * ((rec245[unsafe_offset = (i) - (S32(2))]) + ((rec245[unsafe_offset = i]) - ((2.0) * (rec245[unsafe_offset = (i) - (S32(1))]))))) - ((slow21) * (((slow23) * (rec244[unsafe_offset = (i) - (S32(2))])) + (zec63[i])))
                zec64[i] = (slow33) * (rec243[unsafe_offset = (i) - (S32(1))])
                rec243[unsafe_offset = i] = ((rec244[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec63[i]) + ((slow23) * (rec244[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec243[unsafe_offset = (i) - (S32(2))])) + (zec64[i])))
                rec253[unsafe_offset = i] = -((slow34) * (((slow14) * (rec253[unsafe_offset = (i) - (S32(1))])) - ((yec30[unsafe_offset = i]) + (yec30[unsafe_offset = (i) - (S32(1))]))))
                rec252[unsafe_offset = i] = (rec253[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec252[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec252[unsafe_offset = (i) - (S32(1))]))))
                yec31[unsafe_offset = i] = (slow36) * ((rec252[unsafe_offset = (i) - (S32(2))]) + ((rec252[unsafe_offset = i]) + ((2.0) * (rec252[unsafe_offset = (i) - (S32(1))]))))
                rec251[unsafe_offset = i] = -((slow39) * (((slow22) * (rec251[unsafe_offset = (i) - (S32(1))])) - ((slow19) * ((yec31[unsafe_offset = i]) - (yec31[unsafe_offset = (i) - (S32(1))])))))
                rec250[unsafe_offset = i] = (rec251[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec250[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec250[unsafe_offset = (i) - (S32(1))]))))
                zec65[i] = (slow33) * (rec249[unsafe_offset = (i) - (S32(1))])
                rec249[unsafe_offset = i] = ((slow43) * ((rec250[unsafe_offset = (i) - (S32(2))]) + ((rec250[unsafe_offset = i]) - ((2.0) * (rec250[unsafe_offset = (i) - (S32(1))]))))) - ((slow29) * (((slow31) * (rec249[unsafe_offset = (i) - (S32(2))])) + (zec65[i])))
                rec257[unsafe_offset = i] = -((slow39) * (((slow22) * (rec257[unsafe_offset = (i) - (S32(1))])) - ((yec31[unsafe_offset = i]) + (yec31[unsafe_offset = (i) - (S32(1))]))))
                rec256[unsafe_offset = i] = (rec257[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec256[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec256[unsafe_offset = (i) - (S32(1))]))))
                yec32[unsafe_offset = i] = (slow41) * ((rec256[unsafe_offset = (i) - (S32(2))]) + ((rec256[unsafe_offset = i]) + ((2.0) * (rec256[unsafe_offset = (i) - (S32(1))]))))
                rec255[unsafe_offset = i] = -((slow44) * (((slow30) * (rec255[unsafe_offset = (i) - (S32(1))])) - ((slow27) * ((yec32[unsafe_offset = i]) - (yec32[unsafe_offset = (i) - (S32(1))])))))
                rec254[unsafe_offset = i] = (rec255[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec254[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec254[unsafe_offset = (i) - (S32(1))]))))
                rec259[unsafe_offset = i] = -((slow44) * (((slow30) * (rec259[unsafe_offset = (i) - (S32(1))])) - ((yec32[unsafe_offset = i]) + (yec32[unsafe_offset = (i) - (S32(1))]))))
                rec258[unsafe_offset = i] = (rec259[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec258[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec258[unsafe_offset = (i) - (S32(1))]))))
                rec264[unsafe_offset = i] = -((slow2) * (((slow3) * (rec264[unsafe_offset = (i) - (S32(1))])) - ((slow1) * ((rec13[unsafe_offset = (i) - (S32(1))]) - (rec13[unsafe_offset = (i) - (S32(2))])))))
                rec263[unsafe_offset = i] = (rec264[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec263[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec263[unsafe_offset = (i) - (S32(1))]))))
                zec66[i] = (slow17) * (rec262[unsafe_offset = (i) - (S32(1))])
                rec262[unsafe_offset = i] = ((slow9) * ((rec263[unsafe_offset = (i) - (S32(2))]) + ((rec263[unsafe_offset = i]) - ((2.0) * (rec263[unsafe_offset = (i) - (S32(1))]))))) - ((slow13) * (((slow15) * (rec262[unsafe_offset = (i) - (S32(2))])) + (zec66[i])))
                zec67[i] = (slow25) * (rec261[unsafe_offset = (i) - (S32(1))])
                rec261[unsafe_offset = i] = ((rec262[unsafe_offset = (i) - (S32(2))]) + ((slow13) * ((zec66[i]) + ((slow15) * (rec262[unsafe_offset = i]))))) - ((slow21) * (((slow23) * (rec261[unsafe_offset = (i) - (S32(2))])) + (zec67[i])))
                zec68[i] = (slow33) * (rec260[unsafe_offset = (i) - (S32(1))])
                rec260[unsafe_offset = i] = ((rec261[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec67[i]) + ((slow23) * (rec261[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec260[unsafe_offset = (i) - (S32(2))])) + (zec68[i])))
                rec270[unsafe_offset = i] = -((slow2) * (((slow3) * (rec270[unsafe_offset = (i) - (S32(1))])) - ((rec13[unsafe_offset = (i) - (S32(1))]) + (rec13[unsafe_offset = (i) - (S32(2))]))))
                rec269[unsafe_offset = i] = (rec270[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec269[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec269[unsafe_offset = (i) - (S32(1))]))))
                yec33[unsafe_offset = i] = (slow5) * ((rec269[unsafe_offset = (i) - (S32(2))]) + ((rec269[unsafe_offset = i]) + ((2.0) * (rec269[unsafe_offset = (i) - (S32(1))]))))
                rec268[unsafe_offset = i] = -((slow34) * (((slow14) * (rec268[unsafe_offset = (i) - (S32(1))])) - ((slow11) * ((yec33[unsafe_offset = i]) - (yec33[unsafe_offset = (i) - (S32(1))])))))
                rec267[unsafe_offset = i] = (rec268[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec267[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec267[unsafe_offset = (i) - (S32(1))]))))
                zec69[i] = (slow25) * (rec266[unsafe_offset = (i) - (S32(1))])
                rec266[unsafe_offset = i] = ((slow38) * ((rec267[unsafe_offset = (i) - (S32(2))]) + ((rec267[unsafe_offset = i]) - ((2.0) * (rec267[unsafe_offset = (i) - (S32(1))]))))) - ((slow21) * (((slow23) * (rec266[unsafe_offset = (i) - (S32(2))])) + (zec69[i])))
                zec70[i] = (slow33) * (rec265[unsafe_offset = (i) - (S32(1))])
                rec265[unsafe_offset = i] = ((rec266[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec69[i]) + ((slow23) * (rec266[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec265[unsafe_offset = (i) - (S32(2))])) + (zec70[i])))
                rec275[unsafe_offset = i] = -((slow34) * (((slow14) * (rec275[unsafe_offset = (i) - (S32(1))])) - ((yec33[unsafe_offset = i]) + (yec33[unsafe_offset = (i) - (S32(1))]))))
                rec274[unsafe_offset = i] = (rec275[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec274[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec274[unsafe_offset = (i) - (S32(1))]))))
                yec34[unsafe_offset = i] = (slow36) * ((rec274[unsafe_offset = (i) - (S32(2))]) + ((rec274[unsafe_offset = i]) + ((2.0) * (rec274[unsafe_offset = (i) - (S32(1))]))))
                rec273[unsafe_offset = i] = -((slow39) * (((slow22) * (rec273[unsafe_offset = (i) - (S32(1))])) - ((slow19) * ((yec34[unsafe_offset = i]) - (yec34[unsafe_offset = (i) - (S32(1))])))))
                rec272[unsafe_offset = i] = (rec273[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec272[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec272[unsafe_offset = (i) - (S32(1))]))))
                zec71[i] = (slow33) * (rec271[unsafe_offset = (i) - (S32(1))])
                rec271[unsafe_offset = i] = ((slow43) * ((rec272[unsafe_offset = (i) - (S32(2))]) + ((rec272[unsafe_offset = i]) - ((2.0) * (rec272[unsafe_offset = (i) - (S32(1))]))))) - ((slow29) * (((slow31) * (rec271[unsafe_offset = (i) - (S32(2))])) + (zec71[i])))
                rec279[unsafe_offset = i] = -((slow39) * (((slow22) * (rec279[unsafe_offset = (i) - (S32(1))])) - ((yec34[unsafe_offset = i]) + (yec34[unsafe_offset = (i) - (S32(1))]))))
                rec278[unsafe_offset = i] = (rec279[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec278[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec278[unsafe_offset = (i) - (S32(1))]))))
                yec35[unsafe_offset = i] = (slow41) * ((rec278[unsafe_offset = (i) - (S32(2))]) + ((rec278[unsafe_offset = i]) + ((2.0) * (rec278[unsafe_offset = (i) - (S32(1))]))))
                rec277[unsafe_offset = i] = -((slow44) * (((slow30) * (rec277[unsafe_offset = (i) - (S32(1))])) - ((slow27) * ((yec35[unsafe_offset = i]) - (yec35[unsafe_offset = (i) - (S32(1))])))))
                rec276[unsafe_offset = i] = (rec277[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec276[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec276[unsafe_offset = (i) - (S32(1))]))))
                rec281[unsafe_offset = i] = -((slow44) * (((slow30) * (rec281[unsafe_offset = (i) - (S32(1))])) - ((yec35[unsafe_offset = i]) + (yec35[unsafe_offset = (i) - (S32(1))]))))
                rec280[unsafe_offset = i] = (rec281[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec280[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec280[unsafe_offset = (i) - (S32(1))]))))
                rec286[unsafe_offset = i] = -((slow2) * (((slow3) * (rec286[unsafe_offset = (i) - (S32(1))])) - ((slow1) * ((rec3[unsafe_offset = (i) - (S32(1))]) - (rec3[unsafe_offset = (i) - (S32(2))])))))
                rec285[unsafe_offset = i] = (rec286[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec285[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec285[unsafe_offset = (i) - (S32(1))]))))
                zec72[i] = (slow17) * (rec284[unsafe_offset = (i) - (S32(1))])
                rec284[unsafe_offset = i] = ((slow9) * ((rec285[unsafe_offset = (i) - (S32(2))]) + ((rec285[unsafe_offset = i]) - ((2.0) * (rec285[unsafe_offset = (i) - (S32(1))]))))) - ((slow13) * (((slow15) * (rec284[unsafe_offset = (i) - (S32(2))])) + (zec72[i])))
                zec73[i] = (slow25) * (rec283[unsafe_offset = (i) - (S32(1))])
                rec283[unsafe_offset = i] = ((rec284[unsafe_offset = (i) - (S32(2))]) + ((slow13) * ((zec72[i]) + ((slow15) * (rec284[unsafe_offset = i]))))) - ((slow21) * (((slow23) * (rec283[unsafe_offset = (i) - (S32(2))])) + (zec73[i])))
                zec74[i] = (slow33) * (rec282[unsafe_offset = (i) - (S32(1))])
                rec282[unsafe_offset = i] = ((rec283[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec73[i]) + ((slow23) * (rec283[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec282[unsafe_offset = (i) - (S32(2))])) + (zec74[i])))
                rec292[unsafe_offset = i] = -((slow2) * (((slow3) * (rec292[unsafe_offset = (i) - (S32(1))])) - ((rec3[unsafe_offset = (i) - (S32(1))]) + (rec3[unsafe_offset = (i) - (S32(2))]))))
                rec291[unsafe_offset = i] = (rec292[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec291[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec291[unsafe_offset = (i) - (S32(1))]))))
                yec36[unsafe_offset = i] = (slow5) * ((rec291[unsafe_offset = (i) - (S32(2))]) + ((rec291[unsafe_offset = i]) + ((2.0) * (rec291[unsafe_offset = (i) - (S32(1))]))))
                rec290[unsafe_offset = i] = -((slow34) * (((slow14) * (rec290[unsafe_offset = (i) - (S32(1))])) - ((slow11) * ((yec36[unsafe_offset = i]) - (yec36[unsafe_offset = (i) - (S32(1))])))))
                rec289[unsafe_offset = i] = (rec290[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec289[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec289[unsafe_offset = (i) - (S32(1))]))))
                zec75[i] = (slow25) * (rec288[unsafe_offset = (i) - (S32(1))])
                rec288[unsafe_offset = i] = ((slow38) * ((rec289[unsafe_offset = (i) - (S32(2))]) + ((rec289[unsafe_offset = i]) - ((2.0) * (rec289[unsafe_offset = (i) - (S32(1))]))))) - ((slow21) * (((slow23) * (rec288[unsafe_offset = (i) - (S32(2))])) + (zec75[i])))
                zec76[i] = (slow33) * (rec287[unsafe_offset = (i) - (S32(1))])
                rec287[unsafe_offset = i] = ((rec288[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec75[i]) + ((slow23) * (rec288[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec287[unsafe_offset = (i) - (S32(2))])) + (zec76[i])))
                rec297[unsafe_offset = i] = -((slow34) * (((slow14) * (rec297[unsafe_offset = (i) - (S32(1))])) - ((yec36[unsafe_offset = i]) + (yec36[unsafe_offset = (i) - (S32(1))]))))
                rec296[unsafe_offset = i] = (rec297[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec296[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec296[unsafe_offset = (i) - (S32(1))]))))
                yec37[unsafe_offset = i] = (slow36) * ((rec296[unsafe_offset = (i) - (S32(2))]) + ((rec296[unsafe_offset = i]) + ((2.0) * (rec296[unsafe_offset = (i) - (S32(1))]))))
                rec295[unsafe_offset = i] = -((slow39) * (((slow22) * (rec295[unsafe_offset = (i) - (S32(1))])) - ((slow19) * ((yec37[unsafe_offset = i]) - (yec37[unsafe_offset = (i) - (S32(1))])))))
                rec294[unsafe_offset = i] = (rec295[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec294[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec294[unsafe_offset = (i) - (S32(1))]))))
                zec77[i] = (slow33) * (rec293[unsafe_offset = (i) - (S32(1))])
                rec293[unsafe_offset = i] = ((slow43) * ((rec294[unsafe_offset = (i) - (S32(2))]) + ((rec294[unsafe_offset = i]) - ((2.0) * (rec294[unsafe_offset = (i) - (S32(1))]))))) - ((slow29) * (((slow31) * (rec293[unsafe_offset = (i) - (S32(2))])) + (zec77[i])))
                rec301[unsafe_offset = i] = -((slow39) * (((slow22) * (rec301[unsafe_offset = (i) - (S32(1))])) - ((yec37[unsafe_offset = i]) + (yec37[unsafe_offset = (i) - (S32(1))]))))
                rec300[unsafe_offset = i] = (rec301[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec300[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec300[unsafe_offset = (i) - (S32(1))]))))
                yec38[unsafe_offset = i] = (slow41) * ((rec300[unsafe_offset = (i) - (S32(2))]) + ((rec300[unsafe_offset = i]) + ((2.0) * (rec300[unsafe_offset = (i) - (S32(1))]))))
                rec299[unsafe_offset = i] = -((slow44) * (((slow30) * (rec299[unsafe_offset = (i) - (S32(1))])) - ((slow27) * ((yec38[unsafe_offset = i]) - (yec38[unsafe_offset = (i) - (S32(1))])))))
                rec298[unsafe_offset = i] = (rec299[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec298[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec298[unsafe_offset = (i) - (S32(1))]))))
                rec303[unsafe_offset = i] = -((slow44) * (((slow30) * (rec303[unsafe_offset = (i) - (S32(1))])) - ((yec38[unsafe_offset = i]) + (yec38[unsafe_offset = (i) - (S32(1))]))))
                rec302[unsafe_offset = i] = (rec303[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec302[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec302[unsafe_offset = (i) - (S32(1))]))))
                rec308[unsafe_offset = i] = -((slow2) * (((slow3) * (rec308[unsafe_offset = (i) - (S32(1))])) - ((slow1) * ((rec11[unsafe_offset = (i) - (S32(1))]) - (rec11[unsafe_offset = (i) - (S32(2))])))))
                rec307[unsafe_offset = i] = (rec308[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec307[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec307[unsafe_offset = (i) - (S32(1))]))))
                zec78[i] = (slow17) * (rec306[unsafe_offset = (i) - (S32(1))])
                rec306[unsafe_offset = i] = ((slow9) * ((rec307[unsafe_offset = (i) - (S32(2))]) + ((rec307[unsafe_offset = i]) - ((2.0) * (rec307[unsafe_offset = (i) - (S32(1))]))))) - ((slow13) * (((slow15) * (rec306[unsafe_offset = (i) - (S32(2))])) + (zec78[i])))
                zec79[i] = (slow25) * (rec305[unsafe_offset = (i) - (S32(1))])
                rec305[unsafe_offset = i] = ((rec306[unsafe_offset = (i) - (S32(2))]) + ((slow13) * ((zec78[i]) + ((slow15) * (rec306[unsafe_offset = i]))))) - ((slow21) * (((slow23) * (rec305[unsafe_offset = (i) - (S32(2))])) + (zec79[i])))
                zec80[i] = (slow33) * (rec304[unsafe_offset = (i) - (S32(1))])
                rec304[unsafe_offset = i] = ((rec305[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec79[i]) + ((slow23) * (rec305[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec304[unsafe_offset = (i) - (S32(2))])) + (zec80[i])))
                rec314[unsafe_offset = i] = -((slow2) * (((slow3) * (rec314[unsafe_offset = (i) - (S32(1))])) - ((rec11[unsafe_offset = (i) - (S32(1))]) + (rec11[unsafe_offset = (i) - (S32(2))]))))
                rec313[unsafe_offset = i] = (rec314[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec313[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec313[unsafe_offset = (i) - (S32(1))]))))
                yec39[unsafe_offset = i] = (slow5) * ((rec313[unsafe_offset = (i) - (S32(2))]) + ((rec313[unsafe_offset = i]) + ((2.0) * (rec313[unsafe_offset = (i) - (S32(1))]))))
                rec312[unsafe_offset = i] = -((slow34) * (((slow14) * (rec312[unsafe_offset = (i) - (S32(1))])) - ((slow11) * ((yec39[unsafe_offset = i]) - (yec39[unsafe_offset = (i) - (S32(1))])))))
                rec311[unsafe_offset = i] = (rec312[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec311[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec311[unsafe_offset = (i) - (S32(1))]))))
                zec81[i] = (slow25) * (rec310[unsafe_offset = (i) - (S32(1))])
                rec310[unsafe_offset = i] = ((slow38) * ((rec311[unsafe_offset = (i) - (S32(2))]) + ((rec311[unsafe_offset = i]) - ((2.0) * (rec311[unsafe_offset = (i) - (S32(1))]))))) - ((slow21) * (((slow23) * (rec310[unsafe_offset = (i) - (S32(2))])) + (zec81[i])))
                zec82[i] = (slow33) * (rec309[unsafe_offset = (i) - (S32(1))])
                rec309[unsafe_offset = i] = ((rec310[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec81[i]) + ((slow23) * (rec310[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec309[unsafe_offset = (i) - (S32(2))])) + (zec82[i])))
                rec319[unsafe_offset = i] = -((slow34) * (((slow14) * (rec319[unsafe_offset = (i) - (S32(1))])) - ((yec39[unsafe_offset = i]) + (yec39[unsafe_offset = (i) - (S32(1))]))))
                rec318[unsafe_offset = i] = (rec319[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec318[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec318[unsafe_offset = (i) - (S32(1))]))))
                yec40[unsafe_offset = i] = (slow36) * ((rec318[unsafe_offset = (i) - (S32(2))]) + ((rec318[unsafe_offset = i]) + ((2.0) * (rec318[unsafe_offset = (i) - (S32(1))]))))
                rec317[unsafe_offset = i] = -((slow39) * (((slow22) * (rec317[unsafe_offset = (i) - (S32(1))])) - ((slow19) * ((yec40[unsafe_offset = i]) - (yec40[unsafe_offset = (i) - (S32(1))])))))
                rec316[unsafe_offset = i] = (rec317[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec316[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec316[unsafe_offset = (i) - (S32(1))]))))
                zec83[i] = (slow33) * (rec315[unsafe_offset = (i) - (S32(1))])
                rec315[unsafe_offset = i] = ((slow43) * ((rec316[unsafe_offset = (i) - (S32(2))]) + ((rec316[unsafe_offset = i]) - ((2.0) * (rec316[unsafe_offset = (i) - (S32(1))]))))) - ((slow29) * (((slow31) * (rec315[unsafe_offset = (i) - (S32(2))])) + (zec83[i])))
                rec323[unsafe_offset = i] = -((slow39) * (((slow22) * (rec323[unsafe_offset = (i) - (S32(1))])) - ((yec40[unsafe_offset = i]) + (yec40[unsafe_offset = (i) - (S32(1))]))))
                rec322[unsafe_offset = i] = (rec323[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec322[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec322[unsafe_offset = (i) - (S32(1))]))))
                yec41[unsafe_offset = i] = (slow41) * ((rec322[unsafe_offset = (i) - (S32(2))]) + ((rec322[unsafe_offset = i]) + ((2.0) * (rec322[unsafe_offset = (i) - (S32(1))]))))
                rec321[unsafe_offset = i] = -((slow44) * (((slow30) * (rec321[unsafe_offset = (i) - (S32(1))])) - ((slow27) * ((yec41[unsafe_offset = i]) - (yec41[unsafe_offset = (i) - (S32(1))])))))
                rec320[unsafe_offset = i] = (rec321[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec320[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec320[unsafe_offset = (i) - (S32(1))]))))
                rec325[unsafe_offset = i] = -((slow44) * (((slow30) * (rec325[unsafe_offset = (i) - (S32(1))])) - ((yec41[unsafe_offset = i]) + (yec41[unsafe_offset = (i) - (S32(1))]))))
                rec324[unsafe_offset = i] = (rec325[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec324[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec324[unsafe_offset = (i) - (S32(1))]))))
                rec330[unsafe_offset = i] = -((slow2) * (((slow3) * (rec330[unsafe_offset = (i) - (S32(1))])) - ((slow1) * ((rec7[unsafe_offset = (i) - (S32(1))]) - (rec7[unsafe_offset = (i) - (S32(2))])))))
                rec329[unsafe_offset = i] = (rec330[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec329[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec329[unsafe_offset = (i) - (S32(1))]))))
                zec84[i] = (slow17) * (rec328[unsafe_offset = (i) - (S32(1))])
                rec328[unsafe_offset = i] = ((slow9) * ((rec329[unsafe_offset = (i) - (S32(2))]) + ((rec329[unsafe_offset = i]) - ((2.0) * (rec329[unsafe_offset = (i) - (S32(1))]))))) - ((slow13) * (((slow15) * (rec328[unsafe_offset = (i) - (S32(2))])) + (zec84[i])))
                zec85[i] = (slow25) * (rec327[unsafe_offset = (i) - (S32(1))])
                rec327[unsafe_offset = i] = ((rec328[unsafe_offset = (i) - (S32(2))]) + ((slow13) * ((zec84[i]) + ((slow15) * (rec328[unsafe_offset = i]))))) - ((slow21) * (((slow23) * (rec327[unsafe_offset = (i) - (S32(2))])) + (zec85[i])))
                zec86[i] = (slow33) * (rec326[unsafe_offset = (i) - (S32(1))])
                rec326[unsafe_offset = i] = ((rec327[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec85[i]) + ((slow23) * (rec327[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec326[unsafe_offset = (i) - (S32(2))])) + (zec86[i])))
                rec336[unsafe_offset = i] = -((slow2) * (((slow3) * (rec336[unsafe_offset = (i) - (S32(1))])) - ((rec7[unsafe_offset = (i) - (S32(1))]) + (rec7[unsafe_offset = (i) - (S32(2))]))))
                rec335[unsafe_offset = i] = (rec336[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec335[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec335[unsafe_offset = (i) - (S32(1))]))))
                yec42[unsafe_offset = i] = (slow5) * ((rec335[unsafe_offset = (i) - (S32(2))]) + ((rec335[unsafe_offset = i]) + ((2.0) * (rec335[unsafe_offset = (i) - (S32(1))]))))
                rec334[unsafe_offset = i] = -((slow34) * (((slow14) * (rec334[unsafe_offset = (i) - (S32(1))])) - ((slow11) * ((yec42[unsafe_offset = i]) - (yec42[unsafe_offset = (i) - (S32(1))])))))
                rec333[unsafe_offset = i] = (rec334[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec333[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec333[unsafe_offset = (i) - (S32(1))]))))
                zec87[i] = (slow25) * (rec332[unsafe_offset = (i) - (S32(1))])
                rec332[unsafe_offset = i] = ((slow38) * ((rec333[unsafe_offset = (i) - (S32(2))]) + ((rec333[unsafe_offset = i]) - ((2.0) * (rec333[unsafe_offset = (i) - (S32(1))]))))) - ((slow21) * (((slow23) * (rec332[unsafe_offset = (i) - (S32(2))])) + (zec87[i])))
                zec88[i] = (slow33) * (rec331[unsafe_offset = (i) - (S32(1))])
                rec331[unsafe_offset = i] = ((rec332[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec87[i]) + ((slow23) * (rec332[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec331[unsafe_offset = (i) - (S32(2))])) + (zec88[i])))
                rec341[unsafe_offset = i] = -((slow34) * (((slow14) * (rec341[unsafe_offset = (i) - (S32(1))])) - ((yec42[unsafe_offset = i]) + (yec42[unsafe_offset = (i) - (S32(1))]))))
                rec340[unsafe_offset = i] = (rec341[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec340[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec340[unsafe_offset = (i) - (S32(1))]))))
                yec43[unsafe_offset = i] = (slow36) * ((rec340[unsafe_offset = (i) - (S32(2))]) + ((rec340[unsafe_offset = i]) + ((2.0) * (rec340[unsafe_offset = (i) - (S32(1))]))))
                rec339[unsafe_offset = i] = -((slow39) * (((slow22) * (rec339[unsafe_offset = (i) - (S32(1))])) - ((slow19) * ((yec43[unsafe_offset = i]) - (yec43[unsafe_offset = (i) - (S32(1))])))))
                rec338[unsafe_offset = i] = (rec339[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec338[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec338[unsafe_offset = (i) - (S32(1))]))))
                zec89[i] = (slow33) * (rec337[unsafe_offset = (i) - (S32(1))])
                rec337[unsafe_offset = i] = ((slow43) * ((rec338[unsafe_offset = (i) - (S32(2))]) + ((rec338[unsafe_offset = i]) - ((2.0) * (rec338[unsafe_offset = (i) - (S32(1))]))))) - ((slow29) * (((slow31) * (rec337[unsafe_offset = (i) - (S32(2))])) + (zec89[i])))
                rec345[unsafe_offset = i] = -((slow39) * (((slow22) * (rec345[unsafe_offset = (i) - (S32(1))])) - ((yec43[unsafe_offset = i]) + (yec43[unsafe_offset = (i) - (S32(1))]))))
                rec344[unsafe_offset = i] = (rec345[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec344[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec344[unsafe_offset = (i) - (S32(1))]))))
                yec44[unsafe_offset = i] = (slow41) * ((rec344[unsafe_offset = (i) - (S32(2))]) + ((rec344[unsafe_offset = i]) + ((2.0) * (rec344[unsafe_offset = (i) - (S32(1))]))))
                rec343[unsafe_offset = i] = -((slow44) * (((slow30) * (rec343[unsafe_offset = (i) - (S32(1))])) - ((slow27) * ((yec44[unsafe_offset = i]) - (yec44[unsafe_offset = (i) - (S32(1))])))))
                rec342[unsafe_offset = i] = (rec343[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec342[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec342[unsafe_offset = (i) - (S32(1))]))))
                rec347[unsafe_offset = i] = -((slow44) * (((slow30) * (rec347[unsafe_offset = (i) - (S32(1))])) - ((yec44[unsafe_offset = i]) + (yec44[unsafe_offset = (i) - (S32(1))]))))
                rec346[unsafe_offset = i] = (rec347[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec346[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec346[unsafe_offset = (i) - (S32(1))]))))
                rec352[unsafe_offset = i] = -((slow2) * (((slow3) * (rec352[unsafe_offset = (i) - (S32(1))])) - ((slow1) * ((rec15[unsafe_offset = (i) - (S32(1))]) - (rec15[unsafe_offset = (i) - (S32(2))])))))
                rec351[unsafe_offset = i] = (rec352[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec351[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec351[unsafe_offset = (i) - (S32(1))]))))
                zec90[i] = (slow17) * (rec350[unsafe_offset = (i) - (S32(1))])
                rec350[unsafe_offset = i] = ((slow9) * ((rec351[unsafe_offset = (i) - (S32(2))]) + ((rec351[unsafe_offset = i]) - ((2.0) * (rec351[unsafe_offset = (i) - (S32(1))]))))) - ((slow13) * (((slow15) * (rec350[unsafe_offset = (i) - (S32(2))])) + (zec90[i])))
                zec91[i] = (slow25) * (rec349[unsafe_offset = (i) - (S32(1))])
                rec349[unsafe_offset = i] = ((rec350[unsafe_offset = (i) - (S32(2))]) + ((slow13) * ((zec90[i]) + ((slow15) * (rec350[unsafe_offset = i]))))) - ((slow21) * (((slow23) * (rec349[unsafe_offset = (i) - (S32(2))])) + (zec91[i])))
                zec92[i] = (slow33) * (rec348[unsafe_offset = (i) - (S32(1))])
                rec348[unsafe_offset = i] = ((rec349[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec91[i]) + ((slow23) * (rec349[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec348[unsafe_offset = (i) - (S32(2))])) + (zec92[i])))
                rec358[unsafe_offset = i] = -((slow2) * (((slow3) * (rec358[unsafe_offset = (i) - (S32(1))])) - ((rec15[unsafe_offset = (i) - (S32(1))]) + (rec15[unsafe_offset = (i) - (S32(2))]))))
                rec357[unsafe_offset = i] = (rec358[unsafe_offset = i]) - ((slow5) * (((slow6) * (rec357[unsafe_offset = (i) - (S32(2))])) + ((slow8) * (rec357[unsafe_offset = (i) - (S32(1))]))))
                yec45[unsafe_offset = i] = (slow5) * ((rec357[unsafe_offset = (i) - (S32(2))]) + ((rec357[unsafe_offset = i]) + ((2.0) * (rec357[unsafe_offset = (i) - (S32(1))]))))
                rec356[unsafe_offset = i] = -((slow34) * (((slow14) * (rec356[unsafe_offset = (i) - (S32(1))])) - ((slow11) * ((yec45[unsafe_offset = i]) - (yec45[unsafe_offset = (i) - (S32(1))])))))
                rec355[unsafe_offset = i] = (rec356[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec355[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec355[unsafe_offset = (i) - (S32(1))]))))
                zec93[i] = (slow25) * (rec354[unsafe_offset = (i) - (S32(1))])
                rec354[unsafe_offset = i] = ((slow38) * ((rec355[unsafe_offset = (i) - (S32(2))]) + ((rec355[unsafe_offset = i]) - ((2.0) * (rec355[unsafe_offset = (i) - (S32(1))]))))) - ((slow21) * (((slow23) * (rec354[unsafe_offset = (i) - (S32(2))])) + (zec93[i])))
                zec94[i] = (slow33) * (rec353[unsafe_offset = (i) - (S32(1))])
                rec353[unsafe_offset = i] = ((rec354[unsafe_offset = (i) - (S32(2))]) + ((slow21) * ((zec93[i]) + ((slow23) * (rec354[unsafe_offset = i]))))) - ((slow29) * (((slow31) * (rec353[unsafe_offset = (i) - (S32(2))])) + (zec94[i])))
                rec363[unsafe_offset = i] = -((slow34) * (((slow14) * (rec363[unsafe_offset = (i) - (S32(1))])) - ((yec45[unsafe_offset = i]) + (yec45[unsafe_offset = (i) - (S32(1))]))))
                rec362[unsafe_offset = i] = (rec363[unsafe_offset = i]) - ((slow36) * (((slow37) * (rec362[unsafe_offset = (i) - (S32(2))])) + ((slow17) * (rec362[unsafe_offset = (i) - (S32(1))]))))
                yec46[unsafe_offset = i] = (slow36) * ((rec362[unsafe_offset = (i) - (S32(2))]) + ((rec362[unsafe_offset = i]) + ((2.0) * (rec362[unsafe_offset = (i) - (S32(1))]))))
                rec361[unsafe_offset = i] = -((slow39) * (((slow22) * (rec361[unsafe_offset = (i) - (S32(1))])) - ((slow19) * ((yec46[unsafe_offset = i]) - (yec46[unsafe_offset = (i) - (S32(1))])))))
                rec360[unsafe_offset = i] = (rec361[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec360[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec360[unsafe_offset = (i) - (S32(1))]))))
                zec95[i] = (slow33) * (rec359[unsafe_offset = (i) - (S32(1))])
                rec359[unsafe_offset = i] = ((slow43) * ((rec360[unsafe_offset = (i) - (S32(2))]) + ((rec360[unsafe_offset = i]) - ((2.0) * (rec360[unsafe_offset = (i) - (S32(1))]))))) - ((slow29) * (((slow31) * (rec359[unsafe_offset = (i) - (S32(2))])) + (zec95[i])))
                rec367[unsafe_offset = i] = -((slow39) * (((slow22) * (rec367[unsafe_offset = (i) - (S32(1))])) - ((yec46[unsafe_offset = i]) + (yec46[unsafe_offset = (i) - (S32(1))]))))
                rec366[unsafe_offset = i] = (rec367[unsafe_offset = i]) - ((slow41) * (((slow42) * (rec366[unsafe_offset = (i) - (S32(2))])) + ((slow25) * (rec366[unsafe_offset = (i) - (S32(1))]))))
                yec47[unsafe_offset = i] = (slow41) * ((rec366[unsafe_offset = (i) - (S32(2))]) + ((rec366[unsafe_offset = i]) + ((2.0) * (rec366[unsafe_offset = (i) - (S32(1))]))))
                rec365[unsafe_offset = i] = -((slow44) * (((slow30) * (rec365[unsafe_offset = (i) - (S32(1))])) - ((slow27) * ((yec47[unsafe_offset = i]) - (yec47[unsafe_offset = (i) - (S32(1))])))))
                rec364[unsafe_offset = i] = (rec365[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec364[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec364[unsafe_offset = (i) - (S32(1))]))))
                rec369[unsafe_offset = i] = -((slow44) * (((slow30) * (rec369[unsafe_offset = (i) - (S32(1))])) - ((yec47[unsafe_offset = i]) + (yec47[unsafe_offset = (i) - (S32(1))]))))
                rec368[unsafe_offset = i] = (rec369[unsafe_offset = i]) - ((slow45) * (((slow46) * (rec368[unsafe_offset = (i) - (S32(2))])) + ((slow33) * (rec368[unsafe_offset = (i) - (S32(1))]))))
                zec99[i] = ((((slow54) * ((rec18[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec2[i]) + ((slow31) * (rec18[unsafe_offset = i])))))) + ((slow56) * ((rec23[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec4[i]) + ((slow31) * (rec23[unsafe_offset = i]))))))) + ((slow58) * ((rec29[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec5[i]) + ((slow31) * (rec29[unsafe_offset = i]))))))) + ((slow45) * (((slow60) * ((rec34[unsafe_offset = (i) - (S32(2))]) + ((rec34[unsafe_offset = i]) - ((2.0) * (rec34[unsafe_offset = (i) - (S32(1))]))))) + ((slow62) * ((rec38[unsafe_offset = (i) - (S32(2))]) + ((rec38[unsafe_offset = i]) + ((2.0) * (rec38[unsafe_offset = (i) - (S32(1))])))))))
                zec100[i] = ((((slow66) * ((rec40[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec8[i]) + ((slow31) * (rec40[unsafe_offset = i])))))) + ((slow67) * ((rec45[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec10[i]) + ((slow31) * (rec45[unsafe_offset = i]))))))) + ((slow68) * ((rec51[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec11[i]) + ((slow31) * (rec51[unsafe_offset = i]))))))) + ((slow45) * (((slow69) * ((rec56[unsafe_offset = (i) - (S32(2))]) + ((rec56[unsafe_offset = i]) - ((2.0) * (rec56[unsafe_offset = (i) - (S32(1))]))))) + ((slow70) * ((rec60[unsafe_offset = (i) - (S32(2))]) + ((rec60[unsafe_offset = i]) + ((2.0) * (rec60[unsafe_offset = (i) - (S32(1))])))))))
                zec101[i] = (zec99[i]) + (zec100[i])
                zec102[i] = ((((slow72) * ((rec62[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec14[i]) + ((slow31) * (rec62[unsafe_offset = i])))))) + ((slow73) * ((rec67[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec16[i]) + ((slow31) * (rec67[unsafe_offset = i]))))))) + ((slow74) * ((rec73[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec17[i]) + ((slow31) * (rec73[unsafe_offset = i]))))))) + ((slow45) * (((slow75) * ((rec78[unsafe_offset = (i) - (S32(2))]) + ((rec78[unsafe_offset = i]) - ((2.0) * (rec78[unsafe_offset = (i) - (S32(1))]))))) + ((slow76) * ((rec82[unsafe_offset = (i) - (S32(2))]) + ((rec82[unsafe_offset = i]) + ((2.0) * (rec82[unsafe_offset = (i) - (S32(1))])))))))
                zec103[i] = ((((slow78) * ((rec84[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec20[i]) + ((slow31) * (rec84[unsafe_offset = i])))))) + ((slow79) * ((rec89[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec22[i]) + ((slow31) * (rec89[unsafe_offset = i]))))))) + ((slow80) * ((rec95[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec23[i]) + ((slow31) * (rec95[unsafe_offset = i]))))))) + ((slow45) * (((slow81) * ((rec100[unsafe_offset = (i) - (S32(2))]) + ((rec100[unsafe_offset = i]) - ((2.0) * (rec100[unsafe_offset = (i) - (S32(1))]))))) + ((slow82) * ((rec104[unsafe_offset = (i) - (S32(2))]) + ((rec104[unsafe_offset = i]) + ((2.0) * (rec104[unsafe_offset = (i) - (S32(1))])))))))
                zec104[i] = (zec102[i]) + (zec103[i])
                zec105[i] = (zec101[i]) + (zec104[i])
                zec106[i] = ((((slow84) * ((rec106[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec26[i]) + ((slow31) * (rec106[unsafe_offset = i])))))) + ((slow85) * ((rec111[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec28[i]) + ((slow31) * (rec111[unsafe_offset = i]))))))) + ((slow86) * ((rec117[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec29[i]) + ((slow31) * (rec117[unsafe_offset = i]))))))) + ((slow45) * (((slow87) * ((rec122[unsafe_offset = (i) - (S32(2))]) + ((rec122[unsafe_offset = i]) - ((2.0) * (rec122[unsafe_offset = (i) - (S32(1))]))))) + ((slow88) * ((rec126[unsafe_offset = (i) - (S32(2))]) + ((rec126[unsafe_offset = i]) + ((2.0) * (rec126[unsafe_offset = (i) - (S32(1))])))))))
                zec107[i] = ((((slow90) * ((rec128[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec32[i]) + ((slow31) * (rec128[unsafe_offset = i])))))) + ((slow91) * ((rec133[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec34[i]) + ((slow31) * (rec133[unsafe_offset = i]))))))) + ((slow92) * ((rec139[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec35[i]) + ((slow31) * (rec139[unsafe_offset = i]))))))) + ((slow45) * (((slow93) * ((rec144[unsafe_offset = (i) - (S32(2))]) + ((rec144[unsafe_offset = i]) - ((2.0) * (rec144[unsafe_offset = (i) - (S32(1))]))))) + ((slow94) * ((rec148[unsafe_offset = (i) - (S32(2))]) + ((rec148[unsafe_offset = i]) + ((2.0) * (rec148[unsafe_offset = (i) - (S32(1))])))))))
                zec108[i] = (zec106[i]) + (zec107[i])
                zec109[i] = ((((slow96) * ((rec150[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec38[i]) + ((slow31) * (rec150[unsafe_offset = i])))))) + ((slow97) * ((rec155[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec40[i]) + ((slow31) * (rec155[unsafe_offset = i]))))))) + ((slow98) * ((rec161[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec41[i]) + ((slow31) * (rec161[unsafe_offset = i]))))))) + ((slow45) * (((slow99) * ((rec166[unsafe_offset = (i) - (S32(2))]) + ((rec166[unsafe_offset = i]) - ((2.0) * (rec166[unsafe_offset = (i) - (S32(1))]))))) + ((slow100) * ((rec170[unsafe_offset = (i) - (S32(2))]) + ((rec170[unsafe_offset = i]) + ((2.0) * (rec170[unsafe_offset = (i) - (S32(1))])))))))
                zec110[i] = ((((slow102) * ((rec172[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec44[i]) + ((slow31) * (rec172[unsafe_offset = i])))))) + ((slow103) * ((rec177[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec46[i]) + ((slow31) * (rec177[unsafe_offset = i]))))))) + ((slow104) * ((rec183[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec47[i]) + ((slow31) * (rec183[unsafe_offset = i]))))))) + ((slow45) * (((slow105) * ((rec188[unsafe_offset = (i) - (S32(2))]) + ((rec188[unsafe_offset = i]) - ((2.0) * (rec188[unsafe_offset = (i) - (S32(1))]))))) + ((slow106) * ((rec192[unsafe_offset = (i) - (S32(2))]) + ((rec192[unsafe_offset = i]) + ((2.0) * (rec192[unsafe_offset = (i) - (S32(1))])))))))
                zec111[i] = (zec109[i]) + (zec110[i])
                zec112[i] = (zec108[i]) + (zec111[i])
                zec113[i] = (zec105[i]) + (zec112[i])
                zec114[i] = ((((slow108) * ((rec194[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec50[i]) + ((slow31) * (rec194[unsafe_offset = i])))))) + ((slow109) * ((rec199[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec52[i]) + ((slow31) * (rec199[unsafe_offset = i]))))))) + ((slow110) * ((rec205[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec53[i]) + ((slow31) * (rec205[unsafe_offset = i]))))))) + ((slow45) * (((slow111) * ((rec210[unsafe_offset = (i) - (S32(2))]) + ((rec210[unsafe_offset = i]) - ((2.0) * (rec210[unsafe_offset = (i) - (S32(1))]))))) + ((slow112) * ((rec214[unsafe_offset = (i) - (S32(2))]) + ((rec214[unsafe_offset = i]) + ((2.0) * (rec214[unsafe_offset = (i) - (S32(1))])))))))
                zec115[i] = ((((slow114) * ((rec216[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec56[i]) + ((slow31) * (rec216[unsafe_offset = i])))))) + ((slow115) * ((rec221[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec58[i]) + ((slow31) * (rec221[unsafe_offset = i]))))))) + ((slow116) * ((rec227[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec59[i]) + ((slow31) * (rec227[unsafe_offset = i]))))))) + ((slow45) * (((slow117) * ((rec232[unsafe_offset = (i) - (S32(2))]) + ((rec232[unsafe_offset = i]) - ((2.0) * (rec232[unsafe_offset = (i) - (S32(1))]))))) + ((slow118) * ((rec236[unsafe_offset = (i) - (S32(2))]) + ((rec236[unsafe_offset = i]) + ((2.0) * (rec236[unsafe_offset = (i) - (S32(1))])))))))
                zec116[i] = (zec114[i]) + (zec115[i])
                zec117[i] = ((((slow120) * ((rec238[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec62[i]) + ((slow31) * (rec238[unsafe_offset = i])))))) + ((slow121) * ((rec243[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec64[i]) + ((slow31) * (rec243[unsafe_offset = i]))))))) + ((slow122) * ((rec249[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec65[i]) + ((slow31) * (rec249[unsafe_offset = i]))))))) + ((slow45) * (((slow123) * ((rec254[unsafe_offset = (i) - (S32(2))]) + ((rec254[unsafe_offset = i]) - ((2.0) * (rec254[unsafe_offset = (i) - (S32(1))]))))) + ((slow124) * ((rec258[unsafe_offset = (i) - (S32(2))]) + ((rec258[unsafe_offset = i]) + ((2.0) * (rec258[unsafe_offset = (i) - (S32(1))])))))))
                zec118[i] = ((((slow126) * ((rec260[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec68[i]) + ((slow31) * (rec260[unsafe_offset = i])))))) + ((slow127) * ((rec265[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec70[i]) + ((slow31) * (rec265[unsafe_offset = i]))))))) + ((slow128) * ((rec271[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec71[i]) + ((slow31) * (rec271[unsafe_offset = i]))))))) + ((slow45) * (((slow129) * ((rec276[unsafe_offset = (i) - (S32(2))]) + ((rec276[unsafe_offset = i]) - ((2.0) * (rec276[unsafe_offset = (i) - (S32(1))]))))) + ((slow130) * ((rec280[unsafe_offset = (i) - (S32(2))]) + ((rec280[unsafe_offset = i]) + ((2.0) * (rec280[unsafe_offset = (i) - (S32(1))])))))))
                zec119[i] = (zec117[i]) + (zec118[i])
                zec120[i] = (zec116[i]) + (zec119[i])
                zec121[i] = ((((slow132) * ((rec282[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec74[i]) + ((slow31) * (rec282[unsafe_offset = i])))))) + ((slow133) * ((rec287[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec76[i]) + ((slow31) * (rec287[unsafe_offset = i]))))))) + ((slow134) * ((rec293[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec77[i]) + ((slow31) * (rec293[unsafe_offset = i]))))))) + ((slow45) * (((slow135) * ((rec298[unsafe_offset = (i) - (S32(2))]) + ((rec298[unsafe_offset = i]) - ((2.0) * (rec298[unsafe_offset = (i) - (S32(1))]))))) + ((slow136) * ((rec302[unsafe_offset = (i) - (S32(2))]) + ((rec302[unsafe_offset = i]) + ((2.0) * (rec302[unsafe_offset = (i) - (S32(1))])))))))
                zec122[i] = ((((slow138) * ((rec304[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec80[i]) + ((slow31) * (rec304[unsafe_offset = i])))))) + ((slow139) * ((rec309[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec82[i]) + ((slow31) * (rec309[unsafe_offset = i]))))))) + ((slow140) * ((rec315[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec83[i]) + ((slow31) * (rec315[unsafe_offset = i]))))))) + ((slow45) * (((slow141) * ((rec320[unsafe_offset = (i) - (S32(2))]) + ((rec320[unsafe_offset = i]) - ((2.0) * (rec320[unsafe_offset = (i) - (S32(1))]))))) + ((slow142) * ((rec324[unsafe_offset = (i) - (S32(2))]) + ((rec324[unsafe_offset = i]) + ((2.0) * (rec324[unsafe_offset = (i) - (S32(1))])))))))
                zec123[i] = (zec121[i]) + (zec122[i])
                zec124[i] = ((((slow144) * ((rec326[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec86[i]) + ((slow31) * (rec326[unsafe_offset = i])))))) + ((slow145) * ((rec331[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec88[i]) + ((slow31) * (rec331[unsafe_offset = i]))))))) + ((slow146) * ((rec337[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec89[i]) + ((slow31) * (rec337[unsafe_offset = i]))))))) + ((slow45) * (((slow147) * ((rec342[unsafe_offset = (i) - (S32(2))]) + ((rec342[unsafe_offset = i]) - ((2.0) * (rec342[unsafe_offset = (i) - (S32(1))]))))) + ((slow148) * ((rec346[unsafe_offset = (i) - (S32(2))]) + ((rec346[unsafe_offset = i]) + ((2.0) * (rec346[unsafe_offset = (i) - (S32(1))])))))))
                zec125[i] = ((((slow150) * ((rec348[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec92[i]) + ((slow31) * (rec348[unsafe_offset = i])))))) + ((slow151) * ((rec353[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec94[i]) + ((slow31) * (rec353[unsafe_offset = i]))))))) + ((slow152) * ((rec359[unsafe_offset = (i) - (S32(2))]) + ((slow29) * ((zec95[i]) + ((slow31) * (rec359[unsafe_offset = i]))))))) + ((slow45) * (((slow153) * ((rec364[unsafe_offset = (i) - (S32(2))]) + ((rec364[unsafe_offset = i]) - ((2.0) * (rec364[unsafe_offset = (i) - (S32(1))]))))) + ((slow154) * ((rec368[unsafe_offset = (i) - (S32(2))]) + ((rec368[unsafe_offset = i]) + ((2.0) * (rec368[unsafe_offset = (i) - (S32(1))])))))))
                zec126[i] = (zec124[i]) + (zec125[i])
                zec127[i] = (zec123[i]) + (zec126[i])
                zec128[i] = (zec120[i]) + (zec127[i])
                dsp.yec48[((i) + (dsp.yec48_idx)) & (S32(16383))] = (zec96[i]) + ((zec98[i]) + (((slow50) * ((zec113[i]) + (zec128[i]))) + (zec129[i])))
                rec0[unsafe_offset = i] = dsp.yec48[(((i) + (dsp.yec48_idx)) - (i_slow156)) & (S32(16383))]
                dsp.yec49[((i) + (dsp.yec49_idx)) & (S32(16383))] = (zec130[i]) + ((zec131[i]) + ((zec96[i]) + ((slow50) * ((zec113[i]) - (zec128[i])))))
                rec1[unsafe_offset = i] = dsp.yec49[(((i) + (dsp.yec49_idx)) - (i_slow158)) & (S32(16383))]
                zec133[i] = (zec105[i]) - (zec112[i])
                zec134[i] = (zec120[i]) - (zec127[i])
                dsp.yec50[((i) + (dsp.yec50_idx)) & (S32(16383))] = (zec132[i]) + ((slow50) * ((zec133[i]) + (zec134[i])))
                rec2[unsafe_offset = i] = dsp.yec50[(((i) + (dsp.yec50_idx)) - (i_slow159)) & (S32(16383))]
                dsp.yec51[((i) + (dsp.yec51_idx)) & (S32(16383))] = (zec135[i]) + ((slow50) * ((zec133[i]) - (zec134[i])))
                rec3[unsafe_offset = i] = dsp.yec51[(((i) + (dsp.yec51_idx)) - (i_slow160)) & (S32(16383))]
                zec136[i] = (zec101[i]) - (zec104[i])
                zec137[i] = (zec108[i]) - (zec111[i])
                zec138[i] = (zec136[i]) + (zec137[i])
                zec139[i] = (zec116[i]) - (zec119[i])
                zec140[i] = (zec123[i]) - (zec126[i])
                zec141[i] = (zec139[i]) + (zec140[i])
                dsp.yec52[((i) + (dsp.yec52_idx)) & (S32(16383))] = (zec132[i]) + ((slow50) * ((zec138[i]) + (zec141[i])))
                rec4[unsafe_offset = i] = dsp.yec52[(((i) + (dsp.yec52_idx)) - (i_slow161)) & (S32(16383))]
                dsp.yec53[((i) + (dsp.yec53_idx)) & (S32(16383))] = (zec135[i]) + ((slow50) * ((zec138[i]) - (zec141[i])))
                rec5[unsafe_offset = i] = dsp.yec53[(((i) + (dsp.yec53_idx)) - (i_slow162)) & (S32(16383))]
                zec142[i] = (zec136[i]) - (zec137[i])
                zec143[i] = (zec139[i]) - (zec140[i])
                dsp.yec54[((i) + (dsp.yec54_idx)) & (S32(16383))] = (zec132[i]) + ((slow50) * ((zec142[i]) + (zec143[i])))
                rec6[unsafe_offset = i] = dsp.yec54[(((i) + (dsp.yec54_idx)) - (i_slow163)) & (S32(16383))]
                dsp.yec55[((i) + (dsp.yec55_idx)) & (S32(16383))] = (zec135[i]) + ((slow50) * ((zec142[i]) - (zec143[i])))
                rec7[unsafe_offset = i] = dsp.yec55[(((i) + (dsp.yec55_idx)) - (i_slow164)) & (S32(16383))]
                zec144[i] = (zec99[i]) - (zec100[i])
                zec145[i] = (zec102[i]) - (zec103[i])
                zec146[i] = (zec144[i]) + (zec145[i])
                zec147[i] = (zec106[i]) - (zec107[i])
                zec148[i] = (zec109[i]) - (zec110[i])
                zec149[i] = (zec147[i]) + (zec148[i])
                zec150[i] = (zec146[i]) + (zec149[i])
                zec151[i] = (zec114[i]) - (zec115[i])
                zec152[i] = (zec117[i]) - (zec118[i])
                zec153[i] = (zec151[i]) + (zec152[i])
                zec154[i] = (zec121[i]) - (zec122[i])
                zec155[i] = (zec124[i]) - (zec125[i])
                zec156[i] = (zec154[i]) + (zec155[i])
                zec157[i] = (zec153[i]) + (zec156[i])
                dsp.yec56[((i) + (dsp.yec56_idx)) & (S32(16383))] = (zec132[i]) + ((slow50) * ((zec150[i]) + (zec157[i])))
                rec8[unsafe_offset = i] = dsp.yec56[(((i) + (dsp.yec56_idx)) - (i_slow165)) & (S32(16383))]
                dsp.yec57[((i) + (dsp.yec57_idx)) & (S32(16383))] = (zec135[i]) + ((slow50) * ((zec150[i]) - (zec157[i])))
                rec9[unsafe_offset = i] = dsp.yec57[(((i) + (dsp.yec57_idx)) - (i_slow166)) & (S32(16383))]
                zec158[i] = (zec146[i]) - (zec149[i])
                zec159[i] = (zec153[i]) - (zec156[i])
                dsp.yec58[((i) + (dsp.yec58_idx)) & (S32(16383))] = (zec132[i]) + ((slow50) * ((zec158[i]) + (zec159[i])))
                rec10[unsafe_offset = i] = dsp.yec58[(((i) + (dsp.yec58_idx)) - (i_slow167)) & (S32(16383))]
                dsp.yec59[((i) + (dsp.yec59_idx)) & (S32(16383))] = (zec135[i]) + ((slow50) * ((zec158[i]) - (zec159[i])))
                rec11[unsafe_offset = i] = dsp.yec59[(((i) + (dsp.yec59_idx)) - (i_slow168)) & (S32(16383))]
                zec160[i] = (zec144[i]) - (zec145[i])
                zec161[i] = (zec147[i]) - (zec148[i])
                zec162[i] = (zec160[i]) + (zec161[i])
                zec163[i] = (zec151[i]) - (zec152[i])
                zec164[i] = (zec154[i]) - (zec155[i])
                zec165[i] = (zec163[i]) + (zec164[i])
                dsp.yec60[((i) + (dsp.yec60_idx)) & (S32(16383))] = (zec132[i]) + ((slow50) * ((zec162[i]) + (zec165[i])))
                rec12[unsafe_offset = i] = dsp.yec60[(((i) + (dsp.yec60_idx)) - (i_slow169)) & (S32(16383))]
                dsp.yec61[((i) + (dsp.yec61_idx)) & (S32(16383))] = (zec135[i]) + ((slow50) * ((zec162[i]) - (zec165[i])))
                rec13[unsafe_offset = i] = dsp.yec61[(((i) + (dsp.yec61_idx)) - (i_slow170)) & (S32(16383))]
                zec166[i] = (zec160[i]) - (zec161[i])
                zec167[i] = (zec163[i]) - (zec164[i])
                dsp.yec62[((i) + (dsp.yec62_idx)) & (S32(16383))] = (zec132[i]) + ((slow50) * ((zec166[i]) + (zec167[i])))
                rec14[unsafe_offset = i] = dsp.yec62[(((i) + (dsp.yec62_idx)) - (i_slow171)) & (S32(16383))]
                dsp.yec63[((i) + (dsp.yec63_idx)) & (S32(16383))] = (zec135[i]) + ((slow50) * ((zec166[i]) - (zec167[i])))
                rec15[unsafe_offset = i] = dsp.yec63[(((i) + (dsp.yec63_idx)) - (i_slow172)) & (S32(16383))]
            dsp.yec63_idx_save = vsize
            dsp.yec62_idx_save = vsize
            dsp.yec61_idx_save = vsize
            dsp.yec60_idx_save = vsize
            dsp.yec59_idx_save = vsize
            dsp.yec58_idx_save = vsize
            dsp.yec57_idx_save = vsize
            dsp.yec56_idx_save = vsize
            dsp.yec55_idx_save = vsize
            dsp.yec54_idx_save = vsize
            dsp.yec53_idx_save = vsize
            dsp.yec52_idx_save = vsize
            dsp.yec51_idx_save = vsize
            dsp.yec50_idx_save = vsize
            dsp.yec49_idx_save = vsize
            dsp.yec48_idx_save = vsize
            vstore(dsp.rec369_perm, vload[H](rec369_tmp, vsize))
            vstore(dsp.rec369_perm, vload[H](rec369_tmp, vsize + hsize), hsize)
            vstore(dsp.rec368_perm, vload[H](rec368_tmp, vsize))
            vstore(dsp.rec368_perm, vload[H](rec368_tmp, vsize + hsize), hsize)
            vstore(dsp.yec47_perm, vload[H](yec47_tmp, vsize))
            vstore(dsp.yec47_perm, vload[H](yec47_tmp, vsize + hsize), hsize)
            vstore(dsp.rec367_perm, vload[H](rec367_tmp, vsize))
            vstore(dsp.rec367_perm, vload[H](rec367_tmp, vsize + hsize), hsize)
            vstore(dsp.rec366_perm, vload[H](rec366_tmp, vsize))
            vstore(dsp.rec366_perm, vload[H](rec366_tmp, vsize + hsize), hsize)
            vstore(dsp.rec365_perm, vload[H](rec365_tmp, vsize))
            vstore(dsp.rec365_perm, vload[H](rec365_tmp, vsize + hsize), hsize)
            vstore(dsp.rec364_perm, vload[H](rec364_tmp, vsize))
            vstore(dsp.rec364_perm, vload[H](rec364_tmp, vsize + hsize), hsize)
            vstore(dsp.yec46_perm, vload[H](yec46_tmp, vsize))
            vstore(dsp.yec46_perm, vload[H](yec46_tmp, vsize + hsize), hsize)
            vstore(dsp.rec363_perm, vload[H](rec363_tmp, vsize))
            vstore(dsp.rec363_perm, vload[H](rec363_tmp, vsize + hsize), hsize)
            vstore(dsp.rec362_perm, vload[H](rec362_tmp, vsize))
            vstore(dsp.rec362_perm, vload[H](rec362_tmp, vsize + hsize), hsize)
            vstore(dsp.rec361_perm, vload[H](rec361_tmp, vsize))
            vstore(dsp.rec361_perm, vload[H](rec361_tmp, vsize + hsize), hsize)
            vstore(dsp.rec360_perm, vload[H](rec360_tmp, vsize))
            vstore(dsp.rec360_perm, vload[H](rec360_tmp, vsize + hsize), hsize)
            vstore(dsp.rec359_perm, vload[H](rec359_tmp, vsize))
            vstore(dsp.rec359_perm, vload[H](rec359_tmp, vsize + hsize), hsize)
            vstore(dsp.yec45_perm, vload[H](yec45_tmp, vsize))
            vstore(dsp.yec45_perm, vload[H](yec45_tmp, vsize + hsize), hsize)
            vstore(dsp.rec358_perm, vload[H](rec358_tmp, vsize))
            vstore(dsp.rec358_perm, vload[H](rec358_tmp, vsize + hsize), hsize)
            vstore(dsp.rec357_perm, vload[H](rec357_tmp, vsize))
            vstore(dsp.rec357_perm, vload[H](rec357_tmp, vsize + hsize), hsize)
            vstore(dsp.rec356_perm, vload[H](rec356_tmp, vsize))
            vstore(dsp.rec356_perm, vload[H](rec356_tmp, vsize + hsize), hsize)
            vstore(dsp.rec355_perm, vload[H](rec355_tmp, vsize))
            vstore(dsp.rec355_perm, vload[H](rec355_tmp, vsize + hsize), hsize)
            vstore(dsp.rec354_perm, vload[H](rec354_tmp, vsize))
            vstore(dsp.rec354_perm, vload[H](rec354_tmp, vsize + hsize), hsize)
            vstore(dsp.rec353_perm, vload[H](rec353_tmp, vsize))
            vstore(dsp.rec353_perm, vload[H](rec353_tmp, vsize + hsize), hsize)
            vstore(dsp.rec352_perm, vload[H](rec352_tmp, vsize))
            vstore(dsp.rec352_perm, vload[H](rec352_tmp, vsize + hsize), hsize)
            vstore(dsp.rec351_perm, vload[H](rec351_tmp, vsize))
            vstore(dsp.rec351_perm, vload[H](rec351_tmp, vsize + hsize), hsize)
            vstore(dsp.rec350_perm, vload[H](rec350_tmp, vsize))
            vstore(dsp.rec350_perm, vload[H](rec350_tmp, vsize + hsize), hsize)
            vstore(dsp.rec349_perm, vload[H](rec349_tmp, vsize))
            vstore(dsp.rec349_perm, vload[H](rec349_tmp, vsize + hsize), hsize)
            vstore(dsp.rec348_perm, vload[H](rec348_tmp, vsize))
            vstore(dsp.rec348_perm, vload[H](rec348_tmp, vsize + hsize), hsize)
            vstore(dsp.rec347_perm, vload[H](rec347_tmp, vsize))
            vstore(dsp.rec347_perm, vload[H](rec347_tmp, vsize + hsize), hsize)
            vstore(dsp.rec346_perm, vload[H](rec346_tmp, vsize))
            vstore(dsp.rec346_perm, vload[H](rec346_tmp, vsize + hsize), hsize)
            vstore(dsp.yec44_perm, vload[H](yec44_tmp, vsize))
            vstore(dsp.yec44_perm, vload[H](yec44_tmp, vsize + hsize), hsize)
            vstore(dsp.rec345_perm, vload[H](rec345_tmp, vsize))
            vstore(dsp.rec345_perm, vload[H](rec345_tmp, vsize + hsize), hsize)
            vstore(dsp.rec344_perm, vload[H](rec344_tmp, vsize))
            vstore(dsp.rec344_perm, vload[H](rec344_tmp, vsize + hsize), hsize)
            vstore(dsp.rec343_perm, vload[H](rec343_tmp, vsize))
            vstore(dsp.rec343_perm, vload[H](rec343_tmp, vsize + hsize), hsize)
            vstore(dsp.rec342_perm, vload[H](rec342_tmp, vsize))
            vstore(dsp.rec342_perm, vload[H](rec342_tmp, vsize + hsize), hsize)
            vstore(dsp.yec43_perm, vload[H](yec43_tmp, vsize))
            vstore(dsp.yec43_perm, vload[H](yec43_tmp, vsize + hsize), hsize)
            vstore(dsp.rec341_perm, vload[H](rec341_tmp, vsize))
            vstore(dsp.rec341_perm, vload[H](rec341_tmp, vsize + hsize), hsize)
            vstore(dsp.rec340_perm, vload[H](rec340_tmp, vsize))
            vstore(dsp.rec340_perm, vload[H](rec340_tmp, vsize + hsize), hsize)
            vstore(dsp.rec339_perm, vload[H](rec339_tmp, vsize))
            vstore(dsp.rec339_perm, vload[H](rec339_tmp, vsize + hsize), hsize)
            vstore(dsp.rec338_perm, vload[H](rec338_tmp, vsize))
            vstore(dsp.rec338_perm, vload[H](rec338_tmp, vsize + hsize), hsize)
            vstore(dsp.rec337_perm, vload[H](rec337_tmp, vsize))
            vstore(dsp.rec337_perm, vload[H](rec337_tmp, vsize + hsize), hsize)
            vstore(dsp.yec42_perm, vload[H](yec42_tmp, vsize))
            vstore(dsp.yec42_perm, vload[H](yec42_tmp, vsize + hsize), hsize)
            vstore(dsp.rec336_perm, vload[H](rec336_tmp, vsize))
            vstore(dsp.rec336_perm, vload[H](rec336_tmp, vsize + hsize), hsize)
            vstore(dsp.rec335_perm, vload[H](rec335_tmp, vsize))
            vstore(dsp.rec335_perm, vload[H](rec335_tmp, vsize + hsize), hsize)
            vstore(dsp.rec334_perm, vload[H](rec334_tmp, vsize))
            vstore(dsp.rec334_perm, vload[H](rec334_tmp, vsize + hsize), hsize)
            vstore(dsp.rec333_perm, vload[H](rec333_tmp, vsize))
            vstore(dsp.rec333_perm, vload[H](rec333_tmp, vsize + hsize), hsize)
            vstore(dsp.rec332_perm, vload[H](rec332_tmp, vsize))
            vstore(dsp.rec332_perm, vload[H](rec332_tmp, vsize + hsize), hsize)
            vstore(dsp.rec331_perm, vload[H](rec331_tmp, vsize))
            vstore(dsp.rec331_perm, vload[H](rec331_tmp, vsize + hsize), hsize)
            vstore(dsp.rec330_perm, vload[H](rec330_tmp, vsize))
            vstore(dsp.rec330_perm, vload[H](rec330_tmp, vsize + hsize), hsize)
            vstore(dsp.rec329_perm, vload[H](rec329_tmp, vsize))
            vstore(dsp.rec329_perm, vload[H](rec329_tmp, vsize + hsize), hsize)
            vstore(dsp.rec328_perm, vload[H](rec328_tmp, vsize))
            vstore(dsp.rec328_perm, vload[H](rec328_tmp, vsize + hsize), hsize)
            vstore(dsp.rec327_perm, vload[H](rec327_tmp, vsize))
            vstore(dsp.rec327_perm, vload[H](rec327_tmp, vsize + hsize), hsize)
            vstore(dsp.rec326_perm, vload[H](rec326_tmp, vsize))
            vstore(dsp.rec326_perm, vload[H](rec326_tmp, vsize + hsize), hsize)
            vstore(dsp.rec325_perm, vload[H](rec325_tmp, vsize))
            vstore(dsp.rec325_perm, vload[H](rec325_tmp, vsize + hsize), hsize)
            vstore(dsp.rec324_perm, vload[H](rec324_tmp, vsize))
            vstore(dsp.rec324_perm, vload[H](rec324_tmp, vsize + hsize), hsize)
            vstore(dsp.yec41_perm, vload[H](yec41_tmp, vsize))
            vstore(dsp.yec41_perm, vload[H](yec41_tmp, vsize + hsize), hsize)
            vstore(dsp.rec323_perm, vload[H](rec323_tmp, vsize))
            vstore(dsp.rec323_perm, vload[H](rec323_tmp, vsize + hsize), hsize)
            vstore(dsp.rec322_perm, vload[H](rec322_tmp, vsize))
            vstore(dsp.rec322_perm, vload[H](rec322_tmp, vsize + hsize), hsize)
            vstore(dsp.rec321_perm, vload[H](rec321_tmp, vsize))
            vstore(dsp.rec321_perm, vload[H](rec321_tmp, vsize + hsize), hsize)
            vstore(dsp.rec320_perm, vload[H](rec320_tmp, vsize))
            vstore(dsp.rec320_perm, vload[H](rec320_tmp, vsize + hsize), hsize)
            vstore(dsp.yec40_perm, vload[H](yec40_tmp, vsize))
            vstore(dsp.yec40_perm, vload[H](yec40_tmp, vsize + hsize), hsize)
            vstore(dsp.rec319_perm, vload[H](rec319_tmp, vsize))
            vstore(dsp.rec319_perm, vload[H](rec319_tmp, vsize + hsize), hsize)
            vstore(dsp.rec318_perm, vload[H](rec318_tmp, vsize))
            vstore(dsp.rec318_perm, vload[H](rec318_tmp, vsize + hsize), hsize)
            vstore(dsp.rec317_perm, vload[H](rec317_tmp, vsize))
            vstore(dsp.rec317_perm, vload[H](rec317_tmp, vsize + hsize), hsize)
            vstore(dsp.rec316_perm, vload[H](rec316_tmp, vsize))
            vstore(dsp.rec316_perm, vload[H](rec316_tmp, vsize + hsize), hsize)
            vstore(dsp.rec315_perm, vload[H](rec315_tmp, vsize))
            vstore(dsp.rec315_perm, vload[H](rec315_tmp, vsize + hsize), hsize)
            vstore(dsp.yec39_perm, vload[H](yec39_tmp, vsize))
            vstore(dsp.yec39_perm, vload[H](yec39_tmp, vsize + hsize), hsize)
            vstore(dsp.rec314_perm, vload[H](rec314_tmp, vsize))
            vstore(dsp.rec314_perm, vload[H](rec314_tmp, vsize + hsize), hsize)
            vstore(dsp.rec313_perm, vload[H](rec313_tmp, vsize))
            vstore(dsp.rec313_perm, vload[H](rec313_tmp, vsize + hsize), hsize)
            vstore(dsp.rec312_perm, vload[H](rec312_tmp, vsize))
            vstore(dsp.rec312_perm, vload[H](rec312_tmp, vsize + hsize), hsize)
            vstore(dsp.rec311_perm, vload[H](rec311_tmp, vsize))
            vstore(dsp.rec311_perm, vload[H](rec311_tmp, vsize + hsize), hsize)
            vstore(dsp.rec310_perm, vload[H](rec310_tmp, vsize))
            vstore(dsp.rec310_perm, vload[H](rec310_tmp, vsize + hsize), hsize)
            vstore(dsp.rec309_perm, vload[H](rec309_tmp, vsize))
            vstore(dsp.rec309_perm, vload[H](rec309_tmp, vsize + hsize), hsize)
            vstore(dsp.rec308_perm, vload[H](rec308_tmp, vsize))
            vstore(dsp.rec308_perm, vload[H](rec308_tmp, vsize + hsize), hsize)
            vstore(dsp.rec307_perm, vload[H](rec307_tmp, vsize))
            vstore(dsp.rec307_perm, vload[H](rec307_tmp, vsize + hsize), hsize)
            vstore(dsp.rec306_perm, vload[H](rec306_tmp, vsize))
            vstore(dsp.rec306_perm, vload[H](rec306_tmp, vsize + hsize), hsize)
            vstore(dsp.rec305_perm, vload[H](rec305_tmp, vsize))
            vstore(dsp.rec305_perm, vload[H](rec305_tmp, vsize + hsize), hsize)
            vstore(dsp.rec304_perm, vload[H](rec304_tmp, vsize))
            vstore(dsp.rec304_perm, vload[H](rec304_tmp, vsize + hsize), hsize)
            vstore(dsp.rec303_perm, vload[H](rec303_tmp, vsize))
            vstore(dsp.rec303_perm, vload[H](rec303_tmp, vsize + hsize), hsize)
            vstore(dsp.rec302_perm, vload[H](rec302_tmp, vsize))
            vstore(dsp.rec302_perm, vload[H](rec302_tmp, vsize + hsize), hsize)
            vstore(dsp.yec38_perm, vload[H](yec38_tmp, vsize))
            vstore(dsp.yec38_perm, vload[H](yec38_tmp, vsize + hsize), hsize)
            vstore(dsp.rec301_perm, vload[H](rec301_tmp, vsize))
            vstore(dsp.rec301_perm, vload[H](rec301_tmp, vsize + hsize), hsize)
            vstore(dsp.rec300_perm, vload[H](rec300_tmp, vsize))
            vstore(dsp.rec300_perm, vload[H](rec300_tmp, vsize + hsize), hsize)
            vstore(dsp.rec299_perm, vload[H](rec299_tmp, vsize))
            vstore(dsp.rec299_perm, vload[H](rec299_tmp, vsize + hsize), hsize)
            vstore(dsp.rec298_perm, vload[H](rec298_tmp, vsize))
            vstore(dsp.rec298_perm, vload[H](rec298_tmp, vsize + hsize), hsize)
            vstore(dsp.yec37_perm, vload[H](yec37_tmp, vsize))
            vstore(dsp.yec37_perm, vload[H](yec37_tmp, vsize + hsize), hsize)
            vstore(dsp.rec297_perm, vload[H](rec297_tmp, vsize))
            vstore(dsp.rec297_perm, vload[H](rec297_tmp, vsize + hsize), hsize)
            vstore(dsp.rec296_perm, vload[H](rec296_tmp, vsize))
            vstore(dsp.rec296_perm, vload[H](rec296_tmp, vsize + hsize), hsize)
            vstore(dsp.rec295_perm, vload[H](rec295_tmp, vsize))
            vstore(dsp.rec295_perm, vload[H](rec295_tmp, vsize + hsize), hsize)
            vstore(dsp.rec294_perm, vload[H](rec294_tmp, vsize))
            vstore(dsp.rec294_perm, vload[H](rec294_tmp, vsize + hsize), hsize)
            vstore(dsp.rec293_perm, vload[H](rec293_tmp, vsize))
            vstore(dsp.rec293_perm, vload[H](rec293_tmp, vsize + hsize), hsize)
            vstore(dsp.yec36_perm, vload[H](yec36_tmp, vsize))
            vstore(dsp.yec36_perm, vload[H](yec36_tmp, vsize + hsize), hsize)
            vstore(dsp.rec292_perm, vload[H](rec292_tmp, vsize))
            vstore(dsp.rec292_perm, vload[H](rec292_tmp, vsize + hsize), hsize)
            vstore(dsp.rec291_perm, vload[H](rec291_tmp, vsize))
            vstore(dsp.rec291_perm, vload[H](rec291_tmp, vsize + hsize), hsize)
            vstore(dsp.rec290_perm, vload[H](rec290_tmp, vsize))
            vstore(dsp.rec290_perm, vload[H](rec290_tmp, vsize + hsize), hsize)
            vstore(dsp.rec289_perm, vload[H](rec289_tmp, vsize))
            vstore(dsp.rec289_perm, vload[H](rec289_tmp, vsize + hsize), hsize)
            vstore(dsp.rec288_perm, vload[H](rec288_tmp, vsize))
            vstore(dsp.rec288_perm, vload[H](rec288_tmp, vsize + hsize), hsize)
            vstore(dsp.rec287_perm, vload[H](rec287_tmp, vsize))
            vstore(dsp.rec287_perm, vload[H](rec287_tmp, vsize + hsize), hsize)
            vstore(dsp.rec286_perm, vload[H](rec286_tmp, vsize))
            vstore(dsp.rec286_perm, vload[H](rec286_tmp, vsize + hsize), hsize)
            vstore(dsp.rec285_perm, vload[H](rec285_tmp, vsize))
            vstore(dsp.rec285_perm, vload[H](rec285_tmp, vsize + hsize), hsize)
            vstore(dsp.rec284_perm, vload[H](rec284_tmp, vsize))
            vstore(dsp.rec284_perm, vload[H](rec284_tmp, vsize + hsize), hsize)
            vstore(dsp.rec283_perm, vload[H](rec283_tmp, vsize))
            vstore(dsp.rec283_perm, vload[H](rec283_tmp, vsize + hsize), hsize)
            vstore(dsp.rec282_perm, vload[H](rec282_tmp, vsize))
            vstore(dsp.rec282_perm, vload[H](rec282_tmp, vsize + hsize), hsize)
            vstore(dsp.rec281_perm, vload[H](rec281_tmp, vsize))
            vstore(dsp.rec281_perm, vload[H](rec281_tmp, vsize + hsize), hsize)
            vstore(dsp.rec280_perm, vload[H](rec280_tmp, vsize))
            vstore(dsp.rec280_perm, vload[H](rec280_tmp, vsize + hsize), hsize)
            vstore(dsp.yec35_perm, vload[H](yec35_tmp, vsize))
            vstore(dsp.yec35_perm, vload[H](yec35_tmp, vsize + hsize), hsize)
            vstore(dsp.rec279_perm, vload[H](rec279_tmp, vsize))
            vstore(dsp.rec279_perm, vload[H](rec279_tmp, vsize + hsize), hsize)
            vstore(dsp.rec278_perm, vload[H](rec278_tmp, vsize))
            vstore(dsp.rec278_perm, vload[H](rec278_tmp, vsize + hsize), hsize)
            vstore(dsp.rec277_perm, vload[H](rec277_tmp, vsize))
            vstore(dsp.rec277_perm, vload[H](rec277_tmp, vsize + hsize), hsize)
            vstore(dsp.rec276_perm, vload[H](rec276_tmp, vsize))
            vstore(dsp.rec276_perm, vload[H](rec276_tmp, vsize + hsize), hsize)
            vstore(dsp.yec34_perm, vload[H](yec34_tmp, vsize))
            vstore(dsp.yec34_perm, vload[H](yec34_tmp, vsize + hsize), hsize)
            vstore(dsp.rec275_perm, vload[H](rec275_tmp, vsize))
            vstore(dsp.rec275_perm, vload[H](rec275_tmp, vsize + hsize), hsize)
            vstore(dsp.rec274_perm, vload[H](rec274_tmp, vsize))
            vstore(dsp.rec274_perm, vload[H](rec274_tmp, vsize + hsize), hsize)
            vstore(dsp.rec273_perm, vload[H](rec273_tmp, vsize))
            vstore(dsp.rec273_perm, vload[H](rec273_tmp, vsize + hsize), hsize)
            vstore(dsp.rec272_perm, vload[H](rec272_tmp, vsize))
            vstore(dsp.rec272_perm, vload[H](rec272_tmp, vsize + hsize), hsize)
            vstore(dsp.rec271_perm, vload[H](rec271_tmp, vsize))
            vstore(dsp.rec271_perm, vload[H](rec271_tmp, vsize + hsize), hsize)
            vstore(dsp.yec33_perm, vload[H](yec33_tmp, vsize))
            vstore(dsp.yec33_perm, vload[H](yec33_tmp, vsize + hsize), hsize)
            vstore(dsp.rec270_perm, vload[H](rec270_tmp, vsize))
            vstore(dsp.rec270_perm, vload[H](rec270_tmp, vsize + hsize), hsize)
            vstore(dsp.rec269_perm, vload[H](rec269_tmp, vsize))
            vstore(dsp.rec269_perm, vload[H](rec269_tmp, vsize + hsize), hsize)
            vstore(dsp.rec268_perm, vload[H](rec268_tmp, vsize))
            vstore(dsp.rec268_perm, vload[H](rec268_tmp, vsize + hsize), hsize)
            vstore(dsp.rec267_perm, vload[H](rec267_tmp, vsize))
            vstore(dsp.rec267_perm, vload[H](rec267_tmp, vsize + hsize), hsize)
            vstore(dsp.rec266_perm, vload[H](rec266_tmp, vsize))
            vstore(dsp.rec266_perm, vload[H](rec266_tmp, vsize + hsize), hsize)
            vstore(dsp.rec265_perm, vload[H](rec265_tmp, vsize))
            vstore(dsp.rec265_perm, vload[H](rec265_tmp, vsize + hsize), hsize)
            vstore(dsp.rec264_perm, vload[H](rec264_tmp, vsize))
            vstore(dsp.rec264_perm, vload[H](rec264_tmp, vsize + hsize), hsize)
            vstore(dsp.rec263_perm, vload[H](rec263_tmp, vsize))
            vstore(dsp.rec263_perm, vload[H](rec263_tmp, vsize + hsize), hsize)
            vstore(dsp.rec262_perm, vload[H](rec262_tmp, vsize))
            vstore(dsp.rec262_perm, vload[H](rec262_tmp, vsize + hsize), hsize)
            vstore(dsp.rec261_perm, vload[H](rec261_tmp, vsize))
            vstore(dsp.rec261_perm, vload[H](rec261_tmp, vsize + hsize), hsize)
            vstore(dsp.rec260_perm, vload[H](rec260_tmp, vsize))
            vstore(dsp.rec260_perm, vload[H](rec260_tmp, vsize + hsize), hsize)
            vstore(dsp.rec259_perm, vload[H](rec259_tmp, vsize))
            vstore(dsp.rec259_perm, vload[H](rec259_tmp, vsize + hsize), hsize)
            vstore(dsp.rec258_perm, vload[H](rec258_tmp, vsize))
            vstore(dsp.rec258_perm, vload[H](rec258_tmp, vsize + hsize), hsize)
            vstore(dsp.yec32_perm, vload[H](yec32_tmp, vsize))
            vstore(dsp.yec32_perm, vload[H](yec32_tmp, vsize + hsize), hsize)
            vstore(dsp.rec257_perm, vload[H](rec257_tmp, vsize))
            vstore(dsp.rec257_perm, vload[H](rec257_tmp, vsize + hsize), hsize)
            vstore(dsp.rec256_perm, vload[H](rec256_tmp, vsize))
            vstore(dsp.rec256_perm, vload[H](rec256_tmp, vsize + hsize), hsize)
            vstore(dsp.rec255_perm, vload[H](rec255_tmp, vsize))
            vstore(dsp.rec255_perm, vload[H](rec255_tmp, vsize + hsize), hsize)
            vstore(dsp.rec254_perm, vload[H](rec254_tmp, vsize))
            vstore(dsp.rec254_perm, vload[H](rec254_tmp, vsize + hsize), hsize)
            vstore(dsp.yec31_perm, vload[H](yec31_tmp, vsize))
            vstore(dsp.yec31_perm, vload[H](yec31_tmp, vsize + hsize), hsize)
            vstore(dsp.rec253_perm, vload[H](rec253_tmp, vsize))
            vstore(dsp.rec253_perm, vload[H](rec253_tmp, vsize + hsize), hsize)
            vstore(dsp.rec252_perm, vload[H](rec252_tmp, vsize))
            vstore(dsp.rec252_perm, vload[H](rec252_tmp, vsize + hsize), hsize)
            vstore(dsp.rec251_perm, vload[H](rec251_tmp, vsize))
            vstore(dsp.rec251_perm, vload[H](rec251_tmp, vsize + hsize), hsize)
            vstore(dsp.rec250_perm, vload[H](rec250_tmp, vsize))
            vstore(dsp.rec250_perm, vload[H](rec250_tmp, vsize + hsize), hsize)
            vstore(dsp.rec249_perm, vload[H](rec249_tmp, vsize))
            vstore(dsp.rec249_perm, vload[H](rec249_tmp, vsize + hsize), hsize)
            vstore(dsp.yec30_perm, vload[H](yec30_tmp, vsize))
            vstore(dsp.yec30_perm, vload[H](yec30_tmp, vsize + hsize), hsize)
            vstore(dsp.rec248_perm, vload[H](rec248_tmp, vsize))
            vstore(dsp.rec248_perm, vload[H](rec248_tmp, vsize + hsize), hsize)
            vstore(dsp.rec247_perm, vload[H](rec247_tmp, vsize))
            vstore(dsp.rec247_perm, vload[H](rec247_tmp, vsize + hsize), hsize)
            vstore(dsp.rec246_perm, vload[H](rec246_tmp, vsize))
            vstore(dsp.rec246_perm, vload[H](rec246_tmp, vsize + hsize), hsize)
            vstore(dsp.rec245_perm, vload[H](rec245_tmp, vsize))
            vstore(dsp.rec245_perm, vload[H](rec245_tmp, vsize + hsize), hsize)
            vstore(dsp.rec244_perm, vload[H](rec244_tmp, vsize))
            vstore(dsp.rec244_perm, vload[H](rec244_tmp, vsize + hsize), hsize)
            vstore(dsp.rec243_perm, vload[H](rec243_tmp, vsize))
            vstore(dsp.rec243_perm, vload[H](rec243_tmp, vsize + hsize), hsize)
            vstore(dsp.rec242_perm, vload[H](rec242_tmp, vsize))
            vstore(dsp.rec242_perm, vload[H](rec242_tmp, vsize + hsize), hsize)
            vstore(dsp.rec241_perm, vload[H](rec241_tmp, vsize))
            vstore(dsp.rec241_perm, vload[H](rec241_tmp, vsize + hsize), hsize)
            vstore(dsp.rec240_perm, vload[H](rec240_tmp, vsize))
            vstore(dsp.rec240_perm, vload[H](rec240_tmp, vsize + hsize), hsize)
            vstore(dsp.rec239_perm, vload[H](rec239_tmp, vsize))
            vstore(dsp.rec239_perm, vload[H](rec239_tmp, vsize + hsize), hsize)
            vstore(dsp.rec238_perm, vload[H](rec238_tmp, vsize))
            vstore(dsp.rec238_perm, vload[H](rec238_tmp, vsize + hsize), hsize)
            vstore(dsp.rec237_perm, vload[H](rec237_tmp, vsize))
            vstore(dsp.rec237_perm, vload[H](rec237_tmp, vsize + hsize), hsize)
            vstore(dsp.rec236_perm, vload[H](rec236_tmp, vsize))
            vstore(dsp.rec236_perm, vload[H](rec236_tmp, vsize + hsize), hsize)
            vstore(dsp.yec29_perm, vload[H](yec29_tmp, vsize))
            vstore(dsp.yec29_perm, vload[H](yec29_tmp, vsize + hsize), hsize)
            vstore(dsp.rec235_perm, vload[H](rec235_tmp, vsize))
            vstore(dsp.rec235_perm, vload[H](rec235_tmp, vsize + hsize), hsize)
            vstore(dsp.rec234_perm, vload[H](rec234_tmp, vsize))
            vstore(dsp.rec234_perm, vload[H](rec234_tmp, vsize + hsize), hsize)
            vstore(dsp.rec233_perm, vload[H](rec233_tmp, vsize))
            vstore(dsp.rec233_perm, vload[H](rec233_tmp, vsize + hsize), hsize)
            vstore(dsp.rec232_perm, vload[H](rec232_tmp, vsize))
            vstore(dsp.rec232_perm, vload[H](rec232_tmp, vsize + hsize), hsize)
            vstore(dsp.yec28_perm, vload[H](yec28_tmp, vsize))
            vstore(dsp.yec28_perm, vload[H](yec28_tmp, vsize + hsize), hsize)
            vstore(dsp.rec231_perm, vload[H](rec231_tmp, vsize))
            vstore(dsp.rec231_perm, vload[H](rec231_tmp, vsize + hsize), hsize)
            vstore(dsp.rec230_perm, vload[H](rec230_tmp, vsize))
            vstore(dsp.rec230_perm, vload[H](rec230_tmp, vsize + hsize), hsize)
            vstore(dsp.rec229_perm, vload[H](rec229_tmp, vsize))
            vstore(dsp.rec229_perm, vload[H](rec229_tmp, vsize + hsize), hsize)
            vstore(dsp.rec228_perm, vload[H](rec228_tmp, vsize))
            vstore(dsp.rec228_perm, vload[H](rec228_tmp, vsize + hsize), hsize)
            vstore(dsp.rec227_perm, vload[H](rec227_tmp, vsize))
            vstore(dsp.rec227_perm, vload[H](rec227_tmp, vsize + hsize), hsize)
            vstore(dsp.yec27_perm, vload[H](yec27_tmp, vsize))
            vstore(dsp.yec27_perm, vload[H](yec27_tmp, vsize + hsize), hsize)
            vstore(dsp.rec226_perm, vload[H](rec226_tmp, vsize))
            vstore(dsp.rec226_perm, vload[H](rec226_tmp, vsize + hsize), hsize)
            vstore(dsp.rec225_perm, vload[H](rec225_tmp, vsize))
            vstore(dsp.rec225_perm, vload[H](rec225_tmp, vsize + hsize), hsize)
            vstore(dsp.rec224_perm, vload[H](rec224_tmp, vsize))
            vstore(dsp.rec224_perm, vload[H](rec224_tmp, vsize + hsize), hsize)
            vstore(dsp.rec223_perm, vload[H](rec223_tmp, vsize))
            vstore(dsp.rec223_perm, vload[H](rec223_tmp, vsize + hsize), hsize)
            vstore(dsp.rec222_perm, vload[H](rec222_tmp, vsize))
            vstore(dsp.rec222_perm, vload[H](rec222_tmp, vsize + hsize), hsize)
            vstore(dsp.rec221_perm, vload[H](rec221_tmp, vsize))
            vstore(dsp.rec221_perm, vload[H](rec221_tmp, vsize + hsize), hsize)
            vstore(dsp.rec220_perm, vload[H](rec220_tmp, vsize))
            vstore(dsp.rec220_perm, vload[H](rec220_tmp, vsize + hsize), hsize)
            vstore(dsp.rec219_perm, vload[H](rec219_tmp, vsize))
            vstore(dsp.rec219_perm, vload[H](rec219_tmp, vsize + hsize), hsize)
            vstore(dsp.rec218_perm, vload[H](rec218_tmp, vsize))
            vstore(dsp.rec218_perm, vload[H](rec218_tmp, vsize + hsize), hsize)
            vstore(dsp.rec217_perm, vload[H](rec217_tmp, vsize))
            vstore(dsp.rec217_perm, vload[H](rec217_tmp, vsize + hsize), hsize)
            vstore(dsp.rec216_perm, vload[H](rec216_tmp, vsize))
            vstore(dsp.rec216_perm, vload[H](rec216_tmp, vsize + hsize), hsize)
            vstore(dsp.rec215_perm, vload[H](rec215_tmp, vsize))
            vstore(dsp.rec215_perm, vload[H](rec215_tmp, vsize + hsize), hsize)
            vstore(dsp.rec214_perm, vload[H](rec214_tmp, vsize))
            vstore(dsp.rec214_perm, vload[H](rec214_tmp, vsize + hsize), hsize)
            vstore(dsp.yec26_perm, vload[H](yec26_tmp, vsize))
            vstore(dsp.yec26_perm, vload[H](yec26_tmp, vsize + hsize), hsize)
            vstore(dsp.rec213_perm, vload[H](rec213_tmp, vsize))
            vstore(dsp.rec213_perm, vload[H](rec213_tmp, vsize + hsize), hsize)
            vstore(dsp.rec212_perm, vload[H](rec212_tmp, vsize))
            vstore(dsp.rec212_perm, vload[H](rec212_tmp, vsize + hsize), hsize)
            vstore(dsp.rec211_perm, vload[H](rec211_tmp, vsize))
            vstore(dsp.rec211_perm, vload[H](rec211_tmp, vsize + hsize), hsize)
            vstore(dsp.rec210_perm, vload[H](rec210_tmp, vsize))
            vstore(dsp.rec210_perm, vload[H](rec210_tmp, vsize + hsize), hsize)
            vstore(dsp.yec25_perm, vload[H](yec25_tmp, vsize))
            vstore(dsp.yec25_perm, vload[H](yec25_tmp, vsize + hsize), hsize)
            vstore(dsp.rec209_perm, vload[H](rec209_tmp, vsize))
            vstore(dsp.rec209_perm, vload[H](rec209_tmp, vsize + hsize), hsize)
            vstore(dsp.rec208_perm, vload[H](rec208_tmp, vsize))
            vstore(dsp.rec208_perm, vload[H](rec208_tmp, vsize + hsize), hsize)
            vstore(dsp.rec207_perm, vload[H](rec207_tmp, vsize))
            vstore(dsp.rec207_perm, vload[H](rec207_tmp, vsize + hsize), hsize)
            vstore(dsp.rec206_perm, vload[H](rec206_tmp, vsize))
            vstore(dsp.rec206_perm, vload[H](rec206_tmp, vsize + hsize), hsize)
            vstore(dsp.rec205_perm, vload[H](rec205_tmp, vsize))
            vstore(dsp.rec205_perm, vload[H](rec205_tmp, vsize + hsize), hsize)
            vstore(dsp.yec24_perm, vload[H](yec24_tmp, vsize))
            vstore(dsp.yec24_perm, vload[H](yec24_tmp, vsize + hsize), hsize)
            vstore(dsp.rec204_perm, vload[H](rec204_tmp, vsize))
            vstore(dsp.rec204_perm, vload[H](rec204_tmp, vsize + hsize), hsize)
            vstore(dsp.rec203_perm, vload[H](rec203_tmp, vsize))
            vstore(dsp.rec203_perm, vload[H](rec203_tmp, vsize + hsize), hsize)
            vstore(dsp.rec202_perm, vload[H](rec202_tmp, vsize))
            vstore(dsp.rec202_perm, vload[H](rec202_tmp, vsize + hsize), hsize)
            vstore(dsp.rec201_perm, vload[H](rec201_tmp, vsize))
            vstore(dsp.rec201_perm, vload[H](rec201_tmp, vsize + hsize), hsize)
            vstore(dsp.rec200_perm, vload[H](rec200_tmp, vsize))
            vstore(dsp.rec200_perm, vload[H](rec200_tmp, vsize + hsize), hsize)
            vstore(dsp.rec199_perm, vload[H](rec199_tmp, vsize))
            vstore(dsp.rec199_perm, vload[H](rec199_tmp, vsize + hsize), hsize)
            vstore(dsp.rec198_perm, vload[H](rec198_tmp, vsize))
            vstore(dsp.rec198_perm, vload[H](rec198_tmp, vsize + hsize), hsize)
            vstore(dsp.rec197_perm, vload[H](rec197_tmp, vsize))
            vstore(dsp.rec197_perm, vload[H](rec197_tmp, vsize + hsize), hsize)
            vstore(dsp.rec196_perm, vload[H](rec196_tmp, vsize))
            vstore(dsp.rec196_perm, vload[H](rec196_tmp, vsize + hsize), hsize)
            vstore(dsp.rec195_perm, vload[H](rec195_tmp, vsize))
            vstore(dsp.rec195_perm, vload[H](rec195_tmp, vsize + hsize), hsize)
            vstore(dsp.rec194_perm, vload[H](rec194_tmp, vsize))
            vstore(dsp.rec194_perm, vload[H](rec194_tmp, vsize + hsize), hsize)
            vstore(dsp.rec193_perm, vload[H](rec193_tmp, vsize))
            vstore(dsp.rec193_perm, vload[H](rec193_tmp, vsize + hsize), hsize)
            vstore(dsp.rec192_perm, vload[H](rec192_tmp, vsize))
            vstore(dsp.rec192_perm, vload[H](rec192_tmp, vsize + hsize), hsize)
            vstore(dsp.yec23_perm, vload[H](yec23_tmp, vsize))
            vstore(dsp.yec23_perm, vload[H](yec23_tmp, vsize + hsize), hsize)
            vstore(dsp.rec191_perm, vload[H](rec191_tmp, vsize))
            vstore(dsp.rec191_perm, vload[H](rec191_tmp, vsize + hsize), hsize)
            vstore(dsp.rec190_perm, vload[H](rec190_tmp, vsize))
            vstore(dsp.rec190_perm, vload[H](rec190_tmp, vsize + hsize), hsize)
            vstore(dsp.rec189_perm, vload[H](rec189_tmp, vsize))
            vstore(dsp.rec189_perm, vload[H](rec189_tmp, vsize + hsize), hsize)
            vstore(dsp.rec188_perm, vload[H](rec188_tmp, vsize))
            vstore(dsp.rec188_perm, vload[H](rec188_tmp, vsize + hsize), hsize)
            vstore(dsp.yec22_perm, vload[H](yec22_tmp, vsize))
            vstore(dsp.yec22_perm, vload[H](yec22_tmp, vsize + hsize), hsize)
            vstore(dsp.rec187_perm, vload[H](rec187_tmp, vsize))
            vstore(dsp.rec187_perm, vload[H](rec187_tmp, vsize + hsize), hsize)
            vstore(dsp.rec186_perm, vload[H](rec186_tmp, vsize))
            vstore(dsp.rec186_perm, vload[H](rec186_tmp, vsize + hsize), hsize)
            vstore(dsp.rec185_perm, vload[H](rec185_tmp, vsize))
            vstore(dsp.rec185_perm, vload[H](rec185_tmp, vsize + hsize), hsize)
            vstore(dsp.rec184_perm, vload[H](rec184_tmp, vsize))
            vstore(dsp.rec184_perm, vload[H](rec184_tmp, vsize + hsize), hsize)
            vstore(dsp.rec183_perm, vload[H](rec183_tmp, vsize))
            vstore(dsp.rec183_perm, vload[H](rec183_tmp, vsize + hsize), hsize)
            vstore(dsp.yec21_perm, vload[H](yec21_tmp, vsize))
            vstore(dsp.yec21_perm, vload[H](yec21_tmp, vsize + hsize), hsize)
            vstore(dsp.rec182_perm, vload[H](rec182_tmp, vsize))
            vstore(dsp.rec182_perm, vload[H](rec182_tmp, vsize + hsize), hsize)
            vstore(dsp.rec181_perm, vload[H](rec181_tmp, vsize))
            vstore(dsp.rec181_perm, vload[H](rec181_tmp, vsize + hsize), hsize)
            vstore(dsp.rec180_perm, vload[H](rec180_tmp, vsize))
            vstore(dsp.rec180_perm, vload[H](rec180_tmp, vsize + hsize), hsize)
            vstore(dsp.rec179_perm, vload[H](rec179_tmp, vsize))
            vstore(dsp.rec179_perm, vload[H](rec179_tmp, vsize + hsize), hsize)
            vstore(dsp.rec178_perm, vload[H](rec178_tmp, vsize))
            vstore(dsp.rec178_perm, vload[H](rec178_tmp, vsize + hsize), hsize)
            vstore(dsp.rec177_perm, vload[H](rec177_tmp, vsize))
            vstore(dsp.rec177_perm, vload[H](rec177_tmp, vsize + hsize), hsize)
            vstore(dsp.rec176_perm, vload[H](rec176_tmp, vsize))
            vstore(dsp.rec176_perm, vload[H](rec176_tmp, vsize + hsize), hsize)
            vstore(dsp.rec175_perm, vload[H](rec175_tmp, vsize))
            vstore(dsp.rec175_perm, vload[H](rec175_tmp, vsize + hsize), hsize)
            vstore(dsp.rec174_perm, vload[H](rec174_tmp, vsize))
            vstore(dsp.rec174_perm, vload[H](rec174_tmp, vsize + hsize), hsize)
            vstore(dsp.rec173_perm, vload[H](rec173_tmp, vsize))
            vstore(dsp.rec173_perm, vload[H](rec173_tmp, vsize + hsize), hsize)
            vstore(dsp.rec172_perm, vload[H](rec172_tmp, vsize))
            vstore(dsp.rec172_perm, vload[H](rec172_tmp, vsize + hsize), hsize)
            vstore(dsp.rec171_perm, vload[H](rec171_tmp, vsize))
            vstore(dsp.rec171_perm, vload[H](rec171_tmp, vsize + hsize), hsize)
            vstore(dsp.rec170_perm, vload[H](rec170_tmp, vsize))
            vstore(dsp.rec170_perm, vload[H](rec170_tmp, vsize + hsize), hsize)
            vstore(dsp.yec20_perm, vload[H](yec20_tmp, vsize))
            vstore(dsp.yec20_perm, vload[H](yec20_tmp, vsize + hsize), hsize)
            vstore(dsp.rec169_perm, vload[H](rec169_tmp, vsize))
            vstore(dsp.rec169_perm, vload[H](rec169_tmp, vsize + hsize), hsize)
            vstore(dsp.rec168_perm, vload[H](rec168_tmp, vsize))
            vstore(dsp.rec168_perm, vload[H](rec168_tmp, vsize + hsize), hsize)
            vstore(dsp.rec167_perm, vload[H](rec167_tmp, vsize))
            vstore(dsp.rec167_perm, vload[H](rec167_tmp, vsize + hsize), hsize)
            vstore(dsp.rec166_perm, vload[H](rec166_tmp, vsize))
            vstore(dsp.rec166_perm, vload[H](rec166_tmp, vsize + hsize), hsize)
            vstore(dsp.yec19_perm, vload[H](yec19_tmp, vsize))
            vstore(dsp.yec19_perm, vload[H](yec19_tmp, vsize + hsize), hsize)
            vstore(dsp.rec165_perm, vload[H](rec165_tmp, vsize))
            vstore(dsp.rec165_perm, vload[H](rec165_tmp, vsize + hsize), hsize)
            vstore(dsp.rec164_perm, vload[H](rec164_tmp, vsize))
            vstore(dsp.rec164_perm, vload[H](rec164_tmp, vsize + hsize), hsize)
            vstore(dsp.rec163_perm, vload[H](rec163_tmp, vsize))
            vstore(dsp.rec163_perm, vload[H](rec163_tmp, vsize + hsize), hsize)
            vstore(dsp.rec162_perm, vload[H](rec162_tmp, vsize))
            vstore(dsp.rec162_perm, vload[H](rec162_tmp, vsize + hsize), hsize)
            vstore(dsp.rec161_perm, vload[H](rec161_tmp, vsize))
            vstore(dsp.rec161_perm, vload[H](rec161_tmp, vsize + hsize), hsize)
            vstore(dsp.yec18_perm, vload[H](yec18_tmp, vsize))
            vstore(dsp.yec18_perm, vload[H](yec18_tmp, vsize + hsize), hsize)
            vstore(dsp.rec160_perm, vload[H](rec160_tmp, vsize))
            vstore(dsp.rec160_perm, vload[H](rec160_tmp, vsize + hsize), hsize)
            vstore(dsp.rec159_perm, vload[H](rec159_tmp, vsize))
            vstore(dsp.rec159_perm, vload[H](rec159_tmp, vsize + hsize), hsize)
            vstore(dsp.rec158_perm, vload[H](rec158_tmp, vsize))
            vstore(dsp.rec158_perm, vload[H](rec158_tmp, vsize + hsize), hsize)
            vstore(dsp.rec157_perm, vload[H](rec157_tmp, vsize))
            vstore(dsp.rec157_perm, vload[H](rec157_tmp, vsize + hsize), hsize)
            vstore(dsp.rec156_perm, vload[H](rec156_tmp, vsize))
            vstore(dsp.rec156_perm, vload[H](rec156_tmp, vsize + hsize), hsize)
            vstore(dsp.rec155_perm, vload[H](rec155_tmp, vsize))
            vstore(dsp.rec155_perm, vload[H](rec155_tmp, vsize + hsize), hsize)
            vstore(dsp.rec154_perm, vload[H](rec154_tmp, vsize))
            vstore(dsp.rec154_perm, vload[H](rec154_tmp, vsize + hsize), hsize)
            vstore(dsp.rec153_perm, vload[H](rec153_tmp, vsize))
            vstore(dsp.rec153_perm, vload[H](rec153_tmp, vsize + hsize), hsize)
            vstore(dsp.rec152_perm, vload[H](rec152_tmp, vsize))
            vstore(dsp.rec152_perm, vload[H](rec152_tmp, vsize + hsize), hsize)
            vstore(dsp.rec151_perm, vload[H](rec151_tmp, vsize))
            vstore(dsp.rec151_perm, vload[H](rec151_tmp, vsize + hsize), hsize)
            vstore(dsp.rec150_perm, vload[H](rec150_tmp, vsize))
            vstore(dsp.rec150_perm, vload[H](rec150_tmp, vsize + hsize), hsize)
            vstore(dsp.rec149_perm, vload[H](rec149_tmp, vsize))
            vstore(dsp.rec149_perm, vload[H](rec149_tmp, vsize + hsize), hsize)
            vstore(dsp.rec148_perm, vload[H](rec148_tmp, vsize))
            vstore(dsp.rec148_perm, vload[H](rec148_tmp, vsize + hsize), hsize)
            vstore(dsp.yec17_perm, vload[H](yec17_tmp, vsize))
            vstore(dsp.yec17_perm, vload[H](yec17_tmp, vsize + hsize), hsize)
            vstore(dsp.rec147_perm, vload[H](rec147_tmp, vsize))
            vstore(dsp.rec147_perm, vload[H](rec147_tmp, vsize + hsize), hsize)
            vstore(dsp.rec146_perm, vload[H](rec146_tmp, vsize))
            vstore(dsp.rec146_perm, vload[H](rec146_tmp, vsize + hsize), hsize)
            vstore(dsp.rec145_perm, vload[H](rec145_tmp, vsize))
            vstore(dsp.rec145_perm, vload[H](rec145_tmp, vsize + hsize), hsize)
            vstore(dsp.rec144_perm, vload[H](rec144_tmp, vsize))
            vstore(dsp.rec144_perm, vload[H](rec144_tmp, vsize + hsize), hsize)
            vstore(dsp.yec16_perm, vload[H](yec16_tmp, vsize))
            vstore(dsp.yec16_perm, vload[H](yec16_tmp, vsize + hsize), hsize)
            vstore(dsp.rec143_perm, vload[H](rec143_tmp, vsize))
            vstore(dsp.rec143_perm, vload[H](rec143_tmp, vsize + hsize), hsize)
            vstore(dsp.rec142_perm, vload[H](rec142_tmp, vsize))
            vstore(dsp.rec142_perm, vload[H](rec142_tmp, vsize + hsize), hsize)
            vstore(dsp.rec141_perm, vload[H](rec141_tmp, vsize))
            vstore(dsp.rec141_perm, vload[H](rec141_tmp, vsize + hsize), hsize)
            vstore(dsp.rec140_perm, vload[H](rec140_tmp, vsize))
            vstore(dsp.rec140_perm, vload[H](rec140_tmp, vsize + hsize), hsize)
            vstore(dsp.rec139_perm, vload[H](rec139_tmp, vsize))
            vstore(dsp.rec139_perm, vload[H](rec139_tmp, vsize + hsize), hsize)
            vstore(dsp.yec15_perm, vload[H](yec15_tmp, vsize))
            vstore(dsp.yec15_perm, vload[H](yec15_tmp, vsize + hsize), hsize)
            vstore(dsp.rec138_perm, vload[H](rec138_tmp, vsize))
            vstore(dsp.rec138_perm, vload[H](rec138_tmp, vsize + hsize), hsize)
            vstore(dsp.rec137_perm, vload[H](rec137_tmp, vsize))
            vstore(dsp.rec137_perm, vload[H](rec137_tmp, vsize + hsize), hsize)
            vstore(dsp.rec136_perm, vload[H](rec136_tmp, vsize))
            vstore(dsp.rec136_perm, vload[H](rec136_tmp, vsize + hsize), hsize)
            vstore(dsp.rec135_perm, vload[H](rec135_tmp, vsize))
            vstore(dsp.rec135_perm, vload[H](rec135_tmp, vsize + hsize), hsize)
            vstore(dsp.rec134_perm, vload[H](rec134_tmp, vsize))
            vstore(dsp.rec134_perm, vload[H](rec134_tmp, vsize + hsize), hsize)
            vstore(dsp.rec133_perm, vload[H](rec133_tmp, vsize))
            vstore(dsp.rec133_perm, vload[H](rec133_tmp, vsize + hsize), hsize)
            vstore(dsp.rec132_perm, vload[H](rec132_tmp, vsize))
            vstore(dsp.rec132_perm, vload[H](rec132_tmp, vsize + hsize), hsize)
            vstore(dsp.rec131_perm, vload[H](rec131_tmp, vsize))
            vstore(dsp.rec131_perm, vload[H](rec131_tmp, vsize + hsize), hsize)
            vstore(dsp.rec130_perm, vload[H](rec130_tmp, vsize))
            vstore(dsp.rec130_perm, vload[H](rec130_tmp, vsize + hsize), hsize)
            vstore(dsp.rec129_perm, vload[H](rec129_tmp, vsize))
            vstore(dsp.rec129_perm, vload[H](rec129_tmp, vsize + hsize), hsize)
            vstore(dsp.rec128_perm, vload[H](rec128_tmp, vsize))
            vstore(dsp.rec128_perm, vload[H](rec128_tmp, vsize + hsize), hsize)
            vstore(dsp.rec127_perm, vload[H](rec127_tmp, vsize))
            vstore(dsp.rec127_perm, vload[H](rec127_tmp, vsize + hsize), hsize)
            vstore(dsp.rec126_perm, vload[H](rec126_tmp, vsize))
            vstore(dsp.rec126_perm, vload[H](rec126_tmp, vsize + hsize), hsize)
            vstore(dsp.yec14_perm, vload[H](yec14_tmp, vsize))
            vstore(dsp.yec14_perm, vload[H](yec14_tmp, vsize + hsize), hsize)
            vstore(dsp.rec125_perm, vload[H](rec125_tmp, vsize))
            vstore(dsp.rec125_perm, vload[H](rec125_tmp, vsize + hsize), hsize)
            vstore(dsp.rec124_perm, vload[H](rec124_tmp, vsize))
            vstore(dsp.rec124_perm, vload[H](rec124_tmp, vsize + hsize), hsize)
            vstore(dsp.rec123_perm, vload[H](rec123_tmp, vsize))
            vstore(dsp.rec123_perm, vload[H](rec123_tmp, vsize + hsize), hsize)
            vstore(dsp.rec122_perm, vload[H](rec122_tmp, vsize))
            vstore(dsp.rec122_perm, vload[H](rec122_tmp, vsize + hsize), hsize)
            vstore(dsp.yec13_perm, vload[H](yec13_tmp, vsize))
            vstore(dsp.yec13_perm, vload[H](yec13_tmp, vsize + hsize), hsize)
            vstore(dsp.rec121_perm, vload[H](rec121_tmp, vsize))
            vstore(dsp.rec121_perm, vload[H](rec121_tmp, vsize + hsize), hsize)
            vstore(dsp.rec120_perm, vload[H](rec120_tmp, vsize))
            vstore(dsp.rec120_perm, vload[H](rec120_tmp, vsize + hsize), hsize)
            vstore(dsp.rec119_perm, vload[H](rec119_tmp, vsize))
            vstore(dsp.rec119_perm, vload[H](rec119_tmp, vsize + hsize), hsize)
            vstore(dsp.rec118_perm, vload[H](rec118_tmp, vsize))
            vstore(dsp.rec118_perm, vload[H](rec118_tmp, vsize + hsize), hsize)
            vstore(dsp.rec117_perm, vload[H](rec117_tmp, vsize))
            vstore(dsp.rec117_perm, vload[H](rec117_tmp, vsize + hsize), hsize)
            vstore(dsp.yec12_perm, vload[H](yec12_tmp, vsize))
            vstore(dsp.yec12_perm, vload[H](yec12_tmp, vsize + hsize), hsize)
            vstore(dsp.rec116_perm, vload[H](rec116_tmp, vsize))
            vstore(dsp.rec116_perm, vload[H](rec116_tmp, vsize + hsize), hsize)
            vstore(dsp.rec115_perm, vload[H](rec115_tmp, vsize))
            vstore(dsp.rec115_perm, vload[H](rec115_tmp, vsize + hsize), hsize)
            vstore(dsp.rec114_perm, vload[H](rec114_tmp, vsize))
            vstore(dsp.rec114_perm, vload[H](rec114_tmp, vsize + hsize), hsize)
            vstore(dsp.rec113_perm, vload[H](rec113_tmp, vsize))
            vstore(dsp.rec113_perm, vload[H](rec113_tmp, vsize + hsize), hsize)
            vstore(dsp.rec112_perm, vload[H](rec112_tmp, vsize))
            vstore(dsp.rec112_perm, vload[H](rec112_tmp, vsize + hsize), hsize)
            vstore(dsp.rec111_perm, vload[H](rec111_tmp, vsize))
            vstore(dsp.rec111_perm, vload[H](rec111_tmp, vsize + hsize), hsize)
            vstore(dsp.rec110_perm, vload[H](rec110_tmp, vsize))
            vstore(dsp.rec110_perm, vload[H](rec110_tmp, vsize + hsize), hsize)
            vstore(dsp.rec109_perm, vload[H](rec109_tmp, vsize))
            vstore(dsp.rec109_perm, vload[H](rec109_tmp, vsize + hsize), hsize)
            vstore(dsp.rec108_perm, vload[H](rec108_tmp, vsize))
            vstore(dsp.rec108_perm, vload[H](rec108_tmp, vsize + hsize), hsize)
            vstore(dsp.rec107_perm, vload[H](rec107_tmp, vsize))
            vstore(dsp.rec107_perm, vload[H](rec107_tmp, vsize + hsize), hsize)
            vstore(dsp.rec106_perm, vload[H](rec106_tmp, vsize))
            vstore(dsp.rec106_perm, vload[H](rec106_tmp, vsize + hsize), hsize)
            vstore(dsp.rec105_perm, vload[H](rec105_tmp, vsize))
            vstore(dsp.rec105_perm, vload[H](rec105_tmp, vsize + hsize), hsize)
            vstore(dsp.rec104_perm, vload[H](rec104_tmp, vsize))
            vstore(dsp.rec104_perm, vload[H](rec104_tmp, vsize + hsize), hsize)
            vstore(dsp.yec11_perm, vload[H](yec11_tmp, vsize))
            vstore(dsp.yec11_perm, vload[H](yec11_tmp, vsize + hsize), hsize)
            vstore(dsp.rec103_perm, vload[H](rec103_tmp, vsize))
            vstore(dsp.rec103_perm, vload[H](rec103_tmp, vsize + hsize), hsize)
            vstore(dsp.rec102_perm, vload[H](rec102_tmp, vsize))
            vstore(dsp.rec102_perm, vload[H](rec102_tmp, vsize + hsize), hsize)
            vstore(dsp.rec101_perm, vload[H](rec101_tmp, vsize))
            vstore(dsp.rec101_perm, vload[H](rec101_tmp, vsize + hsize), hsize)
            vstore(dsp.rec100_perm, vload[H](rec100_tmp, vsize))
            vstore(dsp.rec100_perm, vload[H](rec100_tmp, vsize + hsize), hsize)
            vstore(dsp.yec10_perm, vload[H](yec10_tmp, vsize))
            vstore(dsp.yec10_perm, vload[H](yec10_tmp, vsize + hsize), hsize)
            vstore(dsp.rec99_perm, vload[H](rec99_tmp, vsize))
            vstore(dsp.rec99_perm, vload[H](rec99_tmp, vsize + hsize), hsize)
            vstore(dsp.rec98_perm, vload[H](rec98_tmp, vsize))
            vstore(dsp.rec98_perm, vload[H](rec98_tmp, vsize + hsize), hsize)
            vstore(dsp.rec97_perm, vload[H](rec97_tmp, vsize))
            vstore(dsp.rec97_perm, vload[H](rec97_tmp, vsize + hsize), hsize)
            vstore(dsp.rec96_perm, vload[H](rec96_tmp, vsize))
            vstore(dsp.rec96_perm, vload[H](rec96_tmp, vsize + hsize), hsize)
            vstore(dsp.rec95_perm, vload[H](rec95_tmp, vsize))
            vstore(dsp.rec95_perm, vload[H](rec95_tmp, vsize + hsize), hsize)
            vstore(dsp.yec9_perm, vload[H](yec9_tmp, vsize))
            vstore(dsp.yec9_perm, vload[H](yec9_tmp, vsize + hsize), hsize)
            vstore(dsp.rec94_perm, vload[H](rec94_tmp, vsize))
            vstore(dsp.rec94_perm, vload[H](rec94_tmp, vsize + hsize), hsize)
            vstore(dsp.rec93_perm, vload[H](rec93_tmp, vsize))
            vstore(dsp.rec93_perm, vload[H](rec93_tmp, vsize + hsize), hsize)
            vstore(dsp.rec92_perm, vload[H](rec92_tmp, vsize))
            vstore(dsp.rec92_perm, vload[H](rec92_tmp, vsize + hsize), hsize)
            vstore(dsp.rec91_perm, vload[H](rec91_tmp, vsize))
            vstore(dsp.rec91_perm, vload[H](rec91_tmp, vsize + hsize), hsize)
            vstore(dsp.rec90_perm, vload[H](rec90_tmp, vsize))
            vstore(dsp.rec90_perm, vload[H](rec90_tmp, vsize + hsize), hsize)
            vstore(dsp.rec89_perm, vload[H](rec89_tmp, vsize))
            vstore(dsp.rec89_perm, vload[H](rec89_tmp, vsize + hsize), hsize)
            vstore(dsp.rec88_perm, vload[H](rec88_tmp, vsize))
            vstore(dsp.rec88_perm, vload[H](rec88_tmp, vsize + hsize), hsize)
            vstore(dsp.rec87_perm, vload[H](rec87_tmp, vsize))
            vstore(dsp.rec87_perm, vload[H](rec87_tmp, vsize + hsize), hsize)
            vstore(dsp.rec86_perm, vload[H](rec86_tmp, vsize))
            vstore(dsp.rec86_perm, vload[H](rec86_tmp, vsize + hsize), hsize)
            vstore(dsp.rec85_perm, vload[H](rec85_tmp, vsize))
            vstore(dsp.rec85_perm, vload[H](rec85_tmp, vsize + hsize), hsize)
            vstore(dsp.rec84_perm, vload[H](rec84_tmp, vsize))
            vstore(dsp.rec84_perm, vload[H](rec84_tmp, vsize + hsize), hsize)
            vstore(dsp.rec83_perm, vload[H](rec83_tmp, vsize))
            vstore(dsp.rec83_perm, vload[H](rec83_tmp, vsize + hsize), hsize)
            vstore(dsp.rec82_perm, vload[H](rec82_tmp, vsize))
            vstore(dsp.rec82_perm, vload[H](rec82_tmp, vsize + hsize), hsize)
            vstore(dsp.yec8_perm, vload[H](yec8_tmp, vsize))
            vstore(dsp.yec8_perm, vload[H](yec8_tmp, vsize + hsize), hsize)
            vstore(dsp.rec81_perm, vload[H](rec81_tmp, vsize))
            vstore(dsp.rec81_perm, vload[H](rec81_tmp, vsize + hsize), hsize)
            vstore(dsp.rec80_perm, vload[H](rec80_tmp, vsize))
            vstore(dsp.rec80_perm, vload[H](rec80_tmp, vsize + hsize), hsize)
            vstore(dsp.rec79_perm, vload[H](rec79_tmp, vsize))
            vstore(dsp.rec79_perm, vload[H](rec79_tmp, vsize + hsize), hsize)
            vstore(dsp.rec78_perm, vload[H](rec78_tmp, vsize))
            vstore(dsp.rec78_perm, vload[H](rec78_tmp, vsize + hsize), hsize)
            vstore(dsp.yec7_perm, vload[H](yec7_tmp, vsize))
            vstore(dsp.yec7_perm, vload[H](yec7_tmp, vsize + hsize), hsize)
            vstore(dsp.rec77_perm, vload[H](rec77_tmp, vsize))
            vstore(dsp.rec77_perm, vload[H](rec77_tmp, vsize + hsize), hsize)
            vstore(dsp.rec76_perm, vload[H](rec76_tmp, vsize))
            vstore(dsp.rec76_perm, vload[H](rec76_tmp, vsize + hsize), hsize)
            vstore(dsp.rec75_perm, vload[H](rec75_tmp, vsize))
            vstore(dsp.rec75_perm, vload[H](rec75_tmp, vsize + hsize), hsize)
            vstore(dsp.rec74_perm, vload[H](rec74_tmp, vsize))
            vstore(dsp.rec74_perm, vload[H](rec74_tmp, vsize + hsize), hsize)
            vstore(dsp.rec73_perm, vload[H](rec73_tmp, vsize))
            vstore(dsp.rec73_perm, vload[H](rec73_tmp, vsize + hsize), hsize)
            vstore(dsp.yec6_perm, vload[H](yec6_tmp, vsize))
            vstore(dsp.yec6_perm, vload[H](yec6_tmp, vsize + hsize), hsize)
            vstore(dsp.rec72_perm, vload[H](rec72_tmp, vsize))
            vstore(dsp.rec72_perm, vload[H](rec72_tmp, vsize + hsize), hsize)
            vstore(dsp.rec71_perm, vload[H](rec71_tmp, vsize))
            vstore(dsp.rec71_perm, vload[H](rec71_tmp, vsize + hsize), hsize)
            vstore(dsp.rec70_perm, vload[H](rec70_tmp, vsize))
            vstore(dsp.rec70_perm, vload[H](rec70_tmp, vsize + hsize), hsize)
            vstore(dsp.rec69_perm, vload[H](rec69_tmp, vsize))
            vstore(dsp.rec69_perm, vload[H](rec69_tmp, vsize + hsize), hsize)
            vstore(dsp.rec68_perm, vload[H](rec68_tmp, vsize))
            vstore(dsp.rec68_perm, vload[H](rec68_tmp, vsize + hsize), hsize)
            vstore(dsp.rec67_perm, vload[H](rec67_tmp, vsize))
            vstore(dsp.rec67_perm, vload[H](rec67_tmp, vsize + hsize), hsize)
            vstore(dsp.rec66_perm, vload[H](rec66_tmp, vsize))
            vstore(dsp.rec66_perm, vload[H](rec66_tmp, vsize + hsize), hsize)
            vstore(dsp.rec65_perm, vload[H](rec65_tmp, vsize))
            vstore(dsp.rec65_perm, vload[H](rec65_tmp, vsize + hsize), hsize)
            vstore(dsp.rec64_perm, vload[H](rec64_tmp, vsize))
            vstore(dsp.rec64_perm, vload[H](rec64_tmp, vsize + hsize), hsize)
            vstore(dsp.rec63_perm, vload[H](rec63_tmp, vsize))
            vstore(dsp.rec63_perm, vload[H](rec63_tmp, vsize + hsize), hsize)
            vstore(dsp.rec62_perm, vload[H](rec62_tmp, vsize))
            vstore(dsp.rec62_perm, vload[H](rec62_tmp, vsize + hsize), hsize)
            vstore(dsp.rec61_perm, vload[H](rec61_tmp, vsize))
            vstore(dsp.rec61_perm, vload[H](rec61_tmp, vsize + hsize), hsize)
            vstore(dsp.rec60_perm, vload[H](rec60_tmp, vsize))
            vstore(dsp.rec60_perm, vload[H](rec60_tmp, vsize + hsize), hsize)
            vstore(dsp.yec5_perm, vload[H](yec5_tmp, vsize))
            vstore(dsp.yec5_perm, vload[H](yec5_tmp, vsize + hsize), hsize)
            vstore(dsp.rec59_perm, vload[H](rec59_tmp, vsize))
            vstore(dsp.rec59_perm, vload[H](rec59_tmp, vsize + hsize), hsize)
            vstore(dsp.rec58_perm, vload[H](rec58_tmp, vsize))
            vstore(dsp.rec58_perm, vload[H](rec58_tmp, vsize + hsize), hsize)
            vstore(dsp.rec57_perm, vload[H](rec57_tmp, vsize))
            vstore(dsp.rec57_perm, vload[H](rec57_tmp, vsize + hsize), hsize)
            vstore(dsp.rec56_perm, vload[H](rec56_tmp, vsize))
            vstore(dsp.rec56_perm, vload[H](rec56_tmp, vsize + hsize), hsize)
            vstore(dsp.yec4_perm, vload[H](yec4_tmp, vsize))
            vstore(dsp.yec4_perm, vload[H](yec4_tmp, vsize + hsize), hsize)
            vstore(dsp.rec55_perm, vload[H](rec55_tmp, vsize))
            vstore(dsp.rec55_perm, vload[H](rec55_tmp, vsize + hsize), hsize)
            vstore(dsp.rec54_perm, vload[H](rec54_tmp, vsize))
            vstore(dsp.rec54_perm, vload[H](rec54_tmp, vsize + hsize), hsize)
            vstore(dsp.rec53_perm, vload[H](rec53_tmp, vsize))
            vstore(dsp.rec53_perm, vload[H](rec53_tmp, vsize + hsize), hsize)
            vstore(dsp.rec52_perm, vload[H](rec52_tmp, vsize))
            vstore(dsp.rec52_perm, vload[H](rec52_tmp, vsize + hsize), hsize)
            vstore(dsp.rec51_perm, vload[H](rec51_tmp, vsize))
            vstore(dsp.rec51_perm, vload[H](rec51_tmp, vsize + hsize), hsize)
            vstore(dsp.yec3_perm, vload[H](yec3_tmp, vsize))
            vstore(dsp.yec3_perm, vload[H](yec3_tmp, vsize + hsize), hsize)
            vstore(dsp.rec50_perm, vload[H](rec50_tmp, vsize))
            vstore(dsp.rec50_perm, vload[H](rec50_tmp, vsize + hsize), hsize)
            vstore(dsp.rec49_perm, vload[H](rec49_tmp, vsize))
            vstore(dsp.rec49_perm, vload[H](rec49_tmp, vsize + hsize), hsize)
            vstore(dsp.rec48_perm, vload[H](rec48_tmp, vsize))
            vstore(dsp.rec48_perm, vload[H](rec48_tmp, vsize + hsize), hsize)
            vstore(dsp.rec47_perm, vload[H](rec47_tmp, vsize))
            vstore(dsp.rec47_perm, vload[H](rec47_tmp, vsize + hsize), hsize)
            vstore(dsp.rec46_perm, vload[H](rec46_tmp, vsize))
            vstore(dsp.rec46_perm, vload[H](rec46_tmp, vsize + hsize), hsize)
            vstore(dsp.rec45_perm, vload[H](rec45_tmp, vsize))
            vstore(dsp.rec45_perm, vload[H](rec45_tmp, vsize + hsize), hsize)
            vstore(dsp.rec44_perm, vload[H](rec44_tmp, vsize))
            vstore(dsp.rec44_perm, vload[H](rec44_tmp, vsize + hsize), hsize)
            vstore(dsp.rec43_perm, vload[H](rec43_tmp, vsize))
            vstore(dsp.rec43_perm, vload[H](rec43_tmp, vsize + hsize), hsize)
            vstore(dsp.rec42_perm, vload[H](rec42_tmp, vsize))
            vstore(dsp.rec42_perm, vload[H](rec42_tmp, vsize + hsize), hsize)
            vstore(dsp.rec41_perm, vload[H](rec41_tmp, vsize))
            vstore(dsp.rec41_perm, vload[H](rec41_tmp, vsize + hsize), hsize)
            vstore(dsp.rec40_perm, vload[H](rec40_tmp, vsize))
            vstore(dsp.rec40_perm, vload[H](rec40_tmp, vsize + hsize), hsize)
            vstore(dsp.rec39_perm, vload[H](rec39_tmp, vsize))
            vstore(dsp.rec39_perm, vload[H](rec39_tmp, vsize + hsize), hsize)
            vstore(dsp.rec38_perm, vload[H](rec38_tmp, vsize))
            vstore(dsp.rec38_perm, vload[H](rec38_tmp, vsize + hsize), hsize)
            vstore(dsp.yec2_perm, vload[H](yec2_tmp, vsize))
            vstore(dsp.yec2_perm, vload[H](yec2_tmp, vsize + hsize), hsize)
            vstore(dsp.rec37_perm, vload[H](rec37_tmp, vsize))
            vstore(dsp.rec37_perm, vload[H](rec37_tmp, vsize + hsize), hsize)
            vstore(dsp.rec36_perm, vload[H](rec36_tmp, vsize))
            vstore(dsp.rec36_perm, vload[H](rec36_tmp, vsize + hsize), hsize)
            vstore(dsp.rec35_perm, vload[H](rec35_tmp, vsize))
            vstore(dsp.rec35_perm, vload[H](rec35_tmp, vsize + hsize), hsize)
            vstore(dsp.rec34_perm, vload[H](rec34_tmp, vsize))
            vstore(dsp.rec34_perm, vload[H](rec34_tmp, vsize + hsize), hsize)
            vstore(dsp.yec1_perm, vload[H](yec1_tmp, vsize))
            vstore(dsp.yec1_perm, vload[H](yec1_tmp, vsize + hsize), hsize)
            vstore(dsp.rec33_perm, vload[H](rec33_tmp, vsize))
            vstore(dsp.rec33_perm, vload[H](rec33_tmp, vsize + hsize), hsize)
            vstore(dsp.rec32_perm, vload[H](rec32_tmp, vsize))
            vstore(dsp.rec32_perm, vload[H](rec32_tmp, vsize + hsize), hsize)
            vstore(dsp.rec31_perm, vload[H](rec31_tmp, vsize))
            vstore(dsp.rec31_perm, vload[H](rec31_tmp, vsize + hsize), hsize)
            vstore(dsp.rec30_perm, vload[H](rec30_tmp, vsize))
            vstore(dsp.rec30_perm, vload[H](rec30_tmp, vsize + hsize), hsize)
            vstore(dsp.rec29_perm, vload[H](rec29_tmp, vsize))
            vstore(dsp.rec29_perm, vload[H](rec29_tmp, vsize + hsize), hsize)
            vstore(dsp.yec0_perm, vload[H](yec0_tmp, vsize))
            vstore(dsp.yec0_perm, vload[H](yec0_tmp, vsize + hsize), hsize)
            vstore(dsp.rec28_perm, vload[H](rec28_tmp, vsize))
            vstore(dsp.rec28_perm, vload[H](rec28_tmp, vsize + hsize), hsize)
            vstore(dsp.rec27_perm, vload[H](rec27_tmp, vsize))
            vstore(dsp.rec27_perm, vload[H](rec27_tmp, vsize + hsize), hsize)
            vstore(dsp.rec26_perm, vload[H](rec26_tmp, vsize))
            vstore(dsp.rec26_perm, vload[H](rec26_tmp, vsize + hsize), hsize)
            vstore(dsp.rec25_perm, vload[H](rec25_tmp, vsize))
            vstore(dsp.rec25_perm, vload[H](rec25_tmp, vsize + hsize), hsize)
            vstore(dsp.rec24_perm, vload[H](rec24_tmp, vsize))
            vstore(dsp.rec24_perm, vload[H](rec24_tmp, vsize + hsize), hsize)
            vstore(dsp.rec23_perm, vload[H](rec23_tmp, vsize))
            vstore(dsp.rec23_perm, vload[H](rec23_tmp, vsize + hsize), hsize)
            vstore(dsp.rec22_perm, vload[H](rec22_tmp, vsize))
            vstore(dsp.rec22_perm, vload[H](rec22_tmp, vsize + hsize), hsize)
            vstore(dsp.rec21_perm, vload[H](rec21_tmp, vsize))
            vstore(dsp.rec21_perm, vload[H](rec21_tmp, vsize + hsize), hsize)
            vstore(dsp.rec20_perm, vload[H](rec20_tmp, vsize))
            vstore(dsp.rec20_perm, vload[H](rec20_tmp, vsize + hsize), hsize)
            vstore(dsp.rec19_perm, vload[H](rec19_tmp, vsize))
            vstore(dsp.rec19_perm, vload[H](rec19_tmp, vsize + hsize), hsize)
            vstore(dsp.rec18_perm, vload[H](rec18_tmp, vsize))
            vstore(dsp.rec18_perm, vload[H](rec18_tmp, vsize + hsize), hsize)
            vstore(dsp.rec0_perm, vload[H](rec0_tmp, vsize))
            vstore(dsp.rec0_perm, vload[H](rec0_tmp, vsize + hsize), hsize)
            vstore(dsp.rec1_perm, vload[H](rec1_tmp, vsize))
            vstore(dsp.rec1_perm, vload[H](rec1_tmp, vsize + hsize), hsize)
            vstore(dsp.rec2_perm, vload[H](rec2_tmp, vsize))
            vstore(dsp.rec2_perm, vload[H](rec2_tmp, vsize + hsize), hsize)
            vstore(dsp.rec3_perm, vload[H](rec3_tmp, vsize))
            vstore(dsp.rec3_perm, vload[H](rec3_tmp, vsize + hsize), hsize)
            vstore(dsp.rec4_perm, vload[H](rec4_tmp, vsize))
            vstore(dsp.rec4_perm, vload[H](rec4_tmp, vsize + hsize), hsize)
            vstore(dsp.rec5_perm, vload[H](rec5_tmp, vsize))
            vstore(dsp.rec5_perm, vload[H](rec5_tmp, vsize + hsize), hsize)
            vstore(dsp.rec6_perm, vload[H](rec6_tmp, vsize))
            vstore(dsp.rec6_perm, vload[H](rec6_tmp, vsize + hsize), hsize)
            vstore(dsp.rec7_perm, vload[H](rec7_tmp, vsize))
            vstore(dsp.rec7_perm, vload[H](rec7_tmp, vsize + hsize), hsize)
            vstore(dsp.rec8_perm, vload[H](rec8_tmp, vsize))
            vstore(dsp.rec8_perm, vload[H](rec8_tmp, vsize + hsize), hsize)
            vstore(dsp.rec9_perm, vload[H](rec9_tmp, vsize))
            vstore(dsp.rec9_perm, vload[H](rec9_tmp, vsize + hsize), hsize)
            vstore(dsp.rec10_perm, vload[H](rec10_tmp, vsize))
            vstore(dsp.rec10_perm, vload[H](rec10_tmp, vsize + hsize), hsize)
            vstore(dsp.rec11_perm, vload[H](rec11_tmp, vsize))
            vstore(dsp.rec11_perm, vload[H](rec11_tmp, vsize + hsize), hsize)
            vstore(dsp.rec12_perm, vload[H](rec12_tmp, vsize))
            vstore(dsp.rec12_perm, vload[H](rec12_tmp, vsize + hsize), hsize)
            vstore(dsp.rec13_perm, vload[H](rec13_tmp, vsize))
            vstore(dsp.rec13_perm, vload[H](rec13_tmp, vsize + hsize), hsize)
            vstore(dsp.rec14_perm, vload[H](rec14_tmp, vsize))
            vstore(dsp.rec14_perm, vload[H](rec14_tmp, vsize + hsize), hsize)
            vstore(dsp.rec15_perm, vload[H](rec15_tmp, vsize))
            vstore(dsp.rec15_perm, vload[H](rec15_tmp, vsize + hsize), hsize)
            vstore(output0, (((F64Vec(slow173)) * ((((((((vload[H](rec0)) + (vload[H](rec2))) + (vload[H](rec4))) + (vload[H](rec6))) + (vload[H](rec8))) + (vload[H](rec10))) + (vload[H](rec12))) + (vload[H](rec14)))).cast[dfaust]()).join(((F64Vec(slow173)) * ((((((((vload[H](rec0, hsize)) + (vload[H](rec2, hsize))) + (vload[H](rec4, hsize))) + (vload[H](rec6, hsize))) + (vload[H](rec8, hsize))) + (vload[H](rec10, hsize))) + (vload[H](rec12, hsize))) + (vload[H](rec14, hsize)))).cast[dfaust]()))
            vstore(output1, (((F64Vec(slow173)) * ((((((((vload[H](rec1)) + (vload[H](rec3))) + (vload[H](rec5))) + (vload[H](rec7))) + (vload[H](rec9))) + (vload[H](rec11))) + (vload[H](rec13))) + (vload[H](rec15)))).cast[dfaust]()).join(((F64Vec(slow173)) * ((((((((vload[H](rec1, hsize)) + (vload[H](rec3, hsize))) + (vload[H](rec5, hsize))) + (vload[H](rec7, hsize))) + (vload[H](rec9, hsize))) + (vload[H](rec11, hsize))) + (vload[H](rec13, hsize))) + (vload[H](rec15, hsize)))).cast[dfaust]()))
            vindex += vsize

# ==============================================================================
# Faust generated DSP code end.
# ==============================================================================
# Second section of architecture provided code start.
# Defines the main entry point of the application, initializes the dsp object,
# initializes the user interface and calls the dsp runner.
# ==============================================================================

def main() raises -> None:
    var nbsamples = S32(60_000)
    var dsp = unsafe_alloc[mydsp](1)
    dsp[] = mydsp()
    var ctrl_gui = ControlGui()
    dsp[].init(SAMP_RATE)
    dsp[].build_user_interface(ctrl_gui)
    print_header(dsp[], nbsamples)
    run_dsp(dsp, ctrl_gui, nbsamples//4)
    dsp.unsafe_free()

# ==============================================================================
# Second section of architecture provided code end.
# ==============================================================================
