//
//  main.cpp
//  
//
//  Created by Sarah Denoux on 30/05/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//
//
// MAIN OF SERVER FOR REMOTE COMPILATION AND PROCESSING
//
//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------

#include "Server.h"

int main(int argc, char* argv[])
{
    int port = 7777;
    
    if(argv[1] && !strcmp(argv[1],"--port"))
        port = atoi(argv[2]);
    
    Server server;
    
    if (!server.start(port)) {
        std::cerr << "Unable to start Faust Remote Processing Server" << std::endl;
        return 1;
    }
    else
        std::cerr << "Faust Remote Processing Server is running on port : "<< port<<std::endl;
    
    getchar();
    
  	return 0;
}


