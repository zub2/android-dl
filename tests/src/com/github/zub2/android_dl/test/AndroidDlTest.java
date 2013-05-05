package com.github.zub2.android_dl.test;

import android.test.AndroidTestCase;
import com.github.zub2.android_dl.AndroidDl;
import com.github.zub2.android_dl.test.AndroidDlNativeTestLauncher;

public class AndroidDlTest extends AndroidTestCase
{
	static
	{
		System.loadLibrary("android-dl");
		System.loadLibrary("native_api");
	}

	@Override
	protected void setUp()
	{
		AndroidDl.initialize(getContext().getApplicationInfo().nativeLibraryDir);
	}

	public void testLoadLibraryWithDependency()
	{
		AndroidDl.loadLibrary("testDep_main");
	}

	public void testNativeApi()
	{
		assertTrue("android-dl native interface", AndroidDlNativeTestLauncher.testNativeApi());
	}
}
