declare name    "Param Oscillator";
declare author  "James Leonard";
declare date    "April 2020";

/* ========= DESCRITPION =============

A basic oscillator with labelled stiffness and damping parameters
    - inputs: force impulse
    - outputs: oscillator' position.
    - controls: none.
*/

import("stdfaust.lib");
import("mi.lib");

in1 = button("Frc Input 1"): ba.impulsify* 0.25;

OutGain = 1;

K = 0.1;
Z = 0.0003;

model = (
	mi.oscil(1., K, Z, 0, 0., 0.),
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

@K param 0.1
@Z param 0.0003

# Integrated harmonic oscillator 
# with param-controlled K and Z
@o osc 1. K Z 0. 0.

# Add force input to the model
@in1 frcInput @o

# Add position output from the oscillator
@out1 posOutput @o

# end of MIMS script

*/