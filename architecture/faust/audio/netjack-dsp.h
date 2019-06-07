/************************** BEGIN netjack-dsp.h **************************/
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
        int fMIDIInputs;
        int fMIDIOutputs;
        jack_master_t fResult;

    #ifdef RESTART_CB_API
        static int netRestart(void* arg)
        {
            printf("Network failure, restart...\n");
            return static_cast<netjackaudio*>(arg)->restartCb();
        }
    #else 
        static void netShutdown(void* arg)
        {
            printf("Network failure, shutdown...\n");
            static_cast<netjackaudio*>(arg)->shutdown_cb();
        }
    #endif
    
        static int netSampleRate(jack_nframes_t nframes, void* arg)
        {
            return static_cast<netjackaudio*>(arg)->setSampleRate(nframes);
        }
        
        static int netBufferSize(jack_nframes_t nframes, void* arg)
        {
            return static_cast<netjackaudio*>(arg)->setBufferSize(nframes);
        }
        
        static void netError(int error_code, void* arg)
        {
            return static_cast<netjackaudio*>(arg)->errorCb(error_code);
        }
        
        static int netProcess(jack_nframes_t buffer_size,
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

        bool initAux(const char* name, dsp* DSP, int audio_inputs, int audio_outputs, int midi_inputs, int midi_outputs)
        {
            if (initAux(name, audio_inputs, audio_outputs, midi_inputs, midi_outputs)) {
                setDsp(DSP);
                return true;
            } else {
                return false;
            }
        }
    
        bool initAux(const char* name, int audio_inputs, int audio_outputs, int midi_inputs, int midi_outputs)
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

            jack_set_net_slave_process_callback(fNet, netProcess, this);
        #ifdef RESTART_CB_API
            jack_set_net_slave_restart_callback(fNet, netRestart, this);
        #else
            jack_set_net_slave_shutdown_callback(fNet, netShutdown, this);
        #endif
            jack_set_net_slave_sample_rate_callback(fNet, netSampleRate, this);
            jack_set_net_slave_buffer_size_callback(fNet, netBufferSize, this);
            jack_set_net_slave_error_callback(fNet, netError, this);

            return true;
        }
    
        // Possibly to be redefined by subclasses
        
        virtual int restartCb()
        {
            return 0;
        }
       
        virtual void shutdownCb()
        {}
        
        virtual void errorCb(int error_code)
        {}
       
        virtual int setSampleRate(jack_nframes_t nframes)
        {
            return 0;
        }
        
        virtual int setBufferSize(jack_nframes_t nframes)
        {
            return 0;
        }

        virtual void process(int count, float** audio_inputs, float** audio_outputs, void** midi_inputs, void** midi_outputs)
        {
             AVOIDDENORMALS;
             fDSP->compute(count, audio_inputs, audio_outputs);
        }

    public:

        netjackaudio(int net_format,
                     const std::string& master_ip,
                     int master_port,
                     int mtu,
                     int latency,
                     int midi_in,
                     int midi_out)
            : fDSP(0),
            fNet(0),
            fNetFormat(net_format),
            fMasterIP(master_ip),
            fMasterPort(master_port),
            fMTU(mtu),
            fLatency(latency),
            fMIDIInputs(midi_in),
            fMIDIOutputs(midi_out)
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
            return initAux(name, DSP, DSP->getNumInputs(), DSP->getNumOutputs(), fMIDIInputs, fMIDIOutputs);
        }

        virtual bool start() 
        {
            if (jack_net_slave_activate(fNet)) {
                printf("cannot activate net\n");
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
        
        virtual bool isConnexionActive()
        {
            return jack_net_slave_is_active(fNet);
        }

        void setDsp(dsp* DSP)
        {
            fDSP = DSP;
            fDSP->init(fResult.sample_rate);
        }
        
        virtual int getBufferSize() { return fResult.buffer_size; }
        virtual int getSampleRate() { return fResult.sample_rate; }
    
        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }

};

/*
A special NetJack client that uses one more audio input/output to transmit control values.
*/

class netjackaudio_control : public netjackaudio, public ControlUI {  
        
    protected:
        
        virtual void process(int count, float** audio_inputs, float** audio_outputs, void** midi_inputs, void** midi_outputs)
        {
            AVOIDDENORMALS;
            
            // Control buffer always use buffer_size, even if uncomplete data buffer (count < buffer_size) is received
            decodeControl(audio_inputs[0], fResult.buffer_size);
            
            // "count" may be less than buffer_size
            fDSP->compute(count, audio_inputs, audio_outputs);
            
            // Control buffer always use buffer_size, even if uncomplete data buffer (count < buffer_size) is received
            encodeControl(audio_outputs[0], fResult.buffer_size);
        }
        
    public:
        
        netjackaudio_control(int net_format,
                             const std::string& master_ip,
                             int master_port,
                             int mtu,
                             int latency)
            :netjackaudio(net_format, master_ip, master_port, mtu, latency, 0, 0)
        {}
        
        virtual ~netjackaudio_control() 
        {}
    
        bool isConnexionActive()
        {
            return jack_net_slave_is_active(fNet);
        }
    
        virtual bool init(const char* name, dsp* dsp) 
        {
            dsp->buildUserInterface(this);
            return initAux(name, dsp, dsp->getNumInputs() + 1, dsp->getNumOutputs() + 1, fMIDIInputs, fMIDIOutputs); // One more audio port for control
        }
    
        virtual int restartCb()
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
            
            // Control buffer always use buffer_size, even if uncomplete data buffer (count < buffer_size) is received
            decodeMidiControl(midi_inputs[0], fResult.buffer_size);
            
            // Decode MIDI messages
            processMidiInBuffer(midi_inputs[1]);
            
            // "count" may be less than buffer_size
            fDSP->compute(count, audio_inputs, audio_outputs);
            
            // Control buffer always use buffer_size, even if uncomplete data buffer (count < buffer_size) is received
            encodeMidiControl(midi_outputs[0], fResult.buffer_size);
            
            // Encode MIDI messages
            processMidiOutBuffer(midi_outputs[1], true);
        }
        
    public:
    
        // One MIDI port for control, and one MIDI port for messages in both directions
        netjackaudio_midicontrol(int net_format,
                                 const std::string& master_ip,
                                 int master_port,
                                 int mtu,
                                 int latency)
            :netjackaudio(net_format, master_ip, master_port, mtu, latency, 2, 2)
        {}
        
        virtual ~netjackaudio_midicontrol() 
        {}
    
        bool isConnexionActive()
        {
            return jack_net_slave_is_active(fNet);
        }
    
        virtual bool init(const char* name, dsp* dsp) 
        {
            dsp->buildUserInterface(this);
            return initAux(name, dsp, dsp->getNumInputs(), dsp->getNumOutputs(), fMIDIInputs, fMIDIOutputs);
        }
    
        virtual int restartCb()
        {
            return -1;
        }
    
};

#endif

/********************END ARCHITECTURE SECTION (part 2/2)****************/

/**************************  END  netjack-dsp.h **************************/
