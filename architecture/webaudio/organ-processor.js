
/*
Code generated with Faust version 2.63.0
Compilation options: -lang wasm-eb -ct 1 -cn organ -es 1 -mcd 16 -single -ftz 2 
*/

function getJSONorgan() {
    return '{"name": "organ","filename": "organ.dsp","version": "2.63.0","compile_options": "-lang wasm-eb -ct 1 -cn organ -es 1 -mcd 16 -single -ftz 2","library_list": ["/usr/local/share/faust/stdfaust.lib","/usr/local/share/faust/maths.lib","/usr/local/share/faust/platform.lib"],"include_pathnames": ["/usr/local/share/faust","/usr/local/share/faust","/usr/share/faust",".","/Documents/faust-github-faust2/architecture/webaudio"],"size": 64,"inputs": 0,"outputs": 1,"meta": [ { "compile_options": "-lang wasm-eb -ct 1 -cn organ -es 1 -mcd 16 -single -ftz 2" },{ "filename": "organ.dsp" },{ "maths.lib/author": "GRAME" },{ "maths.lib/copyright": "GRAME" },{ "maths.lib/license": "LGPL with exception" },{ "maths.lib/name": "Faust Math Library" },{ "maths.lib/version": "2.6" },{ "name": "organ" },{ "platform.lib/name": "Generic Platform Library" },{ "platform.lib/version": "0.3" }],"ui": [ {"type": "vgroup","label": "organ","items": [ {"type": "hslider","label": "freq","shortname": "freq","address": "/organ/freq","index": 28,"meta": [{ "unit": "Hz" }],"init": 440,"min": 20,"max": 20000,"step": 1},{"type": "hslider","label": "gain","shortname": "gain","address": "/organ/gain","index": 8,"init": 0.5,"min": 0,"max": 10,"step": 0.01},{"type": "button","label": "gate","shortname": "gate","address": "/organ/gate","index": 4},{"type": "hslider","label": "volume","shortname": "volume","address": "/organ/volume","index": 0,"init": 0.5,"min": 0,"max": 1,"step": 0.01}]}]}';
}
function getBase64Codeorgan() { return "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bC9zaGFyZS9mYXVzdCIsIi91c3Ivc2hhcmUvZmF1c3QiLCIuIiwiL0RvY3VtZW50cy9mYXVzdC1naXRodWItZmF1c3QyL2FyY2hpdGVjdHVyZS93ZWJhdWRpbyJdLCJzaXplIjogNjQsImlucHV0cyI6IDAsIm91dHB1dHMiOiAxLCJtZXRhIjogWyB7ICJjb21waWxlX29wdGlvbnMiOiAiLWxhbmcgd2FzbS1lYiAtY3QgMSAtY24gb3JnYW4gLWVzIDEgLW1jZCAxNiAtc2luZ2xlIC1mdHogMiIgfSx7ICJmaWxlbmFtZSI6ICJvcmdhbi5kc3AiIH0seyAibWF0aHMubGliL2F1dGhvciI6ICJHUkFNRSIgfSx7ICJtYXRocy5saWIvY29weXJpZ2h0IjogIkdSQU1FIiB9LHsgIm1hdGhzLmxpYi9saWNlbnNlIjogIkxHUEwgd2l0aCBleGNlcHRpb24iIH0seyAibWF0aHMubGliL25hbWUiOiAiRmF1c3QgTWF0aCBMaWJyYXJ5IiB9LHsgIm1hdGhzLmxpYi92ZXJzaW9uIjogIjIuNiIgfSx7ICJuYW1lIjogIm9yZ2FuIiB9LHsgInBsYXRmb3JtLmxpYi9uYW1lIjogIkdlbmVyaWMgUGxhdGZvcm0gTGlicmFyeSIgfSx7ICJwbGF0Zm9ybS5saWIvdmVyc2lvbiI6ICIwLjMiIH1dLCJ1aSI6IFsgeyJ0eXBlIjogInZncm91cCIsImxhYmVsIjogIm9yZ2FuIiwiaXRlbXMiOiBbIHsidHlwZSI6ICJoc2xpZGVyIiwibGFiZWwiOiAiZnJlcSIsInNob3J0bmFtZSI6ICJmcmVxIiwiYWRkcmVzcyI6ICIvb3JnYW4vZnJlcSIsImluZGV4IjogMjgsIm1ldGEiOiBbeyAidW5pdCI6ICJIeiIgfV0sImluaXQiOiA0NDAsIm1pbiI6IDIwLCJtYXgiOiAyMDAwMCwic3RlcCI6IDF9LHsidHlwZSI6ICJoc2xpZGVyIiwibGFiZWwiOiAiZ2FpbiIsInNob3J0bmFtZSI6ICJnYWluIiwiYWRkcmVzcyI6ICIvb3JnYW4vZ2FpbiIsImluZGV4IjogOCwiaW5pdCI6IDAuNSwibWluIjogMCwibWF4IjogMTAsInN0ZXAiOiAwLjAxfSx7InR5cGUiOiAiYnV0dG9uIiwibGFiZWwiOiAiZ2F0ZSIsInNob3J0bmFtZSI6ICJnYXRlIiwiYWRkcmVzcyI6ICIvb3JnYW4vZ2F0ZSIsImluZGV4IjogNH0seyJ0eXBlIjogImhzbGlkZXIiLCJsYWJlbCI6ICJ2b2x1bWUiLCJzaG9ydG5hbWUiOiAidm9sdW1lIiwiYWRkcmVzcyI6ICIvb3JnYW4vdm9sdW1lIiwiaW5kZXgiOiAwLCJpbml0IjogMC41LCJtaW4iOiAwLCJtYXgiOiAxLCJzdGVwIjogMC4wMX1dfV19"; }

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
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

function getBase64Mixer() { return "AGFzbQEAAAABj4CAgAACYAN/f38AYAR/f39/AX0CkoCAgAABBm1lbW9yeQZtZW1vcnkCAAIDg4CAgAACAAEHmoCAgAACC2NsZWFyT3V0cHV0AAAIbWl4Vm9pY2UAAQqKgoCAAALigICAAAEDfwJAQQAhBQNAAkAgAiAFQQJ0aigCACEDQQAhBANAAkAgAyAEQQJ0akMAAAAAOAIAIARBAWohBCAEIABIBEAMAgUMAQsACwsgBUEBaiEFIAUgAUgEQAwCBQwBCwALCwsLnYGAgAACBH8DfQJ9QQAhB0MAAAAAIQgDQAJAQQAhBiACIAdBAnRqKAIAIQQgAyAHQQJ0aigCACEFA0ACQCAEIAZBAnRqKgIAIQkgCCAJi5chCCAFIAZBAnRqKgIAIQogBSAGQQJ0aiAKIAmSOAIAIAZBAWohBiAGIABIBEAMAgUMAQsACwsgB0EBaiEHIAcgAUgEQAwCBQwBCwALCyAIDwsL"; }

// Polyphonic Faust DSP
class organPolyProcessor extends AudioWorkletProcessor {

    // JSON parsing functions
    static parse_ui(ui, obj, callback) {
        for (var i = 0; i < ui.length; i++) {
            organPolyProcessor.parse_group(ui[i], obj, callback);
        }
    }

    static parse_group(group, obj, callback) {
        if (group.items) {
            organPolyProcessor.parse_items(group.items, obj, callback);
        }
    }

    static parse_items(items, obj, callback) {
        for (var i = 0; i < items.length; i++) {
            callback(items[i], obj, callback);
        }
    }

    static parse_item1(item, obj, callback) {
        if (item.type === "vgroup"
            || item.type === "hgroup"
            || item.type === "tgroup") {
            organPolyProcessor.parse_items(item.items, obj, callback);
        } else if (item.type === "hbargraph"
            || item.type === "vbargraph") {
            // Nothing
        } else if (item.type === "vslider"
            || item.type === "hslider"
            || item.type === "button"
            || item.type === "checkbox"
            || item.type === "nentry") {
            obj.push({
                name: item.address,
                defaultValue: item.init,
                minValue: item.min,
                maxValue: item.max
            });
        }
    }

    static parse_item2(item, obj, callback) {
        if (item.type === "vgroup"
            || item.type === "hgroup"
            || item.type === "tgroup") {
            organPolyProcessor.parse_items(item.items, obj, callback);
        } else if (item.type === "hbargraph"
            || item.type === "vbargraph") {
            // Keep bargraph adresses
            obj.outputs_items.push(item.address);
            obj.pathTable[item.address] = parseInt(item.index);
        } else if (item.type === "vslider"
            || item.type === "hslider"
            || item.type === "button"
            || item.type === "checkbox"
            || item.type === "nentry") {
            // Keep inputs adresses
            obj.inputs_items.push(item.address);
            obj.pathTable[item.address] = parseInt(item.index);
            if (item.meta !== undefined) {
                for (var i = 0; i < item.meta.length; i++) {
                    if (item.meta[i].midi !== undefined) {
                        if (item.meta[i].midi.trim() === "pitchwheel") {
                            obj.fPitchwheelLabel.push({
                                path: item.address,
                                min: parseFloat(item.min),
                                max: parseFloat(item.max)
                            });
                        } else if (item.meta[i].midi.trim().split(" ")[0] === "ctrl") {
                            obj.fCtrlLabel[parseInt(item.meta[i].midi.trim().split(" ")[1])]
                                .push({
                                    path: item.address,
                                    min: parseFloat(item.min),
                                    max: parseFloat(item.max)
                                });
                        }
                    }
                }
            }
        }
    }

    static b64ToUint6(nChr) {
        return nChr > 64 && nChr < 91 ?
            nChr - 65
            : nChr > 96 && nChr < 123 ?
                nChr - 71
                : nChr > 47 && nChr < 58 ?
                    nChr + 4
                    : nChr === 43 ?
                        62
                        : nChr === 47 ?
                            63
                            :
                            0;
    }

    static atob(sBase64, nBlocksSize) {
        if (typeof atob === 'function') {
            return atob(sBase64);
        } else {

            var sB64Enc = sBase64.replace(/[^A-Za-z0-9\+\/]/g, "");
            var nInLen = sB64Enc.length;
            var nOutLen = nBlocksSize ? Math.ceil((nInLen * 3 + 1 >> 2) / nBlocksSize) * nBlocksSize : nInLen * 3 + 1 >> 2;
            var taBytes = new Uint8Array(nOutLen);

            for (var nMod3, nMod4, nUint24 = 0, nOutIdx = 0, nInIdx = 0; nInIdx < nInLen; nInIdx++) {
                nMod4 = nInIdx & 3;
                nUint24 |= organPolyProcessor.b64ToUint6(sB64Enc.charCodeAt(nInIdx)) << 18 - 6 * nMod4;
                if (nMod4 === 3 || nInLen - nInIdx === 1) {
                    for (nMod3 = 0; nMod3 < 3 && nOutIdx < nOutLen; nMod3++, nOutIdx++) {
                        taBytes[nOutIdx] = nUint24 >>> (16 >>> nMod3 & 24) & 255;
                    }
                    nUint24 = 0;
                }
            }
            return taBytes.buffer;
        }
    }

    static remap(v, mn0, mx0, mn1, mx1) {
        return (1.0 * (v - mn0) / (mx0 - mn0)) * (mx1 - mn1) + mn1;
    }

    static get parameterDescriptors() {
        // Analyse JSON to generate AudioParam parameters
        var params = [];

        // Add instrument parameters
        organPolyProcessor.parse_ui(JSON.parse(getJSONorgan()).ui, params, organPolyProcessor.parse_item1);

        // Possibly add effect parameters
        if (typeof (getJSONeffect) !== "undefined") {
            organPolyProcessor.parse_ui(JSON.parse(getJSONeffect()).ui, params, organPolyProcessor.parse_item1);
        }
        return params;
    }

    static createMemory(buffer_size, polyphony) {
        // Memory allocator
        var ptr_size = 4;
        var sample_size = 4;

        function pow2limit(x) {
            var n = 65536; // Minimum = 64 kB
            while (n < x) { n = 2 * n; }
            return n;
        }

        var json_object = null;
        try {
            json_object = JSON.parse(getJSONorgan());
        } catch (e) {
            return null;
        }

        var effect_json_object_size = 0;
        if (typeof (getJSONeffect) !== "undefined") {
            var effect_json_object = null;
            try {
                effect_json_object = JSON.parse(getJSONeffect());
                effect_json_object_size = parseInt(effect_json_object.size);
            } catch (e) {
                faust.error_msg = "Error in JSON.parse: " + e;
                return null;
            }
        }

        var memory_size = pow2limit(effect_json_object_size + parseInt(json_object.size) * polyphony + ((parseInt(json_object.inputs) + parseInt(json_object.outputs) * 2) * (ptr_size + (buffer_size * sample_size)))) / 65536;
        memory_size = Math.max(2, memory_size); // As least 2
        return new WebAssembly.Memory({ initial: memory_size, maximum: memory_size });
    }

    constructor(options) {
        super(options);
        this.running = true;

        this.json_object = JSON.parse(getJSONorgan());
        if (typeof (getJSONeffect) !== "undefined") {
            this.effect_json_object = JSON.parse(getJSONeffect());
        }

        this.output_handler = function (path, value) { this.port.postMessage({ path: path, value: value }); };

        this.debug = false;

        this.ins = null;
        this.outs = null;
        this.mixing = null;
        this.compute_handler = null;

        this.dspInChannnels = [];
        this.dspOutChannnels = [];

        this.fFreqLabel = [];
        this.fGateLabel = [];
        this.fGainLabel = [];
        this.fKeyFun = null;
        this.fVelFun = null;
        this.fDate = 0;

        this.fPitchwheelLabel = [];
        this.fCtrlLabel = new Array(128);
        for (var i = 0; i < this.fCtrlLabel.length; i++) { this.fCtrlLabel[i] = []; }

        this.numIn = parseInt(this.json_object.inputs);
        this.numOut = parseInt(this.json_object.outputs);

        // Memory allocator
        this.ptr_size = 4;
        this.sample_size = 4;

        var wasm_memory = organPolyProcessor.createMemory(organPolyProcessor.buffer_size, options.processorOptions.polyphony);

        // Create Mixer
        this.mixerObject = { imports: { print: arg => console.log(arg) } }
        this.mixerObject["memory"] = { "memory": wasm_memory };

        this.importObject = {
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
                _isnan: Number.isNaN,
                _isinf: function (x) { return !isFinite(x); },
                _copysign: function (x, y) { return Math.sign(x) === Math.sign(y) ? x : -x; },

                memory: wasm_memory,

                table: new WebAssembly.Table({ initial: 0, element: 'anyfunc' })
            }
        }

        // wasm mixer
        this.mixer = new WebAssembly.Instance(organPolyProcessor.wasm_mixer_module, this.mixerObject).exports;

        // wasm instance
        this.factory = new WebAssembly.Instance(organPolyProcessor.wasm_module, this.importObject).exports;

        // wasm effect
        this.effect = (organPolyProcessor.wasm_effect_module) ? new WebAssembly.Instance(organPolyProcessor.wasm_effect_module, this.importObject).exports : null;

        this.HEAP = wasm_memory.buffer;
        this.HEAP32 = new Int32Array(this.HEAP);
        this.HEAPF32 = new Float32Array(this.HEAP);

        // Warning: keeps a ref on HEAP in Chrome and prevent proper GC
        //console.log(this.HEAP);
        //console.log(this.HEAP32);
        //console.log(this.HEAPF32);

        // bargraph
        this.outputs_timer = 5;
        this.outputs_items = [];

        // input items
        this.inputs_items = [];

        // Start of HEAP index
        this.audio_heap_ptr = 0; // Fails when 0...

        // Setup pointers offset
        this.audio_heap_ptr_inputs = this.audio_heap_ptr;
        this.audio_heap_ptr_outputs = this.audio_heap_ptr_inputs + (this.numIn * this.ptr_size);
        this.audio_heap_ptr_mixing = this.audio_heap_ptr_outputs + (this.numOut * this.ptr_size);

        // Setup buffer offset
        this.audio_heap_inputs = this.audio_heap_ptr_mixing + (this.numOut * this.ptr_size);
        this.audio_heap_outputs = this.audio_heap_inputs + (this.numIn * organPolyProcessor.buffer_size * this.sample_size);
        this.audio_heap_mixing = this.audio_heap_outputs + (this.numOut * organPolyProcessor.buffer_size * this.sample_size);

        // Setup DSP voices offset
        this.dsp_start = this.audio_heap_mixing + (this.numOut * organPolyProcessor.buffer_size * this.sample_size);

        if (this.debug) {
            console.log(this.mixer);
            console.log(this.factory);
            console.log(this.effect);
        }

        // Start of DSP memory ('polyphony' DSP voices)
        this.polyphony = options.processorOptions.polyphony;
        this.dsp_voices = [];
        this.dsp_voices_state = [];
        this.dsp_voices_level = [];
        this.dsp_voices_date = [];

        this.kActiveVoice = 0;
        this.kFreeVoice = -1;
        this.kReleaseVoice = -2;
        this.kNoVoice = -3;

        this.pathTable = [];

        // Allocate table for 'setParamValue'
        this.value_table = [];

        for (var i = 0; i < this.polyphony; i++) {
            this.dsp_voices[i] = this.dsp_start + i * parseInt(this.json_object.size);
            this.dsp_voices_state[i] = this.kFreeVoice;
            this.dsp_voices_level[i] = 0;
            this.dsp_voices_date[i] = 0;
        }

        // Effect memory starts after last voice
        this.effect_start = this.dsp_voices[this.polyphony - 1] + parseInt(this.json_object.size);

        this.printMemory = function () {
            console.log("============== Memory layout ==============");
            console.log("json_object.size: " + this.json_object.size);

            console.log("audio_heap_ptr: " + this.audio_heap_ptr);

            console.log("audio_heap_ptr_inputs: " + this.audio_heap_ptr_inputs);
            console.log("audio_heap_ptr_outputs: " + this.audio_heap_ptr_outputs);
            console.log("audio_heap_ptr_mixing: " + this.audio_heap_ptr_mixing);

            console.log("audio_heap_inputs: " + this.audio_heap_inputs);
            console.log("audio_heap_outputs: " + this.audio_heap_outputs);
            console.log("audio_heap_mixing: " + this.audio_heap_mixing);

            console.log("dsp_start: " + this.dsp_start);
            for (var i = 0; i < this.polyphony; i++) {
                console.log("dsp_voices[i]: " + i + " " + this.dsp_voices[i]);
            }
            console.log("effect_start: " + this.effect_start);
        }

        this.getPlayingVoice = function (pitch) {
            var voice_playing = this.kNoVoice;
            var oldest_date_playing = Number.MAX_VALUE;

            for (var i = 0; i < this.polyphony; i++) {
                if (this.dsp_voices_state[i] === pitch) {
                    // Keeps oldest playing voice
                    if (this.dsp_voices_date[i] < oldest_date_playing) {
                        oldest_date_playing = this.dsp_voices_date[i];
                        voice_playing = i;
                    }
                }
            }

            return voice_playing;
        }

        // Always returns a voice
        this.allocVoice = function (voice) {
            // so that envelop is always re-initialized
            this.factory.instanceClear(this.dsp_voices[voice]);
            this.dsp_voices_date[voice] = this.fDate++;
            this.dsp_voices_state[voice] = this.kActiveVoice;
            return voice;
        }

        this.getFreeVoice = function () {
            for (var i = 0; i < this.polyphony; i++) {
                if (this.dsp_voices_state[i] === this.kFreeVoice) {
                    return this.allocVoice(i);
                }
            }

            var voice_release = this.kNoVoice;
            var voice_playing = this.kNoVoice;
            var oldest_date_release = Number.MAX_VALUE;
            var oldest_date_playing = Number.MAX_VALUE;

            // Scan all voices
            for (var i = 0; i < this.polyphony; i++) {
                // Try to steal a voice in kReleaseVoice mode...
                if (this.dsp_voices_state[i] === this.kReleaseVoice) {
                    // Keeps oldest release voice
                    if (this.dsp_voices_date[i] < oldest_date_release) {
                        oldest_date_release = this.dsp_voices_date[i];
                        voice_release = i;
                    }
                } else {
                    if (this.dsp_voices_date[i] < oldest_date_playing) {
                        oldest_date_playing = this.dsp_voices_date[i];
                        voice_playing = i;
                    }
                }
            }

            // Then decide which one to steal
            if (oldest_date_release != Number.MAX_VALUE) {
                if (this.debug) {
                    console.log("Steal release voice : voice_date = %d cur_date = %d voice = %d", this.dsp_voices_date[voice_release], this.fDate, voice_release);
                }
                return this.allocVoice(voice_release);
            } else if (oldest_date_playing != Number.MAX_VALUE) {
                if (this.debug) {
                    console.log("Steal playing voice : voice_date = %d cur_date = %d voice = %d", this.dsp_voices_date[voice_playing], this.fDate, voice_playing);
                }
                return this.allocVoice(voice_playing);
            } else {
                return this.kNoVoice;
            }
        }

        this.update_outputs = function () {
            if (this.outputs_items.length > 0 && this.output_handler && this.outputs_timer-- === 0) {
                this.outputs_timer = 5;
                for (var i = 0; i < this.outputs_items.length; i++) {
                    this.output_handler(this.outputs_items[i], this.factory.getParamValue(this.dsp, this.pathTable[this.outputs_items[i]]));
                }
            }
        }

        this.midiToFreq = function (note) {
            return 440.0 * Math.pow(2.0, (note - 69.0) / 12.0);
        }

        this.initAux = function () {
            var i;

            if (this.numIn > 0) {
                this.ins = this.audio_heap_ptr_inputs;
                for (i = 0; i < this.numIn; i++) {
                    this.HEAP32[(this.ins >> 2) + i] = this.audio_heap_inputs + ((organPolyProcessor.buffer_size * this.sample_size) * i);
                }

                // Prepare Ins buffer tables
                var dspInChans = this.HEAP32.subarray(this.ins >> 2, (this.ins + this.numIn * this.ptr_size) >> 2);
                for (i = 0; i < this.numIn; i++) {
                    this.dspInChannnels[i] = this.HEAPF32.subarray(dspInChans[i] >> 2, (dspInChans[i] + organPolyProcessor.buffer_size * this.sample_size) >> 2);
                }
            }

            if (this.numOut > 0) {
                // allocate memory for output and mixing arrays
                this.outs = this.audio_heap_ptr_outputs;
                this.mixing = this.audio_heap_ptr_mixing;

                for (i = 0; i < this.numOut; i++) {
                    this.HEAP32[(this.outs >> 2) + i] = this.audio_heap_outputs + ((organPolyProcessor.buffer_size * this.sample_size) * i);
                    this.HEAP32[(this.mixing >> 2) + i] = this.audio_heap_mixing + ((organPolyProcessor.buffer_size * this.sample_size) * i);
                }

                // Prepare Out buffer tables
                var dspOutChans = this.HEAP32.subarray(this.outs >> 2, (this.outs + this.numOut * this.ptr_size) >> 2);
                for (i = 0; i < this.numOut; i++) {
                    this.dspOutChannnels[i] = this.HEAPF32.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + organPolyProcessor.buffer_size * this.sample_size) >> 2);
                }
            }

            // Parse UI part
            organPolyProcessor.parse_ui(this.json_object.ui, this, organPolyProcessor.parse_item2);

            if (this.effect) {
                organPolyProcessor.parse_ui(this.effect_json_object.ui, this, organPolyProcessor.parse_item2);
            }

            // keep 'keyOn/keyOff' labels
            for (i = 0; i < this.inputs_items.length; i++) {
                if (this.inputs_items[i].endsWith("/gate")) {
                    this.fGateLabel.push(this.pathTable[this.inputs_items[i]]);
                } else if (this.inputs_items[i].endsWith("/freq")) {
                    this.fKeyFun = (pitch) => { return this.midiToFreq(pitch); };
                    this.fFreqLabel.push(this.pathTable[this.inputs_items[i]]);
                } else if (this.inputs_items[i].endsWith("/key")) {
                    this.fKeyFun = (pitch) => { return pitch; };
                    this.fFreqLabel.push(this.pathTable[this.inputs_items[i]]);
                } else if (this.inputs_items[i].endsWith("/gain")) {
                    this.fVelFun = (vel) => { return vel / 127.0; };
                    this.fGainLabel.push(this.pathTable[this.inputs_items[i]]);
                } else if (this.inputs_items[i].endsWith("/vel") || this.inputs_items[i].endsWith("/velocity")) {
                    this.fVelFun = (vel) => { return vel; };
                    this.fGainLabel.push(this.pathTable[this.inputs_items[i]]);
                }
            }

            // Init DSP voices
            for (i = 0; i < this.polyphony; i++) {
                this.factory.init(this.dsp_voices[i], sampleRate);  // 'sampleRate' is defined in AudioWorkletGlobalScope
            }

            // Init effect
            if (this.effect) {
                this.effect.init(this.effect_start, sampleRate);
            }

            // Print memory layout
            this.printMemory();
        }

        this.keyOn = function (channel, pitch, velocity) {
            var voice = this.getFreeVoice();
            if (this.debug) {
                console.log("keyOn voice %d", voice);
            }
            for (var i = 0; i < this.fFreqLabel.length; i++) {
                this.factory.setParamValue(this.dsp_voices[voice], this.fFreqLabel[i], this.fKeyFun(pitch));
            }
            for (var i = 0; i < this.fGateLabel.length; i++) {
                this.factory.setParamValue(this.dsp_voices[voice], this.fGateLabel[i], 1.0);
            }
            for (var i = 0; i < this.fGainLabel.length; i++) {
                this.factory.setParamValue(this.dsp_voices[voice], this.fGainLabel[i], this.fVelFun(velocity));
            }
            this.dsp_voices_state[voice] = pitch;
        }

        this.keyOff = function (channel, pitch, velocity) {
            var voice = this.getPlayingVoice(pitch);
            if (voice !== this.kNoVoice) {
                if (this.debug) {
                    console.log("keyOff voice %d", voice);
                }
                // No use of velocity for now...
                for (var i = 0; i < this.fGateLabel.length; i++) {
                    this.factory.setParamValue(this.dsp_voices[voice], this.fGateLabel[i], 0.0);
                }
                // Release voice
                this.dsp_voices_state[voice] = this.kReleaseVoice;
            } else {
                if (this.debug) {
                    console.log("Playing voice not found...");
                }
            }
        }

        this.allNotesOff = function () {
            for (var i = 0; i < this.polyphony; i++) {
                for (var j = 0; j < this.fGateLabel.length; j++) {
                    this.factory.setParamValue(this.dsp_voices[i], this.fGateLabel[j], 0.0);
                }
                this.dsp_voices_state[i] = this.kReleaseVoice;
            }
        }

        this.ctrlChange = function (channel, ctrl, value) {
            if (ctrl === 123 || ctrl === 120) {
                this.allNotesOff();
            }

            if (this.fCtrlLabel[ctrl] !== []) {
                for (var i = 0; i < this.fCtrlLabel[ctrl].length; i++) {
                    var path = this.fCtrlLabel[ctrl][i].path;
                    this.setParamValue(path, organPolyProcessor.remap(value, 0, 127, this.fCtrlLabel[ctrl][i].min, this.fCtrlLabel[ctrl][i].max));
                    if (this.output_handler) {
                        this.output_handler(path, this.getParamValue(path));
                    }
                }
            }
        }

        this.pitchWheel = function (channel, wheel) {
            for (var i = 0; i < this.fPitchwheelLabel.length; i++) {
                var pw = this.fPitchwheelLabel[i];
                this.setParamValue(pw.path, organPolyProcessor.remap(wheel, 0, 16383, pw.min, pw.max));
                if (this.output_handler) {
                    this.output_handler(pw.path, this.getParamValue(pw.path));
                }
            }
        }

        this.setParamValue = function (path, val) {
            if (this.effect && getJSONeffect().includes(path)) {
                this.effect.setParamValue(this.effect_start, this.pathTable[path], val);
            } else {
                for (var i = 0; i < this.polyphony; i++) {
                    this.factory.setParamValue(this.dsp_voices[i], this.pathTable[path], val);
                }
            }
        }

        this.getParamValue = function (path) {
            if (this.effect && getJSONeffect().includes(path)) {
                return this.effect.getParamValue(this.effect_start, this.pathTable[path]);
            } else {
                return this.factory.getParamValue(this.dsp_voices[0], this.pathTable[path]);
            }
        }

        // Init resulting DSP
        this.initAux();

        // Set message handler
        this.port.onmessage = this.handleMessage.bind(this);
    }

    handleMessage(event) {
        var msg = event.data;
        switch (msg.type) {
            // Generic MIDI message
            case "midi": this.midiMessage(msg.data); break;
            // Typed MIDI message
            case "keyOn": this.keyOn(msg.data[0], msg.data[1], msg.data[2]); break;
            case "keyOff": this.keyOff(msg.data[0], msg.data[1], msg.data[2]); break;
            case "ctrlChange": this.ctrlChange(msg.data[0], msg.data[1], msg.data[2]); break;
            case "pitchWheel": this.pitchWheel(msg.data[0], msg.data[1]); break;
            // Generic data message
            case "param": this.setParamValue(msg.key, msg.value); break;
            //case "patch": this.onpatch(msg.data); break;
            case "destroy": this.running = false; break;
        }
    }

    midiMessage(data) {
        var cmd = data[0] >> 4;
        var channel = data[0] & 0xf;
        var data1 = data[1];
        var data2 = data[2];

        if (channel === 9) {
            return;
        } else if (cmd === 8 || ((cmd === 9) && (data2 === 0))) {
            this.keyOff(channel, data1, data2);
        } else if (cmd === 9) {
            this.keyOn(channel, data1, data2);
        } else if (cmd === 11) {
            this.ctrlChange(channel, data1, data2);
        } else if (cmd === 14) {
            this.pitchWheel(channel, (data2 * 128.0 + data1));
        }
    }

    process(inputs, outputs, parameters) {
        var input = inputs[0];
        var output = outputs[0];

        // Check inputs
        if (this.numIn > 0 && (!input || !input[0] || input[0].length === 0)) {
            //console.log("Process input error");
            return true;
        }
        // Check outputs
        if (this.numOut > 0 && (!output || !output[0] || output[0].length === 0)) {
            //console.log("Process output error");
            return true;
        }

        // Copy inputs
        if (input !== undefined) {
            for (var chan = 0; chan < Math.min(this.numIn, input.length); ++chan) {
                var dspInput = this.dspInChannnels[chan];
                dspInput.set(input[chan]);
            }
        }

        // Possibly call an externally given callback (for instance to synchronize playing a MIDIFile...)
        if (this.compute_handler) {
            this.compute_handler(organPolyProcessor.buffer_size);
        }

        // First clear the outputs
        this.mixer.clearOutput(organPolyProcessor.buffer_size, this.numOut, this.outs);

        // Compute all running voices
        try {
            for (var i = 0; i < this.polyphony; i++) {
                if (this.dsp_voices_state[i] != this.kFreeVoice) {
                    // Compute voice
                    this.factory.compute(this.dsp_voices[i], organPolyProcessor.buffer_size, this.ins, this.mixing);
                    // Mix it in result
                    this.dsp_voices_level[i] = this.mixer.mixVoice(organPolyProcessor.buffer_size, this.numOut, this.mixing, this.outs);
                    // Check the level to possibly set the voice in kFreeVoice again
                    if ((this.dsp_voices_level[i] < 0.0005) && (this.dsp_voices_state[i] === this.kReleaseVoice)) {
                        this.dsp_voices_state[i] = this.kFreeVoice;
                    }
                }
            }

            // Apply effect
            if (this.effect) {
                this.effect.compute(this.effect_start, organPolyProcessor.buffer_size, this.outs, this.outs);
            }
        } catch (e) {
            console.log("ERROR in compute (" + e + ")");
        }

        // Update bargraph
        this.update_outputs();

        // Copy outputs
        if (output !== undefined) {
            for (var chan = 0; chan < Math.min(this.numOut, output.length); ++chan) {
                var dspOutput = this.dspOutChannnels[chan];
                output[chan].set(dspOutput);
            }
        }

        return this.running;
    }
}

// Globals
organPolyProcessor.buffer_size = 128;

// Synchronously compile and instantiate the WASM modules
try {
    if (organPolyProcessor.wasm_mixer_module == undefined) {
        organPolyProcessor.wasm_mixer_module = new WebAssembly.Module(organPolyProcessor.atob(getBase64Mixer()));
        organPolyProcessor.wasm_module = new WebAssembly.Module(organPolyProcessor.atob(getBase64Codeorgan()));
        // Possibly compile effect
        if (typeof (getBase64Codeeffect) !== "undefined") {
            organPolyProcessor.wasm_effect_module = new WebAssembly.Module(organPolyProcessor.atob(getBase64Codeeffect()));
        }
        registerProcessor('organPoly', organPolyProcessor);
    }
} catch (e) {
    console.log(e); console.log("Faust organPoly cannot be loaded or compiled");
}


