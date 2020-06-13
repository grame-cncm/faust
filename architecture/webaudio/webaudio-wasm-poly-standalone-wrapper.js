/*
 faust2webaudio

 Primarily written by Myles Borins
 During the Spring 2013 offering of Music 420b with Julius Smith
 A bit during the Summer of 2013 with the help of Joshua Kit Clayton
 And finally a sprint during the late fall of 2013 to get everything working
 A Special thanks to Yann Orlarey and Stéphane Letz

 faust2webaudio is distributed under the terms the MIT or GPL2 Licenses.
 Choose the license that best suits your project. The text of the MIT and GPL
 licenses are at the root directory.

 Additional code: GRAME 2014-2019
*/

'use strict';

/**
 * @class FaustWasm2ScriptProcessorPoly
 * @property {string} name - name of current DSP
 * @property {{ [key: string]: any }} dspProps - dsp properties
 * @property {{ [key: string]: any }} effectProps - effect properties
 * @property {any[]} _log - event log
 * @property {string[]} node - ScriptProcessorNode
 * @property {boolean} debug - debug mode
 */
class FaustWasm2ScriptProcessorPoly {

   /**
     * Creates an instance of FaustWasm2ScriptProcessorPoly.
     * @param {string} dspName - dsp name
     * @param {{ [key: string]: any }} dspProps - dsp properties parsed by json
     * @param {{ [key: string]: any }} effectProps - dsp properties parsed by jsonEffect
     * @param {{ debug: boolean, [key: string]: any }} options - compile options
     */
    constructor(dspName, dspProps, effectProps, options) {
        this.name = dspName;
        this.dspProps = dspProps;
        this.effectProps = effectProps;
        this._log = [];
        this.node;
        this.debug = false || (typeof options === "object" && options.debug);
    }
    /**
     * Constructor of Monophonic Faust DSP
     *
     * @param {WebAssembly.Instance} mixerInstance - the wasm mixer instance
     * @param {WebAssembly.Instance} dspInstance - the wasm instance
     * @param {WebAssembly.Instance} effectInstance - the wasm DSP effect instance (can be null)
     * @param {WebAssembly.Memory} memory - the wasm memory
     * @param {AudioContext | webkitAudioContext} audioCtx - the Web Audio context
     * @param {number} bufferSize - the buffer_size in frames
     * @param {number} polyphony - the number of polyphonic voices
     *
     * @returns {ScriptProcessorNode} a valid WebAudio ScriptProcessorNode object or null
     */
    getNode(mixerInstance, dspInstance, effectInstance, memory, audioCtx, bufferSize, polyphony) {
        let sp;
        const inputs = parseInt(this.dspProps.inputs);
        const outputs = parseInt(this.dspProps.outputs);
        try {
            sp = audioCtx.createScriptProcessor(bufferSize, inputs, outputs);
        } catch (e) {
            this.error("Error in createScriptProcessor: " + e);
            return null;
        }
        sp.json_object = this.dspProps;
        sp.effect_json_object = this.effectProps;
    
        sp.output_handler = null;
        sp.ins = null;
        sp.outs = null;
        sp.mixing = null;
        sp.compute_handler = null;
    
        sp.dspInChannnels = [];
        sp.dspOutChannnels = [];
    
        sp.fFreqLabel = [];
        sp.fGateLabel = [];
        sp.fGainLabel = [];
        sp.fDate = 0;
    
        sp.fPitchwheelLabel = [];
        sp.fCtrlLabel = new Array(128).fill(null).map(() => []);
        
        sp.remap = (v, mn0, mx0, mn1, mx1) => (v - mn0) / (mx0 - mn0) * (mx1 - mn1) + mn1;
    
        sp.numIn = inputs;
        sp.numOut = outputs;
    
        this.log(sp.numIn);
        this.log(sp.numOut);
    
        // Memory allocator
        sp.ptr_size = 4;
        sp.sample_size = 4;
    
        sp.factory = dspInstance.exports;
        sp.HEAP = memory.buffer;
        sp.HEAP32 = new Int32Array(sp.HEAP);
        sp.HEAPF32 = new Float32Array(sp.HEAP);
    
        this.log(sp.HEAP);
        this.log(sp.HEAP32);
        this.log(sp.HEAPF32);

        // bargraph
        sp.outputs_timer = 5;
        sp.outputs_items = [];
    
        // input items
        sp.inputs_items = [];
    
        // Start of HEAP index
    
        // DSP is placed first with index 0. Audio buffer start at the end of DSP.
        sp.audio_heap_ptr = 0;
    
        // Setup pointers offset
        sp.audio_heap_ptr_inputs = sp.audio_heap_ptr;
        sp.audio_heap_ptr_outputs = sp.audio_heap_ptr_inputs + sp.numIn * sp.ptr_size;
        sp.audio_heap_ptr_mixing = sp.audio_heap_ptr_outputs + sp.numOut * sp.ptr_size;
    
        // Setup buffer offset
        sp.audio_heap_inputs = sp.audio_heap_ptr_mixing + sp.numOut * sp.ptr_size;
        sp.audio_heap_outputs = sp.audio_heap_inputs + sp.numIn * bufferSize * sp.sample_size;
        sp.audio_heap_mixing = sp.audio_heap_outputs + sp.numOut * bufferSize * sp.sample_size;
        
        // Setup DSP voices offset
        sp.dsp_start = sp.audio_heap_mixing + sp.numOut * bufferSize * sp.sample_size;

        // wasm mixer
        sp.mixer = mixerInstance.exports;
        // wasm effect
        sp.effect = effectInstance ? effectInstance.exports : null;

        this.log(sp.mixer);
        this.log(sp.factory);
        this.log(sp.effect);
        
        // Start of DSP memory ('polyphony' DSP voices)
        sp.dsp_voices = [];
        sp.dsp_voices_state = [];
        sp.dsp_voices_level = [];
        sp.dsp_voices_date = [];
    
        sp.kActiveVoice = 0;
        sp.kFreeVoice = -1;
        sp.kReleaseVoice = -2;
        sp.kNoVoice = -3;

        sp.pathTable = [];
    
        for (let i = 0; i < polyphony; i++) {
            sp.dsp_voices[i] = sp.dsp_start + i * parseInt(sp.json_object.size);
            sp.dsp_voices_state[i] = sp.kFreeVoice;
            sp.dsp_voices_level[i] = 0;
            sp.dsp_voices_date[i] = 0;
        }
            
        // Effect memory starts after last voice
        sp.effect_start = sp.dsp_voices[polyphony - 1] + parseInt(json_object.size);

        sp.getPlayingVoice = pitch => {
            let voice = sp.kNoVoice;
            let oldestDatePlaying = Number.MAX_VALUE;
            for (let i = 0; i < polyphony; i++) {
                if (sp.dsp_voices_state[i] === pitch) {
                    // Keeps oldest playing voice
                    if (sp.dsp_voices_date[i] < oldestDatePlaying) {
                        oldestDatePlaying = sp.dsp_voices_date[i];
                        voice = i;
                    }
                }
            }
            return voice;
        }
        // Always returns a voice
        sp.allocVoice = voice => {
            // so that envelop is always re-initialized
            sp.factory.instanceClear(sp.dsp_voices[voice]);
            sp.dsp_voices_date[voice] = sp.fDate++;
            sp.dsp_voices_state[voice] = sp.kActiveVoice;
            return voice;
        }

        sp.getFreeVoice = () => {
            for (let i = 0; i < polyphony; i++) {
                if (sp.dsp_voices_state[i] === sp.kFreeVoice) return sp.allocVoice(i);
            }
            let voice_release = sp.kNoVoice;
            let voice_playing = sp.kNoVoice;
            let oldest_date_release = Number.MAX_VALUE;
            let oldest_date_playing = Number.MAX_VALUE;
            for (let i = 0; i < polyphony; i++) { // Scan all voices
                // Try to steal a voice in kReleaseVoice mode...
                if (sp.dsp_voices_state[i] === sp.kReleaseVoice) {
                    // Keeps oldest release voice
                    if (sp.dsp_voices_date[i] < oldest_date_release) {
                        oldest_date_release = sp.dsp_voices_date[i];
                        voice_release = i;
                    }
                } else {
                    if (sp.dsp_voices_date[i] < oldest_date_playing) {
                        oldest_date_playing = sp.dsp_voices_date[i];
                        voice_playing = i;
                    }
                }
            }
            // Then decide which one to steal
            if (oldest_date_release != Number.MAX_VALUE) {
                this.log(`Steal release voice : voice_date = ${sp.dsp_voices_date[voice_release]} cur_date = ${sp.fDate} voice = ${voice_release}`);
                return sp.allocVoice(voice_release);
            } else if (oldest_date_playing != Number.MAX_VALUE) {
                this.log(`Steal playing voice : voice_date = ${sp.dsp_voices_date[voice_playing]} cur_date = ${sp.fDate} voice = ${voice_playing}`);
                return sp.allocVoice(voice_playing);
            } else {
                return sp.kNoVoice;
            }
        }
    
        sp.update_outputs = () => {
            if (sp.outputs_items.length > 0 && sp.output_handler && sp.outputs_timer-- === 0) {
                sp.outputs_timer = 5;
                sp.outputs_items.forEach(item => sp.output_handler(item, sp.factory.getParamValue(sp.dsp, sp.pathTable[item])));
            }
        };

        sp.compute = e => {
            for (let i = 0; i < sp.numIn; i++) { // Read inputs
                const input = e.inputBuffer.getChannelData(i);
                const dspInput = sp.dspInChannnels[i];
                dspInput.set(input);
            }
            try {
          
                // Possibly call an externally given callback (for instance to synchronize playing a MIDIFile...)
                if (sp.compute_handler) sp.compute_handler(bufferSize);
                sp.mixer.clearOutput(bufferSize, sp.numOut, sp.outs); // First clear the outputs
                for (let i = 0; i < polyphony; i++) { // Compute all running voices
                    if (sp.dsp_voices_state[i] === sp.kFreeVoice) continue;
                    sp.factory.compute(sp.dsp_voices[i], bufferSize, sp.ins, sp.mixing); // Compute voice
                    sp.dsp_voices_level[i] = sp.mixer.mixVoice(bufferSize, sp.numOut, sp.mixing, sp.outs); // Mix it in result
                    // Check the level to possibly set the voice in kFreeVoice again
                    if (sp.dsp_voices_level[i] < 0.0005 && sp.dsp_voices_state[i] === sp.kReleaseVoice) {
                        sp.dsp_voices_state[i] = sp.kFreeVoice;
                    }
                }
                
                if (sp.effect) sp.effect.compute(sp.effect_start, bufferSize, sp.outs, sp.outs); // Apply effect
            } catch(e) {
                console.log("ERROR in compute (" + e + ")");
            }
            
            sp.update_outputs(); // Update bargraph
            for (let i = 0; i < sp.numOut; i++) { // Write outputs
                const output = e.outputBuffer.getChannelData(i);
                const dspOutput = sp.dspOutChannnels[i];
                output.set(dspOutput);
            }
        };

        sp.midiToFreq = note => 440.0 * Math.pow(2.0, (note - 69.0) / 12.0);

        // JSON parsing
        sp.parse_ui = ui => ui.forEach(group => sp.parse_group(group));
        sp.parse_group = group => group.items ? sp.parse_items(group.items) : null;
        sp.parse_items = items => items.forEach(item => sp.parse_item(item));
        sp.parse_item = item => {
            if (item.type === "vgroup" || item.type === "hgroup" || item.type === "tgroup") {
                sp.parse_items(item.items);
            } else if (item.type === "hbargraph" || item.type === "vbargraph") {
                // Keep bargraph adresses
                sp.outputs_items.push(item.address);
                sp.pathTable[item.address] = parseInt(item.index);
            } else if (item.type === "vslider" || item.type === "hslider" || item.type === "button"
                    || item.type === "checkbox" || item.type === "nentry") {
                // Keep inputs adresses
                sp.inputs_items.push(item.address);
                sp.pathTable[item.address] = parseInt(item.index);
                if (!item.meta) return;
                item.meta.forEach(meta => {
                    const midi = meta.midi;
                    if (!midi) return;
                    const strMidi = midi.trim();
                    if (strMidi === "pitchwheel") {
                        sp.fPitchwheelLabel.push({
                            path: item.address,
                            min: parseFloat(item.min),
                            max: parseFloat(item.max)
                        });
                    } else {
                        const matched = strMidi.match(/^ctrl\s(\d+)/);
                        if (!matched) return;
                        sp.fCtrlLabel[parseInt(matched[1])].push({
                            path: item.address,
                            min: parseFloat(item.min),
                            max: parseFloat(item.max)
                        });
                    }
                })
            }
        }
        sp.initAux = () => { // Setup web audio context
            this.log("buffer_size " + bufferSize);
            sp.onaudioprocess = sp.compute;
            if (sp.numIn > 0) {
                sp.ins = sp.audio_heap_ptr_inputs;
                for (let i = 0; i < sp.numIn; i++) {
                    sp.HEAP32[(sp.ins >> 2) + i] = sp.audio_heap_inputs + bufferSize * sp.sample_size * i;
                }
                // Prepare Ins buffer tables
                const dspInChans = sp.HEAP32.subarray(sp.ins >> 2, (sp.ins + sp.numIn * sp.ptr_size) >> 2);
                for (let i = 0; i < sp.numIn; i++) {
                    sp.dspInChannnels[i] = sp.HEAPF32.subarray(dspInChans[i] >> 2, (dspInChans[i] + bufferSize * sp.sample_size) >> 2);
                }
            }
            if (sp.numOut > 0) {
                sp.outs = sp.audio_heap_ptr_outputs; // allocate memory for output and mixing arrays
                sp.mixing = sp.audio_heap_ptr_mixing;
                for (let i = 0; i < sp.numOut; i++) {
                    sp.HEAP32[(sp.outs >> 2) + i] = sp.audio_heap_outputs + bufferSize * sp.sample_size * i;
                    sp.HEAP32[(sp.mixing >> 2) + i] = sp.audio_heap_mixing + bufferSize * sp.sample_size * i;
                }
                // Prepare Out buffer tables
                const dspOutChans = sp.HEAP32.subarray(sp.outs >> 2, (sp.outs + sp.numOut * sp.ptr_size) >> 2);
                for (let i = 0; i < sp.numOut; i++) {
                    sp.dspOutChannnels[i] = sp.HEAPF32.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + bufferSize * sp.sample_size) >> 2);
                }
            }
            // Parse JSON UI part
            sp.parse_ui(sp.json_object.ui);
            if (sp.effect) sp.parse_ui(sp.effect_json_object.ui);
    
            // keep 'keyOn/keyOff' labels
            sp.inputs_items.forEach(item => {
                if (item.endsWith("/gate")) sp.fGateLabel.push(sp.pathTable[item]);
                else if (item.endsWith("/freq")) sp.fFreqLabel.push(sp.pathTable[item])
                else if (item.endsWith("/gain")) sp.fGainLabel.push(sp.pathTable[item])
            })
            // Init DSP voices
            for (let i = 0; i < polyphony; i++) {
                sp.factory.init(sp.dsp_voices[i], audioCtx.sampleRate);
            }
            
            // Init effect
            if (sp.effect) sp.effect.init(sp.effect_start, audioCtx.sampleRate);
        }
        
        // Public API
        
        /**
         * Destroy the node, deallocate resources.
         */
        sp.destroy = () => {}
        
        sp.getSampleRate = () => audioCtx.sampleRate; // Return current sample rate
        sp.getNumInputs = () => sp.numIn; // Return instance number of audio inputs.
        sp.getNumOutputs = () => sp.numOut; // Return instance number of audio outputs.

        /**
         * Global init, doing the following initialization:
         * - static tables initialization
         * - call 'instanceInit': constants and instance state initialisation
         *
         * @param {number} sampleRate - the sampling rate in Hertz
         */
        sp.init = sampleRate => {
            for (let i = 0; i < polyphony; i++) {
                sp.factory.init(sp.dsp_voices[i], sampleRate);
            }
        }

        /**
         * Init instance state.
         *
         * @param {number} sampleRate - the sampling rate in Hertz
         */
        sp.instanceInit = sampleRate => {
            for (let i = 0; i < polyphony; i++) {
                sp.factory.instanceInit(sp.dsp_voices[i], sampleRate);
            }
        }

        /**
         * Init instance constant state.
         *
         * @param {number} sampleRate - the sampling rate in Hertz
         */
        sp.instanceConstants = sampleRate => {
            for (let i = 0; i < polyphony; i++) {
                sp.factory.instanceConstants(sp.dsp_voices[i], sampleRate);
            }
        }

        /* Init default control parameters values. */
        sp.instanceResetUserInterface = () => {
            for (let i = 0; i < polyphony; i++) {
                sp.factory.instanceResetUserInterface(sp.dsp_voices[i]);
            }
        }

        /* Init instance state (delay lines...).*/
        sp.instanceClear = () => {
            for (let i = 0; i < polyphony; i++) {
                sp.factory.instanceClear(sp.dsp_voices[i]);
            }
        }

        /**
         * Trigger the Meta handler with instance specific calls to 'declare' (key, value) metadata.
         *
         * @param {{ declare: (string, any) => any }} handler - the Meta handler as a 'declare' function of type (key, value)
         */
        sp.metadata = handler => {
            if (this.dspProps.meta) {
                this.dspProps.meta.forEach(meta => handler.declare(Object.keys(meta)[0], Object.values(meta)[0]));
            }
        }

        /**
         * Setup a control output handler with a function of type (path, value)
         * to be used on each generated output value. This handler will be called
         * each audio cycle at the end of the 'compute' method.
         *
         * @param {{ declare: (string, any) => any }} handler - a function of type function(path, value)
         */
        sp.setOutputParamHandler = handler => sp.output_handler = handler;
        /**
         * Get the current output handler.
         */
        sp.getOutputParamHandler = () => sp.output_handler;

        /**
         * Instantiates a new polyphonic voice.
         *
         * @param {number} channel - the MIDI channel (0..15, not used for now)
         * @param {number} pitch - the MIDI pitch (0..127)
         * @param {number} velocity - the MIDI velocity (0..127)
         */
        sp.keyOn = (channel, pitch, velocity) => {
            const voice = sp.getFreeVoice();
            this.log("keyOn voice " + voice);
            for (let i = 0; i < sp.fFreqLabel.length; i++) {
                sp.factory.setParamValue(sp.dsp_voices[voice], sp.fFreqLabel[i], sp.midiToFreq(pitch));
            }
            for (let i = 0; i < sp.fGateLabel.length; i++) {
                sp.factory.setParamValue(sp.dsp_voices[voice], sp.fGateLabel[i], 1.0);
            }
            for (let i = 0; i < sp.fGainLabel.length; i++) {
                sp.factory.setParamValue(sp.dsp_voices[voice], sp.fGainLabel[i], velocity / 127);
            }
            sp.dsp_voices_state[voice] = pitch;
        }

        /**
         * De-instantiates a polyphonic voice.
         *
         * @param {number} channel - the MIDI channel (0..15, not used for now)
         * @param {number} pitch - the MIDI pitch (0..127)
         * @param {number} velocity - the MIDI velocity (0..127)
         */
        sp.keyOff = (channel, pitch, velocity) => {
            const voice = sp.getPlayingVoice(pitch);
            if (voice !== sp.kNoVoice) {
                this.log("keyOff voice" + voice);
                // No use of velocity for now...
                for (let i = 0; i < sp.fGateLabel.length; i++) {
                    sp.factory.setParamValue(sp.dsp_voices[voice], sp.fGateLabel[i], 0.0);
                }
                sp.dsp_voices_state[voice] = sp.kReleaseVoice; // Release voice
            } else {
                this.log("Playing voice not found...");
            }
        }

        /**
         * Gently terminates all the active voices.
         */
        sp.allNotesOff = () => {
            for (var i = 0; i < polyphony; i++) {
                for (let j = 0; j < sp.fGateLabel.length; j++) {
                    sp.factory.setParamValue(sp.dsp_voices[i], sp.fGateLabel[j], 0.0);
                }
                sp.dsp_voices_state[i] = sp.kReleaseVoice;
            }
        }

        /**
         * Control change
         *
         * @param {number} channel - the MIDI channel (0..15, not used for now)
         * @param {number} ctrl - the MIDI controller number (0..127)
         * @param {number} value - the MIDI controller value (0..127)
         */
        sp.ctrlChange = (channel, ctrl, value) => {
            if (ctrl === 123 || ctrl === 120) sp.allNotesOff();
            if (!sp.fCtrlLabel[ctrl].length) return;
             sp.fCtrlLabel[ctrl].forEach(ctrl => {
                const path = ctrl.path;
                sp.setParamValue(path, sp.remap(value, 0, 127, ctrl.min, ctrl.max));
                if (sp.output_handler) sp.output_handler(path, sp.getParamValue(path));
            })
        }

        /**
         * PitchWeel
         *
         * @param {number} channel - the MIDI channel (0..15, not used for now)
         * @param {number} value - the MIDI controller value (0..16383)
         */
        sp.pitchWheel = (channel, wheel) => {
            sp.fPitchwheelLabel.forEach(pw => {
                sp.setParamValue(pw.path, sp.remap(wheel, 0, 16383, pw.min, pw.max));
                if (sp.output_handler) sp.output_handler(pw.path, sp.getParamValue(pw.path));
            });
        }
        const findPath = (o, p) => {
            if (typeof o !== "object") return false;
            if (o.address) {
                if (o.address === p) return true;
                return false;
            }
            for (const k in o) {
                if (findPath(o[k], p)) return true;
            }
            return false;
        }

        /**
         * Set control value.
         *
         * @param {string} path - the path to the wanted control (retrieved using 'getParams' method)
         * @param {number} val - the float value for the wanted parameter
         */
        sp.setParamValue = (path, val) => {
            if (sp.effect && findPath(effect_json_object, path)) {
                sp.effect.setParamValue(sp.effect_start, sp.pathTable[path], val);
            } else {
                for (let i = 0; i < polyphony; i++) {
                    sp.factory.setParamValue(sp.dsp_voices[i], sp.pathTable[path], val);
                }
            }
        }

        /**
         * Get control value.
         *
         * @param {string} path - the path to the wanted control (retrieved using 'getParams' method)
         *
         * @return {number} the float value
         */
        sp.getParamValue = path => {
            if (sp.effect && findPath(effect_json_object, path)) {
                return sp.effect.getParamValue(sp.effect_start, sp.pathTable[path]);
            } else {
                return sp.factory.getParamValue(sp.dsp_voices[0], sp.pathTable[path]);
            }
        }

        /**
         * Get the table of all input parameters paths.
         *
         * @return {object} the table of all input parameter paths.
         */
        sp.getParams = () => sp.inputs_items;

        /**
         * Get DSP JSON description with its UI and metadata.
         *
         * @return {string} DSP JSON description
         */
        sp.getJSON = () => {
            const o = sp.json_object;
            const e = sp.effect_json_object;
            const r = { ...o };
            if (e) {
                r.ui = [{ type: "tgroup", label: "Sequencer", items: [
                    { type: "vgroup", label: "Instrument", items: o.ui },
                    { type: "vgroup", label: "Effect", items: e.ui }
                ] }];
            } else {
                r.ui = [{ type: "tgroup", label: "Polyphonic", items: [
                    { type: "vgroup", label: "Voices", items: o.ui }
                ] }];
            }
            return JSON.stringify(r);
        };
        /**
         * Set a compute handler to be called each audio cycle
         * (for instance to synchronize playing a MIDIFile...).
         *
         * @param {(bufferSize: number) => any} handler - a function of type function(buffer_size)
         */
        sp.setComputeHandler = handler => sp.compute_handler = handler;
        /**
         * Get the current compute handler.
         */
        sp.getComputeHandler = () => sp.compute_handler;
    
        // Init resulting DSP
        sp.initAux();
        return sp;
    }

    createMemory(bufferSize, polyphony) {
        // Memory allocator
        const ptrSize = 4;
        const sampleSize = 4;
        const pow2limit = x => {
            let n = 65536; // Minimum = 64 kB
            while (n < x) { n = 2 * n; }
            return n;
        }
        const effect_json_object_size = effect_json_object ? parseInt(effect_json_object.size) : 0;
        let memorySize = pow2limit(
            effect_json_object_size
            + parseInt(json_object.size) * polyphony
            + (parseInt(json_object.inputs) + parseInt(json_object.outputs) * 2)
            * (ptrSize + bufferSize * sampleSize)
        ) / 65536;
        memorySize = Math.max(2, memorySize); // As least 2
        return new WebAssembly.Memory({ initial: memorySize, maximum: memorySize });
    }
    
    /**
     * Create a ScriptProcessorNode Web Audio object
     * by loading and compiling the Faust wasm file
     *
     * @param {AudioContext | webkitAudioContext} audioCtx - the Web Audio context
     * @param {number} bufferSize - the bufferSize in frames
     * @param {number} polyphony - the number of polyphonic voices
     * @returns {Promise<ScriptProcessorNode>} a Promise for valid WebAudio ScriptProcessorNode object or null
     */
    async createDSP(audioCtx, bufferSize, polyphony) {
        const memory = this.createMemory(bufferSize, polyphony);
        const mixObject = {
            imports: { print: console.log },
            memory: { memory }
        };
        const importObject = {
            env: {
                memory,
                memoryBase: 0,
                tableBase: 0,
                _abs: Math.abs,
                
                // Float version
                _acosf: Math.acos,
                _asinf: Math.asin,
                _atanf: Math.atan,
                _atan2f: Math.atan2,
                _ceilf: Math.ceil,
                _cosf: Math.cos,
                _expf: Math.exp,
                _floorf: Math.floor,
                _fmodf: (x, y) => x % y,
                _logf: Math.log,
                _log10f: Math.log10,
                _max_f: Math.max,
                _min_f: Math.min,
                _remainderf: (x, y) => x - Math.round(x / y) * y,
                _powf: Math.pow,
                _roundf: Math.fround,
                _sinf: Math.sin,
                _sqrtf: Math.sqrt,
                _tanf: Math.tan,
                _acoshf: Math.acosh,
                _asinhf: Math.asinh,
                _atanhf: Math.atanh,
                _coshf: Math.cosh,
                _sinhf: Math.sinh,
                _tanhf: Math.tanh,
                
                // Double version
                _acos: Math.acos,
                _asin: Math.asin,
                _atan: Math.atan,
                _atan2: Math.atan2,
                _ceil: Math.ceil,
                _cos: Math.cos,
                _exp: Math.exp,
                _floor: Math.floor,
                _fmod: (x, y) => x % y,
                _log: Math.log,
                _log10: Math.log10,
                _max_: Math.max,
                _min_: Math.min,
                _remainder: (x, y) => x - Math.round(x / y) * y,
                _pow: Math.pow,
                _round: Math.fround,
                _sin: Math.sin,
                _sqrt: Math.sqrt,
                _tan: Math.tan,
                _acosh: Math.acosh,
                _asinh: Math.asinh,
                _atanh: Math.atanh,
                _cosh: Math.cosh,
                _sinh: Math.sinh,
                _tanh: Math.tanh,
                
                table: new WebAssembly.Table({ initial: 0, element: "anyfunc" })
            }
        };
        try {
            const mixFile = await fetch("mixer32.wasm");
            const mixBuffer = await mixFile.arrayBuffer();
            const mixModule = await WebAssembly.instantiate(mixBuffer, mixObject);
            try {
                const dspFile = await fetch(this.name + ".wasm");
                const dspBuffer = await dspFile.arrayBuffer();
                const dspModule = await WebAssembly.instantiate(dspBuffer, importObject);
                try {
                    const effectFile = await fetch(this.name + "_effect.wasm");
                    const effectBuffer = await effectFile.arrayBuffer();
                    const effectModule = await WebAssembly.instantiate(effectBuffer, importObject);
                    this.node = this.getNode(mixModule.instance, dspModule.instance, effectModule.instance, memory, audioCtx, bufferSize, polyphony);
                    return this.node;
                } catch (e) {
                    this.log(e);
                    this.log("Faust " + this.name + "_effect cannot be loaded or compiled");
                    this.node = this.getNode(mixModule.instance, dspModule.instance, null, memory, audioCtx, bufferSize, polyphony);
                    return this.node;
                }
            } catch (e) {
                this.error(e);
                this.error("Faust " + this.name + " cannot be loaded or compiled");
            }
        } catch (e) {
            this.error(e);
            this.error("Faust mixer32 cannot be loaded or compiled");
        }
    }
    log(str) {
        this._log.push(str);
        if (this.debug) console.log(str);
    }
    error(str) {
        this._log.push(str);
        console.error(str);
    }
}

const dspName = "mydsp";

// Keep JSON parsed object
let json_object;
try {
    // eslint-disable-next-line no-undef
    const json = getJSONmydsp();
    json_object = JSON.parse(json);
} catch (e) {
    console.error("Error in JSON.parse: " + e);
}

// Keep JSON parsed object
let effect_json_object;
try {
    // eslint-disable-next-line no-undef
    const jsonEffect = typeof getJSONeffect === "undefined" ? null : getJSONeffect();
    effect_json_object = JSON.parse(jsonEffect);
} catch (e) {
    console.error("Error in JSON.parse: " + e);
}

const instance = new FaustWasm2ScriptProcessorPoly(dspName, json_object, effect_json_object);
// output to window or npm package module
if (typeof module === "undefined") {
    window[dspName + "Poly"] = instance;
} else {
    const exp = {};
    exp[dspName + "Poly"] = instance;
    module.exports = exp;
}

// Usage : mydspPoly.createDSP(audioCtx, 1024, 16).then(dsp => dsp.connect(audioCtx.destination));
