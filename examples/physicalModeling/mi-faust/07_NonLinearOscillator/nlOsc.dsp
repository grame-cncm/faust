declare name    "Non Linear Oscillator";
declare author  "James Leonard";
declare date    "April 2020";

/* ========= DESCRITPION =============

A non-linear oscillator (containing a cubic stiffness term, making pitch amplitude dependant)
    - inputs: force impulse
    - outputs: oscillator position.
    - controls: value of the non-linear stiffness component.

Note: we are using the nlSpringDamperClipped interaction that defines an upper bound for stiffness.
This can save from numerical divergence when large displacements cause very large reaction forces.
*/

import("stdfaust.lib");

in1 = button("Hammer Input Force"): ba.impulsify* -0.1;

OutGain = 1;

nlK = hslider("non-linear stiffness", 0.005, 0., 0.1, 0.0001);

model = (
	mi.mass(1., 0, 0., 0.),
	mi.ground(0.),
	mi.mass(0.3, 0, 1., 1.),
	mi.ground(1.),
	par(i, nbFrcIn,_):
	RoutingMassToLink ,
	par(i, nbFrcIn,_):
	mi.nlSpringDamperClipped(0.03, nlK, 0.8, 0.0002, 0., 0.),
	mi.springDamper(0.0001, 0.05, 1., 1.),
	mi.collision(0.1, 0.001, 0, 0., 1.),
	par(i, nbOut+nbFrcIn, _):
	RoutingLinkToMass
)~par(i, nbMass, _):
par(i, nbMass, !), par(i, nbOut , _)
with{
	RoutingMassToLink(m0, m1, m2, m3) = /* routed positions */ m1, m0, m3, m2, m0, m2, /* outputs */ m0;
	RoutingLinkToMass(l0_f1, l0_f2, l1_f1, l1_f2, l2_f1, l2_f2, p_out1, f_in1) = /* routed forces  */ l0_f2 + l2_f1, l0_f1, f_in1 + l1_f2 + l2_f2, l1_f1, /* pass-through */ p_out1;
	nbMass = 4;
	nbFrcIn = 1;
	nbOut = 1;
};
process = in1 : model:*(OutGain);

/*
========= MIMS SCRIPT USED FOR MODEL GENERATION =============

# MIMS script file
# Script author: James Leonard

@nlK param 0.005

# Build a non-linear harmonic oscillator 
@m mass 1. 0. 0.
@g ground 0.
@nl nlSpringDamper @g @m 0.03 nlK 0.8 0.0002

# A slow moving oscillator placed above the other
# serving as a hammer
@ham mass 0.3 1. 0.
@g2 ground 1.
@sp springDamper @g2 @ham 0.0001 0.05

# Add force input to the hammer
@in1 frcInput @ham

@c contact @m @ham 0.1 0.001

# Add position output from the oscillator
@out1 posOutput @m
# @out2 posOutput @ham

# end of MIMS script

*/