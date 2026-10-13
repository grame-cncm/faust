/* Copyright 2020-2026 Yann Orlarey, Agathe Herrou, Stéphane Letz
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
#pragma once

#include "directed_rounding.hh"

namespace itv::detail {

// Internal scalar enclosures of exact real functions. Series use outward
// elementary arithmetic and analytic remainder bounds, not the host libm.
// Invalid arguments have two NaN bounds; uncertain reduction widens the image.
struct NumericBounds { double lo, hi; };
NumericBounds referenceUnary(UnaryOp op, double x);
NumericBounds referenceBinary(BinaryOp op, double x, double y);

}  // namespace itv::detail
