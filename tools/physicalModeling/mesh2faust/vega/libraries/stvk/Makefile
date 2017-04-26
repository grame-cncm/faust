ifndef STVK
STVK=STVK

ifndef CLEANFOLDER
CLEANFOLDER=STVK
endif

R ?= ../..
include $(R)/Makefile-headers/Makefile-header

# the object files to be compiled for this library
STVK_OBJECTS=StVKCubeABCD.o StVKElementABCD.o StVKElementABCDLoader.o StVKHessianTensor.o StVKInternalForces.o StVKInternalForcesMT.o StVKStiffnessMatrix.o StVKStiffnessMatrixMT.o StVKTetABCD.o StVKTetHighMemoryABCD.o 

# the libraries this library depends on
STVK_LIBS=minivector volumetricMesh sparseMatrix

# the headers in this library
STVK_HEADERS=StVKCubeABCD.h StVKElementABCD.h StVKElementABCDLoader.h StVKHessianTensor.h StVKInternalForces.h StVKInternalForcesMT.h StVKStiffnessMatrix.h StVKStiffnessMatrixMT.h StVKTetABCD.h StVKTetHighMemoryABCD.h

STVK_OBJECTS_FILENAMES=$(addprefix $(L)/stvk/, $(STVK_OBJECTS))
STVK_HEADER_FILENAMES=$(addprefix $(L)/stvk/, $(STVK_HEADERS))
STVK_LIB_MAKEFILES=$(call GET_LIB_MAKEFILES, $(STVK_LIBS))
STVK_LIB_FILENAMES=$(call GET_LIB_FILENAMES, $(STVK_LIBS))

include $(STVK_LIB_MAKEFILES)

all: $(L)/stvk/libstvk.a

$(L)/stvk/libstvk.a: $(STVK_OBJECTS_FILENAMES)
	ar r $@ $^; cp $@ $(L)/lib; cp $(L)/stvk/*.h $(L)/include

$(STVK_OBJECTS_FILENAMES): %.o: %.cpp $(STVK_LIB_FILENAMES) $(STVK_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $< -o $@

ifeq ($(CLEANFOLDER), STVK)
clean: cleanstvk
endif

deepclean: cleanstvk

cleanstvk:
	$(RM) $(STVK_OBJECTS_FILENAMES) $(L)/stvk/libstvk.a

endif
