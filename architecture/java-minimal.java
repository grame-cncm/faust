/************************************************************************
    FAUST Architecture File
    Copyright (C) 2011 Kjetil Matheussen
    Copyright (C) 2013 Grame
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

/***
    This architecture file needs more work.
 ***/

<<includeIntrinsic>>

import java.lang.Math;

class Meta {
    void declare(String name, String value) {}
}

interface FaustVarAccess {
    public String getId();
    public void set(float val);
    public float get();
}

class UI {

    public void declare(String id, String key, String value) {}

    // -- layout groups

    public void openTabBox(String label) {}
    public void openHorizontalBox(String label) {}
    public void openVerticalBox(String label) {}
    public void closeBox() {}

    // -- active widgets

    public void addButton(String label, FaustVarAccess varAccess) {}
    public void addCheckButton(String label, FaustVarAccess varAccess) {}
    public void addVerticalSlider(String label, FaustVarAccess varAccess, float init, float min, float max, float step) {}
    public void addHorizontalSlider(String label, FaustVarAccess varAccess, float init, float min, float max, float step) {}
    public void addNumEntry(String label, FaustVarAccess varAccess, float init, float min, float max, float step) {}

    // -- passive display widgets

    public void addHorizontalBargraph(String label, FaustVarAccess varAccess, float min, float max) {}
    public void addVerticalBargraph(String label, FaustVarAccess varAccess, float min, float max) {}

}

class dsp {

    public int fSamplingFreq;
}

<<includeclass>>


