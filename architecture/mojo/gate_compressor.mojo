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
# Code generated with Faust 2.85.5 (https://faust.grame.fr)
# name: "gate_compressor"
# Compilation options: 
#   -a impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 
#   -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs
# ==============================================================================

comptime dreal = f64
comptime wreal = simd_width_of[dreal]()
comptime Real = Scalar[dreal]
comptime RVec = SIMD[dreal, simd_width_of[dreal]()]

@fieldwise_init
struct mydsp(FaustDsp):
    var null_val: FaustFloat
    var vslider0: FaustFloat
    var rec4_perm: Arr[F64, 4]
    var vslider1: FaustFloat
    var sample_rate: S32
    var const0: F64
    var const1: F64
    var vslider2: FaustFloat
    var rec6_perm: Arr[F64, 4]
    var rec5_perm: Arr[F64, 4]
    var vslider3: FaustFloat
    var rec7_perm: Arr[F64, 4]
    var vslider4: FaustFloat
    var rec8_perm: Arr[F64, 4]
    var i_rec9_perm: Arr[S32, 4]
    var rec10_perm: Arr[F64, 4]
    var hslider0: FaustFloat
    var hslider1: FaustFloat
    var checkbox0: FaustFloat
    var checkbox1: FaustFloat
    var checkbox2: FaustFloat
    var entry0: FaustFloat
    var i_vec0_perm: Arr[S32, 4]
    var const2: F64
    var yec0_perm: Arr[F64, 4]
    var const3: F64
    var yec1_perm: Arr[F64, 4]
    var yec2_perm: Arr[F64, 4]
    var const4: F64
    var yec3_perm: Arr[F64, 4]
    var yec4_perm: Arr[F64, 4]
    var yec5_perm: Arr[F64, 4]
    var yec6_perm: Arr[F64, 4]
    var yec7_perm: Arr[F64, 4]
    var yec8_perm: Arr[F64, 4]
    var yec9_perm: Arr[F64, 4]
    var yec10_perm: Arr[F64, 4]
    var yec11_perm: Arr[F64, 4]
    var yec12_perm: Arr[F64, 4]
    var yec13_perm: Arr[F64, 4]
    var yec14_perm: Arr[F64, 4]
    var yec15_perm: Arr[F64, 4]
    var yec16_perm: Arr[F64, 4]
    var yec17_perm: Arr[F64, 4]
    var checkbox3: FaustFloat
    var rec14_perm: Arr[F64, 4]
    var hslider2: FaustFloat
    var hslider3: FaustFloat
    var i_yec18_perm: Arr[S32, 4]
    var i_rec15_perm: Arr[S32, 4]
    var rec12_perm: Arr[F64, 4]
    var rec11_perm: Arr[F64, 4]
    var hbargraph0: FaustFloat
    var rec3_perm: Arr[F64, 4]
    var i_yec19_perm: Arr[S32, 4]
    var i_rec16_perm: Arr[S32, 4]
    var rec1_perm: Arr[F64, 4]
    var rec0_perm: Arr[F64, 4]
    var checkbox4: FaustFloat
    var hslider4: FaustFloat
    var hslider5: FaustFloat
    var rec19_perm: Arr[F64, 4]
    var rec18_perm: Arr[F64, 4]
    var const5: F64
    var hslider6: FaustFloat
    var hslider7: FaustFloat
    var rec17_perm: Arr[F64, 4]
    var rec22_perm: Arr[F64, 4]
    var rec21_perm: Arr[F64, 4]
    var rec20_perm: Arr[F64, 4]
    var hslider8: FaustFloat
    var hbargraph1: FaustFloat
    var const6: F64
    var const7: F64
    var const8: F64
    var const9: F64
    var const10: F64
    var const11: F64
    var const12: F64
    var rec26_perm: Arr[F64, 4]
    var const13: F64
    var const14: F64
    var const15: F64
    var const16: F64
    var const17: F64
    var const18: F64
    var rec25_perm: Arr[F64, 4]
    var const19: F64
    var const20: F64
    var const21: F64
    var const22: F64
    var const23: F64
    var const24: F64
    var rec24_perm: Arr[F64, 4]
    var hslider9: FaustFloat
    var const25: F64
    var const26: F64
    var const27: F64
    var const28: F64
    var rec23_perm: Arr[F64, 4]
    var const29: F64
    var const30: F64
    var const31: F64
    var rec33_perm: Arr[F64, 4]
    var const32: F64
    var const33: F64
    var const34: F64
    var const35: F64
    var const36: F64
    var const37: F64
    var rec32_perm: Arr[F64, 4]
    var const38: F64
    var const39: F64
    var const40: F64
    var const41: F64
    var const42: F64
    var rec31_perm: Arr[F64, 4]
    var const43: F64
    var const44: F64
    var const45: F64
    var const46: F64
    var const47: F64
    var const48: F64
    var const49: F64
    var const50: F64
    var const51: F64
    var rec30_perm: Arr[F64, 4]
    var const52: F64
    var const53: F64
    var const54: F64
    var const55: F64
    var const56: F64
    var const57: F64
    var rec29_perm: Arr[F64, 4]
    var const58: F64
    var const59: F64
    var const60: F64
    var const61: F64
    var const62: F64
    var const63: F64
    var rec28_perm: Arr[F64, 4]
    var const64: F64
    var const65: F64
    var const66: F64
    var rec27_perm: Arr[F64, 4]
    var const67: F64
    var const68: F64
    var const69: F64
    var rec40_perm: Arr[F64, 4]
    var const70: F64
    var const71: F64
    var const72: F64
    var const73: F64
    var const74: F64
    var const75: F64
    var rec39_perm: Arr[F64, 4]
    var const76: F64
    var const77: F64
    var const78: F64
    var const79: F64
    var const80: F64
    var rec38_perm: Arr[F64, 4]
    var const81: F64
    var const82: F64
    var const83: F64
    var const84: F64
    var const85: F64
    var const86: F64
    var const87: F64
    var const88: F64
    var const89: F64
    var rec37_perm: Arr[F64, 4]
    var const90: F64
    var const91: F64
    var const92: F64
    var const93: F64
    var const94: F64
    var const95: F64
    var rec36_perm: Arr[F64, 4]
    var const96: F64
    var const97: F64
    var const98: F64
    var const99: F64
    var const100: F64
    var const101: F64
    var rec35_perm: Arr[F64, 4]
    var const102: F64
    var const103: F64
    var const104: F64
    var rec34_perm: Arr[F64, 4]
    var const105: F64
    var const106: F64
    var const107: F64
    var rec47_perm: Arr[F64, 4]
    var const108: F64
    var const109: F64
    var const110: F64
    var const111: F64
    var const112: F64
    var const113: F64
    var rec46_perm: Arr[F64, 4]
    var const114: F64
    var const115: F64
    var const116: F64
    var const117: F64
    var const118: F64
    var rec45_perm: Arr[F64, 4]
    var const119: F64
    var const120: F64
    var const121: F64
    var const122: F64
    var const123: F64
    var const124: F64
    var const125: F64
    var const126: F64
    var const127: F64
    var rec44_perm: Arr[F64, 4]
    var const128: F64
    var const129: F64
    var const130: F64
    var const131: F64
    var const132: F64
    var const133: F64
    var rec43_perm: Arr[F64, 4]
    var const134: F64
    var const135: F64
    var const136: F64
    var const137: F64
    var const138: F64
    var const139: F64
    var rec42_perm: Arr[F64, 4]
    var const140: F64
    var const141: F64
    var const142: F64
    var rec41_perm: Arr[F64, 4]
    var const143: F64
    var const144: F64
    var const145: F64
    var rec54_perm: Arr[F64, 4]
    var const146: F64
    var const147: F64
    var const148: F64
    var const149: F64
    var const150: F64
    var const151: F64
    var rec53_perm: Arr[F64, 4]
    var const152: F64
    var const153: F64
    var const154: F64
    var const155: F64
    var const156: F64
    var rec52_perm: Arr[F64, 4]
    var const157: F64
    var const158: F64
    var const159: F64
    var const160: F64
    var const161: F64
    var const162: F64
    var const163: F64
    var const164: F64
    var const165: F64
    var rec51_perm: Arr[F64, 4]
    var const166: F64
    var const167: F64
    var const168: F64
    var const169: F64
    var const170: F64
    var const171: F64
    var rec50_perm: Arr[F64, 4]
    var const172: F64
    var const173: F64
    var const174: F64
    var const175: F64
    var const176: F64
    var const177: F64
    var rec49_perm: Arr[F64, 4]
    var const178: F64
    var const179: F64
    var const180: F64
    var rec48_perm: Arr[F64, 4]
    var const181: F64
    var const182: F64
    var const183: F64
    var rec61_perm: Arr[F64, 4]
    var const184: F64
    var const185: F64
    var const186: F64
    var const187: F64
    var const188: F64
    var const189: F64
    var rec60_perm: Arr[F64, 4]
    var const190: F64
    var const191: F64
    var const192: F64
    var const193: F64
    var const194: F64
    var rec59_perm: Arr[F64, 4]
    var const195: F64
    var const196: F64
    var const197: F64
    var const198: F64
    var const199: F64
    var const200: F64
    var const201: F64
    var const202: F64
    var const203: F64
    var rec58_perm: Arr[F64, 4]
    var const204: F64
    var const205: F64
    var const206: F64
    var const207: F64
    var const208: F64
    var const209: F64
    var rec57_perm: Arr[F64, 4]
    var const210: F64
    var const211: F64
    var const212: F64
    var const213: F64
    var const214: F64
    var const215: F64
    var rec56_perm: Arr[F64, 4]
    var const216: F64
    var const217: F64
    var const218: F64
    var rec55_perm: Arr[F64, 4]
    var const219: F64
    var const220: F64
    var const221: F64
    var rec68_perm: Arr[F64, 4]
    var const222: F64
    var const223: F64
    var const224: F64
    var const225: F64
    var const226: F64
    var const227: F64
    var rec67_perm: Arr[F64, 4]
    var const228: F64
    var const229: F64
    var const230: F64
    var const231: F64
    var const232: F64
    var rec66_perm: Arr[F64, 4]
    var const233: F64
    var const234: F64
    var const235: F64
    var const236: F64
    var const237: F64
    var const238: F64
    var const239: F64
    var const240: F64
    var const241: F64
    var rec65_perm: Arr[F64, 4]
    var const242: F64
    var const243: F64
    var const244: F64
    var const245: F64
    var const246: F64
    var const247: F64
    var rec64_perm: Arr[F64, 4]
    var const248: F64
    var const249: F64
    var const250: F64
    var const251: F64
    var const252: F64
    var const253: F64
    var rec63_perm: Arr[F64, 4]
    var const254: F64
    var const255: F64
    var const256: F64
    var rec62_perm: Arr[F64, 4]
    var const257: F64
    var const258: F64
    var const259: F64
    var rec75_perm: Arr[F64, 4]
    var const260: F64
    var const261: F64
    var const262: F64
    var const263: F64
    var const264: F64
    var const265: F64
    var rec74_perm: Arr[F64, 4]
    var const266: F64
    var const267: F64
    var const268: F64
    var const269: F64
    var const270: F64
    var rec73_perm: Arr[F64, 4]
    var const271: F64
    var const272: F64
    var const273: F64
    var const274: F64
    var const275: F64
    var const276: F64
    var const277: F64
    var const278: F64
    var const279: F64
    var rec72_perm: Arr[F64, 4]
    var const280: F64
    var const281: F64
    var const282: F64
    var const283: F64
    var const284: F64
    var const285: F64
    var rec71_perm: Arr[F64, 4]
    var const286: F64
    var const287: F64
    var const288: F64
    var const289: F64
    var const290: F64
    var const291: F64
    var rec70_perm: Arr[F64, 4]
    var const292: F64
    var const293: F64
    var const294: F64
    var rec69_perm: Arr[F64, 4]
    var const295: F64
    var const296: F64
    var const297: F64
    var rec82_perm: Arr[F64, 4]
    var const298: F64
    var const299: F64
    var const300: F64
    var const301: F64
    var const302: F64
    var const303: F64
    var rec81_perm: Arr[F64, 4]
    var const304: F64
    var const305: F64
    var const306: F64
    var const307: F64
    var const308: F64
    var rec80_perm: Arr[F64, 4]
    var const309: F64
    var const310: F64
    var const311: F64
    var const312: F64
    var const313: F64
    var const314: F64
    var const315: F64
    var const316: F64
    var const317: F64
    var rec79_perm: Arr[F64, 4]
    var const318: F64
    var const319: F64
    var const320: F64
    var const321: F64
    var const322: F64
    var const323: F64
    var rec78_perm: Arr[F64, 4]
    var const324: F64
    var const325: F64
    var const326: F64
    var const327: F64
    var const328: F64
    var const329: F64
    var rec77_perm: Arr[F64, 4]
    var const330: F64
    var const331: F64
    var const332: F64
    var rec76_perm: Arr[F64, 4]
    var const333: F64
    var const334: F64
    var const335: F64
    var rec89_perm: Arr[F64, 4]
    var const336: F64
    var const337: F64
    var const338: F64
    var const339: F64
    var const340: F64
    var const341: F64
    var rec88_perm: Arr[F64, 4]
    var const342: F64
    var const343: F64
    var const344: F64
    var const345: F64
    var const346: F64
    var rec87_perm: Arr[F64, 4]
    var const347: F64
    var const348: F64
    var const349: F64
    var const350: F64
    var const351: F64
    var const352: F64
    var const353: F64
    var const354: F64
    var const355: F64
    var rec86_perm: Arr[F64, 4]
    var const356: F64
    var const357: F64
    var const358: F64
    var const359: F64
    var const360: F64
    var const361: F64
    var rec85_perm: Arr[F64, 4]
    var const362: F64
    var const363: F64
    var const364: F64
    var const365: F64
    var const366: F64
    var const367: F64
    var rec84_perm: Arr[F64, 4]
    var const368: F64
    var const369: F64
    var const370: F64
    var rec83_perm: Arr[F64, 4]
    var const371: F64
    var const372: F64
    var const373: F64
    var rec96_perm: Arr[F64, 4]
    var const374: F64
    var const375: F64
    var const376: F64
    var const377: F64
    var const378: F64
    var const379: F64
    var rec95_perm: Arr[F64, 4]
    var const380: F64
    var const381: F64
    var const382: F64
    var const383: F64
    var const384: F64
    var rec94_perm: Arr[F64, 4]
    var const385: F64
    var const386: F64
    var const387: F64
    var const388: F64
    var const389: F64
    var const390: F64
    var const391: F64
    var const392: F64
    var const393: F64
    var rec93_perm: Arr[F64, 4]
    var const394: F64
    var const395: F64
    var const396: F64
    var const397: F64
    var const398: F64
    var const399: F64
    var rec92_perm: Arr[F64, 4]
    var const400: F64
    var const401: F64
    var const402: F64
    var const403: F64
    var const404: F64
    var const405: F64
    var rec91_perm: Arr[F64, 4]
    var const406: F64
    var const407: F64
    var const408: F64
    var rec90_perm: Arr[F64, 4]
    var const409: F64
    var const410: F64
    var const411: F64
    var rec103_perm: Arr[F64, 4]
    var const412: F64
    var const413: F64
    var const414: F64
    var const415: F64
    var const416: F64
    var const417: F64
    var rec102_perm: Arr[F64, 4]
    var const418: F64
    var const419: F64
    var const420: F64
    var const421: F64
    var const422: F64
    var rec101_perm: Arr[F64, 4]
    var const423: F64
    var const424: F64
    var const425: F64
    var const426: F64
    var const427: F64
    var const428: F64
    var const429: F64
    var const430: F64
    var const431: F64
    var rec100_perm: Arr[F64, 4]
    var const432: F64
    var const433: F64
    var const434: F64
    var const435: F64
    var const436: F64
    var const437: F64
    var rec99_perm: Arr[F64, 4]
    var const438: F64
    var const439: F64
    var const440: F64
    var const441: F64
    var const442: F64
    var const443: F64
    var rec98_perm: Arr[F64, 4]
    var const444: F64
    var const445: F64
    var const446: F64
    var rec97_perm: Arr[F64, 4]
    var const447: F64
    var const448: F64
    var const449: F64
    var rec110_perm: Arr[F64, 4]
    var const450: F64
    var const451: F64
    var const452: F64
    var const453: F64
    var const454: F64
    var const455: F64
    var rec109_perm: Arr[F64, 4]
    var const456: F64
    var const457: F64
    var const458: F64
    var const459: F64
    var const460: F64
    var rec108_perm: Arr[F64, 4]
    var const461: F64
    var const462: F64
    var const463: F64
    var const464: F64
    var const465: F64
    var const466: F64
    var const467: F64
    var const468: F64
    var const469: F64
    var rec107_perm: Arr[F64, 4]
    var const470: F64
    var const471: F64
    var const472: F64
    var const473: F64
    var const474: F64
    var const475: F64
    var rec106_perm: Arr[F64, 4]
    var const476: F64
    var const477: F64
    var const478: F64
    var const479: F64
    var const480: F64
    var const481: F64
    var rec105_perm: Arr[F64, 4]
    var const482: F64
    var const483: F64
    var const484: F64
    var rec104_perm: Arr[F64, 4]
    var const485: F64
    var const486: F64
    var const487: F64
    var rec117_perm: Arr[F64, 4]
    var const488: F64
    var const489: F64
    var const490: F64
    var const491: F64
    var const492: F64
    var const493: F64
    var rec116_perm: Arr[F64, 4]
    var const494: F64
    var const495: F64
    var const496: F64
    var const497: F64
    var const498: F64
    var rec115_perm: Arr[F64, 4]
    var const499: F64
    var const500: F64
    var const501: F64
    var const502: F64
    var const503: F64
    var const504: F64
    var const505: F64
    var const506: F64
    var const507: F64
    var rec114_perm: Arr[F64, 4]
    var const508: F64
    var const509: F64
    var const510: F64
    var const511: F64
    var const512: F64
    var const513: F64
    var rec113_perm: Arr[F64, 4]
    var const514: F64
    var const515: F64
    var const516: F64
    var const517: F64
    var const518: F64
    var const519: F64
    var rec112_perm: Arr[F64, 4]
    var const520: F64
    var const521: F64
    var const522: F64
    var rec111_perm: Arr[F64, 4]
    var const523: F64
    var const524: F64
    var const525: F64
    var rec121_perm: Arr[F64, 4]
    var const526: F64
    var const527: F64
    var const528: F64
    var const529: F64
    var const530: F64
    var const531: F64
    var rec120_perm: Arr[F64, 4]
    var const532: F64
    var const533: F64
    var const534: F64
    var const535: F64
    var const536: F64
    var rec119_perm: Arr[F64, 4]
    var const537: F64
    var const538: F64
    var rec118_perm: Arr[F64, 4]
    var hslider10: FaustFloat
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
        dsp.vslider0 = 0.0
        dsp.rec4_perm = Arr[F64, 4](fill=0.0)
        dsp.vslider1 = 0.0
        dsp.sample_rate = 0
        dsp.const0 = 0.0
        dsp.const1 = 0.0
        dsp.vslider2 = 0.0
        dsp.rec6_perm = Arr[F64, 4](fill=0.0)
        dsp.rec5_perm = Arr[F64, 4](fill=0.0)
        dsp.vslider3 = 0.0
        dsp.rec7_perm = Arr[F64, 4](fill=0.0)
        dsp.vslider4 = 0.0
        dsp.rec8_perm = Arr[F64, 4](fill=0.0)
        dsp.i_rec9_perm = Arr[S32, 4](fill=0)
        dsp.rec10_perm = Arr[F64, 4](fill=0.0)
        dsp.hslider0 = 0.0
        dsp.hslider1 = 0.0
        dsp.checkbox0 = 0.0
        dsp.checkbox1 = 0.0
        dsp.checkbox2 = 0.0
        dsp.entry0 = 0.0
        dsp.i_vec0_perm = Arr[S32, 4](fill=0)
        dsp.const2 = 0.0
        dsp.yec0_perm = Arr[F64, 4](fill=0.0)
        dsp.const3 = 0.0
        dsp.yec1_perm = Arr[F64, 4](fill=0.0)
        dsp.yec2_perm = Arr[F64, 4](fill=0.0)
        dsp.const4 = 0.0
        dsp.yec3_perm = Arr[F64, 4](fill=0.0)
        dsp.yec4_perm = Arr[F64, 4](fill=0.0)
        dsp.yec5_perm = Arr[F64, 4](fill=0.0)
        dsp.yec6_perm = Arr[F64, 4](fill=0.0)
        dsp.yec7_perm = Arr[F64, 4](fill=0.0)
        dsp.yec8_perm = Arr[F64, 4](fill=0.0)
        dsp.yec9_perm = Arr[F64, 4](fill=0.0)
        dsp.yec10_perm = Arr[F64, 4](fill=0.0)
        dsp.yec11_perm = Arr[F64, 4](fill=0.0)
        dsp.yec12_perm = Arr[F64, 4](fill=0.0)
        dsp.yec13_perm = Arr[F64, 4](fill=0.0)
        dsp.yec14_perm = Arr[F64, 4](fill=0.0)
        dsp.yec15_perm = Arr[F64, 4](fill=0.0)
        dsp.yec16_perm = Arr[F64, 4](fill=0.0)
        dsp.yec17_perm = Arr[F64, 4](fill=0.0)
        dsp.checkbox3 = 0.0
        dsp.rec14_perm = Arr[F64, 4](fill=0.0)
        dsp.hslider2 = 0.0
        dsp.hslider3 = 0.0
        dsp.i_yec18_perm = Arr[S32, 4](fill=0)
        dsp.i_rec15_perm = Arr[S32, 4](fill=0)
        dsp.rec12_perm = Arr[F64, 4](fill=0.0)
        dsp.rec11_perm = Arr[F64, 4](fill=0.0)
        dsp.hbargraph0 = 0.0
        dsp.rec3_perm = Arr[F64, 4](fill=0.0)
        dsp.i_yec19_perm = Arr[S32, 4](fill=0)
        dsp.i_rec16_perm = Arr[S32, 4](fill=0)
        dsp.rec1_perm = Arr[F64, 4](fill=0.0)
        dsp.rec0_perm = Arr[F64, 4](fill=0.0)
        dsp.checkbox4 = 0.0
        dsp.hslider4 = 0.0
        dsp.hslider5 = 0.0
        dsp.rec19_perm = Arr[F64, 4](fill=0.0)
        dsp.rec18_perm = Arr[F64, 4](fill=0.0)
        dsp.const5 = 0.0
        dsp.hslider6 = 0.0
        dsp.hslider7 = 0.0
        dsp.rec17_perm = Arr[F64, 4](fill=0.0)
        dsp.rec22_perm = Arr[F64, 4](fill=0.0)
        dsp.rec21_perm = Arr[F64, 4](fill=0.0)
        dsp.rec20_perm = Arr[F64, 4](fill=0.0)
        dsp.hslider8 = 0.0
        dsp.hbargraph1 = 0.0
        dsp.const6 = 0.0
        dsp.const7 = 0.0
        dsp.const8 = 0.0
        dsp.const9 = 0.0
        dsp.const10 = 0.0
        dsp.const11 = 0.0
        dsp.const12 = 0.0
        dsp.rec26_perm = Arr[F64, 4](fill=0.0)
        dsp.const13 = 0.0
        dsp.const14 = 0.0
        dsp.const15 = 0.0
        dsp.const16 = 0.0
        dsp.const17 = 0.0
        dsp.const18 = 0.0
        dsp.rec25_perm = Arr[F64, 4](fill=0.0)
        dsp.const19 = 0.0
        dsp.const20 = 0.0
        dsp.const21 = 0.0
        dsp.const22 = 0.0
        dsp.const23 = 0.0
        dsp.const24 = 0.0
        dsp.rec24_perm = Arr[F64, 4](fill=0.0)
        dsp.hslider9 = 0.0
        dsp.const25 = 0.0
        dsp.const26 = 0.0
        dsp.const27 = 0.0
        dsp.const28 = 0.0
        dsp.rec23_perm = Arr[F64, 4](fill=0.0)
        dsp.const29 = 0.0
        dsp.const30 = 0.0
        dsp.const31 = 0.0
        dsp.rec33_perm = Arr[F64, 4](fill=0.0)
        dsp.const32 = 0.0
        dsp.const33 = 0.0
        dsp.const34 = 0.0
        dsp.const35 = 0.0
        dsp.const36 = 0.0
        dsp.const37 = 0.0
        dsp.rec32_perm = Arr[F64, 4](fill=0.0)
        dsp.const38 = 0.0
        dsp.const39 = 0.0
        dsp.const40 = 0.0
        dsp.const41 = 0.0
        dsp.const42 = 0.0
        dsp.rec31_perm = Arr[F64, 4](fill=0.0)
        dsp.const43 = 0.0
        dsp.const44 = 0.0
        dsp.const45 = 0.0
        dsp.const46 = 0.0
        dsp.const47 = 0.0
        dsp.const48 = 0.0
        dsp.const49 = 0.0
        dsp.const50 = 0.0
        dsp.const51 = 0.0
        dsp.rec30_perm = Arr[F64, 4](fill=0.0)
        dsp.const52 = 0.0
        dsp.const53 = 0.0
        dsp.const54 = 0.0
        dsp.const55 = 0.0
        dsp.const56 = 0.0
        dsp.const57 = 0.0
        dsp.rec29_perm = Arr[F64, 4](fill=0.0)
        dsp.const58 = 0.0
        dsp.const59 = 0.0
        dsp.const60 = 0.0
        dsp.const61 = 0.0
        dsp.const62 = 0.0
        dsp.const63 = 0.0
        dsp.rec28_perm = Arr[F64, 4](fill=0.0)
        dsp.const64 = 0.0
        dsp.const65 = 0.0
        dsp.const66 = 0.0
        dsp.rec27_perm = Arr[F64, 4](fill=0.0)
        dsp.const67 = 0.0
        dsp.const68 = 0.0
        dsp.const69 = 0.0
        dsp.rec40_perm = Arr[F64, 4](fill=0.0)
        dsp.const70 = 0.0
        dsp.const71 = 0.0
        dsp.const72 = 0.0
        dsp.const73 = 0.0
        dsp.const74 = 0.0
        dsp.const75 = 0.0
        dsp.rec39_perm = Arr[F64, 4](fill=0.0)
        dsp.const76 = 0.0
        dsp.const77 = 0.0
        dsp.const78 = 0.0
        dsp.const79 = 0.0
        dsp.const80 = 0.0
        dsp.rec38_perm = Arr[F64, 4](fill=0.0)
        dsp.const81 = 0.0
        dsp.const82 = 0.0
        dsp.const83 = 0.0
        dsp.const84 = 0.0
        dsp.const85 = 0.0
        dsp.const86 = 0.0
        dsp.const87 = 0.0
        dsp.const88 = 0.0
        dsp.const89 = 0.0
        dsp.rec37_perm = Arr[F64, 4](fill=0.0)
        dsp.const90 = 0.0
        dsp.const91 = 0.0
        dsp.const92 = 0.0
        dsp.const93 = 0.0
        dsp.const94 = 0.0
        dsp.const95 = 0.0
        dsp.rec36_perm = Arr[F64, 4](fill=0.0)
        dsp.const96 = 0.0
        dsp.const97 = 0.0
        dsp.const98 = 0.0
        dsp.const99 = 0.0
        dsp.const100 = 0.0
        dsp.const101 = 0.0
        dsp.rec35_perm = Arr[F64, 4](fill=0.0)
        dsp.const102 = 0.0
        dsp.const103 = 0.0
        dsp.const104 = 0.0
        dsp.rec34_perm = Arr[F64, 4](fill=0.0)
        dsp.const105 = 0.0
        dsp.const106 = 0.0
        dsp.const107 = 0.0
        dsp.rec47_perm = Arr[F64, 4](fill=0.0)
        dsp.const108 = 0.0
        dsp.const109 = 0.0
        dsp.const110 = 0.0
        dsp.const111 = 0.0
        dsp.const112 = 0.0
        dsp.const113 = 0.0
        dsp.rec46_perm = Arr[F64, 4](fill=0.0)
        dsp.const114 = 0.0
        dsp.const115 = 0.0
        dsp.const116 = 0.0
        dsp.const117 = 0.0
        dsp.const118 = 0.0
        dsp.rec45_perm = Arr[F64, 4](fill=0.0)
        dsp.const119 = 0.0
        dsp.const120 = 0.0
        dsp.const121 = 0.0
        dsp.const122 = 0.0
        dsp.const123 = 0.0
        dsp.const124 = 0.0
        dsp.const125 = 0.0
        dsp.const126 = 0.0
        dsp.const127 = 0.0
        dsp.rec44_perm = Arr[F64, 4](fill=0.0)
        dsp.const128 = 0.0
        dsp.const129 = 0.0
        dsp.const130 = 0.0
        dsp.const131 = 0.0
        dsp.const132 = 0.0
        dsp.const133 = 0.0
        dsp.rec43_perm = Arr[F64, 4](fill=0.0)
        dsp.const134 = 0.0
        dsp.const135 = 0.0
        dsp.const136 = 0.0
        dsp.const137 = 0.0
        dsp.const138 = 0.0
        dsp.const139 = 0.0
        dsp.rec42_perm = Arr[F64, 4](fill=0.0)
        dsp.const140 = 0.0
        dsp.const141 = 0.0
        dsp.const142 = 0.0
        dsp.rec41_perm = Arr[F64, 4](fill=0.0)
        dsp.const143 = 0.0
        dsp.const144 = 0.0
        dsp.const145 = 0.0
        dsp.rec54_perm = Arr[F64, 4](fill=0.0)
        dsp.const146 = 0.0
        dsp.const147 = 0.0
        dsp.const148 = 0.0
        dsp.const149 = 0.0
        dsp.const150 = 0.0
        dsp.const151 = 0.0
        dsp.rec53_perm = Arr[F64, 4](fill=0.0)
        dsp.const152 = 0.0
        dsp.const153 = 0.0
        dsp.const154 = 0.0
        dsp.const155 = 0.0
        dsp.const156 = 0.0
        dsp.rec52_perm = Arr[F64, 4](fill=0.0)
        dsp.const157 = 0.0
        dsp.const158 = 0.0
        dsp.const159 = 0.0
        dsp.const160 = 0.0
        dsp.const161 = 0.0
        dsp.const162 = 0.0
        dsp.const163 = 0.0
        dsp.const164 = 0.0
        dsp.const165 = 0.0
        dsp.rec51_perm = Arr[F64, 4](fill=0.0)
        dsp.const166 = 0.0
        dsp.const167 = 0.0
        dsp.const168 = 0.0
        dsp.const169 = 0.0
        dsp.const170 = 0.0
        dsp.const171 = 0.0
        dsp.rec50_perm = Arr[F64, 4](fill=0.0)
        dsp.const172 = 0.0
        dsp.const173 = 0.0
        dsp.const174 = 0.0
        dsp.const175 = 0.0
        dsp.const176 = 0.0
        dsp.const177 = 0.0
        dsp.rec49_perm = Arr[F64, 4](fill=0.0)
        dsp.const178 = 0.0
        dsp.const179 = 0.0
        dsp.const180 = 0.0
        dsp.rec48_perm = Arr[F64, 4](fill=0.0)
        dsp.const181 = 0.0
        dsp.const182 = 0.0
        dsp.const183 = 0.0
        dsp.rec61_perm = Arr[F64, 4](fill=0.0)
        dsp.const184 = 0.0
        dsp.const185 = 0.0
        dsp.const186 = 0.0
        dsp.const187 = 0.0
        dsp.const188 = 0.0
        dsp.const189 = 0.0
        dsp.rec60_perm = Arr[F64, 4](fill=0.0)
        dsp.const190 = 0.0
        dsp.const191 = 0.0
        dsp.const192 = 0.0
        dsp.const193 = 0.0
        dsp.const194 = 0.0
        dsp.rec59_perm = Arr[F64, 4](fill=0.0)
        dsp.const195 = 0.0
        dsp.const196 = 0.0
        dsp.const197 = 0.0
        dsp.const198 = 0.0
        dsp.const199 = 0.0
        dsp.const200 = 0.0
        dsp.const201 = 0.0
        dsp.const202 = 0.0
        dsp.const203 = 0.0
        dsp.rec58_perm = Arr[F64, 4](fill=0.0)
        dsp.const204 = 0.0
        dsp.const205 = 0.0
        dsp.const206 = 0.0
        dsp.const207 = 0.0
        dsp.const208 = 0.0
        dsp.const209 = 0.0
        dsp.rec57_perm = Arr[F64, 4](fill=0.0)
        dsp.const210 = 0.0
        dsp.const211 = 0.0
        dsp.const212 = 0.0
        dsp.const213 = 0.0
        dsp.const214 = 0.0
        dsp.const215 = 0.0
        dsp.rec56_perm = Arr[F64, 4](fill=0.0)
        dsp.const216 = 0.0
        dsp.const217 = 0.0
        dsp.const218 = 0.0
        dsp.rec55_perm = Arr[F64, 4](fill=0.0)
        dsp.const219 = 0.0
        dsp.const220 = 0.0
        dsp.const221 = 0.0
        dsp.rec68_perm = Arr[F64, 4](fill=0.0)
        dsp.const222 = 0.0
        dsp.const223 = 0.0
        dsp.const224 = 0.0
        dsp.const225 = 0.0
        dsp.const226 = 0.0
        dsp.const227 = 0.0
        dsp.rec67_perm = Arr[F64, 4](fill=0.0)
        dsp.const228 = 0.0
        dsp.const229 = 0.0
        dsp.const230 = 0.0
        dsp.const231 = 0.0
        dsp.const232 = 0.0
        dsp.rec66_perm = Arr[F64, 4](fill=0.0)
        dsp.const233 = 0.0
        dsp.const234 = 0.0
        dsp.const235 = 0.0
        dsp.const236 = 0.0
        dsp.const237 = 0.0
        dsp.const238 = 0.0
        dsp.const239 = 0.0
        dsp.const240 = 0.0
        dsp.const241 = 0.0
        dsp.rec65_perm = Arr[F64, 4](fill=0.0)
        dsp.const242 = 0.0
        dsp.const243 = 0.0
        dsp.const244 = 0.0
        dsp.const245 = 0.0
        dsp.const246 = 0.0
        dsp.const247 = 0.0
        dsp.rec64_perm = Arr[F64, 4](fill=0.0)
        dsp.const248 = 0.0
        dsp.const249 = 0.0
        dsp.const250 = 0.0
        dsp.const251 = 0.0
        dsp.const252 = 0.0
        dsp.const253 = 0.0
        dsp.rec63_perm = Arr[F64, 4](fill=0.0)
        dsp.const254 = 0.0
        dsp.const255 = 0.0
        dsp.const256 = 0.0
        dsp.rec62_perm = Arr[F64, 4](fill=0.0)
        dsp.const257 = 0.0
        dsp.const258 = 0.0
        dsp.const259 = 0.0
        dsp.rec75_perm = Arr[F64, 4](fill=0.0)
        dsp.const260 = 0.0
        dsp.const261 = 0.0
        dsp.const262 = 0.0
        dsp.const263 = 0.0
        dsp.const264 = 0.0
        dsp.const265 = 0.0
        dsp.rec74_perm = Arr[F64, 4](fill=0.0)
        dsp.const266 = 0.0
        dsp.const267 = 0.0
        dsp.const268 = 0.0
        dsp.const269 = 0.0
        dsp.const270 = 0.0
        dsp.rec73_perm = Arr[F64, 4](fill=0.0)
        dsp.const271 = 0.0
        dsp.const272 = 0.0
        dsp.const273 = 0.0
        dsp.const274 = 0.0
        dsp.const275 = 0.0
        dsp.const276 = 0.0
        dsp.const277 = 0.0
        dsp.const278 = 0.0
        dsp.const279 = 0.0
        dsp.rec72_perm = Arr[F64, 4](fill=0.0)
        dsp.const280 = 0.0
        dsp.const281 = 0.0
        dsp.const282 = 0.0
        dsp.const283 = 0.0
        dsp.const284 = 0.0
        dsp.const285 = 0.0
        dsp.rec71_perm = Arr[F64, 4](fill=0.0)
        dsp.const286 = 0.0
        dsp.const287 = 0.0
        dsp.const288 = 0.0
        dsp.const289 = 0.0
        dsp.const290 = 0.0
        dsp.const291 = 0.0
        dsp.rec70_perm = Arr[F64, 4](fill=0.0)
        dsp.const292 = 0.0
        dsp.const293 = 0.0
        dsp.const294 = 0.0
        dsp.rec69_perm = Arr[F64, 4](fill=0.0)
        dsp.const295 = 0.0
        dsp.const296 = 0.0
        dsp.const297 = 0.0
        dsp.rec82_perm = Arr[F64, 4](fill=0.0)
        dsp.const298 = 0.0
        dsp.const299 = 0.0
        dsp.const300 = 0.0
        dsp.const301 = 0.0
        dsp.const302 = 0.0
        dsp.const303 = 0.0
        dsp.rec81_perm = Arr[F64, 4](fill=0.0)
        dsp.const304 = 0.0
        dsp.const305 = 0.0
        dsp.const306 = 0.0
        dsp.const307 = 0.0
        dsp.const308 = 0.0
        dsp.rec80_perm = Arr[F64, 4](fill=0.0)
        dsp.const309 = 0.0
        dsp.const310 = 0.0
        dsp.const311 = 0.0
        dsp.const312 = 0.0
        dsp.const313 = 0.0
        dsp.const314 = 0.0
        dsp.const315 = 0.0
        dsp.const316 = 0.0
        dsp.const317 = 0.0
        dsp.rec79_perm = Arr[F64, 4](fill=0.0)
        dsp.const318 = 0.0
        dsp.const319 = 0.0
        dsp.const320 = 0.0
        dsp.const321 = 0.0
        dsp.const322 = 0.0
        dsp.const323 = 0.0
        dsp.rec78_perm = Arr[F64, 4](fill=0.0)
        dsp.const324 = 0.0
        dsp.const325 = 0.0
        dsp.const326 = 0.0
        dsp.const327 = 0.0
        dsp.const328 = 0.0
        dsp.const329 = 0.0
        dsp.rec77_perm = Arr[F64, 4](fill=0.0)
        dsp.const330 = 0.0
        dsp.const331 = 0.0
        dsp.const332 = 0.0
        dsp.rec76_perm = Arr[F64, 4](fill=0.0)
        dsp.const333 = 0.0
        dsp.const334 = 0.0
        dsp.const335 = 0.0
        dsp.rec89_perm = Arr[F64, 4](fill=0.0)
        dsp.const336 = 0.0
        dsp.const337 = 0.0
        dsp.const338 = 0.0
        dsp.const339 = 0.0
        dsp.const340 = 0.0
        dsp.const341 = 0.0
        dsp.rec88_perm = Arr[F64, 4](fill=0.0)
        dsp.const342 = 0.0
        dsp.const343 = 0.0
        dsp.const344 = 0.0
        dsp.const345 = 0.0
        dsp.const346 = 0.0
        dsp.rec87_perm = Arr[F64, 4](fill=0.0)
        dsp.const347 = 0.0
        dsp.const348 = 0.0
        dsp.const349 = 0.0
        dsp.const350 = 0.0
        dsp.const351 = 0.0
        dsp.const352 = 0.0
        dsp.const353 = 0.0
        dsp.const354 = 0.0
        dsp.const355 = 0.0
        dsp.rec86_perm = Arr[F64, 4](fill=0.0)
        dsp.const356 = 0.0
        dsp.const357 = 0.0
        dsp.const358 = 0.0
        dsp.const359 = 0.0
        dsp.const360 = 0.0
        dsp.const361 = 0.0
        dsp.rec85_perm = Arr[F64, 4](fill=0.0)
        dsp.const362 = 0.0
        dsp.const363 = 0.0
        dsp.const364 = 0.0
        dsp.const365 = 0.0
        dsp.const366 = 0.0
        dsp.const367 = 0.0
        dsp.rec84_perm = Arr[F64, 4](fill=0.0)
        dsp.const368 = 0.0
        dsp.const369 = 0.0
        dsp.const370 = 0.0
        dsp.rec83_perm = Arr[F64, 4](fill=0.0)
        dsp.const371 = 0.0
        dsp.const372 = 0.0
        dsp.const373 = 0.0
        dsp.rec96_perm = Arr[F64, 4](fill=0.0)
        dsp.const374 = 0.0
        dsp.const375 = 0.0
        dsp.const376 = 0.0
        dsp.const377 = 0.0
        dsp.const378 = 0.0
        dsp.const379 = 0.0
        dsp.rec95_perm = Arr[F64, 4](fill=0.0)
        dsp.const380 = 0.0
        dsp.const381 = 0.0
        dsp.const382 = 0.0
        dsp.const383 = 0.0
        dsp.const384 = 0.0
        dsp.rec94_perm = Arr[F64, 4](fill=0.0)
        dsp.const385 = 0.0
        dsp.const386 = 0.0
        dsp.const387 = 0.0
        dsp.const388 = 0.0
        dsp.const389 = 0.0
        dsp.const390 = 0.0
        dsp.const391 = 0.0
        dsp.const392 = 0.0
        dsp.const393 = 0.0
        dsp.rec93_perm = Arr[F64, 4](fill=0.0)
        dsp.const394 = 0.0
        dsp.const395 = 0.0
        dsp.const396 = 0.0
        dsp.const397 = 0.0
        dsp.const398 = 0.0
        dsp.const399 = 0.0
        dsp.rec92_perm = Arr[F64, 4](fill=0.0)
        dsp.const400 = 0.0
        dsp.const401 = 0.0
        dsp.const402 = 0.0
        dsp.const403 = 0.0
        dsp.const404 = 0.0
        dsp.const405 = 0.0
        dsp.rec91_perm = Arr[F64, 4](fill=0.0)
        dsp.const406 = 0.0
        dsp.const407 = 0.0
        dsp.const408 = 0.0
        dsp.rec90_perm = Arr[F64, 4](fill=0.0)
        dsp.const409 = 0.0
        dsp.const410 = 0.0
        dsp.const411 = 0.0
        dsp.rec103_perm = Arr[F64, 4](fill=0.0)
        dsp.const412 = 0.0
        dsp.const413 = 0.0
        dsp.const414 = 0.0
        dsp.const415 = 0.0
        dsp.const416 = 0.0
        dsp.const417 = 0.0
        dsp.rec102_perm = Arr[F64, 4](fill=0.0)
        dsp.const418 = 0.0
        dsp.const419 = 0.0
        dsp.const420 = 0.0
        dsp.const421 = 0.0
        dsp.const422 = 0.0
        dsp.rec101_perm = Arr[F64, 4](fill=0.0)
        dsp.const423 = 0.0
        dsp.const424 = 0.0
        dsp.const425 = 0.0
        dsp.const426 = 0.0
        dsp.const427 = 0.0
        dsp.const428 = 0.0
        dsp.const429 = 0.0
        dsp.const430 = 0.0
        dsp.const431 = 0.0
        dsp.rec100_perm = Arr[F64, 4](fill=0.0)
        dsp.const432 = 0.0
        dsp.const433 = 0.0
        dsp.const434 = 0.0
        dsp.const435 = 0.0
        dsp.const436 = 0.0
        dsp.const437 = 0.0
        dsp.rec99_perm = Arr[F64, 4](fill=0.0)
        dsp.const438 = 0.0
        dsp.const439 = 0.0
        dsp.const440 = 0.0
        dsp.const441 = 0.0
        dsp.const442 = 0.0
        dsp.const443 = 0.0
        dsp.rec98_perm = Arr[F64, 4](fill=0.0)
        dsp.const444 = 0.0
        dsp.const445 = 0.0
        dsp.const446 = 0.0
        dsp.rec97_perm = Arr[F64, 4](fill=0.0)
        dsp.const447 = 0.0
        dsp.const448 = 0.0
        dsp.const449 = 0.0
        dsp.rec110_perm = Arr[F64, 4](fill=0.0)
        dsp.const450 = 0.0
        dsp.const451 = 0.0
        dsp.const452 = 0.0
        dsp.const453 = 0.0
        dsp.const454 = 0.0
        dsp.const455 = 0.0
        dsp.rec109_perm = Arr[F64, 4](fill=0.0)
        dsp.const456 = 0.0
        dsp.const457 = 0.0
        dsp.const458 = 0.0
        dsp.const459 = 0.0
        dsp.const460 = 0.0
        dsp.rec108_perm = Arr[F64, 4](fill=0.0)
        dsp.const461 = 0.0
        dsp.const462 = 0.0
        dsp.const463 = 0.0
        dsp.const464 = 0.0
        dsp.const465 = 0.0
        dsp.const466 = 0.0
        dsp.const467 = 0.0
        dsp.const468 = 0.0
        dsp.const469 = 0.0
        dsp.rec107_perm = Arr[F64, 4](fill=0.0)
        dsp.const470 = 0.0
        dsp.const471 = 0.0
        dsp.const472 = 0.0
        dsp.const473 = 0.0
        dsp.const474 = 0.0
        dsp.const475 = 0.0
        dsp.rec106_perm = Arr[F64, 4](fill=0.0)
        dsp.const476 = 0.0
        dsp.const477 = 0.0
        dsp.const478 = 0.0
        dsp.const479 = 0.0
        dsp.const480 = 0.0
        dsp.const481 = 0.0
        dsp.rec105_perm = Arr[F64, 4](fill=0.0)
        dsp.const482 = 0.0
        dsp.const483 = 0.0
        dsp.const484 = 0.0
        dsp.rec104_perm = Arr[F64, 4](fill=0.0)
        dsp.const485 = 0.0
        dsp.const486 = 0.0
        dsp.const487 = 0.0
        dsp.rec117_perm = Arr[F64, 4](fill=0.0)
        dsp.const488 = 0.0
        dsp.const489 = 0.0
        dsp.const490 = 0.0
        dsp.const491 = 0.0
        dsp.const492 = 0.0
        dsp.const493 = 0.0
        dsp.rec116_perm = Arr[F64, 4](fill=0.0)
        dsp.const494 = 0.0
        dsp.const495 = 0.0
        dsp.const496 = 0.0
        dsp.const497 = 0.0
        dsp.const498 = 0.0
        dsp.rec115_perm = Arr[F64, 4](fill=0.0)
        dsp.const499 = 0.0
        dsp.const500 = 0.0
        dsp.const501 = 0.0
        dsp.const502 = 0.0
        dsp.const503 = 0.0
        dsp.const504 = 0.0
        dsp.const505 = 0.0
        dsp.const506 = 0.0
        dsp.const507 = 0.0
        dsp.rec114_perm = Arr[F64, 4](fill=0.0)
        dsp.const508 = 0.0
        dsp.const509 = 0.0
        dsp.const510 = 0.0
        dsp.const511 = 0.0
        dsp.const512 = 0.0
        dsp.const513 = 0.0
        dsp.rec113_perm = Arr[F64, 4](fill=0.0)
        dsp.const514 = 0.0
        dsp.const515 = 0.0
        dsp.const516 = 0.0
        dsp.const517 = 0.0
        dsp.const518 = 0.0
        dsp.const519 = 0.0
        dsp.rec112_perm = Arr[F64, 4](fill=0.0)
        dsp.const520 = 0.0
        dsp.const521 = 0.0
        dsp.const522 = 0.0
        dsp.rec111_perm = Arr[F64, 4](fill=0.0)
        dsp.const523 = 0.0
        dsp.const524 = 0.0
        dsp.const525 = 0.0
        dsp.rec121_perm = Arr[F64, 4](fill=0.0)
        dsp.const526 = 0.0
        dsp.const527 = 0.0
        dsp.const528 = 0.0
        dsp.const529 = 0.0
        dsp.const530 = 0.0
        dsp.const531 = 0.0
        dsp.rec120_perm = Arr[F64, 4](fill=0.0)
        dsp.const532 = 0.0
        dsp.const533 = 0.0
        dsp.const534 = 0.0
        dsp.const535 = 0.0
        dsp.const536 = 0.0
        dsp.rec119_perm = Arr[F64, 4](fill=0.0)
        dsp.const537 = 0.0
        dsp.const538 = 0.0
        dsp.rec118_perm = Arr[F64, 4](fill=0.0)
        dsp.hslider10 = 0.0
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
        return 1

    @always_inline
    def class_init(mut dsp, imm sample_rate: S32) -> None:
        pass

    @always_inline
    def instance_constants(mut dsp, imm sample_rate: S32) -> None:
        dsp.sample_rate = sample_rate
        dsp.const0 = min(1.92e+05, max(1.0, F64(dsp.sample_rate)))
        dsp.const1 = (1.0) / (dsp.const0)
        dsp.const2 = (0.25) * (dsp.const0)
        dsp.const3 = (0.041666666666666664) * (pow_unrolled[2](dsp.const0))
        dsp.const4 = (0.005208333333333333) * (pow_unrolled[3](dsp.const0))
        dsp.const5 = (2.0) / (dsp.const0)
        dsp.const6 = tan((50265.48245743669) / (dsp.const0))
        dsp.const7 = (1.0) / (dsp.const6)
        dsp.const8 = (1.0) / ((((dsp.const7) + (3.1897274020965583)) / (dsp.const6)) + (4.076781969643807))
        dsp.const9 = (((dsp.const7) + (-3.1897274020965583)) / (dsp.const6)) + (4.076781969643807)
        dsp.const10 = pow_unrolled[2](dsp.const6)
        dsp.const11 = (1.0) / (dsp.const10)
        dsp.const12 = (2.0) * ((4.076781969643807) - (dsp.const11))
        dsp.const13 = (0.0017661728399818856) / (dsp.const10)
        dsp.const14 = (dsp.const13) + (0.00040767818495825777)
        dsp.const15 = (2.0) * ((0.00040767818495825777) - (dsp.const13))
        dsp.const16 = (1.0) / ((((dsp.const7) + (0.7431304601070396)) / (dsp.const6)) + (1.450071084655647))
        dsp.const17 = (((dsp.const7) + (-0.7431304601070396)) / (dsp.const6)) + (1.450071084655647)
        dsp.const18 = (2.0) * ((1.450071084655647) - (dsp.const11))
        dsp.const19 = (11.052052171507189) / (dsp.const10)
        dsp.const20 = (dsp.const19) + (1.450071084655647)
        dsp.const21 = (2.0) * ((1.450071084655647) - (dsp.const19))
        dsp.const22 = (1.0) / ((((dsp.const7) + (0.157482159302087)) / (dsp.const6)) + (0.9351401670315425))
        dsp.const23 = (((dsp.const7) + (-0.157482159302087)) / (dsp.const6)) + (0.9351401670315425)
        dsp.const24 = (2.0) * ((0.9351401670315425) - (dsp.const11))
        dsp.const25 = (1e+03) / (dsp.const0)
        dsp.const26 = (50.063807016150385) / (dsp.const10)
        dsp.const27 = (dsp.const26) + (0.9351401670315425)
        dsp.const28 = (2.0) * ((0.9351401670315425) - (dsp.const26))
        dsp.const29 = (1.0) / ((((dsp.const7) + (0.782413046821645)) / (dsp.const6)) + (0.24529150870616))
        dsp.const30 = (((dsp.const7) + (-0.782413046821645)) / (dsp.const6)) + (0.24529150870616)
        dsp.const31 = (2.0) * ((0.24529150870616) - (dsp.const11))
        dsp.const32 = (9.9999997055e-05) / (dsp.const10)
        dsp.const33 = (dsp.const32) + (0.000433227200555)
        dsp.const34 = (2.0) * ((0.000433227200555) - (dsp.const32))
        dsp.const35 = (1.0) / ((((dsp.const7) + (0.512478641889141)) / (dsp.const6)) + (0.689621364484675))
        dsp.const36 = (((dsp.const7) + (-0.512478641889141)) / (dsp.const6)) + (0.689621364484675)
        dsp.const37 = (2.0) * ((0.689621364484675) - (dsp.const11))
        dsp.const38 = (dsp.const11) + (7.621731298870603)
        dsp.const39 = (2.0) * ((7.621731298870603) - (dsp.const11))
        dsp.const40 = (1.0) / ((((dsp.const7) + (0.168404871113589)) / (dsp.const6)) + (1.069358407707312))
        dsp.const41 = (((dsp.const7) + (-0.168404871113589)) / (dsp.const6)) + (1.069358407707312)
        dsp.const42 = (2.0) * ((1.069358407707312) - (dsp.const11))
        dsp.const43 = (dsp.const11) + (53.53615295455673)
        dsp.const44 = (2.0) * ((53.53615295455673) - (dsp.const11))
        dsp.const45 = tan((31665.269715622984) / (dsp.const0))
        dsp.const46 = (1.0) / (dsp.const45)
        dsp.const47 = (1.0) / ((((dsp.const46) + (3.1897274020965583)) / (dsp.const45)) + (4.076781969643807))
        dsp.const48 = (((dsp.const46) + (-3.1897274020965583)) / (dsp.const45)) + (4.076781969643807)
        dsp.const49 = pow_unrolled[2](dsp.const45)
        dsp.const50 = (1.0) / (dsp.const49)
        dsp.const51 = (2.0) * ((4.076781969643807) - (dsp.const50))
        dsp.const52 = (0.0017661728399818856) / (dsp.const49)
        dsp.const53 = (dsp.const52) + (0.00040767818495825777)
        dsp.const54 = (2.0) * ((0.00040767818495825777) - (dsp.const52))
        dsp.const55 = (1.0) / ((((dsp.const46) + (0.7431304601070396)) / (dsp.const45)) + (1.450071084655647))
        dsp.const56 = (((dsp.const46) + (-0.7431304601070396)) / (dsp.const45)) + (1.450071084655647)
        dsp.const57 = (2.0) * ((1.450071084655647) - (dsp.const50))
        dsp.const58 = (11.052052171507189) / (dsp.const49)
        dsp.const59 = (dsp.const58) + (1.450071084655647)
        dsp.const60 = (2.0) * ((1.450071084655647) - (dsp.const58))
        dsp.const61 = (1.0) / ((((dsp.const46) + (0.157482159302087)) / (dsp.const45)) + (0.9351401670315425))
        dsp.const62 = (((dsp.const46) + (-0.157482159302087)) / (dsp.const45)) + (0.9351401670315425)
        dsp.const63 = (2.0) * ((0.9351401670315425) - (dsp.const50))
        dsp.const64 = (50.063807016150385) / (dsp.const49)
        dsp.const65 = (dsp.const64) + (0.9351401670315425)
        dsp.const66 = (2.0) * ((0.9351401670315425) - (dsp.const64))
        dsp.const67 = (1.0) / ((((dsp.const46) + (0.782413046821645)) / (dsp.const45)) + (0.24529150870616))
        dsp.const68 = (((dsp.const46) + (-0.782413046821645)) / (dsp.const45)) + (0.24529150870616)
        dsp.const69 = (2.0) * ((0.24529150870616) - (dsp.const50))
        dsp.const70 = (9.9999997055e-05) / (dsp.const49)
        dsp.const71 = (dsp.const70) + (0.000433227200555)
        dsp.const72 = (2.0) * ((0.000433227200555) - (dsp.const70))
        dsp.const73 = (1.0) / ((((dsp.const46) + (0.512478641889141)) / (dsp.const45)) + (0.689621364484675))
        dsp.const74 = (((dsp.const46) + (-0.512478641889141)) / (dsp.const45)) + (0.689621364484675)
        dsp.const75 = (2.0) * ((0.689621364484675) - (dsp.const50))
        dsp.const76 = (dsp.const50) + (7.621731298870603)
        dsp.const77 = (2.0) * ((7.621731298870603) - (dsp.const50))
        dsp.const78 = (1.0) / ((((dsp.const46) + (0.168404871113589)) / (dsp.const45)) + (1.069358407707312))
        dsp.const79 = (((dsp.const46) + (-0.168404871113589)) / (dsp.const45)) + (1.069358407707312)
        dsp.const80 = (2.0) * ((1.069358407707312) - (dsp.const50))
        dsp.const81 = (dsp.const50) + (53.53615295455673)
        dsp.const82 = (2.0) * ((53.53615295455673) - (dsp.const50))
        dsp.const83 = tan((19947.869932656024) / (dsp.const0))
        dsp.const84 = (1.0) / (dsp.const83)
        dsp.const85 = (1.0) / ((((dsp.const84) + (3.1897274020965583)) / (dsp.const83)) + (4.076781969643807))
        dsp.const86 = (((dsp.const84) + (-3.1897274020965583)) / (dsp.const83)) + (4.076781969643807)
        dsp.const87 = pow_unrolled[2](dsp.const83)
        dsp.const88 = (1.0) / (dsp.const87)
        dsp.const89 = (2.0) * ((4.076781969643807) - (dsp.const88))
        dsp.const90 = (0.0017661728399818856) / (dsp.const87)
        dsp.const91 = (dsp.const90) + (0.00040767818495825777)
        dsp.const92 = (2.0) * ((0.00040767818495825777) - (dsp.const90))
        dsp.const93 = (1.0) / ((((dsp.const84) + (0.7431304601070396)) / (dsp.const83)) + (1.450071084655647))
        dsp.const94 = (((dsp.const84) + (-0.7431304601070396)) / (dsp.const83)) + (1.450071084655647)
        dsp.const95 = (2.0) * ((1.450071084655647) - (dsp.const88))
        dsp.const96 = (11.052052171507189) / (dsp.const87)
        dsp.const97 = (dsp.const96) + (1.450071084655647)
        dsp.const98 = (2.0) * ((1.450071084655647) - (dsp.const96))
        dsp.const99 = (1.0) / ((((dsp.const84) + (0.157482159302087)) / (dsp.const83)) + (0.9351401670315425))
        dsp.const100 = (((dsp.const84) + (-0.157482159302087)) / (dsp.const83)) + (0.9351401670315425)
        dsp.const101 = (2.0) * ((0.9351401670315425) - (dsp.const88))
        dsp.const102 = (50.063807016150385) / (dsp.const87)
        dsp.const103 = (dsp.const102) + (0.9351401670315425)
        dsp.const104 = (2.0) * ((0.9351401670315425) - (dsp.const102))
        dsp.const105 = (1.0) / ((((dsp.const84) + (0.782413046821645)) / (dsp.const83)) + (0.24529150870616))
        dsp.const106 = (((dsp.const84) + (-0.782413046821645)) / (dsp.const83)) + (0.24529150870616)
        dsp.const107 = (2.0) * ((0.24529150870616) - (dsp.const88))
        dsp.const108 = (9.9999997055e-05) / (dsp.const87)
        dsp.const109 = (dsp.const108) + (0.000433227200555)
        dsp.const110 = (2.0) * ((0.000433227200555) - (dsp.const108))
        dsp.const111 = (1.0) / ((((dsp.const84) + (0.512478641889141)) / (dsp.const83)) + (0.689621364484675))
        dsp.const112 = (((dsp.const84) + (-0.512478641889141)) / (dsp.const83)) + (0.689621364484675)
        dsp.const113 = (2.0) * ((0.689621364484675) - (dsp.const88))
        dsp.const114 = (dsp.const88) + (7.621731298870603)
        dsp.const115 = (2.0) * ((7.621731298870603) - (dsp.const88))
        dsp.const116 = (1.0) / ((((dsp.const84) + (0.168404871113589)) / (dsp.const83)) + (1.069358407707312))
        dsp.const117 = (((dsp.const84) + (-0.168404871113589)) / (dsp.const83)) + (1.069358407707312)
        dsp.const118 = (2.0) * ((1.069358407707312) - (dsp.const88))
        dsp.const119 = (dsp.const88) + (53.53615295455673)
        dsp.const120 = (2.0) * ((53.53615295455673) - (dsp.const88))
        dsp.const121 = tan((12566.370614359172) / (dsp.const0))
        dsp.const122 = (1.0) / (dsp.const121)
        dsp.const123 = (1.0) / ((((dsp.const122) + (3.1897274020965583)) / (dsp.const121)) + (4.076781969643807))
        dsp.const124 = (((dsp.const122) + (-3.1897274020965583)) / (dsp.const121)) + (4.076781969643807)
        dsp.const125 = pow_unrolled[2](dsp.const121)
        dsp.const126 = (1.0) / (dsp.const125)
        dsp.const127 = (2.0) * ((4.076781969643807) - (dsp.const126))
        dsp.const128 = (0.0017661728399818856) / (dsp.const125)
        dsp.const129 = (dsp.const128) + (0.00040767818495825777)
        dsp.const130 = (2.0) * ((0.00040767818495825777) - (dsp.const128))
        dsp.const131 = (1.0) / ((((dsp.const122) + (0.7431304601070396)) / (dsp.const121)) + (1.450071084655647))
        dsp.const132 = (((dsp.const122) + (-0.7431304601070396)) / (dsp.const121)) + (1.450071084655647)
        dsp.const133 = (2.0) * ((1.450071084655647) - (dsp.const126))
        dsp.const134 = (11.052052171507189) / (dsp.const125)
        dsp.const135 = (dsp.const134) + (1.450071084655647)
        dsp.const136 = (2.0) * ((1.450071084655647) - (dsp.const134))
        dsp.const137 = (1.0) / ((((dsp.const122) + (0.157482159302087)) / (dsp.const121)) + (0.9351401670315425))
        dsp.const138 = (((dsp.const122) + (-0.157482159302087)) / (dsp.const121)) + (0.9351401670315425)
        dsp.const139 = (2.0) * ((0.9351401670315425) - (dsp.const126))
        dsp.const140 = (50.063807016150385) / (dsp.const125)
        dsp.const141 = (dsp.const140) + (0.9351401670315425)
        dsp.const142 = (2.0) * ((0.9351401670315425) - (dsp.const140))
        dsp.const143 = (1.0) / ((((dsp.const122) + (0.782413046821645)) / (dsp.const121)) + (0.24529150870616))
        dsp.const144 = (((dsp.const122) + (-0.782413046821645)) / (dsp.const121)) + (0.24529150870616)
        dsp.const145 = (2.0) * ((0.24529150870616) - (dsp.const126))
        dsp.const146 = (9.9999997055e-05) / (dsp.const125)
        dsp.const147 = (dsp.const146) + (0.000433227200555)
        dsp.const148 = (2.0) * ((0.000433227200555) - (dsp.const146))
        dsp.const149 = (1.0) / ((((dsp.const122) + (0.512478641889141)) / (dsp.const121)) + (0.689621364484675))
        dsp.const150 = (((dsp.const122) + (-0.512478641889141)) / (dsp.const121)) + (0.689621364484675)
        dsp.const151 = (2.0) * ((0.689621364484675) - (dsp.const126))
        dsp.const152 = (dsp.const126) + (7.621731298870603)
        dsp.const153 = (2.0) * ((7.621731298870603) - (dsp.const126))
        dsp.const154 = (1.0) / ((((dsp.const122) + (0.168404871113589)) / (dsp.const121)) + (1.069358407707312))
        dsp.const155 = (((dsp.const122) + (-0.168404871113589)) / (dsp.const121)) + (1.069358407707312)
        dsp.const156 = (2.0) * ((1.069358407707312) - (dsp.const126))
        dsp.const157 = (dsp.const126) + (53.53615295455673)
        dsp.const158 = (2.0) * ((53.53615295455673) - (dsp.const126))
        dsp.const159 = tan((7916.317428905746) / (dsp.const0))
        dsp.const160 = (1.0) / (dsp.const159)
        dsp.const161 = (1.0) / ((((dsp.const160) + (3.1897274020965583)) / (dsp.const159)) + (4.076781969643807))
        dsp.const162 = (((dsp.const160) + (-3.1897274020965583)) / (dsp.const159)) + (4.076781969643807)
        dsp.const163 = pow_unrolled[2](dsp.const159)
        dsp.const164 = (1.0) / (dsp.const163)
        dsp.const165 = (2.0) * ((4.076781969643807) - (dsp.const164))
        dsp.const166 = (0.0017661728399818856) / (dsp.const163)
        dsp.const167 = (dsp.const166) + (0.00040767818495825777)
        dsp.const168 = (2.0) * ((0.00040767818495825777) - (dsp.const166))
        dsp.const169 = (1.0) / ((((dsp.const160) + (0.7431304601070396)) / (dsp.const159)) + (1.450071084655647))
        dsp.const170 = (((dsp.const160) + (-0.7431304601070396)) / (dsp.const159)) + (1.450071084655647)
        dsp.const171 = (2.0) * ((1.450071084655647) - (dsp.const164))
        dsp.const172 = (11.052052171507189) / (dsp.const163)
        dsp.const173 = (dsp.const172) + (1.450071084655647)
        dsp.const174 = (2.0) * ((1.450071084655647) - (dsp.const172))
        dsp.const175 = (1.0) / ((((dsp.const160) + (0.157482159302087)) / (dsp.const159)) + (0.9351401670315425))
        dsp.const176 = (((dsp.const160) + (-0.157482159302087)) / (dsp.const159)) + (0.9351401670315425)
        dsp.const177 = (2.0) * ((0.9351401670315425) - (dsp.const164))
        dsp.const178 = (50.063807016150385) / (dsp.const163)
        dsp.const179 = (dsp.const178) + (0.9351401670315425)
        dsp.const180 = (2.0) * ((0.9351401670315425) - (dsp.const178))
        dsp.const181 = (1.0) / ((((dsp.const160) + (0.782413046821645)) / (dsp.const159)) + (0.24529150870616))
        dsp.const182 = (((dsp.const160) + (-0.782413046821645)) / (dsp.const159)) + (0.24529150870616)
        dsp.const183 = (2.0) * ((0.24529150870616) - (dsp.const164))
        dsp.const184 = (9.9999997055e-05) / (dsp.const163)
        dsp.const185 = (dsp.const184) + (0.000433227200555)
        dsp.const186 = (2.0) * ((0.000433227200555) - (dsp.const184))
        dsp.const187 = (1.0) / ((((dsp.const160) + (0.512478641889141)) / (dsp.const159)) + (0.689621364484675))
        dsp.const188 = (((dsp.const160) + (-0.512478641889141)) / (dsp.const159)) + (0.689621364484675)
        dsp.const189 = (2.0) * ((0.689621364484675) - (dsp.const164))
        dsp.const190 = (dsp.const164) + (7.621731298870603)
        dsp.const191 = (2.0) * ((7.621731298870603) - (dsp.const164))
        dsp.const192 = (1.0) / ((((dsp.const160) + (0.168404871113589)) / (dsp.const159)) + (1.069358407707312))
        dsp.const193 = (((dsp.const160) + (-0.168404871113589)) / (dsp.const159)) + (1.069358407707312)
        dsp.const194 = (2.0) * ((1.069358407707312) - (dsp.const164))
        dsp.const195 = (dsp.const164) + (53.53615295455673)
        dsp.const196 = (2.0) * ((53.53615295455673) - (dsp.const164))
        dsp.const197 = tan((4986.967483164005) / (dsp.const0))
        dsp.const198 = (1.0) / (dsp.const197)
        dsp.const199 = (1.0) / ((((dsp.const198) + (3.1897274020965583)) / (dsp.const197)) + (4.076781969643807))
        dsp.const200 = (((dsp.const198) + (-3.1897274020965583)) / (dsp.const197)) + (4.076781969643807)
        dsp.const201 = pow_unrolled[2](dsp.const197)
        dsp.const202 = (1.0) / (dsp.const201)
        dsp.const203 = (2.0) * ((4.076781969643807) - (dsp.const202))
        dsp.const204 = (0.0017661728399818856) / (dsp.const201)
        dsp.const205 = (dsp.const204) + (0.00040767818495825777)
        dsp.const206 = (2.0) * ((0.00040767818495825777) - (dsp.const204))
        dsp.const207 = (1.0) / ((((dsp.const198) + (0.7431304601070396)) / (dsp.const197)) + (1.450071084655647))
        dsp.const208 = (((dsp.const198) + (-0.7431304601070396)) / (dsp.const197)) + (1.450071084655647)
        dsp.const209 = (2.0) * ((1.450071084655647) - (dsp.const202))
        dsp.const210 = (11.052052171507189) / (dsp.const201)
        dsp.const211 = (dsp.const210) + (1.450071084655647)
        dsp.const212 = (2.0) * ((1.450071084655647) - (dsp.const210))
        dsp.const213 = (1.0) / ((((dsp.const198) + (0.157482159302087)) / (dsp.const197)) + (0.9351401670315425))
        dsp.const214 = (((dsp.const198) + (-0.157482159302087)) / (dsp.const197)) + (0.9351401670315425)
        dsp.const215 = (2.0) * ((0.9351401670315425) - (dsp.const202))
        dsp.const216 = (50.063807016150385) / (dsp.const201)
        dsp.const217 = (dsp.const216) + (0.9351401670315425)
        dsp.const218 = (2.0) * ((0.9351401670315425) - (dsp.const216))
        dsp.const219 = (1.0) / ((((dsp.const198) + (0.782413046821645)) / (dsp.const197)) + (0.24529150870616))
        dsp.const220 = (((dsp.const198) + (-0.782413046821645)) / (dsp.const197)) + (0.24529150870616)
        dsp.const221 = (2.0) * ((0.24529150870616) - (dsp.const202))
        dsp.const222 = (9.9999997055e-05) / (dsp.const201)
        dsp.const223 = (dsp.const222) + (0.000433227200555)
        dsp.const224 = (2.0) * ((0.000433227200555) - (dsp.const222))
        dsp.const225 = (1.0) / ((((dsp.const198) + (0.512478641889141)) / (dsp.const197)) + (0.689621364484675))
        dsp.const226 = (((dsp.const198) + (-0.512478641889141)) / (dsp.const197)) + (0.689621364484675)
        dsp.const227 = (2.0) * ((0.689621364484675) - (dsp.const202))
        dsp.const228 = (dsp.const202) + (7.621731298870603)
        dsp.const229 = (2.0) * ((7.621731298870603) - (dsp.const202))
        dsp.const230 = (1.0) / ((((dsp.const198) + (0.168404871113589)) / (dsp.const197)) + (1.069358407707312))
        dsp.const231 = (((dsp.const198) + (-0.168404871113589)) / (dsp.const197)) + (1.069358407707312)
        dsp.const232 = (2.0) * ((1.069358407707312) - (dsp.const202))
        dsp.const233 = (dsp.const202) + (53.53615295455673)
        dsp.const234 = (2.0) * ((53.53615295455673) - (dsp.const202))
        dsp.const235 = tan((3141.592653589793) / (dsp.const0))
        dsp.const236 = (1.0) / (dsp.const235)
        dsp.const237 = (1.0) / ((((dsp.const236) + (3.1897274020965583)) / (dsp.const235)) + (4.076781969643807))
        dsp.const238 = (((dsp.const236) + (-3.1897274020965583)) / (dsp.const235)) + (4.076781969643807)
        dsp.const239 = pow_unrolled[2](dsp.const235)
        dsp.const240 = (1.0) / (dsp.const239)
        dsp.const241 = (2.0) * ((4.076781969643807) - (dsp.const240))
        dsp.const242 = (0.0017661728399818856) / (dsp.const239)
        dsp.const243 = (dsp.const242) + (0.00040767818495825777)
        dsp.const244 = (2.0) * ((0.00040767818495825777) - (dsp.const242))
        dsp.const245 = (1.0) / ((((dsp.const236) + (0.7431304601070396)) / (dsp.const235)) + (1.450071084655647))
        dsp.const246 = (((dsp.const236) + (-0.7431304601070396)) / (dsp.const235)) + (1.450071084655647)
        dsp.const247 = (2.0) * ((1.450071084655647) - (dsp.const240))
        dsp.const248 = (11.052052171507189) / (dsp.const239)
        dsp.const249 = (dsp.const248) + (1.450071084655647)
        dsp.const250 = (2.0) * ((1.450071084655647) - (dsp.const248))
        dsp.const251 = (1.0) / ((((dsp.const236) + (0.157482159302087)) / (dsp.const235)) + (0.9351401670315425))
        dsp.const252 = (((dsp.const236) + (-0.157482159302087)) / (dsp.const235)) + (0.9351401670315425)
        dsp.const253 = (2.0) * ((0.9351401670315425) - (dsp.const240))
        dsp.const254 = (50.063807016150385) / (dsp.const239)
        dsp.const255 = (dsp.const254) + (0.9351401670315425)
        dsp.const256 = (2.0) * ((0.9351401670315425) - (dsp.const254))
        dsp.const257 = (1.0) / ((((dsp.const236) + (0.782413046821645)) / (dsp.const235)) + (0.24529150870616))
        dsp.const258 = (((dsp.const236) + (-0.782413046821645)) / (dsp.const235)) + (0.24529150870616)
        dsp.const259 = (2.0) * ((0.24529150870616) - (dsp.const240))
        dsp.const260 = (9.9999997055e-05) / (dsp.const239)
        dsp.const261 = (dsp.const260) + (0.000433227200555)
        dsp.const262 = (2.0) * ((0.000433227200555) - (dsp.const260))
        dsp.const263 = (1.0) / ((((dsp.const236) + (0.512478641889141)) / (dsp.const235)) + (0.689621364484675))
        dsp.const264 = (((dsp.const236) + (-0.512478641889141)) / (dsp.const235)) + (0.689621364484675)
        dsp.const265 = (2.0) * ((0.689621364484675) - (dsp.const240))
        dsp.const266 = (dsp.const240) + (7.621731298870603)
        dsp.const267 = (2.0) * ((7.621731298870603) - (dsp.const240))
        dsp.const268 = (1.0) / ((((dsp.const236) + (0.168404871113589)) / (dsp.const235)) + (1.069358407707312))
        dsp.const269 = (((dsp.const236) + (-0.168404871113589)) / (dsp.const235)) + (1.069358407707312)
        dsp.const270 = (2.0) * ((1.069358407707312) - (dsp.const240))
        dsp.const271 = (dsp.const240) + (53.53615295455673)
        dsp.const272 = (2.0) * ((53.53615295455673) - (dsp.const240))
        dsp.const273 = tan((1979.079357226436) / (dsp.const0))
        dsp.const274 = (1.0) / (dsp.const273)
        dsp.const275 = (1.0) / ((((dsp.const274) + (3.1897274020965583)) / (dsp.const273)) + (4.076781969643807))
        dsp.const276 = (((dsp.const274) + (-3.1897274020965583)) / (dsp.const273)) + (4.076781969643807)
        dsp.const277 = pow_unrolled[2](dsp.const273)
        dsp.const278 = (1.0) / (dsp.const277)
        dsp.const279 = (2.0) * ((4.076781969643807) - (dsp.const278))
        dsp.const280 = (0.0017661728399818856) / (dsp.const277)
        dsp.const281 = (dsp.const280) + (0.00040767818495825777)
        dsp.const282 = (2.0) * ((0.00040767818495825777) - (dsp.const280))
        dsp.const283 = (1.0) / ((((dsp.const274) + (0.7431304601070396)) / (dsp.const273)) + (1.450071084655647))
        dsp.const284 = (((dsp.const274) + (-0.7431304601070396)) / (dsp.const273)) + (1.450071084655647)
        dsp.const285 = (2.0) * ((1.450071084655647) - (dsp.const278))
        dsp.const286 = (11.052052171507189) / (dsp.const277)
        dsp.const287 = (dsp.const286) + (1.450071084655647)
        dsp.const288 = (2.0) * ((1.450071084655647) - (dsp.const286))
        dsp.const289 = (1.0) / ((((dsp.const274) + (0.157482159302087)) / (dsp.const273)) + (0.9351401670315425))
        dsp.const290 = (((dsp.const274) + (-0.157482159302087)) / (dsp.const273)) + (0.9351401670315425)
        dsp.const291 = (2.0) * ((0.9351401670315425) - (dsp.const278))
        dsp.const292 = (50.063807016150385) / (dsp.const277)
        dsp.const293 = (dsp.const292) + (0.9351401670315425)
        dsp.const294 = (2.0) * ((0.9351401670315425) - (dsp.const292))
        dsp.const295 = (1.0) / ((((dsp.const274) + (0.782413046821645)) / (dsp.const273)) + (0.24529150870616))
        dsp.const296 = (((dsp.const274) + (-0.782413046821645)) / (dsp.const273)) + (0.24529150870616)
        dsp.const297 = (2.0) * ((0.24529150870616) - (dsp.const278))
        dsp.const298 = (9.9999997055e-05) / (dsp.const277)
        dsp.const299 = (dsp.const298) + (0.000433227200555)
        dsp.const300 = (2.0) * ((0.000433227200555) - (dsp.const298))
        dsp.const301 = (1.0) / ((((dsp.const274) + (0.512478641889141)) / (dsp.const273)) + (0.689621364484675))
        dsp.const302 = (((dsp.const274) + (-0.512478641889141)) / (dsp.const273)) + (0.689621364484675)
        dsp.const303 = (2.0) * ((0.689621364484675) - (dsp.const278))
        dsp.const304 = (dsp.const278) + (7.621731298870603)
        dsp.const305 = (2.0) * ((7.621731298870603) - (dsp.const278))
        dsp.const306 = (1.0) / ((((dsp.const274) + (0.168404871113589)) / (dsp.const273)) + (1.069358407707312))
        dsp.const307 = (((dsp.const274) + (-0.168404871113589)) / (dsp.const273)) + (1.069358407707312)
        dsp.const308 = (2.0) * ((1.069358407707312) - (dsp.const278))
        dsp.const309 = (dsp.const278) + (53.53615295455673)
        dsp.const310 = (2.0) * ((53.53615295455673) - (dsp.const278))
        dsp.const311 = tan((1246.7418707910015) / (dsp.const0))
        dsp.const312 = (1.0) / (dsp.const311)
        dsp.const313 = (1.0) / ((((dsp.const312) + (3.1897274020965583)) / (dsp.const311)) + (4.076781969643807))
        dsp.const314 = (((dsp.const312) + (-3.1897274020965583)) / (dsp.const311)) + (4.076781969643807)
        dsp.const315 = pow_unrolled[2](dsp.const311)
        dsp.const316 = (1.0) / (dsp.const315)
        dsp.const317 = (2.0) * ((4.076781969643807) - (dsp.const316))
        dsp.const318 = (0.0017661728399818856) / (dsp.const315)
        dsp.const319 = (dsp.const318) + (0.00040767818495825777)
        dsp.const320 = (2.0) * ((0.00040767818495825777) - (dsp.const318))
        dsp.const321 = (1.0) / ((((dsp.const312) + (0.7431304601070396)) / (dsp.const311)) + (1.450071084655647))
        dsp.const322 = (((dsp.const312) + (-0.7431304601070396)) / (dsp.const311)) + (1.450071084655647)
        dsp.const323 = (2.0) * ((1.450071084655647) - (dsp.const316))
        dsp.const324 = (11.052052171507189) / (dsp.const315)
        dsp.const325 = (dsp.const324) + (1.450071084655647)
        dsp.const326 = (2.0) * ((1.450071084655647) - (dsp.const324))
        dsp.const327 = (1.0) / ((((dsp.const312) + (0.157482159302087)) / (dsp.const311)) + (0.9351401670315425))
        dsp.const328 = (((dsp.const312) + (-0.157482159302087)) / (dsp.const311)) + (0.9351401670315425)
        dsp.const329 = (2.0) * ((0.9351401670315425) - (dsp.const316))
        dsp.const330 = (50.063807016150385) / (dsp.const315)
        dsp.const331 = (dsp.const330) + (0.9351401670315425)
        dsp.const332 = (2.0) * ((0.9351401670315425) - (dsp.const330))
        dsp.const333 = (1.0) / ((((dsp.const312) + (0.782413046821645)) / (dsp.const311)) + (0.24529150870616))
        dsp.const334 = (((dsp.const312) + (-0.782413046821645)) / (dsp.const311)) + (0.24529150870616)
        dsp.const335 = (2.0) * ((0.24529150870616) - (dsp.const316))
        dsp.const336 = (9.9999997055e-05) / (dsp.const315)
        dsp.const337 = (dsp.const336) + (0.000433227200555)
        dsp.const338 = (2.0) * ((0.000433227200555) - (dsp.const336))
        dsp.const339 = (1.0) / ((((dsp.const312) + (0.512478641889141)) / (dsp.const311)) + (0.689621364484675))
        dsp.const340 = (((dsp.const312) + (-0.512478641889141)) / (dsp.const311)) + (0.689621364484675)
        dsp.const341 = (2.0) * ((0.689621364484675) - (dsp.const316))
        dsp.const342 = (dsp.const316) + (7.621731298870603)
        dsp.const343 = (2.0) * ((7.621731298870603) - (dsp.const316))
        dsp.const344 = (1.0) / ((((dsp.const312) + (0.168404871113589)) / (dsp.const311)) + (1.069358407707312))
        dsp.const345 = (((dsp.const312) + (-0.168404871113589)) / (dsp.const311)) + (1.069358407707312)
        dsp.const346 = (2.0) * ((1.069358407707312) - (dsp.const316))
        dsp.const347 = (dsp.const316) + (53.53615295455673)
        dsp.const348 = (2.0) * ((53.53615295455673) - (dsp.const316))
        dsp.const349 = tan((785.3981633974482) / (dsp.const0))
        dsp.const350 = (1.0) / (dsp.const349)
        dsp.const351 = (1.0) / ((((dsp.const350) + (3.1897274020965583)) / (dsp.const349)) + (4.076781969643807))
        dsp.const352 = (((dsp.const350) + (-3.1897274020965583)) / (dsp.const349)) + (4.076781969643807)
        dsp.const353 = pow_unrolled[2](dsp.const349)
        dsp.const354 = (1.0) / (dsp.const353)
        dsp.const355 = (2.0) * ((4.076781969643807) - (dsp.const354))
        dsp.const356 = (0.0017661728399818856) / (dsp.const353)
        dsp.const357 = (dsp.const356) + (0.00040767818495825777)
        dsp.const358 = (2.0) * ((0.00040767818495825777) - (dsp.const356))
        dsp.const359 = (1.0) / ((((dsp.const350) + (0.7431304601070396)) / (dsp.const349)) + (1.450071084655647))
        dsp.const360 = (((dsp.const350) + (-0.7431304601070396)) / (dsp.const349)) + (1.450071084655647)
        dsp.const361 = (2.0) * ((1.450071084655647) - (dsp.const354))
        dsp.const362 = (11.052052171507189) / (dsp.const353)
        dsp.const363 = (dsp.const362) + (1.450071084655647)
        dsp.const364 = (2.0) * ((1.450071084655647) - (dsp.const362))
        dsp.const365 = (1.0) / ((((dsp.const350) + (0.157482159302087)) / (dsp.const349)) + (0.9351401670315425))
        dsp.const366 = (((dsp.const350) + (-0.157482159302087)) / (dsp.const349)) + (0.9351401670315425)
        dsp.const367 = (2.0) * ((0.9351401670315425) - (dsp.const354))
        dsp.const368 = (50.063807016150385) / (dsp.const353)
        dsp.const369 = (dsp.const368) + (0.9351401670315425)
        dsp.const370 = (2.0) * ((0.9351401670315425) - (dsp.const368))
        dsp.const371 = (1.0) / ((((dsp.const350) + (0.782413046821645)) / (dsp.const349)) + (0.24529150870616))
        dsp.const372 = (((dsp.const350) + (-0.782413046821645)) / (dsp.const349)) + (0.24529150870616)
        dsp.const373 = (2.0) * ((0.24529150870616) - (dsp.const354))
        dsp.const374 = (9.9999997055e-05) / (dsp.const353)
        dsp.const375 = (dsp.const374) + (0.000433227200555)
        dsp.const376 = (2.0) * ((0.000433227200555) - (dsp.const374))
        dsp.const377 = (1.0) / ((((dsp.const350) + (0.512478641889141)) / (dsp.const349)) + (0.689621364484675))
        dsp.const378 = (((dsp.const350) + (-0.512478641889141)) / (dsp.const349)) + (0.689621364484675)
        dsp.const379 = (2.0) * ((0.689621364484675) - (dsp.const354))
        dsp.const380 = (dsp.const354) + (7.621731298870603)
        dsp.const381 = (2.0) * ((7.621731298870603) - (dsp.const354))
        dsp.const382 = (1.0) / ((((dsp.const350) + (0.168404871113589)) / (dsp.const349)) + (1.069358407707312))
        dsp.const383 = (((dsp.const350) + (-0.168404871113589)) / (dsp.const349)) + (1.069358407707312)
        dsp.const384 = (2.0) * ((1.069358407707312) - (dsp.const354))
        dsp.const385 = (dsp.const354) + (53.53615295455673)
        dsp.const386 = (2.0) * ((53.53615295455673) - (dsp.const354))
        dsp.const387 = tan((494.769839306609) / (dsp.const0))
        dsp.const388 = (1.0) / (dsp.const387)
        dsp.const389 = (1.0) / ((((dsp.const388) + (3.1897274020965583)) / (dsp.const387)) + (4.076781969643807))
        dsp.const390 = (((dsp.const388) + (-3.1897274020965583)) / (dsp.const387)) + (4.076781969643807)
        dsp.const391 = pow_unrolled[2](dsp.const387)
        dsp.const392 = (1.0) / (dsp.const391)
        dsp.const393 = (2.0) * ((4.076781969643807) - (dsp.const392))
        dsp.const394 = (0.0017661728399818856) / (dsp.const391)
        dsp.const395 = (dsp.const394) + (0.00040767818495825777)
        dsp.const396 = (2.0) * ((0.00040767818495825777) - (dsp.const394))
        dsp.const397 = (1.0) / ((((dsp.const388) + (0.7431304601070396)) / (dsp.const387)) + (1.450071084655647))
        dsp.const398 = (((dsp.const388) + (-0.7431304601070396)) / (dsp.const387)) + (1.450071084655647)
        dsp.const399 = (2.0) * ((1.450071084655647) - (dsp.const392))
        dsp.const400 = (11.052052171507189) / (dsp.const391)
        dsp.const401 = (dsp.const400) + (1.450071084655647)
        dsp.const402 = (2.0) * ((1.450071084655647) - (dsp.const400))
        dsp.const403 = (1.0) / ((((dsp.const388) + (0.157482159302087)) / (dsp.const387)) + (0.9351401670315425))
        dsp.const404 = (((dsp.const388) + (-0.157482159302087)) / (dsp.const387)) + (0.9351401670315425)
        dsp.const405 = (2.0) * ((0.9351401670315425) - (dsp.const392))
        dsp.const406 = (50.063807016150385) / (dsp.const391)
        dsp.const407 = (dsp.const406) + (0.9351401670315425)
        dsp.const408 = (2.0) * ((0.9351401670315425) - (dsp.const406))
        dsp.const409 = (1.0) / ((((dsp.const388) + (0.782413046821645)) / (dsp.const387)) + (0.24529150870616))
        dsp.const410 = (((dsp.const388) + (-0.782413046821645)) / (dsp.const387)) + (0.24529150870616)
        dsp.const411 = (2.0) * ((0.24529150870616) - (dsp.const392))
        dsp.const412 = (9.9999997055e-05) / (dsp.const391)
        dsp.const413 = (dsp.const412) + (0.000433227200555)
        dsp.const414 = (2.0) * ((0.000433227200555) - (dsp.const412))
        dsp.const415 = (1.0) / ((((dsp.const388) + (0.512478641889141)) / (dsp.const387)) + (0.689621364484675))
        dsp.const416 = (((dsp.const388) + (-0.512478641889141)) / (dsp.const387)) + (0.689621364484675)
        dsp.const417 = (2.0) * ((0.689621364484675) - (dsp.const392))
        dsp.const418 = (dsp.const392) + (7.621731298870603)
        dsp.const419 = (2.0) * ((7.621731298870603) - (dsp.const392))
        dsp.const420 = (1.0) / ((((dsp.const388) + (0.168404871113589)) / (dsp.const387)) + (1.069358407707312))
        dsp.const421 = (((dsp.const388) + (-0.168404871113589)) / (dsp.const387)) + (1.069358407707312)
        dsp.const422 = (2.0) * ((1.069358407707312) - (dsp.const392))
        dsp.const423 = (dsp.const392) + (53.53615295455673)
        dsp.const424 = (2.0) * ((53.53615295455673) - (dsp.const392))
        dsp.const425 = tan((311.68546769775037) / (dsp.const0))
        dsp.const426 = (1.0) / (dsp.const425)
        dsp.const427 = (1.0) / ((((dsp.const426) + (3.1897274020965583)) / (dsp.const425)) + (4.076781969643807))
        dsp.const428 = (((dsp.const426) + (-3.1897274020965583)) / (dsp.const425)) + (4.076781969643807)
        dsp.const429 = pow_unrolled[2](dsp.const425)
        dsp.const430 = (1.0) / (dsp.const429)
        dsp.const431 = (2.0) * ((4.076781969643807) - (dsp.const430))
        dsp.const432 = (0.0017661728399818856) / (dsp.const429)
        dsp.const433 = (dsp.const432) + (0.00040767818495825777)
        dsp.const434 = (2.0) * ((0.00040767818495825777) - (dsp.const432))
        dsp.const435 = (1.0) / ((((dsp.const426) + (0.7431304601070396)) / (dsp.const425)) + (1.450071084655647))
        dsp.const436 = (((dsp.const426) + (-0.7431304601070396)) / (dsp.const425)) + (1.450071084655647)
        dsp.const437 = (2.0) * ((1.450071084655647) - (dsp.const430))
        dsp.const438 = (11.052052171507189) / (dsp.const429)
        dsp.const439 = (dsp.const438) + (1.450071084655647)
        dsp.const440 = (2.0) * ((1.450071084655647) - (dsp.const438))
        dsp.const441 = (1.0) / ((((dsp.const426) + (0.157482159302087)) / (dsp.const425)) + (0.9351401670315425))
        dsp.const442 = (((dsp.const426) + (-0.157482159302087)) / (dsp.const425)) + (0.9351401670315425)
        dsp.const443 = (2.0) * ((0.9351401670315425) - (dsp.const430))
        dsp.const444 = (50.063807016150385) / (dsp.const429)
        dsp.const445 = (dsp.const444) + (0.9351401670315425)
        dsp.const446 = (2.0) * ((0.9351401670315425) - (dsp.const444))
        dsp.const447 = (1.0) / ((((dsp.const426) + (0.782413046821645)) / (dsp.const425)) + (0.24529150870616))
        dsp.const448 = (((dsp.const426) + (-0.782413046821645)) / (dsp.const425)) + (0.24529150870616)
        dsp.const449 = (2.0) * ((0.24529150870616) - (dsp.const430))
        dsp.const450 = (9.9999997055e-05) / (dsp.const429)
        dsp.const451 = (dsp.const450) + (0.000433227200555)
        dsp.const452 = (2.0) * ((0.000433227200555) - (dsp.const450))
        dsp.const453 = (1.0) / ((((dsp.const426) + (0.512478641889141)) / (dsp.const425)) + (0.689621364484675))
        dsp.const454 = (((dsp.const426) + (-0.512478641889141)) / (dsp.const425)) + (0.689621364484675)
        dsp.const455 = (2.0) * ((0.689621364484675) - (dsp.const430))
        dsp.const456 = (dsp.const430) + (7.621731298870603)
        dsp.const457 = (2.0) * ((7.621731298870603) - (dsp.const430))
        dsp.const458 = (1.0) / ((((dsp.const426) + (0.168404871113589)) / (dsp.const425)) + (1.069358407707312))
        dsp.const459 = (((dsp.const426) + (-0.168404871113589)) / (dsp.const425)) + (1.069358407707312)
        dsp.const460 = (2.0) * ((1.069358407707312) - (dsp.const430))
        dsp.const461 = (dsp.const430) + (53.53615295455673)
        dsp.const462 = (2.0) * ((53.53615295455673) - (dsp.const430))
        dsp.const463 = tan((196.34954084936206) / (dsp.const0))
        dsp.const464 = (1.0) / (dsp.const463)
        dsp.const465 = (1.0) / ((((dsp.const464) + (3.1897274020965583)) / (dsp.const463)) + (4.076781969643807))
        dsp.const466 = (((dsp.const464) + (-3.1897274020965583)) / (dsp.const463)) + (4.076781969643807)
        dsp.const467 = pow_unrolled[2](dsp.const463)
        dsp.const468 = (1.0) / (dsp.const467)
        dsp.const469 = (2.0) * ((4.076781969643807) - (dsp.const468))
        dsp.const470 = (0.0017661728399818856) / (dsp.const467)
        dsp.const471 = (dsp.const470) + (0.00040767818495825777)
        dsp.const472 = (2.0) * ((0.00040767818495825777) - (dsp.const470))
        dsp.const473 = (1.0) / ((((dsp.const464) + (0.7431304601070396)) / (dsp.const463)) + (1.450071084655647))
        dsp.const474 = (((dsp.const464) + (-0.7431304601070396)) / (dsp.const463)) + (1.450071084655647)
        dsp.const475 = (2.0) * ((1.450071084655647) - (dsp.const468))
        dsp.const476 = (11.052052171507189) / (dsp.const467)
        dsp.const477 = (dsp.const476) + (1.450071084655647)
        dsp.const478 = (2.0) * ((1.450071084655647) - (dsp.const476))
        dsp.const479 = (1.0) / ((((dsp.const464) + (0.157482159302087)) / (dsp.const463)) + (0.9351401670315425))
        dsp.const480 = (((dsp.const464) + (-0.157482159302087)) / (dsp.const463)) + (0.9351401670315425)
        dsp.const481 = (2.0) * ((0.9351401670315425) - (dsp.const468))
        dsp.const482 = (50.063807016150385) / (dsp.const467)
        dsp.const483 = (dsp.const482) + (0.9351401670315425)
        dsp.const484 = (2.0) * ((0.9351401670315425) - (dsp.const482))
        dsp.const485 = (1.0) / ((((dsp.const464) + (0.782413046821645)) / (dsp.const463)) + (0.24529150870616))
        dsp.const486 = (((dsp.const464) + (-0.782413046821645)) / (dsp.const463)) + (0.24529150870616)
        dsp.const487 = (2.0) * ((0.24529150870616) - (dsp.const468))
        dsp.const488 = (9.9999997055e-05) / (dsp.const467)
        dsp.const489 = (dsp.const488) + (0.000433227200555)
        dsp.const490 = (2.0) * ((0.000433227200555) - (dsp.const488))
        dsp.const491 = (1.0) / ((((dsp.const464) + (0.512478641889141)) / (dsp.const463)) + (0.689621364484675))
        dsp.const492 = (((dsp.const464) + (-0.512478641889141)) / (dsp.const463)) + (0.689621364484675)
        dsp.const493 = (2.0) * ((0.689621364484675) - (dsp.const468))
        dsp.const494 = (dsp.const468) + (7.621731298870603)
        dsp.const495 = (2.0) * ((7.621731298870603) - (dsp.const468))
        dsp.const496 = (1.0) / ((((dsp.const464) + (0.168404871113589)) / (dsp.const463)) + (1.069358407707312))
        dsp.const497 = (((dsp.const464) + (-0.168404871113589)) / (dsp.const463)) + (1.069358407707312)
        dsp.const498 = (2.0) * ((1.069358407707312) - (dsp.const468))
        dsp.const499 = (dsp.const468) + (53.53615295455673)
        dsp.const500 = (2.0) * ((53.53615295455673) - (dsp.const468))
        dsp.const501 = tan((123.69245982665232) / (dsp.const0))
        dsp.const502 = (1.0) / (dsp.const501)
        dsp.const503 = (1.0) / ((((dsp.const502) + (3.1897274020965583)) / (dsp.const501)) + (4.076781969643807))
        dsp.const504 = (((dsp.const502) + (-3.1897274020965583)) / (dsp.const501)) + (4.076781969643807)
        dsp.const505 = pow_unrolled[2](dsp.const501)
        dsp.const506 = (1.0) / (dsp.const505)
        dsp.const507 = (2.0) * ((4.076781969643807) - (dsp.const506))
        dsp.const508 = (0.0017661728399818856) / (dsp.const505)
        dsp.const509 = (dsp.const508) + (0.00040767818495825777)
        dsp.const510 = (2.0) * ((0.00040767818495825777) - (dsp.const508))
        dsp.const511 = (1.0) / ((((dsp.const502) + (0.7431304601070396)) / (dsp.const501)) + (1.450071084655647))
        dsp.const512 = (((dsp.const502) + (-0.7431304601070396)) / (dsp.const501)) + (1.450071084655647)
        dsp.const513 = (2.0) * ((1.450071084655647) - (dsp.const506))
        dsp.const514 = (11.052052171507189) / (dsp.const505)
        dsp.const515 = (dsp.const514) + (1.450071084655647)
        dsp.const516 = (2.0) * ((1.450071084655647) - (dsp.const514))
        dsp.const517 = (1.0) / ((((dsp.const502) + (0.157482159302087)) / (dsp.const501)) + (0.9351401670315425))
        dsp.const518 = (((dsp.const502) + (-0.157482159302087)) / (dsp.const501)) + (0.9351401670315425)
        dsp.const519 = (2.0) * ((0.9351401670315425) - (dsp.const506))
        dsp.const520 = (50.063807016150385) / (dsp.const505)
        dsp.const521 = (dsp.const520) + (0.9351401670315425)
        dsp.const522 = (2.0) * ((0.9351401670315425) - (dsp.const520))
        dsp.const523 = (1.0) / ((((dsp.const502) + (0.782413046821645)) / (dsp.const501)) + (0.24529150870616))
        dsp.const524 = (((dsp.const502) + (-0.782413046821645)) / (dsp.const501)) + (0.24529150870616)
        dsp.const525 = (2.0) * ((0.24529150870616) - (dsp.const506))
        dsp.const526 = (9.9999997055e-05) / (dsp.const505)
        dsp.const527 = (dsp.const526) + (0.000433227200555)
        dsp.const528 = (2.0) * ((0.000433227200555) - (dsp.const526))
        dsp.const529 = (1.0) / ((((dsp.const502) + (0.512478641889141)) / (dsp.const501)) + (0.689621364484675))
        dsp.const530 = (((dsp.const502) + (-0.512478641889141)) / (dsp.const501)) + (0.689621364484675)
        dsp.const531 = (2.0) * ((0.689621364484675) - (dsp.const506))
        dsp.const532 = (dsp.const506) + (7.621731298870603)
        dsp.const533 = (2.0) * ((7.621731298870603) - (dsp.const506))
        dsp.const534 = (1.0) / ((((dsp.const502) + (0.168404871113589)) / (dsp.const501)) + (1.069358407707312))
        dsp.const535 = (((dsp.const502) + (-0.168404871113589)) / (dsp.const501)) + (1.069358407707312)
        dsp.const536 = (2.0) * ((1.069358407707312) - (dsp.const506))
        dsp.const537 = (dsp.const506) + (53.53615295455673)
        dsp.const538 = (2.0) * ((53.53615295455673) - (dsp.const506))

    @always_inline
    def instance_reset_user_interface(mut dsp) -> None:
        dsp.vslider0 = -20.0
        dsp.vslider1 = 0.1
        dsp.vslider2 = 49.0
        dsp.vslider3 = -0.1
        dsp.vslider4 = 0.1
        dsp.hslider0 = 10.0
        dsp.hslider1 = 100.0
        dsp.checkbox0 = 0.0
        dsp.checkbox1 = 0.0
        dsp.checkbox2 = 0.0
        dsp.entry0 = 2.0
        dsp.checkbox3 = 0.0
        dsp.hslider2 = 200.0
        dsp.hslider3 = -30.0
        dsp.checkbox4 = 0.0
        dsp.hslider4 = 50.0
        dsp.hslider5 = 500.0
        dsp.hslider6 = 5.0
        dsp.hslider7 = -30.0
        dsp.hslider8 = 40.0
        dsp.hslider9 = 100.0
        dsp.hslider10 = 50.0

    @always_inline
    def instance_clear(mut dsp) -> None:
        var l0 = S32(0)
        while (l0) < (S32(4)): 
            dsp.rec4_perm[l0] = 0.0
            l0 = (l0) + (S32(1))
        var l1 = S32(0)
        while (l1) < (S32(4)): 
            dsp.rec6_perm[l1] = 0.0
            l1 = (l1) + (S32(1))
        var l2 = S32(0)
        while (l2) < (S32(4)): 
            dsp.rec5_perm[l2] = 0.0
            l2 = (l2) + (S32(1))
        var l3 = S32(0)
        while (l3) < (S32(4)): 
            dsp.rec7_perm[l3] = 0.0
            l3 = (l3) + (S32(1))
        var l4 = S32(0)
        while (l4) < (S32(4)): 
            dsp.rec8_perm[l4] = 0.0
            l4 = (l4) + (S32(1))
        var l5 = S32(0)
        while (l5) < (S32(4)): 
            dsp.i_rec9_perm[l5] = S32(0)
            l5 = (l5) + (S32(1))
        var l6 = S32(0)
        while (l6) < (S32(4)): 
            dsp.rec10_perm[l6] = 0.0
            l6 = (l6) + (S32(1))
        var l7 = S32(0)
        while (l7) < (S32(4)): 
            dsp.i_vec0_perm[l7] = S32(0)
            l7 = (l7) + (S32(1))
        var l8 = S32(0)
        while (l8) < (S32(4)): 
            dsp.yec0_perm[l8] = 0.0
            l8 = (l8) + (S32(1))
        var l9 = S32(0)
        while (l9) < (S32(4)): 
            dsp.yec1_perm[l9] = 0.0
            l9 = (l9) + (S32(1))
        var l10 = S32(0)
        while (l10) < (S32(4)): 
            dsp.yec2_perm[l10] = 0.0
            l10 = (l10) + (S32(1))
        var l11 = S32(0)
        while (l11) < (S32(4)): 
            dsp.yec3_perm[l11] = 0.0
            l11 = (l11) + (S32(1))
        var l12 = S32(0)
        while (l12) < (S32(4)): 
            dsp.yec4_perm[l12] = 0.0
            l12 = (l12) + (S32(1))
        var l13 = S32(0)
        while (l13) < (S32(4)): 
            dsp.yec5_perm[l13] = 0.0
            l13 = (l13) + (S32(1))
        var l14 = S32(0)
        while (l14) < (S32(4)): 
            dsp.yec6_perm[l14] = 0.0
            l14 = (l14) + (S32(1))
        var l15 = S32(0)
        while (l15) < (S32(4)): 
            dsp.yec7_perm[l15] = 0.0
            l15 = (l15) + (S32(1))
        var l16 = S32(0)
        while (l16) < (S32(4)): 
            dsp.yec8_perm[l16] = 0.0
            l16 = (l16) + (S32(1))
        var l17 = S32(0)
        while (l17) < (S32(4)): 
            dsp.yec9_perm[l17] = 0.0
            l17 = (l17) + (S32(1))
        var l18 = S32(0)
        while (l18) < (S32(4)): 
            dsp.yec10_perm[l18] = 0.0
            l18 = (l18) + (S32(1))
        var l19 = S32(0)
        while (l19) < (S32(4)): 
            dsp.yec11_perm[l19] = 0.0
            l19 = (l19) + (S32(1))
        var l20 = S32(0)
        while (l20) < (S32(4)): 
            dsp.yec12_perm[l20] = 0.0
            l20 = (l20) + (S32(1))
        var l21 = S32(0)
        while (l21) < (S32(4)): 
            dsp.yec13_perm[l21] = 0.0
            l21 = (l21) + (S32(1))
        var l22 = S32(0)
        while (l22) < (S32(4)): 
            dsp.yec14_perm[l22] = 0.0
            l22 = (l22) + (S32(1))
        var l23 = S32(0)
        while (l23) < (S32(4)): 
            dsp.yec15_perm[l23] = 0.0
            l23 = (l23) + (S32(1))
        var l24 = S32(0)
        while (l24) < (S32(4)): 
            dsp.yec16_perm[l24] = 0.0
            l24 = (l24) + (S32(1))
        var l25 = S32(0)
        while (l25) < (S32(4)): 
            dsp.yec17_perm[l25] = 0.0
            l25 = (l25) + (S32(1))
        var l26 = S32(0)
        while (l26) < (S32(4)): 
            dsp.rec14_perm[l26] = 0.0
            l26 = (l26) + (S32(1))
        var l27 = S32(0)
        while (l27) < (S32(4)): 
            dsp.i_yec18_perm[l27] = S32(0)
            l27 = (l27) + (S32(1))
        var l28 = S32(0)
        while (l28) < (S32(4)): 
            dsp.i_rec15_perm[l28] = S32(0)
            l28 = (l28) + (S32(1))
        var l29 = S32(0)
        while (l29) < (S32(4)): 
            dsp.rec12_perm[l29] = 0.0
            l29 = (l29) + (S32(1))
        var l30 = S32(0)
        while (l30) < (S32(4)): 
            dsp.rec11_perm[l30] = 0.0
            l30 = (l30) + (S32(1))
        var l31 = S32(0)
        while (l31) < (S32(4)): 
            dsp.rec3_perm[l31] = 0.0
            l31 = (l31) + (S32(1))
        var l32 = S32(0)
        while (l32) < (S32(4)): 
            dsp.i_yec19_perm[l32] = S32(0)
            l32 = (l32) + (S32(1))
        var l33 = S32(0)
        while (l33) < (S32(4)): 
            dsp.i_rec16_perm[l33] = S32(0)
            l33 = (l33) + (S32(1))
        var l34 = S32(0)
        while (l34) < (S32(4)): 
            dsp.rec1_perm[l34] = 0.0
            l34 = (l34) + (S32(1))
        var l35 = S32(0)
        while (l35) < (S32(4)): 
            dsp.rec0_perm[l35] = 0.0
            l35 = (l35) + (S32(1))
        var l36 = S32(0)
        while (l36) < (S32(4)): 
            dsp.rec19_perm[l36] = 0.0
            l36 = (l36) + (S32(1))
        var l37 = S32(0)
        while (l37) < (S32(4)): 
            dsp.rec18_perm[l37] = 0.0
            l37 = (l37) + (S32(1))
        var l38 = S32(0)
        while (l38) < (S32(4)): 
            dsp.rec17_perm[l38] = 0.0
            l38 = (l38) + (S32(1))
        var l39 = S32(0)
        while (l39) < (S32(4)): 
            dsp.rec22_perm[l39] = 0.0
            l39 = (l39) + (S32(1))
        var l40 = S32(0)
        while (l40) < (S32(4)): 
            dsp.rec21_perm[l40] = 0.0
            l40 = (l40) + (S32(1))
        var l41 = S32(0)
        while (l41) < (S32(4)): 
            dsp.rec20_perm[l41] = 0.0
            l41 = (l41) + (S32(1))
        var l42 = S32(0)
        while (l42) < (S32(4)): 
            dsp.rec26_perm[l42] = 0.0
            l42 = (l42) + (S32(1))
        var l43 = S32(0)
        while (l43) < (S32(4)): 
            dsp.rec25_perm[l43] = 0.0
            l43 = (l43) + (S32(1))
        var l44 = S32(0)
        while (l44) < (S32(4)): 
            dsp.rec24_perm[l44] = 0.0
            l44 = (l44) + (S32(1))
        var l45 = S32(0)
        while (l45) < (S32(4)): 
            dsp.rec23_perm[l45] = 0.0
            l45 = (l45) + (S32(1))
        var l46 = S32(0)
        while (l46) < (S32(4)): 
            dsp.rec33_perm[l46] = 0.0
            l46 = (l46) + (S32(1))
        var l47 = S32(0)
        while (l47) < (S32(4)): 
            dsp.rec32_perm[l47] = 0.0
            l47 = (l47) + (S32(1))
        var l48 = S32(0)
        while (l48) < (S32(4)): 
            dsp.rec31_perm[l48] = 0.0
            l48 = (l48) + (S32(1))
        var l49 = S32(0)
        while (l49) < (S32(4)): 
            dsp.rec30_perm[l49] = 0.0
            l49 = (l49) + (S32(1))
        var l50 = S32(0)
        while (l50) < (S32(4)): 
            dsp.rec29_perm[l50] = 0.0
            l50 = (l50) + (S32(1))
        var l51 = S32(0)
        while (l51) < (S32(4)): 
            dsp.rec28_perm[l51] = 0.0
            l51 = (l51) + (S32(1))
        var l52 = S32(0)
        while (l52) < (S32(4)): 
            dsp.rec27_perm[l52] = 0.0
            l52 = (l52) + (S32(1))
        var l53 = S32(0)
        while (l53) < (S32(4)): 
            dsp.rec40_perm[l53] = 0.0
            l53 = (l53) + (S32(1))
        var l54 = S32(0)
        while (l54) < (S32(4)): 
            dsp.rec39_perm[l54] = 0.0
            l54 = (l54) + (S32(1))
        var l55 = S32(0)
        while (l55) < (S32(4)): 
            dsp.rec38_perm[l55] = 0.0
            l55 = (l55) + (S32(1))
        var l56 = S32(0)
        while (l56) < (S32(4)): 
            dsp.rec37_perm[l56] = 0.0
            l56 = (l56) + (S32(1))
        var l57 = S32(0)
        while (l57) < (S32(4)): 
            dsp.rec36_perm[l57] = 0.0
            l57 = (l57) + (S32(1))
        var l58 = S32(0)
        while (l58) < (S32(4)): 
            dsp.rec35_perm[l58] = 0.0
            l58 = (l58) + (S32(1))
        var l59 = S32(0)
        while (l59) < (S32(4)): 
            dsp.rec34_perm[l59] = 0.0
            l59 = (l59) + (S32(1))
        var l60 = S32(0)
        while (l60) < (S32(4)): 
            dsp.rec47_perm[l60] = 0.0
            l60 = (l60) + (S32(1))
        var l61 = S32(0)
        while (l61) < (S32(4)): 
            dsp.rec46_perm[l61] = 0.0
            l61 = (l61) + (S32(1))
        var l62 = S32(0)
        while (l62) < (S32(4)): 
            dsp.rec45_perm[l62] = 0.0
            l62 = (l62) + (S32(1))
        var l63 = S32(0)
        while (l63) < (S32(4)): 
            dsp.rec44_perm[l63] = 0.0
            l63 = (l63) + (S32(1))
        var l64 = S32(0)
        while (l64) < (S32(4)): 
            dsp.rec43_perm[l64] = 0.0
            l64 = (l64) + (S32(1))
        var l65 = S32(0)
        while (l65) < (S32(4)): 
            dsp.rec42_perm[l65] = 0.0
            l65 = (l65) + (S32(1))
        var l66 = S32(0)
        while (l66) < (S32(4)): 
            dsp.rec41_perm[l66] = 0.0
            l66 = (l66) + (S32(1))
        var l67 = S32(0)
        while (l67) < (S32(4)): 
            dsp.rec54_perm[l67] = 0.0
            l67 = (l67) + (S32(1))
        var l68 = S32(0)
        while (l68) < (S32(4)): 
            dsp.rec53_perm[l68] = 0.0
            l68 = (l68) + (S32(1))
        var l69 = S32(0)
        while (l69) < (S32(4)): 
            dsp.rec52_perm[l69] = 0.0
            l69 = (l69) + (S32(1))
        var l70 = S32(0)
        while (l70) < (S32(4)): 
            dsp.rec51_perm[l70] = 0.0
            l70 = (l70) + (S32(1))
        var l71 = S32(0)
        while (l71) < (S32(4)): 
            dsp.rec50_perm[l71] = 0.0
            l71 = (l71) + (S32(1))
        var l72 = S32(0)
        while (l72) < (S32(4)): 
            dsp.rec49_perm[l72] = 0.0
            l72 = (l72) + (S32(1))
        var l73 = S32(0)
        while (l73) < (S32(4)): 
            dsp.rec48_perm[l73] = 0.0
            l73 = (l73) + (S32(1))
        var l74 = S32(0)
        while (l74) < (S32(4)): 
            dsp.rec61_perm[l74] = 0.0
            l74 = (l74) + (S32(1))
        var l75 = S32(0)
        while (l75) < (S32(4)): 
            dsp.rec60_perm[l75] = 0.0
            l75 = (l75) + (S32(1))
        var l76 = S32(0)
        while (l76) < (S32(4)): 
            dsp.rec59_perm[l76] = 0.0
            l76 = (l76) + (S32(1))
        var l77 = S32(0)
        while (l77) < (S32(4)): 
            dsp.rec58_perm[l77] = 0.0
            l77 = (l77) + (S32(1))
        var l78 = S32(0)
        while (l78) < (S32(4)): 
            dsp.rec57_perm[l78] = 0.0
            l78 = (l78) + (S32(1))
        var l79 = S32(0)
        while (l79) < (S32(4)): 
            dsp.rec56_perm[l79] = 0.0
            l79 = (l79) + (S32(1))
        var l80 = S32(0)
        while (l80) < (S32(4)): 
            dsp.rec55_perm[l80] = 0.0
            l80 = (l80) + (S32(1))
        var l81 = S32(0)
        while (l81) < (S32(4)): 
            dsp.rec68_perm[l81] = 0.0
            l81 = (l81) + (S32(1))
        var l82 = S32(0)
        while (l82) < (S32(4)): 
            dsp.rec67_perm[l82] = 0.0
            l82 = (l82) + (S32(1))
        var l83 = S32(0)
        while (l83) < (S32(4)): 
            dsp.rec66_perm[l83] = 0.0
            l83 = (l83) + (S32(1))
        var l84 = S32(0)
        while (l84) < (S32(4)): 
            dsp.rec65_perm[l84] = 0.0
            l84 = (l84) + (S32(1))
        var l85 = S32(0)
        while (l85) < (S32(4)): 
            dsp.rec64_perm[l85] = 0.0
            l85 = (l85) + (S32(1))
        var l86 = S32(0)
        while (l86) < (S32(4)): 
            dsp.rec63_perm[l86] = 0.0
            l86 = (l86) + (S32(1))
        var l87 = S32(0)
        while (l87) < (S32(4)): 
            dsp.rec62_perm[l87] = 0.0
            l87 = (l87) + (S32(1))
        var l88 = S32(0)
        while (l88) < (S32(4)): 
            dsp.rec75_perm[l88] = 0.0
            l88 = (l88) + (S32(1))
        var l89 = S32(0)
        while (l89) < (S32(4)): 
            dsp.rec74_perm[l89] = 0.0
            l89 = (l89) + (S32(1))
        var l90 = S32(0)
        while (l90) < (S32(4)): 
            dsp.rec73_perm[l90] = 0.0
            l90 = (l90) + (S32(1))
        var l91 = S32(0)
        while (l91) < (S32(4)): 
            dsp.rec72_perm[l91] = 0.0
            l91 = (l91) + (S32(1))
        var l92 = S32(0)
        while (l92) < (S32(4)): 
            dsp.rec71_perm[l92] = 0.0
            l92 = (l92) + (S32(1))
        var l93 = S32(0)
        while (l93) < (S32(4)): 
            dsp.rec70_perm[l93] = 0.0
            l93 = (l93) + (S32(1))
        var l94 = S32(0)
        while (l94) < (S32(4)): 
            dsp.rec69_perm[l94] = 0.0
            l94 = (l94) + (S32(1))
        var l95 = S32(0)
        while (l95) < (S32(4)): 
            dsp.rec82_perm[l95] = 0.0
            l95 = (l95) + (S32(1))
        var l96 = S32(0)
        while (l96) < (S32(4)): 
            dsp.rec81_perm[l96] = 0.0
            l96 = (l96) + (S32(1))
        var l97 = S32(0)
        while (l97) < (S32(4)): 
            dsp.rec80_perm[l97] = 0.0
            l97 = (l97) + (S32(1))
        var l98 = S32(0)
        while (l98) < (S32(4)): 
            dsp.rec79_perm[l98] = 0.0
            l98 = (l98) + (S32(1))
        var l99 = S32(0)
        while (l99) < (S32(4)): 
            dsp.rec78_perm[l99] = 0.0
            l99 = (l99) + (S32(1))
        var l100 = S32(0)
        while (l100) < (S32(4)): 
            dsp.rec77_perm[l100] = 0.0
            l100 = (l100) + (S32(1))
        var l101 = S32(0)
        while (l101) < (S32(4)): 
            dsp.rec76_perm[l101] = 0.0
            l101 = (l101) + (S32(1))
        var l102 = S32(0)
        while (l102) < (S32(4)): 
            dsp.rec89_perm[l102] = 0.0
            l102 = (l102) + (S32(1))
        var l103 = S32(0)
        while (l103) < (S32(4)): 
            dsp.rec88_perm[l103] = 0.0
            l103 = (l103) + (S32(1))
        var l104 = S32(0)
        while (l104) < (S32(4)): 
            dsp.rec87_perm[l104] = 0.0
            l104 = (l104) + (S32(1))
        var l105 = S32(0)
        while (l105) < (S32(4)): 
            dsp.rec86_perm[l105] = 0.0
            l105 = (l105) + (S32(1))
        var l106 = S32(0)
        while (l106) < (S32(4)): 
            dsp.rec85_perm[l106] = 0.0
            l106 = (l106) + (S32(1))
        var l107 = S32(0)
        while (l107) < (S32(4)): 
            dsp.rec84_perm[l107] = 0.0
            l107 = (l107) + (S32(1))
        var l108 = S32(0)
        while (l108) < (S32(4)): 
            dsp.rec83_perm[l108] = 0.0
            l108 = (l108) + (S32(1))
        var l109 = S32(0)
        while (l109) < (S32(4)): 
            dsp.rec96_perm[l109] = 0.0
            l109 = (l109) + (S32(1))
        var l110 = S32(0)
        while (l110) < (S32(4)): 
            dsp.rec95_perm[l110] = 0.0
            l110 = (l110) + (S32(1))
        var l111 = S32(0)
        while (l111) < (S32(4)): 
            dsp.rec94_perm[l111] = 0.0
            l111 = (l111) + (S32(1))
        var l112 = S32(0)
        while (l112) < (S32(4)): 
            dsp.rec93_perm[l112] = 0.0
            l112 = (l112) + (S32(1))
        var l113 = S32(0)
        while (l113) < (S32(4)): 
            dsp.rec92_perm[l113] = 0.0
            l113 = (l113) + (S32(1))
        var l114 = S32(0)
        while (l114) < (S32(4)): 
            dsp.rec91_perm[l114] = 0.0
            l114 = (l114) + (S32(1))
        var l115 = S32(0)
        while (l115) < (S32(4)): 
            dsp.rec90_perm[l115] = 0.0
            l115 = (l115) + (S32(1))
        var l116 = S32(0)
        while (l116) < (S32(4)): 
            dsp.rec103_perm[l116] = 0.0
            l116 = (l116) + (S32(1))
        var l117 = S32(0)
        while (l117) < (S32(4)): 
            dsp.rec102_perm[l117] = 0.0
            l117 = (l117) + (S32(1))
        var l118 = S32(0)
        while (l118) < (S32(4)): 
            dsp.rec101_perm[l118] = 0.0
            l118 = (l118) + (S32(1))
        var l119 = S32(0)
        while (l119) < (S32(4)): 
            dsp.rec100_perm[l119] = 0.0
            l119 = (l119) + (S32(1))
        var l120 = S32(0)
        while (l120) < (S32(4)): 
            dsp.rec99_perm[l120] = 0.0
            l120 = (l120) + (S32(1))
        var l121 = S32(0)
        while (l121) < (S32(4)): 
            dsp.rec98_perm[l121] = 0.0
            l121 = (l121) + (S32(1))
        var l122 = S32(0)
        while (l122) < (S32(4)): 
            dsp.rec97_perm[l122] = 0.0
            l122 = (l122) + (S32(1))
        var l123 = S32(0)
        while (l123) < (S32(4)): 
            dsp.rec110_perm[l123] = 0.0
            l123 = (l123) + (S32(1))
        var l124 = S32(0)
        while (l124) < (S32(4)): 
            dsp.rec109_perm[l124] = 0.0
            l124 = (l124) + (S32(1))
        var l125 = S32(0)
        while (l125) < (S32(4)): 
            dsp.rec108_perm[l125] = 0.0
            l125 = (l125) + (S32(1))
        var l126 = S32(0)
        while (l126) < (S32(4)): 
            dsp.rec107_perm[l126] = 0.0
            l126 = (l126) + (S32(1))
        var l127 = S32(0)
        while (l127) < (S32(4)): 
            dsp.rec106_perm[l127] = 0.0
            l127 = (l127) + (S32(1))
        var l128 = S32(0)
        while (l128) < (S32(4)): 
            dsp.rec105_perm[l128] = 0.0
            l128 = (l128) + (S32(1))
        var l129 = S32(0)
        while (l129) < (S32(4)): 
            dsp.rec104_perm[l129] = 0.0
            l129 = (l129) + (S32(1))
        var l130 = S32(0)
        while (l130) < (S32(4)): 
            dsp.rec117_perm[l130] = 0.0
            l130 = (l130) + (S32(1))
        var l131 = S32(0)
        while (l131) < (S32(4)): 
            dsp.rec116_perm[l131] = 0.0
            l131 = (l131) + (S32(1))
        var l132 = S32(0)
        while (l132) < (S32(4)): 
            dsp.rec115_perm[l132] = 0.0
            l132 = (l132) + (S32(1))
        var l133 = S32(0)
        while (l133) < (S32(4)): 
            dsp.rec114_perm[l133] = 0.0
            l133 = (l133) + (S32(1))
        var l134 = S32(0)
        while (l134) < (S32(4)): 
            dsp.rec113_perm[l134] = 0.0
            l134 = (l134) + (S32(1))
        var l135 = S32(0)
        while (l135) < (S32(4)): 
            dsp.rec112_perm[l135] = 0.0
            l135 = (l135) + (S32(1))
        var l136 = S32(0)
        while (l136) < (S32(4)): 
            dsp.rec111_perm[l136] = 0.0
            l136 = (l136) + (S32(1))
        var l137 = S32(0)
        while (l137) < (S32(4)): 
            dsp.rec121_perm[l137] = 0.0
            l137 = (l137) + (S32(1))
        var l138 = S32(0)
        while (l138) < (S32(4)): 
            dsp.rec120_perm[l138] = 0.0
            l138 = (l138) + (S32(1))
        var l139 = S32(0)
        while (l139) < (S32(4)): 
            dsp.rec119_perm[l139] = 0.0
            l139 = (l139) + (S32(1))
        var l140 = S32(0)
        while (l140) < (S32(4)): 
            dsp.rec118_perm[l140] = 0.0
            l140 = (l140) + (S32(1))

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
        return "{\"name\": \"gate_compressor\",\"filename\": \"gate_compressor.dsp\",\"version\": \"2.85.5\",\"compile_options\": \"-a impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs\",\"library_list\": [\"/usr/local/share/faust/oscillator.lib\",\"/usr/local/share/faust/music.lib\",\"/usr/local/share/faust/math.lib\",\"/usr/local/share/faust/filter.lib\",\"/usr/local/share/faust/effect.lib\"],\"include_pathnames\": [\"/Users/manuelfarzini/Personal/dev/repo/faust/build/share/faust\",\"/usr/local/share/faust\",\"/usr/share/faust\",\"src\",\"/Users/manuelfarzini/Personal/dev/repo/faust/architecture/mojo/src\"],\"size\": 9044,\"inputs\": 1,\"outputs\": 2,\"meta\": [ { \"compile_options\": \"-a impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs\" },{ \"effect.lib/author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"effect.lib/copyright\": \"Julius O. Smith III\" },{ \"effect.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"effect.lib/exciter_author\": \"Priyanka Shekar (pshekar@ccrma.stanford.edu)\" },{ \"effect.lib/exciter_copyright\": \"Copyright (c) 2013 Priyanka Shekar\" },{ \"effect.lib/exciter_license\": \"MIT License (MIT)\" },{ \"effect.lib/exciter_name\": \"Harmonic Exciter\" },{ \"effect.lib/exciter_version\": \"1.0\" },{ \"effect.lib/license\": \"STK-4.3\" },{ \"effect.lib/name\": \"Faust Audio Effect Library\" },{ \"effect.lib/version\": \"1.33\" },{ \"filename\": \"gate_compressor.dsp\" },{ \"filter.lib/author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"filter.lib/copyright\": \"Julius O. Smith III\" },{ \"filter.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"filter.lib/license\": \"STK-4.3\" },{ \"filter.lib/name\": \"Faust Filter Library\" },{ \"filter.lib/reference\": \"https://ccrma.stanford.edu/~jos/filters/\" },{ \"filter.lib/version\": \"1.29\" },{ \"math.lib/author\": \"GRAME\" },{ \"math.lib/copyright\": \"GRAME\" },{ \"math.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"math.lib/license\": \"LGPL with exception\" },{ \"math.lib/name\": \"Math Library\" },{ \"math.lib/version\": \"1.0\" },{ \"music.lib/author\": \"GRAME\" },{ \"music.lib/copyright\": \"GRAME\" },{ \"music.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"music.lib/license\": \"LGPL with exception\" },{ \"music.lib/name\": \"Music Library\" },{ \"music.lib/version\": \"1.0\" },{ \"name\": \"gate_compressor\" },{ \"oscillator.lib/author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"oscillator.lib/copyright\": \"Julius O. Smith III\" },{ \"oscillator.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"oscillator.lib/license\": \"STK-4.3\" },{ \"oscillator.lib/name\": \"Faust Oscillator Library\" },{ \"oscillator.lib/version\": \"1.11\" }],\"ui\": [ {\"type\": \"vgroup\",\"label\": \"gate_compressor\",\"items\": [ {\"type\": \"vgroup\",\"label\": \"sawtooth\",\"meta\": [{ \"1\": \"\" }],\"items\": [ {\"type\": \"vgroup\",\"label\": \"SAWTOOTH OSCILLATOR\",\"meta\": [{ \"0\": \"\" },{ \"tooltip\": \"See Faust\'s oscillator.lib for documentation and references\" }],\"items\": [ {\"type\": \"hgroup\",\"label\": \"0x00\",\"meta\": [{ \"1\": \"\" }],\"items\": [ {\"type\": \"vslider\",\"label\": \"Amplitude\",\"varname\": \"fVslider0\",\"shortname\": \"Amplitude\",\"address\": \"/gate_compressor/sawtooth/SAWTOOTH_OSCILLATOR/0x00/Amplitude\",\"meta\": [{ \"1\": \"\" },{ \"style\": \"knob\" },{ \"tooltip\": \"Sawtooth waveform amplitude\" },{ \"unit\": \"dB\" }],\"init\": -20,\"min\": -120,\"max\": 10,\"step\": 0.1},{\"type\": \"vslider\",\"label\": \"Frequency\",\"varname\": \"fVslider2\",\"shortname\": \"Frequency\",\"address\": \"/gate_compressor/sawtooth/SAWTOOTH_OSCILLATOR/0x00/Frequency\",\"meta\": [{ \"2\": \"\" },{ \"style\": \"knob\" },{ \"tooltip\": \"Sawtooth frequency as a Piano Key (PK) number (A440 = key 49)\" },{ \"unit\": \"PK\" }],\"init\": 49,\"min\": 1,\"max\": 88,\"step\": 0.01},{\"type\": \"vslider\",\"label\": \"Detuning 1\",\"varname\": \"fVslider3\",\"shortname\": \"Detuning_1\",\"address\": \"/gate_compressor/sawtooth/SAWTOOTH_OSCILLATOR/0x00/Detuning_1\",\"meta\": [{ \"3\": \"\" },{ \"style\": \"knob\" },{ \"tooltip\": \"Percentage frequency-shift up or down for second oscillator\" },{ \"unit\": \"%%\" }],\"init\": -0.1,\"min\": -10,\"max\": 10,\"step\": 0.01},{\"type\": \"vslider\",\"label\": \"Detuning 2\",\"varname\": \"fVslider4\",\"shortname\": \"Detuning_2\",\"address\": \"/gate_compressor/sawtooth/SAWTOOTH_OSCILLATOR/0x00/Detuning_2\",\"meta\": [{ \"4\": \"\" },{ \"style\": \"knob\" },{ \"tooltip\": \"Percentage frequency-shift up or down for third detuned oscillator\" },{ \"unit\": \"%%\" }],\"init\": 0.1,\"min\": -10,\"max\": 10,\"step\": 0.01},{\"type\": \"vslider\",\"label\": \"Portamento\",\"varname\": \"fVslider1\",\"shortname\": \"Portamento\",\"address\": \"/gate_compressor/sawtooth/SAWTOOTH_OSCILLATOR/0x00/Portamento\",\"meta\": [{ \"5\": \"\" },{ \"scale\": \"log\" },{ \"style\": \"knob\" },{ \"tooltip\": \"Portamento (frequency-glide) time-constant in seconds\" },{ \"unit\": \"sec\" }],\"init\": 0.1,\"min\": 0.001,\"max\": 10,\"step\": 0.001},{\"type\": \"nentry\",\"label\": \"Saw Order\",\"varname\": \"fEntry0\",\"shortname\": \"Saw_Order\",\"address\": \"/gate_compressor/sawtooth/SAWTOOTH_OSCILLATOR/0x00/Saw_Order\",\"meta\": [{ \"6\": \"\" },{ \"tooltip\": \"Order of sawtootn aliasing suppression\" }],\"init\": 2,\"min\": 1,\"max\": 4,\"step\": 1},{\"type\": \"vgroup\",\"label\": \"Alternate Signals\",\"meta\": [{ \"7\": \"\" }],\"items\": [ {\"type\": \"checkbox\",\"label\": \"Noise (White or Pink - uses only Amplitude control on the left)\",\"varname\": \"fCheckbox2\",\"shortname\": \"Noise_White_or_Pink_uses_only_Amplitude_control_on_the_left\",\"address\": \"/gate_compressor/sawtooth/SAWTOOTH_OSCILLATOR/0x00/Alternate_Signals/Noise__White_or_Pink_-_uses_only_Amplitude_control_on_the_left_\",\"meta\": [{ \"0\": \"\" }]},{\"type\": \"checkbox\",\"label\": \"Pink instead of White Noise (also called 1/f Noise)\",\"varname\": \"fCheckbox3\",\"shortname\": \"Pink_instead_of_White_Noise_also_called_1_f_Noise\",\"address\": \"/gate_compressor/sawtooth/SAWTOOTH_OSCILLATOR/0x00/Alternate_Signals/Pink_instead_of_White_Noise__also_called_1_f_Noise_\",\"meta\": [{ \"1\": \"\" },{ \"tooltip\": \"Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the same total power in every octave\" }]},{\"type\": \"checkbox\",\"label\": \"External Signal Input (overrides Sawtooth/Noise selection above)\",\"varname\": \"fCheckbox1\",\"shortname\": \"External_Signal_Input_overrides_Sawtooth_Noise_selection_above\",\"address\": \"/gate_compressor/sawtooth/SAWTOOTH_OSCILLATOR/0x00/Alternate_Signals/External_Signal_Input__overrides_Sawtooth_Noise_selection_above_\",\"meta\": [{ \"2\": \"\" }]}]}]}]}]},{\"type\": \"vgroup\",\"label\": \"gate\",\"meta\": [{ \"2\": \"\" }],\"items\": [ {\"type\": \"vgroup\",\"label\": \"GATE\",\"meta\": [{ \"tooltip\": \"Reference: http://en.wikipedia.org/wiki/Noise_gate\" }],\"items\": [ {\"type\": \"hgroup\",\"label\": \"0x00\",\"meta\": [{ \"0\": \"\" }],\"items\": [ {\"type\": \"checkbox\",\"label\": \"Bypass\",\"varname\": \"fCheckbox0\",\"shortname\": \"GATE_Bypass\",\"address\": \"/gate_compressor/gate/GATE/0x00/Bypass\",\"meta\": [{ \"0\": \"\" },{ \"tooltip\": \"When this is checked, the gate has no effect\" }]},{\"type\": \"hbargraph\",\"label\": \"Gate Gain\",\"varname\": \"fHbargraph0\",\"shortname\": \"Gate_Gain\",\"address\": \"/gate_compressor/gate/GATE/0x00/Gate_Gain\",\"meta\": [{ \"1\": \"\" },{ \"tooltip\": \"Current gain of the gate in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10}]},{\"type\": \"hgroup\",\"label\": \"0x00\",\"meta\": [{ \"1\": \"\" }],\"items\": [ {\"type\": \"hslider\",\"label\": \"Threshold\",\"varname\": \"fHslider3\",\"shortname\": \"GATE_Threshold\",\"address\": \"/gate_compressor/gate/GATE/0x00/Threshold\",\"meta\": [{ \"1\": \"\" },{ \"style\": \"knob\" },{ \"tooltip\": \"When the signal level falls below the Threshold (expressed in dB), the signal is muted\" },{ \"unit\": \"dB\" }],\"init\": -30,\"min\": -120,\"max\": 0,\"step\": 0.1},{\"type\": \"hslider\",\"label\": \"Attack\",\"varname\": \"fHslider0\",\"shortname\": \"GATE_Attack\",\"address\": \"/gate_compressor/gate/GATE/0x00/Attack\",\"meta\": [{ \"2\": \"\" },{ \"scale\": \"log\" },{ \"style\": \"knob\" },{ \"tooltip\": \"Time constant in MICROseconds (1/e smoothing time) for the gate gain to go (exponentially) from 0 (muted) to 1 (unmuted)\" },{ \"unit\": \"us\" }],\"init\": 10,\"min\": 10,\"max\": 10000,\"step\": 1},{\"type\": \"hslider\",\"label\": \"Hold\",\"varname\": \"fHslider2\",\"shortname\": \"Hold\",\"address\": \"/gate_compressor/gate/GATE/0x00/Hold\",\"meta\": [{ \"3\": \"\" },{ \"scale\": \"log\" },{ \"style\": \"knob\" },{ \"tooltip\": \"Time in ms to keep the gate open (no muting) after the signal level falls below the Threshold\" },{ \"unit\": \"ms\" }],\"init\": 200,\"min\": 1,\"max\": 1000,\"step\": 1},{\"type\": \"hslider\",\"label\": \"Release\",\"varname\": \"fHslider1\",\"shortname\": \"GATE_Release\",\"address\": \"/gate_compressor/gate/GATE/0x00/Release\",\"meta\": [{ \"4\": \"\" },{ \"scale\": \"log\" },{ \"style\": \"knob\" },{ \"tooltip\": \"Time constant in ms (1/e smoothing time) for the gain to go (exponentially) from 1 (unmuted) to 0 (muted)\" },{ \"unit\": \"ms\" }],\"init\": 100,\"min\": 1,\"max\": 1000,\"step\": 1}]}]}]},{\"type\": \"vgroup\",\"label\": \"compressor\",\"meta\": [{ \"3\": \"\" }],\"items\": [ {\"type\": \"vgroup\",\"label\": \"COMPRESSOR\",\"meta\": [{ \"tooltip\": \"Reference: http://en.wikipedia.org/wiki/Dynamic_range_compression\" }],\"items\": [ {\"type\": \"hgroup\",\"label\": \"0x00\",\"meta\": [{ \"0\": \"\" }],\"items\": [ {\"type\": \"checkbox\",\"label\": \"Bypass\",\"varname\": \"fCheckbox4\",\"shortname\": \"COMPRESSOR_Bypass\",\"address\": \"/gate_compressor/compressor/COMPRESSOR/0x00/Bypass\",\"meta\": [{ \"0\": \"\" },{ \"tooltip\": \"When this is checked, the compressor has no effect\" }]},{\"type\": \"hbargraph\",\"label\": \"Compressor Gain\",\"varname\": \"fHbargraph1\",\"shortname\": \"Compressor_Gain\",\"address\": \"/gate_compressor/compressor/COMPRESSOR/0x00/Compressor_Gain\",\"meta\": [{ \"1\": \"\" },{ \"tooltip\": \"Current gain of the compressor in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10}]},{\"type\": \"hgroup\",\"label\": \"0x00\",\"meta\": [{ \"1\": \"\" }],\"items\": [ {\"type\": \"hgroup\",\"label\": \"Compression Control\",\"meta\": [{ \"3\": \"\" }],\"items\": [ {\"type\": \"hslider\",\"label\": \"Ratio\",\"varname\": \"fHslider6\",\"shortname\": \"Ratio\",\"address\": \"/gate_compressor/compressor/COMPRESSOR/0x00/Compression_Control/Ratio\",\"meta\": [{ \"0\": \"\" },{ \"style\": \"knob\" },{ \"tooltip\": \"A compression Ratio of N means that for each N dB increase in input signal level above Threshold, the output level goes up 1 dB\" }],\"init\": 5,\"min\": 1,\"max\": 20,\"step\": 0.1},{\"type\": \"hslider\",\"label\": \"Threshold\",\"varname\": \"fHslider7\",\"shortname\": \"Compression_Control_Threshold\",\"address\": \"/gate_compressor/compressor/COMPRESSOR/0x00/Compression_Control/Threshold\",\"meta\": [{ \"1\": \"\" },{ \"style\": \"knob\" },{ \"tooltip\": \"When the signal level exceeds the Threshold (in dB), its level is compressed according to the Ratio\" },{ \"unit\": \"dB\" }],\"init\": -30,\"min\": -100,\"max\": 10,\"step\": 0.1}]},{\"type\": \"hgroup\",\"label\": \"Compression Response\",\"meta\": [{ \"4\": \"\" }],\"items\": [ {\"type\": \"hslider\",\"label\": \"Attack\",\"varname\": \"fHslider4\",\"shortname\": \"Compression_Response_Attack\",\"address\": \"/gate_compressor/compressor/COMPRESSOR/0x00/Compression_Response/Attack\",\"meta\": [{ \"1\": \"\" },{ \"scale\": \"log\" },{ \"style\": \"knob\" },{ \"tooltip\": \"Time constant in ms (1/e smoothing time) for the compression gain to approach (exponentially) a new lower target level (the compression `kicking in\')\" },{ \"unit\": \"ms\" }],\"init\": 50,\"min\": 1,\"max\": 1000,\"step\": 0.1},{\"type\": \"hslider\",\"label\": \"Release\",\"varname\": \"fHslider5\",\"shortname\": \"Compression_Response_Release\",\"address\": \"/gate_compressor/compressor/COMPRESSOR/0x00/Compression_Response/Release\",\"meta\": [{ \"2\": \"\" },{ \"scale\": \"log\" },{ \"style\": \"knob\" },{ \"tooltip\": \"Time constant in ms (1/e smoothing time) for the compression gain to approach (exponentially) a new higher target level (the compression \'releasing\')\" },{ \"unit\": \"ms\" }],\"init\": 500,\"min\": 1,\"max\": 1000,\"step\": 0.1}]}]},{\"type\": \"hslider\",\"label\": \"Makeup Gain\",\"varname\": \"fHslider8\",\"shortname\": \"Makeup_Gain\",\"address\": \"/gate_compressor/compressor/COMPRESSOR/Makeup_Gain\",\"meta\": [{ \"5\": \"\" },{ \"tooltip\": \"The compressed-signal output level is increased by this amount (in dB) to make up for the level lost due to compression\" },{ \"unit\": \"dB\" }],\"init\": 40,\"min\": -96,\"max\": 96,\"step\": 0.1}]}]},{\"type\": \"vgroup\",\"label\": \"spectral\",\"meta\": [{ \"4\": \"\" }],\"items\": [ {\"type\": \"hgroup\",\"label\": \"CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning LP, 9 octaves below 16000 Hz, HP\",\"meta\": [{ \"0\": \"\" },{ \"tooltip\": \"See Faust\'s filter.lib for documentation and references\" }],\"items\": [ {\"type\": \"vbargraph\",\"label\": \"vbargraph0\",\"varname\": \"fVbargraph14\",\"shortname\": \"vbargraph0\",\"address\": \"/gate_compressor/spectral/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph0\",\"meta\": [{ \"0\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph1\",\"varname\": \"fVbargraph13\",\"shortname\": \"vbargraph1\",\"address\": \"/gate_compressor/spectral/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph1\",\"meta\": [{ \"1\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph2\",\"varname\": \"fVbargraph12\",\"shortname\": \"vbargraph2\",\"address\": \"/gate_compressor/spectral/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph2\",\"meta\": [{ \"2\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph3\",\"varname\": \"fVbargraph11\",\"shortname\": \"vbargraph3\",\"address\": \"/gate_compressor/spectral/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph3\",\"meta\": [{ \"3\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph4\",\"varname\": \"fVbargraph10\",\"shortname\": \"vbargraph4\",\"address\": \"/gate_compressor/spectral/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph4\",\"meta\": [{ \"4\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph5\",\"varname\": \"fVbargraph9\",\"shortname\": \"vbargraph5\",\"address\": \"/gate_compressor/spectral/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph5\",\"meta\": [{ \"5\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph6\",\"varname\": \"fVbargraph8\",\"shortname\": \"vbargraph6\",\"address\": \"/gate_compressor/spectral/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph6\",\"meta\": [{ \"6\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph7\",\"varname\": \"fVbargraph7\",\"shortname\": \"vbargraph7\",\"address\": \"/gate_compressor/spectral/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph7\",\"meta\": [{ \"7\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph8\",\"varname\": \"fVbargraph6\",\"shortname\": \"vbargraph8\",\"address\": \"/gate_compressor/spectral/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph8\",\"meta\": [{ \"8\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph9\",\"varname\": \"fVbargraph5\",\"shortname\": \"vbargraph9\",\"address\": \"/gate_compressor/spectral/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph9\",\"meta\": [{ \"9\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph10\",\"varname\": \"fVbargraph4\",\"shortname\": \"vbargraph10\",\"address\": \"/gate_compressor/spectral/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph10\",\"meta\": [{ \"10\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph11\",\"varname\": \"fVbargraph3\",\"shortname\": \"vbargraph11\",\"address\": \"/gate_compressor/spectral/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph11\",\"meta\": [{ \"11\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph12\",\"varname\": \"fVbargraph2\",\"shortname\": \"vbargraph12\",\"address\": \"/gate_compressor/spectral/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph12\",\"meta\": [{ \"12\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph13\",\"varname\": \"fVbargraph1\",\"shortname\": \"vbargraph13\",\"address\": \"/gate_compressor/spectral/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph13\",\"meta\": [{ \"13\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph14\",\"varname\": \"fVbargraph0\",\"shortname\": \"vbargraph14\",\"address\": \"/gate_compressor/spectral/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph14\",\"meta\": [{ \"14\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10}]},{\"type\": \"hgroup\",\"label\": \"SPECTRUM ANALYZER CONTROLS\",\"meta\": [{ \"1\": \"\" }],\"items\": [ {\"type\": \"hslider\",\"label\": \"Level Averaging Time\",\"varname\": \"fHslider9\",\"shortname\": \"Level_Averaging_Time\",\"address\": \"/gate_compressor/spectral/SPECTRUM_ANALYZER_CONTROLS/Level_Averaging_Time\",\"meta\": [{ \"0\": \"\" },{ \"scale\": \"log\" },{ \"tooltip\": \"band-level averaging time in milliseconds\" },{ \"unit\": \"ms\" }],\"init\": 100,\"min\": 1,\"max\": 10000,\"step\": 1},{\"type\": \"hslider\",\"label\": \"Level dB Offset\",\"varname\": \"fHslider10\",\"shortname\": \"Level_dB_Offset\",\"address\": \"/gate_compressor/spectral/SPECTRUM_ANALYZER_CONTROLS/Level_dB_Offset\",\"meta\": [{ \"1\": \"\" },{ \"tooltip\": \"Level offset in decibels\" },{ \"unit\": \"dB\" }],\"init\": 50,\"min\": 0,\"max\": 100,\"step\": 1}]}]}]}]}"

    @always_inline
    def metadata(imm dsp, mut meta: Some[FaustMeta]) -> None:
        meta.declare("compile_options", "-a impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs")
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
        meta.declare("filename", "gate_compressor.dsp")
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
        meta.declare("name", "gate_compressor")
        meta.declare("oscillator.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)")
        meta.declare("oscillator.lib/copyright", "Julius O. Smith III")
        meta.declare("oscillator.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.")
        meta.declare("oscillator.lib/license", "STK-4.3")
        meta.declare("oscillator.lib/name", "Faust Oscillator Library")
        meta.declare("oscillator.lib/version", "1.11")

    @always_inline
    def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None:
        ui.open_vertical_box("gate_compressor")
        ui.declare(dsp.null_val, "1", "")
        ui.open_vertical_box("sawtooth")
        ui.declare(dsp.null_val, "0", "")
        ui.declare(dsp.null_val, "tooltip", "See Faust's oscillator.lib for documentation and references")
        ui.open_vertical_box("SAWTOOTH OSCILLATOR")
        ui.declare(dsp.null_val, "1", "")
        ui.open_horizontal_box("0x00")
        ui.declare(dsp.vslider0, "1", "")
        ui.declare(dsp.vslider0, "style", "knob")
        ui.declare(dsp.vslider0, "tooltip", "Sawtooth waveform amplitude")
        ui.declare(dsp.vslider0, "unit", "dB")
        ui.add_vertical_slider("Amplitude", dsp.vslider0, FaustFloat(-20.0), FaustFloat(-120.0), FaustFloat(10.0), FaustFloat(0.1))
        ui.declare(dsp.vslider2, "2", "")
        ui.declare(dsp.vslider2, "style", "knob")
        ui.declare(dsp.vslider2, "tooltip", "Sawtooth frequency as a Piano Key (PK) number (A440 = key 49)")
        ui.declare(dsp.vslider2, "unit", "PK")
        ui.add_vertical_slider("Frequency", dsp.vslider2, FaustFloat(49.0), FaustFloat(1.0), FaustFloat(88.0), FaustFloat(0.01))
        ui.declare(dsp.vslider3, "3", "")
        ui.declare(dsp.vslider3, "style", "knob")
        ui.declare(dsp.vslider3, "tooltip", "Percentage frequency-shift up or down for second oscillator")
        ui.declare(dsp.vslider3, "unit", "%%")
        ui.add_vertical_slider("Detuning 1", dsp.vslider3, FaustFloat(-0.1), FaustFloat(-10.0), FaustFloat(10.0), FaustFloat(0.01))
        ui.declare(dsp.vslider4, "4", "")
        ui.declare(dsp.vslider4, "style", "knob")
        ui.declare(dsp.vslider4, "tooltip", "Percentage frequency-shift up or down for third detuned oscillator")
        ui.declare(dsp.vslider4, "unit", "%%")
        ui.add_vertical_slider("Detuning 2", dsp.vslider4, FaustFloat(0.1), FaustFloat(-10.0), FaustFloat(10.0), FaustFloat(0.01))
        ui.declare(dsp.vslider1, "5", "")
        ui.declare(dsp.vslider1, "scale", "log")
        ui.declare(dsp.vslider1, "style", "knob")
        ui.declare(dsp.vslider1, "tooltip", "Portamento (frequency-glide) time-constant in seconds")
        ui.declare(dsp.vslider1, "unit", "sec")
        ui.add_vertical_slider("Portamento", dsp.vslider1, FaustFloat(0.1), FaustFloat(0.001), FaustFloat(10.0), FaustFloat(0.001))
        ui.declare(dsp.entry0, "6", "")
        ui.declare(dsp.entry0, "tooltip", "Order of sawtootn aliasing suppression")
        ui.add_num_entry("Saw Order", dsp.entry0, FaustFloat(2.0), FaustFloat(1.0), FaustFloat(4.0), FaustFloat(1.0))
        ui.declare(dsp.null_val, "7", "")
        ui.open_vertical_box("Alternate Signals")
        ui.declare(dsp.checkbox2, "0", "")
        ui.add_check_button("Noise (White or Pink - uses only Amplitude control on the left)", dsp.checkbox2)
        ui.declare(dsp.checkbox3, "1", "")
        ui.declare(dsp.checkbox3, "tooltip", "Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the same total power in every octave")
        ui.add_check_button("Pink instead of White Noise (also called 1/f Noise)", dsp.checkbox3)
        ui.declare(dsp.checkbox1, "2", "")
        ui.add_check_button("External Signal Input (overrides Sawtooth/Noise selection above)", dsp.checkbox1)
        ui.close_box()
        ui.close_box()
        ui.close_box()
        ui.close_box()
        ui.declare(dsp.null_val, "2", "")
        ui.open_vertical_box("gate")
        ui.declare(dsp.null_val, "tooltip", "Reference: http://en.wikipedia.org/wiki/Noise_gate")
        ui.open_vertical_box("GATE")
        ui.declare(dsp.null_val, "0", "")
        ui.open_horizontal_box("0x00")
        ui.declare(dsp.checkbox0, "0", "")
        ui.declare(dsp.checkbox0, "tooltip", "When this is checked, the gate has no effect")
        ui.add_check_button("Bypass", dsp.checkbox0)
        ui.declare(dsp.hbargraph0, "1", "")
        ui.declare(dsp.hbargraph0, "tooltip", "Current gain of the gate in dB")
        ui.declare(dsp.hbargraph0, "unit", "dB")
        ui.add_horizontal_bargraph("Gate Gain", dsp.hbargraph0, FaustFloat(-50.0), FaustFloat(10.0))
        ui.close_box()
        ui.declare(dsp.null_val, "1", "")
        ui.open_horizontal_box("0x00")
        ui.declare(dsp.hslider3, "1", "")
        ui.declare(dsp.hslider3, "style", "knob")
        ui.declare(dsp.hslider3, "tooltip", "When the signal level falls below the Threshold (expressed in dB), the signal is muted")
        ui.declare(dsp.hslider3, "unit", "dB")
        ui.add_horizontal_slider("Threshold", dsp.hslider3, FaustFloat(-30.0), FaustFloat(-120.0), FaustFloat(0.0), FaustFloat(0.1))
        ui.declare(dsp.hslider0, "2", "")
        ui.declare(dsp.hslider0, "scale", "log")
        ui.declare(dsp.hslider0, "style", "knob")
        ui.declare(dsp.hslider0, "tooltip", "Time constant in MICROseconds (1/e smoothing time) for the gate gain to go (exponentially) from 0 (muted) to 1 (unmuted)")
        ui.declare(dsp.hslider0, "unit", "us")
        ui.add_horizontal_slider("Attack", dsp.hslider0, FaustFloat(10.0), FaustFloat(10.0), FaustFloat(10000.0), FaustFloat(1.0))
        ui.declare(dsp.hslider2, "3", "")
        ui.declare(dsp.hslider2, "scale", "log")
        ui.declare(dsp.hslider2, "style", "knob")
        ui.declare(dsp.hslider2, "tooltip", "Time in ms to keep the gate open (no muting) after the signal level falls below the Threshold")
        ui.declare(dsp.hslider2, "unit", "ms")
        ui.add_horizontal_slider("Hold", dsp.hslider2, FaustFloat(200.0), FaustFloat(1.0), FaustFloat(1000.0), FaustFloat(1.0))
        ui.declare(dsp.hslider1, "4", "")
        ui.declare(dsp.hslider1, "scale", "log")
        ui.declare(dsp.hslider1, "style", "knob")
        ui.declare(dsp.hslider1, "tooltip", "Time constant in ms (1/e smoothing time) for the gain to go (exponentially) from 1 (unmuted) to 0 (muted)")
        ui.declare(dsp.hslider1, "unit", "ms")
        ui.add_horizontal_slider("Release", dsp.hslider1, FaustFloat(100.0), FaustFloat(1.0), FaustFloat(1000.0), FaustFloat(1.0))
        ui.close_box()
        ui.close_box()
        ui.close_box()
        ui.declare(dsp.null_val, "3", "")
        ui.open_vertical_box("compressor")
        ui.declare(dsp.null_val, "tooltip", "Reference: http://en.wikipedia.org/wiki/Dynamic_range_compression")
        ui.open_vertical_box("COMPRESSOR")
        ui.declare(dsp.null_val, "0", "")
        ui.open_horizontal_box("0x00")
        ui.declare(dsp.checkbox4, "0", "")
        ui.declare(dsp.checkbox4, "tooltip", "When this is checked, the compressor has no effect")
        ui.add_check_button("Bypass", dsp.checkbox4)
        ui.declare(dsp.hbargraph1, "1", "")
        ui.declare(dsp.hbargraph1, "tooltip", "Current gain of the compressor in dB")
        ui.declare(dsp.hbargraph1, "unit", "dB")
        ui.add_horizontal_bargraph("Compressor Gain", dsp.hbargraph1, FaustFloat(-50.0), FaustFloat(10.0))
        ui.close_box()
        ui.declare(dsp.null_val, "1", "")
        ui.open_horizontal_box("0x00")
        ui.declare(dsp.null_val, "3", "")
        ui.open_horizontal_box("Compression Control")
        ui.declare(dsp.hslider6, "0", "")
        ui.declare(dsp.hslider6, "style", "knob")
        ui.declare(dsp.hslider6, "tooltip", "A compression Ratio of N means that for each N dB increase in input signal level above Threshold, the output level goes up 1 dB")
        ui.add_horizontal_slider("Ratio", dsp.hslider6, FaustFloat(5.0), FaustFloat(1.0), FaustFloat(20.0), FaustFloat(0.1))
        ui.declare(dsp.hslider7, "1", "")
        ui.declare(dsp.hslider7, "style", "knob")
        ui.declare(dsp.hslider7, "tooltip", "When the signal level exceeds the Threshold (in dB), its level is compressed according to the Ratio")
        ui.declare(dsp.hslider7, "unit", "dB")
        ui.add_horizontal_slider("Threshold", dsp.hslider7, FaustFloat(-30.0), FaustFloat(-100.0), FaustFloat(10.0), FaustFloat(0.1))
        ui.close_box()
        ui.declare(dsp.null_val, "4", "")
        ui.open_horizontal_box("Compression Response")
        ui.declare(dsp.hslider4, "1", "")
        ui.declare(dsp.hslider4, "scale", "log")
        ui.declare(dsp.hslider4, "style", "knob")
        ui.declare(dsp.hslider4, "tooltip", "Time constant in ms (1/e smoothing time) for the compression gain to approach (exponentially) a new lower target level (the compression `kicking in')")
        ui.declare(dsp.hslider4, "unit", "ms")
        ui.add_horizontal_slider("Attack", dsp.hslider4, FaustFloat(50.0), FaustFloat(1.0), FaustFloat(1000.0), FaustFloat(0.1))
        ui.declare(dsp.hslider5, "2", "")
        ui.declare(dsp.hslider5, "scale", "log")
        ui.declare(dsp.hslider5, "style", "knob")
        ui.declare(dsp.hslider5, "tooltip", "Time constant in ms (1/e smoothing time) for the compression gain to approach (exponentially) a new higher target level (the compression 'releasing')")
        ui.declare(dsp.hslider5, "unit", "ms")
        ui.add_horizontal_slider("Release", dsp.hslider5, FaustFloat(500.0), FaustFloat(1.0), FaustFloat(1000.0), FaustFloat(0.1))
        ui.close_box()
        ui.close_box()
        ui.declare(dsp.hslider8, "5", "")
        ui.declare(dsp.hslider8, "tooltip", "The compressed-signal output level is increased by this amount (in dB) to make up for the level lost due to compression")
        ui.declare(dsp.hslider8, "unit", "dB")
        ui.add_horizontal_slider("Makeup Gain", dsp.hslider8, FaustFloat(40.0), FaustFloat(-96.0), FaustFloat(96.0), FaustFloat(0.1))
        ui.close_box()
        ui.close_box()
        ui.declare(dsp.null_val, "4", "")
        ui.open_vertical_box("spectral")
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
        ui.declare(dsp.hslider9, "0", "")
        ui.declare(dsp.hslider9, "scale", "log")
        ui.declare(dsp.hslider9, "tooltip", "band-level averaging time in milliseconds")
        ui.declare(dsp.hslider9, "unit", "ms")
        ui.add_horizontal_slider("Level Averaging Time", dsp.hslider9, FaustFloat(100.0), FaustFloat(1.0), FaustFloat(10000.0), FaustFloat(1.0))
        ui.declare(dsp.hslider10, "1", "")
        ui.declare(dsp.hslider10, "tooltip", "Level offset in decibels")
        ui.declare(dsp.hslider10, "unit", "dB")
        ui.add_horizontal_slider("Level dB Offset", dsp.hslider10, FaustFloat(50.0), FaustFloat(0.0), FaustFloat(100.0), FaustFloat(1.0))
        ui.close_box()
        ui.close_box()
        ui.close_box()

    @always_inline
    def compute(mut dsp, var count: S32, var inputs: ImmStreams, var outputs: MutStreams) -> None:
        comptime assert dfaust == DType.float32, "Expected 32 bit float driver precision."
        comptime vsize = S32(simd_width_of[f32]())
        comptime wsize = S32(simd_width_of[f64]())
        comptime W = simd_width_of[f64]()
        var vindex = S32(0)
        var end = count - vsize
        var lo: SIMD[dfaust, simd_width_of[f64]()]
        var hi: SIMD[dfaust, simd_width_of[f64]()]
        var input0_ptr = inputs[S32(0)]
        var output0_ptr = outputs[S32(0)]
        var output1_ptr = outputs[S32(1)]
        var slow0 = (0.0010000000000000009) * (pow(1e+01, (0.05) * (F64(dsp.vslider0))))
        var rec4_tmp = Arr[F64, 8](uninitialized=True)
        var rec4 = Ptr(to=rec4_tmp[S32(4)])
        var slow1 = F64(dsp.vslider1)
        var slow2 = exp(-((dsp.const1) / (slow1))) if S32((slow1) > (0.0)) else 0.0
        var slow3 = ((4.4e+02) * (pow(2.0, (0.08333333333333333) * ((F64(dsp.vslider2)) + (-49.0))))) * ((1.0) - (slow2))
        var rec6_tmp = Arr[F64, 8](uninitialized=True)
        var rec6 = Ptr(to=rec6_tmp[S32(4)])
        var zec0 = Arr[F64, 4](uninitialized=True)
        var zec1 = Arr[F64, 4](uninitialized=True)
        var rec5_tmp = Arr[F64, 8](uninitialized=True)
        var rec5 = Ptr(to=rec5_tmp[S32(4)])
        var slow4 = ((0.01) * (F64(dsp.vslider3))) + (1.0)
        var zec2 = Arr[F64, 4](uninitialized=True)
        var zec3 = Arr[F64, 4](uninitialized=True)
        var rec7_tmp = Arr[F64, 8](uninitialized=True)
        var rec7 = Ptr(to=rec7_tmp[S32(4)])
        var slow5 = ((0.01) * (F64(dsp.vslider4))) + (1.0)
        var zec4 = Arr[F64, 4](uninitialized=True)
        var zec5 = Arr[F64, 4](uninitialized=True)
        var rec8_tmp = Arr[F64, 8](uninitialized=True)
        var rec8 = Ptr(to=rec8_tmp[S32(4)])
        var i_rec9_tmp = Arr[S32, 8](uninitialized=True)
        var i_rec9 = Ptr(to=i_rec9_tmp[S32(4)])
        var zec6 = Arr[F64, 4](uninitialized=True)
        var rec10_tmp = Arr[F64, 8](uninitialized=True)
        var rec10 = Ptr(to=rec10_tmp[S32(4)])
        var slow6 = max(dsp.const1, (1e-06) * (F64(dsp.hslider0)))
        var slow7 = max(dsp.const1, (0.001) * (F64(dsp.hslider1)))
        var slow8 = min(slow6, slow7)
        var slow9 = exp(-((dsp.const1) / (slow8))) if S32((slow8) > (0.0)) else 0.0
        var i_slow10 = S32(F64(dsp.checkbox0))
        var i_slow11 = S32(F64(dsp.checkbox1))
        var i_slow12 = S32(F64(dsp.checkbox2))
        var i_slow13 = S32((F64(dsp.entry0)) + (-1.0))
        var i_slow14 = S32((i_slow13) >= (S32(2)))
        var i_vec0_tmp = Arr[S32, 8](uninitialized=True)
        var i_vec0 = Ptr(to=i_vec0_tmp[S32(4)])
        var i_slow15 = S32((i_slow13) >= (S32(1)))
        var zec7 = Arr[F64, 4](uninitialized=True)
        var zec8 = Arr[F64, 4](uninitialized=True)
        var zec9 = Arr[F64, 4](uninitialized=True)
        var yec0_tmp = Arr[F64, 8](uninitialized=True)
        var yec0 = Ptr(to=yec0_tmp[S32(4)])
        var i_slow16 = S32((i_slow13) >= (S32(3)))
        var zec10 = Arr[F64, 4](uninitialized=True)
        var zec11 = Arr[F64, 4](uninitialized=True)
        var yec1_tmp = Arr[F64, 8](uninitialized=True)
        var yec1 = Ptr(to=yec1_tmp[S32(4)])
        var yec2_tmp = Arr[F64, 8](uninitialized=True)
        var yec2 = Ptr(to=yec2_tmp[S32(4)])
        var zec12 = Arr[F64, 4](uninitialized=True)
        var yec3_tmp = Arr[F64, 8](uninitialized=True)
        var yec3 = Ptr(to=yec3_tmp[S32(4)])
        var yec4_tmp = Arr[F64, 8](uninitialized=True)
        var yec4 = Ptr(to=yec4_tmp[S32(4)])
        var yec5_tmp = Arr[F64, 8](uninitialized=True)
        var yec5 = Ptr(to=yec5_tmp[S32(4)])
        var zec13 = Arr[F64, 4](uninitialized=True)
        var zec14 = Arr[F64, 4](uninitialized=True)
        var yec6_tmp = Arr[F64, 8](uninitialized=True)
        var yec6 = Ptr(to=yec6_tmp[S32(4)])
        var zec15 = Arr[F64, 4](uninitialized=True)
        var yec7_tmp = Arr[F64, 8](uninitialized=True)
        var yec7 = Ptr(to=yec7_tmp[S32(4)])
        var yec8_tmp = Arr[F64, 8](uninitialized=True)
        var yec8 = Ptr(to=yec8_tmp[S32(4)])
        var yec9_tmp = Arr[F64, 8](uninitialized=True)
        var yec9 = Ptr(to=yec9_tmp[S32(4)])
        var yec10_tmp = Arr[F64, 8](uninitialized=True)
        var yec10 = Ptr(to=yec10_tmp[S32(4)])
        var yec11_tmp = Arr[F64, 8](uninitialized=True)
        var yec11 = Ptr(to=yec11_tmp[S32(4)])
        var zec16 = Arr[F64, 4](uninitialized=True)
        var zec17 = Arr[F64, 4](uninitialized=True)
        var yec12_tmp = Arr[F64, 8](uninitialized=True)
        var yec12 = Ptr(to=yec12_tmp[S32(4)])
        var zec18 = Arr[F64, 4](uninitialized=True)
        var yec13_tmp = Arr[F64, 8](uninitialized=True)
        var yec13 = Ptr(to=yec13_tmp[S32(4)])
        var yec14_tmp = Arr[F64, 8](uninitialized=True)
        var yec14 = Ptr(to=yec14_tmp[S32(4)])
        var yec15_tmp = Arr[F64, 8](uninitialized=True)
        var yec15 = Ptr(to=yec15_tmp[S32(4)])
        var yec16_tmp = Arr[F64, 8](uninitialized=True)
        var yec16 = Ptr(to=yec16_tmp[S32(4)])
        var yec17_tmp = Arr[F64, 8](uninitialized=True)
        var yec17 = Ptr(to=yec17_tmp[S32(4)])
        var i_slow17 = S32(F64(dsp.checkbox3))
        var zec19 = Arr[F64, 4](uninitialized=True)
        var zec20 = Arr[F64, 4](uninitialized=True)
        var zec21 = Arr[F64, 4](uninitialized=True)
        var slow18 = (1.0) - (slow9)
        var rec14_tmp = Arr[F64, 8](uninitialized=True)
        var rec14 = Ptr(to=rec14_tmp[S32(4)])
        var rec13 = Arr[F64, 4](uninitialized=True)
        var i_slow19 = S32((dsp.const0) * (max(dsp.const1, (0.001) * (F64(dsp.hslider2)))))
        var slow20 = pow(1e+01, (0.05) * (F64(dsp.hslider3)))
        var i_yec18_tmp = Arr[S32, 8](uninitialized=True)
        var i_yec18 = Ptr(to=i_yec18_tmp[S32(4)])
        var i_rec15_tmp = Arr[S32, 8](uninitialized=True)
        var i_rec15 = Ptr(to=i_rec15_tmp[S32(4)])
        var zec22 = Arr[F64, 4](uninitialized=True)
        var slow21 = exp(-((dsp.const1) / (slow6))) if S32((slow6) > (0.0)) else 0.0
        var slow22 = exp(-((dsp.const1) / (slow7))) if S32((slow7) > (0.0)) else 0.0
        var zec23 = Arr[F64, 4](uninitialized=True)
        var rec12_tmp = Arr[F64, 8](uninitialized=True)
        var rec12 = Ptr(to=rec12_tmp[S32(4)])
        var rec11_tmp = Arr[F64, 8](uninitialized=True)
        var rec11 = Ptr(to=rec11_tmp[S32(4)])
        var zec24 = Arr[F64, 4](uninitialized=True)
        var rec3_tmp = Arr[F64, 8](uninitialized=True)
        var rec3 = Ptr(to=rec3_tmp[S32(4)])
        var rec2 = Arr[F64, 4](uninitialized=True)
        var i_yec19_tmp = Arr[S32, 8](uninitialized=True)
        var i_yec19 = Ptr(to=i_yec19_tmp[S32(4)])
        var i_rec16_tmp = Arr[S32, 8](uninitialized=True)
        var i_rec16 = Ptr(to=i_rec16_tmp[S32(4)])
        var zec25 = Arr[F64, 4](uninitialized=True)
        var zec26 = Arr[F64, 4](uninitialized=True)
        var rec1_tmp = Arr[F64, 8](uninitialized=True)
        var rec1 = Ptr(to=rec1_tmp[S32(4)])
        var rec0_tmp = Arr[F64, 8](uninitialized=True)
        var rec0 = Ptr(to=rec0_tmp[S32(4)])
        var i_slow23 = S32(F64(dsp.checkbox4))
        var zec27 = Arr[F64, 4](uninitialized=True)
        var zec28 = Arr[F64, 4](uninitialized=True)
        var zec29 = Arr[F64, 4](uninitialized=True)
        var zec30 = Arr[F64, 4](uninitialized=True)
        var zec31 = Arr[F64, 4](uninitialized=True)
        var slow24 = max(dsp.const1, (0.001) * (F64(dsp.hslider4)))
        var slow25 = exp(-((dsp.const1) / (slow24))) if S32((slow24) > (0.0)) else 0.0
        var slow26 = max(dsp.const1, (0.001) * (F64(dsp.hslider5)))
        var slow27 = exp(-((dsp.const1) / (slow26))) if S32((slow26) > (0.0)) else 0.0
        var zec32 = Arr[F64, 4](uninitialized=True)
        var rec19_tmp = Arr[F64, 8](uninitialized=True)
        var rec19 = Ptr(to=rec19_tmp[S32(4)])
        var rec18_tmp = Arr[F64, 8](uninitialized=True)
        var rec18 = Ptr(to=rec18_tmp[S32(4)])
        var slow28 = exp(-((dsp.const5) / (slow24))) if S32(((0.5) * (slow24)) > (0.0)) else 0.0
        var slow29 = ((1.0) / (F64(dsp.hslider6))) + (-1.0)
        var slow30 = F64(dsp.hslider7)
        var slow31 = (1.0) - (slow28)
        var rec17_tmp = Arr[F64, 8](uninitialized=True)
        var rec17 = Ptr(to=rec17_tmp[S32(4)])
        var zec33 = Arr[F64, 4](uninitialized=True)
        var zec34 = Arr[F64, 4](uninitialized=True)
        var zec35 = Arr[F64, 4](uninitialized=True)
        var zec36 = Arr[F64, 4](uninitialized=True)
        var zec37 = Arr[F64, 4](uninitialized=True)
        var rec22_tmp = Arr[F64, 8](uninitialized=True)
        var rec22 = Ptr(to=rec22_tmp[S32(4)])
        var rec21_tmp = Arr[F64, 8](uninitialized=True)
        var rec21 = Ptr(to=rec21_tmp[S32(4)])
        var rec20_tmp = Arr[F64, 8](uninitialized=True)
        var rec20 = Ptr(to=rec20_tmp[S32(4)])
        var slow32 = pow(1e+01, (0.05) * (F64(dsp.hslider8)))
        var zec38 = Arr[F64, 4](uninitialized=True)
        var rec26_tmp = Arr[F64, 8](uninitialized=True)
        var rec26 = Ptr(to=rec26_tmp[S32(4)])
        var rec25_tmp = Arr[F64, 8](uninitialized=True)
        var rec25 = Ptr(to=rec25_tmp[S32(4)])
        var rec24_tmp = Arr[F64, 8](uninitialized=True)
        var rec24 = Ptr(to=rec24_tmp[S32(4)])
        var slow33 = F64(dsp.hslider9)
        var slow34 = exp(-((dsp.const25) / (slow33))) if S32(((0.001) * (slow33)) > (0.0)) else 0.0
        var slow35 = (1.0) - (slow34)
        var rec23_tmp = Arr[F64, 8](uninitialized=True)
        var rec23 = Ptr(to=rec23_tmp[S32(4)])
        var rec33_tmp = Arr[F64, 8](uninitialized=True)
        var rec33 = Ptr(to=rec33_tmp[S32(4)])
        var rec32_tmp = Arr[F64, 8](uninitialized=True)
        var rec32 = Ptr(to=rec32_tmp[S32(4)])
        var rec31_tmp = Arr[F64, 8](uninitialized=True)
        var rec31 = Ptr(to=rec31_tmp[S32(4)])
        var zec39 = Arr[F64, 4](uninitialized=True)
        var rec30_tmp = Arr[F64, 8](uninitialized=True)
        var rec30 = Ptr(to=rec30_tmp[S32(4)])
        var rec29_tmp = Arr[F64, 8](uninitialized=True)
        var rec29 = Ptr(to=rec29_tmp[S32(4)])
        var rec28_tmp = Arr[F64, 8](uninitialized=True)
        var rec28 = Ptr(to=rec28_tmp[S32(4)])
        var rec27_tmp = Arr[F64, 8](uninitialized=True)
        var rec27 = Ptr(to=rec27_tmp[S32(4)])
        var rec40_tmp = Arr[F64, 8](uninitialized=True)
        var rec40 = Ptr(to=rec40_tmp[S32(4)])
        var rec39_tmp = Arr[F64, 8](uninitialized=True)
        var rec39 = Ptr(to=rec39_tmp[S32(4)])
        var rec38_tmp = Arr[F64, 8](uninitialized=True)
        var rec38 = Ptr(to=rec38_tmp[S32(4)])
        var zec40 = Arr[F64, 4](uninitialized=True)
        var rec37_tmp = Arr[F64, 8](uninitialized=True)
        var rec37 = Ptr(to=rec37_tmp[S32(4)])
        var rec36_tmp = Arr[F64, 8](uninitialized=True)
        var rec36 = Ptr(to=rec36_tmp[S32(4)])
        var rec35_tmp = Arr[F64, 8](uninitialized=True)
        var rec35 = Ptr(to=rec35_tmp[S32(4)])
        var rec34_tmp = Arr[F64, 8](uninitialized=True)
        var rec34 = Ptr(to=rec34_tmp[S32(4)])
        var rec47_tmp = Arr[F64, 8](uninitialized=True)
        var rec47 = Ptr(to=rec47_tmp[S32(4)])
        var rec46_tmp = Arr[F64, 8](uninitialized=True)
        var rec46 = Ptr(to=rec46_tmp[S32(4)])
        var rec45_tmp = Arr[F64, 8](uninitialized=True)
        var rec45 = Ptr(to=rec45_tmp[S32(4)])
        var zec41 = Arr[F64, 4](uninitialized=True)
        var rec44_tmp = Arr[F64, 8](uninitialized=True)
        var rec44 = Ptr(to=rec44_tmp[S32(4)])
        var rec43_tmp = Arr[F64, 8](uninitialized=True)
        var rec43 = Ptr(to=rec43_tmp[S32(4)])
        var rec42_tmp = Arr[F64, 8](uninitialized=True)
        var rec42 = Ptr(to=rec42_tmp[S32(4)])
        var rec41_tmp = Arr[F64, 8](uninitialized=True)
        var rec41 = Ptr(to=rec41_tmp[S32(4)])
        var rec54_tmp = Arr[F64, 8](uninitialized=True)
        var rec54 = Ptr(to=rec54_tmp[S32(4)])
        var rec53_tmp = Arr[F64, 8](uninitialized=True)
        var rec53 = Ptr(to=rec53_tmp[S32(4)])
        var rec52_tmp = Arr[F64, 8](uninitialized=True)
        var rec52 = Ptr(to=rec52_tmp[S32(4)])
        var zec42 = Arr[F64, 4](uninitialized=True)
        var rec51_tmp = Arr[F64, 8](uninitialized=True)
        var rec51 = Ptr(to=rec51_tmp[S32(4)])
        var rec50_tmp = Arr[F64, 8](uninitialized=True)
        var rec50 = Ptr(to=rec50_tmp[S32(4)])
        var rec49_tmp = Arr[F64, 8](uninitialized=True)
        var rec49 = Ptr(to=rec49_tmp[S32(4)])
        var rec48_tmp = Arr[F64, 8](uninitialized=True)
        var rec48 = Ptr(to=rec48_tmp[S32(4)])
        var rec61_tmp = Arr[F64, 8](uninitialized=True)
        var rec61 = Ptr(to=rec61_tmp[S32(4)])
        var rec60_tmp = Arr[F64, 8](uninitialized=True)
        var rec60 = Ptr(to=rec60_tmp[S32(4)])
        var rec59_tmp = Arr[F64, 8](uninitialized=True)
        var rec59 = Ptr(to=rec59_tmp[S32(4)])
        var zec43 = Arr[F64, 4](uninitialized=True)
        var rec58_tmp = Arr[F64, 8](uninitialized=True)
        var rec58 = Ptr(to=rec58_tmp[S32(4)])
        var rec57_tmp = Arr[F64, 8](uninitialized=True)
        var rec57 = Ptr(to=rec57_tmp[S32(4)])
        var rec56_tmp = Arr[F64, 8](uninitialized=True)
        var rec56 = Ptr(to=rec56_tmp[S32(4)])
        var rec55_tmp = Arr[F64, 8](uninitialized=True)
        var rec55 = Ptr(to=rec55_tmp[S32(4)])
        var rec68_tmp = Arr[F64, 8](uninitialized=True)
        var rec68 = Ptr(to=rec68_tmp[S32(4)])
        var rec67_tmp = Arr[F64, 8](uninitialized=True)
        var rec67 = Ptr(to=rec67_tmp[S32(4)])
        var rec66_tmp = Arr[F64, 8](uninitialized=True)
        var rec66 = Ptr(to=rec66_tmp[S32(4)])
        var zec44 = Arr[F64, 4](uninitialized=True)
        var rec65_tmp = Arr[F64, 8](uninitialized=True)
        var rec65 = Ptr(to=rec65_tmp[S32(4)])
        var rec64_tmp = Arr[F64, 8](uninitialized=True)
        var rec64 = Ptr(to=rec64_tmp[S32(4)])
        var rec63_tmp = Arr[F64, 8](uninitialized=True)
        var rec63 = Ptr(to=rec63_tmp[S32(4)])
        var rec62_tmp = Arr[F64, 8](uninitialized=True)
        var rec62 = Ptr(to=rec62_tmp[S32(4)])
        var rec75_tmp = Arr[F64, 8](uninitialized=True)
        var rec75 = Ptr(to=rec75_tmp[S32(4)])
        var rec74_tmp = Arr[F64, 8](uninitialized=True)
        var rec74 = Ptr(to=rec74_tmp[S32(4)])
        var rec73_tmp = Arr[F64, 8](uninitialized=True)
        var rec73 = Ptr(to=rec73_tmp[S32(4)])
        var zec45 = Arr[F64, 4](uninitialized=True)
        var rec72_tmp = Arr[F64, 8](uninitialized=True)
        var rec72 = Ptr(to=rec72_tmp[S32(4)])
        var rec71_tmp = Arr[F64, 8](uninitialized=True)
        var rec71 = Ptr(to=rec71_tmp[S32(4)])
        var rec70_tmp = Arr[F64, 8](uninitialized=True)
        var rec70 = Ptr(to=rec70_tmp[S32(4)])
        var rec69_tmp = Arr[F64, 8](uninitialized=True)
        var rec69 = Ptr(to=rec69_tmp[S32(4)])
        var rec82_tmp = Arr[F64, 8](uninitialized=True)
        var rec82 = Ptr(to=rec82_tmp[S32(4)])
        var rec81_tmp = Arr[F64, 8](uninitialized=True)
        var rec81 = Ptr(to=rec81_tmp[S32(4)])
        var rec80_tmp = Arr[F64, 8](uninitialized=True)
        var rec80 = Ptr(to=rec80_tmp[S32(4)])
        var zec46 = Arr[F64, 4](uninitialized=True)
        var rec79_tmp = Arr[F64, 8](uninitialized=True)
        var rec79 = Ptr(to=rec79_tmp[S32(4)])
        var rec78_tmp = Arr[F64, 8](uninitialized=True)
        var rec78 = Ptr(to=rec78_tmp[S32(4)])
        var rec77_tmp = Arr[F64, 8](uninitialized=True)
        var rec77 = Ptr(to=rec77_tmp[S32(4)])
        var rec76_tmp = Arr[F64, 8](uninitialized=True)
        var rec76 = Ptr(to=rec76_tmp[S32(4)])
        var rec89_tmp = Arr[F64, 8](uninitialized=True)
        var rec89 = Ptr(to=rec89_tmp[S32(4)])
        var rec88_tmp = Arr[F64, 8](uninitialized=True)
        var rec88 = Ptr(to=rec88_tmp[S32(4)])
        var rec87_tmp = Arr[F64, 8](uninitialized=True)
        var rec87 = Ptr(to=rec87_tmp[S32(4)])
        var zec47 = Arr[F64, 4](uninitialized=True)
        var rec86_tmp = Arr[F64, 8](uninitialized=True)
        var rec86 = Ptr(to=rec86_tmp[S32(4)])
        var rec85_tmp = Arr[F64, 8](uninitialized=True)
        var rec85 = Ptr(to=rec85_tmp[S32(4)])
        var rec84_tmp = Arr[F64, 8](uninitialized=True)
        var rec84 = Ptr(to=rec84_tmp[S32(4)])
        var rec83_tmp = Arr[F64, 8](uninitialized=True)
        var rec83 = Ptr(to=rec83_tmp[S32(4)])
        var rec96_tmp = Arr[F64, 8](uninitialized=True)
        var rec96 = Ptr(to=rec96_tmp[S32(4)])
        var rec95_tmp = Arr[F64, 8](uninitialized=True)
        var rec95 = Ptr(to=rec95_tmp[S32(4)])
        var rec94_tmp = Arr[F64, 8](uninitialized=True)
        var rec94 = Ptr(to=rec94_tmp[S32(4)])
        var zec48 = Arr[F64, 4](uninitialized=True)
        var rec93_tmp = Arr[F64, 8](uninitialized=True)
        var rec93 = Ptr(to=rec93_tmp[S32(4)])
        var rec92_tmp = Arr[F64, 8](uninitialized=True)
        var rec92 = Ptr(to=rec92_tmp[S32(4)])
        var rec91_tmp = Arr[F64, 8](uninitialized=True)
        var rec91 = Ptr(to=rec91_tmp[S32(4)])
        var rec90_tmp = Arr[F64, 8](uninitialized=True)
        var rec90 = Ptr(to=rec90_tmp[S32(4)])
        var rec103_tmp = Arr[F64, 8](uninitialized=True)
        var rec103 = Ptr(to=rec103_tmp[S32(4)])
        var rec102_tmp = Arr[F64, 8](uninitialized=True)
        var rec102 = Ptr(to=rec102_tmp[S32(4)])
        var rec101_tmp = Arr[F64, 8](uninitialized=True)
        var rec101 = Ptr(to=rec101_tmp[S32(4)])
        var zec49 = Arr[F64, 4](uninitialized=True)
        var rec100_tmp = Arr[F64, 8](uninitialized=True)
        var rec100 = Ptr(to=rec100_tmp[S32(4)])
        var rec99_tmp = Arr[F64, 8](uninitialized=True)
        var rec99 = Ptr(to=rec99_tmp[S32(4)])
        var rec98_tmp = Arr[F64, 8](uninitialized=True)
        var rec98 = Ptr(to=rec98_tmp[S32(4)])
        var rec97_tmp = Arr[F64, 8](uninitialized=True)
        var rec97 = Ptr(to=rec97_tmp[S32(4)])
        var rec110_tmp = Arr[F64, 8](uninitialized=True)
        var rec110 = Ptr(to=rec110_tmp[S32(4)])
        var rec109_tmp = Arr[F64, 8](uninitialized=True)
        var rec109 = Ptr(to=rec109_tmp[S32(4)])
        var rec108_tmp = Arr[F64, 8](uninitialized=True)
        var rec108 = Ptr(to=rec108_tmp[S32(4)])
        var zec50 = Arr[F64, 4](uninitialized=True)
        var rec107_tmp = Arr[F64, 8](uninitialized=True)
        var rec107 = Ptr(to=rec107_tmp[S32(4)])
        var rec106_tmp = Arr[F64, 8](uninitialized=True)
        var rec106 = Ptr(to=rec106_tmp[S32(4)])
        var rec105_tmp = Arr[F64, 8](uninitialized=True)
        var rec105 = Ptr(to=rec105_tmp[S32(4)])
        var rec104_tmp = Arr[F64, 8](uninitialized=True)
        var rec104 = Ptr(to=rec104_tmp[S32(4)])
        var rec117_tmp = Arr[F64, 8](uninitialized=True)
        var rec117 = Ptr(to=rec117_tmp[S32(4)])
        var rec116_tmp = Arr[F64, 8](uninitialized=True)
        var rec116 = Ptr(to=rec116_tmp[S32(4)])
        var rec115_tmp = Arr[F64, 8](uninitialized=True)
        var rec115 = Ptr(to=rec115_tmp[S32(4)])
        var zec51 = Arr[F64, 4](uninitialized=True)
        var rec114_tmp = Arr[F64, 8](uninitialized=True)
        var rec114 = Ptr(to=rec114_tmp[S32(4)])
        var rec113_tmp = Arr[F64, 8](uninitialized=True)
        var rec113 = Ptr(to=rec113_tmp[S32(4)])
        var rec112_tmp = Arr[F64, 8](uninitialized=True)
        var rec112 = Ptr(to=rec112_tmp[S32(4)])
        var rec111_tmp = Arr[F64, 8](uninitialized=True)
        var rec111 = Ptr(to=rec111_tmp[S32(4)])
        var rec121_tmp = Arr[F64, 8](uninitialized=True)
        var rec121 = Ptr(to=rec121_tmp[S32(4)])
        var rec120_tmp = Arr[F64, 8](uninitialized=True)
        var rec120 = Ptr(to=rec120_tmp[S32(4)])
        var rec119_tmp = Arr[F64, 8](uninitialized=True)
        var rec119 = Ptr(to=rec119_tmp[S32(4)])
        var rec118_tmp = Arr[F64, 8](uninitialized=True)
        var rec118 = Ptr(to=rec118_tmp[S32(4)])
        var slow36 = F64(dsp.hslider10)
        var zec52 = Arr[F64, 4](uninitialized=True)
        while vindex <= end:
            var input0 = Ptr(to=input0_ptr[vindex])
            var output0 = Ptr(to=output0_ptr[vindex])
            var output1 = Ptr(to=output1_ptr[vindex])
            vstore(rec4_tmp, vload(dsp.rec4_perm))
            vstore(rec4_tmp, vload(dsp.rec4_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec4[i] = (slow0) + ((0.999) * (rec4[(i) - (S32(1))]))
            vstore(dsp.rec4_perm, vload(rec4_tmp, vsize))
            vstore(dsp.rec4_perm, vload(rec4_tmp, vsize + wsize), wsize)
            vstore(rec6_tmp, vload(dsp.rec6_perm))
            vstore(rec6_tmp, vload(dsp.rec6_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec6[i] = ((rec6[(i) - (S32(1))]) * (slow2)) + (slow3)
            vstore(dsp.rec6_perm, vload(rec6_tmp, vsize))
            vstore(dsp.rec6_perm, vload(rec6_tmp, vsize + wsize), wsize)
            vstore(zec0, max(F64Vec(2e+01), abs(vload(rec6))))
            vstore(zec0, max(F64Vec(2e+01), abs(vload(rec6, wsize))), wsize)
            vstore(rec5_tmp, vload(dsp.rec5_perm))
            vstore(rec5_tmp, vload(dsp.rec5_perm, wsize), wsize)
            comptime for i in range(vsize):
                zec1[i] = (rec5[(i) - (S32(1))]) + ((dsp.const1) * (zec0[i]))
                rec5[i] = (zec1[i]) - (floor(zec1[i]))
            vstore(dsp.rec5_perm, vload(rec5_tmp, vsize))
            vstore(dsp.rec5_perm, vload(rec5_tmp, vsize + wsize), wsize)
            vstore(zec2, max(F64Vec(2e+01), abs((slow4) * (vload(rec6)))))
            vstore(zec2, max(F64Vec(2e+01), abs((slow4) * (vload(rec6, wsize)))), wsize)
            vstore(rec7_tmp, vload(dsp.rec7_perm))
            vstore(rec7_tmp, vload(dsp.rec7_perm, wsize), wsize)
            comptime for i in range(vsize):
                zec3[i] = (rec7[(i) - (S32(1))]) + ((dsp.const1) * (zec2[i]))
                rec7[i] = (zec3[i]) - (floor(zec3[i]))
            vstore(dsp.rec7_perm, vload(rec7_tmp, vsize))
            vstore(dsp.rec7_perm, vload(rec7_tmp, vsize + wsize), wsize)
            vstore(zec4, max(F64Vec(2e+01), abs((slow5) * (vload(rec6)))))
            vstore(zec4, max(F64Vec(2e+01), abs((slow5) * (vload(rec6, wsize)))), wsize)
            vstore(rec8_tmp, vload(dsp.rec8_perm))
            vstore(rec8_tmp, vload(dsp.rec8_perm, wsize), wsize)
            comptime for i in range(vsize):
                zec5[i] = (rec8[(i) - (S32(1))]) + ((dsp.const1) * (zec4[i]))
                rec8[i] = (zec5[i]) - (floor(zec5[i]))
            vstore(dsp.rec8_perm, vload(rec8_tmp, vsize))
            vstore(dsp.rec8_perm, vload(rec8_tmp, vsize + wsize), wsize)
            vstore(i_rec9_tmp, vload(dsp.i_rec9_perm))
            comptime for i in range(vsize):
                i_rec9[i] = ((S32(1103515245)) * (i_rec9[(i) - (S32(1))])) + (S32(12345))
            vstore(dsp.i_rec9_perm, vload(i_rec9_tmp, vsize))
            vstore(zec6, (F64Vec(4.656612875245797e-10)) * ((vload[W](i_rec9)).cast[f64]()))
            vstore(zec6, (F64Vec(4.656612875245797e-10)) * ((vload[W](i_rec9, wsize)).cast[f64]()), wsize)
            vstore(rec10_tmp, vload(dsp.rec10_perm))
            vstore(rec10_tmp, vload(dsp.rec10_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec10[i] = (((0.5221894) * (rec10[(i) - (S32(3))])) + ((zec6[i]) + ((2.494956002) * (rec10[(i) - (S32(1))])))) - ((2.017265875) * (rec10[(i) - (S32(2))]))
            vstore(dsp.rec10_perm, vload(rec10_tmp, vsize))
            vstore(dsp.rec10_perm, vload(rec10_tmp, vsize + wsize), wsize)
            vstore(i_vec0_tmp, vload(dsp.i_vec0_perm))
            vstore(i_vec0, S32Vec(1))
            vstore(dsp.i_vec0_perm, vload(i_vec0_tmp, vsize))
            vstore(zec7, (F64Vec(2.0)) * (vload(rec5)))
            vstore(zec7, (F64Vec(2.0)) * (vload(rec5, wsize)), wsize)
            vstore(zec8, (vload(zec7)) + (F64Vec(-1.0)))
            vstore(zec8, (vload(zec7, wsize)) + (F64Vec(-1.0)), wsize)
            vstore(zec9, (vload[W](i_vec0, - S32(1))).cast[f64]())
            vstore(zec9, (vload[W](i_vec0, - S32(1) + wsize)).cast[f64](), wsize)
            vstore(yec0_tmp, vload(dsp.yec0_perm))
            vstore(yec0_tmp, vload(dsp.yec0_perm, wsize), wsize)
            vstore(yec0, pow_unrolled[2](vload(zec8)))
            vstore(yec0, pow_unrolled[2](vload(zec8, wsize)), wsize)
            vstore(dsp.yec0_perm, vload(yec0_tmp, vsize))
            vstore(dsp.yec0_perm, vload(yec0_tmp, vsize + wsize), wsize)
            vstore(zec10, (vload[W](i_vec0, - S32(2))).cast[f64]())
            vstore(zec10, (vload[W](i_vec0, - S32(2) + wsize)).cast[f64](), wsize)
            vstore(zec11, pow_unrolled[3](vload(zec8)))
            vstore(zec11, pow_unrolled[3](vload(zec8, wsize)), wsize)
            vstore(yec1_tmp, vload(dsp.yec1_perm))
            vstore(yec1_tmp, vload(dsp.yec1_perm, wsize), wsize)
            vstore(yec1, (vload(zec11)) + ((F64Vec(1.0)) - (vload(zec7))))
            vstore(yec1, (vload(zec11, wsize)) + ((F64Vec(1.0)) - (vload(zec7, wsize))), wsize)
            vstore(dsp.yec1_perm, vload(yec1_tmp, vsize))
            vstore(dsp.yec1_perm, vload(yec1_tmp, vsize + wsize), wsize)
            vstore(yec2_tmp, vload(dsp.yec2_perm))
            vstore(yec2_tmp, vload(dsp.yec2_perm, wsize), wsize)
            vstore(yec2, ((vload(zec11)) + ((F64Vec(1.0)) - ((vload(zec7)) + (vload(yec1, - S32(1)))))) / (vload(zec0)))
            vstore(yec2, ((vload(zec11, wsize)) + ((F64Vec(1.0)) - ((vload(zec7, wsize)) + (vload(yec1, - S32(1) + wsize))))) / (vload(zec0, wsize)), wsize)
            vstore(dsp.yec2_perm, vload(yec2_tmp, vsize))
            vstore(dsp.yec2_perm, vload(yec2_tmp, vsize + wsize), wsize)
            vstore(zec12, (vload[W](i_vec0, - S32(3))).cast[f64]())
            vstore(zec12, (vload[W](i_vec0, - S32(3) + wsize)).cast[f64](), wsize)
            vstore(yec3_tmp, vload(dsp.yec3_perm))
            vstore(yec3_tmp, vload(dsp.yec3_perm, wsize), wsize)
            vstore(yec3, (vload(yec0)) * ((vload(yec0)) + (F64Vec(-2.0))))
            vstore(yec3, (vload(yec0, wsize)) * ((vload(yec0, wsize)) + (F64Vec(-2.0))), wsize)
            vstore(dsp.yec3_perm, vload(yec3_tmp, vsize))
            vstore(dsp.yec3_perm, vload(yec3_tmp, vsize + wsize), wsize)
            vstore(yec4_tmp, vload(dsp.yec4_perm))
            vstore(yec4_tmp, vload(dsp.yec4_perm, wsize), wsize)
            vstore(yec4, ((vload(yec3)) - (vload(yec3, - S32(1)))) / (vload(zec0)))
            vstore(yec4, ((vload(yec3, wsize)) - (vload(yec3, - S32(1) + wsize))) / (vload(zec0, wsize)), wsize)
            vstore(dsp.yec4_perm, vload(yec4_tmp, vsize))
            vstore(dsp.yec4_perm, vload(yec4_tmp, vsize + wsize), wsize)
            vstore(yec5_tmp, vload(dsp.yec5_perm))
            vstore(yec5_tmp, vload(dsp.yec5_perm, wsize), wsize)
            vstore(yec5, ((vload(yec4)) - (vload(yec4, - S32(1)))) / (vload(zec0)))
            vstore(yec5, ((vload(yec4, wsize)) - (vload(yec4, - S32(1) + wsize))) / (vload(zec0, wsize)), wsize)
            vstore(dsp.yec5_perm, vload(yec5_tmp, vsize))
            vstore(dsp.yec5_perm, vload(yec5_tmp, vsize + wsize), wsize)
            vstore(zec13, (F64Vec(2.0)) * (vload(rec7)))
            vstore(zec13, (F64Vec(2.0)) * (vload(rec7, wsize)), wsize)
            vstore(zec14, (vload(zec13)) + (F64Vec(-1.0)))
            vstore(zec14, (vload(zec13, wsize)) + (F64Vec(-1.0)), wsize)
            vstore(yec6_tmp, vload(dsp.yec6_perm))
            vstore(yec6_tmp, vload(dsp.yec6_perm, wsize), wsize)
            vstore(yec6, pow_unrolled[2](vload(zec14)))
            vstore(yec6, pow_unrolled[2](vload(zec14, wsize)), wsize)
            vstore(dsp.yec6_perm, vload(yec6_tmp, vsize))
            vstore(dsp.yec6_perm, vload(yec6_tmp, vsize + wsize), wsize)
            vstore(zec15, pow_unrolled[3](vload(zec14)))
            vstore(zec15, pow_unrolled[3](vload(zec14, wsize)), wsize)
            vstore(yec7_tmp, vload(dsp.yec7_perm))
            vstore(yec7_tmp, vload(dsp.yec7_perm, wsize), wsize)
            vstore(yec7, (vload(zec15)) + ((F64Vec(1.0)) - (vload(zec13))))
            vstore(yec7, (vload(zec15, wsize)) + ((F64Vec(1.0)) - (vload(zec13, wsize))), wsize)
            vstore(dsp.yec7_perm, vload(yec7_tmp, vsize))
            vstore(dsp.yec7_perm, vload(yec7_tmp, vsize + wsize), wsize)
            vstore(yec8_tmp, vload(dsp.yec8_perm))
            vstore(yec8_tmp, vload(dsp.yec8_perm, wsize), wsize)
            vstore(yec8, ((vload(zec15)) + ((F64Vec(1.0)) - ((vload(zec13)) + (vload(yec7, - S32(1)))))) / (vload(zec2)))
            vstore(yec8, ((vload(zec15, wsize)) + ((F64Vec(1.0)) - ((vload(zec13, wsize)) + (vload(yec7, - S32(1) + wsize))))) / (vload(zec2, wsize)), wsize)
            vstore(dsp.yec8_perm, vload(yec8_tmp, vsize))
            vstore(dsp.yec8_perm, vload(yec8_tmp, vsize + wsize), wsize)
            vstore(yec9_tmp, vload(dsp.yec9_perm))
            vstore(yec9_tmp, vload(dsp.yec9_perm, wsize), wsize)
            vstore(yec9, (vload(yec6)) * ((vload(yec6)) + (F64Vec(-2.0))))
            vstore(yec9, (vload(yec6, wsize)) * ((vload(yec6, wsize)) + (F64Vec(-2.0))), wsize)
            vstore(dsp.yec9_perm, vload(yec9_tmp, vsize))
            vstore(dsp.yec9_perm, vload(yec9_tmp, vsize + wsize), wsize)
            vstore(yec10_tmp, vload(dsp.yec10_perm))
            vstore(yec10_tmp, vload(dsp.yec10_perm, wsize), wsize)
            vstore(yec10, ((vload(yec9)) - (vload(yec9, - S32(1)))) / (vload(zec2)))
            vstore(yec10, ((vload(yec9, wsize)) - (vload(yec9, - S32(1) + wsize))) / (vload(zec2, wsize)), wsize)
            vstore(dsp.yec10_perm, vload(yec10_tmp, vsize))
            vstore(dsp.yec10_perm, vload(yec10_tmp, vsize + wsize), wsize)
            vstore(yec11_tmp, vload(dsp.yec11_perm))
            vstore(yec11_tmp, vload(dsp.yec11_perm, wsize), wsize)
            vstore(yec11, ((vload(yec10)) - (vload(yec10, - S32(1)))) / (vload(zec2)))
            vstore(yec11, ((vload(yec10, wsize)) - (vload(yec10, - S32(1) + wsize))) / (vload(zec2, wsize)), wsize)
            vstore(dsp.yec11_perm, vload(yec11_tmp, vsize))
            vstore(dsp.yec11_perm, vload(yec11_tmp, vsize + wsize), wsize)
            vstore(zec16, (F64Vec(2.0)) * (vload(rec8)))
            vstore(zec16, (F64Vec(2.0)) * (vload(rec8, wsize)), wsize)
            vstore(zec17, (vload(zec16)) + (F64Vec(-1.0)))
            vstore(zec17, (vload(zec16, wsize)) + (F64Vec(-1.0)), wsize)
            vstore(yec12_tmp, vload(dsp.yec12_perm))
            vstore(yec12_tmp, vload(dsp.yec12_perm, wsize), wsize)
            vstore(yec12, pow_unrolled[2](vload(zec17)))
            vstore(yec12, pow_unrolled[2](vload(zec17, wsize)), wsize)
            vstore(dsp.yec12_perm, vload(yec12_tmp, vsize))
            vstore(dsp.yec12_perm, vload(yec12_tmp, vsize + wsize), wsize)
            vstore(zec18, pow_unrolled[3](vload(zec17)))
            vstore(zec18, pow_unrolled[3](vload(zec17, wsize)), wsize)
            vstore(yec13_tmp, vload(dsp.yec13_perm))
            vstore(yec13_tmp, vload(dsp.yec13_perm, wsize), wsize)
            vstore(yec13, (vload(zec18)) + ((F64Vec(1.0)) - (vload(zec16))))
            vstore(yec13, (vload(zec18, wsize)) + ((F64Vec(1.0)) - (vload(zec16, wsize))), wsize)
            vstore(dsp.yec13_perm, vload(yec13_tmp, vsize))
            vstore(dsp.yec13_perm, vload(yec13_tmp, vsize + wsize), wsize)
            vstore(yec14_tmp, vload(dsp.yec14_perm))
            vstore(yec14_tmp, vload(dsp.yec14_perm, wsize), wsize)
            vstore(yec14, ((vload(zec18)) + ((F64Vec(1.0)) - ((vload(zec16)) + (vload(yec13, - S32(1)))))) / (vload(zec4)))
            vstore(yec14, ((vload(zec18, wsize)) + ((F64Vec(1.0)) - ((vload(zec16, wsize)) + (vload(yec13, - S32(1) + wsize))))) / (vload(zec4, wsize)), wsize)
            vstore(dsp.yec14_perm, vload(yec14_tmp, vsize))
            vstore(dsp.yec14_perm, vload(yec14_tmp, vsize + wsize), wsize)
            vstore(yec15_tmp, vload(dsp.yec15_perm))
            vstore(yec15_tmp, vload(dsp.yec15_perm, wsize), wsize)
            vstore(yec15, (vload(yec12)) * ((vload(yec12)) + (F64Vec(-2.0))))
            vstore(yec15, (vload(yec12, wsize)) * ((vload(yec12, wsize)) + (F64Vec(-2.0))), wsize)
            vstore(dsp.yec15_perm, vload(yec15_tmp, vsize))
            vstore(dsp.yec15_perm, vload(yec15_tmp, vsize + wsize), wsize)
            vstore(yec16_tmp, vload(dsp.yec16_perm))
            vstore(yec16_tmp, vload(dsp.yec16_perm, wsize), wsize)
            vstore(yec16, ((vload(yec15)) - (vload(yec15, - S32(1)))) / (vload(zec4)))
            vstore(yec16, ((vload(yec15, wsize)) - (vload(yec15, - S32(1) + wsize))) / (vload(zec4, wsize)), wsize)
            vstore(dsp.yec16_perm, vload(yec16_tmp, vsize))
            vstore(dsp.yec16_perm, vload(yec16_tmp, vsize + wsize), wsize)
            vstore(yec17_tmp, vload(dsp.yec17_perm))
            vstore(yec17_tmp, vload(dsp.yec17_perm, wsize), wsize)
            vstore(yec17, ((vload(yec16)) - (vload(yec16, - S32(1)))) / (vload(zec4)))
            vstore(yec17, ((vload(yec16, wsize)) - (vload(yec16, - S32(1) + wsize))) / (vload(zec4, wsize)), wsize)
            vstore(dsp.yec17_perm, vload(yec17_tmp, vsize))
            vstore(dsp.yec17_perm, vload(yec17_tmp, vsize + wsize), wsize)
            vstore(zec19, (vload(rec4)) * ((vload[W](input0)).cast[f64]() if i_slow11 else (((F64Vec(0.049922035)) * (vload(rec10))) + ((F64Vec(0.050612699)) * (vload(rec10, - S32(2))))) - (((F64Vec(0.095993537)) * (vload(rec10, - S32(1)))) + ((F64Vec(0.004408786)) * (vload(rec10, - S32(3))))) if i_slow17 else vload(zec6) if i_slow12 else (F64Vec(0.3333333333333333)) * ((vload(rec4)) * ((((dsp.const4) * (((vload(zec12)) * ((vload(yec5)) - (vload(yec5, - S32(1))))) / (vload(zec0))) if i_slow16 else (dsp.const3) * (((vload(zec10)) * ((vload(yec2)) - (vload(yec2, - S32(1))))) / (vload(zec0))) if i_slow14 else (dsp.const2) * (((vload(zec9)) * ((vload(yec0)) - (vload(yec0, - S32(1))))) / (vload(zec0))) if i_slow15 else vload(zec8)) + ((dsp.const4) * (((vload(zec12)) * ((vload(yec11)) - (vload(yec11, - S32(1))))) / (vload(zec2))) if i_slow16 else (dsp.const3) * (((vload(zec10)) * ((vload(yec8)) - (vload(yec8, - S32(1))))) / (vload(zec2))) if i_slow14 else (dsp.const2) * (((vload(zec9)) * ((vload(yec6)) - (vload(yec6, - S32(1))))) / (vload(zec2))) if i_slow15 else vload(zec14))) + ((dsp.const4) * (((vload(zec12)) * ((vload(yec17)) - (vload(yec17, - S32(1))))) / (vload(zec4))) if i_slow16 else (dsp.const3) * (((vload(zec10)) * ((vload(yec14)) - (vload(yec14, - S32(1))))) / (vload(zec4))) if i_slow14 else (dsp.const2) * (((vload(zec9)) * ((vload(yec12)) - (vload(yec12, - S32(1))))) / (vload(zec4))) if i_slow15 else vload(zec17))))))
            vstore(zec19, (vload(rec4, wsize)) * ((vload[W](input0, wsize)).cast[f64]() if i_slow11 else (((F64Vec(0.049922035)) * (vload(rec10, wsize))) + ((F64Vec(0.050612699)) * (vload(rec10, - S32(2) + wsize)))) - (((F64Vec(0.095993537)) * (vload(rec10, - S32(1) + wsize))) + ((F64Vec(0.004408786)) * (vload(rec10, - S32(3) + wsize)))) if i_slow17 else vload(zec6, wsize) if i_slow12 else (F64Vec(0.3333333333333333)) * ((vload(rec4, wsize)) * ((((dsp.const4) * (((vload(zec12, wsize)) * ((vload(yec5, wsize)) - (vload(yec5, - S32(1) + wsize)))) / (vload(zec0, wsize))) if i_slow16 else (dsp.const3) * (((vload(zec10, wsize)) * ((vload(yec2, wsize)) - (vload(yec2, - S32(1) + wsize)))) / (vload(zec0, wsize))) if i_slow14 else (dsp.const2) * (((vload(zec9, wsize)) * ((vload(yec0, wsize)) - (vload(yec0, - S32(1) + wsize)))) / (vload(zec0, wsize))) if i_slow15 else vload(zec8, wsize)) + ((dsp.const4) * (((vload(zec12, wsize)) * ((vload(yec11, wsize)) - (vload(yec11, - S32(1) + wsize)))) / (vload(zec2, wsize))) if i_slow16 else (dsp.const3) * (((vload(zec10, wsize)) * ((vload(yec8, wsize)) - (vload(yec8, - S32(1) + wsize)))) / (vload(zec2, wsize))) if i_slow14 else (dsp.const2) * (((vload(zec9, wsize)) * ((vload(yec6, wsize)) - (vload(yec6, - S32(1) + wsize)))) / (vload(zec2, wsize))) if i_slow15 else vload(zec14, wsize))) + ((dsp.const4) * (((vload(zec12, wsize)) * ((vload(yec17, wsize)) - (vload(yec17, - S32(1) + wsize)))) / (vload(zec4, wsize))) if i_slow16 else (dsp.const3) * (((vload(zec10, wsize)) * ((vload(yec14, wsize)) - (vload(yec14, - S32(1) + wsize)))) / (vload(zec4, wsize))) if i_slow14 else (dsp.const2) * (((vload(zec9, wsize)) * ((vload(yec12, wsize)) - (vload(yec12, - S32(1) + wsize)))) / (vload(zec4, wsize))) if i_slow15 else vload(zec17, wsize))))), wsize)
            vstore(zec20, F64Vec(0.0) if i_slow10 else vload(zec19))
            vstore(zec20, F64Vec(0.0) if i_slow10 else vload(zec19, wsize), wsize)
            vstore(zec21, abs(vload(zec20)))
            vstore(zec21, abs(vload(zec20, wsize)), wsize)
            vstore(rec14_tmp, vload(dsp.rec14_perm))
            vstore(rec14_tmp, vload(dsp.rec14_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec14[i] = ((rec14[(i) - (S32(1))]) * (slow9)) + ((abs((2.0) * (zec21[i]))) * (slow18))
            vstore(dsp.rec14_perm, vload(rec14_tmp, vsize))
            vstore(dsp.rec14_perm, vload(rec14_tmp, vsize + wsize), wsize)
            comptime for i in range(vsize):
                rec13[i] = rec14[i]
            vstore(i_yec18_tmp, vload(dsp.i_yec18_perm))
            vstore(i_yec18, S32Vec((vload(rec13)) > (slow20)))
            vstore(dsp.i_yec18_perm, vload(i_yec18_tmp, vsize))
            vstore(i_rec15_tmp, vload(dsp.i_rec15_perm))
            comptime for i in range(vsize):
                i_rec15[i] = max((i_slow19) * (S32((i_yec18[i]) < (i_yec18[(i) - (S32(1))]))), (i_rec15[(i) - (S32(1))]) + (S32(-1)))
            vstore(dsp.i_rec15_perm, vload(i_rec15_tmp, vsize))
            vstore(zec22, abs(max((vload[W](i_yec18)).cast[f64](), (S32Vec((vload[W](i_rec15)) > (S32Vec(0)))).cast[f64]())))
            vstore(zec22, abs(max((vload[W](i_yec18, wsize)).cast[f64](), (S32Vec((vload[W](i_rec15, wsize)) > (S32Vec(0)))).cast[f64]())), wsize)
            vstore(rec12_tmp, vload(dsp.rec12_perm))
            vstore(rec12_tmp, vload(dsp.rec12_perm, wsize), wsize)
            vstore(rec11_tmp, vload(dsp.rec11_perm))
            vstore(rec11_tmp, vload(dsp.rec11_perm, wsize), wsize)
            comptime for i in range(vsize):
                zec23[i] = slow22 if S32((rec11[(i) - (S32(1))]) > (zec22[i])) else slow21
                rec12[i] = ((rec12[(i) - (S32(1))]) * (zec23[i])) + ((zec22[i]) * ((1.0) - (zec23[i])))
                rec11[i] = rec12[i]
            vstore(dsp.rec12_perm, vload(rec12_tmp, vsize))
            vstore(dsp.rec12_perm, vload(rec12_tmp, vsize + wsize), wsize)
            vstore(dsp.rec11_perm, vload(rec11_tmp, vsize))
            vstore(dsp.rec11_perm, vload(rec11_tmp, vsize + wsize), wsize)
            vstore(zec24, (F64Vec(2e+01)) * (log10(vload(rec11))))
            vstore(zec24, (F64Vec(2e+01)) * (log10(vload(rec11, wsize))), wsize)
            dsp.hbargraph0 = FaustFloat(zec24[vsize - S32(1)])
            vstore(rec3_tmp, vload(dsp.rec3_perm))
            vstore(rec3_tmp, vload(dsp.rec3_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec3[i] = ((rec3[(i) - (S32(1))]) * (slow9)) + ((slow18) * (abs((zec21[i]) + (abs(zec24[i])))))
            vstore(dsp.rec3_perm, vload(rec3_tmp, vsize))
            vstore(dsp.rec3_perm, vload(rec3_tmp, vsize + wsize), wsize)
            comptime for i in range(vsize):
                rec2[i] = rec3[i]
            vstore(i_yec19_tmp, vload(dsp.i_yec19_perm))
            vstore(i_yec19, S32Vec((vload(rec2)) > (slow20)))
            vstore(dsp.i_yec19_perm, vload(i_yec19_tmp, vsize))
            vstore(i_rec16_tmp, vload(dsp.i_rec16_perm))
            comptime for i in range(vsize):
                i_rec16[i] = max((i_slow19) * (S32((i_yec19[i]) < (i_yec19[(i) - (S32(1))]))), (i_rec16[(i) - (S32(1))]) + (S32(-1)))
            vstore(dsp.i_rec16_perm, vload(i_rec16_tmp, vsize))
            vstore(zec25, abs(max((vload[W](i_yec19)).cast[f64](), (S32Vec((vload[W](i_rec16)) > (S32Vec(0)))).cast[f64]())))
            vstore(zec25, abs(max((vload[W](i_yec19, wsize)).cast[f64](), (S32Vec((vload[W](i_rec16, wsize)) > (S32Vec(0)))).cast[f64]())), wsize)
            vstore(rec1_tmp, vload(dsp.rec1_perm))
            vstore(rec1_tmp, vload(dsp.rec1_perm, wsize), wsize)
            vstore(rec0_tmp, vload(dsp.rec0_perm))
            vstore(rec0_tmp, vload(dsp.rec0_perm, wsize), wsize)
            comptime for i in range(vsize):
                zec26[i] = slow22 if S32((rec0[(i) - (S32(1))]) > (zec25[i])) else slow21
                rec1[i] = ((rec1[(i) - (S32(1))]) * (zec26[i])) + ((zec25[i]) * ((1.0) - (zec26[i])))
                rec0[i] = rec1[i]
            vstore(dsp.rec1_perm, vload(rec1_tmp, vsize))
            vstore(dsp.rec1_perm, vload(rec1_tmp, vsize + wsize), wsize)
            vstore(dsp.rec0_perm, vload(rec0_tmp, vsize))
            vstore(dsp.rec0_perm, vload(rec0_tmp, vsize + wsize), wsize)
            vstore(zec27, vload(zec19) if i_slow10 else (vload(rec0)) * (vload(zec24)))
            vstore(zec27, vload(zec19, wsize) if i_slow10 else (vload(rec0, wsize)) * (vload(zec24, wsize)), wsize)
            vstore(zec28, F64Vec(0.0) if i_slow23 else vload(zec27))
            vstore(zec28, F64Vec(0.0) if i_slow23 else vload(zec27, wsize), wsize)
            vstore(zec29, vload(zec19) if i_slow10 else (vload(rec0)) * (vload(zec20)))
            vstore(zec29, vload(zec19, wsize) if i_slow10 else (vload(rec0, wsize)) * (vload(zec20, wsize)), wsize)
            vstore(zec30, F64Vec(0.0) if i_slow23 else vload(zec29))
            vstore(zec30, F64Vec(0.0) if i_slow23 else vload(zec29, wsize), wsize)
            vstore(zec31, abs((abs(vload(zec28))) + (abs(vload(zec30)))))
            vstore(zec31, abs((abs(vload(zec28, wsize))) + (abs(vload(zec30, wsize)))), wsize)
            vstore(rec19_tmp, vload(dsp.rec19_perm))
            vstore(rec19_tmp, vload(dsp.rec19_perm, wsize), wsize)
            vstore(rec18_tmp, vload(dsp.rec18_perm))
            vstore(rec18_tmp, vload(dsp.rec18_perm, wsize), wsize)
            comptime for i in range(vsize):
                zec32[i] = slow27 if S32((rec18[(i) - (S32(1))]) > (zec31[i])) else slow25
                rec19[i] = ((rec19[(i) - (S32(1))]) * (zec32[i])) + ((zec31[i]) * ((1.0) - (zec32[i])))
                rec18[i] = rec19[i]
            vstore(dsp.rec19_perm, vload(rec19_tmp, vsize))
            vstore(dsp.rec19_perm, vload(rec19_tmp, vsize + wsize), wsize)
            vstore(dsp.rec18_perm, vload(rec18_tmp, vsize))
            vstore(dsp.rec18_perm, vload(rec18_tmp, vsize + wsize), wsize)
            vstore(rec17_tmp, vload(dsp.rec17_perm))
            vstore(rec17_tmp, vload(dsp.rec17_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec17[i] = ((rec17[(i) - (S32(1))]) * (slow28)) + ((slow29) * ((max(((2e+01) * (log10(rec18[i]))) - (slow30), 0.0)) * (slow31)))
            vstore(dsp.rec17_perm, vload(rec17_tmp, vsize))
            vstore(dsp.rec17_perm, vload(rec17_tmp, vsize + wsize), wsize)
            vstore(zec33, pow(F64Vec(1e+01), (F64Vec(0.05)) * (vload(rec17))))
            vstore(zec33, pow(F64Vec(1e+01), (F64Vec(0.05)) * (vload(rec17, wsize))), wsize)
            vstore(zec34, (vload(zec28)) * (vload(zec33)))
            vstore(zec34, (vload(zec28, wsize)) * (vload(zec33, wsize)), wsize)
            vstore(zec35, (vload(zec30)) * (vload(zec33)))
            vstore(zec35, (vload(zec30, wsize)) * (vload(zec33, wsize)), wsize)
            vstore(zec36, abs((abs(vload(zec34))) + (abs(vload(zec35)))))
            vstore(zec36, abs((abs(vload(zec34, wsize))) + (abs(vload(zec35, wsize)))), wsize)
            vstore(rec22_tmp, vload(dsp.rec22_perm))
            vstore(rec22_tmp, vload(dsp.rec22_perm, wsize), wsize)
            vstore(rec21_tmp, vload(dsp.rec21_perm))
            vstore(rec21_tmp, vload(dsp.rec21_perm, wsize), wsize)
            comptime for i in range(vsize):
                zec37[i] = slow27 if S32((rec21[(i) - (S32(1))]) > (zec36[i])) else slow25
                rec22[i] = ((rec22[(i) - (S32(1))]) * (zec37[i])) + ((zec36[i]) * ((1.0) - (zec37[i])))
                rec21[i] = rec22[i]
            vstore(dsp.rec22_perm, vload(rec22_tmp, vsize))
            vstore(dsp.rec22_perm, vload(rec22_tmp, vsize + wsize), wsize)
            vstore(dsp.rec21_perm, vload(rec21_tmp, vsize))
            vstore(dsp.rec21_perm, vload(rec21_tmp, vsize + wsize), wsize)
            vstore(rec20_tmp, vload(dsp.rec20_perm))
            vstore(rec20_tmp, vload(dsp.rec20_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec20[i] = ((slow28) * (rec20[(i) - (S32(1))])) + ((slow29) * ((max(((2e+01) * (log10(rec21[i]))) - (slow30), 0.0)) * (slow31)))
            vstore(dsp.rec20_perm, vload(rec20_tmp, vsize))
            vstore(dsp.rec20_perm, vload(rec20_tmp, vsize + wsize), wsize)
            vstore(zec38, (F64Vec(2e+01)) * (log10(pow(F64Vec(1e+01), (F64Vec(0.05)) * (vload(rec20))))))
            vstore(zec38, (F64Vec(2e+01)) * (log10(pow(F64Vec(1e+01), (F64Vec(0.05)) * (vload(rec20, wsize))))), wsize)
            dsp.hbargraph1 = FaustFloat(zec38[vsize - S32(1)])
            vstore(rec26_tmp, vload(dsp.rec26_perm))
            vstore(rec26_tmp, vload(dsp.rec26_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec26[i] = (zec38[i]) - ((dsp.const8) * (((dsp.const9) * (rec26[(i) - (S32(2))])) + ((dsp.const12) * (rec26[(i) - (S32(1))]))))
            vstore(dsp.rec26_perm, vload(rec26_tmp, vsize))
            vstore(dsp.rec26_perm, vload(rec26_tmp, vsize + wsize), wsize)
            vstore(rec25_tmp, vload(dsp.rec25_perm))
            vstore(rec25_tmp, vload(dsp.rec25_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec25[i] = ((dsp.const8) * ((((dsp.const14) * (rec26[i])) + ((dsp.const15) * (rec26[(i) - (S32(1))]))) + ((dsp.const14) * (rec26[(i) - (S32(2))])))) - ((dsp.const16) * (((dsp.const17) * (rec25[(i) - (S32(2))])) + ((dsp.const18) * (rec25[(i) - (S32(1))]))))
            vstore(dsp.rec25_perm, vload(rec25_tmp, vsize))
            vstore(dsp.rec25_perm, vload(rec25_tmp, vsize + wsize), wsize)
            vstore(rec24_tmp, vload(dsp.rec24_perm))
            vstore(rec24_tmp, vload(dsp.rec24_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec24[i] = ((dsp.const16) * ((((dsp.const20) * (rec25[i])) + ((dsp.const21) * (rec25[(i) - (S32(1))]))) + ((dsp.const20) * (rec25[(i) - (S32(2))])))) - ((dsp.const22) * (((dsp.const23) * (rec24[(i) - (S32(2))])) + ((dsp.const24) * (rec24[(i) - (S32(1))]))))
            vstore(dsp.rec24_perm, vload(rec24_tmp, vsize))
            vstore(dsp.rec24_perm, vload(rec24_tmp, vsize + wsize), wsize)
            vstore(rec23_tmp, vload(dsp.rec23_perm))
            vstore(rec23_tmp, vload(dsp.rec23_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec23[i] = ((rec23[(i) - (S32(1))]) * (slow34)) + ((abs((dsp.const22) * ((((dsp.const27) * (rec24[i])) + ((dsp.const28) * (rec24[(i) - (S32(1))]))) + ((dsp.const27) * (rec24[(i) - (S32(2))]))))) * (slow35))
            vstore(dsp.rec23_perm, vload(rec23_tmp, vsize))
            vstore(dsp.rec23_perm, vload(rec23_tmp, vsize + wsize), wsize)
            vstore(rec33_tmp, vload(dsp.rec33_perm))
            vstore(rec33_tmp, vload(dsp.rec33_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec33[i] = (zec38[i]) - ((dsp.const29) * (((dsp.const30) * (rec33[(i) - (S32(2))])) + ((dsp.const31) * (rec33[(i) - (S32(1))]))))
            vstore(dsp.rec33_perm, vload(rec33_tmp, vsize))
            vstore(dsp.rec33_perm, vload(rec33_tmp, vsize + wsize), wsize)
            vstore(rec32_tmp, vload(dsp.rec32_perm))
            vstore(rec32_tmp, vload(dsp.rec32_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec32[i] = ((dsp.const29) * ((((dsp.const33) * (rec33[i])) + ((dsp.const34) * (rec33[(i) - (S32(1))]))) + ((dsp.const33) * (rec33[(i) - (S32(2))])))) - ((dsp.const35) * (((dsp.const36) * (rec32[(i) - (S32(2))])) + ((dsp.const37) * (rec32[(i) - (S32(1))]))))
            vstore(dsp.rec32_perm, vload(rec32_tmp, vsize))
            vstore(dsp.rec32_perm, vload(rec32_tmp, vsize + wsize), wsize)
            vstore(rec31_tmp, vload(dsp.rec31_perm))
            vstore(rec31_tmp, vload(dsp.rec31_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec31[i] = ((dsp.const35) * ((((dsp.const38) * (rec32[i])) + ((dsp.const39) * (rec32[(i) - (S32(1))]))) + ((dsp.const38) * (rec32[(i) - (S32(2))])))) - ((dsp.const40) * (((dsp.const41) * (rec31[(i) - (S32(2))])) + ((dsp.const42) * (rec31[(i) - (S32(1))]))))
            vstore(dsp.rec31_perm, vload(rec31_tmp, vsize))
            vstore(dsp.rec31_perm, vload(rec31_tmp, vsize + wsize), wsize)
            vstore(zec39, (dsp.const40) * ((((dsp.const43) * (vload(rec31))) + ((dsp.const44) * (vload(rec31, - S32(1))))) + ((dsp.const43) * (vload(rec31, - S32(2))))))
            vstore(zec39, (dsp.const40) * ((((dsp.const43) * (vload(rec31, wsize))) + ((dsp.const44) * (vload(rec31, - S32(1) + wsize)))) + ((dsp.const43) * (vload(rec31, - S32(2) + wsize)))), wsize)
            vstore(rec30_tmp, vload(dsp.rec30_perm))
            vstore(rec30_tmp, vload(dsp.rec30_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec30[i] = (zec39[i]) - ((dsp.const47) * (((dsp.const48) * (rec30[(i) - (S32(2))])) + ((dsp.const51) * (rec30[(i) - (S32(1))]))))
            vstore(dsp.rec30_perm, vload(rec30_tmp, vsize))
            vstore(dsp.rec30_perm, vload(rec30_tmp, vsize + wsize), wsize)
            vstore(rec29_tmp, vload(dsp.rec29_perm))
            vstore(rec29_tmp, vload(dsp.rec29_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec29[i] = ((dsp.const47) * ((((dsp.const53) * (rec30[i])) + ((dsp.const54) * (rec30[(i) - (S32(1))]))) + ((dsp.const53) * (rec30[(i) - (S32(2))])))) - ((dsp.const55) * (((dsp.const56) * (rec29[(i) - (S32(2))])) + ((dsp.const57) * (rec29[(i) - (S32(1))]))))
            vstore(dsp.rec29_perm, vload(rec29_tmp, vsize))
            vstore(dsp.rec29_perm, vload(rec29_tmp, vsize + wsize), wsize)
            vstore(rec28_tmp, vload(dsp.rec28_perm))
            vstore(rec28_tmp, vload(dsp.rec28_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec28[i] = ((dsp.const55) * ((((dsp.const59) * (rec29[i])) + ((dsp.const60) * (rec29[(i) - (S32(1))]))) + ((dsp.const59) * (rec29[(i) - (S32(2))])))) - ((dsp.const61) * (((dsp.const62) * (rec28[(i) - (S32(2))])) + ((dsp.const63) * (rec28[(i) - (S32(1))]))))
            vstore(dsp.rec28_perm, vload(rec28_tmp, vsize))
            vstore(dsp.rec28_perm, vload(rec28_tmp, vsize + wsize), wsize)
            vstore(rec27_tmp, vload(dsp.rec27_perm))
            vstore(rec27_tmp, vload(dsp.rec27_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec27[i] = ((slow34) * (rec27[(i) - (S32(1))])) + ((slow35) * (abs((dsp.const61) * ((((dsp.const65) * (rec28[i])) + ((dsp.const66) * (rec28[(i) - (S32(1))]))) + ((dsp.const65) * (rec28[(i) - (S32(2))]))))))
            vstore(dsp.rec27_perm, vload(rec27_tmp, vsize))
            vstore(dsp.rec27_perm, vload(rec27_tmp, vsize + wsize), wsize)
            vstore(rec40_tmp, vload(dsp.rec40_perm))
            vstore(rec40_tmp, vload(dsp.rec40_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec40[i] = (zec39[i]) - ((dsp.const67) * (((dsp.const68) * (rec40[(i) - (S32(2))])) + ((dsp.const69) * (rec40[(i) - (S32(1))]))))
            vstore(dsp.rec40_perm, vload(rec40_tmp, vsize))
            vstore(dsp.rec40_perm, vload(rec40_tmp, vsize + wsize), wsize)
            vstore(rec39_tmp, vload(dsp.rec39_perm))
            vstore(rec39_tmp, vload(dsp.rec39_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec39[i] = ((dsp.const67) * ((((dsp.const71) * (rec40[i])) + ((dsp.const72) * (rec40[(i) - (S32(1))]))) + ((dsp.const71) * (rec40[(i) - (S32(2))])))) - ((dsp.const73) * (((dsp.const74) * (rec39[(i) - (S32(2))])) + ((dsp.const75) * (rec39[(i) - (S32(1))]))))
            vstore(dsp.rec39_perm, vload(rec39_tmp, vsize))
            vstore(dsp.rec39_perm, vload(rec39_tmp, vsize + wsize), wsize)
            vstore(rec38_tmp, vload(dsp.rec38_perm))
            vstore(rec38_tmp, vload(dsp.rec38_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec38[i] = ((dsp.const73) * ((((dsp.const76) * (rec39[i])) + ((dsp.const77) * (rec39[(i) - (S32(1))]))) + ((dsp.const76) * (rec39[(i) - (S32(2))])))) - ((dsp.const78) * (((dsp.const79) * (rec38[(i) - (S32(2))])) + ((dsp.const80) * (rec38[(i) - (S32(1))]))))
            vstore(dsp.rec38_perm, vload(rec38_tmp, vsize))
            vstore(dsp.rec38_perm, vload(rec38_tmp, vsize + wsize), wsize)
            vstore(zec40, (dsp.const78) * ((((dsp.const81) * (vload(rec38))) + ((dsp.const82) * (vload(rec38, - S32(1))))) + ((dsp.const81) * (vload(rec38, - S32(2))))))
            vstore(zec40, (dsp.const78) * ((((dsp.const81) * (vload(rec38, wsize))) + ((dsp.const82) * (vload(rec38, - S32(1) + wsize)))) + ((dsp.const81) * (vload(rec38, - S32(2) + wsize)))), wsize)
            vstore(rec37_tmp, vload(dsp.rec37_perm))
            vstore(rec37_tmp, vload(dsp.rec37_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec37[i] = (zec40[i]) - ((dsp.const85) * (((dsp.const86) * (rec37[(i) - (S32(2))])) + ((dsp.const89) * (rec37[(i) - (S32(1))]))))
            vstore(dsp.rec37_perm, vload(rec37_tmp, vsize))
            vstore(dsp.rec37_perm, vload(rec37_tmp, vsize + wsize), wsize)
            vstore(rec36_tmp, vload(dsp.rec36_perm))
            vstore(rec36_tmp, vload(dsp.rec36_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec36[i] = ((dsp.const85) * ((((dsp.const91) * (rec37[i])) + ((dsp.const92) * (rec37[(i) - (S32(1))]))) + ((dsp.const91) * (rec37[(i) - (S32(2))])))) - ((dsp.const93) * (((dsp.const94) * (rec36[(i) - (S32(2))])) + ((dsp.const95) * (rec36[(i) - (S32(1))]))))
            vstore(dsp.rec36_perm, vload(rec36_tmp, vsize))
            vstore(dsp.rec36_perm, vload(rec36_tmp, vsize + wsize), wsize)
            vstore(rec35_tmp, vload(dsp.rec35_perm))
            vstore(rec35_tmp, vload(dsp.rec35_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec35[i] = ((dsp.const93) * ((((dsp.const97) * (rec36[i])) + ((dsp.const98) * (rec36[(i) - (S32(1))]))) + ((dsp.const97) * (rec36[(i) - (S32(2))])))) - ((dsp.const99) * (((dsp.const100) * (rec35[(i) - (S32(2))])) + ((dsp.const101) * (rec35[(i) - (S32(1))]))))
            vstore(dsp.rec35_perm, vload(rec35_tmp, vsize))
            vstore(dsp.rec35_perm, vload(rec35_tmp, vsize + wsize), wsize)
            vstore(rec34_tmp, vload(dsp.rec34_perm))
            vstore(rec34_tmp, vload(dsp.rec34_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec34[i] = ((slow34) * (rec34[(i) - (S32(1))])) + ((slow35) * (abs((dsp.const99) * ((((dsp.const103) * (rec35[i])) + ((dsp.const104) * (rec35[(i) - (S32(1))]))) + ((dsp.const103) * (rec35[(i) - (S32(2))]))))))
            vstore(dsp.rec34_perm, vload(rec34_tmp, vsize))
            vstore(dsp.rec34_perm, vload(rec34_tmp, vsize + wsize), wsize)
            vstore(rec47_tmp, vload(dsp.rec47_perm))
            vstore(rec47_tmp, vload(dsp.rec47_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec47[i] = (zec40[i]) - ((dsp.const105) * (((dsp.const106) * (rec47[(i) - (S32(2))])) + ((dsp.const107) * (rec47[(i) - (S32(1))]))))
            vstore(dsp.rec47_perm, vload(rec47_tmp, vsize))
            vstore(dsp.rec47_perm, vload(rec47_tmp, vsize + wsize), wsize)
            vstore(rec46_tmp, vload(dsp.rec46_perm))
            vstore(rec46_tmp, vload(dsp.rec46_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec46[i] = ((dsp.const105) * ((((dsp.const109) * (rec47[i])) + ((dsp.const110) * (rec47[(i) - (S32(1))]))) + ((dsp.const109) * (rec47[(i) - (S32(2))])))) - ((dsp.const111) * (((dsp.const112) * (rec46[(i) - (S32(2))])) + ((dsp.const113) * (rec46[(i) - (S32(1))]))))
            vstore(dsp.rec46_perm, vload(rec46_tmp, vsize))
            vstore(dsp.rec46_perm, vload(rec46_tmp, vsize + wsize), wsize)
            vstore(rec45_tmp, vload(dsp.rec45_perm))
            vstore(rec45_tmp, vload(dsp.rec45_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec45[i] = ((dsp.const111) * ((((dsp.const114) * (rec46[i])) + ((dsp.const115) * (rec46[(i) - (S32(1))]))) + ((dsp.const114) * (rec46[(i) - (S32(2))])))) - ((dsp.const116) * (((dsp.const117) * (rec45[(i) - (S32(2))])) + ((dsp.const118) * (rec45[(i) - (S32(1))]))))
            vstore(dsp.rec45_perm, vload(rec45_tmp, vsize))
            vstore(dsp.rec45_perm, vload(rec45_tmp, vsize + wsize), wsize)
            vstore(zec41, (dsp.const116) * ((((dsp.const119) * (vload(rec45))) + ((dsp.const120) * (vload(rec45, - S32(1))))) + ((dsp.const119) * (vload(rec45, - S32(2))))))
            vstore(zec41, (dsp.const116) * ((((dsp.const119) * (vload(rec45, wsize))) + ((dsp.const120) * (vload(rec45, - S32(1) + wsize)))) + ((dsp.const119) * (vload(rec45, - S32(2) + wsize)))), wsize)
            vstore(rec44_tmp, vload(dsp.rec44_perm))
            vstore(rec44_tmp, vload(dsp.rec44_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec44[i] = (zec41[i]) - ((dsp.const123) * (((dsp.const124) * (rec44[(i) - (S32(2))])) + ((dsp.const127) * (rec44[(i) - (S32(1))]))))
            vstore(dsp.rec44_perm, vload(rec44_tmp, vsize))
            vstore(dsp.rec44_perm, vload(rec44_tmp, vsize + wsize), wsize)
            vstore(rec43_tmp, vload(dsp.rec43_perm))
            vstore(rec43_tmp, vload(dsp.rec43_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec43[i] = ((dsp.const123) * ((((dsp.const129) * (rec44[i])) + ((dsp.const130) * (rec44[(i) - (S32(1))]))) + ((dsp.const129) * (rec44[(i) - (S32(2))])))) - ((dsp.const131) * (((dsp.const132) * (rec43[(i) - (S32(2))])) + ((dsp.const133) * (rec43[(i) - (S32(1))]))))
            vstore(dsp.rec43_perm, vload(rec43_tmp, vsize))
            vstore(dsp.rec43_perm, vload(rec43_tmp, vsize + wsize), wsize)
            vstore(rec42_tmp, vload(dsp.rec42_perm))
            vstore(rec42_tmp, vload(dsp.rec42_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec42[i] = ((dsp.const131) * ((((dsp.const135) * (rec43[i])) + ((dsp.const136) * (rec43[(i) - (S32(1))]))) + ((dsp.const135) * (rec43[(i) - (S32(2))])))) - ((dsp.const137) * (((dsp.const138) * (rec42[(i) - (S32(2))])) + ((dsp.const139) * (rec42[(i) - (S32(1))]))))
            vstore(dsp.rec42_perm, vload(rec42_tmp, vsize))
            vstore(dsp.rec42_perm, vload(rec42_tmp, vsize + wsize), wsize)
            vstore(rec41_tmp, vload(dsp.rec41_perm))
            vstore(rec41_tmp, vload(dsp.rec41_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec41[i] = ((slow34) * (rec41[(i) - (S32(1))])) + ((slow35) * (abs((dsp.const137) * ((((dsp.const141) * (rec42[i])) + ((dsp.const142) * (rec42[(i) - (S32(1))]))) + ((dsp.const141) * (rec42[(i) - (S32(2))]))))))
            vstore(dsp.rec41_perm, vload(rec41_tmp, vsize))
            vstore(dsp.rec41_perm, vload(rec41_tmp, vsize + wsize), wsize)
            vstore(rec54_tmp, vload(dsp.rec54_perm))
            vstore(rec54_tmp, vload(dsp.rec54_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec54[i] = (zec41[i]) - ((dsp.const143) * (((dsp.const144) * (rec54[(i) - (S32(2))])) + ((dsp.const145) * (rec54[(i) - (S32(1))]))))
            vstore(dsp.rec54_perm, vload(rec54_tmp, vsize))
            vstore(dsp.rec54_perm, vload(rec54_tmp, vsize + wsize), wsize)
            vstore(rec53_tmp, vload(dsp.rec53_perm))
            vstore(rec53_tmp, vload(dsp.rec53_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec53[i] = ((dsp.const143) * ((((dsp.const147) * (rec54[i])) + ((dsp.const148) * (rec54[(i) - (S32(1))]))) + ((dsp.const147) * (rec54[(i) - (S32(2))])))) - ((dsp.const149) * (((dsp.const150) * (rec53[(i) - (S32(2))])) + ((dsp.const151) * (rec53[(i) - (S32(1))]))))
            vstore(dsp.rec53_perm, vload(rec53_tmp, vsize))
            vstore(dsp.rec53_perm, vload(rec53_tmp, vsize + wsize), wsize)
            vstore(rec52_tmp, vload(dsp.rec52_perm))
            vstore(rec52_tmp, vload(dsp.rec52_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec52[i] = ((dsp.const149) * ((((dsp.const152) * (rec53[i])) + ((dsp.const153) * (rec53[(i) - (S32(1))]))) + ((dsp.const152) * (rec53[(i) - (S32(2))])))) - ((dsp.const154) * (((dsp.const155) * (rec52[(i) - (S32(2))])) + ((dsp.const156) * (rec52[(i) - (S32(1))]))))
            vstore(dsp.rec52_perm, vload(rec52_tmp, vsize))
            vstore(dsp.rec52_perm, vload(rec52_tmp, vsize + wsize), wsize)
            vstore(zec42, (dsp.const154) * ((((dsp.const157) * (vload(rec52))) + ((dsp.const158) * (vload(rec52, - S32(1))))) + ((dsp.const157) * (vload(rec52, - S32(2))))))
            vstore(zec42, (dsp.const154) * ((((dsp.const157) * (vload(rec52, wsize))) + ((dsp.const158) * (vload(rec52, - S32(1) + wsize)))) + ((dsp.const157) * (vload(rec52, - S32(2) + wsize)))), wsize)
            vstore(rec51_tmp, vload(dsp.rec51_perm))
            vstore(rec51_tmp, vload(dsp.rec51_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec51[i] = (zec42[i]) - ((dsp.const161) * (((dsp.const162) * (rec51[(i) - (S32(2))])) + ((dsp.const165) * (rec51[(i) - (S32(1))]))))
            vstore(dsp.rec51_perm, vload(rec51_tmp, vsize))
            vstore(dsp.rec51_perm, vload(rec51_tmp, vsize + wsize), wsize)
            vstore(rec50_tmp, vload(dsp.rec50_perm))
            vstore(rec50_tmp, vload(dsp.rec50_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec50[i] = ((dsp.const161) * ((((dsp.const167) * (rec51[i])) + ((dsp.const168) * (rec51[(i) - (S32(1))]))) + ((dsp.const167) * (rec51[(i) - (S32(2))])))) - ((dsp.const169) * (((dsp.const170) * (rec50[(i) - (S32(2))])) + ((dsp.const171) * (rec50[(i) - (S32(1))]))))
            vstore(dsp.rec50_perm, vload(rec50_tmp, vsize))
            vstore(dsp.rec50_perm, vload(rec50_tmp, vsize + wsize), wsize)
            vstore(rec49_tmp, vload(dsp.rec49_perm))
            vstore(rec49_tmp, vload(dsp.rec49_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec49[i] = ((dsp.const169) * ((((dsp.const173) * (rec50[i])) + ((dsp.const174) * (rec50[(i) - (S32(1))]))) + ((dsp.const173) * (rec50[(i) - (S32(2))])))) - ((dsp.const175) * (((dsp.const176) * (rec49[(i) - (S32(2))])) + ((dsp.const177) * (rec49[(i) - (S32(1))]))))
            vstore(dsp.rec49_perm, vload(rec49_tmp, vsize))
            vstore(dsp.rec49_perm, vload(rec49_tmp, vsize + wsize), wsize)
            vstore(rec48_tmp, vload(dsp.rec48_perm))
            vstore(rec48_tmp, vload(dsp.rec48_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec48[i] = ((slow34) * (rec48[(i) - (S32(1))])) + ((slow35) * (abs((dsp.const175) * ((((dsp.const179) * (rec49[i])) + ((dsp.const180) * (rec49[(i) - (S32(1))]))) + ((dsp.const179) * (rec49[(i) - (S32(2))]))))))
            vstore(dsp.rec48_perm, vload(rec48_tmp, vsize))
            vstore(dsp.rec48_perm, vload(rec48_tmp, vsize + wsize), wsize)
            vstore(rec61_tmp, vload(dsp.rec61_perm))
            vstore(rec61_tmp, vload(dsp.rec61_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec61[i] = (zec42[i]) - ((dsp.const181) * (((dsp.const182) * (rec61[(i) - (S32(2))])) + ((dsp.const183) * (rec61[(i) - (S32(1))]))))
            vstore(dsp.rec61_perm, vload(rec61_tmp, vsize))
            vstore(dsp.rec61_perm, vload(rec61_tmp, vsize + wsize), wsize)
            vstore(rec60_tmp, vload(dsp.rec60_perm))
            vstore(rec60_tmp, vload(dsp.rec60_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec60[i] = ((dsp.const181) * ((((dsp.const185) * (rec61[i])) + ((dsp.const186) * (rec61[(i) - (S32(1))]))) + ((dsp.const185) * (rec61[(i) - (S32(2))])))) - ((dsp.const187) * (((dsp.const188) * (rec60[(i) - (S32(2))])) + ((dsp.const189) * (rec60[(i) - (S32(1))]))))
            vstore(dsp.rec60_perm, vload(rec60_tmp, vsize))
            vstore(dsp.rec60_perm, vload(rec60_tmp, vsize + wsize), wsize)
            vstore(rec59_tmp, vload(dsp.rec59_perm))
            vstore(rec59_tmp, vload(dsp.rec59_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec59[i] = ((dsp.const187) * ((((dsp.const190) * (rec60[i])) + ((dsp.const191) * (rec60[(i) - (S32(1))]))) + ((dsp.const190) * (rec60[(i) - (S32(2))])))) - ((dsp.const192) * (((dsp.const193) * (rec59[(i) - (S32(2))])) + ((dsp.const194) * (rec59[(i) - (S32(1))]))))
            vstore(dsp.rec59_perm, vload(rec59_tmp, vsize))
            vstore(dsp.rec59_perm, vload(rec59_tmp, vsize + wsize), wsize)
            vstore(zec43, (dsp.const192) * ((((dsp.const195) * (vload(rec59))) + ((dsp.const196) * (vload(rec59, - S32(1))))) + ((dsp.const195) * (vload(rec59, - S32(2))))))
            vstore(zec43, (dsp.const192) * ((((dsp.const195) * (vload(rec59, wsize))) + ((dsp.const196) * (vload(rec59, - S32(1) + wsize)))) + ((dsp.const195) * (vload(rec59, - S32(2) + wsize)))), wsize)
            vstore(rec58_tmp, vload(dsp.rec58_perm))
            vstore(rec58_tmp, vload(dsp.rec58_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec58[i] = (zec43[i]) - ((dsp.const199) * (((dsp.const200) * (rec58[(i) - (S32(2))])) + ((dsp.const203) * (rec58[(i) - (S32(1))]))))
            vstore(dsp.rec58_perm, vload(rec58_tmp, vsize))
            vstore(dsp.rec58_perm, vload(rec58_tmp, vsize + wsize), wsize)
            vstore(rec57_tmp, vload(dsp.rec57_perm))
            vstore(rec57_tmp, vload(dsp.rec57_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec57[i] = ((dsp.const199) * ((((dsp.const205) * (rec58[i])) + ((dsp.const206) * (rec58[(i) - (S32(1))]))) + ((dsp.const205) * (rec58[(i) - (S32(2))])))) - ((dsp.const207) * (((dsp.const208) * (rec57[(i) - (S32(2))])) + ((dsp.const209) * (rec57[(i) - (S32(1))]))))
            vstore(dsp.rec57_perm, vload(rec57_tmp, vsize))
            vstore(dsp.rec57_perm, vload(rec57_tmp, vsize + wsize), wsize)
            vstore(rec56_tmp, vload(dsp.rec56_perm))
            vstore(rec56_tmp, vload(dsp.rec56_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec56[i] = ((dsp.const207) * ((((dsp.const211) * (rec57[i])) + ((dsp.const212) * (rec57[(i) - (S32(1))]))) + ((dsp.const211) * (rec57[(i) - (S32(2))])))) - ((dsp.const213) * (((dsp.const214) * (rec56[(i) - (S32(2))])) + ((dsp.const215) * (rec56[(i) - (S32(1))]))))
            vstore(dsp.rec56_perm, vload(rec56_tmp, vsize))
            vstore(dsp.rec56_perm, vload(rec56_tmp, vsize + wsize), wsize)
            vstore(rec55_tmp, vload(dsp.rec55_perm))
            vstore(rec55_tmp, vload(dsp.rec55_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec55[i] = ((slow34) * (rec55[(i) - (S32(1))])) + ((slow35) * (abs((dsp.const213) * ((((dsp.const217) * (rec56[i])) + ((dsp.const218) * (rec56[(i) - (S32(1))]))) + ((dsp.const217) * (rec56[(i) - (S32(2))]))))))
            vstore(dsp.rec55_perm, vload(rec55_tmp, vsize))
            vstore(dsp.rec55_perm, vload(rec55_tmp, vsize + wsize), wsize)
            vstore(rec68_tmp, vload(dsp.rec68_perm))
            vstore(rec68_tmp, vload(dsp.rec68_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec68[i] = (zec43[i]) - ((dsp.const219) * (((dsp.const220) * (rec68[(i) - (S32(2))])) + ((dsp.const221) * (rec68[(i) - (S32(1))]))))
            vstore(dsp.rec68_perm, vload(rec68_tmp, vsize))
            vstore(dsp.rec68_perm, vload(rec68_tmp, vsize + wsize), wsize)
            vstore(rec67_tmp, vload(dsp.rec67_perm))
            vstore(rec67_tmp, vload(dsp.rec67_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec67[i] = ((dsp.const219) * ((((dsp.const223) * (rec68[i])) + ((dsp.const224) * (rec68[(i) - (S32(1))]))) + ((dsp.const223) * (rec68[(i) - (S32(2))])))) - ((dsp.const225) * (((dsp.const226) * (rec67[(i) - (S32(2))])) + ((dsp.const227) * (rec67[(i) - (S32(1))]))))
            vstore(dsp.rec67_perm, vload(rec67_tmp, vsize))
            vstore(dsp.rec67_perm, vload(rec67_tmp, vsize + wsize), wsize)
            vstore(rec66_tmp, vload(dsp.rec66_perm))
            vstore(rec66_tmp, vload(dsp.rec66_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec66[i] = ((dsp.const225) * ((((dsp.const228) * (rec67[i])) + ((dsp.const229) * (rec67[(i) - (S32(1))]))) + ((dsp.const228) * (rec67[(i) - (S32(2))])))) - ((dsp.const230) * (((dsp.const231) * (rec66[(i) - (S32(2))])) + ((dsp.const232) * (rec66[(i) - (S32(1))]))))
            vstore(dsp.rec66_perm, vload(rec66_tmp, vsize))
            vstore(dsp.rec66_perm, vload(rec66_tmp, vsize + wsize), wsize)
            vstore(zec44, (dsp.const230) * ((((dsp.const233) * (vload(rec66))) + ((dsp.const234) * (vload(rec66, - S32(1))))) + ((dsp.const233) * (vload(rec66, - S32(2))))))
            vstore(zec44, (dsp.const230) * ((((dsp.const233) * (vload(rec66, wsize))) + ((dsp.const234) * (vload(rec66, - S32(1) + wsize)))) + ((dsp.const233) * (vload(rec66, - S32(2) + wsize)))), wsize)
            vstore(rec65_tmp, vload(dsp.rec65_perm))
            vstore(rec65_tmp, vload(dsp.rec65_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec65[i] = (zec44[i]) - ((dsp.const237) * (((dsp.const238) * (rec65[(i) - (S32(2))])) + ((dsp.const241) * (rec65[(i) - (S32(1))]))))
            vstore(dsp.rec65_perm, vload(rec65_tmp, vsize))
            vstore(dsp.rec65_perm, vload(rec65_tmp, vsize + wsize), wsize)
            vstore(rec64_tmp, vload(dsp.rec64_perm))
            vstore(rec64_tmp, vload(dsp.rec64_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec64[i] = ((dsp.const237) * ((((dsp.const243) * (rec65[i])) + ((dsp.const244) * (rec65[(i) - (S32(1))]))) + ((dsp.const243) * (rec65[(i) - (S32(2))])))) - ((dsp.const245) * (((dsp.const246) * (rec64[(i) - (S32(2))])) + ((dsp.const247) * (rec64[(i) - (S32(1))]))))
            vstore(dsp.rec64_perm, vload(rec64_tmp, vsize))
            vstore(dsp.rec64_perm, vload(rec64_tmp, vsize + wsize), wsize)
            vstore(rec63_tmp, vload(dsp.rec63_perm))
            vstore(rec63_tmp, vload(dsp.rec63_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec63[i] = ((dsp.const245) * ((((dsp.const249) * (rec64[i])) + ((dsp.const250) * (rec64[(i) - (S32(1))]))) + ((dsp.const249) * (rec64[(i) - (S32(2))])))) - ((dsp.const251) * (((dsp.const252) * (rec63[(i) - (S32(2))])) + ((dsp.const253) * (rec63[(i) - (S32(1))]))))
            vstore(dsp.rec63_perm, vload(rec63_tmp, vsize))
            vstore(dsp.rec63_perm, vload(rec63_tmp, vsize + wsize), wsize)
            vstore(rec62_tmp, vload(dsp.rec62_perm))
            vstore(rec62_tmp, vload(dsp.rec62_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec62[i] = ((slow34) * (rec62[(i) - (S32(1))])) + ((slow35) * (abs((dsp.const251) * ((((dsp.const255) * (rec63[i])) + ((dsp.const256) * (rec63[(i) - (S32(1))]))) + ((dsp.const255) * (rec63[(i) - (S32(2))]))))))
            vstore(dsp.rec62_perm, vload(rec62_tmp, vsize))
            vstore(dsp.rec62_perm, vload(rec62_tmp, vsize + wsize), wsize)
            vstore(rec75_tmp, vload(dsp.rec75_perm))
            vstore(rec75_tmp, vload(dsp.rec75_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec75[i] = (zec44[i]) - ((dsp.const257) * (((dsp.const258) * (rec75[(i) - (S32(2))])) + ((dsp.const259) * (rec75[(i) - (S32(1))]))))
            vstore(dsp.rec75_perm, vload(rec75_tmp, vsize))
            vstore(dsp.rec75_perm, vload(rec75_tmp, vsize + wsize), wsize)
            vstore(rec74_tmp, vload(dsp.rec74_perm))
            vstore(rec74_tmp, vload(dsp.rec74_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec74[i] = ((dsp.const257) * ((((dsp.const261) * (rec75[i])) + ((dsp.const262) * (rec75[(i) - (S32(1))]))) + ((dsp.const261) * (rec75[(i) - (S32(2))])))) - ((dsp.const263) * (((dsp.const264) * (rec74[(i) - (S32(2))])) + ((dsp.const265) * (rec74[(i) - (S32(1))]))))
            vstore(dsp.rec74_perm, vload(rec74_tmp, vsize))
            vstore(dsp.rec74_perm, vload(rec74_tmp, vsize + wsize), wsize)
            vstore(rec73_tmp, vload(dsp.rec73_perm))
            vstore(rec73_tmp, vload(dsp.rec73_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec73[i] = ((dsp.const263) * ((((dsp.const266) * (rec74[i])) + ((dsp.const267) * (rec74[(i) - (S32(1))]))) + ((dsp.const266) * (rec74[(i) - (S32(2))])))) - ((dsp.const268) * (((dsp.const269) * (rec73[(i) - (S32(2))])) + ((dsp.const270) * (rec73[(i) - (S32(1))]))))
            vstore(dsp.rec73_perm, vload(rec73_tmp, vsize))
            vstore(dsp.rec73_perm, vload(rec73_tmp, vsize + wsize), wsize)
            vstore(zec45, (dsp.const268) * ((((dsp.const271) * (vload(rec73))) + ((dsp.const272) * (vload(rec73, - S32(1))))) + ((dsp.const271) * (vload(rec73, - S32(2))))))
            vstore(zec45, (dsp.const268) * ((((dsp.const271) * (vload(rec73, wsize))) + ((dsp.const272) * (vload(rec73, - S32(1) + wsize)))) + ((dsp.const271) * (vload(rec73, - S32(2) + wsize)))), wsize)
            vstore(rec72_tmp, vload(dsp.rec72_perm))
            vstore(rec72_tmp, vload(dsp.rec72_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec72[i] = (zec45[i]) - ((dsp.const275) * (((dsp.const276) * (rec72[(i) - (S32(2))])) + ((dsp.const279) * (rec72[(i) - (S32(1))]))))
            vstore(dsp.rec72_perm, vload(rec72_tmp, vsize))
            vstore(dsp.rec72_perm, vload(rec72_tmp, vsize + wsize), wsize)
            vstore(rec71_tmp, vload(dsp.rec71_perm))
            vstore(rec71_tmp, vload(dsp.rec71_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec71[i] = ((dsp.const275) * ((((dsp.const281) * (rec72[i])) + ((dsp.const282) * (rec72[(i) - (S32(1))]))) + ((dsp.const281) * (rec72[(i) - (S32(2))])))) - ((dsp.const283) * (((dsp.const284) * (rec71[(i) - (S32(2))])) + ((dsp.const285) * (rec71[(i) - (S32(1))]))))
            vstore(dsp.rec71_perm, vload(rec71_tmp, vsize))
            vstore(dsp.rec71_perm, vload(rec71_tmp, vsize + wsize), wsize)
            vstore(rec70_tmp, vload(dsp.rec70_perm))
            vstore(rec70_tmp, vload(dsp.rec70_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec70[i] = ((dsp.const283) * ((((dsp.const287) * (rec71[i])) + ((dsp.const288) * (rec71[(i) - (S32(1))]))) + ((dsp.const287) * (rec71[(i) - (S32(2))])))) - ((dsp.const289) * (((dsp.const290) * (rec70[(i) - (S32(2))])) + ((dsp.const291) * (rec70[(i) - (S32(1))]))))
            vstore(dsp.rec70_perm, vload(rec70_tmp, vsize))
            vstore(dsp.rec70_perm, vload(rec70_tmp, vsize + wsize), wsize)
            vstore(rec69_tmp, vload(dsp.rec69_perm))
            vstore(rec69_tmp, vload(dsp.rec69_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec69[i] = ((slow34) * (rec69[(i) - (S32(1))])) + ((slow35) * (abs((dsp.const289) * ((((dsp.const293) * (rec70[i])) + ((dsp.const294) * (rec70[(i) - (S32(1))]))) + ((dsp.const293) * (rec70[(i) - (S32(2))]))))))
            vstore(dsp.rec69_perm, vload(rec69_tmp, vsize))
            vstore(dsp.rec69_perm, vload(rec69_tmp, vsize + wsize), wsize)
            vstore(rec82_tmp, vload(dsp.rec82_perm))
            vstore(rec82_tmp, vload(dsp.rec82_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec82[i] = (zec45[i]) - ((dsp.const295) * (((dsp.const296) * (rec82[(i) - (S32(2))])) + ((dsp.const297) * (rec82[(i) - (S32(1))]))))
            vstore(dsp.rec82_perm, vload(rec82_tmp, vsize))
            vstore(dsp.rec82_perm, vload(rec82_tmp, vsize + wsize), wsize)
            vstore(rec81_tmp, vload(dsp.rec81_perm))
            vstore(rec81_tmp, vload(dsp.rec81_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec81[i] = ((dsp.const295) * ((((dsp.const299) * (rec82[i])) + ((dsp.const300) * (rec82[(i) - (S32(1))]))) + ((dsp.const299) * (rec82[(i) - (S32(2))])))) - ((dsp.const301) * (((dsp.const302) * (rec81[(i) - (S32(2))])) + ((dsp.const303) * (rec81[(i) - (S32(1))]))))
            vstore(dsp.rec81_perm, vload(rec81_tmp, vsize))
            vstore(dsp.rec81_perm, vload(rec81_tmp, vsize + wsize), wsize)
            vstore(rec80_tmp, vload(dsp.rec80_perm))
            vstore(rec80_tmp, vload(dsp.rec80_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec80[i] = ((dsp.const301) * ((((dsp.const304) * (rec81[i])) + ((dsp.const305) * (rec81[(i) - (S32(1))]))) + ((dsp.const304) * (rec81[(i) - (S32(2))])))) - ((dsp.const306) * (((dsp.const307) * (rec80[(i) - (S32(2))])) + ((dsp.const308) * (rec80[(i) - (S32(1))]))))
            vstore(dsp.rec80_perm, vload(rec80_tmp, vsize))
            vstore(dsp.rec80_perm, vload(rec80_tmp, vsize + wsize), wsize)
            vstore(zec46, (dsp.const306) * ((((dsp.const309) * (vload(rec80))) + ((dsp.const310) * (vload(rec80, - S32(1))))) + ((dsp.const309) * (vload(rec80, - S32(2))))))
            vstore(zec46, (dsp.const306) * ((((dsp.const309) * (vload(rec80, wsize))) + ((dsp.const310) * (vload(rec80, - S32(1) + wsize)))) + ((dsp.const309) * (vload(rec80, - S32(2) + wsize)))), wsize)
            vstore(rec79_tmp, vload(dsp.rec79_perm))
            vstore(rec79_tmp, vload(dsp.rec79_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec79[i] = (zec46[i]) - ((dsp.const313) * (((dsp.const314) * (rec79[(i) - (S32(2))])) + ((dsp.const317) * (rec79[(i) - (S32(1))]))))
            vstore(dsp.rec79_perm, vload(rec79_tmp, vsize))
            vstore(dsp.rec79_perm, vload(rec79_tmp, vsize + wsize), wsize)
            vstore(rec78_tmp, vload(dsp.rec78_perm))
            vstore(rec78_tmp, vload(dsp.rec78_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec78[i] = ((dsp.const313) * ((((dsp.const319) * (rec79[i])) + ((dsp.const320) * (rec79[(i) - (S32(1))]))) + ((dsp.const319) * (rec79[(i) - (S32(2))])))) - ((dsp.const321) * (((dsp.const322) * (rec78[(i) - (S32(2))])) + ((dsp.const323) * (rec78[(i) - (S32(1))]))))
            vstore(dsp.rec78_perm, vload(rec78_tmp, vsize))
            vstore(dsp.rec78_perm, vload(rec78_tmp, vsize + wsize), wsize)
            vstore(rec77_tmp, vload(dsp.rec77_perm))
            vstore(rec77_tmp, vload(dsp.rec77_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec77[i] = ((dsp.const321) * ((((dsp.const325) * (rec78[i])) + ((dsp.const326) * (rec78[(i) - (S32(1))]))) + ((dsp.const325) * (rec78[(i) - (S32(2))])))) - ((dsp.const327) * (((dsp.const328) * (rec77[(i) - (S32(2))])) + ((dsp.const329) * (rec77[(i) - (S32(1))]))))
            vstore(dsp.rec77_perm, vload(rec77_tmp, vsize))
            vstore(dsp.rec77_perm, vload(rec77_tmp, vsize + wsize), wsize)
            vstore(rec76_tmp, vload(dsp.rec76_perm))
            vstore(rec76_tmp, vload(dsp.rec76_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec76[i] = ((slow34) * (rec76[(i) - (S32(1))])) + ((slow35) * (abs((dsp.const327) * ((((dsp.const331) * (rec77[i])) + ((dsp.const332) * (rec77[(i) - (S32(1))]))) + ((dsp.const331) * (rec77[(i) - (S32(2))]))))))
            vstore(dsp.rec76_perm, vload(rec76_tmp, vsize))
            vstore(dsp.rec76_perm, vload(rec76_tmp, vsize + wsize), wsize)
            vstore(rec89_tmp, vload(dsp.rec89_perm))
            vstore(rec89_tmp, vload(dsp.rec89_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec89[i] = (zec46[i]) - ((dsp.const333) * (((dsp.const334) * (rec89[(i) - (S32(2))])) + ((dsp.const335) * (rec89[(i) - (S32(1))]))))
            vstore(dsp.rec89_perm, vload(rec89_tmp, vsize))
            vstore(dsp.rec89_perm, vload(rec89_tmp, vsize + wsize), wsize)
            vstore(rec88_tmp, vload(dsp.rec88_perm))
            vstore(rec88_tmp, vload(dsp.rec88_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec88[i] = ((dsp.const333) * ((((dsp.const337) * (rec89[i])) + ((dsp.const338) * (rec89[(i) - (S32(1))]))) + ((dsp.const337) * (rec89[(i) - (S32(2))])))) - ((dsp.const339) * (((dsp.const340) * (rec88[(i) - (S32(2))])) + ((dsp.const341) * (rec88[(i) - (S32(1))]))))
            vstore(dsp.rec88_perm, vload(rec88_tmp, vsize))
            vstore(dsp.rec88_perm, vload(rec88_tmp, vsize + wsize), wsize)
            vstore(rec87_tmp, vload(dsp.rec87_perm))
            vstore(rec87_tmp, vload(dsp.rec87_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec87[i] = ((dsp.const339) * ((((dsp.const342) * (rec88[i])) + ((dsp.const343) * (rec88[(i) - (S32(1))]))) + ((dsp.const342) * (rec88[(i) - (S32(2))])))) - ((dsp.const344) * (((dsp.const345) * (rec87[(i) - (S32(2))])) + ((dsp.const346) * (rec87[(i) - (S32(1))]))))
            vstore(dsp.rec87_perm, vload(rec87_tmp, vsize))
            vstore(dsp.rec87_perm, vload(rec87_tmp, vsize + wsize), wsize)
            vstore(zec47, (dsp.const344) * ((((dsp.const347) * (vload(rec87))) + ((dsp.const348) * (vload(rec87, - S32(1))))) + ((dsp.const347) * (vload(rec87, - S32(2))))))
            vstore(zec47, (dsp.const344) * ((((dsp.const347) * (vload(rec87, wsize))) + ((dsp.const348) * (vload(rec87, - S32(1) + wsize)))) + ((dsp.const347) * (vload(rec87, - S32(2) + wsize)))), wsize)
            vstore(rec86_tmp, vload(dsp.rec86_perm))
            vstore(rec86_tmp, vload(dsp.rec86_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec86[i] = (zec47[i]) - ((dsp.const351) * (((dsp.const352) * (rec86[(i) - (S32(2))])) + ((dsp.const355) * (rec86[(i) - (S32(1))]))))
            vstore(dsp.rec86_perm, vload(rec86_tmp, vsize))
            vstore(dsp.rec86_perm, vload(rec86_tmp, vsize + wsize), wsize)
            vstore(rec85_tmp, vload(dsp.rec85_perm))
            vstore(rec85_tmp, vload(dsp.rec85_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec85[i] = ((dsp.const351) * ((((dsp.const357) * (rec86[i])) + ((dsp.const358) * (rec86[(i) - (S32(1))]))) + ((dsp.const357) * (rec86[(i) - (S32(2))])))) - ((dsp.const359) * (((dsp.const360) * (rec85[(i) - (S32(2))])) + ((dsp.const361) * (rec85[(i) - (S32(1))]))))
            vstore(dsp.rec85_perm, vload(rec85_tmp, vsize))
            vstore(dsp.rec85_perm, vload(rec85_tmp, vsize + wsize), wsize)
            vstore(rec84_tmp, vload(dsp.rec84_perm))
            vstore(rec84_tmp, vload(dsp.rec84_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec84[i] = ((dsp.const359) * ((((dsp.const363) * (rec85[i])) + ((dsp.const364) * (rec85[(i) - (S32(1))]))) + ((dsp.const363) * (rec85[(i) - (S32(2))])))) - ((dsp.const365) * (((dsp.const366) * (rec84[(i) - (S32(2))])) + ((dsp.const367) * (rec84[(i) - (S32(1))]))))
            vstore(dsp.rec84_perm, vload(rec84_tmp, vsize))
            vstore(dsp.rec84_perm, vload(rec84_tmp, vsize + wsize), wsize)
            vstore(rec83_tmp, vload(dsp.rec83_perm))
            vstore(rec83_tmp, vload(dsp.rec83_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec83[i] = ((slow34) * (rec83[(i) - (S32(1))])) + ((slow35) * (abs((dsp.const365) * ((((dsp.const369) * (rec84[i])) + ((dsp.const370) * (rec84[(i) - (S32(1))]))) + ((dsp.const369) * (rec84[(i) - (S32(2))]))))))
            vstore(dsp.rec83_perm, vload(rec83_tmp, vsize))
            vstore(dsp.rec83_perm, vload(rec83_tmp, vsize + wsize), wsize)
            vstore(rec96_tmp, vload(dsp.rec96_perm))
            vstore(rec96_tmp, vload(dsp.rec96_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec96[i] = (zec47[i]) - ((dsp.const371) * (((dsp.const372) * (rec96[(i) - (S32(2))])) + ((dsp.const373) * (rec96[(i) - (S32(1))]))))
            vstore(dsp.rec96_perm, vload(rec96_tmp, vsize))
            vstore(dsp.rec96_perm, vload(rec96_tmp, vsize + wsize), wsize)
            vstore(rec95_tmp, vload(dsp.rec95_perm))
            vstore(rec95_tmp, vload(dsp.rec95_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec95[i] = ((dsp.const371) * ((((dsp.const375) * (rec96[i])) + ((dsp.const376) * (rec96[(i) - (S32(1))]))) + ((dsp.const375) * (rec96[(i) - (S32(2))])))) - ((dsp.const377) * (((dsp.const378) * (rec95[(i) - (S32(2))])) + ((dsp.const379) * (rec95[(i) - (S32(1))]))))
            vstore(dsp.rec95_perm, vload(rec95_tmp, vsize))
            vstore(dsp.rec95_perm, vload(rec95_tmp, vsize + wsize), wsize)
            vstore(rec94_tmp, vload(dsp.rec94_perm))
            vstore(rec94_tmp, vload(dsp.rec94_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec94[i] = ((dsp.const377) * ((((dsp.const380) * (rec95[i])) + ((dsp.const381) * (rec95[(i) - (S32(1))]))) + ((dsp.const380) * (rec95[(i) - (S32(2))])))) - ((dsp.const382) * (((dsp.const383) * (rec94[(i) - (S32(2))])) + ((dsp.const384) * (rec94[(i) - (S32(1))]))))
            vstore(dsp.rec94_perm, vload(rec94_tmp, vsize))
            vstore(dsp.rec94_perm, vload(rec94_tmp, vsize + wsize), wsize)
            vstore(zec48, (dsp.const382) * ((((dsp.const385) * (vload(rec94))) + ((dsp.const386) * (vload(rec94, - S32(1))))) + ((dsp.const385) * (vload(rec94, - S32(2))))))
            vstore(zec48, (dsp.const382) * ((((dsp.const385) * (vload(rec94, wsize))) + ((dsp.const386) * (vload(rec94, - S32(1) + wsize)))) + ((dsp.const385) * (vload(rec94, - S32(2) + wsize)))), wsize)
            vstore(rec93_tmp, vload(dsp.rec93_perm))
            vstore(rec93_tmp, vload(dsp.rec93_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec93[i] = (zec48[i]) - ((dsp.const389) * (((dsp.const390) * (rec93[(i) - (S32(2))])) + ((dsp.const393) * (rec93[(i) - (S32(1))]))))
            vstore(dsp.rec93_perm, vload(rec93_tmp, vsize))
            vstore(dsp.rec93_perm, vload(rec93_tmp, vsize + wsize), wsize)
            vstore(rec92_tmp, vload(dsp.rec92_perm))
            vstore(rec92_tmp, vload(dsp.rec92_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec92[i] = ((dsp.const389) * ((((dsp.const395) * (rec93[i])) + ((dsp.const396) * (rec93[(i) - (S32(1))]))) + ((dsp.const395) * (rec93[(i) - (S32(2))])))) - ((dsp.const397) * (((dsp.const398) * (rec92[(i) - (S32(2))])) + ((dsp.const399) * (rec92[(i) - (S32(1))]))))
            vstore(dsp.rec92_perm, vload(rec92_tmp, vsize))
            vstore(dsp.rec92_perm, vload(rec92_tmp, vsize + wsize), wsize)
            vstore(rec91_tmp, vload(dsp.rec91_perm))
            vstore(rec91_tmp, vload(dsp.rec91_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec91[i] = ((dsp.const397) * ((((dsp.const401) * (rec92[i])) + ((dsp.const402) * (rec92[(i) - (S32(1))]))) + ((dsp.const401) * (rec92[(i) - (S32(2))])))) - ((dsp.const403) * (((dsp.const404) * (rec91[(i) - (S32(2))])) + ((dsp.const405) * (rec91[(i) - (S32(1))]))))
            vstore(dsp.rec91_perm, vload(rec91_tmp, vsize))
            vstore(dsp.rec91_perm, vload(rec91_tmp, vsize + wsize), wsize)
            vstore(rec90_tmp, vload(dsp.rec90_perm))
            vstore(rec90_tmp, vload(dsp.rec90_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec90[i] = ((slow34) * (rec90[(i) - (S32(1))])) + ((slow35) * (abs((dsp.const403) * ((((dsp.const407) * (rec91[i])) + ((dsp.const408) * (rec91[(i) - (S32(1))]))) + ((dsp.const407) * (rec91[(i) - (S32(2))]))))))
            vstore(dsp.rec90_perm, vload(rec90_tmp, vsize))
            vstore(dsp.rec90_perm, vload(rec90_tmp, vsize + wsize), wsize)
            vstore(rec103_tmp, vload(dsp.rec103_perm))
            vstore(rec103_tmp, vload(dsp.rec103_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec103[i] = (zec48[i]) - ((dsp.const409) * (((dsp.const410) * (rec103[(i) - (S32(2))])) + ((dsp.const411) * (rec103[(i) - (S32(1))]))))
            vstore(dsp.rec103_perm, vload(rec103_tmp, vsize))
            vstore(dsp.rec103_perm, vload(rec103_tmp, vsize + wsize), wsize)
            vstore(rec102_tmp, vload(dsp.rec102_perm))
            vstore(rec102_tmp, vload(dsp.rec102_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec102[i] = ((dsp.const409) * ((((dsp.const413) * (rec103[i])) + ((dsp.const414) * (rec103[(i) - (S32(1))]))) + ((dsp.const413) * (rec103[(i) - (S32(2))])))) - ((dsp.const415) * (((dsp.const416) * (rec102[(i) - (S32(2))])) + ((dsp.const417) * (rec102[(i) - (S32(1))]))))
            vstore(dsp.rec102_perm, vload(rec102_tmp, vsize))
            vstore(dsp.rec102_perm, vload(rec102_tmp, vsize + wsize), wsize)
            vstore(rec101_tmp, vload(dsp.rec101_perm))
            vstore(rec101_tmp, vload(dsp.rec101_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec101[i] = ((dsp.const415) * ((((dsp.const418) * (rec102[i])) + ((dsp.const419) * (rec102[(i) - (S32(1))]))) + ((dsp.const418) * (rec102[(i) - (S32(2))])))) - ((dsp.const420) * (((dsp.const421) * (rec101[(i) - (S32(2))])) + ((dsp.const422) * (rec101[(i) - (S32(1))]))))
            vstore(dsp.rec101_perm, vload(rec101_tmp, vsize))
            vstore(dsp.rec101_perm, vload(rec101_tmp, vsize + wsize), wsize)
            vstore(zec49, (dsp.const420) * ((((dsp.const423) * (vload(rec101))) + ((dsp.const424) * (vload(rec101, - S32(1))))) + ((dsp.const423) * (vload(rec101, - S32(2))))))
            vstore(zec49, (dsp.const420) * ((((dsp.const423) * (vload(rec101, wsize))) + ((dsp.const424) * (vload(rec101, - S32(1) + wsize)))) + ((dsp.const423) * (vload(rec101, - S32(2) + wsize)))), wsize)
            vstore(rec100_tmp, vload(dsp.rec100_perm))
            vstore(rec100_tmp, vload(dsp.rec100_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec100[i] = (zec49[i]) - ((dsp.const427) * (((dsp.const428) * (rec100[(i) - (S32(2))])) + ((dsp.const431) * (rec100[(i) - (S32(1))]))))
            vstore(dsp.rec100_perm, vload(rec100_tmp, vsize))
            vstore(dsp.rec100_perm, vload(rec100_tmp, vsize + wsize), wsize)
            vstore(rec99_tmp, vload(dsp.rec99_perm))
            vstore(rec99_tmp, vload(dsp.rec99_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec99[i] = ((dsp.const427) * ((((dsp.const433) * (rec100[i])) + ((dsp.const434) * (rec100[(i) - (S32(1))]))) + ((dsp.const433) * (rec100[(i) - (S32(2))])))) - ((dsp.const435) * (((dsp.const436) * (rec99[(i) - (S32(2))])) + ((dsp.const437) * (rec99[(i) - (S32(1))]))))
            vstore(dsp.rec99_perm, vload(rec99_tmp, vsize))
            vstore(dsp.rec99_perm, vload(rec99_tmp, vsize + wsize), wsize)
            vstore(rec98_tmp, vload(dsp.rec98_perm))
            vstore(rec98_tmp, vload(dsp.rec98_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec98[i] = ((dsp.const435) * ((((dsp.const439) * (rec99[i])) + ((dsp.const440) * (rec99[(i) - (S32(1))]))) + ((dsp.const439) * (rec99[(i) - (S32(2))])))) - ((dsp.const441) * (((dsp.const442) * (rec98[(i) - (S32(2))])) + ((dsp.const443) * (rec98[(i) - (S32(1))]))))
            vstore(dsp.rec98_perm, vload(rec98_tmp, vsize))
            vstore(dsp.rec98_perm, vload(rec98_tmp, vsize + wsize), wsize)
            vstore(rec97_tmp, vload(dsp.rec97_perm))
            vstore(rec97_tmp, vload(dsp.rec97_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec97[i] = ((slow34) * (rec97[(i) - (S32(1))])) + ((slow35) * (abs((dsp.const441) * ((((dsp.const445) * (rec98[i])) + ((dsp.const446) * (rec98[(i) - (S32(1))]))) + ((dsp.const445) * (rec98[(i) - (S32(2))]))))))
            vstore(dsp.rec97_perm, vload(rec97_tmp, vsize))
            vstore(dsp.rec97_perm, vload(rec97_tmp, vsize + wsize), wsize)
            vstore(rec110_tmp, vload(dsp.rec110_perm))
            vstore(rec110_tmp, vload(dsp.rec110_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec110[i] = (zec49[i]) - ((dsp.const447) * (((dsp.const448) * (rec110[(i) - (S32(2))])) + ((dsp.const449) * (rec110[(i) - (S32(1))]))))
            vstore(dsp.rec110_perm, vload(rec110_tmp, vsize))
            vstore(dsp.rec110_perm, vload(rec110_tmp, vsize + wsize), wsize)
            vstore(rec109_tmp, vload(dsp.rec109_perm))
            vstore(rec109_tmp, vload(dsp.rec109_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec109[i] = ((dsp.const447) * ((((dsp.const451) * (rec110[i])) + ((dsp.const452) * (rec110[(i) - (S32(1))]))) + ((dsp.const451) * (rec110[(i) - (S32(2))])))) - ((dsp.const453) * (((dsp.const454) * (rec109[(i) - (S32(2))])) + ((dsp.const455) * (rec109[(i) - (S32(1))]))))
            vstore(dsp.rec109_perm, vload(rec109_tmp, vsize))
            vstore(dsp.rec109_perm, vload(rec109_tmp, vsize + wsize), wsize)
            vstore(rec108_tmp, vload(dsp.rec108_perm))
            vstore(rec108_tmp, vload(dsp.rec108_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec108[i] = ((dsp.const453) * ((((dsp.const456) * (rec109[i])) + ((dsp.const457) * (rec109[(i) - (S32(1))]))) + ((dsp.const456) * (rec109[(i) - (S32(2))])))) - ((dsp.const458) * (((dsp.const459) * (rec108[(i) - (S32(2))])) + ((dsp.const460) * (rec108[(i) - (S32(1))]))))
            vstore(dsp.rec108_perm, vload(rec108_tmp, vsize))
            vstore(dsp.rec108_perm, vload(rec108_tmp, vsize + wsize), wsize)
            vstore(zec50, (dsp.const458) * ((((dsp.const461) * (vload(rec108))) + ((dsp.const462) * (vload(rec108, - S32(1))))) + ((dsp.const461) * (vload(rec108, - S32(2))))))
            vstore(zec50, (dsp.const458) * ((((dsp.const461) * (vload(rec108, wsize))) + ((dsp.const462) * (vload(rec108, - S32(1) + wsize)))) + ((dsp.const461) * (vload(rec108, - S32(2) + wsize)))), wsize)
            vstore(rec107_tmp, vload(dsp.rec107_perm))
            vstore(rec107_tmp, vload(dsp.rec107_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec107[i] = (zec50[i]) - ((dsp.const465) * (((dsp.const466) * (rec107[(i) - (S32(2))])) + ((dsp.const469) * (rec107[(i) - (S32(1))]))))
            vstore(dsp.rec107_perm, vload(rec107_tmp, vsize))
            vstore(dsp.rec107_perm, vload(rec107_tmp, vsize + wsize), wsize)
            vstore(rec106_tmp, vload(dsp.rec106_perm))
            vstore(rec106_tmp, vload(dsp.rec106_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec106[i] = ((dsp.const465) * ((((dsp.const471) * (rec107[i])) + ((dsp.const472) * (rec107[(i) - (S32(1))]))) + ((dsp.const471) * (rec107[(i) - (S32(2))])))) - ((dsp.const473) * (((dsp.const474) * (rec106[(i) - (S32(2))])) + ((dsp.const475) * (rec106[(i) - (S32(1))]))))
            vstore(dsp.rec106_perm, vload(rec106_tmp, vsize))
            vstore(dsp.rec106_perm, vload(rec106_tmp, vsize + wsize), wsize)
            vstore(rec105_tmp, vload(dsp.rec105_perm))
            vstore(rec105_tmp, vload(dsp.rec105_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec105[i] = ((dsp.const473) * ((((dsp.const477) * (rec106[i])) + ((dsp.const478) * (rec106[(i) - (S32(1))]))) + ((dsp.const477) * (rec106[(i) - (S32(2))])))) - ((dsp.const479) * (((dsp.const480) * (rec105[(i) - (S32(2))])) + ((dsp.const481) * (rec105[(i) - (S32(1))]))))
            vstore(dsp.rec105_perm, vload(rec105_tmp, vsize))
            vstore(dsp.rec105_perm, vload(rec105_tmp, vsize + wsize), wsize)
            vstore(rec104_tmp, vload(dsp.rec104_perm))
            vstore(rec104_tmp, vload(dsp.rec104_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec104[i] = ((slow34) * (rec104[(i) - (S32(1))])) + ((slow35) * (abs((dsp.const479) * ((((dsp.const483) * (rec105[i])) + ((dsp.const484) * (rec105[(i) - (S32(1))]))) + ((dsp.const483) * (rec105[(i) - (S32(2))]))))))
            vstore(dsp.rec104_perm, vload(rec104_tmp, vsize))
            vstore(dsp.rec104_perm, vload(rec104_tmp, vsize + wsize), wsize)
            vstore(rec117_tmp, vload(dsp.rec117_perm))
            vstore(rec117_tmp, vload(dsp.rec117_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec117[i] = (zec50[i]) - ((dsp.const485) * (((dsp.const486) * (rec117[(i) - (S32(2))])) + ((dsp.const487) * (rec117[(i) - (S32(1))]))))
            vstore(dsp.rec117_perm, vload(rec117_tmp, vsize))
            vstore(dsp.rec117_perm, vload(rec117_tmp, vsize + wsize), wsize)
            vstore(rec116_tmp, vload(dsp.rec116_perm))
            vstore(rec116_tmp, vload(dsp.rec116_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec116[i] = ((dsp.const485) * ((((dsp.const489) * (rec117[i])) + ((dsp.const490) * (rec117[(i) - (S32(1))]))) + ((dsp.const489) * (rec117[(i) - (S32(2))])))) - ((dsp.const491) * (((dsp.const492) * (rec116[(i) - (S32(2))])) + ((dsp.const493) * (rec116[(i) - (S32(1))]))))
            vstore(dsp.rec116_perm, vload(rec116_tmp, vsize))
            vstore(dsp.rec116_perm, vload(rec116_tmp, vsize + wsize), wsize)
            vstore(rec115_tmp, vload(dsp.rec115_perm))
            vstore(rec115_tmp, vload(dsp.rec115_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec115[i] = ((dsp.const491) * ((((dsp.const494) * (rec116[i])) + ((dsp.const495) * (rec116[(i) - (S32(1))]))) + ((dsp.const494) * (rec116[(i) - (S32(2))])))) - ((dsp.const496) * (((dsp.const497) * (rec115[(i) - (S32(2))])) + ((dsp.const498) * (rec115[(i) - (S32(1))]))))
            vstore(dsp.rec115_perm, vload(rec115_tmp, vsize))
            vstore(dsp.rec115_perm, vload(rec115_tmp, vsize + wsize), wsize)
            vstore(zec51, (dsp.const496) * ((((dsp.const499) * (vload(rec115))) + ((dsp.const500) * (vload(rec115, - S32(1))))) + ((dsp.const499) * (vload(rec115, - S32(2))))))
            vstore(zec51, (dsp.const496) * ((((dsp.const499) * (vload(rec115, wsize))) + ((dsp.const500) * (vload(rec115, - S32(1) + wsize)))) + ((dsp.const499) * (vload(rec115, - S32(2) + wsize)))), wsize)
            vstore(rec114_tmp, vload(dsp.rec114_perm))
            vstore(rec114_tmp, vload(dsp.rec114_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec114[i] = (zec51[i]) - ((dsp.const503) * (((dsp.const504) * (rec114[(i) - (S32(2))])) + ((dsp.const507) * (rec114[(i) - (S32(1))]))))
            vstore(dsp.rec114_perm, vload(rec114_tmp, vsize))
            vstore(dsp.rec114_perm, vload(rec114_tmp, vsize + wsize), wsize)
            vstore(rec113_tmp, vload(dsp.rec113_perm))
            vstore(rec113_tmp, vload(dsp.rec113_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec113[i] = ((dsp.const503) * ((((dsp.const509) * (rec114[i])) + ((dsp.const510) * (rec114[(i) - (S32(1))]))) + ((dsp.const509) * (rec114[(i) - (S32(2))])))) - ((dsp.const511) * (((dsp.const512) * (rec113[(i) - (S32(2))])) + ((dsp.const513) * (rec113[(i) - (S32(1))]))))
            vstore(dsp.rec113_perm, vload(rec113_tmp, vsize))
            vstore(dsp.rec113_perm, vload(rec113_tmp, vsize + wsize), wsize)
            vstore(rec112_tmp, vload(dsp.rec112_perm))
            vstore(rec112_tmp, vload(dsp.rec112_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec112[i] = ((dsp.const511) * ((((dsp.const515) * (rec113[i])) + ((dsp.const516) * (rec113[(i) - (S32(1))]))) + ((dsp.const515) * (rec113[(i) - (S32(2))])))) - ((dsp.const517) * (((dsp.const518) * (rec112[(i) - (S32(2))])) + ((dsp.const519) * (rec112[(i) - (S32(1))]))))
            vstore(dsp.rec112_perm, vload(rec112_tmp, vsize))
            vstore(dsp.rec112_perm, vload(rec112_tmp, vsize + wsize), wsize)
            vstore(rec111_tmp, vload(dsp.rec111_perm))
            vstore(rec111_tmp, vload(dsp.rec111_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec111[i] = ((slow34) * (rec111[(i) - (S32(1))])) + ((slow35) * (abs((dsp.const517) * ((((dsp.const521) * (rec112[i])) + ((dsp.const522) * (rec112[(i) - (S32(1))]))) + ((dsp.const521) * (rec112[(i) - (S32(2))]))))))
            vstore(dsp.rec111_perm, vload(rec111_tmp, vsize))
            vstore(dsp.rec111_perm, vload(rec111_tmp, vsize + wsize), wsize)
            vstore(rec121_tmp, vload(dsp.rec121_perm))
            vstore(rec121_tmp, vload(dsp.rec121_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec121[i] = (zec51[i]) - ((dsp.const523) * (((dsp.const524) * (rec121[(i) - (S32(2))])) + ((dsp.const525) * (rec121[(i) - (S32(1))]))))
            vstore(dsp.rec121_perm, vload(rec121_tmp, vsize))
            vstore(dsp.rec121_perm, vload(rec121_tmp, vsize + wsize), wsize)
            vstore(rec120_tmp, vload(dsp.rec120_perm))
            vstore(rec120_tmp, vload(dsp.rec120_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec120[i] = ((dsp.const523) * ((((dsp.const527) * (rec121[i])) + ((dsp.const528) * (rec121[(i) - (S32(1))]))) + ((dsp.const527) * (rec121[(i) - (S32(2))])))) - ((dsp.const529) * (((dsp.const530) * (rec120[(i) - (S32(2))])) + ((dsp.const531) * (rec120[(i) - (S32(1))]))))
            vstore(dsp.rec120_perm, vload(rec120_tmp, vsize))
            vstore(dsp.rec120_perm, vload(rec120_tmp, vsize + wsize), wsize)
            vstore(rec119_tmp, vload(dsp.rec119_perm))
            vstore(rec119_tmp, vload(dsp.rec119_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec119[i] = ((dsp.const529) * ((((dsp.const532) * (rec120[i])) + ((dsp.const533) * (rec120[(i) - (S32(1))]))) + ((dsp.const532) * (rec120[(i) - (S32(2))])))) - ((dsp.const534) * (((dsp.const535) * (rec119[(i) - (S32(2))])) + ((dsp.const536) * (rec119[(i) - (S32(1))]))))
            vstore(dsp.rec119_perm, vload(rec119_tmp, vsize))
            vstore(dsp.rec119_perm, vload(rec119_tmp, vsize + wsize), wsize)
            vstore(rec118_tmp, vload(dsp.rec118_perm))
            vstore(rec118_tmp, vload(dsp.rec118_perm, wsize), wsize)
            comptime for i in range(vsize):
                rec118[i] = ((slow34) * (rec118[(i) - (S32(1))])) + ((slow35) * (abs((dsp.const534) * ((((dsp.const537) * (rec119[i])) + ((dsp.const538) * (rec119[(i) - (S32(1))]))) + ((dsp.const537) * (rec119[(i) - (S32(2))]))))))
            vstore(dsp.rec118_perm, vload(rec118_tmp, vsize))
            vstore(dsp.rec118_perm, vload(rec118_tmp, vsize + wsize), wsize)
            comptime for i in range(S32(0), vsize):
                dsp.vbargraph0 = FaustFloat((slow36) + ((2e+01) * (log10(rec23[i]))))
                dsp.vbargraph1 = FaustFloat((slow36) + ((2e+01) * (log10(rec27[i]))))
                dsp.vbargraph2 = FaustFloat((slow36) + ((2e+01) * (log10(rec34[i]))))
                dsp.vbargraph3 = FaustFloat((slow36) + ((2e+01) * (log10(rec41[i]))))
                dsp.vbargraph4 = FaustFloat((slow36) + ((2e+01) * (log10(rec48[i]))))
                dsp.vbargraph5 = FaustFloat((slow36) + ((2e+01) * (log10(rec55[i]))))
                dsp.vbargraph6 = FaustFloat((slow36) + ((2e+01) * (log10(rec62[i]))))
                dsp.vbargraph7 = FaustFloat((slow36) + ((2e+01) * (log10(rec69[i]))))
                dsp.vbargraph8 = FaustFloat((slow36) + ((2e+01) * (log10(rec76[i]))))
                dsp.vbargraph9 = FaustFloat((slow36) + ((2e+01) * (log10(rec83[i]))))
                dsp.vbargraph10 = FaustFloat((slow36) + ((2e+01) * (log10(rec90[i]))))
                dsp.vbargraph11 = FaustFloat((slow36) + ((2e+01) * (log10(rec97[i]))))
                dsp.vbargraph12 = FaustFloat((slow36) + ((2e+01) * (log10(rec104[i]))))
                dsp.vbargraph13 = FaustFloat((slow36) + ((2e+01) * (log10(rec111[i]))))
                dsp.vbargraph14 = FaustFloat((slow36) + ((2e+01) * (log10(rec118[i]))))
            vstore(zec52, vload(zec38))
            vstore(zec52, vload(zec38, wsize), wsize)
            lo = (vload(zec52)).cast[dfaust]()
            hi = (vload(zec52, wsize)).cast[dfaust]()
            vstore(output0, lo.join(hi))
            lo = (vload(zec52)).cast[dfaust]()
            hi = (vload(zec52, wsize)).cast[dfaust]()
            vstore(output1, lo.join(hi))
            vindex += vsize

# ==============================================================================
# Faust generated DSP code end.
# ==============================================================================
# Second section of architecture provided code start.
# Defines the main entry point of the application, initializes the dsp object,
# initializes the user interface and calls the dsp runner.
# ==============================================================================

def main() raises -> None:
    nbsamples = S32(60_000)
    dsp = alloc[mydsp](1)
    dsp[] = mydsp()
    ctrl_gui = ControlGui()
    dsp[].init(SAMP_RATE)
    dsp[].build_user_interface(ctrl_gui)
    print_header(dsp[], nbsamples)
    run_dsp(dsp, ctrl_gui, nbsamples//4)
    dsp.free()

# ==============================================================================
# Second section of architecture provided code end.
# ==============================================================================
