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
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/soundcard.h>
#include <pwd.h>
#include <sys/types.h>
#include <assert.h>
#include <gtk/gtk.h>
#include <pthread.h> 
#include <sys/wait.h>

#include <map>
#include <list>
#include <vector>

#include <iostream>
#include <fstream>

using namespace std;

struct Meta : map<const char*, const char*>
{
    void declare (const char* key, const char* value) { (*this)[key]=value; }
};


// g++ -O3 -lm -lpthread `gtk-config --cflags --libs` ex2.cpp
 

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

//#define BENCHMARKMODE

inline int		lsr (int x, int n)			{ return int(((unsigned int)x) >> n); }

inline int int2pow2 (int x)	{ int r=0; while ((1<<r)<x) r++; return r; }


void setRealtimePriority ()
{
        struct passwd *         pw;
        int                     err;
        uid_t                   uid;
        struct sched_param      param;  
        
        uid = getuid ();
        pw = getpwnam ("root");
        setuid (pw->pw_uid); 
        param.sched_priority = 50; /* 0 to 99  */
        err = sched_setscheduler(0, SCHED_RR,  &param); 
        setuid (uid);
        if (err != -1) {
                printf("OK : Running with realtime priority\n");
        } else {
                printf("Warning : running with non-realtime priority\n");
        }
        
}

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }
//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((size_t)(calloc((nmemb*size)+15,sizeof(char)))+15 & ~15); }

<<includeIntrinsic>>

#ifdef BENCHMARKMODE
// mesuring jack performances
static __inline__ unsigned long long int rdtsc(void)
{
  unsigned long long int x;
     __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
     return x;
}

#define KSKIP 10
#define KMESURE 1024
int mesure = 0;
unsigned long long int starts[KMESURE];
unsigned long long int stops [KMESURE];

#define STARTMESURE starts[mesure%KMESURE] = rdtsc();
#define STOPMESURE stops[mesure%KMESURE] = rdtsc(); mesure = mesure+1;

void printstats()
{
    unsigned long long int low, hi, tot;
    low = hi = tot = (stops[KSKIP] - starts[KSKIP]);

    if (mesure < KMESURE) {
    
        for (int i = KSKIP+1; i<mesure; i++) {
            unsigned long long int m = stops[i] - starts[i];
            if (m<low) low = m;
            if (m>hi) hi = m;
            tot += m;
        }
        cout << low << ' ' << tot/(mesure-KSKIP) << ' ' << hi << endl;

    } else {
    
        for (int i = KSKIP+1; i<KMESURE; i++) {
            unsigned long long int m = stops[i] - starts[i];
            if (m<low) low = m;
            if (m>hi) hi = m;
            tot += m;
        }
        cout << low << ' ' << tot/(KMESURE-KSKIP) << ' ' << hi << endl;

    }    
}
#else

#define STARTMESURE
#define STOPMESURE

#endif

/******************************************************************************
*******************************************************************************

								AUDIO INTERFACE

*******************************************************************************
*******************************************************************************/

enum { kRead = 1, kWrite = 2, kReadWrite = 3 };

// AudioParam : a convenient class to pass parameters to the AudioInterface
struct AudioParam
{
	const char*	fDeviceName;					
	int			fSamplingFrequency;
	int			fRWMode;
	int			fSampleFormat;
	int			fFramesPerBuffer; 
	
	AudioParam() : 
		fDeviceName("/dev/dsp"),
		fSamplingFrequency(44100),
		fRWMode(kReadWrite),
		fSampleFormat(AFMT_S16_LE),
		fFramesPerBuffer(512)
	{}
	
	AudioParam&	device(const char * n)	{ fDeviceName = n; 			return *this; }
	AudioParam&	frequency(int f)		{ fSamplingFrequency = f; 	return *this; }
	AudioParam&	mode(int m)				{ fRWMode = m; 				return *this; }
	AudioParam&	format(int f)			{ fSampleFormat = f; 		return *this; }
	AudioParam&	buffering(int fpb)		{ fFramesPerBuffer = fpb; 	return *this; }
};

class AudioInterface 
{
 private:
	AudioParam	fParam;
	int			fOutputDevice ;		
	int			fInputDevice ;			
	int			fNumOfOutputChannels;
	int			fNumOfInputChannels;
	int			fInputBufferSize;
	short*		fInputBuffer;
	int			fOutputBufferSize;
	short*		fOutputBuffer;
	

 public:
 
	const char*	getDeviceName()				{ return fParam.fDeviceName;  	}
 	int		getSamplingFrequency()			{ return fParam.fSamplingFrequency; 	}
	int		getRWMode()						{ return fParam.fRWMode; 		}
	int		getSampleFormat()				{ return fParam.fSampleFormat; 		}
	int		getFramesPerBuffer()			{ return fParam.fFramesPerBuffer;  	}
	
	int		getNumOutputs()					{ return fNumOfOutputChannels;	}
	int		getNumInputs()					{ return fNumOfInputChannels; 	}
	int		getInputBufferSize()			{ return fInputBufferSize; 		}
	int		getOutputBufferSize()			{ return fOutputBufferSize; 	}

	
	AudioInterface(const AudioParam& ap = AudioParam()) : fParam(ap)
	{
		fOutputDevice 			= -1;
		fInputDevice 			= -1;
		fNumOfOutputChannels	= 0;
		fNumOfInputChannels		= 0;
		fInputBufferSize		= 0;
		fInputBuffer			= 0;
		fOutputBufferSize		= 0;
		fOutputBuffer			= 0;
	}

	void openInputAudioDev ()
	{
		assert( (fInputDevice = ::open(fParam.fDeviceName, O_RDONLY, 0)) 		> 0); 
		assert( ioctl(fInputDevice, SNDCTL_DSP_SETFMT, &fParam.fSampleFormat) 		!= -1);	
		assert( ioctl(fInputDevice, SNDCTL_DSP_CHANNELS, &fNumOfInputChannels) != -1);
		assert( ioctl(fInputDevice, SNDCTL_DSP_SPEED, &fParam.fSamplingFrequency) 	!= -1);

		int gFragFormat = (1 << 16) + int2pow2(fParam.fFramesPerBuffer * 2 * fNumOfInputChannels);	
		assert( ioctl(fInputDevice, SNDCTL_DSP_SETFRAGMENT, &gFragFormat) 		!= -1); 

		fInputBufferSize = 0;
		assert( ioctl(fInputDevice, SNDCTL_DSP_GETBLKSIZE, &fInputBufferSize)  != -1);
		assert( fInputBufferSize == fParam.fFramesPerBuffer * 2 * fNumOfInputChannels );

		fInputBuffer = (short*) calloc(fInputBufferSize, 1);
	}

	void openOutputAudioDev ()
	{
		assert( (fOutputDevice = ::open(fParam.fDeviceName, O_WRONLY, 0)) 		>  0);	
		assert( ioctl(fOutputDevice, SNDCTL_DSP_SETFMT, &fParam.fSampleFormat) 		!= -1);	
		assert( ioctl(fOutputDevice, SNDCTL_DSP_CHANNELS,&fNumOfOutputChannels)!= -1);
		assert( ioctl(fOutputDevice, SNDCTL_DSP_SPEED, &fParam.fSamplingFrequency) 	!= -1);

		int gFragFormat = (1 << 16) + int2pow2(fParam.fFramesPerBuffer * 2 * fNumOfOutputChannels);	
		assert( ioctl(fOutputDevice, SNDCTL_DSP_SETFRAGMENT, &gFragFormat) 	!= -1); 

		fOutputBufferSize = 0;
		assert( ioctl(fOutputDevice, SNDCTL_DSP_GETBLKSIZE, &fOutputBufferSize) != -1);
		assert( fOutputBufferSize == fParam.fFramesPerBuffer * 2 * fNumOfOutputChannels );

		fOutputBuffer = (short*)calloc(fOutputBufferSize, 1);
	}

	void open()
	{
		if (fParam.fRWMode & kRead) openInputAudioDev();
		if (fParam.fRWMode & kWrite) openOutputAudioDev();
	}

	void close()
	{
		if (fParam.fRWMode & kRead) ::close(fOutputDevice);
		if (fParam.fRWMode & kWrite) ::close(fInputDevice);
	}
	
	//----------------------------------------------------------------
	//  allocChanGroup() : allocate a group of audio buffers
	//		chan[] 	: is an array of buffer pointers
	//		n 		: is the number of buffers to allocate
	//		len 	: is the length of each buffer
	//----------------------------------------------------------------
	
	void allocChanGroup(float* chan[], int n, int len)
	{
		for (int c = 0; c < n; c++) {
			chan[c] = (float*) calloc (len, sizeof(float));
		}
	}
	
	//----------------------------------------------------------------
	//  info() : print information on the audio device
	//----------------------------------------------------------------

	void info()
	{
		audio_buf_info 	info;
		int 			cap;
		printf("Audio Interface Description :\n");
		printf("Sampling Frequency : %d, Sample Format : %d, Mode : %d\n", getSamplingFrequency(), getSampleFormat(), getRWMode());
		
		if (getRWMode() & kWrite) {
			assert( ioctl(fOutputDevice, SNDCTL_DSP_GETOSPACE, &info) != -1);
			printf("output space info: fragments=%d, fragstotal=%d, fragsize=%d, bytes=%d\n", info.fragments, info.fragstotal,
				info.fragsize, info.bytes);
		
			assert( ioctl(fOutputDevice,SNDCTL_DSP_GETCAPS, &cap) != -1); 
			printf("Output capabilities - %d channels : ", fNumOfOutputChannels);
	
			if (cap &  DSP_CAP_DUPLEX) 	printf(" DSP_CAP_DUPLEX");
			if (cap &  DSP_CAP_REALTIME) printf(" DSP_CAP_REALTIME");
			if (cap &  DSP_CAP_DUPLEX) 	printf(" DSP_CAP_DUPLEX");
			if (cap &  DSP_CAP_BATCH) 	printf(" DSP_CAP_BATCH");
			if (cap &  DSP_CAP_COPROC) 	printf(" DSP_CAP_COPROC");
			if (cap &  DSP_CAP_TRIGGER) printf(" DSP_CAP_TRIGGER");
			if (cap &  DSP_CAP_MMAP) 	printf(" DSP_CAP_MMAP");
			if (cap &  DSP_CAP_MULTI) 	printf(" DSP_CAP_MULTI");
			if (cap &  DSP_CAP_BIND) 	printf(" DSP_CAP_BIND");
			printf("\n");
			printf("Output block size = %d\n", fOutputBufferSize);
		}
		
		if (getRWMode() & kRead) {
			assert( ioctl(fInputDevice, SNDCTL_DSP_GETISPACE, &info) != -1);
			printf("input space info: fragments=%d, fragstotal=%d, fragsize=%d, bytes=%d\n", info.fragments, info.fragstotal,
				info.fragsize, info.bytes);


			assert( ioctl(fInputDevice,SNDCTL_DSP_GETCAPS, &cap) != -1); 
			printf("Input capabilities - %d channels : ", fNumOfInputChannels);
			if (cap &  DSP_CAP_DUPLEX) 	printf(" DSP_CAP_DUPLEX");
			if (cap &  DSP_CAP_REALTIME) printf(" DSP_CAP_REALTIME");
			if (cap &  DSP_CAP_DUPLEX) 	printf(" DSP_CAP_DUPLEX");
			if (cap &  DSP_CAP_BATCH) 	printf(" DSP_CAP_BATCH");
			if (cap &  DSP_CAP_COPROC) 	printf(" DSP_CAP_COPROC");
			if (cap &  DSP_CAP_TRIGGER) printf(" DSP_CAP_TRIGGER");
			if (cap &  DSP_CAP_MMAP) 	printf(" DSP_CAP_MMAP");
			if (cap &  DSP_CAP_MULTI) 	printf(" DSP_CAP_MULTI");
			if (cap &  DSP_CAP_BIND) 	printf(" DSP_CAP_BIND");
			printf("\n");
			printf("Input block size = %d\n", fInputBufferSize);
		}
	}

	//----------------------------------------------------------------
	//  read() : read 
	//----------------------------------------------------------------

	bool read(int frames, float* channel[])
	{
		int 	bytes = frames * 2 * fNumOfInputChannels; assert(bytes <= fInputBufferSize);
		int		count = ::read(fInputDevice, fInputBuffer, bytes);
		//assert (bytes == count);

		for (int s = 0; s < frames; s++) {
			for (int c = 0; c < fNumOfInputChannels; c++) {
				channel[c][s] = float(fInputBuffer[c + s*fNumOfInputChannels])*(1.0/float(SHRT_MAX));
			}
		}
		return bytes == count;
	}

	bool write(int frames, float* channel[])
	{
		int 	bytes = frames * 2 * fNumOfOutputChannels; assert(bytes <= fOutputBufferSize);

		for (int f = 0; f < frames; f++) {
			for (int c = 0; c < fNumOfOutputChannels; c++) {
				float x = channel[c][f];
				fOutputBuffer[c + f*fNumOfOutputChannels] = short( max(min(x,1.0),-1.0) * float(SHRT_MAX) ) ;
			}
		}

		int count = ::write(fOutputDevice, fOutputBuffer, bytes);
		assert (bytes == count);

		return bytes == count;
	} 
	
};

/******************************************************************************
*******************************************************************************

								GRAPHIC USER INTERFACE (v2)
								  abstract interfaces

*******************************************************************************
*******************************************************************************/

#include <map>
#include <list>

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

	// -- registerZone(z,c) : zone management
	
	void registerZone(float* z, uiItem* c)
	{
		if (fZoneMap.find(z) == fZoneMap.end()) fZoneMap[z] = new clist();
		fZoneMap[z]->push_back(c);
	} 	

	// -- saveState(filename) : save the value of every zone to a file
	
	void saveState(char* filename)	
	{
		ofstream f(filename);
		
		for (zmap::iterator i=fZoneMap.begin(); i!=fZoneMap.end(); i++) { 
			f << *(i->first) << ' ';
		} 
		
		f << endl;
		f.close();
	}

	// -- recallState(filename) : load the value of every zone from a file
	
	void recallState(char* filename)	
	{
		ifstream f(filename);
		if (f.good()) {
			for (zmap::iterator i=fZoneMap.begin(); i!=fZoneMap.end(); i++) { 
				f >> *(i->first);
			} 
		}
		f.close();
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
	
	// -- passive widgets
	
	virtual void addNumDisplay(const char* label, float* zone, int precision) = 0;
	virtual void addTextDisplay(const char* label, float* zone, const char* names[], float min, float max) = 0;
	virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) = 0;
	virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) = 0;
	
	void addCallback(float* zone, uiCallback foo, void* data);
	
	// -- widget's layouts
	
	virtual void openFrameBox(const char* label) = 0;
	virtual void openTabBox(const char* label) = 0;
	virtual void openHorizontalBox(const char* label) = 0;
	virtual void openVerticalBox(const char* label) = 0;
	virtual void closeBox() = 0;
	
	virtual void show() = 0;
	virtual void run() = 0;
	
	void stop()		{ fStopped = true; }
	bool stopped() 	{ return fStopped; }

    virtual void declare(float* zone, const char* key, const char* value) {}
};

/**
 * User Interface Item: abstract definition
 */

class uiItem
{
  protected :
		  
	UI*		fGUI;
	float*		fZone;
	float		fCache;
	
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

// en cours d'installation de call back. a finir!!!!!

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

/******************************************************************************
*******************************************************************************

                                GRAPHIC USER INTERFACE
                                  gtk interface

*******************************************************************************
*******************************************************************************/

#include <gtk/gtk.h>

#define stackSize 256

// Insertion modes

#define kSingleMode 0
#define kBoxMode 1
#define kTabMode 2


/**
 * rmWhiteSpaces(): Remove the leading and trailing white spaces of a string
 * (but not those in the middle of the string)
 */
static string rmWhiteSpaces(const string& s)
{
    size_t i = s.find_first_not_of(" \t");
    size_t j = s.find_last_not_of(" \t");

    if (i != string::npos & j != string::npos) {
        return s.substr(i, 1+j-i);
    } else {
        return "";
    }
}

/**
 * Extracts metdata from a label : 'vol [unit: dB]' -> 'vol' + metadata
 */
static void extractMetadata(const string& fulllabel, string& label, map<string, string>& metadata)
{
    enum {kLabel, kEscape1, kEscape2, kEscape3, kKey, kValue};
    int state = kLabel; int deep = 0;
    string key, value;

    for (unsigned int i=0; i < fulllabel.size(); i++) {
        char c = fulllabel[i];
        switch (state) {
            case kLabel :
                assert (deep == 0);
                switch (c) {
                    case '\\' : state = kEscape1; break;
                    case '[' : state = kKey; deep++; break;
                    default : label += c;
                }
                break;

            case kEscape1 :
                label += c;
                state = kLabel;
                break;

            case kEscape2 :
                key += c;
                state = kKey;
                break;

            case kEscape3 :
                value += c;
                state = kValue;
                break;

            case kKey :
                assert (deep > 0);
                switch (c) {
                    case '\\' :  state = kEscape2;
                                break;

                    case '[' :  deep++;
                                key += c;
                                break;

                    case ':' :  if (deep == 1) {
                                    state = kValue;
                                } else {
                                    key += c;
                                }
                                break;
                    case ']' :  deep--;
                                if (deep < 1) {
                                    metadata[rmWhiteSpaces(key)] = "";
                                    state = kLabel;
                                    key="";
                                    value="";
                                } else {
                                    key += c;
                                }
                                break;
                    default :   key += c;
                }
                break;

            case kValue :
                assert (deep > 0);
                switch (c) {
                    case '\\' : state = kEscape3;
                                break;

                    case '[' :  deep++;
                                value += c;
                                break;

                    case ']' :  deep--;
                                if (deep < 1) {
                                    metadata[rmWhiteSpaces(key)]=rmWhiteSpaces(value);
                                    state = kLabel;
                                    key="";
                                    value="";
                                } else {
                                    value += c;
                                }
                                break;
                    default :   value += c;
                }
                break;

            default :
                cerr << "ERROR unrecognized state " << state << endl;
        }
    }
    label = rmWhiteSpaces(label);
}

class GTKUI : public UI
{
 private :
    static bool                         fInitialized;
    static list<UI*>                    fGuiList;
    static map<float*, float>           fGuiSize;       // map widget zone with widget size coef
    static map<float*, string>          fTooltip;       // map widget zone with tooltip strings
    
 protected :
    GtkWidget*  fWindow;
    int         fTop;
    GtkWidget*  fBox[stackSize];
    int         fMode[stackSize];
    bool        fStopped;

    GtkWidget* addWidget(const char* label, GtkWidget* w);
    virtual void pushBox(int mode, GtkWidget* w);

        
 public :
    
    static const gboolean expand = TRUE;
    static const gboolean fill = TRUE;
    static const gboolean homogene = FALSE;
         
    GTKUI(char * name, int* pargc, char*** pargv);

    // -- Labels and metadata

    virtual void declare (float* zone, const char* key, const char* value);
    virtual int  checkLabelOptions (GtkWidget* widget, const string& fullLabel, string& simplifiedLabel);
    virtual void checkForTooltip (float* zone, GtkWidget* widget);
    
    // -- layout groups
    
    virtual void openFrameBox(const char* label);   
    virtual void openTabBox(const char* label = "");
    virtual void openHorizontalBox(const char* label = "");
    virtual void openVerticalBox(const char* label = "");

    // -- extra widget's layouts

    virtual void openDialogBox(const char* label, float* zone);
    virtual void openEventBox(const char* label = "");
    virtual void openHandleBox(const char* label = "");
    virtual void openExpanderBox(const char* label, float* zone);
    
    virtual void closeBox();
    virtual void adjustStack(int n);

    // -- active widgets
    
    virtual void addButton(const char* label, float* zone);
    virtual void addToggleButton(const char* label, float* zone);
    virtual void addCheckButton(const char* label, float* zone);
    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step);   
    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step); 
    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step);
    
    // -- passive display widgets
    
    virtual void addNumDisplay(const char* label, float* zone, int precision);
    virtual void addTextDisplay(const char* label, float* zone, const char* names[], float min, float max);
    virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max);
    virtual void addVerticalBargraph(const char* label, float* zone, float min, float max);
    
    virtual void show();
    virtual void run();
    
};

/******************************************************************************
*******************************************************************************

                                GRAPHIC USER INTERFACE (v2)
                                  gtk implementation

*******************************************************************************
*******************************************************************************/

// global static fields

list<UI*>                   UI::fGuiList;

bool                        GTKUI::fInitialized = false;
map<float*, float>          GTKUI::fGuiSize;
map<float*, string>         GTKUI::fTooltip;

static gint delete_event( GtkWidget *widget, GdkEvent *event, gpointer data )
{
    return FALSE; 
}

static void destroy_event( GtkWidget *widget, gpointer data )
{
    gtk_main_quit ();
}

GTKUI::GTKUI(char * name, int* pargc, char*** pargv) 
{
    if (!fInitialized) {
        gtk_init(pargc, pargv);
        fInitialized = true;
    }
    
    fWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    //gtk_container_set_border_width (GTK_CONTAINER (fWindow), 10);
    gtk_window_set_title (GTK_WINDOW (fWindow), name);
    gtk_signal_connect (GTK_OBJECT (fWindow), "delete_event", GTK_SIGNAL_FUNC (delete_event), NULL);
    gtk_signal_connect (GTK_OBJECT (fWindow), "destroy", GTK_SIGNAL_FUNC (destroy_event), NULL);

    fTop = 0;
    fBox[fTop] = gtk_vbox_new (homogene, 4);
    fMode[fTop] = kBoxMode;
    gtk_container_add (GTK_CONTAINER (fWindow), fBox[fTop]);
    fStopped = false;
}

// empilement des boites

void GTKUI::pushBox(int mode, GtkWidget* w)
{
    ++fTop;
    assert(fTop < stackSize);
    fMode[fTop]     = mode;
    fBox[fTop]      = w;
}

/**
 * Remove n levels from the stack S before the top level
 * adjustStack(n): S -> S' with S' = S(0),S(n+1),S(n+2),...
 */
void GTKUI::adjustStack(int n)
{
    if (n > 0) {
        assert(fTop >= n);

        fTop -= n; 
        fMode[fTop] = fMode[fTop+n];
        fBox[fTop]  = fBox[fTop+n];
    }
}

void GTKUI::closeBox()
{
    --fTop;
    assert(fTop >= 0);
}

/**
 * Analyses the widget zone metadata declarations and takes
 * appropriate actions 
 */
void GTKUI::declare(float* zone, const char* key, const char* value)
{
    if (strcmp(key,"size")==0) {
        fGuiSize[zone]=atof(value);
    }
    else if (strcmp(key,"tooltip")==0) {
        fTooltip[zone] = value ;
    }
}

/**
 * Analyses a full label and activates the relevant options. returns a simplified
 * label (without options) and an amount of stack adjustement (in case additional
 * containers were pushed on the stack). 
 */

int GTKUI::checkLabelOptions(GtkWidget* widget, const string& fullLabel, string& simplifiedLabel)
{   
    map<string, string> metadata;
    extractMetadata(fullLabel, simplifiedLabel, metadata);

    if (metadata.count("tooltip")) {
        gtk_tooltips_set_tip (gtk_tooltips_new (), widget, metadata["tooltip"].c_str(), NULL);
    }
    if (metadata["option"] == "detachable") {
        openHandleBox(simplifiedLabel.c_str());
        return 1;
    }

    // no adjustement of the stack needed
    return 0;
}

/**
 * Check if a tooltip is associated to a zone and add it to the corresponding widget
 */
void GTKUI::checkForTooltip(float* zone, GtkWidget* widget)
{
    if (fTooltip.count(zone)) {
        gtk_tooltips_set_tip (gtk_tooltips_new (), widget, fTooltip[zone].c_str(), NULL);
    }
}

// les differentes boites

void GTKUI::openFrameBox(const char* label)
{
    GtkWidget * box = gtk_frame_new (label);
    //gtk_container_set_border_width (GTK_CONTAINER (box), 10);
            
    pushBox(kSingleMode, addWidget(label, box));
}

void GTKUI::openTabBox(const char* fullLabel)
{
    string  label;
    GtkWidget* widget = gtk_notebook_new();

    int     adjust = checkLabelOptions(widget, fullLabel, label);

    pushBox(kTabMode, addWidget(label.c_str(), widget));

    // adjust stack because otherwise Handlebox will remain open
    adjustStack(adjust);
}

void GTKUI::openHorizontalBox(const char* fullLabel)
{   
    string   label;
    GtkWidget* box = gtk_hbox_new (homogene, 4);
    int     adjust = checkLabelOptions(box, fullLabel, label);

    gtk_container_set_border_width (GTK_CONTAINER (box), 10);
            
    if (fMode[fTop] != kTabMode && label[0] != 0) {
        GtkWidget * frame = addWidget(label.c_str(), gtk_frame_new (label.c_str()));
        gtk_container_add (GTK_CONTAINER(frame), box);
        gtk_widget_show(box);
        pushBox(kBoxMode, box);
    } else {
        pushBox(kBoxMode, addWidget(label.c_str(), box));
    }

    // adjust stack because otherwise Handlebox will remain open
    adjustStack(adjust);
}

void GTKUI::openVerticalBox(const char* fullLabel)
{
    string  label;
    GtkWidget * box = gtk_vbox_new (homogene, 4);
    int      adjust = checkLabelOptions(box, fullLabel, label);

    gtk_container_set_border_width (GTK_CONTAINER (box), 10);
            
    if (fMode[fTop] != kTabMode && label[0] != 0) {
        GtkWidget * frame = addWidget(label.c_str(), gtk_frame_new (label.c_str()));
        gtk_container_add (GTK_CONTAINER(frame), box);
        gtk_widget_show(box);
        pushBox(kBoxMode, box);
    } else {
        pushBox(kBoxMode, addWidget(label.c_str(), box));
    }

    // adjust stack because otherwise Handlebox will remain open
    adjustStack(adjust);
}

void GTKUI::openHandleBox(const char* label)
{
    GtkWidget * box = gtk_hbox_new (homogene, 4);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);
    if (fMode[fTop] != kTabMode && label[0] != 0)
    {
        GtkWidget * frame = addWidget(label, gtk_handle_box_new ());
        gtk_container_add (GTK_CONTAINER(frame), box);
        gtk_widget_show(box);
        pushBox(kBoxMode, box);
    }
    else
    {
        pushBox(kBoxMode, addWidget(label, box));
    }
}

void GTKUI::openEventBox(const char* label)
{
    GtkWidget * box = gtk_hbox_new (homogene, 4);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);
    if (fMode[fTop] != kTabMode && label[0] != 0)
    {
        GtkWidget * frame = addWidget(label, gtk_event_box_new ());
        gtk_container_add (GTK_CONTAINER(frame), box);
        gtk_widget_show(box);
        pushBox(kBoxMode, box);
    }
    else
    {
        pushBox(kBoxMode, addWidget(label, box));
    }
}

struct uiExpanderBox : public uiItem
{
    GtkExpander* fButton;
    uiExpanderBox(UI* ui, float* zone, GtkExpander* b) : uiItem(ui, zone), fButton(b) {}
    static void expanded (GtkWidget *widget, gpointer data)
    {
        float   v = gtk_expander_get_expanded  (GTK_EXPANDER(widget));
        if (v == 1.000000)
        {
            v = 0;
        }
        else v = 1;
        ((uiItem*)data)->modifyZone(v);
    }

    virtual void reflectZone()
    {
        float   v = *fZone;
        fCache = v;
        gtk_expander_set_expanded(GTK_EXPANDER(fButton), v);
    }
};

void GTKUI::openExpanderBox(const char* label, float* zone)
{
    *zone = 0.0;
    GtkWidget * box = gtk_hbox_new (homogene, 4);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);
    if (fMode[fTop] != kTabMode && label[0] != 0)
    {
        GtkWidget * frame = addWidget(label, gtk_expander_new (label));
        gtk_container_add (GTK_CONTAINER(frame), box);
        uiExpanderBox* c = new uiExpanderBox(this, zone, GTK_EXPANDER(frame));
        gtk_signal_connect (GTK_OBJECT (frame), "activate", GTK_SIGNAL_FUNC (uiExpanderBox::expanded), (gpointer)c);
        gtk_widget_show(box);
        pushBox(kBoxMode, box);
    }
    else
    {
        pushBox(kBoxMode, addWidget(label, box));
    }
}

GtkWidget* GTKUI::addWidget(const char* label, GtkWidget* w)
{ 
    switch (fMode[fTop]) {
        case kSingleMode    : gtk_container_add (GTK_CONTAINER(fBox[fTop]), w);                             break;
        case kBoxMode       : gtk_box_pack_start (GTK_BOX(fBox[fTop]), w, expand, fill, 0);                 break;
        case kTabMode       : gtk_notebook_append_page (GTK_NOTEBOOK(fBox[fTop]), w, gtk_label_new(label)); break;
    }
    gtk_widget_show (w);
    return w;
}

// --------------------------- Press button ---------------------------

struct uiButton : public uiItem
{
    GtkButton*  fButton;
    
    uiButton (UI* ui, float* zone, GtkButton* b) : uiItem(ui, zone), fButton(b) {}
    
    static void pressed( GtkWidget *widget, gpointer   data )
    {
        uiItem* c = (uiItem*) data;
        c->modifyZone(1.0);
    }

    static void released( GtkWidget *widget, gpointer   data )
    {
        uiItem* c = (uiItem*) data;
        c->modifyZone(0.0);
    }

    virtual void reflectZone()  
    { 
        float   v = *fZone;
        fCache = v; 
        if (v > 0.0) gtk_button_pressed(fButton); else gtk_button_released(fButton);
    }
};

void GTKUI::addButton(const char* label, float* zone)
{
    *zone = 0.0;
    GtkWidget*  button = gtk_button_new_with_label (label);
    addWidget(label, button);
    
    uiButton* c = new uiButton(this, zone, GTK_BUTTON(button));
    
    gtk_signal_connect (GTK_OBJECT (button), "pressed", GTK_SIGNAL_FUNC (uiButton::pressed), (gpointer) c);
    gtk_signal_connect (GTK_OBJECT (button), "released", GTK_SIGNAL_FUNC (uiButton::released), (gpointer) c);

    checkForTooltip(zone, button);
}

// ---------------------------  Toggle Buttons ---------------------------

struct uiToggleButton : public uiItem
{
    GtkToggleButton* fButton;
    
    uiToggleButton(UI* ui, float* zone, GtkToggleButton* b) : uiItem(ui, zone), fButton(b) {}
    
    static void toggled (GtkWidget *widget, gpointer data)
    {
        float   v = (GTK_TOGGLE_BUTTON (widget)->active) ? 1.0 : 0.0; 
        ((uiItem*)data)->modifyZone(v);
    }

    virtual void reflectZone()  
    { 
        float   v = *fZone;
        fCache = v; 
        gtk_toggle_button_set_active(fButton, v > 0.0); 
    }
};

void GTKUI::addToggleButton(const char* label, float* zone)
{
    *zone = 0.0;
    GtkWidget*  button = gtk_toggle_button_new_with_label (label);
    addWidget(label, button);
    
    uiToggleButton* c = new uiToggleButton(this, zone, GTK_TOGGLE_BUTTON(button));
    gtk_signal_connect (GTK_OBJECT (button), "toggled", GTK_SIGNAL_FUNC (uiToggleButton::toggled), (gpointer) c);

    checkForTooltip(zone, button);
}

void show_dialog(GtkWidget *widget, gpointer data)
{
    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(widget)) == TRUE)
    {
        gtk_widget_show(GTK_WIDGET(data));
        gint root_x, root_y;
        gtk_window_get_position (GTK_WINDOW(data), &root_x, &root_y);
        root_y -= 120;
        gtk_window_move(GTK_WINDOW(data), root_x, root_y);
    }
    else gtk_widget_hide(GTK_WIDGET(data));
}

static gboolean deleteevent( GtkWidget *widget, gpointer   data )
{
    return TRUE;
} 

void GTKUI::openDialogBox(const char* label, float* zone)
{
    // create toplevel window and set properties
    GtkWidget * dialog = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_decorated(GTK_WINDOW(dialog), TRUE);
    gtk_window_set_deletable(GTK_WINDOW(dialog), FALSE);
    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
    gtk_window_set_gravity(GTK_WINDOW(dialog), GDK_GRAVITY_SOUTH);
    gtk_window_set_transient_for (GTK_WINDOW(dialog), GTK_WINDOW(fWindow));
    gtk_window_set_position (GTK_WINDOW(dialog), GTK_WIN_POS_MOUSE);
    gtk_window_set_keep_below (GTK_WINDOW(dialog), FALSE);
    gtk_window_set_title (GTK_WINDOW (dialog), label);
    g_signal_connect (G_OBJECT (dialog), "delete_event", G_CALLBACK (deleteevent), NULL); 
    gtk_window_set_destroy_with_parent(GTK_WINDOW(dialog), TRUE);

    GtkWidget * box = gtk_hbox_new (homogene, 4);
 
    *zone = 0.0;
    GtkWidget*  button = gtk_toggle_button_new ();
    gtk_signal_connect (GTK_OBJECT (button), "toggled", GTK_SIGNAL_FUNC (show_dialog), (gpointer) dialog);
 
    gtk_container_add (GTK_CONTAINER(fBox[fTop]), button);
    gtk_container_add (GTK_CONTAINER(dialog), box);
    gtk_widget_show (button);
    gtk_widget_show(box);
    pushBox(kBoxMode, box);
}

// ---------------------------  Check Button ---------------------------

struct uiCheckButton : public uiItem
{
    GtkToggleButton* fButton;
    
    uiCheckButton(UI* ui, float* zone, GtkToggleButton* b) : uiItem(ui, zone), fButton(b) {}
    
    static void toggled (GtkWidget *widget, gpointer data)
    {
        float   v = (GTK_TOGGLE_BUTTON (widget)->active) ? 1.0 : 0.0; 
        ((uiItem*)data)->modifyZone(v);
    }

    virtual void reflectZone()  
    { 
        float   v = *fZone;
        fCache = v; 
        gtk_toggle_button_set_active(fButton, v > 0.0); 
    }
};

void GTKUI::addCheckButton(const char* label, float* zone)
{
    *zone = 0.0;
    GtkWidget*  button = gtk_check_button_new_with_label (label);
    addWidget(label, button);
    
    uiCheckButton* c = new uiCheckButton(this, zone, GTK_TOGGLE_BUTTON(button));
    gtk_signal_connect (GTK_OBJECT (button), "toggled", GTK_SIGNAL_FUNC(uiCheckButton::toggled), (gpointer) c);

    checkForTooltip(zone, button);
}

// ---------------------------  Adjustmenty based widgets ---------------------------

struct uiAdjustment : public uiItem
{
    GtkAdjustment* fAdj;
    
    uiAdjustment(UI* ui, float* zone, GtkAdjustment* adj) : uiItem(ui, zone), fAdj(adj) {}
    
    static void changed (GtkWidget *widget, gpointer data)
    {
        float   v = GTK_ADJUSTMENT (widget)->value; 
        ((uiItem*)data)->modifyZone(v);
    }

    virtual void reflectZone()  
    { 
        float   v = *fZone;
        fCache = v; 
        gtk_adjustment_set_value(fAdj, v);  
    }
};

static int precision(double n)
{
    if (n < 0.009999) return 3;
    else if (n < 0.099999) return 2;
    else if (n < 0.999999) return 1;
    else return 0;
}

// -------------------------- Vertical Slider -----------------------------------

void GTKUI::addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
{
    *zone = init;
    GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
    
    uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));

    gtk_signal_connect (GTK_OBJECT (adj), "value-changed", GTK_SIGNAL_FUNC (uiAdjustment::changed), (gpointer) c);
    
    GtkWidget* slider = gtk_vscale_new (GTK_ADJUSTMENT(adj));
    gtk_range_set_inverted (GTK_RANGE(slider), TRUE);
    gtk_scale_set_digits(GTK_SCALE(slider), precision(step));
    float size = 160 * pow(2, fGuiSize[zone]);
    gtk_widget_set_usize(slider, -1, size);

    if (label && label[0]!=0) {
        openFrameBox(label);
        addWidget(label, slider);
        closeBox();
    } else {
        addWidget(label, slider);
    }

    checkForTooltip(zone, slider);
}

// -------------------------- Horizontal Slider -----------------------------------

void GTKUI::addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
{
    *zone = init;
    GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
    
    uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));

    gtk_signal_connect (GTK_OBJECT (adj), "value-changed", GTK_SIGNAL_FUNC (uiAdjustment::changed), (gpointer) c);
    
    GtkWidget* slider = gtk_hscale_new (GTK_ADJUSTMENT(adj));
    gtk_scale_set_digits(GTK_SCALE(slider), precision(step));
    float size = 160 * pow(2, fGuiSize[zone]);
    gtk_widget_set_usize(slider, size, -1);
    
    if (label && label[0]!=0) {
        openFrameBox(label);
        addWidget(label, slider);
        closeBox();
    } else {
        addWidget(label, slider);
    }             

    checkForTooltip(zone, slider);
}

// ------------------------------ Num Entry -----------------------------------

void GTKUI::addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
{
    *zone = init;
    GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, step);
    
    uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));

    gtk_signal_connect (GTK_OBJECT (adj), "value-changed", GTK_SIGNAL_FUNC (uiAdjustment::changed), (gpointer) c);
    
    GtkWidget* spinner = gtk_spin_button_new (GTK_ADJUSTMENT(adj), 0.005, precision(step));

    //gtk_widget_set_usize(slider, 160, -1);
    openFrameBox(label);
    addWidget(label, spinner);
    closeBox();

    checkForTooltip(zone, spinner);
}

// ==========================   passive widgets ===============================

// ------------------------------ Progress Bar -----------------------------------

struct uiBargraph : public uiItem
{
    GtkProgressBar*     fProgressBar;
    float               fMin;
    float               fMax;
    
    uiBargraph(UI* ui, float* zone, GtkProgressBar* pbar, float lo, float hi) 
            : uiItem(ui, zone), fProgressBar(pbar), fMin(lo), fMax(hi) {}

    float scale(float v)        { return (v-fMin)/(fMax-fMin); }
    
    virtual void reflectZone()  
    { 
        float   v = *fZone;
        fCache = v; 
        gtk_progress_bar_set_fraction(fProgressBar, scale(v));  
    }
};

void GTKUI::addVerticalBargraph(const char* label, float* zone, float lo, float hi)
{
    GtkWidget* pb = gtk_progress_bar_new();
    gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(pb), GTK_PROGRESS_BOTTOM_TO_TOP);
    gtk_widget_set_size_request(pb, 8, -1);
    new uiBargraph(this, zone, GTK_PROGRESS_BAR(pb), lo, hi);
    openFrameBox(label);
    addWidget(label, pb);
    closeBox();

    checkForTooltip(zone, pb);
}

void GTKUI::addHorizontalBargraph(const char* label, float* zone, float lo, float hi)
{
    GtkWidget* pb = gtk_progress_bar_new();
    gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(pb), GTK_PROGRESS_LEFT_TO_RIGHT);
    gtk_widget_set_size_request(pb, -1, 8);
    new uiBargraph(this, zone, GTK_PROGRESS_BAR(pb), lo, hi);
    openFrameBox(label);
    addWidget(label, pb);
    closeBox();

    checkForTooltip(zone, pb);
}

// ------------------------------ Num Display -----------------------------------

struct uiNumDisplay : public uiItem
{
    GtkLabel* fLabel;
    int fPrecision;
    
    uiNumDisplay(UI* ui, float* zone, GtkLabel* label, int precision) 
            : uiItem(ui, zone), fLabel(label), fPrecision(precision) {}

    virtual void reflectZone()  
    { 
        float   v = *fZone;
        fCache = v;
        char s[64]; 
        if (fPrecision <= 0) { 
            snprintf(s, 63, "%d", int(v)); 
        } else if (fPrecision>3) {
            snprintf(s, 63, "%f", v);
        } else {
            const char* format[] = {"%.1f", "%.2f", "%.3f"};
            snprintf(s, 63, format[fPrecision-1], v);
        }
        gtk_label_set_text(fLabel, s);
    }
};
    

void GTKUI::addNumDisplay(const char* label, float* zone, int precision )
{
    GtkWidget* lw = gtk_label_new("");
    new uiNumDisplay(this, zone, GTK_LABEL(lw), precision);
    openFrameBox(label);
    addWidget(label, lw);
    closeBox();

    checkForTooltip(zone, lw);
}

// ------------------------------ Text Display -----------------------------------

struct uiTextDisplay : public uiItem
{
    GtkLabel*       fLabel;
    const char**    fNames;
    float           fMin;
    float           fMax;
    int             fNum;
    
    uiTextDisplay (UI* ui, float* zone, GtkLabel* label, const char* names[], float lo, float hi)
                    : uiItem(ui, zone), fLabel(label), fNames(names), fMin(lo), fMax(hi)
    {
            fNum = 0;
            while (fNames[fNum] != 0) fNum++;
    }

    virtual void reflectZone()  
    { 
        float   v = *fZone;
        fCache = v;
        
        int idx = int(fNum*(v-fMin)/(fMax-fMin));
        
        if      (idx < 0)       idx = 0; 
        else if (idx >= fNum)   idx = fNum-1;
                
        gtk_label_set_text(fLabel, fNames[idx]); 
    }
};

void GTKUI::addTextDisplay(const char* label, float* zone, const char* names[], float lo, float hi )
{
    GtkWidget* lw = gtk_label_new("");
    new uiTextDisplay (this, zone, GTK_LABEL(lw), names, lo, hi);
    openFrameBox(label);
    addWidget(label, lw);
    closeBox();

    checkForTooltip(zone, lw);
}

void GTKUI::show() 
{
    assert(fTop == 0);
    gtk_widget_show  (fBox[0]);
    gtk_widget_show  (fWindow);
}

/**
 * Update all user items reflecting zone z
 */
    
static gboolean callUpdateAllGuis(gpointer)
{ 
    UI::updateAllGuis(); 
    return TRUE;
}
void GTKUI::run() 
{
    assert(fTop == 0);
    gtk_widget_show  (fBox[0]);
    gtk_widget_show  (fWindow);
    gtk_timeout_add(40, callUpdateAllGuis, 0);
    gtk_main ();
    stop();
}

/******************************************************************************
*******************************************************************************

								DSP

*******************************************************************************
*******************************************************************************/

//---------------------------------------------------
// tableaux de buffers initialis� par allocChannels
//---------------------------------------------------

float* 	gInChannel[256];
float* 	gOutChannel[256];

void allocChannels (int size, int numInChan, int numOutChan) 
{
	
	assert (numInChan < 256);
	assert (numOutChan < 256);
	
	
	for (int i = 0; i < numInChan; i++) {
		gInChannel[i] = (float*) calloc (size, sizeof(float));
		for (int j = 0; j < size; j++) {
			gInChannel[i][j] = 0.0;
		}
	}
	
	for (int i = 0; i < numOutChan; i++) {
		gOutChannel[i] = (float*) calloc (size, sizeof(float));
		for (int j = 0; j < size; j++) {
			gOutChannel[i][j] = 0.0;
		}
	}
}

//----------------------------------------------------------------
//  d�inition du processeur de signal
//----------------------------------------------------------------
			
class dsp {
 protected:
	int fSamplingFreq;
 public:
	dsp() {}
	virtual ~dsp() {}
	
	virtual int getNumInputs() 										= 0;
	virtual int getNumOutputs() 										= 0;
	virtual void buildUserInterface(UI* interface) 					= 0;
	virtual void init(int samplingRate) 								= 0;
 	virtual void compute(int len, float** inputs, float** outputs) 	= 0;
};

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/
		
<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

mydsp DSP;

/******************************************************************************
*******************************************************************************

								MAIN PLAY THREAD

*******************************************************************************
*******************************************************************************/
	
// Scan Command Line Arguments

long lopt (char *argv[], const char *name, long def) 
{
	int	i;
	for (i=0; argv[i]; i++) if (!strcmp(argv[i], name)) return atoi(argv[i+1]);
	return def;
}
	
//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------
pthread_t	guithread;
	
void* run_ui(void* ptr)
{
	UI* interface = (UI*) ptr;
	interface->run();
	pthread_exit(0);
	return 0;
}

int main(int argc, char *argv[] )
{
	UI* interface = new GTKUI(argv[0], &argc, &argv);
    // compute rcfilename to (re)store application state
    char    rcfilename[256];
    char*   home = getenv("HOME");
    snprintf(rcfilename, 256, "%s/.%src", home, basename(argv[0]));
	
	AudioInterface	audio (
		AudioParam().frequency(lopt(argv, "--frequency", 44100)) 
					.buffering(lopt(argv, "--buffer", 128))
					//.mode( ((DSP.getNumInputs()>0)?kRead:0) | ((DSP.getNumOutputs()>0)?kWrite:0) )
	);
	audio.open();
	audio.info();
	
	DSP.init(audio.getSamplingFrequency());
	DSP.buildUserInterface(interface);
    
    interface->recallState(rcfilename);

	pthread_create(&guithread, NULL, run_ui, interface);
	
	float* 	inChannel[256];
	float* 	outChannel[256];
	int		fpb = audio.getFramesPerBuffer();
	
	audio.allocChanGroup(inChannel,  max(audio.getNumInputs(),  DSP.getNumInputs()), fpb);
	audio.allocChanGroup(outChannel, max(audio.getNumOutputs(), DSP.getNumOutputs()), fpb);
	setRealtimePriority();
    AVOIDDENORMALS;
	// Sound processing loop
	audio.write(fpb, outChannel);	
	audio.write(fpb, outChannel);	
	while(!interface->stopped()) {
		if ( !audio.write(fpb, outChannel)) printf("w");	
		if ( !audio.read (fpb, inChannel)) printf("r");;
    STARTMESURE
        DSP.compute(fpb, inChannel, outChannel);
    STOPMESURE
	}
	
	audio.close();
    interface->saveState(rcfilename);

#ifdef BENCHMARKMODE
    printstats();
#endif       
	//wait(0);
  	return 0;
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/


