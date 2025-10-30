# Parser Test Harness

This directory contains the scaffold for the modernised parser tests:
- `Makefile` provides the `make run` / `make baseline` targets that compile and execute the current placeholder suite.
- `test_file_resolver.cpp` hosts the first unit-tests for the upcoming `FileResolver`. For now the tests only validate bookkeeping behaviour and assert that the unimplemented resolution methods throw.
- `fixtures/` bundles small DSP programs and directory layouts used by the integration tests that will be added during the rewrite.

Run `make` (or `make run`) from this directory to build the test binary and execute the suite locally.
