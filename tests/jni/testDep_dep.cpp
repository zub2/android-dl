#include <android/log.h>

void testDep()
{
	__android_log_write(ANDROID_LOG_DEBUG, "android-dl", "testDep called");
}
