/*
** $Log: strobe_drv.h $
 *
 *
*/

#ifndef _STROBE_DRV_H_
#define _STROBE_DRV_H_

/*******************************************************************************
   * Strobe Command
   *
   ********************************************************************************/
typedef enum
{
    CMD_STROBE_SET_CAP_DELAY = 0,
    CMD_STROBE_GET_WDT_VALUE,
    CMD_STROBE_MAX
} CMD_STROBE_ENUM;



class StrobeDrv
{
protected:

    /*******************************************************************************
       * Functionality : mhal strobe base descontrustor
       *
       ********************************************************************************/
    virtual ~StrobeDrv() = 0;

public:

    /*******************************************************************************
       * Strobe Error Code
       *
       ********************************************************************************/
    typedef enum
    {
        STROBE_NO_ERROR = 0,                  ///< The function work successfully
        STROBE_UNKNOWN_ERROR = 0x80000000,    ///< Unknown error
        STROBE_FILE_ERR,
        STROBE_FILE_ERR2,


        STROBE_ERR_PARA_INVALID,
    } STROBE_ERROR_ENUM;

    /*******************************************************************************
       * Strobe Type
       *
       ********************************************************************************/
    typedef enum
    {
        FLASHLIGHT_NONE = 0,
        FLASHLIGHT_LED_ONOFF,       // LED always on/off
        FLASHLIGHT_LED_CONSTANT,    // CONSTANT type LED
        FLASHLIGHT_LED_PEAK,        // peak strobe type LED
        FLASHLIGHT_LED_TORCH,       // LED turn on when switch FLASH_ON
        FLASHLIGHT_XENON_SCR,       // SCR strobe type Xenon
        FLASHLIGHT_XENON_IGBT       // IGBT strobe type Xenon
    }   FLASHLIGHT_TYPE_ENUM;


    /*******************************************************************************
       * Functionality :
       *
       ********************************************************************************/
    static StrobeDrv*   createInstance();


    /*******************************************************************************
       * Functionality :
       *
       ********************************************************************************/
    virtual void        destroyInstance() = 0 ;


    /*******************************************************************************
       * Functionality :
       *
       ********************************************************************************/
    virtual FLASHLIGHT_TYPE_ENUM getFlashlightType() const = 0;


    /*******************************************************************************
       * Functionality : initialization
       *
       ********************************************************************************/
    virtual int init(unsigned long sensorDev)= 0;


    /*******************************************************************************
       * Functionality : uninitialization
       *
       ********************************************************************************/
    virtual int uninit()= 0;


    /*******************************************************************************
       * Functionality : send IOCTL command to kernel driver to turn on/off the strobe
       *
       ********************************************************************************/
    virtual int setFire(unsigned long a_fire) = 0;


    /*******************************************************************************
       * Functionality : send IOCTL command to kernel driver to set duty of strobe
       *
       ********************************************************************************/
    virtual int setLevel(unsigned long a_level) = 0;


    /*******************************************************************************
       * Functionality :
       *
       ********************************************************************************/
    virtual int setTimeus(unsigned long a_timeus) = 0;


    /*******************************************************************************
       * Functionality :
       *
       ********************************************************************************/
    virtual int setStartTimeus(unsigned long a_timeus) = 0;


    /*******************************************************************************
       * Functionality : send IOCTL command to kernel driver to set state of strobe
       *
       ********************************************************************************/
    virtual int setState(unsigned long a_state) = 0;


    /*******************************************************************************
       * Functionality : control strobe depend on strobe mode
       *
       ********************************************************************************/
    virtual int setFlashlightModeConf(unsigned long a_strobeMode) = 0 ;


    /*******************************************************************************
       * Functionality : control strobe depend on capture parameter of strobe
       *
       ********************************************************************************/
    virtual int setCaptureFlashlightConf(unsigned long a_strobeWidth) = 0;


    /*******************************************************************************
       * Author : Cotta
       * Functionality : commadn control
       *
       ********************************************************************************/
    virtual int sendCommand(unsigned int cmd, unsigned int pArg1, unsigned int *pArg2, unsigned int *pArg3) = 0;


    virtual int setOnOff(int a_isOn) =0;
    virtual int setStep(int step)=0;
	virtual int setDuty(int duty)=0;
	virtual int getFlashReg(int shift, unsigned short* reg)=0;
	virtual int setFlashReg(int shift, unsigned short reg, unsigned short mask)=0;
	virtual int getCoolDownTime(int* ms)=0;

	virtual int lockSensedV()=0;
	virtual int unlockSensedV()=0;
	virtual int mapDutyStep(int peakI, int aveI, int* duty, int* step)=0;

	virtual int getVBat(int* vbat)=0;
	virtual int setTimeOutTime(int ms)=0;



protected:

private:

};

#endif

