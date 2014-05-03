#ifndef FAUST_JSONUI_H
#define FAUST_JSONUI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include "faust/gui/UI.h"
#include "faust/gui/Meta.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

/*******************************************************************************
 * JSONUI : Faust User Interface
 * This class produce a complete JSON decription of the DSP instance.
 ******************************************************************************/

class JSONUI : public UI, public Meta
{

    protected:
    
        std::stringstream fJSON;
        std::stringstream fUI;
        std::stringstream fMeta;
        std::vector<std::string> fControlsLevel;
        bool fClosePar;
        int fTab;
    
        std::string buildPath(const std::string& label) 
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res += fControlsLevel[i];
                res += "/";
            }
            res += label;
            return res;
        }
        
        void tab(int n, std::ostream& fout)
        {
            fout << '\n';
            while (n--) fout << '\t';
        }
      
     public:

        JSONUI(int inputs, int outputs):fTab(0)
        {
            fJSON << "{";
            fTab += 1;
            tab(fTab, fJSON); fJSON << "\"name\": \"\",";
            tab(fTab, fJSON); fJSON << "\"address\": \"\",";
            tab(fTab, fJSON); fJSON << "\"port\": \"0\",";
            if (inputs > 0) { tab(fTab, fJSON); fJSON << "\"inputs\": \"" << inputs << "\","; }
            if (outputs > 0) { tab(fTab, fJSON); fJSON << "\"outputs\": \"" << outputs << "\","; }
            // Start Meta generation
            tab(fTab, fMeta); fMeta << "\"meta\": [";
            // Start UI generation
            tab(fTab, fUI); fUI << "\"ui\": [";
            fClosePar = false;
            fTab += 1;
        }

        virtual ~JSONUI() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label)
        {
            fControlsLevel.push_back(label);
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
                tab(fTab, fUI); fUI << "\"type\": \"tgroup\"," << std::endl;
                tab(fTab, fUI); fUI << "\"label\":" << "\"" << label << "\",";
                tab(fTab, fUI); fUI << "\"items\": [" << std::endl;
            fClosePar = false;
            fTab += 1;
        }
    
        virtual void openHorizontalBox(const char* label)
        {
            fControlsLevel.push_back(label);
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
                tab(fTab, fUI); fUI << "\"type\": \"hgroup\",";
                tab(fTab, fUI); fUI << "\"label\":" << "\"" << label << "\",";
                tab(fTab, fUI); fUI << "\"items\": [";
            fClosePar = false;
            fTab += 1;
        }
    
        virtual void openVerticalBox(const char* label)
        {
            fControlsLevel.push_back(label);
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
                tab(fTab, fUI); fUI << "\"type\": \"vgroup\",";
                tab(fTab, fUI); fUI << "\"label\":" << "\"" << label << "\",";
                tab(fTab, fUI); fUI << "\"items\": [";
            fClosePar = false;
            fTab += 1;
        }
    
        virtual void closeBox()
        {
            fControlsLevel.pop_back();
            fTab -= 1;
            tab(fTab, fUI); fUI << "]";
            fTab -= 1;
            tab(fTab, fUI); fUI << "}" << std::endl;
            fClosePar = true;
        }
    
        // -- active widgets
    
        virtual void addGenericButton(const char* label, const char* name)
        {
            if (fClosePar) fUI << ",";
                tab(fTab, fUI); fUI << "{" << std::endl;
                tab(fTab + 1, fUI); fUI << "\"type\": \"" << name << "\",";
                tab(fTab + 1, fUI); fUI << "\"label\": " << "\"" << label << "\"" << ",";
                tab(fTab + 1, fUI); fUI << "\"address\": " << "\"" << buildPath(label) << "\"" << ",";
            tab(fTab, fUI); fUI << "}";
            fClosePar = true;
        }

        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericButton(label, "button");
        }
    
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
           addGenericButton(label, "checkbutton");
        }
    
        virtual void addGenericEntry(const char* label, const char* name, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            if (fClosePar) fUI << ",";
                tab(fTab, fUI); fUI << "{" << std::endl;
                tab(fTab + 1, fUI); fUI << "\"type\": \"" << name << "\",";
                tab(fTab + 1, fUI); fUI << "\"label\": " << "\"" << label << "\"" << ",";
                tab(fTab + 1, fUI); fUI << "\"address\": " << "\"" << buildPath(label) << "\"" << ",";
                tab(fTab + 1, fUI); fUI << "\"init\": \"" << init << "\",";
                tab(fTab + 1, fUI); fUI << "\"min\": \"" << min << "\",";
                tab(fTab + 1, fUI); fUI << "\"max\": \"" << max << "\",";
                tab(fTab + 1, fUI); fUI << "\"step\": \"" << step << "\"";
            tab(fTab, fUI); fUI << "}";
            fClosePar = true;
        }
    
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericEntry(label, "vslider", init, min, max, step);
        }
    
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericEntry(label, "hslider", init, min, max, step);
        }
    
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericEntry(label, "nentry", init, min, max, step);
        }

        // -- passive widgets
    
        virtual void addGenericBargraph(const char* label, const char* name, FAUSTFLOAT min, FAUSTFLOAT max) 
        {
            if (fClosePar) fUI << ",";
                tab(fTab, fUI); fUI << "{" << std::endl;
                tab(fTab + 1, fUI); fUI << "\"type\": \"" << name << "\",";
                tab(fTab + 1, fUI); fUI << "\"label\": " << "\"" << label << "\"" << ",";
                tab(fTab + 1, fUI); fUI << "\"address\": " << "\"" << buildPath(label) << "\"" << ",";
                tab(fTab + 1, fUI); fUI << "\"min\": \"" << min << "\",";
                tab(fTab + 1, fUI); fUI << "\"max\": \"" << max << "\",";
                tab(fTab, fUI); fUI << "}";
            fClosePar = true;
        }

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
        {
            addGenericBargraph(label, "vbargraph", min, max);
        }
    
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addGenericBargraph(label, "hbargraph", min, max);
        }

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            //std::cout << "declare key : " << key << " val : " << val << std::endl;
        }
    
        // Meta interface
        virtual void declare(const char* key, const char* value)
        {
            if (fClosePar) fMeta << ",";
            tab(fTab, fMeta); fMeta << "{ " << "\"" << key << "\"" << ":" << "\"" << value << "\" }";
            fClosePar = true;
        }
    
        std::string JSON()
        {
            fTab -= 1;
            tab(fTab, fMeta); fMeta << "],";
            tab(fTab, fUI); fUI << "]";
            fTab -= 1;
            fJSON << fMeta.str() << fUI.str();
            tab(fTab, fJSON); fJSON << "}" << std::endl;
            return fJSON.str();
        }
    
};

#endif
