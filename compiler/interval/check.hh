#pragma once

#include <string>
#include <vector>

#include "interval_algebra.hh"
#include "interval_def.hh"
#include "utils.hh"

bool const taylor_lsb = false; // flag that tells us to always compute the LSB using a Taylor expansion of the function 
                              // instead of going for the exact computation

void check(const std::string& testname, const itv::interval& exp);

void check(const std::string& testname, const itv::interval& exp, const itv::interval& res);

void check(const std::string& testname, bool exp, bool res);

using ufun = double (*)(double);
using bfun = double (*)(double, double);

using umth = itv::interval (itv::interval_algebra::*)(const itv::interval& x);
using bmth = itv::interval (itv::interval_algebra::*)(const itv::interval& x, const itv::interval& y);

itv::interval testfun(int N, bfun f, const itv::interval& x, const itv::interval& y);
void          analyzemod(itv::interval x, itv::interval y);

int exactPrecisionUnary(ufun f, long double x, long double u);

void analyzeUnaryFunction(int E, int M, const char* title, const itv::interval& D, ufun f);
void analyzeUnaryMethod(int E, int M, const char* title, const itv::interval& D, ufun f, umth m);

void analyzeBinaryMethod(int E, int M, const char* title, const itv::interval& C, const itv::interval& D, bfun f,
                         bmth m);

void propagateBackwardsUnaryMethod(const char* title, umth f, itv::interval& X, int l);
void propagateBackwardsComposition(std::vector<const char*> titles, std::vector<umth> mps, itv::interval& X, int l);