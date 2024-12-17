/************************************************************************
 ************************************************************************
    FAUST compiler
    Copyright (C) 2024 GRAME, Centre National de Creation Musicale
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

#include "signalRenderer.hh"
#include "compatibility.hh"
#include "xtended.hh"

using namespace std;

//-------------------------SignalRenderer-------------------------------
// Render a signal.
//----------------------------------------------------------------------

template <class REAL>
int signal_dsp_aux<REAL>::getNumInputs()
{
    return fRenderer.fNumInputs;
}

template <class REAL>
int signal_dsp_aux<REAL>::getNumOutputs()
{
    return treeConvert(fRenderer.fOutputSig).size();
}

template <class REAL>
void signal_dsp_aux<REAL>::compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
{
    fRenderer.compute(count, inputs, outputs);
}

template <class REAL>
void SignalRenderer<REAL>::compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
{
    fInputs = inputs;

    for (fSample = 0; fSample < count; fSample++) {
        int  chan   = 0;
        Tree output = fOutputSig;

        while (!isNil(output)) {
            self(hd(output));
            Node res = popRes();
            int  i;
            // Possibly cast the result
            if (isInt(res, &i)) {
                outputs[chan++][fSample] = FAUSTFLOAT(REAL(res.getInt()));
            } else {
                outputs[chan++][fSample] = FAUSTFLOAT(res.getDouble());
            }
            output = tl(output);
            // Reset signals
            fVisited.clear();
        }

        // For delaylines
        fIOTA++;
    }
}

template <class REAL>
void SignalRenderer<REAL>::visit(Tree sig)
{
    int     i, opt;
    int64_t i64;
    double  r;
    Tree    size, gen, wi, ws, tbl, ri, c, sel, x, y, z, u, v, var, le, label, type, name, file, sf;

    xtended* xt = (xtended*)getUserData(sig);
    // Primitive elements
    if (xt) {
        vector<Node> args;
        for (Tree b : sig->branches()) {
            self(b);
            args.push_back(popRes());
        }
        pushRes(xt->compute(args));
    } else if (isSigInt(sig, &i)) {
        pushRes(i);
    } else if (isSigInt64(sig, &i64)) {
        pushRes(i64);
    } else if (isSigReal(sig, &r)) {
        pushRes(r);
    } else if (isSigWaveform(sig)) {
        // TODO
    } else if (isSigInput(sig, &i)) {
        pushRes(fInputs[i][fSample]);
    } else if (isSigOutput(sig, &i, x)) {
        self(x);
    } else if (isSigDelay1(sig, x)) {
        // Evaluate
        self(x);
        Node v1 = popRes();
        // Write and read delayline
        Node one = Node(1);
        pushRes(writeReadDelay(x, v1, one));

    } else if (isSigDelay(sig, x, y)) {
        if (isZeroDelay(y)) {
            self(x);
        } else {
            // Evaluate
            self(x);
            Node v1 = popRes();
            self(y);
            Node v2 = popRes();
            // Write and read delayline
            pushRes(writeReadDelay(x, v1, v2));
        }
    } else if (isSigPrefix(sig, x, y)) {
        self(x);
        self(y);
    } else if (isSigBinOp(sig, &opt, x, y)) {
        self(x);
        Node v1 = popRes();
        self(y);
        Node v2    = popRes();
        int  v1_ty = getCertifiedSigType(x)->nature();
        int  v2_ty = getCertifiedSigType(y)->nature();
        if (v1_ty == kInt && v2_ty == kInt) {
            pushRes(gBinOpTable[opt]->compute(v1.getInt(), v2.getInt()));
        } else {
            pushRes(gBinOpTable[opt]->compute(v1.getDouble(), v2.getDouble()));
        }
    }

    // Foreign variable unctions
    else if (isSigFConst(sig, type, name, file)) {
        // Special case for SR
        if (string(tree2str(name)) == "fSamplingFreq") {
            pushRes(fSampleRate);
        } else {
            faustassert(false);
        }
    }

    // Tables
    else if (isSigWRTbl(sig, size, gen, wi, ws)) {
        // TODO
        self(size);
        self(gen);
        if (wi != gGlobal->nil) {
            // rwtable
            self(wi);
            self(ws);
        }
    } else if (isSigRDTbl(sig, tbl, ri)) {
        // TODO
        self(tbl);
        self(ri);
    }

    // Doc
    else if (isSigDocConstantTbl(sig, x, y)) {
        self(x);
        self(y);
    } else if (isSigDocWriteTbl(sig, x, y, u, v)) {
        self(x);
        self(y);
        self(u);
        self(v);
    } else if (isSigDocAccessTbl(sig, x, y)) {
        self(x);
        self(y);
    }

    // Select2 (and Select3 expressed with Select2)
    else if (isSigSelect2(sig, sel, x, y)) {
        self(sel);
        Node sel_val = popRes();
        self(x);
        Node then_val = popRes();
        self(y);
        Node else_val = popRes();
        // Inverted
        if (sel_val.getInt()) {
            pushRes(else_val);
        } else {
            pushRes(then_val);
        }
    }

    // Table sigGen
    else if (isSigGen(sig, x)) {
        // TODO
        if (fVisitGen) {
            self(x);
        }
    }

    // Recursive signals
    else if (isProj(sig, &i, x)) {
        if (!fVisited.count(sig)) {
            faustassert(isRec(x, var, le));
            fVisited[sig]++;
            // Compute the i projection
            self(nth(le, i));
            Node res  = popRes();
            Node zero = Node(0);
            // Write and read delayline
            pushRes(writeReadDelay(sig, res, zero));
        } else {
            Node one = Node(1);
            // Read delayline
            pushRes(readDelay(sig, one));
        }
    }

    // Int, Bit and Float Cast
    else if (isSigIntCast(sig, x)) {
        self(x);
        Node cur = popRes();
        pushRes(int(cur.getDouble()));
    } else if (isSigBitCast(sig, x)) {
        // TODO
        self(x);
    } else if (isSigFloatCast(sig, x)) {
        self(x);
        Node cur = popRes();
        pushRes(double(cur.getInt()));
    }

    // UI
    // TODO: compute kr separately until ar is reached, using types associated to signals
    else if (isSigButton(sig, label)) {
        pushRes(fInputControls[sig].fZone);
    } else if (isSigCheckbox(sig, label)) {
        pushRes(fInputControls[sig].fZone);
    } else if (isSigVSlider(sig, label, c, x, y, z)) {
        pushRes(fInputControls[sig].fZone);
    } else if (isSigHSlider(sig, label, c, x, y, z)) {
        pushRes(fInputControls[sig].fZone);
    } else if (isSigNumEntry(sig, label, c, x, y, z)) {
        pushRes(fInputControls[sig].fZone);
    } else if (isSigVBargraph(sig, label, x, y, z)) {
        self(z);
        Node val                   = topRes();
        fOutputControls[sig].fZone = val.getDouble();
    } else if (isSigHBargraph(sig, label, x, y, z)) {
        self(z);
        Node val                   = topRes();
        fOutputControls[sig].fZone = val.getDouble();
    }

    // Soundfile length, rate, buffer
    else if (isSigSoundfile(sig, label)) {
        // TODO
    } else if (isSigSoundfileLength(sig, sf, x)) {
        // TODO
        self(sf), self(x);
    } else if (isSigSoundfileRate(sig, sf, x)) {
        // TODO
        self(sf), self(x);
    } else if (isSigSoundfileBuffer(sig, sf, x, y, z)) {
        // TODO
        self(sf), self(x), self(y), self(z);
    }

    // Attach, Enable, Control
    else if (isSigAttach(sig, x, y)) {
        // TODO
        self(x), self(y);

    } else if (isSigEnable(sig, x, y)) {
        // TODO
        self(x), self(y);

    } else if (isSigControl(sig, x, y)) {
        // TODO
        self(x), self(y);
    }

    else if (isSigRegister(sig, &i, x)) {
        // TODO
        self(x);
    }

    else if (isNil(sig)) {
        // now nil can appear in table write instructions
        return;
    } else {
        cerr << __FILE__ << ":" << __LINE__ << " ASSERT : unrecognized signal : " << *sig << endl;
        faustassert(false);
    }
}

// Needed internal API
Tree DSPToBoxes(const string& name_app, const string& dsp_content, int argc, const char* argv[],
                int* inputs, int* outputs, string& error_msg);

tvec boxesToSignals(Tree box, string& error_msg);

extern "C" void createLibContext();
extern "C" void destroyLibContext();

// External C++ API

// Only one factory can be built and used.

signal_dsp_factory* createSignalDSPFactoryFromString(const std::string& name_app,
                                                     const std::string& dsp_content, int argc,
                                                     const char* argv[], std::string& error_msg)
{
    createLibContext();
    try {
        int  inputs, outputs;
        Tree box = DSPToBoxes(name_app, dsp_content, argc, argv, &inputs, &outputs, error_msg);
        if (!box) {
            return nullptr;
        }
        tvec signals = boxesToSignals(box, error_msg);
        if (signals.size() == 0) {
            return nullptr;
        }

        return new signal_dsp_factory(listConvert(signals), argc, argv);
    } catch (faustexception& e) {
        destroyLibContext();
        error_msg = e.Message();
        return nullptr;
    }
}

// Only one factory can be built and used.
signal_dsp_factory* createSignalDSPFactoryFromFile(const std::string& filename, int argc,
                                                   const char* argv[], std::string& error_msg)
{
    string base = basename((char*)filename.c_str());
    size_t pos  = filename.find(".dsp");

    if (pos != string::npos) {
        return createSignalDSPFactoryFromString(base.substr(0, pos), pathToContent(filename), argc,
                                                argv, error_msg);
    } else {
        error_msg = "File Extension is not the one expected (.dsp expected)\n";
        return nullptr;
    }
}

// Has to be used before creating another factory.
bool deleteSignalDSPFactory(signal_dsp_factory* factory)
{
    destroyLibContext();
    delete factory;
    return true;
}
