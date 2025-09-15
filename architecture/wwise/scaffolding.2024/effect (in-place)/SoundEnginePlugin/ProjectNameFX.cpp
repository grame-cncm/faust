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
#include <stdexcept>

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

    channelsAvail = in_rFormat.channelConfig.uNumChannels;
    const int numInputs = m_dsp.getNumInputs();
    const int numOutputs = m_dsp.getNumOutputs();
    // Runtime error in case of misalignment between amount of input and output requested channels by the Faust program
    if (numInputs != numOutputs){
        char errorMsg[256];
        snprintf(errorMsg, sizeof(errorMsg),
            "[ERROR]: Wwise FX plugins require the same amount of input/output channels. In this case {} != {}", 
                numInputs, numOutputs);
        AKPLATFORM::OutputDebugMsg(errorMsg);
        throw std::runtime_error(errorMsg);
    }
    numChannels = numInputs;

    // resize and initialize the faust io (in-place) buffer with nullptr
    faust_inplace_buffer.resize(numChannels, nullptr);

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

void ${name}FX::fillRestOfBuffersWithSilence(const AkUInt32 framesToProcess )
{
    
    // Runs only once filling the rest of the faust channels with silence,
    // and only in case the channels requested by the faust dsp program is
    // greater than the available channels wwise can support.
    
    if (faust_inplace_buffer[channelsAvail] == nullptr)
    {
        if (silenceBuffer.size() < framesToProcess) {
            silenceBuffer.resize(framesToProcess, 0.0f);
        }
        // Fill silent channels
        for (int ch = channelsAvail; ch < numChannels; ++ch) {
            faust_inplace_buffer[ch] = silenceBuffer.data();
        }
        AKPLATFORM::OutputDebugMsg("Filled the input(/output) channels with silence.\n");
    }
}

void ${name}FX::Execute(AkAudioBuffer* io_pBuffer)
{

    channelsAvail = static_cast<int>(io_pBuffer->NumChannels());
    const AkUInt32 framesToProcess = io_pBuffer->uValidFrames;

    <<FOREACHPARAM:IF io_type==input:setParameter("${shortname}", m_pParams->${isRTPC}.${RTPCname});>>

    for (int ch = 0; ch < numChannels; ++ch) {
        if (ch < channelsAvail ){
            faust_inplace_buffer[ch] = io_pBuffer->GetChannel(ch);
        }
    }        

    if (channelsAvail < numChannels)
    {
        fillRestOfBuffersWithSilence(framesToProcess);
        numChannels = channelsAvail;
    }

    m_dsp.compute(static_cast<int>(framesToProcess), faust_inplace_buffer.data(), faust_inplace_buffer.data());
}

AKRESULT ${name}FX::TimeSkip(AkUInt32 in_uFrames)
{
    return AK_DataReady;
}
