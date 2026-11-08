CXX ?= c++
CXXFLAGS ?= -std=c++17 -Wall -I../../architecture

TEST = mapui_index_test

.PHONY: all check clean

all: $(TEST)

$(TEST): $(TEST).cpp ../../architecture/faust/gui/MapUI.h ../../architecture/faust/gui/PathBuilder.h
	$(CXX) $(CXXFLAGS) $(TEST).cpp -o $(TEST)

check: $(TEST)
	./$(TEST)

clean:
	rm -f $(TEST)
