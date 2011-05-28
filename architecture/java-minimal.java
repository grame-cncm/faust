/************************************************************************
    FAUST Architecture File
	Copyright (C) 2011 Kjetil Matheussen
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
    This architechture file needs more work.
 ***/



<<includeIntrinsic>>

class Meta{
    void declare(String name, String value){
    }
}

interface FaustVarAccess{
    public void set(float val);
    public float get();
}

class UI{
    // -- layout groups
    
    public void openFrameBox(String label){}   
    public void openTabBox(String label){}
    public void openHorizontalBox(String label){}
    public void openVerticalBox(String label){}

    // -- extra widget's layouts

    public void openDialogBox(String label, FaustVarAccess varAccess){}
    public void openEventBox(String label){}
    public void openHandleBox(String label){}
    public void openExpanderBox(String label, FaustVarAccess varAccess){}
    
    public void closeBox(){}
    public void adjustStack(int n){}

    // -- active widgets
    
    public void addButton(String label, FaustVarAccess varAccess){}
    public void addToggleButton(String label, FaustVarAccess varAccess){}
    public void addCheckButton(String label, FaustVarAccess varAccess){}
    public void addVerticalSlider(String label, FaustVarAccess varAccess, float init, float min, float max, float step){}   
    public void addHorizontalSlider(String label, FaustVarAccess varAccess, float init, float min, float max, float step){} 
    public void addKnob(String label, FaustVarAccess varAccess, float init, float min, float max, float step){}
    public void addNumEntry(String label, FaustVarAccess varAccess, float init, float min, float max, float step){}
    
    // -- passive display widgets
    
    public void addNumDisplay(String label, FaustVarAccess varAccess, int precision){}
    public void addTextDisplay(String label, FaustVarAccess varAccess, String names[], float min, float max){}
    public void addHorizontalBargraph(String label, FaustVarAccess varAccess, float min, float max){}
    public void addVerticalBargraph(String label, FaustVarAccess varAccess, float min, float max){}

}

class dsp{
    float fSamplingFreq;
}


<<includeclass>>


