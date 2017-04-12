/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
/*  SHA-1 implementation in JavaScript | (c) Chris Veness 2002-2013 | www.movable-type.co.uk      */
/*   - see http://csrc.nist.gov/groups/ST/toolkit/secure_hashing.html                             */
/*         http://csrc.nist.gov/groups/ST/toolkit/examples.html                                   */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

var Sha1 = {};  // Sha1 namespace

/**
 * Generates SHA-1 hash of string
 *
 * @param {String} msg                String to be hashed
 * @param {Boolean} [utf8encode=true] Encode msg as UTF-8 before generating hash
 * @returns {String}                  Hash of msg as hex character string
 */
Sha1.hash = function(msg, utf8encode) {
    utf8encode =  (typeof utf8encode == 'undefined') ? true : utf8encode;
    
    // convert string to UTF-8, as SHA only deals with byte-streams
    if (utf8encode) msg = Utf8.encode(msg);
    
    // constants [§4.2.1]
    var K = [0x5a827999, 0x6ed9eba1, 0x8f1bbcdc, 0xca62c1d6];
    
    // PREPROCESSING 
    
    msg += String.fromCharCode(0x80);  // add trailing '1' bit (+ 0's padding) to string [§5.1.1]
    
    // convert string msg into 512-bit/16-integer blocks arrays of ints [§5.2.1]
    var l = msg.length/4 + 2;  // length (in 32-bit integers) of msg + ‘1’ + appended length
    var N = Math.ceil(l/16);   // number of 16-integer-blocks required to hold 'l' ints
    var M = new Array(N);
    
    for (var i=0; i<N; i++) {
        M[i] = new Array(16);
        for (var j=0; j<16; j++) {  // encode 4 chars per integer, big-endian encoding
            M[i][j] = (msg.charCodeAt(i*64+j*4)<<24) | (msg.charCodeAt(i*64+j*4+1)<<16) | 
            (msg.charCodeAt(i*64+j*4+2)<<8) | (msg.charCodeAt(i*64+j*4+3));
        } // note running off the end of msg is ok 'cos bitwise ops on NaN return 0
    }
    // add length (in bits) into final pair of 32-bit integers (big-endian) [§5.1.1]
    // note: most significant word would be (len-1)*8 >>> 32, but since JS converts
    // bitwise-op args to 32 bits, we need to simulate this by arithmetic operators
    M[N-1][14] = ((msg.length-1)*8) / Math.pow(2, 32); M[N-1][14] = Math.floor(M[N-1][14])
    M[N-1][15] = ((msg.length-1)*8) & 0xffffffff;
    
    // set initial hash value [§5.3.1]
    var H0 = 0x67452301;
    var H1 = 0xefcdab89;
    var H2 = 0x98badcfe;
    var H3 = 0x10325476;
    var H4 = 0xc3d2e1f0;
    
    // HASH COMPUTATION [§6.1.2]
    
    var W = new Array(80); var a, b, c, d, e;
    for (var i=0; i<N; i++) {
        
        // 1 - prepare message schedule 'W'
        for (var t=0;  t<16; t++) W[t] = M[i][t];
        for (var t=16; t<80; t++) W[t] = Sha1.ROTL(W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16], 1);
        
        // 2 - initialise five working variables a, b, c, d, e with previous hash value
        a = H0; b = H1; c = H2; d = H3; e = H4;
        
        // 3 - main loop
        for (var t=0; t<80; t++) {
            var s = Math.floor(t/20); // seq for blocks of 'f' functions and 'K' constants
            var T = (Sha1.ROTL(a,5) + Sha1.f(s,b,c,d) + e + K[s] + W[t]) & 0xffffffff;
            e = d;
            d = c;
            c = Sha1.ROTL(b, 30);
            b = a;
            a = T;
        }
        
        // 4 - compute the new intermediate hash value
        H0 = (H0+a) & 0xffffffff;  // note 'addition modulo 2^32'
        H1 = (H1+b) & 0xffffffff; 
        H2 = (H2+c) & 0xffffffff; 
        H3 = (H3+d) & 0xffffffff; 
        H4 = (H4+e) & 0xffffffff;
    }
    
    return Sha1.toHexStr(H0) + Sha1.toHexStr(H1) + 
    Sha1.toHexStr(H2) + Sha1.toHexStr(H3) + Sha1.toHexStr(H4);
}

//
// function 'f' [§4.1.1]
//
Sha1.f = function(s, x, y, z)  {
    switch (s) {
        case 0: return (x & y) ^ (~x & z);           // Ch()
        case 1: return x ^ y ^ z;                    // Parity()
        case 2: return (x & y) ^ (x & z) ^ (y & z);  // Maj()
        case 3: return x ^ y ^ z;                    // Parity()
    }
}

//
// rotate left (circular left shift) value x by n positions [§3.2.5]
//
Sha1.ROTL = function(x, n) {
    return (x<<n) | (x>>>(32-n));
}

//
// hexadecimal representation of a number 
//   (note toString(16) is implementation-dependant, and  
//   in IE returns signed numbers when used on full words)
//
Sha1.toHexStr = function(n) {
    var s="", v;
    for (var i=7; i>=0; i--) { v = (n>>>(i*4)) & 0xf; s += v.toString(16); }
    return s;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
/*  Utf8 class: encode / decode between multi-byte Unicode characters and UTF-8 multiple          */
/*              single-byte character encoding (c) Chris Veness 2002-2013                         */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

var Utf8 = {};  // Utf8 namespace

/**
 * Encode multi-byte Unicode string into utf-8 multiple single-byte characters 
 * (BMP / basic multilingual plane only)
 *
 * Chars in range U+0080 - U+07FF are encoded in 2 chars, U+0800 - U+FFFF in 3 chars
 *
 * @param {String} strUni Unicode string to be encoded as UTF-8
 * @returns {String} encoded string
 */
Utf8.encode = function(strUni) {
    // use regular expressions & String.replace callback function for better efficiency 
    // than procedural approaches
    var strUtf = strUni.replace(
                                /[\u0080-\u07ff]/g,  // U+0080 - U+07FF => 2 bytes 110yyyyy, 10zzzzzz
                                function(c) { 
                                var cc = c.charCodeAt(0);
                                return String.fromCharCode(0xc0 | cc>>6, 0x80 | cc&0x3f); }
                                );
    strUtf = strUtf.replace(
                            /[\u0800-\uffff]/g,  // U+0800 - U+FFFF => 3 bytes 1110xxxx, 10yyyyyy, 10zzzzzz
                            function(c) { 
                            var cc = c.charCodeAt(0); 
                            return String.fromCharCode(0xe0 | cc>>12, 0x80 | cc>>6&0x3F, 0x80 | cc&0x3f); }
                            );
    return strUtf;
}

/**
 * Decode utf-8 encoded string back into multi-byte Unicode characters
 *
 * @param {String} strUtf UTF-8 string to be decoded back to Unicode
 * @returns {String} decoded string
 */
Utf8.decode = function(strUtf) {
    // note: decode 3-byte chars first as decoded 2-byte strings could appear to be 3-byte char!
    var strUni = strUtf.replace(
                                /[\u00e0-\u00ef][\u0080-\u00bf][\u0080-\u00bf]/g,  // 3-byte chars
                                function(c) {  // (note parentheses for precence)
                                var cc = ((c.charCodeAt(0)&0x0f)<<12) | ((c.charCodeAt(1)&0x3f)<<6) | ( c.charCodeAt(2)&0x3f); 
                                return String.fromCharCode(cc); }
                                );
    strUni = strUni.replace(
                            /[\u00c0-\u00df][\u0080-\u00bf]/g,                 // 2-byte chars
                            function(c) {  // (note parentheses for precence)
                            var cc = (c.charCodeAt(0)&0x1f)<<6 | c.charCodeAt(1)&0x3f;
                            return String.fromCharCode(cc); }
                            );
    return strUni;
}

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

// Shim AudioContext on webkit
window.AudioContext = window.AudioContext || window.webkitAudioContext || undefined;

faust.createWasmCDSPFactoryFromString = Module.cwrap('createWasmCDSPFactoryFromString', 'number', ['number', 'number', 'number', 'number', 'number', 'number']);
faust.expandCDSPFromString = Module.cwrap('expandCDSPFromString', 'number', ['number', 'number', 'number', 'number', 'number', 'number']);
faust.getCLibFaustVersion = Module.cwrap('getCLibFaustVersion', 'number', []);
faust.getWasmCModule = Module.cwrap('getWasmCModule', 'number', ['number']);
faust.getWasmCModuleSize = Module.cwrap('getWasmCModuleSize', 'number', ['number']);
faust.getWasmCHelpers = Module.cwrap('getWasmCHelpers', 'number', ['number']);
faust.freeCWasmModule = Module.cwrap('freeCWasmModule', null, ['number']);

faust.error_msg = null;
faust.factory_number = 0;
faust.factory_table = [];

faust.getErrorMessage = function() { return faust.error_msg; };

faust.createDSPFactoryAux = function (code, argv, callback, internal_memory) {

    var sha_key = Sha1.hash(code, true);
    var factory = faust.factory_table[sha_key];
    if (factory) {
        console.log("Existing library : " + factory.name);
        // Existing factory, do not create it...
        callback(factory);
        return;
    }
    
    console.log("libfaust.js version : " + Pointer_stringify(faust.getCLibFaustVersion()));
    
    // Allocate strings on the HEAP
    var factory_name = "mydsp" + faust.factory_number++;
    var code_ptr = Module._malloc(code.length + 1);
    var name = "FaustDSP";
    var name_ptr = Module._malloc(name.length + 1);
    var error_msg_ptr = Module._malloc(4096);
    
    Module.stringToUTF8(name, name_ptr, lengthBytesUTF8(name) + 1);
    Module.stringToUTF8(code, code_ptr, lengthBytesUTF8(code) + 1);
     
    // Add 'cn' option with the factory name
    argv = (argv === undefined) ? new Array() : argv;
    argv.push("-cn", factory_name);
    
    // Prepare 'argv' array for C side
    var ptr_size = 4; 
    var argv_ptr = Module._malloc(argv.length * ptr_size);  // Get buffer from emscripten.
    var argv_ptr_buffer = new Int32Array(Module.HEAP32.buffer, argv_ptr, argv.length);  // Get a integer view on the newly allocated buffer.
    for (var i = 0; i < argv.length; i++) {
        var arg_ptr = Module._malloc(argv[i].length + 1);
        Module.stringToUTF8(argv[i], arg_ptr, lengthBytesUTF8(argv[i]) + 1);
        argv_ptr_buffer[i] = arg_ptr; 
    }
     
    var module_code_ptr = faust.createWasmCDSPFactoryFromString(name_ptr, code_ptr, argv.length, argv_ptr, error_msg_ptr, internal_memory);
    faust.error_msg = Pointer_stringify(error_msg_ptr);
    
    if (module_code_ptr === 0) {
        callback(null);
    } else {
        
        var factory_code_ptr = faust.getWasmCModule(module_code_ptr);
        var factory_code_size = faust.getWasmCModuleSize(module_code_ptr);
     
        // Copy native 'binary' string in JavaScript Uint8Array
        var factory_code = new Uint8Array(factory_code_size);
        for (var i = 0; i < factory_code_size; i++) {
            // faster than 'getValue' which gets the type of access for each read...
            factory_code[i] = HEAP8[((factory_code_ptr + i) >> 0)];
        }
        
        var helpers_code_ptr = faust.getWasmCHelpers(module_code_ptr);
        var helpers_code = Pointer_stringify(helpers_code_ptr);
        
        // Free strings
        Module._free(code_ptr);
        Module._free(name_ptr);
        Module._free(error_msg_ptr);
        
        // Free C allocated wasm module
        faust.freeCWasmModule(module_code_ptr);
        
        // Free 'argv' C side array
        for (var i = 0; i < argv.length; i++) {
            Module._free(argv_ptr_buffer[i]);
        }
        Module._free(argv_ptr);
    
        faust.readDSPFactoryFromMachineAux(factory_name, factory_code, helpers_code, sha_key, callback);
    }
};

faust.createDSPFactory = function (code, argv, callback) {
    faust.createDSPFactoryAux(code, argv, callback, true);
}

faust.createPolyDSPFactory = function (code, argv, callback) {
    faust.createDSPFactoryAux(code, argv, callback, false);
}

faust.expandDSP = function (code, argv) {
   
    console.log("libfaust.js version : " + Pointer_stringify(faust.getCLibFaustVersion()));
    
    // Force "ajs" compilation
    argv.push("-lang");
    argv.push("ajs");
    
    // Allocate strings on the HEAP
    var code_ptr = Module._malloc(code.length + 1);
    var name = "FaustDSP";
    var name_ptr = Module._malloc(name.length + 1);
    var sha_key_ptr = Module._malloc(64);
    var error_msg_ptr = Module._malloc(4096);
    
    Module.stringToUTF8(name, name_ptr, lengthBytesUTF8(name) + 1);
    Module.stringToUTF8(code, code_ptr, lengthBytesUTF8(code) + 1);
    
    // Add 'cn' option with the factory name
    argv = (argv === undefined) ? new Array() : argv;
    
    // Prepare 'argv' array for C side
    var ptr_size = 4;
    var argv_ptr = Module._malloc(argv.length * ptr_size);  // Get buffer from emscripten.
    var argv_ptr_buffer = new Int32Array(Module.HEAP32.buffer, argv_ptr, argv.length);  // Get a integer view on the newly allocated buffer.
    for (var i = 0; i < argv.length; i++) {
        var arg_ptr = Module._malloc(argv[i].length + 1);
        Module.stringToUTF8(argv[i], arg_ptr, lengthBytesUTF8(argv[i]) + 1);
        argv_ptr_buffer[i] = arg_ptr;
    }
    
    var expand_dsp_ptr = faust.expandCDSPFromString(name_ptr, code_ptr, argv.length, argv_ptr, sha_key_ptr, error_msg_ptr);
    var expand_dsp = Pointer_stringify(expand_dsp_ptr);
    var sha_key = Pointer_stringify(sha_key_ptr);
    faust.error_msg = Pointer_stringify(error_msg_ptr);
    
    // Free strings
    Module._free(code_ptr);
    Module._free(name_ptr);
    Module._free(sha_key_ptr);
    Module._free(error_msg_ptr);
    
    // Free C allocated asm.js module
    faust.freeCDSP(expand_dsp_ptr);
    
    // Free 'argv' C side array
    for (var i = 0; i < argv.length; i++) {
        Module._free(argv_ptr_buffer[i]);
    }
    Module._free(argv_ptr);

    return expand_dsp;
};

faust.writeDSPFactoryToMachine = function (factory)
{
    return { name : factory.name, code : factory.code, helpers : factory.helpers };
}

faust.readDSPFactoryFromMachine = function (machine, callback)
{
    var sha_key = Sha1.hash(machine.code, true);
    var factory = faust.factory_table[sha_key];
    if (factory) {
        // Existing factory, do not create it...
        callback(factory);
    } else {
        faust.readDSPFactoryFromMachineAux(machine.name, machine.code, machine.helpers, sha_key, callback);
    }
}

faust.readDSPFactoryFromMachineAux = function (factory_name, factory_code, helpers_code, sha_key, callback)
{
    WebAssembly.compile(factory_code)
    .then(module => {
          
      var factory = {};
      
      factory.code = factory_code;
      factory.helpers = helpers_code;
      factory.module = module;
      
      // 'libfaust.js' wasm backend generates UI methods, then we compile the code
      eval(helpers_code);
 
      var path_table_function = eval("getPathTable" + factory_name);
      factory.pathTable = path_table_function();
          
      factory.getJSON = eval("getJSON" + factory_name);
      factory.metadata = eval("metadata" + factory_name);
      factory.getSize = eval("getSize" + factory_name);
          
      factory.name = factory_name;
      factory.sha_key = sha_key;
      faust.factory_table[sha_key] = factory;
 
      callback(factory);
    });
}

faust.deleteDSPFactory = function (factory) { faust.factory_table[factory.sha_key] = null; };

// 'mono' DSP
faust.createDSPInstance = function (factory, context, buffer_size, callback) {
    
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
    
    WebAssembly.instantiate(factory.module, importObject)
    .then(instance => {
    
        var sp = context.createScriptProcessor(buffer_size, instance.exports.getNumInputs(0), instance.exports.getNumOutputs(0));
        
        sp.handler = null;
        sp.ins = null;
        sp.outs = null;
       
        sp.dspInChannnels = [];
        sp.dspOutChannnels = [];

        // bargraph
        sp.ouputs_timer = 5;
        sp.ouputs_items = [];
         
        // input items
        sp.inputs_items = [];
        
        // Allocate table for 'setParamValue'
        sp.value_table = [];
        
        // Memory allocator
        sp.ptr_size = 4;
        sp.sample_size = 4;
        
        // Start of DSP memory : DSP is placed first with index 0
        sp.dsp = 0;
        
        sp.HEAP = instance.exports.memory.buffer;
        sp.HEAP32 = new Int32Array(sp.HEAP);
        sp.HEAPF32 = new Float32Array(sp.HEAP);
        
        // Start of HEAP index
        
        sp.numIn = instance.exports.getNumInputs(sp.dsp);
        sp.numOut = instance.exports.getNumOutputs(sp.dsp);
        
        // DSP is placed first with index 0. Audio buffer start at the end od DSP.
        sp.audio_heap_ptr = factory.getSize();
        
        // Setup pointers offset
        sp.audio_heap_ptr_inputs = sp.audio_heap_ptr;
        sp.audio_heap_ptr_outputs = sp.audio_heap_ptr_inputs + (sp.numIn * sp.ptr_size);
        
        // Setup buffer offset
        sp.audio_heap_inputs = sp.audio_heap_ptr_outputs + (sp.numOut * sp.ptr_size);
        sp.audio_heap_outputs = sp.audio_heap_inputs + (sp.numIn * buffer_size * sp.sample_size);
       
        sp.update_outputs = function ()
        {
            if (sp.ouputs_items.length > 0 &&  sp.handler && sp.ouputs_timer-- === 0) {
                sp.ouputs_timer = 5;
                for (var i = 0; i < sp.ouputs_items.length; i++) {
                    sp.handler(sp.ouputs_items[i], instance.exports.getParamValue(sp.dsp, factory.pathTable[sp.ouputs_items[i]]));
                }
            }
        }
      
        sp.compute = function (e) 
        {
            var i, j;
             
            // Read inputs
            for (i = 0; i < sp.numIn; i++) {
                var input = e.inputBuffer.getChannelData(i);
                var dspInput = sp.dspInChannnels[i];
                for (j = 0; j < input.length; j++) {
                    dspInput[j] = input[j];
                }
            }
            
            // Update control state
            for (i = 0; i < sp.inputs_items.length; i++) {
                var path = sp.inputs_items[i];
                var values = sp.value_table[path];
                instance.exports.setParamValue(sp.dsp, factory.pathTable[path], values[0]);
                values[0] = values[1];
            }

            // Compute
            instance.exports.compute(sp.dsp, buffer_size, sp.ins, sp.outs);
           
            // Update bargraph
            sp.update_outputs();

            // Write outputs
            for (i = 0; i < sp.numOut; i++) {
                var output = e.outputBuffer.getChannelData(i);
                var dspOutput = sp.dspOutChannnels[i];
                for (j = 0; j < output.length; j++) {
                    output[j] = dspOutput[j];
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
            if (item.type === "vgroup" || item.type === "hgroup" || item.type === "tgroup") {
                sp.parse_items(item.items);
            } else if (item.type === "hbargraph" || item.type === "vbargraph") {
                // Keep bargraph adresses
                sp.ouputs_items.push(item.address);
            } else if (item.type === "vslider" || item.type === "hslider" || item.type === "button" || item.type === "checkbox" || item.type === "nentry") {
                // Keep inputs adresses
                sp.inputs_items.push(item.address);
            }
        }
        
        sp.initAux = function ()
        {
            // Setup web audio context
            var i;
            
            // Setup web audio context
            console.log("buffer_size %d", buffer_size);
            sp.onaudioprocess = sp.compute;
        
            if (sp.numIn > 0) {
                //ins = Module._malloc(ptr_size * numIn);
                sp.ins = sp.audio_heap_ptr_inputs;
                for (i = 0; i < sp.numIn; i++) {
                    sp.HEAP32[(sp.ins >> 2) + i] = sp.audio_heap_inputs + ((buffer_size * sp.sample_size) * i);
                }

                // Prepare Ins buffer tables
                var dspInChans = sp.HEAP32.subarray(sp.ins >> 2, (sp.ins + sp.numIn * sp.ptr_size) >> 2);
                for (i = 0; i < sp.numIn; i++) {
                    sp.dspInChannnels[i] = sp.HEAPF32.subarray(dspInChans[i] >> 2, (dspInChans[i] + buffer_size * sp.sample_size) >> 2);
                }
            }
          
            if (sp.numOut > 0) {
                //outs = Module._malloc(ptr_size * numOut);
                sp.outs = sp.audio_heap_ptr_outputs;
                for (i = 0; i < sp.numOut; i++) {
                    sp.HEAP32[(sp.outs >> 2) + i] = sp.audio_heap_outputs + ((buffer_size * sp.sample_size) * i);
                }
          
                // Prepare Out buffer tables
                var dspOutChans = sp.HEAP32.subarray(sp.outs >> 2, (sp.outs + sp.numOut * sp.ptr_size) >> 2);
                for (i = 0; i < sp.numOut; i++) {
                    sp.dspOutChannnels[i] = sp.HEAPF32.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + buffer_size * sp.sample_size) >> 2);
                }
            }
          
            // bargraph
            sp.parse_ui(JSON.parse(factory.getJSON()).ui);
        
            // Init DSP
            instance.exports.init(sp.dsp, context.sampleRate);
          
             // Init 'value' table
            for (var i = 0; i < sp.inputs_items.length; i++) {
                var path = sp.inputs_items[i];
                var values = new Float32Array(2);
                values[0] = values[1] = instance.exports.getParamValue(sp.dsp, factory.pathTable[path]);
                sp.value_table[path] = values;
            }
        }
        
        sp.getNumInputs = function ()
        {
            return instance.exports.getNumInputs(sp.dsp);
        }
        
        sp.getNumOutputs = function ()
        {
            return instance.exports.getNumOutputs(sp.dsp);
        }
        
        sp.init = function (sample_rate)
        {
            instance.exports.init(sp.dsp, sample_rate);
        }
        
        sp.instanceInit  = function (sample_rate)
        {
            instance.exports.instanceInit(sp.dsp, sample_rate);
        }
        
        sp.instanceConstants  = function (sample_rate)
        {
            instance.exports.instanceConstants(sp.dsp, sample_rate);
        }
        
        sp.instanceResetUserInterface = function ()
        {
            instance.exports.instanceResetUserInterface(sp.dsp);
        }
        
        sp.instanceClear = function ()
        {
            instance.exports.instanceClear(sp.dsp);
        }
     
        sp.setHandler = function (hd)
        {
            sp.handler = hd;
        }
         
        sp.setParamValue = function (path, val)
        {
            var values = sp.value_table[path];
            if (values) {
                if (instance.exports.getParamValue(sp.dsp, factory.pathTable[path]) == values[0]) {
                    values[0] = val;
                } 
                values[1] = val;
            }
        }
        
        sp.getParamValue = function (path)
        {
            return instance.exports.getParamValue(sp.dsp, factory.pathTable[path]);
        }
        
        sp.controls = function()
        {
            return inputs_items;
        }
        
        sp.json = function ()
        {
            return factory.getJSON();
        }
        
        // Init resulting DSP
        sp.initAux();
        
        // Call continuation
        callback(sp);
           
}); };

faust.deleteDSPInstance = function (dsp) {}

faust.createMemory = function (factory, buffer_size, max_polyphony) {
    
    // Memory allocator
    var ptr_size = 4;
    var sample_size = 4;
    
    function pow2limit(x)
    {
        var n = 2;
        while (n < x) { n = 2 * n; }
        return (n < 65536) ? 65536 : n; // Minimum = 64 kB
    }
    
    // Keep JSON parsed object
    var jon_object = JSON.parse(factory.getJSON());
    
    function getNumInputsAux ()
    {
        return (jon_object.inputs !== undefined) ? parseInt(jon_object.inputs) : 0;
    }
    
    function getNumOutputsAux ()
    {
        return (jon_object.outputs !== undefined) ? parseInt(jon_object.outputs) : 0;
    }
    
    var memory_size = pow2limit(factory.getSize() * max_polyphony + ((getNumInputsAux() + getNumOutputsAux() * 2) * (ptr_size + (buffer_size * sample_size)))) / 65536;
    return new WebAssembly.Memory({initial:memory_size, maximum:memory_size});
}

// 'poly' DSP
faust.createPolyDSPInstance = function (factory, context, buffer_size, max_polyphony, callback) {
    
    var memory = faust.createMemory(factory, buffer_size, max_polyphony);
    
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
    
    var mixObject = { imports: { print: arg => console.log(arg) } }
    mixObject["memory"] = { "memory": memory};
    
    var importObject = { imports: { print: arg => console.log(arg) } }
    importObject["global.Math"] = window.Math;
    importObject["asm2wasm"] = asm2wasm;
    importObject["memory"] = { "memory": memory};
    
    fetch('mixer32.wasm')
    .then(mix_res => mix_res.arrayBuffer())
    .then(mix_bytes => WebAssembly.instantiate(mix_bytes, mixObject))
    .then(mix_module =>  // mix_module.instance
          
    function ()
    {
        WebAssembly.instantiate(factory.module, importObject)
        .then(dsp_instance => {
           
        // Keep JSON parsed object
        var jon_object = JSON.parse(factory.getJSON());
          
        function getNumInputsAux ()
        {
            return (jon_object.inputs !== undefined) ? parseInt(jon_object.inputs) : 0;
        }
          
        function getNumOutputsAux ()
        {
            return (jon_object.outputs !== undefined) ? parseInt(jon_object.outputs) : 0;
        }
      
        var sp = context.createScriptProcessor(buffer_size, getNumInputsAux(), getNumOutputsAux());
        sp.jon_object = jon_object;
      
        sp.handler = null;
        sp.ins = null;
        sp.outs = null
        sp.mixing = null;
        sp.compute_callback = null;
              
        sp.dspInChannnels = [];
        sp.dspOutChannnels = [];
              
        sp.fFreqLabel = "";
        sp.fGateLabel = "";
        sp.fGainLabel = "";
        sp.fDate = 0;
              
        sp.numIn = getNumInputsAux();
        sp.numOut = getNumOutputsAux();
          
        // Memory allocator
        sp.ptr_size = 4;
        sp.sample_size = 4;
          
        sp.factory = dsp_instance.exports;
        sp.HEAP = memory.buffer;
        sp.HEAP32 = new Int32Array(sp.HEAP);
        sp.HEAPF32 = new Float32Array(sp.HEAP);
      
        // bargraph
        sp.ouputs_timer = 5;
        sp.ouputs_items = [];
         
        // input items
        sp.inputs_items = [];
      
        // Start of HEAP index
        sp.audio_heap_ptr = 0;

        // Setup pointers offset
        sp.audio_heap_ptr_inputs = sp.audio_heap_ptr;
        sp.audio_heap_ptr_outputs = sp.audio_heap_ptr_inputs + (getNumInputsAux() * sp.ptr_size);
        sp.audio_heap_ptr_mixing = sp.audio_heap_ptr_outputs + (getNumOutputsAux() * sp.ptr_size);

        // Setup buffer offset
        sp.audio_heap_inputs = sp.audio_heap_ptr_mixing + (getNumOutputsAux() * sp.ptr_size);
        sp.audio_heap_outputs = sp.audio_heap_inputs + (getNumInputsAux() * buffer_size * sp.sample_size);
        sp.audio_heap_mixing = sp.audio_heap_outputs + (getNumOutputsAux() * buffer_size * sp.sample_size);

        // Setup DSP voices offset
        sp.dsp_start = sp.audio_heap_mixing + (getNumOutputsAux() * buffer_size * sp.sample_size);
      
        // wasm mixer
        sp.mixer = mix_module.instance.exports;

        // Start of DSP memory ('polyphony' DSP voices)
        sp.dsp_voices = [];
        sp.dsp_voices_state = [];
        sp.dsp_voices_level = [];
        sp.dsp_voices_date = [];
        sp.dsp_voices_trigger = [];

        sp.kActiveVoice = 0;
        sp.kFreeVoice = -1;
        sp.kReleaseVoice = -2;
        sp.kNoVoice = -3;

        sp.pathTable = factory.pathTable;
    
        for (var i = 0; i < max_polyphony; i++) {
            sp.dsp_voices[i] = sp.dsp_start + i * factory.getSize();
            sp.dsp_voices_state[i] = sp.kFreeVoice;
            sp.dsp_voices_level[i] = 0;
            sp.dsp_voices_date[i] = 0;
            sp.dsp_voices_trigger[i] = false;
        }

        // Always returns a voice
        sp.newVoiceAux = function ()
        {
            var voice = sp.getVoice(sp.kFreeVoice, true);
            sp.dsp_voices_state[voice] = sp.kActiveVoice;
            return voice;
        }
    
        sp.getVoice = function(note, steal)
        {
            for (var i = 0; i < max_polyphony; i++) {
                if (sp.dsp_voices_state[i] === note) {
                    if (steal) { sp.dsp_voices_date[i] = sp.fDate++; }
                    return i;
                }
            }

            if (steal) {
                var voice_release = sp.kNoVoice;
                var voice_playing = sp.kNoVoice;
                var oldest_date_release = Number.MAX_VALUE;
                var oldest_date_playing = Number.MAX_VALUE;

                // Scan all voices
                for (var i = 0; i < max_polyphony; i++) {
                    // Try to steal a voice in kReleaseVoice mode...
                    if (sp.dsp_voices_state[i] === sp.kReleaseVoice) {
                        // Keeps oldest release voice
                        if (sp.dsp_voices_date[i] < oldest_date_release) {
                            oldest_date_release = sp.dsp_voices_date[i];
                            voice_release = i;
                        }
                    } else {
                        if (sp.dsp_voices_date[i] < oldest_date_playing) {
                            oldest_date_playing = sp.dsp_voices_date[i];
                            voice_playing = i;
                        }
                    }
                }

                // Then decide which one to steal
                if (oldest_date_release != Number.MAX_VALUE) {
                    console.log("Steal release voice : voice_date = %d cur_date = %d voice = %d\n", sp.dsp_voices_date[voice_release], sp.fDate, voice_release);
                    sp.dsp_voices_date[voice_release] = sp.fDate++;
                    sp.dsp_voices_trigger[voice_release] = true;
                    return voice_release;
                } else {
                    console.log("Steal playing voice : voice_date = %d cur_date = %d voice = %d\n", sp.dsp_voices_date[voice_playing], sp.fDate, voice_playing);
                    sp.dsp_voices_date[voice_playing] = sp.fDate++;
                    sp.dsp_voices_trigger[voice_playing] = true;
                    return voice_playing;
                }

            } else {
                return sp.kNoVoice;
            }
        }
     
        sp.update_outputs = function ()
        {
            if (sp.ouputs_items.length > 0 && sp.handler && sp.ouputs_timer-- === 0) {
                sp.ouputs_timer = 5;
                for (var i = 0; i < sp.ouputs_items.length; i++) {
                    sp.handler(sp.ouputs_items[i], sp.factory.getParamValue(sp.dsp_voices[0], sp.pathTable[sp.ouputs_items[i]]));
                }
            }
        }
 
        sp.compute = function (e)
        {
            var i, j;
             
            // Read inputs
            for (i = 0; i < sp.numIn; i++) {
                var input = e.inputBuffer.getChannelData(i);
                var dspInput = sp.dspInChannnels[i];
                for (j = 0; j < input.length; j++) {
                    dspInput[j] = input[j];
                }
            }

            // Possibly call an externally given callback (for instance to play a MIDIFile...)
            if (sp.compute_callback) {
                sp.compute_callback(buffer_size);
            }
        
            // First clear the outputs
            sp.mixer.clearOutput(buffer_size, sp.numOut, sp.outs);

            // Compute all running voices
            for (i = 0; i < max_polyphony; i++) {
                if (sp.dsp_voices_state[i] != sp.kFreeVoice) {
                    if (sp.dsp_voices_trigger[i]) {
                        // FIXME : properly cut the buffer in 2 slices...
                        sp.factory.setParamValue(sp.dsp_voices[i], sp.fGateLabel, 0.0);
                        sp.factory.compute(sp.dsp_voices[i], 1, sp.ins, sp.mixing);
                        sp.factory.setParamValue(sp.dsp_voices[i], sp.fGateLabel, 1.0);
                        sp.factory.compute(sp.dsp_voices[i], buffer_size, sp.ins, sp.mixing);
                        sp.dsp_voices_trigger[i] = false;
                    } else {
                        // Compute regular voice
                        sp.factory.compute(sp.dsp_voices[i], buffer_size, sp.ins, sp.mixing);
                    }
                    // Mix it in result
                    sp.dsp_voices_level[i] = sp.mixer.mixVoice(buffer_size, sp.numOut, sp.mixing, sp.outs);
                    // Check the level to possibly set the voice in kFreeVoice again
                    if ((sp.dsp_voices_level[i] < 0.001) && (sp.dsp_voices_state[i] === sp.kReleaseVoice)) {
                        sp.dsp_voices_state[i] = sp.kFreeVoice;
                    }
                }
            }

            // Update bargraph
            sp.update_outputs();

            // Write outputs
            for (i = 0; i < sp.numOut; i++) {
                var output = e.outputBuffer.getChannelData(i);
                var dspOutput = sp.dspOutChannnels[i];
                for (j = 0; j < output.length; j++) {
                    output[j] = dspOutput[j];
                }
            }
        }
    
        sp.midiToFreq = function (note)
        {
            return 440.0 * Math.pow(2.0, (note - 69.0) / 12.0);
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
            if (item.type === "vgroup" || item.type === "hgroup" || item.type === "tgroup") {
                sp.parse_items(item.items);
            } else if (item.type === "hbargraph" || item.type === "vbargraph") {
                // Keep bargraph adresses
                sp.ouputs_items.push(item.address);
            } else if (item.type === "vslider" || item.type === "hslider" || item.type === "button" || item.type === "checkbox" || item.type === "nentry") {
                // Keep inputs adresses
                sp.inputs_items.push(item.address);
            }
        }
      
        sp.initAux = function ()
        {
            // Setup web audio context
            var i;
             
            // Setup web audio context
            console.log("buffer_size %d", buffer_size);
            sp.onaudioprocess = sp.compute;
        
            if (sp.numIn > 0) {
                sp.ins = sp.audio_heap_ptr_inputs;
                for (i = 0; i < sp.numIn; i++) {
                    sp.HEAP32[(sp.ins >> 2) + i] = sp.audio_heap_inputs + ((buffer_size * sp.sample_size) * i);
                }

                // Prepare Ins buffer tables
                var dspInChans = sp.HEAP32.subarray(sp.ins >> 2, (sp.ins + sp.numIn * ptr_size) >> 2);
                for (i = 0; i < sp.numIn; i++) {
                    sp.dspInChannnels[i] = sp.HEAPF32.subarray(dspInChans[i] >> 2, (dspInChans[i] + buffer_size * sp.sample_size) >> 2);
                }
            }
              
            if (sp.numOut > 0) {
              // allocate memory for output and mixing arrays
              sp.outs = sp.audio_heap_ptr_outputs;
              sp.mixing = sp.audio_heap_ptr_mixing;
              
              for (i = 0; i < sp.numOut; i++) {
                sp.HEAP32[(sp.outs >> 2) + i] = sp.audio_heap_outputs + ((buffer_size * sp.sample_size) * i);
                sp.HEAP32[(sp.mixing >> 2) + i] = sp.audio_heap_mixing + ((buffer_size * sp.sample_size) * i);
              }
              
              var dspOutChans = sp.HEAP32.subarray(sp.outs >> 2, (sp.outs + sp.numOut * sp.ptr_size) >> 2);
              for (i = 0; i < sp.numOut; i++) {
                    sp.dspOutChannnels[i] = sp.HEAPF32.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + buffer_size * sp.sample_size) >> 2);
              }
            }
       
            // bargraph
            sp.parse_ui(sp.jon_object.ui);
            
            // keep 'keyOn/keyOff' labels
            for (i = 0; i < sp.inputs_items.length; i++) {
                if (sp.inputs_items[i].endsWith("/gate")) {
                    sp.fGateLabel = sp.pathTable[sp.inputs_items[i]];
                    console.log(sp.fGateLabel);
                } else if (sp.inputs_items[i].endsWith("/freq")) {
                    sp.fFreqLabel = sp.pathTable[sp.inputs_items[i]];
                    console.log(sp.fFreqLabel);
                } else if (sp.inputs_items[i].endsWith("/gain")) {
                    sp.fGainLabel = sp.pathTable[sp.inputs_items[i]];
                    console.log(sp.fGainLabel);
                }
            }
            
            // Init DSP voices
            for (i = 0; i < max_polyphony; i++) {
                sp.factory.init(sp.dsp_voices[i], context.sampleRate);
            }
        }
          
        sp.getNumInputs = function ()
        {
            return getNumInputsAux();
        }

        sp.getNumOutputs = function ()
        {
            return getNumOutputsAux();
        }
        
        sp.init = function (sample_rate)
        {
            for (var i = 0; i < max_polyphony; i++) {
                sp.factory.init(sp.dsp_voices[i], sample_rate);
            }
        }

        sp.instanceInit = function (sample_rate)
        {
            for (var i = 0; i < max_polyphony; i++) {
                sp.factory.instanceInit(sp.dsp_voices[i], sample_rate);
            }
        }

        sp.instanceConstants = function (sample_rate)
        {
            for (var i = 0; i < max_polyphony; i++) {
                fsp.actory.instanceConstants(sp.dsp_voices[i], sample_rate);
            }
        }

        sp.instanceResetUserInterface = function ()
        {
            for (var i = 0; i < max_polyphony; i++) {
                sp.factory.instanceResetUserInterface(sp.dsp_voices[i]);
            }
        }

        sp.instanceClear = function ()
        {
            for (var i = 0; i < max_polyphony; i++) {
                sp.factory.instanceClear(sp.dsp_voices[i]);
            }
        }

        sp.setHandler = function (hd)
        {
            sp.handler = hd;
        }

        sp.keyOn = function (channel, pitch, velocity)
        {
            var voice = sp.newVoiceAux();
            //console.log("keyOn voice %d", voice);
            sp.factory.setParamValue(sp.dsp_voices[voice], sp.fFreqLabel, sp.midiToFreq(pitch));
            sp.factory.setParamValue(sp.dsp_voices[voice], sp.fGainLabel, velocity/127.);
            sp.dsp_voices_state[voice] = pitch;
            sp.dsp_voices_trigger[voice] = true; // so that envelop is always re-initialized
        }

        sp.keyOff = function (channel, pitch, velocity)
        {
            var voice = sp.getVoice(pitch, false);
            if (voice !== sp.kNoVoice) {
                //console.log("keyOff voice %d", voice);
                // No use of velocity for now...
                sp.factory.setParamValue(sp.dsp_voices[voice], sp.fGateLabel, 0.0);
                // Release voice
                sp.dsp_voices_state[voice] = sp.kReleaseVoice;
            } else {
                console.log("Playing voice not found...\n");
            }
        }

        sp.allNotesOff = function ()
        {
            for (var i = 0; i < max_polyphony; i++) {
                sp.factory.setParamValue(sp.dsp_voices[i], sp.fGateLabel, 0.0);
                sp.dsp_voices_state[i] = sp.kReleaseVoice;
            }
        }

        sp.ctrlChange = function (channel, ctrl, value)
        {
            if (ctrl === 123 || ctrl === 120) {
                sp.allNotesOff();
            }
        }

        sp.pitchWheel = function (channel, wheel)
        {}

        sp.setParamValue = function (path, val)
        {
            for (var i = 0; i < max_polyphony; i++) {
                sp.factory.setParamValue(sp.dsp_voices[i], sp.pathTable[path], val);
            }
        }

        sp.getParamValue = function (path)
        {
            return sp.factory.getParamValue(sp.dsp_voices[0], sp.pathTable[path]);
        }

        sp.controls = function()
        {
            return sp.inputs_items;
        }

        sp.json = function ()
        {
            return factory.getJSON();
        }

        sp.getSampleRate = function ()
        {
            return context.sampleRate;
        }
    
        sp.setComputeCallback = function (callback)
        {
            sp.compute_callback = callback;
        }
        
        sp.getComputeCallback = function ()
        {
            return sp.compute_callback;
        }
       
        // Init resulting DSP
        sp.initAux();
      
        // Call continuation
        callback(sp);
          
    }); } ());

}

faust.deletePolyDSPInstance = function (dsp) {}
 
