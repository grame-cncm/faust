importScripts('http://faust.grame.fr/www/libfaust.js');
importScripts('http://faust.grame.fr/www/webaudio-asm-wrapper.js');

onmessage = function(e){

	var factory = faust.createDSPFactory(e.data, ["-I", "http://faust.grame.fr/faustcode/"]);
	
	postMessage(factory);
}
