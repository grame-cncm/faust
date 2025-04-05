/************************** BEGIN pipewire-midi.h ****************************
 FAUST Architecture File
 Copyright (C) 2025 GRAME, Centre National de Creation Musicale
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
***************************************************************************/

#ifndef __pipewire_midi__
#define __pipewire_midi__

#include <iostream>
#include <cstdlib>

#include <pipewire/pipewire.h>
#include <spa/pod/builder.h>
#include <spa/control/control.h>
#include <spa/debug/pod.h>

#include "faust/midi/midi.h"
#include "faust/gui/ring-buffer.h"

class FAUST_API MapUI;

/**
 *  MIDI input/output handling using Pipewire library: https://pipewire.org
 */
struct midi_port{};

class pipewire_midi: public midi_handler {

    protected:

        ringbuffer_t* fOutBuffer;
        midi_port* fInputMidiPort;    // Pipewire input MIDI port
        midi_port* fOutputMidiPort;   // Pipewire output MIDI port
        const int fMidiBufferSize = 4096;

        bool initPorts(pw_filter* filter)
        {
            uint8_t pod_buffer[1024];
            spa_pod_builder builder;
            const spa_pod *params;

            spa_pod_builder_init(&builder, pod_buffer, sizeof(pod_buffer));

            params = (spa_pod*) spa_pod_builder_add_object(&builder,
                    SPA_TYPE_OBJECT_ParamBuffers, SPA_PARAM_Buffers,
                    SPA_PARAM_BUFFERS_buffers, SPA_POD_CHOICE_RANGE_Int(1, 1, 32),
                    SPA_PARAM_BUFFERS_blocks,  SPA_POD_Int(1),
                    // buffer size: request default fMidiBufferSize bytes, min fMidiBufferSize, no maximum
                    SPA_PARAM_BUFFERS_size,    SPA_POD_CHOICE_RANGE_Int(fMidiBufferSize, fMidiBufferSize, INT32_MAX),
                    SPA_PARAM_BUFFERS_stride,  SPA_POD_Int(1));

            fInputMidiPort = static_cast<midi_port*>(pw_filter_add_port(filter,
                    PW_DIRECTION_INPUT,
                    PW_FILTER_PORT_FLAG_MAP_BUFFERS,
                    0,
                    pw_properties_new(
                        PW_KEY_FORMAT_DSP, "8 bit raw midi",
                        PW_KEY_PORT_NAME, "midi_in",
                        nullptr),
                    &params, 1));

            fOutputMidiPort = static_cast<midi_port*>(pw_filter_add_port(filter,
                PW_DIRECTION_OUTPUT,
                PW_FILTER_PORT_FLAG_MAP_BUFFERS,
                0,
                pw_properties_new(
                    PW_KEY_FORMAT_DSP, "8 bit raw midi",
                    PW_KEY_PORT_NAME, "midi_out",
                    nullptr),
                &params, 1));

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

        void processMidiInBuffer(void* buffer)
        {
            spa_pod_sequence *seq;
            spa_pod_control *c;
            spa_pod *pod = (spa_pod*)buffer;

            if (!spa_pod_is_sequence(pod)) {
                printf("midi-in pod is not a sequence pod\n");
                return;
            }

            seq = (spa_pod_sequence *)pod;

            SPA_POD_SEQUENCE_FOREACH(seq, c) {
                const void *data;
                uint32_t size;

                spa_pod_get_bytes(&c->value, &data, &size);

                int type = ((uint8_t *)data)[0] & 0xf0;
                int channel = ((uint8_t *)data)[0] & 0x0f;
                double time = c->offset;

                if (size == 1) {
                    handleSync(time, ((uint8_t *)data)[0]);
                } else if (size == 2) {
                    handleData1(time, type, channel, ((uint8_t *)data)[1]);
                } else if (size == 3) {
                    handleData2(time, type, channel, ((uint8_t *)data)[1], ((uint8_t *)data)[2]);
                } else {
                    std::vector<unsigned char> message((uint8_t *)data, (uint8_t *)data + size);
                    handleMessage(time, type, message);
                }
            }
        }
    
        virtual void processMidiIn(int nframes)
        {
            void *buf = pw_filter_get_dsp_buffer(fInputMidiPort, nframes);
            if (buf) processMidiInBuffer(buf);
        }

        void processMidiOutBuffer(pw_buffer *buf) {
            spa_pod_builder builder;
            spa_pod_frame frame;
            spa_data &d = buf->buffer->datas[0]; 

            d.chunk->offset = 0;
            d.chunk->size = 0;
            d.chunk->stride = 1;
            d.chunk->flags = 0;

            // to write spa_pods on output buffer we init spa_pod_builder on buffer data
            spa_pod_builder_init(&builder, d.data, fMidiBufferSize);
            spa_pod_builder_push_sequence(&builder, &frame, 0);

            DatedMessage dated_message;
            while (ringbuffer_read(fOutBuffer, (char*)&dated_message, sizeof(DatedMessage)) == sizeof(DatedMessage)) {
                // SPA_CONTROL_Midi is deprecated, use SPA_CONTROL_UMP when distros switch to newer versions of pipewire
                spa_pod_builder_control(&builder, 0, SPA_CONTROL_Midi);
                spa_pod_builder_bytes(&builder, dated_message.fBuffer, dated_message.fSize);
            }
            spa_pod_builder_pop(&builder, &frame);
            d.chunk->size = builder.state.offset;
        }
    
        virtual void processMidiOut(int nframes)
        {
            // couldn't get midi out working with pw_filter_get_dsp_buffer like in processMidiIn
            pw_buffer *buf = pw_filter_dequeue_buffer(fOutputMidiPort);
            if (!buf) return;
            processMidiOutBuffer(buf);
            pw_filter_queue_buffer(fOutputMidiPort, buf);
        }

    public:

        pipewire_midi(const std::string& name = "pipewireHandler")
            :midi_handler(name), fInputMidiPort(nullptr), fOutputMidiPort(nullptr)
        {
            fOutBuffer = ringbuffer_create(8192);
        }
        virtual ~pipewire_midi()
        {
            ringbuffer_free(fOutBuffer);
        }
    
        // To be used in polling mode

        int recvMessages(std::vector<MIDIMessage>* messages)
        {
            int count = 0;
            int first_time_stamp = 0;
            void* port_buf_in = pw_filter_get_dsp_buffer(fInputMidiPort, 1024);

            spa_pod_sequence *seq;
            spa_pod_control *c;
            spa_pod *pod = (spa_pod*)port_buf_in;

            if (!spa_pod_is_sequence(pod)) {
                printf("midi-in pod is not a sequence pod\n");
                return 0;
            }

            seq = (spa_pod_sequence *)pod;

            SPA_POD_SEQUENCE_FOREACH(seq, c) {
                const void *data;
                uint32_t size;

                spa_pod_get_bytes(&c->value, &data, &size);

                int type = ((uint8_t *)data)[0] & 0xf0;
                int channel = ((uint8_t *)data)[0] & 0x0f;
                double time = c->offset;

                if (size <= 3) {
                    if (count == 0) first_time_stamp = time;
                    MIDIMessage& mes = messages->at(count++);
                    mes.frameIndex = (uint32_t)(time - first_time_stamp);
                    mes.byte0 = ((uint8_t *)data)[0];
                    mes.byte1 = ((uint8_t *)data)[1];
                    mes.byte2 = ((uint8_t *)data)[2];
                } else {
                    std::cerr << "recvMessages : long messages (" << size << ") are not supported yet\n";
                }
            }
            return count;
        }

        void sendMessages(std::vector<MIDIMessage>* messages, int count)
        {
            for (int i = 0; i < count; ++i) {
                MIDIMessage message = (*messages)[i];
                unsigned char buffer[3] = { ucast(message.byte0), ucast(message.byte1), ucast(message.byte2) };
                writeMessage(0, buffer, 3);
            }
        }
    
        // MIDI output API
        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            unsigned char buffer[3] = { ucast(MIDI_NOTE_ON + channel), ucast(pitch), ucast(velocity) };
            writeMessage(0, buffer, 3);
            return 0;
        }

        void keyOff(int channel, int pitch, int velocity)
        {
            unsigned char buffer[3] = { ucast(MIDI_NOTE_OFF + channel), ucast(pitch), ucast(velocity) };
            writeMessage(0, buffer, 3);
        }

        void ctrlChange(int channel, int ctrl, int val)
        {
            unsigned char buffer[3] = { ucast(MIDI_CONTROL_CHANGE + channel), ucast(ctrl), ucast(val) };
            writeMessage(0, buffer, 3);
        }

        void chanPress(int channel, int press)
        {
            unsigned char buffer[2] = { ucast(MIDI_AFTERTOUCH + channel), ucast(press) };
            writeMessage(0, buffer, 2);
        }

        void progChange(int channel, int pgm)
        {
            unsigned char buffer[2] = { ucast(MIDI_PROGRAM_CHANGE + channel), ucast(pgm) };
            writeMessage(0, buffer, 2);
        }

        void keyPress(int channel, int pitch, int press)
        {
            unsigned char buffer[3] = { ucast(MIDI_POLY_AFTERTOUCH + channel), ucast(pitch), ucast(press) };
            writeMessage(0, buffer, 3);
        }

        void pitchWheel(int channel, int wheel)
        {
            unsigned char buffer[3] = { ucast(MIDI_PITCH_BEND + channel), ucast(wheel & 0x7F), ucast((wheel >> 7) & 0x7F) };
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
/**************************  END  pipewire-midi.h **************************/
