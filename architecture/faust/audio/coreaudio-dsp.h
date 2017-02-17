/************************************************************************
	IMPORTANT NOTE : this file contains two clearly delimited sections :
	the ARCHITECTURE section (in two parts) and the USER section. Each section
	is governed by its own copyright and license. Please check individually
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/

#ifndef __coreaudio_dsp__
#define __coreaudio_dsp__

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <sys/time.h>

#include <AudioToolbox/AudioConverter.h>
#include <CoreAudio/CoreAudio.h>
#include <AudioUnit/AudioUnit.h>
#include <CoreServices/CoreServices.h>

#include "faust/audio/audio.h"
#include "faust/dsp/dsp.h"

/******************************************************************************
*******************************************************************************

							COREAUDIO INTERNAL INTERFACE

*******************************************************************************
*******************************************************************************/

#define OPEN_ERR -1
#define CLOSE_ERR -1
#define NO_ERR 0

#define WAIT_NOTIFICATION_COUNTER 60

typedef	UInt8	CAAudioHardwareDeviceSectionID;
#define	kAudioDeviceSectionInput	((CAAudioHardwareDeviceSectionID)0x01)
#define	kAudioDeviceSectionOutput	((CAAudioHardwareDeviceSectionID)0x00)
#define	kAudioDeviceSectionGlobal	((CAAudioHardwareDeviceSectionID)0x00)
#define	kAudioDeviceSectionWildcard	((CAAudioHardwareDeviceSectionID)0xFF)

class TCoreAudioRenderer;
typedef TCoreAudioRenderer* TCoreAudioRendererPtr;

static void PrintStreamDesc(AudioStreamBasicDescription *inDesc)
{
    printf("- - - - - - - - - - - - - - - - - - - -\n");
    printf("  Sample Rate:%f\n", inDesc->mSampleRate);
    printf("  Format ID:%.*s\n", (int)sizeof(inDesc->mFormatID), (char*)&inDesc->mFormatID);
    printf("  Format Flags:%lX\n", inDesc->mFormatFlags);
    printf("  Bytes per Packet:%ld\n", (long)inDesc->mBytesPerPacket);
    printf("  Frames per Packet:%ld\n", (long)inDesc->mFramesPerPacket);
    printf("  Bytes per Frame:%ld\n", (long)inDesc->mBytesPerFrame);
    printf("  Channels per Frame:%ld\n", (long)inDesc->mChannelsPerFrame);
    printf("  Bits per Channel:%ld\n", (long)inDesc->mBitsPerChannel);
    printf("- - - - - - - - - - - - - - - - - - - -\n");
}

static void printError(OSStatus err)
{
    switch (err) {
        case kAudioHardwareNoError:
            printf("error code : kAudioHardwareNoError\n");
            break;
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
		case kAudioHardwareNotRunningError:
            printf("error code : kAudioHardwareNotRunningError\n");
            break;
        case kAudioHardwareUnknownPropertyError:
            printf("error code : kAudioHardwareUnknownPropertyError\n");
            break;
        case kAudioHardwareIllegalOperationError:
            printf("error code : kAudioHardwareIllegalOperationError\n");
            break;
        case kAudioHardwareBadDeviceError:
            printf("error code : kAudioHardwareBadDeviceError\n");
            break;
        case kAudioHardwareBadStreamError:
            printf("error code : kAudioHardwareBadStreamError\n");
            break;
        case kAudioDeviceUnsupportedFormatError:
            printf("error code : kAudioDeviceUnsupportedFormatError\n");
            break;
        case kAudioDevicePermissionsError:
            printf("error code : kAudioDevicePermissionsError\n");
            break;
        default:
            printf("error code : err = %d\n", err);
            break;
    }
}

static Float64 GetNominalSampleRate(AudioDeviceID inDevice) 
{
    Float64 sampleRate = 0;
    UInt32 outSize =  sizeof(Float64);
    OSStatus err = AudioDeviceGetProperty(inDevice, 0, kAudioDeviceSectionGlobal, kAudioDevicePropertyNominalSampleRate, &outSize, &sampleRate);
    if (err != noErr) {
        printf("Cannot get current sample rate\n");
        printError(err);
        return -1;
    } else {
        return sampleRate;
    }
}

static CFStringRef GetDeviceName(AudioDeviceID id)
{
    UInt32 size = sizeof(CFStringRef);
    CFStringRef UIname;
    OSStatus err = AudioDeviceGetProperty(id, 0, false, kAudioDevicePropertyDeviceUID, &size, &UIname);
    return (err == noErr) ? UIname : NULL;
}

static bool CheckAvailableDeviceName(const char* device_name, AudioDeviceID* device_id, int len = -1)
{
    UInt32 size;
    Boolean isWritable;
    int i, deviceNum;
    OSStatus err;

    err = AudioHardwareGetPropertyInfo(kAudioHardwarePropertyDevices, &size, &isWritable);
    if (err != noErr) {
        return false;
    }

    deviceNum = size / sizeof(AudioDeviceID);
    AudioDeviceID devices[deviceNum];
 
    err = AudioHardwareGetProperty(kAudioHardwarePropertyDevices, &size, devices);
    if (err != noErr) {
        return false;
    }

    for (i = 0; i < deviceNum; i++) {
        char device_name_aux[256];
    
        size = 256;
        err = AudioDeviceGetProperty(devices[i], 0, false, kAudioDevicePropertyDeviceName, &size, device_name_aux);
        if (err != noErr) {
            return false;
        }
 
        if (strncmp(device_name_aux, device_name, (len == -1) ? strlen(device_name) : len) == 0) {
            *device_id = devices[i];
            return true;
        }
    }

    return false;
}

class TCoreAudioRenderer
{
    
    protected:
    
        AudioDeviceID fAggregateDeviceID;
        AudioObjectID fAggregatePluginID;    // Used for aggregate device
     
        int fDevNumInChans;
        int fDevNumOutChans;
        
        int fPhysicalInputs;
        int fPhysicalOutputs;
        
        float** fInChannel;
        float** fOutChannel;

        int fBufferSize;
        int fSampleRate;
    
        bool fIsInJackDevice;
        bool fIsOutJackDevice;
        
        dsp* fDSP;

        AudioBufferList* fInputData;
        AudioDeviceID fDeviceID;
        AudioUnit fAUHAL;
        bool fState;

        OSStatus GetDefaultDeviceAndSampleRate(int inChan, int outChan, int& sample_rate, AudioDeviceID* device)
        {
            
            UInt32 theSize = sizeof(UInt32);
            AudioDeviceID inDefault;
            AudioDeviceID outDefault;
            OSStatus res;
            
            if ((res = AudioHardwareGetProperty(kAudioHardwarePropertyDefaultInputDevice,
                                                &theSize, &inDefault)) != noErr) {
                return res;
            }
            
            if ((res = AudioHardwareGetProperty(kAudioHardwarePropertyDefaultOutputDevice,
                                                &theSize, &outDefault)) != noErr) {
                return res;
            }
            
            /*
            // TODO
            if (inDefault == 0) {
                printf("Error default input device is 0, will take 'Built-in'...\n");
                if (CheckAvailableDeviceName("Built-in Microphone", &inDefault) 
                    || CheckAvailableDeviceName("Built-in Line", &inDefault)) {
                    printf("GetDefaultInputDevice : output = %ld\n", inDefault);
                } else {
                    printf("Cannot find any input device to use...");
                    return -1;
                }
            }
            
            if (outDefault == 0) {
                printf("Error default ouput device is 0, will take 'Built-in'...\n");
                if (CheckAvailableDeviceName("Built-in Output", &outDefault)) {
                    printf("GetDefaultOutputDevice : output = %ld\n", outDefault);
                } else {
                    printf("Cannot find any output device to use...\n");
                    return -1;
                }
            }  
            */          
            
            //printf("GetDefaultDevice : input = %d output = %d\n", inDefault, outDefault);
            
            // Duplex mode
            if (inChan > 0 && outChan > 0) {
                // Get the device only if default input and output are the same
                if (inDefault == outDefault) {
                    *device = inDefault;
                    goto end;
                } else {
                    if (CreateAggregateDevice(inDefault, outDefault, sample_rate) != noErr) {
                        return kAudioHardwareBadDeviceError;
                    }
                    //printf("fAggregateDeviceID %d\n", fAggregateDeviceID);
                    *device = fAggregateDeviceID;
                    goto end;
                }
            } else if (inChan > 0) {
                *device = inDefault;
                goto end;
            } else if (outChan > 0) {
                *device = outDefault;
                goto end;
            } else {
                return kAudioHardwareBadDeviceError;
            }
            
        end:   
            
            if (sample_rate == -1) {
                // Possible take the current sample rate
                sample_rate = int(GetNominalSampleRate(*device));
            } else {
                // Otherwise force the one we want...
                SetupSampleRateAux(*device, sample_rate);
            }
            //printf("samplerate %d\n", sample_rate);
            fSampleRate = sample_rate;
            return noErr;
        }

        OSStatus CreateAggregateDevice(AudioDeviceID captureDeviceID, AudioDeviceID playbackDeviceID, int& sample_rate)
        {
            OSStatus err = noErr;
            AudioObjectID sub_device[32];
            UInt32 outSize = sizeof(sub_device);
            
            //printf("CreateAggregateDevice : input device %d\n", captureDeviceID);
            
            err = AudioDeviceGetProperty(captureDeviceID, 0, kAudioDeviceSectionGlobal, kAudioAggregateDevicePropertyActiveSubDeviceList, &outSize, sub_device);
            std::vector<AudioDeviceID> captureDeviceIDArray;
            
            if (err != noErr) {
                //printf("Input device does not have subdevices\n");
                captureDeviceIDArray.push_back(captureDeviceID);
            } else {
                int num_devices = outSize / sizeof(AudioObjectID);
                //printf("Input device has %d subdevices\n", num_devices);
                for (int i = 0; i < num_devices; i++) {
                    //printf("Input sub_device %d\n", sub_device[i]);
                    captureDeviceIDArray.push_back(sub_device[i]);
                }
            }
            
            outSize = sizeof(sub_device);
            err = AudioDeviceGetProperty(playbackDeviceID, 0, kAudioDeviceSectionGlobal, kAudioAggregateDevicePropertyActiveSubDeviceList, &outSize, sub_device);
            std::vector<AudioDeviceID> playbackDeviceIDArray;
            
            if (err != noErr) {
                //printf("Output device does not have subdevices\n");
                playbackDeviceIDArray.push_back(playbackDeviceID);
            } else {
                int num_devices = outSize / sizeof(AudioObjectID);
                //printf("Output device has %d subdevices\n", num_devices);
                for (int i = 0; i < num_devices; i++) {
                    //printf("Output sub_device %d\n", sub_device[i]);
                    playbackDeviceIDArray.push_back(sub_device[i]);
                }
            }
            
            return CreateAggregateDeviceAux(captureDeviceIDArray, playbackDeviceIDArray, sample_rate);
        }
        
        OSStatus CreateAggregateDeviceAux(std::vector<AudioDeviceID> captureDeviceID, std::vector<AudioDeviceID> playbackDeviceID, int& sample_rate)
        {
            OSStatus osErr = noErr;
            UInt32 outSize;
            Boolean outWritable;
            bool fClockDriftCompensate = true;
            
            // Prepare sub-devices for clock drift compensation
            // Workaround for bug in the HAL : until 10.6.2
            AudioObjectPropertyAddress theAddressOwned = { kAudioObjectPropertyOwnedObjects, kAudioObjectPropertyScopeGlobal, kAudioObjectPropertyElementMaster };
            AudioObjectPropertyAddress theAddressDrift = { kAudioSubDevicePropertyDriftCompensation, kAudioObjectPropertyScopeGlobal, kAudioObjectPropertyElementMaster };
            UInt32 theQualifierDataSize = sizeof(AudioObjectID);
            AudioClassID inClass = kAudioSubDeviceClassID;
            void* theQualifierData = &inClass;
            UInt32 subDevicesNum = 0;
            
            //---------------------------------------------------------------------------
            // Setup SR of both devices otherwise creating AD may fail...
            //---------------------------------------------------------------------------
            UInt32 keptclockdomain = 0;
            UInt32 clockdomain = 0;
            outSize = sizeof(UInt32);
            bool need_clock_drift_compensation = false;
            
            for (UInt32 i = 0; i < captureDeviceID.size(); i++) {
                if (SetupSampleRateAux(captureDeviceID[i], sample_rate) < 0) {
                    printf("TCoreAudioRenderer::CreateAggregateDeviceAux : cannot set SR of input device\n");
                } else  {
                    // Check clock domain
                    osErr = AudioDeviceGetProperty(captureDeviceID[i], 0, kAudioDeviceSectionGlobal, kAudioDevicePropertyClockDomain, &outSize, &clockdomain);
                    if (osErr != 0) {
                        printf("TCoreAudioRenderer::CreateAggregateDeviceAux : kAudioDevicePropertyClockDomain error\n");
                        printError(osErr);
                    } else {
                        keptclockdomain = (keptclockdomain == 0) ? clockdomain : keptclockdomain;
                        //printf("TCoreAudioRenderer::CreateAggregateDevice : input clockdomain = %d\n", clockdomain);
                        if (clockdomain != 0 && clockdomain != keptclockdomain) {
                            //printf("TCoreAudioRenderer::CreateAggregateDevice : devices do not share the same clock!! clock drift compensation would be needed...\n");
                            need_clock_drift_compensation = true;
                        }
                    }
                }
            }
            
            for (UInt32 i = 0; i < playbackDeviceID.size(); i++) {
                if (SetupSampleRateAux(playbackDeviceID[i], sample_rate) < 0) {
                    printf("TCoreAudioRenderer::CreateAggregateDeviceAux : cannot set SR of output device\n");
                } else {
                    // Check clock domain
                    osErr = AudioDeviceGetProperty(playbackDeviceID[i], 0, kAudioDeviceSectionGlobal, kAudioDevicePropertyClockDomain, &outSize, &clockdomain);
                    if (osErr != 0) {
                        printf("TCoreAudioRenderer::CreateAggregateDeviceAux : kAudioDevicePropertyClockDomain error\n");
                        printError(osErr);
                    } else {
                        keptclockdomain = (keptclockdomain == 0) ? clockdomain : keptclockdomain;
                        //printf("TCoreAudioRenderer::CreateAggregateDevice : output clockdomain = %d", clockdomain);
                        if (clockdomain != 0 && clockdomain != keptclockdomain) {
                            //printf("TCoreAudioRenderer::CreateAggregateDevice : devices do not share the same clock!! clock drift compensation would be needed...\n");
                            need_clock_drift_compensation = true;
                        }
                    }
                }
            }
            
            // If no valid clock domain was found, then assume we have to compensate...
            if (keptclockdomain == 0) {
                need_clock_drift_compensation = true;
            }
            
            //---------------------------------------------------------------------------
            // Start to create a new aggregate by getting the base audio hardware plugin
            //---------------------------------------------------------------------------
            
            char device_name[256];
            for (UInt32 i = 0; i < captureDeviceID.size(); i++) {
                GetDeviceNameFromID(captureDeviceID[i], device_name);
                //printf("Separated input = '%s' \n", device_name);
            }
            
            for (UInt32 i = 0; i < playbackDeviceID.size(); i++) {
                GetDeviceNameFromID(playbackDeviceID[i], device_name);
                //printf("Separated output = '%s' \n", device_name);
            }
            
            osErr = AudioHardwareGetPropertyInfo(kAudioHardwarePropertyPlugInForBundleID, &outSize, &outWritable);
            if (osErr != noErr) {
                printf("TCoreAudioRenderer::CreateAggregateDeviceAux : AudioHardwareGetPropertyInfo kAudioHardwarePropertyPlugInForBundleID error\n");
                printError(osErr);
                return osErr;
            }
            
            AudioValueTranslation pluginAVT;
            CFStringRef inBundleRef = CFSTR("com.apple.audio.CoreAudio");
            
            pluginAVT.mInputData = &inBundleRef;
            pluginAVT.mInputDataSize = sizeof(inBundleRef);
            pluginAVT.mOutputData = &fAggregatePluginID;
            pluginAVT.mOutputDataSize = sizeof(fAggregatePluginID);
            
            osErr = AudioHardwareGetProperty(kAudioHardwarePropertyPlugInForBundleID, &outSize, &pluginAVT);
            if (osErr != noErr) {
                printf("TCoreAudioRenderer::CreateAggregateDeviceAux : AudioHardwareGetProperty kAudioHardwarePropertyPlugInForBundleID error\n");
                printError(osErr);
                return osErr;
            }
            
            //-------------------------------------------------
            // Create a CFDictionary for our aggregate device
            //-------------------------------------------------
            
            CFMutableDictionaryRef aggDeviceDict = CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
            
            char buffer1[64];
            char buffer2[64];
            
            // generate "random" name
            struct timeval fTv1;
            struct timezone tz;
            gettimeofday(&fTv1, &tz);
            
            sprintf(buffer1, "com.grame.%d", fTv1.tv_sec + fTv1.tv_usec);
            sprintf(buffer2, "%d", fTv1.tv_sec + fTv1.tv_usec);
            
            CFStringRef AggregateDeviceNameRef = CFStringCreateWithCString(kCFAllocatorDefault, buffer1, CFStringGetSystemEncoding());
            CFStringRef AggregateDeviceUIDRef = CFStringCreateWithCString(kCFAllocatorDefault, buffer2, CFStringGetSystemEncoding());
            
            // add the name of the device to the dictionary
            CFDictionaryAddValue(aggDeviceDict, CFSTR(kAudioAggregateDeviceNameKey), AggregateDeviceNameRef);
            
            // add our choice of UID for the aggregate device to the dictionary
            CFDictionaryAddValue(aggDeviceDict, CFSTR(kAudioAggregateDeviceUIDKey), AggregateDeviceUIDRef);
            
            // add a "private aggregate key" to the dictionary
            int value = 1;
            CFNumberRef AggregateDeviceNumberRef = CFNumberCreate(NULL, kCFNumberIntType, &value);
            
            SInt32 system;
            Gestalt(gestaltSystemVersion, &system);
            
            //printf("TCoreAudioRenderer::CreateAggregateDevice : system version = %x limit = %x\n", system, 0x00001054);
            
            // Starting with 10.5.4 systems, the AD can be internal... (better)
            if (system < 0x00001054) {
                //printf("TCoreAudioRenderer::CreateAggregateDevice : public aggregate device....\n");
            } else {
                //printf("TCoreAudioRenderer::CreateAggregateDevice : private aggregate device....\n");
                CFDictionaryAddValue(aggDeviceDict, CFSTR(kAudioAggregateDeviceIsPrivateKey), AggregateDeviceNumberRef);
            }
            
            // Prepare sub-devices for clock drift compensation
            CFMutableArrayRef subDevicesArrayClock = NULL;
            
            /*
             if (fClockDriftCompensate) {
                 if (need_clock_drift_compensation) {
                     jack_info("Clock drift compensation activated...");
                     subDevicesArrayClock = CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
                     
                     for (UInt32 i = 0; i < captureDeviceID.size(); i++) {
                         CFStringRef UID = GetDeviceName(captureDeviceID[i]);
                         if (UID) {
                         CFMutableDictionaryRef subdeviceAggDeviceDict = CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
                         CFDictionaryAddValue(subdeviceAggDeviceDict, CFSTR(kAudioSubDeviceUIDKey), UID);
                         CFDictionaryAddValue(subdeviceAggDeviceDict, CFSTR(kAudioSubDeviceDriftCompensationKey), AggregateDeviceNumberRef);
                         //CFRelease(UID);
                         CFArrayAppendValue(subDevicesArrayClock, subdeviceAggDeviceDict);
                     }
                 }
                 
                 for (UInt32 i = 0; i < playbackDeviceID.size(); i++) {
                     CFStringRef UID = GetDeviceName(playbackDeviceID[i]);
                     if (UID) {
                         CFMutableDictionaryRef subdeviceAggDeviceDict = CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
                         CFDictionaryAddValue(subdeviceAggDeviceDict, CFSTR(kAudioSubDeviceUIDKey), UID);
                         CFDictionaryAddValue(subdeviceAggDeviceDict, CFSTR(kAudioSubDeviceDriftCompensationKey), AggregateDeviceNumberRef);
                         //CFRelease(UID);
                         CFArrayAppendValue(subDevicesArrayClock, subdeviceAggDeviceDict);
                     }
                 }
                     
                     // add sub-device clock array for the aggregate device to the dictionary
                     CFDictionaryAddValue(aggDeviceDict, CFSTR(kAudioAggregateDeviceSubDeviceListKey), subDevicesArrayClock);
                     } else {
                     jack_info("Clock drift compensation was asked but is not needed (devices use the same clock domain)");
                 }
            }
            */
            
            //-------------------------------------------------
            // Create a CFMutableArray for our sub-device list
            //-------------------------------------------------
            
            // we need to append the UID for each device to a CFMutableArray, so create one here
            CFMutableArrayRef subDevicesArray = CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
            
            std::vector<CFStringRef> captureDeviceUID;
            for (UInt32 i = 0; i < captureDeviceID.size(); i++) {
                CFStringRef ref = GetDeviceName(captureDeviceID[i]);
                if (ref == NULL) {
                    return -1;
                }
                captureDeviceUID.push_back(ref);
                // input sub-devices in this example, so append the sub-device's UID to the CFArray
                CFArrayAppendValue(subDevicesArray, ref);
            }
            
            std::vector<CFStringRef> playbackDeviceUID;
            for (UInt32 i = 0; i < playbackDeviceID.size(); i++) {
                CFStringRef ref = GetDeviceName(playbackDeviceID[i]);
                if (ref == NULL) {
                    return -1;
                }
                playbackDeviceUID.push_back(ref);
                // output sub-devices in this example, so append the sub-device's UID to the CFArray
                CFArrayAppendValue(subDevicesArray, ref);
            }
            
            //-----------------------------------------------------------------------
            // Feed the dictionary to the plugin, to create a blank aggregate device
            //-----------------------------------------------------------------------
            
            AudioObjectPropertyAddress pluginAOPA;
            pluginAOPA.mSelector = kAudioPlugInCreateAggregateDevice;
            pluginAOPA.mScope = kAudioObjectPropertyScopeGlobal;
            pluginAOPA.mElement = kAudioObjectPropertyElementMaster;
            UInt32 outDataSize;
            
            osErr = AudioObjectGetPropertyDataSize(fAggregatePluginID, &pluginAOPA, 0, NULL, &outDataSize);
            if (osErr != noErr) {
                printf("TCoreAudioRenderer::CreateAggregateDeviceAux : AudioObjectGetPropertyDataSize error\n");
                printError(osErr);
                goto error;
            }
            
            osErr = AudioObjectGetPropertyData(fAggregatePluginID, &pluginAOPA, sizeof(aggDeviceDict), &aggDeviceDict, &outDataSize, &fAggregateDeviceID);
            if (osErr != noErr) {
                printf("TCoreAudioRenderer::CreateAggregateDeviceAux : AudioObjectGetPropertyData error\n");
                printError(osErr);
                goto error;
            }
            
            // pause for a bit to make sure that everything completed correctly
            // this is to work around a bug in the HAL where a new aggregate device seems to disappear briefly after it is created
            CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.1, false);
            
            //-------------------------
            // Set the sub-device list
            //-------------------------
            
            pluginAOPA.mSelector = kAudioAggregateDevicePropertyFullSubDeviceList;
            pluginAOPA.mScope = kAudioObjectPropertyScopeGlobal;
            pluginAOPA.mElement = kAudioObjectPropertyElementMaster;
            outDataSize = sizeof(CFMutableArrayRef);
            osErr = AudioObjectSetPropertyData(fAggregateDeviceID, &pluginAOPA, 0, NULL, outDataSize, &subDevicesArray);
            if (osErr != noErr) {
                printf("TCoreAudioRenderer::CreateAggregateDeviceAux : AudioObjectSetPropertyData for sub-device list error\n");
                printError(osErr);
                goto error;
            }
            
            // pause again to give the changes time to take effect
            CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.1, false);
            
            //-----------------------
            // Set the master device
            //-----------------------
            
            // set the master device manually (this is the device which will act as the master clock for the aggregate device)
            // pass in the UID of the device you want to use
            pluginAOPA.mSelector = kAudioAggregateDevicePropertyMasterSubDevice;
            pluginAOPA.mScope = kAudioObjectPropertyScopeGlobal;
            pluginAOPA.mElement = kAudioObjectPropertyElementMaster;
            outDataSize = sizeof(CFStringRef);
            osErr = AudioObjectSetPropertyData(fAggregateDeviceID, &pluginAOPA, 0, NULL, outDataSize, &playbackDeviceUID[0]);  // First playback is master...
            if (osErr != noErr) {
                printf("TCoreAudioRenderer::CreateAggregateDeviceAux : AudioObjectSetPropertyData for master device error\n");
                printError(osErr);
                goto error;
            }
            
            // pause again to give the changes time to take effect
            CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.1, false);
            
            // Prepare sub-devices for clock drift compensation
            // Workaround for bug in the HAL : until 10.6.2
            
            if (fClockDriftCompensate) {
                if (need_clock_drift_compensation) {
                    //printf("Clock drift compensation activated...\n");
                    
                    // Get the property data size
                    osErr = AudioObjectGetPropertyDataSize(fAggregateDeviceID, &theAddressOwned, theQualifierDataSize, theQualifierData, &outSize);
                    if (osErr != noErr) {
                        printf("TCoreAudioRenderer::CreateAggregateDeviceAux kAudioObjectPropertyOwnedObjects error\n");
                        printError(osErr);
                    }
                    
                    //	Calculate the number of object IDs
                    subDevicesNum = outSize / sizeof(AudioObjectID);
                    //printf("TCoreAudioRenderer::CreateAggregateDevice clock drift compensation, number of sub-devices = %d\n", subDevicesNum);
                    AudioObjectID subDevices[subDevicesNum];
                    outSize = sizeof(subDevices);
                    
                    osErr = AudioObjectGetPropertyData(fAggregateDeviceID, &theAddressOwned, theQualifierDataSize, theQualifierData, &outSize, subDevices);
                    if (osErr != noErr) {
                        printf("TCoreAudioRenderer::CreateAggregateDeviceAux kAudioObjectPropertyOwnedObjects error\n");
                        printError(osErr);
                    }
                    
                    // Set kAudioSubDevicePropertyDriftCompensation property...
                    for (UInt32 index = 0; index < subDevicesNum; ++index) {
                        UInt32 theDriftCompensationValue = 1;
                        osErr = AudioObjectSetPropertyData(subDevices[index], &theAddressDrift, 0, NULL, sizeof(UInt32), &theDriftCompensationValue);
                        if (osErr != noErr) {
                            printf("TCoreAudioRenderer::CreateAggregateDeviceAux kAudioSubDevicePropertyDriftCompensation error\n");
                            printError(osErr);
                        }
                    }
                } else {
                    //printf("Clock drift compensation was asked but is not needed (devices use the same clock domain)\n");
                }
            }
            
            // pause again to give the changes time to take effect
            CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.1, false);
            
            //----------
            // Clean up
            //----------
            
            // release the private AD key
            CFRelease(AggregateDeviceNumberRef);
            
            // release the CF objects we have created - we don't need them any more
            CFRelease(aggDeviceDict);
            CFRelease(subDevicesArray);
            
            if (subDevicesArrayClock)
                CFRelease(subDevicesArrayClock);
            
            // release the device UID
            for (UInt32 i = 0; i < captureDeviceUID.size(); i++) {
                CFRelease(captureDeviceUID[i]);
            }
            
            for (UInt32 i = 0; i < playbackDeviceUID.size(); i++) {
                CFRelease(playbackDeviceUID[i]);
            }
            
            //printf("New aggregate device %d\n", fAggregateDeviceID);
            return noErr;
            
        error:
            DestroyAggregateDevice();
            return -1;
        }

        void DestroyAggregateDevice()
        {   
            if (fAggregateDeviceID > 0) {
                OSStatus osErr = noErr;
                AudioObjectPropertyAddress pluginAOPA;
                pluginAOPA.mSelector = kAudioPlugInDestroyAggregateDevice;
                pluginAOPA.mScope = kAudioObjectPropertyScopeGlobal;
                pluginAOPA.mElement = kAudioObjectPropertyElementMaster;
                UInt32 outDataSize;
                if (fAggregatePluginID > 0)   {
                    osErr = AudioObjectGetPropertyDataSize(fAggregatePluginID, &pluginAOPA, 0, NULL, &outDataSize);
                    if (osErr != noErr) {
                        printf("TCoreAudioRenderer::DestroyAggregateDevice : AudioObjectGetPropertyDataSize error\n");
                        printError(osErr);
                    }
                    osErr = AudioObjectGetPropertyData(fAggregatePluginID, &pluginAOPA, 0, NULL, &outDataSize, &fAggregateDeviceID);
                    if (osErr != noErr) {
                        printf("TCoreAudioRenderer::DestroyAggregateDevice : AudioObjectGetPropertyData error\n");
                        printError(osErr);
                    }
                }
            }
        }

        OSStatus GetDeviceNameFromID(AudioDeviceID id, char* name)
        {
            UInt32 size = 256;
            return AudioDeviceGetProperty(id, 0, false, kAudioDevicePropertyDeviceName, &size, name);
        }
        
        int SetupBufferSize(int buffer_size)
        {
            // Setting buffer size
            OSStatus err = noErr;
            UInt32 current_buffer_size = buffer_size;
            UInt32 outSize; 
            AudioValueRange buffer_size_range;
            
            outSize = sizeof(AudioValueRange);
            err = AudioDeviceGetProperty(fDeviceID, 0, true, kAudioDevicePropertyBufferFrameSizeRange, &outSize, &buffer_size_range);
            if (err != noErr) {
                printf("Cannot get buffer size range\n");
                printError(err);
                return -1;
            } else {
                //printf("SetupBufferSize : buffer size range min = %ld max = %ld\n", (int)buffer_size_range.mMinimum, (int)buffer_size_range.mMaximum);
            }
            
            outSize = sizeof(UInt32);
            err = AudioDeviceGetProperty(fDeviceID, 0, kAudioDeviceSectionGlobal, kAudioDevicePropertyBufferFrameSize, &outSize, &current_buffer_size);
            if (err != noErr) {
                printf("Cannot get buffer size\n");
                printError(err);
                return -1;
            } else {
                //printf("SetupBufferSize : current buffer size %ld\n", current_buffer_size);
            }

            // If needed, set new buffer size
            if (buffer_size != current_buffer_size && buffer_size >= (int)buffer_size_range.mMinimum && buffer_size <= (int)buffer_size_range.mMaximum) {
                current_buffer_size = buffer_size;

                // To get BS change notification
                err = AudioDeviceAddPropertyListener(fDeviceID, 0, true, kAudioDevicePropertyBufferFrameSize, BSNotificationCallback, this);
                if (err != noErr) {
                    printf("Error calling AudioDeviceAddPropertyListener with kAudioDevicePropertyBufferFrameSize\n");
                    printError(err);
                    return -1;
                }

                // Waiting for BS change notification
                int count = 0;
                fState = false;

                err = AudioDeviceSetProperty(fDeviceID, NULL, 0, kAudioDeviceSectionGlobal, kAudioDevicePropertyBufferFrameSize, outSize, &current_buffer_size);
                if (err != noErr) {
                    printf("SetupBufferSize : cannot set buffer size = %ld\n", current_buffer_size);
                    printError(err);
                    goto error;
                }

                while (!fState && count++ < WAIT_NOTIFICATION_COUNTER) {
                    usleep(100000);
                    //printf("SetupBufferSize : wait count = %d\n", count);
                }

                if (count >= WAIT_NOTIFICATION_COUNTER) {
                    printf("Did not get buffer size notification...\n");
                    goto error;
                }

                // Check new buffer size
                outSize = sizeof(UInt32);
                err = AudioDeviceGetProperty(fDeviceID, 0, kAudioDeviceSectionGlobal, kAudioDevicePropertyBufferFrameSize, &outSize, &current_buffer_size);
                if (err != noErr) {
                    printf("Cannot get current buffer size\n");
                    printError(err);
                } else {
                    //printf("SetupBufferSize : checked buffer size = %ld\n", current_buffer_size);
                }

                // Remove BS change notification
                AudioDeviceRemovePropertyListener(fDeviceID, 0, true, kAudioDevicePropertyBufferFrameSize, BSNotificationCallback);
            } else {
                //printf("Keep current buffer size = %ld\n", current_buffer_size);
            }
            
            fBufferSize = current_buffer_size;
            return 0;

        error:

            // Remove BS change notification
            AudioDeviceRemovePropertyListener(fDeviceID, 0, true, kAudioDevicePropertyBufferFrameSize, BSNotificationCallback);
            return -1;
        }
        
        static OSStatus BSNotificationCallback(AudioDeviceID inDevice,
                                                         UInt32 inChannel,
                                                         Boolean isInput,
                                                         AudioDevicePropertyID inPropertyID,
                                                         void* inClientData)
        {
            TCoreAudioRenderer* driver = (TCoreAudioRenderer*)inClientData;
        
            switch (inPropertyID) {

                case kAudioDevicePropertyBufferFrameSize: {
                    //printf("BSNotificationCallback kAudioDevicePropertyBufferFrameSize\n");
                    // Check new buffer size
                    UInt32 current_buffer_size;
                    UInt32 outSize = sizeof(UInt32);
                    OSStatus err = AudioDeviceGetProperty(inDevice, 0, kAudioDeviceSectionGlobal, kAudioDevicePropertyBufferFrameSize, &outSize, &current_buffer_size);
                    if (err != noErr) {
                        printf("Cannot get current buffer size\n");
                        printError(err);
                    } else {
                        //printf("BSNotificationCallback : checked current buffer size = %d\n", current_buffer_size);
                    }
                    driver->fState = true;
                    break;
                }
            }

            return noErr;
        }

        int SetupSampleRateAux(AudioDeviceID inDevice, int& sample_rate)
        {
            OSStatus err = noErr;
            UInt32 outSize = sizeof(Float64);
            Float64 sampleRate = GetNominalSampleRate(inDevice);
            
            if (sample_rate != -1 && sample_rate != (int)sampleRate) {
                sampleRate = (Float64)sample_rate;
                
                // To get SR change notification
                err = AudioDeviceAddPropertyListener(inDevice, 0, true, kAudioDevicePropertyNominalSampleRate, SRNotificationCallback, this);
                if (err != noErr) {
                    printf("Error calling AudioDeviceAddPropertyListener with kAudioDevicePropertyNominalSampleRate\n");
                    printError(err);
                    return -1;
                }
                err = AudioDeviceSetProperty(inDevice, NULL, 0, kAudioDeviceSectionGlobal, kAudioDevicePropertyNominalSampleRate, outSize, &sampleRate);
                if (err != noErr) {
                    printf("Cannot set sample rate = %d\n", sample_rate);
                    printError(err);
                    return -1;
                }
                
                // Waiting for SR change notification
                int count = 0;
                while (!fState && count++ < WAIT_NOTIFICATION_COUNTER) {
                    usleep(100000);
                    //printf("Wait count = %d\n", count);
                }
                
                // Check new sample rate
                outSize = sizeof(Float64);
                err = AudioDeviceGetProperty(inDevice, 0, kAudioDeviceSectionGlobal, kAudioDevicePropertyNominalSampleRate, &outSize, &sampleRate);
                if (err != noErr) {
                    printf("Cannot get current sample rate\n");
                    printError(err);
                } else {
                    //printf("Checked sample rate = %f\n", sampleRate);
                }
                
                // Remove SR change notification
                AudioDeviceRemovePropertyListener(inDevice, 0, true, kAudioDevicePropertyNominalSampleRate, SRNotificationCallback);
            }
            
            sample_rate = int(sampleRate);
            return 0;
        }   

        static OSStatus Render(void *inRefCon,
                           AudioUnitRenderActionFlags *ioActionFlags,
                           const AudioTimeStamp *inTimeStamp,
                           UInt32 inBusNumber,
                           UInt32 inNumberFrames,
                           AudioBufferList *ioData)
        {
            return static_cast<TCoreAudioRendererPtr>(inRefCon)->Render(ioActionFlags, inTimeStamp, inNumberFrames, ioData);
        }

        static OSStatus SRNotificationCallback(AudioDeviceID inDevice,
                                            UInt32 inChannel,
                                            Boolean	isInput,
                                            AudioDevicePropertyID inPropertyID,
                                               void* inClientData)
        {
            TCoreAudioRenderer* driver = (TCoreAudioRenderer*)inClientData;
            
            switch (inPropertyID) {
                    
                case kAudioDevicePropertyNominalSampleRate: {
                    //printf("SRNotificationCallback kAudioDevicePropertyNominalSampleRate\n");
                    driver->fState = true;
                    // Check new sample rate
                    Float64 sampleRate;
                    UInt32 outSize = sizeof(Float64);
                    OSStatus err = AudioDeviceGetProperty(inDevice, 0, kAudioDeviceSectionGlobal, kAudioDevicePropertyNominalSampleRate, &outSize, &sampleRate);
                    if (err != noErr) {
                        printf("Cannot get current sample rate\n");
                        printError(err);
                    } else {
                        //printf("SRNotificationCallback : checked sample rate = %f\n", sampleRate);
                    }
                    break;
                }
            }
            
            return noErr;
        }

        virtual OSStatus Render(AudioUnitRenderActionFlags *ioActionFlags,
                            const AudioTimeStamp *inTimeStamp,
                            UInt32 inNumberFrames,
                            AudioBufferList *ioData)
        {
            OSStatus err = noErr;
            if (fDevNumInChans > 0) {
                err = AudioUnitRender(fAUHAL, ioActionFlags, inTimeStamp, 1, inNumberFrames, fInputData);
            }
            if (err == noErr) {
                for (int i = 0; i < fDevNumInChans; i++) {
                    fInChannel[i] = (float*)fInputData->mBuffers[i].mData;
                }
                for (int i = 0; i < fDevNumOutChans; i++) {
                    fOutChannel[i] = (float*)ioData->mBuffers[i].mData;
                }
                fDSP->compute(double(AudioConvertHostTimeToNanos(inTimeStamp->mHostTime))/1000., inNumberFrames, fInChannel, fOutChannel);
            } else {
                printf("AudioUnitRender error... %x\n", fInputData);
                printError(err);
            }
            return err;
        }
        
    public:

        TCoreAudioRenderer()
            :fAggregateDeviceID(-1),fAggregatePluginID(-1),
            fDevNumInChans(0),fDevNumOutChans(0),
            fPhysicalInputs(0), fPhysicalOutputs(0),
            fInChannel(0),fOutChannel(0),
            fBufferSize(0),fSampleRate(0), 
            fDSP(0),fInputData(0),
            fDeviceID(0),fAUHAL(0),
            fState(false), 
            fIsInJackDevice(false),
            fIsOutJackDevice(false)
        {}

        virtual ~TCoreAudioRenderer()
        {}
        
        int GetBufferSize() {return fBufferSize;}
        int GetSampleRate() {return fSampleRate;}
        
        static OSStatus RestartProc(AudioObjectID objectID, UInt32 numberAddresses,
                                   const AudioObjectPropertyAddress inAddresses[],
                                   void *clientData) 
        {
            /*
            TCoreAudioRenderer* renderer = (TCoreAudioRenderer*)clientData;
            AudioDeviceID defaultDevice;
            UInt32 theSize = sizeof(UInt32);
            OSStatus res;
            char device_name[256];
            
            // Test if new device is "JackRouter"
            if (inAddresses[0].mSelector == kAudioHardwarePropertyDefaultInputDevice) {
                
                if ((res = AudioHardwareGetProperty(kAudioHardwarePropertyDefaultInputDevice,
                                                    &theSize, &defaultDevice)) == noErr) {
                    renderer->GetDeviceNameFromID(defaultDevice, device_name);
                    renderer->fIsInJackDevice = strcmp(device_name, "JackRouter") == 0;
                }
                
            } else  if (inAddresses[0].mSelector == kAudioHardwarePropertyDefaultOutputDevice) {
                
                if ((res = AudioHardwareGetProperty(kAudioHardwarePropertyDefaultOutputDevice,
                                                    &theSize, &defaultDevice)) == noErr) {
                    renderer->GetDeviceNameFromID(defaultDevice, device_name);
                    renderer->fIsOutJackDevice = strcmp(device_name, "JackRouter") == 0;
                }
                
            }
            
            // Switch only of input and output are "JackRouter"
            if (renderer->fIsInJackDevice && renderer->fIsOutJackDevice || !renderer->fIsInJackDevice && !renderer->fIsOutJackDevice) {
                renderer->Stop();
                renderer->Close();
                int sampleRate = -1; // Use the current sample rate
                int bufferSize = (renderer->fBufferSize > 0) ? renderer->fBufferSize : 512; // Use default if needed
                renderer->OpenDefault(renderer->fDSP, renderer->fDevNumInChans, renderer->fDevNumOutChans, bufferSize, sampleRate);
                renderer->Start();
            }
            */
            return 0;
        }
    
        int OpenDefault(dsp* DSP, int inChan, int outChan, int bufferSize, int& sampleRate)
        {
            fDevNumInChans = 0;
            fDevNumOutChans = 0;
            fInChannel = 0;
            fOutChannel = 0;
            fBufferSize = 0;
            fSampleRate = 0;
            fDSP = 0;
            fInputData = 0;
            fDeviceID = 0; 
            fAUHAL = 0;
            fState = false;
            return OpenDefault(inChan, outChan, bufferSize, sampleRate);
        }
    
        int OpenDefault(int inChan, int outChan, int buffer_size, int& sample_rate)
        {
            OSStatus err;
            UInt32 outSize;
            UInt32 enableIO;
            Boolean isWritable;
            AudioStreamBasicDescription srcFormat, dstFormat, sampleRate;
            
            fDevNumInChans = inChan;
            fDevNumOutChans = outChan;
            
            fInChannel = new float*[fDevNumInChans];
            fOutChannel = new float*[fDevNumOutChans];
            
            //printf("OpenDefault inChan = %ld outChan = %ld bufferSize = %ld sample_rate = %ld\n", inChan, outChan, bufferSize, sample_rate);
            
            SInt32 major;
            SInt32 minor;
            Gestalt(gestaltSystemVersionMajor, &major);
            Gestalt(gestaltSystemVersionMinor, &minor);
            
            // Starting with 10.6 systems, the HAL notification thread is created internally
            if (major == 10 && minor >= 6) {
                CFRunLoopRef theRunLoop = NULL;
                AudioObjectPropertyAddress theAddress = { kAudioHardwarePropertyRunLoop, kAudioObjectPropertyScopeGlobal, kAudioObjectPropertyElementMaster };
                OSStatus osErr = AudioObjectSetPropertyData (kAudioObjectSystemObject, &theAddress, 0, NULL, sizeof(CFRunLoopRef), &theRunLoop);
                if (osErr != noErr) {
                    printf("TCoreAudioRenderer::Open kAudioHardwarePropertyRunLoop error\n");
                    printError(osErr);
                }
            }
             
            if (GetDefaultDeviceAndSampleRate(inChan, outChan, sample_rate, &fDeviceID) != noErr) {
                printf("Cannot open default device\n");
                return OPEN_ERR;
            }
             
            // Setting buffer size
            if (SetupBufferSize(buffer_size) < 0) {
                return OPEN_ERR;
            }
            
            // fBufferSize now has the real value, either 'bufferSize' (if could be changed) or driver current one
            
            // AUHAL
        
        #ifdef MAC_OS_X_VERSION_10_5
            ComponentDescription cd = {kAudioUnitType_Output, kAudioUnitSubType_HALOutput, kAudioUnitManufacturer_Apple, 0, 0};
            Component HALOutput = FindNextComponent(NULL, &cd);
            err = OpenAComponent(HALOutput, &fAUHAL);
            if (err != noErr) {
                printf("Error calling OpenAComponent\n");
                printError(err);
                goto error;
            }
        #else 
            AudioComponentDescription cd = {kAudioUnitType_Output, kAudioUnitSubType_HALOutput, kAudioUnitManufacturer_Apple, 0, 0};
            AudioComponent HALOutput = AudioComponentFindNext(NULL, &cd);
            err = AudioComponentInstanceNew(HALOutput, &fAUHAL);
            if (err != noErr) {
                printf("Error calling AudioComponentInstanceNew\n");
                printError(err);
                goto error;
            }
        #endif
            
            err = AudioUnitInitialize(fAUHAL);
            if (err != noErr) {
                printf("Cannot initialize AUHAL unit\n");
                printError(err);
                goto error;
            }
            
            if (inChan > 0) {
                enableIO = 1;
                //printf("OpenAUHAL : setup AUHAL input on\n");
            } else {
                enableIO = 0;
                //printf("OpenAUHAL : setup AUHAL input off\n");
            }
            
            err = AudioUnitSetProperty(fAUHAL, kAudioOutputUnitProperty_EnableIO, kAudioUnitScope_Input, 1, &enableIO, sizeof(enableIO));
            if (err != noErr) {
                printf("Error calling AudioUnitSetProperty - kAudioOutputUnitProperty_EnableIO, kAudioUnitScope_Input\n");
                printError(err);
                goto error;
            }
                
            if (outChan > 0) {
                enableIO = 1;
                //printf("OpenAUHAL : setup AUHAL output on\n");
            } else {
                enableIO = 0;
                //printf("OpenAUHAL : setup AUHAL output off\n");
            }
            
            err = AudioUnitSetProperty(fAUHAL, kAudioOutputUnitProperty_EnableIO, kAudioUnitScope_Output, 0, &enableIO, sizeof(enableIO));
            if (err != noErr) {
                printf("Error calling AudioUnitSetProperty - kAudioOutputUnitProperty_EnableIO, kAudioUnitScope_Output\n");
                printError(err);
                goto error;
            }
            
            AudioDeviceID currAudioDeviceID;
            outSize = sizeof(AudioDeviceID);
            err = AudioUnitGetProperty(fAUHAL, kAudioOutputUnitProperty_CurrentDevice, kAudioUnitScope_Global, 0, &currAudioDeviceID, &outSize);
            if (err != noErr) {
                printf("Error calling AudioUnitGetProperty - kAudioOutputUnitProperty_CurrentDevice\n");
                printError(err);
                goto error;
            } else {
                //printf("AudioUnitGetPropertyCurrentDevice = %d\n", currAudioDeviceID);
            }
        
            // Setup up choosen device, in both input and output cases
            err = AudioUnitSetProperty(fAUHAL, kAudioOutputUnitProperty_CurrentDevice, kAudioUnitScope_Global, 0, &fDeviceID, sizeof(AudioDeviceID));
            if (err != noErr) {
                printf("Error calling AudioUnitSetProperty - kAudioOutputUnitProperty_CurrentDevice\n");
                printError(err);
                goto error;
            }
            
            if (inChan > 0) {
                err = AudioUnitSetProperty(fAUHAL, kAudioUnitProperty_MaximumFramesPerSlice, kAudioUnitScope_Global, 1, (UInt32*)&fBufferSize, sizeof(UInt32));
                if (err != noErr) {
                    printf("Error calling AudioUnitSetProperty - kAudioUnitProperty_MaximumFramesPerSlice\n");
                    printError(err);
                    goto error;
                }
            }
            
            if (outChan > 0) {
                err = AudioUnitSetProperty(fAUHAL, kAudioUnitProperty_MaximumFramesPerSlice, kAudioUnitScope_Global, 0, (UInt32*)&fBufferSize, sizeof(UInt32));
                if (err != noErr) {
                    printf("Error calling AudioUnitSetProperty - kAudioUnitProperty_MaximumFramesPerSlice\n");
                    printError(err);
                    goto error;
                }
            }
            
            err = AudioUnitGetPropertyInfo(fAUHAL, kAudioOutputUnitProperty_ChannelMap, kAudioUnitScope_Input, 1, &outSize, &isWritable);
            if (err != noErr) {
                //printf("Error calling AudioUnitGetPropertyInfo - kAudioOutputUnitProperty_ChannelMap 1\n");
                //printError(err);
            } else {
                fPhysicalInputs = (err == noErr) ? outSize / sizeof(SInt32) : 0;
                //printf("fPhysicalInputs = %ld\n", fPhysicalInputs);
            }
                    
            err = AudioUnitGetPropertyInfo(fAUHAL, kAudioOutputUnitProperty_ChannelMap, kAudioUnitScope_Output, 0, &outSize, &isWritable);
            if (err != noErr) {
                //printf("Error calling AudioUnitGetPropertyInfo - kAudioOutputUnitProperty_ChannelMap 0\n");
                //printError(err);
            } else {
                fPhysicalOutputs = (err == noErr) ? outSize / sizeof(SInt32) : 0;
                //printf("fPhysicalOutputs = %ld\n", fPhysicalOutputs);
            }
            
            /*
             Just ignore this case : seems to work without any further change...
             
             if (outChan > fPhysicalOutputs) {
                printf("This device hasn't required output channels\n");
                goto error;
             }
             if (inChan > fPhysicalInputs) {
                printf("This device hasn't required input channels\n");
                goto error;
             }
             */
            
            if (inChan < fPhysicalInputs) {
                SInt32 chanArr[fPhysicalInputs];
                for (int i = 0; i < fPhysicalInputs; i++) {
                    chanArr[i] = -1;
                }
                for (int i = 0; i < inChan; i++) {
                    chanArr[i] = i;
                }
                AudioUnitSetProperty(fAUHAL, kAudioOutputUnitProperty_ChannelMap , kAudioUnitScope_Input, 1, chanArr, sizeof(SInt32) * fPhysicalInputs);
                if (err != noErr) {
                    printf("Error calling AudioUnitSetProperty - kAudioOutputUnitProperty_ChannelMap 1\n");
                    printError(err);
                }
            }
            
            if (outChan < fPhysicalOutputs) {
                SInt32 chanArr[fPhysicalOutputs];
                for (int i = 0;	i < fPhysicalOutputs; i++) {
                    chanArr[i] = -1;
                }
                for (int i = 0; i < outChan; i++) {
                    chanArr[i] = i;
                }
                err = AudioUnitSetProperty(fAUHAL, kAudioOutputUnitProperty_ChannelMap, kAudioUnitScope_Output, 0, chanArr, sizeof(SInt32) * fPhysicalOutputs);
                if (err != noErr) {
                    printf("Error calling AudioUnitSetProperty - kAudioOutputUnitProperty_ChannelMap 0\n");
                    printError(err);
                }
            }
            
            if (inChan > 0) {
                outSize = sizeof(AudioStreamBasicDescription);
                err = AudioUnitGetProperty(fAUHAL, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Output, 1, &srcFormat, &outSize);
                if (err != noErr) {
                    printf("Error calling AudioUnitGetProperty - kAudioUnitProperty_StreamFormat kAudioUnitScope_Output\n");
                    printError(err);
                }
                //PrintStreamDesc(&srcFormat);
                
                srcFormat.mSampleRate = sample_rate;
                srcFormat.mFormatID = kAudioFormatLinearPCM;
                srcFormat.mFormatFlags = kAudioFormatFlagsNativeFloatPacked | kLinearPCMFormatFlagIsNonInterleaved;
                srcFormat.mBytesPerPacket = sizeof(float);
                srcFormat.mFramesPerPacket = 1;
                srcFormat.mBytesPerFrame = sizeof(float);
                srcFormat.mChannelsPerFrame = inChan;
                srcFormat.mBitsPerChannel = 32;
                
                //PrintStreamDesc(&srcFormat);
                
                err = AudioUnitSetProperty(fAUHAL, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Output, 1, &srcFormat, sizeof(AudioStreamBasicDescription));
                if (err != noErr) {
                    printf("Error calling AudioUnitSetProperty - kAudioUnitProperty_StreamFormat kAudioUnitScope_Output\n");
                    printError(err);
                }
            }
            
            if (outChan > 0) {
                outSize = sizeof(AudioStreamBasicDescription);
                err = AudioUnitGetProperty(fAUHAL, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input, 0, &dstFormat, &outSize);
                if (err != noErr) {
                    printf("Error calling AudioUnitGetProperty - kAudioUnitProperty_StreamFormat kAudioUnitScope_Output\n");
                    printError(err);
                }
                //PrintStreamDesc(&dstFormat);
                
                dstFormat.mSampleRate = sample_rate;
                dstFormat.mFormatID = kAudioFormatLinearPCM;
                dstFormat.mFormatFlags = kAudioFormatFlagsNativeFloatPacked | kLinearPCMFormatFlagIsNonInterleaved;
                dstFormat.mBytesPerPacket = sizeof(float);
                dstFormat.mFramesPerPacket = 1;
                dstFormat.mBytesPerFrame = sizeof(float);
                dstFormat.mChannelsPerFrame = outChan;
                dstFormat.mBitsPerChannel = 32;
                
                //PrintStreamDesc(&dstFormat);
                
                err = AudioUnitSetProperty(fAUHAL, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input, 0, &dstFormat, sizeof(AudioStreamBasicDescription));
                if (err != noErr) {
                    printf("Error calling AudioUnitSetProperty - kAudioUnitProperty_StreamFormat kAudioUnitScope_Output\n");
                    printError(err);
                }
            }
            
            if (inChan > 0 && outChan == 0) {
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
            
            if (inChan > 0) {
                fInputData = (AudioBufferList*)malloc(sizeof(UInt32) + inChan * sizeof(AudioBuffer));
                assert(fInputData);
                fInputData->mNumberBuffers = inChan;
                
                // Prepare buffers
                for (int i = 0; i < inChan; i++) {
                    fInputData->mBuffers[i].mNumberChannels = 1;
                    fInputData->mBuffers[i].mData = malloc(fBufferSize * sizeof(float));
                    assert(fInputData->mBuffers[i].mData),
                    fInputData->mBuffers[i].mDataByteSize = fBufferSize * sizeof(float);
                }
            }
            
            AudioObjectPropertyAddress property_address;
            property_address.mScope = kAudioObjectPropertyScopeGlobal;
            property_address.mElement = kAudioObjectPropertyElementMaster;
            
            property_address.mSelector = kAudioHardwarePropertyDefaultInputDevice;
            if (AudioObjectAddPropertyListener(kAudioObjectSystemObject, &property_address, RestartProc, this)) {
                printf("AudioObjectAddPropertyListener() failed\n");
                return OPEN_ERR;
            } else {
                //printf("AudioObjectAddPropertyListener() OK\n");
            }
            
            property_address.mSelector = kAudioHardwarePropertyDefaultOutputDevice;
            if (AudioObjectAddPropertyListener(kAudioObjectSystemObject, &property_address, RestartProc, this)) {
                printf("AudioObjectAddPropertyListener() failed\n");
                return OPEN_ERR;
            } else {
                //printf("AudioObjectAddPropertyListener() OK\n");
            }
             
            return NO_ERR;
            
        error:
            AudioUnitUninitialize(fAUHAL);
            CloseComponent(fAUHAL);
            fAUHAL = 0;
            return OPEN_ERR;
        }
        
        int Close()
        {
            if (!fAUHAL) {
                return CLOSE_ERR;
            }
            
            for (int i = 0; i < fDevNumInChans; i++) {
                free(fInputData->mBuffers[i].mData);
            }
            if (fInputData) {
                free(fInputData);
            }
            AudioUnitUninitialize(fAUHAL);
            CloseComponent(fAUHAL);
            fAUHAL = NULL;
            
            DestroyAggregateDevice();
            
            delete[] fInChannel;
            delete[] fOutChannel;
            
            AudioObjectPropertyAddress property_address;
            property_address.mScope = kAudioObjectPropertyScopeGlobal;
            property_address.mElement = kAudioObjectPropertyElementMaster;
            
            property_address.mSelector = kAudioHardwarePropertyDefaultInputDevice;
            AudioObjectRemovePropertyListener(kAudioObjectSystemObject, &property_address, RestartProc, this);
            
            property_address.mSelector = kAudioHardwarePropertyDefaultOutputDevice;
            AudioObjectRemovePropertyListener(kAudioObjectSystemObject, &property_address, RestartProc, this);
            
            return NO_ERR;
        }

        int Start()
        {
            if (!fAUHAL) {
                return OPEN_ERR;
            }
            
            OSStatus err = AudioOutputUnitStart(fAUHAL);
            
            if (err != noErr) {
                printf("Error while opening device : device open error \n");
                return OPEN_ERR;
            } else {
                return NO_ERR;
            }
        }
        
        int Stop()
        {
            if (!fAUHAL) {
                return OPEN_ERR;
            }
            
            OSStatus err = AudioOutputUnitStop(fAUHAL);
            
            if (err != noErr) {
                printf("Error while closing device : device close error \n");
                return OPEN_ERR;
            } else {
                return NO_ERR;
            }
        }
    
        void set_dsp(dsp* DSP)
        {
            fDSP = DSP;
        }
        
        int GetNumInputs() { return fPhysicalInputs; }
        int GetNumOutputs() { return fPhysicalOutputs; }

};

/******************************************************************************
*******************************************************************************

							CORE AUDIO INTERFACE

*******************************************************************************
*******************************************************************************/
class coreaudio : public audio {

    protected:
        
        TCoreAudioRenderer fAudioDevice;
        int fSampleRate, fBufferSize;

    public:
      
        coreaudio(int srate, int bsize) : fSampleRate(srate), fBufferSize(bsize) {}
            coreaudio(int bsize) : fSampleRate(-1), fBufferSize(bsize) {}
        virtual ~coreaudio() { fAudioDevice.Close(); }

        virtual bool init(const char* /*name*/, dsp* DSP) 
        {
            if (fAudioDevice.OpenDefault(DSP, DSP->getNumInputs(), DSP->getNumOutputs(), fBufferSize, fSampleRate) < 0) {
                printf("Cannot open CoreAudio device\n");
                return false;
            }
            fAudioDevice.set_dsp(DSP);
            // If -1 was given, fSampleRate will be changed by OpenDefault
            DSP->init(fSampleRate);
            return true;
        }

        virtual bool start() 
        {
            if (fAudioDevice.Start() < 0) {
                printf("Cannot start CoreAudio device\n");
                return false;
            }
            return true;
        }

        virtual void stop() 
        {
            fAudioDevice.Stop();
        }
        
        virtual int get_buffer_size() { return fAudioDevice.GetBufferSize(); }
        virtual int get_sample_rate() { return fAudioDevice.GetSampleRate(); }
        
        virtual int get_num_inputs() { return fAudioDevice.GetNumInputs(); }
        virtual int get_num_outputs() { return fAudioDevice.GetNumOutputs(); }

};

#endif

/********************END ARCHITECTURE SECTION (part 2/2)****************/


