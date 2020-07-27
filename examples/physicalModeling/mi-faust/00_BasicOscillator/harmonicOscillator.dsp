declare name    "Harmonic Oscillator";
declare author  "James Leonard";
declare date    "April 2020";

/* ========= DESCRITPION =============

The simplest mass-interaction construct: a harmonic oscillator, containing only one physical element (mi.osc).
    - inputs: force impulse
    - outputs: oscillator' position.
    - controls: none.

Note: The routing pattern could be simplified here (cf.diagram), as the model contains no interaction elements.
*/

import("stdfaust.lib");

in1 = button("Frc Input 1"): ba.impulsify * 0.25;  	//write a specific force input signal operation here

OutGain = 1;

model = (
	mi.oscil(1., 0.1, 0.0003, 0, 0., 0.),
	par(i, nbFrcIn,_):
	RoutingMassToLink ,
	par(i, nbFrcIn,_):
		par(i, nbOut+nbFrcIn, _):
	RoutingLinkToMass
)~par(i, nbMass, _):
par(i, nbMass, !), par(i, nbOut , _)
with{
	RoutingMassToLink(m0) = /* routed positions */ /* outputs */ m0;
	RoutingLinkToMass(p_out1, f_in1) = /* routed forces  */ f_in1, /* pass-through */ p_out1;
	nbMass = 1;
	nbFrcIn = 1;
	nbOut = 1;
};
process = in1 : model:*(OutGain);


/*
========= MIMS SCRIPT USED FOR MODEL GENERATION =============

# MIMS script file
# Script author: James Leonard

# Integrated harmonic oscillator with M = 1, K = 0.1, Z = 0.0003
@o osc 1. 0.1 0.0003 0. 0.

# Add force input to the model
@in1 frcInput @o

# Add position output from the oscillator
@out1 posOutput @o


# end of MIMS script

*/