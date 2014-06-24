LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_PREBUILT_LIBS := \
	lib/libvcodec_oal.so \
	lib/libmp4enc_xa.ca7.so

include $(BUILD_MULTI_PREBUILT)