#### Shared library for libmusicxml ####

LOCAL_PATH := $(call my-dir)
SRC := $(LOCAL_PATH)/../..

include $(CLEAR_VARS)

LOCAL_MODULE := libOSCFaust

# SRC var is a trick to use wildcard in android.mk
# if no wildcard, you have better to use relative path, conforming to android doc
LOCAL_SRC_FILES         := $(subst $(LOCAL_PATH)/,,$(wildcard $(SRC)/faust/src/*/*.cpp) $(wildcard $(SRC)/faust/src/*.cpp) $(wildcard $(SRC)/oscpack/osc/*.cpp) $(wildcard $(SRC)/oscpack/ip/*.cpp) $(wildcard $(SRC)/oscpack/ip/posix/*.cpp))
LOCAL_EXPORT_C_INCLUDES := $(addprefix $(SRC)/, interface)
LOCAL_C_INCLUDES        := $(subst $(LOCAL_PATH)/../,,$(SRC)/faust $(wildcard $(SRC)/faust/src/*) $(SRC)/oscpack $(SRC)/..)
LOCAL_CPPFLAGS          := -Dandroid -frtti -O3 -fexceptions

include $(BUILD_SHARED_LIBRARY)
