CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic -g
LDFLAGS  ?=

ROOT_DIR := ../..
BIN_DIR  := build
TARGET   := $(BIN_DIR)/file_resolver_tests

SRCS := test_file_resolver.cpp

all: run

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(TARGET): $(SRCS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I$(ROOT_DIR) $(SRCS) -o $(TARGET) $(LDFLAGS)

.PHONY: run
run: $(TARGET)
	$(TARGET)

.PHONY: baseline
baseline: run

.PHONY: clean
clean:
	@rm -rf $(BIN_DIR)
