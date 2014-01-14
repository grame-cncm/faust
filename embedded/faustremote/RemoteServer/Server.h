//
//  Server.h
//  
//
//  Created by Sarah Denoux on 13/05/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef _SERVER_h
#define _SERVER_h

#include <sstream>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <stdlib.h>
#include <list>

#include <microhttpd.h>
#include <pthread.h>

#include <map>

#include <dns_sd.h>

#include "faust/audio/netjack-dsp.h"
#include "faust/llvm-dsp.h"
#include "TMutex.h"

#define POSTBUFFERSIZE 512

#define GET 0
#define POST 1

class Server;

using namespace std;

// Structured handled by libmicrohttp related to a connection
struct connection_info_struct {
    
    int                 fConnectiontype;    // GET or POST
    
    MHD_PostProcessor*  fPostprocessor;   // the POST processor used internally by microhttpd
    int                 fAnswercode;         // used internally by microhttpd to see where things went wrong or right
    
    std::string         fAnswerstring;      // the answer sent to the user after upload
    
    //-----DATAS RECEIVED TO CREATE NEW DSP FACTORY---------
    string              fNameApp;
    string              fFaustCode;
    int                 fNumCompilOptions;
    int                 fIndicator;
    string*             fCompilationOptions;
    string              fOpt_level;
    //---------------------------------------------
    
    
    //------DATAS RECEIVED TO CREATE NEW DSP INSTANCE-------
    string              fIP;
    string              fPort;
    string              fCV;
    string              fMTU;
    string              fLatency;
    string              fFactoryIndex;
    //--------------------------------------------- 
    
    void init(){
        
        fFaustCode = "";
        fNumCompilOptions = 0;
        fOpt_level = "";
        
        fIP = "";
        fPort = "";
        fCV = "";
        fMTU = "";
        fLatency = "";
        fFactoryIndex = "";
    }
};
    
#include <netdb.h>
#include <arpa/inet.h>

string searchIP();

// Structure wrapping llvm_dsp_factory
// Instances of this factory are counted so that desallocation is ensured 
// when no more instances are running
struct slave_dsp_factory{
    
    string              fNameApp;
    llvm_dsp_factory*   fLLVMFactory;
    
    int                 fNumInstances;
    
    bool delete_Factory();
    slave_dsp_factory* clone();
    bool init(int argc, const char** argv, const string& nameApp, string faustContent, int opt_level, int factoryIndex,  string& answer);
    
};
    
// Same Prototype LLVM/REMOTE dsp are using for allocation/desallocation
slave_dsp_factory* createSlaveDSPFactory(int argc, const char** argv, const string& nameApp, string faustContent, int opt_level, int factoryIndex,  string& answer);
void deleteSlaveDSPFactory(slave_dsp_factory* smartPtr);
    
// Structure wrapping llvm_dsp with all its needed elements (audio/interface/...)
//
struct slave_dsp{
        
    //    NETJACK PARAMETERS
    string          fIP;
    string          fPort;
    string          fCV;
    string          fMTU;
    string          fLatency;
    
    netjackaudio_control*   fAudio;  //NETJACK SLAVE 
    
    llvm_dsp*               fDSP;          //Real DSP Instance 
    
    slave_dsp_factory*      fSlaveFactory;   //RelatedFactory
    
    //To be sure not access the same resources at the same time, the mutex of the server has to be accessible here
    //So that the server himself is kept
    Server*         fServer;
    
    slave_dsp(slave_dsp_factory* smartFactory, const string& compression, const string& ip, const string& port, const string& mtu, const string& latency, Server* server);
    ~slave_dsp();
};
    
// Same Prototype LLVM/REMOTE dsp are using for allocation/desallocation
slave_dsp* createSlaveDSPInstance(slave_dsp_factory* smartFactory, const string& compression, const string& ip, const string& port, const string& mtu, const string& latency, Server* server);
void deleteSlaveDSPInstance(slave_dsp* smartPtr);
    
class Server{
        
    string          fError;
        
    list<pair<MHD_Connection*, connection_info_struct*> > fConnections;
        
public :
        
    Server();
    ~Server();
        
    TMutex          fLocker;
        
// Factories that can be instanciated. 
// The remote client asking for a new DSP Instance has to send an index corresponding to an existing factory
    map<int, slave_dsp_factory*>         fAvailableFactories;
        
// List of Dsp Currently Running. Use to keep track of Audio that would have lost their connection
    list<slave_dsp*>          fRunningDsp;
        
    struct          MHD_Daemon* fDaemon; //Running http daemon
        
    DNSServiceRef*      fRegistrationService;
    int             fPort; //Port on which server started
    
//  Start server on specified port 
    bool            start(int port = 7777);
    void            stop();
        
// Callback of another thread to wait netjack audio connection without blocking the server
    static void*        start_audioSlave(void *);
        
// A new factory is indexed with the smallest index available
    int                 getSmallestIndexAvailable();
        
// Creates the html to send back
    int             send_page(MHD_Connection *connection, const char *page, int length, int status_code, const char * type = 0);
        
    void            stop_NotActive_DSP();
        
    connection_info_struct* allocate_connection_struct(MHD_Connection *connection, const char *method);
        
// Reaction to any kind of connection to the Server
    static int      answer_to_connection	(void *cls, MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls);
        
        
// Reaction to a GET request
    int             answer_get(MHD_Connection* connection);
        
// Reaction to a POST request
    int             answer_post(MHD_Connection *connection, const char *url, const char *upload_data, size_t *upload_data_size, void **con_cls);
        
// Callback that processes the data send to the server
    static int iterate_post(void *coninfo_cls, MHD_ValueKind kind, const char *key, const char *filename, const char *content_type, const char *transfer_encoding, const char *data, uint64_t off, size_t size);
        
    static void request_completed(void *cls, MHD_Connection *connection, void **con_cls, MHD_RequestTerminationCode toe);
        
// Reaction to a /GetJson request --> Creates llvm_dsp_factory & json interface
    bool        compile_Data(connection_info_struct* con_info);
        
// Reaction to a /CreateInstance request --> Creates llvm_dsp_instance & netjack slave
    bool                createInstance(connection_info_struct* con_info);
    
// Register Service as Available
    bool            registration(DNSServiceRef* reg);
};
    
#endif
    
    
    
    
