#!/bin/bash

rm -f report*

echo "--------------------------------------------------------------------------------"
echo "running benchcpp(float, O0)"
clang++ -std=gnu++23 -DFAUST_TEST -DFILL_INPUTS -Wall -Wextra -pedantic -O0 -o benchcpp_bin benchcpp_test.cc && ./benchcpp_bin &> report_float_O0
echo "--------------------------------------------------------------------------------"
cat report_float_O0
echo "--------------------------------------------------------------------------------"
echo

echo "--------------------------------------------------------------------------------"
echo "running benchcpp(float, O3)"
clang++ -std=gnu++23 -DFAUST_TEST -DFILL_INPUTS -Wall -Wextra -pedantic -O3 -o benchcpp_bin benchcpp_test.cc && ./benchcpp_bin &> report_float_O3
echo "--------------------------------------------------------------------------------"
cat report_float_O3
echo "--------------------------------------------------------------------------------"
echo

echo "--------------------------------------------------------------------------------"
echo "running benchcpp(double, O0)"
clang++ -std=gnu++23 -DFAUSTFLOAT=double -DFAUST_TEST -DFILL_INPUTS -Wall -Wextra -pedantic -O0 -o benchcpp_bin benchcpp_test.cc && ./benchcpp_bin &> report_double_O0
echo "--------------------------------------------------------------------------------"
cat report_double_O0
echo "--------------------------------------------------------------------------------"
echo

echo "--------------------------------------------------------------------------------"
echo "running benchcpp(double, O3)"
clang++ -std=gnu++23 -DFAUSTFLOAT=double -DFAUST_TEST -DFILL_INPUTS -Wall -Wextra -pedantic -O3 -o benchcpp_bin benchcpp_test.cc && ./benchcpp_bin &> report_double_O3
echo "--------------------------------------------------------------------------------"
cat report_double_O3
echo "--------------------------------------------------------------------------------"
echo

rm -f benchcpp_bin
