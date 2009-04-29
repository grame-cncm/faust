//==============================================================================
//
//          CSOUND architecture file for FAUST
//          Y. Orlarey & V. Lazzarini
//
//          Usage : faust -uim -a csound.cpp <myfx>.dsp -o <myfx>.cpp
//                  g++ -O3 -DOPCODE_NAME=<myfx> -c <myfx>.cpp -o <myfx>.o
//                  ld -E --shared <myfx>.o -o <myfx>.so
//
//          History :
//          - 28/04/09 : first version
//          - 29/04/09 : dynamic allocation
//
//==============================================================================

#include <new>
#include <vector>
#include "csdl.h"                       /* CSOUND plugin API header */

// used to transform a symbol in a string
#define sym(name) xsym(name)
#define xsym(name) #name


// we require macro declarations
#define FAUST_UIMACROS

// but we will ignore most of them 
#define FAUST_ADDBUTTON(l,f)
#define FAUST_ADDCHECKBOX(l,f)
#define FAUST_ADDVERTICALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDHORIZONTALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDNUMENTRY(l,f,i,a,b,s)
#define FAUST_ADDVERTICALBARGRAPH(l,f,a,b)
#define FAUST_ADDHORIZONTALBARGRAPH(l,f,a,b)

#define max(x,y) (((x)>(y)) ? (x) : (y))
#define min(x,y) (((x)<(y)) ? (x) : (y))

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




/******************************************************************************
*******************************************************************************

                                   VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/


<<includeIntrinsic>>



/**
 * We will ignore metadata declarations
 */
struct Meta 
{
    void declare (const char* key, const char* value) { }
};

/**
 * Abstract Definition of a user interface
 */
class UI 
{
 public:
        
    virtual ~UI() {}

    // -- active widgets
    
    virtual void addButton(const char* label, float* zone) = 0;
    virtual void addToggleButton(const char* label, float* zone) = 0;
    virtual void addCheckButton(const char* label, float* zone) = 0;
    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) = 0;
    
    // -- passive widgets
    
    virtual void addNumDisplay(const char* label, float* zone, int precision)                           {}
    virtual void addTextDisplay(const char* label, float* zone, char* names[], float min, float max)    {}
    virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max)            {}
    virtual void addVerticalBargraph(const char* label, float* zone, float min, float max)              {}
    
    // -- widget's layouts
    
    virtual void openFrameBox(const char* label)                                                        {}
    virtual void openTabBox(const char* label)                                                          {}
    virtual void openHorizontalBox(const char* label)                                                   {}
    virtual void openVerticalBox(const char* label)                                                     {}
    virtual void closeBox()                                                                             {}

    virtual void declare(float* zone, const char* key, const char* value) {}
};

/**
 * A UI that simply collects the active zones in a vector
 * and provides a method to copy the csound controls
 */
class CSUI : public UI
{
    vector<float*>  vZone;

 public:
    // -- active widgets
    
    virtual void addButton(const char* label, float* zone)                                                          { vZone.push_back(zone); }
    virtual void addToggleButton(const char* label, float* zone)                                                    { vZone.push_back(zone); }
    virtual void addCheckButton(const char* label, float* zone)                                                     { vZone.push_back(zone); }
    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)    { vZone.push_back(zone); }
    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)  { vZone.push_back(zone); }
    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step)          { vZone.push_back(zone); }

    void copyfrom(MYFLT* mem[]) {
        for (unsigned int i=0; i<vZone.size(); i++) { *vZone[i] = *(mem[i]); }
    }

    int size()                  { return vZone.size(); }
};



/**
 * Abstract Definition of a DSP
 */


class dsp {
 protected:
    int fSamplingFreq;
  public:
    virtual int getNumInputs() = 0;
    virtual int getNumOutputs() = 0;
    virtual void instanceInit(int samplingFreq) = 0;
    virtual void init(int samplingFreq)= 0;
    virtual void buildUserInterface(UI* interface) = 0;
    virtual void compute (int count, float** input, float** output) = 0;
};

/**
 * FAUST generated code goes here
 *
 *           |  |
 *           v  v
 */
<<includeclass>>


struct dataspace {
    OPDS      h;                          /* basic attributes */
    MYFLT*    aout[FAUST_OUTPUTS];        /* output buffers   */
    MYFLT*    ain[FAUST_INPUTS];          /* input buffers    */
    MYFLT*    ktl[FAUST_ACTIVES];         /* controls         */
    dsp*      DSP;                        /* the Faust generated object */
    CSUI*     interface;                  /* do the mapping between CSound controls and DSP fields */
    AUXCH     dspmem;                     /* aux memory allocated once to store the DSP object */
    AUXCH     intmem;                     /* aux memory allocated once to store the interface object */
};


/**
 * Creates a "aaakkkk" CSound description string. Note that
 * these string will never be released. Potential memory leak
 */
static char* makeDescription(int numa, int numk=0)
{
    char* str = (char*)malloc(numa+numk+1); // NEED TO BE CHANGED ?
    if (str) {
        for (int i=0; i<numa; i++) str[i] = 'a';
        for (int i=0; i<numk; i++) str[numa+i] = 'k';
        str[numa+numk] = 0;
    }
    return str;
}


/**
 * CSOUND callback that allocates and initializes
 * the FAUST generated DSP object and it's CSound interface
 */
static int init(CSOUND *csound, dataspace *p)
{
    if (p->dspmem.auxp == NULL)
        csound->AuxAlloc(csound, sizeof(mydsp), &p->dspmem);

    if(p->intmem.auxp == NULL)
        csound->AuxAlloc(csound, sizeof(CSUI), &p->intmem);


    p->DSP = new (p->dspmem.auxp) mydsp;
    p->interface = new (p->intmem.auxp) CSUI;

    if ((p->DSP == 0) | (p->interface == 0)) return NOTOK;

    p->DSP->init((int)csound->GetSr(csound));   
    p->DSP->buildUserInterface(p->interface);

    return OK;
}


/**
 * CSound callback that process the samples by updating
 * the controls values and calling the compute() method
 * of the DSP object. (Assume MYFLT = float)
 */
static int process32bits(CSOUND *csound, dataspace *p)
{
  AVOIDDENORMALS;

  // update all the control values
  p->interface->copyfrom(p->ktl);

  p->DSP->compute(csound->GetKsmps(csound), p->ain, p->aout);
  return OK;
}

#if 0
/**
 * CSound callback that process the samples by copying
 * the controls values and calling the compute() method
 * of the FAUST generated DSP object. Assume MYFLT = double
 */
static int process64bits(CSOUND *csound, dataspace *p)
{
  // to be defined
  return NOTOK;
}
#endif

extern "C" {

static OENTRY localops[] = {
    {(char*)sym(OPCODE_NAME), sizeof(dataspace),5,makeDescription(FAUST_OUTPUTS), makeDescription(FAUST_INPUTS,FAUST_ACTIVES),
     (SUBR)init, NULL,(SUBR)process32bits }
};
LINKAGE
}
  
   
 
