/*
 faust2wasm: GRAME 2017-2018
*/

'use strict';

if (typeof (AudioWorkletNode) === "undefined") {
	alert("AudioWorklet is not supported in this browser !")
}

class mydspPolyNode extends AudioWorkletNode {

    constructor(context, options)
    {
        var json_object = JSON.parse(getJSONmydsp());

        // Setting values for the input, the output and the channel count.
        options.numberOfInputs = (parseInt(json_object.inputs) > 0) ? 1 : 0;
        options.numberOfOutputs = (parseInt(json_object.outputs) > 0) ? 1 : 0;
        options.channelCount = Math.max(1, parseInt(json_object.inputs));
        options.outputChannelCount = [parseInt(json_object.outputs)];
        options.channelCountMode = "explicit";
        options.channelInterpretation = "speakers";

        super(context, 'mydspPoly', options);

        // JSON parsing functions
        this.parse_ui = function(ui, obj)
        {
            for (var i = 0; i < ui.length; i++) {
                this.parse_group(ui[i], obj);
            }
        }

        this.parse_group = function(group, obj)
        {
            if (group.items) {
                this.parse_items(group.items, obj);
            }
        }

        this.parse_items = function(items, obj)
        {
            for (var i = 0; i < items.length; i++) {
            	this.parse_item(items[i], obj);
            }
        }

        this.parse_item = function(item, obj)
        {
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
    }

    // To be called by the message port with messages coming from the processor
    handleMessage(event)
    {
        var msg = event.data;
        if (this.output_handler) {
            this.output_handler(msg.path, msg.value);
        }
    }

    // Public API

    /**
     *  Returns a full JSON description of the DSP.
     */
    getJSON()
    {
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

    /**
     *  Set the control value at a given path.
     *
     * @param path - a path to the control
     * @param val - the value to be set
     */
    setParamValue(path, val)
    {
        this.port.postMessage({ type:"param", key:path, value:val });
        this.parameters.get(path).setValueAtTime(val, 0);
    }

    /**
     *  Get the control value at a given path.
     *
     * @return the current control value
     */
    getParamValue(path)
    {
        return this.parameters.get(path).value;
    }

    /**
     * Setup a control output handler with a function of type (path, value)
     * to be used on each generated output value. This handler will be called
     * each audio cycle at the end of the 'compute' method.
     *
     * @param handler - a function of type function(path, value)
     */
    setOutputParamHandler(handler)
    {
        this.output_handler = handler;
    }

    /**
     * Get the current output handler.
     */
    getOutputParamHandler()
    {
        return this.output_handler;
    }

    getNumInputs()
    {
        return parseInt(this.json_object.inputs);
    }

    getNumOutputs()
    {
        return parseInt(this.json_object.outputs);
    }

    /**
     * Returns an array of all input paths (to be used with setParamValue/getParamValue)
     */
    getParams()
    {
        return this.inputs_items;
    }

    /**
     * Instantiates a new polyphonic voice.
     *
     * @param channel - the MIDI channel (0..15, not used for now)
     * @param pitch - the MIDI pitch (0..127)
     * @param velocity - the MIDI velocity (0..127)
     */
    keyOn(channel, pitch, velocity)
    {
        this.port.postMessage({ type: "keyOn", data: [channel, pitch, velocity] });
    }

    /**
     * De-instantiates a polyphonic voice.
     *
     * @param channel - the MIDI channel (0..15, not used for now)
     * @param pitch - the MIDI pitch (0..127)
     * @param velocity - the MIDI velocity (0..127)
     */
    keyOff(channel, pitch, velocity)
    {
        this.port.postMessage({ type: "keyOff", data: [channel, pitch, velocity] });
    }

    /**
     * Gently terminates all the active voices.
     */
    allNotesOff()
    {
        this.port.postMessage({ type: "ctrlChange", data: [channel, 123, 0] });
    }

    /**
     * Control change
     *
     * @param channel - the MIDI channel (0..15, not used for now)
     * @param ctrl - the MIDI controller number (0..127)
     * @param value - the MIDI controller value (0..127)
     */
    ctrlChange(channel, ctrl, value)
    {
        this.port.postMessage({ type: "ctrlChange", data: [channel, ctrl, value] });
    }

    /**
     * PitchWeel
     *
     * @param channel - the MIDI channel (0..15, not used for now)
     * @param value - the MIDI controller value (-1..1)
     */
    pitchWheel(channel, wheel)
    {
        this.port.postMessage({ type: "pitchWheel", data: [channel, wheel] });
    }

    /**
     * Generic MIDI message handler.
     */
    midiMessage(data)
    {
    	this.port.postMessage({ type:"midi", data:data });
    }

}

// Factory class

class mydspPoly {

    /**
     * Factory constructor.
     *
     * @param context - the audio context
     * @param base_url - the base_url of the plugin folder
     */
    constructor(context, base_url)
    {
        // Resume audio context each time...
        context.resume();

        this.context = context;
        this.base_url = base_url;
    }

    /**
     * Load additionnal resources to prepare the custom AudioWorkletNode. Returns a promise to be used with the created node.
     */
    load()
    {
    	return new Promise((resolve, reject) => {
        		this.context.audioWorklet.addModule(this.base_url + "mydsp-processor.js").then(() => {
        		this.node = new mydspPolyNode(this.context, {});
                this.node.onprocessorerror = () => { console.log('An error from mydsp-processor was detected.');}
        		return (this.node);
        	}).then((node) => {
                resolve(node);
            }).catch((e) => {
                reject(e);
            });
        });
    }

    loadGui()
    {
        return new Promise((resolve, reject) => {
            try {
            	var link = document.createElement('link');
            	link.rel = 'import';
            	link.id = 'urlPlugin';
            	link.href = this.base_url + "main.html";
            	document.head.appendChild(link);
            	var element = document.createElement("faust-mydsp");
            	element._plug = this.node;
            	resolve(element);
        	} catch (e) {
            	console.log(e);
            	reject(e);
        	}
    	});
    };
}
