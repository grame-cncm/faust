#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <assert.h>
#include <string>
#include <vector>
#include <math.h>

#ifdef __APPLE__
#include <Carbon/Carbon.h>
#include <unistd.h>
#endif

using namespace std ;
	
	

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


inline int		lsr (int x, int n)			{ return int(((unsigned int)x) >> n); }

inline int int2pow2 (int x)	{ int r=0; while ((1<<r)<x) r++; return r; }


/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }

<<includeIntrinsic>>


/******************************************************************************
*******************************************************************************

								USER INTERFACE

*******************************************************************************
*******************************************************************************/

class UI
{
		bool fStopped;
		
	public:
			
		UI() : fStopped(false) {}
		virtual ~UI() {}
		
		virtual void addButton(char* label, float* zone) = 0;
		virtual void addToggleButton(char* label, float* zone) = 0;
		virtual void addCheckButton(char* label, float* zone) = 0;
		virtual void addVerticalSlider(char* label, float* zone, float init, float min, float max, float step) = 0;
		virtual void addHorizontalSlider(char* label, float* zone, float init, float min, float max, float step) = 0;
		virtual void addNumEntry(char* label, float* zone, float init, float min, float max, float step) = 0;
		
		virtual void addNumDisplay(char* label, float* zone, int precision) = 0;
		virtual void addTextDisplay(char* label, float* zone, char* names[], float min, float max) = 0;
		virtual void addHorizontalBargraph(char* label, float* zone, float min, float max) = 0;
		virtual void addVerticalBargraph(char* label, float* zone, float min, float max) = 0;
		
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

				
/* Faust code wrapper ------- */

#include "ext.h"
#include "z_dsp.h"
#include <string.h>

#define ASSIST_INLET 	1  		/* should be defined somewhere ?? */
#define ASSIST_OUTLET 	2		/* should be defined somewhere ?? */

class mspUI;


/*--------------------------------------------------------------------------*/
typedef struct faust
{
	t_pxobject m_ob;
	t_atom *m_seen,*m_want;
	short m_where;
	void** args;
	mspUI* dspUI;
	mydsp* dsp;
} t_faust;

void *faust_class;

/*--------------------------------------------------------------------------*/
class mspUIObject {

	protected:
		
		string fLabel;
		float* fZone;
		
		float range(float min, float max, float val) {return (val < min) ? min : (val > max) ? max : val;}
	
	public:
			
		mspUIObject(char* label, float* zone):fLabel(label),fZone(zone) {}
		virtual ~mspUIObject() {}
		
		virtual void SetValue(double f) {*fZone = range(0.0,1.0,f);}
		virtual void toString(char* buffer) {}
};

/*--------------------------------------------------------------------------*/
class mspToggleButton : public mspUIObject {
	
	public:	
	
		mspToggleButton(char* label, float* zone):mspUIObject(label,zone) {}
		virtual ~mspToggleButton() {}
				
		void toString(char* buffer)
		{
		#ifdef WIN32
            sprintf(buffer, "ToggleButton(float): %s", fLabel.c_str());
		#else
			std::sprintf(buffer, "ToggleButton(float): %s", fLabel.c_str());
		#endif	
		}
};

/*--------------------------------------------------------------------------*/
class mspCheckButton : public mspUIObject {
	
	public:
	
		mspCheckButton(char* label, float* zone):mspUIObject(label,zone) {}	
		virtual ~mspCheckButton() {}
		
		void toString(char* buffer)
		{
		#ifdef WIN32
            sprintf(buffer, "CheckButton(float): %s", fLabel.c_str());
		#else
			std::sprintf(buffer, "CheckButton(float): %s", fLabel.c_str());
		#endif
		}
};

/*--------------------------------------------------------------------------*/
class mspButton : public mspUIObject {
	
	public:
	
		mspButton(char* label, float* zone):mspUIObject(label,zone) {}
		virtual ~mspButton() {}		
		
		void toString(char* buffer)
		{
		#ifdef WIN32
            sprintf(buffer, "Button(float): %s", fLabel.c_str());
		#else
			std::sprintf(buffer, "Button(float): %s", fLabel.c_str());
		#endif
		}	
};

/*--------------------------------------------------------------------------*/
class mspSlider : public mspUIObject{

	private:
	
		float fInit;
		float fMin;
		float fMax;
		float fStep;
	
	public:	
	
		mspSlider(char* label, float* zone, float init, float min, float max, float step)
			:mspUIObject(label,zone),fInit(init),fMin(min),fMax(max),fStep(step) {}
		virtual ~mspSlider() {}	
		
		void toString(char* buffer)
		{
		#ifdef WIN32
            sprintf(buffer, "Slider(float): %s [%.1f:%.1f:%.1f]", fLabel.c_str(), fMin, fInit, fMax);
		#else
			std::sprintf(buffer, "Slider(float): %s [%.1f:%.1f:%.1f]", fLabel.c_str(), fMin, fInit, fMax);
		#endif
		}
		
		void SetValue(double f) {*fZone = range(fMin,fMax,f);}
};

/*--------------------------------------------------------------------------*/
class mspUI : public UI
{
	private:
	
		vector<mspUIObject*> fUITable;
		
	public:
			
		mspUI(){}
		virtual ~mspUI() 
		{
			for (vector<mspUIObject*>::iterator iter = fUITable.begin(); iter != fUITable.end(); iter++) 
				delete *iter;
   		}
		
		void addButton(char* label, float* zone) {fUITable.push_back(new mspButton(label, zone));}
		
		void addToggleButton(char* label, float* zone) {fUITable.push_back(new mspToggleButton(label, zone));}
		
		void addCheckButton(char* label, float* zone) {fUITable.push_back(new mspCheckButton(label, zone));}
		
		void addVerticalSlider(char* label, float* zone, float init, float min, float max, float step) 
		{ 	
			fUITable.push_back(new mspSlider(label, zone, init, min, max, step));
		}
		
		void addHorizontalSlider(char* label, float* zone, float init, float min, float max, float step) 
		{
			fUITable.push_back(new mspSlider(label, zone, init, min, max, step));
		}
		
		void addNumEntry(char* label, float* zone, float init, float min, float max, float step)
		{
			fUITable.push_back(new mspSlider(label, zone, init, min, max, step));
		}
		
		void openFrameBox(char* label) {}
		void openTabBox(char* label) {}
		void openHorizontalBox(char* label) {}
		void openVerticalBox(char* label) {}
		void closeBox() {}
		
		void SetValue(int slider, double f) 
		{
			assert(slider<fUITable.size()); 
			fUITable[slider]->SetValue(f);
		}
		
		void UIObject2String(char* buffer,int slider) 
		{
			if (fUITable[slider]) 
				fUITable[slider]->toString(buffer);
		}
		
		bool AddInlets(t_faust *x) 
		{
			if (fUITable.size() > 9) return false;
			for (int i = fUITable.size(); i>0 ; i--) 
				floatin((t_pxobject *)x,i);
			return true;
		}
		
		// To be implemented
		void addNumDisplay(char* label, float* zone, int precision){}
		void addTextDisplay(char* label, float* zone, char* names[], float min, float max){}
		void addHorizontalBargraph(char* label, float* zone, float min, float max){}
		void addVerticalBargraph(char* label, float* zone, float min, float max){}
};

/*--------------------------------------------------------------------------*/
void faust_ft1(t_faust* obj, double f) {obj->dspUI->SetValue(0,f);}
void faust_ft2(t_faust* obj, double f) {obj->dspUI->SetValue(1,f);}
void faust_ft3(t_faust* obj, double f) {obj->dspUI->SetValue(2,f);}
void faust_ft4(t_faust* obj, double f) {obj->dspUI->SetValue(3,f);}
void faust_ft5(t_faust* obj, double f) {obj->dspUI->SetValue(4,f);}
void faust_ft6(t_faust* obj, double f) {obj->dspUI->SetValue(5,f);}
void faust_ft7(t_faust* obj, double f) {obj->dspUI->SetValue(6,f);}
void faust_ft8(t_faust* obj, double f) {obj->dspUI->SetValue(7,f);}
void faust_ft9(t_faust* obj, double f) {obj->dspUI->SetValue(8,f);}

/*--------------------------------------------------------------------------*/
void *faust_new(t_symbol *s, short ac, t_atom *av)
{
	t_faust *x = (t_faust *)newobject(faust_class);
		
	x->dsp = new mydsp();
	x->dspUI= new mspUI();
	
	x->dsp->init(long(sys_getsr()));
	x->dsp->buildUserInterface(x->dspUI);
	if (!x->dspUI->AddInlets(x)) {
		post("Error : Faust DSP object cannot be allocated: max inlets is 9");
//		faust_free(x); should be freed but Max crashes 
		return 0;
	}
	
	x->args = (void**)aligned_calloc((x->dsp->getNumInputs()+x->dsp->getNumOutputs())+2, sizeof(void*));
	
	/* Multi in */
	dsp_setup((t_pxobject *)x, x->dsp->getNumInputs());
	
	/* Multi out */
	for (int i = 0; i< x->dsp->getNumOutputs(); i++) 
		outlet_new((t_pxobject *)x, "signal");
	
	((t_pxobject *)x)->z_misc = Z_NO_INPLACE; // To assure input and output buffers are actually different
	return x;
}			

/*--------------------------------------------------------------------------*/
void faust_assist(t_faust *x, void *b, long msg, long a, char *dst)
{
    if (msg == ASSIST_INLET) {
        if (a == 0) {
            if (x->dsp->getNumInputs() == 0) {
			#ifdef WIN32
                sprintf(dst, "(signal) : Unused Input");
			#else
				std::sprintf(dst, "(signal) : Unused Input");
			#endif
            } else {
			#ifdef WIN32
                sprintf(dst, "(signal) : Audio Input %ld", (a+1));
			#else
				std::sprintf(dst, "(signal) : Audio Input %ld", (a+1));
			#endif
			}
        } else if (a < x->dsp->getNumInputs()) {
		#ifdef WIN32
            sprintf(dst, "(signal) : Audio Input %ld", (a+1));
		#else
			std::sprintf(dst, "(signal) : Audio Input %ld", (a+1));
		#endif
        } else {
            x->dspUI->UIObject2String(dst,a - max(1,x->dsp->getNumInputs()));
        }
    } else if (msg == ASSIST_OUTLET) {
	#ifdef WIN32
        sprintf(dst, "(signal) : Audio Output %ld", (a+1));
	#else
		std::sprintf(dst, "(signal) : Audio Output %ld", (a+1));
	#endif
    }
}

/*--------------------------------------------------------------------------*/
void faust_free(t_faust *x)
{
	dsp_free((t_pxobject *)x);
	if (x->dsp) delete x->dsp;
	if (x->dspUI) delete x->dspUI;
	if (x->args)free(x->args);
}

/*--------------------------------------------------------------------------*/
t_int *faust_perform(t_int *w)
{
	t_faust* x = (t_faust*) (w[1]);
	long n = w[2];
	int offset = 3;
	x->dsp->compute(n, ((float**)&w[offset]), ((float**)&w[offset+x->dsp->getNumInputs()]));
	return (w + (x->dsp->getNumInputs()+x->dsp->getNumOutputs())+2+1);
}

/*--------------------------------------------------------------------------*/
void  faust_dsp(t_faust *x, t_signal **sp, short *count)
{
	x->args[0] = x;
	x->args[1] = (void*)sp[0]->s_n;
	for (int i = 0; i<(x->dsp->getNumInputs()+x->dsp->getNumOutputs()); i++) 
		x->args[i+2] = sp[i]->s_vec;
	dsp_addv(faust_perform, (x->dsp->getNumInputs()+x->dsp->getNumOutputs())+2, x->args);
}

/*--------------------------------------------------------------------------*/
int main()
{
	setup((t_messlist **)&faust_class, (method)faust_new, (method)faust_free, 
		(short)sizeof(t_faust), 0L, A_DEFFLOAT, 0);

	// External can have up to 9 inlets
	addftx((method)faust_ft1,1);
	addftx((method)faust_ft2,2);
	addftx((method)faust_ft3,3);
	addftx((method)faust_ft4,4);
	addftx((method)faust_ft5,5);
	addftx((method)faust_ft6,6);
	addftx((method)faust_ft7,7);
	addftx((method)faust_ft8,8);
	addftx((method)faust_ft9,9);
	
	addmess((method)faust_dsp, "dsp", A_CANT, 0);
	addmess((method)faust_assist, "assist", A_CANT, 0);
	dsp_initclass();
	post("Faust DSP object");
	return 0;
}




