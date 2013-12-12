#ifndef FAUST_PUI_H
#define FAUST_PUI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include "faust/gui/UI.h"
#include <vector>
#include <string>

/*******************************************************************************
 * PUI : Faust User Interface
 * This class print arguments given to calls to UI methods and build complete path for labels.
 ******************************************************************************/

class PrintUI : public UI
{

    protected:
    
        std::vector<std::string> fControlsLevel;
        
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
    
    public:

        PrintUI() {}

        virtual ~PrintUI() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label)
        {
            fControlsLevel.push_back(label);
            std::cout << "openTabBox label : " << label << std::endl;
        }
        virtual void openHorizontalBox(const char* label)
        {
            fControlsLevel.push_back(label);
            std::cout << "openHorizontalBox label : " << label << std::endl;
        }
        virtual void openVerticalBox(const char* label)
        {
            fControlsLevel.push_back(label);
            std::cout << "openVerticalBox label : " << label << std::endl;
        }
        virtual void closeBox()
        {
            fControlsLevel.pop_back();
            std::cout << "closeBox" << std::endl;
        }

        // -- active widgets

        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            std::cout << "addButton label : " << buildPath(label) << std::endl;
        }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            std::cout << "addCheckButton label : " << buildPath(label) << std::endl;
        }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            std::cout << "addVerticalSlider label : " << buildPath(label) << " init : " << init << " min : " << min << " max : " << max << " step : " << step << std::endl;
        }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            std::cout << "addHorizontalSlider label : " << buildPath(label) << " init : " << init << " min : " << min << " max : " << max << " step : " << step << std::endl;
        }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            std::cout << "addNumEntry label : " << buildPath(label) << " init : " << init << " min : " << min << " max : " << max << " step : " << step << std::endl;
        }

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
        {
            std::cout << "addHorizontalBargraph label : " << buildPath(label) << " min : " << min << " max : " << max << std::endl;
        }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            std::cout << "addVerticalBargraph label : " << buildPath(label) << " min : " << min << " max : " << max << std::endl;
        }

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            std::cout << "declare key : " << key << " val : " << val << std::endl;
        }
    
};

#endif
