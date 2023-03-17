
#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "faust/gui/CGlue.h"
#include "faust/dsp/one-sample-dsp.h"
#include "controlTools.h"

//----------------------------------------------------------------------------
//FAUST generated code
// ----------------------------------------------------------------------------

<<includeIntrinsic>>

<<includeclass>>

// Wrapping C++ class for the C object in 'one sample' mode

template <typename REAL>
class Cdsp : public one_sample_dsp_real<REAL> {
    
    private:
    
        mydsp* fDSP;
    
    public:
        
        Cdsp()
        {
            fDSP = newmydsp();
        }
        
        virtual ~Cdsp()
        {
            deletemydsp(fDSP);
        }
    
        virtual void init(int sample_rate, int* iZone, REAL* fZone)
        {
            initmydsp(fDSP, sample_rate, iZone, fZone);
        }
        virtual void instanceInit(int sample_rate, int* iZone, REAL* fZone)
        {
            instanceInitmydsp(fDSP, sample_rate, iZone, fZone);
        }
        virtual void instanceConstants(int sample_rate, int* iZone, REAL* fZone)
        {
            instanceConstantsmydsp(fDSP, sample_rate, iZone, fZone);
        }
        virtual void instanceClear(int* iZone, REAL* fZone)
        {
            instanceClearmydsp(fDSP, iZone, fZone);
        }
    
        virtual int getNumIntControls() { return getNumIntControlsmydsp(fDSP); }
    
        virtual int getNumRealControls() { return getNumRealControlsmydsp(fDSP); }
 
        virtual int getiZoneSize() { return getiZoneSizemydsp(fDSP); }
         
        virtual int getfZoneSize() { return getfZoneSizemydsp(fDSP); }
    
        virtual void control(int* iControl, REAL* fControl, int* iZone, REAL* fZone)
        {
            this->checkAlloc();
            controlmydsp(fDSP, iControl, fControl, iZone, fZone);
        }
    
        virtual int getNumInputs() { return getNumInputsmydsp(fDSP); }
        
        virtual int getNumOutputs() { return getNumOutputsmydsp(fDSP); }
        
        virtual void buildUserInterface(UI* ui_interface)
        {
            UIGlue glue;
            buildUIGlue(&glue, ui_interface, true);
            buildUserInterfacemydsp(fDSP, &glue);
        }
        
        virtual int getSampleRate()
        {
            return getSampleRatemydsp(fDSP);
        }
        
        virtual void init(int sample_rate)
        {
            this->checkAlloc();
            initmydsp(fDSP, sample_rate, this->iZone, this->fZone);
        }
        
        static void classInit(int sample_rate)
        {
            classInitmydsp(sample_rate);
        }
        
        virtual void instanceInit(int sample_rate)
        {
            this->checkAlloc();
            instanceInitmydsp(fDSP, sample_rate, this->iZone, this->fZone);
        }
        
        virtual void instanceConstants(int sample_rate)
        {
            this->checkAlloc();
            instanceConstantsmydsp(fDSP, sample_rate, this->iZone, this->fZone);
        }
        
        virtual void instanceResetUserInterface()
        {
            instanceResetUserInterfacemydsp(fDSP);
        }
        
        virtual void instanceClear()
        {
            this->checkAlloc();
            instanceClearmydsp(fDSP, this->iZone, this->fZone);
        }
        
        virtual dsp* clone()
        {
            return new Cdsp();
        }
        
        virtual void metadata(Meta* m)
        {
            MetaGlue glue;
            buildMetaGlue(&glue, m);
            metadatamydsp(&glue);
        }

        virtual void compute(FAUSTFLOAT* inputs, FAUSTFLOAT* outputs, int* iControl, REAL* fControl, int* iZone, REAL* fZone)
        {
            computemydsp(fDSP, inputs, outputs, iControl, fControl, iZone, fZone);
        }
    
};

template <typename REAL>
static int main_aux(int argc, char* argv[])
{
    int linenum = 0;
    int nbsamples = 60000;
    
    // print general informations
    printHeader(new Cdsp<REAL>(), nbsamples);
    
    // linenum is incremented in runDSP and runPolyDSP
    runDSP(new Cdsp<REAL>(), argv[0], linenum, nbsamples/4);
    runDSP(new Cdsp<REAL>(), argv[0], linenum, nbsamples/4, false, true);
    runPolyDSP(new Cdsp<REAL>(), linenum, nbsamples/4, 4);
    runPolyDSP(new Cdsp<REAL>(), linenum, nbsamples/4, 1);
    
    return 0;
}

int main(int argc, char* argv[])
{
    //return main_aux<fixpoint_t>(argc, argv);
    return main_aux<double>(argc, argv);
}

