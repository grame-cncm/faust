/************************************************************************
    IMPORTANT NOTE : this file contains two clearly delimited sections :
    the ARCHITECTURE section (in two parts) and the USER section. Each section
    is governed by its own copyright and license. Please check individually
    each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
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
 
/******************************************************************************
*******************************************************************************

								FAUST DSP

*******************************************************************************
*******************************************************************************/

#ifndef __dsp__
#define __dsp__

#include "faust/dsp/dsp.h" 
#include <vector>

class TimedUI;

//----------------------------------------------------------------
//  Timed signal processor definition
//----------------------------------------------------------------

class timed_dsp : public decorator_dsp {

    protected:
    
        std::vector<TimedUI*> fControlers;

    public:

        timed_dsp(dsp* dsp):decorator_dsp(dsp) {}
        virtual ~timed_dsp() {}
        
        virtual void buildUserInterface(UI* ui_interface)   
        { 
            // Keep TimedUI interfaces
            TimedUI* timed_ui = dynamic_cast<TimedUI*>(ui_interface);
            if (timed_ui) fControlers.push_back(timed_ui);
            
            fDSP->buildUserInterface(ui_interface); 
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            std::vector<TimedUI*>::iterator it;
            
            for (it = fControlers.begin(); it != fControlers.end(); it++) {
                TimedUI* controler= (*it);
                std::vector<FAUSTFLOAT> values;
                
                std::vector<FAUSTFLOAT>:iterator it1;
                for (it1 = values.begin(); it1 != values.end(); it1++) {
                    TimedUI* controler = (*it);
                }
                  
            }
        }
        
};

#endif
