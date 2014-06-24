/*
** $Log: cam_cal_drv_imp.h $
 *
 *
*/

#ifndef _CAM_CAL_DRV_IMP_H_
#define _CAM_CAL_DRV_IMP_H_

//#include <utils/threads.h>

/*******************************************************************************
*
********************************************************************************/

class CamCalDrv : public CamCalDrvBase
{
public:
    /////////////////////////////////////////////////////////////////////////
    //
    // getInstance () -
    //! \brief get instance
    //
    /////////////////////////////////////////////////////////////////////////
    static CamCalDrvBase* getInstance();

    /////////////////////////////////////////////////////////////////////////
    //
    // destroyInstance () -
    //! \brief destroy instance
    //
    /////////////////////////////////////////////////////////////////////////
    virtual void destroyInstance();
  
    virtual int GetCamCalCalData(unsigned long i4SensorDevId,
                          /*unsigned long u4SensorID,*/
                          CAMERA_CAM_CAL_TYPE_ENUM a_eCamCalDataType,
	                      void *a_pCamCalData);	                       

private:
    /////////////////////////////////////////////////////////////////////////
    //
    // CamCalDrv () -
    //! \brief constructor
    //
    /////////////////////////////////////////////////////////////////////////
    CamCalDrv();

    /////////////////////////////////////////////////////////////////////////
    //
    // ~CamCalDrv () -
    //! \brief descontrustor
    //
    /////////////////////////////////////////////////////////////////////////
    virtual ~CamCalDrv();

    int Init(unsigned long u4SensorID,void *a_pCamCalData)  ;

    
private: 
    static CAM_CAL_DATA_STRUCT StCamCalCaldata;
    static MINT32 m32CamCalDataValidation;
};

#endif  //  _NVRAM_DRV_IMP_H_

