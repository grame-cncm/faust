/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2013 Reza Payami
 All rights reserved.
 ----------------------------BSD License------------------------------
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above
 copyright notice, this list of conditions and the following
 disclaimer in the documentation and/or other materials provided
 with the distribution.
 * Neither the name of Remy Muller nor the names of its
 contributors may be used to endorse or promote products derived
 from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 OF THE POSSIBILITY OF SUCH DAMAGE.

 ----------------------------Audio Unit SDK----------------------------------
 In order to compile a AU (TM) plugin with this architecture file
 you will need the proprietary AU SDK from Apple. Please check
 the corresponding license.

 ************************************************************************
 ************************************************************************/

#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string>
#include <vector>

#include "AUEffectBase.h"
#include <AudioToolbox/AudioUnitUtilities.h>
#include "FaustAUVersion.h"
#include "faust/misc.h"

#ifndef FaustAU_FaustAUEffect_h
#include "FaustAU.h" //TODO
#endif

using namespace std;

/******************************************************************************
 *******************************************************************************
 *
 *	VECTOR INTRINSICS
 *
 *******************************************************************************
 *******************************************************************************/

<<includeIntrinsic>>

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

static const int kPreset_One = 0;
static const int kNumberPresets = 1;
static AUPreset kPresets[kNumberPresets] =
{ { kPreset_One, CFSTR("Default") }, };

#define MAX_OUT_CHANNELS 1000

class FaustAUEffect: public AUEffectBase
{

public:

    FaustAUEffect(AudioUnit component);

    ~FaustAUEffect();

    virtual OSStatus Version()
    {
        return kFaustAUVersion;
    }

    virtual OSStatus Initialize();

    virtual OSStatus GetPropertyInfo(AudioUnitPropertyID inID,
                                     AudioUnitScope inScope, AudioUnitElement inElement,
                                     UInt32 & outDataSize, Boolean & outWritable);

    virtual OSStatus GetProperty(AudioUnitPropertyID inID,
                                 AudioUnitScope inScope, AudioUnitElement inElement, void * outData);

    virtual OSStatus GetParameterInfo(AudioUnitScope inScope,
                                      AudioUnitParameterID inParameterID,
                                      AudioUnitParameterInfo &outParameterInfo);

    void SetParameter(AudioUnitParameterID paramID,
                      AudioUnitParameterValue value);

    virtual OSStatus SetParameter(AudioUnitParameterID inID,
                                  AudioUnitScope inScope, AudioUnitElement inElement,
                                  AudioUnitParameterValue inValue, UInt32);

    virtual OSStatus GetPresets(CFArrayRef *outData) const;

    virtual OSStatus NewFactoryPresetSet(const AUPreset & inNewFactoryPreset);

    virtual bool SupportsTail()
    {
        return true;
    }

    virtual Float64 GetTailTime()
    {
        return 3.0;
    }

    //For example, a lookahead compressor or FFT-based processor should report the true latency in seconds
    virtual Float64 GetLatency()
    {
        return 0.0;
    }

    virtual OSStatus ProcessBufferLists(AudioUnitRenderActionFlags &ioActionFlags,
                                        const AudioBufferList &inBuffer, AudioBufferList &outBuffer,
                                        UInt32 inFramesToProcess);

private:
    auUI* dspUI;

public:
    mydsp* dsp;
};

/**********************************************************************************/

AUDIOCOMPONENT_ENTRY(AUBaseFactory, FaustAU)

FaustAUEffect::FaustAUEffect(AudioUnit component)
    : AUEffectBase(component)
{
    CreateElements();
    dspUI = new auUI();
    dsp = new mydsp();
    SetParamHasSampleRateDependency(true);
    dsp->buildUserInterface(dspUI);

    if (dspUI) {
        for (int i = 0; i < dspUI->fUITable.size(); i++) {
            if (dspUI->fUITable[i] && dspUI->fUITable[i]->fZone)
            {
                if (dynamic_cast<auButton*>(dspUI->fUITable[i]))
                {
                    SetParameter(i, 0);
                }
                else if (dynamic_cast<auToggleButton*>(dspUI->fUITable[i]))
                {
                    SetParameter(i, 0);
                }
                else if (dynamic_cast<auCheckButton*>(dspUI->fUITable[i]))
                {
                    SetParameter(i, 0);
                }
                else
                {
                    auSlider* slider = (auSlider*)dspUI->fUITable[i];
                    SetParameter(i, slider->fInit );
                }
            }
        }
    }
}

FaustAUEffect::~FaustAUEffect()
{
    delete dspUI;
    delete dsp;
}

OSStatus FaustAUEffect::Initialize()
{
    OSStatus result = AUEffectBase::Initialize();
    dsp->init(int(GetSampleRate()));
    return result;
}

OSStatus FaustAUEffect::GetParameterInfo(AudioUnitScope inScope,
        AudioUnitParameterID inParameterID,
        AudioUnitParameterInfo &outParameterInfo)
{
    OSStatus result = noErr;

    char name[100];
    CFStringRef str;

    outParameterInfo.flags = kAudioUnitParameterFlag_IsWritable + kAudioUnitParameterFlag_IsReadable;

    if (inScope == kAudioUnitScope_Global)
    {

        if (dspUI && dspUI->fUITable[inParameterID]
                && dspUI->fUITable[inParameterID]->fZone)
        {

            if (dynamic_cast<auButton*>(dspUI->fUITable[inParameterID]))
            {
                auToggleButton* toggle = (auToggleButton*) dspUI->fUITable[inParameterID];
                toggle->GetName(name);
                str = CFStringCreateWithCString(kCFAllocatorDefault, name, 0);

                AUBase::FillInParameterName(outParameterInfo, str, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Boolean;
                outParameterInfo.minValue = 0;
                outParameterInfo.maxValue = 1;
                outParameterInfo.defaultValue = 0;
            }
            else if (dynamic_cast<auToggleButton*>(dspUI->fUITable[inParameterID]))
            {
                auToggleButton* toggle = (auToggleButton*) dspUI->fUITable[inParameterID];
                toggle->GetName(name);

                str = CFStringCreateWithCString(kCFAllocatorDefault, name, 0);

                AUBase::FillInParameterName(outParameterInfo, str, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Boolean;
                outParameterInfo.minValue = 0;
                outParameterInfo.maxValue = 1;
                outParameterInfo.defaultValue = 0;

            }
            else if (dynamic_cast<auCheckButton*>(dspUI->fUITable[inParameterID]))
            {
                auCheckButton* check = (auCheckButton*) dspUI->fUITable[inParameterID];
                check->GetName(name);

                str = CFStringCreateWithCString(kCFAllocatorDefault, name, 0);

                AUBase::FillInParameterName(outParameterInfo, str, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Boolean;
                outParameterInfo.minValue = 0;
                outParameterInfo.maxValue = 1;
                outParameterInfo.defaultValue = 0;
            }
            else
            {
                auSlider* slider = (auSlider*) dspUI->fUITable[inParameterID];
                slider->GetName(name);
                str = CFStringCreateWithCString(kCFAllocatorDefault, name, 0);

                AUBase::FillInParameterName(outParameterInfo, str, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
                outParameterInfo.minValue = slider->fMin;
                outParameterInfo.maxValue = slider->fMax;
                outParameterInfo.defaultValue = slider->fInit;
            }

        }
    }
    else
    {
        result = kAudioUnitErr_InvalidParameter;
    }

    return result;
}

void FaustAUEffect::SetParameter(AudioUnitParameterID paramID,
                                 AudioUnitParameterValue value)
{
    AUEffectBase::SetParameter(paramID, value);
}

OSStatus FaustAUEffect::SetParameter(AudioUnitParameterID inID, AudioUnitScope inScope,
                                     AudioUnitElement inElement, AudioUnitParameterValue inValue,
                                     UInt32 inBufferOffsetInFrames)
{
    if (inScope == kAudioUnitScope_Global)
    {

        if (dspUI)
        {
            if (dspUI->fUITable[inID] && dspUI->fUITable[inID]->fZone)
                *(dspUI->fUITable[inID]->fZone) = (FAUSTFLOAT) inValue;

            if (dynamic_cast<auButton*>(dspUI->fUITable[inID]))
                return AUEffectBase::SetParameter(inID, inScope, inElement, 0,
                                                  inBufferOffsetInFrames);

        }
    }

    return AUEffectBase::SetParameter(inID, inScope, inElement, inValue,
                                      inBufferOffsetInFrames);
}


OSStatus FaustAUEffect::NewFactoryPresetSet(const AUPreset & inNewFactoryPreset)
{
    SInt32 chosenPreset = inNewFactoryPreset.presetNumber;

    for (int i = 0; i < kNumberPresets; ++i)
    {
        if (chosenPreset == kPresets[i].presetNumber)
        {
            switch (chosenPreset)
            {
                case kPreset_One:
                    break;
            }

            SetAFactoryPresetAsCurrent(kPresets[i]);
            return noErr;
        }
    }

    return kAudioUnitErr_InvalidPropertyValue;
}

OSStatus FaustAUEffect::GetPresets(CFArrayRef * outData) const
{
    if (outData == NULL) {
        return noErr;
    }

    CFMutableArrayRef theArray = CFArrayCreateMutable(NULL, kNumberPresets,
                                 NULL);
    for (int i = 0; i < kNumberPresets; ++i)
    {
        CFArrayAppendValue(theArray, &kPresets[i]);
    }

    *outData = (CFArrayRef) theArray;
    return noErr;
}

OSStatus FaustAUEffect::GetPropertyInfo(AudioUnitPropertyID inID,
        AudioUnitScope inScope,
        AudioUnitElement inElement,
        UInt32& outDataSize,
        Boolean& outWritable)
{
    if (inScope == kAudioUnitScope_Global)
    {
        switch (inID)
        {
            case kAudioUnitProperty_CocoaUI:
                outWritable = false;
                outDataSize = sizeof (AudioUnitCocoaViewInfo);
                return noErr;

            case kAudioUnitCustomProperty_dspUI:
            {
                if(inScope != kAudioUnitScope_Global ) return kAudioUnitErr_InvalidScope;
                outWritable = false;
                outDataSize = sizeof (int*);
                return noErr;
            }
        }
    }

    return AUEffectBase::GetPropertyInfo (inID, inScope, inElement, outDataSize, outWritable);
}

OSStatus FaustAUEffect::GetProperty(AudioUnitPropertyID inID,
                                    AudioUnitScope inScope,
                                    AudioUnitElement inElement,
                                    void* outData)
{
    switch (inID)
    {

        // This property allows the host application to find the UI associated with this AudioUnit
        case kAudioUnitProperty_CocoaUI:
        {
            // Look for a resource in the main bundle by name and type.
            CFBundleRef bundle = CFBundleGetBundleWithIdentifier( CFSTR("com.grame.audiounit.FaustAU") );
            if (bundle == NULL) return fnfErr;

            CFURLRef bundleURL = CFBundleCopyResourceURL( bundle,
                                 CFSTR("FaustAUCustomView"),	// this is the name of the cocoa bundle as specified in the CocoaViewFactory.plist
                                 CFSTR("bundle"),			// this is the extension of the cocoa bundle
                                 NULL);

            if (bundleURL == NULL) return fnfErr;

            CFStringRef className = CFSTR("FaustAU_CustomViewFactory");	// name of the main class that implements the AUCocoaUIBase protocol
            AudioUnitCocoaViewInfo cocoaInfo = { bundleURL, { className }};
            *((AudioUnitCocoaViewInfo *)outData) = cocoaInfo;

            return noErr;
        }

        // This is our custom property which reports the dspUI
        case kAudioUnitCustomProperty_dspUI:
        {
            if (inScope != kAudioUnitScope_Global) {
                return kAudioUnitErr_InvalidScope;
            }

            // the kernels are only created if we are initialized
            // since we're using the kernels to get the curve info, let
            // the caller know we can't do it if we're un-initialized
            // the UI should check for the error and not draw the curve in this case
            if(!IsInitialized() ) return kAudioUnitErr_Uninitialized;
            *((auUI**)outData)= dspUI;
            return noErr;
        }
    }

    // if we've gotten this far, handles the standard properties
    return AUEffectBase::GetProperty(inID, inScope, inElement, outData);
}

OSStatus FaustAUEffect::ProcessBufferLists(AudioUnitRenderActionFlags& iFlags,
        const AudioBufferList& inBufferList, AudioBufferList& outBufferList,
        UInt32 iFrames)
{

    int inChannels = dsp->getNumInputs();
    int outChannels = dsp->getNumOutputs();

    // audio data type conversion before faust computation
    FAUSTFLOAT* inputData[inChannels];
    FAUSTFLOAT* outputData[outChannels];
    for (int i = 0; i < inChannels; i++)
    {
        inputData[i] = (FAUSTFLOAT*) inBufferList.mBuffers[i].mData;
    }

    for (int i=0; i < outChannels; i++)
    {
        outputData[i] = (FAUSTFLOAT*) outBufferList.mBuffers[i].mData;
    }

    dsp->compute(iFrames, inputData, outputData);

    // give data back to AU
    for (int i = 0; i < outChannels; i++)
    {
        outBufferList.mBuffers[i].mData = outputData[i];
    }

    //TODO
    /*
     AudioUnitEvent myEvent;
     myEvent.mArgument.mParameter.mAudioUnit = mComponentInstance;
     myEvent.mArgument.mParameter.mScope = kAudioUnitScope_Global;
     myEvent.mArgument.mParameter.mElement = 0;
     myEvent.mEventType = kAudioUnitEvent_ParameterValueChange;

     if (dspUI)
     {
     for (int i = 0; i < dspUI->fUITable.size(); i++)
     {
     myEvent.mArgument.mParameter.mParameterID = i; //TODO
     AUEventListenerNotify(NULL, NULL, &myEvent);
     }
     }
     */
    return noErr;
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/
