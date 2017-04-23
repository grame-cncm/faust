ifndef CONFIGFILE
CONFIGFILE=CONFIGFILE

ifndef CLEANFOLDER
CLEANFOLDER=CONFIGFILE
endif

R ?= ../..
include $(R)/Makefile-headers/Makefile-header

# the object files to be compiled for this library
CONFIGFILE_OBJECTS=configFile.o

# the libraries this library depends on
CONFIGFILE_LIBS=minivector

# the headers in this library
CONFIGFILE_HEADERS=configFile.h

CONFIGFILE_OBJECTS_FILENAMES=$(addprefix $(L)/configFile/, $(CONFIGFILE_OBJECTS))
CONFIGFILE_HEADER_FILENAMES=$(addprefix $(L)/configFile/, $(CONFIGFILE_HEADERS))
CONFIGFILE_LIB_MAKEFILES=$(call GET_LIB_MAKEFILES, $(CONFIGFILE_LIBS))
CONFIGFILE_LIB_FILENAMES=$(call GET_LIB_FILENAMES, $(CONFIGFILE_LIBS))

include $(CONFIGFILE_LIB_MAKEFILES)

all: $(L)/configFile/libconfigFile.a

$(L)/configFile/libconfigFile.a: $(CONFIGFILE_OBJECTS_FILENAMES)
	ar r $@ $^; cp $@ $(L)/lib; cp $(L)/configFile/*.h $(L)/include

$(CONFIGFILE_OBJECTS_FILENAMES): %.o: %.cpp $(CONFIGFILE_LIB_FILENAMES) $(CONFIGFILE_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $< -o $@

ifeq ($(CLEANFOLDER), CONFIGFILE)
clean: cleanconfigFile
endif

deepclean: cleanconfigFile

cleanconfigFile:
	$(RM) $(CONFIGFILE_OBJECTS_FILENAMES) $(L)/configFile/libconfigFile.a

endif
