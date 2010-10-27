
IIR2P(b0,b1,b2,a1,a2) = + ~ conv2 : conv3
	with {
		conv2(x) 	= 0 - a1*x - a2*x';
		conv3(x) 	= b0*x + b1*x' + b2*x'';
	};

process = IIR2P(1.25,1.73,1,1.73,1);
