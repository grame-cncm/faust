gain_h = hslider("[0]controls/gain_h", 0.5, 0.0, 1.0, 0.01);
gain_v = vslider("[1]controls/gain_v", 0.25, 0.0, 1.0, 0.01);
bias_n = nentry("[2]controls/bias_n", 0.0, -1.0, 1.0, 0.001);
gate_c = checkbox("[3]controls/gate_c");
trig_b = button("[4]controls/trig_b");

a0(x) = x * gain_h + bias_n;
a1(x) = x * gain_v - bias_n;
a2(x) = x * (gain_h + gain_v);
a3(x) = x * (gate_c + trig_b);
a4(x) = (x + bias_n) * (gain_h * gain_v);
a5(x) = (x - bias_n) * (1.0 + gate_c);
a6(x) = x * (0.25 + trig_b);
a7(x) = x * (gain_h + gain_v + gate_c + trig_b);

b0(x) = a0(x) : hbargraph("[10]meters/b0_hbar", -2.0, 2.0);
b1(x) = a1(x) : vbargraph("[11]meters/b1_vbar", -2.0, 2.0);
b2(x) = a2(x) : hbargraph("[12]meters/b2_hbar", -2.0, 2.0);
b3(x) = a3(x) : vbargraph("[13]meters/b3_vbar", -2.0, 2.0);

process = _ <: b0, b1, b2, b3, a4, a5, a6, a7;
