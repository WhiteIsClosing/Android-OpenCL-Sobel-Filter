LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

include ../../sdk/native/jni/OpenCV.mk

LOCAL_MODULE    := SobelFilter
LOCAL_SRC_FILES := ImageSobelFilter.cpp aopencl.c
LOCAL_LDLIBS+=-L$(SYSROOT)/usr/lib -llog -ldl

include $(BUILD_SHARED_LIBRARY) 
 
