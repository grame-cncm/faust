ifndef RATIONAL
RATIONAL=RATIONAL

ifndef CLEANFOLDER
CLEANFOLDER=RATIONAL
endif

R ?= ../../..
include $(R)/Makefile-headers/Makefile-header

# the object files to be compiled for this library
RATIONAL_OBJECTS=rational.o integer.o 

# the libraries this library depends on
RATIONAL_LIBS=

# the headers in this library
RATIONAL_HEADERS=rational.h integer.h rVector.h

RATIONAL_OBJECTS_FILENAMES=$(addprefix $(L)/wildMagic/rational/, $(RATIONAL_OBJECTS))
RATIONAL_HEADER_FILENAMES=$(addprefix $(L)/wildMagic/rational/, $(RATIONAL_HEADERS))
RATIONAL_LIB_MAKEFILES=$(call GET_LIB_MAKEFILES, $(RATIONAL_LIBS))
RATIONAL_LIB_FILENAMES=$(call GET_LIB_FILENAMES, $(RATIONAL_LIBS))

include $(RATIONAL_LIB_MAKEFILES)

all: $(L)/wildMagic/rational/librational.a

$(L)/wildMagic/rational/librational.a: $(RATIONAL_OBJECTS_FILENAMES)
	ar r $@ $^; cp $@ $(L)/lib; cp $(L)/wildMagic/rational/*.h $(L)/include

$(RATIONAL_OBJECTS_FILENAMES): %.o: %.cpp $(RATIONAL_LIB_FILENAMES) $(RATIONAL_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $< -o $@

ifeq ($(CLEANFOLDER), RATIONAL)
clean: cleanrational
endif

deepclean: cleanrational

cleanrational:
	$(RM) $(RATIONAL_OBJECTS_FILENAMES) $(L)/wildMagic/rational/librational.a

endif
