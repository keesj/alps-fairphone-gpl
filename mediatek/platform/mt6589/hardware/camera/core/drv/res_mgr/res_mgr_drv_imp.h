#ifndef RES_MGR_DRV_IMP_H
#define RES_MGR_DRV_IMP_H
//-----------------------------------------------------------------------------
using namespace android;
//-----------------------------------------------------------------------------
#define LOG_MSG(fmt, arg...)    XLOGD("[%s]"          fmt, __FUNCTION__,           ##arg)
#define LOG_WRN(fmt, arg...)    XLOGW("[%s]WRN(%5d):" fmt, __FUNCTION__, __LINE__, ##arg)
#define LOG_ERR(fmt, arg...)    XLOGE("[%s]ERR(%5d):" fmt, __FUNCTION__, __LINE__, ##arg)
#define LOG_DMP(fmt, arg...)    XLOGE(""              fmt,                         ##arg)
//-----------------------------------------------------------------------------
#define RES_MGR_DRV_DEVNAME_PIPE_MGR            "/dev/camera-pipemgr"
#define RES_MGR_DRV_DEVNAME_HDMITX              "/dev/hdmitx"
#define RES_MGR_DRV_WAIT_CDP_CONCUR_TIMEOUT     (3000)
#define RES_MGR_DRV_WAIT_CDP_LINK_TIMEOUT       (3000)
//-----------------------------------------------------------------------------
class ResMgrDrvImp : public ResMgrDrv
{
    protected:
        ResMgrDrvImp();
        virtual ~ResMgrDrvImp();
    //
    public:
        static ResMgrDrv* GetInstance(void);
        virtual MVOID   DestroyInstance(void);
        virtual MBOOL   Init(void);
        virtual MBOOL   Uninit(void);
        virtual MBOOL   GetMode(RES_MGR_DRV_MODE_STRUCT* pMode);
        virtual MBOOL   SetMode(RES_MGR_DRV_MODE_STRUCT* pMode);
    private:
        virtual MBOOL   CloseHdmi(MBOOL En);
        //
        mutable Mutex mLock;
        volatile MINT32 mUser;
        MINT32 mFdCamPipeMgr;
        MINT32 mFdHdmiTx;
};
//-----------------------------------------------------------------------------
#endif


