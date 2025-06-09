TITLE:Dsp Constructor in FX.Init
BELOW: m_pContext = in_pContext;
REPLACE: 0
CODE:
    int dsp_outputs = m_dsp.getNumOutputs();
    
    if (dsp_outputs >= 2) {
        in_rFormat.channelConfig.SetStandard(AK_SPEAKER_SETUP_STEREO);
    } else {
        in_rFormat.channelConfig.SetStandard(AK_SPEAKER_SETUP_MONO);
    }
    
    m_dsp.init(static_cast<int>(in_rFormat.uSampleRate));

TITLE:Dsp compute in FX.Execute
BELOW: const AkUInt32 uNumChannels = io_pBuffer->NumChannels();
REPLACE: 15
CODE: 
    const AkUInt32 uNumChannels = io_pBuffer->NumChannels();
    const AkUInt32 maxChannels = AkMin(uNumChannels, (AkUInt32)m_dsp.getNumInputs());
    
    FAUSTFLOAT* inputs[8];
    FAUSTFLOAT* outputs[8];
    AkReal32* AK_RESTRICT channelBufs[8];
    
    // Setup channel pointers
    for (AkUInt32 ch = 0; ch < maxChannels; ++ch)
    {
        channelBufs[ch] = (AkReal32 * AK_RESTRICT)io_pBuffer->GetChannel(ch);
        inputs[ch] = channelBufs[ch];
        outputs[ch] = channelBufs[ch];
    }
    
    // Zero unused channels
    for (AkUInt32 ch = maxChannels; ch < 8; ++ch)
    {
        inputs[ch] = nullptr;
        outputs[ch] = nullptr;
    }
    
    // Process entire buffer at once
    m_dsp.compute((int)io_pBuffer->uValidFrames, inputs, outputs);
}