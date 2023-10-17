/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************
 ************************************************************************/

// faust -a dplug.d -lang dlang noise.dsp -o noise.d

import dplug.core.vec;
import dplug.client;
import core.stdc.stdlib : strtol;

alias FAUSTFLOAT = float;

class Meta {
nothrow:
@nogc:
    void declare(string name, string value) {}
}

class UI {
nothrow:
@nogc:
    void declare(string id, string key, string value) {}
    void declare(int id, string key, string value) {}
    void declare(FAUSTFLOAT* id, string key, string value) {}

    // -- layout groups

    void openTabBox(string label) {}
    void openHorizontalBox(string label) {}
    void openVerticalBox(string label) {}
    void closeBox() {}

    // -- active widgets

    void addButton(string label, FAUSTFLOAT* val) {}
    void addCheckButton(string label, FAUSTFLOAT* val) {}
    void addVerticalSlider(string label, FAUSTFLOAT* val, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
    void addHorizontalSlider(string label, FAUSTFLOAT* val, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
    void addNumEntry(string label, FAUSTFLOAT* val, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}

    // -- passive display widgets

    void addHorizontalBargraph(string label, FAUSTFLOAT* val, FAUSTFLOAT min, FAUSTFLOAT max) {}
    void addVerticalBargraph(string label, FAUSTFLOAT* val, FAUSTFLOAT min, FAUSTFLOAT max) {}
}

interface dsp {
nothrow:
@nogc:
public:
    void metadata(Meta* m);
    int getNumInputs();
    int getNumOutputs();
    void buildUserInterface(UI* uiInterface);
    int getSampleRate();
    void instanceInit(int sample_rate);
    void instanceResetUserInterface();
    void compute(int count, FAUSTFLOAT*[] inputs, FAUSTFLOAT*[] outputs);
    void initialize(int sample_rate);
}

/**
 * Implements and overrides the methods that would provide parameters for use in 
 * a plug-in or GUI.  These parameters are stored in a vector which can be accesed via
 * `readParams()`
 */
class FaustParamAccess : UI {
nothrow:
@nogc:
    this()
    {
        _faustParams = makeVec!FaustParam();
    }

    override void declare(FAUSTFLOAT* id, string key, string value)
    {
        if (value == "")
        {
            nextParamId = cast(int)strtol(key.ptr, null, 0);
        }
        else if (key == "unit")
        {
            nextParamUnit = value;
        }
    }

    override void addButton(string label, FAUSTFLOAT* val)
    {
        _faustParams.pushBack(FaustParam(label, nextParamUnit, val, 0, 0, 0, 0, true, nextParamId));
        resetNextParamMeta();
    }
    
    override void addCheckButton(string label, FAUSTFLOAT* val)
    {
        _faustParams.pushBack(FaustParam(label, nextParamUnit, val, 0, 0, 0, 0, true, nextParamId));
        resetNextParamMeta();
    }
    
    override void addVerticalSlider(string label, FAUSTFLOAT* val, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        _faustParams.pushBack(FaustParam(label, nextParamUnit, val, init, min, max, step, false, nextParamId));
        resetNextParamMeta();
    }

    override void addHorizontalSlider(string label, FAUSTFLOAT* val, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        _faustParams.pushBack(FaustParam(label, nextParamUnit, val, init, min, max, step, false, nextParamId));
        resetNextParamMeta();
    }

    override void addNumEntry(string label, FAUSTFLOAT* val, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        _faustParams.pushBack(FaustParam(label, nextParamUnit, val, init, min, max, step, false, nextParamId));
        resetNextParamMeta();
    }

    FaustParam[] readParams()
    {
        /* return _faustParams.releaseData(); */
        /* Vec!FaustParam _sortedList = makeVec!FaustParam(); */
        return sortParams(_faustParams.releaseData());
    }

    FaustParam readParam(int index)
    {
        return _faustParams[index];
    }

    ulong length()
    {
        return _faustParams.length();
    }

private:
    Vec!FaustParam _faustParams;
    int nextParamId = -1;
    string nextParamUnit = "";

    void resetNextParamMeta()
    {
        nextParamId = -1;
        nextParamUnit = "";
    }

    // simple bubble sort
    FaustParam[] sortParams(FaustParam[] params)
    {
        bool success = true;
        do
        {
            success = true;
            for(int i = 0; i < params.length - 1; ++i)
            {
                auto left = params[i];
                auto right = params[i + 1];
                if (right.ParamId < left.ParamId)
                {
                    params[i] = right;
                    params[i + 1] = left;
                    success = false;
                }
            }
        }
        while(!success);
        return params;
    }
}

struct FaustParam
{
    string label;
    string unit;
    FAUSTFLOAT* val;
    FAUSTFLOAT initial;
    FAUSTFLOAT min;
    FAUSTFLOAT max;
    FAUSTFLOAT step;
    bool isButton = false;
    int ParamId;
}

version(unittest){}
version(faustoverride){}
else
mixin(pluginEntryPoints!FaustClient);

class FaustClient : dplug.client.Client
{
public:
nothrow:
@nogc:

    this()
    {
        buildFaustModule();
    }

    void buildFaustModule()
    {
        _dsp = mallocNew!(FAUSTCLASS)();
        FaustParamAccess _faustUI = mallocNew!FaustParamAccess();
        _dsp.buildUserInterface(cast(UI*)(&_faustUI));
        _faustParams = _faustUI.readParams();
    }

    override PluginInfo buildPluginInfo()
    {
        // Plugin info is parsed from plugin.json here at compile time.
        // Indeed it is strongly recommended that you do not fill PluginInfo 
        // manually, else the information could diverge.
        static immutable PluginInfo pluginInfo = parsePluginInfo(import("plugin.json"));
        return pluginInfo;
    }

    // This is an optional overload, default is zero parameter.
    // Caution when adding parameters: always add the indices
    // in the same order as the parameter enum.
    override Parameter[] buildParameters()
    {
        auto params = makeVec!Parameter();

        // Add faust parameters
        buildFaustModule();
        int faustParamIndexStart = 0;
        foreach(param; _faustParams)
        {
            if (param.isButton)
            {
                params ~= mallocNew!BoolParameter(faustParamIndexStart++, param.label, cast(bool)(*param.val));
            }
            else if (param.step == 1.0f) {
                params ~= mallocNew!IntegerParameter(faustParamIndexStart++, param.label, param.unit, cast(int)param.min, cast(int)param.max, cast(int)param.initial);
            }
            else
            {
                params ~= mallocNew!LinearFloatParameter(faustParamIndexStart++, param.label, param.unit, param.min, param.max, param.initial);
            }
        }

        return params.releaseData();
    }

    override LegalIO[] buildLegalIO()
    {
        auto io = makeVec!LegalIO();
        if (_dsp is null)
        {
            _dsp = mallocNew!(FAUSTCLASS)();
        }
        io ~= LegalIO(_dsp.getNumInputs(), _dsp.getNumOutputs());
        return io.releaseData();
    }

    // This override is optional, the default implementation will
    // have one default preset.
    override Preset[] buildPresets() nothrow @nogc
    {
        auto presets = makeVec!Preset();
        presets ~= makeDefaultPreset();
        return presets.releaseData();
    }

    // This override is also optional. It allows to split audio buffers in order to never
    // exceed some amount of frames at once.
    // This can be useful as a cheap chunking for parameter smoothing.
    // Buffer splitting also allows to allocate statically or on the stack with less worries.
    override int maxFramesInProcess() const //nothrow @nogc
    {
        return 512;
    }

    override void reset(double sampleRate, int maxFrames, int numInputs, int numOutputs) nothrow @nogc
    {
        // Clear here any state and delay buffers you might have.
        _dsp.initialize(cast(int)sampleRate);
        assert(maxFrames <= 512); // guaranteed by audio buffer splitting
    }

    void updateFaustParams()
    {
        foreach(param; params())
        {            
            int paramIndex = param.index();
            foreach(faustParam; _faustParams)
            {
                if (paramIndex == faustParam.ParamId)
                {
                    if (cast(FloatParameter)param)
                    {
                        *(faustParam.val) = (cast(FloatParameter)param).valueAtomic();
                    }
                    else if (cast(IntegerParameter)param)
                    {
                        *(faustParam.val) = cast(FAUSTFLOAT)((cast(IntegerParameter)param).valueAtomic());
                    }
                    else if (cast(BoolParameter)param)
                    {
                        *(faustParam.val) = cast(FAUSTFLOAT)((cast(BoolParameter)param).valueAtomic());
                    }
                    else
                    {
                        assert(false, "Parameter type not implemented");
                    }
                }
            }
        }
    }

    override void processAudio(const(float*)[] inputs, float*[]outputs, int frames,
                               TimeInfo info) nothrow @nogc
    {
        assert(frames <= 512); // guaranteed by audio buffer splitting

        int numInputs = cast(int)inputs.length;
        int numOutputs = cast(int)outputs.length;

        int minChan = numInputs > numOutputs ? numOutputs : numInputs;

        // do reverb
        updateFaustParams();
        _dsp.compute(frames, cast(float*[])inputs, cast(float*[])outputs);

        // fill with zero the remaining channels
        for (int chan = minChan; chan < numOutputs; ++chan)
            outputs[chan][0..frames] = 0; // D has array slices assignments and operations
    }

protected:
    FAUSTCLASS _dsp;
    UI _faustUI;
    FaustParam[] _faustParams;
}

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/

<<includeIntrinsic>>

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

/********************END ARCHITECTURE SECTION (part 2/2)****************/

