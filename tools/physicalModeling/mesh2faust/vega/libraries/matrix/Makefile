ifndef MATRIX
MATRIX=MATRIX

ifndef CLEANFOLDER
CLEANFOLDER=MATRIX
endif

R ?= ../..
include $(R)/Makefile-headers/Makefile-header

# the object files to be compiled for this library
MATRIX_OBJECTS=matrixProjection.o matrixPCA.o matrixBLAS.o matrixLAPACK.o matrix.o matrixExp.o

# the libraries this library depends on
MATRIX_LIBS=matrixIO

# the headers in this library
MATRIX_HEADERS=matrixProjection.h matrixPCA.h matrixBLAS.h matrixLAPACK.h matrix.h matrixExp.h expokit_xgpadm.h

MATRIX_OBJECTS_FILENAMES=$(addprefix $(L)/matrix/, $(MATRIX_OBJECTS))
MATRIX_HEADER_FILENAMES=$(addprefix $(L)/matrix/, $(MATRIX_HEADERS))
MATRIX_LIB_MAKEFILES=$(call GET_LIB_MAKEFILES, $(MATRIX_LIBS))
MATRIX_LIB_FILENAMES=$(call GET_LIB_FILENAMES, $(MATRIX_LIBS))

include $(MATRIX_LIB_MAKEFILES)

all: $(L)/matrix/libmatrix.a

$(L)/matrix/libmatrix.a: $(MATRIX_OBJECTS_FILENAMES)
	ar r $@ $^; cp $@ $(L)/lib; cp $(L)/matrix/*.h $(L)/include

$(L)/matrix/example: $(L)/matrix/libmatrix.a $(L)/matrix/example.cpp
	$(CXXLD) $(LDFLAGS) $(L)/matrix/example.cpp $(L)/matrix/libmatrix.a $(L)/matrixIO/libmatrixIO.a $(SPOOLES_LIB) $(PARDISO_LIB) $(STANDARD_LIBS) $(INCLUDE) -o $@

$(MATRIX_OBJECTS_FILENAMES): %.o: %.cpp $(MATRIX_LIB_FILENAMES) $(MATRIX_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) -I/usr/include/mkl $(BLASLAPACK_INCLUDE) $< -o $@

ifeq ($(CLEANFOLDER), MATRIX)
clean: cleanmatrix
endif

deepclean: cleanmatrix

cleanmatrix:
	$(RM) $(MATRIX_OBJECTS_FILENAMES) $(L)/matrix/libmatrix.a

endif
