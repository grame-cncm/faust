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
 
 Additional code : GRAME 2014
*/

/*global webkitAudioContext, Module, HEAPF32, HEAP32, Pointer_stringify, ALLOC_STACK, intArrayFromString, allocate*/

var faust = faust || {};

// Shim AudioContext on webkit
window.AudioContext = window.AudioContext || window.webkitAudioContext || undefined;

(function () {
 
    var asmjs_dsp_factory = Module.cwrap('asmjs_dsp_factory', null, ['number']);
 
    // Standard Faust DSP

    faust.DSP = function (context, code, buffer_size, handler) {
        var that = {};
        
        faust.context = context;
        that.buffer_size = buffer_size;
        that.handler = handler;
        
        // bargraph
        that.ouputs_timer = 5;
        that.ouputs_items = [];
        
        // input items
        that.inputs_items = [];
 
        var dspcontentPtr = allocate(intArrayFromString(code), 'i8', ALLOC_STACK);
        that.factory_code = Pointer_stringify(asmjs_dsp_factory(dspcontentPtr));
        that.factory = eval(thatfactory_codefactory);
        that.dsp = that.factory.newmydsp();
 
        console.log(that.factory_code);
        console.log(that.factory);
        console.log(that.dsp);
         
        // Bind to C++ Member Functions
        
        that.getNumInputs = function () 
        {
            return that.factory.getNumInputs(that.dsp);
        };
        
        that.getNumOutputs = function () 
        {
            return that.factory.getNumOutputs(that.dsp);
        };
        
        that.update_outputs = function () 
        {
            if (that.ouputs_items.length > 0 && that.handler && that.ouputs_timer-- === 0) {
                that.ouputs_timer = 5;
                var i;
                for (i = 0; i < that.ouputs_items.length; i++) {
                    var pathPtr = allocate(intArrayFromString(that.ouputs_items[i]), 'i8', ALLOC_STACK);
                    that.handler(that.ouputs_items[i], that.factory.getValue(that.dsp, pathPtr));
                }
            }
        };
     
        that.compute = function (e) 
        {
            var i;
 
            var inputs = [];
            for (i = 0; i < that.getNumInputs(); i++) {
                inputs[i] = e.inputBuffer.getChannelData(i);
            }
 
             var outputs = [];
             for (i = 0; i < that.getNumOutputs(); i++) {
                outputs[i] = e.outputBuffer.getChannelData(i);
             }
 
            // Compute
            that.factory.compute(that.dsp, that.buffer_size, inputs, outputs);
           
            // Update bargraph
            that.update_outputs();
        };
        
        that.destroy = function ()
        {
            that.factory.deletemydsp(that.dsp);
        };
        
        // Connect to another node
        that.connect = function (node) 
        {
            if (node.scriptProcessor) {
                that.scriptProcessor.connect(node.scriptProcessor);
            } else {
                that.scriptProcessor.connect(node);
            }
        };
        
        // Bind to Web Audio, external API
        that.start = function () 
        {
            that.scriptProcessor.connect(faust.context.destination);
        };
        
        that.stop = function () 
        {
            that.scriptProcessor.disconnect(faust.context.destination);
        };
        
        that.update = function (path, val) 
        {
            that.factory.setValue(that.dsp, path, val);
        };
        
        that.json = function ()
        {
            return Pointer_stringify(that.factory.JSON());
        }
        
        that.controls = function()
        {
            return that.inputs_items;
        }
        
        // JSON parsing
        that.parse_ui = function(ui) 
        {
            var i;
            for (i = 0; i < ui.length; i++) {
                that.parse_group(ui[i]);
            }
        }
        
        that.parse_group = function(group) 
        {
            if (group.items) {
                that.parse_items(group.items);
            }
        }
        
        that.parse_items = function(items) 
        {
            var i;
            for (i = 0; i < items.length; i++) {
                that.parse_item(items[i]);
            }
        }
        
        that.parse_item = function(item) 
        {
            if (item.type === "vgroup" || item.type === "hgroup" || item.type === "tgroup") {
                that.parse_items(item.items);
            } else if (item.type === "hbargraph" || item.type === "vbargraph") {
                // Keep bargraph adresses
                that.ouputs_items.push(item.address);
            } else if (item.type === "vslider" || item.type === "hslider" || item.type === "button" || item.type === "checkbox" || item.type === "nentry") {
                // Keep inputs adresses
                that.inputs_items.push(item.address);
            }
        }
          
        that.init = function ()
        {
            // Setup web audio context
            console.log("that.buffer_size %d", that.buffer_size);
            that.scriptProcessor = faust.context.createScriptProcessor(that.buffer_size, that.getNumInputs(), that.getNumOutputs());
            that.scriptProcessor.onaudioprocess = that.factory.compute;
                                    
            // bargraph
            that.parse_ui(JSON.parse(that.json()).ui);
 
            // Init DSP
            that.factory.init(that.dsp, faust.context.sampleRate);
        };
        
        that.init();
        
        return that;
    };

}());
