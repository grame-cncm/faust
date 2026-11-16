// WARNING : [scale:log] with min = 0 in 'hslider("gain[scale:log]",0.5f,0.0f,1.0f,0.01f)': log(0) is not defined, the C++ architectures use a floor 60 dB under max

process = hslider("gain[scale:log]", 0.5, 0, 1, 0.01);
