// This code (provided by Felix pfeifer.felix@googlemail.com) takes exponential time to compile
// The problem has been corrected in faust 0996b7

import("math.lib");
import("music.lib");

ndots = 40; // integer ! minimal possible value is 4
/// exponential compile time, change this value

diffy = hslider("DiffY", 1, 0, 1, 0.001);
dots = hslider("Dots", 4, 4, ndots, 1);
freqrange = hslider("Freqrange", 0, 0, 1000, 0.001);
freqcenter = hslider("Freqcenter", 100, 20, 5000, 0.001);

SH(trig,x) = (*(1 - trig) + x * trig) ~ _;
switchN(n, s) = par(i, n , _*(i==s)):>_;

mirror(x) = x*((x<=1)&(x>= -1)) + (1-frac(x))*(x>1) + (-frac(x)-1)*(x< -1);

dynElem(ramp, noise, num) = rampElem(ramp,noise,num), noise, (num+1),
rampElem(ramp,noise,num), ampElem(ramp,noise);
ampElem(ramp, noise) =
(_<:(_*(1-(ramp<ramp'))+mirror(_+noise'*diffy)*(ramp<ramp')))~_;
rampElem(ramp, noise, num)= rampCond(ramp, noise)*(num<=dots)+ramp*(num>dots);
rampCond(ramp, noise) =
(_<:(rampGen(timeC(ramp,noise))*((ramp<ramp')|((_'<_)&(_<=1))) ))~_;
rampGen(time, x) =  x+time;
timeC(ramp, noise) = (SH((ramp<ramp'), noise)*0.5+0.5)*fRange+mFreq;
fRange = 1/SR*freqrange;
mFreq = 1/SR*freqcenter*dots;
imp(x) = 1*(x'==0)+1;
impuls = (imp~_)-1;
rampno1(x) = x+impuls;

///### these are the lines, that cause the exponentially increasing compile time ###
pSeries(1,Func) = Func;
pSeries(i,Func) = Func : pSeries(i-1,Func), _, _;
pchain(n) = pSeries(n,dynElem) ~ rampno1;
rawgen = (noise,1):pchain(ndots);

process = rawgen;
