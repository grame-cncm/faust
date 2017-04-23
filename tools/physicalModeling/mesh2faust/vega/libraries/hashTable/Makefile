ifndef HASHTABLE
HASHTABLE=HASHTABLE

ifndef CLEANFOLDER
CLEANFOLDER=HASHTABLE
endif

R ?= ../..
include $(R)/Makefile-headers/Makefile-header

# the object files to be compiled for this library
HASHTABLE_OBJECTS=hashTable.o

# the libraries this library depends on
HASHTABLE_LIBS=

# the headers in this library
HASHTABLE_HEADERS=hashTable.h

HASHTABLE_OBJECTS_FILENAMES=$(addprefix $(L)/hashTable/, $(HASHTABLE_OBJECTS))
HASHTABLE_HEADER_FILENAMES=$(addprefix $(L)/hashTable/, $(HASHTABLE_HEADERS))
HASHTABLE_LIB_MAKEFILES=$(call GET_LIB_MAKEFILES, $(HASHTABLE_LIBS))
HASHTABLE_LIB_FILENAMES=$(call GET_LIB_FILENAMES, $(HASHTABLE_LIBS))

include $(HASHTABLE_LIB_MAKEFILES)

all: $(L)/hashTable/libhashTable.a

$(L)/hashTable/libhashTable.a: $(HASHTABLE_OBJECTS_FILENAMES)
	ar r $@ $^; cp $@ $(L)/lib; cp $(L)/hashTable/*.h $(L)/include

$(HASHTABLE_OBJECTS_FILENAMES): %.o: %.cpp $(HASHTABLE_LIB_FILENAMES) $(HASHTABLE_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $< -o $@

ifeq ($(CLEANFOLDER), HASHTABLE)
clean: cleanhashTable
endif

deepclean: cleanhashTable

cleanhashTable:
	$(RM) $(HASHTABLE_OBJECTS_FILENAMES) $(L)/hashTable/libhashTable.a

endif

