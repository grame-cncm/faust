declare name    "Polyphonic Triangles";
declare author  "James Leonard";
declare date    "April 2020";

/* ========= DESCRITPION =============

A series of small triangle structures are excited by force impulses.
    - inputs: force impulse.
    - outputs: one mass of the triangle
    - controls: triangle stiffness, damping.

Note: use this model with Poly mode to control voices dynamically according to MIDI input.
*/


declare options "[midi:on][nvoices:12]";
import("stdfaust.lib");

gate = button("gate"):ba.impulsify;
in1 = gate * 0.1; 
freq = hslider("freq",200,50,1000,0.01);
gain = hslider("gain",0.5,0,1,0.01);
m_K = 0.001 * freq * hslider("Model Stiffness", 0.1, 0.0001, 0.3, 0.00001) ;
m_Z = hslider("Model Damping", 0.0001, 0.00001, 0.001, 0.000001) ;

OutGain = 0.3;

model = (
	mi.ground(0.),
	mi.mass(1., 0, 0., 0.),
	mi.mass(1., 0, 0., 0.),
	mi.mass(1., 0, 0., 0.),
	par(i, nbFrcIn,_):
	RoutingMassToLink ,
	par(i, nbFrcIn,_):
	mi.springDamper(0.05, 0.01, 0., 0.),
	mi.springDamper(m_K, m_Z, 0., 0.),
	mi.springDamper(m_K, m_Z, 0., 0.),
	mi.springDamper(m_K, m_Z, 0., 0.),
	par(i, nbOut+nbFrcIn, _):
	RoutingLinkToMass
)~par(i, nbMass, _):
par(i, nbMass, !), par(i, nbOut , _)
with{
	RoutingMassToLink(m0, m1, m2, m3) = /* routed positions */ m0, m1, m1, m2, m2, m3, m3, m1, /* outputs */ m3;
	RoutingLinkToMass(l0_f1, l0_f2, l1_f1, l1_f2, l2_f1, l2_f2, l3_f1, l3_f2, p_out1, f_in1) = /* routed forces  */ l0_f1, l0_f2 + l1_f1 + l3_f2, f_in1 + l1_f2 + l2_f1, l2_f2 + l3_f1, /* pass-through */ p_out1;
	nbMass = 4;
	nbFrcIn = 1;
	nbOut = 1;
};
process = in1 : model:*(OutGain);


/*
========= MIMS SCRIPT USED FOR MODEL GENERATION =============

# Define global parameter attributes
@m_K param 0.1
@m_Z param 0.001

# Create material points
@m_s0 ground 0.
@m_m0 mass 1. 0. 0.
@m_m1 mass 1. 0. 0.
@m_m2 mass 1. 0. 0.

# Create and connect interaction modules
@m_r0 springDamper @m_s0 @m_m0 0.05 0.01
@m_r1 springDamper @m_m0 @m_m1 m_K m_Z
@m_r2 springDamper @m_m1 @m_m2 m_K m_Z
@m_r3 springDamper @m_m2 @m_m0 m_K m_Z

# Force input, applied to m1
@in1 frcInput @m_m1

# Position output, observed on m2
@out1 posOutput @m_m2

*/