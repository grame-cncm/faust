#include "myMapUI.h"

myMapUI::~myMapUI() 
{
    resetStaticCounter();
}

 
void myMapUI::fillShortNames()
{
    for (const auto& it : fShortnameZoneMap) {
        const auto& shortName = it.first;
        const FAUSTFLOAT* zone = it.second;

        auto iter = controls.find(zone);  // only access existing item
        if (iter != controls.end()) {
            iter->second.shortname = shortName; // assign shortname
        }
    }
}

void myMapUI::addParameter(FAUSTFLOAT* zone, std::string type, const char* label, int index, double init, double fmin, double fmax, double step) 
{    
    itemInfo item(type, std::string(label), index, init, fmin, fmax, step);
    controls.emplace(zone, std::move(item));
}

void myMapUI::resetStaticCounter()
{
    ctr = 0;
}

void myMapUI::clearParameters()
{
    controls.clear();
    fLabelZoneMap.clear();
    fShortnameZoneMap.clear();
    fPathZoneMap.clear();
    resetStaticCounter();
}

    // -- active widgets
void myMapUI::addButton(const char* label, FAUSTFLOAT* zone)
{
    MapUI::addZoneLabel(label, zone);
    addParameter(zone, "button", label, ctr++);
}

void myMapUI::addCheckButton(const char* label, FAUSTFLOAT* zone)
{
    addZoneLabel(label, zone);
    addParameter(zone, "checkbox", label, ctr++);
}

void myMapUI::addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
{
    addZoneLabel(label, zone);
    addParameter(zone, "slider", label, ctr++, init, fmin, fmax, step);
}

void myMapUI::addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
{
    addZoneLabel(label, zone);
    addParameter(zone, "slider", label, ctr++, init, fmin, fmax, step);
}

void myMapUI::addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
{
    addZoneLabel(label, zone);
    addParameter(zone, "slider", label, ctr++, init, fmin, fmax, step);
}
    
    // -- passive widgets
void myMapUI::addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
{
    addZoneLabel(label, zone);
    addParameter(zone, "bargraph", label, ctr++, -DBL_MAX, fmin, fmax, -DBL_MAX);
}

void myMapUI::addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
{
    addZoneLabel(label, zone);
    addParameter(zone, "bargraph", label, ctr++, -DBL_MAX, fmin, fmax, -DBL_MAX);
}

// -- soundfiles
// virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}

// -- metadata declarations
// virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val){}