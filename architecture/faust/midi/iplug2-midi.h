/************************** BEGIN iplug2-midi.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2020 GRAME, Centre National de Creation Musicale
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

#ifndef __iplug2_midi__
#define __iplug2_midi__
 
#include "faust/midi/midi.h"
#include "IPlugMidi.h"

class MapUI;

BEGIN_IPLUG_NAMESPACE

//-------------------------------------------------
// MIDI input/output handling using iPlug2 library
//-------------------------------------------------

struct iplug2_midi_handler : public midi_handler {
    
    IMidiMsg fMessage;
    
    void decodeMessage(const IMidiMsg& msg)
    {
        int status = msg.StatusMsg();
        double time = 0.;
        
        switch (status) {
            case IMidiMsg::kNoteOn:
                handleKeyOn(time, msg.Channel(), msg.mData1, msg.mData2);
                break;
            case IMidiMsg::kNoteOff:
                handleKeyOff(time, msg.Channel(), msg.mData1, msg.mData2);
                break;
            case IMidiMsg::kPolyAftertouch:
                handlePolyAfterTouch(time, msg.Channel(), msg.mData1, msg.mData2);
                break;
            case IMidiMsg::kControlChange:
                handleCtrlChange(time, msg.Channel(), msg.mData1, msg.mData2);
                break;
            case IMidiMsg::kProgramChange:
                handleProgChange(time, msg.Channel(), msg.mData1);
                break;
            case IMidiMsg::kChannelAftertouch:
                handleAfterTouch(time, msg.Channel(), msg.mData1);
                break;
            case IMidiMsg::kPitchWheel:
                handlePitchWheel(time, msg.Channel(), msg.mData1, msg.mData2);
                break;
            default:
                // Not handle for now
                break;
        }
    }
    
    iplug2_midi_handler():midi_handler("iPlug2")
    {}

    virtual ~iplug2_midi_handler() {}

    // MIDI output API
    MapUI* keyOn(int channel, int pitch, int velocity)
    {
        //fMessage.MakeNoteOnMsg(pitch, velocity, 0, channel);
        return nullptr;
    }
    
    void keyOff(int channel, int pitch, int velocity)
    {
        //fMessage.MakeNoteOffMsg(pitch, 0, channel);
    }
    
    void ctrlChange(int channel, int ctrl, int val)
    {
        //fMessage.MakeControlChangeMsg(ctrl, val, 0, channel);
    }
    
    void chanPress(int channel, int press)
    {
        //fMessage.MakeChannelATMsg(press, 0, channel);
    }
    
    void progChange(int channel, int pgm)
    {
        //fMessage.MakeProgramChange(pgm, 0, channel);
    }
    
    void keyPress(int channel, int pitch, int press)
    {
        //fMessage.MakePolyATMsg(pitch, press, 0, channel);
    }
    
    void pitchWheel(int channel, int wheel)
    {
        //fMessage.MakePitchWheelMsg(wheel, 0, channel);
    }
    
    void ctrlChange14bits(int channel, int ctrl, int value)
    {
        // TODO
    }
    
    void startSync(double date)
    {
        // TODO
    }
    
    void stopSync(double date)
    {
        // TODO
    }
    
    void clock(double date)
    {
        // TODO
    }

    void sysEx(double date, std::vector<unsigned char>& message)
    {
        // TODO
    }

};

END_IPLUG_NAMESPACE

#endif // __iplug2_midi__

/**************************  END  iplug2-midi.h **************************/
