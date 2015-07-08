//
//  Server.h
//
//  Created by Sarah Denoux on 13/05/13.
//  Copyright (c) 2013 GRAME. All rights reserved.
//

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
#include <microhttpd.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "llvm-dsp.h"
#include "utilities.h"
#include "TMutex.h"

#include "faust/audio/audio.h"

#define POSTBUFFERSIZE 512
#define GET 0
#define POST 1

#ifdef WIN32
    #define	EXPORT __declspec(dllexport)
#else
	#define	EXPORT __attribute__ ((visibility("default")))
#endif

using namespace std;

typedef bool (*createFactoryDSPCallback) (llvm_dsp_factory* factory, void* arg);
typedef bool (*createInstanceDSPCallback) (llvm_dsp* dsp, void* arg);
typedef bool (*deleteFactoryDSPCallback) (llvm_dsp_factory* factory, void* arg);
typedef bool (*deleteInstanceDSPCallback) (llvm_dsp* dsp, void* arg);

// Structure wrapping llvm_dsp with all its needed elements (audio/interface/...)

class audio_dsp {

     protected:
     
        string fInstanceKey;
        string fName;
        
        llvm_dsp* fDSP; // DSP Instance 
        audio* fAudio;
        
        createInstanceDSPCallback fCreateDSPInstanceCb;
        void* fCreateDSPInstanceCb_arg;
   
        deleteInstanceDSPCallback fDeleteDSPInstanceCb;
        void* fDeleteDSPInstanceCb_arg;
  
    public:
    
        audio_dsp(llvm_dsp_factory* factory, const string& name, const string& key, 
            createInstanceDSPCallback cb1, void* cb1_arg,
            deleteInstanceDSPCallback cb2, void* cb2_arg)
            :fName(name), fInstanceKey(key), fAudio(NULL), 
            fCreateDSPInstanceCb(cb1), fCreateDSPInstanceCb_arg(cb1_arg),
            fDeleteDSPInstanceCb(cb2), fDeleteDSPInstanceCb_arg(cb2_arg)
        {
            if (!(fDSP = createDSPInstance(factory))) {
                throw -1;
            }
            
            if (fCreateDSPInstanceCb) {
                fCreateDSPInstanceCb(fDSP, fCreateDSPInstanceCb_arg);
            }
        }
         
        virtual ~audio_dsp()
        {   
            if (fDeleteDSPInstanceCb) {
                fDeleteDSPInstanceCb(fDSP, fDeleteDSPInstanceCb_arg);
            }
            
            delete fAudio;
            deleteDSPInstance(fDSP);
        }
        
        virtual bool start()
        {
            return fAudio->start();
        }
        void stop()
        {
            fAudio->stop();
        }
       
        virtual bool init(int sr, int bs) = 0;
        virtual bool isActive() = 0;
        
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

typedef map<string, pair<string, llvm_dsp_factory*> >& FactoryTable;

class DSPServer;

struct connection_info {
    
    int fAnswercode;    // internally used by libmicrohttpd to see where things went wrong or right
    
    string fAnswer;     // the answer sent to the user after upload
    
    string fAudioType;   // type of audio driver
    
    //-----DATAS RECEIVED TO CREATE NEW DSP FACTORY---------
    string fNameApp;
    string fFaustCode;
    string fFactoryKey;
    vector<string> fCompilationOptions;
    string fOptLevel;
    llvm_dsp_factory* fFactory;
    
    //------DATAS RECEIVED TO CREATE NEW NetJack DSP INSTANCE-------
    string fIP;
    string fPort;
    string fCompression;
    string fMTU;
    string fLatency;
    string fSHAKey;
    string fInstanceKey;
    
    //------DATAS RECEIVED TO CREATE NEW local Audio INSTANCE-------
    string fSampleRate;
    string fBufferSize;
    
    connection_info();
    virtual ~connection_info() {}
    
    string getJson();
    bool getJsonFromKey(FactoryTable& factories);
    
    int iteratePost(const char* key, const char* data, size_t size); 
    
    bool createFactory(FactoryTable factories, DSPServer* server);
    
    virtual int postProcess(const char* upload_data, size_t* upload_data_size)
    {
        return MHD_NO;
    }
    
};

struct connection_info_post : public connection_info {

    MHD_PostProcessor* fPostprocessor;     // the POST processor used internally by libmicrohttpd
 
    connection_info_post(MHD_Connection* connection);
     
    virtual ~connection_info_post()
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

struct connection_info_get : public connection_info  {

    connection_info_get():connection_info()
    {}
}; 

// Same prototype LLVM/REMOTE DSP are using for allocation/desallocation

class DSPServer {
    
    friend struct connection_info_post;
    friend struct connection_info;
    
    createFactoryDSPCallback fCreateDSPFactoryCb;
    void* fCreateDSPFactoryCb_arg;
   
    deleteFactoryDSPCallback fDeleteDSPFactoryCb;
    void* fDeleteDSPFactoryCb_arg;
    
    createInstanceDSPCallback fCreateDSPInstanceCb;
    void* fCreateDSPInstanceCb_arg;
   
    deleteInstanceDSPCallback fDeleteDSPInstanceCb;
    void* fDeleteDSPInstanceCb_arg;
    
    private:

        TMutex fLocker;
        pthread_t fThread;
        int fPort;
        
        // Factories that can be instanciated. 
        // The remote client asking for a new DSP Instance has to send an index corresponding to an existing factory
        // SHAKey, pair<NameApp, Factory>
        map<string, pair<string, llvm_dsp_factory*> > fFactories;
            
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
                                    const char* upload_data, size_t *upload_data_size, 
                                    void** con_cls);
            
        // Reaction to a /CreateInstance request --> Creates llvm_dsp_instance & netjack slave
        bool createInstance(connection_info* con_info);
         
        int createConnection(MHD_Connection* connection, const char* method, void** con_cls);
        
        bool start(const string& shakey);
        bool stop(const string& shakey);
        
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
    
    
    
    
