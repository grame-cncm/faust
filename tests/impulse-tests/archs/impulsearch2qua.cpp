
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
class Cdsp : public one_sample_dsp_real1<REAL> {
    
    private:
    
        mydsp* fDSP;
    
    public:
        
        Cdsp(int* icontrol, REAL* fcontrol, int* izone, REAL* fzone)
        {
            fDSP = newmydsp(icontrol, fcontrol, izone, fzone);
        }
        
        virtual ~Cdsp()
        {
            deletemydsp(fDSP);
        }
    
        virtual int getNumIntControls() { return getNumIntControlsmydsp(fDSP); }
    
        virtual int getNumRealControls() { return getNumRealControlsmydsp(fDSP); }
 
        virtual int getiZoneSize() { return getiZoneSizemydsp(fDSP); }
         
        virtual int getfZoneSize() { return getfZoneSizemydsp(fDSP); }
    
        virtual void control()
        {
            controlmydsp(fDSP);
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
            initmydsp(fDSP, sample_rate);
        }
        
        static void classInit(int sample_rate)
        {
            classInitmydsp(sample_rate);
        }
        
        virtual void instanceInit(int sample_rate)
        {
            instanceInitmydsp(fDSP, sample_rate);
        }
        
        virtual void instanceConstants(int sample_rate)
        {
            instanceConstantsmydsp(fDSP, sample_rate);
        }
        
        virtual void instanceResetUserInterface()
        {
            instanceResetUserInterfacemydsp(fDSP);
        }
        
        virtual void instanceClear()
        {
            instanceClearmydsp(fDSP);
        }
        
        virtual dsp* clone()
        {
            return new Cdsp(fDSP->iControl, fDSP->fControl, fDSP->iZone, fDSP->fZone);
        }
        
        virtual void metadata(Meta* m)
        {
            MetaGlue glue;
            buildMetaGlue(&glue, m);
            metadatamydsp(&glue);
        }

        virtual void compute(FAUSTFLOAT* inputs, FAUSTFLOAT* outputs)
        {
            computemydsp(fDSP, inputs, outputs);
        }
    
};

template <typename REAL>
int main_aux(int argc, char* argv[])
{
    int linenum = 0;
    int nbsamples = 60000;
    
    // Global external memory
    int iControl[FAUST_INT_CONTROLS];
    REAL fControl[FAUST_REAL_CONTROLS];
    int iZone[FAUST_INT_ZONE];
    REAL fZone[FAUST_FLOAT_ZONE];
    
    // print general informations
    printHeader(new Cdsp<REAL>(iControl, fControl, iZone, fZone), nbsamples);
    
    // linenum is incremented in runDSP and runPolyDSP
    runDSP(new Cdsp<REAL>(iControl, fControl, iZone, fZone), argv[0], linenum, nbsamples/4);
    runDSP(new Cdsp<REAL>(iControl, fControl, iZone, fZone), argv[0], linenum, nbsamples/4, false, true);
    
    // DSP clone actually uses the same iControl, fControl, iZone, fZone, so deactivated for now
    //runPolyDSP(new Cdsp<double>(), linenum, nbsamples/4, 4);
    //runPolyDSP(new Cdsp<double>(), linenum, nbsamples/4, 1);
    
    return 0;
}

int main(int argc, char* argv[])
{
    //return main_aux<fixpoint_t>(argc, argv);
    return main_aux<double>(argc, argv);
}
