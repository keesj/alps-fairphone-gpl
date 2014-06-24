#
# libmhaldrv
#
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

ifeq ($(HAVE_AEE_FEATURE),yes)
	LOCAL_CFLAGS += -DHAVE_AEE_FEATURE
endif

LOCAL_SHARED_LIBRARIES := \
    libstlport \
    libcutils \
    liblog \
    libcamdrv \
    libcamalgo

ifeq ($(HAVE_AEE_FEATURE),yes)
	LOCAL_SHARED_LIBRARIES += libaed
endif

ifneq ($(BUILD_MTK_LDVT),true)    
    LOCAL_SHARED_LIBRARIES += lib3a
    LOCAL_SHARED_LIBRARIES += libnvram
    LOCAL_SHARED_LIBRARIES += libcam_camera_exif
    LOCAL_SHARED_LIBRARIES += libcameracustom
    LOCAL_SHARED_LIBRARIES += libcam.utils
    LOCAL_SHARED_LIBRARIES += libdpframework
endif
            
LOCAL_STATIC_LIBRARIES := \

LOCAL_WHOLE_STATIC_LIBRARIES := \
    libfeatureiodrv \
    libfeatureiopipe \

ifeq ($(BUILD_MTK_LDVT),true)
LOCAL_WHOLE_STATIC_LIBRARIES += \
    libuvvf
endif

LOCAL_MODULE := libfeatureio

LOCAL_MODULE_TAGS := eng

LOCAL_PRELINK_MODULE := false

include $(BUILD_SHARED_LIBRARY) 

include $(call all-makefiles-under,$(LOCAL_PATH))
