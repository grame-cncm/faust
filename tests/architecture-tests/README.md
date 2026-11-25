
# FAUST architecture tests #

We test here that `faust2xx` scripts correctly work:

- `testfailure`: tests that all `faust2xxx` scripts correctly fails and report error when there 
  is an error either in the Faust code, or in the generated C++ code. For that purpose we
  use 'badfaust.dsp' and 'badcpp.dsp' (correct Faust code but bad generate c++ code).
- `testsuccess`: tests that `faust2xxx` scripts correctly compile 'good.dsp' or 'sound.dsp', running on macOS and Linux
- `testsuccessrenamed`: tests that `faust2xxx` scripts correctly compile 'good.dsp' or 'sound.dsp' with renamed class and superclass, running on macOS and Linux
- `testserver`: tests that some `faust2xxx` scripts correctly compile 'good.dsp' on the Faust server
- `testtravis`: tests that some `faust2xxx` scripts correctly compile 'good.dsp' using Travis CI tool (not yet in production)

The headless sample-rate adapter lifecycle regression runs with:

```sh
make -C tests/architecture-tests check-sr-adapter-reset -k -j2
```

It checks float and double adapters in both sampling directions, with all
five filter choices and factors 2, 3, 4, 8, 16, and 32. Each case repeats
three times on the same instance. After processing nonzero input, `instanceClear`,
`instanceInit`, and `init` must restore silence for zero input. It also checks
wrapped DSP reset calls, control preservation, and internal sample rates.
`ARCH` can select another checkout's architecture headers for baseline testing;
`CXX` and `CXXFLAGS` select the host compiler and optional sanitizer flags.
