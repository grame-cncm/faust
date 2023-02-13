/************************** BEGIN faust-poly-engine.h *******************
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

#ifndef __faust_poly_engine__
#define __faust_poly_engine__

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "faust/dsp/dsp.h"
#include "faust/audio/audio.h"
#include "faust/gui/meta.h"
#include "faust/gui/JSONUI.h"
#include "faust/gui/APIUI.h"
#include "faust/gui/MidiUI.h"
#include "faust/dsp/poly-dsp.h"
#include "faust/dsp/faust-engine.h"

//**************************************************************
// Mono or polyphonic audio DSP engine
//**************************************************************

class FaustPolyEngine {
        
    protected:

        mydsp_poly* fPolyDSP;     // the polyphonic Faust object
        dsp* fFinalDSP;           // the "final" dsp object submitted to the audio driver
    
        APIUI fAPIUI;             // the UI description

        std::string fJSONUI;
        std::string fJSONMeta;
        bool fRunning;
        audio* fDriver;
    
        midi_handler fMidiHandler;
        MidiUI fMidiUI;
    
        void init(dsp* mono_dsp, audio* driver, midi_handler* handler)
        {
            bool midi_sync = false;
            int nvoices = 0;
            fRunning = false;
            
            MidiMeta::analyse(mono_dsp, midi_sync, nvoices);
            
            // Getting the UI JSON
            JSONUI jsonui1(mono_dsp->getNumInputs(), mono_dsp->getNumOutputs());
            mono_dsp->buildUserInterface(&jsonui1);
            fJSONUI = jsonui1.JSON();
            
            // Getting the metadata JSON
            JSONUI jsonui1M(mono_dsp->getNumInputs(), mono_dsp->getNumOutputs());
            mono_dsp->metadata(&jsonui1M);
            fJSONMeta = jsonui1M.JSON();
            
            if (nvoices > 0) {
                
                fPolyDSP = new mydsp_poly(mono_dsp, nvoices, true);
                
            #if POLY2
                fFinalDSP = new dsp_sequencer(fPolyDSP, new effect());
            #else
                fFinalDSP = fPolyDSP;
            #endif
                
                // Update JSONs with Poly version
                JSONUI jsonui2(mono_dsp->getNumInputs(), mono_dsp->getNumOutputs());
                fFinalDSP->buildUserInterface(&jsonui2);
                fJSONUI = jsonui2.JSON();
                
                JSONUI jsonui2M(mono_dsp->getNumInputs(), mono_dsp->getNumOutputs());
                fFinalDSP->metadata(&jsonui2M);
                fJSONMeta = jsonui2M.JSON();
                
            } else {
                fPolyDSP = nullptr;
                fFinalDSP = mono_dsp;
            }
            
            fFinalDSP->buildUserInterface(&fMidiUI);
            fFinalDSP->buildUserInterface(&fAPIUI);
            
            // Retrieving DSP object name
            struct MyMeta : public Meta
            {
                std::string fName;
                void declare(const char* key, const char* value)
                {
                    if (strcmp(key, "name") == 0) fName = value;
                }
                MyMeta():fName("Dummy"){}
            };
      
            MyMeta meta;
            fFinalDSP->metadata(&meta);
            if (handler) handler->setName(meta.fName);
            
            if (driver) {
                // If driver cannot be initialized, start will fail later on...
                if (!driver->init(meta.fName.c_str(), fFinalDSP)) {
                    delete driver;
                    fDriver = nullptr;
                } else {
                    fDriver = driver;
                }
            } else {
                fDriver = nullptr;
            }
        }
    
    public:
    
        FaustPolyEngine(dsp* mono_dsp, audio* driver = nullptr, midi_handler* midi = nullptr):fMidiUI(&fMidiHandler)
        {
            assert(mono_dsp);
            init(mono_dsp, driver, midi);
        }
    
        virtual ~FaustPolyEngine()
        {
            delete fDriver;
            delete fFinalDSP;
        }

        /*
         * start()
         * Begins the processing and return true if the connection
         * with the audio device was successful and false if not.
         */
        bool start()
        {
            if (!fRunning) {
                fRunning = (fDriver) ? fDriver->start() : false;
            }
            return fRunning;
        }
    
        /*
         * isRunning()
         * Returns true if the DSP frames are being computed and
         * false if not.
         */
        bool isRunning() 
        {
            return fRunning;
        }

        /*
         * stop()
         * Stops the processing, closes the audio engine.
         */
        void stop()
        {
            if (fRunning) {
                fRunning = false;
                if (fDriver) fDriver->stop();
            }
        }
    
        /*
         * keyOn(pitch, velocity)
         * Instantiates a new polyphonic voice where velocity
         * and pitch are MIDI numbers (0-127). keyOn can only
         * be used if nvoices > 0. keyOn will return 0 if the
         * object is not polyphonic and the allocated voice otherwise.
         */
        MapUI* keyOn(int pitch, int velocity)
        {
            if (fPolyDSP) {
                return fPolyDSP->keyOn(0, pitch, velocity); // MapUI* passed to Java as an integer
            } else {
                return 0;
            }
        }

        /*
         * keyOff(pitch)
         * De-instantiates a polyphonic voice where pitch is the
         * MIDI number of the note (0-127). keyOff can only be
         * used if nvoices > 0. keyOff will return 0 if the
         * object is not polyphonic and 1 otherwise.
         */
        int keyOff(int pitch, int velocity = 0)
        {
            if (fPolyDSP) {
                fPolyDSP->keyOff(0, pitch, velocity);
                return 1;
            } else {
                return 0;
            }
        }

        /*
         * newVoice()
         * Instantiate a new voice and returns the corresponding mapUI.
         */
        MapUI* newVoice()
        {
            if (fPolyDSP) {
                return fPolyDSP->newVoice();
            } else {
                return 0;
            }
        }

        /*
         * deleteVoice(MapUI* voice)
         * Delete a voice based on its MapUI*.
         */
        int deleteVoice(MapUI* voice)
        {
            if (fPolyDSP) {
                fPolyDSP->deleteVoice(voice);
                return 1;
            } else {
                return 0;
            }
        }

        /*
         * deleteVoice(uintptr_t voice)
         * Delete a voice based on its MapUI* casted as a uintptr_t.
         */
        int deleteVoice(uintptr_t voice)
        {
            return deleteVoice(reinterpret_cast<MapUI*>(voice));
        }
        
        /*
         * allNotesOff()
         * Terminates all the active voices, gently (with release when hard = false or immediately when hard = true)
         */
        void allNotesOff(bool hard = false)
        {
            if (fPolyDSP) {
                fPolyDSP->allNotesOff(hard);
            }
        }
    
        /*
         * Propagate MIDI data to the Faust object.
         */
        void propagateMidi(int count, double time, int type, int channel, int data1, int data2)
        {
            if (count == 3) fMidiHandler.handleData2(time, type, channel, data1, data2);
            else if (count == 2) fMidiHandler.handleData1(time, type, channel, data1);
            else if (count == 1) fMidiHandler.handleSync(time, type);
            // In POLY mode, update all voices
            GUI::updateAllGuis();
        }
    
        /*
         * getJSONUI()
         * Returns a string containing a JSON description of the
         * UI of the Faust object.
         */
        const char* getJSONUI()
        {
            return fJSONUI.c_str();
        }
        
        /*
         * getJSONMeta()
         * Returns a string containing a JSON description of the
         * metadata of the Faust object.
         */
        const char* getJSONMeta()
        {
            return fJSONMeta.c_str();
        }
    
        /*
         * buildUserInterface(UI* ui_interface)
         * Calls the polyphonic or monophonic buildUserInterface with the ui_interface parameter.
         */
        void buildUserInterface(UI* ui_interface)
        {
            fFinalDSP->buildUserInterface(ui_interface);
        }
    
        void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fFinalDSP->compute(count, inputs, outputs);
        }

        /*
         * getParamsCount()
         * Returns the number of control parameters of the Faust object.
         */
        int getParamsCount()
        {
            return fAPIUI.getParamsCount();
        }
    
        /*
         * setParamValue(address, value)
         * Sets the value of the parameter associated with address.
         */
        void setParamValue(const char* address, float value)
        {
            fAPIUI.setParamValue(address, value);
            // In POLY mode, update all voices
            GUI::updateAllGuis();
        }
        
        /*
         * getParamValue(address)
         * Takes the address of a parameter and returns its current value.
         */
        float getParamValue(const char* address)
        {
            return fAPIUI.getParamValue(address);
        }
    
        /*
         * setParamValue(id, value)
         * Sets the value of the parameter associated with id.
         */
        void setParamValue(int id, float value)
        {
            fAPIUI.setParamValue(id, value);
            // In POLY mode, update all voices
            GUI::updateAllGuis();
        }
        
        /*
         * getParamValue(id)
         * Takes the id of a parameter and returns its current value.
         */
        float getParamValue(int id)
        {
            return fAPIUI.getParamValue(id);
        }

        /*
         * setVoiceParamValue(address, voice, value)
         * Sets the value of the parameter associated with address for
         * the voice. setVoiceParamValue can only be used if nvoices > 0.
         */
        void setVoiceParamValue(const char* address, uintptr_t voice, float value)
        {
            reinterpret_cast<MapUI*>(voice)->setParamValue(address, value);
        }

        /*
         * setVoiceParamValue(id, voice, value)
         * Sets the value of the parameter associated with the id for
         * the voice. setVoiceParamValue can only be used if nvoices > 0.
         */
        void setVoiceParamValue(int id, uintptr_t voice, float value)
        {
            reinterpret_cast<MapUI*>(voice)->setParamValue(reinterpret_cast<MapUI*>(voice)->getParamAddress(id), value);
        }
    
        /*
         * getVoiceParamValue(address, voice)
         * Gets the parameter value associated with address for the voice.
         * getVoiceParamValue can only be used if nvoices > 0.
         */
        float getVoiceParamValue(const char* address, uintptr_t voice)
        {
            return reinterpret_cast<MapUI*>(voice)->getParamValue(address);
        }

        /*
         * getVoiceParamValue(id, voice)
         * Gets the parameter value associated with the id for the voice.
         * getVoiceParamValue can only be used if nvoices > 0.
         */
        float getVoiceParamValue(int id, uintptr_t voice)
        {
            return reinterpret_cast<MapUI*>(voice)->getParamValue(reinterpret_cast<MapUI*>(voice)->getParamAddress(id));
        }
    
        /*
         * getParamLabel(id)
         * Returns the label of a parameter in function of its "id".
         */
        const char* getParamLabel(int id)
        {
            return fAPIUI.getParamLabel(id);
        }
    
        /*
         * getParamShortname(id)
         * Returns the shortname of a parameter in function of its "id".
         */
        const char* getParamShortname(int id)
        {
            return fAPIUI.getParamShortname(id);
        }

        /*
         * getParamAddress(id)
         * Returns the address of a parameter in function of its "id".
         */
        const char* getParamAddress(int id)
        {
            return fAPIUI.getParamAddress(id);
        }

        /*
         * getVoiceParamAddress(id, voice)
         * Returns the address of a parameter for a specific voice in function of its "id".
         */
        const char* getVoiceParamAddress(int id, uintptr_t voice)
        {
            return reinterpret_cast<MapUI*>(voice)->getParamAddress1(id);
        }
        
        /*
         * getParamMin(address)
         * Returns the minimum value of a parameter.
         */
        float getParamMin(const char* address)
        {
            int id = (address) ? fAPIUI.getParamIndex(address) : -1;
            return (id >= 0) ? fAPIUI.getParamMin(id) : 0.f;
        }
    
        /*
         * getParamMin(id)
         * Returns the minimum value of a parameter.
         */
        float getParamMin(int id)
        {
            return fAPIUI.getParamMin(id);
        }
    
        /*
         * getParamMax(address)
         * Returns the maximum value of a parameter.
         */
        float getParamMax(const char* address)
        {
            int id = (address) ? fAPIUI.getParamIndex(address) : -1;
            return (id >= 0) ? fAPIUI.getParamMax(id) : 0.f;
        }
    
        /*
         * getParamMax(id)
         * Returns the maximum value of a parameter.
         */
        float getParamMax(int id)
        {
            return fAPIUI.getParamMax(id);
        }
    
        /*
         * getParamInit(address)
         * Returns the default value of a parameter.
         */
        float getParamInit(const char* address)
        {
            int id = (address) ? fAPIUI.getParamIndex(address) : -1;
            return (id >= 0) ? fAPIUI.getParamInit(id) : 0.f;
        }
    
        /*
         * getParamInit(id)
         * Returns the default value of a parameter.
         */
        float getParamInit(int id)
        {
            return fAPIUI.getParamInit(id);
        }
    
        /*
         * getMetadata(address, key)
         * Returns the metadata of a parameter.
         */
        const char* getMetadata(const char* address, const char* key)
        {
            int id = (address) ? fAPIUI.getParamIndex(address) : -1;
            return (id >= 0) ? fAPIUI.getMetadata(id, key) : "";
        }
    
        /*
         * getMetadata(id, key)
         * Returns the metadata of a parameter.
         */
        const char* getMetadata(int id, const char* key)
        {
            return fAPIUI.getMetadata(id, key);
        }

        /*
         * propagateAcc(int acc, float v)
         * Propage accelerometer value to the curve conversion layer.
         */
        void propagateAcc(int acc, float v)
        {
            fAPIUI.propagateAcc(acc, v);
            // In POLY mode, update all voices
            GUI::updateAllGuis();
        }

        /*
         * setAccConverter(int p, int acc, int curve, float amin, float amid, float amax)
         * Change accelerometer curve mapping.
         */
        void setAccConverter(int p, int acc, int curve, float amin, float amid, float amax)
        {
            fAPIUI.setAccConverter(p, acc, curve, amin, amid, amax);
        }

        /*
         * propagateGyr(int gyr, float v)
         * Propage gyroscope value to the curve conversion layer.
         */
        void propagateGyr(int gyr, float v)
        {
            fAPIUI.propagateGyr(gyr, v);
            // In POLY mode, update all voices
            GUI::updateAllGuis();
        }

        /*
         * setGyrConverter(int p, int acc, int curve, float amin, float amid, float amax)
         * Change gyroscope curve mapping.
         */
        void setGyrConverter(int p, int gyr, int curve, float amin, float amid, float amax)
        {
            fAPIUI.setGyrConverter(p, gyr, curve, amin, amid, amax);
        }
    
        /*
         * getCPULoad()
         * Return DSP CPU load.
         */
        float getCPULoad() { return (fDriver) ? fDriver->getCPULoad() : 0.f; }

        /*
         * getScreenColor()
         * Get the requested screen color.
         * -1 means no screen color control (no screencolor metadata found)
         * otherwise return 0x00RRGGBB a ready to use color
         */
        int getScreenColor()
        {
            return fAPIUI.getScreenColor();
        }

};

// Public C API

#ifdef __cplusplus
extern "C" {
#endif
    
    void destroy(void* dsp) { delete reinterpret_cast<FaustPolyEngine*>(dsp); }

    bool start(void* dsp) { return reinterpret_cast<FaustPolyEngine*>(dsp)->start(); }
    void stop(void* dsp) { reinterpret_cast<FaustPolyEngine*>(dsp)->stop(); }
    
    bool isRunning(void* dsp) { return reinterpret_cast<FaustPolyEngine*>(dsp)->isRunning(); }

    uintptr_t keyOn(void* dsp, int pitch, int velocity) { return (uintptr_t)reinterpret_cast<FaustPolyEngine*>(dsp)->keyOn(pitch, velocity); }
    int keyOff(void* dsp, int pitch) { return reinterpret_cast<FaustPolyEngine*>(dsp)->keyOff(pitch); }
    
    void propagateMidi(void* dsp, int count, double time, int type, int channel, int data1, int data2)
    {
        reinterpret_cast<FaustPolyEngine*>(dsp)->propagateMidi(count, time, type, channel, data1, data2);
    }

    const char* getJSONUI(void* dsp) { return reinterpret_cast<FaustPolyEngine*>(dsp)->getJSONUI(); }
    const char* getJSONMeta(void* dsp) { return reinterpret_cast<FaustPolyEngine*>(dsp)->getJSONMeta(); }

    int getParamsCount(void* dsp) { return reinterpret_cast<FaustPolyEngine*>(dsp)->getParamsCount(); }
    
    void setParamValue(void* dsp, const char* address, float value)
    {
        reinterpret_cast<FaustPolyEngine*>(dsp)->setParamValue(address, value);
    }
    float getParamValue(void* dsp, const char* address) { return reinterpret_cast<FaustPolyEngine*>(dsp)->getParamValue(address); }
   
    void setParamIdValue(void* dsp, int id, float value) { reinterpret_cast<FaustPolyEngine*>(dsp)->setParamValue(id, value); }
    float getParamIdValue(void* dsp, int id) { return reinterpret_cast<FaustPolyEngine*>(dsp)->getParamValue(id); }
    
    void setVoiceParamValue(void* dsp, const char* address, uintptr_t voice, float value)
    {
        reinterpret_cast<FaustPolyEngine*>(dsp)->setVoiceParamValue(address, voice, value);
    }
    float getVoiceParamValue(void* dsp, const char* address, uintptr_t voice)
    {
        return reinterpret_cast<FaustPolyEngine*>(dsp)->getVoiceParamValue(address, voice);
    }
    
    const char* getParamLabel(void* dsp, int id) { return reinterpret_cast<FaustPolyEngine*>(dsp)->getParamLabel(id); }
    const char* getParamShortname(void* dsp, int id) { return reinterpret_cast<FaustPolyEngine*>(dsp)->getParamShortname(id); }
    const char* getParamAddress(void* dsp, int id) { return reinterpret_cast<FaustPolyEngine*>(dsp)->getParamAddress(id); }

    void propagateAcc(void* dsp, int acc, float v) { reinterpret_cast<FaustPolyEngine*>(dsp)->propagateAcc(acc, v); }
    void setAccConverter(void* dsp, int p, int acc, int curve, float amin, float amid, float amax)
    {
        reinterpret_cast<FaustPolyEngine*>(dsp)->setAccConverter(p, acc, curve, amin, amid, amax);
    }
    void propagateGyr(void* dsp, int acc, float v) { reinterpret_cast<FaustPolyEngine*>(dsp)->propagateGyr(acc, v); }
    void setGyrConverter(void* dsp, int p, int gyr, int curve, float amin, float amid, float amax)
    {
        reinterpret_cast<FaustPolyEngine*>(dsp)->setGyrConverter(p, gyr, curve, amin, amid, amax);
    }

    float getCPULoad(void* dsp) { return reinterpret_cast<FaustPolyEngine*>(dsp)->getCPULoad(); }
    int getScreenColor(void* dsp) { return reinterpret_cast<FaustPolyEngine*>(dsp)->getScreenColor(); }
    
#ifdef __cplusplus
}
#endif

#endif // __faust_poly_engine__
/************************** END faust-poly-engine.h **************************/
