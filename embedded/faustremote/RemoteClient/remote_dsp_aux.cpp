/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2003-2015 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include <sstream>
#include <errno.h>
#include <string.h>
#include <libgen.h>

#include "faust/gui/ControlUI.h"
#include "faust/gui/MidiUI.h"
#include "faust/gui/MidiUI.h"
#include "remote_dsp_aux.h"
#include "libfaust.h"
#include "llvm-dsp.h"
#include "interpreter-dsp.h"
#include "utilities.h"
#include "rn_base64.h"

RemoteFactoryDSPTableType remote_dsp_factory::gRemoteFactoryDSPTable;
LocalFactoryDSPTableType remote_dsp_factory::gLocalFactoryDSPTable;

CURL* remote_dsp_factory::gCurl = NULL;

// Standard Callback to store a server response in stringstream
static size_t storeResponse(void *buf, size_t size, size_t nmemb, void* userp)
{
    ostream* os = static_cast<ostream*>(userp);
    streamsize len = size * nmemb;
    return (os->write(static_cast<char*>(buf), len)) ? len : 0;
}

static bool isInteger(const string& str)
{
    for (size_t i = 0; i < str.size(); i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

//Returns true if no problem encountered
//The response string stores the data received 
//(can be error or real data... depending on return value)
//The errorCode stores the error encoded as INT
static bool sendRequest(const string& url, const string& finalRequest, string& response, int& errorCode)
{
    bool res = false;
    printf("Request = %s and url = %s\n", finalRequest.c_str(), url.c_str());
    
    ostringstream oss;
    curl_easy_setopt(remote_dsp_factory::gCurl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(remote_dsp_factory::gCurl, CURLOPT_POST, 1L);
    curl_easy_setopt(remote_dsp_factory::gCurl, CURLOPT_POSTFIELDSIZE, (long)(finalRequest.size()));
    curl_easy_setopt(remote_dsp_factory::gCurl, CURLOPT_POSTFIELDS, finalRequest.c_str());
    curl_easy_setopt(remote_dsp_factory::gCurl, CURLOPT_WRITEFUNCTION, &storeResponse);
    curl_easy_setopt(remote_dsp_factory::gCurl, CURLOPT_FILE, &oss);
    curl_easy_setopt(remote_dsp_factory::gCurl, CURLOPT_CONNECTTIMEOUT, 5); 
    curl_easy_setopt(remote_dsp_factory::gCurl, CURLOPT_TIMEOUT, 30);
    
    if (curl_easy_perform(remote_dsp_factory::gCurl) != CURLE_OK) {
        printf("curl_easy_perform error\n");
        errorCode = ERROR_CURL_CONNECTION;
    } else {
        
        long respcode; //response code of the http transaction
        curl_easy_getinfo(remote_dsp_factory::gCurl, CURLINFO_RESPONSE_CODE, &respcode);
        string res = oss.str();
        
        if (respcode == 200) {
            response = res;
            res = true;
        } else if (respcode == 400) {
            printf("curl_easy_getinfo error\n");
            
            if (isInteger(res)) {
                errorCode = atoi(res.c_str());
            } else {
                response = res;
            }
        }
    }
     
    return res;
}

//------------------FACTORY

remote_dsp_factory::remote_dsp_factory(const string& ip_server, int port_server, const string& sha_key)
{
    stringstream serverURL;
    serverURL << "http://" << ip_server << ":" << port_server;
    fServerURL = serverURL.str();
    fSHAKey = sha_key;
    fExpandedDSP = "";
    fJSONDecoder = 0;
}

remote_dsp_factory::~remote_dsp_factory()
{
    // The index of the factory to delete has to be sent
    string finalRequest = "shaKey=" + fSHAKey;
    string response;
    int errorCode = -1;
    sendRequest(fServerURL + "/DeleteFactory", finalRequest, response, errorCode);
    
    delete fJSONDecoder;
}

bool remote_dsp_factory::sendFinalRequest(void* obj, const string& cmd)
{
    stringstream finalRequest;
    string response;
    int errorCode = -1;
    
    finalRequest << "instanceKey=" << obj;
    return sendRequest(fServerURL + cmd, finalRequest.str(), response, errorCode);
}

// Compile on server side and get machine code on client to re-create a local Factory
static remote_dsp_factory* crossCompile(int argc, const char* argv[], 
                                        const string& name_app, 
                                        const string& dsp_content,
                                        const string& sha_key,
                                        const string& ip_server, 
                                        int port_server,
                                        string& error_msg,
                                        int opt_level)
{
    stringstream finalRequest;
    stringstream serverURL;
    string response;
    serverURL << "http://" << ip_server << ":" << port_server;
    int errorCode = -1;
    
    // Adding name
    finalRequest << "name=" << name_app;
  
    // Adding Compilation options 
    finalRequest << "&number_options=" << argc;
    for (int i = 0; i < argc; i++) {
        finalRequest << "&options=" << argv[i];
    }
    
    // LLVM optimization level and SHA key
    finalRequest << "&opt_level=" << opt_level << "&shaKey=" << sha_key;  // (opt_level = -1 means 'maximum possible value')
    
    // Machine target
    finalRequest << "&target=" << loptions(argv, "-rm", getDSPMachineTarget().c_str());
    
    // Transforming DSP code to URL format
    char* data_url = curl_easy_escape(remote_dsp_factory::gCurl, dsp_content.c_str(), dsp_content.size());
    finalRequest << "&dsp_data=";
    finalRequest << data_url;
    curl_free(data_url);
    
    string url = serverURL.str() + "/CrossCompileFactory";
   
    if (sendRequest(url, finalRequest.str(), response, errorCode)) {
        llvm_dsp_factory* factory = readDSPFactoryFromMachine(response, getDSPMachineTarget());
        remote_dsp_factory::gLocalFactoryDSPTable.push_back(factory);
        return reinterpret_cast<remote_dsp_factory*>(factory); 
    } else {
        error_msg = response;
        return NULL;
    }
}

// Init remote dsp factory sends a POST request to a remote server
// The URL extension used is /CreateFactory
// The datas have a url-encoded form (key/value separated by & and special character are reencoded like spaces = %)
bool remote_dsp_factory::init(int argc, const char* argv[], 
                            const string& name_app, 
                            const string& dsp_content, 
                            string& error_msg, 
                            int opt_level)
{
    fExpandedDSP = dsp_content;
    stringstream finalRequest;
    string response;
   
    // Adding name
    finalRequest << "name=" << name_app;
    
    // Adding Compilation options 
    finalRequest << "&number_options=" << argc;
    for (int i = 0; i < argc; i++) {
        if ((strcmp(argv[i], "-poly") == 0) 
            || (strcmp(argv[i], "-voices") == 0)
            || (strcmp(argv[i], "-group") == 0)) {
            // Move to next token...
            i++;
        } else {
            finalRequest << "&options=" << argv[i];
        }
    }
    
    // LLVM optimization level and SHA key
    finalRequest << "&opt_level=" << opt_level << "&shaKey=" << fSHAKey;
    
    // Polyphonic support
    fPoly = loptions(argc, argv, "-poly", "0");
    fVoices = loptions(argc, argv, "-voices", "4");
    fGroup = loptions(argc, argv, "-group", "0");
    finalRequest << "&poly=" << fPoly;
    finalRequest << "&voices=" << fVoices;
    finalRequest << "&group=" << fGroup;
   
    // Compile on client side and send machine code on server side
    if (isopt(argc, argv, "-lm")) {
    #ifdef LLVM_DSP_FACTORY
        llvm_dsp_factory* factory = createDSPFactoryFromString(name_app, dsp_content, argc, argv, loptions(argv, "-lm", ""), error_msg, opt_level);
    #else
        interpreter_dsp_factory* factory = createInterpreterDSPFactoryFromString(name_app, dsp_content, argc, argv, error_msg);
    #endif
        if (factory) {
            // Transforming machine code to URL format
        #ifdef LLVM_DSP_FACTORY
            string machine_code = writeDSPFactoryToMachine(factory, "");
        #else
            string machine_code = writeInterpreterDSPFactoryToMachine(factory);
        #endif
            char* data_url = curl_easy_escape(remote_dsp_factory::gCurl, machine_code.c_str(), machine_code.size());
            finalRequest << "&dsp_data=";
            finalRequest << data_url;
            curl_free(data_url);
        #ifdef LLVM_DSP_FACTORY
            deleteDSPFactory(dynamic_cast<llvm_dsp_factory*>(factory));
        #else
            deleteInterpreterDSPFactory(dynamic_cast<interpreter_dsp_factory*>(factory));
        #endif
        } else {
            return false;
        }
    } else {
        // Transforming DSP code to URL format
        char* data_url = curl_easy_escape(remote_dsp_factory::gCurl, dsp_content.c_str(), dsp_content.size());
        finalRequest << "&dsp_data=";
        finalRequest << data_url;
        curl_free(data_url);
    }
    
    // Keep library path
    stringstream os(dsp_content);
    string key, name;                 
    while (os >> key) {               
        os >> name;
        // In the expanded version, line of type 'library_path' has been added before line of type 'declare IP "192.168.1.146";'
        if (key == "IP") {
            break;
        } else if (key == "library_path") {
            fPathnameList.push_back(name);
        }  
    }
    
    int errorCode = -1;
    string url = fServerURL + "/CreateFactory";

    if (sendRequest(url, finalRequest.str(), response, errorCode)) {
        decodeJSON(response);
        return true;
    } else {
        error_msg = response;
        return false;
    }
}

// Decoding JSON from a string to
// fUiItems : Structure containing the graphical items
// fMetadatas : Structure containing the metadatas
// Some "extra" metadatas are kept separatly
void remote_dsp_factory::decodeJSON(const string& json)
{
    fJSONDecoder = new JSONUIDecoder(json);
    
    if (fJSONDecoder->fMetadatas.find("code") != fJSONDecoder->fMetadatas.end()) {
        fExpandedDSP = base64_decode(fJSONDecoder->fMetadatas["code"]);
    }
    
    if (fJSONDecoder->fMetadatas.find("sha_key") != fJSONDecoder->fMetadatas.end()) {
        fSHAKey = fJSONDecoder->fMetadatas["sha_key"];
    }
}

// Declaring meta datas
void remote_dsp_factory::metadataRemoteDSPFactory(Meta* m) 
{ 
    map<string,string>::iterator it;
    for (it = fJSONDecoder->fMetadatas.begin() ; it != fJSONDecoder->fMetadatas.end(); it++) {
        m->declare(it->first.c_str(), it->second.c_str());
    }
}   

// Create Remote DSP Instance from factory
remote_dsp_aux* remote_dsp_factory::createRemoteDSPInstance(int argc, const char* argv[], 
                                                            remoteDSPErrorCallback error_callback, 
                                                            void* error_callback_arg, 
                                                            int& error) 
{
    remote_dsp_aux* dsp = new remote_dsp_aux(this);
    if (dsp->init(argc, argv, error_callback, error_callback_arg, error)) {
        return dsp; 
    } else {
        delete dsp;
        return NULL;
    }
}

remote_audio_aux* remote_dsp_factory::createRemoteAudioInstance(int argc, const char* argv[], int& error) 
{
    remote_audio_aux* audio = new remote_audio_aux(this);
    if (audio->init(argc, argv, error)) {
        return audio; 
    } else {
        delete audio;
        return NULL;
    }
}

//---------FACTORY

static bool isRemoteFactory(const string& sha_key, RemoteFactoryDSPTableIt& res)
{
    RemoteFactoryDSPTableIt it;
    
    for (it = remote_dsp_factory::gRemoteFactoryDSPTable.begin(); it != remote_dsp_factory::gRemoteFactoryDSPTable.end(); it++) {
        Sremote_dsp_factory factory = (*it).first;
        if (factory->getSHAKey() == sha_key) {
            res = it;
            return true;
        }
    }
    
    return false;
}

static bool isLocalFactory(const string& sha_key)
{
    LocalFactoryDSPTableIt it;
    
    for (it = remote_dsp_factory::gLocalFactoryDSPTable.begin(); it != remote_dsp_factory::gLocalFactoryDSPTable.end(); it++) {
        llvm_dsp_factory* factory = *it;
        if (factory->getSHAKey() == sha_key) {
            return true;
        }
    }
    
    return false;
}

static bool isLocalFactory(remote_dsp_factory* factory)
{
    llvm_dsp_factory* llvm_factory = reinterpret_cast<llvm_dsp_factory*>(factory);
    LocalFactoryDSPTableIt it;
    
    for (it = remote_dsp_factory::gLocalFactoryDSPTable.begin(); it != remote_dsp_factory::gLocalFactoryDSPTable.end(); it++) {
        if (llvm_factory == *it) {
            return true;
        }
    }
    
    return false;
}

//--------------------DSP INSTANCE

remote_dsp_aux::remote_dsp_aux(remote_dsp_factory* factory)
{
    fFactory = factory;
    fJSONDecoder = new JSONUIDecoder(factory->fJSONDecoder->fJSON);
    
    fNetJack = 0;
    
    fAudioInputs = new float*[getNumInputs()];
    fAudioOutputs = new float*[getNumOutputs()];
    
    for (int i = 0; i < getNumInputs(); i++) {
        fAudioInputs[i] = 0;
    }
    for (int i = 0; i < getNumOutputs(); i++) {
        fAudioOutputs[i] = 0;
    }
    
    fControlInputs = new float*[2];
    fControlOutputs = new float*[2];
    
    fControlInputs[0] = fControlInputs[1] = 0;
    fControlOutputs[0] = fControlOutputs[1] = 0;
    
    fErrorCallback = 0;
    fErrorCallbackArg = 0;
    
    fRunning = true;
}
        
remote_dsp_aux::~remote_dsp_aux()
{
    fFactory->sendFinalRequest(this, "/DeleteInstance");
    
    if (fNetJack) {
    
        jack_net_master_close(fNetJack); 
        
        delete[] fControlInputs[0];
        delete[] fControlInputs[1];
        delete[] fControlOutputs[0];
        delete[] fControlOutputs[1];
    
        fNetJack = 0;
    }
    
    delete[] fAudioInputs;
    delete[] fAudioOutputs;
    
    delete[] fControlInputs;
    delete[] fControlOutputs;
     
    // Remove 'this' from its factory
    RemoteFactoryDSPTableIt it = remote_dsp_factory::gRemoteFactoryDSPTable.find(fFactory);
    assert(it != remote_dsp_factory::gRemoteFactoryDSPTable.end());
    (*it).second.first.remove(this);
    
    delete fJSONDecoder;
}

void remote_dsp_aux::fillBufferWithZerosOffset(int channels, int offset, int size, FAUSTFLOAT** buffer)
{
    // Cleanup audio buffers only 
    for (int i = 0; i < channels; i++) {
        memset(&buffer[i][offset], 0, sizeof(float)*size);
    }
}

// DecodeJSON to build user interface
void remote_dsp_aux::buildUserInterface(UI* ui) 
{
    MidiUI* midi_ui = dynamic_cast<MidiUI*>(ui);
    if (midi_ui) { 
        midi_ui->addMidiIn(this); 
    } else {
        fJSONDecoder->buildUserInterface(ui);
    }
}

void remote_dsp_aux::setupBuffers(FAUSTFLOAT** input, FAUSTFLOAT** output, int offset)
{
    for (int i = 0; i < getNumInputs(); i++) {
        fAudioInputs[i] = &input[i][offset];
    }
    
    for (int i = 0; i < getNumOutputs(); i++) {
        fAudioOutputs[i] = &output[i][offset];
    }
}

void remote_dsp_aux::sendSlice(int buffer_size) 
{
    if (fRunning && jack_net_master_send_slice(fNetJack, getNumInputs(), fAudioInputs, 2, (void**)fControlInputs, buffer_size) < 0) {
        fillBufferWithZerosOffset(getNumOutputs(), 0, buffer_size, fAudioOutputs);
        if (fErrorCallback) {
            fRunning = (fErrorCallback(ERROR_NETJACK_WRITE, fErrorCallbackArg) == 0);
        }
    }
}

void remote_dsp_aux::recvSlice(int buffer_size)
{
    if (fRunning && jack_net_master_recv_slice(fNetJack, getNumOutputs(), fAudioOutputs, 2, (void**)fControlOutputs, buffer_size) < 0) {
        fillBufferWithZerosOffset(getNumOutputs(), 0, buffer_size, fAudioOutputs);
        if (fErrorCallback) {
            fRunning = (fErrorCallback(ERROR_NETJACK_READ, fErrorCallbackArg) == 0);
        }
    }
}

// Compute of the DSP, adding the controls to the input/output passed
void remote_dsp_aux::compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
{
    if (fRunning) {
        
        // If count > fBufferSize : the cycle is divided in numberOfCycles NetJack cycles, and a lastCycle one
        int numberOfCycles = count/fBufferSize;
        int lastCycle = count%fBufferSize;
        
        int i = 0;
        for (i = 0; i < numberOfCycles; i++) {
            setupBuffers(input, output, i*fBufferSize);
            // Hack : do not transmit control in polyphonic mode
            if (fFactory->fPoly == "0") {
                ControlUI::encodeMidiControl(fControlInputs[0], fJSONDecoder->fInControl, fJSONDecoder->fInputItems);
            }
            processMidiOutBuffer(fControlInputs[1], true);
            sendSlice(fBufferSize);
            recvSlice(fBufferSize);
            ControlUI::decodeMidiControl(fControlOutputs[0], fJSONDecoder->fOutControl, fJSONDecoder->fOutputItems);
            processMidiInBuffer(fControlOutputs[1]);
        }
        
        if (lastCycle > 0) {
            setupBuffers(input, output, i*fBufferSize);
            // Hack : do not transmit control in polyphonic mode
            if (fFactory->fPoly == "0") {
                ControlUI::encodeMidiControl(fControlInputs[0], fJSONDecoder->fInControl, fJSONDecoder->fInputItems);
            }
            processMidiOutBuffer(fControlInputs[1], true);
            fillBufferWithZerosOffset(getNumInputs(), lastCycle, fBufferSize-lastCycle, fAudioInputs);
            sendSlice(lastCycle);
            recvSlice(lastCycle);
            ControlUI::decodeMidiControl(fControlOutputs[0], fJSONDecoder->fOutControl, fJSONDecoder->fOutputItems);
            processMidiInBuffer(fControlOutputs[1]);
        }
        
    } else {
        fillBufferWithZerosOffset(getNumOutputs(), 0, count, output);
    }
}

void remote_dsp_aux::metadata(Meta* m)
{ 
    fFactory->metadataRemoteDSPFactory(m);
}

dsp* remote_dsp_aux::clone()
{
    return new remote_dsp_aux(fFactory);
}

int remote_dsp_aux::getSampleRate()
{
    return fSampleRate;
}

// Accessors to number of input/output of DSP
int remote_dsp_aux::getNumInputs()
{ 
    return fJSONDecoder->fNumInputs;
}

int remote_dsp_aux::getNumOutputs()
{ 
    return fJSONDecoder->fNumOutputs;
}

// Useless fonction in our case but required for a DSP interface
//Interesting to implement one day ! 
void remote_dsp_aux::init(int /*samplingRate*/) {}

void remote_dsp_aux::instanceConstants(int /*samplingRate*/) {}

void remote_dsp_aux::instanceInit(int /*samplingRate*/) {}

void remote_dsp_aux::instanceResetUserInterface() {}

void remote_dsp_aux::instanceClear() {}

// Init remote dsp instance sends a POST request to a remote server
// The URL extension used is /CreateInstance
// The datas to send are NetJack parameters & the factory index it is created from
// A NetJack master is created to open a connection with the slave opened on the server's side
bool remote_dsp_aux::init(int argc, const char* argv[], 
                        remoteDSPErrorCallback error_callback, 
                        void* error_callback_arg, 
                        int& error)
{
    
    int buffer_size = atoi(loptions(argc, argv, "--NJ_buffer_size ", "512"));
    int sample_rate = atoi(loptions(argc, argv, "--NJ_sample_rate ", "44100"));
    bool partial_cycle = atoi(loptions(argc, argv, "--NJ_partial", "0"));
    const char* port = loptions(argc, argv, "--NJ_port", "19000");
   
    fBufferSize = buffer_size;
    fSampleRate = sample_rate;
    
    fErrorCallback = error_callback;
    fErrorCallbackArg = error_callback_arg;
     
    // Init Control Buffers
    fControlInputs[0] = new float[8192];
    fControlInputs[1] = new float[8192];
    fControlOutputs[0] = new float[8192];
    fControlOutputs[1] = new float[8192];
 
    memset(fControlInputs[0], 0, sizeof(float) * 8192);
    memset(fControlInputs[1], 0, sizeof(float) * 8192);
    memset(fControlOutputs[0], 0, sizeof(float) * 8192);
    memset(fControlOutputs[1], 0, sizeof(float) * 8192);
    
    // To be sure fCounterIn and fCounterOut are set before 'compute' is called, even if no 'buildUserInterface' is called by the client
    ControlUI dummy_ui;
    buildUserInterface(&dummy_ui);
     
    stringstream finalRequest;
    string response;
    int errorCode = -1;
    
    // Audio driver type
    finalRequest << "audio_type=" << "kNetJack";
    
    // Parse NetJack Parameters
    finalRequest << "&NJ_ip=" << loptions(argc, argv, "--NJ_ip", searchIP().c_str());
    finalRequest << "&NJ_port=" << port;
    finalRequest << "&NJ_compression=" << loptions(argc, argv, "--NJ_compression", "-1");
    finalRequest << "&NJ_latency=" << loptions(argc, argv, "--NJ_latency", "2");
    finalRequest << "&NJ_mtu=" << loptions(argc, argv, "--NJ_mtu", "1500");
    finalRequest << "&shaKey=" << fFactory->getSHAKey();
    finalRequest << "&instanceKey=" << this;
    finalRequest << "&poly=" << fFactory->getPoly();
    finalRequest << "&voices=" << fFactory->getVoices();
    finalRequest << "&group=" << fFactory->getGroup();
    
    bool res = false;
    string url = fFactory->getURL() + "/CreateInstance";
   
    // Open NetJack connection
    if (sendRequest(url, finalRequest.str(), response, errorCode)) {
        jack_master_t request = { -1, -1, -1, -1, 
                                static_cast<jack_nframes_t>(buffer_size), 
                                static_cast<jack_nframes_t>(sample_rate), 
                                "net_master", 5, partial_cycle};
        jack_slave_t result;
        if ((fNetJack = jack_net_master_open(DEFAULT_MULTICAST_IP, atoi(port), &request, &result))) {
            res = true;
        } else {
            error = ERROR_NETJACK_NOTSTARTED;
        }
    } else {
        error = errorCode;
    }
    
    return res;
}     

remote_audio_aux::remote_audio_aux(remote_dsp_factory* factory)
{
    fFactory = factory;
}

remote_audio_aux::~remote_audio_aux()
{
    fFactory->sendFinalRequest(this, "/DeleteInstance");
}  

bool remote_audio_aux::init(int argc, const char* argv[], int& error)
{
    stringstream finalRequest;
    string response;
    int errorCode = -1;
    
    // Audio driver type
    finalRequest << "audio_type=" << "kLocalAudio";
    //finalRequest << "audio_type=" << "kJack";
    
    // Parse NetJack Parameters
    finalRequest << "&LA_sample_rate=" << atoi(loptions(argc, argv, "--LA_sample_rate ", "44100"));
    finalRequest << "&LA_buffer_size=" << atoi(loptions(argc, argv, "--LA_buffer_size ", "512"));
    finalRequest << "&osc=" << loptions(argc, argv, "--osc ", "0");
    finalRequest << "&httpd=" << loptions(argc, argv, "--httpd ", "0");
    finalRequest << "&midi=" << loptions(argc, argv, "--midi ", "0");
    finalRequest << "&shaKey=" << fFactory->getSHAKey();
    finalRequest << "&instanceKey=" << this;
    
    string url = fFactory->getURL() + "/CreateInstance";
    return sendRequest(url, finalRequest.str(), response, errorCode);
}  

bool remote_audio_aux::start()
{
    return fFactory->sendFinalRequest(this, "/StartInstance");
}

bool remote_audio_aux::stop()
{
    return fFactory->sendFinalRequest(this, "/StopInstance");
}            

//------ DISCOVERY OF AVAILABLE MACHINES

remote_DNS* remote_dsp_factory::gDNS = NULL;

__attribute__((constructor)) static void initialize_libfaustremote() 
{
    remote_dsp_factory::gDNS = new remote_DNS();
    remote_dsp_factory::gCurl = curl_easy_init();
    if (!remote_dsp_factory::gCurl) {
        cout << "curl_easy_init error..." << endl;
    }
}

__attribute__((destructor)) static void destroy_libfaustremote()
{
    delete remote_dsp_factory::gDNS;
    if (remote_dsp_factory::gCurl) {
        curl_easy_cleanup(remote_dsp_factory::gCurl);
    }
    
    // Library cleanup...
    deleteAllDSPFactories();
    deleteAllRemoteDSPFactories(); 
}

remote_DNS::remote_DNS()
{
    /* start a new server on port 7770 */
    fLoThread = lo_server_thread_new_multicast("224.0.0.1", "7770", remote_DNS::errorHandler);
    
    /* add method that will match the path /foo/bar, with two numbers, coerced to float and int */
    lo_server_thread_add_method(fLoThread, "/faustcompiler", "is", remote_DNS::pingHandler, this);
     
    lo_server_thread_start(fLoThread);
}
                                
remote_DNS::~remote_DNS()
{
    lo_server_thread_free(fLoThread);
}

void remote_DNS::errorHandler(int num, const char* msg, const char* path)
{
    printf("liblo server error %d in path %s: %s\n", num, path, msg);
}

/* catch any incoming messages and display them. returning 1 means that the
 * message has not been fully handled and the server should try other methods */
int remote_DNS::pingHandler(const char* path, const char* types, 
                            lo_arg** argv,
                            int argc, void* data, 
                            void* user_data)
{
    member messageSender;
    messageSender.pid = argv[0]->i;
    messageSender.hostname = (char*)argv[1];
    lo_timetag_now(&messageSender.timetag);
    stringstream convert;
    convert << messageSender.hostname << ":" << messageSender.pid;
  
    if (remote_dsp_factory::gDNS->fLocker.Lock()) {
        remote_dsp_factory::gDNS->fClients[convert.str()] = messageSender;
        remote_dsp_factory::gDNS->fLocker.Unlock();
    }
        
    return 0;
}

//----------------------------------REMOTE DSP/AUDIO PUBLIC API-------------------------------------------
// FACTORIES

// TODO : possibly recompute the DSP (if Faust compilation parameters change)

EXPORT remote_dsp_factory* getRemoteDSPFactoryFromSHAKey(const string& sha_key, const std::string& ip_server, int port_server)
{
    RemoteFactoryDSPTableIt it;
    
    if (isLocalFactory(sha_key)) {
        return reinterpret_cast<remote_dsp_factory*>(getDSPFactoryFromSHAKey(sha_key));
    // If available in the local remote cache
    } else if (isRemoteFactory(sha_key, it)) {
        Sremote_dsp_factory sfactory = (*it).first;
        sfactory->addReference();
        return sfactory;
    } else {
    
        stringstream serverURL;
        serverURL << "http://" << ip_server << ":" << port_server;
        string response;
        int errorCode = -1;
    
        // Call server side to get remote factory, create local proxy factory, put it in the cache
        string finalRequest = "shaKey=" + sha_key;
        remote_dsp_factory* factory = new remote_dsp_factory(ip_server, port_server, sha_key);
        string url = serverURL.str() + "/GetFactoryFromSHAKey";
        
        if (sendRequest(url, finalRequest, response, errorCode)) {
            factory->decodeJSON(response);
            remote_dsp_factory::gRemoteFactoryDSPTable[factory] = make_pair(list<remote_dsp_aux*>(), list<remote_audio_aux*>());
            return factory;
        } else {
            delete factory;
            return NULL;
        }
    }
}

EXPORT remote_dsp_factory* createRemoteDSPFactoryFromFile(const string& filename, 
                                                        int argc, 
                                                        const char* argv[],
                                                        const string& ip_server, 
                                                        int port_server, 
                                                        string& error_msg, 
                                                        int opt_level)
{
    string base = basename((char*)filename.c_str());
    int pos = base.find(".dsp");
      
    if (pos != string::npos) {
        return createRemoteDSPFactoryFromString(base.substr(0, pos), pathToContent(filename), 
                                                argc, argv, 
                                                ip_server, 
                                                port_server,
                                                error_msg, 
                                                opt_level);
    } else {
        error_msg = "File Extension is not the one expected (.dsp expected)";
        return NULL;
    }
}

EXPORT remote_dsp_factory* createRemoteDSPFactoryFromString(const string& name_app, 
                                                            const string& dsp_content, 
                                                            int argc, 
                                                            const char* argv[], 
                                                            const string& ip_server, 
                                                            int port_server, 
                                                            string& error_msg, 
                                                            int opt_level)
{
    RemoteFactoryDSPTableIt it;
    const char* argv1[argc];
    int argc1 = 0;
 
    // Filter arguments 
    for (int i = 0; i < argc; i++) {
        if (!(strcmp(argv[i],"-svg") == 0 || 
            strcmp(argv[i],"-ps") == 0 || 
            strcmp(argv[i],"-tg") == 0 || 
            strcmp(argv[i],"-sg") == 0 || 
            strcmp(argv[i],"-mdoc") == 0 || 
            strcmp(argv[i],"-mdlang") == 0 || 
            strcmp(argv[i],"-stripdoc") == 0 || 
            strcmp(argv[i],"-xml") == 0))
        {
            argv1[argc1++] = argv[i];
        }
    }
    
    string expanded_dsp;
    string sha_key;
    
    if ((expanded_dsp = expandDSPFromString(name_app, dsp_content, argc1, argv1, sha_key, error_msg)) == "") {
        return NULL; 
        
    // Compile on server side and get machine code on client to re-create a local Factory
    } else if (isopt(argc, argv, "-rm")) {
        return crossCompile(argc, argv, name_app, expanded_dsp, sha_key, ip_server, port_server, error_msg, opt_level);
        
    // If available in the local LLVM cache
    } else if (isLocalFactory(sha_key)) {
        return reinterpret_cast<remote_dsp_factory*>(getDSPFactoryFromSHAKey(sha_key));
        
    // If available in the local remote cache
    } else if (isRemoteFactory(sha_key, it)) {
        Sremote_dsp_factory sfactory = (*it).first;
        sfactory->addReference();
        return sfactory;
    } else {
    
        remote_dsp_factory* factory = new remote_dsp_factory(ip_server, port_server, sha_key);
        if (factory->init(argc1, argv1, name_app, expanded_dsp, error_msg, opt_level)) {
            remote_dsp_factory::gRemoteFactoryDSPTable[factory] = make_pair(list<remote_dsp_aux*>(), list<remote_audio_aux*>());
            return factory;
        } else {
            delete factory;
            return NULL;
        }
    }
}

EXPORT bool deleteRemoteDSPFactory(remote_dsp_factory* factory)
{
    if (isLocalFactory(factory)) {
        return deleteDSPFactory(reinterpret_cast<llvm_dsp_factory*>(factory));
    } else {
        
        RemoteFactoryDSPTableIt it;
        if ((it = remote_dsp_factory::gRemoteFactoryDSPTable.find(factory)) != remote_dsp_factory::gRemoteFactoryDSPTable.end()) {
            Sremote_dsp_factory sfactory = (*it).first;
            RemoteFactoryDSPTable dsp_map = (*it).second;
            list<remote_dsp_aux*> dsp_list1 = dsp_map.first;
            list<remote_audio_aux*> dsp_list2 = dsp_map.second;
            
            if (sfactory->refs() == 2) { // Local stack pointer + the one in gRemoteFactoryDSPTable...
            
                // Possibly delete remaining DSP
                list<remote_dsp_aux*>::iterator it1;
                for (it1 = dsp_list1.begin(); it1 != dsp_list1.end(); it1++) { delete (*it1); }
                
                list<remote_audio_aux*>::iterator it2;
                for (it2 = dsp_list2.begin(); it2 != dsp_list2.end(); it2++) { delete (*it2); }
                
                // Last use, remove from the global table, pointer will be deleted
                remote_dsp_factory::gRemoteFactoryDSPTable.erase(factory);
                return true;
            } else {
                sfactory->removeReference();
            }
        }
    
        return false;
    }
}

EXPORT void deleteAllRemoteDSPFactories()
{
    // Delete remote factories...
    RemoteFactoryDSPTableIt it1;
    for (it1 = remote_dsp_factory::gRemoteFactoryDSPTable.begin(); it1 != remote_dsp_factory::gRemoteFactoryDSPTable.end(); it1++) {
        // Decrement counter up to one...
        while (((*it1).first)->refs() > 1) { ((*it1).first)->removeReference(); }
    }
    // Then clear the table thus finally deleting all ref = 1 smart pointers
    remote_dsp_factory::gRemoteFactoryDSPTable.clear();
    
    // Delete our own local LLVM factories...
    LocalFactoryDSPTableIt it2;
    for (it2 = remote_dsp_factory::gLocalFactoryDSPTable.begin(); it2 != remote_dsp_factory::gLocalFactoryDSPTable.end(); it2++) {
        while (!deleteDSPFactory(*it2)) {}
    }
}

EXPORT std::string remote_dsp_factory::getName() { return fJSONDecoder->fName; }

EXPORT std::string remote_dsp_factory::getSHAKey() { return fSHAKey; }

EXPORT std::string remote_dsp_factory::getDSPCode() { return fExpandedDSP; }

EXPORT std::string remote_dsp_factory::getPoly() { return fPoly; }

EXPORT std::string remote_dsp_factory::getVoices() { return fVoices; }

EXPORT std::string remote_dsp_factory::getGroup() { return fGroup; }

EXPORT void metadataRemoteDSPFactory(remote_dsp_factory* factory, Meta* m)
{
    factory->metadataRemoteDSPFactory(m);
}

EXPORT vector<string> getRemoteDSPFactoryLibraryList(remote_dsp_factory* factory) 
{ 
    return factory->getRemoteDSPFactoryLibraryList(); 
}

EXPORT bool getRemoteDSPMachines(map<string, remote_dsp_machine* >* machine_list)
{
    if (remote_dsp_factory::gDNS && remote_dsp_factory::gDNS->fLocker.Lock()) {
        
        for (map<string, remote_DNS::member>::iterator it = remote_dsp_factory::gDNS->fClients.begin(); it !=  remote_dsp_factory::gDNS->fClients.end(); it++){
            
            remote_DNS::member iterMem = it->second;
            lo_timetag now;
            lo_timetag_now(&now);
            
            // If the server machine did not send a message for 3 secondes, it is considered disconnected
            if ((now.sec - iterMem.timetag.sec) < 3) {
                
                // Cut iterMem.hostname to have Name, Ip, Port of service and Target (tripple + CPU)
                string name_service1 = iterMem.hostname;
                int pos1 = name_service1.find(":");
                string name_service2 = name_service1.substr(pos1 + 1, string::npos);
                int pos2 = name_service2.find(":");
                string name_service3 = name_service2.substr(pos2 + 1, string::npos);
                int pos3 = name_service3.find(":");
    
                string ip = name_service1.substr(0, pos1);
                string port = name_service2.substr(0, pos2);
                string host_name = name_service3.substr(0, pos3);
                string target = name_service3.substr(pos3 + 1, string::npos);
                    
                (*machine_list)[host_name] =  reinterpret_cast<remote_dsp_machine*>(new remote_dsp_machine_aux(ip, atoi(port.c_str()), target));
            }
        }
        
        remote_dsp_factory::gDNS->fLocker.Unlock();
        return true;
    } else {
       return false; 
    }
}

EXPORT bool getRemoteDSPFactories(const string& ip_server, int port_server, vector<pair<string, string> >* factories_list)
{
    bool res = false;
        
    stringstream serverURL;
    serverURL << "http://" << ip_server << ":" << port_server << "/GetAvailableFactories";
   
    ostringstream oss;
    string str1 = serverURL.str();
    curl_easy_setopt(remote_dsp_factory::gCurl, CURLOPT_URL, str1.c_str());
    curl_easy_setopt(remote_dsp_factory::gCurl, CURLOPT_POST, 0L);
    curl_easy_setopt(remote_dsp_factory::gCurl, CURLOPT_WRITEFUNCTION, &storeResponse);
    curl_easy_setopt(remote_dsp_factory::gCurl, CURLOPT_FILE, &oss);
    curl_easy_setopt(remote_dsp_factory::gCurl, CURLOPT_CONNECTTIMEOUT, 5); 
    curl_easy_setopt(remote_dsp_factory::gCurl, CURLOPT_TIMEOUT, 30);
        
    if (curl_easy_perform(remote_dsp_factory::gCurl) == CURLE_OK) {
        
        long respcode; // response code of the http transaction
        curl_easy_getinfo(remote_dsp_factory::gCurl, CURLINFO_RESPONSE_CODE, &respcode);
        
        if (respcode == 200) {
            // PARSE RESPONSE TO EXTRACT KEY/VALUE
            string response = oss.str();
            stringstream os(response);   
            string name, sha_key;   
            while (os >> name) {                
                os >> sha_key;
                factories_list->push_back(make_pair(name, sha_key));
            }
            res = true;
        } else if (respcode == 400) {
            printf("curl_easy_getinfo error\n");
        }
    } else {
        printf("curl_easy_perform error\n");
    }
   
    return res;
}

EXPORT remote_dsp_machine* remote_dsp_machine::create(const std::string& ip, int port, const std::string& target)
{
    return reinterpret_cast<remote_dsp_machine*>(new remote_dsp_machine_aux(ip, port, target));
}

EXPORT void remote_dsp_machine::destroy(remote_dsp_machine* machine)
{
    delete reinterpret_cast<remote_dsp_machine_aux*>(machine);
}

EXPORT std::string remote_dsp_machine::getIP()
{
    return reinterpret_cast<remote_dsp_machine_aux*>(this)->getIP();
}

EXPORT int remote_dsp_machine::getPort()
{
    return reinterpret_cast<remote_dsp_machine_aux*>(this)->getPort();
}

EXPORT std::string remote_dsp_machine::getTarget()
{
    return reinterpret_cast<remote_dsp_machine_aux*>(this)->getTarget();
}

//---------DSP INSTANCE

EXPORT remote_dsp* createRemoteDSPInstance(remote_dsp_factory* factory, 
                                            int argc, 
                                            const char* argv[], 
                                            remoteDSPErrorCallback error_callback, 
                                            void* error_callback_arg, 
                                            int& error)
{
    if (isLocalFactory(factory)) {
        return reinterpret_cast<remote_dsp*>(reinterpret_cast<llvm_dsp_factory*>(factory)->createDSPInstance());
    } else {
        RemoteFactoryDSPTableIt it;
        if ((it = remote_dsp_factory::gRemoteFactoryDSPTable.find(factory)) != remote_dsp_factory::gRemoteFactoryDSPTable.end()) {
            remote_dsp_aux* instance = factory->createRemoteDSPInstance(argc, argv, error_callback, error_callback_arg, error);
            (*it).second.first.push_back(instance);
            return reinterpret_cast<remote_dsp*>(instance);
        } else {
            return NULL;
        }
    }
}

EXPORT void deleteRemoteDSPInstance(remote_dsp* dsp)
{
    remote_dsp_factory* factory = reinterpret_cast<remote_dsp_aux*>(dsp)->getFactory();
    
    /*
    if (isLocalFactory(factory))  {
        deleteDSPInstance(reinterpret_cast<llvm_dsp*>(dsp));
    } else {
        delete reinterpret_cast<remote_dsp_aux*>(dsp); 
    }
    */
    
    delete dsp; // TO CHECK
}

EXPORT void remote_dsp::metadata(Meta* m)
{
    reinterpret_cast<remote_dsp_aux*>(this)->metadata(m);
}

EXPORT int remote_dsp::getNumInputs()
{
    return reinterpret_cast<remote_dsp_aux*>(this)->getNumInputs();
}

EXPORT int remote_dsp::getNumOutputs()
{
    return reinterpret_cast<remote_dsp_aux*>(this)->getNumOutputs();
}

EXPORT void remote_dsp::init(int samplingRate)
{
    reinterpret_cast<remote_dsp_aux*>(this)->init(samplingRate);
}

EXPORT void remote_dsp::instanceInit(int samplingRate)
{
    reinterpret_cast<remote_dsp_aux*>(this)->instanceInit(samplingRate);
}

EXPORT void remote_dsp::instanceConstants(int samplingRate)
{
    reinterpret_cast<remote_dsp_aux*>(this)->instanceConstants(samplingRate);
}

EXPORT void remote_dsp::instanceResetUserInterface()
{
    reinterpret_cast<remote_dsp_aux*>(this)->instanceResetUserInterface();
}

EXPORT void remote_dsp::instanceClear()
{
    reinterpret_cast<remote_dsp_aux*>(this)->instanceClear();
}

EXPORT dsp* remote_dsp::clone()
{
    return reinterpret_cast<remote_dsp_aux*>(this)->clone();
}

EXPORT int remote_dsp::getSampleRate()
{
    return reinterpret_cast<remote_dsp_aux*>(this)->getSampleRate();
}

EXPORT void remote_dsp::buildUserInterface(UI* interface)
{
    reinterpret_cast<remote_dsp_aux*>(this)->buildUserInterface(interface);
}

EXPORT void remote_dsp::compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
{
    reinterpret_cast<remote_dsp_aux*>(this)->compute(count, input, output);
}

// MIDI polyphonic control
EXPORT MapUI* remote_dsp::keyOn(int channel, int pitch, int velocity)
{
    return reinterpret_cast<remote_dsp_aux*>(this)->keyOn(channel, pitch, velocity);
}

EXPORT void remote_dsp::keyOff(int channel, int pitch, int velocity)
{
    reinterpret_cast<remote_dsp_aux*>(this)->keyOff(channel, pitch, velocity);
}

EXPORT void remote_dsp::keyPress(int channel, int pitch, int press)
{
    reinterpret_cast<remote_dsp_aux*>(this)->keyPress(channel, pitch, press);
}

EXPORT void remote_dsp::chanPress(int channel, int press)
{
     reinterpret_cast<remote_dsp_aux*>(this)->chanPress(channel, press);
}

EXPORT void remote_dsp::ctrlChange(int channel, int ctrl, int value)
{
     reinterpret_cast<remote_dsp_aux*>(this)->ctrlChange(channel, ctrl, value);
}

EXPORT void remote_dsp::pitchWheel(int channel, int wheel)
{
     reinterpret_cast<remote_dsp_aux*>(this)->pitchWheel(channel, wheel);
}

EXPORT void remote_dsp::progChange(int channel, int pgm)
{
    reinterpret_cast<remote_dsp_aux*>(this)->progChange(channel, pgm);
}

//---------AUDIO INSTANCE

EXPORT remote_audio* createRemoteAudioInstance(remote_dsp_factory* factory, int argc, const char* argv[], int& error)
{
    RemoteFactoryDSPTableIt it;
    if ((it = remote_dsp_factory::gRemoteFactoryDSPTable.find(factory)) != remote_dsp_factory::gRemoteFactoryDSPTable.end()) {
        remote_audio_aux* instance = factory->createRemoteAudioInstance(argc, argv, error);
        (*it).second.second.push_back(instance);
        return reinterpret_cast<remote_audio*>(instance);
    } else {
        return NULL;
    }
}

EXPORT void deleteRemoteAudioInstance(remote_audio* audio)
{
    RemoteFactoryDSPTableIt it;
    remote_audio_aux* audio_aux = reinterpret_cast<remote_audio_aux*>(audio);
    remote_dsp_factory* factory = audio_aux->getFactory();
    
    it = remote_dsp_factory::gRemoteFactoryDSPTable.find(factory);
    assert(it != remote_dsp_factory::gRemoteFactoryDSPTable.end());
    (*it).second.second.remove(audio_aux);
    
    delete audio_aux; 
}

EXPORT bool remote_audio::start()
{
    return reinterpret_cast<remote_audio_aux*>(this)->start();
}

EXPORT bool remote_audio::stop()
{
    return reinterpret_cast<remote_audio_aux*>(this)->stop();
}

