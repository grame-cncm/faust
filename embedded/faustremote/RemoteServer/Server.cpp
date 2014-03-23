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

#include <openssl/sha.h>

#include "faust/gui/meta.h"
#include "faust/gui/jsonfaustui.h"

enum{
    ERROR_FACTORY_NOTFOUND,
    ERROR_INSTANCE_NOTCREATED
};

// Declare is called for every metadata coded in the faust DSP
// That way, we get the faust name declared in the faust DSP
struct myMeta : public Meta
{
    string name;
    
    virtual void declare(const char* key, const char* value){
        if(strcmp(key, "name") == 0) {
            name = value;
        }
    }
};


//------------SLAVE DSP FACTORY-------------------------------

// Same Allocation/Desallcation Prototype as LLVM/REMOTE-DSP
slave_dsp_factory* createSlaveDSPFactory(const vector<string>& options, const string& name_app, const string& faust_content, int opt_level, string& answer){
    
    slave_dsp_factory* newFactory = new slave_dsp_factory;
    
    if (newFactory->init(options, name_app, faust_content, opt_level, answer)) {
        return newFactory;
    } else {
        return NULL;
    }
}

void deleteSlaveDSPFactory(slave_dsp_factory* smartPtr){
    
    if(smartPtr->delete_Factory())
        delete smartPtr;
}

string slave_dsp_factory::getJson(const string& factoryKey){
    
    myMeta metadata;
    metadataDSPFactory(fLLVMFactory, &metadata);
    fNameApp = metadata.name;
        
    //This instance is used only to build json interface, then it's deleted
    llvm_dsp* dsp = createDSPInstance(fLLVMFactory);
        
    httpdfaust::jsonfaustui json(fNameApp.c_str(), "", 0);
    dsp->buildUserInterface(&json);
    json.numInput(dsp->getNumInputs());
    json.numOutput(dsp->getNumOutputs());
    json.declare("factoryKey", factoryKey.c_str());
    
    printf("JSON = %s\n", json.json().c_str());
        
    string answer = json.json();
        
    deleteDSPInstance(dsp);
    
    fNumInstances = 1;
    
    return answer;
}

// Creation of real LLVM DSP FACTORY 
// & Creation of intermediate DSP Instance to get json interface
bool slave_dsp_factory::init(const vector<string>& options, const string& name_app, const string& faust_content, int opt_level, string& error){
    
    printf("NAMEAPP = %s | faust_content = %s", name_app.c_str(), faust_content.c_str());
    
    int argc = options.size();
    const char* argv[argc];
    
    for(int i=0; i<argc; i++){
        argv[i] = options[i].c_str();
    }
   
    for(int i=0; i<argc; i++)
        printf("argv = %s\n", argv[i]);
    
    fLLVMFactory = createDSPFactoryFromString(name_app, faust_content, argc, argv, "", error, opt_level);
    
    printf("%s\n", error.c_str());
    
    return (fLLVMFactory != 0);
}

// "Smart" Desallocation of factory depending on its running instances
bool slave_dsp_factory::delete_Factory(){
    
    fNumInstances--;
    
    if(fNumInstances == 0){
        deleteDSPFactory(fLLVMFactory);
        return true;
    } else {
        return false;
    }
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


bool slave_dsp::start_audio(){
    return fAudio->start();
}

void slave_dsp::stop_audio(){
    fAudio->stop();
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
    } else {
        return false;
    }
}

void Server::stop(){
   
    if (fDaemon) {
        
        string nameService;
        
        nameService = searchIP();
        nameService += ".RemoteProcessing";
        
//      Is it really important to unregister or is it automatic ?
        DNSServiceRegister(fRegistrationService, 0, 0, nameService.c_str(), "_http._tcp", "local", NULL, 7779, 0, NULL, NULL, NULL);
        DNSServiceRefDeallocate(*fRegistrationService);
        MHD_stop_daemon(fDaemon);
    }
    
    fDaemon = 0;
}

//---- Callback of another thread to wait netjack audio connection without blocking the server
void* Server::start_audioSlave(void *arg ){
    
    slave_dsp* dspToStart = (slave_dsp*) arg;
    
    if(dspToStart->fServer->fLocker.Lock()){
        
        bool success = false;
        
        dspToStart->fAudio = new server_netjackaudio(atoi(dspToStart->fCV.c_str()), 
                                                      dspToStart->fIP, 
                                                      atoi(dspToStart->fPort.c_str()), 
                                                      DEFAULT_MTU, 
                                                      atoi(dspToStart->fLatency.c_str()));
        
        if (dspToStart->fAudio->init(dspToStart->fSlaveFactory->fNameApp.c_str(), dspToStart->fDSP)) {
            if (!dspToStart->fAudio->start())
                printf("Start slave audio failed\n");
            else{
                printf("SLAVE WITH %i INPUTS || %i OUTPUTS\n", dspToStart->fDSP->getNumInputs(), dspToStart->fDSP->getNumOutputs());
                dspToStart->fServer->fRunningDsp.push_back(dspToStart);
                success = true;
            }
        }
        else
            printf("Init slave audio failed\n");
        
        if(!success)
            deleteSlaveDSPInstance(dspToStart);
            
        dspToStart->fServer->fLocker.Unlock();
    }
    return NULL;
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
        } else {
            it++;
        }
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
    } else {
        con_info->fConnectiontype = GET;
    }

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
        } else {
            return MHD_NO;
        }
    }
    
// Once connection struct is allocated, the request is treated
    if (0 == strcmp(method, "GET")) {
        return server->answer_get(connection);
    
    } else if (0 == strcmp(method, "POST")) {
        return server->answer_post(connection, url, upload_data, upload_data_size, con_cls);
    
    } else {
        return server->send_page(connection, "", 0, MHD_HTTP_BAD_REQUEST, "text/html");
    }
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
    } else {
        
        if(strcmp(url, "/GetJson") == 0){
            
            if (compile_Data(con_info)) {
                return send_page(connection, con_info->fAnswerstring.c_str(), con_info->fAnswerstring.size(), MHD_HTTP_OK, "application/json"); 
            } else {
                return send_page(connection, con_info->fAnswerstring.c_str(), con_info->fAnswerstring.size(), MHD_HTTP_BAD_REQUEST, "text/html");
            }
        }
        else if(strcmp(url, "/CreateInstance") == 0){
            
            if (createInstance(con_info)) {
                return send_page(connection, "", 0, MHD_HTTP_OK, "text/html");
            } else {
                return send_page(connection, con_info->fAnswerstring.c_str(), con_info->fAnswerstring.size(), MHD_HTTP_BAD_REQUEST, "text/html");
            }
            
        }
        else if(strcmp(url, "/DeleteFactory") == 0){
                    
            slave_dsp_factory* toDelete = fAvailableFactories[con_info->fSHAKey];
            
            if (toDelete) {
                
                fAvailableFactories.erase(con_info->fSHAKey);
                deleteSlaveDSPFactory(toDelete);
                
                return send_page(connection, "", 0, MHD_HTTP_OK, "application/html"); 
            } else {
                return send_page(connection, "", 0, MHD_HTTP_BAD_REQUEST, "text/html"); 
            }
        }
        else if(strcmp(url, "/StartAudio") == 0){
            
            startAudio(con_info->fSHAKey);
            return send_page(connection, "", 0, MHD_HTTP_OK, "text/html");
        }
        else if(strcmp(url, "/StopAudio") == 0){
            
            stopAudio(con_info->fSHAKey);
            return send_page(connection, "", 0, MHD_HTTP_OK, "text/html");
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
        
        if(strcmp(key,"factoryKey") == 0)
            con_info->fSHAKey = data;
        
        if(strcmp(key,"instanceKey") == 0)
            con_info->fInstanceKey = data;
        
        if(strcmp(key,"options") == 0)
            con_info->fCompilationOptions.push_back(string(data));
        
        if(strcmp(key,"opt_level") == 0)
            con_info->fOptLevel = data;
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
        
        if (NULL != con_info->fPostprocessor) {
            MHD_destroy_post_processor(con_info->fPostprocessor);
        }
    }
    
    delete con_info;
    *con_cls = NULL;
}

// Start/Stop DSP Instance from its SHAKEY
bool Server::startAudio(const string& shakey){
    
    list<slave_dsp*>::iterator it;
    
    for(it = fRunningDsp.begin(); it != fRunningDsp.end(); it++){
        
        if(shakey.compare((*it)->key())==0){
            if((*it)->start_audio()) {
                return true;
            }
        }
    }

    return false;
}

void Server::stopAudio(const string& shakey){
    
    list<slave_dsp*>::iterator it;
    
    for(it = fRunningDsp.begin(); it != fRunningDsp.end(); it++){
        
        if(shakey.compare((*it)->key())==0){
            (*it)->stop_audio();
        }
    }
}

// Create DSP Factory 
bool Server::compile_Data(connection_info_struct* con_info){
    
//  Sort out compilation options
    vector<string> newOptions = reorganizeCompilationOptions(con_info->fCompilationOptions);
     
    string_and_exitstatus structure = generate_sha1(con_info->fFaustCode, newOptions, con_info->fOptLevel);
    
    if(!structure.exitstatus){
        
        string factoryKey = structure.str;
        slave_dsp_factory* realFactory;
        
//      Recycle factory if it is already compiled
        realFactory = fAvailableFactories[factoryKey];
        
        printf("Server::compile_Data SHAKEY = %s\n", factoryKey.c_str());
        
        if(realFactory == NULL){
            
            realFactory = createSlaveDSPFactory(newOptions, con_info->fNameApp, con_info->fFaustCode, atoi(con_info->fOptLevel.c_str()), con_info->fAnswerstring);
            
            if(realFactory)
                fAvailableFactories[factoryKey] = realFactory;
            else
                return false;
        }  
        
//      Once the factory is compiled, the json is stored as answerstring
        con_info->fAnswerstring = realFactory->getJson(factoryKey);
        return true;
    }
    else{
        con_info->fAnswerstring = "Impossible to generate SHA1 key";
        return false;
    }
}

// Create DSP Instance
bool Server::createInstance(connection_info_struct* con_info){
    
//    printf("CREATEINSTANCE WITH INDEX= %s\n", con_info->factoryIndex.c_str());
    
    slave_dsp_factory* realFactory = fAvailableFactories[con_info->fSHAKey];
    
    if(realFactory != NULL){
        
        printf("Instance\n");
        
        slave_dsp* dsp = createSlaveDSPInstance(realFactory, con_info->fCV, con_info->fIP, con_info->fPort, con_info->fMTU, con_info->fLatency, this);
        
        pthread_t myNewThread;
        
        if(dsp && !pthread_create(&myNewThread, NULL, &Server::start_audioSlave, dsp)){
            dsp->setKey(con_info->fInstanceKey);
            return true;
        } else {
            stringstream s;
            s<<ERROR_INSTANCE_NOTCREATED;
            
            con_info->fAnswerstring = s.str();
            return false;
        }
    } else {
        
        stringstream s;
        s<<ERROR_FACTORY_NOTFOUND;
        
        con_info->fAnswerstring = s.str();
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
    
    string nameService = "._";
    
    nameService += searchIP();
    nameService += ":";
    nameService += p.str();
    nameService += "._";
    nameService += host_name;
    
    if (DNSServiceRegister(fRegistrationService, kDNSServiceFlagsAdd, 0, nameService.c_str(), "_faustcompiler._tcp", "local", NULL, 7779, 0, NULL, NULL, NULL) != kDNSServiceErr_NoError) {
        printf("ERROR DURING REGISTRATION\n");
    }
}

/*
 * Generates an SHA-1 key for Faust file or archive and returns 0 for success
 * or 1 for failure along with the key in the string_and_exitstatus structure.
 * If the evaluation fails, the appropriate error message is set. More info
 * on the con_info structure is in Server.h.
 */

string_and_exitstatus Server::generate_sha1(const string& faustCode, const vector<string>& options, const string& opt_value)
{
    string source(faustCode);
  
    for(int i = 0; i < options.size(); i++){
        source += " "; 
        source += options[i];
    }
    
    source += opt_value;
    
    string hash = "";
    
    unsigned char obuf[20];
    
    SHA1((const unsigned char *)(source.c_str()), source.length(), obuf);
    char buffer[20];
    stringstream ss;
    
    for (int i=0; i < 20; i++) {
        sprintf(buffer, "%02x", obuf[i]);
        ss << buffer;
    }
    
    hash = ss.str();
    
    string_and_exitstatus res;
    res.exitstatus = hash.length() == 40 ? 0 : 1;
    
    printf("EXIT STATUS = %i\n", res.exitstatus);
    
    res.str = hash;
    
    return res;
}

//Look for 'key' in 'options' and modify the parameter 'position' if found
bool Server::parseKey(vector<string> options, const string& key, int& position){
    
    for(int i=0; i<options.size(); i++){
        
        if(key.compare(options[i]) == 0){
            position = i;
            return true;
        }
    }
    
    return false;
}

//Add 'key' if existing in 'options', otherwise add 'defaultKey' (if different from "")
//#return true if 'key' was added
bool Server::addKeyIfExisting(vector<string>& options, vector<string>& newoptions, const string& key, const string& defaultKey, int& position){
      
    if(parseKey(options, key, position)){        
        newoptions.push_back(options[position]);
        options.erase(options.begin()+position);
        position--;
        return true;
    }
    else if(defaultKey.compare("") != 0)
        newoptions.push_back(defaultKey);

    return false;
}

//Add 'key' & it's associated value if existing in 'options', otherwise add 'defaultValue' (if different from "")
void Server::addKeyValueIfExisting(vector<string>& options, vector<string>& newoptions, const string& key, const string& defaultValue){
    
    int position = 0;
    
    if(addKeyIfExisting(options, newoptions, key, "", position)){

        if(position+1<options.size() && options[position+1][0] != '-'){
            newoptions.push_back(options[position+1]);
            options.erase(options.begin()+position+1);
            position--;
        }
        else
            newoptions.push_back(defaultValue);
    }
}

/* Reorganizes the compilation options
 * Following the tree of compilation (Faust_Compilation_Options.pdf in distribution)
 */
vector<string> Server::reorganizeCompilationOptions(vector<string>& options){
    
    bool vectorize = false;
    int position = 0;
    
    vector<string> newoptions;
    
//------STEP 1 - Single or Double ?
    
    addKeyIfExisting(options, newoptions, "-double", "-single", position);

//------STEP 2 - Options Leading to -vec inclusion
    if(addKeyIfExisting(options, newoptions, "-sch", "", position))
        vectorize = true;
        
    if(addKeyIfExisting(options, newoptions, "-omp", "", position)){
        vectorize = true;
        addKeyIfExisting(options, newoptions, "-pl", "", position);
    }
    
    if(vectorize)
        newoptions.push_back("-vec");
    
//------STEP3 - Add options depending on -vec/-scal option
    if(vectorize || addKeyIfExisting(options, newoptions, "-vec", "", position)){

        addKeyIfExisting(options, newoptions, "-dfs", "", position);
        addKeyIfExisting(options, newoptions, "-vls", "", position);
        addKeyIfExisting(options, newoptions, "-fun", "", position);
        addKeyIfExisting(options, newoptions, "-g", "", position);
        addKeyValueIfExisting(options, newoptions, "-vs", "32");
        addKeyValueIfExisting(options, newoptions, "-lv", "0");
    }
    else{
        addKeyIfExisting(options, newoptions, "-scal", "-scal", position);
        addKeyIfExisting(options, newoptions, "-inpl", "", position);
    }
    
    addKeyIfExisting(options, newoptions, "-mcd", "", position);
    
//------STEP4 - Add other types of Faust options
    
    addKeyIfExisting(options, newoptions, "-tg", "", position);
    addKeyIfExisting(options, newoptions, "-sg", "", position);
    addKeyIfExisting(options, newoptions, "-ps", "", position);    
    addKeyIfExisting(options, newoptions, "-svg", "", position);    
    
    if(addKeyIfExisting(options, newoptions, "-mdoc", "", position)){
        addKeyValueIfExisting(options, newoptions, "-mdlang", "");
        addKeyValueIfExisting(options, newoptions, "-stripdoc", "");
    }
    
    addKeyIfExisting(options, newoptions, "-sd", "", position);
    addKeyValueIfExisting(options, newoptions, "-f", "25");
    addKeyValueIfExisting(options, newoptions, "-mns", "40"); 
    addKeyIfExisting(options, newoptions, "-sn", "", position);
    addKeyIfExisting(options, newoptions, "-xml", "", position);
    addKeyIfExisting(options, newoptions, "-blur", "", position);    
    addKeyIfExisting(options, newoptions, "-lb", "", position);
    addKeyIfExisting(options, newoptions, "-mb", "", position);
    addKeyIfExisting(options, newoptions, "-rb", "", position);    
    addKeyIfExisting(options, newoptions, "-lt", "", position);    
    addKeyValueIfExisting(options, newoptions, "-mcd", "16");
    addKeyValueIfExisting(options, newoptions, "-a", "");
    addKeyIfExisting(options, newoptions, "-i", "", position);
    addKeyValueIfExisting(options, newoptions, "-cn", "");    
    addKeyValueIfExisting(options, newoptions, "-t", "120");
    addKeyIfExisting(options, newoptions, "-time", "", position);
    addKeyValueIfExisting(options, newoptions, "-o", "");
    addKeyValueIfExisting(options, newoptions, "-lang", "cpp");
    addKeyIfExisting(options, newoptions, "-flist", "", position);
    addKeyValueIfExisting(options, newoptions, "-l", "");
    addKeyValueIfExisting(options, newoptions, "-O", "");
    
//-------Add Other Options that are possibily passed to the compiler (-I, -blabla, ...)
    while(options.size() != 0){
        newoptions.push_back(options[0]);
        options.erase(options.begin());
    }
    
    return newoptions;
}




