/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2025 GRAME, Centre National de Creation Musicale
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

'use strict';

let faust = globalThis.faust || {};

const fs = require('fs');

// Wrapper that loads a double-precision Faust WebAssembly module in Node.js
// and exposes the DSP through a class with a small runner harness.

class FaustDSP {
    /**
     * @param {*} context - Placeholder context (unused in this standalone wrapper).
     * @param {WebAssembly.Instance} instance - Instantiated WASM module.
     * @param {number} buffer_size - Audio block size.
     * @param {number} sample_rate - Sample rate.
     */
    constructor(context, instance, buffer_size, sample_rate) {
        this.context = context;
        this.instance = instance;
        this.buffer_size = buffer_size;
        this.sample_rate = sample_rate;

        this.output_handler = null;
        this.ins = null;
        this.outs = null;

        this.dspInChannnels = [];
        this.dspOutChannnels = [];

        const json_file_text = fs.readFileSync('DSP.json', 'utf8');
        this.json_object = JSON.parse(json_file_text);

        this.numIn = parseInt(this.json_object.inputs);
        this.numOut = parseInt(this.json_object.outputs);

        this.ptr_size = 8;
        this.sample_size = 8;  // double

        this.factory = instance.exports;

        this.HEAP = this.factory.memory.buffer;
        this.HEAP32 = new Int32Array(this.HEAP);
        this.HEAPF = new Float64Array(this.HEAP);

        this.outputs_timer = 5;
        this.outputs_items = [];
        this.inputs_items = [];
        this.buttons_items = [];
        this.default_values = [];

        this.audio_heap_ptr = parseInt(this.json_object.size);
        this.audio_heap_ptr_inputs = this.audio_heap_ptr;
        this.audio_heap_ptr_outputs = this.audio_heap_ptr_inputs + (this.numIn * this.ptr_size);

        this.audio_heap_inputs = this.audio_heap_ptr_outputs + (this.numOut * this.ptr_size);
        this.audio_heap_outputs = this.audio_heap_inputs + (this.numIn * buffer_size * this.sample_size);

        this.dsp = 0;
        this.pathTable = [];

        this.setup();
    }

    /**
     * Periodically forward bargraph outputs to the registered handler.
     */
    update_outputs() {
        if (this.outputs_items.length > 0 && this.output_handler && this.outputs_timer-- === 0) {
            this.outputs_timer = 5;
            for (let i = 0; i < this.outputs_items.length; i++) {
                this.output_handler(this.outputs_items[i], this.factory.getParamValue(this.dsp, this.pathTable[this.outputs_items[i]]));
            }
        }
    }

    /**
     * Copy inputs to DSP heap, invoke compute, and copy outputs back.
     * @param {Float64Array[]} inputs - Input channels from host.
     * @param {Float64Array[]} outputs - Output channels to fill.
     */
    computeAux(inputs, outputs) {
        let i;

        for (i = 0; i < this.numIn; i++) {
            const input = inputs[i];
            const dspInput = this.dspInChannnels[i];
            dspInput.set(input);
        }

        this.factory.compute(this.dsp, this.buffer_size, this.ins, this.outs);

        this.update_outputs();

        for (i = 0; i < this.numOut; i++) {
            const output = outputs[i];
            const dspOutput = this.dspOutChannnels[i];
            output.set(dspOutput);
        }
    }

    /**
     * Parse UI description JSON tree.
     * @param {Array} ui - UI description array.
     */
    parse_ui(ui) {
        for (let i = 0; i < ui.length; i++) {
            this.parse_group(ui[i]);
        }
    }

    /**
     * Parse a single UI group node.
     * @param {Object} group - Group node.
     */
    parse_group(group) {
        if (group.items) {
            this.parse_items(group.items);
        }
    }

    /**
     * Parse a list of UI items.
     * @param {Array} items - UI item list.
     */
    parse_items(items) {
        for (let i = 0; i < items.length; i++) {
            this.parse_item(items[i]);
        }
    }

    /**
     * Collect UI item metadata and populate path tables.
     * @param {Object} item - UI item node.
     */
    parse_item(item) {
        if (item.type === "vgroup"
            || item.type === "hgroup"
            || item.type === "tgroup") {
            this.parse_items(item.items);
        } else if (item.type === "hbargraph"
            || item.type === "vbargraph") {
            this.outputs_items.push(item.address);
            this.pathTable[item.address] = parseInt(item.index);
        } else if (item.type === "vslider"
            || item.type === "hslider"
            || item.type === "button"
            || item.type === "checkbox"
            || item.type === "nentry") {
            this.inputs_items.push(item.address);
            this.pathTable[item.address] = parseInt(item.index);
            if (item.type === "button") {
                this.buttons_items.push(item.address);
                this.default_values.push(0);
            } else if (item.type === "checkbox") {
                this.default_values.push(0);
            } else {
                this.default_values.push(parseFloat(item.init));
            }
        }
    }

    /**
     * Initialize heap pointers, channel views, parse UI, and initialize DSP.
     */
    setup() {
        let i;

        if (this.numIn > 0) {
            this.ins = this.audio_heap_ptr_inputs;
            for (i = 0; i < this.numIn; i++) {
                this.HEAP32[(this.ins >> 2) + i] = this.audio_heap_inputs + ((this.buffer_size * this.sample_size) * i);
            }

            const dspInChans = this.HEAP32.subarray(this.ins >> 2, (this.ins + this.numIn * this.ptr_size) >> 2);
            for (i = 0; i < this.numIn; i++) {
                this.dspInChannnels[i] = this.HEAPF.subarray(dspInChans[i] >> 3, (dspInChans[i] + this.buffer_size * this.sample_size) >> 3);
            }
        }

        if (this.numOut > 0) {
            this.outs = this.audio_heap_ptr_outputs;
            for (i = 0; i < this.numOut; i++) {
                this.HEAP32[(this.outs >> 2) + i] = this.audio_heap_outputs + ((this.buffer_size * this.sample_size) * i);
            }

            const dspOutChans = this.HEAP32.subarray(this.outs >> 2, (this.outs + this.numOut * this.ptr_size) >> 2);
            for (i = 0; i < this.numOut; i++) {
                this.dspOutChannnels[i] = this.HEAPF.subarray(dspOutChans[i] >> 3, (dspOutChans[i] + this.buffer_size * this.sample_size) >> 3);
            }
        }

        this.parse_ui(this.json_object.ui);
        this.factory.init(this.dsp, this.sample_rate);
    }

    /**
     * Get sample rate reported by the DSP.
     */
    getSampleRate() {
        return this.factory.getSampleRate(this.dsp);
    }

    /**
     * Get declared input channels.
     */
    getNumInputs() {
        return this.numIn;
    }

    /**
     * Get declared output channels.
     */
    getNumOutputs() {
        return this.numOut;
    }

    /**
     * Initialize DSP instance with a sample rate.
     * @param {number} sample_rate - Sample rate in Hz.
     */
    init(sample_rate) {
        this.factory.init(this.dsp, sample_rate);
    }

    /**
     * Initialize DSP instance state.
     * @param {number} sample_rate - Sample rate in Hz.
     */
    instanceInit(sample_rate) {
        this.factory.instanceInit(this.dsp, sample_rate);
    }

    /**
     * Push new constants to the DSP instance.
     * @param {number} sample_rate - Sample rate in Hz.
     */
    instanceConstants(sample_rate) {
        this.factory.instanceConstants(this.dsp, sample_rate);
    }

    /**
     * Reset UI-controlled parameters.
     */
    instanceResetUserInterface() {
        this.factory.instanceResetUserInterface(this.dsp);
    }

    /**
     * Clear DSP internal state.
     */
    instanceClear() {
        this.factory.instanceClear(this.dsp);
    }

    /**
     * Register a callback for bargraph outputs.
     * @param {Function} handler - Callback receiving (path, value).
     */
    setOutputParamHandler(handler) {
        this.output_handler = handler;
    }

    /**
     * Return the active bargraph callback.
     */
    getOutputParamHandler() {
        return this.output_handler;
    }

    /**
     * Set a parameter value by path.
     * @param {string} path - Parameter path.
     * @param {number} val - Value to set.
     */
    setParamValue(path, val) {
        this.factory.setParamValue(this.dsp, this.pathTable[path], val);
    }

    /**
     * Get a parameter value by path.
     * @param {string} path - Parameter path.
     * @returns {number} Current value.
     */
    getParamValue(path) {
        return this.factory.getParamValue(this.dsp, this.pathTable[path]);
    }

    /**
     * Get list of parameter paths.
     */
    getParams() {
        return this.inputs_items;
    }

    /**
     * Get list of button parameter paths.
     */
    getButtonsParams() {
        return this.buttons_items;
    }

    /**
     * Return raw JSON description.
     */
    getJSON() {
        return getJSONmydsp();
    }

    /**
     * Compute one audio block.
     * @param {Float64Array[]} inputs - Input channels.
     * @param {Float64Array[]} outputs - Output channels.
     */
    compute(inputs, outputs) {
        this.computeAux(inputs, outputs);
    }

    /**
     * Verify parameters match defaults.
     * @returns {boolean} True if all defaults match.
     */
    checkDefaults() {
        for (let i = 0; i < this.default_values.length; i++) {
            if (this.default_values[i] !== this.factory.getParamValue(this.dsp, this.pathTable[this.inputs_items[i]])) return false;
        }
        return true;
    }

    /**
     * Seed parameters with a fixed non-default value.
     */
    initRandom() {
        for (let i = 0; i < this.default_values.length; i++) {
            this.factory.setParamValue(this.dsp, this.pathTable[this.inputs_items[i]], 0.123456789);
        }
    }

    /**
     * Build the WebAssembly import object for the DSP.
     * @returns {Object} Import object for WebAssembly.instantiate.
     */
    static createImportObject() {
        return {
            env: {
                memoryBase: 0,
                tableBase: 0,

                // Integer version
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
                _fmodf: function (x, y) { return x % y; },
                _logf: Math.log,
                _log10f: Math.log10,
                _max_f: Math.max,
                _min_f: Math.min,
                _remainderf: function (x, y) { return x - Math.round(x / y) * y; },
                _powf: Math.pow,
                _roundf: Math.round,
                _sinf: Math.sin,
                _sqrtf: Math.sqrt,
                _tanf: Math.tan,
                _acosh: Math.acosh,
                _asinh: Math.asinh,
                _atanh: Math.atanh,
                _cosh: Math.cosh,
                _sinh: Math.sinh,
                _tanh: Math.tanh,
                _isnanf: Number.isNaN,
                _isinff: function (x) { return !isFinite(x); },
                _copysignf: function (x, y) { return Math.sign(x) === Math.sign(y) ? x : -x; },

                // Double version
                _acos: Math.acos,
                _asin: Math.asin,
                _atan: Math.atan,
                _atan2: Math.atan2,
                _ceil: Math.ceil,
                _cos: Math.cos,
                _exp: Math.exp,
                _floor: Math.floor,
                _fmod: function (x, y) { return x % y; },
                _log: Math.log,
                _log10: Math.log10,
                _max_: Math.max,
                _min_: Math.min,
                _remainder: function (x, y) { return x - Math.round(x / y) * y; },
                _pow: Math.pow,
                _round: Math.round,
                _sin: Math.sin,
                _sqrt: Math.sqrt,
                _tan: Math.tan,
                _acosh: Math.acosh,
                _asinh: Math.asinh,
                _atanh: Math.atanh,
                _cosh: Math.cosh,
                _sinh: Math.sinh,
                _tanh: Math.tanh,
                _isnan: Number.isNaN,
                _isinf: function (x) { return !isFinite(x); },
                _copysign: function (x, y) { return Math.sign(x) === Math.sign(y) ? x : -x; },

                table: new WebAssembly.Table({ initial: 0, element: 'anyfunc' })
            }
        };
    }
}
faust.mydsp = function (context, instance, buffer_size, sample_rate) {
    return new FaustDSP(context, instance, buffer_size, sample_rate);
};

// Helper functions

/**
 * Allocate input/output buffers for the test harness.
 * @param {number} ins - Number of input channels.
 * @param {number} outs - Number of output channels.
 * @param {number} buffer_size - Block size.
 */
const create = function (ins, outs, buffer_size) {
    for (let i = 0; i < ins; i++) {
        inputs.push(new Float64Array(buffer_size));
    }
    for (let i = 0; i < outs; i++) {
        outputs.push(new Float64Array(buffer_size));
    }
}

/**
 * Fill inputs with an impulse for initial block.
 * @param {number} ins - Number of input channels.
 * @param {number} buffer_size - Block size.
 */
const impulse = function (ins, buffer_size) {
    for (let i = 0; i < ins; i++) {
        inputs[i][0] = 1.0;
        for (let f = 1; f < buffer_size; f++) {
            inputs[i][f] = 0.0;
        }
    }
}

/**
 * Zero input buffers.
 * @param {number} ins - Number of input channels.
 * @param {number} buffer_size - Block size.
 */
const zero = function (ins, buffer_size) {
    for (let i = 0; i < ins; i++) {
        for (let f = 0; f < buffer_size; f++) {
            inputs[i][f] = 0.0;
        }
    }
}

/**
 * Guard tiny values against rounding noise.
 * @param {number} f - Sample value.
 * @returns {number} Normalized value.
 */
const normalize = function (f) {
    return (Math.abs(f) < 0.000001) ? 0.0 : f;
}

/**
 * Apply a button value to all button params.
 * @param {Object} dsp - DSP instance.
 * @param {number} value - Value to set.
 */
const setButtons = function (dsp, value) {
    const buttons = dsp.getButtonsParams();
    for (let i = 0; i < buttons.length; i++) {
        dsp.setParamValue(buttons[i], value);
    }
}

const buffer_size = 64;
const sample_rate = 44100;
const inputs = [];
const outputs = [];
let nbsamples = 15000;
let linenum = 0;
let run = 0;
let control_data;

/**
 * Instantiate DSP, perform validation, and print output samples.
 * @param {WebAssembly.Instance} instance - Instantiated DSP module.
 * @param {number} buffer_size - Block size.
 */
function startDSP(instance, buffer_size) {
    // Creates DSP and buffers
    const DSP = faust.mydsp(null, instance, buffer_size, sample_rate);
    create(DSP.getNumInputs(), DSP.getNumOutputs(), buffer_size);

    // Write output file header
    console.log("number_of_inputs : ", DSP.getNumInputs());
    console.log("number_of_outputs : ", DSP.getNumOutputs());
    console.log("number_of_frames : ", nbsamples);

    // Check getSampleRate
    if (DSP.getSampleRate() !== sample_rate) {
        console.error("ERROR in getSampleRate");
        process.exit(1);
    }

    // Check setParamValue/getParamValue
    const path_table = DSP.getParams();
    for (let i = 0; i < path_table.length; i++) {
        DSP.setParamValue(path_table[i], 0.1234);
        if (DSP.getParamValue(path_table[i]) !== 0.1234) {
            console.error("ERROR in setParamValue/getParamValue for " + path_table[i] + " " + DSP.getParamValue(path_table[i]));
            process.exit(1);
        }
    }

    // Check default after 'instanceResetUserInterface'
    DSP.initRandom();
    DSP.instanceResetUserInterface();
    if (!DSP.checkDefaults()) {
        console.error("ERROR in checkDefaults after 'instanceResetUserInterface'");
        process.exit(1);
    }

    // Check default after 'instanceInit'
    DSP.initRandom();
    DSP.instanceInit();
    if (!DSP.checkDefaults()) {
        console.error("ERROR in checkDefaults after 'instanceInit'");
        process.exit(1);
    }

    // Check default after 'init'
    DSP.initRandom();
    DSP.init(sample_rate);
    if (!DSP.checkDefaults()) {
        console.error("ERROR in checkDefaults after 'init'");
        process.exit(1);
    }

    DSP.init(sample_rate);

    // Read control parameters
    try {
        control_data = fs.readFileSync('mydsprc', 'utf8');
        const lines = control_data.split('\n');
        for (let line = 0; line < lines.length; line++) {
            const param = lines[line].split(' ');
            DSP.setParamValue('/' + param[1], parseFloat(param[0]));
        }
    } catch (e) { }

    // Compute samples and write output file
    while (nbsamples > 0) {
        if (run === 0) {
            impulse(DSP.getNumInputs(), buffer_size);
            setButtons(DSP, 1.0);
        }
        if (run === 1) {
            zero(DSP.getNumInputs(), buffer_size);
            setButtons(DSP, 0.0);
        }
        const nFrames = Math.min(buffer_size, nbsamples);
        DSP.compute(inputs, outputs);
        run++;
        for (let i = 0; i < nFrames; i++) {
            let line = (linenum++) + " : ";
            for (let c = 0; c < DSP.getNumOutputs(); c++) {
                const f = normalize(outputs[c][i]);
                line = line + f + " ";
            }
            console.log(line);
        }
        nbsamples -= nFrames;
    }
}

/**
 * Convert Node.js Buffer to Uint8Array.
 * @param {Buffer} buf - Input buffer.
 * @returns {Uint8Array} Converted array.
 */
function toUint8Array(buf) {
    const res = new Uint8Array(buf.length);
    for (let i = 0; i < buf.length; ++i) {
        res[i] = buf[i];
    }
    return res;
}

/**
 * Minimal runner to instantiate the DSP WASM and execute startDSP.
 */
class FaustDSPRunner {
    /**
     * @param {ArrayBuffer} wasmBytes - WASM binary bytes.
     * @param {number} bufferSize - Block size.
     */
    constructor(wasmBytes, bufferSize) {
        this.wasmBytes = wasmBytes;
        this.imports = FaustDSP.createImportObject();
        this.bufferSize = bufferSize;
    }

    /**
     * Instantiate the WASM module with the DSP imports.
     * @returns {Promise<WebAssembly.Instance>} Instantiated module.
     */
    async createInstance() {
        const { instance } = await WebAssembly.instantiate(this.wasmBytes, this.imports);
        return instance;
    }

    /**
     * Instantiate and run the test harness, exiting on error.
     */
    async start() {
        try {
            const instance = await this.createInstance();
            startDSP(instance, this.bufferSize);
        } catch (error) {
            console.error(error);
            console.error("WebAssembly instantiation failed");
            process.exit(1);
        }
    }
}

// Main code
if (require.main === module) {
    const response = toUint8Array(fs.readFileSync('DSP.wasm'));
    const bytes = response.buffer;

    const dspRunner = new FaustDSPRunner(bytes, buffer_size);
    dspRunner.start();
}
