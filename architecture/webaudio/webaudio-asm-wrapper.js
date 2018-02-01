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
 
 Additional code : GRAME 2014-2015
*/

'use strict';

// asm.js mixer
function mydspMixer(global, foreign, buffer) {
	
    'use asm';

    var HEAP32 = new global.Int32Array(buffer);
    var HEAPF32 = new global.Float32Array(buffer);

    var max = global.Math.max;
    var abs = global.Math.abs;

    function clearOutput(count, channels, outputs) {
        count = count | 0;
        channels = channels | 0;
        outputs = outputs | 0;
        var i = 0;
        var j = 0;
        for (i = 0; ((i | 0) < (channels | 0) | 0); i = ((i | 0) + 1 | 0)) {
            for (j = 0; ((j | 0) < (count | 0) | 0); j = ((j | 0) + 1 | 0)) {
               HEAPF32[(HEAP32[outputs + ((i | 0) << 2) >> 2] | 0) + ((j | 0) << 2) >> 2] = 0.;
            }
        }
    }

    function mixVoice(count, channels, inputs, outputs) {
        count = count | 0;
        channels = channels | 0;
        inputs = inputs | 0;
        outputs = outputs | 0;
        var i = 0;
        var j = 0;
        var level = 0.;
        for (i = 0; ((i | 0) < (channels | 0) | 0); i = ((i | 0) + 1 | 0)) {
            for (j = 0; ((j | 0) < (count | 0) | 0); j = ((j | 0) + 1 | 0)) {
                level = max(+level, +(abs(+(HEAPF32[(HEAP32[inputs + ((i | 0) << 2) >> 2] | 0) + ((j | 0) << 2) >> 2]))));
                HEAPF32[(HEAP32[outputs + ((i | 0) << 2) >> 2] | 0) + ((j | 0) << 2) >> 2] 
                    = +(HEAPF32[(HEAP32[outputs + ((i | 0) << 2) >> 2] | 0) + ((j | 0) << 2) >> 2]) + 
                      +(HEAPF32[(HEAP32[inputs + ((i | 0) << 2) >> 2] | 0) + ((j | 0) << 2) >> 2]);
            }
        }
        return +level;
    }

    return { mixVoice: mixVoice, clearOutput: clearOutput};
}

var faust = faust || {};

Module.lengthBytesUTF8 = function(str) 
{
	var len=0;for(var i=0;i<str.length;++i){var u=str.charCodeAt(i);if(u>=55296&&u<=57343)u=65536+((u&1023)<<10)|str.charCodeAt(++i)&1023;if(u<=127){++len}else if(u<=2047){len+=2}else if(u<=65535){len+=3}else if(u<=2097151){len+=4}else if(u<=67108863){len+=5}else{len+=6}}return len;
}

// Shim AudioContext on webkit
window.AudioContext = window.AudioContext || window.webkitAudioContext || undefined;

faust.createAsmCDSPFactoryFromString = Module.cwrap('createAsmCDSPFactoryFromString', 'number', ['number', 'number', 'number', 'number', 'number']);
faust.expandCDSPFromString = Module.cwrap('expandCDSPFromString', 'number', ['number', 'number', 'number', 'number', 'number', 'number']);
faust.getCLibFaustVersion = Module.cwrap('getCLibFaustVersion', 'number', []);
faust.freeCMemory = Module.cwrap('freeCMemory', null, ['number']);

faust.error_msg = null;
faust.factory_number = 0;
faust.factory_table = [];

faust.getErrorMessage = function() { return faust.error_msg; };

faust.createDSPFactory = function (code, argv) {

    var sha_key = Sha1.hash(code, true);
    var factory = faust.factory_table[sha_key];
    if (factory) {
        // Existing factory, do not create it...
        return factory;
    }
    
    console.log("libfaust.js version : " + Pointer_stringify(faust.getCLibFaustVersion()));
    
    // Allocate strings on the HEAP
    var factory_name = "mydsp" + faust.factory_number++;
    var code_ptr = Module._malloc(code.length + 1);
    var name = "FaustDSP";
    var name_ptr = Module._malloc(name.length + 1);
    var error_msg_ptr = Module._malloc(4096);
    
    Module.stringToUTF8(name, name_ptr, Module.lengthBytesUTF8(name) + 1);
    Module.stringToUTF8(code, code_ptr, Module.lengthBytesUTF8(code) + 1);
     
    // Add 'cn' option with the factory name
    argv = (argv === undefined) ? new Array() : argv;
    argv.push("-cn", factory_name);
    
    // Prepare 'argv' array for C side
    var ptr_size = 4; 
    var argv_ptr = Module._malloc(argv.length * ptr_size);  // Get buffer from emscripten.
    var argv_ptr_buffer = new Int32Array(Module.HEAP32.buffer, argv_ptr, argv.length);  // Get a integer view on the newly allocated buffer.
    for (var i = 0; i < argv.length; i++) {
        var arg_ptr = Module._malloc(argv[i].length + 1);
        Module.stringToUTF8(argv[i], arg_ptr, Module.lengthBytesUTF8(argv[i]) + 1);
        argv_ptr_buffer[i] = arg_ptr; 
    }
     
    var factory_code_ptr = faust.createAsmCDSPFactoryFromString(name_ptr, code_ptr, argv.length, argv_ptr, error_msg_ptr);
    var factory_code = Pointer_stringify(factory_code_ptr);
    faust.error_msg = Pointer_stringify(error_msg_ptr);
    
    // Free strings
    Module._free(code_ptr);
    Module._free(name_ptr);
    Module._free(error_msg_ptr);
    
    // Free C allocated asm.js module
    faust.freeCMemory(factory_code_ptr);
    
    // Free 'argv' C side array
    for (var i = 0; i < argv.length; i++) {
        Module._free(argv_ptr_buffer[i]);
    }
    Module._free(argv_ptr);
    
    if (factory_code === "") {
        return null;
    } else {
        return faust.readDSPFactoryFromMachineAux(factory_name, factory_code, sha_key);
    }
};

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
    
    Module.stringToUTF8(name, name_ptr, Module.lengthBytesUTF8(name) + 1);
    Module.stringToUTF8(code, code_ptr, Module.lengthBytesUTF8(code) + 1);
    
    // Add 'cn' option with the factory name
    argv = (argv === undefined) ? new Array() : argv;
    
    // Prepare 'argv' array for C side
    var ptr_size = 4;
    var argv_ptr = Module._malloc(argv.length * ptr_size);  // Get buffer from emscripten.
    var argv_ptr_buffer = new Int32Array(Module.HEAP32.buffer, argv_ptr, argv.length);  // Get a integer view on the newly allocated buffer.
    for (var i = 0; i < argv.length; i++) {
        var arg_ptr = Module._malloc(argv[i].length + 1);
        Module.stringToUTF8(argv[i], arg_ptr, Module.lengthBytesUTF8(argv[i]) + 1);
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
    faust.freeCMemory(expand_dsp_ptr);
    
    // Free 'argv' C side array
    for (var i = 0; i < argv.length; i++) {
        Module._free(argv_ptr_buffer[i]);
    }
    Module._free(argv_ptr);

    return expand_dsp;
};

faust.writeDSPFactoryToMachine = function (factory)
{
    return { name : factory.name, code : factory.code };
}

faust.readDSPFactoryFromMachine = function (machine)
{
    var sha_key = Sha1.hash(machine.code, true);
    var factory = faust.factory_table[sha_key];
    if (factory) {
        // Existing factory, do not create it...
        return factory;
    } else {
        return faust.readDSPFactoryFromMachineAux(machine.name, machine.code, sha_key);
    }
}

faust.readDSPFactoryFromMachineAux = function (factory_name, factory_code, sha_key)
{
    // 'libfaust.js' asm.js backend generates the ASM module + UI method, then we compile the code
    eval(factory_code);

    // Compile the ASM module itself : 'buffer' is the emscripten global memory context
    var factory = eval(factory_name + "Module(window, window.Math, buffer)");
  
    var path_table_function = eval("getPathTable" + factory_name); 
    factory.pathTable = path_table_function();

    factory.getJSON = eval("getJSON" + factory_name);
    factory.metadata = eval("metadata" + factory_name);
    factory.getSize = eval("getSize" + factory_name);
    
    factory.name = factory_name;
    factory.sha_key = sha_key;
    factory.code = factory_code;
    
    faust.factory_table[sha_key] = factory;
    
    return factory;
}

faust.deleteDSPFactory = function (factory) { faust.factory_table[factory.sha_key] = null; };

// 'mono' DSP
faust.createDSPInstance = function (factory, context, buffer_size) {
 
    var dsp = Module._malloc(factory.getSize());
    var handler = null;
    var ins, outs;
    var numIn, numOut;
    
    var scriptProcessor; 
    
    var dspInChannnels = [];
    var dspOutChannnels = [];

    // bargraph
    var outputs_timer = 5;
    var outputs_items = [];
     
    // input items
    var inputs_items = [];
    
    // Allocate table for 'setParamValue'
    var value_table = [];
    
    function update_outputs () 
    {
        if (outputs_items.length > 0 && handler && outputs_timer-- === 0) {
            outputs_timer = 5;
            for (var i = 0; i < outputs_items.length; i++) {
                handler(outputs_items[i], factory.getParamValue(dsp, factory.pathTable[outputs_items[i]]));
            }
        }
    }
 
    function compute (e) 
    {
        var i, j;
         
        // Read inputs
        for (i = 0; i < numIn; i++) {
            var input = e.inputBuffer.getChannelData(i);
            var dspInput = dspInChannnels[i];
            for (j = 0; j < input.length; j++) {
                dspInput[j] = input[j];
            }
        }
        
        // Update control state
        for (i = 0; i < inputs_items.length; i++) {
            var path = inputs_items[i];
            var values = value_table[path];
            factory.setParamValue(dsp, factory.pathTable[path], values[0]);
            values[0] = values[1];
        }

        // Compute
        factory.compute(dsp, buffer_size, ins, outs);
       
        // Update bargraph
        update_outputs();

        // Write outputs
        for (i = 0; i < numOut; i++) {
            var output = e.outputBuffer.getChannelData(i);
            var dspOutput = dspOutChannnels[i];
            for (j = 0; j < output.length; j++) {
                output[j] = dspOutput[j];
            }
        }
    }
     
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
        for (var i = 0; i < items.length; i++) {
            parse_item(items[i]);
        }
    }
    
    function parse_item (item) 
    {
        if (item.type === "vgroup" 
        	|| item.type === "hgroup" 
        	|| item.type === "tgroup") {
            parse_items(item.items);
        } else if (item.type === "hbargraph" 
        	|| item.type === "vbargraph") {
            // Keep bargraph adresses
            outputs_items.push(item.address);
        } else if (item.type === "vslider" 
        	|| item.type === "hslider" 
        	|| item.type === "button" 
        	|| item.type === "checkbox" 
        	|| item.type === "nentry") {
            // Keep inputs adresses
            inputs_items.push(item.address);
        }
    }
      
    function init ()
    {
        // Setup web audio context
        var i;
        var ptr_size = 4; 
        var sample_size = 4;
         
        // Get input / output counts
        numIn = factory.getNumInputs(dsp);
        numOut = factory.getNumOutputs(dsp);
                 
        // Setup web audio context
        console.log("buffer_size %d", buffer_size);
        scriptProcessor = context.createScriptProcessor(buffer_size, numIn, numOut);
        scriptProcessor.onaudioprocess = compute;
    
        if (numIn > 0) {
            ins = Module._malloc(ptr_size * numIn);
            for (i = 0; i < numIn; i++) { 
                HEAP32[(ins >> 2) + i] = Module._malloc(buffer_size * sample_size); 
            }

            // Prepare Ins buffer tables
            var dspInChans = HEAP32.subarray(ins >> 2, (ins + numIn * ptr_size) >> 2);
            for (i = 0; i < numIn; i++) {
                dspInChannnels[i] = HEAPF32.subarray(dspInChans[i] >> 2, (dspInChans[i] + buffer_size * sample_size) >> 2);
            }
        }
            
        if (numOut > 0) {
            outs = Module._malloc(ptr_size * numOut); 
            for (i = 0; i < numOut; i++) { 
                HEAP32[(outs >> 2) + i] = Module._malloc(buffer_size * sample_size);
            }
         
            // Prepare Out buffer tables
            var dspOutChans = HEAP32.subarray(outs >> 2, (outs + numOut * ptr_size) >> 2);
            for (i = 0; i < numOut; i++) {
                dspOutChannnels[i] = HEAPF32.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + buffer_size * sample_size) >> 2);
            }
        }
                                
        // bargraph
        parse_ui(JSON.parse(factory.getJSON()).ui);

        // Init DSP
        factory.init(dsp, context.sampleRate);
        
         // Init 'value' table
        for (var i = 0; i < inputs_items.length; i++) {
            var path = inputs_items[i];
            var values = new Float32Array(2);
            values[0] = values[1] = factory.getParamValue(dsp, factory.pathTable[path]);
            value_table[path] = values;
        }
    }
   
    init();
    
    // External API
    return {
    
        getNumInputs : function () 
        {
            return factory.getNumInputs(dsp);
        },
        
        getNumOutputs : function () 
        {
            return factory.getNumOutputs(dsp);
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
        
        // Connect/disconnect to another node
        connect : function (node) 
        {
            if (node.getProcessor !== undefined) {
                scriptProcessor.connect(node.getProcessor());
            } else {
                scriptProcessor.connect(node);
            }
        },

        disconnect : function (node) 
        {
            if (node.getProcessor !== undefined) {
                scriptProcessor.disconnect(node.getProcessor());
            } else {
                scriptProcessor.disconnect(node);
            }
        },

        setHandler : function (hd)
        {
            handler = hd;
        },
        
        start : function () 
        {
            scriptProcessor.connect(context.destination);
        },

        stop : function () 
        {
            scriptProcessor.disconnect(context.destination);
        },
        
        setParamValue : function (path, val) 
        {
            var values = value_table[path];
            if (values) {
                if (factory.getParamValue(dsp, factory.pathTable[path]) == values[0]) {
                    values[0] = val;
                } 
                values[1] = val;
            }
        },
        
        getParamValue : function (path) 
        {
            return factory.getParamValue(dsp, factory.pathTable[path]);
        },
        
        controls : function()
        {
            return inputs_items;
        },
        
        json : function ()
        {
            return factory.getJSON();
        },
        
        getProcessor : function ()
        {
            return scriptProcessor;
        }
    }
}

faust.deleteDSPInstance = function (dsp) {
    dsp.stop();
     
    if (dsp.numIn > 0) {
        for (var i = 0; i < dsp.numIn; i++) { 
            Module._free(HEAP32[(dsp.ins >> 2) + i]); 
        }
        Module._free(dsp.ins);
    }
     
    if (dsp.numOut > 0) {
        for (var i = 0; i < dsp.numOut; i++) { 
            Module._free(HEAP32[(dsp.outs >> 2) + i]);
        }
        Module._free(dsp.outs);
    }
  
    Module._free(dsp.dsp);
}

// 'poly' DSP
faust.createPolyDSPInstance = function (factory, context, buffer_size, max_polyphony, callback) {
    
    var handler = null;
    var ins, outs;
    var numIn, numOut, mixing;
    var compute_callback = callback;
    
    var scriptProcessor;
    
    var dspInChannnels = [];
    var dspOutChannnels = [];
  
    // bargraph
    var outputs_timer = 5;
    var outputs_items = [];
     
    // input items
    var inputs_items = [];
    
    var fFreqLabel;
    var fGateLabel;
    var fGainLabel;
    var fDate = 0;
    
    // asm.js mixer
    var mixer = mydspMixer(window, null, buffer);
    
    // Start of DSP memory ('polyphony' DSP voices)
    var dsp_voices = [];
    var dsp_voices_state = [];
    var dsp_voices_level = [];
    var dsp_voices_date = [];
    var dsp_voices_trigger = [];
    
    var kActiveVoice = 0;
    var kFreeVoice = -1;
    var kReleaseVoice = -2;
    var kNoVoice = -3;
    
    for (var i = 0; i < max_polyphony; i++) {
        dsp_voices[i] = Module._malloc(factory.getSize());
        dsp_voices_state[i] = kFreeVoice;
        dsp_voices_level[i] = 0;
        dsp_voices_date[i] = 0;
        dsp_voices_trigger[i] = false;
    }
    
    // Always returns a voice
    function newVoiceAux()
    {
        var voice = getVoice(kFreeVoice, true);
        dsp_voices_state[voice] = kActiveVoice;
        return voice;
    }
    
    function getVoice (note, steal)
    {
        for (var i = 0; i < max_polyphony; i++) {
            if (dsp_voices_state[i] === note) {
                if (steal) { dsp_voices_date[i] = fDate++; }
                return i;
            }
        }
        
        if (steal) {
            var voice_release = kNoVoice;
            var voice_playing = kNoVoice;
            var oldest_date_release = Number.MAX_VALUE;
            var oldest_date_playing = Number.MAX_VALUE;
            
            // Scan all voices
            for (var i = 0; i < max_polyphony; i++) {
                // Try to steal a voice in kReleaseVoice mode...
                if (dsp_voices_state[i] === kReleaseVoice) {
                    // Keeps oldest release voice
                    if (dsp_voices_date[i] < oldest_date_release) {
                        oldest_date_release = dsp_voices_date[i];
                        voice_release = i;
                    }
                } else {
                    if (dsp_voices_date[i] < oldest_date_playing) {
                        oldest_date_playing = dsp_voices_date[i];
                        voice_playing = i;
                    }
                }
            }
            
            // Then decide which one to steal
            if (oldest_date_release != Number.MAX_VALUE) {
                console.log("Steal release voice : voice_date = %d cur_date = %d voice = %d", dsp_voices_date[voice_release], fDate, voice_release);
                dsp_voices_date[voice_release] = fDate++;
                dsp_voices_trigger[voice_release] = true;
                return voice_release;
            } else {
                console.log("Steal playing voice : voice_date = %d cur_date = %d voice = %d", dsp_voices_date[voice_playing], fDate, voice_playing);
                dsp_voices_date[voice_playing] = fDate++;
                dsp_voices_trigger[voice_playing] = true;
                return voice_playing;
            }
            
        } else {
            return kNoVoice;
        }
    }
       
    function update_outputs () 
    {
        if (outputs_items.length > 0 && handler && outputs_timer-- === 0) {
            outputs_timer = 5;
            for (var i = 0; i < outputs_items.length; i++) {
                handler(outputs_items[i], factory.getParamValue(dsp_voices[0], factory.pathTable[outputs_items[i]]));
            }
        }
    }
 
    function compute (e) 
    {
        var i, j;
         
        // Read inputs
        for (i = 0; i < numIn; i++) {
            var input = e.inputBuffer.getChannelData(i);
            var dspInput = dspInChannnels[i];
            for (j = 0; j < input.length; j++) {
                dspInput[j] = input[j];
            }
        }
        
        // Possibly call an externally given callback (for instance to play a MIDIFile...)
        if (compute_callback) {
            compute_callback(buffer_size);
        }

        // First clear the outputs
        mixer.clearOutput(buffer_size, numOut, outs);
        
        // Compute all running voices
        var level;
        for (i = 0; i < max_polyphony; i++) {
            if (dsp_voices_state[i] != kFreeVoice) {
                if (dsp_voices_trigger[i]) {
                	dsp_voices_trigger[i] = false;
                    // FIXME : properly cut the buffer in 2 slices...
                    factory.setParamValue(dsp_voices[i], fGateLabel, 0.0);
                    factory.compute(dsp_voices[i], 1, ins, mixing);
                    factory.setParamValue(dsp_voices[i], fGateLabel, 1.0);
                    factory.compute(dsp_voices[i], buffer_size, ins, mixing);
                } else {
                    // Compute regular voice
                    factory.compute(dsp_voices[i], buffer_size, ins, mixing);
                }
                // Mix it in result
                dsp_voices_level[i] = mixer.mixVoice(buffer_size, numOut, mixing, outs);
                // Check the level to possibly set the voice in kFreeVoice again
                if ((dsp_voices_level[i] < 0.001) && (dsp_voices_state[i] == kReleaseVoice)) {
                    dsp_voices_state[i] = kFreeVoice;
                }
            }
        }
       
        // Update bargraph
        update_outputs();

        // Write outputs
        for (i = 0; i < numOut; i++) {
            var output = e.outputBuffer.getChannelData(i);
            var dspOutput = dspOutChannnels[i];
            for (j = 0; j < output.length; j++) {
                output[j] = dspOutput[j];
            }
        }
    }
    
    function midiToFreq  (note) 
    {
        return 440.0 * Math.pow(2.0, (note - 69.0) / 12.0);
    }
     
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
        for (var i = 0; i < items.length; i++) {
            parse_item(items[i]);
        }
    }
    
    function parse_item (item) 
    {
        if (item.type === "vgroup" || item.type === "hgroup" || item.type === "tgroup") {
            parse_items(item.items);
        } else if (item.type === "hbargraph" || item.type === "vbargraph") {
            // Keep bargraph adresses
            outputs_items.push(item.address);
        } else if (item.type === "vslider" || item.type === "hslider" || item.type === "button" || item.type === "checkbox" || item.type === "nentry") {
            // Keep inputs adresses
            inputs_items.push(item.address);
        }
    }
      
    function init ()
    {
        // Setup web audio context
        var i;
        var ptr_size = 4; 
        var sample_size = 4;
         
        // Get input / output counts
        numIn = factory.getNumInputs(dsp_voices[0]);
        numOut = factory.getNumOutputs(dsp_voices[0]);
         
        // Setup web audio context
        console.log("buffer_size %d", buffer_size);
        scriptProcessor = context.createScriptProcessor(buffer_size, numIn, numOut);
        scriptProcessor.onaudioprocess = compute;
    
        if (numIn > 0) {
            // allocate memory for input arrays
            ins = Module._malloc(ptr_size * numIn);
            for (i = 0; i < numIn; i++) { 
                HEAP32[(ins >> 2) + i] = Module._malloc(buffer_size * sample_size); 
            }

            var dspInChans = HEAP32.subarray(ins >> 2, (ins + numIn * ptr_size) >> 2);
            for (i = 0; i < numIn; i++) {
                dspInChannnels[i] = HEAPF32.subarray(dspInChans[i] >> 2, (dspInChans[i] + buffer_size * sample_size) >> 2);
            }
        }
            
        if (numOut > 0) {
            // allocate memory for output and mixing arrays
            outs = Module._malloc(ptr_size * numOut);
            mixing = Module._malloc(ptr_size * numOut);
             
            for (i = 0; i < numOut; i++) { 
                HEAP32[(outs >> 2) + i] = Module._malloc(buffer_size * sample_size);
                HEAP32[(mixing >> 2) + i] = Module._malloc(buffer_size * sample_size);
            }
            
            var dspOutChans = HEAP32.subarray(outs >> 2, (outs + numOut * ptr_size) >> 2);
            for (i = 0; i < numOut; i++) {
                dspOutChannnels[i] = HEAPF32.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + buffer_size * sample_size) >> 2);
            }
        }
                                
        // bargraph
        parse_ui(JSON.parse(factory.getJSON()).ui);
        
        // keep 'keyOn/keyOff' labels
        for (i = 0; i < inputs_items.length; i++) {
            if (inputs_items[i].endsWith("/gate")) {
                fGateLabel = factory.pathTable[inputs_items[i]];
                console.log(fGateLabel);
            } else if (inputs_items[i].endsWith("/freq")) {
                fFreqLabel = factory.pathTable[inputs_items[i]];
                console.log(fFreqLabel);
            } else if (inputs_items[i].endsWith("/gain")) {
                fGainLabel = factory.pathTable[inputs_items[i]];
                console.log(fGainLabel);
            }
        }
        
        // Init DSP voices
        for (i = 0; i < max_polyphony; i++) {
            factory.init(dsp_voices[i], context.sampleRate);
        }
    }
    
    init();
    
    // External API
    return {
                
        getNumInputs : function () 
        {
            return factory.getNumInputs(dsp_voices[0]);
        },
        
        getNumOutputs : function () 
        {
            return factory.getNumOutputs(dsp_voices[0]);
        },
        
		init : function (sample_rate) 
		{
			for (var i = 0; i < max_polyphony; i++) {
				factory.init(dsp_voices[i], sample_rate);
			}
		},

		instanceInit : function (sample_rate) 
		{
			for (var i = 0; i < max_polyphony; i++) {
				factory.instanceInit(dsp_voices[i], sample_rate);
			}
		},

		instanceConstants : function (sample_rate) 
		{
			for (var i = 0; i < max_polyphony; i++) {
				factory.instanceConstants(dsp_voices[i], sample_rate);
			}
		},
		
        instanceResetUserInterface : function ()
        {
            for (var i = 0; i < max_polyphony; i++) {
                factory.instanceResetUserInterface(dsp_voices[i]);
            }
        },

        instanceClear : function () 
        {
            for (var i = 0; i < max_polyphony; i++) {
                factory.instanceClear(dsp_voices[i]);
            }
        },

        // Connect/disconnect to another node
        connect : function (node) 
        {
            if (node.getProcessor !== undefined) {
                scriptProcessor.connect(node.getProcessor());
            } else {
                scriptProcessor.connect(node);
            }
        },

        disconnect : function (node) 
        {
            if (node.getProcessor !== undefined) {
                scriptProcessor.disconnect(node.getProcessor());
            } else {
                scriptProcessor.disconnect(node);
            }
        },
        
        setHandler : function (hd)
        {
            handler = hd;
        },
        
        keyOn : function (channel, pitch, velocity)
        {
            var voice = newVoiceAux();
            //console.log("keyOn voice %d", voice);
            factory.setParamValue(dsp_voices[voice], fFreqLabel, midiToFreq(pitch));
            factory.setParamValue(dsp_voices[voice], fGainLabel, velocity/127.);
            dsp_voices_state[voice] = pitch;
            dsp_voices_trigger[voice] = true; // so that envelop is always re-initialized
        },
        
        keyOff : function (channel, pitch, velocity)
        {
            var voice = getVoice(pitch, false);
            if (voice !== kNoVoice) {
                //console.log("keyOff voice %d", voice);
                // No use of velocity for now...
                factory.setParamValue(dsp_voices[voice], fGateLabel, 0.0);
                // Release voice
                dsp_voices_state[voice] = kReleaseVoice;
            } else {
                console.log("Playing voice not found...");
            }
        },
        
        allNotesOff : function ()
        {
            for (var i = 0; i < max_polyphony; i++) {
                factory.setParamValue(dsp_voices[i], fGateLabel, 0.0);
                dsp_voices_state[i] = kReleaseVoice;
            }
        },
        
        ctrlChange : function (channel, ctrl, value)
        {
            if (ctrl === 123 || ctrl === 120) {
                for (var i = 0; i < max_polyphony; i++) {
                    factory.setParamValue(dsp_voices[i], fGateLabel, 0.0);
                    dsp_voices_state[i] = kReleaseVoice;
                }
            }
        },
        
        pitchWheel : function (channel, wheel)
        {},
     
        start : function () 
        {
            scriptProcessor.connect(context.destination);
        },
        
        stop : function () 
        {
            scriptProcessor.disconnect(context.destination);
        },
        
        setParamValue : function (path, val) 
        {
            for (var i = 0; i < max_polyphony; i++) {
                factory.setParamValue(dsp_voices[i], factory.pathTable[path], val);
            }
        },
        
        getParamValue : function (path) 
        {
            return factory.getParamValue(dsp_voices[0], factory.pathTable[path]);
        },
        
        controls : function()
        {
            return inputs_items;
        },
          
        json : function ()
        {
            return factory.getJSON();
        },
        
        getSampleRate : function ()
        {
            return context.sampleRate;
        },
        
        setComputeCallback : function (callback) 
        {
            compute_callback = callback;
        },
        
        getComputeCallback : function () 
        {
            return compute_callback;
        },
        
        getProcessor : function ()
        {
            return scriptProcessor;
        }
    };
};

faust.deletePolyDSPInstance = function (dsp) {
    dsp.stop();
    
    if (dsp.numIn > 0) {
        for (var i = 0; i < dsp.numIn; i++) { 
            Module._free(HEAP32[(dsp.ins >> 2) + i]); 
        }
        Module._free(dsp.ins);
    }
     
    if (dsp.numOut > 0) {
        for (var i = 0; i < dsp.numOut; i++) { 
            Module._free(HEAP32[(dsp.outs >> 2) + i]);
            Module._free(HEAP32[(dsp.mixing >> 2) + i])
        }
        Module._free(dsp.outs);
        Module._free(dsp.mixing);
    }
    
    for (var i = 0; i < dsp.max_polyphony; i++) {
        Module._free(dsp.dsp_voices[i]);
    }
};
