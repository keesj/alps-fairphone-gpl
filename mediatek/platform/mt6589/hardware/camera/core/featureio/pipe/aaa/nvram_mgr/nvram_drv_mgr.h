#ifndef _NVRAM_DRV_MGR_H_
#define _NVRAM_DRV_MGR_H_


namespace NS3A
{


/*******************************************************************************
* NVRAM Driver Manager
*******************************************************************************/
class NvramDrvMgr
{
protected:
    virtual ~NvramDrvMgr() {}

public:     ////
    static NvramDrvMgr&   getInstance();

public:     ////    Interfaces.

    virtual MRESULT     init(
        MINT32 const i4SensorDev
    ) = 0;

    virtual MRESULT     uninit() = 0;

public:     ////    Interfaces.

    virtual MVOID   getRefBuf(NVRAM_CAMERA_ISP_PARAM_STRUCT*& rpBuf) const = 0;
    virtual MVOID   getRefBuf(NVRAM_CAMERA_SHADING_STRUCT*& rpBuf) const = 0;
    virtual MVOID   getRefBuf(NVRAM_CAMERA_3A_STRUCT*& rpBuf) const = 0;
    virtual MVOID   getRefBuf(AE_PLINETABLE_T*& rpBuf) const = 0;
    virtual MVOID   getRefBuf(NVRAM_LENS_PARA_STRUCT*& rpBuf) const = 0;
    virtual MVOID   getRefBuf(NVRAM_CAMERA_STROBE_STRUCT*& rpBuf) const = 0;

};


/*******************************************************************************
*
*******************************************************************************/


};  //  NS3A
#endif // _NVRAM_DRV_MGR_H_

