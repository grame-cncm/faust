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
#include "check.hh"
#include "interval_algebra.hh"
#include "interval_def.hh"
// #include "precision_utils.hh"

namespace itv {
//------------------------------------------------------------------------------------------
// Interval IntNum

interval interval_algebra::IntNum(int x) const
{
    int lsb = -24; // lsb_number(x); // x is an integer so lsb is bound to be >=0, but we might be able to shave a couple more bits

    while (floor(x*pow(2, -lsb-1)) == x*pow(2, -lsb-1) and x != 0)
        lsb++;

    return {double(x), double(x), lsb}; 
}
    
interval interval_algebra::Int64Num(int64_t x) const
{
    int lsb = -24; // lsb_number(x); // x is an integer so lsb is bound to be >=0, but we might be able to shave a couple more bits

    while (floor(x*pow(2, -lsb-1)) == x*pow(2, -lsb-1) and x != 0)
        lsb++;

    return {double(x), double(x), lsb};
}
}  // namespace itv
