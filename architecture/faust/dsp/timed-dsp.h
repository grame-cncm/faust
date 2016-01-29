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
                //printf("fOffsetUsec %f\n", fOffsetUsec);
            }
            
            //printf("compute %lld\n", fDateUsec - lastDateUsec);
            
            int control_change_count = 0;
            std::vector<value_it> control_vector_it;
            std::map<FAUSTFLOAT*, zvalues>::iterator it1, it2;
             
            // Time sort values associated with zones
            for (it1 = GUI::gTimedZoneMap.begin(); it1 != GUI::gTimedZoneMap.end(); it1++) {
                zvalues values = (*it1).second;
                // Keep number of all control values changes
                control_change_count += values->size();
                // Keep begin iterator
                control_vector_it.push_back(values->begin());
                // Sort values for the zone : necessary
                //std::sort(values->begin(), values->end(), compareDate);
            }
            
            /*
            if (control_change_count > 0) {
                printf("control_change_count = %d\n", control_change_count);
                printf("control_vector_it size = %d\n", control_vector_it.size());
            }
            */
            
            // Do audio compilation "slice" by "slice"
            int slice, offset = 0;
            
            // Compute audio slices...
            while (control_change_count-- > 0) {
                
                double cur_zone_date = DBL_MAX;
                int i = 0;
                int found = 0;
             
                // Find date of next slice to compute
                for (it1 = GUI::gTimedZoneMap.begin(); it1 != GUI::gTimedZoneMap.end(); it1++, i++) {
                    // If value list is not empty, get the date and keep the minimal one
                    if (control_vector_it[i] != ((*it1).second)->end()) {
                        double date = (*control_vector_it[i]).first;
                        if (date < cur_zone_date) {
                            found = i;
                            it2 = it1;
                            cur_zone_date = date;
                        }
                    }
                }
                
                /*
                printf("cur_zone_date = %f lastDateUsec = %f  delta %f\n", 
                    cur_zone_date, lastDateUsec, cur_zone_date - lastDateUsec);
                */
                
                // Convert cur_zone_date in sample from begining of buffer
                cur_zone_date = ((cur_zone_date - fDateUsec) / 1000000.) * double(getSampleRate());
                
                // Update control
                *((*it2).first) = (*control_vector_it[found]).second;
                
                //printf("sample_offset = %f value = %f\n", cur_zone_date, (*control_vector_it[found]).second);
               
                // Move iterator of the values list to next zone, check for end
                if (control_vector_it[found] != ((*it2).second)->end()) {
                    (control_vector_it[found])++;
                }
                 
                // Compute audio slice
                slice = int(cur_zone_date) - offset;
                //printf("offset = %d slice = %d\n", offset, slice);
                computeSlice(offset, slice, inputs, outputs);
                offset += slice;
            } 
            
            // Compute last audio slice
            slice = count - offset;
            if (slice != count) {
                //printf("last: offset = %d slice = %d\n", offset, slice);
            }
            computeSlice(offset, slice, inputs, outputs);
            
            // Finally clear values for all zones
            for (it1 = GUI::gTimedZoneMap.begin(); it1 != GUI::gTimedZoneMap.end(); it1++) {
                (*it1).second->clear();
            }
            
            // Keep call date
            fDateUsec = date_usec + fOffsetUsec;
        }
        
};

#endif
