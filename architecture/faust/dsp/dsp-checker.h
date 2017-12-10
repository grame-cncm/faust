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

#ifndef __dsp_checker__
#define __dsp_checker__

#include <iostream>
#include <cmath>

#include "faust/dsp/dsp.h"

class dsp_checker : public decorator_dsp
{
    
    private:
    
        long long fFP_SUBNORMAL;
        long long fFP_INFINITE;
        long long fFP_NAN;
    
        void getStats(int cout, FAUSTFLOAT** outputs)
        {
            for (int chan = 0; chan < fDSP->getNumOutputs(); chan++) {
                for (int frame = 0; frame < cout; frame++) {
                    FAUSTFLOAT value = outputs[chan][frame];
                    if (std::isnan(value)) {
                        fFP_NAN++;
                    } else if (std::isinf(value)) {
                        fFP_INFINITE++;
                    } else if (std::fpclassify(val) == FP_SUBNORMAL) {
                        fFP_SUBNORMAL++;
                    }
                }
            }
        }
    
    public:
    
        dsp_checker(dsp* dsp):decorator_dsp(dsp)
        {
            fFP_SUBNORMAL = 0;
            fFP_INFINITE = 0;
            fFP_NAN = 0;
        }
    
        void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP->compute(count, inputs, outputs);
            getStats(count, outputs);
        }
        void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP->compute(date_usec, count, inputs, outputs);
            getStats(count, outputs);
        }
    
        void printStats()
        {
            std::cout << "-------------------------------"<< std::endl;
            std::cout << "FP_SUBNORMAL: " << fFP_SUBNORMAL << std::endl;
            std::cout << "FP_INFINITE: " << fFP_INFINITE << std::endl;
            std::cout << "FP_NAN: " << fFP_NAN << std::endl;
            std::cout << "-------------------------------"<< std::endl;
        }
    
};

#endif
