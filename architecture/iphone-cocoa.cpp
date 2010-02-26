/* link with  */
#include <math.h>
/* link with  */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <sys/types.h>
#include <assert.h>
#include <pthread.h> 
#include <sys/wait.h>

#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <stack>
#include <list>
#include <map>
#include <libgen.h>

#include <AudioToolbox/AudioConverter.h>
#include <AudioToolbox/AudioServices.h>
#include <AudioUnit/AudioUnit.h>

using namespace std;

// On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
// flags to avoid costly denormals
#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS 
#endif

//#define BENCHMARKMODE

struct Meta : map<const char*, const char*>
{
    void declare (const char* key, const char* value) { (*this)[key]=value; }
};
	
#define max(x,y) (((x)>(y)) ? (x) : (y))
#define min(x,y) (((x)<(y)) ? (x) : (y))

inline int	lsr(int x, int n)	{ return int(((unsigned int)x) >> n); }
inline int 	int2pow2(int x)     { int r=0; while ((1<<r)<x) r++; return r; }

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

<<includeIntrinsic>>

/******************************************************************************
*******************************************************************************

								USER INTERFACE

*******************************************************************************
*******************************************************************************/

#include "CocoaUI.h"

/******************************************************************************
*******************************************************************************

			    FAUST DSP

*******************************************************************************
*******************************************************************************/


//----------------------------------------------------------------
//  abstract definition of a signal processor
//----------------------------------------------------------------
			
class dsp {
 protected:
	int fSamplingFreq;
 public:
	dsp() {}
	virtual ~dsp() {}

	virtual int getNumInputs() 						= 0;
	virtual int getNumOutputs() 					= 0;
	virtual void buildUserInterface(UI* interface) 	= 0;
	virtual void init(int samplingRate) 			= 0;
 	virtual void compute(int len, float** inputs, float** outputs) 	= 0;
};
		
//----------------------------------------------------------------------------
//  FAUST generated signal processor
//----------------------------------------------------------------------------
		
<<includeclass>>
				
mydsp	DSP;

/******************************************************************************
*******************************************************************************

							COREAUDIO INTERFACE

*******************************************************************************
*******************************************************************************/

#define MAX_CHANNELS 256
#define OPEN_ERR -1
#define NO_ERR 0

class TiPhoneCoreAudioRenderer
{

    private:

		AudioUnit fAUHAL;
        
        int	fDevNumInChans;
        int	fDevNumOutChans;
        
        int fHWNumInChans;
        int fHWNumOutChans;
     
        float* fInChannel[MAX_CHANNELS];
        float* fOutChannel[MAX_CHANNELS];
	
		static OSStatus Render(void *inRefCon,
                               AudioUnitRenderActionFlags *ioActionFlags,
                               const AudioTimeStamp *inTimeStamp,
                               UInt32 inBusNumber,
                               UInt32 inNumberFrames,
                               AudioBufferList *ioData);
                               
        static void InterruptionListener(void *inClientData, UInt32 inInterruption);

    public:

        TiPhoneCoreAudioRenderer(int input, int output)
            :fDevNumInChans(input), fDevNumOutChans(output)
        {
            for (int i = 0; i < fDevNumInChans; i++) {
                fInChannel[i] = new float[8192];
            }
    
            for (int i = 0; i < fDevNumOutChans; i++) {
                fOutChannel[i] = new float[8192];
            }
        }
        virtual ~TiPhoneCoreAudioRenderer()
        {
            for (int i = 0; i < fDevNumInChans; i++) {
                delete[] fInChannel[i];
            }
    
            for (int i = 0; i < fDevNumOutChans; i++) {
                delete[] fOutChannel[i]; 
            }
        }

        int Open(int bufferSize, int sampleRate);
        int Close();

        int Start();
        int Stop();

};

typedef TiPhoneCoreAudioRenderer * TiPhoneCoreAudioRendererPtr;

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

OSStatus TiPhoneCoreAudioRenderer::Render(void *inRefCon,
                                         AudioUnitRenderActionFlags *ioActionFlags,
                                         const AudioTimeStamp *inTimeStamp,
                                         UInt32,
                                         UInt32 inNumberFrames,
                                         AudioBufferList *ioData)
{
    TiPhoneCoreAudioRendererPtr renderer = (TiPhoneCoreAudioRendererPtr)inRefCon;
    AudioUnitRender(renderer->fAUHAL, ioActionFlags, inTimeStamp, 1, inNumberFrames, ioData);
    
    float coef = float(LONG_MAX);
    float inv_coef = 1.f/float(LONG_MAX);
    
    if (renderer->fHWNumInChans == 1) {
        // Mono ==> stereo
        for (int chan = 0; chan < renderer->fDevNumInChans; chan++) {
            for (int frame = 0; frame < inNumberFrames; frame++) {
                renderer->fInChannel[chan][frame] = float(((long*)ioData->mBuffers[0].mData)[frame]) * inv_coef;
            }
        }
    } else {
        for (int chan = 0; chan < renderer->fDevNumInChans; chan++) {
            for (int frame = 0; frame < inNumberFrames; frame++) {
                renderer->fInChannel[chan][frame] = float(((long*)ioData->mBuffers[chan].mData)[frame]) * inv_coef;
            }
        }
    }
    
    DSP.compute((int)inNumberFrames, renderer->fInChannel, renderer->fOutChannel);
    
    for (int chan = 0; chan < renderer->fDevNumOutChans; chan++) {
        for (int frame = 0; frame < inNumberFrames; frame++) {
           ((long*)ioData->mBuffers[chan].mData)[frame] = long(renderer->fOutChannel[chan][frame] * coef); 
        }
    }
    
 	return 0;
}

void TiPhoneCoreAudioRenderer::InterruptionListener(void *inClientData, UInt32 inInterruption)
{
	TiPhoneCoreAudioRenderer *obj = (TiPhoneCoreAudioRenderer*)inClientData;
	printf("Session interrupted! --- %s ---", inInterruption == kAudioSessionBeginInterruption ? "Begin Interruption" : "End Interruption");
		
	if (inInterruption == kAudioSessionEndInterruption) {
		// make sure we are again the active session
		AudioSessionSetActive(true);
		AudioOutputUnitStart(obj->fAUHAL);
	}
	
	if (inInterruption == kAudioSessionBeginInterruption) {
		AudioOutputUnitStop(obj->fAUHAL);
    }
}

int TiPhoneCoreAudioRenderer::Open(int bufferSize, int samplerate)
{
    OSStatus err1;
    UInt32 outSize;
    UInt32 enableIO;
	AudioStreamBasicDescription srcFormat, dstFormat;
    
    printf("OpenDefault fDevNumInChans = %ld fDevNumOutChans = %ld bufferSize = %ld samplerate = %ld\n", fDevNumInChans, fDevNumOutChans, bufferSize, samplerate);
	  
    // Initialize and configure the audio session
    err1 = AudioSessionInitialize(NULL, NULL, InterruptionListener, this);
    if (err1 != noErr) {
        printf("Couldn't initialize audio session\n");
        printError(err1);
        return OPEN_ERR;
    }
    
    err1 = AudioSessionSetActive(true);
    if (err1 != noErr) {
        printf("Couldn't set audio session active\n");
        printError(err1);
        return OPEN_ERR;
    }
  			
    UInt32 audioCategory = kAudioSessionCategory_PlayAndRecord;
	err1 = AudioSessionSetProperty(kAudioSessionProperty_AudioCategory, sizeof(audioCategory), &audioCategory);
    if (err1 != noErr) {
        printf("Couldn't set audio category\n");
        printError(err1);
        return OPEN_ERR;
    }
    
   	//err1 = AudioSessionAddPropertyListener(kAudioSessionProperty_AudioRouteChange, propListener, self), "couldn't set property listener");
    
    Float64 hwSampleRate;
    outSize = sizeof(hwSampleRate);
	err1 = AudioSessionGetProperty(kAudioSessionProperty_CurrentHardwareSampleRate, &outSize, &hwSampleRate);
    if (err1 != noErr) {
        printf("Couldn't get hw sample rate\n");
        printError(err1);
        return OPEN_ERR;
    } else {
         printf("Get hw sample rate %f\n", hwSampleRate);
    }
    
    Float32 hwBufferSize;
    outSize = sizeof(hwBufferSize);
	err1 = AudioSessionGetProperty(kAudioSessionProperty_CurrentHardwareIOBufferDuration, &outSize, &hwBufferSize);
    if (err1 != noErr) {
        printf("Couldn't get hw buffer duration\n");
        printError(err1);
        return OPEN_ERR;
    } else {
         printf("Get hw buffer duration %f\n", hwBufferSize);
    }

    outSize = sizeof(fHWNumInChans);
	err1 = AudioSessionGetProperty(kAudioSessionProperty_CurrentHardwareInputNumberChannels, &outSize, &fHWNumInChans);
    if (err1 != noErr) {
        printf("Couldn't get hw input channels\n");
        printError(err1);
        return OPEN_ERR;
    } else {
        printf("Get hw input channels %d\n", fHWNumInChans);
    }

    outSize = sizeof(fHWNumOutChans);
	err1 = AudioSessionGetProperty(kAudioSessionProperty_CurrentHardwareOutputNumberChannels, &outSize, &fHWNumOutChans);
    if (err1 != noErr) {
        printf("Couldn't get hw output channels\n");
        printError(err1);
        return OPEN_ERR;
    } else {
        printf("Get hw output channels %d\n", fHWNumOutChans);
    }
			
    Float32 preferredBufferSize = float(bufferSize) / float(samplerate);
    printf("preferredBufferSize %f \n", preferredBufferSize);
    
	err1 = AudioSessionSetProperty(kAudioSessionProperty_PreferredHardwareIOBufferDuration, sizeof(preferredBufferSize), &preferredBufferSize);
    if (err1 != noErr) {
        printf("Couldn't set i/o buffer duration\n");
        printError(err1);
        return OPEN_ERR;
    }
  	
    Float64 preferredSamplerate = float(samplerate);
	err1 = AudioSessionSetProperty(kAudioSessionProperty_PreferredHardwareSampleRate, sizeof(preferredSamplerate), &preferredSamplerate);
    if (err1 != noErr) {
        printf("Couldn't set i/o sample rate\n");
        printError(err1);
        return OPEN_ERR;
    }
  	
    // AUHAL
    AudioComponentDescription cd = {kAudioUnitType_Output, kAudioUnitSubType_RemoteIO, kAudioUnitManufacturer_Apple, 0, 0};
    AudioComponent HALOutput = AudioComponentFindNext(NULL, &cd);

    err1 = AudioComponentInstanceNew(HALOutput, &fAUHAL);
    if (err1 != noErr) {
		printf("Error calling OpenAComponent\n");
        printError(err1);
        goto error;
	}

    enableIO = 1;
    err1 = AudioUnitSetProperty(fAUHAL, kAudioOutputUnitProperty_EnableIO, kAudioUnitScope_Output, 0, &enableIO, sizeof(enableIO));
    if (err1 != noErr) {
        printf("Error calling AudioUnitSetProperty - kAudioOutputUnitProperty_EnableIO, kAudioUnitScope_Output\n");
        printError(err1);
        goto error;
    }
    
    enableIO = 1;
    err1 = AudioUnitSetProperty(fAUHAL, kAudioOutputUnitProperty_EnableIO, kAudioUnitScope_Input, 1, &enableIO, sizeof(enableIO));
    if (err1 != noErr) {
        printf("Error calling AudioUnitSetProperty - kAudioOutputUnitProperty_EnableIO, kAudioUnitScope_Input\n");
        printError(err1);
        goto error;
    }
    
    UInt32 maxFPS;
    outSize = sizeof(maxFPS);
    err1 = AudioUnitGetProperty(fAUHAL, kAudioUnitProperty_MaximumFramesPerSlice, kAudioUnitScope_Global, 0, &maxFPS, &outSize);
    if (err1 != noErr) {
        printf("Couldn't get kAudioUnitProperty_MaximumFramesPerSlice\n");
        printError(err1);
        goto error;
    } else {
        printf("Get kAudioUnitProperty_MaximumFramesPerSlice %d\n", maxFPS);
    }
   
    err1 = AudioUnitSetProperty(fAUHAL, kAudioUnitProperty_MaximumFramesPerSlice, kAudioUnitScope_Global, 1, (UInt32*)&bufferSize, sizeof(UInt32));
    if (err1 != noErr) {
        printf("Error calling AudioUnitSetProperty - kAudioUnitProperty_MaximumFramesPerSlice\n");
        printError(err1);
        goto error;
    }

    err1 = AudioUnitSetProperty(fAUHAL, kAudioUnitProperty_MaximumFramesPerSlice, kAudioUnitScope_Global, 0, (UInt32*)&bufferSize, sizeof(UInt32));
    if (err1 != noErr) {
        printf("Error calling AudioUnitSetProperty - kAudioUnitProperty_MaximumFramesPerSlice\n");
        printError(err1);
        goto error;
    }

    err1 = AudioUnitInitialize(fAUHAL);
    if (err1 != noErr) {
		printf("Cannot initialize AUHAL unit\n");
		printError(err1);
        goto error;
	}

    // Setting format
  	
    if (fDevNumInChans > 0) {
        outSize = sizeof(AudioStreamBasicDescription);
        err1 = AudioUnitGetProperty(fAUHAL, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Output, 1, &srcFormat, &outSize);
        if (err1 != noErr) {
            printf("Error calling AudioUnitGetProperty - kAudioUnitProperty_StreamFormat kAudioUnitScope_Output\n");
            printError(err1);
        }
        PrintStreamDesc(&srcFormat);
        
        srcFormat.mFormatID = kAudioFormatLinearPCM;
        srcFormat.mFormatFlags = kAudioFormatFlagsCanonical | kLinearPCMFormatFlagIsNonInterleaved;
        srcFormat.mBytesPerPacket = sizeof(AudioUnitSampleType);
        srcFormat.mFramesPerPacket = 1;
        srcFormat.mBytesPerFrame = sizeof(AudioUnitSampleType);
        srcFormat.mChannelsPerFrame = fDevNumInChans;
        srcFormat.mBitsPerChannel = 32;
        
        PrintStreamDesc(&srcFormat);
        
        err1 = AudioUnitSetProperty(fAUHAL, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Output, 1, &srcFormat, sizeof(AudioStreamBasicDescription));
        if (err1 != noErr) {
            printf("Error calling AudioUnitSetProperty - kAudioUnitProperty_StreamFormat kAudioUnitScope_Output\n");
            printError(err1);
        }    
    }
	
    if (fDevNumOutChans > 0) {
        outSize = sizeof(AudioStreamBasicDescription);
        err1 = AudioUnitGetProperty(fAUHAL, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input, 0, &dstFormat, &outSize);
        if (err1 != noErr) {
            printf("Error calling AudioUnitGetProperty - kAudioUnitProperty_StreamFormat kAudioUnitScope_Input\n");
            printError(err1);
        }
        PrintStreamDesc(&dstFormat);
        
        dstFormat.mFormatID = kAudioFormatLinearPCM;
        dstFormat.mFormatFlags = kAudioFormatFlagsCanonical | kLinearPCMFormatFlagIsNonInterleaved;
        dstFormat.mBytesPerPacket = sizeof(AudioUnitSampleType);
        dstFormat.mFramesPerPacket = 1;
        dstFormat.mBytesPerFrame = sizeof(AudioUnitSampleType);
        dstFormat.mChannelsPerFrame = fDevNumOutChans;
        dstFormat.mBitsPerChannel = 32;
        
        PrintStreamDesc(&dstFormat);

        err1 = AudioUnitSetProperty(fAUHAL, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input, 0, &dstFormat, sizeof(AudioStreamBasicDescription));
        if (err1 != noErr) {
            printf("Error calling AudioUnitSetProperty - kAudioUnitProperty_StreamFormat kAudioUnitScope_Input\n");
            printError(err1);
        }
    }

    if (fDevNumInChans > 0 && fDevNumOutChans == 0) {
        AURenderCallbackStruct output;
        output.inputProc = Render;
        output.inputProcRefCon = this;
        err1 = AudioUnitSetProperty(fAUHAL, kAudioOutputUnitProperty_SetInputCallback, kAudioUnitScope_Global, 0, &output, sizeof(output));
        if (err1 != noErr) {
            printf("Error calling AudioUnitSetProperty - kAudioUnitProperty_SetRenderCallback 1\n");
            printError(err1);
            goto error;
        }
    } else {
        AURenderCallbackStruct output;
        output.inputProc = Render;
        output.inputProcRefCon = this;
        err1 = AudioUnitSetProperty(fAUHAL, kAudioUnitProperty_SetRenderCallback, kAudioUnitScope_Input, 0, &output, sizeof(output));
        if (err1 != noErr) {
            printf("Error calling AudioUnitSetProperty - kAudioUnitProperty_SetRenderCallback 0\n");
            printError(err1);
            goto error;
        }
    }

    return NO_ERR;

error:
    AudioUnitUninitialize(fAUHAL);
    AudioComponentInstanceDispose(fAUHAL);
    return OPEN_ERR;
}

int TiPhoneCoreAudioRenderer::Close()
{
 	AudioUnitUninitialize(fAUHAL);
    AudioComponentInstanceDispose(fAUHAL);
    return NO_ERR;
}

int TiPhoneCoreAudioRenderer::Start()
{
    AudioSessionSetActive(true);
	OSStatus err = AudioOutputUnitStart(fAUHAL);
  
    if (err != noErr) {
        printf("Error while opening device : device open error \n");
        return OPEN_ERR;
    } else {
        return NO_ERR;
	}
}

int TiPhoneCoreAudioRenderer::Stop()
{
    OSStatus err = AudioOutputUnitStop(fAUHAL);

    if (err != noErr) {
        printf("Error while closing device : device close error \n");
        return OPEN_ERR;
    } else {
        return NO_ERR;
	}
}
