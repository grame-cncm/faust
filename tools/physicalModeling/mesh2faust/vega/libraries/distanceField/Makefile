ifndef DISTANCEFIELD
DISTANCEFIELD=DISTANCEFIELD

ifndef CLEANFOLDER
CLEANFOLDER=DISTANCEFIELD
endif

R ?= ../..
include $(R)/Makefile-headers/Makefile-header

# the object files to be compiled for this library
DISTANCEFIELD_OBJECTS=distanceFieldBase.o distanceField.o distanceFieldMT.o closestPointField.o distanceFieldNarrowBand.o marchingCubes.o distanceFieldCreator.o signedDistanceFieldFromPolygonSoup.o

# the libraries this library depends on
DISTANCEFIELD_LIBS=objMesh hashTable minivector performanceCounter matrixIO configFile

# the headers in this library
DISTANCEFIELD_HEADERS=distanceFieldBase.h distanceField.h distanceFieldMT.h closestPointField.h distanceFieldNarrowBand.h trilinearInterpolation.h marchingCubes.h marchingCubesTable.h distanceFieldCreator.h signedDistanceFieldFromPolygonSoup.h

DISTANCEFIELD_OBJECTS_FILENAMES=$(addprefix $(L)/distanceField/, $(DISTANCEFIELD_OBJECTS))
DISTANCEFIELD_HEADER_FILENAMES=$(addprefix $(L)/distanceField/, $(DISTANCEFIELD_HEADERS))
DISTANCEFIELD_LIB_MAKEFILES=$(call GET_LIB_MAKEFILES, $(DISTANCEFIELD_LIBS))
DISTANCEFIELD_LIB_FILENAMES=$(call GET_LIB_FILENAMES, $(DISTANCEFIELD_LIBS))

include $(DISTANCEFIELD_LIB_MAKEFILES)

all: $(L)/distanceField/libdistanceField.a

$(L)/distanceField/libdistanceField.a: $(DISTANCEFIELD_OBJECTS_FILENAMES)
	ar r $@ $^; cp $@ $(L)/lib; cp $(L)/distanceField/*.h $(L)/include

$(L)/distanceField/distanceField.o: $(L)/distanceField/distanceField.cpp $(L)/distanceField/computeField.cpp $(DISTANCEFIELD_LIB_FILENAMES) $(DISTANCEFIELD_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $< -o $@

$(L)/distanceField/distanceFieldMT.o: $(L)/distanceField/distanceFieldMT.cpp $(L)/distanceField/computeFieldMT.cpp $(DISTANCEFIELD_LIB_FILENAMES) $(DISTANCEFIELD_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $< -o $@

$(L)/distanceField/closestPointField.o: $(L)/distanceField/closestPointField.cpp $(L)/distanceField/computeField.cpp $(DISTANCEFIELD_LIB_FILENAMES) $(DISTANCEFIELD_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $< -o $@

$(L)/distanceField/distanceFieldNarrowBand.o: $(L)/distanceField/distanceFieldNarrowBand.cpp $(L)/distanceField/computeFieldNarrowBand.cpp $(DISTANCEFIELD_LIB_FILENAMES) $(DISTANCEFIELD_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $< -o $@

$(L)/distanceField/distanceFieldNarrowBandMT.o: $(L)/distanceField/distanceFieldNarrowBandMT.cpp $(L)/distanceField/computeFieldNarrowBandMT.cpp $(DISTANCEFIELD_LIB_FILENAMES) $(DISTANCEFIELD_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $< -o $@

$(L)/distanceField/%.o: $(L)/distanceField/%.cpp $(DISTANCEFIELD_LIB_FILENAMES) $(DISTANCEFIELD_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $< -o $@


ifeq ($(CLEANFOLDER), DISTANCEFIELD)
clean: cleandistanceField
endif

deepclean: cleandistanceField

cleandistanceField:
	$(RM) $(DISTANCEFIELD_OBJECTS_FILENAMES) $(L)/distanceField/libdistanceField.a

endif
