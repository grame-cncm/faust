#ifndef __VST_UI_H__
#define __VST_UI_H__

#include <audioeffectx.h>
#include <faust/gui/UI.h>

#ifdef DEBUG
#define TRACE(x) x
#else
#define TRACE(x)
#endif

//////////////////////////// VST UI ////////////////////////

class vstUIObject { /* superclass of all VST UI widgets */
    
protected:
    
    string fLabel;
    float* fZone;
	Meta metadata;
    
    float clip(float min, float max, float val) 
    {
        return (val < min) ? min : (val > max) ? max : val;
    }
    
    float normalize(float min, float max, float val) 
    { // VST parameters are normalized to the range [0;1] on the host
        val = min + val * (max - min);
        return (val < min) ? min : (val > max) ? max : val;
    }
    
public:		
	
    vstUIObject(const char* label, float* zone)
    : fLabel(label), fZone(zone), metadata()
	{}
    
    virtual ~vstUIObject()
	{}
    
    virtual void  GetName(char *text) {
		std::strcpy(text,fLabel.c_str());
	}
    
    virtual void  SetValue(double f) {
		*fZone = normalize(0.0f,1.0f,(float)f);
	}
    
    virtual void  SetValueNoNormalization(double f) {
		*fZone = clip(0.0f,1.0f,(float)f);
	}
    
    virtual float GetValue() {
		return *fZone;
	}
    
	virtual float GetValueNoNormalization() {
		return *fZone;
	}
    
    virtual void  GetDisplay(char *text){
		std::sprintf(text,"%f",*fZone);
	}
	
    virtual long  GetID() {	
		/* returns the sum of all the ASCII characters  contained in the 
         parameter's label */
        unsigned int i;
        long acc;
        for(i=0,acc = 0; i < fLabel.length(); i++) {
			acc += (fLabel.c_str())[i];
		}
        return acc;
    }
    
	const float* getZone() const {
		return fZone;
	}
}; // end of vstUIObject class

/*-------------------------------------------------------------------------*/
class vstToggleButton : public vstUIObject {
	
public:	
	
    vstToggleButton(const char* label, float* zone)
    : vstUIObject(label,zone) 
    {}
    
    virtual ~vstToggleButton() {}
    virtual float GetValue() {
		return *fZone;
	}
    
    virtual void SetValue(double f) {
		*fZone = (f>0.5f) ? 1.0f : 0.0f;
	}
    
	virtual void  GetDisplay(char *text) {
		(*fZone > 0.5f) ? std::strcpy(text,"ON") : std::strcpy(text,"OFF");
	}
};

/*--------------------------------------------------------------------------*/
class vstCheckButton : public vstUIObject {
	
public:
	
    vstCheckButton(const char* label, float* zone):vstUIObject(label,zone) {}	
    
    virtual ~vstCheckButton() {}
    
    virtual float GetValue() {
		return *fZone;
	}
    
    virtual void SetValue(double f) {*fZone = (f>0.5f)?1.0f:0.0f;}
    
    virtual void GetDisplay(char *text) {
		(*fZone>0.5f)? std::strcpy(text,"ON"): std::strcpy(text,"OFF");
	}
};

/*--------------------------------------------------------------------------*/
class vstButton : public vstUIObject {
	
public:
	
    vstButton(const char* label, float* zone)
    : vstUIObject(label,zone) 
    {}
    
    virtual ~vstButton() {}		
    virtual float GetValue() {return *fZone;}
    virtual void SetValue(double f) {*fZone = (f>0.5f)?1.0f:0.0f;}		
    virtual void  GetDisplay(char *text){(*fZone>0.5f)? std::strcpy(text,"ON"): std::strcpy(text,"OFF");}
};

#define MAX_PARAM_DISPLAY_PRECISION 6
/*--------------------------------------------------------------------------*/
class vstSlider : public vstUIObject{
    
private:
	
    float fInit;
    float fMin;
    float fMax;
    float fStep;
    int fPrecision;
	
public:	
	
    vstSlider(const char* label, float* zone, float init, float min, float max, float step)
    :vstUIObject(label,zone), fInit(init), fMin(min), fMax(max), fStep(step), fPrecision(0) {
        for (fPrecision = 0; fPrecision < MAX_PARAM_DISPLAY_PRECISION && step != floor(step); ++fPrecision, step *= 10.0) {;}
    }
    virtual ~vstSlider() {}	
    
    // The VST host calls GetValue() and expects a result in [0,1].
    // The VST host calls SetValue(f) with f in [0,1]. We convert to real units.
    // When we process MIDI controls, we call SetValueNoNormalization(f) with f in real units.
    virtual float GetValue() {
		return (*fZone-fMin)/(fMax-fMin); // normalize
	}
    
    virtual void SetValue(double f) {
		*fZone = normalize(fMin,fMax,(float)f); // denormalize
	}
    
    virtual void SetValueNoNormalization(double f) {
		*fZone = clip(fMin,fMax,(float)f); // raw
	}
    
	int getMinValue() const {
		return fMin;
	}
    
	int getMaxValue() const {
		return fMax;
	}
    
	int getStep() const {
		return fStep;
	}
    
    void GetDisplay(char *text) {
		if(fPrecision == 0) {
			std::sprintf(text, "%d", int(*fZone));
		} else {
			std::sprintf(text,"%.*f", fPrecision, *fZone);
        }
	}
    
};

/*--------------------------------------------------------------------------*/
class vstUI : public UI
{
    
private:
    
    bool fStopped;
    
    vector<vstUIObject*> fUITable;
	map<const float*, Meta*> m_controlMetadataMap;
	
public:
    
    int freqIndex; // note frequency
    int gainIndex; // note velocity
    int gateIndex; // note on/off
    
	// can be used for effects such as portamento where
	// we have to know the previous note
	int prevFreqIndex;
    
	// pitchbend wheel
	int pitchbendIndex;
    
    // Constructor
    vstUI()
    : fStopped(false), freqIndex(-1), gainIndex(-1), gateIndex(-1)
	{ }
    
    // Destructor
    virtual ~vstUI() 
    {
		for (vector<vstUIObject*>::iterator iter = fUITable.begin(); 
             iter != fUITable.end(); iter++) {
			delete *iter;
		}
        
		for (map<const float*, Meta*>::iterator iter = m_controlMetadataMap.begin();
             iter != m_controlMetadataMap.end(); ++iter)
		{
			delete iter->second;
		}
    } // end of destructor
    
    void stop()      { fStopped = true; }
    bool stopped() { return fStopped; }
    
    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* value) {
		map<const float*, Meta*>::iterator iter = m_controlMetadataMap.find(zone);
		if (iter == m_controlMetadataMap.end()) {
			// if Meta for zone doesn't exist, create it now
			pair<const float*, Meta*> entry(zone, new Meta());
			pair< map<const float*, Meta*>::iterator, bool> result = m_controlMetadataMap.insert(entry);
			if (!result.second) {
				TRACE(fprintf(stderr, "Failed adding metadata %s:%s\n", key, value));
				return;
			}
            
			iter = result.first;
		}
		
		iter->second->declare(key, value);	
    } // end of declare
    
	/*
     Return metadata for control (such as style, unit, etc...).
     */
	const char* getControlMetadata(int index, const char* key, const char* defaultString)
	{
		if (index < 0 || index > (int)fUITable.size()) {
			TRACE(fprintf(stderr, "Illegal index (%d) accessed by getControlMetadata\n",
                          index));
			return defaultString;
		}
        
		const	float* zone = fUITable[index]->getZone();
		map<const float*, Meta*>::iterator iter = m_controlMetadataMap.find(zone);
		if (iter == m_controlMetadataMap.end()) {
			TRACE(fprintf(stderr, "Metadata for control %d not found\n", index));
			return defaultString;
		}
        
		return iter->second->get(key, defaultString);
	} // end of getControlMetadata
    
	void setAny(int anyIndex, float val, const char *str) {
		if (anyIndex < 0) {
			// On the Receptor, and perhaps other hosts, output to stderr is 
			// logged in a file.
			TRACE(fprintf(stderr,"*** Faust vsti: %sIndex = %d never set!\n",
                          str,anyIndex) );
			return;
		}
        
		if (anyIndex >= (int)fUITable.size()) {
			TRACE(fprintf(stderr,"*** Faust vsti: %sIndex = %d too large!\n",
                          str,anyIndex));
			return;
		}
		TRACE(fprintf(stderr,"*** Faust vsti: Setting %sIndex = %d to %f\n",
                      str,anyIndex,val));
		fUITable[anyIndex]->SetValueNoNormalization(val);
	} // end of setAny
    
    
	float getAny(int anyIndex, const char* str) {
		if (anyIndex < 0) {
			TRACE(fprintf(stderr, "=== Faust VSTi: %sIndex = %d never set!\n",
                           str, anyIndex));
			return -1;
		}
        
		return fUITable[anyIndex]->GetValueNoNormalization();
	} // end of getAny
    
	void setFreq(float val) {
		setAny(freqIndex, val, "freq");
    }
    
	float getFreq( void ) {
		return getAny(freqIndex, "freq");	
	}
    
    void setGate(float val) {
        setAny(gateIndex, val, "gate");
    }
	
    void setGain(float val) {
        setAny(gainIndex, val, "gain");
    }
    
	void setPrevFreq(float val) {
		setAny(prevFreqIndex, val, "prevfreq");
	}
    
	void setPitchBend(float val) {
		setAny(pitchbendIndex, val, "pitchbend");
	}
    
    bool ckAnyMatch(const char* label, const char* indexName, int *index) {
        if (0 == strcmp(label,indexName)) { 
            TRACE( fprintf(stderr,"=== Faust vsti: label '%s' matches '%s'\n",label,indexName) );
            *index = fUITable.size() - 1; 
            return true;
        }
        return false;
    }
    
    void ckAllMatches(const char* label) {
        ckAnyMatch(label,"gain",&gainIndex);
        ckAnyMatch(label,"gate",&gateIndex);
        ckAnyMatch(label,"freq",&freqIndex);
		ckAnyMatch(label,"prevfreq", &prevFreqIndex);
		ckAnyMatch(label,"pitchbend", &pitchbendIndex);
    }
    
    void addButton(const char* label, float* zone) {
        vstButton* theButton = new vstButton(label, zone);
        fUITable.push_back(theButton);
        TRACE( fprintf(stderr,"=== Faust vsti: Adding Button with label '%s'\n",label) );
        ckAnyMatch(label,"gate",&gateIndex);
    }
    
	void addToggleButton(const char* label, float* zone) {
		fUITable.push_back(new vstToggleButton(label, zone));
	}
    
    void addCheckButton(const char* label, float* zone) {
		fUITable.push_back(new vstCheckButton(label, zone));
    }
    
    void addVerticalSlider(const char* label, float* zone, float init, 
                           float min, float max, float step) 
    { 	
		vstSlider* theSlider = new vstSlider(label, zone, init, min, max, step);
		fUITable.push_back(theSlider);
		TRACE( fprintf(stderr,"=== Faust vsti: Adding VSlider (HSlider) "
                       "with label '%s'\n",label) );
		ckAllMatches(label);
    }
	
    void addHorizontalSlider(const char* label, float* zone, float init, 
                             float min, float max, float step) 
    {
		vstSlider* theSlider = new vstSlider(label, zone, init, min, max, step);
		fUITable.push_back(theSlider);
		TRACE( fprintf(stderr,"=== Faust vsti: Adding HSlider with label '%s'\n",label) );
		ckAllMatches(label);
    }
    
    void addNumEntry(const char* label, float* zone, float init, float min, 
                     float max, float step)
    { 
		/* Number entries converted to horizontal sliders */
		vstSlider* theSlider = new vstSlider(label, zone, init, min, max, step);
        fUITable.push_back(theSlider);
        TRACE( fprintf(stderr,"=== Faust vsti: Adding NumEntry (HSlider) with "
                       "label '%s'\n",label) );
		ckAllMatches(label);
    }
    
	void openFrameBox(const char* label) {}
	void openTabBox(const char* label) {}
    void openHorizontalBox(const char* label) {}
    void openVerticalBox(const char* label) {}
    void closeBox() {}
    
    void  SetValue(VstInt32 index, double f) {
		assert(index < (VstInt32)fUITable.size()); 
		fUITable[index]->SetValue(f);
	}
    
    float GetValue(VstInt32 index) {
		assert(index < (VstInt32)fUITable.size()); 
		return fUITable[index]->GetValue();
	}
    
    void  GetDisplay(VstInt32 index, char *text) {
		assert(index < (VstInt32)fUITable.size()); 
		fUITable[index]->GetDisplay(text);
    }
    
    void  GetName(VstInt32 index, char *text) {
        assert(index < (VstInt32)fUITable.size()); 
		fUITable[index]->GetName(text);
    }
    
    long GetNumParams() {
        return fUITable.size();
    }
    
    /* Creates a (unique?)id by summing all the parameter's labels, 
     * then wrapping it in the range [0;maxNumberOfId] and adding 
     * this number to the offset made by the Four Character ID: 'FAUS'
     */
    long makeID() {   
        const long maxNumberOfId = 128;
        long baseid = 'FAUS';
        long id=0;
        
        for(int i=0;i<(int)fUITable.size();i++) {
			id += fUITable[i]->GetID();
		}
        
		return baseid + id % maxNumberOfId;
    }
    
    // To be implemented
    void addNumDisplay(const char* label, float* zone, int precision) {}
    void addTextDisplay(const char* label, float* zone, char* names[], 
                        float min, float max){}
    void addHorizontalBargraph(const char* label, float* zone, float min, 
                               float max){}
    void addVerticalBargraph(const char* label, float* zone, float min, 
                             float max){}
}; // end of vstUI class

#endif
