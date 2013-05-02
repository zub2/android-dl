package com.github.zub2.android_dl.test;

import android.test.AndroidTestCase;
import com.github.zub2.android_dl.AndroidDl;

public class AndroidDlTest extends AndroidTestCase
{
	static
	{
		System.loadLibrary("android-dl");
	}

	@Override
	protected void setUp()
	{
		AndroidDl.initialize(getContext().getApplicationInfo().nativeLibraryDir);
	}

	public void testLoadLibraryWithDependency()
	{
		AndroidDl.loadLibrary("test1");
	}
}
