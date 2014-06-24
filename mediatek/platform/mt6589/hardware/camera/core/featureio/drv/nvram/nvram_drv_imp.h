/*
** $Log: nvram_drv_imp.h $
 *
 *
*/

#ifndef _NVRAM_DRV_IMP_H_
#define _NVRAM_DRV_IMP_H_

#include <utils/threads.h>

using namespace android; 

/*******************************************************************************
*
********************************************************************************/

class NvramDrv : public NvramDrvBase
{
public:
    /////////////////////////////////////////////////////////////////////////
    //
    // getInstance () -
    //! \brief get instance
    //
    /////////////////////////////////////////////////////////////////////////
    static NvramDrvBase* getInstance();

    /////////////////////////////////////////////////////////////////////////
    //
    // destroyInstance () -
    //! \brief destroy instance
    //
    /////////////////////////////////////////////////////////////////////////
    virtual void destroyInstance();

    /////////////////////////////////////////////////////////////////////////
    //
    // readNvram () -
    //! \brief
    //
    /////////////////////////////////////////////////////////////////////////
    virtual int readNvram(CAMERA_DUAL_CAMERA_SENSOR_ENUM a_eSensorType,
                          unsigned long u4SensorID,
                          CAMERA_DATA_TYPE_ENUM a_eNvramDataType,
	                      void *a_pNvramData,
	                      unsigned long a_u4NvramDataSize);

    /////////////////////////////////////////////////////////////////////////
    //
    // writeNvram () -
    //! \brief
    //
    /////////////////////////////////////////////////////////////////////////
    virtual int writeNvram(CAMERA_DUAL_CAMERA_SENSOR_ENUM a_eSensorType,
                           unsigned long u4SensorID,
                           CAMERA_DATA_TYPE_ENUM a_eNvramDataType,
	                       void *a_pNvramData,
	                       unsigned long a_u4NvramDataSize);

private:
    /////////////////////////////////////////////////////////////////////////
    //
    // NvramDrv () -
    //! \brief constructor
    //
    /////////////////////////////////////////////////////////////////////////
    NvramDrv();

    /////////////////////////////////////////////////////////////////////////
    //
    // ~NvramDrv () -
    //! \brief descontrustor
    //
    /////////////////////////////////////////////////////////////////////////
    virtual ~NvramDrv();

    /////////////////////////////////////////////////////////////////////////
    //
    // checkDataVersion () -
    //! \brief
    //
    /////////////////////////////////////////////////////////////////////////
    int checkDataVersion(CAMERA_DATA_TYPE_ENUM a_eNvramDataType,
	                     void *a_pNvramData);

	/////////////////////////////////////////////////////////////////////////
    //
    // readNvramData () -
    //! \brief
    //
    /////////////////////////////////////////////////////////////////////////
    int readNvramData(CAMERA_DUAL_CAMERA_SENSOR_ENUM a_eSensorType,
                      CAMERA_DATA_TYPE_ENUM a_eCameraDataType,
	                  void *a_pNvramData);

	/////////////////////////////////////////////////////////////////////////
    //
    // writeNvramData () -
    //! \brief
    //
    /////////////////////////////////////////////////////////////////////////
    int writeNvramData(CAMERA_DUAL_CAMERA_SENSOR_ENUM a_eSensorType,
                       CAMERA_DATA_TYPE_ENUM a_eCameraDataType,
	                   void *a_pNvramData);

    /////////////////////////////////////////////////////////////////////////
    //
    // readDefaultData () -
    //! \brief
    //
    /////////////////////////////////////////////////////////////////////////
    int readDefaultData(unsigned long u4SensorID,
                        CAMERA_DATA_TYPE_ENUM a_eCameraDataType,
	                    void *a_pNvramData);

    /////////////////////////////////////////////////////////////////////////
    //
    // testNvramDrv () -
    //! \brief
    //
    /////////////////////////////////////////////////////////////////////////
    void testNvramDrv(CAMERA_DUAL_CAMERA_SENSOR_ENUM a_eSensorType,
                      unsigned long u4SensorID,
                      CAMERA_DATA_TYPE_ENUM a_eCameraDataType,
                      unsigned long a_u4NvramDataSize,
                      unsigned char *a_pNvramData);

private: 
    mutable Mutex mLock; 
    

};

#endif  //  _NVRAM_DRV_IMP_H_

