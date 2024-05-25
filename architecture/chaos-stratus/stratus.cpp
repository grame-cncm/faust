/*
 Architecture wrapper for the Chaos Stratus pedal/platform
*/

/******************* BEGIN stratus.cpp ****************/
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <math.h>

#include <iostream>
#include <cstdio>

//
// The exported functions of the resulting shared object
// And we don't want the Faust class to export - so use the '-nvi' option
// in the Faust compiler
//
#define STRATUS_API virtual

//
// The craziest C macro hack I've come across! So, we don't want the Faust stuff to
// to have a superclass of 'DSP' (in lowercase) - so we use the -scn option in the Faust compile.
// And why don't we want that? Because the Stratus engine needs that to be the (super)class
// of the Stratus interface, but we aren't using class hierarchy here, but the adaptor pattern. 
// HOWEVER what the Faust compiler does with the -scn option is a blanket replacement of 'DSP' 
// (in lowercase), even in our code - so if we want to use 'DSP' (in lowercase) we have to hide 
// it from the Faust compiler - and this is how to do that :D
//
#define STRATUS_CLASS d\
s\
p

//
// And this is that "non-DSP" (in lowercase) superclass. 
// Use the option "-scn FaustDSP" to make this work
#define FAUST_SCN FaustDSP
class FAUST_SCN {};

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#define MAXKNOBS 10
#define MAXSWITCHES 5

#ifndef Uint
typedef unsigned int Uint;
#endif


#define NAME_KEY "name"
#define STRATUS_ID_KEY "stratusId"
#define OLD_VERSION_KEY "version"
#define NEW_VERSION_KEY "stratusVersion"
//using namespace std;
//
// Our implementation of the Faust Meta interface
//
class Meta
{
    protected:
        std::string effectName;
        std::string effectId;
        std::string version;
    public:
        void declare(const char* key, const char* value) {
            if (strcmp(key,NAME_KEY) == 0) {
                effectName.assign(value);
            } else if (strcmp(key,STRATUS_ID_KEY) == 0) {
                effectId.assign(value);
            } else if (strcmp(key,NEW_VERSION_KEY) == 0) {
                version.assign(value);
            } else if (strcmp(key,OLD_VERSION_KEY) == 0 && version.empty()) {
                //
                // Support original version key. That clashes with Faust's version key
                //
                version.assign(value);
            }
        }
    friend class STRATUS_CLASS;
    friend class StratusExtensions;
};

//
// A "control set" is used to manage the switches and knobs of a
// Stratus UI and how they map to the actual values in the Faust
// algorithm
//
class UiControlSet {
    //
    // The maximum number of items in the set (MAXKNOBS or MAXSWITCHES)
    //
    Uint max;

    //
    // Controls with ordering metadata get set immediately
    // unordered stuff is inserted afterwards!
    //
    FAUSTFLOAT** controlValues;
    Uint controlCount = 0;

    //
    // Add a control to the set
    //
    // if the provided index is equal to or greater than 0, and less than the 
    // max value for the set, AND it's indicated slot NULL, we set that slot and
    // increment the number that we have set.
    //
    // Otherwise, the control is ignored
    //
    void add_control(FAUSTFLOAT* control, int index) {
        if (index >= 0 && index < max && controlValues[index] == nullptr) {
            controlValues[index] = control;
            controlCount++;
        }
    }

    //
    // Return a value if the index is valid and the pointer in that slot
    // is valid
    //
    inline FAUSTFLOAT getValue(Uint i) {
        return (i < max && controlValues[i] != nullptr) ? *(controlValues[i]) : 0;
    }

    //
    // Set a value if the index is valid and the pointer in that slot
    // is valid
    //
    inline void setValue(Uint i, FAUSTFLOAT value) {
        if (i < max && controlValues[i] != nullptr) *(controlValues[i]) = value;
    }

    UiControlSet(Uint cmax) {
        max = cmax;
        controlValues = new FAUSTFLOAT*[cmax];
        for (int i = 0; i < cmax; ++i) {
            controlValues[i] = nullptr;
        }
    }

    ~UiControlSet() {
        delete[] controlValues;
    }
        
    friend class UI;
    friend class STRATUS_CLASS;
};

class UI {
    int nextIndex = -1;
    FAUSTFLOAT* nextControl = nullptr;

    void add_knob(FAUSTFLOAT* slider) {
        if (slider == nextControl) {
            knobs.add_control(slider, nextIndex);
        }
    }

    void add_switch(FAUSTFLOAT* swtch) {
        if (swtch == nextControl) {
            switches.add_control(swtch, nextIndex);
        }
    }

    void reset_declare_state() {
        nextIndex = -1;
        nextControl = nullptr;
    }

    protected:
        UiControlSet knobs = UiControlSet(MAXKNOBS);
        UiControlSet switches = UiControlSet(MAXSWITCHES);

        Uint getKnobCount() {
            return knobs.controlCount;
        }

        Uint getSwitchCount() {
            return switches.controlCount;
        }

    public:
        void openTabBox(const char* label) {};
        void openHorizontalBox(const char* label) {};
        void openVerticalBox(const char* label) {};
        void closeBox() {};
        void addSoundfile(const char* label, const char* filename, void** sf_zone) {};

        void addButton(const char* label, FAUSTFLOAT* zone) {
            add_switch(zone);
            reset_declare_state();
        };
        void addCheckButton(const char* label, FAUSTFLOAT* zone) {
            add_switch(zone);
            reset_declare_state();
        };
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {
            add_knob(zone);
            reset_declare_state();
        };
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {
            add_knob(zone);
            reset_declare_state();
        };
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {
            FAUSTFLOAT steps = (max - min)/step;
            if (min == 0 && (max == 1 || max == 2) && step == 1) {
                add_switch(zone);
            }
            reset_declare_state();
        };
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {
            reset_declare_state();
        };
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {
            reset_declare_state();
        };

        //
        // The "declare" state machine!
        //
        // We look for the "stratus" key and a single decimal digit as the value
        //
        void declare(FAUSTFLOAT* control, const char* key, const char* val) {
            if (control != nullptr && strcmp("stratus",key) == 0 && strlen(val) == 1 && val[0] >= '0' && val[0] <= '9') {
                nextControl = control;
                nextIndex = val[0] - '0';
            } 
        }

    friend class STRATUS_CLASS;
    friend class StratusExtensions;
};

/******************************************************************************
 ******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/

<<includeIntrinsic>>

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

//
// The interface to the stratus - very similar to Faust, but not exactly the
// the same, so the default implementation is a "protocol converter" between
// the two, allowing the Faust code to be used as-is.
//
// HOWEVER - the Faust code itself may need tweaking to properly implement the
// algorithm that it represents - THIS code is simply how to use Faust code
// 'directly' in the stratus.
//
class STRATUS_CLASS
{
    int fSampleRate = 44100;
    enum SWITCH_STATE
    {
        UP = 0,
        DOWN = 1,
        MIDDLE = 2
    };

    // Use for switch debugging
    void getTextForEnum(SWITCH_STATE enumVal, std::string *out) {
        switch (enumVal) {
            case 0:  *out = "UP";
            case 1:  *out = "DOWN";
            case 2:  *out = "MIDDLE";
            default: *out = "BAD";
        }
        return;
    }

    SWITCH_STATE stompSwitch = DOWN;
    FAUSTCLASS faust;

    protected:
        UI faustUi;
        Meta faustMeta;

        static SWITCH_STATE switchStateFromValue(int value) {
            switch (value) {
                case 0: return SWITCH_STATE::UP;
                case 1: return SWITCH_STATE::DOWN;
                case 2: return SWITCH_STATE::MIDDLE;
                default: return SWITCH_STATE::DOWN;
            }
        }

    public:
        STRATUS_CLASS()
        {
            faust.init(fSampleRate);
            faust.metadata(&faustMeta);
            faust.buildUserInterface(&faustUi);
        }
        ~STRATUS_CLASS() {}

        STRATUS_API void setKnob(int num, float knobVal)
        {
            faustUi.knobs.setValue(num, knobVal);
        }

        STRATUS_API float getKnob(int in)
        {
            return faustUi.knobs.getValue(in);
        }

        STRATUS_API void setSwitch(int num, SWITCH_STATE switchVal)
        {
            faustUi.switches.setValue(num, switchVal);
        }

        STRATUS_API SWITCH_STATE getSwitch(int in)
        {
            Uint switchVal = faustUi.switches.getValue(in);
            return switchStateFromValue(switchVal < 3 ? switchVal : 0);
        }

        STRATUS_API void setStompSwitch(SWITCH_STATE switchVal)
        {
            stompSwitch = switchVal;
        }

        STRATUS_API bool getStompSwitch()
        {
            return stompSwitch;
        }

        STRATUS_API void stompSwitchPressed(int count, FAUSTFLOAT *inputs, FAUSTFLOAT *outputs)
        {
            if (stompSwitch)
            {
                compute(count, inputs, outputs);
            }
            return;
        }

        STRATUS_API void compute(int count, FAUSTFLOAT *inputs, FAUSTFLOAT *outputs) {
            faust.compute(count,&inputs,&outputs);
        }

    friend class StratusExtensions;

};

//
// The Stratus engine appears to look for a VERY precise set of symbols
// representing its interface - obviously you cannot subtract from that - 
// but also it appears that you cannot simply add to that either.
//
// To facilitate various aspects of effect management, then, we create
// a new class that represents extensions. This is instantiated when requested
// via a new C language function.
//
class StratusExtensions {
    private:
        STRATUS_CLASS* effect;
    public:
        StratusExtensions(STRATUS_CLASS* eff){
        effect = eff;
    }
    STRATUS_API const char* getName()
    {
        return effect->faustMeta.effectName.c_str();
    }

        STRATUS_API const char* getEffectId()
    {
        return effect->faustMeta.effectId.c_str();
    }

    STRATUS_API const char * getVersion()
    {
        return effect->faustMeta.version.c_str();
    }

    STRATUS_API Uint getKnobCount() {
        return effect->faustUi.getKnobCount();
    }

    STRATUS_API Uint getSwitchCount() {
        return effect->faustUi.getSwitchCount();
    }
};

extern "C" {
    STRATUS_CLASS* create() {return new STRATUS_CLASS;}
    StratusExtensions* getExtensions(STRATUS_CLASS* effect) {return new StratusExtensions(effect);}
}

using dsp_creator_t = STRATUS_CLASS *(*)();

/******************* END stratus.cpp ****************/
