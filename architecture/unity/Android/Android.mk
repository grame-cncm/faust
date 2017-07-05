#### Shared library for Unity Plugin ####

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE            := libFaustPlugin_$(FILE)
LOCAL_SRC_FILES         := $(LOCAL_PATH)/$(FILE).cpp
LOCAL_CPPFLAGS          := -frtti -fexceptions -std=c++11
LOCAL_CFLAGS            := -std=c11 -O3 -ffast-math -fPIC
LOCAL_LDLIBS            := -latomic


include $(BUILD_SHARED_LIBRARY)
