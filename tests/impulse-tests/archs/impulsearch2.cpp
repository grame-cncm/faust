
#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif

#include "faust/gui/CGlue.h"
#include "controlTools.h"

//----------------------------------------------------------------------------
//FAUST generated code
// ----------------------------------------------------------------------------

<<includeIntrinsic>>

<<includeclass>>

// Wrapping C++ class for the C object

class Cdsp : public dsp {
    
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
        virtual int getNumInputs() 	{ return getNumInputsmydsp(fDSP); }
        
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
        
        virtual void init(int samplingRate)
        {
            initmydsp(fDSP, samplingRate);
        }
        
        static void classInit(int samplingRate)
        {
            classInitmydsp(samplingRate);
        }
        
        virtual void instanceInit(int samplingRate)
        {
            instanceInitmydsp(fDSP, samplingRate);
        }
        
        virtual void instanceConstants(int samplingRate)
        {
            instanceConstantsmydsp(fDSP, samplingRate);
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
        
        virtual void compute(int count, FAUSTFLOAT** input, FAUSTFLOAT** output)
        {
            computemydsp(fDSP, count, input, output);
        }
    
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            compute(count, inputs, outputs);
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


