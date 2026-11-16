// WARNING : [scale:log] needs positive values, but the range is [-60, 0] in 'hslider("level[scale:log]",-2e+01f,-6e+01f,0.0f,0.1f)': the scale has no meaning here, the C++ architectures use a linear scale (a range in dB, for instance, is already logarithmic)

process = hslider("level[scale:log]", -20, -60, 0, 0.1);
