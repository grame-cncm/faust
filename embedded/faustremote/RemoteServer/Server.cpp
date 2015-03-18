//
//  FLServerHttp.h
//  
//
//  Created by Sarah Denoux on 13/05/13.
//  Copyright (c) 2013 GRAME. All rights reserved.
//
//

#include "Server.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <openssl/sha.h>

#include "faust/gui/meta.h"
#include "faust/gui/JSONUI.h"

enum{
    ERROR_FACTORY_NOTFOUND,
    ERROR_INSTANCE_NOTCREATED
};

// Declare is called for every metadata coded in the faust DSP
// That way, we get the faust name declared in the faust DSP
struct myMeta : public Meta
{
    string name;
    
    virtual void declare(const char* key, const char* value) {
        if (strcmp(key, "name") == 0) {
            name = value;
        }
    }
};

//------------SLAVE DSP FACTORY-------------------------------

string getJson(connection_info_struct* con_info) {
    
    myMeta metadata;
    metadataDSPFactory(con_info->fLLVMFactory, &metadata);
    con_info->fNameApp = metadata.name;
        
    //This instance is used only to build json interface, then it's deleted
    llvm_dsp* dsp = createDSPInstance(con_info->fLLVMFactory);
    
    JSONUI json(dsp->getNumInputs(), dsp->getNumOutputs());
    dsp->buildUserInterface(&json);    
    string answer = json.JSON();
    
    printf("JSON = %s\n", answer.c_str());
        
    deleteDSPInstance(dsp);
    
//    con_info->fNumInstances = 1;
    
    return answer;
}

//--------------SLAVE DSP INSTANCE-----------------------------

// Same Allocation/Desallcation Prototype as LLVM/REMOTE-DSP
slave_dsp* createSlaveDSPInstance(llvm_dsp_factory* smartFactory, 
                                const string& compression, 
                                const string& ip, 
                                const string& port, 
                                const string& mtu, 
                                const string& latency, 
                                Server* server) 
{
    return new slave_dsp(smartFactory, compression, ip, port, mtu, latency, server);
}

void deleteSlaveDSPInstance(slave_dsp* smartPtr)
{
    delete smartPtr;
}

// Allocation of real LLVM DSP INSTANCE
slave_dsp::slave_dsp(llvm_dsp_factory* smartFactory, 
                    const string& compression, 
                    const string& ip, 
                    const string& port, 
                    const string& mtu, 
                    const string& latency, 
                    Server* server) 
                    : fCV(compression), fIP(ip), fPort(port), fMTU(mtu), fLatency(latency), fServer(server) 
{
    fAudio = NULL;
//  fSlaveFactory = smartFactory->clone();
    fDSP = createDSPInstance(smartFactory);
}

bool slave_dsp::start_audio() 
{
    return fAudio->start();
}

void slave_dsp::stop_audio()
{
    fAudio->stop();
}

// Desallocation of slave dsp resources
slave_dsp::~slave_dsp()
{
    delete fAudio;
    deleteDSPInstance(fDSP);
}

//----------------SERVER----------------------------------------

Server::Server() :fDaemon(NULL), fPort(-1) 
{}

Server::~Server(){}
    
//---- START/STOP SERVER
bool Server::start(int port){
    
    fPort = port;
    fDaemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY,
                               port, 
                               NULL, 
                               NULL, 
                               &answer_to_connection, 
                               this, MHD_OPTION_NOTIFY_COMPLETED, 
                               request_completed, NULL, MHD_OPTION_END);

    if (fDaemon) {
        
        if (pthread_create(&fThread, NULL, Server::registration, this) != 0) {
            printf("RemoteServer::pthread_create failed\n");
            return false;
        }
        
        return true;
    } else {
        return false;
    }
}

void Server::stop()
{
    if (fDaemon) {
//      Faire un truc pour arrêter la boucle
        pthread_cancel(fThread);
        pthread_join(fThread, NULL);
        MHD_stop_daemon(fDaemon);
    }
    fDaemon = 0;
}

//---- Callback of another thread to wait netjack audio connection without blocking the server
void* Server::start_audioSlave(void *arg) 
{
    slave_dsp* dspToStart = (slave_dsp*) arg;
    
    if (dspToStart->fServer->fLocker.Lock()) {
        
        bool success = false;
        dspToStart->fAudio = new server_netjackaudio(atoi(dspToStart->fCV.c_str()), 
                                                    dspToStart->fIP, 
                                                    atoi(dspToStart->fPort.c_str()), 
                                                    atoi(dspToStart->fMTU.c_str()), 
                                                    atoi(dspToStart->fLatency.c_str()));
        
        if (dspToStart->fAudio->init(dspToStart->name().c_str(), dspToStart->fDSP)) {
            if (!dspToStart->fAudio->start()) {
                printf("Start slave audio failed\n");
            } else {
                printf("SLAVE WITH %i INPUTS || %i OUTPUTS\n", dspToStart->fDSP->getNumInputs(), dspToStart->fDSP->getNumOutputs());
                dspToStart->fServer->fRunningDsp.push_back(dspToStart);
                success = true;
            }
        } else {
            printf("Init slave audio failed\n");
        }
        
        if (!success) {
            deleteSlaveDSPInstance(dspToStart);
        }
            
        dspToStart->fServer->fLocker.Unlock();
    }
    return NULL;
}
 
//---- Creating response page with right header syntaxe
int Server::send_page(MHD_Connection *connection, const char *page, int length, int status_code, const char * type)
{
    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(length, (void*)page,
                                               MHD_RESPMEM_PERSISTENT);
    if (!response) {
        return MHD_NO;
    }
    
    MHD_add_response_header(response, "Content-Type", type ? type : "text/plain");
   return MHD_queue_response(connection, status_code, response);
}

//-------------------RESPONSE TO CONNEXION

// Checking if every running DSP is really running or if any has stopped
void Server::stop_NotActive_DSP()
{
    list<slave_dsp*>::iterator it = fRunningDsp.begin();
    
    while (it != fRunningDsp.end()) {
        if (!(*it)->fAudio->is_connexion_active()) {
            slave_dsp* toDelete = *it;
            it = fRunningDsp.erase(it); 
            toDelete->fAudio->stop();
            deleteSlaveDSPInstance(toDelete);
        } else {
            it++;
        }
    }
}

// Allocation/Initialization of connection struct
connection_info_struct* Server::allocate_connection_struct(MHD_Connection *connection, const char *method)
{
    struct connection_info_struct *con_info;
    con_info = new connection_info_struct();
    con_info->init();
    
    if (NULL == con_info) {
        return NULL;
    }
    
    if (0 == strcmp(method, "POST")) {
        
        con_info->fPostprocessor = MHD_create_post_processor(connection, POSTBUFFERSIZE, &iterate_post, (void*)con_info);
        
        if (NULL == con_info->fPostprocessor) {
            delete con_info;
            return NULL;
        }
        
        con_info->fConnectiontype = POST;
        con_info->fAnswercode = MHD_HTTP_OK;
    } else {
        con_info->fConnectiontype = GET;
    }

    return con_info;
}

//---- Callback for any type of connection to the server
int Server::answer_to_connection(void *cls, 
                                MHD_Connection *connection, 
                                const char *url, 
                                const char *method, 
                                const char *version, 
                                const char *upload_data, 
                                size_t *upload_data_size, 
                                void **con_cls)
{
    Server *server = (Server*)cls;
    server->stop_NotActive_DSP();
    
// If connection is new, a connection structure is allocated
    if (NULL == *con_cls){
        connection_info_struct* con_struct = server->allocate_connection_struct(connection, method);
        if (con_struct) {
            *con_cls = (void*) con_struct;
            return MHD_YES;
        } else {
            return MHD_NO;
        }
    }
    
// Once connection struct is allocated, the request is treated
    if (0 == strcmp(method, "GET")) {
        return server->answer_get(connection, url);
    
    } else if (0 == strcmp(method, "POST")) {
        return server->answer_post(connection, url, upload_data, upload_data_size, con_cls);
    
    } else {
        return server->send_page(connection, "", 0, MHD_HTTP_BAD_REQUEST, "text/html");
    }
}
    
// For now GET is not a request supported for now
int Server::answer_get(MHD_Connection* connection, const char *url)
{
    printf("IS IT A GET REQUEST\n");
    
    if (strcmp(url, "/GetAvailableFactories") == 0) {
        
        printf("GetAvailableFactories %ld\n", fAvailableFactories.size());
        string answerstring("");
        
        for (map<string, pair<string, llvm_dsp_factory*> >::iterator it = fAvailableFactories.begin(); it != fAvailableFactories.end(); it++) {
            answerstring += " " + it->first;
            answerstring += " " + it->second.first;
        }
        
        return send_page(connection, answerstring.c_str(), answerstring.size(), MHD_HTTP_OK, "text/plain");
    } else {
        return MHD_NO;
    }
}


// Response to all POST request
// 3 requests are correct : 
// - /GetJson --> Receive faust code / Compile Data / Send back jsonInterface
// - /CreateInstance --> Receive factoryIndex / Create instance 
// - /DeleteFactory --> Receive factoryIndex / Delete Factory
int Server::answer_post(MHD_Connection *connection, const char *url, const char *upload_data, size_t *upload_data_size, void **con_cls)
{
    struct connection_info_struct *con_info = (connection_info_struct*)*con_cls;
    
    if (0 != *upload_data_size) {
        
        MHD_post_process(con_info->fPostprocessor, upload_data, *upload_data_size);
        *upload_data_size = 0;
        
        return MHD_YES;
    } else {
        
        if (strcmp(url, "/GetJson") == 0) {
            
            if (compile_Data(con_info)) {
                return send_page(connection, con_info->fAnswerstring.c_str(), con_info->fAnswerstring.size(), MHD_HTTP_OK, "application/json"); 
            } else {
                return send_page(connection, con_info->fAnswerstring.c_str(), con_info->fAnswerstring.size(), MHD_HTTP_BAD_REQUEST, "text/html");
            }
        } else if (strcmp(url, "/GetJsonFromKey") == 0) {
            
            if (getJsonFromKey(con_info)) {
                return send_page(connection, con_info->fAnswerstring.c_str(), con_info->fAnswerstring.size(), MHD_HTTP_OK, "application/json"); 
            } else {
                return send_page(connection, con_info->fAnswerstring.c_str(), con_info->fAnswerstring.size(), MHD_HTTP_BAD_REQUEST, "text/html");
            }
        } else if (strcmp(url, "/CreateInstance") == 0) {
            
            if (createInstance(con_info)) {
                return send_page(connection, "", 0, MHD_HTTP_OK, "text/html");
            } else {
                return send_page(connection, con_info->fAnswerstring.c_str(), con_info->fAnswerstring.size(), MHD_HTTP_BAD_REQUEST, "text/html");
            }
            
        }
//        else if(strcmp(url, "/DeleteFactory") == 0){
//                    
//            llvm_dsp_factory* toDelete = fAvailableFactories[con_info->fSHAKey];
//            
//            if (toDelete) {
//                
//                fAvailableFactories.erase(con_info->fSHAKey);
//                deleteSlaveDSPFactory(toDelete);
//                
//                return send_page(connection, "", 0, MHD_HTTP_OK, "application/html"); 
//            } else {
//                return send_page(connection, "", 0, MHD_HTTP_BAD_REQUEST, "text/html"); 
//            }
//        }
        else if (strcmp(url, "/StartAudio") == 0) {
            startAudio(con_info->fSHAKey);
            return send_page(connection, "", 0, MHD_HTTP_OK, "text/html");
        } else if(strcmp(url, "/StopAudio") == 0){
            stopAudio(con_info->fSHAKey);
            return send_page(connection, "", 0, MHD_HTTP_OK, "text/html");
        } else{
            return send_page(connection, "", 0, MHD_HTTP_BAD_REQUEST, "text/html"); 
        }
    }
}

string nameWithoutSpaces(const string& name)
{
    string newname = name;
    while (newname.find(' ') != string::npos) {
        newname.replace(newname.find(' '), 1, "_");
    }
    return newname;
}

// Callback processing the received data.
// The datas are stocked in connection_info_struct
int Server::iterate_post(void *coninfo_cls, MHD_ValueKind /*kind*/, 
                        const char *key, 
                        const char */*filename*/, 
                        const char */*content_type*/, 
                        const char */*transfer_encoding*/, 
                        const char *data, 
                        uint64_t /*off*/, 
                        size_t size){
    
    struct connection_info_struct *con_info = (connection_info_struct*)coninfo_cls;
    
//    printf("FLServer::iterate_post %s\n", key);
    
    if (size > 0) {
        
        if(strcmp(key,"name") == 0){
            con_info->fNameApp+=nameWithoutSpaces(data);
            if(con_info->fNameApp.compare("") == 0)
                con_info->fNameApp = "RemoteServer_DefaultName";
        }
        if(strcmp(key,"data") == 0)
            con_info->fFaustCode+=data;        
            
        if(strcmp(key,"NJ_ip") == 0) 
            con_info->fIP = data;
        
        if(strcmp(key,"NJ_port") == 0) 
            con_info->fPort =data;   
        
        if(strcmp(key,"NJ_latency") == 0)
            con_info->fLatency = data;
        
        if(strcmp(key,"NJ_compression") == 0)
            con_info->fCV = data;        
        
        if(strcmp(key,"NJ_mtu") == 0) 
            con_info->fMTU = data;
        
        if(strcmp(key,"shaKey") == 0)
            con_info->fSHAKey = data;
        
        if(strcmp(key,"instanceKey") == 0)
            con_info->fInstanceKey = data;
        
        if(strcmp(key,"factoryKey") == 0)
            con_info->fFactoryKey = data;
        
        if(strcmp(key,"options") == 0)
            con_info->fCompilationOptions.push_back(string(data));
        
        if(strcmp(key,"opt_level") == 0)
            con_info->fOptLevel = data;
    }
    
    con_info->fAnswercode = MHD_HTTP_OK;
    return MHD_YES;
}

// Callback when connection is ended
void Server::request_completed(void *cls, MHD_Connection *connection, void **con_cls, MHD_RequestTerminationCode toe) 
{
    struct connection_info_struct *con_info = (connection_info_struct*)*con_cls;
    
    if (con_info) {
        if (con_info->fConnectiontype == POST) {
            if (NULL != con_info->fPostprocessor) {
                MHD_destroy_post_processor(con_info->fPostprocessor);
            }
        }
        delete con_info;
        *con_cls = NULL;
    }
}

// Start/Stop DSP Instance from its SHAKEY
bool Server::startAudio(const string& shakey)
{
    list<slave_dsp*>::iterator it;
    
    for (it = fRunningDsp.begin(); it != fRunningDsp.end(); it++) {
        if (shakey.compare((*it)->key()) == 0) {
            if ((*it)->start_audio()) {
                return true;
            }
        }
    }

    return false;
}

void Server::stopAudio(const string& shakey)
{
    list<slave_dsp*>::iterator it;
    
    for (it = fRunningDsp.begin(); it != fRunningDsp.end(); it++) {
        if (shakey.compare((*it)->key()) == 0) {
            (*it)->stop_audio();
        }
    }
}

bool Server::getJsonFromKey(connection_info_struct* con_info)
{
    string SHA_Key = con_info->fSHAKey;
    con_info->fNameApp = fAvailableFactories[SHA_Key].first;
    con_info->fLLVMFactory = fAvailableFactories[SHA_Key].second;
    
    if (con_info->fLLVMFactory) {
        con_info->fAnswerstring = getJson(con_info);
        return true;
    } else {
        con_info->fAnswerstring = "Factory Not Found!";
        return false;
    }
}

// Create DSP Factory 
bool Server::compile_Data(connection_info_struct* con_info) {
    
    if (con_info->fSHAKey != "") {
        
        // Sort out compilation options
        
        int argc = con_info->fCompilationOptions.size();
        const char* argv[argc];
        
        for (int i=0; i<argc; i++) {
            argv[i] = (con_info->fCompilationOptions[i]).c_str();
        }
        
        string error;
        con_info->fLLVMFactory = createDSPFactoryFromString(con_info->fNameApp, con_info->fFaustCode, argc, argv, "", error, atoi(con_info->fOptLevel.c_str()));
        
        if (con_info->fLLVMFactory) {
            fAvailableFactories[con_info->fSHAKey] = make_pair(con_info->fNameApp, con_info->fLLVMFactory);
            
            // Once the factory is compiled, the json is stored as answerstring
            con_info->fAnswerstring = getJson(con_info);
            return true;
        }
    }
    con_info->fAnswerstring = "Impossible to generate SHA1 key";
    return false;
}

// Create DSP Instance
bool Server::createInstance(connection_info_struct* con_info)
{
    printf("CREATEINSTANCE WITH INDEX= %s\n", con_info->fFactoryKey.c_str());
    llvm_dsp_factory* realFactory = fAvailableFactories[con_info->fFactoryKey].second;
    
    if (realFactory) {
        
        printf("Instance\n");
        
        slave_dsp* dsp = createSlaveDSPInstance(realFactory, con_info->fCV, con_info->fIP, con_info->fPort, con_info->fMTU, con_info->fLatency, this);
        if (!dsp) return false;
        
        dsp->setName(fAvailableFactories[con_info->fFactoryKey].first);
        pthread_t myNewThread;
        
        if (pthread_create(&myNewThread, NULL, Server::start_audioSlave, dsp) == 0){
            dsp->setKey(con_info->fInstanceKey);
            return true;
        } else {
            stringstream s;
            s << ERROR_INSTANCE_NOTCREATED;
            con_info->fAnswerstring = s.str();
            return false;
        }
    } else {
        stringstream s;
        s << ERROR_FACTORY_NOTFOUND;
        con_info->fAnswerstring = s.str();
        return false;
    }    
}

#include "lo/lo.h"

// Register server as available
void* Server::registration(void* arg) {
    
    printf("SERVICE REGISTRATION\n");
    
    char host_name[256];
    gethostname(host_name, sizeof(host_name));
    
    Server* serv = (Server*)arg;
    
    stringstream p;
    p<<serv->fPort;
    string nameRegisterService = "._";
    
    nameRegisterService += searchIP();
    nameRegisterService += ":";
    nameRegisterService += p.str();
    nameRegisterService += "._";
    nameRegisterService += host_name;

    lo_address t = lo_address_new("224.0.0.1", "7770");
    
    while (true) {
#ifdef WIN32
        Sleep(1);
#else
        usleep(1000000);
#endif
        pthread_testcancel();
        
        int pid = getpid();
        lo_send(t, "/faustcompiler", "is", pid, nameRegisterService.c_str());
    }
    
    pthread_exit(NULL);
}




