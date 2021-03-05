/************************************************************************
 FAUST Architecture File
 Copyright (C) 2016 GRAME, Centre National de Creation Musicale
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
 
 ************************************************************************/

#include <iostream>

#include "faust/dsp/llvm-dsp.h"
#include "faust/gui/LayoutUI.h"

using namespace std;

int main(int argc, char* argv[])
{
    cout << "Libfaust version : " << getCLibFaustVersion() << endl;
    
    string error_msg;
    dsp_factory* factory = createDSPFactoryFromFile(argv[argc-1], 0, nullptr, "", error_msg, -1);
    
    if (!factory) {
        cerr << error_msg;
        exit(EXIT_FAILURE);
    }
    
    dsp* DSP = factory->createDSPInstance();
    
    if (!DSP) {
        cerr << "Cannot allocate instance\n";
        exit(EXIT_FAILURE);
    }
    
    LayoutUI layoutUI;
    DSP->buildUserInterface(&layoutUI);
    
    {
        cout << "==========================" << endl;
        for (auto& it : layoutUI.fPathItemMap) {
            cout << it.first << endl;
            cout << it.second << endl;
        }
        
        cout << "Width " << layoutUI.fCurrentGroup->getWidth() << endl;
        cout << "Height " << layoutUI.fCurrentGroup->getHeight() << endl;
    }
    
    {
        cout << "==========================" << endl;
        layoutUI.fCurrentGroup->setSize(100.f, 30.f);
        layoutUI.fCurrentGroup->setPos(0.f, 0.f);
        
        for (auto& it : layoutUI.fPathItemMap) {
            cout << it.first << endl;
            cout << it.second << endl;
        }
        
        cout << "Width " << layoutUI.fCurrentGroup->getWidth() << endl;
        cout << "Height " << layoutUI.fCurrentGroup->getHeight() << endl;
    }
        
    delete DSP;
    deleteDSPFactory(static_cast<llvm_dsp_factory*>(factory));
    return 0;
}


