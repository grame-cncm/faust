/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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

#ifndef __midi__
#define __midi__

#include <vector>
#include <string>
#include <algorithm>
#include <jack/midiport.h>
#include "faust/gui/ring-buffer.h"

//----------------------------------------------------------------
//  MIDI processor definition
//----------------------------------------------------------------

class midi {
 
    public:

        midi() {}
        virtual ~midi() {}

        // Additional time-stamped API for MIDI input
        virtual void keyOn(double date, int channel, int pitch, int velocity)          {}
        virtual void keyOff(double date, int channel, int pitch, int velocity)         {}
        virtual void keyPress(double date, int channel, int pitch, int press)          {}
        virtual void chanPress(double date, int channel, int press)                    {}
        virtual void ctrlChange(double date, int channel, int ctrl, int value)         {}
        virtual void ctrlChange14bits(double date, int channel, int ctrl, int value)   {}
        virtual void pitchWheel(double date, int channel, int wheel)                   {}
        virtual void progChange(double date, int channel, int pgm)                     {}
        
        // MIDI sync
        virtual void start_sync(double date)  {}
        virtual void stop_sync(double date)   {}
        virtual void clock(double date)  {}
        
        // Standard MIDI API
        virtual void keyOn(int channel, int pitch, int velocity)        {}
        virtual void keyOff(int channel, int pitch, int velocity)       {}
        virtual void keyPress(int channel, int pitch, int press)        {}
        virtual void chanPress(int channel, int press)                  {}
        virtual void ctrlChange(int channel, int ctrl, int value)       {}
        virtual void ctrlChange14bits(int channel, int ctrl, int value) {}
        virtual void pitchWheel(int channel, int wheel)                 {}
        virtual void progChange(int channel, int pgm)                   {}
        
        enum MidiStatus {
	
            // channel voice messages
            MIDI_NOTE_OFF           = 0x80, 
            MIDI_NOTE_ON            = 0x90, 
            MIDI_CONTROL_CHANGE     = 0xB0,
            MIDI_PROGRAM_CHANGE     = 0xC0,
            MIDI_PITCH_BEND         = 0xE0,
            MIDI_AFTERTOUCH         = 0xD0,	// aka channel pressure
            MIDI_POLY_AFTERTOUCH    = 0xA0,	// aka key pressure
            MIDI_CLOCK              = 0xF8,
            MIDI_START              = 0xFA,
            MIDI_STOP               = 0xFC

        };
        
        enum MidiCtrl {
            
            ALL_NOTES_OFF = 123,
            ALL_SOUND_OFF = 120
        
        };
};

//----------------------------------------------------------------
//  Base class for MIDI API handling
//----------------------------------------------------------------

class midi_handler : public midi {

    protected:
    
        std::vector<midi*> fMidiInputs;
        std::string fName;
        
        void handleSync(double time, int type) 
        {
            if (type == MIDI_CLOCK) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->clock(time);
                }
            } else if (type == MIDI_START) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->start_sync(time);
                }
            } else if (type == MIDI_STOP) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->stop_sync(time);
                }
            }
        }
        
        void handleData1(double time, int type, int channel, int data1) 
        {
            if (type == MIDI_PROGRAM_CHANGE) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->progChange(time, channel, data1);
                }
            } else if (type == MIDI_AFTERTOUCH) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->chanPress(time, channel, data1);
                }
            }
        }
        
        void handleData2(double time, int type, int channel, int data1, int data2) 
        {
            if (type == MIDI_NOTE_OFF || ((type == MIDI_NOTE_ON) && (data2 == 0))) { 
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->keyOff(time, channel, data1, data2);
                }
            } else if (type == MIDI_NOTE_ON) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->keyOn(time, channel, data1, data2);
                }
            } else if (type == MIDI_CONTROL_CHANGE) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->ctrlChange(time, channel, data1, data2);
                }
            } else if (type == MIDI_PITCH_BEND) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->pitchWheel(time, channel, ((data2 * 128.0 + data1) - 8192) / 8192.0);
                }
            } else if (type == MIDI_POLY_AFTERTOUCH) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->keyPress(time, channel, data1, data2);
                }
            }
        }

    public:

        midi_handler(const std::string& name = "MIDIHandler"):fName(name) {}
        virtual ~midi_handler() {}
        
        virtual void addMidiIn(midi* midi_dsp) { fMidiInputs.push_back(midi_dsp); }
        virtual void removeMidiIn(midi* midi_dsp) 
        { 
            std::vector<midi*>::iterator it = std::find(fMidiInputs.begin(), fMidiInputs.end(), midi_dsp);
            if (it != fMidiInputs.end()) {
                fMidiInputs.erase(it); 
            }
        }
        
        virtual bool start_midi() { return false; }
        virtual void stop_midi() {}

};

class jack_midi_handler : public midi_handler {

    protected:
    
        ringbuffer_t* fOutBuffer;
        
        void writeMessage(unsigned char* buffer, size_t size)
        {
            if (fOutBuffer) {
                size_t res;
                // Write size of message
                if ((res = ringbuffer_write(fOutBuffer, (const char*)&size, sizeof(size_t))) != sizeof(size_t)) {
                    fprintf(stderr, "writeMessage size : error size = %lu res = %lu\n", size, res);
                }
                // Write message content
                if ((res = ringbuffer_write(fOutBuffer, (const char*)buffer, size)) != size) {
                    fprintf(stderr, "writeMessage message : error size = %lu res = %lu\n", size, res);
                }
            }
        }
        
        void processMidiInBuffer(void* port_buf_in) 
        {
            for (int i = 0; i < jack_midi_get_event_count(port_buf_in); ++i) {
                jack_midi_event_t event;
                if (jack_midi_event_get(&event, port_buf_in, i) == 0) {
                
                    size_t nBytes = event.size;
                    int type = (int)event.buffer[0] & 0xf0;
                    int channel = (int)event.buffer[0] & 0x0f;
                    double time = event.time; // Timestamp in frames
                    
                    // MIDI sync
                    if (nBytes == 1) {
                        handleSync(time, (int)event.buffer[0]);
                    } else if (nBytes == 2) {
                        handleData1(time, type, channel, (int)event.buffer[1]);
                    } else if (nBytes == 3) {
                        handleData2(time, type, channel, (int)event.buffer[1], (int)event.buffer[2]);
                    } 
                }
            }
        }
        
        void processMidiOutBuffer(void* port_buf_out_aux) 
        {
            // MIDI output
            unsigned char* port_buf_out = (unsigned char*)port_buf_out_aux; 
            jack_midi_clear_buffer(port_buf_out);
            size_t res, message_size;
            
            // Write each message one by one
            while (ringbuffer_read(fOutBuffer, (char*)&message_size, sizeof(message_size)) == sizeof(message_size)) {
                // Reserve MIDI event with the correct size
                jack_midi_data_t* data = jack_midi_event_reserve(port_buf_out, 0, message_size);
                if (data) {
                    // Write its content
                    if ((res = ringbuffer_read(fOutBuffer, (char*)data, message_size)) != message_size) {
                        fprintf(stderr, "processMidiOut incorrect message : res =  %lu\n", res);
                    }
                } else {
                    fprintf(stderr, "jack_midi_event_reserve error\n");
                }
            }
        }

    public:

        jack_midi_handler(const std::string& name = "JACKHandler")
            :midi_handler(name) 
        {
            fOutBuffer = ringbuffer_create(8192);
        }
        virtual ~jack_midi_handler() 
        {
            ringbuffer_free(fOutBuffer);
        }
        
        void keyOn(int channel, int pitch, int velocity) 
        {
            unsigned char buffer[3] 
                = { static_cast<unsigned char>(MIDI_NOTE_ON + channel), 
                    static_cast<unsigned char>(pitch), 
                    static_cast<unsigned char>(velocity) };
            writeMessage(buffer, 3);
        }
        
        void keyOff(int channel, int pitch, int velocity) 
        {
            unsigned char buffer[3] 
                = { static_cast<unsigned char>(MIDI_NOTE_OFF + channel), 
                    static_cast<unsigned char>(pitch), 
                    static_cast<unsigned char>(velocity) };
            writeMessage(buffer, 3);
        }
        
        void ctrlChange(int channel, int ctrl, int val) 
        {
            unsigned char buffer[3] 
                = { static_cast<unsigned char>(MIDI_CONTROL_CHANGE + channel), 
                    static_cast<unsigned char>(ctrl), 
                    static_cast<unsigned char>(val) };
            writeMessage(buffer, 3);
        }
        
        void chanPress(int channel, int press) 
        {
            unsigned char buffer[2] 
                = { static_cast<unsigned char>(MIDI_AFTERTOUCH + channel), 
                    static_cast<unsigned char>(press) };
            writeMessage(buffer, 2);
        }
        
        void progChange(int channel, int pgm) 
        {
            unsigned char buffer[2] 
                = { static_cast<unsigned char>(MIDI_PROGRAM_CHANGE + channel), 
                    static_cast<unsigned char>(pgm) };
            writeMessage(buffer, 2);
        }
          
        void keyPress(int channel, int pitch, int press) 
        {
            unsigned char buffer[3] 
                = { static_cast<unsigned char>(MIDI_POLY_AFTERTOUCH + channel), 
                    static_cast<unsigned char>(pitch), 
                    static_cast<unsigned char>(press) };
            writeMessage(buffer, 3);
        }
   
        void pitchWheel(int channel, int wheel) 
        {
            unsigned char buffer[3] 
                = { static_cast<unsigned char>(MIDI_PITCH_BEND + channel), 
                    static_cast<unsigned char>(wheel & 0x7F), 
                    static_cast<unsigned char>((wheel >> 7) & 0x7F) };
            writeMessage(buffer, 3);
        }
        
        void ctrlChange14bits(int channel, int ctrl, int value) {}
         
        void start_sync(double date) 
        {
            unsigned char buffer[1] = { MIDI_START };
            writeMessage(buffer, 1);
        }
       
        void stop_sync(double date) 
        {
            unsigned char buffer[1] = { MIDI_STOP };
            writeMessage(buffer, 1);
        }
        
        void clock(double date) 
        {
            unsigned char buffer[1] = { MIDI_CLOCK };
            writeMessage(buffer, 1);
        }

};

#endif // __midi__
