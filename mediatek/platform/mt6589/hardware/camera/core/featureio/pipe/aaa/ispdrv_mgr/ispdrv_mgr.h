#ifndef _ISPDRV_MGR_H_
#define _ISPDRV_MGR_H_

#include <isp_drv.h>

namespace NS3A
{

typedef enum
{
    ISPDRV_MODE_ISP = 1,
    ISPDRV_MODE_CQ0 = 2,
    ISPDRV_MODE_CQ1_SYNC = 4,
    ISPDRV_MODE_CQ2_SYNC = 8
} ISPDRV_MODE_T;

typedef struct
{
    MUINT32     addr;
    MUINT32     val;
} ISPREG_INFO_T;

/*******************************************************************************
* ISP Driver Manager
*******************************************************************************/
class IspDrvMgr
{
public:
    typedef enum MERROR_ENUM
    {
        MERR_OK         = 0,
        MERR_UNKNOWN    = 0x80000000, // Unknown error
        MERR_BAD_ISP_DRV,
        MERR_BAD_ISP_ADDR
    } MERROR_ENUM_T;

public:     ////    Interfaces.
    virtual volatile void*  getIspReg(ISPDRV_MODE_T eIspDrvMode) const = 0;
    virtual MBOOL           readRegs(ISPDRV_MODE_T eIspDrvMode, ISPREG_INFO_T*const pRegInfos, MUINT32 const count) = 0;
    virtual MBOOL           writeRegs(CAM_MODULE_ENUM eCamModule, ISPDRV_MODE_T eIspDrvMode, ISPREG_INFO_T*const pRegInfos, MUINT32 const count) = 0;
    virtual MERROR_ENUM_T   init() = 0;
    virtual MERROR_ENUM_T   uninit() = 0;
    //virtual MERROR_ENUM_T   reinit() = 0;

public:     ////
    static IspDrvMgr&   getInstance();

protected:
    virtual ~IspDrvMgr() {}
};


/*******************************************************************************
*
*******************************************************************************/

};//  NS3A

#endif // _ISPDRV_MGR_H_

