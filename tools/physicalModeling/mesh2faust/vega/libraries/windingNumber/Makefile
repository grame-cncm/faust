ifndef WINDINGNUMBER
WINDINGNUMBER=WINDINGNUMBER

ifndef CLEANFOLDER
CLEANFOLDER=WINDINGNUMBER
endif

R ?= ../..
include $(R)/Makefile-headers/Makefile-header

# the object files to be compiled for this library
WINDINGNUMBER_OBJECTS=windingNumber.o

# the libraries this library depends on
WINDINGNUMBER_LIBS=minivector objMesh

# the headers in this library
WINDINGNUMBER_HEADERS=windingNumber.h

WINDINGNUMBER_OBJECTS_FILENAMES=$(addprefix $(L)/windingNumber/, $(WINDINGNUMBER_OBJECTS))
WINDINGNUMBER_HEADER_FILENAMES=$(addprefix $(L)/windingNumber/, $(WINDINGNUMBER_HEADERS))
WINDINGNUMBER_LIB_MAKEFILES=$(call GET_LIB_MAKEFILES, $(WINDINGNUMBER_LIBS))
WINDINGNUMBER_LIB_FILENAMES=$(call GET_LIB_FILENAMES, $(WINDINGNUMBER_LIBS))

include $(WINDINGNUMBER_LIB_MAKEFILES)

all: $(L)/windingNumber/libwindingNumber.a

$(L)/windingNumber/libwindingNumber.a: $(WINDINGNUMBER_OBJECTS_FILENAMES)
	ar r $@ $^; cp $@ $(L)/lib; cp $(L)/windingNumber/*.h $(L)/include

$(WINDINGNUMBER_OBJECTS_FILENAMES): %.o: %.cpp $(WINDINGNUMBER_LIB_FILENAMES) $(WINDINGNUMBER_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $< -o $@

ifeq ($(CLEANFOLDER), WINDINGNUMBER)
clean: cleanwindingNumber
endif

deepclean: cleanwindingNumber

cleanwindingNumber:
	$(RM) $(WINDINGNUMBER_OBJECTS_FILENAMES) $(L)/windingNumber/libwindingNumber.a

endif

	
