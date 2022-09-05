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
    usage : addin Meta data in UI widget of the Faust Code
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
		
		virtual bool setParameters(const char* Parameters)
		{
			return true;
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
        
        virtual EInOutPin getBelaPin() {
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
            fZone = z;  // zone
            fLabel = l; // label
            fMin = lo;    // minimal value
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
		
		virtual ~TrillWidget()
        {}
        
        void setSensor(Trill* nSensor)
        {
            if (nSensor) sensor = nSensor;
        }
		
		virtual bool setParameters(const char* Parameters)
		{
			return true;
		}

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

};

/**************************************************************************************
 
 TrillCraftWidget : object used by BelaUI to ensures the connection between a Trill Craft sensors values
 and a Faust widget.
 
 ***************************************************************************************/

class TrillCraftWidget : public TrillWidget
{
	 protected:
    
		int lopin;
		int hipin;
		string mode;

     public:
     
        TrillCraftWidget():TrillWidget()
        {
            sensor = NULL;
            type = Trill::CRAFT;
			lopin = -1;
			hipin = -1;
			mode = "PIN";
        }

        TrillCraftWidget(const TrillCraftWidget& w):TrillWidget((TrillWidget)w)
        {
            sensor = NULL;
            type = Trill::CRAFT;
			lopin = -1;
			hipin = -1;
			mode = "PIN";
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
        }
		
        virtual ~TrillCraftWidget()
        {}
		
		virtual bool setParameters(const char* Parameters)
		{
			// take the parameters
			if (Parameters)
			{
                if (parseWord(Parameters, "PIN")) {
                    mode = "PIN";
                } else if (parseWord(Parameters, "UP")) {
                    mode = "UP";
                } else if (parseWord(Parameters, "DOWN")) {
                    mode = "DOWN";
                }
			}
			double tmpval = 0.;
            if (Parameters && parseDouble(Parameters,tmpval)) {
                lopin = (int)tmpval;
            } else {
                lopin = -1;
            }
            if (Parameters && parseChar(Parameters,'-') && parseDouble(Parameters,tmpval)) {
                hipin = (int)tmpval;
            } else {
                hipin = -1;
            }
			return true;
		}
		
		virtual void update(BelaContext* context)
        {
			if (sensor && lopin >= 0)
			{
			    float val = -1.f;
				if (mode == "PIN")
				{
					val = sensor->rawData[lopin];
					*fZone = fMin + fRange * val;
				}
				else if (mode == "UP")
				{
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
				else if (mode == "DOWN")
				{
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
				}
			}
		}
		
		void setMode(const string& mo) { mode = mo; }
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
// max of 8 BAR sensors with 3 parameters (Position,Pressure,Touch), 8 SQUARE sensors with 4 parameters (Position X, Position Y, Pressure, Touch), 8 CRAFT sensors with 1 parameter
#define MAXTRILLWIDGETS 64

class BelaUI : public GenericUI
{
    
    private:
        
        int fIndex;                                 // number of BelaWidgets collected so far
        EInOutPin fBelaPin;                         // current pin id
        BelaWidget fTable[MAXBELAWIDGETS];          // list of BelaWidgets
        
       
        EInOutPin fTrillPin;                        // current trill pin id
        vector<TrillWidget*> fTrillTable;           // list of TrillWidget
		const char* fTrillParams;
        
        
        // check if the widget is linked to a Bela parameter and, if so, add the corresponding BelaWidget
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
			fTrillParams=NULL;
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
		}
        
        // should be called before compute() to update widget's zones registered as Bela parameters
        void update(BelaContext* context)
        {
            for (int i = 0; i < fIndex; i++) {
                fTable[i].update(context);
            }
            for (size_t i = 0; i < fTrillTable.size(); i++) {
                fTrillTable[i]->update(context);
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
						if (parseWord(tmp, pinNamesStrings[i]))
							fTrillParams = tmp;
                    }
                }
            }
			
        }
        
        void setTrill(Trill::Device device,Trill* sensor,int idx)
        {
            EInOutPin CurTrill;
            switch(device) {
                case Trill::BAR:
                    CurTrill = (EInOutPin) (kBAR_POS_0+idx*3);
                    for (size_t i = 0; i < fTrillTable.size(); i++)
                    {
                        if ((fTrillTable[i]->getBelaPin() == CurTrill
                             || fTrillTable[i]->getBelaPin() == (CurTrill+1)
                             || fTrillTable[i]->getBelaPin() == (CurTrill+2)) && fTrillTable[i]->getType() == device)
                            fTrillTable[i]->setSensor(sensor);
                    }
                    break;
                
                case Trill::SQUARE:
                    CurTrill = (EInOutPin) (kSQUARE_XPOS_0+idx*4);
                    for (size_t i = 0; i < fTrillTable.size(); i++)
                    {
                        if ((fTrillTable[i]->getBelaPin() == CurTrill
                             || fTrillTable[i]->getBelaPin() == (CurTrill+1)
                             || fTrillTable[i]->getBelaPin() == (CurTrill+2)
                             || fTrillTable[i]->getBelaPin() == (CurTrill+3)) && fTrillTable[i]->getType() == device)
                            fTrillTable[i]->setSensor(sensor);
                    }
                    break;
                case Trill::CRAFT:
					CurTrill = (EInOutPin) (kCRAFT_0+idx);
					for (size_t i = 0; i < fTrillTable.size(); i++)
                    {
                        if (fTrillTable[i]->getBelaPin() == CurTrill && fTrillTable[i]->getType() == device)
                            fTrillTable[i]->setSensor(sensor);
                    }
					break;
                default:
                    break;
            };
            
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
static dsp* gDSP = NULL;


// Trill implementation ************************************************************

// Trill adress routing
const uint8_t TrillBarAdress[] = {0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27};
const uint8_t TrillSquareAdress[] = {0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F};
const uint8_t TrillCraftAdress[] = {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37};

static vector<Trill*> gTouchSensors;

const int DELAYTRILLLOOP = 5000;

// Return the sensor index corresponding to the i2c address in input
static int trillAdress2index(uint8_t i2cadress)
{
    int cnt = sizeof(TrillBarAdress);
    for (int i = 0; i < cnt; i++)
    {
        if (TrillBarAdress[i] == i2cadress)
            return i;
    }
    cnt = sizeof(TrillSquareAdress);
    for (int i = 0; i < cnt;i++)
    {
        if (TrillSquareAdress[i] == i2cadress)
            return i;
    }
	cnt = sizeof(TrillCraftAdress);
    for (int i = 0; i < cnt;i++)
    {
        if (TrillCraftAdress[i] == i2cadress)
            return i;
    }
    return -1;
}

// This is the auxilary task function which will read our Trill sensors loop
static void trillLoop(void*)
{
    while (!Bela_stopRequested())
    {
        // Read all Trill sensors
        for (size_t n = 0; n < gTouchSensors.size(); ++n)
        {
            Trill* t = gTouchSensors[n];
            t->readI2C();
        }
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
    gDSP->buildUserInterface(&gControlUI); // Maps Bela Analog/Digital IO and Faust widgets
#ifdef HTTPDGUI
    gHttpdInterface = new httpdUI("Bela-UI", gDSP->getNumInputs(), gDSP->getNumOutputs(), 0, NULL);
    gDSP->buildUserInterface(gHttpdInterface);
    gHttpdInterface->run();
#endif /* HTTPDGUI */

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
    
    // Trill sensors initialisation
    unsigned int i2cBus = 1;
    for (uint8_t addr = 0x20; addr <= 0x50; ++addr)
    {
        Trill::Device device = Trill::probe(i2cBus, addr);
        if (device != Trill::NONE /*&& Trill::CRAFT != device*/)
        {
            Trill* newsensor = new Trill(i2cBus, device, addr);
            gTouchSensors.push_back(newsensor);
            //gTouchSensors.back()->printDetails();
            int trillidx = trillAdress2index(addr);
            gControlUI.setTrill(device, newsensor, trillidx);
			
			// config of craft (must move in another place)
			if (device == Trill::CRAFT) {
				newsensor->setPrescaler(4);
				newsensor->setNoiseThreshold(0.12);
			}
        }
    }
    
    // Setup the loop only if needed
    if (gTouchSensors.size() > 0) {
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

    for (auto t : gTouchSensors) {
        delete t;
    }
}

/******************** END bela.cpp ****************/

