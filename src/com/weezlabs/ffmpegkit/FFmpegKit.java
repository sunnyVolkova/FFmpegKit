package com.weezlabs.ffmpegkit;

import android.util.Log;
/**
 * This class is used to call ffmpeg from ndk.
 */
public final class FFmpegKit {
	private static final String TAG = "FFmpegKit";
	private static boolean isLoaded_ = false;
	static {
		try{
			System.loadLibrary("x264-146");
			System.loadLibrary("avutil-54");
			System.loadLibrary("swresample-1");
			System.loadLibrary("avcodec-56");
			System.loadLibrary("avformat-56");
			System.loadLibrary("swscale-3");
			System.loadLibrary("postproc-53");
			System.loadLibrary("avfilter-5");
			System.loadLibrary("avdevice-56");
			System.loadLibrary("ffmpegkit");
			isLoaded_ = true;
		} catch(UnsatisfiedLinkError e){
			isLoaded_ = false;
			Log.e(TAG, "UnsatisfiedLinkError: ", e);
		}
	}
	public boolean isLoaded(){
		return isLoaded_;
	}
	
	/**
	 * run ffmpeg command, log command
	 */
	public int runDebug(String[] args){
		StringBuilder sb = new StringBuilder();
		for(String str: args){
			sb.append(str);
		}
		Log.d(TAG, "run ffmpeg command: " + sb.toString());
		return runprotected(args);
	}
	
	/**
	 * run ffmpeg command
	 * usage: 					
	 * argv[0] -> "ffmpeg",
	 * ... other command options
	 * at leat one output file should be specified
	 * 
	 * return: 0 if success, -1 otherwise
	 */
	public native int runprotected(String[] args);
	
	/**
	 * get file metadata using ffmpeg
	 * usage: 					
	 * argv[0] -> "ffmpeg",
	 * argv[1] -> input file name
	 * argv[2] -> "g" - to find key in general metadata
	 *            "a" - to find key in audio channels
	 *            "v" - to find key in video channels
	 * argv[3] -> key name (for example "rotation")
	 * first found key value will be returned
	 * 
	 * return: key value string if success, NULL otherwise
	 */
	public native String getmetadataprotected(String[] args);
}
