ifndef GRAPH
GRAPH=GRAPH

ifndef CLEANFOLDER
CLEANFOLDER=GRAPH
endif

R ?= ../..
include $(R)/Makefile-headers/Makefile-header

# the object files to be compiled for this library
GRAPH_OBJECTS=graph.o

# the libraries this library depends on
GRAPH_LIBS=matrixIO sparseMatrix

# the headers in this library
GRAPH_HEADERS=graph.h

GRAPH_OBJECTS_FILENAMES=$(addprefix $(L)/graph/, $(GRAPH_OBJECTS))
GRAPH_HEADER_FILENAMES=$(addprefix $(L)/graph/, $(GRAPH_HEADERS))
GRAPH_LIB_MAKEFILES=$(call GET_LIB_MAKEFILES, $(GRAPH_LIBS))
GRAPH_LIB_FILENAMES=$(call GET_LIB_FILENAMES, $(GRAPH_LIBS))

include $(GRAPH_LIB_MAKEFILES)

all: $(L)/graph/libgraph.a

$(L)/graph/libgraph.a: $(GRAPH_OBJECTS_FILENAMES)
	ar r $@ $^; cp $@ $(L)/lib; cp $(L)/graph/*.h $(L)/include

$(GRAPH_OBJECTS_FILENAMES): %.o: %.cpp $(GRAPH_LIB_FILENAMES) $(GRAPH_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $< -o $@

ifeq ($(CLEANFOLDER), GRAPH)
clean: cleangraph
endif

deepclean: cleangraph

cleangraph:
	$(RM) $(GRAPH_OBJECTS_FILENAMES) $(L)/graph/libgraph.a

endif
