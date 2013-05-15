Android Dynamic Library Loader
==============================

This library works around Android's inability to resolve dependencies between your app's shared libraries (as opposed to dependency on system libraries such as *libc.so* and *liblog.so*).
For example, if you load a JNI shared library that depends on another library shipped in your app's *lib/* directory, you'll get a `LinkageError` exception unless you manually preload the dependencies (by performing additional `System.loadLibrary` calls),
For example, if your JNI library *libfoo.so* links with *libgnustl_shared.so*, you have to explicitly perform:

    System.loadLibrary("gnustl_shared");
    System.loadLibrary("foo");

This is what the Android NDK recommends doing (see docs/CPLUSPLUS-SUPPORT.html) and for merely a single dependency this isn't a big deal, but it can get unruly when you have a complicated codebase with a myriad of libraries.

Same goes for performing `dlopen` from within native code.

Technically, this stems from the fact that your app's *lib/* directory (i.e. */data/data/com.company.foobar/lib/*) is not in the Dalvik process' *LD_LIBRARY_PATH* environment variable. Moreover, the environment variable is [only parsed at startup](https://groups.google.com/d/msg/android-ndk/m6OddFQINxs/sAQ34sFhJ7QJ) and there's no way to amend the list at runtime.

A future solution is contained in [Issue 34416](https://code.google.com/p/android/issues/detail?id=34416) but it has not been released at the time of writing. This means devices with Android <= 4.2.2 will not get the fix. If your application is to run on such devices you still need to deal with the issue yourself.

License
=======

This library is licensed under either Mozilla Public License 1.1, or, at your choice, GNU General Public License Version 3 or later or GNU Lesser General Public License Version 3.

History
=======

This code originally comes from the LibreOffice *lo-bootstrap.c* file, with the following modifications:

* Only the dynamic library-related code was kept.
* A different namespace was reinstated.
* Exception reporting was added.
* Documentation.
* Android project packaging.
* Tests added.

Usage
=====

Android-dl is packaged as an Android library project. To use it you need to do the following steps:

## Step 1: Reference the project from your *project.properties*

Add the following to *project.properties* of your project:

<pre>
android.library.reference.1=path/to/android-dl
</pre>

Use the next available number if *android.library.reference.1* is already in use. Replace *path/to/android-dl* with wherever you placed android-dl. It can be a relative path.

## Step 2: Import the NDK module in your native project

Append this to the *end* of your Android.mk:

<pre>
$(call import-add-path, path/to/directory-containing-android-dl)
$(call import-module, android-dl/jni)
</pre>

The import path can be specified as a relative path. Note that it *must* point to the *parent* directory of *android-dl*, it must not be the android-dl directory itself.

In addition, add `android-dl` to your `LOCAL_SHARED_LIBRARIES`, e.g.:
<pre>
include $(CLEAR_VARS)

LOCAL_MODULE := foo
LOCAL_SRC_FILES := foo.c
LOCAL_SHARED_LIBRARIES := bar baz android-dl

include $(BUILD_SHARED_LIBRARY)
</pre>

For more information about importing NDK modules, see docs/IMPORT-MODULE.html in the Android NDK tree.

## Step 3: Initialize android-dl in your Java code

Within your main activity's `onCreate`, call `AndroidDl.initialize( getApplicationInfo().nativeLibraryDir )`.

## Step 4: Use android-dl from your Java code

To load a native library, use `AndroidDl.loadLibrary(libName)` instead of `System.loadLibrary(libName)`.

## Step 5: Use android-dl from your native code

If you wish to load shared libraries from within your native code:

1. `#include "android-dl.h"`
1. Use `android_dlopen(lib)` instead of `dlopen(lib)`.

For an example project using android-dl look at the test project (living in the `tests/` subdirectory).

Notes
====

* If your project contains a native part (which is most often the case when you use android-dl) *do not build the native part of android-dl by ndk-build in the android-dl project itself*. It will be built automatically with the native code of your project. Only build it in the uncommon case your project doesn't have a native part. In that case skip steps 2 and 5 above.

* android-dl should be *mostly* thread-safe. The exception is `android_dl_get_last_error()` where the last thread to run into an error wins.
