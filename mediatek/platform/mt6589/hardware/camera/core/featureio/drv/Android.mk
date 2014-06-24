#
# libfeatureiodrv_comm
#
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

ifeq ($(BUILD_MTK_LDVT),true)
    LOCAL_CFLAGS += -DUSING_MTK_LDVT
endif

LOCAL_SRC_FILES:= \
  nvram/nvram_drv.cpp \
  nvram/nvram_buf_mgr.cpp \
  strobe/strobe_drv.cpp \
  strobe/flashlight_drv.cpp \
  tdri_mgr/tdri_mgr.cpp \
  cam_cal/cam_cal_drv.cpp \
  cam_cal/camera_common_calibration.cpp \
#  eeprom/eeprom_drv.cpp \
#  eeprom/camera_common_calibration.cpp \
 
ifneq ($(BUILD_MTK_LDVT),true)
    LOCAL_SRC_FILES += \
        eis/eis_drv.cpp \
        lce/lce_drv.cpp
endif

ifneq ($(BUILD_MTK_LDVT),true)
    LOCAL_SRC_FILES += \
  lens/mcu_drv.cpp \
  lens/lens_drv.cpp \
  lens/lens_sensor_drv.cpp
endif

# LOCAL_SRC_FILES:= \
#  nvram/nvram_drv.cpp \
#  nvram/nvram_buf_mgr.cpp \

LOCAL_C_INCLUDES:= \
  $(MTK_PATH_CUSTOM)/kernel/imgsensor/inc \
  $(MTK_PATH_SOURCE)/external/nvram/libnvram \
  $(MTK_PATH_CUSTOM)/hal/inc/aaa \
  $(MTK_PATH_CUSTOM)/hal/inc \
  $(MTK_PATH_CUSTOM)/hal/camera \
  $(MTK_PATH_CUSTOM)/kernel/flashlight/inc \
  $(MTK_PATH_CUSTOM)/kernel/lens/inc \
  $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/core/featureio/drv/inc \
    $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/core/drv/imem \
  $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/common \
  $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/drv \
  $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/featureio \
  $(TOP)/$(MTK_PATH_PLATFORM)/external/ldvt/include \
  $(TOP)/$(MTK_PATH_PLATFORM)/hardware/m4u \
  $(TOP)/$(MTK_PATH_PLATFORM)/hardware/camera/inc/common/camutils \

#endif

LOCAL_STATIC_LIBRARIES := \

LOCAL_WHOLE_STATIC_LIBRARIES := \
    
LOCAL_MODULE:= libfeatureiodrv

include $(BUILD_STATIC_LIBRARY)

include $(call all-makefiles-under,$(LOCAL_PATH))
