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
#include "compatibility.hh"  // For basename, pathToContent
#include "xtended.hh"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//-------------------------SignalRenderer-------------------------------
// Render a list of signals
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
        int  chan        = 0;
        Tree output_list = fOutputSig;

        fVisited.clear();  // Clear visited for each top-level signal evaluation per sample

        while (!isNil(output_list)) {
            // Render each output in 'chan'
            Tree out_sig = hd(output_list);
            self(out_sig);
            // Get the result which can contain an integer or REAL value
            Node res = popRes();
            int  int_val;
            if (isInt(res, &int_val)) {
                outputs[chan++][fSample] = static_cast<FAUSTFLOAT>(res.getInt());
            } else {
                outputs[chan++][fSample] = static_cast<FAUSTFLOAT>(res.getDouble());
            }
            output_list = tl(output_list);
        }

        // Increment the delay lines and waveforms shared index
        fIOTA++;
    }
}

template <class REAL>
void SignalRenderer<REAL>::visit(Tree sig)
{
    int     i_val;
    int64_t i64_val;
    double  r_val;
    Tree    size_tree, gen_tree, wi_tree, ws_tree, tbl_tree, ri_tree;
    Tree    c_tree, x_tree, y_tree, z_tree;
    Tree    label_tree, type_tree, name_tree, file_tree, sf_tree, sel;
    int     opt_op;
    int     proj_idx_val;  // For isProj

    /*
    if (global::isDebug("SIG_RENDERER")) {
        std::cout << "SignalRenderer : " << ppsig(sig, 64) << std::endl;
        std::cout << "SignalRenderer : fIOTA " << fIOTA << std::endl;
    }
    */

    xtended* xt = (xtended*)getUserData(sig);
    if (xt) {
        vector<Node> args;
        // Interpret all arguments then call the function
        for (Tree b : sig->branches()) {
            self(b);
            args.push_back(popRes());
        }
        Node res = xt->compute(args);
        //  Hack: for 'min/max' res may actually be of type kInt
        int ty = getCertifiedSigType(sig)->nature();
        pushRes((ty == kInt) ? Node(int(res.getDouble())) : res);
    } else if (isSigInt(sig, &i_val)) {
        pushRes(i_val);
    } else if (isSigInt64(sig, &i64_val)) {
        pushRes(i64_val);
    } else if (isSigReal(sig, &r_val)) {
        pushRes(r_val);
    } else if (isSigInput(sig, &i_val)) {
        pushRes(fInputs[i_val][fSample]);
    } else if (isSigOutput(sig, &i_val, x_tree)) {
        self(x_tree);  // Evaluate the expression connected to the output
    } else if (isSigDelay1(sig, x_tree)) {
        self(x_tree);
        Node v1  = popRes();
        Node one = Node(1);
        pushRes(writeReadDelay(x_tree, v1, one));

    } else if (isSigDelay(sig, x_tree, y_tree)) {
        if (isZeroDelay(y_tree)) {
            self(x_tree);
        } else {
            self(x_tree);
            Node v1 = popRes();
            self(y_tree);
            Node v2 = popRes();
            pushRes(writeReadDelay(x_tree, v1, v2));
        }
    } else if (isSigSelect2(sig, sel, x_tree, y_tree)) {
        // Interpret the condition and both branches
        self(sel);
        Node sel_val = popRes();
        self(x_tree);
        Node x_val = popRes();
        self(y_tree);
        Node y_val = popRes();
        // Inverted
        if (sel_val.getInt()) {
            pushRes(y_val);
        } else {
            pushRes(x_val);
        }
    } else if (isSigPrefix(sig, x_tree, y_tree)) {
        self(y_tree);
        if (fIOTA == 0) {
            self(x_tree);
        }
    } else if (isSigBinOp(sig, &opt_op, x_tree, y_tree)) {
        self(x_tree);
        Node v1 = popRes();
        self(y_tree);
        Node v2 = popRes();
        Type x_type_info = getCertifiedSigType(x_tree);
        Type y_type_info = getCertifiedSigType(y_tree);

        // Integer binop when both arguments are integer
        if (x_type_info->nature() == kInt && y_type_info->nature() == kInt) {
            pushRes(gBinOpTable[opt_op]->compute(v1.getInt(), v2.getInt()));
        } else {
            // Otherwise REAL binop
            pushRes(gBinOpTable[opt_op]->compute(v1.getDouble(), v2.getDouble()));
        }
    } else if (isSigFConst(sig, type_tree, name_tree, file_tree)) {
        if (string(tree2str(name_tree)) == "fSamplingFreq") {
            pushRes(fSampleRate);
        } else {
            faustassert(false);
            pushRes(Node(0));
        }
    } else if (isSigWRTbl(sig, size_tree, gen_tree, wi_tree, ws_tree)) {
        if (isNil(wi_tree)) {
            // Nothing
        } else {
            self(wi_tree);
            Node write_id  = popRes();
            int  write_idx = write_id.getInt();
            self(ws_tree);
            Node val_node = popRes();

            auto it_int  = fIntTables.find(sig);
            auto it_real = fRealTables.find(sig);
            if (it_int != fIntTables.end()) {
                it_int->second.write(write_idx, val_node.getInt());
            } else if (it_real != fRealTables.end()) {
                it_real->second.write(write_idx, val_node.getDouble());
            } else {
                faustassert(false);
                return;
            }
        }
    } else if (isSigRDTbl(sig, tbl_tree, ri_tree)) {
        // Interpret table
        self(tbl_tree);

        // Then read its content
        self(ri_tree);
        Node read_id  = popRes();
        int  read_idx = read_id.getInt();

        auto it_int  = fIntTables.find(tbl_tree);
        auto it_real = fRealTables.find(tbl_tree);
        if (it_int != fIntTables.end()) {
            pushRes(it_int->second.read(read_idx));
        } else if (it_real != fRealTables.end()) {
            pushRes(it_real->second.read(read_idx));
        } else {
            faustassert(false);
            pushRes(Node(0));
        }
    } else if (isSigGen(sig, x_tree)) {
        if (fVisitGen) {
            self(x_tree);
        } else {
            pushRes(Node(0));
        }
    } else if (isSigWaveform(sig)) {
        int size  = sig->arity();
        int index = fIOTA % size;
        self(sig->branch(index));
    } else if (isProj(sig, &proj_idx_val, x_tree)) {
        Tree rec_vars, rec_exprs;
        isRec(x_tree, rec_vars, rec_exprs);

        // First visit of the recursive signal
        if (fVisited.find(sig) == fVisited.end()) {
            faustassert(isRec(x_tree, rec_vars, rec_exprs));
            fVisited[sig]++;
            // Render the actual projection
            self(nth(rec_exprs, proj_idx_val));
            Node res = popRes();
            /*
            if (global::isDebug("SIG_RENDERER")) {
                std::cout << "Proj : " << res << "\n";
            }
            */
            Node zero = Node(0);
            pushRes(writeReadDelay(sig, res, zero));

        } else {
            /*
            if (global::isDebug("SIG_RENDERER")) {
                std::cout << "SignalRenderer : next visit of the recursive signal\n";
            }
            */
            Node zero = Node(0);
            pushRes(readDelay(sig, zero));
        }
    } else if (isSigIntCast(sig, x_tree)) {
        self(x_tree);
        Node cur = popRes();
        pushRes(static_cast<int>(cur.getDouble()));
    } else if (isSigBitCast(sig, x_tree)) {
        // Bitcast is complex. For a simple renderer, it might be an identity if types are
        // "close enough" or a reinterpretation of bits (e.g., float bits as int). This renderer
        // doesn't have type info readily on Node to do a true bitcast. Assuming it's a numeric
        // pass-through for now.
        self(x_tree);
    } else if (isSigFloatCast(sig, x_tree)) {
        self(x_tree);
        Node cur = popRes();
        pushRes(static_cast<REAL>(cur.getInt()));
    } else if (isSigButton(sig, label_tree)) {
        pushRes(fInputControls[sig].fZone);
    } else if (isSigCheckbox(sig, label_tree)) {
        pushRes(fInputControls[sig].fZone);
    } else if (isSigVSlider(sig, label_tree, c_tree, x_tree, y_tree, z_tree)) {
        pushRes(fInputControls[sig].fZone);
    } else if (isSigHSlider(sig, label_tree, c_tree, x_tree, y_tree, z_tree)) {
        pushRes(fInputControls[sig].fZone);
    } else if (isSigNumEntry(sig, label_tree, c_tree, x_tree, y_tree, z_tree)) {
        pushRes(fInputControls[sig].fZone);
    } else if (isSigVBargraph(sig, label_tree, x_tree, y_tree, z_tree)) {
        self(z_tree);
        Node val = topRes();
        fOutputControls[sig].setValue(val.getDouble());
    } else if (isSigHBargraph(sig, label_tree, x_tree, y_tree, z_tree)) {
        self(z_tree);
        Node val = topRes();
        fOutputControls[sig].setValue(val.getDouble());
    } else if (isSigSoundfile(sig, label_tree)) {
        // TODO: Implement soundfile reading. Requires state management for file handlers,
        // position, etc.
        pushRes(Node(0));  // Placeholder: outputs silence
    } else if (isSigSoundfileLength(sig, sf_tree, x_tree)) {
        // TODO
        self(sf_tree);
        popRes();
        self(x_tree);
        popRes();
        pushRes(Node(0));
    } else if (isSigSoundfileRate(sig, sf_tree, x_tree)) {
        // TODO
        self(sf_tree);
        popRes();
        self(x_tree);
        popRes();
        pushRes(Node(0));
    } else if (isSigSoundfileBuffer(sig, sf_tree, x_tree, y_tree, z_tree)) {
        // TODO
        self(sf_tree);
        popRes();
        self(x_tree);
        popRes();
        self(y_tree);
        popRes();
        self(z_tree);
        popRes();
        pushRes(Node(0));
    } else if (isSigAttach(sig, x_tree, y_tree)) {
        // Interpret second arg then drop it
        self(y_tree);
        popRes();
        // And return the first one
        self(x_tree);
    } else if (isSigEnable(sig, x_tree, y_tree)) {  // x_tree is condition, y_tree is signal
        self(x_tree);
        Node enable = popRes();  // Renamed enable_cond
        if (enable.getInt() != 0) {
            self(y_tree);
        } else {
            pushRes(Node(0));
        }
    } else if (isSigControl(sig, x_tree, y_tree)) {  // x_tree is name, y_tree is signal
        self(y_tree);
    } else {
        cerr << __FILE__ << ":" << __LINE__ << " ASSERT : unrecognized signal : " << *sig << endl;
        faustassert(false);
    }
}

// Needed functions
Tree DSPToBoxes(const string& name_app, const string& dsp_content, int argc, const char* argv[],
                int* inputs, int* outputs, string& error_msg);

tvec boxesToSignals(Tree box, string& error_msg);

extern "C" void createLibContext();
extern "C" void destroyLibContext();

// Explicit template instantiations
template struct SignalRenderer<float>;
template struct SignalRenderer<double>;
template struct signal_dsp_aux<float>;
template struct signal_dsp_aux<double>;

// External API

/*
 Since the compilation/interpretation context is global, a UNIQUE factory can be created.
 The context has to be be kept until the factory destroys it in deleteSignalDSPFactory.
 */

signal_dsp_factory* createSignalDSPFactoryFromString(const string& name_app,
                                                     const string& dsp_content, int argc,
                                                     const char* argv[], string& error_msg)
{
    createLibContext();

    class SignalPrefix : public SignalIdentity {
       public:
        SignalPrefix() : SignalIdentity() {}

       protected:
        virtual Tree transformation(Tree sig)
        {
            Tree x, y;
            if (isSigPrefix(sig, x, y)) {
                return sigPrefix(self(x), sigDelay1(self(y)));
            } else {
                // Other cases => identity transformation
                return SignalIdentity::transformation(sig);
            }
        }
    };

    try {
        // Using the DSP to Box API
        int  inputs = 0, outputs = 0;
        Tree box = DSPToBoxes(name_app, dsp_content, argc, argv, &inputs, &outputs, error_msg);
        if (!box) {
            goto error;
        }
        // Then the Box to Signal API
        tvec signals = boxesToSignals(box, error_msg);
        if (signals.empty()) {
            goto error;
        }

        // Rewrite prefix trees
        Tree         res = listConvert(signals);
        SignalPrefix SP;
        res = SP.mapself(res);
        typeAnnotation(res, gGlobal->gLocalCausalityCheck);
        
        // Context has to be kept until destroyed in deleteSignalDSPFactory
        return new signal_dsp_factory(res, argc, argv);
    } catch (faustexception& e) {
        error_msg = e.Message();
    }

error:
    destroyLibContext();
    return nullptr;
}

signal_dsp_factory* createSignalDSPFactoryFromFile(const string& filename, int argc,
                                                   const char* argv[], string& error_msg)
{
    string base = basename((char*)filename.c_str());
    size_t pos  = filename.find(".dsp");

    if (pos != string::npos) {
        return createSignalDSPFactoryFromString(base.substr(0, pos), pathToContent(filename), argc,
                                                argv, error_msg);
    } else {
        error_msg = "ERROR : file extension is not the one expected (.dsp expected)\n";
        return nullptr;
    }
}

bool deleteSignalDSPFactory(signal_dsp_factory* factory)
{
    delete factory;
    // Context is destroyed, a new factory can possibly be created...
    destroyLibContext();
    return true;
}
