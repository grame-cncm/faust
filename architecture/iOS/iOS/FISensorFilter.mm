/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
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
