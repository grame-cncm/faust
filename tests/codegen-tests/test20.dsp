// sharing in second order trandfert function
// only two sample memories should be used

TF2(b0,b1,b2,a1,a2) = sub ~ conv2(a1,a2) : conv3(b0,b1,b2)
	with {
		conv3(k0,k1,k2,x) 	= k0*x + k1*x' + k2*x'';
		conv2(k0,k1,x) 		= k0*x + k1*x';
		sub(x,y)			= y-x;
	};

process = TF2(1.25,1.73,1,1.73,1);
