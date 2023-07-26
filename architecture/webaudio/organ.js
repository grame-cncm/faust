
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

if (typeof (AudioWorkletNode) === "undefined") {
    alert("AudioWorklet is not supported in this browser !")
}

class organPolyNode extends AudioWorkletNode {

    constructor(context, baseURL, options) {
        var json_object = JSON.parse(getJSONorgan());

        // Setting values for the input, the output and the channel count.
        options.numberOfInputs = (parseInt(json_object.inputs) > 0) ? 1 : 0;
        options.numberOfOutputs = (parseInt(json_object.outputs) > 0) ? 1 : 0;
        options.channelCount = Math.max(1, parseInt(json_object.inputs));
        options.outputChannelCount = [parseInt(json_object.outputs)];
        options.channelCountMode = "explicit";
        options.channelInterpretation = "speakers";

        super(context, 'organPoly', options);
        this.baseURL = baseURL;

        // JSON parsing functions
        this.parse_ui = function (ui, obj) {
            for (var i = 0; i < ui.length; i++) {
                this.parse_group(ui[i], obj);
            }
        }

        this.parse_group = function (group, obj) {
            if (group.items) {
                this.parse_items(group.items, obj);
            }
        }

        this.parse_items = function (items, obj) {
            for (var i = 0; i < items.length; i++) {
                this.parse_item(items[i], obj);
            }
        }

        this.parse_item = function (item, obj) {
            if (item.type === "vgroup"
                || item.type === "hgroup"
                || item.type === "tgroup") {
                this.parse_items(item.items, obj);
            } else if (item.type === "hbargraph"
                || item.type === "vbargraph") {
                // Keep bargraph adresses
                obj.outputs_items.push(item.address);
            } else if (item.type === "vslider"
                || item.type === "hslider"
                || item.type === "button"
                || item.type === "checkbox"
                || item.type === "nentry") {
                // Keep inputs adresses
                obj.inputs_items.push(item.address);
                // Define setXXX/getXXX, replacing '/c' with 'C' everywhere in the string
                var set_name = "set" + item.address;
                var get_name = "get" + item.address;
                get_name = get_name.replace(/\/./g, (x) => { return x.substr(1, 1).toUpperCase(); });
                set_name = set_name.replace(/\/./g, (x) => { return x.substr(1, 1).toUpperCase(); });
                obj[set_name] = (val) => { obj.setParamValue(item.address, val); };
                obj[get_name] = () => { return obj.getParamValue(item.address); };
                //console.log(set_name);
                //console.log(get_name);
            }
        }

        this.json_object = json_object;

        if (typeof (getJSONeffect) !== "undefined") {
            this.effect_json_object = JSON.parse(getJSONeffect());
        }

        this.output_handler = null;

        // input/output items
        this.inputs_items = [];
        this.outputs_items = [];

        // Parse UI
        this.parse_ui(this.json_object.ui, this);

        if (this.effect_json_object) {
            this.parse_ui(this.effect_json_object.ui, this);
        }

        // Set message handler
        this.port.onmessage = this.handleMessage.bind(this);
        try {
            if (this.parameters) this.parameters.forEach(p => p.automationRate = "k-rate");
        } catch (e) { }
    }

    // To be called by the message port with messages coming from the processor
    handleMessage(event) {
        var msg = event.data;
        if (this.output_handler) {
            this.output_handler(msg.path, msg.value);
        }
    }

    // Public API

    /**
     * Destroy the node, deallocate resources.
     */
    destroy() {
        this.port.postMessage({ type: "destroy" });
        this.port.close();
    }

    /**
     *  Returns a full JSON description of the DSP.
     */
    getJSON() {
        var res = "";
        res = res.concat("{\"name\":\""); res = res.concat(this.json_object.name); res = res.concat("\",");
        res = res.concat("\"version\":\""); res = res.concat(this.json_object.version); res = res.concat("\",");
        res = res.concat("\"options\":\""); res = res.concat(this.json_object.options); res = res.concat("\",");
        res = res.concat("\"inputs\":\""); res = res.concat(this.json_object.inputs); res = res.concat("\",");
        res = res.concat("\"outputs\":\""); res = res.concat(this.json_object.outputs); res = res.concat("\",");
        res = res.concat("\"meta\":"); res = res.concat(JSON.stringify(this.json_object.meta)); res = res.concat(",");

        if (this.effect_json_object) {
            res = res.concat("\"ui\":[{\"type\":\"tgroup\",\"label\":\"Sequencer\",\"items\":[");
            res = res.concat("{\"type\": \"vgroup\",\"label\":\"Instrument\",\"items\":");
            res = res.concat(JSON.stringify(this.json_object.ui));
            res = res.concat("},");
            res = res.concat("{\"type\":\"vgroup\",\"label\":\"Effect\",\"items\":");
            res = res.concat(JSON.stringify(this.effect_json_object.ui));
            res = res.concat("}");
            res = res.concat("]}]}");
            return res;
        } else {
            res = res.concat("\"ui\":[{\"type\":\"tgroup\",\"label\":\"Polyphonic\",\"items\":[");
            res = res.concat("{\"type\": \"vgroup\",\"label\":\"Voices\",\"items\":");
            res = res.concat(JSON.stringify(this.json_object.ui));
            res = res.concat("},");
            res = res.concat("]}]}");
            return res;
        }
    }

    // For WAP
    async getMetadata() {
        return new Promise(resolve => {
            let real_url = (this.baseURL === "") ? "main.json" : (this.baseURL + "/main.json");
            fetch(real_url).then(responseJSON => {
                return responseJSON.json();
            }).then(json => {
                resolve(json);
            })
        });
    }

    /**
     *  Set the control value at a given path.
     *
     * @param path - a path to the control
     * @param val - the value to be set
     */
    setParamValue(path, val) {
        this.port.postMessage({ type: "param", key: path, value: val });
        this.parameters.get(path).setValueAtTime(val, 0);
    }

    // For WAP
    setParam(path, val) {
        this.port.postMessage({ type: "param", key: path, value: val });
        this.parameters.get(path).setValueAtTime(val, 0);
    }

    /**
     *  Get the control value at a given path.
     *
     * @return the current control value
     */
    getParamValue(path) {
        return this.parameters.get(path).value;
    }

    // For WAP
    getParam(path) {
        return this.parameters.get(path).value;
    }

    /**
     * Setup a control output handler with a function of type (path, value)
     * to be used on each generated output value. This handler will be called
     * each audio cycle at the end of the 'compute' method.
     *
     * @param handler - a function of type function(path, value)
     */
    setOutputParamHandler(handler) {
        this.output_handler = handler;
    }

    /**
     * Get the current output handler.
     */
    getOutputParamHandler() {
        return this.output_handler;
    }

    getNumInputs() {
        return parseInt(this.json_object.inputs);
    }

    getNumOutputs() {
        return parseInt(this.json_object.outputs);
    }

    // For WAP
    inputChannelCount() {
        return parseInt(this.json_object.inputs);
    }

    outputChannelCount() {
        return parseInt(this.json_object.outputs);
    }

    /**
     * Returns an array of all input paths (to be used with setParamValue/getParamValue)
     */
    getParams() {
        return this.inputs_items;
    }

    // For WAP
    getDescriptor() {
        var desc = {};
        for (const item in this.descriptor) {
            if (this.descriptor.hasOwnProperty(item)) {
                if (this.descriptor[item].label != "bypass") {
                    desc = Object.assign({ [this.descriptor[item].label]: { minValue: this.descriptor[item].min, maxValue: this.descriptor[item].max, defaultValue: this.descriptor[item].init } }, desc);
                }
            }
        }
        return desc;
    }

    /**
     * Instantiates a new polyphonic voice.
     *
     * @param channel - the MIDI channel (0..15, not used for now)
     * @param pitch - the MIDI pitch (0..127)
     * @param velocity - the MIDI velocity (0..127)
     */
    keyOn(channel, pitch, velocity) {
        this.port.postMessage({ type: "keyOn", data: [channel, pitch, velocity] });
    }

    /**
     * De-instantiates a polyphonic voice.
     *
     * @param channel - the MIDI channel (0..15, not used for now)
     * @param pitch - the MIDI pitch (0..127)
     * @param velocity - the MIDI velocity (0..127)
     */
    keyOff(channel, pitch, velocity) {
        this.port.postMessage({ type: "keyOff", data: [channel, pitch, velocity] });
    }

    /**
     * Gently terminates all the active voices.
     */
    allNotesOff() {
        this.port.postMessage({ type: "ctrlChange", data: [channel, 123, 0] });
    }

    /**
     * Control change
     *
     * @param channel - the MIDI channel (0..15, not used for now)
     * @param ctrl - the MIDI controller number (0..127)
     * @param value - the MIDI controller value (0..127)
     */
    ctrlChange(channel, ctrl, value) {
        this.port.postMessage({ type: "ctrlChange", data: [channel, ctrl, value] });
    }

    /**
     * PitchWeel
     *
     * @param channel - the MIDI channel (0..15, not used for now)
     * @param value - the MIDI controller value (0..16383)
     */
    pitchWheel(channel, wheel) {
        this.port.postMessage({ type: "pitchWheel", data: [channel, wheel] });
    }

    /**
     * Generic MIDI message handler.
     */
    midiMessage(data) {
        this.port.postMessage({ type: "midi", data: data });
    }

    /**
     * @returns {Object} describes the path for each available param and its current value
     */
    async getState() {
        var params = new Object();
        for (let i = 0; i < this.getParams().length; i++) {
            Object.assign(params, { [this.getParams()[i]]: `${this.getParam(this.getParams()[i])}` });
        }
        return new Promise(resolve => { resolve(params) });
    }

    /**
     * Sets each params with the value indicated in the state object
     * @param {Object} state
     */
    async setState(state) {
        return new Promise(resolve => {
            for (const param in state) {
                if (state.hasOwnProperty(param)) this.setParam(param, state[param]);
            }
            try {
                this.gui.setAttribute('state', JSON.stringify(state));
            } catch (error) {
                console.warn("Plugin without gui or GUI not defined", error);
            }
            resolve(state);
        })
    }

}

// Factory class
class organPoly {

    /**
     * Factory constructor.
     *
     * @param context - the audio context
     * @param polyphony - the number of voices
     * @param baseURL - the baseURL of the plugin folder
     */
    constructor(context, polyphony = 16, baseURL = "") {
        console.log("baseLatency " + context.baseLatency);
        console.log("outputLatency " + context.outputLatency);
        console.log("sampleRate " + context.sampleRate);

        this.context = context;
        this.polyphony = polyphony;
        this.baseURL = baseURL;
    }

    /**
     * Load additionnal resources to prepare the custom AudioWorkletNode. Returns a promise to be used with the created node.
     */
    async load() {
        return new Promise((resolve, reject) => {
            let real_url = (this.baseURL === "") ? "organ-processor.js" : (this.baseURL + "/organ-processor.js");
            let options = { polyphony: this.polyphony };
            this.context.audioWorklet.addModule(real_url).then(() => {
                this.node = new organPolyNode(this.context, this.baseURL, { processorOptions: options });
                this.node.onprocessorerror = () => { console.log('An error from organ-processor was detected.'); }
                return (this.node);
            }).then((node) => {
                resolve(node);
            }).catch((e) => {
                reject(e);
            });
        });
    }

    async loadGui() {
        return new Promise((resolve, reject) => {
            try {
                // DO THIS ONLY ONCE. If another instance has already been added, do not add the html file again
                let real_url = (this.baseURL === "") ? "main.html" : (this.baseURL + "/main.html");
                if (!this.linkExists(real_url)) {
                    // LINK DOES NOT EXIST, let's add it to the document
                    var link = document.createElement('link');
                    link.rel = 'import';
                    link.href = real_url;
                    document.head.appendChild(link);
                    link.onload = (e) => {
                        // the file has been loaded, instanciate GUI
                        // and get back the HTML elem
                        // HERE WE COULD REMOVE THE HARD CODED NAME
                        var element = createorganGUI(this.node);
                        resolve(element);
                    }
                } else {
                    // LINK EXIST, WE AT LEAST CREATED ONE INSTANCE PREVIOUSLY
                    // so we can create another instance
                    var element = createorganGUI(this.node);
                    resolve(element);
                }
            } catch (e) {
                console.log(e);
                reject(e);
            }
        });
    };

    linkExists(url) {
        return document.querySelectorAll(`link[href="${url}"]`).length > 0;
    }
}

const dspName = "organPoly";

// WAP factory or npm package module
if (typeof module === "undefined") {
    window.organPoly = organPoly;
    window.FaustorganPoly = organPoly;
    window[dspName] = organPoly;
} else {
    module.exports = { organPoly };
}
