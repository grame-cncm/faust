//
//  main.cpp
//  
//
//  Created by Sarah Denoux on 30/05/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//
//
// MAIN OF DYNAMIC COMPILER
//
//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------
#include <sys/stat.h>
#include <iostream>

#include "../utilities.h"
#include "faust/remote-dsp.h"
#include "faust/gui/faustqt.h"
#include "faust/audio/coreaudio-dsp.h"
#include "faust/audio/jack-dsp.h"

std::list<GUI*> GUI::fGuiList;

int main(int argc, char* argv[])
{    
    if(argv[1] && !strcmp(argv[1], "--help")){
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

    QApplication myApp(argc, argv);
    
    string filePath = loptions(argv, "--file", "");
            
    string errorFactory("");
            
    const char* arguments[argc];
    int nbArgument = 0;
         
//--- Separate compilation options
    for(int i=1; i<argc; i++){
            
        if(string(argv[i]).find("--")!=string::npos){
            i ++;
        }
        else{
            arguments[nbArgument] = argv[i];
            nbArgument++;
        }
    }
              
    string content = pathToContent(filePath);
    
    remote_dsp_factory* factory = createRemoteDSPFactoryFromString("FaustRemote", content, nbArgument, arguments, "", ipServer, portServer, errorFactory, 3);
            
    if(factory != NULL){
                
        remote_dsp* DSP;
        
        string errorInstance("");
                
        DSP = createRemoteDSPInstance(factory, argc, (const char**)(argv), srate, fpb, errorInstance);
                    
        if(DSP != NULL){
                        
            QTGUI* interface = new QTGUI();
                    
          jackaudio* audio = new jackaudio;
            
//        coreaudio* audio = new coreaudio(srate, fpb);
                    
            DSP->buildUserInterface(interface);   
                    
            if(!audio->init("RemoteExample", DSP))
                printf("Audio could not be initialized\n");
            else if(!audio->start())
                printf("Audio could not be started\n");
            else
                interface->run();
            
            myApp.setStyleSheet(STYLESHEET);
            myApp.exec();
            
            
            //  STOP && DESALLOCATION OF ALL RESOURCES
            
            interface->stop();
            delete interface;
            
            audio->stop();
            delete audio;
            
            deleteRemoteDSPInstance(DSP);
            deleteRemoteDSPFactory(factory);
                
        }
        else
            printf("CREATE INSTANCE FAILED = %s\n", errorInstance.c_str());
    }
    else
        printf("CREATE FACTORY FAILED = %s\n", errorFactory.c_str());
    
  	return 0;
}


