/************************** BEGIN coreaudio-ios-dsp.h ********************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __coreaudio_ios_dsp__
#define __coreaudio_ios_dsp__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>

#include "faust/audio/audio.h"
#include "faust/dsp/dsp.h"

#include <AudioToolbox/AudioConverter.h>
#include <AudioToolbox/AudioServices.h>
#include <AudioUnit/AudioUnit.h>

/******************************************************************************
*******************************************************************************

							COREAUDIO INTERFACE

*******************************************************************************
*******************************************************************************/

#define OPEN_ERR -1
#define NO_ERR 0

class TiPhoneCoreAudioRenderer {

    protected:

        AudioUnit fAUHAL;

        int	fDevNumInChans;
        int	fDevNumOutChans;

        int fHWNumInChans;
        int fHWNumOutChans;

        dsp* fDSP;
    
        audio* fAudio;

        AudioBufferList* fCAInputData;

        static void PrintStreamDesc(AudioStreamBasicDescription *inDesc)
        {
            printf("- - - - - - - - - - - - - - - - - - - -\n");
            printf("  Sample Rate:%f\n", inDesc->mSampleRate);
            printf("  Format ID:%.*s\n", (int) sizeof(inDesc->mFormatID), (char*)&inDesc->mFormatID);
            printf("  Format Flags:%lX\n", inDesc->mFormatFlags);
            printf("  Bytes per Packet:%ld\n", inDesc->mBytesPerPacket);
            printf("  Frames per Packet:%ld\n", inDesc->mFramesPerPacket);
            printf("  Bytes per Frame:%ld\n", inDesc->mBytesPerFrame);
            printf("  Channels per Frame:%ld\n", inDesc->mChannelsPerFrame);
            printf("  Bits per Channel:%ld\n", inDesc->mBitsPerChannel);
            printf("- - - - - - - - - - - - - - - - - - - -\n");
        }

        static void printError(OSStatus err)
        {
            switch (err) {
                case kAudioConverterErr_FormatNotSupported:
                    printf("error code : kAudioConverterErr_FormatNotSupported\n");
                    break;
                case kAudioConverterErr_OperationNotSupported:
                    printf("error code : kAudioConverterErr_OperationNotSupported\n");
                    break;
                case kAudioConverterErr_PropertyNotSupported:
                    printf("error code : kAudioConverterErr_PropertyNotSupported\n");
                    break;
                case kAudioConverterErr_InvalidInputSize:
                    printf("error code : kAudioConverterErr_InvalidInputSize\n");
                    break;
                case kAudioConverterErr_InvalidOutputSize:
                    printf("error code : kAudioConverterErr_InvalidOutputSize\n");
                    break;
                case kAudioConverterErr_UnspecifiedError:
                    printf("error code : kAudioConverterErr_UnspecifiedError\n");
                    break;
                case kAudioConverterErr_BadPropertySizeError:
                    printf("error code : kAudioConverterErr_BadPropertySizeError\n");
                    break;
                case kAudioConverterErr_RequiresPacketDescriptionsError:
                    printf("error code : kAudioConverterErr_RequiresPacketDescriptionsError\n");
                    break;
                case kAudioConverterErr_InputSampleRateOutOfRange:
                    printf("error code : kAudioConverterErr_InputSampleRateOutOfRange\n");
                    break;
                case kAudioConverterErr_OutputSampleRateOutOfRange:
                    printf("error code : kAudioConverterErr_OutputSampleRateOutOfRange\n");
                    break;
                default:
                    printf("error code : unknown\n");
                    break;
            }
        }

        static OSStatus Render(void *inRefCon,AudioUnitRenderActionFlags *ioActionFlags,
                               const AudioTimeStamp *inTimeStamp,
                               UInt32,
                               UInt32 inNumberFrames,
                               AudioBufferList *ioData)
        {
            return static_cast<TiPhoneCoreAudioRenderer*>(inRefCon)->Render(ioActionFlags, inTimeStamp, inNumberFrames, ioData);
        }

        OSStatus Render(AudioUnitRenderActionFlags *ioActionFlags,
                        const AudioTimeStamp *inTimeStamp,
                        UInt32 inNumberFrames,
                        AudioBufferList *ioData)
        {
            OSStatus err = noErr;

            if (fDevNumInChans > 0) {
                err = AudioUnitRender(fAUHAL, ioActionFlags, inTimeStamp, 1, inNumberFrames, fCAInputData);
            }

            if (err == noErr) {
                float* fInChannel[fDevNumInChans];
                float* fOutChannel[fDevNumOutChans];

                for (int chan = 0; chan < fDevNumInChans; chan++) {
                    fInChannel[chan] = (float*)fCAInputData->mBuffers[chan].mData;
                }

                for (int chan = 0; chan < fDevNumOutChans; chan++) {
                    fOutChannel[chan] = (float*)ioData->mBuffers[chan].mData;
                }

                fDSP->compute((int)inNumberFrames, fInChannel, fOutChannel);
                
                fAudio->runControlCallbacks();
            }
            return err;
        }

        static void InterruptionListener(void *inClientData, UInt32 inInterruption)
        {
            TiPhoneCoreAudioRenderer *obj = (TiPhoneCoreAudioRenderer*)inClientData;
            printf("Session interrupted! --- %s ---", (inInterruption == kAudioSessionBeginInterruption) ? "Begin Interruption" : "End Interruption");

            if (inInterruption == kAudioSessionEndInterruption) {
                // Make sure we are again the active session
                AudioSessionSetActive(true);
                obj->SetupMixing();
                AudioOutputUnitStart(obj->fAUHAL);
            }

            if (inInterruption == kAudioSessionBeginInterruption) {
                AudioOutputUnitStop(obj->fAUHAL);
            }
        }
    
        int SetupMixing()
        {
            OSStatus err;

            /*
            01/07/2014 : cause iRig to fail, so deactivated for now...
            CFStringRef route;
            UInt32 routesize = sizeof(route);
            OSStatus err  = AudioSessionGetProperty(kAudioSessionProperty_AudioRoute, &routesize, &route);
            if (err == noErr) {
                if (CFStringCompare(route, CFSTR("ReceiverAndMicrophone"), 0) == kCFCompareEqualTo || CFStringCompare(route,CFSTR("Receiver"), 0) == kCFCompareEqualTo) {
                    // Re-route audio to the speaker (not the receiver, which no music app will ever want)
                    printf("Rerouting audio to speaker\n");
                    UInt32 newRoute = kAudioSessionOverrideAudioRoute_Speaker;
                    AudioSessionSetProperty(kAudioSessionProperty_OverrideAudioRoute, sizeof(newRoute), &newRoute);
                }
             }
            */

            UInt32 allowMixing = true;
            err = AudioSessionSetProperty(kAudioSessionProperty_OverrideCategoryMixWithOthers, sizeof(allowMixing), &allowMixing);
            if (err != noErr) {
                printf("Could not set audio session mixing\n");
                printError(err);
                return -1;
            } else {
                return 0;
            }
        }

        static void AudioSessionPropertyListener(void* inClientData, AudioSessionPropertyID inID, UInt32 inDataSize, const void* inData)
        {
            TiPhoneCoreAudioRenderer *obj = (TiPhoneCoreAudioRenderer*)inData;
            switch (inID) {
                case kAudioSessionProperty_ServerDied: {
                    printf("kAudioSessionProperty_ServerDied\n");
                    break;
                }
                case kAudioSessionProperty_AudioRouteChange: {
                    printf("kAudioSessionProperty_AudioRouteChange\n");
                    obj->SetupMixing();
                    break;
                }
                case kAudioSessionProperty_AudioInputAvailable: {
                    printf("kAudioSessionProperty_AudioInputAvailable\n");
                    obj->SetupMixing();
                    break;
                }
            }
        }

        static int SetAudioCategory(int input, int output)
        {
            // Set the audioCategory the way Faust DSP wants
            UInt32 audioCategory;
            if ((input > 0) && (output > 0)) {
                audioCategory = kAudioSessionCategory_PlayAndRecord;
                printf("AudioCategory kAudioSessionCategory_PlayAndRecord\n");
            } else if (input > 0) {
                audioCategory = kAudioSessionCategory_RecordAudio;
                printf("AudioCategory kAudioSessionCategory_RecordAudio\n");
            } else  if (output > 0) {
                audioCategory = kAudioSessionCategory_MediaPlayback;
                printf("AudioCategory kAudioSessionCategory_MediaPlayback\n");
            }

            OSStatus err = AudioSessionSetProperty(kAudioSessionProperty_AudioCategory, sizeof(audioCategory), &audioCategory);
            if (err != noErr) {
                printf("Couldn't set audio category\n");
                printError(err);
                return OPEN_ERR;
            }

            // 09/07/2015 : https://developer.apple.com/library/ios/qa/qa1754/_index.html
            if (audioCategory == kAudioSessionCategory_PlayAndRecord) {
                
                // 21/09/2017 Compatible with bluetooth devices. Deactivate bluetooth micro which run at 16khz, use internal micro instead.
                /*
                UInt32 overrideAudioRoute = 1;
                err = AudioSessionSetProperty(kAudioSessionProperty_OverrideCategoryDefaultToSpeaker, sizeof(UInt32), &overrideAudioRoute);
                if (err != noErr) {
                    printf("Error setting kAudioSessionProperty_OverrideCategoryDefaultToSpeaker\n");
                    printError(err);
                }

                UInt32 allowBluetoothInput = 1;
                err = AudioSessionSetProperty(kAudioSessionProperty_OverrideCategoryEnableBluetoothInput, sizeof(UInt32), &allowBluetoothInput);
                if (err != noErr) {
                    printf("Error setting kAudioSessionProperty_OverrideCategoryEnableBluetoothInput\n");
                    printError(err);
                }
                */
                
                // On devices with more than one built-in microphone, the microphone closest to the video camera is used.
                UInt32 allowInternalInput = kAudioSessionMode_VideoRecording;
                err = AudioSessionSetProperty(kAudioSessionProperty_Mode, sizeof(UInt32), &allowInternalInput);
                if (err != noErr) {
                    printf("Error setting kAudioSessionMode_VideoRecording\n");
                    printError(err);
                }

            }

        #if NOAGC
            // If input is used, disable AGC
            if (audioCategory == kAudioSessionCategory_RecordAudio || audioCategory == kAudioSessionCategory_PlayAndRecord) {

                UInt32 sessionMode = kAudioSessionMode_Measurement;
                err = AudioSessionSetProperty(kAudioSessionProperty_Mode, sizeof(sessionMode), &sessionMode);
                if (err != noErr) {
                    printf("Error setting kAudioSessionMode_Measurement\n");
                    printError(err);
                }

                UInt32 availableGain;
                UInt32 outSize = sizeof(availableGain);
                err = AudioSessionGetProperty(kAudioSessionProperty_InputGainAvailable, &outSize, &availableGain);
                if (err != noErr) {
                    printf("Error getting kAudioSessionProperty_InputGainAvailable\n");
                    printError(err);
                } else {
                    Float32 gain;
                    printf("Getting kAudioSessionProperty_InputGainAvailable OK\n");
                    outSize = sizeof(Float32);
                    AudioSessionGetProperty(kAudioSessionProperty_InputGainScalar, &outSize, &gain);
                    printf("Getting kAudioSessionProperty_InputGainScalar :  %f\n", gain);
                    gain = 1.0f;
                    err = AudioSessionSetProperty(kAudioSessionProperty_InputGainScalar, sizeof(Float32), &gain);
                    if (err != noErr) {
                        printf("Error setting kAudioSessionProperty_InputGainScalar\n");
                        printError(err);
                    } else {
                        printf("Setting kAudioSessionProperty_InputGainAvailable to 1.0 OK\n");
                    }
                }
            }
        #endif

            return NO_ERR;
        }

        int SetParameters(int bufferSize, int samplerate)
        {
            OSStatus err;
            UInt32 outSize;
            UInt32 enableIO;
            AudioStreamBasicDescription srcFormat, dstFormat;

            printf("SetParameters fDevNumInChans = %d fDevNumOutChans = %d bufferSize = %d samplerate = %d\n", fDevNumInChans, fDevNumOutChans, bufferSize, samplerate);

            err = AudioSessionSetActive(true);
            if (err != noErr) {
                printf("Couldn't set audio session active\n");
                printError(err);
                return OPEN_ERR;
            }

            AudioSessionAddPropertyListener(kAudioSessionProperty_AudioRouteChange, AudioSessionPropertyListener, this);
            AudioSessionAddPropertyListener(kAudioSessionProperty_AudioInputAvailable, AudioSessionPropertyListener, this);
            AudioSessionAddPropertyListener(kAudioSessionProperty_ServerDied, AudioSessionPropertyListener, this);

            if (SetAudioCategory(fDevNumInChans, fDevNumOutChans) != NO_ERR) {
                return OPEN_ERR;
            }

            // Scan Hardware
            outSize = sizeof(fHWNumInChans);
            err = AudioSessionGetProperty(kAudioSessionProperty_CurrentHardwareInputNumberChannels, &outSize, &fHWNumInChans);
            if (err != noErr) {
                fHWNumInChans = 0;
                printf("Couldn't get hw input channels\n");
                printError(err);
            } else {
                printf("Get hw input channels %d\n", fHWNumInChans);
            }

            outSize = sizeof(fHWNumOutChans);
            err = AudioSessionGetProperty(kAudioSessionProperty_CurrentHardwareOutputNumberChannels, &outSize, &fHWNumOutChans);
            if (err != noErr) {
                fHWNumOutChans = 0;
                printf("Couldn't get hw output channels\n");
                printError(err);
            } else {
                printf("Get hw output channels %d\n", fHWNumOutChans);
            }
            /*
            // Possibly reset the audioCategory the way hardware allows
            // 21/09/2017 cause problem when use bluetooth, deactive for now
            if (SetAudioCategory(fHWNumInChans, fHWNumOutChans) != NO_ERR) {
                return OPEN_ERR;
            }
            */
            if (SetupMixing() < 0) {
                return OPEN_ERR;
            }

            Float64 hwSampleRate;
            outSize = sizeof(hwSampleRate);
            err = AudioSessionGetProperty(kAudioSessionProperty_CurrentHardwareSampleRate, &outSize, &hwSampleRate);
            if (err != noErr) {
                printf("Couldn't get hw sample rate\n");
                printError(err);
                return OPEN_ERR;
            } else {
                printf("Get hw sample rate %f\n", hwSampleRate);
            }

            Float32 hwBufferSize;
            outSize = sizeof(hwBufferSize);
            err = AudioSessionGetProperty(kAudioSessionProperty_CurrentHardwareIOBufferDuration, &outSize, &hwBufferSize);
            if (err != noErr) {
                printf("Couldn't get hw buffer duration\n");
                printError(err);
                return OPEN_ERR;
            } else {
                printf("Get hw buffer duration %f\n", hwBufferSize);
            }

            Float32 preferredPeriodDuration = float(bufferSize) / float(samplerate);
            printf("preferredPeriodDuration %f \n", preferredPeriodDuration);

            err = AudioSessionSetProperty(kAudioSessionProperty_PreferredHardwareIOBufferDuration, sizeof(preferredPeriodDuration), &preferredPeriodDuration);
            if (err != noErr) {
                printf("Couldn't set i/o buffer duration\n");
                printError(err);
                return OPEN_ERR;
            }

            Float32 actualPeriodDuration;
            outSize = sizeof(actualPeriodDuration);
            err = AudioSessionGetProperty(kAudioSessionProperty_PreferredHardwareIOBufferDuration, &outSize, &actualPeriodDuration);
            if (err != noErr) {
                printf("Couldn't get hw buffer duration\n");
                printError(err);
                return OPEN_ERR;
            }

            printf("preferredPeriodDuration %f actualPeriodDuration %f\n", preferredPeriodDuration, actualPeriodDuration);
            if (preferredPeriodDuration != actualPeriodDuration) {
                printf("Couldn't set hw buffer duration\n");
                return OPEN_ERR;
            }

            Float64 preferredSamplerate = float(samplerate);
            err = AudioSessionSetProperty(kAudioSessionProperty_PreferredHardwareSampleRate, sizeof(preferredSamplerate), &preferredSamplerate);
            if (err != noErr) {
                printf("Couldn't set i/o sample rate\n");
                printError(err);
                return OPEN_ERR;
            }

            Float32 inputLatency;
            outSize = sizeof(inputLatency);
            err = AudioSessionGetProperty(kAudioSessionProperty_CurrentHardwareInputLatency, &outSize, &inputLatency);
            if (err != noErr) {
                printf("Couldn't get inputLatency\n");
                printError(err);
            } else {
                printf("inputLatency in sec : %f\n", inputLatency);
            }

            Float32 outputLatency;
            outSize = sizeof(outputLatency);
            err = AudioSessionGetProperty(kAudioSessionProperty_CurrentHardwareOutputLatency, &outSize, &outputLatency);
            if (err != noErr) {
                printf("Couldn't get outputLatency\n");
                printError(err);
            } else {
                printf("outputLatency in sec : %f\n", outputLatency);
            }

            // AUHAL
            AudioComponentDescription cd = {kAudioUnitType_Output, kAudioUnitSubType_RemoteIO, kAudioUnitManufacturer_Apple, 0, 0};
            AudioComponent HALOutput = AudioComponentFindNext(NULL, &cd);

            err = AudioComponentInstanceNew(HALOutput, &fAUHAL);
            if (err != noErr) {
                printf("Error calling OpenAComponent\n");
                printError(err);
                goto error;
            }

            enableIO = 1;
            err = AudioUnitSetProperty(fAUHAL, kAudioOutputUnitProperty_EnableIO, kAudioUnitScope_Output, 0, &enableIO, sizeof(enableIO));
            if (err != noErr) {
                printf("Error calling AudioUnitSetProperty - kAudioOutputUnitProperty_EnableIO, kAudioUnitScope_Output\n");
                printError(err);
                goto error;
            }

            if (fDevNumInChans > 0) {
                enableIO = 1;
            } else {
                enableIO = 0;
            }
            err = AudioUnitSetProperty(fAUHAL, kAudioOutputUnitProperty_EnableIO, kAudioUnitScope_Input, 1, &enableIO, sizeof(enableIO));
            if (err != noErr) {
                printf("Error calling AudioUnitSetProperty - kAudioOutputUnitProperty_EnableIO, kAudioUnitScope_Input\n");
                printError(err);
                goto error;
            }

            UInt32 maxFPS;
            outSize = sizeof(maxFPS);
            err = AudioUnitGetProperty(fAUHAL, kAudioUnitProperty_MaximumFramesPerSlice, kAudioUnitScope_Global, 0, &maxFPS, &outSize);
            if (err != noErr) {
                printf("Couldn't get kAudioUnitProperty_MaximumFramesPerSlice\n");
                printError(err);
                goto error;
            } else {
                printf("Get kAudioUnitProperty_MaximumFramesPerSlice %d\n", (unsigned int)maxFPS);
            }

            err = AudioUnitSetProperty(fAUHAL, kAudioUnitProperty_MaximumFramesPerSlice, kAudioUnitScope_Global, 1, (UInt32*)&bufferSize, sizeof(UInt32));
            if (err != noErr) {
                printf("Error calling AudioUnitSetProperty - kAudioUnitProperty_MaximumFramesPerSlice\n");
                printError(err);
                goto error;
            }

            err = AudioUnitSetProperty(fAUHAL, kAudioUnitProperty_MaximumFramesPerSlice, kAudioUnitScope_Global, 0, (UInt32*)&bufferSize, sizeof(UInt32));
            if (err != noErr) {
                printf("Error calling AudioUnitSetProperty - kAudioUnitProperty_MaximumFramesPerSlice\n");
                printError(err);
                goto error;
            }

            err = AudioUnitInitialize(fAUHAL);
            if (err != noErr) {
                printf("Cannot initialize AUHAL unit\n");
                printError(err);
                goto error;
            }

            // Setting format
            if (fDevNumInChans > 0) {
                outSize = sizeof(AudioStreamBasicDescription);
                err = AudioUnitGetProperty(fAUHAL, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Output, 1, &srcFormat, &outSize);
                if (err != noErr) {
                    printf("Error calling AudioUnitGetProperty - kAudioUnitProperty_StreamFormat kAudioUnitScope_Output\n");
                    printError(err);
                }
                PrintStreamDesc(&srcFormat);

                srcFormat.mFormatID = kAudioFormatLinearPCM;
                srcFormat.mFormatFlags = kAudioFormatFlagsNativeFloatPacked | kLinearPCMFormatFlagIsNonInterleaved;
                srcFormat.mBytesPerPacket = sizeof(AudioUnitSampleType);
                srcFormat.mFramesPerPacket = 1;
                srcFormat.mBytesPerFrame = sizeof(AudioUnitSampleType);
                srcFormat.mChannelsPerFrame = fDevNumInChans;
                srcFormat.mBitsPerChannel = 32;

                PrintStreamDesc(&srcFormat);

                err = AudioUnitSetProperty(fAUHAL, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Output, 1, &srcFormat, sizeof(AudioStreamBasicDescription));
                if (err != noErr) {
                    printf("Error calling AudioUnitSetProperty - kAudioUnitProperty_StreamFormat kAudioUnitScope_Output\n");
                    printError(err);
                }
            }

            if (fDevNumOutChans > 0) {
                outSize = sizeof(AudioStreamBasicDescription);
                err = AudioUnitGetProperty(fAUHAL, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input, 0, &dstFormat, &outSize);
                if (err != noErr) {
                    printf("Error calling AudioUnitGetProperty - kAudioUnitProperty_StreamFormat kAudioUnitScope_Input\n");
                    printError(err);
                }
                PrintStreamDesc(&dstFormat);

                dstFormat.mFormatID = kAudioFormatLinearPCM;
                dstFormat.mFormatFlags = kAudioFormatFlagsNativeFloatPacked | kLinearPCMFormatFlagIsNonInterleaved;
                dstFormat.mBytesPerPacket = sizeof(AudioUnitSampleType);
                dstFormat.mFramesPerPacket = 1;
                dstFormat.mBytesPerFrame = sizeof(AudioUnitSampleType);
                dstFormat.mChannelsPerFrame = fDevNumOutChans;
                dstFormat.mBitsPerChannel = 32;

                PrintStreamDesc(&dstFormat);

                err = AudioUnitSetProperty(fAUHAL, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input, 0, &dstFormat, sizeof(AudioStreamBasicDescription));
                if (err != noErr) {
                    printf("Error calling AudioUnitSetProperty - kAudioUnitProperty_StreamFormat kAudioUnitScope_Input\n");
                    printError(err);
                }
            }

            if (fDevNumInChans > 0 && fDevNumOutChans == 0) {
                AURenderCallbackStruct output;
                output.inputProc = Render;
                output.inputProcRefCon = this;
                err = AudioUnitSetProperty(fAUHAL, kAudioOutputUnitProperty_SetInputCallback, kAudioUnitScope_Global, 0, &output, sizeof(output));
                if (err != noErr) {
                    printf("Error calling AudioUnitSetProperty - kAudioUnitProperty_SetRenderCallback 1\n");
                    printError(err);
                    goto error;
                }
            } else {
                AURenderCallbackStruct output;
                output.inputProc = Render;
                output.inputProcRefCon = this;
                err = AudioUnitSetProperty(fAUHAL, kAudioUnitProperty_SetRenderCallback, kAudioUnitScope_Input, 0, &output, sizeof(output));
                if (err != noErr) {
                    printf("Error calling AudioUnitSetProperty - kAudioUnitProperty_SetRenderCallback 0\n");
                    printError(err);
                    goto error;
                }
            }

            // Possibly prepare input buffers
            if (fDevNumInChans > 0) {
                fCAInputData = (AudioBufferList*)malloc(sizeof(float) + fDevNumInChans * sizeof(AudioBuffer));
                fCAInputData->mNumberBuffers = fDevNumInChans;
                for (int i = 0; i < fDevNumInChans; i++) {
                    fCAInputData->mBuffers[i].mNumberChannels = 1;
                    fCAInputData->mBuffers[i].mDataByteSize = bufferSize * sizeof(float);
                    fCAInputData->mBuffers[i].mData = malloc(bufferSize * sizeof(float));
                }
            }

            return NO_ERR;

        error:
            AudioUnitUninitialize(fAUHAL);
            AudioComponentInstanceDispose(fAUHAL);
            return OPEN_ERR;
        }

    public:

        TiPhoneCoreAudioRenderer(audio* audio)
            :fAUHAL(0), fDevNumInChans(0), fDevNumOutChans(0),
            fHWNumInChans(0), fHWNumOutChans(0),
            fDSP(0), fAudio(audio), fCAInputData(NULL)
        {}

        virtual ~TiPhoneCoreAudioRenderer()
        {
            if (fCAInputData) {
                for (int i = 0; i < fDevNumInChans; i++) {
                    free(fCAInputData->mBuffers[i].mData);
                }
                free(fCAInputData);
            }
        }
    
        int Open(dsp* dsp, int inChan, int outChan, int buffersize, int samplerate)
        {
            fDSP = dsp;
            fDevNumInChans = inChan;
            fDevNumOutChans = outChan;
      
            // Initialize and configure the audio session
            OSStatus err = AudioSessionInitialize(NULL, NULL, InterruptionListener, this);
            if (err != noErr && err != kAudioSessionAlreadyInitialized) {
                printf("Couldn't initialize audio session\n");
                printError(err);
                return OPEN_ERR;
            }

            if (SetParameters(buffersize, samplerate) < 0) {
                printf("Cannot set parameters to CoreAudio device\n");
                return OPEN_ERR;
            }

            return NO_ERR;
        }

        int Close()
        {
            AudioUnitUninitialize(fAUHAL);
            AudioComponentInstanceDispose(fAUHAL);
            return NO_ERR;
        }

        int Start()
        {
            AudioSessionSetActive(true);

            if (AudioOutputUnitStart(fAUHAL) != noErr) {
                printf("Error while opening device : device open error\n");
                return OPEN_ERR;
            } else {
                return NO_ERR;
            }
        }

        int Stop()
        {
            AudioSessionSetActive(false);

            if (AudioOutputUnitStop(fAUHAL) != noErr) {
                printf("Error while closing device : device close error\n");
                return OPEN_ERR;
            } else {
                return NO_ERR;
            }
        }

        int GetNumInputs() { return fHWNumInChans; }
        int GetNumOutputs() { return fHWNumOutChans; }

};

/******************************************************************************
 *******************************************************************************

                                CORE AUDIO INTERFACE

 *******************************************************************************
 *******************************************************************************/

class iosaudio : public audio {
    
    protected:

        TiPhoneCoreAudioRenderer fAudioDevice;
        int fSampleRate, fBufferSize;
  
    public:

        iosaudio(int srate, int bsize)
        :fAudioDevice(this), fSampleRate(srate), fBufferSize(bsize)
        {}

        virtual ~iosaudio() { fAudioDevice.Close(); }
   
        virtual bool init(const char* /*name*/, dsp* DSP)
        {
            DSP->init(fSampleRate);
            if (fAudioDevice.Open(DSP, DSP->getNumInputs(), DSP->getNumOutputs(), fBufferSize, fSampleRate) < 0) {
                printf("Cannot open iOS audio device\n");
                return false;
            }
            return true;
        }

        virtual bool start()
        {
            if (fAudioDevice.Start() < 0) {
                printf("Cannot start iOS audio device\n");
                return false;
            }
            return true;
        }

        virtual void stop()
        {
            fAudioDevice.Stop();
        }

        virtual int getBufferSize() { return fBufferSize; }
        virtual int getSampleRate() { return fSampleRate; }

        virtual int getNumInputs() { return fAudioDevice.GetNumInputs(); }
        virtual int getNumOutputs() { return fAudioDevice.GetNumOutputs(); }

};

#endif

/********************END ARCHITECTURE SECTION (part 2/2)****************/
/**************************  END  coreaudio-ios-dsp.h **************************/
