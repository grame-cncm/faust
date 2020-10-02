var options = "-I libraries/";
var errCode = "foo";
var effectCode = "process = _,_;";

//----------------------------------------------------------------------------
// Misc. functions
//----------------------------------------------------------------------------
function misc(faust, log, code) {
	let exp = faust.expandDSP("test", code, options);
	let msg = exp.error ? exp.error : exp.dsp + " sha " + exp.shakey;
	log("  expandDSP             " + msg);

	let aux = faust.generateAuxFiles("test", code, options + " -lang wast/wasm");
	msg = aux.success ? "done" : aux.error;
	log("  generateAuxFiles      " + msg);
}

//----------------------------------------------------------------------------
// create dsp factory and instance 
//----------------------------------------------------------------------------
async function createDsp(faust, log, code) {
	log("createDSPFactory: ");
	let factory = await faust.createDSPFactory("test", code, options, false);
	log("factory JSON: " + factory.json);
	log("factory poly: " + factory.poly);

	log("createDSPInstance: ");
	let instance = await faust.createDSPInstance(factory);
	log("  getNumInputs : " + instance.api.getNumInputs());
	log("  getNumOutputs: " + instance.api.getNumOutputs());
	log("  JSON: " + instance.json);
}

async function createPolyDsp(faust, log, voice_code, effect_code) {
	log("createDSPFactory for voice: ");
	let voice_factory = await faust.createDSPFactory("voice", voice_code, options, true);
	log("voice factory JSON: " + voice_factory.json);
	log("voice factory poly: " + voice_factory.poly);

	log("createDSPFactory for effect: ");
	let effect_factory = await faust.createDSPFactory("effect", effect_code, options, true);
	log("effect factory JSON: " + effect_factory.json);
	log("effect factory poly: " + effect_factory.poly);

	const mixer_file = await fetch("mixer32.wasm");
	const mixer_buffer = await mixer_file.arrayBuffer();
	const mixer_module = await WebAssembly.compile(mixer_buffer);

	log("createPolyDSPInstance: ");
	let poly_instance = await faust.createPolyDSPInstance(voice_factory, mixer_module, 8, effect_factory);
	log("  voice_api getNumInputs : " + poly_instance.voice_api.getNumInputs());
	log("  voice_api getNumOutputs: " + poly_instance.voice_api.getNumOutputs());
	log("  JSON: " + poly_instance.voice_json);
	log("  effect_api getNumInputs : " + poly_instance.effect_api.getNumInputs());
	log("  effect_api getNumOutputs: " + poly_instance.effect_api.getNumOutputs());
	log("  JSON: " + poly_instance.effect_json);
}

var TestSVG1svg;
var TestSVG2svg;
//----------------------------------------------------------------------------
// Test svg diagrams
//----------------------------------------------------------------------------
function svgdiagrams(faust, log, code) {
	filter = "import(\"stdfaust.lib\");\nprocess = dm.oscrs_demo;";

	let svg1 = new Faust.SVGDiagrams(faust, "TestSVG1", code, options)
	if (!svg1.success()) {
		log(svg1.error());
	}
	else {
		log("success");
		let div1 = document.getElementById("svg1");
		div1.innerHTML = svg1.getSVG();
		TestSVG1svg = (path) => { div1.innerHTML = svg1.getSVG(path); }
	}

	let svg2 = new Faust.SVGDiagrams(faust, "TestSVG2", filter, options)
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
// Main entry point
//----------------------------------------------------------------------------
async function run(engine, log, code, context) {
	let faust = new Faust.Compiler(engine);
	log("libfaust version: " + faust.version());

	log("\n-----------------\nMisc tests" + faust.version());
	misc(faust, log, code);
	log("\n-----------------\nMisc tests with error code");
	misc(faust, log, errCode);

	log("\n-----------------\nCreating DSP instance:");
	await createDsp(faust, log, code);

	// log("\n-----------------\nCreating Poly DSP instance:");
	// await createPolyDsp(faust, log, code, effectCode);

	log("\n-----------------\nCreating DSP instance with error code:");
	await createDsp(faust, log, errCode).catch(e => { log(e); });

	log("\n-----------------\nTest SVG diagrams: ");
	svgdiagrams(engine, log, code);

	// Test nodes
	let factory = await faust.createDSPFactory("test", code, options, false);
	console.log(factory);
	console.log(context);
	let fwan = new Faust.AudioNodeFactory();
	let node = await fwan.createMonoNode(context, "test", factory, true, 512);
	console.log(node);
	console.log(node.getParams());
	console.log(node.getJSON());
	//node.setParamValue("/test/Volume", 0.5);
	node.connect(context.destination);

	log("\nEnd of API tests");
}

if ((typeof process !== 'undefined') && (process.release.name === 'node')) {
	module.exports = run;
}
