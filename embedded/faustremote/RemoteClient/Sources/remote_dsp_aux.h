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
#include <assert.h>

#include <sstream>
#include <iostream>
#include <fstream> 

#include "faust/gui/meta.h"
#include "faust/gui/ControlUI.h"
#include "faust/audio/dsp.h"

#include "jack/net.h"
#include <curl/curl.h>

#include "JsonParser.h"

#define	EXPORT __attribute__ ((visibility("default")))

#include <vector>

#ifdef __cplusplus
extern "C"
{
#endif

using namespace std;

class remote_dsp_aux;

class remote_dsp_factory{
    
private:
    
    string      fJsonResponse;  //Response of Server containing the interface as json application
    
    string      fIP, fPort, fCV, fLatency, fServerIP;
    
    string      fIndex;
    
    static size_t      store_Response(void *buf, size_t size, size_t nmemb, void* userp);
    
public: 
    
    remote_dsp_factory();
    virtual ~remote_dsp_factory();
    
    string json();
    
    string  getServerIP(){return fServerIP;}
    string  getIP(){return fIP;}
    
    string  getPort(){return fPort;}
    string  getCV(){return fCV;}
    string  getLatency(){return fLatency;}
    
    void    setIndex(string index){fIndex = index;}

    remote_dsp_aux* createRemoteDSPInstance(int samplingRate, int bufferSize, string& error);

    bool    init(string ipServer, string dspContent, int argc, char** argv, int opt_level, string& error);
    void    stop();
    
};

// Public C++ interface

EXPORT remote_dsp_factory* createRemoteDSPFactory(string ipServer, string dspContent, int argc, char** argv, int opt_level,string& error);

EXPORT void deleteRemoteDSPFactory(remote_dsp_factory* factory);

const char* lopts(char *argv[], const char *name, const char* def);

class remote_dsp_aux : public dsp{

    private:
    
        remote_dsp_factory*      fFactory;
        
        jack_net_master_t* fNetJack;
        float**     fInputs;
        float**     fOutputs;
    
        int         fBufferSize;
    
        int         fNumInputs;
        int         fNumOutputs;
    
        string      fFactoryIndex;
    
        map<string,string>  fMetadatas; //Metadatas extracted from json
        vector<itemInfo*>   fUiItems;   //Items extracted from json
        int         fNumItem;           //Number of real items (!= group or close group)

    
        FAUSTFLOAT*  fOutControl;        //Buffer containing the values of controls
        FAUSTFLOAT*  fInControl;        //Buffer containing the values of controls

        int          countItem();    
    
        static size_t      store_Response(void *buf, size_t size, size_t nmemb, void* userp);
    
        void         metadata(Meta* m);

    
        void         fillBufferWithZeros(int size1, int size2, FAUSTFLOAT** buffer);
    
    public: 
    
        remote_dsp_aux();
        virtual ~remote_dsp_aux();
    
        virtual int     getNumInputs();
        virtual int     getNumOutputs();

        virtual void    init(int samplingFreq);
    
        virtual void    buildUserInterface(UI* ui);
    
        virtual void    compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
    
        bool            init(int samplingFreq, int buffer_size, string& error);
        void            decodeJson(const string& json);
        void            setFactory(remote_dsp_factory* factory){fFactory = factory;}
    
};

class EXPORT remote_dsp : public dsp{
    
public: 
    
    remote_dsp();
    virtual ~remote_dsp();
    
    virtual int     getNumInputs();
    virtual int     getNumOutputs();
    
    virtual void    init(int samplingFreq);
    
    virtual void    buildUserInterface(UI* ui);
    
    virtual void    compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
};

EXPORT remote_dsp*  createRemoteDSPInstance(remote_dsp_factory* factory, int samplingRate, int bufferSize, string& error);

EXPORT void        deleteRemoteDSPInstance(remote_dsp* dsp);

#ifdef __cplusplus
}
#endif
    
#endif



