
prefix ?= /usr/local

all: faust2swift

faust2swift: faust2swift.cpp
	$(CXX) -std=c++11 -O3 faust2swift.cpp -o faust2swift

install: 
	([ -e faust2swift ]) && cp faust2swift $(prefix)/bin

clean:
	rm -f faust2swift
	
