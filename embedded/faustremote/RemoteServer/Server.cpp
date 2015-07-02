//
//  Server.cpp
//
//  Created by Sarah Denoux on 13/05/13.
//  Copyright (c) 2013 GRAME. All rights reserved.
//
//

#include "Server.h"
#include "utilities.h"
#include "faust/gui/meta.h"
#include "faust/gui/JSONUI.h"
#ifdef COREAUDIO
#include "faust/audio/coreaudio-dsp.h"
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <openssl/sha.h>

#ifdef __APPLE__
#include <dns_sd.h>
#endif

// Declare is called for every metadata coded in the Faust DSP
// That way, we get the faust name declared in the Faust DSP
struct myMeta : public Meta
{
    string name;
    
    virtual void declare(const char* key, const char* value) {
        if (strcmp(key, "name") == 0) {
            name = value;
        }
    }
};

static string builtError(int error)
{
    stringstream s; s << error;
    return s.str();
}

//--------------SLAVE DSP INSTANCE-----------------------------

netjack_dsp::netjack_dsp(llvm_dsp_factory* factory, 
                        const string& compression, 
                        const string& ip, 
                        const string& port, 
                        const string& mtu, 
                        const string& latency,
                        const string& name,
                        const string& key)
                        : audio_dsp(factory, name, key), fIP(ip), 
                        fPort(port), fCompression(compression), 
                        fMTU(mtu), fLatency(latency)
{}

bool netjack_dsp::init()
{
    fAudio = new netjackaudio_slave(atoi(fCompression.c_str()), 
                                    fIP, 
                                    atoi(fPort.c_str()), 
                                    atoi(fMTU.c_str()), 
                                    atoi(fLatency.c_str()));
                                        
    if (!fAudio->init(fName.c_str(), fDSP)) {
        printf("netjack_dsp : init slave audio failed\n");
        return false;
    } else {
        return true;
    }
}

#ifdef COREAUDIO

bool coreaudio_dsp::init()
{
    fAudio = new coreaudio(44100, 512);
    
    if (!fAudio->init(fName.c_str(), fDSP)) {
        printf("coreaudio_dsp : init audio failed\n");
        return false;
    } else {
        return true;
    }
}

#endif

//------------ CONNECTION INFO -------------------------------

connection_info::connection_info() 
{   
    fAnswercode = -1;
    fAnswer = "";
    fNameApp = "";
    fFaustCode = "";
    fFactoryKey = "";
    fOptLevel = "";
    fFactory = 0;
    fIP = "";
    fPort = "";
    fCompression = "";
    fMTU = "";
    fLatency = "";
    fSHAKey = "";
    fInstanceKey = "";
}
    
string connection_info::getJson() 
{
    myMeta metadata;
    metadataDSPFactory(fFactory, &metadata);
    fNameApp = metadata.name;
        
    // This instance is used only to build JSON interface, then it's deleted
    llvm_dsp* dsp = createDSPInstance(fFactory);
    JSONUI json(dsp->getNumInputs(), dsp->getNumOutputs());
    dsp->buildUserInterface(&json);
    deleteDSPInstance(dsp);  
      
    return json.JSON();
}

bool connection_info::getJsonFromKey(FactoryTable factories)
{
    fNameApp = factories[fSHAKey].first;
    fFactory = factories[fSHAKey].second;
    
    if (fFactory) {
        fAnswer = getJson();
        return true;
    } else {
        fAnswer = "Factory not found";
        return false;
    }
}

int connection_info::iteratePost(const char* key, const char* data, size_t size) 
{
    if (size > 0) {
        if (strcmp(key,"name") == 0) {
            fNameApp += nameWithoutSpaces(data);
            if (fNameApp == "") {
                fNameApp = "RemoteDSPServer_DefaultName";
            }
        } else if (strcmp(key,"dsp_data") == 0) {
            fFaustCode += data;   
        } else if (strcmp(key,"NJ_ip") == 0) {
            fIP = data;
        } else if (strcmp(key,"NJ_port") == 0) {
            fPort = data;   
        } else if (strcmp(key,"NJ_latency") == 0) {
            fLatency = data;
        } else if (strcmp(key,"NJ_compression") == 0) {
            fCompression = data;        
        } else if (strcmp(key,"NJ_mtu") == 0) {
            fMTU = data;
        } else if (strcmp(key,"shaKey") == 0) {
            fSHAKey = data;
        } else if (strcmp(key,"instanceKey") == 0) {
            fInstanceKey = data;
        } else if (strcmp(key,"factoryKey") == 0) {
            fFactoryKey = data;
        } else if (strcmp(key,"options") == 0) {
            fCompilationOptions.push_back(data);
        } else if (strcmp(key,"opt_level") == 0) {
            fOptLevel = data;
        }
    }
    
    fAnswercode = MHD_HTTP_OK;
    return MHD_YES;
}

// Create DSP Factory 
bool connection_info::createFactory(FactoryTable factories) 
{
    // Factory already compiled ?
    if (factories.find(fSHAKey) != factories.end()) {
        fFactory = factories[fSHAKey].second;
        fAnswer = getJson();
        return true;
    }
    
    string error = "Incorrect machine code";
    
    // Sort out compilation options
    int argc = fCompilationOptions.size();
    const char* argv[argc];
    for (int i = 0; i < argc; i++) {
        argv[i] = (fCompilationOptions[i]).c_str();
    }
    
    if (isopt(argc, argv, "-machine")) {
        // Machine code
        fFactory = readDSPFactoryFromMachine(fFaustCode);
    } else {
        // DSP code
        fFactory = createDSPFactoryFromString(fNameApp, 
                                            fFaustCode, 
                                            argc, argv, "", 
                                            error, atoi(fOptLevel.c_str()));
    }
   
    if (fFactory) {
        factories[fSHAKey] = make_pair(fNameApp, fFactory);
        // Once the factory is compiled, the JSON is stored as answerstring
        fAnswer = getJson();
        return true;
    } else {
        fAnswer = error;
        return false;
    }
}

connection_info_post::connection_info_post(MHD_Connection* connection):connection_info()
{
    fPostprocessor = 0;
    fAnswercode = MHD_HTTP_OK;
    if (!(fPostprocessor = MHD_create_post_processor(connection, POSTBUFFERSIZE, DSPServer::iteratePost, this))) {
        throw -1;
    }
}

//----------------SERVER----------------------------------------

DSPServer::DSPServer(int argc, const char* argv[]):fPort(-1),fDaemon(NULL)
{}

DSPServer::~DSPServer() {}
    
//---- START/STOP SERVER
bool DSPServer::start(int port) 
{
    fPort = port;
    fDaemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY,
                               port, 
                               NULL, 
                               NULL, 
                               answerToConnection, 
                               this, MHD_OPTION_NOTIFY_COMPLETED, 
                               requestCompleted, NULL, MHD_OPTION_END);
    if (!fDaemon) {
        printf("RemoteDSPServer : MHD_start_daemon failed\n");
        return false;
    }                           

    if (pthread_create(&fThread, NULL, DSPServer::registration, this) != 0) {
        printf("RemoteDSPServer : pthread_create failed\n");
        return false;
    }
    
    return true;
}

void DSPServer::stop()
{
    if (fDaemon) {
//      Faire un truc pour arrêter la boucle
        pthread_cancel(fThread);
        pthread_join(fThread, NULL);
        MHD_stop_daemon(fDaemon);
        fDaemon = 0;
    }
}


//---- Callback of another thread to wait netjack audio connection without blocking the server
void* DSPServer::open(void* arg) 
{
    AudioStarter* starter = (AudioStarter*)arg;
    starter->fServer->open(starter->fDSP);
    delete starter;
    return NULL;
}

void DSPServer::open(audio_dsp* dsp)
{
    if (fLocker.Lock()) {
        if (dsp->init() && dsp->start()) {
            fRunningDsp.push_back(dsp);
        } else {
            delete dsp;
        }
        fLocker.Unlock();
    }
}
 
//---- Creating response page with right header syntaxe
int DSPServer::sendPage(MHD_Connection* connection, const string& page, int status_code, const string& type)
{
    struct MHD_Response *response = MHD_create_response_from_buffer(page.size(), (void*)page.c_str(), MHD_RESPMEM_PERSISTENT);
    if (response) {
        MHD_add_response_header(response, "Content-Type", type.c_str());
        return MHD_queue_response(connection, status_code, response);
    } else {
        return MHD_NO;
    }
}

//-------------------RESPONSE TO CONNEXION

// Checking if every running DSP is really running or if any has stopped
void DSPServer::stopNotActiveDSP()
{
    list<audio_dsp*>::iterator it = fRunningDsp.begin();
    
    while (it != fRunningDsp.end()) {
        if (!(*it)->isActive()) {
            audio_dsp* dsp = *it;
            it = fRunningDsp.erase(it); 
            dsp->stop();
            delete dsp;
        } else {
            it++;
        }
    }
}

// If connection is new, a connection structure is allocated
int DSPServer::createConnection(MHD_Connection* connection, const char* method, void** con_cls)
{
    connection_info* info = NULL;
    try {
        if (strcmp(method, "POST") == 0) {
            info = new connection_info_post(connection);
        } else {
            info = new connection_info_get();
        }
        *con_cls = info;
        return MHD_YES;
    } catch (...) {
        delete info; 
        return MHD_NO;
    }
}

//---- Callback for any type of connection to the server
int DSPServer::answerToConnection(void* cls, 
                                MHD_Connection* connection, 
                                const char* url, 
                                const char* method, 
                                const char* version, 
                                const char* upload_data, 
                                size_t* upload_data_size, 
                                void** con_cls)
{

    DSPServer* server = (DSPServer*)cls;
    server->stopNotActiveDSP();
    
    if (*con_cls) {
    
        // Once connection struct is allocated, the request is treated
        if (strcmp(method, "GET") == 0) {
            return server->answerGet(connection, url);
        } else if (strcmp(method, "POST") == 0) {
            return server->answerPost(connection, url, upload_data, upload_data_size, con_cls);
        } else {
            return server->sendPage(connection, "", MHD_HTTP_BAD_REQUEST, "text/html");
        }
        
    } else {
        // If connection is new, a connection structure is allocated
        return server->createConnection(connection, method, con_cls);
    }
}
    
// For now GET is not a request supported for now
int DSPServer::answerGet(MHD_Connection* connection, const char* url)
{
    if (strcmp(url, "/") == 0) {
        return sendPage(connection, pathToContent("remote-server.html"), MHD_HTTP_OK, "text/html");
    } else if (strcmp(url, "/GetAvailableFactories") == 0) {
        stringstream answer;
        for (map<string, pair<string, llvm_dsp_factory*> >::iterator it = fFactories.begin(); it != fFactories.end(); it++) {
            answer << it->first << " " << it->second.first << " ";
        }
        return sendPage(connection, answer.str(), MHD_HTTP_OK, "text/plain");
    } else {
        return MHD_NO;
    }
}

// Response to all POST request
// 3 requests are correct : 
// - /GetJson --> Receive Faust code / Compile Data / Send back jsonInterface
// - /CreateInstance --> Receive factoryIndex / Create instance 
// - /DeleteFactory --> Receive factoryIndex / Delete Factory
int DSPServer::answerPost(MHD_Connection* connection, const char* url, const char* upload_data, size_t* upload_data_size, void** con_cls)
{
    connection_info* info = (connection_info*)*con_cls;
    
    if (*upload_data_size != 0) {
        return info->postProcess(upload_data, upload_data_size);
    } else {
        
        if (strcmp(url, "/GetJson") == 0) {
            if (info->createFactory(fFactories)) {
                return sendPage(connection, info->fAnswer, MHD_HTTP_OK, "application/json"); 
            } else {
                return sendPage(connection, info->fAnswer, MHD_HTTP_BAD_REQUEST, "text/html");
            }
        } else if (strcmp(url, "/GetJsonFromKey") == 0) {
            if (info->getJsonFromKey(fFactories)) {
                return sendPage(connection, info->fAnswer, MHD_HTTP_OK, "application/json"); 
            } else {
                return sendPage(connection, info->fAnswer, MHD_HTTP_BAD_REQUEST, "text/html");
            }
        } else if (strcmp(url, "/CreateInstance") == 0) {
            if (createInstance(info)) {
                return sendPage(connection, "", MHD_HTTP_OK, "text/html");
            } else {
                return sendPage(connection, info->fAnswer, MHD_HTTP_BAD_REQUEST, "text/html");
            }
        }
//        else if(strcmp(url, "/DeleteFactory") == 0){
//                    
//            llvm_dsp_factory* toDelete = fFactories[con_info->fSHAKey];
//            
//            if (toDelete) {
//                
//                fFactories.erase(con_info->fSHAKey);
//                deleteSlaveDSPFactory(toDelete);
//                
//                return send_page(connection, "", 0, MHD_HTTP_OK, "application/html"); 
//            } else {
//                return send_page(connection, "", 0, MHD_HTTP_BAD_REQUEST, "text/html"); 
//            }
//        }
        else {
            return sendPage(connection, "", MHD_HTTP_BAD_REQUEST, "text/html"); 
        }
    }
}

// Callback processing the received data, to be kept in connection_info
int DSPServer::iteratePost(void* coninfo_cls, MHD_ValueKind /*kind*/, 
                            const char* key, 
                            const char* /*filename*/, 
                            const char* /*content_type*/, 
                            const char* /*transfer_encoding*/, 
                            const char* data, 
                            uint64_t /*off*/, 
                            size_t size) {
    
    connection_info* con_info = (connection_info*)coninfo_cls;
    return con_info->iteratePost(key, data, size);
}

// Callback when connection is ended
void DSPServer::requestCompleted(void* cls, MHD_Connection* connection, void** con_cls, MHD_RequestTerminationCode toe) 
{
    connection_info* con_info = (connection_info*)*con_cls;
    delete con_info;
}

// Create DSP Instance
bool DSPServer::createInstance(connection_info* con_info)
{
    llvm_dsp_factory* factory = fFactories[con_info->fFactoryKey].second;
    
    if (factory) {
    
        try {
            audio_dsp* dsp = new netjack_dsp(factory, con_info->fCompression, 
                                            con_info->fIP, con_info->fPort, 
                                            con_info->fMTU, con_info->fLatency, 
                                            fFactories[con_info->fFactoryKey].first, 
                                            con_info->fInstanceKey);
            pthread_t thread;
            AudioStarter* starter = new AudioStarter(this, dsp);
            if (pthread_create(&thread, NULL, DSPServer::open, starter) != 0) {
                goto error;
            }
            
            /*
            // Test local audio
            audio_dsp* dsp = new coreaudio_dsp(factory, fFactories[con_info->fFactoryKey].first, con_info->fInstanceKey);
            if (dsp->init() && dsp->start()) {
                fRunningDsp.push_back(dsp);
            } else {
                delete dsp;
            }
            */
            
        } catch (...) {
             goto error;
        }
        
        return true;
        
    } else {
        con_info->fAnswer = builtError(ERROR_FACTORY_NOTFOUND);
        return false;
    }  
    
error:
    con_info->fAnswer = builtError(ERROR_INSTANCE_NOTCREATED);
    return false;
   
}

#include "lo/lo.h"

// Register server as available
void* DSPServer::registration(void* arg) 
{
    char host_name[256];
    gethostname(host_name, sizeof(host_name));
    DSPServer* serv = (DSPServer*)arg;
    stringstream nameRegisterService;
    nameRegisterService << "._" << searchIP() << ":" << serv->fPort << "._" << host_name;
    lo_address t = lo_address_new("224.0.0.1", "7770");
    
    while (true) {
    #ifdef WIN32
        Sleep(1);
    #else
        usleep(1000000);
    #endif
        pthread_testcancel();
        lo_send(t, "/faustcompiler", "is", getpid(), nameRegisterService.str().c_str());
    }
    
    pthread_exit(NULL);
}

// DSP server API

EXPORT remote_dsp_server* createRemoteDSPServer(int argc, const char* argv[])
{
     return reinterpret_cast<remote_dsp_server*>(new DSPServer(argc, argv));
}

EXPORT void deleteRemoteDSPServer(remote_dsp_server* server)
{
     delete reinterpret_cast<remote_dsp_server*>(server);
}

EXPORT bool remote_dsp_server::start(int port)
{
    return reinterpret_cast<DSPServer*>(this)->start(port);
}

EXPORT void remote_dsp_server::stop()
{
    return reinterpret_cast<DSPServer*>(this)->stop();
}