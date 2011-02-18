src  := $(wildcard *.cpp)
appl := faust-mr

all :  $(appl)


faust-mr : *.cpp *.hh
	$(CXX) -O3 $(CXXFLAGS) *.cpp -o faust-mr
	

clean :
	rm -f $(appl)
