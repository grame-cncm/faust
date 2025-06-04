TITLE:Dsp Constructor in Source.Init
BELOW: m_durationHandler.Setup(m_pParams->RTPC.fDuration, in_pContext->GetNumLoops(), in_rFormat.uSampleRate);
REPLACE: 0
CODE:
    int dsp_outputs = m_dsp.getNumOutputs();
    
    if (dsp_outputs >= 2) {
        in_rFormat.channelConfig.SetStandard(AK_SPEAKER_SETUP_STEREO);
    } else {
        in_rFormat.channelConfig.SetStandard(AK_SPEAKER_SETUP_MONO);
    }
    
    m_dsp.init(static_cast<int>(in_rFormat.uSampleRate));

TITLE:Dsp compute in Source.Execute
BELOW: m_durationHandler.SetDuration(m_pParams->RTPC.fDuration);
REPLACE: 20
CODE:    
    // Faust DSP processing
    m_durationHandler.SetDuration(m_pParams->RTPC.fDuration);
    m_durationHandler.ProduceBuffer(out_pBuffer);

    const AkUInt32 uNumChannels = out_pBuffer->NumChannels();

    AkUInt16 uFramesProduced;
    FAUSTFLOAT* outputs[2];
    AkReal32* AK_RESTRICT pBuf[2];

    for (int i = 0; i < 2; ++i)
    {
        pBuf[i] = (AkReal32 * AK_RESTRICT)out_pBuffer->GetChannel(i);
        outputs[i] = pBuf[i];
    }
    m_dsp.compute((int)out_pBuffer->uValidFrames, nullptr, outputs);
}
