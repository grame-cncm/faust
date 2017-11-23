import("effect.lib");

process(x,y) = stereo_reverb_tester(gui_group,x,y)
with {
  gui_group(x) = hgroup("Stereo Reverb Tester",x);

stereo_reverb_tester(revin_group,x,y) = inx,iny with {
  ck_group(x) = revin_group(vgroup("[1] Input Config",x));
  mutegain = 0;
  pinkin = ck_group(checkbox("[2] Pink Noise
         [tooltip: Pink Noise (or 1/f noise) is Constant-Q Noise (useful for adjusting the EQ sections)]"));

  impulsify = _ <: _,mem : - : >(0);
  imp_group(x) = revin_group(hgroup("[2] Impulse Selection",x));
  pulseL =  imp_group(button("[1] Left
         [tooltip: Send impulse into LEFT channel]")) : impulsify;
  pulseC =  imp_group(button("[2] Center
         [tooltip: Send impulse into LEFT and RIGHT channels]")) : impulsify;
  pulseR =  imp_group(button("[3] Right
         [tooltip: Send impulse into RIGHT channel]")) : impulsify;

  inx = x*mutegain + (pulseL+pulseC) + pn;
  iny = y*mutegain + (pulseR+pulseC) + pn;
  pn = 0.1*pinkin*component("oscillator.lib").pink_noise;
};

};
