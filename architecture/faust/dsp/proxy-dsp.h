/************************************************************************
	IMPORTANT NOTE : this file contains two clearly delimited sections :
	the ARCHITECTURE section (in two parts) and the USER section. Each section
	is governed by its own copyright and license. Please check individually
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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

#ifndef __proxy_dsp__
#define __proxy_dsp__

#include <vector>
#include <map>

#include "faust/audio/dsp.h"
#include "faust/gui/SimpleParser.h"

//----------------------------------------------------------------
//  Proxy processor definition created from the DSP JSON description
//  This class allows a 'proxy' DSP to control a real DSP 
//  running somewhere else
//----------------------------------------------------------------

class proxy_dsp : public dsp {

    private:

        std::string fName;
        
        std::map<std::string, std::string> fMetadatas; 
        std::vector<itemInfo*> fUiItems;     
        
        FAUSTFLOAT* fInControl;
        FAUSTFLOAT* fOutControl;
        
        std::string fJSON;
        
        int fNumInputs, fNumOutputs; 
        int fInputItems, fOutputItems; 
            
    public:

        proxy_dsp(const string& json) 
        {
            fJSON = json;
            const char* p = fJSON.c_str();
            parseJson(p, fMetadatas, fUiItems);
            
            if (fMetadatas.find("name") != fMetadatas.end()) {
                fName = fMetadatas["name"];
                fMetadatas.erase("name");
            }
             
            if (fMetadatas.find("inputs") != fMetadatas.end()) {
                fNumInputs = atoi(fMetadatas["inputs"].c_str());
                fMetadatas.erase("inputs");
            }
            
            if (fMetadatas.find("outputs") != fMetadatas.end()) {
                fNumOutputs = atoi(fMetadatas["outputs"].c_str());
                fMetadatas.erase("outputs");
            }
            
            vector<itemInfo*>::iterator it;
            fInputItems = 0;
            fOutputItems = 0;
            
            for (it = fUiItems.begin(); it != fUiItems.end(); it++) {
                string type = (*it)->type;
                if (type == "vslider" || type == "hslider" || type == "nentry" || type == "button") {
                    fInputItems++;
                } else if (type == "hbargraph" || type == "vbargraph") {
                    fOutputItems++;          
                }
            }
            
            fInControl = new FAUSTFLOAT[fInputItems];
            fOutControl = new FAUSTFLOAT[fOutputItems];
        }
        
        virtual ~proxy_dsp() 
        {
            vector<itemInfo*>::iterator it;
            for (it = fUiItems.begin(); it != fUiItems.end(); it++) {
                delete(*it);
            }
            
            delete [] fInControl;
            delete [] fOutControl;
        }

        virtual int getNumInputs() 	{ return fNumInputs; }
        virtual int getNumOutputs() { return fNumOutputs; }
        
        virtual void buildUserInterface(UI* ui)
        {
            int counterIn = 0;
            int counterOut = 0;
            vector<itemInfo*>::iterator it;
            
            for (it = fUiItems.begin(); it != fUiItems.end(); it++) {
                
                map<string,string>::iterator it2;
                bool isInItem = false;
                bool isOutItem = false;
                string type = (*it)->type;
                
                float init = strtod((*it)->init.c_str(), NULL);
                float min = strtod((*it)->min.c_str(), NULL);
                float max = strtod((*it)->max.c_str(), NULL);
                float step = strtod((*it)->step.c_str(), NULL);
                
                if (type == "vslider" || type == "hslider" || type == "nentry" || type == "button") {
                    isInItem = true;
                } else if (type == "hbargraph" || type == "vbargraph") {
                    isOutItem = true;        
                }
                
                // Meta Data declaration for entry items
                if ((*it)->type.find("group") == string::npos && (*it)->type.find("bargraph") == string::npos && (*it)->type != "close") {
                    fInControl[counterIn] = init;
                    for (it2 = (*it)->meta.begin(); it2 != (*it)->meta.end(); it2++) {
                        ui->declare(&fInControl[counterIn], it2->first.c_str(), it2->second.c_str());
                    }
                }
                // Meta Data declaration for exit items
                else if ((*it)->type.find("bargraph") != string::npos) {
                    fOutControl[counterOut] = init;
                    for (it2 = (*it)->meta.begin(); it2 != (*it)->meta.end(); it2++) {
                        ui->declare(&fOutControl[counterOut], it2->first.c_str(), it2->second.c_str());
                    }
                }
                // Meta Data declaration for group opening or closing
                else {
                    for (it2 = (*it)->meta.begin(); it2 != (*it)->meta.end(); it2++) {
                        ui->declare(0, it2->first.c_str(), it2->second.c_str());
                    }
                }
                
                if (type == "hgroup") {
                    ui->openHorizontalBox((*it)->label.c_str());
                } else if (type == "vgroup") { 
                    ui->openVerticalBox((*it)->label.c_str());
                } else if (type == "tgroup") {
                    ui->openTabBox((*it)->label.c_str());
                } else if (type == "vslider") {
                    ui->addVerticalSlider((*it)->label.c_str(), &fInControl[counterIn], init, min, max, step);
                } else if (type == "hslider") {
                    ui->addHorizontalSlider((*it)->label.c_str(), &fInControl[counterIn], init, min, max, step);            
                } else if (type == "checkbox") {
                    ui->addCheckButton((*it)->label.c_str(), &fInControl[counterIn]);
                } else if (type == "hbargraph") {
                    ui->addHorizontalBargraph((*it)->label.c_str(), &fOutControl[counterOut], min, max);
                } else if (type == "vbargraph") {
                    ui->addVerticalBargraph((*it)->label.c_str(), &fOutControl[counterOut], min, max);
                } else if (type == "nentry") {
                    ui->addNumEntry((*it)->label.c_str(), &fInControl[counterIn], init, min, max, step);
                } else if (type == "button") {
                    ui->addButton((*it)->label.c_str(), &fInControl[counterIn]);
                } else if (type == "close") {
                    ui->closeBox();
                }
                    
                if (isInItem) {
                    counterIn++;
                }
                    
                if (isOutItem) {
                    counterOut++;
                }
            }
        }
        
        virtual void init(int samplingRate) {}  
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {}  
    
};

#endif
