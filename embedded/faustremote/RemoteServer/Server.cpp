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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#ifdef __APPLE__
#include <dns_sd.h>
#endif

//#define JACK 1
#define COREAUDIO 1
//#define PORTAUDIO 1
//#define IOSAUDIO 1
//#define ANDROID 1

#include "faust/audio/netjack-dsp.h"

#ifdef COREAUDIO
#include "faust/audio/coreaudio-dsp.h"
#endif

#ifdef IOSAUDIO
#include "faust/audio/coreaudio-ios-dsp.h"
#endif

#ifdef PORTAUDIO
#include "faust/audio/portaudio-dsp.h"
#endif

#ifdef JACK
#include "faust/audio/jack-dsp.h"
#endif

#ifdef ANDROID
#include "faust/audio/android-dsp.h"
#endif

// Declare is called for every metadata coded in the Faust DSP
// That way, we get the faust name declared in the Faust DSP
struct myMeta : public Meta
{
    string name;
    
    virtual void declare(const char* key, const char* value) 
    {
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

// NetJack slave client

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
                    const string& name, const string& key,
                    createInstanceDSPCallback cb1, void* cb1_arg,
                    deleteInstanceDSPCallback cb2, void* cb2_arg);
        
        bool init(int u1, int u2);
       
        bool isActive() { return dynamic_cast<netjackaudio_slave*>(fAudio)->is_connexion_active(); }

};

netjack_dsp::netjack_dsp(llvm_dsp_factory* factory, 
                        const string& compression, 
                        const string& ip, 
                        const string& port, 
                        const string& mtu, 
                        const string& latency,
                        const string& name,
                        const string& key,
                        createInstanceDSPCallback cb1, void* cb1_arg,
                        deleteInstanceDSPCallback cb2, void* cb2_arg)
                        :audio_dsp(factory, name, key, cb1, cb1_arg, cb2, cb2_arg), fIP(ip), 
                        fPort(port), fCompression(compression), 
                        fMTU(mtu), fLatency(latency)
{}

bool netjack_dsp::init(int u1, int u2)
{
    fAudio = new netjackaudio_slave(atoi(fCompression.c_str()), 
                                    fIP, 
                                    atoi(fPort.c_str()), 
                                    atoi(fMTU.c_str()), 
                                    atoi(fLatency.c_str()));
                                        
    if (!fAudio->init(fName.c_str(), fDSP)) {
        printf("netjack_dsp : init audio failed\n");
        return false;
    } else {
        return true;
    }
}

bool audio_dsp::init(int sr, int bs)
{
#ifdef COREAUDIO
    fAudio = new coreaudio(sr, bs);
#endif  
#ifdef IOSAUDIO
    fAudio = new iosaudio(sr, bs);
#endif 
#ifdef PORTAUDIO
    fAudio = new portaudio(sr, bs);
#endif 
#ifdef JACK
    fAudio = new jackaudio(0, 0);
#endif 
#ifdef ANDROID
    fAudio = new androidaudio(sr, bs);
#endif 
    if (!fAudio->init(fName.c_str(), fDSP)) {
        printf("audio_dsp : init audio failed\n");
        return false;
    } else {
        return true;
    }
}

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
    fJSON = "";
}
    
string connection_info::getJson() 
{
    if (fJSON == "") {
        myMeta metadata;
        metadataDSPFactory(fFactory, &metadata);
        fNameApp = metadata.name;
        
        // This instance is used only to build JSON interface, then it's deleted
        llvm_dsp* dsp = createDSPInstance(fFactory);
        JSONUI json(dsp->getNumInputs(), dsp->getNumOutputs());
        dsp->buildUserInterface(&json);
        deleteDSPInstance(dsp);  
        fJSON = json.JSON();
    }
      
    return fJSON;
}

bool connection_info::getJsonFromKey(FactoryTable factories)
{
    if (factories.find(fSHAKey) != factories.end()) {
        fNameApp = factories[fSHAKey].first;
        fFactory = factories[fSHAKey].second;
        fAnswer = getJson();
        return true;
    } else {
        fAnswer = "Factory not found";
        return false;
    }
}

// Create DSP Factory 
bool connection_info::createFactory(FactoryTable factories, DSPServer* server) 
{
    string error = "Incorrect machine code";
    
    // Sort out compilation options
    int argc = fCompilationOptions.size();
    const char* argv[argc];
    for (int i = 0; i < argc; i++) {
        argv[i] = (fCompilationOptions[i]).c_str();
    }
    
    if (isopt(argc, argv, "-m")) {
        printf("Machine code\n");
        // Machine code
        //fFactory = readDSPFactoryFromMachine(fFaustCode);
        fFactory = readCDSPFactoryFromMachine(fFaustCode.c_str());
    } else {
        // DSP code
        /*
        fFactory = createDSPFactoryFromString(fNameApp,
                                            fFaustCode, 
                                            argc, argv, "", 
                                            error, atoi(fOptLevel.c_str()));
        */
    
        char error1[256];
        fFactory = createCDSPFactoryFromString(fNameApp.c_str(),
                                            fFaustCode.c_str(),
                                            argc, argv, "",
                                            error1, atoi(fOptLevel.c_str()));
    }
    
    if (fFactory) {
        // Possibly call callback
        if (server->fCreateDSPFactoryCb) {
            return server->fCreateDSPFactoryCb(fFactory, server->fCreateDSPFactoryCb_arg);
        }   
        factories[fSHAKey] = make_pair(fNameApp, fFactory);
        return true;
    } else {
        return false;
    }
}

int connection_info::iteratePost(const char* key, const char* data, size_t size) 
{
    if (size > 0) {
        if (strcmp(key, "name") == 0) {
            fNameApp += nameWithoutSpaces(data);
            if (fNameApp == "") {
                fNameApp = "RemoteDSPServer_DefaultName";
            }
        } else if (strcmp(key,"audio_type") == 0) {
            fAudioType = data;
        } else if (strcmp(key,"dsp_data") == 0) {
            fFaustCode += data;  // Possibly several post ?
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
        } else if (strcmp(key,"LA_sample_rate") == 0) {
            fSampleRate = data;
        } else if (strcmp(key,"LA_buffer_size") == 0) {
            fBufferSize = data;
        }
    }
    
    fAnswercode = MHD_HTTP_OK;
    return MHD_YES;
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

#include "lo/lo.h"

DSPServer::DSPServer(int argc, const char* argv[]):fPort(-1),fDaemon(NULL),
fCreateDSPFactoryCb(NULL),fCreateDSPFactoryCb_arg(NULL),
fCreateDSPInstanceCb(NULL),fCreateDSPInstanceCb_arg(NULL),
fDeleteDSPFactoryCb(NULL),fDeleteDSPFactoryCb_arg(NULL),
fDeleteDSPInstanceCb(NULL),fDeleteDSPInstanceCb_arg(NULL)
{}

DSPServer::~DSPServer() {}

// Register server as available
void* DSPServer::registration(void* arg) 
{
    DSPServer* serv = (DSPServer*)arg;
    
    char host_name[256];
    gethostname(host_name, sizeof(host_name));
    char* target = getCDSPMachineTarget();
    stringstream name_service;
    name_service << searchIP() << ":" << serv->fPort << ":" << host_name << ":" << target;
    lo_address adress = lo_address_new("224.0.0.1", "7770");
    
    while (true) {
    #ifdef WIN32
        Sleep(1);
    #else
        usleep(1000000);
    #endif
        pthread_testcancel();
        lo_send(adress, "/faustcompiler", "is", getpid(), name_service.str().c_str());
    }
    
    freeCDSP(target);
    pthread_exit(NULL);
}
    
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
        // Faire un truc pour arrêter la boucle ?
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
        if (dsp->init(-1, -1) && dsp->start()) {
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
        return getAvailableFactories(connection);
    } else {
        return MHD_NO;
    }
}

bool DSPServer::getAvailableFactories(MHD_Connection* connection)
{
    stringstream answer;
    for (map<string, pair<string, llvm_dsp_factory*> >::iterator it = fFactories.begin(); it != fFactories.end(); it++) {
        answer << it->first << " " << it->second.first << " ";
    }
    return sendPage(connection, answer.str(), MHD_HTTP_OK, "text/plain");
}

bool DSPServer::getJsonFromKey(MHD_Connection* connection, connection_info* info)
{
    if (info->getJsonFromKey(fFactories)) {
        return sendPage(connection, info->fAnswer, MHD_HTTP_OK, "application/json"); 
    } else {
        return sendPage(connection, info->fAnswer, MHD_HTTP_BAD_REQUEST, "text/html");
    }
}

bool DSPServer::getJson(MHD_Connection* connection, connection_info* info)
{
    if (info->getJsonFromKey(fFactories) || info->createFactory(fFactories, this)) {
        return sendPage(connection, info->fAnswer, MHD_HTTP_OK, "application/json");
    } else {
        return sendPage(connection, info->fAnswer, MHD_HTTP_BAD_REQUEST, "text/html");
    }
}

bool DSPServer::createInstance(MHD_Connection* connection, connection_info* info)
{
    if (createInstance(info)) {
        return sendPage(connection, "", MHD_HTTP_OK, "text/html");
    } else {
        return sendPage(connection, info->fAnswer, MHD_HTTP_BAD_REQUEST, "text/html");
    }
}

bool DSPServer::start(MHD_Connection* connection, connection_info* info)
{
    if (start(info->fSHAKey)) {
        return sendPage(connection, "", MHD_HTTP_OK, "text/html");
    } else {
        return sendPage(connection, builtError(ERROR_INSTANCE_NOTFOUND), MHD_HTTP_BAD_REQUEST, "text/html");
    }
}

bool DSPServer::stop(MHD_Connection* connection, connection_info* info)
{
    if (stop(info->fSHAKey)) {
        return sendPage(connection, "", MHD_HTTP_OK, "text/html");
    } else {
        return sendPage(connection, builtError(ERROR_INSTANCE_NOTFOUND), MHD_HTTP_BAD_REQUEST, "text/html");
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
            return getJson(connection, info);
        } else if (strcmp(url, "/GetJsonFromKey") == 0) {
            return getJsonFromKey(connection, info);
        } else if (strcmp(url, "/CreateInstance") == 0) {
            return createInstance(connection, info);
        } else if (strcmp(url, "/Start") == 0) {
            return start(connection, info);
        } else if(strcmp(url, "/Stop") == 0) {
            return stop(connection, info);
        } 
//        else if(strcmp(url, "/DeleteFactory") == 0) {
//            llvm_dsp_factory* toDelete = fFactories[con_info->fSHAKey];
//            
//            if (toDelete) {
//                fFactories.erase(con_info->fSHAKey);
//                deleteSlaveDSPFactory(toDelete);
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
    audio_dsp* audio = NULL;
    llvm_dsp* dsp = NULL;
    
    if (factory) {
    
        try {
            if (con_info->fAudioType == "kNetJack") {
                audio = new netjack_dsp(factory, con_info->fCompression, 
                                        con_info->fIP, con_info->fPort, 
                                        con_info->fMTU, con_info->fLatency, 
                                        fFactories[con_info->fFactoryKey].first, 
                                        con_info->fInstanceKey,
                                        fCreateDSPInstanceCb, fCreateDSPInstanceCb_arg,
                                        fDeleteDSPInstanceCb, fDeleteDSPInstanceCb_arg);
                pthread_t thread;
                AudioStarter* starter = new AudioStarter(this, audio);
                if (pthread_create(&thread, NULL, DSPServer::open, starter) != 0) {
                    goto error;
                }
            } else if (con_info->fAudioType == "kLocalAudio") {
                
                 // Steph : 06/15
                if (!(dsp = createDSPInstance(factory))) {
                    return false;
                }
                
                if (fCreateDSPInstanceCb) {
                    fCreateDSPInstanceCb(dsp, fCreateDSPInstanceCb_arg);
                }
                
                /*
                audio = new audio_dsp(factory,
                                    fFactories[con_info->fFactoryKey].first, 
                                    con_info->fInstanceKey,
                                    fCreateDSPInstanceCb, 
                                    fCreateDSPInstanceCb_arg,
                                    fDeleteDSPInstanceCb, 
                                    fDeleteDSPInstanceCb_arg);
                if (audio->init(atoi(con_info->fSampleRate.c_str()), atoi(con_info->fBufferSize.c_str()))) {
                    fRunningDsp.push_back(audio);
                } else {
                    delete audio;
                }
                */
            }
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

// Start/Stop Audio instance from its SHAKEY
bool DSPServer::start(const string& shakey)
{
    list<audio_dsp*>::iterator it;
    
    for (it = fRunningDsp.begin(); it != fRunningDsp.end(); it++) {
        if (shakey == (*it)->getKey()) {
            if ((*it)->start()) {
                return true;
            }
        }
    }

    return false;
}

bool DSPServer::stop(const string& shakey)
{
    list<audio_dsp*>::iterator it;
    
    for (it = fRunningDsp.begin(); it != fRunningDsp.end(); it++) {
        if (shakey == (*it)->getKey()) {
            (*it)->stop();
            return true;
        }
    }

    return false;
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

EXPORT void remote_dsp_server::setCreateDSPFactoryCallback(createFactoryDSPCallback callback, void* callback_arg)
{
    reinterpret_cast<DSPServer*>(this)->setCreateDSPFactoryCallback(callback, callback_arg);
}

EXPORT void remote_dsp_server::setDeleteDSPFactoryCallback(deleteFactoryDSPCallback callback, void* callback_arg)
{
    reinterpret_cast<DSPServer*>(this)->setDeleteDSPFactoryCallback(callback, callback_arg);
}

EXPORT void remote_dsp_server::setCreateDSPInstanceCallback(createInstanceDSPCallback callback, void* callback_arg)
{
    reinterpret_cast<DSPServer*>(this)->setCreateDSPInstanceCallback(callback, callback_arg);
}

EXPORT void remote_dsp_server::setDeleteDSPInstanceCallback(deleteInstanceDSPCallback callback, void* callback_arg)
{
    reinterpret_cast<DSPServer*>(this)->setDeleteDSPInstanceCallback(callback, callback_arg);
}