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
//
//  main.cpp
//
//  Created by Sarah Denoux on 30/05/13.
//  Copyright (c) 2013 GRAME. All rights reserved.
//
//
// MAIN OF DYNAMIC COMPILER
//
//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------
#include <sys/stat.h>
#include <iostream>
#include <pthread.h>
#include <stdio.h>

#include "../../utilities.h"
#include "faust/dsp/remote-dsp.h"
#include "faust/gui/faustqt.h"
#include "faust/gui/httpdUI.h"
//#include "faust/audio/coreaudio-dsp.h"
#include "faust/audio/jack-dsp.h"

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

int testClient(int argc, const char* argv[])
{
    if (argv[1] && !strcmp(argv[1], "--help")){
        printf("\nOPTIONS OF FAUST DISTRIBUTED : \n\n\
               ########### REMOTE CALCULATION PARAMETERS ############\n\
               --ipserver ==> default is localhost\n\
               --portserver ==> default is 7777 \n\
               --frequency ==> default is 44100 \n\
               --buffer ==> default is 512 \n\n\
               ########### NET JACK PARAMETER #######################\n\
               --NJ_ip ==> MULTICAST_DEFAULT_IP \n\
               --NJ_port ==> MULTICAST_DEFAULT_PORT\n\
               --NJ_compression ==> default is -1\n\
               --NJ_mtu ==> default is 1500\n\
               --NJ_latency ==>default is 2 \n\
               ########### DSP TO BE REMOTLY COMPILED ###############\n\
               --file ==> no DSP = no application\n\
               -vec/-sch : faust compilation options\n\
               \n");
        return 0;
    }
    
    string ipServer = loptions(argv, "--ipserver", "localhost");
    int portServer = lopt(argv, "--portserver", 7777);
    int srate = lopt(argv, "--frequency", 44100);
    int	fpb = lopt(argv, "--buffer", 512);

    QApplication myApp(argc, (char**)argv);
    
    string filePath = loptions(argv, "--file", "");
            
    string errorFactory("");
    
 /* vector<pair<string, string> > factories_list;
    getRemoteFactoriesAvailable(ipServer, portServer, &factories_list);
    
    printf("Factories List : \n");
    for(int i=0; i<factories_list.size(); i++)
        printf("%s : %s\n", factories_list[i].first.c_str(), factories_list[i].second.c_str());
   */ 
    const char* arguments[32];
    int nbArgument = 0;
          
//--- Separate compilation options
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]).find("--") != string::npos) {
            i++;
        } else {
            arguments[nbArgument++] = argv[i];
        }
    }
    
    string folder = filePath.substr(0, filePath.find_last_of('/'));
    
    arguments[nbArgument++] = "-I";
    arguments[nbArgument++] = folder.c_str();
    // arguments[nbArgument++] = "-O";
    //arguments[nbArgument++] = folder.c_str();
    
    arguments[nbArgument++] = "-ps";
    arguments[nbArgument++] = "-tg";
    arguments[nbArgument++] = "-sg";
    arguments[nbArgument++] = "-svg";
    arguments[nbArgument++] = "-xml";
    //arguments[nbArgument++] = "-mdoc";
    //arguments[nbArgument++] = "-vec";
              
    string content = pathToContent(filePath);
    remote_dsp_factory* factory = createRemoteDSPFactoryFromString("FaustRemote", content, nbArgument, arguments, ipServer, portServer, errorFactory, 3);
    
    /*remote_dsp_factory* factory = 0;
    
    if (factories_list.size() > 0)
        factory = getRemoteDSPFactoryFromSHAKey(ipServer, portServer, factories_list[0].second.c_str());
    */
    if (factory != NULL) {
                
        remote_dsp* DSP;
        int errorInstance;
        DSP = createRemoteDSPInstance(factory, argc, (const char**)(argv), NULL, NULL, errorInstance);
                    
        if (DSP != NULL) { 
                        
            QTGUI* interface = new QTGUI();
            jackaudio* audio = new jackaudio;
            //coreaudio* audio = new coreaudio(srate, fpb);
                    
            DSP->buildUserInterface(interface);   
                    
            if (!audio->init("RemoteExample", DSP)) {
                printf("Audio could not be initialized\n");
            } else if (!audio->start()) {
                printf("Audio could not be started\n");
            } else {
                interface->run();
            }
            
            //myApp.setStyleSheet(STYLESHEET);
            myApp.exec();
             
            // STOP && DESALLOCATION OF ALL RESOURCES
            
            interface->stop();
            delete interface;
            
            audio->stop();
            delete audio;
            
            deleteRemoteDSPInstance(DSP);
            deleteRemoteDSPFactory(factory);
        } else {
            printf("CREATE INSTANCE FAILED = %d\n", errorInstance);
        }
    } else {
        printf("CREATE FACTORY FAILED = %s\n", errorFactory.c_str());
    }

    return 0;
}

pthread_t gThread;
QTGUI* interface = NULL;
httpdUI* httpdinterface = NULL;
 
static void* RunDSP(void* arg)
{
    llvm_dsp* dsp = (llvm_dsp*)arg;
    
    //QTGUI* interface = new QTGUI();
    //dsp->buildUserInterface(interface);  
    
    httpdinterface = new httpdUI("toto", dsp->getNumInputs(), dsp->getNumOutputs(), 0, NULL);
    dsp->buildUserInterface(httpdinterface);
    httpdinterface->run();
    return 0;
}

static bool DSPCallback(dsp* dsp, void* arg)
{
    printf("DSPCallback\n");
    
    if (interface) {
        interface->stop();
    }
     
    if (pthread_create(&gThread, NULL, RunDSP, dsp) != 0) {
        printf("RemoteDSPServer : pthread_create failed\n");
        return false;
    }
  
    return true;
}

int testServer(int argc, const char* argv[])
{
    int	port = lopt(argv, "--port", 7777);
    QApplication myApp(argc, (char**)argv);
    remote_dsp_server* server = createRemoteDSPServer(0, NULL);
    
    //interface = new QTGUI();
    
    server->setCreateDSPInstanceCallback(DSPCallback, server);
     
    if (!server->start(port)) {
        std::cerr << "Unable to start Faust Remote Processing Server" << std::endl;
        return -1;
    } else {
        std::cerr << "Faust Remote Processing Server is running on port : "<< port<<std::endl;
    }
    
    getchar();
    printf("Quit server...\n");
    server->stop();
    deleteRemoteDSPServer(server);
    return 0;
}

int main(int argc, const char* argv[])
{    
    return testClient(argc, argv);
    //return testServer(argc, argv);
}


