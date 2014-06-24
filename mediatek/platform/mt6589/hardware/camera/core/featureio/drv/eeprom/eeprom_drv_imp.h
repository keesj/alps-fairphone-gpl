/*
** $Log: eeprom_drv_imp.h $
 *
 *
*/

#ifndef _EEPROM_DRV_IMP_H_
#define _EEPROM_DRV_IMP_H_

//#include <utils/threads.h>

/*******************************************************************************
*
********************************************************************************/

class EepromDrv : public EepromDrvBase
{
public:
    /////////////////////////////////////////////////////////////////////////
    //
    // getInstance () -
    //! \brief get instance
    //
    /////////////////////////////////////////////////////////////////////////
    static EepromDrvBase* getInstance();

    /////////////////////////////////////////////////////////////////////////
    //
    // destroyInstance () -
    //! \brief destroy instance
    //
    /////////////////////////////////////////////////////////////////////////
    virtual void destroyInstance();
  
    virtual int GetEepromCalData(unsigned long a_eSensorType,
                          unsigned long u4SensorID,
                          CAMERA_EEPROM_TYPE_ENUM a_eEepromDataType,
	                      void *a_pEepromData);	                       

private:
    /////////////////////////////////////////////////////////////////////////
    //
    // EepromDrv () -
    //! \brief constructor
    //
    /////////////////////////////////////////////////////////////////////////
    EepromDrv();

    /////////////////////////////////////////////////////////////////////////
    //
    // ~EepromDrv () -
    //! \brief descontrustor
    //
    /////////////////////////////////////////////////////////////////////////
    virtual ~EepromDrv();

    int Init(unsigned long u4SensorID,void *a_pEepromData)  ;

    
private: 
    static EEPROM_DATA_STRUCT eEepromCaldata;
    static MINT32 m32EepromDataValidation;
};

#endif  //  _NVRAM_DRV_IMP_H_

