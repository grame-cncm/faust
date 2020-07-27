declare name    "Bowed Oscillator";
declare author  "James Leonard";
declare date    "April 2020";

/* ========= DESCRITPION =============

Friction-based interaction with a simple oscillator => cool squeaky sounds.
    - inputs: position control of the "bowing" mass
    - outputs: oscillator position.
    - controls: none.

Note: the "type" parameter changes the way the friction interaction is calculated
(set to 0 for piecewise linear function or 1 for friction à-la-Bilbao).
*/

import("stdfaust.lib");

in1 = hslider("Bow Position", 0, 0, 100, 0.001):si.smoo:si.smoo:si.smoo; 	//Need very smooth position data here !

OutGain = 20;

type = 0;

model = (
	mi.oscil(1., 0.1, 0.0003, 0, 0., 0.),
	mi.posInput(1.):
	RoutingMassToLink :
	mi.nlBow(1.2, 0.001, type, 0., 1.),
	par(i, nbOut, _):
	RoutingLinkToMass
)~par(i, nbMass, _):
par(i, nbMass, !), par(i, nbOut , _)
with{
	RoutingMassToLink(m0, m1) = /* routed positions */ m0, m1, /* outputs */ m0;
	RoutingLinkToMass(l0_f1, l0_f2, p_out1) = /* routed forces  */ l0_f1, l0_f2, /* pass-through */ p_out1;
	nbMass = 2;
	nbOut = 1;
};
process = in1 : model:*(OutGain);


/*
========= MIMS SCRIPT USED FOR MODEL GENERATION =============

# MIMS script file
# Script author: James Leonard

# parameter to switch how the
# bowing interaction is calculated
@type param 0

# Integrated harmonic oscillator 
@o osc 1. 0.1 0.0003 0. 0.

# Position input, controlled by audio signal
@in1 posInput 1.

@b nlBow @o @in1 1.2 0.001 type

# Add position output from the oscillator
@out1 posOutput @o

# end of MIMS script

*/