#ifndef VSS_IMG_TRANS_IMP_H
#define VSS_IMG_TRANS_IMP_H
//----------------------------------------------------------------------------
using namespace android;
//----------------------------------------------------------------------------
#define LOG_MSG(fmt, arg...)    XLOGD("(%d)[%s]"          fmt, ::gettid(), __FUNCTION__,           ##arg)
#define LOG_WRN(fmt, arg...)    XLOGW("(%d)[%s]WRN(%5d):" fmt, ::gettid(), __FUNCTION__, __LINE__, ##arg)
#define LOG_ERR(fmt, arg...)    XLOGE("(%d)[%s]ERR(%5d):" fmt, ::gettid(), __FUNCTION__, __LINE__, ##arg)
#define LOG_DMP(fmt, arg...)    XLOGE("(%d)"              fmt, ::gettid()                          ##arg)
//----------------------------------------------------------------------------
class VssImgTransImp : public VssImgTrans
{
    protected:
        VssImgTransImp();
        ~VssImgTransImp();
    //
    public:
        static VssImgTrans* GetInstance(void);
        virtual void    DestroyInstance(void);
        virtual MBOOL   Init(CONFIG_STRUCT& Config, MUINT32& TpipeNum);
        virtual MBOOL   Uninit(void);
        virtual MBOOL   Start(MUINT32 TpipeIndex);
        virtual MBOOL   WaitDone(void);
        //
        virtual MVOID   ConfigImgi(PortInfo &ImgiPort);
        virtual MVOID   ConfigDispo(PortInfo &DispoPort);
        virtual MVOID   ConfigVido(PortInfo &VidoPort);
        virtual MVOID   ConfigPass2(void);
    //
    private:
        mutable Mutex       mLock;
        volatile MINT32     mUser;
        volatile MUINT32    mTpipeNum;
        volatile MBOOL      mStart;
        CONFIG_STRUCT       mConfig;
        EScenarioFmt        mFormat;
        PortInfo            mImgiPort;
        PortInfo            mDispoPort;
        PortInfo            mVidoPort;
        IPipe*              mpPipePass2;
        IPostProcPipe*      mpPostProcPipe;
        ICdpPipe*           mpCdpPipe;
        vector<PortInfo const*> mvPortIn;
        vector<PortInfo const*> mvPortOut;
};
//----------------------------------------------------------------------------
#endif





