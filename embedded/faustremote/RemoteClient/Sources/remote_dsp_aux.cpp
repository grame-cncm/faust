
#include "remote_dsp_aux.h"

// Standard Callback to store a server response in strinstream
size_t store_Response(void *buf, size_t size, size_t nmemb, void* userp){
    
    std::ostream& os = *static_cast<std::ostream*>(userp);
    std::streamsize len = size * nmemb;
    if(os.write(static_cast<char*>(buf), len))
        return len;
    else
        return 0;
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
        finalRequest += "&data=";
        
// Transforming faustCode to URL format
        finalRequest += curl_easy_escape(curl , dspContent.c_str() , dspContent.size());
        
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
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, finalRequest.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long) strlen(finalRequest.c_str()));
        
        std::ostringstream oss;
        
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &store_Response);
        curl_easy_setopt(curl, CURLOPT_FILE, &oss);
//        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
        
        CURLcode res = curl_easy_perform(curl);
        
        if(res != CURLE_OK)
            error =  curl_easy_strerror(res);

        else{        
            
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
        
        // The index of the factory to delete has to be sent
        string finalRequest = "factoryIndex=";
        finalRequest += fIndex;
        
        string ip(fServerIP);
        ip += "/DeleteFactory";
        
        curl_easy_setopt(curl, CURLOPT_URL, ip.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, finalRequest.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long) strlen(finalRequest.c_str()));
        
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
    
    fIndex = fMetadatas["indexFactory"];
    fMetadatas.erase("indexFactory");
}

// Declaring meta datas
void remote_dsp_factory::metadataRemoteDSPFactory(Meta* m) { 
    
    map<string,string>::iterator it;
    
    for(it = fMetadatas.begin() ; it != fMetadatas.end(); it++)
        m->declare(it->first.c_str(), it->second.c_str());
}   

// Create Remote DSP Instance from factory
remote_dsp_aux* remote_dsp_factory::createRemoteDSPInstance(int argc, const char *argv[], int samplingRate, int bufferSize, string& error){
 
    remote_dsp_aux* dsp = new remote_dsp_aux(this);
    
    if(dsp->init(argc, argv, samplingRate, bufferSize, error)){
        return dsp; 
    }
    else{
        delete dsp;
        return NULL;
    }
}


//---------FACTORY

#include <libgen.h>

static string PathToContent(const string& path)
{
    ifstream f(path.c_str());
    string result;
    char line[4096];
    
    while (f.getline(line, 4096)) {
        result += line;
        if (!f.fail()) {
            result += "\n";
        }
    }
    
    f.close();
    return result;
}


EXPORT remote_dsp_factory* createRemoteDSPFactoryFromFile( const string& filename, int argc, const char *argv[], const string& ipServer, int portServer, string& error, int opt_level){
    
    string name("");
    
    string base = basename((char*)filename.c_str());
    
    int pos = base.find(".dsp");
    
    if(pos != string::npos){
        name = base.substr(0, pos);
    }
    else{
        error = "File Extension is not the one expected (.dsp expected)";
        return NULL;
    }
    
    printf("NAME = %s\n", name.c_str());
    
    return createRemoteDSPFactoryFromString(name, PathToContent(filename), argc, argv, ipServer, portServer, error, opt_level);
}

EXPORT remote_dsp_factory* createRemoteDSPFactoryFromString(const string& name_app, const string& dsp_content, int argc, const char *argv[], const string& ipServer, int portServer, string& error, int opt_level){
    
    remote_dsp_factory* factory = new remote_dsp_factory();
    
    if(factory->init(argc, argv, ipServer, portServer, name_app, dsp_content, error, opt_level))
        return factory;
    else{
        delete factory;
        return NULL;
    }
}

EXPORT void deleteRemoteDSPFactory(remote_dsp_factory* factory){
    
    factory->stop();
    delete factory;
}

EXPORT void metadataRemoteDSPFactory(remote_dsp_factory* factory, Meta* m){factory->metadataRemoteDSPFactory(m);}

//--------------------INSTANCES

remote_dsp_aux::remote_dsp_aux(remote_dsp_factory* factory){
    
    fFactory = factory;
    fNetJack = NULL;
    
    fInputs = new float*[getNumInputs() + 1];
    fOutputs = new float*[getNumOutputs() + 1];
}
        
remote_dsp_aux::~remote_dsp_aux(){

    delete[] fInputs;
    delete[] fOutputs;
    
    if(fNetJack){
        
        delete[] fInControl;
        delete[] fOutControl;
        
        jack_net_master_close(fNetJack); 
        fNetJack = 0;
    }
}

void remote_dsp_aux::fillBufferWithZeros(int size1, int size2, FAUSTFLOAT** buffer){
    
    // Cleanup audio buffers only (not control one)
    for (int i=1; i<size1; i++) {
        memset(buffer[i], 0, sizeof(float)*size2);
    }
}

// Fonction for command line parsing
const char*  remote_dsp_aux::getValueFromKey(int argc, const char *argv[], const char *key, const char* defaultValue){
	
    for (int i = 0; i<argc; i++){
        if (strcmp(argv[i], key) == 0) 
            return argv[i+1];   
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
    
    setlocale(LC_ALL, tmp_local);
}

// Compute of the DSP, adding the controls to the input/output passed
void remote_dsp_aux::compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output){
    
    int numberOfCycles = count/fBufferSize;

//      If the count > fBufferSize : the cycle is divided in n number of netjack cycles
    for(int i=0; i<numberOfCycles; i++){
        
        fInputs[0] = fInControl;
        
        int offset = i*fBufferSize;
        
//        printf("OFFSET = %i\n", offset);
        
        for(int i=0; i<getNumInputs();i++)
            fInputs[i+1] = &input[i][offset];
        
        fOutputs[0] = fOutControl;
        
        for(int i=0; i<getNumOutputs();i++)
            fOutputs[i+1] = &output[i][offset];
        
        int res;
        
        if ((res = jack_net_master_send(fNetJack, getNumInputs()+1, fInputs, 0, NULL)) < 0){
            fillBufferWithZeros(getNumOutputs()+1, fBufferSize, fOutputs);
            printf("jack_net_master_send failure %d\n", res);
        }
        if ((res = jack_net_master_recv(fNetJack, getNumOutputs()+1, fOutputs, 0, NULL)) < 0) {
            printf("jack_net_master_recv failure %d\n", res);
            fillBufferWithZeros(getNumOutputs()+1, fBufferSize, fOutputs);
        }
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
bool remote_dsp_aux::init(int argc, const char *argv[], int samplingFreq, int buffer_size, string& error){
    
    fBufferSize = buffer_size;
     
//  Init Control Buffers
    fOutControl = new float[buffer_size];
    fInControl = new float[buffer_size];
    
    memset(fOutControl, 0, sizeof(float)*buffer_size);
    memset(fInControl, 0, sizeof(float)*buffer_size);
    
//  PREPARE URL TO SEND TO SERVER
    
// Parse NetJack Parameters
    string finalRequest = "NJ_IP=";
    finalRequest += string(getValueFromKey(argc, argv, "--NJ_ip", DEFAULT_MULTICAST_IP));

    finalRequest += "&NJ_Port=";
    finalRequest += string(getValueFromKey(argc, argv, "--NJ_port", "19000"));
    
    finalRequest += "&NJ_Compression=";
    finalRequest += string(getValueFromKey(argc, argv, "--NJ_compression", "-1"));
    
    finalRequest += "&NJ_Latency=";
    finalRequest += string(getValueFromKey(argc, argv, "--NJ_latency", "2"));
    
    finalRequest += "&NJ_MTU=";
    finalRequest += string(getValueFromKey(argc, argv, "--NJ_mtu", "1500"));
    
    finalRequest += "&factoryIndex=";
    finalRequest += fFactory->index();
    
    printf("finalRequest = %s\n", finalRequest.c_str());
    
    
//  Curl Connection setup
    CURL *curl = curl_easy_init();
    
    bool   isInitSuccessfull = false;
    
    if (curl) {
        
        string ip = fFactory->serverIP();
        ip += "/CreateInstance";
        
        std::ostringstream oss;
        
        curl_easy_setopt(curl, CURLOPT_URL, ip.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, finalRequest.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long) strlen(finalRequest.c_str()));
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &store_Response);
        curl_easy_setopt(curl, CURLOPT_FILE, &oss);
        
        CURLcode res = curl_easy_perform(curl);
        
        if(res != CURLE_OK)
            error = curl_easy_strerror(res);
        else{
            
            long respcode; //response code of the http transaction
            
            curl_easy_getinfo(curl,CURLINFO_RESPONSE_CODE, &respcode);
            
            if(respcode == 200){
                
                //              OPEN NET JACK CONNECTION
                
                printf("BS & SR = %i | %i\n", buffer_size, samplingFreq);
                
                jack_master_t request = { -1, -1, -1, -1, buffer_size, samplingFreq, "test_master", 5};
                
                jack_slave_t result;
                
                fNetJack = jack_net_master_open(DEFAULT_MULTICAST_IP, DEFAULT_PORT, "net_master", &request, &result); 
                
                if(fNetJack)
                    isInitSuccessfull = true;
                else
                    error = "Impossible to open NetJack master";
            }
            else if(respcode == 400)
                error = oss.str();
        }
        
        curl_easy_cleanup(curl);
    }
    else
        error = "Impossible to open http connection";
    
    return isInitSuccessfull;
}                        

//----------------------------------REMOTE DSP API-------------------------------------------

//---------INSTANCES

EXPORT remote_dsp* createRemoteDSPInstance(remote_dsp_factory* factory, int argc, const char *argv[], int samplingRate,int bufferSize, string& error){
    
    return reinterpret_cast<remote_dsp*>(factory->createRemoteDSPInstance(argc, argv, samplingRate, bufferSize, error));
}

EXPORT void deleteRemoteDSPInstance(remote_dsp* dsp){
    
    delete reinterpret_cast<remote_dsp_aux*>(dsp); 
}

EXPORT int remote_dsp::getNumInputs()
{
    return reinterpret_cast<remote_dsp_aux*>(this)->getNumInputs();
}

int EXPORT remote_dsp::getNumOutputs()
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

EXPORT bool        getRemoteMachinesAvailable(map<string, pair<string, int> >* machineList){
    
    DNSServiceRef sd;
    
//  Initialize DNSServiceREF && bind it to its callback
    DNSServiceErrorType err = DNSServiceBrowse(&sd, 0, 0, "_http._tcp", NULL, &browsingCallback, machineList);
    
    if(err == kDNSServiceErr_NoError){
        
//      SELECT IS USED TO SET TIMEOUT  
        fd_set readfds;
        FD_ZERO(&readfds);
        
        FD_SET(DNSServiceRefSockFD(sd), &readfds);
        
        struct timeval tv = { 0, 100 };
        int result = select(0, &readfds, (fd_set*)NULL, (fd_set*)NULL, &tv);
        
        if ( result < 0 ) 
            printf("SELECT ERROR\n");
        
//      Process Result will call the appriate callback binded to ServiceRef
        else
            DNSServiceErrorType err = DNSServiceProcessResult(sd);
        
//      Cleanup DNSService  
        DNSServiceRefDeallocate(sd);
        
        return true;
    }
    else
        return false;
}