//##################################### reverbTester.dsp #################################
// Handy test inputs for reverberator demos below.
//
// Author: JOS.
//########################################################################################
// TODO: author JOS

import("stdfaust.lib");


//==================================== GUI Declaration ===================================
//========================================================================================

reverb_tester(revin_group,x,y) = inx,iny with {
  ck_group(x) = revin_group(vgroup("[1] Input Config",x));
  mutegain = 1 - ck_group(checkbox("[1] Mute Ext Inputs
         [tooltip: When this is checked, the stereo external audio inputs are 
         disabled (good for hearing the impulse response or pink-noise response alone)]"));
  pinkin = ck_group(checkbox("[2] Pink Noise
         [tooltip: Pink Noise (or 1/f noise) is Constant-Q Noise (useful for adjusting 
         the EQ sections)]"));

  imp_group(x) = revin_group(hgroup("[2] Impulse Selection",x));
  pulseL =  imp_group(button("[1] Left
         [tooltip: Send impulse into LEFT channel]")) : ba.impulsify;
  pulseC =  imp_group(button("[2] Center
         [tooltip: Send impulse into LEFT and RIGHT channels]")) : ba.impulsify;
  pulseR =  imp_group(button("[3] Right
         [tooltip: Send impulse into RIGHT channel]")) : ba.impulsify;

  inx = x*mutegain + (pulseL+pulseC) + pn;
  iny = y*mutegain + (pulseR+pulseC) + pn;
  pn = 0.1*pinkin*no.pink_noise;
};


//============================================ DSP =======================================
//========================================================================================

process = reverb_tester(_);