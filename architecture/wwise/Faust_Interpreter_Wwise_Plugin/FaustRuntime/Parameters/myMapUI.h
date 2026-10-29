#ifndef MY_MAPUI_H
#define MY_MAPUI_H

#include <faust/gui/MapUI.h>
#include "parameter.h"
#include <unordered_map>

// static counter to increment for each new parameter. Has to be reset on each reseting. 
static int ctr{0};

struct myMapUI : public MapUI
{    
    struct itemInfo {
        std::string type;
        std::string label;
        std::string shortname;
        int index;
        double init;
        double fmin;
        double fmax;
        double step;
        
        itemInfo(std::string t, std::string l, int idx, double i, double mn, double mx, double s)
            :type(t), label(l), index(idx), init(i), fmin(mn), fmax(mx), step(s)
        {}
    };

    // controls are a map of (zone ptrs, itemInfo) pairs.
    std::unordered_map<const FAUSTFLOAT*,itemInfo> controls;

    ~myMapUI();

    /* function that make use of fShortnameZoneMap to fill in the contros the shortName of each param. */
    void fillShortNames();

    // function that moves a new parameter into the controls structure.
    void addParameter(FAUSTFLOAT* zone, std::string type, const char* label, int index, double init = -DBL_MAX, double fmin = -DBL_MAX, double fmax = -DBL_MAX, double step = -DBL_MAX);
    
    // function to reset the static counter that counts the num of params.
    void resetStaticCounter();
    
    /* function that clears all the internal structures, and resets the static counter. */
    void clearParameters();

    // -- active widgets
    void addButton(const char* label, FAUSTFLOAT* zone);

    void addCheckButton(const char* label, FAUSTFLOAT* zone);
    
    void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step);
    
    void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step);

    void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step);
    
    // -- passive widgets
    void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax);
    
    void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax);

    // -- soundfiles
    // virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone);
    
    // -- metadata declarations
    // virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val);
};

#endif