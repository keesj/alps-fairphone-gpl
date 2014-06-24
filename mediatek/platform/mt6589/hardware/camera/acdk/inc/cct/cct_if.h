#ifndef _CCT_IF_H_
#define _CCT_IF_H_


class IspHal;
/////////////////////////////////////////////////////////////////////////
//! Typedefs 
/////////////////////////////////////////////////////////////////////////
typedef unsigned char   MUINT8;
typedef unsigned short  MUINT16;
typedef unsigned int    MUINT32;
typedef signed char     MINT8;
typedef signed short    MINT16;
typedef signed int      MINT32;
typedef void            MVOID; 
typedef int             MBOOL;


/*******************************************************************************
*
********************************************************************************/
typedef enum {
    CCTIF_NO_ERROR         = 0,            ///< The function work successfully
    CCTIF_UNKNOWN_ERROR    = 0x80000000,   ///< Unknown error    
    CCTIF_INVALID_DRIVER   = 0x80000001,
    CCTIF_UNSUPPORT_SENSOR_TYPE = 0x80000002, 
    CCTIF_BAD_CTRL_CODE, 
    CCTIF_BAD_PARAM, 
    CCTIF_NOT_INIT, 
} CCTIF_ERROR_ENUM;



/*******************************************************************************
*
********************************************************************************/
typedef enum {
    CMD_CCTIF_LOAD_FROM_NVRAM,               //load from nvram
    CMD_CCTIF_SAVE_TO_NVRAM,                   //save to nvram
}CCTIF_NVRAM_CMDS;

/*******************************************************************************
*
********************************************************************************/
class CCTIF
{
protected:

	MINT32  mSensorDev;
    virtual ~CCTIF() {}

public:    

    static CCTIF*   createInstance();
    virtual void    destroyInstance() = 0;
    virtual MINT32  init(MINT32 const sensorType) = 0;
    virtual MINT32  uninit() = 0;

public:    	
	MINT32 setCCTSensorDev(MINT32 sensor_dev);
    virtual MINT32 nvramCCTFeatureControl (MUINT32 a_u4Ioctl, MUINT8 *puParaIn, MUINT32 u4ParaInLen, MUINT8 *puParaOut, MUINT32 u4ParaOutLen, MUINT32 *pu4RealParaOutLen) = 0;
    virtual MINT32 sensorCCTFeatureControl(MUINT32 a_u4Ioctl, MUINT8 *puParaIn, MUINT32 u4ParaInLen, MUINT8 *puParaOut, MUINT32 u4ParaOutLen, MUINT32 *pu4RealParaOutLen) = 0;
    virtual MINT32 aaaCCTFeatureControl(MUINT32 a_u4Ioctl, MUINT8 *puParaIn, MUINT32 u4ParaInLen, MUINT8 *puParaOut, MUINT32 u4ParaOutLen, MUINT32 *pu4RealParaOutLen) = 0;
    virtual MINT32 ispCCTFeatureControl(MUINT32 a_u4Ioctl, MUINT8 *puParaIn, MUINT32 u4ParaInLen, MUINT8 *puParaOut, MUINT32 u4ParaOutLen, MUINT32 *pu4RealParaOutLen) = 0;

};

#endif // _CCT_IF_H_

