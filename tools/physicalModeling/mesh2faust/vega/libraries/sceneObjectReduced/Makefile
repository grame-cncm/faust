ifndef SCENEOBJECTREDUCED
SCENEOBJECTREDUCED=SCENEOBJECTREDUCED

ifndef CLEANFOLDER
CLEANFOLDER=SCENEOBJECTREDUCED
endif

R ?= ../..
include $(R)/Makefile-headers/Makefile-header

# the object files to be compiled for this library
SCENEOBJECTREDUCED_OBJECTS=sceneObjectReduced.o sceneObjectReduced6DOF.o sceneObjectReducedCPU.o sceneObjectReducedCPU6DOF.o
ifneq ($(CG_LIBS),)
SCENEOBJECTREDUCED_OBJECTS+=sceneObjectReducedGPU.o sceneObjectReducedGPU6DOF.o
endif

# the libraries this library depends on
SCENEOBJECTREDUCED_LIBS=objMesh lighting minivector modalMatrix sceneObject
ifneq ($(CG_LIBS),)
SCENEOBJECTREDUCED_LIBS+=objMeshGPUDeformer
endif

# the headers in this library
SCENEOBJECTREDUCED_HEADERS=sceneObjectReduced.h sceneObjectReduced6DOF.h sceneObjectReducedCPU.h sceneObjectReducedCPU6DOF.h
ifneq ($(CG_LIBS),)
SCENEOBJECTREDUCED_HEADERS+=sceneObjectReducedGPU.h sceneObjectReducedGPU6DOF.h
endif

SCENEOBJECTREDUCED_OBJECTS_FILENAMES=$(addprefix $(L)/sceneObjectReduced/, $(SCENEOBJECTREDUCED_OBJECTS))
SCENEOBJECTREDUCED_HEADER_FILENAMES=$(addprefix $(L)/sceneObjectReduced/, $(SCENEOBJECTREDUCED_HEADERS))
SCENEOBJECTREDUCED_LIB_MAKEFILES=$(call GET_LIB_MAKEFILES, $(SCENEOBJECTREDUCED_LIBS))
SCENEOBJECTREDUCED_LIB_FILENAMES=$(call GET_LIB_FILENAMES, $(SCENEOBJECTREDUCED_LIBS))

include $(SCENEOBJECTREDUCED_LIB_MAKEFILES)

all: $(L)/sceneObjectReduced/libsceneObjectReduced.a

$(L)/sceneObjectReduced/libsceneObjectReduced.a: $(SCENEOBJECTREDUCED_OBJECTS_FILENAMES)
	ar r $@ $^; cp $@ $(L)/lib; cp $(L)/sceneObjectReduced/*.h $(L)/include

$(SCENEOBJECTREDUCED_OBJECTS_FILENAMES): %.o: %.cpp $(SCENEOBJECTREDUCED_LIB_FILENAMES) $(SCENEOBJECTREDUCED_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $(CG_INCLUDE) $(BLASLAPACK_INCLUDE) $< -o $@

ifeq ($(CLEANFOLDER), SCENEOBJECTREDUCED)
clean: cleansceneObjectReduced
endif

deepclean: cleansceneObjectReduced

cleansceneObjectReduced:
	$(RM) $(SCENEOBJECTREDUCED_OBJECTS_FILENAMES) $(L)/sceneObjectReduced/libsceneObjectReduced.a

endif

