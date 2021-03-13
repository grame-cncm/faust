
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

/*
class Cdsp : public one_sample_dsp {
    
    private:
    
        int* iZone;
        FAUSTFLOAT* fZone;
        mydsp* fDSP;
    
    public:
        
        Cdsp()
        {
            iZone = new int[getiZoneSizemydsp(fDSP)];
            fZone = new FAUSTFLOAT[getfZoneSizemydsp(fDSP)];
            fDSP = newmydsp();
        }
        
        virtual ~Cdsp()
        {
            delete [] iZone;
            delete [] fZone;
            deletemydsp(fDSP);
        }
    
        virtual int getNumIntControls() { return getNumIntControlsmydsp(fDSP); }
    
        virtual int getNumRealControls() { return getNumRealControlsmydsp(fDSP); }
    
        virtual void control(int* iControl, FAUSTFLOAT* fControl)
        {
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
            initmydsp(fDSP, sample_rate, iZone, fZone);
        }
        
        static void classInit(int sample_rate)
        {
            classInitmydsp(sample_rate);
        }
        
        virtual void instanceInit(int sample_rate)
        {
            instanceInitmydsp(fDSP, sample_rate, iZone, fZone);
        }
        
        virtual void instanceConstants(int sample_rate)
        {
            instanceConstantsmydsp(fDSP, sample_rate, iZone, fZone);
        }
        
        virtual void instanceResetUserInterface()
        {
            instanceResetUserInterfacemydsp(fDSP);
        }
        
        virtual void instanceClear()
        {
            instanceClearmydsp(fDSP, iZone, fZone);
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

        virtual void compute(FAUSTFLOAT* inputs, FAUSTFLOAT* outputs, int* iControl, FAUSTFLOAT* fControl)
        {
            computemydsp(fDSP, inputs, outputs, iControl, fControl, iZone, fZone);
        }
    
};
*/

class Cdsp : public one_sample_dsp {
    
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
    
        virtual int getNumIntControls() { return getNumIntControlsmydsp(fDSP); }
    
        virtual int getNumRealControls() { return getNumRealControlsmydsp(fDSP); }
    
        virtual void control(int* iControl, FAUSTFLOAT* fControl)
        {
            controlmydsp(fDSP, iControl, fControl);
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
            return new Cdsp();
        }
    
        virtual void metadata(Meta* m)
        {
            MetaGlue glue;
            buildMetaGlue(&glue, m);
            metadatamydsp(&glue);
        }
    
        virtual void compute(FAUSTFLOAT* inputs, FAUSTFLOAT* outputs, int* iControl, FAUSTFLOAT* fControl)
        {
            computemydsp(fDSP, inputs, outputs, iControl, fControl);
        }
    
};

int main(int argc, char* argv[])
{
    int linenum = 0;
    int nbsamples = 60000;
    
    // print general informations
    printHeader(new Cdsp(), nbsamples);
    
    // linenum is incremented in runDSP and runPolyDSP
    runDSP(new Cdsp(), argv[0], linenum, nbsamples/4);
    runDSP(new Cdsp(), argv[0], linenum, nbsamples/4, false, true);
    runPolyDSP(new Cdsp(), linenum, nbsamples/4, 4);
    runPolyDSP(new Cdsp(), linenum, nbsamples/4, 1);
    
    return 0;
}


