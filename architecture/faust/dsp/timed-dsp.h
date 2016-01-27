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

#ifndef __timed_dsp__
#define __timed_dsp__

#include "faust/dsp/dsp.h" 
#include "faust/gui/GUI.h" 
#include <vector>
#include <map>

struct TimedZoneUI : public UI
{
    std::vector<FAUSTFLOAT*> fZones;

    TimedZoneUI() {}
    virtual ~TimedZoneUI() {}
    
    // Only keep "timed" zones
    void insertZone(FAUSTFLOAT* zone) 
    {
        if (GUI::gTimedZoneMap.find(zone) != GUI::gTimedZoneMap.end()) {
            fZones.push_back(zone);
        }
    }
    
    virtual void openTabBox(const char* label) {}
    virtual void openHorizontalBox(const char* label) {}
    virtual void openVerticalBox(const char* label) {}
    virtual void closeBox() {}
    
    // -- active widgets

    virtual void addButton(const char* label, FAUSTFLOAT* zone) { insertZone(zone); }
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) { insertZone(zone); }
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 
    { insertZone(zone); }
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    { insertZone(zone); }
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    { insertZone(zone); }

    // -- passive widgets

    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    { insertZone(zone); }
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    { insertZone(zone); }

};

//----------------------------------------------------------------
//  Timed signal processor definition
//----------------------------------------------------------------

typedef std::vector<ts_value>::iterator value_it;

typedef std::pair<value_it, value_it> value_pair_it;

class timed_dsp : public decorator_dsp, public TimedZoneUI {

    protected:
    
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

        timed_dsp(dsp* dsp):decorator_dsp(dsp) 
        {
            // Only keep "timed" zones
            fDSP->buildUserInterface(this); 
        }
        virtual ~timed_dsp() 
        {}
     
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            int control_change_count = 0;
            std::vector<value_pair_it> control_vector_it;
            
            // Time sort values associated with zones
            for (int i = 0; i < fZones.size(); i++) {
                zvalues values = GUI::gTimedZoneMap[fZones[i]];
                // Keep number of all control values changes
                control_change_count += values->size();
                // Keep iterator
                control_vector_it.push_back(std::make_pair(values->begin(), values->end()));
                // Sort values for the zone
                std::sort(values->begin(), values->end(), compareDate);
            }
            
            printf("control_change_count = %d\n", control_change_count);
            
            // Do audio compilation "slice" by "slice"
            int slice, offset = 0;
            
            // Compute audio slices...
            while (control_change_count-- > 0) {
                
                int cur_zone_date = count;
                FAUSTFLOAT* cur_zone;
                value_pair_it cur_zone_pair_it;
             
                // Find time-stamps of next slice to compute
                for (int i = 0; i < fZones.size(); i++) {
                    // Keep minimal date
                    value_pair_it zone_pair_it = control_vector_it[i];
                    int date = (*(zone_pair_it.first)).first;
                    if (date < cur_zone_date) {
                        cur_zone_date = date;
                        cur_zone = fZones[i];
                        cur_zone_pair_it = zone_pair_it;
                    }
                }
                
                // Update control
                *cur_zone = (*(cur_zone_pair_it.first)).second;
               
                // Move iterator of the values list to next zone, check for end
                if (cur_zone_pair_it.first != cur_zone_pair_it.second) {
                    (cur_zone_pair_it.first)++;
                }
                 
                // Compute audio slice
                slice = cur_zone_date - offset;
                printf("offset = %d slice = %d\n", offset, slice);
                computeSlice(offset, slice, inputs, outputs);
                offset += slice;
            } 
            
            // Compute last audio slice
            slice = count - offset;
            computeSlice(offset, slice, inputs, outputs);
            
            // Finally clear values for all zones
            for (int i = 0; i < fZones.size(); i++) {
                GUI::gTimedZoneMap[fZones[i]]->clear();
            }
        }
        
};

#endif
