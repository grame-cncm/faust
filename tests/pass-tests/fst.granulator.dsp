//---------------------------- Granulator ------------------------------

import("music.lib");

//------------------------------------------------------------------
smooth(c)		= *(1-c) : +~*(c);
square(x)		= x*x;
noise2			= (+(12342) ~ *(1123915245))/RANDMAX;
noise3			= (+(12345) ~ *(1094789245))/RANDMAX;
noise4			= (+(12312) ~ *(1103195245))/RANDMAX;

//------------------------ User interface -----------------------

size			= nentry("1 grainsize",200,0.001,10000,1)*(44.1): smooth(0.99);
sizevariation		= fmin(nentry("2 sizevariation",20,0,5000,1)*(44.1),size-2): smooth(0.99);
separation		= nentry("3 grainseparation",200,0,10000,1)*(44.1) : smooth(0.99);
separationvariation	= fmin(nentry("4 ratevariation",20,0,5000,1)*(44.1),separation-2): smooth(0.99);
pitch			= nentry("5 pitch (semitones)", 0,-30,30,0.01): smooth(0.99);
pitchvariation		= nentry("6 pitchvariation",0,0,30,0.01): smooth(0.99);
spread			= nentry("7 stereospread",0.5,0,1,0.01): smooth(0.99);
fixdelay		= nentry("8 fixdelay",0,0,1000,1)*(44.1) : smooth(0.99);
delayrange		= nentry("9 delay range", 0,0,1000,1)*(44.1) : smooth(0.99);
//------------------ Random variations calculation --------------

Sample(sig,selector,y)	= select2(int(selector), y, sig);		//SnH Gives a random value when selector=1 and keeps it while selector=0
SnH(sig)		= Sample(sig,select)~_ : smooth(0.9995) ;	//Usefull to calculate random grain and silence durations

calc(y)			= ((+(1)*(y<size+sizevariation+separation+separationvariation))~_ );
calculate		= calc~_;
select			= calculate==0;					//Selector for SnH, to give a new value at each grain

//------------------- Grain and silence durations --------------

grainsize(sig1)		= size + SnH(sig1)*(sizevariation);

grainseparation(sig2)	= separation + SnH(sig2)*(separationvariation);

//------------------- Counters,Window and Grain ----------------

	//Loop counts form 0 to grainsize+grainseparation
counter(sig1,sig2)	= count(sig1,sig2)~_ 
with {
	count(sig1,sig2,y)	= ((+(1)*(y<grainsize(sig1)+grainseparation(sig2)))~_ ); 
};
playgrain(sig1,sig2)	= (counter(sig1,sig2) < grainsize(sig1));
windowcount(sig1,sig2)	= (counter(sig1,sig2))*(playgrain(sig1,sig2));

TABLESIN(index)	= rdtable(10000, sin(time/100), int(index*100));			//Low cpu cost sine calculation

window(sig1,sig2)	= square(TABLESIN(PI*(windowcount(sig1,sig2)/grainsize(sig1))));

//---------------------- pitch-shifter -------------------------

positivepow(index)	= rdtable(1000, pow(2,(time/100)), int(index*100));
POWER2(index)		= select2(index<0,positivepow(index),1/positivepow(fabs(index)));

transpose (w, x, s, sig)  = fdelay1s(d,sig)*fmin(d/x,1) + fdelay1s(d+w,sig)*(1-fmin(d/x,1)) 
	   	with {  i = 1 - POWER2(s/12);
			d = i : (+ : +(w) : fmod(_,w)) ~ _; };

grain(sig1,sig2,sig3,x)		= x : *(window(sig1,sig2)) : transpose(4000,1000,pitch+SnH(sig3)*(pitchvariation));

//-------------------------- Stereo spread -------------------

stereospread(sig1,sig2)	= _ <: *(1-fabs(SnH(sig1*(spread)))),*(1-fabs(SnH(sig2*(spread)))); //random panoramic

delayedpart		= fdelay1s(fixdelay+SnH((noise+1.1)/(2))*delayrange:smooth(0.999)) : stereospread(noise3,noise4);
realtimepart		= stereospread(noise,noise2);

granulation(x)		= 	x : grain(noise3,noise2,noise) <: realtimepart,delayedpart :> _,_ ;  

process			= hgroup("Granulator",granulation);
