LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := zm_static

LOCAL_MODULE_FILENAME := libzm

LOCAL_SRC_FILES := \
cfgFile.cpp \
hashCode.cpp \
Log.cpp \
MD5.cpp \
mpq/MPQDiffer.cpp \
mpq/MPQPackage.cpp \
mpq/MPQPacker.cpp \
mpq/MPQPatcher.cpp \
RunnableAsync.cpp \
socket/ClientSocket.cpp \
socket/IOSocket.cpp \
socket/MessageBuffer.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
					$(LOCAL_PATH)/mpq \
					$(LOCAL_PATH)/socket

include $(BUILD_STATIC_LIBRARY)

