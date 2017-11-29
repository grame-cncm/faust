/*
 faust2wasm
 
 Additional code: GRAME 2017
*/
 
'use strict';

if (typeof (AudioWorkletNode) === "undefined") {
	alert("AudioWorklet is not supported in this browser !")
}

var faust = faust || {};

class mydsp_polyNode extends AudioWorkletNode {
    
    constructor(context, options) {
        
        var json_object = JSON.parse(getJSONmydsp());
     
        // Setting values for the input, the output and the channel count.
        options.numberOfInputs = parseInt(json_object.inputs);
        options.numberOfOutputs = parseInt(json_object.outputs);
        options.channelCount = 1;
        
        super(context, 'mydsp_poly', options);
        
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
                obj.pathTable[item.address] = parseInt(item.index);
            } else if (item.type === "vslider"
                       || item.type === "hslider"
                       || item.type === "button"
                       || item.type === "checkbox"
                       || item.type === "nentry") {
                // Keep inputs adresses
                obj.inputs_items.push(item.address);
                obj.pathTable[item.address] = parseInt(item.index);
            }
        }
        
        this.json_object = json_object;
            
        // input/output items
        this.inputs_items = [];
        this.outputs_items = [];
        
        this.pathTable = [];
    
        // Parse UI
        this.parse_ui(this.json_object.ui, this);
        
        // Start node/processor communication port
        //this.port.start();
    }
    
    getJSON()
    {
        return getJSONmydsp();
    }
    
    setParamValue(path, val)
    {
        this.parameters.get(path).setValueAtTime(val, 0);
    }
    
    getParamValue(path)
    {
        return this.parameters.get(path).value;
    }
    
     
    setOutputParamHandler(handler)
    {
        // TODO
    }
    
    // TO REMOVE
    getNumInputs()
    {
        return parseInt(this.json_object.inputs);
    }
    
    getNumOutputs()
    {
        return parseInt(this.json_object.outputs);
    }
    
    getParams()
    {
        return this.inputs_items;
    }
}

// Hack : 11/28/17, add an explicit timeout
faust.createmydsp_poly = function(callback)
{
    // The main global scope
    var AWContext = window.audioWorklet || BaseAudioContext.AudioWorklet;
    console.log(AWContext);
    AWContext.addModule("mydsp-processor.js")
    .then(function () {
    	setTimeout(function () {
         	audio_context = new AudioContext();
         	callback(new mydsp_polyNode(audio_context, {}));
    	}, 500)
    })
	.catch(function(error) { console.log(error); console.log("Faust mydsp_poly cannot be loaded or compiled"); });
}
