/*
 faust2wasm
 
 Additional code: GRAME 2017
*/
 
'use strict';

var faust = faust || {};

class mydsp_polyNode extends AudioWorkletNode {
    
    constructor (context, options) {
        
        var json_object = JSON.parse(getJSONmydsp());
     
        // Setting values for the input, the output and the channel count.
        options.numberOfInputs = parseInt(json_object.inputs);
        options.numberOfOutputs = parseInt(json_object.outputs);
        options.channelCount = 1;
        
        super(context, 'mydsp_poly', options);
        
        // Start node/processor communication port
        this.port.start();
    }
    
    getJSON = function ()
    {
        return getJSONmydsp();
    }
}

faust.createmydsp_poly = function(context, callback)
{
    // The main global scope
    window.audioWorklet.addModule("mydsp-processor.js").then(callback(new mydsp_polyNode()));
}

