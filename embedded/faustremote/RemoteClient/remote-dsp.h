/************************************************************************
 ************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2013 GRAME, Centre National de Creation Musicale
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
 
 ************************************************************************
 ************************************************************************/


#ifndef REMOTE_DSP_H
#define REMOTE_DSP_H

#include <string>
#include <map>
#include <vector>
#include "faust/audio/dsp.h"
#include "faust/gui/meta.h"

#ifdef __cplusplus
extern "C"
{
#endif
    
    enum {
        ERROR_FACTORY_NOTFOUND,
        ERROR_INSTANCE_NOTCREATED,
        ERROR_NETJACK_NOTSTARTED,
        ERROR_CURL_CONNECTION
    };
    
    class remote_dsp_factory {
        
        public: 
            
            int numInputs();
            int numOutputs();
    };
    
    /**
     * Get the Faust DSP factory associated with a given SHA key (created from the 'expanded' DSP source), 
     * if already allocated in the factories cache.
     *
     * @param ip_server - IP of remote machine
     * @param port_server - Port on which the Remote Server started
     * @param sha_key - the SHA key for an already created factory, kept in the factory cache
     *
     * @return a valid DSP factory if one is associated with the SHA key, otherwise a null pointer.
     */
    remote_dsp_factory* getRemoteDSPFactoryFromSHAKey(const std::string& ip_server, int port_server, const std::string& sha_key);    
    
    /**
     * Create a Remote DSP factory from a DSP source code. The code is compiled by a server, that returns a JSON application.
     *
     * @param filename - DSP filename
     * @param argc - the number of parameters in argv array
     * @param argv - the array of compilation parameters (-vec/-sch/...)
     * @param ip_server - IP of remote machine
     * @param port_server - Port on which the Remote Server started
     * @param error - the error string to be filled
     * @param opt_level - LLVM IR to IR optimization level (from 0 to 3)
     *
     * @return a valid DSP factory on success, otherwise a null pointer.
     */ 
    remote_dsp_factory* createRemoteDSPFactoryFromFile(const std::string& filename, 
                                                        int argc, const char* argv[], 
                                                        const std::string& ip_server, 
                                                        int port_server, 
                                                        std::string& error_msg, 
                                                        int opt_level = 3);
    
    /**
     * Create a Remote DSP factory from a DSP source code. The code is compiled by a server, that returns a JSON application.
     *
     * @param name_app - the name of the Faust Application to be compiled
     * @param dsp_content - the Faust program as a string
     * @param argc - the number of parameters in argv array
     * @param argv - the array of compilation parameters (-vec/-sch/...)
     * @param ip_server - IP of remote machine
     * @param port_server - Port on which the Remote Server started
     * @param error - the error string to be filled
     * @param opt_level - LLVM IR to IR optimization level (from 0 to 3)
     *
     * @return a valid DSP factory on success, otherwise a null pointer.
     */ 
    remote_dsp_factory* createRemoteDSPFactoryFromString(const std::string& name_app, 
                                                        const std::string& dsp_content, 
                                                        int argc, const char* argv[], 
                                                        const std::string& ip_server, 
                                                        int port_server, 
                                                        std::string& error_msg, 
                                                        int opt_level = 3);
    
    /**
     * Destroy a Faust DSP factory.
     * 
     * @param factory - the DSP factory to be deleted.
     */
    void deleteRemoteDSPFactory(remote_dsp_factory* factory);
    
    /**
     * Destroy all Faust DSP factories kept in the library cache. Beware : all kept factory pointers (in local variables or so...) thus become invalid.
     * 
     */                                 
    void deleteAllRemoteDSPFactories();
    
    /**
     * Call global declarations with the given meta object.
     * 
     * @param factory - the Faust DSP factory
     * @param meta - the meta object to be used.
     *
     */
    void metadataRemoteDSPFactory(remote_dsp_factory* factory, Meta* m);
    
    /**
     * Instance class
     */
    class remote_dsp : public dsp {
        
        public: 
            
            void metadata(Meta* m);
            
            virtual int getNumInputs();
            virtual int getNumOutputs();
            
            virtual void init(int samplingFreq);
            
            virtual void buildUserInterface(UI* ui);
            
            virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
            
            virtual void startAudio();
            virtual void stopAudio();
    };
    
    /*
     Possible error codes
     */
    #define NO_ERROR      0
    #define READ_ERROR   -1
    #define WRITE_ERROR  -2
    
    /**
     * Prototype for DSP instance error callback.
     * @param error_code an error code (see "Possible error codes")
     * @param arg pointer to a client supplied structure given by createRemoteDSPInstance()
     *
     * @return -1 to stop calling DSP 'compute', otherwise 0 to continue.
     */
    typedef int (*RemoteDSPErrorCallback) (int error_code, void* arg);
    
    /**
     * Create a remote DSP instance. A NetJack connexion is initialized with a specified sampling rate and buffer size. 
     * - if '--NJ_partial' is set, then the remote_dsp compute method can be safely called with 
     * a number of frames below bufferSize, partial buffers will be sent and received.
     * - parameter '--NJ_compression' can be used to chose between JackOpusEncoder format 
     * (when --NJ_compression > 0), 'JackFloatEncoder or 'JackIntEncoder'. 
     * An error callabck can be set to be notified in case of network transmision errors.
     * 
     * @param factory - the Remote DSP factory
     * @param argc - the number of parameters in argv array
     * @param argv - the array of parameters 
     *                  --NJ_ip ==> MULTICAST_DEFAULT_IP 
     *                  --NJ_port ==> MULTICAST_DEFAULT_PORT
     *                  --NJ_compression ==> if val > 0, JackOpusEncoder format is used with val kBits, 
     *                                      -1 means 'JackFloatEncoder', -2 means 'JackIntEncoder' (default is 'JackFloatEncoder')
     *                  --NJ_latency ==> default is 2 cycles
     *                  --NJ_mtu ==> default is 1500
     *                  --NJ_partial ==> default is 'false'
     * @param sampling_rate - NetJack slave sampling rate
     * @param buffer_size - NetJack slave buffer size
     * @param error_callback - error callback
     * @param error_callback_arg - error callback argument
     * @param error - the error value to be filled
     * 
     * @return the remote DSP instance on success, otherwise a null pointer.
     */
    remote_dsp* createRemoteDSPInstance(remote_dsp_factory* factory, 
                                        int argc, const char* argv[], 
                                        int sampling_rate, int buffer_size, 
                                        RemoteDSPErrorCallback error_callback,
                                        void* error_callback_arg,
                                        int& error);
    
    /**
     * Destroy a remote DSP instance.
     * 
     * @param dsp - the DSP instance to be deleted.
     */ 
    void deleteRemoteDSPInstance(remote_dsp* dsp);
    
    /**
     * Scan the network to find the available machines for Remote Processing
     * @param machine_list - map to be filled with <name_machine, <ip_machine, port_machine>>
     *
     * @return true if no error was encountered.
     */
    bool getRemoteMachinesAvailable(std::map<std::string, std::pair<std::string, int> >* machine_list);
    
    /**
     * For a machine on the network that does Remote Processing, get the list of all currently available DSP factories.
     * @param ip_server - IP of remote machine
     * @param port_server - port on which the Remote Server started
     * @param factories_list - vector to be filled with <name_factory, shakey_factory>
     *
     * @return true if no error was encountered.
     */    
    bool getRemoteFactoriesAvailable(const std::string& ip_server, int port_server, std::vector<std::pair<std::string, std::string> >* factories_list);
    
#ifdef __cplusplus
}
#endif

#endif

