ifndef GEOMETRYQUERY
GEOMETRYQUERY=GEOMETRYQUERY

ifndef CLEANFOLDER
CLEANFOLDER=GEOMETRYQUERY
endif

R ?= ../../..
include $(R)/Makefile-headers/Makefile-header

# the object files to be compiled for this library
GEOMETRYQUERY_OBJECTS=verticesQuery.o verticesQueryRational.o verticesQueryFiltered.o

# the libraries this library depends on
GEOMETRYQUERY_LIBS=minivector wildMagic/meshKey wildMagic/rational

# the headers in this library
GEOMETRYQUERY_HEADERS=verticesQuery.h verticesQueryRational.h query.h verticesQueryFiltered.h

GEOMETRYQUERY_OBJECTS_FILENAMES=$(addprefix $(L)/wildMagic/geometryQuery/, $(GEOMETRYQUERY_OBJECTS))
GEOMETRYQUERY_HEADER_FILENAMES=$(addprefix $(L)/wildMagic/geometryQuery/, $(GEOMETRYQUERY_HEADERS))
GEOMETRYQUERY_LIB_MAKEFILES=$(call GET_LIB_MAKEFILES, $(GEOMETRYQUERY_LIBS))
GEOMETRYQUERY_LIB_FILENAMES=$(call GET_LIB_FILENAMES, $(GEOMETRYQUERY_LIBS))

include $(GEOMETRYQUERY_LIB_MAKEFILES)

all: $(L)/wildMagic/geometryQuery/libgeometryQuery.a

$(L)/wildMagic/geometryQuery/libgeometryQuery.a: $(GEOMETRYQUERY_OBJECTS_FILENAMES)
	ar r $@ $^; cp $@ $(L)/lib; cp $(L)/wildMagic/geometryQuery/*.h $(L)/include

$(GEOMETRYQUERY_OBJECTS_FILENAMES): %.o: %.cpp $(GEOMETRYQUERY_LIB_FILENAMES) $(GEOMETRYQUERY_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $< -o $@
#	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $(WILDMAGIC_INCLUDE) $< -o $@

ifeq ($(CLEANFOLDER), GEOMETRYQUERY)
clean: cleangeometryQuery
endif

deepclean: cleangeometryQuery

cleangeometryQuery:
	$(RM) $(GEOMETRYQUERY_OBJECTS_FILENAMES) $(L)/wildMagic/geometryQuery/libgeometryQuery.a

endif
	
