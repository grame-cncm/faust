
bandfilter = library("bandfilter.dsp").bandfilter;

process = 	seq(i, 10, 
				vgroup("band %i", 
					bandfilter(1000*(1+i))
				) 
		  	);	

