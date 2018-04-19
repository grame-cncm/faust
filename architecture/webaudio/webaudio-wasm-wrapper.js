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
    utf8encode = (typeof utf8encode == 'undefined') ? true : utf8encode;

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
 Additional code: GRAME 2017-2018
*/

'use strict';

var faust_module = FaustModule(); // Emscripten generated module

faust_module.lengthBytesUTF8 = function(str)
{
	var len=0;for(var i=0;i<str.length;++i){var u=str.charCodeAt(i);if(u>=55296&&u<=57343)u=65536+((u&1023)<<10)|str.charCodeAt(++i)&1023;if(u<=127){++len}else if(u<=2047){len+=2}else if(u<=65535){len+=3}else if(u<=2097151){len+=4}else if(u<=67108863){len+=5}else{len+=6}}return len;
}

var faust = faust || {};

faust.remap = function(v, mn0, mx0, mn1, mx1)
{
    return (1.0 * (v - mn0) / (mx0 - mn0)) * (mx1 - mn1) + mn1;
}

faust.debug = false;

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

faust.getLibFaustVersion = function ()
{
    return faust_module.Pointer_stringify(faust.getCLibFaustVersion());
}

faust.ab2str = function(buf)
{
    if (buf) {
        return String.fromCharCode.apply(null, new Uint8Array(buf));
    } else {
        return null;
    }
}

faust.str2ab = function(str)
{
    if (str) {
        var buf = new ArrayBuffer(str.length);
        var bufView = new Uint8Array(buf);
        for (var i = 0, strLen = str.length; i < strLen; i++) {
            bufView[i] = str.charCodeAt(i);
        }
        return buf;
    } else {
        return null;
    }
}

faust.compileCode = function (factory_name, code, argv, internal_memory)
{
    var code_ptr = faust_module._malloc(code.length + 1);
    var name = "FaustDSP";
    var name_ptr = faust_module._malloc(name.length + 1);
    var error_msg_ptr = faust_module._malloc(4096);

    faust_module.stringToUTF8(name, name_ptr, faust_module.lengthBytesUTF8(name) + 1);
    faust_module.stringToUTF8(code, code_ptr, faust_module.lengthBytesUTF8(code) + 1);

    // Add 'cn' option with the factory name
    var argv_aux = (argv === undefined) ? new Array() : argv;
    argv_aux.push("-cn", factory_name);

    // Prepare 'argv_aux' array for C side
    var ptr_size = 4;
    var argv_ptr = faust_module._malloc(argv_aux.length * ptr_size);  // Get buffer from emscripten.
    var argv_ptr_buffer = new Int32Array(faust_module.HEAP32.buffer, argv_ptr, argv_aux.length);  // Get a integer view on the newly allocated buffer.
    for (var i = 0; i < argv_aux.length; i++) {
        var arg_ptr = faust_module._malloc(argv_aux[i].length + 1);
        faust_module.stringToUTF8(argv_aux[i], arg_ptr, faust_module.lengthBytesUTF8(argv_aux[i]) + 1);
        argv_ptr_buffer[i] = arg_ptr;
    }

    try {
        var time1 = performance.now();
        var module_code_ptr = faust.createWasmCDSPFactoryFromString(name_ptr, code_ptr, argv_aux.length, argv_ptr, error_msg_ptr, internal_memory);
        var time2 = performance.now();
        console.log("Faust compilation duration : " + (time2 - time1));

        faust.error_msg = faust_module.Pointer_stringify(error_msg_ptr);

        if (module_code_ptr === 0) {
            return null;
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

            // Get an updated integer view on the newly allocated buffer after possible emscripten memory grow
            argv_ptr_buffer = new Int32Array(faust_module.HEAP32.buffer, argv_ptr, argv_aux.length);
            // Free 'argv' C side array
            for (var i = 0; i < argv_aux.length; i++) {
                faust_module._free(argv_ptr_buffer[i]);
            }
            faust_module._free(argv_ptr);

            return { code: factory_code, code_source: code, helpers: helpers_code };
        }

    } catch (e) {
        // libfaust is compiled without C++ exception activated, so a JS exception is throwed and catched here
        faust.error_msg = faust_module.Pointer_stringify(faust.getErrorAfterException());
        if (faust.error_msg === "") {
            // Report the Emscripten error
            faust.error_msg = e;
        }
        faust.cleanupAfterException();
        return null;
    }

}

faust.createDSPFactoryAux = function (code, argv, internal_memory, callback)
{
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

    // Factory name for DSP and effect
    var factory_name1 = "mydsp" + faust.factory_number;
    var factory_name2 = "effect" + faust.factory_number++;

    // Create 'effect' expression
    var code_effect = "adapt(1,1) = _; adapt(2,2) = _,_; adapt(1,2) = _ <: _,_; adapt(2,1) = _,_ :> _; adaptor(F,G) = adapt(outputs(F),inputs(G)); dsp_code = environment{";
    code_effect = code_effect.concat(code); code_effect = code_effect.concat("};");
    code_effect = code_effect.concat("process = adaptor(dsp_code.process, dsp_code.effect) : dsp_code.effect;");

    var res1 = faust.compileCode(factory_name1, code, argv, internal_memory);

    if (res1) {
    	var res2 = faust.compileCode(factory_name2, code_effect, argv, internal_memory);
        if (res2) {
            // Effect is in the code
            faust.readDSPFactoryFromMachineAux(factory_name1,
                                               res1.code,
                                               res1.code_source,
                                               res1.helpers,
                                               factory_name2,
                                               res2.code,
                                               res2.code_source,
                                               res2.helpers,
                                               sha_key,
                                               callback);
        } else {
            faust.readDSPFactoryFromMachineAux(factory_name1,
                                               res1.code,
                                               res1.code_source,
                                               res1.helpers,
                                               null,
                                               null,
                                               null,
                                               null,
                                               sha_key,
                                               callback);
        }
    } else {
        callback(null);
    }
}

/**
 * Create a DSP factory from source code as a string to be used to create 'monophonic' DSP
 *
 * @param code - the source code as a string
 * @param argv - an array of parameters to be given to the Faust compiler
 * @param callback - a callback taking the created DSP factory as parameter, or null in case of error
 */
faust.createDSPFactory = function (code, argv, callback)
{
    faust.createDSPFactoryAux(code, argv, true, callback);
}

/**
 * Create a DSP factory from source code as a string to be used to create 'polyphonic' DSP
 *
 * @param code - the source code as a string
 * @param argv - an array of parameters to be given to the Faust compiler
 * @param callback - a callback taking the created DSP factory as parameter, or null in case of error
 */
faust.createPolyDSPFactory = function (code, argv, callback)
{
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
faust.expandDSP = function (code, argv)
{
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

    // Get an updated integer view on the newly allocated buffer after possible emscripten memory grow
    argv_ptr_buffer = new Int32Array(faust_module.HEAP32.buffer, argv_ptr, argv.length);
    // Free 'argv' C side array
    for (var i = 0; i < argv.length; i++) {
        faust_module._free(argv_ptr_buffer[i]);
    }
    faust_module._free(argv_ptr);

    return expand_dsp;
}

/**
 * Write a Faust DSP factory into struct containing name, Faust wasm compiled code, and helpers code.
 *
 * @param factory - the DSP factory
 *
 * @return the machine code as a struct.
 */
faust.writeDSPFactoryToMachine = function (factory)
{
    return { name: factory.name,
            code: faust.ab2str(factory.code),
            code_source: factory.code_source,
            helpers: factory.helpers,
            name_effect : factory.name_effect,
            code_effect: faust.ab2str(factory.code_effect),
            code_source_effect: factory.code_source_effect,
            helpers_effect : factory.helpers_effect,
            };
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
    var sha_key = Sha1.hash(machine.code_source, true);
    var factory = faust.factory_table[sha_key];
    if (factory) {
        // Existing factory, do not create it...
        callback(factory);
    } else {
        faust.readDSPFactoryFromMachineAux(machine.name,
                                           faust.str2ab(machine.code),
                                           machine.code_source,
                                           machine.helpers,
                                           machine.name_effect,
                                           faust.str2ab(machine.code_effect),
                                           machine.code_source_effect,
                                           machine.helpers_effect,
                                           sha_key,
                                           callback);
    }
}

faust.readDSPFactoryFromMachineAux = function (factory_name1,
                                               factory_code1,
                                               factory_code_source1,
                                               helpers_code1,
                                               factory_name2,
                                               factory_code2,
                                               factory_code_source2,
                                               helpers_code2,
                                               sha_key,
                                               callback)
{
    var time1 = performance.now();

    try {
        var binaryen_module = Binaryen.readBinary(factory_code1);
        console.log("Binaryen based optimisation");
        binaryen_module.optimize();
        //console.log(binaryen_module.emitText());
        factory_code = binaryen_module.emitBinary();
        binaryen_module.dispose();
    } catch(e) {
        console.log("Binaryen not available, no optimisation...");
    }

    WebAssembly.compile(factory_code1)
    .then(module => {

        var time2 = performance.now();
        console.log("WASM compilation duration : " + (time2 - time1));

        var factory = {};
        factory.polyphony = [];  // Default mode

        factory.code = factory_code1;
        factory.code_source = factory_code_source1;
        factory.helpers = helpers_code1;
        factory.module = module;

        // 'libfaust.js' wasm backend generates UI methods, then we compile the code
        eval(helpers_code1);
        factory.getJSON = eval("getJSON" + factory_name1);
        factory.getBase64Code = eval("getBase64Code" + factory_name1);

        try {
            factory.json_object = JSON.parse(factory.getJSON());
        } catch (e) {
            faust.error_msg = "Error in JSON.parse: " + e;
            callback(null);
            throw true;
        }

        factory.name = factory_name1;
        factory.sha_key = sha_key;
        faust.factory_table[sha_key] = factory;

        // Possibly compile effect
        if (factory_name2) {
          WebAssembly.compile(factory_code2)
            .then(module_effect => {

                  factory.code_effect = factory_code2;
                  factory.code_source_effect = factory_code_source2;
                  factory.helpers_effect = helpers_code2;
                  factory.module_effect = module_effect;

                  // 'libfaust.js' wasm backend generates UI methods, then we compile the code
                  eval(helpers_code2);
                  factory.getJSONeffect = eval("getJSON" + factory_name2);
                  factory.getBase64Codeeffect = eval("getBase64Code" + factory_name2);

                  try {
                    factory.effect_json_object = JSON.parse(factory.getJSONeffect());
                  } catch (e) {
                    faust.error_msg = "Error in JSON.parse: " + e;
                    callback(null);
                    throw true;
                  }

                  factory.name_effect = factory_name2;
                  callback(factory);
            })
            .catch(function(error) { console.log(error); faust.error_msg = "Faust DSP factory cannot be compiled"; callback(null); });
          } else {
            callback(factory);
          }
    })
    .catch(function(error) { console.log(error); faust.error_msg = "Faust DSP factory cannot be compiled"; callback(null); });
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

/**
 * Create a ScriptProcessorNode Web Audio object from a factory
 *
 * @param factory - the DSP factory
 * @param context - the Web Audio context
 * @param buffer_size - the buffer_size in frames
 * @param callback - a callback taking the created ScriptProcessorNode as parameter, or null in case of error
 */
faust.createDSPInstance = function (factory, context, buffer_size, callback)
{
    // Resume audio context each time...
    context.resume();

    var importObject = {
        env: {
            memoryBase: 0,
            tableBase: 0,

            // Integer version
            _abs: Math.abs,

            // Float version
            _acosf: Math.acos,
            _asinf: Math.asin,
            _atanf: Math.atan,
            _atan2f: Math.atan2,
            _ceilf: Math.ceil,
            _cosf: Math.cos,
            _expf: Math.exp,
            _floorf: Math.floor,
            _fmodf: function(x, y) { return x % y; },
            _logf: Math.log,
            _log10f: Math.log10,
            _max_f: Math.max,
            _min_f: Math.min,
            _remainderf: function(x, y) { return x - Math.round(x/y) * y; },
            _powf: Math.pow,
            _roundf: Math.fround,
            _sinf: Math.sin,
            _sqrtf: Math.sqrt,
            _tanf: Math.tan,

            // Double version
            _acos: Math.acos,
            _asin: Math.asin,
            _atan: Math.atan,
            _atan2: Math.atan2,
            _ceil: Math.ceil,
            _cos: Math.cos,
            _exp: Math.exp,
            _floor: Math.floor,
            _fmod: function(x, y) { return x % y; },
            _log: Math.log,
            _log10: Math.log10,
            _max_: Math.max,
            _min_: Math.min,
            _remainder:function(x, y) { return x - Math.round(x/y) * y; },
            _pow: Math.pow,
            _round: Math.fround,
            _sin: Math.sin,
            _sqrt: Math.sqrt,
            _tan: Math.tan,

            table: new WebAssembly.Table({ initial: 0, element: 'anyfunc' })
        }
    };

    var time1 = performance.now();

    WebAssembly.instantiate(factory.module, importObject)
    .then(dsp_instance => {

        var time2 = performance.now();
        console.log("Instantiation duration : " + (time2 - time1));

        var sp;
        try {
            sp = context.createScriptProcessor(buffer_size, dsp_instance.exports.getNumInputs(0), dsp_instance.exports.getNumOutputs(0));
        } catch (e) {
            faust.error_msg = "Error in createScriptProcessor: " + e;
            callback(null);
            return;
        }

        sp.output_handler = null;
        sp.ins = null;
        sp.outs = null;
        sp.compute_handler = null;

        sp.dspInChannnels = [];
        sp.dspOutChannnels = [];

        sp.fPitchwheelLabel = [];
        sp.fCtrlLabel = new Array(128);
        for (var i = 0; i < sp.fCtrlLabel.length; i++) { sp.fCtrlLabel[i] = []; }

        // bargraph
        sp.outputs_timer = 5;
        sp.outputs_items = [];

        // input items
        sp.inputs_items = [];

        // Memory allocator
        sp.ptr_size = 4;
        sp.sample_size = 4;

        // Start of DSP memory : DSP is placed first with index 0
        sp.dsp = 0;

        sp.pathTable = [];

        sp.factory = dsp_instance.exports;
        sp.HEAP = dsp_instance.exports.memory.buffer;
        sp.HEAP32 = new Int32Array(sp.HEAP);
        sp.HEAPF32 = new Float32Array(sp.HEAP);

        // Start of HEAP index

        sp.numIn = sp.factory.getNumInputs(sp.dsp);
        sp.numOut = sp.factory.getNumOutputs(sp.dsp);

        // DSP is placed first with index 0. Audio buffer starts at the end of DSP.
        sp.audio_heap_ptr = parseInt(factory.json_object.size);

        // Setup pointers offset
        sp.audio_heap_ptr_inputs = sp.audio_heap_ptr;
        sp.audio_heap_ptr_outputs = sp.audio_heap_ptr_inputs + (sp.numIn * sp.ptr_size);

        // Setup buffer offset
        sp.audio_heap_inputs = sp.audio_heap_ptr_outputs + (sp.numOut * sp.ptr_size);
        sp.audio_heap_outputs = sp.audio_heap_inputs + (sp.numIn * buffer_size * sp.sample_size);

        sp.update_outputs = function ()
        {
            if (sp.outputs_items.length > 0 && sp.output_handler && sp.outputs_timer-- === 0) {
                sp.outputs_timer = 5;
                for (var i = 0; i < sp.outputs_items.length; i++) {
                    sp.output_handler(sp.outputs_items[i], sp.factory.getParamValue(sp.dsp, sp.pathTable[sp.outputs_items[i]]));
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
                dspInput.set(input);
            }

            // Possibly call an externally given callback (for instance to synchronize playing a MIDIFile...)
            if (sp.compute_handler) {
                sp.compute_handler(buffer_size);
            }

            // Compute
            sp.factory.compute(sp.dsp, buffer_size, sp.ins, sp.outs);

            // Update bargraph
            sp.update_outputs();

            // Write outputs
            for (i = 0; i < sp.numOut; i++) {
                var output = e.outputBuffer.getChannelData(i);
                var dspOutput = sp.dspOutChannnels[i];
                output.set(dspOutput);
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
                sp.pathTable[item.address] = parseInt(item.index);
            } else if (item.type === "vslider"
            	|| item.type === "hslider"
            	|| item.type === "button"
            	|| item.type === "checkbox"
            	|| item.type === "nentry") {
                // Keep inputs adresses
                sp.inputs_items.push(item.address);
                sp.pathTable[item.address] = parseInt(item.index);
                if (item.meta !== undefined) {
                    for (var i = 0; i < item.meta.length; i++) {
                        if (item.meta[i].midi !== undefined) {
                            if (item.meta[i].midi.trim() === "pitchwheel") {
                                sp.fPitchwheelLabel.push(item.address);
                            } else if (item.meta[i].midi.trim().split(" ")[0] === "ctrl") {
                                sp.fCtrlLabel[parseInt(item.meta[i].midi.trim().split(" ")[1])]
                                    .push({ path:item.address,
                                            min:parseFloat(item.min),
                                            max:parseFloat(item.max) });
                            }
                        }
                    }
                }
            }
        }

        sp.initAux = function ()
        {
            // Setup web audio context
            var i;

            // Setup web audio context
            console.log("buffer_size " + buffer_size);
            sp.onaudioprocess = sp.compute;

            if (sp.numIn > 0) {
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

            // Parse JSON UI part
            sp.parse_ui(factory.json_object.ui);

            // Init DSP
            sp.factory.init(sp.dsp, context.sampleRate);
	    }

        /*
     	 Public API to be used to control the DSP.
         */

    	/* Return current sample rate */
    	sp.getSampleRate = function ()
        {
            return context.sampleRate;
        }

        /* Return instance number of audio inputs. */
        sp.getNumInputs = function ()
        {
            return sp.factory.getNumInputs(sp.dsp);
        }

        /* Return instance number of audio outputs. */
        sp.getNumOutputs = function ()
        {
            return sp.factory.getNumOutputs(sp.dsp);
        }

        /**
     	 * Global init, doing the following initialization:
     	 * - static tables initialization
     	 * - call 'instanceInit': constants and instance state initialisation
     	 *
     	 * @param sample_rate - the sampling rate in Hertz
     	 */
        sp.init = function (sample_rate)
        {
            sp.factory.init(sp.dsp, sample_rate);
        }

        /**
         * Init instance state.
         *
         * @param sample_rate - the sampling rate in Hertz
         */
        sp.instanceInit = function (sample_rate)
        {
            sp.factory.instanceInit(sp.dsp, sample_rate);
        }

        /**
         * Init instance constant state.
         *
         * @param sample_rate - the sampling rate in Hertz
         */
        sp.instanceConstants = function (sample_rate)
        {
            sp.factory.instanceConstants(sp.dsp, sample_rate);
        }

        /* Init default control parameters values. */
        sp.instanceResetUserInterface = function ()
        {
            sp.factory.instanceResetUserInterface(sp.dsp);
        }

        /* Init instance state (delay lines...).*/
        sp.instanceClear = function ()
        {
            sp.factory.instanceClear(sp.dsp);
        }

        /**
         * Trigger the Meta handler with instance specific calls to 'declare' (key, value) metadata.
         *
         * @param handler - the Meta handler as a 'declare' function of type (key, value)
         */
        sp.metadata = function (handler)
        {
            if (factory.json_object.meta) {
                factory.json_object.meta.forEach(function(meta) {
                                           handler.declare(Object.keys(meta)[0], Object.values(meta)[0]);
                                           });
            }
        }

        /**
         * Setup a control output handler with a function of type (path, value)
         * to be used on each generated output value. This handler will be called
         * each audio cycle at the end of the 'compute' method.
         *
         * @param handler - a function of type function(path, value)
         */
        sp.setOutputParamHandler = function (handler)
        {
            sp.output_handler = handler;
        }

        /**
         * Get the current output handler.
         */
        sp.getOutputParamHandler = function ()
        {
            return sp.output_handler;
        }

       /**
        * Controller
        *
        * @param channel - the MIDI channel (0..15, not used for now)
        * @param ctrl - the MIDI controller number (0..127)
        * @param value - the MIDI controller value (0..127)
        */
        sp.ctrlChange = function (channel, ctrl, value)
        {
            if (sp.fCtrlLabel[ctrl] !== []) {
                for (var i = 0; i < sp.fCtrlLabel[ctrl].length; i++) {
                	var path = sp.fCtrlLabel[ctrl][i].path;
                	sp.setParamValue(path, faust.remap(value, 0, 127, sp.fCtrlLabel[ctrl][i].min, sp.fCtrlLabel[ctrl][i].max));
                    if (sp.output_handler) {
                        sp.output_handler(path, sp.getParamValue(path));
                    }
                }
            }
        }

        /**
        * PitchWeel
        *
        * @param channel - the MIDI channel (0..15, not used for now)
        * @param value - the MIDI controller value (-1..1)
        */
      	sp.pitchWheel = function (channel, wheel)
        {
           	for (var i = 0; i < sp.fPitchwheelLabel.length; i++) {
           		var path = sp.fPitchwheelLabel[i];
           		sp.setParamValue(path, Math.pow(2.0, wheel/12.0));
                if (sp.output_handler) {
                    sp.output_handler(path, sp.getParamValue(path));
                }
          	}
        }

        /**
         * Set parameter value.
         *
         * @param path - the path to the wanted parameter (retrieved using 'getParams' method)
         * @param val - the float value for the wanted control
         */
        sp.setParamValue = function (path, val)
        {
         	return sp.factory.setParamValue(sp.dsp, sp.pathTable[path], val);
        }

        /**
         * Get parameter value.
         *
         * @param path - the path to the wanted parameter (retrieved using 'getParams' method)
         *
         * @return the float value
         */
        sp.getParamValue = function (path)
        {
            return sp.factory.getParamValue(sp.dsp, sp.pathTable[path]);
        }

        /**
         * Get the table of all control paths.
         *
         * @return the table of all input parameters paths
         */
        sp.getParams = function()
        {
            return sp.inputs_items;
        }

        /**
         * Get DSP JSON description with its UI and metadata
         *
         * @return DSP JSON description
         */
        sp.getJSON = function ()
        {
            return factory.getJSON();
        }

        // Init resulting DSP
        sp.initAux();

        // Call continuation
        callback(sp);

    })
    .catch(function(error) { console.log(error); faust.error_msg = "Faust DSP cannot be instantiated"; callback(null); });
}

faust.deleteDSPInstance = function (dsp) {}

// Worklet mode

// Template string

var mydspProcessorString = `

    'use strict';

    function getJSONmydsp() { return \`GETJSON\`; }
    function getBase64Codemydsp() { return \`GETBASE64CODE\`; }

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
            // Nothing
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
                if (item.meta !== undefined) {
                    for (var i = 0; i < item.meta.length; i++) {
                        if (item.meta[i].midi !== undefined) {
                            if (item.meta[i].midi.trim() === "pitchwheel") {
                                obj.fPitchwheelLabel.push(item.address);
                            } else if (item.meta[i].midi.trim().split(" ")[0] === "ctrl") {
                                obj.fCtrlLabel[parseInt(item.meta[i].midi.trim().split(" ")[1])]
                                .push({ path:item.address,
                                      min:parseFloat(item.min),
                                      max:parseFloat(item.max) });
                            }
                        }
                    }
                }
            }
        }

        static b64ToUint6(nChr)
        {
            return nChr > 64 && nChr < 91 ?
            nChr - 65
            : nChr > 96 && nChr < 123 ?
            nChr - 71
            : nChr > 47 && nChr < 58 ?
            nChr + 4
            : nChr === 43 ?
            62
            : nChr === 47 ?
            63
            :
            0;
        }

        static atob(sBase64, nBlocksSize)
        {
            if (typeof atob === 'function') {
                return atob(sBase64);
            } else {

                var sB64Enc = sBase64.replace(/[^A-Za-z0-9\+\/]/g, "");
                var nInLen = sB64Enc.length;
                var nOutLen = nBlocksSize ? Math.ceil((nInLen * 3 + 1 >> 2) / nBlocksSize) * nBlocksSize : nInLen * 3 + 1 >> 2;
                var taBytes = new Uint8Array(nOutLen);

                for (var nMod3, nMod4, nUint24 = 0, nOutIdx = 0, nInIdx = 0; nInIdx < nInLen; nInIdx++) {
                    nMod4 = nInIdx & 3;
                    nUint24 |= mydspProcessor.b64ToUint6(sB64Enc.charCodeAt(nInIdx)) << 18 - 6 * nMod4;
                    if (nMod4 === 3 || nInLen - nInIdx === 1) {
                        for (nMod3 = 0; nMod3 < 3 && nOutIdx < nOutLen; nMod3++, nOutIdx++) {
                            taBytes[nOutIdx] = nUint24 >>> (16 >>> nMod3 & 24) & 255;
                        }
                        nUint24 = 0;
                    }
                }
                return taBytes.buffer;
            }
        }

        static remap(v, mn0, mx0, mn1, mx1)
        {
            return (1.0 * (v - mn0) / (mx0 - mn0)) * (mx1 - mn1) + mn1;
        }

        static get parameterDescriptors ()
        {
            // Analyse JSON to generate AudioParam parameters
            var params = [];
            mydspProcessor.parse_ui(JSON.parse(getJSONmydsp()).ui, params, mydspProcessor.parse_item1);
            return params;
        }

        constructor(options)
        {
            super(options);

            this.json_object = JSON.parse(getJSONmydsp());

            this.output_handler = function(path, value) { this.port.postMessage({ path: path, value: value }); };

            this.ins = null;
            this.outs = null;

            this.dspInChannnels = [];
            this.dspOutChannnels = [];

            this.fPitchwheelLabel = [];
            this.fCtrlLabel = new Array(128);
            for (var i = 0; i < this.fCtrlLabel.length; i++) { this.fCtrlLabel[i] = []; }

            this.numIn = parseInt(this.json_object.inputs);
            this.numOut = parseInt(this.json_object.outputs);

            // Memory allocator
            this.ptr_size = 4;
            this.sample_size = 4;

            // Create the WASM instance
            var wasm_instance = new WebAssembly.Instance(mydspProcessor.wasm_module, mydspProcessor.importObject);
            this.factory = wasm_instance.exports;
            this.HEAP = wasm_instance.exports.memory.buffer;
            this.HEAP32 = new Int32Array(this.HEAP);
            this.HEAPF32 = new Float32Array(this.HEAP);

            //console.log(this.HEAP);
            //console.log(this.HEAP32);
            //console.log(this.HEAPF32);

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
            this.audio_heap_outputs = this.audio_heap_inputs + (this.numIn * mydspProcessor.buffer_size * this.sample_size);

            // Start of DSP memory : DSP is placed first with index 0
            this.dsp = 0;

            this.pathTable = [];

            // Send output values to the AudioNode
            this.update_outputs = function ()
            {
                if (this.outputs_items.length > 0 && this.output_handler && this.outputs_timer-- === 0) {
                    this.outputs_timer = 5;
                    for (var i = 0; i < this.outputs_items.length; i++) {
                        this.output_handler(this.outputs_items[i], this.HEAPF32[this.pathTable[this.outputs_items[i]] >> 2]);
                    }
                }
            }

            this.initAux = function ()
            {
                var i;

                if (this.numIn > 0) {
                    this.ins = this.audio_heap_ptr_inputs;
                    for (i = 0; i < this.numIn; i++) {
                        this.HEAP32[(this.ins >> 2) + i] = this.audio_heap_inputs + ((mydspProcessor.buffer_size * this.sample_size) * i);
                    }

                    // Prepare Ins buffer tables
                    var dspInChans = this.HEAP32.subarray(this.ins >> 2, (this.ins + this.numIn * this.ptr_size) >> 2);
                    for (i = 0; i < this.numIn; i++) {
                        this.dspInChannnels[i] = this.HEAPF32.subarray(dspInChans[i] >> 2, (dspInChans[i] + mydspProcessor.buffer_size * this.sample_size) >> 2);
                    }
                }

                if (this.numOut > 0) {
                    this.outs = this.audio_heap_ptr_outputs;
                    for (i = 0; i < this.numOut; i++) {
                        this.HEAP32[(this.outs >> 2) + i] = this.audio_heap_outputs + ((mydspProcessor.buffer_size * this.sample_size) * i);
                    }

                    // Prepare Out buffer tables
                    var dspOutChans = this.HEAP32.subarray(this.outs >> 2, (this.outs + this.numOut * this.ptr_size) >> 2);
                    for (i = 0; i < this.numOut; i++) {
                        this.dspOutChannnels[i] = this.HEAPF32.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + mydspProcessor.buffer_size * this.sample_size) >> 2);
                    }
                }

                // Parse UI
                mydspProcessor.parse_ui(this.json_object.ui, this, mydspProcessor.parse_item2);

                // Init DSP
                this.factory.init(this.dsp, sampleRate); // 'sampleRate' is defined in AudioWorkletGlobalScope
            }

            this.ctrlChange = function (channel, ctrl, value)
            {
                if (this.fCtrlLabel[ctrl] !== []) {
                    for (var i = 0; i < this.fCtrlLabel[ctrl].length; i++) {
                        var path = this.fCtrlLabel[ctrl][i].path;
                        this.setParamValue(path, mydspProcessor.remap(value, 0, 127, this.fCtrlLabel[ctrl][i].min, this.fCtrlLabel[ctrl][i].max));
                        if (this.output_handler) {
                            this.output_handler(path, this.getParamValue(path));
                        }
                    }
                }
            }

            this.pitchWheel = function (channel, wheel)
            {
                for (var i = 0; i < this.fPitchwheelLabel.length; i++) {
                    var path = this.fPitchwheelLabel[i];
                    this.setParamValue(path, Math.pow(2.0, wheel/12.0));
                    if (this.output_handler) {
                        this.output_handler(path, this.getParamValue(path));
                    }
                }
            }

            this.setParamValue = function (path, val)
            {
                this.HEAPF32[this.pathTable[path]] = val;
            }

            this.getParamValue = function (path)
            {
                return this.HEAPF32[this.pathTable[path]];
            }

            // Init resulting DSP
            this.initAux();

            // Set message handler
            this.port.onmessage = this.handleMessage.bind(this);
        }

        handleMessage(event)
        {
            var msg = event.data;
            switch (msg.type) {
                // Generic MIDI message
                case "midi": this.midiMessage(msg.data); break;
                // Typed MIDI message
                case "keyOn": this.keyOn(msg.data[0], msg.data[1], msg.data[2]); break;
                case "keyOff": this.keyOff(msg.data[0], msg.data[1], msg.data[2]); break;
                case "ctrlChange": this.ctrlChange(msg.data[0], msg.data[1], msg.data[2]); break;
                case "pitchWheel": this.pitchWheel(msg.data[0], msg.data[1]); break;
                // Generic data message
                case "param": this.setParamValue(msg.key, msg.value); break;
                //case "patch": this.onpatch(msg.data); break;
            }
        }

        midiMessage(data)
        {
            var cmd = data[0] >> 4;
            var channel = data[0] & 0xf;
            var data1 = data[1];
            var data2 = data[2];

            if (channel === 9) {
                return;
            } else if (cmd === 8 || ((cmd === 9) && (data2 === 0))) {
                //this.keyOff(channel, data1, data2);
            } else if (cmd === 9) {
                //this.keyOn(channel, data1, data2);
            } else if (cmd === 11) {
                //this.ctrlChange(channel, data1, data2);
            } else if (cmd === 14) {
                //this.pitchWheel(channel, ((data2 * 128.0 + data1)-8192)/8192.0);
            }
        }

        process(inputs, outputs, parameters)
        {
            var input = inputs[0];
            var output = outputs[0];

            // Check inputs
            if (this.numIn > 0 && ((input === undefined) || (input[0].length === 0))) {
                //console.log("Process input error");
                return true;
            }
            // Check outputs
            if (this.numOut > 0 && ((output === undefined) || (output[0].length === 0))) {
                //console.log("Process output error");
                return true;
            }

            // Copy inputs
            if (input !== undefined) {
                for (var chan = 0; chan < Math.min(this.numIn, input.length) ; ++chan) {
                    var dspInput = this.dspInChannnels[chan];
                    dspInput.set(input[chan]);
                }
            }

            // Update controls (possibly needed for sample accurate control)
            var params = Object.entries(parameters);
            for (var i = 0; i < params.length; i++) {
                this.HEAPF32[this.pathTable[params[i][0]] >> 2] = params[i][1][0];
            }

            // Compute
            this.factory.compute(this.dsp, mydspProcessor.buffer_size, this.ins, this.outs);

            // Update bargraph
            this.update_outputs();

            // Copy outputs
            if (output !== undefined) {
                for (var chan = 0; chan < Math.min(this.numOut, output.length); ++chan) {
                    var dspOutput = this.dspOutChannnels[chan];
                    output[chan].set(dspOutput);
                }
            }

            return true;
        }
    }

    // Globals

    mydspProcessor.buffer_size = 128;

    mydspProcessor.importObject = {
        env: {
            memoryBase: 0,
            tableBase: 0,

            // Integer version
            _abs: Math.abs,

            // Float version
            _acosf: Math.acos,
            _asinf: Math.asin,
            _atanf: Math.atan,
            _atan2f: Math.atan2,
            _ceilf: Math.ceil,
            _cosf: Math.cos,
            _expf: Math.exp,
            _floorf: Math.floor,
            _fmodf: function(x, y) { return x % y; },
            _logf: Math.log,
            _log10f: Math.log10,
            _max_f: Math.max,
            _min_f: Math.min,
            _remainderf: function(x, y) { return x - Math.round(x/y) * y; },
            _powf: Math.pow,
            _roundf: Math.fround,
            _sinf: Math.sin,
            _sqrtf: Math.sqrt,
            _tanf: Math.tan,

            // Double version
            _acos: Math.acos,
            _asin: Math.asin,
            _atan: Math.atan,
            _atan2: Math.atan2,
            _ceil: Math.ceil,
            _cos: Math.cos,
            _exp: Math.exp,
            _floor: Math.floor,
            _fmod: function(x, y) { return x % y; },
            _log: Math.log,
            _log10: Math.log10,
            _max_: Math.max,
            _min_: Math.min,
            _remainder:function(x, y) { return x - Math.round(x/y) * y; },
            _pow: Math.pow,
            _round: Math.fround,
            _sin: Math.sin,
            _sqrt: Math.sqrt,
            _tan: Math.tan,

            table: new WebAssembly.Table({ initial: 0, element: 'anyfunc' })
        }
    };

    // Synchronously compile and instantiate the WASM module
    try {
        mydspProcessor.wasm_module = new WebAssembly.Module(mydspProcessor.atob(getBase64Codemydsp()));
        registerProcessor('mydsp', mydspProcessor);
    } catch (e) {
        console.log(e); console.log("Faust mydsp cannot be loaded or compiled");
    }
`;

faust.createDSPWorkletInstanceAux = function(factory, context, callback)
{
    // Resume audio context each time...
    context.resume();

	// Create a generic AudioWorkletNode
	var audio_node = new AudioWorkletNode(context, factory.name,
                                          { numberOfInputs: (parseInt(factory.json_object.inputs) > 0) ? 1 : 0,
                                            numberOfOutputs: (parseInt(factory.json_object.outputs) > 0) ? 1 : 0,
                                            channelCount: Math.max(1, parseInt(factory.json_object.inputs)),
                                            outputChannelCount: [parseInt(factory.json_object.outputs)],
                                            channelCountMode: "explicit",
                                            channelInterpretation: "speakers" });

    audio_node.onprocessorerror = () => { console.log('An error from mydspProcessor was detected.');}
    // Patch it with additional functions
    audio_node.handleMessage = function(event)
    {
        var msg = event.data;
        if (this.output_handler) {
            this.output_handler(msg.path, msg.value);
        }
    }

    audio_node.init = function()
    {
        // JSON parsing functions
        this.parse_ui = function(ui, obj)
        {
            for (var i = 0; i < ui.length; i++) {
                this.parse_group(ui[i], obj);
            }
        }

        this.parse_group = function(group, obj)
        {
            if (group.items) {
                this.parse_items(group.items, obj);
            }
        }

        this.parse_items = function(items, obj)
        {
            for (var i = 0; i < items.length; i++) {
                this.parse_item(items[i], obj);
            }
        }

        this.parse_item = function(item, obj)
        {
            if (item.type === "vgroup"
                || item.type === "hgroup"
                || item.type === "tgroup") {
                this.parse_items(item.items, obj);
            } else if (item.type === "hbargraph"
                       || item.type === "vbargraph") {
                // Keep bargraph adresses
                obj.outputs_items.push(item.address);
            } else if (item.type === "vslider"
                       || item.type === "hslider"
                       || item.type === "button"
                       || item.type === "checkbox"
                       || item.type === "nentry") {
                // Keep inputs adresses
                obj.inputs_items.push(item.address);
            }
        }

        this.output_handler = null;

        this.json_object = factory.json_object;

        // input/output items
        this.inputs_items = [];
        this.outputs_items = [];

        // Parse UI
        this.parse_ui(this.json_object.ui, this);

        // Set message handler
        this.port.onmessage = this.handleMessage.bind(this);
    }

    // Call init
    audio_node.init();

    audio_node.getJSON = function() { return factory.getJSON(); }

    // Needed for sample accurate control
    audio_node.setParamValue = function(path, val) { this.parameters.get(path).setValueAtTime(val, 0); }
    audio_node.getParamValue = function(path) { return this.parameters.get(path).value; }

    audio_node.setOutputParamHandler = function(handler) { this.output_handler = handler; }
    audio_node.getOutputParamHandler = function() { return this.output_handler; }

    audio_node.getNumInputs = function() { return parseInt(factory.json_object.inputs); }
    audio_node.getNumOutputs = function() { return parseInt(factory.json_object.outputs); }

    audio_node.getParams = function() { return this.inputs_items; }

    audio_node.ctrlChange = function(channel, ctrl, value)
    {
        this.port.postMessage({ type: "ctrlChange", data: [channel, ctrl, value] });
    }

    audio_node.pitchWheel = function(channel, wheel)
    {
        this.port.postMessage({ type: "pitchWheel", data: [channel, wheel] });
    }

    audio_node.midiMessage = function(data)
    {
        this.port.postMessage({ type:"midi", data:data });
    }

    audio_node.metadata = function (handler) {}

    // And use it
    callback(audio_node);
}

/**
 * Create a AudioWorklet Web Audio object from a factory
 *
 * @param factory - the DSP factory
 * @param context - the Web Audio context
 * @param callback - a callback taking the created AudioWorklet as parameter, or null in case of error
 */
faust.createDSPWorkletInstance = function(factory, context, callback)
{
    if (factory.polyphony.length === 0) {
        var re1 = /mydsp/g;
        var re2 = /GETJSON/g;
        var re3 = /GETBASE64CODE/g;
        var mydspProcessorString1 = mydspProcessorString.replace(re1, factory.name);
        var mydspProcessorString2 = mydspProcessorString1.replace(re2, factory.getJSON());
        var mydspProcessorString3 = mydspProcessorString2.replace(re3, factory.getBase64Code());
        var url = window.URL.createObjectURL(new Blob([mydspProcessorString3], { type: 'text/javascript' }));

        context.audioWorklet.addModule(url)
        .then(function () {
              // Processor has been registered
              factory.polyphony.push(1);
              // Create audio node
              faust.createDSPWorkletInstanceAux(factory, context, callback);
        })
        .catch(function(error) { console.log(error); console.log("Faust mydsp cannot be loaded or compiled"); alert(error); });

    } else {
        // Create audio node
        faust.createDSPWorkletInstanceAux(factory, context, callback);
    }
}

faust.deleteDSPWorkletInstance = function (dsp) {}

/*
    Memory layout for polyphonic DSP : audio buffers pointers, audio buffers, DSP struct (voices)

    -----------
    audio_ptrs:
    -----------
    audio_heap_ptr = audio_heap_ptr_inputs = 0
    getNumInputsAux ==> size = getNumInputsAux * ptr_size
    ---
    ---
    audio_heap_ptr_outputs
    getNumOutputsAux ==> size = getNumOutputsAux * ptr_size
    ---
    ---
    audio_heap_ptr_mixing
    getNumOutputsAux ==> size = getNumOutputsAux * ptr_size
    ---
    ---
    ---------------
    audio_buffers:
    ---------------
    audio_heap_inputs
    getNumInputsAux ==> size = getNumInputsAux * buffer_size * sample_size
    ---
    ---
    audio_heap_outputs
    getNumOutputsAux ==> size = getNumOutputsAux * buffer_size * sample_size
    ---
    ---
    audio_heap_mixing
    getNumOutputsAux ==> size = getNumOutputsAux * buffer_size * sample_size
    ---
    ---
    dsp_start
    dsp_voices[0]  ==> size = parseInt(factory.json_object.size)
    dsp_voices[1]  ==> size = parseInt(factory.json_object.size)
    dsp_voices[2]  ==> size = parseInt(factory.json_object.size)
    dsp_voices[3]  ==> size = parseInt(factory.json_object.size)
    .....
*/

faust.createMemory = function (factory, buffer_size, polyphony) {

    // Memory allocator
    var ptr_size = 4;
    var sample_size = 4;

    function pow2limit (x)
    {
        var n = 65536; // Minimum = 64 kB
        while (n < x) { n = 2 * n; }
        return n;
    }

    var memory_size = pow2limit(((factory.effect_json_object) ?  parseInt(factory.effect_json_object.size) : 0) + parseInt(factory.json_object.size) * polyphony + ((parseInt(factory.json_object.inputs) + parseInt(factory.json_object.outputs) * 2) * (ptr_size + (buffer_size * sample_size)))) / 65536;
  	memory_size = Math.max(2, memory_size); // As least 2
	return new WebAssembly.Memory({ initial: memory_size, maximum: memory_size });
}

// 'poly' DSP

faust.createPolyDSPInstanceAux = function (factory, time1, mixer_instance, dsp_instance, effect_instance, memory, context, buffer_size, polyphony, callback)
{
    // Resume audio context each time...
    context.resume();

    var time2 = performance.now();
    console.log("Instantiation duration : " + (time2 - time1));

    var sp;
    try {
        sp = context.createScriptProcessor(buffer_size, parseInt(factory.json_object.inputs), parseInt(factory.json_object.outputs));
    } catch (e) {
        faust.error_msg = "Error in createScriptProcessor: " + e;
        callback(null);
        return;
    }

    sp.output_handler = null;
    sp.ins = null;
    sp.outs = null
    sp.mixing = null;
    sp.compute_handler = null;

    sp.dspInChannnels = [];
    sp.dspOutChannnels = [];

    sp.fFreqLabel = "";
    sp.fGateLabel = "";
    sp.fGainLabel = "";
    sp.fDate = 0;

    sp.fPitchwheelLabel = [];
    sp.fCtrlLabel = new Array(128);
    for (var i = 0; i < sp.fCtrlLabel.length; i++) { sp.fCtrlLabel[i] = []; }

    sp.numIn = parseInt(factory.json_object.inputs);
    sp.numOut = parseInt(factory.json_object.outputs);

    // Memory allocator
    sp.ptr_size = 4;
    sp.sample_size = 4;

    sp.factory = dsp_instance.exports;
    sp.HEAP = memory.buffer;
    sp.HEAP32 = new Int32Array(sp.HEAP);
    sp.HEAPF32 = new Float32Array(sp.HEAP);

    // bargraph
    sp.outputs_timer = 5;
    sp.outputs_items = [];

    // input items
    sp.inputs_items = [];

    // Start of HEAP index
    sp.audio_heap_ptr = 0;

    // Setup pointers offset
    sp.audio_heap_ptr_inputs = sp.audio_heap_ptr;
    sp.audio_heap_ptr_outputs = sp.audio_heap_ptr_inputs + (sp.numIn * sp.ptr_size);
    sp.audio_heap_ptr_mixing = sp.audio_heap_ptr_outputs + (sp.numOut * sp.ptr_size);

    // Setup buffer offset
    sp.audio_heap_inputs = sp.audio_heap_ptr_mixing + (sp.numOut * sp.ptr_size);
    sp.audio_heap_outputs = sp.audio_heap_inputs + (sp.numIn * buffer_size * sp.sample_size);
    sp.audio_heap_mixing = sp.audio_heap_outputs + (sp.numOut * buffer_size * sp.sample_size);

    // Setup DSP voices offset
    sp.dsp_start = sp.audio_heap_mixing + (sp.numOut * buffer_size * sp.sample_size);

    // wasm mixer
    sp.mixer = mixer_instance.exports;

    // wasm effect
    sp.effect = (effect_instance) ? effect_instance.exports : null;

    //console.log(sp.mixer);
    //console.log(sp.factory);
    //console.log(sp.effect);

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

    sp.pathTable = [];

    for (var i = 0; i < polyphony; i++) {
        sp.dsp_voices[i] = sp.dsp_start + i * parseInt(factory.json_object.size);
        sp.dsp_voices_state[i] = sp.kFreeVoice;
        sp.dsp_voices_level[i] = 0;
        sp.dsp_voices_date[i] = 0;
        sp.dsp_voices_trigger[i] = false;
    }

    // Effect memory starts after last voice
    sp.effect_start = sp.dsp_voices[polyphony - 1] + parseInt(factory.json_object.size);

    sp.getPlayingVoice = function(pitch)
    {
        var voice_playing = sp.kNoVoice;
        var oldest_date_playing = Number.MAX_VALUE;

        for (var i = 0; i < polyphony; i++) {
            if (sp.dsp_voices_state[i] === pitch) {
                // Keeps oldest playing voice
                if (sp.dsp_voices_date[i] < oldest_date_playing) {
                    oldest_date_playing = sp.dsp_voices_date[i];
                    voice_playing = i;
                }
            }
        }

        return voice_playing;
    }

    // Always returns a voice
    sp.allocVoice = function(voice)
    {
        sp.dsp_voices_date[voice] = sp.fDate++;
        sp.dsp_voices_trigger[voice] = true;    //so that envelop is always re-initialized
        sp.dsp_voices_state[voice] = sp.kActiveVoice;
        return voice;
    }

    sp.getFreeVoice = function()
    {
        for (var i = 0; i < polyphony; i++) {
            if (sp.dsp_voices_state[i] === sp.kFreeVoice) {
                return sp.allocVoice(i);
            }
        }

        var voice_release = sp.kNoVoice;
        var voice_playing = sp.kNoVoice;
        var oldest_date_release = Number.MAX_VALUE;
        var oldest_date_playing = Number.MAX_VALUE;

        // Scan all voices
        for (var i = 0; i < polyphony; i++) {
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
            if (faust.debug) {
                console.log("Steal release voice : voice_date = %d cur_date = %d voice = %d", sp.dsp_voices_date[voice_release], sp.fDate, voice_release);
            }
            return sp.allocVoice(voice_release);
        } else if (oldest_date_playing != Number.MAX_VALUE) {
            if (faust.debug) {
                console.log("Steal playing voice : voice_date = %d cur_date = %d voice = %d", sp.dsp_voices_date[voice_playing], sp.fDate, voice_playing);
            }
            return sp.allocVoice(voice_playing);
        } else {
            return sp.kNoVoice;
        }
    }

    sp.update_outputs = function ()
    {
        if (sp.outputs_items.length > 0 && sp.output_handler && sp.outputs_timer-- === 0) {
            sp.outputs_timer = 5;
            for (var i = 0; i < sp.outputs_items.length; i++) {
                sp.output_handler(sp.outputs_items[i], sp.factory.getParamValue(sp.dsp_voices[0], sp.pathTable[sp.outputs_items[i]]));
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
            dspInput.set(input);
        }

        // Possibly call an externally given callback (for instance to play a MIDIFile...)
        if (sp.compute_handler) {
            sp.compute_handler(buffer_size);
        }

        // First clear the outputs
        sp.mixer.clearOutput(buffer_size, sp.numOut, sp.outs);

        // Compute all running voices
        for (i = 0; i < polyphony; i++) {
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

        // Apply effect
        if (sp.effect) {
            sp.effect.compute(sp.effect_start, buffer_size, sp.outs, sp.outs);
        }

        // Update bargraph
        sp.update_outputs();

        // Write outputs
        for (i = 0; i < sp.numOut; i++) {
            var output = e.outputBuffer.getChannelData(i);
            var dspOutput = sp.dspOutChannnels[i];
            output.set(dspOutput);
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
        if (item.type === "vgroup"
            || item.type === "hgroup"
            || item.type === "tgroup") {
            sp.parse_items(item.items);
        } else if (item.type === "hbargraph"
                   || item.type === "vbargraph") {
            // Keep bargraph adresses
            sp.outputs_items.push(item.address);
            sp.pathTable[item.address] = parseInt(item.index);
        } else if (item.type === "vslider"
                   || item.type === "hslider"
                   || item.type === "button"
                   || item.type === "checkbox"
                   || item.type === "nentry") {
            // Keep inputs adresses
            sp.inputs_items.push(item.address);
            sp.pathTable[item.address] = parseInt(item.index);
            if (item.meta !== undefined) {
                for (var i = 0; i < item.meta.length; i++) {
                    if (item.meta[i].midi !== undefined) {
                        if (item.meta[i].midi.trim() === "pitchwheel") {
                            sp.fPitchwheelLabel.push(item.address);
                        } else if (item.meta[i].midi.trim().split(" ")[0] === "ctrl") {
                            sp.fCtrlLabel[parseInt(item.meta[i].midi.trim().split(" ")[1])]
                            .push({ path:item.address,
                                  min:parseFloat(item.min),
                                  max:parseFloat(item.max) });
                        }
                    }
                }
            }
        }
    }

    sp.initAux = function ()
    {
        // Setup web audio context
        var i;

        // Setup web audio context
        console.log("buffer_size " + buffer_size);
        sp.onaudioprocess = sp.compute;

        if (sp.numIn > 0) {
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

        // Parse JSON UI part
        sp.parse_ui(factory.json_object.ui);

        if (sp.effect) {
            sp.parse_ui(factory.effect_json_object.ui);
        }

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
        for (i = 0; i < polyphony; i++) {
            sp.factory.init(sp.dsp_voices[i], context.sampleRate);
        }

        // Init effect
        if (sp.effect) {
            sp.effect.init(sp.effect_start, context.sampleRate);
        }
    }

    /*
     Public API to be used to control the DSP.
     */

    /* Return current sample rate. */
    sp.getSampleRate = function ()
    {
        return context.sampleRate;
    }

    /* Return instance number of audio inputs. */
    sp.getNumInputs = function ()
    {
        return sp.numIn;
    }

    /* Return instance number of audio outputs. */
    sp.getNumOutputs = function ()
    {
        return sp.numOut;
    }

    /**
     * Global init, doing the following initialization:
     * - static tables initialization
     * - call 'instanceInit': constants and instance state initialisation
     *
     * @param sample_rate - the sampling rate in Hertz
     */
    sp.init = function (sample_rate)
    {
        for (var i = 0; i < polyphony; i++) {
            sp.factory.init(sp.dsp_voices[i], sample_rate);
        }
    }

    /**
     * Init instance state.
     *
     * @param sample_rate - the sampling rate in Hertz
     */
    sp.instanceInit = function (sample_rate)
    {
        for (var i = 0; i < polyphony; i++) {
            sp.factory.instanceInit(sp.dsp_voices[i], sample_rate);
        }
    }

    /**
     * Init instance constant state.
     *
     * @param sample_rate - the sampling rate in Hertz
     */
    sp.instanceConstants = function (sample_rate)
    {
        for (var i = 0; i < polyphony; i++) {
            fsp.actory.instanceConstants(sp.dsp_voices[i], sample_rate);
        }
    }

    /* Init default control parameters values. */
    sp.instanceResetUserInterface = function ()
    {
        for (var i = 0; i < polyphony; i++) {
            sp.factory.instanceResetUserInterface(sp.dsp_voices[i]);
        }
    }

    /* Init instance state (delay lines...). */
    sp.instanceClear = function ()
    {
        for (var i = 0; i < polyphony; i++) {
            sp.factory.instanceClear(sp.dsp_voices[i]);
        }
    }

    /**
     * Trigger the Meta handler with instance specific calls to 'declare' (key, value) metadata.
     *
     * @param handler - the Meta handler as a 'declare' function of type (key, value)
     */
    sp.metadata = function (handler)
    {
        if (factory.json_object.meta) {
            factory.json_object.meta.forEach(function(meta) {
                                             handler.declare(Object.keys(meta)[0], Object.values(meta)[0]);
                                             });
        }
    }

    /**
     * Setup a control output handler with a function of type (path, value)
     * to be used on each generated output value. This handler will be called
     * each audio cycle at the end of the 'compute' method.
     *
     * @param handler - a function of type function(path, value)
     */
    sp.setOutputParamHandler = function (handler)
    {
        sp.output_handler = handler;
    }

    /**
     * Get the current output handler.
     */
    sp.getOutputParamHandler = function ()
    {
        return sp.output_handler;
    }

    /**
     * Instantiates a new polyphonic voice.
     *
     * @param channel - the MIDI channel (0..15, not used for now)
     * @param pitch - the MIDI pitch (0..127)
     * @param velocity - the MIDI velocity (0..127)
     */
    sp.keyOn = function (channel, pitch, velocity)
    {
        var voice = sp.getFreeVoice();
        if (faust.debug) {
            console.log("keyOn voice %d", voice);
        }
        sp.factory.setParamValue(sp.dsp_voices[voice], sp.fFreqLabel, sp.midiToFreq(pitch));
        sp.factory.setParamValue(sp.dsp_voices[voice], sp.fGainLabel, velocity/127.);
        sp.dsp_voices_state[voice] = pitch;
    }

    /**
     * De-instantiates a polyphonic voice.
     *
     * @param channel - the MIDI channel (0..15, not used for now)
     * @param pitch - the MIDI pitch (0..127)
     * @param velocity - the MIDI velocity (0..127)
     */
    sp.keyOff = function (channel, pitch, velocity)
    {
        var voice = sp.getPlayingVoice(pitch);
        if (voice !== sp.kNoVoice) {
            if (faust.debug) {
                console.log("keyOff voice %d", voice);
            }
            // No use of velocity for now...
            sp.factory.setParamValue(sp.dsp_voices[voice], sp.fGateLabel, 0.0);
            // Release voice
            sp.dsp_voices_state[voice] = sp.kReleaseVoice;
        } else {
            if (faust.debug) {
                console.log("Playing voice not found...");
            }
        }
    }

    /**
     * Gently terminates all the active voices.
     */
    sp.allNotesOff = function ()
    {
        for (var i = 0; i < polyphony; i++) {
            sp.factory.setParamValue(sp.dsp_voices[i], sp.fGateLabel, 0.0);
            sp.dsp_voices_state[i] = sp.kReleaseVoice;
        }
    }

    /**
     * Controller
     *
     * @param channel - the MIDI channel (0..15, not used for now)
     * @param ctrl - the MIDI controller number (0..127)
     * @param value - the MIDI controller value (0..127)
     */
    sp.ctrlChange = function (channel, ctrl, value)
    {
        if (ctrl === 123 || ctrl === 120) {
            sp.allNotesOff();
        }
        if (sp.fCtrlLabel[ctrl] !== []) {
            for (var i = 0; i < sp.fCtrlLabel[ctrl].length; i++) {
                var path = sp.fCtrlLabel[ctrl][i].path;
                sp.setParamValue(path, faust.remap(value, 0, 127, sp.fCtrlLabel[ctrl][i].min, sp.fCtrlLabel[ctrl][i].max));
                if (sp.output_handler) {
                    sp.output_handler(path, sp.getParamValue(path));
                }
            }
        }
    }

    /**
     * PitchWeel
     *
     * @param channel - the MIDI channel (0..15, not used for now)
     * @param value - the MIDI controller value (-1..1)
     */
    sp.pitchWheel = function (channel, wheel)
    {
        for (var i = 0; i < sp.fPitchwheelLabel.length; i++) {
            var path = sp.fPitchwheelLabel[i];
            sp.setParamValue(path, Math.pow(2.0, wheel/12.0));
            if (sp.output_handler) {
                sp.output_handler(path, sp.getParamValue(path));
            }
        }
    }

    /**
     * Set parameter value.
     *
     * @param path - the path to the wanted parameter (retrieved using 'getParams' method)
     * @param val - the float value for the wanted parameter
     */
    sp.setParamValue = function (path, val)
    {
        if (sp.effect && factory.getJSONeffect().includes(path)) {
            sp.effect.setParamValue(sp.effect_start, sp.pathTable[path], val);
        } else {
            for (var i = 0; i < polyphony; i++) {
                sp.factory.setParamValue(sp.dsp_voices[i], sp.pathTable[path], val);
            }
        }
    }

    /**
     * Get parameter value.
     *
     * @param path - the path to the wanted parameter (retrieved using 'controls' method)
     *
     * @return the float value
     */
    sp.getParamValue = function (path)
    {
        if (sp.effect && factory.getJSONeffect().includes(path)) {
            return sp.effect.getParamValue(sp.effect_start, sp.pathTable[path]);
        } else {
            return sp.factory.getParamValue(sp.dsp_voices[0], sp.pathTable[path]);
        }
    }

    /**
     * Get the table of all input parameters paths.
     *
     * @return the table of all input parameters paths
     */
    sp.getParams = function()
    {
        return sp.inputs_items;
    }

    /**
     * Get DSP JSON description with its UI and metadata.
     *
     * @return DSP JSON description
     */
    sp.getJSON = function ()
    {
        var res = "";
        res = res.concat("{\"name\":\""); res = res.concat(factory.json_object.name); res = res.concat("\",");
        res = res.concat("\"version\":\""); res = res.concat(factory.json_object.version); res = res.concat("\",");
        res = res.concat("\"options\":\""); res = res.concat(factory.json_object.options); res = res.concat("\",");
        res = res.concat("\"inputs\":\""); res = res.concat(factory.json_object.inputs); res = res.concat("\",");
        res = res.concat("\"outputs\":\""); res = res.concat(factory.json_object.outputs); res = res.concat("\",");
        res = res.concat("\"meta\":"); res = res.concat(JSON.stringify(factory.json_object.meta)); res = res.concat(",");

        if (factory.effect_json_object) {
            res = res.concat("\"ui\":[{\"type\":\"tgroup\",\"label\":\"Sequencer\",\"items\":[");
            res = res.concat("{\"type\": \"vgroup\",\"label\":\"Instrument\",\"items\":");
            res = res.concat(JSON.stringify(factory.json_object.ui));
            res = res.concat("},");
            res = res.concat("{\"type\":\"vgroup\",\"label\":\"Effect\",\"items\":");
            res = res.concat(JSON.stringify(factory.effect_json_object.ui));
            res = res.concat("}");
            res = res.concat("]}]}");
            return res;
        } else {
            res = res.concat("\"ui\":[{\"type\":\"tgroup\",\"label\":\"Polyphonic\",\"items\":[");
            res = res.concat("{\"type\": \"vgroup\",\"label\":\"Voices\",\"items\":");
            res = res.concat(JSON.stringify(factory.json_object.ui));
            res = res.concat("},");
            res = res.concat("]}]}");
            return res;
        }
    }

    /**
     * Set a compute handler to be called each audio cycle
     * (for instance to synchronize playing a MIDIFile...).
     *
     * @param handler - a function of type function(buffer_size)
     */
    sp.setComputeHandler = function (handler)
    {
        sp.compute_handler = handler;
    }

    /**
     * Get the current compute handler.
     */
    sp.getComputeHandler = function ()
    {
        return sp.compute_handler;
    }

    // Init resulting DSP
    sp.initAux();

    // Call continuation
    callback(sp);
}

/**
 * Create a 'polyphonic' ScriptProcessorNode Web Audio object from a factory
 *
 * @param factory - the DSP factory
 * @param context - the Web Audio context
 * @param buffer_size - the buffer_size in frames
 * @param polyphony - the number of polyphonic voices
 * @param callback - a callback taking the created ScriptProcessorNode as parameter, or null in case of error
 */
faust.createPolyDSPInstance = function (factory, context, buffer_size, polyphony, callback) {

    var memory = faust.createMemory(factory, buffer_size, polyphony);

    var mixerObject = { imports: { print: arg => console.log(arg) } }
    mixerObject["memory"] = { "memory": memory};

    var importObject = {
        env: {
            memoryBase: 0,
            tableBase: 0,

            // Integer version
            _abs: Math.abs,

            // Float version
            _acosf: Math.acos,
            _asinf: Math.asin,
            _atanf: Math.atan,
            _atan2f: Math.atan2,
            _ceilf: Math.ceil,
            _cosf: Math.cos,
            _expf: Math.exp,
            _floorf: Math.floor,
            _fmodf: function(x, y) { return x % y; },
            _logf: Math.log,
            _log10f: Math.log10,
            _max_f: Math.max,
            _min_f: Math.min,
            _remainderf: function(x, y) { return x - Math.round(x/y) * y; },
            _powf: Math.pow,
            _roundf: Math.fround,
            _sinf: Math.sin,
            _sqrtf: Math.sqrt,
            _tanf: Math.tan,

            // Double version
            _acos: Math.acos,
            _asin: Math.asin,
            _atan: Math.atan,
            _atan2: Math.atan2,
            _ceil: Math.ceil,
            _cos: Math.cos,
            _exp: Math.exp,
            _floor: Math.floor,
            _fmod: function(x, y) { return x % y; },
            _log: Math.log,
            _log10: Math.log10,
            _max_: Math.max,
            _min_: Math.min,
            _remainder:function(x, y) { return x - Math.round(x/y) * y; },
            _pow: Math.pow,
            _round: Math.fround,
            _sin: Math.sin,
            _sqrt: Math.sqrt,
            _tan: Math.tan,

            memory: memory,

            table: new WebAssembly.Table({ initial: 0, element: 'anyfunc' })
        }
    };

    fetch('mixer32.wasm')
    .then(mixer_res => mixer_res.arrayBuffer())
    .then(mixer_bytes => WebAssembly.instantiate(mixer_bytes, mixerObject))
    .then(mixer_module =>
    {
        var time1 = performance.now();
        WebAssembly.instantiate(factory.module, importObject)
        .then(dsp_instance =>
        {
            if (factory.module_effect) {
               WebAssembly.instantiate(factory.module_effect, importObject)
              .then(effect_instance => faust.createPolyDSPInstanceAux(factory, time1,
                                                                      mixer_module.instance,
                                                                      dsp_instance,
                                                                      effect_instance,
                                                                      memory, context,
                                                                      buffer_size,
                                                                      polyphony,
                                                                      callback))
              .catch(function(error) { console.log(error); faust.error_msg = "Faust DSP cannot be instantiated"; callback(null); });
            } else {
              faust.createPolyDSPInstanceAux(factory, time1, mixer_module.instance, dsp_instance, null, memory, context, buffer_size, polyphony, callback);
            }
        })
        .catch(function(error) { console.log(error); faust.error_msg = "Faust DSP cannot be instantiated"; callback(null); });
    })
    .catch(function(error) { console.log(error); faust.error_msg = "Faust DSP cannot be instantiated"; callback(null); });
}

faust.deletePolyDSPInstance = function (dsp) {}

// Worklet mode

// Template string

var mydspPolyProcessorString = `

    'use strict';

    function getJSONmydsp() { return \`GETJSON\`; }
    function getJSONeffect() { return \`CODE1\`; }

    function getBase64Codemydsp() { return \`GETBASE64CODE\`; }
    function getBase64Codeeffect() { return \`CODE2\`; }

    function getBase64Mixer() { return "AGFzbQEAAAABj4CAgAACYAN/f38AYAR/f39/AX0CkoCAgAABBm1lbW9yeQZtZW1vcnkCAAIDg4CAgAACAAEHmoCAgAACC2NsZWFyT3V0cHV0AAAIbWl4Vm9pY2UAAQqKgoCAAALigICAAAEDfwJAQQAhBQNAAkAgAiAFQQJ0aigCACEDQQAhBANAAkAgAyAEQQJ0akMAAAAAOAIAIARBAWohBCAEIABIBEAMAgUMAQsACwsgBUEBaiEFIAUgAUgEQAwCBQwBCwALCwsLnYGAgAACBH8DfQJ9QQAhB0MAAAAAIQgDQAJAQQAhBiACIAdBAnRqKAIAIQQgAyAHQQJ0aigCACEFA0ACQCAEIAZBAnRqKgIAIQkgCCAJi5chCCAFIAZBAnRqKgIAIQogBSAGQQJ0aiAKIAmSOAIAIAZBAWohBiAGIABIBEAMAgUMAQsACwsgB0EBaiEHIAcgAUgEQAwCBQwBCwALCyAIDwsL"; }

    // Polyphonic Faust DSP
    class mydspPolyProcessor extends AudioWorkletProcessor {

        // JSON parsing functions
        static parse_ui(ui, obj, callback)
        {
            for (var i = 0; i < ui.length; i++) {
                mydspPolyProcessor.parse_group(ui[i], obj, callback);
            }
        }

        static parse_group(group, obj, callback)
        {
            if (group.items) {
                mydspPolyProcessor.parse_items(group.items, obj, callback);
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
                mydspPolyProcessor.parse_items(item.items, obj, callback);
            } else if (item.type === "hbargraph"
                       || item.type === "vbargraph") {
            // Nothing
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
                mydspPolyProcessor.parse_items(item.items, obj, callback);
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
                if (item.meta !== undefined) {
                    for (var i = 0; i < item.meta.length; i++) {
                        if (item.meta[i].midi !== undefined) {
                            if (item.meta[i].midi.trim() === "pitchwheel") {
                                obj.fPitchwheelLabel.push(item.address);
                            } else if (item.meta[i].midi.trim().split(" ")[0] === "ctrl") {
                                obj.fCtrlLabel[parseInt(item.meta[i].midi.trim().split(" ")[1])]
                                .push({ path:item.address,
                                      min:parseFloat(item.min),
                                      max:parseFloat(item.max) });
                            }
                        }
                    }
                }
            }
        }

        static b64ToUint6(nChr)
        {
            return nChr > 64 && nChr < 91 ?
            nChr - 65
            : nChr > 96 && nChr < 123 ?
            nChr - 71
            : nChr > 47 && nChr < 58 ?
            nChr + 4
            : nChr === 43 ?
            62
            : nChr === 47 ?
            63
            :
            0;
        }

        static atob(sBase64, nBlocksSize)
        {
            if (typeof atob === 'function') {
                return atob(sBase64);
            } else {

                var sB64Enc = sBase64.replace(/[^A-Za-z0-9\+\/]/g, "");
                var nInLen = sB64Enc.length;
                var nOutLen = nBlocksSize ? Math.ceil((nInLen * 3 + 1 >> 2) / nBlocksSize) * nBlocksSize : nInLen * 3 + 1 >> 2;
                var taBytes = new Uint8Array(nOutLen);

                for (var nMod3, nMod4, nUint24 = 0, nOutIdx = 0, nInIdx = 0; nInIdx < nInLen; nInIdx++) {
                    nMod4 = nInIdx & 3;
                    nUint24 |= mydspPolyProcessor.b64ToUint6(sB64Enc.charCodeAt(nInIdx)) << 18 - 6 * nMod4;
                    if (nMod4 === 3 || nInLen - nInIdx === 1) {
                        for (nMod3 = 0; nMod3 < 3 && nOutIdx < nOutLen; nMod3++, nOutIdx++) {
                            taBytes[nOutIdx] = nUint24 >>> (16 >>> nMod3 & 24) & 255;
                        }
                        nUint24 = 0;
                    }
                }
                return taBytes.buffer;
            }
        }

        static remap(v, mn0, mx0, mn1, mx1)
        {
            return (1.0 * (v - mn0) / (mx0 - mn0)) * (mx1 - mn1) + mn1;
        }

        static get parameterDescriptors ()
        {
            // Analyse JSON to generate AudioParam parameters
            var params = [];

            // Add instrument parameters
            mydspPolyProcessor.parse_ui(JSON.parse(getJSONmydsp()).ui, params, mydspPolyProcessor.parse_item1);

            // Possibly add effect parameters
            if (getJSONeffect() !== "") {
                mydspPolyProcessor.parse_ui(JSON.parse(getJSONeffect()).ui, params, mydspPolyProcessor.parse_item1);
            }
            return params;
        }

        static createMemory(buffer_size, polyphony)
        {
            // Memory allocator
            var ptr_size = 4;
            var sample_size = 4;

            function pow2limit(x)
            {
                var n = 65536; // Minimum = 64 kB
                while (n < x) { n = 2 * n; }
                return n;
            }

            // Keep JSON parsed object
            var json_object = null;
            try {
                json_object = JSON.parse(getJSONmydsp());
            } catch (e) {
                return null;
            }

            var effect_json_object_size = 0;
            if (getJSONeffect() !== "") {
                var effect_json_object = null;
                try {
                    effect_json_object = JSON.parse(getJSONeffect());
                    effect_json_object_size = parseInt(effect_json_object.size);
                } catch (e) {
                    faust.error_msg = "Error in JSON.parse: " + e;
                    return null;
                }
            }

            var memory_size = pow2limit(effect_json_object_size + parseInt(json_object.size) * polyphony + ((parseInt(json_object.inputs) + parseInt(json_object.outputs) * 2) * (ptr_size + (buffer_size * sample_size)))) / 65536;
            memory_size = Math.max(2, memory_size); // As least 2
            return new WebAssembly.Memory({ initial: memory_size, maximum: memory_size });
        }

        constructor(options)
        {
            super(options);

            this.json_object = JSON.parse(getJSONmydsp());
            if (getJSONeffect() !== "") {
                this.effect_json_object = JSON.parse(getJSONeffect());
            }

            this.output_handler = function(path, value) { this.port.postMessage({ path: path, value: value }); };

            this.debug = false;

            this.ins = null;
            this.outs = null;
            this.mixing = null;
            this.compute_handler = null;

            this.dspInChannnels = [];
            this.dspOutChannnels = [];

            this.fFreqLabel = "";
            this.fGateLabel = "";
            this.fGainLabel = "";
            this.fDate = 0;

            this.fPitchwheelLabel = [];
            this.fCtrlLabel = new Array(128);
            for (var i = 0; i < this.fCtrlLabel.length; i++) { this.fCtrlLabel[i] = []; }

            this.numIn = parseInt(this.json_object.inputs);
            this.numOut = parseInt(this.json_object.outputs);

            // Memory allocator
            this.ptr_size = 4;
            this.sample_size = 4;

            // Create the WASM memory
            var wasm_memory = mydspPolyProcessor.createMemory(mydspPolyProcessor.buffer_size, mydspPolyProcessor.polyphony);

            // Create the WASM mixer
            this.mixerObject = { imports: { print: arg => console.log(arg) } }
            this.mixerObject["memory"] = { "memory": wasm_memory };

            this.importObject = {
                env: {
                    memoryBase: 0,
                    tableBase: 0,

                    // Integer version
                    _abs: Math.abs,

                    // Float version
                    _acosf: Math.acos,
                    _asinf: Math.asin,
                    _atanf: Math.atan,
                    _atan2f: Math.atan2,
                    _ceilf: Math.ceil,
                    _cosf: Math.cos,
                    _expf: Math.exp,
                    _floorf: Math.floor,
                    _fmodf: function(x, y) { return x % y; },
                    _logf: Math.log,
                    _log10f: Math.log10,
                    _max_f: Math.max,
                    _min_f: Math.min,
                    _remainderf: function(x, y) { return x - Math.round(x/y) * y; },
                    _powf: Math.pow,
                    _roundf: Math.fround,
                    _sinf: Math.sin,
                    _sqrtf: Math.sqrt,
                    _tanf: Math.tan,

                    // Double version
                    _acos: Math.acos,
                    _asin: Math.asin,
                    _atan: Math.atan,
                    _atan2: Math.atan2,
                    _ceil: Math.ceil,
                    _cos: Math.cos,
                    _exp: Math.exp,
                    _floor: Math.floor,
                    _fmod: function(x, y) { return x % y; },
                    _log: Math.log,
                    _log10: Math.log10,
                    _max_: Math.max,
                    _min_: Math.min,
                    _remainder:function(x, y) { return x - Math.round(x/y) * y; },
                    _pow: Math.pow,
                    _round: Math.fround,
                    _sin: Math.sin,
                    _sqrt: Math.sqrt,
                    _tan: Math.tan,

                    memory: wasm_memory,

                    table: new WebAssembly.Table({ initial: 0, element: 'anyfunc' })
                }
            };

            this.mixer = new WebAssembly.Instance(mydspPolyProcessor.wasm_mixer_module, this.mixerObject).exports;

            // Create the WASM instance
            this.factory = new WebAssembly.Instance(mydspPolyProcessor.wasm_module, this.importObject).exports;

            // Create the WASM effect instance
            if (mydspPolyProcessor.wasm_effect_module) {
                this.effect = new WebAssembly.Instance(mydspPolyProcessor.wasm_effect_module, this.importObject).exports;
            }

            this.HEAP = wasm_memory.buffer;
            this.HEAP32 = new Int32Array(this.HEAP);
            this.HEAPF32 = new Float32Array(this.HEAP);

            //console.log(this.HEAP);
            //console.log(this.HEAP32);
            //console.log(this.HEAPF32);

            // bargraph
            this.outputs_timer = 5;
            this.outputs_items = [];

            // input items
            this.inputs_items = [];

            // Start of HEAP index
            // this.audio_heap_ptr = 0; Fails when 0...
            this.audio_heap_ptr = 65536;

            // Setup pointers offset
            this.audio_heap_ptr_inputs = this.audio_heap_ptr;
            this.audio_heap_ptr_outputs = this.audio_heap_ptr_inputs + (this.numIn * this.ptr_size);
            this.audio_heap_ptr_mixing = this.audio_heap_ptr_outputs + (this.numOut * this.ptr_size);

            // Setup buffer offset
            this.audio_heap_inputs = this.audio_heap_ptr_mixing + (this.numOut * this.ptr_size);
            this.audio_heap_outputs = this.audio_heap_inputs + (this.numIn * mydspPolyProcessor.buffer_size * this.sample_size);
            this.audio_heap_mixing = this.audio_heap_outputs + (this.numOut * mydspPolyProcessor.buffer_size * this.sample_size);

            // Setup DSP voices offset
            this.dsp_start = this.audio_heap_mixing + (this.numOut * mydspPolyProcessor.buffer_size * this.sample_size);

            //console.log(this.mixer);
            //console.log(this.factory);

            // Start of DSP memory ('polyphony' DSP voices)
            this.polyphony = mydspPolyProcessor.polyphony;
            this.dsp_voices = [];
            this.dsp_voices_state = [];
            this.dsp_voices_level = [];
            this.dsp_voices_date = [];
            this.dsp_voices_trigger = [];

            this.kActiveVoice = 0;
            this.kFreeVoice = -1;
            this.kReleaseVoice = -2;
            this.kNoVoice = -3;

            this.pathTable = [];

            // Allocate table for 'setParamValue'
            this.value_table = [];

            for (var i = 0; i <  this.polyphony; i++) {
                this.dsp_voices[i] = this.dsp_start + i * parseInt(this.json_object.size);
                this.dsp_voices_state[i] = this.kFreeVoice;
                this.dsp_voices_level[i] = 0;
                this.dsp_voices_date[i] = 0;
                this.dsp_voices_trigger[i] = false;
            }

            // Effect memory starts after last voice
            this.effect_start = this.dsp_voices[this.polyphony - 1] + parseInt(this.json_object.size);

            this.getPlayingVoice = function(pitch)
            {
                var voice_playing = this.kNoVoice;
                var oldest_date_playing = Number.MAX_VALUE;

                for (var i = 0; i <  this.polyphony; i++) {
                    if (this.dsp_voices_state[i] === pitch) {
                        // Keeps oldest playing voice
                        if (this.dsp_voices_date[i] < oldest_date_playing) {
                            oldest_date_playing = this.dsp_voices_date[i];
                            voice_playing = i;
                        }
                    }
                }

                return voice_playing;
            }

            // Always returns a voice
            this.allocVoice = function(voice)
            {
                this.dsp_voices_date[voice] = this.fDate++;
                this.dsp_voices_trigger[voice] = true;    //so that envelop is always re-initialized
                this.dsp_voices_state[voice] = this.kActiveVoice;
                return voice;
            }

            this.getFreeVoice = function()
            {
                for (var i = 0; i <  this.polyphony; i++) {
                    if (this.dsp_voices_state[i] === this.kFreeVoice) {
                        return this.allocVoice(i);
                    }
                }

                var voice_release = this.kNoVoice;
                var voice_playing = this.kNoVoice;
                var oldest_date_release = Number.MAX_VALUE;
                var oldest_date_playing = Number.MAX_VALUE;

                // Scan all voices
                for (var i = 0; i <  this.polyphony; i++) {
                    // Try to steal a voice in kReleaseVoice mode...
                    if (this.dsp_voices_state[i] === this.kReleaseVoice) {
                        // Keeps oldest release voice
                        if (this.dsp_voices_date[i] < oldest_date_release) {
                            oldest_date_release = this.dsp_voices_date[i];
                            voice_release = i;
                        }
                    } else {
                        if (this.dsp_voices_date[i] < oldest_date_playing) {
                            oldest_date_playing = this.dsp_voices_date[i];
                            voice_playing = i;
                        }
                    }
                }

                // Then decide which one to steal
                if (oldest_date_release != Number.MAX_VALUE) {
                    if (this.debug) {
                        console.log("Steal release voice : voice_date = %d cur_date = %d voice = %d", this.dsp_voices_date[voice_release], this.fDate, voice_release);
                    }
                    return this.allocVoice(voice_release);
                } else if (oldest_date_playing != Number.MAX_VALUE) {
                    if (this.debug) {
                        console.log("Steal playing voice : voice_date = %d cur_date = %d voice = %d", this.dsp_voices_date[voice_playing], this.fDate, voice_playing);
                    }
                    return this.allocVoice(voice_playing);
                } else {
                    return this.kNoVoice;
                }
            }

            this.update_outputs = function ()
            {
                if (this.outputs_items.length > 0 && this.output_handler && this.outputs_timer-- === 0) {
                    this.outputs_timer = 5;
                    for (var i = 0; i < this.outputs_items.length; i++) {
                        this.output_handler(this.outputs_items[i], this.factory.getParamValue(this.dsp, this.pathTable[this.outputs_items[i]]));
                    }
                }
            }

            this.midiToFreq = function (note)
            {
                return 440.0 * Math.pow(2.0, (note - 69.0) / 12.0);
            }

            this.initAux = function ()
            {
                var i;

                if (this.numIn > 0) {
                    this.ins = this.audio_heap_ptr_inputs;
                    for (i = 0; i < this.numIn; i++) {
                        this.HEAP32[(this.ins >> 2) + i] = this.audio_heap_inputs + ((mydspPolyProcessor.buffer_size * this.sample_size) * i);
                    }

                    // Prepare Ins buffer tables
                    var dspInChans = this.HEAP32.subarray(this.ins >> 2, (this.ins + this.numIn * this.ptr_size) >> 2);
                    for (i = 0; i < this.numIn; i++) {
                        this.dspInChannnels[i] = this.HEAPF32.subarray(dspInChans[i] >> 2, (dspInChans[i] + mydspPolyProcessor.buffer_size * this.sample_size) >> 2);
                    }
                }

                if (this.numOut > 0) {
                    // allocate memory for output and mixing arrays
                    this.outs = this.audio_heap_ptr_outputs;
                    this.mixing = this.audio_heap_ptr_mixing;

                    for (i = 0; i < this.numOut; i++) {
                        this.HEAP32[(this.outs >> 2) + i] = this.audio_heap_outputs + ((mydspPolyProcessor.buffer_size * this.sample_size) * i);
                        this.HEAP32[(this.mixing >> 2) + i] = this.audio_heap_mixing + ((mydspPolyProcessor.buffer_size * this.sample_size) * i);
                    }

                    // Prepare Out buffer tables
                    var dspOutChans = this.HEAP32.subarray(this.outs >> 2, (this.outs + this.numOut * this.ptr_size) >> 2);
                    for (i = 0; i < this.numOut; i++) {
                        this.dspOutChannnels[i] = this.HEAPF32.subarray(dspOutChans[i] >> 2, (dspOutChans[i] + mydspPolyProcessor.buffer_size * this.sample_size) >> 2);
                    }
                }

                // Parse UI
                mydspPolyProcessor.parse_ui(this.json_object.ui, this, mydspPolyProcessor.parse_item2);

                if (this.effect) {
                    mydspPolyProcessor.parse_ui(this.effect_json_object.ui, this, mydspPolyProcessor.parse_item2);
                }

                // keep 'keyOn/keyOff' labels
                for (i = 0; i < this.inputs_items.length; i++) {
                    if (this.inputs_items[i].endsWith("/gate")) {
                        this.fGateLabel = this.pathTable[this.inputs_items[i]];
                        console.log(this.fGateLabel);
                    } else if (this.inputs_items[i].endsWith("/freq")) {
                        this.fFreqLabel = this.pathTable[this.inputs_items[i]];
                        console.log(this.fFreqLabel);
                    } else if (this.inputs_items[i].endsWith("/gain")) {
                        this.fGainLabel = this.pathTable[this.inputs_items[i]];
                        console.log(this.fGainLabel);
                    }
                }

                // Init DSP voices
                for (i = 0; i <  this.polyphony; i++) {
                    this.factory.init(this.dsp_voices[i], sampleRate);  // 'sampleRate' is defined in AudioWorkletGlobalScope
                }

                // Init effect
                if (this.effect) {
                    this.effect.init(this.effect_start, sampleRate);
                }
            }

            this.keyOn = function (channel, pitch, velocity)
            {
                var voice = this.getFreeVoice();
                if (this.debug) {
                    console.log("keyOn voice %d", voice);
                }
                this.factory.setParamValue(this.dsp_voices[voice], this.fFreqLabel, this.midiToFreq(pitch));
                this.factory.setParamValue(this.dsp_voices[voice], this.fGainLabel, velocity/127.);
                this.dsp_voices_state[voice] = pitch;
            }

            this.keyOff = function (channel, pitch, velocity)
            {
                var voice = this.getPlayingVoice(pitch);
                if (voice !== this.kNoVoice) {
                    // No use of velocity for now...
                    this.factory.setParamValue(this.dsp_voices[voice], this.fGateLabel, 0.0);
                    // Release voice
                    this.dsp_voices_state[voice] = this.kReleaseVoice;
                } else {
                    if (this.debug) {
                        console.log("Playing voice not found...");
                    }
                }
            }

            this.allNotesOff = function ()
            {
                for (var i = 0; i <  this.polyphony; i++) {
                    this.factory.setParamValue(this.dsp_voices[i], this.fGateLabel, 0.0);
                    this.dsp_voices_state[i] = this.kReleaseVoice;
                }
            }

            this.ctrlChange = function (channel, ctrl, value)
            {
                if (ctrl === 123 || ctrl === 120) {
                    this.allNotesOff();
                }

                if (this.fCtrlLabel[ctrl] !== []) {
                    for (var i = 0; i < this.fCtrlLabel[ctrl].length; i++) {
                        var path = this.fCtrlLabel[ctrl][i].path;
                        this.setParamValue(path, mydspPolyProcessor.remap(value, 0, 127, this.fCtrlLabel[ctrl][i].min, this.fCtrlLabel[ctrl][i].max));
                        if (this.output_handler) {
                            this.output_handler(path, this.getParamValue(path));
                        }
                    }
                }
            }

            this.pitchWheel = function (channel, wheel)
            {
                for (var i = 0; i < this.fPitchwheelLabel.length; i++) {
                    var path = this.fPitchwheelLabel[i];
                    this.setParamValue(path, Math.pow(2.0, wheel/12.0));
                    if (this.output_handler) {
                        this.output_handler(path, this.getParamValue(path));
                    }
                }
            }

            this.setParamValue = function (path, val)
            {
                if (this.effect && getJSONeffect().includes(path)) {
                    this.effect.setParamValue(this.effect_start, this.pathTable[path], val);
                } else {
                    for (var i = 0; i < this.polyphony; i++) {
                        this.factory.setParamValue(this.dsp_voices[i], this.pathTable[path], val);
                    }
                }

            }

            this.getParamValue = function (path)
            {
                if (this.effect && getJSONeffect().includes(path)) {
                    return this.effect.getParamValue(this.effect_start, this.pathTable[path]);
                } else {
                    return this.factory.getParamValue(this.dsp_voices[0], this.pathTable[path]);
                }
            }

            // Init resulting DSP
            this.initAux();

            // Set message handler
            this.port.onmessage = this.handleMessage.bind(this);
        }

        handleMessage(event)
        {
            var msg = event.data;
            switch (msg.type) {
                // Generic MIDI message
                case "midi": this.midiMessage(msg.data); break;
                // Typed MIDI message
                case "keyOn": this.keyOn(msg.data[0], msg.data[1], msg.data[2]); break;
                case "keyOff": this.keyOff(msg.data[0], msg.data[1], msg.data[2]); break;
                case "ctrlChange": this.ctrlChange(msg.data[0], msg.data[1], msg.data[2]); break;
                case "pitchWheel": this.pitchWheel(msg.data[0], msg.data[1]); break;
                // Generic data message
                case "param": this.setParamValue(msg.key, msg.value); break;
                //case "patch": this.onpatch(msg.data); break;
            }
        }

        midiMessage(data)
        {
            var cmd = data[0] >> 4;
            var channel = data[0] & 0xf;
            var data1 = data[1];
            var data2 = data[2];

            if (channel === 9) {
                return;
            } else if (cmd === 8 || ((cmd === 9) && (data2 === 0))) {
                this.keyOff(channel, data1, data2);
            } else if (cmd === 9) {
                this.keyOn(channel, data1, data2);
            } else if (cmd === 11) {
                this.ctrlChange(channel, data1, data2);
            } else if (cmd === 14) {
                this.pitchWheel(channel, ((data2 * 128.0 + data1)-8192)/8192.0);
            }
        }

        process(inputs, outputs, parameters)
        {
            var input = inputs[0];
            var output = outputs[0];

            // Check inputs
            if (this.numIn > 0 && ((input === undefined) || (input[0].length === 0))) {
                //console.log("Process input error");
                return true;
            }
            // Check outputs
            if (this.numOut > 0 && ((output === undefined) || (output[0].length === 0))) {
                //console.log("Process output error");
                return true;
            }

            // Copy inputs
            if (input !== undefined) {
                for (var chan = 0; chan < Math.min(this.numIn, input.length) ; ++chan) {
                    var dspInput = this.dspInChannnels[chan];
                    dspInput.set(input[chan]);
                }
            }

            // Possibly call an externally given callback (for instance to synchronize playing a MIDIFile...)
            if (this.compute_handler) {
                this.compute_handler(mydspPolyProcessor.buffer_size);
            }

            // First clear the outputs
            this.mixer.clearOutput(mydspPolyProcessor.buffer_size, this.numOut, this.outs);

            // Compute all running voices
            for (var i = 0; i < this.polyphony; i++) {
                if (this.dsp_voices_state[i] != this.kFreeVoice) {
                    if (this.dsp_voices_trigger[i]) {
                        // FIXME : properly cut the buffer in 2 slices...
                        this.factory.setParamValue(this.dsp_voices[i], this.fGateLabel, 0.0);
                        this.factory.compute(this.dsp_voices[i], 1, this.ins, this.mixing);
                        this.factory.setParamValue(this.dsp_voices[i], this.fGateLabel, 1.0);
                        this.factory.compute(this.dsp_voices[i], mydspPolyProcessor.buffer_size, this.ins, this.mixing);
                        this.dsp_voices_trigger[i] = false;
                    } else {
                        // Compute regular voice
                        this.factory.compute(this.dsp_voices[i], mydspPolyProcessor.buffer_size, this.ins, this.mixing);
                    }
                    // Mix it in result
                    this.dsp_voices_level[i] = this.mixer.mixVoice(mydspPolyProcessor.buffer_size, this.numOut, this.mixing, this.outs);
                    // Check the level to possibly set the voice in kFreeVoice again
                    if ((this.dsp_voices_level[i] < 0.001) && (this.dsp_voices_state[i] === this.kReleaseVoice)) {
                        this.dsp_voices_state[i] = this.kFreeVoice;
                    }
                }
            }

            // Apply effect
            if (this.effect) {
                this.effect.compute(this.effect_start, mydspPolyProcessor.buffer_size, this.outs, this.outs);
            }

            // Update bargraph
            this.update_outputs();

            // Copy outputs
            if (output !== undefined) {
                for (var chan = 0; chan < Math.min(this.numOut, output.length); ++chan) {
                    var dspOutput = this.dspOutChannnels[chan];
                    output[chan].set(dspOutput);
                }
            }

            return true;
        }
    }

    // Globals

    mydspPolyProcessor.buffer_size = 128;
    mydspPolyProcessor.polyphony = MAX_POLYPHONY;

    // Synchronously compile the WASM modules
    try {
        mydspPolyProcessor.wasm_mixer_module = new WebAssembly.Module(mydspPolyProcessor.atob(getBase64Mixer()));
        mydspPolyProcessor.wasm_module = new WebAssembly.Module(mydspPolyProcessor.atob(getBase64Codemydsp()));
        // Possibly compile effect
        if (getBase64Codeeffect() !== "") {
            mydspPolyProcessor.wasm_effect_module = new WebAssembly.Module(mydspPolyProcessor.atob(getBase64Codeeffect()));
        }
        registerProcessor('mydspPoly', mydspPolyProcessor);
    } catch (e) {
        console.log(e); console.log("Faust mydspPoly cannot be loaded or compiled");
    }

`;

// DSP poly

faust.createPolyDSPWorkletInstanceAux = function (factory, context, polyphony, callback)
{
    // Resume audio context each time...
    context.resume();

	// Create a generic AudioWorkletNode, use polyphony to distinguish different classes
	var audio_node = new AudioWorkletNode(context, factory.name + '_' + polyphony.toString() + "Poly",
                                          { numberOfInputs: (parseInt(factory.json_object.inputs) > 0) ? 1 : 0,
                                            numberOfOutputs: (parseInt(factory.json_object.outputs) > 0) ? 1 : 0,
                                            channelCount: Math.max(1, parseInt(factory.json_object.inputs)),
                                            outputChannelCount: [parseInt(factory.json_object.outputs)],
                                            channelCountMode: "explicit",
                                            channelInterpretation: "speakers" });
    audio_node.onprocessorerror = () => { console.log('An error from mydspPolyProcessor was detected.');}
    // Patch it with additional functions
    audio_node.handleMessage = function(event)
    {
        var msg = event.data;
        if (this.output_handler) {
            this.output_handler(msg.path, msg.value);
        }
    }

    audio_node.init = function()
    {
        // JSON parsing functions
        this.parse_ui = function(ui, obj)
        {
            for (var i = 0; i < ui.length; i++) {
                this.parse_group(ui[i], obj);
            }
        }

        this.parse_group = function(group, obj)
        {
            if (group.items) {
                this.parse_items(group.items, obj);
            }
        }

        this.parse_items = function(items, obj)
        {
            for (var i = 0; i < items.length; i++) {
                this.parse_item(items[i], obj);
            }
        }

        this.parse_item = function(item, obj)
        {
            if (item.type === "vgroup"
                || item.type === "hgroup"
                || item.type === "tgroup") {
                this.parse_items(item.items, obj);
            } else if (item.type === "hbargraph"
                       || item.type === "vbargraph") {
                // Keep bargraph adresses
                obj.outputs_items.push(item.address);
            } else if (item.type === "vslider"
                       || item.type === "hslider"
                       || item.type === "button"
                       || item.type === "checkbox"
                       || item.type === "nentry") {
                // Keep inputs adresses
                obj.inputs_items.push(item.address);
            }
        }

        this.output_handler = null;

        // input/output items
        this.inputs_items = [];
        this.outputs_items = [];

        // Parse UI
        this.parse_ui(factory.json_object.ui, this);

        if (factory.effect_json_object) {
            this.parse_ui(factory.effect_json_object.ui, this);
        }

        // Set message handler
        this.port.onmessage = this.handleMessage.bind(this);
    }

    // Calls init
    audio_node.init();

    audio_node.getJSON = function()
    {
        var res = "";
        res = res.concat("{\"name\":\""); res = res.concat(factory.json_object.name); res = res.concat("\",");
        res = res.concat("\"version\":\""); res = res.concat(factory.json_object.version); res = res.concat("\",");
        res = res.concat("\"options\":\""); res = res.concat(factory.json_object.options); res = res.concat("\",");
        res = res.concat("\"inputs\":\""); res = res.concat(factory.json_object.inputs); res = res.concat("\",");
        res = res.concat("\"outputs\":\""); res = res.concat(factory.json_object.outputs); res = res.concat("\",");
        res = res.concat("\"meta\":"); res = res.concat(JSON.stringify(factory.json_object.meta)); res = res.concat(",");

        if (factory.effect_json_object) {
            res = res.concat("\"ui\":[{\"type\":\"tgroup\",\"label\":\"Sequencer\",\"items\":[");
            res = res.concat("{\"type\": \"vgroup\",\"label\":\"Instrument\",\"items\":");
            res = res.concat(JSON.stringify(factory.json_object.ui));
            res = res.concat("},");
            res = res.concat("{\"type\":\"vgroup\",\"label\":\"Effect\",\"items\":");
            res = res.concat(JSON.stringify(factory.effect_json_object.ui));
            res = res.concat("}");
            res = res.concat("]}]}");
            return res;
        } else {
            res = res.concat("\"ui\":[{\"type\":\"tgroup\",\"label\":\"Polyphonic\",\"items\":[");
            res = res.concat("{\"type\": \"vgroup\",\"label\":\"Voices\",\"items\":");
            res = res.concat(JSON.stringify(factory.json_object.ui));
            res = res.concat("},");
            res = res.concat("]}]}");
            return res;
        }
    }

    audio_node.setParamValue = function(path, val)
    {
        this.port.postMessage({ type:"param", key:path, value:val });
        this.parameters.get(path).setValueAtTime(val, 0);
    }
    audio_node.getParamValue = function(path) { return this.parameters.get(path).value; }

    audio_node.setOutputParamHandler = function(handler) { this.output_handler = handler; }
    audio_node.getOutputParamHandler = function() { return this.output_handler; }

    audio_node.getNumInputs = function() { return parseInt(factory.json_object.inputs); }
    audio_node.getNumOutputs = function() { return parseInt(factory.json_object.outputs); }

    audio_node.getParams = function() { return this.inputs_items; }

    /**
     * Instantiates a new polyphonic voice.
     *
     * @param channel - the MIDI channel (0..15, not used for now)
     * @param pitch - the MIDI pitch (0..127)
     * @param velocity - the MIDI velocity (0..127)
     */
    audio_node.keyOn = function(channel, pitch, velocity)
    {
        this.port.postMessage({ type: "keyOn", data: [channel, pitch, velocity] });
    }

    /**
     * De-instantiates a polyphonic voice.
     *
     * @param channel - the MIDI channel (0..15, not used for now)
     * @param pitch - the MIDI pitch (0..127)
     * @param velocity - the MIDI velocity (0..127)
     */
    audio_node.keyOff = function(channel, pitch, velocity)
    {
        this.port.postMessage({ type: "keyOff", data: [channel, pitch, velocity] });
    }

    /**
     * Gently terminates all the active voices.
     */
    audio_node.allNotesOff = function()
    {
        this.port.postMessage({ type: "ctrlChange", data: [channel, 123, 0] });
    }

    audio_node.ctrlChange = function(channel, ctrl, value)
    {
        this.port.postMessage({ type: "ctrlChange", data: [channel, ctrl, value] });
    }

    audio_node.pitchWheel = function(channel, wheel)
    {
        this.port.postMessage({ type: "pitchWheel", data: [channel, wheel] });
    }

    audio_node.midiMessage = function(data)
    {
        this.port.postMessage({ type:"midi", data:data });
    }

    audio_node.metadata = function (handler) {}

    // And use it
    callback(audio_node);
}

/**
 * Create a 'polyphonic' AudioWorklet Web Audio object from a factory
 *
 * @param factory - the DSP factory
 * @param context - the Web Audio context
 * @param polyphony - the number of polyphonic voices
 * @param callback - a callback taking the created AudioWorklet as parameter, or null in case of error
 */
faust.createPolyDSPWorkletInstance = function(factory, context, polyphony, callback)
{
    if (factory.polyphony.indexOf(polyphony) === -1) {
        var re1 = /mydsp/g;
        var re2 = /MAX_POLYPHONY/g;
        var re3 = /GETJSON/g;
        var re4 = /GETBASE64CODE/g;

        // Use polyphony to distinguish different classes
        var mydspPolyProcessorString1 = mydspPolyProcessorString.replace(re1, factory.name + '_' + polyphony.toString());
        var mydspPolyProcessorString2 = mydspPolyProcessorString1.replace(re2, polyphony);
        var mydspPolyProcessorString3 = mydspPolyProcessorString2.replace(re3, factory.getJSON());
        var mydspPolyProcessorString4 = mydspPolyProcessorString3.replace(re4, factory.getBase64Code());

        var url = null;
        // Is there is an effect to compile
        if (factory.name_effect) {
            var re5 = /CODE1/g;
            var re6 = /CODE2/g;
            var mydspPolyProcessorString5 = mydspPolyProcessorString4.replace(re5, factory.getJSONeffect());
            var mydspPolyProcessorString6 = mydspPolyProcessorString5.replace(re6, factory.getBase64Codeeffect());
            url = window.URL.createObjectURL(new Blob([mydspPolyProcessorString6], { type: 'text/javascript' }));
        } else {
            var re5 = /CODE1/g;
            var re6 = /CODE2/g;
            var mydspPolyProcessorString5 = mydspPolyProcessorString4.replace(re5, "");
            var mydspPolyProcessorString6 = mydspPolyProcessorString5.replace(re6, "");
            url = window.URL.createObjectURL(new Blob([mydspPolyProcessorString6], { type: 'text/javascript' }));
        }

        context.audioWorklet.addModule(url)
        .then(function () {
              // Processor has been registered
              factory.polyphony.push(polyphony);
              // Create audio node
              faust.createPolyDSPWorkletInstanceAux(factory, context, polyphony, callback);
        })
        .catch(function(error) { console.log(error); console.log("Faust mydspPoly cannot be loaded or compiled"); alert(error); });

    } else {
        // Create audio node
        faust.createPolyDSPWorkletInstanceAux(factory, context, polyphony, callback);
    }
}

faust.deletePolyDSPWorkletInstance = function (dsp) {}
