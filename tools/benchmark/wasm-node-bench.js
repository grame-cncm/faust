
'use strict';

var faust = faust || {};

// Build global context
var window = {};
window.Math = {};

window.Int32Array = Int32Array;
window.Float64Array = Float64Array;

window.Math.imul = Math.imul;
window.Math.log = Math.log;
window.Math.abs = global.Math.abs;
window.Math.fabs = global.Math.abs;
window.Math.acos = global.Math.acos;
window.Math.asin = global.Math.asin;
window.Math.atan = global.Math.atan;
window.Math.atan2 = global.Math.atan2;
window.Math.ceil = global.Math.ceil;
window.Math.cos = global.Math.cos;
window.Math.exp = global.Math.exp;
window.Math.floor = global.Math.floor;
window.Math.log = global.Math.log;
window.Math.max = global.Math.max;
window.Math.min = global.Math.min;
window.Math.pow = global.Math.pow;
window.Math.round = global.Math.round;
window.Math.sin = global.Math.sin;
window.Math.sqrt = global.Math.sqrt;
window.Math.tan = global.Math.tan;

// Standard Faust DSP
faust.mydsp = function (context, instance, buffer_size, sample_rate) {

    var output_handler = null;
    var ins, outs;
    
    var dspInChannnels = [];
    var dspOutChannnels = [];
   
    // Keep JSON parsed object
    var json_object = JSON.parse(getJSONmydsp());
    
    function getNumInputsAux () 
    {
        return (json_object.inputs !== undefined) ? parseInt(json_object.inputs) : 0;
    }
    
    function getNumOutputsAux () 
    {
        return (json_object.outputs !== undefined) ? parseInt(json_object.outputs) : 0;
    }
    
    var numIn = getNumInputsAux();
    var numOut = getNumOutputsAux();
     
    // Memory allocator
    var ptr_size = 8;
    var sample_size = 8;  // double
    
    function pow2limit (x)
    {
        var n = 65536; // Minimum = 64 kB
        while (n < x) { n = 2 * n; }
        return n;
    }
     
    var memory_size = pow2limit(getSizemydsp() + (numIn + numOut) * (ptr_size + (buffer_size * sample_size)));
   
    var factory = instance.exports;
    
    var HEAP = instance.exports.memory.buffer;
    var HEAP32 = new Int32Array(HEAP);
    var HEAPF = new Float64Array(HEAP);
  
    // bargraph
    var ouputs_timer = 5;
    var ouputs_items = [];
     
    // input items
    var inputs_items = [];
    
    // buttons items
    var buttons_items = [];
    
    // default values
    var default_values = [];
    
    // DSP is placed first with index 0. Audio buffer start at the end of DSP.
    var audio_heap_ptr = getSizemydsp();
  
    // Setup pointers offset
    var audio_heap_ptr_inputs = audio_heap_ptr; 
    var audio_heap_ptr_outputs = audio_heap_ptr_inputs + (numIn * ptr_size);
     
    // Setup buffer offset
    var audio_heap_inputs = audio_heap_ptr_outputs + (numOut * ptr_size);
    var audio_heap_outputs = audio_heap_inputs + (numIn * buffer_size * sample_size);
    
    // Start of DSP memory : DSP is placed first with index 0
    var dsp = 0;
    
    var pathTable = getPathTablemydsp();
    
    // Allocate table for 'setParamValue'
    var value_table = [];
        
    function update_outputs () 
    {
        if (ouputs_items.length > 0 && output_handler && ouputs_timer-- === 0) {
            ouputs_timer = 5;
            for (var i = 0; i < ouputs_items.length; i++) {
                output_handler(ouputs_items[i], factory.getParamValue(dsp, pathTable[ouputs_items[i]]));
            }
        }
    }
    
    function computeAux (inputs, outputs)
    {
        var i, j;
        
        // Read inputs
        for (i = 0; i < numIn; i++) {
            var input = inputs[i];
            var dspInput = dspInChannnels[i];
            for (j = 0; j < buffer_size; j++) {
                dspInput[j] = input[j];
            }
        }
        
        // Update control state
        for (i = 0; i < inputs_items.length; i++) {
            var path = inputs_items[i];
            var values = value_table[path];
            factory.setParamValue(dsp, pathTable[path], values[0]);
            values[0] = values[1];
        }
        
        // Compute
        factory.compute(dsp, buffer_size, ins, outs);
       
        // Update bargraph
        update_outputs();
        
        // Write outputs
        for (i = 0; i < numOut; i++) {
            var output = outputs[i];
            var dspOutput = dspOutChannnels[i];
            for (j = 0; j < buffer_size; j++) {
                output[j] = dspOutput[j];
            }
        }
    };
         
    // JSON parsing
    function parse_ui (ui) 
    {
        for (var i = 0; i < ui.length; i++) {
            parse_group(ui[i]);
        }
    }
    
    function parse_group (group) 
    {
        if (group.items) {
            parse_items(group.items);
        }
    }
    
    function parse_items (items) 
    {
        var i;
        for (i = 0; i < items.length; i++) {
            parse_item(items[i]);
        }
    }
    
    function parse_item (item) 
    {
        if (item.type === "vgroup" || item.type === "hgroup" || item.type === "tgroup") {
            parse_items(item.items);
        } else if (item.type === "hbargraph" || item.type === "vbargraph") {
            // Keep bargraph adresses
            ouputs_items.push(item.address);
        } else if (item.type === "vslider" || item.type === "hslider" || item.type === "button" || item.type === "checkbox" || item.type === "nentry") {
            // Keep inputs adresses
            inputs_items.push(item.address);
            if (item.type === "button") {
                buttons_items.push(item.address);
                default_values.push(0);
            } else if (item.type === "checkbox") {
            	default_values.push(0);
            } else {
                default_values.push(parseFloat(item.init));
            }
        }
    }
      
    function init ()
    {
        var i;
        
        if (numIn > 0) {
            ins = audio_heap_ptr_inputs; 
            for (i = 0; i < numIn; i++) { 
                HEAP32[(ins >> 2) + i] = audio_heap_inputs + ((buffer_size * sample_size) * i);
           }
     
            // Prepare Ins buffer tables
            var dspInChans = HEAP32.subarray(ins >> 2, (ins + numIn * ptr_size) >> 2);
            for (i = 0; i < numIn; i++) {
                dspInChannnels[i] = HEAPF.subarray(dspInChans[i] >> 3, (dspInChans[i] + buffer_size * sample_size) >> 3);
            }
        }
        
        if (numOut > 0) {
            outs = audio_heap_ptr_outputs; 
            for (i = 0; i < numOut; i++) { 
                HEAP32[(outs >> 2) + i] = audio_heap_outputs + ((buffer_size * sample_size) * i);
            }
          
            // Prepare Out buffer tables
            var dspOutChans = HEAP32.subarray(outs >> 2, (outs + numOut * ptr_size) >> 2);
            for (i = 0; i < numOut; i++) {
                dspOutChannnels[i] = HEAPF.subarray(dspOutChans[i] >> 3, (dspOutChans[i] + buffer_size * sample_size) >> 3);
            }
        }
                                
        // bargraph
        parse_ui(json_object.ui);
        
        // Init DSP
        factory.init(dsp, sample_rate);
        
        // Init 'value' table
        for (i = 0; i < inputs_items.length; i++) {
            var path = inputs_items[i];
            var values = new Float64Array(2);
            values[0] = values[1] = factory.getParamValue(dsp, pathTable[path]);
            value_table[path] = values;
        }
    }
    
	function setParamValueAux (path, val) 
	{
		var values = value_table[path];
		if (values) {
			// relaxing the test
			//if (factory.getParamValue(dsp, pathTable[path]) === values[0]) {
				values[0] = val;
			//} 
			values[1] = val;
		}
	}
    
    init();
    
    // External API
    return {
     	
        getSampleRate : function () 
        {
            return factory.getSampleRate(dsp);
        },
        
        getNumInputs : function () 
        {
            return getNumInputsAux();
        },
        
        getNumOutputs : function () 
        {
            return getNumOutputsAux();
        },
               
        init : function (sample_rate) 
        {
            factory.init(dsp, sample_rate);
        },
        
        instanceInit : function (sample_rate) 
        {
            factory.instanceInit(dsp, sample_rate);
        },
        
        instanceConstants : function (sample_rate) 
        {
            factory.instanceConstants(dsp, sample_rate);
        },
        
        instanceResetUserInterface : function () 
        {
            factory.instanceResetUserInterface(dsp);
        },
        
        instanceClear : function () 
        {
            factory.instanceClear(dsp);
        },
        
        setOutputParamHandler : function (handler)
        {
            output_handler = handler;
        },
        
        getOutputParamHandler : function ()
        {
            return output_handler;
        },
        
        setParamValue : function (path, val) 
        {
        	setParamValueAux(path, val);
        },
        
        setParamValue1 : function (path, val)
        {
            factory.setParamValue(dsp, pathTable[path], val);
        },

        getParamValue : function (path) 
        {
            return factory.getParamValue(dsp, pathTable[path]);
        },
        
        getParams : function()
        {
            return inputs_items;
        },
        
        getButtonsParams : function()
        {
            return buttons_items;
        },
        
        getJSON : function ()
        {
            return getJSONmydsp();
        },
        
        compute : function (inputs, outputs)
        {
            computeAux(inputs, outputs);
        },
        
        checkDefaults : function ()
		{
			for (var i = 0; i < default_values.length; i++) {
				if (default_values[i] !== factory.getParamValue(dsp, pathTable[inputs_items[i]])) return false;
			}
			return true;
		},
	
		initRandom : function ()
		{
			for (var i = 0; i < default_values.length; i++) {
                factory.setParamValue(dsp, pathTable[inputs_items[i]], 0.123456789);
			}
		}
    };
};

// Bench code

var fs = require('fs');
var buffer_size = 1024;
var sample_rate = 44100;
var inputs = [];
var outputs = [];
var run = -1;
var measures = [];
var instance1 = null;
var instance2 = null;

var asm2wasm = { // special asm2wasm imports
    "fmod": function(x, y) {
        return x % y;
    },
    "log10": function(x) {
        return window.Math.log(x) / window.Math.log(10);
    },
    "remainder": function(x, y) {
        return x - window.Math.round(x/y) * y;
    }
};
var importObject = { imports: { print: arg => console.log(arg) } }
importObject["global.Math"] = window.Math;
importObject["asm2wasm"] = asm2wasm;

var response1 = toUint8Array(fs.readFileSync('DSP.wasm'));
var bytes1 = response1.buffer;

var response2 = toUint8Array(fs.readFileSync('DSP-opt.wasm'));
var bytes2 = response2.buffer;

var create = function(ins, outs)
{
    console.log("Allocate ins/outs buffers");
    for (var i = 0; i < ins; i++) {
        inputs.push(new Float64Array(buffer_size));
    }
    for (var i = 0; i < outs; i++) {
        outputs.push(new Float64Array(buffer_size));
    }
}

function benchOne(dsp, run)
{
    var time1 = new Date().getTime();

    // Bench DSP
    while (run-- > 0) {
        dsp.compute(inputs, outputs);
    }

    var time2 = new Date().getTime();
    return (time2 - time1);
}

function bench(instance)
{
    // Creates DSP and buffers
    var DSP = faust.mydsp(null, instance, buffer_size, sample_rate);

    // First call
    if (run === -1) {
        // Setup buffers
        create(DSP.getNumInputs(), DSP.getNumOutputs(), buffer_size);
        // Setup a good value for 'run'
        var delta = benchOne(DSP, 1000);
        console.log("Delta : " + delta);
        run = (1000 / delta) * 5000;
    }

    // Do the bench and keep result
    var duration = benchOne(DSP, run);
    measures.push(duration);
    
    console.log("DSP CPU % : " + ((duration * sample_rate) / (run * buffer_size * 10)));

    // Compare every two tests (normal/optimized)
    if (measures.length % 2 === 0) {
        var v1 = measures[measures.length - 1];
        var v2 = measures[measures.length - 2];

        console.log("Normal : " + v1 + " optimized : " + v2);
        console.log("Gain : " + (v1 - v2)/v1*100);
    }
}

function toUint8Array(buf)
{
    var res = new Uint8Array(buf.length);
    for (var i = 0; i < buf.length; ++i) {
        res[i] = buf[i];
    }
    return res;
}

function compileTwoDSP(bytes1, bytes2, callback)
{
    console.log("compileTwoDSP");
    WebAssembly.compile(bytes1)
        .then(m => { WebAssembly.instantiate(m, importObject)
        .then(instance => {
              instance1 = instance;
              WebAssembly.compile(bytes2)
                .then(m => { WebAssembly.instantiate(m, importObject)
                .then(instance => {
                      instance2 = instance;
                      callback();
                })});
             })});
}

function benchTwoDSP()
{
    console.log("benchTwoDSP");
    for (var i = 0; i < 5; i++) {
        bench(instance1);
        bench(instance2);
    }
}

// Main
compileTwoDSP(bytes1, bytes2, benchTwoDSP);

