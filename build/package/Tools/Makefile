
CXXFLASGS = -std=c++11 -I../../../compiler/utils/
OBJS = exepath.o install.o


../install: $(OBJS)
	$(CXX) $(CXXFLASGS) $(OBJS) -o ../install

clean:
	rm -f ../install $(OBJS)

exepath.o : ../../../compiler/utils/exepath.cpp
	$(CXX) -c $(CXXFLASGS) ../../../compiler/utils/exepath.cpp -o exepath.o

install.o : install.cpp
	$(CXX) -c $(CXXFLASGS) install.cpp -o install.o


