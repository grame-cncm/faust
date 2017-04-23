ifndef MINIVECTOR
MINIVECTOR=MINIVECTOR

ifndef CLEANFOLDER
CLEANFOLDER=MINIVECTOR
endif

R ?= ../..
include $(R)/Makefile-headers/Makefile-header

# the object files to be compiled for this library
MINIVECTOR_OBJECTS=mat3d.o vec3d.o vec3.o vec2d.o eig3.o

# the libraries this library depends on
MINIVECTOR_LIBS=

# the headers in this library
MINIVECTOR_HEADERS=eig3.h mat3d.h minivector.h vec2d.h vec3d.h vec3.h

MINIVECTOR_OBJECTS_FILENAMES=$(addprefix $(L)/minivector/, $(MINIVECTOR_OBJECTS))
MINIVECTOR_HEADER_FILENAMES=$(addprefix $(L)/minivector/, $(MINIVECTOR_HEADERS))
MINIVECTOR_LIB_MAKEFILES=$(call GET_LIB_MAKEFILES, $(MINIVECTOR_LIBS))
MINIVECTOR_LIB_FILENAMES=$(call GET_LIB_FILENAMES, $(MINIVECTOR_LIBS))

include $(MINIVECTOR_LIB_MAKEFILES)

all: $(L)/minivector/libminivector.a

$(L)/minivector/libminivector.a: $(MINIVECTOR_OBJECTS_FILENAMES)
	ar r $@ $^; cp $@ $(L)/lib; cp $(L)/minivector/*.h $(L)/include

$(MINIVECTOR_OBJECTS_FILENAMES): %.o: %.cpp $(MINIVECTOR_LIB_FILENAMES) $(MINIVECTOR_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $< -o $@

ifeq ($(CLEANFOLDER), MINIVECTOR)
clean: cleanminivector
endif

deepclean: cleanminivector

cleanminivector:
	$(RM) $(MINIVECTOR_OBJECTS_FILENAMES) $(L)/minivector/libminivector.a

endif
