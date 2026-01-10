import("stdfaust.lib");

gateA = checkbox("gateA") == 0;
gateB = checkbox("gateB") == 0;

voiceA = gateA : ondemand(os.osc(220));
voiceB = gateB : ondemand(os.square(330));

process = voiceA + voiceB;
