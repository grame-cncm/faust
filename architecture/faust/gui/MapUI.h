#ifndef FAUST_PUI_H
#define FAUST_PUI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include "faust/gui/UI.h"
#include <vector>
#include <map>
#include <string>

/*******************************************************************************
 * MapUI : Faust User Interface
 * This class creates a map of complete path and zones for each UI item.
 ******************************************************************************/

class MapUI : public UI
{
    
    protected:
        
        std::vector<std::string> fControlsLevel;
        std::map<std::string, FAUSTFLOAT*> fZoneMap;
        
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
        
        MapUI() {};
        virtual ~MapUI() {};
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            fControlsLevel.push_back(label);
        };
        void openHorizontalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        };
        void openVerticalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        };
        void closeBox()
        {
            fControlsLevel.pop_back();
        };
        
        // -- active widgets
        void insertMap(std::string label, FAUSTFLOAT* zone)
        {
            fZoneMap[label] = zone;
        }
        
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            insertMap(buildPath(label), zone);
        };
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            insertMap(buildPath(label), zone);
        };
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        };
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        };
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        };
        
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            insertMap(buildPath(label), zone);
        };
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            insertMap(buildPath(label), zone);
        };
        
        // -- metadata declarations
        void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {};
        
        // setters
        void setValue(const std::string& path, float value)
        {
            *fZoneMap[path] = value;
        }
        
        float getValue(const std::string& path)
        {
            return *fZoneMap[path];
        }
};

#endif
