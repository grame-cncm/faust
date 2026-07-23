# ==============================================================================
# Faust to Mojo architecture file for the benchmark framework integration.
# Provides the definitons and the main entry point to run the dsp code in
# several batches and print the write the report to `.tab` and `.csv` files 
# ==============================================================================
# First section of architecture provided code start.
# Imports the modules and the definitions of the architecture code.
# ==============================================================================

from conf import *
from help import *
from mem import *
from bench import *
from dsp import *
from gui import *
from meta import *

# ==============================================================================
# First section of architecture provided code end.
# ==============================================================================
# Code generated with Faust 2.85.5 (https://faust.grame.fr)
# name: "cubic_distortion"
# Compilation options: 
#   -a bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 
#   -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs
# ==============================================================================

comptime dreal = f64
comptime wreal = simd_width_of[dreal]()
comptime Real = Scalar[dreal]
comptime RVec = Vec[dreal]

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
    def get_sample_rate(imm dsp) -> S32:
        return dsp.sample_rate

    @always_inline
    def get_num_outputs(imm dsp) -> S32:
        return 2

    @always_inline
    def get_num_inputs(imm dsp) -> S32:
        return 0

    @always_inline
    def class_init(mut dsp, imm sample_rate: S32) -> None:
        pass

    @always_inline
    def instance_constants(mut dsp, imm sample_rate: S32) -> None:
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
        return "{\"name\": \"cubic_distortion\",\"filename\": \"cubic_distortion.dsp\",\"version\": \"2.85.5\",\"compile_options\": \"-a bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs\",\"library_list\": [\"/usr/local/share/faust/oscillator.lib\",\"/usr/local/share/faust/music.lib\",\"/usr/local/share/faust/math.lib\",\"/usr/local/share/faust/filter.lib\",\"/usr/local/share/faust/effect.lib\"],\"include_pathnames\": [\"/Users/manuelfarzini/Personal/dev/repo/faust/build/share/faust\",\"/usr/local/share/faust\",\"/usr/share/faust\",\"/Users/manuelfarzini/Personal/dev/repo/faust/architecture/_bench/src\",\"/Users/manuelfarzini/Personal/dev/repo/faust/architecture/_bench/src\"],\"size\": 7916,\"inputs\": 0,\"outputs\": 2,\"meta\": [ { \"compile_options\": \"-a bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs\" },{ \"effect.lib/author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"effect.lib/copyright\": \"Julius O. Smith III\" },{ \"effect.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"effect.lib/exciter_author\": \"Priyanka Shekar (pshekar@ccrma.stanford.edu)\" },{ \"effect.lib/exciter_copyright\": \"Copyright (c) 2013 Priyanka Shekar\" },{ \"effect.lib/exciter_license\": \"MIT License (MIT)\" },{ \"effect.lib/exciter_name\": \"Harmonic Exciter\" },{ \"effect.lib/exciter_version\": \"1.0\" },{ \"effect.lib/license\": \"STK-4.3\" },{ \"effect.lib/name\": \"Faust Audio Effect Library\" },{ \"effect.lib/version\": \"1.33\" },{ \"filename\": \"cubic_distortion.dsp\" },{ \"filter.lib/author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"filter.lib/copyright\": \"Julius O. Smith III\" },{ \"filter.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"filter.lib/license\": \"STK-4.3\" },{ \"filter.lib/name\": \"Faust Filter Library\" },{ \"filter.lib/reference\": \"https://ccrma.stanford.edu/~jos/filters/\" },{ \"filter.lib/version\": \"1.29\" },{ \"math.lib/author\": \"GRAME\" },{ \"math.lib/copyright\": \"GRAME\" },{ \"math.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"math.lib/license\": \"LGPL with exception\" },{ \"math.lib/name\": \"Math Library\" },{ \"math.lib/version\": \"1.0\" },{ \"music.lib/author\": \"GRAME\" },{ \"music.lib/copyright\": \"GRAME\" },{ \"music.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"music.lib/license\": \"LGPL with exception\" },{ \"music.lib/name\": \"Music Library\" },{ \"music.lib/version\": \"1.0\" },{ \"name\": \"cubic_distortion\" },{ \"oscillator.lib/author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"oscillator.lib/copyright\": \"Julius O. Smith III\" },{ \"oscillator.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"oscillator.lib/license\": \"STK-4.3\" },{ \"oscillator.lib/name\": \"Faust Oscillator Library\" },{ \"oscillator.lib/version\": \"1.11\" }],\"ui\": [ {\"type\": \"vgroup\",\"label\": \"cubic_distortion\",\"items\": [ {\"type\": \"vgroup\",\"label\": \"0x00\",\"meta\": [{ \"1\": \"\" }],\"items\": [ {\"type\": \"vgroup\",\"label\": \"SINE WAVE OSCILLATOR oscrs\",\"meta\": [{ \"0\": \"\" },{ \"tooltip\": \"Sine oscillator based on 2D vector rotation\" }],\"items\": [ {\"type\": \"hslider\",\"label\": \"Amplitude\",\"varname\": \"fHslider1\",\"shortname\": \"Amplitude\",\"address\": \"/cubic_distortion/0x00/SINE_WAVE_OSCILLATOR_oscrs/Amplitude\",\"meta\": [{ \"1\": \"\" },{ \"tooltip\": \"Sawtooth waveform amplitude\" },{ \"unit\": \"dB\" }],\"init\": -20,\"min\": -120,\"max\": 10,\"step\": 0.1},{\"type\": \"hslider\",\"label\": \"Frequency\",\"varname\": \"fHslider3\",\"shortname\": \"Frequency\",\"address\": \"/cubic_distortion/0x00/SINE_WAVE_OSCILLATOR_oscrs/Frequency\",\"meta\": [{ \"2\": \"\" },{ \"tooltip\": \"Sine wave frequency as a Piano Key (PK) number (A440 = 49 PK)\" },{ \"unit\": \"PK\" }],\"init\": 49,\"min\": 1,\"max\": 88,\"step\": 0.01},{\"type\": \"hslider\",\"label\": \"Portamento\",\"varname\": \"fHslider2\",\"shortname\": \"Portamento\",\"address\": \"/cubic_distortion/0x00/SINE_WAVE_OSCILLATOR_oscrs/Portamento\",\"meta\": [{ \"3\": \"\" },{ \"scale\": \"log\" },{ \"tooltip\": \"Portamento (frequency-glide) time-constant in seconds\" },{ \"unit\": \"sec\" }],\"init\": 0.1,\"min\": 0.001,\"max\": 10,\"step\": 0.001}]}]},{\"type\": \"vgroup\",\"label\": \"0x00\",\"meta\": [{ \"2\": \"\" }],\"items\": [ {\"type\": \"vgroup\",\"label\": \"CUBIC NONLINEARITY cubicnl\",\"meta\": [{ \"tooltip\": \"Reference:          https://ccrma.stanford.edu/~jos/pasp/Cubic_Soft_Clipper.html\" }],\"items\": [ {\"type\": \"checkbox\",\"label\": \"Bypass\",\"varname\": \"fCheckbox0\",\"shortname\": \"Bypass\",\"address\": \"/cubic_distortion/0x00/CUBIC_NONLINEARITY_cubicnl/Bypass\",\"meta\": [{ \"0\": \"\" },{ \"tooltip\": \"When this is checked, the nonlinearity has no effect\" }]},{\"type\": \"hslider\",\"label\": \"Drive\",\"varname\": \"fHslider4\",\"shortname\": \"Drive\",\"address\": \"/cubic_distortion/0x00/CUBIC_NONLINEARITY_cubicnl/Drive\",\"meta\": [{ \"1\": \"\" },{ \"tooltip\": \"Amount of distortion\" }],\"init\": 0,\"min\": 0,\"max\": 1,\"step\": 0.01},{\"type\": \"hslider\",\"label\": \"Offset\",\"varname\": \"fHslider0\",\"shortname\": \"Offset\",\"address\": \"/cubic_distortion/0x00/CUBIC_NONLINEARITY_cubicnl/Offset\",\"meta\": [{ \"2\": \"\" },{ \"tooltip\": \"Brings in even harmonics\" }],\"init\": 0,\"min\": 0,\"max\": 1,\"step\": 0.01}]}]},{\"type\": \"vgroup\",\"label\": \"0x00\",\"meta\": [{ \"3\": \"\" }],\"items\": [ {\"type\": \"hgroup\",\"label\": \"CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning LP, 9 octaves below 16000 Hz, HP\",\"meta\": [{ \"0\": \"\" },{ \"tooltip\": \"See Faust\'s filter.lib for documentation and references\" }],\"items\": [ {\"type\": \"vbargraph\",\"label\": \"vbargraph0\",\"varname\": \"fVbargraph14\",\"shortname\": \"vbargraph0\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph0\",\"meta\": [{ \"0\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph1\",\"varname\": \"fVbargraph13\",\"shortname\": \"vbargraph1\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph1\",\"meta\": [{ \"1\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph2\",\"varname\": \"fVbargraph12\",\"shortname\": \"vbargraph2\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph2\",\"meta\": [{ \"2\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph3\",\"varname\": \"fVbargraph11\",\"shortname\": \"vbargraph3\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph3\",\"meta\": [{ \"3\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph4\",\"varname\": \"fVbargraph10\",\"shortname\": \"vbargraph4\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph4\",\"meta\": [{ \"4\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph5\",\"varname\": \"fVbargraph9\",\"shortname\": \"vbargraph5\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph5\",\"meta\": [{ \"5\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph6\",\"varname\": \"fVbargraph8\",\"shortname\": \"vbargraph6\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph6\",\"meta\": [{ \"6\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph7\",\"varname\": \"fVbargraph7\",\"shortname\": \"vbargraph7\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph7\",\"meta\": [{ \"7\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph8\",\"varname\": \"fVbargraph6\",\"shortname\": \"vbargraph8\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph8\",\"meta\": [{ \"8\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph9\",\"varname\": \"fVbargraph5\",\"shortname\": \"vbargraph9\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph9\",\"meta\": [{ \"9\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph10\",\"varname\": \"fVbargraph4\",\"shortname\": \"vbargraph10\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph10\",\"meta\": [{ \"10\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph11\",\"varname\": \"fVbargraph3\",\"shortname\": \"vbargraph11\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph11\",\"meta\": [{ \"11\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph12\",\"varname\": \"fVbargraph2\",\"shortname\": \"vbargraph12\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph12\",\"meta\": [{ \"12\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph13\",\"varname\": \"fVbargraph1\",\"shortname\": \"vbargraph13\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph13\",\"meta\": [{ \"13\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph14\",\"varname\": \"fVbargraph0\",\"shortname\": \"vbargraph14\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph14\",\"meta\": [{ \"14\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10}]},{\"type\": \"hgroup\",\"label\": \"SPECTRUM ANALYZER CONTROLS\",\"meta\": [{ \"1\": \"\" }],\"items\": [ {\"type\": \"hslider\",\"label\": \"Level Averaging Time\",\"varname\": \"fHslider5\",\"shortname\": \"Level_Averaging_Time\",\"address\": \"/cubic_distortion/0x00/SPECTRUM_ANALYZER_CONTROLS/Level_Averaging_Time\",\"meta\": [{ \"0\": \"\" },{ \"scale\": \"log\" },{ \"tooltip\": \"band-level averaging time in milliseconds\" },{ \"unit\": \"ms\" }],\"init\": 100,\"min\": 1,\"max\": 10000,\"step\": 1},{\"type\": \"hslider\",\"label\": \"Level dB Offset\",\"varname\": \"fHslider6\",\"shortname\": \"Level_dB_Offset\",\"address\": \"/cubic_distortion/0x00/SPECTRUM_ANALYZER_CONTROLS/Level_dB_Offset\",\"meta\": [{ \"1\": \"\" },{ \"tooltip\": \"Level offset in decibels\" },{ \"unit\": \"dB\" }],\"init\": 50,\"min\": 0,\"max\": 100,\"step\": 1}]}]}]}]}"

    @always_inline
    def metadata(imm dsp, mut meta: Some[FaustMeta]) -> None:
        meta.declare("compile_options", "-a bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs")
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
    def compute(mut dsp, var count: S32, var inputs: ImmStreams, var outputs: MutStreams) -> None:
        comptime assert dfaust == DType.float32, "Expected 32 bit float driver precision."
        comptime vsize = S32(4)
        comptime hsize = S32(2)
        var vindex = S32(0)
        var end = count - vsize
        var lo: SIMD[dfaust, simd_width_of[f64]()]
        var hi: SIMD[dfaust, simd_width_of[f64]()]
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
        while vindex <= end:
            var output0 = Ptr(to=output0_ptr[vindex])
            var output1 = Ptr(to=output1_ptr[vindex])
            vstore(rec1_tmp, vload[w64](dsp.rec1_perm))
            vstore(rec1_tmp, vload[w64](dsp.rec1_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec1[i] = (slow0) + ((0.999) * (rec1[(i) - (S32(1))]))
            vstore(dsp.rec1_perm, vload[w64](rec1_tmp, vsize))
            vstore(dsp.rec1_perm, vload[w64](rec1_tmp, vsize + hsize), hsize)
            vstore(rec2_tmp, vload[w64](dsp.rec2_perm))
            vstore(rec2_tmp, vload[w64](dsp.rec2_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec2[i] = (slow1) + ((0.999) * (rec2[(i) - (S32(1))]))
            vstore(dsp.rec2_perm, vload[w64](rec2_tmp, vsize))
            vstore(dsp.rec2_perm, vload[w64](rec2_tmp, vsize + hsize), hsize)
            vstore(rec5_tmp, vload[w64](dsp.rec5_perm))
            vstore(rec5_tmp, vload[w64](dsp.rec5_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec5[i] = ((rec5[(i) - (S32(1))]) * (slow3)) + (slow4)
            vstore(dsp.rec5_perm, vload[w64](rec5_tmp, vsize))
            vstore(dsp.rec5_perm, vload[w64](rec5_tmp, vsize + hsize), hsize)
            vstore(zec0, (dsp.const2) * (vload[w64](rec5)))
            vstore(zec0, (dsp.const2) * (vload[w64](rec5, hsize)), hsize)
            vstore(zec1, sin(vload[w64](zec0)))
            vstore(zec1, sin(vload[w64](zec0, hsize)), hsize)
            vstore(zec2, cos(vload[w64](zec0)))
            vstore(zec2, cos(vload[w64](zec0, hsize)), hsize)
            vstore(i_vec0_tmp, vload[w64](dsp.i_vec0_perm))
            vstore(i_vec0, S32Vec(1))
            vstore(dsp.i_vec0_perm, vload[w64](i_vec0_tmp, vsize))
            vstore(rec3_tmp, vload[w64](dsp.rec3_perm))
            vstore(rec3_tmp, vload[w64](dsp.rec3_perm, hsize), hsize)
            vstore(rec4_tmp, vload[w64](dsp.rec4_perm))
            vstore(rec4_tmp, vload[w64](dsp.rec4_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec3[i] = ((rec4[(i) - (S32(1))]) * (zec1[i])) + ((rec3[(i) - (S32(1))]) * (zec2[i]))
                rec4[i] = ((F64((S32(1)) - (i_vec0[(i) - (S32(1))]))) + ((rec4[(i) - (S32(1))]) * (zec2[i]))) - ((zec1[i]) * (rec3[(i) - (S32(1))]))
            vstore(dsp.rec3_perm, vload[w64](rec3_tmp, vsize))
            vstore(dsp.rec3_perm, vload[w64](rec3_tmp, vsize + hsize), hsize)
            vstore(dsp.rec4_perm, vload[w64](rec4_tmp, vsize))
            vstore(dsp.rec4_perm, vload[w64](rec4_tmp, vsize + hsize), hsize)
            vstore(rec6_tmp, vload[w64](dsp.rec6_perm))
            vstore(rec6_tmp, vload[w64](dsp.rec6_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec6[i] = (slow5) + ((0.999) * (rec6[(i) - (S32(1))]))
            vstore(dsp.rec6_perm, vload[w64](rec6_tmp, vsize))
            vstore(dsp.rec6_perm, vload[w64](rec6_tmp, vsize + hsize), hsize)
            vstore(zec3, (vload[w64](rec2)) * (vload[w64](rec3)))
            vstore(zec3, (vload[w64](rec2, hsize)) * (vload[w64](rec3, hsize)), hsize)
            vstore(zec4, max(F64Vec(-1.0), min(F64Vec(1.0), (vload[w64](rec1)) + ((F64Vec(0.0) if i_slow6 else vload[w64](zec3)) * (pow(F64Vec(1e+01), (F64Vec(2.0)) * (vload[w64](rec6))))))))
            vstore(zec4, max(F64Vec(-1.0), min(F64Vec(1.0), (vload[w64](rec1, hsize)) + ((F64Vec(0.0) if i_slow6 else vload[w64](zec3, hsize)) * (pow(F64Vec(1e+01), (F64Vec(2.0)) * (vload[w64](rec6, hsize))))))), hsize)
            vstore(yec0_tmp, vload[w64](dsp.yec0_perm))
            vstore(yec0_tmp, vload[w64](dsp.yec0_perm, hsize), hsize)
            vstore(yec0, (vload[w64](zec4)) * ((F64Vec(1.0)) - ((F64Vec(0.3333333333333333)) * (pow_unrolled[2](vload[w64](zec4))))))
            vstore(yec0, (vload[w64](zec4, hsize)) * ((F64Vec(1.0)) - ((F64Vec(0.3333333333333333)) * (pow_unrolled[2](vload[w64](zec4, hsize))))), hsize)
            vstore(dsp.yec0_perm, vload[w64](yec0_tmp, vsize))
            vstore(dsp.yec0_perm, vload[w64](yec0_tmp, vsize + hsize), hsize)
            vstore(rec0_tmp, vload[w64](dsp.rec0_perm))
            vstore(rec0_tmp, vload[w64](dsp.rec0_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec0[i] = (((0.995) * (rec0[(i) - (S32(1))])) + (yec0[i])) - (yec0[(i) - (S32(1))])
            vstore(dsp.rec0_perm, vload[w64](rec0_tmp, vsize))
            vstore(dsp.rec0_perm, vload[w64](rec0_tmp, vsize + hsize), hsize)
            vstore(zec5, vload[w64](zec3) if i_slow6 else vload[w64](rec0))
            vstore(zec5, vload[w64](zec3, hsize) if i_slow6 else vload[w64](rec0, hsize), hsize)
            vstore(rec10_tmp, vload[w64](dsp.rec10_perm))
            vstore(rec10_tmp, vload[w64](dsp.rec10_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec10[i] = (zec5[i]) - ((dsp.const5) * (((dsp.const6) * (rec10[(i) - (S32(2))])) + ((dsp.const9) * (rec10[(i) - (S32(1))]))))
            vstore(dsp.rec10_perm, vload[w64](rec10_tmp, vsize))
            vstore(dsp.rec10_perm, vload[w64](rec10_tmp, vsize + hsize), hsize)
            vstore(rec9_tmp, vload[w64](dsp.rec9_perm))
            vstore(rec9_tmp, vload[w64](dsp.rec9_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec9[i] = ((dsp.const5) * ((((dsp.const11) * (rec10[i])) + ((dsp.const12) * (rec10[(i) - (S32(1))]))) + ((dsp.const11) * (rec10[(i) - (S32(2))])))) - ((dsp.const13) * (((dsp.const14) * (rec9[(i) - (S32(2))])) + ((dsp.const15) * (rec9[(i) - (S32(1))]))))
            vstore(dsp.rec9_perm, vload[w64](rec9_tmp, vsize))
            vstore(dsp.rec9_perm, vload[w64](rec9_tmp, vsize + hsize), hsize)
            vstore(rec8_tmp, vload[w64](dsp.rec8_perm))
            vstore(rec8_tmp, vload[w64](dsp.rec8_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec8[i] = ((dsp.const13) * ((((dsp.const17) * (rec9[i])) + ((dsp.const18) * (rec9[(i) - (S32(1))]))) + ((dsp.const17) * (rec9[(i) - (S32(2))])))) - ((dsp.const19) * (((dsp.const20) * (rec8[(i) - (S32(2))])) + ((dsp.const21) * (rec8[(i) - (S32(1))]))))
            vstore(dsp.rec8_perm, vload[w64](rec8_tmp, vsize))
            vstore(dsp.rec8_perm, vload[w64](rec8_tmp, vsize + hsize), hsize)
            vstore(rec7_tmp, vload[w64](dsp.rec7_perm))
            vstore(rec7_tmp, vload[w64](dsp.rec7_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec7[i] = ((rec7[(i) - (S32(1))]) * (slow8)) + ((abs((dsp.const19) * ((((dsp.const24) * (rec8[i])) + ((dsp.const25) * (rec8[(i) - (S32(1))]))) + ((dsp.const24) * (rec8[(i) - (S32(2))]))))) * (slow9))
            vstore(dsp.rec7_perm, vload[w64](rec7_tmp, vsize))
            vstore(dsp.rec7_perm, vload[w64](rec7_tmp, vsize + hsize), hsize)
            vstore(rec17_tmp, vload[w64](dsp.rec17_perm))
            vstore(rec17_tmp, vload[w64](dsp.rec17_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec17[i] = (zec5[i]) - ((dsp.const26) * (((dsp.const27) * (rec17[(i) - (S32(2))])) + ((dsp.const28) * (rec17[(i) - (S32(1))]))))
            vstore(dsp.rec17_perm, vload[w64](rec17_tmp, vsize))
            vstore(dsp.rec17_perm, vload[w64](rec17_tmp, vsize + hsize), hsize)
            vstore(rec16_tmp, vload[w64](dsp.rec16_perm))
            vstore(rec16_tmp, vload[w64](dsp.rec16_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec16[i] = ((dsp.const26) * ((((dsp.const30) * (rec17[i])) + ((dsp.const31) * (rec17[(i) - (S32(1))]))) + ((dsp.const30) * (rec17[(i) - (S32(2))])))) - ((dsp.const32) * (((dsp.const33) * (rec16[(i) - (S32(2))])) + ((dsp.const34) * (rec16[(i) - (S32(1))]))))
            vstore(dsp.rec16_perm, vload[w64](rec16_tmp, vsize))
            vstore(dsp.rec16_perm, vload[w64](rec16_tmp, vsize + hsize), hsize)
            vstore(rec15_tmp, vload[w64](dsp.rec15_perm))
            vstore(rec15_tmp, vload[w64](dsp.rec15_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec15[i] = ((dsp.const32) * ((((dsp.const35) * (rec16[i])) + ((dsp.const36) * (rec16[(i) - (S32(1))]))) + ((dsp.const35) * (rec16[(i) - (S32(2))])))) - ((dsp.const37) * (((dsp.const38) * (rec15[(i) - (S32(2))])) + ((dsp.const39) * (rec15[(i) - (S32(1))]))))
            vstore(dsp.rec15_perm, vload[w64](rec15_tmp, vsize))
            vstore(dsp.rec15_perm, vload[w64](rec15_tmp, vsize + hsize), hsize)
            vstore(zec6, (dsp.const37) * ((((dsp.const40) * (vload[w64](rec15))) + ((dsp.const41) * (vload[w64](rec15, - S32(1))))) + ((dsp.const40) * (vload[w64](rec15, - S32(2))))))
            vstore(zec6, (dsp.const37) * ((((dsp.const40) * (vload[w64](rec15, hsize))) + ((dsp.const41) * (vload[w64](rec15, - S32(1) + hsize)))) + ((dsp.const40) * (vload[w64](rec15, - S32(2) + hsize)))), hsize)
            vstore(rec14_tmp, vload[w64](dsp.rec14_perm))
            vstore(rec14_tmp, vload[w64](dsp.rec14_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec14[i] = (zec6[i]) - ((dsp.const44) * (((dsp.const45) * (rec14[(i) - (S32(2))])) + ((dsp.const48) * (rec14[(i) - (S32(1))]))))
            vstore(dsp.rec14_perm, vload[w64](rec14_tmp, vsize))
            vstore(dsp.rec14_perm, vload[w64](rec14_tmp, vsize + hsize), hsize)
            vstore(rec13_tmp, vload[w64](dsp.rec13_perm))
            vstore(rec13_tmp, vload[w64](dsp.rec13_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec13[i] = ((dsp.const44) * ((((dsp.const50) * (rec14[i])) + ((dsp.const51) * (rec14[(i) - (S32(1))]))) + ((dsp.const50) * (rec14[(i) - (S32(2))])))) - ((dsp.const52) * (((dsp.const53) * (rec13[(i) - (S32(2))])) + ((dsp.const54) * (rec13[(i) - (S32(1))]))))
            vstore(dsp.rec13_perm, vload[w64](rec13_tmp, vsize))
            vstore(dsp.rec13_perm, vload[w64](rec13_tmp, vsize + hsize), hsize)
            vstore(rec12_tmp, vload[w64](dsp.rec12_perm))
            vstore(rec12_tmp, vload[w64](dsp.rec12_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec12[i] = ((dsp.const52) * ((((dsp.const56) * (rec13[i])) + ((dsp.const57) * (rec13[(i) - (S32(1))]))) + ((dsp.const56) * (rec13[(i) - (S32(2))])))) - ((dsp.const58) * (((dsp.const59) * (rec12[(i) - (S32(2))])) + ((dsp.const60) * (rec12[(i) - (S32(1))]))))
            vstore(dsp.rec12_perm, vload[w64](rec12_tmp, vsize))
            vstore(dsp.rec12_perm, vload[w64](rec12_tmp, vsize + hsize), hsize)
            vstore(rec11_tmp, vload[w64](dsp.rec11_perm))
            vstore(rec11_tmp, vload[w64](dsp.rec11_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec11[i] = ((slow8) * (rec11[(i) - (S32(1))])) + ((slow9) * (abs((dsp.const58) * ((((dsp.const62) * (rec12[i])) + ((dsp.const63) * (rec12[(i) - (S32(1))]))) + ((dsp.const62) * (rec12[(i) - (S32(2))]))))))
            vstore(dsp.rec11_perm, vload[w64](rec11_tmp, vsize))
            vstore(dsp.rec11_perm, vload[w64](rec11_tmp, vsize + hsize), hsize)
            vstore(rec24_tmp, vload[w64](dsp.rec24_perm))
            vstore(rec24_tmp, vload[w64](dsp.rec24_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec24[i] = (zec6[i]) - ((dsp.const64) * (((dsp.const65) * (rec24[(i) - (S32(2))])) + ((dsp.const66) * (rec24[(i) - (S32(1))]))))
            vstore(dsp.rec24_perm, vload[w64](rec24_tmp, vsize))
            vstore(dsp.rec24_perm, vload[w64](rec24_tmp, vsize + hsize), hsize)
            vstore(rec23_tmp, vload[w64](dsp.rec23_perm))
            vstore(rec23_tmp, vload[w64](dsp.rec23_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec23[i] = ((dsp.const64) * ((((dsp.const68) * (rec24[i])) + ((dsp.const69) * (rec24[(i) - (S32(1))]))) + ((dsp.const68) * (rec24[(i) - (S32(2))])))) - ((dsp.const70) * (((dsp.const71) * (rec23[(i) - (S32(2))])) + ((dsp.const72) * (rec23[(i) - (S32(1))]))))
            vstore(dsp.rec23_perm, vload[w64](rec23_tmp, vsize))
            vstore(dsp.rec23_perm, vload[w64](rec23_tmp, vsize + hsize), hsize)
            vstore(rec22_tmp, vload[w64](dsp.rec22_perm))
            vstore(rec22_tmp, vload[w64](dsp.rec22_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec22[i] = ((dsp.const70) * ((((dsp.const73) * (rec23[i])) + ((dsp.const74) * (rec23[(i) - (S32(1))]))) + ((dsp.const73) * (rec23[(i) - (S32(2))])))) - ((dsp.const75) * (((dsp.const76) * (rec22[(i) - (S32(2))])) + ((dsp.const77) * (rec22[(i) - (S32(1))]))))
            vstore(dsp.rec22_perm, vload[w64](rec22_tmp, vsize))
            vstore(dsp.rec22_perm, vload[w64](rec22_tmp, vsize + hsize), hsize)
            vstore(zec7, (dsp.const75) * ((((dsp.const78) * (vload[w64](rec22))) + ((dsp.const79) * (vload[w64](rec22, - S32(1))))) + ((dsp.const78) * (vload[w64](rec22, - S32(2))))))
            vstore(zec7, (dsp.const75) * ((((dsp.const78) * (vload[w64](rec22, hsize))) + ((dsp.const79) * (vload[w64](rec22, - S32(1) + hsize)))) + ((dsp.const78) * (vload[w64](rec22, - S32(2) + hsize)))), hsize)
            vstore(rec21_tmp, vload[w64](dsp.rec21_perm))
            vstore(rec21_tmp, vload[w64](dsp.rec21_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec21[i] = (zec7[i]) - ((dsp.const82) * (((dsp.const83) * (rec21[(i) - (S32(2))])) + ((dsp.const86) * (rec21[(i) - (S32(1))]))))
            vstore(dsp.rec21_perm, vload[w64](rec21_tmp, vsize))
            vstore(dsp.rec21_perm, vload[w64](rec21_tmp, vsize + hsize), hsize)
            vstore(rec20_tmp, vload[w64](dsp.rec20_perm))
            vstore(rec20_tmp, vload[w64](dsp.rec20_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec20[i] = ((dsp.const82) * ((((dsp.const88) * (rec21[i])) + ((dsp.const89) * (rec21[(i) - (S32(1))]))) + ((dsp.const88) * (rec21[(i) - (S32(2))])))) - ((dsp.const90) * (((dsp.const91) * (rec20[(i) - (S32(2))])) + ((dsp.const92) * (rec20[(i) - (S32(1))]))))
            vstore(dsp.rec20_perm, vload[w64](rec20_tmp, vsize))
            vstore(dsp.rec20_perm, vload[w64](rec20_tmp, vsize + hsize), hsize)
            vstore(rec19_tmp, vload[w64](dsp.rec19_perm))
            vstore(rec19_tmp, vload[w64](dsp.rec19_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec19[i] = ((dsp.const90) * ((((dsp.const94) * (rec20[i])) + ((dsp.const95) * (rec20[(i) - (S32(1))]))) + ((dsp.const94) * (rec20[(i) - (S32(2))])))) - ((dsp.const96) * (((dsp.const97) * (rec19[(i) - (S32(2))])) + ((dsp.const98) * (rec19[(i) - (S32(1))]))))
            vstore(dsp.rec19_perm, vload[w64](rec19_tmp, vsize))
            vstore(dsp.rec19_perm, vload[w64](rec19_tmp, vsize + hsize), hsize)
            vstore(rec18_tmp, vload[w64](dsp.rec18_perm))
            vstore(rec18_tmp, vload[w64](dsp.rec18_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec18[i] = ((slow8) * (rec18[(i) - (S32(1))])) + ((slow9) * (abs((dsp.const96) * ((((dsp.const100) * (rec19[i])) + ((dsp.const101) * (rec19[(i) - (S32(1))]))) + ((dsp.const100) * (rec19[(i) - (S32(2))]))))))
            vstore(dsp.rec18_perm, vload[w64](rec18_tmp, vsize))
            vstore(dsp.rec18_perm, vload[w64](rec18_tmp, vsize + hsize), hsize)
            vstore(rec31_tmp, vload[w64](dsp.rec31_perm))
            vstore(rec31_tmp, vload[w64](dsp.rec31_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec31[i] = (zec7[i]) - ((dsp.const102) * (((dsp.const103) * (rec31[(i) - (S32(2))])) + ((dsp.const104) * (rec31[(i) - (S32(1))]))))
            vstore(dsp.rec31_perm, vload[w64](rec31_tmp, vsize))
            vstore(dsp.rec31_perm, vload[w64](rec31_tmp, vsize + hsize), hsize)
            vstore(rec30_tmp, vload[w64](dsp.rec30_perm))
            vstore(rec30_tmp, vload[w64](dsp.rec30_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec30[i] = ((dsp.const102) * ((((dsp.const106) * (rec31[i])) + ((dsp.const107) * (rec31[(i) - (S32(1))]))) + ((dsp.const106) * (rec31[(i) - (S32(2))])))) - ((dsp.const108) * (((dsp.const109) * (rec30[(i) - (S32(2))])) + ((dsp.const110) * (rec30[(i) - (S32(1))]))))
            vstore(dsp.rec30_perm, vload[w64](rec30_tmp, vsize))
            vstore(dsp.rec30_perm, vload[w64](rec30_tmp, vsize + hsize), hsize)
            vstore(rec29_tmp, vload[w64](dsp.rec29_perm))
            vstore(rec29_tmp, vload[w64](dsp.rec29_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec29[i] = ((dsp.const108) * ((((dsp.const111) * (rec30[i])) + ((dsp.const112) * (rec30[(i) - (S32(1))]))) + ((dsp.const111) * (rec30[(i) - (S32(2))])))) - ((dsp.const113) * (((dsp.const114) * (rec29[(i) - (S32(2))])) + ((dsp.const115) * (rec29[(i) - (S32(1))]))))
            vstore(dsp.rec29_perm, vload[w64](rec29_tmp, vsize))
            vstore(dsp.rec29_perm, vload[w64](rec29_tmp, vsize + hsize), hsize)
            vstore(zec8, (dsp.const113) * ((((dsp.const116) * (vload[w64](rec29))) + ((dsp.const117) * (vload[w64](rec29, - S32(1))))) + ((dsp.const116) * (vload[w64](rec29, - S32(2))))))
            vstore(zec8, (dsp.const113) * ((((dsp.const116) * (vload[w64](rec29, hsize))) + ((dsp.const117) * (vload[w64](rec29, - S32(1) + hsize)))) + ((dsp.const116) * (vload[w64](rec29, - S32(2) + hsize)))), hsize)
            vstore(rec28_tmp, vload[w64](dsp.rec28_perm))
            vstore(rec28_tmp, vload[w64](dsp.rec28_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec28[i] = (zec8[i]) - ((dsp.const120) * (((dsp.const121) * (rec28[(i) - (S32(2))])) + ((dsp.const124) * (rec28[(i) - (S32(1))]))))
            vstore(dsp.rec28_perm, vload[w64](rec28_tmp, vsize))
            vstore(dsp.rec28_perm, vload[w64](rec28_tmp, vsize + hsize), hsize)
            vstore(rec27_tmp, vload[w64](dsp.rec27_perm))
            vstore(rec27_tmp, vload[w64](dsp.rec27_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec27[i] = ((dsp.const120) * ((((dsp.const126) * (rec28[i])) + ((dsp.const127) * (rec28[(i) - (S32(1))]))) + ((dsp.const126) * (rec28[(i) - (S32(2))])))) - ((dsp.const128) * (((dsp.const129) * (rec27[(i) - (S32(2))])) + ((dsp.const130) * (rec27[(i) - (S32(1))]))))
            vstore(dsp.rec27_perm, vload[w64](rec27_tmp, vsize))
            vstore(dsp.rec27_perm, vload[w64](rec27_tmp, vsize + hsize), hsize)
            vstore(rec26_tmp, vload[w64](dsp.rec26_perm))
            vstore(rec26_tmp, vload[w64](dsp.rec26_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec26[i] = ((dsp.const128) * ((((dsp.const132) * (rec27[i])) + ((dsp.const133) * (rec27[(i) - (S32(1))]))) + ((dsp.const132) * (rec27[(i) - (S32(2))])))) - ((dsp.const134) * (((dsp.const135) * (rec26[(i) - (S32(2))])) + ((dsp.const136) * (rec26[(i) - (S32(1))]))))
            vstore(dsp.rec26_perm, vload[w64](rec26_tmp, vsize))
            vstore(dsp.rec26_perm, vload[w64](rec26_tmp, vsize + hsize), hsize)
            vstore(rec25_tmp, vload[w64](dsp.rec25_perm))
            vstore(rec25_tmp, vload[w64](dsp.rec25_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec25[i] = ((slow8) * (rec25[(i) - (S32(1))])) + ((slow9) * (abs((dsp.const134) * ((((dsp.const138) * (rec26[i])) + ((dsp.const139) * (rec26[(i) - (S32(1))]))) + ((dsp.const138) * (rec26[(i) - (S32(2))]))))))
            vstore(dsp.rec25_perm, vload[w64](rec25_tmp, vsize))
            vstore(dsp.rec25_perm, vload[w64](rec25_tmp, vsize + hsize), hsize)
            vstore(rec38_tmp, vload[w64](dsp.rec38_perm))
            vstore(rec38_tmp, vload[w64](dsp.rec38_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec38[i] = (zec8[i]) - ((dsp.const140) * (((dsp.const141) * (rec38[(i) - (S32(2))])) + ((dsp.const142) * (rec38[(i) - (S32(1))]))))
            vstore(dsp.rec38_perm, vload[w64](rec38_tmp, vsize))
            vstore(dsp.rec38_perm, vload[w64](rec38_tmp, vsize + hsize), hsize)
            vstore(rec37_tmp, vload[w64](dsp.rec37_perm))
            vstore(rec37_tmp, vload[w64](dsp.rec37_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec37[i] = ((dsp.const140) * ((((dsp.const144) * (rec38[i])) + ((dsp.const145) * (rec38[(i) - (S32(1))]))) + ((dsp.const144) * (rec38[(i) - (S32(2))])))) - ((dsp.const146) * (((dsp.const147) * (rec37[(i) - (S32(2))])) + ((dsp.const148) * (rec37[(i) - (S32(1))]))))
            vstore(dsp.rec37_perm, vload[w64](rec37_tmp, vsize))
            vstore(dsp.rec37_perm, vload[w64](rec37_tmp, vsize + hsize), hsize)
            vstore(rec36_tmp, vload[w64](dsp.rec36_perm))
            vstore(rec36_tmp, vload[w64](dsp.rec36_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec36[i] = ((dsp.const146) * ((((dsp.const149) * (rec37[i])) + ((dsp.const150) * (rec37[(i) - (S32(1))]))) + ((dsp.const149) * (rec37[(i) - (S32(2))])))) - ((dsp.const151) * (((dsp.const152) * (rec36[(i) - (S32(2))])) + ((dsp.const153) * (rec36[(i) - (S32(1))]))))
            vstore(dsp.rec36_perm, vload[w64](rec36_tmp, vsize))
            vstore(dsp.rec36_perm, vload[w64](rec36_tmp, vsize + hsize), hsize)
            vstore(zec9, (dsp.const151) * ((((dsp.const154) * (vload[w64](rec36))) + ((dsp.const155) * (vload[w64](rec36, - S32(1))))) + ((dsp.const154) * (vload[w64](rec36, - S32(2))))))
            vstore(zec9, (dsp.const151) * ((((dsp.const154) * (vload[w64](rec36, hsize))) + ((dsp.const155) * (vload[w64](rec36, - S32(1) + hsize)))) + ((dsp.const154) * (vload[w64](rec36, - S32(2) + hsize)))), hsize)
            vstore(rec35_tmp, vload[w64](dsp.rec35_perm))
            vstore(rec35_tmp, vload[w64](dsp.rec35_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec35[i] = (zec9[i]) - ((dsp.const158) * (((dsp.const159) * (rec35[(i) - (S32(2))])) + ((dsp.const162) * (rec35[(i) - (S32(1))]))))
            vstore(dsp.rec35_perm, vload[w64](rec35_tmp, vsize))
            vstore(dsp.rec35_perm, vload[w64](rec35_tmp, vsize + hsize), hsize)
            vstore(rec34_tmp, vload[w64](dsp.rec34_perm))
            vstore(rec34_tmp, vload[w64](dsp.rec34_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec34[i] = ((dsp.const158) * ((((dsp.const164) * (rec35[i])) + ((dsp.const165) * (rec35[(i) - (S32(1))]))) + ((dsp.const164) * (rec35[(i) - (S32(2))])))) - ((dsp.const166) * (((dsp.const167) * (rec34[(i) - (S32(2))])) + ((dsp.const168) * (rec34[(i) - (S32(1))]))))
            vstore(dsp.rec34_perm, vload[w64](rec34_tmp, vsize))
            vstore(dsp.rec34_perm, vload[w64](rec34_tmp, vsize + hsize), hsize)
            vstore(rec33_tmp, vload[w64](dsp.rec33_perm))
            vstore(rec33_tmp, vload[w64](dsp.rec33_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec33[i] = ((dsp.const166) * ((((dsp.const170) * (rec34[i])) + ((dsp.const171) * (rec34[(i) - (S32(1))]))) + ((dsp.const170) * (rec34[(i) - (S32(2))])))) - ((dsp.const172) * (((dsp.const173) * (rec33[(i) - (S32(2))])) + ((dsp.const174) * (rec33[(i) - (S32(1))]))))
            vstore(dsp.rec33_perm, vload[w64](rec33_tmp, vsize))
            vstore(dsp.rec33_perm, vload[w64](rec33_tmp, vsize + hsize), hsize)
            vstore(rec32_tmp, vload[w64](dsp.rec32_perm))
            vstore(rec32_tmp, vload[w64](dsp.rec32_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec32[i] = ((slow8) * (rec32[(i) - (S32(1))])) + ((slow9) * (abs((dsp.const172) * ((((dsp.const176) * (rec33[i])) + ((dsp.const177) * (rec33[(i) - (S32(1))]))) + ((dsp.const176) * (rec33[(i) - (S32(2))]))))))
            vstore(dsp.rec32_perm, vload[w64](rec32_tmp, vsize))
            vstore(dsp.rec32_perm, vload[w64](rec32_tmp, vsize + hsize), hsize)
            vstore(rec45_tmp, vload[w64](dsp.rec45_perm))
            vstore(rec45_tmp, vload[w64](dsp.rec45_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec45[i] = (zec9[i]) - ((dsp.const178) * (((dsp.const179) * (rec45[(i) - (S32(2))])) + ((dsp.const180) * (rec45[(i) - (S32(1))]))))
            vstore(dsp.rec45_perm, vload[w64](rec45_tmp, vsize))
            vstore(dsp.rec45_perm, vload[w64](rec45_tmp, vsize + hsize), hsize)
            vstore(rec44_tmp, vload[w64](dsp.rec44_perm))
            vstore(rec44_tmp, vload[w64](dsp.rec44_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec44[i] = ((dsp.const178) * ((((dsp.const182) * (rec45[i])) + ((dsp.const183) * (rec45[(i) - (S32(1))]))) + ((dsp.const182) * (rec45[(i) - (S32(2))])))) - ((dsp.const184) * (((dsp.const185) * (rec44[(i) - (S32(2))])) + ((dsp.const186) * (rec44[(i) - (S32(1))]))))
            vstore(dsp.rec44_perm, vload[w64](rec44_tmp, vsize))
            vstore(dsp.rec44_perm, vload[w64](rec44_tmp, vsize + hsize), hsize)
            vstore(rec43_tmp, vload[w64](dsp.rec43_perm))
            vstore(rec43_tmp, vload[w64](dsp.rec43_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec43[i] = ((dsp.const184) * ((((dsp.const187) * (rec44[i])) + ((dsp.const188) * (rec44[(i) - (S32(1))]))) + ((dsp.const187) * (rec44[(i) - (S32(2))])))) - ((dsp.const189) * (((dsp.const190) * (rec43[(i) - (S32(2))])) + ((dsp.const191) * (rec43[(i) - (S32(1))]))))
            vstore(dsp.rec43_perm, vload[w64](rec43_tmp, vsize))
            vstore(dsp.rec43_perm, vload[w64](rec43_tmp, vsize + hsize), hsize)
            vstore(zec10, (dsp.const189) * ((((dsp.const192) * (vload[w64](rec43))) + ((dsp.const193) * (vload[w64](rec43, - S32(1))))) + ((dsp.const192) * (vload[w64](rec43, - S32(2))))))
            vstore(zec10, (dsp.const189) * ((((dsp.const192) * (vload[w64](rec43, hsize))) + ((dsp.const193) * (vload[w64](rec43, - S32(1) + hsize)))) + ((dsp.const192) * (vload[w64](rec43, - S32(2) + hsize)))), hsize)
            vstore(rec42_tmp, vload[w64](dsp.rec42_perm))
            vstore(rec42_tmp, vload[w64](dsp.rec42_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec42[i] = (zec10[i]) - ((dsp.const196) * (((dsp.const197) * (rec42[(i) - (S32(2))])) + ((dsp.const200) * (rec42[(i) - (S32(1))]))))
            vstore(dsp.rec42_perm, vload[w64](rec42_tmp, vsize))
            vstore(dsp.rec42_perm, vload[w64](rec42_tmp, vsize + hsize), hsize)
            vstore(rec41_tmp, vload[w64](dsp.rec41_perm))
            vstore(rec41_tmp, vload[w64](dsp.rec41_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec41[i] = ((dsp.const196) * ((((dsp.const202) * (rec42[i])) + ((dsp.const203) * (rec42[(i) - (S32(1))]))) + ((dsp.const202) * (rec42[(i) - (S32(2))])))) - ((dsp.const204) * (((dsp.const205) * (rec41[(i) - (S32(2))])) + ((dsp.const206) * (rec41[(i) - (S32(1))]))))
            vstore(dsp.rec41_perm, vload[w64](rec41_tmp, vsize))
            vstore(dsp.rec41_perm, vload[w64](rec41_tmp, vsize + hsize), hsize)
            vstore(rec40_tmp, vload[w64](dsp.rec40_perm))
            vstore(rec40_tmp, vload[w64](dsp.rec40_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec40[i] = ((dsp.const204) * ((((dsp.const208) * (rec41[i])) + ((dsp.const209) * (rec41[(i) - (S32(1))]))) + ((dsp.const208) * (rec41[(i) - (S32(2))])))) - ((dsp.const210) * (((dsp.const211) * (rec40[(i) - (S32(2))])) + ((dsp.const212) * (rec40[(i) - (S32(1))]))))
            vstore(dsp.rec40_perm, vload[w64](rec40_tmp, vsize))
            vstore(dsp.rec40_perm, vload[w64](rec40_tmp, vsize + hsize), hsize)
            vstore(rec39_tmp, vload[w64](dsp.rec39_perm))
            vstore(rec39_tmp, vload[w64](dsp.rec39_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec39[i] = ((slow8) * (rec39[(i) - (S32(1))])) + ((slow9) * (abs((dsp.const210) * ((((dsp.const214) * (rec40[i])) + ((dsp.const215) * (rec40[(i) - (S32(1))]))) + ((dsp.const214) * (rec40[(i) - (S32(2))]))))))
            vstore(dsp.rec39_perm, vload[w64](rec39_tmp, vsize))
            vstore(dsp.rec39_perm, vload[w64](rec39_tmp, vsize + hsize), hsize)
            vstore(rec52_tmp, vload[w64](dsp.rec52_perm))
            vstore(rec52_tmp, vload[w64](dsp.rec52_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec52[i] = (zec10[i]) - ((dsp.const216) * (((dsp.const217) * (rec52[(i) - (S32(2))])) + ((dsp.const218) * (rec52[(i) - (S32(1))]))))
            vstore(dsp.rec52_perm, vload[w64](rec52_tmp, vsize))
            vstore(dsp.rec52_perm, vload[w64](rec52_tmp, vsize + hsize), hsize)
            vstore(rec51_tmp, vload[w64](dsp.rec51_perm))
            vstore(rec51_tmp, vload[w64](dsp.rec51_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec51[i] = ((dsp.const216) * ((((dsp.const220) * (rec52[i])) + ((dsp.const221) * (rec52[(i) - (S32(1))]))) + ((dsp.const220) * (rec52[(i) - (S32(2))])))) - ((dsp.const222) * (((dsp.const223) * (rec51[(i) - (S32(2))])) + ((dsp.const224) * (rec51[(i) - (S32(1))]))))
            vstore(dsp.rec51_perm, vload[w64](rec51_tmp, vsize))
            vstore(dsp.rec51_perm, vload[w64](rec51_tmp, vsize + hsize), hsize)
            vstore(rec50_tmp, vload[w64](dsp.rec50_perm))
            vstore(rec50_tmp, vload[w64](dsp.rec50_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec50[i] = ((dsp.const222) * ((((dsp.const225) * (rec51[i])) + ((dsp.const226) * (rec51[(i) - (S32(1))]))) + ((dsp.const225) * (rec51[(i) - (S32(2))])))) - ((dsp.const227) * (((dsp.const228) * (rec50[(i) - (S32(2))])) + ((dsp.const229) * (rec50[(i) - (S32(1))]))))
            vstore(dsp.rec50_perm, vload[w64](rec50_tmp, vsize))
            vstore(dsp.rec50_perm, vload[w64](rec50_tmp, vsize + hsize), hsize)
            vstore(zec11, (dsp.const227) * ((((dsp.const230) * (vload[w64](rec50))) + ((dsp.const231) * (vload[w64](rec50, - S32(1))))) + ((dsp.const230) * (vload[w64](rec50, - S32(2))))))
            vstore(zec11, (dsp.const227) * ((((dsp.const230) * (vload[w64](rec50, hsize))) + ((dsp.const231) * (vload[w64](rec50, - S32(1) + hsize)))) + ((dsp.const230) * (vload[w64](rec50, - S32(2) + hsize)))), hsize)
            vstore(rec49_tmp, vload[w64](dsp.rec49_perm))
            vstore(rec49_tmp, vload[w64](dsp.rec49_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec49[i] = (zec11[i]) - ((dsp.const234) * (((dsp.const235) * (rec49[(i) - (S32(2))])) + ((dsp.const238) * (rec49[(i) - (S32(1))]))))
            vstore(dsp.rec49_perm, vload[w64](rec49_tmp, vsize))
            vstore(dsp.rec49_perm, vload[w64](rec49_tmp, vsize + hsize), hsize)
            vstore(rec48_tmp, vload[w64](dsp.rec48_perm))
            vstore(rec48_tmp, vload[w64](dsp.rec48_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec48[i] = ((dsp.const234) * ((((dsp.const240) * (rec49[i])) + ((dsp.const241) * (rec49[(i) - (S32(1))]))) + ((dsp.const240) * (rec49[(i) - (S32(2))])))) - ((dsp.const242) * (((dsp.const243) * (rec48[(i) - (S32(2))])) + ((dsp.const244) * (rec48[(i) - (S32(1))]))))
            vstore(dsp.rec48_perm, vload[w64](rec48_tmp, vsize))
            vstore(dsp.rec48_perm, vload[w64](rec48_tmp, vsize + hsize), hsize)
            vstore(rec47_tmp, vload[w64](dsp.rec47_perm))
            vstore(rec47_tmp, vload[w64](dsp.rec47_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec47[i] = ((dsp.const242) * ((((dsp.const246) * (rec48[i])) + ((dsp.const247) * (rec48[(i) - (S32(1))]))) + ((dsp.const246) * (rec48[(i) - (S32(2))])))) - ((dsp.const248) * (((dsp.const249) * (rec47[(i) - (S32(2))])) + ((dsp.const250) * (rec47[(i) - (S32(1))]))))
            vstore(dsp.rec47_perm, vload[w64](rec47_tmp, vsize))
            vstore(dsp.rec47_perm, vload[w64](rec47_tmp, vsize + hsize), hsize)
            vstore(rec46_tmp, vload[w64](dsp.rec46_perm))
            vstore(rec46_tmp, vload[w64](dsp.rec46_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec46[i] = ((slow8) * (rec46[(i) - (S32(1))])) + ((slow9) * (abs((dsp.const248) * ((((dsp.const252) * (rec47[i])) + ((dsp.const253) * (rec47[(i) - (S32(1))]))) + ((dsp.const252) * (rec47[(i) - (S32(2))]))))))
            vstore(dsp.rec46_perm, vload[w64](rec46_tmp, vsize))
            vstore(dsp.rec46_perm, vload[w64](rec46_tmp, vsize + hsize), hsize)
            vstore(rec59_tmp, vload[w64](dsp.rec59_perm))
            vstore(rec59_tmp, vload[w64](dsp.rec59_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec59[i] = (zec11[i]) - ((dsp.const254) * (((dsp.const255) * (rec59[(i) - (S32(2))])) + ((dsp.const256) * (rec59[(i) - (S32(1))]))))
            vstore(dsp.rec59_perm, vload[w64](rec59_tmp, vsize))
            vstore(dsp.rec59_perm, vload[w64](rec59_tmp, vsize + hsize), hsize)
            vstore(rec58_tmp, vload[w64](dsp.rec58_perm))
            vstore(rec58_tmp, vload[w64](dsp.rec58_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec58[i] = ((dsp.const254) * ((((dsp.const258) * (rec59[i])) + ((dsp.const259) * (rec59[(i) - (S32(1))]))) + ((dsp.const258) * (rec59[(i) - (S32(2))])))) - ((dsp.const260) * (((dsp.const261) * (rec58[(i) - (S32(2))])) + ((dsp.const262) * (rec58[(i) - (S32(1))]))))
            vstore(dsp.rec58_perm, vload[w64](rec58_tmp, vsize))
            vstore(dsp.rec58_perm, vload[w64](rec58_tmp, vsize + hsize), hsize)
            vstore(rec57_tmp, vload[w64](dsp.rec57_perm))
            vstore(rec57_tmp, vload[w64](dsp.rec57_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec57[i] = ((dsp.const260) * ((((dsp.const263) * (rec58[i])) + ((dsp.const264) * (rec58[(i) - (S32(1))]))) + ((dsp.const263) * (rec58[(i) - (S32(2))])))) - ((dsp.const265) * (((dsp.const266) * (rec57[(i) - (S32(2))])) + ((dsp.const267) * (rec57[(i) - (S32(1))]))))
            vstore(dsp.rec57_perm, vload[w64](rec57_tmp, vsize))
            vstore(dsp.rec57_perm, vload[w64](rec57_tmp, vsize + hsize), hsize)
            vstore(zec12, (dsp.const265) * ((((dsp.const268) * (vload[w64](rec57))) + ((dsp.const269) * (vload[w64](rec57, - S32(1))))) + ((dsp.const268) * (vload[w64](rec57, - S32(2))))))
            vstore(zec12, (dsp.const265) * ((((dsp.const268) * (vload[w64](rec57, hsize))) + ((dsp.const269) * (vload[w64](rec57, - S32(1) + hsize)))) + ((dsp.const268) * (vload[w64](rec57, - S32(2) + hsize)))), hsize)
            vstore(rec56_tmp, vload[w64](dsp.rec56_perm))
            vstore(rec56_tmp, vload[w64](dsp.rec56_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec56[i] = (zec12[i]) - ((dsp.const272) * (((dsp.const273) * (rec56[(i) - (S32(2))])) + ((dsp.const276) * (rec56[(i) - (S32(1))]))))
            vstore(dsp.rec56_perm, vload[w64](rec56_tmp, vsize))
            vstore(dsp.rec56_perm, vload[w64](rec56_tmp, vsize + hsize), hsize)
            vstore(rec55_tmp, vload[w64](dsp.rec55_perm))
            vstore(rec55_tmp, vload[w64](dsp.rec55_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec55[i] = ((dsp.const272) * ((((dsp.const278) * (rec56[i])) + ((dsp.const279) * (rec56[(i) - (S32(1))]))) + ((dsp.const278) * (rec56[(i) - (S32(2))])))) - ((dsp.const280) * (((dsp.const281) * (rec55[(i) - (S32(2))])) + ((dsp.const282) * (rec55[(i) - (S32(1))]))))
            vstore(dsp.rec55_perm, vload[w64](rec55_tmp, vsize))
            vstore(dsp.rec55_perm, vload[w64](rec55_tmp, vsize + hsize), hsize)
            vstore(rec54_tmp, vload[w64](dsp.rec54_perm))
            vstore(rec54_tmp, vload[w64](dsp.rec54_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec54[i] = ((dsp.const280) * ((((dsp.const284) * (rec55[i])) + ((dsp.const285) * (rec55[(i) - (S32(1))]))) + ((dsp.const284) * (rec55[(i) - (S32(2))])))) - ((dsp.const286) * (((dsp.const287) * (rec54[(i) - (S32(2))])) + ((dsp.const288) * (rec54[(i) - (S32(1))]))))
            vstore(dsp.rec54_perm, vload[w64](rec54_tmp, vsize))
            vstore(dsp.rec54_perm, vload[w64](rec54_tmp, vsize + hsize), hsize)
            vstore(rec53_tmp, vload[w64](dsp.rec53_perm))
            vstore(rec53_tmp, vload[w64](dsp.rec53_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec53[i] = ((slow8) * (rec53[(i) - (S32(1))])) + ((slow9) * (abs((dsp.const286) * ((((dsp.const290) * (rec54[i])) + ((dsp.const291) * (rec54[(i) - (S32(1))]))) + ((dsp.const290) * (rec54[(i) - (S32(2))]))))))
            vstore(dsp.rec53_perm, vload[w64](rec53_tmp, vsize))
            vstore(dsp.rec53_perm, vload[w64](rec53_tmp, vsize + hsize), hsize)
            vstore(rec66_tmp, vload[w64](dsp.rec66_perm))
            vstore(rec66_tmp, vload[w64](dsp.rec66_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec66[i] = (zec12[i]) - ((dsp.const292) * (((dsp.const293) * (rec66[(i) - (S32(2))])) + ((dsp.const294) * (rec66[(i) - (S32(1))]))))
            vstore(dsp.rec66_perm, vload[w64](rec66_tmp, vsize))
            vstore(dsp.rec66_perm, vload[w64](rec66_tmp, vsize + hsize), hsize)
            vstore(rec65_tmp, vload[w64](dsp.rec65_perm))
            vstore(rec65_tmp, vload[w64](dsp.rec65_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec65[i] = ((dsp.const292) * ((((dsp.const296) * (rec66[i])) + ((dsp.const297) * (rec66[(i) - (S32(1))]))) + ((dsp.const296) * (rec66[(i) - (S32(2))])))) - ((dsp.const298) * (((dsp.const299) * (rec65[(i) - (S32(2))])) + ((dsp.const300) * (rec65[(i) - (S32(1))]))))
            vstore(dsp.rec65_perm, vload[w64](rec65_tmp, vsize))
            vstore(dsp.rec65_perm, vload[w64](rec65_tmp, vsize + hsize), hsize)
            vstore(rec64_tmp, vload[w64](dsp.rec64_perm))
            vstore(rec64_tmp, vload[w64](dsp.rec64_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec64[i] = ((dsp.const298) * ((((dsp.const301) * (rec65[i])) + ((dsp.const302) * (rec65[(i) - (S32(1))]))) + ((dsp.const301) * (rec65[(i) - (S32(2))])))) - ((dsp.const303) * (((dsp.const304) * (rec64[(i) - (S32(2))])) + ((dsp.const305) * (rec64[(i) - (S32(1))]))))
            vstore(dsp.rec64_perm, vload[w64](rec64_tmp, vsize))
            vstore(dsp.rec64_perm, vload[w64](rec64_tmp, vsize + hsize), hsize)
            vstore(zec13, (dsp.const303) * ((((dsp.const306) * (vload[w64](rec64))) + ((dsp.const307) * (vload[w64](rec64, - S32(1))))) + ((dsp.const306) * (vload[w64](rec64, - S32(2))))))
            vstore(zec13, (dsp.const303) * ((((dsp.const306) * (vload[w64](rec64, hsize))) + ((dsp.const307) * (vload[w64](rec64, - S32(1) + hsize)))) + ((dsp.const306) * (vload[w64](rec64, - S32(2) + hsize)))), hsize)
            vstore(rec63_tmp, vload[w64](dsp.rec63_perm))
            vstore(rec63_tmp, vload[w64](dsp.rec63_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec63[i] = (zec13[i]) - ((dsp.const310) * (((dsp.const311) * (rec63[(i) - (S32(2))])) + ((dsp.const314) * (rec63[(i) - (S32(1))]))))
            vstore(dsp.rec63_perm, vload[w64](rec63_tmp, vsize))
            vstore(dsp.rec63_perm, vload[w64](rec63_tmp, vsize + hsize), hsize)
            vstore(rec62_tmp, vload[w64](dsp.rec62_perm))
            vstore(rec62_tmp, vload[w64](dsp.rec62_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec62[i] = ((dsp.const310) * ((((dsp.const316) * (rec63[i])) + ((dsp.const317) * (rec63[(i) - (S32(1))]))) + ((dsp.const316) * (rec63[(i) - (S32(2))])))) - ((dsp.const318) * (((dsp.const319) * (rec62[(i) - (S32(2))])) + ((dsp.const320) * (rec62[(i) - (S32(1))]))))
            vstore(dsp.rec62_perm, vload[w64](rec62_tmp, vsize))
            vstore(dsp.rec62_perm, vload[w64](rec62_tmp, vsize + hsize), hsize)
            vstore(rec61_tmp, vload[w64](dsp.rec61_perm))
            vstore(rec61_tmp, vload[w64](dsp.rec61_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec61[i] = ((dsp.const318) * ((((dsp.const322) * (rec62[i])) + ((dsp.const323) * (rec62[(i) - (S32(1))]))) + ((dsp.const322) * (rec62[(i) - (S32(2))])))) - ((dsp.const324) * (((dsp.const325) * (rec61[(i) - (S32(2))])) + ((dsp.const326) * (rec61[(i) - (S32(1))]))))
            vstore(dsp.rec61_perm, vload[w64](rec61_tmp, vsize))
            vstore(dsp.rec61_perm, vload[w64](rec61_tmp, vsize + hsize), hsize)
            vstore(rec60_tmp, vload[w64](dsp.rec60_perm))
            vstore(rec60_tmp, vload[w64](dsp.rec60_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec60[i] = ((slow8) * (rec60[(i) - (S32(1))])) + ((slow9) * (abs((dsp.const324) * ((((dsp.const328) * (rec61[i])) + ((dsp.const329) * (rec61[(i) - (S32(1))]))) + ((dsp.const328) * (rec61[(i) - (S32(2))]))))))
            vstore(dsp.rec60_perm, vload[w64](rec60_tmp, vsize))
            vstore(dsp.rec60_perm, vload[w64](rec60_tmp, vsize + hsize), hsize)
            vstore(rec73_tmp, vload[w64](dsp.rec73_perm))
            vstore(rec73_tmp, vload[w64](dsp.rec73_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec73[i] = (zec13[i]) - ((dsp.const330) * (((dsp.const331) * (rec73[(i) - (S32(2))])) + ((dsp.const332) * (rec73[(i) - (S32(1))]))))
            vstore(dsp.rec73_perm, vload[w64](rec73_tmp, vsize))
            vstore(dsp.rec73_perm, vload[w64](rec73_tmp, vsize + hsize), hsize)
            vstore(rec72_tmp, vload[w64](dsp.rec72_perm))
            vstore(rec72_tmp, vload[w64](dsp.rec72_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec72[i] = ((dsp.const330) * ((((dsp.const334) * (rec73[i])) + ((dsp.const335) * (rec73[(i) - (S32(1))]))) + ((dsp.const334) * (rec73[(i) - (S32(2))])))) - ((dsp.const336) * (((dsp.const337) * (rec72[(i) - (S32(2))])) + ((dsp.const338) * (rec72[(i) - (S32(1))]))))
            vstore(dsp.rec72_perm, vload[w64](rec72_tmp, vsize))
            vstore(dsp.rec72_perm, vload[w64](rec72_tmp, vsize + hsize), hsize)
            vstore(rec71_tmp, vload[w64](dsp.rec71_perm))
            vstore(rec71_tmp, vload[w64](dsp.rec71_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec71[i] = ((dsp.const336) * ((((dsp.const339) * (rec72[i])) + ((dsp.const340) * (rec72[(i) - (S32(1))]))) + ((dsp.const339) * (rec72[(i) - (S32(2))])))) - ((dsp.const341) * (((dsp.const342) * (rec71[(i) - (S32(2))])) + ((dsp.const343) * (rec71[(i) - (S32(1))]))))
            vstore(dsp.rec71_perm, vload[w64](rec71_tmp, vsize))
            vstore(dsp.rec71_perm, vload[w64](rec71_tmp, vsize + hsize), hsize)
            vstore(zec14, (dsp.const341) * ((((dsp.const344) * (vload[w64](rec71))) + ((dsp.const345) * (vload[w64](rec71, - S32(1))))) + ((dsp.const344) * (vload[w64](rec71, - S32(2))))))
            vstore(zec14, (dsp.const341) * ((((dsp.const344) * (vload[w64](rec71, hsize))) + ((dsp.const345) * (vload[w64](rec71, - S32(1) + hsize)))) + ((dsp.const344) * (vload[w64](rec71, - S32(2) + hsize)))), hsize)
            vstore(rec70_tmp, vload[w64](dsp.rec70_perm))
            vstore(rec70_tmp, vload[w64](dsp.rec70_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec70[i] = (zec14[i]) - ((dsp.const348) * (((dsp.const349) * (rec70[(i) - (S32(2))])) + ((dsp.const352) * (rec70[(i) - (S32(1))]))))
            vstore(dsp.rec70_perm, vload[w64](rec70_tmp, vsize))
            vstore(dsp.rec70_perm, vload[w64](rec70_tmp, vsize + hsize), hsize)
            vstore(rec69_tmp, vload[w64](dsp.rec69_perm))
            vstore(rec69_tmp, vload[w64](dsp.rec69_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec69[i] = ((dsp.const348) * ((((dsp.const354) * (rec70[i])) + ((dsp.const355) * (rec70[(i) - (S32(1))]))) + ((dsp.const354) * (rec70[(i) - (S32(2))])))) - ((dsp.const356) * (((dsp.const357) * (rec69[(i) - (S32(2))])) + ((dsp.const358) * (rec69[(i) - (S32(1))]))))
            vstore(dsp.rec69_perm, vload[w64](rec69_tmp, vsize))
            vstore(dsp.rec69_perm, vload[w64](rec69_tmp, vsize + hsize), hsize)
            vstore(rec68_tmp, vload[w64](dsp.rec68_perm))
            vstore(rec68_tmp, vload[w64](dsp.rec68_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec68[i] = ((dsp.const356) * ((((dsp.const360) * (rec69[i])) + ((dsp.const361) * (rec69[(i) - (S32(1))]))) + ((dsp.const360) * (rec69[(i) - (S32(2))])))) - ((dsp.const362) * (((dsp.const363) * (rec68[(i) - (S32(2))])) + ((dsp.const364) * (rec68[(i) - (S32(1))]))))
            vstore(dsp.rec68_perm, vload[w64](rec68_tmp, vsize))
            vstore(dsp.rec68_perm, vload[w64](rec68_tmp, vsize + hsize), hsize)
            vstore(rec67_tmp, vload[w64](dsp.rec67_perm))
            vstore(rec67_tmp, vload[w64](dsp.rec67_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec67[i] = ((slow8) * (rec67[(i) - (S32(1))])) + ((slow9) * (abs((dsp.const362) * ((((dsp.const366) * (rec68[i])) + ((dsp.const367) * (rec68[(i) - (S32(1))]))) + ((dsp.const366) * (rec68[(i) - (S32(2))]))))))
            vstore(dsp.rec67_perm, vload[w64](rec67_tmp, vsize))
            vstore(dsp.rec67_perm, vload[w64](rec67_tmp, vsize + hsize), hsize)
            vstore(rec80_tmp, vload[w64](dsp.rec80_perm))
            vstore(rec80_tmp, vload[w64](dsp.rec80_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec80[i] = (zec14[i]) - ((dsp.const368) * (((dsp.const369) * (rec80[(i) - (S32(2))])) + ((dsp.const370) * (rec80[(i) - (S32(1))]))))
            vstore(dsp.rec80_perm, vload[w64](rec80_tmp, vsize))
            vstore(dsp.rec80_perm, vload[w64](rec80_tmp, vsize + hsize), hsize)
            vstore(rec79_tmp, vload[w64](dsp.rec79_perm))
            vstore(rec79_tmp, vload[w64](dsp.rec79_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec79[i] = ((dsp.const368) * ((((dsp.const372) * (rec80[i])) + ((dsp.const373) * (rec80[(i) - (S32(1))]))) + ((dsp.const372) * (rec80[(i) - (S32(2))])))) - ((dsp.const374) * (((dsp.const375) * (rec79[(i) - (S32(2))])) + ((dsp.const376) * (rec79[(i) - (S32(1))]))))
            vstore(dsp.rec79_perm, vload[w64](rec79_tmp, vsize))
            vstore(dsp.rec79_perm, vload[w64](rec79_tmp, vsize + hsize), hsize)
            vstore(rec78_tmp, vload[w64](dsp.rec78_perm))
            vstore(rec78_tmp, vload[w64](dsp.rec78_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec78[i] = ((dsp.const374) * ((((dsp.const377) * (rec79[i])) + ((dsp.const378) * (rec79[(i) - (S32(1))]))) + ((dsp.const377) * (rec79[(i) - (S32(2))])))) - ((dsp.const379) * (((dsp.const380) * (rec78[(i) - (S32(2))])) + ((dsp.const381) * (rec78[(i) - (S32(1))]))))
            vstore(dsp.rec78_perm, vload[w64](rec78_tmp, vsize))
            vstore(dsp.rec78_perm, vload[w64](rec78_tmp, vsize + hsize), hsize)
            vstore(zec15, (dsp.const379) * ((((dsp.const382) * (vload[w64](rec78))) + ((dsp.const383) * (vload[w64](rec78, - S32(1))))) + ((dsp.const382) * (vload[w64](rec78, - S32(2))))))
            vstore(zec15, (dsp.const379) * ((((dsp.const382) * (vload[w64](rec78, hsize))) + ((dsp.const383) * (vload[w64](rec78, - S32(1) + hsize)))) + ((dsp.const382) * (vload[w64](rec78, - S32(2) + hsize)))), hsize)
            vstore(rec77_tmp, vload[w64](dsp.rec77_perm))
            vstore(rec77_tmp, vload[w64](dsp.rec77_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec77[i] = (zec15[i]) - ((dsp.const386) * (((dsp.const387) * (rec77[(i) - (S32(2))])) + ((dsp.const390) * (rec77[(i) - (S32(1))]))))
            vstore(dsp.rec77_perm, vload[w64](rec77_tmp, vsize))
            vstore(dsp.rec77_perm, vload[w64](rec77_tmp, vsize + hsize), hsize)
            vstore(rec76_tmp, vload[w64](dsp.rec76_perm))
            vstore(rec76_tmp, vload[w64](dsp.rec76_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec76[i] = ((dsp.const386) * ((((dsp.const392) * (rec77[i])) + ((dsp.const393) * (rec77[(i) - (S32(1))]))) + ((dsp.const392) * (rec77[(i) - (S32(2))])))) - ((dsp.const394) * (((dsp.const395) * (rec76[(i) - (S32(2))])) + ((dsp.const396) * (rec76[(i) - (S32(1))]))))
            vstore(dsp.rec76_perm, vload[w64](rec76_tmp, vsize))
            vstore(dsp.rec76_perm, vload[w64](rec76_tmp, vsize + hsize), hsize)
            vstore(rec75_tmp, vload[w64](dsp.rec75_perm))
            vstore(rec75_tmp, vload[w64](dsp.rec75_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec75[i] = ((dsp.const394) * ((((dsp.const398) * (rec76[i])) + ((dsp.const399) * (rec76[(i) - (S32(1))]))) + ((dsp.const398) * (rec76[(i) - (S32(2))])))) - ((dsp.const400) * (((dsp.const401) * (rec75[(i) - (S32(2))])) + ((dsp.const402) * (rec75[(i) - (S32(1))]))))
            vstore(dsp.rec75_perm, vload[w64](rec75_tmp, vsize))
            vstore(dsp.rec75_perm, vload[w64](rec75_tmp, vsize + hsize), hsize)
            vstore(rec74_tmp, vload[w64](dsp.rec74_perm))
            vstore(rec74_tmp, vload[w64](dsp.rec74_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec74[i] = ((slow8) * (rec74[(i) - (S32(1))])) + ((slow9) * (abs((dsp.const400) * ((((dsp.const404) * (rec75[i])) + ((dsp.const405) * (rec75[(i) - (S32(1))]))) + ((dsp.const404) * (rec75[(i) - (S32(2))]))))))
            vstore(dsp.rec74_perm, vload[w64](rec74_tmp, vsize))
            vstore(dsp.rec74_perm, vload[w64](rec74_tmp, vsize + hsize), hsize)
            vstore(rec87_tmp, vload[w64](dsp.rec87_perm))
            vstore(rec87_tmp, vload[w64](dsp.rec87_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec87[i] = (zec15[i]) - ((dsp.const406) * (((dsp.const407) * (rec87[(i) - (S32(2))])) + ((dsp.const408) * (rec87[(i) - (S32(1))]))))
            vstore(dsp.rec87_perm, vload[w64](rec87_tmp, vsize))
            vstore(dsp.rec87_perm, vload[w64](rec87_tmp, vsize + hsize), hsize)
            vstore(rec86_tmp, vload[w64](dsp.rec86_perm))
            vstore(rec86_tmp, vload[w64](dsp.rec86_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec86[i] = ((dsp.const406) * ((((dsp.const410) * (rec87[i])) + ((dsp.const411) * (rec87[(i) - (S32(1))]))) + ((dsp.const410) * (rec87[(i) - (S32(2))])))) - ((dsp.const412) * (((dsp.const413) * (rec86[(i) - (S32(2))])) + ((dsp.const414) * (rec86[(i) - (S32(1))]))))
            vstore(dsp.rec86_perm, vload[w64](rec86_tmp, vsize))
            vstore(dsp.rec86_perm, vload[w64](rec86_tmp, vsize + hsize), hsize)
            vstore(rec85_tmp, vload[w64](dsp.rec85_perm))
            vstore(rec85_tmp, vload[w64](dsp.rec85_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec85[i] = ((dsp.const412) * ((((dsp.const415) * (rec86[i])) + ((dsp.const416) * (rec86[(i) - (S32(1))]))) + ((dsp.const415) * (rec86[(i) - (S32(2))])))) - ((dsp.const417) * (((dsp.const418) * (rec85[(i) - (S32(2))])) + ((dsp.const419) * (rec85[(i) - (S32(1))]))))
            vstore(dsp.rec85_perm, vload[w64](rec85_tmp, vsize))
            vstore(dsp.rec85_perm, vload[w64](rec85_tmp, vsize + hsize), hsize)
            vstore(zec16, (dsp.const417) * ((((dsp.const420) * (vload[w64](rec85))) + ((dsp.const421) * (vload[w64](rec85, - S32(1))))) + ((dsp.const420) * (vload[w64](rec85, - S32(2))))))
            vstore(zec16, (dsp.const417) * ((((dsp.const420) * (vload[w64](rec85, hsize))) + ((dsp.const421) * (vload[w64](rec85, - S32(1) + hsize)))) + ((dsp.const420) * (vload[w64](rec85, - S32(2) + hsize)))), hsize)
            vstore(rec84_tmp, vload[w64](dsp.rec84_perm))
            vstore(rec84_tmp, vload[w64](dsp.rec84_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec84[i] = (zec16[i]) - ((dsp.const424) * (((dsp.const425) * (rec84[(i) - (S32(2))])) + ((dsp.const428) * (rec84[(i) - (S32(1))]))))
            vstore(dsp.rec84_perm, vload[w64](rec84_tmp, vsize))
            vstore(dsp.rec84_perm, vload[w64](rec84_tmp, vsize + hsize), hsize)
            vstore(rec83_tmp, vload[w64](dsp.rec83_perm))
            vstore(rec83_tmp, vload[w64](dsp.rec83_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec83[i] = ((dsp.const424) * ((((dsp.const430) * (rec84[i])) + ((dsp.const431) * (rec84[(i) - (S32(1))]))) + ((dsp.const430) * (rec84[(i) - (S32(2))])))) - ((dsp.const432) * (((dsp.const433) * (rec83[(i) - (S32(2))])) + ((dsp.const434) * (rec83[(i) - (S32(1))]))))
            vstore(dsp.rec83_perm, vload[w64](rec83_tmp, vsize))
            vstore(dsp.rec83_perm, vload[w64](rec83_tmp, vsize + hsize), hsize)
            vstore(rec82_tmp, vload[w64](dsp.rec82_perm))
            vstore(rec82_tmp, vload[w64](dsp.rec82_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec82[i] = ((dsp.const432) * ((((dsp.const436) * (rec83[i])) + ((dsp.const437) * (rec83[(i) - (S32(1))]))) + ((dsp.const436) * (rec83[(i) - (S32(2))])))) - ((dsp.const438) * (((dsp.const439) * (rec82[(i) - (S32(2))])) + ((dsp.const440) * (rec82[(i) - (S32(1))]))))
            vstore(dsp.rec82_perm, vload[w64](rec82_tmp, vsize))
            vstore(dsp.rec82_perm, vload[w64](rec82_tmp, vsize + hsize), hsize)
            vstore(rec81_tmp, vload[w64](dsp.rec81_perm))
            vstore(rec81_tmp, vload[w64](dsp.rec81_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec81[i] = ((slow8) * (rec81[(i) - (S32(1))])) + ((slow9) * (abs((dsp.const438) * ((((dsp.const442) * (rec82[i])) + ((dsp.const443) * (rec82[(i) - (S32(1))]))) + ((dsp.const442) * (rec82[(i) - (S32(2))]))))))
            vstore(dsp.rec81_perm, vload[w64](rec81_tmp, vsize))
            vstore(dsp.rec81_perm, vload[w64](rec81_tmp, vsize + hsize), hsize)
            vstore(rec94_tmp, vload[w64](dsp.rec94_perm))
            vstore(rec94_tmp, vload[w64](dsp.rec94_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec94[i] = (zec16[i]) - ((dsp.const444) * (((dsp.const445) * (rec94[(i) - (S32(2))])) + ((dsp.const446) * (rec94[(i) - (S32(1))]))))
            vstore(dsp.rec94_perm, vload[w64](rec94_tmp, vsize))
            vstore(dsp.rec94_perm, vload[w64](rec94_tmp, vsize + hsize), hsize)
            vstore(rec93_tmp, vload[w64](dsp.rec93_perm))
            vstore(rec93_tmp, vload[w64](dsp.rec93_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec93[i] = ((dsp.const444) * ((((dsp.const448) * (rec94[i])) + ((dsp.const449) * (rec94[(i) - (S32(1))]))) + ((dsp.const448) * (rec94[(i) - (S32(2))])))) - ((dsp.const450) * (((dsp.const451) * (rec93[(i) - (S32(2))])) + ((dsp.const452) * (rec93[(i) - (S32(1))]))))
            vstore(dsp.rec93_perm, vload[w64](rec93_tmp, vsize))
            vstore(dsp.rec93_perm, vload[w64](rec93_tmp, vsize + hsize), hsize)
            vstore(rec92_tmp, vload[w64](dsp.rec92_perm))
            vstore(rec92_tmp, vload[w64](dsp.rec92_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec92[i] = ((dsp.const450) * ((((dsp.const453) * (rec93[i])) + ((dsp.const454) * (rec93[(i) - (S32(1))]))) + ((dsp.const453) * (rec93[(i) - (S32(2))])))) - ((dsp.const455) * (((dsp.const456) * (rec92[(i) - (S32(2))])) + ((dsp.const457) * (rec92[(i) - (S32(1))]))))
            vstore(dsp.rec92_perm, vload[w64](rec92_tmp, vsize))
            vstore(dsp.rec92_perm, vload[w64](rec92_tmp, vsize + hsize), hsize)
            vstore(zec17, (dsp.const455) * ((((dsp.const458) * (vload[w64](rec92))) + ((dsp.const459) * (vload[w64](rec92, - S32(1))))) + ((dsp.const458) * (vload[w64](rec92, - S32(2))))))
            vstore(zec17, (dsp.const455) * ((((dsp.const458) * (vload[w64](rec92, hsize))) + ((dsp.const459) * (vload[w64](rec92, - S32(1) + hsize)))) + ((dsp.const458) * (vload[w64](rec92, - S32(2) + hsize)))), hsize)
            vstore(rec91_tmp, vload[w64](dsp.rec91_perm))
            vstore(rec91_tmp, vload[w64](dsp.rec91_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec91[i] = (zec17[i]) - ((dsp.const462) * (((dsp.const463) * (rec91[(i) - (S32(2))])) + ((dsp.const466) * (rec91[(i) - (S32(1))]))))
            vstore(dsp.rec91_perm, vload[w64](rec91_tmp, vsize))
            vstore(dsp.rec91_perm, vload[w64](rec91_tmp, vsize + hsize), hsize)
            vstore(rec90_tmp, vload[w64](dsp.rec90_perm))
            vstore(rec90_tmp, vload[w64](dsp.rec90_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec90[i] = ((dsp.const462) * ((((dsp.const468) * (rec91[i])) + ((dsp.const469) * (rec91[(i) - (S32(1))]))) + ((dsp.const468) * (rec91[(i) - (S32(2))])))) - ((dsp.const470) * (((dsp.const471) * (rec90[(i) - (S32(2))])) + ((dsp.const472) * (rec90[(i) - (S32(1))]))))
            vstore(dsp.rec90_perm, vload[w64](rec90_tmp, vsize))
            vstore(dsp.rec90_perm, vload[w64](rec90_tmp, vsize + hsize), hsize)
            vstore(rec89_tmp, vload[w64](dsp.rec89_perm))
            vstore(rec89_tmp, vload[w64](dsp.rec89_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec89[i] = ((dsp.const470) * ((((dsp.const474) * (rec90[i])) + ((dsp.const475) * (rec90[(i) - (S32(1))]))) + ((dsp.const474) * (rec90[(i) - (S32(2))])))) - ((dsp.const476) * (((dsp.const477) * (rec89[(i) - (S32(2))])) + ((dsp.const478) * (rec89[(i) - (S32(1))]))))
            vstore(dsp.rec89_perm, vload[w64](rec89_tmp, vsize))
            vstore(dsp.rec89_perm, vload[w64](rec89_tmp, vsize + hsize), hsize)
            vstore(rec88_tmp, vload[w64](dsp.rec88_perm))
            vstore(rec88_tmp, vload[w64](dsp.rec88_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec88[i] = ((slow8) * (rec88[(i) - (S32(1))])) + ((slow9) * (abs((dsp.const476) * ((((dsp.const480) * (rec89[i])) + ((dsp.const481) * (rec89[(i) - (S32(1))]))) + ((dsp.const480) * (rec89[(i) - (S32(2))]))))))
            vstore(dsp.rec88_perm, vload[w64](rec88_tmp, vsize))
            vstore(dsp.rec88_perm, vload[w64](rec88_tmp, vsize + hsize), hsize)
            vstore(rec101_tmp, vload[w64](dsp.rec101_perm))
            vstore(rec101_tmp, vload[w64](dsp.rec101_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec101[i] = (zec17[i]) - ((dsp.const482) * (((dsp.const483) * (rec101[(i) - (S32(2))])) + ((dsp.const484) * (rec101[(i) - (S32(1))]))))
            vstore(dsp.rec101_perm, vload[w64](rec101_tmp, vsize))
            vstore(dsp.rec101_perm, vload[w64](rec101_tmp, vsize + hsize), hsize)
            vstore(rec100_tmp, vload[w64](dsp.rec100_perm))
            vstore(rec100_tmp, vload[w64](dsp.rec100_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec100[i] = ((dsp.const482) * ((((dsp.const486) * (rec101[i])) + ((dsp.const487) * (rec101[(i) - (S32(1))]))) + ((dsp.const486) * (rec101[(i) - (S32(2))])))) - ((dsp.const488) * (((dsp.const489) * (rec100[(i) - (S32(2))])) + ((dsp.const490) * (rec100[(i) - (S32(1))]))))
            vstore(dsp.rec100_perm, vload[w64](rec100_tmp, vsize))
            vstore(dsp.rec100_perm, vload[w64](rec100_tmp, vsize + hsize), hsize)
            vstore(rec99_tmp, vload[w64](dsp.rec99_perm))
            vstore(rec99_tmp, vload[w64](dsp.rec99_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec99[i] = ((dsp.const488) * ((((dsp.const491) * (rec100[i])) + ((dsp.const492) * (rec100[(i) - (S32(1))]))) + ((dsp.const491) * (rec100[(i) - (S32(2))])))) - ((dsp.const493) * (((dsp.const494) * (rec99[(i) - (S32(2))])) + ((dsp.const495) * (rec99[(i) - (S32(1))]))))
            vstore(dsp.rec99_perm, vload[w64](rec99_tmp, vsize))
            vstore(dsp.rec99_perm, vload[w64](rec99_tmp, vsize + hsize), hsize)
            vstore(zec18, (dsp.const493) * ((((dsp.const496) * (vload[w64](rec99))) + ((dsp.const497) * (vload[w64](rec99, - S32(1))))) + ((dsp.const496) * (vload[w64](rec99, - S32(2))))))
            vstore(zec18, (dsp.const493) * ((((dsp.const496) * (vload[w64](rec99, hsize))) + ((dsp.const497) * (vload[w64](rec99, - S32(1) + hsize)))) + ((dsp.const496) * (vload[w64](rec99, - S32(2) + hsize)))), hsize)
            vstore(rec98_tmp, vload[w64](dsp.rec98_perm))
            vstore(rec98_tmp, vload[w64](dsp.rec98_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec98[i] = (zec18[i]) - ((dsp.const500) * (((dsp.const501) * (rec98[(i) - (S32(2))])) + ((dsp.const504) * (rec98[(i) - (S32(1))]))))
            vstore(dsp.rec98_perm, vload[w64](rec98_tmp, vsize))
            vstore(dsp.rec98_perm, vload[w64](rec98_tmp, vsize + hsize), hsize)
            vstore(rec97_tmp, vload[w64](dsp.rec97_perm))
            vstore(rec97_tmp, vload[w64](dsp.rec97_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec97[i] = ((dsp.const500) * ((((dsp.const506) * (rec98[i])) + ((dsp.const507) * (rec98[(i) - (S32(1))]))) + ((dsp.const506) * (rec98[(i) - (S32(2))])))) - ((dsp.const508) * (((dsp.const509) * (rec97[(i) - (S32(2))])) + ((dsp.const510) * (rec97[(i) - (S32(1))]))))
            vstore(dsp.rec97_perm, vload[w64](rec97_tmp, vsize))
            vstore(dsp.rec97_perm, vload[w64](rec97_tmp, vsize + hsize), hsize)
            vstore(rec96_tmp, vload[w64](dsp.rec96_perm))
            vstore(rec96_tmp, vload[w64](dsp.rec96_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec96[i] = ((dsp.const508) * ((((dsp.const512) * (rec97[i])) + ((dsp.const513) * (rec97[(i) - (S32(1))]))) + ((dsp.const512) * (rec97[(i) - (S32(2))])))) - ((dsp.const514) * (((dsp.const515) * (rec96[(i) - (S32(2))])) + ((dsp.const516) * (rec96[(i) - (S32(1))]))))
            vstore(dsp.rec96_perm, vload[w64](rec96_tmp, vsize))
            vstore(dsp.rec96_perm, vload[w64](rec96_tmp, vsize + hsize), hsize)
            vstore(rec95_tmp, vload[w64](dsp.rec95_perm))
            vstore(rec95_tmp, vload[w64](dsp.rec95_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec95[i] = ((slow8) * (rec95[(i) - (S32(1))])) + ((slow9) * (abs((dsp.const514) * ((((dsp.const518) * (rec96[i])) + ((dsp.const519) * (rec96[(i) - (S32(1))]))) + ((dsp.const518) * (rec96[(i) - (S32(2))]))))))
            vstore(dsp.rec95_perm, vload[w64](rec95_tmp, vsize))
            vstore(dsp.rec95_perm, vload[w64](rec95_tmp, vsize + hsize), hsize)
            vstore(rec105_tmp, vload[w64](dsp.rec105_perm))
            vstore(rec105_tmp, vload[w64](dsp.rec105_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec105[i] = (zec18[i]) - ((dsp.const520) * (((dsp.const521) * (rec105[(i) - (S32(2))])) + ((dsp.const522) * (rec105[(i) - (S32(1))]))))
            vstore(dsp.rec105_perm, vload[w64](rec105_tmp, vsize))
            vstore(dsp.rec105_perm, vload[w64](rec105_tmp, vsize + hsize), hsize)
            vstore(rec104_tmp, vload[w64](dsp.rec104_perm))
            vstore(rec104_tmp, vload[w64](dsp.rec104_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec104[i] = ((dsp.const520) * ((((dsp.const524) * (rec105[i])) + ((dsp.const525) * (rec105[(i) - (S32(1))]))) + ((dsp.const524) * (rec105[(i) - (S32(2))])))) - ((dsp.const526) * (((dsp.const527) * (rec104[(i) - (S32(2))])) + ((dsp.const528) * (rec104[(i) - (S32(1))]))))
            vstore(dsp.rec104_perm, vload[w64](rec104_tmp, vsize))
            vstore(dsp.rec104_perm, vload[w64](rec104_tmp, vsize + hsize), hsize)
            vstore(rec103_tmp, vload[w64](dsp.rec103_perm))
            vstore(rec103_tmp, vload[w64](dsp.rec103_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec103[i] = ((dsp.const526) * ((((dsp.const529) * (rec104[i])) + ((dsp.const530) * (rec104[(i) - (S32(1))]))) + ((dsp.const529) * (rec104[(i) - (S32(2))])))) - ((dsp.const531) * (((dsp.const532) * (rec103[(i) - (S32(2))])) + ((dsp.const533) * (rec103[(i) - (S32(1))]))))
            vstore(dsp.rec103_perm, vload[w64](rec103_tmp, vsize))
            vstore(dsp.rec103_perm, vload[w64](rec103_tmp, vsize + hsize), hsize)
            vstore(rec102_tmp, vload[w64](dsp.rec102_perm))
            vstore(rec102_tmp, vload[w64](dsp.rec102_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec102[i] = ((slow8) * (rec102[(i) - (S32(1))])) + ((slow9) * (abs((dsp.const531) * ((((dsp.const534) * (rec103[i])) + ((dsp.const535) * (rec103[(i) - (S32(1))]))) + ((dsp.const534) * (rec103[(i) - (S32(2))]))))))
            vstore(dsp.rec102_perm, vload[w64](rec102_tmp, vsize))
            vstore(dsp.rec102_perm, vload[w64](rec102_tmp, vsize + hsize), hsize)
            comptime for i in range(S32(0), vsize):
                dsp.vbargraph0 = FaustFloat((slow10) + ((2e+01) * (log10(rec7[i]))))
                dsp.vbargraph1 = FaustFloat((slow10) + ((2e+01) * (log10(rec11[i]))))
                dsp.vbargraph2 = FaustFloat((slow10) + ((2e+01) * (log10(rec18[i]))))
                dsp.vbargraph3 = FaustFloat((slow10) + ((2e+01) * (log10(rec25[i]))))
                dsp.vbargraph4 = FaustFloat((slow10) + ((2e+01) * (log10(rec32[i]))))
                dsp.vbargraph5 = FaustFloat((slow10) + ((2e+01) * (log10(rec39[i]))))
                dsp.vbargraph6 = FaustFloat((slow10) + ((2e+01) * (log10(rec46[i]))))
                dsp.vbargraph7 = FaustFloat((slow10) + ((2e+01) * (log10(rec53[i]))))
                dsp.vbargraph8 = FaustFloat((slow10) + ((2e+01) * (log10(rec60[i]))))
                dsp.vbargraph9 = FaustFloat((slow10) + ((2e+01) * (log10(rec67[i]))))
                dsp.vbargraph10 = FaustFloat((slow10) + ((2e+01) * (log10(rec74[i]))))
                dsp.vbargraph11 = FaustFloat((slow10) + ((2e+01) * (log10(rec81[i]))))
                dsp.vbargraph12 = FaustFloat((slow10) + ((2e+01) * (log10(rec88[i]))))
                dsp.vbargraph13 = FaustFloat((slow10) + ((2e+01) * (log10(rec95[i]))))
                dsp.vbargraph14 = FaustFloat((slow10) + ((2e+01) * (log10(rec102[i]))))
            vstore(zec19, vload[w64](zec5))
            vstore(zec19, vload[w64](zec5, hsize), hsize)
            lo = (vload[w64](zec19)).cast[dfaust]()
            hi = (vload[w64](zec19, hsize)).cast[dfaust]()
            vstore(output0, lo.join(hi))
            lo = (vload[w64](zec19)).cast[dfaust]()
            hi = (vload[w64](zec19, hsize)).cast[dfaust]()
            vstore(output1, lo.join(hi))
            vindex += vsize

# ==============================================================================
# Faust generated DSP code end.
# ==============================================================================
# Second section of architecture provided code start.
# Defines the main entry point of the application, initializes the dsp object
# and the user interface, allocates the buffers and runs the benchmark.
# ==============================================================================

def main() raises -> None:
    var dsp = alloc[mydsp](1)
    dsp[] = mydsp()
    dsp[].init(SAMP_RATE)

    var n_ins = dsp[].get_num_inputs()
    var n_outs = dsp[].get_num_outputs()

    var base, err = make_streams[dfaust](BUFF_SIZE, n_ins, n_outs)
    if err:
        print("Panic in main - Critical allocation error: ", err)
        dsp.free()
        return

    var inputs = base.unsafe_value().bitcast[Ptr[FaustFloat, MUT_NOTRK]]()
    var outputs = inputs + n_ins

    comptime if FILL_INPUTS:
        fill_inputs(inputs, n_ins)

    warmup(dsp[], inputs, outputs)
    var report = measure(dsp[], inputs, outputs)
    report.checksum = checksum_outputs(outputs, n_outs)
    print_report(report) # the output will be redirected via script

    comptime if WRITE_CSV:
        write_csv(report)

    free_streams[dfaust](base)
    dsp.free()

# ==============================================================================
# Second section of architecture provided code end.
# ==============================================================================
