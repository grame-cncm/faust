#ifndef __UNITYAUDIOPLUGININTERFACE__
#define __UNITYAUDIOPLUGININTERFACE__

#define UNITY_AUDIO_PLUGIN_API_VERSION 0x010300

#ifndef UNITY_PREFIX_CONFIGURE_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64)
#   define UNITY_WIN 1
#elif defined(__MACH__) || defined(__APPLE__)
#   define UNITY_OSX 1
#elif defined(__ANDROID__)
#   define UNITY_ANDROID 1
#elif defined(__linux__)
#   define UNITY_LINUX 1
#elif defined(__PS3__)
#   define UNITY_PS3 1
#elif defined(__SPU__)
#   define UNITY_SPU 1
#endif

#if defined(_AMD64_) || defined(__LP64__)
#   define UNITY_64 1
#   define UNITY_32 0
#else
#   define UNITY_64 0
#   define UNITY_32 1
#endif

#ifndef SInt16_defined
#   define SInt16_defined
typedef signed short SInt16;
#endif

#ifndef UInt16_defined
#   define UInt16_defined
typedef unsigned short UInt16;
#endif

#ifndef UInt8_defined
#   define UInt8_defined
typedef unsigned char UInt8;
#endif

#ifndef SInt8_defined
#   define SInt8_defined
typedef signed char SInt8;
#endif

#if UNITY_64
#   if UNITY_LINUX
#       ifndef SInt32_defined
#           define SInt32_defined
typedef signed int SInt32;
#       endif
#       ifndef UInt32_defined
#           define UInt32_defined
typedef unsigned int UInt32;
#       endif
#       ifndef UInt64_defined
#           define UInt64_defined
typedef unsigned long UInt64;
#       endif
#       ifndef SInt64_defined
#           define SInt64_defined
typedef signed long SInt64;
#       endif
#   elif UNITY_OSX
#       ifndef SInt32_defined
#           define SInt32_defined
typedef signed int SInt32;
#       endif
#       ifndef UInt32_defined
#           define UInt32_defined
typedef unsigned int UInt32;
#       endif
#       ifndef UInt64_defined
#           define UInt64_defined
typedef unsigned long long UInt64;
#       endif
#       ifndef SInt64_defined
#           define SInt64_defined
typedef signed long long SInt64;
#       endif
#   elif UNITY_WIN
#       ifndef SInt32_defined
#           define SInt32_defined
typedef signed long SInt32;
#       endif
#       ifndef UInt32_defined
#           define UInt32_defined
typedef unsigned long UInt32;
#       endif
#       ifndef UInt64_defined
#           define UInt64_defined
typedef unsigned long long UInt64;
#       endif
#       ifndef SInt64_defined
#           define SInt64_defined
typedef signed long long SInt64;
#       endif
    #endif
#else
#       ifndef SInt32_defined
#           define SInt32_defined
typedef signed int SInt32;
#       endif
#       ifndef UInt32_defined
#           define UInt32_defined
typedef unsigned int UInt32;
#       endif
#       ifndef UInt64_defined
#           define UInt64_defined
typedef unsigned long long UInt64;
#       endif
#       ifndef SInt64_defined
#           define SInt64_defined
typedef signed long long SInt64;
#       endif
#endif

#endif

#if UNITY_WIN
    #define UNITY_AUDIODSP_CALLBACK __stdcall
#elif UNITY_OSX
    #define UNITY_AUDIODSP_CALLBACK
#else
    #define UNITY_AUDIODSP_CALLBACK
#endif

// Attribute to make function be exported from a plugin
#if UNITY_WIN
    #define UNITY_AUDIODSP_EXPORT_API __declspec(dllexport)
#else
    #define UNITY_AUDIODSP_EXPORT_API
#endif

#if defined(__CYGWIN32__)
    #define UNITY_AUDIODSP_CALLBACK __stdcall
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64)
    #define UNITY_AUDIODSP_CALLBACK __stdcall
#elif defined(__MACH__) || defined(__ANDROID__) || defined(__linux__) || defined(__QNX__)
    #define UNITY_AUDIODSP_CALLBACK
#else
    #define UNITY_AUDIODSP_CALLBACK
#endif

#define UNITY_AUDIODSP_RESULT int

#if !UNITY_SPU // asserts require _exit() to be defined
#include <assert.h>
#endif

enum
{
    UNITY_AUDIODSP_OK = 0,
    UNITY_AUDIODSP_ERR_UNSUPPORTED = 1,
};

struct UnityAudioEffectState;

typedef UNITY_AUDIODSP_RESULT (UNITY_AUDIODSP_CALLBACK * UnityAudioEffect_CreateCallback)(UnityAudioEffectState* state);
typedef UNITY_AUDIODSP_RESULT (UNITY_AUDIODSP_CALLBACK * UnityAudioEffect_ReleaseCallback)(UnityAudioEffectState* state);
typedef UNITY_AUDIODSP_RESULT (UNITY_AUDIODSP_CALLBACK * UnityAudioEffect_ResetCallback)(UnityAudioEffectState* state);
typedef UNITY_AUDIODSP_RESULT (UNITY_AUDIODSP_CALLBACK * UnityAudioEffect_ProcessCallback)(UnityAudioEffectState* state, float* inbuffer, float* outbuffer, unsigned int length, int inchannels, int outchannels);
typedef UNITY_AUDIODSP_RESULT (UNITY_AUDIODSP_CALLBACK * UnityAudioEffect_SetPositionCallback)(UnityAudioEffectState* state, unsigned int pos);
typedef UNITY_AUDIODSP_RESULT (UNITY_AUDIODSP_CALLBACK * UnityAudioEffect_SetFloatParameterCallback)(UnityAudioEffectState* state, int index, float value);
typedef UNITY_AUDIODSP_RESULT (UNITY_AUDIODSP_CALLBACK * UnityAudioEffect_GetFloatParameterCallback)(UnityAudioEffectState* state, int index, float* value, char *valuestr);
typedef UNITY_AUDIODSP_RESULT (UNITY_AUDIODSP_CALLBACK * UnityAudioEffect_GetFloatBufferCallback)(UnityAudioEffectState* state, const char* name, float* buffer, int numsamples);

enum UnityAudioEffectDefinitionFlags
{
    UnityAudioEffectDefinitionFlags_IsSideChainTarget  = 1 << 0,   // Does this effect need a side chain buffer and can it be targeted by a Send?
    UnityAudioEffectDefinitionFlags_IsSpatializer      = 2 << 0,   // Should this plugin be inserted at sources and take over panning?
};

enum UnityAudioEffectStateFlags
{
    UnityAudioEffectStateFlags_IsPlaying               = 1 << 0,   // Set when engine is in play mode. Also true while paused.
    UnityAudioEffectStateFlags_IsPaused                = 1 << 1,   // Set when engine is paused mode.
    UnityAudioEffectStateFlags_IsMuted                 = 1 << 2,   // Set when effect is being muted (only available in the editor)
    UnityAudioEffectStateFlags_IsSideChainTarget       = 1 << 3,   // Does this effect need a side chain buffer and can it be targeted by a Send?
};

// This callback can be used to override the way distance attenuation is performed on AudioSources.
// distanceIn is the distance between the source and the listener and attenuationOut is the output volume.
// attenuationIn is the volume-curve based attenuation that would have been applied by Unity if this callback were not set.
// A typical attenuation curve may look like this: *attenuationOut = 1.0f / max(1.0f, distanceIn);
// The callback may also be used to apply a secondary gain on top of the one through attenuationIn by Unity's AudioSource curve.
typedef UNITY_AUDIODSP_RESULT (UNITY_AUDIODSP_CALLBACK * UnityAudioEffect_DistanceAttenuationCallback)(UnityAudioEffectState* state, float distanceIn, float attenuationIn, float* attenuationOut);

struct UnityAudioSpatializerData
{
    float listenermatrix[16];                                                 // Matrix that transforms sourcepos into the local space of the listener
    float sourcematrix[16];                                                   // Transform matrix of audio source
    float spatialblend;                                                       // Distance-controlled spatial blend
    float reverbzonemix;                                                      // Reverb zone mix level parameter (and curve) on audio source
    float spread;                                                             // Spread parameter of the audio source (0..360 degrees)
    float stereopan;                                                          // Stereo panning parameter of the audio source (-1 = fully left, 1 = fully right)
    UnityAudioEffect_DistanceAttenuationCallback distanceattenuationcallback; // The spatializer plugin may override the distance attenuation in order to influence the voice prioritization (leave this callback as NULL to use the built-in audio source attenuation curve)
};

struct UnityAudioEffectState
{
    union
    {
        struct
        {
            UInt32                             structsize;         // Size of this struct
            UInt32                             samplerate;         // System sample rate
            UInt64                             currdsptick;        // Pointer to a sample counter marking the start of the current block being processed
            UInt64                             prevdsptick;        // Used for determining when DSPs are bypassed and so sidechain info becomes invalid
            float*                             sidechainbuffer;    // Side-chain buffers to read from
            void*                              effectdata;         // Internal data for the effect
            UInt32                             flags;              // Various flags through which information can be queried from the host
            void*                              internal;           // Internal data, do not touch!

            // Version 1.0 of the plugin API only contains data up to here, so perform a state->structsize >= sizeof(UnityAudioEffectState) in your code before you
            // access any of this data in order to detect whether the host API is older than the plugin.

            UnityAudioSpatializerData*         spatializerdata;    // Data for spatializers
            UInt32                             dspbuffersize;      // Number of frames being processed per process callback. Use this to allocate temporary buffers before processing starts.
            UInt32                             hostapiversion;     // Version of plugin API used by host
        };
        unsigned char pad[80]; // This entire structure must be a multiple of 16 bytes (and and instance 16 byte aligned) for PS3 SPU DMA requirements
    };
#ifdef __cplusplus
    template<typename T> inline T* GetEffectData() const
    {
#if !UNITY_SPU // asserts require _exit() to be defined
        assert(effectdata);
        assert(internal);
#endif
        return (T*)effectdata;
    }

#endif
};

struct UnityAudioParameterDefinition
{
    char                                       name[16];           // Display name on the GUI
    char                                       unit[16];           // Scientific unit of parameter to be appended after the value in textboxes
    const char*                                description;        // Description of parameter (displayed in tool tips, automatically generated documentation, etc.)
    float                                      min;                // Minimum value of the parameter
    float                                      max;                // Maximum value of the parameter
    float                                      defaultval;         // Default and initial value of the parameter
    float                                      displayscale;       // Scale factor used only for the display of parameters (i.e. 100 for a percentage value ranging from 0 to 1)
    float                                      displayexponent;    // Exponent for mapping parameters to sliders
};

struct UnityAudioEffectDefinition
{
    UInt32                                     structsize;         // Size of this struct
    UInt32                                     paramstructsize;    // Size of paramdesc fields
    UInt32                                     apiversion;         // Plugin API version
    UInt32                                     pluginversion;      // Version of this plugin
    UInt32                                     channels;           // Number of channels. Effects should set this to 0 and process any number of input/output channels they get in the process callback. Generator elements should specify a >0 value here.
    UInt32                                     numparameters;      // The number of parameters exposed by this plugin.
    UInt64                                     flags;              // Various capabilities and requirements of the plugin.
    char                                       name[32];           // Name used for registration of the effect. This name will also be displayed in the GUI.
    UnityAudioEffect_CreateCallback            create;             // The create callback is called when DSP unit is created and can be null.
    UnityAudioEffect_ReleaseCallback           release;            // The release callback is called just before the plugin is freed and should free any data associated with this specific instance of the plugin. No further callbacks related to the instance will happen after this function has been called.
    UnityAudioEffect_ResetCallback             reset;              // The reset callback is called by the user to bring back the plugin instance into its initial state. Use to avoid clicks or artifacts.
    UnityAudioEffect_ProcessCallback           process;            // The processing callback is repeatedly called with a block of input audio to read from and an output block to write to.
    UnityAudioEffect_SetPositionCallback       setposition;        // The position callback can be used for implementing seek operations.
    UnityAudioParameterDefinition*             paramdefs;          // A pointer to the definitions of the parameters exposed by this plugin. This data pointed to must remain valid for the whole lifetime of the dynamic library (ideally it's static).
    UnityAudioEffect_SetFloatParameterCallback setfloatparameter;  // This is called whenever one of the exposed parameters is changed.
    UnityAudioEffect_GetFloatParameterCallback getfloatparameter;  // This is called to query parameter values.
    UnityAudioEffect_GetFloatBufferCallback    getfloatbuffer;     // Get N samples of named buffer. Used for displaying analysis data from the runtime.
};

// This function fills in N pointers for the N effects contained in the library and returns N.
extern "C" UNITY_AUDIODSP_EXPORT_API int UnityGetAudioEffectDefinitions(UnityAudioEffectDefinition*** descptr);
#endif
