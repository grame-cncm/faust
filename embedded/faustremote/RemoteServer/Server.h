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

#include "faust/audio/netjack-dsp.h"
#include "llvm-dsp.h"
#include "utilities.h"
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

class netjackaudio_slave : public netjackaudio_midicontrol {  

    private:

        int fNumberRestartAttempts;

    public:
    
        netjackaudio_slave(int celt, const std::string& master_ip, int master_port, int mtu, int latency)
            :netjackaudio_midicontrol(celt, master_ip, master_port, mtu, latency)
        {
            fNumberRestartAttempts = 0;
        }
        
        void error_cb(int error_code)
        {
            switch (error_code) {
            
                case SOCKET_ERROR:
                    printf("NetJack : SOCKET_ERROR\n");
                    break;
                    
                case SYNC_PACKET_ERROR:
                    printf("NetJack : SYNC_PACKET_ERROR\n");
                    break;

                 case DATA_PACKET_ERROR:
                    printf("NetJack : DATA_PACKET_ERROR\n");
                    break;
            }
        }
    
        /*
        virtual int restart_cb()
        {
            printf("NetJack : restart_cb\n");
            return 0;
        }
        */

};

// Structure wrapping llvm_dsp with all its needed elements (audio/interface/...)

class audio_dsp {

     protected:
     
        string fInstanceKey;
        string fName;
        
        llvm_dsp* fDSP; // DSP Instance 
        audio* fAudio;
  
    public:
    
        audio_dsp(llvm_dsp_factory* factory, const string& name, const string& key)
            :fName(name), fInstanceKey(key), fAudio(NULL)
        {
            if (!(fDSP = createDSPInstance(factory))) {
                throw -1;
            }
        }
         
        virtual ~audio_dsp()
        {   
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
       
        virtual bool init() = 0;
        virtual bool isActive() = 0;
        
        string  getKey() { return fInstanceKey; }
        void    setKey(const string& key) { fInstanceKey = key; }
        string  getName() { return fName; }
        void    setName(string name) { fName = name; }
        
};

// NetJack slave client

class netjack_dsp : public audio_dsp {

    private: 
        
        // NetJack parameters
        string fIP;
        string fPort;
        string fCompression;
        string fMTU;
        string fLatency;
     
    public:
    
        netjack_dsp(llvm_dsp_factory* factory, 
                    const string& compression, 
                    const string& ip, const string& port, 
                    const string& mtu, const string& latency,
                    const string& name, const string& key);
        
        bool init();
       
        bool isActive() { return dynamic_cast<netjackaudio_slave*>(fAudio)->is_connexion_active(); }

};

// Local CoreAudio client

#ifdef COREAUDIO

class coreaudio_dsp : public audio_dsp {

    public:
     
        coreaudio_dsp(llvm_dsp_factory* factory, const string& name, const string& key)
            :audio_dsp(factory, name, key)
        {}
        
        virtual ~coreaudio_dsp() {}
        
        bool init();
        
        bool isActive() { return true; }
        
};

#endif

// Structure handled by libmicrohttp related to a connection

enum {
    ERROR_FACTORY_NOTFOUND,
    ERROR_INSTANCE_NOTCREATED
};

typedef map<string, pair<string, llvm_dsp_factory*> >& FactoryTable;

struct connection_info {
    
    int fAnswercode;        // used internally by microhttpd to see where things went wrong or right
    
    std::string fAnswer;    // the answer sent to the user after upload
    
    //-----DATAS RECEIVED TO CREATE NEW DSP FACTORY---------
    string fNameApp;
    string fFaustCode;
    string fFactoryKey;
    vector<string> fCompilationOptions;
    string fOptLevel;
    llvm_dsp_factory* fFactory;
    //---------------------------------------------
    
    //------DATAS RECEIVED TO CREATE NEW DSP INSTANCE-------
    string fIP;
    string fPort;
    string fCompression;
    string fMTU;
    string fLatency;
    string fSHAKey;
    string  fInstanceKey;
    //--------------------------------------------- 
    
    connection_info();
    virtual ~connection_info() {}
    
    string getJson();
    bool getJsonFromKey(FactoryTable& factories);
    
    int iteratePost(const char* key, const char* data, size_t size); 
    
    bool createFactory(FactoryTable factories);
    
    virtual int postProcess(const char* upload_data, size_t* upload_data_size)
    {
        return MHD_NO;
    }
    
};

struct connection_info_post : public connection_info {

    MHD_PostProcessor* fPostprocessor;     // the POST processor used internally by microhttpd
 
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

// Same prototype LLVM/REMOTE dsp are using for allocation/desallocation

class DSPServer {
    
    friend struct connection_info_post;
    
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
        MHD_Daemon* fDaemon; //Running http daemon
        
        void openAudio(audio_dsp* dsp);
                
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
        
        bool startAudio(const string& shakey);
        void stopAudio(const string& shakey);
        
        int createConnection(MHD_Connection* connection, const char* method, void** con_cls);
        
        // Register Service as available
        static void* registration(void* arg);
       
        // Callback of another thread to wait netjack audio connection without blocking the server
        static void* openAudio(void* arg);
   
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
        
        bool start(int port);
        void stop();
};

EXPORT remote_dsp_server* createRemoteDSPServer(int argc, const char* argv[]);

EXPORT void deleteRemoteDSPServer(remote_dsp_server* compiler);
    
#endif
    
    
    
    
