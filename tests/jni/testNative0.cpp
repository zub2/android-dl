#include <android/log.h>
#include "testNative1.h"

extern "C" bool testNative0()
{
	__android_log_write(ANDROID_LOG_DEBUG, "android-dl", "testNative0 called");
	return testNative1();
}
