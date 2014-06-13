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
 
    var createDSPFactory = Module.cwrap('createDSPFactory', 'number', ['number', 'number']);
 
    // Standard Faust DSP

    faust.createDSPFactory = function (code) {
        
        // TODO : generate real factory name...
        var factory_name = "mydsp";
        
        // 'buffer' is the emscripten global memory conext
 //console.log(buffer);
 //console.log(globalScope);
        
        //Module.TOTAL_MEMORY = 41943040;
 
        var code_ptr = allocate(intArrayFromString(code), 'i8', ALLOC_STACK);
        var error_msg_ptr = allocate(intArrayFromString('', false, 256), 'i8', ALLOC_STACK);
        var factory_code = Pointer_stringify(createDSPFactory(code_ptr, error_msg_ptr));
        var error_msg = Pointer_stringify(error_msg_ptr);
        console.log(factory_code);
 
        if (factory_code === "") {
            alert(error_msg);
        }
 
        // 'libfaust.js' asm.js backend generates the ASM module + UI method, then we compile the code
        eval(factory_code);
 
        // Compile the ASM module itself
        // console.log(Module);
        var factory = eval(factory_name + "Factory(window, Module, buffer)");        
        console.log(factory);
 
        var path_table_function_name = eval("getPathTable" + factory_name); 
        factory.pathTable = path_table_function_name();
    
        var json_function_name = eval("getJSON" + factory_name);
        factory.getJSON = function() { return json_function_name();}
 
        var metadata_function_name = eval("metadata" + factory_name);
        factory.metadata = function(m) { return metadata_function_name(m);}
 
        var getdspsize_function_name = eval("getDSPSize" + factory_name);
        factory.getDSPSize = function(m) { return getdspsize_function_name(m);}
 
        return factory;
    };
 
    faust.deleteDSPFactory = function (factory) {
 
 }
  
    faust.createDSPInstance = function (factory, context, buffer_size, handler) {
        
        // TODO : generate real factory name...
        var factory_name = "mydsp";
 
        var that = {};
 
        that.factory = factory;
        //that.dsp = that.factory.newDSP();
        that.dsp = Module._malloc(that.factory.getDSPSize());
        faust.context = context;
        that.buffer_size = buffer_size;
        that.handler = handler;
 
        // bargraph
        that.ouputs_timer = 5;
        that.ouputs_items = [];
         
        // input items
        that.inputs_items = [];
               
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
                    that.handler(that.ouputs_items[i], that.factory.getValue(that.dsp, that.factory.pathTable[that.ouputs_items[i]]));
                }
            }
        };
     
        that.compute = function (e) 
        {
            var i, j;
             
            // Read inputs
            for (i = 0; i < that.numIn; i++) {
                var input = e.inputBuffer.getChannelData(i);
                var dspInput = that.dspInChannnels[i];
                for (j = 0; j < input.length; j++) {
                    dspInput[j] = input[j];
                }
            }
 
            // Compute
            that.factory.compute(that.dsp, that.buffer_size, that.ins, that.outs);
           
            // Update bargraph
            that.update_outputs();
 
            // Write outputs
            for (i = 0; i < that.numOut; i++) {
                var output = e.outputBuffer.getChannelData(i);
                var dspOutput = that.dspOutChannnels[i];
                for (j = 0; j < output.length; j++) {
                    output[j] = dspOutput[j];
                }
            }
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
            that.factory.setValue(that.dsp, that.factory.pathTable[path], val);
        };
        
        that.json = function ()
        {
            /*
            var json_function_name = eval("faustUI.getJSON" + factory_name);
 console.log(json_function_name);
            return that.factory.json_function_name();
            */
            return that.factory.getJSON();
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
            var i;
            that.ptrsize = 4; //assuming pointer in emscripten are 32bits
            that.samplesize = 4;
             
            // Get input / output counts
            that.numIn = that.getNumInputs();
            that.numOut = that.getNumOutputs();
             
            // Setup web audio context
            console.log("that.buffer_size %d", that.buffer_size);
            that.scriptProcessor = faust.context.createScriptProcessor(that.buffer_size, that.numIn, that.numOut);
            that.scriptProcessor.onaudioprocess = that.compute;
             
            // TODO the below calls to malloc are not yet being freed, potential memory leak
            // allocate memory for input / output arrays
            that.ins = Module._malloc(that.ptrsize * that.numIn);
             
            // Assign to our array of pointer elements an array of 32bit floats, one for each channel. currently we assume pointers are 32bits
            for (i = 0; i < that.numIn; i++) { 
                // assign memory at that.ins[i] to a new ptr value. Maybe there's an easier way, but this is clearer to me than any typedarray magic beyond the presumably TypedArray HEAP32
                HEAP32[(that.ins >> 2) + i] = Module._malloc(that.buffer_size * that.samplesize); 
            }
             
            //ptrsize, change to eight or use Runtime.QUANTUM? or what?
            that.outs = Module._malloc(that.ptrsize * that.numOut); 
             
            // Assign to our array of pointer elements an array of 64bit floats, one for each channel. Currently we assume pointers are 32bits
            for (i = 0; i < that.numOut; i++) { 
                // Assign memory at that.outs[i] to a new ptr value. Maybe there's an easier way, but this is clearer to me than any typedarray magic beyond the presumably TypedArray HEAP32
                HEAP32[(that.outs >> 2) + i] = Module._malloc(that.buffer_size * that.samplesize);
            }
             
            // Prepare Ins/out buffer tables
            that.dspInChannnels = [];
            var dspInChans = HEAP32.subarray(that.ins >> 2, (that.ins + that.ins * that.ptrsize) >> 2);
            for (i = 0; i < that.numIn; i++) {
                that.dspInChannnels[i] = HEAPF32.subarray(dspInChans[i] >> 2, (dspInChans[i] + that.buffer_size * that.ptrsize) >> 2);
            }
             
            that.dspOutChannnels = [];
            var dspOutChans = HEAP32.subarray(that.outs >> 2, (that.outs + that.numOut * that.ptrsize) >> 2);
            for (i = 0; i < that.numOut; i++) {
                that.dspOutChannnels[i] = HEAPF32.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + that.buffer_size * that.ptrsize) >> 2);
            }
                                    
            // bargraph
            that.parse_ui(JSON.parse(that.json()).ui);
 
            // Init DSP
            that.factory.init(that.dsp, faust.context.sampleRate);
        };
        
        that.init();
        
        return that;
    };
 
    faust.deleteDSPInstance = function (that) {
     
 console.log("faust.deleteDSPInstance ");
 console.log(that);
 that.stop();
         
         for (i = 0; i < that.numIn; i++) { 
            Module._free(HEAP32[(that.ins >> 2) + i]); 
         }
         
         for (i = 0; i < that.numOut; i++) { 
            Module._free(HEAP32[(that.outs >> 2) + i])
         }
         
         Module._free(that.ins);
         Module._free(that.outs);
         
         //that.factory.deleteDSP(that.dsp);
         
         Module._free(that.dsp);
    };

}());
