/* Copyright 2026 Yann Orlarey, Stéphane Letz
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

namespace itv {

/**
 * A real as the unevaluated sum hi + lo of two doubles (double-double), |lo| at most half
 * an ulp of hi : hi is the double nearest to hi + lo. The operations use error-free
 * transformations (the exact error of a sum, and of a product through a fused multiply-add),
 * about 106 bits of precision : a computation made at compile time, as exactly as possible,
 * rounded to the precision of the program when it is written into it (hi for a double,
 * ddToFloat for a float). hi is the double nearest to the exact value, except when that
 * value lies within about 2^-106 of it of a midpoint between two doubles.
 *
 * At the edges, a result follows the plain operation on hi : an exact zero takes its sign,
 * a value near the subnormals (below 2^-969) is the correctly rounded plain product or
 * quotient, and a value that overflows is an infinity (an intermediate that overflows is
 * computed again on scaled operands).
 *
 * The functions are compiled without contraction of a product and a sum into a fused
 * multiply-add (the interval sources are compiled with -ffp-contract=off) : their result
 * does not depend on the compiler that built them.
 */
struct DoubleDouble {
    double hi = 0.0;
    double lo = 0.0;
};

DoubleDouble ddAdd(DoubleDouble x, DoubleDouble y);  ///< x + y
DoubleDouble ddSub(DoubleDouble x, DoubleDouble y);  ///< x - y
DoubleDouble ddMul(DoubleDouble x, DoubleDouble y);  ///< x * y
DoubleDouble ddDiv(DoubleDouble x, DoubleDouble y);  ///< x / y, y not zero
float        ddToFloat(DoubleDouble x);               ///< the float nearest to hi + lo

}  // namespace itv
