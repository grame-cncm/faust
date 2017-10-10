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
 
 Additional code : GRAME 2014-2017
*/

'use strict';

var faust = faust || {};

faust.error_msg = null;
faust.getErrorMessage = function() { return faust.error_msg; };

var DSP_constructor = Module.cwrap('DSP_constructor', 'number', []);
var DSP_destructor = Module.cwrap('DSP_destructor', null, ['number']);
var DSP_getSampleRate = Module.cwrap('DSP_getSampleRate', 'number', ['number']);
var DSP_init = Module.cwrap('DSP_init', null, ['number','number']);
var DSP_instanceInit = Module.cwrap('DSP_instanceInit', null, ['number','number']);
var DSP_instanceConstants = Module.cwrap('DSP_instanceConstants', null, ['number','number']);
var DSP_instanceResetUserInterface = Module.cwrap('DSP_instanceResetUserInterface', null, ['number']);
var DSP_instanceClear = Module.cwrap('DSP_instanceClear', null, ['number']);
var DSP_compute = Module.cwrap('DSP_compute', null, ['number', 'number', 'number', 'number']);
var DSP_getNumInputs = Module.cwrap('DSP_getNumInputs', 'number', ['number']);
var DSP_getNumOutputs = Module.cwrap('DSP_getNumOutputs', 'number', ['number']);
var DSP_getJSON = Module.cwrap('DSP_getJSON', 'number', ['number']);
var DSP_setParamValue = Module.cwrap('DSP_setParamValue', null, ['number', 'number', 'number']);
var DSP_getParamValue = Module.cwrap('DSP_getParamValue', 'number', ['number', 'number']);

// Standard Faust DSP

faust.DSP = function (ptr, context, buffer_size) {
    
    var sp;
    
    try {
        sp = context.createScriptProcessor(buffer_size, DSP_getNumInputs(ptr), DSP_getNumOutputs(ptr));
    } catch (e) {
        faust.error_msg = "Error in createScriptProcessor: " + e;
        return null;
    }
    
    sp.ptr = ptr;
    
    sp.output_handler = null;
    sp.ins = null;
    sp.outs = null;
    
    sp.dspInChannnels = [];
    sp.dspOutChannnels = [];
    
    sp.numIn = DSP_getNumInputs(sp.ptr);
    sp.numOut = DSP_getNumOutputs(sp.ptr);
    
    // Path string
    sp.path_ptr = Module._malloc(512);
    
    // bargraph
    sp.outputs_timer = 5;
    sp.outputs_items = [];
    
    // input items
    sp.inputs_items = [];
    
    sp.update_outputs = function ()
    {
        if (sp.outputs_items.length > 0 && sp.output_handler && sp.outputs_timer-- === 0) {
            sp.outputs_timer = 5;
            for (var i = 0; i < sp.outputs_items.length; i++) {
                Module.stringToUTF8(sp.outputs_items[i], sp.path_ptr, Module.lengthBytesUTF8(sp.outputs_items[i]) + 1);
                sp.output_handler(sp.outputs_items[i], DSP_getParamValue(sp.ptr, sp.path_ptr));
            }
        }
    }
        
    // JSON parsing
    sp.parse_ui = function (ui)
    {
         for (var i = 0; i < ui.length; i++) {
            sp.parse_group(ui[i]);
        }
    }
    
    sp.parse_group = function (group)
    {
        if (group.items) {
            sp.parse_items(group.items);
        }
    }
    
    sp.parse_items = function (items)
    {
        for (var i = 0; i < items.length; i++) {
            sp.parse_item(items[i]);
        }
    }
    
    sp.parse_item = function (item)
    {
        if (item.type === "vgroup"
            || item.type === "hgroup"
            || item.type === "tgroup") {
            sp.parse_items(item.items);
        } else if (item.type === "hbargraph"
                   || item.type === "vbargraph") {
            // Keep bargraph adresses
            sp.outputs_items.push(item.address);
        } else if (item.type === "vslider"
                   || item.type === "hslider"
                   || item.type === "button"
                   || item.type === "checkbox"
                   || item.type === "nentry") {
            // Keep inputs adresses
            sp.inputs_items.push(item.address);
        }
    }
    
    sp.compute = function (e)
    {
        // Read inputs
        for (var i = 0; i < sp.numIn; i++) {
            var input = e.inputBuffer.getChannelData(i);
            var dspInput = sp.dspInChannnels[i];
            for (var j = 0; j < input.length; j++) {
                dspInput[j] = input[j];
            }
        }
        
        // Compute
        DSP_compute(sp.ptr, buffer_size, sp.ins, sp.outs);
       
        // Update bargraph
        sp.update_outputs();
        
        // Write outputs
        for (var i = 0; i < sp.numOut; i++) {
            var output = e.outputBuffer.getChannelData(i);
            var dspOutput = sp.dspOutChannnels[i];
            for (var j = 0; j < output.length; j++) {
                output[j] = dspOutput[j];
            }
        }
    }
    
    sp.initAux = function ()
    {
        var i;
        sp.ptr_size = 4; //assuming pointer in emscripten are 32bits
        sp.sample_size = 4;
        
        // Setup web audio context
        console.log("buffer_size %d", buffer_size);
        sp.onaudioprocess = sp.compute;
        
        if (sp.numIn > 0) {
            sp.ins = Module._malloc(sp.ptr_size * sp.numIn);
            for (i = 0; i < sp.numIn; i++) {
                HEAP32[(sp.ins >> 2) + i] = Module._malloc(buffer_size * sp.sample_size);
            }
            
            // Prepare Ins buffer tables
            var dspInChans = HEAP32.subarray(sp.ins >> 2, (sp.ins + sp.numIn * sp.ptr_size) >> 2);
            for (i = 0; i < sp.numIn; i++) {
                sp.dspInChannnels[i] = HEAPF32.subarray(dspInChans[i] >> 2, (dspInChans[i] + buffer_size * sp.sample_size) >> 2);
            }
        }
        
        if (sp.numOut > 0) {
            sp.outs = Module._malloc(sp.ptr_size * sp.numOut);
            for (i = 0; i < sp.numOut; i++) {
                HEAP32[(sp.outs >> 2) + i] = Module._malloc(buffer_size * sp.sample_size);
            }
           
            // Prepare Outs buffer tables
            var dspOutChans = HEAP32.subarray(sp.outs >> 2, (sp.outs + sp.numOut * sp.ptr_size) >> 2);
            for (i = 0; i < sp.numOut; i++) {
                sp.dspOutChannnels[i] = HEAPF32.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + buffer_size * sp.sample_size) >> 2);
            }
        }
                                
        // bargraph
        sp.parse_ui(JSON.parse(Pointer_stringify(DSP_getJSON(sp.ptr))).ui);
        
        // Init DSP
        DSP_init(sp.ptr, context.sampleRate);
    }
    
    sp.destroy = function ()
    {
        DSP_destructor(sp.ptr);
        
        if (sp.numIn > 0) {
            for (var i = 0; i < sp.numIn; i++) {
                Module._free(HEAP32[(sp.ins >> 2) + i]);
            }
            Module._free(sp.ins);
        }
         
        if (sp.numOut > 0) {
            for (var i = 0; i < sp.numOut; i++) {
                Module._free(HEAP32[(sp.outs >> 2) + i]);
            }
            Module._free(sp.outs);
        }
        
        Module._free(sp.path_ptr);
    }
    
    sp.getNumInputs = function ()
    {
        return DSP_getNumInputs(sp.ptr);
    }
    
    sp.getNumOutputs = function()
    {
        return DSP_getNumOutputs(sp.ptr);
    }
    
    sp.getSampleRate = function ()
    {
        return DSP_getSampleRate(sp.ptr);
    }
    
    sp.init = function (sample_rate)
    {
        DSP_init(sp.ptr, sample_rate);
    }
    
    sp.instanceInit = function (sample_rate)
    {
        DSP_instanceInit(sp.ptr, sample_rate);
    }
    
    sp.instanceConstants = function (sample_rate)
    {
        DSP_instanceConstants(sp.ptr, sample_rate);
    }
    
    sp.instanceResetUserInterface = function ()
    {
        DSP_instanceResetUserInterface(sp.ptr);
    }
    
    sp.instanceClear = function ()
    {
        DSP_instanceClear(sp.ptr);
    }
    
    sp.setOutputParamHandler = function (hd)
    {
        sp.output_handler = hd;
    }
   
    sp.setParamValue = function (path, val)
    {
        Module.stringToUTF8(path, sp.path_ptr, Module.lengthBytesUTF8(path) + 1);
        DSP_setParamValue(sp.ptr, sp.path_ptr, val);
    }
    
    sp.getParamValue = function (path)
    {
        Module.stringToUTF8(path, sp.path_ptr, Module.lengthBytesUTF8(path) + 1);
        return DSP_getParamValue(sp.ptr, sp.path_ptr);
    }
    
    sp.getParams = function ()
    {
        return sp.inputs_items;
    }
    
    sp.getJSON = function ()
    {
        return Pointer_stringify(DSP_getJSON(sp.ptr));
    }
    
    sp.initAux();
    
    return sp;
};

faust.createDSP = function(context, buffer_size, callback)
{
	callback(faust.mydsp(DSP_constructor(), context, buffer_size));
}

