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

/*******************************************************************************
 * FUI : used to save and recall the state of the user interface
 * This class provides essentially two new methods saveState() and recallState()
 * used to save on file and recall from file the state of the user interface.
 * The file is human readable and editable
 ******************************************************************************/

class FUI : public UI
{

    protected:

        std::stack<std::string> fGroupStack;
        std::vector<std::string> fNameList;
        std::map<std::string, FAUSTFLOAT*> fName2Zone;
        std::vector<FAUSTFLOAT*> fButtons;

        // labels are normalized by replacing white spaces by underscores and by removing parenthesis
        std::string normalizeLabel(const char* label)
        {
            std::string s;
            char c;

            while ((c = *label++)) {
                if (isspace(c)) { s += '_'; }
                //else if ((c == '(') | (c == ')') ) 	{ }
                else { s += c; }
            }
            return s;
        }

        // add an element by relating its full name and memory zone
        virtual void addElement(const char* label, FAUSTFLOAT* zone, bool button = false)
        {
            std::string fullname (fGroupStack.top() + '/' + normalizeLabel(label));
            fNameList.push_back(fullname);
            fName2Zone[fullname] = zone;
            if (button) {
                fButtons.push_back(zone);
            }
        }

        // keep track of full group names in a stack
        virtual void pushGroupLabel(const char* label)
        {
            if (fGroupStack.empty()) {
                fGroupStack.push(normalizeLabel(label));
            } else {
                fGroupStack.push(fGroupStack.top() + '/' + normalizeLabel(label));
            }
        }

        virtual void popGroupLabel()
        {
            fGroupStack.pop();
        }

    public:

        FUI() {}
        virtual ~FUI() {}

        // -- Save and recall methods

        // save the zones values and full names
        virtual void saveState(const char* filename)
        {
            std::ofstream f(filename);

            for (unsigned int i = 0; i < fNameList.size(); i++) {
                std::string	n = fNameList[i];
                FAUSTFLOAT*	z = fName2Zone[n];
                f << *z << ' ' << n << std::endl;
            }

            f << std::endl;
            f.close();
        }

        // recall the zones values and full names
        virtual void recallState(const char* filename)
        {
            std::ifstream f(filename);
            FAUSTFLOAT v;
            std::string n;

            while (f.good()) {
                f >> v >> n;
                if (fName2Zone.count(n) > 0) {
                    *(fName2Zone[n]) = v;
                } else if (n.size() > 0) {
                    std::cerr << "recallState : parameter not found : " << n << " with value : " << v << std::endl;
                }
            }
            f.close();
        }

        void setButtons(bool state)
        {
            for (int i = 0; i < fButtons.size(); i++) {
                *fButtons[i] = state;
            }
        }

        // -- widget's layouts (just keep track of group labels)

        virtual void openTabBox(const char* label) { pushGroupLabel(label); }
        virtual void openHorizontalBox(const char* label) { pushGroupLabel(label); }
        virtual void openVerticalBox(const char* label) { pushGroupLabel(label); }
        virtual void closeBox() { popGroupLabel(); };

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

        // -- metadata are not used

        virtual void declare(FAUSTFLOAT*, const char*, const char*) {}

};

#endif

