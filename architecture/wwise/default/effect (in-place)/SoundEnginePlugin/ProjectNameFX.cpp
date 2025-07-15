/*******************************************************************************
The content of this file includes portions of the AUDIOKINETIC Wwise Technology
released in source code form as part of the SDK installer package.

Commercial License Usage

Licensees holding valid commercial licenses to the AUDIOKINETIC Wwise Technology
may use this file in accordance with the end user license agreement provided
with the software or, alternatively, in accordance with the terms contained in a
written agreement between you and Audiokinetic Inc.

Apache License Usage

Alternatively, this file may be used under the Apache License, Version 2.0 (the
"Apache License"); you may not use this file except in compliance with the
Apache License. You may obtain a copy of the Apache License at
http://www.apache.org/licenses/LICENSE-2.0.

Unless required by applicable law or agreed to in writing, software distributed
under the Apache License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES
OR CONDITIONS OF ANY KIND, either express or implied. See the Apache License for
the specific language governing permissions and limitations under the License.

  Copyright (c) 2025 Audiokinetic Inc.
*******************************************************************************/

#include "${name}FX.h"
#include "../${name}Config.h"

#include <AK/AkWwiseSDKVersion.h>

AK::IAkPlugin* Create${name}FX(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, ${name}FX());
}

AK::IAkPluginParam* Create${name}FXParams(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, ${name}FXParams());
}

AK_IMPLEMENT_PLUGIN_FACTORY(${name}FX, AkPluginTypeEffect, ${name}Config::CompanyID, ${name}Config::PluginID)

${name}FX::${name}FX()
    : m_pParams(nullptr)
    , m_pAllocator(nullptr)
    , m_pContext(nullptr)
{
}

${name}FX::~${name}FX()
{
}

AkUInt32 ${name}FX::GetSpeakerConfigChannelMask(int dsp_outputs){
    
    // improved formats based on :
    // https://www.audiokinetic.com/en/public-library/2024.1.6_8842/?source=SDK&id=_ak_speaker_config_8h_source.html
    // @TODO:
    // The configuration that takes place is a coarse one and make assumptions about the maching of config options 
    // .. for instance, 7 speakers may be 7_0 or 6_1 as well.
    // .. so there is space for improvement here...

    AkUInt32 in_uChannelMask;
    switch (dsp_outputs)
    {
    case 1:
        in_uChannelMask = AK_SPEAKER_SETUP_MONO;
        break;
    case 2:
        in_uChannelMask = AK_SPEAKER_SETUP_STEREO;
        break;
    case 3:
        in_uChannelMask = AK_SPEAKER_SETUP_3STEREO;
        break;
    case 4:
        in_uChannelMask = AK_SPEAKER_SETUP_4;
        break;
    case 5:
        in_uChannelMask = AK_SPEAKER_SETUP_5;
        break;
    case 6:
        in_uChannelMask = AK_SPEAKER_SETUP_6;
        break;
    case 7:
        in_uChannelMask = AK_SPEAKER_SETUP_7;
        break;
    case 8:
        in_uChannelMask = AK_SPEAKER_SETUP_7POINT1; // or AK_SPEAKER_SETUP_DEFAULT_PLANE?
        break;
    default:
        in_uChannelMask = AK_SPEAKER_SETUP_STEREO;
        break;
    }

    if (dsp_outputs > 8)
    {
        AKPLATFORM::OutputDebugMsg(" [WARNING] dsp_outputs > 8. This is an unsupported speaker configuration. Falling back to 8 channels (7.1).\n");
        in_uChannelMask = AK_SPEAKER_SETUP_7POINT1;
    }

    return in_uChannelMask;
}

AKRESULT ${name}FX::Init(AK::IAkPluginMemAlloc* in_pAllocator, AK::IAkEffectPluginContext* in_pContext, AK::IAkPluginParam* in_pParams, AkAudioFormat& in_rFormat)
{
    m_pParams = (${name}FXParams*)in_pParams;
    m_pAllocator = in_pAllocator;
    m_pContext = in_pContext;

    numInputs = m_dsp.getNumInputs();
    numOutputs = m_dsp.getNumOutputs();
    faust_inputs.resize(numInputs);
    faust_outputs.resize(numOutputs);
    
    in_rFormat.channelConfig.SetStandard( GetSpeakerConfigChannelMask(numOutputs) );

    initDSP(static_cast<int>(in_rFormat.uSampleRate));

    return AK_Success;
}

AKRESULT ${name}FX::Term(AK::IAkPluginMemAlloc* in_pAllocator)
{
    AK_PLUGIN_DELETE(in_pAllocator, this);
    return AK_Success;
}

AKRESULT ${name}FX::Reset()
{
    return AK_Success;
}

AKRESULT ${name}FX::GetPluginInfo(AkPluginInfo& out_rPluginInfo)
{
    out_rPluginInfo.eType = AkPluginTypeEffect;
    out_rPluginInfo.bIsInPlace = true;
	out_rPluginInfo.bCanProcessObjects = false;
    out_rPluginInfo.uBuildVersion = AK_WWISESDK_VERSION_COMBINED;
    return AK_Success;
}

void ${name}FX::Execute(AkAudioBuffer* io_pBuffer)
{
    // Technical note:
    // This function assumes that the FAUST DSP consumes and produces exactly the same number of frames.(framesProduced variable is discarded)
    // The number of channels are as many as the DSP supports and extra ones are ignored
    // If the DSP needs a different frame ratio, this logic might not be correct.

    const AkUInt32 inChannels = io_pBuffer->NumChannels();
    const AkUInt32 framesToProcess = io_pBuffer->uValidFrames;

    <<FOREACHPARAM: setParameter("${shortname}", m_pParams->${isRTPC}.${RTPCname});>>

    std::fill(faust_inputs.begin(), faust_inputs.end(), nullptr);
    std::fill(faust_outputs.begin(), faust_outputs.end(), nullptr);

    for (int ch = 0; ch < static_cast<int>(io_pBuffer->NumChannels()); ++ch) {
        if (ch < numInputs)
            faust_inputs[ch] = io_pBuffer->GetChannel(ch);
        if (ch < numOutputs)
            faust_outputs[ch] = io_pBuffer->GetChannel(ch);
    }

    m_dsp.compute(static_cast<int>(framesToProcess), faust_inputs.data(), faust_outputs.data());
}

AKRESULT ${name}FX::TimeSkip(AkUInt32 in_uFrames)
{
    return AK_DataReady;
}
