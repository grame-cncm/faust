
# FAUST architecture tests #

We test here that `faust2xx` scripts correctly work:

- `testfailure`: tests that all faust2xxx scripts correctly fails and report error when there 
  is an error either in the Faust code, or in the generated C++ code. For that purpose we
  use 'badfaust.dsp' and 'badcpp.dsp' (correct Faust code but bad generate c++ code).
- `testsuccess (osx|linux)`: tests that `faust2xxx` scripts correctly compile 'good.dsp'
- `testsuccessrenamed (osx|linux)`: tests that `faust2xxx` scripts correctly compile 'good.dsp' with renamed class and superclass
- `testserver`: tests that some `faust2xxx` scripts correctly compile 'good.dsp' on the Faust server
- `testtravis`: tests that some `faust2xxx` scripts correctly compile 'good.dsp' using Travis CI tool (not yet in production)
