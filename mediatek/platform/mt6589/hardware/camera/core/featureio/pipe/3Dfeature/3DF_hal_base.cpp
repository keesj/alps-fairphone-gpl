#define LOG_TAG "3DF_hal_base"
     
#include <stdlib.h>
#include <stdio.h>
#include <common/CamLog.h>
#include <common/CamTypes.h>
#include "mav_hal.h"
#include "pano3d_hal.h"
#include "3DF_hal_base.h"
     
/*******************************************************************************
*
********************************************************************************/
hal3DFBase* 
hal3DFBase::createInstance(Hal3DFObject_e eobject)
{
    if (eobject == HAL_MAV_OBJ_NORMAL) {
        return halMAV::getInstance();
    }
    if (eobject == HAL_PANO3D_OBJ_NORMAL) {   
    	  return halPANO3D::getInstance();
    }	
    else {
        return hal3DFTmp::getInstance();
    }

    return NULL;
}

MINT32 hal3DFBase::mHal3dfAddImg(MavPipeImageInfo* pParaIn)
{                      
	 return 0;           
}	                     
                       
MINT32 hal3DFBase::mHal3dfGetMavResult(void* pParaOut)
{                      
	 return 0;           
}	
                       
MINT32 hal3DFBase::mHal3dfMerge(MUINT32 *MavResult)
{                      
	 return 0;               
}	                     
                       
MINT32 hal3DFBase::mHal3dfDoMotion(void* InputData,MUINT32* MotionResult)
{                      
	 return 0;           
}	    	               
                       
MINT32 hal3DFBase::mHal3dfWarp(MavPipeImageInfo* pParaIn,MUINT32 *MavResult,MUINT8 ImgNum)
{                      
	 return 0;           
}	                                       

MINT32 hal3DFBase::mHal3dfCrop(MUINT32 *MavResult,MUINT8 ImgNum)
{                      
	 return 0;           
}	

MINT32 hal3DFBase::mHal3dfGetResult(MUINT32& MavResult, MUINT32& ClipWidth, MUINT32& ClipHeight)  
{
	 return 0;
}  

MINT32 hal3DFBase::mHal3dfStitch(MUINT32 *MavResult,MUINT8 ImgNum)
{                      
	 return 0;           
}	                                       

MINT32 hal3DFBase::mHal3dfGetStitchResult(void* Pano3dResult)  
{
	 return 0;
} 
  
MINT32 hal3DFBase::mHal3dfGetWokSize(int SrcWidth, int SrcHeight, MUINT32 &WorkingSize)
{
	 return 0;
}      

MINT32 hal3DFBase::mHal3dfSetWokBuff(void* WorkingBuff) 
{
	 return 0;
}  

/*******************************************************************************
*
********************************************************************************/
hal3DFBase*
hal3DFTmp::
getInstance()
{
    CAM_LOGD("[hal3DFTmp] getInstance \n");
    static hal3DFTmp singleton;
    return &singleton;
}

/*******************************************************************************
*
********************************************************************************/
void   
hal3DFTmp::
destroyInstance() 
{
}

