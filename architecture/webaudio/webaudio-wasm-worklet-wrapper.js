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
 faust2wasm
 Additional code: GRAME 2017
*/
 
'use strict';

if (typeof (AudioWorkletNode) === "undefined") {
	alert("AudioWorklet is not supported in this browser !")
}

var faust_module = FaustModule(); // Emscripten generated module

var faust = faust || {};

faust.remap = function(v, mn0, mx0, mn1, mx1)
{
    return (1.0 * (v - mn0) / (mx0 - mn0)) * (mx1 - mn1) + mn1;
}

// Low-level API
faust.createWasmCDSPFactoryFromString = faust_module.cwrap('createWasmCDSPFactoryFromString', 'number', ['number', 'number', 'number', 'number', 'number', 'number']);
faust.expandCDSPFromString = faust_module.cwrap('expandCDSPFromString', 'number', ['number', 'number', 'number', 'number', 'number', 'number']);
faust.getCLibFaustVersion = faust_module.cwrap('getCLibFaustVersion', 'number', []);
faust.getWasmCModule = faust_module.cwrap('getWasmCModule', 'number', ['number']);
faust.getWasmCModuleSize = faust_module.cwrap('getWasmCModuleSize', 'number', ['number']);
faust.getWasmCHelpers = faust_module.cwrap('getWasmCHelpers', 'number', ['number']);
faust.freeWasmCModule = faust_module.cwrap('freeWasmCModule', null, ['number']);
faust.freeCMemory = faust_module.cwrap('freeCMemory', null, ['number']);
faust.cleanupAfterException = faust_module.cwrap('cleanupAfterException', null, []);
faust.getErrorAfterException = faust_module.cwrap('getErrorAfterException', 'number', []);

faust.error_msg = null;
faust.factory_number = 0;
faust.factory_table = [];

faust.getErrorMessage = function() { return faust.error_msg; };

// Audio buffer size
faust.buffer_size = 128;

faust.asm2wasm = { // special asm2wasm imports
    "fmod": function(x, y) {
        return x % y;
    },
    "remainder": function(x, y) {
        return x - Math.round(x/y) * y;
    }
}

faust.importObject = { imports: { print: arg => console.log(arg) } }
faust.importObject["global.Math"] = Math;
faust.importObject["asm2wasm"] = faust.asm2wasm;

faust.getLibFaustVersion = function () {
    return faust_module.Pointer_stringify(faust.getCLibFaustVersion());
}

faust.createDSPFactoryAux = function (code, argv, internal_memory, callback) {
    
    // Code memory type and argv in the SHAKey to differentiate compilation flags and Monophonic and Polyphonic factories
    var argv_str = "";
    for (var i = 0; i < argv.length; i++) {
        argv_str += argv[i];
    }
    var sha_key = Sha1.hash(code + ((internal_memory) ? "internal_memory": "external_memory") + argv_str, true);
    var factory = faust.factory_table[sha_key];
    if (factory) {
        console.log("Existing library : " + factory.name);
        // Existing factory, do not create it...
        callback(factory);
        return;
    }
    
    console.log("libfaust.js version : " + faust.getLibFaustVersion());
    
    // Allocate strings on the HEAP
    var factory_name = "mydsp" + faust.factory_number++;
    var code_ptr = faust_module._malloc(code.length + 1);
    var name = "FaustDSP";
    var name_ptr = faust_module._malloc(name.length + 1);
    var error_msg_ptr = faust_module._malloc(4096);
    
    faust_module.stringToUTF8(name, name_ptr, faust_module.lengthBytesUTF8(name) + 1);
    faust_module.stringToUTF8(code, code_ptr, faust_module.lengthBytesUTF8(code) + 1);
    
    // Add 'cn' option with the factory name
    argv = (argv === undefined) ? new Array() : argv;
    argv.push("-cn", factory_name);
    
    // Prepare 'argv' array for C side
    var ptr_size = 4;
    var argv_ptr = faust_module._malloc(argv.length * ptr_size);  // Get buffer from emscripten.
    var argv_ptr_buffer = new Int32Array(faust_module.HEAP32.buffer, argv_ptr, argv.length);  // Get a integer view on the newly allocated buffer.
    for (var i = 0; i < argv.length; i++) {
        var arg_ptr = faust_module._malloc(argv[i].length + 1);
        faust_module.stringToUTF8(argv[i], arg_ptr, faust_module.lengthBytesUTF8(argv[i]) + 1);
        argv_ptr_buffer[i] = arg_ptr;
    }
    
    try {
        var time1 = performance.now();
        
        var module_code_ptr = faust.createWasmCDSPFactoryFromString(name_ptr, code_ptr, argv.length, argv_ptr, error_msg_ptr, internal_memory);
        
        var time2 = performance.now();
        console.log("Faust compilation duration : " + (time2 - time1));
        
        faust.error_msg = faust_module.Pointer_stringify(error_msg_ptr);
        
        if (module_code_ptr === 0) {
            callback(null);
        } else {
            
            var factory_code_ptr = faust.getWasmCModule(module_code_ptr);
            var factory_code_size = faust.getWasmCModuleSize(module_code_ptr);
            
            // Copy native 'binary' string in JavaScript Uint8Array
            var factory_code = new Uint8Array(factory_code_size);
            for (var i = 0; i < factory_code_size; i++) {
                // faster than 'getValue' which gets the type of access for each read...
                factory_code[i] = faust_module.HEAP8[factory_code_ptr + i];
            }
            
            var helpers_code_ptr = faust.getWasmCHelpers(module_code_ptr);
            var helpers_code = faust_module.Pointer_stringify(helpers_code_ptr);
            
            // Free strings
            faust_module._free(code_ptr);
            faust_module._free(name_ptr);
            faust_module._free(error_msg_ptr);
            
            // Free C allocated wasm module
            faust.freeWasmCModule(module_code_ptr);
            
            // Free 'argv' C side array
            for (var i = 0; i < argv.length; i++) {
                faust_module._free(argv_ptr_buffer[i]);
            }
            faust_module._free(argv_ptr);
            
            faust.readDSPFactoryFromMachineAux(factory_name, factory_code, helpers_code, sha_key, callback);
        }
        
    } catch (e) {
        // libfaust is compiled without C++ exception activated, so a JS exception is throwed and catched here
        faust.error_msg = faust_module.Pointer_stringify(faust.getErrorAfterException());
        if (faust.error_msg === "") {
            // Report the Emscripten error
            faust.error_msg = e;
        }
        faust.cleanupAfterException();
        callback(null);
    }
    
};

/**
 * Create a DSP factory from source code as a string to be used to create 'monophonic' DSP
 *
 * @param code - the source code as a string
 * @param argv - an array of parameters to be given to the Faust compiler
 * @param callback - a callback taking the created DSP factory as parameter, or null in case of error
 */
faust.createDSPFactory = function (code, argv, callback) {
    faust.createDSPFactoryAux(code, argv, true, callback);
}

/**
 * Create a DSP factory from source code as a string to be used to create 'polyphonic' DSP
 *
 * @param code - the source code as a string
 * @param argv - an array of parameters to be given to the Faust compiler
 * @param callback - a callback taking the created DSP factory as parameter, or null in case of error
 */
faust.createPolyDSPFactory = function (code, argv, callback) {
    faust.createDSPFactoryAux(code, argv, false, callback);
}

/**
 * From a DSP source file, creates a 'self-contained' DSP source string where all needed librairies have been included.
 * All compilations options are 'normalized' and included as a comment in the expanded string.
 *
 * @param code - the source code as a string
 * @param argv - and array of paramaters to be given to the Faust compiler
 *
 * @return the expanded DSP as a string (possibly empty).
 */
faust.expandDSP = function (code, argv) {
    
    console.log("libfaust.js version : " + faust.getLibFaustVersion());
    
    // Force "wasm" compilation
    argv.push("-lang");
    argv.push("wasm");
    
    // Allocate strings on the HEAP
    var code_ptr = faust_module._malloc(code.length + 1);
    var name = "FaustDSP";
    var name_ptr = faust_module._malloc(name.length + 1);
    var sha_key_ptr = faust_module._malloc(64);
    var error_msg_ptr = faust_module._malloc(4096);
    
    faust_module.stringToUTF8(name, name_ptr, faust_module.lengthBytesUTF8(name) + 1);
    faust_module.stringToUTF8(code, code_ptr, faust_module.lengthBytesUTF8(code) + 1);
    
    // Add 'cn' option with the factory name
    argv = (argv === undefined) ? new Array() : argv;
    
    // Prepare 'argv' array for C side
    var ptr_size = 4;
    var argv_ptr = faust_module._malloc(argv.length * ptr_size);  // Get buffer from emscripten.
    var argv_ptr_buffer = new Int32Array(faust_module.HEAP32.buffer, argv_ptr, argv.length);  // Get a integer view on the newly allocated buffer.
    for (var i = 0; i < argv.length; i++) {
        var arg_ptr = faust_module._malloc(argv[i].length + 1);
        faust_module.stringToUTF8(argv[i], arg_ptr, faust_module.lengthBytesUTF8(argv[i]) + 1);
        argv_ptr_buffer[i] = arg_ptr;
    }
    
    var expand_dsp_ptr = faust.expandCDSPFromString(name_ptr, code_ptr, argv.length, argv_ptr, sha_key_ptr, error_msg_ptr);
    var expand_dsp = faust_module.Pointer_stringify(expand_dsp_ptr);
    var sha_key = faust_module.Pointer_stringify(sha_key_ptr);
    faust.error_msg = faust_module.Pointer_stringify(error_msg_ptr);
    
    // Free strings
    faust_module._free(code_ptr);
    faust_module._free(name_ptr);
    faust_module._free(sha_key_ptr);
    faust_module._free(error_msg_ptr);
    
    // Free C allocated expanded string
    faust.freeCMemory(expand_dsp_ptr);
    
    // Free 'argv' C side array
    for (var i = 0; i < argv.length; i++) {
        faust_module._free(argv_ptr_buffer[i]);
    }
    faust_module._free(argv_ptr);
    
    return expand_dsp;
};

/**
 * Write a Faust DSP factory into struct containing name, Faust wasm compiled code, and helpers code.
 *
 * @param factory - the DSP factory
 *
 * @return the machine code as a struct.
 */
faust.writeDSPFactoryToMachine = function (factory)
{
    return { name : factory.name, code : factory.code, helpers : factory.helpers };
}

/**
 * Create a Faust DSP factory from a machine code struct. Note that the library keeps an internal cache of all
 * allocated factories so that the compilation of the same DSP code (that is the same machine code file) will return
 * the same factory. You will have to explicitly use deleteDSPFactory when the factory is no more needed.
 *
 * @param machine - the machine code struct
 * @param callback - a callback taking the created DSP factory as parameter, or null in case of error
 *
 * @return the DSP factory on success, otherwise a null pointer.
 */
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
    var time1 = performance.now();
    
    try {
        var binaryen_module = Binaryen.readBinary(factory_code);
        console.log("Binaryen based optimisation");
        binaryen_module.optimize();
        //console.log(binaryen_module.emitText());
        factory_code = binaryen_module.emitBinary();
        binaryen_module.dispose();
    } catch(e) {
        console.log("Binaryen not available, no optimisation...");
    }
    
    /*
    WebAssembly.compile(factory_code)
    .then(module => {
          
        var time2 = performance.now();
     
        console.log("WASM compilation duration : " + (time2 - time1));
          
        var factory = {};
          
        factory.code = factory_code;
        factory.helpers = helpers_code;
        factory.module = module;
          
        // 'libfaust.js' wasm backend generates UI methods, then we compile the code
        eval(helpers_code);
        factory.getJSON = eval("getJSON" + factory_name);
          
        try {
            factory.json_object = JSON.parse(factory.getJSON());
        } catch (e) {
            faust.error_msg = "Error in JSON.parse: " + e;
            callback(null);
            throw true;
        }
          
        factory.name = factory_name;
        factory.sha_key = sha_key;
        faust.factory_table[sha_key] = factory;
          
        callback(factory);
    })
    .catch(function() { faust.error_msg = "Faust DSP factory cannot be compiled"; callback(null); });
    */
    
    var factory = {};
    factory.code = factory_code;
    factory.helpers = helpers_code;
    
    // 'libfaust.js' wasm backend generates UI methods, then we compile the code
    eval(helpers_code);
    factory.getJSON = eval("getJSON" + factory_name);
    factory.getBinaryCode = eval("getBinaryCodeString" + factory_name);
    
    try {
        factory.json_object = JSON.parse(factory.getJSON());
    } catch (e) {
        faust.error_msg = "Error in JSON.parse: " + e;
        callback(null);
        throw true;
    }
    
    factory.binary_code = factory.getBinaryCode();
    factory.name = factory_name;
    factory.sha_key = sha_key;
    faust.factory_table[sha_key] = factory;
    
    callback(factory);
}

faust.deleteDSPFactory = function (factory) { faust.factory_table[factory.sha_key] = null; };

// 'mono' DSP

/*
    Memory layout for monophonic DSP : DSP struct, audio buffers pointers, audio buffers

    dsp = 0;
    size = parseInt(factory.json_object.size)

    -----------
    audio_ptrs:
    -----------
    audio_heap_ptr = audio_heap_ptr_inputs = parseInt(factory.json_object.size)
    getNumInputsAux ==> size = getNumInputsAux * ptr_size
    ---
    ---
    audio_heap_ptr_outputs
    getNumOutputsAux ==> size = getNumOutputsAux * ptr_size
    ---
    ---
    --------------
    audio_buffers:
    --------------
    audio_heap_inputs
    getNumInputsAux ==> size = getNumInputsAux * buffer_size * sample_size
    ---
    ---
    audio_heap_outputs
    getNumOutputsAux ==> size = getNumOutputsAux * buffer_size * sample_size
    ---
    ---
*/

// Template string

var mydspProcessorString = `

    function getJSONmydsp() { return \`GETJSON\`; }

    function getBinaryCodemydsp() { return GETBINARYCODE; }

    'use strict';

    var faust = faust || {};

    faust.error_msg = null;
    faust.getErrorMessage = function() { return faust.error_msg; };

    // Audio buffer size
    faust.buffer_size = 128;

    faust.asm2wasm = { // special asm2wasm imports
        "fmod": function(x, y) {
            return x % y;
        },
        "remainder": function(x, y) {
            return x - Math.round(x/y) * y;
        }
    }

    faust.importObject = { imports: { print: arg => console.log(arg) } }
    faust.importObject["global.Math"] = Math;
    faust.importObject["asm2wasm"] = faust.asm2wasm;

    // WebAssembly instance
    faust.mydsp_instance = null;

    // Monophonic Faust DSP
    class mydspProcessor extends AudioWorkletProcessor {
        
        // JSON parsing functions
        static parse_ui(ui, obj, callback)
        {
            for (var i = 0; i < ui.length; i++) {
                mydspProcessor.parse_group(ui[i], obj, callback);
            }
        }
        
        static parse_group(group, obj, callback)
        {
            if (group.items) {
                mydspProcessor.parse_items(group.items, obj, callback);
            }
        }
        
        static parse_items(items, obj, callback)
        {
            for (var i = 0; i < items.length; i++) {
                callback(items[i], obj, callback);
            }
        }
        
        static parse_item1(item, obj, callback)
        {
            if (item.type === "vgroup"
                || item.type === "hgroup"
                || item.type === "tgroup") {
                mydspProcessor.parse_items(item.items, obj, callback);
            } else if (item.type === "hbargraph"
                       || item.type === "vbargraph") {
                // Keep bargraph adresses
                //obj.outputs_items.push(item.address);
            } else if (item.type === "vslider"
                       || item.type === "hslider"
                       || item.type === "button"
                       || item.type === "checkbox"
                       || item.type === "nentry") {
                obj.push({ name: item.address,
                         defaultValue: item.init,
                         minValue: item.min,
                         maxValue: item.max });
            }
        }
        
        static parse_item2(item, obj, callback)
        {
            if (item.type === "vgroup"
                || item.type === "hgroup"
                || item.type === "tgroup") {
                mydspProcessor.parse_items(item.items, obj, callback);
            } else if (item.type === "hbargraph"
                       || item.type === "vbargraph") {
                // Keep bargraph adresses
                obj.outputs_items.push(item.address);
                obj.pathTable[item.address] = parseInt(item.index);
            } else if (item.type === "vslider"
                       || item.type === "hslider"
                       || item.type === "button"
                       || item.type === "checkbox"
                       || item.type === "nentry") {
                // Keep inputs adresses
                obj.inputs_items.push(item.address);
                obj.pathTable[item.address] = parseInt(item.index);
            }
        }
        
        static get parameterDescriptors () {
            
            // Analyse JSON to generate AudioParam parameters
            var params = [];
            mydspProcessor.parse_ui(JSON.parse(getJSONmydsp()).ui, params, mydspProcessor.parse_item1);
            return params;
        }
        
        constructor(options)
        {
            super(options);
            
            this.json_object = JSON.parse(getJSONmydsp());
            
            this.output_handler = null;
            this.ins = null;
            this.outs = null;
            
            this.dspInChannnels = [];
            this.dspOutChannnels = [];
            
            this.numIn = parseInt(this.json_object.inputs);
            this.numOut = parseInt(this.json_object.outputs);
            
            // Memory allocator
            this.ptr_size = 4;
            this.sample_size = 4;
            
            this.factory = faust.mydsp_instance.exports;
            this.HEAP = faust.mydsp_instance.exports.memory.buffer;
            this.HEAP32 = new Int32Array(this.HEAP);
            this.HEAPF32 = new Float32Array(this.HEAP);
            
            console.log(this.HEAP);
            console.log(this.HEAP32);
            console.log(this.HEAPF32);
            
            // bargraph
            this.outputs_timer = 5;
            this.outputs_items = [];
            
            // input items
            this.inputs_items = [];
            
            // Start of HEAP index
            
            // DSP is placed first with index 0. Audio buffer start at the end of DSP.
            this.audio_heap_ptr = parseInt(this.json_object.size);
            
            // Setup pointers offset
            this.audio_heap_ptr_inputs = this.audio_heap_ptr;
            this.audio_heap_ptr_outputs = this.audio_heap_ptr_inputs + (this.numIn * this.ptr_size);
            
            // Setup buffer offset
            this.audio_heap_inputs = this.audio_heap_ptr_outputs + (this.numOut * this.ptr_size);
            this.audio_heap_outputs = this.audio_heap_inputs + (this.numIn * faust.buffer_size * this.sample_size);
            
            // Start of DSP memory : DSP is placed first with index 0
            this.dsp = 0;
            
            this.pathTable = [];
            
            this.update_outputs = function ()
            {
                if (this.outputs_items.length > 0 && this.output_handler && this.outputs_timer-- === 0) {
                    this.outputs_timer = 5;
                    for (var i = 0; i < this.outputs_items.length; i++) {
                        this.output_handler(this.outputs_items[i], this.factory.getParamValue(this.dsp, this.pathTable[this.outputs_items[i]]));
                    }
                }
            }
            
            this.initAux = function ()
            {
                var i;
                
                if (this.numIn > 0) {
                    this.ins = this.audio_heap_ptr_inputs;
                    for (i = 0; i < this.numIn; i++) {
                        this.HEAP32[(this.ins >> 2) + i] = this.audio_heap_inputs + ((faust.buffer_size * this.sample_size) * i);
                    }
                    
                    // Prepare Ins buffer tables
                    var dspInChans = this.HEAP32.subarray(this.ins >> 2, (this.ins + this.numIn * this.ptr_size) >> 2);
                    for (i = 0; i < this.numIn; i++) {
                        this.dspInChannnels[i] = this.HEAPF32.subarray(dspInChans[i] >> 2, (dspInChans[i] + faust.buffer_size * this.sample_size) >> 2);
                    }
                }
                
                if (this.numOut > 0) {
                    this.outs = this.audio_heap_ptr_outputs;
                    for (i = 0; i < this.numOut; i++) {
                        this.HEAP32[(this.outs >> 2) + i] = this.audio_heap_outputs + ((faust.buffer_size * this.sample_size) * i);
                    }
                    
                    // Prepare Out buffer tables
                    var dspOutChans = this.HEAP32.subarray(this.outs >> 2, (this.outs + this.numOut * this.ptr_size) >> 2);
                    for (i = 0; i < this.numOut; i++) {
                        this.dspOutChannnels[i] = this.HEAPF32.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + faust.buffer_size * this.sample_size) >> 2);
                    }
                }
                
                // Parse UI
                mydspProcessor.parse_ui(this.json_object.ui, this, mydspProcessor.parse_item2);
                
                // Init DSP
                this.factory.init(this.dsp, sampleRate); // 'sampleRate' is defined in AudioWorkletGlobalScope  
            }
           
            // Init resulting DSP
            this.initAux();
        }
        
        process(inputs, outputs, parameters) {
            
            var input = inputs[0];
            var output = outputs[0];
            
            // Copy inputs
            if (input !== undefined) {
                for (var channel = 0; channel < input.length; ++channel) {
                    var dspInput = this.dspInChannnels[channel];
                    dspInput.set(input[channel]);
                }
            }
            
            // Update controls
            var params = Object.entries(parameters);
            for (var i = 0; i < params.length; i++) {
                this.HEAPF32[this.pathTable[params[i][0]] >> 2] = params[i][1][0];
            }
            
            // Compute
            this.factory.compute(this.dsp, 128, this.ins, this.outs);
            
            // Copy outputs
            if (output !== undefined) {
                for (var channel = 0; channel < output.length; ++channel) {
                    var dspOutput = this.dspOutChannnels[channel];
                    output[channel].set(dspOutput);
                }
            }
            
            return true;
        }
    }

    // Compile wasm binary module
    WebAssembly.instantiate(getBinaryCodemydsp(), faust.importObject)
                .then(dsp_module => {
                      faust.mydsp_instance = dsp_module.instance;
                      registerProcessor('mydsp', mydspProcessor);
                })
                .catch(function(error) { console.log(error); console.log("Faust mydsp cannot be loaded or compiled"); });
`;

faust.createDSPInstance = function(factory, callback)
{
    var re1 = /mydsp/g;
    var re2 = /GETJSON/g;
    var re3 = /GETBINARYCODE/g;
    
    var mydspProcessorString1 = mydspProcessorString.replace(re1, factory.name);
    var mydspProcessorString2 = mydspProcessorString1.replace(re2, factory.getJSON());
    var mydspProcessorString3 = mydspProcessorString2.replace(re3, factory.getBinaryCode());
    
    var url = window.URL.createObjectURL(new Blob([mydspProcessorString3], { type: 'text/javascript' }));
    
    // The main global scope
    window.audioWorklet.addModule(url)
    .then(function () {
          audio_context = new AudioContext();
          
          // Create a generic AudioWorkletNode
          var audio_node = new AudioWorkletNode(audio_context, factory.name,
                                                { numberOfInputs: parseInt(factory.json_object.inputs),
                                                numberOfOutputs: parseInt(factory.json_object.outputs),
                                                channelCount: 1 });
          
          // And patch it with additional functions
          audio_node.getJSON = function() { return factory.getJSON(); }
          audio_node.setParamValue = function(path, val) { this.parameters.get(path).setValueAtTime(val, 0); }
          audio_node.getParamValue = function(path) { return this.parameters.get(path).value; }
          audio_node.setOutputParamHandler = function(handler) {}
          audio_node.getNumInputs = function() { return parseInt(factory.json_object.inputs); }
          audio_node.getNumOutputs = function() { return parseInt(factory.json_object.outputs); }
          audio_node.getParams = function() { return []; }
          audio_node.metadata = function (handler) {}
          
          // And use it
          callback(audio_node);
        
    })
    .catch(function(error) { console.log(error); console.log("Faust mydsp cannot be loaded or compiled"); alert(error); });
}

faust.deleteDSPInstance = function (dsp) {}

