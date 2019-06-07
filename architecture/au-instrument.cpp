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
 In order to compile a AU (TM) Synth plugin with this architecture file
 you will need the proprietary AU SDK from Apple. Please check
 the corresponding license.

 ************************************************************************
 ************************************************************************/

#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string>
#include <vector>

#include "AUInstrumentBase.h"
#include "FaustAUVersion.h"
#include "faust/misc.h"
#include "FaustAU.h"

using namespace std;

static const UInt32 kNumNotes = 32;
static const UInt32 kMaxActiveNotes = 32;

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/

<<includeIntrinsic>>

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

class FaustAUInstrument;

struct FaustAUInstrumentNote : public SynthNote
{

    FaustAUInstrumentNote();
    virtual ~FaustAUInstrumentNote();

    virtual OSStatus Initialize();
    virtual bool Attack(const MusicDeviceNoteParams &inParams);
    virtual void Kill(UInt32 inFrame); // voice is being stolen.
    virtual void Release(UInt32 inFrame);
    virtual void FastRelease(UInt32 inFrame);
    void ReleaseAux();
    virtual Float32 Amplitude()
    {
        return amp;
    } // used for finding quietest note for voice stealing.
    virtual OSStatus Render(UInt64 inAbsoluteSampleFrame, UInt32 inNumFrames,
                            AudioBufferList** inBufferList, UInt32 inOutBusCount);
    FaustAUInstrument* synth;
    double amp;
   
    auUI* dspUI = NULL;
    mydsp* dsp = NULL;
    double fSampleRate = -1;

};

class FaustAUInstrument: public AUMonotimbralInstrumentBase
{

public:

    FaustAUInstrument(ComponentInstance inComponentInstance);
    virtual ~FaustAUInstrument();

    virtual OSStatus Initialize();
    virtual void Cleanup();
    virtual OSStatus Version()
    {
        return kFaustAUVersion;
    }

    virtual AUElement* CreateElement(AudioUnitScope scope,
                                     AudioUnitElement element);

    virtual OSStatus GetPropertyInfo (AudioUnitPropertyID inID,
                                      AudioUnitScope inScope,
                                      AudioUnitElement inElement,
                                      UInt32& outDataSize,
                                      Boolean& outWritable);

    virtual OSStatus GetProperty(AudioUnitPropertyID inID,
                                 AudioUnitScope inScope,
                                 AudioUnitElement inElement,
                                 void* outData);

    virtual OSStatus GetParameterInfo(AudioUnitScope inScope,
                                      AudioUnitParameterID inParameterID,
                                      AudioUnitParameterInfo& outParameterInfo);

    void SetParameter(AudioUnitParameterID paramID,
                      AudioUnitParameterValue value);

    virtual OSStatus SetParameter(AudioUnitParameterID inID,
                                  AudioUnitScope inScope, AudioUnitElement inElement,
                                  AudioUnitParameterValue inValue, UInt32);

    MidiControls* GetControls(MusicDeviceGroupID inChannel)
    {
        SynthGroupElement *group = GetElForGroupID(inChannel);
        return (MidiControls *) group->GetMIDIControlHandler();
    }

    mydsp* dsp = NULL;
    
    float freqMin = 0.0;
    float freqMax = 1.0;
    
    int frequencyParameterID = -1;
    int gateParameterID = -1;
    int gainParameterID = -1;

private:

    FaustAUInstrumentNote mNotes[kNumNotes];
    auUI* dspUI = NULL;

};

bool FaustAUInstrumentNote::Attack(const MusicDeviceNoteParams& inParams)
{
    amp = inParams.mVelocity / 127.;
    if (synth->gateParameterID != -1)
    {
        double sr = SampleRate();
        if (fSampleRate != sr) {
            dsp->init(int(sr));
            fSampleRate = sr;
        }
        auUIObject* gate = (auUIObject*) dspUI->fUITable[synth->gateParameterID];
        if (gate) {
            gate->SetValue(1.0); // Tell Faust code to enter "attack" phase
        }
    }
    return true;
}

/**********************************************************************************/

AUDIOCOMPONENT_ENTRY(AUMusicDeviceFactory, FaustAU)

//TODO set the output channels
FaustAUInstrument::FaustAUInstrument(ComponentInstance inComponentInstance)
    : AUMonotimbralInstrumentBase(inComponentInstance, 0, 1)
{
    CreateElements();

    dspUI = new auUI();
    dsp = new mydsp();

    //int inChannels = dsp->getNumInputs();
    //int outChannels = dsp->getNumOutputs();
    //SetParamHasSampleRateDependency(true);

    dsp->buildUserInterface(dspUI);
    Globals()->UseIndexedParameters(dspUI->fUITable.size());

    if (dspUI)
    {
        for (int i = 0; i < dspUI->fUITable.size(); i++)
        {
            if (dspUI->fUITable[i] && dspUI->fUITable[i]->fZone)
            {
                if (dynamic_cast<auButton*>(dspUI->fUITable[i]))
                {
                    Globals()->SetParameter(i, 0);
                }
                else if (dynamic_cast<auToggleButton*>(dspUI->fUITable[i]))
                {
                    Globals()->SetParameter(i, 0);
                }
                else if (dynamic_cast<auCheckButton*>(dspUI->fUITable[i]))
                {
                    Globals()->SetParameter(i, 0);
                }
                else
                {
                    auSlider* slider = (auSlider*)dspUI->fUITable[i];
                    Globals()->SetParameter(i, slider->fInit);
                }
            }
        }
    }
}

FaustAUInstrument::~FaustAUInstrument()
{
    delete dsp;
    delete dspUI;
}

void FaustAUInstrument::Cleanup()
{}

OSStatus FaustAUInstrument::Initialize()
{
    OSStatus result = AUMonotimbralInstrumentBase::Initialize();

    for (int i = 0; i < kNumNotes; i++)
    {
        mNotes[i].Initialize();
        mNotes[i].synth = this;
    }

    SetNotes(kNumNotes, kMaxActiveNotes, mNotes, sizeof(FaustAUInstrumentNote));
    return result;
}

AUElement* FaustAUInstrument::CreateElement(AudioUnitScope scope, AudioUnitElement element)
{
    switch (scope)
    {
        case kAudioUnitScope_Group:
            return new SynthGroupElement(this, element, new MidiControls);
        case kAudioUnitScope_Part:
            return new SynthPartElement(this, element);
        default:
            return AUBase::CreateElement(scope, element);
    }
}

OSStatus FaustAUInstrument::GetPropertyInfo(AudioUnitPropertyID inID,
        AudioUnitScope inScope,
        AudioUnitElement inElement,
        UInt32& outDataSize,
        Boolean& outWritable)
{
    if (inScope == kAudioUnitScope_Global) {

        switch (inID)
        {
            case kAudioUnitProperty_CocoaUI:
                outWritable = false;
                outDataSize = sizeof (AudioUnitCocoaViewInfo);
                return noErr;

            case kAudioUnitCustomProperty_dspUI:
            {
                if (inScope != kAudioUnitScope_Global ) return kAudioUnitErr_InvalidScope;
                outWritable = false;
                outDataSize = sizeof (int*);
                return noErr;
            }
        }
    }

    return AUInstrumentBase::GetPropertyInfo (inID, inScope, inElement, outDataSize, outWritable);
}

OSStatus FaustAUInstrument::GetProperty(AudioUnitPropertyID inID,
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

            CFURLRef bundleURL = CFBundleCopyResourceURL(bundle,
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
            if(inScope != kAudioUnitScope_Global)
                return kAudioUnitErr_InvalidScope;

            // the kernels are only created if we are initialized
            // since we're using the kernels to get the curve info, let
            // the caller know we can't do it if we're un-initialized
            // the UI should check for the error and not draw the curve in this case
            if (!IsInitialized()) return kAudioUnitErr_Uninitialized;
            *((auUI**)outData)= mNotes[0].dspUI; //TODO
            return noErr;
        }
    }

    // if we've gotten this far, handles the standard properties
    return AUInstrumentBase::GetProperty (inID, inScope, inElement, outData);
}

OSStatus FaustAUInstrument::GetParameterInfo(AudioUnitScope inScope,
        AudioUnitParameterID inParameterID,
        AudioUnitParameterInfo& outParameterInfo)
{

    OSStatus result = noErr;
    char name[100];
    CFStringRef str;

    outParameterInfo.flags = kAudioUnitParameterFlag_IsWritable
                             + kAudioUnitParameterFlag_IsReadable;

    if (inScope == kAudioUnitScope_Global)
    {

        if (dspUI && dspUI->fUITable[inParameterID]
                && dspUI->fUITable[inParameterID]->fZone)
        {

            if (dynamic_cast<auButton*>(dspUI->fUITable[inParameterID]) ||
                dynamic_cast<auToggleButton*>(dspUI->fUITable[inParameterID]) ||
                dynamic_cast<auCheckButton*>(dspUI->fUITable[inParameterID]))
            {
                dspUI->fUITable[inParameterID]->GetName(name);
                if (strcmp(name, "gate") == 0)
                {
                    // Faust synth modules use "gate" as the name for the parameter
                    // to be set to 1 by MIDI-in NoteOn and set to 0 by NoteOff.
                    // We leave it in the AU GUI for manual testing w/o MIDI.
                    gateParameterID = inParameterID;
                }
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
                if (strcmp(name, "gain") == 0)
                {
                    // Faust synth modules use "gain" as the name for the parameter
                    // to be set by MIDI-in NoteOn key velocity:
                    // We leave it in the AU GUI for manual testing w/o MIDI.
                    gainParameterID = inParameterID;
                    // gainMin = slider->fMin;
                    // gainMax = slider->fMax;
                }
                else if (strcmp(name, "freq") == 0)
                {
                    frequencyParameterID = inParameterID;
                    freqMin = slider->fMin;
                    freqMax = slider->fMax;
                }
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

OSStatus FaustAUInstrument::SetParameter(AudioUnitParameterID inID,
        AudioUnitScope inScope, AudioUnitElement inElement,
        AudioUnitParameterValue inValue, UInt32 inBufferOffsetInFrames)
{
    if (inScope == kAudioUnitScope_Global)
    {

        if (dspUI)
        {
            if (dspUI->fUITable[inID] && dspUI->fUITable[inID]->fZone)

                *(dspUI->fUITable[inID]->fZone) = (FAUSTFLOAT) inValue;

            for (int i = 0; i < kNumNotes; i++)
            {
                if (mNotes[i].dspUI)
                    *(mNotes[i].dspUI->fUITable[inID]->fZone) =
                        (FAUSTFLOAT) inValue;
            }
        }
    }

    return AUMonotimbralInstrumentBase::SetParameter(inID, inScope, inElement,
            inValue, inBufferOffsetInFrames);
}

/**********************************************************************************/

FaustAUInstrumentNote::FaustAUInstrumentNote():SynthNote()
{}

OSStatus FaustAUInstrumentNote::Initialize()
{
    dspUI = new auUI();
    dsp = new mydsp();
    dsp->buildUserInterface(dspUI);
    // SampleRate() cannot be used here, to moved in Attack
 
    return noErr;
}

FaustAUInstrumentNote::~FaustAUInstrumentNote()
{
    delete dsp;
    delete dspUI;
}

void FaustAUInstrumentNote::ReleaseAux()
{
    if (synth->gateParameterID != -1)
    {
        if (dspUI)
        {
            auUIObject* gate = (auUIObject*) dspUI->fUITable[synth->gateParameterID];
            if (gate) {
                gate->SetValue(0.0); // Tell Faust code to enter "release" phase
            }
        }
    }
}

void FaustAUInstrumentNote::Release(UInt32 inFrame)
{
    ReleaseAux();
    SynthNote::Release(inFrame);
}

void FaustAUInstrumentNote::FastRelease(UInt32 inFrame) // voice is being stolen.
{
    ReleaseAux();
    SynthNote::Release(inFrame);
}

void FaustAUInstrumentNote::Kill(UInt32 inFrame) // voice is being stolen.
{
    ReleaseAux();
    SynthNote::Kill(inFrame);
}

OSStatus FaustAUInstrumentNote::Render(UInt64 inAbsoluteSampleFrame,
                                       UInt32 inNumFrames, AudioBufferList** inBufferList,
                                       UInt32 inOutBusCount)
{
    int MAX_OUT_CHANNELS = 1000;

    float* outBuffer[MAX_OUT_CHANNELS];
    float* audioData[MAX_OUT_CHANNELS];

    int inChannels = dsp->getNumInputs();
    int outChannels = dsp->getNumOutputs();

    // bus number is assumed to be zero
    for (int i = 0; i < outChannels; i++)
    {
        outBuffer[i] = new float[inNumFrames];
        audioData[i] = (float*)inBufferList[0]->mBuffers[i].mData;
    }

    if (synth)
    {
        auSlider* frequencySlider = NULL;
        if (synth->frequencyParameterID != -1)
        {
            if (dspUI) {
                frequencySlider = (auSlider*) dspUI->fUITable[synth->frequencyParameterID];
            }
            if (frequencySlider) {
                //TODO change the SetValue function call accordingly
                frequencySlider->SetValue((Frequency() - synth->freqMin) / (synth->freqMax - synth->freqMin));
                //frequencySlider->SetValue((float) GetMidiKey() / 88.0);
            }
        }

        dsp->compute(inNumFrames, audioData, outBuffer);
    }
    switch (GetState())
    {
        case kNoteState_Attacked:
        case kNoteState_Sostenutoed:
        case kNoteState_ReleasedButSostenutoed:
        case kNoteState_ReleasedButSustained:
        {
            for (int i = 0; i < outChannels; i++)
            {
                for (UInt32 frame = 0; frame < inNumFrames; ++frame)
                {
                    audioData[i][frame] += outBuffer[i][frame] * amp;
                }
            }
            break;
        }

        case kNoteState_Released:
        case kNoteState_FastReleased:
        {
            NoteEnded(0xFFFFFFFF);
            break;
        }
        default:
            break;
    }
    return noErr;
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/
