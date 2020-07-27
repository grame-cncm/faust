declare name    "Strange Physical Construction";
declare author  "James Leonard";
declare date    "April 2020";

/* ========= DESCRITPION =============

A triangle mesh (fixed corners) struck by a hammer, connected (through a slightly non-linear spring)
to a resonant square mesh (fixed corners).
    - inputs: Force impulse applied to the hammer
    - outputs: one listening point on the triangle, another on the resonnant mesh.
    - controls: triangle stiffness and daming, square mesh stiffness and damping, hammer force impulse scaling.

Note: the block diagram of the model will give you nightmares.
*/

import("stdfaust.lib");

in1 = button("Force Impulse"): ba.impulsify * hslider("Force Scaling", 0.5, 0.01, 0.9, 0.001) * -1;

OutGain = 1;

t_M = 1;
t_K = hslider("Triangle Stiffness", 0.1, 0.001, 0.2, 0.0001);
t_Z = hslider("Triangle Damping", 0.0001, 0.00, 0.0008, 0.000001);
t_Zo = 0.00005;
me_M = 1;
me_K = hslider("Mesh Stiffness", 0.1, 0.001, 0.2, 0.0001);
me_Z = hslider("Mesh Damping", 0.0001, 0.00, 0.0008, 0.000001);
me_Zo = 0.00005;

model = (
	mi.mass(0.3, 0, 1., 1.),
	mi.ground(1.),
	mi.ground(0),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.ground(0),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.oscil(t_M, 0, t_Zo, 0, 0., 0.),
	mi.ground(0),
	mi.ground(0),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.ground(0),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.ground(0),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.oscil(me_M, 0, me_Zo, 0, 0., 0.),
	mi.ground(0),
	par(i, nbFrcIn,_):
	RoutingMassToLink ,
	par(i, nbFrcIn,_):
	mi.springDamper(0.0001, 0.05, 1., 1.),
	mi.nlCollisionClipped(0.0, 0.01, 0.5, 0.001, 0, 0., 1.),
	mi.nlSpringDamperClipped(0.01, 0.01, 0.2, 0., 0., 0.),
	mi.springDamper(t_K, t_Z, 0, 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0, 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0, 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0.),
	mi.springDamper(t_K, t_Z, 0., 0),
	mi.springDamper(me_K, me_Z, 0, 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0, 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0),
	mi.springDamper(me_K, me_Z, 0, 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0, 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0.),
	mi.springDamper(me_K, me_Z, 0., 0),
	par(i, nbOut+nbFrcIn, _):
	RoutingLinkToMass
)~par(i, nbMass, _):
par(i, nbMass, !), par(i, nbOut , _)
with{
	RoutingMassToLink(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29, m30, m31, m32, m33, m34, m35, m36, m37, m38, m39, m40, m41, m42, m43, m44, m45, m46, m47, m48, m49, m50, m51, m52, m53, m54, m55, m56, m57, m58, m59, m60, m61, m62, m63, m64, m65, m66, m67, m68, m69, m70, m71, m72, m73, m74, m75, m76, m77, m78, m79, m80, m81, m82, m83, m84, m85, m86, m87, m88, m89, m90, m91, m92, m93, m94, m95, m96, m97, m98, m99, m100, m101, m102, m103, m104, m105, m106, m107, m108, m109, m110, m111, m112, m113, m114, m115, m116, m117, m118, m119, m120, m121, m122, m123, m124, m125, m126, m127, m128, m129, m130, m131, m132, m133, m134, m135, m136, m137, m138, m139, m140, m141, m142, m143, m144, m145, m146, m147, m148, m149, m150, m151, m152, m153, m154, m155, m156) = /* routed positions */ m1, m0, m39, m0, m49, m94, m2, m3, m3, m4, m4, m5, m5, m6, m6, m7, m7, m8, m8, m9, m9, m10, m10, m11, m12, m13, m13, m14, m14, m15, m15, m16, m16, m17, m17, m18, m18, m19, m19, m20, m21, m22, m22, m23, m23, m24, m24, m25, m25, m26, m26, m27, m27, m28, m29, m30, m30, m31, m31, m32, m32, m33, m33, m34, m34, m35, m36, m37, m37, m38, m38, m39, m39, m40, m40, m41, m42, m43, m43, m44, m44, m45, m45, m46, m47, m48, m48, m49, m49, m50, m51, m52, m52, m53, m54, m55, m2, m12, m3, m13, m4, m14, m5, m15, m6, m16, m7, m17, m8, m18, m9, m19, m10, m20, m12, m21, m13, m22, m14, m23, m15, m24, m16, m25, m17, m26, m18, m27, m19, m28, m21, m29, m22, m30, m23, m31, m24, m32, m25, m33, m26, m34, m27, m35, m29, m36, m30, m37, m31, m38, m32, m39, m33, m40, m34, m41, m36, m42, m37, m43, m38, m44, m39, m45, m40, m46, m42, m47, m43, m48, m44, m49, m45, m50, m47, m51, m48, m52, m49, m53, m51, m54, m52, m55, m54, m56, m3, m12, m4, m13, m5, m14, m6, m15, m7, m16, m8, m17, m9, m18, m10, m19, m11, m20, m13, m21, m14, m22, m15, m23, m16, m24, m17, m25, m18, m26, m19, m27, m20, m28, m22, m29, m23, m30, m24, m31, m25, m32, m26, m33, m27, m34, m28, m35, m30, m36, m31, m37, m32, m38, m33, m39, m34, m40, m35, m41, m37, m42, m38, m43, m39, m44, m40, m45, m41, m46, m43, m47, m44, m48, m45, m49, m46, m50, m48, m51, m49, m52, m50, m53, m52, m54, m53, m55, m55, m56, m57, m58, m58, m59, m59, m60, m60, m61, m61, m62, m62, m63, m63, m64, m64, m65, m65, m66, m67, m68, m68, m69, m69, m70, m70, m71, m71, m72, m72, m73, m73, m74, m74, m75, m75, m76, m77, m78, m78, m79, m79, m80, m80, m81, m81, m82, m82, m83, m83, m84, m84, m85, m85, m86, m87, m88, m88, m89, m89, m90, m90, m91, m91, m92, m92, m93, m93, m94, m94, m95, m95, m96, m97, m98, m98, m99, m99, m100, m100, m101, m101, m102, m102, m103, m103, m104, m104, m105, m105, m106, m107, m108, m108, m109, m109, m110, m110, m111, m111, m112, m112, m113, m113, m114, m114, m115, m115, m116, m117, m118, m118, m119, m119, m120, m120, m121, m121, m122, m122, m123, m123, m124, m124, m125, m125, m126, m127, m128, m128, m129, m129, m130, m130, m131, m131, m132, m132, m133, m133, m134, m134, m135, m135, m136, m137, m138, m138, m139, m139, m140, m140, m141, m141, m142, m142, m143, m143, m144, m144, m145, m145, m146, m147, m148, m148, m149, m149, m150, m150, m151, m151, m152, m152, m153, m153, m154, m154, m155, m155, m156, m57, m67, m58, m68, m59, m69, m60, m70, m61, m71, m62, m72, m63, m73, m64, m74, m65, m75, m66, m76, m67, m77, m68, m78, m69, m79, m70, m80, m71, m81, m72, m82, m73, m83, m74, m84, m75, m85, m76, m86, m77, m87, m78, m88, m79, m89, m80, m90, m81, m91, m82, m92, m83, m93, m84, m94, m85, m95, m86, m96, m87, m97, m88, m98, m89, m99, m90, m100, m91, m101, m92, m102, m93, m103, m94, m104, m95, m105, m96, m106, m97, m107, m98, m108, m99, m109, m100, m110, m101, m111, m102, m112, m103, m113, m104, m114, m105, m115, m106, m116, m107, m117, m108, m118, m109, m119, m110, m120, m111, m121, m112, m122, m113, m123, m114, m124, m115, m125, m116, m126, m117, m127, m118, m128, m119, m129, m120, m130, m121, m131, m122, m132, m123, m133, m124, m134, m125, m135, m126, m136, m127, m137, m128, m138, m129, m139, m130, m140, m131, m141, m132, m142, m133, m143, m134, m144, m135, m145, m136, m146, m137, m147, m138, m148, m139, m149, m140, m150, m141, m151, m142, m152, m143, m153, m144, m154, m145, m155, m146, m156, /* outputs */ m112, m22;
	RoutingLinkToMass(l0_f1, l0_f2, l1_f1, l1_f2, l2_f1, l2_f2, l3_f1, l3_f2, l4_f1, l4_f2, l5_f1, l5_f2, l6_f1, l6_f2, l7_f1, l7_f2, l8_f1, l8_f2, l9_f1, l9_f2, l10_f1, l10_f2, l11_f1, l11_f2, l12_f1, l12_f2, l13_f1, l13_f2, l14_f1, l14_f2, l15_f1, l15_f2, l16_f1, l16_f2, l17_f1, l17_f2, l18_f1, l18_f2, l19_f1, l19_f2, l20_f1, l20_f2, l21_f1, l21_f2, l22_f1, l22_f2, l23_f1, l23_f2, l24_f1, l24_f2, l25_f1, l25_f2, l26_f1, l26_f2, l27_f1, l27_f2, l28_f1, l28_f2, l29_f1, l29_f2, l30_f1, l30_f2, l31_f1, l31_f2, l32_f1, l32_f2, l33_f1, l33_f2, l34_f1, l34_f2, l35_f1, l35_f2, l36_f1, l36_f2, l37_f1, l37_f2, l38_f1, l38_f2, l39_f1, l39_f2, l40_f1, l40_f2, l41_f1, l41_f2, l42_f1, l42_f2, l43_f1, l43_f2, l44_f1, l44_f2, l45_f1, l45_f2, l46_f1, l46_f2, l47_f1, l47_f2, l48_f1, l48_f2, l49_f1, l49_f2, l50_f1, l50_f2, l51_f1, l51_f2, l52_f1, l52_f2, l53_f1, l53_f2, l54_f1, l54_f2, l55_f1, l55_f2, l56_f1, l56_f2, l57_f1, l57_f2, l58_f1, l58_f2, l59_f1, l59_f2, l60_f1, l60_f2, l61_f1, l61_f2, l62_f1, l62_f2, l63_f1, l63_f2, l64_f1, l64_f2, l65_f1, l65_f2, l66_f1, l66_f2, l67_f1, l67_f2, l68_f1, l68_f2, l69_f1, l69_f2, l70_f1, l70_f2, l71_f1, l71_f2, l72_f1, l72_f2, l73_f1, l73_f2, l74_f1, l74_f2, l75_f1, l75_f2, l76_f1, l76_f2, l77_f1, l77_f2, l78_f1, l78_f2, l79_f1, l79_f2, l80_f1, l80_f2, l81_f1, l81_f2, l82_f1, l82_f2, l83_f1, l83_f2, l84_f1, l84_f2, l85_f1, l85_f2, l86_f1, l86_f2, l87_f1, l87_f2, l88_f1, l88_f2, l89_f1, l89_f2, l90_f1, l90_f2, l91_f1, l91_f2, l92_f1, l92_f2, l93_f1, l93_f2, l94_f1, l94_f2, l95_f1, l95_f2, l96_f1, l96_f2, l97_f1, l97_f2, l98_f1, l98_f2, l99_f1, l99_f2, l100_f1, l100_f2, l101_f1, l101_f2, l102_f1, l102_f2, l103_f1, l103_f2, l104_f1, l104_f2, l105_f1, l105_f2, l106_f1, l106_f2, l107_f1, l107_f2, l108_f1, l108_f2, l109_f1, l109_f2, l110_f1, l110_f2, l111_f1, l111_f2, l112_f1, l112_f2, l113_f1, l113_f2, l114_f1, l114_f2, l115_f1, l115_f2, l116_f1, l116_f2, l117_f1, l117_f2, l118_f1, l118_f2, l119_f1, l119_f2, l120_f1, l120_f2, l121_f1, l121_f2, l122_f1, l122_f2, l123_f1, l123_f2, l124_f1, l124_f2, l125_f1, l125_f2, l126_f1, l126_f2, l127_f1, l127_f2, l128_f1, l128_f2, l129_f1, l129_f2, l130_f1, l130_f2, l131_f1, l131_f2, l132_f1, l132_f2, l133_f1, l133_f2, l134_f1, l134_f2, l135_f1, l135_f2, l136_f1, l136_f2, l137_f1, l137_f2, l138_f1, l138_f2, l139_f1, l139_f2, l140_f1, l140_f2, l141_f1, l141_f2, l142_f1, l142_f2, l143_f1, l143_f2, l144_f1, l144_f2, l145_f1, l145_f2, l146_f1, l146_f2, l147_f1, l147_f2, l148_f1, l148_f2, l149_f1, l149_f2, l150_f1, l150_f2, l151_f1, l151_f2, l152_f1, l152_f2, l153_f1, l153_f2, l154_f1, l154_f2, l155_f1, l155_f2, l156_f1, l156_f2, l157_f1, l157_f2, l158_f1, l158_f2, l159_f1, l159_f2, l160_f1, l160_f2, l161_f1, l161_f2, l162_f1, l162_f2, l163_f1, l163_f2, l164_f1, l164_f2, l165_f1, l165_f2, l166_f1, l166_f2, l167_f1, l167_f2, l168_f1, l168_f2, l169_f1, l169_f2, l170_f1, l170_f2, l171_f1, l171_f2, l172_f1, l172_f2, l173_f1, l173_f2, l174_f1, l174_f2, l175_f1, l175_f2, l176_f1, l176_f2, l177_f1, l177_f2, l178_f1, l178_f2, l179_f1, l179_f2, l180_f1, l180_f2, l181_f1, l181_f2, l182_f1, l182_f2, l183_f1, l183_f2, l184_f1, l184_f2, l185_f1, l185_f2, l186_f1, l186_f2, l187_f1, l187_f2, l188_f1, l188_f2, l189_f1, l189_f2, l190_f1, l190_f2, l191_f1, l191_f2, l192_f1, l192_f2, l193_f1, l193_f2, l194_f1, l194_f2, l195_f1, l195_f2, l196_f1, l196_f2, l197_f1, l197_f2, l198_f1, l198_f2, l199_f1, l199_f2, l200_f1, l200_f2, l201_f1, l201_f2, l202_f1, l202_f2, l203_f1, l203_f2, l204_f1, l204_f2, l205_f1, l205_f2, l206_f1, l206_f2, l207_f1, l207_f2, l208_f1, l208_f2, l209_f1, l209_f2, l210_f1, l210_f2, l211_f1, l211_f2, l212_f1, l212_f2, l213_f1, l213_f2, l214_f1, l214_f2, l215_f1, l215_f2, l216_f1, l216_f2, l217_f1, l217_f2, l218_f1, l218_f2, l219_f1, l219_f2, l220_f1, l220_f2, l221_f1, l221_f2, l222_f1, l222_f2, l223_f1, l223_f2, l224_f1, l224_f2, l225_f1, l225_f2, l226_f1, l226_f2, l227_f1, l227_f2, l228_f1, l228_f2, l229_f1, l229_f2, l230_f1, l230_f2, l231_f1, l231_f2, l232_f1, l232_f2, l233_f1, l233_f2, l234_f1, l234_f2, l235_f1, l235_f2, l236_f1, l236_f2, l237_f1, l237_f2, l238_f1, l238_f2, l239_f1, l239_f2, l240_f1, l240_f2, l241_f1, l241_f2, l242_f1, l242_f2, l243_f1, l243_f2, l244_f1, l244_f2, l245_f1, l245_f2, l246_f1, l246_f2, l247_f1, l247_f2, l248_f1, l248_f2, l249_f1, l249_f2, l250_f1, l250_f2, l251_f1, l251_f2, l252_f1, l252_f2, l253_f1, l253_f2, l254_f1, l254_f2, l255_f1, l255_f2, l256_f1, l256_f2, l257_f1, l257_f2, l258_f1, l258_f2, l259_f1, l259_f2, l260_f1, l260_f2, l261_f1, l261_f2, l262_f1, l262_f2, l263_f1, l263_f2, l264_f1, l264_f2, l265_f1, l265_f2, l266_f1, l266_f2, l267_f1, l267_f2, l268_f1, l268_f2, l269_f1, l269_f2, l270_f1, l270_f2, l271_f1, l271_f2, l272_f1, l272_f2, l273_f1, l273_f2, l274_f1, l274_f2, l275_f1, l275_f2, l276_f1, l276_f2, l277_f1, l277_f2, l278_f1, l278_f2, l279_f1, l279_f2, l280_f1, l280_f2, l281_f1, l281_f2, l282_f1, l282_f2, l283_f1, l283_f2, l284_f1, l284_f2, l285_f1, l285_f2, l286_f1, l286_f2, l287_f1, l287_f2, l288_f1, l288_f2, l289_f1, l289_f2, l290_f1, l290_f2, l291_f1, l291_f2, l292_f1, l292_f2, l293_f1, l293_f2, l294_f1, l294_f2, l295_f1, l295_f2, l296_f1, l296_f2, l297_f1, l297_f2, l298_f1, l298_f2, l299_f1, l299_f2, l300_f1, l300_f2, l301_f1, l301_f2, l302_f1, l302_f2, l303_f1, l303_f2, l304_f1, l304_f2, l305_f1, l305_f2, l306_f1, l306_f2, l307_f1, l307_f2, l308_f1, l308_f2, l309_f1, l309_f2, l310_f1, l310_f2, l311_f1, l311_f2, l312_f1, l312_f2, l313_f1, l313_f2, l314_f1, l314_f2, l315_f1, l315_f2, l316_f1, l316_f2, l317_f1, l317_f2, p_out1, p_out2, f_in1) = /* routed forces  */ f_in1 + l0_f2 + l1_f2, l0_f1, l3_f1 + l48_f1, l3_f2 + l4_f1 + l49_f1 + l93_f1, l4_f2 + l5_f1 + l50_f1 + l94_f1, l5_f2 + l6_f1 + l51_f1 + l95_f1, l6_f2 + l7_f1 + l52_f1 + l96_f1, l7_f2 + l8_f1 + l53_f1 + l97_f1, l8_f2 + l9_f1 + l54_f1 + l98_f1, l9_f2 + l10_f1 + l55_f1 + l99_f1, l10_f2 + l11_f1 + l56_f1 + l100_f1, l11_f2 + l101_f1, l12_f1 + l48_f2 + l57_f1 + l93_f2, l12_f2 + l13_f1 + l49_f2 + l58_f1 + l94_f2 + l102_f1, l13_f2 + l14_f1 + l50_f2 + l59_f1 + l95_f2 + l103_f1, l14_f2 + l15_f1 + l51_f2 + l60_f1 + l96_f2 + l104_f1, l15_f2 + l16_f1 + l52_f2 + l61_f1 + l97_f2 + l105_f1, l16_f2 + l17_f1 + l53_f2 + l62_f1 + l98_f2 + l106_f1, l17_f2 + l18_f1 + l54_f2 + l63_f1 + l99_f2 + l107_f1, l18_f2 + l19_f1 + l55_f2 + l64_f1 + l100_f2 + l108_f1, l19_f2 + l56_f2 + l101_f2 + l109_f1, l20_f1 + l57_f2 + l65_f1 + l102_f2, l20_f2 + l21_f1 + l58_f2 + l66_f1 + l103_f2 + l110_f1, l21_f2 + l22_f1 + l59_f2 + l67_f1 + l104_f2 + l111_f1, l22_f2 + l23_f1 + l60_f2 + l68_f1 + l105_f2 + l112_f1, l23_f2 + l24_f1 + l61_f2 + l69_f1 + l106_f2 + l113_f1, l24_f2 + l25_f1 + l62_f2 + l70_f1 + l107_f2 + l114_f1, l25_f2 + l26_f1 + l63_f2 + l71_f1 + l108_f2 + l115_f1, l26_f2 + l64_f2 + l109_f2 + l116_f1, l27_f1 + l65_f2 + l72_f1 + l110_f2, l27_f2 + l28_f1 + l66_f2 + l73_f1 + l111_f2 + l117_f1, l28_f2 + l29_f1 + l67_f2 + l74_f1 + l112_f2 + l118_f1, l29_f2 + l30_f1 + l68_f2 + l75_f1 + l113_f2 + l119_f1, l30_f2 + l31_f1 + l69_f2 + l76_f1 + l114_f2 + l120_f1, l31_f2 + l32_f1 + l70_f2 + l77_f1 + l115_f2 + l121_f1, l32_f2 + l71_f2 + l116_f2 + l122_f1, l33_f1 + l72_f2 + l78_f1 + l117_f2, l33_f2 + l34_f1 + l73_f2 + l79_f1 + l118_f2 + l123_f1, l34_f2 + l35_f1 + l74_f2 + l80_f1 + l119_f2 + l124_f1, l1_f1 + l35_f2 + l36_f1 + l75_f2 + l81_f1 + l120_f2 + l125_f1, l36_f2 + l37_f1 + l76_f2 + l82_f1 + l121_f2 + l126_f1, l37_f2 + l77_f2 + l122_f2 + l127_f1, l38_f1 + l78_f2 + l83_f1 + l123_f2, l38_f2 + l39_f1 + l79_f2 + l84_f1 + l124_f2 + l128_f1, l39_f2 + l40_f1 + l80_f2 + l85_f1 + l125_f2 + l129_f1, l40_f2 + l41_f1 + l81_f2 + l86_f1 + l126_f2 + l130_f1, l41_f2 + l82_f2 + l127_f2 + l131_f1, l42_f1 + l83_f2 + l87_f1 + l128_f2, l42_f2 + l43_f1 + l84_f2 + l88_f1 + l129_f2 + l132_f1, l2_f1 + l43_f2 + l44_f1 + l85_f2 + l89_f1 + l130_f2 + l133_f1, l44_f2 + l86_f2 + l131_f2 + l134_f1, l45_f1 + l87_f2 + l90_f1 + l132_f2, l45_f2 + l46_f1 + l88_f2 + l91_f1 + l133_f2 + l135_f1, l46_f2 + l89_f2 + l134_f2 + l136_f1, l47_f1 + l90_f2 + l92_f1 + l135_f2, l47_f2 + l91_f2 + l136_f2 + l137_f1, l92_f2 + l137_f2, l138_f1 + l228_f1, l138_f2 + l139_f1 + l229_f1, l139_f2 + l140_f1 + l230_f1, l140_f2 + l141_f1 + l231_f1, l141_f2 + l142_f1 + l232_f1, l142_f2 + l143_f1 + l233_f1, l143_f2 + l144_f1 + l234_f1, l144_f2 + l145_f1 + l235_f1, l145_f2 + l146_f1 + l236_f1, l146_f2 + l237_f1, l147_f1 + l228_f2 + l238_f1, l147_f2 + l148_f1 + l229_f2 + l239_f1, l148_f2 + l149_f1 + l230_f2 + l240_f1, l149_f2 + l150_f1 + l231_f2 + l241_f1, l150_f2 + l151_f1 + l232_f2 + l242_f1, l151_f2 + l152_f1 + l233_f2 + l243_f1, l152_f2 + l153_f1 + l234_f2 + l244_f1, l153_f2 + l154_f1 + l235_f2 + l245_f1, l154_f2 + l155_f1 + l236_f2 + l246_f1, l155_f2 + l237_f2 + l247_f1, l156_f1 + l238_f2 + l248_f1, l156_f2 + l157_f1 + l239_f2 + l249_f1, l157_f2 + l158_f1 + l240_f2 + l250_f1, l158_f2 + l159_f1 + l241_f2 + l251_f1, l159_f2 + l160_f1 + l242_f2 + l252_f1, l160_f2 + l161_f1 + l243_f2 + l253_f1, l161_f2 + l162_f1 + l244_f2 + l254_f1, l162_f2 + l163_f1 + l245_f2 + l255_f1, l163_f2 + l164_f1 + l246_f2 + l256_f1, l164_f2 + l247_f2 + l257_f1, l165_f1 + l248_f2 + l258_f1, l165_f2 + l166_f1 + l249_f2 + l259_f1, l166_f2 + l167_f1 + l250_f2 + l260_f1, l167_f2 + l168_f1 + l251_f2 + l261_f1, l168_f2 + l169_f1 + l252_f2 + l262_f1, l169_f2 + l170_f1 + l253_f2 + l263_f1, l170_f2 + l171_f1 + l254_f2 + l264_f1, l2_f2 + l171_f2 + l172_f1 + l255_f2 + l265_f1, l172_f2 + l173_f1 + l256_f2 + l266_f1, l173_f2 + l257_f2 + l267_f1, l174_f1 + l258_f2 + l268_f1, l174_f2 + l175_f1 + l259_f2 + l269_f1, l175_f2 + l176_f1 + l260_f2 + l270_f1, l176_f2 + l177_f1 + l261_f2 + l271_f1, l177_f2 + l178_f1 + l262_f2 + l272_f1, l178_f2 + l179_f1 + l263_f2 + l273_f1, l179_f2 + l180_f1 + l264_f2 + l274_f1, l180_f2 + l181_f1 + l265_f2 + l275_f1, l181_f2 + l182_f1 + l266_f2 + l276_f1, l182_f2 + l267_f2 + l277_f1, l183_f1 + l268_f2 + l278_f1, l183_f2 + l184_f1 + l269_f2 + l279_f1, l184_f2 + l185_f1 + l270_f2 + l280_f1, l185_f2 + l186_f1 + l271_f2 + l281_f1, l186_f2 + l187_f1 + l272_f2 + l282_f1, l187_f2 + l188_f1 + l273_f2 + l283_f1, l188_f2 + l189_f1 + l274_f2 + l284_f1, l189_f2 + l190_f1 + l275_f2 + l285_f1, l190_f2 + l191_f1 + l276_f2 + l286_f1, l191_f2 + l277_f2 + l287_f1, l192_f1 + l278_f2 + l288_f1, l192_f2 + l193_f1 + l279_f2 + l289_f1, l193_f2 + l194_f1 + l280_f2 + l290_f1, l194_f2 + l195_f1 + l281_f2 + l291_f1, l195_f2 + l196_f1 + l282_f2 + l292_f1, l196_f2 + l197_f1 + l283_f2 + l293_f1, l197_f2 + l198_f1 + l284_f2 + l294_f1, l198_f2 + l199_f1 + l285_f2 + l295_f1, l199_f2 + l200_f1 + l286_f2 + l296_f1, l200_f2 + l287_f2 + l297_f1, l201_f1 + l288_f2 + l298_f1, l201_f2 + l202_f1 + l289_f2 + l299_f1, l202_f2 + l203_f1 + l290_f2 + l300_f1, l203_f2 + l204_f1 + l291_f2 + l301_f1, l204_f2 + l205_f1 + l292_f2 + l302_f1, l205_f2 + l206_f1 + l293_f2 + l303_f1, l206_f2 + l207_f1 + l294_f2 + l304_f1, l207_f2 + l208_f1 + l295_f2 + l305_f1, l208_f2 + l209_f1 + l296_f2 + l306_f1, l209_f2 + l297_f2 + l307_f1, l210_f1 + l298_f2 + l308_f1, l210_f2 + l211_f1 + l299_f2 + l309_f1, l211_f2 + l212_f1 + l300_f2 + l310_f1, l212_f2 + l213_f1 + l301_f2 + l311_f1, l213_f2 + l214_f1 + l302_f2 + l312_f1, l214_f2 + l215_f1 + l303_f2 + l313_f1, l215_f2 + l216_f1 + l304_f2 + l314_f1, l216_f2 + l217_f1 + l305_f2 + l315_f1, l217_f2 + l218_f1 + l306_f2 + l316_f1, l218_f2 + l307_f2 + l317_f1, l219_f1 + l308_f2, l219_f2 + l220_f1 + l309_f2, l220_f2 + l221_f1 + l310_f2, l221_f2 + l222_f1 + l311_f2, l222_f2 + l223_f1 + l312_f2, l223_f2 + l224_f1 + l313_f2, l224_f2 + l225_f1 + l314_f2, l225_f2 + l226_f1 + l315_f2, l226_f2 + l227_f1 + l316_f2, l227_f2 + l317_f2, /* pass-through */ p_out1, p_out2;
	nbMass = 157;
	nbFrcIn = 1;
	nbOut = 2;
};
process = in1 : model:*(OutGain), *(OutGain);


/*
========= MIMS SCRIPT USED FOR MODEL GENERATION =============


# A plucked triangular mesh model (fixed at corners)
# Script author: James Leonard

# A slow moving oscillator placed above the other
# serving as a hammer
@ham mass 0.3 1. 0.
@g ground 1.
@sp springDamper @g @ham 0.0001 0.05

# Add force input to the hammer
@in1 frcInput @ham

@c nlContact @t_m4_3 @ham 0. 0.01 0.5 0.001

@nls nlSpringDamper @t_m6_2 @me_m3_7 0.01 0.01 0.2 0.

@t_M param 1
@t_K param 0.1
@t_Z param 0.001
@t_Zo param 0.00005

@t_m0_0 ground 0 
@t_m0_1 osc t_M 0 t_Zo 0. 0. 
@t_m0_2 osc t_M 0 t_Zo 0. 0. 
@t_m0_3 osc t_M 0 t_Zo 0. 0. 
@t_m0_4 osc t_M 0 t_Zo 0. 0. 
@t_m0_5 osc t_M 0 t_Zo 0. 0. 
@t_m0_6 osc t_M 0 t_Zo 0. 0. 
@t_m0_7 osc t_M 0 t_Zo 0. 0. 
@t_m0_8 osc t_M 0 t_Zo 0. 0. 
@t_m0_9 ground 0
@t_m1_0 osc t_M 0 t_Zo 0. 0. 
@t_m1_1 osc t_M 0 t_Zo 0. 0. 
@t_m1_2 osc t_M 0 t_Zo 0. 0. 
@t_m1_3 osc t_M 0 t_Zo 0. 0. 
@t_m1_4 osc t_M 0 t_Zo 0. 0. 
@t_m1_5 osc t_M 0 t_Zo 0. 0. 
@t_m1_6 osc t_M 0 t_Zo 0. 0. 
@t_m1_7 osc t_M 0 t_Zo 0. 0. 
@t_m1_8 osc t_M 0 t_Zo 0. 0. 
@t_m2_0 osc t_M 0 t_Zo 0. 0. 
@t_m2_1 osc t_M 0 t_Zo 0. 0. 
@t_m2_2 osc t_M 0 t_Zo 0. 0. 
@t_m2_3 osc t_M 0 t_Zo 0. 0. 
@t_m2_4 osc t_M 0 t_Zo 0. 0. 
@t_m2_5 osc t_M 0 t_Zo 0. 0. 
@t_m2_6 osc t_M 0 t_Zo 0. 0. 
@t_m2_7 osc t_M 0 t_Zo 0. 0. 
@t_m3_0 osc t_M 0 t_Zo 0. 0. 
@t_m3_1 osc t_M 0 t_Zo 0. 0. 
@t_m3_2 osc t_M 0 t_Zo 0. 0. 
@t_m3_3 osc t_M 0 t_Zo 0. 0. 
@t_m3_4 osc t_M 0 t_Zo 0. 0. 
@t_m3_5 osc t_M 0 t_Zo 0. 0. 
@t_m3_6 osc t_M 0 t_Zo 0. 0. 
@t_m4_0 osc t_M 0 t_Zo 0. 0. 
@t_m4_1 osc t_M 0 t_Zo 0. 0. 
@t_m4_2 osc t_M 0 t_Zo 0. 0. 
@t_m4_3 osc t_M 0 t_Zo 0. 0. 
@t_m4_4 osc t_M 0 t_Zo 0. 0. 
@t_m4_5 osc t_M 0 t_Zo 0. 0. 
@t_m5_0 osc t_M 0 t_Zo 0. 0. 
@t_m5_1 osc t_M 0 t_Zo 0. 0. 
@t_m5_2 osc t_M 0 t_Zo 0. 0. 
@t_m5_3 osc t_M 0 t_Zo 0. 0. 
@t_m5_4 osc t_M 0 t_Zo 0. 0. 
@t_m6_0 osc t_M 0 t_Zo 0. 0. 
@t_m6_1 osc t_M 0 t_Zo 0. 0. 
@t_m6_2 osc t_M 0 t_Zo 0. 0. 
@t_m6_3 osc t_M 0 t_Zo 0. 0. 
@t_m7_0 osc t_M 0 t_Zo 0. 0. 
@t_m7_1 osc t_M 0 t_Zo 0. 0. 
@t_m7_2 osc t_M 0 t_Zo 0. 0. 
@t_m8_0 osc t_M 0 t_Zo 0. 0. 
@t_m8_1 osc t_M 0 t_Zo 0. 0. 
@t_m9_0 ground 0

@t_r0 springDamper @t_m0_0 @t_m0_1 t_K t_Z
@t_r1 springDamper @t_m0_1 @t_m0_2 t_K t_Z
@t_r2 springDamper @t_m0_2 @t_m0_3 t_K t_Z
@t_r3 springDamper @t_m0_3 @t_m0_4 t_K t_Z
@t_r4 springDamper @t_m0_4 @t_m0_5 t_K t_Z
@t_r5 springDamper @t_m0_5 @t_m0_6 t_K t_Z
@t_r6 springDamper @t_m0_6 @t_m0_7 t_K t_Z
@t_r7 springDamper @t_m0_7 @t_m0_8 t_K t_Z
@t_r8 springDamper @t_m0_8 @t_m0_9 t_K t_Z
@t_r9 springDamper @t_m1_0 @t_m1_1 t_K t_Z
@t_r10 springDamper @t_m1_1 @t_m1_2 t_K t_Z
@t_r11 springDamper @t_m1_2 @t_m1_3 t_K t_Z
@t_r12 springDamper @t_m1_3 @t_m1_4 t_K t_Z
@t_r13 springDamper @t_m1_4 @t_m1_5 t_K t_Z
@t_r14 springDamper @t_m1_5 @t_m1_6 t_K t_Z
@t_r15 springDamper @t_m1_6 @t_m1_7 t_K t_Z
@t_r16 springDamper @t_m1_7 @t_m1_8 t_K t_Z
@t_r17 springDamper @t_m2_0 @t_m2_1 t_K t_Z
@t_r18 springDamper @t_m2_1 @t_m2_2 t_K t_Z
@t_r19 springDamper @t_m2_2 @t_m2_3 t_K t_Z
@t_r20 springDamper @t_m2_3 @t_m2_4 t_K t_Z
@t_r21 springDamper @t_m2_4 @t_m2_5 t_K t_Z
@t_r22 springDamper @t_m2_5 @t_m2_6 t_K t_Z
@t_r23 springDamper @t_m2_6 @t_m2_7 t_K t_Z
@t_r24 springDamper @t_m3_0 @t_m3_1 t_K t_Z
@t_r25 springDamper @t_m3_1 @t_m3_2 t_K t_Z
@t_r26 springDamper @t_m3_2 @t_m3_3 t_K t_Z
@t_r27 springDamper @t_m3_3 @t_m3_4 t_K t_Z
@t_r28 springDamper @t_m3_4 @t_m3_5 t_K t_Z
@t_r29 springDamper @t_m3_5 @t_m3_6 t_K t_Z
@t_r30 springDamper @t_m4_0 @t_m4_1 t_K t_Z
@t_r31 springDamper @t_m4_1 @t_m4_2 t_K t_Z
@t_r32 springDamper @t_m4_2 @t_m4_3 t_K t_Z
@t_r33 springDamper @t_m4_3 @t_m4_4 t_K t_Z
@t_r34 springDamper @t_m4_4 @t_m4_5 t_K t_Z
@t_r35 springDamper @t_m5_0 @t_m5_1 t_K t_Z
@t_r36 springDamper @t_m5_1 @t_m5_2 t_K t_Z
@t_r37 springDamper @t_m5_2 @t_m5_3 t_K t_Z
@t_r38 springDamper @t_m5_3 @t_m5_4 t_K t_Z
@t_r39 springDamper @t_m6_0 @t_m6_1 t_K t_Z
@t_r40 springDamper @t_m6_1 @t_m6_2 t_K t_Z
@t_r41 springDamper @t_m6_2 @t_m6_3 t_K t_Z
@t_r42 springDamper @t_m7_0 @t_m7_1 t_K t_Z
@t_r43 springDamper @t_m7_1 @t_m7_2 t_K t_Z
@t_r44 springDamper @t_m8_0 @t_m8_1 t_K t_Z

@t_r45 springDamper @t_m0_0 @t_m1_0 t_K t_Z
@t_r46 springDamper @t_m0_1 @t_m1_1 t_K t_Z
@t_r47 springDamper @t_m0_2 @t_m1_2 t_K t_Z
@t_r48 springDamper @t_m0_3 @t_m1_3 t_K t_Z
@t_r49 springDamper @t_m0_4 @t_m1_4 t_K t_Z
@t_r50 springDamper @t_m0_5 @t_m1_5 t_K t_Z
@t_r51 springDamper @t_m0_6 @t_m1_6 t_K t_Z
@t_r52 springDamper @t_m0_7 @t_m1_7 t_K t_Z
@t_r53 springDamper @t_m0_8 @t_m1_8 t_K t_Z
@t_r54 springDamper @t_m1_0 @t_m2_0 t_K t_Z
@t_r55 springDamper @t_m1_1 @t_m2_1 t_K t_Z
@t_r56 springDamper @t_m1_2 @t_m2_2 t_K t_Z
@t_r57 springDamper @t_m1_3 @t_m2_3 t_K t_Z
@t_r58 springDamper @t_m1_4 @t_m2_4 t_K t_Z
@t_r59 springDamper @t_m1_5 @t_m2_5 t_K t_Z
@t_r60 springDamper @t_m1_6 @t_m2_6 t_K t_Z
@t_r61 springDamper @t_m1_7 @t_m2_7 t_K t_Z
@t_r62 springDamper @t_m2_0 @t_m3_0 t_K t_Z
@t_r63 springDamper @t_m2_1 @t_m3_1 t_K t_Z
@t_r64 springDamper @t_m2_2 @t_m3_2 t_K t_Z
@t_r65 springDamper @t_m2_3 @t_m3_3 t_K t_Z
@t_r66 springDamper @t_m2_4 @t_m3_4 t_K t_Z
@t_r67 springDamper @t_m2_5 @t_m3_5 t_K t_Z
@t_r68 springDamper @t_m2_6 @t_m3_6 t_K t_Z
@t_r69 springDamper @t_m3_0 @t_m4_0 t_K t_Z
@t_r70 springDamper @t_m3_1 @t_m4_1 t_K t_Z
@t_r71 springDamper @t_m3_2 @t_m4_2 t_K t_Z
@t_r72 springDamper @t_m3_3 @t_m4_3 t_K t_Z
@t_r73 springDamper @t_m3_4 @t_m4_4 t_K t_Z
@t_r74 springDamper @t_m3_5 @t_m4_5 t_K t_Z
@t_r75 springDamper @t_m4_0 @t_m5_0 t_K t_Z
@t_r76 springDamper @t_m4_1 @t_m5_1 t_K t_Z
@t_r77 springDamper @t_m4_2 @t_m5_2 t_K t_Z
@t_r78 springDamper @t_m4_3 @t_m5_3 t_K t_Z
@t_r79 springDamper @t_m4_4 @t_m5_4 t_K t_Z
@t_r80 springDamper @t_m5_0 @t_m6_0 t_K t_Z
@t_r81 springDamper @t_m5_1 @t_m6_1 t_K t_Z
@t_r82 springDamper @t_m5_2 @t_m6_2 t_K t_Z
@t_r83 springDamper @t_m5_3 @t_m6_3 t_K t_Z
@t_r84 springDamper @t_m6_0 @t_m7_0 t_K t_Z
@t_r85 springDamper @t_m6_1 @t_m7_1 t_K t_Z
@t_r86 springDamper @t_m6_2 @t_m7_2 t_K t_Z
@t_r87 springDamper @t_m7_0 @t_m8_0 t_K t_Z
@t_r88 springDamper @t_m7_1 @t_m8_1 t_K t_Z
@t_r89 springDamper @t_m8_0 @t_m9_0 t_K t_Z

@t_r90 springDamper @t_m0_1 @t_m1_0 t_K t_Z
@t_r91 springDamper @t_m0_2 @t_m1_1 t_K t_Z
@t_r92 springDamper @t_m0_3 @t_m1_2 t_K t_Z
@t_r93 springDamper @t_m0_4 @t_m1_3 t_K t_Z
@t_r94 springDamper @t_m0_5 @t_m1_4 t_K t_Z
@t_r95 springDamper @t_m0_6 @t_m1_5 t_K t_Z
@t_r96 springDamper @t_m0_7 @t_m1_6 t_K t_Z
@t_r97 springDamper @t_m0_8 @t_m1_7 t_K t_Z
@t_r98 springDamper @t_m0_9 @t_m1_8 t_K t_Z
@t_r99 springDamper @t_m1_1 @t_m2_0 t_K t_Z
@t_r100 springDamper @t_m1_2 @t_m2_1 t_K t_Z
@t_r101 springDamper @t_m1_3 @t_m2_2 t_K t_Z
@t_r102 springDamper @t_m1_4 @t_m2_3 t_K t_Z
@t_r103 springDamper @t_m1_5 @t_m2_4 t_K t_Z
@t_r104 springDamper @t_m1_6 @t_m2_5 t_K t_Z
@t_r105 springDamper @t_m1_7 @t_m2_6 t_K t_Z
@t_r106 springDamper @t_m1_8 @t_m2_7 t_K t_Z
@t_r107 springDamper @t_m2_1 @t_m3_0 t_K t_Z
@t_r108 springDamper @t_m2_2 @t_m3_1 t_K t_Z
@t_r109 springDamper @t_m2_3 @t_m3_2 t_K t_Z
@t_r110 springDamper @t_m2_4 @t_m3_3 t_K t_Z
@t_r111 springDamper @t_m2_5 @t_m3_4 t_K t_Z
@t_r112 springDamper @t_m2_6 @t_m3_5 t_K t_Z
@t_r113 springDamper @t_m2_7 @t_m3_6 t_K t_Z
@t_r114 springDamper @t_m3_1 @t_m4_0 t_K t_Z
@t_r115 springDamper @t_m3_2 @t_m4_1 t_K t_Z
@t_r116 springDamper @t_m3_3 @t_m4_2 t_K t_Z
@t_r117 springDamper @t_m3_4 @t_m4_3 t_K t_Z
@t_r118 springDamper @t_m3_5 @t_m4_4 t_K t_Z
@t_r119 springDamper @t_m3_6 @t_m4_5 t_K t_Z
@t_r120 springDamper @t_m4_1 @t_m5_0 t_K t_Z
@t_r121 springDamper @t_m4_2 @t_m5_1 t_K t_Z
@t_r122 springDamper @t_m4_3 @t_m5_2 t_K t_Z
@t_r123 springDamper @t_m4_4 @t_m5_3 t_K t_Z
@t_r124 springDamper @t_m4_5 @t_m5_4 t_K t_Z
@t_r125 springDamper @t_m5_1 @t_m6_0 t_K t_Z
@t_r126 springDamper @t_m5_2 @t_m6_1 t_K t_Z
@t_r127 springDamper @t_m5_3 @t_m6_2 t_K t_Z
@t_r128 springDamper @t_m5_4 @t_m6_3 t_K t_Z
@t_r129 springDamper @t_m6_1 @t_m7_0 t_K t_Z
@t_r130 springDamper @t_m6_2 @t_m7_1 t_K t_Z
@t_r131 springDamper @t_m6_3 @t_m7_2 t_K t_Z
@t_r132 springDamper @t_m7_1 @t_m8_0 t_K t_Z
@t_r133 springDamper @t_m7_2 @t_m8_1 t_K t_Z
@t_r134 springDamper @t_m8_1 @t_m9_0 t_K t_Z



@me_M param 1
@me_K param 0.1
@me_Z param 0.001
@me_Zo param 0.00005

@me_m0_0 ground 0
@me_m0_1 osc me_M 0 me_Zo 0. 0. 
@me_m0_2 osc me_M 0 me_Zo 0. 0. 
@me_m0_3 osc me_M 0 me_Zo 0. 0. 
@me_m0_4 osc me_M 0 me_Zo 0. 0. 
@me_m0_5 osc me_M 0 me_Zo 0. 0. 
@me_m0_6 osc me_M 0 me_Zo 0. 0. 
@me_m0_7 osc me_M 0 me_Zo 0. 0. 
@me_m0_8 osc me_M 0 me_Zo 0. 0. 
@me_m0_9 ground 0
@me_m1_0 osc me_M 0 me_Zo 0. 0. 
@me_m1_1 osc me_M 0 me_Zo 0. 0. 
@me_m1_2 osc me_M 0 me_Zo 0. 0. 
@me_m1_3 osc me_M 0 me_Zo 0. 0. 
@me_m1_4 osc me_M 0 me_Zo 0. 0. 
@me_m1_5 osc me_M 0 me_Zo 0. 0. 
@me_m1_6 osc me_M 0 me_Zo 0. 0. 
@me_m1_7 osc me_M 0 me_Zo 0. 0. 
@me_m1_8 osc me_M 0 me_Zo 0. 0. 
@me_m1_9 osc me_M 0 me_Zo 0. 0. 
@me_m2_0 osc me_M 0 me_Zo 0. 0. 
@me_m2_1 osc me_M 0 me_Zo 0. 0. 
@me_m2_2 osc me_M 0 me_Zo 0. 0. 
@me_m2_3 osc me_M 0 me_Zo 0. 0. 
@me_m2_4 osc me_M 0 me_Zo 0. 0. 
@me_m2_5 osc me_M 0 me_Zo 0. 0. 
@me_m2_6 osc me_M 0 me_Zo 0. 0. 
@me_m2_7 osc me_M 0 me_Zo 0. 0. 
@me_m2_8 osc me_M 0 me_Zo 0. 0. 
@me_m2_9 osc me_M 0 me_Zo 0. 0. 
@me_m3_0 osc me_M 0 me_Zo 0. 0. 
@me_m3_1 osc me_M 0 me_Zo 0. 0. 
@me_m3_2 osc me_M 0 me_Zo 0. 0. 
@me_m3_3 osc me_M 0 me_Zo 0. 0. 
@me_m3_4 osc me_M 0 me_Zo 0. 0. 
@me_m3_5 osc me_M 0 me_Zo 0. 0. 
@me_m3_6 osc me_M 0 me_Zo 0. 0. 
@me_m3_7 osc me_M 0 me_Zo 0. 0. 
@me_m3_8 osc me_M 0 me_Zo 0. 0. 
@me_m3_9 osc me_M 0 me_Zo 0. 0. 
@me_m4_0 osc me_M 0 me_Zo 0. 0. 
@me_m4_1 osc me_M 0 me_Zo 0. 0. 
@me_m4_2 osc me_M 0 me_Zo 0. 0. 
@me_m4_3 osc me_M 0 me_Zo 0. 0. 
@me_m4_4 osc me_M 0 me_Zo 0. 0. 
@me_m4_5 osc me_M 0 me_Zo 0. 0. 
@me_m4_6 osc me_M 0 me_Zo 0. 0. 
@me_m4_7 osc me_M 0 me_Zo 0. 0. 
@me_m4_8 osc me_M 0 me_Zo 0. 0. 
@me_m4_9 osc me_M 0 me_Zo 0. 0. 
@me_m5_0 osc me_M 0 me_Zo 0. 0. 
@me_m5_1 osc me_M 0 me_Zo 0. 0. 
@me_m5_2 osc me_M 0 me_Zo 0. 0. 
@me_m5_3 osc me_M 0 me_Zo 0. 0. 
@me_m5_4 osc me_M 0 me_Zo 0. 0. 
@me_m5_5 osc me_M 0 me_Zo 0. 0. 
@me_m5_6 osc me_M 0 me_Zo 0. 0. 
@me_m5_7 osc me_M 0 me_Zo 0. 0. 
@me_m5_8 osc me_M 0 me_Zo 0. 0. 
@me_m5_9 osc me_M 0 me_Zo 0. 0. 
@me_m6_0 osc me_M 0 me_Zo 0. 0. 
@me_m6_1 osc me_M 0 me_Zo 0. 0. 
@me_m6_2 osc me_M 0 me_Zo 0. 0. 
@me_m6_3 osc me_M 0 me_Zo 0. 0. 
@me_m6_4 osc me_M 0 me_Zo 0. 0. 
@me_m6_5 osc me_M 0 me_Zo 0. 0. 
@me_m6_6 osc me_M 0 me_Zo 0. 0. 
@me_m6_7 osc me_M 0 me_Zo 0. 0. 
@me_m6_8 osc me_M 0 me_Zo 0. 0. 
@me_m6_9 osc me_M 0 me_Zo 0. 0. 
@me_m7_0 osc me_M 0 me_Zo 0. 0. 
@me_m7_1 osc me_M 0 me_Zo 0. 0. 
@me_m7_2 osc me_M 0 me_Zo 0. 0. 
@me_m7_3 osc me_M 0 me_Zo 0. 0. 
@me_m7_4 osc me_M 0 me_Zo 0. 0. 
@me_m7_5 osc me_M 0 me_Zo 0. 0. 
@me_m7_6 osc me_M 0 me_Zo 0. 0. 
@me_m7_7 osc me_M 0 me_Zo 0. 0. 
@me_m7_8 osc me_M 0 me_Zo 0. 0. 
@me_m7_9 osc me_M 0 me_Zo 0. 0. 
@me_m8_0 osc me_M 0 me_Zo 0. 0. 
@me_m8_1 osc me_M 0 me_Zo 0. 0. 
@me_m8_2 osc me_M 0 me_Zo 0. 0. 
@me_m8_3 osc me_M 0 me_Zo 0. 0. 
@me_m8_4 osc me_M 0 me_Zo 0. 0. 
@me_m8_5 osc me_M 0 me_Zo 0. 0. 
@me_m8_6 osc me_M 0 me_Zo 0. 0. 
@me_m8_7 osc me_M 0 me_Zo 0. 0. 
@me_m8_8 osc me_M 0 me_Zo 0. 0. 
@me_m8_9 osc me_M 0 me_Zo 0. 0. 
@me_m9_0 ground 0
@me_m9_1 osc me_M 0 me_Zo 0. 0. 
@me_m9_2 osc me_M 0 me_Zo 0. 0. 
@me_m9_3 osc me_M 0 me_Zo 0. 0. 
@me_m9_4 osc me_M 0 me_Zo 0. 0. 
@me_m9_5 osc me_M 0 me_Zo 0. 0. 
@me_m9_6 osc me_M 0 me_Zo 0. 0. 
@me_m9_7 osc me_M 0 me_Zo 0. 0. 
@me_m9_8 osc me_M 0 me_Zo 0. 0. 
@me_m9_9 ground 0

@me_r0 springDamper @me_m0_0 @me_m0_1 me_K me_Z
@me_r1 springDamper @me_m0_1 @me_m0_2 me_K me_Z
@me_r2 springDamper @me_m0_2 @me_m0_3 me_K me_Z
@me_r3 springDamper @me_m0_3 @me_m0_4 me_K me_Z
@me_r4 springDamper @me_m0_4 @me_m0_5 me_K me_Z
@me_r5 springDamper @me_m0_5 @me_m0_6 me_K me_Z
@me_r6 springDamper @me_m0_6 @me_m0_7 me_K me_Z
@me_r7 springDamper @me_m0_7 @me_m0_8 me_K me_Z
@me_r8 springDamper @me_m0_8 @me_m0_9 me_K me_Z
@me_r9 springDamper @me_m1_0 @me_m1_1 me_K me_Z
@me_r10 springDamper @me_m1_1 @me_m1_2 me_K me_Z
@me_r11 springDamper @me_m1_2 @me_m1_3 me_K me_Z
@me_r12 springDamper @me_m1_3 @me_m1_4 me_K me_Z
@me_r13 springDamper @me_m1_4 @me_m1_5 me_K me_Z
@me_r14 springDamper @me_m1_5 @me_m1_6 me_K me_Z
@me_r15 springDamper @me_m1_6 @me_m1_7 me_K me_Z
@me_r16 springDamper @me_m1_7 @me_m1_8 me_K me_Z
@me_r17 springDamper @me_m1_8 @me_m1_9 me_K me_Z
@me_r18 springDamper @me_m2_0 @me_m2_1 me_K me_Z
@me_r19 springDamper @me_m2_1 @me_m2_2 me_K me_Z
@me_r20 springDamper @me_m2_2 @me_m2_3 me_K me_Z
@me_r21 springDamper @me_m2_3 @me_m2_4 me_K me_Z
@me_r22 springDamper @me_m2_4 @me_m2_5 me_K me_Z
@me_r23 springDamper @me_m2_5 @me_m2_6 me_K me_Z
@me_r24 springDamper @me_m2_6 @me_m2_7 me_K me_Z
@me_r25 springDamper @me_m2_7 @me_m2_8 me_K me_Z
@me_r26 springDamper @me_m2_8 @me_m2_9 me_K me_Z
@me_r27 springDamper @me_m3_0 @me_m3_1 me_K me_Z
@me_r28 springDamper @me_m3_1 @me_m3_2 me_K me_Z
@me_r29 springDamper @me_m3_2 @me_m3_3 me_K me_Z
@me_r30 springDamper @me_m3_3 @me_m3_4 me_K me_Z
@me_r31 springDamper @me_m3_4 @me_m3_5 me_K me_Z
@me_r32 springDamper @me_m3_5 @me_m3_6 me_K me_Z
@me_r33 springDamper @me_m3_6 @me_m3_7 me_K me_Z
@me_r34 springDamper @me_m3_7 @me_m3_8 me_K me_Z
@me_r35 springDamper @me_m3_8 @me_m3_9 me_K me_Z
@me_r36 springDamper @me_m4_0 @me_m4_1 me_K me_Z
@me_r37 springDamper @me_m4_1 @me_m4_2 me_K me_Z
@me_r38 springDamper @me_m4_2 @me_m4_3 me_K me_Z
@me_r39 springDamper @me_m4_3 @me_m4_4 me_K me_Z
@me_r40 springDamper @me_m4_4 @me_m4_5 me_K me_Z
@me_r41 springDamper @me_m4_5 @me_m4_6 me_K me_Z
@me_r42 springDamper @me_m4_6 @me_m4_7 me_K me_Z
@me_r43 springDamper @me_m4_7 @me_m4_8 me_K me_Z
@me_r44 springDamper @me_m4_8 @me_m4_9 me_K me_Z
@me_r45 springDamper @me_m5_0 @me_m5_1 me_K me_Z
@me_r46 springDamper @me_m5_1 @me_m5_2 me_K me_Z
@me_r47 springDamper @me_m5_2 @me_m5_3 me_K me_Z
@me_r48 springDamper @me_m5_3 @me_m5_4 me_K me_Z
@me_r49 springDamper @me_m5_4 @me_m5_5 me_K me_Z
@me_r50 springDamper @me_m5_5 @me_m5_6 me_K me_Z
@me_r51 springDamper @me_m5_6 @me_m5_7 me_K me_Z
@me_r52 springDamper @me_m5_7 @me_m5_8 me_K me_Z
@me_r53 springDamper @me_m5_8 @me_m5_9 me_K me_Z
@me_r54 springDamper @me_m6_0 @me_m6_1 me_K me_Z
@me_r55 springDamper @me_m6_1 @me_m6_2 me_K me_Z
@me_r56 springDamper @me_m6_2 @me_m6_3 me_K me_Z
@me_r57 springDamper @me_m6_3 @me_m6_4 me_K me_Z
@me_r58 springDamper @me_m6_4 @me_m6_5 me_K me_Z
@me_r59 springDamper @me_m6_5 @me_m6_6 me_K me_Z
@me_r60 springDamper @me_m6_6 @me_m6_7 me_K me_Z
@me_r61 springDamper @me_m6_7 @me_m6_8 me_K me_Z
@me_r62 springDamper @me_m6_8 @me_m6_9 me_K me_Z
@me_r63 springDamper @me_m7_0 @me_m7_1 me_K me_Z
@me_r64 springDamper @me_m7_1 @me_m7_2 me_K me_Z
@me_r65 springDamper @me_m7_2 @me_m7_3 me_K me_Z
@me_r66 springDamper @me_m7_3 @me_m7_4 me_K me_Z
@me_r67 springDamper @me_m7_4 @me_m7_5 me_K me_Z
@me_r68 springDamper @me_m7_5 @me_m7_6 me_K me_Z
@me_r69 springDamper @me_m7_6 @me_m7_7 me_K me_Z
@me_r70 springDamper @me_m7_7 @me_m7_8 me_K me_Z
@me_r71 springDamper @me_m7_8 @me_m7_9 me_K me_Z
@me_r72 springDamper @me_m8_0 @me_m8_1 me_K me_Z
@me_r73 springDamper @me_m8_1 @me_m8_2 me_K me_Z
@me_r74 springDamper @me_m8_2 @me_m8_3 me_K me_Z
@me_r75 springDamper @me_m8_3 @me_m8_4 me_K me_Z
@me_r76 springDamper @me_m8_4 @me_m8_5 me_K me_Z
@me_r77 springDamper @me_m8_5 @me_m8_6 me_K me_Z
@me_r78 springDamper @me_m8_6 @me_m8_7 me_K me_Z
@me_r79 springDamper @me_m8_7 @me_m8_8 me_K me_Z
@me_r80 springDamper @me_m8_8 @me_m8_9 me_K me_Z
@me_r81 springDamper @me_m9_0 @me_m9_1 me_K me_Z
@me_r82 springDamper @me_m9_1 @me_m9_2 me_K me_Z
@me_r83 springDamper @me_m9_2 @me_m9_3 me_K me_Z
@me_r84 springDamper @me_m9_3 @me_m9_4 me_K me_Z
@me_r85 springDamper @me_m9_4 @me_m9_5 me_K me_Z
@me_r86 springDamper @me_m9_5 @me_m9_6 me_K me_Z
@me_r87 springDamper @me_m9_6 @me_m9_7 me_K me_Z
@me_r88 springDamper @me_m9_7 @me_m9_8 me_K me_Z
@me_r89 springDamper @me_m9_8 @me_m9_9 me_K me_Z

@me_r90 springDamper @me_m0_0 @me_m1_0 me_K me_Z
@me_r91 springDamper @me_m0_1 @me_m1_1 me_K me_Z
@me_r92 springDamper @me_m0_2 @me_m1_2 me_K me_Z
@me_r93 springDamper @me_m0_3 @me_m1_3 me_K me_Z
@me_r94 springDamper @me_m0_4 @me_m1_4 me_K me_Z
@me_r95 springDamper @me_m0_5 @me_m1_5 me_K me_Z
@me_r96 springDamper @me_m0_6 @me_m1_6 me_K me_Z
@me_r97 springDamper @me_m0_7 @me_m1_7 me_K me_Z
@me_r98 springDamper @me_m0_8 @me_m1_8 me_K me_Z
@me_r99 springDamper @me_m0_9 @me_m1_9 me_K me_Z
@me_r100 springDamper @me_m1_0 @me_m2_0 me_K me_Z
@me_r101 springDamper @me_m1_1 @me_m2_1 me_K me_Z
@me_r102 springDamper @me_m1_2 @me_m2_2 me_K me_Z
@me_r103 springDamper @me_m1_3 @me_m2_3 me_K me_Z
@me_r104 springDamper @me_m1_4 @me_m2_4 me_K me_Z
@me_r105 springDamper @me_m1_5 @me_m2_5 me_K me_Z
@me_r106 springDamper @me_m1_6 @me_m2_6 me_K me_Z
@me_r107 springDamper @me_m1_7 @me_m2_7 me_K me_Z
@me_r108 springDamper @me_m1_8 @me_m2_8 me_K me_Z
@me_r109 springDamper @me_m1_9 @me_m2_9 me_K me_Z
@me_r110 springDamper @me_m2_0 @me_m3_0 me_K me_Z
@me_r111 springDamper @me_m2_1 @me_m3_1 me_K me_Z
@me_r112 springDamper @me_m2_2 @me_m3_2 me_K me_Z
@me_r113 springDamper @me_m2_3 @me_m3_3 me_K me_Z
@me_r114 springDamper @me_m2_4 @me_m3_4 me_K me_Z
@me_r115 springDamper @me_m2_5 @me_m3_5 me_K me_Z
@me_r116 springDamper @me_m2_6 @me_m3_6 me_K me_Z
@me_r117 springDamper @me_m2_7 @me_m3_7 me_K me_Z
@me_r118 springDamper @me_m2_8 @me_m3_8 me_K me_Z
@me_r119 springDamper @me_m2_9 @me_m3_9 me_K me_Z
@me_r120 springDamper @me_m3_0 @me_m4_0 me_K me_Z
@me_r121 springDamper @me_m3_1 @me_m4_1 me_K me_Z
@me_r122 springDamper @me_m3_2 @me_m4_2 me_K me_Z
@me_r123 springDamper @me_m3_3 @me_m4_3 me_K me_Z
@me_r124 springDamper @me_m3_4 @me_m4_4 me_K me_Z
@me_r125 springDamper @me_m3_5 @me_m4_5 me_K me_Z
@me_r126 springDamper @me_m3_6 @me_m4_6 me_K me_Z
@me_r127 springDamper @me_m3_7 @me_m4_7 me_K me_Z
@me_r128 springDamper @me_m3_8 @me_m4_8 me_K me_Z
@me_r129 springDamper @me_m3_9 @me_m4_9 me_K me_Z
@me_r130 springDamper @me_m4_0 @me_m5_0 me_K me_Z
@me_r131 springDamper @me_m4_1 @me_m5_1 me_K me_Z
@me_r132 springDamper @me_m4_2 @me_m5_2 me_K me_Z
@me_r133 springDamper @me_m4_3 @me_m5_3 me_K me_Z
@me_r134 springDamper @me_m4_4 @me_m5_4 me_K me_Z
@me_r135 springDamper @me_m4_5 @me_m5_5 me_K me_Z
@me_r136 springDamper @me_m4_6 @me_m5_6 me_K me_Z
@me_r137 springDamper @me_m4_7 @me_m5_7 me_K me_Z
@me_r138 springDamper @me_m4_8 @me_m5_8 me_K me_Z
@me_r139 springDamper @me_m4_9 @me_m5_9 me_K me_Z
@me_r140 springDamper @me_m5_0 @me_m6_0 me_K me_Z
@me_r141 springDamper @me_m5_1 @me_m6_1 me_K me_Z
@me_r142 springDamper @me_m5_2 @me_m6_2 me_K me_Z
@me_r143 springDamper @me_m5_3 @me_m6_3 me_K me_Z
@me_r144 springDamper @me_m5_4 @me_m6_4 me_K me_Z
@me_r145 springDamper @me_m5_5 @me_m6_5 me_K me_Z
@me_r146 springDamper @me_m5_6 @me_m6_6 me_K me_Z
@me_r147 springDamper @me_m5_7 @me_m6_7 me_K me_Z
@me_r148 springDamper @me_m5_8 @me_m6_8 me_K me_Z
@me_r149 springDamper @me_m5_9 @me_m6_9 me_K me_Z
@me_r150 springDamper @me_m6_0 @me_m7_0 me_K me_Z
@me_r151 springDamper @me_m6_1 @me_m7_1 me_K me_Z
@me_r152 springDamper @me_m6_2 @me_m7_2 me_K me_Z
@me_r153 springDamper @me_m6_3 @me_m7_3 me_K me_Z
@me_r154 springDamper @me_m6_4 @me_m7_4 me_K me_Z
@me_r155 springDamper @me_m6_5 @me_m7_5 me_K me_Z
@me_r156 springDamper @me_m6_6 @me_m7_6 me_K me_Z
@me_r157 springDamper @me_m6_7 @me_m7_7 me_K me_Z
@me_r158 springDamper @me_m6_8 @me_m7_8 me_K me_Z
@me_r159 springDamper @me_m6_9 @me_m7_9 me_K me_Z
@me_r160 springDamper @me_m7_0 @me_m8_0 me_K me_Z
@me_r161 springDamper @me_m7_1 @me_m8_1 me_K me_Z
@me_r162 springDamper @me_m7_2 @me_m8_2 me_K me_Z
@me_r163 springDamper @me_m7_3 @me_m8_3 me_K me_Z
@me_r164 springDamper @me_m7_4 @me_m8_4 me_K me_Z
@me_r165 springDamper @me_m7_5 @me_m8_5 me_K me_Z
@me_r166 springDamper @me_m7_6 @me_m8_6 me_K me_Z
@me_r167 springDamper @me_m7_7 @me_m8_7 me_K me_Z
@me_r168 springDamper @me_m7_8 @me_m8_8 me_K me_Z
@me_r169 springDamper @me_m7_9 @me_m8_9 me_K me_Z
@me_r170 springDamper @me_m8_0 @me_m9_0 me_K me_Z
@me_r171 springDamper @me_m8_1 @me_m9_1 me_K me_Z
@me_r172 springDamper @me_m8_2 @me_m9_2 me_K me_Z
@me_r173 springDamper @me_m8_3 @me_m9_3 me_K me_Z
@me_r174 springDamper @me_m8_4 @me_m9_4 me_K me_Z
@me_r175 springDamper @me_m8_5 @me_m9_5 me_K me_Z
@me_r176 springDamper @me_m8_6 @me_m9_6 me_K me_Z
@me_r177 springDamper @me_m8_7 @me_m9_7 me_K me_Z
@me_r178 springDamper @me_m8_8 @me_m9_8 me_K me_Z
@me_r179 springDamper @me_m8_9 @me_m9_9 me_K me_Z

@out1 posOutput @me_m5_5
@out2 posOutput @t_m2_1

*/