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

// faust -a params.d -lang dlang noise.dsp -o noise.d

import dplug.core.vec;

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

    override void addButton(string label, FAUSTFLOAT* val)
    {
        _faustParams.pushBack(FaustParam(label, val, 0, 0, 0, 0, true));
    }
    
    override void addCheckButton(string label, FAUSTFLOAT* val)
    {
        _faustParams.pushBack(FaustParam(label, val, 0, 0, 0, 0, true));
    }
    
    override void addVerticalSlider(string label, FAUSTFLOAT* val, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        _faustParams.pushBack(FaustParam(label, val, init, min, max, step));
    }

    override void addHorizontalSlider(string label, FAUSTFLOAT* val, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        _faustParams.pushBack(FaustParam(label, val, init, min, max, step));
    }

    override void addNumEntry(string label, FAUSTFLOAT* val, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        _faustParams.pushBack(FaustParam(label, val, init, min, max, step));
    }

    FaustParam[] readParams()
    {
        return _faustParams.releaseData();
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
}

struct FaustParam
{
	string label;
	FAUSTFLOAT* val;
	FAUSTFLOAT initial;
	FAUSTFLOAT min;
	FAUSTFLOAT max;
	FAUSTFLOAT step;
    bool isButton = false;
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

