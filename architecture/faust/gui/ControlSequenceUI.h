/************************** BEGIN ControlSequenceUI.h *******************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 *************************************************************************/


#ifndef CONTROL_SEQUENCE_UI_H
#define CONTROL_SEQUENCE_UI_H

#include <vector>
#include <sstream>
#include <fstream>
#include <assert.h>

#include "faust/gui/MapUI.h"

struct TSMessage {
    uint64_t    fDateSample;
    std::string fPath;
    FAUSTFLOAT  fValue;
    
    TSMessage(uint64_t ds, const std::string& path, FAUSTFLOAT value)
    :fDateSample(ds), fPath(path), fValue(value)
    {}
};

/*
 Allows to process a sequence of timestamped messages.
 */
class ControlSequenceUI : public MapUI {
    
    protected:
    
        std::vector<TSMessage> fSequence;
        uint64_t               fCurSample;
        int                    fEvent;
    
        void processMessage(const TSMessage& message)
        {
            setParamValue(message.fPath, message.fValue);
        }
    
    public:
    
        ControlSequenceUI(const std::vector<TSMessage>& sequence):fSequence(sequence), fCurSample(0), fEvent(0) {}
        virtual ~ControlSequenceUI() {}
       
        void process(uint64_t start_sample, uint64_t end_sample)
        {
            if (fSequence.size() == 0) return;
            
            // Restart from begining if needed
            if (start_sample < fCurSample) {
                fCurSample = 0;
                fEvent = 0;
            }
            
            // Move until start of range
            while (fEvent < fSequence.size() && fSequence[fEvent].fDateSample < start_sample) {
                fEvent++;
            }
            
            // Process all messages in [start_sample, end_sample] range
            while (fEvent < fSequence.size() && fSequence[fEvent].fDateSample <= end_sample) {
                processMessage(fSequence[fEvent]);
                fEvent++;
            }
            
            // Keep last date
            fCurSample = fSequence[fEvent].fDateSample;
        }
    
        void display()
        {
            for (const auto& it : fSequence) {
                std::cout << "fDateSample " << it.fDateSample << " fPath " << it.fPath << " fValue " << it.fValue << std::endl;
            }
        }
    
        void getRange(uint64_t& start_sample, uint64_t& end_sample)
        {
            if (fSequence.size() > 0) {
                start_sample = fSequence[0].fDateSample;
                end_sample = fSequence[fSequence.size()-1].fDateSample;
            } else {
                start_sample = end_sample = 0;
            }
        }
        
};

/*
 Read a sequence of messages of type:
 
 e45377aa.206162f1 /karplus/gate f 1.000000
 e45377aa.360afa2e /karplus/gate f 0.000000
 e45377ab.0a40639d /karplus/params/freq f 267.850006
 e45377ab.1f47f993 /karplus/params/freq f 286.850006
 e45377ab.29c88616 /karplus/params/freq f 296.350006
 e45377ab.34370cdc /karplus/params/freq f 305.850006
 
 where a e451f81c.2be22e5d date is a timestamp in sec.frac format coded in hexadecimal.
 
 To be used with ControlSequenceUI class.
 */

struct OSCSequenceReader {
    
    static uint64_t readDate(const std::string& date, int sample_rate)
    {
        std::stringstream tokenizer(date);
        
        std::string sec, frac;
        getline(tokenizer, sec, '.');
        getline(tokenizer, frac, '.');
        
        std::istringstream sec_reader("0x" + sec);
        std::istringstream frac_reader("0x" + frac);
        uint32_t sec_t, frac_t;
        sec_reader >> std::hex >> sec_t;
        frac_reader >> std::hex >> frac_t;
        
        return uint64_t(sample_rate * (double(sec_t) + (double(frac_t)/std::pow(2,32))));
    }
    
    /**
     * Read the file containing timestamped messages.
     *
     * @param filename - the filename path
     * @param sample_rate - the sampling rate, needed to convert dates in seconds into dates in frames
     *
     * @return a vector of timestamped messages [path, value]
     */
    static std::vector<TSMessage> read(const std::string& filename, int sample_rate)
    {
        std::vector<TSMessage> res;
        std::ifstream in_file(filename);
        bool first_date = true;
        uint64_t first_date_sample;
        
        if (in_file.is_open()) {
            std::string line;
            while (getline(in_file, line)) {
                std::istringstream line_reader(line);
                std::string date, path, type;
                uint32_t sec, frac;
                
                line_reader >> date;
                line_reader >> path;
                line_reader >> type;
                
                // Read date, relative to first one
                uint64_t date_sample = readDate(date, sample_rate);
                if (first_date) {
                    first_date_sample = date_sample;
                    first_date = false;
                }
                date_sample -= first_date_sample;
                
                if (type == "i") {
                    int value_int;
                    line_reader >> value_int;
                    res.push_back(TSMessage(date_sample, path, FAUSTFLOAT(value_int)));
                } else if (type == "f") {
                    FAUSTFLOAT value_float;
                    line_reader >> value_float;
                    res.push_back(TSMessage(date_sample, path, value_float));
                }
            }
            in_file.close();
        }
        
        return res;
    }
};

#endif
/**************************  END ControlSequenceUI.h **************************/
