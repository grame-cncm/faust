//
//  Server.cpp
//
//  Created by Sarah Denoux on 13/05/13.
//  Copyright (c) 2013 GRAME. All rights reserved.
//
//

#include "remote_server.h"
#include "utilities.h"
#include "rn_base64.h"
#include "faust/gui/meta.h"
#include "faust/gui/JSONUI.h"

#include "faust/dsp/poly-dsp.h"
//#include "faust/midi/RtMidi.cpp"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#ifdef __APPLE__
#include <dns_sd.h>

// For iOS specific compilation
#if __IPHONE_OS_VERSION_MIN_REQUIRED >= 50000
#define IOSAUDIO 1
#else
#define COREAUDIO 1
#endif

#endif

#ifdef __linux__
#define JACK 1
#endif

//#define JACK 1
//#define COREAUDIO 1
//#define PORTAUDIO 1
//#define IOSAUDIO 1
//#define ANDROID 1

#ifdef NETJACK
#include "faust/audio/netjack-dsp.h"
#endif

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

static string builtError(int error)
{
    stringstream s; s << error;
    return s.str();
}

//--------------SLAVE DSP INSTANCE-----------------------------

// NetJack slave client

#ifdef NETJACK
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
    
        netjack_dsp(dsp_factory* factory, 
                    const string& compression, 
                    const string& ip, const string& port, 
                    const string& mtu, const string& latency,
                    const string& name, const string& key,
                    const string& poly, const string& voices, const string& group,
                    createInstanceDSPCallback cb1, void* cb1_arg,
                    deleteInstanceDSPCallback cb2, void* cb2_arg);
                    
        virtual ~netjack_dsp() {}
        
        bool init(int u1, int u2);
       
        bool isActive() { return dynamic_cast<netjackaudio_slave*>(fAudio)->is_connexion_active(); }

};

netjack_dsp::netjack_dsp(dsp_factory* factory, 
                        const string& compression, 
                        const string& ip, 
                        const string& port, 
                        const string& mtu, 
                        const string& latency,
                        const string& name,
                        const string& key,
                        const string& poly, 
                        const string& voices,
                        const string& group,
                        createInstanceDSPCallback cb1, void* cb1_arg,
                        deleteInstanceDSPCallback cb2, void* cb2_arg)
                        :audio_dsp(factory, atoi(poly.c_str()), atoi(voices.c_str()), atoi(group.c_str()), 
                        false, false, false,
                        name, key, cb1, cb1_arg, cb2, cb2_arg), fIP(ip), 
                        fPort(port), fCompression(compression), 
                        fMTU(mtu), fLatency(latency)
{}

bool netjack_dsp::init(int u1, int u2)
{
    netjackaudio_slave* netjack_slave = new netjackaudio_slave(atoi(fCompression.c_str()), 
                                                                fIP, 
                                                                atoi(fPort.c_str()), 
                                                                atoi(fMTU.c_str()), 
                                                                atoi(fLatency.c_str()));
    fAudio = netjack_slave;
    
    // If Polyphonic DSP, setup a MIDI interface
#ifdef MIDICTRL
    mydsp_poly* poly = dynamic_cast<mydsp_poly*>(fDSP);
    if (poly) {
        netjack_slave->addMidiIn(poly);
        fMidiUI = new MidiUI(netjack_slave);
        fDSP->buildUserInterface(fMidiUI);
        fMidiUI->run();
    }
#endif
                                        
    if (!fAudio->init(fName.c_str(), fDSP)) {
        printf("netjack_dsp : init audio failed\n");
        return false;
    } else {
        return true;
    }
}
#endif

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
    #ifdef OSCCTRL
        if (fOSCUI)     { fOSCUI->run(); }
    #endif
    #ifdef HTTPCTRL
        if (fHttpdUI)   { fHttpdUI->run(); }
    #endif
    #ifdef MIDICTRL
        if (fMidiUI)    { fMidiUI->run(); }
    #endif
        return true;
    }
}

audio_dsp::audio_dsp(dsp_factory* factory, bool poly, int voices, bool group, 
                    bool osc, bool httpd, bool midi, 
                    const string& name, const string& key, 
                    createInstanceDSPCallback cb1, void* cb1_arg,
                    deleteInstanceDSPCallback cb2, void* cb2_arg)
                    :fName(name), fInstanceKey(key), fAudio(NULL), 
                    fCreateDSPInstanceCb(cb1), fCreateDSPInstanceCb_arg(cb1_arg),
                    fDeleteDSPInstanceCb(cb2), fDeleteDSPInstanceCb_arg(cb2_arg)
{
    dsp* dsp = factory->createDSPInstance();
    if (!dsp) {
        throw -1;
    }
    
    if (poly) {
        fDSP = new mydsp_poly(dsp, voices, true, group);
    } else {
        fDSP = dsp;
    }
    
#ifdef OSCCTRL
    if (osc) {
        fOSCUI = new OSCUI(name.c_str(), 0, NULL);
        fDSP->buildUserInterface(fOSCUI);
    } else {
        fOSCUI = 0;
    }
#endif
  
#ifdef HTTPCTRL
    if (httpd) {
        fHttpdUI = new httpdUI(name.c_str(), fDSP->getNumInputs(),fDSP->getNumOutputs(), 0, NULL);
        fDSP->buildUserInterface(fHttpdUI);
        fHttpdUI->run();
    } else {
        fHttpdUI = 0;
    }
#endif
    
#ifdef MIDICTRL
    if (midi) {
        //fMidiUI = new MidiUI();
        //fDSP->buildUserInterface(fMidiUI);
        fMidiUI = 0;
    } else {
        fMidiUI = 0;
    }
 #endif
   
    if (fCreateDSPInstanceCb) {
        fCreateDSPInstanceCb(fDSP, fCreateDSPInstanceCb_arg);
    }
}
 
audio_dsp::~audio_dsp()
{   
    if (fDeleteDSPInstanceCb) {
        fDeleteDSPInstanceCb(fDSP, fDeleteDSPInstanceCb_arg);
    }
    
    delete fAudio;
    delete fDSP;
  
#ifdef OSCCTRL
    delete fOSCUI;
#endif
#ifdef HTTPCTRL
    delete fHttpdUI;
#endif
#ifdef MIDICTRL
    delete fMidiUI;
#endif
}

//------------ CONNECTION INFO -------------------------------

dsp_server_connection_info::dsp_server_connection_info() 
    :fAnswercode(-1), fAnswer(""), fNameApp(""), fFaustCode(""),
     fTarget(""), fOptLevel(""), fIP(""), fPort(""), fCompression(""),
     fMTU(""), fLatency(""), fSHAKey(""), fInstanceKey(""), 
     fPoly(""), fVoices(""), fGroup(""),
     fOSC(""), fHTTPD(""), fMIDI("")
{}

void dsp_server_connection_info::getJson(dsp_factory* factory) 
{
    fNameApp = factory->getName();
    // Those instances are only used to build JSON interface, then they are deleted
    dsp* tmp_dsp;
    
    if (atoi(fPoly.c_str())) {
        tmp_dsp = new mydsp_poly(factory->createDSPInstance(), atoi(fVoices.c_str()), true, atoi(fGroup.c_str()));
    } else {
        tmp_dsp = factory->createDSPInstance();
    }
   
    string code = factory->getDSPCode();
    JSONUI json(fNameApp,
                tmp_dsp->getNumInputs(),
                tmp_dsp->getNumOutputs(),
                factory->getSHAKey(),
                base64_encode(code.c_str(), int(code.size())),
                "", "", "", std::map<std::string, int>());
    tmp_dsp->metadata(&json);
    tmp_dsp->buildUserInterface(&json);
    delete tmp_dsp;
   
    fAnswer = json.JSON();    
}

bool dsp_server_connection_info::getFactoryFromSHAKey(DSPServer* server)
{
    // Will increment factory reference counter...
#ifdef LLVM_DSP_FACTORY
    dsp_factory* factory = getDSPFactoryFromSHAKey(fSHAKey);
#else
    dsp_factory* factory = getInterpreterDSPFactoryFromSHAKey(fSHAKey);
#endif
    
    if (factory) {
        getJson(factory);
        return true;
    } else {
        fAnswer = "Factory not found";
        return false;
    }
}

// Create DSP Factory 
dsp_factory* dsp_server_connection_info::crossCompileFactory(DSPServer* server, string& error) 
{
    dsp_factory* factory;
  
    // Already in the cache...
#ifdef LLVM_DSP_FACTORY
    if ((factory = getDSPFactoryFromSHAKey(fSHAKey))) {
#else
    if ((factory = getInterpreterDSPFactoryFromSHAKey(fSHAKey))) {
#endif
        return factory;
    } else {
        // Sort out compilation options
        int argc = int(fCompilationOptions.size());
        const char* argv[argc];
        for (int i = 0; i < argc; i++) {
            argv[i] = fCompilationOptions[i].c_str();
        }
   
        string error1;
    #ifdef LLVM_DSP_FACTORY
        factory = createDSPFactoryFromString(fNameApp, fFaustCode, argc, argv, fTarget, error1, atoi(fOptLevel.c_str()));
    #else
        factory = createInterpreterDSPFactoryFromString(fNameApp, fFaustCode, argc, argv, error1);
    #endif
        
        error = error1;                                                    
        if (factory && server->fCreateDSPFactoryCb) {
            // Possibly call callback
            server->fCreateDSPFactoryCb(factory, server->fCreateDSPFactoryCb_arg);
        } 
        return factory;
    }
}

// Create DSP Factory 
dsp_factory* dsp_server_connection_info::createFactory(DSPServer* server, string& error) 
{
    // Sort out compilation options
    int argc = fCompilationOptions.size();
    const char* argv[argc];
    for (int i = 0; i < argc; i++) {
        argv[i] = fCompilationOptions[i].c_str();
    }
    
    dsp_factory* factory = NULL;
     
    if (isopt(argc, argv, "-lm")) {
        // Machine code
    #ifdef LLVM_DSP_FACTORY
        factory = readDSPFactoryFromMachine(fFaustCode, loptions(argv, "-lm", ""));
    #else
        factory = readInterpreterDSPFactoryFromMachine(fFaustCode);
    #endif
    } else {
        // DSP code
        string error1;
        
    #ifdef LLVM_DSP_FACTORY
        factory = createDSPFactoryFromString(fNameApp,fFaustCode, argc, argv, "", error, atoi(fOptLevel.c_str()));
    #else
        factory = createInterpreterDSPFactoryFromString(fNameApp, fFaustCode, argc, argv, error);
    #endif
        error = error1;
    }
    
    if (factory && server->fCreateDSPFactoryCb) {
        // Possibly call callback
        server->fCreateDSPFactoryCb(factory, server->fCreateDSPFactoryCb_arg);
    } 
   
    return factory;
}

int dsp_server_connection_info::iteratePost(const char* key, const char* data, size_t size) 
{
    if (size > 0) {
        if (strcmp(key, "name") == 0) {
            fNameApp += nameWithoutSpaces(data);
            if (fNameApp == "") {
                fNameApp = "RemoteDSPServer_DefaultName";
            }
        } else if (strcmp(key, "audio_type") == 0) {
            fAudioType = data;
        } else if (strcmp(key, "dsp_data") == 0) {
            fFaustCode += data;  // Possibly several post ?
        } else if (strcmp(key,"target") == 0) {
            fTarget = data;  
        } else if (strcmp(key, "NJ_ip") == 0) {
            fIP = data;
        } else if (strcmp(key, "NJ_port") == 0) {
            fPort = data;   
        } else if (strcmp(key, "NJ_latency") == 0) {
            fLatency = data;
        } else if (strcmp(key, "NJ_compression") == 0) {
            fCompression = data;        
        } else if (strcmp(key, "NJ_mtu") == 0) {
            fMTU = data;
        } else if (strcmp(key, "shaKey") == 0) {
            fSHAKey = data;
        } else if (strcmp(key, "instanceKey") == 0) {
            fInstanceKey = data;
        } else if (strcmp(key, "options") == 0) {
            fCompilationOptions.push_back(data);
        } else if (strcmp(key, "opt_level") == 0) {
            fOptLevel = data;
        } else if (strcmp(key, "LA_sample_rate") == 0) {
            fSampleRate = data;
        } else if (strcmp(key, "LA_buffer_size") == 0) {
            fBufferSize = data;
        } else if (strcmp(key, "poly") == 0) {
            fPoly = data;
        } else if (strcmp(key, "voices") == 0) {
            fVoices = data;
        } else if (strcmp(key, "group") == 0) {
            fGroup = data;
        } else if (strcmp(key, "osc") == 0) {
            fOSC = data;
        } else if (strcmp(key, "httpd") == 0) {
            fHTTPD = data;
        } else if (strcmp(key, "midi") == 0) {
            fMIDI = data;
        }  
    }
    
    fAnswercode = MHD_HTTP_OK;
    return MHD_YES;
}

dsp_server_connection_info_post::dsp_server_connection_info_post(MHD_Connection* connection):dsp_server_connection_info()
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

DSPServer::~DSPServer() 
{
    for (FactoryTableIt it = fFactories.begin(); it != fFactories.end(); it++) {
    #ifdef LLVM_DSP_FACTORY
        deleteDSPFactory(dynamic_cast<llvm_dsp_factory*>(*it));
    #else
        deleteInterpreterDSPFactory(dynamic_cast<interpreter_dsp_factory*>(*it));
    #endif
    }
}

// Register server as available
void* DSPServer::registration(void* arg) 
{
    DSPServer* serv = (DSPServer*)arg;
    
    char host_name[256];
    gethostname(host_name, sizeof(host_name));
    
#ifdef LLVM_DSP_FACTORY
    string target = getDSPMachineTarget();
#else
    string target = "Interpreter";
#endif
    
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
        string res = name_service.str();
        lo_send(adress, "/faustcompiler", "is", getpid(), res.c_str());
    }
    
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
        printf("DSPServer::start : MHD_start_daemon failed\n");
        return false;
    }                           

    if (pthread_create(&fThread, NULL, DSPServer::registration, this) != 0) {
        printf("DSPServer::start : pthread_create failed\n");
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
    // Serialize acces to fRunningDsp from possible several starting threads
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
    struct MHD_Response* response = MHD_create_response_from_buffer(page.size(), (void*)page.c_str(), MHD_RESPMEM_PERSISTENT);
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
            dsp->stop();
            delete dsp;
            it = fRunningDsp.erase(it); 
        } else {
            it++;
        }
    }
}

// If connection is new, a connection structure is allocated
int DSPServer::createConnection(MHD_Connection* connection, const char* method, void** con_cls)
{
    dsp_server_connection_info* info = NULL;
    try {
        if (strcmp(method, "POST") == 0) {
            info = new dsp_server_connection_info_post(connection);
        } else {
            info = new dsp_server_connection_info_get();
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
    for (FactoryTableIt it = fFactories.begin(); it != fFactories.end(); it++) {
        dsp_factory* factory = *it;
        //answer << factory->getName() << ":" << factory->getTarget() << " " << factory->getSHAKey() << " ";
        answer << factory->getName() << " " << factory->getSHAKey() << " ";
    }
    return sendPage(connection, answer.str(), MHD_HTTP_OK, "text/plain");
}

bool DSPServer::getFactoryFromSHAKey(MHD_Connection* connection, dsp_server_connection_info* info)
{
    if (info->getFactoryFromSHAKey(this)) {
       return sendPage(connection, info->fAnswer, MHD_HTTP_OK, "application/json"); 
    } else {
        return sendPage(connection, info->fAnswer, MHD_HTTP_BAD_REQUEST, "text/html");
    }
}

bool DSPServer::createFactory(MHD_Connection* connection, dsp_server_connection_info* info)
{
    dsp_factory* factory;
    
    if (info->getFactoryFromSHAKey(this)) {
        return sendPage(connection, info->fAnswer, MHD_HTTP_OK, "application/json");
    } else if ((factory = info->createFactory(this, info->fAnswer))) {
        info->getJson(factory);
        fFactories.insert(factory);
        return sendPage(connection, info->fAnswer, MHD_HTTP_OK, "application/json");
    } else {
         return sendPage(connection, info->fAnswer, MHD_HTTP_BAD_REQUEST, "text/html");
    }
}

bool DSPServer::crossCompileFactory(MHD_Connection* connection, dsp_server_connection_info* info)
{
    dsp_factory* factory;
    
    if ((factory = info->crossCompileFactory(this, info->fAnswer))) {
        fFactories.insert(factory);
        
        // Return machine_code to client, and keep the new compiled target, so that is it "cached"
    #ifdef LLVM_DSP_FACTORY
        string machine_code = writeDSPFactoryToMachine(dynamic_cast<llvm_dsp_factory*>(factory), info->fTarget);
        dsp_factory* new_factory = readDSPFactoryFromMachine(machine_code, info->fTarget);
    #else
        string machine_code = writeInterpreterDSPFactoryToMachine(dynamic_cast<interpreter_dsp_factory*>(factory));
        dsp_factory* new_factory = readInterpreterDSPFactoryFromMachine(machine_code);
    #endif
        
        if (new_factory) {
            fFactories.insert(new_factory);
            if (fCreateDSPFactoryCb) {
                // Possibly call callback
                fCreateDSPFactoryCb(new_factory, fCreateDSPFactoryCb_arg);
            }
        }
        
        return sendPage(connection, machine_code, MHD_HTTP_OK, "text/html");
    } else {
        return sendPage(connection, info->fAnswer, MHD_HTTP_BAD_REQUEST, "text/html");
    }
}

bool DSPServer::createInstance(MHD_Connection* connection, dsp_server_connection_info* info)
{
    if (createInstance(info)) {
        return sendPage(connection, "", MHD_HTTP_OK, "text/html");
    } else {
        return sendPage(connection, info->fAnswer, MHD_HTTP_BAD_REQUEST, "text/html");
    }
}

bool DSPServer::deleteInstance(MHD_Connection* connection, dsp_server_connection_info* info)
{
    if (deleteInstance(info->fInstanceKey)) {
        return sendPage(connection, "", MHD_HTTP_OK, "text/html");
    } else {
        return sendPage(connection, info->fAnswer, MHD_HTTP_BAD_REQUEST, "text/html");
    }
}

bool DSPServer::start(MHD_Connection* connection, dsp_server_connection_info* info)
{
    if (start(info->fInstanceKey)) {
        return sendPage(connection, "", MHD_HTTP_OK, "text/html");
    } else {
        return sendPage(connection, builtError(ERROR_INSTANCE_NOTFOUND), MHD_HTTP_BAD_REQUEST, "text/html");
    }
}

bool DSPServer::stop(MHD_Connection* connection, dsp_server_connection_info* info)
{
    if (stop(info->fInstanceKey)) {
        return sendPage(connection, "", MHD_HTTP_OK, "text/html");
    } else {
        return sendPage(connection, builtError(ERROR_INSTANCE_NOTFOUND), MHD_HTTP_BAD_REQUEST, "text/html");
    }
}

bool DSPServer::deleteFactory(MHD_Connection* connection, dsp_server_connection_info* info)
{
    // Returns the factory (with incremented reference counter)
#ifdef LLVM_DSP_FACTORY
    dsp_factory* factory = getDSPFactoryFromSHAKey(info->fSHAKey);
#else
    dsp_factory* factory = getInterpreterDSPFactoryFromSHAKey(info->fSHAKey);
#endif
    
    if (factory) {
        // Remove from the list
        fFactories.erase(factory);
        // Has to be done twice since getDSPFactoryFromSHAKey has incremented once more...
    #ifdef LLVM_DSP_FACTORY
        deleteDSPFactory(dynamic_cast<llvm_dsp_factory*>(factory));
        deleteDSPFactory(dynamic_cast<llvm_dsp_factory*>(factory));
    #else
        deleteInterpreterDSPFactory(dynamic_cast<interpreter_dsp_factory*>(factory));
        deleteInterpreterDSPFactory(dynamic_cast<interpreter_dsp_factory*>(factory));
    #endif
        return sendPage(connection, "", MHD_HTTP_OK, "text/html");
    } else {
        return sendPage(connection, builtError(ERROR_FACTORY_NOTFOUND), MHD_HTTP_BAD_REQUEST, "text/html");
    }
}

// Response to all POST request
// 3 requests are correct : 
// - /CreateFactory --> Receive Faust code / Compile Data / Send back JSON Interface
// - /CreateInstance --> Receive factoryIndex / Create instance 
// - /DeleteFactory --> Receive factoryIndex / Delete factory
int DSPServer::answerPost(MHD_Connection* connection, const char* url, const char* upload_data, size_t* upload_data_size, void** con_cls)
{
    dsp_server_connection_info* info = (dsp_server_connection_info*)*con_cls;
    
    if (*upload_data_size != 0) {
        return info->postProcess(upload_data, upload_data_size);
    } else {
        
        if (strcmp(url, "/CreateFactory") == 0) {
            return createFactory(connection, info);
        } else if (strcmp(url, "/CrossCompileFactory") == 0) {
            return crossCompileFactory(connection, info);
        } else if (strcmp(url, "/GetFactoryFromSHAKey") == 0) {
            return getFactoryFromSHAKey(connection, info);
        } else if(strcmp(url, "/DeleteFactory") == 0) {
            return deleteFactory(connection, info);
        } else if (strcmp(url, "/CreateInstance") == 0) {
            return createInstance(connection, info);
        } else if (strcmp(url, "/DeleteInstance") == 0) {
            return deleteInstance(connection, info);
        } else if (strcmp(url, "/StartInstance") == 0) {
            return start(connection, info);
        } else if(strcmp(url, "/StopInstance") == 0) {
            return stop(connection, info);
        } else {
            return sendPage(connection, "", MHD_HTTP_BAD_REQUEST, "text/html"); 
        }
    }
}

// Callback processing the received data, to be kept in dsp_server_connection_info
int DSPServer::iteratePost(void* coninfo_cls, MHD_ValueKind /*kind*/, 
                            const char* key, 
                            const char* /*filename*/, 
                            const char* /*content_type*/, 
                            const char* /*transfer_encoding*/, 
                            const char* data, 
                            uint64_t /*off*/, 
                            size_t size) {
    
    dsp_server_connection_info* con_info = (dsp_server_connection_info*)coninfo_cls;
    return con_info->iteratePost(key, data, size);
}

// Callback when connection is ended
void DSPServer::requestCompleted(void* cls, MHD_Connection* connection, void** con_cls, MHD_RequestTerminationCode toe) 
{
    dsp_server_connection_info* con_info = (dsp_server_connection_info*)*con_cls;
    delete con_info;
}

// Create DSP Instance
bool DSPServer::createInstance(dsp_server_connection_info* con_info)
{
#ifdef LLVM_DSP_FACTORY
    dsp_factory* factory = getDSPFactoryFromSHAKey(con_info->fSHAKey);
#else
    dsp_factory* factory = getInterpreterDSPFactoryFromSHAKey(con_info->fSHAKey);
#endif

    audio_dsp* audio = NULL;
    dsp* dsp = NULL;
    
    if (factory) {
    
        try {
            if (con_info->fAudioType == "kNetJack") {
                std::cout << con_info->fPoly << " " << con_info->fVoices << " " << con_info->fGroup << std::endl;
            #ifdef NETJACK
                audio = new netjack_dsp(factory, 
                                        con_info->fCompression, 
                                        con_info->fIP, con_info->fPort, 
                                        con_info->fMTU, con_info->fLatency, 
                                        factory->getName(),
                                        con_info->fInstanceKey,
                                        con_info->fPoly, 
                                        con_info->fVoices, 
                                        con_info->fGroup, 
                                        fCreateDSPInstanceCb, fCreateDSPInstanceCb_arg,
                                        fDeleteDSPInstanceCb, fDeleteDSPInstanceCb_arg);
                pthread_t thread;
                AudioStarter* starter = new AudioStarter(this, audio);
                if (pthread_create(&thread, NULL, DSPServer::open, starter) != 0) {
                    goto error;
                }
                
            #endif
            } else if (con_info->fAudioType == "kLocalAudio") {
                
                /*
                 // Steph : 06/15
                if (!(dsp = factory->createDSPInstance())) {
                    return false;
                }
                
                if (fCreateDSPInstanceCb) {
                    fCreateDSPInstanceCb(dsp, fCreateDSPInstanceCb_arg);
                }
                */
                
                audio = new audio_dsp(factory,
                                    atoi(con_info->fPoly.c_str()),
                                    atoi(con_info->fVoices.c_str()),
                                    atoi(con_info->fGroup.c_str()),
                                    atoi(con_info->fOSC.c_str()),
                                    atoi(con_info->fHTTPD.c_str()),
                                    atoi(con_info->fMIDI.c_str()),
                                    factory->getName(),
                                    //getCName(factory),
                                    con_info->fInstanceKey,
                                    fCreateDSPInstanceCb, 
                                    fCreateDSPInstanceCb_arg,
                                    fDeleteDSPInstanceCb, 
                                    fDeleteDSPInstanceCb_arg);
                
                
                //if (audio->init(atoi(con_info->fSampleRate.c_str()), atoi(con_info->fBufferSize.c_str()))) {
                if (audio->init(22050, 1024)) {
                    fRunningDsp.push_back(audio);
                } else {
                    delete audio;
                }
                
            }
        } catch (...) {
             goto error;
        }
    
        // Not more use of the locally needed factory (actually only decrement it's reference counter...)
    #ifdef LLVM_DSP_FACTORY
        deleteDSPFactory(dynamic_cast<llvm_dsp_factory*>(factory));
    #else
        deleteInterpreterDSPFactory(dynamic_cast<interpreter_dsp_factory*>(factory));
    #endif
        return true;
        
    } else {
        con_info->fAnswer = builtError(ERROR_FACTORY_NOTFOUND);
        return false;
    }  
    
error:
    con_info->fAnswer = builtError(ERROR_INSTANCE_NOTCREATED);
    return false;
}

bool DSPServer::deleteInstance(const string& instance_key)
{
    list<audio_dsp*>::iterator it = fRunningDsp.begin();
    
    while (it != fRunningDsp.end()) {
        if (instance_key == (*it)->getKey()) {
            audio_dsp* dsp = *it;
            dsp->stop();
            delete dsp;
            it = fRunningDsp.erase(it); 
            return true;
        } else {
            it++;
        }
    }
    
    return false;
}

// Start/Stop Audio instance from its instancekey
bool DSPServer::start(const string& instance_key)
{
    list<audio_dsp*>::iterator it;
    
    for (it = fRunningDsp.begin(); it != fRunningDsp.end(); it++) {
        if (instance_key == (*it)->getKey()) {
            if ((*it)->start()) {
                return true;
            }
        }
    }

    return false;
}

bool DSPServer::stop(const string& instance_key)
{
    list<audio_dsp*>::iterator it;
    
    for (it = fRunningDsp.begin(); it != fRunningDsp.end(); it++) {
        if (instance_key == (*it)->getKey()) {
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

