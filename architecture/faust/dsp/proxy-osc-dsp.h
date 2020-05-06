/************************** BEGIN proxy-osc-dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __proxy_osc_dsp__
#define __proxy_osc_dsp__

#include <lo/lo.h>

#include "faust/dsp/proxy-dsp.h"

//----------------------------------------------------------------
// Proxy OSC dsp tries to connect to an OSC aware application and
// creates a proxy to control it.
//----------------------------------------------------------------

class proxy_osc_dsp : public proxy_dsp {
    
    private:
        
        std::string fJSON;
        
        static void errorHandler(int num, const char* msg, const char* where)
        {
            std::cerr << "Server error " << num << " in path" << ((where) ? where : "") << " : " << ((msg) ? msg : "") << std::endl;
        }
        
        static int messageHandler(const char* path, const char* types, lo_arg** argv, int argc, lo_message msg, void* user_data)
        {
            return static_cast<proxy_osc_dsp*>(user_data)->messageHandler(argv, argc);
        }
        
        int messageHandler(lo_arg** argv, int argc)
        {
            if (argc == 2 && strcmp(&argv[0]->s, "json") == 0) {
                fJSON = &argv[1]->s;
            }
            return 0;
        }
        
    public:
        
        proxy_osc_dsp(const std::string& ip, const std::string& root, int int_port, int out_port, int time_out = 5)
        {
            lo_message message = nullptr;
            lo_address target = nullptr;
            
            // Create server
            lo_server server = lo_server_new(std::to_string(int_port).c_str(), errorHandler);
            if (!server) {
                std::cerr << "Could not start a server with port: " << int_port << std::endl;
                goto fail;
            }
            lo_server_add_method(server, NULL, NULL, messageHandler, this);
            
            // Send 'json' message
            target = lo_address_new(ip.c_str(), std::to_string(out_port).c_str());
            message = lo_message_new();
            lo_message_add_string(message, "json");
            if (lo_send_message(target, root.c_str(), message) == -1) {
                std::cerr << "An error occured in lo_send_message: " << lo_address_errstr(target) << std::endl;
                goto fail;
            }
            
            // Wait for 'json' reply from the OSC application
            if (lo_server_recv_noblock(server, time_out * 1000) == 0) {
                std::cerr << "No '" << root << "' OSC application on input " << int_port << " and output " << out_port << std::endl;
                goto fail;
            }
            
            lo_address_free(target);
            lo_message_free(message);
            lo_server_free(server);
            
            // Creates the proxy from the retrieved JSON
            init(fJSON);
            return;
            
        fail:
            if (target) lo_address_free(target);
            if (message) lo_message_free(message);
            if (server) lo_server_free(server);
            throw std::bad_alloc();
        }
    
};

#endif
/**************************  END  proxy-osc-dsp.h **************************/
