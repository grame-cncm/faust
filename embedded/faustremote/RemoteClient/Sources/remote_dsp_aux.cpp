/************************************************************************
 ************************************************************************
 FAUST compiler
 Copyright (C) 2003-2013 GRAME, Centre National de Creation Musicale
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
#include "remote_dsp_aux.h"
#include "faust/gui/ControlUI.h"
#include "llvm-c-dsp.h"
#include "libfaust.h"
#include "utilities.h"
#include <errno.h>
#include <libgen.h>

FactoryTableType remote_dsp_factory::gFactoryTable;

// Standard Callback to store a server response in stringstream
static size_t store_Response(void *buf, size_t size, size_t nmemb, void* userp)
{
    std::ostream* os = static_cast<std::ostream*>(userp);
    std::streamsize len = size * nmemb;
    return (os->write(static_cast<char*>(buf), len)) ? len : 0;
}

//Returns true if no problem encountered
//The response string stores the data received 
//(can be error or real data... depending on return value)
//The errorCode stores the error encoded as INT
static bool send_request(const string& ip, const string& finalRequest, string& response, int& errorCode)
{
    CURL *curl = curl_easy_init();
    bool isInitSuccessfull = false;
    
    if (curl) {
        
        printf("cURL with request = %s and ip = %s\n", finalRequest.c_str(), ip.c_str());
        
        std::ostringstream oss;
        
        curl_easy_setopt(curl, CURLOPT_URL, ip.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)(finalRequest.size()));
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, finalRequest.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &store_Response);
        curl_easy_setopt(curl, CURLOPT_FILE, &oss);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT ,15); 
        curl_easy_setopt(curl,CURLOPT_TIMEOUT, 15);
        
        CURLcode res = curl_easy_perform(curl);
        
        if (res != CURLE_OK) {
            printf("Easy perform error\n");
            errorCode = ERROR_CURL_CONNECTION;
        } else{
            
            long respcode; //response code of the http transaction
            curl_easy_getinfo(curl,CURLINFO_RESPONSE_CODE, &respcode);
            
            if (respcode == 200) {
                response = oss.str();
                isInitSuccessfull = true;
            } else if (respcode == 400) {
                
                printf("INFO Failed\n");
                
                // Is String Int ?
                bool isInt = true;
                const char* intermediateString = oss.str().c_str();
                
                for (size_t i=0; i<strlen(intermediateString); i++) {
                    if (!isdigit(intermediateString[i])) {
                        isInt = false;
                        break;
                    }
                }
                
                if (isInt) {
                    errorCode = atoi(intermediateString);
                } else {
                    response = oss.str();
                }
            }
        }
        
        curl_easy_cleanup(curl);
    } else {
        errorCode = ERROR_CURL_CONNECTION;
    }
    
    return isInitSuccessfull;
}

//------------------FACTORY

// Init remote dsp factory sends a POST request to a remote server
// The URL extension used is /GetJson
// The datas have a url-encoded form (key/value separated by & and special character are reencoded like spaces = %)
bool remote_dsp_factory::init(int argc, const char *argv[], 
                            const string& ip_server, 
                            int port_server, 
                            const string& name_app, 
                            const string& dsp_content, 
                            const string& sha_key, 
                            string& error, 
                            int opt_level){

    bool isInitSuccessfull = false;
    fSHAKey = sha_key;
    
    CURL *curl = curl_easy_init();
    
    if (curl) {

        string finalRequest = "name=";
        finalRequest += name_app;
        
// Adding Compilation Options to request data
        
        finalRequest += "&number_options=";
        
        stringstream nb;
        nb<<argc;
        
        finalRequest += nb.str();
        
        for (int i=0; i<argc; i++) {
            finalRequest += "&options=";
            finalRequest += argv[i];
        }
        
// Adding LLVM optimization Level to request data
        finalRequest += "&opt_level=";
        stringstream ol;
        ol<<opt_level;
        finalRequest +=ol.str(); 
        
        finalRequest += "&shaKey=";
        finalRequest += fSHAKey;
        
        printf("finalRequest = %s\n", finalRequest.c_str());
        
        finalRequest += "&data=";
        
        // Transforming faustCode to URL format
        finalRequest += curl_easy_escape(curl , dsp_content.c_str() , dsp_content.size());
        
        fServerIP = "http://";
        fServerIP += ip_server;
        fServerIP += ":";
        
        stringstream s;
        s<<port_server;
        
        fServerIP += s.str();
        
        string ip = fServerIP;
        ip += "/GetJson";
        
        printf("ip = %s\n", ip.c_str());
        
        string response("");
        int errorCode = -1;
        if (send_request(ip, finalRequest, response, errorCode)) {
            decodeJson(response);
            isInitSuccessfull = true;
        } else if(errorCode != -1) {
            error = "Curl Connection Failed";
        } else {
            error = response;
        }
        
        curl_easy_cleanup(curl); //Standard CleanUp
    }
    
    return isInitSuccessfull;
}

// Delete remote dsp factory sends an explicit delete request to server
void remote_dsp_factory::stop(){
    
    CURL *curl = curl_easy_init();
    printf("fIndex = %s\n", fSHAKey.c_str());
        
    // The index of the factory to delete has to be sent
    string finalRequest = string("shaKey=") + fSHAKey;
    string ip = fServerIP + string("/DeleteFactory");
    printf("ip = %s\n", ip.c_str());
    
    string response;
    int errorCode;
    if (!send_request(ip, finalRequest, response, errorCode)) {
        printf("curl_easy_perform() failed: %s || code %i\n", response.c_str(), errorCode);
    }
}

// Decoding JSON from a string to
// fUiItems : Structure containing the graphical items
// fMetadatas : Structure containing the metadatas
// Some "extra" metadatas are kept separatly
void remote_dsp_factory::decodeJson(const string& json)
{
    const char* p = json.c_str();
    parseJson(p, fMetadatas, fUiItems);
    
    fNumInputs = atoi(fMetadatas["inputs"].c_str());
    fMetadatas.erase("inputs");
    
    fNumOutputs = atoi(fMetadatas["outputs"].c_str());
    fMetadatas.erase("outputs");
}

// Declaring meta datas
void remote_dsp_factory::metadataRemoteDSPFactory(Meta* m) 
{ 
    map<string,string>::iterator it;
    for(it = fMetadatas.begin() ; it != fMetadatas.end(); it++) {
        m->declare(it->first.c_str(), it->second.c_str());
    }
}   

// Create Remote DSP Instance from factory
remote_dsp_aux* remote_dsp_factory::createRemoteDSPInstance(int argc, const char *argv[], 
                                                            int sampling_rate, int buffer_size, 
                                                            RemoteDSPErrorCallback error_callback, 
                                                            void* error_callback_arg, 
                                                            int& error){
    remote_dsp_aux* dsp = new remote_dsp_aux(this);
    if (dsp->init(argc, argv, sampling_rate, buffer_size, error_callback, error_callback_arg, error)) {
        return dsp; 
    } else {
        delete dsp;
        return NULL;
    }
}

//---------FACTORY

static bool getFactory(const string& sha_key, FactoryTableIt& res)
{
    FactoryTableIt it;
    
    for (it = remote_dsp_factory::gFactoryTable.begin(); it != remote_dsp_factory::gFactoryTable.end(); it++) {
        FactoryTableItem val = (*it).second;
        if (val.first == sha_key) {
            res = it;
            return true;
        }
    }
    
    return false;
}

// Expernal API

EXPORT remote_dsp_factory* getRemoteDSPFactoryFromSHAKey(const string& ip_server, int port_server, const std::string& sha_key)
{
    FactoryTableIt it;
    
    /// If available in the local cache, get it
    if (getFactory(sha_key, it)) {
        Sremote_dsp_factory sfactory = (*it).first;
        sfactory->addReference();
        return sfactory;
    } else {
        // Call server side to get remote factory, create local proxy factory, put it in the cache
        
        remote_dsp_factory* factory = new remote_dsp_factory();
        
        string finalRequest = "shaKey=";
        finalRequest += sha_key;
            
        factory->setKey(sha_key);
        
        printf("finalRequest = %s\n", finalRequest.c_str());
            
        string serverIP = "http://";
        serverIP += ip_server;
        serverIP += ":";
        
        stringstream s;
        s<<port_server;
        
        serverIP += s.str();
        
        factory->setIP(serverIP);
        
        serverIP += "/GetJsonFromKey";
        
        printf("ip = %s\n", serverIP.c_str());
        
        string response("");
        int errorCode = -1;
        
        if (send_request(serverIP, finalRequest, response, errorCode)){
            factory->decodeJson(response);
            remote_dsp_factory::gFactoryTable[factory] = make_pair(sha_key, list<remote_dsp_aux*>());
            return factory;
        }
        //else if(errorCode != -1){ ??
        else {
            delete factory;
            return NULL;
        }
    }
}

EXPORT remote_dsp_factory* createRemoteDSPFactoryFromFile(const string& filename, 
                                                        int argc, 
                                                        const char *argv[],
                                                        const string& ip_server, 
                                                        int port_server, 
                                                        string& error_msg, 
                                                        int opt_level)
{
    string base = basename((char*)filename.c_str());
    int pos = base.find(".dsp");
      
    if (pos != string::npos) {
        printf("File extension found\n");
        return createRemoteDSPFactoryFromString(base.substr(0, pos), pathToContent(filename), argc, argv, ip_server, port_server, error_msg, opt_level);
    } else {
        error_msg = "File Extension is not the one expected (.dsp expected)\n";
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
    // Compute SHA1 key using the non-expanded version, IP and port
    stringstream ss;
    ss << port_server;
    
    string sha_key = generateSHA1(dsp_content + " " + ss.str() + " " + ip_server); 
    FactoryTableIt it;
    
    vector<pair<string, string> > factories_list;
    getRemoteFactoriesAvailable(ip_server, port_server, &factories_list);
    
    bool factoryStillExisting = false;
    
    for (int i=0; i<factories_list.size(); i++) {
        if(sha_key == factories_list[i].second.c_str()){
           factoryStillExisting = true;
            break;
        }
    }
    
    if (getFactory(sha_key, it) && factoryStillExisting) {
        Sremote_dsp_factory sfactory = (*it).first;
        sfactory->addReference();
        return sfactory;
    } else {
    
        // Use for it's possible 'side effects', that is generating SVG, XML... files
        char error_msg_aux[256];
        generateCAuxFilesFromString(name_app.c_str(), dsp_content.c_str(),  argc, argv, error_msg_aux);
        
        //  OPTIONS have to be filtered for documentation not to be created on the server's side -tg, -sg, -ps, -svg, -mdoc, -xml
        int argc1 = 0;
        const char* argv1[argc];
        
        for (int i = 0; i < argc; i++) {
            if (strcmp(argv[i],"-tg") != 0 && 
               strcmp(argv[i],"-sg") != 0 &&
               strcmp(argv[i],"-svg") != 0 &&
               strcmp(argv[i],"-ps") != 0 &&
               strcmp(argv[i],"-mdoc") != 0 &&
               strcmp(argv[i],"-xml") != 0)
            {
                argv1[argc1++] = argv[i];
            }
        }

        char sha_key_aux[256];
        std::string expanded_dsp = expandCDSPFromString(name_app.c_str(), dsp_content.c_str(), argc1, argv1, sha_key_aux, error_msg_aux);
        
        if (expanded_dsp == "") {
            return 0; 
        }
    
        remote_dsp_factory* factory = new remote_dsp_factory();
        if (factory->init(argc1, argv1, ip_server, port_server, name_app, expanded_dsp, sha_key, error_msg, opt_level)) {
            printf("Factory pushed in fFactory Table\n");
            remote_dsp_factory::gFactoryTable[factory] = make_pair(sha_key, list<remote_dsp_aux*>());
            return factory;
        } else {
            delete factory;
            return 0;
        }
    }
}

EXPORT void deleteRemoteDSPFactory(remote_dsp_factory* factory)
{
    
    printf("Delete remote DSP Factory\n");
//    
//    FactoryTableIt it;
//    if ((it = remote_dsp_factory::gFactoryTable.find(factory)) != remote_dsp_factory::gFactoryTable.end()) {
//        Sremote_dsp_factory sfactory = (*it).first;
//        if (sfactory->refs() == 2) { // Local stack pointer + the one in gFactoryTable...
//            // Last use, remove from the global table, pointer will be deleted
//            remote_dsp_factory::gFactoryTable.erase(factory);
//        } else {
//            sfactory->removeReference();
//        }
//    }
    factory->stop();
//    
//    string finalRequest = "shaKey="+factory->key();
//    
//    string response;
//    int errorCode;
//    if(send_request("http://192.168.1.174:7777/DeleteFactory", finalRequest, response, errorCode))
//        printf("Factory Well Well deleted\n");
}

EXPORT void deleteAllRemoteDSPFactories()
{
    FactoryTableIt it;
    for (it = remote_dsp_factory::gFactoryTable.begin(); it != remote_dsp_factory::gFactoryTable.end(); it++) {
        // Decrement counter up to one...
        while (((*it).first)->refs() > 1) { ((*it).first)->removeReference(); }
    }
    // Then clear the table thus finally deleting all ref = 1 smart pointers
    remote_dsp_factory::gFactoryTable.clear();
}

EXPORT void metadataRemoteDSPFactory(remote_dsp_factory* factory, Meta* m)
{
    factory->metadataRemoteDSPFactory(m);
}

//--------------------INSTANCES

remote_dsp_aux::remote_dsp_aux(remote_dsp_factory* factory)
{
    fFactory = factory;
    fNetJack = NULL;
    
    fAudioInputs = new float*[getNumInputs()];
    fAudioOutputs = new float*[getNumOutputs()];
    
    fControlInputs = new float*[1];
    fControlOutputs = new float*[1];
    
    fCounterIn = 0;
    fCounterOut = 0;
    
    fErrorCallback = 0;
    fErrorCallbackArg = 0;
    
    fRunningFlag = true;
    
    printf("remote_dsp_aux::remote_dsp_aux = %p\n", this);
}
        
remote_dsp_aux::~remote_dsp_aux()
{
    if (fNetJack) {
    
        jack_net_master_close(fNetJack); 
        
        delete[] fInControl;
        delete[] fOutControl;
        
        delete[] fControlInputs[0];
        delete[] fControlOutputs[0];
    
        fNetJack = 0;
    }
    
    delete[] fAudioInputs;
    delete[] fAudioOutputs;
    
    delete[] fControlInputs;
    delete[] fControlOutputs;
}

void remote_dsp_aux::fillBufferWithZerosOffset(int channels, int offset, int size, FAUSTFLOAT** buffer)
{
    // Cleanup audio buffers only 
    for (int i = 0; i < channels; i++) {
        memset(&buffer[i][offset], 0, sizeof(float)*size);
    }
}

// Fonction for command line parsing
const char* remote_dsp_aux::getValueFromKey(int argc, const char *argv[], const char *key, const char* defaultValue)
{
    for (int i = 0; i<argc; i++){
        if (strcmp(argv[i], key) == 0) {
            return argv[i+1];   
        }
    }
	return defaultValue;
}

// Decode internal structure, to build user interface
void remote_dsp_aux::buildUserInterface(UI* ui){

//    printf("REMOTEDSP::BUILDUSERINTERFACE\n");
    
    vector<itemInfo*> jsonItems = fFactory->itemList();
    
//To be sure the floats are correctly encoded
    char* tmp_local = setlocale(LC_ALL, NULL);
    setlocale(LC_ALL, "C");
    
    vector<itemInfo*>::iterator it;
    
    int counterIn = 0;
    int counterOut = 0;
    
    for (it = jsonItems.begin(); it != jsonItems.end() ; it++) {
        
        float init = strtod((*it)->init.c_str(), NULL);
        float min = strtod((*it)->min.c_str(), NULL);
        float max = strtod((*it)->max.c_str(), NULL);
        float step = strtod((*it)->step.c_str(), NULL);
        
        map<string,string>::iterator it2;
        
        bool isInItem = false;
        bool isOutItem = false;
        
//        Meta Data declaration for entry items
        if((*it)->type.find("group") == string::npos && (*it)->type.find("bargraph") == string::npos && (*it)->type.compare("close") != 0){
            
            fInControl[counterIn] = init;
            isInItem = true;
            
            for(it2 = (*it)->meta.begin(); it2 != (*it)->meta.end(); it2++)
                ui->declare(&fInControl[counterIn], it2->first.c_str(), it2->second.c_str());
        }
//        Meta Data declaration for exit items
        else if((*it)->type.find("bargraph") != string::npos){
            
            fOutControl[counterOut] = init;
            isOutItem = true;
            
            for(it2 = (*it)->meta.begin(); it2 != (*it)->meta.end(); it2++){
                ui->declare(&fOutControl[counterOut], it2->first.c_str(), it2->second.c_str());
            }
        }
//      Meta Data declaration for group opening or closing
        else {
            for(it2 = (*it)->meta.begin(); it2 != (*it)->meta.end(); it2++)
                ui->declare(0, it2->first.c_str(), it2->second.c_str());
        }
        
//      Item declaration
        if((*it)->type.compare("hgroup") == 0)
            ui->openHorizontalBox((*it)->label.c_str());
        
        else if((*it)->type.compare("vgroup") == 0){
            printf("GROUP NAME = %s\n", (*it)->label.c_str());
            ui->openVerticalBox((*it)->label.c_str());
        }
        else if((*it)->type.compare("tgroup") == 0)
            ui->openTabBox((*it)->label.c_str());
        
        else if((*it)->type.compare("vslider") == 0)
            ui->addVerticalSlider((*it)->label.c_str(), &fInControl[counterIn], init, min, max, step);
        
        else if((*it)->type.compare("hslider") == 0)
            ui->addHorizontalSlider((*it)->label.c_str(), &fInControl[counterIn], init, min, max, step);            
        
        else if((*it)->type.compare("checkbox") == 0)
            ui->addCheckButton((*it)->label.c_str(), &fInControl[counterIn]);
        
        else if((*it)->type.compare("hbargraph") == 0)
            ui->addHorizontalBargraph((*it)->label.c_str(), &fOutControl[counterOut], min, max);
        
        else if((*it)->type.compare("vbargraph") == 0)
            ui->addVerticalBargraph((*it)->label.c_str(), &fOutControl[counterOut], min, max);
        
        else if((*it)->type.compare("nentry") == 0)
            ui->addNumEntry((*it)->label.c_str(), &fInControl[counterIn], init, min, max, step);
        
        else if((*it)->type.compare("button") == 0)
            ui->addButton((*it)->label.c_str(), &fInControl[counterIn]);
        
        else if((*it)->type.compare("close") == 0)
            ui->closeBox();
            
        if(isInItem)
            counterIn++;
        if(isOutItem)
            counterOut++;
    }
    
    // Keep them for compute method...
    fCounterIn = counterIn;
    fCounterOut = counterOut;
    
    setlocale(LC_ALL, tmp_local);
}

void remote_dsp_aux::setupBuffers(FAUSTFLOAT** input, FAUSTFLOAT** output, int offset)
{
    for(int j=0; j<getNumInputs(); j++) {
        fAudioInputs[j] = &input[j][offset];
    }
    
    for(int j=0; j<getNumOutputs(); j++) {
        fAudioOutputs[j] = &output[j][offset];
    }
}

void remote_dsp_aux::sendSlice(int buffer_size) 
{
    if (fRunningFlag && jack_net_master_send_slice(fNetJack, getNumInputs(), fAudioInputs, 1, (void**)fControlInputs, buffer_size) < 0){
        fillBufferWithZerosOffset(getNumOutputs(), 0, buffer_size, fAudioOutputs);
        if (fErrorCallback) {
            
            printf("Is sent OK ?\n");
            fRunningFlag = (fErrorCallback(WRITE_ERROR, fErrorCallbackArg) == 0);
        }
    }
}

void remote_dsp_aux::recvSlice(int buffer_size)
{
    if (fRunningFlag && jack_net_master_recv_slice(fNetJack, getNumOutputs(), fAudioOutputs, 1, (void**)fControlOutputs, buffer_size) < 0) {
        fillBufferWithZerosOffset(getNumOutputs(), 0, buffer_size, fAudioOutputs);
        if (fErrorCallback) {
            fRunningFlag = (fErrorCallback(READ_ERROR, fErrorCallbackArg) == 0);
        }
    }
}

// Compute of the DSP, adding the controls to the input/output passed
void remote_dsp_aux::compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
{
    if (fRunningFlag) {
        
        // If count > fBufferSize : the cycle is divided in numberOfCycles NetJack cycles, and a lastCycle one
        
        int numberOfCycles = count/fBufferSize;
        int lastCycle = count%fBufferSize;
        
        int i = 0;
        for (i = 0; i < numberOfCycles; i++) {
            ControlUI::encode_midi_control(fControlInputs[0], fInControl, fCounterIn);
            sendSlice(fBufferSize);
            recvSlice(fBufferSize);
            ControlUI::decode_midi_control(fControlOutputs[0], fOutControl, fCounterOut);
        }
        
        if (lastCycle > 0) {
            setupBuffers(input, output, i*fBufferSize);
            ControlUI::encode_midi_control(fControlInputs[0], fInControl, fCounterIn);
            fillBufferWithZerosOffset(getNumInputs(), lastCycle, fBufferSize-lastCycle, fAudioInputs);
            sendSlice(lastCycle);
            recvSlice(lastCycle);
            ControlUI::decode_midi_control(fControlOutputs[0], fOutControl, fCounterOut);
        }
        
    } else {
        fillBufferWithZerosOffset(getNumOutputs(), 0, count, output);
    }
}

void remote_dsp_aux::metadata(Meta* m)
{ 
    fFactory->metadataRemoteDSPFactory(m);
}

// Accessors to number of input/output of DSP
int remote_dsp_aux::getNumInputs()
{ 
     return fFactory->numInputs();
}

int remote_dsp_aux::getNumOutputs()
{ 
    return fFactory->numOutputs();
}

// Useless fonction in our case but required for a DSP interface
//Interesting to implement one day ! 
void remote_dsp_aux::init(int /*sampling_rate*/){}

// Init remote dsp instance sends a POST request to a remote server
// The URL extension used is /CreateInstance
// The datas to send are NetJack parameters & the factory index it is create from
// A NetJack master is created to open a connection with the slave opened on the server's side
bool remote_dsp_aux::init(int argc, const char *argv[], 
                        int sampling_rate, 
                        int buffer_size, 
                        RemoteDSPErrorCallback error_callback, 
                        void* error_callback_arg, 
                        int& error)
{
    
    fBufferSize = buffer_size;
    
    fErrorCallback = error_callback;
    fErrorCallbackArg = error_callback_arg;
     
// Init Control Buffers

    fOutControl = new float[buffer_size];
    fInControl = new float[buffer_size];

    fControlInputs[0] = new float[8192];
    fControlOutputs[0] = new float[8192];
 
    memset(fOutControl, 0, sizeof(float)*buffer_size);
    memset(fInControl, 0, sizeof(float)*buffer_size);
    
    memset(fControlInputs[0], 0, sizeof(float)*8192);
    memset(fControlOutputs[0], 0, sizeof(float)*8192);
    
    // To be sure fCounterIn and fCounterOut are set before 'compute' is called, even if no 'buildUserInterface' is called by the client
    ControlUI dummy_ui;
    buildUserInterface(&dummy_ui);
    
    bool partial_cycle = atoi(getValueFromKey(argc, argv, "--NJ_partial", "0"));
    
    const char* port = getValueFromKey(argc, argv, "--NJ_port", "19000");
    
// PREPARE URL TO SEND TO SERVER
    
// Parse NetJack Parameters
    string finalRequest = "NJ_ip=";
    finalRequest += string(getValueFromKey(argc, argv, "--NJ_ip", searchIP().c_str()));
  
    finalRequest += "&NJ_port=";
    finalRequest += string(port);
    
    finalRequest += "&NJ_compression=";
    finalRequest += string(getValueFromKey(argc, argv, "--NJ_compression", "-1"));
    
    finalRequest += "&NJ_latency=";
    finalRequest += string(getValueFromKey(argc, argv, "--NJ_latency", "2"));
    
    finalRequest += "&NJ_mtu=";
    finalRequest += string(getValueFromKey(argc, argv, "--NJ_mtu", "1500"));
    
    finalRequest += "&factoryKey=";
    finalRequest += fFactory->key();
    
    finalRequest += "&instanceKey=";
    
    stringstream s;
    s << this;
    
    finalRequest += s.str();
    printf("finalRequest = %s\n", finalRequest.c_str());
    
    bool isInitSuccessfull = false;
        
    string ip = fFactory->serverIP();
    ip += "/CreateInstance";
        
    string response("");
    int errorCode = -1;

// OPEN NET JACK CONNECTION
    if(send_request(ip, finalRequest, response, errorCode)){
        printf("BS & SR = %i | %i\n", buffer_size, sampling_rate);
        
        jack_master_t request = { -1, -1, -1, -1, static_cast<jack_nframes_t>(buffer_size), static_cast<jack_nframes_t>(sampling_rate), "test_master", 5, partial_cycle};
        jack_slave_t result;
        fNetJack = jack_net_master_open(DEFAULT_MULTICAST_IP, atoi(port), "net_master", &request, &result); 
        
        if (fNetJack) {
            isInitSuccessfull = true;
        } else {
            error = ERROR_NETJACK_NOTSTARTED;
        }
    } else {
        error = errorCode;
    }
    
    printf("remote_dsp_aux::init = %p || inputs = %i || outputs = %i\n", this, fFactory->numInputs(), fFactory->numOutputs());
    
    return isInitSuccessfull;
}                        

void remote_dsp_aux::stopAudio()
{
    string finalRequest = "instanceKey=";
    stringstream s;
    s << this;
    
    finalRequest += s.str();
    
    printf("REQUEST = %s\n", finalRequest.c_str());
    
    string ip = fFactory->serverIP();
    ip += "/StopAudio";
    
    string response("");
    int errorCode;
    send_request(ip, finalRequest, response, errorCode);
}

void remote_dsp_aux::startAudio()
{
   string finalRequest = "instanceKey=";
    
    stringstream s;
    s << this;
    
    finalRequest += s.str();
    
    printf("REQUEST = %s\n", finalRequest.c_str());
    
    string ip = fFactory->serverIP();
    ip += "/StartAudio";
    
    string response("");
    int errorCode;
    send_request(ip, finalRequest, response, errorCode);
}

//----------------------------------REMOTE DSP API-------------------------------------------

EXPORT int remote_dsp_factory::numInputs(){return fNumInputs;}
EXPORT int remote_dsp_factory::numOutputs(){return fNumOutputs;}

//---------INSTANCES

EXPORT remote_dsp* createRemoteDSPInstance(remote_dsp_factory* factory, 
                                        int argc, 
                                        const char *argv[], 
                                        int sampling_rate, 
                                        int buffer_size, 
                                        RemoteDSPErrorCallback error_callback, 
                                        void* error_callback_arg, 
                                        int& error)
{
    FactoryTableIt it;
    if ((it = remote_dsp_factory::gFactoryTable.find(factory)) != remote_dsp_factory::gFactoryTable.end()) {
        remote_dsp_aux* instance = factory->createRemoteDSPInstance(argc, argv, sampling_rate, buffer_size, error_callback, error_callback_arg, error);
        (*it).second.second.push_back(instance);
        return reinterpret_cast<remote_dsp*>(instance);
    } else {
        return 0;
    }
}

EXPORT void deleteRemoteDSPInstance(remote_dsp* dsp)
{
    FactoryTableIt it;
    remote_dsp_aux* dsp_aux = reinterpret_cast<remote_dsp_aux*>(dsp);
    remote_dsp_factory* factory = dsp_aux->getFactory();
    
    it = remote_dsp_factory::gFactoryTable.find(factory);
    assert(it != remote_dsp_factory::gFactoryTable.end());
    (*it).second.second.remove(dsp_aux);
    
    delete dsp_aux; 
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

EXPORT void remote_dsp::init(int sampling_rate)
{
    reinterpret_cast<remote_dsp_aux*>(this)->init(sampling_rate);
}

EXPORT void remote_dsp::buildUserInterface(UI* interface)
{
    reinterpret_cast<remote_dsp_aux*>(this)->buildUserInterface(interface);
}

EXPORT void remote_dsp::compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
{
    reinterpret_cast<remote_dsp_aux*>(this)->compute(count, input, output);
}

EXPORT void remote_dsp::startAudio()
{
    reinterpret_cast<remote_dsp_aux*>(this)->startAudio();
}

EXPORT void remote_dsp::stopAudio()
{
    reinterpret_cast<remote_dsp_aux*>(this)->stopAudio();
}

//------ DISCOVERY OF AVAILABLE MACHINES
static remote_DNS* gDNS = NULL;

__attribute__((constructor)) static void initialize_libfaustremote() 
{
    gDNS = new remote_DNS();
}

__attribute__((destructor)) static void destroy_libfaustremote()
{
    delete gDNS;
}

remote_DNS::remote_DNS()
{
  
    /* make address for multicast ip
     * pick a port number for you by passing NULL as the last argument */
    
    //    lo_address t = lo_address_new("224.0.0.1", "7770");
    // lo_server multi = lo_server_new_multicast("drone", "7771", error);
    /* start a new server on port 7770 */
    fLoThread = lo_server_thread_new_multicast("224.0.0.1", "7770", remote_DNS::errorHandler);
    
    /* add method that will match the path /foo/bar, with two numbers, coerced
     * to float and int */
    lo_server_thread_add_method(fLoThread, "/faustcompiler", "is", remote_DNS::pingHandler, this);
    
//    /* add method that will match the path /quit with no args */
//    lo_server_thread_add_method(fLoThread, "/quit", "", remote_DNS::quitHandler, this);
    
    lo_server_thread_start(fLoThread);
}
                                
remote_DNS::~remote_DNS()
{
    lo_server_thread_free(fLoThread);
}

void remote_DNS::errorHandler(int num, const char *msg, const char *path)
{
    printf("liblo server error %d in path %s: %s\n", num, path, msg);
}

/* catch any incoming messages and display them. returning 1 means that the
 * message has not been fully handled and the server should try other methods */
int remote_DNS::pingHandler(const char *path, const char *types, lo_arg ** argv,
                            int argc, void *data, void *user_data)
{
    remote_DNS* dns = (remote_DNS*)user_data;
    
    member messageSender;
    messageSender.pid = argv[0]->i;
    messageSender.hostname = (char *)argv[1];
    lo_timetag_now(&messageSender.timetag);
    ostringstream convert;
    convert << messageSender.pid;
    string key = messageSender.hostname + ":" + convert.str();
    
    if (dns->fLocker.Lock()) {
//        if (dns->fClients[key].timetag.sec == 0)
//            printf("remote_DNS::Connected HostName = %s\n", messageSender.hostname.c_str());
            
//        printf("Client %s updated timetag %i\n", key.c_str(), messageSender.timetag.sec);
        dns->fClients[key] = messageSender;
        gDNS->fLocker.Unlock();
    }
        
    return 0;
}

// Public API

EXPORT bool getRemoteMachinesAvailable(map<string, pair<string, int> >* machineList)
{
    if (gDNS && gDNS->fLocker.Lock()) {
        
        for(map<string, member>::iterator it=gDNS->fClients.begin(); it != gDNS->fClients.end(); it++){
            
            member iterMem = it->second;
            
            lo_timetag now;
            lo_timetag_now(&now);
            
//            If the server machine did not send a message for 3 secondes, it is considered disconnected
            if((now.sec - iterMem.timetag.sec) < 3){
                
//        Decompose HostName to have Name, Ip and Port of service
                string serviceNameCpy(iterMem.hostname);
                
                int pos = serviceNameCpy.find("._");
                string remainingString = serviceNameCpy.substr(pos+2, string::npos);
                pos = remainingString.find("._");
                string serviceIP = remainingString.substr(0, pos);
                
                string hostName = remainingString.substr(pos+2, string::npos);
                
                int pos2 = serviceIP.find(":");
                string ipAddr = serviceIP.substr(0, pos2);
                string port = serviceIP.substr(pos2+1, string::npos);
                
                (*machineList)[hostName] = make_pair(ipAddr, atoi(port.c_str()));
                
            }
        }
        
        gDNS->fLocker.Unlock();
        return true;
    } else {
       return false; 
    }
}

EXPORT bool getRemoteFactoriesAvailable(const string& ip_server, int port_server, vector<pair<string, string> >* factories_list)
{
    printf("remoteDSP::getRemoteFactoriesAvailable\n");
    
    bool isSuccessfull = false;
    CURL *curl = curl_easy_init();
    
    if (curl) {
        
        string ip = "http://";
        ip += ip_server;
        ip += ":";
        
        stringstream s;
        s<<port_server;
        
        ip += s.str();
        
        string finalIP = ip;
        finalIP += "/GetAvailableFactories";
            
        ostringstream oss;
            
        curl_easy_setopt(curl, CURLOPT_URL, finalIP.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &store_Response);
        curl_easy_setopt(curl, CURLOPT_FILE, &oss);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT ,15); 
        curl_easy_setopt(curl,CURLOPT_TIMEOUT, 15);
            
        CURLcode res = curl_easy_perform(curl);
            
        if(res == CURLE_OK){
            
            printf("remoteDSP::getRemoteFactoriesAvailable 1\n");    
            
            long respcode; //response code of the http transaction
            
            curl_easy_getinfo(curl,CURLINFO_RESPONSE_CODE, &respcode);
            
            if(respcode == 200){
 
                // PARSE RESPONSE TO EXTRACT KEY/VALUE
                
                string response = oss.str();
                stringstream os(response);   
                string name, key;   
                
                while (os >> key) {                
                    os >> name;
                    factories_list->push_back(make_pair(name, key));
                }
                    
                isSuccessfull = true;
            }
        }

        curl_easy_cleanup(curl);
    }
    
    return isSuccessfull;
}
