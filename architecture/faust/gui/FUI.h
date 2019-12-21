/************************** BEGIN FUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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

#ifndef FAUST_FUI_H
#define FAUST_FUI_H

#include <string>
#include <map>
#include <set>
#include <vector>
#include <stack>
#include <iostream>
#include <fstream>

#include "faust/gui/UI.h"
#include "faust/gui/PathBuilder.h"

/*******************************************************************************
 * FUI : used to save and recall the state of the user interface
 * This class provides essentially two new methods saveState() and recallState()
 * used to save on file and recall from file the state of the user interface.
 * The file is human readable and editable
 ******************************************************************************/

class FUI : public UI, public PathBuilder
{

    protected:

        std::map<std::string, FAUSTFLOAT*> fName2Zone;
        std::vector<FAUSTFLOAT*> fButtons;

        // add an element by relating its full name and memory zone
        virtual void addElement(const char* label, FAUSTFLOAT* zone, bool button = false)
        {
            std::string path = buildPath(label);
            fName2Zone[path] = zone;
            if (button) {
                fButtons.push_back(zone);
            }
        }

    
    public:

        FUI() {}
        virtual ~FUI() {}

        // -- Save and recall methods

        // save the zones values and full names
        virtual void saveState(const char* filename)
        {
            std::ofstream file(filename);
            std::map<std::string, FAUSTFLOAT*>::iterator it;
            
            if (file.is_open()) {
                for (it = fName2Zone.begin(); it != fName2Zone.end(); ++it) {
                    file << *(*it).second << ' ' << (*it).first << std::endl;
                }

                file << std::endl;
                file.close();
            } else {
                 std::cerr << "Error opening " << filename << " file\n";
            }
        }

        // recall the zones values and full names
        virtual void recallState(const char* filename)
        {
            std::ifstream file(filename);
            FAUSTFLOAT value;
            std::string path1, path2;
            while (file.good()) {
                file >> value >> path1;
                path2 = "/" + path1;
                if (fName2Zone.count(path1) > 0) {          // Old path system
                    *(fName2Zone[path1]) = value;
                } else if (fName2Zone.count(path2) > 0) {   // New path system with the starting '/'
                    *(fName2Zone[path2]) = value;
                } else if (path1.size() > 0) {
                    std::cerr << "recallState : parameter not found : " << path1 << " with value : " << value << std::endl;
                }
            }
            file.close();
        }

        void setButtons(bool state)
        {
            for (size_t i = 0; i < fButtons.size(); i++) {
                *fButtons[i] = state;
            }
        }

        // -- widget's layouts (just keep track of group labels)

        virtual void openTabBox(const char* label) { pushLabel(label); }
        virtual void openHorizontalBox(const char* label) { pushLabel(label);; }
        virtual void openVerticalBox(const char* label) { pushLabel(label); }
        virtual void closeBox() { popLabel(); };

        // -- active widgets (just add an element)

        virtual void addButton(const char* label, FAUSTFLOAT* zone) { addElement(label, zone, true); }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) { addElement(label, zone); }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT)
                                                                    { addElement(label, zone); }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT)
                                                                    { addElement(label, zone); }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT)
                                                                    { addElement(label, zone); }

        // -- passive widgets (are ignored)

        virtual void addHorizontalBargraph(const char*, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT) {};
        virtual void addVerticalBargraph(const char*, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT) {};
    
        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}

        // -- metadata are not used

        virtual void declare(FAUSTFLOAT*, const char*, const char*) {}

};

#endif

/**************************  END  FUI.h **************************/
