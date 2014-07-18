/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

/********************************************************************************************
 *     LEGAL DISCLAIMER
 *
 *     (Header of MediaTek Software/Firmware Release or Documentation)
 *
 *     BY OPENING OR USING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 *     THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE") RECEIVED
 *     FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON AN "AS-IS" BASIS
 *     ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED,
 *     INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR
 *     A PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY
 *     WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 *     INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK
 *     ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
 *     NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION
 *     OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 *
 *     BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE LIABILITY WITH
 *     RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION,
TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE
 *     FEES OR SERVICE CHARGE PAID BY BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 *     THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE WITH THE LAWS
 *     OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF LAWS PRINCIPLES.
 ************************************************************************************************/

#ifndef _AAA_HAL_YUV_H_
#define _AAA_HAL_YUV_H_

//------------Thread-------------
#include <linux/rtpm_prio.h>
#include <pthread.h>
#include <semaphore.h>
//-------------------------------
#include <isp_drv.h>

#include <aaa_hal_base.h>
#include <utils/threads.h>
#include <sensor_hal.h>
#include "strobe_drv.h"
#include "kd_imgsensor_define.h"

using namespace android;

typedef struct
{
    MINT32 i4Left;
    MINT32 i4Right;
    MINT32 i4Top;
    MINT32 i4Bottom;
    MINT32 i4Info;
    
} AREA_T;

#define MAX_FOCUS_AREAS    (9)
#define MAX_METERING_AREAS (9)


namespace NS3A
{


/*******************************************************************************
*
********************************************************************************/
class Hal3AYuv : public Hal3ABase
{

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:
    Hal3AYuv();
    virtual ~Hal3AYuv();

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Interfaces.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:
    static Hal3AYuv* createInstance(MINT32 const i4SensorDevId);
    static Hal3AYuv* getInstance();
    virtual MVOID destroyInstance();
    virtual MBOOL sendCommand(ECmd_T const eCmd, MINT32 const i4Arg = 0);

    virtual inline MINT32 getErrorCode() const
    {
        return m_errorCode;
    }

    virtual inline MBOOL getParams(Param_T &rParam) const
    {
        rParam = m_rParam;
        return MTRUE;
    }

    virtual MBOOL setParams(Param_T const &rNewParam);
    virtual MBOOL getSupportedParams(FeatureParam_T &rFeatureParam);

    virtual inline MBOOL isReadyToCapture() const
    {
        return m_bReadyToCapture;
    }

    virtual MBOOL autoFocus();
    virtual MBOOL cancelAutoFocus();
    virtual MBOOL setZoom(MUINT32 u4ZoomRatio_x100, MUINT32 u4XOffset, MUINT32 u4YOffset, MUINT32 u4Width, MUINT32 u4Height);
    virtual MBOOL set3AEXIFInfo(IBaseCamExif *pIBaseCamExif) const;
    virtual MBOOL setDebugInfo(IBaseCamExif *pIBaseCamExif) const;
    virtual MINT32 getDelayFrame(EQueryType_T const eQueryType) const;
    virtual MBOOL setIspProfile(EIspProfile_T const eIspProfile);
    virtual MRESULT EnableAFThread(MINT32 a_bEnable);
    virtual MBOOL setCallbacks(I3ACallBack* cb);
    virtual MINT32 getCaptureParams(MINT8 index, MINT32 i4EVidx, CaptureParam_T &a_rCaptureInfo);
    virtual MINT32 updateCaptureParams(CaptureParam_T &a_rCaptureInfo);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Implementation
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:
    MRESULT init(MINT32 i4SensorDev);
    MRESULT uninit();

    inline MVOID setErrorCode(MRESULT errorCode)
    {
        m_errorCode = errorCode;
    }

    inline MVOID resetReadyToCapture()
    {
        m_bReadyToCapture = MFALSE;
    }

    inline MVOID notifyReadyToCapture()
    {
        m_bReadyToCapture = MTRUE;
    }

    inline MINT32 getSensorDev()
    {
        return m_i4SensorDev;
    }

    private:
    static MVOID* AFThreadFunc(void *arg);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Data member
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
private:
    volatile int  m_Users;
    mutable Mutex m_Lock;
    MRESULT       m_errorCode;
    Param_T       m_rParam;
    MBOOL         m_bForceUpdatParam;
    MBOOL         m_bReadyToCapture;
    MINT32        m_i4SensorDev;
    I3ACallBack*  m_pAFYuvCallBack;
    SensorHal*    m_pSensorHal;           
    //AF related
    MINT32        m_bIsdummylens;
    MINT32        m_AFzone[6];	
    MINT32        m_AEzone[6];
    AREA_T        m_sAFAREA[MAX_FOCUS_AREAS];      //
    AREA_T        m_sAEAREA[MAX_METERING_AREAS];   //
    MINT32        m_imageXS;
    MINT32        m_imageYS;
    MINT32        m_max_metering_areas;
    MINT32        m_max_af_areas;
    MINT32        m_i4PreAfStatus;
    MINT32        m_i4PreAfMode;
    MINT32        m_i4AFSwitchCtrl;
    MINT32        m_i4AutoFocus;
    MINT32        m_i4AutoFocusTimeout;
    MINT32        m_i4State;

    MBOOL         bAELockSupp;
    MBOOL         bAWBLockSupp;
    StrobeDrv     *m_pStrobeDrvObj;
    //Strobe related
    double        m_strobeTrigerBV;	
    double        BV_THRESHOLD;	
    double        m_strobecurrent_BV;
    double        m_strobePreflashBV;
    MINT32        m_aeFlashlightType;
    SENSOR_FLASHLIGHT_AE_INFO_STRUCT m_AEFlashlightInfo;
    MINT32        pre_shutter;
    MINT32        pre_gain;
    MUINT32       m_preflashFrmCnt;
    MUINT32       m_strobeWidth;
    MBOOL         m_bFlashActive;


private:
    MINT32 mapAEToEnum(MINT32 mval,MFLOAT mstep);
    MINT32 mapISOToEnum(MUINT32 u4NewAEISOSpeed);
    MINT32 mapEnumToISO(MUINT32 u4NewAEIsoEnum) const;
    //AF related
    MINT32 setAFMode(MINT32 AFMode);
    MINT32  isFocused();
    MVOID  setFocusAreas(MINT32 a_i4Cnt, AREA_T *a_psFocusArea);
    MVOID  getFocusAreas(MINT32 &a_i4Cnt, AREA_T **a_psFocusArea);
    MINT32 clamp(MINT32 x, MINT32 min, MINT32 max);
    MVOID  getMeteringAreas(MINT32 &a_i4Cnt, AREA_T **a_psAEArea);
    MVOID  setMeteringAreas(MINT32 a_i4Cnt, AREA_T const *a_psAEArea);
    MVOID  mapAeraToZone(AREA_T *p_area, MINT32 areaW,
                         MINT32 areaH, MINT32* p_zone, 
                         MINT32 zoneW, MINT32 zoneH);

    MINT32 setFlashMode(MINT32 mode);
    MINT32 isAEFlashOn();
    double AEFlashlightLog2(double x);
    double calcBV();    
    MINT32 queryAEFlashlightInfoFromSensor();
    MINT32 updateAeFlashCaptureParams();
    MINT32 setEShutterParam(MUINT32 a_u4ExpTime, MUINT32 a_u4SensorGain);
    MINT32 getHDRCapInfo(Hal3A_HDROutputParam_T &a_strHDROutputInfo);
    void convertFlashExpPara(MINT32 flashEngRatio_x10, MINT32 minAfeGain_x1024, 
								 MINT32 bv0_x1024, MINT32 bv1_x1024,
								 MINT32  exp1, MINT32  afeGain1_x1024, MINT32  ispGain1_x1024, 
								 MINT32& exp2, MINT32& afeGain2_x1024, MINT32& ispGain2_x1024) const;

};

}; // namespace NS3A

#endif
