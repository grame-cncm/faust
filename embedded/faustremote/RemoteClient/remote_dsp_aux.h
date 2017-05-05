/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2003-2015 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#ifndef remote_dsp_aux__h
#define remote_dsp_aux__h

#include <string>
#include <vector>
#include <map>
#include <list>
#include <assert.h>
#include <curl/curl.h>
#include <sstream>
#include <iostream>
#include <fstream> 

#include "faust/gui/MapUI.h"
#include "faust/gui/meta.h"
#include "faust/dsp/dsp.h"
#include "faust/dsp/proxy-dsp.h"
#include "faust/midi/jack-midi.h"
#include "smartpointer.h"
#include "lo/lo.h"
#include "TMutex.h"

#include <jack/net.h>

#ifdef WIN32
	#define	EXPORT __declspec(dllexport)
#else
	#define	EXPORT __attribute__ ((visibility("default")))
#endif

#define LocalFactoryDSPTableType list<llvm_dsp_factory*>
#define LocalFactoryDSPTableIt   LocalFactoryDSPTableType::iterator

#define RemoteFactoryDSPTable     pair<list<remote_dsp_aux*>, list<remote_audio_aux*> >
#define RemoteFactoryDSPTableType map<Sremote_dsp_factory, RemoteFactoryDSPTable>
#define RemoteFactoryDSPTableIt   RemoteFactoryDSPTableType::iterator

using namespace std;

class llvm_dsp_factory;

enum {
    ERROR_FACTORY_NOTFOUND,
    ERROR_INSTANCE_NOTCREATED,
    ERROR_NETJACK_NOTSTARTED,
    ERROR_NETJACK_READ,
    ERROR_NETJACK_WRITE,
    ERROR_CURL_CONNECTION
};

// To be used as a singleton 

struct remote_DNS {

    struct member {
        int pid;
        string hostname;
        lo_timetag timetag;
        
        member() 
        {
            pid = 0;
            hostname = "";
            timetag.sec = 0;
            timetag.frac = 0;
        }
    };
   
    lo_server_thread fLoThread;
    map<string, member> fClients;
    TMutex fLocker;
      
    static void errorHandler(int num, const char* m, const char* path);
    
    static int pingHandler(const char* path, const char* types, lo_arg** argv,
                           int argc, void* data, void* user_data);
   
    remote_DNS();
    virtual ~remote_DNS();
    
};

typedef int (*remoteDSPErrorCallback) (int error_code, void* arg);

class remote_dsp_aux;
class remote_audio_aux;
class remote_dsp_factory;

typedef class SMARTP<remote_dsp_factory> Sremote_dsp_factory;

// The proxy DSP factory 
    
class remote_dsp_factory : public smartable {

    friend class remote_dsp_aux;
    
    private:
        
        string fSHAKey;                // Unique Index to bind a Remote_Factory to its llvm_factory on the server side
        string fExpandedDSP;
        string fServerURL;             // URL of remote server 
        string fPoly; 
        string fVoices; 
        string fGroup; 
        
        JSONUIDecoder* fJSONDecoder;
        
        vector<string> fPathnameList;
           
    public: 
    
        remote_dsp_factory(const string& ip_server, int port_server, const string& sha_key);
        virtual ~remote_dsp_factory();
        
        void decodeJSON(const string& json);
        
        remote_dsp_aux* createRemoteDSPInstance(int argc, const char* argv[],
                                                remoteDSPErrorCallback error_callback, 
                                                void* error_callback_arg, int& error);
                                                
        remote_audio_aux* createRemoteAudioInstance(int argc, const char* argv[], int& error);
        
        bool init(int argc, const char* argv[],
                        const string& name_app, 
                        const string& dsp_content, 
                        string& error_msg, 
                        int opt_level);
        
        void metadataRemoteDSPFactory(Meta* m);  
        
        string getURL() { return fServerURL; }
        
        string getName();
        string getSHAKey();
        string getDSPCode();
        string getPoly();
        string getVoices();
        string getGroup();
        
        vector<string> getRemoteDSPFactoryLibraryList() { return fPathnameList; }
        bool sendFinalRequest(void* obj, const string& cmd);
        
        static LocalFactoryDSPTableType gLocalFactoryDSPTable;
        static RemoteFactoryDSPTableType gRemoteFactoryDSPTable;
        static CURL* gCurl;
        static remote_DNS* gDNS;
     
};

// The proxy DSP instance 

class remote_dsp_aux : public dsp, public jack_midi_handler {
    
    private:
        
        int                     fBufferSize;        // Buffer size of NetJack connection
        int                     fSampleRate;        // Sample rate of NetJack connection
        
        remote_dsp_factory*     fFactory;           // Factory it is created from
        
        jack_net_master_t*      fNetJack;           // NetJack Connection
        
        float**                 fAudioInputs;       // Audio buffer
        float**                 fAudioOutputs;      // Audio buffer
        
        float**                 fControlInputs;     // control buffer
        float**                 fControlOutputs;    // control buffer
         
        remoteDSPErrorCallback  fErrorCallback;
        void*                   fErrorCallbackArg;
        
        bool                    fRunning;
        
        JSONUIDecoder*          fJSONDecoder;
        
        void fillBufferWithZerosOffset(int channels, int offset, int size, FAUSTFLOAT** buffer);
        void setupBuffers(FAUSTFLOAT** input, FAUSTFLOAT** output, int offset);
        
        void sendSlice(int buffer_size);
        void recvSlice(int buffer_size);
        
    public:   
        
        remote_dsp_aux(remote_dsp_factory* factory);
        virtual ~remote_dsp_aux();
        
        bool init(int argc, const char* argv[], 
                remoteDSPErrorCallback errror_callback, 
                void* errror_callback_arg, int& error);
        
        virtual int getNumInputs();
    
        virtual int getNumOutputs();
    
        virtual void buildUserInterface(UI* ui);
    
        virtual int getSampleRate();
        
        virtual void init(int samplingRate);
    
        virtual void instanceInit(int samplingRate);
    
        virtual void instanceConstants(int samplingRate);
    
        virtual void instanceResetUserInterface();
    
        virtual void instanceClear();
    
        virtual dsp* clone();
    
        virtual void metadata(Meta* m);
    
        virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
  
        remote_dsp_factory* getFactory() { return fFactory; }
};

// The proxy audio instance 

class remote_audio_aux {
    
    private:
    
         remote_dsp_factory* fFactory;
         
    public:
    
        remote_audio_aux(remote_dsp_factory* factory);
        virtual ~remote_audio_aux();
        
        bool init(int argc, const char* argv[], int& error);
        
        remote_dsp_factory* getFactory() { return fFactory; }

        bool start();
        bool stop();
};


// The proxy machine 

class remote_dsp_machine_aux {

    private:
    
        string fIP;
        int fPort;
        string fTarget;
    
    public: 
    
        remote_dsp_machine_aux(const string& ip, int port, const string& target)
            :fIP(ip), fPort(port), fTarget(target)
        {}
        virtual ~remote_dsp_machine_aux() {}
        
        string getIP() { return fIP; }
        int getPort() { return fPort; }
        string getTarget() { return fTarget; }
};

//---------------------- Public C++ interface --------

class EXPORT remote_dsp : public dsp, public midi {
    
    public: 
        
        int getNumInputs();
    
        int getNumOutputs();
    
        void buildUserInterface(UI* ui);
        
        void init(int samplingFreq);
    
        void instanceInit(int samplingRate);
    
        void instanceConstants(int samplingRate);
    
        void instanceResetUserInterface();
    
        void instanceClear();
    
        dsp* clone();
    
        void metadata(Meta* m);
    
        int getSampleRate();
    
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

class EXPORT remote_audio {
    
    public: 
        
        bool start();
        bool stop();
         
};

class EXPORT remote_dsp_machine {
    
    public: 
        
        std::string getIP();
        int getPort();
        std::string getTarget();
        
        static remote_dsp_machine* create(const std::string& ip, int port, const std::string& target);
        static void destroy(remote_dsp_machine* machine);
        
};

// Factories
    
EXPORT remote_dsp_factory* getRemoteDSPFactoryFromSHAKey(const string& sha_key, const string& ip_server, int port_server);  

EXPORT remote_dsp_factory* createRemoteDSPFactoryFromFile(const string& filename, int argc, const char* argv[], 
                                                        const string& ip_server, int port_server, 
                                                        string& error_msg, int opt_level = -1);

EXPORT remote_dsp_factory* createRemoteDSPFactoryFromString(const string& name_app, const string& dsp_content, 
                                                            int argc, const char* argv[], 
                                                            const string& ip_server, int port_server, 
                                                            string& error, int opt_level = -1);

EXPORT bool deleteRemoteDSPFactory(remote_dsp_factory* factory);

EXPORT void deleteAllRemoteDSPFactories();    

EXPORT void metadataRemoteDSPFactory(remote_dsp_factory* factory, Meta* m);

EXPORT vector<string> getRemoteDSPFactoryLibraryList(remote_dsp_factory* factory);

// DSP instance

EXPORT remote_dsp* createRemoteDSPInstance(remote_dsp_factory* factory, 
                                           int argc, const char* argv[],
                                           remoteDSPErrorCallback error_callback,
                                           void* errror_callback_arg,
                                           int& error);

EXPORT void deleteRemoteDSPInstance(remote_dsp* dsp);

// Audio instance

EXPORT remote_audio* createRemoteAudioInstance(remote_dsp_factory* factory, 
                                                int argc, const char* argv[],  
                                                int& error);

EXPORT void deleteRemoteAudioInstance(remote_audio* audio);

// Remote machine access
 
EXPORT bool getRemoteDSPMachines(map<string, remote_dsp_machine* >* machine_list);

EXPORT bool getRemoteDSPFactories(const string& ip_server, int port_server, vector<pair<string, string> >* factories_list);

#endif
