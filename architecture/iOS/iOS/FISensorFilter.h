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


#import <Foundation/Foundation.h>

@interface FISensorFilter : NSObject
{
    double      _filterConstant;
}

@property(nonatomic, assign) float xAccel;
@property(nonatomic, assign) float yAccel;
@property(nonatomic, assign) float zAccel;
@property(nonatomic, assign) float xGyro;
@property(nonatomic, assign) float yGyro;
@property(nonatomic, assign) float zGyro;
@property(nonatomic, assign) float heading;

- (id)initWithSampleRate:(double)rate cutoffFrequency:(double)freq;
- (void)addAccelerationX:(float)x y:(float)y z:(float)z;
- (void)addGyroX:(float)x y:(float)y z:(float)z;
- (void)addHeading:(float)h;

@end
