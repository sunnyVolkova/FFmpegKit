#include "logjam.h"
#include "coffeejni.h"
#include "com_weezlabs_ffmpegkit_FFmpegKit.h"
#ifdef __cplusplus
extern "C" {
#endif
#include "metadata.h"
#ifdef __cplusplus
}
#endif
#include <stdlib.h>
#include <stdbool.h>
#include <exception>

int main(int argc, char **argv);

JavaVM *sVm = NULL;

jint JNI_OnLoad( JavaVM* vm, void* reserved )
{
	LOGI("Loading native library compiled at " __TIME__ " " __DATE__);
	sVm = vm;
	return JNI_VERSION_1_6;
}

/** Regular JNI entry point. **/
jint Java_com_weezlabs_ffmpegkit_FFmpegKit_runprotected(JNIEnv* env, jobject object, jobjectArray args) {
	int i = 0;
	int argc = 0;
	int ret = -1;
	char **argv = NULL;
	jstring *strr = NULL;
	if (args != NULL) {
		argc = env->GetArrayLength(args);
		argv = (char **) malloc(sizeof(char *) * argc);
		strr = (jstring *) malloc(sizeof(jstring) * argc);

		for(i=0;i<argc;i++)
		{
			strr[i] = (jstring)(env)->GetObjectArrayElement(args, i);
			argv[i] = (char *)(env)->GetStringUTFChars(strr[i], 0);
		}
	}

	LOGI("try ffmpeg main: ");
	try{
		COFFEE_TRY_JNI(env, ret =  main(argc, argv));
	} catch(std::exception& e){
		LOGE("catch: %s", e.what());
		ret = -1;
	}
	for(i=0;i<argc;i++)
	{
		(env)->ReleaseStringUTFChars(strr[i], argv[i]);
	}
	free(argv);
	free(strr);
	return ret;
}

JNIEXPORT jstring JNICALL Java_com_weezlabs_ffmpegkit_FFmpegKit_getmetadataprotected(JNIEnv *env, jobject obj, jobjectArray args)
{
	int i = 0;
	int argc = 0;
	const char * ret = NULL;
	char **argv = NULL;
	jstring *strr = NULL;
	if (args != NULL) {
		argc = (env)->GetArrayLength(args);
		argv = (char **) malloc(sizeof(char *) * argc);
		strr = (jstring *) malloc(sizeof(jstring) * argc);

		for(i=0;i<argc;i++)
		{
			strr[i] = (jstring)(env)->GetObjectArrayElement(args, i);
			argv[i] = (char *)(env)->GetStringUTFChars(strr[i], 0);
		}
	}
	LOGI("try metadata get_meta_key: ");
	try{
		COFFEE_TRY_JNI(env, ret =  get_meta_key(argc, argv));
	} catch(std::exception& e){
		LOGE("catch: %s", e.what());
		ret = NULL;
	}

	for(i=0;i<argc;i++)
	{
		(env)->ReleaseStringUTFChars(strr[i], argv[i]);
	}
	free(argv);
	free(strr);
	jstring jstrRet = NULL;
	if(ret != NULL){
		jstrRet = (env)->NewStringUTF(ret);
	}
	return jstrRet;
}
