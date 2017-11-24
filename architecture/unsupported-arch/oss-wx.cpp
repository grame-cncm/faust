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
#include <pthread.h> 
#include <sys/wait.h>
#include <list>
#include <vector>
#include <stack>

#include "wx/wx.h"
#include "wx/statbox.h"
#include "wx/notebook.h"
#include "wx/spinctrl.h"

// g++ -O3 -lm `wx-config --cflags --libs` ex2.cpp

using namespace std ;

// abs is now predefined
//template<typename T> T abs (T a)			{ return (a<T(0)) ? -a : a; }


inline int		lsr (int x, int n)			{ return int(((unsigned int)x) >> n); }

inline int 		int2pow2 (int x)	{ int r=0; while ((1<<r)<x) r++; return r; }

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

<<includeIntrinsic>>

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
 private :
	AudioParam	fParam;
	int			fOutputDevice ;		
	int			fInputDevice ;			
	int			fNumOfOutputChannels;
	int			fNumOfInputChannels;
	int			fInputBufferSize;
	short*		fInputBuffer;
	int			fOutputBufferSize;
	short*		fOutputBuffer;
	
 public :
 
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
		int	err = 0;

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
		int	err = 0;

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
		int				err = 0;
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
		assert (bytes == count);

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

								USER INTERFACE

*******************************************************************************
*******************************************************************************/

class UI
{
	bool	fStopped;
public:
		
	UI() : fStopped(false) {}
	virtual ~UI() {}
	
	virtual void addButton(char* label, float* zone) = 0;
	virtual void addToggleButton(char* label, float* zone) = 0;
	virtual void addCheckButton(char* label, float* zone) = 0;
	virtual void addVerticalSlider(char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addHorizontalSlider(char* label, float* zone, float init, float min, float max, float step) = 0;
	virtual void addNumEntry(char* label, float* zone, float init, float min, float max, float step) = 0;
	
	virtual void openFrameBox(char* label) = 0;
	virtual void openTabBox(char* label) = 0;
	virtual void openHorizontalBox(char* label) = 0;
	virtual void openVerticalBox(char* label) = 0;
	virtual void closeBox() = 0;
	
	virtual void run() {};
	
	void stop()		{ fStopped = true; }
	bool stopped() 	{ return fStopped; }
};

/******************************************************************************
*******************************************************************************

								DSP

*******************************************************************************
*******************************************************************************/

//---------------------------------------------------
// tableaux de buffers initialises par allocChannels
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
//  definition du processeur de signal
//----------------------------------------------------------------
			
class dsp {
 protected:
	int fSamplingFreq;
 public:
	dsp() {}
	virtual int getNumInputs() 										= 0;
	virtual int getNumOutputs() 									= 0;
	virtual void buildUserInterface(UI* interface) 					= 0;
	virtual void init(int samplingRate) 							= 0;
 	virtual void compute(int len, float** inputs, float** outputs) 	= 0;
};

<<includeclass>>

mydsp DSP;

/******************************************************************************
*******************************************************************************

							WXWINDOWS USER INTERFACE

*******************************************************************************
*******************************************************************************/


// les modes d'insertion

#define kNormalState 0
#define kNotebookState 1
#define kAutoPageState 2

#define kProp 0
#define kBorder 5
#define kFlag wxALL|wxGROW

	
// faustButton : a wxButton for FAUST. 
class faustButton : public wxButton
{
	float*	fZone;
  public :
	faustButton(wxWindow* parent, const wxString& label, float* zone)
			: wxButton(parent, -1, label, wxPoint(-1, -1)), fZone(zone)
	{ 
		*fZone = 0.0;
	}
  
  	void clickdown (wxCommandEvent& ev)	{ *fZone = 1.0; /*printf("click down : zone (at %p) = %f\n", fZone, *fZone);*/ ev.Skip();}
  	void clickup (wxCommandEvent& ev)	{ *fZone = 0.0; /*printf("click up : zone (at %p) = %f\n", fZone, *fZone);*/ ev.Skip(); }
	
 private:
	DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(faustButton, wxButton)
   EVT_LEFT_DOWN(faustButton::clickdown)
   EVT_LEFT_UP(faustButton::clickup)
END_EVENT_TABLE()
		
	
class faustCheckBox : public wxCheckBox
{
	float*	fZone;
  public :
	faustCheckBox(wxWindow* parent, const wxString& label, float* zone)
			: wxCheckBox(parent, -1, label, wxPoint(-1, -1)), fZone(zone)
	{ 
		*fZone = 0.0;
	}
  
  	void toggle (wxCommandEvent& ev)	{ 
		*fZone = (ev.IsChecked()) ? 1.0 : 0.0; 
		//printf("toogle : zone (at %p) = %f\n", fZone, *fZone); 
	}
	
 private:
	DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(faustCheckBox, wxCheckBox)
    EVT_CHECKBOX(-1, faustCheckBox::toggle)
END_EVENT_TABLE()

class faustHorizontalSlider : public wxSlider
{
	float	fStep;
	float*	fZone;
  public :
	faustHorizontalSlider(wxWindow* parent, float* zone, float init , float min, float max, float step)
			: wxSlider(parent, -1, int(init/step), int(min/step), int(max/step), wxDefaultPosition, wxSize(120,30), wxSL_HORIZONTAL), fStep(step), fZone(zone)
	{ 
		*fZone = init;
	}
  
  	void update (wxCommandEvent& ev)	{ 
		*fZone = GetValue()*fStep; 
		//printf("horizontal slider update : zone (at %p) = %f\n", fZone, *fZone); 
	}
	
 private:
	DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(faustHorizontalSlider, wxSlider)
	EVT_SLIDER (-1, faustHorizontalSlider::update)
END_EVENT_TABLE()

class faustVerticalSlider : public wxSlider
{
	float	fStep;
	float*	fZone;
  public :
	faustVerticalSlider(wxWindow* parent, float* zone, float init , float min, float max, float step)
			: wxSlider(parent, -1, int((max+min-init)/step), int(min/step), int(max/step), wxDefaultPosition, wxSize(30,120), wxSL_VERTICAL), fStep(step), fZone(zone)
	{ 
		*fZone = init;
	}
  
  	void update (wxCommandEvent& ev)	{ 
		*fZone = (GetMin()+GetMax()-GetValue())*fStep; 
		//printf("vertical slider update : zone (at %p) = %f\n", fZone, *fZone); 
	}
	
 private:
	DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(faustVerticalSlider, wxSlider)
	EVT_SLIDER (-1, faustVerticalSlider::update)
END_EVENT_TABLE()

//--------------------------------
// faustSpinCtrl* b = new faustSpinCtrl(topPanel(), zone, init, min, max, step);
//			wxSpinCtrl* b = new wxSpinCtrl( topPanel(), -1, "", wxPoint(200, 160), wxSize(80, -1) );
//    		b->SetRange(int(min),int(max));
//    		b->SetValue(int(init));		

class faustSpinCtrl : public wxSpinCtrl
{
	float	fStep;
	float*	fZone;
  public :
	faustSpinCtrl(wxWindow* parent, float* zone, float init , float min, float max, float step)
			: wxSpinCtrl(parent), fStep(step), fZone(zone)
	{ 
		SetRange(int(min),int(max));
		SetValue(int(init));
		*fZone = init;
	}
	
  	void update (wxCommandEvent& ev)	{ *fZone = GetValue(); printf("spin ctrl update : zone (at %p) = %f\n", fZone, *fZone); }
	
 private:
	DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(faustSpinCtrl, wxSlider)
	EVT_SPINCTRL (-1, faustSpinCtrl::update)
END_EVENT_TABLE()

class WXUI : public UI // user interface
{
	class State 
	{
		int			const fType;
		wxWindow*	const fPanel;
		wxSizer*	const fSizer;

	 public:
		State (int t, wxWindow* p, wxSizer* z) : fType(t), fPanel(p), fSizer(z) {}
		int			type() 	const { return fType; }
		wxWindow*	panel() const { return fPanel; }
		wxSizer*	sizer() const { return fSizer; }
	};
	
	stack<State> 		lState;
	wxFrame*			frame;
	wxSizer*			fSizer;
	
	// gestion de l'etat courant du constructeur
	
	void push (int t, wxWindow* p, wxSizer* z) 	
	{ 
		printf("push %d of %d, %p, %p\n", lState.size(), t, p, z);
		lState.push(State(t,p,z)); 
	}
 	
 	int			topType() 	{ return lState.top().type(); 	}
 	wxWindow*	topPanel() 	{ return lState.top().panel(); 	}
 	wxSizer*	topSizer() 	{ return lState.top().sizer(); 	}
	
	void pop ()									
	{ 
		printf("pop %d", lState.size()-1);
		lState.pop(); 			
		printf(" ok\n");
	}
		  
	void openAutoPage(char* label)
	{
		if (topType() == kNotebookState) {	
					
			if (!label) label = "";
		
    		wxNotebook*	nb 	= (wxNotebook*) topPanel();
    		wxPanel*	p 	= new wxPanel( nb, -1 );
    		wxBoxSizer*	z 	= new wxBoxSizer( wxVERTICAL );
			
    		nb->AddPage(p, label);
    		p->SetAutoLayout(TRUE);
    		p->SetSizer(z);
			
			push(kAutoPageState, p, z);
		}
	}
	
	void closeAutoPage()
	{
		if (topType() == kAutoPageState) pop(); 
	}
	
	void openOrientedBox(char* label, int orientation) 
	{
		openAutoPage(label);
		
		wxSizer* z = (label == 0) 	? new wxBoxSizer(orientation) 
									: new wxStaticBoxSizer(new wxStaticBox(topPanel(), -1, label), orientation);
		
		topSizer()->Add(z, 1, kFlag, kBorder);
		push(kNormalState, topPanel(), z);
	}
	
 public:

	WXUI(){}
	
	virtual ~WXUI() {}
	
	void openFrame(wxFrame* f) 
	{
		frame = f;
		fSizer = new wxBoxSizer(wxVERTICAL);
		frame->SetSizer(fSizer);
		push(kNormalState, frame, fSizer);
	}
		
	wxFrame* closeFrame()
	{
		fSizer->Fit(frame);
		fSizer->SetSizeHints(frame);
		return frame;
	}
	
	virtual void openHorizontalBox(char* label) {	openOrientedBox(label, wxHORIZONTAL); }
	virtual void openVerticalBox(char* label) 	{	openOrientedBox(label, wxVERTICAL); }
	
	virtual void openTabBox(char* label) 
	{
		openAutoPage(label);
		
    	wxNotebook*			nb 	= new wxNotebook( topPanel(), -1 );
    	wxNotebookSizer*	z 	= new wxNotebookSizer( nb );
		
		topSizer()->Add(z, 1, kFlag, kBorder);		
		push(kNotebookState, nb, z);
	}
	
	virtual void closeBox()
	{
		pop();
		closeAutoPage();
	}
				
	//--------------------------------- les elements ------------------------------------------
		
	virtual void addButton(char* label, float* zone) 
	{
		openAutoPage(label);
		faustButton* b = new faustButton(topPanel(), label, zone);
		topSizer()->Add(b, kProp, kFlag, kBorder);
		closeAutoPage();
	}
	
	virtual void addCheckButton(char* label, float* zone)  
	{
		openAutoPage(label);
		faustCheckBox* b = new faustCheckBox(topPanel(), label, zone);
		topSizer()->Add(b, kProp, kFlag, kBorder);
		closeAutoPage();
	}
			
	virtual void addVerticalSlider(char* label, float* zone, float init, float min, float max, float step) 
	{
		openAutoPage(label);
		if (label) {
			wxSizer* z = new wxStaticBoxSizer(new wxStaticBox(topPanel(), -1, label), wxHORIZONTAL);
			topSizer()->Add(z, 1, kFlag, kBorder);
			faustVerticalSlider* b = new faustVerticalSlider(topPanel(), zone, init, min, max, step);
			b->SetToolTip(label);
			z->Add(b, 1, kFlag|wxALIGN_CENTER_VERTICAL, kBorder);
		} else {
			faustVerticalSlider* b = new faustVerticalSlider(topPanel(), zone, init, min, max, step);
			topSizer()->Add(b, kProp, kFlag, kBorder);
		}
		closeAutoPage();
	}
	
	virtual void addHorizontalSlider(char* label, float* zone, float init, float min, float max, float step) 
	{
		openAutoPage(label);
		if (label) {
			wxSizer* z = new wxStaticBoxSizer(new wxStaticBox(topPanel(), -1, label), wxVERTICAL);
			topSizer()->Add(z, 1, kFlag, kBorder);
			faustHorizontalSlider* b = new faustHorizontalSlider(topPanel(), zone, init, min, max, step);
			b->SetToolTip(label);
			z->Add(b, 1, kFlag|wxALIGN_CENTER_HORIZONTAL, kBorder);
		} else {
			faustHorizontalSlider* b = new faustHorizontalSlider(topPanel(), zone, init, min, max, step);
			topSizer()->Add(b, kProp, kFlag, kBorder);
		}
		closeAutoPage();
	}
	
	virtual void addToggleButton(char* label, float* zone) {}	
	virtual void addNumEntry(char* label, float* zone, float init, float min, float max, float step) 
	{
		openAutoPage(label);
		if (label) {
			wxSizer* z = new wxStaticBoxSizer(new wxStaticBox(topPanel(), -1, label), wxVERTICAL);
			topSizer()->Add(z, 0, kFlag, kBorder);
			faustSpinCtrl* b = new faustSpinCtrl(topPanel(), zone, init, min, max, step);
//			wxSpinCtrl* b = new wxSpinCtrl( topPanel(), -1, "", wxPoint(200, 160), wxSize(80, -1) );
//    		b->SetRange(int(min),int(max));
//    		b->SetValue(int(init));
			b->SetToolTip(label);
			z->Add(b, 0, kFlag, kBorder);
		} else {
			faustSpinCtrl* b = new faustSpinCtrl(topPanel(), zone, init, min, max, step);
//			wxSpinCtrl* b = new wxSpinCtrl( topPanel(), -1, "", wxPoint(200, 160), wxSize(80, -1) );
//    		b->SetRange(int(min),int(max));
//    		b->SetValue(int(init));
			topSizer()->Add(b, kProp, kFlag, kBorder);
		}
		closeAutoPage();
	}
	virtual void openFrameBox(char* label) {}
};

/******************************************************************************
*******************************************************************************

							WXWINDOWS APPLICATION
								
*******************************************************************************
*******************************************************************************/

enum { ID_QUIT=1, ID_ABOUT };
 
 
class MyApp : public wxApp
{
	virtual bool OnInit();
};

class MyFrame : public wxFrame
{
 public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size) 
	: wxFrame(0, -1, title, pos, size)
 	{
		wxMenu* m = new wxMenu;
		m->Append(ID_ABOUT, "&About...");
		m->AppendSeparator();
		m->Append(ID_QUIT, "E&xit");
		
		wxMenuBar* b = new wxMenuBar;
		b->Append(m, "&File");
		SetMenuBar(b);
		CreateStatusBar();
		SetStatusText("hello...");
	}
	
	void OnQuit(wxCommandEvent& event)
	{
		Close(TRUE);
	}
	
	void OnAbout(wxCommandEvent& event)
	{
		wxMessageBox("message 1", "message 2", wxOK|wxICON_INFORMATION);
	}

 private:
	DECLARE_EVENT_TABLE()
};
 

 BEGIN_EVENT_TABLE(MyFrame, wxFrame)
		 EVT_MENU(ID_QUIT, MyFrame::OnQuit)
		 EVT_MENU(ID_ABOUT, MyFrame::OnAbout)
 END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

/******************************************************************************
*******************************************************************************

								MAIN PLAY THREAD

*******************************************************************************
*******************************************************************************/
	
// Scan Command Line Arguments

long lopt (char *argv[], char *name, long def) 
{
	int	i;
	for (i=0; argv[i]; i++) if (!strcmp(argv[i], name)) return atoi(argv[i+1]);
	return def;
}

//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------
float* 		inChannel[256];
float* 		outChannel[256];
int			fpb;

pthread_t	soundthread;
	
void* run_sound(void* ptr)
{
	AudioInterface*	audio = (AudioInterface*)ptr;
	
	setRealtimePriority();
	// Sound processing loop
	audio->write(fpb, outChannel);	
	audio->write(fpb, outChannel);	
	while (1) {
		if ( !audio->write(fpb, outChannel)) printf("w");	
		if ( !audio->read (fpb, inChannel)) printf("r");;	
		DSP.compute(fpb, inChannel, outChannel);
	}
	
	audio->close();
	return 0;
}

bool MyApp::OnInit()
{
	// create and init the audio interface card
	AudioInterface*	audio = new AudioInterface(
		AudioParam().frequency(lopt(argv, "--frequency", 44100)) 
					.buffering(lopt(argv, "--buffer", 128))
					//.mode( ((DSP.getNumInputs()>0)?kRead:0) | ((DSP.getNumOutputs()>0)?kWrite:0) )
	);
	audio->open();
	audio->info();
	
	MyFrame* frame = new MyFrame(argv[0], wxPoint(50,50), wxSize(-1, -1));

	wxMenu* m = new wxMenu;
	m->Append(ID_ABOUT, "&About...");
	m->AppendSeparator();
	m->Append(ID_QUIT, "E&xit");
		
	wxMenuBar* b = new wxMenuBar;
	b->Append(m, "&File");
		
	frame->SetMenuBar(b);
	frame->CreateStatusBar();
	frame->SetStatusText("hello...");
				
	WXUI* ui = new WXUI();
	ui->openFrame(frame);
	DSP.buildUserInterface((UI*)ui);
	ui->closeFrame();
	
	DSP.init(audio->getSamplingFrequency());
	fpb = audio->getFramesPerBuffer();	
	audio->allocChanGroup(inChannel,  max(audio->getNumInputs(),  DSP.getNumInputs()), fpb);
	audio->allocChanGroup(outChannel, max(audio->getNumOutputs(), DSP.getNumOutputs()), fpb);
	
	frame->Show(TRUE);
	SetTopWindow(frame);
	
	pthread_create(&soundthread, NULL, run_sound, audio);

	return TRUE;
}
