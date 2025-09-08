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

AkUInt32 ${name}Source::GetSpeakerConfigChannelMask(int dsp_outputs){
    
    // provide default configurations based on given faust dsp outputs

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
        in_uChannelMask = AK_SPEAKER_SETUP_7POINT1;
        break;
    case 9:
        in_uChannelMask = AK_SPEAKER_SETUP_AURO_9;
        break;
    case 10:
        in_uChannelMask = AK_SPEAKER_SETUP_AURO_9POINT1;
        break;
    case 11:
        in_uChannelMask = AK_SPEAKER_SETUP_AURO_10POINT1;
        break;
    case 12:
        in_uChannelMask = AK_SPEAKER_SETUP_AURO_11POINT1;
        break;
    case 13:
        in_uChannelMask = AK_SPEAKER_SETUP_AURO_13_751;
        break;
    case 14:
        in_uChannelMask = AK_SPEAKER_SETUP_AURO_13POINT1_751;
        break;
    default:
        in_uChannelMask = AK_SPEAKER_SETUP_STEREO;
        break;
    }
    if (dsp_outputs > 14)
    {
        AKPLATFORM::OutputDebugMsg(" [WARNING] dsp_outputs > 14. This is an unsupported speaker configuration. Falling back to 14 channels (AK_SPEAKER_SETUP_AURO_13POINT1_751).\n");
        in_uChannelMask = AK_SPEAKER_SETUP_AURO_13POINT1_751;
    }

    return in_uChannelMask;
}

AKRESULT ${name}Source::Init(AK::IAkPluginMemAlloc* in_pAllocator, AK::IAkSourcePluginContext* in_pContext, AK::IAkPluginParam* in_pParams, AkAudioFormat& in_rFormat)
{
    m_pParams = (${name}SourceParams*)in_pParams;
    m_pAllocator = in_pAllocator;
    m_pContext = in_pContext;

    m_durationHandler.Setup(m_pParams->RTPC.fDuration, in_pContext->GetNumLoops(), in_rFormat.uSampleRate);

    numOutputs = m_dsp.getNumOutputs();
    faust_outputs.resize(numOutputs);
    

    in_rFormat.channelConfig.SetStandard( GetSpeakerConfigChannelMask(numOutputs) );
    speakersAvail = in_rFormat.channelConfig.uNumChannels;

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

void ${name}Source::fillRestOfBuffersWithSilence(const AkUInt32 framesToProcess )
{
    
    // Runs only once filling the rest of the faust output channels with silence,  ...
    // ... and only in case the channels requested by the faust dsp program is greater 
    // than the available channels wwise can support.

    static std::vector<FAUSTFLOAT> silenceBuffer;
    if (silenceBuffer.size() < framesToProcess) {
        silenceBuffer.resize(framesToProcess, 0.0f);

    }
    
    // Fill silent channels
    if (!faust_outputs[speakersAvail])
    {
        for (AkUInt32 ch = speakersAvail; ch < static_cast<AkUInt32>(numOutputs); ++ch) {
            faust_outputs[ch] = silenceBuffer.data();
        }
        OutputDebugStringA("Filled the silence buffer!\n");
    }
}

void ${name}Source::Execute(AkAudioBuffer* out_pBuffer)
{
    m_durationHandler.SetDuration(m_pParams->RTPC.fDuration);
    m_durationHandler.ProduceBuffer(out_pBuffer);

    <<FOREACHPARAM:IF io_type==input: setParameter( "${shortname}", m_pParams->${isRTPC}.${RTPCname} );>>

    for (AkUInt32 ch = 0; ch < speakersAvail; ++ch)
    {
        faust_outputs[ch] = out_pBuffer->GetChannel(ch);
    }

    const AkUInt32 framesToProcess = out_pBuffer->uValidFrames;

    fillRestOfBuffersWithSilence(framesToProcess);
        
    m_dsp.compute(static_cast<int>(framesToProcess), nullptr, faust_outputs.data());
}

AkReal32 ${name}Source::GetDuration() const
{
    return m_durationHandler.GetDuration() * 1000.0f;
}
