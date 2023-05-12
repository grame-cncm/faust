#pragma once

#include <cmath>
#include "check.hh"

/** 
 * @brief truncate x at the precision induced by lsb
 * 
 * @param x value to truncate
 * @param lsb the precision to which to truncate
 * @return x truncated with lsb bits of precision
 * */
double truncate(double x, int lsb)
{
    double u = pow(2, lsb); // ulp
    double res = u*(double)floor(x/u);
    return res;
}

/**
 * @brief Computes the position of the least significant bit of a number
 * Floored to -24
 * 
 * @param x The number
 * @return The lsb
*/
int lsb_number(double x)
{
    int precision = -24;

    while (floor(x*pow(2, -precision-1)) == x*pow(2, -precision-1) and x != 0)
        precision++;

    return precision;
}

/**
 * @brief compute the precision needed in the output of a function 
 * 
 * @param f the function to analyse
 * @param x the point at which the tightest precision is needed
 * @param u the signed gap between the two consecutive numbers at which to compute the precision (ie the ulp)
*/
int exactPrecisionUnary(ufun f, long double x, long double u)
{
    int res = floor((double)log2(std::abs(f(x + u) - f(x))));
    return res;
}

/**
 * @brief compute the precision needed in the input of a function 
 * 
 * @param f the function to analyse
 * @param finv a function such that f o finv = Id locally
 * @param x the input point at which the tightest precision is needed
 * @param u the signed gap between the two consecutive numbers at which to compute the precision (ie the ulp)
*/
int exactPrecisionUnaryBackwards(ufun f, ufun finv, double x, double u)
{
    int res = ceil(
            (double)log2(
                std::abs(finv(f(x) + u) - x)
            )
        );
    return res;
}