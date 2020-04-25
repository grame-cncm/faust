/************************** BEGIN PrintUI.h **************************/
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

#ifndef FAUST_PRINTUI_H
#define FAUST_PRINTUI_H

#include <vector>
#include <string>
#include <iostream>

#include "faust/gui/UI.h"
#include "faust/gui/PathBuilder.h"

/*******************************************************************************
 * PrintUI : Faust User Interface
 * This class print arguments given to calls to UI methods and build complete path for labels.
 ******************************************************************************/

class PrintUI : public PathBuilder, public UI
{

    public:

        PrintUI() {}
        virtual ~PrintUI() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label)
        {
            pushLabel(label);
            std::cout << "openTabBox label : [" << label << "]" << std::endl;
        }
        virtual void openHorizontalBox(const char* label)
        {
            pushLabel(label);
            std::cout << "openHorizontalBox label : [" << label << "]" << std::endl;
        }
        virtual void openVerticalBox(const char* label)
        {
            pushLabel(label);
            std::cout << "openVerticalBox label : [" << label << "]" << std::endl;
        }
        virtual void closeBox()
        {
            popLabel();
            std::cout << "closeBox" << std::endl;
        }

        // -- active widgets

        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            std::cout << "addButton label : [" << buildPath(label) << "]" << std::endl;
        }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            std::cout << "addCheckButton label : [" << buildPath(label) << "]" << std::endl;
        }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            std::cout << "addVerticalSlider label : [" << buildPath(label) << " init : " << init << " min : " << min << " max : " << max << " step : " << step << "]" << std::endl;
        }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            std::cout << "addHorizontalSlider label : [" << buildPath(label) << " init : " << init << " min : " << min << " max : " << max << " step : " << step << "]" << std::endl;
        }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            std::cout << "addNumEntry label : [" << buildPath(label) << " init : " << init << " min : " << min << " max : " << max << " step : " << step << "]" << std::endl;
        }

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
        {
            std::cout << "addHorizontalBargraph label : [" << buildPath(label) << " min : " << min << " max : " << max << "]" << std::endl;
        }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            std::cout << "addVerticalBargraph label : [" << buildPath(label) << " min : " << min << " max : " << max << "]" << std::endl;
        }
    
        // -- soundfiles
    
        virtual void addSoundfile(const char* label, const char* filename,  Soundfile** sf_zone)
        {
            std::cout << "addSoundfile label : [" << buildPath(label) << " filename :" << filename << "]" << std::endl;
        }

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            std::cout << "declare key : [" << key << " val : " << val << "]" << std::endl;
        }
    
};

#endif // FAUST_PRINTUI_H
/**************************  END  PrintUI.h **************************/
