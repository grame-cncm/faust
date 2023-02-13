/*
//enveloppe en cloche de cosinus//
import("stdfaust.lib");
grainsize = hslider("grainsize [unit:msec]", 100, 1, 1000, 1);
rarefaction = hslider("rarefaction", 0.2, 0, 1, 0.01);
//durée maximale du retard tiré au sort//
delaymax = hslider("delaymax", 1000, 10, 10000, 1);
//calcul de la fréquence du grain//
grainfreq = 1000 / grainsize;
//ma.PI est le nombre PI
ramp = os.phasor(1, grainfreq);
//@1 : 1 retard de 1 échantillon, c'est l'échantillon d'avant//
//on veut détecter le moment où le phasor (qui monte de 0 à 1 en boucle) passe la valeur 0.0001
//seuil vaut presque tout le temps 0, et 1 quand le phasor franchit la valeur 0.0001
seuil = (ramp > 0.0001) * (ramp@1 <= 0.0001);
phase = ramp : *(0.5) : *(2) : *(ma.PI);
//pas besoin de soustraire -0.25
//parce que l'équivalent de cos~ est oscp qui est un sinus

//on s'occupe du tirage au sort de l'enveloppe : 1 ou 0
//on utilise le noise qui fait des tirages au sort en permanence//
//entre -1 et 1
source = _;

//on prend un noise qu'on ajuste entre 0 et 1
//la comparaison avec > donne 1 (vrai) ou 0 (faux)
test = (no.noise : +(1) : *(0.5)) > rarefaction;
//sample and hold pour laisser passer uniquement quand seuil vaut 1//
factor = test : ba.sAndH(seuil);

//tirage au sort de la durée du retard
//passage de la nouvelle valeur uniquement au début de chaque période
del = no.noise : +(1) : *(0.5) : *(delaymax) : *(ma.SR) : /(1000) : ba.sAndH(seuil);

process = source : de.fdelay(524288, del) : *(os.oscp(0, phase)) *(factor);
*/

declare compilation_options    "-single -scal -e grain3.dsp -o grain3.dsp";
declare library_path "/Documents/faust-github-faust2/tests/impulse-tests/dsp/grain3.dsp";
declare library_path "/usr/local/share/faust/stdfaust.lib";
declare library_path "/usr/local/share/faust/delays.lib";
declare library_path "/usr/local/share/faust/noises.lib";
declare library_path "/usr/local/share/faust/maths.lib";
declare library_path "/usr/local/share/faust/platform.lib";
declare library_path "/usr/local/share/faust/basics.lib";
declare library_path "/usr/local/share/faust/oscillators.lib";
declare basics_lib_name "Faust Basic Element Library";
declare basics_lib_version "0.1";
declare delays_lib_name "Faust Delay Library";
declare delays_lib_version "0.1";
declare filename "grain3.dsp";
declare maths_lib_author "GRAME";
declare maths_lib_copyright "GRAME";
declare maths_lib_license "LGPL with exception";
declare maths_lib_name "Faust Math Library";
declare maths_lib_version "2.3";
declare name "grain3";
declare noises_lib_name "Faust Noise Generator Library";
declare noises_lib_version "0.0";
declare oscillators_lib_name "Faust Oscillator Library";
declare oscillators_lib_version "0.1";
declare platform_lib_name "Generic Platform Library";
declare platform_lib_version "0.1";
process = _ : \(x7).(((x7,(524289,(0,((_,12345 : +)~((_,1103515245 : *),-1 : &),2147483647.0f : / : _,1 : + : _,0.5f : * : _,hslider("delaymax", 1000.0f, 10.0f, 10000.0f, 1.0f) : * : _,(192000.0f,(1.0f,fconstant(int fSamplingFreq, <math.h>) : max) : min) : * : _,1000 : / : (((((1000,hslider("grainsize [unit:msec]", 100.0f, 1.0f, 1000.0f, 1.0f) : /),(192000.0f,(1.0f,fconstant(int fSamplingFreq, <math.h>) : max) : min : float) : / : (+ : \(x10).(x10,(x10 : floor) : -))~_ : _,1.0f : *),0.0001f : >),((((1000,hslider("grainsize [unit:msec]", 100.0f, 1.0f, 1000.0f, 1.0f) : /),(192000.0f,(1.0f,fconstant(int fSamplingFreq, <math.h>) : max) : min : float) : / : (+ : \(x10).(x10,(x10 : floor) : -))~_ : _,1.0f : *),1 : @),0.0001f : <=) : *),_,_ : select2)~_ : int) : max) : min) : @),(1,(((_,12345 : +)~((_,1103515245 : *),-1 : &),2147483647.0f : / : _,1 : + : _,0.5f : * : _,hslider("delaymax", 1000.0f, 10.0f, 10000.0f, 1.0f) : * : _,(192000.0f,(1.0f,fconstant(int fSamplingFreq, <math.h>) : max) : min) : * : _,1000 : / : (((((1000,hslider("grainsize [unit:msec]", 100.0f, 1.0f, 1000.0f, 1.0f) : /),(192000.0f,(1.0f,fconstant(int fSamplingFreq, <math.h>) : max) : min : float) : / : (+ : \(x12).(x12,(x12 : floor) : -))~_ : _,1.0f : *),0.0001f : >),((((1000,hslider("grainsize [unit:msec]", 100.0f, 1.0f, 1000.0f, 1.0f) : /),(192000.0f,(1.0f,fconstant(int fSamplingFreq, <math.h>) : max) : min : float) : / : (+ : \(x12).(x12,(x12 : floor) : -))~_ : _,1.0f : *),1 : @),0.0001f : <=) : *),_,_ : select2)~_),((_,12345 : +)~((_,1103515245 : *),-1 : &),2147483647.0f : / : _,1 : + : _,0.5f : * : _,hslider("delaymax", 1000.0f, 10.0f, 10000.0f, 1.0f) : * : _,(192000.0f,(1.0f,fconstant(int fSamplingFreq, <math.h>) : max) : min) : * : _,1000 : / : (((((1000,hslider("grainsize [unit:msec]", 100.0f, 1.0f, 1000.0f, 1.0f) : /),(192000.0f,(1.0f,fconstant(int fSamplingFreq, <math.h>) : max) : min : float) : / : (+ : \(x12).(x12,(x12 : floor) : -))~_ : _,1.0f : *),0.0001f : >),((((1000,hslider("grainsize [unit:msec]", 100.0f, 1.0f, 1000.0f, 1.0f) : /),(192000.0f,(1.0f,fconstant(int fSamplingFreq, <math.h>) : max) : min : float) : / : (+ : \(x12).(x12,(x12 : floor) : -))~_ : _,1.0f : *),1 : @),0.0001f : <=) : *),_,_ : select2)~_ : floor) : -) : -) : *),((x7,(524289,(0,(((_,12345 : +)~((_,1103515245 : *),-1 : &),2147483647.0f : / : _,1 : + : _,0.5f : * : _,hslider("delaymax", 1000.0f, 10.0f, 10000.0f, 1.0f) : * : _,(192000.0f,(1.0f,fconstant(int fSamplingFreq, <math.h>) : max) : min) : * : _,1000 : / : (((((1000,hslider("grainsize [unit:msec]", 100.0f, 1.0f, 1000.0f, 1.0f) : /),(192000.0f,(1.0f,fconstant(int fSamplingFreq, <math.h>) : max) : min : float) : / : (+ : \(x10).(x10,(x10 : floor) : -))~_ : _,1.0f : *),0.0001f : >),((((1000,hslider("grainsize [unit:msec]", 100.0f, 1.0f, 1000.0f, 1.0f) : /),(192000.0f,(1.0f,fconstant(int fSamplingFreq, <math.h>) : max) : min : float) : / : (+ : \(x10).(x10,(x10 : floor) : -))~_ : _,1.0f : *),1 : @),0.0001f : <=) : *),_,_ : select2)~_ : int),1 : +) : max) : min) : @),(((_,12345 : +)~((_,1103515245 : *),-1 : &),2147483647.0f : / : _,1 : + : _,0.5f : * : _,hslider("delaymax", 1000.0f, 10.0f, 10000.0f, 1.0f) : * : _,(192000.0f,(1.0f,fconstant(int fSamplingFreq, <math.h>) : max) : min) : * : _,1000 : / : (((((1000,hslider("grainsize [unit:msec]", 100.0f, 1.0f, 1000.0f, 1.0f) : /),(192000.0f,(1.0f,fconstant(int fSamplingFreq, <math.h>) : max) : min : float) : / : (+ : \(x12).(x12,(x12 : floor) : -))~_ : _,1.0f : *),0.0001f : >),((((1000,hslider("grainsize [unit:msec]", 100.0f, 1.0f, 1000.0f, 1.0f) : /),(192000.0f,(1.0f,fconstant(int fSamplingFreq, <math.h>) : max) : min : float) : / : (+ : \(x12).(x12,(x12 : floor) : -))~_ : _,1.0f : *),1 : @),0.0001f : <=) : *),_,_ : select2)~_),((_,12345 : +)~((_,1103515245 : *),-1 : &),2147483647.0f : / : _,1 : + : _,0.5f : * : _,hslider("delaymax", 1000.0f, 10.0f, 10000.0f, 1.0f) : * : _,(192000.0f,(1.0f,fconstant(int fSamplingFreq, <math.h>) : max) : min) : * : _,1000 : / : (((((1000,hslider("grainsize [unit:msec]", 100.0f, 1.0f, 1000.0f, 1.0f) : /),(192000.0f,(1.0f,fconstant(int fSamplingFreq, <math.h>) : max) : min : float) : / : (+ : \(x12).(x12,(x12 : floor) : -))~_ : _,1.0f : *),0.0001f : >),((((1000,hslider("grainsize [unit:msec]", 100.0f, 1.0f, 1000.0f, 1.0f) : /),(192000.0f,(1.0f,fconstant(int fSamplingFreq, <math.h>) : max) : min : float) : / : (+ : \(x12).(x12,(x12 : floor) : -))~_ : _,1.0f : *),1 : @),0.0001f : <=) : *),_,_ : select2)~_ : floor) : -) : *) : +) : (_,(((65536,((((_,1 : +)~_,1 : - : float),6.2831853071795862f : *),(65536 : float) : / : sin),(0,(192000.0f,(1.0f,fconstant(int fSamplingFreq, <math.h>) : max) : min : float) : / : (+ : \(x5).(x5,(x5 : floor) : -))~_ : _,(65536 : float) : * : int) : rdtable),((1000,hslider("grainsize [unit:msec]", 100.0f, 1.0f, 1000.0f, 1.0f) : /),(192000.0f,(1.0f,fconstant(int fSamplingFreq, <math.h>) : max) : min : float) : / : (+ : \(x6).(x6,(x6 : floor) : -))~_ : _,1.0f : * : _,0.5f : * : _,2 : * : _,3.1415926535897931f : * : cos) : *),((65536,((((_,1 : +)~_,1 : - : float),6.2831853071795862f : *),(65536 : float) : / : cos),(0,(192000.0f,(1.0f,fconstant(int fSamplingFreq, <math.h>) : max) : min : float) : / : (+ : \(x5).(x5,(x5 : floor) : -))~_ : _,(65536 : float) : * : int) : rdtable),((1000,hslider("grainsize [unit:msec]", 100.0f, 1.0f, 1000.0f, 1.0f) : /),(192000.0f,(1.0f,fconstant(int fSamplingFreq, <math.h>) : max) : min : float) : / : (+ : \(x6).(x6,(x6 : floor) : -))~_ : _,1.0f : * : _,0.5f : * : _,2 : * : _,3.1415926535897931f : * : sin) : *) : +) : *),(((_,12345 : +)~((_,1103515245 : *),-1 : &),2147483647.0f : / : _,1 : + : _,0.5f : *),hslider("rarefaction", 0.20000000000000001f, 0.0f, 1.0f, 0.01f) : > : (((((1000,hslider("grainsize [unit:msec]", 100.0f, 1.0f, 1000.0f, 1.0f) : /),(192000.0f,(1.0f,fconstant(int fSamplingFreq, <math.h>) : max) : min : float) : / : (+ : \(x2).(x2,(x2 : floor) : -))~_ : _,1.0f : *),0.0001f : >),((((1000,hslider("grainsize [unit:msec]", 100.0f, 1.0f, 1000.0f, 1.0f) : /),(192000.0f,(1.0f,fconstant(int fSamplingFreq, <math.h>) : max) : min : float) : / : (+ : \(x2).(x2,(x2 : floor) : -))~_ : _,1.0f : *),1 : @),0.0001f : <=) : *),_,_ : select2)~_) : *;
