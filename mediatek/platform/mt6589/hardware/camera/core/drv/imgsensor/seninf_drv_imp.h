#ifndef _SENINF_DRV_IMP_H_
#define _SENINF_DRV_IMP_H_


#include <utils/Errors.h>
#include <cutils/log.h>
#include "seninf_drv.h"

//-----------------------------------------------------------------------------

using namespace android;
//-----------------------------------------------------------------------------


#ifndef USING_MTK_LDVT
#define LOG_MSG(fmt, arg...)    ALOGD("[%s]"fmt, __FUNCTION__, ##arg)
#define LOG_WRN(fmt, arg...)    ALOGD("[%s]Warning(%5d):"fmt, __FUNCTION__, __LINE__, ##arg)
#define LOG_ERR(fmt, arg...)    ALOGE("[%s]Err(%5d):"fmt, __FUNCTION__, __LINE__, ##arg)
#else
#include "uvvf.h"

#if 1
#define LOG_MSG(fmt, arg...)    VV_MSG("[%s]"fmt, __FUNCTION__, ##arg)
#define LOG_WRN(fmt, arg...)    VV_MSG("[%s]Warning(%5d):"fmt, __FUNCTION__, __LINE__, ##arg)
#define LOG_ERR(fmt, arg...)    VV_ERRMSG("[%s]Err(%5d):"fmt, __FUNCTION__, __LINE__, ##arg)
#else
#define LOG_MSG(fmt, arg...)    
#define LOG_WRN(fmt, arg...)    
#define LOG_ERR(fmt, arg...)    
#endif    
#endif


/*******************************************************************************
*
********************************************************************************/
class SeninfDrvImp : public SeninfDrv {
public:
    static SeninfDrv* getInstance();
    virtual void destroyInstance();
//
private:
    SeninfDrvImp();
    virtual ~SeninfDrvImp();
//
public:
    virtual int init();
    virtual int uninit();
	virtual int waitSeninf1Irq(int mode);
	virtual int waitSeninf2Irq(int mode);
    virtual unsigned long readReg(unsigned long addr);
    virtual int writeReg(unsigned long addr, unsigned long val);
    virtual int readRegs(reg_t *pregs, int count);
    virtual int writeRegs(reg_t *pregs, int count);
    virtual int holdReg(bool isHold);
    virtual int dumpReg();
    //
    virtual int setTg1PhaseCounter(unsigned long pcEn, unsigned long mclkSel,
        unsigned long clkCnt, unsigned long clkPol,
        unsigned long clkFallEdge, unsigned long clkRiseEdge, unsigned long padPclkInv);
    //
    virtual int setTg2PhaseCounter(unsigned long pcEn, unsigned long mclkSel,
        unsigned long clkCnt, unsigned long clkPol,
        unsigned long clkFallEdge, unsigned long clkRiseEdge, unsigned long padPclkInv);
    //
    virtual int setTg1GrabRange(unsigned long pixelStart, unsigned long pixelEnd,
        unsigned long lineStart, unsigned long lineEnd);
    //
    virtual int setTg2GrabRange(unsigned long pixelStart, unsigned long pixelEnd,
        unsigned long lineStart, unsigned long lineEnd);
    //
    virtual int setTg1SensorModeCfg(unsigned long hsPol, unsigned long vsPol);
	//
	virtual int setTg2SensorModeCfg(unsigned long hsPol, unsigned long vsPol);

    //
    virtual int setTg1ViewFinderMode(unsigned long spMode, unsigned long spDelay);
    //
    virtual int setTg2ViewFinderMode(unsigned long spMode, unsigned long spDelay);

    //
    virtual int setTg1InputCfg(PAD2CAM_DATA_ENUM padSel, SENINF_SOURCE_ENUM inSrcTypeSel,
								 TG_FORMAT_ENUM inDataType, SENSOR_DATA_BITS_ENUM senInLsb);
    //
    virtual int setTg2InputCfg(PAD2CAM_DATA_ENUM padSel, SENINF_SOURCE_ENUM inSrcTypeSel,
								 TG_FORMAT_ENUM inDataType, SENSOR_DATA_BITS_ENUM senInLsb);

    //
    virtual int sendCommand(int cmd, int arg1 = 0, int arg2 = 0, int arg3 = 0);
    //
    virtual int initTg1CSI2(bool csi2_en);
    //
    virtual int initTg2CSI2(bool csi2_en);	
    //
    virtual int setTg1CSI2(unsigned long dataTermDelay, 
                        unsigned long dataSettleDelay, 
                        unsigned long clkTermDelay, 
                        unsigned long vsyncType, 
                        unsigned long dlane_num, 
                        unsigned long csi2_en,
                        unsigned long dataheaderOrder,
                        unsigned long dataFlow);
    //
    virtual int setTg2CSI2(unsigned long dataTermDelay, 
                        unsigned long dataSettleDelay, 
                        unsigned long clkTermDelay, 
                        unsigned long vsyncType, 
                        unsigned long dlane_num, 
                        unsigned long csi2_en,
                        unsigned long dataheaderOrder,
                        unsigned long dataFlow);

	//
    virtual int setTg1IODrivingCurrent(unsigned long ioDrivingCurrent);
	//
    virtual int setTg2IODrivingCurrent(unsigned long ioDrivingCurrent);	
	//
    virtual int setTg1MCLKEn(bool isEn);
	//
    virtual int setTg2MCLKEn(bool isEn);
	//
   	virtual int setFlashA(unsigned long endFrame, unsigned long startPoint, unsigned long lineUnit, unsigned long unitCount, unsigned long startLine, unsigned long startPixel, unsigned long  flashPol);
	//
	virtual int setFlashB(unsigned long contiFrm, unsigned long startFrame, unsigned long lineUnit, unsigned long unitCount, unsigned long startLine, unsigned long startPixel);
	//
	virtual int setFlashEn(bool flashEn);
	//
	virtual int setCCIR656Cfg(CCIR656_OUTPUT_POLARITY_ENUM vsPol, CCIR656_OUTPUT_POLARITY_ENUM hsPol, unsigned long hsStart, unsigned long hsEnd);
	//
	virtual int setN3DCfg(unsigned long n3dEn, unsigned long i2c1En, unsigned long i2c2En, unsigned long n3dMode);
	//
	virtual int setN3DI2CPos(unsigned long n3dPos);
	//
	virtual int setN3DTrigger(bool i2c1TrigOn, bool i2c2TrigOn);
	//
	virtual int checkSeninf1Input();
	//
	virtual int checkSeninf2Input();

private:
    //
    IspDrv *m_pIspDrv;
    volatile int mUsers;
    mutable Mutex mLock;
    int mfd;
	unsigned long *mpIspHwRegAddr;
	unsigned long *mpSeninfHwRegAddr;
    unsigned long *mpPLLHwRegAddr;
    unsigned long *mpIPllCon0RegAddr;
    unsigned long *mpCAMAPConRegAddr;    
    unsigned long *mpCAMIODrvRegAddr;
    unsigned long *mpCAMMMSYSRegAddr;
    unsigned long *mpSENINFClearGateRegAddr;
    unsigned long *mpSENINFSetGateRegAddr;	
    unsigned long *mpCSI2RxAnalogRegStartAddr;    	
    unsigned long *mpCSI2RxAnalogRegAddr;    
    unsigned long *mpCSI2RxConfigRegAddr;       
    unsigned long *mpGpioHwRegAddr;
    unsigned long *mpTg2IOPinMuxCfgAddr;
	MINT32 mDevice;
	int tg1GrabWidth;
	int tg1GrabHeight;
	int tg2GrabWidth;
	int tg2GrabHeight;
    //    
};

#endif // _ISP_DRV_H_

