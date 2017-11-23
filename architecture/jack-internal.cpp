/************************************************************************

	IMPORTANT NOTE : this file contains two clearly delimited sections : 
	the ARCHITECTURE section (in two parts) and the USER section. Each section 
	is governed by its own copyright and license. Please check individually 
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <vector>
#include <stack>
#include <string>
#include <map>
#include <list>
#include <iostream> 
#include <assert.h> 

#include <libgen.h>
#include <jack/jack.h>
#include <jack/jslist.h>

using namespace std;

// On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
// flags to avoid costly denormals
#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS 
#endif

struct Meta : map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key]=value; }
};

// abs is now predefined
//template<typename T> T abs (T a)			{ return (a<T(0)) ? -a : a; }

inline int		lsr (int x, int n)			{ return int(((unsigned int)x) >> n); }

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }
//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((size_t)(calloc((nmemb*size)+15,sizeof(char)))+15 & ~15); }

<<includeIntrinsic>>

/******************************************************************************
*******************************************************************************

								GRAPHIC USER INTERFACE (v2)
								  abstract interfaces

*******************************************************************************
*******************************************************************************/

using namespace std;

struct uiItem;
typedef void (*uiCallback)(float val, void* data);

/**
 * Graphic User Interface : abstract definition
 */

class UI 
{
	typedef list<uiItem*> clist;
	typedef map<float*, clist*> zmap;
	
 private:
 	static list<UI*>	fGuiList;
	zmap				fZoneMap;
	bool				fStopped;
	
 public:
		
	UI() : fStopped(false) {	
		fGuiList.push_back(this);
	}
	
	virtual ~UI() {
		// suppression de this dans fGuiList
	}

	// -- zone management
	
	void registerZone(float* z, uiItem* c)
	{
		if (fZoneMap.find(z) == fZoneMap.end()) fZoneMap[z] = new clist();
		fZoneMap[z]->push_back(c);
	} 	
	
	void updateAllZones();
	
	void updateZone(float* z);
	
	static void updateAllGuis()
	{
		list<UI*>::iterator g;
		for (g = fGuiList.begin(); g != fGuiList.end(); g++) {
			(*g)->updateAllZones();
		}
	}
	
	// -- active widgets
	
	virtual void addButton(const char* label, float* zone) = 0;
	virtual void addToggleButton(const char* label, float* zone) = 0;
	virtual void addCheckButton(const char* label, float* zone) = 0;
	virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) = 0;
	
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
    
	// -- passive widgets
	
	virtual void addNumDisplay(const char* label, float* zone, int precision) = 0;
	virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max) = 0;
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) = 0;
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) = 0;
	
	void addCallback(float* zone, uiCallback foo, void* data);
	
	// -- widget's layouts
	
	virtual void openFrameBox(const char* label) = 0;
	virtual void openTabBox(const char* label) = 0;
	virtual void openHorizontalBox(const char* label) = 0;
	virtual void openVerticalBox(const char* label) = 0;
	virtual void closeBox() = 0;

    virtual void declare(float* zone, const char* key, const char* value) {}
};

class OSCUI : public UI 
{
 public:
		
	OSCUI() : UI() 
    {}
	
	virtual ~OSCUI() {
		// suppression de this dans fGuiList
	}

	
	// -- active widgets
	
	virtual void addButton(const char* label, float* zone) {}
	virtual void addToggleButton(const char* label, float* zone) {}
	virtual void addCheckButton(const char* label, float* zone) {}
	virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) {}
	virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) {}
	virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) {}
	
	// -- passive widgets
	
	virtual void addNumDisplay(const char* label, float* zone, int precision) {}
	virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max) {}
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) {}
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) {}
	
	void addCallback(float* zone, uiCallback foo, void* data);
	
	// -- widget's layouts
	
	virtual void openFrameBox(const char* label) {}
	virtual void openTabBox(const char* label) {}
	virtual void openHorizontalBox(const char* label) {}
	virtual void openVerticalBox(const char* label) {}
	virtual void closeBox() {}

    virtual void declare(float* zone, const char* key, const char* value) {}
};

list<UI*> UI::fGuiList;

/**
 * User Interface Item: abstract definition
 */

class uiItem
{
  protected :
		  
	UI*		fGUI;
	float*	fZone;
	float	fCache;
	
	uiItem (UI* ui, float* zone) : fGUI(ui), fZone(zone), fCache(-123456.654321) 
	{ 
		ui->registerZone(zone, this); 
	}	
	
  public :

	virtual ~uiItem() {}
	
	void modifyZone(float v) 	
	{ 
		fCache = v;
		if (*fZone != v) {
			*fZone = v;
			fGUI->updateZone(fZone);
		}
	}
		  	
	float			cache()			{ return fCache; }
	virtual void 	reflectZone() 	= 0;	
};

/**
 * Callback Item
 */

struct uiCallbackItem : public uiItem
{
	uiCallback	fCallback;
	void*		fData;
	
	uiCallbackItem(UI* ui, float* zone, uiCallback foo, void* data) 
			: uiItem(ui, zone), fCallback(foo), fData(data) {}
	
	virtual void 	reflectZone() {		
		float 	v = *fZone;
		fCache = v; 
		fCallback(v, fData);	
	}
};

/**
 * Update all user items reflecting zone z
 */

inline void UI::updateZone(float* z)
{
	float 	v = *z;
	clist* 	l = fZoneMap[z];
	for (clist::iterator c = l->begin(); c != l->end(); c++) {
		if ((*c)->cache() != v) (*c)->reflectZone();
	}
}

/**
 * Update all user items not up to date
 */

inline void UI::updateAllZones()
{
	for (zmap::iterator m = fZoneMap.begin(); m != fZoneMap.end(); m++) {
		float* 	z = m->first;
		clist*	l = m->second;
		float	v = *z;
		for (clist::iterator c = l->begin(); c != l->end(); c++) {
			if ((*c)->cache() != v) (*c)->reflectZone();
		}
	}
}

inline void UI::addCallback(float* zone, uiCallback foo, void* data) 
{ 
	new uiCallbackItem(this, zone, foo, data); 
};		

//----------------------------------------------------------------
//  definition du processeur de signal
//----------------------------------------------------------------
			
class dsp {
 protected:
	int fSamplingFreq;
 public:
	dsp() {}
	virtual ~dsp() {}
	
	virtual int getNumInputs() 										= 0;
	virtual int getNumOutputs() 									= 0;
	virtual void buildUserInterface(UI* interface) 					= 0;
	virtual void init(int samplingRate) 							= 0;
 	virtual void compute(int len, float** inputs, float** outputs) 	= 0;
 	virtual void conclude() 										{}
};

		
/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/
		
<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/
					

/******************************************************************************
*******************************************************************************

							JACK AUDIO INTERFACE

*******************************************************************************
*******************************************************************************/

#define JACK_DRIVER_NAME_MAX          15
#define JACK_DRIVER_PARAM_NAME_MAX    15
#define JACK_DRIVER_PARAM_STRING_MAX  63
#define JACK_DRIVER_PARAM_DESC        255
#define JACK_PATH_MAX                 511

/** Driver parameter types */
typedef enum
{
    JackDriverParamInt = 1,
    JackDriverParamUInt,
    JackDriverParamChar,
    JackDriverParamString,
    JackDriverParamBool
} jack_driver_param_type_t;

/** Driver parameter value */
typedef union
{
    uint32_t ui;
    int32_t i;
    char c;
    char str[JACK_DRIVER_PARAM_STRING_MAX + 1];
} jack_driver_param_value_t;


/** A driver parameter descriptor */
typedef struct {
    char name[JACK_DRIVER_NAME_MAX + 1]; /**< The parameter's name */
    char character;                    /**< The parameter's character (for getopt, etc) */
    jack_driver_param_type_t type;     /**< The parameter's type */
    jack_driver_param_value_t value;   /**< The parameter's (default) value */
    char short_desc[64];               /**< A short (~30 chars) description for the user */
    char long_desc[1024];              /**< A longer description for the user */
}
jack_driver_param_desc_t;

/** A driver parameter */
typedef struct {
    char character;
    jack_driver_param_value_t value;
}
jack_driver_param_t;

/** A struct for describing a jack driver */
typedef struct {
    char name[JACK_DRIVER_NAME_MAX + 1];      /**< The driver's canonical name */
    char desc[JACK_DRIVER_PARAM_DESC + 1];    /**< The driver's extended description */
    char file[JACK_PATH_MAX + 1];             /**< The filename of the driver's shared object file */
    uint32_t nparams;                         /**< The number of parameters the driver has */
    jack_driver_param_desc_t * params;        /**< An array of parameter descriptors */
}
jack_driver_desc_t;

// class JackArgParser ***************************************************
class  JackArgParser
{
    private:

        std::string fArgString;
        int fArgc;
        std::vector<std::string> fArgv;

    public:

        JackArgParser (const char* arg);
        ~JackArgParser();
        std::string GetArgString();
        int GetNumArgv();
        int GetArgc();
        int GetArgv (std::vector<std::string>& argv);
        int GetArgv (char** argv);
        void DeleteArgv (const char** argv);
        void ParseParams (jack_driver_desc_t* desc, JSList** param_list);
        void FreeParams (JSList* param_list);
};

JackArgParser::JackArgParser (const char* arg)
{
    printf ("JackArgParser::JackArgParser, arg_string : '%s' \n", arg);

    fArgc = 0;
    //if empty string
    if (strlen(arg) == 0)
        return;
    fArgString = string(arg);
    //else parse the arg string
    const size_t arg_len = fArgString.length();
    unsigned int i = 0;
    size_t pos = 0;
    size_t start = 0;
    size_t copy_start = 0;
    size_t copy_length = 0;
    //we need a 'space terminated' string
    fArgString += " ";
    //first fill a vector with args
    do {
        //find the first non-space character from the actual position
        start = fArgString.find_first_not_of (' ', start);
        //get the next quote or space position
        pos = fArgString.find_first_of (" \"" , start);
        //no more quotes or spaces, consider the end of the string
        if (pos == string::npos)
            pos = arg_len;
        //if double quote
        if (fArgString[pos] == '\"') {
            //first character : copy the substring
            if (pos == start) {
                copy_start = start + 1;
                pos = fArgString.find ('\"', ++pos);
                copy_length = pos - copy_start;
                start = pos + 1;
            }
            //else there is someting before the quote, first copy that
            else {
                copy_start = start;
                copy_length = pos - copy_start;
                start = pos;
            }
        }
        //if space
        if (fArgString[pos] == ' ') {
            //short option descriptor
            if ((fArgString[start] == '-') && (fArgString[start + 1] != '-')) {
                copy_start = start;
                copy_length = 2;
                start += copy_length;
            }
            //else copy all the space delimitated string
            else {
                copy_start = start;
                copy_length = pos - copy_start;
                start = pos + 1;
            }
        }
        //then push the substring to the args vector
        fArgv.push_back (fArgString.substr (copy_start, copy_length));
        printf("JackArgParser::JackArgParser, add : '%s' \n", (*fArgv.rbegin()).c_str());
    } while (start < arg_len);

    //finally count the options
    for (i = 0; i < fArgv.size(); i++)
        if (fArgv[i].at(0) == '-')
            fArgc++;
}

JackArgParser::~JackArgParser()
{}

string JackArgParser::GetArgString()
{
    return fArgString;
}

int JackArgParser::GetNumArgv()
{
    return fArgv.size();
}

int JackArgParser::GetArgc()
{
    return fArgc;
}

int JackArgParser::GetArgv(vector<string>& argv)
{
    argv = fArgv;
    return 0;
}

int JackArgParser::GetArgv(char** argv)
{
    //argv must be NULL
    if (argv)
        return -1;
    //else allocate and fill it
    argv = (char**)calloc(fArgv.size(), sizeof(char*));
    for (unsigned int i = 0; i < fArgv.size(); i++) {
        argv[i] = (char*)calloc(fArgv[i].length(), sizeof(char));
        fill_n(argv[i], fArgv[i].length() + 1, 0);
        fArgv[i].copy(argv[i], fArgv[i].length());
    }
    return 0;
}

void JackArgParser::DeleteArgv(const char** argv)
{
    unsigned int i;
    for (i = 0; i < fArgv.size(); i++)
        free((void*)argv[i]);
    free((void*)argv);
}

void JackArgParser::ParseParams(jack_driver_desc_t* desc, JSList** param_list)
{
    string options_list;
    unsigned long i = 0;
    unsigned int param = 0;
    size_t param_id = 0;
    JSList* params = NULL;
    jack_driver_param_t* intclient_param;

    for (i = 0; i < desc->nparams; i++)
        options_list += desc->params[i].character;

    for (param = 0; param < fArgv.size(); param++)
    {
        if (fArgv[param][0] == '-')
        {
            //valid option
            if ((param_id = options_list.find_first_of(fArgv[param].at(1))) != string::npos)
            {
                intclient_param = static_cast<jack_driver_param_t*>(calloc(1, sizeof(jack_driver_param_t)));
                intclient_param->character = desc->params[param_id].character;

                switch (desc->params[param_id].type)
                {
                    case JackDriverParamInt:
                        if (param + 1 < fArgv.size()) // something to parse
                            intclient_param->value.i = atoi(fArgv[param + 1].c_str());
                        break;
                        
                    case JackDriverParamUInt:
                        if (param + 1 < fArgv.size()) // something to parse
                            intclient_param->value.ui = strtoul(fArgv[param + 1].c_str(), NULL, 10);
                        break;
                        
                    case JackDriverParamChar:
                        if (param + 1 < fArgv.size()) // something to parse
                            intclient_param->value.c = fArgv[param + 1][0];
                        break;
                        
                    case JackDriverParamString:
                        if (param + 1 < fArgv.size()) // something to parse
                            fArgv[param + 1].copy(intclient_param->value.str, min(static_cast<int>(fArgv[param + 1].length()), JACK_DRIVER_PARAM_STRING_MAX));
                        break;
                        
                    case JackDriverParamBool:
                        intclient_param->value.i = true;
                        break;
                }
                //add to the list
                params = jack_slist_append(params, intclient_param);
            }
            //invalid option
            else
                printf("Invalid option '%c'\n", fArgv[param][1]);
        }
    }

    assert(param_list);
    *param_list = params;
}

void JackArgParser::FreeParams(JSList* param_list)
{
    JSList *node_ptr = param_list;
    JSList *next_node_ptr;

    while (node_ptr) {
        next_node_ptr = node_ptr->next;
        free(node_ptr->data);
        free(node_ptr);
        node_ptr = next_node_ptr;
    }
}

struct JackFaustInternal {

    //----------------------------------------------------------------------------
    // 	number of input and output channels
    //----------------------------------------------------------------------------

    int	fNumInChans;
    int	fNumOutChans;

    //----------------------------------------------------------------------------
    // Jack ports
    //----------------------------------------------------------------------------

    jack_port_t* fInputPorts[256];
    jack_port_t* fOutputPorts[256];

    //----------------------------------------------------------------------------
    // tables of noninterleaved input and output channels for FAUST
    //----------------------------------------------------------------------------

    float* fInChannel[256];
    float* fOutChannel[256];
    
    jack_client_t* fClient;
    UI* fInterface;
    mydsp fDSP;
    
    JackFaustInternal(jack_client_t* client, const JSList* params)
        :fClient(client)
    {}
    
    ~JackFaustInternal()
    {
        delete fInterface;
    }
    
    int Open()
    {
        char**	physicalInPorts;
        char**	physicalOutPorts;
 
        fInterface = new OSCUI();
        fDSP.buildUserInterface(fInterface);
         
        jack_set_process_callback(fClient, process, this);
        jack_set_sample_rate_callback(fClient, srate, this);
        
        fNumInChans = fDSP.getNumInputs();
        fNumOutChans = fDSP.getNumOutputs();
        
        for (int i = 0; i < fNumInChans; i++) {
            char buf[256];
            snprintf(buf, 256, "in_%d", i); 
            fInputPorts[i] = jack_port_register(fClient, buf, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
        }
        for (int i = 0; i < fNumOutChans; i++) {
            char buf[256];
            snprintf(buf, 256, "out_%d", i); 
            fOutputPorts[i] = jack_port_register(fClient, buf, JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
        }
        
        fDSP.init(jack_get_sample_rate(fClient));
        
        physicalInPorts = (char **)jack_get_ports(fClient, NULL, NULL, JackPortIsPhysical|JackPortIsInput);
        physicalOutPorts = (char **)jack_get_ports(fClient, NULL, NULL, JackPortIsPhysical|JackPortIsOutput);
            
        if (jack_activate(fClient)) {
            fprintf(stderr, "cannot activate client");
            return -1;
        }
        
        if (physicalOutPorts != NULL) {
            for (int i = 0; i < fNumInChans && physicalOutPorts[i]; i++) {
                jack_connect(fClient, physicalOutPorts[i], jack_port_name(fInputPorts[i]));
            }
        }
        
        if (physicalInPorts != NULL) {
            for (int i = 0; i < fNumOutChans && physicalInPorts[i]; i++) {
                jack_connect(fClient, jack_port_name(fOutputPorts[i]), physicalInPorts[i]);
            } 		
        }
  
        return 0;
    }    
 
    //----------------------------------------------------------------------------
    // Jack Callbacks 
    //----------------------------------------------------------------------------

    static int srate(jack_nframes_t nframes, void *arg)
    {
        printf("the sample rate is now %u/sec\n", nframes);
        return 0;
    }

    static int process(jack_nframes_t nframes, void *arg)
    {
        JackFaustInternal* obj = (JackFaustInternal*)arg;
        AVOIDDENORMALS;
        
        for (int i = 0; i < obj->fNumInChans; i++) {
            obj->fInChannel[i] = (float *)jack_port_get_buffer(obj->fInputPorts[i], nframes);
        }
        for (int i = 0; i < obj->fNumOutChans; i++) {
            obj->fOutChannel[i] = (float *)jack_port_get_buffer(obj->fOutputPorts[i], nframes);
        }
        obj->fDSP.compute(nframes, obj->fInChannel, obj->fOutChannel);
        
        return 0;
    }
    
};

#ifdef __cplusplus
extern "C"
{
#endif

jack_driver_desc_t* jack_get_descriptor() 
{
    jack_driver_desc_t *desc;
    unsigned int i;
    desc = (jack_driver_desc_t*)calloc(1, sizeof(jack_driver_desc_t));

    strcpy(desc->name, "faust");                                    // size MUST be less then JACK_DRIVER_NAME_MAX + 1
    strcpy(desc->desc, " Faust generated internal");      // size MUST be less then JACK_DRIVER_PARAM_DESC + 1
    
    desc->nparams = 0;
    /*
    desc->nparams = 2;
    desc->params = (jack_driver_param_desc_t*)calloc(desc->nparams, sizeof(jack_driver_param_desc_t));

    i = 0;
    strcpy(desc->params[i].name, "channels");
    desc->params[i].character = 'c';
    desc->params[i].type = JackDriverParamInt;
    desc->params[i].value.ui = 0;
    strcpy(desc->params[i].short_desc, "Maximum number of channels");
    strcpy(desc->params[i].long_desc, desc->params[i].short_desc);

    i++;
    strcpy(desc->params[i].name, "inchannels");
    desc->params[i].character = 'i';
    desc->params[i].type = JackDriverParamInt;
    desc->params[i].value.ui = 0;
    strcpy(desc->params[i].short_desc, "Maximum number of input channels");
    strcpy(desc->params[i].long_desc, desc->params[i].short_desc);
    */

    return desc;
}

int jack_internal_initialize(jack_client_t* client, const JSList* params)
{
    try {
    
        JackFaustInternal* internal = new JackFaustInternal(client, params);
        if (internal->Open() == 0) {
            return 0;
        } else {
            delete internal;
            return 1;
        }
    
    } catch (...) {
        return 1;
    }
}

int jack_initialize(jack_client_t* client, const char* load_init)
{
    JSList* params = NULL;
    jack_driver_desc_t *desc = jack_get_descriptor();

    JackArgParser parser(load_init);
    if (parser.GetArgc() > 0) 
        parser.ParseParams(desc, &params);
    
    int res = jack_internal_initialize(client, params);
    parser.FreeParams(params);
    return res;
}

void jack_finish(void* arg)
{
    JackFaustInternal* internal = static_cast<JackFaustInternal*>(arg);

    if (internal) {
        printf("Unloading internal\n");
        delete internal;
    }
}

#ifdef __cplusplus
}
#endif
	
/********************END ARCHITECTURE SECTION (part 2/2)****************/
					

