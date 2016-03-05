/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
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


 ************************************************************************
 ************************************************************************/

#ifndef __httpdUI__
#define __httpdUI__

#include <unistd.h>

#include "faust/gui/HTTPDControler.h"
#include "faust/gui/UI.h"
#include "faust/gui/PathBuilder.h"
#include "faust/misc.h"

#include <iostream>
#include <sstream>

#ifndef _WIN32
#include <pthread.h>
#endif

/******************************************************************************
*******************************************************************************

					HTTPD USER INTERFACE

*******************************************************************************
*******************************************************************************/

class httpdUIAux
{
    public: 
    
        virtual void run()              = 0;
        virtual void stop()             = 0;
        virtual int getTCPPort()        = 0;
        virtual std::string getJSON()   = 0;
};

/*

Note about URLs and the Faust UI names:
----------------------------------------------------
Characters in a url could be:
1. Reserved: ; / ? : @ & = + $ ,
   These characters delimit URL parts.
2. Unreserved: alphanum - _ . ! ~ * ' ( )
   These characters have no special meaning and can be used as is.
3. Excluded: control characters, space, < > # % ", { } | \ ^ [ ] `

To solve potential conflicts between the Faust UI objects naming scheme and
the URL allowed characters, the reserved and excluded characters are replaced
with '-' (hyphen).
Space or tabulation are replaced with '_' (underscore)
*/

class httpdServerUI : public UI, public httpdUIAux
{
    private:

        httpdfaust::HTTPDControler*	fCtrl;	
          
        const char* tr(const char* label) const
        {
            static char buffer[1024];
            char * ptr = buffer; int n = 1;
            while (*label && (n++ < 1024)) {
                switch (*label) {
                    case ' ': case '	':
                        *ptr++ = '_';
                        break;
                    case ';': case '/': case '?': case ':': case '@': 
                    case '&': case '=': case '+': case '$': case ',':
                    case '<': case '>': case '#': case '%': case '"': 
                    case '{': case '}': case '|': case '\\': case '^': 
                    case '[': case ']': case '`':
                        *ptr++ = '_';
                        break;
                    default: 
                        *ptr++ = *label;
                }
                label++;
            }
            *ptr = 0;
            return buffer;
        }

    public:
        
        httpdServerUI(const char* applicationname, int inputs, int outputs, int argc, char* argv[], bool init = true) 
        { 
            fCtrl = new httpdfaust::HTTPDControler(argc, argv, applicationname, init); 
            fCtrl->setInputs(inputs);
            fCtrl->setOutputs(outputs);
        }

        virtual ~httpdServerUI() { delete fCtrl; }
            
        // -- widget's layouts
        virtual void openTabBox(const char* label) 			{ fCtrl->opengroup("tgroup", tr(label)); }
        virtual void openHorizontalBox(const char* label) 	{ fCtrl->opengroup("hgroup", tr(label)); }
        virtual void openVerticalBox(const char* label) 	{ fCtrl->opengroup("vgroup", tr(label)); }
        virtual void closeBox() 							{ fCtrl->closegroup(); }

        // -- active widgets
        virtual void addButton(const char* label, FAUSTFLOAT* zone)			{ fCtrl->addnode("button", tr(label), zone); }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)	{ fCtrl->addnode("checkbox", tr(label), zone); }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
                                        { fCtrl->addnode("vslider", tr(label), zone, init, min, max, step); }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 	
                                        { fCtrl->addnode("hslider", tr(label), zone, init, min, max, step); }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 			
                                        { fCtrl->addnode("nentry", tr(label), zone, init, min, max, step); }

        // -- passive widgets	
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
                                        { fCtrl->addnode("hbargraph", tr(label), zone, min, max); }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
                                        { fCtrl->addnode("vbargraph", tr(label), zone, min, max); }

        virtual void declare(FAUSTFLOAT*, const char* key, const char* val) { fCtrl->declare(key, val); }

        void run()						{ fCtrl->run(); }
        void stop()						{ fCtrl->stop(); }
        int getTCPPort()                { return fCtrl->getTCPPort(); }

        std::string getJSON() { return fCtrl->getJSON(); }

};

// API from sourcefetcher.hh and compiled in libHTTPDFaust library.
int http_fetch(const char *url, char **fileBuf);


/*
Use to control a running Faust DSP wrapped with "httpdServerUI".
*/

#ifndef _WIN32
class httpdClientUI : public GUI, public PathBuilder, public httpdUIAux
{

    private:
    
        class uiUrlValue : public uiItem
        {

            private:
            
                std::string fPathURL;
                 
            public:
            
                uiUrlValue(const std::string& path_url, GUI* ui, FAUSTFLOAT* zone)
                    :uiItem(ui, zone),fPathURL(path_url)
                {}
                virtual ~uiUrlValue()
                {}
                
                virtual void reflectZone()
                {
                    FAUSTFLOAT v = *fZone;
                    fCache = v;
                    std::stringstream str;
                    str << fPathURL << "?value=" << v;
                    std::string path = str.str();
                    http_fetch(path.c_str(), NULL);
                }
            
        };
        
        std::string fServerURL;
        std::string fJSON;
        std::map<std::string, FAUSTFLOAT*> fZoneMap;
        pthread_t fThread;
        int fTCPPort;
        bool fRunning;
        
        void insertMap(std::string label, FAUSTFLOAT* zone)
        {
            fZoneMap[label] = zone;
        }
      
        static void* UpdateUI(void* arg)
        {
            httpdClientUI* ui = static_cast<httpdClientUI*>(arg);
            std::map<std::string, FAUSTFLOAT*>::iterator it;
            while (ui->fRunning) {
                for (it = ui->fZoneMap.begin(); it != ui->fZoneMap.end(); it++) {
                    char* answer;
                    std::string path = (*it).first;
                    http_fetch(path.c_str(), &answer);
                    std::string answer_str = answer;
                    (*(*it).second) = (FAUSTFLOAT)strtod(answer_str.substr(answer_str.find(' ')).c_str(), NULL);
                    // 'http_fetch' result must be deallocated
                    free(answer);
                }
                usleep(100000);
            }
			return 0;
        }
     
        virtual void addGeneric(const char* label, FAUSTFLOAT* zone)			
        { 
            std::string url = fServerURL + buildPath(label); 
            insertMap(url, zone); 
            new uiUrlValue(url, this, zone); 
        }
            
    public:
            
        httpdClientUI(const std::string& server_url):fServerURL(server_url), fRunning(false)
        {
            char* json_buffer = 0;
            std::string json_url = std::string(server_url) + "/JSON";
            http_fetch(json_url.c_str(), &json_buffer);
            if (json_buffer) {
                fJSON = json_buffer;
                fTCPPort = atoi(server_url.substr(server_url.find_last_of(':') + 1).c_str());
                // 'http_fetch' result must be deallocated
                free(json_buffer);
                std::cout << "Faust httpd client controling server '" << server_url << "'" << std::endl;
            } else {
                fJSON = "";
                fTCPPort = -1;
            }
        }
        
        virtual ~httpdClientUI() 
        {
            stop();
        }
            
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void openHorizontalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void openVerticalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void closeBox()
        {
            fControlsLevel.pop_back();
        }
        
        // -- active widgets
        virtual void addButton(const char* label, FAUSTFLOAT* zone)			
        { 
            // addGeneric(label, zone);
            // Do not update button state with received messages (otherwise on/off messages may be lost...)
            std::string url = fServerURL + buildPath(label); 
            new uiUrlValue(url, this, zone); 
        }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) 
        { 
            addGeneric(label, zone); 
        }        
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        { 
            addGeneric(label, zone);
        }  
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 	
        { 
            addGeneric(label, zone);
        } 
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 			
        { 
            addGeneric(label, zone); 
        } 
        
        // -- passive widgets	
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
        { 
            addGeneric(label, zone); 
        } 
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        { 
            addGeneric(label, zone);
        } 
        
        virtual void declare(FAUSTFLOAT*, const char* key, const char* val) {}
        
        void run()
        { 
            if (fTCPPort > 0) {
                fRunning = true;
                pthread_create(&fThread, NULL, UpdateUI, this);
            }
        }
        
        void stop()
        { 
            if (fRunning) {
                fRunning = false;
                pthread_join(fThread, NULL);
            }
        }
        
        int getTCPPort() 
        { 
            return fTCPPort; 
        }

        std::string getJSON() { return fJSON; }

};
#endif

/*
Creates a httpdServerUI or httpdClientUI depending of the presence of '-server URL' parameter.
*/

class httpdUI : public DecoratorUI
{
   
    public:
    
        httpdUI(const char* applicationname, int inputs, int outputs, int argc, char* argv[], bool init = true)
        { 
            if (argv && isopt(argv, "-server")) {
            #ifndef _WIN32
                fUI = new httpdClientUI(lopts(argv, "-server", "http://localhost:5510"));
            #endif
            } else {
                fUI = new httpdServerUI(applicationname, inputs, outputs, argc, argv, init);
            }
        }

        void run() { dynamic_cast<httpdUIAux*>(fUI)->run(); }
        void stop() { dynamic_cast<httpdUIAux*>(fUI)->stop(); }
        int getTCPPort() { return dynamic_cast<httpdUIAux*>(fUI)->getTCPPort(); }

        std::string getJSON() { return dynamic_cast<httpdUIAux*>(fUI)->getJSON(); }

};

#endif
