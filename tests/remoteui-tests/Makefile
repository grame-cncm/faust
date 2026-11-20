# RemoteUI (architecture/faust/gui/RemoteUI.h, RemoteHost.h, RemoteSocket.h)
#
#   make check     the host's unit tests (no network, no DSP), then a check
#                  that RemoteUI compiles in an architecture with a real DSP
#
# The comparison with faustwasm's own host, on the wire, is in faustwasm:
#   FAUST_SOURCE_DIR=<this repository> node --test test/cli/remote-native.test.mjs

CXX ?= c++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wno-unused-parameter -I../../architecture
FAUST ?= ../../build/bin/faust

GUI = ../../architecture/faust/gui
HEADERS = $(GUI)/RemoteHost.h $(GUI)/RemoteSocket.h

.PHONY: all check clean

all: remote_host_test remote_test

remote_host_test: remote_host_test.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) remote_host_test.cpp -o remote_host_test

# remote_host.cpp is a test architecture: no audio device, RemoteUI on the command line's -remote
remote_test: remote_host.cpp remote_test.dsp $(HEADERS) $(GUI)/RemoteUI.h
	$(FAUST) -a remote_host.cpp -I ../../architecture remote_test.dsp -o remote_test.cpp
	$(CXX) $(CXXFLAGS) -Wno-unused-function -Wno-cast-function-type-mismatch remote_test.cpp -o remote_test -lpthread

check: remote_host_test remote_test
	./remote_host_test
	./remote_test 2>/dev/null; test $$? -eq 1

clean:
	rm -f remote_host_test remote_test remote_test.cpp
