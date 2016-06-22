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
//  Copyright (c) 2013 GRAME All rights reserved.
//
//
// MAIN OF SERVER FOR REMOTE COMPILATION AND PROCESSING
//
//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------

#include "remote-dsp.h"
#include "faust/gui/GUI.h"
#include "utilities.h"
#include <stdio.h>
#include <iostream>

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

int main(int argc, const char* argv[])
{
    int	port = lopt(argv, "--port", 7777);
    
    if (isopt((const char**)argv, "--help")) {
        std::cout << "RemoteServer --port XXX (default port is 7777)" << std::endl;
        return -1;
    }
    
    remote_dsp_server* server = createRemoteDSPServer(0, NULL);
    
    if (!server->start(port)) {
        std::cerr << "Unable to start Faust Remote Processing Server" << std::endl;
        return -1;
    } else {
        std::cerr << "Faust Remote Processing Server is running on port : "<< port << std::endl;
    }
   
    printf("Type 'q' to quit server...\n");
    while (getchar() != 'q') {}
    server->stop();
    deleteRemoteDSPServer(server);
    return 0;
}


