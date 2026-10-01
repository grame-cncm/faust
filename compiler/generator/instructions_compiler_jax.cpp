/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2017-2021 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include "floats.hh"
#include "instructions_compiler_jax.hh"
#include "ppsig.hh"
#include "sigtyperules.hh"

using namespace std;

StatementInst* InstructionsCompilerJAX::generateShiftArray(const string& vname, int delay)
{
    Values truncated_args;
    truncated_args.push_back(IB::genLoadArrayStructVar(vname));
    truncated_args.push_back(IB::genLoadStackVar("1"));
    return IB::genStoreArrayStructVar(vname,
                                      IB::genFunCallInst(string("jnp.roll"), truncated_args));
}

ValueInst* InstructionsCompilerJAX::generateDelayLine(ValueInst* exp, BasicTyped* ctype,
                                                      const string& vname, int mxd,
                                                      Address::AccessType& access, ValueInst* ccs)
{
    if (mxd == 0) {
        // Generate scalar use
        if (dynamic_cast<NullValueInst*>(ccs)) {
            pushComputeDSPMethod(IB::genDecStackVar(vname, ctype, exp));
        } else {
            pushPreComputeDSPMethod(IB::genDecStackVar(vname, ctype, IB::genTypedZero(ctype)));
            pushComputeDSPMethod(IB::genControlInst(ccs, IB::genStoreStackVar(vname, exp)));
        }

    } else if (mxd < gGlobal->gMaxCopyDelay) {
        // Generates table init
        generateInitArray(vname, ctype, mxd + 1);

        // Generate table use
        pushComputeDSPMethod(IB::genControlInst(
            ccs, IB::genStoreArrayStructVar(vname, IB::genInt32NumInst(0), exp)));

        // Generates post processing copy code to update delay values
        if (mxd == 1) {
            pushPostComputeDSPMethod(IB::genControlInst(ccs, generateCopyArray(vname, 0, 1)));
        } else if (mxd == 2) {
            pushPostComputeDSPMethod(IB::genControlInst(ccs, generateCopyArray(vname, 1, 2)));
            pushPostComputeDSPMethod(IB::genControlInst(ccs, generateCopyArray(vname, 0, 1)));
        } else {
            pushPostComputeDSPMethod(IB::genControlInst(ccs, generateShiftArray(vname, mxd)));
        }

    } else {
        int N = pow2limit(mxd + 1);
        if (N <= gGlobal->gMaskDelayLineThreshold) {
            ensureIotaCode();

            // Generates table init
            generateInitArray(vname, ctype, N);

            // Generate table use
            if (gGlobal->gComputeIOTA) {  // Ensure IOTA base fixed delays are computed once
                if (fIOTATable.find(N) == fIOTATable.end()) {
                    string   iota_name = subst("i$0", gGlobal->getFreshID(fCurrentIOTA + "_temp"));
                    FIRIndex value2 =
                        FIRIndex(IB::genLoadStructVar(fCurrentIOTA)) & FIRIndex(N - 1);

                    pushPreComputeDSPMethod(
                        IB::genDecStackVar(iota_name, IB::genInt32Typed(), IB::genInt32NumInst(0)));
                    pushComputeDSPMethod(
                        IB::genControlInst(ccs, IB::genStoreStackVar(iota_name, value2)));

                    fIOTATable[N] = iota_name;
                }

                pushComputeDSPMethod(IB::genControlInst(
                    ccs,
                    IB::genStoreArrayStructVar(vname, IB::genLoadStackVar(fIOTATable[N]), exp)));

            } else {
                FIRIndex value2 = FIRIndex(IB::genLoadStructVar(fCurrentIOTA)) & FIRIndex(N - 1);
                pushComputeDSPMethod(
                    IB::genControlInst(ccs, IB::genStoreArrayStructVar(vname, value2, exp)));
            }
        } else {
            // 'select' based delay
            string widx_tmp_name = vname + "_widx_tmp";
            string widx_name     = vname + "_widx";

            // Generates table write index
            pushDeclare(IB::genDecStructVar(widx_name, IB::genInt32Typed()));
            pushInitMethod(IB::genStoreStructVar(widx_name, IB::genInt32NumInst(0)));

            // Generates table init
            generateInitArray(vname, ctype, mxd + 1);

            // int w = widx;
            pushComputeDSPMethod(IB::genControlInst(
                ccs, IB::genDecStackVar(widx_tmp_name, IB::genBasicTyped(Typed::kInt32),
                                        IB::genLoadStructVar(widx_name))));

            // dline[w] = v;
            pushComputeDSPMethod(IB::genControlInst(
                ccs, IB::genStoreArrayStructVar(vname, IB::genLoadStackVar(widx_tmp_name), exp)));

            // w = w + 1;
            FIRIndex widx_tmp1 = FIRIndex(IB::genLoadStackVar(widx_tmp_name));
            pushPostComputeDSPMethod(
                IB::genControlInst(ccs, IB::genStoreStackVar(widx_tmp_name, widx_tmp1 + 1)));

            // w = ((w == delay) ? 0 : w);
            FIRIndex widx_tmp2 = FIRIndex(IB::genLoadStackVar(widx_tmp_name));
            pushPostComputeDSPMethod(IB::genControlInst(
                ccs, IB::genStoreStackVar(widx_tmp_name,
                                          IB::genSelect2Inst(widx_tmp2 == FIRIndex(mxd + 1),
                                                             FIRIndex(0), widx_tmp2))));
            // *widx = w
            pushPostComputeDSPMethod(IB::genControlInst(
                ccs, IB::genStoreStructVar(widx_name, IB::genLoadStackVar(widx_tmp_name))));
        }
    }

    return exp;
}

ValueInst* InstructionsCompilerJAX::generateSoundfile(Tree sig, Tree path)
{
    string varname = gGlobal->getFreshID("fSoundfile");
    string SFcache = varname + "ca";

    Tree uipath   = reverse(tl(path));

    Tree uiwidget = uiWidget(hd(path), tree(varname), sig);

    fUITree.addUIWidget(uipath, uiwidget);

    pushDeclare(IB::genDecStructVar(varname, IB::genBasicTyped(Typed::kSound_ptr)));

    if (gGlobal->gUseDefaultSound) {
        BlockInst* block = IB::genBlockInst();
        block->pushBackInst(IB::genStoreStructVar(varname, IB::genLoadGlobalVar("defaultsound")));

        pushResetUIInstructions(IB::genIfInst(
            IB::genEqual(
                IB::genCastInst(IB::genLoadStructVar(varname), IB::genBasicTyped(Typed::kUint_ptr)),
                IB::genTypedZero(Typed::kSound_ptr)),
            block, IB::genBlockInst()));
    }

    if (gGlobal->gOneSample >= 0) {
        pushDeclare(IB::genDecStructVar(SFcache, IB::genBasicTyped(Typed::kSound_ptr)));
        pushComputeBlockMethod(IB::genStoreStructVar(SFcache, IB::genLoadStructVar(varname)));
    } else {
        pushComputeBlockMethod(IB::genDecStackVar(SFcache, IB::genBasicTyped(Typed::kSound_ptr),
                                                  IB::genLoadStructVar(varname)));
    }

    return IB::genLoadStructVar(varname);
}

ValueInst* InstructionsCompilerJAX::generateSoundfileBuffer(Tree sig, ValueInst* sf, ValueInst* x,
                                                            ValueInst* y, ValueInst* z)
{
    LoadVarInst* load = dynamic_cast<LoadVarInst*>(sf);
    faustassert(load);

    Typed* type1 = IB::genBasicTyped(itfloatptrptr());
    Typed* type2 = IB::genItFloatTyped();
    Typed* type3 = IB::genBasicTyped(Typed::kInt32_ptr);

    string SFcache             = load->fAddress->getName() + "ca";
    string SFcache_buffer      = gGlobal->getFreshID(SFcache + "_bu");
    string SFcache_buffer_chan = gGlobal->getFreshID(SFcache + "_bu_ch");
    string SFcache_offset      = gGlobal->getFreshID(SFcache + "_of");

    // add_soundfile() (architecture/jax/minimal.py and minimal_linen.py) sizes
    // the runtime buffer to the actual channel count of the loaded audio
    // file(s), which can be smaller than the channel count declared in the
    // `soundfile(label, chan)` primitive (e.g. a mono or stereo file read as
    // if it had more channels, a documented and common case). The base
    // (C++) architecture handles this with Soundfile::shareBuffers(), which
    // duplicates real channels cyclically (chan % cur_chan) up to the
    // requested count. JAX has no such runtime hook, and plain array
    // indexing with a static out-of-range channel number silently clamps to
    // the last real channel instead of wrapping, so channels beyond the
    // real count end up reading the wrong (repeated) channel's audio.
    // Wrapping the channel index with the buffer's own runtime length here
    // reproduces the same chan % cur_chan duplication.
    auto wrapChannel = [&](ValueInst* buffer_load) -> ValueInst* {
        Values len_args;
        len_args.push_back(buffer_load);
        return IB::genRem(x, IB::genFunCallInst("len", len_args));
    };

    if (gGlobal->gExtControl) {
        // Struct access using an index that will be converted as a field name
        ValueInst* v1 = IB::genLoadStructPtrVar(SFcache, Address::kStruct, IB::genInt32NumInst(3));

        pushDeclare(IB::genDecStructVar(SFcache_offset, type3));
        pushControlDeclare(IB::genStoreStructVar(SFcache_offset, v1));

        // Struct access using an index that will be converted as a field name
        LoadVarInst* load1 =
            IB::genLoadStructPtrVar(SFcache, Address::kStruct, IB::genInt32NumInst(0));

        pushDeclare(IB::genDecStructVar(SFcache_buffer, type1));
        // SFcache_buffer type is void* and has to be casted in the runtime buffer type
        pushControlDeclare(IB::genStoreStructVar(SFcache_buffer, IB::genCastInst(load1, type1)));

        pushDeclare(IB::genDecStructVar(SFcache_buffer_chan, IB::genArrayTyped(type2, 0)));
        pushControlDeclare(IB::genStoreStructVar(
            SFcache_buffer_chan,
            IB::genLoadStructPtrVar(SFcache_buffer, Address::kStruct,
                                    wrapChannel(IB::genLoadStructVar(SFcache_buffer)))));

        return IB::genLoadStructPtrVar(SFcache_buffer_chan, Address::kStruct,
                                       IB::genAdd(IB::genLoadArrayStructVar(SFcache_offset, y), z));
    } else {
        // Struct access using an index that will be converted as a field name
        ValueInst* v1 = IB::genLoadStructPtrVar(SFcache, Address::kStack, IB::genInt32NumInst(3));

        pushComputeBlockMethod(IB::genDecStackVar(SFcache_offset, type3, v1));

        // Struct access using an index that will be converted as a field name
        LoadVarInst* load1 =
            IB::genLoadStructPtrVar(SFcache, Address::kStack, IB::genInt32NumInst(0));

        // SFcache_buffer type is void* and has to be casted in the runtime buffer type
        pushComputeBlockMethod(
            IB::genDecStackVar(SFcache_buffer, type1, IB::genCastInst(load1, type1)));
        pushComputeBlockMethod(IB::genDecStackVar(
            SFcache_buffer_chan, IB::genArrayTyped(type2, 0),
            IB::genLoadStructPtrVar(SFcache_buffer, Address::kStack,
                                    wrapChannel(IB::genLoadStackVar(SFcache_buffer)))));
        return IB::genLoadStructPtrVar(SFcache_buffer_chan, Address::kStack,
                                       IB::genAdd(IB::genLoadArrayStackVar(SFcache_offset, y), z));
    }
}
