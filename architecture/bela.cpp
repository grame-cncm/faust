/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/******************* BEGIN bela.cpp ****************/

/************************************************************************
 Bela FAUST Architecture file
 Oli Larkin 2016
 www.olilarkin.co.uk
 Based on owl.cpp
 
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
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
 
 /************************************************************************
    Evolution (2022): Trill Sensors support

    type of sensors supported :
        BAR : Position, Pressure, Touched. (Multitouch not supported)
        SQUARE : Position X & Y, Pressure, Touched. (Multitouch not supported)
        CRAFT : Pressure or index of (first or last) active pin (depend on mode)
    usage : add in Meta data in UI widget of the Faust Code
        TRILL:BAR_POS_n
        TRILL:BAR_LVL_n
        TRILL:BAR_TOUCH_n
        TRILL:SQUARE_XPOS_n
        TRILL:SQUARE_YPOS_n
        TRILL:SQUARE_LVL_n
        TRILL:SQUARE_TOUCH_n
        TRILL:CRAFT_n PIN no_pin
        TRILL:CRAFT_n UP lo_pin-hi_pin (return the index of the higher pin active in the array of pin defined or -1 if no pin active)
        TRILL:CRAFT_n DOWN lo_pin-hi_pin (return the index of the lower pin active in the array of pin defined or -1 if no pin active)
    where n is the sensors index. index suported are 0 to 7 for each type of sensor.
    3 arrays (TrillBarAdress, TrillSquareAdress and TrillCraftAdress) allow to route the i2c addresses of the sensors.
    
    sensibility settings for craft :
        declare trill_settings "{ 'CRAFT_n' : { 'prescaler' : 4 ; 'threshold' : 0.15 } ; CRAFT_m ... }"
        
    mapping of the sensors i2c adresses (required) :
        declare trill_mappings "{'BAR' : {'0' : 0x20 ; '1' : 0x21 ...} ; 'SQUARE' : {'0' : 0x28 ; '1' : 0x29 ...} ; 'CRAFT' : '{'0' : 0x30 ...}' }"
        
    keyboard for polyphony :
        declare trill_keyboard "{CRAFT_n : {'start_pin' : 0 ; 'end_pin' : 29 ; 'start_note' : {'C' : 4} ; 'scale' : {1 ; 0.5 ; 1 ; 1 ; 1 ; 1 ; 0.5 } }; CRAFT_m : {'start_pin' : 0 ; 'end_pin' : 12 ...} ...}"
        
        'start_pin' and 'end_pin' are the limits of the array of pin used for a craft sensor.
        'start_note' is note of the first keyboard's pin in the forme : { 'Note' : octave }.
        'scale' is an optional argument. if not present the scale of the keyboard is chromatic. The scale is defined by the values of spaces betwen the note. The resolution is the semi-tone. ex of scale : { 1 ; 1 ; 1.5 ; 1 ; 1.5 }
        
        The trill_keyboard update the sliders defined as freq, gain and gate (via the mydsp_poly key_On and key_Off functions).
    
 ************************************************************************/ 

#ifndef __FaustBela_H__
#define __FaustBela_H__

#include <cstddef>
#include <string>
#include <iostream>
#include <math.h>
#include <strings.h>
#include <cstdlib>
#include <Bela.h>
#include <Utilities.h>

#include <libraries/Trill/Trill.h>

using namespace std;

#include "faust/gui/SimpleParser.h"
#include "faust/dsp/timed-dsp.h"
#include "faust/gui/DecoratorUI.h"
#include "faust/gui/MidiUI.h"

// for MIDI support
#ifdef MIDICTRL
#include "faust/midi/bela-midi.h"
#endif

// for OSC support
#ifdef OSCCTRL
#include "faust/gui/BelaOSCUI.h"
#endif

// for HTTPDGUI support
#ifdef HTTPDGUI
#include "faust/gui/httpdUI.h"
#endif

// for soundfile support
#ifdef SOUNDFILE
#include "faust/gui/SoundUI.h"
#endif

// for polyphonic synths
#include "faust/dsp/poly-dsp.h"

// for polyphonic synths with FX
#ifdef POLY2
#include "faust/dsp/dsp-combiner.h"
#include "effect.h"
#endif

const unsigned int i2cBus = 1;

const char* const pinNamesStrings[] =
{
    "ANALOG_0",
    "ANALOG_1",
    "ANALOG_2",
    "ANALOG_3",
    "ANALOG_4",
    "ANALOG_5",
    "ANALOG_6",
    "ANALOG_7",
    "ANALOG_8",
    "DIGITAL_0",
    "DIGITAL_1",
    "DIGITAL_2",
    "DIGITAL_3",
    "DIGITAL_4",
    "DIGITAL_5",
    "DIGITAL_6",
    "DIGITAL_7",
    "DIGITAL_8",
    "DIGITAL_9",
    "DIGITAL_10",
    "DIGITAL_11",
    "DIGITAL_12",
    "DIGITAL_13",
    "DIGITAL_14",
    "DIGITAL_15",
    "ANALOG_OUT_0", // outputs
    "ANALOG_OUT_1",
    "ANALOG_OUT_2",
    "ANALOG_OUT_3",
    "ANALOG_OUT_4",
    "ANALOG_OUT_5",
    "ANALOG_OUT_6",
    "ANALOG_OUT_7",
    "ANALOG_OUT_8",
    "BAR_POS_0",   // Trill sensors
    "BAR_LVL_0",
    "BAR_TOUCH_0",
    "BAR_POS_1",
    "BAR_LVL_1",
    "BAR_TOUCH_1",
    "BAR_POS_2",
    "BAR_LVL_2",
    "BAR_TOUCH_2",
    "BAR_POS_3",
    "BAR_LVL_3",
    "BAR_TOUCH_3",
    "BAR_POS_4",
    "BAR_LVL_4",
    "BAR_TOUCH_4",
    "BAR_POS_5",
    "BAR_LVL_5",
    "BAR_TOUCH_5",
    "BAR_POS_6",
    "BAR_LVL_6",
    "BAR_TOUCH_6",
    "BAR_POS_7",
    "BAR_LVL_7",
    "BAR_TOUCH_7",
    "SQUARE_XPOS_0",
    "SQUARE_YPOS_0",
    "SQUARE_LVL_0",
    "SQUARE_TOUCH_0",
    "SQUARE_XPOS_1",
    "SQUARE_YPOS_1",
    "SQUARE_LVL_1",
    "SQUARE_TOUCH_1",
    "SQUARE_XPOS_2",
    "SQUARE_YPOS_2",    
    "SQUARE_LVL_2",
    "SQUARE_TOUCH_2",
    "SQUARE_XPOS_3",
    "SQUARE_YPOS_3",
    "SQUARE_LVL_3",
    "SQUARE_TOUCH_3",
    "SQUARE_XPOS_4",
    "SQUARE_YPOS_4",    
    "SQUARE_LVL_4",
    "SQUARE_TOUCH_4",
    "SQUARE_XPOS_5",
    "SQUARE_YPOS_5",
    "SQUARE_LVL_5",
    "SQUARE_TOUCH_5",
    "SQUARE_XPOS_6",
    "SQUARE_YPOS_6",    
    "SQUARE_LVL_6",
    "SQUARE_TOUCH_6",
    "SQUARE_XPOS_7",
    "SQUARE_YPOS_7",
    "SQUARE_LVL_7",
    "SQUARE_TOUCH_7",
    "CRAFT_0",
    "CRAFT_1",
    "CRAFT_2",
    "CRAFT_3",
    "CRAFT_4",
    "CRAFT_5",
    "CRAFT_6",
    "CRAFT_7"
};

enum EInOutPin
{
    kNoPin = -1,
    kANALOG_0 = 0,
    kANALOG_1,
    kANALOG_2,
    kANALOG_3,
    kANALOG_4,
    kANALOG_5,
    kANALOG_6,
    kANALOG_7,
    kANALOG_8,
    kDIGITAL_0,
    kDIGITAL_1,
    kDIGITAL_2,
    kDIGITAL_3,
    kDIGITAL_4,
    kDIGITAL_5,
    kDIGITAL_6,
    kDIGITAL_7,
    kDIGITAL_8,
    kDIGITAL_9,
    kDIGITAL_10,
    kDIGITAL_11,
    kDIGITAL_12,
    kDIGITAL_13,
    kDIGITAL_14,
    kDIGITAL_15,
    kANALOG_OUT_0,
    kANALOG_OUT_1,
    kANALOG_OUT_2,
    kANALOG_OUT_3,
    kANALOG_OUT_4,
    kANALOG_OUT_5,
    kANALOG_OUT_6,
    kANALOG_OUT_7,
    kANALOG_OUT_8,
    kBAR_POS_0,
    kBAR_LVL_0,
    kBAR_TOUCH_0,
    kBAR_POS_1,
    kBAR_LVL_1,
    kBAR_TOUCH_1,
    kBAR_POS_2,
    kBAR_LVL_2,
    kBAR_TOUCH_2,
    kBAR_POS_3,
    kBAR_LVL_3,
    kBAR_TOUCH_3,
    kBAR_POS_4,
    kBAR_LVL_4,
    kBAR_TOUCH_4,
    kBAR_POS_5,
    kBAR_LVL_5,
    kBAR_TOUCH_5,
    kBAR_POS_6,
    kBAR_LVL_6,
    kBAR_TOUCH_6,
    kBAR_POS_7,
    kBAR_LVL_7,
    kBAR_TOUCH_7,
    kSQUARE_XPOS_0,
    kSQUARE_YPOS_0,
    kSQUARE_LVL_0,
    kSQUARE_TOUCH_0,
    kSQUARE_XPOS_1,
    kSQUARE_YPOS_1,
    kSQUARE_LVL_1,
    kSQUARE_TOUCH_1,
    kSQUARE_XPOS_2,
    kSQUARE_YPOS_2,
    kSQUARE_LVL_2,    
    kSQUARE_TOUCH_2,
    kSQUARE_XPOS_3,
    kSQUARE_YPOS_3,
    kSQUARE_LVL_3,
    kSQUARE_TOUCH_3,
    kSQUARE_XPOS_4,
    kSQUARE_YPOS_4,
    kSQUARE_LVL_4,    
    kSQUARE_TOUCH_4,
    kSQUARE_XPOS_5,
    kSQUARE_YPOS_5,
    kSQUARE_LVL_5,
    kSQUARE_TOUCH_5,
    kSQUARE_XPOS_6,
    kSQUARE_YPOS_6,
    kSQUARE_LVL_6,    
    kSQUARE_TOUCH_6,
    kSQUARE_XPOS_7,
    kSQUARE_YPOS_7,
    kSQUARE_LVL_7,
    kSQUARE_TOUCH_7,
    kCRAFT_0,
    kCRAFT_1,
    kCRAFT_2,
    kCRAFT_3,
    kCRAFT_4,
    kCRAFT_5,
    kCRAFT_6,
    kCRAFT_7,
    kNumInputPins
};

const char* const NoteStrings[] =
{
    "A",
    "A#",
    "B",
    "C",
    "C#",
    "D",
    "D#",
    "E",
    "F",
    "F#",
    "G",
    "G#"
};

/**
 * @brief parseBracketString, parse an arbitrary {} string {...} and store the result in s
 * @param p the string to parse, then the remaining string
 * @param quote the character used to quote the string
 * @param s the string found if any
 * @return true if a string was found at the begin of p
 */
static bool parseBracketString(const char*& p, string& s)
{
    string str;
    skipBlank(p);
    int level = 0;
    
    const char* saved = p;  // to restore position if we fail
    if (*p++ == '{') {
        level++;
        while (*p != 0) {
            if (*p == '{') level ++;
            else if (*p == '}') {
                if (level > 1) {
                    level--;
                } else {
                  *p++;
                   break;
                }
            }
            str += *p++;
        }
        if (level == 1) {
            s = "{" + str + "}";
            return true;
        }
    }
    p = saved;
    return false;
}

/**
 * @brief parseMenuItemStr, parse a menu item ...'low':{...}...
 * @param p the string to parse, then the remaining string
 * @param name the name found
 * @param value the value found as String
 * @return true if a nemu item was found
 */
static bool parseMenuItemStr(const char*& p, string& name, string& value)
{
    const char* saved = p;  // to restore position if we fail
    if (parseSQString(p, name) && parseChar(p, ':') && parseBracketString(p, value)) {
        return true;
    } else {
        p = saved;
        return false;
    }
}

/**
 * @brief parseMenuListMenu, parse a menu list { 'setting1' : { 'param1' : 40 ; 'param2' : 880.0 ...} ; 'setting2' : { 'param1' : 40 ; 'param2' : 880.0 ...}...}
 * @param p the string to parse, then the remaining string
 * @param names the vector of names found
 * @param values the vector of menus found
 * @return true if a menu list was found
 */
static bool parseMenuListMenu(const char*& p, vector<string>& names, vector<string>& values)
{
    vector<string> tmpnames;
    vector<string> tmpvalues;
    const char* saved = p; // to restore position if we fail

    if (parseChar(p, '{')) {
        do {
            string n;
            string v;
            if (parseMenuItemStr(p, n, v)) {
                tmpnames.push_back(n);
                tmpvalues.push_back(v);
            } else {
                p = saved;
                return false;
            }
        } while (parseChar(p, ';'));
        if (parseChar(p, '}')) {
            // we suceeded
            names = tmpnames;
            values = tmpvalues;
            return true;
        }
    }
    p = saved;
    return false;
}

/// ---------------------------------------------------------------------
// Parse list of double
/// ---------------------------------------------------------------------
static bool parseListDouble(const char*& p, vector<double>& items)
{
    const char* saved = p;  // to restore position if we fail    
    if (parseChar(p, '{')) {
        do {
            double item;
            if (!parseDouble(p, item)) {
                p = saved;
                return false;
            }
            items.push_back(item);
        } while (tryChar(p, ';'));
    
        return parseChar(p, '}');
    }
    return false;
}

static dsp* gDSP = NULL;

/**************************************************************************************
 BelaWidget : object used by BelaUI to ensures the connection between a Bela parameter
 and a Faust widget
 ***************************************************************************************/

class BelaWidget
{
    
    protected:
        
        EInOutPin fBelaPin;
        FAUSTFLOAT* fZone;  // zone
        const char* fLabel;  // label
        FAUSTFLOAT fMin;    // minimal value
        FAUSTFLOAT fRange;  // value range (max-min)
        
    public:
        
        BelaWidget()
        :fBelaPin(kNoPin)
        ,fZone(0)
        ,fLabel("")
        ,fMin(0)
        ,fRange(1)
        {}
        
        BelaWidget(const BelaWidget& w)
        :fBelaPin(w.fBelaPin)
        ,fZone(w.fZone)
        ,fLabel(w.fLabel)
        ,fMin(w.fMin)
        ,fRange(w.fRange)
        {}
        
        BelaWidget(EInOutPin pin, FAUSTFLOAT* z, const char* l, FAUSTFLOAT lo, FAUSTFLOAT hi)
        :fBelaPin(pin)
        ,fZone(z)
        ,fLabel(l)
        ,fMin(lo)
        ,fRange(hi-lo)
        {}
        
        virtual ~BelaWidget() {}
        
        virtual bool setParameters(const char* parameters)
        { 
            return false; 
        }
        
        virtual void update(BelaContext* context)
        {
            switch(fBelaPin) {
                case kANALOG_0:
                case kANALOG_1:
                case kANALOG_2:
                case kANALOG_3:
                case kANALOG_4:
                case kANALOG_5:
                case kANALOG_6:
                case kANALOG_7:
                    *fZone = fMin + fRange * analogReadNI(context, 0, (int)fBelaPin);
                    break;
                    
                case kDIGITAL_0:
                case kDIGITAL_1:
                case kDIGITAL_2:
                case kDIGITAL_3:
                case kDIGITAL_4:
                case kDIGITAL_5:
                case kDIGITAL_6:
                case kDIGITAL_7:
                case kDIGITAL_8:
                case kDIGITAL_9:
                case kDIGITAL_10:
                case kDIGITAL_11:
                case kDIGITAL_12:
                case kDIGITAL_13:
                case kDIGITAL_14:
                case kDIGITAL_15:
                    *fZone = digitalRead(context, 0, ((int)fBelaPin - kDIGITAL_0)) == 0 ? fMin : fMin+fRange;
                    break;
                    
                case kANALOG_OUT_0:
                case kANALOG_OUT_1:
                case kANALOG_OUT_2:
                case kANALOG_OUT_3:
                case kANALOG_OUT_4:
                case kANALOG_OUT_5:
                case kANALOG_OUT_6:
                case kANALOG_OUT_7:
                    analogWriteNI(context, 0, ((int)fBelaPin) - kANALOG_OUT_0, (*fZone - fMin)/(fRange+fMin));
                    break;
                    
                default:
                    break;
            };
        }
        
        virtual EInOutPin getBelaPin()
        {
            return  fBelaPin;
        }
            
};

/**************************************************************************************
 
 TrillWidget : object used by BelaUI to ensures the connection between a Trill sensors values
 and a Faust widget.
 
 ***************************************************************************************/

class TrillWidget : public BelaWidget
{
    protected:
       
        Trill* sensor;
        Trill::Device type;
      
    public:
     
        TrillWidget():BelaWidget()
        {
            sensor = NULL;
            type = Trill::NONE;
        }

        TrillWidget(const TrillWidget& w):BelaWidget((BelaWidget)w)
        {
            sensor = NULL;
            type = Trill::NONE;
        }

        TrillWidget(EInOutPin pin, FAUSTFLOAT* z, const char* l, FAUSTFLOAT lo, FAUSTFLOAT hi)
        {
            fBelaPin = pin;
            fZone = z;      // zone
            fLabel = l;     // label
            fMin = lo;      // minimal value
            fRange = hi;
            sensor = NULL;
            if (strstr(pinNamesStrings[fBelaPin], "BAR")) {
                type = Trill::BAR;
            } else if (strstr(pinNamesStrings[fBelaPin], "SQUARE")) {
                type = Trill::SQUARE;
            } else {
                type = Trill::NONE;
            }
        }
        
        virtual ~TrillWidget() {}
        
        virtual void setSensor(Trill* nSensor)
        {
            if (nSensor) sensor = nSensor;
        }
        
        /* set the parameters defined in the declare directive or in the widget's metadata */
        virtual bool setParameters(const char* parameters)
        {
            const char* saved = parameters; // to restore position if we fail
            bool result = false;
            if (parseChar(parameters, '{')) {
                do {
                    string n;
                    string v;
                    double vd;
                    if (parseMenuItemStr(parameters, n, v)) {
                        setParameter(n, v);
                        result = true;
                    } else if (parseMenuItem(parameters, n, vd)) {
                        setParameter(n, vd);
                        result = true;
                    }
                    else {
                        parameters = saved;
                        return result;
                    }
                } while (parseChar(parameters, ';'));
                if (parseChar(parameters, '}')) {
                    // we suceeded
                    return result;
                }
            }
            parameters = saved;
            return result;               
        }
        
        virtual void setParameter(const string& name, double value) { }
        
        virtual void setParameter(const string& name, const string& value) { }

        virtual void update(BelaContext* context)
        {
            float val = 0.f;
            switch (fBelaPin) {
                case kBAR_POS_0:
                case kBAR_POS_1:
                case kBAR_POS_2:
                case kBAR_POS_3:
                case kBAR_POS_4:
                case kBAR_POS_5:
                case kBAR_POS_6:
                case kBAR_POS_7:
                    if (sensor && sensor->getNumTouches() > 0)
                        val = sensor->compoundTouchLocation();
                    *fZone = fMin + fRange * val;
                    break;
                
                case kBAR_LVL_0:
                case kBAR_LVL_1:
                case kBAR_LVL_2:
                case kBAR_LVL_3:
                case kBAR_LVL_4:
                case kBAR_LVL_5:
                case kBAR_LVL_6:
                case kBAR_LVL_7:
                    if (sensor && sensor->getNumTouches() > 0)
                        val = sensor->compoundTouchSize();
                    *fZone = fMin + fRange * val;
                    break;
                    
                case kBAR_TOUCH_0:
                case kBAR_TOUCH_1:
                case kBAR_TOUCH_2:
                case kBAR_TOUCH_3:
                case kBAR_TOUCH_4:
                case kBAR_TOUCH_5:
                case kBAR_TOUCH_6:
                case kBAR_TOUCH_7:
                    if (sensor)
                        val = sensor->getNumTouches();
                    *fZone = max(fRange,val);
                    break;
                    
                case kSQUARE_XPOS_0:
                case kSQUARE_XPOS_1:
                case kSQUARE_XPOS_2:
                case kSQUARE_XPOS_3:
                case kSQUARE_XPOS_4:
                case kSQUARE_XPOS_5:
                case kSQUARE_XPOS_6:
                case kSQUARE_XPOS_7:
                    if (sensor && sensor->getNumTouches() > 0)
                        val = sensor->compoundTouchHorizontalLocation();
                    *fZone = fMin + fRange * val;
                    break;
                
                case kSQUARE_YPOS_0:
                case kSQUARE_YPOS_1:
                case kSQUARE_YPOS_2:
                case kSQUARE_YPOS_3:
                case kSQUARE_YPOS_4:
                case kSQUARE_YPOS_5:
                case kSQUARE_YPOS_6:
                case kSQUARE_YPOS_7:
                    if (sensor && sensor->getNumTouches() > 0)
                        val = sensor->compoundTouchLocation();
                    *fZone = fMin + fRange * val;
                    break;
                
                case kSQUARE_LVL_0:
                case kSQUARE_LVL_1:
                case kSQUARE_LVL_2:
                case kSQUARE_LVL_3:
                case kSQUARE_LVL_4:
                case kSQUARE_LVL_5:
                case kSQUARE_LVL_6:
                case kSQUARE_LVL_7:
                    if (sensor && sensor->getNumTouches() > 0)
                        val = sensor->compoundTouchSize();
                    *fZone = fMin + fRange * val;
                    break;
                
                case kSQUARE_TOUCH_0:
                case kSQUARE_TOUCH_1:
                case kSQUARE_TOUCH_2:
                case kSQUARE_TOUCH_3:
                case kSQUARE_TOUCH_4:
                case kSQUARE_TOUCH_5:
                case kSQUARE_TOUCH_6:
                case kSQUARE_TOUCH_7:
                    if (sensor)
                        val = sensor->getNumTouches();
                    *fZone = max(fRange,val);
                    break;
                    
                default:
                    break;
            };
        }
        
        Trill::Device getType() { return type; }
        
        Trill* getSensor() { return sensor; }
};

/**************************************************************************************
 
 TrillCraftWidget : object used by BelaUI to ensures the connection between a Trill Craft sensors values
 and a Faust widget.
 
 ***************************************************************************************/
typedef struct {
    int note;
    double state;
} TrillNote;

class TrillCraftWidget : public TrillWidget
{
     protected:
    
        int lopin;
        int hipin;
        string mode;
        int prescaler;
        double threshold;
        
        vector<TrillNote*> Keyboard;                    // list of keys in the trillkeyboard (polyphony mode)
        int start_note;
        vector<int> Scale;                              // in semitone

        int noteToMidiNumber(const string& note, int octave)    // return the midi number of the note at the octave defined
        {
            if (octave >= 0) {
               int deltaoct = octave*12;
               int deltanote = 0;
               for (int i = 0; i < 12 ; i++) {
                   if (strcasecmp(note.c_str(),NoteStrings[i]) == 0) {
                       deltanote = i;
                   }
               }
               return deltaoct+deltanote+21;
            } else {
                return 69;
            }
        }

     public:   
        
        TrillCraftWidget():TrillWidget()
        {
            sensor = NULL;
            type = Trill::CRAFT;
            lopin = -1;
            hipin = -1;
            mode = "PIN";
            prescaler = 2;
            threshold = 0.10;
            start_note = 0;
        }

        TrillCraftWidget(const TrillCraftWidget& w):TrillWidget((TrillWidget)w)
        {
            sensor = NULL;
            type = Trill::CRAFT;
            lopin = -1;
            hipin = -1;
            mode = "PIN";
            prescaler = 2;
            threshold = 0.10;
            start_note = 0;
        }

        TrillCraftWidget(EInOutPin pin, FAUSTFLOAT* z, const char* l, FAUSTFLOAT lo, FAUSTFLOAT hi)
        {
            fBelaPin = pin;
            fZone = z;  // zone
            fLabel = l; // label
            fMin = lo;  // minimal value
            fRange = hi;
            sensor = NULL;
            type = Trill::CRAFT;
            lopin = -1;
            hipin = -1;
            mode = "PIN";
            prescaler = 2;
            threshold = 0.10;
            start_note = 0;
        }
        
        virtual ~TrillCraftWidget() 
        {
            for (auto t : Keyboard) {
                delete t;
            }
        }
        
        virtual void setSensor(Trill* nSensor)
        {
            TrillWidget::setSensor(nSensor);   
            if (sensor) {
                sensor->setPrescaler(prescaler);
                sensor->setNoiseThreshold(threshold);
            }
        }
        
        virtual bool setParameters(const char* parameters)
        {
            if (parameters && !TrillWidget::setParameters(parameters)) {
                if (parseWord(parameters, "PIN")) {
                    mode = "PIN"; 
                } else if (parseWord(parameters, "UP")) {
                    mode = "UP";
                } else if (parseWord(parameters, "DOWN")) {
                    mode = "DOWN";
                }
                double tmpval = 0.;
                if (parameters && parseDouble(parameters, tmpval)) {
                    lopin = (int)tmpval;
                } else {
                    lopin = -1;
                }
                if (parameters && parseChar(parameters, '-') && parseDouble(parameters, tmpval)) {
                    hipin = (int)tmpval;
                } else {
                    hipin = -1;
                }
            }
            return true;
        }
        
        virtual void setParameter(const string& name, double value)
        {
            TrillWidget::setParameter(name, value);
            if (name == "prescaler") prescaler = (int)value;
            else if (name == "threshold") threshold = (int)value;
            else if (name == "start_pin") lopin = (int)value;
            else if (name == "end_pin") hipin = (int)value;
        }

        virtual void setParameter(const string& name, const string& value)
        {
            const char* tmpval = value.c_str();
            if (name == "start_note") {
                vector<string> names;
                vector<double> values;
                if (parseMenuList(tmpval, names, values) && names.size() > 0) {
                    start_note = noteToMidiNumber(names[0], (int)values[0]);
                }
            } else if (name == "scale") {
                vector<double> values;
                if (parseListDouble(tmpval, values) && values.size() > 0) {
                    for (int i = 0; i < values.size(); i++) {
                        Scale.push_back((int)(values[i]*2));
                    }
                }
            }
        }
        
        virtual void update(BelaContext* context)
        {
            if (sensor && lopin >= 0)
            {
                float val = -1.f;
                if (mode == "PIN") {
                    val = sensor->rawData[lopin];
                    *fZone = fMin + fRange * val;
                }
                else if (mode == "UP") {
                    float sval = 0.f;
                    for (int i = hipin; i >= lopin; i--)
                    {
                        sval = sensor->rawData[i];
                        if (sval > 0.f)
                        {    
                            val = i-lopin;
                            break;
                        }
                    }            
                    *fZone = val;
                }
                else if (mode == "DOWN") {
                    float sval = 0.f;
                    for (int i = lopin; i <= hipin; i++)
                    {
                        sval = sensor->rawData[i];
                        if (sval > 0.f)
                        {
                            val = i-lopin;
                            break;
                        }
                    }
                    *fZone = val;
                } else if (mode == "KEYBOARD") {
                    mydsp_poly* TmpDsp = (mydsp_poly*)gDSP;
                    for (int i = lopin; i <= hipin; i++) {
                        TrillNote* CurKey = Keyboard[i-lopin];
                        double sval = sensor->rawData[i];
                        if (sval == 0 && CurKey->state > 0) {
                            TmpDsp->keyOff(0,CurKey->note);
                            CurKey->state = 0;
                        } else if (sval > 0 && CurKey->state == 0) {
                            TmpDsp->keyOn(0,CurKey->note, (int) (sval*127));
                            CurKey->state = sval;
                        }
                    }
                }
            }
        }
        
        void setMode(const string& mo) 
        { 
            mode = mo;             
            if (mode == "KEYBOARD" && lopin >= 0 && hipin >= lopin && start_note > 0) {   // create the array of trill keyboard
                double curnote = start_note;
                int scalecounter = 0;
                for (int i = lopin ; i <= hipin ; i++) {
                    TrillNote* newkey = new TrillNote;
                    newkey->note = curnote;
                    newkey->state = 0;
                    Keyboard.push_back(newkey);
                    if (Scale.size() > 0) {                     //configure the custom scale
                        if (scalecounter >= Scale.size()) {
                            scalecounter = 0;
                        }
                        curnote = curnote + Scale[scalecounter];
                        scalecounter++;
                    } else {
                        curnote = curnote + 1;                  // configure default scale (chromatic)
                    }
                }
            }
        }
        
        void setLopin(int pin) { lopin = pin; }
        
        void setHipin(int pin) { hipin = pin; }
};

/**************************************************************************************
 
 BelaUI : Faust User Interface builder. Passed to buildUserInterface BelaUI allows
 the mapping between BELA pins and Faust widgets. It relies on specific
 metadata "...[BELA:DIGITAL_0]..." in the widget's label for that. For example any
 Faust widget with metadata [BELA:DIGITAL_0] will be controlled by DIGITAL_0
 (the second knob).
 
 ***************************************************************************************/

// The maximum number of mappings between Bela parameters and Faust widgets
// To be modified: We can have 8 inputs, 8 outputs, and 16 digital In or Out.
#define MAXBELAWIDGETS 16

// Max number of trill sensors parameters mapped.
// max of 8 BAR sensors with 3 parameters (Position,Pressure,Touch), 8 SQUARE sensors with 4 parameters
// (Position X, Position Y, Pressure, Touch), 8 CRAFT sensors with 1 parameter
#define MAXTRILLWIDGETS 64

class BelaUI : public GenericUI, public Meta
{
    
    private:
        
        int fIndex;                                 // number of BelaWidgets collected so far
        EInOutPin fBelaPin;                         // current pin id
        BelaWidget fTable[MAXBELAWIDGETS];          // list of BelaWidgets
        
        EInOutPin fTrillPin;                        // current trill pin id
        vector<TrillWidget*> fTrillTable;           // list of TrillWidget
        const char* fTrillParams;
        
        vector<Trill*> fTouchSensors;               // list of Trill sensors

        // Check if the widget is linked to a Bela parameter and, if so, add the corresponding BelaWidget
        void addBelaWidget(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT lo, FAUSTFLOAT hi)
        {
            if (fBelaPin != kNoPin && (fIndex < MAXBELAWIDGETS)) {
                fTable[fIndex] = BelaWidget(fBelaPin, zone, label, lo, hi);
                fIndex++;
            }
            fBelaPin = kNoPin;
        }
        
        void addTrillWidget(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT lo, FAUSTFLOAT hi)
        {
            if (fTrillPin != kNoPin && (fTrillTable.size() < MAXTRILLWIDGETS)) {
            
                if (strstr(pinNamesStrings[fTrillPin], "CRAFT"))
                {
                    TrillCraftWidget* newcraft = new TrillCraftWidget(fTrillPin, zone, label, lo, hi);
                    newcraft->setParameters(fTrillParams);    
                    fTrillTable.push_back(newcraft);
                }
                else
                {
                    TrillWidget* newtrill = new TrillWidget(fTrillPin, zone, label, lo, hi);
                    newtrill->setParameters(fTrillParams);    
                    fTrillTable.push_back(newtrill);
                }
                
            }
            fTrillPin = kNoPin;
            fTrillParams = NULL;
        }
        
        TrillWidget* findTrillbyid(int id)
        {
            for (int i = 0; i < fTrillTable.size(); i++) {
                if (fTrillTable[i]->getBelaPin() == id)
                    return fTrillTable[i];
            }
            return NULL;
        }
        
    public:
        
        BelaUI()
        : fIndex(0)
        , fBelaPin(kNoPin)
        , fTrillPin(kNoPin)
        , fTrillParams(NULL)
        {}
        
        virtual ~BelaUI()
        {
            for (auto t : fTrillTable) {
                delete t;
            }
            for (auto t : fTouchSensors) {
                delete t;
            }
        }
        
        // Should be called before compute() to update widget's zones registered as Bela parameters
        void update(BelaContext* context)
        {
            for (int i = 0; i < fIndex; i++) {
                fTable[i].update(context);
            }
            for (size_t i = 0; i < fTrillTable.size(); i++) {
                fTrillTable[i]->update(context);
            }
        }
        
        // Should be called in auxiliary loop to read de sensor's values
        void updateSensors()
        {
            for (size_t n = 0; n < fTouchSensors.size(); ++n) {
                Trill* t = fTouchSensors[n];
                t->readI2C();
            }  
        }
        
        // -- active widgets
        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            if (fBelaPin != kNoPin)
                addBelaWidget(label, zone, FAUSTFLOAT(0), FAUSTFLOAT(1)); 
            else
                addTrillWidget(label, zone, FAUSTFLOAT(0), FAUSTFLOAT(1)); 
        }
        
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            if (fBelaPin != kNoPin)
                addBelaWidget(label, zone, FAUSTFLOAT(0), FAUSTFLOAT(1)); 
            else
                addTrillWidget(label, zone, FAUSTFLOAT(0), FAUSTFLOAT(1));  
        }
        
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT lo, FAUSTFLOAT hi, FAUSTFLOAT step)
        {
            if (fBelaPin != kNoPin)
                addBelaWidget(label, zone, lo, hi); 
            else
                addTrillWidget(label, zone, lo, hi); 
        }
        
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT lo, FAUSTFLOAT hi, FAUSTFLOAT step)
        {
            if (fBelaPin != kNoPin)
                addBelaWidget(label, zone, lo, hi); 
            else
                addTrillWidget(label, zone, lo, hi); 
        }
        
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT lo, FAUSTFLOAT hi, FAUSTFLOAT step)
        {
            if (fBelaPin != kNoPin)
                addBelaWidget(label, zone, lo, hi); 
            else
                addTrillWidget(label, zone, lo, hi); 
        }
        
        // -- passive widgets
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT lo, FAUSTFLOAT hi)
        { addBelaWidget(label, zone, lo, hi); }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT lo, FAUSTFLOAT hi)
        { addBelaWidget(label, zone, lo, hi); }
        
        // -- metadata declarations
        virtual void declare(FAUSTFLOAT* z, const char* k, const char* id)
        {
            if (strcasecmp(k, "BELA") == 0) {
                for (int i = 0; i < kNumInputPins; i++) {
                    if (strcasecmp(id, pinNamesStrings[i]) == 0) {
                        fBelaPin = (EInOutPin)i;
                    }
                }
            }
            else if (strcasecmp(k, "TRILL") == 0) {
                for (int i = 0; i < kNumInputPins; i++) {
                    if (strstr(id, pinNamesStrings[i])) {
                        fTrillPin = (EInOutPin)i;
                        const char* tmp = id;
                        if (parseWord(tmp, pinNamesStrings[i])) {
                            fTrillParams = tmp;
                        }
                    }
                }
            }
        }
        
        virtual void declare(const char* k, const char* id)     // assumes that ui metadata are already parsed
        {		
            if (strcasecmp(k, "trill_settings") == 0) {
                vector<string> names;
                vector<string> values;
                if (parseMenuListMenu(id, names, values)) {
                    for (int i = 0; i < names.size(); i++) {
                        for (int j = 0; j < kNumInputPins; j++) {
                            if (strcasecmp(names[i].c_str(),pinNamesStrings[j] ) == 0) {
                                TrillWidget* curwidget = findTrillbyid(j);      // find the right widget
                                if (curwidget) {
                                    curwidget->setParameters(values[i].c_str()); 
                                }
                            }
                        }
                    }
                }
            } else if (strcasecmp(k, "trill_mappings") == 0) {
                vector<string> names;
                vector<string> values;
                if (parseMenuListMenu(id, names, values)) {
                   for (int i = 0; i<names.size();i++) {
                       if (names[i] == "BAR") {
                           initSensorWidgets(Trill::BAR, values[i]);
                       } else if(names[i] == "SQUARE") {
                           initSensorWidgets(Trill::SQUARE, values[i]);
                       } else if(names[i] == "CRAFT") {
                           initSensorWidgets(Trill::CRAFT, values[i]);
                       }
                   }                       
                }
#ifdef NVOICES    
            } else if (strcasecmp(k, "trill_keyboard") == 0) {
                vector<string> names;
                vector<string> values;
                if (parseMenuListMenu(id, names, values)) {
                    for (int i = 0; i<names.size(); i++) {
                        EInOutPin FoundPin = kNoPin;
                        for (int j = 0; j < kNumInputPins; j++) {
                            if (strstr(names[i].c_str(), pinNamesStrings[j])) {
                                FoundPin = (EInOutPin)j;
                                break;
                            }
                        }
                        if (FoundPin != kNoPin) {
                            TrillCraftWidget* newcraft = new TrillCraftWidget(FoundPin, 0, "Keyboard", 0, 0);
                            newcraft->setParameters(values[i].c_str());
                            newcraft->setMode("KEYBOARD");
                            fTrillTable.push_back(newcraft);
                        }
                    }
                }
#endif                
            }
        }
        
        // Initialize the sensors and affect there to the right widgets
        void initSensorWidgets(Trill::Device device, const string& mapping)
        {
            vector<string> names;
            vector<double> values;
            Trill* curSensor = NULL;
            bool affected = false;
            const char* tmpmapping = mapping.c_str();
            if (parseMenuList(tmpmapping, names, values)) {
                for (int i = 0; i < names.size(); i++) {
                    Trill::Device typedevice = Trill::probe(i2cBus, (uint8_t)values[i]);
                    if (typedevice == device) {                                             // is the right sensor type
                        curSensor = new Trill(i2cBus, device, (uint8_t)values[i]);
                        for (int j = 0; j < fTrillTable.size(); j++) {                       // find the right widgets
                            TrillWidget* CurWidget = fTrillTable[j];
                            if (CurWidget && device == CurWidget->getType() && strstr(pinNamesStrings[CurWidget->getBelaPin()], names[i].c_str())) {
                                affected = true;
                                CurWidget->setSensor(curSensor);
                            }
                        }
                        if (affected) {
                            fTouchSensors.push_back(curSensor);                             // preserve the sensor affected to the widget(s)
                        }
                        else if (curSensor) {                                                // delete if not affected
                            delete curSensor;
                        }
                    }
                    affected = false;
                    curSensor = NULL;
                }                
            }
        }
        
        int getNbTrill()
        {
           return fTrillTable.size(); 
        }
        
};

#endif // __FaustCommonInfrastructure__

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/

<<includeIntrinsic>>

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

/**************************************************************************************
  Bela render.cpp that calls FAUST generated code
***************************************************************************************/

#ifdef MIDICTRL
static bela_midi gMIDI;
static MidiUI* gMidiInterface = NULL;
#endif

#ifdef OSCCTRL
#define OSC_IP_ADDRESS  "192.168.7.1"
#define OSC_IN_PORT     5510
#define OSC_OUT_PORT    5511
static BelaOSCUI gOSCUI(OSC_IP_ADDRESS, OSC_IN_PORT, OSC_OUT_PORT);
#endif

#ifdef HTTPDGUI
static httpdUI* gHttpdInterface = NULL;
#endif

#ifdef SOUNDFILE
// Use bundle path
static SoundUI gSoundInterface(SoundUI::getBinaryPath());
#endif

static FAUSTFLOAT** gInputs = NULL;   // array of pointers to context->audioIn data
static FAUSTFLOAT** gOutputs = NULL;  // array of pointers to context->audioOut data

static BelaUI gControlUI;

const int DELAYTRILLLOOP = 5000;

// This is the auxilary task function which will read our Trill sensors loop
static void trillLoop(void*)
{
    while (!Bela_stopRequested())
    {
        // Read all Trill sensors
        gControlUI.updateSensors();
        
        // Put the process to sleep when finished
        usleep(DELAYTRILLLOOP);
    }
}

//*******************************************************************************

void Bela_userSettings(BelaInitSettings* settings)
{
    // Faust code needs non-interleaved data
    settings->uniformSampleRate = 1;
    settings->interleave = 0;
    settings->analogOutputsPersist = 0;
}

bool setup(BelaContext* context, void* userData)
{
    int nvoices = 0;
    bool midi_sync = false;
    mydsp* tmp_dsp = new mydsp();
    MidiMeta::analyse(tmp_dsp, midi_sync, nvoices);
    delete tmp_dsp;
    
    // Routing the stderr stream to a file (some code part in the mydsp_poly are too talkative and generate mode switch during the execution)
    freopen ("stderr_file.txt", "w", stderr);
    
    // Access deinterleaded inputs
    gInputs = new FAUSTFLOAT*[context->audioInChannels];
    for (unsigned int ch = 0; ch < context->audioInChannels; ch++) {
        gInputs[ch] = (float*)&context->audioIn[ch * context->audioFrames];
    }
    
    // Access deinterleaded outputs
    gOutputs = new FAUSTFLOAT*[context->audioOutChannels];
    for (unsigned int ch = 0; ch < context->audioOutChannels; ch++) {
        gOutputs[ch] = (float*)&context->audioOut[ch * context->audioFrames];
    }
    
    // Polyphonic with effect
#ifdef POLY2
    int group = 1;
    cout << "Started with " << nvoices << " voices" << endl;
    gDSP = new mydsp_poly(new mydsp(), nvoices, true, group);
    
#ifdef MIDICTRL
    if (midi_sync) {
        gDSP = new timed_dsp(new dsp_sequencer(gDSP, new effect()));
    } else {
        gDSP = new dsp_sequencer(gDSP, new effect());
    }
#else
    gDSP = new dsp_sequencer(gDSP, new effect());
#endif
    
#else
    int group = 1;
    
    if (nvoices > 0) {
        cout << "Started with " << nvoices << " voices" << endl;
        gDSP = new mydsp_poly(new mydsp(), nvoices, true, group);
        
#ifdef MIDICTRL
        if (midi_sync) {
            gDSP = new timed_dsp(gDSP);
        }
#endif
    } else {
#ifdef MIDICTRL
        if (midi_sync) {
            gDSP = new timed_dsp(new mydsp());
        } else {
            gDSP = new mydsp();
        }
#else
        gDSP = new mydsp();
#endif
    }
#endif
    
    if (gDSP == NULL) {
        cerr << "Unable to allocate Faust DSP object" << endl;
        return false;
    }
    
    gDSP->init(context->audioSampleRate);
    gDSP->buildUserInterface(&gControlUI);  // Maps Bela Analog/Digital IO, Trill sensors and Faust widgets
	gDSP->metadata(&gControlUI);            // Get the extra settings for Trill sensors
#ifdef HTTPDGUI
    gHttpdInterface = new httpdUI("Bela-UI", gDSP->getNumInputs(), gDSP->getNumOutputs(), 0, NULL);
    gDSP->buildUserInterface(gHttpdInterface);
    gHttpdInterface->run();
#endif /* HTTPD GUI */

#ifdef MIDICTRL
    gMidiInterface = new MidiUI(&gMIDI);
    gDSP->buildUserInterface(gMidiInterface);
    gMidiInterface->run();
#endif
    
// OSC
#ifdef OSCCTRL
    gDSP->buildUserInterface(&gOSCUI);
    gOSCUI.run();
#endif
    
#ifdef SOUNDFILE
    // SoundUI has to be dispatched on all internal voices
    gDSP->buildUserInterface(&gSoundInterface);
#endif
    // Setup the trill sensors only if needed
    if (gControlUI.getNbTrill() > 0) {
        Bela_runAuxiliaryTask(trillLoop);        
    }
    return true;
}

void render(BelaContext* context, void* userData)
{
    // Reads Bela pins and updates corresponding Faust Widgets zones
    gControlUI.update(context);
    // Synchronize all GUI controllers
    GUI::updateAllGuis();
    // Process Faust DSP
    gDSP->compute(context->audioFrames, gInputs, gOutputs);
}

void cleanup(BelaContext* context, void* userData)
{
#ifdef HTTPDGUI
    delete gHttpdInterface;
#endif /* HTTPDGUI */
    delete [] gInputs;
    delete [] gOutputs;
    delete gDSP;    
#ifdef MIDICTRL
    delete gMidiInterface;
#endif
}

/******************** END bela.cpp ****************/

