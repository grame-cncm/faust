declare name    "Plucked Oscillator";
declare author  "James Leonard";
declare date    "April 2020";

/* ========= DESCRITPION =============

Plucking a simple oscillator
    - inputs: position control of the "plucking" mass
    - outputs: oscillator position.
    - controls: none.
*/

import("stdfaust.lib");

in1 = hslider("Pluck Position", 0, -1, 1, 0.001):si.smoo;

OutGain = 8;

model = (
	mi.oscil(1., 0.1, 0.0003, 0, 0., 0.),
	mi.posInput(1.):
	RoutingMassToLink :
	mi.nlPluck(0.5, 0.1, 0.001, 0., 1.),
	par(i, nbOut, _):
	RoutingLinkToMass
)~par(i, nbMass, _):
par(i, nbMass, !), par(i, nbOut , _)
with{
	RoutingMassToLink(m0, m1) = /* routed positions */ m0, m1, /* outputs */ m0, m1;
	RoutingLinkToMass(l0_f1, l0_f2, p_out1, p_out2) = /* routed forces  */ l0_f1, l0_f2, /* pass-through */ p_out1, p_out2;
	nbMass = 2;
	nbOut = 2;
};
process = in1 : model:*(OutGain), *(OutGain);


/*
========= MIMS SCRIPT USED FOR MODEL GENERATION =============

# MIMS script file
# Script author: James Leonard

# Integrated harmonic oscillator 
@o osc 1. 0.1 0.0003 0. 0.

# Position input, controlled by audio signal
@in1 posInput 1.

@pl nlPluck @o @in1 0.5 0.1 0.001

# Add position output from the oscillator
@out1 posOutput @o
@out2 posOutput @in1

# end of MIMS script

*/