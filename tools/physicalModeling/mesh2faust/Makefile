ifndef MESH2FAUST
MESH2FAUST=MESH2FAUST

ifndef CLEANFOLDER
CLEANFOLDER=MESH2FAUST
endif

include vega/Makefile-headers/Makefile-header
R ?= vega

MESH2FAUST_LIBS=mesher windingNumber volumetricMesh stvk sparseMatrix objMesh
MESH2FAUST_LINK=$(addprefix -l, $(MESH2FAUST_LIBS)) $(STANDARD_LIBS)

MESH2FAUST_HEADER_FILENAMES=$(addprefix $(R)/src/, $(MESH2FAUST_HEADERS))
MESH2FAUST_LIB_MAKEFILES=$(call GET_LIB_MAKEFILES, $(MESH2FAUST_LIBS))
MESH2FAUST_LIB_FILENAMES=$(call GET_LIB_FILENAMES, $(MESH2FAUST_LIBS))

include $(MESH2FAUST_LIB_MAKEFILES)

all: vega/libraries/wildMagic/rational vega/libraries/wildMagic/meshKey vega/libraries/wildMagic/geometryQuery src/mesh2faust

src/mesh2faust: src/mesh2faust.cpp
	$(CXXLD) $(LDFLAGS) $(INCLUDE) -I/usr/include/eigen3 -Ispectra/include $(MESH2FAUST_OBJECTS) src/mesh2faust.cpp $(MESH2FAUST_LINK) -lgeometryQuery -lmeshKey -lrational -o $@

ifeq ($(CLEANFOLDER), MESH2FAUST)
clean: cleanMeshToFaust
endif

install:
	cp src/mesh2faust /usr/local/bin

deepclean: cleanMeshToFaust

cleanMeshToFaust:
	$(RM) $(MESH2FAUST_OBJECTS_FILENAMES) src/mesh2faust

endif
