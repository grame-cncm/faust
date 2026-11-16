CXX ?= c++
CXXFLAGS ?= -std=c++11 -Wall -ffp-contract=off -I../../architecture

TEST = valueconverter_test

.PHONY: all check clean

all: $(TEST)

$(TEST): $(TEST).cpp ../../architecture/faust/gui/ValueConverter.h
	$(CXX) $(CXXFLAGS) $(TEST).cpp -o $(TEST)

check: $(TEST)
	./$(TEST)

clean:
	rm -f $(TEST)
