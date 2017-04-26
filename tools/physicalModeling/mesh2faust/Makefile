ifndef MESH2FAUST
MESH2FAUST=MESH2FAUST

ifndef CLEANFOLDER
CLEANFOLDER=MESH2FAUST
endif

include vega/Makefile-headers/Makefile-header
R ?= vega


# the object files to be compiled for this utility
#MESH2FAUST_OBJECTS=

MESH2FAUST_LIBS=minivector mesher windingNumber volumetricMesh stvk sparseSolver sparseMatrix objMesh matrix matrixIO

# the headers in this utility
#MESH2FAUST_HEADERS=

# TODO: this ight need some cleaning
MESH2FAUST_LINK=$(addprefix -l, $(MESH2FAUST_LIBS)) $(ARPACK_LIB) $(BLASLAPACK_LIB) $(PARDISO_LIB) $(STANDARD_LIBS)

#MESH2FAUST_OBJECTS_FILENAMES=$(addprefix $(R)/src/, $(MESH2FAUST_OBJECTS))
MESH2FAUST_HEADER_FILENAMES=$(addprefix $(R)/src/, $(MESH2FAUST_HEADERS))
MESH2FAUST_LIB_MAKEFILES=$(call GET_LIB_MAKEFILES, $(MESH2FAUST_LIBS))
MESH2FAUST_LIB_FILENAMES=$(call GET_LIB_FILENAMES, $(MESH2FAUST_LIBS))

include $(MESH2FAUST_LIB_MAKEFILES)

all: vega/libraries/wildMagic/rational vega/libraries/wildMagic/meshKey vega/libraries/wildMagic/geometryQuery src/mesh2faust

src/mesh2faust: src/mesh2faust.cpp
	$(CXXLD) $(LDFLAGS) $(INCLUDE) $(MESH2FAUST_OBJECTS) src/mesh2faust.cpp $(MESH2FAUST_LINK) -lgeometryQuery -lmeshKey -lrational -o $@

#$(MESH2FAUST_OBJECTS_FILENAMES): %.o: %.cpp $(MESH2FAUST_LIB_FILENAMES) $(MESH2FAUST_HEADER_FILENAMES)
#	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $< -o $@

ifeq ($(CLEANFOLDER), MESH2FAUST)
clean: cleanMeshToFaust
endif

install:
	cp src/mesh2faust /usr/local/bin

deepclean: cleanMeshToFaust

cleanMeshToFaust:
	$(RM) $(MESH2FAUST_OBJECTS_FILENAMES) src/mesh2faust

endif
