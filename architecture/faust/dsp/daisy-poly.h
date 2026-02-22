template<long unsigned int N>
class mydsp_poly
{
public:
    mydsp_poly()
    {}    

    void init(size_t sample_rate)
    {
        for(uint8_t i = 0; i < N_OUTPUTS; ++i)
            voices_outputs[i] = voices_data[i];
        for(size_t i = 0; i < N; ++i)
            voices[i].init(sample_rate);
    }

    void instanceInit(int sample_rate)
    {
        for(size_t i = 0; i < N; ++i)
            voices[i].instanceInit(sample_rate);
    }


    #ifdef USE_SDRAM 
    void memoryCreate() {
        for(auto & it : voices) 
            it.memoryCreate();
    }
    #endif

    void set_out(int count, FAUSTFLOAT **outputs)
    {
        for(size_t ch = 0; ch < voices[0].getNumOutputs(); ++ch)
        {
            for(size_t i = 0; i < count; ++i)
                outputs[ch][i] = voices_outputs[ch][i];
        }
    }

    void mix(int count, FAUSTFLOAT **outputs)
    {
        for(size_t ch = 0; ch < voices[0].getNumOutputs(); ++ch)
        {
            for(size_t i = 0; i < count; ++i)
                outputs[ch][i] += voices_outputs[ch][i];
        }
    }
    void compute(int count, FAUSTFLOAT ** RESTRICT inputs, FAUSTFLOAT ** RESTRICT outputs)
    {
        voices[0].compute(count, inputs, voices_outputs);
        set_out(count, outputs); 
        for(uint8_t i = 1; i < voices.size(); ++i)
        {
            voices[i].compute(count, inputs, voices_outputs);
            mix(count, outputs);
        }

    }

    void buildUserInterface(UI * ui_interface)
    {
        for(auto & it : voices)
            it.buildUserInterface(ui_interface);
    }

private: 
    FAUSTFLOAT voices_data[N_OUTPUTS][MY_BUFFER_SIZE];
    FAUSTFLOAT *voices_outputs[N_OUTPUTS]; 
    std::array<mydsp, N> voices;
};