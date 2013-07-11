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

@synthesize xAccel;
@synthesize yAccel;
@synthesize zAccel;
@synthesize xGyro;
@synthesize yGyro;
@synthesize zGyro;
@synthesize heading;

-(id)initWithSampleRate:(double)rate cutoffFrequency:(double)freq
{
	self = [super init];
    
	if(self != nil)
	{
		double dt = 1.0 / rate;
		double RC = 1.0 / freq;
		_filterConstant = dt / (dt + RC);
        self.xAccel = 0.;
        self.yAccel = 0.;
        self.zAccel = 0.;
        self.xGyro = 0.;
        self.yGyro = 0.;
        self.zGyro = 0.;
        self.heading = 0.;
	}
	return self;
}

- (void)addAccelerationX:(float)x y:(float)y z:(float)z
{
	double alpha = _filterConstant;
	
	self.xAccel = x * alpha + self.xAccel * (1.0 - alpha);
	self.yAccel = y * alpha + self.yAccel * (1.0 - alpha);
	self.zAccel = z * alpha + self.zAccel * (1.0 - alpha);
}

- (void)addGyroX:(float)x y:(float)y z:(float)z
{
	double alpha = _filterConstant;
	
	self.xGyro = x * alpha + self.xGyro * (1.0 - alpha);
	self.yGyro = y * alpha + self.yGyro * (1.0 - alpha);
	self.zGyro = z * alpha + self.zGyro * (1.0 - alpha);
}

- (void)addHeading:(float)h
{
	double alpha = _filterConstant;
	
	self.heading = h * alpha + self.heading * (1.0 - alpha);
}

@end
