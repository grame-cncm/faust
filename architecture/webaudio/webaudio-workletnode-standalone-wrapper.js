/*
 faust2wasm
 
 Additional code: GRAME 2017
*/
 
'use strict';

var faust = faust || {};

// JSON parsing functions
faust.parse_ui = function (ui, callback)
{
    for (var i = 0; i < ui.length; i++) {
        faust.parse_group(ui[i], callback);
    }
}

faust.parse_group = function (group, callback)
{
    if (group.items) {
        faust.parse_items(group.items, callback);
    }
}

faust.parse_items = function (items, callback)
{
    var i;
    for (i = 0; i < items.length; i++) {
        callback(items[i]);
    }
}

class mydspNode extends AudioWorkletNode {
    
    constructor(context, options) {
        
        this.json_object = JSON.parse(getJSONmydsp());
        
        // input/output items
        this.inputs_items = [];
        this.outputs_items = [];
     
        // Setting values for the input, the output and the channel count.
        options.numberOfInputs = parseInt(json_object.inputs);
        options.numberOfOutputs = parseInt(json_object.outputs);
        options.channelCount = 1;
        
        // Parse UI
        faust.parse_ui(this.json_object.ui,
                       function (item) {
                           if (item.type === "vgroup"
                               || item.type === "hgroup"
                               || item.type === "tgroup") {
                                faust.parse_items(item.items);
                           } else if (item.type === "hbargraph"
                                      || item.type === "vbargraph") {
                                // Keep bargraph adresses
                                this.outputs_items.push(item.address);
                           } else if (item.type === "vslider"
                                      || item.type === "hslider"
                                      || item.type === "button"
                                      || item.type === "checkbox"
                                      || item.type === "nentry") {
                                // Keep inputs adresses
                                this.inputs_items.push(item.address);
                           }
                       });
        
        // Start node/processor communication port
        this.port.start();
        
        super(context, 'mydsp', options);
    }
    
    getJSON()
    {
        return getJSONmydsp();
    }
    
    getParams()
    {
        return this.inputs_items;
    }
}

faust.createmydsp = function(context, buffer_size, callback)
{
    // The main global scope
    window.audioWorklet.addModule("mydsp-processor.js").then(callback(new mydspNode(context)));
}

