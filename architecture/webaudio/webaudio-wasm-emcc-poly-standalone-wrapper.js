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

const faust_module = FaustModule(); // Emscripten generated module

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
     * @param {{ debug: boolean, [key: string]: any }} options - compile options
     */
    constructor(dspName, options) {
        this.name = dspName;
        this._log = [];
        this.node;
        this.debug = false || (typeof options === "object" && options.debug);
    }
    
    async asyncForEach(array, callback) {
        for (let index = 0; index < array.length; index++) {
            await callback(array[index], index, array);
        }
    }
    
    async loadAudioFiles(json) {
        
        // Get filenames in JSON
        let json_object = JSON.parse(json);
        let soundfiles = [];
        let parse_ui = ui => ui.forEach(group => parse_group(group));
        let parse_group = group => group.items ? parse_items(group.items) : null;
        let parse_items = items => items.forEach(item => parse_item(item));
        let parse_item = item => { 
            if (item.type === "vgroup"
                || item.type === "hgroup"
                || item.type === "tgroup") {
                parse_items(item.items);
            } else if (item.type === "soundfile") {
                item.url.slice(1, -1).split(';').forEach(item => soundfiles.push(item));
            }
        }
        parse_ui(json_object.ui);
        
        // Load each file and save it in EMCC local FS
        await this.asyncForEach(soundfiles, async name_aux => {
                                let name = name_aux.slice(1, -1);
                                console.log(name);
                                //const soundfile = await fetch(name, { mode: 'no-cors' });
                                const soundfile = await fetch(name);
                                const data = await soundfile.arrayBuffer();
                                let stream = faust_module.FS.open(name, 'w+');
                                let buf = new Uint8Array(data);
                                let res1 = faust_module.FS.write(stream, buf, 0, buf.length, 0);
                                faust_module.FS.close(stream);
                                });
    }

    /**
     * Constructor of Monophonic Faust DSP
     *
     * @param {WebAssembly.Instance} instance - the wasm instance
     * @param {AudioContext | webkitAudioContext} audioCtx - the Web Audio context
     * @param {number} bufferSize - the buffer_size in frames
     * @param {number} polyphony - the number of polyphonic voices
     *
     * @returns {ScriptProcessorNode} a valid WebAudio ScriptProcessorNode object or null
     */
    getNode(instance, audioCtx, bufferSize) {
    
        this.json = instance.getJSON();
        this.json_object = JSON.parse(this.json);

        console.log("getNumInputs " + instance.getNumInputs());
        console.log("getNumOutputs " + instance.getNumOutputs());
        
        let sp;
        const inputs = parseInt(this.json_object.inputs);
        const outputs = parseInt(this.json_object.outputs);
        try {
            sp = audioCtx.createScriptProcessor(bufferSize, inputs, outputs);
        } catch (e) {
            this.error("Error in createScriptProcessor: " + e);
            return null;
        }
        
        sp.output_handler = null;
        sp.ins = null;
        sp.outs = null;
        sp.mixing = null;
        sp.compute_handler = null;
    
        sp.dspInChannnels = [];
        sp.dspOutChannnels = [];
    
        sp.fPitchwheelLabel = [];
        sp.fCtrlLabel = new Array(128).fill(null).map(() => []);

        sp.numIn = inputs;
        sp.numOut = outputs;
    
        this.log(sp.numIn);
        this.log(sp.numOut);
    
        // Memory allocator
        sp.ptr_size = 4;
        sp.sample_size = 4;
    
        sp.instance = instance;
    
        // bargraph
        sp.outputs_timer = 5;
        sp.outputs_items = [];
    
        // input items
        sp.inputs_items = [];
    
        sp.update_outputs = () => {
            if (sp.outputs_items.length > 0 && sp.output_handler && sp.outputs_timer-- === 0) {
                sp.outputs_timer = 5;
                sp.outputs_items.forEach(item => sp.output_handler(item, sp.instance.getParamValue(sp.pathTable[item])));
            }
        };

        sp.compute = e => {
            // Read inputs
            for (let i = 0; i < sp.numIn; i++) { 
                const input = e.inputBuffer.getChannelData(i);
                const dspInput = sp.dspInChannnels[i];
                dspInput.set(input);
            }
            // Possibly call an externally given callback (for instance to synchronize playing a MIDIFile...)
            if (sp.compute_handler) sp.compute_handler(bufferSize);
            // Compute
            try {
            	sp.instance.compute(bufferSize, sp.ins, sp.outs); 
            } catch(e) {
            	console.log("ERROR in compute (" + e + ")");
            }
            // Update bargraph
            sp.update_outputs();
            // Write outputs
            for (let i = 0; i < sp.numOut; i++) { 
                const output = e.outputBuffer.getChannelData(i);
                const dspOutput = sp.dspOutChannnels[i];
                output.set(dspOutput);
            }
        };

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
            } else if (item.type === "vslider" || item.type === "hslider" || item.type === "button"
                    || item.type === "checkbox" || item.type === "nentry") {
                // Keep inputs adresses
                sp.inputs_items.push(item.address);
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
        
        // Setup web audio context
        sp.initAux = () => {
            this.log("buffer_size " + bufferSize);
            sp.onaudioprocess = sp.compute;
            
            if (sp.numIn > 0) {
                sp.ins = faust_module._malloc(sp.numIn * sp.ptr_size);
                for (let i = 0; i < sp.numIn; i++) {
                    faust_module.HEAP32[(sp.ins >> 2) + i] = faust_module._malloc(bufferSize * sp.sample_size);
                }
                // Prepare Ins buffer tables
                const dspInChans = faust_module.HEAP32.subarray(sp.ins >> 2, (sp.ins + sp.numIn * sp.ptr_size) >> 2);
                for (let i = 0; i < sp.numIn; i++) {
                    sp.dspInChannnels[i] = faust_module.HEAPF32.subarray(dspInChans[i] >> 2, (dspInChans[i] + bufferSize * sp.sample_size) >> 2);
                }
            } else {
                // Null pointer for C++ side
                sp.ins = 0;
            }

            if (sp.numOut > 0) {
                sp.outs = faust_module._malloc(sp.numOut * sp.ptr_size);
                for (let i = 0; i < sp.numOut; i++) {
                    faust_module.HEAP32[(sp.outs >> 2) + i] = faust_module._malloc(bufferSize * sp.sample_size);
                }
                // Prepare Out buffer tables
                const dspOutChans = faust_module.HEAP32.subarray(sp.outs >> 2, (sp.outs + sp.numOut * sp.ptr_size) >> 2);
                for (let i = 0; i < sp.numOut; i++) {
                    sp.dspOutChannnels[i] = faust_module.HEAPF32.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + bufferSize * sp.sample_size) >> 2);
                }
            } else {
                // Null pointer for C++ side
                sp.outs = 0;
            }
            
    	    // Parse JSON UI part
            sp.parse_ui(this.json_object.ui);
            // Init DSP
            sp.instance.init(audioCtx.sampleRate);
        }
        
        // Public API
        
        /**
         * Destroy the node, deallocate resources.
         */
    	sp.destroy = () => {}
        
        sp.getSampleRate = () => audioCtx.sampleRate;   // Return current sample rate
        sp.getNumInputs = () => sp.numIn;               // Return instance number of audio inputs.
        sp.getNumOutputs = () => sp.numOut;             // Return instance number of audio outputs.
        
        /**
         * Global init, doing the following initialization:
         * - static tables initialization
         * - call 'instanceInit': constants and instance state initialisation
         *
         * @param {number} sampleRate - the sampling rate in Hertz
         */
        sp.init = sampleRate => sp.instance.init(sampleRate);
        
        /**
         * Init instance state.
         *
         * @param {number} sampleRate - the sampling rate in Hertz
         */
        sp.instanceInit = sampleRate => sp.instance.instanceInit(sampleRate);
        
        /**
        * Init instance constant state.
        *
        * @param {number} sampleRate - the sampling rate in Hertz
        */
        sp.instanceConstants = sampleRate => sp.instance.instanceConstants(sampleRate);
        
        /* Init default control parameters values. */
        sp.instanceResetUserInterface = () => sp.instance.instanceResetUserInterface();
        
        /* Init instance state (delay lines...).*/
        sp.instanceClear = () => sp.instance.instanceClear();
     
        /**
         * Trigger the Meta handler with instance specific calls to 'declare' (key, value) metadata.
         *
         * @param {{ declare: (string, any) => any }} handler - the Meta handler as a 'declare' function of type (key, value)
         */
        sp.metadata = handler => {
            if (this.json_object.meta) {
                this.json_object.meta.forEach(meta => handler.declare(Object.keys(meta)[0], Object.values(meta)[0]));
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
         
        sp.keyOn = (channel, pitch, velocity) => { sp.instance.keyOn(channel, pitch, velocity); }
        /**
         * De-instantiates a polyphonic voice.
         *
         * @param {number} channel - the MIDI channel (0..15, not used for now)
         * @param {number} pitch - the MIDI pitch (0..127)
         * @param {number} velocity - the MIDI velocity (0..127)
         */
         
        sp.keyOff = (channel, pitch, velocity) => { sp.instance.keyOff(channel, pitch, velocity); }
        /**
         * Gently terminates all the active voices. TODO
         */
         
        sp.allNotesOff = () => {}
        /**
         * Control change
         *
         * @param {number} channel - the MIDI channel (0..15, not used for now)
         * @param {number} ctrl - the MIDI controller number (0..127)
         * @param {number} value - the MIDI controller value (0..127)
         */
         
        sp.ctrlChange = (channel, ctrl, value) => { sp.instance.ctrlChange(channel, ctrl, value); }
        /**
         * PitchWeel
         *
         * @param {number} channel - the MIDI channel (0..15, not used for now)
         * @param {number} value - the MIDI controller value (-1..1)
         */
         
        sp.pitchWheel = (channel, wheel) => { sp.instance.pitchWheel(channel, wheel); }
       
        /**
         * Set control value.
         *
         * @param {string} path - the path to the wanted control (retrieved using 'getParams' method)
         * @param {number} val - the float value for the wanted parameter
         */
         
        sp.setParamValue = (path, val) => { sp.instance.setParamValue(path, parseFloat(val)); }
        /**
         * Get control value.
         *
         * @param {string} path - the path to the wanted control (retrieved using 'controls' method)
         *
         * @return {number} the float value
         */
         
        sp.getParamValue = path => { return sp.instance.getParamValue(path); }
        /**
         * Get the table of all input parameters paths.
         *
         * @return {object} the table of all input parameter paths.
         */
         
        sp.getParams = () => sp.inputs_items;
        /**
         * Get DSP JSON description with its UI and metadata
         *
         * @return {string} DSP JSON description
         */
         
        sp.getJSON = () => { return this.json; }
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
    
        faust_module.faust = faust_module.faust || {};
        faust_module.faust.wasm_instance = faust_module.faust.wasm_instance || [];

        const wasm_file = await fetch(this.name + ".wasm");
        const wasm_buffer = await wasm_file.arrayBuffer();
        const json = faust_module.wasm_dsp_factory.extractJSON(wasm_buffer);

        let wasm_effect_file = null;
        let wasm_effect_buffer = null;
        let json_effect = null;

        wasm_effect_file = await fetch(this.name + "_effect.wasm");
        if (wasm_effect_file.ok) {
            wasm_effect_buffer = await wasm_effect_file.arrayBuffer();
            json_effect = faust_module.wasm_dsp_factory.extractJSON(wasm_effect_buffer);
        }

        await this.loadAudioFiles(json);
        
        const importObject = {
            env: {
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
                
                memory : faust_module.faust.memory,
                
                table: new WebAssembly.Table({ initial: 0, element: "anyfunc" })
            }
        };

        const wasm_instance = await WebAssembly.instantiate(wasm_buffer, importObject);
        faust_module.faust.wasm_instance.push(wasm_instance.instance);	 	
        const factory = faust_module.wasm_dsp_factory.createWasmDSPFactory(0, json);

        let factory_effect = null;
        if (wasm_effect_buffer) {
            const wasm_effect_instance = await WebAssembly.instantiate(wasm_effect_buffer, importObject);
            faust_module.faust.wasm_instance.push(wasm_effect_instance.instance);
            factory_effect = faust_module.wasm_dsp_factory.createWasmDSPFactory(1, json_effect);
        }

        const factory_poly = new faust_module.wasm_dsp_poly_factory(factory, factory_effect);
        return this.getNode(factory_poly.createPolyDSPInstance(polyphony, true, true), audioCtx, bufferSize);
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
const instance = new FaustWasm2ScriptProcessorPoly(dspName);

// output to window or npm package module
if (typeof module === "undefined") {
    window[dspName + "Poly"] = instance;
} else {
    const exp = {};
    exp[dspName + "Poly"] = instance;
    module.exports = exp;
}

// Usage : mydspPoly.createDSP(audioCtx, 1024, 16).then(dsp => dsp.connect(audioCtx.destination));
