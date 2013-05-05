#include <jni.h>
#include <android/log.h>
#include <stddef.h>

#include "android-dl.h"

static bool testNativeApi();

// implement a "launcher" class that can be used to trigger the tests from Java code
#define METHOD_NAME(clazz, method) Java_com_github_zub2_android_1dl_test_##clazz##_##method

extern "C" JNIEXPORT jboolean JNICALL METHOD_NAME(AndroidDlNativeTestLauncher, testNativeApi)(JNIEnv *env, jclass)
{
	return testNativeApi() ?  JNI_TRUE : JNI_FALSE;
}

inline void logFailure(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	__android_log_vprint(ANDROID_LOG_ERROR, "android-dl", fmt, ap);
	va_end(ap);
}

static bool testNativeApi()
{
	void *dlHandle = android_dlopen("libtestNative0.so");
	if (dlHandle == NULL)
	{
		logFailure("android_dlopen failed");
		return false;
	}

	typedef void (*TEST_PROTOTYPE)();
	TEST_PROTOTYPE testFunction = (TEST_PROTOTYPE) android_dlsym(dlHandle, "testNative0");
	if (!testFunction)
	{
		logFailure("android_dlsym failed");
		return false;
	}

	testFunction();

	if (android_dlclose(dlHandle) != 0)
	{
		logFailure("android_dlclose failed");
		return false;
	}
	return true;
}
