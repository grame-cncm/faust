//This program crash on faust 0.9.9.1

v = hslider("volume",0,0,100,1);
process =  +(v-v'), *(3*v);
