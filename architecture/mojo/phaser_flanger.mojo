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
# name: "phaser_flanger"
# Compilation options: 
#   
#   -a /Users/manuelfarzini/Personal/dev/repo/faust/architecture/mojo/impulse.mojo 
#   -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double 
#   -ftz 0 -vec -lv 0 -vs 4 -dfs
# ==============================================================================

comptime dreal = f64
comptime wreal = simd_width_of[dreal]()
comptime Real = Scalar[dreal]
comptime RVec = SIMD[dreal, simd_width_of[dreal]()]

@fieldwise_init
struct mydsp(FaustDsp):
    var null_val: FaustFloat
    var vslider0: FaustFloat
    var rec0_perm: Arr[F64, 4]
    var vslider1: FaustFloat
    var sample_rate: S32
    var const0: F64
    var const1: F64
    var vslider2: FaustFloat
    var rec2_perm: Arr[F64, 4]
    var rec1_perm: Arr[F64, 4]
    var vslider3: FaustFloat
    var rec3_perm: Arr[F64, 4]
    var vslider4: FaustFloat
    var rec4_perm: Arr[F64, 4]
    var i_rec5_perm: Arr[S32, 4]
    var rec6_perm: Arr[F64, 4]
    var const2: F64
    var hslider0: FaustFloat
    var rec7_perm: Arr[F64, 4]
    var i_vec0_perm: Arr[S32, 4]
    var rec8_perm: Arr[F64, 4]
    var hslider1: FaustFloat
    var hslider2: FaustFloat
    var hbargraph0: FaustFloat
    var checkbox0: FaustFloat
    var checkbox1: FaustFloat
    var checkbox2: FaustFloat
    var entry0: FaustFloat
    var const3: F64
    var yec0_perm: Arr[F64, 4]
    var const4: F64
    var yec1_perm: Arr[F64, 4]
    var yec2_perm: Arr[F64, 4]
    var const5: F64
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
    var yec18: Arr[F64, 4096]
    var yec18_idx: S32
    var yec18_idx_save: S32
    var hslider3: FaustFloat
    var hslider4: FaustFloat
    var rec9_perm: Arr[F64, 4]
    var hslider5: FaustFloat
    var rec15_perm: Arr[F64, 4]
    var rec16_perm: Arr[F64, 4]
    var hslider6: FaustFloat
    var checkbox4: FaustFloat
    var checkbox5: FaustFloat
    var hslider7: FaustFloat
    var hslider8: FaustFloat
    var const6: F64
    var hslider9: FaustFloat
    var hslider10: FaustFloat
    var hslider11: FaustFloat
    var hslider12: FaustFloat
    var rec14_perm: Arr[F64, 4]
    var rec13_perm: Arr[F64, 4]
    var rec12_perm: Arr[F64, 4]
    var rec11_perm: Arr[F64, 4]
    var rec10_perm: Arr[F64, 4]
    var yec19: Arr[F64, 4096]
    var yec19_idx: S32
    var yec19_idx_save: S32
    var rec17_perm: Arr[F64, 4]
    var rec22_perm: Arr[F64, 4]
    var rec21_perm: Arr[F64, 4]
    var rec20_perm: Arr[F64, 4]
    var rec19_perm: Arr[F64, 4]
    var rec18_perm: Arr[F64, 4]
    var checkbox6: FaustFloat
    var hslider13: FaustFloat
    var checkbox7: FaustFloat
    var const7: F64
    var const8: F64
    var const9: F64
    var const10: F64
    var const11: F64
    var const12: F64
    var const13: F64
    var rec26_perm: Arr[F64, 4]
    var const14: F64
    var const15: F64
    var const16: F64
    var const17: F64
    var const18: F64
    var const19: F64
    var rec25_perm: Arr[F64, 4]
    var const20: F64
    var const21: F64
    var const22: F64
    var const23: F64
    var const24: F64
    var const25: F64
    var rec24_perm: Arr[F64, 4]
    var hslider14: FaustFloat
    var const26: F64
    var const27: F64
    var const28: F64
    var const29: F64
    var rec23_perm: Arr[F64, 4]
    var const30: F64
    var const31: F64
    var const32: F64
    var rec33_perm: Arr[F64, 4]
    var const33: F64
    var const34: F64
    var const35: F64
    var const36: F64
    var const37: F64
    var const38: F64
    var rec32_perm: Arr[F64, 4]
    var const39: F64
    var const40: F64
    var const41: F64
    var const42: F64
    var const43: F64
    var rec31_perm: Arr[F64, 4]
    var const44: F64
    var const45: F64
    var const46: F64
    var const47: F64
    var const48: F64
    var const49: F64
    var const50: F64
    var const51: F64
    var const52: F64
    var rec30_perm: Arr[F64, 4]
    var const53: F64
    var const54: F64
    var const55: F64
    var const56: F64
    var const57: F64
    var const58: F64
    var rec29_perm: Arr[F64, 4]
    var const59: F64
    var const60: F64
    var const61: F64
    var const62: F64
    var const63: F64
    var const64: F64
    var rec28_perm: Arr[F64, 4]
    var const65: F64
    var const66: F64
    var const67: F64
    var rec27_perm: Arr[F64, 4]
    var const68: F64
    var const69: F64
    var const70: F64
    var rec40_perm: Arr[F64, 4]
    var const71: F64
    var const72: F64
    var const73: F64
    var const74: F64
    var const75: F64
    var const76: F64
    var rec39_perm: Arr[F64, 4]
    var const77: F64
    var const78: F64
    var const79: F64
    var const80: F64
    var const81: F64
    var rec38_perm: Arr[F64, 4]
    var const82: F64
    var const83: F64
    var const84: F64
    var const85: F64
    var const86: F64
    var const87: F64
    var const88: F64
    var const89: F64
    var const90: F64
    var rec37_perm: Arr[F64, 4]
    var const91: F64
    var const92: F64
    var const93: F64
    var const94: F64
    var const95: F64
    var const96: F64
    var rec36_perm: Arr[F64, 4]
    var const97: F64
    var const98: F64
    var const99: F64
    var const100: F64
    var const101: F64
    var const102: F64
    var rec35_perm: Arr[F64, 4]
    var const103: F64
    var const104: F64
    var const105: F64
    var rec34_perm: Arr[F64, 4]
    var const106: F64
    var const107: F64
    var const108: F64
    var rec47_perm: Arr[F64, 4]
    var const109: F64
    var const110: F64
    var const111: F64
    var const112: F64
    var const113: F64
    var const114: F64
    var rec46_perm: Arr[F64, 4]
    var const115: F64
    var const116: F64
    var const117: F64
    var const118: F64
    var const119: F64
    var rec45_perm: Arr[F64, 4]
    var const120: F64
    var const121: F64
    var const122: F64
    var const123: F64
    var const124: F64
    var const125: F64
    var const126: F64
    var const127: F64
    var const128: F64
    var rec44_perm: Arr[F64, 4]
    var const129: F64
    var const130: F64
    var const131: F64
    var const132: F64
    var const133: F64
    var const134: F64
    var rec43_perm: Arr[F64, 4]
    var const135: F64
    var const136: F64
    var const137: F64
    var const138: F64
    var const139: F64
    var const140: F64
    var rec42_perm: Arr[F64, 4]
    var const141: F64
    var const142: F64
    var const143: F64
    var rec41_perm: Arr[F64, 4]
    var const144: F64
    var const145: F64
    var const146: F64
    var rec54_perm: Arr[F64, 4]
    var const147: F64
    var const148: F64
    var const149: F64
    var const150: F64
    var const151: F64
    var const152: F64
    var rec53_perm: Arr[F64, 4]
    var const153: F64
    var const154: F64
    var const155: F64
    var const156: F64
    var const157: F64
    var rec52_perm: Arr[F64, 4]
    var const158: F64
    var const159: F64
    var const160: F64
    var const161: F64
    var const162: F64
    var const163: F64
    var const164: F64
    var const165: F64
    var const166: F64
    var rec51_perm: Arr[F64, 4]
    var const167: F64
    var const168: F64
    var const169: F64
    var const170: F64
    var const171: F64
    var const172: F64
    var rec50_perm: Arr[F64, 4]
    var const173: F64
    var const174: F64
    var const175: F64
    var const176: F64
    var const177: F64
    var const178: F64
    var rec49_perm: Arr[F64, 4]
    var const179: F64
    var const180: F64
    var const181: F64
    var rec48_perm: Arr[F64, 4]
    var const182: F64
    var const183: F64
    var const184: F64
    var rec61_perm: Arr[F64, 4]
    var const185: F64
    var const186: F64
    var const187: F64
    var const188: F64
    var const189: F64
    var const190: F64
    var rec60_perm: Arr[F64, 4]
    var const191: F64
    var const192: F64
    var const193: F64
    var const194: F64
    var const195: F64
    var rec59_perm: Arr[F64, 4]
    var const196: F64
    var const197: F64
    var const198: F64
    var const199: F64
    var const200: F64
    var const201: F64
    var const202: F64
    var const203: F64
    var const204: F64
    var rec58_perm: Arr[F64, 4]
    var const205: F64
    var const206: F64
    var const207: F64
    var const208: F64
    var const209: F64
    var const210: F64
    var rec57_perm: Arr[F64, 4]
    var const211: F64
    var const212: F64
    var const213: F64
    var const214: F64
    var const215: F64
    var const216: F64
    var rec56_perm: Arr[F64, 4]
    var const217: F64
    var const218: F64
    var const219: F64
    var rec55_perm: Arr[F64, 4]
    var const220: F64
    var const221: F64
    var const222: F64
    var rec68_perm: Arr[F64, 4]
    var const223: F64
    var const224: F64
    var const225: F64
    var const226: F64
    var const227: F64
    var const228: F64
    var rec67_perm: Arr[F64, 4]
    var const229: F64
    var const230: F64
    var const231: F64
    var const232: F64
    var const233: F64
    var rec66_perm: Arr[F64, 4]
    var const234: F64
    var const235: F64
    var const236: F64
    var const237: F64
    var const238: F64
    var const239: F64
    var const240: F64
    var const241: F64
    var const242: F64
    var rec65_perm: Arr[F64, 4]
    var const243: F64
    var const244: F64
    var const245: F64
    var const246: F64
    var const247: F64
    var const248: F64
    var rec64_perm: Arr[F64, 4]
    var const249: F64
    var const250: F64
    var const251: F64
    var const252: F64
    var const253: F64
    var const254: F64
    var rec63_perm: Arr[F64, 4]
    var const255: F64
    var const256: F64
    var const257: F64
    var rec62_perm: Arr[F64, 4]
    var const258: F64
    var const259: F64
    var const260: F64
    var rec75_perm: Arr[F64, 4]
    var const261: F64
    var const262: F64
    var const263: F64
    var const264: F64
    var const265: F64
    var const266: F64
    var rec74_perm: Arr[F64, 4]
    var const267: F64
    var const268: F64
    var const269: F64
    var const270: F64
    var const271: F64
    var rec73_perm: Arr[F64, 4]
    var const272: F64
    var const273: F64
    var const274: F64
    var const275: F64
    var const276: F64
    var const277: F64
    var const278: F64
    var const279: F64
    var const280: F64
    var rec72_perm: Arr[F64, 4]
    var const281: F64
    var const282: F64
    var const283: F64
    var const284: F64
    var const285: F64
    var const286: F64
    var rec71_perm: Arr[F64, 4]
    var const287: F64
    var const288: F64
    var const289: F64
    var const290: F64
    var const291: F64
    var const292: F64
    var rec70_perm: Arr[F64, 4]
    var const293: F64
    var const294: F64
    var const295: F64
    var rec69_perm: Arr[F64, 4]
    var const296: F64
    var const297: F64
    var const298: F64
    var rec82_perm: Arr[F64, 4]
    var const299: F64
    var const300: F64
    var const301: F64
    var const302: F64
    var const303: F64
    var const304: F64
    var rec81_perm: Arr[F64, 4]
    var const305: F64
    var const306: F64
    var const307: F64
    var const308: F64
    var const309: F64
    var rec80_perm: Arr[F64, 4]
    var const310: F64
    var const311: F64
    var const312: F64
    var const313: F64
    var const314: F64
    var const315: F64
    var const316: F64
    var const317: F64
    var const318: F64
    var rec79_perm: Arr[F64, 4]
    var const319: F64
    var const320: F64
    var const321: F64
    var const322: F64
    var const323: F64
    var const324: F64
    var rec78_perm: Arr[F64, 4]
    var const325: F64
    var const326: F64
    var const327: F64
    var const328: F64
    var const329: F64
    var const330: F64
    var rec77_perm: Arr[F64, 4]
    var const331: F64
    var const332: F64
    var const333: F64
    var rec76_perm: Arr[F64, 4]
    var const334: F64
    var const335: F64
    var const336: F64
    var rec89_perm: Arr[F64, 4]
    var const337: F64
    var const338: F64
    var const339: F64
    var const340: F64
    var const341: F64
    var const342: F64
    var rec88_perm: Arr[F64, 4]
    var const343: F64
    var const344: F64
    var const345: F64
    var const346: F64
    var const347: F64
    var rec87_perm: Arr[F64, 4]
    var const348: F64
    var const349: F64
    var const350: F64
    var const351: F64
    var const352: F64
    var const353: F64
    var const354: F64
    var const355: F64
    var const356: F64
    var rec86_perm: Arr[F64, 4]
    var const357: F64
    var const358: F64
    var const359: F64
    var const360: F64
    var const361: F64
    var const362: F64
    var rec85_perm: Arr[F64, 4]
    var const363: F64
    var const364: F64
    var const365: F64
    var const366: F64
    var const367: F64
    var const368: F64
    var rec84_perm: Arr[F64, 4]
    var const369: F64
    var const370: F64
    var const371: F64
    var rec83_perm: Arr[F64, 4]
    var const372: F64
    var const373: F64
    var const374: F64
    var rec96_perm: Arr[F64, 4]
    var const375: F64
    var const376: F64
    var const377: F64
    var const378: F64
    var const379: F64
    var const380: F64
    var rec95_perm: Arr[F64, 4]
    var const381: F64
    var const382: F64
    var const383: F64
    var const384: F64
    var const385: F64
    var rec94_perm: Arr[F64, 4]
    var const386: F64
    var const387: F64
    var const388: F64
    var const389: F64
    var const390: F64
    var const391: F64
    var const392: F64
    var const393: F64
    var const394: F64
    var rec93_perm: Arr[F64, 4]
    var const395: F64
    var const396: F64
    var const397: F64
    var const398: F64
    var const399: F64
    var const400: F64
    var rec92_perm: Arr[F64, 4]
    var const401: F64
    var const402: F64
    var const403: F64
    var const404: F64
    var const405: F64
    var const406: F64
    var rec91_perm: Arr[F64, 4]
    var const407: F64
    var const408: F64
    var const409: F64
    var rec90_perm: Arr[F64, 4]
    var const410: F64
    var const411: F64
    var const412: F64
    var rec103_perm: Arr[F64, 4]
    var const413: F64
    var const414: F64
    var const415: F64
    var const416: F64
    var const417: F64
    var const418: F64
    var rec102_perm: Arr[F64, 4]
    var const419: F64
    var const420: F64
    var const421: F64
    var const422: F64
    var const423: F64
    var rec101_perm: Arr[F64, 4]
    var const424: F64
    var const425: F64
    var const426: F64
    var const427: F64
    var const428: F64
    var const429: F64
    var const430: F64
    var const431: F64
    var const432: F64
    var rec100_perm: Arr[F64, 4]
    var const433: F64
    var const434: F64
    var const435: F64
    var const436: F64
    var const437: F64
    var const438: F64
    var rec99_perm: Arr[F64, 4]
    var const439: F64
    var const440: F64
    var const441: F64
    var const442: F64
    var const443: F64
    var const444: F64
    var rec98_perm: Arr[F64, 4]
    var const445: F64
    var const446: F64
    var const447: F64
    var rec97_perm: Arr[F64, 4]
    var const448: F64
    var const449: F64
    var const450: F64
    var rec110_perm: Arr[F64, 4]
    var const451: F64
    var const452: F64
    var const453: F64
    var const454: F64
    var const455: F64
    var const456: F64
    var rec109_perm: Arr[F64, 4]
    var const457: F64
    var const458: F64
    var const459: F64
    var const460: F64
    var const461: F64
    var rec108_perm: Arr[F64, 4]
    var const462: F64
    var const463: F64
    var const464: F64
    var const465: F64
    var const466: F64
    var const467: F64
    var const468: F64
    var const469: F64
    var const470: F64
    var rec107_perm: Arr[F64, 4]
    var const471: F64
    var const472: F64
    var const473: F64
    var const474: F64
    var const475: F64
    var const476: F64
    var rec106_perm: Arr[F64, 4]
    var const477: F64
    var const478: F64
    var const479: F64
    var const480: F64
    var const481: F64
    var const482: F64
    var rec105_perm: Arr[F64, 4]
    var const483: F64
    var const484: F64
    var const485: F64
    var rec104_perm: Arr[F64, 4]
    var const486: F64
    var const487: F64
    var const488: F64
    var rec117_perm: Arr[F64, 4]
    var const489: F64
    var const490: F64
    var const491: F64
    var const492: F64
    var const493: F64
    var const494: F64
    var rec116_perm: Arr[F64, 4]
    var const495: F64
    var const496: F64
    var const497: F64
    var const498: F64
    var const499: F64
    var rec115_perm: Arr[F64, 4]
    var const500: F64
    var const501: F64
    var const502: F64
    var const503: F64
    var const504: F64
    var const505: F64
    var const506: F64
    var const507: F64
    var const508: F64
    var rec114_perm: Arr[F64, 4]
    var const509: F64
    var const510: F64
    var const511: F64
    var const512: F64
    var const513: F64
    var const514: F64
    var rec113_perm: Arr[F64, 4]
    var const515: F64
    var const516: F64
    var const517: F64
    var const518: F64
    var const519: F64
    var const520: F64
    var rec112_perm: Arr[F64, 4]
    var const521: F64
    var const522: F64
    var const523: F64
    var rec111_perm: Arr[F64, 4]
    var const524: F64
    var const525: F64
    var const526: F64
    var rec121_perm: Arr[F64, 4]
    var const527: F64
    var const528: F64
    var const529: F64
    var const530: F64
    var const531: F64
    var const532: F64
    var rec120_perm: Arr[F64, 4]
    var const533: F64
    var const534: F64
    var const535: F64
    var const536: F64
    var const537: F64
    var rec119_perm: Arr[F64, 4]
    var const538: F64
    var const539: F64
    var rec118_perm: Arr[F64, 4]
    var hslider15: FaustFloat
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
        dsp.rec0_perm = Arr[F64, 4](fill=0.0)
        dsp.vslider1 = 0.0
        dsp.sample_rate = 0
        dsp.const0 = 0.0
        dsp.const1 = 0.0
        dsp.vslider2 = 0.0
        dsp.rec2_perm = Arr[F64, 4](fill=0.0)
        dsp.rec1_perm = Arr[F64, 4](fill=0.0)
        dsp.vslider3 = 0.0
        dsp.rec3_perm = Arr[F64, 4](fill=0.0)
        dsp.vslider4 = 0.0
        dsp.rec4_perm = Arr[F64, 4](fill=0.0)
        dsp.i_rec5_perm = Arr[S32, 4](fill=0)
        dsp.rec6_perm = Arr[F64, 4](fill=0.0)
        dsp.const2 = 0.0
        dsp.hslider0 = 0.0
        dsp.rec7_perm = Arr[F64, 4](fill=0.0)
        dsp.i_vec0_perm = Arr[S32, 4](fill=0)
        dsp.rec8_perm = Arr[F64, 4](fill=0.0)
        dsp.hslider1 = 0.0
        dsp.hslider2 = 0.0
        dsp.hbargraph0 = 0.0
        dsp.checkbox0 = 0.0
        dsp.checkbox1 = 0.0
        dsp.checkbox2 = 0.0
        dsp.entry0 = 0.0
        dsp.const3 = 0.0
        dsp.yec0_perm = Arr[F64, 4](fill=0.0)
        dsp.const4 = 0.0
        dsp.yec1_perm = Arr[F64, 4](fill=0.0)
        dsp.yec2_perm = Arr[F64, 4](fill=0.0)
        dsp.const5 = 0.0
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
        dsp.yec18 = Arr[F64, 4096](fill=0.0)
        dsp.yec18_idx = 0
        dsp.yec18_idx_save = 0
        dsp.hslider3 = 0.0
        dsp.hslider4 = 0.0
        dsp.rec9_perm = Arr[F64, 4](fill=0.0)
        dsp.hslider5 = 0.0
        dsp.rec15_perm = Arr[F64, 4](fill=0.0)
        dsp.rec16_perm = Arr[F64, 4](fill=0.0)
        dsp.hslider6 = 0.0
        dsp.checkbox4 = 0.0
        dsp.checkbox5 = 0.0
        dsp.hslider7 = 0.0
        dsp.hslider8 = 0.0
        dsp.const6 = 0.0
        dsp.hslider9 = 0.0
        dsp.hslider10 = 0.0
        dsp.hslider11 = 0.0
        dsp.hslider12 = 0.0
        dsp.rec14_perm = Arr[F64, 4](fill=0.0)
        dsp.rec13_perm = Arr[F64, 4](fill=0.0)
        dsp.rec12_perm = Arr[F64, 4](fill=0.0)
        dsp.rec11_perm = Arr[F64, 4](fill=0.0)
        dsp.rec10_perm = Arr[F64, 4](fill=0.0)
        dsp.yec19 = Arr[F64, 4096](fill=0.0)
        dsp.yec19_idx = 0
        dsp.yec19_idx_save = 0
        dsp.rec17_perm = Arr[F64, 4](fill=0.0)
        dsp.rec22_perm = Arr[F64, 4](fill=0.0)
        dsp.rec21_perm = Arr[F64, 4](fill=0.0)
        dsp.rec20_perm = Arr[F64, 4](fill=0.0)
        dsp.rec19_perm = Arr[F64, 4](fill=0.0)
        dsp.rec18_perm = Arr[F64, 4](fill=0.0)
        dsp.checkbox6 = 0.0
        dsp.hslider13 = 0.0
        dsp.checkbox7 = 0.0
        dsp.const7 = 0.0
        dsp.const8 = 0.0
        dsp.const9 = 0.0
        dsp.const10 = 0.0
        dsp.const11 = 0.0
        dsp.const12 = 0.0
        dsp.const13 = 0.0
        dsp.rec26_perm = Arr[F64, 4](fill=0.0)
        dsp.const14 = 0.0
        dsp.const15 = 0.0
        dsp.const16 = 0.0
        dsp.const17 = 0.0
        dsp.const18 = 0.0
        dsp.const19 = 0.0
        dsp.rec25_perm = Arr[F64, 4](fill=0.0)
        dsp.const20 = 0.0
        dsp.const21 = 0.0
        dsp.const22 = 0.0
        dsp.const23 = 0.0
        dsp.const24 = 0.0
        dsp.const25 = 0.0
        dsp.rec24_perm = Arr[F64, 4](fill=0.0)
        dsp.hslider14 = 0.0
        dsp.const26 = 0.0
        dsp.const27 = 0.0
        dsp.const28 = 0.0
        dsp.const29 = 0.0
        dsp.rec23_perm = Arr[F64, 4](fill=0.0)
        dsp.const30 = 0.0
        dsp.const31 = 0.0
        dsp.const32 = 0.0
        dsp.rec33_perm = Arr[F64, 4](fill=0.0)
        dsp.const33 = 0.0
        dsp.const34 = 0.0
        dsp.const35 = 0.0
        dsp.const36 = 0.0
        dsp.const37 = 0.0
        dsp.const38 = 0.0
        dsp.rec32_perm = Arr[F64, 4](fill=0.0)
        dsp.const39 = 0.0
        dsp.const40 = 0.0
        dsp.const41 = 0.0
        dsp.const42 = 0.0
        dsp.const43 = 0.0
        dsp.rec31_perm = Arr[F64, 4](fill=0.0)
        dsp.const44 = 0.0
        dsp.const45 = 0.0
        dsp.const46 = 0.0
        dsp.const47 = 0.0
        dsp.const48 = 0.0
        dsp.const49 = 0.0
        dsp.const50 = 0.0
        dsp.const51 = 0.0
        dsp.const52 = 0.0
        dsp.rec30_perm = Arr[F64, 4](fill=0.0)
        dsp.const53 = 0.0
        dsp.const54 = 0.0
        dsp.const55 = 0.0
        dsp.const56 = 0.0
        dsp.const57 = 0.0
        dsp.const58 = 0.0
        dsp.rec29_perm = Arr[F64, 4](fill=0.0)
        dsp.const59 = 0.0
        dsp.const60 = 0.0
        dsp.const61 = 0.0
        dsp.const62 = 0.0
        dsp.const63 = 0.0
        dsp.const64 = 0.0
        dsp.rec28_perm = Arr[F64, 4](fill=0.0)
        dsp.const65 = 0.0
        dsp.const66 = 0.0
        dsp.const67 = 0.0
        dsp.rec27_perm = Arr[F64, 4](fill=0.0)
        dsp.const68 = 0.0
        dsp.const69 = 0.0
        dsp.const70 = 0.0
        dsp.rec40_perm = Arr[F64, 4](fill=0.0)
        dsp.const71 = 0.0
        dsp.const72 = 0.0
        dsp.const73 = 0.0
        dsp.const74 = 0.0
        dsp.const75 = 0.0
        dsp.const76 = 0.0
        dsp.rec39_perm = Arr[F64, 4](fill=0.0)
        dsp.const77 = 0.0
        dsp.const78 = 0.0
        dsp.const79 = 0.0
        dsp.const80 = 0.0
        dsp.const81 = 0.0
        dsp.rec38_perm = Arr[F64, 4](fill=0.0)
        dsp.const82 = 0.0
        dsp.const83 = 0.0
        dsp.const84 = 0.0
        dsp.const85 = 0.0
        dsp.const86 = 0.0
        dsp.const87 = 0.0
        dsp.const88 = 0.0
        dsp.const89 = 0.0
        dsp.const90 = 0.0
        dsp.rec37_perm = Arr[F64, 4](fill=0.0)
        dsp.const91 = 0.0
        dsp.const92 = 0.0
        dsp.const93 = 0.0
        dsp.const94 = 0.0
        dsp.const95 = 0.0
        dsp.const96 = 0.0
        dsp.rec36_perm = Arr[F64, 4](fill=0.0)
        dsp.const97 = 0.0
        dsp.const98 = 0.0
        dsp.const99 = 0.0
        dsp.const100 = 0.0
        dsp.const101 = 0.0
        dsp.const102 = 0.0
        dsp.rec35_perm = Arr[F64, 4](fill=0.0)
        dsp.const103 = 0.0
        dsp.const104 = 0.0
        dsp.const105 = 0.0
        dsp.rec34_perm = Arr[F64, 4](fill=0.0)
        dsp.const106 = 0.0
        dsp.const107 = 0.0
        dsp.const108 = 0.0
        dsp.rec47_perm = Arr[F64, 4](fill=0.0)
        dsp.const109 = 0.0
        dsp.const110 = 0.0
        dsp.const111 = 0.0
        dsp.const112 = 0.0
        dsp.const113 = 0.0
        dsp.const114 = 0.0
        dsp.rec46_perm = Arr[F64, 4](fill=0.0)
        dsp.const115 = 0.0
        dsp.const116 = 0.0
        dsp.const117 = 0.0
        dsp.const118 = 0.0
        dsp.const119 = 0.0
        dsp.rec45_perm = Arr[F64, 4](fill=0.0)
        dsp.const120 = 0.0
        dsp.const121 = 0.0
        dsp.const122 = 0.0
        dsp.const123 = 0.0
        dsp.const124 = 0.0
        dsp.const125 = 0.0
        dsp.const126 = 0.0
        dsp.const127 = 0.0
        dsp.const128 = 0.0
        dsp.rec44_perm = Arr[F64, 4](fill=0.0)
        dsp.const129 = 0.0
        dsp.const130 = 0.0
        dsp.const131 = 0.0
        dsp.const132 = 0.0
        dsp.const133 = 0.0
        dsp.const134 = 0.0
        dsp.rec43_perm = Arr[F64, 4](fill=0.0)
        dsp.const135 = 0.0
        dsp.const136 = 0.0
        dsp.const137 = 0.0
        dsp.const138 = 0.0
        dsp.const139 = 0.0
        dsp.const140 = 0.0
        dsp.rec42_perm = Arr[F64, 4](fill=0.0)
        dsp.const141 = 0.0
        dsp.const142 = 0.0
        dsp.const143 = 0.0
        dsp.rec41_perm = Arr[F64, 4](fill=0.0)
        dsp.const144 = 0.0
        dsp.const145 = 0.0
        dsp.const146 = 0.0
        dsp.rec54_perm = Arr[F64, 4](fill=0.0)
        dsp.const147 = 0.0
        dsp.const148 = 0.0
        dsp.const149 = 0.0
        dsp.const150 = 0.0
        dsp.const151 = 0.0
        dsp.const152 = 0.0
        dsp.rec53_perm = Arr[F64, 4](fill=0.0)
        dsp.const153 = 0.0
        dsp.const154 = 0.0
        dsp.const155 = 0.0
        dsp.const156 = 0.0
        dsp.const157 = 0.0
        dsp.rec52_perm = Arr[F64, 4](fill=0.0)
        dsp.const158 = 0.0
        dsp.const159 = 0.0
        dsp.const160 = 0.0
        dsp.const161 = 0.0
        dsp.const162 = 0.0
        dsp.const163 = 0.0
        dsp.const164 = 0.0
        dsp.const165 = 0.0
        dsp.const166 = 0.0
        dsp.rec51_perm = Arr[F64, 4](fill=0.0)
        dsp.const167 = 0.0
        dsp.const168 = 0.0
        dsp.const169 = 0.0
        dsp.const170 = 0.0
        dsp.const171 = 0.0
        dsp.const172 = 0.0
        dsp.rec50_perm = Arr[F64, 4](fill=0.0)
        dsp.const173 = 0.0
        dsp.const174 = 0.0
        dsp.const175 = 0.0
        dsp.const176 = 0.0
        dsp.const177 = 0.0
        dsp.const178 = 0.0
        dsp.rec49_perm = Arr[F64, 4](fill=0.0)
        dsp.const179 = 0.0
        dsp.const180 = 0.0
        dsp.const181 = 0.0
        dsp.rec48_perm = Arr[F64, 4](fill=0.0)
        dsp.const182 = 0.0
        dsp.const183 = 0.0
        dsp.const184 = 0.0
        dsp.rec61_perm = Arr[F64, 4](fill=0.0)
        dsp.const185 = 0.0
        dsp.const186 = 0.0
        dsp.const187 = 0.0
        dsp.const188 = 0.0
        dsp.const189 = 0.0
        dsp.const190 = 0.0
        dsp.rec60_perm = Arr[F64, 4](fill=0.0)
        dsp.const191 = 0.0
        dsp.const192 = 0.0
        dsp.const193 = 0.0
        dsp.const194 = 0.0
        dsp.const195 = 0.0
        dsp.rec59_perm = Arr[F64, 4](fill=0.0)
        dsp.const196 = 0.0
        dsp.const197 = 0.0
        dsp.const198 = 0.0
        dsp.const199 = 0.0
        dsp.const200 = 0.0
        dsp.const201 = 0.0
        dsp.const202 = 0.0
        dsp.const203 = 0.0
        dsp.const204 = 0.0
        dsp.rec58_perm = Arr[F64, 4](fill=0.0)
        dsp.const205 = 0.0
        dsp.const206 = 0.0
        dsp.const207 = 0.0
        dsp.const208 = 0.0
        dsp.const209 = 0.0
        dsp.const210 = 0.0
        dsp.rec57_perm = Arr[F64, 4](fill=0.0)
        dsp.const211 = 0.0
        dsp.const212 = 0.0
        dsp.const213 = 0.0
        dsp.const214 = 0.0
        dsp.const215 = 0.0
        dsp.const216 = 0.0
        dsp.rec56_perm = Arr[F64, 4](fill=0.0)
        dsp.const217 = 0.0
        dsp.const218 = 0.0
        dsp.const219 = 0.0
        dsp.rec55_perm = Arr[F64, 4](fill=0.0)
        dsp.const220 = 0.0
        dsp.const221 = 0.0
        dsp.const222 = 0.0
        dsp.rec68_perm = Arr[F64, 4](fill=0.0)
        dsp.const223 = 0.0
        dsp.const224 = 0.0
        dsp.const225 = 0.0
        dsp.const226 = 0.0
        dsp.const227 = 0.0
        dsp.const228 = 0.0
        dsp.rec67_perm = Arr[F64, 4](fill=0.0)
        dsp.const229 = 0.0
        dsp.const230 = 0.0
        dsp.const231 = 0.0
        dsp.const232 = 0.0
        dsp.const233 = 0.0
        dsp.rec66_perm = Arr[F64, 4](fill=0.0)
        dsp.const234 = 0.0
        dsp.const235 = 0.0
        dsp.const236 = 0.0
        dsp.const237 = 0.0
        dsp.const238 = 0.0
        dsp.const239 = 0.0
        dsp.const240 = 0.0
        dsp.const241 = 0.0
        dsp.const242 = 0.0
        dsp.rec65_perm = Arr[F64, 4](fill=0.0)
        dsp.const243 = 0.0
        dsp.const244 = 0.0
        dsp.const245 = 0.0
        dsp.const246 = 0.0
        dsp.const247 = 0.0
        dsp.const248 = 0.0
        dsp.rec64_perm = Arr[F64, 4](fill=0.0)
        dsp.const249 = 0.0
        dsp.const250 = 0.0
        dsp.const251 = 0.0
        dsp.const252 = 0.0
        dsp.const253 = 0.0
        dsp.const254 = 0.0
        dsp.rec63_perm = Arr[F64, 4](fill=0.0)
        dsp.const255 = 0.0
        dsp.const256 = 0.0
        dsp.const257 = 0.0
        dsp.rec62_perm = Arr[F64, 4](fill=0.0)
        dsp.const258 = 0.0
        dsp.const259 = 0.0
        dsp.const260 = 0.0
        dsp.rec75_perm = Arr[F64, 4](fill=0.0)
        dsp.const261 = 0.0
        dsp.const262 = 0.0
        dsp.const263 = 0.0
        dsp.const264 = 0.0
        dsp.const265 = 0.0
        dsp.const266 = 0.0
        dsp.rec74_perm = Arr[F64, 4](fill=0.0)
        dsp.const267 = 0.0
        dsp.const268 = 0.0
        dsp.const269 = 0.0
        dsp.const270 = 0.0
        dsp.const271 = 0.0
        dsp.rec73_perm = Arr[F64, 4](fill=0.0)
        dsp.const272 = 0.0
        dsp.const273 = 0.0
        dsp.const274 = 0.0
        dsp.const275 = 0.0
        dsp.const276 = 0.0
        dsp.const277 = 0.0
        dsp.const278 = 0.0
        dsp.const279 = 0.0
        dsp.const280 = 0.0
        dsp.rec72_perm = Arr[F64, 4](fill=0.0)
        dsp.const281 = 0.0
        dsp.const282 = 0.0
        dsp.const283 = 0.0
        dsp.const284 = 0.0
        dsp.const285 = 0.0
        dsp.const286 = 0.0
        dsp.rec71_perm = Arr[F64, 4](fill=0.0)
        dsp.const287 = 0.0
        dsp.const288 = 0.0
        dsp.const289 = 0.0
        dsp.const290 = 0.0
        dsp.const291 = 0.0
        dsp.const292 = 0.0
        dsp.rec70_perm = Arr[F64, 4](fill=0.0)
        dsp.const293 = 0.0
        dsp.const294 = 0.0
        dsp.const295 = 0.0
        dsp.rec69_perm = Arr[F64, 4](fill=0.0)
        dsp.const296 = 0.0
        dsp.const297 = 0.0
        dsp.const298 = 0.0
        dsp.rec82_perm = Arr[F64, 4](fill=0.0)
        dsp.const299 = 0.0
        dsp.const300 = 0.0
        dsp.const301 = 0.0
        dsp.const302 = 0.0
        dsp.const303 = 0.0
        dsp.const304 = 0.0
        dsp.rec81_perm = Arr[F64, 4](fill=0.0)
        dsp.const305 = 0.0
        dsp.const306 = 0.0
        dsp.const307 = 0.0
        dsp.const308 = 0.0
        dsp.const309 = 0.0
        dsp.rec80_perm = Arr[F64, 4](fill=0.0)
        dsp.const310 = 0.0
        dsp.const311 = 0.0
        dsp.const312 = 0.0
        dsp.const313 = 0.0
        dsp.const314 = 0.0
        dsp.const315 = 0.0
        dsp.const316 = 0.0
        dsp.const317 = 0.0
        dsp.const318 = 0.0
        dsp.rec79_perm = Arr[F64, 4](fill=0.0)
        dsp.const319 = 0.0
        dsp.const320 = 0.0
        dsp.const321 = 0.0
        dsp.const322 = 0.0
        dsp.const323 = 0.0
        dsp.const324 = 0.0
        dsp.rec78_perm = Arr[F64, 4](fill=0.0)
        dsp.const325 = 0.0
        dsp.const326 = 0.0
        dsp.const327 = 0.0
        dsp.const328 = 0.0
        dsp.const329 = 0.0
        dsp.const330 = 0.0
        dsp.rec77_perm = Arr[F64, 4](fill=0.0)
        dsp.const331 = 0.0
        dsp.const332 = 0.0
        dsp.const333 = 0.0
        dsp.rec76_perm = Arr[F64, 4](fill=0.0)
        dsp.const334 = 0.0
        dsp.const335 = 0.0
        dsp.const336 = 0.0
        dsp.rec89_perm = Arr[F64, 4](fill=0.0)
        dsp.const337 = 0.0
        dsp.const338 = 0.0
        dsp.const339 = 0.0
        dsp.const340 = 0.0
        dsp.const341 = 0.0
        dsp.const342 = 0.0
        dsp.rec88_perm = Arr[F64, 4](fill=0.0)
        dsp.const343 = 0.0
        dsp.const344 = 0.0
        dsp.const345 = 0.0
        dsp.const346 = 0.0
        dsp.const347 = 0.0
        dsp.rec87_perm = Arr[F64, 4](fill=0.0)
        dsp.const348 = 0.0
        dsp.const349 = 0.0
        dsp.const350 = 0.0
        dsp.const351 = 0.0
        dsp.const352 = 0.0
        dsp.const353 = 0.0
        dsp.const354 = 0.0
        dsp.const355 = 0.0
        dsp.const356 = 0.0
        dsp.rec86_perm = Arr[F64, 4](fill=0.0)
        dsp.const357 = 0.0
        dsp.const358 = 0.0
        dsp.const359 = 0.0
        dsp.const360 = 0.0
        dsp.const361 = 0.0
        dsp.const362 = 0.0
        dsp.rec85_perm = Arr[F64, 4](fill=0.0)
        dsp.const363 = 0.0
        dsp.const364 = 0.0
        dsp.const365 = 0.0
        dsp.const366 = 0.0
        dsp.const367 = 0.0
        dsp.const368 = 0.0
        dsp.rec84_perm = Arr[F64, 4](fill=0.0)
        dsp.const369 = 0.0
        dsp.const370 = 0.0
        dsp.const371 = 0.0
        dsp.rec83_perm = Arr[F64, 4](fill=0.0)
        dsp.const372 = 0.0
        dsp.const373 = 0.0
        dsp.const374 = 0.0
        dsp.rec96_perm = Arr[F64, 4](fill=0.0)
        dsp.const375 = 0.0
        dsp.const376 = 0.0
        dsp.const377 = 0.0
        dsp.const378 = 0.0
        dsp.const379 = 0.0
        dsp.const380 = 0.0
        dsp.rec95_perm = Arr[F64, 4](fill=0.0)
        dsp.const381 = 0.0
        dsp.const382 = 0.0
        dsp.const383 = 0.0
        dsp.const384 = 0.0
        dsp.const385 = 0.0
        dsp.rec94_perm = Arr[F64, 4](fill=0.0)
        dsp.const386 = 0.0
        dsp.const387 = 0.0
        dsp.const388 = 0.0
        dsp.const389 = 0.0
        dsp.const390 = 0.0
        dsp.const391 = 0.0
        dsp.const392 = 0.0
        dsp.const393 = 0.0
        dsp.const394 = 0.0
        dsp.rec93_perm = Arr[F64, 4](fill=0.0)
        dsp.const395 = 0.0
        dsp.const396 = 0.0
        dsp.const397 = 0.0
        dsp.const398 = 0.0
        dsp.const399 = 0.0
        dsp.const400 = 0.0
        dsp.rec92_perm = Arr[F64, 4](fill=0.0)
        dsp.const401 = 0.0
        dsp.const402 = 0.0
        dsp.const403 = 0.0
        dsp.const404 = 0.0
        dsp.const405 = 0.0
        dsp.const406 = 0.0
        dsp.rec91_perm = Arr[F64, 4](fill=0.0)
        dsp.const407 = 0.0
        dsp.const408 = 0.0
        dsp.const409 = 0.0
        dsp.rec90_perm = Arr[F64, 4](fill=0.0)
        dsp.const410 = 0.0
        dsp.const411 = 0.0
        dsp.const412 = 0.0
        dsp.rec103_perm = Arr[F64, 4](fill=0.0)
        dsp.const413 = 0.0
        dsp.const414 = 0.0
        dsp.const415 = 0.0
        dsp.const416 = 0.0
        dsp.const417 = 0.0
        dsp.const418 = 0.0
        dsp.rec102_perm = Arr[F64, 4](fill=0.0)
        dsp.const419 = 0.0
        dsp.const420 = 0.0
        dsp.const421 = 0.0
        dsp.const422 = 0.0
        dsp.const423 = 0.0
        dsp.rec101_perm = Arr[F64, 4](fill=0.0)
        dsp.const424 = 0.0
        dsp.const425 = 0.0
        dsp.const426 = 0.0
        dsp.const427 = 0.0
        dsp.const428 = 0.0
        dsp.const429 = 0.0
        dsp.const430 = 0.0
        dsp.const431 = 0.0
        dsp.const432 = 0.0
        dsp.rec100_perm = Arr[F64, 4](fill=0.0)
        dsp.const433 = 0.0
        dsp.const434 = 0.0
        dsp.const435 = 0.0
        dsp.const436 = 0.0
        dsp.const437 = 0.0
        dsp.const438 = 0.0
        dsp.rec99_perm = Arr[F64, 4](fill=0.0)
        dsp.const439 = 0.0
        dsp.const440 = 0.0
        dsp.const441 = 0.0
        dsp.const442 = 0.0
        dsp.const443 = 0.0
        dsp.const444 = 0.0
        dsp.rec98_perm = Arr[F64, 4](fill=0.0)
        dsp.const445 = 0.0
        dsp.const446 = 0.0
        dsp.const447 = 0.0
        dsp.rec97_perm = Arr[F64, 4](fill=0.0)
        dsp.const448 = 0.0
        dsp.const449 = 0.0
        dsp.const450 = 0.0
        dsp.rec110_perm = Arr[F64, 4](fill=0.0)
        dsp.const451 = 0.0
        dsp.const452 = 0.0
        dsp.const453 = 0.0
        dsp.const454 = 0.0
        dsp.const455 = 0.0
        dsp.const456 = 0.0
        dsp.rec109_perm = Arr[F64, 4](fill=0.0)
        dsp.const457 = 0.0
        dsp.const458 = 0.0
        dsp.const459 = 0.0
        dsp.const460 = 0.0
        dsp.const461 = 0.0
        dsp.rec108_perm = Arr[F64, 4](fill=0.0)
        dsp.const462 = 0.0
        dsp.const463 = 0.0
        dsp.const464 = 0.0
        dsp.const465 = 0.0
        dsp.const466 = 0.0
        dsp.const467 = 0.0
        dsp.const468 = 0.0
        dsp.const469 = 0.0
        dsp.const470 = 0.0
        dsp.rec107_perm = Arr[F64, 4](fill=0.0)
        dsp.const471 = 0.0
        dsp.const472 = 0.0
        dsp.const473 = 0.0
        dsp.const474 = 0.0
        dsp.const475 = 0.0
        dsp.const476 = 0.0
        dsp.rec106_perm = Arr[F64, 4](fill=0.0)
        dsp.const477 = 0.0
        dsp.const478 = 0.0
        dsp.const479 = 0.0
        dsp.const480 = 0.0
        dsp.const481 = 0.0
        dsp.const482 = 0.0
        dsp.rec105_perm = Arr[F64, 4](fill=0.0)
        dsp.const483 = 0.0
        dsp.const484 = 0.0
        dsp.const485 = 0.0
        dsp.rec104_perm = Arr[F64, 4](fill=0.0)
        dsp.const486 = 0.0
        dsp.const487 = 0.0
        dsp.const488 = 0.0
        dsp.rec117_perm = Arr[F64, 4](fill=0.0)
        dsp.const489 = 0.0
        dsp.const490 = 0.0
        dsp.const491 = 0.0
        dsp.const492 = 0.0
        dsp.const493 = 0.0
        dsp.const494 = 0.0
        dsp.rec116_perm = Arr[F64, 4](fill=0.0)
        dsp.const495 = 0.0
        dsp.const496 = 0.0
        dsp.const497 = 0.0
        dsp.const498 = 0.0
        dsp.const499 = 0.0
        dsp.rec115_perm = Arr[F64, 4](fill=0.0)
        dsp.const500 = 0.0
        dsp.const501 = 0.0
        dsp.const502 = 0.0
        dsp.const503 = 0.0
        dsp.const504 = 0.0
        dsp.const505 = 0.0
        dsp.const506 = 0.0
        dsp.const507 = 0.0
        dsp.const508 = 0.0
        dsp.rec114_perm = Arr[F64, 4](fill=0.0)
        dsp.const509 = 0.0
        dsp.const510 = 0.0
        dsp.const511 = 0.0
        dsp.const512 = 0.0
        dsp.const513 = 0.0
        dsp.const514 = 0.0
        dsp.rec113_perm = Arr[F64, 4](fill=0.0)
        dsp.const515 = 0.0
        dsp.const516 = 0.0
        dsp.const517 = 0.0
        dsp.const518 = 0.0
        dsp.const519 = 0.0
        dsp.const520 = 0.0
        dsp.rec112_perm = Arr[F64, 4](fill=0.0)
        dsp.const521 = 0.0
        dsp.const522 = 0.0
        dsp.const523 = 0.0
        dsp.rec111_perm = Arr[F64, 4](fill=0.0)
        dsp.const524 = 0.0
        dsp.const525 = 0.0
        dsp.const526 = 0.0
        dsp.rec121_perm = Arr[F64, 4](fill=0.0)
        dsp.const527 = 0.0
        dsp.const528 = 0.0
        dsp.const529 = 0.0
        dsp.const530 = 0.0
        dsp.const531 = 0.0
        dsp.const532 = 0.0
        dsp.rec120_perm = Arr[F64, 4](fill=0.0)
        dsp.const533 = 0.0
        dsp.const534 = 0.0
        dsp.const535 = 0.0
        dsp.const536 = 0.0
        dsp.const537 = 0.0
        dsp.rec119_perm = Arr[F64, 4](fill=0.0)
        dsp.const538 = 0.0
        dsp.const539 = 0.0
        dsp.rec118_perm = Arr[F64, 4](fill=0.0)
        dsp.hslider15 = 0.0
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
        dsp.const2 = (6.283185307179586) / (dsp.const0)
        dsp.const3 = (0.25) * (dsp.const0)
        dsp.const4 = (0.041666666666666664) * (pow_unrolled[2](dsp.const0))
        dsp.const5 = (0.005208333333333333) * (pow_unrolled[3](dsp.const0))
        dsp.const6 = (3.141592653589793) / (dsp.const0)
        dsp.const7 = tan((50265.48245743669) / (dsp.const0))
        dsp.const8 = (1.0) / (dsp.const7)
        dsp.const9 = (1.0) / ((((dsp.const8) + (3.1897274020965583)) / (dsp.const7)) + (4.076781969643807))
        dsp.const10 = (((dsp.const8) + (-3.1897274020965583)) / (dsp.const7)) + (4.076781969643807)
        dsp.const11 = pow_unrolled[2](dsp.const7)
        dsp.const12 = (1.0) / (dsp.const11)
        dsp.const13 = (2.0) * ((4.076781969643807) - (dsp.const12))
        dsp.const14 = (0.0017661728399818856) / (dsp.const11)
        dsp.const15 = (dsp.const14) + (0.00040767818495825777)
        dsp.const16 = (2.0) * ((0.00040767818495825777) - (dsp.const14))
        dsp.const17 = (1.0) / ((((dsp.const8) + (0.7431304601070396)) / (dsp.const7)) + (1.450071084655647))
        dsp.const18 = (((dsp.const8) + (-0.7431304601070396)) / (dsp.const7)) + (1.450071084655647)
        dsp.const19 = (2.0) * ((1.450071084655647) - (dsp.const12))
        dsp.const20 = (11.052052171507189) / (dsp.const11)
        dsp.const21 = (dsp.const20) + (1.450071084655647)
        dsp.const22 = (2.0) * ((1.450071084655647) - (dsp.const20))
        dsp.const23 = (1.0) / ((((dsp.const8) + (0.157482159302087)) / (dsp.const7)) + (0.9351401670315425))
        dsp.const24 = (((dsp.const8) + (-0.157482159302087)) / (dsp.const7)) + (0.9351401670315425)
        dsp.const25 = (2.0) * ((0.9351401670315425) - (dsp.const12))
        dsp.const26 = (1e+03) / (dsp.const0)
        dsp.const27 = (50.063807016150385) / (dsp.const11)
        dsp.const28 = (dsp.const27) + (0.9351401670315425)
        dsp.const29 = (2.0) * ((0.9351401670315425) - (dsp.const27))
        dsp.const30 = (1.0) / ((((dsp.const8) + (0.782413046821645)) / (dsp.const7)) + (0.24529150870616))
        dsp.const31 = (((dsp.const8) + (-0.782413046821645)) / (dsp.const7)) + (0.24529150870616)
        dsp.const32 = (2.0) * ((0.24529150870616) - (dsp.const12))
        dsp.const33 = (9.9999997055e-05) / (dsp.const11)
        dsp.const34 = (dsp.const33) + (0.000433227200555)
        dsp.const35 = (2.0) * ((0.000433227200555) - (dsp.const33))
        dsp.const36 = (1.0) / ((((dsp.const8) + (0.512478641889141)) / (dsp.const7)) + (0.689621364484675))
        dsp.const37 = (((dsp.const8) + (-0.512478641889141)) / (dsp.const7)) + (0.689621364484675)
        dsp.const38 = (2.0) * ((0.689621364484675) - (dsp.const12))
        dsp.const39 = (dsp.const12) + (7.621731298870603)
        dsp.const40 = (2.0) * ((7.621731298870603) - (dsp.const12))
        dsp.const41 = (1.0) / ((((dsp.const8) + (0.168404871113589)) / (dsp.const7)) + (1.069358407707312))
        dsp.const42 = (((dsp.const8) + (-0.168404871113589)) / (dsp.const7)) + (1.069358407707312)
        dsp.const43 = (2.0) * ((1.069358407707312) - (dsp.const12))
        dsp.const44 = (dsp.const12) + (53.53615295455673)
        dsp.const45 = (2.0) * ((53.53615295455673) - (dsp.const12))
        dsp.const46 = tan((31665.269715622984) / (dsp.const0))
        dsp.const47 = (1.0) / (dsp.const46)
        dsp.const48 = (1.0) / ((((dsp.const47) + (3.1897274020965583)) / (dsp.const46)) + (4.076781969643807))
        dsp.const49 = (((dsp.const47) + (-3.1897274020965583)) / (dsp.const46)) + (4.076781969643807)
        dsp.const50 = pow_unrolled[2](dsp.const46)
        dsp.const51 = (1.0) / (dsp.const50)
        dsp.const52 = (2.0) * ((4.076781969643807) - (dsp.const51))
        dsp.const53 = (0.0017661728399818856) / (dsp.const50)
        dsp.const54 = (dsp.const53) + (0.00040767818495825777)
        dsp.const55 = (2.0) * ((0.00040767818495825777) - (dsp.const53))
        dsp.const56 = (1.0) / ((((dsp.const47) + (0.7431304601070396)) / (dsp.const46)) + (1.450071084655647))
        dsp.const57 = (((dsp.const47) + (-0.7431304601070396)) / (dsp.const46)) + (1.450071084655647)
        dsp.const58 = (2.0) * ((1.450071084655647) - (dsp.const51))
        dsp.const59 = (11.052052171507189) / (dsp.const50)
        dsp.const60 = (dsp.const59) + (1.450071084655647)
        dsp.const61 = (2.0) * ((1.450071084655647) - (dsp.const59))
        dsp.const62 = (1.0) / ((((dsp.const47) + (0.157482159302087)) / (dsp.const46)) + (0.9351401670315425))
        dsp.const63 = (((dsp.const47) + (-0.157482159302087)) / (dsp.const46)) + (0.9351401670315425)
        dsp.const64 = (2.0) * ((0.9351401670315425) - (dsp.const51))
        dsp.const65 = (50.063807016150385) / (dsp.const50)
        dsp.const66 = (dsp.const65) + (0.9351401670315425)
        dsp.const67 = (2.0) * ((0.9351401670315425) - (dsp.const65))
        dsp.const68 = (1.0) / ((((dsp.const47) + (0.782413046821645)) / (dsp.const46)) + (0.24529150870616))
        dsp.const69 = (((dsp.const47) + (-0.782413046821645)) / (dsp.const46)) + (0.24529150870616)
        dsp.const70 = (2.0) * ((0.24529150870616) - (dsp.const51))
        dsp.const71 = (9.9999997055e-05) / (dsp.const50)
        dsp.const72 = (dsp.const71) + (0.000433227200555)
        dsp.const73 = (2.0) * ((0.000433227200555) - (dsp.const71))
        dsp.const74 = (1.0) / ((((dsp.const47) + (0.512478641889141)) / (dsp.const46)) + (0.689621364484675))
        dsp.const75 = (((dsp.const47) + (-0.512478641889141)) / (dsp.const46)) + (0.689621364484675)
        dsp.const76 = (2.0) * ((0.689621364484675) - (dsp.const51))
        dsp.const77 = (dsp.const51) + (7.621731298870603)
        dsp.const78 = (2.0) * ((7.621731298870603) - (dsp.const51))
        dsp.const79 = (1.0) / ((((dsp.const47) + (0.168404871113589)) / (dsp.const46)) + (1.069358407707312))
        dsp.const80 = (((dsp.const47) + (-0.168404871113589)) / (dsp.const46)) + (1.069358407707312)
        dsp.const81 = (2.0) * ((1.069358407707312) - (dsp.const51))
        dsp.const82 = (dsp.const51) + (53.53615295455673)
        dsp.const83 = (2.0) * ((53.53615295455673) - (dsp.const51))
        dsp.const84 = tan((19947.869932656024) / (dsp.const0))
        dsp.const85 = (1.0) / (dsp.const84)
        dsp.const86 = (1.0) / ((((dsp.const85) + (3.1897274020965583)) / (dsp.const84)) + (4.076781969643807))
        dsp.const87 = (((dsp.const85) + (-3.1897274020965583)) / (dsp.const84)) + (4.076781969643807)
        dsp.const88 = pow_unrolled[2](dsp.const84)
        dsp.const89 = (1.0) / (dsp.const88)
        dsp.const90 = (2.0) * ((4.076781969643807) - (dsp.const89))
        dsp.const91 = (0.0017661728399818856) / (dsp.const88)
        dsp.const92 = (dsp.const91) + (0.00040767818495825777)
        dsp.const93 = (2.0) * ((0.00040767818495825777) - (dsp.const91))
        dsp.const94 = (1.0) / ((((dsp.const85) + (0.7431304601070396)) / (dsp.const84)) + (1.450071084655647))
        dsp.const95 = (((dsp.const85) + (-0.7431304601070396)) / (dsp.const84)) + (1.450071084655647)
        dsp.const96 = (2.0) * ((1.450071084655647) - (dsp.const89))
        dsp.const97 = (11.052052171507189) / (dsp.const88)
        dsp.const98 = (dsp.const97) + (1.450071084655647)
        dsp.const99 = (2.0) * ((1.450071084655647) - (dsp.const97))
        dsp.const100 = (1.0) / ((((dsp.const85) + (0.157482159302087)) / (dsp.const84)) + (0.9351401670315425))
        dsp.const101 = (((dsp.const85) + (-0.157482159302087)) / (dsp.const84)) + (0.9351401670315425)
        dsp.const102 = (2.0) * ((0.9351401670315425) - (dsp.const89))
        dsp.const103 = (50.063807016150385) / (dsp.const88)
        dsp.const104 = (dsp.const103) + (0.9351401670315425)
        dsp.const105 = (2.0) * ((0.9351401670315425) - (dsp.const103))
        dsp.const106 = (1.0) / ((((dsp.const85) + (0.782413046821645)) / (dsp.const84)) + (0.24529150870616))
        dsp.const107 = (((dsp.const85) + (-0.782413046821645)) / (dsp.const84)) + (0.24529150870616)
        dsp.const108 = (2.0) * ((0.24529150870616) - (dsp.const89))
        dsp.const109 = (9.9999997055e-05) / (dsp.const88)
        dsp.const110 = (dsp.const109) + (0.000433227200555)
        dsp.const111 = (2.0) * ((0.000433227200555) - (dsp.const109))
        dsp.const112 = (1.0) / ((((dsp.const85) + (0.512478641889141)) / (dsp.const84)) + (0.689621364484675))
        dsp.const113 = (((dsp.const85) + (-0.512478641889141)) / (dsp.const84)) + (0.689621364484675)
        dsp.const114 = (2.0) * ((0.689621364484675) - (dsp.const89))
        dsp.const115 = (dsp.const89) + (7.621731298870603)
        dsp.const116 = (2.0) * ((7.621731298870603) - (dsp.const89))
        dsp.const117 = (1.0) / ((((dsp.const85) + (0.168404871113589)) / (dsp.const84)) + (1.069358407707312))
        dsp.const118 = (((dsp.const85) + (-0.168404871113589)) / (dsp.const84)) + (1.069358407707312)
        dsp.const119 = (2.0) * ((1.069358407707312) - (dsp.const89))
        dsp.const120 = (dsp.const89) + (53.53615295455673)
        dsp.const121 = (2.0) * ((53.53615295455673) - (dsp.const89))
        dsp.const122 = tan((12566.370614359172) / (dsp.const0))
        dsp.const123 = (1.0) / (dsp.const122)
        dsp.const124 = (1.0) / ((((dsp.const123) + (3.1897274020965583)) / (dsp.const122)) + (4.076781969643807))
        dsp.const125 = (((dsp.const123) + (-3.1897274020965583)) / (dsp.const122)) + (4.076781969643807)
        dsp.const126 = pow_unrolled[2](dsp.const122)
        dsp.const127 = (1.0) / (dsp.const126)
        dsp.const128 = (2.0) * ((4.076781969643807) - (dsp.const127))
        dsp.const129 = (0.0017661728399818856) / (dsp.const126)
        dsp.const130 = (dsp.const129) + (0.00040767818495825777)
        dsp.const131 = (2.0) * ((0.00040767818495825777) - (dsp.const129))
        dsp.const132 = (1.0) / ((((dsp.const123) + (0.7431304601070396)) / (dsp.const122)) + (1.450071084655647))
        dsp.const133 = (((dsp.const123) + (-0.7431304601070396)) / (dsp.const122)) + (1.450071084655647)
        dsp.const134 = (2.0) * ((1.450071084655647) - (dsp.const127))
        dsp.const135 = (11.052052171507189) / (dsp.const126)
        dsp.const136 = (dsp.const135) + (1.450071084655647)
        dsp.const137 = (2.0) * ((1.450071084655647) - (dsp.const135))
        dsp.const138 = (1.0) / ((((dsp.const123) + (0.157482159302087)) / (dsp.const122)) + (0.9351401670315425))
        dsp.const139 = (((dsp.const123) + (-0.157482159302087)) / (dsp.const122)) + (0.9351401670315425)
        dsp.const140 = (2.0) * ((0.9351401670315425) - (dsp.const127))
        dsp.const141 = (50.063807016150385) / (dsp.const126)
        dsp.const142 = (dsp.const141) + (0.9351401670315425)
        dsp.const143 = (2.0) * ((0.9351401670315425) - (dsp.const141))
        dsp.const144 = (1.0) / ((((dsp.const123) + (0.782413046821645)) / (dsp.const122)) + (0.24529150870616))
        dsp.const145 = (((dsp.const123) + (-0.782413046821645)) / (dsp.const122)) + (0.24529150870616)
        dsp.const146 = (2.0) * ((0.24529150870616) - (dsp.const127))
        dsp.const147 = (9.9999997055e-05) / (dsp.const126)
        dsp.const148 = (dsp.const147) + (0.000433227200555)
        dsp.const149 = (2.0) * ((0.000433227200555) - (dsp.const147))
        dsp.const150 = (1.0) / ((((dsp.const123) + (0.512478641889141)) / (dsp.const122)) + (0.689621364484675))
        dsp.const151 = (((dsp.const123) + (-0.512478641889141)) / (dsp.const122)) + (0.689621364484675)
        dsp.const152 = (2.0) * ((0.689621364484675) - (dsp.const127))
        dsp.const153 = (dsp.const127) + (7.621731298870603)
        dsp.const154 = (2.0) * ((7.621731298870603) - (dsp.const127))
        dsp.const155 = (1.0) / ((((dsp.const123) + (0.168404871113589)) / (dsp.const122)) + (1.069358407707312))
        dsp.const156 = (((dsp.const123) + (-0.168404871113589)) / (dsp.const122)) + (1.069358407707312)
        dsp.const157 = (2.0) * ((1.069358407707312) - (dsp.const127))
        dsp.const158 = (dsp.const127) + (53.53615295455673)
        dsp.const159 = (2.0) * ((53.53615295455673) - (dsp.const127))
        dsp.const160 = tan((7916.317428905746) / (dsp.const0))
        dsp.const161 = (1.0) / (dsp.const160)
        dsp.const162 = (1.0) / ((((dsp.const161) + (3.1897274020965583)) / (dsp.const160)) + (4.076781969643807))
        dsp.const163 = (((dsp.const161) + (-3.1897274020965583)) / (dsp.const160)) + (4.076781969643807)
        dsp.const164 = pow_unrolled[2](dsp.const160)
        dsp.const165 = (1.0) / (dsp.const164)
        dsp.const166 = (2.0) * ((4.076781969643807) - (dsp.const165))
        dsp.const167 = (0.0017661728399818856) / (dsp.const164)
        dsp.const168 = (dsp.const167) + (0.00040767818495825777)
        dsp.const169 = (2.0) * ((0.00040767818495825777) - (dsp.const167))
        dsp.const170 = (1.0) / ((((dsp.const161) + (0.7431304601070396)) / (dsp.const160)) + (1.450071084655647))
        dsp.const171 = (((dsp.const161) + (-0.7431304601070396)) / (dsp.const160)) + (1.450071084655647)
        dsp.const172 = (2.0) * ((1.450071084655647) - (dsp.const165))
        dsp.const173 = (11.052052171507189) / (dsp.const164)
        dsp.const174 = (dsp.const173) + (1.450071084655647)
        dsp.const175 = (2.0) * ((1.450071084655647) - (dsp.const173))
        dsp.const176 = (1.0) / ((((dsp.const161) + (0.157482159302087)) / (dsp.const160)) + (0.9351401670315425))
        dsp.const177 = (((dsp.const161) + (-0.157482159302087)) / (dsp.const160)) + (0.9351401670315425)
        dsp.const178 = (2.0) * ((0.9351401670315425) - (dsp.const165))
        dsp.const179 = (50.063807016150385) / (dsp.const164)
        dsp.const180 = (dsp.const179) + (0.9351401670315425)
        dsp.const181 = (2.0) * ((0.9351401670315425) - (dsp.const179))
        dsp.const182 = (1.0) / ((((dsp.const161) + (0.782413046821645)) / (dsp.const160)) + (0.24529150870616))
        dsp.const183 = (((dsp.const161) + (-0.782413046821645)) / (dsp.const160)) + (0.24529150870616)
        dsp.const184 = (2.0) * ((0.24529150870616) - (dsp.const165))
        dsp.const185 = (9.9999997055e-05) / (dsp.const164)
        dsp.const186 = (dsp.const185) + (0.000433227200555)
        dsp.const187 = (2.0) * ((0.000433227200555) - (dsp.const185))
        dsp.const188 = (1.0) / ((((dsp.const161) + (0.512478641889141)) / (dsp.const160)) + (0.689621364484675))
        dsp.const189 = (((dsp.const161) + (-0.512478641889141)) / (dsp.const160)) + (0.689621364484675)
        dsp.const190 = (2.0) * ((0.689621364484675) - (dsp.const165))
        dsp.const191 = (dsp.const165) + (7.621731298870603)
        dsp.const192 = (2.0) * ((7.621731298870603) - (dsp.const165))
        dsp.const193 = (1.0) / ((((dsp.const161) + (0.168404871113589)) / (dsp.const160)) + (1.069358407707312))
        dsp.const194 = (((dsp.const161) + (-0.168404871113589)) / (dsp.const160)) + (1.069358407707312)
        dsp.const195 = (2.0) * ((1.069358407707312) - (dsp.const165))
        dsp.const196 = (dsp.const165) + (53.53615295455673)
        dsp.const197 = (2.0) * ((53.53615295455673) - (dsp.const165))
        dsp.const198 = tan((4986.967483164005) / (dsp.const0))
        dsp.const199 = (1.0) / (dsp.const198)
        dsp.const200 = (1.0) / ((((dsp.const199) + (3.1897274020965583)) / (dsp.const198)) + (4.076781969643807))
        dsp.const201 = (((dsp.const199) + (-3.1897274020965583)) / (dsp.const198)) + (4.076781969643807)
        dsp.const202 = pow_unrolled[2](dsp.const198)
        dsp.const203 = (1.0) / (dsp.const202)
        dsp.const204 = (2.0) * ((4.076781969643807) - (dsp.const203))
        dsp.const205 = (0.0017661728399818856) / (dsp.const202)
        dsp.const206 = (dsp.const205) + (0.00040767818495825777)
        dsp.const207 = (2.0) * ((0.00040767818495825777) - (dsp.const205))
        dsp.const208 = (1.0) / ((((dsp.const199) + (0.7431304601070396)) / (dsp.const198)) + (1.450071084655647))
        dsp.const209 = (((dsp.const199) + (-0.7431304601070396)) / (dsp.const198)) + (1.450071084655647)
        dsp.const210 = (2.0) * ((1.450071084655647) - (dsp.const203))
        dsp.const211 = (11.052052171507189) / (dsp.const202)
        dsp.const212 = (dsp.const211) + (1.450071084655647)
        dsp.const213 = (2.0) * ((1.450071084655647) - (dsp.const211))
        dsp.const214 = (1.0) / ((((dsp.const199) + (0.157482159302087)) / (dsp.const198)) + (0.9351401670315425))
        dsp.const215 = (((dsp.const199) + (-0.157482159302087)) / (dsp.const198)) + (0.9351401670315425)
        dsp.const216 = (2.0) * ((0.9351401670315425) - (dsp.const203))
        dsp.const217 = (50.063807016150385) / (dsp.const202)
        dsp.const218 = (dsp.const217) + (0.9351401670315425)
        dsp.const219 = (2.0) * ((0.9351401670315425) - (dsp.const217))
        dsp.const220 = (1.0) / ((((dsp.const199) + (0.782413046821645)) / (dsp.const198)) + (0.24529150870616))
        dsp.const221 = (((dsp.const199) + (-0.782413046821645)) / (dsp.const198)) + (0.24529150870616)
        dsp.const222 = (2.0) * ((0.24529150870616) - (dsp.const203))
        dsp.const223 = (9.9999997055e-05) / (dsp.const202)
        dsp.const224 = (dsp.const223) + (0.000433227200555)
        dsp.const225 = (2.0) * ((0.000433227200555) - (dsp.const223))
        dsp.const226 = (1.0) / ((((dsp.const199) + (0.512478641889141)) / (dsp.const198)) + (0.689621364484675))
        dsp.const227 = (((dsp.const199) + (-0.512478641889141)) / (dsp.const198)) + (0.689621364484675)
        dsp.const228 = (2.0) * ((0.689621364484675) - (dsp.const203))
        dsp.const229 = (dsp.const203) + (7.621731298870603)
        dsp.const230 = (2.0) * ((7.621731298870603) - (dsp.const203))
        dsp.const231 = (1.0) / ((((dsp.const199) + (0.168404871113589)) / (dsp.const198)) + (1.069358407707312))
        dsp.const232 = (((dsp.const199) + (-0.168404871113589)) / (dsp.const198)) + (1.069358407707312)
        dsp.const233 = (2.0) * ((1.069358407707312) - (dsp.const203))
        dsp.const234 = (dsp.const203) + (53.53615295455673)
        dsp.const235 = (2.0) * ((53.53615295455673) - (dsp.const203))
        dsp.const236 = tan((3141.592653589793) / (dsp.const0))
        dsp.const237 = (1.0) / (dsp.const236)
        dsp.const238 = (1.0) / ((((dsp.const237) + (3.1897274020965583)) / (dsp.const236)) + (4.076781969643807))
        dsp.const239 = (((dsp.const237) + (-3.1897274020965583)) / (dsp.const236)) + (4.076781969643807)
        dsp.const240 = pow_unrolled[2](dsp.const236)
        dsp.const241 = (1.0) / (dsp.const240)
        dsp.const242 = (2.0) * ((4.076781969643807) - (dsp.const241))
        dsp.const243 = (0.0017661728399818856) / (dsp.const240)
        dsp.const244 = (dsp.const243) + (0.00040767818495825777)
        dsp.const245 = (2.0) * ((0.00040767818495825777) - (dsp.const243))
        dsp.const246 = (1.0) / ((((dsp.const237) + (0.7431304601070396)) / (dsp.const236)) + (1.450071084655647))
        dsp.const247 = (((dsp.const237) + (-0.7431304601070396)) / (dsp.const236)) + (1.450071084655647)
        dsp.const248 = (2.0) * ((1.450071084655647) - (dsp.const241))
        dsp.const249 = (11.052052171507189) / (dsp.const240)
        dsp.const250 = (dsp.const249) + (1.450071084655647)
        dsp.const251 = (2.0) * ((1.450071084655647) - (dsp.const249))
        dsp.const252 = (1.0) / ((((dsp.const237) + (0.157482159302087)) / (dsp.const236)) + (0.9351401670315425))
        dsp.const253 = (((dsp.const237) + (-0.157482159302087)) / (dsp.const236)) + (0.9351401670315425)
        dsp.const254 = (2.0) * ((0.9351401670315425) - (dsp.const241))
        dsp.const255 = (50.063807016150385) / (dsp.const240)
        dsp.const256 = (dsp.const255) + (0.9351401670315425)
        dsp.const257 = (2.0) * ((0.9351401670315425) - (dsp.const255))
        dsp.const258 = (1.0) / ((((dsp.const237) + (0.782413046821645)) / (dsp.const236)) + (0.24529150870616))
        dsp.const259 = (((dsp.const237) + (-0.782413046821645)) / (dsp.const236)) + (0.24529150870616)
        dsp.const260 = (2.0) * ((0.24529150870616) - (dsp.const241))
        dsp.const261 = (9.9999997055e-05) / (dsp.const240)
        dsp.const262 = (dsp.const261) + (0.000433227200555)
        dsp.const263 = (2.0) * ((0.000433227200555) - (dsp.const261))
        dsp.const264 = (1.0) / ((((dsp.const237) + (0.512478641889141)) / (dsp.const236)) + (0.689621364484675))
        dsp.const265 = (((dsp.const237) + (-0.512478641889141)) / (dsp.const236)) + (0.689621364484675)
        dsp.const266 = (2.0) * ((0.689621364484675) - (dsp.const241))
        dsp.const267 = (dsp.const241) + (7.621731298870603)
        dsp.const268 = (2.0) * ((7.621731298870603) - (dsp.const241))
        dsp.const269 = (1.0) / ((((dsp.const237) + (0.168404871113589)) / (dsp.const236)) + (1.069358407707312))
        dsp.const270 = (((dsp.const237) + (-0.168404871113589)) / (dsp.const236)) + (1.069358407707312)
        dsp.const271 = (2.0) * ((1.069358407707312) - (dsp.const241))
        dsp.const272 = (dsp.const241) + (53.53615295455673)
        dsp.const273 = (2.0) * ((53.53615295455673) - (dsp.const241))
        dsp.const274 = tan((1979.079357226436) / (dsp.const0))
        dsp.const275 = (1.0) / (dsp.const274)
        dsp.const276 = (1.0) / ((((dsp.const275) + (3.1897274020965583)) / (dsp.const274)) + (4.076781969643807))
        dsp.const277 = (((dsp.const275) + (-3.1897274020965583)) / (dsp.const274)) + (4.076781969643807)
        dsp.const278 = pow_unrolled[2](dsp.const274)
        dsp.const279 = (1.0) / (dsp.const278)
        dsp.const280 = (2.0) * ((4.076781969643807) - (dsp.const279))
        dsp.const281 = (0.0017661728399818856) / (dsp.const278)
        dsp.const282 = (dsp.const281) + (0.00040767818495825777)
        dsp.const283 = (2.0) * ((0.00040767818495825777) - (dsp.const281))
        dsp.const284 = (1.0) / ((((dsp.const275) + (0.7431304601070396)) / (dsp.const274)) + (1.450071084655647))
        dsp.const285 = (((dsp.const275) + (-0.7431304601070396)) / (dsp.const274)) + (1.450071084655647)
        dsp.const286 = (2.0) * ((1.450071084655647) - (dsp.const279))
        dsp.const287 = (11.052052171507189) / (dsp.const278)
        dsp.const288 = (dsp.const287) + (1.450071084655647)
        dsp.const289 = (2.0) * ((1.450071084655647) - (dsp.const287))
        dsp.const290 = (1.0) / ((((dsp.const275) + (0.157482159302087)) / (dsp.const274)) + (0.9351401670315425))
        dsp.const291 = (((dsp.const275) + (-0.157482159302087)) / (dsp.const274)) + (0.9351401670315425)
        dsp.const292 = (2.0) * ((0.9351401670315425) - (dsp.const279))
        dsp.const293 = (50.063807016150385) / (dsp.const278)
        dsp.const294 = (dsp.const293) + (0.9351401670315425)
        dsp.const295 = (2.0) * ((0.9351401670315425) - (dsp.const293))
        dsp.const296 = (1.0) / ((((dsp.const275) + (0.782413046821645)) / (dsp.const274)) + (0.24529150870616))
        dsp.const297 = (((dsp.const275) + (-0.782413046821645)) / (dsp.const274)) + (0.24529150870616)
        dsp.const298 = (2.0) * ((0.24529150870616) - (dsp.const279))
        dsp.const299 = (9.9999997055e-05) / (dsp.const278)
        dsp.const300 = (dsp.const299) + (0.000433227200555)
        dsp.const301 = (2.0) * ((0.000433227200555) - (dsp.const299))
        dsp.const302 = (1.0) / ((((dsp.const275) + (0.512478641889141)) / (dsp.const274)) + (0.689621364484675))
        dsp.const303 = (((dsp.const275) + (-0.512478641889141)) / (dsp.const274)) + (0.689621364484675)
        dsp.const304 = (2.0) * ((0.689621364484675) - (dsp.const279))
        dsp.const305 = (dsp.const279) + (7.621731298870603)
        dsp.const306 = (2.0) * ((7.621731298870603) - (dsp.const279))
        dsp.const307 = (1.0) / ((((dsp.const275) + (0.168404871113589)) / (dsp.const274)) + (1.069358407707312))
        dsp.const308 = (((dsp.const275) + (-0.168404871113589)) / (dsp.const274)) + (1.069358407707312)
        dsp.const309 = (2.0) * ((1.069358407707312) - (dsp.const279))
        dsp.const310 = (dsp.const279) + (53.53615295455673)
        dsp.const311 = (2.0) * ((53.53615295455673) - (dsp.const279))
        dsp.const312 = tan((1246.7418707910015) / (dsp.const0))
        dsp.const313 = (1.0) / (dsp.const312)
        dsp.const314 = (1.0) / ((((dsp.const313) + (3.1897274020965583)) / (dsp.const312)) + (4.076781969643807))
        dsp.const315 = (((dsp.const313) + (-3.1897274020965583)) / (dsp.const312)) + (4.076781969643807)
        dsp.const316 = pow_unrolled[2](dsp.const312)
        dsp.const317 = (1.0) / (dsp.const316)
        dsp.const318 = (2.0) * ((4.076781969643807) - (dsp.const317))
        dsp.const319 = (0.0017661728399818856) / (dsp.const316)
        dsp.const320 = (dsp.const319) + (0.00040767818495825777)
        dsp.const321 = (2.0) * ((0.00040767818495825777) - (dsp.const319))
        dsp.const322 = (1.0) / ((((dsp.const313) + (0.7431304601070396)) / (dsp.const312)) + (1.450071084655647))
        dsp.const323 = (((dsp.const313) + (-0.7431304601070396)) / (dsp.const312)) + (1.450071084655647)
        dsp.const324 = (2.0) * ((1.450071084655647) - (dsp.const317))
        dsp.const325 = (11.052052171507189) / (dsp.const316)
        dsp.const326 = (dsp.const325) + (1.450071084655647)
        dsp.const327 = (2.0) * ((1.450071084655647) - (dsp.const325))
        dsp.const328 = (1.0) / ((((dsp.const313) + (0.157482159302087)) / (dsp.const312)) + (0.9351401670315425))
        dsp.const329 = (((dsp.const313) + (-0.157482159302087)) / (dsp.const312)) + (0.9351401670315425)
        dsp.const330 = (2.0) * ((0.9351401670315425) - (dsp.const317))
        dsp.const331 = (50.063807016150385) / (dsp.const316)
        dsp.const332 = (dsp.const331) + (0.9351401670315425)
        dsp.const333 = (2.0) * ((0.9351401670315425) - (dsp.const331))
        dsp.const334 = (1.0) / ((((dsp.const313) + (0.782413046821645)) / (dsp.const312)) + (0.24529150870616))
        dsp.const335 = (((dsp.const313) + (-0.782413046821645)) / (dsp.const312)) + (0.24529150870616)
        dsp.const336 = (2.0) * ((0.24529150870616) - (dsp.const317))
        dsp.const337 = (9.9999997055e-05) / (dsp.const316)
        dsp.const338 = (dsp.const337) + (0.000433227200555)
        dsp.const339 = (2.0) * ((0.000433227200555) - (dsp.const337))
        dsp.const340 = (1.0) / ((((dsp.const313) + (0.512478641889141)) / (dsp.const312)) + (0.689621364484675))
        dsp.const341 = (((dsp.const313) + (-0.512478641889141)) / (dsp.const312)) + (0.689621364484675)
        dsp.const342 = (2.0) * ((0.689621364484675) - (dsp.const317))
        dsp.const343 = (dsp.const317) + (7.621731298870603)
        dsp.const344 = (2.0) * ((7.621731298870603) - (dsp.const317))
        dsp.const345 = (1.0) / ((((dsp.const313) + (0.168404871113589)) / (dsp.const312)) + (1.069358407707312))
        dsp.const346 = (((dsp.const313) + (-0.168404871113589)) / (dsp.const312)) + (1.069358407707312)
        dsp.const347 = (2.0) * ((1.069358407707312) - (dsp.const317))
        dsp.const348 = (dsp.const317) + (53.53615295455673)
        dsp.const349 = (2.0) * ((53.53615295455673) - (dsp.const317))
        dsp.const350 = tan((785.3981633974482) / (dsp.const0))
        dsp.const351 = (1.0) / (dsp.const350)
        dsp.const352 = (1.0) / ((((dsp.const351) + (3.1897274020965583)) / (dsp.const350)) + (4.076781969643807))
        dsp.const353 = (((dsp.const351) + (-3.1897274020965583)) / (dsp.const350)) + (4.076781969643807)
        dsp.const354 = pow_unrolled[2](dsp.const350)
        dsp.const355 = (1.0) / (dsp.const354)
        dsp.const356 = (2.0) * ((4.076781969643807) - (dsp.const355))
        dsp.const357 = (0.0017661728399818856) / (dsp.const354)
        dsp.const358 = (dsp.const357) + (0.00040767818495825777)
        dsp.const359 = (2.0) * ((0.00040767818495825777) - (dsp.const357))
        dsp.const360 = (1.0) / ((((dsp.const351) + (0.7431304601070396)) / (dsp.const350)) + (1.450071084655647))
        dsp.const361 = (((dsp.const351) + (-0.7431304601070396)) / (dsp.const350)) + (1.450071084655647)
        dsp.const362 = (2.0) * ((1.450071084655647) - (dsp.const355))
        dsp.const363 = (11.052052171507189) / (dsp.const354)
        dsp.const364 = (dsp.const363) + (1.450071084655647)
        dsp.const365 = (2.0) * ((1.450071084655647) - (dsp.const363))
        dsp.const366 = (1.0) / ((((dsp.const351) + (0.157482159302087)) / (dsp.const350)) + (0.9351401670315425))
        dsp.const367 = (((dsp.const351) + (-0.157482159302087)) / (dsp.const350)) + (0.9351401670315425)
        dsp.const368 = (2.0) * ((0.9351401670315425) - (dsp.const355))
        dsp.const369 = (50.063807016150385) / (dsp.const354)
        dsp.const370 = (dsp.const369) + (0.9351401670315425)
        dsp.const371 = (2.0) * ((0.9351401670315425) - (dsp.const369))
        dsp.const372 = (1.0) / ((((dsp.const351) + (0.782413046821645)) / (dsp.const350)) + (0.24529150870616))
        dsp.const373 = (((dsp.const351) + (-0.782413046821645)) / (dsp.const350)) + (0.24529150870616)
        dsp.const374 = (2.0) * ((0.24529150870616) - (dsp.const355))
        dsp.const375 = (9.9999997055e-05) / (dsp.const354)
        dsp.const376 = (dsp.const375) + (0.000433227200555)
        dsp.const377 = (2.0) * ((0.000433227200555) - (dsp.const375))
        dsp.const378 = (1.0) / ((((dsp.const351) + (0.512478641889141)) / (dsp.const350)) + (0.689621364484675))
        dsp.const379 = (((dsp.const351) + (-0.512478641889141)) / (dsp.const350)) + (0.689621364484675)
        dsp.const380 = (2.0) * ((0.689621364484675) - (dsp.const355))
        dsp.const381 = (dsp.const355) + (7.621731298870603)
        dsp.const382 = (2.0) * ((7.621731298870603) - (dsp.const355))
        dsp.const383 = (1.0) / ((((dsp.const351) + (0.168404871113589)) / (dsp.const350)) + (1.069358407707312))
        dsp.const384 = (((dsp.const351) + (-0.168404871113589)) / (dsp.const350)) + (1.069358407707312)
        dsp.const385 = (2.0) * ((1.069358407707312) - (dsp.const355))
        dsp.const386 = (dsp.const355) + (53.53615295455673)
        dsp.const387 = (2.0) * ((53.53615295455673) - (dsp.const355))
        dsp.const388 = tan((494.769839306609) / (dsp.const0))
        dsp.const389 = (1.0) / (dsp.const388)
        dsp.const390 = (1.0) / ((((dsp.const389) + (3.1897274020965583)) / (dsp.const388)) + (4.076781969643807))
        dsp.const391 = (((dsp.const389) + (-3.1897274020965583)) / (dsp.const388)) + (4.076781969643807)
        dsp.const392 = pow_unrolled[2](dsp.const388)
        dsp.const393 = (1.0) / (dsp.const392)
        dsp.const394 = (2.0) * ((4.076781969643807) - (dsp.const393))
        dsp.const395 = (0.0017661728399818856) / (dsp.const392)
        dsp.const396 = (dsp.const395) + (0.00040767818495825777)
        dsp.const397 = (2.0) * ((0.00040767818495825777) - (dsp.const395))
        dsp.const398 = (1.0) / ((((dsp.const389) + (0.7431304601070396)) / (dsp.const388)) + (1.450071084655647))
        dsp.const399 = (((dsp.const389) + (-0.7431304601070396)) / (dsp.const388)) + (1.450071084655647)
        dsp.const400 = (2.0) * ((1.450071084655647) - (dsp.const393))
        dsp.const401 = (11.052052171507189) / (dsp.const392)
        dsp.const402 = (dsp.const401) + (1.450071084655647)
        dsp.const403 = (2.0) * ((1.450071084655647) - (dsp.const401))
        dsp.const404 = (1.0) / ((((dsp.const389) + (0.157482159302087)) / (dsp.const388)) + (0.9351401670315425))
        dsp.const405 = (((dsp.const389) + (-0.157482159302087)) / (dsp.const388)) + (0.9351401670315425)
        dsp.const406 = (2.0) * ((0.9351401670315425) - (dsp.const393))
        dsp.const407 = (50.063807016150385) / (dsp.const392)
        dsp.const408 = (dsp.const407) + (0.9351401670315425)
        dsp.const409 = (2.0) * ((0.9351401670315425) - (dsp.const407))
        dsp.const410 = (1.0) / ((((dsp.const389) + (0.782413046821645)) / (dsp.const388)) + (0.24529150870616))
        dsp.const411 = (((dsp.const389) + (-0.782413046821645)) / (dsp.const388)) + (0.24529150870616)
        dsp.const412 = (2.0) * ((0.24529150870616) - (dsp.const393))
        dsp.const413 = (9.9999997055e-05) / (dsp.const392)
        dsp.const414 = (dsp.const413) + (0.000433227200555)
        dsp.const415 = (2.0) * ((0.000433227200555) - (dsp.const413))
        dsp.const416 = (1.0) / ((((dsp.const389) + (0.512478641889141)) / (dsp.const388)) + (0.689621364484675))
        dsp.const417 = (((dsp.const389) + (-0.512478641889141)) / (dsp.const388)) + (0.689621364484675)
        dsp.const418 = (2.0) * ((0.689621364484675) - (dsp.const393))
        dsp.const419 = (dsp.const393) + (7.621731298870603)
        dsp.const420 = (2.0) * ((7.621731298870603) - (dsp.const393))
        dsp.const421 = (1.0) / ((((dsp.const389) + (0.168404871113589)) / (dsp.const388)) + (1.069358407707312))
        dsp.const422 = (((dsp.const389) + (-0.168404871113589)) / (dsp.const388)) + (1.069358407707312)
        dsp.const423 = (2.0) * ((1.069358407707312) - (dsp.const393))
        dsp.const424 = (dsp.const393) + (53.53615295455673)
        dsp.const425 = (2.0) * ((53.53615295455673) - (dsp.const393))
        dsp.const426 = tan((311.68546769775037) / (dsp.const0))
        dsp.const427 = (1.0) / (dsp.const426)
        dsp.const428 = (1.0) / ((((dsp.const427) + (3.1897274020965583)) / (dsp.const426)) + (4.076781969643807))
        dsp.const429 = (((dsp.const427) + (-3.1897274020965583)) / (dsp.const426)) + (4.076781969643807)
        dsp.const430 = pow_unrolled[2](dsp.const426)
        dsp.const431 = (1.0) / (dsp.const430)
        dsp.const432 = (2.0) * ((4.076781969643807) - (dsp.const431))
        dsp.const433 = (0.0017661728399818856) / (dsp.const430)
        dsp.const434 = (dsp.const433) + (0.00040767818495825777)
        dsp.const435 = (2.0) * ((0.00040767818495825777) - (dsp.const433))
        dsp.const436 = (1.0) / ((((dsp.const427) + (0.7431304601070396)) / (dsp.const426)) + (1.450071084655647))
        dsp.const437 = (((dsp.const427) + (-0.7431304601070396)) / (dsp.const426)) + (1.450071084655647)
        dsp.const438 = (2.0) * ((1.450071084655647) - (dsp.const431))
        dsp.const439 = (11.052052171507189) / (dsp.const430)
        dsp.const440 = (dsp.const439) + (1.450071084655647)
        dsp.const441 = (2.0) * ((1.450071084655647) - (dsp.const439))
        dsp.const442 = (1.0) / ((((dsp.const427) + (0.157482159302087)) / (dsp.const426)) + (0.9351401670315425))
        dsp.const443 = (((dsp.const427) + (-0.157482159302087)) / (dsp.const426)) + (0.9351401670315425)
        dsp.const444 = (2.0) * ((0.9351401670315425) - (dsp.const431))
        dsp.const445 = (50.063807016150385) / (dsp.const430)
        dsp.const446 = (dsp.const445) + (0.9351401670315425)
        dsp.const447 = (2.0) * ((0.9351401670315425) - (dsp.const445))
        dsp.const448 = (1.0) / ((((dsp.const427) + (0.782413046821645)) / (dsp.const426)) + (0.24529150870616))
        dsp.const449 = (((dsp.const427) + (-0.782413046821645)) / (dsp.const426)) + (0.24529150870616)
        dsp.const450 = (2.0) * ((0.24529150870616) - (dsp.const431))
        dsp.const451 = (9.9999997055e-05) / (dsp.const430)
        dsp.const452 = (dsp.const451) + (0.000433227200555)
        dsp.const453 = (2.0) * ((0.000433227200555) - (dsp.const451))
        dsp.const454 = (1.0) / ((((dsp.const427) + (0.512478641889141)) / (dsp.const426)) + (0.689621364484675))
        dsp.const455 = (((dsp.const427) + (-0.512478641889141)) / (dsp.const426)) + (0.689621364484675)
        dsp.const456 = (2.0) * ((0.689621364484675) - (dsp.const431))
        dsp.const457 = (dsp.const431) + (7.621731298870603)
        dsp.const458 = (2.0) * ((7.621731298870603) - (dsp.const431))
        dsp.const459 = (1.0) / ((((dsp.const427) + (0.168404871113589)) / (dsp.const426)) + (1.069358407707312))
        dsp.const460 = (((dsp.const427) + (-0.168404871113589)) / (dsp.const426)) + (1.069358407707312)
        dsp.const461 = (2.0) * ((1.069358407707312) - (dsp.const431))
        dsp.const462 = (dsp.const431) + (53.53615295455673)
        dsp.const463 = (2.0) * ((53.53615295455673) - (dsp.const431))
        dsp.const464 = tan((196.34954084936206) / (dsp.const0))
        dsp.const465 = (1.0) / (dsp.const464)
        dsp.const466 = (1.0) / ((((dsp.const465) + (3.1897274020965583)) / (dsp.const464)) + (4.076781969643807))
        dsp.const467 = (((dsp.const465) + (-3.1897274020965583)) / (dsp.const464)) + (4.076781969643807)
        dsp.const468 = pow_unrolled[2](dsp.const464)
        dsp.const469 = (1.0) / (dsp.const468)
        dsp.const470 = (2.0) * ((4.076781969643807) - (dsp.const469))
        dsp.const471 = (0.0017661728399818856) / (dsp.const468)
        dsp.const472 = (dsp.const471) + (0.00040767818495825777)
        dsp.const473 = (2.0) * ((0.00040767818495825777) - (dsp.const471))
        dsp.const474 = (1.0) / ((((dsp.const465) + (0.7431304601070396)) / (dsp.const464)) + (1.450071084655647))
        dsp.const475 = (((dsp.const465) + (-0.7431304601070396)) / (dsp.const464)) + (1.450071084655647)
        dsp.const476 = (2.0) * ((1.450071084655647) - (dsp.const469))
        dsp.const477 = (11.052052171507189) / (dsp.const468)
        dsp.const478 = (dsp.const477) + (1.450071084655647)
        dsp.const479 = (2.0) * ((1.450071084655647) - (dsp.const477))
        dsp.const480 = (1.0) / ((((dsp.const465) + (0.157482159302087)) / (dsp.const464)) + (0.9351401670315425))
        dsp.const481 = (((dsp.const465) + (-0.157482159302087)) / (dsp.const464)) + (0.9351401670315425)
        dsp.const482 = (2.0) * ((0.9351401670315425) - (dsp.const469))
        dsp.const483 = (50.063807016150385) / (dsp.const468)
        dsp.const484 = (dsp.const483) + (0.9351401670315425)
        dsp.const485 = (2.0) * ((0.9351401670315425) - (dsp.const483))
        dsp.const486 = (1.0) / ((((dsp.const465) + (0.782413046821645)) / (dsp.const464)) + (0.24529150870616))
        dsp.const487 = (((dsp.const465) + (-0.782413046821645)) / (dsp.const464)) + (0.24529150870616)
        dsp.const488 = (2.0) * ((0.24529150870616) - (dsp.const469))
        dsp.const489 = (9.9999997055e-05) / (dsp.const468)
        dsp.const490 = (dsp.const489) + (0.000433227200555)
        dsp.const491 = (2.0) * ((0.000433227200555) - (dsp.const489))
        dsp.const492 = (1.0) / ((((dsp.const465) + (0.512478641889141)) / (dsp.const464)) + (0.689621364484675))
        dsp.const493 = (((dsp.const465) + (-0.512478641889141)) / (dsp.const464)) + (0.689621364484675)
        dsp.const494 = (2.0) * ((0.689621364484675) - (dsp.const469))
        dsp.const495 = (dsp.const469) + (7.621731298870603)
        dsp.const496 = (2.0) * ((7.621731298870603) - (dsp.const469))
        dsp.const497 = (1.0) / ((((dsp.const465) + (0.168404871113589)) / (dsp.const464)) + (1.069358407707312))
        dsp.const498 = (((dsp.const465) + (-0.168404871113589)) / (dsp.const464)) + (1.069358407707312)
        dsp.const499 = (2.0) * ((1.069358407707312) - (dsp.const469))
        dsp.const500 = (dsp.const469) + (53.53615295455673)
        dsp.const501 = (2.0) * ((53.53615295455673) - (dsp.const469))
        dsp.const502 = tan((123.69245982665232) / (dsp.const0))
        dsp.const503 = (1.0) / (dsp.const502)
        dsp.const504 = (1.0) / ((((dsp.const503) + (3.1897274020965583)) / (dsp.const502)) + (4.076781969643807))
        dsp.const505 = (((dsp.const503) + (-3.1897274020965583)) / (dsp.const502)) + (4.076781969643807)
        dsp.const506 = pow_unrolled[2](dsp.const502)
        dsp.const507 = (1.0) / (dsp.const506)
        dsp.const508 = (2.0) * ((4.076781969643807) - (dsp.const507))
        dsp.const509 = (0.0017661728399818856) / (dsp.const506)
        dsp.const510 = (dsp.const509) + (0.00040767818495825777)
        dsp.const511 = (2.0) * ((0.00040767818495825777) - (dsp.const509))
        dsp.const512 = (1.0) / ((((dsp.const503) + (0.7431304601070396)) / (dsp.const502)) + (1.450071084655647))
        dsp.const513 = (((dsp.const503) + (-0.7431304601070396)) / (dsp.const502)) + (1.450071084655647)
        dsp.const514 = (2.0) * ((1.450071084655647) - (dsp.const507))
        dsp.const515 = (11.052052171507189) / (dsp.const506)
        dsp.const516 = (dsp.const515) + (1.450071084655647)
        dsp.const517 = (2.0) * ((1.450071084655647) - (dsp.const515))
        dsp.const518 = (1.0) / ((((dsp.const503) + (0.157482159302087)) / (dsp.const502)) + (0.9351401670315425))
        dsp.const519 = (((dsp.const503) + (-0.157482159302087)) / (dsp.const502)) + (0.9351401670315425)
        dsp.const520 = (2.0) * ((0.9351401670315425) - (dsp.const507))
        dsp.const521 = (50.063807016150385) / (dsp.const506)
        dsp.const522 = (dsp.const521) + (0.9351401670315425)
        dsp.const523 = (2.0) * ((0.9351401670315425) - (dsp.const521))
        dsp.const524 = (1.0) / ((((dsp.const503) + (0.782413046821645)) / (dsp.const502)) + (0.24529150870616))
        dsp.const525 = (((dsp.const503) + (-0.782413046821645)) / (dsp.const502)) + (0.24529150870616)
        dsp.const526 = (2.0) * ((0.24529150870616) - (dsp.const507))
        dsp.const527 = (9.9999997055e-05) / (dsp.const506)
        dsp.const528 = (dsp.const527) + (0.000433227200555)
        dsp.const529 = (2.0) * ((0.000433227200555) - (dsp.const527))
        dsp.const530 = (1.0) / ((((dsp.const503) + (0.512478641889141)) / (dsp.const502)) + (0.689621364484675))
        dsp.const531 = (((dsp.const503) + (-0.512478641889141)) / (dsp.const502)) + (0.689621364484675)
        dsp.const532 = (2.0) * ((0.689621364484675) - (dsp.const507))
        dsp.const533 = (dsp.const507) + (7.621731298870603)
        dsp.const534 = (2.0) * ((7.621731298870603) - (dsp.const507))
        dsp.const535 = (1.0) / ((((dsp.const503) + (0.168404871113589)) / (dsp.const502)) + (1.069358407707312))
        dsp.const536 = (((dsp.const503) + (-0.168404871113589)) / (dsp.const502)) + (1.069358407707312)
        dsp.const537 = (2.0) * ((1.069358407707312) - (dsp.const507))
        dsp.const538 = (dsp.const507) + (53.53615295455673)
        dsp.const539 = (2.0) * ((53.53615295455673) - (dsp.const507))

    @always_inline
    def instance_reset_user_interface(mut dsp) -> None:
        dsp.vslider0 = -20.0
        dsp.vslider1 = 0.1
        dsp.vslider2 = 49.0
        dsp.vslider3 = -0.1
        dsp.vslider4 = 0.1
        dsp.hslider0 = 0.5
        dsp.hslider1 = 0.0
        dsp.hslider2 = 0.0
        dsp.checkbox0 = 0.0
        dsp.checkbox1 = 0.0
        dsp.checkbox2 = 0.0
        dsp.entry0 = 2.0
        dsp.checkbox3 = 0.0
        dsp.hslider3 = 1.0
        dsp.hslider4 = 10.0
        dsp.hslider5 = 0.5
        dsp.hslider6 = 0.0
        dsp.checkbox4 = 0.0
        dsp.checkbox5 = 0.0
        dsp.hslider7 = 1.0
        dsp.hslider8 = 0.0
        dsp.hslider9 = 1000.0
        dsp.hslider10 = 1.5
        dsp.hslider11 = 100.0
        dsp.hslider12 = 800.0
        dsp.checkbox6 = 0.0
        dsp.hslider13 = 1.0
        dsp.checkbox7 = 0.0
        dsp.hslider14 = 100.0
        dsp.hslider15 = 50.0

    @always_inline
    def instance_clear(mut dsp) -> None:
        var l0 = S32(0)
        while (l0) < (S32(4)): 
            dsp.rec0_perm[l0] = 0.0
            l0 = (l0) + (S32(1))
        var l1 = S32(0)
        while (l1) < (S32(4)): 
            dsp.rec2_perm[l1] = 0.0
            l1 = (l1) + (S32(1))
        var l2 = S32(0)
        while (l2) < (S32(4)): 
            dsp.rec1_perm[l2] = 0.0
            l2 = (l2) + (S32(1))
        var l3 = S32(0)
        while (l3) < (S32(4)): 
            dsp.rec3_perm[l3] = 0.0
            l3 = (l3) + (S32(1))
        var l4 = S32(0)
        while (l4) < (S32(4)): 
            dsp.rec4_perm[l4] = 0.0
            l4 = (l4) + (S32(1))
        var l5 = S32(0)
        while (l5) < (S32(4)): 
            dsp.i_rec5_perm[l5] = S32(0)
            l5 = (l5) + (S32(1))
        var l6 = S32(0)
        while (l6) < (S32(4)): 
            dsp.rec6_perm[l6] = 0.0
            l6 = (l6) + (S32(1))
        var l7 = S32(0)
        while (l7) < (S32(4)): 
            dsp.rec7_perm[l7] = 0.0
            l7 = (l7) + (S32(1))
        var l8 = S32(0)
        while (l8) < (S32(4)): 
            dsp.i_vec0_perm[l8] = S32(0)
            l8 = (l8) + (S32(1))
        var l9 = S32(0)
        while (l9) < (S32(4)): 
            dsp.rec8_perm[l9] = 0.0
            l9 = (l9) + (S32(1))
        var l10 = S32(0)
        while (l10) < (S32(4)): 
            dsp.yec0_perm[l10] = 0.0
            l10 = (l10) + (S32(1))
        var l11 = S32(0)
        while (l11) < (S32(4)): 
            dsp.yec1_perm[l11] = 0.0
            l11 = (l11) + (S32(1))
        var l12 = S32(0)
        while (l12) < (S32(4)): 
            dsp.yec2_perm[l12] = 0.0
            l12 = (l12) + (S32(1))
        var l13 = S32(0)
        while (l13) < (S32(4)): 
            dsp.yec3_perm[l13] = 0.0
            l13 = (l13) + (S32(1))
        var l14 = S32(0)
        while (l14) < (S32(4)): 
            dsp.yec4_perm[l14] = 0.0
            l14 = (l14) + (S32(1))
        var l15 = S32(0)
        while (l15) < (S32(4)): 
            dsp.yec5_perm[l15] = 0.0
            l15 = (l15) + (S32(1))
        var l16 = S32(0)
        while (l16) < (S32(4)): 
            dsp.yec6_perm[l16] = 0.0
            l16 = (l16) + (S32(1))
        var l17 = S32(0)
        while (l17) < (S32(4)): 
            dsp.yec7_perm[l17] = 0.0
            l17 = (l17) + (S32(1))
        var l18 = S32(0)
        while (l18) < (S32(4)): 
            dsp.yec8_perm[l18] = 0.0
            l18 = (l18) + (S32(1))
        var l19 = S32(0)
        while (l19) < (S32(4)): 
            dsp.yec9_perm[l19] = 0.0
            l19 = (l19) + (S32(1))
        var l20 = S32(0)
        while (l20) < (S32(4)): 
            dsp.yec10_perm[l20] = 0.0
            l20 = (l20) + (S32(1))
        var l21 = S32(0)
        while (l21) < (S32(4)): 
            dsp.yec11_perm[l21] = 0.0
            l21 = (l21) + (S32(1))
        var l22 = S32(0)
        while (l22) < (S32(4)): 
            dsp.yec12_perm[l22] = 0.0
            l22 = (l22) + (S32(1))
        var l23 = S32(0)
        while (l23) < (S32(4)): 
            dsp.yec13_perm[l23] = 0.0
            l23 = (l23) + (S32(1))
        var l24 = S32(0)
        while (l24) < (S32(4)): 
            dsp.yec14_perm[l24] = 0.0
            l24 = (l24) + (S32(1))
        var l25 = S32(0)
        while (l25) < (S32(4)): 
            dsp.yec15_perm[l25] = 0.0
            l25 = (l25) + (S32(1))
        var l26 = S32(0)
        while (l26) < (S32(4)): 
            dsp.yec16_perm[l26] = 0.0
            l26 = (l26) + (S32(1))
        var l27 = S32(0)
        while (l27) < (S32(4)): 
            dsp.yec17_perm[l27] = 0.0
            l27 = (l27) + (S32(1))
        var l28 = S32(0)
        while (l28) < (S32(4096)): 
            dsp.yec18[l28] = 0.0
            l28 = (l28) + (S32(1))
        dsp.yec18_idx = S32(0)
        dsp.yec18_idx_save = S32(0)
        var l29 = S32(0)
        while (l29) < (S32(4)): 
            dsp.rec9_perm[l29] = 0.0
            l29 = (l29) + (S32(1))
        var l30 = S32(0)
        while (l30) < (S32(4)): 
            dsp.rec15_perm[l30] = 0.0
            l30 = (l30) + (S32(1))
        var l31 = S32(0)
        while (l31) < (S32(4)): 
            dsp.rec16_perm[l31] = 0.0
            l31 = (l31) + (S32(1))
        var l32 = S32(0)
        while (l32) < (S32(4)): 
            dsp.rec14_perm[l32] = 0.0
            l32 = (l32) + (S32(1))
        var l33 = S32(0)
        while (l33) < (S32(4)): 
            dsp.rec13_perm[l33] = 0.0
            l33 = (l33) + (S32(1))
        var l34 = S32(0)
        while (l34) < (S32(4)): 
            dsp.rec12_perm[l34] = 0.0
            l34 = (l34) + (S32(1))
        var l35 = S32(0)
        while (l35) < (S32(4)): 
            dsp.rec11_perm[l35] = 0.0
            l35 = (l35) + (S32(1))
        var l36 = S32(0)
        while (l36) < (S32(4)): 
            dsp.rec10_perm[l36] = 0.0
            l36 = (l36) + (S32(1))
        var l37 = S32(0)
        while (l37) < (S32(4096)): 
            dsp.yec19[l37] = 0.0
            l37 = (l37) + (S32(1))
        dsp.yec19_idx = S32(0)
        dsp.yec19_idx_save = S32(0)
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
            dsp.rec19_perm[l42] = 0.0
            l42 = (l42) + (S32(1))
        var l43 = S32(0)
        while (l43) < (S32(4)): 
            dsp.rec18_perm[l43] = 0.0
            l43 = (l43) + (S32(1))
        var l44 = S32(0)
        while (l44) < (S32(4)): 
            dsp.rec26_perm[l44] = 0.0
            l44 = (l44) + (S32(1))
        var l45 = S32(0)
        while (l45) < (S32(4)): 
            dsp.rec25_perm[l45] = 0.0
            l45 = (l45) + (S32(1))
        var l46 = S32(0)
        while (l46) < (S32(4)): 
            dsp.rec24_perm[l46] = 0.0
            l46 = (l46) + (S32(1))
        var l47 = S32(0)
        while (l47) < (S32(4)): 
            dsp.rec23_perm[l47] = 0.0
            l47 = (l47) + (S32(1))
        var l48 = S32(0)
        while (l48) < (S32(4)): 
            dsp.rec33_perm[l48] = 0.0
            l48 = (l48) + (S32(1))
        var l49 = S32(0)
        while (l49) < (S32(4)): 
            dsp.rec32_perm[l49] = 0.0
            l49 = (l49) + (S32(1))
        var l50 = S32(0)
        while (l50) < (S32(4)): 
            dsp.rec31_perm[l50] = 0.0
            l50 = (l50) + (S32(1))
        var l51 = S32(0)
        while (l51) < (S32(4)): 
            dsp.rec30_perm[l51] = 0.0
            l51 = (l51) + (S32(1))
        var l52 = S32(0)
        while (l52) < (S32(4)): 
            dsp.rec29_perm[l52] = 0.0
            l52 = (l52) + (S32(1))
        var l53 = S32(0)
        while (l53) < (S32(4)): 
            dsp.rec28_perm[l53] = 0.0
            l53 = (l53) + (S32(1))
        var l54 = S32(0)
        while (l54) < (S32(4)): 
            dsp.rec27_perm[l54] = 0.0
            l54 = (l54) + (S32(1))
        var l55 = S32(0)
        while (l55) < (S32(4)): 
            dsp.rec40_perm[l55] = 0.0
            l55 = (l55) + (S32(1))
        var l56 = S32(0)
        while (l56) < (S32(4)): 
            dsp.rec39_perm[l56] = 0.0
            l56 = (l56) + (S32(1))
        var l57 = S32(0)
        while (l57) < (S32(4)): 
            dsp.rec38_perm[l57] = 0.0
            l57 = (l57) + (S32(1))
        var l58 = S32(0)
        while (l58) < (S32(4)): 
            dsp.rec37_perm[l58] = 0.0
            l58 = (l58) + (S32(1))
        var l59 = S32(0)
        while (l59) < (S32(4)): 
            dsp.rec36_perm[l59] = 0.0
            l59 = (l59) + (S32(1))
        var l60 = S32(0)
        while (l60) < (S32(4)): 
            dsp.rec35_perm[l60] = 0.0
            l60 = (l60) + (S32(1))
        var l61 = S32(0)
        while (l61) < (S32(4)): 
            dsp.rec34_perm[l61] = 0.0
            l61 = (l61) + (S32(1))
        var l62 = S32(0)
        while (l62) < (S32(4)): 
            dsp.rec47_perm[l62] = 0.0
            l62 = (l62) + (S32(1))
        var l63 = S32(0)
        while (l63) < (S32(4)): 
            dsp.rec46_perm[l63] = 0.0
            l63 = (l63) + (S32(1))
        var l64 = S32(0)
        while (l64) < (S32(4)): 
            dsp.rec45_perm[l64] = 0.0
            l64 = (l64) + (S32(1))
        var l65 = S32(0)
        while (l65) < (S32(4)): 
            dsp.rec44_perm[l65] = 0.0
            l65 = (l65) + (S32(1))
        var l66 = S32(0)
        while (l66) < (S32(4)): 
            dsp.rec43_perm[l66] = 0.0
            l66 = (l66) + (S32(1))
        var l67 = S32(0)
        while (l67) < (S32(4)): 
            dsp.rec42_perm[l67] = 0.0
            l67 = (l67) + (S32(1))
        var l68 = S32(0)
        while (l68) < (S32(4)): 
            dsp.rec41_perm[l68] = 0.0
            l68 = (l68) + (S32(1))
        var l69 = S32(0)
        while (l69) < (S32(4)): 
            dsp.rec54_perm[l69] = 0.0
            l69 = (l69) + (S32(1))
        var l70 = S32(0)
        while (l70) < (S32(4)): 
            dsp.rec53_perm[l70] = 0.0
            l70 = (l70) + (S32(1))
        var l71 = S32(0)
        while (l71) < (S32(4)): 
            dsp.rec52_perm[l71] = 0.0
            l71 = (l71) + (S32(1))
        var l72 = S32(0)
        while (l72) < (S32(4)): 
            dsp.rec51_perm[l72] = 0.0
            l72 = (l72) + (S32(1))
        var l73 = S32(0)
        while (l73) < (S32(4)): 
            dsp.rec50_perm[l73] = 0.0
            l73 = (l73) + (S32(1))
        var l74 = S32(0)
        while (l74) < (S32(4)): 
            dsp.rec49_perm[l74] = 0.0
            l74 = (l74) + (S32(1))
        var l75 = S32(0)
        while (l75) < (S32(4)): 
            dsp.rec48_perm[l75] = 0.0
            l75 = (l75) + (S32(1))
        var l76 = S32(0)
        while (l76) < (S32(4)): 
            dsp.rec61_perm[l76] = 0.0
            l76 = (l76) + (S32(1))
        var l77 = S32(0)
        while (l77) < (S32(4)): 
            dsp.rec60_perm[l77] = 0.0
            l77 = (l77) + (S32(1))
        var l78 = S32(0)
        while (l78) < (S32(4)): 
            dsp.rec59_perm[l78] = 0.0
            l78 = (l78) + (S32(1))
        var l79 = S32(0)
        while (l79) < (S32(4)): 
            dsp.rec58_perm[l79] = 0.0
            l79 = (l79) + (S32(1))
        var l80 = S32(0)
        while (l80) < (S32(4)): 
            dsp.rec57_perm[l80] = 0.0
            l80 = (l80) + (S32(1))
        var l81 = S32(0)
        while (l81) < (S32(4)): 
            dsp.rec56_perm[l81] = 0.0
            l81 = (l81) + (S32(1))
        var l82 = S32(0)
        while (l82) < (S32(4)): 
            dsp.rec55_perm[l82] = 0.0
            l82 = (l82) + (S32(1))
        var l83 = S32(0)
        while (l83) < (S32(4)): 
            dsp.rec68_perm[l83] = 0.0
            l83 = (l83) + (S32(1))
        var l84 = S32(0)
        while (l84) < (S32(4)): 
            dsp.rec67_perm[l84] = 0.0
            l84 = (l84) + (S32(1))
        var l85 = S32(0)
        while (l85) < (S32(4)): 
            dsp.rec66_perm[l85] = 0.0
            l85 = (l85) + (S32(1))
        var l86 = S32(0)
        while (l86) < (S32(4)): 
            dsp.rec65_perm[l86] = 0.0
            l86 = (l86) + (S32(1))
        var l87 = S32(0)
        while (l87) < (S32(4)): 
            dsp.rec64_perm[l87] = 0.0
            l87 = (l87) + (S32(1))
        var l88 = S32(0)
        while (l88) < (S32(4)): 
            dsp.rec63_perm[l88] = 0.0
            l88 = (l88) + (S32(1))
        var l89 = S32(0)
        while (l89) < (S32(4)): 
            dsp.rec62_perm[l89] = 0.0
            l89 = (l89) + (S32(1))
        var l90 = S32(0)
        while (l90) < (S32(4)): 
            dsp.rec75_perm[l90] = 0.0
            l90 = (l90) + (S32(1))
        var l91 = S32(0)
        while (l91) < (S32(4)): 
            dsp.rec74_perm[l91] = 0.0
            l91 = (l91) + (S32(1))
        var l92 = S32(0)
        while (l92) < (S32(4)): 
            dsp.rec73_perm[l92] = 0.0
            l92 = (l92) + (S32(1))
        var l93 = S32(0)
        while (l93) < (S32(4)): 
            dsp.rec72_perm[l93] = 0.0
            l93 = (l93) + (S32(1))
        var l94 = S32(0)
        while (l94) < (S32(4)): 
            dsp.rec71_perm[l94] = 0.0
            l94 = (l94) + (S32(1))
        var l95 = S32(0)
        while (l95) < (S32(4)): 
            dsp.rec70_perm[l95] = 0.0
            l95 = (l95) + (S32(1))
        var l96 = S32(0)
        while (l96) < (S32(4)): 
            dsp.rec69_perm[l96] = 0.0
            l96 = (l96) + (S32(1))
        var l97 = S32(0)
        while (l97) < (S32(4)): 
            dsp.rec82_perm[l97] = 0.0
            l97 = (l97) + (S32(1))
        var l98 = S32(0)
        while (l98) < (S32(4)): 
            dsp.rec81_perm[l98] = 0.0
            l98 = (l98) + (S32(1))
        var l99 = S32(0)
        while (l99) < (S32(4)): 
            dsp.rec80_perm[l99] = 0.0
            l99 = (l99) + (S32(1))
        var l100 = S32(0)
        while (l100) < (S32(4)): 
            dsp.rec79_perm[l100] = 0.0
            l100 = (l100) + (S32(1))
        var l101 = S32(0)
        while (l101) < (S32(4)): 
            dsp.rec78_perm[l101] = 0.0
            l101 = (l101) + (S32(1))
        var l102 = S32(0)
        while (l102) < (S32(4)): 
            dsp.rec77_perm[l102] = 0.0
            l102 = (l102) + (S32(1))
        var l103 = S32(0)
        while (l103) < (S32(4)): 
            dsp.rec76_perm[l103] = 0.0
            l103 = (l103) + (S32(1))
        var l104 = S32(0)
        while (l104) < (S32(4)): 
            dsp.rec89_perm[l104] = 0.0
            l104 = (l104) + (S32(1))
        var l105 = S32(0)
        while (l105) < (S32(4)): 
            dsp.rec88_perm[l105] = 0.0
            l105 = (l105) + (S32(1))
        var l106 = S32(0)
        while (l106) < (S32(4)): 
            dsp.rec87_perm[l106] = 0.0
            l106 = (l106) + (S32(1))
        var l107 = S32(0)
        while (l107) < (S32(4)): 
            dsp.rec86_perm[l107] = 0.0
            l107 = (l107) + (S32(1))
        var l108 = S32(0)
        while (l108) < (S32(4)): 
            dsp.rec85_perm[l108] = 0.0
            l108 = (l108) + (S32(1))
        var l109 = S32(0)
        while (l109) < (S32(4)): 
            dsp.rec84_perm[l109] = 0.0
            l109 = (l109) + (S32(1))
        var l110 = S32(0)
        while (l110) < (S32(4)): 
            dsp.rec83_perm[l110] = 0.0
            l110 = (l110) + (S32(1))
        var l111 = S32(0)
        while (l111) < (S32(4)): 
            dsp.rec96_perm[l111] = 0.0
            l111 = (l111) + (S32(1))
        var l112 = S32(0)
        while (l112) < (S32(4)): 
            dsp.rec95_perm[l112] = 0.0
            l112 = (l112) + (S32(1))
        var l113 = S32(0)
        while (l113) < (S32(4)): 
            dsp.rec94_perm[l113] = 0.0
            l113 = (l113) + (S32(1))
        var l114 = S32(0)
        while (l114) < (S32(4)): 
            dsp.rec93_perm[l114] = 0.0
            l114 = (l114) + (S32(1))
        var l115 = S32(0)
        while (l115) < (S32(4)): 
            dsp.rec92_perm[l115] = 0.0
            l115 = (l115) + (S32(1))
        var l116 = S32(0)
        while (l116) < (S32(4)): 
            dsp.rec91_perm[l116] = 0.0
            l116 = (l116) + (S32(1))
        var l117 = S32(0)
        while (l117) < (S32(4)): 
            dsp.rec90_perm[l117] = 0.0
            l117 = (l117) + (S32(1))
        var l118 = S32(0)
        while (l118) < (S32(4)): 
            dsp.rec103_perm[l118] = 0.0
            l118 = (l118) + (S32(1))
        var l119 = S32(0)
        while (l119) < (S32(4)): 
            dsp.rec102_perm[l119] = 0.0
            l119 = (l119) + (S32(1))
        var l120 = S32(0)
        while (l120) < (S32(4)): 
            dsp.rec101_perm[l120] = 0.0
            l120 = (l120) + (S32(1))
        var l121 = S32(0)
        while (l121) < (S32(4)): 
            dsp.rec100_perm[l121] = 0.0
            l121 = (l121) + (S32(1))
        var l122 = S32(0)
        while (l122) < (S32(4)): 
            dsp.rec99_perm[l122] = 0.0
            l122 = (l122) + (S32(1))
        var l123 = S32(0)
        while (l123) < (S32(4)): 
            dsp.rec98_perm[l123] = 0.0
            l123 = (l123) + (S32(1))
        var l124 = S32(0)
        while (l124) < (S32(4)): 
            dsp.rec97_perm[l124] = 0.0
            l124 = (l124) + (S32(1))
        var l125 = S32(0)
        while (l125) < (S32(4)): 
            dsp.rec110_perm[l125] = 0.0
            l125 = (l125) + (S32(1))
        var l126 = S32(0)
        while (l126) < (S32(4)): 
            dsp.rec109_perm[l126] = 0.0
            l126 = (l126) + (S32(1))
        var l127 = S32(0)
        while (l127) < (S32(4)): 
            dsp.rec108_perm[l127] = 0.0
            l127 = (l127) + (S32(1))
        var l128 = S32(0)
        while (l128) < (S32(4)): 
            dsp.rec107_perm[l128] = 0.0
            l128 = (l128) + (S32(1))
        var l129 = S32(0)
        while (l129) < (S32(4)): 
            dsp.rec106_perm[l129] = 0.0
            l129 = (l129) + (S32(1))
        var l130 = S32(0)
        while (l130) < (S32(4)): 
            dsp.rec105_perm[l130] = 0.0
            l130 = (l130) + (S32(1))
        var l131 = S32(0)
        while (l131) < (S32(4)): 
            dsp.rec104_perm[l131] = 0.0
            l131 = (l131) + (S32(1))
        var l132 = S32(0)
        while (l132) < (S32(4)): 
            dsp.rec117_perm[l132] = 0.0
            l132 = (l132) + (S32(1))
        var l133 = S32(0)
        while (l133) < (S32(4)): 
            dsp.rec116_perm[l133] = 0.0
            l133 = (l133) + (S32(1))
        var l134 = S32(0)
        while (l134) < (S32(4)): 
            dsp.rec115_perm[l134] = 0.0
            l134 = (l134) + (S32(1))
        var l135 = S32(0)
        while (l135) < (S32(4)): 
            dsp.rec114_perm[l135] = 0.0
            l135 = (l135) + (S32(1))
        var l136 = S32(0)
        while (l136) < (S32(4)): 
            dsp.rec113_perm[l136] = 0.0
            l136 = (l136) + (S32(1))
        var l137 = S32(0)
        while (l137) < (S32(4)): 
            dsp.rec112_perm[l137] = 0.0
            l137 = (l137) + (S32(1))
        var l138 = S32(0)
        while (l138) < (S32(4)): 
            dsp.rec111_perm[l138] = 0.0
            l138 = (l138) + (S32(1))
        var l139 = S32(0)
        while (l139) < (S32(4)): 
            dsp.rec121_perm[l139] = 0.0
            l139 = (l139) + (S32(1))
        var l140 = S32(0)
        while (l140) < (S32(4)): 
            dsp.rec120_perm[l140] = 0.0
            l140 = (l140) + (S32(1))
        var l141 = S32(0)
        while (l141) < (S32(4)): 
            dsp.rec119_perm[l141] = 0.0
            l141 = (l141) + (S32(1))
        var l142 = S32(0)
        while (l142) < (S32(4)): 
            dsp.rec118_perm[l142] = 0.0
            l142 = (l142) + (S32(1))

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
        return "{\"name\": \"phaser_flanger\",\"filename\": \"phaser_flanger.dsp\",\"version\": \"2.87.10\",\"compile_options\": \"-a /Users/manuelfarzini/Personal/dev/repo/faust/architecture/mojo/impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs\",\"library_list\": [\"/Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/dsp/oscillator.lib\",\"/Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/dsp/music.lib\",\"/Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/dsp/math.lib\",\"/Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/dsp/filter.lib\",\"/Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/dsp/effect.lib\"],\"include_pathnames\": [\"/Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/dsp\",\"/Users/manuelfarzini/Personal/dev/repo/faust/build/share/faust\",\"/Users/manuelfarzini/Personal/dev/repo/faust/build/bin//share/faust\",\"/usr/local/share/faust\",\"/usr/share/faust\",\"/Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/dsp\",\"/Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/dsp\"],\"size\": 74724,\"inputs\": 1,\"outputs\": 2,\"meta\": [ { \"compile_options\": \"-a /Users/manuelfarzini/Personal/dev/repo/faust/architecture/mojo/impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs\" },{ \"effect.lib/bypass2:author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"effect.lib/bypass2:copyright\": \"Julius O. Smith III\" },{ \"effect.lib/bypass2:license\": \"STK-4.3\" },{ \"effect.lib/cross2:author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"effect.lib/cross2:copyright\": \"Julius O. Smith III\" },{ \"effect.lib/cross2:license\": \"STK-4.3\" },{ \"effect.lib/flanger_demo:author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"effect.lib/flanger_demo:copyright\": \"Julius O. Smith III\" },{ \"effect.lib/flanger_demo:license\": \"STK-4.3\" },{ \"effect.lib/flanger_mono:author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"effect.lib/flanger_mono:copyright\": \"Julius O. Smith III\" },{ \"effect.lib/flanger_mono:license\": \"STK-4.3\" },{ \"effect.lib/flanger_stereo:author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"effect.lib/flanger_stereo:copyright\": \"Julius O. Smith III\" },{ \"effect.lib/flanger_stereo:license\": \"STK-4.3\" },{ \"effect.lib/name\": \"Faust Audio Effect Library\" },{ \"effect.lib/phaser2_demo:author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"effect.lib/phaser2_demo:copyright\": \"Julius O. Smith III\" },{ \"effect.lib/phaser2_demo:license\": \"STK-4.3\" },{ \"effect.lib/phaser2_mono:author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"effect.lib/phaser2_mono:copyright\": \"Julius O. Smith III\" },{ \"effect.lib/phaser2_mono:license\": \"STK-4.3\" },{ \"effect.lib/phaser2_stereo:author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"effect.lib/phaser2_stereo:copyright\": \"Julius O. Smith III\" },{ \"effect.lib/phaser2_stereo:license\": \"STK-4.3\" },{ \"effect.lib/select2stereo:author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"effect.lib/select2stereo:copyright\": \"Julius O. Smith III\" },{ \"effect.lib/select2stereo:license\": \"STK-4.3\" },{ \"effect.lib/vibrato2_mono:author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"effect.lib/vibrato2_mono:copyright\": \"Julius O. Smith III\" },{ \"effect.lib/vibrato2_mono:license\": \"STK-4.3\" },{ \"filename\": \"phaser_flanger.dsp\" },{ \"filter.lib/author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"filter.lib/copyright\": \"Julius O. Smith III\" },{ \"filter.lib/license\": \"STK-4.3\" },{ \"filter.lib/name\": \"Faust Filter Library\" },{ \"filter.lib/reference\": \"https://ccrma.stanford.edu/~jos/filters/\" },{ \"filter.lib/version\": \"1.29\" },{ \"math.lib/author\": \"GRAME\" },{ \"math.lib/copyright\": \"GRAME\" },{ \"math.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"math.lib/license\": \"LGPL with exception\" },{ \"math.lib/name\": \"Math Library\" },{ \"math.lib/version\": \"1.0\" },{ \"music.lib/author\": \"GRAME\" },{ \"music.lib/copyright\": \"GRAME\" },{ \"music.lib/license\": \"LGPL with exception\" },{ \"music.lib/name\": \"Music Library\" },{ \"music.lib/version\": \"1.0\" },{ \"name\": \"phaser_flanger\" },{ \"oscillator.lib/author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"oscillator.lib/copyright\": \"Julius O. Smith III\" },{ \"oscillator.lib/license\": \"STK-4.3\" },{ \"oscillator.lib/name\": \"Faust Oscillator Library\" },{ \"oscillator.lib/version\": \"1.11\" }],\"ui\": [ {\"type\": \"vgroup\",\"label\": \"phaser_flanger\",\"items\": [ {\"type\": \"vgroup\",\"label\": \"0x00\",\"meta\": [{ \"1\": \"\" }],\"items\": [ {\"type\": \"vgroup\",\"label\": \"SAWTOOTH OSCILLATOR\",\"meta\": [{ \"0\": \"\" },{ \"tooltip\": \"See Faust\'s oscillator.lib for documentation and references\" }],\"items\": [ {\"type\": \"hgroup\",\"label\": \"0x00\",\"meta\": [{ \"1\": \"\" }],\"items\": [ {\"type\": \"vslider\",\"label\": \"Amplitude\",\"varname\": \"fVslider0\",\"shortname\": \"Amplitude\",\"address\": \"/phaser_flanger/0x00/SAWTOOTH_OSCILLATOR/0x00/Amplitude\",\"meta\": [{ \"1\": \"\" },{ \"style\": \"knob\" },{ \"tooltip\": \"Sawtooth waveform amplitude\" },{ \"unit\": \"dB\" }],\"init\": -20,\"min\": -120,\"max\": 10,\"step\": 0.1},{\"type\": \"vslider\",\"label\": \"Frequency\",\"varname\": \"fVslider2\",\"shortname\": \"Frequency\",\"address\": \"/phaser_flanger/0x00/SAWTOOTH_OSCILLATOR/0x00/Frequency\",\"meta\": [{ \"2\": \"\" },{ \"style\": \"knob\" },{ \"tooltip\": \"Sawtooth frequency as a Piano Key (PK) number (A440 = key 49)\" },{ \"unit\": \"PK\" }],\"init\": 49,\"min\": 1,\"max\": 88,\"step\": 0.01},{\"type\": \"vslider\",\"label\": \"Detuning 1\",\"varname\": \"fVslider3\",\"shortname\": \"Detuning_1\",\"address\": \"/phaser_flanger/0x00/SAWTOOTH_OSCILLATOR/0x00/Detuning_1\",\"meta\": [{ \"3\": \"\" },{ \"style\": \"knob\" },{ \"tooltip\": \"Percentage frequency-shift up or down for second oscillator\" },{ \"unit\": \"%%\" }],\"init\": -0.1,\"min\": -10,\"max\": 10,\"step\": 0.01},{\"type\": \"vslider\",\"label\": \"Detuning 2\",\"varname\": \"fVslider4\",\"shortname\": \"Detuning_2\",\"address\": \"/phaser_flanger/0x00/SAWTOOTH_OSCILLATOR/0x00/Detuning_2\",\"meta\": [{ \"4\": \"\" },{ \"style\": \"knob\" },{ \"tooltip\": \"Percentage frequency-shift up or down for third detuned oscillator\" },{ \"unit\": \"%%\" }],\"init\": 0.1,\"min\": -10,\"max\": 10,\"step\": 0.01},{\"type\": \"vslider\",\"label\": \"Portamento\",\"varname\": \"fVslider1\",\"shortname\": \"Portamento\",\"address\": \"/phaser_flanger/0x00/SAWTOOTH_OSCILLATOR/0x00/Portamento\",\"meta\": [{ \"5\": \"\" },{ \"scale\": \"log\" },{ \"style\": \"knob\" },{ \"tooltip\": \"Portamento (frequency-glide) time-constant in seconds\" },{ \"unit\": \"sec\" }],\"init\": 0.1,\"min\": 0.001,\"max\": 10,\"step\": 0.001},{\"type\": \"nentry\",\"label\": \"Saw Order\",\"varname\": \"fEntry0\",\"shortname\": \"Saw_Order\",\"address\": \"/phaser_flanger/0x00/SAWTOOTH_OSCILLATOR/0x00/Saw_Order\",\"meta\": [{ \"6\": \"\" },{ \"tooltip\": \"Order of sawtootn aliasing suppression\" }],\"init\": 2,\"min\": 1,\"max\": 4,\"step\": 1},{\"type\": \"vgroup\",\"label\": \"Alternate Signals\",\"meta\": [{ \"7\": \"\" }],\"items\": [ {\"type\": \"checkbox\",\"label\": \"Noise (White or Pink - uses only Amplitude control on the left)\",\"varname\": \"fCheckbox2\",\"shortname\": \"Noise_White_or_Pink_uses_only_Amplitude_control_on_the_left\",\"address\": \"/phaser_flanger/0x00/SAWTOOTH_OSCILLATOR/0x00/Alternate_Signals/Noise__White_or_Pink_-_uses_only_Amplitude_control_on_the_left_\",\"meta\": [{ \"0\": \"\" }]},{\"type\": \"checkbox\",\"label\": \"Pink instead of White Noise (also called 1/f Noise)\",\"varname\": \"fCheckbox3\",\"shortname\": \"Pink_instead_of_White_Noise_also_called_1_f_Noise\",\"address\": \"/phaser_flanger/0x00/SAWTOOTH_OSCILLATOR/0x00/Alternate_Signals/Pink_instead_of_White_Noise__also_called_1_f_Noise_\",\"meta\": [{ \"1\": \"\" },{ \"tooltip\": \"Pink Noise (or 1/f noise) is Constant-Q Noise, meaning that it has the same total power in every octave\" }]},{\"type\": \"checkbox\",\"label\": \"External Signal Input (overrides Sawtooth/Noise selection above)\",\"varname\": \"fCheckbox1\",\"shortname\": \"External_Signal_Input_overrides_Sawtooth_Noise_selection_above\",\"address\": \"/phaser_flanger/0x00/SAWTOOTH_OSCILLATOR/0x00/Alternate_Signals/External_Signal_Input__overrides_Sawtooth_Noise_selection_above_\",\"meta\": [{ \"2\": \"\" }]}]}]}]}]},{\"type\": \"vgroup\",\"label\": \"0x00\",\"meta\": [{ \"2\": \"\" }],\"items\": [ {\"type\": \"vgroup\",\"label\": \"FLANGER\",\"meta\": [{ \"tooltip\": \"Reference: https://ccrma.stanford.edu/~jos/pasp/Flanging.html\" }],\"items\": [ {\"type\": \"hgroup\",\"label\": \"0x00\",\"meta\": [{ \"0\": \"\" }],\"items\": [ {\"type\": \"checkbox\",\"label\": \"Bypass\",\"varname\": \"fCheckbox0\",\"shortname\": \"FLANGER_Bypass\",\"address\": \"/phaser_flanger/0x00/FLANGER/0x00/Bypass\",\"meta\": [{ \"0\": \"\" },{ \"tooltip\": \"When this is checked, the flanger has no effect\" }]},{\"type\": \"checkbox\",\"label\": \"Invert Flange Sum\",\"varname\": \"fCheckbox5\",\"shortname\": \"Invert_Flange_Sum\",\"address\": \"/phaser_flanger/0x00/FLANGER/0x00/Invert_Flange_Sum\",\"meta\": [{ \"1\": \"\" }]},{\"type\": \"hbargraph\",\"label\": \"Flange LFO\",\"varname\": \"fHbargraph0\",\"shortname\": \"Flange_LFO\",\"address\": \"/phaser_flanger/0x00/FLANGER/0x00/Flange_LFO\",\"meta\": [{ \"2\": \"\" },{ \"style\": \"led\" },{ \"tooltip\": \"Display sum of flange delays\" }],\"min\": -1.5,\"max\": 1.5}]},{\"type\": \"hgroup\",\"label\": \"0x00\",\"meta\": [{ \"1\": \"\" }],\"items\": [ {\"type\": \"hslider\",\"label\": \"Speed\",\"varname\": \"fHslider0\",\"shortname\": \"FLANGER_Speed\",\"address\": \"/phaser_flanger/0x00/FLANGER/0x00/Speed\",\"meta\": [{ \"1\": \"\" },{ \"style\": \"knob\" },{ \"unit\": \"Hz\" }],\"init\": 0.5,\"min\": 0,\"max\": 10,\"step\": 0.01},{\"type\": \"hslider\",\"label\": \"Depth\",\"varname\": \"fHslider7\",\"shortname\": \"Depth\",\"address\": \"/phaser_flanger/0x00/FLANGER/0x00/Depth\",\"meta\": [{ \"2\": \"\" },{ \"style\": \"knob\" }],\"init\": 1,\"min\": 0,\"max\": 1,\"step\": 0.001},{\"type\": \"hslider\",\"label\": \"Feedback\",\"varname\": \"fHslider1\",\"shortname\": \"Feedback\",\"address\": \"/phaser_flanger/0x00/FLANGER/0x00/Feedback\",\"meta\": [{ \"3\": \"\" },{ \"style\": \"knob\" }],\"init\": 0,\"min\": -0.999,\"max\": 0.999,\"step\": 0.001}]},{\"type\": \"hgroup\",\"label\": \"Delay Controls\",\"meta\": [{ \"2\": \"\" }],\"items\": [ {\"type\": \"hslider\",\"label\": \"Flange Delay\",\"varname\": \"fHslider4\",\"shortname\": \"Flange_Delay\",\"address\": \"/phaser_flanger/0x00/FLANGER/Delay_Controls/Flange_Delay\",\"meta\": [{ \"1\": \"\" },{ \"style\": \"knob\" },{ \"unit\": \"ms\" }],\"init\": 10,\"min\": 0,\"max\": 20,\"step\": 0.001},{\"type\": \"hslider\",\"label\": \"Delay Offset\",\"varname\": \"fHslider3\",\"shortname\": \"Delay_Offset\",\"address\": \"/phaser_flanger/0x00/FLANGER/Delay_Controls/Delay_Offset\",\"meta\": [{ \"2\": \"\" },{ \"style\": \"knob\" },{ \"unit\": \"ms\" }],\"init\": 1,\"min\": 0,\"max\": 20,\"step\": 0.001}]},{\"type\": \"hgroup\",\"label\": \"0x00\",\"meta\": [{ \"3\": \"\" }],\"items\": [ {\"type\": \"hslider\",\"label\": \"Flanger Output Level\",\"varname\": \"fHslider2\",\"shortname\": \"Flanger_Output_Level\",\"address\": \"/phaser_flanger/0x00/FLANGER/0x00/Flanger_Output_Level\",\"meta\": [{ \"unit\": \"dB\" }],\"init\": 0,\"min\": -60,\"max\": 10,\"step\": 0.1}]}]}]},{\"type\": \"vgroup\",\"label\": \"0x00\",\"meta\": [{ \"3\": \"\" }],\"items\": [ {\"type\": \"vgroup\",\"label\": \"PHASER2\",\"meta\": [{ \"tooltip\": \"Reference: https://ccrma.stanford.edu/~jos/pasp/Flanging.html\" }],\"items\": [ {\"type\": \"hgroup\",\"label\": \"0x00\",\"meta\": [{ \"0\": \"\" }],\"items\": [ {\"type\": \"checkbox\",\"label\": \"Bypass\",\"varname\": \"fCheckbox4\",\"shortname\": \"PHASER2_Bypass\",\"address\": \"/phaser_flanger/0x00/PHASER2/0x00/Bypass\",\"meta\": [{ \"0\": \"\" },{ \"tooltip\": \"When this is checked, the phaser has no effect\" }]},{\"type\": \"checkbox\",\"label\": \"Invert Internal Phaser Sum\",\"varname\": \"fCheckbox7\",\"shortname\": \"Invert_Internal_Phaser_Sum\",\"address\": \"/phaser_flanger/0x00/PHASER2/0x00/Invert_Internal_Phaser_Sum\",\"meta\": [{ \"1\": \"\" }]},{\"type\": \"checkbox\",\"label\": \"Vibrato Mode\",\"varname\": \"fCheckbox6\",\"shortname\": \"Vibrato_Mode\",\"address\": \"/phaser_flanger/0x00/PHASER2/0x00/Vibrato_Mode\",\"meta\": [{ \"2\": \"\" }]}]},{\"type\": \"hgroup\",\"label\": \"0x00\",\"meta\": [{ \"1\": \"\" }],\"items\": [ {\"type\": \"hslider\",\"label\": \"Speed\",\"varname\": \"fHslider5\",\"shortname\": \"PHASER2_Speed\",\"address\": \"/phaser_flanger/0x00/PHASER2/0x00/Speed\",\"meta\": [{ \"1\": \"\" },{ \"style\": \"knob\" },{ \"unit\": \"Hz\" }],\"init\": 0.5,\"min\": 0,\"max\": 10,\"step\": 0.001},{\"type\": \"hslider\",\"label\": \"Notch Depth (Intensity)\",\"varname\": \"fHslider13\",\"shortname\": \"Notch_Depth_Intensity\",\"address\": \"/phaser_flanger/0x00/PHASER2/0x00/Notch_Depth__Intensity_\",\"meta\": [{ \"2\": \"\" },{ \"style\": \"knob\" }],\"init\": 1,\"min\": 0,\"max\": 1,\"step\": 0.001},{\"type\": \"hslider\",\"label\": \"Feedback Gain\",\"varname\": \"fHslider8\",\"shortname\": \"Feedback_Gain\",\"address\": \"/phaser_flanger/0x00/PHASER2/0x00/Feedback_Gain\",\"meta\": [{ \"3\": \"\" },{ \"style\": \"knob\" }],\"init\": 0,\"min\": -0.999,\"max\": 0.999,\"step\": 0.001}]},{\"type\": \"hgroup\",\"label\": \"0x00\",\"meta\": [{ \"2\": \"\" }],\"items\": [ {\"type\": \"hslider\",\"label\": \"Notch width\",\"varname\": \"fHslider9\",\"shortname\": \"Notch_width\",\"address\": \"/phaser_flanger/0x00/PHASER2/0x00/Notch_width\",\"meta\": [{ \"1\": \"\" },{ \"scale\": \"log\" },{ \"style\": \"knob\" },{ \"unit\": \"Hz\" }],\"init\": 1000,\"min\": 10,\"max\": 5000,\"step\": 1},{\"type\": \"hslider\",\"label\": \"Min Notch1 Freq\",\"varname\": \"fHslider11\",\"shortname\": \"Min_Notch1_Freq\",\"address\": \"/phaser_flanger/0x00/PHASER2/0x00/Min_Notch1_Freq\",\"meta\": [{ \"2\": \"\" },{ \"scale\": \"log\" },{ \"style\": \"knob\" },{ \"unit\": \"Hz\" }],\"init\": 100,\"min\": 20,\"max\": 5000,\"step\": 1},{\"type\": \"hslider\",\"label\": \"Max Notch1 Freq\",\"varname\": \"fHslider12\",\"shortname\": \"Max_Notch1_Freq\",\"address\": \"/phaser_flanger/0x00/PHASER2/0x00/Max_Notch1_Freq\",\"meta\": [{ \"3\": \"\" },{ \"scale\": \"log\" },{ \"style\": \"knob\" },{ \"unit\": \"Hz\" }],\"init\": 800,\"min\": 20,\"max\": 10000,\"step\": 1},{\"type\": \"hslider\",\"label\": \"Notch Freq Ratio: NotchFreq(n+1)/NotchFreq(n)\",\"varname\": \"fHslider10\",\"shortname\": \"Notch_Freq_Ratio_NotchFreq_n_1_NotchFreq_n\",\"address\": \"/phaser_flanger/0x00/PHASER2/0x00/Notch_Freq_Ratio:_NotchFreq_n+1__NotchFreq_n_\",\"meta\": [{ \"4\": \"\" },{ \"style\": \"knob\" }],\"init\": 1.5,\"min\": 1.1,\"max\": 4,\"step\": 0.001}]},{\"type\": \"hgroup\",\"label\": \"0x00\",\"meta\": [{ \"3\": \"\" }],\"items\": [ {\"type\": \"hslider\",\"label\": \"Phaser Output Level\",\"varname\": \"fHslider6\",\"shortname\": \"Phaser_Output_Level\",\"address\": \"/phaser_flanger/0x00/PHASER2/0x00/Phaser_Output_Level\",\"meta\": [{ \"unit\": \"dB\" }],\"init\": 0,\"min\": -60,\"max\": 10,\"step\": 0.1}]}]}]},{\"type\": \"vgroup\",\"label\": \"0x00\",\"meta\": [{ \"4\": \"\" }],\"items\": [ {\"type\": \"hgroup\",\"label\": \"CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning LP, 9 octaves below 16000 Hz, HP\",\"meta\": [{ \"0\": \"\" },{ \"tooltip\": \"See Faust\'s filter.lib for documentation and references\" }],\"items\": [ {\"type\": \"vbargraph\",\"label\": \"vbargraph0\",\"varname\": \"fVbargraph14\",\"shortname\": \"vbargraph0\",\"address\": \"/phaser_flanger/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph0\",\"meta\": [{ \"0\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph1\",\"varname\": \"fVbargraph13\",\"shortname\": \"vbargraph1\",\"address\": \"/phaser_flanger/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph1\",\"meta\": [{ \"1\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph2\",\"varname\": \"fVbargraph12\",\"shortname\": \"vbargraph2\",\"address\": \"/phaser_flanger/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph2\",\"meta\": [{ \"2\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph3\",\"varname\": \"fVbargraph11\",\"shortname\": \"vbargraph3\",\"address\": \"/phaser_flanger/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph3\",\"meta\": [{ \"3\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph4\",\"varname\": \"fVbargraph10\",\"shortname\": \"vbargraph4\",\"address\": \"/phaser_flanger/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph4\",\"meta\": [{ \"4\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph5\",\"varname\": \"fVbargraph9\",\"shortname\": \"vbargraph5\",\"address\": \"/phaser_flanger/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph5\",\"meta\": [{ \"5\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph6\",\"varname\": \"fVbargraph8\",\"shortname\": \"vbargraph6\",\"address\": \"/phaser_flanger/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph6\",\"meta\": [{ \"6\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph7\",\"varname\": \"fVbargraph7\",\"shortname\": \"vbargraph7\",\"address\": \"/phaser_flanger/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph7\",\"meta\": [{ \"7\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph8\",\"varname\": \"fVbargraph6\",\"shortname\": \"vbargraph8\",\"address\": \"/phaser_flanger/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph8\",\"meta\": [{ \"8\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph9\",\"varname\": \"fVbargraph5\",\"shortname\": \"vbargraph9\",\"address\": \"/phaser_flanger/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph9\",\"meta\": [{ \"9\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph10\",\"varname\": \"fVbargraph4\",\"shortname\": \"vbargraph10\",\"address\": \"/phaser_flanger/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph10\",\"meta\": [{ \"10\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph11\",\"varname\": \"fVbargraph3\",\"shortname\": \"vbargraph11\",\"address\": \"/phaser_flanger/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph11\",\"meta\": [{ \"11\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph12\",\"varname\": \"fVbargraph2\",\"shortname\": \"vbargraph12\",\"address\": \"/phaser_flanger/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph12\",\"meta\": [{ \"12\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph13\",\"varname\": \"fVbargraph1\",\"shortname\": \"vbargraph13\",\"address\": \"/phaser_flanger/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph13\",\"meta\": [{ \"13\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph14\",\"varname\": \"fVbargraph0\",\"shortname\": \"vbargraph14\",\"address\": \"/phaser_flanger/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph14\",\"meta\": [{ \"14\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10}]},{\"type\": \"hgroup\",\"label\": \"SPECTRUM ANALYZER CONTROLS\",\"meta\": [{ \"1\": \"\" }],\"items\": [ {\"type\": \"hslider\",\"label\": \"Level Averaging Time\",\"varname\": \"fHslider14\",\"shortname\": \"Level_Averaging_Time\",\"address\": \"/phaser_flanger/0x00/SPECTRUM_ANALYZER_CONTROLS/Level_Averaging_Time\",\"meta\": [{ \"0\": \"\" },{ \"scale\": \"log\" },{ \"tooltip\": \"band-level averaging time in milliseconds\" },{ \"unit\": \"ms\" }],\"init\": 100,\"min\": 1,\"max\": 10000,\"step\": 1},{\"type\": \"hslider\",\"label\": \"Level dB Offset\",\"varname\": \"fHslider15\",\"shortname\": \"Level_dB_Offset\",\"address\": \"/phaser_flanger/0x00/SPECTRUM_ANALYZER_CONTROLS/Level_dB_Offset\",\"meta\": [{ \"1\": \"\" },{ \"tooltip\": \"Level offset in decibels\" },{ \"unit\": \"dB\" }],\"init\": 50,\"min\": 0,\"max\": 100,\"step\": 1}]}]}]}]}"

    @always_inline
    def metadata(imm dsp, mut meta: Some[FaustMeta]) -> None:
        meta.declare("compile_options", "-a /Users/manuelfarzini/Personal/dev/repo/faust/architecture/mojo/impulse.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0 -vec -lv 0 -vs 4 -dfs")
        meta.declare("effect.lib/bypass2:author", "Julius O. Smith (jos at ccrma.stanford.edu)")
        meta.declare("effect.lib/bypass2:copyright", "Julius O. Smith III")
        meta.declare("effect.lib/bypass2:license", "STK-4.3")
        meta.declare("effect.lib/cross2:author", "Julius O. Smith (jos at ccrma.stanford.edu)")
        meta.declare("effect.lib/cross2:copyright", "Julius O. Smith III")
        meta.declare("effect.lib/cross2:license", "STK-4.3")
        meta.declare("effect.lib/flanger_demo:author", "Julius O. Smith (jos at ccrma.stanford.edu)")
        meta.declare("effect.lib/flanger_demo:copyright", "Julius O. Smith III")
        meta.declare("effect.lib/flanger_demo:license", "STK-4.3")
        meta.declare("effect.lib/flanger_mono:author", "Julius O. Smith (jos at ccrma.stanford.edu)")
        meta.declare("effect.lib/flanger_mono:copyright", "Julius O. Smith III")
        meta.declare("effect.lib/flanger_mono:license", "STK-4.3")
        meta.declare("effect.lib/flanger_stereo:author", "Julius O. Smith (jos at ccrma.stanford.edu)")
        meta.declare("effect.lib/flanger_stereo:copyright", "Julius O. Smith III")
        meta.declare("effect.lib/flanger_stereo:license", "STK-4.3")
        meta.declare("effect.lib/name", "Faust Audio Effect Library")
        meta.declare("effect.lib/phaser2_demo:author", "Julius O. Smith (jos at ccrma.stanford.edu)")
        meta.declare("effect.lib/phaser2_demo:copyright", "Julius O. Smith III")
        meta.declare("effect.lib/phaser2_demo:license", "STK-4.3")
        meta.declare("effect.lib/phaser2_mono:author", "Julius O. Smith (jos at ccrma.stanford.edu)")
        meta.declare("effect.lib/phaser2_mono:copyright", "Julius O. Smith III")
        meta.declare("effect.lib/phaser2_mono:license", "STK-4.3")
        meta.declare("effect.lib/phaser2_stereo:author", "Julius O. Smith (jos at ccrma.stanford.edu)")
        meta.declare("effect.lib/phaser2_stereo:copyright", "Julius O. Smith III")
        meta.declare("effect.lib/phaser2_stereo:license", "STK-4.3")
        meta.declare("effect.lib/select2stereo:author", "Julius O. Smith (jos at ccrma.stanford.edu)")
        meta.declare("effect.lib/select2stereo:copyright", "Julius O. Smith III")
        meta.declare("effect.lib/select2stereo:license", "STK-4.3")
        meta.declare("effect.lib/vibrato2_mono:author", "Julius O. Smith (jos at ccrma.stanford.edu)")
        meta.declare("effect.lib/vibrato2_mono:copyright", "Julius O. Smith III")
        meta.declare("effect.lib/vibrato2_mono:license", "STK-4.3")
        meta.declare("filename", "phaser_flanger.dsp")
        meta.declare("filter.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)")
        meta.declare("filter.lib/copyright", "Julius O. Smith III")
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
        meta.declare("music.lib/license", "LGPL with exception")
        meta.declare("music.lib/name", "Music Library")
        meta.declare("music.lib/version", "1.0")
        meta.declare("name", "phaser_flanger")
        meta.declare("oscillator.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)")
        meta.declare("oscillator.lib/copyright", "Julius O. Smith III")
        meta.declare("oscillator.lib/license", "STK-4.3")
        meta.declare("oscillator.lib/name", "Faust Oscillator Library")
        meta.declare("oscillator.lib/version", "1.11")

    @always_inline
    def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None:
        ui.open_vertical_box("phaser_flanger")
        ui.declare(dsp.null_val, "1", "")
        ui.open_vertical_box("0x00")
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
        ui.open_vertical_box("0x00")
        ui.declare(dsp.null_val, "tooltip", "Reference: https://ccrma.stanford.edu/~jos/pasp/Flanging.html")
        ui.open_vertical_box("FLANGER")
        ui.declare(dsp.null_val, "0", "")
        ui.open_horizontal_box("0x00")
        ui.declare(dsp.checkbox0, "0", "")
        ui.declare(dsp.checkbox0, "tooltip", "When this is checked, the flanger has no effect")
        ui.add_check_button("Bypass", dsp.checkbox0)
        ui.declare(dsp.checkbox5, "1", "")
        ui.add_check_button("Invert Flange Sum", dsp.checkbox5)
        ui.declare(dsp.hbargraph0, "2", "")
        ui.declare(dsp.hbargraph0, "style", "led")
        ui.declare(dsp.hbargraph0, "tooltip", "Display sum of flange delays")
        ui.add_horizontal_bargraph("Flange LFO", dsp.hbargraph0, FaustFloat(-1.5), FaustFloat(1.5))
        ui.close_box()
        ui.declare(dsp.null_val, "1", "")
        ui.open_horizontal_box("0x00")
        ui.declare(dsp.hslider0, "1", "")
        ui.declare(dsp.hslider0, "style", "knob")
        ui.declare(dsp.hslider0, "unit", "Hz")
        ui.add_horizontal_slider("Speed", dsp.hslider0, FaustFloat(0.5), FaustFloat(0.0), FaustFloat(10.0), FaustFloat(0.01))
        ui.declare(dsp.hslider7, "2", "")
        ui.declare(dsp.hslider7, "style", "knob")
        ui.add_horizontal_slider("Depth", dsp.hslider7, FaustFloat(1.0), FaustFloat(0.0), FaustFloat(1.0), FaustFloat(0.001))
        ui.declare(dsp.hslider1, "3", "")
        ui.declare(dsp.hslider1, "style", "knob")
        ui.add_horizontal_slider("Feedback", dsp.hslider1, FaustFloat(0.0), FaustFloat(-0.999), FaustFloat(0.999), FaustFloat(0.001))
        ui.close_box()
        ui.declare(dsp.null_val, "2", "")
        ui.open_horizontal_box("Delay Controls")
        ui.declare(dsp.hslider4, "1", "")
        ui.declare(dsp.hslider4, "style", "knob")
        ui.declare(dsp.hslider4, "unit", "ms")
        ui.add_horizontal_slider("Flange Delay", dsp.hslider4, FaustFloat(10.0), FaustFloat(0.0), FaustFloat(20.0), FaustFloat(0.001))
        ui.declare(dsp.hslider3, "2", "")
        ui.declare(dsp.hslider3, "style", "knob")
        ui.declare(dsp.hslider3, "unit", "ms")
        ui.add_horizontal_slider("Delay Offset", dsp.hslider3, FaustFloat(1.0), FaustFloat(0.0), FaustFloat(20.0), FaustFloat(0.001))
        ui.close_box()
        ui.declare(dsp.null_val, "3", "")
        ui.open_horizontal_box("0x00")
        ui.declare(dsp.hslider2, "unit", "dB")
        ui.add_horizontal_slider("Flanger Output Level", dsp.hslider2, FaustFloat(0.0), FaustFloat(-60.0), FaustFloat(10.0), FaustFloat(0.1))
        ui.close_box()
        ui.close_box()
        ui.close_box()
        ui.declare(dsp.null_val, "3", "")
        ui.open_vertical_box("0x00")
        ui.declare(dsp.null_val, "tooltip", "Reference: https://ccrma.stanford.edu/~jos/pasp/Flanging.html")
        ui.open_vertical_box("PHASER2")
        ui.declare(dsp.null_val, "0", "")
        ui.open_horizontal_box("0x00")
        ui.declare(dsp.checkbox4, "0", "")
        ui.declare(dsp.checkbox4, "tooltip", "When this is checked, the phaser has no effect")
        ui.add_check_button("Bypass", dsp.checkbox4)
        ui.declare(dsp.checkbox7, "1", "")
        ui.add_check_button("Invert Internal Phaser Sum", dsp.checkbox7)
        ui.declare(dsp.checkbox6, "2", "")
        ui.add_check_button("Vibrato Mode", dsp.checkbox6)
        ui.close_box()
        ui.declare(dsp.null_val, "1", "")
        ui.open_horizontal_box("0x00")
        ui.declare(dsp.hslider5, "1", "")
        ui.declare(dsp.hslider5, "style", "knob")
        ui.declare(dsp.hslider5, "unit", "Hz")
        ui.add_horizontal_slider("Speed", dsp.hslider5, FaustFloat(0.5), FaustFloat(0.0), FaustFloat(10.0), FaustFloat(0.001))
        ui.declare(dsp.hslider13, "2", "")
        ui.declare(dsp.hslider13, "style", "knob")
        ui.add_horizontal_slider("Notch Depth (Intensity)", dsp.hslider13, FaustFloat(1.0), FaustFloat(0.0), FaustFloat(1.0), FaustFloat(0.001))
        ui.declare(dsp.hslider8, "3", "")
        ui.declare(dsp.hslider8, "style", "knob")
        ui.add_horizontal_slider("Feedback Gain", dsp.hslider8, FaustFloat(0.0), FaustFloat(-0.999), FaustFloat(0.999), FaustFloat(0.001))
        ui.close_box()
        ui.declare(dsp.null_val, "2", "")
        ui.open_horizontal_box("0x00")
        ui.declare(dsp.hslider9, "1", "")
        ui.declare(dsp.hslider9, "scale", "log")
        ui.declare(dsp.hslider9, "style", "knob")
        ui.declare(dsp.hslider9, "unit", "Hz")
        ui.add_horizontal_slider("Notch width", dsp.hslider9, FaustFloat(1000.0), FaustFloat(10.0), FaustFloat(5000.0), FaustFloat(1.0))
        ui.declare(dsp.hslider11, "2", "")
        ui.declare(dsp.hslider11, "scale", "log")
        ui.declare(dsp.hslider11, "style", "knob")
        ui.declare(dsp.hslider11, "unit", "Hz")
        ui.add_horizontal_slider("Min Notch1 Freq", dsp.hslider11, FaustFloat(100.0), FaustFloat(20.0), FaustFloat(5000.0), FaustFloat(1.0))
        ui.declare(dsp.hslider12, "3", "")
        ui.declare(dsp.hslider12, "scale", "log")
        ui.declare(dsp.hslider12, "style", "knob")
        ui.declare(dsp.hslider12, "unit", "Hz")
        ui.add_horizontal_slider("Max Notch1 Freq", dsp.hslider12, FaustFloat(800.0), FaustFloat(20.0), FaustFloat(10000.0), FaustFloat(1.0))
        ui.declare(dsp.hslider10, "4", "")
        ui.declare(dsp.hslider10, "style", "knob")
        ui.add_horizontal_slider("Notch Freq Ratio: NotchFreq(n+1)/NotchFreq(n)", dsp.hslider10, FaustFloat(1.5), FaustFloat(1.1), FaustFloat(4.0), FaustFloat(0.001))
        ui.close_box()
        ui.declare(dsp.null_val, "3", "")
        ui.open_horizontal_box("0x00")
        ui.declare(dsp.hslider6, "unit", "dB")
        ui.add_horizontal_slider("Phaser Output Level", dsp.hslider6, FaustFloat(0.0), FaustFloat(-60.0), FaustFloat(10.0), FaustFloat(0.1))
        ui.close_box()
        ui.close_box()
        ui.close_box()
        ui.declare(dsp.null_val, "4", "")
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
        ui.declare(dsp.hslider14, "0", "")
        ui.declare(dsp.hslider14, "scale", "log")
        ui.declare(dsp.hslider14, "tooltip", "band-level averaging time in milliseconds")
        ui.declare(dsp.hslider14, "unit", "ms")
        ui.add_horizontal_slider("Level Averaging Time", dsp.hslider14, FaustFloat(100.0), FaustFloat(1.0), FaustFloat(10000.0), FaustFloat(1.0))
        ui.declare(dsp.hslider15, "1", "")
        ui.declare(dsp.hslider15, "tooltip", "Level offset in decibels")
        ui.declare(dsp.hslider15, "unit", "dB")
        ui.add_horizontal_slider("Level dB Offset", dsp.hslider15, FaustFloat(50.0), FaustFloat(0.0), FaustFloat(100.0), FaustFloat(1.0))
        ui.close_box()
        ui.close_box()
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
        var output0_ptr = outputs[unsafe_offset = S32(0)]
        var output1_ptr = outputs[unsafe_offset = S32(1)]
        var slow0 = (0.0010000000000000009) * (pow(1e+01, (0.05) * (F64(dsp.vslider0))))
        var rec0_tmp = Arr[F64, 8](uninitialized=True)
        var rec0 = Ptr(to=rec0_tmp[S32(4)])
        var slow1 = F64(dsp.vslider1)
        var slow2 = exp(-((dsp.const1) / (slow1))) if S32((slow1) > (0.0)) else 0.0
        var slow3 = ((4.4e+02) * (pow(2.0, (0.08333333333333333) * ((F64(dsp.vslider2)) + (-49.0))))) * ((1.0) - (slow2))
        var rec2_tmp = Arr[F64, 8](uninitialized=True)
        var rec2 = Ptr(to=rec2_tmp[S32(4)])
        var zec0 = Arr[F64, 4](uninitialized=True)
        var zec1 = Arr[F64, 4](uninitialized=True)
        var rec1_tmp = Arr[F64, 8](uninitialized=True)
        var rec1 = Ptr(to=rec1_tmp[S32(4)])
        var slow4 = ((0.01) * (F64(dsp.vslider3))) + (1.0)
        var zec2 = Arr[F64, 4](uninitialized=True)
        var zec3 = Arr[F64, 4](uninitialized=True)
        var rec3_tmp = Arr[F64, 8](uninitialized=True)
        var rec3 = Ptr(to=rec3_tmp[S32(4)])
        var slow5 = ((0.01) * (F64(dsp.vslider4))) + (1.0)
        var zec4 = Arr[F64, 4](uninitialized=True)
        var zec5 = Arr[F64, 4](uninitialized=True)
        var rec4_tmp = Arr[F64, 8](uninitialized=True)
        var rec4 = Ptr(to=rec4_tmp[S32(4)])
        var i_rec5_tmp = Arr[S32, 8](uninitialized=True)
        var i_rec5 = Ptr(to=i_rec5_tmp[S32(4)])
        var zec6 = Arr[F64, 4](uninitialized=True)
        var rec6_tmp = Arr[F64, 8](uninitialized=True)
        var rec6 = Ptr(to=rec6_tmp[S32(4)])
        var slow6 = (dsp.const2) * (F64(dsp.hslider0))
        var slow7 = sin(slow6)
        var slow8 = cos(slow6)
        var rec7_tmp = Arr[F64, 8](uninitialized=True)
        var rec7 = Ptr(to=rec7_tmp[S32(4)])
        var i_vec0_tmp = Arr[S32, 8](uninitialized=True)
        var i_vec0 = Ptr(to=i_vec0_tmp[S32(4)])
        var zec7 = Arr[F64, 4](uninitialized=True)
        var rec8_tmp = Arr[F64, 8](uninitialized=True)
        var rec8 = Ptr(to=rec8_tmp[S32(4)])
        var slow9 = F64(dsp.hslider1)
        var slow10 = pow(1e+01, (0.05) * (F64(dsp.hslider2)))
        var i_slow11 = S32(F64(dsp.checkbox0))
        var i_slow12 = S32(F64(dsp.checkbox1))
        var i_slow13 = S32(F64(dsp.checkbox2))
        var i_slow14 = S32((F64(dsp.entry0)) + (-1.0))
        var i_slow15 = S32((i_slow14) >= (S32(2)))
        var i_slow16 = S32((i_slow14) >= (S32(1)))
        var zec8 = Arr[F64, 4](uninitialized=True)
        var zec9 = Arr[F64, 4](uninitialized=True)
        var zec10 = Arr[F64, 4](uninitialized=True)
        var yec0_tmp = Arr[F64, 8](uninitialized=True)
        var yec0 = Ptr(to=yec0_tmp[S32(4)])
        var i_slow17 = S32((i_slow14) >= (S32(3)))
        var zec11 = Arr[F64, 4](uninitialized=True)
        var zec12 = Arr[F64, 4](uninitialized=True)
        var yec1_tmp = Arr[F64, 8](uninitialized=True)
        var yec1 = Ptr(to=yec1_tmp[S32(4)])
        var yec2_tmp = Arr[F64, 8](uninitialized=True)
        var yec2 = Ptr(to=yec2_tmp[S32(4)])
        var zec13 = Arr[F64, 4](uninitialized=True)
        var yec3_tmp = Arr[F64, 8](uninitialized=True)
        var yec3 = Ptr(to=yec3_tmp[S32(4)])
        var yec4_tmp = Arr[F64, 8](uninitialized=True)
        var yec4 = Ptr(to=yec4_tmp[S32(4)])
        var yec5_tmp = Arr[F64, 8](uninitialized=True)
        var yec5 = Ptr(to=yec5_tmp[S32(4)])
        var zec14 = Arr[F64, 4](uninitialized=True)
        var zec15 = Arr[F64, 4](uninitialized=True)
        var yec6_tmp = Arr[F64, 8](uninitialized=True)
        var yec6 = Ptr(to=yec6_tmp[S32(4)])
        var zec16 = Arr[F64, 4](uninitialized=True)
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
        var zec17 = Arr[F64, 4](uninitialized=True)
        var zec18 = Arr[F64, 4](uninitialized=True)
        var yec12_tmp = Arr[F64, 8](uninitialized=True)
        var yec12 = Ptr(to=yec12_tmp[S32(4)])
        var zec19 = Arr[F64, 4](uninitialized=True)
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
        var i_slow18 = S32(F64(dsp.checkbox3))
        var zec20 = Arr[F64, 4](uninitialized=True)
        var zec21 = Arr[F64, 4](uninitialized=True)
        var zec22 = Arr[F64, 4](uninitialized=True)
        var slow19 = (0.001) * (F64(dsp.hslider3))
        var slow20 = (0.0005) * (F64(dsp.hslider4))
        var zec23 = Arr[F64, 4](uninitialized=True)
        var i_zec24 = Arr[S32, 4](uninitialized=True)
        var zec25 = Arr[F64, 4](uninitialized=True)
        var rec9_tmp = Arr[F64, 8](uninitialized=True)
        var rec9 = Ptr(to=rec9_tmp[S32(4)])
        var slow21 = (dsp.const2) * (F64(dsp.hslider5))
        var slow22 = sin(slow21)
        var slow23 = cos(slow21)
        var rec15_tmp = Arr[F64, 8](uninitialized=True)
        var rec15 = Ptr(to=rec15_tmp[S32(4)])
        var rec16_tmp = Arr[F64, 8](uninitialized=True)
        var rec16 = Ptr(to=rec16_tmp[S32(4)])
        var slow24 = pow(1e+01, (0.05) * (F64(dsp.hslider6)))
        var i_slow25 = S32(F64(dsp.checkbox4))
        var slow26 = F64(dsp.hslider7)
        var slow27 = -slow26 if S32(F64(dsp.checkbox5)) else slow26
        var zec26 = Arr[F64, 4](uninitialized=True)
        var zec27 = Arr[F64, 4](uninitialized=True)
        var slow28 = F64(dsp.hslider8)
        var slow29 = exp(-((dsp.const6) * (F64(dsp.hslider9))))
        var slow30 = (2.0) * (slow29)
        var slow31 = F64(dsp.hslider10)
        var slow32 = (dsp.const1) * (slow31)
        var slow33 = F64(dsp.hslider11)
        var slow34 = (6.283185307179586) * (slow33)
        var slow35 = (3.141592653589793) * ((slow33) - (max(slow33, F64(dsp.hslider12))))
        var zec28 = Arr[F64, 4](uninitialized=True)
        var zec29 = Arr[F64, 4](uninitialized=True)
        var slow36 = pow_unrolled[2](slow29)
        var rec14_tmp = Arr[F64, 8](uninitialized=True)
        var rec14 = Ptr(to=rec14_tmp[S32(4)])
        var slow37 = (dsp.const1) * (pow_unrolled[2](slow31))
        var zec30 = Arr[F64, 4](uninitialized=True)
        var rec13_tmp = Arr[F64, 8](uninitialized=True)
        var rec13 = Ptr(to=rec13_tmp[S32(4)])
        var slow38 = (dsp.const1) * (pow_unrolled[3](slow31))
        var zec31 = Arr[F64, 4](uninitialized=True)
        var rec12_tmp = Arr[F64, 8](uninitialized=True)
        var rec12 = Ptr(to=rec12_tmp[S32(4)])
        var slow39 = (dsp.const1) * (pow_unrolled[4](slow31))
        var zec32 = Arr[F64, 4](uninitialized=True)
        var rec11_tmp = Arr[F64, 8](uninitialized=True)
        var rec11 = Ptr(to=rec11_tmp[S32(4)])
        var rec10_tmp = Arr[F64, 8](uninitialized=True)
        var rec10 = Ptr(to=rec10_tmp[S32(4)])
        var zec33 = Arr[F64, 4](uninitialized=True)
        var zec34 = Arr[F64, 4](uninitialized=True)
        var i_zec35 = Arr[S32, 4](uninitialized=True)
        var zec36 = Arr[F64, 4](uninitialized=True)
        var rec17_tmp = Arr[F64, 8](uninitialized=True)
        var rec17 = Ptr(to=rec17_tmp[S32(4)])
        var zec37 = Arr[F64, 4](uninitialized=True)
        var zec38 = Arr[F64, 4](uninitialized=True)
        var zec39 = Arr[F64, 4](uninitialized=True)
        var zec40 = Arr[F64, 4](uninitialized=True)
        var rec22_tmp = Arr[F64, 8](uninitialized=True)
        var rec22 = Ptr(to=rec22_tmp[S32(4)])
        var zec41 = Arr[F64, 4](uninitialized=True)
        var rec21_tmp = Arr[F64, 8](uninitialized=True)
        var rec21 = Ptr(to=rec21_tmp[S32(4)])
        var zec42 = Arr[F64, 4](uninitialized=True)
        var rec20_tmp = Arr[F64, 8](uninitialized=True)
        var rec20 = Ptr(to=rec20_tmp[S32(4)])
        var zec43 = Arr[F64, 4](uninitialized=True)
        var rec19_tmp = Arr[F64, 8](uninitialized=True)
        var rec19 = Ptr(to=rec19_tmp[S32(4)])
        var rec18_tmp = Arr[F64, 8](uninitialized=True)
        var rec18 = Ptr(to=rec18_tmp[S32(4)])
        var slow40 = (0.5) * (2.0 if S32(F64(dsp.checkbox6)) else F64(dsp.hslider13))
        var slow41 = (1.0) - (slow40)
        var slow42 = -slow40 if S32(F64(dsp.checkbox7)) else slow40
        var zec44 = Arr[F64, 4](uninitialized=True)
        var zec45 = Arr[F64, 4](uninitialized=True)
        var zec46 = Arr[F64, 4](uninitialized=True)
        var rec26_tmp = Arr[F64, 8](uninitialized=True)
        var rec26 = Ptr(to=rec26_tmp[S32(4)])
        var rec25_tmp = Arr[F64, 8](uninitialized=True)
        var rec25 = Ptr(to=rec25_tmp[S32(4)])
        var rec24_tmp = Arr[F64, 8](uninitialized=True)
        var rec24 = Ptr(to=rec24_tmp[S32(4)])
        var slow43 = F64(dsp.hslider14)
        var slow44 = exp(-((dsp.const26) / (slow43))) if S32(((0.001) * (slow43)) > (0.0)) else 0.0
        var slow45 = (1.0) - (slow44)
        var rec23_tmp = Arr[F64, 8](uninitialized=True)
        var rec23 = Ptr(to=rec23_tmp[S32(4)])
        var rec33_tmp = Arr[F64, 8](uninitialized=True)
        var rec33 = Ptr(to=rec33_tmp[S32(4)])
        var rec32_tmp = Arr[F64, 8](uninitialized=True)
        var rec32 = Ptr(to=rec32_tmp[S32(4)])
        var rec31_tmp = Arr[F64, 8](uninitialized=True)
        var rec31 = Ptr(to=rec31_tmp[S32(4)])
        var zec47 = Arr[F64, 4](uninitialized=True)
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
        var zec48 = Arr[F64, 4](uninitialized=True)
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
        var zec49 = Arr[F64, 4](uninitialized=True)
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
        var zec50 = Arr[F64, 4](uninitialized=True)
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
        var zec51 = Arr[F64, 4](uninitialized=True)
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
        var zec52 = Arr[F64, 4](uninitialized=True)
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
        var zec53 = Arr[F64, 4](uninitialized=True)
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
        var zec54 = Arr[F64, 4](uninitialized=True)
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
        var zec55 = Arr[F64, 4](uninitialized=True)
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
        var zec56 = Arr[F64, 4](uninitialized=True)
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
        var zec57 = Arr[F64, 4](uninitialized=True)
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
        var zec58 = Arr[F64, 4](uninitialized=True)
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
        var zec59 = Arr[F64, 4](uninitialized=True)
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
        var slow46 = F64(dsp.hslider15)
        while vindex <= end:
            var input0 = Ptr(to=input0_ptr[unsafe_offset = vindex])
            var output0 = Ptr(to=output0_ptr[unsafe_offset = vindex])
            var output1 = Ptr(to=output1_ptr[unsafe_offset = vindex])
            vstore(rec0_tmp, vload[H](dsp.rec0_perm))
            vstore(rec0_tmp, vload[H](dsp.rec0_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec0[unsafe_offset = i] = (slow0) + ((0.999) * (rec0[unsafe_offset = (i) - (S32(1))]))
            vstore(dsp.rec0_perm, vload[H](rec0_tmp, vsize))
            vstore(dsp.rec0_perm, vload[H](rec0_tmp, vsize + hsize), hsize)
            vstore(rec2_tmp, vload[H](dsp.rec2_perm))
            vstore(rec2_tmp, vload[H](dsp.rec2_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec2[unsafe_offset = i] = ((rec2[unsafe_offset = (i) - (S32(1))]) * (slow2)) + (slow3)
            vstore(dsp.rec2_perm, vload[H](rec2_tmp, vsize))
            vstore(dsp.rec2_perm, vload[H](rec2_tmp, vsize + hsize), hsize)
            vstore(zec0, max(F64Vec(2e+01), abs(vload[H](rec2))))
            vstore(zec0, max(F64Vec(2e+01), abs(vload[H](rec2, hsize))), hsize)
            vstore(rec1_tmp, vload[H](dsp.rec1_perm))
            vstore(rec1_tmp, vload[H](dsp.rec1_perm, hsize), hsize)
            comptime for i in range(vsize):
                zec1[i] = (rec1[unsafe_offset = (i) - (S32(1))]) + ((dsp.const1) * (zec0[i]))
                rec1[unsafe_offset = i] = (zec1[i]) - (floor(zec1[i]))
            vstore(dsp.rec1_perm, vload[H](rec1_tmp, vsize))
            vstore(dsp.rec1_perm, vload[H](rec1_tmp, vsize + hsize), hsize)
            vstore(zec2, max(F64Vec(2e+01), abs((F64Vec(slow4)) * (vload[H](rec2)))))
            vstore(zec2, max(F64Vec(2e+01), abs((F64Vec(slow4)) * (vload[H](rec2, hsize)))), hsize)
            vstore(rec3_tmp, vload[H](dsp.rec3_perm))
            vstore(rec3_tmp, vload[H](dsp.rec3_perm, hsize), hsize)
            comptime for i in range(vsize):
                zec3[i] = (rec3[unsafe_offset = (i) - (S32(1))]) + ((dsp.const1) * (zec2[i]))
                rec3[unsafe_offset = i] = (zec3[i]) - (floor(zec3[i]))
            vstore(dsp.rec3_perm, vload[H](rec3_tmp, vsize))
            vstore(dsp.rec3_perm, vload[H](rec3_tmp, vsize + hsize), hsize)
            vstore(zec4, max(F64Vec(2e+01), abs((F64Vec(slow5)) * (vload[H](rec2)))))
            vstore(zec4, max(F64Vec(2e+01), abs((F64Vec(slow5)) * (vload[H](rec2, hsize)))), hsize)
            vstore(rec4_tmp, vload[H](dsp.rec4_perm))
            vstore(rec4_tmp, vload[H](dsp.rec4_perm, hsize), hsize)
            comptime for i in range(vsize):
                zec5[i] = (rec4[unsafe_offset = (i) - (S32(1))]) + ((dsp.const1) * (zec4[i]))
                rec4[unsafe_offset = i] = (zec5[i]) - (floor(zec5[i]))
            vstore(dsp.rec4_perm, vload[H](rec4_tmp, vsize))
            vstore(dsp.rec4_perm, vload[H](rec4_tmp, vsize + hsize), hsize)
            vstore(i_rec5_tmp, vload(dsp.i_rec5_perm))
            comptime for i in range(vsize):
                i_rec5[unsafe_offset = i] = ((S32(1103515245)) * (i_rec5[unsafe_offset = (i) - (S32(1))])) + (S32(12345))
            vstore(dsp.i_rec5_perm, vload(i_rec5_tmp, vsize))
            vstore(zec6, (F64Vec(4.656612875245797e-10)) * ((vload[H](i_rec5)).cast[f64]()))
            vstore(zec6, (F64Vec(4.656612875245797e-10)) * ((vload[H](i_rec5, hsize)).cast[f64]()), hsize)
            vstore(rec6_tmp, vload[H](dsp.rec6_perm))
            vstore(rec6_tmp, vload[H](dsp.rec6_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec6[unsafe_offset = i] = (((0.5221894) * (rec6[unsafe_offset = (i) - (S32(3))])) + ((zec6[i]) + ((2.494956002) * (rec6[unsafe_offset = (i) - (S32(1))])))) - ((2.017265875) * (rec6[unsafe_offset = (i) - (S32(2))]))
            vstore(dsp.rec6_perm, vload[H](rec6_tmp, vsize))
            vstore(dsp.rec6_perm, vload[H](rec6_tmp, vsize + hsize), hsize)
            vstore(i_vec0_tmp, vload(dsp.i_vec0_perm))
            vstore(i_vec0, S32Vec(1))
            vstore(dsp.i_vec0_perm, vload(i_vec0_tmp, vsize))
            vstore(zec7, ((S32Hec(1)) - (vload[H](i_vec0, - S32(1)))).cast[f64]())
            vstore(zec7, ((S32Hec(1)) - (vload[H](i_vec0, - S32(1) + hsize))).cast[f64](), hsize)
            vstore(rec7_tmp, vload[H](dsp.rec7_perm))
            vstore(rec7_tmp, vload[H](dsp.rec7_perm, hsize), hsize)
            vstore(rec8_tmp, vload[H](dsp.rec8_perm))
            vstore(rec8_tmp, vload[H](dsp.rec8_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec7[unsafe_offset = i] = ((slow7) * (rec8[unsafe_offset = (i) - (S32(1))])) + ((slow8) * (rec7[unsafe_offset = (i) - (S32(1))]))
                rec8[unsafe_offset = i] = ((zec7[i]) + ((slow8) * (rec8[unsafe_offset = (i) - (S32(1))]))) - ((slow7) * (rec7[unsafe_offset = (i) - (S32(1))]))
            vstore(dsp.rec7_perm, vload[H](rec7_tmp, vsize))
            vstore(dsp.rec7_perm, vload[H](rec7_tmp, vsize + hsize), hsize)
            vstore(dsp.rec8_perm, vload[H](rec8_tmp, vsize))
            vstore(dsp.rec8_perm, vload[H](rec8_tmp, vsize + hsize), hsize)
            vstore(zec8, (F64Vec(2.0)) * (vload[H](rec1)))
            vstore(zec8, (F64Vec(2.0)) * (vload[H](rec1, hsize)), hsize)
            vstore(zec9, (vload[H](zec8)) + (F64Vec(-1.0)))
            vstore(zec9, (vload[H](zec8, hsize)) + (F64Vec(-1.0)), hsize)
            vstore(zec10, (vload[H](i_vec0, - S32(1))).cast[f64]())
            vstore(zec10, (vload[H](i_vec0, - S32(1) + hsize)).cast[f64](), hsize)
            vstore(yec0_tmp, vload[H](dsp.yec0_perm))
            vstore(yec0_tmp, vload[H](dsp.yec0_perm, hsize), hsize)
            vstore(yec0, pow_unrolled[2](vload[H](zec9)))
            vstore(yec0, pow_unrolled[2](vload[H](zec9, hsize)), hsize)
            vstore(dsp.yec0_perm, vload[H](yec0_tmp, vsize))
            vstore(dsp.yec0_perm, vload[H](yec0_tmp, vsize + hsize), hsize)
            vstore(zec11, (vload[H](i_vec0, - S32(2))).cast[f64]())
            vstore(zec11, (vload[H](i_vec0, - S32(2) + hsize)).cast[f64](), hsize)
            vstore(zec12, pow_unrolled[3](vload[H](zec9)))
            vstore(zec12, pow_unrolled[3](vload[H](zec9, hsize)), hsize)
            vstore(yec1_tmp, vload[H](dsp.yec1_perm))
            vstore(yec1_tmp, vload[H](dsp.yec1_perm, hsize), hsize)
            vstore(yec1, (vload[H](zec12)) + ((F64Vec(1.0)) - (vload[H](zec8))))
            vstore(yec1, (vload[H](zec12, hsize)) + ((F64Vec(1.0)) - (vload[H](zec8, hsize))), hsize)
            vstore(dsp.yec1_perm, vload[H](yec1_tmp, vsize))
            vstore(dsp.yec1_perm, vload[H](yec1_tmp, vsize + hsize), hsize)
            vstore(yec2_tmp, vload[H](dsp.yec2_perm))
            vstore(yec2_tmp, vload[H](dsp.yec2_perm, hsize), hsize)
            vstore(yec2, ((vload[H](zec12)) + ((F64Vec(1.0)) - ((vload[H](zec8)) + (vload[H](yec1, - S32(1)))))) / (vload[H](zec0)))
            vstore(yec2, ((vload[H](zec12, hsize)) + ((F64Vec(1.0)) - ((vload[H](zec8, hsize)) + (vload[H](yec1, - S32(1) + hsize))))) / (vload[H](zec0, hsize)), hsize)
            vstore(dsp.yec2_perm, vload[H](yec2_tmp, vsize))
            vstore(dsp.yec2_perm, vload[H](yec2_tmp, vsize + hsize), hsize)
            vstore(zec13, (vload[H](i_vec0, - S32(3))).cast[f64]())
            vstore(zec13, (vload[H](i_vec0, - S32(3) + hsize)).cast[f64](), hsize)
            vstore(yec3_tmp, vload[H](dsp.yec3_perm))
            vstore(yec3_tmp, vload[H](dsp.yec3_perm, hsize), hsize)
            vstore(yec3, (vload[H](yec0)) * ((vload[H](yec0)) + (F64Vec(-2.0))))
            vstore(yec3, (vload[H](yec0, hsize)) * ((vload[H](yec0, hsize)) + (F64Vec(-2.0))), hsize)
            vstore(dsp.yec3_perm, vload[H](yec3_tmp, vsize))
            vstore(dsp.yec3_perm, vload[H](yec3_tmp, vsize + hsize), hsize)
            vstore(yec4_tmp, vload[H](dsp.yec4_perm))
            vstore(yec4_tmp, vload[H](dsp.yec4_perm, hsize), hsize)
            vstore(yec4, ((vload[H](yec3)) - (vload[H](yec3, - S32(1)))) / (vload[H](zec0)))
            vstore(yec4, ((vload[H](yec3, hsize)) - (vload[H](yec3, - S32(1) + hsize))) / (vload[H](zec0, hsize)), hsize)
            vstore(dsp.yec4_perm, vload[H](yec4_tmp, vsize))
            vstore(dsp.yec4_perm, vload[H](yec4_tmp, vsize + hsize), hsize)
            vstore(yec5_tmp, vload[H](dsp.yec5_perm))
            vstore(yec5_tmp, vload[H](dsp.yec5_perm, hsize), hsize)
            vstore(yec5, ((vload[H](yec4)) - (vload[H](yec4, - S32(1)))) / (vload[H](zec0)))
            vstore(yec5, ((vload[H](yec4, hsize)) - (vload[H](yec4, - S32(1) + hsize))) / (vload[H](zec0, hsize)), hsize)
            vstore(dsp.yec5_perm, vload[H](yec5_tmp, vsize))
            vstore(dsp.yec5_perm, vload[H](yec5_tmp, vsize + hsize), hsize)
            vstore(zec14, (F64Vec(2.0)) * (vload[H](rec3)))
            vstore(zec14, (F64Vec(2.0)) * (vload[H](rec3, hsize)), hsize)
            vstore(zec15, (vload[H](zec14)) + (F64Vec(-1.0)))
            vstore(zec15, (vload[H](zec14, hsize)) + (F64Vec(-1.0)), hsize)
            vstore(yec6_tmp, vload[H](dsp.yec6_perm))
            vstore(yec6_tmp, vload[H](dsp.yec6_perm, hsize), hsize)
            vstore(yec6, pow_unrolled[2](vload[H](zec15)))
            vstore(yec6, pow_unrolled[2](vload[H](zec15, hsize)), hsize)
            vstore(dsp.yec6_perm, vload[H](yec6_tmp, vsize))
            vstore(dsp.yec6_perm, vload[H](yec6_tmp, vsize + hsize), hsize)
            vstore(zec16, pow_unrolled[3](vload[H](zec15)))
            vstore(zec16, pow_unrolled[3](vload[H](zec15, hsize)), hsize)
            vstore(yec7_tmp, vload[H](dsp.yec7_perm))
            vstore(yec7_tmp, vload[H](dsp.yec7_perm, hsize), hsize)
            vstore(yec7, (vload[H](zec16)) + ((F64Vec(1.0)) - (vload[H](zec14))))
            vstore(yec7, (vload[H](zec16, hsize)) + ((F64Vec(1.0)) - (vload[H](zec14, hsize))), hsize)
            vstore(dsp.yec7_perm, vload[H](yec7_tmp, vsize))
            vstore(dsp.yec7_perm, vload[H](yec7_tmp, vsize + hsize), hsize)
            vstore(yec8_tmp, vload[H](dsp.yec8_perm))
            vstore(yec8_tmp, vload[H](dsp.yec8_perm, hsize), hsize)
            vstore(yec8, ((vload[H](zec16)) + ((F64Vec(1.0)) - ((vload[H](zec14)) + (vload[H](yec7, - S32(1)))))) / (vload[H](zec2)))
            vstore(yec8, ((vload[H](zec16, hsize)) + ((F64Vec(1.0)) - ((vload[H](zec14, hsize)) + (vload[H](yec7, - S32(1) + hsize))))) / (vload[H](zec2, hsize)), hsize)
            vstore(dsp.yec8_perm, vload[H](yec8_tmp, vsize))
            vstore(dsp.yec8_perm, vload[H](yec8_tmp, vsize + hsize), hsize)
            vstore(yec9_tmp, vload[H](dsp.yec9_perm))
            vstore(yec9_tmp, vload[H](dsp.yec9_perm, hsize), hsize)
            vstore(yec9, (vload[H](yec6)) * ((vload[H](yec6)) + (F64Vec(-2.0))))
            vstore(yec9, (vload[H](yec6, hsize)) * ((vload[H](yec6, hsize)) + (F64Vec(-2.0))), hsize)
            vstore(dsp.yec9_perm, vload[H](yec9_tmp, vsize))
            vstore(dsp.yec9_perm, vload[H](yec9_tmp, vsize + hsize), hsize)
            vstore(yec10_tmp, vload[H](dsp.yec10_perm))
            vstore(yec10_tmp, vload[H](dsp.yec10_perm, hsize), hsize)
            vstore(yec10, ((vload[H](yec9)) - (vload[H](yec9, - S32(1)))) / (vload[H](zec2)))
            vstore(yec10, ((vload[H](yec9, hsize)) - (vload[H](yec9, - S32(1) + hsize))) / (vload[H](zec2, hsize)), hsize)
            vstore(dsp.yec10_perm, vload[H](yec10_tmp, vsize))
            vstore(dsp.yec10_perm, vload[H](yec10_tmp, vsize + hsize), hsize)
            vstore(yec11_tmp, vload[H](dsp.yec11_perm))
            vstore(yec11_tmp, vload[H](dsp.yec11_perm, hsize), hsize)
            vstore(yec11, ((vload[H](yec10)) - (vload[H](yec10, - S32(1)))) / (vload[H](zec2)))
            vstore(yec11, ((vload[H](yec10, hsize)) - (vload[H](yec10, - S32(1) + hsize))) / (vload[H](zec2, hsize)), hsize)
            vstore(dsp.yec11_perm, vload[H](yec11_tmp, vsize))
            vstore(dsp.yec11_perm, vload[H](yec11_tmp, vsize + hsize), hsize)
            vstore(zec17, (F64Vec(2.0)) * (vload[H](rec4)))
            vstore(zec17, (F64Vec(2.0)) * (vload[H](rec4, hsize)), hsize)
            vstore(zec18, (vload[H](zec17)) + (F64Vec(-1.0)))
            vstore(zec18, (vload[H](zec17, hsize)) + (F64Vec(-1.0)), hsize)
            vstore(yec12_tmp, vload[H](dsp.yec12_perm))
            vstore(yec12_tmp, vload[H](dsp.yec12_perm, hsize), hsize)
            vstore(yec12, pow_unrolled[2](vload[H](zec18)))
            vstore(yec12, pow_unrolled[2](vload[H](zec18, hsize)), hsize)
            vstore(dsp.yec12_perm, vload[H](yec12_tmp, vsize))
            vstore(dsp.yec12_perm, vload[H](yec12_tmp, vsize + hsize), hsize)
            vstore(zec19, pow_unrolled[3](vload[H](zec18)))
            vstore(zec19, pow_unrolled[3](vload[H](zec18, hsize)), hsize)
            vstore(yec13_tmp, vload[H](dsp.yec13_perm))
            vstore(yec13_tmp, vload[H](dsp.yec13_perm, hsize), hsize)
            vstore(yec13, (vload[H](zec19)) + ((F64Vec(1.0)) - (vload[H](zec17))))
            vstore(yec13, (vload[H](zec19, hsize)) + ((F64Vec(1.0)) - (vload[H](zec17, hsize))), hsize)
            vstore(dsp.yec13_perm, vload[H](yec13_tmp, vsize))
            vstore(dsp.yec13_perm, vload[H](yec13_tmp, vsize + hsize), hsize)
            vstore(yec14_tmp, vload[H](dsp.yec14_perm))
            vstore(yec14_tmp, vload[H](dsp.yec14_perm, hsize), hsize)
            vstore(yec14, ((vload[H](zec19)) + ((F64Vec(1.0)) - ((vload[H](zec17)) + (vload[H](yec13, - S32(1)))))) / (vload[H](zec4)))
            vstore(yec14, ((vload[H](zec19, hsize)) + ((F64Vec(1.0)) - ((vload[H](zec17, hsize)) + (vload[H](yec13, - S32(1) + hsize))))) / (vload[H](zec4, hsize)), hsize)
            vstore(dsp.yec14_perm, vload[H](yec14_tmp, vsize))
            vstore(dsp.yec14_perm, vload[H](yec14_tmp, vsize + hsize), hsize)
            vstore(yec15_tmp, vload[H](dsp.yec15_perm))
            vstore(yec15_tmp, vload[H](dsp.yec15_perm, hsize), hsize)
            vstore(yec15, (vload[H](yec12)) * ((vload[H](yec12)) + (F64Vec(-2.0))))
            vstore(yec15, (vload[H](yec12, hsize)) * ((vload[H](yec12, hsize)) + (F64Vec(-2.0))), hsize)
            vstore(dsp.yec15_perm, vload[H](yec15_tmp, vsize))
            vstore(dsp.yec15_perm, vload[H](yec15_tmp, vsize + hsize), hsize)
            vstore(yec16_tmp, vload[H](dsp.yec16_perm))
            vstore(yec16_tmp, vload[H](dsp.yec16_perm, hsize), hsize)
            vstore(yec16, ((vload[H](yec15)) - (vload[H](yec15, - S32(1)))) / (vload[H](zec4)))
            vstore(yec16, ((vload[H](yec15, hsize)) - (vload[H](yec15, - S32(1) + hsize))) / (vload[H](zec4, hsize)), hsize)
            vstore(dsp.yec16_perm, vload[H](yec16_tmp, vsize))
            vstore(dsp.yec16_perm, vload[H](yec16_tmp, vsize + hsize), hsize)
            vstore(yec17_tmp, vload[H](dsp.yec17_perm))
            vstore(yec17_tmp, vload[H](dsp.yec17_perm, hsize), hsize)
            vstore(yec17, ((vload[H](yec16)) - (vload[H](yec16, - S32(1)))) / (vload[H](zec4)))
            vstore(yec17, ((vload[H](yec16, hsize)) - (vload[H](yec16, - S32(1) + hsize))) / (vload[H](zec4, hsize)), hsize)
            vstore(dsp.yec17_perm, vload[H](yec17_tmp, vsize))
            vstore(dsp.yec17_perm, vload[H](yec17_tmp, vsize + hsize), hsize)
            vstore(zec20, (vload[H](rec0)) * ((vload[H](input0)).cast[f64]() if i_slow12 else (((F64Vec(0.049922035)) * (vload[H](rec6))) + ((F64Vec(0.050612699)) * (vload[H](rec6, - S32(2))))) - (((F64Vec(0.095993537)) * (vload[H](rec6, - S32(1)))) + ((F64Vec(0.004408786)) * (vload[H](rec6, - S32(3))))) if i_slow18 else vload[H](zec6) if i_slow13 else (F64Vec(0.3333333333333333)) * ((vload[H](rec0)) * ((((F64Vec(dsp.const5)) * (((vload[H](zec13)) * ((vload[H](yec5)) - (vload[H](yec5, - S32(1))))) / (vload[H](zec0))) if i_slow17 else (F64Vec(dsp.const4)) * (((vload[H](zec11)) * ((vload[H](yec2)) - (vload[H](yec2, - S32(1))))) / (vload[H](zec0))) if i_slow15 else (F64Vec(dsp.const3)) * (((vload[H](zec10)) * ((vload[H](yec0)) - (vload[H](yec0, - S32(1))))) / (vload[H](zec0))) if i_slow16 else vload[H](zec9)) + ((F64Vec(dsp.const5)) * (((vload[H](zec13)) * ((vload[H](yec11)) - (vload[H](yec11, - S32(1))))) / (vload[H](zec2))) if i_slow17 else (F64Vec(dsp.const4)) * (((vload[H](zec11)) * ((vload[H](yec8)) - (vload[H](yec8, - S32(1))))) / (vload[H](zec2))) if i_slow15 else (F64Vec(dsp.const3)) * (((vload[H](zec10)) * ((vload[H](yec6)) - (vload[H](yec6, - S32(1))))) / (vload[H](zec2))) if i_slow16 else vload[H](zec15))) + ((F64Vec(dsp.const5)) * (((vload[H](zec13)) * ((vload[H](yec17)) - (vload[H](yec17, - S32(1))))) / (vload[H](zec4))) if i_slow17 else (F64Vec(dsp.const4)) * (((vload[H](zec11)) * ((vload[H](yec14)) - (vload[H](yec14, - S32(1))))) / (vload[H](zec4))) if i_slow15 else (F64Vec(dsp.const3)) * (((vload[H](zec10)) * ((vload[H](yec12)) - (vload[H](yec12, - S32(1))))) / (vload[H](zec4))) if i_slow16 else vload[H](zec18))))))
            vstore(zec20, (vload[H](rec0, hsize)) * ((vload[H](input0, hsize)).cast[f64]() if i_slow12 else (((F64Vec(0.049922035)) * (vload[H](rec6, hsize))) + ((F64Vec(0.050612699)) * (vload[H](rec6, - S32(2) + hsize)))) - (((F64Vec(0.095993537)) * (vload[H](rec6, - S32(1) + hsize))) + ((F64Vec(0.004408786)) * (vload[H](rec6, - S32(3) + hsize)))) if i_slow18 else vload[H](zec6, hsize) if i_slow13 else (F64Vec(0.3333333333333333)) * ((vload[H](rec0, hsize)) * ((((F64Vec(dsp.const5)) * (((vload[H](zec13, hsize)) * ((vload[H](yec5, hsize)) - (vload[H](yec5, - S32(1) + hsize)))) / (vload[H](zec0, hsize))) if i_slow17 else (F64Vec(dsp.const4)) * (((vload[H](zec11, hsize)) * ((vload[H](yec2, hsize)) - (vload[H](yec2, - S32(1) + hsize)))) / (vload[H](zec0, hsize))) if i_slow15 else (F64Vec(dsp.const3)) * (((vload[H](zec10, hsize)) * ((vload[H](yec0, hsize)) - (vload[H](yec0, - S32(1) + hsize)))) / (vload[H](zec0, hsize))) if i_slow16 else vload[H](zec9, hsize)) + ((F64Vec(dsp.const5)) * (((vload[H](zec13, hsize)) * ((vload[H](yec11, hsize)) - (vload[H](yec11, - S32(1) + hsize)))) / (vload[H](zec2, hsize))) if i_slow17 else (F64Vec(dsp.const4)) * (((vload[H](zec11, hsize)) * ((vload[H](yec8, hsize)) - (vload[H](yec8, - S32(1) + hsize)))) / (vload[H](zec2, hsize))) if i_slow15 else (F64Vec(dsp.const3)) * (((vload[H](zec10, hsize)) * ((vload[H](yec6, hsize)) - (vload[H](yec6, - S32(1) + hsize)))) / (vload[H](zec2, hsize))) if i_slow16 else vload[H](zec15, hsize))) + ((F64Vec(dsp.const5)) * (((vload[H](zec13, hsize)) * ((vload[H](yec17, hsize)) - (vload[H](yec17, - S32(1) + hsize)))) / (vload[H](zec4, hsize))) if i_slow17 else (F64Vec(dsp.const4)) * (((vload[H](zec11, hsize)) * ((vload[H](yec14, hsize)) - (vload[H](yec14, - S32(1) + hsize)))) / (vload[H](zec4, hsize))) if i_slow15 else (F64Vec(dsp.const3)) * (((vload[H](zec10, hsize)) * ((vload[H](yec12, hsize)) - (vload[H](yec12, - S32(1) + hsize)))) / (vload[H](zec4, hsize))) if i_slow16 else vload[H](zec18, hsize))))), hsize)
            vstore(zec21, F64Vec(0.0) if i_slow11 else vload[H](zec20))
            vstore(zec21, F64Vec(0.0) if i_slow11 else vload[H](zec20, hsize), hsize)
            vstore(zec22, (vload(rec8)) + (vload(rec7)))
            vstore(zec22, (vload(rec8, hsize)) + (vload(rec7, hsize)), hsize)
            dsp.hbargraph0 = FaustFloat(zec22[vsize - S32(1)])
            vstore(zec23, (F64Vec(dsp.const0)) * ((F64Vec(slow19)) + ((F64Vec(slow20)) * ((vload[H](rec7)) + (F64Vec(1.0))))))
            vstore(zec23, (F64Vec(dsp.const0)) * ((F64Vec(slow19)) + ((F64Vec(slow20)) * ((vload[H](rec7, hsize)) + (F64Vec(1.0))))), hsize)
            vstore(i_zec24, ((vload(zec23)).cast[s32]()).join((vload(zec23, hsize)).cast[s32]()))
            vstore(zec25, (vload[H](i_zec24)).cast[f64]())
            vstore(zec25, (vload[H](i_zec24, hsize)).cast[f64](), hsize)
            dsp.yec18_idx = ((dsp.yec18_idx) + (dsp.yec18_idx_save)) & (S32(4095))
            vstore(rec9_tmp, vload[H](dsp.rec9_perm))
            vstore(rec9_tmp, vload[H](dsp.rec9_perm, hsize), hsize)
            comptime for i in range(vsize):
                dsp.yec18[((i) + (dsp.yec18_idx)) & (S32(4095))] = ((slow9) * (rec9[unsafe_offset = (i) - (S32(1))])) - (zec22[i])
                rec9[unsafe_offset = i] = ((dsp.yec18[(((i) + (dsp.yec18_idx)) - ((i_zec24[i]) & (S32(2047)))) & (S32(4095))]) * ((zec25[i]) + ((1.0) - (zec23[i])))) + (((zec23[i]) - (zec25[i])) * (dsp.yec18[(((i) + (dsp.yec18_idx)) - (((i_zec24[i]) + (S32(1))) & (S32(2047)))) & (S32(4095))]))
            dsp.yec18_idx_save = vsize
            vstore(dsp.rec9_perm, vload[H](rec9_tmp, vsize))
            vstore(dsp.rec9_perm, vload[H](rec9_tmp, vsize + hsize), hsize)
            vstore(rec15_tmp, vload[H](dsp.rec15_perm))
            vstore(rec15_tmp, vload[H](dsp.rec15_perm, hsize), hsize)
            vstore(rec16_tmp, vload[H](dsp.rec16_perm))
            vstore(rec16_tmp, vload[H](dsp.rec16_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec15[unsafe_offset = i] = ((slow22) * (rec16[unsafe_offset = (i) - (S32(1))])) + ((slow23) * (rec15[unsafe_offset = (i) - (S32(1))]))
                rec16[unsafe_offset = i] = ((zec7[i]) + ((slow23) * (rec16[unsafe_offset = (i) - (S32(1))]))) - ((slow22) * (rec15[unsafe_offset = (i) - (S32(1))]))
            vstore(dsp.rec15_perm, vload[H](rec15_tmp, vsize))
            vstore(dsp.rec15_perm, vload[H](rec15_tmp, vsize + hsize), hsize)
            vstore(dsp.rec16_perm, vload[H](rec16_tmp, vsize))
            vstore(dsp.rec16_perm, vload[H](rec16_tmp, vsize + hsize), hsize)
            vstore(zec26, vload[H](zec20) if i_slow11 else (F64Vec(0.5)) * ((vload[H](zec22)) + ((vload[H](rec9)) * (F64Vec(slow27)))))
            vstore(zec26, vload[H](zec20, hsize) if i_slow11 else (F64Vec(0.5)) * ((vload[H](zec22, hsize)) + ((vload[H](rec9, hsize)) * (F64Vec(slow27)))), hsize)
            vstore(zec27, F64Vec(0.0) if i_slow25 else vload[H](zec26))
            vstore(zec27, F64Vec(0.0) if i_slow25 else vload[H](zec26, hsize), hsize)
            vstore(zec28, (F64Vec(slow34)) - ((F64Vec(slow35)) * ((F64Vec(1.0)) - (vload[H](rec15)))))
            vstore(zec28, (F64Vec(slow34)) - ((F64Vec(slow35)) * ((F64Vec(1.0)) - (vload[H](rec15, hsize)))), hsize)
            vstore(rec14_tmp, vload[H](dsp.rec14_perm))
            vstore(rec14_tmp, vload[H](dsp.rec14_perm, hsize), hsize)
            vstore(rec13_tmp, vload[H](dsp.rec13_perm))
            vstore(rec13_tmp, vload[H](dsp.rec13_perm, hsize), hsize)
            vstore(rec12_tmp, vload[H](dsp.rec12_perm))
            vstore(rec12_tmp, vload[H](dsp.rec12_perm, hsize), hsize)
            vstore(rec11_tmp, vload[H](dsp.rec11_perm))
            vstore(rec11_tmp, vload[H](dsp.rec11_perm, hsize), hsize)
            vstore(rec10_tmp, vload[H](dsp.rec10_perm))
            vstore(rec10_tmp, vload[H](dsp.rec10_perm, hsize), hsize)
            comptime for i in range(vsize):
                zec29[i] = (rec14[unsafe_offset = (i) - (S32(1))]) * (cos((slow32) * (zec28[i])))
                rec14[unsafe_offset = i] = ((((slow24) * (zec27[i])) + ((slow28) * (rec10[unsafe_offset = (i) - (S32(1))]))) + ((slow30) * (zec29[i]))) - ((slow36) * (rec14[unsafe_offset = (i) - (S32(2))]))
                zec30[i] = (rec13[unsafe_offset = (i) - (S32(1))]) * (cos((slow37) * (zec28[i])))
                rec13[unsafe_offset = i] = ((rec14[unsafe_offset = (i) - (S32(2))]) + ((slow36) * ((rec14[unsafe_offset = i]) - (rec13[unsafe_offset = (i) - (S32(2))])))) - ((slow30) * ((zec29[i]) - (zec30[i])))
                zec31[i] = (rec12[unsafe_offset = (i) - (S32(1))]) * (cos((slow38) * (zec28[i])))
                rec12[unsafe_offset = i] = ((rec13[unsafe_offset = (i) - (S32(2))]) + ((slow36) * ((rec13[unsafe_offset = i]) - (rec12[unsafe_offset = (i) - (S32(2))])))) - ((slow30) * ((zec30[i]) - (zec31[i])))
                zec32[i] = (rec11[unsafe_offset = (i) - (S32(1))]) * (cos((slow39) * (zec28[i])))
                rec11[unsafe_offset = i] = ((rec12[unsafe_offset = (i) - (S32(2))]) + ((slow36) * ((rec12[unsafe_offset = i]) - (rec11[unsafe_offset = (i) - (S32(2))])))) - ((slow30) * ((zec31[i]) - (zec32[i])))
                rec10[unsafe_offset = i] = ((rec11[unsafe_offset = (i) - (S32(2))]) + ((slow36) * (rec11[unsafe_offset = i]))) - ((slow30) * (zec32[i]))
            vstore(dsp.rec14_perm, vload[H](rec14_tmp, vsize))
            vstore(dsp.rec14_perm, vload[H](rec14_tmp, vsize + hsize), hsize)
            vstore(dsp.rec13_perm, vload[H](rec13_tmp, vsize))
            vstore(dsp.rec13_perm, vload[H](rec13_tmp, vsize + hsize), hsize)
            vstore(dsp.rec12_perm, vload[H](rec12_tmp, vsize))
            vstore(dsp.rec12_perm, vload[H](rec12_tmp, vsize + hsize), hsize)
            vstore(dsp.rec11_perm, vload[H](rec11_tmp, vsize))
            vstore(dsp.rec11_perm, vload[H](rec11_tmp, vsize + hsize), hsize)
            vstore(dsp.rec10_perm, vload[H](rec10_tmp, vsize))
            vstore(dsp.rec10_perm, vload[H](rec10_tmp, vsize + hsize), hsize)
            vstore(zec33, (F64Vec(slow10)) * (vload[H](zec21)))
            vstore(zec33, (F64Vec(slow10)) * (vload[H](zec21, hsize)), hsize)
            vstore(zec34, (F64Vec(dsp.const0)) * ((F64Vec(slow19)) + ((F64Vec(slow20)) * ((vload[H](rec8)) + (F64Vec(1.0))))))
            vstore(zec34, (F64Vec(dsp.const0)) * ((F64Vec(slow19)) + ((F64Vec(slow20)) * ((vload[H](rec8, hsize)) + (F64Vec(1.0))))), hsize)
            vstore(i_zec35, ((vload(zec34)).cast[s32]()).join((vload(zec34, hsize)).cast[s32]()))
            vstore(zec36, (vload[H](i_zec35)).cast[f64]())
            vstore(zec36, (vload[H](i_zec35, hsize)).cast[f64](), hsize)
            dsp.yec19_idx = ((dsp.yec19_idx) + (dsp.yec19_idx_save)) & (S32(4095))
            vstore(rec17_tmp, vload[H](dsp.rec17_perm))
            vstore(rec17_tmp, vload[H](dsp.rec17_perm, hsize), hsize)
            comptime for i in range(vsize):
                dsp.yec19[((i) + (dsp.yec19_idx)) & (S32(4095))] = ((slow9) * (rec17[unsafe_offset = (i) - (S32(1))])) - (zec33[i])
                rec17[unsafe_offset = i] = ((dsp.yec19[(((i) + (dsp.yec19_idx)) - ((i_zec35[i]) & (S32(2047)))) & (S32(4095))]) * ((zec36[i]) + ((1.0) - (zec34[i])))) + (((zec34[i]) - (zec36[i])) * (dsp.yec19[(((i) + (dsp.yec19_idx)) - (((i_zec35[i]) + (S32(1))) & (S32(2047)))) & (S32(4095))]))
            dsp.yec19_idx_save = vsize
            vstore(dsp.rec17_perm, vload[H](rec17_tmp, vsize))
            vstore(dsp.rec17_perm, vload[H](rec17_tmp, vsize + hsize), hsize)
            vstore(zec37, vload[H](zec20) if i_slow11 else (F64Vec(0.5)) * ((vload[H](zec33)) + ((vload[H](rec17)) * (F64Vec(slow27)))))
            vstore(zec37, vload[H](zec20, hsize) if i_slow11 else (F64Vec(0.5)) * ((vload[H](zec33, hsize)) + ((vload[H](rec17, hsize)) * (F64Vec(slow27)))), hsize)
            vstore(zec38, F64Vec(0.0) if i_slow25 else vload[H](zec37))
            vstore(zec38, F64Vec(0.0) if i_slow25 else vload[H](zec37, hsize), hsize)
            vstore(zec39, (F64Vec(slow34)) - ((F64Vec(slow35)) * ((F64Vec(1.0)) - (vload[H](rec16)))))
            vstore(zec39, (F64Vec(slow34)) - ((F64Vec(slow35)) * ((F64Vec(1.0)) - (vload[H](rec16, hsize)))), hsize)
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
            comptime for i in range(vsize):
                zec40[i] = (rec22[unsafe_offset = (i) - (S32(1))]) * (cos((slow32) * (zec39[i])))
                rec22[unsafe_offset = i] = ((((slow24) * (zec38[i])) + ((slow28) * (rec18[unsafe_offset = (i) - (S32(1))]))) + ((slow30) * (zec40[i]))) - ((slow36) * (rec22[unsafe_offset = (i) - (S32(2))]))
                zec41[i] = (rec21[unsafe_offset = (i) - (S32(1))]) * (cos((slow37) * (zec39[i])))
                rec21[unsafe_offset = i] = ((rec22[unsafe_offset = (i) - (S32(2))]) + ((slow36) * ((rec22[unsafe_offset = i]) - (rec21[unsafe_offset = (i) - (S32(2))])))) - ((slow30) * ((zec40[i]) - (zec41[i])))
                zec42[i] = (rec20[unsafe_offset = (i) - (S32(1))]) * (cos((slow38) * (zec39[i])))
                rec20[unsafe_offset = i] = ((rec21[unsafe_offset = (i) - (S32(2))]) + ((slow36) * ((rec21[unsafe_offset = i]) - (rec20[unsafe_offset = (i) - (S32(2))])))) - ((slow30) * ((zec41[i]) - (zec42[i])))
                zec43[i] = (rec19[unsafe_offset = (i) - (S32(1))]) * (cos((slow39) * (zec39[i])))
                rec19[unsafe_offset = i] = ((rec20[unsafe_offset = (i) - (S32(2))]) + ((slow36) * ((rec20[unsafe_offset = i]) - (rec19[unsafe_offset = (i) - (S32(2))])))) - ((slow30) * ((zec42[i]) - (zec43[i])))
                rec18[unsafe_offset = i] = ((rec19[unsafe_offset = (i) - (S32(2))]) + ((slow36) * (rec19[unsafe_offset = i]))) - ((slow30) * (zec43[i]))
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
            vstore(zec44, vload[H](zec26) if i_slow25 else ((F64Vec(slow24)) * ((vload[H](zec27)) * (F64Vec(slow41)))) + ((vload[H](rec10)) * (F64Vec(slow42))))
            vstore(zec44, vload[H](zec26, hsize) if i_slow25 else ((F64Vec(slow24)) * ((vload[H](zec27, hsize)) * (F64Vec(slow41)))) + ((vload[H](rec10, hsize)) * (F64Vec(slow42))), hsize)
            vstore(zec45, vload[H](zec37) if i_slow25 else ((F64Vec(slow24)) * ((F64Vec(slow41)) * (vload[H](zec38)))) + ((vload[H](rec18)) * (F64Vec(slow42))))
            vstore(zec45, vload[H](zec37, hsize) if i_slow25 else ((F64Vec(slow24)) * ((F64Vec(slow41)) * (vload[H](zec38, hsize)))) + ((vload[H](rec18, hsize)) * (F64Vec(slow42))), hsize)
            vstore(zec46, (vload[H](zec44)) + (vload[H](zec45)))
            vstore(zec46, (vload[H](zec44, hsize)) + (vload[H](zec45, hsize)), hsize)
            vstore(rec26_tmp, vload[H](dsp.rec26_perm))
            vstore(rec26_tmp, vload[H](dsp.rec26_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec26[unsafe_offset = i] = (zec46[i]) - ((dsp.const9) * (((dsp.const10) * (rec26[unsafe_offset = (i) - (S32(2))])) + ((dsp.const13) * (rec26[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec26_perm, vload[H](rec26_tmp, vsize))
            vstore(dsp.rec26_perm, vload[H](rec26_tmp, vsize + hsize), hsize)
            vstore(rec25_tmp, vload[H](dsp.rec25_perm))
            vstore(rec25_tmp, vload[H](dsp.rec25_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec25[unsafe_offset = i] = ((dsp.const9) * ((((dsp.const15) * (rec26[unsafe_offset = i])) + ((dsp.const16) * (rec26[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const15) * (rec26[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const17) * (((dsp.const18) * (rec25[unsafe_offset = (i) - (S32(2))])) + ((dsp.const19) * (rec25[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec25_perm, vload[H](rec25_tmp, vsize))
            vstore(dsp.rec25_perm, vload[H](rec25_tmp, vsize + hsize), hsize)
            vstore(rec24_tmp, vload[H](dsp.rec24_perm))
            vstore(rec24_tmp, vload[H](dsp.rec24_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec24[unsafe_offset = i] = ((dsp.const17) * ((((dsp.const21) * (rec25[unsafe_offset = i])) + ((dsp.const22) * (rec25[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const21) * (rec25[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const23) * (((dsp.const24) * (rec24[unsafe_offset = (i) - (S32(2))])) + ((dsp.const25) * (rec24[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec24_perm, vload[H](rec24_tmp, vsize))
            vstore(dsp.rec24_perm, vload[H](rec24_tmp, vsize + hsize), hsize)
            vstore(rec23_tmp, vload[H](dsp.rec23_perm))
            vstore(rec23_tmp, vload[H](dsp.rec23_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec23[unsafe_offset = i] = ((rec23[unsafe_offset = (i) - (S32(1))]) * (slow44)) + ((abs((dsp.const23) * ((((dsp.const28) * (rec24[unsafe_offset = i])) + ((dsp.const29) * (rec24[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const28) * (rec24[unsafe_offset = (i) - (S32(2))]))))) * (slow45))
            vstore(dsp.rec23_perm, vload[H](rec23_tmp, vsize))
            vstore(dsp.rec23_perm, vload[H](rec23_tmp, vsize + hsize), hsize)
            vstore(rec33_tmp, vload[H](dsp.rec33_perm))
            vstore(rec33_tmp, vload[H](dsp.rec33_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec33[unsafe_offset = i] = (zec46[i]) - ((dsp.const30) * (((dsp.const31) * (rec33[unsafe_offset = (i) - (S32(2))])) + ((dsp.const32) * (rec33[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec33_perm, vload[H](rec33_tmp, vsize))
            vstore(dsp.rec33_perm, vload[H](rec33_tmp, vsize + hsize), hsize)
            vstore(rec32_tmp, vload[H](dsp.rec32_perm))
            vstore(rec32_tmp, vload[H](dsp.rec32_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec32[unsafe_offset = i] = ((dsp.const30) * ((((dsp.const34) * (rec33[unsafe_offset = i])) + ((dsp.const35) * (rec33[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const34) * (rec33[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const36) * (((dsp.const37) * (rec32[unsafe_offset = (i) - (S32(2))])) + ((dsp.const38) * (rec32[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec32_perm, vload[H](rec32_tmp, vsize))
            vstore(dsp.rec32_perm, vload[H](rec32_tmp, vsize + hsize), hsize)
            vstore(rec31_tmp, vload[H](dsp.rec31_perm))
            vstore(rec31_tmp, vload[H](dsp.rec31_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec31[unsafe_offset = i] = ((dsp.const36) * ((((dsp.const39) * (rec32[unsafe_offset = i])) + ((dsp.const40) * (rec32[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const39) * (rec32[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const41) * (((dsp.const42) * (rec31[unsafe_offset = (i) - (S32(2))])) + ((dsp.const43) * (rec31[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec31_perm, vload[H](rec31_tmp, vsize))
            vstore(dsp.rec31_perm, vload[H](rec31_tmp, vsize + hsize), hsize)
            vstore(zec47, (F64Vec(dsp.const41)) * ((((F64Vec(dsp.const44)) * (vload[H](rec31))) + ((F64Vec(dsp.const45)) * (vload[H](rec31, - S32(1))))) + ((F64Vec(dsp.const44)) * (vload[H](rec31, - S32(2))))))
            vstore(zec47, (F64Vec(dsp.const41)) * ((((F64Vec(dsp.const44)) * (vload[H](rec31, hsize))) + ((F64Vec(dsp.const45)) * (vload[H](rec31, - S32(1) + hsize)))) + ((F64Vec(dsp.const44)) * (vload[H](rec31, - S32(2) + hsize)))), hsize)
            vstore(rec30_tmp, vload[H](dsp.rec30_perm))
            vstore(rec30_tmp, vload[H](dsp.rec30_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec30[unsafe_offset = i] = (zec47[i]) - ((dsp.const48) * (((dsp.const49) * (rec30[unsafe_offset = (i) - (S32(2))])) + ((dsp.const52) * (rec30[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec30_perm, vload[H](rec30_tmp, vsize))
            vstore(dsp.rec30_perm, vload[H](rec30_tmp, vsize + hsize), hsize)
            vstore(rec29_tmp, vload[H](dsp.rec29_perm))
            vstore(rec29_tmp, vload[H](dsp.rec29_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec29[unsafe_offset = i] = ((dsp.const48) * ((((dsp.const54) * (rec30[unsafe_offset = i])) + ((dsp.const55) * (rec30[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const54) * (rec30[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const56) * (((dsp.const57) * (rec29[unsafe_offset = (i) - (S32(2))])) + ((dsp.const58) * (rec29[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec29_perm, vload[H](rec29_tmp, vsize))
            vstore(dsp.rec29_perm, vload[H](rec29_tmp, vsize + hsize), hsize)
            vstore(rec28_tmp, vload[H](dsp.rec28_perm))
            vstore(rec28_tmp, vload[H](dsp.rec28_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec28[unsafe_offset = i] = ((dsp.const56) * ((((dsp.const60) * (rec29[unsafe_offset = i])) + ((dsp.const61) * (rec29[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const60) * (rec29[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const62) * (((dsp.const63) * (rec28[unsafe_offset = (i) - (S32(2))])) + ((dsp.const64) * (rec28[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec28_perm, vload[H](rec28_tmp, vsize))
            vstore(dsp.rec28_perm, vload[H](rec28_tmp, vsize + hsize), hsize)
            vstore(rec27_tmp, vload[H](dsp.rec27_perm))
            vstore(rec27_tmp, vload[H](dsp.rec27_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec27[unsafe_offset = i] = ((slow44) * (rec27[unsafe_offset = (i) - (S32(1))])) + ((slow45) * (abs((dsp.const62) * ((((dsp.const66) * (rec28[unsafe_offset = i])) + ((dsp.const67) * (rec28[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const66) * (rec28[unsafe_offset = (i) - (S32(2))]))))))
            vstore(dsp.rec27_perm, vload[H](rec27_tmp, vsize))
            vstore(dsp.rec27_perm, vload[H](rec27_tmp, vsize + hsize), hsize)
            vstore(rec40_tmp, vload[H](dsp.rec40_perm))
            vstore(rec40_tmp, vload[H](dsp.rec40_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec40[unsafe_offset = i] = (zec47[i]) - ((dsp.const68) * (((dsp.const69) * (rec40[unsafe_offset = (i) - (S32(2))])) + ((dsp.const70) * (rec40[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec40_perm, vload[H](rec40_tmp, vsize))
            vstore(dsp.rec40_perm, vload[H](rec40_tmp, vsize + hsize), hsize)
            vstore(rec39_tmp, vload[H](dsp.rec39_perm))
            vstore(rec39_tmp, vload[H](dsp.rec39_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec39[unsafe_offset = i] = ((dsp.const68) * ((((dsp.const72) * (rec40[unsafe_offset = i])) + ((dsp.const73) * (rec40[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const72) * (rec40[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const74) * (((dsp.const75) * (rec39[unsafe_offset = (i) - (S32(2))])) + ((dsp.const76) * (rec39[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec39_perm, vload[H](rec39_tmp, vsize))
            vstore(dsp.rec39_perm, vload[H](rec39_tmp, vsize + hsize), hsize)
            vstore(rec38_tmp, vload[H](dsp.rec38_perm))
            vstore(rec38_tmp, vload[H](dsp.rec38_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec38[unsafe_offset = i] = ((dsp.const74) * ((((dsp.const77) * (rec39[unsafe_offset = i])) + ((dsp.const78) * (rec39[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const77) * (rec39[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const79) * (((dsp.const80) * (rec38[unsafe_offset = (i) - (S32(2))])) + ((dsp.const81) * (rec38[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec38_perm, vload[H](rec38_tmp, vsize))
            vstore(dsp.rec38_perm, vload[H](rec38_tmp, vsize + hsize), hsize)
            vstore(zec48, (F64Vec(dsp.const79)) * ((((F64Vec(dsp.const82)) * (vload[H](rec38))) + ((F64Vec(dsp.const83)) * (vload[H](rec38, - S32(1))))) + ((F64Vec(dsp.const82)) * (vload[H](rec38, - S32(2))))))
            vstore(zec48, (F64Vec(dsp.const79)) * ((((F64Vec(dsp.const82)) * (vload[H](rec38, hsize))) + ((F64Vec(dsp.const83)) * (vload[H](rec38, - S32(1) + hsize)))) + ((F64Vec(dsp.const82)) * (vload[H](rec38, - S32(2) + hsize)))), hsize)
            vstore(rec37_tmp, vload[H](dsp.rec37_perm))
            vstore(rec37_tmp, vload[H](dsp.rec37_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec37[unsafe_offset = i] = (zec48[i]) - ((dsp.const86) * (((dsp.const87) * (rec37[unsafe_offset = (i) - (S32(2))])) + ((dsp.const90) * (rec37[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec37_perm, vload[H](rec37_tmp, vsize))
            vstore(dsp.rec37_perm, vload[H](rec37_tmp, vsize + hsize), hsize)
            vstore(rec36_tmp, vload[H](dsp.rec36_perm))
            vstore(rec36_tmp, vload[H](dsp.rec36_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec36[unsafe_offset = i] = ((dsp.const86) * ((((dsp.const92) * (rec37[unsafe_offset = i])) + ((dsp.const93) * (rec37[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const92) * (rec37[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const94) * (((dsp.const95) * (rec36[unsafe_offset = (i) - (S32(2))])) + ((dsp.const96) * (rec36[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec36_perm, vload[H](rec36_tmp, vsize))
            vstore(dsp.rec36_perm, vload[H](rec36_tmp, vsize + hsize), hsize)
            vstore(rec35_tmp, vload[H](dsp.rec35_perm))
            vstore(rec35_tmp, vload[H](dsp.rec35_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec35[unsafe_offset = i] = ((dsp.const94) * ((((dsp.const98) * (rec36[unsafe_offset = i])) + ((dsp.const99) * (rec36[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const98) * (rec36[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const100) * (((dsp.const101) * (rec35[unsafe_offset = (i) - (S32(2))])) + ((dsp.const102) * (rec35[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec35_perm, vload[H](rec35_tmp, vsize))
            vstore(dsp.rec35_perm, vload[H](rec35_tmp, vsize + hsize), hsize)
            vstore(rec34_tmp, vload[H](dsp.rec34_perm))
            vstore(rec34_tmp, vload[H](dsp.rec34_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec34[unsafe_offset = i] = ((slow44) * (rec34[unsafe_offset = (i) - (S32(1))])) + ((slow45) * (abs((dsp.const100) * ((((dsp.const104) * (rec35[unsafe_offset = i])) + ((dsp.const105) * (rec35[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const104) * (rec35[unsafe_offset = (i) - (S32(2))]))))))
            vstore(dsp.rec34_perm, vload[H](rec34_tmp, vsize))
            vstore(dsp.rec34_perm, vload[H](rec34_tmp, vsize + hsize), hsize)
            vstore(rec47_tmp, vload[H](dsp.rec47_perm))
            vstore(rec47_tmp, vload[H](dsp.rec47_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec47[unsafe_offset = i] = (zec48[i]) - ((dsp.const106) * (((dsp.const107) * (rec47[unsafe_offset = (i) - (S32(2))])) + ((dsp.const108) * (rec47[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec47_perm, vload[H](rec47_tmp, vsize))
            vstore(dsp.rec47_perm, vload[H](rec47_tmp, vsize + hsize), hsize)
            vstore(rec46_tmp, vload[H](dsp.rec46_perm))
            vstore(rec46_tmp, vload[H](dsp.rec46_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec46[unsafe_offset = i] = ((dsp.const106) * ((((dsp.const110) * (rec47[unsafe_offset = i])) + ((dsp.const111) * (rec47[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const110) * (rec47[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const112) * (((dsp.const113) * (rec46[unsafe_offset = (i) - (S32(2))])) + ((dsp.const114) * (rec46[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec46_perm, vload[H](rec46_tmp, vsize))
            vstore(dsp.rec46_perm, vload[H](rec46_tmp, vsize + hsize), hsize)
            vstore(rec45_tmp, vload[H](dsp.rec45_perm))
            vstore(rec45_tmp, vload[H](dsp.rec45_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec45[unsafe_offset = i] = ((dsp.const112) * ((((dsp.const115) * (rec46[unsafe_offset = i])) + ((dsp.const116) * (rec46[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const115) * (rec46[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const117) * (((dsp.const118) * (rec45[unsafe_offset = (i) - (S32(2))])) + ((dsp.const119) * (rec45[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec45_perm, vload[H](rec45_tmp, vsize))
            vstore(dsp.rec45_perm, vload[H](rec45_tmp, vsize + hsize), hsize)
            vstore(zec49, (F64Vec(dsp.const117)) * ((((F64Vec(dsp.const120)) * (vload[H](rec45))) + ((F64Vec(dsp.const121)) * (vload[H](rec45, - S32(1))))) + ((F64Vec(dsp.const120)) * (vload[H](rec45, - S32(2))))))
            vstore(zec49, (F64Vec(dsp.const117)) * ((((F64Vec(dsp.const120)) * (vload[H](rec45, hsize))) + ((F64Vec(dsp.const121)) * (vload[H](rec45, - S32(1) + hsize)))) + ((F64Vec(dsp.const120)) * (vload[H](rec45, - S32(2) + hsize)))), hsize)
            vstore(rec44_tmp, vload[H](dsp.rec44_perm))
            vstore(rec44_tmp, vload[H](dsp.rec44_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec44[unsafe_offset = i] = (zec49[i]) - ((dsp.const124) * (((dsp.const125) * (rec44[unsafe_offset = (i) - (S32(2))])) + ((dsp.const128) * (rec44[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec44_perm, vload[H](rec44_tmp, vsize))
            vstore(dsp.rec44_perm, vload[H](rec44_tmp, vsize + hsize), hsize)
            vstore(rec43_tmp, vload[H](dsp.rec43_perm))
            vstore(rec43_tmp, vload[H](dsp.rec43_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec43[unsafe_offset = i] = ((dsp.const124) * ((((dsp.const130) * (rec44[unsafe_offset = i])) + ((dsp.const131) * (rec44[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const130) * (rec44[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const132) * (((dsp.const133) * (rec43[unsafe_offset = (i) - (S32(2))])) + ((dsp.const134) * (rec43[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec43_perm, vload[H](rec43_tmp, vsize))
            vstore(dsp.rec43_perm, vload[H](rec43_tmp, vsize + hsize), hsize)
            vstore(rec42_tmp, vload[H](dsp.rec42_perm))
            vstore(rec42_tmp, vload[H](dsp.rec42_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec42[unsafe_offset = i] = ((dsp.const132) * ((((dsp.const136) * (rec43[unsafe_offset = i])) + ((dsp.const137) * (rec43[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const136) * (rec43[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const138) * (((dsp.const139) * (rec42[unsafe_offset = (i) - (S32(2))])) + ((dsp.const140) * (rec42[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec42_perm, vload[H](rec42_tmp, vsize))
            vstore(dsp.rec42_perm, vload[H](rec42_tmp, vsize + hsize), hsize)
            vstore(rec41_tmp, vload[H](dsp.rec41_perm))
            vstore(rec41_tmp, vload[H](dsp.rec41_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec41[unsafe_offset = i] = ((slow44) * (rec41[unsafe_offset = (i) - (S32(1))])) + ((slow45) * (abs((dsp.const138) * ((((dsp.const142) * (rec42[unsafe_offset = i])) + ((dsp.const143) * (rec42[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const142) * (rec42[unsafe_offset = (i) - (S32(2))]))))))
            vstore(dsp.rec41_perm, vload[H](rec41_tmp, vsize))
            vstore(dsp.rec41_perm, vload[H](rec41_tmp, vsize + hsize), hsize)
            vstore(rec54_tmp, vload[H](dsp.rec54_perm))
            vstore(rec54_tmp, vload[H](dsp.rec54_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec54[unsafe_offset = i] = (zec49[i]) - ((dsp.const144) * (((dsp.const145) * (rec54[unsafe_offset = (i) - (S32(2))])) + ((dsp.const146) * (rec54[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec54_perm, vload[H](rec54_tmp, vsize))
            vstore(dsp.rec54_perm, vload[H](rec54_tmp, vsize + hsize), hsize)
            vstore(rec53_tmp, vload[H](dsp.rec53_perm))
            vstore(rec53_tmp, vload[H](dsp.rec53_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec53[unsafe_offset = i] = ((dsp.const144) * ((((dsp.const148) * (rec54[unsafe_offset = i])) + ((dsp.const149) * (rec54[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const148) * (rec54[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const150) * (((dsp.const151) * (rec53[unsafe_offset = (i) - (S32(2))])) + ((dsp.const152) * (rec53[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec53_perm, vload[H](rec53_tmp, vsize))
            vstore(dsp.rec53_perm, vload[H](rec53_tmp, vsize + hsize), hsize)
            vstore(rec52_tmp, vload[H](dsp.rec52_perm))
            vstore(rec52_tmp, vload[H](dsp.rec52_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec52[unsafe_offset = i] = ((dsp.const150) * ((((dsp.const153) * (rec53[unsafe_offset = i])) + ((dsp.const154) * (rec53[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const153) * (rec53[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const155) * (((dsp.const156) * (rec52[unsafe_offset = (i) - (S32(2))])) + ((dsp.const157) * (rec52[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec52_perm, vload[H](rec52_tmp, vsize))
            vstore(dsp.rec52_perm, vload[H](rec52_tmp, vsize + hsize), hsize)
            vstore(zec50, (F64Vec(dsp.const155)) * ((((F64Vec(dsp.const158)) * (vload[H](rec52))) + ((F64Vec(dsp.const159)) * (vload[H](rec52, - S32(1))))) + ((F64Vec(dsp.const158)) * (vload[H](rec52, - S32(2))))))
            vstore(zec50, (F64Vec(dsp.const155)) * ((((F64Vec(dsp.const158)) * (vload[H](rec52, hsize))) + ((F64Vec(dsp.const159)) * (vload[H](rec52, - S32(1) + hsize)))) + ((F64Vec(dsp.const158)) * (vload[H](rec52, - S32(2) + hsize)))), hsize)
            vstore(rec51_tmp, vload[H](dsp.rec51_perm))
            vstore(rec51_tmp, vload[H](dsp.rec51_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec51[unsafe_offset = i] = (zec50[i]) - ((dsp.const162) * (((dsp.const163) * (rec51[unsafe_offset = (i) - (S32(2))])) + ((dsp.const166) * (rec51[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec51_perm, vload[H](rec51_tmp, vsize))
            vstore(dsp.rec51_perm, vload[H](rec51_tmp, vsize + hsize), hsize)
            vstore(rec50_tmp, vload[H](dsp.rec50_perm))
            vstore(rec50_tmp, vload[H](dsp.rec50_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec50[unsafe_offset = i] = ((dsp.const162) * ((((dsp.const168) * (rec51[unsafe_offset = i])) + ((dsp.const169) * (rec51[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const168) * (rec51[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const170) * (((dsp.const171) * (rec50[unsafe_offset = (i) - (S32(2))])) + ((dsp.const172) * (rec50[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec50_perm, vload[H](rec50_tmp, vsize))
            vstore(dsp.rec50_perm, vload[H](rec50_tmp, vsize + hsize), hsize)
            vstore(rec49_tmp, vload[H](dsp.rec49_perm))
            vstore(rec49_tmp, vload[H](dsp.rec49_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec49[unsafe_offset = i] = ((dsp.const170) * ((((dsp.const174) * (rec50[unsafe_offset = i])) + ((dsp.const175) * (rec50[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const174) * (rec50[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const176) * (((dsp.const177) * (rec49[unsafe_offset = (i) - (S32(2))])) + ((dsp.const178) * (rec49[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec49_perm, vload[H](rec49_tmp, vsize))
            vstore(dsp.rec49_perm, vload[H](rec49_tmp, vsize + hsize), hsize)
            vstore(rec48_tmp, vload[H](dsp.rec48_perm))
            vstore(rec48_tmp, vload[H](dsp.rec48_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec48[unsafe_offset = i] = ((slow44) * (rec48[unsafe_offset = (i) - (S32(1))])) + ((slow45) * (abs((dsp.const176) * ((((dsp.const180) * (rec49[unsafe_offset = i])) + ((dsp.const181) * (rec49[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const180) * (rec49[unsafe_offset = (i) - (S32(2))]))))))
            vstore(dsp.rec48_perm, vload[H](rec48_tmp, vsize))
            vstore(dsp.rec48_perm, vload[H](rec48_tmp, vsize + hsize), hsize)
            vstore(rec61_tmp, vload[H](dsp.rec61_perm))
            vstore(rec61_tmp, vload[H](dsp.rec61_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec61[unsafe_offset = i] = (zec50[i]) - ((dsp.const182) * (((dsp.const183) * (rec61[unsafe_offset = (i) - (S32(2))])) + ((dsp.const184) * (rec61[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec61_perm, vload[H](rec61_tmp, vsize))
            vstore(dsp.rec61_perm, vload[H](rec61_tmp, vsize + hsize), hsize)
            vstore(rec60_tmp, vload[H](dsp.rec60_perm))
            vstore(rec60_tmp, vload[H](dsp.rec60_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec60[unsafe_offset = i] = ((dsp.const182) * ((((dsp.const186) * (rec61[unsafe_offset = i])) + ((dsp.const187) * (rec61[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const186) * (rec61[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const188) * (((dsp.const189) * (rec60[unsafe_offset = (i) - (S32(2))])) + ((dsp.const190) * (rec60[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec60_perm, vload[H](rec60_tmp, vsize))
            vstore(dsp.rec60_perm, vload[H](rec60_tmp, vsize + hsize), hsize)
            vstore(rec59_tmp, vload[H](dsp.rec59_perm))
            vstore(rec59_tmp, vload[H](dsp.rec59_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec59[unsafe_offset = i] = ((dsp.const188) * ((((dsp.const191) * (rec60[unsafe_offset = i])) + ((dsp.const192) * (rec60[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const191) * (rec60[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const193) * (((dsp.const194) * (rec59[unsafe_offset = (i) - (S32(2))])) + ((dsp.const195) * (rec59[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec59_perm, vload[H](rec59_tmp, vsize))
            vstore(dsp.rec59_perm, vload[H](rec59_tmp, vsize + hsize), hsize)
            vstore(zec51, (F64Vec(dsp.const193)) * ((((F64Vec(dsp.const196)) * (vload[H](rec59))) + ((F64Vec(dsp.const197)) * (vload[H](rec59, - S32(1))))) + ((F64Vec(dsp.const196)) * (vload[H](rec59, - S32(2))))))
            vstore(zec51, (F64Vec(dsp.const193)) * ((((F64Vec(dsp.const196)) * (vload[H](rec59, hsize))) + ((F64Vec(dsp.const197)) * (vload[H](rec59, - S32(1) + hsize)))) + ((F64Vec(dsp.const196)) * (vload[H](rec59, - S32(2) + hsize)))), hsize)
            vstore(rec58_tmp, vload[H](dsp.rec58_perm))
            vstore(rec58_tmp, vload[H](dsp.rec58_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec58[unsafe_offset = i] = (zec51[i]) - ((dsp.const200) * (((dsp.const201) * (rec58[unsafe_offset = (i) - (S32(2))])) + ((dsp.const204) * (rec58[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec58_perm, vload[H](rec58_tmp, vsize))
            vstore(dsp.rec58_perm, vload[H](rec58_tmp, vsize + hsize), hsize)
            vstore(rec57_tmp, vload[H](dsp.rec57_perm))
            vstore(rec57_tmp, vload[H](dsp.rec57_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec57[unsafe_offset = i] = ((dsp.const200) * ((((dsp.const206) * (rec58[unsafe_offset = i])) + ((dsp.const207) * (rec58[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const206) * (rec58[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const208) * (((dsp.const209) * (rec57[unsafe_offset = (i) - (S32(2))])) + ((dsp.const210) * (rec57[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec57_perm, vload[H](rec57_tmp, vsize))
            vstore(dsp.rec57_perm, vload[H](rec57_tmp, vsize + hsize), hsize)
            vstore(rec56_tmp, vload[H](dsp.rec56_perm))
            vstore(rec56_tmp, vload[H](dsp.rec56_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec56[unsafe_offset = i] = ((dsp.const208) * ((((dsp.const212) * (rec57[unsafe_offset = i])) + ((dsp.const213) * (rec57[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const212) * (rec57[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const214) * (((dsp.const215) * (rec56[unsafe_offset = (i) - (S32(2))])) + ((dsp.const216) * (rec56[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec56_perm, vload[H](rec56_tmp, vsize))
            vstore(dsp.rec56_perm, vload[H](rec56_tmp, vsize + hsize), hsize)
            vstore(rec55_tmp, vload[H](dsp.rec55_perm))
            vstore(rec55_tmp, vload[H](dsp.rec55_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec55[unsafe_offset = i] = ((slow44) * (rec55[unsafe_offset = (i) - (S32(1))])) + ((slow45) * (abs((dsp.const214) * ((((dsp.const218) * (rec56[unsafe_offset = i])) + ((dsp.const219) * (rec56[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const218) * (rec56[unsafe_offset = (i) - (S32(2))]))))))
            vstore(dsp.rec55_perm, vload[H](rec55_tmp, vsize))
            vstore(dsp.rec55_perm, vload[H](rec55_tmp, vsize + hsize), hsize)
            vstore(rec68_tmp, vload[H](dsp.rec68_perm))
            vstore(rec68_tmp, vload[H](dsp.rec68_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec68[unsafe_offset = i] = (zec51[i]) - ((dsp.const220) * (((dsp.const221) * (rec68[unsafe_offset = (i) - (S32(2))])) + ((dsp.const222) * (rec68[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec68_perm, vload[H](rec68_tmp, vsize))
            vstore(dsp.rec68_perm, vload[H](rec68_tmp, vsize + hsize), hsize)
            vstore(rec67_tmp, vload[H](dsp.rec67_perm))
            vstore(rec67_tmp, vload[H](dsp.rec67_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec67[unsafe_offset = i] = ((dsp.const220) * ((((dsp.const224) * (rec68[unsafe_offset = i])) + ((dsp.const225) * (rec68[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const224) * (rec68[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const226) * (((dsp.const227) * (rec67[unsafe_offset = (i) - (S32(2))])) + ((dsp.const228) * (rec67[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec67_perm, vload[H](rec67_tmp, vsize))
            vstore(dsp.rec67_perm, vload[H](rec67_tmp, vsize + hsize), hsize)
            vstore(rec66_tmp, vload[H](dsp.rec66_perm))
            vstore(rec66_tmp, vload[H](dsp.rec66_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec66[unsafe_offset = i] = ((dsp.const226) * ((((dsp.const229) * (rec67[unsafe_offset = i])) + ((dsp.const230) * (rec67[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const229) * (rec67[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const231) * (((dsp.const232) * (rec66[unsafe_offset = (i) - (S32(2))])) + ((dsp.const233) * (rec66[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec66_perm, vload[H](rec66_tmp, vsize))
            vstore(dsp.rec66_perm, vload[H](rec66_tmp, vsize + hsize), hsize)
            vstore(zec52, (F64Vec(dsp.const231)) * ((((F64Vec(dsp.const234)) * (vload[H](rec66))) + ((F64Vec(dsp.const235)) * (vload[H](rec66, - S32(1))))) + ((F64Vec(dsp.const234)) * (vload[H](rec66, - S32(2))))))
            vstore(zec52, (F64Vec(dsp.const231)) * ((((F64Vec(dsp.const234)) * (vload[H](rec66, hsize))) + ((F64Vec(dsp.const235)) * (vload[H](rec66, - S32(1) + hsize)))) + ((F64Vec(dsp.const234)) * (vload[H](rec66, - S32(2) + hsize)))), hsize)
            vstore(rec65_tmp, vload[H](dsp.rec65_perm))
            vstore(rec65_tmp, vload[H](dsp.rec65_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec65[unsafe_offset = i] = (zec52[i]) - ((dsp.const238) * (((dsp.const239) * (rec65[unsafe_offset = (i) - (S32(2))])) + ((dsp.const242) * (rec65[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec65_perm, vload[H](rec65_tmp, vsize))
            vstore(dsp.rec65_perm, vload[H](rec65_tmp, vsize + hsize), hsize)
            vstore(rec64_tmp, vload[H](dsp.rec64_perm))
            vstore(rec64_tmp, vload[H](dsp.rec64_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec64[unsafe_offset = i] = ((dsp.const238) * ((((dsp.const244) * (rec65[unsafe_offset = i])) + ((dsp.const245) * (rec65[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const244) * (rec65[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const246) * (((dsp.const247) * (rec64[unsafe_offset = (i) - (S32(2))])) + ((dsp.const248) * (rec64[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec64_perm, vload[H](rec64_tmp, vsize))
            vstore(dsp.rec64_perm, vload[H](rec64_tmp, vsize + hsize), hsize)
            vstore(rec63_tmp, vload[H](dsp.rec63_perm))
            vstore(rec63_tmp, vload[H](dsp.rec63_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec63[unsafe_offset = i] = ((dsp.const246) * ((((dsp.const250) * (rec64[unsafe_offset = i])) + ((dsp.const251) * (rec64[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const250) * (rec64[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const252) * (((dsp.const253) * (rec63[unsafe_offset = (i) - (S32(2))])) + ((dsp.const254) * (rec63[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec63_perm, vload[H](rec63_tmp, vsize))
            vstore(dsp.rec63_perm, vload[H](rec63_tmp, vsize + hsize), hsize)
            vstore(rec62_tmp, vload[H](dsp.rec62_perm))
            vstore(rec62_tmp, vload[H](dsp.rec62_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec62[unsafe_offset = i] = ((slow44) * (rec62[unsafe_offset = (i) - (S32(1))])) + ((slow45) * (abs((dsp.const252) * ((((dsp.const256) * (rec63[unsafe_offset = i])) + ((dsp.const257) * (rec63[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const256) * (rec63[unsafe_offset = (i) - (S32(2))]))))))
            vstore(dsp.rec62_perm, vload[H](rec62_tmp, vsize))
            vstore(dsp.rec62_perm, vload[H](rec62_tmp, vsize + hsize), hsize)
            vstore(rec75_tmp, vload[H](dsp.rec75_perm))
            vstore(rec75_tmp, vload[H](dsp.rec75_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec75[unsafe_offset = i] = (zec52[i]) - ((dsp.const258) * (((dsp.const259) * (rec75[unsafe_offset = (i) - (S32(2))])) + ((dsp.const260) * (rec75[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec75_perm, vload[H](rec75_tmp, vsize))
            vstore(dsp.rec75_perm, vload[H](rec75_tmp, vsize + hsize), hsize)
            vstore(rec74_tmp, vload[H](dsp.rec74_perm))
            vstore(rec74_tmp, vload[H](dsp.rec74_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec74[unsafe_offset = i] = ((dsp.const258) * ((((dsp.const262) * (rec75[unsafe_offset = i])) + ((dsp.const263) * (rec75[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const262) * (rec75[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const264) * (((dsp.const265) * (rec74[unsafe_offset = (i) - (S32(2))])) + ((dsp.const266) * (rec74[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec74_perm, vload[H](rec74_tmp, vsize))
            vstore(dsp.rec74_perm, vload[H](rec74_tmp, vsize + hsize), hsize)
            vstore(rec73_tmp, vload[H](dsp.rec73_perm))
            vstore(rec73_tmp, vload[H](dsp.rec73_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec73[unsafe_offset = i] = ((dsp.const264) * ((((dsp.const267) * (rec74[unsafe_offset = i])) + ((dsp.const268) * (rec74[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const267) * (rec74[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const269) * (((dsp.const270) * (rec73[unsafe_offset = (i) - (S32(2))])) + ((dsp.const271) * (rec73[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec73_perm, vload[H](rec73_tmp, vsize))
            vstore(dsp.rec73_perm, vload[H](rec73_tmp, vsize + hsize), hsize)
            vstore(zec53, (F64Vec(dsp.const269)) * ((((F64Vec(dsp.const272)) * (vload[H](rec73))) + ((F64Vec(dsp.const273)) * (vload[H](rec73, - S32(1))))) + ((F64Vec(dsp.const272)) * (vload[H](rec73, - S32(2))))))
            vstore(zec53, (F64Vec(dsp.const269)) * ((((F64Vec(dsp.const272)) * (vload[H](rec73, hsize))) + ((F64Vec(dsp.const273)) * (vload[H](rec73, - S32(1) + hsize)))) + ((F64Vec(dsp.const272)) * (vload[H](rec73, - S32(2) + hsize)))), hsize)
            vstore(rec72_tmp, vload[H](dsp.rec72_perm))
            vstore(rec72_tmp, vload[H](dsp.rec72_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec72[unsafe_offset = i] = (zec53[i]) - ((dsp.const276) * (((dsp.const277) * (rec72[unsafe_offset = (i) - (S32(2))])) + ((dsp.const280) * (rec72[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec72_perm, vload[H](rec72_tmp, vsize))
            vstore(dsp.rec72_perm, vload[H](rec72_tmp, vsize + hsize), hsize)
            vstore(rec71_tmp, vload[H](dsp.rec71_perm))
            vstore(rec71_tmp, vload[H](dsp.rec71_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec71[unsafe_offset = i] = ((dsp.const276) * ((((dsp.const282) * (rec72[unsafe_offset = i])) + ((dsp.const283) * (rec72[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const282) * (rec72[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const284) * (((dsp.const285) * (rec71[unsafe_offset = (i) - (S32(2))])) + ((dsp.const286) * (rec71[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec71_perm, vload[H](rec71_tmp, vsize))
            vstore(dsp.rec71_perm, vload[H](rec71_tmp, vsize + hsize), hsize)
            vstore(rec70_tmp, vload[H](dsp.rec70_perm))
            vstore(rec70_tmp, vload[H](dsp.rec70_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec70[unsafe_offset = i] = ((dsp.const284) * ((((dsp.const288) * (rec71[unsafe_offset = i])) + ((dsp.const289) * (rec71[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const288) * (rec71[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const290) * (((dsp.const291) * (rec70[unsafe_offset = (i) - (S32(2))])) + ((dsp.const292) * (rec70[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec70_perm, vload[H](rec70_tmp, vsize))
            vstore(dsp.rec70_perm, vload[H](rec70_tmp, vsize + hsize), hsize)
            vstore(rec69_tmp, vload[H](dsp.rec69_perm))
            vstore(rec69_tmp, vload[H](dsp.rec69_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec69[unsafe_offset = i] = ((slow44) * (rec69[unsafe_offset = (i) - (S32(1))])) + ((slow45) * (abs((dsp.const290) * ((((dsp.const294) * (rec70[unsafe_offset = i])) + ((dsp.const295) * (rec70[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const294) * (rec70[unsafe_offset = (i) - (S32(2))]))))))
            vstore(dsp.rec69_perm, vload[H](rec69_tmp, vsize))
            vstore(dsp.rec69_perm, vload[H](rec69_tmp, vsize + hsize), hsize)
            vstore(rec82_tmp, vload[H](dsp.rec82_perm))
            vstore(rec82_tmp, vload[H](dsp.rec82_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec82[unsafe_offset = i] = (zec53[i]) - ((dsp.const296) * (((dsp.const297) * (rec82[unsafe_offset = (i) - (S32(2))])) + ((dsp.const298) * (rec82[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec82_perm, vload[H](rec82_tmp, vsize))
            vstore(dsp.rec82_perm, vload[H](rec82_tmp, vsize + hsize), hsize)
            vstore(rec81_tmp, vload[H](dsp.rec81_perm))
            vstore(rec81_tmp, vload[H](dsp.rec81_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec81[unsafe_offset = i] = ((dsp.const296) * ((((dsp.const300) * (rec82[unsafe_offset = i])) + ((dsp.const301) * (rec82[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const300) * (rec82[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const302) * (((dsp.const303) * (rec81[unsafe_offset = (i) - (S32(2))])) + ((dsp.const304) * (rec81[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec81_perm, vload[H](rec81_tmp, vsize))
            vstore(dsp.rec81_perm, vload[H](rec81_tmp, vsize + hsize), hsize)
            vstore(rec80_tmp, vload[H](dsp.rec80_perm))
            vstore(rec80_tmp, vload[H](dsp.rec80_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec80[unsafe_offset = i] = ((dsp.const302) * ((((dsp.const305) * (rec81[unsafe_offset = i])) + ((dsp.const306) * (rec81[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const305) * (rec81[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const307) * (((dsp.const308) * (rec80[unsafe_offset = (i) - (S32(2))])) + ((dsp.const309) * (rec80[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec80_perm, vload[H](rec80_tmp, vsize))
            vstore(dsp.rec80_perm, vload[H](rec80_tmp, vsize + hsize), hsize)
            vstore(zec54, (F64Vec(dsp.const307)) * ((((F64Vec(dsp.const310)) * (vload[H](rec80))) + ((F64Vec(dsp.const311)) * (vload[H](rec80, - S32(1))))) + ((F64Vec(dsp.const310)) * (vload[H](rec80, - S32(2))))))
            vstore(zec54, (F64Vec(dsp.const307)) * ((((F64Vec(dsp.const310)) * (vload[H](rec80, hsize))) + ((F64Vec(dsp.const311)) * (vload[H](rec80, - S32(1) + hsize)))) + ((F64Vec(dsp.const310)) * (vload[H](rec80, - S32(2) + hsize)))), hsize)
            vstore(rec79_tmp, vload[H](dsp.rec79_perm))
            vstore(rec79_tmp, vload[H](dsp.rec79_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec79[unsafe_offset = i] = (zec54[i]) - ((dsp.const314) * (((dsp.const315) * (rec79[unsafe_offset = (i) - (S32(2))])) + ((dsp.const318) * (rec79[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec79_perm, vload[H](rec79_tmp, vsize))
            vstore(dsp.rec79_perm, vload[H](rec79_tmp, vsize + hsize), hsize)
            vstore(rec78_tmp, vload[H](dsp.rec78_perm))
            vstore(rec78_tmp, vload[H](dsp.rec78_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec78[unsafe_offset = i] = ((dsp.const314) * ((((dsp.const320) * (rec79[unsafe_offset = i])) + ((dsp.const321) * (rec79[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const320) * (rec79[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const322) * (((dsp.const323) * (rec78[unsafe_offset = (i) - (S32(2))])) + ((dsp.const324) * (rec78[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec78_perm, vload[H](rec78_tmp, vsize))
            vstore(dsp.rec78_perm, vload[H](rec78_tmp, vsize + hsize), hsize)
            vstore(rec77_tmp, vload[H](dsp.rec77_perm))
            vstore(rec77_tmp, vload[H](dsp.rec77_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec77[unsafe_offset = i] = ((dsp.const322) * ((((dsp.const326) * (rec78[unsafe_offset = i])) + ((dsp.const327) * (rec78[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const326) * (rec78[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const328) * (((dsp.const329) * (rec77[unsafe_offset = (i) - (S32(2))])) + ((dsp.const330) * (rec77[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec77_perm, vload[H](rec77_tmp, vsize))
            vstore(dsp.rec77_perm, vload[H](rec77_tmp, vsize + hsize), hsize)
            vstore(rec76_tmp, vload[H](dsp.rec76_perm))
            vstore(rec76_tmp, vload[H](dsp.rec76_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec76[unsafe_offset = i] = ((slow44) * (rec76[unsafe_offset = (i) - (S32(1))])) + ((slow45) * (abs((dsp.const328) * ((((dsp.const332) * (rec77[unsafe_offset = i])) + ((dsp.const333) * (rec77[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const332) * (rec77[unsafe_offset = (i) - (S32(2))]))))))
            vstore(dsp.rec76_perm, vload[H](rec76_tmp, vsize))
            vstore(dsp.rec76_perm, vload[H](rec76_tmp, vsize + hsize), hsize)
            vstore(rec89_tmp, vload[H](dsp.rec89_perm))
            vstore(rec89_tmp, vload[H](dsp.rec89_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec89[unsafe_offset = i] = (zec54[i]) - ((dsp.const334) * (((dsp.const335) * (rec89[unsafe_offset = (i) - (S32(2))])) + ((dsp.const336) * (rec89[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec89_perm, vload[H](rec89_tmp, vsize))
            vstore(dsp.rec89_perm, vload[H](rec89_tmp, vsize + hsize), hsize)
            vstore(rec88_tmp, vload[H](dsp.rec88_perm))
            vstore(rec88_tmp, vload[H](dsp.rec88_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec88[unsafe_offset = i] = ((dsp.const334) * ((((dsp.const338) * (rec89[unsafe_offset = i])) + ((dsp.const339) * (rec89[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const338) * (rec89[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const340) * (((dsp.const341) * (rec88[unsafe_offset = (i) - (S32(2))])) + ((dsp.const342) * (rec88[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec88_perm, vload[H](rec88_tmp, vsize))
            vstore(dsp.rec88_perm, vload[H](rec88_tmp, vsize + hsize), hsize)
            vstore(rec87_tmp, vload[H](dsp.rec87_perm))
            vstore(rec87_tmp, vload[H](dsp.rec87_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec87[unsafe_offset = i] = ((dsp.const340) * ((((dsp.const343) * (rec88[unsafe_offset = i])) + ((dsp.const344) * (rec88[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const343) * (rec88[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const345) * (((dsp.const346) * (rec87[unsafe_offset = (i) - (S32(2))])) + ((dsp.const347) * (rec87[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec87_perm, vload[H](rec87_tmp, vsize))
            vstore(dsp.rec87_perm, vload[H](rec87_tmp, vsize + hsize), hsize)
            vstore(zec55, (F64Vec(dsp.const345)) * ((((F64Vec(dsp.const348)) * (vload[H](rec87))) + ((F64Vec(dsp.const349)) * (vload[H](rec87, - S32(1))))) + ((F64Vec(dsp.const348)) * (vload[H](rec87, - S32(2))))))
            vstore(zec55, (F64Vec(dsp.const345)) * ((((F64Vec(dsp.const348)) * (vload[H](rec87, hsize))) + ((F64Vec(dsp.const349)) * (vload[H](rec87, - S32(1) + hsize)))) + ((F64Vec(dsp.const348)) * (vload[H](rec87, - S32(2) + hsize)))), hsize)
            vstore(rec86_tmp, vload[H](dsp.rec86_perm))
            vstore(rec86_tmp, vload[H](dsp.rec86_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec86[unsafe_offset = i] = (zec55[i]) - ((dsp.const352) * (((dsp.const353) * (rec86[unsafe_offset = (i) - (S32(2))])) + ((dsp.const356) * (rec86[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec86_perm, vload[H](rec86_tmp, vsize))
            vstore(dsp.rec86_perm, vload[H](rec86_tmp, vsize + hsize), hsize)
            vstore(rec85_tmp, vload[H](dsp.rec85_perm))
            vstore(rec85_tmp, vload[H](dsp.rec85_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec85[unsafe_offset = i] = ((dsp.const352) * ((((dsp.const358) * (rec86[unsafe_offset = i])) + ((dsp.const359) * (rec86[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const358) * (rec86[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const360) * (((dsp.const361) * (rec85[unsafe_offset = (i) - (S32(2))])) + ((dsp.const362) * (rec85[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec85_perm, vload[H](rec85_tmp, vsize))
            vstore(dsp.rec85_perm, vload[H](rec85_tmp, vsize + hsize), hsize)
            vstore(rec84_tmp, vload[H](dsp.rec84_perm))
            vstore(rec84_tmp, vload[H](dsp.rec84_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec84[unsafe_offset = i] = ((dsp.const360) * ((((dsp.const364) * (rec85[unsafe_offset = i])) + ((dsp.const365) * (rec85[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const364) * (rec85[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const366) * (((dsp.const367) * (rec84[unsafe_offset = (i) - (S32(2))])) + ((dsp.const368) * (rec84[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec84_perm, vload[H](rec84_tmp, vsize))
            vstore(dsp.rec84_perm, vload[H](rec84_tmp, vsize + hsize), hsize)
            vstore(rec83_tmp, vload[H](dsp.rec83_perm))
            vstore(rec83_tmp, vload[H](dsp.rec83_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec83[unsafe_offset = i] = ((slow44) * (rec83[unsafe_offset = (i) - (S32(1))])) + ((slow45) * (abs((dsp.const366) * ((((dsp.const370) * (rec84[unsafe_offset = i])) + ((dsp.const371) * (rec84[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const370) * (rec84[unsafe_offset = (i) - (S32(2))]))))))
            vstore(dsp.rec83_perm, vload[H](rec83_tmp, vsize))
            vstore(dsp.rec83_perm, vload[H](rec83_tmp, vsize + hsize), hsize)
            vstore(rec96_tmp, vload[H](dsp.rec96_perm))
            vstore(rec96_tmp, vload[H](dsp.rec96_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec96[unsafe_offset = i] = (zec55[i]) - ((dsp.const372) * (((dsp.const373) * (rec96[unsafe_offset = (i) - (S32(2))])) + ((dsp.const374) * (rec96[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec96_perm, vload[H](rec96_tmp, vsize))
            vstore(dsp.rec96_perm, vload[H](rec96_tmp, vsize + hsize), hsize)
            vstore(rec95_tmp, vload[H](dsp.rec95_perm))
            vstore(rec95_tmp, vload[H](dsp.rec95_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec95[unsafe_offset = i] = ((dsp.const372) * ((((dsp.const376) * (rec96[unsafe_offset = i])) + ((dsp.const377) * (rec96[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const376) * (rec96[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const378) * (((dsp.const379) * (rec95[unsafe_offset = (i) - (S32(2))])) + ((dsp.const380) * (rec95[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec95_perm, vload[H](rec95_tmp, vsize))
            vstore(dsp.rec95_perm, vload[H](rec95_tmp, vsize + hsize), hsize)
            vstore(rec94_tmp, vload[H](dsp.rec94_perm))
            vstore(rec94_tmp, vload[H](dsp.rec94_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec94[unsafe_offset = i] = ((dsp.const378) * ((((dsp.const381) * (rec95[unsafe_offset = i])) + ((dsp.const382) * (rec95[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const381) * (rec95[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const383) * (((dsp.const384) * (rec94[unsafe_offset = (i) - (S32(2))])) + ((dsp.const385) * (rec94[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec94_perm, vload[H](rec94_tmp, vsize))
            vstore(dsp.rec94_perm, vload[H](rec94_tmp, vsize + hsize), hsize)
            vstore(zec56, (F64Vec(dsp.const383)) * ((((F64Vec(dsp.const386)) * (vload[H](rec94))) + ((F64Vec(dsp.const387)) * (vload[H](rec94, - S32(1))))) + ((F64Vec(dsp.const386)) * (vload[H](rec94, - S32(2))))))
            vstore(zec56, (F64Vec(dsp.const383)) * ((((F64Vec(dsp.const386)) * (vload[H](rec94, hsize))) + ((F64Vec(dsp.const387)) * (vload[H](rec94, - S32(1) + hsize)))) + ((F64Vec(dsp.const386)) * (vload[H](rec94, - S32(2) + hsize)))), hsize)
            vstore(rec93_tmp, vload[H](dsp.rec93_perm))
            vstore(rec93_tmp, vload[H](dsp.rec93_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec93[unsafe_offset = i] = (zec56[i]) - ((dsp.const390) * (((dsp.const391) * (rec93[unsafe_offset = (i) - (S32(2))])) + ((dsp.const394) * (rec93[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec93_perm, vload[H](rec93_tmp, vsize))
            vstore(dsp.rec93_perm, vload[H](rec93_tmp, vsize + hsize), hsize)
            vstore(rec92_tmp, vload[H](dsp.rec92_perm))
            vstore(rec92_tmp, vload[H](dsp.rec92_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec92[unsafe_offset = i] = ((dsp.const390) * ((((dsp.const396) * (rec93[unsafe_offset = i])) + ((dsp.const397) * (rec93[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const396) * (rec93[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const398) * (((dsp.const399) * (rec92[unsafe_offset = (i) - (S32(2))])) + ((dsp.const400) * (rec92[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec92_perm, vload[H](rec92_tmp, vsize))
            vstore(dsp.rec92_perm, vload[H](rec92_tmp, vsize + hsize), hsize)
            vstore(rec91_tmp, vload[H](dsp.rec91_perm))
            vstore(rec91_tmp, vload[H](dsp.rec91_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec91[unsafe_offset = i] = ((dsp.const398) * ((((dsp.const402) * (rec92[unsafe_offset = i])) + ((dsp.const403) * (rec92[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const402) * (rec92[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const404) * (((dsp.const405) * (rec91[unsafe_offset = (i) - (S32(2))])) + ((dsp.const406) * (rec91[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec91_perm, vload[H](rec91_tmp, vsize))
            vstore(dsp.rec91_perm, vload[H](rec91_tmp, vsize + hsize), hsize)
            vstore(rec90_tmp, vload[H](dsp.rec90_perm))
            vstore(rec90_tmp, vload[H](dsp.rec90_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec90[unsafe_offset = i] = ((slow44) * (rec90[unsafe_offset = (i) - (S32(1))])) + ((slow45) * (abs((dsp.const404) * ((((dsp.const408) * (rec91[unsafe_offset = i])) + ((dsp.const409) * (rec91[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const408) * (rec91[unsafe_offset = (i) - (S32(2))]))))))
            vstore(dsp.rec90_perm, vload[H](rec90_tmp, vsize))
            vstore(dsp.rec90_perm, vload[H](rec90_tmp, vsize + hsize), hsize)
            vstore(rec103_tmp, vload[H](dsp.rec103_perm))
            vstore(rec103_tmp, vload[H](dsp.rec103_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec103[unsafe_offset = i] = (zec56[i]) - ((dsp.const410) * (((dsp.const411) * (rec103[unsafe_offset = (i) - (S32(2))])) + ((dsp.const412) * (rec103[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec103_perm, vload[H](rec103_tmp, vsize))
            vstore(dsp.rec103_perm, vload[H](rec103_tmp, vsize + hsize), hsize)
            vstore(rec102_tmp, vload[H](dsp.rec102_perm))
            vstore(rec102_tmp, vload[H](dsp.rec102_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec102[unsafe_offset = i] = ((dsp.const410) * ((((dsp.const414) * (rec103[unsafe_offset = i])) + ((dsp.const415) * (rec103[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const414) * (rec103[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const416) * (((dsp.const417) * (rec102[unsafe_offset = (i) - (S32(2))])) + ((dsp.const418) * (rec102[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec102_perm, vload[H](rec102_tmp, vsize))
            vstore(dsp.rec102_perm, vload[H](rec102_tmp, vsize + hsize), hsize)
            vstore(rec101_tmp, vload[H](dsp.rec101_perm))
            vstore(rec101_tmp, vload[H](dsp.rec101_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec101[unsafe_offset = i] = ((dsp.const416) * ((((dsp.const419) * (rec102[unsafe_offset = i])) + ((dsp.const420) * (rec102[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const419) * (rec102[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const421) * (((dsp.const422) * (rec101[unsafe_offset = (i) - (S32(2))])) + ((dsp.const423) * (rec101[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec101_perm, vload[H](rec101_tmp, vsize))
            vstore(dsp.rec101_perm, vload[H](rec101_tmp, vsize + hsize), hsize)
            vstore(zec57, (F64Vec(dsp.const421)) * ((((F64Vec(dsp.const424)) * (vload[H](rec101))) + ((F64Vec(dsp.const425)) * (vload[H](rec101, - S32(1))))) + ((F64Vec(dsp.const424)) * (vload[H](rec101, - S32(2))))))
            vstore(zec57, (F64Vec(dsp.const421)) * ((((F64Vec(dsp.const424)) * (vload[H](rec101, hsize))) + ((F64Vec(dsp.const425)) * (vload[H](rec101, - S32(1) + hsize)))) + ((F64Vec(dsp.const424)) * (vload[H](rec101, - S32(2) + hsize)))), hsize)
            vstore(rec100_tmp, vload[H](dsp.rec100_perm))
            vstore(rec100_tmp, vload[H](dsp.rec100_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec100[unsafe_offset = i] = (zec57[i]) - ((dsp.const428) * (((dsp.const429) * (rec100[unsafe_offset = (i) - (S32(2))])) + ((dsp.const432) * (rec100[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec100_perm, vload[H](rec100_tmp, vsize))
            vstore(dsp.rec100_perm, vload[H](rec100_tmp, vsize + hsize), hsize)
            vstore(rec99_tmp, vload[H](dsp.rec99_perm))
            vstore(rec99_tmp, vload[H](dsp.rec99_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec99[unsafe_offset = i] = ((dsp.const428) * ((((dsp.const434) * (rec100[unsafe_offset = i])) + ((dsp.const435) * (rec100[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const434) * (rec100[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const436) * (((dsp.const437) * (rec99[unsafe_offset = (i) - (S32(2))])) + ((dsp.const438) * (rec99[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec99_perm, vload[H](rec99_tmp, vsize))
            vstore(dsp.rec99_perm, vload[H](rec99_tmp, vsize + hsize), hsize)
            vstore(rec98_tmp, vload[H](dsp.rec98_perm))
            vstore(rec98_tmp, vload[H](dsp.rec98_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec98[unsafe_offset = i] = ((dsp.const436) * ((((dsp.const440) * (rec99[unsafe_offset = i])) + ((dsp.const441) * (rec99[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const440) * (rec99[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const442) * (((dsp.const443) * (rec98[unsafe_offset = (i) - (S32(2))])) + ((dsp.const444) * (rec98[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec98_perm, vload[H](rec98_tmp, vsize))
            vstore(dsp.rec98_perm, vload[H](rec98_tmp, vsize + hsize), hsize)
            vstore(rec97_tmp, vload[H](dsp.rec97_perm))
            vstore(rec97_tmp, vload[H](dsp.rec97_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec97[unsafe_offset = i] = ((slow44) * (rec97[unsafe_offset = (i) - (S32(1))])) + ((slow45) * (abs((dsp.const442) * ((((dsp.const446) * (rec98[unsafe_offset = i])) + ((dsp.const447) * (rec98[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const446) * (rec98[unsafe_offset = (i) - (S32(2))]))))))
            vstore(dsp.rec97_perm, vload[H](rec97_tmp, vsize))
            vstore(dsp.rec97_perm, vload[H](rec97_tmp, vsize + hsize), hsize)
            vstore(rec110_tmp, vload[H](dsp.rec110_perm))
            vstore(rec110_tmp, vload[H](dsp.rec110_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec110[unsafe_offset = i] = (zec57[i]) - ((dsp.const448) * (((dsp.const449) * (rec110[unsafe_offset = (i) - (S32(2))])) + ((dsp.const450) * (rec110[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec110_perm, vload[H](rec110_tmp, vsize))
            vstore(dsp.rec110_perm, vload[H](rec110_tmp, vsize + hsize), hsize)
            vstore(rec109_tmp, vload[H](dsp.rec109_perm))
            vstore(rec109_tmp, vload[H](dsp.rec109_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec109[unsafe_offset = i] = ((dsp.const448) * ((((dsp.const452) * (rec110[unsafe_offset = i])) + ((dsp.const453) * (rec110[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const452) * (rec110[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const454) * (((dsp.const455) * (rec109[unsafe_offset = (i) - (S32(2))])) + ((dsp.const456) * (rec109[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec109_perm, vload[H](rec109_tmp, vsize))
            vstore(dsp.rec109_perm, vload[H](rec109_tmp, vsize + hsize), hsize)
            vstore(rec108_tmp, vload[H](dsp.rec108_perm))
            vstore(rec108_tmp, vload[H](dsp.rec108_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec108[unsafe_offset = i] = ((dsp.const454) * ((((dsp.const457) * (rec109[unsafe_offset = i])) + ((dsp.const458) * (rec109[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const457) * (rec109[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const459) * (((dsp.const460) * (rec108[unsafe_offset = (i) - (S32(2))])) + ((dsp.const461) * (rec108[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec108_perm, vload[H](rec108_tmp, vsize))
            vstore(dsp.rec108_perm, vload[H](rec108_tmp, vsize + hsize), hsize)
            vstore(zec58, (F64Vec(dsp.const459)) * ((((F64Vec(dsp.const462)) * (vload[H](rec108))) + ((F64Vec(dsp.const463)) * (vload[H](rec108, - S32(1))))) + ((F64Vec(dsp.const462)) * (vload[H](rec108, - S32(2))))))
            vstore(zec58, (F64Vec(dsp.const459)) * ((((F64Vec(dsp.const462)) * (vload[H](rec108, hsize))) + ((F64Vec(dsp.const463)) * (vload[H](rec108, - S32(1) + hsize)))) + ((F64Vec(dsp.const462)) * (vload[H](rec108, - S32(2) + hsize)))), hsize)
            vstore(rec107_tmp, vload[H](dsp.rec107_perm))
            vstore(rec107_tmp, vload[H](dsp.rec107_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec107[unsafe_offset = i] = (zec58[i]) - ((dsp.const466) * (((dsp.const467) * (rec107[unsafe_offset = (i) - (S32(2))])) + ((dsp.const470) * (rec107[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec107_perm, vload[H](rec107_tmp, vsize))
            vstore(dsp.rec107_perm, vload[H](rec107_tmp, vsize + hsize), hsize)
            vstore(rec106_tmp, vload[H](dsp.rec106_perm))
            vstore(rec106_tmp, vload[H](dsp.rec106_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec106[unsafe_offset = i] = ((dsp.const466) * ((((dsp.const472) * (rec107[unsafe_offset = i])) + ((dsp.const473) * (rec107[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const472) * (rec107[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const474) * (((dsp.const475) * (rec106[unsafe_offset = (i) - (S32(2))])) + ((dsp.const476) * (rec106[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec106_perm, vload[H](rec106_tmp, vsize))
            vstore(dsp.rec106_perm, vload[H](rec106_tmp, vsize + hsize), hsize)
            vstore(rec105_tmp, vload[H](dsp.rec105_perm))
            vstore(rec105_tmp, vload[H](dsp.rec105_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec105[unsafe_offset = i] = ((dsp.const474) * ((((dsp.const478) * (rec106[unsafe_offset = i])) + ((dsp.const479) * (rec106[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const478) * (rec106[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const480) * (((dsp.const481) * (rec105[unsafe_offset = (i) - (S32(2))])) + ((dsp.const482) * (rec105[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec105_perm, vload[H](rec105_tmp, vsize))
            vstore(dsp.rec105_perm, vload[H](rec105_tmp, vsize + hsize), hsize)
            vstore(rec104_tmp, vload[H](dsp.rec104_perm))
            vstore(rec104_tmp, vload[H](dsp.rec104_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec104[unsafe_offset = i] = ((slow44) * (rec104[unsafe_offset = (i) - (S32(1))])) + ((slow45) * (abs((dsp.const480) * ((((dsp.const484) * (rec105[unsafe_offset = i])) + ((dsp.const485) * (rec105[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const484) * (rec105[unsafe_offset = (i) - (S32(2))]))))))
            vstore(dsp.rec104_perm, vload[H](rec104_tmp, vsize))
            vstore(dsp.rec104_perm, vload[H](rec104_tmp, vsize + hsize), hsize)
            vstore(rec117_tmp, vload[H](dsp.rec117_perm))
            vstore(rec117_tmp, vload[H](dsp.rec117_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec117[unsafe_offset = i] = (zec58[i]) - ((dsp.const486) * (((dsp.const487) * (rec117[unsafe_offset = (i) - (S32(2))])) + ((dsp.const488) * (rec117[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec117_perm, vload[H](rec117_tmp, vsize))
            vstore(dsp.rec117_perm, vload[H](rec117_tmp, vsize + hsize), hsize)
            vstore(rec116_tmp, vload[H](dsp.rec116_perm))
            vstore(rec116_tmp, vload[H](dsp.rec116_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec116[unsafe_offset = i] = ((dsp.const486) * ((((dsp.const490) * (rec117[unsafe_offset = i])) + ((dsp.const491) * (rec117[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const490) * (rec117[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const492) * (((dsp.const493) * (rec116[unsafe_offset = (i) - (S32(2))])) + ((dsp.const494) * (rec116[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec116_perm, vload[H](rec116_tmp, vsize))
            vstore(dsp.rec116_perm, vload[H](rec116_tmp, vsize + hsize), hsize)
            vstore(rec115_tmp, vload[H](dsp.rec115_perm))
            vstore(rec115_tmp, vload[H](dsp.rec115_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec115[unsafe_offset = i] = ((dsp.const492) * ((((dsp.const495) * (rec116[unsafe_offset = i])) + ((dsp.const496) * (rec116[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const495) * (rec116[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const497) * (((dsp.const498) * (rec115[unsafe_offset = (i) - (S32(2))])) + ((dsp.const499) * (rec115[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec115_perm, vload[H](rec115_tmp, vsize))
            vstore(dsp.rec115_perm, vload[H](rec115_tmp, vsize + hsize), hsize)
            vstore(zec59, (F64Vec(dsp.const497)) * ((((F64Vec(dsp.const500)) * (vload[H](rec115))) + ((F64Vec(dsp.const501)) * (vload[H](rec115, - S32(1))))) + ((F64Vec(dsp.const500)) * (vload[H](rec115, - S32(2))))))
            vstore(zec59, (F64Vec(dsp.const497)) * ((((F64Vec(dsp.const500)) * (vload[H](rec115, hsize))) + ((F64Vec(dsp.const501)) * (vload[H](rec115, - S32(1) + hsize)))) + ((F64Vec(dsp.const500)) * (vload[H](rec115, - S32(2) + hsize)))), hsize)
            vstore(rec114_tmp, vload[H](dsp.rec114_perm))
            vstore(rec114_tmp, vload[H](dsp.rec114_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec114[unsafe_offset = i] = (zec59[i]) - ((dsp.const504) * (((dsp.const505) * (rec114[unsafe_offset = (i) - (S32(2))])) + ((dsp.const508) * (rec114[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec114_perm, vload[H](rec114_tmp, vsize))
            vstore(dsp.rec114_perm, vload[H](rec114_tmp, vsize + hsize), hsize)
            vstore(rec113_tmp, vload[H](dsp.rec113_perm))
            vstore(rec113_tmp, vload[H](dsp.rec113_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec113[unsafe_offset = i] = ((dsp.const504) * ((((dsp.const510) * (rec114[unsafe_offset = i])) + ((dsp.const511) * (rec114[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const510) * (rec114[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const512) * (((dsp.const513) * (rec113[unsafe_offset = (i) - (S32(2))])) + ((dsp.const514) * (rec113[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec113_perm, vload[H](rec113_tmp, vsize))
            vstore(dsp.rec113_perm, vload[H](rec113_tmp, vsize + hsize), hsize)
            vstore(rec112_tmp, vload[H](dsp.rec112_perm))
            vstore(rec112_tmp, vload[H](dsp.rec112_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec112[unsafe_offset = i] = ((dsp.const512) * ((((dsp.const516) * (rec113[unsafe_offset = i])) + ((dsp.const517) * (rec113[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const516) * (rec113[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const518) * (((dsp.const519) * (rec112[unsafe_offset = (i) - (S32(2))])) + ((dsp.const520) * (rec112[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec112_perm, vload[H](rec112_tmp, vsize))
            vstore(dsp.rec112_perm, vload[H](rec112_tmp, vsize + hsize), hsize)
            vstore(rec111_tmp, vload[H](dsp.rec111_perm))
            vstore(rec111_tmp, vload[H](dsp.rec111_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec111[unsafe_offset = i] = ((slow44) * (rec111[unsafe_offset = (i) - (S32(1))])) + ((slow45) * (abs((dsp.const518) * ((((dsp.const522) * (rec112[unsafe_offset = i])) + ((dsp.const523) * (rec112[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const522) * (rec112[unsafe_offset = (i) - (S32(2))]))))))
            vstore(dsp.rec111_perm, vload[H](rec111_tmp, vsize))
            vstore(dsp.rec111_perm, vload[H](rec111_tmp, vsize + hsize), hsize)
            vstore(rec121_tmp, vload[H](dsp.rec121_perm))
            vstore(rec121_tmp, vload[H](dsp.rec121_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec121[unsafe_offset = i] = (zec59[i]) - ((dsp.const524) * (((dsp.const525) * (rec121[unsafe_offset = (i) - (S32(2))])) + ((dsp.const526) * (rec121[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec121_perm, vload[H](rec121_tmp, vsize))
            vstore(dsp.rec121_perm, vload[H](rec121_tmp, vsize + hsize), hsize)
            vstore(rec120_tmp, vload[H](dsp.rec120_perm))
            vstore(rec120_tmp, vload[H](dsp.rec120_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec120[unsafe_offset = i] = ((dsp.const524) * ((((dsp.const528) * (rec121[unsafe_offset = i])) + ((dsp.const529) * (rec121[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const528) * (rec121[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const530) * (((dsp.const531) * (rec120[unsafe_offset = (i) - (S32(2))])) + ((dsp.const532) * (rec120[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec120_perm, vload[H](rec120_tmp, vsize))
            vstore(dsp.rec120_perm, vload[H](rec120_tmp, vsize + hsize), hsize)
            vstore(rec119_tmp, vload[H](dsp.rec119_perm))
            vstore(rec119_tmp, vload[H](dsp.rec119_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec119[unsafe_offset = i] = ((dsp.const530) * ((((dsp.const533) * (rec120[unsafe_offset = i])) + ((dsp.const534) * (rec120[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const533) * (rec120[unsafe_offset = (i) - (S32(2))])))) - ((dsp.const535) * (((dsp.const536) * (rec119[unsafe_offset = (i) - (S32(2))])) + ((dsp.const537) * (rec119[unsafe_offset = (i) - (S32(1))]))))
            vstore(dsp.rec119_perm, vload[H](rec119_tmp, vsize))
            vstore(dsp.rec119_perm, vload[H](rec119_tmp, vsize + hsize), hsize)
            vstore(rec118_tmp, vload[H](dsp.rec118_perm))
            vstore(rec118_tmp, vload[H](dsp.rec118_perm, hsize), hsize)
            comptime for i in range(vsize):
                rec118[unsafe_offset = i] = ((slow44) * (rec118[unsafe_offset = (i) - (S32(1))])) + ((slow45) * (abs((dsp.const535) * ((((dsp.const538) * (rec119[unsafe_offset = i])) + ((dsp.const539) * (rec119[unsafe_offset = (i) - (S32(1))]))) + ((dsp.const538) * (rec119[unsafe_offset = (i) - (S32(2))]))))))
            vstore(dsp.rec118_perm, vload[H](rec118_tmp, vsize))
            vstore(dsp.rec118_perm, vload[H](rec118_tmp, vsize + hsize), hsize)
            comptime for i in range(S32(0), vsize):
                dsp.vbargraph0 = FaustFloat((slow46) + ((2e+01) * (log10(rec23[unsafe_offset = i]))))
                dsp.vbargraph1 = FaustFloat((slow46) + ((2e+01) * (log10(rec27[unsafe_offset = i]))))
                dsp.vbargraph2 = FaustFloat((slow46) + ((2e+01) * (log10(rec34[unsafe_offset = i]))))
                dsp.vbargraph3 = FaustFloat((slow46) + ((2e+01) * (log10(rec41[unsafe_offset = i]))))
                dsp.vbargraph4 = FaustFloat((slow46) + ((2e+01) * (log10(rec48[unsafe_offset = i]))))
                dsp.vbargraph5 = FaustFloat((slow46) + ((2e+01) * (log10(rec55[unsafe_offset = i]))))
                dsp.vbargraph6 = FaustFloat((slow46) + ((2e+01) * (log10(rec62[unsafe_offset = i]))))
                dsp.vbargraph7 = FaustFloat((slow46) + ((2e+01) * (log10(rec69[unsafe_offset = i]))))
                dsp.vbargraph8 = FaustFloat((slow46) + ((2e+01) * (log10(rec76[unsafe_offset = i]))))
                dsp.vbargraph9 = FaustFloat((slow46) + ((2e+01) * (log10(rec83[unsafe_offset = i]))))
                dsp.vbargraph10 = FaustFloat((slow46) + ((2e+01) * (log10(rec90[unsafe_offset = i]))))
                dsp.vbargraph11 = FaustFloat((slow46) + ((2e+01) * (log10(rec97[unsafe_offset = i]))))
                dsp.vbargraph12 = FaustFloat((slow46) + ((2e+01) * (log10(rec104[unsafe_offset = i]))))
                dsp.vbargraph13 = FaustFloat((slow46) + ((2e+01) * (log10(rec111[unsafe_offset = i]))))
                dsp.vbargraph14 = FaustFloat((slow46) + ((2e+01) * (log10(rec118[unsafe_offset = i]))))
            vstore(output0, ((vload[H](zec44)).cast[dfaust]()).join((vload[H](zec44, hsize)).cast[dfaust]()))
            vstore(output1, ((vload[H](zec45)).cast[dfaust]()).join((vload[H](zec45, hsize)).cast[dfaust]()))
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
