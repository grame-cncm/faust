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

    int dsp_outputs = m_dsp.getNumOutputs();
    
    if (dsp_outputs >= 2) {
        in_rFormat.channelConfig.SetStandard(AK_SPEAKER_SETUP_STEREO);
    } else {
        in_rFormat.channelConfig.SetStandard(AK_SPEAKER_SETUP_MONO);
    }
    
    m_dsp.init(static_cast<int>(in_rFormat.uSampleRate));

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

AKRESULT ${name}FX::TimeSkip(AkUInt32 in_uFrames)
{
    return AK_DataReady;
}
