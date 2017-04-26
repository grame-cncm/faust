ifndef MESHER
MESHER=MESHER

ifndef CLEANFOLDER
CLEANFOLDER=MESHER
endif

R ?= ../..
include $(R)/Makefile-headers/Makefile-header

# the object files to be compiled for this library
MESHER_OBJECTS=delaunayMesher.o isosurfaceMesher.o tetMesher.o triangleTetIntersection.o

# the libraries this library depends on
MESHER_LIBS=distanceField minivector objMesh volumetricMesh windingNumber performanceCounter wildMagic/geometryQuery wildMagic/meshKey wildMagic/rational

# the headers in this library
MESHER_HEADERS=delaunayMesher.h isosurfaceMesher.h tetMesher.h triangleTetIntersection.h

MESHER_OBJECTS_FILENAMES=$(addprefix $(L)/mesher/, $(MESHER_OBJECTS))
MESHER_HEADER_FILENAMES=$(addprefix $(L)/mesher/, $(MESHER_HEADERS))
MESHER_LIB_MAKEFILES=$(call GET_LIB_MAKEFILES, $(MESHER_LIBS))
MESHER_LIB_FILENAMES=$(call GET_LIB_FILENAMES, $(MESHER_LIBS))

include $(MESHER_LIB_MAKEFILES)

all: $(L)/mesher/libmesher.a

$(L)/mesher/libmesher.a: $(MESHER_OBJECTS_FILENAMES)
	ar r $@ $^; cp $@ $(L)/lib; cp $(L)/mesher/*.h $(L)/include

$(MESHER_OBJECTS_FILENAMES): %.o: %.cpp $(MESHER_LIB_FILENAMES) $(MESHER_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $< -o $@

ifeq ($(CLEANFOLDER), MESHER)
clean: cleanmesher
endif

deepclean: cleanmesher

cleanmesher:
	$(RM) $(MESHER_OBJECTS_FILENAMES) $(L)/mesher/libmesher.a

endif

	
