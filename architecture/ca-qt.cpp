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
#include <CoreAudio/CoreAudio.h>
#include <AudioUnit/AudioUnit.h>

#include "faustqt.h"


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

//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }

// g++ -O3 -lm -ljack `gtk-config --cflags --libs` ex2.cpp
 
	

#define max(x,y) (((x)>(y)) ? (x) : (y))
#define min(x,y) (((x)<(y)) ? (x) : (y))


// abs is now predefined
//template<typename T> T abs (T a)			{ return (a<T(0)) ? -a : a; }


inline int		lsr (int x, int n)			{ return int(((unsigned int)x) >> n); }

inline int 		int2pow2 (int x)	{ int r=0; while ((1<<r)<x) r++; return r; }



/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }
//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((size_t)(calloc((nmemb*size)+15,sizeof(char)))+15 & ~15); }


<<includeIntrinsic>>


/******************************************************************************
*******************************************************************************

								FAUST DSP

*******************************************************************************
*******************************************************************************/





//----------------------------------------------------------------
//  définition du processeur de signal
//----------------------------------------------------------------
			
class dsp {
 protected:
	int fSamplingFreq;
 public:
	dsp() {}
	virtual ~dsp() {}
	
	virtual int getNumInputs() 										= 0;
	virtual int getNumOutputs() 									= 0;
	virtual void buildUserInterface(UI* interface) 					= 0;
	virtual void init(int samplingRate) 							= 0;
 	virtual void compute(int len, float** inputs, float** outputs) 	= 0;
};
		

//----------------------------------------------------------------------------
// 	FAUST generated code
//----------------------------------------------------------------------------
		
<<includeclass>>
		
				
mydsp	DSP;


/******************************************************************************
*******************************************************************************

							COREAUDIO INTERFACE

*******************************************************************************
*******************************************************************************/


//----------------------------------------------------------------------------
// 	number of physical input and output channels of the CA device
//----------------------------------------------------------------------------

int	gDevNumInChans;
int	gDevNumOutChans;

//----------------------------------------------------------------------------
// tables of noninterleaved input and output channels for FAUST
//----------------------------------------------------------------------------

float* 	gInChannel[256];
float* 	gOutChannel[256];

#define OPEN_ERR -1
#define NO_ERR 0

class TCoreAudioRenderer
{

    private:

		AudioBufferList* fInputData;
		AudioDeviceID fDeviceID;
		AudioUnit fAUHAL;
		
		OSStatus GetDefaultDevice(int inChan, int outChan, AudioDeviceID* id);
  
		static	OSStatus Render(void *inRefCon,
                               AudioUnitRenderActionFlags *ioActionFlags,
                               const AudioTimeStamp *inTimeStamp,
                               UInt32 inBusNumber,
                               UInt32 inNumberFrames,
                               AudioBufferList *ioData);

    public:

        TCoreAudioRenderer()
        {}
        virtual ~TCoreAudioRenderer()
        {}

        long OpenDefault(long inChan, long outChan, long bufferSize, long sampleRate);
        long Close();

        long Start();
        long Stop();

};

typedef TCoreAudioRenderer * TCoreAudioRendererPtr;

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
#ifdef DEBUG
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
            printf("error code : unknown\n");
            break;
    }
#endif
}

OSStatus TCoreAudioRenderer::Render(void *inRefCon,
                                     AudioUnitRenderActionFlags *ioActionFlags,
                                     const AudioTimeStamp *inTimeStamp,
                                     UInt32 inBusNumber,
                                     UInt32 inNumberFrames,
                                     AudioBufferList *ioData)
{
    TCoreAudioRendererPtr renderer = (TCoreAudioRendererPtr)inRefCon;
    AudioUnitRender(renderer->fAUHAL, ioActionFlags, inTimeStamp, 1, inNumberFrames, renderer->fInputData);
    for (int i = 0; i < gDevNumInChans; i++) {
        gInChannel[i] = (float*)renderer->fInputData->mBuffers[i].mData;
    }
    for (int i = 0; i < gDevNumOutChans; i++) {
        gOutChannel[i] = (float*)ioData->mBuffers[i].mData;
    }
    DSP.compute((int)inNumberFrames, gInChannel, gOutChannel);
	return 0;
}

OSStatus TCoreAudioRenderer::GetDefaultDevice(int inChan, int outChan, AudioDeviceID* id)
{
    UInt32 theSize = sizeof(UInt32);
    AudioDeviceID inDefault;
    AudioDeviceID outDefault;
	OSStatus res;

    if ((res = AudioHardwareGetProperty(kAudioHardwarePropertyDefaultInputDevice,
                                        &theSize, &inDefault)) != noErr)
        return res;

    if ((res = AudioHardwareGetProperty(kAudioHardwarePropertyDefaultOutputDevice,
                                        &theSize, &outDefault)) != noErr)
        return res;
	
	// Duplex mode
	if (inChan > 0 && outChan > 0) {
		// Get the device only if default input and output are the same
		if (inDefault == outDefault) {
			*id = inDefault;
			return noErr;
		} else {
			printf("GetDefaultDevice : error input = %ld and output = %ld are not the same\n", inDefault, outDefault);
			return kAudioHardwareBadDeviceError;
		}
	} else if (inChan > 0) {
		*id = inDefault;
		return noErr;
	} else if (outChan > 0) {
		*id = outDefault;
		return noErr;
	} else {
		return kAudioHardwareBadDeviceError;
	}
	
	return noErr;
}

long TCoreAudioRenderer::OpenDefault(long inChan, long outChan, long bufferSize, long samplerate)
{
	OSStatus err = noErr;
    ComponentResult err1;
    UInt32 outSize;
    UInt32 enableIO;
	Boolean isWritable;
	AudioStreamBasicDescription srcFormat, dstFormat, sampleRate;
    long in_nChannels, out_nChannels;
	
	if (GetDefaultDevice(inChan, outChan, &fDeviceID) != noErr) {
		printf("Cannot open default device\n");
		return OPEN_ERR;
	}
	
	// Setting buffer size
    outSize = sizeof(UInt32);
    err = AudioDeviceSetProperty(fDeviceID, NULL, 0, false, kAudioDevicePropertyBufferFrameSize, outSize, &bufferSize);
    if (err != noErr) {
        printf("Cannot set buffer size %ld\n", bufferSize);
        printError(err);
        return OPEN_ERR;
    }

    // Setting sample rate
    outSize = sizeof(AudioStreamBasicDescription);
    err = AudioDeviceGetProperty(fDeviceID, 0, false, kAudioDevicePropertyStreamFormat, &outSize, &sampleRate);
    if (err != noErr) {
        printf("Cannot get current sample rate\n");
        printError(err);
        return OPEN_ERR;
    }

    if (samplerate != (unsigned long)sampleRate.mSampleRate) {
        sampleRate.mSampleRate = (Float64)(samplerate);
        err = AudioDeviceSetProperty(fDeviceID, NULL, 0, false, kAudioDevicePropertyStreamFormat, outSize, &sampleRate);
        if (err != noErr) {
            printf("Cannot set sample rate = %ld\n", samplerate);
            printError(err);
            return OPEN_ERR;
        }
    }

    // AUHAL
    ComponentDescription cd = {kAudioUnitType_Output, kAudioUnitSubType_HALOutput, kAudioUnitManufacturer_Apple, 0, 0};
    Component HALOutput = FindNextComponent(NULL, &cd);

    err1 = OpenAComponent(HALOutput, &fAUHAL);
    if (err1 != noErr) {
		printf("Error calling OpenAComponent");
        printError(err1);
        goto error;
	}

    err1 = AudioUnitInitialize(fAUHAL);
    if (err1 != noErr) {
		printf("Cannot initialize AUHAL unit");
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
    
    err1 = AudioUnitSetProperty(fAUHAL, kAudioOutputUnitProperty_CurrentDevice, kAudioUnitScope_Global, 0, &fDeviceID, sizeof(AudioDeviceID));
    if (err1 != noErr) {
        printf("Error calling AudioUnitSetProperty - kAudioOutputUnitProperty_CurrentDevice\n");
        printError(err1);
        goto error;
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

    err1 = AudioUnitGetPropertyInfo(fAUHAL, kAudioOutputUnitProperty_ChannelMap, kAudioUnitScope_Input, 1, &outSize, &isWritable);
    if (err1 != noErr) {
        printf("Error calling AudioUnitSetProperty - kAudioOutputUnitProperty_ChannelMap-INFO 1\n");
        printError(err1);
    }

    in_nChannels = (err1 == noErr) ? outSize / sizeof(SInt32) : 0;

    err1 = AudioUnitGetPropertyInfo(fAUHAL, kAudioOutputUnitProperty_ChannelMap, kAudioUnitScope_Output, 0, &outSize, &isWritable);
    if (err1 != noErr) {
        printf("Error calling AudioUnitSetProperty - kAudioOutputUnitProperty_ChannelMap-INFO 0\n");
        printError(err1);
    }

    out_nChannels = (err1 == noErr) ? outSize / sizeof(SInt32) : 0;

    if (outChan > out_nChannels) {
        printf("This device hasn't required output channels\n");
        goto error;
    }
    if (inChan > in_nChannels) {
        printf("This device hasn't required input channels\n");
        goto error;
    }

    if (outChan < out_nChannels) {
        SInt32 chanArr[out_nChannels];
        for (int i = 0;	i < out_nChannels; i++) {
            chanArr[i] = -1;
        }
        for (int i = 0; i < outChan; i++) {
            chanArr[i] = i;
        }
        err1 = AudioUnitSetProperty(fAUHAL, kAudioOutputUnitProperty_ChannelMap, kAudioUnitScope_Output, 0, chanArr, sizeof(SInt32) * out_nChannels);
        if (err1 != noErr) {
            printf("Error calling AudioUnitSetProperty - kAudioOutputUnitProperty_ChannelMap 0\n");
            printError(err1);
        }
    }

    if (inChan < in_nChannels) {
        SInt32 chanArr[in_nChannels];
        for (int i = 0; i < in_nChannels; i++) {
            chanArr[i] = -1;
        }
        for (int i = 0; i < inChan; i++) {
            chanArr[i] = i;
        }
        AudioUnitSetProperty(fAUHAL, kAudioOutputUnitProperty_ChannelMap , kAudioUnitScope_Input, 1, chanArr, sizeof(SInt32) * in_nChannels);
        if (err1 != noErr) {
            printf("Error calling AudioUnitSetProperty - kAudioOutputUnitProperty_ChannelMap 1\n");
            printError(err1);
        }
    }
	
	outSize = sizeof(AudioStreamBasicDescription);
	err1 = AudioUnitGetProperty(fAUHAL, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input, 0, &srcFormat, &outSize);
    if (err1 != noErr) {
        printf("Error calling AudioUnitGetProperty - kAudioUnitProperty_StreamFormat kAudioUnitScope_Input\n");
        printError(err1);
    }
	PrintStreamDesc(&srcFormat);
	
	outSize = sizeof(AudioStreamBasicDescription);
	err1 = AudioUnitGetProperty(fAUHAL, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Output, 1, &dstFormat, &outSize);
    if (err1 != noErr) {
        printf("Error calling AudioUnitGetProperty - kAudioUnitProperty_StreamFormat kAudioUnitScope_Output\n");
        printError(err1);
    }
	PrintStreamDesc(&dstFormat);
	
    /*
	srcFormat.mSampleRate = samplerate;
    srcFormat.mFormatID = kAudioFormatLinearPCM;
	srcFormat.mBitsPerChannel = 32;
	srcFormat.mFormatFlags = kAudioFormatFlagsNativeFloatPacked;
	srcFormat.mChannelsPerFrame = outChan;
	srcFormat.mFramesPerPacket = 1;
	srcFormat.mBytesPerFrame = srcFormat.mBitsPerChannel * srcFormat.mChannelsPerFrame / 8;
    srcFormat.mBytesPerPacket = srcFormat.mBytesPerFrame * srcFormat.mFramesPerPacket;
    */
    
    srcFormat.mSampleRate = samplerate;
    srcFormat.mFormatID = kAudioFormatLinearPCM;
    srcFormat.mFormatFlags = kAudioFormatFlagsNativeFloatPacked | kLinearPCMFormatFlagIsNonInterleaved;
    srcFormat.mBytesPerPacket = sizeof(float);
    srcFormat.mFramesPerPacket = 1;
    srcFormat.mBytesPerFrame = sizeof(float);
    srcFormat.mChannelsPerFrame = outChan;
    srcFormat.mBitsPerChannel = 32;
		
	PrintStreamDesc(&srcFormat);

    err1 = AudioUnitSetProperty(fAUHAL, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input, 0, &srcFormat, sizeof(AudioStreamBasicDescription));
    if (err1 != noErr) {
        printf("Error calling AudioUnitSetProperty - kAudioUnitProperty_StreamFormat kAudioUnitScope_Input\n");
        printError(err1);
    }
	
    /*
    dstFormat.mSampleRate = samplerate;
	dstFormat.mFormatID = kAudioFormatLinearPCM;
	dstFormat.mBitsPerChannel = 32;
	dstFormat.mFormatFlags = kAudioFormatFlagsNativeFloatPacked;
	dstFormat.mChannelsPerFrame = inChan;
	dstFormat.mFramesPerPacket = 1;
	dstFormat.mBytesPerFrame = dstFormat.mBitsPerChannel * dstFormat.mChannelsPerFrame / 8;
    dstFormat.mBytesPerPacket = dstFormat.mBytesPerFrame * dstFormat.mFramesPerPacket;
    */
    
    dstFormat.mSampleRate = samplerate;
    dstFormat.mFormatID = kAudioFormatLinearPCM;
    dstFormat.mFormatFlags = kAudioFormatFlagsNativeFloatPacked | kLinearPCMFormatFlagIsNonInterleaved;
    dstFormat.mBytesPerPacket = sizeof(float);
    dstFormat.mFramesPerPacket = 1;
    dstFormat.mBytesPerFrame = sizeof(float);
    dstFormat.mChannelsPerFrame = inChan;
    dstFormat.mBitsPerChannel = 32;
	
	PrintStreamDesc(&dstFormat);

    err1 = AudioUnitSetProperty(fAUHAL, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Output, 1, &dstFormat, sizeof(AudioStreamBasicDescription));
    if (err1 != noErr) {
        printf("Error calling AudioUnitSetProperty - kAudioUnitProperty_StreamFormat kAudioUnitScope_Output\n");
        printError(err1);
    }

    if (inChan > 0 && outChan == 0) {
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

    fInputData = (AudioBufferList*)malloc(sizeof(UInt32) + inChan * sizeof(AudioBuffer));
    if (fInputData == 0) {
		printf("Cannot allocate memory for input buffers\n");
        goto error;
	}
    fInputData->mNumberBuffers = inChan;

    // Prepare buffers
    for (int i = 0; i < inChan; i++) {
        fInputData->mBuffers[i].mNumberChannels = 1;
        fInputData->mBuffers[i].mData = malloc(bufferSize * sizeof(float));
        fInputData->mBuffers[i].mDataByteSize = bufferSize * sizeof(float);
    }
 	
    return NO_ERR;

error:
    AudioUnitUninitialize(fAUHAL);
    CloseComponent(fAUHAL);
    return OPEN_ERR;
}

long TCoreAudioRenderer::Close()
{
    for (int i = 0; i < gDevNumInChans; i++) {
        free(fInputData->mBuffers[i].mData);
    }
	free(fInputData);
	AudioUnitUninitialize(fAUHAL);
    CloseComponent(fAUHAL);
    return NO_ERR;
}

long TCoreAudioRenderer::Start()
{
	OSStatus err = AudioOutputUnitStart(fAUHAL);
  
    if (err != noErr) {
        printf("Error while opening device : device open error \n");
        return OPEN_ERR;
    } else {
        return NO_ERR;
	}
}

long TCoreAudioRenderer::Stop()
{
    OSStatus err = AudioOutputUnitStop(fAUHAL);

    if (err != noErr) {
        printf("Error while closing device : device close error \n");
        return OPEN_ERR;
    } else {
        return NO_ERR;
	}
}

/******************************************************************************
*******************************************************************************

								MAIN PLAY THREAD

*******************************************************************************
*******************************************************************************/

long lopt (char *argv[], const char *name, long def) 
{
	int	i;
	for (i=0; argv[i]; i++) if (!strcmp(argv[i], name)) return atoi(argv[i+1]);
	return def;
}
	
//-------------------------------------------------------------------------
// 									MAIN
//-------------------------------------------------------------------------
list<UI*> UI::fGuiList;

int main( int argc, char *argv[] )
{
	UI* interface = new QTGUI(argc, argv);
	char rcfilename[256];
    TCoreAudioRenderer audio_device;
		
    long srate = (long)lopt(argv, "--frequency", 44100);
    int	fpb = lopt(argv, "--buffer", 128);
 		
	DSP.init(long(srate));
	DSP.buildUserInterface(interface);
	
    const char* home = getenv("HOME");
    if (home == 0) home = ".";
    snprintf(rcfilename, 256, "%s/.%src", home, basename(argv[0]));
    
    gDevNumInChans = min(2, DSP.getNumInputs());
    gDevNumOutChans = min(2, DSP.getNumOutputs());
    
    interface->recallState(rcfilename);
    if (audio_device.OpenDefault(gDevNumInChans, gDevNumOutChans, fpb, srate) < 0) {
        printf("Cannot open CoreAudio device\n");
        return 0;
    }
    
    if (audio_device.Start() < 0) {
        printf("Cannot start CoreAudio device\n");
        return 0;
    }
    
    printf("inchan = %d, outchan = %d, freq = %ld\n", gDevNumInChans, gDevNumOutChans, srate);

	interface->run();
    audio_device.Stop();
    audio_device.Close();
    interface->saveState(rcfilename);
  	return 0;
}

