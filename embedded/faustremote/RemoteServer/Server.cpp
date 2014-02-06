//
//  FLServerHttp.h
//  
//
//  Created by Sarah Denoux on 13/05/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//
//

#include "Server.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "faust/gui/meta.h"
#include "faust/gui/jsonfaustui.h"


// Declare is called for every metadata coded in the faust DSP
// That way, we get the faust name declared in the faust DSP
struct myMeta : public Meta
{
    string name;
    
    virtual void declare(const char* key, const char* value){
        if(strcmp(key, "name") == 0)
            name = value;
    }
};


//------------SLAVE DSP FACTORY-------------------------------

// Same Allocation/Desallcation Prototype as LLVM/REMOTE-DSP
slave_dsp_factory* createSlaveDSPFactory(int argc, const char** argv, const string& nameApp, const string& faustContent, int opt_level, int factoryIndex, string& answer){
    
    slave_dsp_factory* newFactory = new slave_dsp_factory;
    
    if(newFactory->init(argc, argv, nameApp, faustContent, opt_level, factoryIndex, answer))
        return newFactory;
    else
        return NULL;
}

void deleteSlaveDSPFactory(slave_dsp_factory* smartPtr){
    
    if(smartPtr->delete_Factory())
        delete smartPtr;
}

// Creation of real LLVM DSP FACTORY 
// & Creation of intermediate DSP Instance to get json interface
bool slave_dsp_factory::init(int argc, const char** argv, const string& nameApp, const string& faustContent, int opt_level, int factoryIndex, string& answer){
    
    printf("NAMEAPP = %s | faustContent = %s", nameApp.c_str(), faustContent.c_str());
    printf("AGRC = %i | argv = %p\n", argc, argv);
    
    string error_msg;
    fLLVMFactory = createDSPFactoryFromString(nameApp, faustContent, argc, argv, "", error_msg, opt_level);
    
    printf("%s\n", error_msg.c_str());
    
    if(fLLVMFactory){
        
        myMeta metadata;
        metadataDSPFactory(fLLVMFactory, &metadata);
        
        fNameApp = metadata.name;
        
        //This instance is used only to build json interface, then it's deleted
        llvm_dsp* dsp = createDSPInstance(fLLVMFactory);
        
        stringstream s;
        s<<factoryIndex;
        
        string nameOfApp(fNameApp.c_str());
        
        httpdfaust::jsonfaustui json(nameOfApp.c_str(), "", 0);
        dsp->buildUserInterface(&json);
        json.numInput(dsp->getNumInputs());
        json.numOutput(dsp->getNumOutputs());
        json.declare("indexFactory", s.str().c_str());
        
        printf("JSON = %s\n", json.json().c_str());
        
        answer = json.json();
        
        deleteDSPInstance(dsp);
        
        fNumInstances = 1;
        return true;
    } else {
        answer = error_msg;
        return false;
    }
}

// "Smart" Desallocation of factory depending on its running instances
bool slave_dsp_factory::delete_Factory(){
    
    fNumInstances--;
    
    if(fNumInstances == 0){
        deleteDSPFactory(fLLVMFactory);
        return true;
    }
    else
        return false;
}

// Everytime a factory is used, it is cloned, to ensure the right count of its instances
slave_dsp_factory* slave_dsp_factory::clone(){
    
    fNumInstances++;
    return this;
}


//--------------SLAVE DSP INSTANCE-----------------------------

// Same Allocation/Desallcation Prototype as LLVM/REMOTE-DSP
slave_dsp* createSlaveDSPInstance(slave_dsp_factory* smartFactory, const string& compression, const string& ip, const string& port, const string& mtu, const string& latency, Server* server){
    
    return new slave_dsp(smartFactory, compression, ip, port, mtu, latency, server);
}

void deleteSlaveDSPInstance(slave_dsp* smartPtr){
    
    delete smartPtr;
}

// Allocation of real LLVM DSP INSTANCE
slave_dsp::slave_dsp(slave_dsp_factory* smartFactory, const string& compression, const string& ip, const string& port, const string& mtu, const string& latency, Server* server) : fCV(compression), fIP(ip), fPort(port), fMTU(mtu), fLatency(latency), fServer(server){
    
    fAudio = NULL;

    fSlaveFactory = smartFactory->clone();
    fDSP = createDSPInstance(fSlaveFactory->fLLVMFactory);
}

// Desallocation of slave dsp resources
slave_dsp::~slave_dsp(){
    
    fAudio->stop();
    
    delete fAudio;
    deleteDSPInstance(fDSP);
    deleteSlaveDSPFactory(fSlaveFactory);
}

//----------------SERVER----------------------------------------

Server::Server(){
    fError = "";
    fDaemon = NULL;
}

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

    if(fDaemon){
        fRegistrationService = new DNSServiceRef; //Structure allocate to register as available web service
        registration();
        return true;
    }
    else
        return false;
}

void Server::stop(){
   
    if (fDaemon) {
        
        string nameService;
        
        nameService = searchIP();
        nameService += ".RemoteProcessing";
        
        DNSServiceRegister(fRegistrationService, 0, 0, nameService.c_str(), "_http._tcp", "local", NULL, 7779, 0, NULL, NULL, NULL );
        DNSServiceRefDeallocate(*fRegistrationService);
        MHD_stop_daemon(fDaemon);
    }
    
    fDaemon = 0;
}

//---- Callback of another thread to wait netjack audio connection without blocking the server
void* Server::start_audioSlave(void *arg ){
    
    slave_dsp* dspToStart = (slave_dsp*) arg;
    
    if(dspToStart->fServer->fLocker.Lock()){
        
        dspToStart->fAudio = new server_netjackaudio(atoi(dspToStart->fCV.c_str()), 
                                                      dspToStart->fIP, 
                                                      atoi(dspToStart->fPort.c_str()), 
                                                      DEFAULT_MTU, 
                                                      atoi(dspToStart->fLatency.c_str()));
        
        if (dspToStart->fAudio->init(dspToStart->fSlaveFactory->fNameApp.c_str(), dspToStart->fDSP)) {
            if (!dspToStart->fAudio->start())
                printf("Start slave audio failed\n");
            else
                dspToStart->fServer->fRunningDsp.push_back(dspToStart);
        }
        else
            printf("Init slave audio failed\n");
        
        dspToStart->fServer->fLocker.Unlock();
    }
    return NULL;
}
  
//---- Every new factory is mapped with an unique index : the smallest one unused
int Server::getSmallestIndexAvailable(){

    bool found = true;
    int i = 0;
    
    while(found && fAvailableFactories.size() != 0){
        found = (fAvailableFactories.find(i) != fAvailableFactories.end());
        i++;
    }
    
    return i;
}
 
//---- Creating response page with right header syntaxe
int Server::send_page(MHD_Connection *connection, const char *page, int length, int status_code, const char * type){
    
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
void Server::stop_NotActive_DSP(){
    
    list<slave_dsp*>::iterator it = fRunningDsp.begin();
    
    while (it != fRunningDsp.end())
    {
        if(!(*it)->fAudio->is_connexion_active()){
            slave_dsp* toDelete = *it;
            it = fRunningDsp.erase(it);
            deleteSlaveDSPInstance(toDelete);
        }
        else
            it++;
    }
}

// Allocation/Initialization of connection struct
connection_info_struct* Server::allocate_connection_struct(MHD_Connection *connection, const char *method){
    
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
    }
    
    else
        con_info->fConnectiontype = GET;

    return con_info;
}

//---- Callback for any type of connection to the server
int Server::answer_to_connection	(void *cls, MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls){
   
    Server *server = (Server*)cls;
    
    server->stop_NotActive_DSP();
    
// If connection is new, a connection structure is allocated
    if (NULL == *con_cls){
        
        connection_info_struct* con_struct = server->allocate_connection_struct(connection, method);
    
        if(con_struct){
            *con_cls = (void*) con_struct;
            return MHD_YES;
        }
        else
            return MHD_NO;
    }
    
// Once connection struct is allocated, the request is treated
    if (0 == strcmp(method, "GET"))
        return server->answer_get(connection);
    
    else if (0 == strcmp(method, "POST"))
        return server->answer_post(connection, url, upload_data, upload_data_size, con_cls);
    
    else
        return server->send_page(connection, "", 0, MHD_HTTP_BAD_REQUEST, "text/html");
}
    
// For now GET is not a request supported for now
int Server::answer_get(MHD_Connection* connection){

    return send_page(connection, "", 0, MHD_HTTP_BAD_REQUEST, "text/html");
}
    
// Response to all POST request
// 3 requests are correct : 
// - /GetJson --> Receive faust code / Compile Data / Send back jsonInterface
// - /CreateInstance --> Receive factoryIndex / Create instance 
// - /DeleteFactory --> Receive factoryIndex / Delete Factory
int Server::answer_post(MHD_Connection *connection, const char *url, const char *upload_data, size_t *upload_data_size, void **con_cls){
    
    struct connection_info_struct *con_info = (connection_info_struct*)*con_cls;
    
    if (0 != *upload_data_size) {
        
        MHD_post_process(con_info->fPostprocessor, upload_data, *upload_data_size);
        *upload_data_size = 0;
        
        return MHD_YES;
    } 
    else{
        
        if(strcmp(url, "/GetJson") == 0){
            
            if(compile_Data(con_info))
                return send_page(connection, con_info->fAnswerstring.c_str(), con_info->fAnswerstring.size(), MHD_HTTP_OK, "application/json"); 
            else
                return send_page(connection, con_info->fAnswerstring.c_str(), con_info->fAnswerstring.size(), MHD_HTTP_BAD_REQUEST, "text/html");
        }
        else if(strcmp(url, "/CreateInstance") == 0){
            
            if(createInstance(con_info))
                return send_page(connection, "", 0, MHD_HTTP_OK, "text/html"); 
            else{
                return send_page(connection, con_info->fAnswerstring.c_str(), con_info->fAnswerstring.size(), MHD_HTTP_BAD_REQUEST, "text/html");
            }
            
        }
        else if(strcmp(url, "/DeleteFactory") == 0){
                    
            slave_dsp_factory* toDelete = fAvailableFactories[atoi(con_info->fFactoryIndex.c_str())];
            
            if(toDelete){
                
                fAvailableFactories.erase(atoi(con_info->fFactoryIndex.c_str()));
                deleteSlaveDSPFactory(toDelete);
                
                return send_page(connection, "", 0, MHD_HTTP_OK, "application/html"); 
            }
            else
                return send_page(connection, "", 0, MHD_HTTP_BAD_REQUEST, "text/html"); 
        }
        else{
            return send_page(connection, "", 0, MHD_HTTP_BAD_REQUEST, "text/html"); 
    
        }
    }
}

// Callback processing the received data.
// The datas are stocked in connection_info_struct
int Server::iterate_post(void *coninfo_cls, MHD_ValueKind /*kind*/, const char *key, const char */*filename*/, const char */*content_type*/, const char */*transfer_encoding*/, const char *data, uint64_t /*off*/, size_t size){
    
    struct connection_info_struct *con_info = (connection_info_struct*)coninfo_cls;
    
//    printf("FLServer::iterate_post %s\n", key);
    
    if (size > 0) {
        
        if(strcmp(key,"name") == 0)
            con_info->fNameApp+=data;
        
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
        
        if(strcmp(key,"factoryIndex") == 0)
            con_info->fFactoryIndex = data;

        if(strcmp(key,"number_options") == 0){
            con_info->fNumCompilOptions = atoi(data);
            con_info->fCompilationOptions = new string[con_info->fNumCompilOptions];
            con_info->fIndicator = 0;
        }
        if(strcmp(key,"options") == 0){
            con_info->fCompilationOptions[con_info->fIndicator] = data;
            con_info->fIndicator++;
        }
        
        if(strcmp(key,"opt_level") == 0)
            con_info->fOpt_level = data;
    }
    
    con_info->fAnswercode = MHD_HTTP_OK;
    
    return MHD_YES;
    
}

// Callback when connection is ended
void Server::request_completed(void *cls, MHD_Connection *connection, void **con_cls, MHD_RequestTerminationCode toe){
    
    struct connection_info_struct *con_info = (connection_info_struct*)*con_cls;
    
    if (NULL == con_info) {
        return;
    }
    
    if (con_info->fConnectiontype == POST) {
        
        if (NULL != con_info->fPostprocessor)
            MHD_destroy_post_processor(con_info->fPostprocessor);
        if(con_info->fNumCompilOptions != 0)
            delete[] con_info->fCompilationOptions;
    }
    
    delete con_info;
    *con_cls = NULL;
}

// Create DSP Factory 
bool Server::compile_Data(connection_info_struct* con_info){
    
    int factoryIndex = getSmallestIndexAvailable();

    const char* compilationOptions[con_info->fNumCompilOptions];
    
    for(int i=0; i<con_info->fNumCompilOptions; i++)
        compilationOptions[i] = con_info->fCompilationOptions[i].c_str();
    
    slave_dsp_factory* realFactory = createSlaveDSPFactory(con_info->fNumCompilOptions, compilationOptions, con_info->fNameApp, con_info->fFaustCode, atoi(con_info->fOpt_level.c_str()), factoryIndex, con_info->fAnswerstring);
    
    if(realFactory){
    
        fAvailableFactories[factoryIndex] = realFactory;
        return true;
    }
    else
        return false;
}

// Create DSP Instance
bool Server::createInstance(connection_info_struct* con_info){
    
//    printf("CREATEINSTANCE WITH INDEX= %s\n", con_info->factoryIndex.c_str());
    
    slave_dsp_factory* realFactory = fAvailableFactories[atoi(con_info->fFactoryIndex.c_str())];
    
    if(realFactory != NULL){
        
        slave_dsp* dsp = createSlaveDSPInstance(realFactory, con_info->fCV, con_info->fIP, con_info->fPort, con_info->fMTU, con_info->fLatency, this);
        
        pthread_t myNewThread;
        
        if(!pthread_create(&myNewThread, NULL, &Server::start_audioSlave, dsp))
            return true;
        else{
            con_info->fAnswerstring = "ERROR = Impossible to create new audio thread in server";
            return false;
        }
    }
    else{
        con_info->fAnswerstring = "ERROR = Factory not found";
        return false;
    }    
}

//------------------------REGISTRATION TO DISCOVERY SYSTEM

string searchIP(){
    
    char host_name[256];
    gethostname(host_name, sizeof(host_name));
    
    struct hostent* host = gethostbyname(host_name);
    
    if(host){
        
        for(int i=0; host->h_addr_list[i] != 0; i++){
            struct in_addr addr;
            memcpy(&addr, host->h_addr_list[i], sizeof(struct in_addr));
            return string(inet_ntoa(addr));
        }
    }
    
    return "";
}

// Register server as available
void Server::registration(){
    
    printf("SERVICE REGISTRATION\n");
    
    char host_name[256];
    gethostname(host_name, sizeof(host_name));
    
    stringstream p;
    p<<fPort;
    
    string nameService = "FaustCompiler._";
    
    nameService += searchIP();
    nameService += ":";
    nameService += p.str();
    nameService += "._";
    nameService += host_name;
    
    if(DNSServiceRegister(fRegistrationService, kDNSServiceFlagsAdd, 0, nameService.c_str(), "_http._tcp", "local", NULL, 7779, 0, NULL, NULL, NULL ) != kDNSServiceErr_NoError)
        printf("ERROR DURING REGISTRATION\n");
}




