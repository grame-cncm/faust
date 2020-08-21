// verification des problèmes éventuels de "capture"
import("stdfaust.lib");

// OK: faust -svg tests/ondemand/tod1.dsp
// test rewriting of ondemand code
clock(n) = 1 : (+,n:%)~_  : ==(1); 

time = +(1)~_ ;
//process = clock(2), time: ondemand(_); // maintenant ça fonctionne ! // ici time est capturé

process = time, (clock(2), time: ondemand(_)); // ici time n'est pas capturé

//