

#include "remote_dsp_aux.h"

const char* lopts(char *argv[], const char *name, const char* def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return argv[i+1];
	return def;
}

//------------------FACTORY

size_t remote_dsp_factory::store_Response(void *buf, size_t size, size_t nmemb, void* userp){
    
    std::ostream& os = *static_cast<std::ostream*>(userp);
    std::streamsize len = size * nmemb;
    if(os.write(static_cast<char*>(buf), len))
        return len;
    else
        return 0;
}

string getValue(int argc, char** argv, const string& key, vector<int>* toBePassed){
    
    for(int i = 0; i < argc ; i++){
        
        if(key.compare(argv[i]) == 0){
            toBePassed->push_back(i);
            toBePassed->push_back(i+1);
            return argv[i+1];;
        }
    }
    
    return "";
}

remote_dsp_factory::remote_dsp_factory(){}

bool remote_dsp_factory::init(string ipServer, string dspContent, int argc, char** argv, int opt_level, string& error){
    
    bool isInit = false;
    
    fServerIP = ipServer;
    
    CURL *curl;
    CURLcode res;
    
    std::ostringstream oss;
    
    curl = curl_easy_init();
    
    string finalString = "data=";
    finalString += curl_easy_escape(curl , dspContent.c_str() , dspContent.size());
    
    string IP, Port, Latency, CV;
    
    vector<int> toBePassed;
    
    IP = lopts(argv, "--NJ_ip", "");
    Port = lopts(argv, "--NJ_port", "");
    Latency = lopts(argv, "--NJ_latency", "");
    CV = lopts(argv, "--NJ_compression", "");
    
    fIP = IP;
    fPort = Port;
    fLatency = Latency;
    fCV = CV;
    
    finalString += "&options=";
    
    for(int i=1; i<argc; i++){
        
        if(string(argv[i]).find("--")!=string::npos){
            i ++;
        }
        else{
            finalString += argv[i];
            finalString += "%";
        }
    }
    
    finalString += "&opt_level=";
    stringstream ol;
    ol<<opt_level;
    finalString +=ol.str(); 
    
    
    printf("finalString = %s\n", finalString.c_str());
    
    if (curl) {
        
        string ip = ipServer;
        ip += "/GetJson";
        
        curl_easy_setopt(curl, CURLOPT_URL, ip.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, finalString.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long) strlen(finalString.c_str()));
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &remote_dsp_factory::store_Response);
        curl_easy_setopt(curl, CURLOPT_FILE, &oss);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
        
        res = curl_easy_perform(curl);
        
        long respcode; //response code of the http transaction
        
        curl_easy_getinfo(curl,CURLINFO_RESPONSE_CODE, &respcode);
        
        printf("RESPONSE CODE= %ld\n", respcode);
        
        if(res != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            error =  curl_easy_strerror(res);
        }
        else{
            if(respcode == 200){
                fJsonResponse = oss.str();
                //            fprintf(stderr, "curl_easy_perform() success: %s\n", oss.str().c_str());
                //            printf("fJsonResponse = %s\n", fJsonResponse.c_str());
                isInit = true;
            }
            else if(respcode == 400)
                error = oss.str();
            
        }
        curl_easy_cleanup(curl);
    }
    
    return isInit;
}

remote_dsp_factory::~remote_dsp_factory(){}

void remote_dsp_factory::stop(){
    
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    
    string finalString = "factoryIndex=";
    finalString += fIndex;
    
    //    printf("finalString = %s\n", finalString.c_str());
    
    if (curl) {
        
        string ip = fServerIP;
        ip += "/DeleteFactory";
        
        curl_easy_setopt(curl, CURLOPT_URL, ip.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, finalString.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long) strlen(finalString.c_str()));
        
        res = curl_easy_perform(curl);
        
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        //        else
        //            fprintf(stderr, "curl_easy_perform() success \n");
        
        curl_easy_cleanup(curl);
    }
}

string remote_dsp_factory::json(){
    
    return fJsonResponse;
}

remote_dsp_aux* remote_dsp_factory::createRemoteDSPInstance(int samplingRate, int bufferSize, string& error){
 
    printf("CREATE REMOTE DSP\n");
    
    remote_dsp_aux* dsp = new remote_dsp_aux;
    
    dsp->setFactory(this);
    dsp->decodeJson(this->json());
    
    if(dsp->init(samplingRate, bufferSize, error)){
        return dsp; 
    }
    else{
        delete dsp;
        return NULL;
    }
}

//--------------------INSTANCES

size_t remote_dsp_aux::store_Response(void *buf, size_t size, size_t nmemb, void* userp){
    
    std::ostream& os = *static_cast<std::ostream*>(userp);
    std::streamsize len = size * nmemb;
    if(os.write(static_cast<char*>(buf), len))
        return len;
    else
        return 0;
}

remote_dsp_aux::remote_dsp_aux(){

    fNetJack = NULL;
}
        
remote_dsp_aux::~remote_dsp_aux(){

    if(fNetJack){
        
        delete fInControl;
        delete fOutControl;
        
        delete fInputs;
        delete fOutputs;
        
        jack_net_master_close(fNetJack); 
        fNetJack = 0;
    }
}

int remote_dsp_aux::countItem(){
   
    int counter = 0;
    
    for(unsigned int i = 0; i<fUiItems.size(); i++){
        if(fUiItems[i]->type.find("group") == string::npos && fUiItems[i]->type.compare("close")!=0)
            counter++;
    }
    
    return counter;
}

//Decode fUiItems to build user interface
void remote_dsp_aux::buildUserInterface(UI* ui){

//    printf("REMOTEDSP::BUILDUSERINTERFACE\n");
    
//To be sure the float is correctly encoded
    char* tmp_local = setlocale(LC_ALL, NULL);
    setlocale(LC_ALL, "C");
    
    vector<itemInfo*>::iterator it;
    
    int counterIn = 0;
    int counterOut = 0;
    
    fNumItem = countItem();
    
    for(it = fUiItems.begin(); it != fUiItems.end() ; it++){
        
        float init = strtod((*it)->init.c_str(), NULL);
        float min = strtod((*it)->min.c_str(), NULL);
        float max = strtod((*it)->max.c_str(), NULL);
        float step = strtod((*it)->step.c_str(), NULL);
        
        map<string,string>::iterator it2;
        
        bool isInItem = false;
        bool isOutItem = false;
        
        if((*it)->type.find("group") == string::npos && (*it)->type.find("bargraph") == string::npos && (*it)->type.compare("close")!=0){
            
            fInControl[counterIn] = init;
            isInItem = true;
            
            for(it2 = (*it)->meta.begin(); it2 != (*it)->meta.end(); it2++)
                ui->declare(&fInControl[counterIn], it2->first.c_str(), it2->second.c_str());
        }
        else if((*it)->type.find("bargraph") != string::npos){
            
            fOutControl[counterOut] = init;
            isOutItem = true;
            
            for(it2 = (*it)->meta.begin(); it2 != (*it)->meta.end(); it2++){
                ui->declare(&fOutControl[counterOut], it2->first.c_str(), it2->second.c_str());
            }
        }
        else {
            for(it2 = (*it)->meta.begin(); it2 != (*it)->meta.end(); it2++)
                ui->declare(0, it2->first.c_str(), it2->second.c_str());
        }
        
        if((*it)->type.compare("hgroup") == 0)
            ui->openHorizontalBox((*it)->label.c_str());
        
        else if((*it)->type.compare("vgroup") == 0)
            ui->openVerticalBox((*it)->label.c_str());
        
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

void remote_dsp_aux::fillBufferWithZeros(int size1, int size2, FAUSTFLOAT** buffer){
    
    for(int i=0; i<size1; i++){
        for(int j=0; j<size2; j++)
            buffer[i][j] = 0.0f;
    }
}

//Compute of the DSP, adding the controls to the input/output passed
void remote_dsp_aux::compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output){
    
    fInputs[0] = fInControl;
    
    for(int i=0; i<getNumInputs();i++)
        fInputs[i+1] = input[i];
    
    fOutputs[0] = fOutControl;
    
    for(int i=0; i<getNumOutputs();i++)
        fOutputs[i+1] = output[i];
    
    int res;
    if ((res = jack_net_master_send(fNetJack, getNumInputs()+1, fInputs, 0, NULL)) < 0){
        fillBufferWithZeros(getNumOutputs(), count, output);
        printf("jack_net_master_send failure %d\n", res);
    }
    if ((res = jack_net_master_recv(fNetJack, getNumOutputs()+1, fOutputs, 0, NULL)) < 0) {
        printf("jack_net_master_recv failure %d\n", res);
        fillBufferWithZeros(getNumOutputs(), count, output);
    }
}

int remote_dsp_aux::getNumInputs(){ 
    
    return fNumInputs;
}

int remote_dsp_aux::getNumOutputs(){ 
    
    return fNumOutputs;
}

void remote_dsp_aux::init(int /*samplingFreq*/){}

bool remote_dsp_aux::init(int samplingFreq, int buffer_size, string& error){
    
//    INIT BUFFER SIZE
    fBufferSize = buffer_size;
    
    fOutControl = new float[fBufferSize];
    fInControl = new float[fBufferSize];
    
    for(int i=0; i<fBufferSize; i++){
        fOutControl[i] = 0.0f;
        fInControl[i] = 0.0f;
    }
    
//  INIT SAMPLING RATE
//    fSamplingFreq = samplingFreq;
    
    
//  PREPARE URL TO SEND TO SERVER
    string finalString = "factoryIndex=";
    finalString += fFactoryIndex;
    
    string IP = fFactory->getIP();
    string Port = fFactory->getPort();
    string Latency = fFactory->getLatency();
    string CV = fFactory->getCV();
    
    finalString += "&NJ_IP=";
    
    if(IP.compare("") == 0)
        IP = DEFAULT_MULTICAST_IP;
    
    finalString += IP;
    finalString += "&NJ_Port=";
    
    if(Port.compare("") == 0)
        Port = "19000";
    
    finalString += Port;
    finalString += "&NJ_Compression=";
    
    if(CV.compare("") == 0)
        CV = "-1";
    
    finalString += CV;
    finalString += "&NJ_Latency=";
    
    if(Latency.compare("") == 0)
        Latency = "2";
    
    finalString += Latency;
    
    printf("finalString = %s\n", finalString.c_str());
    
    
//  POST PARAMETERS
    CURL *curl;
    CURLcode res;
    
    curl = curl_easy_init();
    
    bool   isOpen = false;
    
    if (curl) {
        
        string ip = fFactory->getServerIP();
        ip += "/CreateInstance";
        
        std::ostringstream oss;
        
        curl_easy_setopt(curl, CURLOPT_URL, ip.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, finalString.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long) strlen(finalString.c_str()));
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &remote_dsp_aux::store_Response);
        curl_easy_setopt(curl, CURLOPT_FILE, &oss);
        
        res = curl_easy_perform(curl);
        
        if(res == CURLE_OK){

            long respcode; //response code of the http transaction
            
            curl_easy_getinfo(curl,CURLINFO_RESPONSE_CODE, &respcode);
            
            if(respcode == 200){
                
                //          OPEN NET JACK CONNECTION
                
                jack_master_t request = { -1, -1, -1, -1, fBufferSize, samplingFreq, "test_master", 3};
                
                jack_slave_t result;
                
                fNetJack = jack_net_master_open(DEFAULT_MULTICAST_IP, DEFAULT_PORT, "net_master", &request, &result); 
                
                if(fNetJack){
                    fInputs = new float*[getNumInputs() + 1];
                    fOutputs = new float*[getNumOutputs() + 1];
                    isOpen = true;
                }
            }
            else if(respcode == 400)
                error = oss.str();
        }
        else
            error = curl_easy_strerror(res);
        
        curl_easy_cleanup(curl);
    }
    
    return isOpen;
}

void remote_dsp_aux::decodeJson(const string& json){
    
    const char* p = json.c_str();
    parseJson(p, fMetadatas, fUiItems);
    
    fNumInputs = atoi(fMetadatas["inputs"].c_str());
    fMetadatas.erase("inputs");
    
    fNumOutputs = atoi(fMetadatas["outputs"].c_str());
    fMetadatas.erase("outputs");
    
    fFactoryIndex = fMetadatas["indexFactory"];
    fMetadatas.erase("indexFactory");
    
    fFactory->setIndex(fFactoryIndex);
    
    printf("NAME = %s || FACTORY Index = %s\n", fMetadatas["name"].c_str(), fFactoryIndex.c_str());
}

void remote_dsp_aux::metadata(Meta* m) { 
    
    map<string,string>::iterator it;
    
    for(it = fMetadatas.begin() ; it != fMetadatas.end(); it++)
        m->declare(it->first.c_str(), it->second.c_str());
}                           

//----------------------------------REMOTE DSP API-------------------------------------------

//---------FACTORY
EXPORT remote_dsp_factory* createRemoteDSPFactory(string ipServer, string dspContent, int argc, char** argv, int opt_level, string& error){
    
    printf("CREATE REMOTE FACTORY\n");
    
    remote_dsp_factory* factory = new remote_dsp_factory();
    
    if(factory->init(ipServer, dspContent, argc, argv, opt_level, error))
        return factory;
    else{
        delete factory;
        return NULL;
    }
    
}

EXPORT void deleteRemoteDSPFactory(remote_dsp_factory* factory){
    
    printf("DELETE REMOTE FACTORY\n");
    factory->stop();
    delete factory;
}

//---------INSTANCES

EXPORT remote_dsp* createRemoteDSPInstance(remote_dsp_factory* factory, int samplingRate,int bufferSize, string& error){
    
    return reinterpret_cast<remote_dsp*>(factory->createRemoteDSPInstance(samplingRate, bufferSize, error));
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







