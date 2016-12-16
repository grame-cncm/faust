/************************************************************************
    FAUST Architecture File
    Copyright (C) 2016 GRAME, Centre National de Creation Musicale
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

#ifndef __jack_midi__
#define __jack_midi__

#include <iostream>
#include <cstdlib>
#include <jack/midiport.h>
#include "faust/midi/midi.h"
#include "faust/gui/ring-buffer.h"

class MapUI;

class jack_midi_handler : public midi_handler {

    protected:

        ringbuffer_t* fOutBuffer;

        void writeMessage(unsigned char* buffer, size_t size)
        {
            if (fOutBuffer) {
                size_t res;
                // Write size of message
                if ((res = ringbuffer_write(fOutBuffer, (const char*)&size, sizeof(size_t))) != sizeof(size_t)) {
                    std::cerr << "writeMessage size : error size = " << size << " res = " << res << std::endl;
                }
                // Write message content
                if ((res = ringbuffer_write(fOutBuffer, (const char*)buffer, size)) != size) {
                    std::cerr << "writeMessage size : error size = " << size << " res = " << res << std::endl;
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

        void processMidiOutBuffer(void* port_buf_out_aux, bool reset = false)
        {
            // MIDI output
            unsigned char* port_buf_out = (unsigned char*)port_buf_out_aux;
            if (reset) {
                jack_midi_reset_buffer(port_buf_out);
            } else {
                jack_midi_clear_buffer(port_buf_out);
            }
            size_t res, message_size;
         
            // Write each message one by one
            while (ringbuffer_read(fOutBuffer, (char*)&message_size, sizeof(message_size)) == sizeof(message_size)) {
                // Reserve MIDI event with the correct size
                jack_midi_data_t* data = jack_midi_event_reserve(port_buf_out, 0, message_size);
                if (data) {
                    // Write its content
                    if ((res = ringbuffer_read(fOutBuffer, (char*)data, message_size)) != message_size) {
                        std::cerr << "processMidiOut incorrect message : res = " << res << std::endl;
                    }
                } else {
                    std::cerr << "jack_midi_event_reserve error" << std::endl;
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

        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            unsigned char buffer[3]
                = { static_cast<unsigned char>(MIDI_NOTE_ON + channel),
                    static_cast<unsigned char>(pitch),
                    static_cast<unsigned char>(velocity) };
            writeMessage(buffer, 3);
            return 0;
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

#endif
