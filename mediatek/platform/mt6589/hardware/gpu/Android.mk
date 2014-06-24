LOCAL_PATH := $(my-dir)

ifeq ($(MTK_PLATFORM),$(filter $(MTK_PLATFORM), MT6589))
ifneq ($(MTK_GPU_SUPPORT),no)

VER:=eng

include $(CLEAR_VARS)
LOCAL_MODULE := libBLPP.so
LOCAL_MODULE_CLASS := MODULE
LOCAL_MODULE_PATH := $(TARGET_OUT)/vendor/lib
LOCAL_SRC_FILES := $(LOCAL_MODULE)
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := rc.fac
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_MODULE_PATH := $(TARGET_OUT)/vendor/bin
LOCAL_SRC_FILES := $(LOCAL_MODULE)
include $(BUILD_PREBUILT)


ifneq ($(strip $(TARGET_BUILD_VARIANT)),)
ifneq ($(strip $(TARGET_BUILD_VARIANT)),eng)
ifneq ($(strip $(MTK_3D_DEBUG_FOR_USER_VERSION)),yes)
VER:=user
endif
endif
endif

include $(LOCAL_PATH)/$(VER)/Android.mk

endif

endif # MTK_PLATFORM
