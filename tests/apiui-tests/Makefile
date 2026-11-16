CXX ?= c++
CXXFLAGS ?= -std=c++11 -Wall
CPPFLAGS += -I../../architecture

.PHONY: all check clean

all: sensor_mapping_test

sensor_mapping_test: sensor_mapping_test.cpp ../../architecture/faust/gui/APIUI.h ../../architecture/faust/gui/ValueConverter.h ../../architecture/faust/gui/UI.h ../../architecture/faust/gui/PathBuilder.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $< -o $@ $(LDLIBS)

check: sensor_mapping_test
	./sensor_mapping_test

clean:
	rm -f sensor_mapping_test
