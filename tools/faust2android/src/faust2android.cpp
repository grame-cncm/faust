
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <math.h>


#ifndef FAUSTCLASS
#define FAUSTCLASS mydsp
#endif


//********************************************************
// Added elements
//********************************************************

#ifndef max
	#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef min
	#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

class UI
{

 public:

	UI() {
		//addaddHorizontalSlider
	}

	virtual ~UI() {}

	virtual void initUI(void) = 0;

    // -- widget's layouts

    virtual void openTabBox(const char* label) = 0;
    virtual void openHorizontalBox(const char* label) = 0;
    virtual void openVerticalBox(const char* label) = 0;
    virtual void closeBox() = 0;

    // -- active widgets

    virtual void addButton(const char* label, FAUSTFLOAT* zone) = 0;
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) = 0;
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;

    // -- passive widgets

    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;

	// -- metadata declarations

    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) {}
};

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
 	virtual void compute(int len, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 	= 0;
};

struct Meta
{
    virtual void declare(const char* key, const char* value) = 0;
};

class GUI : public UI {
	public:
	struct para {
		int cnt;
		int cntLay;
		int typeLay[10];
		const char *labelLay[10];
		int type[30];
		int layoutEl[30];
		const char *label[30];
		float *value[30];
		float init[30];
		float min[30];
		float max[30];
		float step[30];
	} params;

		virtual void initUI() {
			params.cnt=0;
			params.cntLay=0;
		};

		// -- widget's layouts

	    virtual void openTabBox(const char* label) {};
	    virtual void openHorizontalBox(const char* label) {
	    	params.typeLay[params.cntLay] = 0;
	    	params.labelLay[params.cntLay] = label;
	    	if(params.layoutEl[params.cnt]>1) params.layoutEl[params.cnt]++;
	    	else params.layoutEl[params.cnt] = 1;
	    	params.cntLay++;
	    };
	    virtual void openVerticalBox(const char* label) {
	    	params.typeLay[params.cntLay] = 1;
	    	params.labelLay[params.cntLay] = label;
	    	if(params.layoutEl[params.cnt]>1) params.layoutEl[params.cnt]++;
	    	else params.layoutEl[params.cnt] = 1;
	    	params.cntLay++;
	    };
	    virtual void closeBox() {};

	    // -- active widgets

	    virtual void addButton(const char* label, FAUSTFLOAT* zone) {
	    	params.type[params.cnt] = 0;
	    	params.label[params.cnt] = label;
	    	params.value[params.cnt] = zone;
	    	if(params.layoutEl[params.cnt]<1) params.layoutEl[params.cnt] = 0;
	    	params.cnt++;
	    };
	    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) {
	    	params.type[params.cnt] = 1;
	    	params.label[params.cnt] = label;
	    	params.value[params.cnt] = zone;
	    	if(params.layoutEl[params.cnt]<1) params.layoutEl[params.cnt] = 0;
	    	params.cnt++;
	    };
	    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {
	    	params.type[params.cnt] = 2;
	    	params.label[params.cnt] = label;
	    	params.value[params.cnt] = zone;
	    	params.init[params.cnt] = init;
	    	params.min[params.cnt] = min;
	    	params.max[params.cnt] = max;
	    	params.step[params.cnt] = step;
	    	if(params.layoutEl[params.cnt]<1) params.layoutEl[params.cnt] = 0;
	    	params.cnt++;
	    };
	    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {
	    	params.type[params.cnt] = 3;
	    	params.label[params.cnt] = label;
	    	params.value[params.cnt] = zone;
	    	params.init[params.cnt] = init;
	    	params.min[params.cnt] = min;
	    	params.max[params.cnt] = max;
	    	params.step[params.cnt] = step;
	    	if(params.layoutEl[params.cnt]<1) params.layoutEl[params.cnt] = 0;
	    	params.cnt++;
	    };
	    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {
	    	params.type[params.cnt] = 4;
	    	params.label[params.cnt] = label;
	    	params.value[params.cnt] = zone;
	    	params.init[params.cnt] = init;
	    	params.min[params.cnt] = min;
	    	params.max[params.cnt] = max;
	    	params.step[params.cnt] = step;
	    	if(params.layoutEl[params.cnt]<1) params.layoutEl[params.cnt] = 0;
	    	params.cnt++;
	    };

	    // -- passive widgets

	    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {};
	    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {};

		// -- metadata declarations

	    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) {}
};

//**************************************************************
// DSP class
//**************************************************************

<<includeIntrinsic>>

<<includeclass>>
