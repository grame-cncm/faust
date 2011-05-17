declare name 		"envelop";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

import("music.lib");

//-------------------------------------------------
// 		ADSR Envelop Generator
//		The 'state' of the envelop generator is
//		defined by a phase signal p2 allowing to
//		distinguish the attack and the decay-sustain
//		phases, and the envelop signal y itself.
//-------------------------------------------------

envelop(a,d,s,r,t) = adsr ~ (_,_) : (!,_) // The 2 'state' signal are feedback
    with {
		adsr (p2,y) = (t>0) & (p2|(y>=1)), // p2 = decay-sustain phase
		y + p1*a - (p2&(y>s))*d*y - p3*r*y	// y  = envelop signal
		with {
			p1 = (p2==0) & (t>0) & (y<1); // p1 = attack phase
			p3 = (t<=0) & (y>0); // p3 = release phase
		};
    };


attack 	= 1.0/(SR*nentry("1-attack (ms)", 20, 1, 1000, 1)/1000);
decay  	= nentry("2-decay (speed)", 2, 1, 100, 0.1)/100000;
sustain	= nentry("3-sustain (pcent)", 10, 1, 100, 0.1)/100;
release	= nentry("4-release (speed)", 10, 1, 100, 0.1)/100000;


process =  button("play"): envelop(attack, decay, sustain, release) : *(noise);

