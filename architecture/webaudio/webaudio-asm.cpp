
// Adapted From https://gist.github.com/camupod/5640386
// compile using "C" linkage to avoid name obfuscation

#include <emscripten.h>
#include <vector>
#include <string>

#include "faust/gui/JSONUI.h"
#include "faust/audio/dsp.h"

// "mydsp" part will be replaced by the actual '-cn' parameter

// Usage : faust -i -uim -a faust-wrapper1.cpp -cn karplus karplus.dsp -o karplus.cpp

inline int max (unsigned int a, unsigned int b) { return (a>b) ? a : b; }
inline int max (int a, int b)		{ return (a>b) ? a : b; }

inline long max (long a, long b) 		{ return (a>b) ? a : b; }
inline long max (int a, long b) 		{ return (a>b) ? a : b; }
inline long max (long a, int b) 		{ return (a>b) ? a : b; }

inline float max (float a, float b) 	{ return (a>b) ? a : b; }
inline float max (int a, float b) 		{ return (a>b) ? a : b; }
inline float max (float a, int b) 		{ return (a>b) ? a : b; }
inline float max (long a, float b) 		{ return (a>b) ? a : b; }
inline float max (float a, long b) 		{ return (a>b) ? a : b; }

inline double max (double a, double b) 	{ return (a>b) ? a : b; }
inline double max (int a, double b) 	{ return (a>b) ? a : b; }
inline double max (double a, int b) 	{ return (a>b) ? a : b; }
inline double max (long a, double b) 	{ return (a>b) ? a : b; }
inline double max (double a, long b) 	{ return (a>b) ? a : b; }
inline double max (float a, double b) 	{ return (a>b) ? a : b; }
inline double max (double a, float b) 	{ return (a>b) ? a : b; }

inline int	min (int a, int b)		{ return (a<b) ? a : b; }

inline long min (long a, long b) 	{ return (a<b) ? a : b; }
inline long min (int a, long b) 	{ return (a<b) ? a : b; }
inline long min (long a, int b) 	{ return (a<b) ? a : b; }

inline float min (float a, float b) 	{ return (a<b) ? a : b; }
inline float min (int a, float b) 		{ return (a<b) ? a : b; }
inline float min (float a, int b) 		{ return (a<b) ? a : b; }
inline float min (long a, float b) 		{ return (a<b) ? a : b; }
inline float min (float a, long b) 		{ return (a<b) ? a : b; }

inline double min (double a, double b) 	{ return (a<b) ? a : b; }
inline double min (int a, double b) 	{ return (a<b) ? a : b; }
inline double min (double a, int b) 	{ return (a<b) ? a : b; }
inline double min (long a, double b) 	{ return (a<b) ? a : b; }
inline double min (double a, long b) 	{ return (a<b) ? a : b; }
inline double min (float a, double b) 	{ return (a<b) ? a : b; }
inline double min (double a, float b) 	{ return (a<b) ? a : b; }

<<includeIntrinsic>>

<<includeclass>>

extern "C" {
    
    typedef std::vector<std::pair<std::string, FAUSTFLOAT*> > UImap;
    
    class JSUI : public UI
    {
        
    protected:
        
        std::vector<std::string> fControlsLevel;
        
        std::string buildPath(const std::string& label) 
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res += fControlsLevel[i];
                res += "/";
            }
            res += label;
            return res;
        }

     public:
        
        JSUI() {};
        ~JSUI() {};
        
        UImap fUIMap;
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            fControlsLevel.push_back(label);
        };
        void openHorizontalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        };
        void openVerticalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        };
        void closeBox()
        {
            fControlsLevel.pop_back();
        };

        // -- active widgets
        void insertMap(std::string label, FAUSTFLOAT* zone)
        {
            fUIMap.push_back(std::pair<std::string, FAUSTFLOAT*>(label, zone));
        }

        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            insertMap(buildPath(label), zone);
        };
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            insertMap(buildPath(label), zone);
        };
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        };
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        };
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        };

        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            insertMap(buildPath(label), zone);
        };
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            insertMap(buildPath(label), zone);
        };

    	// -- metadata declarations
        void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {};
    };
    
    // Just inherit from both classes...
    struct mydsp_wrap : public mydsp, public JSUI
    {
        std::string fJSON;
    };
    
    //constructor
    mydsp_wrap* mydsp_constructor(int samplingFreq) 
    {
        // Make a new dsp object
        mydsp_wrap* n = new mydsp_wrap();
        
        // Init it with samplingFreq supplied...
        n->init(samplingFreq);
        n->buildUserInterface(n);
        
        // Creates JSON
        JSONUI builder(n->getNumInputs(), n->getNumOutputs());
        mydsp::metadata(&builder);
        n->buildUserInterface(&builder);
        n->fJSON = builder.JSON();
        
        return n;
    }
    
    void mydsp_destructor(mydsp_wrap* n) 
    {
        delete n;
    }

    int mydsp_getNumParams(mydsp_wrap* n)
    {
        return n->fUIMap.size();
    }
    
    FAUSTFLOAT* mydsp_getIndexedParam(mydsp_wrap* n, int item, char* key)
    {
        strcpy(key, n->fUIMap[item].first.c_str());
        return n->fUIMap[item].second;
    }
    
    void mydsp_compute(mydsp_wrap* n, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 
    {
        n->compute(count, inputs, outputs);
    }
    
    int mydsp_getNumInputs(mydsp_wrap* n)
    {
        return n->getNumInputs();
    }
    
    int mydsp_getNumOutputs(mydsp_wrap* n)
    {
        return n->getNumOutputs();
    }
    
    void mydsp_getJSON(mydsp_wrap* n, char* json)
    {
        strcpy(json, n->fJSON.c_str());
    }
    
}