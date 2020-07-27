declare name    "2-mass Chain";
declare author  "James Leonard";
declare date    "April 2020";

/* ========= DESCRITPION =============

A logical step from a simple oscillator: a chain of two masses connected by spring-dampers,
fixed at one end to a fixed point !
    - inputs: force impulse on the last mass of the chain.
    - outputs: position of the last mass of the chain.
    - controls: none
*/

import("stdfaust.lib");

in1 = button("Frc Input 1"): ba.impulsify;

OutGain = 0.1;

K1 = 0.1;
Z1 = 0.0003;
K2 = 0.1;
Z2 = 0.0003;

model = (
	mi.ground(0.),
	mi.mass(1., 0, 0., 0.),
	mi.mass(1., 0, 0., 0.),
	par(i, nbFrcIn,_):
	RoutingMassToLink ,
	par(i, nbFrcIn,_):
	mi.springDamper(K1, Z1, 0., 0.),
	mi.springDamper(K2, Z2, 0., 0.),
	par(i, nbOut+nbFrcIn, _):
	RoutingLinkToMass
)~par(i, nbMass, _):
par(i, nbMass, !), par(i, nbOut , _)
with{
	RoutingMassToLink(m0, m1, m2) = /* routed positions */ m0, m1, m1, m2, /* outputs */ m2;
	RoutingLinkToMass(l0_f1, l0_f2, l1_f1, l1_f2, p_out1, f_in1) = /* routed forces  */ l0_f1, l0_f2 + l1_f1, f_in1 + l1_f2, /* pass-through */ p_out1;
	nbMass = 3;
	nbFrcIn = 1;
	nbOut = 1;
};
process = in1 : model:*(OutGain);


/*
========= MIMS SCRIPT USED FOR MODEL GENERATION =============

# MIMS script file
# Script author: James Leonard

@K1 param 0.1
@Z1 param 0.0003
@K2 param 0.1
@Z2 param 0.0003

@g ground 0.
@m1 mass 1. 0. 0.
@m2 mass 1. 0. 0.

@s1 springDamper @g @m1 K1 Z1
@s2 springDamper @m1 @m2 K2 Z2

# Add force input to the model
@in1 frcInput @m2

# Add position output from the oscillator
@out1 posOutput @m2


# end of MIMS script

*/