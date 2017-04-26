ifndef MATRIXIO
MATRIXIO=MATRIXIO

ifndef CLEANFOLDER
CLEANFOLDER=MATRIXIO
endif

include vega/Makefile-headers/Makefile-header
R ?= vega

# the object files to be compiled for this library
MATRIXIO_OBJECTS=matrixIO.o multiMatrixIO.o

# the libraries this library depends on
MATRIXIO_LIBS=

# the headers in this library
MATRIXIO_HEADERS=matrixIO.h multiMatrixIO.h matrixMacros.h

MATRIXIO_OBJECTS_FILENAMES=$(addprefix $(L)/matrixIO/, $(MATRIXIO_OBJECTS))
MATRIXIO_HEADER_FILENAMES=$(addprefix $(L)/matrixIO/, $(MATRIXIO_HEADERS))
MATRIXIO_LIB_MAKEFILES=$(call GET_LIB_MAKEFILES, $(MATRIXIO_LIBS))
MATRIXIO_LIB_FILENAMES=$(call GET_LIB_FILENAMES, $(MATRIXIO_LIBS))

include $(MATRIXIO_LIB_MAKEFILES)

all: $(L)/matrixIO/libmatrixIO.a

$(L)/matrixIO/libmatrixIO.a: $(MATRIXIO_OBJECTS_FILENAMES)
	ar r $@ $^; cp $@ $(L)/lib; cp $(L)/matrixIO/*.h $(L)/include

$(MATRIXIO_OBJECTS_FILENAMES): %.o: %.cpp $(MATRIXIO_LIB_FILENAMES) $(MATRIXIO_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $< -o $@

ifeq ($(CLEANFOLDER), MATRIXIO)
clean: cleanmatrixIO
endif

deepclean: cleanmatrixIO

cleanmatrixIO:
	$(RM) $(MATRIXIO_OBJECTS_FILENAMES) $(L)/matrixIO/libmatrixIO.a

endif
