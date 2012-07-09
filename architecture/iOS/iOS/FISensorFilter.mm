/************************************************************************
 ************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2012 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 
 This is sample code. This file is provided as an example of minimal
 FAUST architecture file. Redistribution and use in source and binary
 forms, with or without modification, in part or in full are permitted.
 In particular you can create a derived work of this FAUST architecture
 and distribute that work under terms of your choice.
 
 This sample code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 ************************************************************************
 ************************************************************************/

/************************************************************************
 ************************************************************************
 Based on Apple AccelerometerGraph - http://developer.apple.com/library/ios/#samplecode/AccelerometerGraph
 Copyright (C) 2010 Apple Inc. All Rights Reserved.
 ************************************************************************
 ************************************************************************/


#import "FISensorFilter.h"

@implementation FISensorFilter

@synthesize x = _x;
@synthesize y = _y;
@synthesize z = _z;
@synthesize h = _h;

-(id)initWithSampleRate:(double)rate cutoffFrequency:(double)freq
{
	self = [super init];
	if(self != nil)
	{
		double dt = 1.0 / rate;
		double RC = 1.0 / freq;
		_filterConstant = dt / (dt + RC);
	}
	return self;
}

- (void)addAccelerationX:(float)x y:(float)y z:(float)z
{
	double alpha = _filterConstant;
	
	_x = x * alpha + _x * (1.0 - alpha);
	_y = y * alpha + _y * (1.0 - alpha);
	_z = z * alpha + _z * (1.0 - alpha);
}

- (void)addHeading:(float)h
{
	double alpha = _filterConstant;
	
	_h = h * alpha + _h * (1.0 - alpha);
}

@end
