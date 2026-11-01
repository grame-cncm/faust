#ifndef TEMPLATE_EFFECT_PLUGIN_H
#define TEMPLATE_EFFECT_PLUGIN_H

#include "abstract.h"

class WwiseEffectPlugin: public AbstractPlugin
{
public:
    WwiseEffectPlugin(PluginConfiguration&, ParameterList&, InterpreterWrapper&);
    ~WwiseEffectPlugin() override final;
    void reset() override final;
    void setup() override final;
    void callback(std::vector<FAUSTFLOAT*>&, const AkUInt32) override final;
    //sets an audio input given its ID.
    void setAudioInput(int);
    void setSampleRate(int);
private:
    std::vector<FAUSTFLOAT*> faust_inputs;
    std::vector<std::vector<FAUSTFLOAT>> silenceBuffers;
    dsp* audioSource;
    void preprocessInputChannels(const AkUInt32);
};

#endif