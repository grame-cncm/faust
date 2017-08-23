/*
 faust2webaudio
 
 Additional code: GRAME 2017
*/
 
'use strict';

var faust = faust || {};

class mydspNode extends AudioWorkletNode {
    
    constructor (context, options) {
        
        var json_object = JSON.parse(getJSONmydsp());
     
        // Setting values for the input, the output and the channel count.
        options.numberOfInputs = (json_object.inputs !== undefined) ? parseInt(json_object.inputs) : 0;
        options.numberOfOutputs = (json_object.outputs !== undefined) ? parseInt(json_object.outputs) : 0;
        options.channelCount = 1;
        
        super(context, 'mydsp', options);
        
        // Start node/processor communication port
        this.port.start();
    }
    
    getJSON = function ()
    {
        return getJSONmydsp();
    }
}

faust.createmydsp = function(context, callback)
{
    // The main global scope
    window.audioWorklet.addModule("mydsp-processor.js").then(callback(new mydspNode()));
}

