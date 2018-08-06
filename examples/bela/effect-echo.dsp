// Enter Faust code here
import("music.lib");
import("filter.lib");


myEcho = _ <: *(dry), (+~(fdelay(65536,delLength)*feedback*-1) : *(1-dry)) :> _
with{
	delLength = 1000;
	feedback = 0.9;
	dry = 0;
};

process = myEcho;