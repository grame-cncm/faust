/*
 faust2wasm
 
 Additional code: GRAME 2017
*/
 
'use strict';

var faust = faust || {};

class mydspNode extends AudioWorkletNode {
    
    constructor(context, options) {
        
        var json_object = JSON.parse(getJSONmydsp());
     
        // Setting values for the input, the output and the channel count.
        options.numberOfInputs = parseInt(json_object.inputs);
        options.numberOfOutputs = parseInt(json_object.outputs);
        options.channelCount = 1;
        
        super(context, 'mydsp', options);
        
        // Start node/processor communication port
        this.port.start();
    }
    
    getJSON()
    {
        return getJSONmydsp();
    }
}

faust.createmydsp = function(context, buffer_size, callback)
{
    // The main global scope
    window.audioWorklet.addModule("mydsp-processor.js").then(callback(new mydspNode(context)));
}

