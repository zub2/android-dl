/*
 * This file depends on testDep_dep.h which is implemented
 * in libtestDep_dep.so.
 *
 * It's used in the testcase for loading a library with dependencies.
 */
#include <android/log.h>
#include "testDep_dep.h"

void testMain()
{
	__android_log_write(ANDROID_LOG_DEBUG, "android-dl", "testMain called, invoking testDep");
	testDep();
}
