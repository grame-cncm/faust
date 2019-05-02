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

#ifndef __JSONUIDecoder__
#define __JSONUIDecoder__

#include <vector>
#include <map>
#include <utility>
#include <cstdlib>
#include <sstream>

#include "faust/gui/CGlue.h"
#include "faust/gui/meta.h"
#include "faust/gui/SimpleParser.h"

#ifdef _WIN32
#include <windows.h>
#define snprintf _snprintf
#endif

//-------------------------------------------------------------------
//  Decode a dsp JSON description and implement 'buildUserInterface'
//-------------------------------------------------------------------

#define REAL_UI(ui_interface)  reinterpret_cast<UIReal<REAL>*>(ui_interface)
#define REAL_ADR(offset)       reinterpret_cast<REAL*>(&memory_block[offset])
#define SOUNDFILE_ADR(offset)  reinterpret_cast<Soundfile**>(&memory_block[offset])

template <typename REAL>
struct JSONUIDecoderAux {

    typedef std::map<std::string, std::pair <int, REAL*> > controlMap;
    
    REAL STR2REAL(const std::string& str) { return REAL(std::strtod(str.c_str(), NULL)); }
 
    std::string fName;
    std::string fFileName;
    std::string fJSON;
    std::string fVersion;
    std::string fCompileOptions;
    
    std::map<std::string, std::string> fMetadata;
    std::vector<itemInfo*> fUiItems;     
    
    std::vector<std::string> fLibraryList;
    std::vector<std::string> fIncludePathnames;
    
    REAL* fInControl;
    REAL* fOutControl;
    Soundfile** fSoundfiles;
    
    int fNumInputs, fNumOutputs, fSRIndex;
    int fInputItems, fOutputItems, fSoundfileItems;
    int fDSPSize;
    
    controlMap fPathInputTable;     // [path, <index, zone>]
    controlMap fPathOutputTable;    // [path, <index, zone>]

    bool isInput(const std::string& type) { return (type == "vslider" || type == "hslider" || type == "nentry" || type == "button" || type == "checkbox"); }
    bool isOutput(const std::string& type) { return (type == "hbargraph" || type == "vbargraph"); }
    bool isSoundfile(const std::string& type) { return (type == "soundfile"); }

    JSONUIDecoderAux(const std::string& json)
    {
        fJSON = json;
        const char* p = fJSON.c_str();
        std::map<std::string, std::string > meta_data0;
        std::map<std::string, std::vector<std::string> > meta_data2;
        parseJson(p, meta_data0, fMetadata, meta_data2, fUiItems);
        
        // meta_data0 contains <name : val>, <inputs : val>, <ouputs : val> pairs etc...
        fName = (meta_data0.find("name") != meta_data0.end()) ? meta_data0["name"] : "";
        fFileName = (meta_data0.find("filename") != meta_data0.end()) ? meta_data0["filename"] : "";
        fVersion = (meta_data0.find("version") != meta_data0.end()) ? meta_data0["version"] : "";
        fCompileOptions = (meta_data0.find("compile_options") != meta_data0.end()) ? meta_data0["compile_options"] : "";
        
        if (meta_data2.find("library_list") != meta_data2.end()) {
            fLibraryList = meta_data2["library_list"];
        }
        if (meta_data2.find("include_pathnames") != meta_data2.end()) {
            fIncludePathnames = meta_data2["include_pathnames"];
        }
        
        fDSPSize = (meta_data0.find("size") != meta_data0.end()) ? std::atoi(meta_data0["size"].c_str()) : -1;
        fNumInputs = (meta_data0.find("inputs") != meta_data0.end()) ? std::atoi(meta_data0["inputs"].c_str()) : -1;
        fNumOutputs = (meta_data0.find("outputs") != meta_data0.end()) ? std::atoi(meta_data0["outputs"].c_str()) : -1;
        fSRIndex = (meta_data0.find("sr_index") != meta_data0.end()) ? std::atoi(meta_data0["sr_index"].c_str()) : -1;
       
        fInputItems = 0;
        fOutputItems = 0;
        fSoundfileItems = 0;
        
        std::vector<itemInfo*>::iterator it;
        for (it = fUiItems.begin(); it != fUiItems.end(); it++) {
            std::string type = (*it)->type;
            if (isInput(type)) {
                fInputItems++;
            } else if (isOutput(type)) {
                fOutputItems++;          
            } else if (isSoundfile(type)) {
                fSoundfileItems++;
            }
        }
        
        fInControl = new REAL[fInputItems];
        fOutControl = new REAL[fOutputItems];
        fSoundfiles = new Soundfile*[fSoundfileItems];
        
        int counterIn = 0;
        int counterOut = 0;
        
        // Prepare the fPathTable and init zone
        for (it = fUiItems.begin(); it != fUiItems.end(); it++) {
            std::string type = (*it)->type;
            // Meta data declaration for input items
            if (isInput(type)) {
                if ((*it)->address != "") {
                    fPathInputTable[(*it)->address] = std::make_pair(std::atoi((*it)->index.c_str()), &fInControl[counterIn]);
                }
                fInControl[counterIn] = STR2REAL((*it)->init);
                counterIn++;
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                if ((*it)->address != "") {
                    fPathOutputTable[(*it)->address] = std::make_pair(std::atoi((*it)->index.c_str()), &fOutControl[counterOut]);
                }
                fOutControl[counterOut] = REAL(0);
                counterOut++;
            }
        }
    }
    
    virtual ~JSONUIDecoderAux()
    {
        std::vector<itemInfo*>::iterator it;
        for (it = fUiItems.begin(); it != fUiItems.end(); it++) {
            delete(*it);
        }
        delete [] fInControl;
        delete [] fOutControl;
        delete [] fSoundfiles;
    }
    
    void metadata(Meta* m)
    {
        std::map<std::string, std::string>::iterator it;
        for (it = fMetadata.begin(); it != fMetadata.end(); it++) {
            m->declare((*it).first.c_str(), (*it).second.c_str());
        }
    }
    
    void metadata(MetaGlue* m)
    {
        std::map<std::string, std::string>::iterator it;
        for (it = fMetadata.begin(); it != fMetadata.end(); it++) {
            m->declare(m->metaInterface, (*it).first.c_str(), (*it).second.c_str());
        }
    }
    
    void resetUserInterface()
    {
        std::vector<itemInfo*>::iterator it;
        int item = 0;
        for (it = fUiItems.begin(); it != fUiItems.end(); it++) {
            if (isInput((*it)->type)) {
                fInControl[item++] = STR2REAL((*it)->init);
            }
        }
    }
    
    void resetUserInterface(char* memory_block, Soundfile* defaultsound = nullptr)
    {
        std::vector<itemInfo*>::iterator it;
        for (it = fUiItems.begin(); it != fUiItems.end(); it++) {
            int offset = std::atoi((*it)->index.c_str());
            if (isInput((*it)->type)) {
                *REAL_ADR(offset) = STR2REAL((*it)->init);
            } else if (isSoundfile((*it)->type)) {
                if (*SOUNDFILE_ADR(offset) == nullptr) {
                    *SOUNDFILE_ADR(offset) = defaultsound;
                }
            }
        }
    }
    
    int getSampleRate(char* memory_block)
    {
        return *reinterpret_cast<int*>(&memory_block[fSRIndex]);
    }
   
    void buildUserInterface(UI* ui_interface)
    {
        int counterIn = 0;
        int counterOut = 0;
        int counterSound = 0;
        std::vector<itemInfo*>::iterator it;
        
        for (it = fUiItems.begin(); it != fUiItems.end(); it++) {
            
            std::string type = (*it)->type;
            
            REAL init = STR2REAL((*it)->init);
            REAL min = STR2REAL((*it)->min);
            REAL max = STR2REAL((*it)->max);
            REAL step = STR2REAL((*it)->step);
            
            // Meta data declaration for input items
            if (isInput(type)) {
                for (size_t i = 0; i < (*it)->meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(&fInControl[counterIn], (*it)->meta[i].first.c_str(), (*it)->meta[i].second.c_str());
                }
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                for (size_t i = 0; i < (*it)->meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(&fOutControl[counterOut], (*it)->meta[i].first.c_str(), (*it)->meta[i].second.c_str());
                }
            }
            // Meta data declaration for group opening or closing
            else {
                for (size_t i = 0; i < (*it)->meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(0, (*it)->meta[i].first.c_str(), (*it)->meta[i].second.c_str());
                }
            }
            
            if (type == "hgroup") {
                REAL_UI(ui_interface)->openHorizontalBox((*it)->label.c_str());
            } else if (type == "vgroup") { 
                REAL_UI(ui_interface)->openVerticalBox((*it)->label.c_str());
            } else if (type == "tgroup") {
                REAL_UI(ui_interface)->openTabBox((*it)->label.c_str());
            } else if (type == "vslider") {
                REAL_UI(ui_interface)->addVerticalSlider((*it)->label.c_str(), &fInControl[counterIn], init, min, max, step);
            } else if (type == "hslider") {
                REAL_UI(ui_interface)->addHorizontalSlider((*it)->label.c_str(), &fInControl[counterIn], init, min, max, step);            
            } else if (type == "checkbox") {
                REAL_UI(ui_interface)->addCheckButton((*it)->label.c_str(), &fInControl[counterIn]);
            } else if (type == "soundfile") {
                REAL_UI(ui_interface)->addSoundfile((*it)->label.c_str(), (*it)->url.c_str(), &fSoundfiles[counterSound]);
            } else if (type == "hbargraph") {
                REAL_UI(ui_interface)->addHorizontalBargraph((*it)->label.c_str(), &fOutControl[counterOut], min, max);
            } else if (type == "vbargraph") {
                REAL_UI(ui_interface)->addVerticalBargraph((*it)->label.c_str(), &fOutControl[counterOut], min, max);
            } else if (type == "nentry") {
                REAL_UI(ui_interface)->addNumEntry((*it)->label.c_str(), &fInControl[counterIn], init, min, max, step);
            } else if (type == "button") {
                REAL_UI(ui_interface)->addButton((*it)->label.c_str(), &fInControl[counterIn]);
            } else if (type == "close") {
                REAL_UI(ui_interface)->closeBox();
            }
            
            if (isInput(type)) {
                counterIn++;
            } else if (isOutput(type)) {
                counterOut++;
            } else if (isSoundfile(type)) {
                counterSound++;
            }
        }
    }
    
    void buildUserInterface(UI* ui_interface, char* memory_block)
    {
        int counterSound = 0;
        std::vector<itemInfo*>::iterator it;
        
        for (it = fUiItems.begin(); it != fUiItems.end(); it++) {
            
            std::string type = (*it)->type;
            int offset = std::atoi((*it)->index.c_str());
            
            REAL init = STR2REAL((*it)->init);
            REAL min = STR2REAL((*it)->min);
            REAL max = STR2REAL((*it)->max);
            REAL step = STR2REAL((*it)->step);
            
            // Meta data declaration for input items
            if (isInput(type)) {
                for (size_t i = 0; i < (*it)->meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(REAL_ADR(offset), (*it)->meta[i].first.c_str(), (*it)->meta[i].second.c_str());
                }
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                for (size_t i = 0; i < (*it)->meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(REAL_ADR(offset), (*it)->meta[i].first.c_str(), (*it)->meta[i].second.c_str());
                }
            }
            // Meta data declaration for group opening or closing
            else {
                for (size_t i = 0; i < (*it)->meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(0, (*it)->meta[i].first.c_str(), (*it)->meta[i].second.c_str());
                }
            }
            
            if (type == "hgroup") {
                REAL_UI(ui_interface)->openHorizontalBox((*it)->label.c_str());
            } else if (type == "vgroup") {
                REAL_UI(ui_interface)->openVerticalBox((*it)->label.c_str());
            } else if (type == "tgroup") {
                REAL_UI(ui_interface)->openTabBox((*it)->label.c_str());
            } else if (type == "vslider") {
                REAL_UI(ui_interface)->addVerticalSlider((*it)->label.c_str(), REAL_ADR(offset), init, min, max, step);
            } else if (type == "hslider") {
                REAL_UI(ui_interface)->addHorizontalSlider((*it)->label.c_str(), REAL_ADR(offset), init, min, max, step);
            } else if (type == "checkbox") {
                REAL_UI(ui_interface)->addCheckButton((*it)->label.c_str(), REAL_ADR(offset));
            } else if (type == "soundfile") {
                REAL_UI(ui_interface)->addSoundfile((*it)->label.c_str(), (*it)->url.c_str(), SOUNDFILE_ADR(offset));
            } else if (type == "hbargraph") {
                REAL_UI(ui_interface)->addHorizontalBargraph((*it)->label.c_str(), REAL_ADR(offset), min, max);
            } else if (type == "vbargraph") {
                REAL_UI(ui_interface)->addVerticalBargraph((*it)->label.c_str(), REAL_ADR(offset), min, max);
            } else if (type == "nentry") {
                REAL_UI(ui_interface)->addNumEntry((*it)->label.c_str(), REAL_ADR(offset), init, min, max, step);
            } else if (type == "button") {
                REAL_UI(ui_interface)->addButton((*it)->label.c_str(), REAL_ADR(offset));
            } else if (type == "close") {
                REAL_UI(ui_interface)->closeBox();
            }
            
            if (isSoundfile(type)) {
                counterSound++;
            }
        }
    }
    
    void buildUserInterface(UIGlue* ui_interface, char* memory_block)
    {
        /*
        int counterSound = 0;
        std::vector<itemInfo*>::iterator it;
        
        for (it = fUiItems.begin(); it != fUiItems.end(); it++) {
            
            std::string type = (*it)->type;
            int offset = std::atoi((*it)->index.c_str());
            
            REAL init = STR2REAL((*it)->init);
            REAL min = STR2REAL((*it)->min);
            REAL max = STR2REAL((*it)->max);
            REAL step = STR2REAL((*it)->step);
            
            // Meta data declaration for input items
            if (isInput(type)) {
                for (size_t i = 0; i < (*it)->meta.size(); i++) {
                    ui_interface->declare(ui_interface->uiInterface, REAL_ADR(offset), (*it)->meta[i].first.c_str(), (*it)->meta[i].second.c_str());
                }
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                for (size_t i = 0; i < (*it)->meta.size(); i++) {
                    ui_interface->declare(ui_interface->uiInterface, REAL_ADR(offset), (*it)->meta[i].first.c_str(), (*it)->meta[i].second.c_str());
                }
            }
            // Meta data declaration for group opening or closing
            else {
                for (size_t i = 0; i < (*it)->meta.size(); i++) {
                    ui_interface->declare(ui_interface->uiInterface, 0, (*it)->meta[i].first.c_str(), (*it)->meta[i].second.c_str());
                }
            }
            
            if (type == "hgroup") {
                ui_interface->openHorizontalBox(ui_interface->uiInterface, (*it)->label.c_str());
            } else if (type == "vgroup") {
                ui_interface->openVerticalBox(ui_interface->uiInterface, (*it)->label.c_str());
            } else if (type == "tgroup") {
                ui_interface->openTabBox(ui_interface->uiInterface, (*it)->label.c_str());
            } else if (type == "vslider") {
                ui_interface->addVerticalSlider(ui_interface->uiInterface, (*it)->label.c_str(), REAL_ADR(offset), init, min, max, step);
            } else if (type == "hslider") {
                ui_interface->addHorizontalSlider(ui_interface->uiInterface, (*it)->label.c_str(), REAL_ADR(offset), init, min, max, step);
            } else if (type == "checkbox") {
                ui_interface->addCheckButton(ui_interface->uiInterface, (*it)->label.c_str(), REAL_ADR(offset));
            } else if (type == "soundfile") {
                ui_interface->addSoundfile(ui_interface->uiInterface, (*it)->label.c_str(), (*it)->url.c_str(), &fSoundfiles[counterSound]);
            } else if (type == "hbargraph") {
                ui_interface->addHorizontalBargraph(ui_interface->uiInterface, (*it)->label.c_str(), REAL_ADR(offset), min, max);
            } else if (type == "vbargraph") {
                ui_interface->addVerticalBargraph(ui_interface->uiInterface, (*it)->label.c_str(), REAL_ADR(offset), min, max);
            } else if (type == "nentry") {
                ui_interface->addNumEntry(ui_interface->uiInterface,(*it)->label.c_str(), REAL_ADR(offset), init, min, max, step);
            } else if (type == "button") {
                ui_interface->addButton(ui_interface->uiInterface, (*it)->label.c_str(), REAL_ADR(offset));
            } else if (type == "close") {
                ui_interface->closeBox(ui_interface->uiInterface);
            }
            
            if (isSoundfile(type)) {
                counterSound++;
            }
        }
        */
    }
    
    bool hasCompileOption(const std::string& option)
    {
        std::istringstream iss(fCompileOptions);
        std::string token;
        while (std::getline(iss, token, ' ')) {
            if (token == option) return true;
        }
        return false;
    }
    
};

// Templated decoder

struct JSONUITemplatedDecoder
{

    virtual ~JSONUITemplatedDecoder()
    {}
    
    virtual void metadata(Meta* m) = 0;
    virtual void metadata(MetaGlue* glue) = 0;
    virtual int getDSPSize() = 0;
    virtual std::string getName() = 0;
    virtual std::string getLibVersion() = 0;
    virtual std::string getCompileOptions() = 0;
    virtual std::vector<std::string> getLibraryList() = 0;
    virtual std::vector<std::string> getIncludePathnames() = 0;
    virtual int getNumInputs() = 0;
    virtual int getNumOutputs() = 0;
    virtual int getSampleRate(char* memory_block) = 0;
    virtual void resetUserInterface(char* memory_block, Soundfile* defaultsound = nullptr) = 0;
    virtual void buildUserInterface(UI* ui_interface, char* memory_block) = 0;
    virtual void buildUserInterface(UIGlue* ui_interface, char* memory_block) = 0;
    virtual bool hasCompileOption(const std::string& option) = 0;
};

struct JSONUIFloatDecoder : public JSONUIDecoderAux<float>, public JSONUITemplatedDecoder
{
    JSONUIFloatDecoder(const std::string& json):JSONUIDecoderAux<float>(json)
    {}
    
    void metadata(Meta* m) { JSONUIDecoderAux<float>::metadata(m); }
    void metadata(MetaGlue* glue) { JSONUIDecoderAux<float>::metadata(glue); }
    int getDSPSize() { return fDSPSize; }
    std::string getName() { return fName; }
    std::string getLibVersion() { return fVersion; }
    std::string getCompileOptions() { return fCompileOptions; }
    std::vector<std::string> getLibraryList() { return fLibraryList; }
    std::vector<std::string> getIncludePathnames() { return fIncludePathnames; }
    int getNumInputs() { return fNumInputs; }
    int getNumOutputs() { return fNumOutputs; }
    int getSampleRate(char* memory_block)  { return JSONUIDecoderAux<float>::getSampleRate(memory_block); }
    void resetUserInterface(char* memory_block, Soundfile* defaultsound = nullptr)
    {
        JSONUIDecoderAux<float>::resetUserInterface(memory_block, defaultsound);
    }
    void buildUserInterface(UI* ui_interface, char* memory_block)
    {
        JSONUIDecoderAux<float>::buildUserInterface(ui_interface, memory_block);
    }
    void buildUserInterface(UIGlue* ui_interface, char* memory_block)
    {
        JSONUIDecoderAux<float>::buildUserInterface(ui_interface, memory_block);
    }
    bool hasCompileOption(const std::string& option) { return JSONUIDecoderAux<float>::hasCompileOption(option); }
};

struct JSONUIDoubleDecoder : public JSONUIDecoderAux<double>, public JSONUITemplatedDecoder
{
    JSONUIDoubleDecoder(const std::string& json):JSONUIDecoderAux<double>(json)
    {}
    
    void metadata(Meta* m) { JSONUIDecoderAux<double>::metadata(m); }
    void metadata(MetaGlue* glue) { JSONUIDecoderAux<double>::metadata(glue); }
    int getDSPSize() { return fDSPSize; }
    std::string getName() { return fName; }
    std::string getLibVersion() { return fVersion; }
    std::string getCompileOptions() { return fCompileOptions; }
    std::vector<std::string> getLibraryList() { return fLibraryList; }
    std::vector<std::string> getIncludePathnames() { return fIncludePathnames; }
    int getNumInputs() { return fNumInputs; }
    int getNumOutputs() { return fNumOutputs; }
    int getSampleRate(char* memory_block) { return JSONUIDecoderAux<double>::getSampleRate(memory_block); }
    void resetUserInterface(char* memory_block, Soundfile* defaultsound = nullptr)
    {
        JSONUIDecoderAux<double>::resetUserInterface(memory_block, defaultsound);
    }
    void buildUserInterface(UI* ui_interface, char* memory_block)
    {
        JSONUIDecoderAux<double>::buildUserInterface(ui_interface, memory_block);
    }
    void buildUserInterface(UIGlue* ui_interface, char* memory_block)
    {
        JSONUIDecoderAux<double>::buildUserInterface(ui_interface, memory_block);
    }
    bool hasCompileOption(const std::string& option) { return JSONUIDecoderAux<double>::hasCompileOption(option); }
};

// FAUSTFLOAT decoder

struct JSONUIDecoder : public JSONUIDecoderAux<FAUSTFLOAT>
{
    JSONUIDecoder(const std::string& json):JSONUIDecoderAux<FAUSTFLOAT>(json)
    {}
};

static JSONUITemplatedDecoder* createJSONUIDecoder(const std::string& json)
{
    JSONUIDecoder decoder(json);
    if (decoder.hasCompileOption("-double")) {
        return new JSONUIDoubleDecoder(json);
    } else {
        return new JSONUIFloatDecoder(json);
    }
}

#endif
