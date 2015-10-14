#include "AppDelegate.h"
#include "cocos2d.h"
#include "CCEventType.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
#include "Log.h"

// google-breakpadÒýÓÃ
#include "client/linux/handler/exception_handler.h"
#include "client/linux/handler/minidump_descriptor.h"
using namespace google_breakpad;

#define  LOG_TAG    "main"
#ifndef	 LOGD	
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#endif
using namespace cocos2d;

bool onMinidumpDumped(const MinidumpDescriptor& descriptor,
					  void* context,
					  bool succeeded)
{
	LOGE("Dump generation request %s.",succeeded ? "succeeded" : "failed");
	gLog->Close();
	return succeeded;
}

void cocos_android_app_init (JNIEnv* env, jobject thiz) {
	CCLOG("---------cocos_android_app_init--------------");
	google_breakpad::MinidumpDescriptor descriptor("/mnt/sdcard/com.zm.mszb/log");
	google_breakpad::ExceptionHandler *pCrashHandler = new google_breakpad::ExceptionHandler(descriptor, NULL, onMinidumpDumped,NULL, true, -1);
    AppDelegate *pAppDelegate = new AppDelegate();
}
