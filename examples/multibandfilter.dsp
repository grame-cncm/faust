//---------------------------Multi Band Filter-----------------------------
//
//-------------------------------------------------------------------------

process 		= hgroup("Multi Band Filter", 
							seq( i, 10, vgroup("peak %i", component("bandfilter.dsp").bandfilter(1000*(1+i))) )
						);
