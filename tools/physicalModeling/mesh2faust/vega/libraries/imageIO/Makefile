ifndef IMAGEIO
IMAGEIO=IMAGEIO

ifndef CLEANFOLDER
CLEANFOLDER=IMAGEIO
endif

R ?= ../..
include $(R)/Makefile-headers/Makefile-header

# the object files to be compiled for this library
IMAGEIO_OBJECTS=imageIO.o

# the libraries this library depends on
IMAGEIO_LIBS=

# the headers in this library
IMAGEIO_HEADERS=imageIO.h imageFormats.h

IMAGEIO_OBJECTS_FILENAMES=$(addprefix $(L)/imageIO/, $(IMAGEIO_OBJECTS))
IMAGEIO_HEADER_FILENAMES=$(addprefix $(L)/imageIO/, $(IMAGEIO_HEADERS))
IMAGEIO_LIB_MAKEFILES=$(call GET_LIB_MAKEFILES, $(IMAGEIO_LIBS))
IMAGEIO_LIB_FILENAMES=$(call GET_LIB_FILENAMES, $(IMAGEIO_LIBS))

include $(IMAGEIO_LIB_MAKEFILES)

all: $(L)/imageIO/libimageIO.a

$(L)/imageIO/libimageIO.a: $(IMAGEIO_OBJECTS_FILENAMES)
	ar r $@ $^; cp $@ $(L)/lib; cp $(L)/imageIO/*.h $(L)/include

$(IMAGEIO_OBJECTS_FILENAMES): %.o: %.cpp $(IMAGEIO_LIB_FILENAMES) $(IMAGEIO_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c -I$(LIBRARIES_DIR)/include $(IMAGE_INCLUDE) $< -o $@

ifeq ($(CLEANFOLDER), IMAGEIO)
clean: cleanimageIO
endif

deepclean: cleanimageIO

cleanimageIO:
	$(RM) $(IMAGEIO_OBJECTS_FILENAMES) $(L)/imageIO/libimageIO.a

endif
