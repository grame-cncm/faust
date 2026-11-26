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

#include "Faust_Interpreter_Wwise_PluginSource.h"
#include "../Faust_Interpreter_Wwise_PluginConfig.h"
#include <AK/AkWwiseSDKVersion.h>
#include <string>

AK::IAkPlugin* CreateFaust_Interpreter_Wwise_PluginSource(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, Faust_Interpreter_Wwise_PluginSource());
}

AK::IAkPluginParam* CreateFaust_Interpreter_Wwise_PluginSourceParams(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, Faust_Interpreter_Wwise_PluginSourceParams());
}

AK_IMPLEMENT_PLUGIN_FACTORY(Faust_Interpreter_Wwise_PluginSource, AkPluginTypeSource, Faust_Interpreter_Wwise_PluginConfig::CompanyID, Faust_Interpreter_Wwise_PluginConfig::PluginID)

Faust_Interpreter_Wwise_PluginSource::Faust_Interpreter_Wwise_PluginSource()
    : m_pParams(nullptr)
    , m_pAllocator(nullptr)
    , m_pContext(nullptr)
{

}

Faust_Interpreter_Wwise_PluginSource::~Faust_Interpreter_Wwise_PluginSource()
{
}

AkUInt32 Faust_Interpreter_Wwise_PluginSource::GetSpeakerConfigChannelMask(int preAllocatedOutputs){
    
    // provide default configurations based on given faust dsp outputs

    AkUInt32 in_uChannelMask;
    switch (preAllocatedOutputs)
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
    if (preAllocatedOutputs > 14)
    {
        AKPLATFORM::OutputDebugMsg(" [WARNING] dsp_outputs > 14. This is an unsupported speaker configuration. Falling back to 14 channels (AK_SPEAKER_SETUP_AURO_13POINT1_751).\n");
        in_uChannelMask = AK_SPEAKER_SETUP_AURO_13POINT1_751;
    }

    return in_uChannelMask;
}

AKRESULT Faust_Interpreter_Wwise_PluginSource::Init(AK::IAkPluginMemAlloc* in_pAllocator, AK::IAkSourcePluginContext* in_pContext, AK::IAkPluginParam* in_pParams, AkAudioFormat& in_rFormat)
{
    m_pParams = (Faust_Interpreter_Wwise_PluginSourceParams*)in_pParams;
    m_pAllocator = in_pAllocator;
    m_pContext = in_pContext;

    AKPLATFORM::OutputDebugMsg("Init is called!\n");

    PluginState state = pluginLoader.getPluginState();
    
    if (state != PluginState::READY)
    {

        m_durationHandler.Setup(0.0f, in_pContext->GetNumLoops(), in_rFormat.uSampleRate);
        
        int channelsRequested = pluginLoader.setupAudio(
            static_cast<int>(in_rFormat.uSampleRate)
        );
        // Set the speaker configuration
        in_rFormat.channelConfig.SetStandard( GetSpeakerConfigChannelMask(channelsRequested) );
        speakersAvail = in_rFormat.channelConfig.uNumChannels;

        WwiseOutputs.resize(speakersAvail, nullptr);

        isInitializedOnce = true;
        return AK_Success;
    }
    isInitializedOnce = false;
    return AK_AlreadyInitialized;
}

AKRESULT Faust_Interpreter_Wwise_PluginSource::Term(AK::IAkPluginMemAlloc* in_pAllocator)
{
    AKPLATFORM::OutputDebugMsg("Term is called!\n");
    
    if (isInitializedOnce)
    {
        // that is an reset signal
        pluginLoader.resetPlugin(); 
    }
    else    
    {
        // that is a subsequent Play trigger, so reset the variable to true.
        isInitializedOnce = true;
    }

    AK_PLUGIN_DELETE(in_pAllocator, this);
    return AK_Success;
}

AKRESULT Faust_Interpreter_Wwise_PluginSource::Reset()
{
    AKPLATFORM::OutputDebugMsg("Reset is called!\n");
    return AK_Success;
}

AKRESULT Faust_Interpreter_Wwise_PluginSource::GetPluginInfo(AkPluginInfo& out_rPluginInfo)
{
    out_rPluginInfo.eType = AkPluginTypeSource;
    out_rPluginInfo.bIsInPlace = true;
    out_rPluginInfo.uBuildVersion = AK_WWISESDK_VERSION_COMBINED;
    return AK_Success;
}

/*
void Faust_Interpreter_Wwise_PluginSource::initializeAllChannelsWithSilence(const AkUInt32 framesToProcess)
{
        // Runs only once filling the rest of the faust output channels with silence,  ...
    // ... and only in case the channels requested by the faust dsp program is greater 
    // than the available channels wwise can support.

    if (silenceBuffer.size() < framesToProcess) {
        silenceBuffer.resize(framesToProcess, 0.0f);
    
        // Fill silent channels
        if (!WwiseOutputs[speakersAvail-1]) // if the last buffer is nullptr
        {
            for (AkUInt32 ch = 0; ch < speakersAvail; ++ch) {
                WwiseOutputs[ch] = silenceBuffer.data();
            }
            AKPLATFORM::OutputDebugMsg("Filled the silence buffer!\n");
        }
    }
}
    */

void Faust_Interpreter_Wwise_PluginSource::Execute(AkAudioBuffer* out_pBuffer)
{
    
    if ( pluginLoader.getPluginState() == PluginState::READY)
    {
        m_durationHandler.SetDuration(m_pParams->RTPC.fDuration);
        m_durationHandler.ProduceBuffer(out_pBuffer);

        const AkUInt32 uNumChannels = out_pBuffer->NumChannels();
        const AkUInt32 framesToProcess = out_pBuffer->uValidFrames;

        for (AkUInt32 i = 0; i < speakersAvail; ++i)
        {
            WwiseOutputs[i] = (AkReal32* AK_RESTRICT) out_pBuffer->GetChannel(i);
        }
        AKPLATFORM::OutputDebugMsg("Execute function is running!\n");
        pluginLoader.callback(WwiseOutputs, framesToProcess);
    
    }
    else{
        m_durationHandler.SetDuration(0.0f);
        m_durationHandler.SetLooping(1.0f);         // @TODO : Enable user to loop endlesly. Currently this is disabled.
        m_durationHandler.ProduceBuffer(out_pBuffer);
        // for (AkUInt32 i = 0; i < speakersAvail; ++i)
        // {
        //     AkReal32* AK_RESTRICT pBuf = (AkReal32* AK_RESTRICT)out_pBuffer->GetChannel(i);
        //     // pBuf->ZeroPadToMaxFrames();
        //     AkUInt16 uFramesProduced = 0;
        //     while (uFramesProduced < out_pBuffer->uValidFrames)
        //     {
        //         // Generate output here
        //         *pBuf++ = 0.0f;
        //         ++uFramesProduced;
        //     }
        // }        
    }
}

AkReal32 Faust_Interpreter_Wwise_PluginSource::GetDuration() const
{
    return m_durationHandler.GetDuration() * 1000.0f;
}
