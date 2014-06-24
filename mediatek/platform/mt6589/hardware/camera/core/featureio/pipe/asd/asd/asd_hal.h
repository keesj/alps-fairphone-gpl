/*
** $Log: asd_hal.h $
 *
*/ 

#ifndef _ASD_HAL_H_
#define _ASD_HAL_H_

#include "asd_hal_base.h"
#include "MTKAsd.h"
#include "asd_aaa_param.h"

class MTKAsd;

/*******************************************************************************
*
********************************************************************************/
class halASD: public halASDBase 
{
public:
    //
    static halASDBase* getInstance();
    virtual void destroyInstance();
    //
    /////////////////////////////////////////////////////////////////////////
    //
    // halFDBase () -
    //! \brief FD Hal constructor
    //
    /////////////////////////////////////////////////////////////////////////                       
    halASD(); 

    /////////////////////////////////////////////////////////////////////////
    //
    // ~mhalCamBase () -
    //! \brief mhal cam base descontrustor 
    //
    /////////////////////////////////////////////////////////////////////////    
    virtual ~halASD();
    
    /////////////////////////////////////////////////////////////////////////
    //
    // mHalAUTORAMAInit () -
    //! \brief init autorama
    //
    /////////////////////////////////////////////////////////////////////////     
    virtual MINT32 mHalAsdInit(void* AAAData,void* working_buffer,MUINT8 SensorType, MINT32 width, MINT32 height);

    /////////////////////////////////////////////////////////////////////////
    //
    // mHalAsdUnInit () -
    //! \brief uninit autorama
    //
    /////////////////////////////////////////////////////////////////////////      
    virtual MINT32 mHalAsdUnInit();

    /////////////////////////////////////////////////////////////////////////
    //
    // mHalAsdDoSceneDet () -
    //! \brief Do Scene Det
    //
    /////////////////////////////////////////////////////////////////////////    
    virtual MINT32 mHalAsdDoSceneDet(void* src, MUINT16 imgw, MUINT16 imgh);
    
    /////////////////////////////////////////////////////////////////////////
    //
    // mHalAsdDoSceneDet () -
    //! \brief Asd Decider
    //
    /////////////////////////////////////////////////////////////////////////      
    virtual MINT32 mHalAsdDecider(void* AAAData,void* FDResult,mhal_ASD_DECIDER_UI_SCENE_TYPE_ENUM &Scene);
    
    
protected:


private:
    MTKAsd* m_pMTKAsdObj;   
    ASD_INIT_INFO					          gMyAsdInitInfo;
    ASD_SCD_SET_ENV_INFO_STRUCT		  gMyAsdEnvInfo;					
    ASD_DECIDER_REF_STRUCT			    gMyDeciderEnvInfo;
    ASD_DECIDER_TUNING_PARA_STRUCT	gMyDeciderTuningInfo;   // tuning parameters       
};
 
#endif

