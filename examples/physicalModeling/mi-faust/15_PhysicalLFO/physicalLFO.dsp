declare name    "Physical LFO";
declare author  "James Leonard";
declare date    "April 2020";

/* ========= DESCRITPION =============

You can use physical models for other things than sythesizing "acoustical" sounds!
Here, we use a very floppy string as an LFO generator to modulate a white noise signal.
    - inputs: force impulse to excite the string.
    - outputs: position of one mass of the string (used to modulate the white noise)
    - controls: string stiffness and damping.

Note: when excited, the string first displays strong harmonic content, resulting in complex
modulation patterns that die down as damping tends to return to the fundamental frequency.
*/

import("stdfaust.lib");

gateT = button("Excite String"):ba.impulsify;
in1 = gateT * 0.1; 

OutGain = hslider("output gain", 0.01, 0, 0.02, 0.00001);

str_M = 1.0;
str_K = hslider("string stiffness", 0.000001, 0.0000001, 0.00001, 0.0000001);
str_Z = hslider("string damping", 0.0001, 0, 0.002, 0.00001);


model = (
	mi.ground(0.),
	mi.mass(str_M, 0, 0., 0.),
	mi.mass(str_M, 0, 0., 0.),
	mi.mass(str_M, 0, 0., 0.),
	mi.mass(str_M, 0, 0., 0.),
	mi.mass(str_M, 0, 0., 0.),
	mi.mass(str_M, 0, 0., 0.),
	mi.mass(str_M, 0, 0., 0.),
	mi.mass(str_M, 0, 0., 0.),
	mi.mass(str_M, 0, 0., 0.),
	mi.mass(str_M, 0, 0., 0.),
	mi.ground(0.),
	par(i, nbFrcIn,_):
	RoutingMassToLink ,
	par(i, nbFrcIn,_):
	mi.springDamper(str_K, str_Z, 0., 0.),
	mi.springDamper(str_K, str_Z, 0., 0.),
	mi.springDamper(str_K, str_Z, 0., 0.),
	mi.springDamper(str_K, str_Z, 0., 0.),
	mi.springDamper(str_K, str_Z, 0., 0.),
	mi.springDamper(str_K, str_Z, 0., 0.),
	mi.springDamper(str_K, str_Z, 0., 0.),
	mi.springDamper(str_K, str_Z, 0., 0.),
	mi.springDamper(str_K, str_Z, 0., 0.),
	mi.springDamper(str_K, str_Z, 0., 0.),
	mi.springDamper(str_K, str_Z, 0., 0.),
	par(i, nbOut+nbFrcIn, _):
	RoutingLinkToMass
)~par(i, nbMass, _):
par(i, nbMass, !), par(i, nbOut , _)
with{
	RoutingMassToLink(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11) = /* routed positions */ m0, m1, m1, m2, m2, m3, m3, m4, m4, m5, m5, m6, m6, m7, m7, m8, m8, m9, m9, m10, m10, m11, /* outputs */ m2;
	RoutingLinkToMass(l0_f1, l0_f2, l1_f1, l1_f2, l2_f1, l2_f2, l3_f1, l3_f2, l4_f1, l4_f2, l5_f1, l5_f2, l6_f1, l6_f2, l7_f1, l7_f2, l8_f1, l8_f2, l9_f1, l9_f2, l10_f1, l10_f2, p_out1, f_in1) = /* routed forces  */ l0_f1, f_in1 + l0_f2 + l1_f1, l1_f2 + l2_f1, l2_f2 + l3_f1, l3_f2 + l4_f1, l4_f2 + l5_f1, l5_f2 + l6_f1, l6_f2 + l7_f1, l7_f2 + l8_f1, l8_f2 + l9_f1, l9_f2 + l10_f1, l10_f2, /* pass-through */ p_out1;
	nbMass = 12;
	nbFrcIn = 1;
	nbOut = 1;
};
process = in1 : model:*(OutGain)*no.noise;


/*
========= MIMS SCRIPT USED FOR MODEL GENERATION =============

@str_M param 1.0
@str_K param 0.1
@str_Z param 0.001

@str_s0 ground 0.
@str_m0 mass str_M 0. 0.
@str_m1 mass str_M 0. 0.
@str_m2 mass str_M 0. 0.
@str_m3 mass str_M 0. 0.
@str_m4 mass str_M 0. 0.
@str_m5 mass str_M 0. 0.
@str_m6 mass str_M 0. 0.
@str_m7 mass str_M 0. 0.
@str_m8 mass str_M 0. 0.
@str_m9 mass str_M 0. 0.
@str_s1 ground 0.

@str_r0 springDamper @str_s0 @str_m0 str_K str_Z
@str_r1 springDamper @str_m0 @str_m1 str_K str_Z
@str_r2 springDamper @str_m1 @str_m2 str_K str_Z
@str_r3 springDamper @str_m2 @str_m3 str_K str_Z
@str_r4 springDamper @str_m3 @str_m4 str_K str_Z
@str_r5 springDamper @str_m4 @str_m5 str_K str_Z
@str_r6 springDamper @str_m5 @str_m6 str_K str_Z
@str_r7 springDamper @str_m6 @str_m7 str_K str_Z
@str_r8 springDamper @str_m7 @str_m8 str_K str_Z
@str_r9 springDamper @str_m8 @str_m9 str_K str_Z
@str_r10 springDamper @str_m9 @str_s1 str_K str_Z


@in1 frcInput @str_m0

@out1 posOutput @str_m1

*/