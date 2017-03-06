/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
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
 
#ifndef MetaData_UI_H
#define MetaData_UI_H

#include <map>
#include <set>
#include <string>
#include <assert.h>

#include "faust/gui/SimpleParser.h"

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

static inline bool startWith(const std::string& str, const std::string& prefix)
{
    return (str.substr(0, prefix.size()) == prefix);
}

/**
 * Convert a dB value into a scale between 0 and 1 (following IEC standard ?)
 */
static inline FAUSTFLOAT dB2Scale(FAUSTFLOAT dB)
{
    FAUSTFLOAT scale = FAUSTFLOAT(1.0);
    
    /*if (dB < -70.0f)
     scale = 0.0f;
     else*/
    if (dB < FAUSTFLOAT(-60.0))
         scale = (dB + FAUSTFLOAT(70.0)) * FAUSTFLOAT(0.0025);
    else if (dB < FAUSTFLOAT(-50.0))
         scale = (dB + FAUSTFLOAT(60.0)) * FAUSTFLOAT(0.005) + FAUSTFLOAT(0.025);
    else if (dB < FAUSTFLOAT(-40.0))
         scale = (dB + FAUSTFLOAT(50.0)) * FAUSTFLOAT(0.0075) + FAUSTFLOAT(0.075);
    else if (dB < FAUSTFLOAT(-30.0))
         scale = (dB + FAUSTFLOAT(40.0)) * FAUSTFLOAT(0.015) + FAUSTFLOAT(0.15);
    else if (dB < FAUSTFLOAT(-20.0))
         scale = (dB + FAUSTFLOAT(30.0)) * FAUSTFLOAT(0.02) + FAUSTFLOAT(0.3);
    else if (dB < FAUSTFLOAT(-0.001) || dB > FAUSTFLOAT(0.001))  /* if (dB < 0.0) */
         scale = (dB + FAUSTFLOAT(20.0)) * FAUSTFLOAT(0.025) + FAUSTFLOAT(0.5);
    
    return scale;
}

/*******************************************************************************
 * MetaDataUI : Common class for MetaData handling
 ******************************************************************************/

//============================= BEGIN GROUP LABEL METADATA===========================
// Unlike widget's label, metadata inside group's label are not extracted directly by
// the Faust compiler. Therefore they must be extracted within the architecture file
//-----------------------------------------------------------------------------------

class MetaDataUI {
    
protected:
    
    std::string                         fGroupTooltip;
    std::map<FAUSTFLOAT*, FAUSTFLOAT>   fGuiSize;            // map widget zone with widget size coef
    std::map<FAUSTFLOAT*, std::string>  fTooltip;            // map widget zone with tooltip strings
    std::map<FAUSTFLOAT*, std::string>  fUnit;               // map widget zone to unit string (i.e. "dB")
    std::map<FAUSTFLOAT*, std::string>  fRadioDescription;   // map zone to {'low':440; ...; 'hi':1000.0}
    std::map<FAUSTFLOAT*, std::string>  fMenuDescription;    // map zone to {'low':440; ...; 'hi':1000.0}
    std::set<FAUSTFLOAT*>               fKnobSet;            // set of widget zone to be knobs
    std::set<FAUSTFLOAT*>               fLedSet;             // set of widget zone to be LEDs
    std::set<FAUSTFLOAT*>               fNumSet;             // set of widget zone to be numerical bargraphs
    std::set<FAUSTFLOAT*>               fLogSet;             // set of widget zone having a log UI scale
    std::set<FAUSTFLOAT*>               fExpSet;             // set of widget zone having an exp UI scale
    
    void clearMetadata()
    {
        fGuiSize.clear();
        fTooltip.clear();
        fUnit.clear();
        fRadioDescription.clear();
        fMenuDescription.clear();
        fKnobSet.clear();
        fLedSet.clear();
        fNumSet.clear();
        fLogSet.clear();
        fExpSet.clear();
    }
    
    bool isKnob(FAUSTFLOAT* zone)
    {
        return fKnobSet.count(zone) > 0;
    }
    
    bool isRadio(FAUSTFLOAT* zone)
    {
        return fRadioDescription.count(zone) > 0;
    }
    
    bool isMenu(FAUSTFLOAT* zone)
    {
        return fMenuDescription.count(zone) > 0;
    }
    
    bool isLed(FAUSTFLOAT* zone)
    {
        return fLedSet.count(zone) > 0;
    }
    
    bool isNumerical(FAUSTFLOAT* zone)
    {
        return fNumSet.count(zone) > 0;
    }
    
    /**
    * rmWhiteSpaces(): Remove the leading and trailing white spaces of a string
    * (but not those in the middle of the string)
    */
    std::string rmWhiteSpaces(const std::string& s)
    {
        size_t i = s.find_first_not_of(" \t");
        size_t j = s.find_last_not_of(" \t");
        if ((i != std::string::npos) && (j != std::string::npos)) {
            return s.substr(i, 1+j-i);
        } else {
            return "";
        }
    }
  
    /**
     * Extracts metdata from a label : 'vol [unit: dB]' -> 'vol' + metadata(unit=dB)
     */
    void extractMetadata(const std::string& fulllabel, std::string& label, std::map<std::string, std::string>& metadata)
    {
        enum {kLabel, kEscape1, kEscape2, kEscape3, kKey, kValue};
        int state = kLabel; int deep = 0;
        std::string key, value;
        
        for (unsigned int i = 0; i < fulllabel.size(); i++) {
            char c = fulllabel[i];
            switch (state) {
                case kLabel :
                    assert(deep == 0);
                    switch (c) {
                        case '\\' : state = kEscape1; break;
                        case '[' : state = kKey; deep++; break;
                        default : label += c;
                    }
                    break;
                    
                case kEscape1:
                    label += c;
                    state = kLabel;
                    break;
                    
                case kEscape2:
                    key += c;
                    state = kKey;
                    break;
                    
                case kEscape3:
                    value += c;
                    state = kValue;
                    break;
                    
                case kKey:
                    assert(deep > 0);
                    switch (c) {
                        case '\\':
                            state = kEscape2;
                            break;
                            
                        case '[':
                            deep++;
                            key += c;
                            break;
                            
                        case ':':
                        if (deep == 1) {
                            state = kValue;
                        } else {
                            key += c;
                        }
                            break;
                        case ']':
                            deep--;
                            if (deep < 1) {
                                metadata[rmWhiteSpaces(key)] = "";
                                state = kLabel;
                                key="";
                                value="";
                            } else {
                                key += c;
                            }
                            break;
                        default : key += c;
                    }
                    break;
                    
                case kValue:
                    assert(deep > 0);
                    switch (c) {
                        case '\\':
                            state = kEscape3;
                            break;
                            
                        case '[':
                            deep++;
                            value += c;
                            break;
                            
                        case ']':
                            deep--;
                            if (deep < 1) {
                                metadata[rmWhiteSpaces(key)] = rmWhiteSpaces(value);
                                state = kLabel;
                                key = "";
                                value = "";
                            } else {
                                value += c;
                            }
                            break;
                        default : value += c;
                    }
                    break;
                    
                default:
                    std::cerr << "ERROR unrecognized state " << state << std::endl;
            }
        }
        label = rmWhiteSpaces(label);
    }
   
    /**
     * Format tooltip string by replacing some white spaces by
     * return characters so that line width doesn't exceed n.
     * Limitation : long words exceeding n are not cut
     */
    std::string formatTooltip(int n, const std::string& tt)
    {
        std::string  ss = tt;	// ss string we are going to format
        int	lws = 0;            // last white space encountered
        int lri = 0;            // last return inserted
        for (int i = 0; i < (int)tt.size(); i++) {
            if (tt[i] == ' ') lws = i;
            if (((i-lri) >= n) && (lws > lri)) {
                // insert return here
                ss[lws] = '\n';
                lri = lws;
            }
        }
        return ss;
    }
    
public:
    
    virtual ~MetaDataUI()
    {}
    
    enum Scale {
        kLin,
        kLog,
        kExp
    };
    
    Scale getScale(FAUSTFLOAT* zone)
    {
        if (fLogSet.count(zone) > 0) return kLog;
        if (fExpSet.count(zone) > 0) return kExp;
        return kLin;
    }
    
    /**
     * Analyses the widget zone metadata declarations and takes appropriate actions
     */
    void declare(FAUSTFLOAT* zone, const char* key, const char* value)
    {
        if (zone == 0) {
            // special zone 0 means group metadata
            if (strcmp(key,"tooltip") == 0) {
                // only group tooltip are currently implemented
                fGroupTooltip = formatTooltip(30, value);
            }
        } else {
            if (strcmp(key,"size") == 0) {
                fGuiSize[zone] = atof(value);
            }
            else if (strcmp(key,"tooltip") == 0) {
                fTooltip[zone] = formatTooltip(30, value);
            }
            else if (strcmp(key,"unit") == 0) {
                fUnit[zone] = value ;
            }
            else if (strcmp(key,"scale") == 0) {
                if (strcmp(value,"log") == 0) {
                    fLogSet.insert(zone);
                } else if (strcmp(value,"exp") == 0) {
                    fExpSet.insert(zone);
                }
            }
            else if (strcmp(key,"style") == 0) {
                if (strcmp(value,"knob") == 0) {
                    fKnobSet.insert(zone);
                } else if (strcmp(value,"led") == 0) {
                    fLedSet.insert(zone);
                } else if (strcmp(value,"numerical") == 0) {
                    fNumSet.insert(zone);
                } else {
                    const char* p = value;
                    if (parseWord(p, "radio")) {
                        fRadioDescription[zone] = std::string(p);
                    } else if (parseWord(p, "menu")) {
                        fMenuDescription[zone] = std::string(p);
                    }
                }
            }
        }
    }
    
};

#endif
