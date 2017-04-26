ifndef OBJMESH
OBJMESH=OBJMESH

ifndef CLEANFOLDER
CLEANFOLDER=OBJMESH
endif

R ?= ../..
include $(R)/Makefile-headers/Makefile-header

# the object files to be compiled for this library
OBJMESH_OBJECTS=objMeshBinaryLoader.o objMesh.o objMesh-disjointSet.o objMeshRender.o objMeshEncode.o objMeshOctree.o objMeshOffsetVoxels.o objMeshOrientable.o octree.o boundingBox.o simpleSphere.o triangle.o tribox3.o objMeshGraph.o objMeshClose.o 

# the libraries this library depends on
OBJMESH_LIBS=minivector matrixIO graph imageIO

# the headers in this library
OBJMESH_HEADERS=objMeshBinaryLoader.h objMesh.h objMesh-disjointSet.h objMeshRender.h objMeshEncode.h objMeshOctree.h objMeshOffsetVoxels.h objMeshOrientable.h octree.h boundingBox.h simpleSphere.h triangle.h tribox3.h objMeshGraph.h objMeshClose.h 

OBJMESH_OBJECTS_FILENAMES=$(addprefix $(L)/objMesh/, $(OBJMESH_OBJECTS))
OBJMESH_HEADER_FILENAMES=$(addprefix $(L)/objMesh/, $(OBJMESH_HEADERS))
OBJMESH_LIB_MAKEFILES=$(call GET_LIB_MAKEFILES, $(OBJMESH_LIBS))
OBJMESH_LIB_FILENAMES=$(call GET_LIB_FILENAMES, $(OBJMESH_LIBS))

include $(OBJMESH_LIB_MAKEFILES)

all: $(L)/objMesh/libobjMesh.a

$(L)/objMesh/libobjMesh.a: $(OBJMESH_OBJECTS_FILENAMES)
	ar r $@ $^; cp $@ $(L)/lib; cp $(L)/objMesh/*.h $(L)/include

$(OBJMESH_OBJECTS_FILENAMES): %.o: %.cpp $(OBJMESH_LIB_FILENAMES) $(OBJMESH_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $< -o $@

ifeq ($(CLEANFOLDER), OBJMESH)
clean: cleanobjMesh
endif

deepclean: cleanobjMesh

cleanobjMesh:
	$(RM) $(OBJMESH_OBJECTS_FILENAMES) $(L)/objMesh/libobjMesh.a

endif
