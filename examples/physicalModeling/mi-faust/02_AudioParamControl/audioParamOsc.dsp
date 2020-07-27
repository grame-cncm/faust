declare name    "Audio Param Oscillator";
declare author  "James Leonard";
declare date    "April 2020";

/* ========= DESCRITPION =============

A basic oscillator with labelled stiffness and damping parameters, controlled by sliders
    - inputs: force impulse
    - outputs: oscillator' position.
    - controls: stiffness and damping.
*/

import("stdfaust.lib");

in1 = button("Force Impulse"): ba.impulsify;
in2 = hslider("Stiffness", 0.01, 0, 0.1, 0.0001):si.smoo; 
in3 = hslider("Damping", 0.0001, 0, 0.005, 0.000001):si.smoo;

OutGain = 0.05;

K = in2;
Z = in3;

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

@K audioParam @in2
@Z audioParam @in3

# Integrated harmonic oscillator 
# with param-controlled K and Z
@o osc 1. K Z 0. 0.

# Add force input to the model
@in1 frcInput @o

# Add position output from the oscillator
@out1 posOutput @o

# end of MIMS script

*/