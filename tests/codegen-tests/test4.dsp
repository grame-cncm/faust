
IIR2P(b0,b1,b2,a1,a2) = + ~ conv2 : conv3
	with {
		conv2 	= _ <: 0 - _*a1 - mem*a2 ;
		conv3 	= _ <: _*b0 + mem*b1 + (mem:mem)*b2;
	};

process = IIR2P(1.25,1.73,1,1.73,1);
