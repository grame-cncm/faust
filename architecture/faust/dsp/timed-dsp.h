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
#include <vector>
#include <map>
#include <float.h>

double GetCurrentTimeInUsec();

//----------------------------------------------------------------
//  Timed signal processor definition
//----------------------------------------------------------------

typedef std::vector<ts_value>::iterator value_it;

class timed_dsp : public decorator_dsp {

    protected:
        
        double fDateUsec;
        double fOffsetUsec;
        bool fFirstCallback;
        
        static bool compareDate(const ts_value& a, const ts_value& b) { return a.first < b.first; }
        
        void computeSlice(int offset, int slice, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 
        {
            // Do audio compilation "slice" by "slice"
            FAUSTFLOAT* inputs_slice[fDSP->getNumInputs()];
            FAUSTFLOAT* outputs_slice[fDSP->getNumOutputs()];
            
            for (int chan = 0; chan < fDSP->getNumInputs(); chan++) {
                inputs_slice[chan] = &(inputs[chan])[offset];
            }
            for (int chan = 0; chan < fDSP->getNumOutputs(); chan++) {
                outputs_slice[chan] = &(outputs[chan])[offset];
            }
            
            fDSP->compute(slice, inputs_slice, outputs_slice);
        }
  
    public:

        timed_dsp(dsp* dsp):decorator_dsp(dsp),fDateUsec(0),fFirstCallback(true), fOffsetUsec(0)
        {}
        virtual ~timed_dsp() 
        {}
        
        // Default method take a timestamp at 'compute' call time
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            compute(GetCurrentTimeInUsec(), count, inputs, outputs);
        }    
        
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            // Save the timestamp offset...
            if (fFirstCallback) {
                fOffsetUsec = GetCurrentTimeInUsec() - date_usec;
                fFirstCallback = false;
            }
            
            int control_change_count = 0;
            std::vector<value_it> control_vector_it;
            std::map<FAUSTFLOAT*, zvalues>::iterator it;
             
            // Time sort values associated with zones
            for (it = GUI::gTimedZoneMap.begin(); it != GUI::gTimedZoneMap.end(); it++) {
                zvalues values = (*it).second;
                // Keep number of all control values changes
                control_change_count += values->size();
                // Keep begin iterator
                control_vector_it.push_back(values->begin());
                // Sort values for the zone : necessary ?
                //std::sort(values->begin(), values->end(), compareDate);
            }
             
            // Do audio compilation "slice" by "slice"
            int slice, offset = 0;
            
            // Compute audio slices...
            while (control_change_count-- > 0) {
                
                double cur_zone_date = DBL_MAX;
                FAUSTFLOAT* cur_zone;
                value_it cur_found_it;
                int i = 0;
             
                // Find date of next slice to compute
                for (it = GUI::gTimedZoneMap.begin(); it != GUI::gTimedZoneMap.end(); it++, i++) {
                    // If value list is not empty, get the date and keep the minimal one
                    if (control_vector_it[i] != ((*it).second)->end()) {
                        double date = (*control_vector_it[i]).first;
                        if (date < cur_zone_date) {
                            cur_found_it = control_vector_it[i];
                            cur_zone = (*it).first;
                            cur_zone_date = date;
                        }
                    }
                }
                
                // Convert cur_zone_date in sample from begining of buffer
                cur_zone_date = ((cur_zone_date - fDateUsec) / 1000000.) * double(getSampleRate());
                
                // Update control
                *cur_zone = (*cur_found_it).second;
                
                //printf("sample_offset = %f value = %f\n", cur_zone_date, *cur_zone);
               
                // Move iterator of the values list to next zone
                cur_found_it++;
                 
                // Compute audio slice
                slice = int(cur_zone_date) - offset;
                computeSlice(offset, slice, inputs, outputs);
                offset += slice;
            } 
            
            // Compute last audio slice
            slice = count - offset;
            computeSlice(offset, slice, inputs, outputs);
            
            // Finally clear values for all zones
            for (it = GUI::gTimedZoneMap.begin(); it != GUI::gTimedZoneMap.end(); it++) {
                (*it).second->clear();
            }
            
            // Keep call date
            fDateUsec = date_usec + fOffsetUsec;
        }
        
};

#endif
