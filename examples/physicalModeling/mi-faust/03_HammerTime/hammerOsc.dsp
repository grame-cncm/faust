declare name    "Hammered Oscillator";
declare author  "James Leonard";
declare date    "April 2020";

/* ========= DESCRITPION =============

An oscillator struck by a hammer (a second "loose" oscillator placed above it)
    - inputs: force impulse onto the hammer mass
    - outputs: oscillator and hammer positions.
    - controls: none.

Note: The "clicking" sound is because we are listening to the hammer mass position on the
second output channel. Listening to this mass allows to plot the collision, but if you 
were just interested in the oscillator's sound you should only listen to that.
*/

import("stdfaust.lib");

in1 = button("Frc Input 1"): ba.impulsify * -0.1;

OutGain = 1;

model = (
	mi.oscil(1., 0.1, 0.0003, 0, 0., 0.),
	mi.mass(0.3, 0, 1., 1.),
	mi.ground(1.),
	par(i, nbFrcIn,_):
	RoutingMassToLink ,
	par(i, nbFrcIn,_):
	mi.springDamper(0.0001, 0.05, 1., 1.),
	mi.collision(0.1, 0.001, 0, 0., 1.),
	par(i, nbOut+nbFrcIn, _):
	RoutingLinkToMass
)~par(i, nbMass, _):
par(i, nbMass, !), par(i, nbOut , _)
with{
	RoutingMassToLink(m0, m1, m2) = /* routed positions */ m2, m1, m0, m1, /* outputs */ m0, m1;
	RoutingLinkToMass(l0_f1, l0_f2, l1_f1, l1_f2, p_out1, p_out2, f_in1) = /* routed forces  */ l1_f1, f_in1 + l0_f2 + l1_f2, l0_f1, /* pass-through */ p_out1, p_out2;
	nbMass = 3;
	nbFrcIn = 1;
	nbOut = 2;
};
process = in1 : model:*(OutGain), *(OutGain);

/*
========= MIMS SCRIPT USED FOR MODEL GENERATION =============

# MIMS script file
# Script author: James Leonard

# Integrated harmonic oscillator 
@o osc 1. 0.1 0.0003 0. 0.

# A slow moving oscillator placed above the other
# serving as a hammer
@ham mass 0.3 1. 0.
@g ground 1.
@sp springDamper @g @ham 0.0001 0.05

# Add force input to the hammer
@in1 frcInput @ham

@c contact @o @ham 0.1 0.001

# Add position output from the oscillator
@out1 posOutput @o
@out2 posOutput @ham

# end of MIMS script

*/