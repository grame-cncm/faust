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

#ifndef remote_dsp_aux__h
#define remote_dsp_aux__h

#include <string>
#include <vector>
#include <map>
#include <list>
#include <assert.h>
#include <pthread.h>

#include <curl/curl.h>

#include "TMutex.h"

#include <sstream>
#include <iostream>
#include <fstream> 

#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "faust/audio/dsp.h"
#include "JsonParser.h"
#include "smartpointer.h"

#include "lo/lo.h"

#include <jack/net.h>

#define	EXPORT __attribute__ ((visibility("default")))

#ifdef __cplusplus
extern "C"
{
#endif
    
    using namespace std;
    
    enum{
        ERROR_FACTORY_NOTFOUND,
        ERROR_INSTANCE_NOTCREATED,
        ERROR_NETJACK_NOTSTARTED,
        ERROR_CURL_CONNECTION
    };
    
    struct member {
        int pid;
        string hostname;
        lo_timetag timetag;
        
        member(){
            pid = 0;
            hostname = "";
            timetag.sec = 0;
            timetag.frac = 0;
        }
    };
    
    struct remote_DNS {
        
        static void cleanupMachineList(std::map<string, member> clients_list);
        
        static void errorHandler(int num, const char *m, const char *path);
        
        static int pingHandler(const char *path, const char *types, lo_arg ** argv,
                               int argc, void *data, void *user_data);
        
        lo_server_thread fLoThread;
        
        std::map<string, member> fClients;
        
        TMutex fLocker;
        
        remote_DNS();
        virtual ~remote_DNS();
        
    };
    
#define NO_ERROR      0
#define READ_ERROR   -1
#define WRITE_ERROR  -2
    
    typedef int (*RemoteDSPErrorCallback) (int error_code, void* arg);
    
    class remote_dsp_aux;
    
    // Standard Callback to store a server response in strinstream
    static size_t store_Response(void *buf, size_t size, size_t nmemb, void* userp);
    
    static CURLcode send_request(CURL* curl, const string& ipadd, const string& request, string& response);
    
    class remote_dsp_factory;
    
    typedef class SMARTP<remote_dsp_factory> Sremote_dsp_factory;
    
#define FactoryTableItem   pair< string, list<remote_dsp_aux*> >
#define FactoryTableType   map< Sremote_dsp_factory, FactoryTableItem >
#define FactoryTableIt     FactoryTableType::iterator
    
    class remote_dsp_factory : public smartable {
        
    private:
        
        string      fSHAKey;            //Unique Index to bind a Remote_Factory to its llvm_Factory on the server side
        
        int         fNumInputs;
        int         fNumOutputs;        //Num of In/Output of compiled DSP factory
        
        string      fServerIP;          //IP of remote server 
        
        map<string,string>  fMetadatas; //Metadatas extracted from json
        vector<itemInfo*>   fUiItems;   //Items extracted from json
         
    public: 
        
        void        decodeJson(const string& json);
        
        remote_dsp_aux* createRemoteDSPInstance(int argc, const char *argv[], int sampling_rate, int buffer_size, RemoteDSPErrorCallback error_callback, void* error_callback_arg, int& error);
        
        bool        init(int argc, const char *argv[], 
                        const string& ip_server, 
                        int port_server, 
                        const string& name_app, 
                        const string& dsp_content, 
                        const string& sha_key, 
                        string& error_msg, 
                        int opt_level);
        void        stop();
        
        void        metadataRemoteDSPFactory(Meta* m);  
        
        //    ACCESSORS
        string              serverIP(){return fServerIP;}
        void                setIP(const string& ip){fServerIP = ip;}
        vector<itemInfo*>   itemList(){return fUiItems;}
        int                 numInputs();
        int                 numOutputs();
        
        string              key(){return fSHAKey;}
        void                setKey(const string& sha_key){fSHAKey = sha_key;}
        
        static FactoryTableType gFactoryTable;
    };
    
    //---------------------- Public C++ interface
    
    EXPORT remote_dsp_factory* getRemoteDSPFactoryFromSHAKey(const string& ip_server, int port_server, const std::string& sha_key);  
    
    EXPORT remote_dsp_factory* createRemoteDSPFactoryFromFile(const string& filename, int argc, const char *argv[], const string& ip_server, int port_server, string& error_msg, int opt_level);
    
    EXPORT remote_dsp_factory* createRemoteDSPFactoryFromString(const string& name_app, const string& dsp_content, int argc, const char *argv[], const string& ip_server, int port_server, string& error, int opt_level);
    
    EXPORT void deleteRemoteDSPFactory(remote_dsp_factory* factory);
    
    EXPORT void deleteAllRemoteDSPFactories();    
    
    EXPORT void metadataRemoteDSPFactory(remote_dsp_factory* factory, Meta* m);
    
    class remote_dsp_aux : public dsp {
        
    private:
        
        int                     fBufferSize;        //Buffer Size of NetJack connection   
        
        remote_dsp_factory*     fFactory;           //Factory is it created from
        
        jack_net_master_t*      fNetJack;           //Jack Connection
        
        float**                 fAudioInputs;       //Audio buffer
        float**                 fAudioOutputs;      //Audio buffer
        
        float**                 fControlInputs;     //control buffer
        float**                 fControlOutputs;    //control buffer
        
        FAUSTFLOAT*             fOutControl;        //Buffer containing the values of controls
        FAUSTFLOAT*             fInControl;         //Buffer containing the values of controls
        
        int                     fCounterIn;
        int                     fCounterOut;
        
        RemoteDSPErrorCallback  fErrorCallback;
        void*                   fErrorCallbackArg;
        
        bool                    fRunningFlag;
        
        void fillBufferWithZerosOffset(int channels, int offset, int size, FAUSTFLOAT** buffer);
        void setupBuffers(FAUSTFLOAT** input, FAUSTFLOAT** output, int offset);
        
        //    Command-line parsing fonction
        const char* getValueFromKey(int argc, const char *argv[], const char *key, const char* defaultValue);
        
        void sendSlice(int buffer_size);
        void recvSlice(int buffer_size);
        
    public:   
        
        remote_dsp_aux(remote_dsp_factory* factory);
        ~remote_dsp_aux();
        
        bool init(int argc, const char *argv[], int sampling_rate, int buffer_size, RemoteDSPErrorCallback errror_callback, void* errror_callback_arg, int& error);
        
        void metadata(Meta* m);
        
        virtual int getNumInputs();
        virtual int getNumOutputs();
        
        virtual void init(int samplingFreq);
        
        virtual void buildUserInterface(UI* ui);
        
        virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
        
        virtual void startAudio();
        virtual void stopAudio();
        
        remote_dsp_factory* getFactory() { return fFactory; }
    };
    
    class EXPORT remote_dsp : public dsp {
        
    public: 
        
        void metadata(Meta* m);
        
        virtual int getNumInputs();
        virtual int getNumOutputs();
        
        virtual void init(int samplingFreq);
        
        virtual void buildUserInterface(UI* ui);
        
        virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
        
        virtual void startAudio();
        virtual void stopAudio();
    };
    
    EXPORT remote_dsp* createRemoteDSPInstance(remote_dsp_factory* factory, 
                                               int argc, const char *argv[], 
                                               int sampling_rate, int buffer_size, 
                                               RemoteDSPErrorCallback error_callback,
                                               void* errror_callback_arg,
                                               int& error);
    
    EXPORT void deleteRemoteDSPInstance(remote_dsp* dsp);
    
    EXPORT bool getRemoteMachinesAvailable(map<string, pair<string, int> >* machineList);
    
    EXPORT bool getRemoteFactoriesAvailable(const string& ip_server, int port_server, vector<pair<string, string> >* factories_list);
    
#ifdef __cplusplus
}
#endif

#endif
