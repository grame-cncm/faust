//
//  Server.h
//  
//
//  Created by Sarah Denoux on 13/05/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//
//
// FaustLive can become a server.

#ifndef _SERVER_h
#define _SERVER_h

#include <sstream>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <stdlib.h>

#include <microhttpd.h>
#include <pthread.h>

#include <map>

#include <boost/wave/util/cpp_include_paths.hpp>

namespace fs = boost::filesystem;

#include "faust/audio/netjack-dsp.h"
#include "faust/llvm-dsp.h"
#include "TMutex.h"

class Server;

using namespace std;

struct connection_info_struct {
    
    int              connectiontype; // GET or POST
    
    MHD_PostProcessor *postprocessor; // the POST processor used internally by microhttpd
    int             answercode; // used internally by microhttpd to see where things went wrong or right
    
    MHD_Connection*     connection;
    
    std::string     answerstring; // the answer sent to the user after upload
    
//-----DATAS TO CREATE NEW DSP FACTORY---------
    string          data;
    string          compilationOptions;
    string          opt_level;
//---------------------------------------------
    
    
//------DATAS TO CREATE NEW DSP INSTANCE-------
    string          IP;
    string          Port;
    string          CV;
    string          Latency;
    string          factoryIndex;
//--------------------------------------------- 
    
    void init(){
        data = "";
        compilationOptions = "";
        
        IP = "";
        Port = "";
        CV = "";
        Latency = "";
    }
};

struct Slave_DSP_Factory{
    
    string              nameApp;
    llvm_dsp_factory*   factory;
    
    int                 numInstances;
    
    bool delete_Factory(){
                    
        numInstances--;
        
        if(numInstances == 0){        
            printf("DELETE FACTORY NAME = %s\n", nameApp.c_str());
            deleteDSPFactory(factory);
            return true;
        }
        else{
            printf("DELETE FACTORY %s || Instances = %i\n", nameApp.c_str(), numInstances);
            return false;
        }
    }
    
    Slave_DSP_Factory* clone(){
        
        numInstances++;
        printf("ADD INSTANCE = %i\n", numInstances);
        return this;
    }
    
    void init(){
        numInstances = 1;
    }
    
};

Slave_DSP_Factory* createSlaveFactory();
void deleteSlaveFactory(Slave_DSP_Factory* smartPtr);

struct Slave_DSP{
    
    string          IP;
    string          Port;
    string          CV;
    string          Latency;
    
    netjackaudio_control*   audio;
    
    llvm_dsp*       myDSP;
    ControlUI*      controlUI;
    
//To be sure not access the same resources at the same time, the mutex of the server has to be accessible here;
    Server*         server;
    
    Slave_DSP_Factory*   factory;
    
    void delete_DSP(){
        
        printf("DELETING AUDIO %s\n", factory->nameApp.c_str());
        
        audio->stop();
        
        delete audio;
        delete controlUI;
        deleteDSPInstance(myDSP);
        deleteSlaveFactory(factory);
        
    }
    
    void init(){
        IP = "";
        Port = "";
        CV = "";
        Latency = "";
        
        audio = NULL;
        
        myDSP = NULL;
        controlUI = NULL;
    }
};

Slave_DSP* createSlaveInstance(Slave_DSP_Factory* smartFactory);
void deleteSlaveInstance(Slave_DSP* smartPtr);

class Server{
    
    int             fMax_clients;
    string          fError;
    
    list<pair<MHD_Connection*, connection_info_struct*> > fConnections;
    
    public :

    TMutex          fLocker;
    
    
    map<int, Slave_DSP_Factory*>         fAvailableFactories;
    list<Slave_DSP*>          fRunningDsp;
    
//    static int      fNr_of_uploading_clients;
    
    struct          MHD_Daemon* fDaemon;
    
                    Server();
                    ~Server();
    
    const int       getMaxClients();
    
    bool            start(int port = 7777);
    void            stop();

    static void*        start_audioSlave(void *);
    static void         stop_audioSlave(void *);
    
    int                 getSmallestIndexAvailable();
    Slave_DSP_Factory*   getFactoryFromIndex(int factoryIndex);
    
    bool                createInstance(connection_info_struct* con_info);
    
    int             send_page(MHD_Connection *connection, const char *page, int length, int status_code, const char * type = 0);
    
    static int      answer_to_connection	(void *cls, MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls);
    
    int             answer_get(MHD_Connection* connection);
    
    int             answer_post(MHD_Connection *connection, const char *url, const char *upload_data, size_t *upload_data_size, void **con_cls);
    
    static void request_completed(void *cls, MHD_Connection *connection, void **con_cls, MHD_RequestTerminationCode toe);
    
    static int iterate_post(void *coninfo_cls, MHD_ValueKind kind, const char *key, const char *filename, const char *content_type, const char *transfer_encoding, const char *data, uint64_t off, size_t size);
    
    bool        compile_Data(connection_info_struct* con_info);
  
    int         get_numberParameters(string compilOptions);
    string     parse_compilationParams(string& compilOptions);
};

#endif




