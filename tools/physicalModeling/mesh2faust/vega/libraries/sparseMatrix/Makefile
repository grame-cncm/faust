ifndef SPARSEMATRIX
SPARSEMATRIX=SPARSEMATRIX

ifndef CLEANFOLDER
CLEANFOLDER=SPARSEMATRIX
endif

R ?= ../..
include $(R)/Makefile-headers/Makefile-header

# the object files to be compiled for this library
SPARSEMATRIX_OBJECTS=sparseMatrix.o sparseMatrixMT.o

# the libraries this library depends on
SPARSEMATRIX_LIBS=

# the headers in this library
SPARSEMATRIX_HEADERS=sparseMatrix.h sparseMatrixMT.h

SPARSEMATRIX_OBJECTS_FILENAMES=$(addprefix $(L)/sparseMatrix/, $(SPARSEMATRIX_OBJECTS))
SPARSEMATRIX_HEADER_FILENAMES=$(addprefix $(L)/sparseMatrix/, $(SPARSEMATRIX_HEADERS))
SPARSEMATRIX_LIB_MAKEFILES=$(call GET_LIB_MAKEFILES, $(SPARSEMATRIX_LIBS))
SPARSEMATRIX_LIB_FILENAMES=$(call GET_LIB_FILENAMES, $(SPARSEMATRIX_LIBS))

include $(SPARSEMATRIX_LIB_MAKEFILES)

all: $(L)/sparseMatrix/libsparseMatrix.a

$(L)/sparseMatrix/libsparseMatrix.a: $(SPARSEMATRIX_OBJECTS_FILENAMES)
	ar r $@ $^; cp $@ $(L)/lib; cp $(L)/sparseMatrix/*.h $(L)/include

$(SPARSEMATRIX_OBJECTS_FILENAMES): %.o: %.cpp $(SPARSEMATRIX_LIB_FILENAMES) $(SPARSEMATRIX_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $< -o $@

ifeq ($(CLEANFOLDER), SPARSEMATRIX)
clean: cleansparseMatrix
endif

deepclean: cleansparseMatrix

cleansparseMatrix:
	$(RM) $(SPARSEMATRIX_OBJECTS_FILENAMES) $(L)/sparseMatrix/libsparseMatrix.a

endif
