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
#include <AK/Wwise/Plugin/PluginDef.h>
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

    numInputs = m_dsp.getNumInputs();
    numOutputs = m_dsp.getNumOutputs();

    // Runtime error in case of misalignment between amount of input and output requested channels by the Faust program
    if (numInputs != numOutputs){
        char errorMsg[256];
        snprintf(errorMsg, sizeof(errorMsg),
            "[ERROR]: Wwise FX plugins require the same amount of input/output channels. In this case {} != {}", 
                numInputs, numOutputs);
        AKPLATFORM::OutputDebugMsg(errorMsg);
        throw std::runtime_error(errorMsg);
    }

    // resize and initialize the faust io buffers with nullptr
    faust_inputs.resize(numInputs,nullptr);
    faust_outputs.resize(numOutputs,nullptr);
    
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

void ${name}FX::fillRestOfBuffersWithSilence(const AkUInt32 framesToProcess )
{
    
    // Runs only once filling the rest of the faust input channels with silence
    // and allocate memory for the output buffers using the helperOutBuffs vector.
    // This is done only in case the channels requested by the faust dsp program
    // is greater than the available channels wwise can support.

    if ( faust_inputs[channelsAvail]==nullptr || faust_outputs[channelsAvail]==nullptr)
    {
        
        if (silenceBuffer.size() < framesToProcess) {
            silenceBuffer.resize(framesToProcess, 0.0f);
        }

        if (faust_inputs[channelsAvail]==nullptr)
        {
            // Fill silent input channels
            for (int ch = channelsAvail; ch < numInputs; ++ch) {
                faust_inputs[ch] = silenceBuffer.data();
            }
            AKPLATFORM::OutputDebugMsg("Filled input channels with silence.\n");
        }

        if (faust_outputs[channelsAvail]==nullptr)
        {
            // allocate storage for the rest of the output buffer channels using the helperOutBuff vector
            helperOutBuff.resize(numOutputs - channelsAvail);
            for (int ch = channelsAvail; ch < numOutputs; ++ch) {
                int idx = ch-channelsAvail;
                helperOutBuff[idx].resize(framesToProcess);
                faust_outputs[ch] = helperOutBuff[idx].data();
            }
            AKPLATFORM::OutputDebugMsg("Set the output buffer with a zeroed array.\n");
        }
    }
}

void ${name}FX::Execute(AkAudioBuffer* in_pBuffer, AkUInt32 in_ulnOffset, AkAudioBuffer* out_pBuffer)
{
    // Technical note:
    // This function assumes that the FAUST DSP consumes and produces exactly the same number of frames.(framesProduced variable is discarded)
    // The number of channels are as many as the DSP supports and extra ones are ignored
    // If the DSP needs a different frame ratio, this logic might not be correct.

    channelsAvail = static_cast<int>(in_pBuffer->NumChannels());
    const AkUInt32 framesToProcess = in_pBuffer->uValidFrames;

    <<FOREACHPARAM:IF io_type==input: setParameter("${shortname}", m_pParams->${isRTPC}.${RTPCname});>>

    for (int ch = 0; ch < numInputs; ++ch)
    {
        if (ch < channelsAvail)
        {
            faust_inputs[ch] = in_pBuffer->GetChannel(ch) + in_ulnOffset;
        }
    }

    for (int ch = 0; ch < numOutputs; ++ch)
    {
        if (ch < channelsAvail )
        {
            faust_outputs[ch] = out_pBuffer->GetChannel(ch) + out_pBuffer->uValidFrames;
        }
    }

    // Fill rest of the channels, in case channelsAvail are less then numInputs.
    // This condition can be evaluated as true only once.
    if (channelsAvail < numInputs)
    {
        fillRestOfBuffersWithSilence(framesToProcess);
        // micro-optimization
        numInputs = channelsAvail;      
        numOutputs = channelsAvail;
    }

    m_dsp.compute(static_cast<int>(framesToProcess), faust_inputs.data(), faust_outputs.data());

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
