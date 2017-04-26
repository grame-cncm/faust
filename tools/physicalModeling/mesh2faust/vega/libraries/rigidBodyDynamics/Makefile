ifndef RIGIDBODYDYNAMICS
RIGIDBODYDYNAMICS=RIGIDBODYDYNAMICS

ifndef CLEANFOLDER
CLEANFOLDER=RIGIDBODYDYNAMICS
endif

R ?= ../..
include $(R)/Makefile-headers/Makefile-header

# the object files to be compiled for this library
RIGIDBODYDYNAMICSOBJECTS=rigidBody.o rigidBody_generalTensor.o

# the libraries this library depends on
RIGIDBODYDYNAMICSLIBS=quaternion

# the headers in this library
RIGIDBODYDYNAMICSHEADERS=rigidBody.h rigidBody_generalTensor.h

RIGIDBODYDYNAMICSOBJECTS_FILENAMES=$(addprefix $(L)/rigidBodyDynamics/, $(RIGIDBODYDYNAMICSOBJECTS))
RIGIDBODYDYNAMICSHEADER_FILENAMES=$(addprefix $(L)/rigidBodyDynamics/, $(RIGIDBODYDYNAMICSHEADERS))
RIGIDBODYDYNAMICSLIB_MAKEFILES=$(call GET_LIB_MAKEFILES, $(RIGIDBODYDYNAMICSLIBS))
RIGIDBODYDYNAMICSLIB_FILENAMES=$(call GET_LIB_FILENAMES, $(RIGIDBODYDYNAMICSLIBS))

include $(RIGIDBODYDYNAMICSLIB_MAKEFILES)

all: $(L)/rigidBodyDynamics/librigidBodyDynamics.a

$(L)/rigidBodyDynamics/librigidBodyDynamics.a: $(RIGIDBODYDYNAMICSOBJECTS_FILENAMES)
	ar r $@ $^; cp $@ $(L)/lib; cp $(L)/rigidBodyDynamics/*.h $(L)/include

$(RIGIDBODYDYNAMICSOBJECTS_FILENAMES): %.o: %.cpp $(RIGIDBODYDYNAMICSLIB_FILENAMES) $(RIGIDBODYDYNAMICSHEADER_FILENAMES)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE) $(BLASLAPACK_INCLUDE) $< -o $@

ifeq ($(CLEANFOLDER), RIGIDBODYDYNAMICS)
clean: cleanrigidBodyDynamics
endif

deepclean: cleanrigidBodyDynamics

cleanrigidBodyDynamics:
	$(RM) $(RIGIDBODYDYNAMICSOBJECTS_FILENAMES) $(L)/rigidBodyDynamics/librigidBodyDynamics.a

endif

