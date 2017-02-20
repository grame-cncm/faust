/************************************************************************

	IMPORTANT NOTE : this file contains two clearly delimited sections :
	the ARCHITECTURE section (in two parts) and the USER section. Each section
	is governed by its own copyright and license. Please check individually
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

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

#ifndef __netjack_dsp__
#define __netjack_dsp__

#include <stdio.h>
#include "faust/audio/audio.h"
#include "faust/dsp/dsp.h"
#include "faust/gui/ControlUI.h"
#include "faust/midi/jack-midi.h"

#include <jack/net.h>
#include <string>
#include <assert.h>

class netjackaudio : public audio
{

    protected:
    
        dsp* fDSP;
        jack_net_slave_t* fNet;
        int fNetFormat;
        std::string fMasterIP;
        int fMasterPort;
        int fMTU;
        int fLatency;
        jack_master_t fResult;

    #ifdef RESTART_CB_API
        static int net_restart(void* arg) 
        {
            printf("Network failure, restart...\n");
            return static_cast<netjackaudio*>(arg)->restart_cb();
        }
    #else 
        static void net_shutdown(void* arg) 
        {
            printf("Network failure, shutdown...\n");
            static_cast<netjackaudio*>(arg)->shutdown_cb();
        }
    #endif
    
        static int net_sample_rate(jack_nframes_t nframes, void* arg) 
        {
            return static_cast<netjackaudio*>(arg)->set_sample_rate(nframes);
        }
        
        static int net_buffer_size(jack_nframes_t nframes, void* arg) 
        {
            return static_cast<netjackaudio*>(arg)->set_buffer_size(nframes);
        }
        
        static void net_error(int error_code, void* arg)
        {
            return static_cast<netjackaudio*>(arg)->error_cb(error_code);
        }
        
        static int net_process(jack_nframes_t buffer_size,
                               int,
                               float** audio_inputs,
                               int,
                               void** midi_inputs,
                               int,
                               float** audio_outputs,
                               int,
                               void** midi_outputs,
                               void* arg) 
        {
            static_cast<netjackaudio*>(arg)->process(buffer_size, audio_inputs, audio_outputs, midi_inputs, midi_outputs);
            return 0;
        }

        bool init_aux(const char* name, dsp* DSP, int audio_inputs, int audio_outputs, int midi_inputs, int midi_outputs) 
        {
            if (init_aux(name, audio_inputs, audio_outputs, midi_inputs, midi_outputs)) {
                set_dsp(DSP);
                return true;
            } else {
                return false;
            }
        }
    
        bool init_aux(const char* name, int audio_inputs, int audio_outputs, int midi_inputs, int midi_outputs) 
        {
            jack_slave_t request = {
                audio_inputs,
                audio_outputs,
                midi_inputs, 
                midi_outputs,
                fMTU,
                2,
                (fNetFormat > 0) ? JackOpusEncoder : ((fNetFormat == -1) ? JackFloatEncoder : JackIntEncoder),
                (fNetFormat > 0) ? fNetFormat : 0,
                fLatency
            };
      
            if ((fNet = jack_net_slave_open(fMasterIP.c_str(), fMasterPort, name, &request, &fResult)) == 0) {
                printf("JACK remote server not running ?\n");
                return false;
            }

            jack_set_net_slave_process_callback(fNet, net_process, this);
        #ifdef RESTART_CB_API
            jack_set_net_slave_restart_callback(fNet, net_restart, this);
        #else
            jack_set_net_slave_shutdown_callback(fNet, net_shutdown, this);
        #endif
            jack_set_net_slave_sample_rate_callback(fNet, net_sample_rate, this);
            
            jack_set_net_slave_buffer_size_callback(fNet, net_buffer_size, this);
            
            jack_set_net_slave_error_callback(fNet, net_error, this);

            return true;
        }
    
        // Possibly to be redefined by subclasses
        
        virtual int restart_cb()
        {
            return 0;
        }
       
        virtual void shutdown_cb()
        {}
        
        virtual void error_cb(int error_code)
        {}
       
        virtual int set_sample_rate(jack_nframes_t nframes)
        {
            return 0;
        }
        
        virtual int set_buffer_size(jack_nframes_t nframes)
        {
            return 0;
        }

        virtual void process(int count, float** audio_inputs, float** audio_outputs, void** midi_inputs, void** midi_outputs)
        {
             AVOIDDENORMALS;
             fDSP->compute(count, audio_inputs, audio_outputs);
        }

    public:

        netjackaudio(int net_format, const std::string& master_ip, int master_port, int mtu, int latency = 2)
            : fDSP(0), fNet(0), fNetFormat(net_format), fMasterIP(master_ip), fMasterPort(master_port), fMTU(mtu), fLatency(latency)
        {}
        
        virtual ~netjackaudio() 
        {
            if (fNet) {
                stop();
                jack_net_slave_close(fNet);
            }
        }

        virtual bool init(const char* name, dsp* DSP) 
        {
            return init_aux(name, DSP, DSP->getNumInputs(), DSP->getNumOutputs(), 0, 0);
        }

        virtual bool start() 
        {
            if (jack_net_slave_activate(fNet)) {
                printf("cannot activate net");
                return false;
            }
            return true;
        }

        virtual void stop() 
        {
            if (fNet) {
                jack_net_slave_deactivate(fNet);
            }
        }
        
        void set_dsp(dsp* DSP) 
        {
            fDSP = DSP;
            fDSP->init(fResult.sample_rate);
        }
        
        virtual int get_buffer_size() { return fResult.buffer_size; }
        virtual int get_sample_rate() { return fResult.sample_rate; }

};

/*
A special NetJack client that uses one more audio input/output to transmit control values.
*/

class netjackaudio_control : public netjackaudio, public ControlUI {  
        
    protected:
        
        virtual void process(int count, float** audio_inputs, float** audio_outputs, void** midi_inputs, void** midi_outputs)
        {
            AVOIDDENORMALS;
            
            float** inputs_tmp = (float**)alloca(fDSP->getNumInputs()*sizeof(float*));
            float** outputs_tmp = (float**)alloca(fDSP->getNumOutputs()*sizeof(float*));
            
            for (int i = 0; i < fDSP->getNumInputs(); i++) {
                inputs_tmp[i] = audio_inputs[i+1];
            }
            
            for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                outputs_tmp[i] = audio_outputs[i+1];
            }
            
            // Control buffer always use buffer_size, even if uncomplete data buffer (count < buffer_size) is received
            decode_control(audio_inputs[0], fResult.buffer_size);
            
            // "count" may be less than buffer_size
            fDSP->compute(count, inputs_tmp, outputs_tmp);
            
            // Control buffer always use buffer_size, even if uncomplete data buffer (count < buffer_size) is received
            encode_control(audio_outputs[0], fResult.buffer_size);
        }
        
    public:
        
        netjackaudio_control(int net_format, const std::string& master_ip, int master_port, int mtu, int latency)
            :netjackaudio(net_format, master_ip, master_port, mtu, latency)
        {}
        
        virtual ~netjackaudio_control() 
        {}
        
        bool is_connexion_active()
        {
            return jack_net_slave_is_active(fNet);
        }
    
        virtual bool init(const char* name, dsp* dsp) 
        {
            dsp->buildUserInterface(this);
            return init_aux(name, dsp, dsp->getNumInputs() + 1, dsp->getNumOutputs() + 1, 0, 0); // One more audio port for control
        }
    
        virtual int restart_cb()
        {
            return -1;
        }
    
};

/*
A special NetJack client that uses MIDI input/output to transmit control values.
*/

class netjackaudio_midicontrol : public netjackaudio, public ControlUI, public jack_midi_handler {  
        
    protected:
        
        virtual void process(int count, float** audio_inputs, float** audio_outputs, void** midi_inputs, void** midi_outputs)
        {
            AVOIDDENORMALS;
            
            float** inputs_tmp = (float**)alloca(fDSP->getNumInputs()*sizeof(float*));
            float** outputs_tmp = (float**)alloca(fDSP->getNumOutputs()*sizeof(float*));
            
            for (int i = 0; i < fDSP->getNumInputs(); i++) {
                inputs_tmp[i] = audio_inputs[i];
            }
            
            for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                outputs_tmp[i] = audio_outputs[i];
            }
            
            // Control buffer always use buffer_size, even if uncomplete data buffer (count < buffer_size) is received
            decode_midi_control(midi_inputs[0], fResult.buffer_size);
            
            // Decode MIDI messages
            processMidiInBuffer(midi_inputs[1]);
            
            // "count" may be less than buffer_size
            fDSP->compute(count, inputs_tmp, outputs_tmp);
            
            // Control buffer always use buffer_size, even if uncomplete data buffer (count < buffer_size) is received
            encode_midi_control(midi_outputs[0], fResult.buffer_size);
            
            // Encode MIDI messages
            processMidiOutBuffer(midi_outputs[1], true);
        }
        
    public:
        
        netjackaudio_midicontrol(int net_format, const std::string& master_ip, int master_port, int mtu, int latency)
            :netjackaudio(net_format, master_ip, master_port, mtu, latency)
        {}
        
        virtual ~netjackaudio_midicontrol() 
        {}
        
        bool is_connexion_active()
        {
            return jack_net_slave_is_active(fNet);
        }
    
        virtual bool init(const char* name, dsp* dsp) 
        {
            dsp->buildUserInterface(this);
            // One MIDI channel for control, and one MIDI channel for messages in both direction
            return init_aux(name, dsp, dsp->getNumInputs(), dsp->getNumOutputs(), 2, 2);
        }
    
        virtual int restart_cb()
        {
            return -1;
        }
    
};

#endif

/********************END ARCHITECTURE SECTION (part 2/2)****************/

