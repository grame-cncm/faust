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
#include <list>


// g++ -O3 -lm -lpthread `gtk-config --cflags --libs` ex2.cpp
 
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


inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }


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

		fInputBuffer = (short*) aligned_calloc(fInputBufferSize, 1);
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

		fOutputBuffer = (short*)aligned_calloc(fOutputBufferSize, 1);
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
			chan[c] = (float*) aligned_calloc (len, sizeof(float));
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


// callback pour les différents widgets
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

								DSP

*******************************************************************************
*******************************************************************************/


//---------------------------------------------------
// tableaux de buffers initialisés par allocChannels
//---------------------------------------------------

float* 	gInChannel[256];
float* 	gOutChannel[256];

void allocChannels (int size, int numInChan, int numOutChan) 
{
	
	assert (numInChan < 256);
	assert (numOutChan < 256);
	
	
	for (int i = 0; i < numInChan; i++) {
		gInChannel[i] = (float*) aligned_calloc (size, sizeof(float));
		for (int j = 0; j < size; j++) {
			gInChannel[i][j] = 0.0;
		}
	}
	
	for (int i = 0; i < numOutChan; i++) {
		gOutChannel[i] = (float*) aligned_calloc (size, sizeof(float));
		for (int j = 0; j < size; j++) {
			gOutChannel[i][j] = 0.0;
		}
	}
}



//----------------------------------------------------------------
//  définition du processeur de signal
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

int main(int argc, char *argv[] )
{
	gtk_init (&argc, &argv);
	UI* interface = new GTKUI(argv[0]);
	
	AudioInterface	audio (
		AudioParam().frequency(lopt(argv, "--frequency", 44100)) 
					.buffering(lopt(argv, "--buffer", 128))
					//.mode( ((DSP.getNumInputs()>0)?kRead:0) | ((DSP.getNumOutputs()>0)?kWrite:0) )
	);
	audio.open();
	audio.info();
	
	DSP.init(audio.getSamplingFrequency());
	DSP.buildUserInterface(interface);

	pthread_create(&guithread, NULL, run_ui, interface);
	
	float* 	inChannel[256];
	float* 	outChannel[256];
	int		fpb = audio.getFramesPerBuffer();
	
	audio.allocChanGroup(inChannel,  max(audio.getNumInputs(),  DSP.getNumInputs()), fpb);
	audio.allocChanGroup(outChannel, max(audio.getNumOutputs(), DSP.getNumOutputs()), fpb);
	setRealtimePriority();
	// Sound processing loop
	audio.write(fpb, outChannel);	
	audio.write(fpb, outChannel);	
	while(!interface->stopped()) {
		if ( !audio.write(fpb, outChannel)) printf("w");	
		if ( !audio.read (fpb, inChannel)) printf("r");;	
		DSP.compute(fpb, inChannel, outChannel);
	}
	
	audio.close();
	//wait(0);
  	return 0;
}
