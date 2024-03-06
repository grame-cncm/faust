#include <cmath>

// Dummy omega
float omega(float x) { return std::max(0.f, x); }
float sign(float x) { return (x < 0) ? -1 : ((x > 0) ? 1 : 0); }

class diode_clipper
{
    public:
        void setSampleRate(float sampleRate);
        void reset();
        void process(float *x, float *y_out_, int nSamples);


    private:

        
        float k2 = 0.0f;
        float k3 = 0.0f;
        float k5 = 0.0f;
        float k6 = 0.0f;
        float _delayed_3 = 0.0f;

        

        float fs;
        char firstRun;

};
