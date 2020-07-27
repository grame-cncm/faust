/************************** BEGIN jack-dsp.h **************************/
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

#ifndef __jack_dsp__
#define __jack_dsp__

#include <stdio.h>
#include <cstdlib>
#include <list>
#include <vector>
#include <string.h>
#include <jack/jack.h>

#include "faust/midi/jack-midi.h"
#include "faust/audio/audio.h"
#include "faust/dsp/dsp.h"

#if defined(_WIN32) && !defined(__MINGW32__)
#define snprintf _snprintf_s
#endif

/******************************************************************************
 *******************************************************************************
 
 JACK AUDIO INTERFACE
 
 *******************************************************************************
 *******************************************************************************/

class jackaudio : public audio {
    
    protected:
        
        dsp* fDSP;              // FAUST DSP
        jack_client_t* fClient; // JACK client
        
        std::vector<jack_port_t*> fInputPorts;   // JACK input ports
        std::vector<jack_port_t*> fOutputPorts;  // JACK output ports
        
        std::vector<char*> fPhysicalInputs;
        std::vector<char*> fPhysicalOutputs;
        
        bool fAutoConnect;  // autoconnect with system in/out ports
        
        std::list<std::pair<std::string, std::string> > fConnections;   // Connections list
        
        static int _jack_srate(jack_nframes_t nframes, void* arg)
        {
            fprintf(stdout, "The sample rate is now %u/sec\n", nframes);
            return 0;
        }
        
        static void _jack_shutdown(void* arg)
        {}
        
        static void _jack_info_shutdown(jack_status_t code, const char* reason, void* arg)
        {
            fprintf(stderr, "%s\n", reason);
            static_cast<jackaudio*>(arg)->shutdown(reason);
        }
        
        static int _jack_process(jack_nframes_t nframes, void* arg)
        {
            return static_cast<jackaudio*>(arg)->process(nframes);
        }
        
        static int _jack_buffersize(jack_nframes_t nframes, void* arg)
        {
            fprintf(stdout, "The buffer size is now %u/sec\n", nframes);
            return 0;
        }
        
    #ifdef _OPENMP
        static void* _jack_thread(void* arg)
        {
            jackaudio* audio = (jackaudio*)arg;
            audio->process_thread();
            return 0;
        }
    #endif
        
        void shutdown(const char* message)
        {
            fClient = nullptr;
            
            if (fShutdown) {
                fShutdown(message, fShutdownArg);
            } else {
                exit(1); // By default
            }
        }
        
        // Save client connections
        virtual bool saveConnections()
        {
            if (fClient) {
                fConnections.clear();
                
                for (size_t i = 0; i < fInputPorts.size(); i++) {
                    const char** connected_port = jack_port_get_all_connections(fClient, fInputPorts[i]);
                    if (connected_port != nullptr) {
                        for (int port = 0; connected_port[port]; port++) {
                            fConnections.push_back(std::make_pair(connected_port[port], jack_port_name(fInputPorts[i])));
                            // printf("INPUT %s ==> %s\n", connected_port[port], jack_port_name(fInputPorts[i]));
                        }
                        jack_free(connected_port);
                    }
                }
                
                for (size_t i = 0; i < fOutputPorts.size(); i++) {
                    const char** connected_port = jack_port_get_all_connections(fClient, fOutputPorts[i]);
                    if (connected_port != nullptr) {
                        for (int port = 0; connected_port[port]; port++) {
                            fConnections.push_back(std::make_pair(jack_port_name(fOutputPorts[i]), connected_port[port]));
                            // printf("OUTPUT %s ==> %s\n", jack_port_name(fOutputPorts[i]), connected_port[port]);
                        }
                        jack_free(connected_port);
                    }
                }
                return true;
            } else {
                fprintf(stdout, "Client no more running...\n");
                return false;
            }
        }
        
        // Load client connections
        void loadConnections()
        {
            std::list<std::pair<std::string, std::string> >::const_iterator it;
            for (it = fConnections.begin(); it != fConnections.end(); it++) {
                std::pair<std::string, std::string> connection = *it;
                jack_connect(fClient, connection.first.c_str(), connection.second.c_str());
            }
        }
        
    #ifdef _OPENMP
        void process_thread()
        {
            jack_nframes_t nframes;
            while (1) {
                nframes = jack_cycle_wait(fClient);
                process(nframes);
                jack_cycle_signal(fClient, 0);
            }
        }
    #endif
        
        // JACK callbacks
        virtual int	process(jack_nframes_t nframes)
        {
            AVOIDDENORMALS;
            
            // Retrieve JACK inputs/output audio buffers
            float** fInChannel = (float**)alloca(fInputPorts.size() * sizeof(float*));
            for (size_t i = 0; i < fInputPorts.size(); i++) {
                fInChannel[i] = (float*)jack_port_get_buffer(fInputPorts[i], nframes);
            }
            
            float** fOutChannel = (float**)alloca(fOutputPorts.size() * sizeof(float*));
            for (size_t i = 0; i < fOutputPorts.size(); i++) {
                fOutChannel[i] = (float*)jack_port_get_buffer(fOutputPorts[i], nframes);
            }
            
            fDSP->compute(nframes, reinterpret_cast<FAUSTFLOAT**>(fInChannel), reinterpret_cast<FAUSTFLOAT**>(fOutChannel));
            
            runControlCallbacks();
            return 0;
        }
        
    public:
        
        jackaudio(bool auto_connect = true)
        : fDSP(0), fClient(0), fAutoConnect(auto_connect)
        {}
        
        virtual ~jackaudio()
        {
            if (fClient) {
                stop();
                
                for (size_t i = 0; i < fInputPorts.size(); i++) {
                    jack_port_unregister(fClient, fInputPorts[i]);
                }
                for (size_t i = 0; i < fOutputPorts.size(); i++) {
                    jack_port_unregister(fClient, fOutputPorts[i]);
                }
                jack_client_close(fClient);
            }
        }
        
        virtual bool init(const char* name, dsp* dsp)
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
            if ((fClient = jack_client_open(name, JackNullOption, nullptr)) == 0) {
                fprintf(stderr, "JACK server not running ?\n");
                return false;
            }
            
    #ifdef _OPENMP
            jack_set_process_thread(fClient, _jack_thread, this);
    #else
            jack_set_process_callback(fClient, _jack_process, this);
    #endif
            
            jack_set_sample_rate_callback(fClient, _jack_srate, this);
            jack_set_buffer_size_callback(fClient, _jack_buffersize, this);
            jack_on_info_shutdown(fClient, _jack_info_shutdown, this);
            
            // Get Physical inputs
            int inputs = 0;
            char** physicalInPorts = (char**)jack_get_ports(fClient, nullptr, JACK_DEFAULT_AUDIO_TYPE, JackPortIsPhysical|JackPortIsOutput);
            if (physicalInPorts != nullptr) {
                while (physicalInPorts[inputs]) {
                    fPhysicalInputs.push_back(physicalInPorts[inputs]);
                    printf("physical input %s\n", physicalInPorts[inputs]);
                    inputs++;
                }
                jack_free(physicalInPorts);
            }
            
            // Get Physical outputs
            int outputs = 0;
            char** physicalOutPorts = (char**)jack_get_ports(fClient, nullptr, JACK_DEFAULT_AUDIO_TYPE, JackPortIsPhysical|JackPortIsInput);
            if (physicalOutPorts != nullptr) {
                while (physicalOutPorts[outputs]) {
                    fPhysicalOutputs.push_back(physicalOutPorts[outputs]);
                    printf("physical output %s\n", physicalOutPorts[outputs]);
                    outputs++;
                }
                jack_free(physicalOutPorts);
            }
            
            return true;
        }
        
        virtual bool start()
        {
            if (jack_activate(fClient)) {
                fprintf(stderr, "Cannot activate client\n");
                return false;
            }
            
            if (fConnections.size() > 0) {
                loadConnections();
            } else if (fAutoConnect) {
                defaultConnections();
            }
            
            return true;
        }
        
        virtual void stop()
        {
            if (fClient) {
                saveConnections();
                jack_deactivate(fClient);
            }
        }
        
        virtual int getBufferSize() { return jack_get_buffer_size(fClient); }
        virtual int getSampleRate() { return jack_get_sample_rate(fClient); }
        
        virtual int getNumInputs()
        {
            return fPhysicalInputs.size();
        }
        
        virtual int getNumOutputs()
        {
            return fPhysicalOutputs.size();
        }
        
        // Additional public API
        
        jack_client_t* getClient() { return fClient; }
        
        // Connect to physical inputs/outputs
        void defaultConnections()
        {
            // To avoid feedback at launch time, don't connect hardware inputs
            /*
             for (int i = 0; i < fInputPorts.size() && i < fPhysicalOutputs.size(); i++) {
                jack_connect(fClient, fPhysicalInputs[i], jack_port_name(fInputPorts[i]));
             }
             */
            for (size_t i = 0; i < fOutputPorts.size() && i < fPhysicalInputs.size(); i++) {
                jack_connect(fClient, jack_port_name(fOutputPorts[i]), fPhysicalOutputs[i]);
            }
        }
        
        virtual void setDsp(dsp* dsp)
        {
            fDSP = dsp;
            for (int i = 0; i < fDSP->getNumInputs(); i++) {
                char buf[256];
                snprintf(buf, 256, "in_%d", i);
                fInputPorts.push_back(jack_port_register(fClient, buf, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0));
            }
            for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                char buf[256];
                snprintf(buf, 256, "out_%d", i);
                fOutputPorts.push_back(jack_port_register(fClient, buf, JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0));
            }
            fDSP->init(jack_get_sample_rate(fClient));
        }
        
        void connect(jackaudio* driver, int src, int dst, bool reverse)
        {
            if (driver) {
                // Connection between drivers
                jack_port_t* src_port = getOutputPort(src);
                jack_port_t* dst_port = driver->getInputPort(src);
                if (src_port && dst_port) {
                    jack_connect(fClient, jack_port_name(src_port), jack_port_name(dst_port));
                }
            } else if (reverse) {
                // Connection to physical input
                if ((size_t)src > fPhysicalInputs.size()) return;
                jack_port_t* dst_port = getInputPort(dst);
                if (dst_port) {
                    jack_connect(fClient, fPhysicalInputs[src], jack_port_name(dst_port));
                }
            } else {
                // Connection to physical output
                if ((size_t)dst > fPhysicalOutputs.size()) return;
                jack_port_t* src_port = getOutputPort(src);
                if (src_port) {
                    jack_connect(fClient, jack_port_name(src_port), fPhysicalOutputs[dst]);
                }
            }
        }
        
        void disconnect(jackaudio* driver, int src, int dst, bool reverse)
        {
            if (driver) {
                // Connection between drivers
                jack_port_t* src_port = getOutputPort(src);
                jack_port_t* dst_port = driver->getInputPort(src);
                if (src_port && dst_port) {
                    jack_disconnect(fClient, jack_port_name(src_port), jack_port_name(dst_port));
                }
            } else if (reverse) {
                // Connection to physical input
                if ((size_t)src > fPhysicalInputs.size()) return;
                jack_port_t* dst_port = getInputPort(dst);
                if (dst_port) {
                    jack_disconnect(fClient, fPhysicalInputs[src], jack_port_name(dst_port));
                }
            } else {
                // Connection to physical output
                if ((size_t)dst > fPhysicalOutputs.size()) return;
                jack_port_t* src_port = getOutputPort(src);
                if (src_port) {
                    jack_disconnect(fClient, jack_port_name(src_port), fPhysicalOutputs[dst]);
                }
            }
        }
        
        bool isConnected(jackaudio* driver, int src, int dst, bool reverse)
        {
            if (driver) {
                // Connection between drivers
                jack_port_t* src_port = getOutputPort(src);
                jack_port_t* dst_port = driver->getInputPort(src);
                if (src_port && dst_port) {
                    return jack_port_connected_to(src_port, jack_port_name(dst_port));
                } else {
                    return false;
                }
            } else if (reverse) {
                // Connection to physical input
                if ((size_t)src > fPhysicalInputs.size()) return false;
                jack_port_t* dst_port = getInputPort(dst);
                if (dst_port) {
                    return jack_port_connected_to(dst_port, fPhysicalInputs[src]);
                } else {
                    return false;
                }
            } else {
                // Connection to physical output
                if ((size_t)dst > fPhysicalOutputs.size()) return false;
                jack_port_t* src_port = getOutputPort(src);
                if (src_port) {
                    return jack_port_connected_to(src_port, fPhysicalOutputs[dst]);
                } else {
                    return false;
                }
            }
        }
        
        jack_port_t* getInputPort(int port)  { return (port >= 0 && port < (int)fInputPorts.size()) ? fInputPorts[port] : nullptr; }
        jack_port_t* getOutputPort(int port) { return (port >= 0 && port < (int)fOutputPorts.size()) ? fOutputPorts[port] : nullptr; }
        
};

// Add JACK MIDI

class jackaudio_midi : public jackaudio, public jack_midi_handler {
        
    protected:
    
        bool fPolling;
    
        virtual bool saveConnections()
        {
            if (jackaudio::saveConnections()) { // Audio connections can be saved, so try MIDI
                
                if (fInputMidiPort) {
                    const char** connected_port = jack_port_get_all_connections(fClient, fInputMidiPort);
                    if (connected_port != nullptr) {
                        for (int port = 0; connected_port[port]; port++) {
                            fConnections.push_back(std::make_pair(connected_port[port], jack_port_name(fInputMidiPort)));
                            // printf("INPUT %s ==> %s\n", connected_port[port], jack_port_name(fInputPorts[i]));
                        }
                        jack_free(connected_port);
                    }
                }
                
                if (fOutputMidiPort) {
                    const char** connected_port = jack_port_get_all_connections(fClient, fOutputMidiPort);
                    if (connected_port != nullptr) {
                        for (int port = 0; connected_port[port]; port++) {
                            fConnections.push_back(std::make_pair(jack_port_name(fOutputMidiPort), connected_port[port]));
                            // printf("OUTPUT %s ==> %s\n", jack_port_name(fOutputPorts[i]), connected_port[port]);
                        }
                        jack_free(connected_port);
                    }
                }
                return true;
                
            } else {
                return false;
            }
        }
    
        virtual void processAudio(jack_nframes_t nframes)
        {
            // Audio
            AVOIDDENORMALS;
            
            // Retrieve JACK inputs/output audio buffers
            float** fInChannel = (float**)alloca(fInputPorts.size() * sizeof(float*));
            for (size_t i = 0; i < fInputPorts.size(); i++) {
                fInChannel[i] = (float*)jack_port_get_buffer(fInputPorts[i], nframes);
            }
            
            float** fOutChannel = (float**)alloca(fOutputPorts.size() * sizeof(float*));
            for (size_t i = 0; i < fOutputPorts.size(); i++) {
                fOutChannel[i] = (float*)jack_port_get_buffer(fOutputPorts[i], nframes);
            }
            
            // By convention timestamp of -1 means 'no timestamp conversion' : events already have a timestamp espressed in frames
            fDSP->compute(-1, nframes, reinterpret_cast<FAUSTFLOAT**>(fInChannel), reinterpret_cast<FAUSTFLOAT**>(fOutChannel));
        }
    
        virtual int process(jack_nframes_t nframes)
        {
            // MIDI in
            if (!fPolling) processMidiIn(nframes);
            
            // Audio
            processAudio(nframes);
            
            // MIDI out
            processMidiOut(nframes);
            
            runControlCallbacks();
            return 0;
        }
        
    public:
        
        jackaudio_midi(bool auto_connect = true, bool is_polling = false)
        :jackaudio(auto_connect), jack_midi_handler("JACKMidi"), fPolling(is_polling)
        {}
        
        virtual ~jackaudio_midi()
        {}
        
        virtual bool init(const char* name, dsp* dsp)
        {
            if (jackaudio::initAux(name)) {
                if (dsp) { setDsp(dsp); }
                return initPorts(fClient);
            } else {
                return false;
            }
        }
        
        virtual bool start()
        {
            return jackaudio::start();
        }
        
        virtual void stop()
        {
            jackaudio::stop();
        }
    
};

#endif
/**************************  END  jack-dsp.h **************************/
