from conf import *
from help import *
from mem import *
from bench import *
from dsp import *
from gui import *
from meta import *

# ------------------------------------------------------------------------------
# Code generated with Faust 2.85.5 (https://faust.grame.fr)
# name: "bells"
# Compilation options: 
#   -a mojo/bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 
#   -mdy 33 -double -ftz 0
# ------------------------------------------------------------------------------

@fieldwise_init
struct mydsp(FaustDsp):
    var null_val: FaustFloat
    var sample_rate: S32
    var const0: F64
    var const1: F64
    var const2: F64
    var const3: F64
    var entry0: FaustFloat
    var const4: F64
    var entry1: FaustFloat
    var button0: FaustFloat
    var vec0: Arr[F64, 2]
    var iota0: S32
    var vec1: Arr[F64, 256]
    var const5: F64
    var const6: F64
    var const7: F64
    var rec1: Arr[F64, 3]
    var rec0: Arr[F64, 2]
    var entry2: FaustFloat
    var button1: FaustFloat
    var vec2: Arr[F64, 2]
    var vec3: Arr[F64, 256]
    var rec3: Arr[F64, 3]
    var rec2: Arr[F64, 2]
    var entry3: FaustFloat
    var button2: FaustFloat
    var vec4: Arr[F64, 2]
    var vec5: Arr[F64, 256]
    var rec5: Arr[F64, 3]
    var rec4: Arr[F64, 2]
    var entry4: FaustFloat
    var button3: FaustFloat
    var vec6: Arr[F64, 2]
    var vec7: Arr[F64, 256]
    var rec7: Arr[F64, 3]
    var rec6: Arr[F64, 2]
    var entry5: FaustFloat
    var button4: FaustFloat
    var vec8: Arr[F64, 2]
    var vec9: Arr[F64, 256]
    var rec9: Arr[F64, 3]
    var rec8: Arr[F64, 2]
    var entry6: FaustFloat
    var button5: FaustFloat
    var vec10: Arr[F64, 2]
    var vec11: Arr[F64, 256]
    var rec11: Arr[F64, 3]
    var rec10: Arr[F64, 2]
    var entry7: FaustFloat
    var button6: FaustFloat
    var vec12: Arr[F64, 2]
    var vec13: Arr[F64, 256]
    var rec13: Arr[F64, 3]
    var rec12: Arr[F64, 2]
    var entry8: FaustFloat
    var button7: FaustFloat
    var vec14: Arr[F64, 2]
    var vec15: Arr[F64, 256]
    var rec15: Arr[F64, 3]
    var rec14: Arr[F64, 2]
    var entry9: FaustFloat
    var button8: FaustFloat
    var vec16: Arr[F64, 2]
    var vec17: Arr[F64, 256]
    var rec17: Arr[F64, 3]
    var rec16: Arr[F64, 2]
    var entry10: FaustFloat
    var button9: FaustFloat
    var vec18: Arr[F64, 2]
    var vec19: Arr[F64, 256]
    var rec19: Arr[F64, 3]
    var rec18: Arr[F64, 2]
    var vec20: Arr[F64, 64]
    var const8: F64
    var const9: F64
    var rec21: Arr[F64, 3]
    var rec20: Arr[F64, 2]
    var vec21: Arr[F64, 64]
    var const10: F64
    var const11: F64
    var rec23: Arr[F64, 3]
    var rec22: Arr[F64, 2]
    var vec22: Arr[F64, 64]
    var const12: F64
    var const13: F64
    var rec25: Arr[F64, 3]
    var rec24: Arr[F64, 2]
    var vec23: Arr[F64, 64]
    var const14: F64
    var const15: F64
    var rec27: Arr[F64, 3]
    var rec26: Arr[F64, 2]
    var vec24: Arr[F64, 128]
    var const16: F64
    var const17: F64
    var rec29: Arr[F64, 3]
    var rec28: Arr[F64, 2]
    var vec25: Arr[F64, 128]
    var const18: F64
    var const19: F64
    var rec31: Arr[F64, 3]
    var rec30: Arr[F64, 2]
    var vec26: Arr[F64, 256]
    var const20: F64
    var const21: F64
    var rec33: Arr[F64, 3]
    var rec32: Arr[F64, 2]
    var vec27: Arr[F64, 256]
    var const22: F64
    var const23: F64
    var rec35: Arr[F64, 3]
    var rec34: Arr[F64, 2]
    var vec28: Arr[F64, 1024]
    var const24: F64
    var const25: F64
    var rec37: Arr[F64, 3]
    var rec36: Arr[F64, 2]
    var vec29: Arr[F64, 1024]
    var const26: F64
    var const27: F64
    var rec39: Arr[F64, 3]
    var rec38: Arr[F64, 2]
    var vec30: Arr[F64, 64]
    var rec41: Arr[F64, 3]
    var rec40: Arr[F64, 2]
    var vec31: Arr[F64, 64]
    var rec43: Arr[F64, 3]
    var rec42: Arr[F64, 2]
    var vec32: Arr[F64, 64]
    var rec45: Arr[F64, 3]
    var rec44: Arr[F64, 2]
    var vec33: Arr[F64, 64]
    var rec47: Arr[F64, 3]
    var rec46: Arr[F64, 2]
    var vec34: Arr[F64, 128]
    var rec49: Arr[F64, 3]
    var rec48: Arr[F64, 2]
    var vec35: Arr[F64, 128]
    var rec51: Arr[F64, 3]
    var rec50: Arr[F64, 2]
    var vec36: Arr[F64, 256]
    var rec53: Arr[F64, 3]
    var rec52: Arr[F64, 2]
    var vec37: Arr[F64, 256]
    var rec55: Arr[F64, 3]
    var rec54: Arr[F64, 2]
    var vec38: Arr[F64, 1024]
    var rec57: Arr[F64, 3]
    var rec56: Arr[F64, 2]
    var vec39: Arr[F64, 1024]
    var rec59: Arr[F64, 3]
    var rec58: Arr[F64, 2]
    var vec40: Arr[F64, 64]
    var rec61: Arr[F64, 3]
    var rec60: Arr[F64, 2]
    var vec41: Arr[F64, 64]
    var rec63: Arr[F64, 3]
    var rec62: Arr[F64, 2]
    var vec42: Arr[F64, 64]
    var rec65: Arr[F64, 3]
    var rec64: Arr[F64, 2]
    var vec43: Arr[F64, 64]
    var rec67: Arr[F64, 3]
    var rec66: Arr[F64, 2]
    var vec44: Arr[F64, 128]
    var rec69: Arr[F64, 3]
    var rec68: Arr[F64, 2]
    var vec45: Arr[F64, 128]
    var rec71: Arr[F64, 3]
    var rec70: Arr[F64, 2]
    var vec46: Arr[F64, 256]
    var rec73: Arr[F64, 3]
    var rec72: Arr[F64, 2]
    var vec47: Arr[F64, 256]
    var rec75: Arr[F64, 3]
    var rec74: Arr[F64, 2]
    var vec48: Arr[F64, 1024]
    var rec77: Arr[F64, 3]
    var rec76: Arr[F64, 2]
    var vec49: Arr[F64, 1024]
    var rec79: Arr[F64, 3]
    var rec78: Arr[F64, 2]
    var vec50: Arr[F64, 64]
    var rec81: Arr[F64, 3]
    var rec80: Arr[F64, 2]
    var vec51: Arr[F64, 64]
    var rec83: Arr[F64, 3]
    var rec82: Arr[F64, 2]
    var vec52: Arr[F64, 64]
    var rec85: Arr[F64, 3]
    var rec84: Arr[F64, 2]
    var vec53: Arr[F64, 64]
    var rec87: Arr[F64, 3]
    var rec86: Arr[F64, 2]
    var vec54: Arr[F64, 128]
    var rec89: Arr[F64, 3]
    var rec88: Arr[F64, 2]
    var vec55: Arr[F64, 128]
    var rec91: Arr[F64, 3]
    var rec90: Arr[F64, 2]
    var vec56: Arr[F64, 256]
    var rec93: Arr[F64, 3]
    var rec92: Arr[F64, 2]
    var vec57: Arr[F64, 256]
    var rec95: Arr[F64, 3]
    var rec94: Arr[F64, 2]
    var vec58: Arr[F64, 1024]
    var rec97: Arr[F64, 3]
    var rec96: Arr[F64, 2]
    var vec59: Arr[F64, 1024]
    var rec99: Arr[F64, 3]
    var rec98: Arr[F64, 2]
    var vec60: Arr[F64, 64]
    var rec101: Arr[F64, 3]
    var rec100: Arr[F64, 2]
    var vec61: Arr[F64, 64]
    var rec103: Arr[F64, 3]
    var rec102: Arr[F64, 2]
    var vec62: Arr[F64, 64]
    var rec105: Arr[F64, 3]
    var rec104: Arr[F64, 2]
    var vec63: Arr[F64, 64]
    var rec107: Arr[F64, 3]
    var rec106: Arr[F64, 2]
    var vec64: Arr[F64, 128]
    var rec109: Arr[F64, 3]
    var rec108: Arr[F64, 2]
    var vec65: Arr[F64, 128]
    var rec111: Arr[F64, 3]
    var rec110: Arr[F64, 2]
    var vec66: Arr[F64, 256]
    var rec113: Arr[F64, 3]
    var rec112: Arr[F64, 2]
    var vec67: Arr[F64, 256]
    var rec115: Arr[F64, 3]
    var rec114: Arr[F64, 2]
    var vec68: Arr[F64, 1024]
    var rec117: Arr[F64, 3]
    var rec116: Arr[F64, 2]
    var vec69: Arr[F64, 1024]
    var rec119: Arr[F64, 3]
    var rec118: Arr[F64, 2]
    var vec70: Arr[F64, 64]
    var rec121: Arr[F64, 3]
    var rec120: Arr[F64, 2]
    var vec71: Arr[F64, 64]
    var rec123: Arr[F64, 3]
    var rec122: Arr[F64, 2]
    var vec72: Arr[F64, 64]
    var rec125: Arr[F64, 3]
    var rec124: Arr[F64, 2]
    var vec73: Arr[F64, 64]
    var rec127: Arr[F64, 3]
    var rec126: Arr[F64, 2]
    var vec74: Arr[F64, 128]
    var rec129: Arr[F64, 3]
    var rec128: Arr[F64, 2]
    var vec75: Arr[F64, 128]
    var rec131: Arr[F64, 3]
    var rec130: Arr[F64, 2]
    var vec76: Arr[F64, 256]
    var rec133: Arr[F64, 3]
    var rec132: Arr[F64, 2]
    var vec77: Arr[F64, 256]
    var rec135: Arr[F64, 3]
    var rec134: Arr[F64, 2]
    var vec78: Arr[F64, 1024]
    var rec137: Arr[F64, 3]
    var rec136: Arr[F64, 2]
    var vec79: Arr[F64, 1024]
    var rec139: Arr[F64, 3]
    var rec138: Arr[F64, 2]
    var vec80: Arr[F64, 64]
    var rec141: Arr[F64, 3]
    var rec140: Arr[F64, 2]
    var vec81: Arr[F64, 64]
    var rec143: Arr[F64, 3]
    var rec142: Arr[F64, 2]
    var vec82: Arr[F64, 64]
    var rec145: Arr[F64, 3]
    var rec144: Arr[F64, 2]
    var vec83: Arr[F64, 64]
    var rec147: Arr[F64, 3]
    var rec146: Arr[F64, 2]
    var vec84: Arr[F64, 128]
    var rec149: Arr[F64, 3]
    var rec148: Arr[F64, 2]
    var vec85: Arr[F64, 128]
    var rec151: Arr[F64, 3]
    var rec150: Arr[F64, 2]
    var vec86: Arr[F64, 256]
    var rec153: Arr[F64, 3]
    var rec152: Arr[F64, 2]
    var vec87: Arr[F64, 256]
    var rec155: Arr[F64, 3]
    var rec154: Arr[F64, 2]
    var vec88: Arr[F64, 1024]
    var rec157: Arr[F64, 3]
    var rec156: Arr[F64, 2]
    var vec89: Arr[F64, 1024]
    var rec159: Arr[F64, 3]
    var rec158: Arr[F64, 2]
    var vec90: Arr[F64, 64]
    var rec161: Arr[F64, 3]
    var rec160: Arr[F64, 2]
    var vec91: Arr[F64, 64]
    var rec163: Arr[F64, 3]
    var rec162: Arr[F64, 2]
    var vec92: Arr[F64, 64]
    var rec165: Arr[F64, 3]
    var rec164: Arr[F64, 2]
    var vec93: Arr[F64, 64]
    var rec167: Arr[F64, 3]
    var rec166: Arr[F64, 2]
    var vec94: Arr[F64, 128]
    var rec169: Arr[F64, 3]
    var rec168: Arr[F64, 2]
    var vec95: Arr[F64, 128]
    var rec171: Arr[F64, 3]
    var rec170: Arr[F64, 2]
    var vec96: Arr[F64, 256]
    var rec173: Arr[F64, 3]
    var rec172: Arr[F64, 2]
    var vec97: Arr[F64, 256]
    var rec175: Arr[F64, 3]
    var rec174: Arr[F64, 2]
    var vec98: Arr[F64, 1024]
    var rec177: Arr[F64, 3]
    var rec176: Arr[F64, 2]
    var vec99: Arr[F64, 1024]
    var rec179: Arr[F64, 3]
    var rec178: Arr[F64, 2]
    var vec100: Arr[F64, 64]
    var rec181: Arr[F64, 3]
    var rec180: Arr[F64, 2]
    var vec101: Arr[F64, 64]
    var rec183: Arr[F64, 3]
    var rec182: Arr[F64, 2]
    var vec102: Arr[F64, 64]
    var rec185: Arr[F64, 3]
    var rec184: Arr[F64, 2]
    var vec103: Arr[F64, 64]
    var rec187: Arr[F64, 3]
    var rec186: Arr[F64, 2]
    var vec104: Arr[F64, 128]
    var rec189: Arr[F64, 3]
    var rec188: Arr[F64, 2]
    var vec105: Arr[F64, 128]
    var rec191: Arr[F64, 3]
    var rec190: Arr[F64, 2]
    var vec106: Arr[F64, 256]
    var rec193: Arr[F64, 3]
    var rec192: Arr[F64, 2]
    var vec107: Arr[F64, 256]
    var rec195: Arr[F64, 3]
    var rec194: Arr[F64, 2]
    var vec108: Arr[F64, 1024]
    var rec197: Arr[F64, 3]
    var rec196: Arr[F64, 2]
    var vec109: Arr[F64, 1024]
    var rec199: Arr[F64, 3]
    var rec198: Arr[F64, 2]
    var vec110: Arr[F64, 64]
    var rec201: Arr[F64, 3]
    var rec200: Arr[F64, 2]
    var vec111: Arr[F64, 64]
    var rec203: Arr[F64, 3]
    var rec202: Arr[F64, 2]
    var vec112: Arr[F64, 64]
    var rec205: Arr[F64, 3]
    var rec204: Arr[F64, 2]
    var vec113: Arr[F64, 64]
    var rec207: Arr[F64, 3]
    var rec206: Arr[F64, 2]
    var vec114: Arr[F64, 128]
    var rec209: Arr[F64, 3]
    var rec208: Arr[F64, 2]
    var vec115: Arr[F64, 1024]
    var rec211: Arr[F64, 3]
    var rec210: Arr[F64, 2]
    var vec116: Arr[F64, 1024]
    var rec213: Arr[F64, 3]
    var rec212: Arr[F64, 2]
    var vec117: Arr[F64, 256]
    var rec215: Arr[F64, 3]
    var rec214: Arr[F64, 2]
    var vec118: Arr[F64, 256]
    var rec217: Arr[F64, 3]
    var rec216: Arr[F64, 2]
    var vec119: Arr[F64, 128]
    var rec219: Arr[F64, 3]
    var rec218: Arr[F64, 2]

    @always_inline
    def __init__(out dsp):
        dsp.null_val = FaustFloat(0.0)
        dsp.sample_rate = 0
        dsp.const0 = 0.0
        dsp.const1 = 0.0
        dsp.const2 = 0.0
        dsp.const3 = 0.0
        dsp.entry0 = 0.0
        dsp.const4 = 0.0
        dsp.entry1 = 0.0
        dsp.button0 = 0.0
        dsp.vec0 = Arr[F64, 2](fill=0.0)
        dsp.iota0 = 0
        dsp.vec1 = Arr[F64, 256](fill=0.0)
        dsp.const5 = 0.0
        dsp.const6 = 0.0
        dsp.const7 = 0.0
        dsp.rec1 = Arr[F64, 3](fill=0.0)
        dsp.rec0 = Arr[F64, 2](fill=0.0)
        dsp.entry2 = 0.0
        dsp.button1 = 0.0
        dsp.vec2 = Arr[F64, 2](fill=0.0)
        dsp.vec3 = Arr[F64, 256](fill=0.0)
        dsp.rec3 = Arr[F64, 3](fill=0.0)
        dsp.rec2 = Arr[F64, 2](fill=0.0)
        dsp.entry3 = 0.0
        dsp.button2 = 0.0
        dsp.vec4 = Arr[F64, 2](fill=0.0)
        dsp.vec5 = Arr[F64, 256](fill=0.0)
        dsp.rec5 = Arr[F64, 3](fill=0.0)
        dsp.rec4 = Arr[F64, 2](fill=0.0)
        dsp.entry4 = 0.0
        dsp.button3 = 0.0
        dsp.vec6 = Arr[F64, 2](fill=0.0)
        dsp.vec7 = Arr[F64, 256](fill=0.0)
        dsp.rec7 = Arr[F64, 3](fill=0.0)
        dsp.rec6 = Arr[F64, 2](fill=0.0)
        dsp.entry5 = 0.0
        dsp.button4 = 0.0
        dsp.vec8 = Arr[F64, 2](fill=0.0)
        dsp.vec9 = Arr[F64, 256](fill=0.0)
        dsp.rec9 = Arr[F64, 3](fill=0.0)
        dsp.rec8 = Arr[F64, 2](fill=0.0)
        dsp.entry6 = 0.0
        dsp.button5 = 0.0
        dsp.vec10 = Arr[F64, 2](fill=0.0)
        dsp.vec11 = Arr[F64, 256](fill=0.0)
        dsp.rec11 = Arr[F64, 3](fill=0.0)
        dsp.rec10 = Arr[F64, 2](fill=0.0)
        dsp.entry7 = 0.0
        dsp.button6 = 0.0
        dsp.vec12 = Arr[F64, 2](fill=0.0)
        dsp.vec13 = Arr[F64, 256](fill=0.0)
        dsp.rec13 = Arr[F64, 3](fill=0.0)
        dsp.rec12 = Arr[F64, 2](fill=0.0)
        dsp.entry8 = 0.0
        dsp.button7 = 0.0
        dsp.vec14 = Arr[F64, 2](fill=0.0)
        dsp.vec15 = Arr[F64, 256](fill=0.0)
        dsp.rec15 = Arr[F64, 3](fill=0.0)
        dsp.rec14 = Arr[F64, 2](fill=0.0)
        dsp.entry9 = 0.0
        dsp.button8 = 0.0
        dsp.vec16 = Arr[F64, 2](fill=0.0)
        dsp.vec17 = Arr[F64, 256](fill=0.0)
        dsp.rec17 = Arr[F64, 3](fill=0.0)
        dsp.rec16 = Arr[F64, 2](fill=0.0)
        dsp.entry10 = 0.0
        dsp.button9 = 0.0
        dsp.vec18 = Arr[F64, 2](fill=0.0)
        dsp.vec19 = Arr[F64, 256](fill=0.0)
        dsp.rec19 = Arr[F64, 3](fill=0.0)
        dsp.rec18 = Arr[F64, 2](fill=0.0)
        dsp.vec20 = Arr[F64, 64](fill=0.0)
        dsp.const8 = 0.0
        dsp.const9 = 0.0
        dsp.rec21 = Arr[F64, 3](fill=0.0)
        dsp.rec20 = Arr[F64, 2](fill=0.0)
        dsp.vec21 = Arr[F64, 64](fill=0.0)
        dsp.const10 = 0.0
        dsp.const11 = 0.0
        dsp.rec23 = Arr[F64, 3](fill=0.0)
        dsp.rec22 = Arr[F64, 2](fill=0.0)
        dsp.vec22 = Arr[F64, 64](fill=0.0)
        dsp.const12 = 0.0
        dsp.const13 = 0.0
        dsp.rec25 = Arr[F64, 3](fill=0.0)
        dsp.rec24 = Arr[F64, 2](fill=0.0)
        dsp.vec23 = Arr[F64, 64](fill=0.0)
        dsp.const14 = 0.0
        dsp.const15 = 0.0
        dsp.rec27 = Arr[F64, 3](fill=0.0)
        dsp.rec26 = Arr[F64, 2](fill=0.0)
        dsp.vec24 = Arr[F64, 128](fill=0.0)
        dsp.const16 = 0.0
        dsp.const17 = 0.0
        dsp.rec29 = Arr[F64, 3](fill=0.0)
        dsp.rec28 = Arr[F64, 2](fill=0.0)
        dsp.vec25 = Arr[F64, 128](fill=0.0)
        dsp.const18 = 0.0
        dsp.const19 = 0.0
        dsp.rec31 = Arr[F64, 3](fill=0.0)
        dsp.rec30 = Arr[F64, 2](fill=0.0)
        dsp.vec26 = Arr[F64, 256](fill=0.0)
        dsp.const20 = 0.0
        dsp.const21 = 0.0
        dsp.rec33 = Arr[F64, 3](fill=0.0)
        dsp.rec32 = Arr[F64, 2](fill=0.0)
        dsp.vec27 = Arr[F64, 256](fill=0.0)
        dsp.const22 = 0.0
        dsp.const23 = 0.0
        dsp.rec35 = Arr[F64, 3](fill=0.0)
        dsp.rec34 = Arr[F64, 2](fill=0.0)
        dsp.vec28 = Arr[F64, 1024](fill=0.0)
        dsp.const24 = 0.0
        dsp.const25 = 0.0
        dsp.rec37 = Arr[F64, 3](fill=0.0)
        dsp.rec36 = Arr[F64, 2](fill=0.0)
        dsp.vec29 = Arr[F64, 1024](fill=0.0)
        dsp.const26 = 0.0
        dsp.const27 = 0.0
        dsp.rec39 = Arr[F64, 3](fill=0.0)
        dsp.rec38 = Arr[F64, 2](fill=0.0)
        dsp.vec30 = Arr[F64, 64](fill=0.0)
        dsp.rec41 = Arr[F64, 3](fill=0.0)
        dsp.rec40 = Arr[F64, 2](fill=0.0)
        dsp.vec31 = Arr[F64, 64](fill=0.0)
        dsp.rec43 = Arr[F64, 3](fill=0.0)
        dsp.rec42 = Arr[F64, 2](fill=0.0)
        dsp.vec32 = Arr[F64, 64](fill=0.0)
        dsp.rec45 = Arr[F64, 3](fill=0.0)
        dsp.rec44 = Arr[F64, 2](fill=0.0)
        dsp.vec33 = Arr[F64, 64](fill=0.0)
        dsp.rec47 = Arr[F64, 3](fill=0.0)
        dsp.rec46 = Arr[F64, 2](fill=0.0)
        dsp.vec34 = Arr[F64, 128](fill=0.0)
        dsp.rec49 = Arr[F64, 3](fill=0.0)
        dsp.rec48 = Arr[F64, 2](fill=0.0)
        dsp.vec35 = Arr[F64, 128](fill=0.0)
        dsp.rec51 = Arr[F64, 3](fill=0.0)
        dsp.rec50 = Arr[F64, 2](fill=0.0)
        dsp.vec36 = Arr[F64, 256](fill=0.0)
        dsp.rec53 = Arr[F64, 3](fill=0.0)
        dsp.rec52 = Arr[F64, 2](fill=0.0)
        dsp.vec37 = Arr[F64, 256](fill=0.0)
        dsp.rec55 = Arr[F64, 3](fill=0.0)
        dsp.rec54 = Arr[F64, 2](fill=0.0)
        dsp.vec38 = Arr[F64, 1024](fill=0.0)
        dsp.rec57 = Arr[F64, 3](fill=0.0)
        dsp.rec56 = Arr[F64, 2](fill=0.0)
        dsp.vec39 = Arr[F64, 1024](fill=0.0)
        dsp.rec59 = Arr[F64, 3](fill=0.0)
        dsp.rec58 = Arr[F64, 2](fill=0.0)
        dsp.vec40 = Arr[F64, 64](fill=0.0)
        dsp.rec61 = Arr[F64, 3](fill=0.0)
        dsp.rec60 = Arr[F64, 2](fill=0.0)
        dsp.vec41 = Arr[F64, 64](fill=0.0)
        dsp.rec63 = Arr[F64, 3](fill=0.0)
        dsp.rec62 = Arr[F64, 2](fill=0.0)
        dsp.vec42 = Arr[F64, 64](fill=0.0)
        dsp.rec65 = Arr[F64, 3](fill=0.0)
        dsp.rec64 = Arr[F64, 2](fill=0.0)
        dsp.vec43 = Arr[F64, 64](fill=0.0)
        dsp.rec67 = Arr[F64, 3](fill=0.0)
        dsp.rec66 = Arr[F64, 2](fill=0.0)
        dsp.vec44 = Arr[F64, 128](fill=0.0)
        dsp.rec69 = Arr[F64, 3](fill=0.0)
        dsp.rec68 = Arr[F64, 2](fill=0.0)
        dsp.vec45 = Arr[F64, 128](fill=0.0)
        dsp.rec71 = Arr[F64, 3](fill=0.0)
        dsp.rec70 = Arr[F64, 2](fill=0.0)
        dsp.vec46 = Arr[F64, 256](fill=0.0)
        dsp.rec73 = Arr[F64, 3](fill=0.0)
        dsp.rec72 = Arr[F64, 2](fill=0.0)
        dsp.vec47 = Arr[F64, 256](fill=0.0)
        dsp.rec75 = Arr[F64, 3](fill=0.0)
        dsp.rec74 = Arr[F64, 2](fill=0.0)
        dsp.vec48 = Arr[F64, 1024](fill=0.0)
        dsp.rec77 = Arr[F64, 3](fill=0.0)
        dsp.rec76 = Arr[F64, 2](fill=0.0)
        dsp.vec49 = Arr[F64, 1024](fill=0.0)
        dsp.rec79 = Arr[F64, 3](fill=0.0)
        dsp.rec78 = Arr[F64, 2](fill=0.0)
        dsp.vec50 = Arr[F64, 64](fill=0.0)
        dsp.rec81 = Arr[F64, 3](fill=0.0)
        dsp.rec80 = Arr[F64, 2](fill=0.0)
        dsp.vec51 = Arr[F64, 64](fill=0.0)
        dsp.rec83 = Arr[F64, 3](fill=0.0)
        dsp.rec82 = Arr[F64, 2](fill=0.0)
        dsp.vec52 = Arr[F64, 64](fill=0.0)
        dsp.rec85 = Arr[F64, 3](fill=0.0)
        dsp.rec84 = Arr[F64, 2](fill=0.0)
        dsp.vec53 = Arr[F64, 64](fill=0.0)
        dsp.rec87 = Arr[F64, 3](fill=0.0)
        dsp.rec86 = Arr[F64, 2](fill=0.0)
        dsp.vec54 = Arr[F64, 128](fill=0.0)
        dsp.rec89 = Arr[F64, 3](fill=0.0)
        dsp.rec88 = Arr[F64, 2](fill=0.0)
        dsp.vec55 = Arr[F64, 128](fill=0.0)
        dsp.rec91 = Arr[F64, 3](fill=0.0)
        dsp.rec90 = Arr[F64, 2](fill=0.0)
        dsp.vec56 = Arr[F64, 256](fill=0.0)
        dsp.rec93 = Arr[F64, 3](fill=0.0)
        dsp.rec92 = Arr[F64, 2](fill=0.0)
        dsp.vec57 = Arr[F64, 256](fill=0.0)
        dsp.rec95 = Arr[F64, 3](fill=0.0)
        dsp.rec94 = Arr[F64, 2](fill=0.0)
        dsp.vec58 = Arr[F64, 1024](fill=0.0)
        dsp.rec97 = Arr[F64, 3](fill=0.0)
        dsp.rec96 = Arr[F64, 2](fill=0.0)
        dsp.vec59 = Arr[F64, 1024](fill=0.0)
        dsp.rec99 = Arr[F64, 3](fill=0.0)
        dsp.rec98 = Arr[F64, 2](fill=0.0)
        dsp.vec60 = Arr[F64, 64](fill=0.0)
        dsp.rec101 = Arr[F64, 3](fill=0.0)
        dsp.rec100 = Arr[F64, 2](fill=0.0)
        dsp.vec61 = Arr[F64, 64](fill=0.0)
        dsp.rec103 = Arr[F64, 3](fill=0.0)
        dsp.rec102 = Arr[F64, 2](fill=0.0)
        dsp.vec62 = Arr[F64, 64](fill=0.0)
        dsp.rec105 = Arr[F64, 3](fill=0.0)
        dsp.rec104 = Arr[F64, 2](fill=0.0)
        dsp.vec63 = Arr[F64, 64](fill=0.0)
        dsp.rec107 = Arr[F64, 3](fill=0.0)
        dsp.rec106 = Arr[F64, 2](fill=0.0)
        dsp.vec64 = Arr[F64, 128](fill=0.0)
        dsp.rec109 = Arr[F64, 3](fill=0.0)
        dsp.rec108 = Arr[F64, 2](fill=0.0)
        dsp.vec65 = Arr[F64, 128](fill=0.0)
        dsp.rec111 = Arr[F64, 3](fill=0.0)
        dsp.rec110 = Arr[F64, 2](fill=0.0)
        dsp.vec66 = Arr[F64, 256](fill=0.0)
        dsp.rec113 = Arr[F64, 3](fill=0.0)
        dsp.rec112 = Arr[F64, 2](fill=0.0)
        dsp.vec67 = Arr[F64, 256](fill=0.0)
        dsp.rec115 = Arr[F64, 3](fill=0.0)
        dsp.rec114 = Arr[F64, 2](fill=0.0)
        dsp.vec68 = Arr[F64, 1024](fill=0.0)
        dsp.rec117 = Arr[F64, 3](fill=0.0)
        dsp.rec116 = Arr[F64, 2](fill=0.0)
        dsp.vec69 = Arr[F64, 1024](fill=0.0)
        dsp.rec119 = Arr[F64, 3](fill=0.0)
        dsp.rec118 = Arr[F64, 2](fill=0.0)
        dsp.vec70 = Arr[F64, 64](fill=0.0)
        dsp.rec121 = Arr[F64, 3](fill=0.0)
        dsp.rec120 = Arr[F64, 2](fill=0.0)
        dsp.vec71 = Arr[F64, 64](fill=0.0)
        dsp.rec123 = Arr[F64, 3](fill=0.0)
        dsp.rec122 = Arr[F64, 2](fill=0.0)
        dsp.vec72 = Arr[F64, 64](fill=0.0)
        dsp.rec125 = Arr[F64, 3](fill=0.0)
        dsp.rec124 = Arr[F64, 2](fill=0.0)
        dsp.vec73 = Arr[F64, 64](fill=0.0)
        dsp.rec127 = Arr[F64, 3](fill=0.0)
        dsp.rec126 = Arr[F64, 2](fill=0.0)
        dsp.vec74 = Arr[F64, 128](fill=0.0)
        dsp.rec129 = Arr[F64, 3](fill=0.0)
        dsp.rec128 = Arr[F64, 2](fill=0.0)
        dsp.vec75 = Arr[F64, 128](fill=0.0)
        dsp.rec131 = Arr[F64, 3](fill=0.0)
        dsp.rec130 = Arr[F64, 2](fill=0.0)
        dsp.vec76 = Arr[F64, 256](fill=0.0)
        dsp.rec133 = Arr[F64, 3](fill=0.0)
        dsp.rec132 = Arr[F64, 2](fill=0.0)
        dsp.vec77 = Arr[F64, 256](fill=0.0)
        dsp.rec135 = Arr[F64, 3](fill=0.0)
        dsp.rec134 = Arr[F64, 2](fill=0.0)
        dsp.vec78 = Arr[F64, 1024](fill=0.0)
        dsp.rec137 = Arr[F64, 3](fill=0.0)
        dsp.rec136 = Arr[F64, 2](fill=0.0)
        dsp.vec79 = Arr[F64, 1024](fill=0.0)
        dsp.rec139 = Arr[F64, 3](fill=0.0)
        dsp.rec138 = Arr[F64, 2](fill=0.0)
        dsp.vec80 = Arr[F64, 64](fill=0.0)
        dsp.rec141 = Arr[F64, 3](fill=0.0)
        dsp.rec140 = Arr[F64, 2](fill=0.0)
        dsp.vec81 = Arr[F64, 64](fill=0.0)
        dsp.rec143 = Arr[F64, 3](fill=0.0)
        dsp.rec142 = Arr[F64, 2](fill=0.0)
        dsp.vec82 = Arr[F64, 64](fill=0.0)
        dsp.rec145 = Arr[F64, 3](fill=0.0)
        dsp.rec144 = Arr[F64, 2](fill=0.0)
        dsp.vec83 = Arr[F64, 64](fill=0.0)
        dsp.rec147 = Arr[F64, 3](fill=0.0)
        dsp.rec146 = Arr[F64, 2](fill=0.0)
        dsp.vec84 = Arr[F64, 128](fill=0.0)
        dsp.rec149 = Arr[F64, 3](fill=0.0)
        dsp.rec148 = Arr[F64, 2](fill=0.0)
        dsp.vec85 = Arr[F64, 128](fill=0.0)
        dsp.rec151 = Arr[F64, 3](fill=0.0)
        dsp.rec150 = Arr[F64, 2](fill=0.0)
        dsp.vec86 = Arr[F64, 256](fill=0.0)
        dsp.rec153 = Arr[F64, 3](fill=0.0)
        dsp.rec152 = Arr[F64, 2](fill=0.0)
        dsp.vec87 = Arr[F64, 256](fill=0.0)
        dsp.rec155 = Arr[F64, 3](fill=0.0)
        dsp.rec154 = Arr[F64, 2](fill=0.0)
        dsp.vec88 = Arr[F64, 1024](fill=0.0)
        dsp.rec157 = Arr[F64, 3](fill=0.0)
        dsp.rec156 = Arr[F64, 2](fill=0.0)
        dsp.vec89 = Arr[F64, 1024](fill=0.0)
        dsp.rec159 = Arr[F64, 3](fill=0.0)
        dsp.rec158 = Arr[F64, 2](fill=0.0)
        dsp.vec90 = Arr[F64, 64](fill=0.0)
        dsp.rec161 = Arr[F64, 3](fill=0.0)
        dsp.rec160 = Arr[F64, 2](fill=0.0)
        dsp.vec91 = Arr[F64, 64](fill=0.0)
        dsp.rec163 = Arr[F64, 3](fill=0.0)
        dsp.rec162 = Arr[F64, 2](fill=0.0)
        dsp.vec92 = Arr[F64, 64](fill=0.0)
        dsp.rec165 = Arr[F64, 3](fill=0.0)
        dsp.rec164 = Arr[F64, 2](fill=0.0)
        dsp.vec93 = Arr[F64, 64](fill=0.0)
        dsp.rec167 = Arr[F64, 3](fill=0.0)
        dsp.rec166 = Arr[F64, 2](fill=0.0)
        dsp.vec94 = Arr[F64, 128](fill=0.0)
        dsp.rec169 = Arr[F64, 3](fill=0.0)
        dsp.rec168 = Arr[F64, 2](fill=0.0)
        dsp.vec95 = Arr[F64, 128](fill=0.0)
        dsp.rec171 = Arr[F64, 3](fill=0.0)
        dsp.rec170 = Arr[F64, 2](fill=0.0)
        dsp.vec96 = Arr[F64, 256](fill=0.0)
        dsp.rec173 = Arr[F64, 3](fill=0.0)
        dsp.rec172 = Arr[F64, 2](fill=0.0)
        dsp.vec97 = Arr[F64, 256](fill=0.0)
        dsp.rec175 = Arr[F64, 3](fill=0.0)
        dsp.rec174 = Arr[F64, 2](fill=0.0)
        dsp.vec98 = Arr[F64, 1024](fill=0.0)
        dsp.rec177 = Arr[F64, 3](fill=0.0)
        dsp.rec176 = Arr[F64, 2](fill=0.0)
        dsp.vec99 = Arr[F64, 1024](fill=0.0)
        dsp.rec179 = Arr[F64, 3](fill=0.0)
        dsp.rec178 = Arr[F64, 2](fill=0.0)
        dsp.vec100 = Arr[F64, 64](fill=0.0)
        dsp.rec181 = Arr[F64, 3](fill=0.0)
        dsp.rec180 = Arr[F64, 2](fill=0.0)
        dsp.vec101 = Arr[F64, 64](fill=0.0)
        dsp.rec183 = Arr[F64, 3](fill=0.0)
        dsp.rec182 = Arr[F64, 2](fill=0.0)
        dsp.vec102 = Arr[F64, 64](fill=0.0)
        dsp.rec185 = Arr[F64, 3](fill=0.0)
        dsp.rec184 = Arr[F64, 2](fill=0.0)
        dsp.vec103 = Arr[F64, 64](fill=0.0)
        dsp.rec187 = Arr[F64, 3](fill=0.0)
        dsp.rec186 = Arr[F64, 2](fill=0.0)
        dsp.vec104 = Arr[F64, 128](fill=0.0)
        dsp.rec189 = Arr[F64, 3](fill=0.0)
        dsp.rec188 = Arr[F64, 2](fill=0.0)
        dsp.vec105 = Arr[F64, 128](fill=0.0)
        dsp.rec191 = Arr[F64, 3](fill=0.0)
        dsp.rec190 = Arr[F64, 2](fill=0.0)
        dsp.vec106 = Arr[F64, 256](fill=0.0)
        dsp.rec193 = Arr[F64, 3](fill=0.0)
        dsp.rec192 = Arr[F64, 2](fill=0.0)
        dsp.vec107 = Arr[F64, 256](fill=0.0)
        dsp.rec195 = Arr[F64, 3](fill=0.0)
        dsp.rec194 = Arr[F64, 2](fill=0.0)
        dsp.vec108 = Arr[F64, 1024](fill=0.0)
        dsp.rec197 = Arr[F64, 3](fill=0.0)
        dsp.rec196 = Arr[F64, 2](fill=0.0)
        dsp.vec109 = Arr[F64, 1024](fill=0.0)
        dsp.rec199 = Arr[F64, 3](fill=0.0)
        dsp.rec198 = Arr[F64, 2](fill=0.0)
        dsp.vec110 = Arr[F64, 64](fill=0.0)
        dsp.rec201 = Arr[F64, 3](fill=0.0)
        dsp.rec200 = Arr[F64, 2](fill=0.0)
        dsp.vec111 = Arr[F64, 64](fill=0.0)
        dsp.rec203 = Arr[F64, 3](fill=0.0)
        dsp.rec202 = Arr[F64, 2](fill=0.0)
        dsp.vec112 = Arr[F64, 64](fill=0.0)
        dsp.rec205 = Arr[F64, 3](fill=0.0)
        dsp.rec204 = Arr[F64, 2](fill=0.0)
        dsp.vec113 = Arr[F64, 64](fill=0.0)
        dsp.rec207 = Arr[F64, 3](fill=0.0)
        dsp.rec206 = Arr[F64, 2](fill=0.0)
        dsp.vec114 = Arr[F64, 128](fill=0.0)
        dsp.rec209 = Arr[F64, 3](fill=0.0)
        dsp.rec208 = Arr[F64, 2](fill=0.0)
        dsp.vec115 = Arr[F64, 1024](fill=0.0)
        dsp.rec211 = Arr[F64, 3](fill=0.0)
        dsp.rec210 = Arr[F64, 2](fill=0.0)
        dsp.vec116 = Arr[F64, 1024](fill=0.0)
        dsp.rec213 = Arr[F64, 3](fill=0.0)
        dsp.rec212 = Arr[F64, 2](fill=0.0)
        dsp.vec117 = Arr[F64, 256](fill=0.0)
        dsp.rec215 = Arr[F64, 3](fill=0.0)
        dsp.rec214 = Arr[F64, 2](fill=0.0)
        dsp.vec118 = Arr[F64, 256](fill=0.0)
        dsp.rec217 = Arr[F64, 3](fill=0.0)
        dsp.rec216 = Arr[F64, 2](fill=0.0)
        dsp.vec119 = Arr[F64, 128](fill=0.0)
        dsp.rec219 = Arr[F64, 3](fill=0.0)
        dsp.rec218 = Arr[F64, 2](fill=0.0)

    @always_inline
    def get_sample_rate(read dsp) -> S32:
        return dsp.sample_rate

    @always_inline
    def get_num_outputs(read dsp) -> S32:
        return 1

    @always_inline
    def get_num_inputs(read dsp) -> S32:
        return 0

    @always_inline
    def class_init(mut dsp, sample_rate: S32) -> None:
        pass

    @always_inline
    def instance_constants(mut dsp, sample_rate: S32) -> None:
        dsp.sample_rate = sample_rate
        dsp.const0 = min(F64(1.92e+05), max(F64(1.0), F64(dsp.sample_rate)))
        dsp.const1 = (F64(100.53097)) / (dsp.const0)
        dsp.const2 = pow((F64(1.0)) - (dsp.const1), F64(2.0))
        dsp.const3 = (F64(0.5)) * ((F64(1.0)) - (dsp.const2))
        dsp.const4 = (F64(0.5)) * (dsp.const0)
        dsp.const5 = (F64(0.0003984129014894459)) * (dsp.const0)
        dsp.const6 = (F64(2.0)) * ((dsp.const1) - (F64(1.0)))
        dsp.const7 = (F64(15770.53724041224)) / (dsp.const0)
        dsp.const8 = (F64(0.00010341847835949931)) * (dsp.const0)
        dsp.const9 = (F64(60754.95984536373)) / (dsp.const0)
        dsp.const10 = (F64(0.0001315173052074703)) * (dsp.const0)
        dsp.const11 = (F64(47774.591260733265)) / (dsp.const0)
        dsp.const12 = (F64(0.00017745447685774287)) * (dsp.const0)
        dsp.const13 = (F64(35407.309025158844)) / (dsp.const0)
        dsp.const14 = (F64(0.00017709981763677576)) * (dsp.const0)
        dsp.const15 = (F64(35478.215527508604)) / (dsp.const0)
        dsp.const16 = (F64(0.0002520911795242428)) * (dsp.const0)
        dsp.const17 = (F64(24924.25761130514)) / (dsp.const0)
        dsp.const18 = (F64(0.00025257576767878827)) * (dsp.const0)
        dsp.const19 = (F64(24876.438297084)) / (dsp.const0)
        dsp.const20 = (F64(0.0007592720726222721)) * (dsp.const0)
        dsp.const21 = (F64(8275.275394102113)) / (dsp.const0)
        dsp.const22 = (F64(0.0007628705880371271)) * (dsp.const0)
        dsp.const23 = (F64(8236.24032506836)) / (dsp.const0)
        dsp.const24 = (F64(0.0022639167877643303)) * (dsp.const0)
        dsp.const25 = (F64(2775.3606201245543)) / (dsp.const0)
        dsp.const26 = (F64(0.002281606486610892)) * (dsp.const0)
        dsp.const27 = (F64(2753.842758105527)) / (dsp.const0)

    @always_inline
    def instance_reset_user_interface(mut dsp) -> None:
        dsp.entry0 = 69.0
        dsp.entry1 = 0.989
        dsp.button0 = 0.0
        dsp.entry2 = 68.0
        dsp.button1 = 0.0
        dsp.entry3 = 67.0
        dsp.button2 = 0.0
        dsp.entry4 = 66.0
        dsp.button3 = 0.0
        dsp.entry5 = 65.0
        dsp.button4 = 0.0
        dsp.entry6 = 64.0
        dsp.button5 = 0.0
        dsp.entry7 = 63.0
        dsp.button6 = 0.0
        dsp.entry8 = 62.0
        dsp.button7 = 0.0
        dsp.entry9 = 60.0
        dsp.button8 = 0.0
        dsp.entry10 = 61.0
        dsp.button9 = 0.0

    @always_inline
    def instance_clear(mut dsp) -> None:
        var l0 = S32(0)
        while ((l0) < (S32(2))): 
            dsp.vec0[l0] = F64(0.0)
            l0 = (l0) + (S32(1))
        dsp.iota0 = S32(0)
        var l1 = S32(0)
        while ((l1) < (S32(256))): 
            dsp.vec1[l1] = F64(0.0)
            l1 = (l1) + (S32(1))
        var l2 = S32(0)
        while ((l2) < (S32(3))): 
            dsp.rec1[l2] = F64(0.0)
            l2 = (l2) + (S32(1))
        var l3 = S32(0)
        while ((l3) < (S32(2))): 
            dsp.rec0[l3] = F64(0.0)
            l3 = (l3) + (S32(1))
        var l4 = S32(0)
        while ((l4) < (S32(2))): 
            dsp.vec2[l4] = F64(0.0)
            l4 = (l4) + (S32(1))
        var l5 = S32(0)
        while ((l5) < (S32(256))): 
            dsp.vec3[l5] = F64(0.0)
            l5 = (l5) + (S32(1))
        var l6 = S32(0)
        while ((l6) < (S32(3))): 
            dsp.rec3[l6] = F64(0.0)
            l6 = (l6) + (S32(1))
        var l7 = S32(0)
        while ((l7) < (S32(2))): 
            dsp.rec2[l7] = F64(0.0)
            l7 = (l7) + (S32(1))
        var l8 = S32(0)
        while ((l8) < (S32(2))): 
            dsp.vec4[l8] = F64(0.0)
            l8 = (l8) + (S32(1))
        var l9 = S32(0)
        while ((l9) < (S32(256))): 
            dsp.vec5[l9] = F64(0.0)
            l9 = (l9) + (S32(1))
        var l10 = S32(0)
        while ((l10) < (S32(3))): 
            dsp.rec5[l10] = F64(0.0)
            l10 = (l10) + (S32(1))
        var l11 = S32(0)
        while ((l11) < (S32(2))): 
            dsp.rec4[l11] = F64(0.0)
            l11 = (l11) + (S32(1))
        var l12 = S32(0)
        while ((l12) < (S32(2))): 
            dsp.vec6[l12] = F64(0.0)
            l12 = (l12) + (S32(1))
        var l13 = S32(0)
        while ((l13) < (S32(256))): 
            dsp.vec7[l13] = F64(0.0)
            l13 = (l13) + (S32(1))
        var l14 = S32(0)
        while ((l14) < (S32(3))): 
            dsp.rec7[l14] = F64(0.0)
            l14 = (l14) + (S32(1))
        var l15 = S32(0)
        while ((l15) < (S32(2))): 
            dsp.rec6[l15] = F64(0.0)
            l15 = (l15) + (S32(1))
        var l16 = S32(0)
        while ((l16) < (S32(2))): 
            dsp.vec8[l16] = F64(0.0)
            l16 = (l16) + (S32(1))
        var l17 = S32(0)
        while ((l17) < (S32(256))): 
            dsp.vec9[l17] = F64(0.0)
            l17 = (l17) + (S32(1))
        var l18 = S32(0)
        while ((l18) < (S32(3))): 
            dsp.rec9[l18] = F64(0.0)
            l18 = (l18) + (S32(1))
        var l19 = S32(0)
        while ((l19) < (S32(2))): 
            dsp.rec8[l19] = F64(0.0)
            l19 = (l19) + (S32(1))
        var l20 = S32(0)
        while ((l20) < (S32(2))): 
            dsp.vec10[l20] = F64(0.0)
            l20 = (l20) + (S32(1))
        var l21 = S32(0)
        while ((l21) < (S32(256))): 
            dsp.vec11[l21] = F64(0.0)
            l21 = (l21) + (S32(1))
        var l22 = S32(0)
        while ((l22) < (S32(3))): 
            dsp.rec11[l22] = F64(0.0)
            l22 = (l22) + (S32(1))
        var l23 = S32(0)
        while ((l23) < (S32(2))): 
            dsp.rec10[l23] = F64(0.0)
            l23 = (l23) + (S32(1))
        var l24 = S32(0)
        while ((l24) < (S32(2))): 
            dsp.vec12[l24] = F64(0.0)
            l24 = (l24) + (S32(1))
        var l25 = S32(0)
        while ((l25) < (S32(256))): 
            dsp.vec13[l25] = F64(0.0)
            l25 = (l25) + (S32(1))
        var l26 = S32(0)
        while ((l26) < (S32(3))): 
            dsp.rec13[l26] = F64(0.0)
            l26 = (l26) + (S32(1))
        var l27 = S32(0)
        while ((l27) < (S32(2))): 
            dsp.rec12[l27] = F64(0.0)
            l27 = (l27) + (S32(1))
        var l28 = S32(0)
        while ((l28) < (S32(2))): 
            dsp.vec14[l28] = F64(0.0)
            l28 = (l28) + (S32(1))
        var l29 = S32(0)
        while ((l29) < (S32(256))): 
            dsp.vec15[l29] = F64(0.0)
            l29 = (l29) + (S32(1))
        var l30 = S32(0)
        while ((l30) < (S32(3))): 
            dsp.rec15[l30] = F64(0.0)
            l30 = (l30) + (S32(1))
        var l31 = S32(0)
        while ((l31) < (S32(2))): 
            dsp.rec14[l31] = F64(0.0)
            l31 = (l31) + (S32(1))
        var l32 = S32(0)
        while ((l32) < (S32(2))): 
            dsp.vec16[l32] = F64(0.0)
            l32 = (l32) + (S32(1))
        var l33 = S32(0)
        while ((l33) < (S32(256))): 
            dsp.vec17[l33] = F64(0.0)
            l33 = (l33) + (S32(1))
        var l34 = S32(0)
        while ((l34) < (S32(3))): 
            dsp.rec17[l34] = F64(0.0)
            l34 = (l34) + (S32(1))
        var l35 = S32(0)
        while ((l35) < (S32(2))): 
            dsp.rec16[l35] = F64(0.0)
            l35 = (l35) + (S32(1))
        var l36 = S32(0)
        while ((l36) < (S32(2))): 
            dsp.vec18[l36] = F64(0.0)
            l36 = (l36) + (S32(1))
        var l37 = S32(0)
        while ((l37) < (S32(256))): 
            dsp.vec19[l37] = F64(0.0)
            l37 = (l37) + (S32(1))
        var l38 = S32(0)
        while ((l38) < (S32(3))): 
            dsp.rec19[l38] = F64(0.0)
            l38 = (l38) + (S32(1))
        var l39 = S32(0)
        while ((l39) < (S32(2))): 
            dsp.rec18[l39] = F64(0.0)
            l39 = (l39) + (S32(1))
        var l40 = S32(0)
        while ((l40) < (S32(64))): 
            dsp.vec20[l40] = F64(0.0)
            l40 = (l40) + (S32(1))
        var l41 = S32(0)
        while ((l41) < (S32(3))): 
            dsp.rec21[l41] = F64(0.0)
            l41 = (l41) + (S32(1))
        var l42 = S32(0)
        while ((l42) < (S32(2))): 
            dsp.rec20[l42] = F64(0.0)
            l42 = (l42) + (S32(1))
        var l43 = S32(0)
        while ((l43) < (S32(64))): 
            dsp.vec21[l43] = F64(0.0)
            l43 = (l43) + (S32(1))
        var l44 = S32(0)
        while ((l44) < (S32(3))): 
            dsp.rec23[l44] = F64(0.0)
            l44 = (l44) + (S32(1))
        var l45 = S32(0)
        while ((l45) < (S32(2))): 
            dsp.rec22[l45] = F64(0.0)
            l45 = (l45) + (S32(1))
        var l46 = S32(0)
        while ((l46) < (S32(64))): 
            dsp.vec22[l46] = F64(0.0)
            l46 = (l46) + (S32(1))
        var l47 = S32(0)
        while ((l47) < (S32(3))): 
            dsp.rec25[l47] = F64(0.0)
            l47 = (l47) + (S32(1))
        var l48 = S32(0)
        while ((l48) < (S32(2))): 
            dsp.rec24[l48] = F64(0.0)
            l48 = (l48) + (S32(1))
        var l49 = S32(0)
        while ((l49) < (S32(64))): 
            dsp.vec23[l49] = F64(0.0)
            l49 = (l49) + (S32(1))
        var l50 = S32(0)
        while ((l50) < (S32(3))): 
            dsp.rec27[l50] = F64(0.0)
            l50 = (l50) + (S32(1))
        var l51 = S32(0)
        while ((l51) < (S32(2))): 
            dsp.rec26[l51] = F64(0.0)
            l51 = (l51) + (S32(1))
        var l52 = S32(0)
        while ((l52) < (S32(128))): 
            dsp.vec24[l52] = F64(0.0)
            l52 = (l52) + (S32(1))
        var l53 = S32(0)
        while ((l53) < (S32(3))): 
            dsp.rec29[l53] = F64(0.0)
            l53 = (l53) + (S32(1))
        var l54 = S32(0)
        while ((l54) < (S32(2))): 
            dsp.rec28[l54] = F64(0.0)
            l54 = (l54) + (S32(1))
        var l55 = S32(0)
        while ((l55) < (S32(128))): 
            dsp.vec25[l55] = F64(0.0)
            l55 = (l55) + (S32(1))
        var l56 = S32(0)
        while ((l56) < (S32(3))): 
            dsp.rec31[l56] = F64(0.0)
            l56 = (l56) + (S32(1))
        var l57 = S32(0)
        while ((l57) < (S32(2))): 
            dsp.rec30[l57] = F64(0.0)
            l57 = (l57) + (S32(1))
        var l58 = S32(0)
        while ((l58) < (S32(256))): 
            dsp.vec26[l58] = F64(0.0)
            l58 = (l58) + (S32(1))
        var l59 = S32(0)
        while ((l59) < (S32(3))): 
            dsp.rec33[l59] = F64(0.0)
            l59 = (l59) + (S32(1))
        var l60 = S32(0)
        while ((l60) < (S32(2))): 
            dsp.rec32[l60] = F64(0.0)
            l60 = (l60) + (S32(1))
        var l61 = S32(0)
        while ((l61) < (S32(256))): 
            dsp.vec27[l61] = F64(0.0)
            l61 = (l61) + (S32(1))
        var l62 = S32(0)
        while ((l62) < (S32(3))): 
            dsp.rec35[l62] = F64(0.0)
            l62 = (l62) + (S32(1))
        var l63 = S32(0)
        while ((l63) < (S32(2))): 
            dsp.rec34[l63] = F64(0.0)
            l63 = (l63) + (S32(1))
        var l64 = S32(0)
        while ((l64) < (S32(1024))): 
            dsp.vec28[l64] = F64(0.0)
            l64 = (l64) + (S32(1))
        var l65 = S32(0)
        while ((l65) < (S32(3))): 
            dsp.rec37[l65] = F64(0.0)
            l65 = (l65) + (S32(1))
        var l66 = S32(0)
        while ((l66) < (S32(2))): 
            dsp.rec36[l66] = F64(0.0)
            l66 = (l66) + (S32(1))
        var l67 = S32(0)
        while ((l67) < (S32(1024))): 
            dsp.vec29[l67] = F64(0.0)
            l67 = (l67) + (S32(1))
        var l68 = S32(0)
        while ((l68) < (S32(3))): 
            dsp.rec39[l68] = F64(0.0)
            l68 = (l68) + (S32(1))
        var l69 = S32(0)
        while ((l69) < (S32(2))): 
            dsp.rec38[l69] = F64(0.0)
            l69 = (l69) + (S32(1))
        var l70 = S32(0)
        while ((l70) < (S32(64))): 
            dsp.vec30[l70] = F64(0.0)
            l70 = (l70) + (S32(1))
        var l71 = S32(0)
        while ((l71) < (S32(3))): 
            dsp.rec41[l71] = F64(0.0)
            l71 = (l71) + (S32(1))
        var l72 = S32(0)
        while ((l72) < (S32(2))): 
            dsp.rec40[l72] = F64(0.0)
            l72 = (l72) + (S32(1))
        var l73 = S32(0)
        while ((l73) < (S32(64))): 
            dsp.vec31[l73] = F64(0.0)
            l73 = (l73) + (S32(1))
        var l74 = S32(0)
        while ((l74) < (S32(3))): 
            dsp.rec43[l74] = F64(0.0)
            l74 = (l74) + (S32(1))
        var l75 = S32(0)
        while ((l75) < (S32(2))): 
            dsp.rec42[l75] = F64(0.0)
            l75 = (l75) + (S32(1))
        var l76 = S32(0)
        while ((l76) < (S32(64))): 
            dsp.vec32[l76] = F64(0.0)
            l76 = (l76) + (S32(1))
        var l77 = S32(0)
        while ((l77) < (S32(3))): 
            dsp.rec45[l77] = F64(0.0)
            l77 = (l77) + (S32(1))
        var l78 = S32(0)
        while ((l78) < (S32(2))): 
            dsp.rec44[l78] = F64(0.0)
            l78 = (l78) + (S32(1))
        var l79 = S32(0)
        while ((l79) < (S32(64))): 
            dsp.vec33[l79] = F64(0.0)
            l79 = (l79) + (S32(1))
        var l80 = S32(0)
        while ((l80) < (S32(3))): 
            dsp.rec47[l80] = F64(0.0)
            l80 = (l80) + (S32(1))
        var l81 = S32(0)
        while ((l81) < (S32(2))): 
            dsp.rec46[l81] = F64(0.0)
            l81 = (l81) + (S32(1))
        var l82 = S32(0)
        while ((l82) < (S32(128))): 
            dsp.vec34[l82] = F64(0.0)
            l82 = (l82) + (S32(1))
        var l83 = S32(0)
        while ((l83) < (S32(3))): 
            dsp.rec49[l83] = F64(0.0)
            l83 = (l83) + (S32(1))
        var l84 = S32(0)
        while ((l84) < (S32(2))): 
            dsp.rec48[l84] = F64(0.0)
            l84 = (l84) + (S32(1))
        var l85 = S32(0)
        while ((l85) < (S32(128))): 
            dsp.vec35[l85] = F64(0.0)
            l85 = (l85) + (S32(1))
        var l86 = S32(0)
        while ((l86) < (S32(3))): 
            dsp.rec51[l86] = F64(0.0)
            l86 = (l86) + (S32(1))
        var l87 = S32(0)
        while ((l87) < (S32(2))): 
            dsp.rec50[l87] = F64(0.0)
            l87 = (l87) + (S32(1))
        var l88 = S32(0)
        while ((l88) < (S32(256))): 
            dsp.vec36[l88] = F64(0.0)
            l88 = (l88) + (S32(1))
        var l89 = S32(0)
        while ((l89) < (S32(3))): 
            dsp.rec53[l89] = F64(0.0)
            l89 = (l89) + (S32(1))
        var l90 = S32(0)
        while ((l90) < (S32(2))): 
            dsp.rec52[l90] = F64(0.0)
            l90 = (l90) + (S32(1))
        var l91 = S32(0)
        while ((l91) < (S32(256))): 
            dsp.vec37[l91] = F64(0.0)
            l91 = (l91) + (S32(1))
        var l92 = S32(0)
        while ((l92) < (S32(3))): 
            dsp.rec55[l92] = F64(0.0)
            l92 = (l92) + (S32(1))
        var l93 = S32(0)
        while ((l93) < (S32(2))): 
            dsp.rec54[l93] = F64(0.0)
            l93 = (l93) + (S32(1))
        var l94 = S32(0)
        while ((l94) < (S32(1024))): 
            dsp.vec38[l94] = F64(0.0)
            l94 = (l94) + (S32(1))
        var l95 = S32(0)
        while ((l95) < (S32(3))): 
            dsp.rec57[l95] = F64(0.0)
            l95 = (l95) + (S32(1))
        var l96 = S32(0)
        while ((l96) < (S32(2))): 
            dsp.rec56[l96] = F64(0.0)
            l96 = (l96) + (S32(1))
        var l97 = S32(0)
        while ((l97) < (S32(1024))): 
            dsp.vec39[l97] = F64(0.0)
            l97 = (l97) + (S32(1))
        var l98 = S32(0)
        while ((l98) < (S32(3))): 
            dsp.rec59[l98] = F64(0.0)
            l98 = (l98) + (S32(1))
        var l99 = S32(0)
        while ((l99) < (S32(2))): 
            dsp.rec58[l99] = F64(0.0)
            l99 = (l99) + (S32(1))
        var l100 = S32(0)
        while ((l100) < (S32(64))): 
            dsp.vec40[l100] = F64(0.0)
            l100 = (l100) + (S32(1))
        var l101 = S32(0)
        while ((l101) < (S32(3))): 
            dsp.rec61[l101] = F64(0.0)
            l101 = (l101) + (S32(1))
        var l102 = S32(0)
        while ((l102) < (S32(2))): 
            dsp.rec60[l102] = F64(0.0)
            l102 = (l102) + (S32(1))
        var l103 = S32(0)
        while ((l103) < (S32(64))): 
            dsp.vec41[l103] = F64(0.0)
            l103 = (l103) + (S32(1))
        var l104 = S32(0)
        while ((l104) < (S32(3))): 
            dsp.rec63[l104] = F64(0.0)
            l104 = (l104) + (S32(1))
        var l105 = S32(0)
        while ((l105) < (S32(2))): 
            dsp.rec62[l105] = F64(0.0)
            l105 = (l105) + (S32(1))
        var l106 = S32(0)
        while ((l106) < (S32(64))): 
            dsp.vec42[l106] = F64(0.0)
            l106 = (l106) + (S32(1))
        var l107 = S32(0)
        while ((l107) < (S32(3))): 
            dsp.rec65[l107] = F64(0.0)
            l107 = (l107) + (S32(1))
        var l108 = S32(0)
        while ((l108) < (S32(2))): 
            dsp.rec64[l108] = F64(0.0)
            l108 = (l108) + (S32(1))
        var l109 = S32(0)
        while ((l109) < (S32(64))): 
            dsp.vec43[l109] = F64(0.0)
            l109 = (l109) + (S32(1))
        var l110 = S32(0)
        while ((l110) < (S32(3))): 
            dsp.rec67[l110] = F64(0.0)
            l110 = (l110) + (S32(1))
        var l111 = S32(0)
        while ((l111) < (S32(2))): 
            dsp.rec66[l111] = F64(0.0)
            l111 = (l111) + (S32(1))
        var l112 = S32(0)
        while ((l112) < (S32(128))): 
            dsp.vec44[l112] = F64(0.0)
            l112 = (l112) + (S32(1))
        var l113 = S32(0)
        while ((l113) < (S32(3))): 
            dsp.rec69[l113] = F64(0.0)
            l113 = (l113) + (S32(1))
        var l114 = S32(0)
        while ((l114) < (S32(2))): 
            dsp.rec68[l114] = F64(0.0)
            l114 = (l114) + (S32(1))
        var l115 = S32(0)
        while ((l115) < (S32(128))): 
            dsp.vec45[l115] = F64(0.0)
            l115 = (l115) + (S32(1))
        var l116 = S32(0)
        while ((l116) < (S32(3))): 
            dsp.rec71[l116] = F64(0.0)
            l116 = (l116) + (S32(1))
        var l117 = S32(0)
        while ((l117) < (S32(2))): 
            dsp.rec70[l117] = F64(0.0)
            l117 = (l117) + (S32(1))
        var l118 = S32(0)
        while ((l118) < (S32(256))): 
            dsp.vec46[l118] = F64(0.0)
            l118 = (l118) + (S32(1))
        var l119 = S32(0)
        while ((l119) < (S32(3))): 
            dsp.rec73[l119] = F64(0.0)
            l119 = (l119) + (S32(1))
        var l120 = S32(0)
        while ((l120) < (S32(2))): 
            dsp.rec72[l120] = F64(0.0)
            l120 = (l120) + (S32(1))
        var l121 = S32(0)
        while ((l121) < (S32(256))): 
            dsp.vec47[l121] = F64(0.0)
            l121 = (l121) + (S32(1))
        var l122 = S32(0)
        while ((l122) < (S32(3))): 
            dsp.rec75[l122] = F64(0.0)
            l122 = (l122) + (S32(1))
        var l123 = S32(0)
        while ((l123) < (S32(2))): 
            dsp.rec74[l123] = F64(0.0)
            l123 = (l123) + (S32(1))
        var l124 = S32(0)
        while ((l124) < (S32(1024))): 
            dsp.vec48[l124] = F64(0.0)
            l124 = (l124) + (S32(1))
        var l125 = S32(0)
        while ((l125) < (S32(3))): 
            dsp.rec77[l125] = F64(0.0)
            l125 = (l125) + (S32(1))
        var l126 = S32(0)
        while ((l126) < (S32(2))): 
            dsp.rec76[l126] = F64(0.0)
            l126 = (l126) + (S32(1))
        var l127 = S32(0)
        while ((l127) < (S32(1024))): 
            dsp.vec49[l127] = F64(0.0)
            l127 = (l127) + (S32(1))
        var l128 = S32(0)
        while ((l128) < (S32(3))): 
            dsp.rec79[l128] = F64(0.0)
            l128 = (l128) + (S32(1))
        var l129 = S32(0)
        while ((l129) < (S32(2))): 
            dsp.rec78[l129] = F64(0.0)
            l129 = (l129) + (S32(1))
        var l130 = S32(0)
        while ((l130) < (S32(64))): 
            dsp.vec50[l130] = F64(0.0)
            l130 = (l130) + (S32(1))
        var l131 = S32(0)
        while ((l131) < (S32(3))): 
            dsp.rec81[l131] = F64(0.0)
            l131 = (l131) + (S32(1))
        var l132 = S32(0)
        while ((l132) < (S32(2))): 
            dsp.rec80[l132] = F64(0.0)
            l132 = (l132) + (S32(1))
        var l133 = S32(0)
        while ((l133) < (S32(64))): 
            dsp.vec51[l133] = F64(0.0)
            l133 = (l133) + (S32(1))
        var l134 = S32(0)
        while ((l134) < (S32(3))): 
            dsp.rec83[l134] = F64(0.0)
            l134 = (l134) + (S32(1))
        var l135 = S32(0)
        while ((l135) < (S32(2))): 
            dsp.rec82[l135] = F64(0.0)
            l135 = (l135) + (S32(1))
        var l136 = S32(0)
        while ((l136) < (S32(64))): 
            dsp.vec52[l136] = F64(0.0)
            l136 = (l136) + (S32(1))
        var l137 = S32(0)
        while ((l137) < (S32(3))): 
            dsp.rec85[l137] = F64(0.0)
            l137 = (l137) + (S32(1))
        var l138 = S32(0)
        while ((l138) < (S32(2))): 
            dsp.rec84[l138] = F64(0.0)
            l138 = (l138) + (S32(1))
        var l139 = S32(0)
        while ((l139) < (S32(64))): 
            dsp.vec53[l139] = F64(0.0)
            l139 = (l139) + (S32(1))
        var l140 = S32(0)
        while ((l140) < (S32(3))): 
            dsp.rec87[l140] = F64(0.0)
            l140 = (l140) + (S32(1))
        var l141 = S32(0)
        while ((l141) < (S32(2))): 
            dsp.rec86[l141] = F64(0.0)
            l141 = (l141) + (S32(1))
        var l142 = S32(0)
        while ((l142) < (S32(128))): 
            dsp.vec54[l142] = F64(0.0)
            l142 = (l142) + (S32(1))
        var l143 = S32(0)
        while ((l143) < (S32(3))): 
            dsp.rec89[l143] = F64(0.0)
            l143 = (l143) + (S32(1))
        var l144 = S32(0)
        while ((l144) < (S32(2))): 
            dsp.rec88[l144] = F64(0.0)
            l144 = (l144) + (S32(1))
        var l145 = S32(0)
        while ((l145) < (S32(128))): 
            dsp.vec55[l145] = F64(0.0)
            l145 = (l145) + (S32(1))
        var l146 = S32(0)
        while ((l146) < (S32(3))): 
            dsp.rec91[l146] = F64(0.0)
            l146 = (l146) + (S32(1))
        var l147 = S32(0)
        while ((l147) < (S32(2))): 
            dsp.rec90[l147] = F64(0.0)
            l147 = (l147) + (S32(1))
        var l148 = S32(0)
        while ((l148) < (S32(256))): 
            dsp.vec56[l148] = F64(0.0)
            l148 = (l148) + (S32(1))
        var l149 = S32(0)
        while ((l149) < (S32(3))): 
            dsp.rec93[l149] = F64(0.0)
            l149 = (l149) + (S32(1))
        var l150 = S32(0)
        while ((l150) < (S32(2))): 
            dsp.rec92[l150] = F64(0.0)
            l150 = (l150) + (S32(1))
        var l151 = S32(0)
        while ((l151) < (S32(256))): 
            dsp.vec57[l151] = F64(0.0)
            l151 = (l151) + (S32(1))
        var l152 = S32(0)
        while ((l152) < (S32(3))): 
            dsp.rec95[l152] = F64(0.0)
            l152 = (l152) + (S32(1))
        var l153 = S32(0)
        while ((l153) < (S32(2))): 
            dsp.rec94[l153] = F64(0.0)
            l153 = (l153) + (S32(1))
        var l154 = S32(0)
        while ((l154) < (S32(1024))): 
            dsp.vec58[l154] = F64(0.0)
            l154 = (l154) + (S32(1))
        var l155 = S32(0)
        while ((l155) < (S32(3))): 
            dsp.rec97[l155] = F64(0.0)
            l155 = (l155) + (S32(1))
        var l156 = S32(0)
        while ((l156) < (S32(2))): 
            dsp.rec96[l156] = F64(0.0)
            l156 = (l156) + (S32(1))
        var l157 = S32(0)
        while ((l157) < (S32(1024))): 
            dsp.vec59[l157] = F64(0.0)
            l157 = (l157) + (S32(1))
        var l158 = S32(0)
        while ((l158) < (S32(3))): 
            dsp.rec99[l158] = F64(0.0)
            l158 = (l158) + (S32(1))
        var l159 = S32(0)
        while ((l159) < (S32(2))): 
            dsp.rec98[l159] = F64(0.0)
            l159 = (l159) + (S32(1))
        var l160 = S32(0)
        while ((l160) < (S32(64))): 
            dsp.vec60[l160] = F64(0.0)
            l160 = (l160) + (S32(1))
        var l161 = S32(0)
        while ((l161) < (S32(3))): 
            dsp.rec101[l161] = F64(0.0)
            l161 = (l161) + (S32(1))
        var l162 = S32(0)
        while ((l162) < (S32(2))): 
            dsp.rec100[l162] = F64(0.0)
            l162 = (l162) + (S32(1))
        var l163 = S32(0)
        while ((l163) < (S32(64))): 
            dsp.vec61[l163] = F64(0.0)
            l163 = (l163) + (S32(1))
        var l164 = S32(0)
        while ((l164) < (S32(3))): 
            dsp.rec103[l164] = F64(0.0)
            l164 = (l164) + (S32(1))
        var l165 = S32(0)
        while ((l165) < (S32(2))): 
            dsp.rec102[l165] = F64(0.0)
            l165 = (l165) + (S32(1))
        var l166 = S32(0)
        while ((l166) < (S32(64))): 
            dsp.vec62[l166] = F64(0.0)
            l166 = (l166) + (S32(1))
        var l167 = S32(0)
        while ((l167) < (S32(3))): 
            dsp.rec105[l167] = F64(0.0)
            l167 = (l167) + (S32(1))
        var l168 = S32(0)
        while ((l168) < (S32(2))): 
            dsp.rec104[l168] = F64(0.0)
            l168 = (l168) + (S32(1))
        var l169 = S32(0)
        while ((l169) < (S32(64))): 
            dsp.vec63[l169] = F64(0.0)
            l169 = (l169) + (S32(1))
        var l170 = S32(0)
        while ((l170) < (S32(3))): 
            dsp.rec107[l170] = F64(0.0)
            l170 = (l170) + (S32(1))
        var l171 = S32(0)
        while ((l171) < (S32(2))): 
            dsp.rec106[l171] = F64(0.0)
            l171 = (l171) + (S32(1))
        var l172 = S32(0)
        while ((l172) < (S32(128))): 
            dsp.vec64[l172] = F64(0.0)
            l172 = (l172) + (S32(1))
        var l173 = S32(0)
        while ((l173) < (S32(3))): 
            dsp.rec109[l173] = F64(0.0)
            l173 = (l173) + (S32(1))
        var l174 = S32(0)
        while ((l174) < (S32(2))): 
            dsp.rec108[l174] = F64(0.0)
            l174 = (l174) + (S32(1))
        var l175 = S32(0)
        while ((l175) < (S32(128))): 
            dsp.vec65[l175] = F64(0.0)
            l175 = (l175) + (S32(1))
        var l176 = S32(0)
        while ((l176) < (S32(3))): 
            dsp.rec111[l176] = F64(0.0)
            l176 = (l176) + (S32(1))
        var l177 = S32(0)
        while ((l177) < (S32(2))): 
            dsp.rec110[l177] = F64(0.0)
            l177 = (l177) + (S32(1))
        var l178 = S32(0)
        while ((l178) < (S32(256))): 
            dsp.vec66[l178] = F64(0.0)
            l178 = (l178) + (S32(1))
        var l179 = S32(0)
        while ((l179) < (S32(3))): 
            dsp.rec113[l179] = F64(0.0)
            l179 = (l179) + (S32(1))
        var l180 = S32(0)
        while ((l180) < (S32(2))): 
            dsp.rec112[l180] = F64(0.0)
            l180 = (l180) + (S32(1))
        var l181 = S32(0)
        while ((l181) < (S32(256))): 
            dsp.vec67[l181] = F64(0.0)
            l181 = (l181) + (S32(1))
        var l182 = S32(0)
        while ((l182) < (S32(3))): 
            dsp.rec115[l182] = F64(0.0)
            l182 = (l182) + (S32(1))
        var l183 = S32(0)
        while ((l183) < (S32(2))): 
            dsp.rec114[l183] = F64(0.0)
            l183 = (l183) + (S32(1))
        var l184 = S32(0)
        while ((l184) < (S32(1024))): 
            dsp.vec68[l184] = F64(0.0)
            l184 = (l184) + (S32(1))
        var l185 = S32(0)
        while ((l185) < (S32(3))): 
            dsp.rec117[l185] = F64(0.0)
            l185 = (l185) + (S32(1))
        var l186 = S32(0)
        while ((l186) < (S32(2))): 
            dsp.rec116[l186] = F64(0.0)
            l186 = (l186) + (S32(1))
        var l187 = S32(0)
        while ((l187) < (S32(1024))): 
            dsp.vec69[l187] = F64(0.0)
            l187 = (l187) + (S32(1))
        var l188 = S32(0)
        while ((l188) < (S32(3))): 
            dsp.rec119[l188] = F64(0.0)
            l188 = (l188) + (S32(1))
        var l189 = S32(0)
        while ((l189) < (S32(2))): 
            dsp.rec118[l189] = F64(0.0)
            l189 = (l189) + (S32(1))
        var l190 = S32(0)
        while ((l190) < (S32(64))): 
            dsp.vec70[l190] = F64(0.0)
            l190 = (l190) + (S32(1))
        var l191 = S32(0)
        while ((l191) < (S32(3))): 
            dsp.rec121[l191] = F64(0.0)
            l191 = (l191) + (S32(1))
        var l192 = S32(0)
        while ((l192) < (S32(2))): 
            dsp.rec120[l192] = F64(0.0)
            l192 = (l192) + (S32(1))
        var l193 = S32(0)
        while ((l193) < (S32(64))): 
            dsp.vec71[l193] = F64(0.0)
            l193 = (l193) + (S32(1))
        var l194 = S32(0)
        while ((l194) < (S32(3))): 
            dsp.rec123[l194] = F64(0.0)
            l194 = (l194) + (S32(1))
        var l195 = S32(0)
        while ((l195) < (S32(2))): 
            dsp.rec122[l195] = F64(0.0)
            l195 = (l195) + (S32(1))
        var l196 = S32(0)
        while ((l196) < (S32(64))): 
            dsp.vec72[l196] = F64(0.0)
            l196 = (l196) + (S32(1))
        var l197 = S32(0)
        while ((l197) < (S32(3))): 
            dsp.rec125[l197] = F64(0.0)
            l197 = (l197) + (S32(1))
        var l198 = S32(0)
        while ((l198) < (S32(2))): 
            dsp.rec124[l198] = F64(0.0)
            l198 = (l198) + (S32(1))
        var l199 = S32(0)
        while ((l199) < (S32(64))): 
            dsp.vec73[l199] = F64(0.0)
            l199 = (l199) + (S32(1))
        var l200 = S32(0)
        while ((l200) < (S32(3))): 
            dsp.rec127[l200] = F64(0.0)
            l200 = (l200) + (S32(1))
        var l201 = S32(0)
        while ((l201) < (S32(2))): 
            dsp.rec126[l201] = F64(0.0)
            l201 = (l201) + (S32(1))
        var l202 = S32(0)
        while ((l202) < (S32(128))): 
            dsp.vec74[l202] = F64(0.0)
            l202 = (l202) + (S32(1))
        var l203 = S32(0)
        while ((l203) < (S32(3))): 
            dsp.rec129[l203] = F64(0.0)
            l203 = (l203) + (S32(1))
        var l204 = S32(0)
        while ((l204) < (S32(2))): 
            dsp.rec128[l204] = F64(0.0)
            l204 = (l204) + (S32(1))
        var l205 = S32(0)
        while ((l205) < (S32(128))): 
            dsp.vec75[l205] = F64(0.0)
            l205 = (l205) + (S32(1))
        var l206 = S32(0)
        while ((l206) < (S32(3))): 
            dsp.rec131[l206] = F64(0.0)
            l206 = (l206) + (S32(1))
        var l207 = S32(0)
        while ((l207) < (S32(2))): 
            dsp.rec130[l207] = F64(0.0)
            l207 = (l207) + (S32(1))
        var l208 = S32(0)
        while ((l208) < (S32(256))): 
            dsp.vec76[l208] = F64(0.0)
            l208 = (l208) + (S32(1))
        var l209 = S32(0)
        while ((l209) < (S32(3))): 
            dsp.rec133[l209] = F64(0.0)
            l209 = (l209) + (S32(1))
        var l210 = S32(0)
        while ((l210) < (S32(2))): 
            dsp.rec132[l210] = F64(0.0)
            l210 = (l210) + (S32(1))
        var l211 = S32(0)
        while ((l211) < (S32(256))): 
            dsp.vec77[l211] = F64(0.0)
            l211 = (l211) + (S32(1))
        var l212 = S32(0)
        while ((l212) < (S32(3))): 
            dsp.rec135[l212] = F64(0.0)
            l212 = (l212) + (S32(1))
        var l213 = S32(0)
        while ((l213) < (S32(2))): 
            dsp.rec134[l213] = F64(0.0)
            l213 = (l213) + (S32(1))
        var l214 = S32(0)
        while ((l214) < (S32(1024))): 
            dsp.vec78[l214] = F64(0.0)
            l214 = (l214) + (S32(1))
        var l215 = S32(0)
        while ((l215) < (S32(3))): 
            dsp.rec137[l215] = F64(0.0)
            l215 = (l215) + (S32(1))
        var l216 = S32(0)
        while ((l216) < (S32(2))): 
            dsp.rec136[l216] = F64(0.0)
            l216 = (l216) + (S32(1))
        var l217 = S32(0)
        while ((l217) < (S32(1024))): 
            dsp.vec79[l217] = F64(0.0)
            l217 = (l217) + (S32(1))
        var l218 = S32(0)
        while ((l218) < (S32(3))): 
            dsp.rec139[l218] = F64(0.0)
            l218 = (l218) + (S32(1))
        var l219 = S32(0)
        while ((l219) < (S32(2))): 
            dsp.rec138[l219] = F64(0.0)
            l219 = (l219) + (S32(1))
        var l220 = S32(0)
        while ((l220) < (S32(64))): 
            dsp.vec80[l220] = F64(0.0)
            l220 = (l220) + (S32(1))
        var l221 = S32(0)
        while ((l221) < (S32(3))): 
            dsp.rec141[l221] = F64(0.0)
            l221 = (l221) + (S32(1))
        var l222 = S32(0)
        while ((l222) < (S32(2))): 
            dsp.rec140[l222] = F64(0.0)
            l222 = (l222) + (S32(1))
        var l223 = S32(0)
        while ((l223) < (S32(64))): 
            dsp.vec81[l223] = F64(0.0)
            l223 = (l223) + (S32(1))
        var l224 = S32(0)
        while ((l224) < (S32(3))): 
            dsp.rec143[l224] = F64(0.0)
            l224 = (l224) + (S32(1))
        var l225 = S32(0)
        while ((l225) < (S32(2))): 
            dsp.rec142[l225] = F64(0.0)
            l225 = (l225) + (S32(1))
        var l226 = S32(0)
        while ((l226) < (S32(64))): 
            dsp.vec82[l226] = F64(0.0)
            l226 = (l226) + (S32(1))
        var l227 = S32(0)
        while ((l227) < (S32(3))): 
            dsp.rec145[l227] = F64(0.0)
            l227 = (l227) + (S32(1))
        var l228 = S32(0)
        while ((l228) < (S32(2))): 
            dsp.rec144[l228] = F64(0.0)
            l228 = (l228) + (S32(1))
        var l229 = S32(0)
        while ((l229) < (S32(64))): 
            dsp.vec83[l229] = F64(0.0)
            l229 = (l229) + (S32(1))
        var l230 = S32(0)
        while ((l230) < (S32(3))): 
            dsp.rec147[l230] = F64(0.0)
            l230 = (l230) + (S32(1))
        var l231 = S32(0)
        while ((l231) < (S32(2))): 
            dsp.rec146[l231] = F64(0.0)
            l231 = (l231) + (S32(1))
        var l232 = S32(0)
        while ((l232) < (S32(128))): 
            dsp.vec84[l232] = F64(0.0)
            l232 = (l232) + (S32(1))
        var l233 = S32(0)
        while ((l233) < (S32(3))): 
            dsp.rec149[l233] = F64(0.0)
            l233 = (l233) + (S32(1))
        var l234 = S32(0)
        while ((l234) < (S32(2))): 
            dsp.rec148[l234] = F64(0.0)
            l234 = (l234) + (S32(1))
        var l235 = S32(0)
        while ((l235) < (S32(128))): 
            dsp.vec85[l235] = F64(0.0)
            l235 = (l235) + (S32(1))
        var l236 = S32(0)
        while ((l236) < (S32(3))): 
            dsp.rec151[l236] = F64(0.0)
            l236 = (l236) + (S32(1))
        var l237 = S32(0)
        while ((l237) < (S32(2))): 
            dsp.rec150[l237] = F64(0.0)
            l237 = (l237) + (S32(1))
        var l238 = S32(0)
        while ((l238) < (S32(256))): 
            dsp.vec86[l238] = F64(0.0)
            l238 = (l238) + (S32(1))
        var l239 = S32(0)
        while ((l239) < (S32(3))): 
            dsp.rec153[l239] = F64(0.0)
            l239 = (l239) + (S32(1))
        var l240 = S32(0)
        while ((l240) < (S32(2))): 
            dsp.rec152[l240] = F64(0.0)
            l240 = (l240) + (S32(1))
        var l241 = S32(0)
        while ((l241) < (S32(256))): 
            dsp.vec87[l241] = F64(0.0)
            l241 = (l241) + (S32(1))
        var l242 = S32(0)
        while ((l242) < (S32(3))): 
            dsp.rec155[l242] = F64(0.0)
            l242 = (l242) + (S32(1))
        var l243 = S32(0)
        while ((l243) < (S32(2))): 
            dsp.rec154[l243] = F64(0.0)
            l243 = (l243) + (S32(1))
        var l244 = S32(0)
        while ((l244) < (S32(1024))): 
            dsp.vec88[l244] = F64(0.0)
            l244 = (l244) + (S32(1))
        var l245 = S32(0)
        while ((l245) < (S32(3))): 
            dsp.rec157[l245] = F64(0.0)
            l245 = (l245) + (S32(1))
        var l246 = S32(0)
        while ((l246) < (S32(2))): 
            dsp.rec156[l246] = F64(0.0)
            l246 = (l246) + (S32(1))
        var l247 = S32(0)
        while ((l247) < (S32(1024))): 
            dsp.vec89[l247] = F64(0.0)
            l247 = (l247) + (S32(1))
        var l248 = S32(0)
        while ((l248) < (S32(3))): 
            dsp.rec159[l248] = F64(0.0)
            l248 = (l248) + (S32(1))
        var l249 = S32(0)
        while ((l249) < (S32(2))): 
            dsp.rec158[l249] = F64(0.0)
            l249 = (l249) + (S32(1))
        var l250 = S32(0)
        while ((l250) < (S32(64))): 
            dsp.vec90[l250] = F64(0.0)
            l250 = (l250) + (S32(1))
        var l251 = S32(0)
        while ((l251) < (S32(3))): 
            dsp.rec161[l251] = F64(0.0)
            l251 = (l251) + (S32(1))
        var l252 = S32(0)
        while ((l252) < (S32(2))): 
            dsp.rec160[l252] = F64(0.0)
            l252 = (l252) + (S32(1))
        var l253 = S32(0)
        while ((l253) < (S32(64))): 
            dsp.vec91[l253] = F64(0.0)
            l253 = (l253) + (S32(1))
        var l254 = S32(0)
        while ((l254) < (S32(3))): 
            dsp.rec163[l254] = F64(0.0)
            l254 = (l254) + (S32(1))
        var l255 = S32(0)
        while ((l255) < (S32(2))): 
            dsp.rec162[l255] = F64(0.0)
            l255 = (l255) + (S32(1))
        var l256 = S32(0)
        while ((l256) < (S32(64))): 
            dsp.vec92[l256] = F64(0.0)
            l256 = (l256) + (S32(1))
        var l257 = S32(0)
        while ((l257) < (S32(3))): 
            dsp.rec165[l257] = F64(0.0)
            l257 = (l257) + (S32(1))
        var l258 = S32(0)
        while ((l258) < (S32(2))): 
            dsp.rec164[l258] = F64(0.0)
            l258 = (l258) + (S32(1))
        var l259 = S32(0)
        while ((l259) < (S32(64))): 
            dsp.vec93[l259] = F64(0.0)
            l259 = (l259) + (S32(1))
        var l260 = S32(0)
        while ((l260) < (S32(3))): 
            dsp.rec167[l260] = F64(0.0)
            l260 = (l260) + (S32(1))
        var l261 = S32(0)
        while ((l261) < (S32(2))): 
            dsp.rec166[l261] = F64(0.0)
            l261 = (l261) + (S32(1))
        var l262 = S32(0)
        while ((l262) < (S32(128))): 
            dsp.vec94[l262] = F64(0.0)
            l262 = (l262) + (S32(1))
        var l263 = S32(0)
        while ((l263) < (S32(3))): 
            dsp.rec169[l263] = F64(0.0)
            l263 = (l263) + (S32(1))
        var l264 = S32(0)
        while ((l264) < (S32(2))): 
            dsp.rec168[l264] = F64(0.0)
            l264 = (l264) + (S32(1))
        var l265 = S32(0)
        while ((l265) < (S32(128))): 
            dsp.vec95[l265] = F64(0.0)
            l265 = (l265) + (S32(1))
        var l266 = S32(0)
        while ((l266) < (S32(3))): 
            dsp.rec171[l266] = F64(0.0)
            l266 = (l266) + (S32(1))
        var l267 = S32(0)
        while ((l267) < (S32(2))): 
            dsp.rec170[l267] = F64(0.0)
            l267 = (l267) + (S32(1))
        var l268 = S32(0)
        while ((l268) < (S32(256))): 
            dsp.vec96[l268] = F64(0.0)
            l268 = (l268) + (S32(1))
        var l269 = S32(0)
        while ((l269) < (S32(3))): 
            dsp.rec173[l269] = F64(0.0)
            l269 = (l269) + (S32(1))
        var l270 = S32(0)
        while ((l270) < (S32(2))): 
            dsp.rec172[l270] = F64(0.0)
            l270 = (l270) + (S32(1))
        var l271 = S32(0)
        while ((l271) < (S32(256))): 
            dsp.vec97[l271] = F64(0.0)
            l271 = (l271) + (S32(1))
        var l272 = S32(0)
        while ((l272) < (S32(3))): 
            dsp.rec175[l272] = F64(0.0)
            l272 = (l272) + (S32(1))
        var l273 = S32(0)
        while ((l273) < (S32(2))): 
            dsp.rec174[l273] = F64(0.0)
            l273 = (l273) + (S32(1))
        var l274 = S32(0)
        while ((l274) < (S32(1024))): 
            dsp.vec98[l274] = F64(0.0)
            l274 = (l274) + (S32(1))
        var l275 = S32(0)
        while ((l275) < (S32(3))): 
            dsp.rec177[l275] = F64(0.0)
            l275 = (l275) + (S32(1))
        var l276 = S32(0)
        while ((l276) < (S32(2))): 
            dsp.rec176[l276] = F64(0.0)
            l276 = (l276) + (S32(1))
        var l277 = S32(0)
        while ((l277) < (S32(1024))): 
            dsp.vec99[l277] = F64(0.0)
            l277 = (l277) + (S32(1))
        var l278 = S32(0)
        while ((l278) < (S32(3))): 
            dsp.rec179[l278] = F64(0.0)
            l278 = (l278) + (S32(1))
        var l279 = S32(0)
        while ((l279) < (S32(2))): 
            dsp.rec178[l279] = F64(0.0)
            l279 = (l279) + (S32(1))
        var l280 = S32(0)
        while ((l280) < (S32(64))): 
            dsp.vec100[l280] = F64(0.0)
            l280 = (l280) + (S32(1))
        var l281 = S32(0)
        while ((l281) < (S32(3))): 
            dsp.rec181[l281] = F64(0.0)
            l281 = (l281) + (S32(1))
        var l282 = S32(0)
        while ((l282) < (S32(2))): 
            dsp.rec180[l282] = F64(0.0)
            l282 = (l282) + (S32(1))
        var l283 = S32(0)
        while ((l283) < (S32(64))): 
            dsp.vec101[l283] = F64(0.0)
            l283 = (l283) + (S32(1))
        var l284 = S32(0)
        while ((l284) < (S32(3))): 
            dsp.rec183[l284] = F64(0.0)
            l284 = (l284) + (S32(1))
        var l285 = S32(0)
        while ((l285) < (S32(2))): 
            dsp.rec182[l285] = F64(0.0)
            l285 = (l285) + (S32(1))
        var l286 = S32(0)
        while ((l286) < (S32(64))): 
            dsp.vec102[l286] = F64(0.0)
            l286 = (l286) + (S32(1))
        var l287 = S32(0)
        while ((l287) < (S32(3))): 
            dsp.rec185[l287] = F64(0.0)
            l287 = (l287) + (S32(1))
        var l288 = S32(0)
        while ((l288) < (S32(2))): 
            dsp.rec184[l288] = F64(0.0)
            l288 = (l288) + (S32(1))
        var l289 = S32(0)
        while ((l289) < (S32(64))): 
            dsp.vec103[l289] = F64(0.0)
            l289 = (l289) + (S32(1))
        var l290 = S32(0)
        while ((l290) < (S32(3))): 
            dsp.rec187[l290] = F64(0.0)
            l290 = (l290) + (S32(1))
        var l291 = S32(0)
        while ((l291) < (S32(2))): 
            dsp.rec186[l291] = F64(0.0)
            l291 = (l291) + (S32(1))
        var l292 = S32(0)
        while ((l292) < (S32(128))): 
            dsp.vec104[l292] = F64(0.0)
            l292 = (l292) + (S32(1))
        var l293 = S32(0)
        while ((l293) < (S32(3))): 
            dsp.rec189[l293] = F64(0.0)
            l293 = (l293) + (S32(1))
        var l294 = S32(0)
        while ((l294) < (S32(2))): 
            dsp.rec188[l294] = F64(0.0)
            l294 = (l294) + (S32(1))
        var l295 = S32(0)
        while ((l295) < (S32(128))): 
            dsp.vec105[l295] = F64(0.0)
            l295 = (l295) + (S32(1))
        var l296 = S32(0)
        while ((l296) < (S32(3))): 
            dsp.rec191[l296] = F64(0.0)
            l296 = (l296) + (S32(1))
        var l297 = S32(0)
        while ((l297) < (S32(2))): 
            dsp.rec190[l297] = F64(0.0)
            l297 = (l297) + (S32(1))
        var l298 = S32(0)
        while ((l298) < (S32(256))): 
            dsp.vec106[l298] = F64(0.0)
            l298 = (l298) + (S32(1))
        var l299 = S32(0)
        while ((l299) < (S32(3))): 
            dsp.rec193[l299] = F64(0.0)
            l299 = (l299) + (S32(1))
        var l300 = S32(0)
        while ((l300) < (S32(2))): 
            dsp.rec192[l300] = F64(0.0)
            l300 = (l300) + (S32(1))
        var l301 = S32(0)
        while ((l301) < (S32(256))): 
            dsp.vec107[l301] = F64(0.0)
            l301 = (l301) + (S32(1))
        var l302 = S32(0)
        while ((l302) < (S32(3))): 
            dsp.rec195[l302] = F64(0.0)
            l302 = (l302) + (S32(1))
        var l303 = S32(0)
        while ((l303) < (S32(2))): 
            dsp.rec194[l303] = F64(0.0)
            l303 = (l303) + (S32(1))
        var l304 = S32(0)
        while ((l304) < (S32(1024))): 
            dsp.vec108[l304] = F64(0.0)
            l304 = (l304) + (S32(1))
        var l305 = S32(0)
        while ((l305) < (S32(3))): 
            dsp.rec197[l305] = F64(0.0)
            l305 = (l305) + (S32(1))
        var l306 = S32(0)
        while ((l306) < (S32(2))): 
            dsp.rec196[l306] = F64(0.0)
            l306 = (l306) + (S32(1))
        var l307 = S32(0)
        while ((l307) < (S32(1024))): 
            dsp.vec109[l307] = F64(0.0)
            l307 = (l307) + (S32(1))
        var l308 = S32(0)
        while ((l308) < (S32(3))): 
            dsp.rec199[l308] = F64(0.0)
            l308 = (l308) + (S32(1))
        var l309 = S32(0)
        while ((l309) < (S32(2))): 
            dsp.rec198[l309] = F64(0.0)
            l309 = (l309) + (S32(1))
        var l310 = S32(0)
        while ((l310) < (S32(64))): 
            dsp.vec110[l310] = F64(0.0)
            l310 = (l310) + (S32(1))
        var l311 = S32(0)
        while ((l311) < (S32(3))): 
            dsp.rec201[l311] = F64(0.0)
            l311 = (l311) + (S32(1))
        var l312 = S32(0)
        while ((l312) < (S32(2))): 
            dsp.rec200[l312] = F64(0.0)
            l312 = (l312) + (S32(1))
        var l313 = S32(0)
        while ((l313) < (S32(64))): 
            dsp.vec111[l313] = F64(0.0)
            l313 = (l313) + (S32(1))
        var l314 = S32(0)
        while ((l314) < (S32(3))): 
            dsp.rec203[l314] = F64(0.0)
            l314 = (l314) + (S32(1))
        var l315 = S32(0)
        while ((l315) < (S32(2))): 
            dsp.rec202[l315] = F64(0.0)
            l315 = (l315) + (S32(1))
        var l316 = S32(0)
        while ((l316) < (S32(64))): 
            dsp.vec112[l316] = F64(0.0)
            l316 = (l316) + (S32(1))
        var l317 = S32(0)
        while ((l317) < (S32(3))): 
            dsp.rec205[l317] = F64(0.0)
            l317 = (l317) + (S32(1))
        var l318 = S32(0)
        while ((l318) < (S32(2))): 
            dsp.rec204[l318] = F64(0.0)
            l318 = (l318) + (S32(1))
        var l319 = S32(0)
        while ((l319) < (S32(64))): 
            dsp.vec113[l319] = F64(0.0)
            l319 = (l319) + (S32(1))
        var l320 = S32(0)
        while ((l320) < (S32(3))): 
            dsp.rec207[l320] = F64(0.0)
            l320 = (l320) + (S32(1))
        var l321 = S32(0)
        while ((l321) < (S32(2))): 
            dsp.rec206[l321] = F64(0.0)
            l321 = (l321) + (S32(1))
        var l322 = S32(0)
        while ((l322) < (S32(128))): 
            dsp.vec114[l322] = F64(0.0)
            l322 = (l322) + (S32(1))
        var l323 = S32(0)
        while ((l323) < (S32(3))): 
            dsp.rec209[l323] = F64(0.0)
            l323 = (l323) + (S32(1))
        var l324 = S32(0)
        while ((l324) < (S32(2))): 
            dsp.rec208[l324] = F64(0.0)
            l324 = (l324) + (S32(1))
        var l325 = S32(0)
        while ((l325) < (S32(1024))): 
            dsp.vec115[l325] = F64(0.0)
            l325 = (l325) + (S32(1))
        var l326 = S32(0)
        while ((l326) < (S32(3))): 
            dsp.rec211[l326] = F64(0.0)
            l326 = (l326) + (S32(1))
        var l327 = S32(0)
        while ((l327) < (S32(2))): 
            dsp.rec210[l327] = F64(0.0)
            l327 = (l327) + (S32(1))
        var l328 = S32(0)
        while ((l328) < (S32(1024))): 
            dsp.vec116[l328] = F64(0.0)
            l328 = (l328) + (S32(1))
        var l329 = S32(0)
        while ((l329) < (S32(3))): 
            dsp.rec213[l329] = F64(0.0)
            l329 = (l329) + (S32(1))
        var l330 = S32(0)
        while ((l330) < (S32(2))): 
            dsp.rec212[l330] = F64(0.0)
            l330 = (l330) + (S32(1))
        var l331 = S32(0)
        while ((l331) < (S32(256))): 
            dsp.vec117[l331] = F64(0.0)
            l331 = (l331) + (S32(1))
        var l332 = S32(0)
        while ((l332) < (S32(3))): 
            dsp.rec215[l332] = F64(0.0)
            l332 = (l332) + (S32(1))
        var l333 = S32(0)
        while ((l333) < (S32(2))): 
            dsp.rec214[l333] = F64(0.0)
            l333 = (l333) + (S32(1))
        var l334 = S32(0)
        while ((l334) < (S32(256))): 
            dsp.vec118[l334] = F64(0.0)
            l334 = (l334) + (S32(1))
        var l335 = S32(0)
        while ((l335) < (S32(3))): 
            dsp.rec217[l335] = F64(0.0)
            l335 = (l335) + (S32(1))
        var l336 = S32(0)
        while ((l336) < (S32(2))): 
            dsp.rec216[l336] = F64(0.0)
            l336 = (l336) + (S32(1))
        var l337 = S32(0)
        while ((l337) < (S32(128))): 
            dsp.vec119[l337] = F64(0.0)
            l337 = (l337) + (S32(1))
        var l338 = S32(0)
        while ((l338) < (S32(3))): 
            dsp.rec219[l338] = F64(0.0)
            l338 = (l338) + (S32(1))
        var l339 = S32(0)
        while ((l339) < (S32(2))): 
            dsp.rec218[l339] = F64(0.0)
            l339 = (l339) + (S32(1))

    @always_inline
    def instance_init(mut dsp, sample_rate: S32) -> None:
        dsp.instance_constants(sample_rate)
        dsp.instance_reset_user_interface()
        dsp.instance_clear()

    @always_inline
    def init(mut dsp, sample_rate: S32) -> None:
        dsp.class_init(sample_rate)
        dsp.instance_init(sample_rate)

    @always_inline
    def get_json(read dsp) -> String:
        return "{\"name\": \"bells\",\"filename\": \"bells.dsp\",\"version\": \"2.85.5\",\"compile_options\": \"-a mojo/bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0\",\"include_pathnames\": [\"/Users/manuelfarzini/Personal/dev/repo/faust/build/share/faust\",\"/usr/local/share/faust\",\"/usr/share/faust\",\"src\",\"/Users/manuelfarzini/Personal/dev/repo/faust/architecture/_bench/src\"],\"size\": 271200,\"inputs\": 0,\"outputs\": 1,\"meta\": [ { \"compile_options\": \"-a mojo/bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0\" },{ \"filename\": \"bells.dsp\" },{ \"name\": \"bells\" }],\"ui\": [ {\"type\": \"vgroup\",\"label\": \"bells\",\"items\": [ {\"type\": \"nentry\",\"label\": \"feedback\",\"varname\": \"fEntry1\",\"shortname\": \"feedback\",\"address\": \"/bells/feedback\",\"init\": 0.989,\"min\": 0,\"max\": 1,\"step\": 0.001},{\"type\": \"nentry\",\"label\": \"pitch0\",\"varname\": \"fEntry9\",\"shortname\": \"pitch0\",\"address\": \"/bells/pitch0\",\"init\": 60,\"min\": 60,\"max\": 160,\"step\": 0.01},{\"type\": \"nentry\",\"label\": \"pitch1\",\"varname\": \"fEntry10\",\"shortname\": \"pitch1\",\"address\": \"/bells/pitch1\",\"init\": 61,\"min\": 60,\"max\": 160,\"step\": 0.01},{\"type\": \"nentry\",\"label\": \"pitch2\",\"varname\": \"fEntry8\",\"shortname\": \"pitch2\",\"address\": \"/bells/pitch2\",\"init\": 62,\"min\": 60,\"max\": 160,\"step\": 0.01},{\"type\": \"nentry\",\"label\": \"pitch3\",\"varname\": \"fEntry7\",\"shortname\": \"pitch3\",\"address\": \"/bells/pitch3\",\"init\": 63,\"min\": 60,\"max\": 160,\"step\": 0.01},{\"type\": \"nentry\",\"label\": \"pitch4\",\"varname\": \"fEntry6\",\"shortname\": \"pitch4\",\"address\": \"/bells/pitch4\",\"init\": 64,\"min\": 60,\"max\": 160,\"step\": 0.01},{\"type\": \"nentry\",\"label\": \"pitch5\",\"varname\": \"fEntry5\",\"shortname\": \"pitch5\",\"address\": \"/bells/pitch5\",\"init\": 65,\"min\": 60,\"max\": 160,\"step\": 0.01},{\"type\": \"nentry\",\"label\": \"pitch6\",\"varname\": \"fEntry4\",\"shortname\": \"pitch6\",\"address\": \"/bells/pitch6\",\"init\": 66,\"min\": 60,\"max\": 160,\"step\": 0.01},{\"type\": \"nentry\",\"label\": \"pitch7\",\"varname\": \"fEntry3\",\"shortname\": \"pitch7\",\"address\": \"/bells/pitch7\",\"init\": 67,\"min\": 60,\"max\": 160,\"step\": 0.01},{\"type\": \"nentry\",\"label\": \"pitch8\",\"varname\": \"fEntry2\",\"shortname\": \"pitch8\",\"address\": \"/bells/pitch8\",\"init\": 68,\"min\": 60,\"max\": 160,\"step\": 0.01},{\"type\": \"nentry\",\"label\": \"pitch9\",\"varname\": \"fEntry0\",\"shortname\": \"pitch9\",\"address\": \"/bells/pitch9\",\"init\": 69,\"min\": 60,\"max\": 160,\"step\": 0.01},{\"type\": \"button\",\"label\": \"play0\",\"varname\": \"fButton8\",\"shortname\": \"play0\",\"address\": \"/bells/play0\"},{\"type\": \"button\",\"label\": \"play1\",\"varname\": \"fButton9\",\"shortname\": \"play1\",\"address\": \"/bells/play1\"},{\"type\": \"button\",\"label\": \"play2\",\"varname\": \"fButton7\",\"shortname\": \"play2\",\"address\": \"/bells/play2\"},{\"type\": \"button\",\"label\": \"play3\",\"varname\": \"fButton6\",\"shortname\": \"play3\",\"address\": \"/bells/play3\"},{\"type\": \"button\",\"label\": \"play4\",\"varname\": \"fButton5\",\"shortname\": \"play4\",\"address\": \"/bells/play4\"},{\"type\": \"button\",\"label\": \"play5\",\"varname\": \"fButton4\",\"shortname\": \"play5\",\"address\": \"/bells/play5\"},{\"type\": \"button\",\"label\": \"play6\",\"varname\": \"fButton3\",\"shortname\": \"play6\",\"address\": \"/bells/play6\"},{\"type\": \"button\",\"label\": \"play7\",\"varname\": \"fButton2\",\"shortname\": \"play7\",\"address\": \"/bells/play7\"},{\"type\": \"button\",\"label\": \"play8\",\"varname\": \"fButton1\",\"shortname\": \"play8\",\"address\": \"/bells/play8\"},{\"type\": \"button\",\"label\": \"play9\",\"varname\": \"fButton0\",\"shortname\": \"play9\",\"address\": \"/bells/play9\"}]}]}"

    @always_inline
    def metadata(read dsp, mut meta: Some[FaustMeta]) -> None:
        meta.declare("compile_options", "-a mojo/bench.mojo -lang mojo -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -double -ftz 0")
        meta.declare("filename", "bells.dsp")
        meta.declare("name", "bells")

    @always_inline
    def build_user_interface(mut dsp, mut ui: Some[FaustGui]) -> None:
        ui.open_vertical_box("bells")
        ui.add_num_entry("feedback", dsp.entry1, FaustFloat(0.989), FaustFloat(0.0), FaustFloat(1.0), FaustFloat(0.001))
        ui.add_num_entry("pitch0", dsp.entry9, FaustFloat(60.0), FaustFloat(60.0), FaustFloat(160.0), FaustFloat(0.01))
        ui.add_num_entry("pitch1", dsp.entry10, FaustFloat(61.0), FaustFloat(60.0), FaustFloat(160.0), FaustFloat(0.01))
        ui.add_num_entry("pitch2", dsp.entry8, FaustFloat(62.0), FaustFloat(60.0), FaustFloat(160.0), FaustFloat(0.01))
        ui.add_num_entry("pitch3", dsp.entry7, FaustFloat(63.0), FaustFloat(60.0), FaustFloat(160.0), FaustFloat(0.01))
        ui.add_num_entry("pitch4", dsp.entry6, FaustFloat(64.0), FaustFloat(60.0), FaustFloat(160.0), FaustFloat(0.01))
        ui.add_num_entry("pitch5", dsp.entry5, FaustFloat(65.0), FaustFloat(60.0), FaustFloat(160.0), FaustFloat(0.01))
        ui.add_num_entry("pitch6", dsp.entry4, FaustFloat(66.0), FaustFloat(60.0), FaustFloat(160.0), FaustFloat(0.01))
        ui.add_num_entry("pitch7", dsp.entry3, FaustFloat(67.0), FaustFloat(60.0), FaustFloat(160.0), FaustFloat(0.01))
        ui.add_num_entry("pitch8", dsp.entry2, FaustFloat(68.0), FaustFloat(60.0), FaustFloat(160.0), FaustFloat(0.01))
        ui.add_num_entry("pitch9", dsp.entry0, FaustFloat(69.0), FaustFloat(60.0), FaustFloat(160.0), FaustFloat(0.01))
        ui.add_button("play0", dsp.button8)
        ui.add_button("play1", dsp.button9)
        ui.add_button("play2", dsp.button7)
        ui.add_button("play3", dsp.button6)
        ui.add_button("play4", dsp.button5)
        ui.add_button("play5", dsp.button4)
        ui.add_button("play6", dsp.button3)
        ui.add_button("play7", dsp.button2)
        ui.add_button("play8", dsp.button1)
        ui.add_button("play9", dsp.button0)
        ui.close_box()

    @always_inline
    def compute[dreal: DType](
        mut dsp,
        var count:      S32,
        var inputs:     ReadStreams[dreal],
        var outputs:    MutaStreams[dreal]
    ) -> None:
        var output0 = outputs[S32(0)]
        var slow0 = pow(F64(2.0), (F64(0.08333333333333333)) * ((F64(dsp.entry0)) + (F64(-69.0))))
        var slow1 = F64(S32(((F64(2509.95888)) * (slow0)) < (dsp.const4)))
        var slow2 = F64(dsp.entry1)
        var slow3 = F64(dsp.button0)
        var i_slow4 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const5) / (slow0))))
        var slow5 = (dsp.const6) * (cos((dsp.const7) * (slow0)))
        var slow6 = pow(F64(2.0), (F64(0.08333333333333333)) * ((F64(dsp.entry2)) + (F64(-69.0))))
        var slow7 = F64(S32(((F64(2509.95888)) * (slow6)) < (dsp.const4)))
        var slow8 = F64(dsp.button1)
        var i_slow9 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const5) / (slow6))))
        var slow10 = (dsp.const6) * (cos((dsp.const7) * (slow6)))
        var slow11 = pow(F64(2.0), (F64(0.08333333333333333)) * ((F64(dsp.entry3)) + (F64(-69.0))))
        var slow12 = F64(S32(((F64(2509.95888)) * (slow11)) < (dsp.const4)))
        var slow13 = F64(dsp.button2)
        var i_slow14 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const5) / (slow11))))
        var slow15 = (dsp.const6) * (cos((dsp.const7) * (slow11)))
        var slow16 = pow(F64(2.0), (F64(0.08333333333333333)) * ((F64(dsp.entry4)) + (F64(-69.0))))
        var slow17 = F64(S32(((F64(2509.95888)) * (slow16)) < (dsp.const4)))
        var slow18 = F64(dsp.button3)
        var i_slow19 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const5) / (slow16))))
        var slow20 = (dsp.const6) * (cos((dsp.const7) * (slow16)))
        var slow21 = pow(F64(2.0), (F64(0.08333333333333333)) * ((F64(dsp.entry5)) + (F64(-69.0))))
        var slow22 = F64(S32(((F64(2509.95888)) * (slow21)) < (dsp.const4)))
        var slow23 = F64(dsp.button4)
        var i_slow24 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const5) / (slow21))))
        var slow25 = (dsp.const6) * (cos((dsp.const7) * (slow21)))
        var slow26 = pow(F64(2.0), (F64(0.08333333333333333)) * ((F64(dsp.entry6)) + (F64(-69.0))))
        var slow27 = F64(S32(((F64(2509.95888)) * (slow26)) < (dsp.const4)))
        var slow28 = F64(dsp.button5)
        var i_slow29 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const5) / (slow26))))
        var slow30 = (dsp.const6) * (cos((dsp.const7) * (slow26)))
        var slow31 = pow(F64(2.0), (F64(0.08333333333333333)) * ((F64(dsp.entry7)) + (F64(-69.0))))
        var slow32 = F64(S32(((F64(2509.95888)) * (slow31)) < (dsp.const4)))
        var slow33 = F64(dsp.button6)
        var i_slow34 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const5) / (slow31))))
        var slow35 = (dsp.const6) * (cos((dsp.const7) * (slow31)))
        var slow36 = pow(F64(2.0), (F64(0.08333333333333333)) * ((F64(dsp.entry8)) + (F64(-69.0))))
        var slow37 = F64(S32(((F64(2509.95888)) * (slow36)) < (dsp.const4)))
        var slow38 = F64(dsp.button7)
        var i_slow39 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const5) / (slow36))))
        var slow40 = (dsp.const6) * (cos((dsp.const7) * (slow36)))
        var slow41 = pow(F64(2.0), (F64(0.08333333333333333)) * ((F64(dsp.entry9)) + (F64(-69.0))))
        var slow42 = F64(S32(((F64(2509.95888)) * (slow41)) < (dsp.const4)))
        var slow43 = F64(dsp.button8)
        var i_slow44 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const5) / (slow41))))
        var slow45 = (dsp.const6) * (cos((dsp.const7) * (slow41)))
        var slow46 = pow(F64(2.0), (F64(0.08333333333333333)) * ((F64(dsp.entry10)) + (F64(-69.0))))
        var slow47 = F64(S32(((F64(2509.95888)) * (slow46)) < (dsp.const4)))
        var slow48 = F64(dsp.button9)
        var i_slow49 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const5) / (slow46))))
        var slow50 = (dsp.const6) * (cos((dsp.const7) * (slow46)))
        var slow51 = F64(S32(((F64(9669.451879999999)) * (slow0)) < (dsp.const4)))
        var i_slow52 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const8) / (slow0))))
        var slow53 = (dsp.const6) * (cos((dsp.const9) * (slow0)))
        var slow54 = F64(S32(((F64(7603.5621200000005)) * (slow0)) < (dsp.const4)))
        var i_slow55 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const10) / (slow0))))
        var slow56 = (dsp.const6) * (cos((dsp.const11) * (slow0)))
        var slow57 = (F64(0.9999655)) * (F64(S32(((F64(5635.24808)) * (slow0)) < (dsp.const4))))
        var i_slow58 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const12) / (slow0))))
        var slow59 = (dsp.const6) * (cos((dsp.const13) * (slow0)))
        var slow60 = (F64(0.9999655)) * (F64(S32(((F64(5646.533200000001)) * (slow0)) < (dsp.const4))))
        var i_slow61 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const14) / (slow0))))
        var slow62 = (dsp.const6) * (cos((dsp.const15) * (slow0)))
        var slow63 = F64(S32(((F64(3966.81868)) * (slow0)) < (dsp.const4)))
        var i_slow64 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const16) / (slow0))))
        var slow65 = (dsp.const6) * (cos((dsp.const17) * (slow0)))
        var slow66 = F64(S32(((F64(3959.208)) * (slow0)) < (dsp.const4)))
        var i_slow67 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const18) / (slow0))))
        var slow68 = (dsp.const6) * (cos((dsp.const19) * (slow0)))
        var slow69 = (F64(0.9999828)) * (F64(S32(((F64(1317.050944)) * (slow0)) < (dsp.const4))))
        var i_slow70 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const20) / (slow0))))
        var slow71 = (dsp.const6) * (cos((dsp.const21) * (slow0)))
        var slow72 = (F64(0.9999828)) * (F64(S32(((F64(1310.83832)) * (slow0)) < (dsp.const4))))
        var i_slow73 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const22) / (slow0))))
        var slow74 = (dsp.const6) * (cos((dsp.const23) * (slow0)))
        var slow75 = (F64(0.999926)) * (F64(S32(((F64(441.712348)) * (slow0)) < (dsp.const4))))
        var i_slow76 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const24) / (slow0))))
        var slow77 = (dsp.const6) * (cos((dsp.const25) * (slow0)))
        var slow78 = (F64(0.999926)) * (F64(S32(((F64(438.287674)) * (slow0)) < (dsp.const4))))
        var i_slow79 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const26) / (slow0))))
        var slow80 = (dsp.const6) * (cos((dsp.const27) * (slow0)))
        var slow81 = F64(S32(((F64(9669.451879999999)) * (slow6)) < (dsp.const4)))
        var i_slow82 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const8) / (slow6))))
        var slow83 = (dsp.const6) * (cos((dsp.const9) * (slow6)))
        var slow84 = F64(S32(((F64(7603.5621200000005)) * (slow6)) < (dsp.const4)))
        var i_slow85 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const10) / (slow6))))
        var slow86 = (dsp.const6) * (cos((dsp.const11) * (slow6)))
        var slow87 = (F64(0.9999655)) * (F64(S32(((F64(5635.24808)) * (slow6)) < (dsp.const4))))
        var i_slow88 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const12) / (slow6))))
        var slow89 = (dsp.const6) * (cos((dsp.const13) * (slow6)))
        var slow90 = (F64(0.9999655)) * (F64(S32(((F64(5646.533200000001)) * (slow6)) < (dsp.const4))))
        var i_slow91 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const14) / (slow6))))
        var slow92 = (dsp.const6) * (cos((dsp.const15) * (slow6)))
        var slow93 = F64(S32(((F64(3966.81868)) * (slow6)) < (dsp.const4)))
        var i_slow94 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const16) / (slow6))))
        var slow95 = (dsp.const6) * (cos((dsp.const17) * (slow6)))
        var slow96 = F64(S32(((F64(3959.208)) * (slow6)) < (dsp.const4)))
        var i_slow97 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const18) / (slow6))))
        var slow98 = (dsp.const6) * (cos((dsp.const19) * (slow6)))
        var slow99 = (F64(0.9999828)) * (F64(S32(((F64(1317.050944)) * (slow6)) < (dsp.const4))))
        var i_slow100 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const20) / (slow6))))
        var slow101 = (dsp.const6) * (cos((dsp.const21) * (slow6)))
        var slow102 = (F64(0.9999828)) * (F64(S32(((F64(1310.83832)) * (slow6)) < (dsp.const4))))
        var i_slow103 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const22) / (slow6))))
        var slow104 = (dsp.const6) * (cos((dsp.const23) * (slow6)))
        var slow105 = (F64(0.999926)) * (F64(S32(((F64(441.712348)) * (slow6)) < (dsp.const4))))
        var i_slow106 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const24) / (slow6))))
        var slow107 = (dsp.const6) * (cos((dsp.const25) * (slow6)))
        var slow108 = (F64(0.999926)) * (F64(S32(((F64(438.287674)) * (slow6)) < (dsp.const4))))
        var i_slow109 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const26) / (slow6))))
        var slow110 = (dsp.const6) * (cos((dsp.const27) * (slow6)))
        var slow111 = F64(S32(((F64(9669.451879999999)) * (slow11)) < (dsp.const4)))
        var i_slow112 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const8) / (slow11))))
        var slow113 = (dsp.const6) * (cos((dsp.const9) * (slow11)))
        var slow114 = F64(S32(((F64(7603.5621200000005)) * (slow11)) < (dsp.const4)))
        var i_slow115 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const10) / (slow11))))
        var slow116 = (dsp.const6) * (cos((dsp.const11) * (slow11)))
        var slow117 = (F64(0.9999655)) * (F64(S32(((F64(5635.24808)) * (slow11)) < (dsp.const4))))
        var i_slow118 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const12) / (slow11))))
        var slow119 = (dsp.const6) * (cos((dsp.const13) * (slow11)))
        var slow120 = (F64(0.9999655)) * (F64(S32(((F64(5646.533200000001)) * (slow11)) < (dsp.const4))))
        var i_slow121 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const14) / (slow11))))
        var slow122 = (dsp.const6) * (cos((dsp.const15) * (slow11)))
        var slow123 = F64(S32(((F64(3966.81868)) * (slow11)) < (dsp.const4)))
        var i_slow124 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const16) / (slow11))))
        var slow125 = (dsp.const6) * (cos((dsp.const17) * (slow11)))
        var slow126 = F64(S32(((F64(3959.208)) * (slow11)) < (dsp.const4)))
        var i_slow127 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const18) / (slow11))))
        var slow128 = (dsp.const6) * (cos((dsp.const19) * (slow11)))
        var slow129 = (F64(0.9999828)) * (F64(S32(((F64(1317.050944)) * (slow11)) < (dsp.const4))))
        var i_slow130 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const20) / (slow11))))
        var slow131 = (dsp.const6) * (cos((dsp.const21) * (slow11)))
        var slow132 = (F64(0.9999828)) * (F64(S32(((F64(1310.83832)) * (slow11)) < (dsp.const4))))
        var i_slow133 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const22) / (slow11))))
        var slow134 = (dsp.const6) * (cos((dsp.const23) * (slow11)))
        var slow135 = (F64(0.999926)) * (F64(S32(((F64(441.712348)) * (slow11)) < (dsp.const4))))
        var i_slow136 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const24) / (slow11))))
        var slow137 = (dsp.const6) * (cos((dsp.const25) * (slow11)))
        var slow138 = (F64(0.999926)) * (F64(S32(((F64(438.287674)) * (slow11)) < (dsp.const4))))
        var i_slow139 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const26) / (slow11))))
        var slow140 = (dsp.const6) * (cos((dsp.const27) * (slow11)))
        var slow141 = F64(S32(((F64(9669.451879999999)) * (slow16)) < (dsp.const4)))
        var i_slow142 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const8) / (slow16))))
        var slow143 = (dsp.const6) * (cos((dsp.const9) * (slow16)))
        var slow144 = F64(S32(((F64(7603.5621200000005)) * (slow16)) < (dsp.const4)))
        var i_slow145 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const10) / (slow16))))
        var slow146 = (dsp.const6) * (cos((dsp.const11) * (slow16)))
        var slow147 = (F64(0.9999655)) * (F64(S32(((F64(5635.24808)) * (slow16)) < (dsp.const4))))
        var i_slow148 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const12) / (slow16))))
        var slow149 = (dsp.const6) * (cos((dsp.const13) * (slow16)))
        var slow150 = (F64(0.9999655)) * (F64(S32(((F64(5646.533200000001)) * (slow16)) < (dsp.const4))))
        var i_slow151 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const14) / (slow16))))
        var slow152 = (dsp.const6) * (cos((dsp.const15) * (slow16)))
        var slow153 = F64(S32(((F64(3966.81868)) * (slow16)) < (dsp.const4)))
        var i_slow154 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const16) / (slow16))))
        var slow155 = (dsp.const6) * (cos((dsp.const17) * (slow16)))
        var slow156 = F64(S32(((F64(3959.208)) * (slow16)) < (dsp.const4)))
        var i_slow157 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const18) / (slow16))))
        var slow158 = (dsp.const6) * (cos((dsp.const19) * (slow16)))
        var slow159 = (F64(0.9999828)) * (F64(S32(((F64(1317.050944)) * (slow16)) < (dsp.const4))))
        var i_slow160 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const20) / (slow16))))
        var slow161 = (dsp.const6) * (cos((dsp.const21) * (slow16)))
        var slow162 = (F64(0.9999828)) * (F64(S32(((F64(1310.83832)) * (slow16)) < (dsp.const4))))
        var i_slow163 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const22) / (slow16))))
        var slow164 = (dsp.const6) * (cos((dsp.const23) * (slow16)))
        var slow165 = (F64(0.999926)) * (F64(S32(((F64(441.712348)) * (slow16)) < (dsp.const4))))
        var i_slow166 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const24) / (slow16))))
        var slow167 = (dsp.const6) * (cos((dsp.const25) * (slow16)))
        var slow168 = (F64(0.999926)) * (F64(S32(((F64(438.287674)) * (slow16)) < (dsp.const4))))
        var i_slow169 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const26) / (slow16))))
        var slow170 = (dsp.const6) * (cos((dsp.const27) * (slow16)))
        var slow171 = F64(S32(((F64(9669.451879999999)) * (slow21)) < (dsp.const4)))
        var i_slow172 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const8) / (slow21))))
        var slow173 = (dsp.const6) * (cos((dsp.const9) * (slow21)))
        var slow174 = F64(S32(((F64(7603.5621200000005)) * (slow21)) < (dsp.const4)))
        var i_slow175 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const10) / (slow21))))
        var slow176 = (dsp.const6) * (cos((dsp.const11) * (slow21)))
        var slow177 = (F64(0.9999655)) * (F64(S32(((F64(5635.24808)) * (slow21)) < (dsp.const4))))
        var i_slow178 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const12) / (slow21))))
        var slow179 = (dsp.const6) * (cos((dsp.const13) * (slow21)))
        var slow180 = (F64(0.9999655)) * (F64(S32(((F64(5646.533200000001)) * (slow21)) < (dsp.const4))))
        var i_slow181 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const14) / (slow21))))
        var slow182 = (dsp.const6) * (cos((dsp.const15) * (slow21)))
        var slow183 = F64(S32(((F64(3966.81868)) * (slow21)) < (dsp.const4)))
        var i_slow184 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const16) / (slow21))))
        var slow185 = (dsp.const6) * (cos((dsp.const17) * (slow21)))
        var slow186 = F64(S32(((F64(3959.208)) * (slow21)) < (dsp.const4)))
        var i_slow187 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const18) / (slow21))))
        var slow188 = (dsp.const6) * (cos((dsp.const19) * (slow21)))
        var slow189 = (F64(0.9999828)) * (F64(S32(((F64(1317.050944)) * (slow21)) < (dsp.const4))))
        var i_slow190 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const20) / (slow21))))
        var slow191 = (dsp.const6) * (cos((dsp.const21) * (slow21)))
        var slow192 = (F64(0.9999828)) * (F64(S32(((F64(1310.83832)) * (slow21)) < (dsp.const4))))
        var i_slow193 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const22) / (slow21))))
        var slow194 = (dsp.const6) * (cos((dsp.const23) * (slow21)))
        var slow195 = (F64(0.999926)) * (F64(S32(((F64(441.712348)) * (slow21)) < (dsp.const4))))
        var i_slow196 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const24) / (slow21))))
        var slow197 = (dsp.const6) * (cos((dsp.const25) * (slow21)))
        var slow198 = (F64(0.999926)) * (F64(S32(((F64(438.287674)) * (slow21)) < (dsp.const4))))
        var i_slow199 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const26) / (slow21))))
        var slow200 = (dsp.const6) * (cos((dsp.const27) * (slow21)))
        var slow201 = F64(S32(((F64(9669.451879999999)) * (slow26)) < (dsp.const4)))
        var i_slow202 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const8) / (slow26))))
        var slow203 = (dsp.const6) * (cos((dsp.const9) * (slow26)))
        var slow204 = F64(S32(((F64(7603.5621200000005)) * (slow26)) < (dsp.const4)))
        var i_slow205 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const10) / (slow26))))
        var slow206 = (dsp.const6) * (cos((dsp.const11) * (slow26)))
        var slow207 = (F64(0.9999655)) * (F64(S32(((F64(5635.24808)) * (slow26)) < (dsp.const4))))
        var i_slow208 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const12) / (slow26))))
        var slow209 = (dsp.const6) * (cos((dsp.const13) * (slow26)))
        var slow210 = (F64(0.9999655)) * (F64(S32(((F64(5646.533200000001)) * (slow26)) < (dsp.const4))))
        var i_slow211 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const14) / (slow26))))
        var slow212 = (dsp.const6) * (cos((dsp.const15) * (slow26)))
        var slow213 = F64(S32(((F64(3966.81868)) * (slow26)) < (dsp.const4)))
        var i_slow214 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const16) / (slow26))))
        var slow215 = (dsp.const6) * (cos((dsp.const17) * (slow26)))
        var slow216 = F64(S32(((F64(3959.208)) * (slow26)) < (dsp.const4)))
        var i_slow217 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const18) / (slow26))))
        var slow218 = (dsp.const6) * (cos((dsp.const19) * (slow26)))
        var slow219 = (F64(0.9999828)) * (F64(S32(((F64(1317.050944)) * (slow26)) < (dsp.const4))))
        var i_slow220 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const20) / (slow26))))
        var slow221 = (dsp.const6) * (cos((dsp.const21) * (slow26)))
        var slow222 = (F64(0.9999828)) * (F64(S32(((F64(1310.83832)) * (slow26)) < (dsp.const4))))
        var i_slow223 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const22) / (slow26))))
        var slow224 = (dsp.const6) * (cos((dsp.const23) * (slow26)))
        var slow225 = (F64(0.999926)) * (F64(S32(((F64(441.712348)) * (slow26)) < (dsp.const4))))
        var i_slow226 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const24) / (slow26))))
        var slow227 = (dsp.const6) * (cos((dsp.const25) * (slow26)))
        var slow228 = (F64(0.999926)) * (F64(S32(((F64(438.287674)) * (slow26)) < (dsp.const4))))
        var i_slow229 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const26) / (slow26))))
        var slow230 = (dsp.const6) * (cos((dsp.const27) * (slow26)))
        var slow231 = F64(S32(((F64(9669.451879999999)) * (slow31)) < (dsp.const4)))
        var i_slow232 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const8) / (slow31))))
        var slow233 = (dsp.const6) * (cos((dsp.const9) * (slow31)))
        var slow234 = F64(S32(((F64(7603.5621200000005)) * (slow31)) < (dsp.const4)))
        var i_slow235 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const10) / (slow31))))
        var slow236 = (dsp.const6) * (cos((dsp.const11) * (slow31)))
        var slow237 = (F64(0.9999655)) * (F64(S32(((F64(5635.24808)) * (slow31)) < (dsp.const4))))
        var i_slow238 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const12) / (slow31))))
        var slow239 = (dsp.const6) * (cos((dsp.const13) * (slow31)))
        var slow240 = (F64(0.9999655)) * (F64(S32(((F64(5646.533200000001)) * (slow31)) < (dsp.const4))))
        var i_slow241 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const14) / (slow31))))
        var slow242 = (dsp.const6) * (cos((dsp.const15) * (slow31)))
        var slow243 = F64(S32(((F64(3966.81868)) * (slow31)) < (dsp.const4)))
        var i_slow244 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const16) / (slow31))))
        var slow245 = (dsp.const6) * (cos((dsp.const17) * (slow31)))
        var slow246 = F64(S32(((F64(3959.208)) * (slow31)) < (dsp.const4)))
        var i_slow247 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const18) / (slow31))))
        var slow248 = (dsp.const6) * (cos((dsp.const19) * (slow31)))
        var slow249 = (F64(0.9999828)) * (F64(S32(((F64(1317.050944)) * (slow31)) < (dsp.const4))))
        var i_slow250 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const20) / (slow31))))
        var slow251 = (dsp.const6) * (cos((dsp.const21) * (slow31)))
        var slow252 = (F64(0.9999828)) * (F64(S32(((F64(1310.83832)) * (slow31)) < (dsp.const4))))
        var i_slow253 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const22) / (slow31))))
        var slow254 = (dsp.const6) * (cos((dsp.const23) * (slow31)))
        var slow255 = (F64(0.999926)) * (F64(S32(((F64(441.712348)) * (slow31)) < (dsp.const4))))
        var i_slow256 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const24) / (slow31))))
        var slow257 = (dsp.const6) * (cos((dsp.const25) * (slow31)))
        var slow258 = (F64(0.999926)) * (F64(S32(((F64(438.287674)) * (slow31)) < (dsp.const4))))
        var i_slow259 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const26) / (slow31))))
        var slow260 = (dsp.const6) * (cos((dsp.const27) * (slow31)))
        var slow261 = F64(S32(((F64(9669.451879999999)) * (slow36)) < (dsp.const4)))
        var i_slow262 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const8) / (slow36))))
        var slow263 = (dsp.const6) * (cos((dsp.const9) * (slow36)))
        var slow264 = F64(S32(((F64(7603.5621200000005)) * (slow36)) < (dsp.const4)))
        var i_slow265 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const10) / (slow36))))
        var slow266 = (dsp.const6) * (cos((dsp.const11) * (slow36)))
        var slow267 = (F64(0.9999655)) * (F64(S32(((F64(5635.24808)) * (slow36)) < (dsp.const4))))
        var i_slow268 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const12) / (slow36))))
        var slow269 = (dsp.const6) * (cos((dsp.const13) * (slow36)))
        var slow270 = (F64(0.9999655)) * (F64(S32(((F64(5646.533200000001)) * (slow36)) < (dsp.const4))))
        var i_slow271 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const14) / (slow36))))
        var slow272 = (dsp.const6) * (cos((dsp.const15) * (slow36)))
        var slow273 = F64(S32(((F64(3966.81868)) * (slow36)) < (dsp.const4)))
        var i_slow274 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const16) / (slow36))))
        var slow275 = (dsp.const6) * (cos((dsp.const17) * (slow36)))
        var slow276 = F64(S32(((F64(3959.208)) * (slow36)) < (dsp.const4)))
        var i_slow277 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const18) / (slow36))))
        var slow278 = (dsp.const6) * (cos((dsp.const19) * (slow36)))
        var slow279 = (F64(0.9999828)) * (F64(S32(((F64(1317.050944)) * (slow36)) < (dsp.const4))))
        var i_slow280 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const20) / (slow36))))
        var slow281 = (dsp.const6) * (cos((dsp.const21) * (slow36)))
        var slow282 = (F64(0.9999828)) * (F64(S32(((F64(1310.83832)) * (slow36)) < (dsp.const4))))
        var i_slow283 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const22) / (slow36))))
        var slow284 = (dsp.const6) * (cos((dsp.const23) * (slow36)))
        var slow285 = (F64(0.999926)) * (F64(S32(((F64(441.712348)) * (slow36)) < (dsp.const4))))
        var i_slow286 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const24) / (slow36))))
        var slow287 = (dsp.const6) * (cos((dsp.const25) * (slow36)))
        var slow288 = (F64(0.999926)) * (F64(S32(((F64(438.287674)) * (slow36)) < (dsp.const4))))
        var i_slow289 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const26) / (slow36))))
        var slow290 = (dsp.const6) * (cos((dsp.const27) * (slow36)))
        var slow291 = F64(S32(((F64(9669.451879999999)) * (slow46)) < (dsp.const4)))
        var i_slow292 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const8) / (slow46))))
        var slow293 = (dsp.const6) * (cos((dsp.const9) * (slow46)))
        var slow294 = F64(S32(((F64(7603.5621200000005)) * (slow46)) < (dsp.const4)))
        var i_slow295 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const10) / (slow46))))
        var slow296 = (dsp.const6) * (cos((dsp.const11) * (slow46)))
        var slow297 = (F64(0.9999655)) * (F64(S32(((F64(5635.24808)) * (slow46)) < (dsp.const4))))
        var i_slow298 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const12) / (slow46))))
        var slow299 = (dsp.const6) * (cos((dsp.const13) * (slow46)))
        var slow300 = (F64(0.9999655)) * (F64(S32(((F64(5646.533200000001)) * (slow46)) < (dsp.const4))))
        var i_slow301 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const14) / (slow46))))
        var slow302 = (dsp.const6) * (cos((dsp.const15) * (slow46)))
        var slow303 = F64(S32(((F64(3966.81868)) * (slow46)) < (dsp.const4)))
        var i_slow304 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const16) / (slow46))))
        var slow305 = (dsp.const6) * (cos((dsp.const17) * (slow46)))
        var slow306 = F64(S32(((F64(3959.208)) * (slow46)) < (dsp.const4)))
        var i_slow307 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const18) / (slow46))))
        var slow308 = (dsp.const6) * (cos((dsp.const19) * (slow46)))
        var slow309 = (F64(0.9999828)) * (F64(S32(((F64(1317.050944)) * (slow46)) < (dsp.const4))))
        var i_slow310 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const20) / (slow46))))
        var slow311 = (dsp.const6) * (cos((dsp.const21) * (slow46)))
        var slow312 = (F64(0.9999828)) * (F64(S32(((F64(1310.83832)) * (slow46)) < (dsp.const4))))
        var i_slow313 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const22) / (slow46))))
        var slow314 = (dsp.const6) * (cos((dsp.const23) * (slow46)))
        var slow315 = (F64(0.999926)) * (F64(S32(((F64(441.712348)) * (slow46)) < (dsp.const4))))
        var i_slow316 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const24) / (slow46))))
        var slow317 = (dsp.const6) * (cos((dsp.const25) * (slow46)))
        var slow318 = (F64(0.999926)) * (F64(S32(((F64(438.287674)) * (slow46)) < (dsp.const4))))
        var i_slow319 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const26) / (slow46))))
        var slow320 = (dsp.const6) * (cos((dsp.const27) * (slow46)))
        var slow321 = F64(S32(((F64(9669.451879999999)) * (slow41)) < (dsp.const4)))
        var i_slow322 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const8) / (slow41))))
        var slow323 = (dsp.const6) * (cos((dsp.const9) * (slow41)))
        var slow324 = F64(S32(((F64(7603.5621200000005)) * (slow41)) < (dsp.const4)))
        var i_slow325 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const10) / (slow41))))
        var slow326 = (dsp.const6) * (cos((dsp.const11) * (slow41)))
        var slow327 = (F64(0.9999655)) * (F64(S32(((F64(5635.24808)) * (slow41)) < (dsp.const4))))
        var i_slow328 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const12) / (slow41))))
        var slow329 = (dsp.const6) * (cos((dsp.const13) * (slow41)))
        var slow330 = (F64(0.9999655)) * (F64(S32(((F64(5646.533200000001)) * (slow41)) < (dsp.const4))))
        var i_slow331 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const14) / (slow41))))
        var slow332 = (dsp.const6) * (cos((dsp.const15) * (slow41)))
        var slow333 = F64(S32(((F64(3966.81868)) * (slow41)) < (dsp.const4)))
        var i_slow334 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const16) / (slow41))))
        var slow335 = (dsp.const6) * (cos((dsp.const17) * (slow41)))
        var slow336 = (F64(0.999926)) * (F64(S32(((F64(438.287674)) * (slow41)) < (dsp.const4))))
        var i_slow337 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const26) / (slow41))))
        var slow338 = (dsp.const6) * (cos((dsp.const27) * (slow41)))
        var slow339 = (F64(0.999926)) * (F64(S32(((F64(441.712348)) * (slow41)) < (dsp.const4))))
        var i_slow340 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const24) / (slow41))))
        var slow341 = (dsp.const6) * (cos((dsp.const25) * (slow41)))
        var slow342 = (F64(0.9999828)) * (F64(S32(((F64(1310.83832)) * (slow41)) < (dsp.const4))))
        var i_slow343 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const22) / (slow41))))
        var slow344 = (dsp.const6) * (cos((dsp.const23) * (slow41)))
        var slow345 = (F64(0.9999828)) * (F64(S32(((F64(1317.050944)) * (slow41)) < (dsp.const4))))
        var i_slow346 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const20) / (slow41))))
        var slow347 = (dsp.const6) * (cos((dsp.const21) * (slow41)))
        var slow348 = F64(S32(((F64(3959.208)) * (slow41)) < (dsp.const4)))
        var i_slow349 = S32(min(F64(4096.0), max(F64(0.0), (dsp.const18) / (slow41))))
        var slow350 = (dsp.const6) * (cos((dsp.const19) * (slow41)))
        for var i0 in range(S32(0), count):
            dsp.vec0[S32(0)] = slow3
            var temp0 = F64(S32((slow3) > (dsp.vec0[S32(1)])))
            dsp.vec1[(dsp.iota0) & (S32(255))] = ((slow2) * (dsp.rec0[S32(1)])) + ((F64(5.2995043)) * (temp0))
            dsp.rec1[S32(0)] = ((slow1) * (dsp.vec1[((dsp.iota0) - (i_slow4)) & (S32(255))])) - (((slow5) * (dsp.rec1[S32(1)])) + ((dsp.const2) * (dsp.rec1[S32(2)])))
            dsp.rec0[S32(0)] = (dsp.const3) * ((dsp.rec1[S32(0)]) - (dsp.rec1[S32(2)]))
            dsp.vec2[S32(0)] = slow8
            var temp1 = F64(S32((slow8) > (dsp.vec2[S32(1)])))
            dsp.vec3[(dsp.iota0) & (S32(255))] = ((slow2) * (dsp.rec2[S32(1)])) + ((F64(5.2995043)) * (temp1))
            dsp.rec3[S32(0)] = ((slow7) * (dsp.vec3[((dsp.iota0) - (i_slow9)) & (S32(255))])) - (((slow10) * (dsp.rec3[S32(1)])) + ((dsp.const2) * (dsp.rec3[S32(2)])))
            dsp.rec2[S32(0)] = (dsp.const3) * ((dsp.rec3[S32(0)]) - (dsp.rec3[S32(2)]))
            dsp.vec4[S32(0)] = slow13
            var temp2 = F64(S32((slow13) > (dsp.vec4[S32(1)])))
            dsp.vec5[(dsp.iota0) & (S32(255))] = ((slow2) * (dsp.rec4[S32(1)])) + ((F64(5.2995043)) * (temp2))
            dsp.rec5[S32(0)] = ((slow12) * (dsp.vec5[((dsp.iota0) - (i_slow14)) & (S32(255))])) - (((slow15) * (dsp.rec5[S32(1)])) + ((dsp.const2) * (dsp.rec5[S32(2)])))
            dsp.rec4[S32(0)] = (dsp.const3) * ((dsp.rec5[S32(0)]) - (dsp.rec5[S32(2)]))
            dsp.vec6[S32(0)] = slow18
            var temp3 = F64(S32((slow18) > (dsp.vec6[S32(1)])))
            dsp.vec7[(dsp.iota0) & (S32(255))] = ((slow2) * (dsp.rec6[S32(1)])) + ((F64(5.2995043)) * (temp3))
            dsp.rec7[S32(0)] = ((slow17) * (dsp.vec7[((dsp.iota0) - (i_slow19)) & (S32(255))])) - (((slow20) * (dsp.rec7[S32(1)])) + ((dsp.const2) * (dsp.rec7[S32(2)])))
            dsp.rec6[S32(0)] = (dsp.const3) * ((dsp.rec7[S32(0)]) - (dsp.rec7[S32(2)]))
            dsp.vec8[S32(0)] = slow23
            var temp4 = F64(S32((slow23) > (dsp.vec8[S32(1)])))
            dsp.vec9[(dsp.iota0) & (S32(255))] = ((slow2) * (dsp.rec8[S32(1)])) + ((F64(5.2995043)) * (temp4))
            dsp.rec9[S32(0)] = ((slow22) * (dsp.vec9[((dsp.iota0) - (i_slow24)) & (S32(255))])) - (((slow25) * (dsp.rec9[S32(1)])) + ((dsp.const2) * (dsp.rec9[S32(2)])))
            dsp.rec8[S32(0)] = (dsp.const3) * ((dsp.rec9[S32(0)]) - (dsp.rec9[S32(2)]))
            dsp.vec10[S32(0)] = slow28
            var temp5 = F64(S32((slow28) > (dsp.vec10[S32(1)])))
            dsp.vec11[(dsp.iota0) & (S32(255))] = ((slow2) * (dsp.rec10[S32(1)])) + ((F64(5.2995043)) * (temp5))
            dsp.rec11[S32(0)] = ((slow27) * (dsp.vec11[((dsp.iota0) - (i_slow29)) & (S32(255))])) - (((slow30) * (dsp.rec11[S32(1)])) + ((dsp.const2) * (dsp.rec11[S32(2)])))
            dsp.rec10[S32(0)] = (dsp.const3) * ((dsp.rec11[S32(0)]) - (dsp.rec11[S32(2)]))
            dsp.vec12[S32(0)] = slow33
            var temp6 = F64(S32((slow33) > (dsp.vec12[S32(1)])))
            dsp.vec13[(dsp.iota0) & (S32(255))] = ((slow2) * (dsp.rec12[S32(1)])) + ((F64(5.2995043)) * (temp6))
            dsp.rec13[S32(0)] = ((slow32) * (dsp.vec13[((dsp.iota0) - (i_slow34)) & (S32(255))])) - (((slow35) * (dsp.rec13[S32(1)])) + ((dsp.const2) * (dsp.rec13[S32(2)])))
            dsp.rec12[S32(0)] = (dsp.const3) * ((dsp.rec13[S32(0)]) - (dsp.rec13[S32(2)]))
            dsp.vec14[S32(0)] = slow38
            var temp7 = F64(S32((slow38) > (dsp.vec14[S32(1)])))
            dsp.vec15[(dsp.iota0) & (S32(255))] = ((slow2) * (dsp.rec14[S32(1)])) + ((F64(5.2995043)) * (temp7))
            dsp.rec15[S32(0)] = ((slow37) * (dsp.vec15[((dsp.iota0) - (i_slow39)) & (S32(255))])) - (((slow40) * (dsp.rec15[S32(1)])) + ((dsp.const2) * (dsp.rec15[S32(2)])))
            dsp.rec14[S32(0)] = (dsp.const3) * ((dsp.rec15[S32(0)]) - (dsp.rec15[S32(2)]))
            dsp.vec16[S32(0)] = slow43
            var temp8 = F64(S32((slow43) > (dsp.vec16[S32(1)])))
            dsp.vec17[(dsp.iota0) & (S32(255))] = ((slow2) * (dsp.rec16[S32(1)])) + ((F64(5.2995043)) * (temp8))
            dsp.rec17[S32(0)] = ((slow42) * (dsp.vec17[((dsp.iota0) - (i_slow44)) & (S32(255))])) - (((slow45) * (dsp.rec17[S32(1)])) + ((dsp.const2) * (dsp.rec17[S32(2)])))
            dsp.rec16[S32(0)] = (dsp.const3) * ((dsp.rec17[S32(0)]) - (dsp.rec17[S32(2)]))
            dsp.vec18[S32(0)] = slow48
            var temp9 = F64(S32((slow48) > (dsp.vec18[S32(1)])))
            dsp.vec19[(dsp.iota0) & (S32(255))] = ((slow2) * (dsp.rec18[S32(1)])) + ((F64(5.2995043)) * (temp9))
            dsp.rec19[S32(0)] = ((slow47) * (dsp.vec19[((dsp.iota0) - (i_slow49)) & (S32(255))])) - (((slow50) * (dsp.rec19[S32(1)])) + ((dsp.const2) * (dsp.rec19[S32(2)])))
            dsp.rec18[S32(0)] = (dsp.const3) * ((dsp.rec19[S32(0)]) - (dsp.rec19[S32(2)]))
            var temp10 = (F64(6.7063036)) * (temp0)
            dsp.vec20[(dsp.iota0) & (S32(63))] = (temp10) + ((slow2) * (dsp.rec20[S32(1)]))
            dsp.rec21[S32(0)] = ((slow51) * (dsp.vec20[((dsp.iota0) - (i_slow52)) & (S32(63))])) - (((slow53) * (dsp.rec21[S32(1)])) + ((dsp.const2) * (dsp.rec21[S32(2)])))
            dsp.rec20[S32(0)] = (dsp.const3) * ((dsp.rec21[S32(0)]) - (dsp.rec21[S32(2)]))
            dsp.vec21[(dsp.iota0) & (S32(63))] = ((slow2) * (dsp.rec22[S32(1)])) + (temp10)
            dsp.rec23[S32(0)] = ((slow54) * (dsp.vec21[((dsp.iota0) - (i_slow55)) & (S32(63))])) - (((slow56) * (dsp.rec23[S32(1)])) + ((dsp.const2) * (dsp.rec23[S32(2)])))
            dsp.rec22[S32(0)] = (dsp.const3) * ((dsp.rec23[S32(0)]) - (dsp.rec23[S32(2)]))
            var temp11 = (F64(1.7063034)) * (temp0)
            dsp.vec22[(dsp.iota0) & (S32(63))] = (temp11) + ((slow2) * (dsp.rec24[S32(1)]))
            dsp.rec25[S32(0)] = ((slow57) * (dsp.vec22[((dsp.iota0) - (i_slow58)) & (S32(63))])) - (((slow59) * (dsp.rec25[S32(1)])) + ((dsp.const2) * (dsp.rec25[S32(2)])))
            dsp.rec24[S32(0)] = (dsp.const3) * ((dsp.rec25[S32(0)]) - (dsp.rec25[S32(2)]))
            dsp.vec23[(dsp.iota0) & (S32(63))] = ((slow2) * (dsp.rec26[S32(1)])) + (temp11)
            dsp.rec27[S32(0)] = ((slow60) * (dsp.vec23[((dsp.iota0) - (i_slow61)) & (S32(63))])) - (((slow62) * (dsp.rec27[S32(1)])) + ((dsp.const2) * (dsp.rec27[S32(2)])))
            dsp.rec26[S32(0)] = (dsp.const3) * ((dsp.rec27[S32(0)]) - (dsp.rec27[S32(2)]))
            var temp12 = (F64(5.0063033)) * (temp0)
            dsp.vec24[(dsp.iota0) & (S32(127))] = (temp12) + ((slow2) * (dsp.rec28[S32(1)]))
            dsp.rec29[S32(0)] = ((slow63) * (dsp.vec24[((dsp.iota0) - (i_slow64)) & (S32(127))])) - (((slow65) * (dsp.rec29[S32(1)])) + ((dsp.const2) * (dsp.rec29[S32(2)])))
            dsp.rec28[S32(0)] = (dsp.const3) * ((dsp.rec29[S32(0)]) - (dsp.rec29[S32(2)]))
            dsp.vec25[(dsp.iota0) & (S32(127))] = ((slow2) * (dsp.rec30[S32(1)])) + (temp12)
            dsp.rec31[S32(0)] = ((slow66) * (dsp.vec25[((dsp.iota0) - (i_slow67)) & (S32(127))])) - (((slow68) * (dsp.rec31[S32(1)])) + ((dsp.const2) * (dsp.rec31[S32(2)])))
            dsp.rec30[S32(0)] = (dsp.const3) * ((dsp.rec31[S32(0)]) - (dsp.rec31[S32(2)]))
            var temp13 = (F64(2.0914886)) * (temp0)
            dsp.vec26[(dsp.iota0) & (S32(255))] = (temp13) + ((slow2) * (dsp.rec32[S32(1)]))
            dsp.rec33[S32(0)] = ((slow69) * (dsp.vec26[((dsp.iota0) - (i_slow70)) & (S32(255))])) - (((slow71) * (dsp.rec33[S32(1)])) + ((dsp.const2) * (dsp.rec33[S32(2)])))
            dsp.rec32[S32(0)] = (dsp.const3) * ((dsp.rec33[S32(0)]) - (dsp.rec33[S32(2)]))
            dsp.vec27[(dsp.iota0) & (S32(255))] = ((slow2) * (dsp.rec34[S32(1)])) + (temp13)
            dsp.rec35[S32(0)] = ((slow72) * (dsp.vec27[((dsp.iota0) - (i_slow73)) & (S32(255))])) - (((slow74) * (dsp.rec35[S32(1)])) + ((dsp.const2) * (dsp.rec35[S32(2)])))
            dsp.rec34[S32(0)] = (dsp.const3) * ((dsp.rec35[S32(0)]) - (dsp.rec35[S32(2)]))
            var temp14 = (F64(2.1900357)) * (temp0)
            dsp.vec28[(dsp.iota0) & (S32(1023))] = (temp14) + ((slow2) * (dsp.rec36[S32(1)]))
            dsp.rec37[S32(0)] = ((slow75) * (dsp.vec28[((dsp.iota0) - (i_slow76)) & (S32(1023))])) - (((slow77) * (dsp.rec37[S32(1)])) + ((dsp.const2) * (dsp.rec37[S32(2)])))
            dsp.rec36[S32(0)] = (dsp.const3) * ((dsp.rec37[S32(0)]) - (dsp.rec37[S32(2)]))
            dsp.vec29[(dsp.iota0) & (S32(1023))] = ((slow2) * (dsp.rec38[S32(1)])) + (temp14)
            dsp.rec39[S32(0)] = ((slow78) * (dsp.vec29[((dsp.iota0) - (i_slow79)) & (S32(1023))])) - (((slow80) * (dsp.rec39[S32(1)])) + ((dsp.const2) * (dsp.rec39[S32(2)])))
            dsp.rec38[S32(0)] = (dsp.const3) * ((dsp.rec39[S32(0)]) - (dsp.rec39[S32(2)]))
            var temp15 = (F64(6.7063036)) * (temp1)
            dsp.vec30[(dsp.iota0) & (S32(63))] = (temp15) + ((slow2) * (dsp.rec40[S32(1)]))
            dsp.rec41[S32(0)] = ((slow81) * (dsp.vec30[((dsp.iota0) - (i_slow82)) & (S32(63))])) - (((slow83) * (dsp.rec41[S32(1)])) + ((dsp.const2) * (dsp.rec41[S32(2)])))
            dsp.rec40[S32(0)] = (dsp.const3) * ((dsp.rec41[S32(0)]) - (dsp.rec41[S32(2)]))
            dsp.vec31[(dsp.iota0) & (S32(63))] = ((slow2) * (dsp.rec42[S32(1)])) + (temp15)
            dsp.rec43[S32(0)] = ((slow84) * (dsp.vec31[((dsp.iota0) - (i_slow85)) & (S32(63))])) - (((slow86) * (dsp.rec43[S32(1)])) + ((dsp.const2) * (dsp.rec43[S32(2)])))
            dsp.rec42[S32(0)] = (dsp.const3) * ((dsp.rec43[S32(0)]) - (dsp.rec43[S32(2)]))
            var temp16 = (F64(1.7063034)) * (temp1)
            dsp.vec32[(dsp.iota0) & (S32(63))] = (temp16) + ((slow2) * (dsp.rec44[S32(1)]))
            dsp.rec45[S32(0)] = ((slow87) * (dsp.vec32[((dsp.iota0) - (i_slow88)) & (S32(63))])) - (((slow89) * (dsp.rec45[S32(1)])) + ((dsp.const2) * (dsp.rec45[S32(2)])))
            dsp.rec44[S32(0)] = (dsp.const3) * ((dsp.rec45[S32(0)]) - (dsp.rec45[S32(2)]))
            dsp.vec33[(dsp.iota0) & (S32(63))] = ((slow2) * (dsp.rec46[S32(1)])) + (temp16)
            dsp.rec47[S32(0)] = ((slow90) * (dsp.vec33[((dsp.iota0) - (i_slow91)) & (S32(63))])) - (((slow92) * (dsp.rec47[S32(1)])) + ((dsp.const2) * (dsp.rec47[S32(2)])))
            dsp.rec46[S32(0)] = (dsp.const3) * ((dsp.rec47[S32(0)]) - (dsp.rec47[S32(2)]))
            var temp17 = (F64(5.0063033)) * (temp1)
            dsp.vec34[(dsp.iota0) & (S32(127))] = (temp17) + ((slow2) * (dsp.rec48[S32(1)]))
            dsp.rec49[S32(0)] = ((slow93) * (dsp.vec34[((dsp.iota0) - (i_slow94)) & (S32(127))])) - (((slow95) * (dsp.rec49[S32(1)])) + ((dsp.const2) * (dsp.rec49[S32(2)])))
            dsp.rec48[S32(0)] = (dsp.const3) * ((dsp.rec49[S32(0)]) - (dsp.rec49[S32(2)]))
            dsp.vec35[(dsp.iota0) & (S32(127))] = ((slow2) * (dsp.rec50[S32(1)])) + (temp17)
            dsp.rec51[S32(0)] = ((slow96) * (dsp.vec35[((dsp.iota0) - (i_slow97)) & (S32(127))])) - (((slow98) * (dsp.rec51[S32(1)])) + ((dsp.const2) * (dsp.rec51[S32(2)])))
            dsp.rec50[S32(0)] = (dsp.const3) * ((dsp.rec51[S32(0)]) - (dsp.rec51[S32(2)]))
            var temp18 = (F64(2.0914886)) * (temp1)
            dsp.vec36[(dsp.iota0) & (S32(255))] = (temp18) + ((slow2) * (dsp.rec52[S32(1)]))
            dsp.rec53[S32(0)] = ((slow99) * (dsp.vec36[((dsp.iota0) - (i_slow100)) & (S32(255))])) - (((slow101) * (dsp.rec53[S32(1)])) + ((dsp.const2) * (dsp.rec53[S32(2)])))
            dsp.rec52[S32(0)] = (dsp.const3) * ((dsp.rec53[S32(0)]) - (dsp.rec53[S32(2)]))
            dsp.vec37[(dsp.iota0) & (S32(255))] = ((slow2) * (dsp.rec54[S32(1)])) + (temp18)
            dsp.rec55[S32(0)] = ((slow102) * (dsp.vec37[((dsp.iota0) - (i_slow103)) & (S32(255))])) - (((slow104) * (dsp.rec55[S32(1)])) + ((dsp.const2) * (dsp.rec55[S32(2)])))
            dsp.rec54[S32(0)] = (dsp.const3) * ((dsp.rec55[S32(0)]) - (dsp.rec55[S32(2)]))
            var temp19 = (F64(2.1900357)) * (temp1)
            dsp.vec38[(dsp.iota0) & (S32(1023))] = (temp19) + ((slow2) * (dsp.rec56[S32(1)]))
            dsp.rec57[S32(0)] = ((slow105) * (dsp.vec38[((dsp.iota0) - (i_slow106)) & (S32(1023))])) - (((slow107) * (dsp.rec57[S32(1)])) + ((dsp.const2) * (dsp.rec57[S32(2)])))
            dsp.rec56[S32(0)] = (dsp.const3) * ((dsp.rec57[S32(0)]) - (dsp.rec57[S32(2)]))
            dsp.vec39[(dsp.iota0) & (S32(1023))] = ((slow2) * (dsp.rec58[S32(1)])) + (temp19)
            dsp.rec59[S32(0)] = ((slow108) * (dsp.vec39[((dsp.iota0) - (i_slow109)) & (S32(1023))])) - (((slow110) * (dsp.rec59[S32(1)])) + ((dsp.const2) * (dsp.rec59[S32(2)])))
            dsp.rec58[S32(0)] = (dsp.const3) * ((dsp.rec59[S32(0)]) - (dsp.rec59[S32(2)]))
            var temp20 = (F64(6.7063036)) * (temp2)
            dsp.vec40[(dsp.iota0) & (S32(63))] = (temp20) + ((slow2) * (dsp.rec60[S32(1)]))
            dsp.rec61[S32(0)] = ((slow111) * (dsp.vec40[((dsp.iota0) - (i_slow112)) & (S32(63))])) - (((slow113) * (dsp.rec61[S32(1)])) + ((dsp.const2) * (dsp.rec61[S32(2)])))
            dsp.rec60[S32(0)] = (dsp.const3) * ((dsp.rec61[S32(0)]) - (dsp.rec61[S32(2)]))
            dsp.vec41[(dsp.iota0) & (S32(63))] = ((slow2) * (dsp.rec62[S32(1)])) + (temp20)
            dsp.rec63[S32(0)] = ((slow114) * (dsp.vec41[((dsp.iota0) - (i_slow115)) & (S32(63))])) - (((slow116) * (dsp.rec63[S32(1)])) + ((dsp.const2) * (dsp.rec63[S32(2)])))
            dsp.rec62[S32(0)] = (dsp.const3) * ((dsp.rec63[S32(0)]) - (dsp.rec63[S32(2)]))
            var temp21 = (F64(1.7063034)) * (temp2)
            dsp.vec42[(dsp.iota0) & (S32(63))] = (temp21) + ((slow2) * (dsp.rec64[S32(1)]))
            dsp.rec65[S32(0)] = ((slow117) * (dsp.vec42[((dsp.iota0) - (i_slow118)) & (S32(63))])) - (((slow119) * (dsp.rec65[S32(1)])) + ((dsp.const2) * (dsp.rec65[S32(2)])))
            dsp.rec64[S32(0)] = (dsp.const3) * ((dsp.rec65[S32(0)]) - (dsp.rec65[S32(2)]))
            dsp.vec43[(dsp.iota0) & (S32(63))] = ((slow2) * (dsp.rec66[S32(1)])) + (temp21)
            dsp.rec67[S32(0)] = ((slow120) * (dsp.vec43[((dsp.iota0) - (i_slow121)) & (S32(63))])) - (((slow122) * (dsp.rec67[S32(1)])) + ((dsp.const2) * (dsp.rec67[S32(2)])))
            dsp.rec66[S32(0)] = (dsp.const3) * ((dsp.rec67[S32(0)]) - (dsp.rec67[S32(2)]))
            var temp22 = (F64(5.0063033)) * (temp2)
            dsp.vec44[(dsp.iota0) & (S32(127))] = (temp22) + ((slow2) * (dsp.rec68[S32(1)]))
            dsp.rec69[S32(0)] = ((slow123) * (dsp.vec44[((dsp.iota0) - (i_slow124)) & (S32(127))])) - (((slow125) * (dsp.rec69[S32(1)])) + ((dsp.const2) * (dsp.rec69[S32(2)])))
            dsp.rec68[S32(0)] = (dsp.const3) * ((dsp.rec69[S32(0)]) - (dsp.rec69[S32(2)]))
            dsp.vec45[(dsp.iota0) & (S32(127))] = ((slow2) * (dsp.rec70[S32(1)])) + (temp22)
            dsp.rec71[S32(0)] = ((slow126) * (dsp.vec45[((dsp.iota0) - (i_slow127)) & (S32(127))])) - (((slow128) * (dsp.rec71[S32(1)])) + ((dsp.const2) * (dsp.rec71[S32(2)])))
            dsp.rec70[S32(0)] = (dsp.const3) * ((dsp.rec71[S32(0)]) - (dsp.rec71[S32(2)]))
            var temp23 = (F64(2.0914886)) * (temp2)
            dsp.vec46[(dsp.iota0) & (S32(255))] = (temp23) + ((slow2) * (dsp.rec72[S32(1)]))
            dsp.rec73[S32(0)] = ((slow129) * (dsp.vec46[((dsp.iota0) - (i_slow130)) & (S32(255))])) - (((slow131) * (dsp.rec73[S32(1)])) + ((dsp.const2) * (dsp.rec73[S32(2)])))
            dsp.rec72[S32(0)] = (dsp.const3) * ((dsp.rec73[S32(0)]) - (dsp.rec73[S32(2)]))
            dsp.vec47[(dsp.iota0) & (S32(255))] = ((slow2) * (dsp.rec74[S32(1)])) + (temp23)
            dsp.rec75[S32(0)] = ((slow132) * (dsp.vec47[((dsp.iota0) - (i_slow133)) & (S32(255))])) - (((slow134) * (dsp.rec75[S32(1)])) + ((dsp.const2) * (dsp.rec75[S32(2)])))
            dsp.rec74[S32(0)] = (dsp.const3) * ((dsp.rec75[S32(0)]) - (dsp.rec75[S32(2)]))
            var temp24 = (F64(2.1900357)) * (temp2)
            dsp.vec48[(dsp.iota0) & (S32(1023))] = (temp24) + ((slow2) * (dsp.rec76[S32(1)]))
            dsp.rec77[S32(0)] = ((slow135) * (dsp.vec48[((dsp.iota0) - (i_slow136)) & (S32(1023))])) - (((slow137) * (dsp.rec77[S32(1)])) + ((dsp.const2) * (dsp.rec77[S32(2)])))
            dsp.rec76[S32(0)] = (dsp.const3) * ((dsp.rec77[S32(0)]) - (dsp.rec77[S32(2)]))
            dsp.vec49[(dsp.iota0) & (S32(1023))] = ((slow2) * (dsp.rec78[S32(1)])) + (temp24)
            dsp.rec79[S32(0)] = ((slow138) * (dsp.vec49[((dsp.iota0) - (i_slow139)) & (S32(1023))])) - (((slow140) * (dsp.rec79[S32(1)])) + ((dsp.const2) * (dsp.rec79[S32(2)])))
            dsp.rec78[S32(0)] = (dsp.const3) * ((dsp.rec79[S32(0)]) - (dsp.rec79[S32(2)]))
            var temp25 = (F64(6.7063036)) * (temp3)
            dsp.vec50[(dsp.iota0) & (S32(63))] = (temp25) + ((slow2) * (dsp.rec80[S32(1)]))
            dsp.rec81[S32(0)] = ((slow141) * (dsp.vec50[((dsp.iota0) - (i_slow142)) & (S32(63))])) - (((slow143) * (dsp.rec81[S32(1)])) + ((dsp.const2) * (dsp.rec81[S32(2)])))
            dsp.rec80[S32(0)] = (dsp.const3) * ((dsp.rec81[S32(0)]) - (dsp.rec81[S32(2)]))
            dsp.vec51[(dsp.iota0) & (S32(63))] = ((slow2) * (dsp.rec82[S32(1)])) + (temp25)
            dsp.rec83[S32(0)] = ((slow144) * (dsp.vec51[((dsp.iota0) - (i_slow145)) & (S32(63))])) - (((slow146) * (dsp.rec83[S32(1)])) + ((dsp.const2) * (dsp.rec83[S32(2)])))
            dsp.rec82[S32(0)] = (dsp.const3) * ((dsp.rec83[S32(0)]) - (dsp.rec83[S32(2)]))
            var temp26 = (F64(1.7063034)) * (temp3)
            dsp.vec52[(dsp.iota0) & (S32(63))] = (temp26) + ((slow2) * (dsp.rec84[S32(1)]))
            dsp.rec85[S32(0)] = ((slow147) * (dsp.vec52[((dsp.iota0) - (i_slow148)) & (S32(63))])) - (((slow149) * (dsp.rec85[S32(1)])) + ((dsp.const2) * (dsp.rec85[S32(2)])))
            dsp.rec84[S32(0)] = (dsp.const3) * ((dsp.rec85[S32(0)]) - (dsp.rec85[S32(2)]))
            dsp.vec53[(dsp.iota0) & (S32(63))] = ((slow2) * (dsp.rec86[S32(1)])) + (temp26)
            dsp.rec87[S32(0)] = ((slow150) * (dsp.vec53[((dsp.iota0) - (i_slow151)) & (S32(63))])) - (((slow152) * (dsp.rec87[S32(1)])) + ((dsp.const2) * (dsp.rec87[S32(2)])))
            dsp.rec86[S32(0)] = (dsp.const3) * ((dsp.rec87[S32(0)]) - (dsp.rec87[S32(2)]))
            var temp27 = (F64(5.0063033)) * (temp3)
            dsp.vec54[(dsp.iota0) & (S32(127))] = (temp27) + ((slow2) * (dsp.rec88[S32(1)]))
            dsp.rec89[S32(0)] = ((slow153) * (dsp.vec54[((dsp.iota0) - (i_slow154)) & (S32(127))])) - (((slow155) * (dsp.rec89[S32(1)])) + ((dsp.const2) * (dsp.rec89[S32(2)])))
            dsp.rec88[S32(0)] = (dsp.const3) * ((dsp.rec89[S32(0)]) - (dsp.rec89[S32(2)]))
            dsp.vec55[(dsp.iota0) & (S32(127))] = ((slow2) * (dsp.rec90[S32(1)])) + (temp27)
            dsp.rec91[S32(0)] = ((slow156) * (dsp.vec55[((dsp.iota0) - (i_slow157)) & (S32(127))])) - (((slow158) * (dsp.rec91[S32(1)])) + ((dsp.const2) * (dsp.rec91[S32(2)])))
            dsp.rec90[S32(0)] = (dsp.const3) * ((dsp.rec91[S32(0)]) - (dsp.rec91[S32(2)]))
            var temp28 = (F64(2.0914886)) * (temp3)
            dsp.vec56[(dsp.iota0) & (S32(255))] = (temp28) + ((slow2) * (dsp.rec92[S32(1)]))
            dsp.rec93[S32(0)] = ((slow159) * (dsp.vec56[((dsp.iota0) - (i_slow160)) & (S32(255))])) - (((slow161) * (dsp.rec93[S32(1)])) + ((dsp.const2) * (dsp.rec93[S32(2)])))
            dsp.rec92[S32(0)] = (dsp.const3) * ((dsp.rec93[S32(0)]) - (dsp.rec93[S32(2)]))
            dsp.vec57[(dsp.iota0) & (S32(255))] = ((slow2) * (dsp.rec94[S32(1)])) + (temp28)
            dsp.rec95[S32(0)] = ((slow162) * (dsp.vec57[((dsp.iota0) - (i_slow163)) & (S32(255))])) - (((slow164) * (dsp.rec95[S32(1)])) + ((dsp.const2) * (dsp.rec95[S32(2)])))
            dsp.rec94[S32(0)] = (dsp.const3) * ((dsp.rec95[S32(0)]) - (dsp.rec95[S32(2)]))
            var temp29 = (F64(2.1900357)) * (temp3)
            dsp.vec58[(dsp.iota0) & (S32(1023))] = (temp29) + ((slow2) * (dsp.rec96[S32(1)]))
            dsp.rec97[S32(0)] = ((slow165) * (dsp.vec58[((dsp.iota0) - (i_slow166)) & (S32(1023))])) - (((slow167) * (dsp.rec97[S32(1)])) + ((dsp.const2) * (dsp.rec97[S32(2)])))
            dsp.rec96[S32(0)] = (dsp.const3) * ((dsp.rec97[S32(0)]) - (dsp.rec97[S32(2)]))
            dsp.vec59[(dsp.iota0) & (S32(1023))] = ((slow2) * (dsp.rec98[S32(1)])) + (temp29)
            dsp.rec99[S32(0)] = ((slow168) * (dsp.vec59[((dsp.iota0) - (i_slow169)) & (S32(1023))])) - (((slow170) * (dsp.rec99[S32(1)])) + ((dsp.const2) * (dsp.rec99[S32(2)])))
            dsp.rec98[S32(0)] = (dsp.const3) * ((dsp.rec99[S32(0)]) - (dsp.rec99[S32(2)]))
            var temp30 = (F64(6.7063036)) * (temp4)
            dsp.vec60[(dsp.iota0) & (S32(63))] = (temp30) + ((slow2) * (dsp.rec100[S32(1)]))
            dsp.rec101[S32(0)] = ((slow171) * (dsp.vec60[((dsp.iota0) - (i_slow172)) & (S32(63))])) - (((slow173) * (dsp.rec101[S32(1)])) + ((dsp.const2) * (dsp.rec101[S32(2)])))
            dsp.rec100[S32(0)] = (dsp.const3) * ((dsp.rec101[S32(0)]) - (dsp.rec101[S32(2)]))
            dsp.vec61[(dsp.iota0) & (S32(63))] = ((slow2) * (dsp.rec102[S32(1)])) + (temp30)
            dsp.rec103[S32(0)] = ((slow174) * (dsp.vec61[((dsp.iota0) - (i_slow175)) & (S32(63))])) - (((slow176) * (dsp.rec103[S32(1)])) + ((dsp.const2) * (dsp.rec103[S32(2)])))
            dsp.rec102[S32(0)] = (dsp.const3) * ((dsp.rec103[S32(0)]) - (dsp.rec103[S32(2)]))
            var temp31 = (F64(1.7063034)) * (temp4)
            dsp.vec62[(dsp.iota0) & (S32(63))] = (temp31) + ((slow2) * (dsp.rec104[S32(1)]))
            dsp.rec105[S32(0)] = ((slow177) * (dsp.vec62[((dsp.iota0) - (i_slow178)) & (S32(63))])) - (((slow179) * (dsp.rec105[S32(1)])) + ((dsp.const2) * (dsp.rec105[S32(2)])))
            dsp.rec104[S32(0)] = (dsp.const3) * ((dsp.rec105[S32(0)]) - (dsp.rec105[S32(2)]))
            dsp.vec63[(dsp.iota0) & (S32(63))] = ((slow2) * (dsp.rec106[S32(1)])) + (temp31)
            dsp.rec107[S32(0)] = ((slow180) * (dsp.vec63[((dsp.iota0) - (i_slow181)) & (S32(63))])) - (((slow182) * (dsp.rec107[S32(1)])) + ((dsp.const2) * (dsp.rec107[S32(2)])))
            dsp.rec106[S32(0)] = (dsp.const3) * ((dsp.rec107[S32(0)]) - (dsp.rec107[S32(2)]))
            var temp32 = (F64(5.0063033)) * (temp4)
            dsp.vec64[(dsp.iota0) & (S32(127))] = (temp32) + ((slow2) * (dsp.rec108[S32(1)]))
            dsp.rec109[S32(0)] = ((slow183) * (dsp.vec64[((dsp.iota0) - (i_slow184)) & (S32(127))])) - (((slow185) * (dsp.rec109[S32(1)])) + ((dsp.const2) * (dsp.rec109[S32(2)])))
            dsp.rec108[S32(0)] = (dsp.const3) * ((dsp.rec109[S32(0)]) - (dsp.rec109[S32(2)]))
            dsp.vec65[(dsp.iota0) & (S32(127))] = ((slow2) * (dsp.rec110[S32(1)])) + (temp32)
            dsp.rec111[S32(0)] = ((slow186) * (dsp.vec65[((dsp.iota0) - (i_slow187)) & (S32(127))])) - (((slow188) * (dsp.rec111[S32(1)])) + ((dsp.const2) * (dsp.rec111[S32(2)])))
            dsp.rec110[S32(0)] = (dsp.const3) * ((dsp.rec111[S32(0)]) - (dsp.rec111[S32(2)]))
            var temp33 = (F64(2.0914886)) * (temp4)
            dsp.vec66[(dsp.iota0) & (S32(255))] = (temp33) + ((slow2) * (dsp.rec112[S32(1)]))
            dsp.rec113[S32(0)] = ((slow189) * (dsp.vec66[((dsp.iota0) - (i_slow190)) & (S32(255))])) - (((slow191) * (dsp.rec113[S32(1)])) + ((dsp.const2) * (dsp.rec113[S32(2)])))
            dsp.rec112[S32(0)] = (dsp.const3) * ((dsp.rec113[S32(0)]) - (dsp.rec113[S32(2)]))
            dsp.vec67[(dsp.iota0) & (S32(255))] = ((slow2) * (dsp.rec114[S32(1)])) + (temp33)
            dsp.rec115[S32(0)] = ((slow192) * (dsp.vec67[((dsp.iota0) - (i_slow193)) & (S32(255))])) - (((slow194) * (dsp.rec115[S32(1)])) + ((dsp.const2) * (dsp.rec115[S32(2)])))
            dsp.rec114[S32(0)] = (dsp.const3) * ((dsp.rec115[S32(0)]) - (dsp.rec115[S32(2)]))
            var temp34 = (F64(2.1900357)) * (temp4)
            dsp.vec68[(dsp.iota0) & (S32(1023))] = (temp34) + ((slow2) * (dsp.rec116[S32(1)]))
            dsp.rec117[S32(0)] = ((slow195) * (dsp.vec68[((dsp.iota0) - (i_slow196)) & (S32(1023))])) - (((slow197) * (dsp.rec117[S32(1)])) + ((dsp.const2) * (dsp.rec117[S32(2)])))
            dsp.rec116[S32(0)] = (dsp.const3) * ((dsp.rec117[S32(0)]) - (dsp.rec117[S32(2)]))
            dsp.vec69[(dsp.iota0) & (S32(1023))] = ((slow2) * (dsp.rec118[S32(1)])) + (temp34)
            dsp.rec119[S32(0)] = ((slow198) * (dsp.vec69[((dsp.iota0) - (i_slow199)) & (S32(1023))])) - (((slow200) * (dsp.rec119[S32(1)])) + ((dsp.const2) * (dsp.rec119[S32(2)])))
            dsp.rec118[S32(0)] = (dsp.const3) * ((dsp.rec119[S32(0)]) - (dsp.rec119[S32(2)]))
            var temp35 = (F64(6.7063036)) * (temp5)
            dsp.vec70[(dsp.iota0) & (S32(63))] = (temp35) + ((slow2) * (dsp.rec120[S32(1)]))
            dsp.rec121[S32(0)] = ((slow201) * (dsp.vec70[((dsp.iota0) - (i_slow202)) & (S32(63))])) - (((slow203) * (dsp.rec121[S32(1)])) + ((dsp.const2) * (dsp.rec121[S32(2)])))
            dsp.rec120[S32(0)] = (dsp.const3) * ((dsp.rec121[S32(0)]) - (dsp.rec121[S32(2)]))
            dsp.vec71[(dsp.iota0) & (S32(63))] = ((slow2) * (dsp.rec122[S32(1)])) + (temp35)
            dsp.rec123[S32(0)] = ((slow204) * (dsp.vec71[((dsp.iota0) - (i_slow205)) & (S32(63))])) - (((slow206) * (dsp.rec123[S32(1)])) + ((dsp.const2) * (dsp.rec123[S32(2)])))
            dsp.rec122[S32(0)] = (dsp.const3) * ((dsp.rec123[S32(0)]) - (dsp.rec123[S32(2)]))
            var temp36 = (F64(1.7063034)) * (temp5)
            dsp.vec72[(dsp.iota0) & (S32(63))] = (temp36) + ((slow2) * (dsp.rec124[S32(1)]))
            dsp.rec125[S32(0)] = ((slow207) * (dsp.vec72[((dsp.iota0) - (i_slow208)) & (S32(63))])) - (((slow209) * (dsp.rec125[S32(1)])) + ((dsp.const2) * (dsp.rec125[S32(2)])))
            dsp.rec124[S32(0)] = (dsp.const3) * ((dsp.rec125[S32(0)]) - (dsp.rec125[S32(2)]))
            dsp.vec73[(dsp.iota0) & (S32(63))] = ((slow2) * (dsp.rec126[S32(1)])) + (temp36)
            dsp.rec127[S32(0)] = ((slow210) * (dsp.vec73[((dsp.iota0) - (i_slow211)) & (S32(63))])) - (((slow212) * (dsp.rec127[S32(1)])) + ((dsp.const2) * (dsp.rec127[S32(2)])))
            dsp.rec126[S32(0)] = (dsp.const3) * ((dsp.rec127[S32(0)]) - (dsp.rec127[S32(2)]))
            var temp37 = (F64(5.0063033)) * (temp5)
            dsp.vec74[(dsp.iota0) & (S32(127))] = (temp37) + ((slow2) * (dsp.rec128[S32(1)]))
            dsp.rec129[S32(0)] = ((slow213) * (dsp.vec74[((dsp.iota0) - (i_slow214)) & (S32(127))])) - (((slow215) * (dsp.rec129[S32(1)])) + ((dsp.const2) * (dsp.rec129[S32(2)])))
            dsp.rec128[S32(0)] = (dsp.const3) * ((dsp.rec129[S32(0)]) - (dsp.rec129[S32(2)]))
            dsp.vec75[(dsp.iota0) & (S32(127))] = ((slow2) * (dsp.rec130[S32(1)])) + (temp37)
            dsp.rec131[S32(0)] = ((slow216) * (dsp.vec75[((dsp.iota0) - (i_slow217)) & (S32(127))])) - (((slow218) * (dsp.rec131[S32(1)])) + ((dsp.const2) * (dsp.rec131[S32(2)])))
            dsp.rec130[S32(0)] = (dsp.const3) * ((dsp.rec131[S32(0)]) - (dsp.rec131[S32(2)]))
            var temp38 = (F64(2.0914886)) * (temp5)
            dsp.vec76[(dsp.iota0) & (S32(255))] = (temp38) + ((slow2) * (dsp.rec132[S32(1)]))
            dsp.rec133[S32(0)] = ((slow219) * (dsp.vec76[((dsp.iota0) - (i_slow220)) & (S32(255))])) - (((slow221) * (dsp.rec133[S32(1)])) + ((dsp.const2) * (dsp.rec133[S32(2)])))
            dsp.rec132[S32(0)] = (dsp.const3) * ((dsp.rec133[S32(0)]) - (dsp.rec133[S32(2)]))
            dsp.vec77[(dsp.iota0) & (S32(255))] = ((slow2) * (dsp.rec134[S32(1)])) + (temp38)
            dsp.rec135[S32(0)] = ((slow222) * (dsp.vec77[((dsp.iota0) - (i_slow223)) & (S32(255))])) - (((slow224) * (dsp.rec135[S32(1)])) + ((dsp.const2) * (dsp.rec135[S32(2)])))
            dsp.rec134[S32(0)] = (dsp.const3) * ((dsp.rec135[S32(0)]) - (dsp.rec135[S32(2)]))
            var temp39 = (F64(2.1900357)) * (temp5)
            dsp.vec78[(dsp.iota0) & (S32(1023))] = (temp39) + ((slow2) * (dsp.rec136[S32(1)]))
            dsp.rec137[S32(0)] = ((slow225) * (dsp.vec78[((dsp.iota0) - (i_slow226)) & (S32(1023))])) - (((slow227) * (dsp.rec137[S32(1)])) + ((dsp.const2) * (dsp.rec137[S32(2)])))
            dsp.rec136[S32(0)] = (dsp.const3) * ((dsp.rec137[S32(0)]) - (dsp.rec137[S32(2)]))
            dsp.vec79[(dsp.iota0) & (S32(1023))] = ((slow2) * (dsp.rec138[S32(1)])) + (temp39)
            dsp.rec139[S32(0)] = ((slow228) * (dsp.vec79[((dsp.iota0) - (i_slow229)) & (S32(1023))])) - (((slow230) * (dsp.rec139[S32(1)])) + ((dsp.const2) * (dsp.rec139[S32(2)])))
            dsp.rec138[S32(0)] = (dsp.const3) * ((dsp.rec139[S32(0)]) - (dsp.rec139[S32(2)]))
            var temp40 = (F64(6.7063036)) * (temp6)
            dsp.vec80[(dsp.iota0) & (S32(63))] = (temp40) + ((slow2) * (dsp.rec140[S32(1)]))
            dsp.rec141[S32(0)] = ((slow231) * (dsp.vec80[((dsp.iota0) - (i_slow232)) & (S32(63))])) - (((slow233) * (dsp.rec141[S32(1)])) + ((dsp.const2) * (dsp.rec141[S32(2)])))
            dsp.rec140[S32(0)] = (dsp.const3) * ((dsp.rec141[S32(0)]) - (dsp.rec141[S32(2)]))
            dsp.vec81[(dsp.iota0) & (S32(63))] = ((slow2) * (dsp.rec142[S32(1)])) + (temp40)
            dsp.rec143[S32(0)] = ((slow234) * (dsp.vec81[((dsp.iota0) - (i_slow235)) & (S32(63))])) - (((slow236) * (dsp.rec143[S32(1)])) + ((dsp.const2) * (dsp.rec143[S32(2)])))
            dsp.rec142[S32(0)] = (dsp.const3) * ((dsp.rec143[S32(0)]) - (dsp.rec143[S32(2)]))
            var temp41 = (F64(1.7063034)) * (temp6)
            dsp.vec82[(dsp.iota0) & (S32(63))] = (temp41) + ((slow2) * (dsp.rec144[S32(1)]))
            dsp.rec145[S32(0)] = ((slow237) * (dsp.vec82[((dsp.iota0) - (i_slow238)) & (S32(63))])) - (((slow239) * (dsp.rec145[S32(1)])) + ((dsp.const2) * (dsp.rec145[S32(2)])))
            dsp.rec144[S32(0)] = (dsp.const3) * ((dsp.rec145[S32(0)]) - (dsp.rec145[S32(2)]))
            dsp.vec83[(dsp.iota0) & (S32(63))] = ((slow2) * (dsp.rec146[S32(1)])) + (temp41)
            dsp.rec147[S32(0)] = ((slow240) * (dsp.vec83[((dsp.iota0) - (i_slow241)) & (S32(63))])) - (((slow242) * (dsp.rec147[S32(1)])) + ((dsp.const2) * (dsp.rec147[S32(2)])))
            dsp.rec146[S32(0)] = (dsp.const3) * ((dsp.rec147[S32(0)]) - (dsp.rec147[S32(2)]))
            var temp42 = (F64(5.0063033)) * (temp6)
            dsp.vec84[(dsp.iota0) & (S32(127))] = (temp42) + ((slow2) * (dsp.rec148[S32(1)]))
            dsp.rec149[S32(0)] = ((slow243) * (dsp.vec84[((dsp.iota0) - (i_slow244)) & (S32(127))])) - (((slow245) * (dsp.rec149[S32(1)])) + ((dsp.const2) * (dsp.rec149[S32(2)])))
            dsp.rec148[S32(0)] = (dsp.const3) * ((dsp.rec149[S32(0)]) - (dsp.rec149[S32(2)]))
            dsp.vec85[(dsp.iota0) & (S32(127))] = ((slow2) * (dsp.rec150[S32(1)])) + (temp42)
            dsp.rec151[S32(0)] = ((slow246) * (dsp.vec85[((dsp.iota0) - (i_slow247)) & (S32(127))])) - (((slow248) * (dsp.rec151[S32(1)])) + ((dsp.const2) * (dsp.rec151[S32(2)])))
            dsp.rec150[S32(0)] = (dsp.const3) * ((dsp.rec151[S32(0)]) - (dsp.rec151[S32(2)]))
            var temp43 = (F64(2.0914886)) * (temp6)
            dsp.vec86[(dsp.iota0) & (S32(255))] = (temp43) + ((slow2) * (dsp.rec152[S32(1)]))
            dsp.rec153[S32(0)] = ((slow249) * (dsp.vec86[((dsp.iota0) - (i_slow250)) & (S32(255))])) - (((slow251) * (dsp.rec153[S32(1)])) + ((dsp.const2) * (dsp.rec153[S32(2)])))
            dsp.rec152[S32(0)] = (dsp.const3) * ((dsp.rec153[S32(0)]) - (dsp.rec153[S32(2)]))
            dsp.vec87[(dsp.iota0) & (S32(255))] = ((slow2) * (dsp.rec154[S32(1)])) + (temp43)
            dsp.rec155[S32(0)] = ((slow252) * (dsp.vec87[((dsp.iota0) - (i_slow253)) & (S32(255))])) - (((slow254) * (dsp.rec155[S32(1)])) + ((dsp.const2) * (dsp.rec155[S32(2)])))
            dsp.rec154[S32(0)] = (dsp.const3) * ((dsp.rec155[S32(0)]) - (dsp.rec155[S32(2)]))
            var temp44 = (F64(2.1900357)) * (temp6)
            dsp.vec88[(dsp.iota0) & (S32(1023))] = (temp44) + ((slow2) * (dsp.rec156[S32(1)]))
            dsp.rec157[S32(0)] = ((slow255) * (dsp.vec88[((dsp.iota0) - (i_slow256)) & (S32(1023))])) - (((slow257) * (dsp.rec157[S32(1)])) + ((dsp.const2) * (dsp.rec157[S32(2)])))
            dsp.rec156[S32(0)] = (dsp.const3) * ((dsp.rec157[S32(0)]) - (dsp.rec157[S32(2)]))
            dsp.vec89[(dsp.iota0) & (S32(1023))] = ((slow2) * (dsp.rec158[S32(1)])) + (temp44)
            dsp.rec159[S32(0)] = ((slow258) * (dsp.vec89[((dsp.iota0) - (i_slow259)) & (S32(1023))])) - (((slow260) * (dsp.rec159[S32(1)])) + ((dsp.const2) * (dsp.rec159[S32(2)])))
            dsp.rec158[S32(0)] = (dsp.const3) * ((dsp.rec159[S32(0)]) - (dsp.rec159[S32(2)]))
            var temp45 = (F64(6.7063036)) * (temp7)
            dsp.vec90[(dsp.iota0) & (S32(63))] = (temp45) + ((slow2) * (dsp.rec160[S32(1)]))
            dsp.rec161[S32(0)] = ((slow261) * (dsp.vec90[((dsp.iota0) - (i_slow262)) & (S32(63))])) - (((slow263) * (dsp.rec161[S32(1)])) + ((dsp.const2) * (dsp.rec161[S32(2)])))
            dsp.rec160[S32(0)] = (dsp.const3) * ((dsp.rec161[S32(0)]) - (dsp.rec161[S32(2)]))
            dsp.vec91[(dsp.iota0) & (S32(63))] = ((slow2) * (dsp.rec162[S32(1)])) + (temp45)
            dsp.rec163[S32(0)] = ((slow264) * (dsp.vec91[((dsp.iota0) - (i_slow265)) & (S32(63))])) - (((slow266) * (dsp.rec163[S32(1)])) + ((dsp.const2) * (dsp.rec163[S32(2)])))
            dsp.rec162[S32(0)] = (dsp.const3) * ((dsp.rec163[S32(0)]) - (dsp.rec163[S32(2)]))
            var temp46 = (F64(1.7063034)) * (temp7)
            dsp.vec92[(dsp.iota0) & (S32(63))] = (temp46) + ((slow2) * (dsp.rec164[S32(1)]))
            dsp.rec165[S32(0)] = ((slow267) * (dsp.vec92[((dsp.iota0) - (i_slow268)) & (S32(63))])) - (((slow269) * (dsp.rec165[S32(1)])) + ((dsp.const2) * (dsp.rec165[S32(2)])))
            dsp.rec164[S32(0)] = (dsp.const3) * ((dsp.rec165[S32(0)]) - (dsp.rec165[S32(2)]))
            dsp.vec93[(dsp.iota0) & (S32(63))] = ((slow2) * (dsp.rec166[S32(1)])) + (temp46)
            dsp.rec167[S32(0)] = ((slow270) * (dsp.vec93[((dsp.iota0) - (i_slow271)) & (S32(63))])) - (((slow272) * (dsp.rec167[S32(1)])) + ((dsp.const2) * (dsp.rec167[S32(2)])))
            dsp.rec166[S32(0)] = (dsp.const3) * ((dsp.rec167[S32(0)]) - (dsp.rec167[S32(2)]))
            var temp47 = (F64(5.0063033)) * (temp7)
            dsp.vec94[(dsp.iota0) & (S32(127))] = (temp47) + ((slow2) * (dsp.rec168[S32(1)]))
            dsp.rec169[S32(0)] = ((slow273) * (dsp.vec94[((dsp.iota0) - (i_slow274)) & (S32(127))])) - (((slow275) * (dsp.rec169[S32(1)])) + ((dsp.const2) * (dsp.rec169[S32(2)])))
            dsp.rec168[S32(0)] = (dsp.const3) * ((dsp.rec169[S32(0)]) - (dsp.rec169[S32(2)]))
            dsp.vec95[(dsp.iota0) & (S32(127))] = ((slow2) * (dsp.rec170[S32(1)])) + (temp47)
            dsp.rec171[S32(0)] = ((slow276) * (dsp.vec95[((dsp.iota0) - (i_slow277)) & (S32(127))])) - (((slow278) * (dsp.rec171[S32(1)])) + ((dsp.const2) * (dsp.rec171[S32(2)])))
            dsp.rec170[S32(0)] = (dsp.const3) * ((dsp.rec171[S32(0)]) - (dsp.rec171[S32(2)]))
            var temp48 = (F64(2.0914886)) * (temp7)
            dsp.vec96[(dsp.iota0) & (S32(255))] = (temp48) + ((slow2) * (dsp.rec172[S32(1)]))
            dsp.rec173[S32(0)] = ((slow279) * (dsp.vec96[((dsp.iota0) - (i_slow280)) & (S32(255))])) - (((slow281) * (dsp.rec173[S32(1)])) + ((dsp.const2) * (dsp.rec173[S32(2)])))
            dsp.rec172[S32(0)] = (dsp.const3) * ((dsp.rec173[S32(0)]) - (dsp.rec173[S32(2)]))
            dsp.vec97[(dsp.iota0) & (S32(255))] = ((slow2) * (dsp.rec174[S32(1)])) + (temp48)
            dsp.rec175[S32(0)] = ((slow282) * (dsp.vec97[((dsp.iota0) - (i_slow283)) & (S32(255))])) - (((slow284) * (dsp.rec175[S32(1)])) + ((dsp.const2) * (dsp.rec175[S32(2)])))
            dsp.rec174[S32(0)] = (dsp.const3) * ((dsp.rec175[S32(0)]) - (dsp.rec175[S32(2)]))
            var temp49 = (F64(2.1900357)) * (temp7)
            dsp.vec98[(dsp.iota0) & (S32(1023))] = (temp49) + ((slow2) * (dsp.rec176[S32(1)]))
            dsp.rec177[S32(0)] = ((slow285) * (dsp.vec98[((dsp.iota0) - (i_slow286)) & (S32(1023))])) - (((slow287) * (dsp.rec177[S32(1)])) + ((dsp.const2) * (dsp.rec177[S32(2)])))
            dsp.rec176[S32(0)] = (dsp.const3) * ((dsp.rec177[S32(0)]) - (dsp.rec177[S32(2)]))
            dsp.vec99[(dsp.iota0) & (S32(1023))] = ((slow2) * (dsp.rec178[S32(1)])) + (temp49)
            dsp.rec179[S32(0)] = ((slow288) * (dsp.vec99[((dsp.iota0) - (i_slow289)) & (S32(1023))])) - (((slow290) * (dsp.rec179[S32(1)])) + ((dsp.const2) * (dsp.rec179[S32(2)])))
            dsp.rec178[S32(0)] = (dsp.const3) * ((dsp.rec179[S32(0)]) - (dsp.rec179[S32(2)]))
            var temp50 = (F64(6.7063036)) * (temp9)
            dsp.vec100[(dsp.iota0) & (S32(63))] = (temp50) + ((slow2) * (dsp.rec180[S32(1)]))
            dsp.rec181[S32(0)] = ((slow291) * (dsp.vec100[((dsp.iota0) - (i_slow292)) & (S32(63))])) - (((slow293) * (dsp.rec181[S32(1)])) + ((dsp.const2) * (dsp.rec181[S32(2)])))
            dsp.rec180[S32(0)] = (dsp.const3) * ((dsp.rec181[S32(0)]) - (dsp.rec181[S32(2)]))
            dsp.vec101[(dsp.iota0) & (S32(63))] = ((slow2) * (dsp.rec182[S32(1)])) + (temp50)
            dsp.rec183[S32(0)] = ((slow294) * (dsp.vec101[((dsp.iota0) - (i_slow295)) & (S32(63))])) - (((slow296) * (dsp.rec183[S32(1)])) + ((dsp.const2) * (dsp.rec183[S32(2)])))
            dsp.rec182[S32(0)] = (dsp.const3) * ((dsp.rec183[S32(0)]) - (dsp.rec183[S32(2)]))
            var temp51 = (F64(1.7063034)) * (temp9)
            dsp.vec102[(dsp.iota0) & (S32(63))] = (temp51) + ((slow2) * (dsp.rec184[S32(1)]))
            dsp.rec185[S32(0)] = ((slow297) * (dsp.vec102[((dsp.iota0) - (i_slow298)) & (S32(63))])) - (((slow299) * (dsp.rec185[S32(1)])) + ((dsp.const2) * (dsp.rec185[S32(2)])))
            dsp.rec184[S32(0)] = (dsp.const3) * ((dsp.rec185[S32(0)]) - (dsp.rec185[S32(2)]))
            dsp.vec103[(dsp.iota0) & (S32(63))] = ((slow2) * (dsp.rec186[S32(1)])) + (temp51)
            dsp.rec187[S32(0)] = ((slow300) * (dsp.vec103[((dsp.iota0) - (i_slow301)) & (S32(63))])) - (((slow302) * (dsp.rec187[S32(1)])) + ((dsp.const2) * (dsp.rec187[S32(2)])))
            dsp.rec186[S32(0)] = (dsp.const3) * ((dsp.rec187[S32(0)]) - (dsp.rec187[S32(2)]))
            var temp52 = (F64(5.0063033)) * (temp9)
            dsp.vec104[(dsp.iota0) & (S32(127))] = (temp52) + ((slow2) * (dsp.rec188[S32(1)]))
            dsp.rec189[S32(0)] = ((slow303) * (dsp.vec104[((dsp.iota0) - (i_slow304)) & (S32(127))])) - (((slow305) * (dsp.rec189[S32(1)])) + ((dsp.const2) * (dsp.rec189[S32(2)])))
            dsp.rec188[S32(0)] = (dsp.const3) * ((dsp.rec189[S32(0)]) - (dsp.rec189[S32(2)]))
            dsp.vec105[(dsp.iota0) & (S32(127))] = ((slow2) * (dsp.rec190[S32(1)])) + (temp52)
            dsp.rec191[S32(0)] = ((slow306) * (dsp.vec105[((dsp.iota0) - (i_slow307)) & (S32(127))])) - (((slow308) * (dsp.rec191[S32(1)])) + ((dsp.const2) * (dsp.rec191[S32(2)])))
            dsp.rec190[S32(0)] = (dsp.const3) * ((dsp.rec191[S32(0)]) - (dsp.rec191[S32(2)]))
            var temp53 = (F64(2.0914886)) * (temp9)
            dsp.vec106[(dsp.iota0) & (S32(255))] = (temp53) + ((slow2) * (dsp.rec192[S32(1)]))
            dsp.rec193[S32(0)] = ((slow309) * (dsp.vec106[((dsp.iota0) - (i_slow310)) & (S32(255))])) - (((slow311) * (dsp.rec193[S32(1)])) + ((dsp.const2) * (dsp.rec193[S32(2)])))
            dsp.rec192[S32(0)] = (dsp.const3) * ((dsp.rec193[S32(0)]) - (dsp.rec193[S32(2)]))
            dsp.vec107[(dsp.iota0) & (S32(255))] = ((slow2) * (dsp.rec194[S32(1)])) + (temp53)
            dsp.rec195[S32(0)] = ((slow312) * (dsp.vec107[((dsp.iota0) - (i_slow313)) & (S32(255))])) - (((slow314) * (dsp.rec195[S32(1)])) + ((dsp.const2) * (dsp.rec195[S32(2)])))
            dsp.rec194[S32(0)] = (dsp.const3) * ((dsp.rec195[S32(0)]) - (dsp.rec195[S32(2)]))
            var temp54 = (F64(2.1900357)) * (temp9)
            dsp.vec108[(dsp.iota0) & (S32(1023))] = (temp54) + ((slow2) * (dsp.rec196[S32(1)]))
            dsp.rec197[S32(0)] = ((slow315) * (dsp.vec108[((dsp.iota0) - (i_slow316)) & (S32(1023))])) - (((slow317) * (dsp.rec197[S32(1)])) + ((dsp.const2) * (dsp.rec197[S32(2)])))
            dsp.rec196[S32(0)] = (dsp.const3) * ((dsp.rec197[S32(0)]) - (dsp.rec197[S32(2)]))
            dsp.vec109[(dsp.iota0) & (S32(1023))] = ((slow2) * (dsp.rec198[S32(1)])) + (temp54)
            dsp.rec199[S32(0)] = ((slow318) * (dsp.vec109[((dsp.iota0) - (i_slow319)) & (S32(1023))])) - (((slow320) * (dsp.rec199[S32(1)])) + ((dsp.const2) * (dsp.rec199[S32(2)])))
            dsp.rec198[S32(0)] = (dsp.const3) * ((dsp.rec199[S32(0)]) - (dsp.rec199[S32(2)]))
            var temp55 = (F64(6.7063036)) * (temp8)
            dsp.vec110[(dsp.iota0) & (S32(63))] = (temp55) + ((slow2) * (dsp.rec200[S32(1)]))
            dsp.rec201[S32(0)] = ((slow321) * (dsp.vec110[((dsp.iota0) - (i_slow322)) & (S32(63))])) - (((slow323) * (dsp.rec201[S32(1)])) + ((dsp.const2) * (dsp.rec201[S32(2)])))
            dsp.rec200[S32(0)] = (dsp.const3) * ((dsp.rec201[S32(0)]) - (dsp.rec201[S32(2)]))
            dsp.vec111[(dsp.iota0) & (S32(63))] = ((slow2) * (dsp.rec202[S32(1)])) + (temp55)
            dsp.rec203[S32(0)] = ((slow324) * (dsp.vec111[((dsp.iota0) - (i_slow325)) & (S32(63))])) - (((slow326) * (dsp.rec203[S32(1)])) + ((dsp.const2) * (dsp.rec203[S32(2)])))
            dsp.rec202[S32(0)] = (dsp.const3) * ((dsp.rec203[S32(0)]) - (dsp.rec203[S32(2)]))
            var temp56 = (F64(1.7063034)) * (temp8)
            dsp.vec112[(dsp.iota0) & (S32(63))] = (temp56) + ((slow2) * (dsp.rec204[S32(1)]))
            dsp.rec205[S32(0)] = ((slow327) * (dsp.vec112[((dsp.iota0) - (i_slow328)) & (S32(63))])) - (((slow329) * (dsp.rec205[S32(1)])) + ((dsp.const2) * (dsp.rec205[S32(2)])))
            dsp.rec204[S32(0)] = (dsp.const3) * ((dsp.rec205[S32(0)]) - (dsp.rec205[S32(2)]))
            dsp.vec113[(dsp.iota0) & (S32(63))] = ((slow2) * (dsp.rec206[S32(1)])) + (temp56)
            dsp.rec207[S32(0)] = ((slow330) * (dsp.vec113[((dsp.iota0) - (i_slow331)) & (S32(63))])) - (((slow332) * (dsp.rec207[S32(1)])) + ((dsp.const2) * (dsp.rec207[S32(2)])))
            dsp.rec206[S32(0)] = (dsp.const3) * ((dsp.rec207[S32(0)]) - (dsp.rec207[S32(2)]))
            var temp57 = (F64(5.0063033)) * (temp8)
            dsp.vec114[(dsp.iota0) & (S32(127))] = (temp57) + ((slow2) * (dsp.rec208[S32(1)]))
            dsp.rec209[S32(0)] = ((slow333) * (dsp.vec114[((dsp.iota0) - (i_slow334)) & (S32(127))])) - (((slow335) * (dsp.rec209[S32(1)])) + ((dsp.const2) * (dsp.rec209[S32(2)])))
            dsp.rec208[S32(0)] = (dsp.const3) * ((dsp.rec209[S32(0)]) - (dsp.rec209[S32(2)]))
            var temp58 = (F64(2.1900357)) * (temp8)
            dsp.vec115[(dsp.iota0) & (S32(1023))] = ((slow2) * (dsp.rec210[S32(1)])) + (temp58)
            dsp.rec211[S32(0)] = ((slow336) * (dsp.vec115[((dsp.iota0) - (i_slow337)) & (S32(1023))])) - (((slow338) * (dsp.rec211[S32(1)])) + ((dsp.const2) * (dsp.rec211[S32(2)])))
            dsp.rec210[S32(0)] = (dsp.const3) * ((dsp.rec211[S32(0)]) - (dsp.rec211[S32(2)]))
            dsp.vec116[(dsp.iota0) & (S32(1023))] = (temp58) + ((slow2) * (dsp.rec212[S32(1)]))
            dsp.rec213[S32(0)] = ((slow339) * (dsp.vec116[((dsp.iota0) - (i_slow340)) & (S32(1023))])) - (((slow341) * (dsp.rec213[S32(1)])) + ((dsp.const2) * (dsp.rec213[S32(2)])))
            dsp.rec212[S32(0)] = (dsp.const3) * ((dsp.rec213[S32(0)]) - (dsp.rec213[S32(2)]))
            var temp59 = (F64(2.0914886)) * (temp8)
            dsp.vec117[(dsp.iota0) & (S32(255))] = ((slow2) * (dsp.rec214[S32(1)])) + (temp59)
            dsp.rec215[S32(0)] = ((slow342) * (dsp.vec117[((dsp.iota0) - (i_slow343)) & (S32(255))])) - (((slow344) * (dsp.rec215[S32(1)])) + ((dsp.const2) * (dsp.rec215[S32(2)])))
            dsp.rec214[S32(0)] = (dsp.const3) * ((dsp.rec215[S32(0)]) - (dsp.rec215[S32(2)]))
            dsp.vec118[(dsp.iota0) & (S32(255))] = (temp59) + ((slow2) * (dsp.rec216[S32(1)]))
            dsp.rec217[S32(0)] = ((slow345) * (dsp.vec118[((dsp.iota0) - (i_slow346)) & (S32(255))])) - (((slow347) * (dsp.rec217[S32(1)])) + ((dsp.const2) * (dsp.rec217[S32(2)])))
            dsp.rec216[S32(0)] = (dsp.const3) * ((dsp.rec217[S32(0)]) - (dsp.rec217[S32(2)]))
            dsp.vec119[(dsp.iota0) & (S32(127))] = ((slow2) * (dsp.rec218[S32(1)])) + (temp57)
            dsp.rec219[S32(0)] = ((slow348) * (dsp.vec119[((dsp.iota0) - (i_slow349)) & (S32(127))])) - (((slow350) * (dsp.rec219[S32(1)])) + ((dsp.const2) * (dsp.rec219[S32(2)])))
            dsp.rec218[S32(0)] = (dsp.const3) * ((dsp.rec219[S32(0)]) - (dsp.rec219[S32(2)]))
            output0[i0] = SIMD[dreal, 1](((F64(2.0)) * ((dsp.rec0[S32(0)]) + ((dsp.rec2[S32(0)]) + ((dsp.rec4[S32(0)]) + ((dsp.rec6[S32(0)]) + ((dsp.rec8[S32(0)]) + ((dsp.rec10[S32(0)]) + ((dsp.rec12[S32(0)]) + ((dsp.rec14[S32(0)]) + ((dsp.rec16[S32(0)]) + (dsp.rec18[S32(0)]))))))))))) + ((dsp.rec20[S32(0)]) + ((dsp.rec22[S32(0)]) + ((dsp.rec24[S32(0)]) + ((dsp.rec26[S32(0)]) + ((dsp.rec28[S32(0)]) + ((dsp.rec30[S32(0)]) + ((dsp.rec32[S32(0)]) + ((dsp.rec34[S32(0)]) + ((dsp.rec36[S32(0)]) + ((dsp.rec38[S32(0)]) + ((dsp.rec40[S32(0)]) + ((dsp.rec42[S32(0)]) + ((dsp.rec44[S32(0)]) + ((dsp.rec46[S32(0)]) + ((dsp.rec48[S32(0)]) + ((dsp.rec50[S32(0)]) + ((dsp.rec52[S32(0)]) + ((dsp.rec54[S32(0)]) + ((dsp.rec56[S32(0)]) + ((dsp.rec58[S32(0)]) + ((dsp.rec60[S32(0)]) + ((dsp.rec62[S32(0)]) + ((dsp.rec64[S32(0)]) + ((dsp.rec66[S32(0)]) + ((dsp.rec68[S32(0)]) + ((dsp.rec70[S32(0)]) + ((dsp.rec72[S32(0)]) + ((dsp.rec74[S32(0)]) + ((dsp.rec76[S32(0)]) + ((dsp.rec78[S32(0)]) + ((dsp.rec80[S32(0)]) + ((dsp.rec82[S32(0)]) + ((dsp.rec84[S32(0)]) + ((dsp.rec86[S32(0)]) + ((dsp.rec88[S32(0)]) + ((dsp.rec90[S32(0)]) + ((dsp.rec92[S32(0)]) + ((dsp.rec94[S32(0)]) + ((dsp.rec96[S32(0)]) + ((dsp.rec98[S32(0)]) + ((dsp.rec100[S32(0)]) + ((dsp.rec102[S32(0)]) + ((dsp.rec104[S32(0)]) + ((dsp.rec106[S32(0)]) + ((dsp.rec108[S32(0)]) + ((dsp.rec110[S32(0)]) + ((dsp.rec112[S32(0)]) + ((dsp.rec114[S32(0)]) + ((dsp.rec116[S32(0)]) + ((dsp.rec118[S32(0)]) + ((dsp.rec120[S32(0)]) + ((dsp.rec122[S32(0)]) + ((dsp.rec124[S32(0)]) + ((dsp.rec126[S32(0)]) + ((dsp.rec128[S32(0)]) + ((dsp.rec130[S32(0)]) + ((dsp.rec132[S32(0)]) + ((dsp.rec134[S32(0)]) + ((dsp.rec136[S32(0)]) + ((dsp.rec138[S32(0)]) + ((dsp.rec140[S32(0)]) + ((dsp.rec142[S32(0)]) + ((dsp.rec144[S32(0)]) + ((dsp.rec146[S32(0)]) + ((dsp.rec148[S32(0)]) + ((dsp.rec150[S32(0)]) + ((dsp.rec152[S32(0)]) + ((dsp.rec154[S32(0)]) + ((dsp.rec156[S32(0)]) + ((dsp.rec158[S32(0)]) + ((dsp.rec160[S32(0)]) + ((dsp.rec162[S32(0)]) + ((dsp.rec164[S32(0)]) + ((dsp.rec166[S32(0)]) + ((dsp.rec168[S32(0)]) + ((dsp.rec170[S32(0)]) + ((dsp.rec172[S32(0)]) + ((dsp.rec174[S32(0)]) + ((dsp.rec176[S32(0)]) + ((dsp.rec178[S32(0)]) + ((dsp.rec180[S32(0)]) + ((dsp.rec182[S32(0)]) + ((dsp.rec184[S32(0)]) + ((dsp.rec186[S32(0)]) + ((dsp.rec188[S32(0)]) + ((dsp.rec190[S32(0)]) + ((dsp.rec192[S32(0)]) + ((dsp.rec194[S32(0)]) + ((dsp.rec196[S32(0)]) + ((dsp.rec198[S32(0)]) + ((dsp.rec200[S32(0)]) + ((dsp.rec202[S32(0)]) + ((dsp.rec204[S32(0)]) + ((dsp.rec206[S32(0)]) + ((dsp.rec208[S32(0)]) + (((((dsp.rec210[S32(0)]) + (dsp.rec212[S32(0)])) + (dsp.rec214[S32(0)])) + (dsp.rec216[S32(0)])) + (dsp.rec218[S32(0)]))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))
            dsp.vec0[S32(1)] = dsp.vec0[S32(0)]
            dsp.iota0 = (dsp.iota0) + (S32(1))
            dsp.rec1[S32(2)] = dsp.rec1[S32(1)]
            dsp.rec1[S32(1)] = dsp.rec1[S32(0)]
            dsp.rec0[S32(1)] = dsp.rec0[S32(0)]
            dsp.vec2[S32(1)] = dsp.vec2[S32(0)]
            dsp.rec3[S32(2)] = dsp.rec3[S32(1)]
            dsp.rec3[S32(1)] = dsp.rec3[S32(0)]
            dsp.rec2[S32(1)] = dsp.rec2[S32(0)]
            dsp.vec4[S32(1)] = dsp.vec4[S32(0)]
            dsp.rec5[S32(2)] = dsp.rec5[S32(1)]
            dsp.rec5[S32(1)] = dsp.rec5[S32(0)]
            dsp.rec4[S32(1)] = dsp.rec4[S32(0)]
            dsp.vec6[S32(1)] = dsp.vec6[S32(0)]
            dsp.rec7[S32(2)] = dsp.rec7[S32(1)]
            dsp.rec7[S32(1)] = dsp.rec7[S32(0)]
            dsp.rec6[S32(1)] = dsp.rec6[S32(0)]
            dsp.vec8[S32(1)] = dsp.vec8[S32(0)]
            dsp.rec9[S32(2)] = dsp.rec9[S32(1)]
            dsp.rec9[S32(1)] = dsp.rec9[S32(0)]
            dsp.rec8[S32(1)] = dsp.rec8[S32(0)]
            dsp.vec10[S32(1)] = dsp.vec10[S32(0)]
            dsp.rec11[S32(2)] = dsp.rec11[S32(1)]
            dsp.rec11[S32(1)] = dsp.rec11[S32(0)]
            dsp.rec10[S32(1)] = dsp.rec10[S32(0)]
            dsp.vec12[S32(1)] = dsp.vec12[S32(0)]
            dsp.rec13[S32(2)] = dsp.rec13[S32(1)]
            dsp.rec13[S32(1)] = dsp.rec13[S32(0)]
            dsp.rec12[S32(1)] = dsp.rec12[S32(0)]
            dsp.vec14[S32(1)] = dsp.vec14[S32(0)]
            dsp.rec15[S32(2)] = dsp.rec15[S32(1)]
            dsp.rec15[S32(1)] = dsp.rec15[S32(0)]
            dsp.rec14[S32(1)] = dsp.rec14[S32(0)]
            dsp.vec16[S32(1)] = dsp.vec16[S32(0)]
            dsp.rec17[S32(2)] = dsp.rec17[S32(1)]
            dsp.rec17[S32(1)] = dsp.rec17[S32(0)]
            dsp.rec16[S32(1)] = dsp.rec16[S32(0)]
            dsp.vec18[S32(1)] = dsp.vec18[S32(0)]
            dsp.rec19[S32(2)] = dsp.rec19[S32(1)]
            dsp.rec19[S32(1)] = dsp.rec19[S32(0)]
            dsp.rec18[S32(1)] = dsp.rec18[S32(0)]
            dsp.rec21[S32(2)] = dsp.rec21[S32(1)]
            dsp.rec21[S32(1)] = dsp.rec21[S32(0)]
            dsp.rec20[S32(1)] = dsp.rec20[S32(0)]
            dsp.rec23[S32(2)] = dsp.rec23[S32(1)]
            dsp.rec23[S32(1)] = dsp.rec23[S32(0)]
            dsp.rec22[S32(1)] = dsp.rec22[S32(0)]
            dsp.rec25[S32(2)] = dsp.rec25[S32(1)]
            dsp.rec25[S32(1)] = dsp.rec25[S32(0)]
            dsp.rec24[S32(1)] = dsp.rec24[S32(0)]
            dsp.rec27[S32(2)] = dsp.rec27[S32(1)]
            dsp.rec27[S32(1)] = dsp.rec27[S32(0)]
            dsp.rec26[S32(1)] = dsp.rec26[S32(0)]
            dsp.rec29[S32(2)] = dsp.rec29[S32(1)]
            dsp.rec29[S32(1)] = dsp.rec29[S32(0)]
            dsp.rec28[S32(1)] = dsp.rec28[S32(0)]
            dsp.rec31[S32(2)] = dsp.rec31[S32(1)]
            dsp.rec31[S32(1)] = dsp.rec31[S32(0)]
            dsp.rec30[S32(1)] = dsp.rec30[S32(0)]
            dsp.rec33[S32(2)] = dsp.rec33[S32(1)]
            dsp.rec33[S32(1)] = dsp.rec33[S32(0)]
            dsp.rec32[S32(1)] = dsp.rec32[S32(0)]
            dsp.rec35[S32(2)] = dsp.rec35[S32(1)]
            dsp.rec35[S32(1)] = dsp.rec35[S32(0)]
            dsp.rec34[S32(1)] = dsp.rec34[S32(0)]
            dsp.rec37[S32(2)] = dsp.rec37[S32(1)]
            dsp.rec37[S32(1)] = dsp.rec37[S32(0)]
            dsp.rec36[S32(1)] = dsp.rec36[S32(0)]
            dsp.rec39[S32(2)] = dsp.rec39[S32(1)]
            dsp.rec39[S32(1)] = dsp.rec39[S32(0)]
            dsp.rec38[S32(1)] = dsp.rec38[S32(0)]
            dsp.rec41[S32(2)] = dsp.rec41[S32(1)]
            dsp.rec41[S32(1)] = dsp.rec41[S32(0)]
            dsp.rec40[S32(1)] = dsp.rec40[S32(0)]
            dsp.rec43[S32(2)] = dsp.rec43[S32(1)]
            dsp.rec43[S32(1)] = dsp.rec43[S32(0)]
            dsp.rec42[S32(1)] = dsp.rec42[S32(0)]
            dsp.rec45[S32(2)] = dsp.rec45[S32(1)]
            dsp.rec45[S32(1)] = dsp.rec45[S32(0)]
            dsp.rec44[S32(1)] = dsp.rec44[S32(0)]
            dsp.rec47[S32(2)] = dsp.rec47[S32(1)]
            dsp.rec47[S32(1)] = dsp.rec47[S32(0)]
            dsp.rec46[S32(1)] = dsp.rec46[S32(0)]
            dsp.rec49[S32(2)] = dsp.rec49[S32(1)]
            dsp.rec49[S32(1)] = dsp.rec49[S32(0)]
            dsp.rec48[S32(1)] = dsp.rec48[S32(0)]
            dsp.rec51[S32(2)] = dsp.rec51[S32(1)]
            dsp.rec51[S32(1)] = dsp.rec51[S32(0)]
            dsp.rec50[S32(1)] = dsp.rec50[S32(0)]
            dsp.rec53[S32(2)] = dsp.rec53[S32(1)]
            dsp.rec53[S32(1)] = dsp.rec53[S32(0)]
            dsp.rec52[S32(1)] = dsp.rec52[S32(0)]
            dsp.rec55[S32(2)] = dsp.rec55[S32(1)]
            dsp.rec55[S32(1)] = dsp.rec55[S32(0)]
            dsp.rec54[S32(1)] = dsp.rec54[S32(0)]
            dsp.rec57[S32(2)] = dsp.rec57[S32(1)]
            dsp.rec57[S32(1)] = dsp.rec57[S32(0)]
            dsp.rec56[S32(1)] = dsp.rec56[S32(0)]
            dsp.rec59[S32(2)] = dsp.rec59[S32(1)]
            dsp.rec59[S32(1)] = dsp.rec59[S32(0)]
            dsp.rec58[S32(1)] = dsp.rec58[S32(0)]
            dsp.rec61[S32(2)] = dsp.rec61[S32(1)]
            dsp.rec61[S32(1)] = dsp.rec61[S32(0)]
            dsp.rec60[S32(1)] = dsp.rec60[S32(0)]
            dsp.rec63[S32(2)] = dsp.rec63[S32(1)]
            dsp.rec63[S32(1)] = dsp.rec63[S32(0)]
            dsp.rec62[S32(1)] = dsp.rec62[S32(0)]
            dsp.rec65[S32(2)] = dsp.rec65[S32(1)]
            dsp.rec65[S32(1)] = dsp.rec65[S32(0)]
            dsp.rec64[S32(1)] = dsp.rec64[S32(0)]
            dsp.rec67[S32(2)] = dsp.rec67[S32(1)]
            dsp.rec67[S32(1)] = dsp.rec67[S32(0)]
            dsp.rec66[S32(1)] = dsp.rec66[S32(0)]
            dsp.rec69[S32(2)] = dsp.rec69[S32(1)]
            dsp.rec69[S32(1)] = dsp.rec69[S32(0)]
            dsp.rec68[S32(1)] = dsp.rec68[S32(0)]
            dsp.rec71[S32(2)] = dsp.rec71[S32(1)]
            dsp.rec71[S32(1)] = dsp.rec71[S32(0)]
            dsp.rec70[S32(1)] = dsp.rec70[S32(0)]
            dsp.rec73[S32(2)] = dsp.rec73[S32(1)]
            dsp.rec73[S32(1)] = dsp.rec73[S32(0)]
            dsp.rec72[S32(1)] = dsp.rec72[S32(0)]
            dsp.rec75[S32(2)] = dsp.rec75[S32(1)]
            dsp.rec75[S32(1)] = dsp.rec75[S32(0)]
            dsp.rec74[S32(1)] = dsp.rec74[S32(0)]
            dsp.rec77[S32(2)] = dsp.rec77[S32(1)]
            dsp.rec77[S32(1)] = dsp.rec77[S32(0)]
            dsp.rec76[S32(1)] = dsp.rec76[S32(0)]
            dsp.rec79[S32(2)] = dsp.rec79[S32(1)]
            dsp.rec79[S32(1)] = dsp.rec79[S32(0)]
            dsp.rec78[S32(1)] = dsp.rec78[S32(0)]
            dsp.rec81[S32(2)] = dsp.rec81[S32(1)]
            dsp.rec81[S32(1)] = dsp.rec81[S32(0)]
            dsp.rec80[S32(1)] = dsp.rec80[S32(0)]
            dsp.rec83[S32(2)] = dsp.rec83[S32(1)]
            dsp.rec83[S32(1)] = dsp.rec83[S32(0)]
            dsp.rec82[S32(1)] = dsp.rec82[S32(0)]
            dsp.rec85[S32(2)] = dsp.rec85[S32(1)]
            dsp.rec85[S32(1)] = dsp.rec85[S32(0)]
            dsp.rec84[S32(1)] = dsp.rec84[S32(0)]
            dsp.rec87[S32(2)] = dsp.rec87[S32(1)]
            dsp.rec87[S32(1)] = dsp.rec87[S32(0)]
            dsp.rec86[S32(1)] = dsp.rec86[S32(0)]
            dsp.rec89[S32(2)] = dsp.rec89[S32(1)]
            dsp.rec89[S32(1)] = dsp.rec89[S32(0)]
            dsp.rec88[S32(1)] = dsp.rec88[S32(0)]
            dsp.rec91[S32(2)] = dsp.rec91[S32(1)]
            dsp.rec91[S32(1)] = dsp.rec91[S32(0)]
            dsp.rec90[S32(1)] = dsp.rec90[S32(0)]
            dsp.rec93[S32(2)] = dsp.rec93[S32(1)]
            dsp.rec93[S32(1)] = dsp.rec93[S32(0)]
            dsp.rec92[S32(1)] = dsp.rec92[S32(0)]
            dsp.rec95[S32(2)] = dsp.rec95[S32(1)]
            dsp.rec95[S32(1)] = dsp.rec95[S32(0)]
            dsp.rec94[S32(1)] = dsp.rec94[S32(0)]
            dsp.rec97[S32(2)] = dsp.rec97[S32(1)]
            dsp.rec97[S32(1)] = dsp.rec97[S32(0)]
            dsp.rec96[S32(1)] = dsp.rec96[S32(0)]
            dsp.rec99[S32(2)] = dsp.rec99[S32(1)]
            dsp.rec99[S32(1)] = dsp.rec99[S32(0)]
            dsp.rec98[S32(1)] = dsp.rec98[S32(0)]
            dsp.rec101[S32(2)] = dsp.rec101[S32(1)]
            dsp.rec101[S32(1)] = dsp.rec101[S32(0)]
            dsp.rec100[S32(1)] = dsp.rec100[S32(0)]
            dsp.rec103[S32(2)] = dsp.rec103[S32(1)]
            dsp.rec103[S32(1)] = dsp.rec103[S32(0)]
            dsp.rec102[S32(1)] = dsp.rec102[S32(0)]
            dsp.rec105[S32(2)] = dsp.rec105[S32(1)]
            dsp.rec105[S32(1)] = dsp.rec105[S32(0)]
            dsp.rec104[S32(1)] = dsp.rec104[S32(0)]
            dsp.rec107[S32(2)] = dsp.rec107[S32(1)]
            dsp.rec107[S32(1)] = dsp.rec107[S32(0)]
            dsp.rec106[S32(1)] = dsp.rec106[S32(0)]
            dsp.rec109[S32(2)] = dsp.rec109[S32(1)]
            dsp.rec109[S32(1)] = dsp.rec109[S32(0)]
            dsp.rec108[S32(1)] = dsp.rec108[S32(0)]
            dsp.rec111[S32(2)] = dsp.rec111[S32(1)]
            dsp.rec111[S32(1)] = dsp.rec111[S32(0)]
            dsp.rec110[S32(1)] = dsp.rec110[S32(0)]
            dsp.rec113[S32(2)] = dsp.rec113[S32(1)]
            dsp.rec113[S32(1)] = dsp.rec113[S32(0)]
            dsp.rec112[S32(1)] = dsp.rec112[S32(0)]
            dsp.rec115[S32(2)] = dsp.rec115[S32(1)]
            dsp.rec115[S32(1)] = dsp.rec115[S32(0)]
            dsp.rec114[S32(1)] = dsp.rec114[S32(0)]
            dsp.rec117[S32(2)] = dsp.rec117[S32(1)]
            dsp.rec117[S32(1)] = dsp.rec117[S32(0)]
            dsp.rec116[S32(1)] = dsp.rec116[S32(0)]
            dsp.rec119[S32(2)] = dsp.rec119[S32(1)]
            dsp.rec119[S32(1)] = dsp.rec119[S32(0)]
            dsp.rec118[S32(1)] = dsp.rec118[S32(0)]
            dsp.rec121[S32(2)] = dsp.rec121[S32(1)]
            dsp.rec121[S32(1)] = dsp.rec121[S32(0)]
            dsp.rec120[S32(1)] = dsp.rec120[S32(0)]
            dsp.rec123[S32(2)] = dsp.rec123[S32(1)]
            dsp.rec123[S32(1)] = dsp.rec123[S32(0)]
            dsp.rec122[S32(1)] = dsp.rec122[S32(0)]
            dsp.rec125[S32(2)] = dsp.rec125[S32(1)]
            dsp.rec125[S32(1)] = dsp.rec125[S32(0)]
            dsp.rec124[S32(1)] = dsp.rec124[S32(0)]
            dsp.rec127[S32(2)] = dsp.rec127[S32(1)]
            dsp.rec127[S32(1)] = dsp.rec127[S32(0)]
            dsp.rec126[S32(1)] = dsp.rec126[S32(0)]
            dsp.rec129[S32(2)] = dsp.rec129[S32(1)]
            dsp.rec129[S32(1)] = dsp.rec129[S32(0)]
            dsp.rec128[S32(1)] = dsp.rec128[S32(0)]
            dsp.rec131[S32(2)] = dsp.rec131[S32(1)]
            dsp.rec131[S32(1)] = dsp.rec131[S32(0)]
            dsp.rec130[S32(1)] = dsp.rec130[S32(0)]
            dsp.rec133[S32(2)] = dsp.rec133[S32(1)]
            dsp.rec133[S32(1)] = dsp.rec133[S32(0)]
            dsp.rec132[S32(1)] = dsp.rec132[S32(0)]
            dsp.rec135[S32(2)] = dsp.rec135[S32(1)]
            dsp.rec135[S32(1)] = dsp.rec135[S32(0)]
            dsp.rec134[S32(1)] = dsp.rec134[S32(0)]
            dsp.rec137[S32(2)] = dsp.rec137[S32(1)]
            dsp.rec137[S32(1)] = dsp.rec137[S32(0)]
            dsp.rec136[S32(1)] = dsp.rec136[S32(0)]
            dsp.rec139[S32(2)] = dsp.rec139[S32(1)]
            dsp.rec139[S32(1)] = dsp.rec139[S32(0)]
            dsp.rec138[S32(1)] = dsp.rec138[S32(0)]
            dsp.rec141[S32(2)] = dsp.rec141[S32(1)]
            dsp.rec141[S32(1)] = dsp.rec141[S32(0)]
            dsp.rec140[S32(1)] = dsp.rec140[S32(0)]
            dsp.rec143[S32(2)] = dsp.rec143[S32(1)]
            dsp.rec143[S32(1)] = dsp.rec143[S32(0)]
            dsp.rec142[S32(1)] = dsp.rec142[S32(0)]
            dsp.rec145[S32(2)] = dsp.rec145[S32(1)]
            dsp.rec145[S32(1)] = dsp.rec145[S32(0)]
            dsp.rec144[S32(1)] = dsp.rec144[S32(0)]
            dsp.rec147[S32(2)] = dsp.rec147[S32(1)]
            dsp.rec147[S32(1)] = dsp.rec147[S32(0)]
            dsp.rec146[S32(1)] = dsp.rec146[S32(0)]
            dsp.rec149[S32(2)] = dsp.rec149[S32(1)]
            dsp.rec149[S32(1)] = dsp.rec149[S32(0)]
            dsp.rec148[S32(1)] = dsp.rec148[S32(0)]
            dsp.rec151[S32(2)] = dsp.rec151[S32(1)]
            dsp.rec151[S32(1)] = dsp.rec151[S32(0)]
            dsp.rec150[S32(1)] = dsp.rec150[S32(0)]
            dsp.rec153[S32(2)] = dsp.rec153[S32(1)]
            dsp.rec153[S32(1)] = dsp.rec153[S32(0)]
            dsp.rec152[S32(1)] = dsp.rec152[S32(0)]
            dsp.rec155[S32(2)] = dsp.rec155[S32(1)]
            dsp.rec155[S32(1)] = dsp.rec155[S32(0)]
            dsp.rec154[S32(1)] = dsp.rec154[S32(0)]
            dsp.rec157[S32(2)] = dsp.rec157[S32(1)]
            dsp.rec157[S32(1)] = dsp.rec157[S32(0)]
            dsp.rec156[S32(1)] = dsp.rec156[S32(0)]
            dsp.rec159[S32(2)] = dsp.rec159[S32(1)]
            dsp.rec159[S32(1)] = dsp.rec159[S32(0)]
            dsp.rec158[S32(1)] = dsp.rec158[S32(0)]
            dsp.rec161[S32(2)] = dsp.rec161[S32(1)]
            dsp.rec161[S32(1)] = dsp.rec161[S32(0)]
            dsp.rec160[S32(1)] = dsp.rec160[S32(0)]
            dsp.rec163[S32(2)] = dsp.rec163[S32(1)]
            dsp.rec163[S32(1)] = dsp.rec163[S32(0)]
            dsp.rec162[S32(1)] = dsp.rec162[S32(0)]
            dsp.rec165[S32(2)] = dsp.rec165[S32(1)]
            dsp.rec165[S32(1)] = dsp.rec165[S32(0)]
            dsp.rec164[S32(1)] = dsp.rec164[S32(0)]
            dsp.rec167[S32(2)] = dsp.rec167[S32(1)]
            dsp.rec167[S32(1)] = dsp.rec167[S32(0)]
            dsp.rec166[S32(1)] = dsp.rec166[S32(0)]
            dsp.rec169[S32(2)] = dsp.rec169[S32(1)]
            dsp.rec169[S32(1)] = dsp.rec169[S32(0)]
            dsp.rec168[S32(1)] = dsp.rec168[S32(0)]
            dsp.rec171[S32(2)] = dsp.rec171[S32(1)]
            dsp.rec171[S32(1)] = dsp.rec171[S32(0)]
            dsp.rec170[S32(1)] = dsp.rec170[S32(0)]
            dsp.rec173[S32(2)] = dsp.rec173[S32(1)]
            dsp.rec173[S32(1)] = dsp.rec173[S32(0)]
            dsp.rec172[S32(1)] = dsp.rec172[S32(0)]
            dsp.rec175[S32(2)] = dsp.rec175[S32(1)]
            dsp.rec175[S32(1)] = dsp.rec175[S32(0)]
            dsp.rec174[S32(1)] = dsp.rec174[S32(0)]
            dsp.rec177[S32(2)] = dsp.rec177[S32(1)]
            dsp.rec177[S32(1)] = dsp.rec177[S32(0)]
            dsp.rec176[S32(1)] = dsp.rec176[S32(0)]
            dsp.rec179[S32(2)] = dsp.rec179[S32(1)]
            dsp.rec179[S32(1)] = dsp.rec179[S32(0)]
            dsp.rec178[S32(1)] = dsp.rec178[S32(0)]
            dsp.rec181[S32(2)] = dsp.rec181[S32(1)]
            dsp.rec181[S32(1)] = dsp.rec181[S32(0)]
            dsp.rec180[S32(1)] = dsp.rec180[S32(0)]
            dsp.rec183[S32(2)] = dsp.rec183[S32(1)]
            dsp.rec183[S32(1)] = dsp.rec183[S32(0)]
            dsp.rec182[S32(1)] = dsp.rec182[S32(0)]
            dsp.rec185[S32(2)] = dsp.rec185[S32(1)]
            dsp.rec185[S32(1)] = dsp.rec185[S32(0)]
            dsp.rec184[S32(1)] = dsp.rec184[S32(0)]
            dsp.rec187[S32(2)] = dsp.rec187[S32(1)]
            dsp.rec187[S32(1)] = dsp.rec187[S32(0)]
            dsp.rec186[S32(1)] = dsp.rec186[S32(0)]
            dsp.rec189[S32(2)] = dsp.rec189[S32(1)]
            dsp.rec189[S32(1)] = dsp.rec189[S32(0)]
            dsp.rec188[S32(1)] = dsp.rec188[S32(0)]
            dsp.rec191[S32(2)] = dsp.rec191[S32(1)]
            dsp.rec191[S32(1)] = dsp.rec191[S32(0)]
            dsp.rec190[S32(1)] = dsp.rec190[S32(0)]
            dsp.rec193[S32(2)] = dsp.rec193[S32(1)]
            dsp.rec193[S32(1)] = dsp.rec193[S32(0)]
            dsp.rec192[S32(1)] = dsp.rec192[S32(0)]
            dsp.rec195[S32(2)] = dsp.rec195[S32(1)]
            dsp.rec195[S32(1)] = dsp.rec195[S32(0)]
            dsp.rec194[S32(1)] = dsp.rec194[S32(0)]
            dsp.rec197[S32(2)] = dsp.rec197[S32(1)]
            dsp.rec197[S32(1)] = dsp.rec197[S32(0)]
            dsp.rec196[S32(1)] = dsp.rec196[S32(0)]
            dsp.rec199[S32(2)] = dsp.rec199[S32(1)]
            dsp.rec199[S32(1)] = dsp.rec199[S32(0)]
            dsp.rec198[S32(1)] = dsp.rec198[S32(0)]
            dsp.rec201[S32(2)] = dsp.rec201[S32(1)]
            dsp.rec201[S32(1)] = dsp.rec201[S32(0)]
            dsp.rec200[S32(1)] = dsp.rec200[S32(0)]
            dsp.rec203[S32(2)] = dsp.rec203[S32(1)]
            dsp.rec203[S32(1)] = dsp.rec203[S32(0)]
            dsp.rec202[S32(1)] = dsp.rec202[S32(0)]
            dsp.rec205[S32(2)] = dsp.rec205[S32(1)]
            dsp.rec205[S32(1)] = dsp.rec205[S32(0)]
            dsp.rec204[S32(1)] = dsp.rec204[S32(0)]
            dsp.rec207[S32(2)] = dsp.rec207[S32(1)]
            dsp.rec207[S32(1)] = dsp.rec207[S32(0)]
            dsp.rec206[S32(1)] = dsp.rec206[S32(0)]
            dsp.rec209[S32(2)] = dsp.rec209[S32(1)]
            dsp.rec209[S32(1)] = dsp.rec209[S32(0)]
            dsp.rec208[S32(1)] = dsp.rec208[S32(0)]
            dsp.rec211[S32(2)] = dsp.rec211[S32(1)]
            dsp.rec211[S32(1)] = dsp.rec211[S32(0)]
            dsp.rec210[S32(1)] = dsp.rec210[S32(0)]
            dsp.rec213[S32(2)] = dsp.rec213[S32(1)]
            dsp.rec213[S32(1)] = dsp.rec213[S32(0)]
            dsp.rec212[S32(1)] = dsp.rec212[S32(0)]
            dsp.rec215[S32(2)] = dsp.rec215[S32(1)]
            dsp.rec215[S32(1)] = dsp.rec215[S32(0)]
            dsp.rec214[S32(1)] = dsp.rec214[S32(0)]
            dsp.rec217[S32(2)] = dsp.rec217[S32(1)]
            dsp.rec217[S32(1)] = dsp.rec217[S32(0)]
            dsp.rec216[S32(1)] = dsp.rec216[S32(0)]
            dsp.rec219[S32(2)] = dsp.rec219[S32(1)]
            dsp.rec219[S32(1)] = dsp.rec219[S32(0)]
            dsp.rec218[S32(1)] = dsp.rec218[S32(0)]


def main() raises -> None:
    comptime dreal = dfaust
    comptime Real = SIMD[dreal, 1]

    var dsp = alloc[mydsp](1)
    dsp[] = mydsp()
    dsp[].init(SAMP_RATE)

    var n_ins = dsp[].get_num_inputs()
    var n_outs = dsp[].get_num_outputs()

    var base, err = make_buffers[dreal](BUFF_SIZE, n_ins, n_outs)
    if err:
        print("Critical allocation error: ", err)
        dsp.free()
        return

    var inputs = base.bitcast[Ptr[Real, MUTA_EXT]]()
    var outputs = inputs + n_ins

    comptime if FILL_INPUTS:
        fill_inputs[dreal](inputs, n_ins)

    warmup[dreal](dsp[], inputs, outputs)
    var report = measure[dreal](dsp[], inputs, outputs)
    report.checksum = checksum_outputs[dreal](outputs, n_outs)
    print_report(report) # the output will be redirected via script

    comptime if WRITE_CSV:
        write_csv(report)

    free_buffers[dreal](base)
    dsp.free()
