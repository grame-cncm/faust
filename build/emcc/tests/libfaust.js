
"use strict";

//----------------------------------------------------------------------------
// the libfaust interface
//----------------------------------------------------------------------------
class libfaust {
	constructor() {
		this.fCompiler = 0;
	}
	
	//------------------------------------------------------------------------
	// async initialization
	initialize (lib) {
		if ((typeof process !== 'undefined') && (process.release.name === 'node')) {
			var module = require (lib);
			return new Promise ( (success) => {
					module().then ( (instance) => {
					this.moduleInit ( instance );
					success ( this ); 
				});
			});
		}
		else {
			var module = FaustModule();
			return new Promise ( (success, failure) => {
				module['onRuntimeInitialized'] = () => {
				this.moduleInit ( module );
				success ( this ); 
				}
			});
		}
	}
	
	//------------------------------------------------------------------------
	// async initialization
	moduleInit ( module ) {
		this.fCompiler = new module.libFaustWasm();
	}
	
	get faust() { return this.fCompiler; }
}


if ((typeof process !== 'undefined') && (process.release.name === 'node')) {
	module.exports = libfaust;
}
