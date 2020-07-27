declare name    "Plucked String";
declare author  "James Leonard";
declare date    "April 2020";

/* ========= DESCRITPION =============

A plucked string with a few controls.
    - inputs: pick position.
    - outputs: two listening points on the string.
    - controls: pick stiffness and damping, string stiffness, damping and air friction.

Note: the model block diagram is starting to look like a piece of modern art.
*/


import("stdfaust.lib");

in1 = hslider("Pick position", 0, -1, 1, 0.001):si.smoo;

OutGain = 5;

str_M = 1.0;
str_K = hslider("string stiffness", 0.7, 0.001, 0.7, 0.001):si.smoo;
str_Z = hslider("string internal damping", 0.0009, 0.00, 0.01, 0.00001):si.smoo;
str_Zo = hslider("string air friction", 0.00005, 0.00, 0.0002, 0.00001):si.smoo;
nlK = hslider("pick stiffness", 0.5, 0., 0.8, 0.001);
nlscale = 0.05;
pZ = hslider("pick damping", 0.04, 0., 0.1, 0.001);

model = (
	mi.ground(0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.oscil(str_M, 0, str_Zo, 0, 0., 0.),
	mi.ground(0.),
	mi.posInput(0.):
	RoutingMassToLink :
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
	mi.springDamper(str_K, str_Z, 0., 0.),
	mi.springDamper(str_K, str_Z, 0., 0.),
	mi.springDamper(str_K, str_Z, 0., 0.),
	mi.springDamper(str_K, str_Z, 0., 0.),
	mi.springDamper(str_K, str_Z, 0., 0.),
	mi.springDamper(str_K, str_Z, 0., 0.),
	mi.springDamper(str_K, str_Z, 0., 0.),
	mi.springDamper(str_K, str_Z, 0., 0.),
	mi.nlPluck(nlK, nlscale, pZ, 0., 0.),
	par(i, nbOut, _):
	RoutingLinkToMass
)~par(i, nbMass, _):
par(i, nbMass, !), par(i, nbOut , _)
with{
	RoutingMassToLink(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29, m30, m31, m32, m33, m34, m35, m36, m37, m38, m39, m40, m41, m42, m43, m44, m45, m46, m47, m48, m49, m50, m51, m52, m53, m54, m55, m56, m57, m58, m59, m60, m61, m62, m63, m64, m65, m66, m67, m68, m69, m70, m71, m72, m73, m74, m75, m76, m77, m78, m79, m80, m81, m82, m83, m84, m85, m86, m87, m88, m89, m90, m91, m92, m93, m94, m95, m96, m97, m98, m99, m100, m101, m102, m103, m104, m105, m106, m107, m108, m109, m110, m111, m112, m113, m114, m115, m116, m117, m118, m119, m120, m121, m122, m123, m124, m125, m126, m127, m128, m129, m130, m131, m132, m133, m134, m135, m136, m137, m138, m139, m140, m141, m142, m143, m144, m145, m146, m147, m148, m149, m150, m151, m152) = /* routed positions */ m0, m1, m1, m2, m2, m3, m3, m4, m4, m5, m5, m6, m6, m7, m7, m8, m8, m9, m9, m10, m10, m11, m11, m12, m12, m13, m13, m14, m14, m15, m15, m16, m16, m17, m17, m18, m18, m19, m19, m20, m20, m21, m21, m22, m22, m23, m23, m24, m24, m25, m25, m26, m26, m27, m27, m28, m28, m29, m29, m30, m30, m31, m31, m32, m32, m33, m33, m34, m34, m35, m35, m36, m36, m37, m37, m38, m38, m39, m39, m40, m40, m41, m41, m42, m42, m43, m43, m44, m44, m45, m45, m46, m46, m47, m47, m48, m48, m49, m49, m50, m50, m51, m51, m52, m52, m53, m53, m54, m54, m55, m55, m56, m56, m57, m57, m58, m58, m59, m59, m60, m60, m61, m61, m62, m62, m63, m63, m64, m64, m65, m65, m66, m66, m67, m67, m68, m68, m69, m69, m70, m70, m71, m71, m72, m72, m73, m73, m74, m74, m75, m75, m76, m76, m77, m77, m78, m78, m79, m79, m80, m80, m81, m81, m82, m82, m83, m83, m84, m84, m85, m85, m86, m86, m87, m87, m88, m88, m89, m89, m90, m90, m91, m91, m92, m92, m93, m93, m94, m94, m95, m95, m96, m96, m97, m97, m98, m98, m99, m99, m100, m100, m101, m101, m102, m102, m103, m103, m104, m104, m105, m105, m106, m106, m107, m107, m108, m108, m109, m109, m110, m110, m111, m111, m112, m112, m113, m113, m114, m114, m115, m115, m116, m116, m117, m117, m118, m118, m119, m119, m120, m120, m121, m121, m122, m122, m123, m123, m124, m124, m125, m125, m126, m126, m127, m127, m128, m128, m129, m129, m130, m130, m131, m131, m132, m132, m133, m133, m134, m134, m135, m135, m136, m136, m137, m137, m138, m138, m139, m139, m140, m140, m141, m141, m142, m142, m143, m143, m144, m144, m145, m145, m146, m146, m147, m147, m148, m148, m149, m149, m150, m150, m151, m152, m141, /* outputs */ m21, m11;
	RoutingLinkToMass(l0_f1, l0_f2, l1_f1, l1_f2, l2_f1, l2_f2, l3_f1, l3_f2, l4_f1, l4_f2, l5_f1, l5_f2, l6_f1, l6_f2, l7_f1, l7_f2, l8_f1, l8_f2, l9_f1, l9_f2, l10_f1, l10_f2, l11_f1, l11_f2, l12_f1, l12_f2, l13_f1, l13_f2, l14_f1, l14_f2, l15_f1, l15_f2, l16_f1, l16_f2, l17_f1, l17_f2, l18_f1, l18_f2, l19_f1, l19_f2, l20_f1, l20_f2, l21_f1, l21_f2, l22_f1, l22_f2, l23_f1, l23_f2, l24_f1, l24_f2, l25_f1, l25_f2, l26_f1, l26_f2, l27_f1, l27_f2, l28_f1, l28_f2, l29_f1, l29_f2, l30_f1, l30_f2, l31_f1, l31_f2, l32_f1, l32_f2, l33_f1, l33_f2, l34_f1, l34_f2, l35_f1, l35_f2, l36_f1, l36_f2, l37_f1, l37_f2, l38_f1, l38_f2, l39_f1, l39_f2, l40_f1, l40_f2, l41_f1, l41_f2, l42_f1, l42_f2, l43_f1, l43_f2, l44_f1, l44_f2, l45_f1, l45_f2, l46_f1, l46_f2, l47_f1, l47_f2, l48_f1, l48_f2, l49_f1, l49_f2, l50_f1, l50_f2, l51_f1, l51_f2, l52_f1, l52_f2, l53_f1, l53_f2, l54_f1, l54_f2, l55_f1, l55_f2, l56_f1, l56_f2, l57_f1, l57_f2, l58_f1, l58_f2, l59_f1, l59_f2, l60_f1, l60_f2, l61_f1, l61_f2, l62_f1, l62_f2, l63_f1, l63_f2, l64_f1, l64_f2, l65_f1, l65_f2, l66_f1, l66_f2, l67_f1, l67_f2, l68_f1, l68_f2, l69_f1, l69_f2, l70_f1, l70_f2, l71_f1, l71_f2, l72_f1, l72_f2, l73_f1, l73_f2, l74_f1, l74_f2, l75_f1, l75_f2, l76_f1, l76_f2, l77_f1, l77_f2, l78_f1, l78_f2, l79_f1, l79_f2, l80_f1, l80_f2, l81_f1, l81_f2, l82_f1, l82_f2, l83_f1, l83_f2, l84_f1, l84_f2, l85_f1, l85_f2, l86_f1, l86_f2, l87_f1, l87_f2, l88_f1, l88_f2, l89_f1, l89_f2, l90_f1, l90_f2, l91_f1, l91_f2, l92_f1, l92_f2, l93_f1, l93_f2, l94_f1, l94_f2, l95_f1, l95_f2, l96_f1, l96_f2, l97_f1, l97_f2, l98_f1, l98_f2, l99_f1, l99_f2, l100_f1, l100_f2, l101_f1, l101_f2, l102_f1, l102_f2, l103_f1, l103_f2, l104_f1, l104_f2, l105_f1, l105_f2, l106_f1, l106_f2, l107_f1, l107_f2, l108_f1, l108_f2, l109_f1, l109_f2, l110_f1, l110_f2, l111_f1, l111_f2, l112_f1, l112_f2, l113_f1, l113_f2, l114_f1, l114_f2, l115_f1, l115_f2, l116_f1, l116_f2, l117_f1, l117_f2, l118_f1, l118_f2, l119_f1, l119_f2, l120_f1, l120_f2, l121_f1, l121_f2, l122_f1, l122_f2, l123_f1, l123_f2, l124_f1, l124_f2, l125_f1, l125_f2, l126_f1, l126_f2, l127_f1, l127_f2, l128_f1, l128_f2, l129_f1, l129_f2, l130_f1, l130_f2, l131_f1, l131_f2, l132_f1, l132_f2, l133_f1, l133_f2, l134_f1, l134_f2, l135_f1, l135_f2, l136_f1, l136_f2, l137_f1, l137_f2, l138_f1, l138_f2, l139_f1, l139_f2, l140_f1, l140_f2, l141_f1, l141_f2, l142_f1, l142_f2, l143_f1, l143_f2, l144_f1, l144_f2, l145_f1, l145_f2, l146_f1, l146_f2, l147_f1, l147_f2, l148_f1, l148_f2, l149_f1, l149_f2, l150_f1, l150_f2, l151_f1, l151_f2, p_out1, p_out2) = /* routed forces  */ l0_f1, l0_f2 + l1_f1, l1_f2 + l2_f1, l2_f2 + l3_f1, l3_f2 + l4_f1, l4_f2 + l5_f1, l5_f2 + l6_f1, l6_f2 + l7_f1, l7_f2 + l8_f1, l8_f2 + l9_f1, l9_f2 + l10_f1, l10_f2 + l11_f1, l11_f2 + l12_f1, l12_f2 + l13_f1, l13_f2 + l14_f1, l14_f2 + l15_f1, l15_f2 + l16_f1, l16_f2 + l17_f1, l17_f2 + l18_f1, l18_f2 + l19_f1, l19_f2 + l20_f1, l20_f2 + l21_f1, l21_f2 + l22_f1, l22_f2 + l23_f1, l23_f2 + l24_f1, l24_f2 + l25_f1, l25_f2 + l26_f1, l26_f2 + l27_f1, l27_f2 + l28_f1, l28_f2 + l29_f1, l29_f2 + l30_f1, l30_f2 + l31_f1, l31_f2 + l32_f1, l32_f2 + l33_f1, l33_f2 + l34_f1, l34_f2 + l35_f1, l35_f2 + l36_f1, l36_f2 + l37_f1, l37_f2 + l38_f1, l38_f2 + l39_f1, l39_f2 + l40_f1, l40_f2 + l41_f1, l41_f2 + l42_f1, l42_f2 + l43_f1, l43_f2 + l44_f1, l44_f2 + l45_f1, l45_f2 + l46_f1, l46_f2 + l47_f1, l47_f2 + l48_f1, l48_f2 + l49_f1, l49_f2 + l50_f1, l50_f2 + l51_f1, l51_f2 + l52_f1, l52_f2 + l53_f1, l53_f2 + l54_f1, l54_f2 + l55_f1, l55_f2 + l56_f1, l56_f2 + l57_f1, l57_f2 + l58_f1, l58_f2 + l59_f1, l59_f2 + l60_f1, l60_f2 + l61_f1, l61_f2 + l62_f1, l62_f2 + l63_f1, l63_f2 + l64_f1, l64_f2 + l65_f1, l65_f2 + l66_f1, l66_f2 + l67_f1, l67_f2 + l68_f1, l68_f2 + l69_f1, l69_f2 + l70_f1, l70_f2 + l71_f1, l71_f2 + l72_f1, l72_f2 + l73_f1, l73_f2 + l74_f1, l74_f2 + l75_f1, l75_f2 + l76_f1, l76_f2 + l77_f1, l77_f2 + l78_f1, l78_f2 + l79_f1, l79_f2 + l80_f1, l80_f2 + l81_f1, l81_f2 + l82_f1, l82_f2 + l83_f1, l83_f2 + l84_f1, l84_f2 + l85_f1, l85_f2 + l86_f1, l86_f2 + l87_f1, l87_f2 + l88_f1, l88_f2 + l89_f1, l89_f2 + l90_f1, l90_f2 + l91_f1, l91_f2 + l92_f1, l92_f2 + l93_f1, l93_f2 + l94_f1, l94_f2 + l95_f1, l95_f2 + l96_f1, l96_f2 + l97_f1, l97_f2 + l98_f1, l98_f2 + l99_f1, l99_f2 + l100_f1, l100_f2 + l101_f1, l101_f2 + l102_f1, l102_f2 + l103_f1, l103_f2 + l104_f1, l104_f2 + l105_f1, l105_f2 + l106_f1, l106_f2 + l107_f1, l107_f2 + l108_f1, l108_f2 + l109_f1, l109_f2 + l110_f1, l110_f2 + l111_f1, l111_f2 + l112_f1, l112_f2 + l113_f1, l113_f2 + l114_f1, l114_f2 + l115_f1, l115_f2 + l116_f1, l116_f2 + l117_f1, l117_f2 + l118_f1, l118_f2 + l119_f1, l119_f2 + l120_f1, l120_f2 + l121_f1, l121_f2 + l122_f1, l122_f2 + l123_f1, l123_f2 + l124_f1, l124_f2 + l125_f1, l125_f2 + l126_f1, l126_f2 + l127_f1, l127_f2 + l128_f1, l128_f2 + l129_f1, l129_f2 + l130_f1, l130_f2 + l131_f1, l131_f2 + l132_f1, l132_f2 + l133_f1, l133_f2 + l134_f1, l134_f2 + l135_f1, l135_f2 + l136_f1, l136_f2 + l137_f1, l137_f2 + l138_f1, l138_f2 + l139_f1, l139_f2 + l140_f1, l140_f2 + l141_f1 + l151_f2, l141_f2 + l142_f1, l142_f2 + l143_f1, l143_f2 + l144_f1, l144_f2 + l145_f1, l145_f2 + l146_f1, l146_f2 + l147_f1, l147_f2 + l148_f1, l148_f2 + l149_f1, l149_f2 + l150_f1, l150_f2, l151_f1, /* pass-through */ p_out1, p_out2;
	nbMass = 153;
	nbOut = 2;
};
process = in1 : model:*(OutGain), *(OutGain);


/*
========= MIMS SCRIPT USED FOR MODEL GENERATION =============

# Plucked string model
# Script author : James Leonard

@nlK param 0.8                                 
@nlscale param 0.005
@pZ param 0.001

@str_M param 1
@str_K param 0.5
@str_Z param 0.001
@str_Zo param 0.00005

@str_s0 ground 0.
@str_m0 osc str_M 0 str_Zo 0. 0.
@str_m1 osc str_M 0 str_Zo 0. 0.
@str_m2 osc str_M 0 str_Zo 0. 0.
@str_m3 osc str_M 0 str_Zo 0. 0.
@str_m4 osc str_M 0 str_Zo 0. 0.
@str_m5 osc str_M 0 str_Zo 0. 0.
@str_m6 osc str_M 0 str_Zo 0. 0.
@str_m7 osc str_M 0 str_Zo 0. 0.
@str_m8 osc str_M 0 str_Zo 0. 0.
@str_m9 osc str_M 0 str_Zo 0. 0.
@str_m10 osc str_M 0 str_Zo 0. 0.
@str_m11 osc str_M 0 str_Zo 0. 0.
@str_m12 osc str_M 0 str_Zo 0. 0.
@str_m13 osc str_M 0 str_Zo 0. 0.
@str_m14 osc str_M 0 str_Zo 0. 0.
@str_m15 osc str_M 0 str_Zo 0. 0.
@str_m16 osc str_M 0 str_Zo 0. 0.
@str_m17 osc str_M 0 str_Zo 0. 0.
@str_m18 osc str_M 0 str_Zo 0. 0.
@str_m19 osc str_M 0 str_Zo 0. 0.
@str_m20 osc str_M 0 str_Zo 0. 0.
@str_m21 osc str_M 0 str_Zo 0. 0.
@str_m22 osc str_M 0 str_Zo 0. 0.
@str_m23 osc str_M 0 str_Zo 0. 0.
@str_m24 osc str_M 0 str_Zo 0. 0.
@str_m25 osc str_M 0 str_Zo 0. 0.
@str_m26 osc str_M 0 str_Zo 0. 0.
@str_m27 osc str_M 0 str_Zo 0. 0.
@str_m28 osc str_M 0 str_Zo 0. 0.
@str_m29 osc str_M 0 str_Zo 0. 0.
@str_m30 osc str_M 0 str_Zo 0. 0.
@str_m31 osc str_M 0 str_Zo 0. 0.
@str_m32 osc str_M 0 str_Zo 0. 0.
@str_m33 osc str_M 0 str_Zo 0. 0.
@str_m34 osc str_M 0 str_Zo 0. 0.
@str_m35 osc str_M 0 str_Zo 0. 0.
@str_m36 osc str_M 0 str_Zo 0. 0.
@str_m37 osc str_M 0 str_Zo 0. 0.
@str_m38 osc str_M 0 str_Zo 0. 0.
@str_m39 osc str_M 0 str_Zo 0. 0.
@str_m40 osc str_M 0 str_Zo 0. 0.
@str_m41 osc str_M 0 str_Zo 0. 0.
@str_m42 osc str_M 0 str_Zo 0. 0.
@str_m43 osc str_M 0 str_Zo 0. 0.
@str_m44 osc str_M 0 str_Zo 0. 0.
@str_m45 osc str_M 0 str_Zo 0. 0.
@str_m46 osc str_M 0 str_Zo 0. 0.
@str_m47 osc str_M 0 str_Zo 0. 0.
@str_m48 osc str_M 0 str_Zo 0. 0.
@str_m49 osc str_M 0 str_Zo 0. 0.
@str_m50 osc str_M 0 str_Zo 0. 0.
@str_m51 osc str_M 0 str_Zo 0. 0.
@str_m52 osc str_M 0 str_Zo 0. 0.
@str_m53 osc str_M 0 str_Zo 0. 0.
@str_m54 osc str_M 0 str_Zo 0. 0.
@str_m55 osc str_M 0 str_Zo 0. 0.
@str_m56 osc str_M 0 str_Zo 0. 0.
@str_m57 osc str_M 0 str_Zo 0. 0.
@str_m58 osc str_M 0 str_Zo 0. 0.
@str_m59 osc str_M 0 str_Zo 0. 0.
@str_m60 osc str_M 0 str_Zo 0. 0.
@str_m61 osc str_M 0 str_Zo 0. 0.
@str_m62 osc str_M 0 str_Zo 0. 0.
@str_m63 osc str_M 0 str_Zo 0. 0.
@str_m64 osc str_M 0 str_Zo 0. 0.
@str_m65 osc str_M 0 str_Zo 0. 0.
@str_m66 osc str_M 0 str_Zo 0. 0.
@str_m67 osc str_M 0 str_Zo 0. 0.
@str_m68 osc str_M 0 str_Zo 0. 0.
@str_m69 osc str_M 0 str_Zo 0. 0.
@str_m70 osc str_M 0 str_Zo 0. 0.
@str_m71 osc str_M 0 str_Zo 0. 0.
@str_m72 osc str_M 0 str_Zo 0. 0.
@str_m73 osc str_M 0 str_Zo 0. 0.
@str_m74 osc str_M 0 str_Zo 0. 0.
@str_m75 osc str_M 0 str_Zo 0. 0.
@str_m76 osc str_M 0 str_Zo 0. 0.
@str_m77 osc str_M 0 str_Zo 0. 0.
@str_m78 osc str_M 0 str_Zo 0. 0.
@str_m79 osc str_M 0 str_Zo 0. 0.
@str_m80 osc str_M 0 str_Zo 0. 0.
@str_m81 osc str_M 0 str_Zo 0. 0.
@str_m82 osc str_M 0 str_Zo 0. 0.
@str_m83 osc str_M 0 str_Zo 0. 0.
@str_m84 osc str_M 0 str_Zo 0. 0.
@str_m85 osc str_M 0 str_Zo 0. 0.
@str_m86 osc str_M 0 str_Zo 0. 0.
@str_m87 osc str_M 0 str_Zo 0. 0.
@str_m88 osc str_M 0 str_Zo 0. 0.
@str_m89 osc str_M 0 str_Zo 0. 0.
@str_m90 osc str_M 0 str_Zo 0. 0.
@str_m91 osc str_M 0 str_Zo 0. 0.
@str_m92 osc str_M 0 str_Zo 0. 0.
@str_m93 osc str_M 0 str_Zo 0. 0.
@str_m94 osc str_M 0 str_Zo 0. 0.
@str_m95 osc str_M 0 str_Zo 0. 0.
@str_m96 osc str_M 0 str_Zo 0. 0.
@str_m97 osc str_M 0 str_Zo 0. 0.
@str_m98 osc str_M 0 str_Zo 0. 0.
@str_m99 osc str_M 0 str_Zo 0. 0.
@str_m100 osc str_M 0 str_Zo 0. 0.
@str_m101 osc str_M 0 str_Zo 0. 0.
@str_m102 osc str_M 0 str_Zo 0. 0.
@str_m103 osc str_M 0 str_Zo 0. 0.
@str_m104 osc str_M 0 str_Zo 0. 0.
@str_m105 osc str_M 0 str_Zo 0. 0.
@str_m106 osc str_M 0 str_Zo 0. 0.
@str_m107 osc str_M 0 str_Zo 0. 0.
@str_m108 osc str_M 0 str_Zo 0. 0.
@str_m109 osc str_M 0 str_Zo 0. 0.
@str_m110 osc str_M 0 str_Zo 0. 0.
@str_m111 osc str_M 0 str_Zo 0. 0.
@str_m112 osc str_M 0 str_Zo 0. 0.
@str_m113 osc str_M 0 str_Zo 0. 0.
@str_m114 osc str_M 0 str_Zo 0. 0.
@str_m115 osc str_M 0 str_Zo 0. 0.
@str_m116 osc str_M 0 str_Zo 0. 0.
@str_m117 osc str_M 0 str_Zo 0. 0.
@str_m118 osc str_M 0 str_Zo 0. 0.
@str_m119 osc str_M 0 str_Zo 0. 0.
@str_m120 osc str_M 0 str_Zo 0. 0.
@str_m121 osc str_M 0 str_Zo 0. 0.
@str_m122 osc str_M 0 str_Zo 0. 0.
@str_m123 osc str_M 0 str_Zo 0. 0.
@str_m124 osc str_M 0 str_Zo 0. 0.
@str_m125 osc str_M 0 str_Zo 0. 0.
@str_m126 osc str_M 0 str_Zo 0. 0.
@str_m127 osc str_M 0 str_Zo 0. 0.
@str_m128 osc str_M 0 str_Zo 0. 0.
@str_m129 osc str_M 0 str_Zo 0. 0.
@str_m130 osc str_M 0 str_Zo 0. 0.
@str_m131 osc str_M 0 str_Zo 0. 0.
@str_m132 osc str_M 0 str_Zo 0. 0.
@str_m133 osc str_M 0 str_Zo 0. 0.
@str_m134 osc str_M 0 str_Zo 0. 0.
@str_m135 osc str_M 0 str_Zo 0. 0.
@str_m136 osc str_M 0 str_Zo 0. 0.
@str_m137 osc str_M 0 str_Zo 0. 0.
@str_m138 osc str_M 0 str_Zo 0. 0.
@str_m139 osc str_M 0 str_Zo 0. 0.
@str_m140 osc str_M 0 str_Zo 0. 0.
@str_m141 osc str_M 0 str_Zo 0. 0.
@str_m142 osc str_M 0 str_Zo 0. 0.
@str_m143 osc str_M 0 str_Zo 0. 0.
@str_m144 osc str_M 0 str_Zo 0. 0.
@str_m145 osc str_M 0 str_Zo 0. 0.
@str_m146 osc str_M 0 str_Zo 0. 0.
@str_m147 osc str_M 0 str_Zo 0. 0.
@str_m148 osc str_M 0 str_Zo 0. 0.
@str_m149 osc str_M 0 str_Zo 0. 0.
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
@str_r10 springDamper @str_m9 @str_m10 str_K str_Z
@str_r11 springDamper @str_m10 @str_m11 str_K str_Z
@str_r12 springDamper @str_m11 @str_m12 str_K str_Z
@str_r13 springDamper @str_m12 @str_m13 str_K str_Z
@str_r14 springDamper @str_m13 @str_m14 str_K str_Z
@str_r15 springDamper @str_m14 @str_m15 str_K str_Z
@str_r16 springDamper @str_m15 @str_m16 str_K str_Z
@str_r17 springDamper @str_m16 @str_m17 str_K str_Z
@str_r18 springDamper @str_m17 @str_m18 str_K str_Z
@str_r19 springDamper @str_m18 @str_m19 str_K str_Z
@str_r20 springDamper @str_m19 @str_m20 str_K str_Z
@str_r21 springDamper @str_m20 @str_m21 str_K str_Z
@str_r22 springDamper @str_m21 @str_m22 str_K str_Z
@str_r23 springDamper @str_m22 @str_m23 str_K str_Z
@str_r24 springDamper @str_m23 @str_m24 str_K str_Z
@str_r25 springDamper @str_m24 @str_m25 str_K str_Z
@str_r26 springDamper @str_m25 @str_m26 str_K str_Z
@str_r27 springDamper @str_m26 @str_m27 str_K str_Z
@str_r28 springDamper @str_m27 @str_m28 str_K str_Z
@str_r29 springDamper @str_m28 @str_m29 str_K str_Z
@str_r30 springDamper @str_m29 @str_m30 str_K str_Z
@str_r31 springDamper @str_m30 @str_m31 str_K str_Z
@str_r32 springDamper @str_m31 @str_m32 str_K str_Z
@str_r33 springDamper @str_m32 @str_m33 str_K str_Z
@str_r34 springDamper @str_m33 @str_m34 str_K str_Z
@str_r35 springDamper @str_m34 @str_m35 str_K str_Z
@str_r36 springDamper @str_m35 @str_m36 str_K str_Z
@str_r37 springDamper @str_m36 @str_m37 str_K str_Z
@str_r38 springDamper @str_m37 @str_m38 str_K str_Z
@str_r39 springDamper @str_m38 @str_m39 str_K str_Z
@str_r40 springDamper @str_m39 @str_m40 str_K str_Z
@str_r41 springDamper @str_m40 @str_m41 str_K str_Z
@str_r42 springDamper @str_m41 @str_m42 str_K str_Z
@str_r43 springDamper @str_m42 @str_m43 str_K str_Z
@str_r44 springDamper @str_m43 @str_m44 str_K str_Z
@str_r45 springDamper @str_m44 @str_m45 str_K str_Z
@str_r46 springDamper @str_m45 @str_m46 str_K str_Z
@str_r47 springDamper @str_m46 @str_m47 str_K str_Z
@str_r48 springDamper @str_m47 @str_m48 str_K str_Z
@str_r49 springDamper @str_m48 @str_m49 str_K str_Z
@str_r50 springDamper @str_m49 @str_m50 str_K str_Z
@str_r51 springDamper @str_m50 @str_m51 str_K str_Z
@str_r52 springDamper @str_m51 @str_m52 str_K str_Z
@str_r53 springDamper @str_m52 @str_m53 str_K str_Z
@str_r54 springDamper @str_m53 @str_m54 str_K str_Z
@str_r55 springDamper @str_m54 @str_m55 str_K str_Z
@str_r56 springDamper @str_m55 @str_m56 str_K str_Z
@str_r57 springDamper @str_m56 @str_m57 str_K str_Z
@str_r58 springDamper @str_m57 @str_m58 str_K str_Z
@str_r59 springDamper @str_m58 @str_m59 str_K str_Z
@str_r60 springDamper @str_m59 @str_m60 str_K str_Z
@str_r61 springDamper @str_m60 @str_m61 str_K str_Z
@str_r62 springDamper @str_m61 @str_m62 str_K str_Z
@str_r63 springDamper @str_m62 @str_m63 str_K str_Z
@str_r64 springDamper @str_m63 @str_m64 str_K str_Z
@str_r65 springDamper @str_m64 @str_m65 str_K str_Z
@str_r66 springDamper @str_m65 @str_m66 str_K str_Z
@str_r67 springDamper @str_m66 @str_m67 str_K str_Z
@str_r68 springDamper @str_m67 @str_m68 str_K str_Z
@str_r69 springDamper @str_m68 @str_m69 str_K str_Z
@str_r70 springDamper @str_m69 @str_m70 str_K str_Z
@str_r71 springDamper @str_m70 @str_m71 str_K str_Z
@str_r72 springDamper @str_m71 @str_m72 str_K str_Z
@str_r73 springDamper @str_m72 @str_m73 str_K str_Z
@str_r74 springDamper @str_m73 @str_m74 str_K str_Z
@str_r75 springDamper @str_m74 @str_m75 str_K str_Z
@str_r76 springDamper @str_m75 @str_m76 str_K str_Z
@str_r77 springDamper @str_m76 @str_m77 str_K str_Z
@str_r78 springDamper @str_m77 @str_m78 str_K str_Z
@str_r79 springDamper @str_m78 @str_m79 str_K str_Z
@str_r80 springDamper @str_m79 @str_m80 str_K str_Z
@str_r81 springDamper @str_m80 @str_m81 str_K str_Z
@str_r82 springDamper @str_m81 @str_m82 str_K str_Z
@str_r83 springDamper @str_m82 @str_m83 str_K str_Z
@str_r84 springDamper @str_m83 @str_m84 str_K str_Z
@str_r85 springDamper @str_m84 @str_m85 str_K str_Z
@str_r86 springDamper @str_m85 @str_m86 str_K str_Z
@str_r87 springDamper @str_m86 @str_m87 str_K str_Z
@str_r88 springDamper @str_m87 @str_m88 str_K str_Z
@str_r89 springDamper @str_m88 @str_m89 str_K str_Z
@str_r90 springDamper @str_m89 @str_m90 str_K str_Z
@str_r91 springDamper @str_m90 @str_m91 str_K str_Z
@str_r92 springDamper @str_m91 @str_m92 str_K str_Z
@str_r93 springDamper @str_m92 @str_m93 str_K str_Z
@str_r94 springDamper @str_m93 @str_m94 str_K str_Z
@str_r95 springDamper @str_m94 @str_m95 str_K str_Z
@str_r96 springDamper @str_m95 @str_m96 str_K str_Z
@str_r97 springDamper @str_m96 @str_m97 str_K str_Z
@str_r98 springDamper @str_m97 @str_m98 str_K str_Z
@str_r99 springDamper @str_m98 @str_m99 str_K str_Z
@str_r100 springDamper @str_m99 @str_m100 str_K str_Z
@str_r101 springDamper @str_m100 @str_m101 str_K str_Z
@str_r102 springDamper @str_m101 @str_m102 str_K str_Z
@str_r103 springDamper @str_m102 @str_m103 str_K str_Z
@str_r104 springDamper @str_m103 @str_m104 str_K str_Z
@str_r105 springDamper @str_m104 @str_m105 str_K str_Z
@str_r106 springDamper @str_m105 @str_m106 str_K str_Z
@str_r107 springDamper @str_m106 @str_m107 str_K str_Z
@str_r108 springDamper @str_m107 @str_m108 str_K str_Z
@str_r109 springDamper @str_m108 @str_m109 str_K str_Z
@str_r110 springDamper @str_m109 @str_m110 str_K str_Z
@str_r111 springDamper @str_m110 @str_m111 str_K str_Z
@str_r112 springDamper @str_m111 @str_m112 str_K str_Z
@str_r113 springDamper @str_m112 @str_m113 str_K str_Z
@str_r114 springDamper @str_m113 @str_m114 str_K str_Z
@str_r115 springDamper @str_m114 @str_m115 str_K str_Z
@str_r116 springDamper @str_m115 @str_m116 str_K str_Z
@str_r117 springDamper @str_m116 @str_m117 str_K str_Z
@str_r118 springDamper @str_m117 @str_m118 str_K str_Z
@str_r119 springDamper @str_m118 @str_m119 str_K str_Z
@str_r120 springDamper @str_m119 @str_m120 str_K str_Z
@str_r121 springDamper @str_m120 @str_m121 str_K str_Z
@str_r122 springDamper @str_m121 @str_m122 str_K str_Z
@str_r123 springDamper @str_m122 @str_m123 str_K str_Z
@str_r124 springDamper @str_m123 @str_m124 str_K str_Z
@str_r125 springDamper @str_m124 @str_m125 str_K str_Z
@str_r126 springDamper @str_m125 @str_m126 str_K str_Z
@str_r127 springDamper @str_m126 @str_m127 str_K str_Z
@str_r128 springDamper @str_m127 @str_m128 str_K str_Z
@str_r129 springDamper @str_m128 @str_m129 str_K str_Z
@str_r130 springDamper @str_m129 @str_m130 str_K str_Z
@str_r131 springDamper @str_m130 @str_m131 str_K str_Z
@str_r132 springDamper @str_m131 @str_m132 str_K str_Z
@str_r133 springDamper @str_m132 @str_m133 str_K str_Z
@str_r134 springDamper @str_m133 @str_m134 str_K str_Z
@str_r135 springDamper @str_m134 @str_m135 str_K str_Z
@str_r136 springDamper @str_m135 @str_m136 str_K str_Z
@str_r137 springDamper @str_m136 @str_m137 str_K str_Z
@str_r138 springDamper @str_m137 @str_m138 str_K str_Z
@str_r139 springDamper @str_m138 @str_m139 str_K str_Z
@str_r140 springDamper @str_m139 @str_m140 str_K str_Z
@str_r141 springDamper @str_m140 @str_m141 str_K str_Z
@str_r142 springDamper @str_m141 @str_m142 str_K str_Z
@str_r143 springDamper @str_m142 @str_m143 str_K str_Z
@str_r144 springDamper @str_m143 @str_m144 str_K str_Z
@str_r145 springDamper @str_m144 @str_m145 str_K str_Z
@str_r146 springDamper @str_m145 @str_m146 str_K str_Z
@str_r147 springDamper @str_m146 @str_m147 str_K str_Z
@str_r148 springDamper @str_m147 @str_m148 str_K str_Z
@str_r149 springDamper @str_m148 @str_m149 str_K str_Z
@str_r150 springDamper @str_m149 @str_s1 str_K str_Z

@in1 posInput 0.

@out1 posOutput @str_m20
@out2 posOutput @str_m10


@nlp0 nlPluck @in1 @str_m140 nlK nlscale pZ

*/
