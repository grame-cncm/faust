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

#include "faust/audio/audio.h"
#include "faust/audio/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/ControlUI.h"
#include <jack/net.h>
#include <string>
#include <vector>
#include <assert.h>

class netjackaudio : public audio
{

    protected:
    
        dsp* fDsp;
        jack_net_slave_t* fNet;
        int fCelt;
        std::string fMasterIP;
        int fMasterPort;
        int fLatency;

    #ifdef RESTART_CB_API
        static int net_restart(void* arg) 
        {
            printf("Network failure, restart...\n");
            return 0;
        }
    #else 
        static void net_shutdown(void* arg) 
        {
            printf("Network failure, restart...\n");
        }
    #endif
        
        static int net_sample_rate(jack_nframes_t nframes, void* arg) 
        {
            netjackaudio* obj = (netjackaudio*)arg;
            printf("New sample rate = %u\n", nframes);
            obj->fDsp->init(nframes);
            return 0;
        }

        static int net_process(jack_nframes_t buffer_size,
                               int,
                               float** audio_input_buffer,
                               int,
                               void**,
                               int,
                               float** audio_output_buffer,
                               int,
                               void**,
                               void* arg) 
        {
            static_cast<netjackaudio*>(arg)->process(buffer_size, audio_input_buffer, audio_output_buffer);
            return 0;
        }
        
        virtual void process(int count,  float** inputs, float** outputs)
        {
             AVOIDDENORMALS;
             fDsp->compute(count, inputs, outputs);
        }
        
        bool init_aux(const char* name, dsp* DSP, int inputs, int outputs) 
        {
            fDsp = DSP;
            jack_slave_t request = {
                inputs,
                outputs,
                0, 0,
                DEFAULT_MTU,
                -1,
                (fCelt > 0) ? JackCeltEncoder : JackFloatEncoder,
                (fCelt > 0) ? fCelt : 0,
                fLatency
            };

            jack_master_t result;
            if ((fNet = jack_net_slave_open(fMasterIP.c_str(), fMasterPort, name, &request, &result)) == 0) {
                printf("jack remote server not running ?\n");
                return false;
            }

            jack_set_net_slave_process_callback(fNet, net_process, this);
        #ifdef RESTART_CB_API
            jack_set_net_slave_restart_callback(fNet, net_restart, this);
        #else
            jack_set_net_slave_shutdown_callback(fNet, net_shutdown, this);
        #endif
            jack_set_net_slave_sample_rate_callback(fNet, net_sample_rate, this);

            fDsp->init(result.sample_rate);
            return true;
        }

    public:

        netjackaudio(int celt, const std::string master_ip, int master_port, int latency = 2)
            : fDsp(0), fNet(0), fCelt(celt), fMasterIP(master_ip), fMasterPort(master_port), fLatency(latency)
        {}
        
        virtual ~netjackaudio() 
        {}

        virtual bool init(const char* name, dsp* DSP) 
        {
            return init_aux(name, DSP, DSP->getNumInputs(), DSP->getNumOutputs());
        }

        virtual bool start() {
            if (jack_net_slave_activate(fNet)) {
                printf("cannot activate net");
                return false;
            }
            return true;
        }

        virtual void stop() {
            jack_net_slave_deactivate(fNet);
            jack_net_slave_close(fNet);
        }

};

/*
A special NetJack client that uses one more audio input/output to transmit control values.
*/

class netjackaudio_control : public netjackaudio, public ControlUI {  
  
    protected:
    
        virtual void process(int count,  float** inputs, float** outputs)
        {
            AVOIDDENORMALS;
            decode_control(inputs[fDsp->getNumInputs()], count);
            fDsp->compute(count, inputs, outputs);
            encode_control(outputs[fDsp->getNumOutputs()], count);
        }
   
    public:
    
        netjackaudio_control(int celt, const std::string master_ip, int master_port, int latency = 2)
            :netjackaudio(celt, master_ip, master_port, latency)
        {}
        
        virtual ~netjackaudio_control() 
        {}
        
        virtual bool init(const char* name, dsp* DSP) 
        {
            DSP->buildUserInterface(this);
            return init_aux(name, DSP, DSP->getNumInputs() + 1, DSP->getNumOutputs() + 1); // One more audio port for control
        }
        
};

#endif

/********************END ARCHITECTURE SECTION (part 2/2)****************/

