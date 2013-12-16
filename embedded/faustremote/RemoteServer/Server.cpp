//
//  FLServerHttp.h
//  
//
//  Created by Sarah Denoux on 13/05/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//
//
// FaustLive can become a server.

#include "Server.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "faust/gui/meta.h"
#include "faust/gui/jsonfaustui.h"

#define POSTBUFFERSIZE 512

#define GET 0
#define POST 1

struct myMeta : public Meta
{
    string name;
    
    virtual void declare(const char* key, const char* value){
        if(strcmp(key, "name") == 0)
            name = value;
    }
};

Slave_DSP_Factory* createSlaveFactory(){
    
    Slave_DSP_Factory* newFactory = new Slave_DSP_Factory;
    newFactory->init();
    
    return newFactory;
}

void deleteSlaveFactory(Slave_DSP_Factory* smartPtr){
    
    if(smartPtr->delete_Factory())
        delete smartPtr;
}

Slave_DSP* createSlaveInstance(Slave_DSP_Factory* smartFactory){
    
    Slave_DSP* newDSP = new Slave_DSP;
    newDSP->init();
    
    newDSP->myDSP = createDSPInstance(smartFactory->factory);
    
    newDSP->factory = smartFactory->clone();
    
    newDSP->controlUI = new ControlUI;
    newDSP->myDSP->buildUserInterface(newDSP->controlUI);
    
    return newDSP;
}

void deleteSlaveInstance(Slave_DSP* smartPtr){
    
    smartPtr->delete_DSP();
    delete smartPtr;
}

Server::Server(){

    fMax_clients = 12;
    fError = "";

//    Server::fNr_of_uploading_clients = 0;
    
    //IL Y AVAIT AUTRE CHOSE
}

Server::~Server(){}
    
const int Server::getMaxClients(){return fMax_clients;}
    
bool Server::start(int port){
    
    fDaemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY,
                               port, 
                               NULL, 
                               NULL, 
                               &answer_to_connection, 
                               this, MHD_OPTION_NOTIFY_COMPLETED, 
                               request_completed, NULL, MHD_OPTION_END);
    
    printf("SERVER STARTED\n");
    
    return fDaemon != NULL;
}

void Server::stop(){
    if (fDaemon) {
        MHD_stop_daemon(fDaemon);
    }
    
    fDaemon = 0;

}

void* Server::start_audioSlave(void *arg ){
    
    pthread_detach(pthread_self());
    
    Slave_DSP* argument = (Slave_DSP*) arg;
    
    if(argument->server->fLocker.Lock()){
        
        printf("AUDIO PARAMS = %s || %s || %s || %s\n",argument->CV.c_str(),  argument->IP.c_str(), argument->Port.c_str(), argument->Latency.c_str());
        
        argument->audio = new netjackaudio_control(atoi(argument->CV.c_str()), argument->IP.c_str(), atoi(argument->Port.c_str()), atoi(argument->Latency.c_str()), argument->controlUI);
        
        if (argument->audio->init(argument->factory->nameApp.c_str(), argument->myDSP)) {
            if (!argument->audio->start())
                printf("AUDIO NOT STARTED\n");
            else
                argument->server->fRunningDsp.push_back(argument);
        }
        else
            printf("AUDIO NOT INIT\n");
        
        argument->server->fLocker.Unlock();
    }
     pthread_exit((void *) 0);
//    return NULL;
}
    
int Server::getSmallestIndexAvailable(){

    map<int, Slave_DSP_Factory*>::iterator it;
    bool found = true;
    int i = 0;
    
    //    printf("current index list = %i\n", FLW_List.size());
    
    while(found && fAvailableFactories.size() != 0){
        i++;
        for (it = fAvailableFactories.begin(); it != fAvailableFactories.end(); it++){
            if(it->first == i){
                found = true;
                break;
            }
            else
                found = false;
        }        
    }
    if(i == 0)
        i=1;
    return i;

}

Slave_DSP_Factory*   Server::getFactoryFromIndex(int factoryIndex){
    
    map<int, Slave_DSP_Factory*>::iterator it;

    for(it = fAvailableFactories.begin(); it != fAvailableFactories.end(); it++){
        if(it->first == factoryIndex)
            return it->second;
    }
    
    return NULL;
}
    
bool Server::createInstance(connection_info_struct* con_info){
    
    printf("CREATEINSTANCE WITH INDEX= %s\n", con_info->factoryIndex.c_str());
    
    Slave_DSP_Factory* realFactory = getFactoryFromIndex(atoi(con_info->factoryIndex.c_str()));
    
    if(realFactory != NULL){
        
        Slave_DSP* myRealDSP = createSlaveInstance(realFactory);
        
        myRealDSP->IP = con_info->IP;
        myRealDSP->Port = con_info->Port;
        myRealDSP->Latency = con_info->Latency;
        myRealDSP->CV = con_info->CV;
        myRealDSP->server = this;
        
        pthread_t myNewThread;
        
        if(!pthread_create(&myNewThread, NULL, &Server::start_audioSlave, myRealDSP))
            return true;
        else{
            con_info->answerstring = "ERROR = Impossible to create new audio thread in server";
            return false;
        }
    }
    else{
        con_info->answerstring = "ERROR = Factory not found";
        return false;
    }
        
}
    
int Server::send_page(MHD_Connection *connection, const char *page, int length, int status_code, const char * type){
    
    int ret;
    struct MHD_Response *response;
    
    response = MHD_create_response_from_buffer(length, (void*)page,
                                               MHD_RESPMEM_PERSISTENT);
    if (!response) {
        return MHD_NO;
    }
    
    MHD_add_response_header(response, "Content-Type", type ? type : "text/plain");
//    cout << "FLServerHttp::send_page " << status_code << endl;
    ret = MHD_queue_response(connection, status_code, response);
    
    return ret;
}

int Server::answer_to_connection	(void *cls, MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls){
   
//    printf("SERVER::Answer to connection = %s\n", url);
    
    Server *server = (Server*)cls;
    
//    ICI ON VÉRIFIE QUE TOUS LES RUNNING DSP TOURNENT RÉELLEMENT 
    list<Slave_DSP*>::iterator it = server->fRunningDsp.begin();
    
    while (it != server->fRunningDsp.end())
    {
        if(!(*it)->audio->is_Connexion_Active()){
            Slave_DSP* toDelete = *it;
            it = server->fRunningDsp.erase(it);
            
            deleteSlaveInstance(toDelete);
        }
        else
            it++;
    }
    
    
    if (NULL == *con_cls) {
        struct connection_info_struct *con_info;
        
//        if (fNr_of_uploading_clients >= server->getMaxClients()) 
//            return server->send_page(connection, "", 0, MHD_HTTP_SERVICE_UNAVAILABLE, "text/html");
        
        con_info = new connection_info_struct();
        con_info->init();
        
        if (NULL == con_info) {
            return MHD_NO;
        }
        
        if (0 == strcmp(method, "POST")) {
            
            con_info->postprocessor = MHD_create_post_processor(connection, POSTBUFFERSIZE, iterate_post, (void*)con_info);
            
            if (NULL == con_info->postprocessor) {
                delete con_info;
                return MHD_NO;
            }
            
//            fNr_of_uploading_clients++;
            
            con_info->connectiontype = POST;
            con_info->answercode = MHD_HTTP_OK;
        }
        
        else {
            con_info->connectiontype = GET;
        }
        
        *con_cls = (void*)con_info;
        
        return MHD_YES;
    }
    
    if (0 == strcmp(method, "GET"))
        return server->answer_get(connection);
    
    if (0 == strcmp(method, "POST"))
        return server->answer_post(connection, url, upload_data, upload_data_size, con_cls);
    else
        return server->send_page(connection, "", 0, MHD_HTTP_BAD_REQUEST, "text/html");
}
    
int Server::answer_get(MHD_Connection* connection){

    return send_page(connection, "", 0, MHD_HTTP_BAD_REQUEST, "text/html");
}
    
int Server::answer_post(MHD_Connection *connection, const char *url, const char *upload_data, size_t *upload_data_size, void **con_cls){


//    printf("POST PROCESSORING\n");
    
    struct connection_info_struct *con_info = (connection_info_struct*)*con_cls;
    
    if (0 != *upload_data_size) {
        
        MHD_post_process(con_info->postprocessor, upload_data, *upload_data_size);
        *upload_data_size = 0;
        
        return MHD_YES;
    } 
    else{
        
        if(strcmp(url, "/GetJson") == 0){
            
            if(compile_Data(con_info))
                return send_page(connection, con_info->answerstring.c_str(), con_info->answerstring.size(), MHD_HTTP_OK, "application/json"); 
            else
                return send_page(connection, con_info->answerstring.c_str(), con_info->answerstring.size(), MHD_HTTP_BAD_REQUEST, "text/html");
        }
        else if(strcmp(url, "/CreateInstance") == 0){
            
            if(createInstance(con_info))
                return send_page(connection, "", 0, MHD_HTTP_OK, "text/html"); 
            else{
                return send_page(connection, con_info->answerstring.c_str(), con_info->answerstring.size(), MHD_HTTP_BAD_REQUEST, "text/html");
            }
            
        }
        else if(strcmp(url, "/DeleteFactory") == 0){
            
            Slave_DSP_Factory* toDelete = getFactoryFromIndex(atoi(con_info->factoryIndex.c_str()));
            fAvailableFactories.erase(atoi(con_info->factoryIndex.c_str()));
            
            deleteSlaveFactory(toDelete);
            
            return send_page(connection, "", 0, MHD_HTTP_OK, "application/html"); 
        }
        else{
            printf("BAD REQUEST\n");
            return send_page(connection, "", 0, MHD_HTTP_BAD_REQUEST, "text/html"); 
    
        }
    }
}

void Server::request_completed(void *cls, MHD_Connection *connection, void **con_cls, MHD_RequestTerminationCode toe){

//    printf("FaustServer::request_completed()\n");
    
    struct connection_info_struct *con_info = (connection_info_struct*)*con_cls;
    
    if (NULL == con_info) {
        return;
    }
    
    if (con_info->connectiontype == POST) {
        if (NULL != con_info->postprocessor) {
            MHD_destroy_post_processor(con_info->postprocessor);
//            fNr_of_uploading_clients--;
        }
    }
    
    free(con_info);
    *con_cls = NULL;

}

int Server::iterate_post(void *coninfo_cls, MHD_ValueKind /*kind*/, const char *key, const char */*filename*/, const char */*content_type*/, const char */*transfer_encoding*/, const char *data, uint64_t /*off*/, size_t size){
    
    struct connection_info_struct *con_info = (connection_info_struct*)coninfo_cls;
    
//    printf("FLServer::iterate_post %s\n", key);
    
    if (size > 0) {
        
        if(strcmp(key,"data") ==0 )
            con_info->data+=data;        
            
        if(strcmp(key,"NJ_IP") ==0 )
            con_info->IP = data;
        
        if(strcmp(key,"NJ_Port") ==0 )
            con_info->Port =data;        
        
        if(strcmp(key,"NJ_Latency") ==0 )
            con_info->Latency = data;
        
        if(strcmp(key,"NJ_Compression") ==0 )
            con_info->CV =data;        
        
        if(strcmp(key,"factoryIndex") ==0 ){
            con_info->factoryIndex = data;
            printf("INDEX = %s\n", data);
        }
        
        if(strcmp(key,"options") ==0 )
            con_info->compilationOptions = data;
        
        if(strcmp(key,"opt_level") ==0 )
            con_info->opt_level = data;
    }
    
    con_info->answercode = MHD_HTTP_OK;
    
    return MHD_YES;
    
}
    
bool Server::compile_Data(connection_info_struct* con_info){

    printf("SERVER::CompileData\n");
    
    int argc = get_numberParameters(con_info->compilationOptions);
    
    char ** argv;
    argv = new char*[argc];
    
    //Parsing the compilationOptions from a string to a char**
    string copy = con_info->compilationOptions;
    
    for(int i=0; i<argc; i++){
        
        string parseResult = parse_compilationParams(copy);
        argv[i] = (char*)parseResult.c_str();
        printf("ARGUMENT = %s\n", argv[i]);
    }

    const char** argument = (const char**) argv;

    Slave_DSP_Factory* realFactory = createSlaveFactory();
    
    string error;
    
    llvm_dsp_factory* factory= createDSPFactory(argc , argument, "", "", "", con_info->data, "", error, atoi(con_info->opt_level.c_str()));
    
    if(factory){
        
        myMeta metadata;
        metadataDSPFactory(factory, &metadata);

        realFactory->nameApp = metadata.name;
        
        realFactory->factory = factory;
        
        //This instance is used only to build json interface, then it's deleted
        llvm_dsp* dsp = createDSPInstance(factory);
        
        int index = getSmallestIndexAvailable();
        
        stringstream s;
        s<<index;
        
        fAvailableFactories.insert(make_pair(index, realFactory));
        
        string nameOfApp(realFactory->nameApp.c_str());
        
        httpdfaust::jsonfaustui json(nameOfApp.c_str(), "", 0);
        dsp->buildUserInterface(&json);
        json.numInput(dsp->getNumInputs());
        json.numOutput(dsp->getNumOutputs());
        json.declare("indexFactory", s.str().c_str());
        
//        printf("JSON = %s\n", json.json());
        
        con_info->answerstring = json.json();
        
        deleteDSPInstance(dsp);
        
        return true;
    }
    else{
        con_info->answerstring = error;
        return false;

    }
}
  
int Server::get_numberParameters(string compilOptions){

    string copy = compilOptions;
    
    int argc = 0;
    int pos = 0;
    
    if(copy.find("-") == string::npos){
        return 0;
    }
    
    while(copy.find(" ", pos+1) != string::npos){
        argc++;
        pos = copy.find(" ", pos+1);
    }
    
    return argc+1;

}

string Server::parse_compilationParams(string& compilOptions){

    string returning = "";
    
    size_t pos = compilOptions.find(" ");
    
    if(pos != string::npos){
        returning = compilOptions.substr(0, pos);
        compilOptions.erase(0, pos+1);
    }
    else if(compilOptions.compare("") != 0)
        returning = compilOptions.substr(0, compilOptions.length());
    
    return returning;

}






