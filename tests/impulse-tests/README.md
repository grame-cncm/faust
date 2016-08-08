# Test Code Generation #

This test suite allows to check that the compiler generates correct code by comparing the impulse response of a set of Faust programs with the expected one.

- First make sure you have installed the varipus `impulsearchXX.cpp` architecture files and the `faust2impulseXX` scripts. Use for that the command: `sudo ./install.sh`
	
- Then use `./test.sh` to compile and run all the programs in `codes-to-test/` and compare the impulse reponses produced with the expected one stored in `expected-responses/`. The impulse reponses should be the same.

- After changing to `codes-to-test/`, run the script `./makeReferenceImpulses.sh` to update the expected impulse responses in `codes-to-test/`.
