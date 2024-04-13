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
#include <climits>
#include <iostream>
#include <random>
#include <set>
#include <sstream>
#include <string>

#include "check.hh"
#include "interval_algebra.hh"
#include "precision_utils.hh"

/**
 * @brief check we have the expected interval
 *
 * @param expected interval as a string
 * @param exp interval to test
 */
void check(const std::string& expected, const itv::interval& exp)
{
    std::stringstream ss;
    ss << exp;
    if (ss.str().compare(expected) == 0) {
        std::cout << "\033[32m"
                  << "OK: " << expected << "\033[0m" << std::endl;
    } else {
        std::cout << "\033[31m"
                  << "ERR:  We got " << ss.str() << " instead of " << expected << "\033[0m" << std::endl;
    }
}

/**
 * @brief check that an interval result is the expected one
 *
 * @param testname
 * @param exp
 * @param res
 */
void check(const std::string& testname, const itv::interval& exp, const itv::interval& res)
{
    if (exp == res) {
        std::cout << "\033[32m"
                  << "OK: " << testname << " " << exp << " = " << res << "\033[0m" << std::endl;
        if (exp.lsb() != res.lsb()) {
            std::cout << "\033[33m"
                      << "\t But precisions differ by " << exp.lsb() - res.lsb() << "\033[0m" << std::endl;
        }
    } else {
        std::cout << "\033[31m"
                  << "ERR:" << testname << " FAILED. We got " << exp << " instead of " << res << "\033[0m" << std::endl;
    }
}

/**
 * @brief check that a boolean result is the expected one
 *
 * @param testname
 * @param exp
 * @param res
 */
void check(const std::string& testname, bool exp, bool res)
{
    if (exp == res) {
        std::cout << "\033[32m"
                  << "OK: " << testname << "\033[0m" << std::endl;
    } else {
        std::cout << "\033[31m"
                  << "ERR:" << testname << " FAILED. We got " << exp << " instead of " << res << "\033[0m" << std::endl;
    }
}

/**
 * @brief Approximate the resulting interval of a function
 *
 * @param N the number of iterations
 * @param f the function to test
 * @param x the interval of its first argument
 * @param y the interval of its second argument
 * @return interval the interval of the results
 */
itv::interval testfun(int N, bfun f, const itv::interval& x, const itv::interval& y)
{
    std::random_device             rd;  // used to generate a random seed, based on some hardware randomness
    std::default_random_engine     generator(rd());
    std::uniform_real_distribution rx(x.lo(), x.hi());
    std::uniform_real_distribution ry(y.lo(), y.hi());

    double a = f(x.lo(), y.lo());
    double b = f(x.lo(), y.hi());
    double c = f(x.hi(), y.lo());
    double d = f(x.hi(), y.hi());

    double l = itv::min4(a, b, c, d);
    double h = itv::max4(a, b, c, d);

    for (int i = 0; i < N; i++) {
        double u = rx(generator);
        double v = ry(generator);
        double r = f(u, v);
        if (r < l) {
            l = r;
        }
        if (r > h) {
            h = r;
        }
    }

    return {l, h};
}

/**
 * @brief analyze the Mod function, print the simulated and computed resulting interval.
 * The two should be close enough.
 *
 * @param x first argument interval
 * @param y second argument interval
 */
void analyzemod(itv::interval x, itv::interval y)
{
    itv::interval_algebra A;
    std::cout << "simulated fmod(" << x << "," << y << ") = " << testfun(10000, fmod, x, y) << std::endl;
    std::cout << "computed  fmod(" << x << "," << y << ") = " << A.Mod(x, y) << std::endl;
    std::cout << std::endl;
}

/**
 * @brief Compute numerically the output interval of a function
 *
 * @param E number of intervals/experiments
 * @param M number of measurements used to estimate the resulting interval
 * @param title name of the tested function
 * @param D maximal interval for the argument
 * @param f the numerical function of reference
 */
void analyzeUnaryFunction(int E, int M, const char* title, const itv::interval& D, ufun f)
{
    std::random_device             R;  // used to generate a random seed, based on some hardware randomness
    std::default_random_engine     generator(R());
    std::uniform_real_distribution rd(D.lo(), D.hi());

    std::cout << "Analysis of " << title << " in domain " << D << std::endl;

    for (int e = 0; e < E; e++) {  // E experiments

        // X: random input interval X < I
        double        a = rd(generator);
        double        b = rd(generator);
        itv::interval X(std::min(a, b), std::max(a, b));

        // [ylo,yhi] initial f(X) interval
        double t0 = f(X.lo());
        double t1 = f(X.hi());
        double y0 = std::min(t0, t1);
        double y1 = std::max(t0, t1);

        // random values in X
        std::uniform_real_distribution rx(X.lo(), X.hi());

        for (int m = 0; m < M; m++) {  // M measurements
            double y = f(rx(generator));
            if (y < y0) {
                y0 = y;
            }
            if (y > y1) {
                y1 = y;
            }
        }
        itv::interval Y(y0, y1);

        std::cout << e << ": " << title << "(" << X << ") = " << Y << std::endl;
    }
    std::cout << std::endl;
}

/**
 * @brief Check the unary interval function gives a good approximation of the numerical function
 *
 * @param E number of intervals/experiments
 * @param M number of measurements used to estimate the resulting interval
 * @param title name of the tested function
 * @param D maximal interval for the argument
 * @param f the numerical function of reference
 * @param mp the interval method corresponding to f
 */
void analyzeUnaryMethod(int E, int M, const char* title, const itv::interval& D, ufun f, umth mp)
{
    std::random_device             R;  // used to generate a random seed, based on some hardware randomness
    std::default_random_engine     generator(R());
    std::uniform_real_distribution rd(D.lo(), D.hi());
    itv::interval_algebra          A;

    std::cout << "Analysis of " << title << " in domain " << D << " (u = " << pow(2, D.lsb()) << ")" << std::endl;

    for (int e = 0; e < E; e++) {  // E experiments

        // X: random input interval X < I
        double        a = truncate(rd(generator), D.lsb());
        double        b = truncate(rd(generator), D.lsb());
        itv::interval X(std::min(a, b), std::max(a, b), D.lsb());

        // boundaries of the resulting interval
        double y0 = HUGE_VAL;   // std::min(t0, t1);
        double y1 = -HUGE_VAL;  // std::max(t0, t1);

        // precision of the resulting interval
        int lsb = INT_MAX;

        // random values in X
        std::uniform_real_distribution rx(X.lo(), X.hi());

        // std::vector<double> measurements;
        std::set<double> measurements;

        // the loop has almost no chance of drawing X.hi(): we manually add it
        double sample =
            X.hi();  // not truncated since morally the interval boundaries should already have the right precision
        double y = f(sample);
        // y = truncate(y, -30);

        measurements.insert(y);

        if (!std::isnan(y)) {
            if (y < y0) {
                y0 = y;
            }
            if (y > y1) {
                y1 = y;
            }
        }

        for (int m = 0; m < M; m++) {                         // M measurements
            double presample = rx(generator);                 // non-truncated sample
            sample           = truncate(presample, D.lsb());  // truncated sample
            double pre_y     = f(presample);
            y                = f(sample);
            // y         = truncate(y, -30); // workaround to avoid artefacts in trigonometric functions

            measurements.insert(y);

            // interval bounds
            if (!std::isnan(pre_y)) {
                /* if (y < y0) {
                    y0 = y;
                }
                if (y > y1) {
                    y1 = y;
                } */
                if (pre_y < y0) {
                    y0 = pre_y;
                }
                if (pre_y > y1) {
                    y1 = pre_y;
                }
            }
        }

        double meas = *(measurements.begin());

        for (auto it = std::next(measurements.begin()); it != measurements.end(); ++it) {
            double next = *it;
            double l    = log2(next - meas);
            if (l < lsb) {
                lsb = floor(l);
            }

            meas = next;
        }

        itv::interval Y(y0, y1, lsb);
        if (y0 > y1) {
            Y = itv::interval::empty();  // if we didn't manage to draw any samples
        }
        itv::interval Z = (A.*mp)(X);

        if (Z >= Y and Z.lsb() <= Y.lsb()) {
            double precision = (Z.size() == 0) ? 1 : Y.size() / Z.size();

            std::cout << "\033[32m"
                      << "OK    " << e << ": " << title << "(" << X << ") = \n"
                      << Z << "(c)\t >= \t" << Y << "(m)\t (precision " << precision
                      << ", LSB diff = " << Y.lsb() - Z.lsb() << ")"
                      << "\033[0m" << std::endl;
        } else {
            std::cout << "\033[31m"
                      << "ERROR " << e << ": " << title << "(" << X << ") = \n"
                      << Z << "(c)\t INSTEAD OF \t" << Y << "(m), \t LSB diff = " << Y.lsb() - Z.lsb() << "\033[0m"
                      << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}

/**
 * @brief Check the binary interval function gives a good approximation of the numerical function.
 *
 * @param E number of intervals/experiments
 * @param M number of measurements used to estimate the resulting interval
 * @param title, name of the tested function
 * @param Dx maximal interval for x
 * @param Dy maximal interval for y
 * @param f the numerical function of reference
 * @param bm the interval method corresponding to f
 */

void analyzeBinaryMethod(int E, int M, const char* title, const itv::interval& Dx, const itv::interval& Dy, bfun f,
                         bmth bm)
{
    std::random_device             R;  // used to generate a random seed, based on some hardware randomness
    std::default_random_engine     generator(R());
    std::uniform_real_distribution rdx(Dx.lo(), Dx.hi());
    std::uniform_real_distribution rdy(Dy.lo(), Dy.hi());
    itv::interval_algebra          A;

    std::cout << "Analysis of " << title << " in domains " << Dx << " x " << Dy << std::endl;

    for (int e = 0; e < E; e++) {  // for each experiment

        // store output values in order to measure the output precision
        std::set<double> measurements;
        if (Dx.lsb() < 0 or Dy.lsb() < 0)  // if we're not doing an integer operation
        {
            // X: random input interval X < Dx
            double        x0 = truncate(rdx(generator), Dx.lsb());
            double        x1 = truncate(rdx(generator), Dx.lsb());
            itv::interval X(std::min(x0, x1), std::max(x0, x1), Dx.lsb());

            // Y: random input interval Y < Dy
            double        y0 = truncate(rdy(generator), Dy.lsb());
            double        y1 = truncate(rdy(generator), Dy.lsb());
            itv::interval Y(std::min(y0, y1), std::max(y0, y1), Dy.lsb());

            // boundaries of the resulting interval Z
            double zlo = HUGE_VAL;   // std::min(t0, t1);
            double zhi = -HUGE_VAL;  // std::max(t0, t1);

            // precision of the resulting interval
            int lsb = INT_MAX;

            // random values in X
            std::uniform_real_distribution rvx(X.lo(), X.hi());
            std::uniform_real_distribution rvy(Y.lo(), Y.hi());

            // draw the upper bounds manually
            double z = f(X.hi(), Y.hi());  // no need to truncate: interval boundaries are already truncated
            measurements.insert(z);

            if (!std::isnan(z)) {
                if (z < zlo) {
                    zlo = z;
                }
                if (z > zhi) {
                    zhi = z;
                }
            }

            // measure the interval Z using the numerical function f
            for (int m = 0; m < M; m++) {  // M measurements
                z = f(truncate(rvx(generator), Dx.lsb()), truncate(rvy(generator), Dy.lsb()));

                measurements.insert(z);

                if (!std::isnan(z)) {
                    if (z < zlo) {
                        zlo = z;
                    }
                    if (z > zhi) {
                        zhi = z;
                    }
                }
            }

            double meas = *(measurements.begin());

            for (auto it = std::next(measurements.begin()); it != measurements.end(); ++it) {
                double next = *it;
                double l    = log2(next - meas);
                if (l < lsb) {
                    lsb = floor(l);
                }

                meas = next;
            }

            itv::interval Zm(zlo, zhi, lsb);  // the measured Z
            if (zlo > zhi) {
                Zm = itv::interval::empty();  // if we didn't manage to draw any samples
            }
            itv::interval Zc        = (A.*bm)(X, Y);  // the computed Z
            double        precision = (Zm.size() == Zc.size()) ? 1 : Zm.size() / Zc.size();

            if (Zc >= Zm and Zc.lsb() <= Zm.lsb()) {
                std::string color = "\033[32m";
                if (precision < 0.8 or Zm.lsb() - Zc.lsb() >= 10) {
                    color = "\033[36m";  // cyan instead of green if approximation is technically correct but of poor
                                         // quality
                }
                std::cout << color << "OK    " << e << ": " << title << "(" << X << ",\t" << Y << ")\n =c=> " << Zc
                          << "(c) >= " << Zm << "(m)"
                          << "\t (precision " << precision << "), \t LSB diff = " << Zm.lsb() - Zc.lsb() << "\033[0m"
                          << std::endl;
            } else if (Zc >= Zm) {
                std::cout << "\033[33m"
                          << "WARNING " << e << ": " << title << "(" << X << ",\t" << Y << ")\n =c=> " << Zc
                          << "(c) >= " << Zm << "(m)"
                          << "\t LSB diff = " << Zm.lsb() - Zc.lsb() << "\033[0m" << std::endl;
            } else {
                std::cout << "\033[31m"
                          << "ERROR " << e << ": " << title << "(" << X << ",\t" << Y << ")\n =c=> " << Zc << "(c) < "
                          << Zm << "(m)"
                          << "\t LSB diff = " << Zm.lsb() - Zc.lsb() << "\033[0m" << std::endl;
            }
        } else {  // integer operation
            // std::cout << "Testing integer version of " << title << std::endl;
            // X: random input interval X < Dx
            double        x0 = truncate(rdx(generator), Dx.lsb());
            double        x1 = truncate(rdx(generator), Dx.lsb());
            itv::interval X(std::min(x0, x1), std::max(x0, x1), Dx.lsb());

            // Y: random input interval Y < Dy
            double        y0 = truncate(rdy(generator), Dy.lsb());
            double        y1 = truncate(rdy(generator), Dy.lsb());
            itv::interval Y(std::min(y0, y1), std::max(y0, y1), Dy.lsb());

            // boundaries of the resulting interval Z
            int zlo = INT_MAX;  // std::min(t0, t1);
            int zhi = INT_MIN;  // std::max(t0, t1);

            // precision of the resulting interval
            int lsb = INT_MAX;

            // random values in X and Y
            std::uniform_int_distribution ivx((int)X.lo(), (int)X.hi());
            std::uniform_int_distribution ivy((int)Y.lo(), (int)Y.hi());

            // draw the upper bounds manually
            int z = f(X.hi(), Y.hi());  // no need to truncate: interval boundaries are already truncated
            measurements.insert((double)z);

            if (z < zlo) {
                zlo = z;
            }
            if (z > zhi) {
                zhi = z;
            }

            // measure the interval Z using the numerical function f
            for (int m = 0; m < M; m++) {  // M measurements
                int pre_x = ivx(generator);
                int x     = truncate(pre_x, Dx.lsb());
                int pre_y = ivy(generator);
                int y     = truncate(pre_y, Dy.lsb());
                z         = f(x, y);
                int pre_z = f(pre_x, pre_y);

                measurements.insert(z);

                if (!std::isnan(pre_z)) {
                    if (z < zlo) {
                        zlo = pre_z;
                    }
                    if (z > zhi) {
                        zhi = pre_z;
                    }
                }
            }

            double meas = *(measurements.begin());

            for (auto it = std::next(measurements.begin()); it != measurements.end(); ++it) {
                double next = *it;
                double l    = log2(next - meas);
                if (l < lsb) {
                    lsb = floor(l);
                }

                meas = next;
            }

            itv::interval Zm(zlo, zhi, lsb);          // the measured Z
            itv::interval Zc        = (A.*bm)(X, Y);  // the computed Z
            double        precision = (Zm.size() == Zc.size()) ? 1 : Zm.size() / Zc.size();

            if (Zc >= Zm and Zc.lsb() <= Zm.lsb()) {
                std::string color = "\033[32m";
                if (precision < 0.8 or Zm.lsb() - Zc.lsb() >= 10) {
                    color = "\033[36m";  // cyan instead of green if approximation is technically correct but of poor
                                         // quality
                }
                std::cout << color << "OK    " << e << ": " << title << "(" << X << ",\t" << Y << ")\n =c=> " << Zc
                          << "(c) >= " << Zm << "(m)"
                          << "\t (precision " << precision << "), \t LSB diff = " << Zm.lsb() - Zc.lsb() << "\033[0m"
                          << std::endl;
            } else if (Zc >= Zm) {
                std::string color = "\033[33m";

                std::cout << color << "WARNING    " << e << ": " << title << "(" << X << ",\t" << Y << ")\n =c=> " << Zc
                          << "(c) >= " << Zm << "(m)"
                          << "\t (precision " << precision << "), \t LSB diff = " << Zm.lsb() - Zc.lsb() << "\033[0m"
                          << std::endl;
            } else {
                std::cout << "\033[31m"
                          << "ERROR " << e << ": " << title << "(" << X << ",\t" << Y << ")\n =c=> " << Zc << "(c) < "
                          << Zm << "(m)"
                          << "\t LSB diff = " << Zm.lsb() - Zc.lsb() << "\033[0m" << std::endl;
            }
        }
    }
    std::cout << std::endl;
}

/**
 * @brief Adjusts the lsb of an input interval to match a target output lsb
 *
 * @param title name of the tested function
 * @param mp the interval method of the studied function
 * @param X the input interval
 * @param l the target lsb for the output
 */
void propagateBackwardsUnaryMethod(const char* title, umth mp, itv::interval& X, int l)
{
    std::cout << "Shaving input " << X << " of " << title << " to achieve an output lsb of " << l << std::endl;

    itv::interval_algebra A;
    // itv::interval X = itv::interval(D.lo(), D.hi(), D.lsb());
    itv::interval Z = (A.*mp)(X);

    while (Z.lsb() < l)  // the lsb of Z is more precise than l
    {
        X = itv::interval(X.lo(), X.hi(), X.lsb() + 1);
        Z = (A.*mp)(X);
        std::cout << X.lsb() << " -> " << Z.lsb() << std::endl;
    }

    if (Z.lsb() > l) {  // if we've overshot the target lsb
        X = itv::interval(X.lo(), X.hi(), X.lsb() - 1);
    }

    std::cout << "Input interval " << X << " is sufficient" << std::endl;
}

/**
 * @brief Adjusts the lsbs of two input intervals to a binary function to match a target output lbs
 *
 * @param title name of the tested function
 * @param bm the interval method of the studied function
 * @param X the first input interval
 * @param Y the second input interval
 * @param l the target lsb for the output
 */
void propagateBackwardsBinaryMethod(const char* title, bmth bm, itv::interval& X, itv::interval& Y, int l)
{
    std::cout << "Shaving inputs " << X << " and " << Y << " of " << title << " to achieve an output lsb of " << l
              << std::endl;

    itv::interval_algebra A;

    itv::interval Z = (A.*bm)(X, Y);

    while (Z.lsb() < l) {
        // std::cout << "X = " << X << "; Y = " << Y << std::endl;
        if (X.lsb() < Y.lsb()) {
            X = itv::interval(X.lo(), X.hi(), X.lsb() + 1);
            std::cout << "Shaving interval X = " << X << std::endl;
        } else {
            Y = itv::interval(Y.lo(), Y.hi(), Y.lsb() + 1);
            std::cout << "Shaving interval Y = " << Y << std::endl;
        }
        Z = (A.*bm)(X, Y);
    }

    std::cout << "Input intervals " << X << " and " << Y << " are sufficient" << std::endl;
}

/**
 * @brief Adjusts the lsb of an input iterval to a list of composed functions to match a target output lsb
 *
 * @param titles names of the tested functions, from outermost to innermost
 * @param mps the interval methods of the functions, from outermost to innermost
 * @param X the input interval
 * @param l the target lsb for the output
 */
void propagateBackwardsComposition(std::vector<const char*> titles, std::vector<umth> mps, itv::interval& X, int l)
{
    if (titles.size() != mps.size()) {
        std::cout << "Incompatible vector sizes" << std::endl;
        return;
    }

    unsigned long n = titles.size();

    std::cout << "Shaving input " << X << " of ";
    for (const auto* t : titles) {
        std::cout << t << " ○ ";
    }
    std::cout << "\b\b\b";
    std::cout << " to achieve an output lsb of " << l << std::endl << std::endl;

    itv::interval_algebra      A;
    std::vector<itv::interval> intermediate_intervals{X};  // should be one element bigger than titles and mps

    for (int i = 0; i < n; i++) {
        intermediate_intervals.push_back((A.*(mps[n - i - 1]))(intermediate_intervals[i]));
        std::cout << titles[n - i - 1] << "(" << intermediate_intervals[i] << ") = " << intermediate_intervals[i + 1]
                  << std::endl;
    }

    std::cout << std::endl << "Intermediate intervals before shaving:" << std::endl;

    for (auto Y : intermediate_intervals) {
        std::cout << Y << std::endl;
    }

    std::cout << std::endl;
    int li = l;

    for (int i = 0; i < n - 1; i++) {
        propagateBackwardsUnaryMethod(titles[i], mps[i], intermediate_intervals[n - i - 1], li);
        li = intermediate_intervals[n - i - 1].lsb();
        std::cout << std::endl;
    }
    propagateBackwardsUnaryMethod(titles[n - 1], mps[n - 1], X, li);
    // propagateBackwardsUnaryMethod(titles[0], mps[0], X, li);
    // propagateBackwardsUnaryMethod(titles[1], mps[1], X, intermediate_intervals[1].lsb());

    std::cout << std::endl;

    itv::interval Y = X;

    for (int i = 0; i < n; i++) {
        std::cout << titles[n - i - 1] << "(" << Y << ") = ";
        Y = (A.*mps[n - i - 1])(Y);
        std::cout << Y << std::endl;
    }

    std::cout << std::endl << "Intermediate intervals after shaving:" << std::endl;

    std::cout << X << std::endl;
    for (auto Y : intermediate_intervals) {
        std::cout << Y << std::endl;
    }
}