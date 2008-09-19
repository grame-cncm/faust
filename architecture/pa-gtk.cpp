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
#include <gtk/gtk.h>
#include <pthread.h> 
#include <sys/wait.h>
#include <list>

#include <portaudio.h>

// g++ -O3 -lm -lportaudio `gtk-config --cflags --libs` ex2.cpp
 
	
#ifdef __GNUC__

//-------------------------------------------------------------------
// Generic min and max using gcc extensions
//-------------------------------------------------------------------

#define max(x,y) ((x)>?(y))
#define min(x,y) ((x)<?(y))

//abs(x) should be already predefined

#else

//-------------------------------------------------------------------
// Generic min and max using c++ inline
//-------------------------------------------------------------------

inline int 		max (unsigned int a, unsigned int b) { return (a>b) ? a : b; }
inline int 		max (int a, int b) 			{ return (a>b) ? a : b; }

inline long 	max (long a, long b) 		{ return (a>b) ? a : b; }
inline long 	max (int a, long b) 		{ return (a>b) ? a : b; }
inline long 	max (long a, int b) 		{ return (a>b) ? a : b; }

inline float 	max (float a, float b) 		{ return (a>b) ? a : b; }
inline float 	max (int a, float b) 		{ return (a>b) ? a : b; }
inline float 	max (float a, int b) 		{ return (a>b) ? a : b; }
inline float 	max (long a, float b) 		{ return (a>b) ? a : b; }
inline float 	max (float a, long b) 		{ return (a>b) ? a : b; }

inline double 	max (double a, double b) 	{ return (a>b) ? a : b; }
inline double 	max (int a, double b) 		{ return (a>b) ? a : b; }
inline double 	max (double a, int b) 		{ return (a>b) ? a : b; }
inline double 	max (long a, double b) 		{ return (a>b) ? a : b; }
inline double 	max (double a, long b) 		{ return (a>b) ? a : b; }
inline double 	max (float a, double b) 	{ return (a>b) ? a : b; }
inline double 	max (double a, float b) 	{ return (a>b) ? a : b; }


inline int 		min (int a, int b) 			{ return (a<b) ? a : b; }

inline long 	min (long a, long b) 		{ return (a<b) ? a : b; }
inline long 	min (int a, long b) 		{ return (a<b) ? a : b; }
inline long 	min (long a, int b) 		{ return (a<b) ? a : b; }

inline float 	min (float a, float b) 		{ return (a<b) ? a : b; }
inline float 	min (int a, float b) 		{ return (a<b) ? a : b; }
inline float 	min (float a, int b) 		{ return (a<b) ? a : b; }
inline float 	min (long a, float b) 		{ return (a<b) ? a : b; }
inline float 	min (float a, long b) 		{ return (a<b) ? a : b; }

inline double 	min (double a, double b) 	{ return (a<b) ? a : b; }
inline double 	min (int a, double b) 		{ return (a<b) ? a : b; }
inline double 	min (double a, int b) 		{ return (a<b) ? a : b; }
inline double 	min (long a, double b) 		{ return (a<b) ? a : b; }
inline double 	min (double a, long b) 		{ return (a<b) ? a : b; }
inline double 	min (float a, double b) 	{ return (a<b) ? a : b; }
inline double 	min (double a, float b) 	{ return (a<b) ? a : b; }
		
#endif

// abs is now predefined
//template<typename T> T abs (T a)			{ return (a<T(0)) ? -a : a; }


inline int		lsr (int x, int n)			{ return int(((unsigned int)x) >> n); }

inline int int2pow2 (int x)	{ int r=0; while ((1<<r)<x) r++; return r; }


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

								USER INTERFACE

*******************************************************************************
*******************************************************************************/


#define stackSize 256

// les modes d'insertion

#define kSingleMode 0
#define kBoxMode 1
#define kTabMode 2

typedef GtkWidget* gtkptr;


class UI
{
	bool	fStopped;
public:
		
	UI() : fStopped(false) {}
	virtual ~UI() {}
	
 	static const gboolean expand = TRUE;
	static const gboolean fill = TRUE;
	static const gboolean homogene = FALSE;
	
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
	
	virtual void run() = 0;
	
	void stop()		{ fStopped = true; }
	bool stopped() 	{ return fStopped; }
};


float myZone;

		
static gint delete_event( GtkWidget *widget, GdkEvent *event, gpointer data )
{
    //g_print ("delete event occurred\n");
    return FALSE; 
}

static void destroy_event( GtkWidget *widget, gpointer data )
{
    //g_print ("destroy event occurred\n");
    gtk_main_quit ();
}


// callback pour les diff�rents widgets
//-------------------------------------

void pressed( GtkWidget *widget, gpointer   data )
{
	float * zone = (float*) data;
	
	*zone = 1.0;
    //g_print ("Button - zone was pressed : %f\n", *zone);
}

void released( GtkWidget *widget, gpointer   data )
{
	float * zone = (float*) data;
	
	*zone = 0.0;
    //g_print ("Button - zone was released : %f\n", *zone);
}

void toggled (GtkWidget *widget, gpointer data)
{
	float * zone = (float*) data;
	
    if (GTK_TOGGLE_BUTTON (widget)->active) 
    {
		*zone = 1.0;
    	//g_print ("Toggle - zone was pressed : %f\n", *zone);
   
    } else {
		*zone = 0.0;
    	//g_print ("Toggle - zone was unpressed : %f\n", *zone);
    }
}

void changed (GtkAdjustment *adjustment, gpointer data)
{
	float * zone = (float*) data;
	*zone = adjustment->value;
   	//g_print ("Adjustment - zone was changed : %f\n", *zone);
}



class GTKUI : public UI
{
	GtkWidget* 	fWindow;
	int			fTop;
	GtkWidget* 	fBox[stackSize];
	int 		fMode[stackSize];
	bool		fStopped;
		
 public :
		 
	GTKUI(char * name) 
	{
		
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
	
	virtual void pushBox(int mode, GtkWidget* w)
	{
		assert(++fTop < stackSize);
		fMode[fTop] 	= mode;
		fBox[fTop] 		= w;
	}
	
	virtual void closeBox()
	{
		assert(--fTop >= 0);
	}
	
	// ajout dans la boite courante 
	
	GtkWidget* addWidget(char* label, GtkWidget* w)
	{ 
		switch (fMode[fTop]) {
			case kSingleMode	: gtk_container_add (GTK_CONTAINER(fBox[fTop]), w); 				break;
			case kBoxMode 		: gtk_box_pack_start (GTK_BOX(fBox[fTop]), w, expand, fill, 0); 	break;
			case kTabMode 		: gtk_notebook_append_page (GTK_NOTEBOOK(fBox[fTop]), w, gtk_label_new(label)); break;
		}
    	gtk_widget_show (w);
		return w;
	}

	
	// les differentes boites
	
	virtual void openFrameBox(char* label)
	{
		GtkWidget * box = gtk_frame_new (label);
		//gtk_container_set_border_width (GTK_CONTAINER (box), 10);
				
		pushBox(kSingleMode, addWidget(label, box));
	}
	
	virtual void openTabBox(char* label = "")
	{
		pushBox(kTabMode, addWidget(label, gtk_notebook_new ()));
	}

	virtual void openHorizontalBox(char* label = "")
	{	
		GtkWidget * box = gtk_hbox_new (homogene, 4);
		gtk_container_set_border_width (GTK_CONTAINER (box), 10);
				
		if (fMode[fTop] != kTabMode && label[0] != 0) {
			GtkWidget * frame = addWidget(label, gtk_frame_new (label));
			gtk_container_add (GTK_CONTAINER(frame), box);
			gtk_widget_show(box);
			pushBox(kBoxMode, box);
		} else {
			pushBox(kBoxMode, addWidget(label, box));
		}
	}

	virtual void openVerticalBox(char* label = "")
	{
		GtkWidget * box = gtk_vbox_new (homogene, 4);
		gtk_container_set_border_width (GTK_CONTAINER (box), 10);
				
		if (fMode[fTop] != kTabMode && label[0] != 0) {
			GtkWidget * frame = addWidget(label, gtk_frame_new (label));
			gtk_container_add (GTK_CONTAINER(frame), box);
			gtk_widget_show(box);
			pushBox(kBoxMode, box);
		} else {
			pushBox(kBoxMode, addWidget(label, box));
		}
	}
	
	virtual void addButton(char* label, float* zone)
	{
		GtkWidget* 	button = gtk_button_new_with_label (label);
		
		addWidget(label, button);
    	gtk_signal_connect (GTK_OBJECT (button), "pressed", GTK_SIGNAL_FUNC (pressed), (gpointer) zone);
    	gtk_signal_connect (GTK_OBJECT (button), "released", GTK_SIGNAL_FUNC (released), (gpointer) zone);

	}
	
	
	virtual void addToggleButton(char* label, float* zone)
	{
		GtkWidget* 	button = gtk_toggle_button_new_with_label (label);
		
		addWidget(label, button);
    	gtk_signal_connect (GTK_OBJECT (button), "toggled", GTK_SIGNAL_FUNC (toggled), (gpointer) zone);
	}
	
	
	virtual void addCheckButton(char* label, float* zone)
	{
		GtkWidget* 	button = gtk_check_button_new_with_label (label);
		
		addWidget(label, button);
    	gtk_signal_connect (GTK_OBJECT (button), "toggled", GTK_SIGNAL_FUNC (toggled), (gpointer) zone);
	}
	
	static int precision(float n)
	{
		int p = 0;
		if (n>0) while (n<1.0) { p++; n*=10; }
		fprintf(stderr, "precision = %d\n", p);
		return p;
	}
	
	
	virtual void addVerticalSlider(char* label, float* zone, float init, float min, float max, float step)
	{
		*zone = init;
		GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, step);
    	gtk_signal_connect (GTK_OBJECT (adj), "value-changed", GTK_SIGNAL_FUNC (changed), (gpointer) zone);
		
		GtkWidget* slider = gtk_vscale_new (GTK_ADJUSTMENT(adj));
		gtk_scale_set_digits(GTK_SCALE(slider), precision(step));
		gtk_widget_set_usize(slider, -1, 160);
		openFrameBox(label);
		addWidget(label, slider);
		closeBox();
	}
	
	
	virtual void addHorizontalSlider(char* label, float* zone, float init, float min, float max, float step)
	{
		*zone = init;
		GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, step);
    	gtk_signal_connect (GTK_OBJECT (adj), "value-changed", GTK_SIGNAL_FUNC (changed), (gpointer) zone);
		
		GtkWidget* slider = gtk_hscale_new (GTK_ADJUSTMENT(adj));
		gtk_scale_set_digits(GTK_SCALE(slider), precision(step));
		gtk_widget_set_usize(slider, 160, -1);
		openFrameBox(label);
		addWidget(label, slider);
		closeBox();
	}
	
	virtual void addNumEntry(char* label, float* zone, float init, float min, float max, float step)
	{
		*zone = init;
		GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, step);
    	gtk_signal_connect (GTK_OBJECT (adj), "value-changed", GTK_SIGNAL_FUNC (changed), (gpointer) zone);
		
		GtkWidget* spinner = gtk_spin_button_new (GTK_ADJUSTMENT(adj), 0.001, precision(step));

		//gtk_widget_set_usize(slider, 160, -1);
		openFrameBox(label);
		addWidget(label, spinner);
		closeBox();
	}
	
	virtual void run() 
	{
		assert(fTop == 0);
    	gtk_widget_show  (fBox[0]);
    	gtk_widget_show  (fWindow);
    	gtk_main ();
		stop();
	}
	
	
};


pthread_t	guithread;
	
void* run_ui(void* ptr)
{
	UI* interface = (UI*) ptr;
	interface->run();
	pthread_exit(0);
	return 0;
}


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
		

//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------
		
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
		gInChannel[i] = (float*) alloc (size, sizeof(float));
		for (int j = 0; j < size; j++) {
			gInChannel[i][j] = 0.0;
		}
	}
	
	for (int i = 0; i < numOutChan; i++) {
		gOutChannel[i] = (float*) alloc (size, sizeof(float));
		for (int j = 0; j < size; j++) {
			gOutChannel[i][j] = 0.0;
		}
	}
}


//----------------------------------------------------------------------------
// Search the best (closest) sample rate 
//----------------------------------------------------------------------------

double searchBestSampleRate(const PaDeviceInfo* dev, double requestedRate)
{
	if (dev->numSampleRates == -1) {
		double minRate = min(dev->sampleRates[0], dev->sampleRates[1]);
		double maxRate = max(dev->sampleRates[0], dev->sampleRates[1]);
		if (requestedRate <= minRate) return minRate;
		if (requestedRate >= maxRate) return maxRate;
		return requestedRate;
	} else {
		double bestDiff = abs(dev->sampleRates[0] - requestedRate);
		double bestRate = dev->sampleRates[0];
		for (int j=1; j<dev->numSampleRates; j++ ) {
			double diff = abs(dev->sampleRates[j] - requestedRate);
			if (diff < bestDiff) {
				bestDiff = diff;
				bestRate = dev->sampleRates[j];
			}
		}
		return bestRate;
	}
}


//----------------------------------------------------------------------------
// Port Audio Callback 
//----------------------------------------------------------------------------

static int audioCallback( void *ibuf, void *obuf, unsigned long frames, PaTimestamp, void * )
{
	float* fInputBuffer = (float*) ibuf;
	float* fOutputBuffer = (float*) obuf;
		
	// split input samples
	for (int s = 0; s < frames; s++) {
		for (int c = 0; c < gDevNumInChans; c++) {
			gInChannel[c][s] = fInputBuffer[c + s*gDevNumInChans];
		}
	}
	
	// process samples
	DSP.compute(frames, gInChannel, gOutChannel);

	// merge output samples
	for (int s = 0; s < frames; s++) {
		for (int c = 0; c < gDevNumOutChans; c++) {
			fOutputBuffer[c + s*gDevNumOutChans] = gOutChannel[c][s];
		}
	}
			
    return 0;
}
		




/******************************************************************************
*******************************************************************************

								MAIN PLAY THREAD

*******************************************************************************
*******************************************************************************/
	
	
	
//-------------------------------------------------------------------------
// 							Scan Command Line Arguments
//-------------------------------------------------------------------------

long lopt (char *argv[], char *name, long def) 
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
//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------

int main(int argc, char *argv[] )
{
	gtk_init (&argc, &argv);
	
	UI* 				interface = new GTKUI(argv[0]);
	PortAudioStream*	as;
	
	
	pa_error( Pa_Initialize() );
	
	const PaDeviceInfo*	idev = Pa_GetDeviceInfo(Pa_GetDefaultInputDeviceID());
	const PaDeviceInfo*	odev = Pa_GetDeviceInfo(Pa_GetDefaultOutputDeviceID());
	
	double 	srate 	= searchBestSampleRate(odev, lopt(argv, "--frequency", 44100));
	int		fpb 	= lopt(argv, "--buffer", 128);
	
	gDevNumInChans 	= (DSP.getNumInputs() > 0) ? idev->maxInputChannels : 0 ;
	gDevNumOutChans = (DSP.getNumOutputs() > 0) ? odev->maxOutputChannels : 0;
	
	printf("inchan = %d, outchan = %d, freq = %f\n", gDevNumInChans, gDevNumOutChans, srate);
	
	
	allocChannels( fpb, max(gDevNumInChans,  DSP.getNumInputs()), max(gDevNumOutChans, DSP.getNumOutputs()) );
	
	DSP.init(long(srate));
	DSP.buildUserInterface(interface);

			
	pa_error( Pa_OpenDefaultStream( &as, gDevNumInChans, gDevNumOutChans, paFloat32, srate, fpb, 0, audioCallback, 0) );
	
	Pa_StartStream(as);
	interface->run();
	Pa_StopStream(as);
	
	Pa_CloseStream(as);
  	return 0;
}

