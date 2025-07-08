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

AKRESULT ${name}FX::Init(AK::IAkPluginMemAlloc* in_pAllocator, AK::IAkEffectPluginContext* in_pContext, AK::IAkPluginParam* in_pParams, AkAudioFormat& in_rFormat)
{
    m_pParams = (${name}FXParams*)in_pParams;
    m_pAllocator = in_pAllocator;
    m_pContext = in_pContext;

    // @TODO improve dsp_outputs

    int dsp_outputs = m_dsp.getNumOutputs();
    
    if (dsp_outputs >= 2) {
        in_rFormat.channelConfig.SetStandard(AK_SPEAKER_SETUP_STEREO);
    } else {
        in_rFormat.channelConfig.SetStandard(AK_SPEAKER_SETUP_MONO);
    }
    
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
    out_rPluginInfo.bIsInPlace = false;
	out_rPluginInfo.bCanProcessObjects = false;
    out_rPluginInfo.uBuildVersion = AK_WWISESDK_VERSION_COMBINED;
    return AK_Success;
}

// void ${name}FX::Execute(AkAudioBuffer* in_pBuffer, AkUInt32 in_ulnOffset, AkAudioBuffer* out_pBuffer)
// {
//     const AkUInt32 uNumChannels = in_pBuffer->NumChannels();

//     AkUInt16 uFramesConsumed;
//     AkUInt16 uFramesProduced;
//     for (AkUInt32 i = 0; i < uNumChannels; ++i)
//     {
//         AkReal32* AK_RESTRICT pInBuf = (AkReal32* AK_RESTRICT)in_pBuffer->GetChannel(i) + in_ulnOffset;
//         AkReal32* AK_RESTRICT pOutBuf = (AkReal32* AK_RESTRICT)out_pBuffer->GetChannel(i) +  out_pBuffer->uValidFrames;

//         uFramesConsumed = 0;
//         uFramesProduced = 0;
//         while (uFramesConsumed < in_pBuffer->uValidFrames
//             && uFramesProduced < out_pBuffer->MaxFrames())
//         {
//              // Execute DSP that consumes input and produces output at different rate here
//             *pOutBuf++ = *pInBuf++;
//             ++uFramesConsumed;
//             ++uFramesProduced;
//         }
//     }

//     in_pBuffer->uValidFrames -= uFramesConsumed;
//     out_pBuffer->uValidFrames += uFramesProduced;

//     if (in_pBuffer->eState == AK_NoMoreData && in_pBuffer->uValidFrames == 0)
//         out_pBuffer->eState = AK_NoMoreData;
//     else if (out_pBuffer->uValidFrames == out_pBuffer->MaxFrames())
//         out_pBuffer->eState = AK_DataReady;
//     else
//         out_pBuffer->eState = AK_DataNeeded;
// }

void ${name}FX::Execute(AkAudioBuffer* in_pBuffer, AkUInt32 in_ulnOffset, AkAudioBuffer* out_pBuffer)
{
    const AkUInt32 uNumChannels = in_pBuffer->NumChannels();
    const AkUInt32 maxChannels = AkMin(uNumChannels, (AkUInt32)m_dsp.getNumInputs());

    // Set all Faust parameters
    <<FOREACHPARAM: setParameter( "${shortname}", m_pParams->${isRTPC}.${RTPCname} );>>

    FAUSTFLOAT* inputs[8];
    FAUSTFLOAT* outputs[8];

    // Setup input/output channel pointers
    for (AkUInt32 ch = 0; ch < maxChannels; ++ch)
    {
        AkReal32* AK_RESTRICT pInBuf = (AkReal32* AK_RESTRICT)in_pBuffer->GetChannel(ch) + in_ulnOffset;
        AkReal32* AK_RESTRICT pOutBuf = (AkReal32* AK_RESTRICT)out_pBuffer->GetChannel(ch) + out_pBuffer->uValidFrames;

        inputs[ch] = pInBuf;
        outputs[ch] = pOutBuf;
    }

    // Zero unused channels
    for (AkUInt32 ch = maxChannels; ch < 8; ++ch)
    {
        inputs[ch] = nullptr;
        outputs[ch] = nullptr;
    }

    // Compute number of frames to process
    AkUInt32 framesToProcess = AkMin(
        in_pBuffer->uValidFrames,
        out_pBuffer->MaxFrames() - out_pBuffer->uValidFrames
    );

    // Perform DSP processing
    m_dsp.compute((int)framesToProcess, inputs, outputs);

    // Update buffer states
    in_pBuffer->uValidFrames -= framesToProcess;
    out_pBuffer->uValidFrames += framesToProcess;

    if (in_pBuffer->eState == AK_NoMoreData && in_pBuffer->uValidFrames == 0)
        out_pBuffer->eState = AK_NoMoreData;
    else if (out_pBuffer->uValidFrames == out_pBuffer->MaxFrames())
        out_pBuffer->eState = AK_DataReady;
    else
        out_pBuffer->eState = AK_DataNeeded;
}


AKRESULT ${name}FX::TimeSkip(AkUInt32 &io_uFrames)
{
    return AK_DataReady;
}
