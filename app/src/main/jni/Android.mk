LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_LDLIBS    := -lm -llog

LOCAL_MODULE    := jni-test

LOCAL_SRC_FILES := jni-test.cpp

include $(BUILD_SHARED_LIBRARY)