declare name    "Plucked Triangle";
declare author  "James Leonard";
declare date    "April 2020";

/* ========= DESCRITPION =============

A triangular mesh (fixed at its corners) excited by a plucking mass
    - inputs: pluck position
    - outputs: two listening points on the triangle
    - controls: triangle mesh stiffness, damping and air friction.
*/


import("stdfaust.lib");

in1 = hslider("Pluck Position", 0, -1, 1, 0.001):si.smoo;

OutGain = 30;

t_M = 1;
t_K = hslider("Mesh Stiffness", 0.1, 0.001, 0.3, 0.0001);
t_Z = hslider("Mesh Damping", 0.001, 0.00001, 0.003, 0.00001);
t_Zo = hslider("Air Friction", 0.00005, 0.00, 0.0001, 0.000001);

model = (
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
	mi.posInput(0.):
	RoutingMassToLink :
	mi.nlPluck(0.5, 0.03, 0.001, 0., 0.),
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
	par(i, nbOut, _):
	RoutingLinkToMass
)~par(i, nbMass, _):
par(i, nbMass, !), par(i, nbOut , _)
with{
	RoutingMassToLink(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29, m30, m31, m32, m33, m34, m35, m36, m37, m38, m39, m40, m41, m42, m43, m44, m45, m46, m47, m48, m49, m50, m51, m52, m53, m54, m55) = /* routed positions */ m55, m37, m0, m1, m1, m2, m2, m3, m3, m4, m4, m5, m5, m6, m6, m7, m7, m8, m8, m9, m10, m11, m11, m12, m12, m13, m13, m14, m14, m15, m15, m16, m16, m17, m17, m18, m19, m20, m20, m21, m21, m22, m22, m23, m23, m24, m24, m25, m25, m26, m27, m28, m28, m29, m29, m30, m30, m31, m31, m32, m32, m33, m34, m35, m35, m36, m36, m37, m37, m38, m38, m39, m40, m41, m41, m42, m42, m43, m43, m44, m45, m46, m46, m47, m47, m48, m49, m50, m50, m51, m52, m53, m0, m10, m1, m11, m2, m12, m3, m13, m4, m14, m5, m15, m6, m16, m7, m17, m8, m18, m10, m19, m11, m20, m12, m21, m13, m22, m14, m23, m15, m24, m16, m25, m17, m26, m19, m27, m20, m28, m21, m29, m22, m30, m23, m31, m24, m32, m25, m33, m27, m34, m28, m35, m29, m36, m30, m37, m31, m38, m32, m39, m34, m40, m35, m41, m36, m42, m37, m43, m38, m44, m40, m45, m41, m46, m42, m47, m43, m48, m45, m49, m46, m50, m47, m51, m49, m52, m50, m53, m52, m54, m1, m10, m2, m11, m3, m12, m4, m13, m5, m14, m6, m15, m7, m16, m8, m17, m9, m18, m11, m19, m12, m20, m13, m21, m14, m22, m15, m23, m16, m24, m17, m25, m18, m26, m20, m27, m21, m28, m22, m29, m23, m30, m24, m31, m25, m32, m26, m33, m28, m34, m29, m35, m30, m36, m31, m37, m32, m38, m33, m39, m35, m40, m36, m41, m37, m42, m38, m43, m39, m44, m41, m45, m42, m46, m43, m47, m44, m48, m46, m49, m47, m50, m48, m51, m50, m52, m51, m53, m53, m54, /* outputs */ m41;
	RoutingLinkToMass(l0_f1, l0_f2, l1_f1, l1_f2, l2_f1, l2_f2, l3_f1, l3_f2, l4_f1, l4_f2, l5_f1, l5_f2, l6_f1, l6_f2, l7_f1, l7_f2, l8_f1, l8_f2, l9_f1, l9_f2, l10_f1, l10_f2, l11_f1, l11_f2, l12_f1, l12_f2, l13_f1, l13_f2, l14_f1, l14_f2, l15_f1, l15_f2, l16_f1, l16_f2, l17_f1, l17_f2, l18_f1, l18_f2, l19_f1, l19_f2, l20_f1, l20_f2, l21_f1, l21_f2, l22_f1, l22_f2, l23_f1, l23_f2, l24_f1, l24_f2, l25_f1, l25_f2, l26_f1, l26_f2, l27_f1, l27_f2, l28_f1, l28_f2, l29_f1, l29_f2, l30_f1, l30_f2, l31_f1, l31_f2, l32_f1, l32_f2, l33_f1, l33_f2, l34_f1, l34_f2, l35_f1, l35_f2, l36_f1, l36_f2, l37_f1, l37_f2, l38_f1, l38_f2, l39_f1, l39_f2, l40_f1, l40_f2, l41_f1, l41_f2, l42_f1, l42_f2, l43_f1, l43_f2, l44_f1, l44_f2, l45_f1, l45_f2, l46_f1, l46_f2, l47_f1, l47_f2, l48_f1, l48_f2, l49_f1, l49_f2, l50_f1, l50_f2, l51_f1, l51_f2, l52_f1, l52_f2, l53_f1, l53_f2, l54_f1, l54_f2, l55_f1, l55_f2, l56_f1, l56_f2, l57_f1, l57_f2, l58_f1, l58_f2, l59_f1, l59_f2, l60_f1, l60_f2, l61_f1, l61_f2, l62_f1, l62_f2, l63_f1, l63_f2, l64_f1, l64_f2, l65_f1, l65_f2, l66_f1, l66_f2, l67_f1, l67_f2, l68_f1, l68_f2, l69_f1, l69_f2, l70_f1, l70_f2, l71_f1, l71_f2, l72_f1, l72_f2, l73_f1, l73_f2, l74_f1, l74_f2, l75_f1, l75_f2, l76_f1, l76_f2, l77_f1, l77_f2, l78_f1, l78_f2, l79_f1, l79_f2, l80_f1, l80_f2, l81_f1, l81_f2, l82_f1, l82_f2, l83_f1, l83_f2, l84_f1, l84_f2, l85_f1, l85_f2, l86_f1, l86_f2, l87_f1, l87_f2, l88_f1, l88_f2, l89_f1, l89_f2, l90_f1, l90_f2, l91_f1, l91_f2, l92_f1, l92_f2, l93_f1, l93_f2, l94_f1, l94_f2, l95_f1, l95_f2, l96_f1, l96_f2, l97_f1, l97_f2, l98_f1, l98_f2, l99_f1, l99_f2, l100_f1, l100_f2, l101_f1, l101_f2, l102_f1, l102_f2, l103_f1, l103_f2, l104_f1, l104_f2, l105_f1, l105_f2, l106_f1, l106_f2, l107_f1, l107_f2, l108_f1, l108_f2, l109_f1, l109_f2, l110_f1, l110_f2, l111_f1, l111_f2, l112_f1, l112_f2, l113_f1, l113_f2, l114_f1, l114_f2, l115_f1, l115_f2, l116_f1, l116_f2, l117_f1, l117_f2, l118_f1, l118_f2, l119_f1, l119_f2, l120_f1, l120_f2, l121_f1, l121_f2, l122_f1, l122_f2, l123_f1, l123_f2, l124_f1, l124_f2, l125_f1, l125_f2, l126_f1, l126_f2, l127_f1, l127_f2, l128_f1, l128_f2, l129_f1, l129_f2, l130_f1, l130_f2, l131_f1, l131_f2, l132_f1, l132_f2, l133_f1, l133_f2, l134_f1, l134_f2, l135_f1, l135_f2, p_out1) = /* routed forces  */ l1_f1 + l46_f1, l1_f2 + l2_f1 + l47_f1 + l91_f1, l2_f2 + l3_f1 + l48_f1 + l92_f1, l3_f2 + l4_f1 + l49_f1 + l93_f1, l4_f2 + l5_f1 + l50_f1 + l94_f1, l5_f2 + l6_f1 + l51_f1 + l95_f1, l6_f2 + l7_f1 + l52_f1 + l96_f1, l7_f2 + l8_f1 + l53_f1 + l97_f1, l8_f2 + l9_f1 + l54_f1 + l98_f1, l9_f2 + l99_f1, l10_f1 + l46_f2 + l55_f1 + l91_f2, l10_f2 + l11_f1 + l47_f2 + l56_f1 + l92_f2 + l100_f1, l11_f2 + l12_f1 + l48_f2 + l57_f1 + l93_f2 + l101_f1, l12_f2 + l13_f1 + l49_f2 + l58_f1 + l94_f2 + l102_f1, l13_f2 + l14_f1 + l50_f2 + l59_f1 + l95_f2 + l103_f1, l14_f2 + l15_f1 + l51_f2 + l60_f1 + l96_f2 + l104_f1, l15_f2 + l16_f1 + l52_f2 + l61_f1 + l97_f2 + l105_f1, l16_f2 + l17_f1 + l53_f2 + l62_f1 + l98_f2 + l106_f1, l17_f2 + l54_f2 + l99_f2 + l107_f1, l18_f1 + l55_f2 + l63_f1 + l100_f2, l18_f2 + l19_f1 + l56_f2 + l64_f1 + l101_f2 + l108_f1, l19_f2 + l20_f1 + l57_f2 + l65_f1 + l102_f2 + l109_f1, l20_f2 + l21_f1 + l58_f2 + l66_f1 + l103_f2 + l110_f1, l21_f2 + l22_f1 + l59_f2 + l67_f1 + l104_f2 + l111_f1, l22_f2 + l23_f1 + l60_f2 + l68_f1 + l105_f2 + l112_f1, l23_f2 + l24_f1 + l61_f2 + l69_f1 + l106_f2 + l113_f1, l24_f2 + l62_f2 + l107_f2 + l114_f1, l25_f1 + l63_f2 + l70_f1 + l108_f2, l25_f2 + l26_f1 + l64_f2 + l71_f1 + l109_f2 + l115_f1, l26_f2 + l27_f1 + l65_f2 + l72_f1 + l110_f2 + l116_f1, l27_f2 + l28_f1 + l66_f2 + l73_f1 + l111_f2 + l117_f1, l28_f2 + l29_f1 + l67_f2 + l74_f1 + l112_f2 + l118_f1, l29_f2 + l30_f1 + l68_f2 + l75_f1 + l113_f2 + l119_f1, l30_f2 + l69_f2 + l114_f2 + l120_f1, l31_f1 + l70_f2 + l76_f1 + l115_f2, l31_f2 + l32_f1 + l71_f2 + l77_f1 + l116_f2 + l121_f1, l32_f2 + l33_f1 + l72_f2 + l78_f1 + l117_f2 + l122_f1, l0_f2 + l33_f2 + l34_f1 + l73_f2 + l79_f1 + l118_f2 + l123_f1, l34_f2 + l35_f1 + l74_f2 + l80_f1 + l119_f2 + l124_f1, l35_f2 + l75_f2 + l120_f2 + l125_f1, l36_f1 + l76_f2 + l81_f1 + l121_f2, l36_f2 + l37_f1 + l77_f2 + l82_f1 + l122_f2 + l126_f1, l37_f2 + l38_f1 + l78_f2 + l83_f1 + l123_f2 + l127_f1, l38_f2 + l39_f1 + l79_f2 + l84_f1 + l124_f2 + l128_f1, l39_f2 + l80_f2 + l125_f2 + l129_f1, l40_f1 + l81_f2 + l85_f1 + l126_f2, l40_f2 + l41_f1 + l82_f2 + l86_f1 + l127_f2 + l130_f1, l41_f2 + l42_f1 + l83_f2 + l87_f1 + l128_f2 + l131_f1, l42_f2 + l84_f2 + l129_f2 + l132_f1, l43_f1 + l85_f2 + l88_f1 + l130_f2, l43_f2 + l44_f1 + l86_f2 + l89_f1 + l131_f2 + l133_f1, l44_f2 + l87_f2 + l132_f2 + l134_f1, l45_f1 + l88_f2 + l90_f1 + l133_f2, l45_f2 + l89_f2 + l134_f2 + l135_f1, l90_f2 + l135_f2, l0_f1, /* pass-through */ p_out1;
	nbMass = 56;
	nbOut = 1;
};
process = in1 : model:*(OutGain);



/*
========= MIMS SCRIPT USED FOR MODEL GENERATION =============


# A plucked triangular mesh model (fixed at corners)
# Script author: James Leonard


@t_M param 1
@t_K param 0.1
@t_Z param 0.001
@t_Zo param 0.00005

@in1 posInput 0.

@pl nlPluck @in1 @t_m4_3 0.5 0.03 0.001


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


@out1 posOutput @t_m5_1

*/