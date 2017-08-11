
'use strict';

// Build global context
var window = {};
window.Math = {};

window.Int32Array = Int32Array;
window.Float32Array = Float32Array;

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

<<includeIntrinsic>>
<<includeclass>>

// Standard Faust DSP

var faust = faust || {};

faust.mydsp = function (buffer_size, sample_rate) {

    var handler = null;
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
    var ptr_size = 4; 
    var sample_size = 4;    // float
    
   	function pow2limit (x)
    {
		var n = 65536; // Minimum = 64 kB
		while (n < x) { n = 2 * n; }
		return n;
    }
     
    var memory_size = pow2limit(getSizemydsp() + (numIn + numOut) * (ptr_size + (buffer_size * sample_size)));
   
    var HEAP = new ArrayBuffer(memory_size);
    var HEAP32 = new Int32Array(HEAP);
    var HEAPF = new Float32Array(HEAP);
  
    // bargraph
    var ouputs_timer = 5;
    var ouputs_items = [];
     
    // input items
    var inputs_items = [];
    
    // buttons items
    var buttons_items = [];
    
    // default values
    var default_values = [];
     
    // Start of HEAP index
    var audio_heap_ptr = 0;
     
    // Setup pointers offset
    var audio_heap_ptr_inputs = audio_heap_ptr; 
    var audio_heap_ptr_outputs = audio_heap_ptr_inputs + (numIn * ptr_size);
     
    // Setup buffer offset
    var audio_heap_inputs = audio_heap_ptr_outputs + (numOut * ptr_size);
    var audio_heap_outputs = audio_heap_inputs + (numIn * buffer_size * sample_size);
    
    // Setup DSP offset
    var dsp_start = audio_heap_outputs + (numOut * buffer_size * sample_size);
     
    // Start of DSP memory
    var dsp = dsp_start;
 
    // ASM module
    var factory = mydspModule(window, window.Math, HEAP);
    //console.log(factory);
 
    var pathTable = getPathTablemydsp();
    
    // Allocate table for 'setParamValue'
    var value_table = [];
        
    function update_outputs () 
    {
        if (ouputs_items.length > 0 && handler && ouputs_timer-- === 0) {
            ouputs_timer = 5;
            for (var i = 0; i < ouputs_items.length; i++) {
                handler(ouputs_items[i], factory.getParamValue(dsp, pathTable[ouputs_items[i]]));
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
                dspInChannnels[i] = HEAPF.subarray(dspInChans[i] >> 2, (dspInChans[i] + buffer_size * sample_size) >> 2);
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
                dspOutChannnels[i] = HEAPF.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + buffer_size * sample_size) >> 2);
            }
        }
                                
        // bargraph
        parse_ui(json_object.ui);
        
        // Init DSP
        factory.init(dsp, sample_rate);
        
        // Init 'value' table
        for (i = 0; i < inputs_items.length; i++) {
            var path = inputs_items[i];
            var values = new Float32Array(2);
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
    
        destroy : function ()
        {
            // Nothing to do
        },
        
        getNumInputs : function () 
        {
            return getNumInputsAux();
        },
        
        getNumOutputs : function () 
        {
            return getNumOutputsAux();
        },
        
        getSampleRate : function () 
        {
            return factory.getSampleRate(dsp);
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
        
        setHandler : function (hd)
        {
            handler = hd;
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
        
        controls : function()
        {
            return inputs_items;
        },
        
        buttons : function()
        {
            return buttons_items;
        },
        
        json : function ()
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

// Helper functions

var create = function(ins, outs, buffer_size) {
    for (var i = 0; i < ins; i++) {
        inputs.push(new Float32Array(buffer_size));
    }
    for (var i = 0; i < outs; i++) {
        outputs.push(new Float32Array(buffer_size));
    }
}

var impulse = function(ins, buffer_size) {
    for (var i = 0; i < ins; i++) {
        inputs[i][0] = 1.0;
        for (var f = 1; f < buffer_size; f++) {
            inputs[i][f] = 0.0;
        }
    }
}

var zero = function(ins, buffer_size) {
    for (var i = 0; i < ins; i++) {
        for (var f = 0; f < buffer_size; f++) {
            inputs[i][f] = 0.0;
        }
    }
}

var normalize = function(f)
{
    return (Math.abs(f) < 0.000001) ? 0.0 : f;
}

var setButtons = function(dsp, value)
{
    var buttons = dsp.buttons();
    for (var i = 0; i < buttons.length; i++) {
         dsp.setParamValue(buttons[i], value);
    }
}

var fs = require('fs');

var buffer_size = 64;
var sample_rate = 44100;
var inputs = [];
var outputs = [];
var nbsamples = 60000;
var linenum = 0;
var run = 0;
var control_data;

// Creates DSP and buffers
var DSP = faust.mydsp(buffer_size, sample_rate);
create(DSP.getNumInputs(), DSP.getNumOutputs(), buffer_size);

//console.log(DSP);
//console.log(DSP.getNumInputs());
//console.log(DSP.getNumOutputs());
//console.log(DSP.json());
//console.log(DSP.buttons());
//console.log(control_data);
//console.log(DSP.controls());

// Write output file header
console.log("number_of_inputs  : ", DSP.getNumInputs());
console.log("number_of_outputs : ", DSP.getNumOutputs());
console.log("number_of_frames  : ", nbsamples);

// Check getSampleRate
if (DSP.getSampleRate() !== sample_rate) {
    console.error("ERROR in getSampleRate");
    process.exit(1);
}

// Check setParamValue/getParamValue
var path_table = DSP.controls();
for (var i = 0; i < path_table.length; i++) {
    DSP.setParamValue1(path_table[i], 0.1234);
    if (DSP.getParamValue(path_table[i]) !== 0.1234) {
        console.error("ERROR in setParamValue/getParamValue for " + path_table[i] + " " + DSP.getParamValue(path_table[i]));
        process.exit(1);
    }
}

// Check default after 'instanceResetUserInterface'
DSP.initRandom();
DSP.instanceResetUserInterface();
if (!DSP.checkDefaults()) {
    console.error("ERROR in checkDefaults after 'instanceResetUserInterface'");
    process.exit(1);
}

// Check default after 'instanceInit'
DSP.initRandom();
DSP.instanceInit();
if (!DSP.checkDefaults()) {
    console.error("ERROR in checkDefaults after 'instanceInit'");
    process.exit(1);
}

// Check default after 'init'
DSP.initRandom();
DSP.init(sample_rate);
if (!DSP.checkDefaults()) {
    console.error("ERROR in checkDefaults after 'init'");
    process.exit(1);
}

DSP.init(sample_rate);

// Read control parameters
try {
    control_data = fs.readFileSync('mydsprc', 'utf8');
    var lines = control_data.split('\n');
    for (var line = 0; line < lines.length; line++) {
        var param = lines[line].split(' ');
        DSP.setParamValue('/'+ param[1], parseFloat(param[0]));
    }
} catch (e) {}

// Compute samples and write output file
while (nbsamples > 0) {
    if (run === 0) {
        impulse(DSP.getNumInputs(), buffer_size);
        setButtons(DSP, 1.0);
    }
    if (run === 1) {
        zero(DSP.getNumInputs(), buffer_size);
        setButtons(DSP, 0.0);
    }
    var nFrames = Math.min(buffer_size, nbsamples);
    DSP.compute(inputs, outputs);
    run++;
    for (var i = 0; i < nFrames; i++) {
        var line = (linenum++) + " : ";
        for (var c = 0; c < DSP.getNumOutputs(); c++) {
            var f = normalize(outputs[c][i]);
            line = line + f + " ";
        }
        console.log(line);
    }
    nbsamples -= nFrames;
}
