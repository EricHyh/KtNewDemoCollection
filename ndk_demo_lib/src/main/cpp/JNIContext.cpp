//
// Created by eriche on 2024/8/16.
//

#include "JNIContext.h"

JavaVM *JNIContext::g_jvm_ = nullptr;

void JNIContext::SetJVM(JavaVM *jvm)
{
	g_jvm_ = jvm;
}

JNIContext::JNIContext(JNIEnv *&env)
{
	jint status = g_jvm_->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6);
	if (status == JNI_EDETACHED)
	{
		g_jvm_->AttachCurrentThread(&env, nullptr);
		flag_ = true;
	} else
	{
		flag_ = false;
	}
}

JNIContext::~JNIContext()
{
	if (flag_)
	{
		g_jvm_->DetachCurrentThread();
	}
}
