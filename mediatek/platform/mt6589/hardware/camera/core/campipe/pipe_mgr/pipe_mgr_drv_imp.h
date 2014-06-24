#ifndef PIPE_MGR_DRV_IMP_H
#define PIPE_MGR_DRV_IMP_H
//-----------------------------------------------------------------------------
using namespace android;
//-----------------------------------------------------------------------------
#define LOG_MSG(fmt, arg...)    XLOGD("[%s]"          fmt, __FUNCTION__,           ##arg)
#define LOG_WRN(fmt, arg...)    XLOGW("[%s]WRN(%5d):" fmt, __FUNCTION__, __LINE__, ##arg)
#define LOG_ERR(fmt, arg...)    XLOGE("[%s]ERR(%5d):" fmt, __FUNCTION__, __LINE__, ##arg)
#define LOG_DMP(fmt, arg...)    XLOGE(""              fmt,                         ##arg)
//-----------------------------------------------------------------------------
#define PIPE_MGR_DRV_DEVNAME    "/dev/camera-pipemgr"
//-----------------------------------------------------------------------------
class PipeMgrDrvImp : public PipeMgrDrv
{
    protected:
        PipeMgrDrvImp();
        virtual ~PipeMgrDrvImp();
    //
    public:
        static PipeMgrDrv* GetInstance(void);
        virtual MVOID   DestroyInstance(void);
        virtual MBOOL   Init(void);
        virtual MBOOL   Uninit(void);
        virtual MBOOL   Lock(PIPE_MGR_DRV_LOCK_STRUCT* pLock);
        virtual MBOOL   Unlock(PIPE_MGR_DRV_UNLOCK_STRUCT* pUnlock);
        virtual MBOOL   Dump(void);
        //
    private:
        mutable Mutex mLock;
        volatile MINT32 mUser;
        MINT32 mFd;
        MUINT32 mLogMask;
};
//-----------------------------------------------------------------------------
#endif

