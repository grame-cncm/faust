#pragma once

#include <cmath>

#include "interval_def.hh"

namespace itv {

/**
 * @brief Computes the minimum of four doubles
 */
static double min4(double a, double b, double c, double d)
{
    return std::min(std::min(a, b), std::min(c, d));
}

/**
 * @brief Computes the maximum of four doubles
 */
static double max4(double a, double b, double c, double d)
{
    return std::max(std::max(a, b), std::max(c, d));
}

/**
 * @brief Computes the minimum of four ints
 */
static double min4(int a, int b, int c, int d)
{
    return std::min(std::min(a, b), std::min(c, d));
}

/**
 * @brief Computes the maximum of four ints
 */
static double max4(int a, int b, int c, int d)
{
    return std::max(std::max(a, b), std::max(c, d));
}

/**
 * @brief Computes the value with minimum absolute value among the bounds of an interval
 */
static double minValAbs(interval x)
{
    if (std::abs(x.lo()) < std::abs(x.hi())) {
        return x.lo();
    }
    return x.hi();
}

/**
 * @brief Computes the value with maximum absolute value
 */
static double maxValAbs(interval x)
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
static int signMinValAbs(interval x)
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
static int signMaxValAbs(interval x)
{
    if (std::abs(x.lo()) < std::abs(x.hi())) {
        return -1;
    }
    return 1;
}

}  // namespace itv