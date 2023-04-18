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

namespace itv {
//------------------------------------------------------------------------------------------
// Interval IntNum

interval interval_algebra::VSlider(const interval& name, const interval& init, const interval& lo, const interval& hi,
                                   const interval& step) const
{
    // elements of a slider with range [lo; hi] and step step are of the form lo + k·step <= hi with k an integer
    // the precision needed to represent such elements is the minimum between
    int lsb = std::min(step.lsb(), lo.lsb()); // the precision of the lower bound and that of the step
    if (step.lo() > 0) // if we don't have negative or zero steps 
        lsb = std::min(lsb, (int)log2(step.lo())); // and that associated to the smallest value the step can take

    return {lo.lo(), hi.hi(), lsb};  // TODO: step, init
}
}  // namespace itv
