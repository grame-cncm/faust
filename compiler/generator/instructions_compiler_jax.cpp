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

#include "instructions_compiler_jax.hh"
#include "ensure.hh"
#include "sigtyperules.hh"


/**
 * Generate code for a projection of a group of mutually recursive definitions
 */
ValueInst* InstructionsCompilerJAX::generateRecProj(Tree sig, Tree r, int i)
{
    string     vname;
    Tree       var, le;
    ValueInst* res;

    if (!getVectorNameProperty(sig, vname)) {
        ensure(isRec(r, var, le));
        res = generateRec(r, var, le, i);
        ensure(getVectorNameProperty(sig, vname));
    } else {
        res = InstBuilder::genNullValueInst();  // Result not used
    }
    return res;
}

/**
 * Generate code for a group of mutually recursive definitions
 */
ValueInst* InstructionsCompilerJAX::generateRec(Tree sig, Tree var, Tree le, int index)
{
    int N = len(le);

    ValueInst*             res = nullptr;
    vector<bool>           used(N);
    vector<int>            delay(N);
    vector<string>         vname(N);
    vector<Typed::VarType> ctype(N);

    // Prepare each element of a recursive definition
    for (int i = 0; i < N; i++) {
        Tree e = sigProj(i, sig);  // recreate each recursive definition
        if (fOccMarkup->retrieve(e)) {
            // This projection is used
            used[i] = true;
            getTypedNames(getCertifiedSigType(e), "Rec", ctype[i], vname[i]);
            setVectorNameProperty(e, vname[i]);
            delay[i] = fOccMarkup->retrieve(e)->getMaxDelay();
        } else {
            // This projection is not used therefore
            // we should not generate code for it
            used[i] = false;
        }
    }

    // Generate delayline for each element of a recursive definition
    for (int i = 0; i < N; i++) {
        if (used[i]) {
            Address::AccessType var_access;
            ValueInst* ccs = getConditionCode(nth(le, i));
            if (index == i) {
                res = generateDelayLine(CS(nth(le, i)), ctype[i], vname[i], delay[i], var_access, ccs);
            } else {
                generateDelayLine(CS(nth(le, i)), ctype[i], vname[i], delay[i], var_access, ccs);
            }
        }
    }

    return res;
}

ValueInst* InstructionsCompilerJAX::generateDelayLine(ValueInst* exp, Typed::VarType ctype, const string& vname, int mxd,
                                                   Address::AccessType& var_access, ValueInst* ccs)
{
    if (mxd == 0) {

        // Generate scalar use
        if (dynamic_cast<NullValueInst*>(ccs)) {
            pushComputeDSPMethod(InstBuilder::genDecStackVar(vname, InstBuilder::genBasicTyped(ctype), exp));
        } else {
            pushPreComputeDSPMethod(InstBuilder::genDecStackVar(vname, InstBuilder::genBasicTyped(ctype), InstBuilder::genTypedZero(ctype)));
            pushComputeDSPMethod(InstBuilder::genControlInst(ccs, InstBuilder::genStoreStackVar(vname, exp)));
        }

    } else if (mxd < gGlobal->gMaxCopyDelay) {

        // Generates table init
        pushClearMethod(generateInitArray(vname, ctype, mxd + 1));

        // Generate table use
        pushComputeDSPMethod(InstBuilder::genControlInst(ccs, InstBuilder::genStoreArrayStructVar(vname, InstBuilder::genInt32NumInst(0), exp)));

        // Generates post processing copy code to update delay values
        if (mxd == 1) {
            pushPostComputeDSPMethod(InstBuilder::genControlInst(ccs, generateCopyArray(vname, 0, 1)));
        } else if (mxd == 2) {
            pushPostComputeDSPMethod(InstBuilder::genControlInst(ccs, generateCopyArray(vname, 1, 2)));
            pushPostComputeDSPMethod(InstBuilder::genControlInst(ccs, generateCopyArray(vname, 0, 1)));
        } else {
            pushPostComputeDSPMethod(InstBuilder::genControlInst(ccs, generateShiftArray(vname, mxd)));
        }

    } else {

        int N = pow2limit(mxd + 1);
        if (N <= gGlobal->gMaskDelayLineThreshold) {

            ensureIotaCode();

            // Generates table init
            pushClearMethod(generateInitArray(vname, ctype, N));

            // Generate table use
            if (gGlobal->gComputeIOTA) {  // Ensure IOTA base fixed delays are computed once
                if (fIOTATable.find(N) == fIOTATable.end()) {
                    string   iota_name = subst("i$0", gGlobal->getFreshID(fCurrentIOTA + "_temp"));
                    FIRIndex value2 = FIRIndex(InstBuilder::genLoadStructVar(fCurrentIOTA)) & FIRIndex(N - 1);

                    pushPreComputeDSPMethod(InstBuilder::genDecStackVar(iota_name, InstBuilder::genInt32Typed(), InstBuilder::genInt32NumInst(0)));
                    pushComputeDSPMethod(InstBuilder::genControlInst(ccs, InstBuilder::genStoreStackVar(iota_name, value2)));

                    fIOTATable[N] = iota_name;
                }

                pushComputeDSPMethod(InstBuilder::genControlInst(ccs,
                    InstBuilder::genStoreArrayStructVar(vname, InstBuilder::genLoadStackVar(fIOTATable[N]), exp)));

            } else {
                FIRIndex value2 = FIRIndex(InstBuilder::genLoadStructVar(fCurrentIOTA)) & FIRIndex(N - 1);
                pushComputeDSPMethod(InstBuilder::genControlInst(ccs, InstBuilder::genStoreArrayStructVar(vname, value2, exp)));
            }
        } else {

            // 'select' based delay
            string widx_tmp_name = vname + "_widx_tmp";
            string widx_name = vname + "_widx";

            // Generates table write index
            pushDeclare(InstBuilder::genDecStructVar(widx_name, InstBuilder::genInt32Typed()));
            pushInitMethod(InstBuilder::genStoreStructVar(widx_name, InstBuilder::genInt32NumInst(0)));

            // Generates table init
            pushClearMethod(generateInitArray(vname, ctype, mxd + 1));

            // int w = widx;
            pushComputeDSPMethod(InstBuilder::genControlInst(ccs, InstBuilder::genDecStackVar(widx_tmp_name, InstBuilder::genBasicTyped(Typed::kInt32), InstBuilder::genLoadStructVar(widx_name))));

            // dline[w] = v;
            pushComputeDSPMethod(InstBuilder::genControlInst(ccs, InstBuilder::genStoreArrayStructVar(vname, InstBuilder::genLoadStackVar(widx_tmp_name), exp)));

            // w = w + 1;
            FIRIndex widx_tmp1 = FIRIndex(InstBuilder::genLoadStackVar(widx_tmp_name));
            pushPostComputeDSPMethod(InstBuilder::genControlInst(ccs, InstBuilder::genStoreStackVar(widx_tmp_name, widx_tmp1 + 1)));

            // w = ((w == delay) ? 0 : w);
            FIRIndex widx_tmp2 = FIRIndex(InstBuilder::genLoadStackVar(widx_tmp_name));
            pushPostComputeDSPMethod(InstBuilder::genControlInst(ccs, InstBuilder::genStoreStackVar(widx_tmp_name,
                                                                   InstBuilder::genSelect2Inst(widx_tmp2 == FIRIndex(mxd + 1),
                                                                                               FIRIndex(0),
                                                                                               widx_tmp2))));
            // *widx = w
            pushPostComputeDSPMethod(InstBuilder::genControlInst(ccs, InstBuilder::genStoreStructVar(widx_name, InstBuilder::genLoadStackVar(widx_tmp_name))));
        }
    }

    return exp;
}
