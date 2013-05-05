#include <android/log.h>
#include "testNative2.h"

bool testNative2()
{
	__android_log_write(ANDROID_LOG_DEBUG, "android-dl", "testNative2 called");
	return true;
}
