
#include "remote_dsp_aux.h"
#include "faust/gui/ControlUI.h"
#include "faust/llvm-dsp.h"

// Standard Callback to store a server response in strinstream
size_t store_Response(void *buf, size_t size, size_t nmemb, void* userp)
{
    std::ostream* os = static_cast<std::ostream*>(userp);
    std::streamsize len = size * nmemb;
    return (os->write(static_cast<char*>(buf), len)) ? len : 0;
}

//------------------FACTORY

// Init remote dsp factory sends a POST request to a remote server
// The URL extension used is /GetJson
// The datas have a url-encoded form (key/value separated by & and special character are reencoded like spaces = %)
bool remote_dsp_factory::init(int argc, const char *argv[], const string& ipServer, int portServer, const string& nameApp, string dspContent, string& error, int opt_level){

    bool isInitSuccessfull = false;
    
    CURL *curl = curl_easy_init();
    
    if (curl) {

        string finalRequest = "name=";
        finalRequest += nameApp;
        
// Adding Compilation Options to request data
        
        finalRequest += "&number_options=";
        
        stringstream nb;
        nb<<argc;
        
        finalRequest += nb.str();
        
        for(int i=0; i<argc; i++){
            finalRequest += "&options=";
            finalRequest += argv[i];
        }
        
// Adding LLVM optimization Level to request data
        finalRequest += "&opt_level=";
        stringstream ol;
        ol<<opt_level;
        finalRequest +=ol.str(); 
        
        printf("finalRequest = %s\n", finalRequest.c_str());

        
        finalRequest += "&data=";
        
        // Transforming faustCode to URL format
        finalRequest += curl_easy_escape(curl , dspContent.c_str() , dspContent.size());
        
        
        fServerIP = "http://";
        fServerIP += ipServer;
        fServerIP += ":";
        
        stringstream s;
        s<<portServer;
        
        fServerIP += s.str();
        
        string ip = fServerIP;
        ip += "/GetJson";
        
        printf("ip = %s\n", ip.c_str());
        
        
        
// Connection Setups
        curl_easy_setopt(curl, CURLOPT_URL, ip.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long) (finalRequest.size()));
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, finalRequest.c_str());
        
        std::ostringstream oss;
        
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &store_Response);
        curl_easy_setopt(curl, CURLOPT_FILE, &oss);
//        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT ,15); 
        curl_easy_setopt(curl,CURLOPT_TIMEOUT, 15);
        
        CURLcode res = curl_easy_perform(curl);
        
        if(res != CURLE_OK) {
            error =  curl_easy_strerror(res);
        } else {        
            
            //Response code of the http transaction
            long respcode;
            curl_easy_getinfo(curl,CURLINFO_RESPONSE_CODE, &respcode);
            
            if(respcode == 200){
                decodeJson(oss.str());
                isInitSuccessfull = true;
            }
            else if(respcode == 400)
                error = oss.str();
        }
        
        curl_easy_cleanup(curl); //Standard CleanUp
    }
    
    return isInitSuccessfull;
}

// Delete remote dsp factory sends an explicit delete request to server
void remote_dsp_factory::stop(){
    
    CURL *curl = curl_easy_init();
    
    if (curl) {
        
        printf("fIndex = %s\n", fSHAKey.c_str());
        printf("fIP = %s\n", fServerIP.c_str());
        
        // The index of the factory to delete has to be sent
        string finalRequest = string("factoryKey=") + fSHAKey;
        string ip = fServerIP + string("/DeleteFactory");
        
        curl_easy_setopt(curl, CURLOPT_URL, ip.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)(finalRequest.size()));
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, finalRequest.c_str());
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT ,15); 
        curl_easy_setopt(curl,CURLOPT_TIMEOUT, 15);
        
        CURLcode res = curl_easy_perform(curl);
        
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        
        curl_easy_cleanup(curl);
    }
}

// Decoding JSON from a string to
// fUiItems : Structure containing the graphical items
// fMetadatas : Structure containing the metadatas
// Some "extra" metadatas are kept separatly
void remote_dsp_factory::decodeJson(const string& json){
    
    const char* p = json.c_str();
    parseJson(p, fMetadatas, fUiItems);
    
    fNumInputs = atoi(fMetadatas["inputs"].c_str());
    fMetadatas.erase("inputs");
    
    fNumOutputs = atoi(fMetadatas["outputs"].c_str());
    fMetadatas.erase("outputs");
    
    fSHAKey = fMetadatas["factoryKey"];
    fMetadatas.erase("factoryKey");
}

// Declaring meta datas
void remote_dsp_factory::metadataRemoteDSPFactory(Meta* m) { 
    
    map<string,string>::iterator it;
    
    for(it = fMetadatas.begin() ; it != fMetadatas.end(); it++)
        m->declare(it->first.c_str(), it->second.c_str());
}   

// Create Remote DSP Instance from factory
remote_dsp_aux* remote_dsp_factory::createRemoteDSPInstance(int argc, const char *argv[], 
                                                            int samplingRate, int bufferSize, 
                                                            RemoteDSPErrorCallback error_callback, void* error_callback_arg, 
                                                            int& error){
 
    remote_dsp_aux* dsp = new remote_dsp_aux(this);
    
    if(dsp->init(argc, argv, samplingRate, bufferSize, error_callback, error_callback_arg, error)){
        return dsp; 
    } else {
        delete dsp;
        return NULL;
    }
}

//---------FACTORY

#include <libgen.h>

static string PathToContent(const string& path)
{
    ifstream file(path.c_str(), std::ifstream::binary);

    file.seekg (0, file.end);
    int size = file.tellg();
    file.seekg (0, file.beg);
   
    // And allocate buffer to that a single line can be read...
    char* buffer = new char[size + 1];
    file.read(buffer, size);
    
    // Terminate the string
    buffer[size] = 0;
    string result = buffer;
    file.close();
    delete [] buffer;
    return result;
}

// Expernal API

EXPORT remote_dsp_factory* createRemoteDSPFactoryFromFile(const string& filename, int argc, const char *argv[],  const string& ip_server, int port_server, string& error_msg, int opt_level){
    
    string name("");
    string base = basename((char*)filename.c_str());
    
    int pos = base.find(".dsp");
    
    if (pos != string::npos) {
        name = base.substr(0, pos);
    } else {
        error_msg = "File Extension is not the one expected (.dsp expected)";
        return NULL;
    }
    
    printf("NAME = %s\n", name.c_str());
    
    return createRemoteDSPFactoryFromString(name, PathToContent(filename), argc, argv, ip_server, port_server, error_msg, opt_level);
}

EXPORT remote_dsp_factory* createRemoteDSPFactoryFromString(const string& name_app, const string& dsp_content, int argc, const char *argv[], const string& ip_server, int port_server, string& error_msg, int opt_level){
    
    std::string expanded_dsp;
    
    // Use for it's possible 'side effects', that is generating SVG, XML... files
    printf("createRemoteDSPFactoryFromString %s\n", dsp_content.c_str()); 
    
    generateAuxFilesFromString(name_app, dsp_content, argc, argv, error_msg);
    
    if ((expanded_dsp = expandDSPFromString(name_app, dsp_content, argc, argv, error_msg)) == "") {
        return NULL;
    } else {
        remote_dsp_factory* factory = new remote_dsp_factory();
        if (factory->init(argc, argv, ip_server, port_server, name_app, expanded_dsp, error_msg, opt_level)) {
            return factory;
        } else {
            delete factory;
            return NULL;
        }
    }
}

EXPORT void deleteRemoteDSPFactory(remote_dsp_factory* factory)
{
    if (factory) {
        factory->stop();
        delete factory;
    }
}

EXPORT void metadataRemoteDSPFactory(remote_dsp_factory* factory, Meta* m)
{
    factory->metadataRemoteDSPFactory(m);
}

//--------------------INSTANCES

remote_dsp_aux::remote_dsp_aux(remote_dsp_factory* factory){
    
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
        
remote_dsp_aux::~remote_dsp_aux(){

    printf("remote_dsp_aux::~remote_dsp_aux = %p\n", this);
    
    if (fNetJack){
    
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

void remote_dsp_aux::fillBufferWithZerosOffset(int channels, int offset, int size, FAUSTFLOAT** buffer){
    
    // Cleanup audio buffers only 
    for (int i = 0; i < channels; i++) {
        memset(&buffer[i][offset], 0, sizeof(float)*size);
    }
}

// Fonction for command line parsing
const char* remote_dsp_aux::getValueFromKey(int argc, const char *argv[], const char *key, const char* defaultValue){
	
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
    
    for(it = jsonItems.begin(); it != jsonItems.end() ; it++){
        
        float init = strtod((*it)->init.c_str(), NULL);
        float min = strtod((*it)->min.c_str(), NULL);
        float max = strtod((*it)->max.c_str(), NULL);
        float step = strtod((*it)->step.c_str(), NULL);
        
        map<string,string>::iterator it2;
        
        bool isInItem = false;
        bool isOutItem = false;
        
//        Meta Data declaration for entry items
        if((*it)->type.find("group") == string::npos && (*it)->type.find("bargraph") == string::npos && (*it)->type.compare("close")!=0){
            
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

// Compute of the DSP, adding the controls to the input/output passed
void remote_dsp_aux::compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output){
    
//    printf("remote_dsp_aux::compute = %p\n", this);
    
    if(fRunningFlag){
        
        int numberOfCycles = count/fBufferSize;
        int lastCycle = count%fBufferSize;
        int res;
        
        // If the count > fBufferSize : the cycle is divided in n number of netjack cycles
        int i = 0;
        
        for (i=0; i<numberOfCycles; i++) {
            
            int offset = i*fBufferSize;
            setupBuffers(input, output, offset);
            
            ControlUI::encode_midi_control(fControlInputs[0], fInControl, fCounterIn);
            
            if ((res = jack_net_master_send(fNetJack, getNumInputs(), fAudioInputs, 1, (void**)fControlInputs)) < 0){
                fillBufferWithZerosOffset(getNumOutputs(), 0, fBufferSize, fAudioOutputs);
                if (fErrorCallback) {
                    if(fErrorCallback(WRITE_ERROR, fErrorCallbackArg)==-1)
                        fRunningFlag = false;
                }
            }
            if ((res = jack_net_master_recv(fNetJack, getNumOutputs(), fAudioOutputs, 1, (void**)fControlOutputs)) < 0) {
                fillBufferWithZerosOffset(getNumOutputs(), 0, fBufferSize, fAudioOutputs);
                if (fErrorCallback) {
                    if(fErrorCallback(READ_ERROR, fErrorCallbackArg) == -1)
                    fRunningFlag = false;
                }
            }
            
            ControlUI::decode_midi_control(fControlOutputs[0], fOutControl, fCounterOut);
        }
        
        if (lastCycle > 0) {
            
            int offset = i*fBufferSize;
            setupBuffers(input, output, offset);
            
            ControlUI::encode_midi_control(fControlInputs[0], fInControl, fCounterIn);
            
            fillBufferWithZerosOffset(getNumInputs(), lastCycle, fBufferSize-lastCycle, fAudioInputs);
            
            if ((res = jack_net_master_send_slice(fNetJack, getNumInputs(), fAudioInputs, 1, (void**)fControlInputs, lastCycle)) < 0){
                fillBufferWithZerosOffset(getNumOutputs(), 0, lastCycle, fAudioOutputs);
                if (fErrorCallback) {
                    if(fErrorCallback(WRITE_ERROR, fErrorCallbackArg)==-1)
                        fRunningFlag = false;
                }
            }
            if ((res = jack_net_master_recv_slice(fNetJack, getNumOutputs(), fAudioOutputs, 1, (void**)fControlOutputs, lastCycle)) < 0) {
                fillBufferWithZerosOffset(getNumOutputs(), 0, lastCycle, fAudioOutputs);
                if (fErrorCallback) {
                    if(fErrorCallback(READ_ERROR, fErrorCallbackArg) == -1)
                        fRunningFlag = false;
                }
            }
            
            ControlUI::decode_midi_control(fControlOutputs[0], fOutControl, fCounterOut);
        }
    }
    else{
        fillBufferWithZerosOffset(getNumOutputs(), 0, count, output);
    }
}

// Accessors to number of input/output of DSP
int remote_dsp_aux::getNumInputs(){ 
    
    return fFactory->numInputs();
}

int remote_dsp_aux::getNumOutputs(){ 
    
    return fFactory->numOutputs();
}

// Useless fonction in our case but required for a DSP interface
void remote_dsp_aux::init(int /*samplingFreq*/){}

// Init remote dsp instance sends a POST request to a remote server
// The URL extension used is /CreateInstance
// The datas to send are NetJack parameters & the factory index it is create from
// A NetJack master is created to open a connection with the slave opened on the server's side
bool remote_dsp_aux::init(int argc, const char *argv[], int samplingFreq, int buffer_size, RemoteDSPErrorCallback error_callback, void* error_callback_arg, int& error){
    
    fBufferSize = buffer_size;
    
    fErrorCallback = error_callback;
    fErrorCallbackArg = error_callback_arg;
     
//  Init Control Buffers

    fOutControl = new float[buffer_size];
    fInControl = new float[buffer_size];

    fControlInputs[0] = new float[8192];
    fControlOutputs[0] = new float[8192];
 
    memset(fOutControl, 0, sizeof(float)*buffer_size);
    memset(fInControl, 0, sizeof(float)*buffer_size);
    
    memset(fControlInputs[0], 0, sizeof(float)*8192);
    memset(fControlOutputs[0], 0, sizeof(float)*8192);
    
    bool partial_cycle = atoi(getValueFromKey(argc, argv, "--NJ_partial", "0"));
    
    const char* port = getValueFromKey(argc, argv, "--NJ_port", "19000");
    
//  PREPARE URL TO SEND TO SERVER
    
// Parse NetJack Parameters
    string finalRequest = "NJ_ip=";
    finalRequest += string(getValueFromKey(argc, argv, "--NJ_ip", DEFAULT_MULTICAST_IP));

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
    
    //printf("finalRequest = %s\n", finalRequest.c_str());
    
//  Curl Connection setup
    CURL *curl = curl_easy_init();
    
    bool isInitSuccessfull = false;
    
    if (curl) {
        
        string ip = fFactory->serverIP();
        ip += "/CreateInstance";
        
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
        
        if(res != CURLE_OK)
            error = ERROR_CURL_CONNECTION;
        else{
            
            long respcode; //response code of the http transaction
            
            curl_easy_getinfo(curl,CURLINFO_RESPONSE_CODE, &respcode);
            
            if(respcode == 200){
                
                //              OPEN NET JACK CONNECTION
                
                printf("BS & SR = %i | %i\n", buffer_size, samplingFreq);
                
                jack_master_t request = { -1, -1, -1, -1, static_cast<jack_nframes_t>(buffer_size), static_cast<jack_nframes_t>(samplingFreq), "test_master", 5, partial_cycle};
                jack_slave_t result;
                fNetJack = jack_net_master_open(DEFAULT_MULTICAST_IP, atoi(port), "net_master", &request, &result); 
                
                if(fNetJack)
                    isInitSuccessfull = true;
                else
                    error = ERROR_NETJACK_NOTSTARTED;
            }
            else if(respcode == 400)
                error = atoi(oss.str().c_str());
        }
        
        curl_easy_cleanup(curl);
    }
    else
        error = ERROR_CURL_CONNECTION;
    
    printf("remote_dsp_aux::init = %p || inputs = %i || outputs = %i\n", this, fFactory->numInputs(), fFactory->numOutputs());
    
    return isInitSuccessfull;
}                        

//----------------------------------REMOTE DSP API-------------------------------------------

//---------INSTANCES

EXPORT remote_dsp* createRemoteDSPInstance(remote_dsp_factory* factory, int argc, const char *argv[], int samplingRate, int bufferSize, RemoteDSPErrorCallback error_callback, void* error_callback_arg, int& error){
    
    return reinterpret_cast<remote_dsp*>(factory->createRemoteDSPInstance(argc, argv, samplingRate, bufferSize, error_callback, error_callback_arg, error));
}

EXPORT void deleteRemoteDSPInstance(remote_dsp* dsp){
    
    delete reinterpret_cast<remote_dsp_aux*>(dsp); 
}

EXPORT int remote_dsp::getNumInputs()
{
    return reinterpret_cast<remote_dsp_aux*>(this)->getNumInputs();
}

EXPORT int remote_dsp::getNumOutputs()
{
    return reinterpret_cast<remote_dsp_aux*>(this)->getNumOutputs();
}

EXPORT void remote_dsp::init(int samplingFreq)
{
    reinterpret_cast<remote_dsp_aux*>(this)->init(samplingFreq);
}

EXPORT void remote_dsp::buildUserInterface(UI* interface)
{
    reinterpret_cast<remote_dsp_aux*>(this)->buildUserInterface(interface);
}

EXPORT void remote_dsp::compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
{
    reinterpret_cast<remote_dsp_aux*>(this)->compute(count, input, output);
}

//------ DISCOVERY OF AVAILABLE MACHINES

//--- Callback whenever a server in the regtype/replyDomain is found
static void browsingCallback(DNSServiceRef sdRef, DNSServiceFlags flags, uint32_t interfaceIndex, DNSServiceErrorType errorCode, const char *serviceName, const char *regtype, const char *replyDomain, void *context ){
    
    map<string, pair<string,int> >* machineList = (map<string, pair< string, int> >*)context;
    
    string serviceNameCpy(serviceName);
    
    int pos = serviceNameCpy.find("._");
    
//   DIVIDED SERVICE NAME INTO NameOfService && IPaddress & hostName 
    if(serviceNameCpy.substr(0, pos).compare("FaustCompiler") == 0){
        
        string remainingString = serviceNameCpy.substr(pos+2, string::npos);
        
        pos = remainingString.find("._");
        
        string serviceIP = remainingString.substr(0, pos);
        string hostName = remainingString.substr(pos+2, string::npos);
        
        if(flags == kDNSServiceFlagsAdd || kDNSServiceFlagsMoreComing){
         
            int pos = serviceIP.find(":");
            
            string ipAddr = serviceIP.substr(0, pos);
            string port = serviceIP.substr(pos+1, string::npos);
            
            (*machineList)[hostName] = make_pair(ipAddr, atoi(port.c_str()));
        }
        else
            machineList->erase(hostName);
    }
}

//--- Research of available remote machines

EXPORT bool getRemoteMachinesAvailable(map<string, pair<string, int> >* machineList){
    
    DNSServiceRef sd;
    
//  Initialize DNSServiceREF && bind it to its callback
    DNSServiceErrorType err = DNSServiceBrowse(&sd, 0, 0, "_http._tcp", NULL, &browsingCallback, machineList);
    
    if (err == kDNSServiceErr_NoError){
        
//      SELECT IS USED TO SET TIMEOUT  

        int fd = DNSServiceRefSockFD(sd);
        int nfds = fd + 1;
        struct timeval tv = { 0, 100000 };
        
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);
        
        if (select(nfds, &readfds, (fd_set*)NULL, (fd_set*)NULL, &tv) > 0 && FD_ISSET(fd, &readfds)) {
            DNSServiceErrorType err = DNSServiceProcessResult(sd);
        }
        
//      Cleanup DNSService  

        DNSServiceRefDeallocate(sd);
        return true;
    } else {
        return false;
    }
}

