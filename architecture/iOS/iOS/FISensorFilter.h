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
