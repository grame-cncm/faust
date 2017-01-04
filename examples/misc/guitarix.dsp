/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
 * Copyright (C) 2011 Pete Shorthose
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * 
 * ----------------------------------------------------------------------------
 * Adapted version from guitarixlite (v.0.28) using foreign functions 
 * to this self-contained Faust version (v.0.29)
 * Adapted by GRAME - 2014
 * ----------------------------------------------------------------------------
 */

declare name        "guitarix";
declare version     "0.29";
declare author   	"Guitarix project (http://guitarix.sourceforge.net/)";
declare copyright 	"Guitarix project";
declare license   	"LGPL";

ba = library("basics.lib");
si = library("signals.lib");

import("tubes.lib");
import("tonestacks.lib");

process = preamp; 

/****************************************************************
 ** Tube Preamp Emulation with
 *  tubescreamer -  tube stage 1 - 2 - tonestack - cabinet
 */
preamp = hgroup("Guitarix",
         hgroup("[0]TubeScreamer",ts9sim) :
         hgroup("[1]preamp: 12AX7", stage1 : stage2 ): 
         hgroup("[2]tonestack: jcm2000", tstack) :
         hgroup("[3]Cabinet", cab) )with {

    stage1 = T1_12AX7 : *(preamp): fi.lowpass(1,6531.0) : 
    			T2_12AX7 : *(preamp) with {
                preamp = vslider("[0] Pregain [style:knob]",-6,-20,20,0.1) : 
                  ba.db2linear : si.smoo;
             };

    stage2 = fi.lowpass(1,6531.0) : T3_12AX7 : *(gain) with {
                gain = vslider("[1] Gain [style:knob]",-6,-20.0,20.0,0.1) : 
                  ba.db2linear : si.smoo;
             };

    tstack = jcm2000(t, m, l) with {
        t = vslider("[2] Treble [style:knob]",0.5,0,1,0.01);
        m = vslider("[3] Middle [style:knob]",0.5,0,1,0.01);
        l = vslider("[4] Bass [style:knob]",0.5,0,1,0.01);
    };
};

/****************************************************************************************/

//-- Rdtable from waveform
rtable(table, r) = (table, int(r)):rdtable;

// Change sign of input signal x;
inverse(x) = abs(x) * invsign(x);

//function that takes f value and x sign
ccopysign(f, x) = abs(f)*sign(x);       

//-- Get sign and reversed sign of a signal x
sign (x) = x<0, 1, -1 : select2;  
invsign (x) = x<0, -1, 1 : select2;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           

//-- Interpolate value between i and i+1 in table with coefficient f.
interpolation (table, f, i) = rtable(table, i)*(1-f) + rtable(table,i+1)*f;

//-- Bound Index with table boundaries
boundIndex(size, index) = index : floor: min(size-1) : max(0);

//-- Bound factor of interpolation : factor-index if still in the table boundaries, 0 otherwise
boundFactor(size, factor, index) = 0<index<size-1, factor - index, 0 : select2;  

/****************************************************************************************
 * 1-dimensional function tables for linear interpolation
****************************************************************************************/

// Linear interpolation of x value in table
tubeF(table, low, high, step, size, x) = interpolation(
											table, 
											getFactor(low, step, size, x),
											linindex(low, step, x) : boundIndex(size));

//--Get interpolation factor
getFactor(low, step, size, x) = boundFactor(size, linindex(low, step, x), linindex(low, step, x) : boundIndex(size));

//-- Calculate linear index
linindex(low, step, x) = (x - low) * step;

/****************************************************************************************
 * 1-dimensional function tables for nonlinear interpolation
****************************************************************************************/
nonlininterpolation(table, low, high, step, size, x) = ts9(low, step, size, table, x) , inverse(x) : ccopysign;

//-- Interpolate value from table
ts9 (low, step, size, table, x) = interpolation(
										table, 
										getCoef(low, step, size, x), 
										nonlinindex(low, step, x) : boundIndex(size));

//-- Calculate non linear index
nonlinindex(low, step, x) = (abs(x)/(3.0 + abs(x)) - low) * step;

//--Get interpolation factor
getCoef(low, step, size, x) = boundFactor(size, nonlinindex(low, step, x), nonlinindex(low, step, x) : boundIndex(size));

/********* Faust Version of ts9nonlin.cc, generated by tools/ts9sim.py ****************/

ts9comp = nonlininterpolation(ts9table, low, high, step, size) with{

// Characteristics of the wavetable
	low = 0.0;
	high = 0.970874;
	step = 101.97;
	size = 100;
	
ts9table = waveform{0.0,-0.0296990148227,-0.0599780676992,-0.0908231643281,-0.122163239629,
	-0.15376009788,-0.184938007182,-0.214177260107,-0.239335434213,-0.259232575019,
	-0.274433909887,-0.286183308354,-0.29553854444,-0.303222323477,-0.309706249977,
	-0.315301338712,-0.320218440785,-0.324604982281,-0.328567120703,-0.332183356975,
	-0.335513124719,-0.33860236542,-0.34148724693,-0.344196707008,-0.346754233717,
	-0.34917913798,-0.351487480543,-0.35369275887,-0.355806424152,-0.357838275995,
	-0.359796767655,-0.361689244919,-0.363522135105,-0.365301098113,-0.367031148289,
	-0.368716753588,-0.370361916943,-0.371970243537,-0.373544996828,-0.375089145544,
	-0.376605403346,-0.378096262548,-0.379564022938,-0.381010816596,-0.382438629377,
	-0.383849319643,-0.385244634694,-0.386626225283,-0.387995658543,-0.389354429565,
	-0.39070397188,-0.392045667012,-0.393380853288,-0.39471083403,-0.396036885269,
	-0.397360263098,-0.398682210753,-0.400003965547,-0.401326765733,-0.402651857394,
	-0.403980501471,-0.405313980999,-0.406653608692,-0.40800073496,-0.409356756504,
	-0.410723125631,-0.412101360439,-0.413493056085,-0.414899897347,-0.416323672745,
	-0.417766290556,-0.419229797097,-0.420716397759,-0.422228481377,-0.423768648654,
	-0.425339745558,-0.426944902828,-0.428587583057,-0.430271637224,-0.432001373102,
	-0.433781638746,-0.435617925286,-0.437516494692,-0.439484540257,-0.441530390423,
	-0.443663770898,-0.445896146322,-0.448241172434,-0.450715304661,-0.453338632988,
	-0.45613605235,-0.45913894467,-0.46238766699,-0.465935359011,-0.469854010456,
	-0.474244617411,-0.479255257451,-0.48511588606,-0.492212726244,-0.501272723631
	};
};
/****************************************************************************************/

/****************************************************************************************
*	declare id 		"ts9sim";
*	declare name            "Tube Screamer";
*	declare category        "Distortion";
*
** 		based on a circuit diagram of the Ibanez TS-9 and
** 		a mathematical analysis published by Tamás Kenéz
****************************************************************************************/

smoothi(c) = *(1-c) : +~*(c);

ts9sim = ts9nonlin : lowpassfilter : *(gain) with {

    R1 = 4700;
    R2 = 51000 + 500000 * vslider("drive[name:Drive][style:knob]", 0.5, 0, 1, 0.01);
    C = 0.047 * 1e-6;
    a1 = (R1 + R2) * C * 2 * ma.SR;
    a2 = R1 * C * 2 * ma.SR;
    B0 = (1 + a1) / (1 + a2);
    B1 = (1 - a1) / (1 + a2);
    A1 = (1 - a2) / (1 + a2);
    X2 = fi.tf1(B0, B1, A1);

    ts9nonlin = _ <: _ ,(X2,_ : - : ts9comp) : - :> _;
    
    fc = vslider("tone[log][name:Tone][style:knob]", 400, 100, 1000, 1.03);
    lowpassfilter = fi.lowpass(1,fc);
    gain = vslider("level[name:Level][style:knob]", -16, -20, 4, 0.1) : ba.db2linear : smoothi(0.999);
};

/****************************************************************************************
*	declare name            "cabinet";
*
** 		based on a circuit diagram of the Ibanez TS-9 and
** 		a mathematical analysis published by Tamás Kenéz
****************************************************************************************/

wetdry = vslider("[5] amount[style:knob]",  100, 0, 100, 1) : /(100);
dry = 1 - wetdry;

cab = _<:(*(dry):_), (*(wetdry):fi.conv((0.000488281, -0.0020752, 0.000561523, -0.00231934, 0.000634766, -0.00247803, 0.000512695, -0.00247803, 0.000146484, -0.00219727, -0.000622559, -0.00145264, -0.00202637, 
    -2.44141e-05, -0.00438232, 0.00247803, -0.00822754, 0.00706787, -0.0159546, 0.0202148, -0.0471558, 0.0953003, -0.208582, 0.312427, 0.75, -0.26803, 
    0.399963, 0.200696, -0.146655, -0.29303, -0.222168, -0.113098, 0.0267334, 0.0312134, 0.164685, 0.0443481, 0.186621, 0.0540039, 0.123303, 
    0.0805054, 0.0739868, 0.0591797, 0.0661743, 0.0400391, 0.0429932, 0.0339844, 0.0320557, 0.02323, 0.0217285, 0.0182007, 0.0157227, 0.0130005, 
    0.0103882, 0.00942383, 0.00718994, 0.0067749, 0.00458984, 0.00455322, 0.00272217, 0.00294189, 0.00140381, 0.00170898, 0.000402832, 0.000720215, -0.000354004, 
    -2.44141e-05, -0.000915527, -0.000610352, -0.00134277, -0.0010498, -0.00166016, -0.0013916, -0.0019043, -0.00166016, -0.0020874, -0.00187988, -0.00224609, -0.00203857, 
    -0.00235596, -0.00217285, -0.0024292, -0.0022583, -0.00247803, -0.00233154, -0.00252686, -0.00238037, -0.00256348, -0.0024292, 0.75, -0.00246582, -0.0026001, 
    -0.00247803, -0.0026001, -0.00249023, -0.0026001, -0.00250244, -0.0026001, -0.00251465, -0.0026001, -0.00251465, -0.0026001, -0.00251465, -0.0026001, -0.00252686, 
    -0.00258789, -0.00252686, -0.00258789, -0.00251465, -0.00257568, -0.00251465, -0.00256348, -0.00251465, -0.00256348, -0.00251465, -0.00256348, -0.00251465, -0.00256348, 
    -0.00251465, -0.00256348, -0.00251465, -0.00256348, -0.00252686, -0.00256348, -0.00252686, -0.00255127, -0.00252686, -0.00255127, -0.00252686, -0.00255127, -0.00252686, 
    -0.00255127, -0.00252686, -0.00256348
     ))):>_;
