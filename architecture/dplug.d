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

// faust -a dplug.cpp -lang dlang noise.dsp -o noise.d

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
import std.stdio;
import std.conv;
import dplug.core.vec;

class Meta {
nothrow:
@nogc:
    void declare(string name, string value) {}
}

class UI {
nothrow:
@nogc:
    this()
    {
        _faustParams = makeVec!FaustParam();
    }

    void declare(string id, string key, string value) {}
    void declare(int id, string key, string value) {}
    void declare(float* id, string key, string value) {}

    // -- layout groups

    void openTabBox(string label) {}
    void openHorizontalBox(string label) {}
    void openVerticalBox(string label) {}
    void closeBox() {}

    // -- active widgets

    void addButton(string label, float* val) {}
    void addCheckButton(string label, float* val) {}
    void addVerticalSlider(string label, float* val, float init, float min, float max, float step) {}
    void addHorizontalSlider(string label, float* val, float init, float min, float max, float step)
    {
        _faustParams.pushBack(FaustParam(label, val, init, min, max, step));
    }
    void addNumEntry(string label, float* val, float init, float min, float max, float step) {}

    // -- passive display widgets

    void addHorizontalBargraph(string label, float* val, float min, float max) {}
    void addVerticalBargraph(string label, float* val, float min, float max) {}

    FaustParam[] readParams()
    {
        return _faustParams.releaseData();
    }

private:
	Vec!FaustParam _faustParams;
}

struct FaustParam
{
	string label;
	float* val;
	float init;
	float min;
	float max;
	float step;
}

class dsp {
nothrow:
@nogc:
public:
    int fSamplingFreq;
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/

