ifndef MESHKEY
MESHKEY=MESHKEY

ifndef CLEANFOLDER
CLEANFOLDER=MESHKEY
endif

R ?= ../../..
include $(R)/Makefile-headers/Makefile-header

# the object files to be compiled for this library
MESHKEY_OBJECTS=triKey.o tetKey.o

# the libraries this library depends on
MESHKEY_LIBS=

# the headers in this library
MESHKEY_HEADERS=triKey.h tetKey.h 

MESHKEY_OBJECTS_FILENAMES=$(addprefix $(L)/wildMagic/meshKey/, $(MESHKEY_OBJECTS))
MESHKEY_HEADER_FILENAMES=$(addprefix $(L)/wildMagic/meshKey/, $(MESHKEY_HEADERS))
MESHKEY_LIB_MAKEFILES=$(call GET_LIB_MAKEFILES, $(MESHKEY_LIBS))
MESHKEY_LIB_FILENAMES=$(call GET_LIB_FILENAMES, $(MESHKEY_LIBS))

include $(MESHKEY_LIB_MAKEFILES)

all: $(L)/wildMagic/meshKey/libmeshKey.a

$(L)/wildMagic/meshKey/libmeshKey.a: $(MESHKEY_OBJECTS_FILENAMES)
	ar r $@ $^; cp $@ $(L)/lib; cp $(L)/wildMagic/meshKey/*.h $(L)/include

$(MESHKEY_OBJECTS_FILENAMES): %.o: %.cpp $(MESHKEY_LIB_FILENAMES) $(MESHKEY_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $< -o $@

ifeq ($(CLEANFOLDER), MESHKEY)
clean: cleanmeshKey
endif

deepclean: cleanmeshKey

cleanmeshKey:
	$(RM) $(MESHKEY_OBJECTS_FILENAMES) $(L)/wildMagic/meshKey/libmeshKey.a

endif
	
