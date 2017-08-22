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
 
#ifndef _SERVER_h
#define _SERVER_h

#include <sstream>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <stdlib.h>
#include <list>
#include <map>
#include <vector>
#include <set>
#include <microhttpd.h>
#include <netdb.h>
#include <arpa/inet.h>

#define LLVM_DSP 1
/*
#define OSCCTRL 1
#define HTTPCTRL 1
#define MIDICTRL 1
#define NETJACK 1
*/

#ifdef LLVM_DSP_FACTORY
#include "llvm-dsp.h"
#else
#include "interpreter-dsp.h"
#endif

#include "faust/audio/audio.h"

#ifdef OSCCTRL
#include "faust/gui/OSCUI.h"
#endif

#ifdef HTTPCTRL
#include "faust/gui/httpdUI.h"
#endif

#ifdef MIDICTRL
#include "faust/gui/MidiUI.h"
#endif

#include "TMutex.h"

#define POSTBUFFERSIZE 512
#define GET 0
#define POST 1

#ifdef WIN32
    #define	EXPORT __declspec(dllexport)
#else
	#define	EXPORT __attribute__ ((visibility("default")))
#endif

using namespace std;

typedef bool (*createFactoryDSPCallback) (dsp_factory* factory, void* arg);
typedef bool (*createInstanceDSPCallback) (dsp* dsp, void* arg);
typedef bool (*deleteFactoryDSPCallback) (dsp_factory* factory, void* arg);
typedef bool (*deleteInstanceDSPCallback) (dsp* dsp, void* arg);

/*
TODO :

- possibly return 'machine code' to client side?
- better define where the DSP instance and the audio driver is going to run (server or client side) 

*/

// Structure wrapping llvm_dsp with all its needed elements (audio/interface/...)

class audio_dsp {

     protected:
     
        string fInstanceKey;
        string fName;
        
        dsp* fDSP;          // DSP Instance 
        audio* fAudio;      // Audio driver
    
    #ifdef OSCCTRL
        OSCUI* fOSCUI;      // OSC controler
    #endif
    
    #ifdef HTTPCTRL
        httpdUI* fHttpdUI;  // Httpd controler
    #endif
    
    #ifdef MIDICTRL
        MidiUI* fMidiUI;    // MIDIcontroler
    #endif
    
        createInstanceDSPCallback fCreateDSPInstanceCb;
        void* fCreateDSPInstanceCb_arg;
   
        deleteInstanceDSPCallback fDeleteDSPInstanceCb;
        void* fDeleteDSPInstanceCb_arg;
  
    public:
    
        audio_dsp(dsp_factory* factory, 
                bool poly, int voices, bool group, 
                bool osc, bool httpd, bool midi,
                const string& name, const string& key, 
                createInstanceDSPCallback cb1, void* cb1_arg,
                deleteInstanceDSPCallback cb2, void* cb2_arg);
        virtual ~audio_dsp();
          
        virtual bool init(int sr, int bs);
          
        virtual bool start()
        {
            return fAudio->start();
        }
        void stop()
        {
            fAudio->stop();
        }
       
        virtual bool isActive() { return true; }
        
        string  getKey() { return fInstanceKey; }
        void    setKey(const string& key) { fInstanceKey = key; }
        string  getName() { return fName; }
        void    setName(string name) { fName = name; }
         
};

// Structure handled by libmicrohttp related to a connection

enum {
    ERROR_FACTORY_NOTFOUND,
    ERROR_INSTANCE_NOTCREATED,
    ERROR_INSTANCE_NOTFOUND
};


typedef set<dsp_factory*> FactoryTable;  // TO CHECK
#define FactoryTableIt FactoryTable::iterator

class DSPServer;

struct dsp_server_connection_info {
    
    int fAnswercode;    // internally used by libmicrohttpd to see where things went wrong or right
    
    string fAnswer;     // the answer sent to the user after upload
    
    string fAudioType;  // audio driver type
    
    //-----DATAS RECEIVED TO CREATE NEW DSP FACTORY---------
    string fNameApp;
    string fFaustCode;
    string fTarget;
    vector<string> fCompilationOptions;
    string fOptLevel;
    
    //------DATAS RECEIVED TO CREATE NEW NetJack DSP INSTANCE-------
    string fIP;
    string fPort;
    string fCompression;
    string fMTU;
    string fLatency;
    string fSHAKey;
    string fInstanceKey;
    
    //------DATAS RECEIVED TO CREATE POLYPOHONIC -------
    string fPoly;
    string fVoices;
    string fGroup;
    
    //------DATAS RECEIVED TO CREATE NEW local Audio INSTANCE-------
    string fSampleRate;
    string fBufferSize;
    string fOSC;
    string fHTTPD;
    string fMIDI;
    
    dsp_server_connection_info();
    virtual ~dsp_server_connection_info() {}
    
    void getJson(dsp_factory* factory);
    bool getFactoryFromSHAKey(DSPServer* server);
    
    int iteratePost(const char* key, const char* data, size_t size); 
    
    dsp_factory* createFactory(DSPServer* server, string& error);
    dsp_factory* crossCompileFactory(DSPServer* server, string& error);
    
    virtual int postProcess(const char* upload_data, size_t* upload_data_size)
    {
        return MHD_NO;
    }
    
};

struct dsp_server_connection_info_post : public dsp_server_connection_info {

    MHD_PostProcessor* fPostprocessor;     // the POST processor used internally by libmicrohttpd
 
    dsp_server_connection_info_post(MHD_Connection* connection);
     
    virtual ~dsp_server_connection_info_post()
    {
        MHD_destroy_post_processor(fPostprocessor);
    }

    int postProcess(const char* upload_data, size_t* upload_data_size)
    {
        MHD_post_process(fPostprocessor, upload_data, *upload_data_size);
        *upload_data_size = 0;
        return MHD_YES;
    }
}; 

struct dsp_server_connection_info_get : public dsp_server_connection_info  {

    dsp_server_connection_info_get():dsp_server_connection_info()
    {}
}; 

// Same prototype LLVM/REMOTE DSP are using for allocation/desallocation

class DSPServer {
    
    friend struct dsp_server_connection_info_post;
    friend struct dsp_server_connection_info;
    
    private:
      
        createFactoryDSPCallback fCreateDSPFactoryCb;
        void* fCreateDSPFactoryCb_arg;
       
        deleteFactoryDSPCallback fDeleteDSPFactoryCb;
        void* fDeleteDSPFactoryCb_arg;
        
        createInstanceDSPCallback fCreateDSPInstanceCb;
        void* fCreateDSPInstanceCb_arg;
       
        deleteInstanceDSPCallback fDeleteDSPInstanceCb;
        void* fDeleteDSPInstanceCb_arg;

        TMutex fLocker;
        pthread_t fThread;
        int fPort;
        
        // Factories that can be instanciated. 
        // The remote client asking for a new DSP Instance has to send an SHA key corresponding to an existing factory
        FactoryTable fFactories;
            
        // List of currently running DSP. Use to keep track of Audio that would have lost their connection
        list<audio_dsp*> fRunningDsp;
        MHD_Daemon* fDaemon;    // Running http daemon
        
        void open(audio_dsp* dsp);
                
        // Creates the html to send back
        int sendPage(MHD_Connection* connection, const string& page, int status_code, const string& type);
            
        void stopNotActiveDSP();
            
        // Reaction to a GET request
        int answerGet(MHD_Connection* connection, const char* url);
            
        // Reaction to a POST request
        int answerPost(MHD_Connection* connection, const char* url, 
                        const char* upload_data, size_t* upload_data_size,
                        void** con_cls);
    
        // Reaction to a /CreateInstance request --> Creates llvm_dsp_instance & NetJack slave
        bool createInstance(dsp_server_connection_info* con_info);
        
        // Reaction to a /Delete request --> stops NetJack slave and delete object
        bool deleteInstance(const string& instance_key);
     
        int createConnection(MHD_Connection* connection, const char* method, void** con_cls);
        
        bool start(const string& instance_key);
        bool stop(const string& instance_key);
        
        bool getAvailableFactories(MHD_Connection* connection);
        
        bool getFactoryFromSHAKey(MHD_Connection* connection, dsp_server_connection_info* info);
        bool createFactory(MHD_Connection* connection, dsp_server_connection_info* info);
        
        bool createInstance(MHD_Connection* connection, dsp_server_connection_info* info);
        bool deleteInstance(MHD_Connection* connection, dsp_server_connection_info* info);
        
        bool start(MHD_Connection* connection, dsp_server_connection_info* info);
        bool stop(MHD_Connection* connection, dsp_server_connection_info* info);
        
        bool crossCompileFactory(MHD_Connection* connection, dsp_server_connection_info* info);
        
        bool deleteFactory(MHD_Connection* connection, dsp_server_connection_info* info);
        
        // Register Service as available
        static void* registration(void* arg);
       
        // Callback of another thread to wait netjack audio connection without blocking the server
        static void* open(void* arg);
   
        // Callback that processes the data send to the server
        static int iteratePost(void* coninfo_cls, MHD_ValueKind kind, const char* key, 
                                const char* filename, const char* content_type, 
                                const char* transfer_encoding, const char* data, 
                                uint64_t off, size_t size);
            
        static void requestCompleted(void* cls, MHD_Connection* connection, void** con_cls, MHD_RequestTerminationCode toe);
        
        // Reaction to any kind of connection to the Server
        static int answerToConnection(void* cls, MHD_Connection* connection, 
                                        const char* url, const char* method, 
                                        const char* version, const char* upload_data, 
                                        size_t* upload_data_size, void** con_cls);
    
    public:
            
        DSPServer(int argc, const char* argv[]);
        virtual ~DSPServer();
            
        // Start server on specified port 
        bool start(int port = 7777);
        void stop();
        
        void setCreateDSPFactoryCallback(createFactoryDSPCallback callback, void* callback_arg)
        {
            fCreateDSPFactoryCb = callback;
            fCreateDSPFactoryCb_arg = callback_arg;
        }
        void setDeleteDSPFactoryCallback(deleteFactoryDSPCallback callback, void* callback_arg)
        {
            fDeleteDSPFactoryCb = callback;
            fDeleteDSPFactoryCb_arg = callback_arg;
        }
        
        void setCreateDSPInstanceCallback(createInstanceDSPCallback callback, void* callback_arg)
        {
            fCreateDSPInstanceCb = callback;
            fCreateDSPInstanceCb_arg = callback_arg;
        }
        void setDeleteDSPInstanceCallback(deleteInstanceDSPCallback callback, void* callback_arg)
        {
            fDeleteDSPInstanceCb = callback;
            fDeleteDSPInstanceCb_arg = callback_arg;
        }
     
};

// Helper class

struct AudioStarter {
    
    DSPServer* fServer;
    audio_dsp* fDSP;
    
    AudioStarter(DSPServer* server, audio_dsp* dsp):fServer(server),fDSP(dsp)
    {}
  
};

// Public C++ API

class EXPORT remote_dsp_server {
    
    public: 
        
        bool start(int port = 7777);
        void stop();
        
        void setCreateDSPFactoryCallback(createFactoryDSPCallback callback, void* callback_arg);
        void setDeleteDSPFactoryCallback(deleteFactoryDSPCallback callback, void* callback_arg);
        
        void setCreateDSPInstanceCallback(createInstanceDSPCallback callback, void* callback_arg);
        void setDeleteDSPInstanceCallback(deleteInstanceDSPCallback callback, void* callback_arg);
      
};

EXPORT remote_dsp_server* createRemoteDSPServer(int argc, const char* argv[]);

EXPORT void deleteRemoteDSPServer(remote_dsp_server* compiler);
    
#endif
    
