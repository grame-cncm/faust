/************************** BEGIN SaveUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019-2020 GRAME, Centre National de Creation Musicale
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

#ifndef FAUST_SAVEUI_H
#define FAUST_SAVEUI_H

#include "faust/gui/DecoratorUI.h"
#include "faust/gui/PathBuilder.h"

// Base class to handle controllers state save/load

class SaveUI : public GenericUI {

    protected:
    
        struct SavedZone {
            FAUSTFLOAT* fZone;
            FAUSTFLOAT fCurrent;
            FAUSTFLOAT fInit;
            
            SavedZone():fZone(nullptr), fCurrent(FAUSTFLOAT(0)), fInit(FAUSTFLOAT(0))
            {}
            SavedZone(FAUSTFLOAT* zone, FAUSTFLOAT current, FAUSTFLOAT init)
            :fZone(zone), fCurrent(current), fInit(init)
            {
                *fZone = current;
            }
            ~SavedZone()
            {}
        };
        
        std::map<std::string, SavedZone> fName2Zone;
    
        virtual void addItem(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init) = 0;
    
    public:
    
        SaveUI() {}
        virtual ~SaveUI() {}
    
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addItem(label, zone, FAUSTFLOAT(0));
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addItem(label, zone, FAUSTFLOAT(0));
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addItem(label, zone, init);
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addItem(label, zone, init);
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addItem(label, zone, init);
        }

        void reset()
        {
            for (auto& it : fName2Zone) {
                *it.second.fZone = it.second.fInit;
            }
        }
        
        void display()
        {
            for (auto& it : fName2Zone) {
                std::cout << "SaveUI::display path = " << it.first << " value = " << *it.second.fZone << std::endl;
            }
        }
        
        void save()
        {
            for (auto& it : fName2Zone) {
                it.second.fCurrent = *it.second.fZone;
            }
        }
};

/*
 Save/load current value using the label, reset to init value
 */

class SaveLabelUI : public SaveUI {
    
    protected:
    
        void addItem(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init)
        {
            if (fName2Zone.find(label) != fName2Zone.end()) {
                FAUSTFLOAT current = fName2Zone[label].fCurrent;
                fName2Zone[label] = SavedZone(zone, current, init);
            } else {
                fName2Zone[label] = SavedZone(zone, init, init);
            }
        }
        
    public:
        
        SaveLabelUI() : SaveUI() {}
        virtual ~SaveLabelUI() {}        
   
};

/*
 Save/load current value using the complete path, reset to init value
*/

class SavePathUI : public SaveUI, public PathBuilder {
    
    protected:
    
        void openTabBox(const char* label) { pushLabel(label); }
        void openHorizontalBox(const char* label) { pushLabel(label);; }
        void openVerticalBox(const char* label) { pushLabel(label); }
        void closeBox() { popLabel(); };
    
        void addItem(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init)
        {
            std::string path = buildPath(label);
            if (fName2Zone.find(path) != fName2Zone.end()) {
                FAUSTFLOAT current = fName2Zone[path].fCurrent;
                fName2Zone[path] = SavedZone(zone, current, init);
            } else {
                fName2Zone[path] = SavedZone(zone, init, init);
            }
        }
   
    public:

        SavePathUI(): SaveUI() {}
        virtual ~SavePathUI() {}

};

#endif

/**************************  END  SaveUI.h **************************/
