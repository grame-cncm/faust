/* Copyright 2023 Yann ORLAREY
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <algorithm>
#include <functional>
#include <random>

#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval Atan2
// interval Atan2(const interval& x, const interval& y) const;
// void testAtan2() const;

// be careful with the order of the arguments:
// atan2 is typically called as atan2(y,x) 
// (where (x,y) are the cartesian coordinates of the point we wish to retrieve the angle of)
interval interval_algebra::Atan2(const interval& y, const interval& x) const 
{
    double lo = -M_PI;
    double hi = M_PI;

    // atan2 is continuous on the plane except on Ox- = {(x,y)| x<=0 and y=0} where the angle gap happens
    // if the domain spans the discontinuity, we split in along the Ox axis 
    // in order to have a continuous function on each domain
    // we study it on each of the sub-domains and then combine the results
    
    // atan2(y, x) = atan(y/x) + constant: precision is that of y/x compounded with that of atan
    // cf https://en.wikipedia.org/wiki/Atan2#Definition_and_computation

    if (x.lo() <= 0 and y.hasZero()) // if we intersect the Ox- axis
    {
        interval yp = {0, y.hi(), y.lsb()}; // positive part of y
        interval yn = {y.lo(), 0, y.lsb()}; // negative part of y

        interval dp = interval_algebra::Div(yp, x);
        interval dn = interval_algebra::Div(yn, x);

        int precisionp = exactPrecisionUnary(atan, maxValAbs(dp), signMaxValAbs(dp)*pow(2, dp.lsb())); 
        int precisionn = exactPrecisionUnary(atan, maxValAbs(dn), signMaxValAbs(dn)*pow(2, dn.lsb())); 

        return {lo, hi, std::min(precisionp, precisionn)}; // final precision is the finest precision attained on either of the domains
    }
        
    interval d = interval_algebra::Div(y, x);
    int precision = exactPrecisionUnary(atan, maxValAbs(d), signMaxValAbs(d)*pow(2, d.lsb())); 

    // highest angle between a point of XxY and the x-axis
    if (y.lo() >= 0) // the domain XxY is entirely included in the higher half of the plane, where the angle is highest
    {
        if (x.lo() <= 0) // we intersect the quadrant in which atan2 takes the highest values
            hi = atan2(y.lo(), x.lo());
        else 
            hi = atan2(y.hi(), x.lo());
    } else {
        if (x.hi() >= 0)
        {
            if (y.hi() >=0 )
                hi = atan2(y.hi(), x.lo());
            else 
                hi = atan2(y.hi(), x.hi());
        } else {
            hi = atan2(y.lo(), x.hi());   
        }
    }

    // lowest angle between a point of XxY and the x-axis
    if (y.hi() <= 0) // the domain XxY is entirely included in the lower half of the plane, where the angle is highest
    {
        if (x.lo() <= 0)
            lo = atan2(y.hi(), x.lo());
        else 
            lo = atan2(y.lo(), x.lo());
    } else {
        if (x.hi() >= 0)
        {
            if (y.lo() >= 0)
                lo = atan2(y.lo(), x.hi());
            else 
                lo = atan2(y.lo(), x.lo());
        } else {
            lo = atan2(y.hi(), x.hi());
        }
    }
    
    return {lo, hi, precision};
}

void interval_algebra::testAtan2() const
{
    // std::cout << "Atan2 not implemented" << std::endl;
    analyzeBinaryMethod(10, 1000000, "atan2", interval(1, 2, -24), interval(1, 2, -24), atan2, &interval_algebra::Atan2);
    analyzeBinaryMethod(10, 1000000, "atan2", interval(-1, 2, -24), interval(1, 2, -24), atan2, &interval_algebra::Atan2);
    analyzeBinaryMethod(10, 1000000, "atan2", interval(-2, -1, -24), interval(1, 2, -24), atan2, &interval_algebra::Atan2);
    analyzeBinaryMethod(10, 1000000, "atan2", interval(-2, -1, -24), interval(-1, 2, -24), atan2, &interval_algebra::Atan2);
    analyzeBinaryMethod(10, 1000000, "atan2", interval(-2, -1, -24), interval(-2, -1, -24), atan2, &interval_algebra::Atan2);

    analyzeBinaryMethod(10, 1000000, "atan2", interval(-1, 2, -24), interval(-1, 2, -24), atan2, &interval_algebra::Atan2);
    analyzeBinaryMethod(10, 1000000, "atan2", interval(-1, 2, -24), interval(-2, -1, -24), atan2, &interval_algebra::Atan2);
}
}  // namespace itv