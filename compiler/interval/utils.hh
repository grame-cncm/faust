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

#include <cmath>

#include "interval_def.hh"

namespace itv {

/**
 * @brief Computes the minimum of four doubles
 */
inline double min4(double a, double b, double c, double d)
{
    return std::min(std::min(a, b), std::min(c, d));
}

/**
 * @brief Computes the maximum of four doubles
 */
inline double max4(double a, double b, double c, double d)
{
    return std::max(std::max(a, b), std::max(c, d));
}

/**
 * @brief Computes the minimum of four ints
 */
inline double min4(int a, int b, int c, int d)
{
    return std::min(std::min(a, b), std::min(c, d));
}

/**
 * @brief Computes the maximum of four ints
 */
inline double max4(int a, int b, int c, int d)
{
    return std::max(std::max(a, b), std::max(c, d));
}

/**
 * @brief Computes the value with minimum absolute value among the bounds of an interval
 */
inline double minValAbs(interval x)
{
    if (std::abs(x.lo()) < std::abs(x.hi())) {
        return x.lo();
    }
    return x.hi();
}

/**
 * @brief Computes the value with maximum absolute value
 */
inline double maxValAbs(interval x)
{
    if (std::abs(x.lo()) < std::abs(x.hi())) {
        return x.hi();
    }
    return x.lo();
}

/**
 * @brief Computes the direction of the interior of the interval at the minimum absolute value of
 * its bounds
 */
inline int signMinValAbs(interval x)
{
    if (std::abs(x.lo()) < std::abs(x.hi())) {
        return 1;
    }
    return -1;
}

/**
 * @brief Computes the direction of the interior of the interval at the maximum absolute value of
 * its bounds
 */
inline int signMaxValAbs(interval x)
{
    if (std::abs(x.lo()) < std::abs(x.hi())) {
        return -1;
    }
    return 1;
}

}  // namespace itv