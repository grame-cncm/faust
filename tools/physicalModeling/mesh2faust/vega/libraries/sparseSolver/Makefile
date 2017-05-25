ifndef SPARSESOLVER
SPARSESOLVER=SPARSESOLVER

ifndef CLEANFOLDER
CLEANFOLDER=SPARSESOLVER
endif

include vega/Makefile-headers/Makefile-header
R ?= vega


# the object files to be compiled for this library
SPARSESOLVER_OBJECTS=linearSolver.o PardisoSolver.o SPOOLESSolver.o SPOOLESSolverMT.o CGSolver.o
ifneq ($(ARPACK_LIB),)
SPARSESOLVER_OBJECTS+=ARPACKSolver.o invMKSolver.o ZTAZMultiplicator.o invZTAZSolver.o invZTAZMSolver.o
endif

# the libraries this library depends on
SPARSESOLVER_LIBS=sparseMatrix
ifneq ($(ARPACK_LIB),)
SPARSESOLVER_LIBS+=matrix
endif

# the headers in this library
SPARSESOLVER_HEADERS=linearSolver.h PardisoSolver.h SPOOLESSolver.h SPOOLESSolverMT.h CGSolver.h sparseSolverAvailability.h sparseSolvers.h
ifneq ($(ARPACK_LIB),)
SPARSESOLVER_HEADERS+=ARPACKSolver.h invMKSolver.h ZTAZMultiplicator.h invZTAZSolver.h invZTAZMSolver.h
endif

SPARSESOLVER_OBJECTS_FILENAMES=$(addprefix $(L)/sparseSolver/, $(SPARSESOLVER_OBJECTS))
SPARSESOLVER_HEADER_FILENAMES=$(addprefix $(L)/sparseSolver/, $(SPARSESOLVER_HEADERS))
SPARSESOLVER_LIB_MAKEFILES=$(call GET_LIB_MAKEFILES, $(SPARSESOLVER_LIBS))
SPARSESOLVER_LIB_FILENAMES=$(call GET_LIB_FILENAMES, $(SPARSESOLVER_LIBS))

include $(SPARSESOLVER_LIB_MAKEFILES)

all: $(L)/sparseSolver/libsparseSolver.a

$(L)/sparseSolver/libsparseSolver.a: $(SPARSESOLVER_OBJECTS_FILENAMES)
	ar r $@ $^; cp $@ $(L)/lib; cp $(L)/sparseSolver/*.h $(L)/include

$(SPARSESOLVER_OBJECTS_FILENAMES): %.o: %.cpp $(SPARSESOLVER_LIB_FILENAMES) $(SPARSESOLVER_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $(SPOOLES_INCLUDE) $(PARDISO_INCLUDE) $< -o $@

ifeq ($(CLEANFOLDER), SPARSESOLVER)
clean: cleansparseSolver
endif

deepclean: cleansparseSolver

cleansparseSolver:
	$(RM) $(SPARSESOLVER_OBJECTS_FILENAMES) $(L)/sparseSolver/libsparseSolver.a

endif
