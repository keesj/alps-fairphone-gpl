/*
**
** Copyright 2008, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#ifndef _APP_FDFT_SW_H
#define _APP_FDFT_SW_H

#include "MTKDetection.h"



class AppFDFT_SW : public MTKDetection {
public:
    //int FaceCnt;
    
    static MTKDetection* getInstance();
    virtual void destroyInstance();
    
    AppFDFT_SW();
    virtual ~AppFDFT_SW();
    
    void FDVTInit(MTKFDFTInitInfo *init_data);
    
    void FDVTMain(MUINT32 ImageScaleBuffer, MUINT32 ImageBufferRGB565,  FDVT_OPERATION_MODE_ENUM fd_state, FACEDETECT_GSENSOR_DIRECTION direction, int gfd_fast_mode);
    
    void FDVTReset(void);
    MUINT32 FDVTGetResultSize(void);
    MUINT8 FDVTGetResult(MUINT32 FD_result_Adr, FACEDETECT_TRACKING_RESULT_TYPE_ENUM result_type);
    
    //void FDVTGetICSResult(camera_frame_metadata_mtk *FD_ICS_Result, struct result * FD_Results, MUINT32 Width,MUINT32 Heigh, MUINT32 LCM, MUINT32 Sensor, MUINT32 Camera_TYPE, MUINT32 Draw_TYPE);
    void FDVTGetICSResult(MUINT32  FD_ICS_Result, MUINT32 FD_Results, MUINT32 Width,MUINT32 Heigh, MUINT32 LCM, MUINT32 Sensor, MUINT32 Camera_TYPE, MUINT32 Draw_TYPE);
    //void FDVTGetFDInfo(MUINT32  FD_Info_Result);
    void FDVTDrawFaceRect(MUINT32 image_buffer_address,MUINT32 Width,MUINT32 Height,MUINT32 OffsetW,MUINT32 OffsetH,MUINT8 orientation);
    //#ifdef SmileDetect
    MUINT8 FDVTGetSDResult(MUINT32 FD_result_Adr);
    void FDVTGetMode(FDVT_OPERATION_MODE_ENUM *mode);
    //void FDVTSDDrawFaceRect(MUINT32 image_buffer_address,MUINT32 Width,MUINT32 Height,MUINT32 OffsetW,MUINT32 OffsetH,MUINT8 orientation);
    //#endif
    //*/
};


#endif