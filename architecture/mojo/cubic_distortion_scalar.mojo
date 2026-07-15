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
#   -mdy 33 -double -ftz 0
# ==============================================================================

comptime dreal = f64
comptime wreal = S32(simd_width_of[dreal]())
comptime Real = Scalar[dreal]
comptime RVec = Vec[dreal]

@fieldwise_init
struct mydsp(FaustDsp):
    var null_val: FaustFloat
    var hslider0: FaustFloat
    var i_vec0: Arr[S32, 2]
    var hslider1: FaustFloat
    var sample_rate: S32
    var const0: F64
    var const1: F64
    var const2: F64
    var const3: F64
    var const4: F64
    var const5: F64
    var const6: F64
    var const7: F64
    var const8: F64
    var const9: F64
    var const10: F64
    var const11: F64
    var const12: F64
    var const13: F64
    var checkbox0: FaustFloat
    var hslider2: FaustFloat
    var rec5: Arr[F64, 2]
    var hslider3: FaustFloat
    var rec6: Arr[F64, 2]
    var const14: F64
    var hslider4: FaustFloat
    var const15: F64
    var hslider5: FaustFloat
    var rec9: Arr[F64, 2]
    var rec7: Arr[F64, 2]
    var rec8: Arr[F64, 2]
    var hslider6: FaustFloat
    var rec10: Arr[F64, 2]
    var vec1: Arr[F64, 2]
    var rec4: Arr[F64, 2]
    var const16: F64
    var const17: F64
    var const18: F64
    var rec3: Arr[F64, 3]
    var const19: F64
    var const20: F64
    var const21: F64
    var rec2: Arr[F64, 3]
    var const22: F64
    var const23: F64
    var const24: F64
    var rec1: Arr[F64, 3]
    var const25: F64
    var rec0: Arr[F64, 2]
    var vbargraph0: FaustFloat
    var const26: F64
    var const27: F64
    var const28: F64
    var const29: F64
    var const30: F64
    var const31: F64
    var const32: F64
    var const33: F64
    var const34: F64
    var const35: F64
    var const36: F64
    var const37: F64
    var const38: F64
    var const39: F64
    var const40: F64
    var const41: F64
    var const42: F64
    var const43: F64
    var const44: F64
    var const45: F64
    var const46: F64
    var rec17: Arr[F64, 3]
    var const47: F64
    var const48: F64
    var const49: F64
    var rec16: Arr[F64, 3]
    var const50: F64
    var const51: F64
    var const52: F64
    var rec15: Arr[F64, 3]
    var const53: F64
    var const54: F64
    var const55: F64
    var const56: F64
    var rec14: Arr[F64, 3]
    var const57: F64
    var const58: F64
    var const59: F64
    var rec13: Arr[F64, 3]
    var const60: F64
    var const61: F64
    var const62: F64
    var rec12: Arr[F64, 3]
    var const63: F64
    var rec11: Arr[F64, 2]
    var vbargraph1: FaustFloat
    var const64: F64
    var const65: F64
    var const66: F64
    var const67: F64
    var const68: F64
    var const69: F64
    var const70: F64
    var const71: F64
    var const72: F64
    var const73: F64
    var const74: F64
    var const75: F64
    var const76: F64
    var const77: F64
    var const78: F64
    var const79: F64
    var const80: F64
    var const81: F64
    var const82: F64
    var const83: F64
    var const84: F64
    var rec24: Arr[F64, 3]
    var const85: F64
    var const86: F64
    var const87: F64
    var rec23: Arr[F64, 3]
    var const88: F64
    var const89: F64
    var const90: F64
    var rec22: Arr[F64, 3]
    var const91: F64
    var const92: F64
    var const93: F64
    var const94: F64
    var rec21: Arr[F64, 3]
    var const95: F64
    var const96: F64
    var const97: F64
    var rec20: Arr[F64, 3]
    var const98: F64
    var const99: F64
    var const100: F64
    var rec19: Arr[F64, 3]
    var const101: F64
    var rec18: Arr[F64, 2]
    var vbargraph2: FaustFloat
    var const102: F64
    var const103: F64
    var const104: F64
    var const105: F64
    var const106: F64
    var const107: F64
    var const108: F64
    var const109: F64
    var const110: F64
    var const111: F64
    var const112: F64
    var const113: F64
    var const114: F64
    var const115: F64
    var const116: F64
    var const117: F64
    var const118: F64
    var const119: F64
    var const120: F64
    var const121: F64
    var const122: F64
    var rec31: Arr[F64, 3]
    var const123: F64
    var const124: F64
    var const125: F64
    var rec30: Arr[F64, 3]
    var const126: F64
    var const127: F64
    var const128: F64
    var rec29: Arr[F64, 3]
    var const129: F64
    var const130: F64
    var const131: F64
    var const132: F64
    var rec28: Arr[F64, 3]
    var const133: F64
    var const134: F64
    var const135: F64
    var rec27: Arr[F64, 3]
    var const136: F64
    var const137: F64
    var const138: F64
    var rec26: Arr[F64, 3]
    var const139: F64
    var rec25: Arr[F64, 2]
    var vbargraph3: FaustFloat
    var const140: F64
    var const141: F64
    var const142: F64
    var const143: F64
    var const144: F64
    var const145: F64
    var const146: F64
    var const147: F64
    var const148: F64
    var const149: F64
    var const150: F64
    var const151: F64
    var const152: F64
    var const153: F64
    var const154: F64
    var const155: F64
    var const156: F64
    var const157: F64
    var const158: F64
    var const159: F64
    var const160: F64
    var rec38: Arr[F64, 3]
    var const161: F64
    var const162: F64
    var const163: F64
    var rec37: Arr[F64, 3]
    var const164: F64
    var const165: F64
    var const166: F64
    var rec36: Arr[F64, 3]
    var const167: F64
    var const168: F64
    var const169: F64
    var const170: F64
    var rec35: Arr[F64, 3]
    var const171: F64
    var const172: F64
    var const173: F64
    var rec34: Arr[F64, 3]
    var const174: F64
    var const175: F64
    var const176: F64
    var rec33: Arr[F64, 3]
    var const177: F64
    var rec32: Arr[F64, 2]
    var vbargraph4: FaustFloat
    var const178: F64
    var const179: F64
    var const180: F64
    var const181: F64
    var const182: F64
    var const183: F64
    var const184: F64
    var const185: F64
    var const186: F64
    var const187: F64
    var const188: F64
    var const189: F64
    var const190: F64
    var const191: F64
    var const192: F64
    var const193: F64
    var const194: F64
    var const195: F64
    var const196: F64
    var const197: F64
    var const198: F64
    var rec45: Arr[F64, 3]
    var const199: F64
    var const200: F64
    var const201: F64
    var rec44: Arr[F64, 3]
    var const202: F64
    var const203: F64
    var const204: F64
    var rec43: Arr[F64, 3]
    var const205: F64
    var const206: F64
    var const207: F64
    var const208: F64
    var rec42: Arr[F64, 3]
    var const209: F64
    var const210: F64
    var const211: F64
    var rec41: Arr[F64, 3]
    var const212: F64
    var const213: F64
    var const214: F64
    var rec40: Arr[F64, 3]
    var const215: F64
    var rec39: Arr[F64, 2]
    var vbargraph5: FaustFloat
    var const216: F64
    var const217: F64
    var const218: F64
    var const219: F64
    var const220: F64
    var const221: F64
    var const222: F64
    var const223: F64
    var const224: F64
    var const225: F64
    var const226: F64
    var const227: F64
    var const228: F64
    var const229: F64
    var const230: F64
    var const231: F64
    var const232: F64
    var const233: F64
    var const234: F64
    var const235: F64
    var const236: F64
    var rec52: Arr[F64, 3]
    var const237: F64
    var const238: F64
    var const239: F64
    var rec51: Arr[F64, 3]
    var const240: F64
    var const241: F64
    var const242: F64
    var rec50: Arr[F64, 3]
    var const243: F64
    var const244: F64
    var const245: F64
    var const246: F64
    var rec49: Arr[F64, 3]
    var const247: F64
    var const248: F64
    var const249: F64
    var rec48: Arr[F64, 3]
    var const250: F64
    var const251: F64
    var const252: F64
    var rec47: Arr[F64, 3]
    var const253: F64
    var rec46: Arr[F64, 2]
    var vbargraph6: FaustFloat
    var const254: F64
    var const255: F64
    var const256: F64
    var const257: F64
    var const258: F64
    var const259: F64
    var const260: F64
    var const261: F64
    var const262: F64
    var const263: F64
    var const264: F64
    var const265: F64
    var const266: F64
    var const267: F64
    var const268: F64
    var const269: F64
    var const270: F64
    var const271: F64
    var const272: F64
    var const273: F64
    var const274: F64
    var rec59: Arr[F64, 3]
    var const275: F64
    var const276: F64
    var const277: F64
    var rec58: Arr[F64, 3]
    var const278: F64
    var const279: F64
    var const280: F64
    var rec57: Arr[F64, 3]
    var const281: F64
    var const282: F64
    var const283: F64
    var const284: F64
    var rec56: Arr[F64, 3]
    var const285: F64
    var const286: F64
    var const287: F64
    var rec55: Arr[F64, 3]
    var const288: F64
    var const289: F64
    var const290: F64
    var rec54: Arr[F64, 3]
    var const291: F64
    var rec53: Arr[F64, 2]
    var vbargraph7: FaustFloat
    var const292: F64
    var const293: F64
    var const294: F64
    var const295: F64
    var const296: F64
    var const297: F64
    var const298: F64
    var const299: F64
    var const300: F64
    var const301: F64
    var const302: F64
    var const303: F64
    var const304: F64
    var const305: F64
    var const306: F64
    var const307: F64
    var const308: F64
    var const309: F64
    var const310: F64
    var const311: F64
    var const312: F64
    var rec66: Arr[F64, 3]
    var const313: F64
    var const314: F64
    var const315: F64
    var rec65: Arr[F64, 3]
    var const316: F64
    var const317: F64
    var const318: F64
    var rec64: Arr[F64, 3]
    var const319: F64
    var const320: F64
    var const321: F64
    var const322: F64
    var rec63: Arr[F64, 3]
    var const323: F64
    var const324: F64
    var const325: F64
    var rec62: Arr[F64, 3]
    var const326: F64
    var const327: F64
    var const328: F64
    var rec61: Arr[F64, 3]
    var const329: F64
    var rec60: Arr[F64, 2]
    var vbargraph8: FaustFloat
    var const330: F64
    var const331: F64
    var const332: F64
    var const333: F64
    var const334: F64
    var const335: F64
    var const336: F64
    var const337: F64
    var const338: F64
    var const339: F64
    var const340: F64
    var const341: F64
    var const342: F64
    var const343: F64
    var const344: F64
    var const345: F64
    var const346: F64
    var const347: F64
    var const348: F64
    var const349: F64
    var const350: F64
    var rec73: Arr[F64, 3]
    var const351: F64
    var const352: F64
    var const353: F64
    var rec72: Arr[F64, 3]
    var const354: F64
    var const355: F64
    var const356: F64
    var rec71: Arr[F64, 3]
    var const357: F64
    var const358: F64
    var const359: F64
    var const360: F64
    var rec70: Arr[F64, 3]
    var const361: F64
    var const362: F64
    var const363: F64
    var rec69: Arr[F64, 3]
    var const364: F64
    var const365: F64
    var const366: F64
    var rec68: Arr[F64, 3]
    var const367: F64
    var rec67: Arr[F64, 2]
    var vbargraph9: FaustFloat
    var const368: F64
    var const369: F64
    var const370: F64
    var const371: F64
    var const372: F64
    var const373: F64
    var const374: F64
    var const375: F64
    var const376: F64
    var const377: F64
    var const378: F64
    var const379: F64
    var const380: F64
    var const381: F64
    var const382: F64
    var const383: F64
    var const384: F64
    var const385: F64
    var const386: F64
    var const387: F64
    var const388: F64
    var rec80: Arr[F64, 3]
    var const389: F64
    var const390: F64
    var const391: F64
    var rec79: Arr[F64, 3]
    var const392: F64
    var const393: F64
    var const394: F64
    var rec78: Arr[F64, 3]
    var const395: F64
    var const396: F64
    var const397: F64
    var const398: F64
    var rec77: Arr[F64, 3]
    var const399: F64
    var const400: F64
    var const401: F64
    var rec76: Arr[F64, 3]
    var const402: F64
    var const403: F64
    var const404: F64
    var rec75: Arr[F64, 3]
    var const405: F64
    var rec74: Arr[F64, 2]
    var vbargraph10: FaustFloat
    var const406: F64
    var const407: F64
    var const408: F64
    var const409: F64
    var const410: F64
    var const411: F64
    var const412: F64
    var const413: F64
    var const414: F64
    var const415: F64
    var const416: F64
    var const417: F64
    var const418: F64
    var const419: F64
    var const420: F64
    var const421: F64
    var const422: F64
    var const423: F64
    var const424: F64
    var const425: F64
    var const426: F64
    var rec87: Arr[F64, 3]
    var const427: F64
    var const428: F64
    var const429: F64
    var rec86: Arr[F64, 3]
    var const430: F64
    var const431: F64
    var const432: F64
    var rec85: Arr[F64, 3]
    var const433: F64
    var const434: F64
    var const435: F64
    var const436: F64
    var rec84: Arr[F64, 3]
    var const437: F64
    var const438: F64
    var const439: F64
    var rec83: Arr[F64, 3]
    var const440: F64
    var const441: F64
    var const442: F64
    var rec82: Arr[F64, 3]
    var const443: F64
    var rec81: Arr[F64, 2]
    var vbargraph11: FaustFloat
    var const444: F64
    var const445: F64
    var const446: F64
    var const447: F64
    var const448: F64
    var const449: F64
    var const450: F64
    var const451: F64
    var const452: F64
    var const453: F64
    var const454: F64
    var const455: F64
    var const456: F64
    var const457: F64
    var const458: F64
    var const459: F64
    var const460: F64
    var const461: F64
    var const462: F64
    var const463: F64
    var const464: F64
    var rec94: Arr[F64, 3]
    var const465: F64
    var const466: F64
    var const467: F64
    var rec93: Arr[F64, 3]
    var const468: F64
    var const469: F64
    var const470: F64
    var rec92: Arr[F64, 3]
    var const471: F64
    var const472: F64
    var const473: F64
    var const474: F64
    var rec91: Arr[F64, 3]
    var const475: F64
    var const476: F64
    var const477: F64
    var rec90: Arr[F64, 3]
    var const478: F64
    var const479: F64
    var const480: F64
    var rec89: Arr[F64, 3]
    var const481: F64
    var rec88: Arr[F64, 2]
    var vbargraph12: FaustFloat
    var const482: F64
    var const483: F64
    var const484: F64
    var const485: F64
    var const486: F64
    var const487: F64
    var const488: F64
    var const489: F64
    var const490: F64
    var const491: F64
    var const492: F64
    var const493: F64
    var const494: F64
    var const495: F64
    var const496: F64
    var const497: F64
    var const498: F64
    var const499: F64
    var const500: F64
    var const501: F64
    var const502: F64
    var rec101: Arr[F64, 3]
    var const503: F64
    var const504: F64
    var const505: F64
    var rec100: Arr[F64, 3]
    var const506: F64
    var const507: F64
    var const508: F64
    var rec99: Arr[F64, 3]
    var const509: F64
    var const510: F64
    var const511: F64
    var const512: F64
    var rec98: Arr[F64, 3]
    var const513: F64
    var const514: F64
    var const515: F64
    var rec97: Arr[F64, 3]
    var const516: F64
    var const517: F64
    var const518: F64
    var rec96: Arr[F64, 3]
    var const519: F64
    var rec95: Arr[F64, 2]
    var vbargraph13: FaustFloat
    var const520: F64
    var const521: F64
    var const522: F64
    var const523: F64
    var const524: F64
    var const525: F64
    var const526: F64
    var const527: F64
    var const528: F64
    var rec105: Arr[F64, 3]
    var const529: F64
    var const530: F64
    var const531: F64
    var rec104: Arr[F64, 3]
    var const532: F64
    var const533: F64
    var const534: F64
    var rec103: Arr[F64, 3]
    var const535: F64
    var rec102: Arr[F64, 2]
    var vbargraph14: FaustFloat

    @always_inline
    def __init__(out dsp):
        dsp.null_val = FaustFloat(0.0)
        dsp.hslider0 = 0.0
        dsp.i_vec0 = Arr[S32, 2](fill=0)
        dsp.hslider1 = 0.0
        dsp.sample_rate = 0
        dsp.const0 = 0.0
        dsp.const1 = 0.0
        dsp.const2 = 0.0
        dsp.const3 = 0.0
        dsp.const4 = 0.0
        dsp.const5 = 0.0
        dsp.const6 = 0.0
        dsp.const7 = 0.0
        dsp.const8 = 0.0
        dsp.const9 = 0.0
        dsp.const10 = 0.0
        dsp.const11 = 0.0
        dsp.const12 = 0.0
        dsp.const13 = 0.0
        dsp.checkbox0 = 0.0
        dsp.hslider2 = 0.0
        dsp.rec5 = Arr[F64, 2](fill=0.0)
        dsp.hslider3 = 0.0
        dsp.rec6 = Arr[F64, 2](fill=0.0)
        dsp.const14 = 0.0
        dsp.hslider4 = 0.0
        dsp.const15 = 0.0
        dsp.hslider5 = 0.0
        dsp.rec9 = Arr[F64, 2](fill=0.0)
        dsp.rec7 = Arr[F64, 2](fill=0.0)
        dsp.rec8 = Arr[F64, 2](fill=0.0)
        dsp.hslider6 = 0.0
        dsp.rec10 = Arr[F64, 2](fill=0.0)
        dsp.vec1 = Arr[F64, 2](fill=0.0)
        dsp.rec4 = Arr[F64, 2](fill=0.0)
        dsp.const16 = 0.0
        dsp.const17 = 0.0
        dsp.const18 = 0.0
        dsp.rec3 = Arr[F64, 3](fill=0.0)
        dsp.const19 = 0.0
        dsp.const20 = 0.0
        dsp.const21 = 0.0
        dsp.rec2 = Arr[F64, 3](fill=0.0)
        dsp.const22 = 0.0
        dsp.const23 = 0.0
        dsp.const24 = 0.0
        dsp.rec1 = Arr[F64, 3](fill=0.0)
        dsp.const25 = 0.0
        dsp.rec0 = Arr[F64, 2](fill=0.0)
        dsp.vbargraph0 = 0.0
        dsp.const26 = 0.0
        dsp.const27 = 0.0
        dsp.const28 = 0.0
        dsp.const29 = 0.0
        dsp.const30 = 0.0
        dsp.const31 = 0.0
        dsp.const32 = 0.0
        dsp.const33 = 0.0
        dsp.const34 = 0.0
        dsp.const35 = 0.0
        dsp.const36 = 0.0
        dsp.const37 = 0.0
        dsp.const38 = 0.0
        dsp.const39 = 0.0
        dsp.const40 = 0.0
        dsp.const41 = 0.0
        dsp.const42 = 0.0
        dsp.const43 = 0.0
        dsp.const44 = 0.0
        dsp.const45 = 0.0
        dsp.const46 = 0.0
        dsp.rec17 = Arr[F64, 3](fill=0.0)
        dsp.const47 = 0.0
        dsp.const48 = 0.0
        dsp.const49 = 0.0
        dsp.rec16 = Arr[F64, 3](fill=0.0)
        dsp.const50 = 0.0
        dsp.const51 = 0.0
        dsp.const52 = 0.0
        dsp.rec15 = Arr[F64, 3](fill=0.0)
        dsp.const53 = 0.0
        dsp.const54 = 0.0
        dsp.const55 = 0.0
        dsp.const56 = 0.0
        dsp.rec14 = Arr[F64, 3](fill=0.0)
        dsp.const57 = 0.0
        dsp.const58 = 0.0
        dsp.const59 = 0.0
        dsp.rec13 = Arr[F64, 3](fill=0.0)
        dsp.const60 = 0.0
        dsp.const61 = 0.0
        dsp.const62 = 0.0
        dsp.rec12 = Arr[F64, 3](fill=0.0)
        dsp.const63 = 0.0
        dsp.rec11 = Arr[F64, 2](fill=0.0)
        dsp.vbargraph1 = 0.0
        dsp.const64 = 0.0
        dsp.const65 = 0.0
        dsp.const66 = 0.0
        dsp.const67 = 0.0
        dsp.const68 = 0.0
        dsp.const69 = 0.0
        dsp.const70 = 0.0
        dsp.const71 = 0.0
        dsp.const72 = 0.0
        dsp.const73 = 0.0
        dsp.const74 = 0.0
        dsp.const75 = 0.0
        dsp.const76 = 0.0
        dsp.const77 = 0.0
        dsp.const78 = 0.0
        dsp.const79 = 0.0
        dsp.const80 = 0.0
        dsp.const81 = 0.0
        dsp.const82 = 0.0
        dsp.const83 = 0.0
        dsp.const84 = 0.0
        dsp.rec24 = Arr[F64, 3](fill=0.0)
        dsp.const85 = 0.0
        dsp.const86 = 0.0
        dsp.const87 = 0.0
        dsp.rec23 = Arr[F64, 3](fill=0.0)
        dsp.const88 = 0.0
        dsp.const89 = 0.0
        dsp.const90 = 0.0
        dsp.rec22 = Arr[F64, 3](fill=0.0)
        dsp.const91 = 0.0
        dsp.const92 = 0.0
        dsp.const93 = 0.0
        dsp.const94 = 0.0
        dsp.rec21 = Arr[F64, 3](fill=0.0)
        dsp.const95 = 0.0
        dsp.const96 = 0.0
        dsp.const97 = 0.0
        dsp.rec20 = Arr[F64, 3](fill=0.0)
        dsp.const98 = 0.0
        dsp.const99 = 0.0
        dsp.const100 = 0.0
        dsp.rec19 = Arr[F64, 3](fill=0.0)
        dsp.const101 = 0.0
        dsp.rec18 = Arr[F64, 2](fill=0.0)
        dsp.vbargraph2 = 0.0
        dsp.const102 = 0.0
        dsp.const103 = 0.0
        dsp.const104 = 0.0
        dsp.const105 = 0.0
        dsp.const106 = 0.0
        dsp.const107 = 0.0
        dsp.const108 = 0.0
        dsp.const109 = 0.0
        dsp.const110 = 0.0
        dsp.const111 = 0.0
        dsp.const112 = 0.0
        dsp.const113 = 0.0
        dsp.const114 = 0.0
        dsp.const115 = 0.0
        dsp.const116 = 0.0
        dsp.const117 = 0.0
        dsp.const118 = 0.0
        dsp.const119 = 0.0
        dsp.const120 = 0.0
        dsp.const121 = 0.0
        dsp.const122 = 0.0
        dsp.rec31 = Arr[F64, 3](fill=0.0)
        dsp.const123 = 0.0
        dsp.const124 = 0.0
        dsp.const125 = 0.0
        dsp.rec30 = Arr[F64, 3](fill=0.0)
        dsp.const126 = 0.0
        dsp.const127 = 0.0
        dsp.const128 = 0.0
        dsp.rec29 = Arr[F64, 3](fill=0.0)
        dsp.const129 = 0.0
        dsp.const130 = 0.0
        dsp.const131 = 0.0
        dsp.const132 = 0.0
        dsp.rec28 = Arr[F64, 3](fill=0.0)
        dsp.const133 = 0.0
        dsp.const134 = 0.0
        dsp.const135 = 0.0
        dsp.rec27 = Arr[F64, 3](fill=0.0)
        dsp.const136 = 0.0
        dsp.const137 = 0.0
        dsp.const138 = 0.0
        dsp.rec26 = Arr[F64, 3](fill=0.0)
        dsp.const139 = 0.0
        dsp.rec25 = Arr[F64, 2](fill=0.0)
        dsp.vbargraph3 = 0.0
        dsp.const140 = 0.0
        dsp.const141 = 0.0
        dsp.const142 = 0.0
        dsp.const143 = 0.0
        dsp.const144 = 0.0
        dsp.const145 = 0.0
        dsp.const146 = 0.0
        dsp.const147 = 0.0
        dsp.const148 = 0.0
        dsp.const149 = 0.0
        dsp.const150 = 0.0
        dsp.const151 = 0.0
        dsp.const152 = 0.0
        dsp.const153 = 0.0
        dsp.const154 = 0.0
        dsp.const155 = 0.0
        dsp.const156 = 0.0
        dsp.const157 = 0.0
        dsp.const158 = 0.0
        dsp.const159 = 0.0
        dsp.const160 = 0.0
        dsp.rec38 = Arr[F64, 3](fill=0.0)
        dsp.const161 = 0.0
        dsp.const162 = 0.0
        dsp.const163 = 0.0
        dsp.rec37 = Arr[F64, 3](fill=0.0)
        dsp.const164 = 0.0
        dsp.const165 = 0.0
        dsp.const166 = 0.0
        dsp.rec36 = Arr[F64, 3](fill=0.0)
        dsp.const167 = 0.0
        dsp.const168 = 0.0
        dsp.const169 = 0.0
        dsp.const170 = 0.0
        dsp.rec35 = Arr[F64, 3](fill=0.0)
        dsp.const171 = 0.0
        dsp.const172 = 0.0
        dsp.const173 = 0.0
        dsp.rec34 = Arr[F64, 3](fill=0.0)
        dsp.const174 = 0.0
        dsp.const175 = 0.0
        dsp.const176 = 0.0
        dsp.rec33 = Arr[F64, 3](fill=0.0)
        dsp.const177 = 0.0
        dsp.rec32 = Arr[F64, 2](fill=0.0)
        dsp.vbargraph4 = 0.0
        dsp.const178 = 0.0
        dsp.const179 = 0.0
        dsp.const180 = 0.0
        dsp.const181 = 0.0
        dsp.const182 = 0.0
        dsp.const183 = 0.0
        dsp.const184 = 0.0
        dsp.const185 = 0.0
        dsp.const186 = 0.0
        dsp.const187 = 0.0
        dsp.const188 = 0.0
        dsp.const189 = 0.0
        dsp.const190 = 0.0
        dsp.const191 = 0.0
        dsp.const192 = 0.0
        dsp.const193 = 0.0
        dsp.const194 = 0.0
        dsp.const195 = 0.0
        dsp.const196 = 0.0
        dsp.const197 = 0.0
        dsp.const198 = 0.0
        dsp.rec45 = Arr[F64, 3](fill=0.0)
        dsp.const199 = 0.0
        dsp.const200 = 0.0
        dsp.const201 = 0.0
        dsp.rec44 = Arr[F64, 3](fill=0.0)
        dsp.const202 = 0.0
        dsp.const203 = 0.0
        dsp.const204 = 0.0
        dsp.rec43 = Arr[F64, 3](fill=0.0)
        dsp.const205 = 0.0
        dsp.const206 = 0.0
        dsp.const207 = 0.0
        dsp.const208 = 0.0
        dsp.rec42 = Arr[F64, 3](fill=0.0)
        dsp.const209 = 0.0
        dsp.const210 = 0.0
        dsp.const211 = 0.0
        dsp.rec41 = Arr[F64, 3](fill=0.0)
        dsp.const212 = 0.0
        dsp.const213 = 0.0
        dsp.const214 = 0.0
        dsp.rec40 = Arr[F64, 3](fill=0.0)
        dsp.const215 = 0.0
        dsp.rec39 = Arr[F64, 2](fill=0.0)
        dsp.vbargraph5 = 0.0
        dsp.const216 = 0.0
        dsp.const217 = 0.0
        dsp.const218 = 0.0
        dsp.const219 = 0.0
        dsp.const220 = 0.0
        dsp.const221 = 0.0
        dsp.const222 = 0.0
        dsp.const223 = 0.0
        dsp.const224 = 0.0
        dsp.const225 = 0.0
        dsp.const226 = 0.0
        dsp.const227 = 0.0
        dsp.const228 = 0.0
        dsp.const229 = 0.0
        dsp.const230 = 0.0
        dsp.const231 = 0.0
        dsp.const232 = 0.0
        dsp.const233 = 0.0
        dsp.const234 = 0.0
        dsp.const235 = 0.0
        dsp.const236 = 0.0
        dsp.rec52 = Arr[F64, 3](fill=0.0)
        dsp.const237 = 0.0
        dsp.const238 = 0.0
        dsp.const239 = 0.0
        dsp.rec51 = Arr[F64, 3](fill=0.0)
        dsp.const240 = 0.0
        dsp.const241 = 0.0
        dsp.const242 = 0.0
        dsp.rec50 = Arr[F64, 3](fill=0.0)
        dsp.const243 = 0.0
        dsp.const244 = 0.0
        dsp.const245 = 0.0
        dsp.const246 = 0.0
        dsp.rec49 = Arr[F64, 3](fill=0.0)
        dsp.const247 = 0.0
        dsp.const248 = 0.0
        dsp.const249 = 0.0
        dsp.rec48 = Arr[F64, 3](fill=0.0)
        dsp.const250 = 0.0
        dsp.const251 = 0.0
        dsp.const252 = 0.0
        dsp.rec47 = Arr[F64, 3](fill=0.0)
        dsp.const253 = 0.0
        dsp.rec46 = Arr[F64, 2](fill=0.0)
        dsp.vbargraph6 = 0.0
        dsp.const254 = 0.0
        dsp.const255 = 0.0
        dsp.const256 = 0.0
        dsp.const257 = 0.0
        dsp.const258 = 0.0
        dsp.const259 = 0.0
        dsp.const260 = 0.0
        dsp.const261 = 0.0
        dsp.const262 = 0.0
        dsp.const263 = 0.0
        dsp.const264 = 0.0
        dsp.const265 = 0.0
        dsp.const266 = 0.0
        dsp.const267 = 0.0
        dsp.const268 = 0.0
        dsp.const269 = 0.0
        dsp.const270 = 0.0
        dsp.const271 = 0.0
        dsp.const272 = 0.0
        dsp.const273 = 0.0
        dsp.const274 = 0.0
        dsp.rec59 = Arr[F64, 3](fill=0.0)
        dsp.const275 = 0.0
        dsp.const276 = 0.0
        dsp.const277 = 0.0
        dsp.rec58 = Arr[F64, 3](fill=0.0)
        dsp.const278 = 0.0
        dsp.const279 = 0.0
        dsp.const280 = 0.0
        dsp.rec57 = Arr[F64, 3](fill=0.0)
        dsp.const281 = 0.0
        dsp.const282 = 0.0
        dsp.const283 = 0.0
        dsp.const284 = 0.0
        dsp.rec56 = Arr[F64, 3](fill=0.0)
        dsp.const285 = 0.0
        dsp.const286 = 0.0
        dsp.const287 = 0.0
        dsp.rec55 = Arr[F64, 3](fill=0.0)
        dsp.const288 = 0.0
        dsp.const289 = 0.0
        dsp.const290 = 0.0
        dsp.rec54 = Arr[F64, 3](fill=0.0)
        dsp.const291 = 0.0
        dsp.rec53 = Arr[F64, 2](fill=0.0)
        dsp.vbargraph7 = 0.0
        dsp.const292 = 0.0
        dsp.const293 = 0.0
        dsp.const294 = 0.0
        dsp.const295 = 0.0
        dsp.const296 = 0.0
        dsp.const297 = 0.0
        dsp.const298 = 0.0
        dsp.const299 = 0.0
        dsp.const300 = 0.0
        dsp.const301 = 0.0
        dsp.const302 = 0.0
        dsp.const303 = 0.0
        dsp.const304 = 0.0
        dsp.const305 = 0.0
        dsp.const306 = 0.0
        dsp.const307 = 0.0
        dsp.const308 = 0.0
        dsp.const309 = 0.0
        dsp.const310 = 0.0
        dsp.const311 = 0.0
        dsp.const312 = 0.0
        dsp.rec66 = Arr[F64, 3](fill=0.0)
        dsp.const313 = 0.0
        dsp.const314 = 0.0
        dsp.const315 = 0.0
        dsp.rec65 = Arr[F64, 3](fill=0.0)
        dsp.const316 = 0.0
        dsp.const317 = 0.0
        dsp.const318 = 0.0
        dsp.rec64 = Arr[F64, 3](fill=0.0)
        dsp.const319 = 0.0
        dsp.const320 = 0.0
        dsp.const321 = 0.0
        dsp.const322 = 0.0
        dsp.rec63 = Arr[F64, 3](fill=0.0)
        dsp.const323 = 0.0
        dsp.const324 = 0.0
        dsp.const325 = 0.0
        dsp.rec62 = Arr[F64, 3](fill=0.0)
        dsp.const326 = 0.0
        dsp.const327 = 0.0
        dsp.const328 = 0.0
        dsp.rec61 = Arr[F64, 3](fill=0.0)
        dsp.const329 = 0.0
        dsp.rec60 = Arr[F64, 2](fill=0.0)
        dsp.vbargraph8 = 0.0
        dsp.const330 = 0.0
        dsp.const331 = 0.0
        dsp.const332 = 0.0
        dsp.const333 = 0.0
        dsp.const334 = 0.0
        dsp.const335 = 0.0
        dsp.const336 = 0.0
        dsp.const337 = 0.0
        dsp.const338 = 0.0
        dsp.const339 = 0.0
        dsp.const340 = 0.0
        dsp.const341 = 0.0
        dsp.const342 = 0.0
        dsp.const343 = 0.0
        dsp.const344 = 0.0
        dsp.const345 = 0.0
        dsp.const346 = 0.0
        dsp.const347 = 0.0
        dsp.const348 = 0.0
        dsp.const349 = 0.0
        dsp.const350 = 0.0
        dsp.rec73 = Arr[F64, 3](fill=0.0)
        dsp.const351 = 0.0
        dsp.const352 = 0.0
        dsp.const353 = 0.0
        dsp.rec72 = Arr[F64, 3](fill=0.0)
        dsp.const354 = 0.0
        dsp.const355 = 0.0
        dsp.const356 = 0.0
        dsp.rec71 = Arr[F64, 3](fill=0.0)
        dsp.const357 = 0.0
        dsp.const358 = 0.0
        dsp.const359 = 0.0
        dsp.const360 = 0.0
        dsp.rec70 = Arr[F64, 3](fill=0.0)
        dsp.const361 = 0.0
        dsp.const362 = 0.0
        dsp.const363 = 0.0
        dsp.rec69 = Arr[F64, 3](fill=0.0)
        dsp.const364 = 0.0
        dsp.const365 = 0.0
        dsp.const366 = 0.0
        dsp.rec68 = Arr[F64, 3](fill=0.0)
        dsp.const367 = 0.0
        dsp.rec67 = Arr[F64, 2](fill=0.0)
        dsp.vbargraph9 = 0.0
        dsp.const368 = 0.0
        dsp.const369 = 0.0
        dsp.const370 = 0.0
        dsp.const371 = 0.0
        dsp.const372 = 0.0
        dsp.const373 = 0.0
        dsp.const374 = 0.0
        dsp.const375 = 0.0
        dsp.const376 = 0.0
        dsp.const377 = 0.0
        dsp.const378 = 0.0
        dsp.const379 = 0.0
        dsp.const380 = 0.0
        dsp.const381 = 0.0
        dsp.const382 = 0.0
        dsp.const383 = 0.0
        dsp.const384 = 0.0
        dsp.const385 = 0.0
        dsp.const386 = 0.0
        dsp.const387 = 0.0
        dsp.const388 = 0.0
        dsp.rec80 = Arr[F64, 3](fill=0.0)
        dsp.const389 = 0.0
        dsp.const390 = 0.0
        dsp.const391 = 0.0
        dsp.rec79 = Arr[F64, 3](fill=0.0)
        dsp.const392 = 0.0
        dsp.const393 = 0.0
        dsp.const394 = 0.0
        dsp.rec78 = Arr[F64, 3](fill=0.0)
        dsp.const395 = 0.0
        dsp.const396 = 0.0
        dsp.const397 = 0.0
        dsp.const398 = 0.0
        dsp.rec77 = Arr[F64, 3](fill=0.0)
        dsp.const399 = 0.0
        dsp.const400 = 0.0
        dsp.const401 = 0.0
        dsp.rec76 = Arr[F64, 3](fill=0.0)
        dsp.const402 = 0.0
        dsp.const403 = 0.0
        dsp.const404 = 0.0
        dsp.rec75 = Arr[F64, 3](fill=0.0)
        dsp.const405 = 0.0
        dsp.rec74 = Arr[F64, 2](fill=0.0)
        dsp.vbargraph10 = 0.0
        dsp.const406 = 0.0
        dsp.const407 = 0.0
        dsp.const408 = 0.0
        dsp.const409 = 0.0
        dsp.const410 = 0.0
        dsp.const411 = 0.0
        dsp.const412 = 0.0
        dsp.const413 = 0.0
        dsp.const414 = 0.0
        dsp.const415 = 0.0
        dsp.const416 = 0.0
        dsp.const417 = 0.0
        dsp.const418 = 0.0
        dsp.const419 = 0.0
        dsp.const420 = 0.0
        dsp.const421 = 0.0
        dsp.const422 = 0.0
        dsp.const423 = 0.0
        dsp.const424 = 0.0
        dsp.const425 = 0.0
        dsp.const426 = 0.0
        dsp.rec87 = Arr[F64, 3](fill=0.0)
        dsp.const427 = 0.0
        dsp.const428 = 0.0
        dsp.const429 = 0.0
        dsp.rec86 = Arr[F64, 3](fill=0.0)
        dsp.const430 = 0.0
        dsp.const431 = 0.0
        dsp.const432 = 0.0
        dsp.rec85 = Arr[F64, 3](fill=0.0)
        dsp.const433 = 0.0
        dsp.const434 = 0.0
        dsp.const435 = 0.0
        dsp.const436 = 0.0
        dsp.rec84 = Arr[F64, 3](fill=0.0)
        dsp.const437 = 0.0
        dsp.const438 = 0.0
        dsp.const439 = 0.0
        dsp.rec83 = Arr[F64, 3](fill=0.0)
        dsp.const440 = 0.0
        dsp.const441 = 0.0
        dsp.const442 = 0.0
        dsp.rec82 = Arr[F64, 3](fill=0.0)
        dsp.const443 = 0.0
        dsp.rec81 = Arr[F64, 2](fill=0.0)
        dsp.vbargraph11 = 0.0
        dsp.const444 = 0.0
        dsp.const445 = 0.0
        dsp.const446 = 0.0
        dsp.const447 = 0.0
        dsp.const448 = 0.0
        dsp.const449 = 0.0
        dsp.const450 = 0.0
        dsp.const451 = 0.0
        dsp.const452 = 0.0
        dsp.const453 = 0.0
        dsp.const454 = 0.0
        dsp.const455 = 0.0
        dsp.const456 = 0.0
        dsp.const457 = 0.0
        dsp.const458 = 0.0
        dsp.const459 = 0.0
        dsp.const460 = 0.0
        dsp.const461 = 0.0
        dsp.const462 = 0.0
        dsp.const463 = 0.0
        dsp.const464 = 0.0
        dsp.rec94 = Arr[F64, 3](fill=0.0)
        dsp.const465 = 0.0
        dsp.const466 = 0.0
        dsp.const467 = 0.0
        dsp.rec93 = Arr[F64, 3](fill=0.0)
        dsp.const468 = 0.0
        dsp.const469 = 0.0
        dsp.const470 = 0.0
        dsp.rec92 = Arr[F64, 3](fill=0.0)
        dsp.const471 = 0.0
        dsp.const472 = 0.0
        dsp.const473 = 0.0
        dsp.const474 = 0.0
        dsp.rec91 = Arr[F64, 3](fill=0.0)
        dsp.const475 = 0.0
        dsp.const476 = 0.0
        dsp.const477 = 0.0
        dsp.rec90 = Arr[F64, 3](fill=0.0)
        dsp.const478 = 0.0
        dsp.const479 = 0.0
        dsp.const480 = 0.0
        dsp.rec89 = Arr[F64, 3](fill=0.0)
        dsp.const481 = 0.0
        dsp.rec88 = Arr[F64, 2](fill=0.0)
        dsp.vbargraph12 = 0.0
        dsp.const482 = 0.0
        dsp.const483 = 0.0
        dsp.const484 = 0.0
        dsp.const485 = 0.0
        dsp.const486 = 0.0
        dsp.const487 = 0.0
        dsp.const488 = 0.0
        dsp.const489 = 0.0
        dsp.const490 = 0.0
        dsp.const491 = 0.0
        dsp.const492 = 0.0
        dsp.const493 = 0.0
        dsp.const494 = 0.0
        dsp.const495 = 0.0
        dsp.const496 = 0.0
        dsp.const497 = 0.0
        dsp.const498 = 0.0
        dsp.const499 = 0.0
        dsp.const500 = 0.0
        dsp.const501 = 0.0
        dsp.const502 = 0.0
        dsp.rec101 = Arr[F64, 3](fill=0.0)
        dsp.const503 = 0.0
        dsp.const504 = 0.0
        dsp.const505 = 0.0
        dsp.rec100 = Arr[F64, 3](fill=0.0)
        dsp.const506 = 0.0
        dsp.const507 = 0.0
        dsp.const508 = 0.0
        dsp.rec99 = Arr[F64, 3](fill=0.0)
        dsp.const509 = 0.0
        dsp.const510 = 0.0
        dsp.const511 = 0.0
        dsp.const512 = 0.0
        dsp.rec98 = Arr[F64, 3](fill=0.0)
        dsp.const513 = 0.0
        dsp.const514 = 0.0
        dsp.const515 = 0.0
        dsp.rec97 = Arr[F64, 3](fill=0.0)
        dsp.const516 = 0.0
        dsp.const517 = 0.0
        dsp.const518 = 0.0
        dsp.rec96 = Arr[F64, 3](fill=0.0)
        dsp.const519 = 0.0
        dsp.rec95 = Arr[F64, 2](fill=0.0)
        dsp.vbargraph13 = 0.0
        dsp.const520 = 0.0
        dsp.const521 = 0.0
        dsp.const522 = 0.0
        dsp.const523 = 0.0
        dsp.const524 = 0.0
        dsp.const525 = 0.0
        dsp.const526 = 0.0
        dsp.const527 = 0.0
        dsp.const528 = 0.0
        dsp.rec105 = Arr[F64, 3](fill=0.0)
        dsp.const529 = 0.0
        dsp.const530 = 0.0
        dsp.const531 = 0.0
        dsp.rec104 = Arr[F64, 3](fill=0.0)
        dsp.const532 = 0.0
        dsp.const533 = 0.0
        dsp.const534 = 0.0
        dsp.rec103 = Arr[F64, 3](fill=0.0)
        dsp.const535 = 0.0
        dsp.rec102 = Arr[F64, 2](fill=0.0)
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
        dsp.const1 = (1e+03) / (dsp.const0)
        dsp.const2 = tan((50265.48245743669) / (dsp.const0))
        dsp.const3 = (1.0) / (dsp.const2)
        dsp.const4 = (1.0) / ((((dsp.const3) + (0.157482159302087)) / (dsp.const2)) + (0.9351401670315425))
        dsp.const5 = pow_unrolled[2](dsp.const2)
        dsp.const6 = (50.063807016150385) / (dsp.const5)
        dsp.const7 = (dsp.const6) + (0.9351401670315425)
        dsp.const8 = (1.0) / ((((dsp.const3) + (0.7431304601070396)) / (dsp.const2)) + (1.450071084655647))
        dsp.const9 = (11.052052171507189) / (dsp.const5)
        dsp.const10 = (dsp.const9) + (1.450071084655647)
        dsp.const11 = (1.0) / ((((dsp.const3) + (3.1897274020965583)) / (dsp.const2)) + (4.076781969643807))
        dsp.const12 = (0.0017661728399818856) / (dsp.const5)
        dsp.const13 = (dsp.const12) + (0.00040767818495825777)
        dsp.const14 = (6.283185307179586) / (dsp.const0)
        dsp.const15 = (1.0) / (dsp.const0)
        dsp.const16 = (((dsp.const3) + (-3.1897274020965583)) / (dsp.const2)) + (4.076781969643807)
        dsp.const17 = (1.0) / (dsp.const5)
        dsp.const18 = (2.0) * ((4.076781969643807) - (dsp.const17))
        dsp.const19 = (2.0) * ((0.00040767818495825777) - (dsp.const12))
        dsp.const20 = (((dsp.const3) + (-0.7431304601070396)) / (dsp.const2)) + (1.450071084655647)
        dsp.const21 = (2.0) * ((1.450071084655647) - (dsp.const17))
        dsp.const22 = (2.0) * ((1.450071084655647) - (dsp.const9))
        dsp.const23 = (((dsp.const3) + (-0.157482159302087)) / (dsp.const2)) + (0.9351401670315425)
        dsp.const24 = (2.0) * ((0.9351401670315425) - (dsp.const17))
        dsp.const25 = (2.0) * ((0.9351401670315425) - (dsp.const6))
        dsp.const26 = tan((31665.269715622984) / (dsp.const0))
        dsp.const27 = (1.0) / (dsp.const26)
        dsp.const28 = (1.0) / ((((dsp.const27) + (0.157482159302087)) / (dsp.const26)) + (0.9351401670315425))
        dsp.const29 = pow_unrolled[2](dsp.const26)
        dsp.const30 = (50.063807016150385) / (dsp.const29)
        dsp.const31 = (dsp.const30) + (0.9351401670315425)
        dsp.const32 = (1.0) / ((((dsp.const27) + (0.7431304601070396)) / (dsp.const26)) + (1.450071084655647))
        dsp.const33 = (11.052052171507189) / (dsp.const29)
        dsp.const34 = (dsp.const33) + (1.450071084655647)
        dsp.const35 = (1.0) / ((((dsp.const27) + (3.1897274020965583)) / (dsp.const26)) + (4.076781969643807))
        dsp.const36 = (0.0017661728399818856) / (dsp.const29)
        dsp.const37 = (dsp.const36) + (0.00040767818495825777)
        dsp.const38 = (1.0) / ((((dsp.const3) + (0.168404871113589)) / (dsp.const2)) + (1.069358407707312))
        dsp.const39 = (dsp.const17) + (53.53615295455673)
        dsp.const40 = (1.0) / ((((dsp.const3) + (0.512478641889141)) / (dsp.const2)) + (0.689621364484675))
        dsp.const41 = (dsp.const17) + (7.621731298870603)
        dsp.const42 = (1.0) / ((((dsp.const3) + (0.782413046821645)) / (dsp.const2)) + (0.24529150870616))
        dsp.const43 = (9.9999997055e-05) / (dsp.const5)
        dsp.const44 = (dsp.const43) + (0.000433227200555)
        dsp.const45 = (((dsp.const3) + (-0.782413046821645)) / (dsp.const2)) + (0.24529150870616)
        dsp.const46 = (2.0) * ((0.24529150870616) - (dsp.const17))
        dsp.const47 = (2.0) * ((0.000433227200555) - (dsp.const43))
        dsp.const48 = (((dsp.const3) + (-0.512478641889141)) / (dsp.const2)) + (0.689621364484675)
        dsp.const49 = (2.0) * ((0.689621364484675) - (dsp.const17))
        dsp.const50 = (2.0) * ((7.621731298870603) - (dsp.const17))
        dsp.const51 = (((dsp.const3) + (-0.168404871113589)) / (dsp.const2)) + (1.069358407707312)
        dsp.const52 = (2.0) * ((1.069358407707312) - (dsp.const17))
        dsp.const53 = (2.0) * ((53.53615295455673) - (dsp.const17))
        dsp.const54 = (((dsp.const27) + (-3.1897274020965583)) / (dsp.const26)) + (4.076781969643807)
        dsp.const55 = (1.0) / (dsp.const29)
        dsp.const56 = (2.0) * ((4.076781969643807) - (dsp.const55))
        dsp.const57 = (2.0) * ((0.00040767818495825777) - (dsp.const36))
        dsp.const58 = (((dsp.const27) + (-0.7431304601070396)) / (dsp.const26)) + (1.450071084655647)
        dsp.const59 = (2.0) * ((1.450071084655647) - (dsp.const55))
        dsp.const60 = (2.0) * ((1.450071084655647) - (dsp.const33))
        dsp.const61 = (((dsp.const27) + (-0.157482159302087)) / (dsp.const26)) + (0.9351401670315425)
        dsp.const62 = (2.0) * ((0.9351401670315425) - (dsp.const55))
        dsp.const63 = (2.0) * ((0.9351401670315425) - (dsp.const30))
        dsp.const64 = tan((19947.869932656024) / (dsp.const0))
        dsp.const65 = (1.0) / (dsp.const64)
        dsp.const66 = (1.0) / ((((dsp.const65) + (0.157482159302087)) / (dsp.const64)) + (0.9351401670315425))
        dsp.const67 = pow_unrolled[2](dsp.const64)
        dsp.const68 = (50.063807016150385) / (dsp.const67)
        dsp.const69 = (dsp.const68) + (0.9351401670315425)
        dsp.const70 = (1.0) / ((((dsp.const65) + (0.7431304601070396)) / (dsp.const64)) + (1.450071084655647))
        dsp.const71 = (11.052052171507189) / (dsp.const67)
        dsp.const72 = (dsp.const71) + (1.450071084655647)
        dsp.const73 = (1.0) / ((((dsp.const65) + (3.1897274020965583)) / (dsp.const64)) + (4.076781969643807))
        dsp.const74 = (0.0017661728399818856) / (dsp.const67)
        dsp.const75 = (dsp.const74) + (0.00040767818495825777)
        dsp.const76 = (1.0) / ((((dsp.const27) + (0.168404871113589)) / (dsp.const26)) + (1.069358407707312))
        dsp.const77 = (dsp.const55) + (53.53615295455673)
        dsp.const78 = (1.0) / ((((dsp.const27) + (0.512478641889141)) / (dsp.const26)) + (0.689621364484675))
        dsp.const79 = (dsp.const55) + (7.621731298870603)
        dsp.const80 = (1.0) / ((((dsp.const27) + (0.782413046821645)) / (dsp.const26)) + (0.24529150870616))
        dsp.const81 = (9.9999997055e-05) / (dsp.const29)
        dsp.const82 = (dsp.const81) + (0.000433227200555)
        dsp.const83 = (((dsp.const27) + (-0.782413046821645)) / (dsp.const26)) + (0.24529150870616)
        dsp.const84 = (2.0) * ((0.24529150870616) - (dsp.const55))
        dsp.const85 = (2.0) * ((0.000433227200555) - (dsp.const81))
        dsp.const86 = (((dsp.const27) + (-0.512478641889141)) / (dsp.const26)) + (0.689621364484675)
        dsp.const87 = (2.0) * ((0.689621364484675) - (dsp.const55))
        dsp.const88 = (2.0) * ((7.621731298870603) - (dsp.const55))
        dsp.const89 = (((dsp.const27) + (-0.168404871113589)) / (dsp.const26)) + (1.069358407707312)
        dsp.const90 = (2.0) * ((1.069358407707312) - (dsp.const55))
        dsp.const91 = (2.0) * ((53.53615295455673) - (dsp.const55))
        dsp.const92 = (((dsp.const65) + (-3.1897274020965583)) / (dsp.const64)) + (4.076781969643807)
        dsp.const93 = (1.0) / (dsp.const67)
        dsp.const94 = (2.0) * ((4.076781969643807) - (dsp.const93))
        dsp.const95 = (2.0) * ((0.00040767818495825777) - (dsp.const74))
        dsp.const96 = (((dsp.const65) + (-0.7431304601070396)) / (dsp.const64)) + (1.450071084655647)
        dsp.const97 = (2.0) * ((1.450071084655647) - (dsp.const93))
        dsp.const98 = (2.0) * ((1.450071084655647) - (dsp.const71))
        dsp.const99 = (((dsp.const65) + (-0.157482159302087)) / (dsp.const64)) + (0.9351401670315425)
        dsp.const100 = (2.0) * ((0.9351401670315425) - (dsp.const93))
        dsp.const101 = (2.0) * ((0.9351401670315425) - (dsp.const68))
        dsp.const102 = tan((12566.370614359172) / (dsp.const0))
        dsp.const103 = (1.0) / (dsp.const102)
        dsp.const104 = (1.0) / ((((dsp.const103) + (0.157482159302087)) / (dsp.const102)) + (0.9351401670315425))
        dsp.const105 = pow_unrolled[2](dsp.const102)
        dsp.const106 = (50.063807016150385) / (dsp.const105)
        dsp.const107 = (dsp.const106) + (0.9351401670315425)
        dsp.const108 = (1.0) / ((((dsp.const103) + (0.7431304601070396)) / (dsp.const102)) + (1.450071084655647))
        dsp.const109 = (11.052052171507189) / (dsp.const105)
        dsp.const110 = (dsp.const109) + (1.450071084655647)
        dsp.const111 = (1.0) / ((((dsp.const103) + (3.1897274020965583)) / (dsp.const102)) + (4.076781969643807))
        dsp.const112 = (0.0017661728399818856) / (dsp.const105)
        dsp.const113 = (dsp.const112) + (0.00040767818495825777)
        dsp.const114 = (1.0) / ((((dsp.const65) + (0.168404871113589)) / (dsp.const64)) + (1.069358407707312))
        dsp.const115 = (dsp.const93) + (53.53615295455673)
        dsp.const116 = (1.0) / ((((dsp.const65) + (0.512478641889141)) / (dsp.const64)) + (0.689621364484675))
        dsp.const117 = (dsp.const93) + (7.621731298870603)
        dsp.const118 = (1.0) / ((((dsp.const65) + (0.782413046821645)) / (dsp.const64)) + (0.24529150870616))
        dsp.const119 = (9.9999997055e-05) / (dsp.const67)
        dsp.const120 = (dsp.const119) + (0.000433227200555)
        dsp.const121 = (((dsp.const65) + (-0.782413046821645)) / (dsp.const64)) + (0.24529150870616)
        dsp.const122 = (2.0) * ((0.24529150870616) - (dsp.const93))
        dsp.const123 = (2.0) * ((0.000433227200555) - (dsp.const119))
        dsp.const124 = (((dsp.const65) + (-0.512478641889141)) / (dsp.const64)) + (0.689621364484675)
        dsp.const125 = (2.0) * ((0.689621364484675) - (dsp.const93))
        dsp.const126 = (2.0) * ((7.621731298870603) - (dsp.const93))
        dsp.const127 = (((dsp.const65) + (-0.168404871113589)) / (dsp.const64)) + (1.069358407707312)
        dsp.const128 = (2.0) * ((1.069358407707312) - (dsp.const93))
        dsp.const129 = (2.0) * ((53.53615295455673) - (dsp.const93))
        dsp.const130 = (((dsp.const103) + (-3.1897274020965583)) / (dsp.const102)) + (4.076781969643807)
        dsp.const131 = (1.0) / (dsp.const105)
        dsp.const132 = (2.0) * ((4.076781969643807) - (dsp.const131))
        dsp.const133 = (2.0) * ((0.00040767818495825777) - (dsp.const112))
        dsp.const134 = (((dsp.const103) + (-0.7431304601070396)) / (dsp.const102)) + (1.450071084655647)
        dsp.const135 = (2.0) * ((1.450071084655647) - (dsp.const131))
        dsp.const136 = (2.0) * ((1.450071084655647) - (dsp.const109))
        dsp.const137 = (((dsp.const103) + (-0.157482159302087)) / (dsp.const102)) + (0.9351401670315425)
        dsp.const138 = (2.0) * ((0.9351401670315425) - (dsp.const131))
        dsp.const139 = (2.0) * ((0.9351401670315425) - (dsp.const106))
        dsp.const140 = tan((7916.317428905746) / (dsp.const0))
        dsp.const141 = (1.0) / (dsp.const140)
        dsp.const142 = (1.0) / ((((dsp.const141) + (0.157482159302087)) / (dsp.const140)) + (0.9351401670315425))
        dsp.const143 = pow_unrolled[2](dsp.const140)
        dsp.const144 = (50.063807016150385) / (dsp.const143)
        dsp.const145 = (dsp.const144) + (0.9351401670315425)
        dsp.const146 = (1.0) / ((((dsp.const141) + (0.7431304601070396)) / (dsp.const140)) + (1.450071084655647))
        dsp.const147 = (11.052052171507189) / (dsp.const143)
        dsp.const148 = (dsp.const147) + (1.450071084655647)
        dsp.const149 = (1.0) / ((((dsp.const141) + (3.1897274020965583)) / (dsp.const140)) + (4.076781969643807))
        dsp.const150 = (0.0017661728399818856) / (dsp.const143)
        dsp.const151 = (dsp.const150) + (0.00040767818495825777)
        dsp.const152 = (1.0) / ((((dsp.const103) + (0.168404871113589)) / (dsp.const102)) + (1.069358407707312))
        dsp.const153 = (dsp.const131) + (53.53615295455673)
        dsp.const154 = (1.0) / ((((dsp.const103) + (0.512478641889141)) / (dsp.const102)) + (0.689621364484675))
        dsp.const155 = (dsp.const131) + (7.621731298870603)
        dsp.const156 = (1.0) / ((((dsp.const103) + (0.782413046821645)) / (dsp.const102)) + (0.24529150870616))
        dsp.const157 = (9.9999997055e-05) / (dsp.const105)
        dsp.const158 = (dsp.const157) + (0.000433227200555)
        dsp.const159 = (((dsp.const103) + (-0.782413046821645)) / (dsp.const102)) + (0.24529150870616)
        dsp.const160 = (2.0) * ((0.24529150870616) - (dsp.const131))
        dsp.const161 = (2.0) * ((0.000433227200555) - (dsp.const157))
        dsp.const162 = (((dsp.const103) + (-0.512478641889141)) / (dsp.const102)) + (0.689621364484675)
        dsp.const163 = (2.0) * ((0.689621364484675) - (dsp.const131))
        dsp.const164 = (2.0) * ((7.621731298870603) - (dsp.const131))
        dsp.const165 = (((dsp.const103) + (-0.168404871113589)) / (dsp.const102)) + (1.069358407707312)
        dsp.const166 = (2.0) * ((1.069358407707312) - (dsp.const131))
        dsp.const167 = (2.0) * ((53.53615295455673) - (dsp.const131))
        dsp.const168 = (((dsp.const141) + (-3.1897274020965583)) / (dsp.const140)) + (4.076781969643807)
        dsp.const169 = (1.0) / (dsp.const143)
        dsp.const170 = (2.0) * ((4.076781969643807) - (dsp.const169))
        dsp.const171 = (2.0) * ((0.00040767818495825777) - (dsp.const150))
        dsp.const172 = (((dsp.const141) + (-0.7431304601070396)) / (dsp.const140)) + (1.450071084655647)
        dsp.const173 = (2.0) * ((1.450071084655647) - (dsp.const169))
        dsp.const174 = (2.0) * ((1.450071084655647) - (dsp.const147))
        dsp.const175 = (((dsp.const141) + (-0.157482159302087)) / (dsp.const140)) + (0.9351401670315425)
        dsp.const176 = (2.0) * ((0.9351401670315425) - (dsp.const169))
        dsp.const177 = (2.0) * ((0.9351401670315425) - (dsp.const144))
        dsp.const178 = tan((4986.967483164005) / (dsp.const0))
        dsp.const179 = (1.0) / (dsp.const178)
        dsp.const180 = (1.0) / ((((dsp.const179) + (0.157482159302087)) / (dsp.const178)) + (0.9351401670315425))
        dsp.const181 = pow_unrolled[2](dsp.const178)
        dsp.const182 = (50.063807016150385) / (dsp.const181)
        dsp.const183 = (dsp.const182) + (0.9351401670315425)
        dsp.const184 = (1.0) / ((((dsp.const179) + (0.7431304601070396)) / (dsp.const178)) + (1.450071084655647))
        dsp.const185 = (11.052052171507189) / (dsp.const181)
        dsp.const186 = (dsp.const185) + (1.450071084655647)
        dsp.const187 = (1.0) / ((((dsp.const179) + (3.1897274020965583)) / (dsp.const178)) + (4.076781969643807))
        dsp.const188 = (0.0017661728399818856) / (dsp.const181)
        dsp.const189 = (dsp.const188) + (0.00040767818495825777)
        dsp.const190 = (1.0) / ((((dsp.const141) + (0.168404871113589)) / (dsp.const140)) + (1.069358407707312))
        dsp.const191 = (dsp.const169) + (53.53615295455673)
        dsp.const192 = (1.0) / ((((dsp.const141) + (0.512478641889141)) / (dsp.const140)) + (0.689621364484675))
        dsp.const193 = (dsp.const169) + (7.621731298870603)
        dsp.const194 = (1.0) / ((((dsp.const141) + (0.782413046821645)) / (dsp.const140)) + (0.24529150870616))
        dsp.const195 = (9.9999997055e-05) / (dsp.const143)
        dsp.const196 = (dsp.const195) + (0.000433227200555)
        dsp.const197 = (((dsp.const141) + (-0.782413046821645)) / (dsp.const140)) + (0.24529150870616)
        dsp.const198 = (2.0) * ((0.24529150870616) - (dsp.const169))
        dsp.const199 = (2.0) * ((0.000433227200555) - (dsp.const195))
        dsp.const200 = (((dsp.const141) + (-0.512478641889141)) / (dsp.const140)) + (0.689621364484675)
        dsp.const201 = (2.0) * ((0.689621364484675) - (dsp.const169))
        dsp.const202 = (2.0) * ((7.621731298870603) - (dsp.const169))
        dsp.const203 = (((dsp.const141) + (-0.168404871113589)) / (dsp.const140)) + (1.069358407707312)
        dsp.const204 = (2.0) * ((1.069358407707312) - (dsp.const169))
        dsp.const205 = (2.0) * ((53.53615295455673) - (dsp.const169))
        dsp.const206 = (((dsp.const179) + (-3.1897274020965583)) / (dsp.const178)) + (4.076781969643807)
        dsp.const207 = (1.0) / (dsp.const181)
        dsp.const208 = (2.0) * ((4.076781969643807) - (dsp.const207))
        dsp.const209 = (2.0) * ((0.00040767818495825777) - (dsp.const188))
        dsp.const210 = (((dsp.const179) + (-0.7431304601070396)) / (dsp.const178)) + (1.450071084655647)
        dsp.const211 = (2.0) * ((1.450071084655647) - (dsp.const207))
        dsp.const212 = (2.0) * ((1.450071084655647) - (dsp.const185))
        dsp.const213 = (((dsp.const179) + (-0.157482159302087)) / (dsp.const178)) + (0.9351401670315425)
        dsp.const214 = (2.0) * ((0.9351401670315425) - (dsp.const207))
        dsp.const215 = (2.0) * ((0.9351401670315425) - (dsp.const182))
        dsp.const216 = tan((3141.592653589793) / (dsp.const0))
        dsp.const217 = (1.0) / (dsp.const216)
        dsp.const218 = (1.0) / ((((dsp.const217) + (0.157482159302087)) / (dsp.const216)) + (0.9351401670315425))
        dsp.const219 = pow_unrolled[2](dsp.const216)
        dsp.const220 = (50.063807016150385) / (dsp.const219)
        dsp.const221 = (dsp.const220) + (0.9351401670315425)
        dsp.const222 = (1.0) / ((((dsp.const217) + (0.7431304601070396)) / (dsp.const216)) + (1.450071084655647))
        dsp.const223 = (11.052052171507189) / (dsp.const219)
        dsp.const224 = (dsp.const223) + (1.450071084655647)
        dsp.const225 = (1.0) / ((((dsp.const217) + (3.1897274020965583)) / (dsp.const216)) + (4.076781969643807))
        dsp.const226 = (0.0017661728399818856) / (dsp.const219)
        dsp.const227 = (dsp.const226) + (0.00040767818495825777)
        dsp.const228 = (1.0) / ((((dsp.const179) + (0.168404871113589)) / (dsp.const178)) + (1.069358407707312))
        dsp.const229 = (dsp.const207) + (53.53615295455673)
        dsp.const230 = (1.0) / ((((dsp.const179) + (0.512478641889141)) / (dsp.const178)) + (0.689621364484675))
        dsp.const231 = (dsp.const207) + (7.621731298870603)
        dsp.const232 = (1.0) / ((((dsp.const179) + (0.782413046821645)) / (dsp.const178)) + (0.24529150870616))
        dsp.const233 = (9.9999997055e-05) / (dsp.const181)
        dsp.const234 = (dsp.const233) + (0.000433227200555)
        dsp.const235 = (((dsp.const179) + (-0.782413046821645)) / (dsp.const178)) + (0.24529150870616)
        dsp.const236 = (2.0) * ((0.24529150870616) - (dsp.const207))
        dsp.const237 = (2.0) * ((0.000433227200555) - (dsp.const233))
        dsp.const238 = (((dsp.const179) + (-0.512478641889141)) / (dsp.const178)) + (0.689621364484675)
        dsp.const239 = (2.0) * ((0.689621364484675) - (dsp.const207))
        dsp.const240 = (2.0) * ((7.621731298870603) - (dsp.const207))
        dsp.const241 = (((dsp.const179) + (-0.168404871113589)) / (dsp.const178)) + (1.069358407707312)
        dsp.const242 = (2.0) * ((1.069358407707312) - (dsp.const207))
        dsp.const243 = (2.0) * ((53.53615295455673) - (dsp.const207))
        dsp.const244 = (((dsp.const217) + (-3.1897274020965583)) / (dsp.const216)) + (4.076781969643807)
        dsp.const245 = (1.0) / (dsp.const219)
        dsp.const246 = (2.0) * ((4.076781969643807) - (dsp.const245))
        dsp.const247 = (2.0) * ((0.00040767818495825777) - (dsp.const226))
        dsp.const248 = (((dsp.const217) + (-0.7431304601070396)) / (dsp.const216)) + (1.450071084655647)
        dsp.const249 = (2.0) * ((1.450071084655647) - (dsp.const245))
        dsp.const250 = (2.0) * ((1.450071084655647) - (dsp.const223))
        dsp.const251 = (((dsp.const217) + (-0.157482159302087)) / (dsp.const216)) + (0.9351401670315425)
        dsp.const252 = (2.0) * ((0.9351401670315425) - (dsp.const245))
        dsp.const253 = (2.0) * ((0.9351401670315425) - (dsp.const220))
        dsp.const254 = tan((1979.079357226436) / (dsp.const0))
        dsp.const255 = (1.0) / (dsp.const254)
        dsp.const256 = (1.0) / ((((dsp.const255) + (0.157482159302087)) / (dsp.const254)) + (0.9351401670315425))
        dsp.const257 = pow_unrolled[2](dsp.const254)
        dsp.const258 = (50.063807016150385) / (dsp.const257)
        dsp.const259 = (dsp.const258) + (0.9351401670315425)
        dsp.const260 = (1.0) / ((((dsp.const255) + (0.7431304601070396)) / (dsp.const254)) + (1.450071084655647))
        dsp.const261 = (11.052052171507189) / (dsp.const257)
        dsp.const262 = (dsp.const261) + (1.450071084655647)
        dsp.const263 = (1.0) / ((((dsp.const255) + (3.1897274020965583)) / (dsp.const254)) + (4.076781969643807))
        dsp.const264 = (0.0017661728399818856) / (dsp.const257)
        dsp.const265 = (dsp.const264) + (0.00040767818495825777)
        dsp.const266 = (1.0) / ((((dsp.const217) + (0.168404871113589)) / (dsp.const216)) + (1.069358407707312))
        dsp.const267 = (dsp.const245) + (53.53615295455673)
        dsp.const268 = (1.0) / ((((dsp.const217) + (0.512478641889141)) / (dsp.const216)) + (0.689621364484675))
        dsp.const269 = (dsp.const245) + (7.621731298870603)
        dsp.const270 = (1.0) / ((((dsp.const217) + (0.782413046821645)) / (dsp.const216)) + (0.24529150870616))
        dsp.const271 = (9.9999997055e-05) / (dsp.const219)
        dsp.const272 = (dsp.const271) + (0.000433227200555)
        dsp.const273 = (((dsp.const217) + (-0.782413046821645)) / (dsp.const216)) + (0.24529150870616)
        dsp.const274 = (2.0) * ((0.24529150870616) - (dsp.const245))
        dsp.const275 = (2.0) * ((0.000433227200555) - (dsp.const271))
        dsp.const276 = (((dsp.const217) + (-0.512478641889141)) / (dsp.const216)) + (0.689621364484675)
        dsp.const277 = (2.0) * ((0.689621364484675) - (dsp.const245))
        dsp.const278 = (2.0) * ((7.621731298870603) - (dsp.const245))
        dsp.const279 = (((dsp.const217) + (-0.168404871113589)) / (dsp.const216)) + (1.069358407707312)
        dsp.const280 = (2.0) * ((1.069358407707312) - (dsp.const245))
        dsp.const281 = (2.0) * ((53.53615295455673) - (dsp.const245))
        dsp.const282 = (((dsp.const255) + (-3.1897274020965583)) / (dsp.const254)) + (4.076781969643807)
        dsp.const283 = (1.0) / (dsp.const257)
        dsp.const284 = (2.0) * ((4.076781969643807) - (dsp.const283))
        dsp.const285 = (2.0) * ((0.00040767818495825777) - (dsp.const264))
        dsp.const286 = (((dsp.const255) + (-0.7431304601070396)) / (dsp.const254)) + (1.450071084655647)
        dsp.const287 = (2.0) * ((1.450071084655647) - (dsp.const283))
        dsp.const288 = (2.0) * ((1.450071084655647) - (dsp.const261))
        dsp.const289 = (((dsp.const255) + (-0.157482159302087)) / (dsp.const254)) + (0.9351401670315425)
        dsp.const290 = (2.0) * ((0.9351401670315425) - (dsp.const283))
        dsp.const291 = (2.0) * ((0.9351401670315425) - (dsp.const258))
        dsp.const292 = tan((1246.7418707910015) / (dsp.const0))
        dsp.const293 = (1.0) / (dsp.const292)
        dsp.const294 = (1.0) / ((((dsp.const293) + (0.157482159302087)) / (dsp.const292)) + (0.9351401670315425))
        dsp.const295 = pow_unrolled[2](dsp.const292)
        dsp.const296 = (50.063807016150385) / (dsp.const295)
        dsp.const297 = (dsp.const296) + (0.9351401670315425)
        dsp.const298 = (1.0) / ((((dsp.const293) + (0.7431304601070396)) / (dsp.const292)) + (1.450071084655647))
        dsp.const299 = (11.052052171507189) / (dsp.const295)
        dsp.const300 = (dsp.const299) + (1.450071084655647)
        dsp.const301 = (1.0) / ((((dsp.const293) + (3.1897274020965583)) / (dsp.const292)) + (4.076781969643807))
        dsp.const302 = (0.0017661728399818856) / (dsp.const295)
        dsp.const303 = (dsp.const302) + (0.00040767818495825777)
        dsp.const304 = (1.0) / ((((dsp.const255) + (0.168404871113589)) / (dsp.const254)) + (1.069358407707312))
        dsp.const305 = (dsp.const283) + (53.53615295455673)
        dsp.const306 = (1.0) / ((((dsp.const255) + (0.512478641889141)) / (dsp.const254)) + (0.689621364484675))
        dsp.const307 = (dsp.const283) + (7.621731298870603)
        dsp.const308 = (1.0) / ((((dsp.const255) + (0.782413046821645)) / (dsp.const254)) + (0.24529150870616))
        dsp.const309 = (9.9999997055e-05) / (dsp.const257)
        dsp.const310 = (dsp.const309) + (0.000433227200555)
        dsp.const311 = (((dsp.const255) + (-0.782413046821645)) / (dsp.const254)) + (0.24529150870616)
        dsp.const312 = (2.0) * ((0.24529150870616) - (dsp.const283))
        dsp.const313 = (2.0) * ((0.000433227200555) - (dsp.const309))
        dsp.const314 = (((dsp.const255) + (-0.512478641889141)) / (dsp.const254)) + (0.689621364484675)
        dsp.const315 = (2.0) * ((0.689621364484675) - (dsp.const283))
        dsp.const316 = (2.0) * ((7.621731298870603) - (dsp.const283))
        dsp.const317 = (((dsp.const255) + (-0.168404871113589)) / (dsp.const254)) + (1.069358407707312)
        dsp.const318 = (2.0) * ((1.069358407707312) - (dsp.const283))
        dsp.const319 = (2.0) * ((53.53615295455673) - (dsp.const283))
        dsp.const320 = (((dsp.const293) + (-3.1897274020965583)) / (dsp.const292)) + (4.076781969643807)
        dsp.const321 = (1.0) / (dsp.const295)
        dsp.const322 = (2.0) * ((4.076781969643807) - (dsp.const321))
        dsp.const323 = (2.0) * ((0.00040767818495825777) - (dsp.const302))
        dsp.const324 = (((dsp.const293) + (-0.7431304601070396)) / (dsp.const292)) + (1.450071084655647)
        dsp.const325 = (2.0) * ((1.450071084655647) - (dsp.const321))
        dsp.const326 = (2.0) * ((1.450071084655647) - (dsp.const299))
        dsp.const327 = (((dsp.const293) + (-0.157482159302087)) / (dsp.const292)) + (0.9351401670315425)
        dsp.const328 = (2.0) * ((0.9351401670315425) - (dsp.const321))
        dsp.const329 = (2.0) * ((0.9351401670315425) - (dsp.const296))
        dsp.const330 = tan((785.3981633974482) / (dsp.const0))
        dsp.const331 = (1.0) / (dsp.const330)
        dsp.const332 = (1.0) / ((((dsp.const331) + (0.157482159302087)) / (dsp.const330)) + (0.9351401670315425))
        dsp.const333 = pow_unrolled[2](dsp.const330)
        dsp.const334 = (50.063807016150385) / (dsp.const333)
        dsp.const335 = (dsp.const334) + (0.9351401670315425)
        dsp.const336 = (1.0) / ((((dsp.const331) + (0.7431304601070396)) / (dsp.const330)) + (1.450071084655647))
        dsp.const337 = (11.052052171507189) / (dsp.const333)
        dsp.const338 = (dsp.const337) + (1.450071084655647)
        dsp.const339 = (1.0) / ((((dsp.const331) + (3.1897274020965583)) / (dsp.const330)) + (4.076781969643807))
        dsp.const340 = (0.0017661728399818856) / (dsp.const333)
        dsp.const341 = (dsp.const340) + (0.00040767818495825777)
        dsp.const342 = (1.0) / ((((dsp.const293) + (0.168404871113589)) / (dsp.const292)) + (1.069358407707312))
        dsp.const343 = (dsp.const321) + (53.53615295455673)
        dsp.const344 = (1.0) / ((((dsp.const293) + (0.512478641889141)) / (dsp.const292)) + (0.689621364484675))
        dsp.const345 = (dsp.const321) + (7.621731298870603)
        dsp.const346 = (1.0) / ((((dsp.const293) + (0.782413046821645)) / (dsp.const292)) + (0.24529150870616))
        dsp.const347 = (9.9999997055e-05) / (dsp.const295)
        dsp.const348 = (dsp.const347) + (0.000433227200555)
        dsp.const349 = (((dsp.const293) + (-0.782413046821645)) / (dsp.const292)) + (0.24529150870616)
        dsp.const350 = (2.0) * ((0.24529150870616) - (dsp.const321))
        dsp.const351 = (2.0) * ((0.000433227200555) - (dsp.const347))
        dsp.const352 = (((dsp.const293) + (-0.512478641889141)) / (dsp.const292)) + (0.689621364484675)
        dsp.const353 = (2.0) * ((0.689621364484675) - (dsp.const321))
        dsp.const354 = (2.0) * ((7.621731298870603) - (dsp.const321))
        dsp.const355 = (((dsp.const293) + (-0.168404871113589)) / (dsp.const292)) + (1.069358407707312)
        dsp.const356 = (2.0) * ((1.069358407707312) - (dsp.const321))
        dsp.const357 = (2.0) * ((53.53615295455673) - (dsp.const321))
        dsp.const358 = (((dsp.const331) + (-3.1897274020965583)) / (dsp.const330)) + (4.076781969643807)
        dsp.const359 = (1.0) / (dsp.const333)
        dsp.const360 = (2.0) * ((4.076781969643807) - (dsp.const359))
        dsp.const361 = (2.0) * ((0.00040767818495825777) - (dsp.const340))
        dsp.const362 = (((dsp.const331) + (-0.7431304601070396)) / (dsp.const330)) + (1.450071084655647)
        dsp.const363 = (2.0) * ((1.450071084655647) - (dsp.const359))
        dsp.const364 = (2.0) * ((1.450071084655647) - (dsp.const337))
        dsp.const365 = (((dsp.const331) + (-0.157482159302087)) / (dsp.const330)) + (0.9351401670315425)
        dsp.const366 = (2.0) * ((0.9351401670315425) - (dsp.const359))
        dsp.const367 = (2.0) * ((0.9351401670315425) - (dsp.const334))
        dsp.const368 = tan((494.769839306609) / (dsp.const0))
        dsp.const369 = (1.0) / (dsp.const368)
        dsp.const370 = (1.0) / ((((dsp.const369) + (0.157482159302087)) / (dsp.const368)) + (0.9351401670315425))
        dsp.const371 = pow_unrolled[2](dsp.const368)
        dsp.const372 = (50.063807016150385) / (dsp.const371)
        dsp.const373 = (dsp.const372) + (0.9351401670315425)
        dsp.const374 = (1.0) / ((((dsp.const369) + (0.7431304601070396)) / (dsp.const368)) + (1.450071084655647))
        dsp.const375 = (11.052052171507189) / (dsp.const371)
        dsp.const376 = (dsp.const375) + (1.450071084655647)
        dsp.const377 = (1.0) / ((((dsp.const369) + (3.1897274020965583)) / (dsp.const368)) + (4.076781969643807))
        dsp.const378 = (0.0017661728399818856) / (dsp.const371)
        dsp.const379 = (dsp.const378) + (0.00040767818495825777)
        dsp.const380 = (1.0) / ((((dsp.const331) + (0.168404871113589)) / (dsp.const330)) + (1.069358407707312))
        dsp.const381 = (dsp.const359) + (53.53615295455673)
        dsp.const382 = (1.0) / ((((dsp.const331) + (0.512478641889141)) / (dsp.const330)) + (0.689621364484675))
        dsp.const383 = (dsp.const359) + (7.621731298870603)
        dsp.const384 = (1.0) / ((((dsp.const331) + (0.782413046821645)) / (dsp.const330)) + (0.24529150870616))
        dsp.const385 = (9.9999997055e-05) / (dsp.const333)
        dsp.const386 = (dsp.const385) + (0.000433227200555)
        dsp.const387 = (((dsp.const331) + (-0.782413046821645)) / (dsp.const330)) + (0.24529150870616)
        dsp.const388 = (2.0) * ((0.24529150870616) - (dsp.const359))
        dsp.const389 = (2.0) * ((0.000433227200555) - (dsp.const385))
        dsp.const390 = (((dsp.const331) + (-0.512478641889141)) / (dsp.const330)) + (0.689621364484675)
        dsp.const391 = (2.0) * ((0.689621364484675) - (dsp.const359))
        dsp.const392 = (2.0) * ((7.621731298870603) - (dsp.const359))
        dsp.const393 = (((dsp.const331) + (-0.168404871113589)) / (dsp.const330)) + (1.069358407707312)
        dsp.const394 = (2.0) * ((1.069358407707312) - (dsp.const359))
        dsp.const395 = (2.0) * ((53.53615295455673) - (dsp.const359))
        dsp.const396 = (((dsp.const369) + (-3.1897274020965583)) / (dsp.const368)) + (4.076781969643807)
        dsp.const397 = (1.0) / (dsp.const371)
        dsp.const398 = (2.0) * ((4.076781969643807) - (dsp.const397))
        dsp.const399 = (2.0) * ((0.00040767818495825777) - (dsp.const378))
        dsp.const400 = (((dsp.const369) + (-0.7431304601070396)) / (dsp.const368)) + (1.450071084655647)
        dsp.const401 = (2.0) * ((1.450071084655647) - (dsp.const397))
        dsp.const402 = (2.0) * ((1.450071084655647) - (dsp.const375))
        dsp.const403 = (((dsp.const369) + (-0.157482159302087)) / (dsp.const368)) + (0.9351401670315425)
        dsp.const404 = (2.0) * ((0.9351401670315425) - (dsp.const397))
        dsp.const405 = (2.0) * ((0.9351401670315425) - (dsp.const372))
        dsp.const406 = tan((311.68546769775037) / (dsp.const0))
        dsp.const407 = (1.0) / (dsp.const406)
        dsp.const408 = (1.0) / ((((dsp.const407) + (0.157482159302087)) / (dsp.const406)) + (0.9351401670315425))
        dsp.const409 = pow_unrolled[2](dsp.const406)
        dsp.const410 = (50.063807016150385) / (dsp.const409)
        dsp.const411 = (dsp.const410) + (0.9351401670315425)
        dsp.const412 = (1.0) / ((((dsp.const407) + (0.7431304601070396)) / (dsp.const406)) + (1.450071084655647))
        dsp.const413 = (11.052052171507189) / (dsp.const409)
        dsp.const414 = (dsp.const413) + (1.450071084655647)
        dsp.const415 = (1.0) / ((((dsp.const407) + (3.1897274020965583)) / (dsp.const406)) + (4.076781969643807))
        dsp.const416 = (0.0017661728399818856) / (dsp.const409)
        dsp.const417 = (dsp.const416) + (0.00040767818495825777)
        dsp.const418 = (1.0) / ((((dsp.const369) + (0.168404871113589)) / (dsp.const368)) + (1.069358407707312))
        dsp.const419 = (dsp.const397) + (53.53615295455673)
        dsp.const420 = (1.0) / ((((dsp.const369) + (0.512478641889141)) / (dsp.const368)) + (0.689621364484675))
        dsp.const421 = (dsp.const397) + (7.621731298870603)
        dsp.const422 = (1.0) / ((((dsp.const369) + (0.782413046821645)) / (dsp.const368)) + (0.24529150870616))
        dsp.const423 = (9.9999997055e-05) / (dsp.const371)
        dsp.const424 = (dsp.const423) + (0.000433227200555)
        dsp.const425 = (((dsp.const369) + (-0.782413046821645)) / (dsp.const368)) + (0.24529150870616)
        dsp.const426 = (2.0) * ((0.24529150870616) - (dsp.const397))
        dsp.const427 = (2.0) * ((0.000433227200555) - (dsp.const423))
        dsp.const428 = (((dsp.const369) + (-0.512478641889141)) / (dsp.const368)) + (0.689621364484675)
        dsp.const429 = (2.0) * ((0.689621364484675) - (dsp.const397))
        dsp.const430 = (2.0) * ((7.621731298870603) - (dsp.const397))
        dsp.const431 = (((dsp.const369) + (-0.168404871113589)) / (dsp.const368)) + (1.069358407707312)
        dsp.const432 = (2.0) * ((1.069358407707312) - (dsp.const397))
        dsp.const433 = (2.0) * ((53.53615295455673) - (dsp.const397))
        dsp.const434 = (((dsp.const407) + (-3.1897274020965583)) / (dsp.const406)) + (4.076781969643807)
        dsp.const435 = (1.0) / (dsp.const409)
        dsp.const436 = (2.0) * ((4.076781969643807) - (dsp.const435))
        dsp.const437 = (2.0) * ((0.00040767818495825777) - (dsp.const416))
        dsp.const438 = (((dsp.const407) + (-0.7431304601070396)) / (dsp.const406)) + (1.450071084655647)
        dsp.const439 = (2.0) * ((1.450071084655647) - (dsp.const435))
        dsp.const440 = (2.0) * ((1.450071084655647) - (dsp.const413))
        dsp.const441 = (((dsp.const407) + (-0.157482159302087)) / (dsp.const406)) + (0.9351401670315425)
        dsp.const442 = (2.0) * ((0.9351401670315425) - (dsp.const435))
        dsp.const443 = (2.0) * ((0.9351401670315425) - (dsp.const410))
        dsp.const444 = tan((196.34954084936206) / (dsp.const0))
        dsp.const445 = (1.0) / (dsp.const444)
        dsp.const446 = (1.0) / ((((dsp.const445) + (0.157482159302087)) / (dsp.const444)) + (0.9351401670315425))
        dsp.const447 = pow_unrolled[2](dsp.const444)
        dsp.const448 = (50.063807016150385) / (dsp.const447)
        dsp.const449 = (dsp.const448) + (0.9351401670315425)
        dsp.const450 = (1.0) / ((((dsp.const445) + (0.7431304601070396)) / (dsp.const444)) + (1.450071084655647))
        dsp.const451 = (11.052052171507189) / (dsp.const447)
        dsp.const452 = (dsp.const451) + (1.450071084655647)
        dsp.const453 = (1.0) / ((((dsp.const445) + (3.1897274020965583)) / (dsp.const444)) + (4.076781969643807))
        dsp.const454 = (0.0017661728399818856) / (dsp.const447)
        dsp.const455 = (dsp.const454) + (0.00040767818495825777)
        dsp.const456 = (1.0) / ((((dsp.const407) + (0.168404871113589)) / (dsp.const406)) + (1.069358407707312))
        dsp.const457 = (dsp.const435) + (53.53615295455673)
        dsp.const458 = (1.0) / ((((dsp.const407) + (0.512478641889141)) / (dsp.const406)) + (0.689621364484675))
        dsp.const459 = (dsp.const435) + (7.621731298870603)
        dsp.const460 = (1.0) / ((((dsp.const407) + (0.782413046821645)) / (dsp.const406)) + (0.24529150870616))
        dsp.const461 = (9.9999997055e-05) / (dsp.const409)
        dsp.const462 = (dsp.const461) + (0.000433227200555)
        dsp.const463 = (((dsp.const407) + (-0.782413046821645)) / (dsp.const406)) + (0.24529150870616)
        dsp.const464 = (2.0) * ((0.24529150870616) - (dsp.const435))
        dsp.const465 = (2.0) * ((0.000433227200555) - (dsp.const461))
        dsp.const466 = (((dsp.const407) + (-0.512478641889141)) / (dsp.const406)) + (0.689621364484675)
        dsp.const467 = (2.0) * ((0.689621364484675) - (dsp.const435))
        dsp.const468 = (2.0) * ((7.621731298870603) - (dsp.const435))
        dsp.const469 = (((dsp.const407) + (-0.168404871113589)) / (dsp.const406)) + (1.069358407707312)
        dsp.const470 = (2.0) * ((1.069358407707312) - (dsp.const435))
        dsp.const471 = (2.0) * ((53.53615295455673) - (dsp.const435))
        dsp.const472 = (((dsp.const445) + (-3.1897274020965583)) / (dsp.const444)) + (4.076781969643807)
        dsp.const473 = (1.0) / (dsp.const447)
        dsp.const474 = (2.0) * ((4.076781969643807) - (dsp.const473))
        dsp.const475 = (2.0) * ((0.00040767818495825777) - (dsp.const454))
        dsp.const476 = (((dsp.const445) + (-0.7431304601070396)) / (dsp.const444)) + (1.450071084655647)
        dsp.const477 = (2.0) * ((1.450071084655647) - (dsp.const473))
        dsp.const478 = (2.0) * ((1.450071084655647) - (dsp.const451))
        dsp.const479 = (((dsp.const445) + (-0.157482159302087)) / (dsp.const444)) + (0.9351401670315425)
        dsp.const480 = (2.0) * ((0.9351401670315425) - (dsp.const473))
        dsp.const481 = (2.0) * ((0.9351401670315425) - (dsp.const448))
        dsp.const482 = tan((123.69245982665232) / (dsp.const0))
        dsp.const483 = (1.0) / (dsp.const482)
        dsp.const484 = (1.0) / ((((dsp.const483) + (0.157482159302087)) / (dsp.const482)) + (0.9351401670315425))
        dsp.const485 = pow_unrolled[2](dsp.const482)
        dsp.const486 = (50.063807016150385) / (dsp.const485)
        dsp.const487 = (dsp.const486) + (0.9351401670315425)
        dsp.const488 = (1.0) / ((((dsp.const483) + (0.7431304601070396)) / (dsp.const482)) + (1.450071084655647))
        dsp.const489 = (11.052052171507189) / (dsp.const485)
        dsp.const490 = (dsp.const489) + (1.450071084655647)
        dsp.const491 = (1.0) / ((((dsp.const483) + (3.1897274020965583)) / (dsp.const482)) + (4.076781969643807))
        dsp.const492 = (0.0017661728399818856) / (dsp.const485)
        dsp.const493 = (dsp.const492) + (0.00040767818495825777)
        dsp.const494 = (1.0) / ((((dsp.const445) + (0.168404871113589)) / (dsp.const444)) + (1.069358407707312))
        dsp.const495 = (dsp.const473) + (53.53615295455673)
        dsp.const496 = (1.0) / ((((dsp.const445) + (0.512478641889141)) / (dsp.const444)) + (0.689621364484675))
        dsp.const497 = (dsp.const473) + (7.621731298870603)
        dsp.const498 = (1.0) / ((((dsp.const445) + (0.782413046821645)) / (dsp.const444)) + (0.24529150870616))
        dsp.const499 = (9.9999997055e-05) / (dsp.const447)
        dsp.const500 = (dsp.const499) + (0.000433227200555)
        dsp.const501 = (((dsp.const445) + (-0.782413046821645)) / (dsp.const444)) + (0.24529150870616)
        dsp.const502 = (2.0) * ((0.24529150870616) - (dsp.const473))
        dsp.const503 = (2.0) * ((0.000433227200555) - (dsp.const499))
        dsp.const504 = (((dsp.const445) + (-0.512478641889141)) / (dsp.const444)) + (0.689621364484675)
        dsp.const505 = (2.0) * ((0.689621364484675) - (dsp.const473))
        dsp.const506 = (2.0) * ((7.621731298870603) - (dsp.const473))
        dsp.const507 = (((dsp.const445) + (-0.168404871113589)) / (dsp.const444)) + (1.069358407707312)
        dsp.const508 = (2.0) * ((1.069358407707312) - (dsp.const473))
        dsp.const509 = (2.0) * ((53.53615295455673) - (dsp.const473))
        dsp.const510 = (((dsp.const483) + (-3.1897274020965583)) / (dsp.const482)) + (4.076781969643807)
        dsp.const511 = (1.0) / (dsp.const485)
        dsp.const512 = (2.0) * ((4.076781969643807) - (dsp.const511))
        dsp.const513 = (2.0) * ((0.00040767818495825777) - (dsp.const492))
        dsp.const514 = (((dsp.const483) + (-0.7431304601070396)) / (dsp.const482)) + (1.450071084655647)
        dsp.const515 = (2.0) * ((1.450071084655647) - (dsp.const511))
        dsp.const516 = (2.0) * ((1.450071084655647) - (dsp.const489))
        dsp.const517 = (((dsp.const483) + (-0.157482159302087)) / (dsp.const482)) + (0.9351401670315425)
        dsp.const518 = (2.0) * ((0.9351401670315425) - (dsp.const511))
        dsp.const519 = (2.0) * ((0.9351401670315425) - (dsp.const486))
        dsp.const520 = (1.0) / ((((dsp.const483) + (0.168404871113589)) / (dsp.const482)) + (1.069358407707312))
        dsp.const521 = (dsp.const511) + (53.53615295455673)
        dsp.const522 = (1.0) / ((((dsp.const483) + (0.512478641889141)) / (dsp.const482)) + (0.689621364484675))
        dsp.const523 = (dsp.const511) + (7.621731298870603)
        dsp.const524 = (1.0) / ((((dsp.const483) + (0.782413046821645)) / (dsp.const482)) + (0.24529150870616))
        dsp.const525 = (9.9999997055e-05) / (dsp.const485)
        dsp.const526 = (dsp.const525) + (0.000433227200555)
        dsp.const527 = (((dsp.const483) + (-0.782413046821645)) / (dsp.const482)) + (0.24529150870616)
        dsp.const528 = (2.0) * ((0.24529150870616) - (dsp.const511))
        dsp.const529 = (2.0) * ((0.000433227200555) - (dsp.const525))
        dsp.const530 = (((dsp.const483) + (-0.512478641889141)) / (dsp.const482)) + (0.689621364484675)
        dsp.const531 = (2.0) * ((0.689621364484675) - (dsp.const511))
        dsp.const532 = (2.0) * ((7.621731298870603) - (dsp.const511))
        dsp.const533 = (((dsp.const483) + (-0.168404871113589)) / (dsp.const482)) + (1.069358407707312)
        dsp.const534 = (2.0) * ((1.069358407707312) - (dsp.const511))
        dsp.const535 = (2.0) * ((53.53615295455673) - (dsp.const511))

    @always_inline
    def instance_reset_user_interface(mut dsp) -> None:
        dsp.hslider0 = 50.0
        dsp.hslider1 = 100.0
        dsp.checkbox0 = 0.0
        dsp.hslider2 = 0.0
        dsp.hslider3 = -20.0
        dsp.hslider4 = 0.1
        dsp.hslider5 = 49.0
        dsp.hslider6 = 0.0

    @always_inline
    def instance_clear(mut dsp) -> None:
        var l0 = S32(0)
        while (l0) < (S32(2)): 
            dsp.i_vec0[l0] = S32(0)
            l0 = (l0) + (S32(1))
        var l1 = S32(0)
        while (l1) < (S32(2)): 
            dsp.rec5[l1] = 0.0
            l1 = (l1) + (S32(1))
        var l2 = S32(0)
        while (l2) < (S32(2)): 
            dsp.rec6[l2] = 0.0
            l2 = (l2) + (S32(1))
        var l3 = S32(0)
        while (l3) < (S32(2)): 
            dsp.rec9[l3] = 0.0
            l3 = (l3) + (S32(1))
        var l4 = S32(0)
        while (l4) < (S32(2)): 
            dsp.rec7[l4] = 0.0
            l4 = (l4) + (S32(1))
        var l5 = S32(0)
        while (l5) < (S32(2)): 
            dsp.rec8[l5] = 0.0
            l5 = (l5) + (S32(1))
        var l6 = S32(0)
        while (l6) < (S32(2)): 
            dsp.rec10[l6] = 0.0
            l6 = (l6) + (S32(1))
        var l7 = S32(0)
        while (l7) < (S32(2)): 
            dsp.vec1[l7] = 0.0
            l7 = (l7) + (S32(1))
        var l8 = S32(0)
        while (l8) < (S32(2)): 
            dsp.rec4[l8] = 0.0
            l8 = (l8) + (S32(1))
        var l9 = S32(0)
        while (l9) < (S32(3)): 
            dsp.rec3[l9] = 0.0
            l9 = (l9) + (S32(1))
        var l10 = S32(0)
        while (l10) < (S32(3)): 
            dsp.rec2[l10] = 0.0
            l10 = (l10) + (S32(1))
        var l11 = S32(0)
        while (l11) < (S32(3)): 
            dsp.rec1[l11] = 0.0
            l11 = (l11) + (S32(1))
        var l12 = S32(0)
        while (l12) < (S32(2)): 
            dsp.rec0[l12] = 0.0
            l12 = (l12) + (S32(1))
        var l13 = S32(0)
        while (l13) < (S32(3)): 
            dsp.rec17[l13] = 0.0
            l13 = (l13) + (S32(1))
        var l14 = S32(0)
        while (l14) < (S32(3)): 
            dsp.rec16[l14] = 0.0
            l14 = (l14) + (S32(1))
        var l15 = S32(0)
        while (l15) < (S32(3)): 
            dsp.rec15[l15] = 0.0
            l15 = (l15) + (S32(1))
        var l16 = S32(0)
        while (l16) < (S32(3)): 
            dsp.rec14[l16] = 0.0
            l16 = (l16) + (S32(1))
        var l17 = S32(0)
        while (l17) < (S32(3)): 
            dsp.rec13[l17] = 0.0
            l17 = (l17) + (S32(1))
        var l18 = S32(0)
        while (l18) < (S32(3)): 
            dsp.rec12[l18] = 0.0
            l18 = (l18) + (S32(1))
        var l19 = S32(0)
        while (l19) < (S32(2)): 
            dsp.rec11[l19] = 0.0
            l19 = (l19) + (S32(1))
        var l20 = S32(0)
        while (l20) < (S32(3)): 
            dsp.rec24[l20] = 0.0
            l20 = (l20) + (S32(1))
        var l21 = S32(0)
        while (l21) < (S32(3)): 
            dsp.rec23[l21] = 0.0
            l21 = (l21) + (S32(1))
        var l22 = S32(0)
        while (l22) < (S32(3)): 
            dsp.rec22[l22] = 0.0
            l22 = (l22) + (S32(1))
        var l23 = S32(0)
        while (l23) < (S32(3)): 
            dsp.rec21[l23] = 0.0
            l23 = (l23) + (S32(1))
        var l24 = S32(0)
        while (l24) < (S32(3)): 
            dsp.rec20[l24] = 0.0
            l24 = (l24) + (S32(1))
        var l25 = S32(0)
        while (l25) < (S32(3)): 
            dsp.rec19[l25] = 0.0
            l25 = (l25) + (S32(1))
        var l26 = S32(0)
        while (l26) < (S32(2)): 
            dsp.rec18[l26] = 0.0
            l26 = (l26) + (S32(1))
        var l27 = S32(0)
        while (l27) < (S32(3)): 
            dsp.rec31[l27] = 0.0
            l27 = (l27) + (S32(1))
        var l28 = S32(0)
        while (l28) < (S32(3)): 
            dsp.rec30[l28] = 0.0
            l28 = (l28) + (S32(1))
        var l29 = S32(0)
        while (l29) < (S32(3)): 
            dsp.rec29[l29] = 0.0
            l29 = (l29) + (S32(1))
        var l30 = S32(0)
        while (l30) < (S32(3)): 
            dsp.rec28[l30] = 0.0
            l30 = (l30) + (S32(1))
        var l31 = S32(0)
        while (l31) < (S32(3)): 
            dsp.rec27[l31] = 0.0
            l31 = (l31) + (S32(1))
        var l32 = S32(0)
        while (l32) < (S32(3)): 
            dsp.rec26[l32] = 0.0
            l32 = (l32) + (S32(1))
        var l33 = S32(0)
        while (l33) < (S32(2)): 
            dsp.rec25[l33] = 0.0
            l33 = (l33) + (S32(1))
        var l34 = S32(0)
        while (l34) < (S32(3)): 
            dsp.rec38[l34] = 0.0
            l34 = (l34) + (S32(1))
        var l35 = S32(0)
        while (l35) < (S32(3)): 
            dsp.rec37[l35] = 0.0
            l35 = (l35) + (S32(1))
        var l36 = S32(0)
        while (l36) < (S32(3)): 
            dsp.rec36[l36] = 0.0
            l36 = (l36) + (S32(1))
        var l37 = S32(0)
        while (l37) < (S32(3)): 
            dsp.rec35[l37] = 0.0
            l37 = (l37) + (S32(1))
        var l38 = S32(0)
        while (l38) < (S32(3)): 
            dsp.rec34[l38] = 0.0
            l38 = (l38) + (S32(1))
        var l39 = S32(0)
        while (l39) < (S32(3)): 
            dsp.rec33[l39] = 0.0
            l39 = (l39) + (S32(1))
        var l40 = S32(0)
        while (l40) < (S32(2)): 
            dsp.rec32[l40] = 0.0
            l40 = (l40) + (S32(1))
        var l41 = S32(0)
        while (l41) < (S32(3)): 
            dsp.rec45[l41] = 0.0
            l41 = (l41) + (S32(1))
        var l42 = S32(0)
        while (l42) < (S32(3)): 
            dsp.rec44[l42] = 0.0
            l42 = (l42) + (S32(1))
        var l43 = S32(0)
        while (l43) < (S32(3)): 
            dsp.rec43[l43] = 0.0
            l43 = (l43) + (S32(1))
        var l44 = S32(0)
        while (l44) < (S32(3)): 
            dsp.rec42[l44] = 0.0
            l44 = (l44) + (S32(1))
        var l45 = S32(0)
        while (l45) < (S32(3)): 
            dsp.rec41[l45] = 0.0
            l45 = (l45) + (S32(1))
        var l46 = S32(0)
        while (l46) < (S32(3)): 
            dsp.rec40[l46] = 0.0
            l46 = (l46) + (S32(1))
        var l47 = S32(0)
        while (l47) < (S32(2)): 
            dsp.rec39[l47] = 0.0
            l47 = (l47) + (S32(1))
        var l48 = S32(0)
        while (l48) < (S32(3)): 
            dsp.rec52[l48] = 0.0
            l48 = (l48) + (S32(1))
        var l49 = S32(0)
        while (l49) < (S32(3)): 
            dsp.rec51[l49] = 0.0
            l49 = (l49) + (S32(1))
        var l50 = S32(0)
        while (l50) < (S32(3)): 
            dsp.rec50[l50] = 0.0
            l50 = (l50) + (S32(1))
        var l51 = S32(0)
        while (l51) < (S32(3)): 
            dsp.rec49[l51] = 0.0
            l51 = (l51) + (S32(1))
        var l52 = S32(0)
        while (l52) < (S32(3)): 
            dsp.rec48[l52] = 0.0
            l52 = (l52) + (S32(1))
        var l53 = S32(0)
        while (l53) < (S32(3)): 
            dsp.rec47[l53] = 0.0
            l53 = (l53) + (S32(1))
        var l54 = S32(0)
        while (l54) < (S32(2)): 
            dsp.rec46[l54] = 0.0
            l54 = (l54) + (S32(1))
        var l55 = S32(0)
        while (l55) < (S32(3)): 
            dsp.rec59[l55] = 0.0
            l55 = (l55) + (S32(1))
        var l56 = S32(0)
        while (l56) < (S32(3)): 
            dsp.rec58[l56] = 0.0
            l56 = (l56) + (S32(1))
        var l57 = S32(0)
        while (l57) < (S32(3)): 
            dsp.rec57[l57] = 0.0
            l57 = (l57) + (S32(1))
        var l58 = S32(0)
        while (l58) < (S32(3)): 
            dsp.rec56[l58] = 0.0
            l58 = (l58) + (S32(1))
        var l59 = S32(0)
        while (l59) < (S32(3)): 
            dsp.rec55[l59] = 0.0
            l59 = (l59) + (S32(1))
        var l60 = S32(0)
        while (l60) < (S32(3)): 
            dsp.rec54[l60] = 0.0
            l60 = (l60) + (S32(1))
        var l61 = S32(0)
        while (l61) < (S32(2)): 
            dsp.rec53[l61] = 0.0
            l61 = (l61) + (S32(1))
        var l62 = S32(0)
        while (l62) < (S32(3)): 
            dsp.rec66[l62] = 0.0
            l62 = (l62) + (S32(1))
        var l63 = S32(0)
        while (l63) < (S32(3)): 
            dsp.rec65[l63] = 0.0
            l63 = (l63) + (S32(1))
        var l64 = S32(0)
        while (l64) < (S32(3)): 
            dsp.rec64[l64] = 0.0
            l64 = (l64) + (S32(1))
        var l65 = S32(0)
        while (l65) < (S32(3)): 
            dsp.rec63[l65] = 0.0
            l65 = (l65) + (S32(1))
        var l66 = S32(0)
        while (l66) < (S32(3)): 
            dsp.rec62[l66] = 0.0
            l66 = (l66) + (S32(1))
        var l67 = S32(0)
        while (l67) < (S32(3)): 
            dsp.rec61[l67] = 0.0
            l67 = (l67) + (S32(1))
        var l68 = S32(0)
        while (l68) < (S32(2)): 
            dsp.rec60[l68] = 0.0
            l68 = (l68) + (S32(1))
        var l69 = S32(0)
        while (l69) < (S32(3)): 
            dsp.rec73[l69] = 0.0
            l69 = (l69) + (S32(1))
        var l70 = S32(0)
        while (l70) < (S32(3)): 
            dsp.rec72[l70] = 0.0
            l70 = (l70) + (S32(1))
        var l71 = S32(0)
        while (l71) < (S32(3)): 
            dsp.rec71[l71] = 0.0
            l71 = (l71) + (S32(1))
        var l72 = S32(0)
        while (l72) < (S32(3)): 
            dsp.rec70[l72] = 0.0
            l72 = (l72) + (S32(1))
        var l73 = S32(0)
        while (l73) < (S32(3)): 
            dsp.rec69[l73] = 0.0
            l73 = (l73) + (S32(1))
        var l74 = S32(0)
        while (l74) < (S32(3)): 
            dsp.rec68[l74] = 0.0
            l74 = (l74) + (S32(1))
        var l75 = S32(0)
        while (l75) < (S32(2)): 
            dsp.rec67[l75] = 0.0
            l75 = (l75) + (S32(1))
        var l76 = S32(0)
        while (l76) < (S32(3)): 
            dsp.rec80[l76] = 0.0
            l76 = (l76) + (S32(1))
        var l77 = S32(0)
        while (l77) < (S32(3)): 
            dsp.rec79[l77] = 0.0
            l77 = (l77) + (S32(1))
        var l78 = S32(0)
        while (l78) < (S32(3)): 
            dsp.rec78[l78] = 0.0
            l78 = (l78) + (S32(1))
        var l79 = S32(0)
        while (l79) < (S32(3)): 
            dsp.rec77[l79] = 0.0
            l79 = (l79) + (S32(1))
        var l80 = S32(0)
        while (l80) < (S32(3)): 
            dsp.rec76[l80] = 0.0
            l80 = (l80) + (S32(1))
        var l81 = S32(0)
        while (l81) < (S32(3)): 
            dsp.rec75[l81] = 0.0
            l81 = (l81) + (S32(1))
        var l82 = S32(0)
        while (l82) < (S32(2)): 
            dsp.rec74[l82] = 0.0
            l82 = (l82) + (S32(1))
        var l83 = S32(0)
        while (l83) < (S32(3)): 
            dsp.rec87[l83] = 0.0
            l83 = (l83) + (S32(1))
        var l84 = S32(0)
        while (l84) < (S32(3)): 
            dsp.rec86[l84] = 0.0
            l84 = (l84) + (S32(1))
        var l85 = S32(0)
        while (l85) < (S32(3)): 
            dsp.rec85[l85] = 0.0
            l85 = (l85) + (S32(1))
        var l86 = S32(0)
        while (l86) < (S32(3)): 
            dsp.rec84[l86] = 0.0
            l86 = (l86) + (S32(1))
        var l87 = S32(0)
        while (l87) < (S32(3)): 
            dsp.rec83[l87] = 0.0
            l87 = (l87) + (S32(1))
        var l88 = S32(0)
        while (l88) < (S32(3)): 
            dsp.rec82[l88] = 0.0
            l88 = (l88) + (S32(1))
        var l89 = S32(0)
        while (l89) < (S32(2)): 
            dsp.rec81[l89] = 0.0
            l89 = (l89) + (S32(1))
        var l90 = S32(0)
        while (l90) < (S32(3)): 
            dsp.rec94[l90] = 0.0
            l90 = (l90) + (S32(1))
        var l91 = S32(0)
        while (l91) < (S32(3)): 
            dsp.rec93[l91] = 0.0
            l91 = (l91) + (S32(1))
        var l92 = S32(0)
        while (l92) < (S32(3)): 
            dsp.rec92[l92] = 0.0
            l92 = (l92) + (S32(1))
        var l93 = S32(0)
        while (l93) < (S32(3)): 
            dsp.rec91[l93] = 0.0
            l93 = (l93) + (S32(1))
        var l94 = S32(0)
        while (l94) < (S32(3)): 
            dsp.rec90[l94] = 0.0
            l94 = (l94) + (S32(1))
        var l95 = S32(0)
        while (l95) < (S32(3)): 
            dsp.rec89[l95] = 0.0
            l95 = (l95) + (S32(1))
        var l96 = S32(0)
        while (l96) < (S32(2)): 
            dsp.rec88[l96] = 0.0
            l96 = (l96) + (S32(1))
        var l97 = S32(0)
        while (l97) < (S32(3)): 
            dsp.rec101[l97] = 0.0
            l97 = (l97) + (S32(1))
        var l98 = S32(0)
        while (l98) < (S32(3)): 
            dsp.rec100[l98] = 0.0
            l98 = (l98) + (S32(1))
        var l99 = S32(0)
        while (l99) < (S32(3)): 
            dsp.rec99[l99] = 0.0
            l99 = (l99) + (S32(1))
        var l100 = S32(0)
        while (l100) < (S32(3)): 
            dsp.rec98[l100] = 0.0
            l100 = (l100) + (S32(1))
        var l101 = S32(0)
        while (l101) < (S32(3)): 
            dsp.rec97[l101] = 0.0
            l101 = (l101) + (S32(1))
        var l102 = S32(0)
        while (l102) < (S32(3)): 
            dsp.rec96[l102] = 0.0
            l102 = (l102) + (S32(1))
        var l103 = S32(0)
        while (l103) < (S32(2)): 
            dsp.rec95[l103] = 0.0
            l103 = (l103) + (S32(1))
        var l104 = S32(0)
        while (l104) < (S32(3)): 
            dsp.rec105[l104] = 0.0
            l104 = (l104) + (S32(1))
        var l105 = S32(0)
        while (l105) < (S32(3)): 
            dsp.rec104[l105] = 0.0
            l105 = (l105) + (S32(1))
        var l106 = S32(0)
        while (l106) < (S32(3)): 
            dsp.rec103[l106] = 0.0
            l106 = (l106) + (S32(1))
        var l107 = S32(0)
        while (l107) < (S32(2)): 
            dsp.rec102[l107] = 0.0
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
        return "{\"name\": \"cubic_distortion\",\"filename\": \"cubic_distortion.dsp\",\"version\": \"2.85.5\",\"compile_options\": \"-a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0\",\"library_list\": [\"/usr/local/share/faust/oscillator.lib\",\"/usr/local/share/faust/music.lib\",\"/usr/local/share/faust/math.lib\",\"/usr/local/share/faust/filter.lib\",\"/usr/local/share/faust/effect.lib\"],\"include_pathnames\": [\"/Users/manuelfarzini/Personal/dev/repo/faust/build/share/faust\",\"/usr/local/share/faust\",\"/usr/share/faust\",\"/Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/dsp\",\"/Users/manuelfarzini/Personal/dev/repo/faust/tests/impulse-tests/dsp\"],\"size\": 6868,\"inputs\": 0,\"outputs\": 2,\"meta\": [ { \"compile_options\": \"-a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0\" },{ \"effect.lib/author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"effect.lib/copyright\": \"Julius O. Smith III\" },{ \"effect.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"effect.lib/exciter_author\": \"Priyanka Shekar (pshekar@ccrma.stanford.edu)\" },{ \"effect.lib/exciter_copyright\": \"Copyright (c) 2013 Priyanka Shekar\" },{ \"effect.lib/exciter_license\": \"MIT License (MIT)\" },{ \"effect.lib/exciter_name\": \"Harmonic Exciter\" },{ \"effect.lib/exciter_version\": \"1.0\" },{ \"effect.lib/license\": \"STK-4.3\" },{ \"effect.lib/name\": \"Faust Audio Effect Library\" },{ \"effect.lib/version\": \"1.33\" },{ \"filename\": \"cubic_distortion.dsp\" },{ \"filter.lib/author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"filter.lib/copyright\": \"Julius O. Smith III\" },{ \"filter.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"filter.lib/license\": \"STK-4.3\" },{ \"filter.lib/name\": \"Faust Filter Library\" },{ \"filter.lib/reference\": \"https://ccrma.stanford.edu/~jos/filters/\" },{ \"filter.lib/version\": \"1.29\" },{ \"math.lib/author\": \"GRAME\" },{ \"math.lib/copyright\": \"GRAME\" },{ \"math.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"math.lib/license\": \"LGPL with exception\" },{ \"math.lib/name\": \"Math Library\" },{ \"math.lib/version\": \"1.0\" },{ \"music.lib/author\": \"GRAME\" },{ \"music.lib/copyright\": \"GRAME\" },{ \"music.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"music.lib/license\": \"LGPL with exception\" },{ \"music.lib/name\": \"Music Library\" },{ \"music.lib/version\": \"1.0\" },{ \"name\": \"cubic_distortion\" },{ \"oscillator.lib/author\": \"Julius O. Smith (jos at ccrma.stanford.edu)\" },{ \"oscillator.lib/copyright\": \"Julius O. Smith III\" },{ \"oscillator.lib/deprecated\": \"This library is deprecated and is not maintained anymore. It will be removed in August 2017.\" },{ \"oscillator.lib/license\": \"STK-4.3\" },{ \"oscillator.lib/name\": \"Faust Oscillator Library\" },{ \"oscillator.lib/version\": \"1.11\" }],\"ui\": [ {\"type\": \"vgroup\",\"label\": \"cubic_distortion\",\"items\": [ {\"type\": \"vgroup\",\"label\": \"0x00\",\"meta\": [{ \"1\": \"\" }],\"items\": [ {\"type\": \"vgroup\",\"label\": \"SINE WAVE OSCILLATOR oscrs\",\"meta\": [{ \"0\": \"\" },{ \"tooltip\": \"Sine oscillator based on 2D vector rotation\" }],\"items\": [ {\"type\": \"hslider\",\"label\": \"Amplitude\",\"varname\": \"fHslider3\",\"shortname\": \"Amplitude\",\"address\": \"/cubic_distortion/0x00/SINE_WAVE_OSCILLATOR_oscrs/Amplitude\",\"meta\": [{ \"1\": \"\" },{ \"tooltip\": \"Sawtooth waveform amplitude\" },{ \"unit\": \"dB\" }],\"init\": -20,\"min\": -120,\"max\": 10,\"step\": 0.1},{\"type\": \"hslider\",\"label\": \"Frequency\",\"varname\": \"fHslider5\",\"shortname\": \"Frequency\",\"address\": \"/cubic_distortion/0x00/SINE_WAVE_OSCILLATOR_oscrs/Frequency\",\"meta\": [{ \"2\": \"\" },{ \"tooltip\": \"Sine wave frequency as a Piano Key (PK) number (A440 = 49 PK)\" },{ \"unit\": \"PK\" }],\"init\": 49,\"min\": 1,\"max\": 88,\"step\": 0.01},{\"type\": \"hslider\",\"label\": \"Portamento\",\"varname\": \"fHslider4\",\"shortname\": \"Portamento\",\"address\": \"/cubic_distortion/0x00/SINE_WAVE_OSCILLATOR_oscrs/Portamento\",\"meta\": [{ \"3\": \"\" },{ \"scale\": \"log\" },{ \"tooltip\": \"Portamento (frequency-glide) time-constant in seconds\" },{ \"unit\": \"sec\" }],\"init\": 0.1,\"min\": 0.001,\"max\": 10,\"step\": 0.001}]}]},{\"type\": \"vgroup\",\"label\": \"0x00\",\"meta\": [{ \"2\": \"\" }],\"items\": [ {\"type\": \"vgroup\",\"label\": \"CUBIC NONLINEARITY cubicnl\",\"meta\": [{ \"tooltip\": \"Reference:          https://ccrma.stanford.edu/~jos/pasp/Cubic_Soft_Clipper.html\" }],\"items\": [ {\"type\": \"checkbox\",\"label\": \"Bypass\",\"varname\": \"fCheckbox0\",\"shortname\": \"Bypass\",\"address\": \"/cubic_distortion/0x00/CUBIC_NONLINEARITY_cubicnl/Bypass\",\"meta\": [{ \"0\": \"\" },{ \"tooltip\": \"When this is checked, the nonlinearity has no effect\" }]},{\"type\": \"hslider\",\"label\": \"Drive\",\"varname\": \"fHslider6\",\"shortname\": \"Drive\",\"address\": \"/cubic_distortion/0x00/CUBIC_NONLINEARITY_cubicnl/Drive\",\"meta\": [{ \"1\": \"\" },{ \"tooltip\": \"Amount of distortion\" }],\"init\": 0,\"min\": 0,\"max\": 1,\"step\": 0.01},{\"type\": \"hslider\",\"label\": \"Offset\",\"varname\": \"fHslider2\",\"shortname\": \"Offset\",\"address\": \"/cubic_distortion/0x00/CUBIC_NONLINEARITY_cubicnl/Offset\",\"meta\": [{ \"2\": \"\" },{ \"tooltip\": \"Brings in even harmonics\" }],\"init\": 0,\"min\": 0,\"max\": 1,\"step\": 0.01}]}]},{\"type\": \"vgroup\",\"label\": \"0x00\",\"meta\": [{ \"3\": \"\" }],\"items\": [ {\"type\": \"hgroup\",\"label\": \"CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning LP, 9 octaves below 16000 Hz, HP\",\"meta\": [{ \"0\": \"\" },{ \"tooltip\": \"See Faust\'s filter.lib for documentation and references\" }],\"items\": [ {\"type\": \"vbargraph\",\"label\": \"vbargraph0\",\"varname\": \"fVbargraph14\",\"shortname\": \"vbargraph0\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph0\",\"meta\": [{ \"0\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph1\",\"varname\": \"fVbargraph13\",\"shortname\": \"vbargraph1\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph1\",\"meta\": [{ \"1\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph2\",\"varname\": \"fVbargraph12\",\"shortname\": \"vbargraph2\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph2\",\"meta\": [{ \"2\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph3\",\"varname\": \"fVbargraph11\",\"shortname\": \"vbargraph3\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph3\",\"meta\": [{ \"3\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph4\",\"varname\": \"fVbargraph10\",\"shortname\": \"vbargraph4\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph4\",\"meta\": [{ \"4\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph5\",\"varname\": \"fVbargraph9\",\"shortname\": \"vbargraph5\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph5\",\"meta\": [{ \"5\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph6\",\"varname\": \"fVbargraph8\",\"shortname\": \"vbargraph6\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph6\",\"meta\": [{ \"6\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph7\",\"varname\": \"fVbargraph7\",\"shortname\": \"vbargraph7\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph7\",\"meta\": [{ \"7\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph8\",\"varname\": \"fVbargraph6\",\"shortname\": \"vbargraph8\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph8\",\"meta\": [{ \"8\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph9\",\"varname\": \"fVbargraph5\",\"shortname\": \"vbargraph9\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph9\",\"meta\": [{ \"9\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph10\",\"varname\": \"fVbargraph4\",\"shortname\": \"vbargraph10\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph10\",\"meta\": [{ \"10\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph11\",\"varname\": \"fVbargraph3\",\"shortname\": \"vbargraph11\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph11\",\"meta\": [{ \"11\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph12\",\"varname\": \"fVbargraph2\",\"shortname\": \"vbargraph12\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph12\",\"meta\": [{ \"12\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph13\",\"varname\": \"fVbargraph1\",\"shortname\": \"vbargraph13\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph13\",\"meta\": [{ \"13\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10},{\"type\": \"vbargraph\",\"label\": \"vbargraph14\",\"varname\": \"fVbargraph0\",\"shortname\": \"vbargraph14\",\"address\": \"/cubic_distortion/0x00/CONSTANT-Q_SPECTRUM_ANALYZER__6E___15_bands_spanning_LP__9_octaves_below_16000_Hz__HP/vbargraph14\",\"meta\": [{ \"14\": \"\" },{ \"tooltip\": \"Spectral Band Level in dB\" },{ \"unit\": \"dB\" }],\"min\": -50,\"max\": 10}]},{\"type\": \"hgroup\",\"label\": \"SPECTRUM ANALYZER CONTROLS\",\"meta\": [{ \"1\": \"\" }],\"items\": [ {\"type\": \"hslider\",\"label\": \"Level Averaging Time\",\"varname\": \"fHslider1\",\"shortname\": \"Level_Averaging_Time\",\"address\": \"/cubic_distortion/0x00/SPECTRUM_ANALYZER_CONTROLS/Level_Averaging_Time\",\"meta\": [{ \"0\": \"\" },{ \"scale\": \"log\" },{ \"tooltip\": \"band-level averaging time in milliseconds\" },{ \"unit\": \"ms\" }],\"init\": 100,\"min\": 1,\"max\": 10000,\"step\": 1},{\"type\": \"hslider\",\"label\": \"Level dB Offset\",\"varname\": \"fHslider0\",\"shortname\": \"Level_dB_Offset\",\"address\": \"/cubic_distortion/0x00/SPECTRUM_ANALYZER_CONTROLS/Level_dB_Offset\",\"meta\": [{ \"1\": \"\" },{ \"tooltip\": \"Level offset in decibels\" },{ \"unit\": \"dB\" }],\"init\": 50,\"min\": 0,\"max\": 100,\"step\": 1}]}]}]}]}"

    @always_inline
    def metadata(read dsp, mut meta: Some[FaustMeta]) -> None:
        meta.declare("compile_options", "-a inspect.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0")
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
        ui.declare(dsp.hslider3, "1", "")
        ui.declare(dsp.hslider3, "tooltip", "Sawtooth waveform amplitude")
        ui.declare(dsp.hslider3, "unit", "dB")
        ui.add_horizontal_slider("Amplitude", dsp.hslider3, FaustFloat(-20.0), FaustFloat(-120.0), FaustFloat(10.0), FaustFloat(0.1))
        ui.declare(dsp.hslider5, "2", "")
        ui.declare(dsp.hslider5, "tooltip", "Sine wave frequency as a Piano Key (PK) number (A440 = 49 PK)")
        ui.declare(dsp.hslider5, "unit", "PK")
        ui.add_horizontal_slider("Frequency", dsp.hslider5, FaustFloat(49.0), FaustFloat(1.0), FaustFloat(88.0), FaustFloat(0.01))
        ui.declare(dsp.hslider4, "3", "")
        ui.declare(dsp.hslider4, "scale", "log")
        ui.declare(dsp.hslider4, "tooltip", "Portamento (frequency-glide) time-constant in seconds")
        ui.declare(dsp.hslider4, "unit", "sec")
        ui.add_horizontal_slider("Portamento", dsp.hslider4, FaustFloat(0.1), FaustFloat(0.001), FaustFloat(10.0), FaustFloat(0.001))
        ui.close_box()
        ui.close_box()
        ui.declare(dsp.null_val, "2", "")
        ui.open_vertical_box("0x00")
        ui.declare(dsp.null_val, "tooltip", "Reference:          https://ccrma.stanford.edu/~jos/pasp/Cubic_Soft_Clipper.html")
        ui.open_vertical_box("CUBIC NONLINEARITY cubicnl")
        ui.declare(dsp.checkbox0, "0", "")
        ui.declare(dsp.checkbox0, "tooltip", "When this is checked, the nonlinearity has no effect")
        ui.add_check_button("Bypass", dsp.checkbox0)
        ui.declare(dsp.hslider6, "1", "")
        ui.declare(dsp.hslider6, "tooltip", "Amount of distortion")
        ui.add_horizontal_slider("Drive", dsp.hslider6, FaustFloat(0.0), FaustFloat(0.0), FaustFloat(1.0), FaustFloat(0.01))
        ui.declare(dsp.hslider2, "2", "")
        ui.declare(dsp.hslider2, "tooltip", "Brings in even harmonics")
        ui.add_horizontal_slider("Offset", dsp.hslider2, FaustFloat(0.0), FaustFloat(0.0), FaustFloat(1.0), FaustFloat(0.01))
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
        ui.declare(dsp.hslider1, "0", "")
        ui.declare(dsp.hslider1, "scale", "log")
        ui.declare(dsp.hslider1, "tooltip", "band-level averaging time in milliseconds")
        ui.declare(dsp.hslider1, "unit", "ms")
        ui.add_horizontal_slider("Level Averaging Time", dsp.hslider1, FaustFloat(100.0), FaustFloat(1.0), FaustFloat(10000.0), FaustFloat(1.0))
        ui.declare(dsp.hslider0, "1", "")
        ui.declare(dsp.hslider0, "tooltip", "Level offset in decibels")
        ui.declare(dsp.hslider0, "unit", "dB")
        ui.add_horizontal_slider("Level dB Offset", dsp.hslider0, FaustFloat(50.0), FaustFloat(0.0), FaustFloat(100.0), FaustFloat(1.0))
        ui.close_box()
        ui.close_box()
        ui.close_box()

    @always_inline
    def compute(
        mut dsp, var count: S32, var inputs: ReadStreams, var outputs: MutaStreams
    ) -> None:
        var output0 = outputs[S32(0)]
        var output1 = outputs[S32(1)]
        var slow0 = F64(dsp.hslider0)
        var slow1 = F64(dsp.hslider1)
        var slow2 = exp(-((dsp.const1) / (slow1))) if S32(((0.001) * (slow1)) > (0.0)) else 0.0
        var i_slow3 = S32(F64(dsp.checkbox0))
        var slow4 = (0.0010000000000000009) * (F64(dsp.hslider2))
        var slow5 = (0.0010000000000000009) * (pow(1e+01, (0.05) * (F64(dsp.hslider3))))
        var slow6 = F64(dsp.hslider4)
        var slow7 = exp(-((dsp.const15) / (slow6))) if S32((slow6) > (0.0)) else 0.0
        var slow8 = ((4.4e+02) * (pow(2.0, (0.08333333333333333) * ((F64(dsp.hslider5)) + (-49.0))))) * ((1.0) - (slow7))
        var slow9 = (0.0010000000000000009) * (F64(dsp.hslider6))
        var slow10 = (1.0) - (slow2)
        for var i0 in range(S32(0), count):
            dsp.i_vec0[S32(0)] = S32(1)
            dsp.rec5[S32(0)] = (slow4) + ((0.999) * (dsp.rec5[S32(1)]))
            dsp.rec6[S32(0)] = (slow5) + ((0.999) * (dsp.rec6[S32(1)]))
            dsp.rec9[S32(0)] = ((dsp.rec9[S32(1)]) * (slow7)) + (slow8)
            var temp0 = (dsp.const14) * (dsp.rec9[S32(0)])
            var temp1 = sin(temp0)
            var temp2 = cos(temp0)
            dsp.rec7[S32(0)] = ((dsp.rec8[S32(1)]) * (temp1)) + ((dsp.rec7[S32(1)]) * (temp2))
            dsp.rec8[S32(0)] = ((F64((S32(1)) - (dsp.i_vec0[S32(1)]))) + ((dsp.rec8[S32(1)]) * (temp2))) - ((temp1) * (dsp.rec7[S32(1)]))
            var temp3 = (dsp.rec6[S32(0)]) * (dsp.rec7[S32(0)])
            dsp.rec10[S32(0)] = (slow9) + ((0.999) * (dsp.rec10[S32(1)]))
            var temp4 = max(-1.0, min(1.0, (dsp.rec5[S32(0)]) + ((0.0 if i_slow3 else temp3) * (pow(1e+01, (2.0) * (dsp.rec10[S32(0)]))))))
            var temp5 = (temp4) * ((1.0) - ((0.3333333333333333) * (pow_unrolled[2](temp4))))
            dsp.vec1[S32(0)] = temp5
            dsp.rec4[S32(0)] = (((0.995) * (dsp.rec4[S32(1)])) + (temp5)) - (dsp.vec1[S32(1)])
            var temp6 = temp3 if i_slow3 else dsp.rec4[S32(0)]
            dsp.rec3[S32(0)] = (temp6) - ((dsp.const11) * (((dsp.const16) * (dsp.rec3[S32(2)])) + ((dsp.const18) * (dsp.rec3[S32(1)]))))
            dsp.rec2[S32(0)] = ((dsp.const11) * ((((dsp.const13) * (dsp.rec3[S32(0)])) + ((dsp.const19) * (dsp.rec3[S32(1)]))) + ((dsp.const13) * (dsp.rec3[S32(2)])))) - ((dsp.const8) * (((dsp.const20) * (dsp.rec2[S32(2)])) + ((dsp.const21) * (dsp.rec2[S32(1)]))))
            dsp.rec1[S32(0)] = ((dsp.const8) * ((((dsp.const10) * (dsp.rec2[S32(0)])) + ((dsp.const22) * (dsp.rec2[S32(1)]))) + ((dsp.const10) * (dsp.rec2[S32(2)])))) - ((dsp.const4) * (((dsp.const23) * (dsp.rec1[S32(2)])) + ((dsp.const24) * (dsp.rec1[S32(1)]))))
            dsp.rec0[S32(0)] = ((dsp.rec0[S32(1)]) * (slow2)) + ((abs((dsp.const4) * ((((dsp.const7) * (dsp.rec1[S32(0)])) + ((dsp.const25) * (dsp.rec1[S32(1)]))) + ((dsp.const7) * (dsp.rec1[S32(2)]))))) * (slow10))
            dsp.vbargraph0 = FaustFloat((slow0) + ((2e+01) * (log10(dsp.rec0[S32(0)]))))
            dsp.rec17[S32(0)] = (temp6) - ((dsp.const42) * (((dsp.const45) * (dsp.rec17[S32(2)])) + ((dsp.const46) * (dsp.rec17[S32(1)]))))
            dsp.rec16[S32(0)] = ((dsp.const42) * ((((dsp.const44) * (dsp.rec17[S32(0)])) + ((dsp.const47) * (dsp.rec17[S32(1)]))) + ((dsp.const44) * (dsp.rec17[S32(2)])))) - ((dsp.const40) * (((dsp.const48) * (dsp.rec16[S32(2)])) + ((dsp.const49) * (dsp.rec16[S32(1)]))))
            dsp.rec15[S32(0)] = ((dsp.const40) * ((((dsp.const41) * (dsp.rec16[S32(0)])) + ((dsp.const50) * (dsp.rec16[S32(1)]))) + ((dsp.const41) * (dsp.rec16[S32(2)])))) - ((dsp.const38) * (((dsp.const51) * (dsp.rec15[S32(2)])) + ((dsp.const52) * (dsp.rec15[S32(1)]))))
            var temp7 = (dsp.const38) * ((((dsp.const39) * (dsp.rec15[S32(0)])) + ((dsp.const53) * (dsp.rec15[S32(1)]))) + ((dsp.const39) * (dsp.rec15[S32(2)])))
            dsp.rec14[S32(0)] = (temp7) - ((dsp.const35) * (((dsp.const54) * (dsp.rec14[S32(2)])) + ((dsp.const56) * (dsp.rec14[S32(1)]))))
            dsp.rec13[S32(0)] = ((dsp.const35) * ((((dsp.const37) * (dsp.rec14[S32(0)])) + ((dsp.const57) * (dsp.rec14[S32(1)]))) + ((dsp.const37) * (dsp.rec14[S32(2)])))) - ((dsp.const32) * (((dsp.const58) * (dsp.rec13[S32(2)])) + ((dsp.const59) * (dsp.rec13[S32(1)]))))
            dsp.rec12[S32(0)] = ((dsp.const32) * ((((dsp.const34) * (dsp.rec13[S32(0)])) + ((dsp.const60) * (dsp.rec13[S32(1)]))) + ((dsp.const34) * (dsp.rec13[S32(2)])))) - ((dsp.const28) * (((dsp.const61) * (dsp.rec12[S32(2)])) + ((dsp.const62) * (dsp.rec12[S32(1)]))))
            dsp.rec11[S32(0)] = ((slow2) * (dsp.rec11[S32(1)])) + ((slow10) * (abs((dsp.const28) * ((((dsp.const31) * (dsp.rec12[S32(0)])) + ((dsp.const63) * (dsp.rec12[S32(1)]))) + ((dsp.const31) * (dsp.rec12[S32(2)]))))))
            dsp.vbargraph1 = FaustFloat((slow0) + ((2e+01) * (log10(dsp.rec11[S32(0)]))))
            dsp.rec24[S32(0)] = (temp7) - ((dsp.const80) * (((dsp.const83) * (dsp.rec24[S32(2)])) + ((dsp.const84) * (dsp.rec24[S32(1)]))))
            dsp.rec23[S32(0)] = ((dsp.const80) * ((((dsp.const82) * (dsp.rec24[S32(0)])) + ((dsp.const85) * (dsp.rec24[S32(1)]))) + ((dsp.const82) * (dsp.rec24[S32(2)])))) - ((dsp.const78) * (((dsp.const86) * (dsp.rec23[S32(2)])) + ((dsp.const87) * (dsp.rec23[S32(1)]))))
            dsp.rec22[S32(0)] = ((dsp.const78) * ((((dsp.const79) * (dsp.rec23[S32(0)])) + ((dsp.const88) * (dsp.rec23[S32(1)]))) + ((dsp.const79) * (dsp.rec23[S32(2)])))) - ((dsp.const76) * (((dsp.const89) * (dsp.rec22[S32(2)])) + ((dsp.const90) * (dsp.rec22[S32(1)]))))
            var temp8 = (dsp.const76) * ((((dsp.const77) * (dsp.rec22[S32(0)])) + ((dsp.const91) * (dsp.rec22[S32(1)]))) + ((dsp.const77) * (dsp.rec22[S32(2)])))
            dsp.rec21[S32(0)] = (temp8) - ((dsp.const73) * (((dsp.const92) * (dsp.rec21[S32(2)])) + ((dsp.const94) * (dsp.rec21[S32(1)]))))
            dsp.rec20[S32(0)] = ((dsp.const73) * ((((dsp.const75) * (dsp.rec21[S32(0)])) + ((dsp.const95) * (dsp.rec21[S32(1)]))) + ((dsp.const75) * (dsp.rec21[S32(2)])))) - ((dsp.const70) * (((dsp.const96) * (dsp.rec20[S32(2)])) + ((dsp.const97) * (dsp.rec20[S32(1)]))))
            dsp.rec19[S32(0)] = ((dsp.const70) * ((((dsp.const72) * (dsp.rec20[S32(0)])) + ((dsp.const98) * (dsp.rec20[S32(1)]))) + ((dsp.const72) * (dsp.rec20[S32(2)])))) - ((dsp.const66) * (((dsp.const99) * (dsp.rec19[S32(2)])) + ((dsp.const100) * (dsp.rec19[S32(1)]))))
            dsp.rec18[S32(0)] = ((slow2) * (dsp.rec18[S32(1)])) + ((slow10) * (abs((dsp.const66) * ((((dsp.const69) * (dsp.rec19[S32(0)])) + ((dsp.const101) * (dsp.rec19[S32(1)]))) + ((dsp.const69) * (dsp.rec19[S32(2)]))))))
            dsp.vbargraph2 = FaustFloat((slow0) + ((2e+01) * (log10(dsp.rec18[S32(0)]))))
            dsp.rec31[S32(0)] = (temp8) - ((dsp.const118) * (((dsp.const121) * (dsp.rec31[S32(2)])) + ((dsp.const122) * (dsp.rec31[S32(1)]))))
            dsp.rec30[S32(0)] = ((dsp.const118) * ((((dsp.const120) * (dsp.rec31[S32(0)])) + ((dsp.const123) * (dsp.rec31[S32(1)]))) + ((dsp.const120) * (dsp.rec31[S32(2)])))) - ((dsp.const116) * (((dsp.const124) * (dsp.rec30[S32(2)])) + ((dsp.const125) * (dsp.rec30[S32(1)]))))
            dsp.rec29[S32(0)] = ((dsp.const116) * ((((dsp.const117) * (dsp.rec30[S32(0)])) + ((dsp.const126) * (dsp.rec30[S32(1)]))) + ((dsp.const117) * (dsp.rec30[S32(2)])))) - ((dsp.const114) * (((dsp.const127) * (dsp.rec29[S32(2)])) + ((dsp.const128) * (dsp.rec29[S32(1)]))))
            var temp9 = (dsp.const114) * ((((dsp.const115) * (dsp.rec29[S32(0)])) + ((dsp.const129) * (dsp.rec29[S32(1)]))) + ((dsp.const115) * (dsp.rec29[S32(2)])))
            dsp.rec28[S32(0)] = (temp9) - ((dsp.const111) * (((dsp.const130) * (dsp.rec28[S32(2)])) + ((dsp.const132) * (dsp.rec28[S32(1)]))))
            dsp.rec27[S32(0)] = ((dsp.const111) * ((((dsp.const113) * (dsp.rec28[S32(0)])) + ((dsp.const133) * (dsp.rec28[S32(1)]))) + ((dsp.const113) * (dsp.rec28[S32(2)])))) - ((dsp.const108) * (((dsp.const134) * (dsp.rec27[S32(2)])) + ((dsp.const135) * (dsp.rec27[S32(1)]))))
            dsp.rec26[S32(0)] = ((dsp.const108) * ((((dsp.const110) * (dsp.rec27[S32(0)])) + ((dsp.const136) * (dsp.rec27[S32(1)]))) + ((dsp.const110) * (dsp.rec27[S32(2)])))) - ((dsp.const104) * (((dsp.const137) * (dsp.rec26[S32(2)])) + ((dsp.const138) * (dsp.rec26[S32(1)]))))
            dsp.rec25[S32(0)] = ((slow2) * (dsp.rec25[S32(1)])) + ((slow10) * (abs((dsp.const104) * ((((dsp.const107) * (dsp.rec26[S32(0)])) + ((dsp.const139) * (dsp.rec26[S32(1)]))) + ((dsp.const107) * (dsp.rec26[S32(2)]))))))
            dsp.vbargraph3 = FaustFloat((slow0) + ((2e+01) * (log10(dsp.rec25[S32(0)]))))
            dsp.rec38[S32(0)] = (temp9) - ((dsp.const156) * (((dsp.const159) * (dsp.rec38[S32(2)])) + ((dsp.const160) * (dsp.rec38[S32(1)]))))
            dsp.rec37[S32(0)] = ((dsp.const156) * ((((dsp.const158) * (dsp.rec38[S32(0)])) + ((dsp.const161) * (dsp.rec38[S32(1)]))) + ((dsp.const158) * (dsp.rec38[S32(2)])))) - ((dsp.const154) * (((dsp.const162) * (dsp.rec37[S32(2)])) + ((dsp.const163) * (dsp.rec37[S32(1)]))))
            dsp.rec36[S32(0)] = ((dsp.const154) * ((((dsp.const155) * (dsp.rec37[S32(0)])) + ((dsp.const164) * (dsp.rec37[S32(1)]))) + ((dsp.const155) * (dsp.rec37[S32(2)])))) - ((dsp.const152) * (((dsp.const165) * (dsp.rec36[S32(2)])) + ((dsp.const166) * (dsp.rec36[S32(1)]))))
            var temp10 = (dsp.const152) * ((((dsp.const153) * (dsp.rec36[S32(0)])) + ((dsp.const167) * (dsp.rec36[S32(1)]))) + ((dsp.const153) * (dsp.rec36[S32(2)])))
            dsp.rec35[S32(0)] = (temp10) - ((dsp.const149) * (((dsp.const168) * (dsp.rec35[S32(2)])) + ((dsp.const170) * (dsp.rec35[S32(1)]))))
            dsp.rec34[S32(0)] = ((dsp.const149) * ((((dsp.const151) * (dsp.rec35[S32(0)])) + ((dsp.const171) * (dsp.rec35[S32(1)]))) + ((dsp.const151) * (dsp.rec35[S32(2)])))) - ((dsp.const146) * (((dsp.const172) * (dsp.rec34[S32(2)])) + ((dsp.const173) * (dsp.rec34[S32(1)]))))
            dsp.rec33[S32(0)] = ((dsp.const146) * ((((dsp.const148) * (dsp.rec34[S32(0)])) + ((dsp.const174) * (dsp.rec34[S32(1)]))) + ((dsp.const148) * (dsp.rec34[S32(2)])))) - ((dsp.const142) * (((dsp.const175) * (dsp.rec33[S32(2)])) + ((dsp.const176) * (dsp.rec33[S32(1)]))))
            dsp.rec32[S32(0)] = ((slow2) * (dsp.rec32[S32(1)])) + ((slow10) * (abs((dsp.const142) * ((((dsp.const145) * (dsp.rec33[S32(0)])) + ((dsp.const177) * (dsp.rec33[S32(1)]))) + ((dsp.const145) * (dsp.rec33[S32(2)]))))))
            dsp.vbargraph4 = FaustFloat((slow0) + ((2e+01) * (log10(dsp.rec32[S32(0)]))))
            dsp.rec45[S32(0)] = (temp10) - ((dsp.const194) * (((dsp.const197) * (dsp.rec45[S32(2)])) + ((dsp.const198) * (dsp.rec45[S32(1)]))))
            dsp.rec44[S32(0)] = ((dsp.const194) * ((((dsp.const196) * (dsp.rec45[S32(0)])) + ((dsp.const199) * (dsp.rec45[S32(1)]))) + ((dsp.const196) * (dsp.rec45[S32(2)])))) - ((dsp.const192) * (((dsp.const200) * (dsp.rec44[S32(2)])) + ((dsp.const201) * (dsp.rec44[S32(1)]))))
            dsp.rec43[S32(0)] = ((dsp.const192) * ((((dsp.const193) * (dsp.rec44[S32(0)])) + ((dsp.const202) * (dsp.rec44[S32(1)]))) + ((dsp.const193) * (dsp.rec44[S32(2)])))) - ((dsp.const190) * (((dsp.const203) * (dsp.rec43[S32(2)])) + ((dsp.const204) * (dsp.rec43[S32(1)]))))
            var temp11 = (dsp.const190) * ((((dsp.const191) * (dsp.rec43[S32(0)])) + ((dsp.const205) * (dsp.rec43[S32(1)]))) + ((dsp.const191) * (dsp.rec43[S32(2)])))
            dsp.rec42[S32(0)] = (temp11) - ((dsp.const187) * (((dsp.const206) * (dsp.rec42[S32(2)])) + ((dsp.const208) * (dsp.rec42[S32(1)]))))
            dsp.rec41[S32(0)] = ((dsp.const187) * ((((dsp.const189) * (dsp.rec42[S32(0)])) + ((dsp.const209) * (dsp.rec42[S32(1)]))) + ((dsp.const189) * (dsp.rec42[S32(2)])))) - ((dsp.const184) * (((dsp.const210) * (dsp.rec41[S32(2)])) + ((dsp.const211) * (dsp.rec41[S32(1)]))))
            dsp.rec40[S32(0)] = ((dsp.const184) * ((((dsp.const186) * (dsp.rec41[S32(0)])) + ((dsp.const212) * (dsp.rec41[S32(1)]))) + ((dsp.const186) * (dsp.rec41[S32(2)])))) - ((dsp.const180) * (((dsp.const213) * (dsp.rec40[S32(2)])) + ((dsp.const214) * (dsp.rec40[S32(1)]))))
            dsp.rec39[S32(0)] = ((slow2) * (dsp.rec39[S32(1)])) + ((slow10) * (abs((dsp.const180) * ((((dsp.const183) * (dsp.rec40[S32(0)])) + ((dsp.const215) * (dsp.rec40[S32(1)]))) + ((dsp.const183) * (dsp.rec40[S32(2)]))))))
            dsp.vbargraph5 = FaustFloat((slow0) + ((2e+01) * (log10(dsp.rec39[S32(0)]))))
            dsp.rec52[S32(0)] = (temp11) - ((dsp.const232) * (((dsp.const235) * (dsp.rec52[S32(2)])) + ((dsp.const236) * (dsp.rec52[S32(1)]))))
            dsp.rec51[S32(0)] = ((dsp.const232) * ((((dsp.const234) * (dsp.rec52[S32(0)])) + ((dsp.const237) * (dsp.rec52[S32(1)]))) + ((dsp.const234) * (dsp.rec52[S32(2)])))) - ((dsp.const230) * (((dsp.const238) * (dsp.rec51[S32(2)])) + ((dsp.const239) * (dsp.rec51[S32(1)]))))
            dsp.rec50[S32(0)] = ((dsp.const230) * ((((dsp.const231) * (dsp.rec51[S32(0)])) + ((dsp.const240) * (dsp.rec51[S32(1)]))) + ((dsp.const231) * (dsp.rec51[S32(2)])))) - ((dsp.const228) * (((dsp.const241) * (dsp.rec50[S32(2)])) + ((dsp.const242) * (dsp.rec50[S32(1)]))))
            var temp12 = (dsp.const228) * ((((dsp.const229) * (dsp.rec50[S32(0)])) + ((dsp.const243) * (dsp.rec50[S32(1)]))) + ((dsp.const229) * (dsp.rec50[S32(2)])))
            dsp.rec49[S32(0)] = (temp12) - ((dsp.const225) * (((dsp.const244) * (dsp.rec49[S32(2)])) + ((dsp.const246) * (dsp.rec49[S32(1)]))))
            dsp.rec48[S32(0)] = ((dsp.const225) * ((((dsp.const227) * (dsp.rec49[S32(0)])) + ((dsp.const247) * (dsp.rec49[S32(1)]))) + ((dsp.const227) * (dsp.rec49[S32(2)])))) - ((dsp.const222) * (((dsp.const248) * (dsp.rec48[S32(2)])) + ((dsp.const249) * (dsp.rec48[S32(1)]))))
            dsp.rec47[S32(0)] = ((dsp.const222) * ((((dsp.const224) * (dsp.rec48[S32(0)])) + ((dsp.const250) * (dsp.rec48[S32(1)]))) + ((dsp.const224) * (dsp.rec48[S32(2)])))) - ((dsp.const218) * (((dsp.const251) * (dsp.rec47[S32(2)])) + ((dsp.const252) * (dsp.rec47[S32(1)]))))
            dsp.rec46[S32(0)] = ((slow2) * (dsp.rec46[S32(1)])) + ((slow10) * (abs((dsp.const218) * ((((dsp.const221) * (dsp.rec47[S32(0)])) + ((dsp.const253) * (dsp.rec47[S32(1)]))) + ((dsp.const221) * (dsp.rec47[S32(2)]))))))
            dsp.vbargraph6 = FaustFloat((slow0) + ((2e+01) * (log10(dsp.rec46[S32(0)]))))
            dsp.rec59[S32(0)] = (temp12) - ((dsp.const270) * (((dsp.const273) * (dsp.rec59[S32(2)])) + ((dsp.const274) * (dsp.rec59[S32(1)]))))
            dsp.rec58[S32(0)] = ((dsp.const270) * ((((dsp.const272) * (dsp.rec59[S32(0)])) + ((dsp.const275) * (dsp.rec59[S32(1)]))) + ((dsp.const272) * (dsp.rec59[S32(2)])))) - ((dsp.const268) * (((dsp.const276) * (dsp.rec58[S32(2)])) + ((dsp.const277) * (dsp.rec58[S32(1)]))))
            dsp.rec57[S32(0)] = ((dsp.const268) * ((((dsp.const269) * (dsp.rec58[S32(0)])) + ((dsp.const278) * (dsp.rec58[S32(1)]))) + ((dsp.const269) * (dsp.rec58[S32(2)])))) - ((dsp.const266) * (((dsp.const279) * (dsp.rec57[S32(2)])) + ((dsp.const280) * (dsp.rec57[S32(1)]))))
            var temp13 = (dsp.const266) * ((((dsp.const267) * (dsp.rec57[S32(0)])) + ((dsp.const281) * (dsp.rec57[S32(1)]))) + ((dsp.const267) * (dsp.rec57[S32(2)])))
            dsp.rec56[S32(0)] = (temp13) - ((dsp.const263) * (((dsp.const282) * (dsp.rec56[S32(2)])) + ((dsp.const284) * (dsp.rec56[S32(1)]))))
            dsp.rec55[S32(0)] = ((dsp.const263) * ((((dsp.const265) * (dsp.rec56[S32(0)])) + ((dsp.const285) * (dsp.rec56[S32(1)]))) + ((dsp.const265) * (dsp.rec56[S32(2)])))) - ((dsp.const260) * (((dsp.const286) * (dsp.rec55[S32(2)])) + ((dsp.const287) * (dsp.rec55[S32(1)]))))
            dsp.rec54[S32(0)] = ((dsp.const260) * ((((dsp.const262) * (dsp.rec55[S32(0)])) + ((dsp.const288) * (dsp.rec55[S32(1)]))) + ((dsp.const262) * (dsp.rec55[S32(2)])))) - ((dsp.const256) * (((dsp.const289) * (dsp.rec54[S32(2)])) + ((dsp.const290) * (dsp.rec54[S32(1)]))))
            dsp.rec53[S32(0)] = ((slow2) * (dsp.rec53[S32(1)])) + ((slow10) * (abs((dsp.const256) * ((((dsp.const259) * (dsp.rec54[S32(0)])) + ((dsp.const291) * (dsp.rec54[S32(1)]))) + ((dsp.const259) * (dsp.rec54[S32(2)]))))))
            dsp.vbargraph7 = FaustFloat((slow0) + ((2e+01) * (log10(dsp.rec53[S32(0)]))))
            dsp.rec66[S32(0)] = (temp13) - ((dsp.const308) * (((dsp.const311) * (dsp.rec66[S32(2)])) + ((dsp.const312) * (dsp.rec66[S32(1)]))))
            dsp.rec65[S32(0)] = ((dsp.const308) * ((((dsp.const310) * (dsp.rec66[S32(0)])) + ((dsp.const313) * (dsp.rec66[S32(1)]))) + ((dsp.const310) * (dsp.rec66[S32(2)])))) - ((dsp.const306) * (((dsp.const314) * (dsp.rec65[S32(2)])) + ((dsp.const315) * (dsp.rec65[S32(1)]))))
            dsp.rec64[S32(0)] = ((dsp.const306) * ((((dsp.const307) * (dsp.rec65[S32(0)])) + ((dsp.const316) * (dsp.rec65[S32(1)]))) + ((dsp.const307) * (dsp.rec65[S32(2)])))) - ((dsp.const304) * (((dsp.const317) * (dsp.rec64[S32(2)])) + ((dsp.const318) * (dsp.rec64[S32(1)]))))
            var temp14 = (dsp.const304) * ((((dsp.const305) * (dsp.rec64[S32(0)])) + ((dsp.const319) * (dsp.rec64[S32(1)]))) + ((dsp.const305) * (dsp.rec64[S32(2)])))
            dsp.rec63[S32(0)] = (temp14) - ((dsp.const301) * (((dsp.const320) * (dsp.rec63[S32(2)])) + ((dsp.const322) * (dsp.rec63[S32(1)]))))
            dsp.rec62[S32(0)] = ((dsp.const301) * ((((dsp.const303) * (dsp.rec63[S32(0)])) + ((dsp.const323) * (dsp.rec63[S32(1)]))) + ((dsp.const303) * (dsp.rec63[S32(2)])))) - ((dsp.const298) * (((dsp.const324) * (dsp.rec62[S32(2)])) + ((dsp.const325) * (dsp.rec62[S32(1)]))))
            dsp.rec61[S32(0)] = ((dsp.const298) * ((((dsp.const300) * (dsp.rec62[S32(0)])) + ((dsp.const326) * (dsp.rec62[S32(1)]))) + ((dsp.const300) * (dsp.rec62[S32(2)])))) - ((dsp.const294) * (((dsp.const327) * (dsp.rec61[S32(2)])) + ((dsp.const328) * (dsp.rec61[S32(1)]))))
            dsp.rec60[S32(0)] = ((slow2) * (dsp.rec60[S32(1)])) + ((slow10) * (abs((dsp.const294) * ((((dsp.const297) * (dsp.rec61[S32(0)])) + ((dsp.const329) * (dsp.rec61[S32(1)]))) + ((dsp.const297) * (dsp.rec61[S32(2)]))))))
            dsp.vbargraph8 = FaustFloat((slow0) + ((2e+01) * (log10(dsp.rec60[S32(0)]))))
            dsp.rec73[S32(0)] = (temp14) - ((dsp.const346) * (((dsp.const349) * (dsp.rec73[S32(2)])) + ((dsp.const350) * (dsp.rec73[S32(1)]))))
            dsp.rec72[S32(0)] = ((dsp.const346) * ((((dsp.const348) * (dsp.rec73[S32(0)])) + ((dsp.const351) * (dsp.rec73[S32(1)]))) + ((dsp.const348) * (dsp.rec73[S32(2)])))) - ((dsp.const344) * (((dsp.const352) * (dsp.rec72[S32(2)])) + ((dsp.const353) * (dsp.rec72[S32(1)]))))
            dsp.rec71[S32(0)] = ((dsp.const344) * ((((dsp.const345) * (dsp.rec72[S32(0)])) + ((dsp.const354) * (dsp.rec72[S32(1)]))) + ((dsp.const345) * (dsp.rec72[S32(2)])))) - ((dsp.const342) * (((dsp.const355) * (dsp.rec71[S32(2)])) + ((dsp.const356) * (dsp.rec71[S32(1)]))))
            var temp15 = (dsp.const342) * ((((dsp.const343) * (dsp.rec71[S32(0)])) + ((dsp.const357) * (dsp.rec71[S32(1)]))) + ((dsp.const343) * (dsp.rec71[S32(2)])))
            dsp.rec70[S32(0)] = (temp15) - ((dsp.const339) * (((dsp.const358) * (dsp.rec70[S32(2)])) + ((dsp.const360) * (dsp.rec70[S32(1)]))))
            dsp.rec69[S32(0)] = ((dsp.const339) * ((((dsp.const341) * (dsp.rec70[S32(0)])) + ((dsp.const361) * (dsp.rec70[S32(1)]))) + ((dsp.const341) * (dsp.rec70[S32(2)])))) - ((dsp.const336) * (((dsp.const362) * (dsp.rec69[S32(2)])) + ((dsp.const363) * (dsp.rec69[S32(1)]))))
            dsp.rec68[S32(0)] = ((dsp.const336) * ((((dsp.const338) * (dsp.rec69[S32(0)])) + ((dsp.const364) * (dsp.rec69[S32(1)]))) + ((dsp.const338) * (dsp.rec69[S32(2)])))) - ((dsp.const332) * (((dsp.const365) * (dsp.rec68[S32(2)])) + ((dsp.const366) * (dsp.rec68[S32(1)]))))
            dsp.rec67[S32(0)] = ((slow2) * (dsp.rec67[S32(1)])) + ((slow10) * (abs((dsp.const332) * ((((dsp.const335) * (dsp.rec68[S32(0)])) + ((dsp.const367) * (dsp.rec68[S32(1)]))) + ((dsp.const335) * (dsp.rec68[S32(2)]))))))
            dsp.vbargraph9 = FaustFloat((slow0) + ((2e+01) * (log10(dsp.rec67[S32(0)]))))
            dsp.rec80[S32(0)] = (temp15) - ((dsp.const384) * (((dsp.const387) * (dsp.rec80[S32(2)])) + ((dsp.const388) * (dsp.rec80[S32(1)]))))
            dsp.rec79[S32(0)] = ((dsp.const384) * ((((dsp.const386) * (dsp.rec80[S32(0)])) + ((dsp.const389) * (dsp.rec80[S32(1)]))) + ((dsp.const386) * (dsp.rec80[S32(2)])))) - ((dsp.const382) * (((dsp.const390) * (dsp.rec79[S32(2)])) + ((dsp.const391) * (dsp.rec79[S32(1)]))))
            dsp.rec78[S32(0)] = ((dsp.const382) * ((((dsp.const383) * (dsp.rec79[S32(0)])) + ((dsp.const392) * (dsp.rec79[S32(1)]))) + ((dsp.const383) * (dsp.rec79[S32(2)])))) - ((dsp.const380) * (((dsp.const393) * (dsp.rec78[S32(2)])) + ((dsp.const394) * (dsp.rec78[S32(1)]))))
            var temp16 = (dsp.const380) * ((((dsp.const381) * (dsp.rec78[S32(0)])) + ((dsp.const395) * (dsp.rec78[S32(1)]))) + ((dsp.const381) * (dsp.rec78[S32(2)])))
            dsp.rec77[S32(0)] = (temp16) - ((dsp.const377) * (((dsp.const396) * (dsp.rec77[S32(2)])) + ((dsp.const398) * (dsp.rec77[S32(1)]))))
            dsp.rec76[S32(0)] = ((dsp.const377) * ((((dsp.const379) * (dsp.rec77[S32(0)])) + ((dsp.const399) * (dsp.rec77[S32(1)]))) + ((dsp.const379) * (dsp.rec77[S32(2)])))) - ((dsp.const374) * (((dsp.const400) * (dsp.rec76[S32(2)])) + ((dsp.const401) * (dsp.rec76[S32(1)]))))
            dsp.rec75[S32(0)] = ((dsp.const374) * ((((dsp.const376) * (dsp.rec76[S32(0)])) + ((dsp.const402) * (dsp.rec76[S32(1)]))) + ((dsp.const376) * (dsp.rec76[S32(2)])))) - ((dsp.const370) * (((dsp.const403) * (dsp.rec75[S32(2)])) + ((dsp.const404) * (dsp.rec75[S32(1)]))))
            dsp.rec74[S32(0)] = ((slow2) * (dsp.rec74[S32(1)])) + ((slow10) * (abs((dsp.const370) * ((((dsp.const373) * (dsp.rec75[S32(0)])) + ((dsp.const405) * (dsp.rec75[S32(1)]))) + ((dsp.const373) * (dsp.rec75[S32(2)]))))))
            dsp.vbargraph10 = FaustFloat((slow0) + ((2e+01) * (log10(dsp.rec74[S32(0)]))))
            dsp.rec87[S32(0)] = (temp16) - ((dsp.const422) * (((dsp.const425) * (dsp.rec87[S32(2)])) + ((dsp.const426) * (dsp.rec87[S32(1)]))))
            dsp.rec86[S32(0)] = ((dsp.const422) * ((((dsp.const424) * (dsp.rec87[S32(0)])) + ((dsp.const427) * (dsp.rec87[S32(1)]))) + ((dsp.const424) * (dsp.rec87[S32(2)])))) - ((dsp.const420) * (((dsp.const428) * (dsp.rec86[S32(2)])) + ((dsp.const429) * (dsp.rec86[S32(1)]))))
            dsp.rec85[S32(0)] = ((dsp.const420) * ((((dsp.const421) * (dsp.rec86[S32(0)])) + ((dsp.const430) * (dsp.rec86[S32(1)]))) + ((dsp.const421) * (dsp.rec86[S32(2)])))) - ((dsp.const418) * (((dsp.const431) * (dsp.rec85[S32(2)])) + ((dsp.const432) * (dsp.rec85[S32(1)]))))
            var temp17 = (dsp.const418) * ((((dsp.const419) * (dsp.rec85[S32(0)])) + ((dsp.const433) * (dsp.rec85[S32(1)]))) + ((dsp.const419) * (dsp.rec85[S32(2)])))
            dsp.rec84[S32(0)] = (temp17) - ((dsp.const415) * (((dsp.const434) * (dsp.rec84[S32(2)])) + ((dsp.const436) * (dsp.rec84[S32(1)]))))
            dsp.rec83[S32(0)] = ((dsp.const415) * ((((dsp.const417) * (dsp.rec84[S32(0)])) + ((dsp.const437) * (dsp.rec84[S32(1)]))) + ((dsp.const417) * (dsp.rec84[S32(2)])))) - ((dsp.const412) * (((dsp.const438) * (dsp.rec83[S32(2)])) + ((dsp.const439) * (dsp.rec83[S32(1)]))))
            dsp.rec82[S32(0)] = ((dsp.const412) * ((((dsp.const414) * (dsp.rec83[S32(0)])) + ((dsp.const440) * (dsp.rec83[S32(1)]))) + ((dsp.const414) * (dsp.rec83[S32(2)])))) - ((dsp.const408) * (((dsp.const441) * (dsp.rec82[S32(2)])) + ((dsp.const442) * (dsp.rec82[S32(1)]))))
            dsp.rec81[S32(0)] = ((slow2) * (dsp.rec81[S32(1)])) + ((slow10) * (abs((dsp.const408) * ((((dsp.const411) * (dsp.rec82[S32(0)])) + ((dsp.const443) * (dsp.rec82[S32(1)]))) + ((dsp.const411) * (dsp.rec82[S32(2)]))))))
            dsp.vbargraph11 = FaustFloat((slow0) + ((2e+01) * (log10(dsp.rec81[S32(0)]))))
            dsp.rec94[S32(0)] = (temp17) - ((dsp.const460) * (((dsp.const463) * (dsp.rec94[S32(2)])) + ((dsp.const464) * (dsp.rec94[S32(1)]))))
            dsp.rec93[S32(0)] = ((dsp.const460) * ((((dsp.const462) * (dsp.rec94[S32(0)])) + ((dsp.const465) * (dsp.rec94[S32(1)]))) + ((dsp.const462) * (dsp.rec94[S32(2)])))) - ((dsp.const458) * (((dsp.const466) * (dsp.rec93[S32(2)])) + ((dsp.const467) * (dsp.rec93[S32(1)]))))
            dsp.rec92[S32(0)] = ((dsp.const458) * ((((dsp.const459) * (dsp.rec93[S32(0)])) + ((dsp.const468) * (dsp.rec93[S32(1)]))) + ((dsp.const459) * (dsp.rec93[S32(2)])))) - ((dsp.const456) * (((dsp.const469) * (dsp.rec92[S32(2)])) + ((dsp.const470) * (dsp.rec92[S32(1)]))))
            var temp18 = (dsp.const456) * ((((dsp.const457) * (dsp.rec92[S32(0)])) + ((dsp.const471) * (dsp.rec92[S32(1)]))) + ((dsp.const457) * (dsp.rec92[S32(2)])))
            dsp.rec91[S32(0)] = (temp18) - ((dsp.const453) * (((dsp.const472) * (dsp.rec91[S32(2)])) + ((dsp.const474) * (dsp.rec91[S32(1)]))))
            dsp.rec90[S32(0)] = ((dsp.const453) * ((((dsp.const455) * (dsp.rec91[S32(0)])) + ((dsp.const475) * (dsp.rec91[S32(1)]))) + ((dsp.const455) * (dsp.rec91[S32(2)])))) - ((dsp.const450) * (((dsp.const476) * (dsp.rec90[S32(2)])) + ((dsp.const477) * (dsp.rec90[S32(1)]))))
            dsp.rec89[S32(0)] = ((dsp.const450) * ((((dsp.const452) * (dsp.rec90[S32(0)])) + ((dsp.const478) * (dsp.rec90[S32(1)]))) + ((dsp.const452) * (dsp.rec90[S32(2)])))) - ((dsp.const446) * (((dsp.const479) * (dsp.rec89[S32(2)])) + ((dsp.const480) * (dsp.rec89[S32(1)]))))
            dsp.rec88[S32(0)] = ((slow2) * (dsp.rec88[S32(1)])) + ((slow10) * (abs((dsp.const446) * ((((dsp.const449) * (dsp.rec89[S32(0)])) + ((dsp.const481) * (dsp.rec89[S32(1)]))) + ((dsp.const449) * (dsp.rec89[S32(2)]))))))
            dsp.vbargraph12 = FaustFloat((slow0) + ((2e+01) * (log10(dsp.rec88[S32(0)]))))
            dsp.rec101[S32(0)] = (temp18) - ((dsp.const498) * (((dsp.const501) * (dsp.rec101[S32(2)])) + ((dsp.const502) * (dsp.rec101[S32(1)]))))
            dsp.rec100[S32(0)] = ((dsp.const498) * ((((dsp.const500) * (dsp.rec101[S32(0)])) + ((dsp.const503) * (dsp.rec101[S32(1)]))) + ((dsp.const500) * (dsp.rec101[S32(2)])))) - ((dsp.const496) * (((dsp.const504) * (dsp.rec100[S32(2)])) + ((dsp.const505) * (dsp.rec100[S32(1)]))))
            dsp.rec99[S32(0)] = ((dsp.const496) * ((((dsp.const497) * (dsp.rec100[S32(0)])) + ((dsp.const506) * (dsp.rec100[S32(1)]))) + ((dsp.const497) * (dsp.rec100[S32(2)])))) - ((dsp.const494) * (((dsp.const507) * (dsp.rec99[S32(2)])) + ((dsp.const508) * (dsp.rec99[S32(1)]))))
            var temp19 = (dsp.const494) * ((((dsp.const495) * (dsp.rec99[S32(0)])) + ((dsp.const509) * (dsp.rec99[S32(1)]))) + ((dsp.const495) * (dsp.rec99[S32(2)])))
            dsp.rec98[S32(0)] = (temp19) - ((dsp.const491) * (((dsp.const510) * (dsp.rec98[S32(2)])) + ((dsp.const512) * (dsp.rec98[S32(1)]))))
            dsp.rec97[S32(0)] = ((dsp.const491) * ((((dsp.const493) * (dsp.rec98[S32(0)])) + ((dsp.const513) * (dsp.rec98[S32(1)]))) + ((dsp.const493) * (dsp.rec98[S32(2)])))) - ((dsp.const488) * (((dsp.const514) * (dsp.rec97[S32(2)])) + ((dsp.const515) * (dsp.rec97[S32(1)]))))
            dsp.rec96[S32(0)] = ((dsp.const488) * ((((dsp.const490) * (dsp.rec97[S32(0)])) + ((dsp.const516) * (dsp.rec97[S32(1)]))) + ((dsp.const490) * (dsp.rec97[S32(2)])))) - ((dsp.const484) * (((dsp.const517) * (dsp.rec96[S32(2)])) + ((dsp.const518) * (dsp.rec96[S32(1)]))))
            dsp.rec95[S32(0)] = ((slow2) * (dsp.rec95[S32(1)])) + ((slow10) * (abs((dsp.const484) * ((((dsp.const487) * (dsp.rec96[S32(0)])) + ((dsp.const519) * (dsp.rec96[S32(1)]))) + ((dsp.const487) * (dsp.rec96[S32(2)]))))))
            dsp.vbargraph13 = FaustFloat((slow0) + ((2e+01) * (log10(dsp.rec95[S32(0)]))))
            dsp.rec105[S32(0)] = (temp19) - ((dsp.const524) * (((dsp.const527) * (dsp.rec105[S32(2)])) + ((dsp.const528) * (dsp.rec105[S32(1)]))))
            dsp.rec104[S32(0)] = ((dsp.const524) * ((((dsp.const526) * (dsp.rec105[S32(0)])) + ((dsp.const529) * (dsp.rec105[S32(1)]))) + ((dsp.const526) * (dsp.rec105[S32(2)])))) - ((dsp.const522) * (((dsp.const530) * (dsp.rec104[S32(2)])) + ((dsp.const531) * (dsp.rec104[S32(1)]))))
            dsp.rec103[S32(0)] = ((dsp.const522) * ((((dsp.const523) * (dsp.rec104[S32(0)])) + ((dsp.const532) * (dsp.rec104[S32(1)]))) + ((dsp.const523) * (dsp.rec104[S32(2)])))) - ((dsp.const520) * (((dsp.const533) * (dsp.rec103[S32(2)])) + ((dsp.const534) * (dsp.rec103[S32(1)]))))
            dsp.rec102[S32(0)] = ((slow2) * (dsp.rec102[S32(1)])) + ((slow10) * (abs((dsp.const520) * ((((dsp.const521) * (dsp.rec103[S32(0)])) + ((dsp.const535) * (dsp.rec103[S32(1)]))) + ((dsp.const521) * (dsp.rec103[S32(2)]))))))
            dsp.vbargraph14 = FaustFloat((slow0) + ((2e+01) * (log10(dsp.rec102[S32(0)]))))
            var temp20 = temp6
            output0[i0] = FaustFloat(temp20)
            output1[i0] = FaustFloat(temp20)
            dsp.i_vec0[S32(1)] = dsp.i_vec0[S32(0)]
            dsp.rec5[S32(1)] = dsp.rec5[S32(0)]
            dsp.rec6[S32(1)] = dsp.rec6[S32(0)]
            dsp.rec9[S32(1)] = dsp.rec9[S32(0)]
            dsp.rec7[S32(1)] = dsp.rec7[S32(0)]
            dsp.rec8[S32(1)] = dsp.rec8[S32(0)]
            dsp.rec10[S32(1)] = dsp.rec10[S32(0)]
            dsp.vec1[S32(1)] = dsp.vec1[S32(0)]
            dsp.rec4[S32(1)] = dsp.rec4[S32(0)]
            dsp.rec3[S32(2)] = dsp.rec3[S32(1)]
            dsp.rec3[S32(1)] = dsp.rec3[S32(0)]
            dsp.rec2[S32(2)] = dsp.rec2[S32(1)]
            dsp.rec2[S32(1)] = dsp.rec2[S32(0)]
            dsp.rec1[S32(2)] = dsp.rec1[S32(1)]
            dsp.rec1[S32(1)] = dsp.rec1[S32(0)]
            dsp.rec0[S32(1)] = dsp.rec0[S32(0)]
            dsp.rec17[S32(2)] = dsp.rec17[S32(1)]
            dsp.rec17[S32(1)] = dsp.rec17[S32(0)]
            dsp.rec16[S32(2)] = dsp.rec16[S32(1)]
            dsp.rec16[S32(1)] = dsp.rec16[S32(0)]
            dsp.rec15[S32(2)] = dsp.rec15[S32(1)]
            dsp.rec15[S32(1)] = dsp.rec15[S32(0)]
            dsp.rec14[S32(2)] = dsp.rec14[S32(1)]
            dsp.rec14[S32(1)] = dsp.rec14[S32(0)]
            dsp.rec13[S32(2)] = dsp.rec13[S32(1)]
            dsp.rec13[S32(1)] = dsp.rec13[S32(0)]
            dsp.rec12[S32(2)] = dsp.rec12[S32(1)]
            dsp.rec12[S32(1)] = dsp.rec12[S32(0)]
            dsp.rec11[S32(1)] = dsp.rec11[S32(0)]
            dsp.rec24[S32(2)] = dsp.rec24[S32(1)]
            dsp.rec24[S32(1)] = dsp.rec24[S32(0)]
            dsp.rec23[S32(2)] = dsp.rec23[S32(1)]
            dsp.rec23[S32(1)] = dsp.rec23[S32(0)]
            dsp.rec22[S32(2)] = dsp.rec22[S32(1)]
            dsp.rec22[S32(1)] = dsp.rec22[S32(0)]
            dsp.rec21[S32(2)] = dsp.rec21[S32(1)]
            dsp.rec21[S32(1)] = dsp.rec21[S32(0)]
            dsp.rec20[S32(2)] = dsp.rec20[S32(1)]
            dsp.rec20[S32(1)] = dsp.rec20[S32(0)]
            dsp.rec19[S32(2)] = dsp.rec19[S32(1)]
            dsp.rec19[S32(1)] = dsp.rec19[S32(0)]
            dsp.rec18[S32(1)] = dsp.rec18[S32(0)]
            dsp.rec31[S32(2)] = dsp.rec31[S32(1)]
            dsp.rec31[S32(1)] = dsp.rec31[S32(0)]
            dsp.rec30[S32(2)] = dsp.rec30[S32(1)]
            dsp.rec30[S32(1)] = dsp.rec30[S32(0)]
            dsp.rec29[S32(2)] = dsp.rec29[S32(1)]
            dsp.rec29[S32(1)] = dsp.rec29[S32(0)]
            dsp.rec28[S32(2)] = dsp.rec28[S32(1)]
            dsp.rec28[S32(1)] = dsp.rec28[S32(0)]
            dsp.rec27[S32(2)] = dsp.rec27[S32(1)]
            dsp.rec27[S32(1)] = dsp.rec27[S32(0)]
            dsp.rec26[S32(2)] = dsp.rec26[S32(1)]
            dsp.rec26[S32(1)] = dsp.rec26[S32(0)]
            dsp.rec25[S32(1)] = dsp.rec25[S32(0)]
            dsp.rec38[S32(2)] = dsp.rec38[S32(1)]
            dsp.rec38[S32(1)] = dsp.rec38[S32(0)]
            dsp.rec37[S32(2)] = dsp.rec37[S32(1)]
            dsp.rec37[S32(1)] = dsp.rec37[S32(0)]
            dsp.rec36[S32(2)] = dsp.rec36[S32(1)]
            dsp.rec36[S32(1)] = dsp.rec36[S32(0)]
            dsp.rec35[S32(2)] = dsp.rec35[S32(1)]
            dsp.rec35[S32(1)] = dsp.rec35[S32(0)]
            dsp.rec34[S32(2)] = dsp.rec34[S32(1)]
            dsp.rec34[S32(1)] = dsp.rec34[S32(0)]
            dsp.rec33[S32(2)] = dsp.rec33[S32(1)]
            dsp.rec33[S32(1)] = dsp.rec33[S32(0)]
            dsp.rec32[S32(1)] = dsp.rec32[S32(0)]
            dsp.rec45[S32(2)] = dsp.rec45[S32(1)]
            dsp.rec45[S32(1)] = dsp.rec45[S32(0)]
            dsp.rec44[S32(2)] = dsp.rec44[S32(1)]
            dsp.rec44[S32(1)] = dsp.rec44[S32(0)]
            dsp.rec43[S32(2)] = dsp.rec43[S32(1)]
            dsp.rec43[S32(1)] = dsp.rec43[S32(0)]
            dsp.rec42[S32(2)] = dsp.rec42[S32(1)]
            dsp.rec42[S32(1)] = dsp.rec42[S32(0)]
            dsp.rec41[S32(2)] = dsp.rec41[S32(1)]
            dsp.rec41[S32(1)] = dsp.rec41[S32(0)]
            dsp.rec40[S32(2)] = dsp.rec40[S32(1)]
            dsp.rec40[S32(1)] = dsp.rec40[S32(0)]
            dsp.rec39[S32(1)] = dsp.rec39[S32(0)]
            dsp.rec52[S32(2)] = dsp.rec52[S32(1)]
            dsp.rec52[S32(1)] = dsp.rec52[S32(0)]
            dsp.rec51[S32(2)] = dsp.rec51[S32(1)]
            dsp.rec51[S32(1)] = dsp.rec51[S32(0)]
            dsp.rec50[S32(2)] = dsp.rec50[S32(1)]
            dsp.rec50[S32(1)] = dsp.rec50[S32(0)]
            dsp.rec49[S32(2)] = dsp.rec49[S32(1)]
            dsp.rec49[S32(1)] = dsp.rec49[S32(0)]
            dsp.rec48[S32(2)] = dsp.rec48[S32(1)]
            dsp.rec48[S32(1)] = dsp.rec48[S32(0)]
            dsp.rec47[S32(2)] = dsp.rec47[S32(1)]
            dsp.rec47[S32(1)] = dsp.rec47[S32(0)]
            dsp.rec46[S32(1)] = dsp.rec46[S32(0)]
            dsp.rec59[S32(2)] = dsp.rec59[S32(1)]
            dsp.rec59[S32(1)] = dsp.rec59[S32(0)]
            dsp.rec58[S32(2)] = dsp.rec58[S32(1)]
            dsp.rec58[S32(1)] = dsp.rec58[S32(0)]
            dsp.rec57[S32(2)] = dsp.rec57[S32(1)]
            dsp.rec57[S32(1)] = dsp.rec57[S32(0)]
            dsp.rec56[S32(2)] = dsp.rec56[S32(1)]
            dsp.rec56[S32(1)] = dsp.rec56[S32(0)]
            dsp.rec55[S32(2)] = dsp.rec55[S32(1)]
            dsp.rec55[S32(1)] = dsp.rec55[S32(0)]
            dsp.rec54[S32(2)] = dsp.rec54[S32(1)]
            dsp.rec54[S32(1)] = dsp.rec54[S32(0)]
            dsp.rec53[S32(1)] = dsp.rec53[S32(0)]
            dsp.rec66[S32(2)] = dsp.rec66[S32(1)]
            dsp.rec66[S32(1)] = dsp.rec66[S32(0)]
            dsp.rec65[S32(2)] = dsp.rec65[S32(1)]
            dsp.rec65[S32(1)] = dsp.rec65[S32(0)]
            dsp.rec64[S32(2)] = dsp.rec64[S32(1)]
            dsp.rec64[S32(1)] = dsp.rec64[S32(0)]
            dsp.rec63[S32(2)] = dsp.rec63[S32(1)]
            dsp.rec63[S32(1)] = dsp.rec63[S32(0)]
            dsp.rec62[S32(2)] = dsp.rec62[S32(1)]
            dsp.rec62[S32(1)] = dsp.rec62[S32(0)]
            dsp.rec61[S32(2)] = dsp.rec61[S32(1)]
            dsp.rec61[S32(1)] = dsp.rec61[S32(0)]
            dsp.rec60[S32(1)] = dsp.rec60[S32(0)]
            dsp.rec73[S32(2)] = dsp.rec73[S32(1)]
            dsp.rec73[S32(1)] = dsp.rec73[S32(0)]
            dsp.rec72[S32(2)] = dsp.rec72[S32(1)]
            dsp.rec72[S32(1)] = dsp.rec72[S32(0)]
            dsp.rec71[S32(2)] = dsp.rec71[S32(1)]
            dsp.rec71[S32(1)] = dsp.rec71[S32(0)]
            dsp.rec70[S32(2)] = dsp.rec70[S32(1)]
            dsp.rec70[S32(1)] = dsp.rec70[S32(0)]
            dsp.rec69[S32(2)] = dsp.rec69[S32(1)]
            dsp.rec69[S32(1)] = dsp.rec69[S32(0)]
            dsp.rec68[S32(2)] = dsp.rec68[S32(1)]
            dsp.rec68[S32(1)] = dsp.rec68[S32(0)]
            dsp.rec67[S32(1)] = dsp.rec67[S32(0)]
            dsp.rec80[S32(2)] = dsp.rec80[S32(1)]
            dsp.rec80[S32(1)] = dsp.rec80[S32(0)]
            dsp.rec79[S32(2)] = dsp.rec79[S32(1)]
            dsp.rec79[S32(1)] = dsp.rec79[S32(0)]
            dsp.rec78[S32(2)] = dsp.rec78[S32(1)]
            dsp.rec78[S32(1)] = dsp.rec78[S32(0)]
            dsp.rec77[S32(2)] = dsp.rec77[S32(1)]
            dsp.rec77[S32(1)] = dsp.rec77[S32(0)]
            dsp.rec76[S32(2)] = dsp.rec76[S32(1)]
            dsp.rec76[S32(1)] = dsp.rec76[S32(0)]
            dsp.rec75[S32(2)] = dsp.rec75[S32(1)]
            dsp.rec75[S32(1)] = dsp.rec75[S32(0)]
            dsp.rec74[S32(1)] = dsp.rec74[S32(0)]
            dsp.rec87[S32(2)] = dsp.rec87[S32(1)]
            dsp.rec87[S32(1)] = dsp.rec87[S32(0)]
            dsp.rec86[S32(2)] = dsp.rec86[S32(1)]
            dsp.rec86[S32(1)] = dsp.rec86[S32(0)]
            dsp.rec85[S32(2)] = dsp.rec85[S32(1)]
            dsp.rec85[S32(1)] = dsp.rec85[S32(0)]
            dsp.rec84[S32(2)] = dsp.rec84[S32(1)]
            dsp.rec84[S32(1)] = dsp.rec84[S32(0)]
            dsp.rec83[S32(2)] = dsp.rec83[S32(1)]
            dsp.rec83[S32(1)] = dsp.rec83[S32(0)]
            dsp.rec82[S32(2)] = dsp.rec82[S32(1)]
            dsp.rec82[S32(1)] = dsp.rec82[S32(0)]
            dsp.rec81[S32(1)] = dsp.rec81[S32(0)]
            dsp.rec94[S32(2)] = dsp.rec94[S32(1)]
            dsp.rec94[S32(1)] = dsp.rec94[S32(0)]
            dsp.rec93[S32(2)] = dsp.rec93[S32(1)]
            dsp.rec93[S32(1)] = dsp.rec93[S32(0)]
            dsp.rec92[S32(2)] = dsp.rec92[S32(1)]
            dsp.rec92[S32(1)] = dsp.rec92[S32(0)]
            dsp.rec91[S32(2)] = dsp.rec91[S32(1)]
            dsp.rec91[S32(1)] = dsp.rec91[S32(0)]
            dsp.rec90[S32(2)] = dsp.rec90[S32(1)]
            dsp.rec90[S32(1)] = dsp.rec90[S32(0)]
            dsp.rec89[S32(2)] = dsp.rec89[S32(1)]
            dsp.rec89[S32(1)] = dsp.rec89[S32(0)]
            dsp.rec88[S32(1)] = dsp.rec88[S32(0)]
            dsp.rec101[S32(2)] = dsp.rec101[S32(1)]
            dsp.rec101[S32(1)] = dsp.rec101[S32(0)]
            dsp.rec100[S32(2)] = dsp.rec100[S32(1)]
            dsp.rec100[S32(1)] = dsp.rec100[S32(0)]
            dsp.rec99[S32(2)] = dsp.rec99[S32(1)]
            dsp.rec99[S32(1)] = dsp.rec99[S32(0)]
            dsp.rec98[S32(2)] = dsp.rec98[S32(1)]
            dsp.rec98[S32(1)] = dsp.rec98[S32(0)]
            dsp.rec97[S32(2)] = dsp.rec97[S32(1)]
            dsp.rec97[S32(1)] = dsp.rec97[S32(0)]
            dsp.rec96[S32(2)] = dsp.rec96[S32(1)]
            dsp.rec96[S32(1)] = dsp.rec96[S32(0)]
            dsp.rec95[S32(1)] = dsp.rec95[S32(0)]
            dsp.rec105[S32(2)] = dsp.rec105[S32(1)]
            dsp.rec105[S32(1)] = dsp.rec105[S32(0)]
            dsp.rec104[S32(2)] = dsp.rec104[S32(1)]
            dsp.rec104[S32(1)] = dsp.rec104[S32(0)]
            dsp.rec103[S32(2)] = dsp.rec103[S32(1)]
            dsp.rec103[S32(1)] = dsp.rec103[S32(0)]
            dsp.rec102[S32(1)] = dsp.rec102[S32(0)]

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
