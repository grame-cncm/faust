ifndef MULTICORE
MULTICORE=MULTICORE

ifndef CLEANFOLDER
CLEANFOLDER=MULTICORE
endif

R ?= ../..
include $(R)/Makefile-headers/Makefile-header

# the object files to be compiled for this library
MULTICORE_OBJECTS=getNumCores.o multicore.o

# the libraries this library depends on
MULTICORE_LIBS=

# the headers in this library
MULTICORE_HEADERS=getNumCores.h multicore.h

MULTICORE_OBJECTS_FILENAMES=$(addprefix $(L)/multicore/, $(MULTICORE_OBJECTS))
MULTICORE_HEADER_FILENAMES=$(addprefix $(L)/multicore/, $(MULTICORE_HEADERS))
MULTICORE_LIB_MAKEFILES=$(call GET_LIB_MAKEFILES, $(MULTICORE_LIBS))
MULTICORE_LIB_FILENAMES=$(call GET_LIB_FILENAMES, $(MULTICORE_LIBS))

include $(MULTICORE_LIB_MAKEFILES)

all: $(L)/multicore/libmulticore.a

$(L)/multicore/libmulticore.a: $(MULTICORE_OBJECTS_FILENAMES)
	ar r $@ $^; cp $@ $(L)/lib; cp $(L)/multicore/*.h $(L)/include

$(MULTICORE_OBJECTS_FILENAMES): %.o: %.cpp $(MULTICORE_LIB_FILENAMES) $(MULTICORE_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $< -o $@

ifeq ($(CLEANFOLDER), MULTICORE)
clean: cleanmulticore
endif

deepclean: cleanmulticore

cleanmulticore:
	$(RM) $(MULTICORE_OBJECTS_FILENAMES) $(L)/multicore/libmulticore.a

endif

