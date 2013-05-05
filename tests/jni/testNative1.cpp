#include <android/log.h>
#include "testNative1.h"
#include "testNative2.h"

bool testNative1()
{
	__android_log_write(ANDROID_LOG_DEBUG, "android-dl", "testNative1 called");
	return testNative2();
}
