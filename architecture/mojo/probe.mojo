from std.sys.intrinsics import assume
from conf import *

def compute(count: S32, inputs: ReadStreams, outputs: MutaStreams):
    assume(SInt(count) * SInt(inputs) <= SInt(outputs) or SInt(count) * SInt(outputs) <= SInt(inputs))
    for i in range(count):
        outputs[i][0] = inputs[i][0]

def main():
    count: SInt = 64
    inputs: ReadStreams  = alloc[Ptr[FaustFloat, READ_NOTRK]](2 * count)
    outputs: MutaStreams = alloc[Ptr[FaustFloat, MUTA_NOTRK]](2 * count)
    compute(S32(count), inputs, outputs)

