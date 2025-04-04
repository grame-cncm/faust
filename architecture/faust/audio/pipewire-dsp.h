/************************** BEGIN pipewire-dsp.h **************************
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
 **********************************************************************/

#ifndef __pipewire_dsp__
#define __pipewire_dsp__

#include <stdio.h>
#include <cstdlib>
#include <list>
#include <vector>
#include <memory>
#include <string.h>

#include <pipewire/pipewire.h>
#include <pipewire/filter.h>

#include <spa/param/audio/format-utils.h>
#include <spa/param/latency-utils.h>
#include <spa/utils/defs.h>
#include <spa/debug/pod.h>

#include "faust/midi/pipewire-midi.h"
#include "faust/audio/audio.h"
#include "faust/dsp/dsp.h"

#if defined(_WIN32) && !defined(__MINGW32__)
#define snprintf _snprintf_s
#endif


/******************************************************************************
 *******************************************************************************
 
 PIPEWIRE AUDIO INTERFACE
 
 *******************************************************************************
 *******************************************************************************/


struct audio_port {};

class pipewireaudio : public audio {

    protected:
        ::dsp* fDSP;
        pw_thread_loop *loop;
        pw_filter *filter;
        std::vector<audio_port*> fInputPorts;
        std::vector<audio_port*> fOutputPorts;
        bool fAutoConnect;

        pw_filter_events filter_events = {
            .version = PW_VERSION_FILTER_EVENTS,
            .process = _pw_process
        };

        spa_hook filter_listener;

        static void _pw_process(void* data, spa_io_position *position)
        {
            static_cast<pipewireaudio*>(data)->process(data, position);
        }

        virtual int process(void *d, spa_io_position *position)
        {
            AVOIDDENORMALS;
            int nframes = position->clock.duration;

            float** fInChannel = (float**)alloca(fInputPorts.size() * sizeof(float*));
            for (size_t i = 0; i < fInputPorts.size(); i++) {
                void *buf = pw_filter_get_dsp_buffer(fInputPorts[i], nframes);
                if (!buf) {
                    buf = alloca(nframes * sizeof(float));
                    memset(buf, 0, nframes * sizeof(float));
                }
                fInChannel[i] = (float*)buf;
            }
            
            float** fOutChannel = (float**)alloca(fOutputPorts.size() * sizeof(float*));
            for (size_t i = 0; i < fOutputPorts.size(); i++) {
                void *buf = pw_filter_get_dsp_buffer(fOutputPorts[i], nframes);
                if (!buf) {
                    buf = alloca(nframes * sizeof(float));
                }
                fOutChannel[i] = (float*) buf;
            }

            fDSP->compute(nframes, reinterpret_cast<FAUSTFLOAT**>(fInChannel), reinterpret_cast<FAUSTFLOAT**>(fOutChannel));
            
            runControlCallbacks();
            return 0;
        }

        void shutdown(const char* message)
        {
            loop = nullptr;
            
            if (fShutdown) {
                fShutdown(message, fShutdownArg);
            } else {
                exit(1); // By default
            }
        }
        
    public:

        pipewireaudio(bool auto_connect = true)
        : fDSP(nullptr), loop(nullptr), fAutoConnect(auto_connect)
        {}
        
        virtual ~pipewireaudio()
        {
            if (filter) {
                pw_core *core = pw_filter_get_core(filter);
                pw_context *context = pw_core_get_context(core);

                stop();
                pw_filter_destroy(filter);
                pw_core_disconnect(core);
                pw_context_destroy(context);
                pw_thread_loop_destroy(loop);
                pw_deinit();
            }
        }
        
        virtual bool init(const char* name, ::dsp* dsp)
        {
            if (initAux(name)) {
                if (dsp) { setDsp(dsp); }
                return true;
            } else {
                return false;
            }
        }

        bool initAux(const char* name)
        {
            pw_init(nullptr, nullptr);

            loop = pw_thread_loop_new(nullptr, nullptr);

            pw_context *context = pw_context_new(pw_thread_loop_get_loop(loop), nullptr, 0);
            pw_core *core = pw_context_connect(context, nullptr, 0);

            filter = pw_filter_new(core, name, pw_properties_new(
                PW_KEY_MEDIA_TYPE, "Audio",
                PW_KEY_MEDIA_CATEGORY, "Filter",
                PW_KEY_MEDIA_ROLE, "DSP",
                nullptr
            ));

            pw_filter_add_listener(filter, &filter_listener, &filter_events, this);
            return true;
        }

        virtual bool start()
        {
            uint8_t buffer[1024];
            struct spa_pod_builder b = SPA_POD_BUILDER_INIT(buffer, sizeof(buffer));

            if (pw_filter_connect(filter,
                        PW_FILTER_FLAG_RT_PROCESS,
                        nullptr, 0) < 0) {
                fprintf(stderr, "can't connect the filter\n");
                return false;
            }
            pw_thread_loop_start(loop);
            return true;
        }
    
        virtual void stop()
        {
            pw_thread_loop_lock(loop);
            pw_filter_disconnect(filter);
            pw_thread_loop_unlock(loop);
            pw_thread_loop_stop(loop);
        }

        virtual int getBufferSize() {
            const pw_properties *properties = pw_core_get_properties(pw_filter_get_core(filter));
            const char *bufsize = pw_properties_get(properties, "default.clock.quantum");
            return atoi(bufsize);
        }
    
        virtual int getSampleRate() {
            const pw_properties *properties = pw_core_get_properties(pw_filter_get_core(filter));
            const char *bufsize = pw_properties_get(properties, "default.clock.rate");
            return atoi(bufsize);
        }

        virtual int getNumInputs()
        {
            return fInputPorts.size();
        }
        
        virtual int getNumOutputs()
        {
            return fOutputPorts.size();
        }
        
        virtual void setDsp(::dsp* dsp)
        {
            fDSP = dsp;

            char port_name[256];
            for (int i = 0; i < fDSP->getNumInputs(); i++) {
                snprintf(port_name, 256, "in_%d", i);
                void *in = pw_filter_add_port(filter,
                    PW_DIRECTION_INPUT,
                    PW_FILTER_PORT_FLAG_MAP_BUFFERS,
                    sizeof(audio_port),
                    pw_properties_new(
                        PW_KEY_FORMAT_DSP, "32 bit float mono audio",
                        PW_KEY_PORT_NAME, port_name,
                        nullptr),
                    nullptr, 0);
                fInputPorts.push_back(static_cast<audio_port*>(in));
            }

            for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                snprintf(port_name, 256, "out_%d", i);
                void *out = pw_filter_add_port(filter,
                    PW_DIRECTION_OUTPUT,
                    PW_FILTER_PORT_FLAG_MAP_BUFFERS,
                    sizeof(audio_port),
                    pw_properties_new(
                        PW_KEY_FORMAT_DSP, "32 bit float mono audio",
                        PW_KEY_PORT_NAME, port_name,
                        nullptr),
                    nullptr, 0);
                fOutputPorts.push_back(static_cast<audio_port*>(out));
            }

            fDSP->init(getSampleRate());
        }
};

class pipewireaudio_midi : public pipewireaudio, public pipewire_midi {

    protected:

        bool fPolling;
    
        virtual int process(void *d, spa_io_position *position) override
        {
            int nframes = position->clock.duration;
            // MIDI in
            if (!fPolling) processMidiIn(nframes);
            
            // Audio
            pipewireaudio::process(d, position);
            
            // MIDI out
            processMidiOut(nframes);
            
            runControlCallbacks();
            return 0;
        }
        
    public:
        
        pipewireaudio_midi(bool auto_connect = true, bool is_polling = false)
        :pipewireaudio(auto_connect), pipewire_midi("pipewire_midi"), fPolling(is_polling)
        {}
        
        virtual ~pipewireaudio_midi()
        {}
        
        virtual bool init(const char* name, ::dsp* dsp)
        {
            if (pipewireaudio::initAux(name)) {
                if (dsp) { setDsp(dsp); }
                return initPorts(filter);
            } else {
                return false;
            }
        }
        
        virtual bool start()
        {
            return pipewireaudio::start();
        }
        
        virtual void stop()
        {
            pipewireaudio::stop();
        }
    
};

#endif
/**************************  END  pipewire-dsp.h **************************/
