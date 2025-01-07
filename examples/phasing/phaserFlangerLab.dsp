declare name "phaserFlangerLab";

import("pkg:faust/faust/stdfaust.lib@1.0.0");

fx_stack = 
 vgroup("[1]", dm.sawtooth_demo) <:
 vgroup("[2]", dm.flanger_demo) : 
 vgroup("[3]", dm.phaser2_demo);

level_viewer(x,y) = attach(x, vgroup("[4]", dm.spectral_level_demo(x+y))),y;

process = fx_stack : level_viewer;
