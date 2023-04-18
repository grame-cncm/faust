#pragma once

#include <string>
#include <vector>

#include "interval_algebra.hh"
#include "interval_def.hh"
#include "utils.hh"

void check(const std::string& testname, const itv::interval& exp);

void check(const std::string& testname, const itv::interval& exp, const itv::interval& res);

void check(const std::string& testname, bool exp, bool res);

using ufun = double (*)(double);
using bfun = double (*)(double, double);

using umth = itv::interval (itv::interval_algebra::*)(const itv::interval& x) const;
using bmth = itv::interval (itv::interval_algebra::*)(const itv::interval& x, const itv::interval& y) const;

itv::interval testfun(int N, bfun f, const itv::interval& x, const itv::interval& y);
void          analyzemod(itv::interval x, itv::interval y);

int exactPrecisionUnary(ufun f, long double x, long double epsilon);

void analyzeUnaryFunction(int E, int M, const char* title, const itv::interval& D, ufun f);
void analyzeUnaryMethod(int E, int M, const char* title, const itv::interval& D, ufun f, umth m);

void analyzeBinaryMethod(int E, int M, const char* title, const itv::interval& C, const itv::interval& D, bfun f,
                         bmth m);
