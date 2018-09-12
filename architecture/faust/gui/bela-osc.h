/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
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
 
#ifndef __bela_osc__
#define __bela_osc__

#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "faust/gui/APIUI.h"

/**************************BEGIN OSC SECTION **************************/

class oscItem : public uiItem {
    
protected:
    
    OSCClient* fSender;
    string fPath;
    
public:
    
    oscItem(OSCClient* sender, GUI* ui, const string& path, FAUSTFLOAT* zone)
    :uiItem(ui, zone), fSender(sender), fPath(path) {}
    virtual ~oscItem()
    {}
    
    virtual void reflectZone()
    {}
    
};

class BelaOSCUI : public GUI {
    
private:
    string fIP;
    int fInputPort;
    int fOutputPort;
    
    APIUI fAPIUI;
    vector<oscItem*> fOSCItems;
    
    AuxiliaryTask fOscTask;
    
    OSCServer oscServer;
    OSCClient oscClient;
    
    static void OSCTask(void* arg)
    {
        static_cast<BelaOSCUI*>(arg)->oscMessageReceived();
    }
    
public:

    BelaOSCUI(const string& ip, int in_port, int out_port):fIP(ip), fInputPort(in_port), fOutputPort(out_port){}
    
    virtual ~BelaOSCUI()
    {}
    
    // for auxiliaryTask:
    void oscMessageReceived()
    {
        while (oscServer.messageWaiting()){
            float floatArg;
            oscpkt::Message msg;
            msg = oscServer.popMessage();
            string msgAdress = msg.addressPattern();
            int paramIndex = fAPIUI.getParamIndex(msg.addressPattern().c_str());
            if (msg.match(msgAdress).popFloat(floatArg).isOkNoMoreArgs() && paramIndex !=-1){
                fAPIUI.setParamValue(paramIndex, floatArg);
            // "get" message with correct address
            } else if (msg.match("/get").isOkNoMoreArgs()){
                for (int p = 0; p < fAPIUI.getParamsCount(); ++p) {
                    // show datat to console.
                    rt_printf("%s %f to %f\n", fAPIUI.getParamAddress(p), fAPIUI.getParamMin(p), fAPIUI.getParamMax(p));
                    // set data by OSC.
                    oscClient.queueMessage(oscClient.newMessage.to(std::string(fAPIUI.getParamAddress(p))).add(fAPIUI.getParamMin(p)).add(fAPIUI.getParamMax(p)).end());
                }
            // "hello" message
            } else if (msg.match("/hello").isOkNoMoreArgs()){
                // show datat to console.
                rt_printf("adresses:%s, in:%i, out:%i\n", fIP, fInputPort, fOutputPort );
                // set data by OSC.
                std::string s = fAPIUI.getParamAddress(0);
                s.erase(0, 1);
                s = s.substr(0, s.find("/"));
                s.insert (0, 1, '/');
                oscClient.queueMessage(oscClient.newMessage.to(s).add(std::string(fIP)).add(fInputPort).add(fOutputPort).end());//("/adress IP")
            }
        }
    }
    
    bool run() override {
        oscServer.setup(fOutputPort);
        oscClient.setup(fInputPort, fIP);
        rt_printf("initconnect\n");
        if (fOSCItems.size() == 0) {
            rt_printf("%i widgets, OSC Adresses:\n", fAPIUI.getParamsCount());
            
            for (int p = 0; p < fAPIUI.getParamsCount(); ++p) {
                rt_printf("%s %f to %f\n", fAPIUI.getParamAddress(p), fAPIUI.getParamMin(p), fAPIUI.getParamMax(p));
                fOSCItems.push_back(new oscItem(&oscClient, this, fAPIUI.getParamAddress(p), fAPIUI.getParamZone(p)));
            }
        }
        
        rt_printf("connected\n");
        
        fOscTask = Bela_createAuxiliaryTask(OSCTask, 50, "bela-osc", this);
        
        return true;
    }
    
    void scheduleOSC()
    {
        Bela_scheduleAuxiliaryTask(fOscTask);
    }
    
    // -- widget's layouts
    void openTabBox(const char* label) override { fAPIUI.openTabBox(label); }
    void openHorizontalBox(const char* label) override { fAPIUI.openHorizontalBox(label); }
    void openVerticalBox(const char* label) override { fAPIUI.openVerticalBox(label); }
    void closeBox() override  { fAPIUI.closeBox(); }
    
    // -- active widgets
    
    void addButton(const char* label, FAUSTFLOAT* zone) override { fAPIUI.addButton(label, zone); }
    void addCheckButton(const char* label, FAUSTFLOAT* zone) override { fAPIUI.addCheckButton(label, zone); }
    
    void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override
    { fAPIUI.addVerticalSlider(label, zone, init, min, max, step); }
    
    void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override
    { fAPIUI.addHorizontalSlider(label, zone, init, min, max, step); }
    void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override
    { fAPIUI.addNumEntry(label, zone, init, min, max, step); }
    
    // -- passive widgets
    
    void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) override
    { fAPIUI.addHorizontalBargraph(label, zone, min, max); }
    void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) override
    { fAPIUI.addVerticalBargraph(label, zone, min, max); }
    
    // -- metadata declarations
    
    void declare(FAUSTFLOAT* zone, const char* key, const char* val) override { fAPIUI.declare(zone, key, val); }
};

/***************************END OSC SECTION ***************************/

#endif // __bela_osc__
