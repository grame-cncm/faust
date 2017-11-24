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

#include <portaudio.h>

// linux : g++ -O3 -lm -lportaudio `wx-config --cflags --libs` ex2.cpp
// macosx: g++ karplus-strong.cpp  -D__WXMAC__ -DWXMAKINGDLL -lwx_mac-2.4 -ljack -o karplus

using namespace std ;
 

// abs is now predefined
//template<typename T> T abs (T a)			{ return (a<T(0)) ? -a : a; }


inline int		lsr (int x, int n)			{ return int(((unsigned int)x) >> n); }

inline int int2pow2 (int x)	{ int r=0; while ((1<<r)<x) r++; return r; }

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/


<<includeIntrinsic>>



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

								FAUST DSP

*******************************************************************************
*******************************************************************************/



//----------------------------------------------------------------
//  d�finition du processeur de signal
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
		
				
mydsp	DSP;




/******************************************************************************
*******************************************************************************

							PORT AUDIO INTERFACE

*******************************************************************************
*******************************************************************************/



//----------------------------------------------------------------------------
// 	number of physical input and output channels of the PA device
//----------------------------------------------------------------------------

int		gDevNumInChans;
int		gDevNumOutChans;


//----------------------------------------------------------------------------
// tables of noninterleaved input and output channels for FAUST
//----------------------------------------------------------------------------

float* 	gInChannel[256];
float* 	gOutChannel[256];


//----------------------------------------------------------------------------
// allocated the noninterleaved input and output channels for FAUST
//----------------------------------------------------------------------------

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

//----------------------------------------------------------------------------
// Port Audio Callback 
//----------------------------------------------------------------------------

static int audioCallback(const void *ibuf, void *obuf, unsigned long frames, const PaStreamCallbackTimeInfo*,  PaStreamCallbackFlags, void *)
{
	float* fInputBuffer = (float*) ibuf;
	float* fOutputBuffer = (float*) obuf;
		
	// split input samples
	for (unsigned long s = 0; s < frames; s++) {
		for (int c = 0; c < gDevNumInChans; c++) {
			gInChannel[c][s] = fInputBuffer[c + s*gDevNumInChans];
		}
	}
	
	// process samples
	DSP.compute(frames, gInChannel, gOutChannel);

	// merge output samples
	for (unsigned long s = 0; s < frames; s++) {
		for (int c = 0; c < gDevNumOutChans; c++) {
			fOutputBuffer[c + s*gDevNumOutChans] = gOutChannel[c][s];
		}
	}
			
    return 0;
}
		



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
 
#ifdef MACOSX 
  	void clickdown (wxCommandEvent& ev)	{ *fZone = 1.0; /*printf("click down : zone (at %p) = %f\n", fZone, *fZone); ev.Skip();*/}
  	void clickup (wxCommandEvent& ev)	{ *fZone = 0.0; /*printf("click up : zone (at %p) = %f\n", fZone, *fZone);ev.Skip();*/  }
#else
  	void clickdown (wxCommandEvent& ev)	{ *fZone = 1.0; /*printf("click down : zone (at %p) = %f\n", fZone, *fZone);*/ ev.Skip();}
  	void clickup (wxCommandEvent& ev)	{ *fZone = 0.0; /*printf("click up : zone (at %p) = %f\n", fZone, *fZone);*/ ev.Skip(); }
#endif	
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

BEGIN_EVENT_TABLE(faustSpinCtrl, wxSpinCtrl)
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

							WXWINDOWS TOP FRAME
								
*******************************************************************************
*******************************************************************************/


enum { ID_QUIT=1, ID_ABOUT };
 
 
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

		 

/******************************************************************************
*******************************************************************************

							WXWINDOWS MAIN APPLICATION

*******************************************************************************
*******************************************************************************/
	
// Scan Command Line Arguments

class MyApp : public wxApp
{
	PaStream* as;

	long lopt (char *name, long def) 
	{
		int	i;
		for (i=0; argv[i]; i++) if (!strcmp(argv[i], name)) return atoi(argv[i+1]);
		return def;
	}
	
	void pa_error(int err)
	{
		if (err != paNoError) {
			printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );
			exit(1);
		}
	}
	
	virtual bool OnInit()
	{
		MyFrame* frame = new MyFrame(argv[0], wxPoint(50,50), wxSize(-1, -1));
/*
		wxMenu* m = new wxMenu;
		m->Append(ID_ABOUT, "&About...");
		m->AppendSeparator();
		m->Append(ID_QUIT, "E&xit");

		wxMenuBar* b = new wxMenuBar;
		b->Append(m, "&File");

		frame->SetMenuBar(b);
		frame->CreateStatusBar();
		frame->SetStatusText("Faust dsp...");
*/
		WXUI* ui = new WXUI();
		ui->openFrame(frame);
		DSP.buildUserInterface((UI*)ui);
		ui->closeFrame();

		frame->Show(TRUE);
		SetTopWindow(frame);

		// initialize portaudio
		pa_error(Pa_Initialize());
	
		const PaDeviceInfo*	idev = Pa_GetDeviceInfo(Pa_GetDefaultInputDevice());
		const PaDeviceInfo*	odev = Pa_GetDeviceInfo(Pa_GetDefaultOutputDevice());

		long srate = (long)lopt(argv, "--frequency", 44100);
		int	fpb = lopt("--buffer", 128);

		gDevNumInChans 	= (DSP.getNumInputs() > 0) ? idev->maxInputChannels : 0 ;
		gDevNumOutChans = (DSP.getNumOutputs() > 0) ? odev->maxOutputChannels : 0;
        
        PaStreamParameters inputParameters;
        PaStreamParameters outputParameters;
        
        inputParameters.device = Pa_GetDefaultInputDevice();
        inputParameters.sampleFormat = paFloat32;
        inputParameters.channelCount = gDevNumInChans;
        inputParameters.hostApiSpecificStreamInfo = 0;
        
        outputParameters.device = Pa_GetDefaultOutputDevice();
        outputParameters.sampleFormat = paFloat32;
        outputParameters.channelCount = gDevNumOutChans;
        outputParameters.hostApiSpecificStreamInfo = 0;
        
        PaError err;
        if ((err = Pa_IsFormatSupported(
            ((gDevNumInChans > 0) ? &inputParameters : 0), 
            ((gDevNumOutChans > 0) ? &outputParameters : 0), srate)) != 0) {
            printf("stream format is not supported err = %d\n", err);
            exit(1);
        }

		printf("inchan = %d, outchan = %d, freq = %f\n", gDevNumInChans, gDevNumOutChans, srate);
		allocChannels(fpb, max(gDevNumInChans, DSP.getNumInputs()), max(gDevNumOutChans, DSP.getNumOutputs()));
		DSP.init(long(srate));
		pa_error(Pa_OpenDefaultStream(&as, gDevNumInChans, gDevNumOutChans, paFloat32, srate, fpb, audioCallback, 0));
		Pa_StartStream(as);

		return TRUE;
	}

	virtual int OnExit()
	{
		Pa_StopStream(as);
		Pa_CloseStream(as);
		return 0;
	}
};


IMPLEMENT_APP(MyApp)

