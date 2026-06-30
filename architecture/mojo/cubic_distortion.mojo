# ==============================================================================
# Faust to Mojo inspect architecture for the benchmark framework.
# Provides the minimal definitions and entry point needed to generate
# low-level code with clear symbols for inspecting the generated compute code.
# ==============================================================================
# First section of architecture provided code start.
# Imports the modules and the definitions of the architecture code.
# ==============================================================================

from conf import *
from help import *
from mem import *
from dsp import *
from gui import *
from meta import *

from std.benchmark import keep, clobber_memory

comptime SAMP_RATE = S32(get_defined_int["SAMP_RATE", 96_000]())
comptime BUFF_SIZE = S32(get_defined_int["BUFF_SIZE", 512]())
comptime COMPUTE_ITERS = S32(get_defined_int["COMPUTE_ITERS", 100]())

def assert_dfaust() -> None: comptime assert dfaust == F32.dtype
comptime _ = assert_dfaust()

# ==============================================================================
# First section of architecture provided code end.
# ==============================================================================
# Code generated with Faust 2.85.5 (https://faust.grame.fr)
# name: "cubic_distortion"
# Compilation options: 
#   -a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 
#   -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs
# ==============================================================================

comptime dreal = f64
comptime dreal_width = S32(simd_width_of[dreal]())

@fieldwise_init
struct mydsp(FaustDsp):
    var null_val: FaustFloat
    var hslider0: FaustFloat
    var rec1_perm: Arr[F64, 4]
    var hslider1: FaustFloat
    var rec2_perm: Arr[F64, 4]
    var hslider2: FaustFloat
    var sample_rate: S32
    var const0: F64
    var const1: F64
    var hslider3: FaustFloat
    var rec5_perm: Arr[F64, 4]
    var const2: F64
    var rec3_perm: Arr[F64, 4]
    var i_vec0_perm: Arr[S32, 4]
    var rec4_perm: Arr[F64, 4]
    var hslider4: FaustFloat
    var rec6_perm: Arr[F64, 4]
    var checkbox0: FaustFloat
    var yec0_perm: Arr[F64, 4]
    var rec0_perm: Arr[F64, 4]
    var const3: F64
    var const4: F64
    var const5: F64
    var const6: F64
    var const7: F64
    var const8: F64
    var const9: F64
    var rec10_perm: Arr[F64, 4]
    var const10: F64
    var const11: F64
    var const12: F64
    var const13: F64
    var const14: F64
    var const15: F64
    var rec9_perm: Arr[F64, 4]
    var const16: F64
    var const17: F64
    var const18: F64
    var const19: F64
    var const20: F64
    var const21: F64
    var rec8_perm: Arr[F64, 4]
    var hslider5: FaustFloat
    var const22: F64
    var const23: F64
    var const24: F64
    var const25: F64
    var rec7_perm: Arr[F64, 4]
    var const26: F64
    var const27: F64
    var const28: F64
    var rec17_perm: Arr[F64, 4]
    var const29: F64
    var const30: F64
    var const31: F64
    var const32: F64
    var const33: F64
    var const34: F64
    var rec16_perm: Arr[F64, 4]
    var const35: F64
    var const36: F64
    var const37: F64
    var const38: F64
    var const39: F64
    var rec15_perm: Arr[F64, 4]
    var const40: F64
    var const41: F64
    var const42: F64
    var const43: F64
    var const44: F64
    var const45: F64
    var const46: F64
    var const47: F64
    var const48: F64
    var rec14_perm: Arr[F64, 4]
    var const49: F64
    var const50: F64
    var const51: F64
    var const52: F64
    var const53: F64
    var const54: F64
    var rec13_perm: Arr[F64, 4]
    var const55: F64
    var const56: F64
    var const57: F64
    var const58: F64
    var const59: F64
    var const60: F64
    var rec12_perm: Arr[F64, 4]
    var const61: F64
    var const62: F64
    var const63: F64
    var rec11_perm: Arr[F64, 4]
    var const64: F64
    var const65: F64
    var const66: F64
    var rec24_perm: Arr[F64, 4]
    var const67: F64
    var const68: F64
    var const69: F64
    var const70: F64
    var const71: F64
    var const72: F64
    var rec23_perm: Arr[F64, 4]
    var const73: F64
    var const74: F64
    var const75: F64
    var const76: F64
    var const77: F64
    var rec22_perm: Arr[F64, 4]
    var const78: F64
    var const79: F64
    var const80: F64
    var const81: F64
    var const82: F64
    var const83: F64
    var const84: F64
    var const85: F64
    var const86: F64
    var rec21_perm: Arr[F64, 4]
    var const87: F64
    var const88: F64
    var const89: F64
    var const90: F64
    var const91: F64
    var const92: F64
    var rec20_perm: Arr[F64, 4]
    var const93: F64
    var const94: F64
    var const95: F64
    var const96: F64
    var const97: F64
    var const98: F64
    var rec19_perm: Arr[F64, 4]
    var const99: F64
    var const100: F64
    var const101: F64
    var rec18_perm: Arr[F64, 4]
    var const102: F64
    var const103: F64
    var const104: F64
    var rec31_perm: Arr[F64, 4]
    var const105: F64
    var const106: F64
    var const107: F64
    var const108: F64
    var const109: F64
    var const110: F64
    var rec30_perm: Arr[F64, 4]
    var const111: F64
    var const112: F64
    var const113: F64
    var const114: F64
    var const115: F64
    var rec29_perm: Arr[F64, 4]
    var const116: F64
    var const117: F64
    var const118: F64
    var const119: F64
    var const120: F64
    var const121: F64
    var const122: F64
    var const123: F64
    var const124: F64
    var rec28_perm: Arr[F64, 4]
    var const125: F64
    var const126: F64
    var const127: F64
    var const128: F64
    var const129: F64
    var const130: F64
    var rec27_perm: Arr[F64, 4]
    var const131: F64
    var const132: F64
    var const133: F64
    var const134: F64
    var const135: F64
    var const136: F64
    var rec26_perm: Arr[F64, 4]
    var const137: F64
    var const138: F64
    var const139: F64
    var rec25_perm: Arr[F64, 4]
    var const140: F64
    var const141: F64
    var const142: F64
    var rec38_perm: Arr[F64, 4]
    var const143: F64
    var const144: F64
    var const145: F64
    var const146: F64
    var const147: F64
    var const148: F64
    var rec37_perm: Arr[F64, 4]
    var const149: F64
    var const150: F64
    var const151: F64
    var const152: F64
    var const153: F64
    var rec36_perm: Arr[F64, 4]
    var const154: F64
    var const155: F64
    var const156: F64
    var const157: F64
    var const158: F64
    var const159: F64
    var const160: F64
    var const161: F64
    var const162: F64
    var rec35_perm: Arr[F64, 4]
    var const163: F64
    var const164: F64
    var const165: F64
    var const166: F64
    var const167: F64
    var const168: F64
    var rec34_perm: Arr[F64, 4]
    var const169: F64
    var const170: F64
    var const171: F64
    var const172: F64
    var const173: F64
    var const174: F64
    var rec33_perm: Arr[F64, 4]
    var const175: F64
    var const176: F64
    var const177: F64
    var rec32_perm: Arr[F64, 4]
    var const178: F64
    var const179: F64
    var const180: F64
    var rec45_perm: Arr[F64, 4]
    var const181: F64
    var const182: F64
    var const183: F64
    var const184: F64
    var const185: F64
    var const186: F64
    var rec44_perm: Arr[F64, 4]
    var const187: F64
    var const188: F64
    var const189: F64
    var const190: F64
    var const191: F64
    var rec43_perm: Arr[F64, 4]
    var const192: F64
    var const193: F64
    var const194: F64
    var const195: F64
    var const196: F64
    var const197: F64
    var const198: F64
    var const199: F64
    var const200: F64
    var rec42_perm: Arr[F64, 4]
    var const201: F64
    var const202: F64
    var const203: F64
    var const204: F64
    var const205: F64
    var const206: F64
    var rec41_perm: Arr[F64, 4]
    var const207: F64
    var const208: F64
    var const209: F64
    var const210: F64
    var const211: F64
    var const212: F64
    var rec40_perm: Arr[F64, 4]
    var const213: F64
    var const214: F64
    var const215: F64
    var rec39_perm: Arr[F64, 4]
    var const216: F64
    var const217: F64
    var const218: F64
    var rec52_perm: Arr[F64, 4]
    var const219: F64
    var const220: F64
    var const221: F64
    var const222: F64
    var const223: F64
    var const224: F64
    var rec51_perm: Arr[F64, 4]
    var const225: F64
    var const226: F64
    var const227: F64
    var const228: F64
    var const229: F64
    var rec50_perm: Arr[F64, 4]
    var const230: F64
    var const231: F64
    var const232: F64
    var const233: F64
    var const234: F64
    var const235: F64
    var const236: F64
    var const237: F64
    var const238: F64
    var rec49_perm: Arr[F64, 4]
    var const239: F64
    var const240: F64
    var const241: F64
    var const242: F64
    var const243: F64
    var const244: F64
    var rec48_perm: Arr[F64, 4]
    var const245: F64
    var const246: F64
    var const247: F64
    var const248: F64
    var const249: F64
    var const250: F64
    var rec47_perm: Arr[F64, 4]
    var const251: F64
    var const252: F64
    var const253: F64
    var rec46_perm: Arr[F64, 4]
    var const254: F64
    var const255: F64
    var const256: F64
    var rec59_perm: Arr[F64, 4]
    var const257: F64
    var const258: F64
    var const259: F64
    var const260: F64
    var const261: F64
    var const262: F64
    var rec58_perm: Arr[F64, 4]
    var const263: F64
    var const264: F64
    var const265: F64
    var const266: F64
    var const267: F64
    var rec57_perm: Arr[F64, 4]
    var const268: F64
    var const269: F64
    var const270: F64
    var const271: F64
    var const272: F64
    var const273: F64
    var const274: F64
    var const275: F64
    var const276: F64
    var rec56_perm: Arr[F64, 4]
    var const277: F64
    var const278: F64
    var const279: F64
    var const280: F64
    var const281: F64
    var const282: F64
    var rec55_perm: Arr[F64, 4]
    var const283: F64
    var const284: F64
    var const285: F64
    var const286: F64
    var const287: F64
    var const288: F64
    var rec54_perm: Arr[F64, 4]
    var const289: F64
    var const290: F64
    var const291: F64
    var rec53_perm: Arr[F64, 4]
    var const292: F64
    var const293: F64
    var const294: F64
    var rec66_perm: Arr[F64, 4]
    var const295: F64
    var const296: F64
    var const297: F64
    var const298: F64
    var const299: F64
    var const300: F64
    var rec65_perm: Arr[F64, 4]
    var const301: F64
    var const302: F64
    var const303: F64
    var const304: F64
    var const305: F64
    var rec64_perm: Arr[F64, 4]
    var const306: F64
    var const307: F64
    var const308: F64
    var const309: F64
    var const310: F64
    var const311: F64
    var const312: F64
    var const313: F64
    var const314: F64
    var rec63_perm: Arr[F64, 4]
    var const315: F64
    var const316: F64
    var const317: F64
    var const318: F64
    var const319: F64
    var const320: F64
    var rec62_perm: Arr[F64, 4]
    var const321: F64
    var const322: F64
    var const323: F64
    var const324: F64
    var const325: F64
    var const326: F64
    var rec61_perm: Arr[F64, 4]
    var const327: F64
    var const328: F64
    var const329: F64
    var rec60_perm: Arr[F64, 4]
    var const330: F64
    var const331: F64
    var const332: F64
    var rec73_perm: Arr[F64, 4]
    var const333: F64
    var const334: F64
    var const335: F64
    var const336: F64
    var const337: F64
    var const338: F64
    var rec72_perm: Arr[F64, 4]
    var const339: F64
    var const340: F64
    var const341: F64
    var const342: F64
    var const343: F64
    var rec71_perm: Arr[F64, 4]
    var const344: F64
    var const345: F64
    var const346: F64
    var const347: F64
    var const348: F64
    var const349: F64
    var const350: F64
    var const351: F64
    var const352: F64
    var rec70_perm: Arr[F64, 4]
    var const353: F64
    var const354: F64
    var const355: F64
    var const356: F64
    var const357: F64
    var const358: F64
    var rec69_perm: Arr[F64, 4]
    var const359: F64
    var const360: F64
    var const361: F64
    var const362: F64
    var const363: F64
    var const364: F64
    var rec68_perm: Arr[F64, 4]
    var const365: F64
    var const366: F64
    var const367: F64
    var rec67_perm: Arr[F64, 4]
    var const368: F64
    var const369: F64
    var const370: F64
    var rec80_perm: Arr[F64, 4]
    var const371: F64
    var const372: F64
    var const373: F64
    var const374: F64
    var const375: F64
    var const376: F64
    var rec79_perm: Arr[F64, 4]
    var const377: F64
    var const378: F64
    var const379: F64
    var const380: F64
    var const381: F64
    var rec78_perm: Arr[F64, 4]
    var const382: F64
    var const383: F64
    var const384: F64
    var const385: F64
    var const386: F64
    var const387: F64
    var const388: F64
    var const389: F64
    var const390: F64
    var rec77_perm: Arr[F64, 4]
    var const391: F64
    var const392: F64
    var const393: F64
    var const394: F64
    var const395: F64
    var const396: F64
    var rec76_perm: Arr[F64, 4]
    var const397: F64
    var const398: F64
    var const399: F64
    var const400: F64
    var const401: F64
    var const402: F64
    var rec75_perm: Arr[F64, 4]
    var const403: F64
    var const404: F64
    var const405: F64
    var rec74_perm: Arr[F64, 4]
    var const406: F64
    var const407: F64
    var const408: F64
    var rec87_perm: Arr[F64, 4]
    var const409: F64
    var const410: F64
    var const411: F64
    var const412: F64
    var const413: F64
    var const414: F64
    var rec86_perm: Arr[F64, 4]
    var const415: F64
    var const416: F64
    var const417: F64
    var const418: F64
    var const419: F64
    var rec85_perm: Arr[F64, 4]
    var const420: F64
    var const421: F64
    var const422: F64
    var const423: F64
    var const424: F64
    var const425: F64
    var const426: F64
    var const427: F64
    var const428: F64
    var rec84_perm: Arr[F64, 4]
    var const429: F64
    var const430: F64
    var const431: F64
    var const432: F64
    var const433: F64
    var const434: F64
    var rec83_perm: Arr[F64, 4]
    var const435: F64
    var const436: F64
    var const437: F64
    var const438: F64
    var const439: F64
    var const440: F64
    var rec82_perm: Arr[F64, 4]
    var const441: F64
    var const442: F64
    var const443: F64
    var rec81_perm: Arr[F64, 4]
    var const444: F64
    var const445: F64
    var const446: F64
    var rec94_perm: Arr[F64, 4]
    var const447: F64
    var const448: F64
    var const449: F64
    var const450: F64
    var const451: F64
    var const452: F64
    var rec93_perm: Arr[F64, 4]
    var const453: F64
    var const454: F64
    var const455: F64
    var const456: F64
    var const457: F64
    var rec92_perm: Arr[F64, 4]
    var const458: F64
    var const459: F64
    var const460: F64
    var const461: F64
    var const462: F64
    var const463: F64
    var const464: F64
    var const465: F64
    var const466: F64
    var rec91_perm: Arr[F64, 4]
    var const467: F64
    var const468: F64
    var const469: F64
    var const470: F64
    var const471: F64
    var const472: F64
    var rec90_perm: Arr[F64, 4]
    var const473: F64
    var const474: F64
    var const475: F64
    var const476: F64
    var const477: F64
    var const478: F64
    var rec89_perm: Arr[F64, 4]
    var const479: F64
    var const480: F64
    var const481: F64
    var rec88_perm: Arr[F64, 4]
    var const482: F64
    var const483: F64
    var const484: F64
    var rec101_perm: Arr[F64, 4]
    var const485: F64
    var const486: F64
    var const487: F64
    var const488: F64
    var const489: F64
    var const490: F64
    var rec100_perm: Arr[F64, 4]
    var const491: F64
    var const492: F64
    var const493: F64
    var const494: F64
    var const495: F64
    var rec99_perm: Arr[F64, 4]
    var const496: F64
    var const497: F64
    var const498: F64
    var const499: F64
    var const500: F64
    var const501: F64
    var const502: F64
    var const503: F64
    var const504: F64
    var rec98_perm: Arr[F64, 4]
    var const505: F64
    var const506: F64
    var const507: F64
    var const508: F64
    var const509: F64
    var const510: F64
    var rec97_perm: Arr[F64, 4]
    var const511: F64
    var const512: F64
    var const513: F64
    var const514: F64
    var const515: F64
    var const516: F64
    var rec96_perm: Arr[F64, 4]
    var const517: F64
    var const518: F64
    var const519: F64
    var rec95_perm: Arr[F64, 4]
    var const520: F64
    var const521: F64
    var const522: F64
    var rec105_perm: Arr[F64, 4]
    var const523: F64
    var const524: F64
    var const525: F64
    var const526: F64
    var const527: F64
    var const528: F64
    var rec104_perm: Arr[F64, 4]
    var const529: F64
    var const530: F64
    var const531: F64
    var const532: F64
    var const533: F64
    var rec103_perm: Arr[F64, 4]
    var const534: F64
    var const535: F64
    var rec102_perm: Arr[F64, 4]
    var hslider6: FaustFloat
    var vbargraph0: FaustFloat
    var vbargraph1: FaustFloat
    var vbargraph2: FaustFloat
    var vbargraph3: FaustFloat
    var vbargraph4: FaustFloat
    var vbargraph5: FaustFloat
    var vbargraph6: FaustFloat
    var vbargraph7: FaustFloat
    var vbargraph8: FaustFloat
    var vbargraph9: FaustFloat
    var vbargraph10: FaustFloat
    var vbargraph11: FaustFloat
    var vbargraph12: FaustFloat
    var vbargraph13: FaustFloat
    var vbargraph14: FaustFloat

    @always_inline
    def __init__(out dsp):
        dsp.null_val = FaustFloat(0.0)
        dsp.hslider0 = 0.0
        dsp.rec1_perm = Arr[F64, 4](fill=0.0)
        dsp.hslider1 = 0.0
        dsp.rec2_perm = Arr[F64, 4](fill=0.0)
        dsp.hslider2 = 0.0
        dsp.sample_rate = 0
        dsp.const0 = 0.0
        dsp.const1 = 0.0
        dsp.hslider3 = 0.0
        dsp.rec5_perm = Arr[F64, 4](fill=0.0)
        dsp.const2 = 0.0
        dsp.rec3_perm = Arr[F64, 4](fill=0.0)
        dsp.i_vec0_perm = Arr[S32, 4](fill=0)
        dsp.rec4_perm = Arr[F64, 4](fill=0.0)
        dsp.hslider4 = 0.0
        dsp.rec6_perm = Arr[F64, 4](fill=0.0)
        dsp.checkbox0 = 0.0
        dsp.yec0_perm = Arr[F64, 4](fill=0.0)
        dsp.rec0_perm = Arr[F64, 4](fill=0.0)
        dsp.const3 = 0.0
        dsp.const4 = 0.0
        dsp.const5 = 0.0
        dsp.const6 = 0.0
        dsp.const7 = 0.0
        dsp.const8 = 0.0
        dsp.const9 = 0.0
        dsp.rec10_perm = Arr[F64, 4](fill=0.0)
        dsp.const10 = 0.0
        dsp.const11 = 0.0
        dsp.const12 = 0.0
        dsp.const13 = 0.0
        dsp.const14 = 0.0
        dsp.const15 = 0.0
        dsp.rec9_perm = Arr[F64, 4](fill=0.0)
        dsp.const16 = 0.0
        dsp.const17 = 0.0
        dsp.const18 = 0.0
        dsp.const19 = 0.0
        dsp.const20 = 0.0
        dsp.const21 = 0.0
        dsp.rec8_perm = Arr[F64, 4](fill=0.0)
        dsp.hslider5 = 0.0
        dsp.const22 = 0.0
        dsp.const23 = 0.0
        dsp.const24 = 0.0
        dsp.const25 = 0.0
        dsp.rec7_perm = Arr[F64, 4](fill=0.0)
        dsp.const26 = 0.0
        dsp.const27 = 0.0
        dsp.const28 = 0.0
        dsp.rec17_perm = Arr[F64, 4](fill=0.0)
        dsp.const29 = 0.0
        dsp.const30 = 0.0
        dsp.const31 = 0.0
        dsp.const32 = 0.0
        dsp.const33 = 0.0
        dsp.const34 = 0.0
        dsp.rec16_perm = Arr[F64, 4](fill=0.0)
        dsp.const35 = 0.0
        dsp.const36 = 0.0
        dsp.const37 = 0.0
        dsp.const38 = 0.0
        dsp.const39 = 0.0
        dsp.rec15_perm = Arr[F64, 4](fill=0.0)
        dsp.const40 = 0.0
        dsp.const41 = 0.0
        dsp.const42 = 0.0
        dsp.const43 = 0.0
        dsp.const44 = 0.0
        dsp.const45 = 0.0
        dsp.const46 = 0.0
        dsp.const47 = 0.0
        dsp.const48 = 0.0
        dsp.rec14_perm = Arr[F64, 4](fill=0.0)
        dsp.const49 = 0.0
        dsp.const50 = 0.0
        dsp.const51 = 0.0
        dsp.const52 = 0.0
        dsp.const53 = 0.0
        dsp.const54 = 0.0
        dsp.rec13_perm = Arr[F64, 4](fill=0.0)
        dsp.const55 = 0.0
        dsp.const56 = 0.0
        dsp.const57 = 0.0
        dsp.const58 = 0.0
        dsp.const59 = 0.0
        dsp.const60 = 0.0
        dsp.rec12_perm = Arr[F64, 4](fill=0.0)
        dsp.const61 = 0.0
        dsp.const62 = 0.0
        dsp.const63 = 0.0
        dsp.rec11_perm = Arr[F64, 4](fill=0.0)
        dsp.const64 = 0.0
        dsp.const65 = 0.0
        dsp.const66 = 0.0
        dsp.rec24_perm = Arr[F64, 4](fill=0.0)
        dsp.const67 = 0.0
        dsp.const68 = 0.0
        dsp.const69 = 0.0
        dsp.const70 = 0.0
        dsp.const71 = 0.0
        dsp.const72 = 0.0
        dsp.rec23_perm = Arr[F64, 4](fill=0.0)
        dsp.const73 = 0.0
        dsp.const74 = 0.0
        dsp.const75 = 0.0
        dsp.const76 = 0.0
        dsp.const77 = 0.0
        dsp.rec22_perm = Arr[F64, 4](fill=0.0)
        dsp.const78 = 0.0
        dsp.const79 = 0.0
        dsp.const80 = 0.0
        dsp.const81 = 0.0
        dsp.const82 = 0.0
        dsp.const83 = 0.0
        dsp.const84 = 0.0
        dsp.const85 = 0.0
        dsp.const86 = 0.0
        dsp.rec21_perm = Arr[F64, 4](fill=0.0)
        dsp.const87 = 0.0
        dsp.const88 = 0.0
        dsp.const89 = 0.0
        dsp.const90 = 0.0
        dsp.const91 = 0.0
        dsp.const92 = 0.0
        dsp.rec20_perm = Arr[F64, 4](fill=0.0)
        dsp.const93 = 0.0
        dsp.const94 = 0.0
        dsp.const95 = 0.0
        dsp.const96 = 0.0
        dsp.const97 = 0.0
        dsp.const98 = 0.0
        dsp.rec19_perm = Arr[F64, 4](fill=0.0)
        dsp.const99 = 0.0
        dsp.const100 = 0.0
        dsp.const101 = 0.0
        dsp.rec18_perm = Arr[F64, 4](fill=0.0)
        dsp.const102 = 0.0
        dsp.const103 = 0.0
        dsp.const104 = 0.0
        dsp.rec31_perm = Arr[F64, 4](fill=0.0)
        dsp.const105 = 0.0
        dsp.const106 = 0.0
        dsp.const107 = 0.0
        dsp.const108 = 0.0
        dsp.const109 = 0.0
        dsp.const110 = 0.0
        dsp.rec30_perm = Arr[F64, 4](fill=0.0)
        dsp.const111 = 0.0
        dsp.const112 = 0.0
        dsp.const113 = 0.0
        dsp.const114 = 0.0
        dsp.const115 = 0.0
        dsp.rec29_perm = Arr[F64, 4](fill=0.0)
        dsp.const116 = 0.0
        dsp.const117 = 0.0
        dsp.const118 = 0.0
        dsp.const119 = 0.0
        dsp.const120 = 0.0
        dsp.const121 = 0.0
        dsp.const122 = 0.0
        dsp.const123 = 0.0
        dsp.const124 = 0.0
        dsp.rec28_perm = Arr[F64, 4](fill=0.0)
        dsp.const125 = 0.0
        dsp.const126 = 0.0
        dsp.const127 = 0.0
        dsp.const128 = 0.0
        dsp.const129 = 0.0
        dsp.const130 = 0.0
        dsp.rec27_perm = Arr[F64, 4](fill=0.0)
        dsp.const131 = 0.0
        dsp.const132 = 0.0
        dsp.const133 = 0.0
        dsp.const134 = 0.0
        dsp.const135 = 0.0
        dsp.const136 = 0.0
        dsp.rec26_perm = Arr[F64, 4](fill=0.0)
        dsp.const137 = 0.0
        dsp.const138 = 0.0
        dsp.const139 = 0.0
        dsp.rec25_perm = Arr[F64, 4](fill=0.0)
        dsp.const140 = 0.0
        dsp.const141 = 0.0
        dsp.const142 = 0.0
        dsp.rec38_perm = Arr[F64, 4](fill=0.0)
        dsp.const143 = 0.0
        dsp.const144 = 0.0
        dsp.const145 = 0.0
        dsp.const146 = 0.0
        dsp.const147 = 0.0
        dsp.const148 = 0.0
        dsp.rec37_perm = Arr[F64, 4](fill=0.0)
        dsp.const149 = 0.0
        dsp.const150 = 0.0
        dsp.const151 = 0.0
        dsp.const152 = 0.0
        dsp.const153 = 0.0
        dsp.rec36_perm = Arr[F64, 4](fill=0.0)
        dsp.const154 = 0.0
        dsp.const155 = 0.0
        dsp.const156 = 0.0
        dsp.const157 = 0.0
        dsp.const158 = 0.0
        dsp.const159 = 0.0
        dsp.const160 = 0.0
        dsp.const161 = 0.0
        dsp.const162 = 0.0
        dsp.rec35_perm = Arr[F64, 4](fill=0.0)
        dsp.const163 = 0.0
        dsp.const164 = 0.0
        dsp.const165 = 0.0
        dsp.const166 = 0.0
        dsp.const167 = 0.0
        dsp.const168 = 0.0
        dsp.rec34_perm = Arr[F64, 4](fill=0.0)
        dsp.const169 = 0.0
        dsp.const170 = 0.0
        dsp.const171 = 0.0
        dsp.const172 = 0.0
        dsp.const173 = 0.0
        dsp.const174 = 0.0
        dsp.rec33_perm = Arr[F64, 4](fill=0.0)
        dsp.const175 = 0.0
        dsp.const176 = 0.0
        dsp.const177 = 0.0
        dsp.rec32_perm = Arr[F64, 4](fill=0.0)
        dsp.const178 = 0.0
        dsp.const179 = 0.0
        dsp.const180 = 0.0
        dsp.rec45_perm = Arr[F64, 4](fill=0.0)
        dsp.const181 = 0.0
        dsp.const182 = 0.0
        dsp.const183 = 0.0
        dsp.const184 = 0.0
        dsp.const185 = 0.0
        dsp.const186 = 0.0
        dsp.rec44_perm = Arr[F64, 4](fill=0.0)
        dsp.const187 = 0.0
        dsp.const188 = 0.0
        dsp.const189 = 0.0
        dsp.const190 = 0.0
        dsp.const191 = 0.0
        dsp.rec43_perm = Arr[F64, 4](fill=0.0)
        dsp.const192 = 0.0
        dsp.const193 = 0.0
        dsp.const194 = 0.0
        dsp.const195 = 0.0
        dsp.const196 = 0.0
        dsp.const197 = 0.0
        dsp.const198 = 0.0
        dsp.const199 = 0.0
        dsp.const200 = 0.0
        dsp.rec42_perm = Arr[F64, 4](fill=0.0)
        dsp.const201 = 0.0
        dsp.const202 = 0.0
        dsp.const203 = 0.0
        dsp.const204 = 0.0
        dsp.const205 = 0.0
        dsp.const206 = 0.0
        dsp.rec41_perm = Arr[F64, 4](fill=0.0)
        dsp.const207 = 0.0
        dsp.const208 = 0.0
        dsp.const209 = 0.0
        dsp.const210 = 0.0
        dsp.const211 = 0.0
        dsp.const212 = 0.0
        dsp.rec40_perm = Arr[F64, 4](fill=0.0)
        dsp.const213 = 0.0
        dsp.const214 = 0.0
        dsp.const215 = 0.0
        dsp.rec39_perm = Arr[F64, 4](fill=0.0)
        dsp.const216 = 0.0
        dsp.const217 = 0.0
        dsp.const218 = 0.0
        dsp.rec52_perm = Arr[F64, 4](fill=0.0)
        dsp.const219 = 0.0
        dsp.const220 = 0.0
        dsp.const221 = 0.0
        dsp.const222 = 0.0
        dsp.const223 = 0.0
        dsp.const224 = 0.0
        dsp.rec51_perm = Arr[F64, 4](fill=0.0)
        dsp.const225 = 0.0
        dsp.const226 = 0.0
        dsp.const227 = 0.0
        dsp.const228 = 0.0
        dsp.const229 = 0.0
        dsp.rec50_perm = Arr[F64, 4](fill=0.0)
        dsp.const230 = 0.0
        dsp.const231 = 0.0
        dsp.const232 = 0.0
        dsp.const233 = 0.0
        dsp.const234 = 0.0
        dsp.const235 = 0.0
        dsp.const236 = 0.0
        dsp.const237 = 0.0
        dsp.const238 = 0.0
        dsp.rec49_perm = Arr[F64, 4](fill=0.0)
        dsp.const239 = 0.0
        dsp.const240 = 0.0
        dsp.const241 = 0.0
        dsp.const242 = 0.0
        dsp.const243 = 0.0
        dsp.const244 = 0.0
        dsp.rec48_perm = Arr[F64, 4](fill=0.0)
        dsp.const245 = 0.0
        dsp.const246 = 0.0
        dsp.const247 = 0.0
        dsp.const248 = 0.0
        dsp.const249 = 0.0
        dsp.const250 = 0.0
        dsp.rec47_perm = Arr[F64, 4](fill=0.0)
        dsp.const251 = 0.0
        dsp.const252 = 0.0
        dsp.const253 = 0.0
        dsp.rec46_perm = Arr[F64, 4](fill=0.0)
        dsp.const254 = 0.0
        dsp.const255 = 0.0
        dsp.const256 = 0.0
        dsp.rec59_perm = Arr[F64, 4](fill=0.0)
        dsp.const257 = 0.0
        dsp.const258 = 0.0
        dsp.const259 = 0.0
        dsp.const260 = 0.0
        dsp.const261 = 0.0
        dsp.const262 = 0.0
        dsp.rec58_perm = Arr[F64, 4](fill=0.0)
        dsp.const263 = 0.0
        dsp.const264 = 0.0
        dsp.const265 = 0.0
        dsp.const266 = 0.0
        dsp.const267 = 0.0
        dsp.rec57_perm = Arr[F64, 4](fill=0.0)
        dsp.const268 = 0.0
        dsp.const269 = 0.0
        dsp.const270 = 0.0
        dsp.const271 = 0.0
        dsp.const272 = 0.0
        dsp.const273 = 0.0
        dsp.const274 = 0.0
        dsp.const275 = 0.0
        dsp.const276 = 0.0
        dsp.rec56_perm = Arr[F64, 4](fill=0.0)
        dsp.const277 = 0.0
        dsp.const278 = 0.0
        dsp.const279 = 0.0
        dsp.const280 = 0.0
        dsp.const281 = 0.0
        dsp.const282 = 0.0
        dsp.rec55_perm = Arr[F64, 4](fill=0.0)
        dsp.const283 = 0.0
        dsp.const284 = 0.0
        dsp.const285 = 0.0
        dsp.const286 = 0.0
        dsp.const287 = 0.0
        dsp.const288 = 0.0
        dsp.rec54_perm = Arr[F64, 4](fill=0.0)
        dsp.const289 = 0.0
        dsp.const290 = 0.0
        dsp.const291 = 0.0
        dsp.rec53_perm = Arr[F64, 4](fill=0.0)
        dsp.const292 = 0.0
        dsp.const293 = 0.0
        dsp.const294 = 0.0
        dsp.rec66_perm = Arr[F64, 4](fill=0.0)
        dsp.const295 = 0.0
        dsp.const296 = 0.0
        dsp.const297 = 0.0
        dsp.const298 = 0.0
        dsp.const299 = 0.0
        dsp.const300 = 0.0
        dsp.rec65_perm = Arr[F64, 4](fill=0.0)
        dsp.const301 = 0.0
        dsp.const302 = 0.0
        dsp.const303 = 0.0
        dsp.const304 = 0.0
        dsp.const305 = 0.0
        dsp.rec64_perm = Arr[F64, 4](fill=0.0)
        dsp.const306 = 0.0
        dsp.const307 = 0.0
        dsp.const308 = 0.0
        dsp.const309 = 0.0
        dsp.const310 = 0.0
        dsp.const311 = 0.0
        dsp.const312 = 0.0
        dsp.const313 = 0.0
        dsp.const314 = 0.0
        dsp.rec63_perm = Arr[F64, 4](fill=0.0)
        dsp.const315 = 0.0
        dsp.const316 = 0.0
        dsp.const317 = 0.0
        dsp.const318 = 0.0
        dsp.const319 = 0.0
        dsp.const320 = 0.0
        dsp.rec62_perm = Arr[F64, 4](fill=0.0)
        dsp.const321 = 0.0
        dsp.const322 = 0.0
        dsp.const323 = 0.0
        dsp.const324 = 0.0
        dsp.const325 = 0.0
        dsp.const326 = 0.0
        dsp.rec61_perm = Arr[F64, 4](fill=0.0)
        dsp.const327 = 0.0
        dsp.const328 = 0.0
        dsp.const329 = 0.0
        dsp.rec60_perm = Arr[F64, 4](fill=0.0)
        dsp.const330 = 0.0
        dsp.const331 = 0.0
        dsp.const332 = 0.0
        dsp.rec73_perm = Arr[F64, 4](fill=0.0)
        dsp.const333 = 0.0
        dsp.const334 = 0.0
        dsp.const335 = 0.0
        dsp.const336 = 0.0
        dsp.const337 = 0.0
        dsp.const338 = 0.0
        dsp.rec72_perm = Arr[F64, 4](fill=0.0)
        dsp.const339 = 0.0
        dsp.const340 = 0.0
        dsp.const341 = 0.0
        dsp.const342 = 0.0
        dsp.const343 = 0.0
        dsp.rec71_perm = Arr[F64, 4](fill=0.0)
        dsp.const344 = 0.0
        dsp.const345 = 0.0
        dsp.const346 = 0.0
        dsp.const347 = 0.0
        dsp.const348 = 0.0
        dsp.const349 = 0.0
        dsp.const350 = 0.0
        dsp.const351 = 0.0
        dsp.const352 = 0.0
        dsp.rec70_perm = Arr[F64, 4](fill=0.0)
        dsp.const353 = 0.0
        dsp.const354 = 0.0
        dsp.const355 = 0.0
        dsp.const356 = 0.0
        dsp.const357 = 0.0
        dsp.const358 = 0.0
        dsp.rec69_perm = Arr[F64, 4](fill=0.0)
        dsp.const359 = 0.0
        dsp.const360 = 0.0
        dsp.const361 = 0.0
        dsp.const362 = 0.0
        dsp.const363 = 0.0
        dsp.const364 = 0.0
        dsp.rec68_perm = Arr[F64, 4](fill=0.0)
        dsp.const365 = 0.0
        dsp.const366 = 0.0
        dsp.const367 = 0.0
        dsp.rec67_perm = Arr[F64, 4](fill=0.0)
        dsp.const368 = 0.0
        dsp.const369 = 0.0
        dsp.const370 = 0.0
        dsp.rec80_perm = Arr[F64, 4](fill=0.0)
        dsp.const371 = 0.0
        dsp.const372 = 0.0
        dsp.const373 = 0.0
        dsp.const374 = 0.0
        dsp.const375 = 0.0
        dsp.const376 = 0.0
        dsp.rec79_perm = Arr[F64, 4](fill=0.0)
        dsp.const377 = 0.0
        dsp.const378 = 0.0
        dsp.const379 = 0.0
        dsp.const380 = 0.0
        dsp.const381 = 0.0
        dsp.rec78_perm = Arr[F64, 4](fill=0.0)
        dsp.const382 = 0.0
        dsp.const383 = 0.0
        dsp.const384 = 0.0
        dsp.const385 = 0.0
        dsp.const386 = 0.0
        dsp.const387 = 0.0
        dsp.const388 = 0.0
        dsp.const389 = 0.0
        dsp.const390 = 0.0
        dsp.rec77_perm = Arr[F64, 4](fill=0.0)
        dsp.const391 = 0.0
        dsp.const392 = 0.0
        dsp.const393 = 0.0
        dsp.const394 = 0.0
        dsp.const395 = 0.0
        dsp.const396 = 0.0
        dsp.rec76_perm = Arr[F64, 4](fill=0.0)
        dsp.const397 = 0.0
        dsp.const398 = 0.0
        dsp.const399 = 0.0
        dsp.const400 = 0.0
        dsp.const401 = 0.0
        dsp.const402 = 0.0
        dsp.rec75_perm = Arr[F64, 4](fill=0.0)
        dsp.const403 = 0.0
        dsp.const404 = 0.0
        dsp.const405 = 0.0
        dsp.rec74_perm = Arr[F64, 4](fill=0.0)
        dsp.const406 = 0.0
        dsp.const407 = 0.0
        dsp.const408 = 0.0
        dsp.rec87_perm = Arr[F64, 4](fill=0.0)
        dsp.const409 = 0.0
        dsp.const410 = 0.0
        dsp.const411 = 0.0
        dsp.const412 = 0.0
        dsp.const413 = 0.0
        dsp.const414 = 0.0
        dsp.rec86_perm = Arr[F64, 4](fill=0.0)
        dsp.const415 = 0.0
        dsp.const416 = 0.0
        dsp.const417 = 0.0
        dsp.const418 = 0.0
        dsp.const419 = 0.0
        dsp.rec85_perm = Arr[F64, 4](fill=0.0)
        dsp.const420 = 0.0
        dsp.const421 = 0.0
        dsp.const422 = 0.0
        dsp.const423 = 0.0
        dsp.const424 = 0.0
        dsp.const425 = 0.0
        dsp.const426 = 0.0
        dsp.const427 = 0.0
        dsp.const428 = 0.0
        dsp.rec84_perm = Arr[F64, 4](fill=0.0)
        dsp.const429 = 0.0
        dsp.const430 = 0.0
        dsp.const431 = 0.0
        dsp.const432 = 0.0
        dsp.const433 = 0.0
        dsp.const434 = 0.0
        dsp.rec83_perm = Arr[F64, 4](fill=0.0)
        dsp.const435 = 0.0
        dsp.const436 = 0.0
        dsp.const437 = 0.0
        dsp.const438 = 0.0
        dsp.const439 = 0.0
        dsp.const440 = 0.0
        dsp.rec82_perm = Arr[F64, 4](fill=0.0)
        dsp.const441 = 0.0
        dsp.const442 = 0.0
        dsp.const443 = 0.0
        dsp.rec81_perm = Arr[F64, 4](fill=0.0)
        dsp.const444 = 0.0
        dsp.const445 = 0.0
        dsp.const446 = 0.0
        dsp.rec94_perm = Arr[F64, 4](fill=0.0)
        dsp.const447 = 0.0
        dsp.const448 = 0.0
        dsp.const449 = 0.0
        dsp.const450 = 0.0
        dsp.const451 = 0.0
        dsp.const452 = 0.0
        dsp.rec93_perm = Arr[F64, 4](fill=0.0)
        dsp.const453 = 0.0
        dsp.const454 = 0.0
        dsp.const455 = 0.0
        dsp.const456 = 0.0
        dsp.const457 = 0.0
        dsp.rec92_perm = Arr[F64, 4](fill=0.0)
        dsp.const458 = 0.0
        dsp.const459 = 0.0
        dsp.const460 = 0.0
        dsp.const461 = 0.0
        dsp.const462 = 0.0
        dsp.const463 = 0.0
        dsp.const464 = 0.0
        dsp.const465 = 0.0
        dsp.const466 = 0.0
        dsp.rec91_perm = Arr[F64, 4](fill=0.0)
        dsp.const467 = 0.0
        dsp.const468 = 0.0
        dsp.const469 = 0.0
        dsp.const470 = 0.0
        dsp.const471 = 0.0
        dsp.const472 = 0.0
        dsp.rec90_perm = Arr[F64, 4](fill=0.0)
        dsp.const473 = 0.0
        dsp.const474 = 0.0
        dsp.const475 = 0.0
        dsp.const476 = 0.0
        dsp.const477 = 0.0
        dsp.const478 = 0.0
        dsp.rec89_perm = Arr[F64, 4](fill=0.0)
        dsp.const479 = 0.0
        dsp.const480 = 0.0
        dsp.const481 = 0.0
        dsp.rec88_perm = Arr[F64, 4](fill=0.0)
        dsp.const482 = 0.0
        dsp.const483 = 0.0
        dsp.const484 = 0.0
        dsp.rec101_perm = Arr[F64, 4](fill=0.0)
        dsp.const485 = 0.0
        dsp.const486 = 0.0
        dsp.const487 = 0.0
        dsp.const488 = 0.0
        dsp.const489 = 0.0
        dsp.const490 = 0.0
        dsp.rec100_perm = Arr[F64, 4](fill=0.0)
        dsp.const491 = 0.0
        dsp.const492 = 0.0
        dsp.const493 = 0.0
        dsp.const494 = 0.0
        dsp.const495 = 0.0
        dsp.rec99_perm = Arr[F64, 4](fill=0.0)
        dsp.const496 = 0.0
        dsp.const497 = 0.0
        dsp.const498 = 0.0
        dsp.const499 = 0.0
        dsp.const500 = 0.0
        dsp.const501 = 0.0
        dsp.const502 = 0.0
        dsp.const503 = 0.0
        dsp.const504 = 0.0
        dsp.rec98_perm = Arr[F64, 4](fill=0.0)
        dsp.const505 = 0.0
        dsp.const506 = 0.0
        dsp.const507 = 0.0
        dsp.const508 = 0.0
        dsp.const509 = 0.0
        dsp.const510 = 0.0
        dsp.rec97_perm = Arr[F64, 4](fill=0.0)
        dsp.const511 = 0.0
        dsp.const512 = 0.0
        dsp.const513 = 0.0
        dsp.const514 = 0.0
        dsp.const515 = 0.0
        dsp.const516 = 0.0
        dsp.rec96_perm = Arr[F64, 4](fill=0.0)
        dsp.const517 = 0.0
        dsp.const518 = 0.0
        dsp.const519 = 0.0
        dsp.rec95_perm = Arr[F64, 4](fill=0.0)
        dsp.const520 = 0.0
        dsp.const521 = 0.0
        dsp.const522 = 0.0
        dsp.rec105_perm = Arr[F64, 4](fill=0.0)
        dsp.const523 = 0.0
        dsp.const524 = 0.0
        dsp.const525 = 0.0
        dsp.const526 = 0.0
        dsp.const527 = 0.0
        dsp.const528 = 0.0
        dsp.rec104_perm = Arr[F64, 4](fill=0.0)
        dsp.const529 = 0.0
        dsp.const530 = 0.0
        dsp.const531 = 0.0
        dsp.const532 = 0.0
        dsp.const533 = 0.0
        dsp.rec103_perm = Arr[F64, 4](fill=0.0)
        dsp.const534 = 0.0
        dsp.const535 = 0.0
        dsp.rec102_perm = Arr[F64, 4](fill=0.0)
        dsp.hslider6 = 0.0
        dsp.vbargraph0 = 0.0
        dsp.vbargraph1 = 0.0
        dsp.vbargraph2 = 0.0
        dsp.vbargraph3 = 0.0
        dsp.vbargraph4 = 0.0
        dsp.vbargraph5 = 0.0
        dsp.vbargraph6 = 0.0
        dsp.vbargraph7 = 0.0
        dsp.vbargraph8 = 0.0
        dsp.vbargraph9 = 0.0
        dsp.vbargraph10 = 0.0
        dsp.vbargraph11 = 0.0
        dsp.vbargraph12 = 0.0
        dsp.vbargraph13 = 0.0
        dsp.vbargraph14 = 0.0

    @always_inline
    def get_sample_rate(read dsp) -> S32:
        return dsp.sample_rate

    @always_inline
    def get_num_outputs(read dsp) -> S32:
        return 2

    @always_inline
    def get_num_inputs(read dsp) -> S32:
        return 0

    @always_inline
    def class_init(mut dsp, read sample_rate: S32) -> None:
        pass

    @always_inline
    def instance_constants(mut dsp, read sample_rate: S32) -> None:
        dsp.sample_rate = sample_rate
        dsp.const0 = min(1.92e+05, max(1.0, F64(dsp.sample_rate)))
        dsp.const1 = (1.0) / (dsp.const0)
        dsp.const2 = (6.283185307179586) / (dsp.const0)
        dsp.const3 = tan((50265.48245743669) / (dsp.const0))
        dsp.const4 = (1.0) / (dsp.const3)
        dsp.const5 = (1.0) / ((((dsp.const4) + (3.1897274020965583)) / (dsp.const3)) + (4.076781969643807))
        dsp.const6 = (((dsp.const4) + (-3.1897274020965583)) / (dsp.const3)) + (4.076781969643807)
        dsp.const7 = pow_unrolled[2](dsp.const3)
        dsp.const8 = (1.0) / (dsp.const7)
        dsp.const9 = (2.0) * ((4.076781969643807) - (dsp.const8))
        dsp.const10 = (0.0017661728399818856) / (dsp.const7)
        dsp.const11 = (dsp.const10) + (0.00040767818495825777)
        dsp.const12 = (2.0) * ((0.00040767818495825777) - (dsp.const10))
        dsp.const13 = (1.0) / ((((dsp.const4) + (0.7431304601070396)) / (dsp.const3)) + (1.450071084655647))
        dsp.const14 = (((dsp.const4) + (-0.7431304601070396)) / (dsp.const3)) + (1.450071084655647)
        dsp.const15 = (2.0) * ((1.450071084655647) - (dsp.const8))
        dsp.const16 = (11.052052171507189) / (dsp.const7)
        dsp.const17 = (dsp.const16) + (1.450071084655647)
        dsp.const18 = (2.0) * ((1.450071084655647) - (dsp.const16))
        dsp.const19 = (1.0) / ((((dsp.const4) + (0.157482159302087)) / (dsp.const3)) + (0.9351401670315425))
        dsp.const20 = (((dsp.const4) + (-0.157482159302087)) / (dsp.const3)) + (0.9351401670315425)
        dsp.const21 = (2.0) * ((0.9351401670315425) - (dsp.const8))
        dsp.const22 = (1e+03) / (dsp.const0)
        dsp.const23 = (50.063807016150385) / (dsp.const7)
        dsp.const24 = (dsp.const23) + (0.9351401670315425)
        dsp.const25 = (2.0) * ((0.9351401670315425) - (dsp.const23))
        dsp.const26 = (1.0) / ((((dsp.const4) + (0.782413046821645)) / (dsp.const3)) + (0.24529150870616))
        dsp.const27 = (((dsp.const4) + (-0.782413046821645)) / (dsp.const3)) + (0.24529150870616)
        dsp.const28 = (2.0) * ((0.24529150870616) - (dsp.const8))
        dsp.const29 = (9.9999997055e-05) / (dsp.const7)
        dsp.const30 = (dsp.const29) + (0.000433227200555)
        dsp.const31 = (2.0) * ((0.000433227200555) - (dsp.const29))
        dsp.const32 = (1.0) / ((((dsp.const4) + (0.512478641889141)) / (dsp.const3)) + (0.689621364484675))
        dsp.const33 = (((dsp.const4) + (-0.512478641889141)) / (dsp.const3)) + (0.689621364484675)
        dsp.const34 = (2.0) * ((0.689621364484675) - (dsp.const8))
        dsp.const35 = (dsp.const8) + (7.621731298870603)
        dsp.const36 = (2.0) * ((7.621731298870603) - (dsp.const8))
        dsp.const37 = (1.0) / ((((dsp.const4) + (0.168404871113589)) / (dsp.const3)) + (1.069358407707312))
        dsp.const38 = (((dsp.const4) + (-0.168404871113589)) / (dsp.const3)) + (1.069358407707312)
        dsp.const39 = (2.0) * ((1.069358407707312) - (dsp.const8))
        dsp.const40 = (dsp.const8) + (53.53615295455673)
        dsp.const41 = (2.0) * ((53.53615295455673) - (dsp.const8))
        dsp.const42 = tan((31665.269715622984) / (dsp.const0))
        dsp.const43 = (1.0) / (dsp.const42)
        dsp.const44 = (1.0) / ((((dsp.const43) + (3.1897274020965583)) / (dsp.const42)) + (4.076781969643807))
        dsp.const45 = (((dsp.const43) + (-3.1897274020965583)) / (dsp.const42)) + (4.076781969643807)
        dsp.const46 = pow_unrolled[2](dsp.const42)
        dsp.const47 = (1.0) / (dsp.const46)
        dsp.const48 = (2.0) * ((4.076781969643807) - (dsp.const47))
        dsp.const49 = (0.0017661728399818856) / (dsp.const46)
        dsp.const50 = (dsp.const49) + (0.00040767818495825777)
        dsp.const51 = (2.0) * ((0.00040767818495825777) - (dsp.const49))
        dsp.const52 = (1.0) / ((((dsp.const43) + (0.7431304601070396)) / (dsp.const42)) + (1.450071084655647))
        dsp.const53 = (((dsp.const43) + (-0.7431304601070396)) / (dsp.const42)) + (1.450071084655647)
        dsp.const54 = (2.0) * ((1.450071084655647) - (dsp.const47))
        dsp.const55 = (11.052052171507189) / (dsp.const46)
        dsp.const56 = (dsp.const55) + (1.450071084655647)
        dsp.const57 = (2.0) * ((1.450071084655647) - (dsp.const55))
        dsp.const58 = (1.0) / ((((dsp.const43) + (0.157482159302087)) / (dsp.const42)) + (0.9351401670315425))
        dsp.const59 = (((dsp.const43) + (-0.157482159302087)) / (dsp.const42)) + (0.9351401670315425)
        dsp.const60 = (2.0) * ((0.9351401670315425) - (dsp.const47))
        dsp.const61 = (50.063807016150385) / (dsp.const46)
        dsp.const62 = (dsp.const61) + (0.9351401670315425)
        dsp.const63 = (2.0) * ((0.9351401670315425) - (dsp.const61))
        dsp.const64 = (1.0) / ((((dsp.const43) + (0.782413046821645)) / (dsp.const42)) + (0.24529150870616))
        dsp.const65 = (((dsp.const43) + (-0.782413046821645)) / (dsp.const42)) + (0.24529150870616)
        dsp.const66 = (2.0) * ((0.24529150870616) - (dsp.const47))
        dsp.const67 = (9.9999997055e-05) / (dsp.const46)
        dsp.const68 = (dsp.const67) + (0.000433227200555)
        dsp.const69 = (2.0) * ((0.000433227200555) - (dsp.const67))
        dsp.const70 = (1.0) / ((((dsp.const43) + (0.512478641889141)) / (dsp.const42)) + (0.689621364484675))
        dsp.const71 = (((dsp.const43) + (-0.512478641889141)) / (dsp.const42)) + (0.689621364484675)
        dsp.const72 = (2.0) * ((0.689621364484675) - (dsp.const47))
        dsp.const73 = (dsp.const47) + (7.621731298870603)
        dsp.const74 = (2.0) * ((7.621731298870603) - (dsp.const47))
        dsp.const75 = (1.0) / ((((dsp.const43) + (0.168404871113589)) / (dsp.const42)) + (1.069358407707312))
        dsp.const76 = (((dsp.const43) + (-0.168404871113589)) / (dsp.const42)) + (1.069358407707312)
        dsp.const77 = (2.0) * ((1.069358407707312) - (dsp.const47))
        dsp.const78 = (dsp.const47) + (53.53615295455673)
        dsp.const79 = (2.0) * ((53.53615295455673) - (dsp.const47))
        dsp.const80 = tan((19947.869932656024) / (dsp.const0))
        dsp.const81 = (1.0) / (dsp.const80)
        dsp.const82 = (1.0) / ((((dsp.const81) + (3.1897274020965583)) / (dsp.const80)) + (4.076781969643807))
        dsp.const83 = (((dsp.const81) + (-3.1897274020965583)) / (dsp.const80)) + (4.076781969643807)
        dsp.const84 = pow_unrolled[2](dsp.const80)
        dsp.const85 = (1.0) / (dsp.const84)
        dsp.const86 = (2.0) * ((4.076781969643807) - (dsp.const85))
        dsp.const87 = (0.0017661728399818856) / (dsp.const84)
        dsp.const88 = (dsp.const87) + (0.00040767818495825777)
        dsp.const89 = (2.0) * ((0.00040767818495825777) - (dsp.const87))
        dsp.const90 = (1.0) / ((((dsp.const81) + (0.7431304601070396)) / (dsp.const80)) + (1.450071084655647))
        dsp.const91 = (((dsp.const81) + (-0.7431304601070396)) / (dsp.const80)) + (1.450071084655647)
        dsp.const92 = (2.0) * ((1.450071084655647) - (dsp.const85))
        dsp.const93 = (11.052052171507189) / (dsp.const84)
        dsp.const94 = (dsp.const93) + (1.450071084655647)
        dsp.const95 = (2.0) * ((1.450071084655647) - (dsp.const93))
        dsp.const96 = (1.0) / ((((dsp.const81) + (0.157482159302087)) / (dsp.const80)) + (0.9351401670315425))
        dsp.const97 = (((dsp.const81) + (-0.157482159302087)) / (dsp.const80)) + (0.9351401670315425)
        dsp.const98 = (2.0) * ((0.9351401670315425) - (dsp.const85))
        dsp.const99 = (50.063807016150385) / (dsp.const84)
        dsp.const100 = (dsp.const99) + (0.9351401670315425)
        dsp.const101 = (2.0) * ((0.9351401670315425) - (dsp.const99))
        dsp.const102 = (1.0) / ((((dsp.const81) + (0.782413046821645)) / (dsp.const80)) + (0.24529150870616))
        dsp.const103 = (((dsp.const81) + (-0.782413046821645)) / (dsp.const80)) + (0.24529150870616)
        dsp.const104 = (2.0) * ((0.24529150870616) - (dsp.const85))
        dsp.const105 = (9.9999997055e-05) / (dsp.const84)
        dsp.const106 = (dsp.const105) + (0.000433227200555)
        dsp.const107 = (2.0) * ((0.000433227200555) - (dsp.const105))
        dsp.const108 = (1.0) / ((((dsp.const81) + (0.512478641889141)) / (dsp.const80)) + (0.689621364484675))
        dsp.const109 = (((dsp.const81) + (-0.512478641889141)) / (dsp.const80)) + (0.689621364484675)
        dsp.const110 = (2.0) * ((0.689621364484675) - (dsp.const85))
        dsp.const111 = (dsp.const85) + (7.621731298870603)
        dsp.const112 = (2.0) * ((7.621731298870603) - (dsp.const85))
        dsp.const113 = (1.0) / ((((dsp.const81) + (0.168404871113589)) / (dsp.const80)) + (1.069358407707312))
        dsp.const114 = (((dsp.const81) + (-0.168404871113589)) / (dsp.const80)) + (1.069358407707312)
        dsp.const115 = (2.0) * ((1.069358407707312) - (dsp.const85))
        dsp.const116 = (dsp.const85) + (53.53615295455673)
        dsp.const117 = (2.0) * ((53.53615295455673) - (dsp.const85))
        dsp.const118 = tan((12566.370614359172) / (dsp.const0))
        dsp.const119 = (1.0) / (dsp.const118)
        dsp.const120 = (1.0) / ((((dsp.const119) + (3.1897274020965583)) / (dsp.const118)) + (4.076781969643807))
        dsp.const121 = (((dsp.const119) + (-3.1897274020965583)) / (dsp.const118)) + (4.076781969643807)
        dsp.const122 = pow_unrolled[2](dsp.const118)
        dsp.const123 = (1.0) / (dsp.const122)
        dsp.const124 = (2.0) * ((4.076781969643807) - (dsp.const123))
        dsp.const125 = (0.0017661728399818856) / (dsp.const122)
        dsp.const126 = (dsp.const125) + (0.00040767818495825777)
        dsp.const127 = (2.0) * ((0.00040767818495825777) - (dsp.const125))
        dsp.const128 = (1.0) / ((((dsp.const119) + (0.7431304601070396)) / (dsp.const118)) + (1.450071084655647))
        dsp.const129 = (((dsp.const119) + (-0.7431304601070396)) / (dsp.const118)) + (1.450071084655647)
        dsp.const130 = (2.0) * ((1.450071084655647) - (dsp.const123))
        dsp.const131 = (11.052052171507189) / (dsp.const122)
        dsp.const132 = (dsp.const131) + (1.450071084655647)
        dsp.const133 = (2.0) * ((1.450071084655647) - (dsp.const131))
        dsp.const134 = (1.0) / ((((dsp.const119) + (0.157482159302087)) / (dsp.const118)) + (0.9351401670315425))
        dsp.const135 = (((dsp.const119) + (-0.157482159302087)) / (dsp.const118)) + (0.9351401670315425)
        dsp.const136 = (2.0) * ((0.9351401670315425) - (dsp.const123))
        dsp.const137 = (50.063807016150385) / (dsp.const122)
        dsp.const138 = (dsp.const137) + (0.9351401670315425)
        dsp.const139 = (2.0) * ((0.9351401670315425) - (dsp.const137))
        dsp.const140 = (1.0) / ((((dsp.const119) + (0.782413046821645)) / (dsp.const118)) + (0.24529150870616))
        dsp.const141 = (((dsp.const119) + (-0.782413046821645)) / (dsp.const118)) + (0.24529150870616)
        dsp.const142 = (2.0) * ((0.24529150870616) - (dsp.const123))
        dsp.const143 = (9.9999997055e-05) / (dsp.const122)
        dsp.const144 = (dsp.const143) + (0.000433227200555)
        dsp.const145 = (2.0) * ((0.000433227200555) - (dsp.const143))
        dsp.const146 = (1.0) / ((((dsp.const119) + (0.512478641889141)) / (dsp.const118)) + (0.689621364484675))
        dsp.const147 = (((dsp.const119) + (-0.512478641889141)) / (dsp.const118)) + (0.689621364484675)
        dsp.const148 = (2.0) * ((0.689621364484675) - (dsp.const123))
        dsp.const149 = (dsp.const123) + (7.621731298870603)
        dsp.const150 = (2.0) * ((7.621731298870603) - (dsp.const123))
        dsp.const151 = (1.0) / ((((dsp.const119) + (0.168404871113589)) / (dsp.const118)) + (1.069358407707312))
        dsp.const152 = (((dsp.const119) + (-0.168404871113589)) / (dsp.const118)) + (1.069358407707312)
        dsp.const153 = (2.0) * ((1.069358407707312) - (dsp.const123))
        dsp.const154 = (dsp.const123) + (53.53615295455673)
        dsp.const155 = (2.0) * ((53.53615295455673) - (dsp.const123))
        dsp.const156 = tan((7916.317428905746) / (dsp.const0))
        dsp.const157 = (1.0) / (dsp.const156)
        dsp.const158 = (1.0) / ((((dsp.const157) + (3.1897274020965583)) / (dsp.const156)) + (4.076781969643807))
        dsp.const159 = (((dsp.const157) + (-3.1897274020965583)) / (dsp.const156)) + (4.076781969643807)
        dsp.const160 = pow_unrolled[2](dsp.const156)
        dsp.const161 = (1.0) / (dsp.const160)
        dsp.const162 = (2.0) * ((4.076781969643807) - (dsp.const161))
        dsp.const163 = (0.0017661728399818856) / (dsp.const160)
        dsp.const164 = (dsp.const163) + (0.00040767818495825777)
        dsp.const165 = (2.0) * ((0.00040767818495825777) - (dsp.const163))
        dsp.const166 = (1.0) / ((((dsp.const157) + (0.7431304601070396)) / (dsp.const156)) + (1.450071084655647))
        dsp.const167 = (((dsp.const157) + (-0.7431304601070396)) / (dsp.const156)) + (1.450071084655647)
        dsp.const168 = (2.0) * ((1.450071084655647) - (dsp.const161))
        dsp.const169 = (11.052052171507189) / (dsp.const160)
        dsp.const170 = (dsp.const169) + (1.450071084655647)
        dsp.const171 = (2.0) * ((1.450071084655647) - (dsp.const169))
        dsp.const172 = (1.0) / ((((dsp.const157) + (0.157482159302087)) / (dsp.const156)) + (0.9351401670315425))
        dsp.const173 = (((dsp.const157) + (-0.157482159302087)) / (dsp.const156)) + (0.9351401670315425)
        dsp.const174 = (2.0) * ((0.9351401670315425) - (dsp.const161))
        dsp.const175 = (50.063807016150385) / (dsp.const160)
        dsp.const176 = (dsp.const175) + (0.9351401670315425)
        dsp.const177 = (2.0) * ((0.9351401670315425) - (dsp.const175))
        dsp.const178 = (1.0) / ((((dsp.const157) + (0.782413046821645)) / (dsp.const156)) + (0.24529150870616))
        dsp.const179 = (((dsp.const157) + (-0.782413046821645)) / (dsp.const156)) + (0.24529150870616)
        dsp.const180 = (2.0) * ((0.24529150870616) - (dsp.const161))
        dsp.const181 = (9.9999997055e-05) / (dsp.const160)
        dsp.const182 = (dsp.const181) + (0.000433227200555)
        dsp.const183 = (2.0) * ((0.000433227200555) - (dsp.const181))
        dsp.const184 = (1.0) / ((((dsp.const157) + (0.512478641889141)) / (dsp.const156)) + (0.689621364484675))
        dsp.const185 = (((dsp.const157) + (-0.512478641889141)) / (dsp.const156)) + (0.689621364484675)
        dsp.const186 = (2.0) * ((0.689621364484675) - (dsp.const161))
        dsp.const187 = (dsp.const161) + (7.621731298870603)
        dsp.const188 = (2.0) * ((7.621731298870603) - (dsp.const161))
        dsp.const189 = (1.0) / ((((dsp.const157) + (0.168404871113589)) / (dsp.const156)) + (1.069358407707312))
        dsp.const190 = (((dsp.const157) + (-0.168404871113589)) / (dsp.const156)) + (1.069358407707312)
        dsp.const191 = (2.0) * ((1.069358407707312) - (dsp.const161))
        dsp.const192 = (dsp.const161) + (53.53615295455673)
        dsp.const193 = (2.0) * ((53.53615295455673) - (dsp.const161))
        dsp.const194 = tan((4986.967483164005) / (dsp.const0))
        dsp.const195 = (1.0) / (dsp.const194)
        dsp.const196 = (1.0) / ((((dsp.const195) + (3.1897274020965583)) / (dsp.const194)) + (4.076781969643807))
        dsp.const197 = (((dsp.const195) + (-3.1897274020965583)) / (dsp.const194)) + (4.076781969643807)
        dsp.const198 = pow_unrolled[2](dsp.const194)
        dsp.const199 = (1.0) / (dsp.const198)
        dsp.const200 = (2.0) * ((4.076781969643807) - (dsp.const199))
        dsp.const201 = (0.0017661728399818856) / (dsp.const198)
        dsp.const202 = (dsp.const201) + (0.00040767818495825777)
        dsp.const203 = (2.0) * ((0.00040767818495825777) - (dsp.const201))
        dsp.const204 = (1.0) / ((((dsp.const195) + (0.7431304601070396)) / (dsp.const194)) + (1.450071084655647))
        dsp.const205 = (((dsp.const195) + (-0.7431304601070396)) / (dsp.const194)) + (1.450071084655647)
        dsp.const206 = (2.0) * ((1.450071084655647) - (dsp.const199))
        dsp.const207 = (11.052052171507189) / (dsp.const198)
        dsp.const208 = (dsp.const207) + (1.450071084655647)
        dsp.const209 = (2.0) * ((1.450071084655647) - (dsp.const207))
        dsp.const210 = (1.0) / ((((dsp.const195) + (0.157482159302087)) / (dsp.const194)) + (0.9351401670315425))
        dsp.const211 = (((dsp.const195) + (-0.157482159302087)) / (dsp.const194)) + (0.9351401670315425)
        dsp.const212 = (2.0) * ((0.9351401670315425) - (dsp.const199))
        dsp.const213 = (50.063807016150385) / (dsp.const198)
        dsp.const214 = (dsp.const213) + (0.9351401670315425)
        dsp.const215 = (2.0) * ((0.9351401670315425) - (dsp.const213))
        dsp.const216 = (1.0) / ((((dsp.const195) + (0.782413046821645)) / (dsp.const194)) + (0.24529150870616))
        dsp.const217 = (((dsp.const195) + (-0.782413046821645)) / (dsp.const194)) + (0.24529150870616)
        dsp.const218 = (2.0) * ((0.24529150870616) - (dsp.const199))
        dsp.const219 = (9.9999997055e-05) / (dsp.const198)
        dsp.const220 = (dsp.const219) + (0.000433227200555)
        dsp.const221 = (2.0) * ((0.000433227200555) - (dsp.const219))
        dsp.const222 = (1.0) / ((((dsp.const195) + (0.512478641889141)) / (dsp.const194)) + (0.689621364484675))
        dsp.const223 = (((dsp.const195) + (-0.512478641889141)) / (dsp.const194)) + (0.689621364484675)
        dsp.const224 = (2.0) * ((0.689621364484675) - (dsp.const199))
        dsp.const225 = (dsp.const199) + (7.621731298870603)
        dsp.const226 = (2.0) * ((7.621731298870603) - (dsp.const199))
        dsp.const227 = (1.0) / ((((dsp.const195) + (0.168404871113589)) / (dsp.const194)) + (1.069358407707312))
        dsp.const228 = (((dsp.const195) + (-0.168404871113589)) / (dsp.const194)) + (1.069358407707312)
        dsp.const229 = (2.0) * ((1.069358407707312) - (dsp.const199))
        dsp.const230 = (dsp.const199) + (53.53615295455673)
        dsp.const231 = (2.0) * ((53.53615295455673) - (dsp.const199))
        dsp.const232 = tan((3141.592653589793) / (dsp.const0))
        dsp.const233 = (1.0) / (dsp.const232)
        dsp.const234 = (1.0) / ((((dsp.const233) + (3.1897274020965583)) / (dsp.const232)) + (4.076781969643807))
        dsp.const235 = (((dsp.const233) + (-3.1897274020965583)) / (dsp.const232)) + (4.076781969643807)
        dsp.const236 = pow_unrolled[2](dsp.const232)
        dsp.const237 = (1.0) / (dsp.const236)
        dsp.const238 = (2.0) * ((4.076781969643807) - (dsp.const237))
        dsp.const239 = (0.0017661728399818856) / (dsp.const236)
        dsp.const240 = (dsp.const239) + (0.00040767818495825777)
        dsp.const241 = (2.0) * ((0.00040767818495825777) - (dsp.const239))
        dsp.const242 = (1.0) / ((((dsp.const233) + (0.7431304601070396)) / (dsp.const232)) + (1.450071084655647))
        dsp.const243 = (((dsp.const233) + (-0.7431304601070396)) / (dsp.const232)) + (1.450071084655647)
        dsp.const244 = (2.0) * ((1.450071084655647) - (dsp.const237))
        dsp.const245 = (11.052052171507189) / (dsp.const236)
        dsp.const246 = (dsp.const245) + (1.450071084655647)
        dsp.const247 = (2.0) * ((1.450071084655647) - (dsp.const245))
        dsp.const248 = (1.0) / ((((dsp.const233) + (0.157482159302087)) / (dsp.const232)) + (0.9351401670315425))
        dsp.const249 = (((dsp.const233) + (-0.157482159302087)) / (dsp.const232)) + (0.9351401670315425)
        dsp.const250 = (2.0) * ((0.9351401670315425) - (dsp.const237))
        dsp.const251 = (50.063807016150385) / (dsp.const236)
        dsp.const252 = (dsp.const251) + (0.9351401670315425)
        dsp.const253 = (2.0) * ((0.9351401670315425) - (dsp.const251))
        dsp.const254 = (1.0) / ((((dsp.const233) + (0.782413046821645)) / (dsp.const232)) + (0.24529150870616))
        dsp.const255 = (((dsp.const233) + (-0.782413046821645)) / (dsp.const232)) + (0.24529150870616)
        dsp.const256 = (2.0) * ((0.24529150870616) - (dsp.const237))
        dsp.const257 = (9.9999997055e-05) / (dsp.const236)
        dsp.const258 = (dsp.const257) + (0.000433227200555)
        dsp.const259 = (2.0) * ((0.000433227200555) - (dsp.const257))
        dsp.const260 = (1.0) / ((((dsp.const233) + (0.512478641889141)) / (dsp.const232)) + (0.689621364484675))
        dsp.const261 = (((dsp.const233) + (-0.512478641889141)) / (dsp.const232)) + (0.689621364484675)
        dsp.const262 = (2.0) * ((0.689621364484675) - (dsp.const237))
        dsp.const263 = (dsp.const237) + (7.621731298870603)
        dsp.const264 = (2.0) * ((7.621731298870603) - (dsp.const237))
        dsp.const265 = (1.0) / ((((dsp.const233) + (0.168404871113589)) / (dsp.const232)) + (1.069358407707312))
        dsp.const266 = (((dsp.const233) + (-0.168404871113589)) / (dsp.const232)) + (1.069358407707312)
        dsp.const267 = (2.0) * ((1.069358407707312) - (dsp.const237))
        dsp.const268 = (dsp.const237) + (53.53615295455673)
        dsp.const269 = (2.0) * ((53.53615295455673) - (dsp.const237))
        dsp.const270 = tan((1979.079357226436) / (dsp.const0))
        dsp.const271 = (1.0) / (dsp.const270)
        dsp.const272 = (1.0) / ((((dsp.const271) + (3.1897274020965583)) / (dsp.const270)) + (4.076781969643807))
        dsp.const273 = (((dsp.const271) + (-3.1897274020965583)) / (dsp.const270)) + (4.076781969643807)
        dsp.const274 = pow_unrolled[2](dsp.const270)
        dsp.const275 = (1.0) / (dsp.const274)
        dsp.const276 = (2.0) * ((4.076781969643807) - (dsp.const275))
        dsp.const277 = (0.0017661728399818856) / (dsp.const274)
        dsp.const278 = (dsp.const277) + (0.00040767818495825777)
        dsp.const279 = (2.0) * ((0.00040767818495825777) - (dsp.const277))
        dsp.const280 = (1.0) / ((((dsp.const271) + (0.7431304601070396)) / (dsp.const270)) + (1.450071084655647))
        dsp.const281 = (((dsp.const271) + (-0.7431304601070396)) / (dsp.const270)) + (1.450071084655647)
        dsp.const282 = (2.0) * ((1.450071084655647) - (dsp.const275))
        dsp.const283 = (11.052052171507189) / (dsp.const274)
        dsp.const284 = (dsp.const283) + (1.450071084655647)
        dsp.const285 = (2.0) * ((1.450071084655647) - (dsp.const283))
        dsp.const286 = (1.0) / ((((dsp.const271) + (0.157482159302087)) / (dsp.const270)) + (0.9351401670315425))
        dsp.const287 = (((dsp.const271) + (-0.157482159302087)) / (dsp.const270)) + (0.9351401670315425)
        dsp.const288 = (2.0) * ((0.9351401670315425) - (dsp.const275))
        dsp.const289 = (50.063807016150385) / (dsp.const274)
        dsp.const290 = (dsp.const289) + (0.9351401670315425)
        dsp.const291 = (2.0) * ((0.9351401670315425) - (dsp.const289))
        dsp.const292 = (1.0) / ((((dsp.const271) + (0.782413046821645)) / (dsp.const270)) + (0.24529150870616))
        dsp.const293 = (((dsp.const271) + (-0.782413046821645)) / (dsp.const270)) + (0.24529150870616)
        dsp.const294 = (2.0) * ((0.24529150870616) - (dsp.const275))
        dsp.const295 = (9.9999997055e-05) / (dsp.const274)
        dsp.const296 = (dsp.const295) + (0.000433227200555)
        dsp.const297 = (2.0) * ((0.000433227200555) - (dsp.const295))
        dsp.const298 = (1.0) / ((((dsp.const271) + (0.512478641889141)) / (dsp.const270)) + (0.689621364484675))
        dsp.const299 = (((dsp.const271) + (-0.512478641889141)) / (dsp.const270)) + (0.689621364484675)
        dsp.const300 = (2.0) * ((0.689621364484675) - (dsp.const275))
        dsp.const301 = (dsp.const275) + (7.621731298870603)
        dsp.const302 = (2.0) * ((7.621731298870603) - (dsp.const275))
        dsp.const303 = (1.0) / ((((dsp.const271) + (0.168404871113589)) / (dsp.const270)) + (1.069358407707312))
        dsp.const304 = (((dsp.const271) + (-0.168404871113589)) / (dsp.const270)) + (1.069358407707312)
        dsp.const305 = (2.0) * ((1.069358407707312) - (dsp.const275))
        dsp.const306 = (dsp.const275) + (53.53615295455673)
        dsp.const307 = (2.0) * ((53.53615295455673) - (dsp.const275))
        dsp.const308 = tan((1246.7418707910015) / (dsp.const0))
        dsp.const309 = (1.0) / (dsp.const308)
        dsp.const310 = (1.0) / ((((dsp.const309) + (3.1897274020965583)) / (dsp.const308)) + (4.076781969643807))
        dsp.const311 = (((dsp.const309) + (-3.1897274020965583)) / (dsp.const308)) + (4.076781969643807)
        dsp.const312 = pow_unrolled[2](dsp.const308)
        dsp.const313 = (1.0) / (dsp.const312)
        dsp.const314 = (2.0) * ((4.076781969643807) - (dsp.const313))
        dsp.const315 = (0.0017661728399818856) / (dsp.const312)
        dsp.const316 = (dsp.const315) + (0.00040767818495825777)
        dsp.const317 = (2.0) * ((0.00040767818495825777) - (dsp.const315))
        dsp.const318 = (1.0) / ((((dsp.const309) + (0.7431304601070396)) / (dsp.const308)) + (1.450071084655647))
        dsp.const319 = (((dsp.const309) + (-0.7431304601070396)) / (dsp.const308)) + (1.450071084655647)
        dsp.const320 = (2.0) * ((1.450071084655647) - (dsp.const313))
        dsp.const321 = (11.052052171507189) / (dsp.const312)
        dsp.const322 = (dsp.const321) + (1.450071084655647)
        dsp.const323 = (2.0) * ((1.450071084655647) - (dsp.const321))
        dsp.const324 = (1.0) / ((((dsp.const309) + (0.157482159302087)) / (dsp.const308)) + (0.9351401670315425))
        dsp.const325 = (((dsp.const309) + (-0.157482159302087)) / (dsp.const308)) + (0.9351401670315425)
        dsp.const326 = (2.0) * ((0.9351401670315425) - (dsp.const313))
        dsp.const327 = (50.063807016150385) / (dsp.const312)
        dsp.const328 = (dsp.const327) + (0.9351401670315425)
        dsp.const329 = (2.0) * ((0.9351401670315425) - (dsp.const327))
        dsp.const330 = (1.0) / ((((dsp.const309) + (0.782413046821645)) / (dsp.const308)) + (0.24529150870616))
        dsp.const331 = (((dsp.const309) + (-0.782413046821645)) / (dsp.const308)) + (0.24529150870616)
        dsp.const332 = (2.0) * ((0.24529150870616) - (dsp.const313))
        dsp.const333 = (9.9999997055e-05) / (dsp.const312)
        dsp.const334 = (dsp.const333) + (0.000433227200555)
        dsp.const335 = (2.0) * ((0.000433227200555) - (dsp.const333))
        dsp.const336 = (1.0) / ((((dsp.const309) + (0.512478641889141)) / (dsp.const308)) + (0.689621364484675))
        dsp.const337 = (((dsp.const309) + (-0.512478641889141)) / (dsp.const308)) + (0.689621364484675)
        dsp.const338 = (2.0) * ((0.689621364484675) - (dsp.const313))
        dsp.const339 = (dsp.const313) + (7.621731298870603)
        dsp.const340 = (2.0) * ((7.621731298870603) - (dsp.const313))
        dsp.const341 = (1.0) / ((((dsp.const309) + (0.168404871113589)) / (dsp.const308)) + (1.069358407707312))
        dsp.const342 = (((dsp.const309) + (-0.168404871113589)) / (dsp.const308)) + (1.069358407707312)
        dsp.const343 = (2.0) * ((1.069358407707312) - (dsp.const313))
        dsp.const344 = (dsp.const313) + (53.53615295455673)
        dsp.const345 = (2.0) * ((53.53615295455673) - (dsp.const313))
        dsp.const346 = tan((785.3981633974482) / (dsp.const0))
        dsp.const347 = (1.0) / (dsp.const346)
        dsp.const348 = (1.0) / ((((dsp.const347) + (3.1897274020965583)) / (dsp.const346)) + (4.076781969643807))
        dsp.const349 = (((dsp.const347) + (-3.1897274020965583)) / (dsp.const346)) + (4.076781969643807)
        dsp.const350 = pow_unrolled[2](dsp.const346)
        dsp.const351 = (1.0) / (dsp.const350)
        dsp.const352 = (2.0) * ((4.076781969643807) - (dsp.const351))
        dsp.const353 = (0.0017661728399818856) / (dsp.const350)
        dsp.const354 = (dsp.const353) + (0.00040767818495825777)
        dsp.const355 = (2.0) * ((0.00040767818495825777) - (dsp.const353))
        dsp.const356 = (1.0) / ((((dsp.const347) + (0.7431304601070396)) / (dsp.const346)) + (1.450071084655647))
        dsp.const357 = (((dsp.const347) + (-0.7431304601070396)) / (dsp.const346)) + (1.450071084655647)
        dsp.const358 = (2.0) * ((1.450071084655647) - (dsp.const351))
        dsp.const359 = (11.052052171507189) / (dsp.const350)
        dsp.const360 = (dsp.const359) + (1.450071084655647)
        dsp.const361 = (2.0) * ((1.450071084655647) - (dsp.const359))
        dsp.const362 = (1.0) / ((((dsp.const347) + (0.157482159302087)) / (dsp.const346)) + (0.9351401670315425))
        dsp.const363 = (((dsp.const347) + (-0.157482159302087)) / (dsp.const346)) + (0.9351401670315425)
        dsp.const364 = (2.0) * ((0.9351401670315425) - (dsp.const351))
        dsp.const365 = (50.063807016150385) / (dsp.const350)
        dsp.const366 = (dsp.const365) + (0.9351401670315425)
        dsp.const367 = (2.0) * ((0.9351401670315425) - (dsp.const365))
        dsp.const368 = (1.0) / ((((dsp.const347) + (0.782413046821645)) / (dsp.const346)) + (0.24529150870616))
        dsp.const369 = (((dsp.const347) + (-0.782413046821645)) / (dsp.const346)) + (0.24529150870616)
        dsp.const370 = (2.0) * ((0.24529150870616) - (dsp.const351))
        dsp.const371 = (9.9999997055e-05) / (dsp.const350)
        dsp.const372 = (dsp.const371) + (0.000433227200555)
        dsp.const373 = (2.0) * ((0.000433227200555) - (dsp.const371))
        dsp.const374 = (1.0) / ((((dsp.const347) + (0.512478641889141)) / (dsp.const346)) + (0.689621364484675))
        dsp.const375 = (((dsp.const347) + (-0.512478641889141)) / (dsp.const346)) + (0.689621364484675)
        dsp.const376 = (2.0) * ((0.689621364484675) - (dsp.const351))
        dsp.const377 = (dsp.const351) + (7.621731298870603)
        dsp.const378 = (2.0) * ((7.621731298870603) - (dsp.const351))
        dsp.const379 = (1.0) / ((((dsp.const347) + (0.168404871113589)) / (dsp.const346)) + (1.069358407707312))
        dsp.const380 = (((dsp.const347) + (-0.168404871113589)) / (dsp.const346)) + (1.069358407707312)
        dsp.const381 = (2.0) * ((1.069358407707312) - (dsp.const351))
        dsp.const382 = (dsp.const351) + (53.53615295455673)
        dsp.const383 = (2.0) * ((53.53615295455673) - (dsp.const351))
        dsp.const384 = tan((494.769839306609) / (dsp.const0))
        dsp.const385 = (1.0) / (dsp.const384)
        dsp.const386 = (1.0) / ((((dsp.const385) + (3.1897274020965583)) / (dsp.const384)) + (4.076781969643807))
        dsp.const387 = (((dsp.const385) + (-3.1897274020965583)) / (dsp.const384)) + (4.076781969643807)
        dsp.const388 = pow_unrolled[2](dsp.const384)
        dsp.const389 = (1.0) / (dsp.const388)
        dsp.const390 = (2.0) * ((4.076781969643807) - (dsp.const389))
        dsp.const391 = (0.0017661728399818856) / (dsp.const388)
        dsp.const392 = (dsp.const391) + (0.00040767818495825777)
        dsp.const393 = (2.0) * ((0.00040767818495825777) - (dsp.const391))
        dsp.const394 = (1.0) / ((((dsp.const385) + (0.7431304601070396)) / (dsp.const384)) + (1.450071084655647))
        dsp.const395 = (((dsp.const385) + (-0.7431304601070396)) / (dsp.const384)) + (1.450071084655647)
        dsp.const396 = (2.0) * ((1.450071084655647) - (dsp.const389))
        dsp.const397 = (11.052052171507189) / (dsp.const388)
        dsp.const398 = (dsp.const397) + (1.450071084655647)
        dsp.const399 = (2.0) * ((1.450071084655647) - (dsp.const397))
        dsp.const400 = (1.0) / ((((dsp.const385) + (0.157482159302087)) / (dsp.const384)) + (0.9351401670315425))
        dsp.const401 = (((dsp.const385) + (-0.157482159302087)) / (dsp.const384)) + (0.9351401670315425)
        dsp.const402 = (2.0) * ((0.9351401670315425) - (dsp.const389))
        dsp.const403 = (50.063807016150385) / (dsp.const388)
        dsp.const404 = (dsp.const403) + (0.9351401670315425)
        dsp.const405 = (2.0) * ((0.9351401670315425) - (dsp.const403))
        dsp.const406 = (1.0) / ((((dsp.const385) + (0.782413046821645)) / (dsp.const384)) + (0.24529150870616))
        dsp.const407 = (((dsp.const385) + (-0.782413046821645)) / (dsp.const384)) + (0.24529150870616)
        dsp.const408 = (2.0) * ((0.24529150870616) - (dsp.const389))
        dsp.const409 = (9.9999997055e-05) / (dsp.const388)
        dsp.const410 = (dsp.const409) + (0.000433227200555)
        dsp.const411 = (2.0) * ((0.000433227200555) - (dsp.const409))
        dsp.const412 = (1.0) / ((((dsp.const385) + (0.512478641889141)) / (dsp.const384)) + (0.689621364484675))
        dsp.const413 = (((dsp.const385) + (-0.512478641889141)) / (dsp.const384)) + (0.689621364484675)
        dsp.const414 = (2.0) * ((0.689621364484675) - (dsp.const389))
        dsp.const415 = (dsp.const389) + (7.621731298870603)
        dsp.const416 = (2.0) * ((7.621731298870603) - (dsp.const389))
        dsp.const417 = (1.0) / ((((dsp.const385) + (0.168404871113589)) / (dsp.const384)) + (1.069358407707312))
        dsp.const418 = (((dsp.const385) + (-0.168404871113589)) / (dsp.const384)) + (1.069358407707312)
        dsp.const419 = (2.0) * ((1.069358407707312) - (dsp.const389))
        dsp.const420 = (dsp.const389) + (53.53615295455673)
        dsp.const421 = (2.0) * ((53.53615295455673) - (dsp.const389))
        dsp.const422 = tan((311.68546769775037) / (dsp.const0))
        dsp.const423 = (1.0) / (dsp.const422)
        dsp.const424 = (1.0) / ((((dsp.const423) + (3.1897274020965583)) / (dsp.const422)) + (4.076781969643807))
        dsp.const425 = (((dsp.const423) + (-3.1897274020965583)) / (dsp.const422)) + (4.076781969643807)
        dsp.const426 = pow_unrolled[2](dsp.const422)
        dsp.const427 = (1.0) / (dsp.const426)
        dsp.const428 = (2.0) * ((4.076781969643807) - (dsp.const427))
        dsp.const429 = (0.0017661728399818856) / (dsp.const426)
        dsp.const430 = (dsp.const429) + (0.00040767818495825777)
        dsp.const431 = (2.0) * ((0.00040767818495825777) - (dsp.const429))
        dsp.const432 = (1.0) / ((((dsp.const423) + (0.7431304601070396)) / (dsp.const422)) + (1.450071084655647))
        dsp.const433 = (((dsp.const423) + (-0.7431304601070396)) / (dsp.const422)) + (1.450071084655647)
        dsp.const434 = (2.0) * ((1.450071084655647) - (dsp.const427))
        dsp.const435 = (11.052052171507189) / (dsp.const426)
        dsp.const436 = (dsp.const435) + (1.450071084655647)
        dsp.const437 = (2.0) * ((1.450071084655647) - (dsp.const435))
        dsp.const438 = (1.0) / ((((dsp.const423) + (0.157482159302087)) / (dsp.const422)) + (0.9351401670315425))
        dsp.const439 = (((dsp.const423) + (-0.157482159302087)) / (dsp.const422)) + (0.9351401670315425)
        dsp.const440 = (2.0) * ((0.9351401670315425) - (dsp.const427))
        dsp.const441 = (50.063807016150385) / (dsp.const426)
        dsp.const442 = (dsp.const441) + (0.9351401670315425)
        dsp.const443 = (2.0) * ((0.9351401670315425) - (dsp.const441))
        dsp.const444 = (1.0) / ((((dsp.const423) + (0.782413046821645)) / (dsp.const422)) + (0.24529150870616))
        dsp.const445 = (((dsp.const423) + (-0.782413046821645)) / (dsp.const422)) + (0.24529150870616)
        dsp.const446 = (2.0) * ((0.24529150870616) - (dsp.const427))
        dsp.const447 = (9.9999997055e-05) / (dsp.const426)
        dsp.const448 = (dsp.const447) + (0.000433227200555)
        dsp.const449 = (2.0) * ((0.000433227200555) - (dsp.const447))
        dsp.const450 = (1.0) / ((((dsp.const423) + (0.512478641889141)) / (dsp.const422)) + (0.689621364484675))
        dsp.const451 = (((dsp.const423) + (-0.512478641889141)) / (dsp.const422)) + (0.689621364484675)
        dsp.const452 = (2.0) * ((0.689621364484675) - (dsp.const427))
        dsp.const453 = (dsp.const427) + (7.621731298870603)
        dsp.const454 = (2.0) * ((7.621731298870603) - (dsp.const427))
        dsp.const455 = (1.0) / ((((dsp.const423) + (0.168404871113589)) / (dsp.const422)) + (1.069358407707312))
        dsp.const456 = (((dsp.const423) + (-0.168404871113589)) / (dsp.const422)) + (1.069358407707312)
        dsp.const457 = (2.0) * ((1.069358407707312) - (dsp.const427))
        dsp.const458 = (dsp.const427) + (53.53615295455673)
        dsp.const459 = (2.0) * ((53.53615295455673) - (dsp.const427))
        dsp.const460 = tan((196.34954084936206) / (dsp.const0))
        dsp.const461 = (1.0) / (dsp.const460)
        dsp.const462 = (1.0) / ((((dsp.const461) + (3.1897274020965583)) / (dsp.const460)) + (4.076781969643807))
        dsp.const463 = (((dsp.const461) + (-3.1897274020965583)) / (dsp.const460)) + (4.076781969643807)
        dsp.const464 = pow_unrolled[2](dsp.const460)
        dsp.const465 = (1.0) / (dsp.const464)
        dsp.const466 = (2.0) * ((4.076781969643807) - (dsp.const465))
        dsp.const467 = (0.0017661728399818856) / (dsp.const464)
        dsp.const468 = (dsp.const467) + (0.00040767818495825777)
        dsp.const469 = (2.0) * ((0.00040767818495825777) - (dsp.const467))
        dsp.const470 = (1.0) / ((((dsp.const461) + (0.7431304601070396)) / (dsp.const460)) + (1.450071084655647))
        dsp.const471 = (((dsp.const461) + (-0.7431304601070396)) / (dsp.const460)) + (1.450071084655647)
        dsp.const472 = (2.0) * ((1.450071084655647) - (dsp.const465))
        dsp.const473 = (11.052052171507189) / (dsp.const464)
        dsp.const474 = (dsp.const473) + (1.450071084655647)
        dsp.const475 = (2.0) * ((1.450071084655647) - (dsp.const473))
        dsp.const476 = (1.0) / ((((dsp.const461) + (0.157482159302087)) / (dsp.const460)) + (0.9351401670315425))
        dsp.const477 = (((dsp.const461) + (-0.157482159302087)) / (dsp.const460)) + (0.9351401670315425)
        dsp.const478 = (2.0) * ((0.9351401670315425) - (dsp.const465))
        dsp.const479 = (50.063807016150385) / (dsp.const464)
        dsp.const480 = (dsp.const479) + (0.9351401670315425)
        dsp.const481 = (2.0) * ((0.9351401670315425) - (dsp.const479))
        dsp.const482 = (1.0) / ((((dsp.const461) + (0.782413046821645)) / (dsp.const460)) + (0.24529150870616))
        dsp.const483 = (((dsp.const461) + (-0.782413046821645)) / (dsp.const460)) + (0.24529150870616)
        dsp.const484 = (2.0) * ((0.24529150870616) - (dsp.const465))
        dsp.const485 = (9.9999997055e-05) / (dsp.const464)
        dsp.const486 = (dsp.const485) + (0.000433227200555)
        dsp.const487 = (2.0) * ((0.000433227200555) - (dsp.const485))
        dsp.const488 = (1.0) / ((((dsp.const461) + (0.512478641889141)) / (dsp.const460)) + (0.689621364484675))
        dsp.const489 = (((dsp.const461) + (-0.512478641889141)) / (dsp.const460)) + (0.689621364484675)
        dsp.const490 = (2.0) * ((0.689621364484675) - (dsp.const465))
        dsp.const491 = (dsp.const465) + (7.621731298870603)
        dsp.const492 = (2.0) * ((7.621731298870603) - (dsp.const465))
        dsp.const493 = (1.0) / ((((dsp.const461) + (0.168404871113589)) / (dsp.const460)) + (1.069358407707312))
        dsp.const494 = (((dsp.const461) + (-0.168404871113589)) / (dsp.const460)) + (1.069358407707312)
        dsp.const495 = (2.0) * ((1.069358407707312) - (dsp.const465))
        dsp.const496 = (dsp.const465) + (53.53615295455673)
        dsp.const497 = (2.0) * ((53.53615295455673) - (dsp.const465))
        dsp.const498 = tan((123.69245982665232) / (dsp.const0))
        dsp.const499 = (1.0) / (dsp.const498)
        dsp.const500 = (1.0) / ((((dsp.const499) + (3.1897274020965583)) / (dsp.const498)) + (4.076781969643807))
        dsp.const501 = (((dsp.const499) + (-3.1897274020965583)) / (dsp.const498)) + (4.076781969643807)
        dsp.const502 = pow_unrolled[2](dsp.const498)
        dsp.const503 = (1.0) / (dsp.const502)
        dsp.const504 = (2.0) * ((4.076781969643807) - (dsp.const503))
        dsp.const505 = (0.0017661728399818856) / (dsp.const502)
        dsp.const506 = (dsp.const505) + (0.00040767818495825777)
        dsp.const507 = (2.0) * ((0.00040767818495825777) - (dsp.const505))
        dsp.const508 = (1.0) / ((((dsp.const499) + (0.7431304601070396)) / (dsp.const498)) + (1.450071084655647))
        dsp.const509 = (((dsp.const499) + (-0.7431304601070396)) / (dsp.const498)) + (1.450071084655647)
        dsp.const510 = (2.0) * ((1.450071084655647) - (dsp.const503))
        dsp.const511 = (11.052052171507189) / (dsp.const502)
        dsp.const512 = (dsp.const511) + (1.450071084655647)
        dsp.const513 = (2.0) * ((1.450071084655647) - (dsp.const511))
        dsp.const514 = (1.0) / ((((dsp.const499) + (0.157482159302087)) / (dsp.const498)) + (0.9351401670315425))
        dsp.const515 = (((dsp.const499) + (-0.157482159302087)) / (dsp.const498)) + (0.9351401670315425)
        dsp.const516 = (2.0) * ((0.9351401670315425) - (dsp.const503))
        dsp.const517 = (50.063807016150385) / (dsp.const502)
        dsp.const518 = (dsp.const517) + (0.9351401670315425)
        dsp.const519 = (2.0) * ((0.9351401670315425) - (dsp.const517))
        dsp.const520 = (1.0) / ((((dsp.const499) + (0.782413046821645)) / (dsp.const498)) + (0.24529150870616))
        dsp.const521 = (((dsp.const499) + (-0.782413046821645)) / (dsp.const498)) + (0.24529150870616)
        dsp.const522 = (2.0) * ((0.24529150870616) - (dsp.const503))
        dsp.const523 = (9.9999997055e-05) / (dsp.const502)
        dsp.const524 = (dsp.const523) + (0.000433227200555)
        dsp.const525 = (2.0) * ((0.000433227200555) - (dsp.const523))
        dsp.const526 = (1.0) / ((((dsp.const499) + (0.512478641889141)) / (dsp.const498)) + (0.689621364484675))
        dsp.const527 = (((dsp.const499) + (-0.512478641889141)) / (dsp.const498)) + (0.689621364484675)
        dsp.const528 = (2.0) * ((0.689621364484675) - (dsp.const503))
        dsp.const529 = (dsp.const503) + (7.621731298870603)
        dsp.const530 = (2.0) * ((7.621731298870603) - (dsp.const503))
        dsp.const531 = (1.0) / ((((dsp.const499) + (0.168404871113589)) / (dsp.const498)) + (1.069358407707312))
        dsp.const532 = (((dsp.const499) + (-0.168404871113589)) / (dsp.const498)) + (1.069358407707312)
        dsp.const533 = (2.0) * ((1.069358407707312) - (dsp.const503))
        dsp.const534 = (dsp.const503) + (53.53615295455673)
        dsp.const535 = (2.0) * ((53.53615295455673) - (dsp.const503))

    @always_inline
    def instance_reset_user_interface(mut dsp) -> None:
        dsp.hslider0 = 0.0
        dsp.hslider1 = -20.0
        dsp.hslider2 = 0.1
        dsp.hslider3 = 49.0
        dsp.hslider4 = 0.0
        dsp.checkbox0 = 0.0
        dsp.hslider5 = 100.0
        dsp.hslider6 = 50.0

    @always_inline
    def instance_clear(mut dsp) -> None:
        var l0 = S32(0)
        while (l0) < (S32(4)): 
            dsp.rec1_perm[l0] = 0.0
            l0 = (l0) + (S32(1))
        var l1 = S32(0)
        while (l1) < (S32(4)): 
            dsp.rec2_perm[l1] = 0.0
            l1 = (l1) + (S32(1))
        var l2 = S32(0)
        while (l2) < (S32(4)): 
            dsp.rec5_perm[l2] = 0.0
            l2 = (l2) + (S32(1))
        var l3 = S32(0)
        while (l3) < (S32(4)): 
            dsp.rec3_perm[l3] = 0.0
            l3 = (l3) + (S32(1))
        var l4 = S32(0)
        while (l4) < (S32(4)): 
            dsp.i_vec0_perm[l4] = S32(0)
            l4 = (l4) + (S32(1))
        var l5 = S32(0)
        while (l5) < (S32(4)): 
            dsp.rec4_perm[l5] = 0.0
            l5 = (l5) + (S32(1))
        var l6 = S32(0)
        while (l6) < (S32(4)): 
            dsp.rec6_perm[l6] = 0.0
            l6 = (l6) + (S32(1))
        var l7 = S32(0)
        while (l7) < (S32(4)): 
            dsp.yec0_perm[l7] = 0.0
            l7 = (l7) + (S32(1))
        var l8 = S32(0)
        while (l8) < (S32(4)): 
            dsp.rec0_perm[l8] = 0.0
            l8 = (l8) + (S32(1))
        var l9 = S32(0)
        while (l9) < (S32(4)): 
            dsp.rec10_perm[l9] = 0.0
            l9 = (l9) + (S32(1))
        var l10 = S32(0)
        while (l10) < (S32(4)): 
            dsp.rec9_perm[l10] = 0.0
            l10 = (l10) + (S32(1))
        var l11 = S32(0)
        while (l11) < (S32(4)): 
            dsp.rec8_perm[l11] = 0.0
            l11 = (l11) + (S32(1))
        var l12 = S32(0)
        while (l12) < (S32(4)): 
            dsp.rec7_perm[l12] = 0.0
            l12 = (l12) + (S32(1))
        var l13 = S32(0)
        while (l13) < (S32(4)): 
            dsp.rec17_perm[l13] = 0.0
            l13 = (l13) + (S32(1))
        var l14 = S32(0)
        while (l14) < (S32(4)): 
            dsp.rec16_perm[l14] = 0.0
            l14 = (l14) + (S32(1))
        var l15 = S32(0)
        while (l15) < (S32(4)): 
            dsp.rec15_perm[l15] = 0.0
            l15 = (l15) + (S32(1))
        var l16 = S32(0)
        while (l16) < (S32(4)): 
            dsp.rec14_perm[l16] = 0.0
            l16 = (l16) + (S32(1))
        var l17 = S32(0)
        while (l17) < (S32(4)): 
            dsp.rec13_perm[l17] = 0.0
            l17 = (l17) + (S32(1))
        var l18 = S32(0)
        while (l18) < (S32(4)): 
            dsp.rec12_perm[l18] = 0.0
            l18 = (l18) + (S32(1))
        var l19 = S32(0)
        while (l19) < (S32(4)): 
            dsp.rec11_perm[l19] = 0.0
            l19 = (l19) + (S32(1))
        var l20 = S32(0)
        while (l20) < (S32(4)): 
            dsp.rec24_perm[l20] = 0.0
            l20 = (l20) + (S32(1))
        var l21 = S32(0)
        while (l21) < (S32(4)): 
            dsp.rec23_perm[l21] = 0.0
            l21 = (l21) + (S32(1))
        var l22 = S32(0)
        while (l22) < (S32(4)): 
            dsp.rec22_perm[l22] = 0.0
            l22 = (l22) + (S32(1))
        var l23 = S32(0)
        while (l23) < (S32(4)): 
            dsp.rec21_perm[l23] = 0.0
            l23 = (l23) + (S32(1))
        var l24 = S32(0)
        while (l24) < (S32(4)): 
            dsp.rec20_perm[l24] = 0.0
            l24 = (l24) + (S32(1))
        var l25 = S32(0)
        while (l25) < (S32(4)): 
            dsp.rec19_perm[l25] = 0.0
            l25 = (l25) + (S32(1))
        var l26 = S32(0)
        while (l26) < (S32(4)): 
            dsp.rec18_perm[l26] = 0.0
            l26 = (l26) + (S32(1))
        var l27 = S32(0)
        while (l27) < (S32(4)): 
            dsp.rec31_perm[l27] = 0.0
            l27 = (l27) + (S32(1))
        var l28 = S32(0)
        while (l28) < (S32(4)): 
            dsp.rec30_perm[l28] = 0.0
            l28 = (l28) + (S32(1))
        var l29 = S32(0)
        while (l29) < (S32(4)): 
            dsp.rec29_perm[l29] = 0.0
            l29 = (l29) + (S32(1))
        var l30 = S32(0)
        while (l30) < (S32(4)): 
            dsp.rec28_perm[l30] = 0.0
            l30 = (l30) + (S32(1))
        var l31 = S32(0)
        while (l31) < (S32(4)): 
            dsp.rec27_perm[l31] = 0.0
            l31 = (l31) + (S32(1))
        var l32 = S32(0)
        while (l32) < (S32(4)): 
            dsp.rec26_perm[l32] = 0.0
            l32 = (l32) + (S32(1))
        var l33 = S32(0)
        while (l33) < (S32(4)): 
            dsp.rec25_perm[l33] = 0.0
            l33 = (l33) + (S32(1))
        var l34 = S32(0)
        while (l34) < (S32(4)): 
            dsp.rec38_perm[l34] = 0.0
            l34 = (l34) + (S32(1))
        var l35 = S32(0)
        while (l35) < (S32(4)): 
            dsp.rec37_perm[l35] = 0.0
            l35 = (l35) + (S32(1))
        var l36 = S32(0)
        while (l36) < (S32(4)): 
            dsp.rec36_perm[l36] = 0.0
            l36 = (l36) + (S32(1))
        var l37 = S32(0)
        while (l37) < (S32(4)): 
            dsp.rec35_perm[l37] = 0.0
            l37 = (l37) + (S32(1))
        var l38 = S32(0)
        while (l38) < (S32(4)): 
            dsp.rec34_perm[l38] = 0.0
            l38 = (l38) + (S32(1))
        var l39 = S32(0)
        while (l39) < (S32(4)): 
            dsp.rec33_perm[l39] = 0.0
            l39 = (l39) + (S32(1))
        var l40 = S32(0)
        while (l40) < (S32(4)): 
            dsp.rec32_perm[l40] = 0.0
            l40 = (l40) + (S32(1))
        var l41 = S32(0)
        while (l41) < (S32(4)): 
            dsp.rec45_perm[l41] = 0.0
            l41 = (l41) + (S32(1))
        var l42 = S32(0)
        while (l42) < (S32(4)): 
            dsp.rec44_perm[l42] = 0.0
            l42 = (l42) + (S32(1))
        var l43 = S32(0)
        while (l43) < (S32(4)): 
            dsp.rec43_perm[l43] = 0.0
            l43 = (l43) + (S32(1))
        var l44 = S32(0)
        while (l44) < (S32(4)): 
            dsp.rec42_perm[l44] = 0.0
            l44 = (l44) + (S32(1))
        var l45 = S32(0)
        while (l45) < (S32(4)): 
            dsp.rec41_perm[l45] = 0.0
            l45 = (l45) + (S32(1))
        var l46 = S32(0)
        while (l46) < (S32(4)): 
            dsp.rec40_perm[l46] = 0.0
            l46 = (l46) + (S32(1))
        var l47 = S32(0)
        while (l47) < (S32(4)): 
            dsp.rec39_perm[l47] = 0.0
            l47 = (l47) + (S32(1))
        var l48 = S32(0)
        while (l48) < (S32(4)): 
            dsp.rec52_perm[l48] = 0.0
            l48 = (l48) + (S32(1))
        var l49 = S32(0)
        while (l49) < (S32(4)): 
            dsp.rec51_perm[l49] = 0.0
            l49 = (l49) + (S32(1))
        var l50 = S32(0)
        while (l50) < (S32(4)): 
            dsp.rec50_perm[l50] = 0.0
            l50 = (l50) + (S32(1))
        var l51 = S32(0)
        while (l51) < (S32(4)): 
            dsp.rec49_perm[l51] = 0.0
            l51 = (l51) + (S32(1))
        var l52 = S32(0)
        while (l52) < (S32(4)): 
            dsp.rec48_perm[l52] = 0.0
            l52 = (l52) + (S32(1))
        var l53 = S32(0)
        while (l53) < (S32(4)): 
            dsp.rec47_perm[l53] = 0.0
            l53 = (l53) + (S32(1))
        var l54 = S32(0)
        while (l54) < (S32(4)): 
            dsp.rec46_perm[l54] = 0.0
            l54 = (l54) + (S32(1))
        var l55 = S32(0)
        while (l55) < (S32(4)): 
            dsp.rec59_perm[l55] = 0.0
            l55 = (l55) + (S32(1))
        var l56 = S32(0)
        while (l56) < (S32(4)): 
            dsp.rec58_perm[l56] = 0.0
            l56 = (l56) + (S32(1))
        var l57 = S32(0)
        while (l57) < (S32(4)): 
            dsp.rec57_perm[l57] = 0.0
            l57 = (l57) + (S32(1))
        var l58 = S32(0)
        while (l58) < (S32(4)): 
            dsp.rec56_perm[l58] = 0.0
            l58 = (l58) + (S32(1))
        var l59 = S32(0)
        while (l59) < (S32(4)): 
            dsp.rec55_perm[l59] = 0.0
            l59 = (l59) + (S32(1))
        var l60 = S32(0)
        while (l60) < (S32(4)): 
            dsp.rec54_perm[l60] = 0.0
            l60 = (l60) + (S32(1))
        var l61 = S32(0)
        while (l61) < (S32(4)): 
            dsp.rec53_perm[l61] = 0.0
            l61 = (l61) + (S32(1))
        var l62 = S32(0)
        while (l62) < (S32(4)): 
            dsp.rec66_perm[l62] = 0.0
            l62 = (l62) + (S32(1))
        var l63 = S32(0)
        while (l63) < (S32(4)): 
            dsp.rec65_perm[l63] = 0.0
            l63 = (l63) + (S32(1))
        var l64 = S32(0)
        while (l64) < (S32(4)): 
            dsp.rec64_perm[l64] = 0.0
            l64 = (l64) + (S32(1))
        var l65 = S32(0)
        while (l65) < (S32(4)): 
            dsp.rec63_perm[l65] = 0.0
            l65 = (l65) + (S32(1))
        var l66 = S32(0)
        while (l66) < (S32(4)): 
            dsp.rec62_perm[l66] = 0.0
            l66 = (l66) + (S32(1))
        var l67 = S32(0)
        while (l67) < (S32(4)): 
            dsp.rec61_perm[l67] = 0.0
            l67 = (l67) + (S32(1))
        var l68 = S32(0)
        while (l68) < (S32(4)): 
            dsp.rec60_perm[l68] = 0.0
            l68 = (l68) + (S32(1))
        var l69 = S32(0)
        while (l69) < (S32(4)): 
            dsp.rec73_perm[l69] = 0.0
            l69 = (l69) + (S32(1))
        var l70 = S32(0)
        while (l70) < (S32(4)): 
            dsp.rec72_perm[l70] = 0.0
            l70 = (l70) + (S32(1))
        var l71 = S32(0)
        while (l71) < (S32(4)): 
            dsp.rec71_perm[l71] = 0.0
            l71 = (l71) + (S32(1))
        var l72 = S32(0)
        while (l72) < (S32(4)): 
            dsp.rec70_perm[l72] = 0.0
            l72 = (l72) + (S32(1))
        var l73 = S32(0)
        while (l73) < (S32(4)): 
            dsp.rec69_perm[l73] = 0.0
            l73 = (l73) + (S32(1))
        var l74 = S32(0)
        while (l74) < (S32(4)): 
            dsp.rec68_perm[l74] = 0.0
            l74 = (l74) + (S32(1))
        var l75 = S32(0)
        while (l75) < (S32(4)): 
            dsp.rec67_perm[l75] = 0.0
            l75 = (l75) + (S32(1))
        var l76 = S32(0)
        while (l76) < (S32(4)): 
            dsp.rec80_perm[l76] = 0.0
            l76 = (l76) + (S32(1))
        var l77 = S32(0)
        while (l77) < (S32(4)): 
            dsp.rec79_perm[l77] = 0.0
            l77 = (l77) + (S32(1))
        var l78 = S32(0)
        while (l78) < (S32(4)): 
            dsp.rec78_perm[l78] = 0.0
            l78 = (l78) + (S32(1))
        var l79 = S32(0)
        while (l79) < (S32(4)): 
            dsp.rec77_perm[l79] = 0.0
            l79 = (l79) + (S32(1))
        var l80 = S32(0)
        while (l80) < (S32(4)): 
            dsp.rec76_perm[l80] = 0.0
            l80 = (l80) + (S32(1))
        var l81 = S32(0)
        while (l81) < (S32(4)): 
            dsp.rec75_perm[l81] = 0.0
            l81 = (l81) + (S32(1))
        var l82 = S32(0)
        while (l82) < (S32(4)): 
            dsp.rec74_perm[l82] = 0.0
            l82 = (l82) + (S32(1))
        var l83 = S32(0)
        while (l83) < (S32(4)): 
            dsp.rec87_perm[l83] = 0.0
            l83 = (l83) + (S32(1))
        var l84 = S32(0)
        while (l84) < (S32(4)): 
            dsp.rec86_perm[l84] = 0.0
            l84 = (l84) + (S32(1))
        var l85 = S32(0)
        while (l85) < (S32(4)): 
            dsp.rec85_perm[l85] = 0.0
            l85 = (l85) + (S32(1))
        var l86 = S32(0)
        while (l86) < (S32(4)): 
            dsp.rec84_perm[l86] = 0.0
            l86 = (l86) + (S32(1))
        var l87 = S32(0)
        while (l87) < (S32(4)): 
            dsp.rec83_perm[l87] = 0.0
            l87 = (l87) + (S32(1))
        var l88 = S32(0)
        while (l88) < (S32(4)): 
            dsp.rec82_perm[l88] = 0.0
            l88 = (l88) + (S32(1))
        var l89 = S32(0)
        while (l89) < (S32(4)): 
            dsp.rec81_perm[l89] = 0.0
            l89 = (l89) + (S32(1))
        var l90 = S32(0)
        while (l90) < (S32(4)): 
            dsp.rec94_perm[l90] = 0.0
            l90 = (l90) + (S32(1))
        var l91 = S32(0)
        while (l91) < (S32(4)): 
            dsp.rec93_perm[l91] = 0.0
            l91 = (l91) + (S32(1))
        var l92 = S32(0)
        while (l92) < (S32(4)): 
            dsp.rec92_perm[l92] = 0.0
            l92 = (l92) + (S32(1))
        var l93 = S32(0)
        while (l93) < (S32(4)): 
            dsp.rec91_perm[l93] = 0.0
            l93 = (l93) + (S32(1))
        var l94 = S32(0)
        while (l94) < (S32(4)): 
            dsp.rec90_perm[l94] = 0.0
            l94 = (l94) + (S32(1))
        var l95 = S32(0)
        while (l95) < (S32(4)): 
            dsp.rec89_perm[l95] = 0.0
            l95 = (l95) + (S32(1))
        var l96 = S32(0)
        while (l96) < (S32(4)): 
            dsp.rec88_perm[l96] = 0.0
            l96 = (l96) + (S32(1))
        var l97 = S32(0)
        while (l97) < (S32(4)): 
            dsp.rec101_perm[l97] = 0.0
            l97 = (l97) + (S32(1))
        var l98 = S32(0)
        while (l98) < (S32(4)): 
            dsp.rec100_perm[l98] = 0.0
            l98 = (l98) + (S32(1))
        var l99 = S32(0)
        while (l99) < (S32(4)): 
            dsp.rec99_perm[l99] = 0.0
            l99 = (l99) + (S32(1))
        var l100 = S32(0)
        while (l100) < (S32(4)): 
            dsp.rec98_perm[l100] = 0.0
            l100 = (l100) + (S32(1))
        var l101 = S32(0)
        while (l101) < (S32(4)): 
            dsp.rec97_perm[l101] = 0.0
            l101 = (l101) + (S32(1))
        var l102 = S32(0)
        while (l102) < (S32(4)): 
            dsp.rec96_perm[l102] = 0.0
            l102 = (l102) + (S32(1))
        var l103 = S32(0)
        while (l103) < (S32(4)): 
            dsp.rec95_perm[l103] = 0.0
            l103 = (l103) + (S32(1))
        var l104 = S32(0)
        while (l104) < (S32(4)): 
            dsp.rec105_perm[l104] = 0.0
            l104 = (l104) + (S32(1))
        var l105 = S32(0)
        while (l105) < (S32(4)): 
            dsp.rec104_perm[l105] = 0.0
            l105 = (l105) + (S32(1))
        var l106 = S32(0)
        while (l106) < (S32(4)): 
            dsp.rec103_perm[l106] = 0.0
            l106 = (l106) + (S32(1))
        var l107 = S32(0)
        while (l107) < (S32(4)): 
            dsp.rec102_perm[l107] = 0.0
            l107 = (l107) + (S32(1))

    @always_inline
    def instance_init(mut dsp, read sample_rate: S32) -> None:
        dsp.instance_constants(sample_rate)
        dsp.instance_reset_user_interface()
        dsp.instance_clear()

    @always_inline
    def init(mut dsp, read sample_rate: S32) -> None:
        dsp.class_init(sample_rate)
        dsp.instance_init(sample_rate)

    @always_inline
    def get_json(read dsp) -> String:
        return "{\"name\": \"cubic_distortion\",\"filename\": \"cubic_distortion.dsp\",\"version\": \"2.85.5\",\"compile_options\": \"-a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs\",\"library_list\": [\"/usr/local/share/faust/oscillator.lib\",\"/usr/local/share/faust/music.lib\",\"/usr/local/share/faust/math.lib\",\"/usr/local/share/faust/filter.lib\",\"/usr/local/share/faust/effect.lib\"],\"include_pathnames\": [\"/Users/manuelfarzini/Personal/dev/repo/faust/build/share/faust\",\"/usr/local/share/faust\",\"/usr/share/faust\",\"/Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/dsp\",\"/Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/dsp\"],\"size\": 7916,\"inputs\": 0,\"outputs\": 2,\"meta\": [ { \"compile_options\": \"-a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs\" },{ \"effect.lib/author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"effect.lib/copyright\": \"Julius O. Smith III\" },{ \"effect.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"effect.lib/exciter_author\": \"Priyanka Shekar (pshekar@ccrma.stanford.edu)\" },{ \"effect.lib/exciter_copyright\": \"Copyright (c) 2013 Priyanka Shekar\" },{ \"effect.lib/exciter_license\": \"MIT License (MIT)\" },{ \"effect.lib/exciter_name\": \"Harmonic Exciter\" },{ \"effect.lib/exciter_version\": \"1.0\" },{ \"effect.lib/license\": \"STK-4.3\" },{ \"effect.lib/name\": \"Faust Audio Effect Library\" },{ \"effect.lib/version\": \"1.33\" },{ \"filename\": \"cubic_distortion.dsp\" },{ \"filter.lib/author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"filter.lib/copyright\": \"Julius O. Smith III\" },{ \"filter.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"filter.lib/license\": \"STK-4.3\" },{ \"filter.lib/name\": \"Faust Filter Library\" },{ \"filter.lib/reference\": \"https://ccrma.stanford.edu/~jos/filters/\" },{ \"filter.lib/version\": \"1.29\" },{ \"math.lib/author\": \"GRAME\" },{ \"math.lib/copyright\": \"GRAME\" },{ \"math.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"math.lib/license\": \"LGPL with exception\" },{ \"math.lib/name\": \"Math Library\" },{ \"math.lib/version\": \"1.0\" },{ \"music.lib/author\": \"GRAME\" },{ \"music.lib/copyright\": \"GRAME\" },{ \"music.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"music.lib/license\": \"LGPL with exception\" },{ \"music.lib/name\": \"Music Library\" },{ \"music.lib/version\": \"1.0\" },{ \"name\": \"cubic_distortion\" },{ \"oscillator.lib/author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"oscillator.lib/copyright\": \"Julius O. Smith III\" },{ \"oscillator.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"oscillator.lib/license\": \"STK-4.3\" },{ \"oscillator.lib/name\": \"Faust Oscillator Library\" },{ \"oscillator.lib/version\": \"1.11\" }],\"ui\": [ {\"type\": \"vgroup\",\"label\": \"cubic_distortion\",\"items\": [ {\"type\": \"vgroup\",\"label\": \"0x00\",\"meta\": [{ \"1\": \"\" }],\"items\": [ {\"type\": \"vgroup\",\"label\": \"SINE WAVE OSCILLATOR oscrs\",\"meta\": [{ \"0\": \"\" },{ \"tooltip\": \"Sine oscillator based on 2D vector rotation\" }],\"items\": [ {\"type\": \"hslider\",\"label\": \"Amplitude\",\"varname\": \"fHslider1\",\"shortname\": \"Amplitude\",\"address\": \"/cubic_distortion/0x00/SINE_WAVE_OSCILLATOR_oscrs/Amplitude\",\"meta\": [{ \"1\": \"\" },{ \"tooltip\": \"Sawtooth waveform amplitude\" },{ \"unit\": \"dB\" }],\"init\": -20,\"min\": -120,\"max\": 10,\"step\": 0.1},{\"type\": \"hslider\",\"label\": \"Frequency\",\"varname\": \"fHslider3\",\"shortname\": \"Frequency\",\"address\": \"/cubic_distortion/0x00/SINE_WAVE_OSCILLATOR_oscrs/Frequency\",\"meta\": [{ \"2\": \"\" },{ \"tooltip\": \"Sine wave frequency as a Piano Key (PK) number (A440 = 49 PK)\" },{ \"unit\": \"PK\" }],\"init\": 49,\"min\": 1,\"max\": 88,\"step\": 0.01},{\"type\": \"hslider\",\"label\": \"Portamento\",\"varname\": \"fHslider2\",\"shortname\": \"Portamento\",\"address\": \"/cubic_distortion/0x00/SINE_WAVE_OSCILLATOR_oscrs/Portamento\",\"meta\": [{ \"3\": \"\" },{ \"scale\": \"log\" },{ \"tooltip\": \"Portamento (frequency-glide) time-constant in seconds\" },{ \"unit\": \"sec\" }],\"init\": 0.1,\"min\": 0.001,\"max\": 10,\"step\": 0.001}]}]},{\"type\": \"vgroup\",\"label\": \"0x00\",\"meta\": [{ \"2\": \"\" }],\"items\": [ {\"type\": \"vgroup\",\"label\": \"CUBIC NONLINEARITY cubicnl\",\"meta\": [{ \"tooltip\": \"Reference:          https://ccrma.stanford.edu/~jos/pasp/Cubic_Soft_Clipper.html\" }],\"items\": [ {\"type\": \"checkbox\",\"label\": \"Bypass\",\"varname\": \"fCheckbox0\",\"shortname\": \"Bypass\",\"address\": \"/cubic_distortion/0x00/CUBIC_NONLINEARITY_cubicnl/Bypass\",\"meta\": [{ \"0\": \"\" },{ \"tooltip\": \"When this is checked, the nonlinearity has no effect\" }]},{\"type\": \"hslider\",\"label\": \"Drive\",\"varname\": \"fHslider4\",\"shortname\": \"Drive\",\"address\": \"/cubic_distortion/0x00/CUBIC_NONLINEARITY_cubicnl/Drive\",\"meta\": [{ \"1\": \"\" },{ \"tooltip\": \"Amount of distortion\" }],\"init\": 0,\"min\": 0,\"max\": 1,\"step\": 0.01},{\"type\": \"hslider\",\"label\": \"Offset\",\"varname\": \"fHslider0\",\"shortname\": \"Offset\",\"address\": \"/cubic_distortion/0x00/CUBIC_NONLINEARITY_cubicnl/Offset\",\"meta\": [{ \"2\": \"\" },{ \"tooltip\": \"Brings in even harmonics\" }],\"init\": 0,\"min\": 0,\"max\": 1,\"step\": 0.01}]}]},{\"type\": \"vgroup\",\"label\": \"0x00\",\"meta\": [{ \"3\": \"\" }],\"items\": [ {\"type\": \"hgroup\",\"label\": \"CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning LP, 9 octaves below 16000 Hz, HP\",\"meta\": [{ \"0\": \"\" },{ \"tooltip\": \"See Faust\'s filter.lib for documentation and references\" }],\"items\": [ {\"type\": \"vbargraph\",\"label\": \"vbargraph0\",\"varname\": \"fVbargraph14\",\"shortname\": \"vbargraph0\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph0\",\"meta\": [{ \"0\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph1\",\"varname\": \"fVbargraph13\",\"shortname\": \"vbargraph1\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph1\",\"meta\": [{ \"1\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph2\",\"varname\": \"fVbargraph12\",\"shortname\": \"vbargraph2\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph2\",\"meta\": [{ \"2\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph3\",\"varname\": \"fVbargraph11\",\"shortname\": \"vbargraph3\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph3\",\"meta\": [{ \"3\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph4\",\"varname\": \"fVbargraph10\",\"shortname\": \"vbargraph4\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph4\",\"meta\": [{ \"4\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph5\",\"varname\": \"fVbargraph9\",\"shortname\": \"vbargraph5\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph5\",\"meta\": [{ \"5\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph6\",\"varname\": \"fVbargraph8\",\"shortname\": \"vbargraph6\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph6\",\"meta\": [{ \"6\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph7\",\"varname\": \"fVbargraph7\",\"shortname\": \"vbargraph7\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph7\",\"meta\": [{ \"7\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph8\",\"varname\": \"fVbargraph6\",\"shortname\": \"vbargraph8\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph8\",\"meta\": [{ \"8\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph9\",\"varname\": \"fVbargraph5\",\"shortname\": \"vbargraph9\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph9\",\"meta\": [{ \"9\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph10\",\"varname\": \"fVbargraph4\",\"shortname\": \"vbargraph10\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph10\",\"meta\": [{ \"10\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph11\",\"varname\": \"fVbargraph3\",\"shortname\": \"vbargraph11\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph11\",\"meta\": [{ \"11\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph12\",\"varname\": \"fVbargraph2\",\"shortname\": \"vbargraph12\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph12\",\"meta\": [{ \"12\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph13\",\"varname\": \"fVbargraph1\",\"shortname\": \"vbargraph13\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph13\",\"meta\": [{ \"13\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph14\",\"varname\": \"fVbargraph0\",\"shortname\": \"vbargraph14\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph14\",\"meta\": [{ \"14\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10}]},{\"type\": \"hgroup\",\"label\": \"SPECTRUM ANALYZER CONTROLS\",\"meta\": [{ \"1\": \"\" }],\"items\": [ {\"type\": \"hslider\",\"label\": \"Level Averaging Time\",\"varname\": \"fHslider5\",\"shortname\": \"Level_Averaging_Time\",\"address\": \"/cubic_distortion/0x00/SPECTRUM_ANALYZER_CONTROLS/Level_Averaging_Time\",\"meta\": [{ \"0\": \"\" },{ \"scale\": \"log\" },{ \"tooltip\": \"band-level averaging time in milliseconds\" },{ \"unit\": \"ms\" }],\"init\": 100,\"min\": 1,\"max\": 10000,\"step\": 1},{\"type\": \"hslider\",\"label\": \"Level dB Offset\",\"varname\": \"fHslider6\",\"shortname\": \"Level_dB_Offset\",\"address\": \"/cubic_distortion/0x00/SPECTRUM_ANALYZER_CONTROLS/Level_dB_Offset\",\"meta\": [{ \"1\": \"\" },{ \"tooltip\": \"Level offset in decibels\" },{ \"unit\": \"dB\" }],\"init\": 50,\"min\": 0,\"max\": 100,\"step\": 1}]}]}]}]}"

    @always_inline
    def metadata(read dsp, mut meta: Some[FaustMeta]) -> None:
        meta.declare("compile_options", "-a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs")
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
        meta.declare("filename", "cubic_distortion.dsp")
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
        meta.declare("name", "cubic_distortion")
        meta.declare("oscillator.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)")
        meta.declare("oscillator.lib/copyright", "Julius O. Smith III")
        meta.declare("oscillator.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.")
        meta.declare("oscillator.lib/license", "STK-4.3")
        meta.declare("oscillator.lib/name", "Faust Oscillator Library")
        meta.declare("oscillator.lib/version", "1.11")

    @always_inline
    def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None:
        ui.open_vertical_box("cubic_distortion")
        ui.declare(dsp.null_val, "1", "")
        ui.open_vertical_box("0x00")
        ui.declare(dsp.null_val, "0", "")
        ui.declare(dsp.null_val, "tooltip", "Sine oscillator based on 2D vector rotation")
        ui.open_vertical_box("SINE WAVE OSCILLATOR oscrs")
        ui.declare(dsp.hslider1, "1", "")
        ui.declare(dsp.hslider1, "tooltip", "Sawtooth waveform amplitude")
        ui.declare(dsp.hslider1, "unit", "dB")
        ui.add_horizontal_slider("Amplitude", dsp.hslider1, FaustFloat(-20.0), FaustFloat(-120.0), FaustFloat(10.0), FaustFloat(0.1))
        ui.declare(dsp.hslider3, "2", "")
        ui.declare(dsp.hslider3, "tooltip", "Sine wave frequency as a Piano Key (PK) number (A440 = 49 PK)")
        ui.declare(dsp.hslider3, "unit", "PK")
        ui.add_horizontal_slider("Frequency", dsp.hslider3, FaustFloat(49.0), FaustFloat(1.0), FaustFloat(88.0), FaustFloat(0.01))
        ui.declare(dsp.hslider2, "3", "")
        ui.declare(dsp.hslider2, "scale", "log")
        ui.declare(dsp.hslider2, "tooltip", "Portamento (frequency-glide) time-constant in seconds")
        ui.declare(dsp.hslider2, "unit", "sec")
        ui.add_horizontal_slider("Portamento", dsp.hslider2, FaustFloat(0.1), FaustFloat(0.001), FaustFloat(10.0), FaustFloat(0.001))
        ui.close_box()
        ui.close_box()
        ui.declare(dsp.null_val, "2", "")
        ui.open_vertical_box("0x00")
        ui.declare(dsp.null_val, "tooltip", "Reference:          https://ccrma.stanford.edu/~jos/pasp/Cubic_Soft_Clipper.html")
        ui.open_vertical_box("CUBIC NONLINEARITY cubicnl")
        ui.declare(dsp.checkbox0, "0", "")
        ui.declare(dsp.checkbox0, "tooltip", "When this is checked, the nonlinearity has no effect")
        ui.add_check_button("Bypass", dsp.checkbox0)
        ui.declare(dsp.hslider4, "1", "")
        ui.declare(dsp.hslider4, "tooltip", "Amount of distortion")
        ui.add_horizontal_slider("Drive", dsp.hslider4, FaustFloat(0.0), FaustFloat(0.0), FaustFloat(1.0), FaustFloat(0.01))
        ui.declare(dsp.hslider0, "2", "")
        ui.declare(dsp.hslider0, "tooltip", "Brings in even harmonics")
        ui.add_horizontal_slider("Offset", dsp.hslider0, FaustFloat(0.0), FaustFloat(0.0), FaustFloat(1.0), FaustFloat(0.01))
        ui.close_box()
        ui.close_box()
        ui.declare(dsp.null_val, "3", "")
        ui.open_vertical_box("0x00")
        ui.declare(dsp.null_val, "0", "")
        ui.declare(dsp.null_val, "tooltip", "See Faust's filter.lib for documentation and references")
        ui.open_horizontal_box("CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning LP, 9 octaves below 16000 Hz, HP")
        ui.declare(dsp.vbargraph14, "0", "")
        ui.declare(dsp.vbargraph14, "tooltip", "Spectral Band Level in dB")
        ui.declare(dsp.vbargraph14, "unit", "dB")
        ui.add_vertical_bargraph("vbargraph0", dsp.vbargraph14, FaustFloat(-50.0), FaustFloat(10.0))
        ui.declare(dsp.vbargraph13, "1", "")
        ui.declare(dsp.vbargraph13, "tooltip", "Spectral Band Level in dB")
        ui.declare(dsp.vbargraph13, "unit", "dB")
        ui.add_vertical_bargraph("vbargraph1", dsp.vbargraph13, FaustFloat(-50.0), FaustFloat(10.0))
        ui.declare(dsp.vbargraph12, "2", "")
        ui.declare(dsp.vbargraph12, "tooltip", "Spectral Band Level in dB")
        ui.declare(dsp.vbargraph12, "unit", "dB")
        ui.add_vertical_bargraph("vbargraph2", dsp.vbargraph12, FaustFloat(-50.0), FaustFloat(10.0))
        ui.declare(dsp.vbargraph11, "3", "")
        ui.declare(dsp.vbargraph11, "tooltip", "Spectral Band Level in dB")
        ui.declare(dsp.vbargraph11, "unit", "dB")
        ui.add_vertical_bargraph("vbargraph3", dsp.vbargraph11, FaustFloat(-50.0), FaustFloat(10.0))
        ui.declare(dsp.vbargraph10, "4", "")
        ui.declare(dsp.vbargraph10, "tooltip", "Spectral Band Level in dB")
        ui.declare(dsp.vbargraph10, "unit", "dB")
        ui.add_vertical_bargraph("vbargraph4", dsp.vbargraph10, FaustFloat(-50.0), FaustFloat(10.0))
        ui.declare(dsp.vbargraph9, "5", "")
        ui.declare(dsp.vbargraph9, "tooltip", "Spectral Band Level in dB")
        ui.declare(dsp.vbargraph9, "unit", "dB")
        ui.add_vertical_bargraph("vbargraph5", dsp.vbargraph9, FaustFloat(-50.0), FaustFloat(10.0))
        ui.declare(dsp.vbargraph8, "6", "")
        ui.declare(dsp.vbargraph8, "tooltip", "Spectral Band Level in dB")
        ui.declare(dsp.vbargraph8, "unit", "dB")
        ui.add_vertical_bargraph("vbargraph6", dsp.vbargraph8, FaustFloat(-50.0), FaustFloat(10.0))
        ui.declare(dsp.vbargraph7, "7", "")
        ui.declare(dsp.vbargraph7, "tooltip", "Spectral Band Level in dB")
        ui.declare(dsp.vbargraph7, "unit", "dB")
        ui.add_vertical_bargraph("vbargraph7", dsp.vbargraph7, FaustFloat(-50.0), FaustFloat(10.0))
        ui.declare(dsp.vbargraph6, "8", "")
        ui.declare(dsp.vbargraph6, "tooltip", "Spectral Band Level in dB")
        ui.declare(dsp.vbargraph6, "unit", "dB")
        ui.add_vertical_bargraph("vbargraph8", dsp.vbargraph6, FaustFloat(-50.0), FaustFloat(10.0))
        ui.declare(dsp.vbargraph5, "9", "")
        ui.declare(dsp.vbargraph5, "tooltip", "Spectral Band Level in dB")
        ui.declare(dsp.vbargraph5, "unit", "dB")
        ui.add_vertical_bargraph("vbargraph9", dsp.vbargraph5, FaustFloat(-50.0), FaustFloat(10.0))
        ui.declare(dsp.vbargraph4, "10", "")
        ui.declare(dsp.vbargraph4, "tooltip", "Spectral Band Level in dB")
        ui.declare(dsp.vbargraph4, "unit", "dB")
        ui.add_vertical_bargraph("vbargraph10", dsp.vbargraph4, FaustFloat(-50.0), FaustFloat(10.0))
        ui.declare(dsp.vbargraph3, "11", "")
        ui.declare(dsp.vbargraph3, "tooltip", "Spectral Band Level in dB")
        ui.declare(dsp.vbargraph3, "unit", "dB")
        ui.add_vertical_bargraph("vbargraph11", dsp.vbargraph3, FaustFloat(-50.0), FaustFloat(10.0))
        ui.declare(dsp.vbargraph2, "12", "")
        ui.declare(dsp.vbargraph2, "tooltip", "Spectral Band Level in dB")
        ui.declare(dsp.vbargraph2, "unit", "dB")
        ui.add_vertical_bargraph("vbargraph12", dsp.vbargraph2, FaustFloat(-50.0), FaustFloat(10.0))
        ui.declare(dsp.vbargraph1, "13", "")
        ui.declare(dsp.vbargraph1, "tooltip", "Spectral Band Level in dB")
        ui.declare(dsp.vbargraph1, "unit", "dB")
        ui.add_vertical_bargraph("vbargraph13", dsp.vbargraph1, FaustFloat(-50.0), FaustFloat(10.0))
        ui.declare(dsp.vbargraph0, "14", "")
        ui.declare(dsp.vbargraph0, "tooltip", "Spectral Band Level in dB")
        ui.declare(dsp.vbargraph0, "unit", "dB")
        ui.add_vertical_bargraph("vbargraph14", dsp.vbargraph0, FaustFloat(-50.0), FaustFloat(10.0))
        ui.close_box()
        ui.declare(dsp.null_val, "1", "")
        ui.open_horizontal_box("SPECTRUM ANALYZER CONTROLS")
        ui.declare(dsp.hslider5, "0", "")
        ui.declare(dsp.hslider5, "scale", "log")
        ui.declare(dsp.hslider5, "tooltip", "band-level averaging time in milliseconds")
        ui.declare(dsp.hslider5, "unit", "ms")
        ui.add_horizontal_slider("Level Averaging Time", dsp.hslider5, FaustFloat(100.0), FaustFloat(1.0), FaustFloat(10000.0), FaustFloat(1.0))
        ui.declare(dsp.hslider6, "1", "")
        ui.declare(dsp.hslider6, "tooltip", "Level offset in decibels")
        ui.declare(dsp.hslider6, "unit", "dB")
        ui.add_horizontal_slider("Level dB Offset", dsp.hslider6, FaustFloat(50.0), FaustFloat(0.0), FaustFloat(100.0), FaustFloat(1.0))
        ui.close_box()
        ui.close_box()
        ui.close_box()

    @always_inline
    def compute(
        mut dsp, var count: S32, var inputs: ReadStreams, var outputs: MutaStreams
    ) -> None:
        var output0_ptr = outputs[S32(0)]
        var output1_ptr = outputs[S32(1)]
        var slow0 = (0.0010000000000000009) * (F64(dsp.hslider0))
        var rec1_tmp = Arr[F64, 8](uninitialized=True)
        var rec1 = Ptr(to=rec1_tmp[S32(4)])
        var slow1 = (0.0010000000000000009) * (pow(1e+01, (0.05) * (F64(dsp.hslider1))))
        var rec2_tmp = Arr[F64, 8](uninitialized=True)
        var rec2 = Ptr(to=rec2_tmp[S32(4)])
        var slow2 = F64(dsp.hslider2)
        var slow3 = exp(-((dsp.const1) / (slow2))) if S32((slow2) > (0.0)) else 0.0
        var slow4 = ((4.4e+02) * (pow(2.0, (0.08333333333333333) * ((F64(dsp.hslider3)) + (-49.0))))) * ((1.0) - (slow3))
        var rec5_tmp = Arr[F64, 8](uninitialized=True)
        var rec5 = Ptr(to=rec5_tmp[S32(4)])
        var zec0 = Arr[F64, 4](uninitialized=True)
        var zec1 = Arr[F64, 4](uninitialized=True)
        var zec2 = Arr[F64, 4](uninitialized=True)
        var rec3_tmp = Arr[F64, 8](uninitialized=True)
        var rec3 = Ptr(to=rec3_tmp[S32(4)])
        var i_vec0_tmp = Arr[S32, 8](uninitialized=True)
        var i_vec0 = Ptr(to=i_vec0_tmp[S32(4)])
        var rec4_tmp = Arr[F64, 8](uninitialized=True)
        var rec4 = Ptr(to=rec4_tmp[S32(4)])
        var slow5 = (0.0010000000000000009) * (F64(dsp.hslider4))
        var rec6_tmp = Arr[F64, 8](uninitialized=True)
        var rec6 = Ptr(to=rec6_tmp[S32(4)])
        var i_slow6 = S32(F64(dsp.checkbox0))
        var zec3 = Arr[F64, 4](uninitialized=True)
        var zec4 = Arr[F64, 4](uninitialized=True)
        var yec0_tmp = Arr[F64, 8](uninitialized=True)
        var yec0 = Ptr(to=yec0_tmp[S32(4)])
        var rec0_tmp = Arr[F64, 8](uninitialized=True)
        var rec0 = Ptr(to=rec0_tmp[S32(4)])
        var zec5 = Arr[F64, 4](uninitialized=True)
        var rec10_tmp = Arr[F64, 8](uninitialized=True)
        var rec10 = Ptr(to=rec10_tmp[S32(4)])
        var rec9_tmp = Arr[F64, 8](uninitialized=True)
        var rec9 = Ptr(to=rec9_tmp[S32(4)])
        var rec8_tmp = Arr[F64, 8](uninitialized=True)
        var rec8 = Ptr(to=rec8_tmp[S32(4)])
        var slow7 = F64(dsp.hslider5)
        var slow8 = exp(-((dsp.const22) / (slow7))) if S32(((0.001) * (slow7)) > (0.0)) else 0.0
        var slow9 = (1.0) - (slow8)
        var rec7_tmp = Arr[F64, 8](uninitialized=True)
        var rec7 = Ptr(to=rec7_tmp[S32(4)])
        var rec17_tmp = Arr[F64, 8](uninitialized=True)
        var rec17 = Ptr(to=rec17_tmp[S32(4)])
        var rec16_tmp = Arr[F64, 8](uninitialized=True)
        var rec16 = Ptr(to=rec16_tmp[S32(4)])
        var rec15_tmp = Arr[F64, 8](uninitialized=True)
        var rec15 = Ptr(to=rec15_tmp[S32(4)])
        var zec6 = Arr[F64, 4](uninitialized=True)
        var rec14_tmp = Arr[F64, 8](uninitialized=True)
        var rec14 = Ptr(to=rec14_tmp[S32(4)])
        var rec13_tmp = Arr[F64, 8](uninitialized=True)
        var rec13 = Ptr(to=rec13_tmp[S32(4)])
        var rec12_tmp = Arr[F64, 8](uninitialized=True)
        var rec12 = Ptr(to=rec12_tmp[S32(4)])
        var rec11_tmp = Arr[F64, 8](uninitialized=True)
        var rec11 = Ptr(to=rec11_tmp[S32(4)])
        var rec24_tmp = Arr[F64, 8](uninitialized=True)
        var rec24 = Ptr(to=rec24_tmp[S32(4)])
        var rec23_tmp = Arr[F64, 8](uninitialized=True)
        var rec23 = Ptr(to=rec23_tmp[S32(4)])
        var rec22_tmp = Arr[F64, 8](uninitialized=True)
        var rec22 = Ptr(to=rec22_tmp[S32(4)])
        var zec7 = Arr[F64, 4](uninitialized=True)
        var rec21_tmp = Arr[F64, 8](uninitialized=True)
        var rec21 = Ptr(to=rec21_tmp[S32(4)])
        var rec20_tmp = Arr[F64, 8](uninitialized=True)
        var rec20 = Ptr(to=rec20_tmp[S32(4)])
        var rec19_tmp = Arr[F64, 8](uninitialized=True)
        var rec19 = Ptr(to=rec19_tmp[S32(4)])
        var rec18_tmp = Arr[F64, 8](uninitialized=True)
        var rec18 = Ptr(to=rec18_tmp[S32(4)])
        var rec31_tmp = Arr[F64, 8](uninitialized=True)
        var rec31 = Ptr(to=rec31_tmp[S32(4)])
        var rec30_tmp = Arr[F64, 8](uninitialized=True)
        var rec30 = Ptr(to=rec30_tmp[S32(4)])
        var rec29_tmp = Arr[F64, 8](uninitialized=True)
        var rec29 = Ptr(to=rec29_tmp[S32(4)])
        var zec8 = Arr[F64, 4](uninitialized=True)
        var rec28_tmp = Arr[F64, 8](uninitialized=True)
        var rec28 = Ptr(to=rec28_tmp[S32(4)])
        var rec27_tmp = Arr[F64, 8](uninitialized=True)
        var rec27 = Ptr(to=rec27_tmp[S32(4)])
        var rec26_tmp = Arr[F64, 8](uninitialized=True)
        var rec26 = Ptr(to=rec26_tmp[S32(4)])
        var rec25_tmp = Arr[F64, 8](uninitialized=True)
        var rec25 = Ptr(to=rec25_tmp[S32(4)])
        var rec38_tmp = Arr[F64, 8](uninitialized=True)
        var rec38 = Ptr(to=rec38_tmp[S32(4)])
        var rec37_tmp = Arr[F64, 8](uninitialized=True)
        var rec37 = Ptr(to=rec37_tmp[S32(4)])
        var rec36_tmp = Arr[F64, 8](uninitialized=True)
        var rec36 = Ptr(to=rec36_tmp[S32(4)])
        var zec9 = Arr[F64, 4](uninitialized=True)
        var rec35_tmp = Arr[F64, 8](uninitialized=True)
        var rec35 = Ptr(to=rec35_tmp[S32(4)])
        var rec34_tmp = Arr[F64, 8](uninitialized=True)
        var rec34 = Ptr(to=rec34_tmp[S32(4)])
        var rec33_tmp = Arr[F64, 8](uninitialized=True)
        var rec33 = Ptr(to=rec33_tmp[S32(4)])
        var rec32_tmp = Arr[F64, 8](uninitialized=True)
        var rec32 = Ptr(to=rec32_tmp[S32(4)])
        var rec45_tmp = Arr[F64, 8](uninitialized=True)
        var rec45 = Ptr(to=rec45_tmp[S32(4)])
        var rec44_tmp = Arr[F64, 8](uninitialized=True)
        var rec44 = Ptr(to=rec44_tmp[S32(4)])
        var rec43_tmp = Arr[F64, 8](uninitialized=True)
        var rec43 = Ptr(to=rec43_tmp[S32(4)])
        var zec10 = Arr[F64, 4](uninitialized=True)
        var rec42_tmp = Arr[F64, 8](uninitialized=True)
        var rec42 = Ptr(to=rec42_tmp[S32(4)])
        var rec41_tmp = Arr[F64, 8](uninitialized=True)
        var rec41 = Ptr(to=rec41_tmp[S32(4)])
        var rec40_tmp = Arr[F64, 8](uninitialized=True)
        var rec40 = Ptr(to=rec40_tmp[S32(4)])
        var rec39_tmp = Arr[F64, 8](uninitialized=True)
        var rec39 = Ptr(to=rec39_tmp[S32(4)])
        var rec52_tmp = Arr[F64, 8](uninitialized=True)
        var rec52 = Ptr(to=rec52_tmp[S32(4)])
        var rec51_tmp = Arr[F64, 8](uninitialized=True)
        var rec51 = Ptr(to=rec51_tmp[S32(4)])
        var rec50_tmp = Arr[F64, 8](uninitialized=True)
        var rec50 = Ptr(to=rec50_tmp[S32(4)])
        var zec11 = Arr[F64, 4](uninitialized=True)
        var rec49_tmp = Arr[F64, 8](uninitialized=True)
        var rec49 = Ptr(to=rec49_tmp[S32(4)])
        var rec48_tmp = Arr[F64, 8](uninitialized=True)
        var rec48 = Ptr(to=rec48_tmp[S32(4)])
        var rec47_tmp = Arr[F64, 8](uninitialized=True)
        var rec47 = Ptr(to=rec47_tmp[S32(4)])
        var rec46_tmp = Arr[F64, 8](uninitialized=True)
        var rec46 = Ptr(to=rec46_tmp[S32(4)])
        var rec59_tmp = Arr[F64, 8](uninitialized=True)
        var rec59 = Ptr(to=rec59_tmp[S32(4)])
        var rec58_tmp = Arr[F64, 8](uninitialized=True)
        var rec58 = Ptr(to=rec58_tmp[S32(4)])
        var rec57_tmp = Arr[F64, 8](uninitialized=True)
        var rec57 = Ptr(to=rec57_tmp[S32(4)])
        var zec12 = Arr[F64, 4](uninitialized=True)
        var rec56_tmp = Arr[F64, 8](uninitialized=True)
        var rec56 = Ptr(to=rec56_tmp[S32(4)])
        var rec55_tmp = Arr[F64, 8](uninitialized=True)
        var rec55 = Ptr(to=rec55_tmp[S32(4)])
        var rec54_tmp = Arr[F64, 8](uninitialized=True)
        var rec54 = Ptr(to=rec54_tmp[S32(4)])
        var rec53_tmp = Arr[F64, 8](uninitialized=True)
        var rec53 = Ptr(to=rec53_tmp[S32(4)])
        var rec66_tmp = Arr[F64, 8](uninitialized=True)
        var rec66 = Ptr(to=rec66_tmp[S32(4)])
        var rec65_tmp = Arr[F64, 8](uninitialized=True)
        var rec65 = Ptr(to=rec65_tmp[S32(4)])
        var rec64_tmp = Arr[F64, 8](uninitialized=True)
        var rec64 = Ptr(to=rec64_tmp[S32(4)])
        var zec13 = Arr[F64, 4](uninitialized=True)
        var rec63_tmp = Arr[F64, 8](uninitialized=True)
        var rec63 = Ptr(to=rec63_tmp[S32(4)])
        var rec62_tmp = Arr[F64, 8](uninitialized=True)
        var rec62 = Ptr(to=rec62_tmp[S32(4)])
        var rec61_tmp = Arr[F64, 8](uninitialized=True)
        var rec61 = Ptr(to=rec61_tmp[S32(4)])
        var rec60_tmp = Arr[F64, 8](uninitialized=True)
        var rec60 = Ptr(to=rec60_tmp[S32(4)])
        var rec73_tmp = Arr[F64, 8](uninitialized=True)
        var rec73 = Ptr(to=rec73_tmp[S32(4)])
        var rec72_tmp = Arr[F64, 8](uninitialized=True)
        var rec72 = Ptr(to=rec72_tmp[S32(4)])
        var rec71_tmp = Arr[F64, 8](uninitialized=True)
        var rec71 = Ptr(to=rec71_tmp[S32(4)])
        var zec14 = Arr[F64, 4](uninitialized=True)
        var rec70_tmp = Arr[F64, 8](uninitialized=True)
        var rec70 = Ptr(to=rec70_tmp[S32(4)])
        var rec69_tmp = Arr[F64, 8](uninitialized=True)
        var rec69 = Ptr(to=rec69_tmp[S32(4)])
        var rec68_tmp = Arr[F64, 8](uninitialized=True)
        var rec68 = Ptr(to=rec68_tmp[S32(4)])
        var rec67_tmp = Arr[F64, 8](uninitialized=True)
        var rec67 = Ptr(to=rec67_tmp[S32(4)])
        var rec80_tmp = Arr[F64, 8](uninitialized=True)
        var rec80 = Ptr(to=rec80_tmp[S32(4)])
        var rec79_tmp = Arr[F64, 8](uninitialized=True)
        var rec79 = Ptr(to=rec79_tmp[S32(4)])
        var rec78_tmp = Arr[F64, 8](uninitialized=True)
        var rec78 = Ptr(to=rec78_tmp[S32(4)])
        var zec15 = Arr[F64, 4](uninitialized=True)
        var rec77_tmp = Arr[F64, 8](uninitialized=True)
        var rec77 = Ptr(to=rec77_tmp[S32(4)])
        var rec76_tmp = Arr[F64, 8](uninitialized=True)
        var rec76 = Ptr(to=rec76_tmp[S32(4)])
        var rec75_tmp = Arr[F64, 8](uninitialized=True)
        var rec75 = Ptr(to=rec75_tmp[S32(4)])
        var rec74_tmp = Arr[F64, 8](uninitialized=True)
        var rec74 = Ptr(to=rec74_tmp[S32(4)])
        var rec87_tmp = Arr[F64, 8](uninitialized=True)
        var rec87 = Ptr(to=rec87_tmp[S32(4)])
        var rec86_tmp = Arr[F64, 8](uninitialized=True)
        var rec86 = Ptr(to=rec86_tmp[S32(4)])
        var rec85_tmp = Arr[F64, 8](uninitialized=True)
        var rec85 = Ptr(to=rec85_tmp[S32(4)])
        var zec16 = Arr[F64, 4](uninitialized=True)
        var rec84_tmp = Arr[F64, 8](uninitialized=True)
        var rec84 = Ptr(to=rec84_tmp[S32(4)])
        var rec83_tmp = Arr[F64, 8](uninitialized=True)
        var rec83 = Ptr(to=rec83_tmp[S32(4)])
        var rec82_tmp = Arr[F64, 8](uninitialized=True)
        var rec82 = Ptr(to=rec82_tmp[S32(4)])
        var rec81_tmp = Arr[F64, 8](uninitialized=True)
        var rec81 = Ptr(to=rec81_tmp[S32(4)])
        var rec94_tmp = Arr[F64, 8](uninitialized=True)
        var rec94 = Ptr(to=rec94_tmp[S32(4)])
        var rec93_tmp = Arr[F64, 8](uninitialized=True)
        var rec93 = Ptr(to=rec93_tmp[S32(4)])
        var rec92_tmp = Arr[F64, 8](uninitialized=True)
        var rec92 = Ptr(to=rec92_tmp[S32(4)])
        var zec17 = Arr[F64, 4](uninitialized=True)
        var rec91_tmp = Arr[F64, 8](uninitialized=True)
        var rec91 = Ptr(to=rec91_tmp[S32(4)])
        var rec90_tmp = Arr[F64, 8](uninitialized=True)
        var rec90 = Ptr(to=rec90_tmp[S32(4)])
        var rec89_tmp = Arr[F64, 8](uninitialized=True)
        var rec89 = Ptr(to=rec89_tmp[S32(4)])
        var rec88_tmp = Arr[F64, 8](uninitialized=True)
        var rec88 = Ptr(to=rec88_tmp[S32(4)])
        var rec101_tmp = Arr[F64, 8](uninitialized=True)
        var rec101 = Ptr(to=rec101_tmp[S32(4)])
        var rec100_tmp = Arr[F64, 8](uninitialized=True)
        var rec100 = Ptr(to=rec100_tmp[S32(4)])
        var rec99_tmp = Arr[F64, 8](uninitialized=True)
        var rec99 = Ptr(to=rec99_tmp[S32(4)])
        var zec18 = Arr[F64, 4](uninitialized=True)
        var rec98_tmp = Arr[F64, 8](uninitialized=True)
        var rec98 = Ptr(to=rec98_tmp[S32(4)])
        var rec97_tmp = Arr[F64, 8](uninitialized=True)
        var rec97 = Ptr(to=rec97_tmp[S32(4)])
        var rec96_tmp = Arr[F64, 8](uninitialized=True)
        var rec96 = Ptr(to=rec96_tmp[S32(4)])
        var rec95_tmp = Arr[F64, 8](uninitialized=True)
        var rec95 = Ptr(to=rec95_tmp[S32(4)])
        var rec105_tmp = Arr[F64, 8](uninitialized=True)
        var rec105 = Ptr(to=rec105_tmp[S32(4)])
        var rec104_tmp = Arr[F64, 8](uninitialized=True)
        var rec104 = Ptr(to=rec104_tmp[S32(4)])
        var rec103_tmp = Arr[F64, 8](uninitialized=True)
        var rec103 = Ptr(to=rec103_tmp[S32(4)])
        var rec102_tmp = Arr[F64, 8](uninitialized=True)
        var rec102 = Ptr(to=rec102_tmp[S32(4)])
        var slow10 = F64(dsp.hslider6)
        var zec19 = Arr[F64, 4](uninitialized=True)
        # Main loop 
        vindex_re0 = S32(0)
        while (vindex_re0) <= ((count) - (S32(4))): 
            var output0 = Ptr(to=output0_ptr[vindex_re0])
            var output1 = Ptr(to=output1_ptr[vindex_re0])
            var vsize_re0 = S32(4)
            # Recursive loop 0 
            # Pre code 
            var j0_re0 = S32(0)
            comptime dtype0 = f64
            comptime width0 = S32(simd_width_of[dtype0]())
            while j0_re0 <= S32(4) - width0:
                var values = simd_load(dsp.rec1_perm, j0_re0)
                simd_store(rec1_tmp, j0_re0, values)
                j0_re0 = j0_re0 + S32(width0)
            # Compute code 
            var i_re0 = S32(0)
            while (i_re0) < (vsize_re0): 
                rec1[i_re0] = (slow0) + ((0.999) * (rec1[(i_re0) - (S32(1))]))
                i_re0 = (i_re0) + (S32(1))
            # Post code 
            var j1_re0 = S32(0)
            while (j1_re0) < (S32(4)): 
                dsp.rec1_perm[j1_re0] = rec1_tmp[(vsize_re0) + (j1_re0)]
                j1_re0 = (j1_re0) + (S32(1))
            # Recursive loop 1 
            # Pre code 
            var j2_re0 = S32(0)
            comptime dtype2 = f64
            comptime width2 = S32(simd_width_of[dtype2]())
            while j2_re0 <= S32(4) - width2:
                var values = simd_load(dsp.rec2_perm, j2_re0)
                simd_store(rec2_tmp, j2_re0, values)
                j2_re0 = j2_re0 + S32(width2)
            # Compute code 
            var i_re1 = S32(0)
            while (i_re1) < (vsize_re0): 
                rec2[i_re1] = (slow1) + ((0.999) * (rec2[(i_re1) - (S32(1))]))
                i_re1 = (i_re1) + (S32(1))
            # Post code 
            var j3_re0 = S32(0)
            while (j3_re0) < (S32(4)): 
                dsp.rec2_perm[j3_re0] = rec2_tmp[(vsize_re0) + (j3_re0)]
                j3_re0 = (j3_re0) + (S32(1))
            # Recursive loop 2 
            # Pre code 
            var j4_re0 = S32(0)
            comptime dtype4 = f64
            comptime width4 = S32(simd_width_of[dtype4]())
            while j4_re0 <= S32(4) - width4:
                var values = simd_load(dsp.rec5_perm, j4_re0)
                simd_store(rec5_tmp, j4_re0, values)
                j4_re0 = j4_re0 + S32(width4)
            # Compute code 
            var i_re2 = S32(0)
            while (i_re2) < (vsize_re0): 
                rec5[i_re2] = ((rec5[(i_re2) - (S32(1))]) * (slow3)) + (slow4)
                i_re2 = (i_re2) + (S32(1))
            # Post code 
            var j5_re0 = S32(0)
            while (j5_re0) < (S32(4)): 
                dsp.rec5_perm[j5_re0] = rec5_tmp[(vsize_re0) + (j5_re0)]
                j5_re0 = (j5_re0) + (S32(1))
            # Vectorizable loop 3 
            # Compute code 
            var i_re3 = S32(0)
            comptime dtype6 = f64
            comptime width6 = S32(simd_width_of[dtype6]())
            while i_re3 <= vsize_re0 - width6:
                var values = (dsp.const2) * (simd_load(rec5, i_re3))
                simd_store(zec0, i_re3, values)
                i_re3 = i_re3 + S32(width6)
            # Vectorizable loop 4 
            # Compute code 
            var i_re4 = S32(0)
            comptime dtype7 = f64
            comptime width7 = S32(simd_width_of[dtype7]())
            while i_re4 <= vsize_re0 - width7:
                var values = sin(simd_load(zec0, i_re4))
                simd_store(zec1, i_re4, values)
                i_re4 = i_re4 + S32(width7)
            # Vectorizable loop 5 
            # Compute code 
            var i_re5 = S32(0)
            comptime dtype8 = f64
            comptime width8 = S32(simd_width_of[dtype8]())
            while i_re5 <= vsize_re0 - width8:
                var values = cos(simd_load(zec0, i_re5))
                simd_store(zec2, i_re5, values)
                i_re5 = i_re5 + S32(width8)
            # Vectorizable loop 6 
            # Pre code 
            var j8_re0 = S32(0)
            comptime dtype9 = s32
            comptime width9 = S32(simd_width_of[dtype9]())
            while j8_re0 <= S32(4) - width9:
                var values = simd_load(dsp.i_vec0_perm, j8_re0)
                simd_store(i_vec0_tmp, j8_re0, values)
                j8_re0 = j8_re0 + S32(width9)
            # Compute code 
            var i_re6 = S32(0)
            comptime dtype10 = s32
            comptime width10 = S32(simd_width_of[dtype10]())
            while i_re6 <= vsize_re0 - width10:
                var values = S32(1)
                simd_store(i_vec0, i_re6, values)
                i_re6 = i_re6 + S32(width10)
            # Post code 
            var j9_re0 = S32(0)
            while (j9_re0) < (S32(4)): 
                dsp.i_vec0_perm[j9_re0] = i_vec0_tmp[(vsize_re0) + (j9_re0)]
                j9_re0 = (j9_re0) + (S32(1))
            # Recursive loop 7 
            # Pre code 
            var j6_re0 = S32(0)
            comptime dtype12 = f64
            comptime width12 = S32(simd_width_of[dtype12]())
            while j6_re0 <= S32(4) - width12:
                var values = simd_load(dsp.rec3_perm, j6_re0)
                simd_store(rec3_tmp, j6_re0, values)
                j6_re0 = j6_re0 + S32(width12)
            var j10_re0 = S32(0)
            comptime dtype13 = f64
            comptime width13 = S32(simd_width_of[dtype13]())
            while j10_re0 <= S32(4) - width13:
                var values = simd_load(dsp.rec4_perm, j10_re0)
                simd_store(rec4_tmp, j10_re0, values)
                j10_re0 = j10_re0 + S32(width13)
            # Compute code 
            var i_re7 = S32(0)
            while (i_re7) < (vsize_re0): 
                rec3[i_re7] = ((rec4[(i_re7) - (S32(1))]) * (zec1[i_re7])) + ((rec3[(i_re7) - (S32(1))]) * (zec2[i_re7]))
                rec4[i_re7] = ((F64((S32(1)) - (i_vec0[(i_re7) - (S32(1))]))) + ((rec4[(i_re7) - (S32(1))]) * (zec2[i_re7]))) - ((zec1[i_re7]) * (rec3[(i_re7) - (S32(1))]))
                i_re7 = (i_re7) + (S32(1))
            # Post code 
            var j7_re0 = S32(0)
            while (j7_re0) < (S32(4)): 
                dsp.rec3_perm[j7_re0] = rec3_tmp[(vsize_re0) + (j7_re0)]
                j7_re0 = (j7_re0) + (S32(1))
            var j11_re0 = S32(0)
            while (j11_re0) < (S32(4)): 
                dsp.rec4_perm[j11_re0] = rec4_tmp[(vsize_re0) + (j11_re0)]
                j11_re0 = (j11_re0) + (S32(1))
            # Recursive loop 8 
            # Pre code 
            var j12_re0 = S32(0)
            comptime dtype16 = f64
            comptime width16 = S32(simd_width_of[dtype16]())
            while j12_re0 <= S32(4) - width16:
                var values = simd_load(dsp.rec6_perm, j12_re0)
                simd_store(rec6_tmp, j12_re0, values)
                j12_re0 = j12_re0 + S32(width16)
            # Compute code 
            var i_re8 = S32(0)
            while (i_re8) < (vsize_re0): 
                rec6[i_re8] = (slow5) + ((0.999) * (rec6[(i_re8) - (S32(1))]))
                i_re8 = (i_re8) + (S32(1))
            # Post code 
            var j13_re0 = S32(0)
            while (j13_re0) < (S32(4)): 
                dsp.rec6_perm[j13_re0] = rec6_tmp[(vsize_re0) + (j13_re0)]
                j13_re0 = (j13_re0) + (S32(1))
            # Vectorizable loop 9 
            # Compute code 
            var i_re9 = S32(0)
            comptime dtype18 = f64
            comptime width18 = S32(simd_width_of[dtype18]())
            while i_re9 <= vsize_re0 - width18:
                var values = (simd_load(rec2, i_re9)) * (simd_load(rec3, i_re9))
                simd_store(zec3, i_re9, values)
                i_re9 = i_re9 + S32(width18)
            # Vectorizable loop 10 
            # Compute code 
            var i_re10 = S32(0)
            comptime dtype19 = f64
            comptime width19 = S32(simd_width_of[dtype19]())
            while i_re10 <= vsize_re0 - width19:
                var values = max(-1.0, min(1.0, (simd_load(rec1, i_re10)) + ((0.0 if i_slow6 else simd_load(zec3, i_re10)) * (pow(1e+01, (2.0) * (simd_load(rec6, i_re10)))))))
                simd_store(zec4, i_re10, values)
                i_re10 = i_re10 + S32(width19)
            # Vectorizable loop 11 
            # Pre code 
            var j14_re0 = S32(0)
            comptime dtype20 = f64
            comptime width20 = S32(simd_width_of[dtype20]())
            while j14_re0 <= S32(4) - width20:
                var values = simd_load(dsp.yec0_perm, j14_re0)
                simd_store(yec0_tmp, j14_re0, values)
                j14_re0 = j14_re0 + S32(width20)
            # Compute code 
            var i_re11 = S32(0)
            comptime dtype21 = f64
            comptime width21 = S32(simd_width_of[dtype21]())
            while i_re11 <= vsize_re0 - width21:
                var values = (simd_load(zec4, i_re11)) * ((1.0) - ((0.3333333333333333) * (pow_unrolled[2](simd_load(zec4, i_re11)))))
                simd_store(yec0, i_re11, values)
                i_re11 = i_re11 + S32(width21)
            # Post code 
            var j15_re0 = S32(0)
            while (j15_re0) < (S32(4)): 
                dsp.yec0_perm[j15_re0] = yec0_tmp[(vsize_re0) + (j15_re0)]
                j15_re0 = (j15_re0) + (S32(1))
            # Recursive loop 12 
            # Pre code 
            var j16_re0 = S32(0)
            comptime dtype23 = f64
            comptime width23 = S32(simd_width_of[dtype23]())
            while j16_re0 <= S32(4) - width23:
                var values = simd_load(dsp.rec0_perm, j16_re0)
                simd_store(rec0_tmp, j16_re0, values)
                j16_re0 = j16_re0 + S32(width23)
            # Compute code 
            var i_re12 = S32(0)
            while (i_re12) < (vsize_re0): 
                rec0[i_re12] = (((0.995) * (rec0[(i_re12) - (S32(1))])) + (yec0[i_re12])) - (yec0[(i_re12) - (S32(1))])
                i_re12 = (i_re12) + (S32(1))
            # Post code 
            var j17_re0 = S32(0)
            while (j17_re0) < (S32(4)): 
                dsp.rec0_perm[j17_re0] = rec0_tmp[(vsize_re0) + (j17_re0)]
                j17_re0 = (j17_re0) + (S32(1))
            # Vectorizable loop 13 
            # Compute code 
            var i_re13 = S32(0)
            comptime dtype25 = f64
            comptime width25 = S32(simd_width_of[dtype25]())
            while i_re13 <= vsize_re0 - width25:
                var values = simd_load(zec3, i_re13) if i_slow6 else simd_load(rec0, i_re13)
                simd_store(zec5, i_re13, values)
                i_re13 = i_re13 + S32(width25)
            # Recursive loop 14 
            # Pre code 
            var j18_re0 = S32(0)
            comptime dtype26 = f64
            comptime width26 = S32(simd_width_of[dtype26]())
            while j18_re0 <= S32(4) - width26:
                var values = simd_load(dsp.rec10_perm, j18_re0)
                simd_store(rec10_tmp, j18_re0, values)
                j18_re0 = j18_re0 + S32(width26)
            # Compute code 
            var i_re14 = S32(0)
            while (i_re14) < (vsize_re0): 
                rec10[i_re14] = (zec5[i_re14]) - ((dsp.const5) * (((dsp.const6) * (rec10[(i_re14) - (S32(2))])) + ((dsp.const9) * (rec10[(i_re14) - (S32(1))]))))
                i_re14 = (i_re14) + (S32(1))
            # Post code 
            var j19_re0 = S32(0)
            while (j19_re0) < (S32(4)): 
                dsp.rec10_perm[j19_re0] = rec10_tmp[(vsize_re0) + (j19_re0)]
                j19_re0 = (j19_re0) + (S32(1))
            # Recursive loop 15 
            # Pre code 
            var j20_re0 = S32(0)
            comptime dtype28 = f64
            comptime width28 = S32(simd_width_of[dtype28]())
            while j20_re0 <= S32(4) - width28:
                var values = simd_load(dsp.rec9_perm, j20_re0)
                simd_store(rec9_tmp, j20_re0, values)
                j20_re0 = j20_re0 + S32(width28)
            # Compute code 
            var i_re15 = S32(0)
            while (i_re15) < (vsize_re0): 
                rec9[i_re15] = ((dsp.const5) * ((((dsp.const11) * (rec10[i_re15])) + ((dsp.const12) * (rec10[(i_re15) - (S32(1))]))) + ((dsp.const11) * (rec10[(i_re15) - (S32(2))])))) - ((dsp.const13) * (((dsp.const14) * (rec9[(i_re15) - (S32(2))])) + ((dsp.const15) * (rec9[(i_re15) - (S32(1))]))))
                i_re15 = (i_re15) + (S32(1))
            # Post code 
            var j21_re0 = S32(0)
            while (j21_re0) < (S32(4)): 
                dsp.rec9_perm[j21_re0] = rec9_tmp[(vsize_re0) + (j21_re0)]
                j21_re0 = (j21_re0) + (S32(1))
            # Recursive loop 16 
            # Pre code 
            var j22_re0 = S32(0)
            comptime dtype30 = f64
            comptime width30 = S32(simd_width_of[dtype30]())
            while j22_re0 <= S32(4) - width30:
                var values = simd_load(dsp.rec8_perm, j22_re0)
                simd_store(rec8_tmp, j22_re0, values)
                j22_re0 = j22_re0 + S32(width30)
            # Compute code 
            var i_re16 = S32(0)
            while (i_re16) < (vsize_re0): 
                rec8[i_re16] = ((dsp.const13) * ((((dsp.const17) * (rec9[i_re16])) + ((dsp.const18) * (rec9[(i_re16) - (S32(1))]))) + ((dsp.const17) * (rec9[(i_re16) - (S32(2))])))) - ((dsp.const19) * (((dsp.const20) * (rec8[(i_re16) - (S32(2))])) + ((dsp.const21) * (rec8[(i_re16) - (S32(1))]))))
                i_re16 = (i_re16) + (S32(1))
            # Post code 
            var j23_re0 = S32(0)
            while (j23_re0) < (S32(4)): 
                dsp.rec8_perm[j23_re0] = rec8_tmp[(vsize_re0) + (j23_re0)]
                j23_re0 = (j23_re0) + (S32(1))
            # Recursive loop 17 
            # Pre code 
            var j24_re0 = S32(0)
            comptime dtype32 = f64
            comptime width32 = S32(simd_width_of[dtype32]())
            while j24_re0 <= S32(4) - width32:
                var values = simd_load(dsp.rec7_perm, j24_re0)
                simd_store(rec7_tmp, j24_re0, values)
                j24_re0 = j24_re0 + S32(width32)
            # Compute code 
            var i_re17 = S32(0)
            while (i_re17) < (vsize_re0): 
                rec7[i_re17] = ((rec7[(i_re17) - (S32(1))]) * (slow8)) + ((abs((dsp.const19) * ((((dsp.const24) * (rec8[i_re17])) + ((dsp.const25) * (rec8[(i_re17) - (S32(1))]))) + ((dsp.const24) * (rec8[(i_re17) - (S32(2))]))))) * (slow9))
                i_re17 = (i_re17) + (S32(1))
            # Post code 
            var j25_re0 = S32(0)
            while (j25_re0) < (S32(4)): 
                dsp.rec7_perm[j25_re0] = rec7_tmp[(vsize_re0) + (j25_re0)]
                j25_re0 = (j25_re0) + (S32(1))
            # Recursive loop 18 
            # Pre code 
            var j26_re0 = S32(0)
            comptime dtype34 = f64
            comptime width34 = S32(simd_width_of[dtype34]())
            while j26_re0 <= S32(4) - width34:
                var values = simd_load(dsp.rec17_perm, j26_re0)
                simd_store(rec17_tmp, j26_re0, values)
                j26_re0 = j26_re0 + S32(width34)
            # Compute code 
            var i_re18 = S32(0)
            while (i_re18) < (vsize_re0): 
                rec17[i_re18] = (zec5[i_re18]) - ((dsp.const26) * (((dsp.const27) * (rec17[(i_re18) - (S32(2))])) + ((dsp.const28) * (rec17[(i_re18) - (S32(1))]))))
                i_re18 = (i_re18) + (S32(1))
            # Post code 
            var j27_re0 = S32(0)
            while (j27_re0) < (S32(4)): 
                dsp.rec17_perm[j27_re0] = rec17_tmp[(vsize_re0) + (j27_re0)]
                j27_re0 = (j27_re0) + (S32(1))
            # Recursive loop 19 
            # Pre code 
            var j28_re0 = S32(0)
            comptime dtype36 = f64
            comptime width36 = S32(simd_width_of[dtype36]())
            while j28_re0 <= S32(4) - width36:
                var values = simd_load(dsp.rec16_perm, j28_re0)
                simd_store(rec16_tmp, j28_re0, values)
                j28_re0 = j28_re0 + S32(width36)
            # Compute code 
            var i_re19 = S32(0)
            while (i_re19) < (vsize_re0): 
                rec16[i_re19] = ((dsp.const26) * ((((dsp.const30) * (rec17[i_re19])) + ((dsp.const31) * (rec17[(i_re19) - (S32(1))]))) + ((dsp.const30) * (rec17[(i_re19) - (S32(2))])))) - ((dsp.const32) * (((dsp.const33) * (rec16[(i_re19) - (S32(2))])) + ((dsp.const34) * (rec16[(i_re19) - (S32(1))]))))
                i_re19 = (i_re19) + (S32(1))
            # Post code 
            var j29_re0 = S32(0)
            while (j29_re0) < (S32(4)): 
                dsp.rec16_perm[j29_re0] = rec16_tmp[(vsize_re0) + (j29_re0)]
                j29_re0 = (j29_re0) + (S32(1))
            # Recursive loop 20 
            # Pre code 
            var j30_re0 = S32(0)
            comptime dtype38 = f64
            comptime width38 = S32(simd_width_of[dtype38]())
            while j30_re0 <= S32(4) - width38:
                var values = simd_load(dsp.rec15_perm, j30_re0)
                simd_store(rec15_tmp, j30_re0, values)
                j30_re0 = j30_re0 + S32(width38)
            # Compute code 
            var i_re20 = S32(0)
            while (i_re20) < (vsize_re0): 
                rec15[i_re20] = ((dsp.const32) * ((((dsp.const35) * (rec16[i_re20])) + ((dsp.const36) * (rec16[(i_re20) - (S32(1))]))) + ((dsp.const35) * (rec16[(i_re20) - (S32(2))])))) - ((dsp.const37) * (((dsp.const38) * (rec15[(i_re20) - (S32(2))])) + ((dsp.const39) * (rec15[(i_re20) - (S32(1))]))))
                i_re20 = (i_re20) + (S32(1))
            # Post code 
            var j31_re0 = S32(0)
            while (j31_re0) < (S32(4)): 
                dsp.rec15_perm[j31_re0] = rec15_tmp[(vsize_re0) + (j31_re0)]
                j31_re0 = (j31_re0) + (S32(1))
            # Vectorizable loop 21 
            # Compute code 
            var i_re21 = S32(0)
            comptime dtype40 = f64
            comptime width40 = S32(simd_width_of[dtype40]())
            while i_re21 <= vsize_re0 - width40:
                var values = (dsp.const37) * ((((dsp.const40) * (simd_load(rec15, i_re21))) + ((dsp.const41) * (simd_load(rec15, i_re21 - S32(1))))) + ((dsp.const40) * (simd_load(rec15, i_re21 - S32(2)))))
                simd_store(zec6, i_re21, values)
                i_re21 = i_re21 + S32(width40)
            # Recursive loop 22 
            # Pre code 
            var j32_re0 = S32(0)
            comptime dtype41 = f64
            comptime width41 = S32(simd_width_of[dtype41]())
            while j32_re0 <= S32(4) - width41:
                var values = simd_load(dsp.rec14_perm, j32_re0)
                simd_store(rec14_tmp, j32_re0, values)
                j32_re0 = j32_re0 + S32(width41)
            # Compute code 
            var i_re22 = S32(0)
            while (i_re22) < (vsize_re0): 
                rec14[i_re22] = (zec6[i_re22]) - ((dsp.const44) * (((dsp.const45) * (rec14[(i_re22) - (S32(2))])) + ((dsp.const48) * (rec14[(i_re22) - (S32(1))]))))
                i_re22 = (i_re22) + (S32(1))
            # Post code 
            var j33_re0 = S32(0)
            while (j33_re0) < (S32(4)): 
                dsp.rec14_perm[j33_re0] = rec14_tmp[(vsize_re0) + (j33_re0)]
                j33_re0 = (j33_re0) + (S32(1))
            # Recursive loop 23 
            # Pre code 
            var j34_re0 = S32(0)
            comptime dtype43 = f64
            comptime width43 = S32(simd_width_of[dtype43]())
            while j34_re0 <= S32(4) - width43:
                var values = simd_load(dsp.rec13_perm, j34_re0)
                simd_store(rec13_tmp, j34_re0, values)
                j34_re0 = j34_re0 + S32(width43)
            # Compute code 
            var i_re23 = S32(0)
            while (i_re23) < (vsize_re0): 
                rec13[i_re23] = ((dsp.const44) * ((((dsp.const50) * (rec14[i_re23])) + ((dsp.const51) * (rec14[(i_re23) - (S32(1))]))) + ((dsp.const50) * (rec14[(i_re23) - (S32(2))])))) - ((dsp.const52) * (((dsp.const53) * (rec13[(i_re23) - (S32(2))])) + ((dsp.const54) * (rec13[(i_re23) - (S32(1))]))))
                i_re23 = (i_re23) + (S32(1))
            # Post code 
            var j35_re0 = S32(0)
            while (j35_re0) < (S32(4)): 
                dsp.rec13_perm[j35_re0] = rec13_tmp[(vsize_re0) + (j35_re0)]
                j35_re0 = (j35_re0) + (S32(1))
            # Recursive loop 24 
            # Pre code 
            var j36_re0 = S32(0)
            comptime dtype45 = f64
            comptime width45 = S32(simd_width_of[dtype45]())
            while j36_re0 <= S32(4) - width45:
                var values = simd_load(dsp.rec12_perm, j36_re0)
                simd_store(rec12_tmp, j36_re0, values)
                j36_re0 = j36_re0 + S32(width45)
            # Compute code 
            var i_re24 = S32(0)
            while (i_re24) < (vsize_re0): 
                rec12[i_re24] = ((dsp.const52) * ((((dsp.const56) * (rec13[i_re24])) + ((dsp.const57) * (rec13[(i_re24) - (S32(1))]))) + ((dsp.const56) * (rec13[(i_re24) - (S32(2))])))) - ((dsp.const58) * (((dsp.const59) * (rec12[(i_re24) - (S32(2))])) + ((dsp.const60) * (rec12[(i_re24) - (S32(1))]))))
                i_re24 = (i_re24) + (S32(1))
            # Post code 
            var j37_re0 = S32(0)
            while (j37_re0) < (S32(4)): 
                dsp.rec12_perm[j37_re0] = rec12_tmp[(vsize_re0) + (j37_re0)]
                j37_re0 = (j37_re0) + (S32(1))
            # Recursive loop 25 
            # Pre code 
            var j38_re0 = S32(0)
            comptime dtype47 = f64
            comptime width47 = S32(simd_width_of[dtype47]())
            while j38_re0 <= S32(4) - width47:
                var values = simd_load(dsp.rec11_perm, j38_re0)
                simd_store(rec11_tmp, j38_re0, values)
                j38_re0 = j38_re0 + S32(width47)
            # Compute code 
            var i_re25 = S32(0)
            while (i_re25) < (vsize_re0): 
                rec11[i_re25] = ((slow8) * (rec11[(i_re25) - (S32(1))])) + ((slow9) * (abs((dsp.const58) * ((((dsp.const62) * (rec12[i_re25])) + ((dsp.const63) * (rec12[(i_re25) - (S32(1))]))) + ((dsp.const62) * (rec12[(i_re25) - (S32(2))]))))))
                i_re25 = (i_re25) + (S32(1))
            # Post code 
            var j39_re0 = S32(0)
            while (j39_re0) < (S32(4)): 
                dsp.rec11_perm[j39_re0] = rec11_tmp[(vsize_re0) + (j39_re0)]
                j39_re0 = (j39_re0) + (S32(1))
            # Recursive loop 26 
            # Pre code 
            var j40_re0 = S32(0)
            comptime dtype49 = f64
            comptime width49 = S32(simd_width_of[dtype49]())
            while j40_re0 <= S32(4) - width49:
                var values = simd_load(dsp.rec24_perm, j40_re0)
                simd_store(rec24_tmp, j40_re0, values)
                j40_re0 = j40_re0 + S32(width49)
            # Compute code 
            var i_re26 = S32(0)
            while (i_re26) < (vsize_re0): 
                rec24[i_re26] = (zec6[i_re26]) - ((dsp.const64) * (((dsp.const65) * (rec24[(i_re26) - (S32(2))])) + ((dsp.const66) * (rec24[(i_re26) - (S32(1))]))))
                i_re26 = (i_re26) + (S32(1))
            # Post code 
            var j41_re0 = S32(0)
            while (j41_re0) < (S32(4)): 
                dsp.rec24_perm[j41_re0] = rec24_tmp[(vsize_re0) + (j41_re0)]
                j41_re0 = (j41_re0) + (S32(1))
            # Recursive loop 27 
            # Pre code 
            var j42_re0 = S32(0)
            comptime dtype51 = f64
            comptime width51 = S32(simd_width_of[dtype51]())
            while j42_re0 <= S32(4) - width51:
                var values = simd_load(dsp.rec23_perm, j42_re0)
                simd_store(rec23_tmp, j42_re0, values)
                j42_re0 = j42_re0 + S32(width51)
            # Compute code 
            var i_re27 = S32(0)
            while (i_re27) < (vsize_re0): 
                rec23[i_re27] = ((dsp.const64) * ((((dsp.const68) * (rec24[i_re27])) + ((dsp.const69) * (rec24[(i_re27) - (S32(1))]))) + ((dsp.const68) * (rec24[(i_re27) - (S32(2))])))) - ((dsp.const70) * (((dsp.const71) * (rec23[(i_re27) - (S32(2))])) + ((dsp.const72) * (rec23[(i_re27) - (S32(1))]))))
                i_re27 = (i_re27) + (S32(1))
            # Post code 
            var j43_re0 = S32(0)
            while (j43_re0) < (S32(4)): 
                dsp.rec23_perm[j43_re0] = rec23_tmp[(vsize_re0) + (j43_re0)]
                j43_re0 = (j43_re0) + (S32(1))
            # Recursive loop 28 
            # Pre code 
            var j44_re0 = S32(0)
            comptime dtype53 = f64
            comptime width53 = S32(simd_width_of[dtype53]())
            while j44_re0 <= S32(4) - width53:
                var values = simd_load(dsp.rec22_perm, j44_re0)
                simd_store(rec22_tmp, j44_re0, values)
                j44_re0 = j44_re0 + S32(width53)
            # Compute code 
            var i_re28 = S32(0)
            while (i_re28) < (vsize_re0): 
                rec22[i_re28] = ((dsp.const70) * ((((dsp.const73) * (rec23[i_re28])) + ((dsp.const74) * (rec23[(i_re28) - (S32(1))]))) + ((dsp.const73) * (rec23[(i_re28) - (S32(2))])))) - ((dsp.const75) * (((dsp.const76) * (rec22[(i_re28) - (S32(2))])) + ((dsp.const77) * (rec22[(i_re28) - (S32(1))]))))
                i_re28 = (i_re28) + (S32(1))
            # Post code 
            var j45_re0 = S32(0)
            while (j45_re0) < (S32(4)): 
                dsp.rec22_perm[j45_re0] = rec22_tmp[(vsize_re0) + (j45_re0)]
                j45_re0 = (j45_re0) + (S32(1))
            # Vectorizable loop 29 
            # Compute code 
            var i_re29 = S32(0)
            comptime dtype55 = f64
            comptime width55 = S32(simd_width_of[dtype55]())
            while i_re29 <= vsize_re0 - width55:
                var values = (dsp.const75) * ((((dsp.const78) * (simd_load(rec22, i_re29))) + ((dsp.const79) * (simd_load(rec22, i_re29 - S32(1))))) + ((dsp.const78) * (simd_load(rec22, i_re29 - S32(2)))))
                simd_store(zec7, i_re29, values)
                i_re29 = i_re29 + S32(width55)
            # Recursive loop 30 
            # Pre code 
            var j46_re0 = S32(0)
            comptime dtype56 = f64
            comptime width56 = S32(simd_width_of[dtype56]())
            while j46_re0 <= S32(4) - width56:
                var values = simd_load(dsp.rec21_perm, j46_re0)
                simd_store(rec21_tmp, j46_re0, values)
                j46_re0 = j46_re0 + S32(width56)
            # Compute code 
            var i_re30 = S32(0)
            while (i_re30) < (vsize_re0): 
                rec21[i_re30] = (zec7[i_re30]) - ((dsp.const82) * (((dsp.const83) * (rec21[(i_re30) - (S32(2))])) + ((dsp.const86) * (rec21[(i_re30) - (S32(1))]))))
                i_re30 = (i_re30) + (S32(1))
            # Post code 
            var j47_re0 = S32(0)
            while (j47_re0) < (S32(4)): 
                dsp.rec21_perm[j47_re0] = rec21_tmp[(vsize_re0) + (j47_re0)]
                j47_re0 = (j47_re0) + (S32(1))
            # Recursive loop 31 
            # Pre code 
            var j48_re0 = S32(0)
            comptime dtype58 = f64
            comptime width58 = S32(simd_width_of[dtype58]())
            while j48_re0 <= S32(4) - width58:
                var values = simd_load(dsp.rec20_perm, j48_re0)
                simd_store(rec20_tmp, j48_re0, values)
                j48_re0 = j48_re0 + S32(width58)
            # Compute code 
            var i_re31 = S32(0)
            while (i_re31) < (vsize_re0): 
                rec20[i_re31] = ((dsp.const82) * ((((dsp.const88) * (rec21[i_re31])) + ((dsp.const89) * (rec21[(i_re31) - (S32(1))]))) + ((dsp.const88) * (rec21[(i_re31) - (S32(2))])))) - ((dsp.const90) * (((dsp.const91) * (rec20[(i_re31) - (S32(2))])) + ((dsp.const92) * (rec20[(i_re31) - (S32(1))]))))
                i_re31 = (i_re31) + (S32(1))
            # Post code 
            var j49_re0 = S32(0)
            while (j49_re0) < (S32(4)): 
                dsp.rec20_perm[j49_re0] = rec20_tmp[(vsize_re0) + (j49_re0)]
                j49_re0 = (j49_re0) + (S32(1))
            # Recursive loop 32 
            # Pre code 
            var j50_re0 = S32(0)
            comptime dtype60 = f64
            comptime width60 = S32(simd_width_of[dtype60]())
            while j50_re0 <= S32(4) - width60:
                var values = simd_load(dsp.rec19_perm, j50_re0)
                simd_store(rec19_tmp, j50_re0, values)
                j50_re0 = j50_re0 + S32(width60)
            # Compute code 
            var i_re32 = S32(0)
            while (i_re32) < (vsize_re0): 
                rec19[i_re32] = ((dsp.const90) * ((((dsp.const94) * (rec20[i_re32])) + ((dsp.const95) * (rec20[(i_re32) - (S32(1))]))) + ((dsp.const94) * (rec20[(i_re32) - (S32(2))])))) - ((dsp.const96) * (((dsp.const97) * (rec19[(i_re32) - (S32(2))])) + ((dsp.const98) * (rec19[(i_re32) - (S32(1))]))))
                i_re32 = (i_re32) + (S32(1))
            # Post code 
            var j51_re0 = S32(0)
            while (j51_re0) < (S32(4)): 
                dsp.rec19_perm[j51_re0] = rec19_tmp[(vsize_re0) + (j51_re0)]
                j51_re0 = (j51_re0) + (S32(1))
            # Recursive loop 33 
            # Pre code 
            var j52_re0 = S32(0)
            comptime dtype62 = f64
            comptime width62 = S32(simd_width_of[dtype62]())
            while j52_re0 <= S32(4) - width62:
                var values = simd_load(dsp.rec18_perm, j52_re0)
                simd_store(rec18_tmp, j52_re0, values)
                j52_re0 = j52_re0 + S32(width62)
            # Compute code 
            var i_re33 = S32(0)
            while (i_re33) < (vsize_re0): 
                rec18[i_re33] = ((slow8) * (rec18[(i_re33) - (S32(1))])) + ((slow9) * (abs((dsp.const96) * ((((dsp.const100) * (rec19[i_re33])) + ((dsp.const101) * (rec19[(i_re33) - (S32(1))]))) + ((dsp.const100) * (rec19[(i_re33) - (S32(2))]))))))
                i_re33 = (i_re33) + (S32(1))
            # Post code 
            var j53_re0 = S32(0)
            while (j53_re0) < (S32(4)): 
                dsp.rec18_perm[j53_re0] = rec18_tmp[(vsize_re0) + (j53_re0)]
                j53_re0 = (j53_re0) + (S32(1))
            # Recursive loop 34 
            # Pre code 
            var j54_re0 = S32(0)
            comptime dtype64 = f64
            comptime width64 = S32(simd_width_of[dtype64]())
            while j54_re0 <= S32(4) - width64:
                var values = simd_load(dsp.rec31_perm, j54_re0)
                simd_store(rec31_tmp, j54_re0, values)
                j54_re0 = j54_re0 + S32(width64)
            # Compute code 
            var i_re34 = S32(0)
            while (i_re34) < (vsize_re0): 
                rec31[i_re34] = (zec7[i_re34]) - ((dsp.const102) * (((dsp.const103) * (rec31[(i_re34) - (S32(2))])) + ((dsp.const104) * (rec31[(i_re34) - (S32(1))]))))
                i_re34 = (i_re34) + (S32(1))
            # Post code 
            var j55_re0 = S32(0)
            while (j55_re0) < (S32(4)): 
                dsp.rec31_perm[j55_re0] = rec31_tmp[(vsize_re0) + (j55_re0)]
                j55_re0 = (j55_re0) + (S32(1))
            # Recursive loop 35 
            # Pre code 
            var j56_re0 = S32(0)
            comptime dtype66 = f64
            comptime width66 = S32(simd_width_of[dtype66]())
            while j56_re0 <= S32(4) - width66:
                var values = simd_load(dsp.rec30_perm, j56_re0)
                simd_store(rec30_tmp, j56_re0, values)
                j56_re0 = j56_re0 + S32(width66)
            # Compute code 
            var i_re35 = S32(0)
            while (i_re35) < (vsize_re0): 
                rec30[i_re35] = ((dsp.const102) * ((((dsp.const106) * (rec31[i_re35])) + ((dsp.const107) * (rec31[(i_re35) - (S32(1))]))) + ((dsp.const106) * (rec31[(i_re35) - (S32(2))])))) - ((dsp.const108) * (((dsp.const109) * (rec30[(i_re35) - (S32(2))])) + ((dsp.const110) * (rec30[(i_re35) - (S32(1))]))))
                i_re35 = (i_re35) + (S32(1))
            # Post code 
            var j57_re0 = S32(0)
            while (j57_re0) < (S32(4)): 
                dsp.rec30_perm[j57_re0] = rec30_tmp[(vsize_re0) + (j57_re0)]
                j57_re0 = (j57_re0) + (S32(1))
            # Recursive loop 36 
            # Pre code 
            var j58_re0 = S32(0)
            comptime dtype68 = f64
            comptime width68 = S32(simd_width_of[dtype68]())
            while j58_re0 <= S32(4) - width68:
                var values = simd_load(dsp.rec29_perm, j58_re0)
                simd_store(rec29_tmp, j58_re0, values)
                j58_re0 = j58_re0 + S32(width68)
            # Compute code 
            var i_re36 = S32(0)
            while (i_re36) < (vsize_re0): 
                rec29[i_re36] = ((dsp.const108) * ((((dsp.const111) * (rec30[i_re36])) + ((dsp.const112) * (rec30[(i_re36) - (S32(1))]))) + ((dsp.const111) * (rec30[(i_re36) - (S32(2))])))) - ((dsp.const113) * (((dsp.const114) * (rec29[(i_re36) - (S32(2))])) + ((dsp.const115) * (rec29[(i_re36) - (S32(1))]))))
                i_re36 = (i_re36) + (S32(1))
            # Post code 
            var j59_re0 = S32(0)
            while (j59_re0) < (S32(4)): 
                dsp.rec29_perm[j59_re0] = rec29_tmp[(vsize_re0) + (j59_re0)]
                j59_re0 = (j59_re0) + (S32(1))
            # Vectorizable loop 37 
            # Compute code 
            var i_re37 = S32(0)
            comptime dtype70 = f64
            comptime width70 = S32(simd_width_of[dtype70]())
            while i_re37 <= vsize_re0 - width70:
                var values = (dsp.const113) * ((((dsp.const116) * (simd_load(rec29, i_re37))) + ((dsp.const117) * (simd_load(rec29, i_re37 - S32(1))))) + ((dsp.const116) * (simd_load(rec29, i_re37 - S32(2)))))
                simd_store(zec8, i_re37, values)
                i_re37 = i_re37 + S32(width70)
            # Recursive loop 38 
            # Pre code 
            var j60_re0 = S32(0)
            comptime dtype71 = f64
            comptime width71 = S32(simd_width_of[dtype71]())
            while j60_re0 <= S32(4) - width71:
                var values = simd_load(dsp.rec28_perm, j60_re0)
                simd_store(rec28_tmp, j60_re0, values)
                j60_re0 = j60_re0 + S32(width71)
            # Compute code 
            var i_re38 = S32(0)
            while (i_re38) < (vsize_re0): 
                rec28[i_re38] = (zec8[i_re38]) - ((dsp.const120) * (((dsp.const121) * (rec28[(i_re38) - (S32(2))])) + ((dsp.const124) * (rec28[(i_re38) - (S32(1))]))))
                i_re38 = (i_re38) + (S32(1))
            # Post code 
            var j61_re0 = S32(0)
            while (j61_re0) < (S32(4)): 
                dsp.rec28_perm[j61_re0] = rec28_tmp[(vsize_re0) + (j61_re0)]
                j61_re0 = (j61_re0) + (S32(1))
            # Recursive loop 39 
            # Pre code 
            var j62_re0 = S32(0)
            comptime dtype73 = f64
            comptime width73 = S32(simd_width_of[dtype73]())
            while j62_re0 <= S32(4) - width73:
                var values = simd_load(dsp.rec27_perm, j62_re0)
                simd_store(rec27_tmp, j62_re0, values)
                j62_re0 = j62_re0 + S32(width73)
            # Compute code 
            var i_re39 = S32(0)
            while (i_re39) < (vsize_re0): 
                rec27[i_re39] = ((dsp.const120) * ((((dsp.const126) * (rec28[i_re39])) + ((dsp.const127) * (rec28[(i_re39) - (S32(1))]))) + ((dsp.const126) * (rec28[(i_re39) - (S32(2))])))) - ((dsp.const128) * (((dsp.const129) * (rec27[(i_re39) - (S32(2))])) + ((dsp.const130) * (rec27[(i_re39) - (S32(1))]))))
                i_re39 = (i_re39) + (S32(1))
            # Post code 
            var j63_re0 = S32(0)
            while (j63_re0) < (S32(4)): 
                dsp.rec27_perm[j63_re0] = rec27_tmp[(vsize_re0) + (j63_re0)]
                j63_re0 = (j63_re0) + (S32(1))
            # Recursive loop 40 
            # Pre code 
            var j64_re0 = S32(0)
            comptime dtype75 = f64
            comptime width75 = S32(simd_width_of[dtype75]())
            while j64_re0 <= S32(4) - width75:
                var values = simd_load(dsp.rec26_perm, j64_re0)
                simd_store(rec26_tmp, j64_re0, values)
                j64_re0 = j64_re0 + S32(width75)
            # Compute code 
            var i_re40 = S32(0)
            while (i_re40) < (vsize_re0): 
                rec26[i_re40] = ((dsp.const128) * ((((dsp.const132) * (rec27[i_re40])) + ((dsp.const133) * (rec27[(i_re40) - (S32(1))]))) + ((dsp.const132) * (rec27[(i_re40) - (S32(2))])))) - ((dsp.const134) * (((dsp.const135) * (rec26[(i_re40) - (S32(2))])) + ((dsp.const136) * (rec26[(i_re40) - (S32(1))]))))
                i_re40 = (i_re40) + (S32(1))
            # Post code 
            var j65_re0 = S32(0)
            while (j65_re0) < (S32(4)): 
                dsp.rec26_perm[j65_re0] = rec26_tmp[(vsize_re0) + (j65_re0)]
                j65_re0 = (j65_re0) + (S32(1))
            # Recursive loop 41 
            # Pre code 
            var j66_re0 = S32(0)
            comptime dtype77 = f64
            comptime width77 = S32(simd_width_of[dtype77]())
            while j66_re0 <= S32(4) - width77:
                var values = simd_load(dsp.rec25_perm, j66_re0)
                simd_store(rec25_tmp, j66_re0, values)
                j66_re0 = j66_re0 + S32(width77)
            # Compute code 
            var i_re41 = S32(0)
            while (i_re41) < (vsize_re0): 
                rec25[i_re41] = ((slow8) * (rec25[(i_re41) - (S32(1))])) + ((slow9) * (abs((dsp.const134) * ((((dsp.const138) * (rec26[i_re41])) + ((dsp.const139) * (rec26[(i_re41) - (S32(1))]))) + ((dsp.const138) * (rec26[(i_re41) - (S32(2))]))))))
                i_re41 = (i_re41) + (S32(1))
            # Post code 
            var j67_re0 = S32(0)
            while (j67_re0) < (S32(4)): 
                dsp.rec25_perm[j67_re0] = rec25_tmp[(vsize_re0) + (j67_re0)]
                j67_re0 = (j67_re0) + (S32(1))
            # Recursive loop 42 
            # Pre code 
            var j68_re0 = S32(0)
            comptime dtype79 = f64
            comptime width79 = S32(simd_width_of[dtype79]())
            while j68_re0 <= S32(4) - width79:
                var values = simd_load(dsp.rec38_perm, j68_re0)
                simd_store(rec38_tmp, j68_re0, values)
                j68_re0 = j68_re0 + S32(width79)
            # Compute code 
            var i_re42 = S32(0)
            while (i_re42) < (vsize_re0): 
                rec38[i_re42] = (zec8[i_re42]) - ((dsp.const140) * (((dsp.const141) * (rec38[(i_re42) - (S32(2))])) + ((dsp.const142) * (rec38[(i_re42) - (S32(1))]))))
                i_re42 = (i_re42) + (S32(1))
            # Post code 
            var j69_re0 = S32(0)
            while (j69_re0) < (S32(4)): 
                dsp.rec38_perm[j69_re0] = rec38_tmp[(vsize_re0) + (j69_re0)]
                j69_re0 = (j69_re0) + (S32(1))
            # Recursive loop 43 
            # Pre code 
            var j70_re0 = S32(0)
            comptime dtype81 = f64
            comptime width81 = S32(simd_width_of[dtype81]())
            while j70_re0 <= S32(4) - width81:
                var values = simd_load(dsp.rec37_perm, j70_re0)
                simd_store(rec37_tmp, j70_re0, values)
                j70_re0 = j70_re0 + S32(width81)
            # Compute code 
            var i_re43 = S32(0)
            while (i_re43) < (vsize_re0): 
                rec37[i_re43] = ((dsp.const140) * ((((dsp.const144) * (rec38[i_re43])) + ((dsp.const145) * (rec38[(i_re43) - (S32(1))]))) + ((dsp.const144) * (rec38[(i_re43) - (S32(2))])))) - ((dsp.const146) * (((dsp.const147) * (rec37[(i_re43) - (S32(2))])) + ((dsp.const148) * (rec37[(i_re43) - (S32(1))]))))
                i_re43 = (i_re43) + (S32(1))
            # Post code 
            var j71_re0 = S32(0)
            while (j71_re0) < (S32(4)): 
                dsp.rec37_perm[j71_re0] = rec37_tmp[(vsize_re0) + (j71_re0)]
                j71_re0 = (j71_re0) + (S32(1))
            # Recursive loop 44 
            # Pre code 
            var j72_re0 = S32(0)
            comptime dtype83 = f64
            comptime width83 = S32(simd_width_of[dtype83]())
            while j72_re0 <= S32(4) - width83:
                var values = simd_load(dsp.rec36_perm, j72_re0)
                simd_store(rec36_tmp, j72_re0, values)
                j72_re0 = j72_re0 + S32(width83)
            # Compute code 
            var i_re44 = S32(0)
            while (i_re44) < (vsize_re0): 
                rec36[i_re44] = ((dsp.const146) * ((((dsp.const149) * (rec37[i_re44])) + ((dsp.const150) * (rec37[(i_re44) - (S32(1))]))) + ((dsp.const149) * (rec37[(i_re44) - (S32(2))])))) - ((dsp.const151) * (((dsp.const152) * (rec36[(i_re44) - (S32(2))])) + ((dsp.const153) * (rec36[(i_re44) - (S32(1))]))))
                i_re44 = (i_re44) + (S32(1))
            # Post code 
            var j73_re0 = S32(0)
            while (j73_re0) < (S32(4)): 
                dsp.rec36_perm[j73_re0] = rec36_tmp[(vsize_re0) + (j73_re0)]
                j73_re0 = (j73_re0) + (S32(1))
            # Vectorizable loop 45 
            # Compute code 
            var i_re45 = S32(0)
            comptime dtype85 = f64
            comptime width85 = S32(simd_width_of[dtype85]())
            while i_re45 <= vsize_re0 - width85:
                var values = (dsp.const151) * ((((dsp.const154) * (simd_load(rec36, i_re45))) + ((dsp.const155) * (simd_load(rec36, i_re45 - S32(1))))) + ((dsp.const154) * (simd_load(rec36, i_re45 - S32(2)))))
                simd_store(zec9, i_re45, values)
                i_re45 = i_re45 + S32(width85)
            # Recursive loop 46 
            # Pre code 
            var j74_re0 = S32(0)
            comptime dtype86 = f64
            comptime width86 = S32(simd_width_of[dtype86]())
            while j74_re0 <= S32(4) - width86:
                var values = simd_load(dsp.rec35_perm, j74_re0)
                simd_store(rec35_tmp, j74_re0, values)
                j74_re0 = j74_re0 + S32(width86)
            # Compute code 
            var i_re46 = S32(0)
            while (i_re46) < (vsize_re0): 
                rec35[i_re46] = (zec9[i_re46]) - ((dsp.const158) * (((dsp.const159) * (rec35[(i_re46) - (S32(2))])) + ((dsp.const162) * (rec35[(i_re46) - (S32(1))]))))
                i_re46 = (i_re46) + (S32(1))
            # Post code 
            var j75_re0 = S32(0)
            while (j75_re0) < (S32(4)): 
                dsp.rec35_perm[j75_re0] = rec35_tmp[(vsize_re0) + (j75_re0)]
                j75_re0 = (j75_re0) + (S32(1))
            # Recursive loop 47 
            # Pre code 
            var j76_re0 = S32(0)
            comptime dtype88 = f64
            comptime width88 = S32(simd_width_of[dtype88]())
            while j76_re0 <= S32(4) - width88:
                var values = simd_load(dsp.rec34_perm, j76_re0)
                simd_store(rec34_tmp, j76_re0, values)
                j76_re0 = j76_re0 + S32(width88)
            # Compute code 
            var i_re47 = S32(0)
            while (i_re47) < (vsize_re0): 
                rec34[i_re47] = ((dsp.const158) * ((((dsp.const164) * (rec35[i_re47])) + ((dsp.const165) * (rec35[(i_re47) - (S32(1))]))) + ((dsp.const164) * (rec35[(i_re47) - (S32(2))])))) - ((dsp.const166) * (((dsp.const167) * (rec34[(i_re47) - (S32(2))])) + ((dsp.const168) * (rec34[(i_re47) - (S32(1))]))))
                i_re47 = (i_re47) + (S32(1))
            # Post code 
            var j77_re0 = S32(0)
            while (j77_re0) < (S32(4)): 
                dsp.rec34_perm[j77_re0] = rec34_tmp[(vsize_re0) + (j77_re0)]
                j77_re0 = (j77_re0) + (S32(1))
            # Recursive loop 48 
            # Pre code 
            var j78_re0 = S32(0)
            comptime dtype90 = f64
            comptime width90 = S32(simd_width_of[dtype90]())
            while j78_re0 <= S32(4) - width90:
                var values = simd_load(dsp.rec33_perm, j78_re0)
                simd_store(rec33_tmp, j78_re0, values)
                j78_re0 = j78_re0 + S32(width90)
            # Compute code 
            var i_re48 = S32(0)
            while (i_re48) < (vsize_re0): 
                rec33[i_re48] = ((dsp.const166) * ((((dsp.const170) * (rec34[i_re48])) + ((dsp.const171) * (rec34[(i_re48) - (S32(1))]))) + ((dsp.const170) * (rec34[(i_re48) - (S32(2))])))) - ((dsp.const172) * (((dsp.const173) * (rec33[(i_re48) - (S32(2))])) + ((dsp.const174) * (rec33[(i_re48) - (S32(1))]))))
                i_re48 = (i_re48) + (S32(1))
            # Post code 
            var j79_re0 = S32(0)
            while (j79_re0) < (S32(4)): 
                dsp.rec33_perm[j79_re0] = rec33_tmp[(vsize_re0) + (j79_re0)]
                j79_re0 = (j79_re0) + (S32(1))
            # Recursive loop 49 
            # Pre code 
            var j80_re0 = S32(0)
            comptime dtype92 = f64
            comptime width92 = S32(simd_width_of[dtype92]())
            while j80_re0 <= S32(4) - width92:
                var values = simd_load(dsp.rec32_perm, j80_re0)
                simd_store(rec32_tmp, j80_re0, values)
                j80_re0 = j80_re0 + S32(width92)
            # Compute code 
            var i_re49 = S32(0)
            while (i_re49) < (vsize_re0): 
                rec32[i_re49] = ((slow8) * (rec32[(i_re49) - (S32(1))])) + ((slow9) * (abs((dsp.const172) * ((((dsp.const176) * (rec33[i_re49])) + ((dsp.const177) * (rec33[(i_re49) - (S32(1))]))) + ((dsp.const176) * (rec33[(i_re49) - (S32(2))]))))))
                i_re49 = (i_re49) + (S32(1))
            # Post code 
            var j81_re0 = S32(0)
            while (j81_re0) < (S32(4)): 
                dsp.rec32_perm[j81_re0] = rec32_tmp[(vsize_re0) + (j81_re0)]
                j81_re0 = (j81_re0) + (S32(1))
            # Recursive loop 50 
            # Pre code 
            var j82_re0 = S32(0)
            comptime dtype94 = f64
            comptime width94 = S32(simd_width_of[dtype94]())
            while j82_re0 <= S32(4) - width94:
                var values = simd_load(dsp.rec45_perm, j82_re0)
                simd_store(rec45_tmp, j82_re0, values)
                j82_re0 = j82_re0 + S32(width94)
            # Compute code 
            var i_re50 = S32(0)
            while (i_re50) < (vsize_re0): 
                rec45[i_re50] = (zec9[i_re50]) - ((dsp.const178) * (((dsp.const179) * (rec45[(i_re50) - (S32(2))])) + ((dsp.const180) * (rec45[(i_re50) - (S32(1))]))))
                i_re50 = (i_re50) + (S32(1))
            # Post code 
            var j83_re0 = S32(0)
            while (j83_re0) < (S32(4)): 
                dsp.rec45_perm[j83_re0] = rec45_tmp[(vsize_re0) + (j83_re0)]
                j83_re0 = (j83_re0) + (S32(1))
            # Recursive loop 51 
            # Pre code 
            var j84_re0 = S32(0)
            comptime dtype96 = f64
            comptime width96 = S32(simd_width_of[dtype96]())
            while j84_re0 <= S32(4) - width96:
                var values = simd_load(dsp.rec44_perm, j84_re0)
                simd_store(rec44_tmp, j84_re0, values)
                j84_re0 = j84_re0 + S32(width96)
            # Compute code 
            var i_re51 = S32(0)
            while (i_re51) < (vsize_re0): 
                rec44[i_re51] = ((dsp.const178) * ((((dsp.const182) * (rec45[i_re51])) + ((dsp.const183) * (rec45[(i_re51) - (S32(1))]))) + ((dsp.const182) * (rec45[(i_re51) - (S32(2))])))) - ((dsp.const184) * (((dsp.const185) * (rec44[(i_re51) - (S32(2))])) + ((dsp.const186) * (rec44[(i_re51) - (S32(1))]))))
                i_re51 = (i_re51) + (S32(1))
            # Post code 
            var j85_re0 = S32(0)
            while (j85_re0) < (S32(4)): 
                dsp.rec44_perm[j85_re0] = rec44_tmp[(vsize_re0) + (j85_re0)]
                j85_re0 = (j85_re0) + (S32(1))
            # Recursive loop 52 
            # Pre code 
            var j86_re0 = S32(0)
            comptime dtype98 = f64
            comptime width98 = S32(simd_width_of[dtype98]())
            while j86_re0 <= S32(4) - width98:
                var values = simd_load(dsp.rec43_perm, j86_re0)
                simd_store(rec43_tmp, j86_re0, values)
                j86_re0 = j86_re0 + S32(width98)
            # Compute code 
            var i_re52 = S32(0)
            while (i_re52) < (vsize_re0): 
                rec43[i_re52] = ((dsp.const184) * ((((dsp.const187) * (rec44[i_re52])) + ((dsp.const188) * (rec44[(i_re52) - (S32(1))]))) + ((dsp.const187) * (rec44[(i_re52) - (S32(2))])))) - ((dsp.const189) * (((dsp.const190) * (rec43[(i_re52) - (S32(2))])) + ((dsp.const191) * (rec43[(i_re52) - (S32(1))]))))
                i_re52 = (i_re52) + (S32(1))
            # Post code 
            var j87_re0 = S32(0)
            while (j87_re0) < (S32(4)): 
                dsp.rec43_perm[j87_re0] = rec43_tmp[(vsize_re0) + (j87_re0)]
                j87_re0 = (j87_re0) + (S32(1))
            # Vectorizable loop 53 
            # Compute code 
            var i_re53 = S32(0)
            comptime dtype100 = f64
            comptime width100 = S32(simd_width_of[dtype100]())
            while i_re53 <= vsize_re0 - width100:
                var values = (dsp.const189) * ((((dsp.const192) * (simd_load(rec43, i_re53))) + ((dsp.const193) * (simd_load(rec43, i_re53 - S32(1))))) + ((dsp.const192) * (simd_load(rec43, i_re53 - S32(2)))))
                simd_store(zec10, i_re53, values)
                i_re53 = i_re53 + S32(width100)
            # Recursive loop 54 
            # Pre code 
            var j88_re0 = S32(0)
            comptime dtype101 = f64
            comptime width101 = S32(simd_width_of[dtype101]())
            while j88_re0 <= S32(4) - width101:
                var values = simd_load(dsp.rec42_perm, j88_re0)
                simd_store(rec42_tmp, j88_re0, values)
                j88_re0 = j88_re0 + S32(width101)
            # Compute code 
            var i_re54 = S32(0)
            while (i_re54) < (vsize_re0): 
                rec42[i_re54] = (zec10[i_re54]) - ((dsp.const196) * (((dsp.const197) * (rec42[(i_re54) - (S32(2))])) + ((dsp.const200) * (rec42[(i_re54) - (S32(1))]))))
                i_re54 = (i_re54) + (S32(1))
            # Post code 
            var j89_re0 = S32(0)
            while (j89_re0) < (S32(4)): 
                dsp.rec42_perm[j89_re0] = rec42_tmp[(vsize_re0) + (j89_re0)]
                j89_re0 = (j89_re0) + (S32(1))
            # Recursive loop 55 
            # Pre code 
            var j90_re0 = S32(0)
            comptime dtype103 = f64
            comptime width103 = S32(simd_width_of[dtype103]())
            while j90_re0 <= S32(4) - width103:
                var values = simd_load(dsp.rec41_perm, j90_re0)
                simd_store(rec41_tmp, j90_re0, values)
                j90_re0 = j90_re0 + S32(width103)
            # Compute code 
            var i_re55 = S32(0)
            while (i_re55) < (vsize_re0): 
                rec41[i_re55] = ((dsp.const196) * ((((dsp.const202) * (rec42[i_re55])) + ((dsp.const203) * (rec42[(i_re55) - (S32(1))]))) + ((dsp.const202) * (rec42[(i_re55) - (S32(2))])))) - ((dsp.const204) * (((dsp.const205) * (rec41[(i_re55) - (S32(2))])) + ((dsp.const206) * (rec41[(i_re55) - (S32(1))]))))
                i_re55 = (i_re55) + (S32(1))
            # Post code 
            var j91_re0 = S32(0)
            while (j91_re0) < (S32(4)): 
                dsp.rec41_perm[j91_re0] = rec41_tmp[(vsize_re0) + (j91_re0)]
                j91_re0 = (j91_re0) + (S32(1))
            # Recursive loop 56 
            # Pre code 
            var j92_re0 = S32(0)
            comptime dtype105 = f64
            comptime width105 = S32(simd_width_of[dtype105]())
            while j92_re0 <= S32(4) - width105:
                var values = simd_load(dsp.rec40_perm, j92_re0)
                simd_store(rec40_tmp, j92_re0, values)
                j92_re0 = j92_re0 + S32(width105)
            # Compute code 
            var i_re56 = S32(0)
            while (i_re56) < (vsize_re0): 
                rec40[i_re56] = ((dsp.const204) * ((((dsp.const208) * (rec41[i_re56])) + ((dsp.const209) * (rec41[(i_re56) - (S32(1))]))) + ((dsp.const208) * (rec41[(i_re56) - (S32(2))])))) - ((dsp.const210) * (((dsp.const211) * (rec40[(i_re56) - (S32(2))])) + ((dsp.const212) * (rec40[(i_re56) - (S32(1))]))))
                i_re56 = (i_re56) + (S32(1))
            # Post code 
            var j93_re0 = S32(0)
            while (j93_re0) < (S32(4)): 
                dsp.rec40_perm[j93_re0] = rec40_tmp[(vsize_re0) + (j93_re0)]
                j93_re0 = (j93_re0) + (S32(1))
            # Recursive loop 57 
            # Pre code 
            var j94_re0 = S32(0)
            comptime dtype107 = f64
            comptime width107 = S32(simd_width_of[dtype107]())
            while j94_re0 <= S32(4) - width107:
                var values = simd_load(dsp.rec39_perm, j94_re0)
                simd_store(rec39_tmp, j94_re0, values)
                j94_re0 = j94_re0 + S32(width107)
            # Compute code 
            var i_re57 = S32(0)
            while (i_re57) < (vsize_re0): 
                rec39[i_re57] = ((slow8) * (rec39[(i_re57) - (S32(1))])) + ((slow9) * (abs((dsp.const210) * ((((dsp.const214) * (rec40[i_re57])) + ((dsp.const215) * (rec40[(i_re57) - (S32(1))]))) + ((dsp.const214) * (rec40[(i_re57) - (S32(2))]))))))
                i_re57 = (i_re57) + (S32(1))
            # Post code 
            var j95_re0 = S32(0)
            while (j95_re0) < (S32(4)): 
                dsp.rec39_perm[j95_re0] = rec39_tmp[(vsize_re0) + (j95_re0)]
                j95_re0 = (j95_re0) + (S32(1))
            # Recursive loop 58 
            # Pre code 
            var j96_re0 = S32(0)
            comptime dtype109 = f64
            comptime width109 = S32(simd_width_of[dtype109]())
            while j96_re0 <= S32(4) - width109:
                var values = simd_load(dsp.rec52_perm, j96_re0)
                simd_store(rec52_tmp, j96_re0, values)
                j96_re0 = j96_re0 + S32(width109)
            # Compute code 
            var i_re58 = S32(0)
            while (i_re58) < (vsize_re0): 
                rec52[i_re58] = (zec10[i_re58]) - ((dsp.const216) * (((dsp.const217) * (rec52[(i_re58) - (S32(2))])) + ((dsp.const218) * (rec52[(i_re58) - (S32(1))]))))
                i_re58 = (i_re58) + (S32(1))
            # Post code 
            var j97_re0 = S32(0)
            while (j97_re0) < (S32(4)): 
                dsp.rec52_perm[j97_re0] = rec52_tmp[(vsize_re0) + (j97_re0)]
                j97_re0 = (j97_re0) + (S32(1))
            # Recursive loop 59 
            # Pre code 
            var j98_re0 = S32(0)
            comptime dtype111 = f64
            comptime width111 = S32(simd_width_of[dtype111]())
            while j98_re0 <= S32(4) - width111:
                var values = simd_load(dsp.rec51_perm, j98_re0)
                simd_store(rec51_tmp, j98_re0, values)
                j98_re0 = j98_re0 + S32(width111)
            # Compute code 
            var i_re59 = S32(0)
            while (i_re59) < (vsize_re0): 
                rec51[i_re59] = ((dsp.const216) * ((((dsp.const220) * (rec52[i_re59])) + ((dsp.const221) * (rec52[(i_re59) - (S32(1))]))) + ((dsp.const220) * (rec52[(i_re59) - (S32(2))])))) - ((dsp.const222) * (((dsp.const223) * (rec51[(i_re59) - (S32(2))])) + ((dsp.const224) * (rec51[(i_re59) - (S32(1))]))))
                i_re59 = (i_re59) + (S32(1))
            # Post code 
            var j99_re0 = S32(0)
            while (j99_re0) < (S32(4)): 
                dsp.rec51_perm[j99_re0] = rec51_tmp[(vsize_re0) + (j99_re0)]
                j99_re0 = (j99_re0) + (S32(1))
            # Recursive loop 60 
            # Pre code 
            var j100_re0 = S32(0)
            comptime dtype113 = f64
            comptime width113 = S32(simd_width_of[dtype113]())
            while j100_re0 <= S32(4) - width113:
                var values = simd_load(dsp.rec50_perm, j100_re0)
                simd_store(rec50_tmp, j100_re0, values)
                j100_re0 = j100_re0 + S32(width113)
            # Compute code 
            var i_re60 = S32(0)
            while (i_re60) < (vsize_re0): 
                rec50[i_re60] = ((dsp.const222) * ((((dsp.const225) * (rec51[i_re60])) + ((dsp.const226) * (rec51[(i_re60) - (S32(1))]))) + ((dsp.const225) * (rec51[(i_re60) - (S32(2))])))) - ((dsp.const227) * (((dsp.const228) * (rec50[(i_re60) - (S32(2))])) + ((dsp.const229) * (rec50[(i_re60) - (S32(1))]))))
                i_re60 = (i_re60) + (S32(1))
            # Post code 
            var j101_re0 = S32(0)
            while (j101_re0) < (S32(4)): 
                dsp.rec50_perm[j101_re0] = rec50_tmp[(vsize_re0) + (j101_re0)]
                j101_re0 = (j101_re0) + (S32(1))
            # Vectorizable loop 61 
            # Compute code 
            var i_re61 = S32(0)
            comptime dtype115 = f64
            comptime width115 = S32(simd_width_of[dtype115]())
            while i_re61 <= vsize_re0 - width115:
                var values = (dsp.const227) * ((((dsp.const230) * (simd_load(rec50, i_re61))) + ((dsp.const231) * (simd_load(rec50, i_re61 - S32(1))))) + ((dsp.const230) * (simd_load(rec50, i_re61 - S32(2)))))
                simd_store(zec11, i_re61, values)
                i_re61 = i_re61 + S32(width115)
            # Recursive loop 62 
            # Pre code 
            var j102_re0 = S32(0)
            comptime dtype116 = f64
            comptime width116 = S32(simd_width_of[dtype116]())
            while j102_re0 <= S32(4) - width116:
                var values = simd_load(dsp.rec49_perm, j102_re0)
                simd_store(rec49_tmp, j102_re0, values)
                j102_re0 = j102_re0 + S32(width116)
            # Compute code 
            var i_re62 = S32(0)
            while (i_re62) < (vsize_re0): 
                rec49[i_re62] = (zec11[i_re62]) - ((dsp.const234) * (((dsp.const235) * (rec49[(i_re62) - (S32(2))])) + ((dsp.const238) * (rec49[(i_re62) - (S32(1))]))))
                i_re62 = (i_re62) + (S32(1))
            # Post code 
            var j103_re0 = S32(0)
            while (j103_re0) < (S32(4)): 
                dsp.rec49_perm[j103_re0] = rec49_tmp[(vsize_re0) + (j103_re0)]
                j103_re0 = (j103_re0) + (S32(1))
            # Recursive loop 63 
            # Pre code 
            var j104_re0 = S32(0)
            comptime dtype118 = f64
            comptime width118 = S32(simd_width_of[dtype118]())
            while j104_re0 <= S32(4) - width118:
                var values = simd_load(dsp.rec48_perm, j104_re0)
                simd_store(rec48_tmp, j104_re0, values)
                j104_re0 = j104_re0 + S32(width118)
            # Compute code 
            var i_re63 = S32(0)
            while (i_re63) < (vsize_re0): 
                rec48[i_re63] = ((dsp.const234) * ((((dsp.const240) * (rec49[i_re63])) + ((dsp.const241) * (rec49[(i_re63) - (S32(1))]))) + ((dsp.const240) * (rec49[(i_re63) - (S32(2))])))) - ((dsp.const242) * (((dsp.const243) * (rec48[(i_re63) - (S32(2))])) + ((dsp.const244) * (rec48[(i_re63) - (S32(1))]))))
                i_re63 = (i_re63) + (S32(1))
            # Post code 
            var j105_re0 = S32(0)
            while (j105_re0) < (S32(4)): 
                dsp.rec48_perm[j105_re0] = rec48_tmp[(vsize_re0) + (j105_re0)]
                j105_re0 = (j105_re0) + (S32(1))
            # Recursive loop 64 
            # Pre code 
            var j106_re0 = S32(0)
            comptime dtype120 = f64
            comptime width120 = S32(simd_width_of[dtype120]())
            while j106_re0 <= S32(4) - width120:
                var values = simd_load(dsp.rec47_perm, j106_re0)
                simd_store(rec47_tmp, j106_re0, values)
                j106_re0 = j106_re0 + S32(width120)
            # Compute code 
            var i_re64 = S32(0)
            while (i_re64) < (vsize_re0): 
                rec47[i_re64] = ((dsp.const242) * ((((dsp.const246) * (rec48[i_re64])) + ((dsp.const247) * (rec48[(i_re64) - (S32(1))]))) + ((dsp.const246) * (rec48[(i_re64) - (S32(2))])))) - ((dsp.const248) * (((dsp.const249) * (rec47[(i_re64) - (S32(2))])) + ((dsp.const250) * (rec47[(i_re64) - (S32(1))]))))
                i_re64 = (i_re64) + (S32(1))
            # Post code 
            var j107_re0 = S32(0)
            while (j107_re0) < (S32(4)): 
                dsp.rec47_perm[j107_re0] = rec47_tmp[(vsize_re0) + (j107_re0)]
                j107_re0 = (j107_re0) + (S32(1))
            # Recursive loop 65 
            # Pre code 
            var j108_re0 = S32(0)
            comptime dtype122 = f64
            comptime width122 = S32(simd_width_of[dtype122]())
            while j108_re0 <= S32(4) - width122:
                var values = simd_load(dsp.rec46_perm, j108_re0)
                simd_store(rec46_tmp, j108_re0, values)
                j108_re0 = j108_re0 + S32(width122)
            # Compute code 
            var i_re65 = S32(0)
            while (i_re65) < (vsize_re0): 
                rec46[i_re65] = ((slow8) * (rec46[(i_re65) - (S32(1))])) + ((slow9) * (abs((dsp.const248) * ((((dsp.const252) * (rec47[i_re65])) + ((dsp.const253) * (rec47[(i_re65) - (S32(1))]))) + ((dsp.const252) * (rec47[(i_re65) - (S32(2))]))))))
                i_re65 = (i_re65) + (S32(1))
            # Post code 
            var j109_re0 = S32(0)
            while (j109_re0) < (S32(4)): 
                dsp.rec46_perm[j109_re0] = rec46_tmp[(vsize_re0) + (j109_re0)]
                j109_re0 = (j109_re0) + (S32(1))
            # Recursive loop 66 
            # Pre code 
            var j110_re0 = S32(0)
            comptime dtype124 = f64
            comptime width124 = S32(simd_width_of[dtype124]())
            while j110_re0 <= S32(4) - width124:
                var values = simd_load(dsp.rec59_perm, j110_re0)
                simd_store(rec59_tmp, j110_re0, values)
                j110_re0 = j110_re0 + S32(width124)
            # Compute code 
            var i_re66 = S32(0)
            while (i_re66) < (vsize_re0): 
                rec59[i_re66] = (zec11[i_re66]) - ((dsp.const254) * (((dsp.const255) * (rec59[(i_re66) - (S32(2))])) + ((dsp.const256) * (rec59[(i_re66) - (S32(1))]))))
                i_re66 = (i_re66) + (S32(1))
            # Post code 
            var j111_re0 = S32(0)
            while (j111_re0) < (S32(4)): 
                dsp.rec59_perm[j111_re0] = rec59_tmp[(vsize_re0) + (j111_re0)]
                j111_re0 = (j111_re0) + (S32(1))
            # Recursive loop 67 
            # Pre code 
            var j112_re0 = S32(0)
            comptime dtype126 = f64
            comptime width126 = S32(simd_width_of[dtype126]())
            while j112_re0 <= S32(4) - width126:
                var values = simd_load(dsp.rec58_perm, j112_re0)
                simd_store(rec58_tmp, j112_re0, values)
                j112_re0 = j112_re0 + S32(width126)
            # Compute code 
            var i_re67 = S32(0)
            while (i_re67) < (vsize_re0): 
                rec58[i_re67] = ((dsp.const254) * ((((dsp.const258) * (rec59[i_re67])) + ((dsp.const259) * (rec59[(i_re67) - (S32(1))]))) + ((dsp.const258) * (rec59[(i_re67) - (S32(2))])))) - ((dsp.const260) * (((dsp.const261) * (rec58[(i_re67) - (S32(2))])) + ((dsp.const262) * (rec58[(i_re67) - (S32(1))]))))
                i_re67 = (i_re67) + (S32(1))
            # Post code 
            var j113_re0 = S32(0)
            while (j113_re0) < (S32(4)): 
                dsp.rec58_perm[j113_re0] = rec58_tmp[(vsize_re0) + (j113_re0)]
                j113_re0 = (j113_re0) + (S32(1))
            # Recursive loop 68 
            # Pre code 
            var j114_re0 = S32(0)
            comptime dtype128 = f64
            comptime width128 = S32(simd_width_of[dtype128]())
            while j114_re0 <= S32(4) - width128:
                var values = simd_load(dsp.rec57_perm, j114_re0)
                simd_store(rec57_tmp, j114_re0, values)
                j114_re0 = j114_re0 + S32(width128)
            # Compute code 
            var i_re68 = S32(0)
            while (i_re68) < (vsize_re0): 
                rec57[i_re68] = ((dsp.const260) * ((((dsp.const263) * (rec58[i_re68])) + ((dsp.const264) * (rec58[(i_re68) - (S32(1))]))) + ((dsp.const263) * (rec58[(i_re68) - (S32(2))])))) - ((dsp.const265) * (((dsp.const266) * (rec57[(i_re68) - (S32(2))])) + ((dsp.const267) * (rec57[(i_re68) - (S32(1))]))))
                i_re68 = (i_re68) + (S32(1))
            # Post code 
            var j115_re0 = S32(0)
            while (j115_re0) < (S32(4)): 
                dsp.rec57_perm[j115_re0] = rec57_tmp[(vsize_re0) + (j115_re0)]
                j115_re0 = (j115_re0) + (S32(1))
            # Vectorizable loop 69 
            # Compute code 
            var i_re69 = S32(0)
            comptime dtype130 = f64
            comptime width130 = S32(simd_width_of[dtype130]())
            while i_re69 <= vsize_re0 - width130:
                var values = (dsp.const265) * ((((dsp.const268) * (simd_load(rec57, i_re69))) + ((dsp.const269) * (simd_load(rec57, i_re69 - S32(1))))) + ((dsp.const268) * (simd_load(rec57, i_re69 - S32(2)))))
                simd_store(zec12, i_re69, values)
                i_re69 = i_re69 + S32(width130)
            # Recursive loop 70 
            # Pre code 
            var j116_re0 = S32(0)
            comptime dtype131 = f64
            comptime width131 = S32(simd_width_of[dtype131]())
            while j116_re0 <= S32(4) - width131:
                var values = simd_load(dsp.rec56_perm, j116_re0)
                simd_store(rec56_tmp, j116_re0, values)
                j116_re0 = j116_re0 + S32(width131)
            # Compute code 
            var i_re70 = S32(0)
            while (i_re70) < (vsize_re0): 
                rec56[i_re70] = (zec12[i_re70]) - ((dsp.const272) * (((dsp.const273) * (rec56[(i_re70) - (S32(2))])) + ((dsp.const276) * (rec56[(i_re70) - (S32(1))]))))
                i_re70 = (i_re70) + (S32(1))
            # Post code 
            var j117_re0 = S32(0)
            while (j117_re0) < (S32(4)): 
                dsp.rec56_perm[j117_re0] = rec56_tmp[(vsize_re0) + (j117_re0)]
                j117_re0 = (j117_re0) + (S32(1))
            # Recursive loop 71 
            # Pre code 
            var j118_re0 = S32(0)
            comptime dtype133 = f64
            comptime width133 = S32(simd_width_of[dtype133]())
            while j118_re0 <= S32(4) - width133:
                var values = simd_load(dsp.rec55_perm, j118_re0)
                simd_store(rec55_tmp, j118_re0, values)
                j118_re0 = j118_re0 + S32(width133)
            # Compute code 
            var i_re71 = S32(0)
            while (i_re71) < (vsize_re0): 
                rec55[i_re71] = ((dsp.const272) * ((((dsp.const278) * (rec56[i_re71])) + ((dsp.const279) * (rec56[(i_re71) - (S32(1))]))) + ((dsp.const278) * (rec56[(i_re71) - (S32(2))])))) - ((dsp.const280) * (((dsp.const281) * (rec55[(i_re71) - (S32(2))])) + ((dsp.const282) * (rec55[(i_re71) - (S32(1))]))))
                i_re71 = (i_re71) + (S32(1))
            # Post code 
            var j119_re0 = S32(0)
            while (j119_re0) < (S32(4)): 
                dsp.rec55_perm[j119_re0] = rec55_tmp[(vsize_re0) + (j119_re0)]
                j119_re0 = (j119_re0) + (S32(1))
            # Recursive loop 72 
            # Pre code 
            var j120_re0 = S32(0)
            comptime dtype135 = f64
            comptime width135 = S32(simd_width_of[dtype135]())
            while j120_re0 <= S32(4) - width135:
                var values = simd_load(dsp.rec54_perm, j120_re0)
                simd_store(rec54_tmp, j120_re0, values)
                j120_re0 = j120_re0 + S32(width135)
            # Compute code 
            var i_re72 = S32(0)
            while (i_re72) < (vsize_re0): 
                rec54[i_re72] = ((dsp.const280) * ((((dsp.const284) * (rec55[i_re72])) + ((dsp.const285) * (rec55[(i_re72) - (S32(1))]))) + ((dsp.const284) * (rec55[(i_re72) - (S32(2))])))) - ((dsp.const286) * (((dsp.const287) * (rec54[(i_re72) - (S32(2))])) + ((dsp.const288) * (rec54[(i_re72) - (S32(1))]))))
                i_re72 = (i_re72) + (S32(1))
            # Post code 
            var j121_re0 = S32(0)
            while (j121_re0) < (S32(4)): 
                dsp.rec54_perm[j121_re0] = rec54_tmp[(vsize_re0) + (j121_re0)]
                j121_re0 = (j121_re0) + (S32(1))
            # Recursive loop 73 
            # Pre code 
            var j122_re0 = S32(0)
            comptime dtype137 = f64
            comptime width137 = S32(simd_width_of[dtype137]())
            while j122_re0 <= S32(4) - width137:
                var values = simd_load(dsp.rec53_perm, j122_re0)
                simd_store(rec53_tmp, j122_re0, values)
                j122_re0 = j122_re0 + S32(width137)
            # Compute code 
            var i_re73 = S32(0)
            while (i_re73) < (vsize_re0): 
                rec53[i_re73] = ((slow8) * (rec53[(i_re73) - (S32(1))])) + ((slow9) * (abs((dsp.const286) * ((((dsp.const290) * (rec54[i_re73])) + ((dsp.const291) * (rec54[(i_re73) - (S32(1))]))) + ((dsp.const290) * (rec54[(i_re73) - (S32(2))]))))))
                i_re73 = (i_re73) + (S32(1))
            # Post code 
            var j123_re0 = S32(0)
            while (j123_re0) < (S32(4)): 
                dsp.rec53_perm[j123_re0] = rec53_tmp[(vsize_re0) + (j123_re0)]
                j123_re0 = (j123_re0) + (S32(1))
            # Recursive loop 74 
            # Pre code 
            var j124_re0 = S32(0)
            comptime dtype139 = f64
            comptime width139 = S32(simd_width_of[dtype139]())
            while j124_re0 <= S32(4) - width139:
                var values = simd_load(dsp.rec66_perm, j124_re0)
                simd_store(rec66_tmp, j124_re0, values)
                j124_re0 = j124_re0 + S32(width139)
            # Compute code 
            var i_re74 = S32(0)
            while (i_re74) < (vsize_re0): 
                rec66[i_re74] = (zec12[i_re74]) - ((dsp.const292) * (((dsp.const293) * (rec66[(i_re74) - (S32(2))])) + ((dsp.const294) * (rec66[(i_re74) - (S32(1))]))))
                i_re74 = (i_re74) + (S32(1))
            # Post code 
            var j125_re0 = S32(0)
            while (j125_re0) < (S32(4)): 
                dsp.rec66_perm[j125_re0] = rec66_tmp[(vsize_re0) + (j125_re0)]
                j125_re0 = (j125_re0) + (S32(1))
            # Recursive loop 75 
            # Pre code 
            var j126_re0 = S32(0)
            comptime dtype141 = f64
            comptime width141 = S32(simd_width_of[dtype141]())
            while j126_re0 <= S32(4) - width141:
                var values = simd_load(dsp.rec65_perm, j126_re0)
                simd_store(rec65_tmp, j126_re0, values)
                j126_re0 = j126_re0 + S32(width141)
            # Compute code 
            var i_re75 = S32(0)
            while (i_re75) < (vsize_re0): 
                rec65[i_re75] = ((dsp.const292) * ((((dsp.const296) * (rec66[i_re75])) + ((dsp.const297) * (rec66[(i_re75) - (S32(1))]))) + ((dsp.const296) * (rec66[(i_re75) - (S32(2))])))) - ((dsp.const298) * (((dsp.const299) * (rec65[(i_re75) - (S32(2))])) + ((dsp.const300) * (rec65[(i_re75) - (S32(1))]))))
                i_re75 = (i_re75) + (S32(1))
            # Post code 
            var j127_re0 = S32(0)
            while (j127_re0) < (S32(4)): 
                dsp.rec65_perm[j127_re0] = rec65_tmp[(vsize_re0) + (j127_re0)]
                j127_re0 = (j127_re0) + (S32(1))
            # Recursive loop 76 
            # Pre code 
            var j128_re0 = S32(0)
            comptime dtype143 = f64
            comptime width143 = S32(simd_width_of[dtype143]())
            while j128_re0 <= S32(4) - width143:
                var values = simd_load(dsp.rec64_perm, j128_re0)
                simd_store(rec64_tmp, j128_re0, values)
                j128_re0 = j128_re0 + S32(width143)
            # Compute code 
            var i_re76 = S32(0)
            while (i_re76) < (vsize_re0): 
                rec64[i_re76] = ((dsp.const298) * ((((dsp.const301) * (rec65[i_re76])) + ((dsp.const302) * (rec65[(i_re76) - (S32(1))]))) + ((dsp.const301) * (rec65[(i_re76) - (S32(2))])))) - ((dsp.const303) * (((dsp.const304) * (rec64[(i_re76) - (S32(2))])) + ((dsp.const305) * (rec64[(i_re76) - (S32(1))]))))
                i_re76 = (i_re76) + (S32(1))
            # Post code 
            var j129_re0 = S32(0)
            while (j129_re0) < (S32(4)): 
                dsp.rec64_perm[j129_re0] = rec64_tmp[(vsize_re0) + (j129_re0)]
                j129_re0 = (j129_re0) + (S32(1))
            # Vectorizable loop 77 
            # Compute code 
            var i_re77 = S32(0)
            comptime dtype145 = f64
            comptime width145 = S32(simd_width_of[dtype145]())
            while i_re77 <= vsize_re0 - width145:
                var values = (dsp.const303) * ((((dsp.const306) * (simd_load(rec64, i_re77))) + ((dsp.const307) * (simd_load(rec64, i_re77 - S32(1))))) + ((dsp.const306) * (simd_load(rec64, i_re77 - S32(2)))))
                simd_store(zec13, i_re77, values)
                i_re77 = i_re77 + S32(width145)
            # Recursive loop 78 
            # Pre code 
            var j130_re0 = S32(0)
            comptime dtype146 = f64
            comptime width146 = S32(simd_width_of[dtype146]())
            while j130_re0 <= S32(4) - width146:
                var values = simd_load(dsp.rec63_perm, j130_re0)
                simd_store(rec63_tmp, j130_re0, values)
                j130_re0 = j130_re0 + S32(width146)
            # Compute code 
            var i_re78 = S32(0)
            while (i_re78) < (vsize_re0): 
                rec63[i_re78] = (zec13[i_re78]) - ((dsp.const310) * (((dsp.const311) * (rec63[(i_re78) - (S32(2))])) + ((dsp.const314) * (rec63[(i_re78) - (S32(1))]))))
                i_re78 = (i_re78) + (S32(1))
            # Post code 
            var j131_re0 = S32(0)
            while (j131_re0) < (S32(4)): 
                dsp.rec63_perm[j131_re0] = rec63_tmp[(vsize_re0) + (j131_re0)]
                j131_re0 = (j131_re0) + (S32(1))
            # Recursive loop 79 
            # Pre code 
            var j132_re0 = S32(0)
            comptime dtype148 = f64
            comptime width148 = S32(simd_width_of[dtype148]())
            while j132_re0 <= S32(4) - width148:
                var values = simd_load(dsp.rec62_perm, j132_re0)
                simd_store(rec62_tmp, j132_re0, values)
                j132_re0 = j132_re0 + S32(width148)
            # Compute code 
            var i_re79 = S32(0)
            while (i_re79) < (vsize_re0): 
                rec62[i_re79] = ((dsp.const310) * ((((dsp.const316) * (rec63[i_re79])) + ((dsp.const317) * (rec63[(i_re79) - (S32(1))]))) + ((dsp.const316) * (rec63[(i_re79) - (S32(2))])))) - ((dsp.const318) * (((dsp.const319) * (rec62[(i_re79) - (S32(2))])) + ((dsp.const320) * (rec62[(i_re79) - (S32(1))]))))
                i_re79 = (i_re79) + (S32(1))
            # Post code 
            var j133_re0 = S32(0)
            while (j133_re0) < (S32(4)): 
                dsp.rec62_perm[j133_re0] = rec62_tmp[(vsize_re0) + (j133_re0)]
                j133_re0 = (j133_re0) + (S32(1))
            # Recursive loop 80 
            # Pre code 
            var j134_re0 = S32(0)
            comptime dtype150 = f64
            comptime width150 = S32(simd_width_of[dtype150]())
            while j134_re0 <= S32(4) - width150:
                var values = simd_load(dsp.rec61_perm, j134_re0)
                simd_store(rec61_tmp, j134_re0, values)
                j134_re0 = j134_re0 + S32(width150)
            # Compute code 
            var i_re80 = S32(0)
            while (i_re80) < (vsize_re0): 
                rec61[i_re80] = ((dsp.const318) * ((((dsp.const322) * (rec62[i_re80])) + ((dsp.const323) * (rec62[(i_re80) - (S32(1))]))) + ((dsp.const322) * (rec62[(i_re80) - (S32(2))])))) - ((dsp.const324) * (((dsp.const325) * (rec61[(i_re80) - (S32(2))])) + ((dsp.const326) * (rec61[(i_re80) - (S32(1))]))))
                i_re80 = (i_re80) + (S32(1))
            # Post code 
            var j135_re0 = S32(0)
            while (j135_re0) < (S32(4)): 
                dsp.rec61_perm[j135_re0] = rec61_tmp[(vsize_re0) + (j135_re0)]
                j135_re0 = (j135_re0) + (S32(1))
            # Recursive loop 81 
            # Pre code 
            var j136_re0 = S32(0)
            comptime dtype152 = f64
            comptime width152 = S32(simd_width_of[dtype152]())
            while j136_re0 <= S32(4) - width152:
                var values = simd_load(dsp.rec60_perm, j136_re0)
                simd_store(rec60_tmp, j136_re0, values)
                j136_re0 = j136_re0 + S32(width152)
            # Compute code 
            var i_re81 = S32(0)
            while (i_re81) < (vsize_re0): 
                rec60[i_re81] = ((slow8) * (rec60[(i_re81) - (S32(1))])) + ((slow9) * (abs((dsp.const324) * ((((dsp.const328) * (rec61[i_re81])) + ((dsp.const329) * (rec61[(i_re81) - (S32(1))]))) + ((dsp.const328) * (rec61[(i_re81) - (S32(2))]))))))
                i_re81 = (i_re81) + (S32(1))
            # Post code 
            var j137_re0 = S32(0)
            while (j137_re0) < (S32(4)): 
                dsp.rec60_perm[j137_re0] = rec60_tmp[(vsize_re0) + (j137_re0)]
                j137_re0 = (j137_re0) + (S32(1))
            # Recursive loop 82 
            # Pre code 
            var j138_re0 = S32(0)
            comptime dtype154 = f64
            comptime width154 = S32(simd_width_of[dtype154]())
            while j138_re0 <= S32(4) - width154:
                var values = simd_load(dsp.rec73_perm, j138_re0)
                simd_store(rec73_tmp, j138_re0, values)
                j138_re0 = j138_re0 + S32(width154)
            # Compute code 
            var i_re82 = S32(0)
            while (i_re82) < (vsize_re0): 
                rec73[i_re82] = (zec13[i_re82]) - ((dsp.const330) * (((dsp.const331) * (rec73[(i_re82) - (S32(2))])) + ((dsp.const332) * (rec73[(i_re82) - (S32(1))]))))
                i_re82 = (i_re82) + (S32(1))
            # Post code 
            var j139_re0 = S32(0)
            while (j139_re0) < (S32(4)): 
                dsp.rec73_perm[j139_re0] = rec73_tmp[(vsize_re0) + (j139_re0)]
                j139_re0 = (j139_re0) + (S32(1))
            # Recursive loop 83 
            # Pre code 
            var j140_re0 = S32(0)
            comptime dtype156 = f64
            comptime width156 = S32(simd_width_of[dtype156]())
            while j140_re0 <= S32(4) - width156:
                var values = simd_load(dsp.rec72_perm, j140_re0)
                simd_store(rec72_tmp, j140_re0, values)
                j140_re0 = j140_re0 + S32(width156)
            # Compute code 
            var i_re83 = S32(0)
            while (i_re83) < (vsize_re0): 
                rec72[i_re83] = ((dsp.const330) * ((((dsp.const334) * (rec73[i_re83])) + ((dsp.const335) * (rec73[(i_re83) - (S32(1))]))) + ((dsp.const334) * (rec73[(i_re83) - (S32(2))])))) - ((dsp.const336) * (((dsp.const337) * (rec72[(i_re83) - (S32(2))])) + ((dsp.const338) * (rec72[(i_re83) - (S32(1))]))))
                i_re83 = (i_re83) + (S32(1))
            # Post code 
            var j141_re0 = S32(0)
            while (j141_re0) < (S32(4)): 
                dsp.rec72_perm[j141_re0] = rec72_tmp[(vsize_re0) + (j141_re0)]
                j141_re0 = (j141_re0) + (S32(1))
            # Recursive loop 84 
            # Pre code 
            var j142_re0 = S32(0)
            comptime dtype158 = f64
            comptime width158 = S32(simd_width_of[dtype158]())
            while j142_re0 <= S32(4) - width158:
                var values = simd_load(dsp.rec71_perm, j142_re0)
                simd_store(rec71_tmp, j142_re0, values)
                j142_re0 = j142_re0 + S32(width158)
            # Compute code 
            var i_re84 = S32(0)
            while (i_re84) < (vsize_re0): 
                rec71[i_re84] = ((dsp.const336) * ((((dsp.const339) * (rec72[i_re84])) + ((dsp.const340) * (rec72[(i_re84) - (S32(1))]))) + ((dsp.const339) * (rec72[(i_re84) - (S32(2))])))) - ((dsp.const341) * (((dsp.const342) * (rec71[(i_re84) - (S32(2))])) + ((dsp.const343) * (rec71[(i_re84) - (S32(1))]))))
                i_re84 = (i_re84) + (S32(1))
            # Post code 
            var j143_re0 = S32(0)
            while (j143_re0) < (S32(4)): 
                dsp.rec71_perm[j143_re0] = rec71_tmp[(vsize_re0) + (j143_re0)]
                j143_re0 = (j143_re0) + (S32(1))
            # Vectorizable loop 85 
            # Compute code 
            var i_re85 = S32(0)
            comptime dtype160 = f64
            comptime width160 = S32(simd_width_of[dtype160]())
            while i_re85 <= vsize_re0 - width160:
                var values = (dsp.const341) * ((((dsp.const344) * (simd_load(rec71, i_re85))) + ((dsp.const345) * (simd_load(rec71, i_re85 - S32(1))))) + ((dsp.const344) * (simd_load(rec71, i_re85 - S32(2)))))
                simd_store(zec14, i_re85, values)
                i_re85 = i_re85 + S32(width160)
            # Recursive loop 86 
            # Pre code 
            var j144_re0 = S32(0)
            comptime dtype161 = f64
            comptime width161 = S32(simd_width_of[dtype161]())
            while j144_re0 <= S32(4) - width161:
                var values = simd_load(dsp.rec70_perm, j144_re0)
                simd_store(rec70_tmp, j144_re0, values)
                j144_re0 = j144_re0 + S32(width161)
            # Compute code 
            var i_re86 = S32(0)
            while (i_re86) < (vsize_re0): 
                rec70[i_re86] = (zec14[i_re86]) - ((dsp.const348) * (((dsp.const349) * (rec70[(i_re86) - (S32(2))])) + ((dsp.const352) * (rec70[(i_re86) - (S32(1))]))))
                i_re86 = (i_re86) + (S32(1))
            # Post code 
            var j145_re0 = S32(0)
            while (j145_re0) < (S32(4)): 
                dsp.rec70_perm[j145_re0] = rec70_tmp[(vsize_re0) + (j145_re0)]
                j145_re0 = (j145_re0) + (S32(1))
            # Recursive loop 87 
            # Pre code 
            var j146_re0 = S32(0)
            comptime dtype163 = f64
            comptime width163 = S32(simd_width_of[dtype163]())
            while j146_re0 <= S32(4) - width163:
                var values = simd_load(dsp.rec69_perm, j146_re0)
                simd_store(rec69_tmp, j146_re0, values)
                j146_re0 = j146_re0 + S32(width163)
            # Compute code 
            var i_re87 = S32(0)
            while (i_re87) < (vsize_re0): 
                rec69[i_re87] = ((dsp.const348) * ((((dsp.const354) * (rec70[i_re87])) + ((dsp.const355) * (rec70[(i_re87) - (S32(1))]))) + ((dsp.const354) * (rec70[(i_re87) - (S32(2))])))) - ((dsp.const356) * (((dsp.const357) * (rec69[(i_re87) - (S32(2))])) + ((dsp.const358) * (rec69[(i_re87) - (S32(1))]))))
                i_re87 = (i_re87) + (S32(1))
            # Post code 
            var j147_re0 = S32(0)
            while (j147_re0) < (S32(4)): 
                dsp.rec69_perm[j147_re0] = rec69_tmp[(vsize_re0) + (j147_re0)]
                j147_re0 = (j147_re0) + (S32(1))
            # Recursive loop 88 
            # Pre code 
            var j148_re0 = S32(0)
            comptime dtype165 = f64
            comptime width165 = S32(simd_width_of[dtype165]())
            while j148_re0 <= S32(4) - width165:
                var values = simd_load(dsp.rec68_perm, j148_re0)
                simd_store(rec68_tmp, j148_re0, values)
                j148_re0 = j148_re0 + S32(width165)
            # Compute code 
            var i_re88 = S32(0)
            while (i_re88) < (vsize_re0): 
                rec68[i_re88] = ((dsp.const356) * ((((dsp.const360) * (rec69[i_re88])) + ((dsp.const361) * (rec69[(i_re88) - (S32(1))]))) + ((dsp.const360) * (rec69[(i_re88) - (S32(2))])))) - ((dsp.const362) * (((dsp.const363) * (rec68[(i_re88) - (S32(2))])) + ((dsp.const364) * (rec68[(i_re88) - (S32(1))]))))
                i_re88 = (i_re88) + (S32(1))
            # Post code 
            var j149_re0 = S32(0)
            while (j149_re0) < (S32(4)): 
                dsp.rec68_perm[j149_re0] = rec68_tmp[(vsize_re0) + (j149_re0)]
                j149_re0 = (j149_re0) + (S32(1))
            # Recursive loop 89 
            # Pre code 
            var j150_re0 = S32(0)
            comptime dtype167 = f64
            comptime width167 = S32(simd_width_of[dtype167]())
            while j150_re0 <= S32(4) - width167:
                var values = simd_load(dsp.rec67_perm, j150_re0)
                simd_store(rec67_tmp, j150_re0, values)
                j150_re0 = j150_re0 + S32(width167)
            # Compute code 
            var i_re89 = S32(0)
            while (i_re89) < (vsize_re0): 
                rec67[i_re89] = ((slow8) * (rec67[(i_re89) - (S32(1))])) + ((slow9) * (abs((dsp.const362) * ((((dsp.const366) * (rec68[i_re89])) + ((dsp.const367) * (rec68[(i_re89) - (S32(1))]))) + ((dsp.const366) * (rec68[(i_re89) - (S32(2))]))))))
                i_re89 = (i_re89) + (S32(1))
            # Post code 
            var j151_re0 = S32(0)
            while (j151_re0) < (S32(4)): 
                dsp.rec67_perm[j151_re0] = rec67_tmp[(vsize_re0) + (j151_re0)]
                j151_re0 = (j151_re0) + (S32(1))
            # Recursive loop 90 
            # Pre code 
            var j152_re0 = S32(0)
            comptime dtype169 = f64
            comptime width169 = S32(simd_width_of[dtype169]())
            while j152_re0 <= S32(4) - width169:
                var values = simd_load(dsp.rec80_perm, j152_re0)
                simd_store(rec80_tmp, j152_re0, values)
                j152_re0 = j152_re0 + S32(width169)
            # Compute code 
            var i_re90 = S32(0)
            while (i_re90) < (vsize_re0): 
                rec80[i_re90] = (zec14[i_re90]) - ((dsp.const368) * (((dsp.const369) * (rec80[(i_re90) - (S32(2))])) + ((dsp.const370) * (rec80[(i_re90) - (S32(1))]))))
                i_re90 = (i_re90) + (S32(1))
            # Post code 
            var j153_re0 = S32(0)
            while (j153_re0) < (S32(4)): 
                dsp.rec80_perm[j153_re0] = rec80_tmp[(vsize_re0) + (j153_re0)]
                j153_re0 = (j153_re0) + (S32(1))
            # Recursive loop 91 
            # Pre code 
            var j154_re0 = S32(0)
            comptime dtype171 = f64
            comptime width171 = S32(simd_width_of[dtype171]())
            while j154_re0 <= S32(4) - width171:
                var values = simd_load(dsp.rec79_perm, j154_re0)
                simd_store(rec79_tmp, j154_re0, values)
                j154_re0 = j154_re0 + S32(width171)
            # Compute code 
            var i_re91 = S32(0)
            while (i_re91) < (vsize_re0): 
                rec79[i_re91] = ((dsp.const368) * ((((dsp.const372) * (rec80[i_re91])) + ((dsp.const373) * (rec80[(i_re91) - (S32(1))]))) + ((dsp.const372) * (rec80[(i_re91) - (S32(2))])))) - ((dsp.const374) * (((dsp.const375) * (rec79[(i_re91) - (S32(2))])) + ((dsp.const376) * (rec79[(i_re91) - (S32(1))]))))
                i_re91 = (i_re91) + (S32(1))
            # Post code 
            var j155_re0 = S32(0)
            while (j155_re0) < (S32(4)): 
                dsp.rec79_perm[j155_re0] = rec79_tmp[(vsize_re0) + (j155_re0)]
                j155_re0 = (j155_re0) + (S32(1))
            # Recursive loop 92 
            # Pre code 
            var j156_re0 = S32(0)
            comptime dtype173 = f64
            comptime width173 = S32(simd_width_of[dtype173]())
            while j156_re0 <= S32(4) - width173:
                var values = simd_load(dsp.rec78_perm, j156_re0)
                simd_store(rec78_tmp, j156_re0, values)
                j156_re0 = j156_re0 + S32(width173)
            # Compute code 
            var i_re92 = S32(0)
            while (i_re92) < (vsize_re0): 
                rec78[i_re92] = ((dsp.const374) * ((((dsp.const377) * (rec79[i_re92])) + ((dsp.const378) * (rec79[(i_re92) - (S32(1))]))) + ((dsp.const377) * (rec79[(i_re92) - (S32(2))])))) - ((dsp.const379) * (((dsp.const380) * (rec78[(i_re92) - (S32(2))])) + ((dsp.const381) * (rec78[(i_re92) - (S32(1))]))))
                i_re92 = (i_re92) + (S32(1))
            # Post code 
            var j157_re0 = S32(0)
            while (j157_re0) < (S32(4)): 
                dsp.rec78_perm[j157_re0] = rec78_tmp[(vsize_re0) + (j157_re0)]
                j157_re0 = (j157_re0) + (S32(1))
            # Vectorizable loop 93 
            # Compute code 
            var i_re93 = S32(0)
            comptime dtype175 = f64
            comptime width175 = S32(simd_width_of[dtype175]())
            while i_re93 <= vsize_re0 - width175:
                var values = (dsp.const379) * ((((dsp.const382) * (simd_load(rec78, i_re93))) + ((dsp.const383) * (simd_load(rec78, i_re93 - S32(1))))) + ((dsp.const382) * (simd_load(rec78, i_re93 - S32(2)))))
                simd_store(zec15, i_re93, values)
                i_re93 = i_re93 + S32(width175)
            # Recursive loop 94 
            # Pre code 
            var j158_re0 = S32(0)
            comptime dtype176 = f64
            comptime width176 = S32(simd_width_of[dtype176]())
            while j158_re0 <= S32(4) - width176:
                var values = simd_load(dsp.rec77_perm, j158_re0)
                simd_store(rec77_tmp, j158_re0, values)
                j158_re0 = j158_re0 + S32(width176)
            # Compute code 
            var i_re94 = S32(0)
            while (i_re94) < (vsize_re0): 
                rec77[i_re94] = (zec15[i_re94]) - ((dsp.const386) * (((dsp.const387) * (rec77[(i_re94) - (S32(2))])) + ((dsp.const390) * (rec77[(i_re94) - (S32(1))]))))
                i_re94 = (i_re94) + (S32(1))
            # Post code 
            var j159_re0 = S32(0)
            while (j159_re0) < (S32(4)): 
                dsp.rec77_perm[j159_re0] = rec77_tmp[(vsize_re0) + (j159_re0)]
                j159_re0 = (j159_re0) + (S32(1))
            # Recursive loop 95 
            # Pre code 
            var j160_re0 = S32(0)
            comptime dtype178 = f64
            comptime width178 = S32(simd_width_of[dtype178]())
            while j160_re0 <= S32(4) - width178:
                var values = simd_load(dsp.rec76_perm, j160_re0)
                simd_store(rec76_tmp, j160_re0, values)
                j160_re0 = j160_re0 + S32(width178)
            # Compute code 
            var i_re95 = S32(0)
            while (i_re95) < (vsize_re0): 
                rec76[i_re95] = ((dsp.const386) * ((((dsp.const392) * (rec77[i_re95])) + ((dsp.const393) * (rec77[(i_re95) - (S32(1))]))) + ((dsp.const392) * (rec77[(i_re95) - (S32(2))])))) - ((dsp.const394) * (((dsp.const395) * (rec76[(i_re95) - (S32(2))])) + ((dsp.const396) * (rec76[(i_re95) - (S32(1))]))))
                i_re95 = (i_re95) + (S32(1))
            # Post code 
            var j161_re0 = S32(0)
            while (j161_re0) < (S32(4)): 
                dsp.rec76_perm[j161_re0] = rec76_tmp[(vsize_re0) + (j161_re0)]
                j161_re0 = (j161_re0) + (S32(1))
            # Recursive loop 96 
            # Pre code 
            var j162_re0 = S32(0)
            comptime dtype180 = f64
            comptime width180 = S32(simd_width_of[dtype180]())
            while j162_re0 <= S32(4) - width180:
                var values = simd_load(dsp.rec75_perm, j162_re0)
                simd_store(rec75_tmp, j162_re0, values)
                j162_re0 = j162_re0 + S32(width180)
            # Compute code 
            var i_re96 = S32(0)
            while (i_re96) < (vsize_re0): 
                rec75[i_re96] = ((dsp.const394) * ((((dsp.const398) * (rec76[i_re96])) + ((dsp.const399) * (rec76[(i_re96) - (S32(1))]))) + ((dsp.const398) * (rec76[(i_re96) - (S32(2))])))) - ((dsp.const400) * (((dsp.const401) * (rec75[(i_re96) - (S32(2))])) + ((dsp.const402) * (rec75[(i_re96) - (S32(1))]))))
                i_re96 = (i_re96) + (S32(1))
            # Post code 
            var j163_re0 = S32(0)
            while (j163_re0) < (S32(4)): 
                dsp.rec75_perm[j163_re0] = rec75_tmp[(vsize_re0) + (j163_re0)]
                j163_re0 = (j163_re0) + (S32(1))
            # Recursive loop 97 
            # Pre code 
            var j164_re0 = S32(0)
            comptime dtype182 = f64
            comptime width182 = S32(simd_width_of[dtype182]())
            while j164_re0 <= S32(4) - width182:
                var values = simd_load(dsp.rec74_perm, j164_re0)
                simd_store(rec74_tmp, j164_re0, values)
                j164_re0 = j164_re0 + S32(width182)
            # Compute code 
            var i_re97 = S32(0)
            while (i_re97) < (vsize_re0): 
                rec74[i_re97] = ((slow8) * (rec74[(i_re97) - (S32(1))])) + ((slow9) * (abs((dsp.const400) * ((((dsp.const404) * (rec75[i_re97])) + ((dsp.const405) * (rec75[(i_re97) - (S32(1))]))) + ((dsp.const404) * (rec75[(i_re97) - (S32(2))]))))))
                i_re97 = (i_re97) + (S32(1))
            # Post code 
            var j165_re0 = S32(0)
            while (j165_re0) < (S32(4)): 
                dsp.rec74_perm[j165_re0] = rec74_tmp[(vsize_re0) + (j165_re0)]
                j165_re0 = (j165_re0) + (S32(1))
            # Recursive loop 98 
            # Pre code 
            var j166_re0 = S32(0)
            comptime dtype184 = f64
            comptime width184 = S32(simd_width_of[dtype184]())
            while j166_re0 <= S32(4) - width184:
                var values = simd_load(dsp.rec87_perm, j166_re0)
                simd_store(rec87_tmp, j166_re0, values)
                j166_re0 = j166_re0 + S32(width184)
            # Compute code 
            var i_re98 = S32(0)
            while (i_re98) < (vsize_re0): 
                rec87[i_re98] = (zec15[i_re98]) - ((dsp.const406) * (((dsp.const407) * (rec87[(i_re98) - (S32(2))])) + ((dsp.const408) * (rec87[(i_re98) - (S32(1))]))))
                i_re98 = (i_re98) + (S32(1))
            # Post code 
            var j167_re0 = S32(0)
            while (j167_re0) < (S32(4)): 
                dsp.rec87_perm[j167_re0] = rec87_tmp[(vsize_re0) + (j167_re0)]
                j167_re0 = (j167_re0) + (S32(1))
            # Recursive loop 99 
            # Pre code 
            var j168_re0 = S32(0)
            comptime dtype186 = f64
            comptime width186 = S32(simd_width_of[dtype186]())
            while j168_re0 <= S32(4) - width186:
                var values = simd_load(dsp.rec86_perm, j168_re0)
                simd_store(rec86_tmp, j168_re0, values)
                j168_re0 = j168_re0 + S32(width186)
            # Compute code 
            var i_re99 = S32(0)
            while (i_re99) < (vsize_re0): 
                rec86[i_re99] = ((dsp.const406) * ((((dsp.const410) * (rec87[i_re99])) + ((dsp.const411) * (rec87[(i_re99) - (S32(1))]))) + ((dsp.const410) * (rec87[(i_re99) - (S32(2))])))) - ((dsp.const412) * (((dsp.const413) * (rec86[(i_re99) - (S32(2))])) + ((dsp.const414) * (rec86[(i_re99) - (S32(1))]))))
                i_re99 = (i_re99) + (S32(1))
            # Post code 
            var j169_re0 = S32(0)
            while (j169_re0) < (S32(4)): 
                dsp.rec86_perm[j169_re0] = rec86_tmp[(vsize_re0) + (j169_re0)]
                j169_re0 = (j169_re0) + (S32(1))
            # Recursive loop 100 
            # Pre code 
            var j170_re0 = S32(0)
            comptime dtype188 = f64
            comptime width188 = S32(simd_width_of[dtype188]())
            while j170_re0 <= S32(4) - width188:
                var values = simd_load(dsp.rec85_perm, j170_re0)
                simd_store(rec85_tmp, j170_re0, values)
                j170_re0 = j170_re0 + S32(width188)
            # Compute code 
            var i_re100 = S32(0)
            while (i_re100) < (vsize_re0): 
                rec85[i_re100] = ((dsp.const412) * ((((dsp.const415) * (rec86[i_re100])) + ((dsp.const416) * (rec86[(i_re100) - (S32(1))]))) + ((dsp.const415) * (rec86[(i_re100) - (S32(2))])))) - ((dsp.const417) * (((dsp.const418) * (rec85[(i_re100) - (S32(2))])) + ((dsp.const419) * (rec85[(i_re100) - (S32(1))]))))
                i_re100 = (i_re100) + (S32(1))
            # Post code 
            var j171_re0 = S32(0)
            while (j171_re0) < (S32(4)): 
                dsp.rec85_perm[j171_re0] = rec85_tmp[(vsize_re0) + (j171_re0)]
                j171_re0 = (j171_re0) + (S32(1))
            # Vectorizable loop 101 
            # Compute code 
            var i_re101 = S32(0)
            comptime dtype190 = f64
            comptime width190 = S32(simd_width_of[dtype190]())
            while i_re101 <= vsize_re0 - width190:
                var values = (dsp.const417) * ((((dsp.const420) * (simd_load(rec85, i_re101))) + ((dsp.const421) * (simd_load(rec85, i_re101 - S32(1))))) + ((dsp.const420) * (simd_load(rec85, i_re101 - S32(2)))))
                simd_store(zec16, i_re101, values)
                i_re101 = i_re101 + S32(width190)
            # Recursive loop 102 
            # Pre code 
            var j172_re0 = S32(0)
            comptime dtype191 = f64
            comptime width191 = S32(simd_width_of[dtype191]())
            while j172_re0 <= S32(4) - width191:
                var values = simd_load(dsp.rec84_perm, j172_re0)
                simd_store(rec84_tmp, j172_re0, values)
                j172_re0 = j172_re0 + S32(width191)
            # Compute code 
            var i_re102 = S32(0)
            while (i_re102) < (vsize_re0): 
                rec84[i_re102] = (zec16[i_re102]) - ((dsp.const424) * (((dsp.const425) * (rec84[(i_re102) - (S32(2))])) + ((dsp.const428) * (rec84[(i_re102) - (S32(1))]))))
                i_re102 = (i_re102) + (S32(1))
            # Post code 
            var j173_re0 = S32(0)
            while (j173_re0) < (S32(4)): 
                dsp.rec84_perm[j173_re0] = rec84_tmp[(vsize_re0) + (j173_re0)]
                j173_re0 = (j173_re0) + (S32(1))
            # Recursive loop 103 
            # Pre code 
            var j174_re0 = S32(0)
            comptime dtype193 = f64
            comptime width193 = S32(simd_width_of[dtype193]())
            while j174_re0 <= S32(4) - width193:
                var values = simd_load(dsp.rec83_perm, j174_re0)
                simd_store(rec83_tmp, j174_re0, values)
                j174_re0 = j174_re0 + S32(width193)
            # Compute code 
            var i_re103 = S32(0)
            while (i_re103) < (vsize_re0): 
                rec83[i_re103] = ((dsp.const424) * ((((dsp.const430) * (rec84[i_re103])) + ((dsp.const431) * (rec84[(i_re103) - (S32(1))]))) + ((dsp.const430) * (rec84[(i_re103) - (S32(2))])))) - ((dsp.const432) * (((dsp.const433) * (rec83[(i_re103) - (S32(2))])) + ((dsp.const434) * (rec83[(i_re103) - (S32(1))]))))
                i_re103 = (i_re103) + (S32(1))
            # Post code 
            var j175_re0 = S32(0)
            while (j175_re0) < (S32(4)): 
                dsp.rec83_perm[j175_re0] = rec83_tmp[(vsize_re0) + (j175_re0)]
                j175_re0 = (j175_re0) + (S32(1))
            # Recursive loop 104 
            # Pre code 
            var j176_re0 = S32(0)
            comptime dtype195 = f64
            comptime width195 = S32(simd_width_of[dtype195]())
            while j176_re0 <= S32(4) - width195:
                var values = simd_load(dsp.rec82_perm, j176_re0)
                simd_store(rec82_tmp, j176_re0, values)
                j176_re0 = j176_re0 + S32(width195)
            # Compute code 
            var i_re104 = S32(0)
            while (i_re104) < (vsize_re0): 
                rec82[i_re104] = ((dsp.const432) * ((((dsp.const436) * (rec83[i_re104])) + ((dsp.const437) * (rec83[(i_re104) - (S32(1))]))) + ((dsp.const436) * (rec83[(i_re104) - (S32(2))])))) - ((dsp.const438) * (((dsp.const439) * (rec82[(i_re104) - (S32(2))])) + ((dsp.const440) * (rec82[(i_re104) - (S32(1))]))))
                i_re104 = (i_re104) + (S32(1))
            # Post code 
            var j177_re0 = S32(0)
            while (j177_re0) < (S32(4)): 
                dsp.rec82_perm[j177_re0] = rec82_tmp[(vsize_re0) + (j177_re0)]
                j177_re0 = (j177_re0) + (S32(1))
            # Recursive loop 105 
            # Pre code 
            var j178_re0 = S32(0)
            comptime dtype197 = f64
            comptime width197 = S32(simd_width_of[dtype197]())
            while j178_re0 <= S32(4) - width197:
                var values = simd_load(dsp.rec81_perm, j178_re0)
                simd_store(rec81_tmp, j178_re0, values)
                j178_re0 = j178_re0 + S32(width197)
            # Compute code 
            var i_re105 = S32(0)
            while (i_re105) < (vsize_re0): 
                rec81[i_re105] = ((slow8) * (rec81[(i_re105) - (S32(1))])) + ((slow9) * (abs((dsp.const438) * ((((dsp.const442) * (rec82[i_re105])) + ((dsp.const443) * (rec82[(i_re105) - (S32(1))]))) + ((dsp.const442) * (rec82[(i_re105) - (S32(2))]))))))
                i_re105 = (i_re105) + (S32(1))
            # Post code 
            var j179_re0 = S32(0)
            while (j179_re0) < (S32(4)): 
                dsp.rec81_perm[j179_re0] = rec81_tmp[(vsize_re0) + (j179_re0)]
                j179_re0 = (j179_re0) + (S32(1))
            # Recursive loop 106 
            # Pre code 
            var j180_re0 = S32(0)
            comptime dtype199 = f64
            comptime width199 = S32(simd_width_of[dtype199]())
            while j180_re0 <= S32(4) - width199:
                var values = simd_load(dsp.rec94_perm, j180_re0)
                simd_store(rec94_tmp, j180_re0, values)
                j180_re0 = j180_re0 + S32(width199)
            # Compute code 
            var i_re106 = S32(0)
            while (i_re106) < (vsize_re0): 
                rec94[i_re106] = (zec16[i_re106]) - ((dsp.const444) * (((dsp.const445) * (rec94[(i_re106) - (S32(2))])) + ((dsp.const446) * (rec94[(i_re106) - (S32(1))]))))
                i_re106 = (i_re106) + (S32(1))
            # Post code 
            var j181_re0 = S32(0)
            while (j181_re0) < (S32(4)): 
                dsp.rec94_perm[j181_re0] = rec94_tmp[(vsize_re0) + (j181_re0)]
                j181_re0 = (j181_re0) + (S32(1))
            # Recursive loop 107 
            # Pre code 
            var j182_re0 = S32(0)
            comptime dtype201 = f64
            comptime width201 = S32(simd_width_of[dtype201]())
            while j182_re0 <= S32(4) - width201:
                var values = simd_load(dsp.rec93_perm, j182_re0)
                simd_store(rec93_tmp, j182_re0, values)
                j182_re0 = j182_re0 + S32(width201)
            # Compute code 
            var i_re107 = S32(0)
            while (i_re107) < (vsize_re0): 
                rec93[i_re107] = ((dsp.const444) * ((((dsp.const448) * (rec94[i_re107])) + ((dsp.const449) * (rec94[(i_re107) - (S32(1))]))) + ((dsp.const448) * (rec94[(i_re107) - (S32(2))])))) - ((dsp.const450) * (((dsp.const451) * (rec93[(i_re107) - (S32(2))])) + ((dsp.const452) * (rec93[(i_re107) - (S32(1))]))))
                i_re107 = (i_re107) + (S32(1))
            # Post code 
            var j183_re0 = S32(0)
            while (j183_re0) < (S32(4)): 
                dsp.rec93_perm[j183_re0] = rec93_tmp[(vsize_re0) + (j183_re0)]
                j183_re0 = (j183_re0) + (S32(1))
            # Recursive loop 108 
            # Pre code 
            var j184_re0 = S32(0)
            comptime dtype203 = f64
            comptime width203 = S32(simd_width_of[dtype203]())
            while j184_re0 <= S32(4) - width203:
                var values = simd_load(dsp.rec92_perm, j184_re0)
                simd_store(rec92_tmp, j184_re0, values)
                j184_re0 = j184_re0 + S32(width203)
            # Compute code 
            var i_re108 = S32(0)
            while (i_re108) < (vsize_re0): 
                rec92[i_re108] = ((dsp.const450) * ((((dsp.const453) * (rec93[i_re108])) + ((dsp.const454) * (rec93[(i_re108) - (S32(1))]))) + ((dsp.const453) * (rec93[(i_re108) - (S32(2))])))) - ((dsp.const455) * (((dsp.const456) * (rec92[(i_re108) - (S32(2))])) + ((dsp.const457) * (rec92[(i_re108) - (S32(1))]))))
                i_re108 = (i_re108) + (S32(1))
            # Post code 
            var j185_re0 = S32(0)
            while (j185_re0) < (S32(4)): 
                dsp.rec92_perm[j185_re0] = rec92_tmp[(vsize_re0) + (j185_re0)]
                j185_re0 = (j185_re0) + (S32(1))
            # Vectorizable loop 109 
            # Compute code 
            var i_re109 = S32(0)
            comptime dtype205 = f64
            comptime width205 = S32(simd_width_of[dtype205]())
            while i_re109 <= vsize_re0 - width205:
                var values = (dsp.const455) * ((((dsp.const458) * (simd_load(rec92, i_re109))) + ((dsp.const459) * (simd_load(rec92, i_re109 - S32(1))))) + ((dsp.const458) * (simd_load(rec92, i_re109 - S32(2)))))
                simd_store(zec17, i_re109, values)
                i_re109 = i_re109 + S32(width205)
            # Recursive loop 110 
            # Pre code 
            var j186_re0 = S32(0)
            comptime dtype206 = f64
            comptime width206 = S32(simd_width_of[dtype206]())
            while j186_re0 <= S32(4) - width206:
                var values = simd_load(dsp.rec91_perm, j186_re0)
                simd_store(rec91_tmp, j186_re0, values)
                j186_re0 = j186_re0 + S32(width206)
            # Compute code 
            var i_re110 = S32(0)
            while (i_re110) < (vsize_re0): 
                rec91[i_re110] = (zec17[i_re110]) - ((dsp.const462) * (((dsp.const463) * (rec91[(i_re110) - (S32(2))])) + ((dsp.const466) * (rec91[(i_re110) - (S32(1))]))))
                i_re110 = (i_re110) + (S32(1))
            # Post code 
            var j187_re0 = S32(0)
            while (j187_re0) < (S32(4)): 
                dsp.rec91_perm[j187_re0] = rec91_tmp[(vsize_re0) + (j187_re0)]
                j187_re0 = (j187_re0) + (S32(1))
            # Recursive loop 111 
            # Pre code 
            var j188_re0 = S32(0)
            comptime dtype208 = f64
            comptime width208 = S32(simd_width_of[dtype208]())
            while j188_re0 <= S32(4) - width208:
                var values = simd_load(dsp.rec90_perm, j188_re0)
                simd_store(rec90_tmp, j188_re0, values)
                j188_re0 = j188_re0 + S32(width208)
            # Compute code 
            var i_re111 = S32(0)
            while (i_re111) < (vsize_re0): 
                rec90[i_re111] = ((dsp.const462) * ((((dsp.const468) * (rec91[i_re111])) + ((dsp.const469) * (rec91[(i_re111) - (S32(1))]))) + ((dsp.const468) * (rec91[(i_re111) - (S32(2))])))) - ((dsp.const470) * (((dsp.const471) * (rec90[(i_re111) - (S32(2))])) + ((dsp.const472) * (rec90[(i_re111) - (S32(1))]))))
                i_re111 = (i_re111) + (S32(1))
            # Post code 
            var j189_re0 = S32(0)
            while (j189_re0) < (S32(4)): 
                dsp.rec90_perm[j189_re0] = rec90_tmp[(vsize_re0) + (j189_re0)]
                j189_re0 = (j189_re0) + (S32(1))
            # Recursive loop 112 
            # Pre code 
            var j190_re0 = S32(0)
            comptime dtype210 = f64
            comptime width210 = S32(simd_width_of[dtype210]())
            while j190_re0 <= S32(4) - width210:
                var values = simd_load(dsp.rec89_perm, j190_re0)
                simd_store(rec89_tmp, j190_re0, values)
                j190_re0 = j190_re0 + S32(width210)
            # Compute code 
            var i_re112 = S32(0)
            while (i_re112) < (vsize_re0): 
                rec89[i_re112] = ((dsp.const470) * ((((dsp.const474) * (rec90[i_re112])) + ((dsp.const475) * (rec90[(i_re112) - (S32(1))]))) + ((dsp.const474) * (rec90[(i_re112) - (S32(2))])))) - ((dsp.const476) * (((dsp.const477) * (rec89[(i_re112) - (S32(2))])) + ((dsp.const478) * (rec89[(i_re112) - (S32(1))]))))
                i_re112 = (i_re112) + (S32(1))
            # Post code 
            var j191_re0 = S32(0)
            while (j191_re0) < (S32(4)): 
                dsp.rec89_perm[j191_re0] = rec89_tmp[(vsize_re0) + (j191_re0)]
                j191_re0 = (j191_re0) + (S32(1))
            # Recursive loop 113 
            # Pre code 
            var j192_re0 = S32(0)
            comptime dtype212 = f64
            comptime width212 = S32(simd_width_of[dtype212]())
            while j192_re0 <= S32(4) - width212:
                var values = simd_load(dsp.rec88_perm, j192_re0)
                simd_store(rec88_tmp, j192_re0, values)
                j192_re0 = j192_re0 + S32(width212)
            # Compute code 
            var i_re113 = S32(0)
            while (i_re113) < (vsize_re0): 
                rec88[i_re113] = ((slow8) * (rec88[(i_re113) - (S32(1))])) + ((slow9) * (abs((dsp.const476) * ((((dsp.const480) * (rec89[i_re113])) + ((dsp.const481) * (rec89[(i_re113) - (S32(1))]))) + ((dsp.const480) * (rec89[(i_re113) - (S32(2))]))))))
                i_re113 = (i_re113) + (S32(1))
            # Post code 
            var j193_re0 = S32(0)
            while (j193_re0) < (S32(4)): 
                dsp.rec88_perm[j193_re0] = rec88_tmp[(vsize_re0) + (j193_re0)]
                j193_re0 = (j193_re0) + (S32(1))
            # Recursive loop 114 
            # Pre code 
            var j194_re0 = S32(0)
            comptime dtype214 = f64
            comptime width214 = S32(simd_width_of[dtype214]())
            while j194_re0 <= S32(4) - width214:
                var values = simd_load(dsp.rec101_perm, j194_re0)
                simd_store(rec101_tmp, j194_re0, values)
                j194_re0 = j194_re0 + S32(width214)
            # Compute code 
            var i_re114 = S32(0)
            while (i_re114) < (vsize_re0): 
                rec101[i_re114] = (zec17[i_re114]) - ((dsp.const482) * (((dsp.const483) * (rec101[(i_re114) - (S32(2))])) + ((dsp.const484) * (rec101[(i_re114) - (S32(1))]))))
                i_re114 = (i_re114) + (S32(1))
            # Post code 
            var j195_re0 = S32(0)
            while (j195_re0) < (S32(4)): 
                dsp.rec101_perm[j195_re0] = rec101_tmp[(vsize_re0) + (j195_re0)]
                j195_re0 = (j195_re0) + (S32(1))
            # Recursive loop 115 
            # Pre code 
            var j196_re0 = S32(0)
            comptime dtype216 = f64
            comptime width216 = S32(simd_width_of[dtype216]())
            while j196_re0 <= S32(4) - width216:
                var values = simd_load(dsp.rec100_perm, j196_re0)
                simd_store(rec100_tmp, j196_re0, values)
                j196_re0 = j196_re0 + S32(width216)
            # Compute code 
            var i_re115 = S32(0)
            while (i_re115) < (vsize_re0): 
                rec100[i_re115] = ((dsp.const482) * ((((dsp.const486) * (rec101[i_re115])) + ((dsp.const487) * (rec101[(i_re115) - (S32(1))]))) + ((dsp.const486) * (rec101[(i_re115) - (S32(2))])))) - ((dsp.const488) * (((dsp.const489) * (rec100[(i_re115) - (S32(2))])) + ((dsp.const490) * (rec100[(i_re115) - (S32(1))]))))
                i_re115 = (i_re115) + (S32(1))
            # Post code 
            var j197_re0 = S32(0)
            while (j197_re0) < (S32(4)): 
                dsp.rec100_perm[j197_re0] = rec100_tmp[(vsize_re0) + (j197_re0)]
                j197_re0 = (j197_re0) + (S32(1))
            # Recursive loop 116 
            # Pre code 
            var j198_re0 = S32(0)
            comptime dtype218 = f64
            comptime width218 = S32(simd_width_of[dtype218]())
            while j198_re0 <= S32(4) - width218:
                var values = simd_load(dsp.rec99_perm, j198_re0)
                simd_store(rec99_tmp, j198_re0, values)
                j198_re0 = j198_re0 + S32(width218)
            # Compute code 
            var i_re116 = S32(0)
            while (i_re116) < (vsize_re0): 
                rec99[i_re116] = ((dsp.const488) * ((((dsp.const491) * (rec100[i_re116])) + ((dsp.const492) * (rec100[(i_re116) - (S32(1))]))) + ((dsp.const491) * (rec100[(i_re116) - (S32(2))])))) - ((dsp.const493) * (((dsp.const494) * (rec99[(i_re116) - (S32(2))])) + ((dsp.const495) * (rec99[(i_re116) - (S32(1))]))))
                i_re116 = (i_re116) + (S32(1))
            # Post code 
            var j199_re0 = S32(0)
            while (j199_re0) < (S32(4)): 
                dsp.rec99_perm[j199_re0] = rec99_tmp[(vsize_re0) + (j199_re0)]
                j199_re0 = (j199_re0) + (S32(1))
            # Vectorizable loop 117 
            # Compute code 
            var i_re117 = S32(0)
            comptime dtype220 = f64
            comptime width220 = S32(simd_width_of[dtype220]())
            while i_re117 <= vsize_re0 - width220:
                var values = (dsp.const493) * ((((dsp.const496) * (simd_load(rec99, i_re117))) + ((dsp.const497) * (simd_load(rec99, i_re117 - S32(1))))) + ((dsp.const496) * (simd_load(rec99, i_re117 - S32(2)))))
                simd_store(zec18, i_re117, values)
                i_re117 = i_re117 + S32(width220)
            # Recursive loop 118 
            # Pre code 
            var j200_re0 = S32(0)
            comptime dtype221 = f64
            comptime width221 = S32(simd_width_of[dtype221]())
            while j200_re0 <= S32(4) - width221:
                var values = simd_load(dsp.rec98_perm, j200_re0)
                simd_store(rec98_tmp, j200_re0, values)
                j200_re0 = j200_re0 + S32(width221)
            # Compute code 
            var i_re118 = S32(0)
            while (i_re118) < (vsize_re0): 
                rec98[i_re118] = (zec18[i_re118]) - ((dsp.const500) * (((dsp.const501) * (rec98[(i_re118) - (S32(2))])) + ((dsp.const504) * (rec98[(i_re118) - (S32(1))]))))
                i_re118 = (i_re118) + (S32(1))
            # Post code 
            var j201_re0 = S32(0)
            while (j201_re0) < (S32(4)): 
                dsp.rec98_perm[j201_re0] = rec98_tmp[(vsize_re0) + (j201_re0)]
                j201_re0 = (j201_re0) + (S32(1))
            # Recursive loop 119 
            # Pre code 
            var j202_re0 = S32(0)
            comptime dtype223 = f64
            comptime width223 = S32(simd_width_of[dtype223]())
            while j202_re0 <= S32(4) - width223:
                var values = simd_load(dsp.rec97_perm, j202_re0)
                simd_store(rec97_tmp, j202_re0, values)
                j202_re0 = j202_re0 + S32(width223)
            # Compute code 
            var i_re119 = S32(0)
            while (i_re119) < (vsize_re0): 
                rec97[i_re119] = ((dsp.const500) * ((((dsp.const506) * (rec98[i_re119])) + ((dsp.const507) * (rec98[(i_re119) - (S32(1))]))) + ((dsp.const506) * (rec98[(i_re119) - (S32(2))])))) - ((dsp.const508) * (((dsp.const509) * (rec97[(i_re119) - (S32(2))])) + ((dsp.const510) * (rec97[(i_re119) - (S32(1))]))))
                i_re119 = (i_re119) + (S32(1))
            # Post code 
            var j203_re0 = S32(0)
            while (j203_re0) < (S32(4)): 
                dsp.rec97_perm[j203_re0] = rec97_tmp[(vsize_re0) + (j203_re0)]
                j203_re0 = (j203_re0) + (S32(1))
            # Recursive loop 120 
            # Pre code 
            var j204_re0 = S32(0)
            comptime dtype225 = f64
            comptime width225 = S32(simd_width_of[dtype225]())
            while j204_re0 <= S32(4) - width225:
                var values = simd_load(dsp.rec96_perm, j204_re0)
                simd_store(rec96_tmp, j204_re0, values)
                j204_re0 = j204_re0 + S32(width225)
            # Compute code 
            var i_re120 = S32(0)
            while (i_re120) < (vsize_re0): 
                rec96[i_re120] = ((dsp.const508) * ((((dsp.const512) * (rec97[i_re120])) + ((dsp.const513) * (rec97[(i_re120) - (S32(1))]))) + ((dsp.const512) * (rec97[(i_re120) - (S32(2))])))) - ((dsp.const514) * (((dsp.const515) * (rec96[(i_re120) - (S32(2))])) + ((dsp.const516) * (rec96[(i_re120) - (S32(1))]))))
                i_re120 = (i_re120) + (S32(1))
            # Post code 
            var j205_re0 = S32(0)
            while (j205_re0) < (S32(4)): 
                dsp.rec96_perm[j205_re0] = rec96_tmp[(vsize_re0) + (j205_re0)]
                j205_re0 = (j205_re0) + (S32(1))
            # Recursive loop 121 
            # Pre code 
            var j206_re0 = S32(0)
            comptime dtype227 = f64
            comptime width227 = S32(simd_width_of[dtype227]())
            while j206_re0 <= S32(4) - width227:
                var values = simd_load(dsp.rec95_perm, j206_re0)
                simd_store(rec95_tmp, j206_re0, values)
                j206_re0 = j206_re0 + S32(width227)
            # Compute code 
            var i_re121 = S32(0)
            while (i_re121) < (vsize_re0): 
                rec95[i_re121] = ((slow8) * (rec95[(i_re121) - (S32(1))])) + ((slow9) * (abs((dsp.const514) * ((((dsp.const518) * (rec96[i_re121])) + ((dsp.const519) * (rec96[(i_re121) - (S32(1))]))) + ((dsp.const518) * (rec96[(i_re121) - (S32(2))]))))))
                i_re121 = (i_re121) + (S32(1))
            # Post code 
            var j207_re0 = S32(0)
            while (j207_re0) < (S32(4)): 
                dsp.rec95_perm[j207_re0] = rec95_tmp[(vsize_re0) + (j207_re0)]
                j207_re0 = (j207_re0) + (S32(1))
            # Recursive loop 122 
            # Pre code 
            var j208_re0 = S32(0)
            comptime dtype229 = f64
            comptime width229 = S32(simd_width_of[dtype229]())
            while j208_re0 <= S32(4) - width229:
                var values = simd_load(dsp.rec105_perm, j208_re0)
                simd_store(rec105_tmp, j208_re0, values)
                j208_re0 = j208_re0 + S32(width229)
            # Compute code 
            var i_re122 = S32(0)
            while (i_re122) < (vsize_re0): 
                rec105[i_re122] = (zec18[i_re122]) - ((dsp.const520) * (((dsp.const521) * (rec105[(i_re122) - (S32(2))])) + ((dsp.const522) * (rec105[(i_re122) - (S32(1))]))))
                i_re122 = (i_re122) + (S32(1))
            # Post code 
            var j209_re0 = S32(0)
            while (j209_re0) < (S32(4)): 
                dsp.rec105_perm[j209_re0] = rec105_tmp[(vsize_re0) + (j209_re0)]
                j209_re0 = (j209_re0) + (S32(1))
            # Recursive loop 123 
            # Pre code 
            var j210_re0 = S32(0)
            comptime dtype231 = f64
            comptime width231 = S32(simd_width_of[dtype231]())
            while j210_re0 <= S32(4) - width231:
                var values = simd_load(dsp.rec104_perm, j210_re0)
                simd_store(rec104_tmp, j210_re0, values)
                j210_re0 = j210_re0 + S32(width231)
            # Compute code 
            var i_re123 = S32(0)
            while (i_re123) < (vsize_re0): 
                rec104[i_re123] = ((dsp.const520) * ((((dsp.const524) * (rec105[i_re123])) + ((dsp.const525) * (rec105[(i_re123) - (S32(1))]))) + ((dsp.const524) * (rec105[(i_re123) - (S32(2))])))) - ((dsp.const526) * (((dsp.const527) * (rec104[(i_re123) - (S32(2))])) + ((dsp.const528) * (rec104[(i_re123) - (S32(1))]))))
                i_re123 = (i_re123) + (S32(1))
            # Post code 
            var j211_re0 = S32(0)
            while (j211_re0) < (S32(4)): 
                dsp.rec104_perm[j211_re0] = rec104_tmp[(vsize_re0) + (j211_re0)]
                j211_re0 = (j211_re0) + (S32(1))
            # Recursive loop 124 
            # Pre code 
            var j212_re0 = S32(0)
            comptime dtype233 = f64
            comptime width233 = S32(simd_width_of[dtype233]())
            while j212_re0 <= S32(4) - width233:
                var values = simd_load(dsp.rec103_perm, j212_re0)
                simd_store(rec103_tmp, j212_re0, values)
                j212_re0 = j212_re0 + S32(width233)
            # Compute code 
            var i_re124 = S32(0)
            while (i_re124) < (vsize_re0): 
                rec103[i_re124] = ((dsp.const526) * ((((dsp.const529) * (rec104[i_re124])) + ((dsp.const530) * (rec104[(i_re124) - (S32(1))]))) + ((dsp.const529) * (rec104[(i_re124) - (S32(2))])))) - ((dsp.const531) * (((dsp.const532) * (rec103[(i_re124) - (S32(2))])) + ((dsp.const533) * (rec103[(i_re124) - (S32(1))]))))
                i_re124 = (i_re124) + (S32(1))
            # Post code 
            var j213_re0 = S32(0)
            while (j213_re0) < (S32(4)): 
                dsp.rec103_perm[j213_re0] = rec103_tmp[(vsize_re0) + (j213_re0)]
                j213_re0 = (j213_re0) + (S32(1))
            # Recursive loop 125 
            # Pre code 
            var j214_re0 = S32(0)
            comptime dtype235 = f64
            comptime width235 = S32(simd_width_of[dtype235]())
            while j214_re0 <= S32(4) - width235:
                var values = simd_load(dsp.rec102_perm, j214_re0)
                simd_store(rec102_tmp, j214_re0, values)
                j214_re0 = j214_re0 + S32(width235)
            # Compute code 
            var i_re125 = S32(0)
            while (i_re125) < (vsize_re0): 
                rec102[i_re125] = ((slow8) * (rec102[(i_re125) - (S32(1))])) + ((slow9) * (abs((dsp.const531) * ((((dsp.const534) * (rec103[i_re125])) + ((dsp.const535) * (rec103[(i_re125) - (S32(1))]))) + ((dsp.const534) * (rec103[(i_re125) - (S32(2))]))))))
                i_re125 = (i_re125) + (S32(1))
            # Post code 
            var j215_re0 = S32(0)
            while (j215_re0) < (S32(4)): 
                dsp.rec102_perm[j215_re0] = rec102_tmp[(vsize_re0) + (j215_re0)]
                j215_re0 = (j215_re0) + (S32(1))
            # Vectorizable loop 126 
            # Compute code 
            var i_re126 = S32(0)
            comptime dtype237 = dfaust
            comptime width237 = S32(simd_width_of[dtype237]())
            while i_re126 <= vsize_re0 - width237:

                # dsp.vbargraph0 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec7, i_re126)))))
                # dsp.vbargraph1 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec11, i_re126)))))
                # dsp.vbargraph2 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec18, i_re126)))))
                # dsp.vbargraph3 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec25, i_re126)))))
                # dsp.vbargraph4 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec32, i_re126)))))
                # dsp.vbargraph5 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec39, i_re126)))))
                # dsp.vbargraph6 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec46, i_re126)))))
                # dsp.vbargraph7 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec53, i_re126)))))
                # dsp.vbargraph8 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec60, i_re126)))))
                # dsp.vbargraph9 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec67, i_re126)))))
                # dsp.vbargraph10 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec74, i_re126)))))
                # dsp.vbargraph11 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec81, i_re126)))))
                # dsp.vbargraph12 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec88, i_re126)))))
                # dsp.vbargraph13 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec95, i_re126)))))
                # dsp.vbargraph14 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec102, i_re126)))))
                # simd_load(zec19, i_re126) = simd_load(zec5, i_re126)
                #                 i_re126 = i_re126 + S32(width237)

            # Vectorizable loop 127 
            # Compute code 
            var i_re127 = S32(0)
            comptime dtype238 = dfaust
            comptime width238 = S32(simd_width_of[dtype238]())
            while i_re127 <= vsize_re0 - width238:
                var values = (simd_load(zec19, i_re127)).cast[dfaust]()
                simd_store(output0, i_re127, values)
                i_re127 = i_re127 + S32(width238)
            # Vectorizable loop 128 
            # Compute code 
            var i_re128 = S32(0)
            comptime dtype239 = dfaust
            comptime width239 = S32(simd_width_of[dtype239]())
            while i_re128 <= vsize_re0 - width239:
                var values = (simd_load(zec19, i_re128)).cast[dfaust]()
                simd_store(output1, i_re128, values)
                i_re128 = i_re128 + S32(width239)
            vindex_re0 = (vindex_re0) + (S32(4))
        # Remaining frames 
        if ((vindex_re0) < (count) != 0):
            var output0 = Ptr(to=output0_ptr[vindex_re0])
            var output1 = Ptr(to=output1_ptr[vindex_re0])
            var vsize_re1 = (count) - (vindex_re0)
            # Recursive loop 0 
            # Pre code 
            var j0_re1 = S32(0)
            comptime dtype240 = f64
            comptime width240 = S32(simd_width_of[dtype240]())
            while j0_re1 <= S32(4) - width240:
                var values = simd_load(dsp.rec1_perm, j0_re1)
                simd_store(rec1_tmp, j0_re1, values)
                j0_re1 = j0_re1 + S32(width240)
            # Compute code 
            var i_re129 = S32(0)
            while (i_re129) < (vsize_re1): 
                rec1[i_re129] = (slow0) + ((0.999) * (rec1[(i_re129) - (S32(1))]))
                i_re129 = (i_re129) + (S32(1))
            # Post code 
            var j1_re1 = S32(0)
            while (j1_re1) < (S32(4)): 
                dsp.rec1_perm[j1_re1] = rec1_tmp[(vsize_re1) + (j1_re1)]
                j1_re1 = (j1_re1) + (S32(1))
            # Recursive loop 1 
            # Pre code 
            var j2_re1 = S32(0)
            comptime dtype242 = f64
            comptime width242 = S32(simd_width_of[dtype242]())
            while j2_re1 <= S32(4) - width242:
                var values = simd_load(dsp.rec2_perm, j2_re1)
                simd_store(rec2_tmp, j2_re1, values)
                j2_re1 = j2_re1 + S32(width242)
            # Compute code 
            var i_re130 = S32(0)
            while (i_re130) < (vsize_re1): 
                rec2[i_re130] = (slow1) + ((0.999) * (rec2[(i_re130) - (S32(1))]))
                i_re130 = (i_re130) + (S32(1))
            # Post code 
            var j3_re1 = S32(0)
            while (j3_re1) < (S32(4)): 
                dsp.rec2_perm[j3_re1] = rec2_tmp[(vsize_re1) + (j3_re1)]
                j3_re1 = (j3_re1) + (S32(1))
            # Recursive loop 2 
            # Pre code 
            var j4_re1 = S32(0)
            comptime dtype244 = f64
            comptime width244 = S32(simd_width_of[dtype244]())
            while j4_re1 <= S32(4) - width244:
                var values = simd_load(dsp.rec5_perm, j4_re1)
                simd_store(rec5_tmp, j4_re1, values)
                j4_re1 = j4_re1 + S32(width244)
            # Compute code 
            var i_re131 = S32(0)
            while (i_re131) < (vsize_re1): 
                rec5[i_re131] = ((rec5[(i_re131) - (S32(1))]) * (slow3)) + (slow4)
                i_re131 = (i_re131) + (S32(1))
            # Post code 
            var j5_re1 = S32(0)
            while (j5_re1) < (S32(4)): 
                dsp.rec5_perm[j5_re1] = rec5_tmp[(vsize_re1) + (j5_re1)]
                j5_re1 = (j5_re1) + (S32(1))
            # Vectorizable loop 3 
            # Compute code 
            var i_re132 = S32(0)
            comptime dtype246 = f64
            comptime width246 = S32(simd_width_of[dtype246]())
            while i_re132 <= vsize_re1 - width246:
                var values = (dsp.const2) * (simd_load(rec5, i_re132))
                simd_store(zec0, i_re132, values)
                i_re132 = i_re132 + S32(width246)
            # Vectorizable loop 4 
            # Compute code 
            var i_re133 = S32(0)
            comptime dtype247 = f64
            comptime width247 = S32(simd_width_of[dtype247]())
            while i_re133 <= vsize_re1 - width247:
                var values = sin(simd_load(zec0, i_re133))
                simd_store(zec1, i_re133, values)
                i_re133 = i_re133 + S32(width247)
            # Vectorizable loop 5 
            # Compute code 
            var i_re134 = S32(0)
            comptime dtype248 = f64
            comptime width248 = S32(simd_width_of[dtype248]())
            while i_re134 <= vsize_re1 - width248:
                var values = cos(simd_load(zec0, i_re134))
                simd_store(zec2, i_re134, values)
                i_re134 = i_re134 + S32(width248)
            # Vectorizable loop 6 
            # Pre code 
            var j8_re1 = S32(0)
            comptime dtype249 = s32
            comptime width249 = S32(simd_width_of[dtype249]())
            while j8_re1 <= S32(4) - width249:
                var values = simd_load(dsp.i_vec0_perm, j8_re1)
                simd_store(i_vec0_tmp, j8_re1, values)
                j8_re1 = j8_re1 + S32(width249)
            # Compute code 
            var i_re135 = S32(0)
            comptime dtype250 = s32
            comptime width250 = S32(simd_width_of[dtype250]())
            while i_re135 <= vsize_re1 - width250:
                var values = S32(1)
                simd_store(i_vec0, i_re135, values)
                i_re135 = i_re135 + S32(width250)
            # Post code 
            var j9_re1 = S32(0)
            while (j9_re1) < (S32(4)): 
                dsp.i_vec0_perm[j9_re1] = i_vec0_tmp[(vsize_re1) + (j9_re1)]
                j9_re1 = (j9_re1) + (S32(1))
            # Recursive loop 7 
            # Pre code 
            var j6_re1 = S32(0)
            comptime dtype252 = f64
            comptime width252 = S32(simd_width_of[dtype252]())
            while j6_re1 <= S32(4) - width252:
                var values = simd_load(dsp.rec3_perm, j6_re1)
                simd_store(rec3_tmp, j6_re1, values)
                j6_re1 = j6_re1 + S32(width252)
            var j10_re1 = S32(0)
            comptime dtype253 = f64
            comptime width253 = S32(simd_width_of[dtype253]())
            while j10_re1 <= S32(4) - width253:
                var values = simd_load(dsp.rec4_perm, j10_re1)
                simd_store(rec4_tmp, j10_re1, values)
                j10_re1 = j10_re1 + S32(width253)
            # Compute code 
            var i_re136 = S32(0)
            while (i_re136) < (vsize_re1): 
                rec3[i_re136] = ((rec4[(i_re136) - (S32(1))]) * (zec1[i_re136])) + ((rec3[(i_re136) - (S32(1))]) * (zec2[i_re136]))
                rec4[i_re136] = ((F64((S32(1)) - (i_vec0[(i_re136) - (S32(1))]))) + ((rec4[(i_re136) - (S32(1))]) * (zec2[i_re136]))) - ((zec1[i_re136]) * (rec3[(i_re136) - (S32(1))]))
                i_re136 = (i_re136) + (S32(1))
            # Post code 
            var j7_re1 = S32(0)
            while (j7_re1) < (S32(4)): 
                dsp.rec3_perm[j7_re1] = rec3_tmp[(vsize_re1) + (j7_re1)]
                j7_re1 = (j7_re1) + (S32(1))
            var j11_re1 = S32(0)
            while (j11_re1) < (S32(4)): 
                dsp.rec4_perm[j11_re1] = rec4_tmp[(vsize_re1) + (j11_re1)]
                j11_re1 = (j11_re1) + (S32(1))
            # Recursive loop 8 
            # Pre code 
            var j12_re1 = S32(0)
            comptime dtype256 = f64
            comptime width256 = S32(simd_width_of[dtype256]())
            while j12_re1 <= S32(4) - width256:
                var values = simd_load(dsp.rec6_perm, j12_re1)
                simd_store(rec6_tmp, j12_re1, values)
                j12_re1 = j12_re1 + S32(width256)
            # Compute code 
            var i_re137 = S32(0)
            while (i_re137) < (vsize_re1): 
                rec6[i_re137] = (slow5) + ((0.999) * (rec6[(i_re137) - (S32(1))]))
                i_re137 = (i_re137) + (S32(1))
            # Post code 
            var j13_re1 = S32(0)
            while (j13_re1) < (S32(4)): 
                dsp.rec6_perm[j13_re1] = rec6_tmp[(vsize_re1) + (j13_re1)]
                j13_re1 = (j13_re1) + (S32(1))
            # Vectorizable loop 9 
            # Compute code 
            var i_re138 = S32(0)
            comptime dtype258 = f64
            comptime width258 = S32(simd_width_of[dtype258]())
            while i_re138 <= vsize_re1 - width258:
                var values = (simd_load(rec2, i_re138)) * (simd_load(rec3, i_re138))
                simd_store(zec3, i_re138, values)
                i_re138 = i_re138 + S32(width258)
            # Vectorizable loop 10 
            # Compute code 
            var i_re139 = S32(0)
            comptime dtype259 = f64
            comptime width259 = S32(simd_width_of[dtype259]())
            while i_re139 <= vsize_re1 - width259:
                var values = max(-1.0, min(1.0, (simd_load(rec1, i_re139)) + ((0.0 if i_slow6 else simd_load(zec3, i_re139)) * (pow(1e+01, (2.0) * (simd_load(rec6, i_re139)))))))
                simd_store(zec4, i_re139, values)
                i_re139 = i_re139 + S32(width259)
            # Vectorizable loop 11 
            # Pre code 
            var j14_re1 = S32(0)
            comptime dtype260 = f64
            comptime width260 = S32(simd_width_of[dtype260]())
            while j14_re1 <= S32(4) - width260:
                var values = simd_load(dsp.yec0_perm, j14_re1)
                simd_store(yec0_tmp, j14_re1, values)
                j14_re1 = j14_re1 + S32(width260)
            # Compute code 
            var i_re140 = S32(0)
            comptime dtype261 = f64
            comptime width261 = S32(simd_width_of[dtype261]())
            while i_re140 <= vsize_re1 - width261:
                var values = (simd_load(zec4, i_re140)) * ((1.0) - ((0.3333333333333333) * (pow_unrolled[2](simd_load(zec4, i_re140)))))
                simd_store(yec0, i_re140, values)
                i_re140 = i_re140 + S32(width261)
            # Post code 
            var j15_re1 = S32(0)
            while (j15_re1) < (S32(4)): 
                dsp.yec0_perm[j15_re1] = yec0_tmp[(vsize_re1) + (j15_re1)]
                j15_re1 = (j15_re1) + (S32(1))
            # Recursive loop 12 
            # Pre code 
            var j16_re1 = S32(0)
            comptime dtype263 = f64
            comptime width263 = S32(simd_width_of[dtype263]())
            while j16_re1 <= S32(4) - width263:
                var values = simd_load(dsp.rec0_perm, j16_re1)
                simd_store(rec0_tmp, j16_re1, values)
                j16_re1 = j16_re1 + S32(width263)
            # Compute code 
            var i_re141 = S32(0)
            while (i_re141) < (vsize_re1): 
                rec0[i_re141] = (((0.995) * (rec0[(i_re141) - (S32(1))])) + (yec0[i_re141])) - (yec0[(i_re141) - (S32(1))])
                i_re141 = (i_re141) + (S32(1))
            # Post code 
            var j17_re1 = S32(0)
            while (j17_re1) < (S32(4)): 
                dsp.rec0_perm[j17_re1] = rec0_tmp[(vsize_re1) + (j17_re1)]
                j17_re1 = (j17_re1) + (S32(1))
            # Vectorizable loop 13 
            # Compute code 
            var i_re142 = S32(0)
            comptime dtype265 = f64
            comptime width265 = S32(simd_width_of[dtype265]())
            while i_re142 <= vsize_re1 - width265:
                var values = simd_load(zec3, i_re142) if i_slow6 else simd_load(rec0, i_re142)
                simd_store(zec5, i_re142, values)
                i_re142 = i_re142 + S32(width265)
            # Recursive loop 14 
            # Pre code 
            var j18_re1 = S32(0)
            comptime dtype266 = f64
            comptime width266 = S32(simd_width_of[dtype266]())
            while j18_re1 <= S32(4) - width266:
                var values = simd_load(dsp.rec10_perm, j18_re1)
                simd_store(rec10_tmp, j18_re1, values)
                j18_re1 = j18_re1 + S32(width266)
            # Compute code 
            var i_re143 = S32(0)
            while (i_re143) < (vsize_re1): 
                rec10[i_re143] = (zec5[i_re143]) - ((dsp.const5) * (((dsp.const6) * (rec10[(i_re143) - (S32(2))])) + ((dsp.const9) * (rec10[(i_re143) - (S32(1))]))))
                i_re143 = (i_re143) + (S32(1))
            # Post code 
            var j19_re1 = S32(0)
            while (j19_re1) < (S32(4)): 
                dsp.rec10_perm[j19_re1] = rec10_tmp[(vsize_re1) + (j19_re1)]
                j19_re1 = (j19_re1) + (S32(1))
            # Recursive loop 15 
            # Pre code 
            var j20_re1 = S32(0)
            comptime dtype268 = f64
            comptime width268 = S32(simd_width_of[dtype268]())
            while j20_re1 <= S32(4) - width268:
                var values = simd_load(dsp.rec9_perm, j20_re1)
                simd_store(rec9_tmp, j20_re1, values)
                j20_re1 = j20_re1 + S32(width268)
            # Compute code 
            var i_re144 = S32(0)
            while (i_re144) < (vsize_re1): 
                rec9[i_re144] = ((dsp.const5) * ((((dsp.const11) * (rec10[i_re144])) + ((dsp.const12) * (rec10[(i_re144) - (S32(1))]))) + ((dsp.const11) * (rec10[(i_re144) - (S32(2))])))) - ((dsp.const13) * (((dsp.const14) * (rec9[(i_re144) - (S32(2))])) + ((dsp.const15) * (rec9[(i_re144) - (S32(1))]))))
                i_re144 = (i_re144) + (S32(1))
            # Post code 
            var j21_re1 = S32(0)
            while (j21_re1) < (S32(4)): 
                dsp.rec9_perm[j21_re1] = rec9_tmp[(vsize_re1) + (j21_re1)]
                j21_re1 = (j21_re1) + (S32(1))
            # Recursive loop 16 
            # Pre code 
            var j22_re1 = S32(0)
            comptime dtype270 = f64
            comptime width270 = S32(simd_width_of[dtype270]())
            while j22_re1 <= S32(4) - width270:
                var values = simd_load(dsp.rec8_perm, j22_re1)
                simd_store(rec8_tmp, j22_re1, values)
                j22_re1 = j22_re1 + S32(width270)
            # Compute code 
            var i_re145 = S32(0)
            while (i_re145) < (vsize_re1): 
                rec8[i_re145] = ((dsp.const13) * ((((dsp.const17) * (rec9[i_re145])) + ((dsp.const18) * (rec9[(i_re145) - (S32(1))]))) + ((dsp.const17) * (rec9[(i_re145) - (S32(2))])))) - ((dsp.const19) * (((dsp.const20) * (rec8[(i_re145) - (S32(2))])) + ((dsp.const21) * (rec8[(i_re145) - (S32(1))]))))
                i_re145 = (i_re145) + (S32(1))
            # Post code 
            var j23_re1 = S32(0)
            while (j23_re1) < (S32(4)): 
                dsp.rec8_perm[j23_re1] = rec8_tmp[(vsize_re1) + (j23_re1)]
                j23_re1 = (j23_re1) + (S32(1))
            # Recursive loop 17 
            # Pre code 
            var j24_re1 = S32(0)
            comptime dtype272 = f64
            comptime width272 = S32(simd_width_of[dtype272]())
            while j24_re1 <= S32(4) - width272:
                var values = simd_load(dsp.rec7_perm, j24_re1)
                simd_store(rec7_tmp, j24_re1, values)
                j24_re1 = j24_re1 + S32(width272)
            # Compute code 
            var i_re146 = S32(0)
            while (i_re146) < (vsize_re1): 
                rec7[i_re146] = ((rec7[(i_re146) - (S32(1))]) * (slow8)) + ((abs((dsp.const19) * ((((dsp.const24) * (rec8[i_re146])) + ((dsp.const25) * (rec8[(i_re146) - (S32(1))]))) + ((dsp.const24) * (rec8[(i_re146) - (S32(2))]))))) * (slow9))
                i_re146 = (i_re146) + (S32(1))
            # Post code 
            var j25_re1 = S32(0)
            while (j25_re1) < (S32(4)): 
                dsp.rec7_perm[j25_re1] = rec7_tmp[(vsize_re1) + (j25_re1)]
                j25_re1 = (j25_re1) + (S32(1))
            # Recursive loop 18 
            # Pre code 
            var j26_re1 = S32(0)
            comptime dtype274 = f64
            comptime width274 = S32(simd_width_of[dtype274]())
            while j26_re1 <= S32(4) - width274:
                var values = simd_load(dsp.rec17_perm, j26_re1)
                simd_store(rec17_tmp, j26_re1, values)
                j26_re1 = j26_re1 + S32(width274)
            # Compute code 
            var i_re147 = S32(0)
            while (i_re147) < (vsize_re1): 
                rec17[i_re147] = (zec5[i_re147]) - ((dsp.const26) * (((dsp.const27) * (rec17[(i_re147) - (S32(2))])) + ((dsp.const28) * (rec17[(i_re147) - (S32(1))]))))
                i_re147 = (i_re147) + (S32(1))
            # Post code 
            var j27_re1 = S32(0)
            while (j27_re1) < (S32(4)): 
                dsp.rec17_perm[j27_re1] = rec17_tmp[(vsize_re1) + (j27_re1)]
                j27_re1 = (j27_re1) + (S32(1))
            # Recursive loop 19 
            # Pre code 
            var j28_re1 = S32(0)
            comptime dtype276 = f64
            comptime width276 = S32(simd_width_of[dtype276]())
            while j28_re1 <= S32(4) - width276:
                var values = simd_load(dsp.rec16_perm, j28_re1)
                simd_store(rec16_tmp, j28_re1, values)
                j28_re1 = j28_re1 + S32(width276)
            # Compute code 
            var i_re148 = S32(0)
            while (i_re148) < (vsize_re1): 
                rec16[i_re148] = ((dsp.const26) * ((((dsp.const30) * (rec17[i_re148])) + ((dsp.const31) * (rec17[(i_re148) - (S32(1))]))) + ((dsp.const30) * (rec17[(i_re148) - (S32(2))])))) - ((dsp.const32) * (((dsp.const33) * (rec16[(i_re148) - (S32(2))])) + ((dsp.const34) * (rec16[(i_re148) - (S32(1))]))))
                i_re148 = (i_re148) + (S32(1))
            # Post code 
            var j29_re1 = S32(0)
            while (j29_re1) < (S32(4)): 
                dsp.rec16_perm[j29_re1] = rec16_tmp[(vsize_re1) + (j29_re1)]
                j29_re1 = (j29_re1) + (S32(1))
            # Recursive loop 20 
            # Pre code 
            var j30_re1 = S32(0)
            comptime dtype278 = f64
            comptime width278 = S32(simd_width_of[dtype278]())
            while j30_re1 <= S32(4) - width278:
                var values = simd_load(dsp.rec15_perm, j30_re1)
                simd_store(rec15_tmp, j30_re1, values)
                j30_re1 = j30_re1 + S32(width278)
            # Compute code 
            var i_re149 = S32(0)
            while (i_re149) < (vsize_re1): 
                rec15[i_re149] = ((dsp.const32) * ((((dsp.const35) * (rec16[i_re149])) + ((dsp.const36) * (rec16[(i_re149) - (S32(1))]))) + ((dsp.const35) * (rec16[(i_re149) - (S32(2))])))) - ((dsp.const37) * (((dsp.const38) * (rec15[(i_re149) - (S32(2))])) + ((dsp.const39) * (rec15[(i_re149) - (S32(1))]))))
                i_re149 = (i_re149) + (S32(1))
            # Post code 
            var j31_re1 = S32(0)
            while (j31_re1) < (S32(4)): 
                dsp.rec15_perm[j31_re1] = rec15_tmp[(vsize_re1) + (j31_re1)]
                j31_re1 = (j31_re1) + (S32(1))
            # Vectorizable loop 21 
            # Compute code 
            var i_re150 = S32(0)
            comptime dtype280 = f64
            comptime width280 = S32(simd_width_of[dtype280]())
            while i_re150 <= vsize_re1 - width280:
                var values = (dsp.const37) * ((((dsp.const40) * (simd_load(rec15, i_re150))) + ((dsp.const41) * (simd_load(rec15, i_re150 - S32(1))))) + ((dsp.const40) * (simd_load(rec15, i_re150 - S32(2)))))
                simd_store(zec6, i_re150, values)
                i_re150 = i_re150 + S32(width280)
            # Recursive loop 22 
            # Pre code 
            var j32_re1 = S32(0)
            comptime dtype281 = f64
            comptime width281 = S32(simd_width_of[dtype281]())
            while j32_re1 <= S32(4) - width281:
                var values = simd_load(dsp.rec14_perm, j32_re1)
                simd_store(rec14_tmp, j32_re1, values)
                j32_re1 = j32_re1 + S32(width281)
            # Compute code 
            var i_re151 = S32(0)
            while (i_re151) < (vsize_re1): 
                rec14[i_re151] = (zec6[i_re151]) - ((dsp.const44) * (((dsp.const45) * (rec14[(i_re151) - (S32(2))])) + ((dsp.const48) * (rec14[(i_re151) - (S32(1))]))))
                i_re151 = (i_re151) + (S32(1))
            # Post code 
            var j33_re1 = S32(0)
            while (j33_re1) < (S32(4)): 
                dsp.rec14_perm[j33_re1] = rec14_tmp[(vsize_re1) + (j33_re1)]
                j33_re1 = (j33_re1) + (S32(1))
            # Recursive loop 23 
            # Pre code 
            var j34_re1 = S32(0)
            comptime dtype283 = f64
            comptime width283 = S32(simd_width_of[dtype283]())
            while j34_re1 <= S32(4) - width283:
                var values = simd_load(dsp.rec13_perm, j34_re1)
                simd_store(rec13_tmp, j34_re1, values)
                j34_re1 = j34_re1 + S32(width283)
            # Compute code 
            var i_re152 = S32(0)
            while (i_re152) < (vsize_re1): 
                rec13[i_re152] = ((dsp.const44) * ((((dsp.const50) * (rec14[i_re152])) + ((dsp.const51) * (rec14[(i_re152) - (S32(1))]))) + ((dsp.const50) * (rec14[(i_re152) - (S32(2))])))) - ((dsp.const52) * (((dsp.const53) * (rec13[(i_re152) - (S32(2))])) + ((dsp.const54) * (rec13[(i_re152) - (S32(1))]))))
                i_re152 = (i_re152) + (S32(1))
            # Post code 
            var j35_re1 = S32(0)
            while (j35_re1) < (S32(4)): 
                dsp.rec13_perm[j35_re1] = rec13_tmp[(vsize_re1) + (j35_re1)]
                j35_re1 = (j35_re1) + (S32(1))
            # Recursive loop 24 
            # Pre code 
            var j36_re1 = S32(0)
            comptime dtype285 = f64
            comptime width285 = S32(simd_width_of[dtype285]())
            while j36_re1 <= S32(4) - width285:
                var values = simd_load(dsp.rec12_perm, j36_re1)
                simd_store(rec12_tmp, j36_re1, values)
                j36_re1 = j36_re1 + S32(width285)
            # Compute code 
            var i_re153 = S32(0)
            while (i_re153) < (vsize_re1): 
                rec12[i_re153] = ((dsp.const52) * ((((dsp.const56) * (rec13[i_re153])) + ((dsp.const57) * (rec13[(i_re153) - (S32(1))]))) + ((dsp.const56) * (rec13[(i_re153) - (S32(2))])))) - ((dsp.const58) * (((dsp.const59) * (rec12[(i_re153) - (S32(2))])) + ((dsp.const60) * (rec12[(i_re153) - (S32(1))]))))
                i_re153 = (i_re153) + (S32(1))
            # Post code 
            var j37_re1 = S32(0)
            while (j37_re1) < (S32(4)): 
                dsp.rec12_perm[j37_re1] = rec12_tmp[(vsize_re1) + (j37_re1)]
                j37_re1 = (j37_re1) + (S32(1))
            # Recursive loop 25 
            # Pre code 
            var j38_re1 = S32(0)
            comptime dtype287 = f64
            comptime width287 = S32(simd_width_of[dtype287]())
            while j38_re1 <= S32(4) - width287:
                var values = simd_load(dsp.rec11_perm, j38_re1)
                simd_store(rec11_tmp, j38_re1, values)
                j38_re1 = j38_re1 + S32(width287)
            # Compute code 
            var i_re154 = S32(0)
            while (i_re154) < (vsize_re1): 
                rec11[i_re154] = ((slow8) * (rec11[(i_re154) - (S32(1))])) + ((slow9) * (abs((dsp.const58) * ((((dsp.const62) * (rec12[i_re154])) + ((dsp.const63) * (rec12[(i_re154) - (S32(1))]))) + ((dsp.const62) * (rec12[(i_re154) - (S32(2))]))))))
                i_re154 = (i_re154) + (S32(1))
            # Post code 
            var j39_re1 = S32(0)
            while (j39_re1) < (S32(4)): 
                dsp.rec11_perm[j39_re1] = rec11_tmp[(vsize_re1) + (j39_re1)]
                j39_re1 = (j39_re1) + (S32(1))
            # Recursive loop 26 
            # Pre code 
            var j40_re1 = S32(0)
            comptime dtype289 = f64
            comptime width289 = S32(simd_width_of[dtype289]())
            while j40_re1 <= S32(4) - width289:
                var values = simd_load(dsp.rec24_perm, j40_re1)
                simd_store(rec24_tmp, j40_re1, values)
                j40_re1 = j40_re1 + S32(width289)
            # Compute code 
            var i_re155 = S32(0)
            while (i_re155) < (vsize_re1): 
                rec24[i_re155] = (zec6[i_re155]) - ((dsp.const64) * (((dsp.const65) * (rec24[(i_re155) - (S32(2))])) + ((dsp.const66) * (rec24[(i_re155) - (S32(1))]))))
                i_re155 = (i_re155) + (S32(1))
            # Post code 
            var j41_re1 = S32(0)
            while (j41_re1) < (S32(4)): 
                dsp.rec24_perm[j41_re1] = rec24_tmp[(vsize_re1) + (j41_re1)]
                j41_re1 = (j41_re1) + (S32(1))
            # Recursive loop 27 
            # Pre code 
            var j42_re1 = S32(0)
            comptime dtype291 = f64
            comptime width291 = S32(simd_width_of[dtype291]())
            while j42_re1 <= S32(4) - width291:
                var values = simd_load(dsp.rec23_perm, j42_re1)
                simd_store(rec23_tmp, j42_re1, values)
                j42_re1 = j42_re1 + S32(width291)
            # Compute code 
            var i_re156 = S32(0)
            while (i_re156) < (vsize_re1): 
                rec23[i_re156] = ((dsp.const64) * ((((dsp.const68) * (rec24[i_re156])) + ((dsp.const69) * (rec24[(i_re156) - (S32(1))]))) + ((dsp.const68) * (rec24[(i_re156) - (S32(2))])))) - ((dsp.const70) * (((dsp.const71) * (rec23[(i_re156) - (S32(2))])) + ((dsp.const72) * (rec23[(i_re156) - (S32(1))]))))
                i_re156 = (i_re156) + (S32(1))
            # Post code 
            var j43_re1 = S32(0)
            while (j43_re1) < (S32(4)): 
                dsp.rec23_perm[j43_re1] = rec23_tmp[(vsize_re1) + (j43_re1)]
                j43_re1 = (j43_re1) + (S32(1))
            # Recursive loop 28 
            # Pre code 
            var j44_re1 = S32(0)
            comptime dtype293 = f64
            comptime width293 = S32(simd_width_of[dtype293]())
            while j44_re1 <= S32(4) - width293:
                var values = simd_load(dsp.rec22_perm, j44_re1)
                simd_store(rec22_tmp, j44_re1, values)
                j44_re1 = j44_re1 + S32(width293)
            # Compute code 
            var i_re157 = S32(0)
            while (i_re157) < (vsize_re1): 
                rec22[i_re157] = ((dsp.const70) * ((((dsp.const73) * (rec23[i_re157])) + ((dsp.const74) * (rec23[(i_re157) - (S32(1))]))) + ((dsp.const73) * (rec23[(i_re157) - (S32(2))])))) - ((dsp.const75) * (((dsp.const76) * (rec22[(i_re157) - (S32(2))])) + ((dsp.const77) * (rec22[(i_re157) - (S32(1))]))))
                i_re157 = (i_re157) + (S32(1))
            # Post code 
            var j45_re1 = S32(0)
            while (j45_re1) < (S32(4)): 
                dsp.rec22_perm[j45_re1] = rec22_tmp[(vsize_re1) + (j45_re1)]
                j45_re1 = (j45_re1) + (S32(1))
            # Vectorizable loop 29 
            # Compute code 
            var i_re158 = S32(0)
            comptime dtype295 = f64
            comptime width295 = S32(simd_width_of[dtype295]())
            while i_re158 <= vsize_re1 - width295:
                var values = (dsp.const75) * ((((dsp.const78) * (simd_load(rec22, i_re158))) + ((dsp.const79) * (simd_load(rec22, i_re158 - S32(1))))) + ((dsp.const78) * (simd_load(rec22, i_re158 - S32(2)))))
                simd_store(zec7, i_re158, values)
                i_re158 = i_re158 + S32(width295)
            # Recursive loop 30 
            # Pre code 
            var j46_re1 = S32(0)
            comptime dtype296 = f64
            comptime width296 = S32(simd_width_of[dtype296]())
            while j46_re1 <= S32(4) - width296:
                var values = simd_load(dsp.rec21_perm, j46_re1)
                simd_store(rec21_tmp, j46_re1, values)
                j46_re1 = j46_re1 + S32(width296)
            # Compute code 
            var i_re159 = S32(0)
            while (i_re159) < (vsize_re1): 
                rec21[i_re159] = (zec7[i_re159]) - ((dsp.const82) * (((dsp.const83) * (rec21[(i_re159) - (S32(2))])) + ((dsp.const86) * (rec21[(i_re159) - (S32(1))]))))
                i_re159 = (i_re159) + (S32(1))
            # Post code 
            var j47_re1 = S32(0)
            while (j47_re1) < (S32(4)): 
                dsp.rec21_perm[j47_re1] = rec21_tmp[(vsize_re1) + (j47_re1)]
                j47_re1 = (j47_re1) + (S32(1))
            # Recursive loop 31 
            # Pre code 
            var j48_re1 = S32(0)
            comptime dtype298 = f64
            comptime width298 = S32(simd_width_of[dtype298]())
            while j48_re1 <= S32(4) - width298:
                var values = simd_load(dsp.rec20_perm, j48_re1)
                simd_store(rec20_tmp, j48_re1, values)
                j48_re1 = j48_re1 + S32(width298)
            # Compute code 
            var i_re160 = S32(0)
            while (i_re160) < (vsize_re1): 
                rec20[i_re160] = ((dsp.const82) * ((((dsp.const88) * (rec21[i_re160])) + ((dsp.const89) * (rec21[(i_re160) - (S32(1))]))) + ((dsp.const88) * (rec21[(i_re160) - (S32(2))])))) - ((dsp.const90) * (((dsp.const91) * (rec20[(i_re160) - (S32(2))])) + ((dsp.const92) * (rec20[(i_re160) - (S32(1))]))))
                i_re160 = (i_re160) + (S32(1))
            # Post code 
            var j49_re1 = S32(0)
            while (j49_re1) < (S32(4)): 
                dsp.rec20_perm[j49_re1] = rec20_tmp[(vsize_re1) + (j49_re1)]
                j49_re1 = (j49_re1) + (S32(1))
            # Recursive loop 32 
            # Pre code 
            var j50_re1 = S32(0)
            comptime dtype300 = f64
            comptime width300 = S32(simd_width_of[dtype300]())
            while j50_re1 <= S32(4) - width300:
                var values = simd_load(dsp.rec19_perm, j50_re1)
                simd_store(rec19_tmp, j50_re1, values)
                j50_re1 = j50_re1 + S32(width300)
            # Compute code 
            var i_re161 = S32(0)
            while (i_re161) < (vsize_re1): 
                rec19[i_re161] = ((dsp.const90) * ((((dsp.const94) * (rec20[i_re161])) + ((dsp.const95) * (rec20[(i_re161) - (S32(1))]))) + ((dsp.const94) * (rec20[(i_re161) - (S32(2))])))) - ((dsp.const96) * (((dsp.const97) * (rec19[(i_re161) - (S32(2))])) + ((dsp.const98) * (rec19[(i_re161) - (S32(1))]))))
                i_re161 = (i_re161) + (S32(1))
            # Post code 
            var j51_re1 = S32(0)
            while (j51_re1) < (S32(4)): 
                dsp.rec19_perm[j51_re1] = rec19_tmp[(vsize_re1) + (j51_re1)]
                j51_re1 = (j51_re1) + (S32(1))
            # Recursive loop 33 
            # Pre code 
            var j52_re1 = S32(0)
            comptime dtype302 = f64
            comptime width302 = S32(simd_width_of[dtype302]())
            while j52_re1 <= S32(4) - width302:
                var values = simd_load(dsp.rec18_perm, j52_re1)
                simd_store(rec18_tmp, j52_re1, values)
                j52_re1 = j52_re1 + S32(width302)
            # Compute code 
            var i_re162 = S32(0)
            while (i_re162) < (vsize_re1): 
                rec18[i_re162] = ((slow8) * (rec18[(i_re162) - (S32(1))])) + ((slow9) * (abs((dsp.const96) * ((((dsp.const100) * (rec19[i_re162])) + ((dsp.const101) * (rec19[(i_re162) - (S32(1))]))) + ((dsp.const100) * (rec19[(i_re162) - (S32(2))]))))))
                i_re162 = (i_re162) + (S32(1))
            # Post code 
            var j53_re1 = S32(0)
            while (j53_re1) < (S32(4)): 
                dsp.rec18_perm[j53_re1] = rec18_tmp[(vsize_re1) + (j53_re1)]
                j53_re1 = (j53_re1) + (S32(1))
            # Recursive loop 34 
            # Pre code 
            var j54_re1 = S32(0)
            comptime dtype304 = f64
            comptime width304 = S32(simd_width_of[dtype304]())
            while j54_re1 <= S32(4) - width304:
                var values = simd_load(dsp.rec31_perm, j54_re1)
                simd_store(rec31_tmp, j54_re1, values)
                j54_re1 = j54_re1 + S32(width304)
            # Compute code 
            var i_re163 = S32(0)
            while (i_re163) < (vsize_re1): 
                rec31[i_re163] = (zec7[i_re163]) - ((dsp.const102) * (((dsp.const103) * (rec31[(i_re163) - (S32(2))])) + ((dsp.const104) * (rec31[(i_re163) - (S32(1))]))))
                i_re163 = (i_re163) + (S32(1))
            # Post code 
            var j55_re1 = S32(0)
            while (j55_re1) < (S32(4)): 
                dsp.rec31_perm[j55_re1] = rec31_tmp[(vsize_re1) + (j55_re1)]
                j55_re1 = (j55_re1) + (S32(1))
            # Recursive loop 35 
            # Pre code 
            var j56_re1 = S32(0)
            comptime dtype306 = f64
            comptime width306 = S32(simd_width_of[dtype306]())
            while j56_re1 <= S32(4) - width306:
                var values = simd_load(dsp.rec30_perm, j56_re1)
                simd_store(rec30_tmp, j56_re1, values)
                j56_re1 = j56_re1 + S32(width306)
            # Compute code 
            var i_re164 = S32(0)
            while (i_re164) < (vsize_re1): 
                rec30[i_re164] = ((dsp.const102) * ((((dsp.const106) * (rec31[i_re164])) + ((dsp.const107) * (rec31[(i_re164) - (S32(1))]))) + ((dsp.const106) * (rec31[(i_re164) - (S32(2))])))) - ((dsp.const108) * (((dsp.const109) * (rec30[(i_re164) - (S32(2))])) + ((dsp.const110) * (rec30[(i_re164) - (S32(1))]))))
                i_re164 = (i_re164) + (S32(1))
            # Post code 
            var j57_re1 = S32(0)
            while (j57_re1) < (S32(4)): 
                dsp.rec30_perm[j57_re1] = rec30_tmp[(vsize_re1) + (j57_re1)]
                j57_re1 = (j57_re1) + (S32(1))
            # Recursive loop 36 
            # Pre code 
            var j58_re1 = S32(0)
            comptime dtype308 = f64
            comptime width308 = S32(simd_width_of[dtype308]())
            while j58_re1 <= S32(4) - width308:
                var values = simd_load(dsp.rec29_perm, j58_re1)
                simd_store(rec29_tmp, j58_re1, values)
                j58_re1 = j58_re1 + S32(width308)
            # Compute code 
            var i_re165 = S32(0)
            while (i_re165) < (vsize_re1): 
                rec29[i_re165] = ((dsp.const108) * ((((dsp.const111) * (rec30[i_re165])) + ((dsp.const112) * (rec30[(i_re165) - (S32(1))]))) + ((dsp.const111) * (rec30[(i_re165) - (S32(2))])))) - ((dsp.const113) * (((dsp.const114) * (rec29[(i_re165) - (S32(2))])) + ((dsp.const115) * (rec29[(i_re165) - (S32(1))]))))
                i_re165 = (i_re165) + (S32(1))
            # Post code 
            var j59_re1 = S32(0)
            while (j59_re1) < (S32(4)): 
                dsp.rec29_perm[j59_re1] = rec29_tmp[(vsize_re1) + (j59_re1)]
                j59_re1 = (j59_re1) + (S32(1))
            # Vectorizable loop 37 
            # Compute code 
            var i_re166 = S32(0)
            comptime dtype310 = f64
            comptime width310 = S32(simd_width_of[dtype310]())
            while i_re166 <= vsize_re1 - width310:
                var values = (dsp.const113) * ((((dsp.const116) * (simd_load(rec29, i_re166))) + ((dsp.const117) * (simd_load(rec29, i_re166 - S32(1))))) + ((dsp.const116) * (simd_load(rec29, i_re166 - S32(2)))))
                simd_store(zec8, i_re166, values)
                i_re166 = i_re166 + S32(width310)
            # Recursive loop 38 
            # Pre code 
            var j60_re1 = S32(0)
            comptime dtype311 = f64
            comptime width311 = S32(simd_width_of[dtype311]())
            while j60_re1 <= S32(4) - width311:
                var values = simd_load(dsp.rec28_perm, j60_re1)
                simd_store(rec28_tmp, j60_re1, values)
                j60_re1 = j60_re1 + S32(width311)
            # Compute code 
            var i_re167 = S32(0)
            while (i_re167) < (vsize_re1): 
                rec28[i_re167] = (zec8[i_re167]) - ((dsp.const120) * (((dsp.const121) * (rec28[(i_re167) - (S32(2))])) + ((dsp.const124) * (rec28[(i_re167) - (S32(1))]))))
                i_re167 = (i_re167) + (S32(1))
            # Post code 
            var j61_re1 = S32(0)
            while (j61_re1) < (S32(4)): 
                dsp.rec28_perm[j61_re1] = rec28_tmp[(vsize_re1) + (j61_re1)]
                j61_re1 = (j61_re1) + (S32(1))
            # Recursive loop 39 
            # Pre code 
            var j62_re1 = S32(0)
            comptime dtype313 = f64
            comptime width313 = S32(simd_width_of[dtype313]())
            while j62_re1 <= S32(4) - width313:
                var values = simd_load(dsp.rec27_perm, j62_re1)
                simd_store(rec27_tmp, j62_re1, values)
                j62_re1 = j62_re1 + S32(width313)
            # Compute code 
            var i_re168 = S32(0)
            while (i_re168) < (vsize_re1): 
                rec27[i_re168] = ((dsp.const120) * ((((dsp.const126) * (rec28[i_re168])) + ((dsp.const127) * (rec28[(i_re168) - (S32(1))]))) + ((dsp.const126) * (rec28[(i_re168) - (S32(2))])))) - ((dsp.const128) * (((dsp.const129) * (rec27[(i_re168) - (S32(2))])) + ((dsp.const130) * (rec27[(i_re168) - (S32(1))]))))
                i_re168 = (i_re168) + (S32(1))
            # Post code 
            var j63_re1 = S32(0)
            while (j63_re1) < (S32(4)): 
                dsp.rec27_perm[j63_re1] = rec27_tmp[(vsize_re1) + (j63_re1)]
                j63_re1 = (j63_re1) + (S32(1))
            # Recursive loop 40 
            # Pre code 
            var j64_re1 = S32(0)
            comptime dtype315 = f64
            comptime width315 = S32(simd_width_of[dtype315]())
            while j64_re1 <= S32(4) - width315:
                var values = simd_load(dsp.rec26_perm, j64_re1)
                simd_store(rec26_tmp, j64_re1, values)
                j64_re1 = j64_re1 + S32(width315)
            # Compute code 
            var i_re169 = S32(0)
            while (i_re169) < (vsize_re1): 
                rec26[i_re169] = ((dsp.const128) * ((((dsp.const132) * (rec27[i_re169])) + ((dsp.const133) * (rec27[(i_re169) - (S32(1))]))) + ((dsp.const132) * (rec27[(i_re169) - (S32(2))])))) - ((dsp.const134) * (((dsp.const135) * (rec26[(i_re169) - (S32(2))])) + ((dsp.const136) * (rec26[(i_re169) - (S32(1))]))))
                i_re169 = (i_re169) + (S32(1))
            # Post code 
            var j65_re1 = S32(0)
            while (j65_re1) < (S32(4)): 
                dsp.rec26_perm[j65_re1] = rec26_tmp[(vsize_re1) + (j65_re1)]
                j65_re1 = (j65_re1) + (S32(1))
            # Recursive loop 41 
            # Pre code 
            var j66_re1 = S32(0)
            comptime dtype317 = f64
            comptime width317 = S32(simd_width_of[dtype317]())
            while j66_re1 <= S32(4) - width317:
                var values = simd_load(dsp.rec25_perm, j66_re1)
                simd_store(rec25_tmp, j66_re1, values)
                j66_re1 = j66_re1 + S32(width317)
            # Compute code 
            var i_re170 = S32(0)
            while (i_re170) < (vsize_re1): 
                rec25[i_re170] = ((slow8) * (rec25[(i_re170) - (S32(1))])) + ((slow9) * (abs((dsp.const134) * ((((dsp.const138) * (rec26[i_re170])) + ((dsp.const139) * (rec26[(i_re170) - (S32(1))]))) + ((dsp.const138) * (rec26[(i_re170) - (S32(2))]))))))
                i_re170 = (i_re170) + (S32(1))
            # Post code 
            var j67_re1 = S32(0)
            while (j67_re1) < (S32(4)): 
                dsp.rec25_perm[j67_re1] = rec25_tmp[(vsize_re1) + (j67_re1)]
                j67_re1 = (j67_re1) + (S32(1))
            # Recursive loop 42 
            # Pre code 
            var j68_re1 = S32(0)
            comptime dtype319 = f64
            comptime width319 = S32(simd_width_of[dtype319]())
            while j68_re1 <= S32(4) - width319:
                var values = simd_load(dsp.rec38_perm, j68_re1)
                simd_store(rec38_tmp, j68_re1, values)
                j68_re1 = j68_re1 + S32(width319)
            # Compute code 
            var i_re171 = S32(0)
            while (i_re171) < (vsize_re1): 
                rec38[i_re171] = (zec8[i_re171]) - ((dsp.const140) * (((dsp.const141) * (rec38[(i_re171) - (S32(2))])) + ((dsp.const142) * (rec38[(i_re171) - (S32(1))]))))
                i_re171 = (i_re171) + (S32(1))
            # Post code 
            var j69_re1 = S32(0)
            while (j69_re1) < (S32(4)): 
                dsp.rec38_perm[j69_re1] = rec38_tmp[(vsize_re1) + (j69_re1)]
                j69_re1 = (j69_re1) + (S32(1))
            # Recursive loop 43 
            # Pre code 
            var j70_re1 = S32(0)
            comptime dtype321 = f64
            comptime width321 = S32(simd_width_of[dtype321]())
            while j70_re1 <= S32(4) - width321:
                var values = simd_load(dsp.rec37_perm, j70_re1)
                simd_store(rec37_tmp, j70_re1, values)
                j70_re1 = j70_re1 + S32(width321)
            # Compute code 
            var i_re172 = S32(0)
            while (i_re172) < (vsize_re1): 
                rec37[i_re172] = ((dsp.const140) * ((((dsp.const144) * (rec38[i_re172])) + ((dsp.const145) * (rec38[(i_re172) - (S32(1))]))) + ((dsp.const144) * (rec38[(i_re172) - (S32(2))])))) - ((dsp.const146) * (((dsp.const147) * (rec37[(i_re172) - (S32(2))])) + ((dsp.const148) * (rec37[(i_re172) - (S32(1))]))))
                i_re172 = (i_re172) + (S32(1))
            # Post code 
            var j71_re1 = S32(0)
            while (j71_re1) < (S32(4)): 
                dsp.rec37_perm[j71_re1] = rec37_tmp[(vsize_re1) + (j71_re1)]
                j71_re1 = (j71_re1) + (S32(1))
            # Recursive loop 44 
            # Pre code 
            var j72_re1 = S32(0)
            comptime dtype323 = f64
            comptime width323 = S32(simd_width_of[dtype323]())
            while j72_re1 <= S32(4) - width323:
                var values = simd_load(dsp.rec36_perm, j72_re1)
                simd_store(rec36_tmp, j72_re1, values)
                j72_re1 = j72_re1 + S32(width323)
            # Compute code 
            var i_re173 = S32(0)
            while (i_re173) < (vsize_re1): 
                rec36[i_re173] = ((dsp.const146) * ((((dsp.const149) * (rec37[i_re173])) + ((dsp.const150) * (rec37[(i_re173) - (S32(1))]))) + ((dsp.const149) * (rec37[(i_re173) - (S32(2))])))) - ((dsp.const151) * (((dsp.const152) * (rec36[(i_re173) - (S32(2))])) + ((dsp.const153) * (rec36[(i_re173) - (S32(1))]))))
                i_re173 = (i_re173) + (S32(1))
            # Post code 
            var j73_re1 = S32(0)
            while (j73_re1) < (S32(4)): 
                dsp.rec36_perm[j73_re1] = rec36_tmp[(vsize_re1) + (j73_re1)]
                j73_re1 = (j73_re1) + (S32(1))
            # Vectorizable loop 45 
            # Compute code 
            var i_re174 = S32(0)
            comptime dtype325 = f64
            comptime width325 = S32(simd_width_of[dtype325]())
            while i_re174 <= vsize_re1 - width325:
                var values = (dsp.const151) * ((((dsp.const154) * (simd_load(rec36, i_re174))) + ((dsp.const155) * (simd_load(rec36, i_re174 - S32(1))))) + ((dsp.const154) * (simd_load(rec36, i_re174 - S32(2)))))
                simd_store(zec9, i_re174, values)
                i_re174 = i_re174 + S32(width325)
            # Recursive loop 46 
            # Pre code 
            var j74_re1 = S32(0)
            comptime dtype326 = f64
            comptime width326 = S32(simd_width_of[dtype326]())
            while j74_re1 <= S32(4) - width326:
                var values = simd_load(dsp.rec35_perm, j74_re1)
                simd_store(rec35_tmp, j74_re1, values)
                j74_re1 = j74_re1 + S32(width326)
            # Compute code 
            var i_re175 = S32(0)
            while (i_re175) < (vsize_re1): 
                rec35[i_re175] = (zec9[i_re175]) - ((dsp.const158) * (((dsp.const159) * (rec35[(i_re175) - (S32(2))])) + ((dsp.const162) * (rec35[(i_re175) - (S32(1))]))))
                i_re175 = (i_re175) + (S32(1))
            # Post code 
            var j75_re1 = S32(0)
            while (j75_re1) < (S32(4)): 
                dsp.rec35_perm[j75_re1] = rec35_tmp[(vsize_re1) + (j75_re1)]
                j75_re1 = (j75_re1) + (S32(1))
            # Recursive loop 47 
            # Pre code 
            var j76_re1 = S32(0)
            comptime dtype328 = f64
            comptime width328 = S32(simd_width_of[dtype328]())
            while j76_re1 <= S32(4) - width328:
                var values = simd_load(dsp.rec34_perm, j76_re1)
                simd_store(rec34_tmp, j76_re1, values)
                j76_re1 = j76_re1 + S32(width328)
            # Compute code 
            var i_re176 = S32(0)
            while (i_re176) < (vsize_re1): 
                rec34[i_re176] = ((dsp.const158) * ((((dsp.const164) * (rec35[i_re176])) + ((dsp.const165) * (rec35[(i_re176) - (S32(1))]))) + ((dsp.const164) * (rec35[(i_re176) - (S32(2))])))) - ((dsp.const166) * (((dsp.const167) * (rec34[(i_re176) - (S32(2))])) + ((dsp.const168) * (rec34[(i_re176) - (S32(1))]))))
                i_re176 = (i_re176) + (S32(1))
            # Post code 
            var j77_re1 = S32(0)
            while (j77_re1) < (S32(4)): 
                dsp.rec34_perm[j77_re1] = rec34_tmp[(vsize_re1) + (j77_re1)]
                j77_re1 = (j77_re1) + (S32(1))
            # Recursive loop 48 
            # Pre code 
            var j78_re1 = S32(0)
            comptime dtype330 = f64
            comptime width330 = S32(simd_width_of[dtype330]())
            while j78_re1 <= S32(4) - width330:
                var values = simd_load(dsp.rec33_perm, j78_re1)
                simd_store(rec33_tmp, j78_re1, values)
                j78_re1 = j78_re1 + S32(width330)
            # Compute code 
            var i_re177 = S32(0)
            while (i_re177) < (vsize_re1): 
                rec33[i_re177] = ((dsp.const166) * ((((dsp.const170) * (rec34[i_re177])) + ((dsp.const171) * (rec34[(i_re177) - (S32(1))]))) + ((dsp.const170) * (rec34[(i_re177) - (S32(2))])))) - ((dsp.const172) * (((dsp.const173) * (rec33[(i_re177) - (S32(2))])) + ((dsp.const174) * (rec33[(i_re177) - (S32(1))]))))
                i_re177 = (i_re177) + (S32(1))
            # Post code 
            var j79_re1 = S32(0)
            while (j79_re1) < (S32(4)): 
                dsp.rec33_perm[j79_re1] = rec33_tmp[(vsize_re1) + (j79_re1)]
                j79_re1 = (j79_re1) + (S32(1))
            # Recursive loop 49 
            # Pre code 
            var j80_re1 = S32(0)
            comptime dtype332 = f64
            comptime width332 = S32(simd_width_of[dtype332]())
            while j80_re1 <= S32(4) - width332:
                var values = simd_load(dsp.rec32_perm, j80_re1)
                simd_store(rec32_tmp, j80_re1, values)
                j80_re1 = j80_re1 + S32(width332)
            # Compute code 
            var i_re178 = S32(0)
            while (i_re178) < (vsize_re1): 
                rec32[i_re178] = ((slow8) * (rec32[(i_re178) - (S32(1))])) + ((slow9) * (abs((dsp.const172) * ((((dsp.const176) * (rec33[i_re178])) + ((dsp.const177) * (rec33[(i_re178) - (S32(1))]))) + ((dsp.const176) * (rec33[(i_re178) - (S32(2))]))))))
                i_re178 = (i_re178) + (S32(1))
            # Post code 
            var j81_re1 = S32(0)
            while (j81_re1) < (S32(4)): 
                dsp.rec32_perm[j81_re1] = rec32_tmp[(vsize_re1) + (j81_re1)]
                j81_re1 = (j81_re1) + (S32(1))
            # Recursive loop 50 
            # Pre code 
            var j82_re1 = S32(0)
            comptime dtype334 = f64
            comptime width334 = S32(simd_width_of[dtype334]())
            while j82_re1 <= S32(4) - width334:
                var values = simd_load(dsp.rec45_perm, j82_re1)
                simd_store(rec45_tmp, j82_re1, values)
                j82_re1 = j82_re1 + S32(width334)
            # Compute code 
            var i_re179 = S32(0)
            while (i_re179) < (vsize_re1): 
                rec45[i_re179] = (zec9[i_re179]) - ((dsp.const178) * (((dsp.const179) * (rec45[(i_re179) - (S32(2))])) + ((dsp.const180) * (rec45[(i_re179) - (S32(1))]))))
                i_re179 = (i_re179) + (S32(1))
            # Post code 
            var j83_re1 = S32(0)
            while (j83_re1) < (S32(4)): 
                dsp.rec45_perm[j83_re1] = rec45_tmp[(vsize_re1) + (j83_re1)]
                j83_re1 = (j83_re1) + (S32(1))
            # Recursive loop 51 
            # Pre code 
            var j84_re1 = S32(0)
            comptime dtype336 = f64
            comptime width336 = S32(simd_width_of[dtype336]())
            while j84_re1 <= S32(4) - width336:
                var values = simd_load(dsp.rec44_perm, j84_re1)
                simd_store(rec44_tmp, j84_re1, values)
                j84_re1 = j84_re1 + S32(width336)
            # Compute code 
            var i_re180 = S32(0)
            while (i_re180) < (vsize_re1): 
                rec44[i_re180] = ((dsp.const178) * ((((dsp.const182) * (rec45[i_re180])) + ((dsp.const183) * (rec45[(i_re180) - (S32(1))]))) + ((dsp.const182) * (rec45[(i_re180) - (S32(2))])))) - ((dsp.const184) * (((dsp.const185) * (rec44[(i_re180) - (S32(2))])) + ((dsp.const186) * (rec44[(i_re180) - (S32(1))]))))
                i_re180 = (i_re180) + (S32(1))
            # Post code 
            var j85_re1 = S32(0)
            while (j85_re1) < (S32(4)): 
                dsp.rec44_perm[j85_re1] = rec44_tmp[(vsize_re1) + (j85_re1)]
                j85_re1 = (j85_re1) + (S32(1))
            # Recursive loop 52 
            # Pre code 
            var j86_re1 = S32(0)
            comptime dtype338 = f64
            comptime width338 = S32(simd_width_of[dtype338]())
            while j86_re1 <= S32(4) - width338:
                var values = simd_load(dsp.rec43_perm, j86_re1)
                simd_store(rec43_tmp, j86_re1, values)
                j86_re1 = j86_re1 + S32(width338)
            # Compute code 
            var i_re181 = S32(0)
            while (i_re181) < (vsize_re1): 
                rec43[i_re181] = ((dsp.const184) * ((((dsp.const187) * (rec44[i_re181])) + ((dsp.const188) * (rec44[(i_re181) - (S32(1))]))) + ((dsp.const187) * (rec44[(i_re181) - (S32(2))])))) - ((dsp.const189) * (((dsp.const190) * (rec43[(i_re181) - (S32(2))])) + ((dsp.const191) * (rec43[(i_re181) - (S32(1))]))))
                i_re181 = (i_re181) + (S32(1))
            # Post code 
            var j87_re1 = S32(0)
            while (j87_re1) < (S32(4)): 
                dsp.rec43_perm[j87_re1] = rec43_tmp[(vsize_re1) + (j87_re1)]
                j87_re1 = (j87_re1) + (S32(1))
            # Vectorizable loop 53 
            # Compute code 
            var i_re182 = S32(0)
            comptime dtype340 = f64
            comptime width340 = S32(simd_width_of[dtype340]())
            while i_re182 <= vsize_re1 - width340:
                var values = (dsp.const189) * ((((dsp.const192) * (simd_load(rec43, i_re182))) + ((dsp.const193) * (simd_load(rec43, i_re182 - S32(1))))) + ((dsp.const192) * (simd_load(rec43, i_re182 - S32(2)))))
                simd_store(zec10, i_re182, values)
                i_re182 = i_re182 + S32(width340)
            # Recursive loop 54 
            # Pre code 
            var j88_re1 = S32(0)
            comptime dtype341 = f64
            comptime width341 = S32(simd_width_of[dtype341]())
            while j88_re1 <= S32(4) - width341:
                var values = simd_load(dsp.rec42_perm, j88_re1)
                simd_store(rec42_tmp, j88_re1, values)
                j88_re1 = j88_re1 + S32(width341)
            # Compute code 
            var i_re183 = S32(0)
            while (i_re183) < (vsize_re1): 
                rec42[i_re183] = (zec10[i_re183]) - ((dsp.const196) * (((dsp.const197) * (rec42[(i_re183) - (S32(2))])) + ((dsp.const200) * (rec42[(i_re183) - (S32(1))]))))
                i_re183 = (i_re183) + (S32(1))
            # Post code 
            var j89_re1 = S32(0)
            while (j89_re1) < (S32(4)): 
                dsp.rec42_perm[j89_re1] = rec42_tmp[(vsize_re1) + (j89_re1)]
                j89_re1 = (j89_re1) + (S32(1))
            # Recursive loop 55 
            # Pre code 
            var j90_re1 = S32(0)
            comptime dtype343 = f64
            comptime width343 = S32(simd_width_of[dtype343]())
            while j90_re1 <= S32(4) - width343:
                var values = simd_load(dsp.rec41_perm, j90_re1)
                simd_store(rec41_tmp, j90_re1, values)
                j90_re1 = j90_re1 + S32(width343)
            # Compute code 
            var i_re184 = S32(0)
            while (i_re184) < (vsize_re1): 
                rec41[i_re184] = ((dsp.const196) * ((((dsp.const202) * (rec42[i_re184])) + ((dsp.const203) * (rec42[(i_re184) - (S32(1))]))) + ((dsp.const202) * (rec42[(i_re184) - (S32(2))])))) - ((dsp.const204) * (((dsp.const205) * (rec41[(i_re184) - (S32(2))])) + ((dsp.const206) * (rec41[(i_re184) - (S32(1))]))))
                i_re184 = (i_re184) + (S32(1))
            # Post code 
            var j91_re1 = S32(0)
            while (j91_re1) < (S32(4)): 
                dsp.rec41_perm[j91_re1] = rec41_tmp[(vsize_re1) + (j91_re1)]
                j91_re1 = (j91_re1) + (S32(1))
            # Recursive loop 56 
            # Pre code 
            var j92_re1 = S32(0)
            comptime dtype345 = f64
            comptime width345 = S32(simd_width_of[dtype345]())
            while j92_re1 <= S32(4) - width345:
                var values = simd_load(dsp.rec40_perm, j92_re1)
                simd_store(rec40_tmp, j92_re1, values)
                j92_re1 = j92_re1 + S32(width345)
            # Compute code 
            var i_re185 = S32(0)
            while (i_re185) < (vsize_re1): 
                rec40[i_re185] = ((dsp.const204) * ((((dsp.const208) * (rec41[i_re185])) + ((dsp.const209) * (rec41[(i_re185) - (S32(1))]))) + ((dsp.const208) * (rec41[(i_re185) - (S32(2))])))) - ((dsp.const210) * (((dsp.const211) * (rec40[(i_re185) - (S32(2))])) + ((dsp.const212) * (rec40[(i_re185) - (S32(1))]))))
                i_re185 = (i_re185) + (S32(1))
            # Post code 
            var j93_re1 = S32(0)
            while (j93_re1) < (S32(4)): 
                dsp.rec40_perm[j93_re1] = rec40_tmp[(vsize_re1) + (j93_re1)]
                j93_re1 = (j93_re1) + (S32(1))
            # Recursive loop 57 
            # Pre code 
            var j94_re1 = S32(0)
            comptime dtype347 = f64
            comptime width347 = S32(simd_width_of[dtype347]())
            while j94_re1 <= S32(4) - width347:
                var values = simd_load(dsp.rec39_perm, j94_re1)
                simd_store(rec39_tmp, j94_re1, values)
                j94_re1 = j94_re1 + S32(width347)
            # Compute code 
            var i_re186 = S32(0)
            while (i_re186) < (vsize_re1): 
                rec39[i_re186] = ((slow8) * (rec39[(i_re186) - (S32(1))])) + ((slow9) * (abs((dsp.const210) * ((((dsp.const214) * (rec40[i_re186])) + ((dsp.const215) * (rec40[(i_re186) - (S32(1))]))) + ((dsp.const214) * (rec40[(i_re186) - (S32(2))]))))))
                i_re186 = (i_re186) + (S32(1))
            # Post code 
            var j95_re1 = S32(0)
            while (j95_re1) < (S32(4)): 
                dsp.rec39_perm[j95_re1] = rec39_tmp[(vsize_re1) + (j95_re1)]
                j95_re1 = (j95_re1) + (S32(1))
            # Recursive loop 58 
            # Pre code 
            var j96_re1 = S32(0)
            comptime dtype349 = f64
            comptime width349 = S32(simd_width_of[dtype349]())
            while j96_re1 <= S32(4) - width349:
                var values = simd_load(dsp.rec52_perm, j96_re1)
                simd_store(rec52_tmp, j96_re1, values)
                j96_re1 = j96_re1 + S32(width349)
            # Compute code 
            var i_re187 = S32(0)
            while (i_re187) < (vsize_re1): 
                rec52[i_re187] = (zec10[i_re187]) - ((dsp.const216) * (((dsp.const217) * (rec52[(i_re187) - (S32(2))])) + ((dsp.const218) * (rec52[(i_re187) - (S32(1))]))))
                i_re187 = (i_re187) + (S32(1))
            # Post code 
            var j97_re1 = S32(0)
            while (j97_re1) < (S32(4)): 
                dsp.rec52_perm[j97_re1] = rec52_tmp[(vsize_re1) + (j97_re1)]
                j97_re1 = (j97_re1) + (S32(1))
            # Recursive loop 59 
            # Pre code 
            var j98_re1 = S32(0)
            comptime dtype351 = f64
            comptime width351 = S32(simd_width_of[dtype351]())
            while j98_re1 <= S32(4) - width351:
                var values = simd_load(dsp.rec51_perm, j98_re1)
                simd_store(rec51_tmp, j98_re1, values)
                j98_re1 = j98_re1 + S32(width351)
            # Compute code 
            var i_re188 = S32(0)
            while (i_re188) < (vsize_re1): 
                rec51[i_re188] = ((dsp.const216) * ((((dsp.const220) * (rec52[i_re188])) + ((dsp.const221) * (rec52[(i_re188) - (S32(1))]))) + ((dsp.const220) * (rec52[(i_re188) - (S32(2))])))) - ((dsp.const222) * (((dsp.const223) * (rec51[(i_re188) - (S32(2))])) + ((dsp.const224) * (rec51[(i_re188) - (S32(1))]))))
                i_re188 = (i_re188) + (S32(1))
            # Post code 
            var j99_re1 = S32(0)
            while (j99_re1) < (S32(4)): 
                dsp.rec51_perm[j99_re1] = rec51_tmp[(vsize_re1) + (j99_re1)]
                j99_re1 = (j99_re1) + (S32(1))
            # Recursive loop 60 
            # Pre code 
            var j100_re1 = S32(0)
            comptime dtype353 = f64
            comptime width353 = S32(simd_width_of[dtype353]())
            while j100_re1 <= S32(4) - width353:
                var values = simd_load(dsp.rec50_perm, j100_re1)
                simd_store(rec50_tmp, j100_re1, values)
                j100_re1 = j100_re1 + S32(width353)
            # Compute code 
            var i_re189 = S32(0)
            while (i_re189) < (vsize_re1): 
                rec50[i_re189] = ((dsp.const222) * ((((dsp.const225) * (rec51[i_re189])) + ((dsp.const226) * (rec51[(i_re189) - (S32(1))]))) + ((dsp.const225) * (rec51[(i_re189) - (S32(2))])))) - ((dsp.const227) * (((dsp.const228) * (rec50[(i_re189) - (S32(2))])) + ((dsp.const229) * (rec50[(i_re189) - (S32(1))]))))
                i_re189 = (i_re189) + (S32(1))
            # Post code 
            var j101_re1 = S32(0)
            while (j101_re1) < (S32(4)): 
                dsp.rec50_perm[j101_re1] = rec50_tmp[(vsize_re1) + (j101_re1)]
                j101_re1 = (j101_re1) + (S32(1))
            # Vectorizable loop 61 
            # Compute code 
            var i_re190 = S32(0)
            comptime dtype355 = f64
            comptime width355 = S32(simd_width_of[dtype355]())
            while i_re190 <= vsize_re1 - width355:
                var values = (dsp.const227) * ((((dsp.const230) * (simd_load(rec50, i_re190))) + ((dsp.const231) * (simd_load(rec50, i_re190 - S32(1))))) + ((dsp.const230) * (simd_load(rec50, i_re190 - S32(2)))))
                simd_store(zec11, i_re190, values)
                i_re190 = i_re190 + S32(width355)
            # Recursive loop 62 
            # Pre code 
            var j102_re1 = S32(0)
            comptime dtype356 = f64
            comptime width356 = S32(simd_width_of[dtype356]())
            while j102_re1 <= S32(4) - width356:
                var values = simd_load(dsp.rec49_perm, j102_re1)
                simd_store(rec49_tmp, j102_re1, values)
                j102_re1 = j102_re1 + S32(width356)
            # Compute code 
            var i_re191 = S32(0)
            while (i_re191) < (vsize_re1): 
                rec49[i_re191] = (zec11[i_re191]) - ((dsp.const234) * (((dsp.const235) * (rec49[(i_re191) - (S32(2))])) + ((dsp.const238) * (rec49[(i_re191) - (S32(1))]))))
                i_re191 = (i_re191) + (S32(1))
            # Post code 
            var j103_re1 = S32(0)
            while (j103_re1) < (S32(4)): 
                dsp.rec49_perm[j103_re1] = rec49_tmp[(vsize_re1) + (j103_re1)]
                j103_re1 = (j103_re1) + (S32(1))
            # Recursive loop 63 
            # Pre code 
            var j104_re1 = S32(0)
            comptime dtype358 = f64
            comptime width358 = S32(simd_width_of[dtype358]())
            while j104_re1 <= S32(4) - width358:
                var values = simd_load(dsp.rec48_perm, j104_re1)
                simd_store(rec48_tmp, j104_re1, values)
                j104_re1 = j104_re1 + S32(width358)
            # Compute code 
            var i_re192 = S32(0)
            while (i_re192) < (vsize_re1): 
                rec48[i_re192] = ((dsp.const234) * ((((dsp.const240) * (rec49[i_re192])) + ((dsp.const241) * (rec49[(i_re192) - (S32(1))]))) + ((dsp.const240) * (rec49[(i_re192) - (S32(2))])))) - ((dsp.const242) * (((dsp.const243) * (rec48[(i_re192) - (S32(2))])) + ((dsp.const244) * (rec48[(i_re192) - (S32(1))]))))
                i_re192 = (i_re192) + (S32(1))
            # Post code 
            var j105_re1 = S32(0)
            while (j105_re1) < (S32(4)): 
                dsp.rec48_perm[j105_re1] = rec48_tmp[(vsize_re1) + (j105_re1)]
                j105_re1 = (j105_re1) + (S32(1))
            # Recursive loop 64 
            # Pre code 
            var j106_re1 = S32(0)
            comptime dtype360 = f64
            comptime width360 = S32(simd_width_of[dtype360]())
            while j106_re1 <= S32(4) - width360:
                var values = simd_load(dsp.rec47_perm, j106_re1)
                simd_store(rec47_tmp, j106_re1, values)
                j106_re1 = j106_re1 + S32(width360)
            # Compute code 
            var i_re193 = S32(0)
            while (i_re193) < (vsize_re1): 
                rec47[i_re193] = ((dsp.const242) * ((((dsp.const246) * (rec48[i_re193])) + ((dsp.const247) * (rec48[(i_re193) - (S32(1))]))) + ((dsp.const246) * (rec48[(i_re193) - (S32(2))])))) - ((dsp.const248) * (((dsp.const249) * (rec47[(i_re193) - (S32(2))])) + ((dsp.const250) * (rec47[(i_re193) - (S32(1))]))))
                i_re193 = (i_re193) + (S32(1))
            # Post code 
            var j107_re1 = S32(0)
            while (j107_re1) < (S32(4)): 
                dsp.rec47_perm[j107_re1] = rec47_tmp[(vsize_re1) + (j107_re1)]
                j107_re1 = (j107_re1) + (S32(1))
            # Recursive loop 65 
            # Pre code 
            var j108_re1 = S32(0)
            comptime dtype362 = f64
            comptime width362 = S32(simd_width_of[dtype362]())
            while j108_re1 <= S32(4) - width362:
                var values = simd_load(dsp.rec46_perm, j108_re1)
                simd_store(rec46_tmp, j108_re1, values)
                j108_re1 = j108_re1 + S32(width362)
            # Compute code 
            var i_re194 = S32(0)
            while (i_re194) < (vsize_re1): 
                rec46[i_re194] = ((slow8) * (rec46[(i_re194) - (S32(1))])) + ((slow9) * (abs((dsp.const248) * ((((dsp.const252) * (rec47[i_re194])) + ((dsp.const253) * (rec47[(i_re194) - (S32(1))]))) + ((dsp.const252) * (rec47[(i_re194) - (S32(2))]))))))
                i_re194 = (i_re194) + (S32(1))
            # Post code 
            var j109_re1 = S32(0)
            while (j109_re1) < (S32(4)): 
                dsp.rec46_perm[j109_re1] = rec46_tmp[(vsize_re1) + (j109_re1)]
                j109_re1 = (j109_re1) + (S32(1))
            # Recursive loop 66 
            # Pre code 
            var j110_re1 = S32(0)
            comptime dtype364 = f64
            comptime width364 = S32(simd_width_of[dtype364]())
            while j110_re1 <= S32(4) - width364:
                var values = simd_load(dsp.rec59_perm, j110_re1)
                simd_store(rec59_tmp, j110_re1, values)
                j110_re1 = j110_re1 + S32(width364)
            # Compute code 
            var i_re195 = S32(0)
            while (i_re195) < (vsize_re1): 
                rec59[i_re195] = (zec11[i_re195]) - ((dsp.const254) * (((dsp.const255) * (rec59[(i_re195) - (S32(2))])) + ((dsp.const256) * (rec59[(i_re195) - (S32(1))]))))
                i_re195 = (i_re195) + (S32(1))
            # Post code 
            var j111_re1 = S32(0)
            while (j111_re1) < (S32(4)): 
                dsp.rec59_perm[j111_re1] = rec59_tmp[(vsize_re1) + (j111_re1)]
                j111_re1 = (j111_re1) + (S32(1))
            # Recursive loop 67 
            # Pre code 
            var j112_re1 = S32(0)
            comptime dtype366 = f64
            comptime width366 = S32(simd_width_of[dtype366]())
            while j112_re1 <= S32(4) - width366:
                var values = simd_load(dsp.rec58_perm, j112_re1)
                simd_store(rec58_tmp, j112_re1, values)
                j112_re1 = j112_re1 + S32(width366)
            # Compute code 
            var i_re196 = S32(0)
            while (i_re196) < (vsize_re1): 
                rec58[i_re196] = ((dsp.const254) * ((((dsp.const258) * (rec59[i_re196])) + ((dsp.const259) * (rec59[(i_re196) - (S32(1))]))) + ((dsp.const258) * (rec59[(i_re196) - (S32(2))])))) - ((dsp.const260) * (((dsp.const261) * (rec58[(i_re196) - (S32(2))])) + ((dsp.const262) * (rec58[(i_re196) - (S32(1))]))))
                i_re196 = (i_re196) + (S32(1))
            # Post code 
            var j113_re1 = S32(0)
            while (j113_re1) < (S32(4)): 
                dsp.rec58_perm[j113_re1] = rec58_tmp[(vsize_re1) + (j113_re1)]
                j113_re1 = (j113_re1) + (S32(1))
            # Recursive loop 68 
            # Pre code 
            var j114_re1 = S32(0)
            comptime dtype368 = f64
            comptime width368 = S32(simd_width_of[dtype368]())
            while j114_re1 <= S32(4) - width368:
                var values = simd_load(dsp.rec57_perm, j114_re1)
                simd_store(rec57_tmp, j114_re1, values)
                j114_re1 = j114_re1 + S32(width368)
            # Compute code 
            var i_re197 = S32(0)
            while (i_re197) < (vsize_re1): 
                rec57[i_re197] = ((dsp.const260) * ((((dsp.const263) * (rec58[i_re197])) + ((dsp.const264) * (rec58[(i_re197) - (S32(1))]))) + ((dsp.const263) * (rec58[(i_re197) - (S32(2))])))) - ((dsp.const265) * (((dsp.const266) * (rec57[(i_re197) - (S32(2))])) + ((dsp.const267) * (rec57[(i_re197) - (S32(1))]))))
                i_re197 = (i_re197) + (S32(1))
            # Post code 
            var j115_re1 = S32(0)
            while (j115_re1) < (S32(4)): 
                dsp.rec57_perm[j115_re1] = rec57_tmp[(vsize_re1) + (j115_re1)]
                j115_re1 = (j115_re1) + (S32(1))
            # Vectorizable loop 69 
            # Compute code 
            var i_re198 = S32(0)
            comptime dtype370 = f64
            comptime width370 = S32(simd_width_of[dtype370]())
            while i_re198 <= vsize_re1 - width370:
                var values = (dsp.const265) * ((((dsp.const268) * (simd_load(rec57, i_re198))) + ((dsp.const269) * (simd_load(rec57, i_re198 - S32(1))))) + ((dsp.const268) * (simd_load(rec57, i_re198 - S32(2)))))
                simd_store(zec12, i_re198, values)
                i_re198 = i_re198 + S32(width370)
            # Recursive loop 70 
            # Pre code 
            var j116_re1 = S32(0)
            comptime dtype371 = f64
            comptime width371 = S32(simd_width_of[dtype371]())
            while j116_re1 <= S32(4) - width371:
                var values = simd_load(dsp.rec56_perm, j116_re1)
                simd_store(rec56_tmp, j116_re1, values)
                j116_re1 = j116_re1 + S32(width371)
            # Compute code 
            var i_re199 = S32(0)
            while (i_re199) < (vsize_re1): 
                rec56[i_re199] = (zec12[i_re199]) - ((dsp.const272) * (((dsp.const273) * (rec56[(i_re199) - (S32(2))])) + ((dsp.const276) * (rec56[(i_re199) - (S32(1))]))))
                i_re199 = (i_re199) + (S32(1))
            # Post code 
            var j117_re1 = S32(0)
            while (j117_re1) < (S32(4)): 
                dsp.rec56_perm[j117_re1] = rec56_tmp[(vsize_re1) + (j117_re1)]
                j117_re1 = (j117_re1) + (S32(1))
            # Recursive loop 71 
            # Pre code 
            var j118_re1 = S32(0)
            comptime dtype373 = f64
            comptime width373 = S32(simd_width_of[dtype373]())
            while j118_re1 <= S32(4) - width373:
                var values = simd_load(dsp.rec55_perm, j118_re1)
                simd_store(rec55_tmp, j118_re1, values)
                j118_re1 = j118_re1 + S32(width373)
            # Compute code 
            var i_re200 = S32(0)
            while (i_re200) < (vsize_re1): 
                rec55[i_re200] = ((dsp.const272) * ((((dsp.const278) * (rec56[i_re200])) + ((dsp.const279) * (rec56[(i_re200) - (S32(1))]))) + ((dsp.const278) * (rec56[(i_re200) - (S32(2))])))) - ((dsp.const280) * (((dsp.const281) * (rec55[(i_re200) - (S32(2))])) + ((dsp.const282) * (rec55[(i_re200) - (S32(1))]))))
                i_re200 = (i_re200) + (S32(1))
            # Post code 
            var j119_re1 = S32(0)
            while (j119_re1) < (S32(4)): 
                dsp.rec55_perm[j119_re1] = rec55_tmp[(vsize_re1) + (j119_re1)]
                j119_re1 = (j119_re1) + (S32(1))
            # Recursive loop 72 
            # Pre code 
            var j120_re1 = S32(0)
            comptime dtype375 = f64
            comptime width375 = S32(simd_width_of[dtype375]())
            while j120_re1 <= S32(4) - width375:
                var values = simd_load(dsp.rec54_perm, j120_re1)
                simd_store(rec54_tmp, j120_re1, values)
                j120_re1 = j120_re1 + S32(width375)
            # Compute code 
            var i_re201 = S32(0)
            while (i_re201) < (vsize_re1): 
                rec54[i_re201] = ((dsp.const280) * ((((dsp.const284) * (rec55[i_re201])) + ((dsp.const285) * (rec55[(i_re201) - (S32(1))]))) + ((dsp.const284) * (rec55[(i_re201) - (S32(2))])))) - ((dsp.const286) * (((dsp.const287) * (rec54[(i_re201) - (S32(2))])) + ((dsp.const288) * (rec54[(i_re201) - (S32(1))]))))
                i_re201 = (i_re201) + (S32(1))
            # Post code 
            var j121_re1 = S32(0)
            while (j121_re1) < (S32(4)): 
                dsp.rec54_perm[j121_re1] = rec54_tmp[(vsize_re1) + (j121_re1)]
                j121_re1 = (j121_re1) + (S32(1))
            # Recursive loop 73 
            # Pre code 
            var j122_re1 = S32(0)
            comptime dtype377 = f64
            comptime width377 = S32(simd_width_of[dtype377]())
            while j122_re1 <= S32(4) - width377:
                var values = simd_load(dsp.rec53_perm, j122_re1)
                simd_store(rec53_tmp, j122_re1, values)
                j122_re1 = j122_re1 + S32(width377)
            # Compute code 
            var i_re202 = S32(0)
            while (i_re202) < (vsize_re1): 
                rec53[i_re202] = ((slow8) * (rec53[(i_re202) - (S32(1))])) + ((slow9) * (abs((dsp.const286) * ((((dsp.const290) * (rec54[i_re202])) + ((dsp.const291) * (rec54[(i_re202) - (S32(1))]))) + ((dsp.const290) * (rec54[(i_re202) - (S32(2))]))))))
                i_re202 = (i_re202) + (S32(1))
            # Post code 
            var j123_re1 = S32(0)
            while (j123_re1) < (S32(4)): 
                dsp.rec53_perm[j123_re1] = rec53_tmp[(vsize_re1) + (j123_re1)]
                j123_re1 = (j123_re1) + (S32(1))
            # Recursive loop 74 
            # Pre code 
            var j124_re1 = S32(0)
            comptime dtype379 = f64
            comptime width379 = S32(simd_width_of[dtype379]())
            while j124_re1 <= S32(4) - width379:
                var values = simd_load(dsp.rec66_perm, j124_re1)
                simd_store(rec66_tmp, j124_re1, values)
                j124_re1 = j124_re1 + S32(width379)
            # Compute code 
            var i_re203 = S32(0)
            while (i_re203) < (vsize_re1): 
                rec66[i_re203] = (zec12[i_re203]) - ((dsp.const292) * (((dsp.const293) * (rec66[(i_re203) - (S32(2))])) + ((dsp.const294) * (rec66[(i_re203) - (S32(1))]))))
                i_re203 = (i_re203) + (S32(1))
            # Post code 
            var j125_re1 = S32(0)
            while (j125_re1) < (S32(4)): 
                dsp.rec66_perm[j125_re1] = rec66_tmp[(vsize_re1) + (j125_re1)]
                j125_re1 = (j125_re1) + (S32(1))
            # Recursive loop 75 
            # Pre code 
            var j126_re1 = S32(0)
            comptime dtype381 = f64
            comptime width381 = S32(simd_width_of[dtype381]())
            while j126_re1 <= S32(4) - width381:
                var values = simd_load(dsp.rec65_perm, j126_re1)
                simd_store(rec65_tmp, j126_re1, values)
                j126_re1 = j126_re1 + S32(width381)
            # Compute code 
            var i_re204 = S32(0)
            while (i_re204) < (vsize_re1): 
                rec65[i_re204] = ((dsp.const292) * ((((dsp.const296) * (rec66[i_re204])) + ((dsp.const297) * (rec66[(i_re204) - (S32(1))]))) + ((dsp.const296) * (rec66[(i_re204) - (S32(2))])))) - ((dsp.const298) * (((dsp.const299) * (rec65[(i_re204) - (S32(2))])) + ((dsp.const300) * (rec65[(i_re204) - (S32(1))]))))
                i_re204 = (i_re204) + (S32(1))
            # Post code 
            var j127_re1 = S32(0)
            while (j127_re1) < (S32(4)): 
                dsp.rec65_perm[j127_re1] = rec65_tmp[(vsize_re1) + (j127_re1)]
                j127_re1 = (j127_re1) + (S32(1))
            # Recursive loop 76 
            # Pre code 
            var j128_re1 = S32(0)
            comptime dtype383 = f64
            comptime width383 = S32(simd_width_of[dtype383]())
            while j128_re1 <= S32(4) - width383:
                var values = simd_load(dsp.rec64_perm, j128_re1)
                simd_store(rec64_tmp, j128_re1, values)
                j128_re1 = j128_re1 + S32(width383)
            # Compute code 
            var i_re205 = S32(0)
            while (i_re205) < (vsize_re1): 
                rec64[i_re205] = ((dsp.const298) * ((((dsp.const301) * (rec65[i_re205])) + ((dsp.const302) * (rec65[(i_re205) - (S32(1))]))) + ((dsp.const301) * (rec65[(i_re205) - (S32(2))])))) - ((dsp.const303) * (((dsp.const304) * (rec64[(i_re205) - (S32(2))])) + ((dsp.const305) * (rec64[(i_re205) - (S32(1))]))))
                i_re205 = (i_re205) + (S32(1))
            # Post code 
            var j129_re1 = S32(0)
            while (j129_re1) < (S32(4)): 
                dsp.rec64_perm[j129_re1] = rec64_tmp[(vsize_re1) + (j129_re1)]
                j129_re1 = (j129_re1) + (S32(1))
            # Vectorizable loop 77 
            # Compute code 
            var i_re206 = S32(0)
            comptime dtype385 = f64
            comptime width385 = S32(simd_width_of[dtype385]())
            while i_re206 <= vsize_re1 - width385:
                var values = (dsp.const303) * ((((dsp.const306) * (simd_load(rec64, i_re206))) + ((dsp.const307) * (simd_load(rec64, i_re206 - S32(1))))) + ((dsp.const306) * (simd_load(rec64, i_re206 - S32(2)))))
                simd_store(zec13, i_re206, values)
                i_re206 = i_re206 + S32(width385)
            # Recursive loop 78 
            # Pre code 
            var j130_re1 = S32(0)
            comptime dtype386 = f64
            comptime width386 = S32(simd_width_of[dtype386]())
            while j130_re1 <= S32(4) - width386:
                var values = simd_load(dsp.rec63_perm, j130_re1)
                simd_store(rec63_tmp, j130_re1, values)
                j130_re1 = j130_re1 + S32(width386)
            # Compute code 
            var i_re207 = S32(0)
            while (i_re207) < (vsize_re1): 
                rec63[i_re207] = (zec13[i_re207]) - ((dsp.const310) * (((dsp.const311) * (rec63[(i_re207) - (S32(2))])) + ((dsp.const314) * (rec63[(i_re207) - (S32(1))]))))
                i_re207 = (i_re207) + (S32(1))
            # Post code 
            var j131_re1 = S32(0)
            while (j131_re1) < (S32(4)): 
                dsp.rec63_perm[j131_re1] = rec63_tmp[(vsize_re1) + (j131_re1)]
                j131_re1 = (j131_re1) + (S32(1))
            # Recursive loop 79 
            # Pre code 
            var j132_re1 = S32(0)
            comptime dtype388 = f64
            comptime width388 = S32(simd_width_of[dtype388]())
            while j132_re1 <= S32(4) - width388:
                var values = simd_load(dsp.rec62_perm, j132_re1)
                simd_store(rec62_tmp, j132_re1, values)
                j132_re1 = j132_re1 + S32(width388)
            # Compute code 
            var i_re208 = S32(0)
            while (i_re208) < (vsize_re1): 
                rec62[i_re208] = ((dsp.const310) * ((((dsp.const316) * (rec63[i_re208])) + ((dsp.const317) * (rec63[(i_re208) - (S32(1))]))) + ((dsp.const316) * (rec63[(i_re208) - (S32(2))])))) - ((dsp.const318) * (((dsp.const319) * (rec62[(i_re208) - (S32(2))])) + ((dsp.const320) * (rec62[(i_re208) - (S32(1))]))))
                i_re208 = (i_re208) + (S32(1))
            # Post code 
            var j133_re1 = S32(0)
            while (j133_re1) < (S32(4)): 
                dsp.rec62_perm[j133_re1] = rec62_tmp[(vsize_re1) + (j133_re1)]
                j133_re1 = (j133_re1) + (S32(1))
            # Recursive loop 80 
            # Pre code 
            var j134_re1 = S32(0)
            comptime dtype390 = f64
            comptime width390 = S32(simd_width_of[dtype390]())
            while j134_re1 <= S32(4) - width390:
                var values = simd_load(dsp.rec61_perm, j134_re1)
                simd_store(rec61_tmp, j134_re1, values)
                j134_re1 = j134_re1 + S32(width390)
            # Compute code 
            var i_re209 = S32(0)
            while (i_re209) < (vsize_re1): 
                rec61[i_re209] = ((dsp.const318) * ((((dsp.const322) * (rec62[i_re209])) + ((dsp.const323) * (rec62[(i_re209) - (S32(1))]))) + ((dsp.const322) * (rec62[(i_re209) - (S32(2))])))) - ((dsp.const324) * (((dsp.const325) * (rec61[(i_re209) - (S32(2))])) + ((dsp.const326) * (rec61[(i_re209) - (S32(1))]))))
                i_re209 = (i_re209) + (S32(1))
            # Post code 
            var j135_re1 = S32(0)
            while (j135_re1) < (S32(4)): 
                dsp.rec61_perm[j135_re1] = rec61_tmp[(vsize_re1) + (j135_re1)]
                j135_re1 = (j135_re1) + (S32(1))
            # Recursive loop 81 
            # Pre code 
            var j136_re1 = S32(0)
            comptime dtype392 = f64
            comptime width392 = S32(simd_width_of[dtype392]())
            while j136_re1 <= S32(4) - width392:
                var values = simd_load(dsp.rec60_perm, j136_re1)
                simd_store(rec60_tmp, j136_re1, values)
                j136_re1 = j136_re1 + S32(width392)
            # Compute code 
            var i_re210 = S32(0)
            while (i_re210) < (vsize_re1): 
                rec60[i_re210] = ((slow8) * (rec60[(i_re210) - (S32(1))])) + ((slow9) * (abs((dsp.const324) * ((((dsp.const328) * (rec61[i_re210])) + ((dsp.const329) * (rec61[(i_re210) - (S32(1))]))) + ((dsp.const328) * (rec61[(i_re210) - (S32(2))]))))))
                i_re210 = (i_re210) + (S32(1))
            # Post code 
            var j137_re1 = S32(0)
            while (j137_re1) < (S32(4)): 
                dsp.rec60_perm[j137_re1] = rec60_tmp[(vsize_re1) + (j137_re1)]
                j137_re1 = (j137_re1) + (S32(1))
            # Recursive loop 82 
            # Pre code 
            var j138_re1 = S32(0)
            comptime dtype394 = f64
            comptime width394 = S32(simd_width_of[dtype394]())
            while j138_re1 <= S32(4) - width394:
                var values = simd_load(dsp.rec73_perm, j138_re1)
                simd_store(rec73_tmp, j138_re1, values)
                j138_re1 = j138_re1 + S32(width394)
            # Compute code 
            var i_re211 = S32(0)
            while (i_re211) < (vsize_re1): 
                rec73[i_re211] = (zec13[i_re211]) - ((dsp.const330) * (((dsp.const331) * (rec73[(i_re211) - (S32(2))])) + ((dsp.const332) * (rec73[(i_re211) - (S32(1))]))))
                i_re211 = (i_re211) + (S32(1))
            # Post code 
            var j139_re1 = S32(0)
            while (j139_re1) < (S32(4)): 
                dsp.rec73_perm[j139_re1] = rec73_tmp[(vsize_re1) + (j139_re1)]
                j139_re1 = (j139_re1) + (S32(1))
            # Recursive loop 83 
            # Pre code 
            var j140_re1 = S32(0)
            comptime dtype396 = f64
            comptime width396 = S32(simd_width_of[dtype396]())
            while j140_re1 <= S32(4) - width396:
                var values = simd_load(dsp.rec72_perm, j140_re1)
                simd_store(rec72_tmp, j140_re1, values)
                j140_re1 = j140_re1 + S32(width396)
            # Compute code 
            var i_re212 = S32(0)
            while (i_re212) < (vsize_re1): 
                rec72[i_re212] = ((dsp.const330) * ((((dsp.const334) * (rec73[i_re212])) + ((dsp.const335) * (rec73[(i_re212) - (S32(1))]))) + ((dsp.const334) * (rec73[(i_re212) - (S32(2))])))) - ((dsp.const336) * (((dsp.const337) * (rec72[(i_re212) - (S32(2))])) + ((dsp.const338) * (rec72[(i_re212) - (S32(1))]))))
                i_re212 = (i_re212) + (S32(1))
            # Post code 
            var j141_re1 = S32(0)
            while (j141_re1) < (S32(4)): 
                dsp.rec72_perm[j141_re1] = rec72_tmp[(vsize_re1) + (j141_re1)]
                j141_re1 = (j141_re1) + (S32(1))
            # Recursive loop 84 
            # Pre code 
            var j142_re1 = S32(0)
            comptime dtype398 = f64
            comptime width398 = S32(simd_width_of[dtype398]())
            while j142_re1 <= S32(4) - width398:
                var values = simd_load(dsp.rec71_perm, j142_re1)
                simd_store(rec71_tmp, j142_re1, values)
                j142_re1 = j142_re1 + S32(width398)
            # Compute code 
            var i_re213 = S32(0)
            while (i_re213) < (vsize_re1): 
                rec71[i_re213] = ((dsp.const336) * ((((dsp.const339) * (rec72[i_re213])) + ((dsp.const340) * (rec72[(i_re213) - (S32(1))]))) + ((dsp.const339) * (rec72[(i_re213) - (S32(2))])))) - ((dsp.const341) * (((dsp.const342) * (rec71[(i_re213) - (S32(2))])) + ((dsp.const343) * (rec71[(i_re213) - (S32(1))]))))
                i_re213 = (i_re213) + (S32(1))
            # Post code 
            var j143_re1 = S32(0)
            while (j143_re1) < (S32(4)): 
                dsp.rec71_perm[j143_re1] = rec71_tmp[(vsize_re1) + (j143_re1)]
                j143_re1 = (j143_re1) + (S32(1))
            # Vectorizable loop 85 
            # Compute code 
            var i_re214 = S32(0)
            comptime dtype400 = f64
            comptime width400 = S32(simd_width_of[dtype400]())
            while i_re214 <= vsize_re1 - width400:
                var values = (dsp.const341) * ((((dsp.const344) * (simd_load(rec71, i_re214))) + ((dsp.const345) * (simd_load(rec71, i_re214 - S32(1))))) + ((dsp.const344) * (simd_load(rec71, i_re214 - S32(2)))))
                simd_store(zec14, i_re214, values)
                i_re214 = i_re214 + S32(width400)
            # Recursive loop 86 
            # Pre code 
            var j144_re1 = S32(0)
            comptime dtype401 = f64
            comptime width401 = S32(simd_width_of[dtype401]())
            while j144_re1 <= S32(4) - width401:
                var values = simd_load(dsp.rec70_perm, j144_re1)
                simd_store(rec70_tmp, j144_re1, values)
                j144_re1 = j144_re1 + S32(width401)
            # Compute code 
            var i_re215 = S32(0)
            while (i_re215) < (vsize_re1): 
                rec70[i_re215] = (zec14[i_re215]) - ((dsp.const348) * (((dsp.const349) * (rec70[(i_re215) - (S32(2))])) + ((dsp.const352) * (rec70[(i_re215) - (S32(1))]))))
                i_re215 = (i_re215) + (S32(1))
            # Post code 
            var j145_re1 = S32(0)
            while (j145_re1) < (S32(4)): 
                dsp.rec70_perm[j145_re1] = rec70_tmp[(vsize_re1) + (j145_re1)]
                j145_re1 = (j145_re1) + (S32(1))
            # Recursive loop 87 
            # Pre code 
            var j146_re1 = S32(0)
            comptime dtype403 = f64
            comptime width403 = S32(simd_width_of[dtype403]())
            while j146_re1 <= S32(4) - width403:
                var values = simd_load(dsp.rec69_perm, j146_re1)
                simd_store(rec69_tmp, j146_re1, values)
                j146_re1 = j146_re1 + S32(width403)
            # Compute code 
            var i_re216 = S32(0)
            while (i_re216) < (vsize_re1): 
                rec69[i_re216] = ((dsp.const348) * ((((dsp.const354) * (rec70[i_re216])) + ((dsp.const355) * (rec70[(i_re216) - (S32(1))]))) + ((dsp.const354) * (rec70[(i_re216) - (S32(2))])))) - ((dsp.const356) * (((dsp.const357) * (rec69[(i_re216) - (S32(2))])) + ((dsp.const358) * (rec69[(i_re216) - (S32(1))]))))
                i_re216 = (i_re216) + (S32(1))
            # Post code 
            var j147_re1 = S32(0)
            while (j147_re1) < (S32(4)): 
                dsp.rec69_perm[j147_re1] = rec69_tmp[(vsize_re1) + (j147_re1)]
                j147_re1 = (j147_re1) + (S32(1))
            # Recursive loop 88 
            # Pre code 
            var j148_re1 = S32(0)
            comptime dtype405 = f64
            comptime width405 = S32(simd_width_of[dtype405]())
            while j148_re1 <= S32(4) - width405:
                var values = simd_load(dsp.rec68_perm, j148_re1)
                simd_store(rec68_tmp, j148_re1, values)
                j148_re1 = j148_re1 + S32(width405)
            # Compute code 
            var i_re217 = S32(0)
            while (i_re217) < (vsize_re1): 
                rec68[i_re217] = ((dsp.const356) * ((((dsp.const360) * (rec69[i_re217])) + ((dsp.const361) * (rec69[(i_re217) - (S32(1))]))) + ((dsp.const360) * (rec69[(i_re217) - (S32(2))])))) - ((dsp.const362) * (((dsp.const363) * (rec68[(i_re217) - (S32(2))])) + ((dsp.const364) * (rec68[(i_re217) - (S32(1))]))))
                i_re217 = (i_re217) + (S32(1))
            # Post code 
            var j149_re1 = S32(0)
            while (j149_re1) < (S32(4)): 
                dsp.rec68_perm[j149_re1] = rec68_tmp[(vsize_re1) + (j149_re1)]
                j149_re1 = (j149_re1) + (S32(1))
            # Recursive loop 89 
            # Pre code 
            var j150_re1 = S32(0)
            comptime dtype407 = f64
            comptime width407 = S32(simd_width_of[dtype407]())
            while j150_re1 <= S32(4) - width407:
                var values = simd_load(dsp.rec67_perm, j150_re1)
                simd_store(rec67_tmp, j150_re1, values)
                j150_re1 = j150_re1 + S32(width407)
            # Compute code 
            var i_re218 = S32(0)
            while (i_re218) < (vsize_re1): 
                rec67[i_re218] = ((slow8) * (rec67[(i_re218) - (S32(1))])) + ((slow9) * (abs((dsp.const362) * ((((dsp.const366) * (rec68[i_re218])) + ((dsp.const367) * (rec68[(i_re218) - (S32(1))]))) + ((dsp.const366) * (rec68[(i_re218) - (S32(2))]))))))
                i_re218 = (i_re218) + (S32(1))
            # Post code 
            var j151_re1 = S32(0)
            while (j151_re1) < (S32(4)): 
                dsp.rec67_perm[j151_re1] = rec67_tmp[(vsize_re1) + (j151_re1)]
                j151_re1 = (j151_re1) + (S32(1))
            # Recursive loop 90 
            # Pre code 
            var j152_re1 = S32(0)
            comptime dtype409 = f64
            comptime width409 = S32(simd_width_of[dtype409]())
            while j152_re1 <= S32(4) - width409:
                var values = simd_load(dsp.rec80_perm, j152_re1)
                simd_store(rec80_tmp, j152_re1, values)
                j152_re1 = j152_re1 + S32(width409)
            # Compute code 
            var i_re219 = S32(0)
            while (i_re219) < (vsize_re1): 
                rec80[i_re219] = (zec14[i_re219]) - ((dsp.const368) * (((dsp.const369) * (rec80[(i_re219) - (S32(2))])) + ((dsp.const370) * (rec80[(i_re219) - (S32(1))]))))
                i_re219 = (i_re219) + (S32(1))
            # Post code 
            var j153_re1 = S32(0)
            while (j153_re1) < (S32(4)): 
                dsp.rec80_perm[j153_re1] = rec80_tmp[(vsize_re1) + (j153_re1)]
                j153_re1 = (j153_re1) + (S32(1))
            # Recursive loop 91 
            # Pre code 
            var j154_re1 = S32(0)
            comptime dtype411 = f64
            comptime width411 = S32(simd_width_of[dtype411]())
            while j154_re1 <= S32(4) - width411:
                var values = simd_load(dsp.rec79_perm, j154_re1)
                simd_store(rec79_tmp, j154_re1, values)
                j154_re1 = j154_re1 + S32(width411)
            # Compute code 
            var i_re220 = S32(0)
            while (i_re220) < (vsize_re1): 
                rec79[i_re220] = ((dsp.const368) * ((((dsp.const372) * (rec80[i_re220])) + ((dsp.const373) * (rec80[(i_re220) - (S32(1))]))) + ((dsp.const372) * (rec80[(i_re220) - (S32(2))])))) - ((dsp.const374) * (((dsp.const375) * (rec79[(i_re220) - (S32(2))])) + ((dsp.const376) * (rec79[(i_re220) - (S32(1))]))))
                i_re220 = (i_re220) + (S32(1))
            # Post code 
            var j155_re1 = S32(0)
            while (j155_re1) < (S32(4)): 
                dsp.rec79_perm[j155_re1] = rec79_tmp[(vsize_re1) + (j155_re1)]
                j155_re1 = (j155_re1) + (S32(1))
            # Recursive loop 92 
            # Pre code 
            var j156_re1 = S32(0)
            comptime dtype413 = f64
            comptime width413 = S32(simd_width_of[dtype413]())
            while j156_re1 <= S32(4) - width413:
                var values = simd_load(dsp.rec78_perm, j156_re1)
                simd_store(rec78_tmp, j156_re1, values)
                j156_re1 = j156_re1 + S32(width413)
            # Compute code 
            var i_re221 = S32(0)
            while (i_re221) < (vsize_re1): 
                rec78[i_re221] = ((dsp.const374) * ((((dsp.const377) * (rec79[i_re221])) + ((dsp.const378) * (rec79[(i_re221) - (S32(1))]))) + ((dsp.const377) * (rec79[(i_re221) - (S32(2))])))) - ((dsp.const379) * (((dsp.const380) * (rec78[(i_re221) - (S32(2))])) + ((dsp.const381) * (rec78[(i_re221) - (S32(1))]))))
                i_re221 = (i_re221) + (S32(1))
            # Post code 
            var j157_re1 = S32(0)
            while (j157_re1) < (S32(4)): 
                dsp.rec78_perm[j157_re1] = rec78_tmp[(vsize_re1) + (j157_re1)]
                j157_re1 = (j157_re1) + (S32(1))
            # Vectorizable loop 93 
            # Compute code 
            var i_re222 = S32(0)
            comptime dtype415 = f64
            comptime width415 = S32(simd_width_of[dtype415]())
            while i_re222 <= vsize_re1 - width415:
                var values = (dsp.const379) * ((((dsp.const382) * (simd_load(rec78, i_re222))) + ((dsp.const383) * (simd_load(rec78, i_re222 - S32(1))))) + ((dsp.const382) * (simd_load(rec78, i_re222 - S32(2)))))
                simd_store(zec15, i_re222, values)
                i_re222 = i_re222 + S32(width415)
            # Recursive loop 94 
            # Pre code 
            var j158_re1 = S32(0)
            comptime dtype416 = f64
            comptime width416 = S32(simd_width_of[dtype416]())
            while j158_re1 <= S32(4) - width416:
                var values = simd_load(dsp.rec77_perm, j158_re1)
                simd_store(rec77_tmp, j158_re1, values)
                j158_re1 = j158_re1 + S32(width416)
            # Compute code 
            var i_re223 = S32(0)
            while (i_re223) < (vsize_re1): 
                rec77[i_re223] = (zec15[i_re223]) - ((dsp.const386) * (((dsp.const387) * (rec77[(i_re223) - (S32(2))])) + ((dsp.const390) * (rec77[(i_re223) - (S32(1))]))))
                i_re223 = (i_re223) + (S32(1))
            # Post code 
            var j159_re1 = S32(0)
            while (j159_re1) < (S32(4)): 
                dsp.rec77_perm[j159_re1] = rec77_tmp[(vsize_re1) + (j159_re1)]
                j159_re1 = (j159_re1) + (S32(1))
            # Recursive loop 95 
            # Pre code 
            var j160_re1 = S32(0)
            comptime dtype418 = f64
            comptime width418 = S32(simd_width_of[dtype418]())
            while j160_re1 <= S32(4) - width418:
                var values = simd_load(dsp.rec76_perm, j160_re1)
                simd_store(rec76_tmp, j160_re1, values)
                j160_re1 = j160_re1 + S32(width418)
            # Compute code 
            var i_re224 = S32(0)
            while (i_re224) < (vsize_re1): 
                rec76[i_re224] = ((dsp.const386) * ((((dsp.const392) * (rec77[i_re224])) + ((dsp.const393) * (rec77[(i_re224) - (S32(1))]))) + ((dsp.const392) * (rec77[(i_re224) - (S32(2))])))) - ((dsp.const394) * (((dsp.const395) * (rec76[(i_re224) - (S32(2))])) + ((dsp.const396) * (rec76[(i_re224) - (S32(1))]))))
                i_re224 = (i_re224) + (S32(1))
            # Post code 
            var j161_re1 = S32(0)
            while (j161_re1) < (S32(4)): 
                dsp.rec76_perm[j161_re1] = rec76_tmp[(vsize_re1) + (j161_re1)]
                j161_re1 = (j161_re1) + (S32(1))
            # Recursive loop 96 
            # Pre code 
            var j162_re1 = S32(0)
            comptime dtype420 = f64
            comptime width420 = S32(simd_width_of[dtype420]())
            while j162_re1 <= S32(4) - width420:
                var values = simd_load(dsp.rec75_perm, j162_re1)
                simd_store(rec75_tmp, j162_re1, values)
                j162_re1 = j162_re1 + S32(width420)
            # Compute code 
            var i_re225 = S32(0)
            while (i_re225) < (vsize_re1): 
                rec75[i_re225] = ((dsp.const394) * ((((dsp.const398) * (rec76[i_re225])) + ((dsp.const399) * (rec76[(i_re225) - (S32(1))]))) + ((dsp.const398) * (rec76[(i_re225) - (S32(2))])))) - ((dsp.const400) * (((dsp.const401) * (rec75[(i_re225) - (S32(2))])) + ((dsp.const402) * (rec75[(i_re225) - (S32(1))]))))
                i_re225 = (i_re225) + (S32(1))
            # Post code 
            var j163_re1 = S32(0)
            while (j163_re1) < (S32(4)): 
                dsp.rec75_perm[j163_re1] = rec75_tmp[(vsize_re1) + (j163_re1)]
                j163_re1 = (j163_re1) + (S32(1))
            # Recursive loop 97 
            # Pre code 
            var j164_re1 = S32(0)
            comptime dtype422 = f64
            comptime width422 = S32(simd_width_of[dtype422]())
            while j164_re1 <= S32(4) - width422:
                var values = simd_load(dsp.rec74_perm, j164_re1)
                simd_store(rec74_tmp, j164_re1, values)
                j164_re1 = j164_re1 + S32(width422)
            # Compute code 
            var i_re226 = S32(0)
            while (i_re226) < (vsize_re1): 
                rec74[i_re226] = ((slow8) * (rec74[(i_re226) - (S32(1))])) + ((slow9) * (abs((dsp.const400) * ((((dsp.const404) * (rec75[i_re226])) + ((dsp.const405) * (rec75[(i_re226) - (S32(1))]))) + ((dsp.const404) * (rec75[(i_re226) - (S32(2))]))))))
                i_re226 = (i_re226) + (S32(1))
            # Post code 
            var j165_re1 = S32(0)
            while (j165_re1) < (S32(4)): 
                dsp.rec74_perm[j165_re1] = rec74_tmp[(vsize_re1) + (j165_re1)]
                j165_re1 = (j165_re1) + (S32(1))
            # Recursive loop 98 
            # Pre code 
            var j166_re1 = S32(0)
            comptime dtype424 = f64
            comptime width424 = S32(simd_width_of[dtype424]())
            while j166_re1 <= S32(4) - width424:
                var values = simd_load(dsp.rec87_perm, j166_re1)
                simd_store(rec87_tmp, j166_re1, values)
                j166_re1 = j166_re1 + S32(width424)
            # Compute code 
            var i_re227 = S32(0)
            while (i_re227) < (vsize_re1): 
                rec87[i_re227] = (zec15[i_re227]) - ((dsp.const406) * (((dsp.const407) * (rec87[(i_re227) - (S32(2))])) + ((dsp.const408) * (rec87[(i_re227) - (S32(1))]))))
                i_re227 = (i_re227) + (S32(1))
            # Post code 
            var j167_re1 = S32(0)
            while (j167_re1) < (S32(4)): 
                dsp.rec87_perm[j167_re1] = rec87_tmp[(vsize_re1) + (j167_re1)]
                j167_re1 = (j167_re1) + (S32(1))
            # Recursive loop 99 
            # Pre code 
            var j168_re1 = S32(0)
            comptime dtype426 = f64
            comptime width426 = S32(simd_width_of[dtype426]())
            while j168_re1 <= S32(4) - width426:
                var values = simd_load(dsp.rec86_perm, j168_re1)
                simd_store(rec86_tmp, j168_re1, values)
                j168_re1 = j168_re1 + S32(width426)
            # Compute code 
            var i_re228 = S32(0)
            while (i_re228) < (vsize_re1): 
                rec86[i_re228] = ((dsp.const406) * ((((dsp.const410) * (rec87[i_re228])) + ((dsp.const411) * (rec87[(i_re228) - (S32(1))]))) + ((dsp.const410) * (rec87[(i_re228) - (S32(2))])))) - ((dsp.const412) * (((dsp.const413) * (rec86[(i_re228) - (S32(2))])) + ((dsp.const414) * (rec86[(i_re228) - (S32(1))]))))
                i_re228 = (i_re228) + (S32(1))
            # Post code 
            var j169_re1 = S32(0)
            while (j169_re1) < (S32(4)): 
                dsp.rec86_perm[j169_re1] = rec86_tmp[(vsize_re1) + (j169_re1)]
                j169_re1 = (j169_re1) + (S32(1))
            # Recursive loop 100 
            # Pre code 
            var j170_re1 = S32(0)
            comptime dtype428 = f64
            comptime width428 = S32(simd_width_of[dtype428]())
            while j170_re1 <= S32(4) - width428:
                var values = simd_load(dsp.rec85_perm, j170_re1)
                simd_store(rec85_tmp, j170_re1, values)
                j170_re1 = j170_re1 + S32(width428)
            # Compute code 
            var i_re229 = S32(0)
            while (i_re229) < (vsize_re1): 
                rec85[i_re229] = ((dsp.const412) * ((((dsp.const415) * (rec86[i_re229])) + ((dsp.const416) * (rec86[(i_re229) - (S32(1))]))) + ((dsp.const415) * (rec86[(i_re229) - (S32(2))])))) - ((dsp.const417) * (((dsp.const418) * (rec85[(i_re229) - (S32(2))])) + ((dsp.const419) * (rec85[(i_re229) - (S32(1))]))))
                i_re229 = (i_re229) + (S32(1))
            # Post code 
            var j171_re1 = S32(0)
            while (j171_re1) < (S32(4)): 
                dsp.rec85_perm[j171_re1] = rec85_tmp[(vsize_re1) + (j171_re1)]
                j171_re1 = (j171_re1) + (S32(1))
            # Vectorizable loop 101 
            # Compute code 
            var i_re230 = S32(0)
            comptime dtype430 = f64
            comptime width430 = S32(simd_width_of[dtype430]())
            while i_re230 <= vsize_re1 - width430:
                var values = (dsp.const417) * ((((dsp.const420) * (simd_load(rec85, i_re230))) + ((dsp.const421) * (simd_load(rec85, i_re230 - S32(1))))) + ((dsp.const420) * (simd_load(rec85, i_re230 - S32(2)))))
                simd_store(zec16, i_re230, values)
                i_re230 = i_re230 + S32(width430)
            # Recursive loop 102 
            # Pre code 
            var j172_re1 = S32(0)
            comptime dtype431 = f64
            comptime width431 = S32(simd_width_of[dtype431]())
            while j172_re1 <= S32(4) - width431:
                var values = simd_load(dsp.rec84_perm, j172_re1)
                simd_store(rec84_tmp, j172_re1, values)
                j172_re1 = j172_re1 + S32(width431)
            # Compute code 
            var i_re231 = S32(0)
            while (i_re231) < (vsize_re1): 
                rec84[i_re231] = (zec16[i_re231]) - ((dsp.const424) * (((dsp.const425) * (rec84[(i_re231) - (S32(2))])) + ((dsp.const428) * (rec84[(i_re231) - (S32(1))]))))
                i_re231 = (i_re231) + (S32(1))
            # Post code 
            var j173_re1 = S32(0)
            while (j173_re1) < (S32(4)): 
                dsp.rec84_perm[j173_re1] = rec84_tmp[(vsize_re1) + (j173_re1)]
                j173_re1 = (j173_re1) + (S32(1))
            # Recursive loop 103 
            # Pre code 
            var j174_re1 = S32(0)
            comptime dtype433 = f64
            comptime width433 = S32(simd_width_of[dtype433]())
            while j174_re1 <= S32(4) - width433:
                var values = simd_load(dsp.rec83_perm, j174_re1)
                simd_store(rec83_tmp, j174_re1, values)
                j174_re1 = j174_re1 + S32(width433)
            # Compute code 
            var i_re232 = S32(0)
            while (i_re232) < (vsize_re1): 
                rec83[i_re232] = ((dsp.const424) * ((((dsp.const430) * (rec84[i_re232])) + ((dsp.const431) * (rec84[(i_re232) - (S32(1))]))) + ((dsp.const430) * (rec84[(i_re232) - (S32(2))])))) - ((dsp.const432) * (((dsp.const433) * (rec83[(i_re232) - (S32(2))])) + ((dsp.const434) * (rec83[(i_re232) - (S32(1))]))))
                i_re232 = (i_re232) + (S32(1))
            # Post code 
            var j175_re1 = S32(0)
            while (j175_re1) < (S32(4)): 
                dsp.rec83_perm[j175_re1] = rec83_tmp[(vsize_re1) + (j175_re1)]
                j175_re1 = (j175_re1) + (S32(1))
            # Recursive loop 104 
            # Pre code 
            var j176_re1 = S32(0)
            comptime dtype435 = f64
            comptime width435 = S32(simd_width_of[dtype435]())
            while j176_re1 <= S32(4) - width435:
                var values = simd_load(dsp.rec82_perm, j176_re1)
                simd_store(rec82_tmp, j176_re1, values)
                j176_re1 = j176_re1 + S32(width435)
            # Compute code 
            var i_re233 = S32(0)
            while (i_re233) < (vsize_re1): 
                rec82[i_re233] = ((dsp.const432) * ((((dsp.const436) * (rec83[i_re233])) + ((dsp.const437) * (rec83[(i_re233) - (S32(1))]))) + ((dsp.const436) * (rec83[(i_re233) - (S32(2))])))) - ((dsp.const438) * (((dsp.const439) * (rec82[(i_re233) - (S32(2))])) + ((dsp.const440) * (rec82[(i_re233) - (S32(1))]))))
                i_re233 = (i_re233) + (S32(1))
            # Post code 
            var j177_re1 = S32(0)
            while (j177_re1) < (S32(4)): 
                dsp.rec82_perm[j177_re1] = rec82_tmp[(vsize_re1) + (j177_re1)]
                j177_re1 = (j177_re1) + (S32(1))
            # Recursive loop 105 
            # Pre code 
            var j178_re1 = S32(0)
            comptime dtype437 = f64
            comptime width437 = S32(simd_width_of[dtype437]())
            while j178_re1 <= S32(4) - width437:
                var values = simd_load(dsp.rec81_perm, j178_re1)
                simd_store(rec81_tmp, j178_re1, values)
                j178_re1 = j178_re1 + S32(width437)
            # Compute code 
            var i_re234 = S32(0)
            while (i_re234) < (vsize_re1): 
                rec81[i_re234] = ((slow8) * (rec81[(i_re234) - (S32(1))])) + ((slow9) * (abs((dsp.const438) * ((((dsp.const442) * (rec82[i_re234])) + ((dsp.const443) * (rec82[(i_re234) - (S32(1))]))) + ((dsp.const442) * (rec82[(i_re234) - (S32(2))]))))))
                i_re234 = (i_re234) + (S32(1))
            # Post code 
            var j179_re1 = S32(0)
            while (j179_re1) < (S32(4)): 
                dsp.rec81_perm[j179_re1] = rec81_tmp[(vsize_re1) + (j179_re1)]
                j179_re1 = (j179_re1) + (S32(1))
            # Recursive loop 106 
            # Pre code 
            var j180_re1 = S32(0)
            comptime dtype439 = f64
            comptime width439 = S32(simd_width_of[dtype439]())
            while j180_re1 <= S32(4) - width439:
                var values = simd_load(dsp.rec94_perm, j180_re1)
                simd_store(rec94_tmp, j180_re1, values)
                j180_re1 = j180_re1 + S32(width439)
            # Compute code 
            var i_re235 = S32(0)
            while (i_re235) < (vsize_re1): 
                rec94[i_re235] = (zec16[i_re235]) - ((dsp.const444) * (((dsp.const445) * (rec94[(i_re235) - (S32(2))])) + ((dsp.const446) * (rec94[(i_re235) - (S32(1))]))))
                i_re235 = (i_re235) + (S32(1))
            # Post code 
            var j181_re1 = S32(0)
            while (j181_re1) < (S32(4)): 
                dsp.rec94_perm[j181_re1] = rec94_tmp[(vsize_re1) + (j181_re1)]
                j181_re1 = (j181_re1) + (S32(1))
            # Recursive loop 107 
            # Pre code 
            var j182_re1 = S32(0)
            comptime dtype441 = f64
            comptime width441 = S32(simd_width_of[dtype441]())
            while j182_re1 <= S32(4) - width441:
                var values = simd_load(dsp.rec93_perm, j182_re1)
                simd_store(rec93_tmp, j182_re1, values)
                j182_re1 = j182_re1 + S32(width441)
            # Compute code 
            var i_re236 = S32(0)
            while (i_re236) < (vsize_re1): 
                rec93[i_re236] = ((dsp.const444) * ((((dsp.const448) * (rec94[i_re236])) + ((dsp.const449) * (rec94[(i_re236) - (S32(1))]))) + ((dsp.const448) * (rec94[(i_re236) - (S32(2))])))) - ((dsp.const450) * (((dsp.const451) * (rec93[(i_re236) - (S32(2))])) + ((dsp.const452) * (rec93[(i_re236) - (S32(1))]))))
                i_re236 = (i_re236) + (S32(1))
            # Post code 
            var j183_re1 = S32(0)
            while (j183_re1) < (S32(4)): 
                dsp.rec93_perm[j183_re1] = rec93_tmp[(vsize_re1) + (j183_re1)]
                j183_re1 = (j183_re1) + (S32(1))
            # Recursive loop 108 
            # Pre code 
            var j184_re1 = S32(0)
            comptime dtype443 = f64
            comptime width443 = S32(simd_width_of[dtype443]())
            while j184_re1 <= S32(4) - width443:
                var values = simd_load(dsp.rec92_perm, j184_re1)
                simd_store(rec92_tmp, j184_re1, values)
                j184_re1 = j184_re1 + S32(width443)
            # Compute code 
            var i_re237 = S32(0)
            while (i_re237) < (vsize_re1): 
                rec92[i_re237] = ((dsp.const450) * ((((dsp.const453) * (rec93[i_re237])) + ((dsp.const454) * (rec93[(i_re237) - (S32(1))]))) + ((dsp.const453) * (rec93[(i_re237) - (S32(2))])))) - ((dsp.const455) * (((dsp.const456) * (rec92[(i_re237) - (S32(2))])) + ((dsp.const457) * (rec92[(i_re237) - (S32(1))]))))
                i_re237 = (i_re237) + (S32(1))
            # Post code 
            var j185_re1 = S32(0)
            while (j185_re1) < (S32(4)): 
                dsp.rec92_perm[j185_re1] = rec92_tmp[(vsize_re1) + (j185_re1)]
                j185_re1 = (j185_re1) + (S32(1))
            # Vectorizable loop 109 
            # Compute code 
            var i_re238 = S32(0)
            comptime dtype445 = f64
            comptime width445 = S32(simd_width_of[dtype445]())
            while i_re238 <= vsize_re1 - width445:
                var values = (dsp.const455) * ((((dsp.const458) * (simd_load(rec92, i_re238))) + ((dsp.const459) * (simd_load(rec92, i_re238 - S32(1))))) + ((dsp.const458) * (simd_load(rec92, i_re238 - S32(2)))))
                simd_store(zec17, i_re238, values)
                i_re238 = i_re238 + S32(width445)
            # Recursive loop 110 
            # Pre code 
            var j186_re1 = S32(0)
            comptime dtype446 = f64
            comptime width446 = S32(simd_width_of[dtype446]())
            while j186_re1 <= S32(4) - width446:
                var values = simd_load(dsp.rec91_perm, j186_re1)
                simd_store(rec91_tmp, j186_re1, values)
                j186_re1 = j186_re1 + S32(width446)
            # Compute code 
            var i_re239 = S32(0)
            while (i_re239) < (vsize_re1): 
                rec91[i_re239] = (zec17[i_re239]) - ((dsp.const462) * (((dsp.const463) * (rec91[(i_re239) - (S32(2))])) + ((dsp.const466) * (rec91[(i_re239) - (S32(1))]))))
                i_re239 = (i_re239) + (S32(1))
            # Post code 
            var j187_re1 = S32(0)
            while (j187_re1) < (S32(4)): 
                dsp.rec91_perm[j187_re1] = rec91_tmp[(vsize_re1) + (j187_re1)]
                j187_re1 = (j187_re1) + (S32(1))
            # Recursive loop 111 
            # Pre code 
            var j188_re1 = S32(0)
            comptime dtype448 = f64
            comptime width448 = S32(simd_width_of[dtype448]())
            while j188_re1 <= S32(4) - width448:
                var values = simd_load(dsp.rec90_perm, j188_re1)
                simd_store(rec90_tmp, j188_re1, values)
                j188_re1 = j188_re1 + S32(width448)
            # Compute code 
            var i_re240 = S32(0)
            while (i_re240) < (vsize_re1): 
                rec90[i_re240] = ((dsp.const462) * ((((dsp.const468) * (rec91[i_re240])) + ((dsp.const469) * (rec91[(i_re240) - (S32(1))]))) + ((dsp.const468) * (rec91[(i_re240) - (S32(2))])))) - ((dsp.const470) * (((dsp.const471) * (rec90[(i_re240) - (S32(2))])) + ((dsp.const472) * (rec90[(i_re240) - (S32(1))]))))
                i_re240 = (i_re240) + (S32(1))
            # Post code 
            var j189_re1 = S32(0)
            while (j189_re1) < (S32(4)): 
                dsp.rec90_perm[j189_re1] = rec90_tmp[(vsize_re1) + (j189_re1)]
                j189_re1 = (j189_re1) + (S32(1))
            # Recursive loop 112 
            # Pre code 
            var j190_re1 = S32(0)
            comptime dtype450 = f64
            comptime width450 = S32(simd_width_of[dtype450]())
            while j190_re1 <= S32(4) - width450:
                var values = simd_load(dsp.rec89_perm, j190_re1)
                simd_store(rec89_tmp, j190_re1, values)
                j190_re1 = j190_re1 + S32(width450)
            # Compute code 
            var i_re241 = S32(0)
            while (i_re241) < (vsize_re1): 
                rec89[i_re241] = ((dsp.const470) * ((((dsp.const474) * (rec90[i_re241])) + ((dsp.const475) * (rec90[(i_re241) - (S32(1))]))) + ((dsp.const474) * (rec90[(i_re241) - (S32(2))])))) - ((dsp.const476) * (((dsp.const477) * (rec89[(i_re241) - (S32(2))])) + ((dsp.const478) * (rec89[(i_re241) - (S32(1))]))))
                i_re241 = (i_re241) + (S32(1))
            # Post code 
            var j191_re1 = S32(0)
            while (j191_re1) < (S32(4)): 
                dsp.rec89_perm[j191_re1] = rec89_tmp[(vsize_re1) + (j191_re1)]
                j191_re1 = (j191_re1) + (S32(1))
            # Recursive loop 113 
            # Pre code 
            var j192_re1 = S32(0)
            comptime dtype452 = f64
            comptime width452 = S32(simd_width_of[dtype452]())
            while j192_re1 <= S32(4) - width452:
                var values = simd_load(dsp.rec88_perm, j192_re1)
                simd_store(rec88_tmp, j192_re1, values)
                j192_re1 = j192_re1 + S32(width452)
            # Compute code 
            var i_re242 = S32(0)
            while (i_re242) < (vsize_re1): 
                rec88[i_re242] = ((slow8) * (rec88[(i_re242) - (S32(1))])) + ((slow9) * (abs((dsp.const476) * ((((dsp.const480) * (rec89[i_re242])) + ((dsp.const481) * (rec89[(i_re242) - (S32(1))]))) + ((dsp.const480) * (rec89[(i_re242) - (S32(2))]))))))
                i_re242 = (i_re242) + (S32(1))
            # Post code 
            var j193_re1 = S32(0)
            while (j193_re1) < (S32(4)): 
                dsp.rec88_perm[j193_re1] = rec88_tmp[(vsize_re1) + (j193_re1)]
                j193_re1 = (j193_re1) + (S32(1))
            # Recursive loop 114 
            # Pre code 
            var j194_re1 = S32(0)
            comptime dtype454 = f64
            comptime width454 = S32(simd_width_of[dtype454]())
            while j194_re1 <= S32(4) - width454:
                var values = simd_load(dsp.rec101_perm, j194_re1)
                simd_store(rec101_tmp, j194_re1, values)
                j194_re1 = j194_re1 + S32(width454)
            # Compute code 
            var i_re243 = S32(0)
            while (i_re243) < (vsize_re1): 
                rec101[i_re243] = (zec17[i_re243]) - ((dsp.const482) * (((dsp.const483) * (rec101[(i_re243) - (S32(2))])) + ((dsp.const484) * (rec101[(i_re243) - (S32(1))]))))
                i_re243 = (i_re243) + (S32(1))
            # Post code 
            var j195_re1 = S32(0)
            while (j195_re1) < (S32(4)): 
                dsp.rec101_perm[j195_re1] = rec101_tmp[(vsize_re1) + (j195_re1)]
                j195_re1 = (j195_re1) + (S32(1))
            # Recursive loop 115 
            # Pre code 
            var j196_re1 = S32(0)
            comptime dtype456 = f64
            comptime width456 = S32(simd_width_of[dtype456]())
            while j196_re1 <= S32(4) - width456:
                var values = simd_load(dsp.rec100_perm, j196_re1)
                simd_store(rec100_tmp, j196_re1, values)
                j196_re1 = j196_re1 + S32(width456)
            # Compute code 
            var i_re244 = S32(0)
            while (i_re244) < (vsize_re1): 
                rec100[i_re244] = ((dsp.const482) * ((((dsp.const486) * (rec101[i_re244])) + ((dsp.const487) * (rec101[(i_re244) - (S32(1))]))) + ((dsp.const486) * (rec101[(i_re244) - (S32(2))])))) - ((dsp.const488) * (((dsp.const489) * (rec100[(i_re244) - (S32(2))])) + ((dsp.const490) * (rec100[(i_re244) - (S32(1))]))))
                i_re244 = (i_re244) + (S32(1))
            # Post code 
            var j197_re1 = S32(0)
            while (j197_re1) < (S32(4)): 
                dsp.rec100_perm[j197_re1] = rec100_tmp[(vsize_re1) + (j197_re1)]
                j197_re1 = (j197_re1) + (S32(1))
            # Recursive loop 116 
            # Pre code 
            var j198_re1 = S32(0)
            comptime dtype458 = f64
            comptime width458 = S32(simd_width_of[dtype458]())
            while j198_re1 <= S32(4) - width458:
                var values = simd_load(dsp.rec99_perm, j198_re1)
                simd_store(rec99_tmp, j198_re1, values)
                j198_re1 = j198_re1 + S32(width458)
            # Compute code 
            var i_re245 = S32(0)
            while (i_re245) < (vsize_re1): 
                rec99[i_re245] = ((dsp.const488) * ((((dsp.const491) * (rec100[i_re245])) + ((dsp.const492) * (rec100[(i_re245) - (S32(1))]))) + ((dsp.const491) * (rec100[(i_re245) - (S32(2))])))) - ((dsp.const493) * (((dsp.const494) * (rec99[(i_re245) - (S32(2))])) + ((dsp.const495) * (rec99[(i_re245) - (S32(1))]))))
                i_re245 = (i_re245) + (S32(1))
            # Post code 
            var j199_re1 = S32(0)
            while (j199_re1) < (S32(4)): 
                dsp.rec99_perm[j199_re1] = rec99_tmp[(vsize_re1) + (j199_re1)]
                j199_re1 = (j199_re1) + (S32(1))
            # Vectorizable loop 117 
            # Compute code 
            var i_re246 = S32(0)
            comptime dtype460 = f64
            comptime width460 = S32(simd_width_of[dtype460]())
            while i_re246 <= vsize_re1 - width460:
                var values = (dsp.const493) * ((((dsp.const496) * (simd_load(rec99, i_re246))) + ((dsp.const497) * (simd_load(rec99, i_re246 - S32(1))))) + ((dsp.const496) * (simd_load(rec99, i_re246 - S32(2)))))
                simd_store(zec18, i_re246, values)
                i_re246 = i_re246 + S32(width460)
            # Recursive loop 118 
            # Pre code 
            var j200_re1 = S32(0)
            comptime dtype461 = f64
            comptime width461 = S32(simd_width_of[dtype461]())
            while j200_re1 <= S32(4) - width461:
                var values = simd_load(dsp.rec98_perm, j200_re1)
                simd_store(rec98_tmp, j200_re1, values)
                j200_re1 = j200_re1 + S32(width461)
            # Compute code 
            var i_re247 = S32(0)
            while (i_re247) < (vsize_re1): 
                rec98[i_re247] = (zec18[i_re247]) - ((dsp.const500) * (((dsp.const501) * (rec98[(i_re247) - (S32(2))])) + ((dsp.const504) * (rec98[(i_re247) - (S32(1))]))))
                i_re247 = (i_re247) + (S32(1))
            # Post code 
            var j201_re1 = S32(0)
            while (j201_re1) < (S32(4)): 
                dsp.rec98_perm[j201_re1] = rec98_tmp[(vsize_re1) + (j201_re1)]
                j201_re1 = (j201_re1) + (S32(1))
            # Recursive loop 119 
            # Pre code 
            var j202_re1 = S32(0)
            comptime dtype463 = f64
            comptime width463 = S32(simd_width_of[dtype463]())
            while j202_re1 <= S32(4) - width463:
                var values = simd_load(dsp.rec97_perm, j202_re1)
                simd_store(rec97_tmp, j202_re1, values)
                j202_re1 = j202_re1 + S32(width463)
            # Compute code 
            var i_re248 = S32(0)
            while (i_re248) < (vsize_re1): 
                rec97[i_re248] = ((dsp.const500) * ((((dsp.const506) * (rec98[i_re248])) + ((dsp.const507) * (rec98[(i_re248) - (S32(1))]))) + ((dsp.const506) * (rec98[(i_re248) - (S32(2))])))) - ((dsp.const508) * (((dsp.const509) * (rec97[(i_re248) - (S32(2))])) + ((dsp.const510) * (rec97[(i_re248) - (S32(1))]))))
                i_re248 = (i_re248) + (S32(1))
            # Post code 
            var j203_re1 = S32(0)
            while (j203_re1) < (S32(4)): 
                dsp.rec97_perm[j203_re1] = rec97_tmp[(vsize_re1) + (j203_re1)]
                j203_re1 = (j203_re1) + (S32(1))
            # Recursive loop 120 
            # Pre code 
            var j204_re1 = S32(0)
            comptime dtype465 = f64
            comptime width465 = S32(simd_width_of[dtype465]())
            while j204_re1 <= S32(4) - width465:
                var values = simd_load(dsp.rec96_perm, j204_re1)
                simd_store(rec96_tmp, j204_re1, values)
                j204_re1 = j204_re1 + S32(width465)
            # Compute code 
            var i_re249 = S32(0)
            while (i_re249) < (vsize_re1): 
                rec96[i_re249] = ((dsp.const508) * ((((dsp.const512) * (rec97[i_re249])) + ((dsp.const513) * (rec97[(i_re249) - (S32(1))]))) + ((dsp.const512) * (rec97[(i_re249) - (S32(2))])))) - ((dsp.const514) * (((dsp.const515) * (rec96[(i_re249) - (S32(2))])) + ((dsp.const516) * (rec96[(i_re249) - (S32(1))]))))
                i_re249 = (i_re249) + (S32(1))
            # Post code 
            var j205_re1 = S32(0)
            while (j205_re1) < (S32(4)): 
                dsp.rec96_perm[j205_re1] = rec96_tmp[(vsize_re1) + (j205_re1)]
                j205_re1 = (j205_re1) + (S32(1))
            # Recursive loop 121 
            # Pre code 
            var j206_re1 = S32(0)
            comptime dtype467 = f64
            comptime width467 = S32(simd_width_of[dtype467]())
            while j206_re1 <= S32(4) - width467:
                var values = simd_load(dsp.rec95_perm, j206_re1)
                simd_store(rec95_tmp, j206_re1, values)
                j206_re1 = j206_re1 + S32(width467)
            # Compute code 
            var i_re250 = S32(0)
            while (i_re250) < (vsize_re1): 
                rec95[i_re250] = ((slow8) * (rec95[(i_re250) - (S32(1))])) + ((slow9) * (abs((dsp.const514) * ((((dsp.const518) * (rec96[i_re250])) + ((dsp.const519) * (rec96[(i_re250) - (S32(1))]))) + ((dsp.const518) * (rec96[(i_re250) - (S32(2))]))))))
                i_re250 = (i_re250) + (S32(1))
            # Post code 
            var j207_re1 = S32(0)
            while (j207_re1) < (S32(4)): 
                dsp.rec95_perm[j207_re1] = rec95_tmp[(vsize_re1) + (j207_re1)]
                j207_re1 = (j207_re1) + (S32(1))
            # Recursive loop 122 
            # Pre code 
            var j208_re1 = S32(0)
            comptime dtype469 = f64
            comptime width469 = S32(simd_width_of[dtype469]())
            while j208_re1 <= S32(4) - width469:
                var values = simd_load(dsp.rec105_perm, j208_re1)
                simd_store(rec105_tmp, j208_re1, values)
                j208_re1 = j208_re1 + S32(width469)
            # Compute code 
            var i_re251 = S32(0)
            while (i_re251) < (vsize_re1): 
                rec105[i_re251] = (zec18[i_re251]) - ((dsp.const520) * (((dsp.const521) * (rec105[(i_re251) - (S32(2))])) + ((dsp.const522) * (rec105[(i_re251) - (S32(1))]))))
                i_re251 = (i_re251) + (S32(1))
            # Post code 
            var j209_re1 = S32(0)
            while (j209_re1) < (S32(4)): 
                dsp.rec105_perm[j209_re1] = rec105_tmp[(vsize_re1) + (j209_re1)]
                j209_re1 = (j209_re1) + (S32(1))
            # Recursive loop 123 
            # Pre code 
            var j210_re1 = S32(0)
            comptime dtype471 = f64
            comptime width471 = S32(simd_width_of[dtype471]())
            while j210_re1 <= S32(4) - width471:
                var values = simd_load(dsp.rec104_perm, j210_re1)
                simd_store(rec104_tmp, j210_re1, values)
                j210_re1 = j210_re1 + S32(width471)
            # Compute code 
            var i_re252 = S32(0)
            while (i_re252) < (vsize_re1): 
                rec104[i_re252] = ((dsp.const520) * ((((dsp.const524) * (rec105[i_re252])) + ((dsp.const525) * (rec105[(i_re252) - (S32(1))]))) + ((dsp.const524) * (rec105[(i_re252) - (S32(2))])))) - ((dsp.const526) * (((dsp.const527) * (rec104[(i_re252) - (S32(2))])) + ((dsp.const528) * (rec104[(i_re252) - (S32(1))]))))
                i_re252 = (i_re252) + (S32(1))
            # Post code 
            var j211_re1 = S32(0)
            while (j211_re1) < (S32(4)): 
                dsp.rec104_perm[j211_re1] = rec104_tmp[(vsize_re1) + (j211_re1)]
                j211_re1 = (j211_re1) + (S32(1))
            # Recursive loop 124 
            # Pre code 
            var j212_re1 = S32(0)
            comptime dtype473 = f64
            comptime width473 = S32(simd_width_of[dtype473]())
            while j212_re1 <= S32(4) - width473:
                var values = simd_load(dsp.rec103_perm, j212_re1)
                simd_store(rec103_tmp, j212_re1, values)
                j212_re1 = j212_re1 + S32(width473)
            # Compute code 
            var i_re253 = S32(0)
            while (i_re253) < (vsize_re1): 
                rec103[i_re253] = ((dsp.const526) * ((((dsp.const529) * (rec104[i_re253])) + ((dsp.const530) * (rec104[(i_re253) - (S32(1))]))) + ((dsp.const529) * (rec104[(i_re253) - (S32(2))])))) - ((dsp.const531) * (((dsp.const532) * (rec103[(i_re253) - (S32(2))])) + ((dsp.const533) * (rec103[(i_re253) - (S32(1))]))))
                i_re253 = (i_re253) + (S32(1))
            # Post code 
            var j213_re1 = S32(0)
            while (j213_re1) < (S32(4)): 
                dsp.rec103_perm[j213_re1] = rec103_tmp[(vsize_re1) + (j213_re1)]
                j213_re1 = (j213_re1) + (S32(1))
            # Recursive loop 125 
            # Pre code 
            var j214_re1 = S32(0)
            comptime dtype475 = f64
            comptime width475 = S32(simd_width_of[dtype475]())
            while j214_re1 <= S32(4) - width475:
                var values = simd_load(dsp.rec102_perm, j214_re1)
                simd_store(rec102_tmp, j214_re1, values)
                j214_re1 = j214_re1 + S32(width475)
            # Compute code 
            var i_re254 = S32(0)
            while (i_re254) < (vsize_re1): 
                rec102[i_re254] = ((slow8) * (rec102[(i_re254) - (S32(1))])) + ((slow9) * (abs((dsp.const531) * ((((dsp.const534) * (rec103[i_re254])) + ((dsp.const535) * (rec103[(i_re254) - (S32(1))]))) + ((dsp.const534) * (rec103[(i_re254) - (S32(2))]))))))
                i_re254 = (i_re254) + (S32(1))
            # Post code 
            var j215_re1 = S32(0)
            while (j215_re1) < (S32(4)): 
                dsp.rec102_perm[j215_re1] = rec102_tmp[(vsize_re1) + (j215_re1)]
                j215_re1 = (j215_re1) + (S32(1))
            # Vectorizable loop 126 
            # Compute code 
            var i_re255 = S32(0)
            comptime dtype477 = dfaust
            comptime width477 = S32(simd_width_of[dtype477]())
            while i_re255 <= vsize_re1 - width477:

                dsp.vbargraph0 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec7, i_re255)))))
                dsp.vbargraph1 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec11, i_re255)))))
                dsp.vbargraph2 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec18, i_re255)))))
                dsp.vbargraph3 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec25, i_re255)))))
                dsp.vbargraph4 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec32, i_re255)))))
                dsp.vbargraph5 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec39, i_re255)))))
                dsp.vbargraph6 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec46, i_re255)))))
                dsp.vbargraph7 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec53, i_re255)))))
                dsp.vbargraph8 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec60, i_re255)))))
                dsp.vbargraph9 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec67, i_re255)))))
                dsp.vbargraph10 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec74, i_re255)))))
                dsp.vbargraph11 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec81, i_re255)))))
                dsp.vbargraph12 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec88, i_re255)))))
                dsp.vbargraph13 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec95, i_re255)))))
                dsp.vbargraph14 = FaustFloat((slow10) + ((2e+01) * (log10(simd_load(rec102, i_re255)))))
                simd_load(zec19, i_re255) = simd_load(zec5, i_re255)
                                i_re255 = i_re255 + S32(width477)
            # Vectorizable loop 127 
            # Compute code 
            var i_re256 = S32(0)
            comptime dtype478 = dfaust
            comptime width478 = S32(simd_width_of[dtype478]())
            while i_re256 <= vsize_re1 - width478:
                var values = (simd_load(zec19, i_re256)).cast[dfaust]()
                simd_store(output0, i_re256, values)
                i_re256 = i_re256 + S32(width478)
            # Vectorizable loop 128 
            # Compute code 
            var i_re257 = S32(0)
            comptime dtype479 = dfaust
            comptime width479 = S32(simd_width_of[dtype479]())
            while i_re257 <= vsize_re1 - width479:
                var values = (simd_load(zec19, i_re257)).cast[dfaust]()
                simd_store(output1, i_re257, values)
                i_re257 = i_re257 + S32(width479)

# ==============================================================================
# Faust generated DSP code end.
# ==============================================================================
# Second section of architecture provided code start.
# Defines the main entry point of the application.
# Initializes the dsp object, allocates and intializes the audio buffers and
# calls the inspect function to run the dsp code.
# ==============================================================================

def main() -> None:
    var dsp = alloc[mydsp](1)
    dsp[] = mydsp()
    dsp[].init(SAMP_RATE)
    var n_ins = dsp[].get_num_inputs()
    var n_outs = dsp[].get_num_outputs()
    var base, err = make_streams[dfaust](BUFF_SIZE, n_ins, n_outs)
    if err:
        dsp.free()
        return
    var ptr = base.unsafe_value()
    var inputs = ptr.bitcast[Ptr[FaustFloat, READ_NOTRK]]().as_immutable()
    var outputs = (ptr + n_ins).bitcast[Ptr[FaustFloat, MUTA_NOTRK]]()
    inspect_compute(dsp[], inputs, outputs)
    ptr.free()
    dsp.free()

@no_inline
@export("inspect_compute")
def inspect_compute(
    mut dsp: mydsp, inputs: ReadStreams, outputs: MutaStreams
) abi("Mojo") -> None:
    for _ in range(COMPUTE_ITERS):
        keep(inputs)
        keep(outputs)
        dsp.compute(BUFF_SIZE, inputs, outputs)
        clobber_memory()

# ==============================================================================
# Second section of architecture provided code end.
# ==============================================================================
