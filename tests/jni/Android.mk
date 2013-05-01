LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := test2
LOCAL_SRC_FILES := test2.cpp
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := test1
LOCAL_SRC_FILES := test1.cpp
LOCAL_SHARED_LIBRARIES := test2
include $(BUILD_SHARED_LIBRARY)
