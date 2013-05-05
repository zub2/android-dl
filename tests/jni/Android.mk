LOCAL_PATH := $(call my-dir)

# The transitional dependency loading testcase
include $(CLEAR_VARS)
LOCAL_MODULE := testDep_dep
LOCAL_SRC_FILES := testDep_dep.cpp
LOCAL_LDLIBS := -llog
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := testDep_main
LOCAL_SRC_FILES := testDep_main.cpp
LOCAL_LDLIBS := -llog
LOCAL_SHARED_LIBRARIES := testDep_dep
include $(BUILD_SHARED_LIBRARY)

# 3-level transitional dependency testcase (used from C++)
include $(CLEAR_VARS)
LOCAL_MODULE := testNative2
LOCAL_SRC_FILES := testNative2.cpp
LOCAL_LDLIBS := -llog
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := testNative1
LOCAL_SRC_FILES := testNative1.cpp
LOCAL_LDLIBS := -llog
LOCAL_SHARED_LIBRARIES := testNative2
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := testNative0
LOCAL_SRC_FILES := testNative0.cpp
LOCAL_LDLIBS := -llog
LOCAL_SHARED_LIBRARIES := testNative1
include $(BUILD_SHARED_LIBRARY)

# Using android-dl from C++ testcase
include $(CLEAR_VARS)
LOCAL_MODULE := native_api
LOCAL_SRC_FILES :=  native_api.cpp
LOCAL_LDLIBS := -llog
LOCAL_SHARED_LIBRARIES := android-dl
include $(BUILD_SHARED_LIBRARY)

# import android-dl
$(call import-add-path, ../..)
$(call import-module, android-dl/jni)
