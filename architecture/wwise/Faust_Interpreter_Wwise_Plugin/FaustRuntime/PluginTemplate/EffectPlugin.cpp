#include "EffectPlugin.h"
#include "AudioInput/audio_inputs.h"

WwiseEffectPlugin::WwiseEffectPlugin(
    PluginConfiguration& config, 
    ParameterList& params, 
    InterpreterWrapper& interpreter
) 
    : AbstractPlugin(config, params, interpreter)
    , audioSource(nullptr)
{}

WwiseEffectPlugin::~WwiseEffectPlugin()
{
    if (audioSource)
    {
        delete audioSource;
        audioSource = nullptr;
    }
}

void WwiseEffectPlugin::reset()
{
    AbstractPlugin::reset();
    faust_inputs.clear();
    silenceBuffers.clear();
    delete audioSource;
    audioSource = nullptr;
}

void WwiseEffectPlugin::setup()
{
    AbstractPlugin::setup();
    faust_inputs.resize(cfg.num_inputs);
}

void WwiseEffectPlugin::setAudioInput(int audioInputID)
{
    audioSource = AudioInputs::createAudioInputById(audioInputID);
}

void WwiseEffectPlugin::setSampleRate(int SR)
{
    audioSource->init(SR);
}

void WwiseEffectPlugin::callback(std::vector<FAUSTFLOAT*>& outputs, const AkUInt32 bufferSize)
{
    setParameters();

    for (AkUInt32 ch = 0; ch < cfg.num_outputs; ++ch)
    {
        faust_outputs[ch] = outputs[ch];
    }
    
    preprocessInputChannels(bufferSize);

    // fill the input. The input to the plugin is the output of the audioSource.
    audioSource->compute(bufferSize,nullptr,faust_inputs.data());
    
    faustInterpreter.callback(bufferSize, faust_inputs.data(), faust_outputs.data());

}

void WwiseEffectPlugin::preprocessInputChannels(const AkUInt32 bufferSize)
{
    // Runs only once initializing the faust_inputs with silence 
    // .. and resizing them to the max size between audio gen and effect plugin...
    
    if (silenceBuffers.empty()){
    
        int numChannelsEffect = cfg.num_inputs;
        int numChannelsGenerator = audioSource->getNumOutputs();
        int maxChannels = (numChannelsEffect >= numChannelsGenerator) ? numChannelsEffect : numChannelsGenerator;
        
        if (maxChannels != numChannelsEffect)
            faust_inputs.resize(maxChannels);
        silenceBuffers.resize(maxChannels);

        for (int ch = 0; ch < maxChannels ; ++ch)
        {
            silenceBuffers[ch].resize(bufferSize, 0.0f);
            faust_inputs[ch] = silenceBuffers[ch].data();
        }
    }
}