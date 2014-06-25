package com.white.imagesobelfilter;

public class nativeSobelFilter extends Thread{
	String resultString;
	String imagePath;

	public nativeSobelFilter(String imagePath) {
		this.imagePath = imagePath;
	}

	static {
		System.loadLibrary("SobelFilter");
	}

	public void run() {
		resultString=sobelFilter(imagePath);
	}

	public native String sobelFilter(String imagePath);

}
