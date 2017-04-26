//----------------------`wind`--------------------------
// A very simple wind simulator, based on a filtered white noise
//
// #### Usage
//
// ```
//  wind(f) : _
// ```
//
// Where:
//
// * `f`: is the force of the wind: between 0 and 1
//
//----------------------------------------------------------

import("stdfaust.lib");

wind(force) = no.multinoise(2) : par(i, 2, ve.moog_vcf_2bn(force,freq)) : par(i, 2, *(force))
	with {
		freq = (force*87)+1 : ba.pianokey2hz;
	};

process = wind ( hslider("v:wind/force",0.66,0,1,0.01) : si.smooth (0.997) );
