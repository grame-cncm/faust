
# FAUST architecture tests #

We test here that `faust2xx` scripts correctly work:

- `testfailure`: tests that all `faust2xxx` scripts correctly fails and report error when there 
  is an error either in the Faust code, or in the generated C++ code. For that purpose we
  use 'badfaust.dsp' and 'badcpp.dsp' (correct Faust code but bad generate c++ code).
- `testsuccess`: tests that `faust2xxx` scripts correctly compile 'good.dsp' or 'sound.dsp', running on macOS and Linux
- `testsuccessrenamed`: tests that `faust2xxx` scripts correctly compile 'good.dsp' or 'sound.dsp' with renamed class and superclass, running on macOS and Linux
- `testserver`: tests that some `faust2xxx` scripts correctly compile 'good.dsp' on the Faust server
- `testtravis`: tests that some `faust2xxx` scripts correctly compile 'good.dsp' using Travis CI tool (not yet in production)
