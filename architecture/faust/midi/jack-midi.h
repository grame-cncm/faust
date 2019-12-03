/************************** BEGIN jack-midi.h **************************/
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

#ifndef __jack_midi__
#define __jack_midi__

#include <iostream>
#include <cstdlib>

#include <jack/jack.h>
#include <jack/midiport.h>

#include "faust/midi/midi.h"
#include "faust/gui/ring-buffer.h"

class MapUI;

//-----------------------------------------------
// MIDI input/output handling using JACK library
//-----------------------------------------------

class jack_midi_handler : public midi_handler {
        
    protected:

        ringbuffer_t* fOutBuffer;
        jack_port_t* fInputMidiPort;    // JACK input MIDI port
        jack_port_t* fOutputMidiPort;   // JACK output MIDI port

        bool initPorts(jack_client_t* client)
        {
            fInputMidiPort = jack_port_register(client, "midi_in_1", JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);
            fOutputMidiPort = jack_port_register(client, "midi_out_1", JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput, 0);
            return fInputMidiPort && fOutputMidiPort;
        }
    
        void writeMessage(double date, unsigned char* buffer, size_t size)
        {
            size_t res;
            DatedMessage dated_message(date, buffer, size);
            if ((res = ringbuffer_write(fOutBuffer, (const char*)&dated_message, sizeof(DatedMessage))) != sizeof(DatedMessage)) {
                std::cerr << "ringbuffer_write error DatedMessage" << std::endl;
            }
        }

        void processMidiInBuffer(void* port_buf_in)
        {
            for (size_t i = 0; i < jack_midi_get_event_count(port_buf_in); ++i) {
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
                    } else {
                        std::vector<unsigned char> message(event.buffer, event.buffer + event.size);
                        handleMessage(time, type, message);
                    }
                }
            }
        }
    
        virtual void processMidiIn(jack_nframes_t nframes)
        {
            // MIDI input
            processMidiInBuffer(jack_port_get_buffer(fInputMidiPort, nframes));
        }

        void processMidiOutBuffer(void* port_buf_out_aux, bool reset = false)
        {
            // MIDI output
            unsigned char* port_buf_out = (unsigned char*)port_buf_out_aux;
            if (reset) {
                /*
                // 08/03/2019: "jack_midi_reset_buffer" is not official in JACK, so we deactivate the code.
                jack_midi_reset_buffer(port_buf_out);
                */
            } else {
                jack_midi_clear_buffer(port_buf_out);
            }
           
            // Write each message one by one
            DatedMessage dated_message;
            while (ringbuffer_read(fOutBuffer, (char*)&dated_message, sizeof(DatedMessage)) == sizeof(DatedMessage)) {
                jack_midi_data_t* data = jack_midi_event_reserve(port_buf_out, dated_message.fDate, dated_message.fSize);
                if (data) {
                    memcpy(data, dated_message.fBuffer, dated_message.fSize);
                } else {
                    std::cerr << "jack_midi_event_reserve error" << std::endl;
                }
            }
        }
    
        virtual void processMidiOut(jack_nframes_t nframes)
        {
            // MIDI output
            processMidiOutBuffer(jack_port_get_buffer(fOutputMidiPort, nframes));
        }

    public:

        jack_midi_handler(const std::string& name = "JACKHandler")
            :midi_handler(name), fInputMidiPort(nullptr), fOutputMidiPort(nullptr)
        {
            fOutBuffer = ringbuffer_create(8192);
        }
        virtual ~jack_midi_handler()
        {
            ringbuffer_free(fOutBuffer);
        }
    
        // To be used in polling mode
        int recvMessages(std::vector<MIDIMessage>* messages)
        {
            int count = 0;
            jack_nframes_t first_time_stamp = 0;
            void* port_buf_in = jack_port_get_buffer(fInputMidiPort, 1024);
            for (size_t i = 0; i < jack_midi_get_event_count(port_buf_in); ++i) {
                jack_midi_event_t event;
                if (jack_midi_event_get(&event, port_buf_in, i) == 0) {
                    // Small messages
                    if (event.size <= 3) {
                        if (count == 0) first_time_stamp = event.time;
                        MIDIMessage& mes = messages->at(count++);
                        mes.frameIndex = (uint32_t)(event.time - first_time_stamp);
                        mes.byte0 = event.buffer[0];
                        mes.byte1 = event.buffer[1];
                        mes.byte2 = event.buffer[2];
                    } else {
                        std::cerr << "recvMessages : long messages (" << event.size << ") are not supported yet\n";
                    }
                }
            }
            return count;
        }
    
        void sendMessages(std::vector<MIDIMessage>* messages, int count)
        {
            for (int i = 0; i < count; ++i) {
                MIDIMessage message = (*messages)[i];
                unsigned char buffer[3]
                    = { static_cast<unsigned char>(message.byte0),
                        static_cast<unsigned char>(message.byte1),
                        static_cast<unsigned char>(message.byte2) };
                writeMessage(0, buffer, 3);
            }
        }
    
        // MIDI output API
        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            unsigned char buffer[3]
                = { static_cast<unsigned char>(MIDI_NOTE_ON + channel),
                    static_cast<unsigned char>(pitch),
                    static_cast<unsigned char>(velocity) };
            writeMessage(0, buffer, 3);
            return 0;
        }

        void keyOff(int channel, int pitch, int velocity)
        {
            unsigned char buffer[3]
                = { static_cast<unsigned char>(MIDI_NOTE_OFF + channel),
                    static_cast<unsigned char>(pitch),
                    static_cast<unsigned char>(velocity) };
            writeMessage(0, buffer, 3);
        }

        void ctrlChange(int channel, int ctrl, int val)
        {
            unsigned char buffer[3]
                = { static_cast<unsigned char>(MIDI_CONTROL_CHANGE + channel),
                    static_cast<unsigned char>(ctrl),
                    static_cast<unsigned char>(val) };
            writeMessage(0, buffer, 3);
        }

        void chanPress(int channel, int press)
        {
            unsigned char buffer[2]
                = { static_cast<unsigned char>(MIDI_AFTERTOUCH + channel),
                    static_cast<unsigned char>(press) };
            writeMessage(0, buffer, 2);
        }

        void progChange(int channel, int pgm)
        {
            unsigned char buffer[2]
                = { static_cast<unsigned char>(MIDI_PROGRAM_CHANGE + channel),
                    static_cast<unsigned char>(pgm) };
            writeMessage(0, buffer, 2);
        }

        void keyPress(int channel, int pitch, int press)
        {
            unsigned char buffer[3]
                = { static_cast<unsigned char>(MIDI_POLY_AFTERTOUCH + channel),
                    static_cast<unsigned char>(pitch),
                    static_cast<unsigned char>(press) };
            writeMessage(0, buffer, 3);
        }

        void pitchWheel(int channel, int wheel)
        {
            unsigned char buffer[3]
                = { static_cast<unsigned char>(MIDI_PITCH_BEND + channel),
                    static_cast<unsigned char>(wheel & 0x7F),
                    static_cast<unsigned char>((wheel >> 7) & 0x7F) };
            writeMessage(0, buffer, 3);
        }

        void ctrlChange14bits(int channel, int ctrl, int value) {}

        void startSync(double date)
        {
            unsigned char buffer[1] = { MIDI_START };
            writeMessage(date, buffer, 1);
        }
  
        void stopSync(double date)
        {
            unsigned char buffer[1] = { MIDI_STOP };
            writeMessage(date, buffer, 1);
        }

        void clock(double date)
        {
            unsigned char buffer[1] = { MIDI_CLOCK };
            writeMessage(date, buffer, 1);
        }
    
        void sysEx(double date, std::vector<unsigned char>& message)
        {
            writeMessage(date, message.data(), (int)message.size());
        }

};

#endif
/**************************  END  jack-midi.h **************************/
