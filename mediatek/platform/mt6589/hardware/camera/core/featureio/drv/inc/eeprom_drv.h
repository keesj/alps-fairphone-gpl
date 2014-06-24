/*
** $Log: eeprom_drv.h $
 *
 *
*/

#ifndef _EEPROM_DRV_H_
#define _EEPROM_DRV_H_

#include "camera_custom_nvram.h"
#include "camera_custom_eeprom.h"
#define DRV_EEPROM_SUPPORT (0)
#ifndef USING_MTK_LDVT
    #define EEPROM_SUPPORT
#endif
typedef enum {
    EEPROM_NO_ERROR  = 0,            ///< The function work successfully
    EEPROM_UNKNOWN   = 0x80000000,   ///< Unknown error
    EEPROM_READ_PARAMETER_ERROR,     ///< EEPROM read parameter error
    EEPROM_PARAMETER_INVALIDITY,    ///< EEPROM write parameter error
    EEPROM_CAMERA_FILE_ERROR,        ///< EEPROM camera file error
    EEPROM_MEMORY_ALLOCATE_ERROR,    ///< EEPROM memory alocate error
    EEPROM_DATA_READ_ERROR,          ///< EEPROM data read error
    EEPROM_DATA_WRITE_ERROR,         ///< EEPROM data write error
    EEPROM_DEFAULT_DATA_READ_ERROR,  ///< EEPROM data read error
    EEPROM_DATA_VERSION_ERROR,       ///< EEPROM data version error
    EEPROM_BAD_SENSOR_ENUM,          ///< EEPROM bad sensor enum
} EEPROM_ERROR_ENUM;

typedef enum {

    EEPROM_MASK_SHADING = 0x01,
    EEPROM_MASK_DEFECT = 0x02,
    EEPROM_MASK_PREGAIN = 0x04,
    EEPROM_MASK_ALL  = 0x07
} EEPROM_MASK_ENUM;





/*******************************************************************************
*
********************************************************************************/

class EepromDrvBase {

public:
    /////////////////////////////////////////////////////////////////////////
    //
    // createInstance () -
    //! \brief create instance
    //
    /////////////////////////////////////////////////////////////////////////
    static EepromDrvBase* createInstance();

    /////////////////////////////////////////////////////////////////////////
    //
    // destroyInstance () -
    //! \brief destroy instance
    //
    /////////////////////////////////////////////////////////////////////////
    virtual void destroyInstance() = 0;

    /////////////////////////////////////////////////////////////////////////
    //
    // readEeprom () -
    //! \brief
    //
    /////////////////////////////////////////////////////////////////////////
	virtual int GetEepromCalData(unsigned long a_eSensorType,
                          unsigned long u4SensorID,
                          CAMERA_EEPROM_TYPE_ENUM a_eEepromDataType,
	                      void *a_pEepromData) = 0;

protected:
    /////////////////////////////////////////////////////////////////////////
    //
    // ~EepromDrvBase () -
    //! \brief descontrustor
    //
    /////////////////////////////////////////////////////////////////////////
    virtual ~EepromDrvBase() {}

private:
	
};





#endif  

