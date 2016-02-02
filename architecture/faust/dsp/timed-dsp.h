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

#ifndef __timed_dsp__
#define __timed_dsp__

#include "faust/dsp/dsp.h" 
#include "faust/gui/GUI.h" 
#include "faust/gui/ring-buffer.h"

#include <vector>
#include <map>
#include <float.h>

double GetCurrentTimeInUsec();

//----------------------------------------------------------------
//  Timed signal processor definition
//----------------------------------------------------------------

class timed_dsp : public decorator_dsp {

    protected:
        
        double fSamplingFreq;
        double fDateUsec;       // Compute call date in usec
        double fOffsetUsec;     // Compute call offset in usec
        bool fFirstCallback;
        
        void computeSlice(int offset, int slice, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 
        {
            if (slice > 0) {
                printf("fDSP->getNumInputs() %d fDSP->getNumOutputs() %d\n", fDSP->getNumInputs(), fDSP->getNumOutputs());
                FAUSTFLOAT* inputs_slice[fDSP->getNumInputs()];
                FAUSTFLOAT* outputs_slice[fDSP->getNumOutputs()];
                
                for (int chan = 0; chan < fDSP->getNumInputs(); chan++) {
                    inputs_slice[chan] = &(inputs[chan][offset]);
                }
                for (int chan = 0; chan < fDSP->getNumOutputs(); chan++) {
                    outputs_slice[chan] = &(outputs[chan][offset]);
                }
                
                fDSP->compute(slice, inputs_slice, outputs_slice);
            } 
        }
        
        double convertUsecToSample(double usec)
        {
            return std::max(0., (fSamplingFreq * (usec - fDateUsec)) / 1000000.);
        }
        
        virtual void computeAux(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs, bool convert_ts)
        {
            int control_change_count = 0;
             ztimedmap::iterator it1, it2;
             
            // Time sort values associated with zones
            for (it1 = GUI::gTimedZoneMap.begin(); it1 != GUI::gTimedZoneMap.end(); it1++) {
                // Keep number of all control values changes
                control_change_count += ringbuffer_read_space((*it1).second) / (sizeof(double) + sizeof(FAUSTFLOAT));
            }
             
            // Do audio computation "slice" by "slice"
            int slice, offset = 0;
            
            // Compute audio slices...
            while (control_change_count-- > 0) {
                
                double cur_zone_date = DBL_MAX;
              
                // Find date of next audio slice to compute
                for (it1 = GUI::gTimedZoneMap.begin(); it1 != GUI::gTimedZoneMap.end(); it1++) {
                    // If value list is not empty, get the date and keep the minimal one
                    ringbuffer_t* values = (*it1).second;
                    
                    if (ringbuffer_read_space(values) > 0) {
                        double date;
                        if (ringbuffer_peek(values, (char*)&date, sizeof(double)) != sizeof(double)) {
                            std::cout << "ringbuffer_peek error date" << std::endl;
                        } else if (date < cur_zone_date) {
                            it2 = it1;
                            cur_zone_date = date;
                        }
                    }
                }
                
                // If needed, convert cur_zone_date in samples from begining of the buffer, possible moving to 0 (if negative)
                if (convert_ts) {
                    cur_zone_date = convertUsecToSample(cur_zone_date);
                }
                 
                // Compute audio slice
                slice = int(cur_zone_date) - offset;
                computeSlice(offset, slice, inputs, outputs);
                offset += slice;
                
                // Update control
                ringbuffer_t* values = (*it2).second;
                double date;
                if (ringbuffer_read(values, (char*)&date, sizeof(double)) != sizeof(double)) {
                    std::cout << "ringbuffer_peek error date" << std::endl;
                }
                
                FAUSTFLOAT value;
                if (ringbuffer_read(values, (char*)&value, sizeof(FAUSTFLOAT)) != sizeof(FAUSTFLOAT)) {
                    std::cout << "ringbuffer_read error value" << std::endl;
                }
                
                *((*it2).first) = value;
            } 
            
            // Compute last audio slice
            slice = count - offset;
            computeSlice(offset, slice, inputs, outputs);
        }

    public:

        timed_dsp(dsp* dsp):decorator_dsp(dsp),fSamplingFreq(0), fDateUsec(0),fOffsetUsec(0), fFirstCallback(true) 
        {}
        virtual ~timed_dsp() 
        {}
        
        virtual void init(int samplingRate)
        {
            fSamplingFreq = double(samplingRate);
            fDSP->init(samplingRate);
        }
        
        // Default method take a timestamp at 'compute' call time
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            compute(GetCurrentTimeInUsec(), count, inputs, outputs);
        }    
        
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            if (date_usec == -1) {
                // JACK mode : timestamp is already in frames
                computeAux(count, inputs, outputs, false);
            } else {
                // Save the timestamp offset in the first callback
                if (fFirstCallback) {
                    fOffsetUsec = GetCurrentTimeInUsec() - date_usec;
                    fDateUsec = date_usec + fOffsetUsec;
                    fFirstCallback = false;
                }
                
                // RtMidi mode : timestamp must be converted in frames
                computeAux(count, inputs, outputs, true);
                
                // Keep call date 
                fDateUsec = date_usec + fOffsetUsec;
            }
        }
        
};

#endif
