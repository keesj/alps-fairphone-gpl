/*
** $Log: cam_cal_drv.h $
 *
 *
*/

#ifndef _CAM_CAL_DRV_H_
#define _CAM_CAL_DRV_H_

//seaniln 121017 for 658x #include "camera_custom_nvram.h"
#include "camera_custom_cam_cal.h"
#define DRV_CAM_CAL_SUPPORT (0)

#include "camera_custom_nvram.h"
#ifndef USING_MTK_LDVT
    #define CAM_CAL_SUPPORT
#endif
/* //SeanLin@121116 No Use>
typedef enum {
    CAM_CAL_NO_ERROR  = 0,            ///< The function work successfully
    CAM_CAL_UNKNOWN   = 0x80000000,   ///< Unknown error
    CAM_CAL_READ_PARAMETER_ERROR,     ///< CAM_CAL read parameter error
    CAM_CAL_PARAMETER_INVALIDITY,    ///< CAM_CAL write parameter error
    CAM_CAL_CAMERA_FILE_ERROR,        ///< CAM_CAL camera file error
    CAM_CAL_MEMORY_ALLOCATE_ERROR,    ///< CAM_CAL memory alocate error
    CAM_CAL_DATA_READ_ERROR,          ///< CAM_CAL data read error
    CAM_CAL_DATA_WRITE_ERROR,         ///< CAM_CAL data write error
    CAM_CAL_DEFAULT_DATA_READ_ERROR,  ///< CAM_CAL data read error
    CAM_CAL_DATA_VERSION_ERROR,       ///< CAM_CAL data version error
    CAM_CAL_BAD_SENSOR_ENUM,          ///< CAM_CAL bad sensor enum
} CAM_CAL_ERROR_ENUM;
typedef enum {

    CAM_CAL_MASK_SHADING = 0x01,
    CAM_CAL_MASK_DEFECT = 0x02,
    CAM_CAL_MASK_PREGAIN = 0x04,
    CAM_CAL_MASK_ALL  = 0x07
} CAM_CAL_MASK_ENUM;


*/ //SeanLin@121116 No Use<



/*******************************************************************************
*
********************************************************************************/

class CamCalDrvBase {

public:
    /////////////////////////////////////////////////////////////////////////
    //
    // createInstance () -
    //! \brief create instance
    //
    /////////////////////////////////////////////////////////////////////////
    static CamCalDrvBase* createInstance();

    /////////////////////////////////////////////////////////////////////////
    //
    // destroyInstance () -
    //! \brief destroy instance
    //
    /////////////////////////////////////////////////////////////////////////
    virtual void destroyInstance() = 0;

    /////////////////////////////////////////////////////////////////////////
    //
    // readCamCal () -
    //! \brief
    //
    /////////////////////////////////////////////////////////////////////////
	virtual int GetCamCalCalData(unsigned long i4SensorDevId,
                          /*unsigned long u4SensorID,*/
                          CAMERA_CAM_CAL_TYPE_ENUM a_eCamCalDataType,
	                      void *a_pCamCalData) = 0;

protected:
    /////////////////////////////////////////////////////////////////////////
    //
    // ~CamCalDrvBase () -
    //! \brief descontrustor
    //
    /////////////////////////////////////////////////////////////////////////
    virtual ~CamCalDrvBase() {}

private:
	
};





#endif  

