ifndef PERFORMANCECOUNTER
PERFORMANCECOUNTER=PERFORMANCECOUNTER

ifndef CLEANFOLDER
CLEANFOLDER=PERFORMANCECOUNTER
endif

R ?= ../..
include $(R)/Makefile-headers/Makefile-header

# the object files to be compiled for this library
PERFORMANCECOUNTER_OBJECTS=performanceCounter.o

# the libraries this library depends on
PERFORMANCECOUNTER_LIBS=

# the headers in this library
PERFORMANCECOUNTER_HEADERS=performanceCounter.h

PERFORMANCECOUNTER_OBJECTS_FILENAMES=$(addprefix $(L)/performanceCounter/, $(PERFORMANCECOUNTER_OBJECTS))
PERFORMANCECOUNTER_HEADER_FILENAMES=$(addprefix $(L)/performanceCounter/, $(PERFORMANCECOUNTER_HEADERS))
PERFORMANCECOUNTER_LIB_MAKEFILES=$(call GET_LIB_MAKEFILES, $(PERFORMANCECOUNTER_LIBS))
PERFORMANCECOUNTER_LIB_FILENAMES=$(call GET_LIB_FILENAMES, $(PERFORMANCECOUNTER_LIBS))

include $(PERFORMANCECOUNTER_LIB_MAKEFILES)

all: $(L)/performanceCounter/libperformanceCounter.a

$(L)/performanceCounter/libperformanceCounter.a: $(PERFORMANCECOUNTER_OBJECTS_FILENAMES)
	ar r $@ $^; cp $@ $(L)/lib; cp $(L)/performanceCounter/*.h $(L)/include

$(PERFORMANCECOUNTER_OBJECTS_FILENAMES): %.o: %.cpp $(PERFORMANCECOUNTER_LIB_FILENAMES) $(PERFORMANCECOUNTER_HEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $< -o $@

ifeq ($(CLEANFOLDER), PERFORMANCECOUNTER)
clean: cleanperformanceCounter
endif

deepclean: cleanperformanceCounter

cleanperformanceCounter:
	$(RM) $(PERFORMANCECOUNTER_OBJECTS_FILENAMES) $(L)/performanceCounter/libperformanceCounter.a

endif
