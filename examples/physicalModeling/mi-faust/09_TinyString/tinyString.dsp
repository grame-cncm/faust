declare name    "Tiny String";
declare author  "James Leonard";
declare date    "April 2020";

/* ========= DESCRITPION =============

A small string, composed of 8 masses and two fixed points, connected by spring-dampers
    - inputs: force impulse on mass 7.
    - outputs: position of mass 2.
    - controls: none

Note: the model block diagram is starting to get more complex, but it's still readable.    
*/

import("stdfaust.lib");

in1 = button("Force Impulse"): ba.impulsify;

OutGain = 0.6;

stiffness = 0.5;
damping = 0.0003;

model = (
	mi.ground(0.),
	mi.mass(1., 0, 0., 0.),
	mi.mass(1., 0, 0., 0.),
	mi.mass(1., 0, 0., 0.),
	mi.mass(1., 0, 0., 0.),
	mi.mass(1., 0, 0., 0.),
	mi.mass(1., 0, 0., 0.),
	mi.mass(1., 0, 0., 0.),
	mi.mass(1., 0, 0., 0.),
	mi.ground(0.),
	par(i, nbFrcIn,_):
	RoutingMassToLink ,
	par(i, nbFrcIn,_):
	mi.springDamper(stiffness, damping, 0., 0.),
	mi.springDamper(stiffness, damping, 0., 0.),
	mi.springDamper(stiffness, damping, 0., 0.),
	mi.springDamper(stiffness, damping, 0., 0.),
	mi.springDamper(stiffness, damping, 0., 0.),
	mi.springDamper(stiffness, damping, 0., 0.),
	mi.springDamper(stiffness, damping, 0., 0.),
	mi.springDamper(stiffness, damping, 0., 0.),
	mi.springDamper(stiffness, damping, 0., 0.),
	par(i, nbOut+nbFrcIn, _):
	RoutingLinkToMass
)~par(i, nbMass, _):
par(i, nbMass, !), par(i, nbOut , _)
with{
	RoutingMassToLink(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9) = /* routed positions */ m0, m1, m1, m2, m2, m3, m3, m4, m4, m5, m5, m6, m6, m7, m7, m8, m8, m0, /* outputs */ m2;
	RoutingLinkToMass(l0_f1, l0_f2, l1_f1, l1_f2, l2_f1, l2_f2, l3_f1, l3_f2, l4_f1, l4_f2, l5_f1, l5_f2, l6_f1, l6_f2, l7_f1, l7_f2, l8_f1, l8_f2, p_out1, f_in1) = /* routed forces  */ l0_f1 + l8_f2, l0_f2 + l1_f1, l1_f2 + l2_f1, l2_f2 + l3_f1, l3_f2 + l4_f1, l4_f2 + l5_f1, l5_f2 + l6_f1, f_in1 + l6_f2 + l7_f1, l7_f2 + l8_f1, 0, /* pass-through */ p_out1;
	nbMass = 10;
	nbFrcIn = 1;
	nbOut = 1;
};
process = in1 : model:*(OutGain);


/*
========= MIMS SCRIPT USED FOR MODEL GENERATION =============

# MIMS script file
# Script author: James Leonard

@stiffness param 0.5
@damping param 0.0003

@g ground 0.
@m1 mass 1. 0. 0.
@m2 mass 1. 0. 0.
@m3 mass 1. 0. 0.
@m4 mass 1. 0. 0.
@m5 mass 1. 0. 0.
@m6 mass 1. 0. 0.
@m7 mass 1. 0. 0.
@m8 mass 1. 0. 0.
@g2 ground 0.

@s1 springDamper @g @m1 stiffness damping
@s2 springDamper @m1 @m2 stiffness damping
@s3 springDamper @m2 @m3 stiffness damping
@s4 springDamper @m3 @m4 stiffness damping
@s5 springDamper @m4 @m5 stiffness damping
@s6 springDamper @m5 @m6 stiffness damping
@s7 springDamper @m6 @m7 stiffness damping
@s8 springDamper @m7 @m8 stiffness damping
@s9 springDamper @m8 @g stiffness damping


# Add force input to the model
@in1 frcInput @m7

# Add position output from the string
@out1 posOutput @m2


# end of MIMS script

*/