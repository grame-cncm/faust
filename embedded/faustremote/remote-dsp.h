/************************************************************************
 ************************************************************************
 FAUST Architecture File
 Copyright (C) 2013-2015 GRAME, Centre National de Creation Musicale
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
#include "faust/dsp/dsp.h"
#include "faust/gui/meta.h"
#include "faust/midi/midi.h"

/**
 * Possible error codes
*/
    
enum {
    ERROR_FACTORY_NOTFOUND,
    ERROR_INSTANCE_NOTCREATED,
    ERROR_NETJACK_NOTSTARTED,
    ERROR_NETJACK_READ,
    ERROR_NETJACK_WRITE,
    ERROR_CURL_CONNECTION
};

/**
 * DSP factory class.
 * Each received DSP source will be compiled as a 'DSP factory'. Depending of the kind of created factory 
 * (local = client side) or (remote = server side), 'DSP instances' will be create locally or remotely.
 * Remote 'DSP instances' will be connected to the client side using NetJack master/slave connection
 * or possibly launched on server side.
 */
class remote_dsp_factory : public dsp_factory {
    
    public: 
    
        /* Return Factory name */
        std::string getName();
        
        /* Return Factory SHA key */
        std::string getSHAKey();
  
        /* Return Factory expanded DSP code */
        std::string getDSPCode();
        
};

/**
 * Get the Faust remote DSP factory associated with a given SHA key (created from the 'expanded' DSP source), 
 * if already allocated in the factories cache and increment it's reference counter. You will have to explicitly
 * use deleteRemoteDSPFactory to properly decrement reference counter when the factory is no more needed.
 *
 * @param sha_key - the SHA key for an already created factory, kept in the factory cache
 * @param ip_server - IP of remote machine
 * @param port_server - port on which the remote machine started
 *
 * @return a valid DSP factory if one is associated with the SHA key, otherwise a null pointer.
 */
remote_dsp_factory* getRemoteDSPFactoryFromSHAKey(const std::string& sha_key, const std::string& ip_server, int port_server); 

/**
 * Create a Faust remote DSP factory from a DSP source code. You will have to explicitly use 
 * deleteRemoteDSPFactory to properly decrement reference counter when the factory is no more needed.
 *
 * @param filename - DSP filename
 * @param argc - the number of parameters in argv array
 * @param argv - the array of compilation parameters :
 *  - Faust compilation parameters (like '-vec/-sch/'...)
 *  - '-lm <target>' (like '-lm x86_64-apple-macosx10.6.0:opteron') to cross-compile on client side and send machine code on server
 *  - '-rm <target>' (like '-rm arm-apple-ios7.0:cortex-a9') to cross-compile on server side and get machine code on client to re-create a local Factory
 *  - '-poly <0/1>' to create a polyphonic DSP factory
 *  - '-voices <num>' number of polyphonic DSP voices
 *  - '-group <0/1>' whether to group polyphonic DSP voices
 * @param ip_server - IP of remote machine
 * @param port_server - port on which the remote machine started
 * @param error - the error string to be filled
 * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value')
 *
 * @return a valid DSP factory on success, otherwise a null pointer.
 */ 
remote_dsp_factory* createRemoteDSPFactoryFromFile(const std::string& filename, 
                                                    int argc, const char* argv[], 
                                                    const std::string& ip_server, 
                                                    int port_server, 
                                                    std::string& error_msg, 
                                                    int opt_level = -1);

/**
 * Create a Faust remote DSP factory from a DSP source code. You will have to explicitly use  
 * deleteRemoteDSPFactory to properly decrement reference counter when the factory is no more needed.
 *
 * @param name_app - the name of the Faust Application to be compiled
 * @param dsp_content - the Faust program as a string
 * @param argc - the number of parameters in argv array
 * @param argv - the array of compilation parameters :
 *  - Faust compilation parameters (like '-vec/-sch/'...)
 *  - '-lm <target>' (like '-lm x86_64-apple-macosx10.6.0:opteron') to cross-compile on client side and send machine code on server
 *  - '-rm <target>' (like '-rm arm-apple-ios7.0:cortex-a9') to cross-compile on server side and get machine code on client to re-create a local Factory
 *  - '-poly <0/1>' to create a polyphonic DSP factory
 *  - '-voices <num>' number of polyphonic DSP voices
 *  - '-group <0/1>' whether to group polyphonic DSP voices
 * @param ip_server - IP of remote machine
 * @param port_server - port on which the remote machine started
 * @param error - the error string to be filled
 * @param opt_level - LLVM IR to IR optimization level (from -1 to 4, -1 means 'maximum possible value')
 *
 * @return a valid DSP factory on success, otherwise a null pointer.
 */ 
remote_dsp_factory* createRemoteDSPFactoryFromString(const std::string& name_app, 
                                                    const std::string& dsp_content, 
                                                    int argc, const char* argv[], 
                                                    const std::string& ip_server, 
                                                    int port_server, 
                                                    std::string& error_msg, 
                                                    int opt_level = -1);

/**
 * Delete a Faust remote DSP factory, that is decrements it's reference counter, possible really deleting the internal pointer. 
 * Possibly also delete DSP pointers associated with this factory.
 * Beware : all kept factories and DSP pointers (in local variables...) thus become invalid.
 * 
 * @param factory - the DSP factory
 *
 * @return true if the factory internal pointer was really deleted, and false if only 'decremented'.
 */
bool deleteRemoteDSPFactory(remote_dsp_factory* factory);

/**
 * Delete all Faust remote DSP factories kept in the library cache. Beware : all kept factory pointers (in local variables...) thus become invalid.
 * 
 */                                 
void deleteAllRemoteDSPFactories();

/**
 * Call global declarations with the given meta object.
 * 
 * @param factory - the DSP factory
 *
 * @param meta - the meta object to be used.
 *
 */
void metadataRemoteDSPFactory(remote_dsp_factory* factory, Meta* m);

/**
 * Get the list of library dependancies of the Faust remote DSP factory.
 *
 * @param factory - the DSP factory
 * 
 * @return the list as a vector of strings.
 */
std::vector<std::string> getRemoteDSPFactoryLibraryList(remote_dsp_factory* factory);

/**
 * Remote DSP instance class with methods.
 */
class remote_dsp : public dsp, public midi {
    
    public: 
        
        int getNumInputs();
    
        int getNumOutputs();
    
        void buildUserInterface(UI* ui);
    
        int getSampleRate();
        
        void init(int samplingRate);
    
        void instanceInit(int samplingRate);
    
        void instanceConstants(int samplingRate);
    
        void instanceResetUserInterface();
    
        void instanceClear();
    
        remote_dsp* clone();
    
        void metadata(Meta* m);
    
        void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
    
        // MIDI polyphonic control
        MapUI* keyOn(int channel, int pitch, int velocity);
        
        void keyOff(int channel, int pitch, int velocity);
        
        void keyPress(int channel, int pitch, int press);
        
        void chanPress(int channel, int press);
        
        void ctrlChange(int channel, int ctrl, int value);
        
        void pitchWheel(int channel, int wheel);
        
        void progChange(int channel, int pgm);

};

/**
 * Prototype for remote DSP instance error callback.
 * @param error_code - an error code (see "Possible error codes")
 * @param arg - pointer to a client supplied structure given by createRemoteDSPInstance()
 *
 * @return -1 to stop calling DSP 'compute', otherwise 0 to continue.
 */
typedef int (*remoteDSPErrorCallback) (int error_code, void* arg);

/**
 * Create a Faust local/remote DSP instance, depending of the kind of factory is it created from.
 * When created rempotely, a NetJack connexion is initialized with a specified sampling rate and buffer size. 
 * - if '--NJ_partial' is set, then the remote_dsp compute method can be safely called with 
 * a number of frames below bufferSize, partial buffers will be sent and received.
 * - parameter '--NJ_compression' can be used to chose between JackOpusEncoder format 
 * (when --NJ_compression > 0), 'JackFloatEncoder or 'JackIntEncoder'. 
 * An error callabck can be set to be notified in case of network transmision errors.
 * 
 * @param factory - the DSP factory
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters 
 *                  --NJ_ip ==> MULTICAST_DEFAULT_IP 
 *                  --NJ_port ==> MULTICAST_DEFAULT_PORT
 *                  --NJ_compression ==> if val > 0, JackOpusEncoder format is used with val kBits, 
 *                                      -1 means 'JackFloatEncoder', -2 means 'JackIntEncoder' (default is 'JackFloatEncoder')
 *                  --NJ_latency ==> default is 2 cycles
 *                  --NJ_mtu ==> default is 1500
 *                  --NJ_partial ==> default is 'false'
 *                  --NJ_buffer_size 
 *                  --NJ_sample_rate 
 * @param error_callback - error callback
 * @param error_callback_arg - error callback argument
 * @param error - the error value to be filled
 * 
 * @return the remote DSP instance on success, otherwise a null pointer.
 */
remote_dsp* createRemoteDSPInstance(remote_dsp_factory* factory, 
                                    int argc, const char* argv[], 
                                    remoteDSPErrorCallback error_callback,
                                    void* error_callback_arg,
                                    int& error);

/**
 * Delete a Faust remote DSP instance. You can also simply use C++ 'delete'. 
 * 
 * @param dsp - the DSP instance to be deleted.
 */ 
void deleteRemoteDSPInstance(remote_dsp* dsp);

/**
 * Audio instance class. Use 'start/stop' to control audio instance on server side.
 */
class remote_audio {
    
    public: 
        
        /* Start remote audio instance rendering */
        bool start();
        
        /* Stop remote audio instance rendering */
        bool stop();
  
};

/**
 * Create a Faust remote audio instance.
 * 
 * @param factory - the DSP factory
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters 
 *                  --LA_buffer_size size
 *                  --LA_sample_rate rate
 *                  --osc <0/1>
 *                  --httpd <0/1>
 *                  --midi <0/1> 
 * @param error - the error value to be filled
 * 
 * @return the remote DSP instance on success, otherwise a null pointer.
 */
remote_audio* createRemoteAudioInstance(remote_dsp_factory* factory, int argc, const char* argv[], int& error);

/**
 * Delete a Faust remote Audio instance. You can also simply use C++ 'delete'.
 * 
 * @param audio - the Audio instance to be deleted.
 */ 
void deleteRemoteAudioInstance(remote_audio* audio);

/**
 * Remote machine instance class
 */
class remote_dsp_machine {
    
    public: 
        
        /* Return remote machine IP */
        std::string getIP();
        
        /* Return remote machine port */
        int getPort();
        
        /* Return remote machine LLVM target (something of the form : 'arm-apple-ios7.0:cortex-a9', to be used when cross-compiling) */
        std::string getTarget();
        
        static remote_dsp_machine* create(const std::string& ip, int port, const std::string& target);
        static void destroy(remote_dsp_machine* machine);
};

/**
 * Scan the network to find the available machines for Remote Compilation/Processing
 * @param machine_list - map to be filled with <machine_name, remote_dsp_machine>
 *
 * @return true if no error was encountered.
 */
bool getRemoteDSPMachines(std::map<std::string, remote_dsp_machine* >* machine_list);

/**
 * For a machine on the network that does Remote Compilation/Processing, get the list of all currently available DSP factories.
 * @param ip_server - IP of remote machine
 * @param port_server - port on which the Remote Server started
 * @param factories_list - vector to be filled with <factory_name, factory_sha_key>
 *
 * @return true if no error was encountered.
 */    
bool getRemoteDSPFactories(const std::string& ip_server, int port_server, std::vector<std::pair<std::string, std::string> >* factories_list);

 /**
 * DSP compilation service class : after being started, the server waits for compilation 
 * request from clients (delivered using the client API part). 
 * Each received DSP source will be compiled as a 'DSP factory'. Remote (= server side) 'DSP instances' 
 * will be created and connected to the client side using a NetJack master/slave connection.
 */
 
/* Called each time a new DSP factory is created */
typedef bool (*createFactoryDSPCallback) (dsp_factory* factory, void* arg);

/* Called each time a DSP factory is deleted */
typedef bool (*createInstanceDSPCallback) (dsp* dsp, void* arg);

/* Called each time a new DSP instance is created */
typedef bool (*deleteFactoryDSPCallback) (dsp_factory* factory, void* arg);

/* Called each time a DSP instance is deleted */
typedef bool (*deleteInstanceDSPCallback) (dsp* dsp, void* arg);

class remote_dsp_server {
    
    public: 
        
        bool start(int port = 7777); /* Start the DSP compilation service on a given port. */
        void stop();                 /* Stop the DSP compilation service. */
        
        void setCreateDSPFactoryCallback(createFactoryDSPCallback callback, void* callback_arg);
        void setDeleteDSPFactoryCallback(deleteFactoryDSPCallback callback, void* callback_arg);
        
        void setCreateDSPInstanceCallback(createInstanceDSPCallback callback, void* callback_arg);
        void setDeleteDSPInstanceCallback(deleteInstanceDSPCallback callback, void* callback_arg);
};

 /**
 * Create a Faust remote DSP server.
 *
 * @param argc - the number of parameters in argv array
 * @param argv - the array of parameters 
 *
 * @return the DSP server or NULL if allocation error.
 */ 
remote_dsp_server* createRemoteDSPServer(int argc, const char* argv[]);

/**
 * Delete a Faust remote DSP server. You can also simply use C++ 'delete'.
 * 
 * @param server - the DSP server to be deleted.
 */ 
void deleteRemoteDSPServer(remote_dsp_server* server);

#endif

