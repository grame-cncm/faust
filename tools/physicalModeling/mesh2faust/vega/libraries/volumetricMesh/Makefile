ifndef VOLUMETRICMESH
VOLUMETRICMESH=VOLUMETRICMESH

ifndef CLEANFOLDER
CLEANFOLDER=VOLUMETRICMESH
endif

R ?= ../..
include $(R)/Makefile-headers/Makefile-header

# the object files to be compiled for this library
VOLUMETRICMESH_OBJECTS=volumetricMeshParser.o generateInterpolationMatrix.o generateMassMatrix.o generateSurfaceMesh.o generateMeshGraph.o cubicMesh.o tetMesh.o volumetricMeshLoader.o volumetricMesh.o volumetricMeshENuMaterial.o volumetricMeshMooneyRivlinMaterial.o volumetricMeshExtensions.o computeStiffnessMatrixNullspace.o volumetricMeshOrthotropicMaterial.o interpolationWeightsMultiLoad.o volumetricMeshDeformationGradient.o generateTetMeshFromCubicMesh.o generateGradientMatrix.o

# the libraries this library depends on
VOLUMETRICMESH_LIBS=sparseMatrix graph matrixIO objMesh minivector

# the headers in this library
VOLUMETRICMESH_HEADERS=volumetricMeshParser.h generateInterpolationMatrix.h generateMassMatrix.h generateSurfaceMesh.h generateMeshGraph.h cubicMesh.h tetMesh.h volumetricMesh.h volumetricMeshLoader.h volumetricMeshENuMaterial.h volumetricMeshMooneyRivlinMaterial.h volumetricMeshExtensions.h computeStiffnessMatrixNullspace.h volumetricMeshOrthotropicMaterial.h interpolationWeightsMultiLoad.h volumetricMeshDeformationGradient.h generateTetMeshFromCubicMesh.h generateGradientMatrix.h

VOLUMETRICMESH_OBJECTS_FILENAMES=$(addprefix $(L)/volumetricMesh/, $(VOLUMETRICMESH_OBJECTS))
VOLUMETRICMESH_HEADER_FILENAMES=$(addprefix $(L)/volumetricMesh/, $(VOLUMETRICMESH_HEADERS))
VOLUMETRICMESH_LIB_MAKEFILES=$(call GET_LIB_MAKEFILES, $(VOLUMETRICMESH_LIBS))
VOLUMETRICMESH_LIB_FILENAMES=$(call GET_LIB_FILENAMES, $(VOLUMETRICMESH_LIBS))

include $(VOLUMETRICMESH_LIB_MAKEFILES)

all: $(L)/volumetricMesh/libvolumetricMesh.a

$(L)/volumetricMesh/libvolumetricMesh.a: $(VOLUMETRICMESH_OBJECTS_FILENAMES)
	ar r $@ $^; cp $@ $(L)/lib; cp $(L)/volumetricMesh/*.h $(L)/include

$(VOLUMETRICMESH_OBJECTS_FILENAMES): %.o: %.cpp $(VOLUMETRICMESH_LIB_FILENAMES) $(VOLUMETRICMESH_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $< -o $@

ifeq ($(CLEANFOLDER), VOLUMETRICMESH)
clean: cleanvolumetricMesh
endif

deepclean: cleanvolumetricMesh

cleanvolumetricMesh:
	$(RM) $(VOLUMETRICMESH_OBJECTS_FILENAMES) $(L)/volumetricMesh/libvolumetricMesh.a

endif
