ifndef ELASTICFORCEMODEL
ELASTICFORCEMODEL=ELASTICFORCEMODEL

ifndef CLEANFOLDER
CLEANFOLDER=ELASTICFORCEMODEL
endif

R ?= ../..
include $(R)/Makefile-headers/Makefile-header

# the object files to be compiled for this library
ELASTICFORCEMODELOBJECTS=corotationalLinearFEMForceModel.o massSpringSystemForceModel.o StVKForceModel.o isotropicHyperelasticFEMForceModel.o linearFEMForceModel.o clothBWForceModel.o

# the libraries this library depends on
ELASTICFORCEMODELLIBS=forceModel corotationalLinearFEM massSpringSystem stvk isotropicHyperelasticFEM clothBW

# the headers in this library
ELASTICFORCEMODELHEADERS=corotationalLinearFEMForceModel.h massSpringSystemForceModel.h StVKForceModel.h isotropicHyperelasticFEMForceModel.h linearFEMForceModel.h clothBWForceModel.h

ELASTICFORCEMODELOBJECTS_FILENAMES=$(addprefix $(L)/elasticForceModel/, $(ELASTICFORCEMODELOBJECTS))
ELASTICFORCEMODELHEADER_FILENAMES=$(addprefix $(L)/elasticForceModel/, $(ELASTICFORCEMODELHEADERS))
ELASTICFORCEMODELLIB_MAKEFILES=$(call GET_LIB_MAKEFILES, $(ELASTICFORCEMODELLIBS))
ELASTICFORCEMODELLIB_FILENAMES=$(call GET_LIB_FILENAMES, $(ELASTICFORCEMODELLIBS))

include $(ELASTICFORCEMODELLIB_MAKEFILES)

all: $(L)/elasticForceModel/libelasticForceModel.a

$(L)/elasticForceModel/libelasticForceModel.a: $(ELASTICFORCEMODELOBJECTS_FILENAMES)
	ar r $@ $^; cp $@ $(L)/lib; cp $(L)/elasticForceModel/*.h $(L)/include

$(ELASTICFORCEMODELOBJECTS_FILENAMES): %.o: %.cpp $(ELASTICFORCEMODELLIB_FILENAMES) $(ELASTICFORCEMODELHEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $< -o $@

ifeq ($(CLEANFOLDER), ELASTICFORCEMODEL)
clean: cleanelasticForceModel
endif

deepclean: cleanelasticForceModel

cleanelasticForceModel:
	$(RM) $(ELASTICFORCEMODELOBJECTS_FILENAMES) $(L)/elasticForceModel/libelasticForceModel.a

endif

