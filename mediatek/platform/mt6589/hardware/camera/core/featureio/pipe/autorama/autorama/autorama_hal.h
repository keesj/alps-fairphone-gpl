/*
** $Log: autorama_hal.h $
 *
*/

#ifndef _AUTORAMA_HAL_H_
#define _AUTORAMA_HAL_H_

#include "autorama_hal_base.h"
#include "MTKMotion.h"

class MTKAutorama;
class MTKMotion;
/*******************************************************************************
*
********************************************************************************/
class halAUTORAMA: public halAUTORAMABase 
{
public:
    //
    static halAUTORAMABase* getInstance();
    virtual void destroyInstance();
    //
    /////////////////////////////////////////////////////////////////////////
    //
    // halFDBase () -
    //! \brief FD Hal constructor
    //
    /////////////////////////////////////////////////////////////////////////                       
    halAUTORAMA(); 

    /////////////////////////////////////////////////////////////////////////
    //
    // ~mhalCamBase () -
    //! \brief mhal cam base descontrustor 
    //
    /////////////////////////////////////////////////////////////////////////    
    virtual ~halAUTORAMA();

        /////////////////////////////////////////////////////////////////////////
    //
    // mHalAUTORAMAInit () -
    //! \brief init autorama
    //
    /////////////////////////////////////////////////////////////////////////    
    virtual MINT32 mHalAutoramaInit(MTKPipeAutoramaEnvInfo AutoramaInitInData, MTKPipeMotionEnvInfo MotionInitInfo);

    /////////////////////////////////////////////////////////////////////////
    //
    // mHalAutoramaUninit () -
    //! \brief autorama uninit 
    //
    /////////////////////////////////////////////////////////////////////////    
    virtual MINT32 mHalAutoramaUninit();
       
    /////////////////////////////////////////////////////////////////////////
    //
    // mHalAutoramaGetParam () -
    //! \brief draw fd face detection result rectangle 
    //
    /////////////////////////////////////////////////////////////////////////    
    virtual MINT32 mHalAutoramaGetResult(MTKPipeAutoramaResultInfo* ResultInfo );

    /////////////////////////////////////////////////////////////////////////
    //
    // mHalAutoramaCalcStitch () -
    //! \brief get face detection result 
    //
    /////////////////////////////////////////////////////////////////////////    
    virtual MINT32 mHalAutoramaCalcStitch(void* SrcImg,MINT32 gEv,MTKPIPEAUTORAMA_DIRECTION_ENUM DIRECTION);
    
    /////////////////////////////////////////////////////////////////////////
    //
    // mHalAutoramaDoStitch () -
    //! \brief get face detection result 
    //
    /////////////////////////////////////////////////////////////////////////    
    virtual MINT32 mHalAutoramaDoStitch(); 

    /////////////////////////////////////////////////////////////////////////
    //
    // mHalAutoramaDoMotion () -
    //! \brief check motion and capture 
    //
    ///////////////////////////////////////////////////////////////////////// 
    virtual MINT32 mHalAutoramaDoMotion(MUINT32* ImgSrc,MUINT32* MotionResult);

    /////////////////////////////////////////////////////////////////////////
    //
    // mHalAutoramaGetWokSize () -
    //! \brief get working buffer size 
    //
    ///////////////////////////////////////////////////////////////////////// 
    virtual MINT32 mHalAutoramaGetWokSize(int SrcWidth, int SrcHeight, int ShotNum, int &WorkingSize);
    
protected:


private:
    MTKAutorama* m_pMTKAutoramaObj;
    MTKMotion* m_pMTKMotionObj;
};

#endif

