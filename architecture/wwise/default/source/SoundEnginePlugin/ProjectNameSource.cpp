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

#include "${name}Source.h"
#include "../${name}Config.h"

#include <AK/AkWwiseSDKVersion.h>

AK::IAkPlugin* Create${name}Source(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, ${name}Source());
}

AK::IAkPluginParam* Create${name}SourceParams(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, ${name}SourceParams());
}

AK_IMPLEMENT_PLUGIN_FACTORY(${name}Source, AkPluginTypeSource, ${name}Config::CompanyID, ${name}Config::PluginID)

${name}Source::${name}Source()
    : m_pParams(nullptr)
    , m_pAllocator(nullptr)
    , m_pContext(nullptr)
{
}

${name}Source::~${name}Source()
{
}

AKRESULT ${name}Source::Init(AK::IAkPluginMemAlloc* in_pAllocator, AK::IAkSourcePluginContext* in_pContext, AK::IAkPluginParam* in_pParams, AkAudioFormat& in_rFormat)
{
    m_pParams = (${name}SourceParams*)in_pParams;
    m_pAllocator = in_pAllocator;
    m_pContext = in_pContext;

    m_durationHandler.Setup(m_pParams->RTPC.fDuration, in_pContext->GetNumLoops(), in_rFormat.uSampleRate);

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

AKRESULT ${name}Source::Term(AK::IAkPluginMemAlloc* in_pAllocator)
{
    AK_PLUGIN_DELETE(in_pAllocator, this);
    return AK_Success;
}

AKRESULT ${name}Source::Reset()
{
    return AK_Success;
}

AKRESULT ${name}Source::GetPluginInfo(AkPluginInfo& out_rPluginInfo)
{
    out_rPluginInfo.eType = AkPluginTypeSource;
    out_rPluginInfo.bIsInPlace = true;
    out_rPluginInfo.uBuildVersion = AK_WWISESDK_VERSION_COMBINED;
    return AK_Success;
}

void ${name}Source::Execute(AkAudioBuffer* out_pBuffer)
{
    // Faust DSP processing
    m_durationHandler.SetDuration(m_pParams->RTPC.fDuration);
    m_durationHandler.ProduceBuffer(out_pBuffer);

    <<FOREACHPARAM: setParameter( "${shortname}", m_pParams->${isRTPC}.${RTPCname} );>>

    const AkUInt32 uNumChannels = out_pBuffer->NumChannels();

    // @TODO improve outputs, pbuf
    
    // AkUInt16 uFramesProduced;
    FAUSTFLOAT* outputs[2];
    AkReal32* AK_RESTRICT pBuf[2];

    for (int i = 0; i < 2; ++i)
    {
        pBuf[i] = (AkReal32 * AK_RESTRICT)out_pBuffer->GetChannel(i);
        outputs[i] = pBuf[i];
    }

    m_dsp.compute((int)out_pBuffer->uValidFrames, nullptr, outputs);

}

AkReal32 ${name}Source::GetDuration() const
{
    return m_durationHandler.GetDuration() * 1000.0f;
}
