LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE   := dsp_faust
LOCAL_C_INCLUDES := $(LOCAL_PATH)
#LOCAL_EXPORT_C_INCLUDE_DIRS  := $(LOCAL_PATH)/faust
LOCAL_CFLAGS := -O3
LOCAL_CPPFLAGS :=$(LOCAL_CFLAGS)
###

LOCAL_SRC_FILES := dsp_faust.cpp \
java_interface_wrap.cpp 

LOCAL_LDLIBS := -llog -lOpenSLES

include $(BUILD_SHARED_LIBRARY)


