declare name    "Bowed String";
declare author  "James Leonard";
declare date    "April 2020";

/* ========= DESCRITPION =============

A simple bowed string model
    - inputs: bow position (move it slowly to yield self-sustained oscillations!).
    - outputs: two listening points on the string.
    - controls: bow pressure and string stiffness.
*/

import("stdfaust.lib");

in1 = hslider("Bow Position", 0, -1, 1, 0.001):si.smoo:si.smoo:si.smoo; 	// nice and smooth position signal

OutGain = 150.;

low_M = 1.0;
low_K = hslider("String Stiffness",0.3,0.001,0.7,0.0001) : si.smoo;
low_Z = 0.001;
nlZ = hslider("Bow Pressure",0.3,0.001,0.5,0.0001) : si.smoo;
nlscale = 0.00005;

model = (
	mi.ground(0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.mass(low_M, 0, 0., 0.),
	mi.ground(0.),
	mi.posInput(1.):
	RoutingMassToLink :
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.springDamper(low_K, low_Z, 0., 0.),
	mi.nlBow(nlZ, nlscale, 0, 1., 0.),
	par(i, nbOut, _):
	RoutingLinkToMass
)~par(i, nbMass, _):
par(i, nbMass, !), par(i, nbOut , _)
with{
	RoutingMassToLink(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29, m30, m31, m32, m33, m34, m35, m36, m37, m38, m39, m40, m41, m42, m43, m44, m45, m46, m47, m48, m49, m50, m51, m52, m53, m54, m55, m56, m57, m58, m59, m60, m61, m62, m63, m64, m65, m66, m67, m68, m69, m70, m71, m72, m73, m74, m75, m76, m77, m78, m79, m80, m81, m82, m83, m84, m85, m86, m87, m88, m89, m90, m91, m92, m93, m94, m95, m96, m97, m98, m99, m100, m101, m102, m103, m104, m105, m106, m107, m108, m109, m110, m111, m112, m113, m114, m115, m116, m117, m118, m119, m120, m121, m122, m123, m124, m125, m126, m127, m128, m129, m130, m131, m132, m133, m134, m135, m136, m137, m138, m139, m140, m141, m142, m143, m144, m145, m146, m147, m148, m149, m150, m151, m152) = /* routed positions */ m0, m1, m1, m2, m2, m3, m3, m4, m4, m5, m5, m6, m6, m7, m7, m8, m8, m9, m9, m10, m10, m11, m11, m12, m12, m13, m13, m14, m14, m15, m15, m16, m16, m17, m17, m18, m18, m19, m19, m20, m20, m21, m21, m22, m22, m23, m23, m24, m24, m25, m25, m26, m26, m27, m27, m28, m28, m29, m29, m30, m30, m31, m31, m32, m32, m33, m33, m34, m34, m35, m35, m36, m36, m37, m37, m38, m38, m39, m39, m40, m40, m41, m41, m42, m42, m43, m43, m44, m44, m45, m45, m46, m46, m47, m47, m48, m48, m49, m49, m50, m50, m51, m51, m52, m52, m53, m53, m54, m54, m55, m55, m56, m56, m57, m57, m58, m58, m59, m59, m60, m60, m61, m61, m62, m62, m63, m63, m64, m64, m65, m65, m66, m66, m67, m67, m68, m68, m69, m69, m70, m70, m71, m71, m72, m72, m73, m73, m74, m74, m75, m75, m76, m76, m77, m77, m78, m78, m79, m79, m80, m80, m81, m81, m82, m82, m83, m83, m84, m84, m85, m85, m86, m86, m87, m87, m88, m88, m89, m89, m90, m90, m91, m91, m92, m92, m93, m93, m94, m94, m95, m95, m96, m96, m97, m97, m98, m98, m99, m99, m100, m100, m101, m101, m102, m102, m103, m103, m104, m104, m105, m105, m106, m106, m107, m107, m108, m108, m109, m109, m110, m110, m111, m111, m112, m112, m113, m113, m114, m114, m115, m115, m116, m116, m117, m117, m118, m118, m119, m119, m120, m120, m121, m121, m122, m122, m123, m123, m124, m124, m125, m125, m126, m126, m127, m127, m128, m128, m129, m129, m130, m130, m131, m131, m132, m132, m133, m133, m134, m134, m135, m135, m136, m136, m137, m137, m138, m138, m139, m139, m140, m140, m141, m141, m142, m142, m143, m143, m144, m144, m145, m145, m146, m146, m147, m147, m148, m148, m149, m149, m150, m150, m151, m152, m144, /* outputs */ m31, m41;
	RoutingLinkToMass(l0_f1, l0_f2, l1_f1, l1_f2, l2_f1, l2_f2, l3_f1, l3_f2, l4_f1, l4_f2, l5_f1, l5_f2, l6_f1, l6_f2, l7_f1, l7_f2, l8_f1, l8_f2, l9_f1, l9_f2, l10_f1, l10_f2, l11_f1, l11_f2, l12_f1, l12_f2, l13_f1, l13_f2, l14_f1, l14_f2, l15_f1, l15_f2, l16_f1, l16_f2, l17_f1, l17_f2, l18_f1, l18_f2, l19_f1, l19_f2, l20_f1, l20_f2, l21_f1, l21_f2, l22_f1, l22_f2, l23_f1, l23_f2, l24_f1, l24_f2, l25_f1, l25_f2, l26_f1, l26_f2, l27_f1, l27_f2, l28_f1, l28_f2, l29_f1, l29_f2, l30_f1, l30_f2, l31_f1, l31_f2, l32_f1, l32_f2, l33_f1, l33_f2, l34_f1, l34_f2, l35_f1, l35_f2, l36_f1, l36_f2, l37_f1, l37_f2, l38_f1, l38_f2, l39_f1, l39_f2, l40_f1, l40_f2, l41_f1, l41_f2, l42_f1, l42_f2, l43_f1, l43_f2, l44_f1, l44_f2, l45_f1, l45_f2, l46_f1, l46_f2, l47_f1, l47_f2, l48_f1, l48_f2, l49_f1, l49_f2, l50_f1, l50_f2, l51_f1, l51_f2, l52_f1, l52_f2, l53_f1, l53_f2, l54_f1, l54_f2, l55_f1, l55_f2, l56_f1, l56_f2, l57_f1, l57_f2, l58_f1, l58_f2, l59_f1, l59_f2, l60_f1, l60_f2, l61_f1, l61_f2, l62_f1, l62_f2, l63_f1, l63_f2, l64_f1, l64_f2, l65_f1, l65_f2, l66_f1, l66_f2, l67_f1, l67_f2, l68_f1, l68_f2, l69_f1, l69_f2, l70_f1, l70_f2, l71_f1, l71_f2, l72_f1, l72_f2, l73_f1, l73_f2, l74_f1, l74_f2, l75_f1, l75_f2, l76_f1, l76_f2, l77_f1, l77_f2, l78_f1, l78_f2, l79_f1, l79_f2, l80_f1, l80_f2, l81_f1, l81_f2, l82_f1, l82_f2, l83_f1, l83_f2, l84_f1, l84_f2, l85_f1, l85_f2, l86_f1, l86_f2, l87_f1, l87_f2, l88_f1, l88_f2, l89_f1, l89_f2, l90_f1, l90_f2, l91_f1, l91_f2, l92_f1, l92_f2, l93_f1, l93_f2, l94_f1, l94_f2, l95_f1, l95_f2, l96_f1, l96_f2, l97_f1, l97_f2, l98_f1, l98_f2, l99_f1, l99_f2, l100_f1, l100_f2, l101_f1, l101_f2, l102_f1, l102_f2, l103_f1, l103_f2, l104_f1, l104_f2, l105_f1, l105_f2, l106_f1, l106_f2, l107_f1, l107_f2, l108_f1, l108_f2, l109_f1, l109_f2, l110_f1, l110_f2, l111_f1, l111_f2, l112_f1, l112_f2, l113_f1, l113_f2, l114_f1, l114_f2, l115_f1, l115_f2, l116_f1, l116_f2, l117_f1, l117_f2, l118_f1, l118_f2, l119_f1, l119_f2, l120_f1, l120_f2, l121_f1, l121_f2, l122_f1, l122_f2, l123_f1, l123_f2, l124_f1, l124_f2, l125_f1, l125_f2, l126_f1, l126_f2, l127_f1, l127_f2, l128_f1, l128_f2, l129_f1, l129_f2, l130_f1, l130_f2, l131_f1, l131_f2, l132_f1, l132_f2, l133_f1, l133_f2, l134_f1, l134_f2, l135_f1, l135_f2, l136_f1, l136_f2, l137_f1, l137_f2, l138_f1, l138_f2, l139_f1, l139_f2, l140_f1, l140_f2, l141_f1, l141_f2, l142_f1, l142_f2, l143_f1, l143_f2, l144_f1, l144_f2, l145_f1, l145_f2, l146_f1, l146_f2, l147_f1, l147_f2, l148_f1, l148_f2, l149_f1, l149_f2, l150_f1, l150_f2, l151_f1, l151_f2, p_out1, p_out2) = /* routed forces  */ l0_f1, l0_f2 + l1_f1, l1_f2 + l2_f1, l2_f2 + l3_f1, l3_f2 + l4_f1, l4_f2 + l5_f1, l5_f2 + l6_f1, l6_f2 + l7_f1, l7_f2 + l8_f1, l8_f2 + l9_f1, l9_f2 + l10_f1, l10_f2 + l11_f1, l11_f2 + l12_f1, l12_f2 + l13_f1, l13_f2 + l14_f1, l14_f2 + l15_f1, l15_f2 + l16_f1, l16_f2 + l17_f1, l17_f2 + l18_f1, l18_f2 + l19_f1, l19_f2 + l20_f1, l20_f2 + l21_f1, l21_f2 + l22_f1, l22_f2 + l23_f1, l23_f2 + l24_f1, l24_f2 + l25_f1, l25_f2 + l26_f1, l26_f2 + l27_f1, l27_f2 + l28_f1, l28_f2 + l29_f1, l29_f2 + l30_f1, l30_f2 + l31_f1, l31_f2 + l32_f1, l32_f2 + l33_f1, l33_f2 + l34_f1, l34_f2 + l35_f1, l35_f2 + l36_f1, l36_f2 + l37_f1, l37_f2 + l38_f1, l38_f2 + l39_f1, l39_f2 + l40_f1, l40_f2 + l41_f1, l41_f2 + l42_f1, l42_f2 + l43_f1, l43_f2 + l44_f1, l44_f2 + l45_f1, l45_f2 + l46_f1, l46_f2 + l47_f1, l47_f2 + l48_f1, l48_f2 + l49_f1, l49_f2 + l50_f1, l50_f2 + l51_f1, l51_f2 + l52_f1, l52_f2 + l53_f1, l53_f2 + l54_f1, l54_f2 + l55_f1, l55_f2 + l56_f1, l56_f2 + l57_f1, l57_f2 + l58_f1, l58_f2 + l59_f1, l59_f2 + l60_f1, l60_f2 + l61_f1, l61_f2 + l62_f1, l62_f2 + l63_f1, l63_f2 + l64_f1, l64_f2 + l65_f1, l65_f2 + l66_f1, l66_f2 + l67_f1, l67_f2 + l68_f1, l68_f2 + l69_f1, l69_f2 + l70_f1, l70_f2 + l71_f1, l71_f2 + l72_f1, l72_f2 + l73_f1, l73_f2 + l74_f1, l74_f2 + l75_f1, l75_f2 + l76_f1, l76_f2 + l77_f1, l77_f2 + l78_f1, l78_f2 + l79_f1, l79_f2 + l80_f1, l80_f2 + l81_f1, l81_f2 + l82_f1, l82_f2 + l83_f1, l83_f2 + l84_f1, l84_f2 + l85_f1, l85_f2 + l86_f1, l86_f2 + l87_f1, l87_f2 + l88_f1, l88_f2 + l89_f1, l89_f2 + l90_f1, l90_f2 + l91_f1, l91_f2 + l92_f1, l92_f2 + l93_f1, l93_f2 + l94_f1, l94_f2 + l95_f1, l95_f2 + l96_f1, l96_f2 + l97_f1, l97_f2 + l98_f1, l98_f2 + l99_f1, l99_f2 + l100_f1, l100_f2 + l101_f1, l101_f2 + l102_f1, l102_f2 + l103_f1, l103_f2 + l104_f1, l104_f2 + l105_f1, l105_f2 + l106_f1, l106_f2 + l107_f1, l107_f2 + l108_f1, l108_f2 + l109_f1, l109_f2 + l110_f1, l110_f2 + l111_f1, l111_f2 + l112_f1, l112_f2 + l113_f1, l113_f2 + l114_f1, l114_f2 + l115_f1, l115_f2 + l116_f1, l116_f2 + l117_f1, l117_f2 + l118_f1, l118_f2 + l119_f1, l119_f2 + l120_f1, l120_f2 + l121_f1, l121_f2 + l122_f1, l122_f2 + l123_f1, l123_f2 + l124_f1, l124_f2 + l125_f1, l125_f2 + l126_f1, l126_f2 + l127_f1, l127_f2 + l128_f1, l128_f2 + l129_f1, l129_f2 + l130_f1, l130_f2 + l131_f1, l131_f2 + l132_f1, l132_f2 + l133_f1, l133_f2 + l134_f1, l134_f2 + l135_f1, l135_f2 + l136_f1, l136_f2 + l137_f1, l137_f2 + l138_f1, l138_f2 + l139_f1, l139_f2 + l140_f1, l140_f2 + l141_f1, l141_f2 + l142_f1, l142_f2 + l143_f1, l143_f2 + l144_f1 + l151_f2, l144_f2 + l145_f1, l145_f2 + l146_f1, l146_f2 + l147_f1, l147_f2 + l148_f1, l148_f2 + l149_f1, l149_f2 + l150_f1, l150_f2, l151_f1, /* pass-through */ p_out1, p_out2;
	nbMass = 153;
	nbOut = 2;
};
process = in1 : model:*(OutGain), *(OutGain);


/*
========= MIMS SCRIPT USED FOR MODEL GENERATION =============

@low_M param  1.0
@low_K param  0.3
@low_Z param 0.001


@nlZ param 0.08                                    
@nlscale param 0.00005

@low_s0 ground 0.
@low_m0 mass low_M 0. 0.
@low_m1 mass low_M 0. 0.
@low_m2 mass low_M 0. 0.
@low_m3 mass low_M 0. 0.
@low_m4 mass low_M 0. 0.
@low_m5 mass low_M 0. 0.
@low_m6 mass low_M 0. 0.
@low_m7 mass low_M 0. 0.
@low_m8 mass low_M 0. 0.
@low_m9 mass low_M 0. 0.
@low_m10 mass low_M 0. 0.
@low_m11 mass low_M 0. 0.
@low_m12 mass low_M 0. 0.
@low_m13 mass low_M 0. 0.
@low_m14 mass low_M 0. 0.
@low_m15 mass low_M 0. 0.
@low_m16 mass low_M 0. 0.
@low_m17 mass low_M 0. 0.
@low_m18 mass low_M 0. 0.
@low_m19 mass low_M 0. 0.
@low_m20 mass low_M 0. 0.
@low_m21 mass low_M 0. 0.
@low_m22 mass low_M 0. 0.
@low_m23 mass low_M 0. 0.
@low_m24 mass low_M 0. 0.
@low_m25 mass low_M 0. 0.
@low_m26 mass low_M 0. 0.
@low_m27 mass low_M 0. 0.
@low_m28 mass low_M 0. 0.
@low_m29 mass low_M 0. 0.
@low_m30 mass low_M 0. 0.
@low_m31 mass low_M 0. 0.
@low_m32 mass low_M 0. 0.
@low_m33 mass low_M 0. 0.
@low_m34 mass low_M 0. 0.
@low_m35 mass low_M 0. 0.
@low_m36 mass low_M 0. 0.
@low_m37 mass low_M 0. 0.
@low_m38 mass low_M 0. 0.
@low_m39 mass low_M 0. 0.
@low_m40 mass low_M 0. 0.
@low_m41 mass low_M 0. 0.
@low_m42 mass low_M 0. 0.
@low_m43 mass low_M 0. 0.
@low_m44 mass low_M 0. 0.
@low_m45 mass low_M 0. 0.
@low_m46 mass low_M 0. 0.
@low_m47 mass low_M 0. 0.
@low_m48 mass low_M 0. 0.
@low_m49 mass low_M 0. 0.
@low_m50 mass low_M 0. 0.
@low_m51 mass low_M 0. 0.
@low_m52 mass low_M 0. 0.
@low_m53 mass low_M 0. 0.
@low_m54 mass low_M 0. 0.
@low_m55 mass low_M 0. 0.
@low_m56 mass low_M 0. 0.
@low_m57 mass low_M 0. 0.
@low_m58 mass low_M 0. 0.
@low_m59 mass low_M 0. 0.
@low_m60 mass low_M 0. 0.
@low_m61 mass low_M 0. 0.
@low_m62 mass low_M 0. 0.
@low_m63 mass low_M 0. 0.
@low_m64 mass low_M 0. 0.
@low_m65 mass low_M 0. 0.
@low_m66 mass low_M 0. 0.
@low_m67 mass low_M 0. 0.
@low_m68 mass low_M 0. 0.
@low_m69 mass low_M 0. 0.
@low_m70 mass low_M 0. 0.
@low_m71 mass low_M 0. 0.
@low_m72 mass low_M 0. 0.
@low_m73 mass low_M 0. 0.
@low_m74 mass low_M 0. 0.
@low_m75 mass low_M 0. 0.
@low_m76 mass low_M 0. 0.
@low_m77 mass low_M 0. 0.
@low_m78 mass low_M 0. 0.
@low_m79 mass low_M 0. 0.
@low_m80 mass low_M 0. 0.
@low_m81 mass low_M 0. 0.
@low_m82 mass low_M 0. 0.
@low_m83 mass low_M 0. 0.
@low_m84 mass low_M 0. 0.
@low_m85 mass low_M 0. 0.
@low_m86 mass low_M 0. 0.
@low_m87 mass low_M 0. 0.
@low_m88 mass low_M 0. 0.
@low_m89 mass low_M 0. 0.
@low_m90 mass low_M 0. 0.
@low_m91 mass low_M 0. 0.
@low_m92 mass low_M 0. 0.
@low_m93 mass low_M 0. 0.
@low_m94 mass low_M 0. 0.
@low_m95 mass low_M 0. 0.
@low_m96 mass low_M 0. 0.
@low_m97 mass low_M 0. 0.
@low_m98 mass low_M 0. 0.
@low_m99 mass low_M 0. 0.
@low_m100 mass low_M 0. 0.
@low_m101 mass low_M 0. 0.
@low_m102 mass low_M 0. 0.
@low_m103 mass low_M 0. 0.
@low_m104 mass low_M 0. 0.
@low_m105 mass low_M 0. 0.
@low_m106 mass low_M 0. 0.
@low_m107 mass low_M 0. 0.
@low_m108 mass low_M 0. 0.
@low_m109 mass low_M 0. 0.
@low_m110 mass low_M 0. 0.
@low_m111 mass low_M 0. 0.
@low_m112 mass low_M 0. 0.
@low_m113 mass low_M 0. 0.
@low_m114 mass low_M 0. 0.
@low_m115 mass low_M 0. 0.
@low_m116 mass low_M 0. 0.
@low_m117 mass low_M 0. 0.
@low_m118 mass low_M 0. 0.
@low_m119 mass low_M 0. 0.
@low_m120 mass low_M 0. 0.
@low_m121 mass low_M 0. 0.
@low_m122 mass low_M 0. 0.
@low_m123 mass low_M 0. 0.
@low_m124 mass low_M 0. 0.
@low_m125 mass low_M 0. 0.
@low_m126 mass low_M 0. 0.
@low_m127 mass low_M 0. 0.
@low_m128 mass low_M 0. 0.
@low_m129 mass low_M 0. 0.
@low_m130 mass low_M 0. 0.
@low_m131 mass low_M 0. 0.
@low_m132 mass low_M 0. 0.
@low_m133 mass low_M 0. 0.
@low_m134 mass low_M 0. 0.
@low_m135 mass low_M 0. 0.
@low_m136 mass low_M 0. 0.
@low_m137 mass low_M 0. 0.
@low_m138 mass low_M 0. 0.
@low_m139 mass low_M 0. 0.
@low_m140 mass low_M 0. 0.
@low_m141 mass low_M 0. 0.
@low_m142 mass low_M 0. 0.
@low_m143 mass low_M 0. 0.
@low_m144 mass low_M 0. 0.
@low_m145 mass low_M 0. 0.
@low_m146 mass low_M 0. 0.
@low_m147 mass low_M 0. 0.
@low_m148 mass low_M 0. 0.
@low_m149 mass low_M 0. 0.
@low_s1 ground 0.

@low_r0 springDamper @low_s0 @low_m0 low_K low_Z
@low_r1 springDamper @low_m0 @low_m1 low_K low_Z
@low_r2 springDamper @low_m1 @low_m2 low_K low_Z
@low_r3 springDamper @low_m2 @low_m3 low_K low_Z
@low_r4 springDamper @low_m3 @low_m4 low_K low_Z
@low_r5 springDamper @low_m4 @low_m5 low_K low_Z
@low_r6 springDamper @low_m5 @low_m6 low_K low_Z
@low_r7 springDamper @low_m6 @low_m7 low_K low_Z
@low_r8 springDamper @low_m7 @low_m8 low_K low_Z
@low_r9 springDamper @low_m8 @low_m9 low_K low_Z
@low_r10 springDamper @low_m9 @low_m10 low_K low_Z
@low_r11 springDamper @low_m10 @low_m11 low_K low_Z
@low_r12 springDamper @low_m11 @low_m12 low_K low_Z
@low_r13 springDamper @low_m12 @low_m13 low_K low_Z
@low_r14 springDamper @low_m13 @low_m14 low_K low_Z
@low_r15 springDamper @low_m14 @low_m15 low_K low_Z
@low_r16 springDamper @low_m15 @low_m16 low_K low_Z
@low_r17 springDamper @low_m16 @low_m17 low_K low_Z
@low_r18 springDamper @low_m17 @low_m18 low_K low_Z
@low_r19 springDamper @low_m18 @low_m19 low_K low_Z
@low_r20 springDamper @low_m19 @low_m20 low_K low_Z
@low_r21 springDamper @low_m20 @low_m21 low_K low_Z
@low_r22 springDamper @low_m21 @low_m22 low_K low_Z
@low_r23 springDamper @low_m22 @low_m23 low_K low_Z
@low_r24 springDamper @low_m23 @low_m24 low_K low_Z
@low_r25 springDamper @low_m24 @low_m25 low_K low_Z
@low_r26 springDamper @low_m25 @low_m26 low_K low_Z
@low_r27 springDamper @low_m26 @low_m27 low_K low_Z
@low_r28 springDamper @low_m27 @low_m28 low_K low_Z
@low_r29 springDamper @low_m28 @low_m29 low_K low_Z
@low_r30 springDamper @low_m29 @low_m30 low_K low_Z
@low_r31 springDamper @low_m30 @low_m31 low_K low_Z
@low_r32 springDamper @low_m31 @low_m32 low_K low_Z
@low_r33 springDamper @low_m32 @low_m33 low_K low_Z
@low_r34 springDamper @low_m33 @low_m34 low_K low_Z
@low_r35 springDamper @low_m34 @low_m35 low_K low_Z
@low_r36 springDamper @low_m35 @low_m36 low_K low_Z
@low_r37 springDamper @low_m36 @low_m37 low_K low_Z
@low_r38 springDamper @low_m37 @low_m38 low_K low_Z
@low_r39 springDamper @low_m38 @low_m39 low_K low_Z
@low_r40 springDamper @low_m39 @low_m40 low_K low_Z
@low_r41 springDamper @low_m40 @low_m41 low_K low_Z
@low_r42 springDamper @low_m41 @low_m42 low_K low_Z
@low_r43 springDamper @low_m42 @low_m43 low_K low_Z
@low_r44 springDamper @low_m43 @low_m44 low_K low_Z
@low_r45 springDamper @low_m44 @low_m45 low_K low_Z
@low_r46 springDamper @low_m45 @low_m46 low_K low_Z
@low_r47 springDamper @low_m46 @low_m47 low_K low_Z
@low_r48 springDamper @low_m47 @low_m48 low_K low_Z
@low_r49 springDamper @low_m48 @low_m49 low_K low_Z
@low_r50 springDamper @low_m49 @low_m50 low_K low_Z
@low_r51 springDamper @low_m50 @low_m51 low_K low_Z
@low_r52 springDamper @low_m51 @low_m52 low_K low_Z
@low_r53 springDamper @low_m52 @low_m53 low_K low_Z
@low_r54 springDamper @low_m53 @low_m54 low_K low_Z
@low_r55 springDamper @low_m54 @low_m55 low_K low_Z
@low_r56 springDamper @low_m55 @low_m56 low_K low_Z
@low_r57 springDamper @low_m56 @low_m57 low_K low_Z
@low_r58 springDamper @low_m57 @low_m58 low_K low_Z
@low_r59 springDamper @low_m58 @low_m59 low_K low_Z
@low_r60 springDamper @low_m59 @low_m60 low_K low_Z
@low_r61 springDamper @low_m60 @low_m61 low_K low_Z
@low_r62 springDamper @low_m61 @low_m62 low_K low_Z
@low_r63 springDamper @low_m62 @low_m63 low_K low_Z
@low_r64 springDamper @low_m63 @low_m64 low_K low_Z
@low_r65 springDamper @low_m64 @low_m65 low_K low_Z
@low_r66 springDamper @low_m65 @low_m66 low_K low_Z
@low_r67 springDamper @low_m66 @low_m67 low_K low_Z
@low_r68 springDamper @low_m67 @low_m68 low_K low_Z
@low_r69 springDamper @low_m68 @low_m69 low_K low_Z
@low_r70 springDamper @low_m69 @low_m70 low_K low_Z
@low_r71 springDamper @low_m70 @low_m71 low_K low_Z
@low_r72 springDamper @low_m71 @low_m72 low_K low_Z
@low_r73 springDamper @low_m72 @low_m73 low_K low_Z
@low_r74 springDamper @low_m73 @low_m74 low_K low_Z
@low_r75 springDamper @low_m74 @low_m75 low_K low_Z
@low_r76 springDamper @low_m75 @low_m76 low_K low_Z
@low_r77 springDamper @low_m76 @low_m77 low_K low_Z
@low_r78 springDamper @low_m77 @low_m78 low_K low_Z
@low_r79 springDamper @low_m78 @low_m79 low_K low_Z
@low_r80 springDamper @low_m79 @low_m80 low_K low_Z
@low_r81 springDamper @low_m80 @low_m81 low_K low_Z
@low_r82 springDamper @low_m81 @low_m82 low_K low_Z
@low_r83 springDamper @low_m82 @low_m83 low_K low_Z
@low_r84 springDamper @low_m83 @low_m84 low_K low_Z
@low_r85 springDamper @low_m84 @low_m85 low_K low_Z
@low_r86 springDamper @low_m85 @low_m86 low_K low_Z
@low_r87 springDamper @low_m86 @low_m87 low_K low_Z
@low_r88 springDamper @low_m87 @low_m88 low_K low_Z
@low_r89 springDamper @low_m88 @low_m89 low_K low_Z
@low_r90 springDamper @low_m89 @low_m90 low_K low_Z
@low_r91 springDamper @low_m90 @low_m91 low_K low_Z
@low_r92 springDamper @low_m91 @low_m92 low_K low_Z
@low_r93 springDamper @low_m92 @low_m93 low_K low_Z
@low_r94 springDamper @low_m93 @low_m94 low_K low_Z
@low_r95 springDamper @low_m94 @low_m95 low_K low_Z
@low_r96 springDamper @low_m95 @low_m96 low_K low_Z
@low_r97 springDamper @low_m96 @low_m97 low_K low_Z
@low_r98 springDamper @low_m97 @low_m98 low_K low_Z
@low_r99 springDamper @low_m98 @low_m99 low_K low_Z
@low_r100 springDamper @low_m99 @low_m100 low_K low_Z
@low_r101 springDamper @low_m100 @low_m101 low_K low_Z
@low_r102 springDamper @low_m101 @low_m102 low_K low_Z
@low_r103 springDamper @low_m102 @low_m103 low_K low_Z
@low_r104 springDamper @low_m103 @low_m104 low_K low_Z
@low_r105 springDamper @low_m104 @low_m105 low_K low_Z
@low_r106 springDamper @low_m105 @low_m106 low_K low_Z
@low_r107 springDamper @low_m106 @low_m107 low_K low_Z
@low_r108 springDamper @low_m107 @low_m108 low_K low_Z
@low_r109 springDamper @low_m108 @low_m109 low_K low_Z
@low_r110 springDamper @low_m109 @low_m110 low_K low_Z
@low_r111 springDamper @low_m110 @low_m111 low_K low_Z
@low_r112 springDamper @low_m111 @low_m112 low_K low_Z
@low_r113 springDamper @low_m112 @low_m113 low_K low_Z
@low_r114 springDamper @low_m113 @low_m114 low_K low_Z
@low_r115 springDamper @low_m114 @low_m115 low_K low_Z
@low_r116 springDamper @low_m115 @low_m116 low_K low_Z
@low_r117 springDamper @low_m116 @low_m117 low_K low_Z
@low_r118 springDamper @low_m117 @low_m118 low_K low_Z
@low_r119 springDamper @low_m118 @low_m119 low_K low_Z
@low_r120 springDamper @low_m119 @low_m120 low_K low_Z
@low_r121 springDamper @low_m120 @low_m121 low_K low_Z
@low_r122 springDamper @low_m121 @low_m122 low_K low_Z
@low_r123 springDamper @low_m122 @low_m123 low_K low_Z
@low_r124 springDamper @low_m123 @low_m124 low_K low_Z
@low_r125 springDamper @low_m124 @low_m125 low_K low_Z
@low_r126 springDamper @low_m125 @low_m126 low_K low_Z
@low_r127 springDamper @low_m126 @low_m127 low_K low_Z
@low_r128 springDamper @low_m127 @low_m128 low_K low_Z
@low_r129 springDamper @low_m128 @low_m129 low_K low_Z
@low_r130 springDamper @low_m129 @low_m130 low_K low_Z
@low_r131 springDamper @low_m130 @low_m131 low_K low_Z
@low_r132 springDamper @low_m131 @low_m132 low_K low_Z
@low_r133 springDamper @low_m132 @low_m133 low_K low_Z
@low_r134 springDamper @low_m133 @low_m134 low_K low_Z
@low_r135 springDamper @low_m134 @low_m135 low_K low_Z
@low_r136 springDamper @low_m135 @low_m136 low_K low_Z
@low_r137 springDamper @low_m136 @low_m137 low_K low_Z
@low_r138 springDamper @low_m137 @low_m138 low_K low_Z
@low_r139 springDamper @low_m138 @low_m139 low_K low_Z
@low_r140 springDamper @low_m139 @low_m140 low_K low_Z
@low_r141 springDamper @low_m140 @low_m141 low_K low_Z
@low_r142 springDamper @low_m141 @low_m142 low_K low_Z
@low_r143 springDamper @low_m142 @low_m143 low_K low_Z
@low_r144 springDamper @low_m143 @low_m144 low_K low_Z
@low_r145 springDamper @low_m144 @low_m145 low_K low_Z
@low_r146 springDamper @low_m145 @low_m146 low_K low_Z
@low_r147 springDamper @low_m146 @low_m147 low_K low_Z
@low_r148 springDamper @low_m147 @low_m148 low_K low_Z
@low_r149 springDamper @low_m148 @low_m149 low_K low_Z
@low_r150 springDamper @low_m149 @low_s1 low_K low_Z

@in1 posInput 1.

@out1 posOutput @low_m30
@out2 posOutput @low_m40


@nlb0 nlBow @in1 @low_m143 nlZ nlscale



*/