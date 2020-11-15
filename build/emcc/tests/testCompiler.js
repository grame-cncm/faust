var options = "-ftz 0 -I libraries/";
var errCode = "foo";
var effectCode = 'process = _*(hslider("Left", 0.1, 0, 1, 0.01)), _*(hslider("Right", 0.0, 0, 1, 0.01));';

//----------------------------------------------------------------------------
// Misc. functions
//----------------------------------------------------------------------------
function misc(faust, log, code) {
    let exp = faust.expandDSP("test", code, options);
    let msg = (exp) ? exp : faust.getErrorMessage();
    log("  expandDSP             " + msg);

    let res = faust.generateAuxFiles("test", code, options + " -svg");
    msg = (res) ? "done" : faust.getErrorMessage();
    log("  generateAuxFiles      " + msg);

}
//----------------------------------------------------------------------------
// create dsp factory and instance 
//----------------------------------------------------------------------------
async function createDsp(faust, log, code) {
    let gen = Faust.createGenerator();

    log("createMonoDSPFactory: ");
    let factory = await faust.createMonoDSPFactory("test", code, options);
    if (factory) {
        log("factory JSON: " + factory.json);
        log("factory poly: " + factory.poly);
    } else {
        log("factory is null");
        return;
    }
    log("deleteDSPFactory");
    faust.deleteDSPFactory(factory);

    log("createSyncMonoDSPInstance: ");
    let instance1 = gen.createSyncMonoDSPInstance(factory);
    if (instance1) {
        log("  getNumInputs : " + instance1.api.getNumInputs());
        log("  getNumOutputs: " + instance1.api.getNumOutputs());
        log("  JSON: " + instance1.json);
    } else {
        log("instance1 is null");
    }

    log("createAsyncMonoDSPInstance: ");
    let instance2 = await gen.createAsyncMonoDSPInstance(factory);
    if (instance2) {
        log("  getNumInputs : " + instance2.api.getNumInputs());
        log("  getNumOutputs: " + instance2.api.getNumOutputs());
        log("  JSON: " + instance2.json);
    } else {
        log("instance2 is null");
    }
}

async function createPolyDsp(faust, log, voice_code, effect_code) {
    let gen = Faust.createGenerator();

    log("createPolyDSPFactory for voice: ");
    let voice_factory = await faust.createPolyDSPFactory("voice", voice_code, options);
    if (voice_factory) {
        log("voice factory JSON: " + voice_factory.json);
        log("voice factory poly: " + voice_factory.poly);
    } else {
        log("voice_factory is null");
        return;
    }
    log("createPolyDSPFactory for effect: ");
    let effect_factory = await faust.createPolyDSPFactory("effect", effect_code, options);
    if (effect_factory) {
        log("effect factory JSON: " + effect_factory.json);
        log("effect factory poly: " + effect_factory.poly);
    } else {
        log("effect_factory is null");
    }

    const mixer_file = await fetch("mixer32.wasm");
    const mixer_buffer = await mixer_file.arrayBuffer();
    const mixer_module = await WebAssembly.compile(mixer_buffer);

    log("createSyncPolyDSPInstance: ");
    let poly_instance1 = gen.createSyncPolyDSPInstance(voice_factory, mixer_module, 8, effect_factory);
    if (poly_instance1) {
        log("  voice_api getNumInputs : " + poly_instance1.voice_api.getNumInputs());
        log("  voice_api getNumOutputs: " + poly_instance1.voice_api.getNumOutputs());
        log("  JSON: " + poly_instance1.voice_json);
        log("  effect_api getNumInputs : " + poly_instance1.effect_api.getNumInputs());
        log("  effect_api getNumOutputs: " + poly_instance1.effect_api.getNumOutputs());
        log("  JSON: " + poly_instance1.effect_json);
    } else {
        log("poly_instance1 is null");
    }

    log("createAsyncPolyDSPInstance: ");
    let poly_instance2 = await gen.createAsyncPolyDSPInstance(voice_factory, mixer_module, 8, effect_factory);
    if (poly_instance2) {
        log("  voice_api getNumInputs : " + poly_instance2.voice_api.getNumInputs());
        log("  voice_api getNumOutputs: " + poly_instance2.voice_api.getNumOutputs());
        log("  JSON: " + poly_instance2.voice_json);
        log("  effect_api getNumInputs : " + poly_instance2.effect_api.getNumInputs());
        log("  effect_api getNumOutputs: " + poly_instance2.effect_api.getNumOutputs());
        log("  JSON: " + poly_instance2.effect_json);
    } else {
        log("poly_instance2 is null");
    }
}

var TestSVG1svg;
var TestSVG2svg;
//----------------------------------------------------------------------------
// Test svg diagrams
//----------------------------------------------------------------------------
function svgdiagrams(faust, log, code) {
    filter = "import(\"stdfaust.lib\");\nprocess = dm.oscrs_demo;";

    let svg1 = Faust.createSVGDiagrams(faust, "TestSVG1", code, options)
    if (!svg1.success()) {
        log(svg1.error());
    }
    else {
        log("success");
        let div1 = document.getElementById("svg1");
        div1.innerHTML = svg1.getSVG();
        TestSVG1svg = (path) => { div1.innerHTML = svg1.getSVG(path); }
    }

    let svg2 = Faust.createSVGDiagrams(faust, "TestSVG2", filter, options)
    if (!svg2.success()) {
        log(svg2.error());
    }
    else {
        log("success");
        let div2 = document.getElementById("svg2");
        div2.innerHTML = svg2.getSVG();
        TestSVG2svg = (path) => { div2.innerHTML = svg2.getSVG(path); }
    }
}

//----------------------------------------------------------------------------
// Test offline processor
//----------------------------------------------------------------------------
async function offlineProcessor(faust, log) {

    let signal = "import(\"stdfaust.lib\");\nprocess = 0.25,0.33, 0.6;";
    let factory = await faust.createMonoDSPFactory("test", signal, options);
    let fwan = Faust.createAudioNodeFactory();

    log("offlineProcessor");
    let offline = await fwan.createOfflineMonoProcessor(factory, 44100, 32);
    let plotted = offline.plot(100);
    for (let chan = 0; chan < plotted.length; chan++) {
        for (let frame = 0; frame < 100; frame++) {
            console.log("Chan %d sample %f\n", chan, plotted[chan][frame])
        }
    }
}

//----------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------
async function run(engine, log, code, context) {

    let faust = Faust.createCompiler(engine);

    log("libfaust version: " + faust.version());

    log("\n-----------------\nMisc tests" + faust.version());
    misc(faust, log, code);
    log("\n-----------------\nMisc tests with error code");
    misc(faust, log, errCode);

    log("\n-----------------\nCreating DSP instance:");
    await createDsp(faust, log, code);


    log("\n-----------------\nCreating Poly DSP instance:");
    await createPolyDsp(faust, log, code, effectCode);


    log("\n-----------------\nCreating DSP instance with error code:");
    await createDsp(faust, log, errCode).catch(e => { log(e); });

    log("\n-----------------\nCreating Poly DSP instance with error code:");
    await createPolyDsp(faust, log, errCode, effectCode).catch(e => { log(e); });

    log("\n-----------------\nTest SVG diagrams: ");
    svgdiagrams(engine, log, code);

    log("\n-----------------\nTest Offline processor ");
    offlineProcessor(faust, log);

    // Test nodes

    // Created with libfaust.js

    /*
    let factory = await faust.createMonoDSPFactory("test", code, options);
    console.log(factory);
    console.log(context);
    let fwan = faust.createAudioNodeFactory();
    */

    /*
    // Testing SP mode
    let node = await fwan.createMonoNode(context, "test", factory, true, 512);
    console.log(node);
    console.log(node.getParams());
    console.log(node.getJSON());
    node.setParamValue("/test/freq", 300);
    node.connect(context.destination);
    node.setPlotHandler((output, index, events) => { console.log(index); console.log(events); });
    */

    /*
    // Testing Worklet mode
    let node1 = await fwan.createMonoNode(context, "mydsp1", factory, false);
    console.log(node1);
    console.log(node1.getParams());
    console.log(node1.getJSON());
    node1.setParamValue("/test/freq", 700);
    node1.connect(context.destination);
    node1.setPlotHandler((output, index, events) => { console.log(index); console.log(events); });
    */

    /*
    let node2 = await fwan.createMonoNode(context, "mydsp2", factory, false);
    console.log(node2);
    console.log(node2.getParams());
    console.log(node2.getJSON());
    node2.setParamValue("/test/freq", 200);
    node2.connect(context.destination);
    */

    // Polyphonic factory
    let factory = await faust.createPolyDSPFactory("test", code, options);
    console.log(factory);
    console.log(context);

    let fwan = Faust.createAudioNodeFactory();
    const mixer_file = await fetch("mixer32.wasm");
    const mixer_buffer = await mixer_file.arrayBuffer();
    const mixer_module = await WebAssembly.compile(mixer_buffer);

    /*
    // Testing polyphonic SP mode
    let node3 = await fwan.createPolyNode(context, "mydsp2", factory, mixer_module, 8, true, null, 512);
    console.log(node3);
    console.log(node3.getParams());
    console.log(node3.getJSON());
    //node3.setParamValue("/test/freq", 600);
    node3.connect(context.destination);
    node3.keyOn(0, 60, 50);
    //node3.keyOn(0, 64, 50);
    node3.keyOn(0, 67, 50);
    //node3.keyOn(0, 71, 50);
    //node3.keyOn(0, 76, 50);
    node3.setPlotHandler((output, index, events) => { console.log(index); console.log(events); });
    */

    // Testing polyphonic Worklet mode
    let node3 = await fwan.createPolyNode(context, "mydsp2", factory, mixer_module, 8, false);
    console.log(node3);
    console.log(node3.getParams());
    console.log(node3.getJSON());
    //node3.setParamValue("/test/freq", 600);
    node3.connect(context.destination);
    node3.keyOn(0, 60, 50);
    node3.keyOn(0, 64, 50);
    node3.keyOn(0, 67, 50);
    node3.keyOn(0, 71, 50);
    node3.keyOn(0, 76, 50);
    //node3.setPlotHandler((output, index, events) => { console.log(index); console.log(events); });

    /*
    // Testing polyphonic Worklet mode
    let node4 = await fwan.createPolyNode(context, "mydsp3", factory, mixer_module, 16, false);
    console.log(node4);
    console.log(node4.getParams());
    console.log(node4.getJSON());
    //node4.setParamValue("/test/freq", 600);
    node4.connect(context.destination);
    node4.keyOn(0, 70, 50);
    node4.keyOn(0, 74, 50);
    node4.keyOn(0, 77, 50);
    node4.keyOn(0, 81, 50);
    //node3.keyOn(0, 76, 50);
    */

    /*
    // Testing polyphonic SP mode
    console.log(faust);
    let node5 = await fwan.compilePolyNode(context, "mydsp2", faust, code, options, 8, true, 512);
    console.log(node5);
    console.log(node5.getParams());
    console.log(node5.getJSON());
    //node5.setParamValue("/test/freq", 600);
    node5.connect(context.destination);
    node5.keyOn(0, 60, 50);
    //node5.keyOn(0, 64, 50);
    node5.keyOn(0, 67, 50);
    //node5.keyOn(0, 71, 50);
    //node5.keyOn(0, 76, 50);
    */

    /*
    // Testing polyphonic Worklet mode
    console.log(faust);
    let node6 = await fwan.compilePolyNode(context, "mydsp2", faust, code, options, 8, false);
    console.log(node6);
    console.log(node6.getParams());
    console.log(node6.getJSON());
    //node6.setParamValue("/test/freq", 600);
    node6.connect(context.destination);
    node6.keyOn(0, 60, 50);
    //node6.keyOn(0, 64, 50);
    node6.keyOn(0, 67, 50);
    node6.keyOn(0, 71, 50);
    //node6.keyOn(0, 76, 50);
    */

    /*
    const factory1 = await Faust.createGenerator().loadDSPFactory("noise.wasm", "noise.js");
    const node = await Faust.createAudioNodeFactory().createMonoNode(context, "test", factory1, true, 512);
    console.log(node);
    console.log(node.getParams());
    console.log(node.getJSON());
    node.setParamValue("/Noise/Volume", 0.1);
    node.connect(context.destination);
    */

    log("\nEnd of API tests");
}

if ((typeof process !== 'undefined') && (process.release.name === 'node')) {
    module.exports = run;
}
